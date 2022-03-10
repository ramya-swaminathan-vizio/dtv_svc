// Copyright (C) 2021 VIZIO, Inc.  All rights reserved.
//
#include "systemui_visibility.h"

#include <atomic>
#include <chrono>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <thread>
#include <unistd.h>

#include <broker.h>
#include <connection.h>
#include <systemregistry.h>

namespace ipc = vizio::ipc;

const std::chrono::milliseconds _checkExit = std::chrono::milliseconds(100);
const std::chrono::milliseconds _wait = std::chrono::seconds(2);

using SystemUIStateEnumMap = std::map<std::string, SystemUIState>;
SystemUIStateEnumMap toEnumMap {
  {"Visible", SystemUIState::SystemUIStateVisible},
  {"Invisible", SystemUIState::SystemUIStateInvisible},
  {"Unknown", SystemUIState::SystemUIStateUnknown}
};

bool toEnum(const std::string& s, SystemUIState& state)
{
  auto ms = toEnumMap.find(s);
  if (toEnumMap.end() != ms)
  {
    state = ms->second;
    return true;
  }
  return false;
}

const std::string _srServerName = "SystemRegistry";

template<typename TReply, typename TRequest> std::unique_ptr<TReply> sendMessage(std::unique_ptr<ipc::Connection> & channel, const TRequest & message, const std::string & id)
{
  ipc::SerializableMessage<TRequest> request(message);
  auto sent = channel->send(request, id);
  if (sent)
  {
    auto reply = channel->receiveSerialized<TReply>(id);
    if(reply.second) {
      return std::make_unique<TReply>(*reply.first);
    }
  }
  return nullptr;
}

std::unique_ptr<SysRegSubscribeEvent> waitForEvent(std::unique_ptr<ipc::Connection> & channel, std::chrono::milliseconds timeout = std::chrono::milliseconds(TEN_YEARS_IN_MS))
{
  auto event = channel->receiveSerialized<SysRegSubscribeEvent>(SYSREG_CMD_ID_SUBSCRIBE_EVENT, timeout);
  if (event.second) {
    return std::make_unique<SysRegSubscribeEvent>(*event.first);
  }
  return nullptr;
}

bool subscribeSystemUIStateEvent(std::unique_ptr<ipc::Connection>& connection, const std::string& topic)
{
  if (topic.empty())
  {
    std::cout << "Topic is empty!" << std::endl;
    return false;
  }

  SysRegSubscribeRequest request(topic);
  auto reply = sendMessage<SysRegSubscribeResponse>(connection, request, SYSREG_CMD_ID_SUBSCRIBE);
  if (!reply || (reply && reply->status != SYSREG_RESULT_SUCCESS))
  {
    std::cout << "Failed to subscribe." << std::endl;
    return false;
  }
  std::cout << "Successfully subscribed." << std::endl;
  return true;
}

bool getSystemUIStateEvent(std::unique_ptr<ipc::Connection>& connection,
       const std::string& topic,
       std::chrono::milliseconds  timeout = _wait)
{
  if (topic.empty())
  {
    std::cout << "Topic is empty!" << std::endl;
    return false;
  }

  auto event = waitForEvent(connection);
  if (!event || (event && (event->key != topic || event->reason != SYSREG_EVENT_CHANGE)))
  {
    std::cout << "Failed waitForEvent!" << std::endl;
    if (!event)
    {
      std::cout << "No event object replied!" << std::endl;
    }
    else
    {
      std::cout << "Failed to get a unsuccessful changed event!" << std::endl;
    }

    return false;
  }
  std::cout << "Successfully get a changed event!" << std::endl;

  return true;
}

std::string getSystemUIState(std::unique_ptr<ipc::Connection> & connection, const std::string & topic)
{
  std::string visibility;
  if (topic.empty())
  {
    std::cout << "Topic is empty!" << std::endl;
    return visibility;
  }

  SysRegGetRequest request(topic);
  auto reply = sendMessage<SysRegGetResponse>(connection, request, SYSREG_CMD_ID_GET);
  if (!reply || (reply && reply->status != SYSREG_RESULT_SUCCESS))
  {
    std::cout << "Failed to get SystemUI state." << std::endl;
  }
  else
  {
    visibility = reply->value;
  }

  std::cout << "Successfully received SystemUI state." << std::endl;

  return visibility;
}


auto printSystemUIState = [](SystemUIState visibility) -> void { std::cout << "SystemUIState: There is no registered callback!" << std::endl;};
struct _SystemUIClient
{
  std::unique_ptr<ipc::Connection> _connection{std::unique_ptr<ipc::Connection>()};
  std::atomic<bool> _initialized{false};
  std::atomic<bool> _exit{false};
  SystemUIState _state{SystemUIState::SystemUIStateUnknown};
  FUNC_PTR_SYSTEMUISTATE _callback{printSystemUIState};
  std::mutex _mtx;

  bool initialize()
  {
    ipc::Broker& broker = ipc::Broker::getDefaultBroker();
    _connection = broker.connectToServer(_srServerName);
    return (_initialized = (nullptr != _connection) ? true : false);
  }
};

_SystemUIClient _systemuiClient;


bool initializeSystemUIState()
{
  std::cout << "Initialize SystemUIState..." << std::endl;
  if (!_systemuiClient._initialized)
  {
    if (!_systemuiClient.initialize())
    {
      std::cout << "Failed initializeSystemUIState" << std::endl;
      return false;
    }
  }

  std::thread cReceiver([&] {
    while (!_systemuiClient._exit) {
      if (!subscribeSystemUIStateEvent(_systemuiClient._connection, "/systemui/visibility"))
      {
        std::cout << "Failed to subcribe." << std::endl;
        std::this_thread::sleep_for(_checkExit);
        continue;
      }

      if (!getSystemUIStateEvent(_systemuiClient._connection, "/systemui/visibility"))
      {
        std::cout << "Failed getSystemUIStateEvent" << std::endl;
        std::this_thread::sleep_for(_checkExit);
        continue;
      }

      auto reply = getSystemUIState(_systemuiClient._connection, "/systemui/visibility");
      if (reply.empty())
      {
        std::cout << "returns empty string." << std::endl;
        std::this_thread::sleep_for(_checkExit);
        continue;
      }

      if (!toEnum(reply, _systemuiClient._state))
      {
        std::cout << "Failed to find in toEnum()." << std::endl;
        std::this_thread::sleep_for(_checkExit);
        continue;
      }
      std::cout << "Invoke callback." << std::endl;

      std::unique_lock<std::mutex> lock(_systemuiClient._mtx);
      _systemuiClient._callback(_systemuiClient._state);
      lock.unlock();

    } //end of while (!_systemuiClient._exit)
   }); //end of std::thread cReceiver([&]

  cReceiver.detach();
  return true;
}

bool deinitializeSystemUIState()
{
  std::cout << "Deinitialize SystemUIState..." << std::endl;
  return (_systemuiClient._exit = true);
}

SystemUIState getCurrentSystemUIState()
{
  std::cout << "Calling getCurrentSystemUIState..." << std::endl;
  return _systemuiClient._state;
}

bool onSystemUIStateChange(FUNC_PTR_SYSTEMUISTATE callback)
{
  std::cout << "Calling onSystemUIStateChange..." << std::endl;
  std::lock_guard<std::mutex> lock(_systemuiClient._mtx);
  _systemuiClient._callback = callback;
  return true;
}
