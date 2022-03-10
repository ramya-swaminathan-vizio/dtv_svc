#pragma once

#include <sstream>

//
// SystemRegistry is a wrapper around systemregistry to ease interaction with
// it. An example workflow is as follows:
//
// 1) Create an instance of the SystemRegistry class. It will create a connection
// to the systemregistry.
// 2) Initialize the wrapper with ::initialize() function. In the case of an
// error it returns 'false'.
// 3) Work with systemregistry through the public member functions.
//
// One could use the following member functions to interact with
// systemregistry:
//
// get -- get a value of a key
// update -- set a value to existed key
// create -- create a key recursively
// enumerate -- return a vector of strings with keys in specified key
// remove -- delete a key
// subscribe -- subscribe for an event
// exists -- check whether a key does exist
// getStatus -- get the latest status of an operation with systemregistry
//
// For more info please refer to a specific member function description.
//

namespace vizio
{
namespace systemregistry
{
using SysRegCallback = std::function<bool(const std::string &, sysreg_event_t)>;

class SystemRegistry
{
  public:
   SystemRegistry(vizio::ipc::Broker & broker)
         : _broker(broker), _channel(broker.connectToServer("SystemRegistry")),
           _status(SYSREG_RESULT_SUCCESS), _keep(true)
   {
   }

   // Desctructor would interrupt Broker in order to release the thread
   // in the case if it waits for an event.
   ~SystemRegistry()
   {
      if (_thread.joinable()) {
         // Wait for thread to finish
         _keep = false;
         _broker.interrupt();
         _block.notify_one();
         _thread.join();
      }
   }

   bool initialize();

   std::pair<std::string, bool> get(const std::string & key);
   bool                         update(const std::string & key, const std::string & value);
   bool                         create(const std::string & key, const std::string & value = "",
                                 const std::string & perm  = SYSREG_META_DEFAULT_PERM,
                                 const std::string & owner = SYSREG_META_DEFAULT_OWNER);
   std::pair<std::vector<std::string>, bool> enumerate(const std::string & key);
   bool                                      remove(const std::string & key);
   bool subscribe(const std::string & key, SysRegCallback callback = nullptr);
   std::pair<std::string, bool> exists(const std::string & key);

   sysreg_status_t getStatus() const
   {
      return _status;
   }

  private:
   vizio::ipc::Broker &                    _broker;
   std::unique_ptr<vizio::ipc::Connection> _channel;
   sysreg_status_t                         _status;
   std::thread                             _thread;
   std::map<std::string, SysRegCallback>   _eventCallbacks;
   std::mutex                              _mutex;
   std::condition_variable                 _block;
   bool                                    _keep;

