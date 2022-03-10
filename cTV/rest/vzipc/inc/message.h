//
// message.h
// © 2020 Vizio Services, All Rights Reserved
//
// The Message class is an efficient way to send messages of any size that can be represented in
// memory as a single, fixed-size unit.  This includes all the numeric types and fixed-size
// character arrays, as well as structures that contain any number of these.
//
// A specializtion of the Message<T> class is provided for std::string, and the
// SerializableMessage<T> is also available for more complex scenarios.  However, both
// Message<std::string> and SerializableMessage<T> are less efficient than Message<T> due to their
// need to make additional allocations and copies of the data before sending.
//
// USING MESSAGE<T> IS THE PREFERRED WAY TO ENCAPSULATE DATA.  PLEASE USE MESSAGE<T> OVER
// MESSAGE<std::string> AND SERIALIZABLEMESSAGE<T> WHENEVER POSSIBLE.
//
// Often this can be made possible simply by using a fixed-length character string rather than a
// "const char *" or a std::string.
//

#pragma once

#include <memory>
#include <string>
#include <utility>

#include "internal/_message.h"
#include "internal/ipc.h"

namespace vizio
{
namespace ipc
{
// clang-format off
template<typename T> class Message;
template<>           class Message<void>;
// clang-format on

//
// Any type may be used for T, so long as it meets the following qualifications:
//
//    1.  It is default- and trivially-constructible.
//    2.  All data associated with the object is located in a contiguous block, starting at the
//        address given by &T and extending for sizeof(T) bytes.
//    3.  T does not contain absolute pointers.
//
template<typename T>
class Message : public _Message
{
  public:
   template<typename... Args>
   Message(Args &&... args) : _Message(sizeof(T))
   {
      new (operator->()) T(std::forward<Args>(args)...);
   }
   Message(Message && o) = default;

   Message<T> & operator=(Message<T> && o) = default;

   T & operator*()
   {
      return *reinterpret_cast<T *>(data());
   }
   const T & operator*() const
   {
      return *reinterpret_cast<T *>(data());
   }

   T * operator->()
   {
      return reinterpret_cast<T *>(data());
   }
   const T * operator->() const
   {
      return reinterpret_cast<T *>(data());
   }

   bool operator==(const Message<T> & o) const
   {
      return **this == *o;
   }

  private:
   friend class MessageQueue;
   friend class Broker;
   uint8_t * outputBuffer() const
   {
      return _data.get();
   }
   size_t outputSize() const
   {
      return sizeof(ipc::Header) + (_shared ? sizeof(int) : sizeof(T));
   }

   friend class Message<void>;
   Message(std::unique_ptr<uint8_t[]> && serializedData) : _Message(std::move(serializedData)) {}
};

//
// The most efficient use of the Message<std::string> type is to either construct the string
// directly in the Message() constructor or to std::move() in an existing string.  Example:
//
//    Message<std::string> m1("Hello world");      // Better
//
//    std::string s1("Hello world");
//    Message<std::string> m2(std::move(s1));      // OK
//
//    std::string s2("Hello world");
//    Message<std::string> m3(s2);                 // Avoid
//    -or-
//    Message<std::string> m3;
//    *m3 = s2;                                    // Avoid
//
// Please consider using a fixed-length string whenever possible for efficiency:
//
//    Message<char [MESSAGE_LENGTH_MAX]> m4;
//    memcpy(**m4, "Hello world", 12);             // Most efficient
//
template<>
class Message<std::string> : public _Message
{
  public:
   template<typename... Args>
   Message(Args &&... args) : _Message(0), _string(std::forward<Args>(args)...)
   {
   }
   Message(Message &&) = default;

   std::string & operator*()
   {
      return _string;
   }
   const std::string & operator*() const
   {
      return _string;
   }

   std::string * operator->()
   {
      return &_string;
   }
   const std::string * operator->() const
   {
      return &_string;
   }

   bool operator==(const Message<std::string> & o) const
   {
      return _string == o._string;
   }

  private:
   friend class MessageQueue;
   friend class Broker;
   uint8_t * outputBuffer();
   size_t    outputSize() const;

   friend class Message<void>;
   Message(std::unique_ptr<uint8_t[]> && serializedData);

  private:
   std::string _string;
};

}   // namespace ipc
}   // namespace vizio
