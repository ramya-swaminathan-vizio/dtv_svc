#include "vzIpcServer.h"
#include "broker.h"
#include "connection.h"
#include "log.h"
#include "vzIpcMessage.h"
#include <iostream>
#include <mutex>
#include <unistd.h>

extern "C"
{
#include "app_util/a_network.h"
#include "c_os.h"
#include "vol_ctrl.h"
#include "u_common.h"
#include "wizard_anim/wzd.h"
#include <stdio.h>
#include <string.h>
#include "menu2/menu_vizio/menu_page_bt_devices.h"
#include "rest/rest_network.h"
#include <cJSON.h>

  extern INT32 a_cfg_get_wzd_status(UINT16 *pui2_status);
  extern INT32 a_nw_wlan_drv_start(VOID);
  extern INT32 a_nw_wlan_drv_stop(VOID);
  extern BOOL a_wzd_is_oobe_mode(VOID);
  extern INT32 a_tv_get_focus_win(TV_WIN_ID_T *pe_focus_id);
  extern INT32 a_nw_wlan_status(NW_WLAN_STATE_T *pe_wlan_state);
  extern BOOL  a_nw_is_ethernet_plugin(VOID);
  UINT32 BT_MAX_SCAN_TIME_SEC = 20;
  UINT32 BT_MAX_PAIR_TIME_SEC = 20;
  UINT32 BT_MAX_CONN_TIME_SEC = 20;
  extern INT32  a_nw_is_network_connected(BOOL* pb_is_connected);
  extern REST_DATA_WIFI_APS_T t_g_ap_list;
}

static std::mutex g_VZMutex;
static std::thread::id g_ActiveHmonThrdId;
static std::thread::id g_ActiveBTSoftMicThrdId;
static std::thread::id g_ActiveBTAudioThrdId;

extern volatile int g_run;

static HANDLE_T h_BTSOFTMIC_queue = NULL_HANDLE;
static HANDLE_T h_BTAUDIO_req_queue = NULL_HANDLE;
static HANDLE_T h_BTAUDIO_resp_queue = NULL_HANDLE;

typedef struct btaudioMsg
{
  tBtAudio type;
  size_t msg_len;
  char *msg;
} t_btaudioMsg;

static UINT32 ui4_time = 5000; // 5sec

bool handleHealthmonRequests(
    std::unique_ptr<ipc::SerializableMessage<healthMonMsg>> &message);
void printHMONMsg(std::unique_ptr<ipc::SerializableMessage<healthMonMsg>> &message);
void printBtMsg(ipc::SerializableMessage<btapiMsg> &message);

