#ifndef _VZIPC_MESSAGE_
#define _VZIPC_MESSAGE_ 

#include "broker.h"
#include "connection.h"

namespace ipc = vizio::ipc;

enum class vzIpcReqType : int
{
  HMON_REQ,
  HMON_RESP,
  BTSOFTMIC_REQ,
  BTSOFTMIC_RESP,
  BTAPI_REQ,
  BTAPI_RESP,
  REQ_MAX
};




enum class vzIpcAppType : int
{
    APP_BTSOFTMIC,
    APP_HMON,
    APP_DTV_SVC,
    APP_BTAPI,
    APP_MAX
};


enum class btSoftMicMsgId : int
{
  BTSOFTMIC_INIT,
  BTSOFTMIC_START,
  BTSOFTMIC_STOP,
  BTSOFTMIC_MSG_MAX
};


enum class hMonMsgId : int
{
    HMON_INIT,
    HMON_WIFI_START,
    HMON_WIFI_STOP,
    HMON_IS_OOBE,
    HMON_VIRTUAL_INPUT_SOURCE,
    HMON_NETSTATUS,
    HMON_PINGSTATUS,
    HMON_WIFI_SSID,
    HMON_SCAN_FIND_SSID,
    HMON_GET_CONNECTION_STATUS,
    HMON_MSG_MAX
};

enum class btapiMsgId : int
{
    BTAPI_PROVISIONING,
    BTAPI_START_SCAN,
    BTAPI_STOP_SCAN,
    BTAPI_GET_SCAN_LIST,
    BTAPI_START_STREAM,
    BTAPI_STOP_STREAM,
    BTAPI_PAIR_DEVICE,
    BTAPI_UNPAIR_DEVICE,
    BTAPI_SET_VOLUME,
    BTAPI_GET_VOLUME,
    BTAPI_GET_AUDIO_DEV_CONN_STATE,
    BTAPI_VOLUME_INFO,
    BTAPI_VOLUME_UP,
    BTAPI_VOLUME_DOWN,
    BTAPI_SINK_CONNECTED,
    BTAPI_SINK_DISCONNECTED,
    BTAPI_SINK_STREAM_STARTED,
    BTAPI_SINK_STREAM_STOPPED,
    BTAPI_SEND_TO_SENTRY,
    BTAPI_MSG_MAX
}; 


struct healthMonMsg
{
  vzIpcReqType _vzIpcReqType;
  vzIpcAppType _vzIpcAppType;
  hMonMsgId _hMonMsgId;
  unsigned int _payloadSize;
  std::string  _payload;
  bool _status;
  unsigned int _ReqCount;

  void size(ipc::Sizer & s) {
    s.size(_vzIpcReqType, _vzIpcAppType, _hMonMsgId, _payloadSize, _payload, _status, _ReqCount);
  }
  void serialize(ipc::Serializer & s) {
    s.add(_vzIpcReqType, _vzIpcAppType, _hMonMsgId, _payloadSize);
    if(_payloadSize != 0) {
      s.add(_payload);
    }
    s.add(_status, _ReqCount);
  }
  void deserialize(ipc::Deserializer & d) {
    d.extract(_vzIpcReqType);
    d.extract(_vzIpcAppType);
    d.extract(_hMonMsgId);
    d.extract(_payloadSize);
    if(_payloadSize != 0) {
      d.extract(_payload);
    } else {
       _payload = "";
    }

    d.extract(_status);
    d.extract(_ReqCount);
  }
};



struct btSoftMicMsg
{
  vzIpcReqType _vzIpcReqType;
  vzIpcAppType _vzIpcAppType;
  btSoftMicMsgId _btSoftMicMsgId;
  bool _status;
  unsigned int _ReqCount;
};

struct btapiMsg
{
  vzIpcReqType _vzIpcReqType;
  vzIpcAppType _vzIpcAppType;
  btapiMsgId   _btapiMsgId;
  unsigned int _payloadSize;
  std::string  _payload;
  bool         _status;
  unsigned int _ReqCount;

  void size(ipc::Sizer & s) { 
    s.size(_vzIpcReqType, _vzIpcAppType, _btapiMsgId, _payloadSize, _payload, _status, _ReqCount);
  }
  void serialize(ipc::Serializer & s) { 
    s.add(_vzIpcReqType, _vzIpcAppType, _btapiMsgId, _payloadSize);
    if(_payloadSize != 0) {
      s.add(_payload);
    }
    s.add(_status, _ReqCount);
  }
  void deserialize(ipc::Deserializer & d) {
      d.extract(_vzIpcReqType);
      d.extract(_vzIpcAppType);
      d.extract(_btapiMsgId);
      d.extract(_payloadSize);
      if(_payloadSize != 0) {
        d.extract(_payload);
      } else {
        _payload = "";
      }
      d.extract(_status);
      d.extract(_ReqCount);
  }
};

#endif //_VZIPC_MESSAGE_

