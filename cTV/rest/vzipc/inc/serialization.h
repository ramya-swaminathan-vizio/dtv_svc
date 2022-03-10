//
// serialization.h
// © 2020 Vizio Services, All Rights Reserved
//

#pragma once

#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

namespace vizio
{
namespace ipc
{
// implementation details, which are no supposed to be used by client
namespace detail
{
// note: used STL naming conventions here, because some of these names
// are available in C++17 or later, to make transition to new standard
// easier

template<typename T>
struct remove_cvref
{
   using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

// helper
template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

// trait for supported container types
// https://en.cppreference.com/w/cpp/named_req/Container
template<typename T, typename Enable = void>
struct is_container : std::false_type
{
};

template<typename... Ts>
struct is_container_helper
{
};

template<typename T>
struct is_container<T,
      std::conditional_t<false,
            is_container_helper<typename T::value_type, typename T::size_type, typename T::iterator,
                  typename T::const_iterator, decltype(std::declval<T>().size()),
                  decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>,
            void>   // std::conditional_t<
      > : public std::true_type
{
};

// same as above but for associative containers only
// https://en.cppreference.com/w/cpp/named_req/AssociativeContainer
template<typename T, typename Enable = void>
struct is_mapping_container : std::false_type
{
};

template<typename T>
struct is_mapping_container<T,
      std::conditional_t<false,
            is_container_helper<typename T::key_type, typename T::mapped_type,
                  typename T::value_type, typename T::size_type, typename T::iterator,
                  typename T::const_iterator, decltype(std::declval<T>().size()),
                  decltype(std::declval<T>().begin()), decltype(std::declval<T>().end())>,
            void>   // std::conditional_t<
      > : public std::true_type
{
};

template<typename T>
struct is_bounded_array : std::false_type
{
};

template<typename T, std::size_t N>
struct is_bounded_array<T[N]> : std::true_type
{
};

// helper functions for "C++14 folding expression"
template<typename F, typename T0>
auto accumulate(F && f, T0 && t)
{
   return f(std::forward<T0>(t));
}

template<typename F, typename T0, typename... Ts>
auto accumulate(F && f, T0 && t, Ts &&... ts)
{
   return f(std::forward<T0>(t)) + accumulate(f, std::forward<Ts>(ts)...);
}

template<typename F, typename T0>
void for_each(F && f, T0 && t)
{
   return f(std::forward<T0>(t));
}

template<typename F, typename T0, typename... Ts>
void for_each(F && f, T0 && t, Ts &&... ts)
{
   f(std::forward<T0>(t));
   for_each(f, std::forward<Ts>(ts)...);
}

}   // namespace detail

// Size ////////////////////////////////////////////////////////////////////

// primary template
template<typename T, typename Enable = void>
struct size;

// Partial specialization for arithmetic/enum types
template<typename T>
struct size<T, std::enable_if_t<std::is_arithmetic<T>::value || std::is_enum<T>::value>>
{
   size_t operator()(T) const noexcept
   {
      return sizeof(T);
   }
};

// raw data, call operator expectes pointer to memory location and its size
template<typename T>
struct size<T, std::enable_if_t<std::is_pointer<T>::value>>
{
   size_t operator()(T, const size_t size) const noexcept
   {
      return sizeof(size_t) + size;
   }
};

// std::string
// accept all T:  std::string, std::string&, const std::string, const std::string&
template<typename T>
struct size<T, std::enable_if_t<std::is_same<std::string, detail::remove_cvref_t<T>>::value>>
{
   size_t operator()(const T & s) const noexcept
   {
      return sizeof(size_t) + s.size();
   }
};

// std::vector<T>, std::set<T> or any other non-associative container (and not std::string)
// T can be lvalue, lvalue reference, const lvalue or const lvalue reference
template<typename T>
struct size<T, std::enable_if_t<detail::is_container<detail::remove_cvref_t<T>>::value
                                && !detail::is_mapping_container<detail::remove_cvref_t<T>>::value
                                && !std::is_same<std::string, detail::remove_cvref_t<T>>::value>>
{
   size_t operator()(const T & v) const noexcept
   {
      size_t result = sizeof(size_t);

      // get size of every element separately to support non-POD as well
      size<typename detail::remove_cvref_t<T>::value_type> elementSize;
      for (const auto & e : v) {
         result += elementSize(e);
      }

      return result;
   }
};

// std::map, std::multimap_map or any other associative container
template<typename T>
struct size<T, std::enable_if_t<detail::is_mapping_container<detail::remove_cvref_t<T>>::value>>
{
   size_t operator()(const T & m) const noexcept
   {
      size_t result = sizeof(size_t);

      // get size of every element separately to support non-POD as well
      size<typename detail::remove_cvref_t<T>::key_type>    keySize;
      size<typename detail::remove_cvref_t<T>::mapped_type> valueSize;
      for (const auto & pair : m) {
         result += keySize(pair.first);
         result += valueSize(pair.second);
      }

      return result;
   }
};

// one-dimensional arrays
template<typename T>
struct size<T, std::enable_if_t<detail::is_bounded_array<detail::remove_cvref_t<T>>::value
                                && std::rank<T>::value == 1>>
{
   size_t operator()(const T & a) const noexcept
   {
      size_t result = sizeof(size_t);

      // get size of every element separately to support non-POD as well
      size<typename std::remove_extent<T>::type> elementSize;
      for (size_t i = 0; i < std::extent<T>::value; ++i) {
         result += elementSize(a[i]);
      }

      return result;
   }
};

// portion of code that is not intended to be used by client
namespace detail
{
// helper for variadic size getter
struct GetSize
{
   template<typename T>
   size_t operator()(const T & t) const
   {
      return size<T>()(t);
   }
};

}   // namespace detail

// convenience helper to get sizes of serveral things in one call
template<typename... Ts>
size_t size_of_all(Ts &&... args)
{
   return detail::accumulate(detail::GetSize(), std::forward<Ts>(args)...);
}

// Serialize ////////////////////////////////////////////////////////////////////

// primary template
template<typename T, typename Enable = void>
struct serialize;

// Partial specialization for arithmetic/enum types
template<typename T>
struct serialize<T, std::enable_if_t<std::is_arithmetic<T>::value || std::is_enum<T>::value>>
{
   void operator()(uint8_t *& buffer, T n) const noexcept
   {
      *reinterpret_cast<std::remove_cv_t<T> *>(buffer) = n;
      buffer += sizeof(T);
   }
};

// raw data, call operator expectes pointer to memory location and its size
template<typename T>
struct serialize<T, std::enable_if_t<std::is_pointer<T>::value>>
{
   void operator()(uint8_t *& buffer, T p, const size_t size) const noexcept
   {
      serialize<size_t>()(buffer, size);
      buffer = std::copy(reinterpret_cast<const uint8_t *>(p),
            reinterpret_cast<const uint8_t *>(p) + size, buffer);
   }
};

// std::string
// accept all T:  std::string, std::string&, const std::string, const std::string&
template<typename T>
struct serialize<T, std::enable_if_t<std::is_same<std::string, detail::remove_cvref_t<T>>::value>>
{
   void operator()(uint8_t *& buffer, const T & s) const noexcept
   {
      serialize<const char *>()(buffer, s.data(), s.size());
   }
};

// std::vector<T>, std::set<T> or any other non-associative container (but not std::string)
// T can be lvalue, lvalue reference, const lvalue or const lvalue reference
template<typename T>
struct serialize<T,
      std::enable_if_t<detail::is_container<detail::remove_cvref_t<T>>::value
                       && !detail::is_mapping_container<detail::remove_cvref_t<T>>::value
                       && !std::is_same<std::string, detail::remove_cvref_t<T>>::value>>
{
   void operator()(uint8_t *& buffer, const T & v) const noexcept
   {
      serialize<size_t>()(buffer, v.size());

      serialize<typename detail::remove_cvref_t<T>::value_type> serializeElement;
      for (const auto & e : v) {
         serializeElement(buffer, e);
      }
   }
};

// std::map, std::multimap_map or any other associative container
template<typename T>
struct serialize<T,
      std::enable_if_t<detail::is_mapping_container<detail::remove_cvref_t<T>>::value>>
{
   void operator()(uint8_t *& buffer, const T & m) const noexcept
   {
      serialize<size_t>()(buffer, m.size());

      serialize<typename detail::remove_cvref_t<T>::key_type>    serializeKey;
      serialize<typename detail::remove_cvref_t<T>::mapped_type> serializeValue;

      for (const auto & pair : m) {
         serializeKey(buffer, pair.first);
         serializeValue(buffer, pair.second);
      }
   }
};

// one-dimensional arrays
template<typename T>
struct serialize<T, std::enable_if_t<detail::is_bounded_array<detail::remove_cvref_t<T>>::value
                                     && std::rank<T>::value == 1>>
{
   void operator()(uint8_t *& buffer, const T & a) const noexcept
   {
      size_t size = std::extent<T>::value;
      serialize<size_t>()(buffer, size);

      serialize<typename std::remove_extent<T>::type> serializeElement;
      for (size_t i = 0; i < size; ++i) {
         serializeElement(buffer, a[i]);
      }
   }
};

// portion of code that is not intended to be used by client
namespace detail
{
// helper for variadic size getter
struct Serialize
{
   uint8_t *& buffer;