/* DTV_SVC as Server */
void vz_ipc_task_thread(void *pv_arg)
{
  vzlog::Log::log(vzlog::Log::LEVEL_ERROR, "VZIPC", "enter vz_ipc_task_thread\n");
  ipc::Broker &broker = ipc::Broker::getDefaultServerBroker();
  std::cout << "program_invocation_short_name: "
            << program_invocation_short_name << std::endl;

  int tConnections = 1;

  while (g_run)
  {
    auto connection = broker.acceptClientConnection();

    if (connection == nullptr)
    {
      std::cout << "Failed to accept new connection" << std::endl;
      continue;
    }
    else
    {
      std::cout << "Accepted new connection :# " << tConnections << std::endl;
    }

    std::thread threadHandler(
        [tConnections](ipc::Connection connection) {
          std::thread::id currentThrdId = std::this_thread::get_id();
          std::cout << "Created connection: " << tConnections
                    << " ,currentThrdId: " << currentThrdId << std::endl;

          while (g_run)
          {
            std::string verifyData =
                connection.waitForData({"HEALTHMON", "BTSOFTMIC", "BTAUDIO"},
                                       std::chrono::milliseconds(5000));
            if (verifyData == "HEALTHMON")
            {
              auto result = connection.receiveSerialized<healthMonMsg>( "HEALTHMON", std::chrono::milliseconds(5000));
              if(result.second == true)
              {
                std::cout << "Received Data from client [HEALTHMON]....." << std::endl;
                auto recvHMONReq = std::make_unique<ipc::SerializableMessage<healthMonMsg>> (*result.first);

                if ((*recvHMONReq)->_hMonMsgId == hMonMsgId::HMON_INIT)
                {
                  std::lock_guard<std::mutex> lock(g_VZMutex);
                  g_ActiveHmonThrdId = currentThrdId;
                }

                handleHealthmonRequests(recvHMONReq);
                std::cout << "Sending Response to client [HEALTHMON], Status: " << (*recvHMONReq)->_status << std::endl;
                connection.send(*recvHMONReq, "HEALTHMON");
              }
            }
            else if (verifyData == "BTSOFTMIC")
            {
              auto result = connection.receive<btSoftMicMsg>( "BTSOFTMIC", std::chrono::milliseconds(5000));
              if(result.second == true)
              {
                std::cout << "Received Data from client [BTSOFTMIC]....." << std::endl;
                auto message = std::make_unique<ipc::Message<btSoftMicMsg>> (*result.first);

                if ((*message)->_btSoftMicMsgId ==
                    btSoftMicMsgId::BTSOFTMIC_INIT)
                {
                  std::cout << "Received BTSOFTMIC_INIT....." << std::endl;
                  std::lock_guard<std::mutex> lock(g_VZMutex);
                  g_ActiveBTSoftMicThrdId = currentThrdId;
                }

                /* After accepting client BTSOFTMIC_INIT, Create the Q.  */

                if (NULL_HANDLE == h_BTSOFTMIC_queue)
                {
                  if (c_msg_q_create(&h_BTSOFTMIC_queue, "btsoftmic_q",
                                     sizeof(int), 64) != OSR_OK)
                  {
                    h_BTSOFTMIC_queue = NULL_HANDLE;
                    std::cout << "ERR: create BTSOFTMIC queue fail\n";
                    return;
                  }
                }

                int t_msg = 0;
                SIZE_T z_size = sizeof(t_msg);
                UINT16 ui2_index = 0;
                int ReqCount = 0;

                while (g_run)
                {
                  if (OSR_OK == c_msg_q_receive_timeout(
                                    &ui2_index, (VOID *)&t_msg, &z_size,
                                    &h_BTSOFTMIC_queue, 1, ui4_time))
                  {
                    btSoftMicMsg lbtSoftMicMsg;
                    lbtSoftMicMsg._vzIpcReqType = vzIpcReqType::BTSOFTMIC_REQ;
                    lbtSoftMicMsg._vzIpcAppType = vzIpcAppType::APP_DTV_SVC;
                    if (t_msg == SOFTMIC_START)
                      lbtSoftMicMsg._btSoftMicMsgId =
                          btSoftMicMsgId::BTSOFTMIC_START;
                    else
                      lbtSoftMicMsg._btSoftMicMsgId =
                          btSoftMicMsgId::BTSOFTMIC_STOP;
                    lbtSoftMicMsg._status = true;
                    lbtSoftMicMsg._ReqCount = ReqCount++;

                    ipc::Message<btSoftMicMsg> message(std::move(lbtSoftMicMsg));

                    std::cout
                        << "Sending Request to Client MsgId:"
                        << static_cast<int>(lbtSoftMicMsg._btSoftMicMsgId);
                    std::cout << "---------------------------------------------"
                                 "-----------------"
                              << std::endl;
                    connection.send(message, "BTSOFTMIC", false);
                  }

                  {
                    std::lock_guard<std::mutex> lock(g_VZMutex);
                    if (g_ActiveBTSoftMicThrdId != currentThrdId)
                    {
                      std::cout
                          << "Closing BTSoftMic connection: " << tConnections
                          << " ,currentThrdId: " << currentThrdId << std::endl;
                      break;
                    }
                  }
                }
              }
            }
            else if (verifyData == "BTAUDIO")
            {
              auto result = connection.receiveSerialized<btapiMsg>( "BTAUDIO", std::chrono::milliseconds(5000));
              if(result.second == true)
              {
                std::cout << "Received Data from client [BTAUDIO]....." << std::endl;
                auto message = std::make_unique<ipc::SerializableMessage<btapiMsg>> (*result.first);
                //std::unique_ptr<ipc::SerializableMessage<btapiMsg>> message = std::make_unique<ipc::SerializableMessage<btapiMsg>> (result.first);

                printBtMsg(*message);

                if ((*message)->_btapiMsgId ==
                    btapiMsgId::BTAPI_PROVISIONING)
                {
                  std::cout << "Received BTAPI_PROVISIONING btdaemon V:"
                            << (*message)->_payload
                            << std::endl;

                  if (!((*message)->_payload).empty())
                  {
                      cJSON *json_bt_config_db = cJSON_Parse(((*message)->_payload).c_str());
                      if (json_bt_config_db == NULL)
                      {
                          std::cout << "BT_HEADPHONES_VZIPC : Failed to parse the bt timer config values" << std::endl;
                      }
                      else
                      {
                          cJSON *j_value_name = NULL;
                          
                          j_value_name = cJSON_GetObjectItem(json_bt_config_db, "max_scan_time");
                          if (j_value_name == NULL)
                          {
                              std::cout << "BT_HEADPHONES_VZIPC : Failed to get max_scan_time object" << std::endl;
                          }
                          else
                          {
                              BT_MAX_SCAN_TIME_SEC = j_value_name->valueint;
                              std::cout << "BT_HEADPHONES_VZIPC : BT_MAX_SCAN_TIME_SEC  = " << BT_MAX_SCAN_TIME_SEC << std::endl;
                          }
                      
                          j_value_name = cJSON_GetObjectItem(json_bt_config_db, "max_pair_time");
                          if (j_value_name == NULL)
                          {
                              std::cout << "BT_HEADPHONES_VZIPC : Failed to get max_pair_time object" << std::endl;
                          }
                          else
                          {
                              BT_MAX_PAIR_TIME_SEC = j_value_name->valueint;
                              std::cout << "BT_HEADPHONES_VZIPC : BT_MAX_PAIR_TIME_SEC = " << BT_MAX_PAIR_TIME_SEC << std::endl;
                          }

                          j_value_name = cJSON_GetObjectItem(json_bt_config_db, "max_conn_time");
                          if (j_value_name == NULL)
                          {
                              std::cout << "BT_HEADPHONES_VZIPC : Failed to get max_conn_time object" << std::endl;
                          }
                          else
                          {
                              BT_MAX_CONN_TIME_SEC = j_value_name->valueint;
                              std::cout << "BT_HEADPHONES_VZIPC : BT_MAX_CONN_TIME_SEC = " << BT_MAX_CONN_TIME_SEC << std::endl;
                          }        
                          cJSON_Delete(json_bt_config_db);
                      }
                  }

                  // Sending ACK back
                  // client should keep sending BTAPI_PROVISIONING till it receivs ack
                  // TVPF-8651
                  btapiMsg lbtAudioApiMsg;
                  lbtAudioApiMsg._vzIpcReqType = vzIpcReqType::BTSOFTMIC_RESP;
                  lbtAudioApiMsg._vzIpcAppType = vzIpcAppType::APP_DTV_SVC;
                  lbtAudioApiMsg._btapiMsgId = static_cast< btapiMsgId >( btapiMsgId::BTAPI_PROVISIONING );
                  lbtAudioApiMsg._status = true;
                  lbtAudioApiMsg._ReqCount = 0;
                  lbtAudioApiMsg._payloadSize = 0;
                  lbtAudioApiMsg._payload = "";

                  ipc::SerializableMessage<btapiMsg> msg( std::move( lbtAudioApiMsg ));

                  connection.send( msg, "BTAUDIO", false);

                  std::lock_guard<std::mutex> lock(g_VZMutex);
                  g_ActiveBTAudioThrdId = currentThrdId;
                }

                if (NULL_HANDLE == h_BTAUDIO_req_queue)
                {
                  if (c_msg_q_create(&h_BTAUDIO_req_queue, "btaudio_req_q",
                                     sizeof(t_btaudioMsg), 64) != OSR_OK)
                  {
                    h_BTAUDIO_req_queue = NULL_HANDLE;
                    std::cout << "ERR: create request h_BTAUDIO_req_queue "
                                 "queue fail\n";
                    return;
                  }
                }

                if (NULL_HANDLE == h_BTAUDIO_resp_queue)
                {
                  if (c_msg_q_create(&h_BTAUDIO_resp_queue, "btaudio_resp_q",
                                     sizeof(t_btaudioMsg), 64) != OSR_OK)
                  {
                    h_BTAUDIO_resp_queue = NULL_HANDLE;
                    std::cout
                        << "ERR: create response h_BTAUDIO_queue queue fail\n";
                    return;
                  }
                }

                std::thread writerThread([currentThrdId, tConnections,
                                          &connection]() {
                  t_btaudioMsg reqMsg;
                  memset(&reqMsg, 0x00, sizeof(reqMsg));
                  SIZE_T z_size = sizeof(reqMsg);
                  UINT16 ui2_index = 0;
                  int ReqCount = 0;
                  const int RECEIVE_WAIT_TIME = 2000;
                  while (g_run)
                  {
                    if (OSR_OK ==
                        c_msg_q_receive_timeout(&ui2_index, (VOID *)&reqMsg,
                                                &z_size, &h_BTAUDIO_req_queue,
                                                1, RECEIVE_WAIT_TIME))
                    {
                      btapiMsg lbtAudioApiMsg;
                      lbtAudioApiMsg._vzIpcReqType =
                          vzIpcReqType::BTSOFTMIC_REQ;
                      lbtAudioApiMsg._vzIpcAppType = vzIpcAppType::APP_DTV_SVC;
                      lbtAudioApiMsg._btapiMsgId =
                          static_cast<btapiMsgId>(reqMsg.type);
                      lbtAudioApiMsg._status = true;
                      lbtAudioApiMsg._ReqCount = ReqCount++;
                      lbtAudioApiMsg._payloadSize = 0;
                      lbtAudioApiMsg._payload = "";
                      if (reqMsg.msg_len)
                      {
                        lbtAudioApiMsg._payload.assign(reqMsg.msg,
                                                       reqMsg.msg_len);
                      }
                      lbtAudioApiMsg._payloadSize = lbtAudioApiMsg._payload.size();

                      ipc::SerializableMessage<btapiMsg> msg(
                          std::move(lbtAudioApiMsg));

                      printBtMsg(msg);
                      std::cout << "Sending Request to Client MsgId:"
                                << static_cast<int>(lbtAudioApiMsg._btapiMsgId);
                      std::cout << "-------------------------------------------"
                                   "-------------------"
                                << std::endl;
                      connection.send(msg, "BTAUDIO", false);
                    }
                    {
                      std::lock_guard<std::mutex> lock(g_VZMutex);
                      if (g_ActiveBTAudioThrdId != currentThrdId)
                      {
                        std::cout
                            << "Sender Thread: Closing BT Audio connection: "
                            << tConnections
                            << " ,currentThrdId: " << currentThrdId
                            << std::endl;
                        break;
                      }
                    }
                  }
                });

                while (g_run)
                {
                  auto result = connection.receiveSerialized<btapiMsg>( "BTAUDIO", std::chrono::milliseconds(5000));
                  if(result.second == true)
                  {
                    auto message = std::make_unique<ipc::SerializableMessage<btapiMsg>> (*result.first);
                    //std::unique_ptr<ipc::SerializableMessage<btapiMsg>> message = std::make_unique<ipc::SerializableMessage<btapiMsg>> (result.first);
                    printBtMsg(*message);

                    size_t payload_size = ((*message)->_payloadSize);
                    btapiMsgId msgId = ((*message)->_btapiMsgId);

                    t_btaudioMsg respMsg;
                    respMsg.type = (tBtAudio)msgId;
                    respMsg.msg_len = payload_size;
                    if (payload_size)
                    {
                      respMsg.msg = (char *)malloc(payload_size);
                      if(respMsg.msg != NULL) {
                        memset(respMsg.msg, 0x00, payload_size);
                        memcpy(respMsg.msg, (*message)->_payload.c_str(), payload_size);
                        std::cout << "Payload is : " << respMsg.msg << std::endl;
                      } else {
                        std::cout << "Unable to allocate memory for Received Payload\n";
                        continue;
                      }
                    }
                    else
                    {
                      respMsg.msg = NULL;
                      std::cout << "Payload is NULL\n";
                    }

                    std::cout << "Received Type is : " << respMsg.type << "\n";
                    switch (respMsg.type)
                    {
                    case BTAPI_SINK_CONNECTED:
                    case BTAPI_SINK_DISCONNECTED:             
                    case BTAPI_SINK_STREAM_STARTED:
                    case BTAPI_SINK_STREAM_STOPPED:
                    case BTAPI_VOLUME_INFO:
                    case BTAPI_VOLUME_UP:
                    case BTAPI_VOLUME_DOWN:
                    case BTAPI_MUTE_UNMUTE:
                    {
                      if( BTAPI_SINK_CONNECTED == respMsg.type)
                      {                 
                          std::cout << "BTAPI_SINK_CONNECTED is Received\n";    
                          if (respMsg.msg != NULL)
                          { 
                              std::cout << "MAC address is : \n" << (*message)->_payload;
                              handle_bt_sink_connect((*message)->_payload.c_str());
                          }
                      }
                      else if( BTAPI_SINK_DISCONNECTED == respMsg.type)
                      {
                          std::cout << "BTAPI_SINK_DISCONNECTED is Received\n";
                          if (respMsg.msg != NULL)
                          {
                              std::cout << "MAC address is : \n" << (*message)->_payload;
                              handle_bt_device_disconnection((*message)->_payload.c_str());
                          }
                      }
                      else if( BTAPI_SINK_STREAM_STARTED == respMsg.type)
                      {
                        std::cout << "BTAPI_SINK_STREAM_STARTED is Received\n";
                        if (respMsg.msg != NULL)
                        {
                          std::cout << "MAC address is : " << (*message)->_payload  << std::endl;
                          handle_bt_start_stream((*message)->_payload.c_str());
                        }
                      }
                      else if( BTAPI_SINK_STREAM_STOPPED == respMsg.type)
                      {
                        std::cout << "BTAPI_SINK_STREAM_STOPPED is Received\n";
                        if (respMsg.msg != NULL)
                        {
                          std::cout << "MAC address is : " << (*message)->_payload  << std::endl;
                          handle_bt_stop_stream((*message)->_payload.c_str());
                        }
                      }
                      if (respMsg.msg != NULL)
                      {
                        memset(respMsg.msg, 0x00, payload_size);
                        memcpy(respMsg.msg, (*message)->_payload.c_str(),
                               payload_size);
                        char *btui_text;
                        int volume = 0;

                        sscanf(respMsg.msg, "%d", &volume);
                        int length =
                            snprintf(NULL, 0, "%d %d", respMsg.type, volume);

                        btui_text = (char *)c_mem_alloc(length);
                        if (btui_text == NULL)
                        {
                          std::cout << "Unable to allocate Memory for btui_text" << std::endl;
                          /* Free the memory allocated for forming the message, since we are processing further */
                          free(respMsg.msg);
                          continue;
                        }
                        c_memset((VOID *)btui_text, 0x00, length);

                        sprintf(btui_text, "%d %d", respMsg.type, volume);
                        std::cout << "BTAPI_VOLUME is Received, Volume is : "
                                  << volume << std::endl;
                        // if (is_bt_audio_device_streaming())
                        // {
                          nav_request_context_switch(bt_vol_ctrl_post_bt_event,
                                                     (VOID *)btui_text, NULL,
                                                     NULL);
                        // }
                        // else
                        // {
                        //   std::cout << "BTAPI_VOLUME event is ignored, "
                        //                "streaming is not going on\n";
                        // }
                      }
                      else
                      {
                        std::cout << "Unable to allocate memory for Volume Notification\n";
                      }
                    }
                    break;
                    case BTAPI_START_SCAN:
                    case BTAPI_STOP_SCAN:
                    case BTAPI_GET_SCAN_LIST:
                    case BTAPI_START_STREAM:
                    case BTAPI_STOP_STREAM:
                    case BTAPI_PAIR_DEVICE:
                    case BTAPI_UNPAIR_DEVICE:
                    case BTAPI_SET_VOLUME:
                    case BTAPI_GET_VOLUME:
                    case BTAPI_GET_AUDIO_DEV_CONN_STATE:
                    {
                      if (NULL_HANDLE == h_BTAUDIO_resp_queue)
                      {
                        std::cout
                            << "ERR: BTAUDIO queue is not yet created \n";
                        return;
                      }
                      if (OSR_OK != c_msg_q_send(h_BTAUDIO_resp_queue,
                                                 (VOID *)&respMsg,
                                                 sizeof(respMsg), 200))
                      {
                        std::cout << "ERR: BTAUDIO queue failed to send \n";
                      }
                    }
                    default:
                      break;
                    }
                  }
                  {
                    std::lock_guard<std::mutex> lock(g_VZMutex);
                    if (g_ActiveBTAudioThrdId != currentThrdId)
                    {
                      std::cout
                          << "Receiver Thread:  Closing BT Audio connection: "
                          << tConnections
                          << " ,currentThrdId: " << currentThrdId << std::endl;
                      break;
                    }
                  }
                }
                if (writerThread.joinable())
                  writerThread.join();
              }
            }

            {
              std::lock_guard<std::mutex> lock(g_VZMutex);
              if (!((g_ActiveBTSoftMicThrdId == currentThrdId) ||
                    (g_ActiveBTAudioThrdId == currentThrdId) ||
                    (g_ActiveHmonThrdId == currentThrdId)))
              {
                std::cout << "Closing connection: " << tConnections
                          << " ,currentThrdId: " << currentThrdId << std::endl;
                break;
              }
            }
          }
        },
        std::move(*connection.release()));

    ++tConnections;
    threadHandler.detach();
  }
}

