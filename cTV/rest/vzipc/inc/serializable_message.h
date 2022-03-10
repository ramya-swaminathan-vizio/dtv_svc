//
// serializable_message.h
// © 2020 Vizio Services, All Rights Reserved
//
// The SerializableMessage class is used to send messages that cannot be represented with simple
// structures.  This could be because there are multiple variable-length strings, or because there
// are pointers, or because there are complex types, or even because a developer wants to send
// only a portion of the data in a class.
//
// USING THIS CLASS IS NOT AS EFFICIENT AS USING THE MESSAGE<T> CLASS.  PLEASE USE MESSAGE<T>
// WHENEVER POSSIBLE.
//

#pragma once

#include <map>
#include <memory>
#include <set>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
#include <cstring>

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
// This helper class is used to simplify adding data to the buffer.  It supports all numeric types,
// std::strings, std:vectors, and std::maps of any supported type.  Custom types are supported
// automatically as long as they have the serialize(Serializer &) method.  Example:
//
// void Class::serialize(Serializer & s)
// {
//    s.add(int(42));                        // OK
//    s.add(double(12.34));                  // OK
//    s.add("Hello");                        // ERROR - raw pointers not allowed.
//    s.add(std::string("Hello"));           // OK
//    s.add(std::vector<std::string>());     // OK
//    s.add(std::map<std::string, int>());   // OK
//    s.add(OtherType());                    // OK - if OtherType::serialize(Serializer &) exists
//    s.addRaw(_buffer, _size);              // OK - adds an internal buffer
//
//    a.add(42, 12.34, "Hello", ...);        // OK - short form
// }
//
struct Serializer
{
   Serializer() : buffer(nullptr) {}
   Serializer(uint8_t * buffer) : buffer(buffer) {}

   template<typename T1, typename T2, typename... Ts>
   void add(T1 && t1, T2 && t2, Ts &&... ts)
   {
      add(std::forward<T1>(t1));
      add(std::forward<T2>(t2), std::forward<Ts>(ts)...);
   }

   template<typename T>
   void add(T *)
   {
      static_assert(std::is_pointer<T>::value,
            "\nSerializing raw pointers is not allowed.  "
            "Use either:\n   add(std::string), or\n   addRaw(const void * data, size_t size)");
   }

   template<typename T>
   typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type add(T t)
   {
      memcpy(buffer, &t, sizeof(T));
      buffer += sizeof(T);
   }

   void addRaw(const void * data, size_t size)
   {
      add(size);
      std::copy(reinterpret_cast<const uint8_t *>(data),
            reinterpret_cast<const uint8_t *>(data) + size, buffer);
      buffer += size;
   }

   void add(const std::string & string)
   {
      addRaw(string.data(), string.size());
   }

   template<typename T>
   auto add(T & t) -> decltype(t.serialize(*this))
   {
      t.serialize(*this);
   }

   template<typename T>
   void add(std::vector<T> & v)
   {
      add(v.size());
      for (auto & e : v) {
         add(e);
      }
   }

   template<typename T>
   void add(const std::vector<T> & v)
   {
      add(v.size());
      for (const auto & e : v) {
         add(e);
      }
   }

   template<typename T>
   void add(std::set<T> & s)
   {
      add(s.size());
      for (auto & e : s) {
         add(e);
      }
   }

   template<typename T>
   void add(const std::set<T> & s)
   {
      add(s.size());
      for (const auto & e : s) {
         add(e);
      }
   }

   template<typename K, typename V>
   void add(std::map<K, V> & m)
   {
      add(m.size());
      for (auto & e : m) {
         add(e.first);
         add(e.second);
      }
   }

   template<typename K, typename V>
   void add(const std::map<K, V> & m)
   {
      add(m.size());
      for (const auto & e : m) {
         add(e.first);
         add(e.second);
      }
   }

   uint8_t * buffer;
};

//
// This helper class is used to simplify determining the buffer size needed to serialize the overall
// type.  It supports all the same types that the Serializer supports.  Example:
//
// void Class::size(Sizer & s)
// {
//    s.size(int(42));
//    s.size(std::string("Hello"));
//    s.size(std::map<std::string, int>());
//    s.sizeRaw(_buffer, _size);
//    ...
// }
//
struct Sizer
{
   Sizer() : total(0) {}

