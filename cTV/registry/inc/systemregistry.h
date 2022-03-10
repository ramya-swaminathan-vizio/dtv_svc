#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <serializable_message.h>
#pragma GCC diagnostic pop

#include <string>
namespace ipc = vizio::ipc;

static constexpr char SYSREG_VERSION[] = "1.2";

static constexpr char SYSREG_CMD_ID_API_VERSION[]     = "V";
static constexpr char SYSREG_CMD_ID_AUTH[]            = "?";
static constexpr char SYSREG_CMD_ID_GET[]             = "g";
static constexpr char SYSREG_CMD_ID_UPDATE[]          = "u";
static constexpr char SYSREG_CMD_ID_CREATE[]          = "C";
static constexpr char SYSREG_CMD_ID_ENUMERATE[]       = "e";
static constexpr char SYSREG_CMD_ID_REMOVE[]          = "d";
static constexpr char SYSREG_CMD_ID_SUBSCRIBE[]       = "S";
static constexpr char SYSREG_CMD_ID_UNSUBSCRIBE[]     = "U";
static constexpr char SYSREG_CMD_ID_SUBSCRIBE_EVENT[] = "E";

// Create Request
static constexpr char SYSREG_META_DEFAULT_PERM[]  = "777";
static constexpr char SYSREG_META_DEFAULT_OWNER[] = "others";

enum sysreg_status_t
{
   SYSREG_RESULT_SUCCESS = 0,
   SYSREG_RESULT_INVALID_ARGUMENT,
   SYSREG_RESULT_PERMISSION_DENY,
   SYSREG_RESULT_KEY_NOT_FOUND,
   SYSREG_RESULT_INTERNAL_ERROR,
   SYSREG_RESULT_EXIST
};

enum sysreg_event_t
{
   SYSREG_EVENT_CHANGE = 0,
   SYSREG_EVENT_DELETE
};

enum sysreg_flag_t
{
   SYSREG_FLAG_NONE        = 0,
   SYSREG_FLAG_TMP_STORAGE = (1 << 0)
};

// ***** REQUEST *****
struct SysRegVersionRequest
{
   std::string version;

   SysRegVersionRequest(const std::string & version = "");
   inline ~SysRegVersionRequest() = default;

   void size(ipc::Sizer & s)
   {
      s.size(version);
   }
   void serialize(ipc::Serializer & s)
   {
      s.add(version);
   }
   void deserialize(ipc::Deserializer & d)
   {
      d.extract(version);
   }
};

struct SysRegAuthRequest
{
   std::string username;

   SysRegAuthRequest(const std::string & username = "");
   inline ~SysRegAuthRequest() = default;

   void size(ipc::Sizer & s)
   {
      s.size(username);
   }
   void serialize(ipc::Serializer & s)
   {
      s.add(username);
   }
   void deserialize(ipc::Deserializer & d)
   {
      d.extract(username);
   }
};

struct SysRegGetRequest
{
   std::string key;

   SysRegGetRequest(const std::string & key = "");
   inline ~SysRegGetRequest() = default;

   void size(ipc::Sizer & s)
   {
      s.size(key);
   }

   void serialize(ipc::Serializer & s)
   {
      s.add(key);
   }

   void deserialize(ipc::Deserializer & d)
   {
      d.extract(key);
   }
};

struct SysRegUpdateRequest
{
   std::string key;
   std::string value;

   SysRegUpdateRequest(const std::string & key = "", const std::string & value = "");
   inline ~SysRegUpdateRequest() = default;

   void size(ipc::Sizer & s)
   {
      s.size(key, value);
   }

   void serialize(ipc::Serializer & s)
   {
      s.add(key, value);
   }

   void deserialize(ipc::Deserializer & d)
   {
      d.extract(key, value);
   }
};

struct SysRegCreateRequest
{
   std::string   key;
   std::string   value;
   sysreg_flag_t flags;
   std::string   perm;
   std::string   owner;

   SysRegCreateRequest(const std::string & key = "", const std::string & value = "",
         const sysreg_flag_t & flags = SYSREG_FLAG_NONE,
         const std::string &   perm  = SYSREG_META_DEFAULT_PERM,
         const std::string &   owner = SYSREG_META_DEFAULT_OWNER);
   inline ~SysRegCreateRequest() = default;

   void size(ipc::Sizer & s)
   {
      s.size(key, value, perm, owner, flags);
   }

   void serialize(ipc::Serializer & s)
   {
      s.add(key, value, perm, owner, flags);
   }

   void deserialize(ipc::Deserializer & d)
   {
      d.extract(key, value, perm, owner, flags);
   }
};

struct SysRegSubscribeRequest
{
   std::string key;

   SysRegSubscribeRequest(const std::string & key = "");
   inline ~SysRegSubscribeRequest() = default;

   void size(ipc::Sizer & s)
   {
      s.size(key);
   }

   void serialize(ipc::Serializer & s)
   {
      s.add(key);
   }

   void deserialize(ipc::Deserializer & d)
   {
      d.extract(key);
   }
};
struct SysRegUnsubscribeRequest
{
    std::string key;

    SysRegUnsubscribeRequest(const std::string & key = "");

    inline ~SysRegUnsubscribeRequest() = default;

    void size(vizio::ipc::Sizer & s)
    {
        s.size(key);
    }
    void serialize(vizio::ipc::Serializer & s)
    {
        s.add(key);
    }
    void deserialize(vizio::ipc::Deserializer & d)
    {
        d.extract(key);
    }
};

