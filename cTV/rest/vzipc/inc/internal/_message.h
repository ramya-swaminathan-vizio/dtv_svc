//
// _message.h
// © 2020 Vizio Services, All Rights Reserved
//
// The _Message class is the base class for several message types, including Message<T> and
// SerializableMessage<T>.  _Message is not a template type - the goal here is to reduce the
// generated code size by pulling functionality that does not need to know about the end templated
// type into common functions that can be reused.
//

#pragma once

#include <memory>

#include "ipc.h"

namespace vizio
{
namespace ipc
{
class _Message
{
  public:
   static const size_t MAX_MESSAGE_SIZE = 1024 - sizeof(ipc::Header);

  public:
   ~_Message();

   void typeID(MessageTypeID typeID)
   {
      header()->typeID = typeID;
   }
   MessageTypeID typeID() const
   {
      return header()->typeID;
   }

   void source(MessageQueueID source)
   {
      header()->source = source;
   }
   MessageQueueID source() const
   {
      return header()->source;
   }

   void sequence(SequenceID sequence)
   {
      header()->sequence = sequence;
   }
   SequenceID sequence() const
   {
      return header()->sequence;
   }

   template<typename T>
   void subTopic(T subTopic)
   {
      header()->subTopic = static_cast<unsigned long>(subTopic);
   }
   template<typename T>
   T subTopic() const
   {
      return static_cast<T>(header()->subTopic);
   }

  protected:
   _Message(size_t size);
   _Message(_Message && o);
   _Message(std::unique_ptr<uint8_t[]> && serializedData);

   _Message & operator=(_Message && o);

   void initialize(size_t size, MessageTypeID typeID = 0, MessageQueueID source = 0,
         unsigned long subTopic = 0);

   ipc::Header * header() const
   {
      return reinterpret_cast<ipc::Header *>(_data.get());
   }

   uint8_t * data() const
   {
      return (_shared ? _shared : _data.get() + sizeof(ipc::Header));
   }

  protected:
   std::unique_ptr<uint8_t[]> _data;
   uint8_t *                  _shared;
};

}   // namespace ipc
}   // namespace vizio
