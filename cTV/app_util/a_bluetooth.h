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
 * $RCSfile: a_bluetooth.h,v $
 * $Revision: #7 $
 * $Date: 2016/01/05 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_BLUETOOTH_SUPPORT

#ifndef _A_BLUETOOTH_H_
#define _A_BLUETOOTH_H_

#ifdef __cplusplus              /* __cplusplus */
extern "C" {
#endif                          /* __cplusplus */
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
//#include "u_common.h"

#include <u_bt_mw_a2dp.h>
#include <u_bt_mw_gap.h>
#include <u_bt_mw_gatt.h>

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/* Return Values */
#define BTR_OK                                              ((INT32) 0)
#define BTR_FAIL                                            ((INT32)-1)
#define BTR_INV_ARG                                         ((INT32)-2)

#define BT_APPR_OK                          ((INT32)0)
#define BT_APPR_FAIL                        ((INT32)-1)
#define BT_APPR_INV_ARG                     ((INT32)-2)
#define BT_APPR_TX_AUTO_CONNECTION_FAIL     ((INT32)-3)

#define BT_APP_PAIRED_SINK_DEV_MAX      (32)  //The registered devices are displayed in the list, max:32
#define BT_APP_TOTAL_SINK_DEV_MAX       (128) //The max of sum of registered and detected devices is 128

#define BT_APP_NAME_LEN_MAX   MAX_NAME_LEN
#define BT_APP_BTADDR_LEN_MAX MAX_BDADDR_LEN
#define MAX_DEV_NUM (9)

/**
 * @brief This enum lists all network notify id.
 */

// ======================= old define ===================
typedef struct _BT_TARGET_DEV_INFO
{
    UINT8              fg_istv;/*target device is TV or not*/
    UINT32             u4delay_value;/*target device is TV or not*/
    CHAR               bdAddr[MAX_BDADDR_LEN];/* Bluetooth Address */
    CHAR               name[MAX_NAME_LEN];/* Name of device */
    UINT32  cod;                         // Class of Device
    UINT32  device_type;
}BT_TARGET_DEV_INFO;

typedef struct _BT_TARGET_DEV_LIST
{
    UINT32             head_idx;
    UINT32             dev_num;
    BT_TARGET_DEV_INFO device_list[9];
}BT_TARGET_DEV_LIST;

typedef struct _BT_HID_TARGET_DEV_LIST
{
    UINT32             head_idx;
    UINT32             dev_num;
    BT_TARGET_DEV_INFO device_list[9];
}BT_HID_TARGET_DEV_LIST;

typedef enum _BT_AUDIO_CODEC_TYPE
{
    BT_AUDIO_SBC    = 0x01,
    BT_AUDIO_AAC    = 0x02,
    BT_AUDIO_LDAC   = 0x04,
    BT_AUDIO_UNKONW = 0x10
}BT_AUDIO_CODEC_TYPE;

typedef enum
{
    BT_PAIRED_STATUS = 0,
    BT_CONNECTED_STATUS = 1,
}BT_STATUS;

typedef struct _BT_HID_STATUS_STRUCT
{
    BT_STATUS          status;
    CHAR               bdAddr[MAX_BDADDR_LEN];
}BT_HID_STATUS_STRUCT;

typedef struct _BT_HID_STATUS_STRUCT_LIST
{
    UINT32             head_idx;
    UINT32             dev_num;
    BT_HID_STATUS_STRUCT device_list[9];
}BT_HID_STATUS_STRUCT_LIST;

typedef struct
{
    INT32             conn_id;
    BT_GATT_SRVC_ID_T srvc_id;
} BT_GATTC_SEARCH_RST_T;


typedef struct
{
    INT32             conn_id;
    INT32             char_prop;
    BT_GATT_SRVC_ID_T srvc_id;
    BT_GATT_ID_T      char_id;
} BT_GATTC_GET_CHAR_RST_T;

typedef struct
{
    INT32                conn_id;
    BT_GATT_SRVC_ID_T    srvc_id;
    BT_GATT_ID_T         char_id;
    BT_GATT_ID_T         descr_id;
} BT_GATTC_GET_DESCR_RST_T;


// ======================= old define ===================


typedef enum _BT_NFY_ID_T
{
    BT_NFY_ID_UNKNOWN = 0,              /**< Unknowne message */

    BT_NFY_ID_SCAN_FINISH,              /**< Scan result notification \ref NotifyMsg "message" */
    BT_NFY_ID_CONNECT_SUCCESS,          /**< Scan result notification \ref NotifyMsg "message" */
    BT_NFY_ID_CONNECT_FAIL,             /**< Scan result notification \ref NotifyMsg "message" */
    BT_NFY_ID_DISCONNECT_SUCCESS,       /**< Scan result notification \ref NotifyMsg "message" */
    BT_NFY_ID_DISCONNECT_FAIL,          /**< Scan result notification \ref NotifyMsg "message" */
    BT_NFY_ID_AVPCP_GET_META_DATA_OK,    /**< avpcp get meta data  \ref NotifyMsg "message" */
    BT_NFY_ID_AVPCP_GET_PLAY_STATUS_OK, /**< avpcp get play status  \ref NotifyMsg "message" */
    BT_NFY_ID_PAIRING_KEY,
    BT_NFY_ID_A2DP_SNK_DEVICE = 9,
    BT_NFY_ID_GAP_STATE_ON =10,
    BT_NFY_ID_GAP_STATE_OFF=11,
    BT_NFY_ID_GAP_STATE_ACL_CONNECTED =12,
    BT_NFY_ID_GAP_STATE_ACL_DISCONNECTED=13,
    BT_NFY_ID_GAP_STATE_BONDED=14,
    BT_NFY_ID_GAP_STATE_BONDING=15,
    BT_NFY_ID_GAP_STATE_NO_BOND=16, /* pair fail */
    BT_NFY_ID_GAP_STATE_UNPAIR_SUCCESS=17, /* unpair success */
    BT_NFY_ID_GAP_STATE_DISCOVERY_STARTED=18,
    BT_NFY_ID_GAP_STATE_DISCOVERY_STOPED=19,

    BT_NFY_ID_LAST_ENTRY                /**< Only for count*/

}BT_NFY_ID_T;

typedef VOID (*bt_nfy_fct)(VOID* pv_tag, BT_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);

typedef struct _BT_MW_UTIL_NFY_CLIENT_T
{
    bt_nfy_fct               pf_notify;
    VOID*                    pv_tag;
    UINT32                   ui4_nfy_id;
} BT_MW_UTIL_NFY_CLIENT_T;

typedef struct
{
    BT_NFY_ID_T    e_msg_id;       /**< The message ID. */
    VOID*          pv_nfy_param;    /**< Message specific data. */
} BT_MW_UTIL_MSG_T;

/**
 * @brief This enum lists all Wifi states.
 */
typedef enum _BT_STATUS_T
{
    BT_UNPLUG,          /** BT dongle not plug */
    BT_PLUG             /** BT dongle plug */
}BT_STATUS_T;

typedef enum _BT_DEVICE_LIST_TYPE
{
    BT_DEVICE_LIST_TYPE_SINK,
    BT_DEVICE_LIST_TYPE_AUDIO_OUTPUT
}BT_DEVICE_LIST_TYPE_E;

/* Refer to BD_LAYER CODE_vxx.xlsx */
typedef enum _BT_APP_DATA_SYNC_BT_CMD_E{
    BT_APP_DVD_CMD_BT_MODE,
    BT_APP_DVD_CMD_BT_STANDBY,
    BT_APP_DVD_CMD_BT_AAC,
    BT_APP_DVD_CMD_BT_LDAC,
    BT_APP_DVD_CMD_BT_TX_QOS,
    BT_APP_DVD_CMD_BT_SCAN,
    BT_APP_DVD_CMD_BT_TX_DEV_LIST,
    BT_APP_DVD_CMD_BT_RX_A2DP_CONNECT_DISCONNECT,
    BT_APP_DVD_CMD_BT_TX_A2DP_CONNECT_DISCONNECT,
    BT_APP_DVD_CMD_BT_MAX
}BT_APP_DATA_SYNC_BT_CMD_E;

// RSSI: Received Signal Strength Indication
// RSSI of remote device is mapped to 5 levels.
#define BT_APP_RSSI_LEVEL_NUM 5
typedef enum _BT_APP_RSSI_LEVEL
{
    BT_RSSI_LEVEL_0 = 0,
    BT_RSSI_LEVEL_1,
    BT_RSSI_LEVEL_2,
    BT_RSSI_LEVEL_3,
    BT_RSSI_LEVEL_4,
    BT_RSSI_LEVEL_5
}BT_APP_RSSI_LEVEL_E;

typedef enum _BT_APP_REMOTE_DEVICE_STATUS   // the status of remote device
{
    BT_APP_REMOTE_DEVICE_STATUS_UNPAIRED = 0,  // unpaired
    BT_APP_REMOTE_DEVICE_STATUS_PAIRED,        // paired
    BT_APP_REMOTE_DEVICE_STATUS_CONNECTED,     // connected
}BT_APP_REMOTE_DEV_STATUS_E;
typedef enum _BT_APP_SET_DONGLE_MODE   // the status of remote device
{
    BT_APP_SET_DONGLE_MODE_WAKEUP = 0,  // WAKEUP
    BT_APP_SET_DONGLE_MODE_SUSPEND,     // SUSPEND
    BT_APP_SET_DONGLE_MODE_INVALID,
}BT_APP_SET_DONGLE_MODE_E;

typedef struct _BT_APP_DEVICE_INFO_T    // the structure for bluetooth device info
{
    CHAR    ac_name[BT_APP_NAME_LEN_MAX];    // Device name
    CHAR    ac_addr[BT_APP_BTADDR_LEN_MAX];  // Bluetooth Address (MAC)
    UINT32  ui4_cod;                         // Class of Device
    UINT32  ui4_service;                     // Service supported
    BT_APP_REMOTE_DEV_STATUS_E e_status;     // Status (connected, paired, unpaired)
    BT_APP_RSSI_LEVEL_E        e_rssi_level; // RSSI Level
}BT_APP_DEVICE_INFO_T;

typedef struct{
    UINT8                   u1_total_dev_num;           //total sink device number, including paired and unpaired
    UINT8                   u1_paired_dev_num;          //paired device number
    UINT8                   u1_unpaired_dev_num;        //unpaired device number
    UINT8                   u1_first_dev_index;         //device which is displayed in the first row
    UINT8                   u1_focus_row_index;         //which row is focused, 0xFF means focus on scaning icon
    BOOL                    b_scrollbar_shown;          //flag indicate is it need to show scrollbar
    UINT8                   u1_paired_dev_scanned_num;  // indicate how many paired devices are scanned in one scaning circle
    UINT8                   au1_paired_dev_scan_status[BT_APP_PAIRED_SINK_DEV_MAX]; //store every paired sink device scanning status in one scanning circle, 1 for scanned, 0 for not scanned
    BT_APP_DEVICE_INFO_T    sink_dev_list[BT_APP_TOTAL_SINK_DEV_MAX];   //store all sink devices, including Connected,Paired,Not paired
} BT_APP_SINK_DEV_LIST_INFO_T;

typedef enum _bluetoothAudioInputMode
{
    BLUETOOTH_AUDIO_INPUT_MODE_PAIRING,
    BLUETOOTH_AUDIO_INPUT_MODE_CONNECT,
    BLUETOOTH_AUDIO_INPUT_MODE_PLAY,
    BLUETOOTH_AUDIO_INPUT_MODE_CLOSED
}bluetoothAudioInputMode;

typedef enum
{
    TV_VOLUME_TYPE_UP = 0,
    TV_VOLUME_TYPE_DOWN

}TVVolType;


/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32  a_bt_init(VOID);
extern BOOL   a_bt_app_has_init(VOID);
extern BOOL   a_bt_check_bt_device(VOID);
extern INT32  a_bt_register(bt_nfy_fct pf_nfy, VOID* pv_tag, UINT32* pui4_nfy_id);
extern INT32  a_bt_unregister(UINT32 ui4_nfy_id);
extern INT32  a_bt_status(BT_STATUS_T* pe_bt_status );
extern INT32  a_bt_app_start_sink_device_list(BT_DEVICE_LIST_TYPE_E list_type);
extern INT32  a_bt_app_connect_with_sink_dev(BOOL b_auto_connection, BT_TARGET_DEV_INFO* pt_target_device);
extern INT32  a_bt_app_disconnect_with_sink_dev(VOID);
extern INT32 a_bt_app_connect_with_hid_dev(char* bt_mac);
extern INT32 a_bt_app_disconnect_with_hid_dev(char* bt_mac);
extern VOID  a_bt_app_stop_scaning(void);
extern BOOL  a_bluetooth_driver_init_done(VOID);
extern INT32  a_bt_app_on_off_proc(VOID);
extern VOID   a_bt_app_set_poweron_sequence_finish(BOOL b_finish);
extern BOOL   a_bt_app_is_poweron_sequence_finish(VOID);
extern VOID   a_bt_app_set_system_power_state(BOOL b_poweron);
extern BOOL   a_bt_app_is_system_power_on(VOID);
extern INT32  a_bt_req_bt_enable_disable(BOOL b_enable);
extern INT32  a_bt_enable_disable(BOOL b_enable);
extern BOOL   a_bt_is_bluetooth_enabled(VOID);
extern BOOL   a_bt_is_bt_standby_enable(VOID);
extern VOID   a_bt_setup_bt_standby(BOOL b_register_save);
extern BOOL   a_bt_power_setting_is_on(VOID);
extern VOID   a_bt_disable_bt_in_network_playback(BOOL b_disable_bt);
extern VOID   a_bt_enable_disable_recovery(BOOL b_sync);
extern VOID   a_bt_bluetooth_mode_set(UINT8 u1_bt_mode);
extern UINT8  a_bt_bluetooth_mode_get(VOID);
extern INT32  a_bt_send_bt_setting_mode_chg_nfy(UINT8 bt_mode_cfg);
extern INT32  a_bt_send_bt_tx_device_list_req(UINT8 u1_bt_snk_dev_index);
extern INT32  a_bt_send_data_sync_ifcon_bt_cmd_nfy(BT_APP_DATA_SYNC_BT_CMD_E e_bt_cmd_type, UINT8 u1_data);
extern INT32  a_bt_system_bootup_sequence_init(VOID);
extern INT32  a_bt_power_off_post_proc(VOID);
extern INT32  a_bt_system_power_on_proc(VOID);
extern INT32  a_bt_system_power_off_proc(VOID);
extern INT32  a_bt_set_aac_enable(UINT8 u1_aac_cfg);
extern INT32  a_bt_set_ldac_enable(UINT8 u1_ldac_cfg);
extern INT32  a_bt_set_transmitter_quality(UINT8 u1_qua_cfg);
extern INT32  a_bt_app_send_local_name_req(CHAR* pc_name);
extern INT32  a_bt_app_set_local_device_name(CHAR* pc_name);

extern UINT32 a_bt_app_get_paired_src_device_num(VOID);
extern UINT32 a_bt_app_get_paired_sink_device_num(VOID);

extern INT32  a_bt_app_src_paired_device_remove(CHAR* pc_addr);
extern INT32  a_bt_app_src_paired_device_remove_all(VOID);

extern INT32  a_bt_app_save_bluetooth_data(VOID);
extern INT32  a_bt_app_clear_bluetooth_data(VOID);
extern INT32  a_bt_app_clear_wireless_controller_data(VOID);

extern INT32  a_bt_set_media_information(VOID);

extern INT32  a_bt_app_get_paired_device_list(BT_TARGET_DEV_LIST *pt_device_list);
extern INT32  a_bt_app_get_target_device_name(CHAR *pc_device_name, UINT32 ui4_len);

extern VOID   a_bt_app_ui_sink_dev_list_data_update(BOOL b_update_data);
extern BOOL   a_bt_app_ui_bt_sink_dev_list_info_get(BT_APP_SINK_DEV_LIST_INFO_T* pr_sink_list_info);
extern INT32  a_bt_app_ui_sink_device_list_get_focused_device(BT_TARGET_DEV_INFO *pt_device);
extern INT32  a_bt_app_ui_bt_sink_dev_list_set_focus(UINT8 ui1_focus_idx);
extern INT32 a_bluetooth_pbk_audio_input_start(bluetoothAudioInputMode mode, UINT32 tosec);
extern INT32 a_bt_app_send_req_to_get_meta_data(VOID);
extern INT32 a_bt_app_send_req_to_get_playstatus(VOID);
extern VOID a_bt_app_ui_sink_dev_list_info_print(VOID);
extern BOOL a_bt_app_output_a2dp_connected(VOID);
extern BOOL a_bt_app_keyboard_mouse_connected(VOID);
extern INT32 a_bt_app_sink_paired_device_remove_all(VOID);
extern INT32 a_bt_app_sink_paired_device_remove(CHAR* pc_addr);
extern INT32 bluetooth_hid_remove_one(CHAR* addr);
extern INT32 bluetooth_hid_remove_all(VOID);
extern INT32 bt_app_get_cur_connect_status(CHAR *addr, BT_A2DP_ROLE *local_role, BOOL *status);

#ifdef APP_BLE_SUPPORT
extern INT32  a_bt_app_set_suspend_mode(BT_APP_SET_DONGLE_MODE_E e_bt_set_mode);
#endif
extern INT32 a_bt_pre_suspend_exit(VOID);
extern INT32 a_bt_app_write_pin_code(CHAR *remote_bd_addr, pairing_key_value_t pin, int len);


#ifdef __cplusplus              /* __cplusplus */
}
#endif                          /* __cplusplus */

#endif /* _A_BLUETOOTH_H_ */

#endif /* APP_BLUETOOTH_SUPPORT */

