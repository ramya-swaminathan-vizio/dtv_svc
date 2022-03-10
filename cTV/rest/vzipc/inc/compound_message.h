//
// compound_message.h
// © 2020 Vizio Services, All Rights Reserved
//
// The CompoundMessage class is used to send messages that contain more than one
// field of supported types. It is different from SerializableMessage in the way
// you don't need to write boilerplate code for every tuple of types.
// For example this:
//   CompoundMessage<int, double, std::string> message;
// Is equivalent to:
//   1. Creating struct with int, double and std::string fields
//   2. Writing size(), serialize(), deserialize() methods for the struct
//   3. Declaring SerializableMessage<MyStruct> message;
// Please note that CompoundMessage supports only types accepted by Sizer,
// Serializer and Deserializer classes (see serializable_message.h)
//
// USING THIS CLASS IS NOT AS EFFICIENT AS USING THE MESSAGE<T> CLASS. PLEASE
// USE MESSAGE<T> WHENEVER POSSIBLE.
//

#pragma once

#include "serializable_message.h"
#include "serialization.h"

namespace vizio
{
namespace ipc
{
// Namespace with implementation details that should not be used by the client
// directly
namespace detail
{
// The utility functions for_each() defined below allow us to call provided
// callbable object with every element of the tuple. This behavior is similar
// to boost::fusion::for_each().
// First, the two function for const tuples are defined, they are used in cases
// where tuple is read-only (const). The second set of functions is used in
// cases where callable has to modify the elements of the tuple.

// "Terminating" function used when index I is equal to the size of the tuple to
// stop the recursion.
template<std::size_t I = 0, typename F, typename... Tp>
inline std::enable_if_t<I == sizeof...(Tp)> for_each(const std::tuple<Tp...> &, F)
{
}

// This function is used for all of the tuple elements. It invokes the callable
// passing the current element of the tuple and recursively calls itself passing
// the incremented index of the element.
template<std::size_t I = 0, typename F, typename... Tp>
      inline std::enable_if_t < I<sizeof...(Tp)> for_each(const std::tuple<Tp...> & t, F f)
{
   f(std::get<I>(t));
   for_each<I + 1, F, Tp...>(t, f);
}

// Same as above but for mutable tuple
template<std::size_t I = 0, typename F, typename... Tp>
inline std::enable_if_t<I == sizeof...(Tp)> for_each(std::tuple<Tp...> &, F)
{
}

// Same as above but for mutable tuple
template<std::size_t I = 0, typename F, typename... Tp>
      inline std::enable_if_t < I<sizeof...(Tp)> for_each(std::tuple<Tp...> & t, F f)
{
   f(std::get<I>(t));
   for_each<I + 1, F, Tp...>(t, f);
}

// Same as above but for accumulating results of the applied function
template<typename R, std::size_t I = 0, typename F, typename... Tp>
inline std::enable_if_t<I == sizeof...(Tp), R> sum(const std::tuple<Tp...> &, F)
{
   return R();
}

// This function is used for all of the tuple elements. It invokes the callable
// passing the current element of the tuple and recursively calls itself passing
// the incremented index of the element.
template<typename R, std::size_t I = 0, typename F, typename... Tp>
      inline std::enable_if_t < I<sizeof...(Tp), R> sum(const std::tuple<Tp...> & t, F f)
{
   return f(std::get<I>(t)) + sum<R, I + 1, F, Tp...>(t, f);
}

}   // namespace detail

//
// Any types that are supported by Sizer/Serializer/Deserializer (see
// serializable_message.h) may be used for Ts. For example, all arithmetic
// types (int, double, etc.), enumeration, std::string, std::vector, std::set,
// std::map.
//
template<typename... Ts>
class CompoundMessage : public _Message
{
  public:
   using value_type = std::tuple<Ts...>;

  public:
   CompoundMessage() : _Message(0) {}
   CompoundMessage(Ts &&... args) : _Message(0), _elements(std::forward<Ts>(args)...) {}

   CompoundMessage(CompoundMessage &&) = default;

   CompoundMessage & operator=(const CompoundMessage &) = default;
   CompoundMessage & operator=(CompoundMessage &&) = default;

   template<int Index, typename T>
   void set(T && value)
   {
      std::get<Index>(_elements) = std::forward<T>(value);
   }

   template<int Index>
   auto get()
   {
      return std::get<Index>(_elements);
   }

   value_type & operator*()
   {
      return _elements;
   }
   const value_type & operator*() const
   {
      return _elements;
   }

   value_type * operator->()
   {
      return &_elements;
   }
   const value_type * operator->() const
   {
      return &_elements;
   }

   bool operator==(const CompoundMessage<Ts...> & o)
   {
      return **this == *o;
   }

  private:
   friend class Broker;
   friend class MessageQueue;
   friend class Message<void>;

   uint8_t * outputBuffer()
   {
      initialize(dataSize(), header()->typeID, header()->source, header()->subTopic);
      uint8_t * buffer = data();
      detail::for_each(_elements, detail::Serialize {buffer});
      return _data.get();
   }

   size_t outputSize() const
   {
      const size_t size = dataSize();
      return sizeof(ipc::Header) + ((size > MAX_MESSAGE_SIZE) ? sizeof(int) : size);
   }

   size_t dataSize() const
   {
      return detail::sum<size_t>(_elements, detail::GetSize());
   }

   CompoundMessage(std::unique_ptr<uint8_t[]> && serializedData)
         : _Message(std::move(serializedData))
   {
      uint8_t * buffer = data();
      detail::for_each(_elements, detail::Deserialize {buffer});
   }

  private:
   value_type _elements;
};

}   // namespace ipc
}   // namespace vizio