   template<typename T>
   void operator()(T & t) const
   {
      serialize<T>()(buffer, t);
   }
};

}   // namespace detail

// convenience helper to get sizes of serveral things in one call
template<typename... Ts>
void serialize_all(uint8_t *& buffer, Ts &&... args)
{
   return detail::for_each(detail::Serialize {buffer}, std::forward<Ts>(args)...);
}

// Deserialize ////////////////////////////////////////////////////////////////////

// primary template
template<typename T, typename Enable = void>
struct deserialize;

// Partial specialization for arithmetic/enum types
template<typename T>
struct deserialize<T, std::enable_if_t<std::is_arithmetic<T>::value || std::is_enum<T>::value>>
{
   T operator()(uint8_t *& buffer) const noexcept
   {
      buffer += sizeof(T);
      return *reinterpret_cast<T *>(buffer - sizeof(T));
   }

   void operator()(uint8_t *& buffer, T & n) const noexcept
   {
      n = (*this)(buffer);
   }
};

// raw data, call operator expectes pointer to memory location and its size
template<typename T>
struct deserialize<T, std::enable_if_t<std::is_pointer<T>::value>>
{
   // Use this to peek at the data size when extracting a raw data blob if
   // the required destination buffer size is unknown in advance.
   size_t peekSize(uint8_t *& buffer) const noexcept
   {
      return *reinterpret_cast<size_t *>(buffer);
   }

