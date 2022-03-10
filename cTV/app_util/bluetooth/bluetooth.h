/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation ("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright (C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights (including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation ("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights (including without limitation, patent, copyright, and      *
 * trade secrets) in and to any modifications and derivatives to MediaTek     *
 * Software, whoever made, shall also remain the exclusive property of        *
 * MediaTek Inc.  Nothing herein shall be construed as any transfer of any    *
 * title to any intellectual property right in MediaTek Software to Receiver. *
 *                                                                            *
 *   2)This MediaTek Software Receiver received from MediaTek Inc. and/or its *
 * representatives is provided to Receiver on an "AS IS" basis only.          *
 * MediaTek Inc. expressly disclaims all warranties, expressed or implied,    *
 * including but not limited to any implied warranties of merchantability,    *
 * non-infringement and fitness for a particular purpose and any warranties   *
 * arising out of course of performance, course of dealing or usage of trade. *
 * MediaTek Inc. does not provide any warranty whatsoever with respect to the *
 * software of any third party which may be used by, incorporated in, or      *
 * supplied with the MediaTek Software, and Receiver agrees to look only to   *
 * such third parties for any warranty claim relating thereto.  Receiver      *
 * expressly acknowledges that it is Receiver's sole responsibility to obtain *
 * from any third party all proper licenses contained in or delivered with    *
 * MediaTek Software.  MediaTek is not responsible for any MediaTek Software  *
 * releases made to Receiver's specifications or to conform to a particular   *
 * standard or open forum.                                                    *
 *                                                                            *
 *   3)Receiver further acknowledge that Receiver may, either presently       *
 * and/or in the future, instruct MediaTek Inc. to assist it in the           *
 * development and the implementation, in accordance with Receiver's designs, *
 * of certain softwares relating to Receiver's product(s) (the "Services").   *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MediaTek Inc. with respect  *
 * to the Services provided, and the Services are provided on an "AS IS"      *
 * basis. Receiver further acknowledges that the Services may contain errors  *
 * that testing is important and it is solely responsible for fully testing   *
 * the Services and/or derivatives thereof before they are used, sublicensed  *
 * or distributed. Should there be any third party action brought against     *
 * MediaTek Inc. arising out of or relating to the Services, Receiver agree   *
 * to fully indemnify and hold MediaTek Inc. harmless.  If the parties        *
 * mutually agree to enter into or continue a business relationship or other  *
 * arrangement, the terms and conditions set forth herein shall remain        *
 * effective and, unless explicitly stated otherwise, shall prevail in the    *
 * event of a conflict in the terms in any agreements entered into between    *
 * the parties.                                                               *
 *                                                                            *
 *   4)Receiver's sole and exclusive remedy and MediaTek Inc.'s entire and    *
 * cumulative liability with respect to MediaTek Software released hereunder  *
 * will be, at MediaTek Inc.'s sole discretion, to replace or revise the      *
 * MediaTek Software at issue.                                                *
 *                                                                            *
 *   5)The transaction contemplated hereunder shall be construed in           *
 * accordance with the laws of Singapore, excluding its conflict of laws      *
 * principles.  Any disputes, controversies or claims arising thereof and     *
 * related thereto shall be settled via arbitration in Singapore, under the   *
 * then current rules of the International Chamber of Commerce (ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * $RCSfile: bluetooth.h,v $
 * $Revision: #6 $
 * $Date: 2015/11/17 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *      This file is the internal header file for bluetooth.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

#ifndef _BLUETOOTH_H_
#define _BLUETOOTH_H_

#include "../a_bluetooth.h"

#include "u_common.h"
//#include "u_bluetooth.h"
#include "u_dbg.h"
#include "u_bt_mw_avrcp.h"

/* Return Values */
#define PBR_OK                                              ((INT32) 0)
#define PBR_FAIL                                            ((INT32)-1)
#define PBR_INV_ARG                                         ((INT32)-2)

#define PLAYBACKR_OK                                        ((INT32) 0)
#define BLUETOOTH_DEVICE_ADDR_LEN                           ((INT32) 48)

#define BT_MAX_NUM_NOTIFY_CLIENT                (16)

/* Debug */
#undef DBG_INIT_LEVEL
#ifdef DBG_INIT_LEVEL_APP_BLUETOOTH
    #define DBG_INIT_LEVEL              DBG_INIT_LEVEL_APP_BLUETOOTH
#else
    #define DBG_INIT_LEVEL              DBG_LEVEL_ALL
#endif

#undef DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE                bluetooth_get_dbg_level()

#ifdef DBG_MODULE_NAME_PREFIX
#undef DBG_MODULE_NAME_PREFIX
#endif
#define DBG_MODULE_NAME_PREFIX    "[BT_APP]"

//#define BT_APP_LOG_DEFAULT(_stmt)    DBG_ERROR (_stmt)
//#define BT_APP_LOG_ERR(_stmt)        DBG_ERROR (_stmt)
//#define BT_APP_LOG_API(_stmt)        DBG_API  (_stmt)
//#define BT_APP_LOG_INFO(_stmt)       DBG_INFO (_stmt)
//#define BT_APP_LOG_SANITY(_stmt)     DBG_INFO (_stmt)
//#define DBG_ERROR_PLAYBACK(_stmt)    DBG_ERROR(_stmt)
//#define DBG_DEFAULT_PLAYBACK(_stmt)  DBG_ERROR(_stmt)

#define BT_APP_LOG_DEFAULT(_stmt)    DBG_LOG_PRINT (_stmt)
#define BT_APP_LOG_ERR(_stmt)        DBG_LOG_PRINT (_stmt)
#define BT_APP_LOG_API(_stmt)        DBG_LOG_PRINT  (_stmt)
#define BT_APP_LOG_INFO(_stmt)       DBG_LOG_PRINT (_stmt)
#define BT_APP_LOG_SANITY(_stmt)     DBG_LOG_PRINT (_stmt)
#define DBG_ERROR_PLAYBACK(_stmt)    DBG_LOG_PRINT(_stmt)
#define DBG_DEFAULT_PLAYBACK(_stmt)  DBG_LOG_PRINT(_stmt)


// define SRC mode AVRCP cmd implement method, finally we chose to send sircs key to IFCON
// because some key is treated as command/status from IFCON, like [TUNING+] key in FM
#define BT_APP_SRC_MODE_AVRCP_CMD_TO_IFCON  (1)

#define BT_APP_CHK_FAIL(_ret, _ret_on_err)                            \
{                                                                      \
    if(_ret < 0)                                                       \
    {                                                                  \
        BT_APP_LOG_ERR(("<BT_APP> ERR: file=%s, line=%d, reason=%d\n", \
                         __FILE__, __LINE__, _ret));                   \
        return _ret_on_err;                                            \
    }                                                                  \
}

#define BT_APP_LOG_ON_FAIL(_ret)                                       \
{                                                                      \
    if(_ret < 0)                                                       \
    {                                                                  \
        BT_APP_LOG_ERR(("<BT_APP> ERR: file=%s, line=%d, reason=%d\n", \
                         __FILE__, __LINE__, _ret));                   \
        _ret = 0;                                                      \
    }                                                                  \
}

typedef enum _BT_APP_MSG_TYPE          // Bluetooth APP message type
{
    BT_APP_MSG_BTM_NFY_GAP_EVENT,        // The event from BTM: GAP event
    BT_APP_MSG_BTM_NFY_A2DP_SNK_DEV,     // The event from BTM: Find A2DP Sink device
    BT_APP_MSG_BTM_NFY_TRACK_CHGD,       // The event form BTM: Track is changed
    BT_APP_MSG_BTM_NFY_PLAY_STATE_CHGD,  // The event from BTM: playback state is changed
    BT_APP_MSG_BTM_NFY_META_DATA_OK,     // The event from BTM: meta data has been ready in BTM
    BT_APP_MSG_BTM_NFY_PLAY_STATUS_OK,   // The event from BTM: play status has been ready in BTM
    BT_APP_MSG_BTM_NFY_VOLUME_CHG,       // The event from BTM: volume chang
    BT_APP_MSG_BTM_NFY_SPP_EVENT,        // The event from BTM: SPP event
    BT_APP_MSG_IFCON_CMD_BT_START_KEY,   // The command from IFCon: COM_DVD_BT_start
    BT_APP_MSG_IFCON_CMD_NFC_START,      // The command from IFCon: COM_DVD_NFC_start
    BT_APP_MSG_EVENT_NFC_TOUCH_TIME_OUT, // The event: no device request to connect after NFC touch
    BT_APP_MSG_REQ_ENABLE_BT,         // Request: enable bluetooth
    BT_APP_MSG_REQ_DISABLE_BT,        // Request: disable bluetooth
    BT_APP_MSG_REQ_SET_LOCAL_NAME,       // Request: set local bluetooth device name
    BT_APP_MSG_REQ_START_BT_INPUT,       // Request:  start bluetooth
    BT_APP_MSG_REQ_STOP_BT_INPUT,        // Request: stop bluetooth
    BT_APP_MSG_REQ_SPP_CONNECT,          // Request: establish SPP connection
    BT_APP_MSG_REQ_SPP_DISCONNECT,       // Request: disconnect SPP connection
    BT_APP_MSG_REQ_GET_BITRATE,          // Request: get bitrate from BTM and update UI
    BT_APP_MSG_REQ_GET_PLAYSTATUS,       // Request: get play status from BTM
    BT_APP_MSG_REQ_GET_RSSI_LEVEL,       // Request: get RSSI level of connected SRC device and update UI
    BT_APP_MSG_REQ_HIDE_PLAY_WINDOW,     // Request: hide playback window
    BT_APP_MSG_NFY_VISUALIZER_STT,       // The event: Visualizer stt is changed
    BT_APP_MSG_NFY_FUNCTION_KEY_STT, // The event: the status of [FUNCTION] key is changed (enable or disable)
    BT_APP_MSG_EVENT_NO_AVRCP,       // The event: cannot establish AVRCP
    BT_APP_MSG_NFY_AMP_VOLUME_CHGD,       // The event: platform absolute volume change, need to response to SRC device, newly added for AVRCP1.5
    BT_APP_MSG_BTM_NFY_AVRCP_KEY_CMD,    // The event: Operate with A2DP source mode,target as category1 device, receive key: PLAY/PAUSE/STOP/NEXT/PREV/FF/FR
    BT_APP_MSG_BTM_NFY_UPLOAD_INFO,      // The event: BTM notify upload info to request APP to set decode downsample
    BT_APP_MSG_REQ_START_SINK_DEVICE_LIST,//The event: show sink device list
    BT_APP_MSG_REQ_CLOSE_SINK_DEVICE_LIST,//The event: close sink device list
    BT_APP_MSG_NFY_SINK_SCAN_START,       //The event: start scan sink device
    BT_APP_MSG_NFY_SINK_SCAN_FINISH,      //The event: scan sink device list time out
    BT_APP_MSG_SINK_LIST_KEY_EVENT,       //The event: key proc for sink device list
    BT_APP_MSG_NFY_BT_MODE_CHG,           //The event:bluetooth mode is changed in setup
    BT_APP_MSG_NFY_BT_DONGLE_ATTACH,      //The event:bluetooth dongle is attach
    BT_APP_MSG_REQ_BT_TX_DEV_LIST,        //The event:ifcon request to get the sink device list information
    BT_APP_MSG_IFCON_DATA_SYNC_BT_CMD,    //The event:ifcon send bt command like COM_DVD_BT_XX
    BT_APP_MSG_NFY_SRC_MODE_PBC_STT,     //The event:playback status change
    BT_APP_MSG_REQ_INPUT_A2DP_CONNECT_DISCONNECT, //The event:connect or disconnect input a2dp
    BT_APP_MSG_NFY_HID_EVENT, //The event from MW:HID event
    BT_APP_MSG_NFY_A2DP_EVENT, //The event from MW:A2DP event
    BT_APP_MSG_INIT,
    BT_APP_MSG_ON_OFF_PROC,
    BT_APP_MSG_GET_PAIRING_KEY,
    BT_APP_MSG_PRE_SUSPEND_EXIT,
    BT_APP_MSG_TYPE_MAX
} BT_APP_MSG_TYPE_E;

typedef struct _BT_APP_MSG_E
{
    BT_APP_MSG_TYPE_E msg_type;
    UINT32 ui4_msg_id;
    UINT32 ui4_data1;
    UINT32 ui4_data_size;
    VOID   *pv_data;
} BT_APP_MSG_T;

typedef enum _BT_APP_MODE   // Bluetooth APP Mode
{
    BT_APP_MODE_PAIRING = 1, // Pairing mode: The unit is waiting other device pairing/connection.
    BT_APP_MODE_CONNECT,     // Connecting mode:  The unit is trying to connect other device.
    BT_APP_MODE_PLAY,        // Playing mode: The unit is playing Bluetooth audio as a Bluetooth A2DP SNK device.
} BT_APP_MODE_E;

/* Refer to I2C_Category_DVD_CD_forMTK_Ver004.xlsx "Key Remocon" sheet*/
typedef enum _BT_APP_AVRCP_KEY_CODE
{
    BT_APP_AVRCP_KEY_CODE_NONE   = 0x00,
    BT_APP_AVRCP_KEY_CODE_PLAY   = 0x10,
    BT_APP_AVRCP_KEY_CODE_PAUSE  = 0x11,
    BT_APP_AVRCP_KEY_CODE_STOP   = 0x13,
    BT_APP_AVRCP_KEY_CODE_NEXT   = 0x16,
    BT_APP_AVRCP_KEY_CODE_PREV   = 0x17,
    BT_APP_AVRCP_KEY_CODE_FF     = 0x3E,
    BT_APP_AVRCP_KEY_CODE_FR     = 0x3F,
} BT_APP_AVRCP_KEY_CODE_E;


typedef enum _ErrorCode
{
    ERRORCODE_OK = 0,
    ERRORCODE_NORMAL_ERROR,
    ERRORCODE_INV_ARG
}ErrorCode;

//extern BOOL  bluetooth_driver_init_done(VOID);
extern INT32 bluetooth_init(VOID);
extern INT32 bluetooth_system_power_on_proc(VOID);

//extern VOID bt_app_msg_proc(VOID* pt_btmsg);
extern INT32 bt_app_send_msg_to_bt_thread(BT_APP_MSG_T *pt_bt_msg);
extern INT32 bt_app_send_bt_msg_to_playback(BT_APP_MSG_T *pt_bt_msg);
//extern INT32 bt_insert_ko_and_start_blueangel(VOID);
extern BOOL  bt_app_in_playing_mode(VOID);
extern INT32 bt_app_enter_connecting_mode(VOID);
extern INT32 bt_app_start_bluetooth(BT_APP_MODE_E e_mode);
extern INT32 bt_app_stop_bluetooth();
extern INT32 bt_app_connect(CHAR *ps_bt_mac);
extern INT32 bt_app_disconnect_with_src_dev(VOID);
extern INT32 bt_app_disconnect_with_sink_dev(VOID);
extern INT32 bt_app_connect_with_sink_dev(BOOL b_auto_connection, BT_TARGET_DEV_INFO* pt_target_device);

extern INT32 bt_app_function_key_stt_nfy(BOOL bEnable);

extern VOID  bt_app_notify_input_a2dp_connect_to_x2(VOID);
extern VOID  bt_app_notify_input_a2dp_disconnect_to_x2(VOID);
extern VOID  bt_app_notify_input_a2dp_avrcp_connect_to_x2(VOID);

// bluetooth audio output
extern VOID bt_app_notify_output_a2dp_connect_to_x2(VOID);
extern VOID bt_app_notify_output_a2dp_disconnect_to_x2(VOID);

//NFC
extern VOID bt_app_notify_nfc_detected_to_x2(VOID);

//Bluetooth key: PAIRING/CONNECTION KEY
extern VOID bt_app_notify_bt_cmd_key_to_x2(UINT8 u1_bt_cmd);


extern BOOL  bt_app_wait_x2_start_playback(VOID);

extern UINT16 bluetooth_get_dbg_level(VOID);
extern VOID   bluetooth_set_dbg_level(UINT16 ui2_db_level);
//extern VOID   bluetooth_cli_attach_cmd_tbl(VOID);
extern VOID bluetooth_absolute_volume_cmd_cbk(UINT16 flag, UINT8 *bt_absolute_volume, void* pv_tag);
extern VOID bluetooth_avrcp_cmd_cbk(BT_AVRCP_CMD_TYPE bt_cmd_type, UINT8 press, void* pv_tag);

// For sink device list
extern INT32 bt_app_start_sink_device_list(BT_DEVICE_LIST_TYPE_E list_type);
extern INT32 bt_app_close_sink_device_list();

extern INT32 bt_app_system_key_proc();

extern INT32 bt_app_audio_output_dev_list_start(VOID);
extern ErrorCode bluetooth_pbk_audio_input_start(bluetoothAudioInputMode mode, UINT32 tosec);
extern ErrorCode bluetooth_pbk_audio_input_stop(VOID);
extern INT32 bluetooth_audio_input_mode_get(bluetoothAudioInputMode* mode, UINT32* tosec);
extern ErrorCode bluetooth_audio_output_device_list_start(void);
extern ErrorCode bluetooth_audio_output_device_list_close(void);
extern BOOL bluetooth_iplib_get_fw_version(char* version);
extern BOOL bluetooth_iplib_get_hw_version(char* version);
extern BOOL bluetooth_iplib_get_name(char* name);
extern BOOL bluetooth_iplib_get_model(char* model);
extern ErrorCode bluetooth_audio_output_connect_start(void);
extern VOID  bt_msg_brdcast(BT_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);
extern INT32 bt_app_amp_volume_changed_proc(VOID);

#endif
#endif
//--------------------------------------------------------------------