bool SendReqBTSOFTMIC_Q(int t_msg)
{

  if (NULL_HANDLE == h_BTSOFTMIC_queue)
  {
    std::cout << "ERR: BTSOFTMIC queue is not yet created \n";
    return false;
  }

  if (OSR_OK !=
      c_msg_q_send(h_BTSOFTMIC_queue, (VOID *)&t_msg, sizeof(t_msg), 200))
  {
    std::cout << "ERR: BTSOFTMIC queue failed to send \n";
    return false;
  }
  return true;
}

int SendReqBTAUDIO_Q(tBtAudio type, char *payload)
{
  INT32 ret = 0;
  t_btaudioMsg reqMsg;
  std::cout << "SendReqBTAUDIO_Q for : " << type  << std::endl;
  size_t len;

  reqMsg.type = type;
  if (NULL != payload)
  {
    len = strlen(payload);
    reqMsg.msg_len = len;
    reqMsg.msg = (char *)malloc(len+1);// 1 extra space for \0
    if (NULL == reqMsg.msg)
    {
      std::cout << "ERR: BTAUDIO cannot allocate memory for payload...\n";
      return -2;
    }
    memcpy(reqMsg.msg, payload, len);
  }
  else
  {
    reqMsg.msg_len = 0;
    reqMsg.msg = NULL;
  }

  if (NULL_HANDLE == h_BTAUDIO_req_queue)
  {
    std::cout << "ERR: BTAUDIO queue is not yet created \n";
    return -1;
  }

  ret = c_msg_q_send(h_BTAUDIO_req_queue, (VOID *)&reqMsg, sizeof(reqMsg), 200);
  if (OSR_OK != ret)
  {
    std::cout << "ERR: BTAUDIO queue failed to send err:" << ret << std::endl;
    return -1;
  }
  return 0;
}