   void operator()(uint8_t *& buffer, T data) const noexcept
   {
      const size_t size = deserialize<size_t>()(buffer);
      std::copy(buffer, buffer + size, reinterpret_cast<uint8_t *>(data));
      buffer += size;
   }

   void operator()(uint8_t *& buffer, T & data, size_t & size) const noexcept
   {
      size = deserialize<size_t>()(buffer);
      std::copy(buffer, buffer + size, reinterpret_cast<uint8_t *>(data));
      buffer += size;
   }
};

// std::string (T can be std::string, std::string&, const std::string or const std::string&)
template<typename T>
struct deserialize<T, std::enable_if_t<std::is_same<std::string, detail::remove_cvref_t<T>>::value>>
{
   void operator()(uint8_t *& buffer, T & s) const noexcept
   {
      const size_t size = deserialize<size_t>()(buffer);
      s.assign(reinterpret_cast<char *>(buffer), size);
      buffer += size;
   }
};

// separate specialization for std::vector to leverage resize()
template<typename T>
struct deserialize<T, std::enable_if_t<std::is_same<std::vector<typename T::value_type>,
                            detail::remove_cvref_t<T>>::value>>
{
   void operator()(uint8_t *& buffer, T & v) const noexcept
   {
      const size_t size = deserialize<size_t>()(buffer);
      v.resize(size);

      using value_type = typename detail::remove_cvref_t<T>::value_type;
      deserialize<value_type> deserializeElement;

      for (size_t i = 0; i < size; ++i) {
         deserializeElement(buffer, v[i]);
      }
   }
};

// std::set<T> or any other non-mapping container (but not std::string or std::vector)
// T can be lvalue, lvalue reference, const lvalue or const lvalue reference
template<typename T>
struct deserialize<T,
      std::enable_if_t<detail::is_container<detail::remove_cvref_t<T>>::value
                       && !detail::is_mapping_container<detail::remove_cvref_t<T>>::value
                       && !std::is_same<std::string, detail::remove_cvref_t<T>>::value
                       && !std::is_same<std::vector<typename T::value_type>,
                             detail::remove_cvref_t<T>>::value>>
{
   void operator()(uint8_t *& buffer, T & v) const noexcept
   {
      const size_t size = deserialize<size_t>()(buffer);

      using value_type = typename detail::remove_cvref_t<T>::value_type;
      deserialize<value_type> deserializeElement;

      for (size_t i = 0; i < size; ++i) {
         value_type e;   // has to be default-constructible, obviously
         deserializeElement(buffer, e);
         v.emplace(std::move(e));
      }
   }
};

// std::map, std::multimap_map or any other mapping container
template<typename T>
struct deserialize<T,
      std::enable_if_t<detail::is_mapping_container<detail::remove_cvref_t<T>>::value>>
{
   void operator()(uint8_t *& buffer, T & m) const noexcept
   {
      const size_t size = deserialize<size_t>()(buffer);

      using key_type    = typename detail::remove_cvref_t<T>::key_type;
      using mapped_type = typename detail::remove_cvref_t<T>::mapped_type;
      deserialize<key_type>    deserializeKey;
      deserialize<mapped_type> deserializeValue;

      for (size_t i = 0; i < size; ++i) {
         key_type key;
         deserializeKey(buffer, key);

         mapped_type value;
         deserializeValue(buffer, value);

         m.emplace(std::move(key), std::move(value));
      }
   }
};

// one-dimensional arrays
template<typename T>
struct deserialize<T, std::enable_if_t<detail::is_bounded_array<detail::remove_cvref_t<T>>::value
                                       && std::rank<T>::value == 1>>
{
   void operator()(uint8_t *& buffer, T & a) const noexcept
   {
      const size_t size = deserialize<size_t>()(buffer);

      using value_type = typename std::remove_extent<T>::type;
      deserialize<value_type> deserializeElement;

      for (size_t i = 0; i < size; ++i) {
         deserializeElement(buffer, a[i]);
      }
   }
};

// portion of code that is not intended to be used by client
namespace detail
{
// helper for variadic size getter
struct Deserialize
{
   uint8_t *& buffer;

   template<typename T>
   void operator()(T & t) const
   {
      deserialize<T>()(buffer, t);
   }
};

}   // namespace detail

// convenience helper to get sizes of serveral things in one call
template<typename... Ts>
void deserialize_all(uint8_t *& buffer, Ts &&... args)
{
   return detail::for_each(detail::Deserialize {buffer}, std::forward<Ts>(args)...);
}

}   // namespace ipc
}   // namespace vizio