   template<typename T1, typename T2, typename... Ts>
   void size(T1 && t1, T2 && t2, Ts &&... ts)
   {
      size(std::forward<T1>(t1));
      size(std::forward<T2>(t2), std::forward<Ts>(ts)...);
   }

   template<typename T>
   void size(T *)
   {
      static_assert(std::is_pointer<T>::value,
            "\nSizing raw pointers is not allowed.  "
            "Use either:\n   size(std::string), or\n   sizeRaw(const void * data, size_t size)");
   }

   template<typename T>
   typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type
   size(const T &)
   {
      total += sizeof(T);
   }

   void sizeRaw(const void *, size_t size)
   {
      Sizer::size(size);
      total += size;
   }

   void size(const std::string & string)
   {
      sizeRaw(string.data(), string.size());
   }

   template<typename T>
   auto size(T & t) -> decltype(t.size(*this))
   {
      t.size(*this);
   }

   template<typename T>
   void size(std::vector<T> & v)
   {
      size(v.size());
      for (auto & e : v) {
         size(e);
      }
   }

   template<typename T>
   void size(const std::vector<T> & v)
   {
      size(v.size());
      for (const auto & e : v) {
         size(e);
      }
   }

   template<typename T>
   void size(std::set<T> & s)
   {
      size(s.size());
      for (auto & e : s) {
         size(e);
      }
   }

   template<typename T>
   void size(const std::set<T> & s)
   {
      size(s.size());
      for (const auto & e : s) {
         size(e);
      }
   }

   template<typename K, typename V>
   void size(std::map<K, V> & m)
   {
      size(m.size());
      for (auto & e : m) {
         size(e.first);
         size(e.second);
      }
   }

   template<typename K, typename V>
   void size(const std::map<K, V> & m)
   {
      size(m.size());
      for (const auto & e : m) {
         size(e.first);
         size(e.second);
      }
   }

   size_t total;
};

//
// This helper class is used to simplify extracting data from the buffer.  It supports all the same
// types that Serializer supports.
//
// void Class::deserialize(Deserializer & d)
// {
//    int i;
//    std::string s;
//    std::vector<double> v;
//
//    d.extract(i);
//    d.extract(s);
//    d.extract(v);
//
//    // Assigns `cstring` and `cstring_size` to point to the address and size of the raw data.
//    char * cstring;
//    size_t cstring_size;
//    d.extractRaw(cstring, cstring_size);
//
//    // Copies the raw data into `fixedString`
//    char fixedString[10];
//    d.extractRaw(fixedString);
// }
//
struct Deserializer
{
   Deserializer() : buffer(nullptr), totalSize(0) {}
   Deserializer(uint8_t * buffer, size_t totalSize) : buffer(buffer), totalSize(totalSize) {}

   template<typename T1, typename T2, typename... Ts>
   void extract(T1 && t1, T2 && t2, Ts &&... ts)
   {
      extract(std::forward<T1>(t1));
      extract(std::forward<T2>(t2), std::forward<Ts>(ts)...);
   }

   template<typename T>
   void extract(T *)
   {
      static_assert(std::is_pointer<T>::value,
            "\nExtracting raw pointers is not allowed.  "
            "Use either:\n   extract(std::string), or\n   extractRaw(T *& data, size_t & size)");
   }

   template<typename T>
   typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value, T>::type
   extract()
   {
      T value;
      memcpy(&value, buffer, sizeof(T));
      buffer += sizeof(T);

      return value;
   }

   template<typename T>
   typename std::enable_if<std::is_arithmetic<T>::value || std::is_enum<T>::value>::type
   extract(T & t)
   {
      memcpy(&t, buffer, sizeof(T));
      buffer += sizeof(T);
   }

   // Use this to peek at the data size when extracting a raw data blob if the required destination
   // buffer size is unknown in advance.
   size_t peekRawSize()
   {
      return *reinterpret_cast<size_t *>(buffer);
   }