   bool isVersionOk();
   bool auth();
};

// Initialize the wrapper. If it fails it returns 'false'.
// During initialization it will authenticate and check the version of
// systemregistry.
inline bool SystemRegistry::initialize()
{
   if (!_channel) {
      return false;
   }
   if (!auth()) {
      _channel.reset(nullptr);
      return false;
   }
   if (!isVersionOk()) {
      _channel.reset(nullptr);
      return false;
   }

   return true;
}

// Get a value for a key. The value would be stored in the second argument.
inline std::pair<std::string, bool> SystemRegistry::get(const std::string & key)
{
   std::stringstream ss;
   ss << std::this_thread::get_id();
   size_t      subtopic = vizio::ipc::hash(ss.str(), size_t(0));
   std::string rxTopic  = std::string(SYSREG_CMD_ID_GET) + ":" + std::to_string(subtopic);

   vizio::ipc::SerializableMessage<SysRegGetRequest> request(key);
   request.subTopic(subtopic);
   auto ret = _channel->sendAndReceiveSerialized<SysRegGetResponse>(
         request, SYSREG_CMD_ID_GET, rxTopic);
   auto & reply   = ret.first;
   auto   success = ret.second;

   _status = success ? reply->status : SYSREG_RESULT_INTERNAL_ERROR;
   success = _status == SYSREG_RESULT_SUCCESS;

   return std::make_pair(std::move(reply->value), success);
}

// Set a value to a key
inline bool SystemRegistry::update(const std::string & key, const std::string & value)
{
   std::stringstream ss;
   ss << std::this_thread::get_id();
   size_t      subtopic = vizio::ipc::hash(ss.str(), size_t(0));
   std::string rxTopic  = std::string(SYSREG_CMD_ID_UPDATE) + ":" + std::to_string(subtopic);

   vizio::ipc::SerializableMessage<SysRegUpdateRequest> request(key, value);
   request.subTopic(subtopic);
   auto ret = _channel->sendAndReceiveSerialized<SysRegUpdateResponse>(
         request, SYSREG_CMD_ID_UPDATE, rxTopic);
   auto & reply   = ret.first;
   auto   success = ret.second;

   if (!success) {
      _status = SYSREG_RESULT_INTERNAL_ERROR;
      return false;
   }

   _status = reply->status;
   return _status == SYSREG_RESULT_SUCCESS;
}

// Create a key with specific value, permission and owner. By default value is
// empty, permission and owner are default. This function would recursively
// create keys which does not exist. These keys would have default permission
// and owner. Only for a leaf key the permission and owner would be specified
// from the arguments
inline bool SystemRegistry::create(const std::string & key, const std::string & value,
      const std::string & perm, const std::string & owner)
{
   auto createKey = [this](const std::string & key, const std::string & value,
                          const std::string & perm, const std::string & owner) {
      std::stringstream ss;
      ss << std::this_thread::get_id();
      size_t      subtopic = vizio::ipc::hash(ss.str(), size_t(0));
      std::string rxTopic  = std::string(SYSREG_CMD_ID_CREATE) + ":" + std::to_string(subtopic);

      vizio::ipc::SerializableMessage<SysRegCreateRequest> request(
            key, value, SYSREG_FLAG_NONE, perm, owner);
      request.subTopic(subtopic);
      auto ret = _channel->sendAndReceiveSerialized<SysRegCreateResponse>(
            request, SYSREG_CMD_ID_CREATE, rxTopic);
      auto & reply   = ret.first;
      auto   success = ret.second;

      if (!success) {
         return SYSREG_RESULT_INTERNAL_ERROR;
      }

      return reply->status;
   };

   // Basic sanity check
   if (key[0] != '/') {
      _status = SYSREG_RESULT_INVALID_ARGUMENT;
      return false;
   }

   std::stringstream        keyPath(key);
   std::vector<std::string> tokens;
   std::string              token;
   std::string              path;

   bool notEOF = true;
   while (notEOF) {
      auto & st = getline(keyPath, token, '/');
      if (token.empty()) {
         continue;
      }

      path += "/" + token;

      if (!st.eof()) {
         _status = createKey(path, "", SYSREG_META_DEFAULT_PERM, SYSREG_META_DEFAULT_OWNER);
         if (_status != SYSREG_RESULT_SUCCESS && _status != SYSREG_RESULT_EXIST) {
            return false;
         }
      } else {
         notEOF  = false;
         _status = createKey(path, value, perm, owner);
      }
   }

   return _status == SYSREG_RESULT_SUCCESS;
}

// List keys at a 'key' path. The result vector would contains strings with
// keys.
inline std::pair<std::vector<std::string>, bool> SystemRegistry::enumerate(const std::string & key)
{
   std::stringstream ss;
   ss << std::this_thread::get_id();
   size_t      subtopic = vizio::ipc::hash(ss.str(), size_t(0));
   std::string rxTopic  = std::string(SYSREG_CMD_ID_ENUMERATE) + ":" + std::to_string(subtopic);

   vizio::ipc::SerializableMessage<SysRegEnumerateRequest> request(key);
   request.subTopic(subtopic);

   auto ret = _channel->sendAndReceiveSerialized<SysRegEnumerateResponse>(
         request, SYSREG_CMD_ID_ENUMERATE, rxTopic);
   auto & reply   = ret.first;
   auto   success = ret.second;

   _status = success ? reply->status : SYSREG_RESULT_INTERNAL_ERROR;
   success = _status == SYSREG_RESULT_SUCCESS;

   return std::make_pair(std::move(reply->value), success);
}

// Delete a key from systemregistry
inline bool SystemRegistry::remove(const std::string & key)
{
   std::stringstream ss;
   ss << std::this_thread::get_id();
   size_t      subtopic = vizio::ipc::hash(ss.str(), size_t(0));
   std::string rxTopic  = std::string(SYSREG_CMD_ID_REMOVE) + ":" + std::to_string(subtopic);

   vizio::ipc::SerializableMessage<SysRegRemoveRequest> request(key);
   request.subTopic(subtopic);

   auto ret = _channel->sendAndReceiveSerialized<SysRegRemoveResponse>(
         request, SYSREG_CMD_ID_REMOVE, rxTopic);
   auto & reply   = ret.first;
   auto   success = ret.second;

   if (!success) {
      _status = SYSREG_RESULT_INTERNAL_ERROR;
      return false;
   }
   _status = reply->status;
   return _status == SYSREG_RESULT_SUCCESS;
}

// Subscribe to an event (change or delete). callback is a function to be
// called when the event arrives. The callback function should return 'true'
// or 'false':
// 'true'  -- keep receiving events for specific key and call the corresponding callback function.
// 'false' -- unsubscribe from specific key and erase the callback function
//            from _eventCallbacks.
inline bool SystemRegistry::subscribe(const std::string & key, SysRegCallback callback)
{
   if (callback == nullptr) {
      return false;
   }

   std::stringstream ss;
   ss << std::this_thread::get_id();
   size_t      subtopic = vizio::ipc::hash(ss.str(), size_t(0));
   std::string rxTopic  = std::string(SYSREG_CMD_ID_SUBSCRIBE) + ":" + std::to_string(subtopic);
   std::string rxTopicEvent
         = std::string(SYSREG_CMD_ID_SUBSCRIBE_EVENT) + ":" + std::to_string(subtopic);

   vizio::ipc::SerializableMessage<SysRegSubscribeRequest> request(key);
   request.subTopic(subtopic);

   auto ret = _channel->sendAndReceiveSerialized<SysRegSubscribeResponse>(
         request, SYSREG_CMD_ID_SUBSCRIBE, rxTopic);
   auto & reply   = ret.first;
   auto   success = ret.second;

   if (!success || (success && reply->status != SYSREG_RESULT_SUCCESS)) {
      return false;
   } else {
      std::lock_guard<std::mutex> lock(_mutex);
      auto                        cbfn = _eventCallbacks.find(key);
      if (cbfn == _eventCallbacks.end()) {
         _eventCallbacks[key] = callback;
         _block.notify_one();
      } else {
         return false;
      }
   }

   if (_thread.get_id() == std::thread::id()) {
      _thread = std::thread([this, rxTopicEvent] {
         while (_keep) {
            auto   ret     = _channel->receiveSerialized<SysRegSubscribeEvent>(rxTopicEvent);
            auto & reply   = ret.first;
            auto   success = ret.second;

            if (success) {
               auto &                            event = reply;
               const std::lock_guard<std::mutex> lock(_mutex);
               auto &                            key    = event->key;
               auto &                            reason = event->reason;
               auto                              cbfn   = _eventCallbacks.find(key);
               if (cbfn != _eventCallbacks.end() && !cbfn->second(key, reason)) {
                  std::stringstream ss;
                  ss << std::this_thread::get_id();
                  size_t      subtopic = vizio::ipc::hash(ss.str(), size_t(0));
                  std::string rxTopic
                        = std::string(SYSREG_CMD_ID_UNSUBSCRIBE) + ":" + std::to_string(subtopic);

                  vizio::ipc::SerializableMessage<SysRegUnsubscribeRequest> request(key);
                  request.subTopic(subtopic);

                  auto retval = _channel->sendAndReceiveSerialized<SysRegUnsubscribeResponse>(
                        request, SYSREG_CMD_ID_UNSUBSCRIBE, rxTopic);
                  auto & response   = retval.first;
                  auto   successval = retval.second;
                  if (successval && response->status == SYSREG_RESULT_SUCCESS) {
                     _eventCallbacks.erase(cbfn);
                  }
               }
            }
            {
               std::unique_lock<std::mutex> lock(_mutex);
               if (_eventCallbacks.empty()) {
                  _block.wait(lock);
               }
            }
         }
      });
   }

   return true;
}

// Check whether a key does exist. In the case when a second value of a pair
// is false the function returns path to a first node which doesn't exist. If
// the second value is true, then it returns path which is equals to a key
// argument.
inline std::pair<std::string, bool> SystemRegistry::exists(const std::string & key)
{
   std::stringstream        keyPath(key);
   std::vector<std::string> tokens;
   std::string              path, token;

   // Basic sanity check
   if (key[0] != '/') {
      _status = SYSREG_RESULT_INVALID_ARGUMENT;
      return std::make_pair("", false);
   }

   // Tokenize the key path
   while (getline(keyPath, token, '/')) {
      if (!token.empty()) {
         tokens.push_back(token);
      }
   }

   auto noNode = [this, &path](auto node) {
      std::string checkPath = path + "/" + node;
      this->get(checkPath);
      bool ok = _status == SYSREG_RESULT_SUCCESS || _status == SYSREG_RESULT_EXIST
                || _status == SYSREG_RESULT_PERMISSION_DENY;

      if (ok) {
         path += "/" + node;
      }
      return !ok;
   };

   bool isOk = !std::any_of(tokens.begin(), tokens.end(), noNode);
   return std::make_pair(std::move(path), isOk);
}

// Check that the versions are compatible
inline bool SystemRegistry::isVersionOk()
{
   std::stringstream ss;
   ss << std::this_thread::get_id();
   size_t      subtopic = vizio::ipc::hash(ss.str(), size_t(0));
   std::string rxTopic  = std::string(SYSREG_CMD_ID_API_VERSION) + ":" + std::to_string(subtopic);

   vizio::ipc::SerializableMessage<SysRegVersionRequest> request(SYSREG_VERSION);
   request.subTopic(subtopic);
   auto ret = _channel->sendAndReceiveSerialized<SysRegVersionResponse>(
         request, SYSREG_CMD_ID_API_VERSION, rxTopic);
   auto & reply   = ret.first;
   auto   success = ret.second;

   return success && reply->isCompatible;
}

// Authenticate
inline bool SystemRegistry::auth()
{
   // Just a stub
   return true;
}

}   // namespace systemregistry
}   // namespace vizio
