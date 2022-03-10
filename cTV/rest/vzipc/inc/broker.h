//
// broker.h
// © 2020 Vizio Services, All Rights Reserved
//
// This header file documents the Broker class, which is used to faciliate the creation of
// Connection objects.
//
// Under the hood, the IPC mechanism that drives the ViziOS messaging system is the XSI Message
// Queue primitive.  Any number of writers can add to a queue, and any number of readers can read
// from a queue (assuming all the permissions are right).  However, since every read from a queue
// removes the message permanently, message queues are not especially suitable for broadcast
// messages, and they are not even perfectly suited for point-to-point messaging since another
// reader can grab a message.
//
// To deal with this and create a more familiar point-to-point or connection-like interface, the
// Broker class handles the construction of Connection objects, which aren't actually stateful
// connections at all but constucts that provide a comfortable send/receive API for sharing messages
// between two message queues.  The concept of 'topics' (short human-readable strings) are paired
// with the messages due to the fact that in order to receive a message, you need to know its type.
// Thus, by using a single type per topic, a sender and receiver can agree on the type of message
// being transmitted.
//
// It is possible to have multiple Broker classes in a single application, but the assumption is
// that there will be only one.  If the application is a singleton (like a system daemon), it should
// typically use Broker::getDefaultServerBroker() to acquire its Broker object.  Any other
// application can connect to this process simply by knowing the process name ('storaged', for
// example).  When multiple applications of the same type can exist, the applications should use
// Broker::getDefaultBroker() to acquire their Broker object.  Different instances are
// distinguishable by their PIDs, but the server does not need to worry about this as long as it
// calls Broker::acceptClientConnection() to create a connection to one of these application
// instances, and the application instance calls Broker::connectToServer() to connect to the server.
//

#pragma once

#include <chrono>
#include <condition_variable>
#include <deque>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <sys/types.h>
#include <thread>
#include <vizio-log/logger.h>

#include "internal/ipc.h"
#include "message_queue.h"

#define TEN_YEARS_IN_MS 315569520000

namespace vizio
{
namespace ipc
{
// clang-format off
template<typename T> class Message;
template<>           class Message<void>;
// clang-format on

class Connection;

enum Settings {
   // if enabled, when the endpoint does not exist, Broker::connectToServer API will return NULL.
   // if enabled, when the endpoint does not exist, Connection::send API will return false.
   // by default disabled
   BROKER_KEEP_ALIVE_MODE = 1,
};

class Broker
{
  public:
   Broker();
   Broker(Broker &&) = delete;
   ~Broker();

   // These functions return a Broker initialized in the conventional way, which is as follows:
   //    For a singleton app / server:        { process name from command line, pid = 0 }
   //    For a regular or multi-instance app: { process name from command line, pid = getpid() }
   // These functions call initialize() on the resulting broker and will return an empty
   // std::shared_ptr if initialize() fails.
   static Broker & getDefaultBroker();
   static Broker & getDefaultServerBroker();

   // Initialize a Broker object if creating one directly.  The Broker object can be initialized
   // only once.
   bool initialize(const std::string & appName, pid_t pid);

   // Stop the Broker.  Once this is called, the Broker will no longer accept new connections or
   // messages.  Any blocking APIs such as acceptClientConnection() will be interrupted and the
   // functions will return immediately.  If messages have been received by the Broker but not
   // processed by a user, they will still be available for retrieval.
   void stop();

   // Enable/Disable various broker settings
   void setSettings(Settings option, bool enabled);

   // Establish an outbound connection to another application following a peer-to-peer model.
   // The other application also needs to call this API to connect back.
   std::unique_ptr<Connection> connectToPeer(const std::string & appName, pid_t pid);

   // Establish a connection based on a client-server model.  Two (or more) applications agree
   // on which one will be the "server" and which will be the "client(s)".  The "client" calls
   // connectToServer().  The "server" calls acceptClientConnection().
   std::unique_ptr<Connection> connectToServer(const std::string & appName, pid_t pid = 0);

   // Establish a connection based on a client-server model.  The "server" calls the blocking
   // call acceptClientConnection(), which will return with a Connection object initialized to
   // communicate with the client after it calls connectToServer().
   std::unique_ptr<Connection> acceptClientConnection();

   // Establish a loop-back connection to the local Broker.  This can be used to send messages
   // from one part of an application to another, or from one thread to another inside the same
   // process.
   std::unique_ptr<Connection> connectToSelf();