   // Copies data - prefer the `extractRaw(T *& data, size_t & size)` form if possible.
   template<typename T>
   typename std::enable_if<
         std::is_void<T>::value
         || std::is_same<signed char, typename std::make_signed<T>::type>::value>::type
   extractRaw(T * data)
   {
      size_t size = extract<size_t>();
      std::copy(buffer, buffer + size, reinterpret_cast<char *>(data));
      buffer += size;
   }

   template<typename T>
   typename std::enable_if<
         std::is_void<T>::value
         || std::is_same<signed char, typename std::make_signed<T>::type>::value>::type
   extractRaw(T *& data, size_t & size)
   {
      size = extract<size_t>();
      data = reinterpret_cast<T *>(buffer);
      buffer += size;
   }

   void extract(std::string & string)
   {
      size_t size = extract<size_t>();
      string.assign(reinterpret_cast<char *>(buffer), size);
      buffer += size;
   }

   template<typename T>
   auto extract(T & t) -> decltype(t.deserialize(*this))
   {
      t.deserialize(*this);
   }

   template<typename T>
   void extract(std::vector<T> & v)
   {
      v.resize(extract<typename std::vector<T>::size_type>());
      for (size_t i = 0; i < v.size(); i++) {
         extract(v[i]);
      }
   }

   template<typename T>
   void extract(std::set<T> & s)
   {
      size_t size = extract<typename std::set<T>::size_type>();
      s.clear();
      for (size_t i = 0; i < size; i++) {
         T t;
         extract(t);
         s.emplace(std::move(t));
      }
   }

   template<typename K, typename V>
   void extract(std::map<K, V> & m)
   {
      size_t size = extract<typename std::map<K, V>::size_type>();
      m.clear();
      for (size_t i = 0; i < size; i++) {
         K k;
         extract(k);
         V v;
         extract(v);
         m.emplace(std::move(k), std::move(v));
      }
   }

   uint8_t * buffer;
   size_t    totalSize;
};

//
// Any type may be used for T, so long as it meets the following qualifications:
//
//    1. It is default-constructible.
//
//    2. It implements the following three functions:
//       struct T
//       {
//          // Generates the total size of the serialized data.  This method is called BEFORE
//          // actually serializing the data so that a buffer of the proper size can be allocated
//          // with the necessary headers needed by the messaging layer.
//          void size(Sizer & s);
//
//          // Serialize the object using the given Serializer helper class.  The buffer referenced
//          // by the Serializer object will be at least as large as the value provided by
//          // size(Sizer &), which will be called BEFORE this function.  Note that serialization
//          // can be nested.
//          void serialize(Serializer & s);
//
//          // Deserialize the object from a serialized buffer using the given Deserializer class.
//          // The deserialization happens in the same order as serialization.
//          void deserialize(Deserializer & d);
//       };
//
template<typename T>
class SerializableMessage : public _Message
{
  public:
   template<typename... Args>
   SerializableMessage(Args &&... args) : _Message(0), _t(std::forward<Args>(args)...), _size(0)
   {
   }

   SerializableMessage(SerializableMessage &&) = default;

   T & operator*()
   {
      return _t;
   }
   const T & operator*() const
   {
      return _t;
   }

   T * operator->()
   {
      return &_t;
   }
   const T * operator->() const
   {
      return &_t;
   }

   bool operator==(const SerializableMessage<T> & o)
   {
      return **this == *o;
   }

  private:
   friend class MessageQueue;
   friend class Broker;

   uint8_t * outputBuffer()
   {
      initialize(_size, header()->typeID, header()->source, header()->subTopic);
      Serializer s {data()};
      s.add(_t);
      return _data.get();
   }

   size_t outputSize()
   {
      Sizer s;
      s.size(_t);
      _size = s.total;
      return sizeof(ipc::Header) + ((_size > MAX_MESSAGE_SIZE) ? sizeof(int) : _size);
   }

   friend class Message<void>;
   SerializableMessage(std::unique_ptr<uint8_t[]> && serializedData)
         : _Message(std::move(serializedData)), _size(0)
   {
      Deserializer d {data(), header()->size};
      d.extract(_t);
   }

  private:
   T      _t;
   size_t _size;
};

}   // namespace ipc
}   // namespace vizio
