//
// message_queue.h
// © 2020 Vizio Services, All Rights Reserved
//
// This header file documents part of the interface that applications can use to send and receive
// messages and events.  This is done through a pub/sub mechanism where interested parties send and
// receive messages over particular named channels called 'topics'.
//
// The system needs and realities that drove this design are as follows:
//    1.  There are a relatively small number of applications that need local communication.
//    2.  Messages need to be low-latency.
//    3.  Broadcast messages are rare, and more generally, the connectivity model is USUALLY hub-
//        and-spoke (with the Application Controller, the Platform Orchestrator, and the Key
//        Manager components acting collectively as the hub).
//    4.  Message sizes are usually relatively small and usually messages can be made fixed types.
//
// The XSI Message Queue primitives were chosen as the IPC mechanism that meets all the needs of
// the system.  If anyone at some point would like to benchmark the efficiency of these queues and
// compare them with POSIX message queues, it would be interesting to see the data.  However, any
// performance differences are likely to be negligible.  Similarly, it would be an interesting
// experiment to see this implemented with Unix domain sockets, but given the current protocol
// and the lack of sub-topics in Unix sockets, either sub-topic logic would need to be implemented
// or there there would be 3X as many sockets as there are message queues (the AC, PO, and KM
// components would all need their own socket).  Regardless, there are some key advantages to using
// XSI Message Queues:
//    1.  Unlike POSIX Message Queues, which sort messages according to priority and then always
//        pull the highest message, XSI Message Queues let you pull a message with a specific
//        priority / type ID.  This allows the concept of "sub-topics" within the queue, which in
//        turn allows you to use just a single message queue for each application.
//    2.  Unlike sockets, it is very easy to limit the amount of total data retained in memory
//        - even temporarily - by IPC events and messages.
//    3.  Unlike sockets, Message Queues retain their data even if one of the processes involved
//        crashes.  This means in theory the process could be restarted and continue responding to
//        data previously sent to it before the crash.
//
// Platform applications should generally not use this API directly.  Rather, the Message Queue
// class is used as a building block for the Broker and Connection classes.
//
// ADDENDUM:
// The system design has changed somewhat to address pitfalls that could occur as a result of using
// a different type ID at the MessageQueue level and managing the assignment of these ID's via the
// Broker class.  Now, the messages include a header that describes the sender of the message as
// well as the message topic.  This allows (or forces, depending on your persepctive) the Broker to
// extract all messages from the queue as soon as they arrive and cache them locally.  This provides
// some benefits in exchange for some tradeoffs.  As a result, only a single global type ID is used
// for all messages.
//

#pragma once

#include <memory>
#include <string>

#include "internal/ipc.h"

namespace vizio
{
namespace ipc
{
// clang-format off
template<typename T> class Message;
template<>           class Message<void>;
// clang-format on

class MessageQueue
{
  public:
   MessageQueue();
   MessageQueue(const MessageQueue &) = default;

   bool initialize(const std::string & queueName);

   template<typename M>
   bool push(M & message, bool block = false)
   {
      size_t    outputSize   = message.outputSize() - sizeof(long);
      uint8_t * outputBuffer = message.outputBuffer();
      return push_internal(std::move(outputBuffer), outputSize, block);
   }

   bool push(uint8_t * data, size_t size, bool block = false)
   {
      return push_internal(data, size - sizeof(long), block);
   }

   std::unique_ptr<Message<void>> pop(bool block = true);

   bool operator==(const MessageQueue & o) const
   {
      return _id == o._id;
   }

   MessageQueueID nativeID() const
   {
      return _id;
   }

   // These methods attempt to remove the shared data structure in the kernel, eliminating all
   // currently queued messages and preventing new ones from being added (until the queue is
   // initialized again).
   bool destroy();

   static bool destroy(const std::string & queueName);

   pid_t getRecieverPid() const;

  private:
   bool push_internal(uint8_t * data, size_t size, bool block);

   friend class ApplicationController;
   bool setBufferSize(size_t size);

   friend class Broker;
   MessageQueue(MessageQueueID id);

  private:
   MessageQueueID _id;
};

}   // namespace ipc
}   // namespace vizio