struct SysRegSubscribeEvent
{
   std::string    key;
   sysreg_event_t reason;

   SysRegSubscribeEvent(const std::string & key = "", sysreg_event_t reason = SYSREG_EVENT_CHANGE);
   inline ~SysRegSubscribeEvent() = default;

   void size(ipc::Sizer & s)
   {
      s.size(key, reason);
   }

   void serialize(ipc::Serializer & s)
   {
      s.add(key, reason);
   }

   void deserialize(ipc::Deserializer & d)
   {
      d.extract(key, reason);
   }
};

struct SysRegEnumerateRequest : SysRegGetRequest
{
   using SysRegGetRequest::SysRegGetRequest;
};
struct SysRegRemoveRequest : SysRegGetRequest
{
   using SysRegGetRequest::SysRegGetRequest;
};

// ****** RESPONSE ******
struct SysRegGetResponse
{
   sysreg_status_t status;
   std::string     value;

   SysRegGetResponse(sysreg_status_t status = SYSREG_RESULT_SUCCESS, const std::string & value = "");
   inline ~SysRegGetResponse() = default;

   void size(ipc::Sizer & s)
   {
      s.size(status, value);
   }
   void serialize(ipc::Serializer & s)
   {
      s.add(status, value);
   }
   void deserialize(ipc::Deserializer & d)
   {
      d.extract(status, value);
   }
};

struct SysRegEnumerateResponse
{
   sysreg_status_t          status;
   std::vector<std::string> value;

   SysRegEnumerateResponse(sysreg_status_t status = SYSREG_RESULT_SUCCESS,
         const std::vector<std::string> &  value  = {});
   inline ~SysRegEnumerateResponse() = default;

   void size(ipc::Sizer & s)
   {
      s.size(status, value);
   }
   void serialize(ipc::Serializer & s)
   {
      s.add(status, value);
   }
   void deserialize(ipc::Deserializer & d)
   {
      d.extract(status, value);
   }
};

struct SysRegStatusResponse
{
   sysreg_status_t status;

   SysRegStatusResponse(sysreg_status_t status = SYSREG_RESULT_SUCCESS);
   inline ~SysRegStatusResponse() = default;

   void size(ipc::Sizer & s)
   {
      s.size(status);
   }
   void serialize(ipc::Serializer & s)
   {
      s.add(status);
   }
   void deserialize(ipc::Deserializer & d)
   {
      d.extract(status);
   }
};

struct SysRegVersionResponse
{
   std::string version;
   bool        isCompatible;

   SysRegVersionResponse(const std::string & version = "", bool isCompatible = false);
   inline ~SysRegVersionResponse() = default;

   void size(ipc::Sizer & s)
   {
      s.size(version, isCompatible);
   }
   void serialize(ipc::Serializer & s)
   {
      s.add(version, isCompatible);
   }
   void deserialize(ipc::Deserializer & d)
   {
      d.extract(version, isCompatible);
   }
};

struct SysRegCreateResponse : SysRegStatusResponse
{
   using SysRegStatusResponse::SysRegStatusResponse;
};
struct SysRegAuthResponse : SysRegStatusResponse
{
   using SysRegStatusResponse::SysRegStatusResponse;
};
struct SysRegUpdateResponse : SysRegStatusResponse
{
   using SysRegStatusResponse::SysRegStatusResponse;
};
struct SysRegRemoveResponse : SysRegStatusResponse
{
   using SysRegStatusResponse::SysRegStatusResponse;
};
struct SysRegSubscribeResponse : SysRegStatusResponse
{
   using SysRegStatusResponse::SysRegStatusResponse;
};
struct SysRegUnsubscribeResponse : SysRegStatusResponse
{
    using SysRegStatusResponse::SysRegStatusResponse;
};


// Fix [chromium-style] warnings
// https://www.chromium.org/developers/coding-style/chromium-style-checker-errors

inline SysRegVersionRequest::SysRegVersionRequest(const std::string & version)
   : version(version) {}

inline SysRegAuthRequest::SysRegAuthRequest(const std::string & username)
   : username(username) {}

inline SysRegGetRequest::SysRegGetRequest(const std::string & key)
   : key(key) {}

inline SysRegUpdateRequest::SysRegUpdateRequest(const std::string & key, const std::string & value)
   : key(key), value(value) {}

inline SysRegCreateRequest::SysRegCreateRequest(
   const std::string & key, const std::string & value,
   const sysreg_flag_t & flags, const std::string &   perm,
   const std::string &   owner)
      : key(key), value(value), flags(flags), perm(perm), owner(owner) {}

inline SysRegSubscribeRequest::SysRegSubscribeRequest(const std::string & key) 
   : key(key) {}

inline SysRegSubscribeEvent::SysRegSubscribeEvent(const std::string & key, sysreg_event_t reason)
   : key(key), reason(reason) {}

inline SysRegGetResponse::SysRegGetResponse(sysreg_status_t status, const std::string & value)
   : status(status), value(value) {}

inline SysRegEnumerateResponse::SysRegEnumerateResponse(
   sysreg_status_t status, const std::vector<std::string> &  value)
      : status(status), value(value) {}

inline SysRegStatusResponse::SysRegStatusResponse(sysreg_status_t status) 
   : status(status) {}

inline SysRegVersionResponse::SysRegVersionResponse(const std::string & version, bool isCompatible)
   : version(version), isCompatible(isCompatible) {}
