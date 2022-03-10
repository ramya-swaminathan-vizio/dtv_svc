//
// message_void.h
// © 2020 Vizio Services, All Rights Reserved
//
// The Message<void> class is a helper type that represents a serialized message of an unknown
// type that has been pulled from the message queue.  At this point, both the header and the data
// are available, but the data cannot be used until it is either cast as a type (for Message<T>-
// based data) or deserialized (for SerializableMessage<T>-based data).
//

#pragma once

#include <utility>

#include "../message.h"
#include "../serializable_message.h"
#include "_message.h"

namespace vizio
{
namespace ipc
{
template<>
class Message<void> : public _Message
{
  public:
   Message() : _Message(MAX_MESSAGE_SIZE) {}
   Message(Message &&) = default;

   template<typename T>
   T as()
   {
      return T(std::move(_data));
   }

  private:
   friend class MessageQueue;
   uint8_t * inputBuffer()
   {
      return _data.get();
   }
   size_t inputSize() const
   {
      return sizeof(ipc::Header) + MAX_MESSAGE_SIZE;
   }
};

}   // namespace ipc
}   // namespace vizio
