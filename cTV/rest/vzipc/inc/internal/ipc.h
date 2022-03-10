//
// ipc.h
// © 2020 Vizio Services, All Rights Reserved
//

#pragma once

#include <limits>
#include <string>
#include <type_traits>
#include <signal.h>
#include <errno.h>

namespace vizio
{
namespace ipc
{
using MessageTypeID  = long;
using MessageQueueID = int;
using SequenceID     = unsigned int;

struct Header
{
   MessageTypeID  mtype;
   MessageTypeID  typeID;
   unsigned long  subTopic;
   MessageQueueID source;
   SequenceID     sequence;
   size_t         size;
} __attribute__((__packed__));

template<typename T>
T hash(const std::string & string, T min = std::numeric_limits<T>::min())
{
   T hash = static_cast<T>(string.size());
   for (char c : string) {
      hash = hash * 37 + c;
      hash += (hash >> 5);
   }
   if (hash < min && min != std::numeric_limits<T>::min()) {
      using U = typename std::make_unsigned<T>::type;

      U shifted = static_cast<U>(hash - std::numeric_limits<T>::min());
      U divisor = static_cast<U>(std::numeric_limits<T>::max() - min + 1);

      hash = static_cast<T>(shifted % divisor) + min;
   }
   return hash;
}

inline bool endpointExist(pid_t pid)
{
   int result = kill(pid, 0);
   return (result >= 0 || (result < 0 && errno == EPERM));
}

}   // namespace ipc
}   // namespace vizio
