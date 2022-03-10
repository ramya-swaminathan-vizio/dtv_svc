//
// connection.cpp
// © 2020 Vizio Services, All Rights Reserved
//
// The Connection class is used to tie two message queues together, and provide a comfortable
// send/receive API for communicating between them.  There is no actual connection state, as the
// underlying message queues can push or pop messages from anyone at any time.
//

#pragma once

#include <chrono>
#include <set>
#include <string>
#include <sys/types.h>
#include <vizio-log/logger.h>

#include "broker.h"
#include "internal/ipc.h"
#include "internal/message_void.h"
#include "message.h"
#include "message_queue.h"
#include "serializable_message.h"

namespace vizio
{
namespace ipc
{
class Connection
{
  public:
   Connection(Connection &&) = default;
   ~Connection()             = default;

   // if enabled, when the connection is lost, send function will return false.
   // by default disabled
   void enableKeepAliveMode(bool enabled)
   {
      _keepAlive = enabled;
   }

   // Sends a message on a particular topic to the other side of the connection.  By default,
   // this will block until the message has been pushed into the receiving message queue, but
   // this behavior can be modified to return immediately if the receiving message queue is full.
   // In a properly functioning system, the message queue should never be full.  Returns true if
   // the message was successfully pushed.
   template<typename M>
   bool send(M & message, const std::string & topic, bool block = true)
   {
      TRACE();

      if (_keepAlive) {
         pid_t dst = _remoteQueue.getRecieverPid();
         if (!(dst && endpointExist(dst))) {
            errno = ESRCH;
            return false;
         }
      }

      message.typeID(_broker.lookUpTypeID(topic));
      message.source(_localQueue.nativeID());
      bool result = _remoteQueue.push(message, block);
      if (result) {
         DEBUG("Successfully sent {}blocking message on topic {}: {} --> {}", (block ? "" : "non-"),
               topic, localID(), remoteID());
      } else {
         WARNING("Failed to send {}blocking message on topic {}: {} --> {}", (block ? "" : "non-"),
               topic, localID(), remoteID());
      }
      return result;
   }

   // Receives a message on a particular topic from the other side of the connection.  By
   // default, this will block until a matching message is available, but a timeout may be
   // specified.  Returns a unique_ptr<> to the message if successful, or an empty unique_ptr<>
   // otherwise.
   template<typename T>
   auto receive(const std::string & topic,
         std::chrono::milliseconds  timeout = std::chrono::milliseconds(TEN_YEARS_IN_MS))
   {
      TRACE();

      return receiveAs<Message<T>>(topic, timeout);
   }

   // Receives a serializable message on a particular topic from the other side of the
   // connection.  By default, this will block until a matching message is available, but a
   // timeout may be specified.  Returns a unique_ptr<> to the message if successful, or an empty
   // unique_ptr<> otherwise.
   template<typename T>
   auto receiveSerialized(const std::string & topic,
         std::chrono::milliseconds            timeout = std::chrono::milliseconds(TEN_YEARS_IN_MS))
   {
      TRACE();

      return receiveAs<SerializableMessage<T>>(topic, timeout);
   }

   // Helper function for a send/receive message pair.
   template<typename TReceive, typename TSend>
   auto sendAndReceive(TSend & message, const std::string & sendTopic,
         const std::string & receiveTopic, bool blockSend = true,
         std::chrono::milliseconds receiveTimeout = std::chrono::milliseconds(TEN_YEARS_IN_MS))
   {
      TRACE();

      return sendAndReceiveAs<Message<TReceive>>(
            message, sendTopic, receiveTopic, blockSend, receiveTimeout);
   }

   // Helper function for a send/receive message pair.
   template<typename TReceive, typename TSend>
   auto sendAndReceiveSerialized(TSend & message, const std::string & sendTopic,
         const std::string & receiveTopic, bool blockSend = true,
         std::chrono::milliseconds receiveTimeout = std::chrono::milliseconds(TEN_YEARS_IN_MS))
   {
      TRACE();

      return sendAndReceiveAs<SerializableMessage<TReceive>>(
            message, sendTopic, receiveTopic, blockSend, receiveTimeout);
   }