char *GetRespBTAUDIO_Q(tBtAudio type)
{
  t_btaudioMsg respMsg;
  int ret = 0;
  UINT16 count = 0;
  SIZE_T z_size = sizeof(respMsg);
  UINT16 ui2_index = 0;

  std::cout << "GetRespBTAUDIO_Q for type: " << type << std::endl;

  ret = c_msg_q_num_msgs(h_BTAUDIO_resp_queue, &count);

  std::cout << "h_BTAUDIO_resp_queue is contains : " << count << std::endl;

  if (ret < 0)
  {
    std::cout << "h_BTAUDIO_resp_queue c_msg_q_num_msgs returned : " << ret
              << std::endl;
    return NULL;
  }

  memset(&respMsg, 0x00, sizeof(t_btaudioMsg));

  if (count)
  {
    for (size_t i = 0; i < count; i++)
    {
      std::cout
          << "h_BTAUDIO_resp_queue queue not empty, try read one msg from: "
          << count << std::endl;

      ret = c_msg_q_receive_timeout(&ui2_index, (VOID *)&respMsg, &z_size,
                                    &h_BTAUDIO_resp_queue, 1, ui4_time);
      if (OSR_OK == ret)
      {
        std::cout << "h_BTAUDIO_resp_queue message was successfully readed! "
                  << std::endl;
        std::cout << "h_BTAUDIO_resp_queue readed type: " << respMsg.type
                  << " req type: " << type << std::endl;
        if (respMsg.type == type)
        {
          std::cout
              << "h_BTAUDIO_resp_queue message with proper type was found "
              << respMsg.msg << std::endl;
          return respMsg.msg;
        }
        if (NULL != respMsg.msg)
        {
          free(respMsg.msg);
          respMsg.msg = NULL;
        }
        continue;
      }
      else
      {
        std::cout << "h_BTAUDIO_resp_queue during reading message ERROR ocured "
                  << ret << std::endl;
        return NULL;
      }
    }
  }
  else
  {
    std::cout << "h_BTAUDIO_resp_queue nothing to be read quit..." << std::endl;
    return NULL;
  }

  std::cout << "h_BTAUDIO_resp_queue required type not found quit..."
            << std::endl;
  return NULL;
}