   // Send a message to all connections in the set.  Note that if there are multiple connections
   // to the same target in the set, the message will be sent multiple times.  If 'block' is
   // true, it will block until all messages have been sent (or an error occurs).  This method
   // will return true if the message was successfully sent to all connections; false otherwise.
   template<typename M>
   bool broadcast(M & message, const std::string & topic, const std::set<Connection *> & targets,
         bool block = true)
   {
      message.typeID(lookUpTypeID(topic));
      message.source(_localQueue.nativeID());
      size_t outputSize = message.outputSize();
      return broadcast(message.outputBuffer(), outputSize, targets, block);
   }

   // Wait for data on the given topics from any source to become available.  This will return the
   // Connection and topic of the oldest such message if available, or the first Connection to
   // receive a matching message otherwise.  By default, this call will block until data is
   // available, but a timeout may be specified.  If the call times out, the return value will be
   // { nullptr, "" }.
   std::pair<std::unique_ptr<Connection>, std::string>
   waitForData(const std::set<std::string> & topics,
         std::chrono::milliseconds           timeout = std::chrono::milliseconds(TEN_YEARS_IN_MS));

   // Interrupt all threads currently waiting to receive a message.  This method will cause any
   // caller of the following methods to return immediately.  The return value of each method will
   // be as if a timeout was specified and had expired.
   //  - Broker::waitForData()
   //  - Connection::receive<T>()
   //  - Connection::receiveSerialized<T>()
   //  - Connection::sendAndReceive<T>()
   //  - Connection::sendAndReceiveSerialized<T>()
   //  - Connection::waitForData()
   void interrupt();

  private:
   using MessageDeque  = std::deque<std::unique_ptr<Message<void>>>;
   using MessageList   = std::list<std::unique_ptr<Message<void>>>;
   using IteratorDeque = std::deque<typename MessageList::iterator>;

   struct MessageIndices
   {
      MessageIndices();
      MessageIndices(MessageIndices &&) = delete;
      ~MessageIndices();

      std::condition_variable                cv;
      std::map<MessageTypeID, IteratorDeque> byTypeID;
   };

   struct Cache
   {
      Cache();
      Cache(Cache &&) = delete;
      ~Cache();

      std::mutex                               mutex;
      std::condition_variable                  cv;
      MessageList                              data;
      std::map<MessageQueueID, MessageIndices> bySource;
   };

  private:
   friend class Connection;

   // friend Connection::send();
   MessageTypeID lookUpTypeID(const std::string & topic);

   // friend Connection::receive();
   // friend Connection::receiveSerialized();
   std::unique_ptr<Message<void>>
   pop(MessageQueueID source, const std::string & topic, std::chrono::milliseconds timeout);

   // friend Connection::waitForData();
   std::string waitForData(MessageQueueID source, const std::set<std::string> & topics,
         std::chrono::milliseconds timeout);

   // friend Connection::getMessageSubTopic();
   unsigned long getMessageSubTopic(MessageQueueID source, const std::string & topic);

   std::string             lookUpTopic(MessageTypeID typeID);
   std::set<MessageTypeID> convertTopicsToTypeIDs(const std::set<std::string> & topics);

   bool broadcast(uint8_t * data, size_t size, const std::set<Connection *> & targets, bool block);

   std::unique_ptr<Connection> connectToPeer(const std::string & remoteQueueName);

   static std::string generateQueueName(const std::string & appName, pid_t pid);

   void interruptAllListeners();

   void receiveMessages();

  private:
   bool _initialized              = false;
   bool _shutDown                 = false;
   std::map<Settings, bool> _settings;

   std::string  _localQueueName;
   MessageQueue _localQueue;
   std::thread  _listenerThread;
   SequenceID   _sequence = std::numeric_limits<SequenceID>::min();

   Cache    _cache;
   uint32_t _interrupt;

   MessageDeque            _connectionRequests;
   std::mutex              _connectionMutex;
   std::condition_variable _connectionCV;

   std::mutex                           _topicsMutex;
   std::map<std::string, MessageTypeID> _topicToTypeID;
   std::map<MessageTypeID, std::string> _typeIDToTopic;

   Logger _logger;

   static const MessageTypeID CONNECTION_FROM_CLIENT      = std::numeric_limits<MessageTypeID>::min();
   static const MessageTypeID BROKER_TOUCH_LOCAL_MSGQUEUE = CONNECTION_FROM_CLIENT + 1;
   static const MessageTypeID HASH_MIN                    = BROKER_TOUCH_LOCAL_MSGQUEUE + 1;
};

}   // namespace ipc
}   // namespace vizio
