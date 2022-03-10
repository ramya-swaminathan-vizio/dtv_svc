#ifndef __VZ_IPC_THREAD__
#define __VZ_IPC_THREAD__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

enum Softmic
{
  SOFTMIC_START,
  SOFTMIC_STOP
};

typedef enum _BtAudio
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
  BTAPI_MUTE_UNMUTE,
  COMMON_DTV_TO_SENTRY,
  BTAPI_MSG_MAX
}tBtAudio;

/**
 * @brief This function pointer to thread which maintain VIZIO IPC.
 * 
 * @param pv_arg 
 */
void vz_ipc_task_thread(void* pv_arg);

/**
 * @brief This function must be used for send 
 * notifications START|STOP from starboard (Youtube)
 * to the hidraw-test-msbc app.
 * 
 * @param t_msg enum with event type SOFTMIC_START | SOFTMIC_STOP 
 * @return bool TRUE if message was successfully added to queue, FALSE if queu is not exists.
 */
bool SendReqBTSOFTMIC_Q(int t_msg);

/**
 * @brief This function send reques to BT stack during user intract with sidebar menu
 * for manage BT audio devices.
 * 
 * @param type ENUM with request type.
 * @param payload pointer to the string with which contains payload data which depends on
 * request type, usually payload will contains string with the MAC address of managed device.
 * @return int result of adding request to the queue, success 0. rest negative value fail.
 */
int SendReqBTAUDIO_Q(tBtAudio type, char *payload);

/**
 * @brief This function check is queue is contains new messages from BT stack to sidebar menu,
 * some part of request requires responce with payload, for example scan list of scanned devices,
 * result for connect/pair/disconnect.
 *
 * BTAPI_GET_SCAN_LIST - must retutn JSON formatted string.
 * BTAPI_START_STREAM | BTAPI_STOP_STREAM - must return back MAC address of paired/connected/disconnected device.
 * 
 * @return char* in SUCCESS case return pointer to the string with payload, either return NULL as FAIL.
 */
char *GetRespBTAUDIO_Q(tBtAudio type);

#ifdef __cplusplus
}
#endif

#endif //__VZ_IPC_THREAD__