void printHMONMsg(std::unique_ptr<ipc::SerializableMessage<healthMonMsg>> &message)
{
  std::cout << "Received Request from cleint [HMON]:- vzIpcReqType: "
            << static_cast<int>((*message)->_vzIpcReqType)
            << ",vzIpcAppType: " << static_cast<int>((*message)->_vzIpcAppType)
            << ",hMonMsgId: " << static_cast<int>((*message)->_hMonMsgId)
            << ",Payload: " << static_cast<std::string>((*message)->_payload)
            << ",Status: " << (((*message)->_status) ? "True" : "False")
            << ",ReqCount: " << ((*message)->_ReqCount) << std::endl;
}

bool handleHealthmonRequests(
    std::unique_ptr<ipc::SerializableMessage<healthMonMsg>> &message)
{
  printHMONMsg(message);

  switch ((*message)->_hMonMsgId)
  {
  case hMonMsgId::HMON_INIT:
    std::cout << "Received HMON_INIT Request! Lets start!" << std::endl;
    (*message)->_status = true;
    break;

  case hMonMsgId::HMON_WIFI_START:
    std::cout << "Received HMON_WIFI_START Request" << std::endl;
    (*message)->_status = !a_nw_wlan_drv_start();
    break;

  case hMonMsgId::HMON_WIFI_STOP:
    std::cout << "Received HMON_WIFI_STOP Request" << std::endl;
    (*message)->_status = !a_nw_wlan_drv_stop();
    break;

  case hMonMsgId::HMON_IS_OOBE:
    std::cout << "Received HMON_IS_OOBE Request" << std::endl;
    (*message)->_status = a_wzd_is_oobe_mode();
    break;

  case hMonMsgId::HMON_VIRTUAL_INPUT_SOURCE:
  {
    std::cout << "Received HMON_VIRTUAL_INPUT_SOURCE Request" << std::endl;
    INT32 i4_ret = TVR_FAIL;
    ISL_REC_T t_isl_active = {0};
    TV_WIN_ID_T e_tv_win_id = TV_WIN_ID_MAIN;
    UTF16_T *pw2s_source_name = NULL;
    char sourceName[256] = {0};
    (*message)->_status = false;

    do
    {
      if ((i4_ret = a_tv_get_focus_win(&e_tv_win_id)) != TVR_OK)
      {
        std::cout << "HMON_VIRTUAL_INPUT_SOURCE: call a_tv_get_focus_win failed"
                  << i4_ret << std::endl;
        break;
      }

      if ((i4_ret = a_tv_get_isl_rec_by_win_id(e_tv_win_id, &t_isl_active)) !=
          TVR_OK)
      {
        std::cout << "HMON_VIRTUAL_INPUT_SOURCE: call "
                     "a_tv_get_isl_rec_by_win_id failed"
                  << i4_ret << std::endl;
        break;
      }

      if ((pw2s_source_name = a_isl_get_display_name(&t_isl_active)) == NULL)
      {
        std::cout
            << "HMON_VIRTUAL_INPUT_SOURCE: call a_isl_get_display_name failed"
            << std::endl;
        break;
      }

      c_uc_w2s_to_ps(pw2s_source_name, sourceName, 256);
      (*message)->_status = true;
      (*message)->_payload = sourceName;
      (*message)->_payloadSize = (*message)->_payload.length();

    } while (0);
  }
  break;

  case hMonMsgId::HMON_WIFI_SSID:
  {
    std::cout << "Received HMON_SSID Request" << std::endl;
    (*message)->_status = false;

#if 0
        CHAR s_ssid[NET_802_11_MAX_LEN_SSID+1] = {0};

        NW_WLAN_STATE_T         e_wlan_state;
        INT32 i4_ret = a_nw_wlan_status(&e_wlan_state);
        if (i4_ret != NWR_OK) {
          std::cout << "HMON_SSID: call a_nw_wlan_status failed: " << i4_ret << std::endl;
        }
        std::cout << "HMON_SSID: a_nw_wlan_status: " << e_wlan_state<< std::endl;
#endif

    do
    {

      if (a_nw_is_ethernet_plugin() == TRUE)
      {
        std::cout
            << "HMON_IS_WIFI: a_nw_is_ethernet_plugin, Ethernet connected:"
            << std::endl;
        break;
      }

      NET_802_11_SSID_T t_Ssid;
      c_memset(&t_Ssid, 0, sizeof(t_Ssid));

      // a_nw_get_wlan_ssid internally calls a_cfg_get_wlan_ssid
      INT32 i4_ret = a_nw_get_wlan_ssid(&t_Ssid);
      if (i4_ret == NWR_OK)
      {
        std::cout << "HMON_SSID: a_nw_get_wlan_ssid: t_Ssid.ui4_SsidLen: "
                  << t_Ssid.ui4_SsidLen << " SSID: " << t_Ssid.ui1_aSsid
                  << std::endl;

        /* If case no SSID, a_nw_get_wlan_ssid returns NWR_OK, Check is required
         * to verify whether SSID len */
        if (t_Ssid.ui4_SsidLen > 0)
        {
          (*message)->_status = true;
          (*message)->_payload = t_Ssid.ui1_aSsid;
          (*message)->_payloadSize = (*message)->_payload.length();
        } else {
          std::cout << "HMON_SSID: No SSID associated" << std::endl;
          (*message)->_status = true;
          (*message)->_payload = "";
          (*message)->_payloadSize = 0;
        }
        break;
      }

    } while (0);
  }
  break;

  case hMonMsgId::HMON_GET_CONNECTION_STATUS:
  {
    std::cout << "Received HMON_GET_CONNECTION_STATUS Request" << std::endl;
    BOOL b_is_connect = FALSE;
    BOOL b_ethernet = FALSE;

    /* Get the Connection Type */
    a_nw_get_ethernet_connect_info(&b_ethernet);
    if(b_ethernet) {
      (*message)->_payload = "Ethernet";
      (*message)->_payloadSize = (*message)->_payload.length();
    } else {
      (*message)->_payload = "WIFI";
      (*message)->_payloadSize = (*message)->_payload.length();
    }

    /* Get the Connection Status */
    a_nw_is_network_connected(&b_is_connect);
    if(b_is_connect) {
      (*message)->_status = true;
    }else {
      (*message)->_status = false;
    }
  }
  break;
 

  case hMonMsgId::HMON_SCAN_FIND_SSID:
  {
    std::cout << "Received HMON_GET_SCANLIST Request" << std::endl;
    (*message)->_status = false;
    (*message)->_payloadSize = 0;

    INT32 i4_ret = NET_WLAN_OK;
    NET_802_11_ESS_LIST_T       t_essList_tmp;
    c_memset (&t_essList_tmp, 0, sizeof(t_essList_tmp));
    UINT32                      ui4_idx = 0;
    NET_802_11_ESS_INFO_T*      p_essInfo = NULL;

    i4_ret = a_nw_wlan_scan();
    if(NET_WLAN_OK != i4_ret) {
      std::cout << "[ERROR] HMON_GET_SCANLIST failed for start a_nw_wlan_scan(), retry" << std::endl;
      sleep(3);
      if(NET_WLAN_OK != a_nw_wlan_scan()) {
        std::cout << "[ERROR] HMON_GET_SCANLIST start a_nw_wlan_scan(), second retry also failed" << std::endl;
      }
    }

    /* wait for 5 sec to get the scan list */
    sleep(5);

    NET_802_11_SCAN_RESULT_T    t_scan_result;
    c_memset (&t_scan_result, 0, sizeof(t_scan_result));

    i4_ret = a_nw_wlan_get_scan_result(&t_scan_result);
    if(NET_WLAN_OK != i4_ret) {
      std::cout << "HMON_GET_SCANLIST failed a_nw_wlan_get_scan_result\n" << std::endl;
      (*message)->_payload = "SCAN_RESULT_FAILED";
      (*message)->_payloadSize = (*message)->_payload.length();
      return false;
    }

    if(!t_scan_result.ui4_NumberOfItems) {
      std::cout << "HMON_GET_SCANLIST :a_nw_wlan_get_scan_result empty list\n" << std::endl;
      (*message)->_payload = "SCAN_RESULT_EMPTY";
      (*message)->_payloadSize = (*message)->_payload.length();
      return false;
    }

    NET_802_11_BSS_INFO_T*      p_bssInfo = NULL;
    std::cout << "HMON_GET_SCANLIST a_nw_wlan_get_scan_result: Total NumberOfItems:" << t_scan_result.ui4_NumberOfItems << std::endl;

    std::string validateSSID = (*message)->_payload;
    (*message)->_payload = "SSID_NOT_FOUND";
    (*message)->_payloadSize = (*message)->_payload.length();

    for (ui4_idx = 0; ui4_idx < t_scan_result.ui4_NumberOfItems; ui4_idx++) {
      p_bssInfo = &(t_scan_result.p_BssInfo[ui4_idx]);
      if ((NULL != p_bssInfo) && (p_bssInfo->t_Ssid.ui4_SsidLen >= 7)) {
        std::cout << ": HMON_GET_SCANLIST: SSIDINFO:" << p_bssInfo->t_Ssid.ui1_aSsid << ", len: " << p_bssInfo->t_Ssid.ui4_SsidLen << std::endl;
        if(validateSSID == p_bssInfo->t_Ssid.ui1_aSsid) {
        (*message)->_status = true;
        (*message)->_payload = "SSID_FOUND";
        (*message)->_payloadSize = (*message)->_payload.length();
        break;
        }
      }
    }
  }
  break;

  default:
  {
    std::cout << "Cannot Handle HMON Request: "
              << static_cast<int>((*message)->_hMonMsgId) << std::endl;
    (*message)->_status = false;
  }
  }

  (*message)->_vzIpcReqType = vzIpcReqType::HMON_RESP;
  (*message)->_vzIpcAppType = vzIpcAppType::APP_DTV_SVC;

  return true;
}

void printBtMsg(ipc::SerializableMessage<btapiMsg> &message)
{
  std::cout << "Received Request from client [BTAudio]:- vzIpcReqType: "
            << static_cast<int>((*message)._vzIpcReqType)
            << ",vzIpcAppType: " << static_cast<int>((*message)._vzIpcAppType)
            << ",_btapiMsgId: " << static_cast<int>((*message)._btapiMsgId)
            << ",Payload: " << static_cast<std::string>((*message)._payload)
            << ",PayloadSize: " << static_cast<int>((*message)._payloadSize)
            << ",Status: " << ((*message)._status ? "True" : "False")
            << ",ReqCount: " << static_cast<int>((*message)._ReqCount) << std::endl;
}