   // Receives a message on a particular topic from the other side of the connection.
   // By default, this will block until a matching message is available, but a timeout may be
   // specified.  In successful case returns the std::pair of message and true, othewise the
   // std::pair of default-constructed message and false.
   template<typename T>
   auto receiveAs(const std::string & topic,
         std::chrono::milliseconds    timeout = std::chrono::milliseconds(TEN_YEARS_IN_MS))
   {
      TRACE();

      if (auto message = _broker.pop(_remoteQueue.nativeID(), topic, timeout)) {
         return std::make_pair(std::move(message->as<T>()), true);
      }
      return std::make_pair(T(), false);
   }

   // Helper function for a send/receive message pair. TReceive is full message type, e.g.
   // Message<std::string> or SerializableMessage<MyData>
   template<typename TReceive, typename TSend>
   auto sendAndReceiveAs(TSend & message, const std::string & sendTopic,
         const std::string & receiveTopic, bool blockSend = true,
         std::chrono::milliseconds receiveTimeout = std::chrono::milliseconds(TEN_YEARS_IN_MS))
   {
      TRACE();

      if (send(message, sendTopic, blockSend)) {
         return receiveAs<TReceive>(receiveTopic, receiveTimeout);
      }
      return std::make_pair(TReceive(), false);
   }

   // Waits for data to become available on any one of the given topics.  It returns the name of
   // the topic with the oldest message if any messages are pending, or the first topic to
   // receive a message if there are no messages available on any topic.  By default, this will
   // block until at least one topic has data available, but a timeout may be specified.
   std::string waitForData(const std::set<std::string> & topics,
         std::chrono::milliseconds timeout = std::chrono::milliseconds(TEN_YEARS_IN_MS))
   {
      TRACE();

      return _broker.waitForData(_remoteQueue.nativeID(), topics, timeout);
   }

   // Returns the (optionally set) subTopic of the oldest message on the given topic.  This
   // allows the caller to use multiple types in a single topic: the subTopic is set to a user-
   // defined value, and getting that value here allows the caller to call receive() with the
   // appropriate type.  This method should be used in conjunction with waitForData() as it does
   // not block; if no message is immediately available, it returns static_cast<T>(0).
   template<typename T>
   T getMessageSubTopic(const std::string & topic)
   {
      TRACE();

      return static_cast<T>(_broker.getMessageSubTopic(_remoteQueue.nativeID(), topic));
   }

   using EndpointID = MessageQueueID;

   // Return an ID that uniquely identifies the remote end of this connection.  Multiple connections
   // to the same remote target will return the same EndpointID, but different remote targets will
   // all have different EndpointID's.
   EndpointID remoteID() const
   {
      return _remoteQueue.nativeID();
   }

   // Return an ID that uniquely identifies the local end of this connection.  All connections
   // created with the same Broker - or a Broker initialized with an identical appName/pid - will
   // have the same EndpointID.  This ID is equality-comparable against the EndpointID returned by
   // remoteID().
   EndpointID localID() const
   {
      return _localQueue.nativeID();
   }

   // Equality operator.  This considers the originating Broker and the two endpoints in determining
   // equality.
   bool operator==(const Connection & o) const
   {
      return (&_broker == &o._broker) && (_localQueue == o._localQueue)
             && (_remoteQueue == o._remoteQueue);
   }

   // Inequality operator.  This considers the originating Broker and the two endpoints in
   // determining inequality.
   bool operator!=(const Connection & o) const
   {
      return !operator==(o);
   }

  private:
   friend class Broker;
   Connection(Broker & broker, MessageQueue local, MessageQueue remote)
         : _broker(broker), _localQueue(local), _remoteQueue(remote), _logger("IPC"),
           _keepAlive(false)
   {
   }

   MessageQueue & localQueue()
   {
      return _localQueue;
   }
   MessageQueue & remoteQueue()
   {
      return _remoteQueue;
   }

  private:
   Broker &     _broker;
   MessageQueue _localQueue;
   MessageQueue _remoteQueue;
   Logger       _logger;
   bool         _keepAlive;
};

}   // namespace ipc
}   // namespace vizio
