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
 * $RCSfile: bluetooth.c,v $
 * $Revision: #12 $
 * $Date: 2016/01/05 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file implements the API of bluetooth.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

/*-----------------------------------------------------------------------------
                        include files
-----------------------------------------------------------------------------*/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "c_dbg.h"
#include "c_os.h"

#include "c_fm.h"
#include "c_dm.h"

#include "a_cfg.h"
#include "a_tv.h"

#include "bluetooth.h"
#include "bluetooth_msgproc.h"
#include "bluetooth_spp.h"
#include "bluetooth_device.h"
#include "bluetooth_device_list.h"
#include "bluetooth_timer.h"
#include "bluetooth_global_variables.h"
#include "bluetooth_hid.h"

#include "bluetooth_gatt/bluetooth_gattc.h"

#include "rmv_dev/a_rmv_dev.h"

#include "agent/agent.h"
#include <string.h>

#include "mtk_bt_service_gap_wrapper.h"
#include "mtk_bt_service_hidh_wrapper.h"
#include "mtk_bt_service_a2dp_wrapper.h"
#include "mtk_bt_service_avrcp_wrapper.h"
#include "mtk_bt_service_spp_wrapper.h"
#include "u_bt_mw_common.h"
#include "u_bt_mw_spp.h"



#define BT_FILE_VAR_PATH   LINUX_TMP_PATH"/bluetooth/"

// The command to insert Bluetooth KO
#define BLUETOOTH_INSTALL_KO_CMD  "sh "LINUX_ETC_PATH"/bluetooth.script/bluetooth_load_driver.sh"

// The command to enable wake on bluetooth
#define BLUETOOTH_WOW_OFF_ENABLE_WOBT_CMD  "sh "LINUX_ETC_PATH"/bluetooth.script/mtk_enable_wobt.sh WOW_OFF"
#define BLUETOOTH_WOW_ON_ENABLE_WOBT_CMD  "sh "LINUX_ETC_PATH"/bluetooth.script/mtk_enable_wobt.sh WOW_ON"

//BT init thread
#define BLUETOOTH_INIT_THREAD_NAME            "bluetooth_init"
#define BLUETOOTH_INIT_STACK_SIZE             (1024 * 32)
#define BLUETOOTH_INIT_THREAD_PRIORITY        ((UINT8) 200)
//static HANDLE_T h_bluetooth_init_thread = NULL_HANDLE;

typedef VOID (*bluetooth_audio_input_a2dp_connected_cbk_fct)(VOID);
typedef VOID (*bluetooth_audio_input_a2dp_disconnected_cbk_fct)(VOID);
typedef VOID (*bluetooth_audio_output_a2dp_connected_cbk_fct)(CHAR* pv_tag);
typedef VOID (*bluetooth_audio_output_a2dp_disconnected_cbk_fct)(CHAR* pv_tag);
typedef VOID (*bluetooth_audio_input_a2dp_avrcp_connected_cbk_fct)(VOID);

typedef VOID (*nfc_detected_cbk_fct)(VOID);
typedef VOID (*mtkstub_bluetooth_command_cbk_fct)(UINT8 u1_tag);

// pf_input_a2dp_connected_cbk_fct is callback to notify the event of receiving audio input A2DP connection
static bluetooth_audio_input_a2dp_connected_cbk_fct pf_input_a2dp_connected_cbk_fct = NULL;

// pf_input_a2dp_disconnected_cbk_fct is callback to notify the event of receiving audio input A2DP disconnection
static bluetooth_audio_input_a2dp_disconnected_cbk_fct pf_input_a2dp_disconnected_cbk_fct = NULL;

// pf_output_a2dp_connected_cbk_fct is callback to notify the event of receiving audio output A2DP connection
static bluetooth_audio_output_a2dp_connected_cbk_fct pf_output_a2dp_connected_cbk_fct = NULL;

// pf_output_a2dp_disconnected_cbk_fct is callback to notify the event of receiving audio output A2DP disconnection
static bluetooth_audio_output_a2dp_disconnected_cbk_fct pf_output_a2dp_disconnected_cbk_fct = NULL;

// pf_input_a2dp_avrcp_connected_cbk_fct is callback to notify the event that both Input A2DP and AVRCP are established
static bluetooth_audio_input_a2dp_avrcp_connected_cbk_fct pf_input_a2dp_avrcp_connected_cbk_fct = NULL;

// pf_nfc_detected_cbk_fct is callback to notify the event of NFC touch
static nfc_detected_cbk_fct pf_nfc_detected_cbk_fct = NULL;

// pf_bt_cmd_cbk_fct is callback to notify the event that PAIRING key or CONNECT key is pressed
static mtkstub_bluetooth_command_cbk_fct pf_bt_cmd_cbk_fct = NULL;

// This flag to specifies BT APP has been initialized or not.
static BOOL fg_bt_app_has_init = FALSE;

// The flag to specifies bluetooth is enabled or disabled
static BOOL fg_bt_app_bluetooth_enable = FALSE;

// This flag to specifies BT APP has processed power on event or not
static BOOL fg_bt_poweron_sequence_finish = FALSE;

// This flag to specifies system is power on or power off state
static BOOL fg_system_power_state = FALSE;

//bluetooth mode(internally value, not setting value): transmitter, receiver, off, here initialized 255 as invalid value
static UINT8 u1_bluetooth_mode = 255;

// Time out second for Pairing mode, The default value is 300 second.
// If _gui4_pairing_mode_timeout != 0, XMB is displayed after time-out in PAIRING mode
// If _gui4_pairing_mode_timeout == 0, time-out doesn't happen.
static UINT32 _gui4_pairing_mode_tout_sec = 300;

// Save connected a2dp device name
char ac_output_a2dp_target_name[MAX_NAME_LEN] = {0};


//extern char ac_connect_target_uuid[SPP_UUID_LENGTH];

static BT_MW_UTIL_NFY_CLIENT_T t_g_bt_nfy[BT_MAX_NUM_NOTIFY_CLIENT] = {{0}};
static BT_STATUS_T             t_g_bt_status = BT_UNPLUG;

static RMV_DEV_NFY_ID_T        e_g_bt_nfy_id = RMV_DEV_NFY_ID_UNKNOWN;
static pairing_key_value_t bt_pairing_key_value;
static UINT16  ui2_acfg_gl_nfy=0;
static UINT16               ui2_vol_id = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL);
static INT16   i2_volume=0;

extern INT32 x_thread_create(HANDLE_T    *ph_th_hdl,         /* thread handle */
            const CHAR  *ps_name,
            SIZE_T       z_stacksize,
            UINT8        ui1_pri,           /* thread priority */
            x_os_thread_main_fct pf_main,   /* thread's main function */
            SIZE_T       z_arg_size,
            VOID         *pv_arg);

extern VOID _bt_app_a2dp_snk_inquiry_response_cbk_fct(tBTMW_GAP_DEVICE_INFO* pt_result, void* pv_tag);


VOID  bt_msg_brdcast(BT_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    BT_MW_UTIL_NFY_CLIENT_T*        pt_bt_nfy    = t_g_bt_nfy;
    BT_MW_UTIL_NFY_CLIENT_T*        pt_client    = NULL;
    UINT16                          ui2_i     = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));
    BT_APP_LOG_DEFAULT(("<BT_APP> Brdcast the msg  -> %d\n", e_nfy_id));
    bt_app_sema_lock();
    /* Collect all notify clients in to sort structure. */
    for (ui2_i = 0;
         ui2_i < (UINT16)BT_MAX_NUM_NOTIFY_CLIENT;
         ui2_i ++)
    {
        /* Load the client/ */
        pt_client =  &(pt_bt_nfy[ui2_i]);

        /* Check match the group. */
        if (pt_client->pf_notify == NULL)
        {
            continue;
        }

        BT_APP_LOG_DEFAULT(("<BT_APP> %s, pf_notify\n", __FUNCTION__));

        pt_client->pf_notify(pt_client->pv_tag, e_nfy_id, pv_nfy_param);
    }
    bt_app_sema_unlock();

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));

    return;
}

/**-----------------------------------------------------------------------------
  * Name          - _bt_check_bt_device
  *
  * Description  - Check whether bluetooth dongle exist or not.
  *
  * Returns       - TRUE: Bluetooth dongle exists, FLASE: Bluetooth dongle doesn't exist.
  *
  *---------------------------------------------------------------------------*/
BOOL _bt_check_bt_device(VOID)
{
#if 1
    INT32 i4_ret = 0;

    DM_COND_T       t_dev_spec;
    DM_DEV_FILTR_T  t_filtr;
    DM_DEV_STAT_T   t_stat[1];
    UINT32          ui4_dev_ns = 1;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));
    BT_APP_LOG_DEFAULT(("<BT_APP> Check BT dongle\n"));

    t_dev_spec.t_hw_type = DM_HW_TYPE_USB;
    t_dev_spec.t_dev_type = DM_DEV_MISC_TYPE_USB_WIRELESS_SUBWOOFER;
    t_filtr.pt_dev_filtr = &t_dev_spec;
    t_filtr.ui4_dev_filtr_ns = 1;

    i4_ret = c_dm_get_devices(&t_filtr, t_stat, &ui4_dev_ns);

    if((i4_ret == 0) && (ui4_dev_ns != 0))
    {
        t_g_bt_status = BT_PLUG;
        return TRUE;
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: Not found BT dongle, %d, %d\n", i4_ret, ui4_dev_ns));
        t_g_bt_status = BT_UNPLUG;
        return FALSE;
    }
#endif
    return TRUE;
}

/**-----------------------------------------------------------------------------
  * Name          - _bt_send_bt_dongle_attach_nfy
  *
  * Description  - Notify the event that bluetooth dongle is attached
  *
  * Inputs        -
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 _bt_send_bt_dongle_attach_remove_nfy(BT_STATUS_T status)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));
    BT_APP_LOG_DEFAULT(("<BT_APP> Notify: bluetooth dongle is attached\n"));

    t_bt_msg.msg_type = BT_APP_MSG_NFY_BT_DONGLE_ATTACH;
    t_bt_msg.ui4_msg_id = status;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send BT_APP_MSG_NFY_BT_DONGLE_ATTACH fail, %d\n", i4_ret));
    }

    return i4_ret;
}

#if 1
static VOID _bt_dev_notify_fct(
    VOID*                   pv_tag,
    RMV_DEV_NFY_ID_T        e_nfy_id,
    VOID*                   pv_nfy_param)
{
    INT32                  i4_ret;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, e_nfy_id: %d\n", __FUNCTION__, e_nfy_id));

    if (REV_DEV_NFY_ID_WIRELESS_SUBWOOFER_INSERT == e_nfy_id)
    {
        i4_ret = _bt_send_bt_dongle_attach_remove_nfy(BT_PLUG);

        if (i4_ret != PBR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: _bt_send_bt_dongle_attach_nfy fail, %d\n", i4_ret));
        }
    }
    else if (REV_DEV_NFY_ID_WIRELESS_SUBWOOFER_REMOVED== e_nfy_id)
    {
        i4_ret = _bt_send_bt_dongle_attach_remove_nfy(BT_UNPLUG);

        if (i4_ret != PBR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: _bt_send_bt_dongle_attach_nfy fail, %d\n", i4_ret));
        }
    }

    return;
}
#endif

ErrorCode bluetooth_pbk_audio_input_start(bluetoothAudioInputMode mode, UINT32 tosec)
{
    INT32 i4_ret = ERRORCODE_OK;
    BT_APP_MODE_E e_bt_mode = BT_APP_MODE_PAIRING;
    BT_APP_MSG_T t_bt_msg = {0};
    UINT8   u1_count = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> bluetooth_pbk_audio_input_start is called, %d, %d\n", mode, tosec));

    // Check if bluetooth dongle exist or not.
    while (!_bt_check_bt_device())
    {
        c_thread_delay(200);
        u1_count++;

        BT_APP_LOG_DEFAULT(("<BT_APP> Wait for bluetooth dongle attach...[%d]\n", u1_count));

        if (50 == u1_count)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: Exit %s : Dongle not attached\n", __FUNCTION__));

            return ERRORCODE_NORMAL_ERROR;
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Bluetooth device has been attached [%d]\n", u1_count));

    if (!a_bt_app_is_system_power_on())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: Exit %s : System is power off state.\n", __FUNCTION__));

        return ERRORCODE_NORMAL_ERROR;
    }

    switch (mode)
    {
        case BLUETOOTH_AUDIO_INPUT_MODE_PAIRING:
        {
            e_bt_mode = BT_APP_MODE_PAIRING;

            // Change Pairing mode time out second
            _gui4_pairing_mode_tout_sec = tosec;
            break;
        }
        case BLUETOOTH_AUDIO_INPUT_MODE_CONNECT:
        {
            e_bt_mode = BT_APP_MODE_CONNECT;
            break;
        }
        case BLUETOOTH_AUDIO_INPUT_MODE_PLAY:
        {
            e_bt_mode = BT_APP_MODE_PLAY;
            break;
        }
        default:
        {
            return ERRORCODE_INV_ARG;
        }
    }


    t_bt_msg.msg_type = BT_APP_MSG_REQ_START_BT_INPUT;
    t_bt_msg.ui4_msg_id = e_bt_mode;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));

    return i4_ret;
}

ErrorCode bluetooth_pbk_audio_input_stop(VOID)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    t_bt_msg.msg_type = BT_APP_MSG_REQ_STOP_BT_INPUT;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send warn hide msg fail, %d\n", i4_ret));
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));

    return i4_ret;
}

INT32 bluetooth_audio_input_mode_get(bluetoothAudioInputMode* mode, UINT32* tosec)
{
#if 0
    BT_MODE_TYPE e_mode;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s, line:%d\n",__FUNCTION__,__LINE__));

    if((NULL == mode) || (NULL == tosec))
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> get mode, invalid arg\n"));
        return PBR_INV_ARG;
    }

    e_mode = a_mtkapi_bt_gap_get_mode();
    switch(e_mode)
    {
        case BT_MODE_PAIRING:
        {
            *mode = BLUETOOTH_AUDIO_INPUT_MODE_PAIRING;
            *tosec = 0;
            break;
        }
        case BT_MODE_CONNECTING:
        {
            *mode = BLUETOOTH_AUDIO_INPUT_MODE_CONNECT;
            *tosec = 0;
            break;
        }
        case BT_MODE_PLAYING:
        {
            *mode = BLUETOOTH_AUDIO_INPUT_MODE_PLAY;
            *tosec = 0;
            break;
        }
        case BT_MODE_CLOSE:
        {
            *mode = BLUETOOTH_AUDIO_INPUT_MODE_CLOSED;
            *tosec = 0;
            break;
        }
        default:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP>ERR: Invalid mode, %d\n", e_mode));
            *mode = BLUETOOTH_AUDIO_INPUT_MODE_CLOSED;
            *tosec = 0;
            return PBR_FAIL;
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Bluetooth mode:%d, tosec:%d\n", *mode, *tosec));

#endif
    return PBR_OK;
}

BOOL bluetooth_audio_input_set_delay(UINT32 delay)
{
    if (delay > 0)
    {
        bt_app_set_flag_input_a2dp_connection_with_TV(TRUE);
    }
    else
    {
        bt_app_set_flag_input_a2dp_connection_with_TV(FALSE);
    }

#ifdef ADD_DELAY_BEFORE_PLAY
    c_btm_set_delay_value(delay);
#endif

    return TRUE;
}

#if 0
BOOL bluetooth_audio_control_remote_meta_data_event_cbk_reg(
    bluetooth_audio_control_remote_meta_data_event_cbk_fct fct)
{
    return TRUE;
}

BOOL bluetooth_audio_control_remote_meta_data_event_cbk_unreg(void)
{
    return TRUE;
}

UINT32 bluetooth_special_cmd_set(char* data)
{
    return TRUE;
}

ErrorCode bluetooth_special_data_set(bluetoothSpecialData_t data)
{
    return 0;
}

ErrorCode bluetooth_special_data_get(bluetoothSpecialData_t* data)
{
    return 0;
}

BOOL bluetooth_special_data_cbk_reg(mtkstub_bluetooth_special_data_cbk_fct fct)
{
    return TRUE;
}

BOOL bluetooth_special_data_cbk_unreg(void)
{
    return TRUE;
}

BOOL bluetooth_audio_input_a2dp_connected_cbk_reg(
    bluetooth_audio_input_a2dp_connected_cbk_fct fct)
{
    pf_input_a2dp_connected_cbk_fct = fct;

    return TRUE;
}

BOOL bluetooth_audio_input_a2dp_connected_cbk_unreg(void)
{
    pf_input_a2dp_connected_cbk_fct = NULL;

    return TRUE;
}

BOOL bluetooth_audio_input_a2dp_disconnected_cbk_reg(
    bluetooth_audio_input_a2dp_disconnected_cbk_fct fct)
{
    if (NULL != fct)
    {
        pf_input_a2dp_disconnected_cbk_fct = fct;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL bluetooth_audio_input_a2dp_disconnected_cbk_unreg(void)
{
    pf_input_a2dp_disconnected_cbk_fct = NULL;

    return TRUE;
}

BOOL bluetooth_audio_output_a2dp_connected_cbk_reg(
    bluetooth_audio_output_a2dp_connected_cbk_fct fct)
{
    if (NULL != fct)
    {
        pf_output_a2dp_connected_cbk_fct = fct;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL bluetooth_audio_output_a2dp_connected_cbk_unreg(void)
{
    pf_output_a2dp_connected_cbk_fct = NULL;

    return TRUE;
}

BOOL bluetooth_audio_output_a2dp_disconnected_cbk_reg(
    bluetooth_audio_output_a2dp_disconnected_cbk_fct fct)
{
    if (NULL != fct)
    {
        pf_output_a2dp_disconnected_cbk_fct = fct;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL bluetooth_audio_output_a2dp_disconnected_cbk_unreg(void)
{
    pf_output_a2dp_disconnected_cbk_fct = NULL;

    return TRUE;
}

BOOL nfc_detected_cbk_reg(nfc_detected_cbk_fct fct)
{
    if (NULL != fct)
    {
        pf_nfc_detected_cbk_fct = fct;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

BOOL nfc_detected_cbk_unreg()
{
    pf_nfc_detected_cbk_fct = NULL;

    return TRUE;
}

BOOL bluetooth_audio_input_a2dp_avrcp_connected_cbk_reg(
    bluetooth_audio_input_a2dp_avrcp_connected_cbk_fct fct)
{
    pf_input_a2dp_avrcp_connected_cbk_fct = fct;

    return TRUE;
}

BOOL bluetooth_audio_input_a2dp_avrcp_connected_cbk_unreg(void)
{
    pf_input_a2dp_avrcp_connected_cbk_fct = NULL;

    return TRUE;
}
#endif

/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_gap_event_cbk_fct
  *
  * Description  - callback this function to notify GAP event
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static VOID _bluetooth_gap_event_cbk_fct(tBTMW_GAP_STATE *msg_id, void* pv_tag)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    tBTMW_GAP_STATE *bt_msg_data = NULL;

    BT_APP_LOG_DEFAULT(("<BT_APP> %s receive GAP event: %d \n", __FUNCTION__, msg_id->state));

    // where to free the memory.
    bt_msg_data = (tBTMW_GAP_STATE *)c_mem_alloc(sizeof(tBTMW_GAP_STATE));
    if (NULL == bt_msg_data)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for gap event fail\n"));
        return ;
    }

    c_memcpy(bt_msg_data, msg_id, sizeof(tBTMW_GAP_STATE));

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_GAP_EVENT;
    t_bt_msg.ui4_data_size  = sizeof(tBTMW_GAP_STATE);
    t_bt_msg.pv_data = bt_msg_data;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send GAP event fail\n"));
    }

    return ;
}

#if 0
/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_play_state_chg_cbk_fct
  *
  * Description  - callback this function to notify the event of play state changed
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static VOID _bluetooth_play_state_chg_cbk_fct(BTPlayState bt_playstate, void* pv_tag)

{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> receive play state msg: %d \n", bt_playstate));

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_PLAY_STATE_CHGD;
    t_bt_msg.ui4_msg_id = bt_playstate;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send play status msg fail\n"));
    }

    return ;
}

/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_volume_chg_cbk_fct
  *
  * Description  - callback this function to notify the command to change volume
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static VOID _bluetooth_volume_chg_cbk_fct(BTVolType bt_volume, void* pv_tag)

{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_INFO(("<BT_APP> Receive volume chg msg: %d\n", bt_volume));

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_VOLUME_CHG;
    t_bt_msg.ui4_msg_id = bt_volume;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send volume msg fail\n"));
    }

    return ;
}

/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_track_chg_cbk_fct
  *
  * Description  - callback this function to notify the event of track changed
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static VOID _bluetooth_track_chg_cbk_fct(UINT32 bt_track_index, void* pv_tag)

{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> receive track chg msg, %d \n", bt_track_index));

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_TRACK_CHGD;
    t_bt_msg.ui4_msg_id = bt_track_index;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send track msg fail\n"));
    }

    return ;
}

/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_mediainfo_play_status_cbk
  *
  * Description  - callback this function to notify media info or play status have been ready
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static VOID _bluetooth_mediainfo_play_status_cbk(BTMediaPlayState bt_status, void* pv_tag)

{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> receive mediainfo or play status: %d\n", bt_status));

    switch (bt_status)
    {
        case BT_MEDIA_INFO_OK:  // Meta data has been ready in BTM
        {
            t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_META_DATA_OK;
            break;
        }
        case BT_PLAY_STATUS_OK: // Play status has been ready in BTM
        {
            t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_PLAY_STATUS_OK;
            break;
        }
        case BT_MEDIA_INFO_FAIL:  // get meta data fail, not use temporarily
        case BT_PLAY_STATUS_FAIL: // get play status fail, not use temporarily
        default :
        {
            break;
        }
    }

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send mediainfo msg fail\n"));
    }

    return ;
}

/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_spp_cbk
  *
  * Description  - MW callback this function to notify the event of SPP
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static VOID _bluetooth_spp_cbk(BT_SPP_CBK_STRUCT *pt_spp_struct, void* pv_tag)

{
#if 0
    INT32 i4_ret = PBR_OK;
    CHAR  *pc_uuid = NULL;
    BT_APP_MSG_T t_bt_msg = {0};
    BT_SPP_RECEIVED_DATA *pt_spp_data = NULL;

    if (NULL == pt_spp_struct)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, pt_spp_struct is NULL\n", __FUNCTION__));
        return ;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> receive SPP event, %d\n", pt_spp_struct->bt_spp_event_type));

    /* When event type is connect/disconnect fail, BTM don't notify with UUID */
    if (BT_SPP_CONNECT_FAIL == pt_spp_struct->bt_spp_event_type)
    {
        pt_spp_struct->uuid = ac_connect_target_uuid;
        pt_spp_struct->uuid_len = (UINT8)c_strlen(ac_connect_target_uuid);
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR:%s, spp connect fail, uuid:%s, length:%d\n", __FUNCTION__, pt_spp_struct->uuid, pt_spp_struct->uuid_len));
    }

    if (NULL == pt_spp_struct->uuid)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, uuid is NULL\n", __FUNCTION__));
        return ;
    }

    if(pt_spp_struct->uuid_len >= SPP_UUID_LENGTH)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: UUID is too long\n"));
        return ;
    }

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_SPP_EVENT;
    t_bt_msg.ui4_msg_id = pt_spp_struct->bt_spp_event_type;

    switch (pt_spp_struct->bt_spp_event_type)
    {
        case BT_SPP_RECV_DATA:   // the event of receiving SPP data
        {
            if(NULL == pt_spp_struct->spp_data)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: %s, no SPP data\n", __FUNCTION__));
                return ;
            }

            if(pt_spp_struct->spp_data_len > MAX_SPP_DATA_LENGTH_APP)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: SPP data len is too long\n"));
                return ;
            }

            pt_spp_data = (BT_SPP_RECEIVED_DATA *)c_mem_alloc(sizeof(BT_SPP_RECEIVED_DATA));
            if(NULL == pt_spp_data)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem to receive spp data fail\n"));
                return ;
            }
            c_memset(pt_spp_data, 0, sizeof(BT_SPP_RECEIVED_DATA));

            pt_spp_data->ui4_data_len = pt_spp_struct->spp_data_len;
            c_strncpy(pt_spp_data->ac_uuid, pt_spp_struct->uuid, pt_spp_struct->uuid_len);
            c_memcpy(pt_spp_data->aui1_data,
                     pt_spp_struct->spp_data,
                     pt_spp_struct->spp_data_len);

            t_bt_msg.ui4_data_size = sizeof(BT_SPP_RECEIVED_DATA);
            t_bt_msg.pv_data = pt_spp_data;

            break;
        }
        case BT_SPP_CONNECT:
        case BT_SPP_CONNECT_FAIL:
        case BT_SPP_DISCONNECT:
        case BT_SPP_DISCONNECT_FAIL:
        {
            pc_uuid = (CHAR *)c_mem_alloc(pt_spp_struct->uuid_len + 1);
            if(NULL == pc_uuid)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for uuid fail\n"));
                return ;
            }
            c_memset(pc_uuid, 0, pt_spp_struct->uuid_len + 1);

            c_strncpy(pc_uuid, pt_spp_struct->uuid, pt_spp_struct->uuid_len);

            t_bt_msg.ui4_data_size = pt_spp_struct->uuid_len + 1;
            t_bt_msg.pv_data = pc_uuid;

            break;
        }
        default:
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: invalid SPP event\n"));
            return ;
        }
    }

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send mediainfo msg fail\n"));
    }
#endif
    return ;
}
#if 0
/**-----------------------------------------------------------------------------------------
  * Name          - _bluetooth_init_thread
  *
  * Description  -
  *
  * Inputs         -
  *----------------------------------------------------------------------------------------*/
static VOID _bluetooth_init_thread(VOID *pv_arg)
{
    INT32   i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if(TRUE == bluetooth_driver_init_done())
    {
    	//c_thread_delay(10000);
        i4_ret = bluetooth_init();
        BT_APP_LOG_ON_FAIL(i4_ret);

        i4_ret = bluetooth_system_power_on_proc();
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, bluetooth_driver_init_done fail.\n",__FUNCTION__));
        i4_ret =  BT_APPR_FAIL;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return;
}
#endif

/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_absolute_volume_cmd_cbk
  *
  * Description  - MW callback this function to notify the event that SRC send absolute volume command.
  *
  * Inputs        -  arg[in] flag specify the event type
  *                     BT_GET_VOLUME : SRC want sink to response with current platform volume value in percentage.
  *                     BT_SEND_VOLUME: SRC set volume value percentage to sink, sink should change it according to the value.
  *
  *                     arg[in] bt_absolute_volume specify the volume percentage to be set when flag is BT_SEND_VOLUME.
  *
  * Returns       - arg[out] bt_absolute_volume is the sink volume in the format of percentage, effective only when flag is BT_GET_VOLUME.
  *------------------------------------------------------------------------------------------------------------------*/
VOID bluetooth_absolute_volume_cmd_cbk(UINT16 flag, UINT8 *bt_absolute_volume, void* pv_tag)

{
#if 0
    INT32 i4_ret = PBR_OK;
    IFCON_TA_ABSOLUTE_VOLUME_T r_absolute_volume = {0};
    UINT8 u1_avrcp_absolute_volume = 0;
    UINT8 u1_ifcon_absolute_volume = 0;
    T_IFCON_VOLUME_STATUS t_volume_info = {0};
    UINT8 u1_volume_diff_abs = 0;
    INT8 u1_volume_diff = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> %s : receive AVRCP v1.5 absolute volume command cbk, flag[%d], volume[%d]\n",__FUNCTION__,flag, *bt_absolute_volume));

    if (TRUE == a_acfg_get_flag_volume_info_nfy())
    {
        t_volume_info = a_acfg_get_platform_volume_info();
        u1_ifcon_absolute_volume = t_volume_info.u1_volume_value_percentage;
        BT_APP_LOG_DEFAULT(("<BT_APP> Get platform absolute volume value from IFCON notify data: %d%% [0~100%%]\n",u1_ifcon_absolute_volume));
    }
    else
    {
        i4_ret = d_ifcon_get_volume_info_directly(&t_volume_info);
        if (TRUE != i4_ret)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: d_ifcon_get_absolute_volume_directly fail\n"));
        }
        else
        {
            u1_ifcon_absolute_volume = t_volume_info.u1_volume_value_percentage;
            BT_APP_LOG_DEFAULT(("<BT_APP> Get platform absolute volume value from IFCON directly: %d%% [0~100%%]\n",u1_ifcon_absolute_volume));
        }
    }

    u1_avrcp_absolute_volume = u1_ifcon_absolute_volume * 127 / 100;

    BT_APP_LOG_DEFAULT(("<BT_APP> Map to AVRCP absolute volume value: %d [0~127]\n",u1_avrcp_absolute_volume));

    if (BT_GET_VOLUME == flag)
    {
        *bt_absolute_volume = u1_avrcp_absolute_volume;
    }
    else if (BT_SEND_VOLUME == flag)
    {
        if (bt_app_is_bluetooth_audio_function_start())
        {
            // add this countermeasuer for IOS bug, IOS(before IOS 8) sets absolute volume with 100% in first pairing
            u1_volume_diff = (*bt_absolute_volume) - u1_avrcp_absolute_volume;
            u1_volume_diff_abs = (u1_volume_diff >= 0) ? u1_volume_diff : (-u1_volume_diff);

            if (u1_volume_diff_abs > 127/4) //>25%
            {
                if (u1_volume_diff > 0)
                {
                    //volume up case
                    *bt_absolute_volume = u1_avrcp_absolute_volume + 127/4;
                }
            }

            // avrcp absolute volume value: 0 ~ 127, IFCON side: 0 ~ 100, need to map
            r_absolute_volume.demand = IFCON_TA_CMD_VOLUME_DEMAND_BT;
            r_absolute_volume.data   = (*bt_absolute_volume) * 100 / 127;

            d_ifcon_set_absolute_volume(r_absolute_volume);

            BT_APP_LOG_DEFAULT(("<BT_APP> Set AVRCP absolute volume value:%d, convert to IFCON absolute volume: %d%% [0~100%%]\n",*bt_absolute_volume, r_absolute_volume.data));
        }
        else
        {
            BT_APP_LOG_API(("<BT_APP> BT function is inactive, response AVRCP v1.5 absolute volume:%d [0~127]\n",u1_avrcp_absolute_volume));
            c_btm_set_volume(u1_avrcp_absolute_volume);
        }
    }

    return;

#endif

}

/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_avrcp_cmd_cbk
  *
  * Description  - MW callback this function to notify the event that SRC send avrcp command.
  *
  * Inputs        -  arg[in] bt_cmd_type specify avrcp command type
  *                     arg[in] press   1: press, 0: release
  *
  * Returns       -
  *------------------------------------------------------------------------------------------------------------------*/
VOID bluetooth_avrcp_cmd_cbk(BT_AVRCP_CMD_TYPE bt_cmd_type, UINT8 press, void* pv_tag)

{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> receive AVRCP command cbk, cmd_type:%d, state:%d\n",bt_cmd_type, press));

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_AVRCP_KEY_CMD;
    t_bt_msg.ui4_msg_id = bt_cmd_type;
    t_bt_msg.ui4_data1 = press;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send BT_APP_MSG_BTM_NFY_AVRCP_KEY_CMD msg fail\n"));
    }

    return;
}

/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_upload_info_cbk
  *
  * Description  - MW callback this function to notify upload info, APP need to set decode downsample
  *                    Source -> downsample
  *                    192K -> 96K, 176.4K -> 88.2K, 96K -> 96K, 88.2K -> 88.2K
  *
  * Inputs        -
  * Returns       -
  *------------------------------------------------------------------------------------------------------------------*/
    VOID bluetooth_upload_info_cbk(BT_A2DP_UPLOAD_INFO* pt_upload_info, BOOL fg_only_check_mute, void* pv_tag)

{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    BT_A2DP_UPLOAD_INFO* pt_bt_app_upload_info = NULL;

    BT_APP_LOG_DEFAULT(("<BT_APP> receive upload info cbk, fg_only_check_mute[%d], sample_freq[%d], channel_num[%d], fgNeedMuteACP[%d]\n",   \
        fg_only_check_mute, pt_upload_info->sample_freq, pt_upload_info->channel_num, pt_upload_info->fgNeedMuteACP));

    pt_bt_app_upload_info = (BT_A2DP_UPLOAD_INFO *)c_mem_alloc(sizeof(BT_A2DP_UPLOAD_INFO));
    if (NULL == pt_bt_app_upload_info)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for upload info fail\n"));
        return ;
    }

    c_memcpy(pt_bt_app_upload_info, pt_upload_info, sizeof(BT_A2DP_UPLOAD_INFO));

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_UPLOAD_INFO;
    t_bt_msg.ui4_msg_id = fg_only_check_mute;
    t_bt_msg.ui4_data_size  = sizeof(BT_A2DP_UPLOAD_INFO);
    t_bt_msg.pv_data = pt_bt_app_upload_info;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send BT_APP_MSG_BTM_NFY_UPLOAD_INFO msg fail\n"));
    }

    return;
}


/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_src_get_play_status_cbk
  *
  * Description  - MW callback this function to get play status in SRC mode
  *
  * Inputs        -
  * Returns       -
  *------------------------------------------------------------------------------------------------------------------*/
//extern VOID a_browser_get_playstatus(PB_PBC_STT_E *ePBCStt);
VOID bluetooth_src_get_play_status_cbk(BTPlayState *bt_playstatus, void* pv_tag)

{
    #if 0
    INT32 i4_ret = PBR_OK;
    PB_PBC_STT_INFO_T    t_pbc_state = {0};
    PB_PBC_STT_E    e_pbc_stt = 0;
    BTPlayState     e_bt_playstatus = BT_PLAY_STATE_MAX;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));

    if (a_browser_ex_is_active())
    {
        a_browser_get_playstatus(&t_pbc_state.ePBCStt);

        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s : Browser playback\n", __FUNCTION__));
    }

    e_pbc_stt = t_pbc_state.ePBCStt;

    switch (e_pbc_stt)
    {
        case PB_PBC_STT_STOP:
        case PB_PBC_STT_SWITCHING_DISC:
        case PB_PBC_STT_STOP_PARSE:
        case PB_PBC_STT_PREV_NEXT:
        case PB_PBC_STT_NOT_LAST_FIlE:
            e_bt_playstatus = BT_PLAY_STATE_STOP;
            break;

        case PB_PBC_STT_PLAY:
        case PB_PBC_STT_STEP:
        case PB_PBC_STT_FSPLAY:
            e_bt_playstatus = BT_PLAY_STATE_PLAY;
            break;

        case PB_PBC_STT_PAUSE:
            e_bt_playstatus = BT_PLAY_STATE_PAUSE;
            break;

        case PB_PBC_STT_FF:
        case PB_PBC_STT_SF:
            e_bt_playstatus = BT_PLAY_STATUS_FWD_SEEK;
            break;

        case PB_PBC_STT_FR:
        case PB_PBC_STT_SR:
            e_bt_playstatus = BT_PLAY_STATUS_REV_SEEK;
            break;

        default:
            e_bt_playstatus = BT_PLAY_STATE_STOP;
            break;
    }

    *bt_playstatus = e_bt_playstatus;

    BT_APP_LOG_DEFAULT(("<BT_APP> Map play status[%d] to BTPlayState[%d]\n",e_pbc_stt, e_bt_playstatus));

    return;
    #endif
}


/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_src_play_ctrl_cbk
  *
  * Description  - MW callback this function to ctrl src playback, because when sample rate convert, BTM will stop uploader and restart uploader
  *                     during uploader stop and start, audio will output from speaker, it is forbidden.
  *                     So BTM will callback this fct to pause play before stop uploader and start play after restart uploader.
  *
  *                     MW do reconfig > callback app to stop playback > MW stop uploader, uninit encoder > init encoder, start uploader > callback app to start playback
  *
  * Inputs        -
  * Returns       -
  *------------------------------------------------------------------------------------------------------------------*/
VOID bluetooth_src_play_ctrl_cbk(BTPlayState bt_playback_cmd, void* pv_tag)

{
    #if 0
    INT32 i4_ret = BT_APPR_OK;
    UINT8 ui1_high_category_code = 0;
    UINT8 ui1_low_category_code = 0;
    UINT8 ui1_key_code = 0;
    PB_PBC_STT_INFO_T    t_pbc_state = {0};
    PB_PBC_STT_E         e_PBCStt = 0;
    UINT8 u1_audio_output_setting = 0;

    if (a_browser_ex_is_active())
    {

        a_browser_get_playstatus(&t_pbc_state.ePBCStt);

        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s : Browser playback\n", __FUNCTION__));
    }

    e_PBCStt = t_pbc_state.ePBCStt;

    // get audio output setting
    a_cfg_get_audio_output(&u1_audio_output_setting);

    BT_APP_LOG_DEFAULT(("<BT_APP> receive src play ctrl cbk, current pbc stt:%d, ctrl play state:%d\n", e_PBCStt ,bt_playback_cmd));

    switch(bt_playback_cmd)
    {
        case BT_PLAY_STATE_PAUSE:
        {
            if (PB_PBC_STT_PAUSE == e_PBCStt
                || PB_PBC_STT_STOP == e_PBCStt)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> %s, Line:%d, current pbc stt:%d, return\n", __FUNCTION__, __LINE__, e_PBCStt));
            }
            else
            {
                bluetooth_avrcp_cmd_map_sircs_cmd(BT_AVRCP_CMD_TYPE_PAUSE, &ui1_high_category_code, &ui1_low_category_code, &ui1_key_code);

                d_ifcon_send_sircs_code(ui1_high_category_code, ui1_low_category_code, ui1_key_code, 165);
            }

            break;
        }
        case BT_PLAY_STATE_PLAY:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> %s, audio unmute\n", __FUNCTION__));

            // only when HDMI IN, need to unmute, due to input playback can't stop
            switch (u1_audio_output_setting)
            {
                case CFG_AUDIO_OUTPUT_SPK:
                    // unmute speaker
                    a_cfg_set_aud_adac_mute(FALSE);
                    break;
                case CFG_AUDIO_OUTPUT_HDMI:
                    // unmute HDMI
                    pb_set_avd_hdmi_mute_to_scc(FALSE);
                    break;
                case CFG_AUDIO_OUTPUT_SPK_HDMI:
                    // unmute speaker and hdmi
                    a_cfg_set_aud_adac_mute(FALSE);
                    pb_set_avd_hdmi_mute_to_scc(FALSE);
                    break;
                default:
                    break;
            }

            if (PB_PBC_STT_PLAY == e_PBCStt
                || PB_PBC_STT_FF == e_PBCStt
                || PB_PBC_STT_FR == e_PBCStt
                || PB_PBC_STT_SF == e_PBCStt
                || PB_PBC_STT_SR == e_PBCStt
                || PB_PBC_STT_STEP == e_PBCStt
                || PB_PBC_STT_FSPLAY == e_PBCStt)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> %s, Line:%d, current pbc stt:%d, return\n", __FUNCTION__, __LINE__, e_PBCStt));
            }
            else
            {
                bluetooth_avrcp_cmd_map_sircs_cmd(BT_AVRCP_CMD_TYPE_PLAY, &ui1_high_category_code, &ui1_low_category_code, &ui1_key_code);

                d_ifcon_send_sircs_code(ui1_high_category_code, ui1_low_category_code, ui1_key_code, 165);
            }

            break;
        }
        case BT_PLAY_STATE_STOP:
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> %s, audio mute\n", __FUNCTION__));

            // only when HDMI IN, need to mute, due to input playback can't stop
            switch (u1_audio_output_setting)
            {
                case CFG_AUDIO_OUTPUT_SPK:
                    // mute speaker
                    a_cfg_set_aud_adac_mute(TRUE);
                    break;
                case CFG_AUDIO_OUTPUT_HDMI:
                    // mute HDMI
                    pb_set_avd_hdmi_mute_to_scc(TRUE);
                    break;
                case CFG_AUDIO_OUTPUT_SPK_HDMI:
                    // mute speaker and hdmi
                    a_cfg_set_aud_adac_mute(TRUE);
                    pb_set_avd_hdmi_mute_to_scc(TRUE);
                    break;
                default:
                    break;
            }

            if (PB_PBC_STT_PAUSE == e_PBCStt
                || PB_PBC_STT_STOP == e_PBCStt)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> %s, Line:%d, current pbc stt:%d, return\n", __FUNCTION__, __LINE__, e_PBCStt));
            }
            else
            {
                bluetooth_avrcp_cmd_map_sircs_cmd(BT_AVRCP_CMD_TYPE_STOP, &ui1_high_category_code, &ui1_low_category_code, &ui1_key_code);

                d_ifcon_send_sircs_code(ui1_high_category_code, ui1_low_category_code, ui1_key_code, 165);
            }

            // delay 200ms to avoid noise
            c_thread_delay(200);

            break;
        }
        default:
        {
            break;
        }
    }

    return;
    #endif
}


VOID a2dp_connect_audio_reset_cbk(void* pv_tag)

{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s,do audio reset to enable 48K down samples \n",__FUNCTION__));
	//acfg_check_audio_reset();
}
#endif
#if 0
#define BTMW_RPC_A2DP_CASE_RETURN_STR(const) case const: return #const;

static CHAR* btmw_rpc_test_a2dp_sink_app_event(BT_A2DP_EVENT event)
{
    switch((int)event)
    {
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_CONNECTED)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_DISCONNECTED)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_CONNECT_TIMEOUT)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_STREAM_SUSPEND)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_STREAM_START)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_CONNECT_COMING)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_PLAYER_EVENT)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_EVENT_ROLE_CHANGED)
        default: return "UNKNOWN_EVENT";
   }
}
static CHAR* btmw_rpc_test_a2dp_sink_player_event_str(BT_A2DP_PLAYER_EVENT player_event)
{
    switch((int)player_event)
    {
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_ALSA_PB_EVENT_STOP)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_ALSA_PB_EVENT_STOP_FAIL)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_ALSA_PB_EVENT_START)
        BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_ALSA_PB_EVENT_START_FAIL)
        default: return "UNKNOWN_EVENT";
   }
}

static CHAR* btmw_rpc_test_a2dp_get_codec_str(UINT8 codec_tpye)
{
     switch(codec_tpye)
     {
         BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_CODEC_TYPE_SBC)
         BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_CODEC_TYPE_MP3)
         BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_CODEC_TYPE_AAC)
         BTMW_RPC_A2DP_CASE_RETURN_STR(BT_A2DP_CODEC_TYPE_LDAC)
         default: return "UNKNOWN_CODEC_TYPE";
    }
}

CHAR g_rpc_a2dp_addr_test[18];
static BT_A2DP_ROLE g_rpc_a2dp_local_role = BT_A2DP_ROLE_SRC;
BT_A2DP_STREAM_STATE g_rpc_a2dp_stream_state = BT_A2DP_STREAM_STATE_SUSPEND;

/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_hid_event_cbk
  *
  * Description  - MW callback this function to notify APP of HID event
  *
  * Inputs        -
  * Returns       -
  *------------------------------------------------------------------------------------------------------------------*/
VOID bluetooth_a2dp_event_cbk2(BT_A2DP_EVENT_PARAM *param, void* pv_tag)
{
    UINT8 codec_type = 0;

    if (NULL == param)
    {
        BT_APP_LOG_DEFAULT(("param is NULL\n"));
        return;
    }

    BT_APP_LOG_DEFAULT(("tanss addr=%s, event=%d, %s\n", param->addr, param->event,
        btmw_rpc_test_a2dp_sink_app_event(param->event)));
    switch (param->event)
    {
        case BT_A2DP_EVENT_CONNECTED:
            //a_mtkapi_a2dp_sink_start_player();
            BT_APP_LOG_DEFAULT(("A2DP connected(%s)\n", param->addr));

            strcpy(g_rpc_a2dp_addr_test, param->addr);
            g_rpc_a2dp_local_role = param->data.connected_data.local_role;

            codec_type = param->data.connected_data.config.codec_type;
            BT_APP_LOG_DEFAULT(("current codec is:%s(%d)\n", \
                btmw_rpc_test_a2dp_get_codec_str(codec_type), \
                codec_type));
            switch (codec_type)
            {
                case BT_A2DP_CODEC_TYPE_SBC: //A2D_MEDIA_CT_SBC
                {
                    BT_A2DP_SBC_CONF *local_sbc = &param->data.connected_data.config.codec_conf.sbc_conf;
                    BT_APP_LOG_DEFAULT(("min_bitpool:%d\n", local_sbc->min_bitpool));
                    BT_APP_LOG_DEFAULT(("max_bitpool:%d\n", local_sbc->max_bitpool));


                    break;
                }
                case BT_A2DP_CODEC_TYPE_AAC:
                {
                    BT_A2DP_AAC_CONF *local_aac = &param->data.connected_data.config.codec_conf.aac_conf;
                    BT_APP_LOG_DEFAULT(("object_type:%d\n", local_aac->object_type));
                    BT_APP_LOG_DEFAULT(("sample_rate:%ld\n", local_aac->samp_freq));
                    BT_APP_LOG_DEFAULT(("channels:%d\n", local_aac->channels));
                    BT_APP_LOG_DEFAULT(("VBR supported? (%s)\n", local_aac->vbr ? "TRUE" : "FALSE"));
                    BT_APP_LOG_DEFAULT(("bit_rate:%d\n", local_aac->bitrate));

                    break;
                }
                default:
                    BT_APP_LOG_DEFAULT(("invalid codec type:%d\n", codec_type));
                    break;
            }
            break;
        case BT_A2DP_EVENT_DISCONNECTED:
            a_mtkapi_a2dp_sink_stop_player();
            BT_APP_LOG_DEFAULT(("A2DP disconnected(%s)\n", param->addr));
            g_rpc_a2dp_addr_test[0] = 0;
            break;
        case BT_A2DP_EVENT_CONNECT_TIMEOUT:
            BT_APP_LOG_DEFAULT(("A2DP Connect Timeout(%s)\n", param->addr));
            g_rpc_a2dp_addr_test[0] = 0;
            break;
        case BT_A2DP_EVENT_STREAM_SUSPEND:
            g_rpc_a2dp_stream_state = BT_A2DP_STREAM_STATE_SUSPEND;
            break;
        case BT_A2DP_EVENT_STREAM_START:
            //a_mtkapi_a2dp_sink_start_player();
             //BT_APP_LOG_DEFAULT(("to start player(open alsa)\n"));
            g_rpc_a2dp_stream_state = BT_A2DP_STREAM_STATE_PLAYING;
            if (BT_A2DP_ROLE_SINK == g_rpc_a2dp_local_role)
            {
                BT_APP_LOG_DEFAULT(("tanss to start player(open alsa)\n"));
                a_mtkapi_a2dp_sink_start_player();
            }
            break;
        case BT_A2DP_EVENT_CONNECT_COMING:
            break;
        case BT_A2DP_EVENT_PLAYER_EVENT:
            BT_APP_LOG_DEFAULT(("player event %s(%d)\n",
                btmw_rpc_test_a2dp_sink_player_event_str(param->data.player_event),
                param->data.player_event));
            break;
        case BT_A2DP_EVENT_ROLE_CHANGED:
            break;
        default:
            break;
    }
    return;
}
#endif
VOID bluetooth_a2dp_event_cbk(BT_A2DP_EVENT_PARAM *a2dp_struct_data, void* pv_tag)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    BT_A2DP_EVENT_PARAM *bt_msg_data = NULL;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));

    bt_msg_data = (BT_A2DP_EVENT_PARAM *)c_mem_alloc(sizeof(BT_A2DP_EVENT_PARAM));
    if (NULL == bt_msg_data)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for a2dp event fail\n"));
        return ;
    }

    c_memcpy(bt_msg_data, a2dp_struct_data, sizeof(BT_A2DP_EVENT_PARAM));


    t_bt_msg.msg_type = BT_APP_MSG_NFY_A2DP_EVENT;//BT_APP_MSG_NFY_A2DP_EVENT;
    t_bt_msg.ui4_data_size  = sizeof(BT_A2DP_EVENT_PARAM);
    t_bt_msg.pv_data = bt_msg_data;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send BT_APP_MSG_NFY_A2DP_EVENT msg fail\n"));
    }
    return;

}


/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_hid_event_cbk
  *
  * Description  - MW callback this function to notify APP of HID event
  *
  * Inputs        -
  * Returns       -
  *------------------------------------------------------------------------------------------------------------------*/
VOID bluetooth_hid_event_cbk(BT_HIDH_CBK_STRUCT *hid_struct_data, void* pv_tag)

{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    BT_HIDH_CBK_STRUCT *bt_msg_data = NULL;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));

    bt_msg_data = (BT_HIDH_CBK_STRUCT *)c_mem_alloc(sizeof(BT_HIDH_CBK_STRUCT));
    if (NULL == bt_msg_data)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for hid event fail\n"));
        return ;
    }

    c_memcpy(bt_msg_data, hid_struct_data, sizeof(BT_HIDH_CBK_STRUCT));

    t_bt_msg.msg_type = BT_APP_MSG_NFY_HID_EVENT;
    t_bt_msg.ui4_data_size  = sizeof(BT_HIDH_CBK_STRUCT);
    t_bt_msg.pv_data = bt_msg_data;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send BT_APP_MSG_NFY_HID_EVENT msg fail\n"));
    }

    return;
}

CHAR* print_spp_event(BT_SPP_EVENT bt_event)
{
    switch (bt_event)
    {
        case BT_SPP_CONNECT:
            return "BT_SPP_CONNECT";
        case BT_SPP_DISCONNECT:
            return "BT_SPP_DISCONNECT";
        case BT_SPP_RECV_DATA:
            return "BT_SPP_RECV_DATA";
        case BT_SPP_CONNECT_FAIL:
            return "BT_SPP_CONNECT_FAIL";
        case BT_SPP_DISCONNECT_FAIL:
            return "BT_SPP_DISCONNECT_FAIL";
        default:
            break;
    }

    return "";
}


void bluetooth_spp_callback(BT_SPP_CBK_STRUCT *pt_spp_struct, void* pv_tag)
{
    BT_APP_LOG_DEFAULT(("[GAP] %s()\n",  __func__));
    BT_APP_LOG_DEFAULT(("[SPP] event: %s\n", print_spp_event(pt_spp_struct->event)));
    BT_APP_LOG_DEFAULT(("[SPP]bd_addr:%s\n", pt_spp_struct->bd_addr));
    BT_APP_LOG_DEFAULT(("[SPP]uuid:%s\n", pt_spp_struct->uuid));
    BT_APP_LOG_DEFAULT(("[SPP]spp_data:%s\n", pt_spp_struct->spp_data));
    BT_APP_LOG_DEFAULT(("[SPP]uuid_len:%d\n", pt_spp_struct->uuid_len));
    BT_APP_LOG_DEFAULT(("[SPP]spp_data_len:%d\n", pt_spp_struct->spp_data_len));
    return;
}


/**-----------------------------------------------------------------------------
  * Name          - _bluetooth_spp_cbk
  *
  * Description  - MW callback this function to notify the event of SPP
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
static VOID _bluetooth_spp_cbk(BT_SPP_CBK_STRUCT *pt_spp_struct, void* pv_tag)

{
#if 0
    INT32 i4_ret = PBR_OK;
    CHAR  *pc_uuid = NULL;
    BT_APP_MSG_T t_bt_msg = {0};
    BT_SPP_RECEIVED_DATA *pt_spp_data = NULL;

    if (NULL == pt_spp_struct)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, pt_spp_struct is NULL\n", __FUNCTION__));
        return ;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> receive SPP event, %d\n", pt_spp_struct->event));

    /* When event type is connect/disconnect fail, BTM don't notify with UUID */
    if (BT_SPP_CONNECT_FAIL == pt_spp_struct->event)
    {
        //pt_spp_struct->uuid = ac_connect_target_uuid;
        strcpy(pt_spp_struct->uuid, ac_connect_target_uuid);
        pt_spp_struct->uuid_len = (UINT8)c_strlen(ac_connect_target_uuid);
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR:%s, spp connect fail, uuid:%s, length:%d\n", __FUNCTION__, pt_spp_struct->uuid, pt_spp_struct->uuid_len));
    }

    if (NULL == pt_spp_struct->uuid)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, uuid is NULL\n", __FUNCTION__));
        return ;
    }

    if(pt_spp_struct->uuid_len >= SPP_UUID_LENGTH)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: UUID is too long\n"));
        return ;
    }

    t_bt_msg.msg_type = BT_APP_MSG_BTM_NFY_SPP_EVENT;
    t_bt_msg.ui4_msg_id = pt_spp_struct->event;

    switch (pt_spp_struct->event)
    {
        case BT_SPP_RECV_DATA:   // the event of receiving SPP data
        {
            if(NULL == pt_spp_struct->spp_data)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: %s, no SPP data\n", __FUNCTION__));
                return ;
            }

            if(pt_spp_struct->spp_data_len > MAX_SPP_DATA_LENGTH_APP)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: SPP data len is too long\n"));
                return ;
            }

            pt_spp_data = (BT_SPP_RECEIVED_DATA *)c_mem_alloc(sizeof(BT_SPP_RECEIVED_DATA));
            if(NULL == pt_spp_data)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem to receive spp data fail\n"));
                return ;
            }
            c_memset(pt_spp_data, 0, sizeof(BT_SPP_RECEIVED_DATA));

            pt_spp_data->ui4_data_len = pt_spp_struct->spp_data_len;
            c_strncpy(pt_spp_data->ac_uuid, pt_spp_struct->uuid, pt_spp_struct->uuid_len);
            c_memcpy(pt_spp_data->aui1_data,
                     pt_spp_struct->spp_data,
                     pt_spp_struct->spp_data_len);

            t_bt_msg.ui4_data_size = sizeof(BT_SPP_RECEIVED_DATA);
            t_bt_msg.pv_data = pt_spp_data;

            break;
        }
        case BT_SPP_CONNECT:
        case BT_SPP_CONNECT_FAIL:
        case BT_SPP_DISCONNECT:
        case BT_SPP_DISCONNECT_FAIL:
        {
            pc_uuid = (CHAR *)c_mem_alloc(pt_spp_struct->uuid_len + 1);
            if(NULL == pc_uuid)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for uuid fail\n"));
                return ;
            }
            c_memset(pc_uuid, 0, pt_spp_struct->uuid_len + 1);

            c_strncpy(pc_uuid, pt_spp_struct->uuid, pt_spp_struct->uuid_len);

            t_bt_msg.ui4_data_size = pt_spp_struct->uuid_len + 1;
            t_bt_msg.pv_data = pc_uuid;

            break;
        }
        default:
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: invalid SPP event\n"));
            return ;
        }
    }

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send mediainfo msg fail\n"));
    }
#endif
    return ;
}


/**------------------------------------------------------------------------------------------------------------------
  * Name          - bluetooth_get_pairingkey_cbk
  *
  * Description  - MW callback this function to notify APP of HID event
  *
  * Inputs        -
  * Returns       -
  *------------------------------------------------------------------------------------------------------------------*/
VOID bluetooth_get_pairingkey_cbk(pairing_key_value_t *bt_pairing_key, UINT8 *fg_accept, void* pv_tag)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    //pairing_key_value_t *bt_msg_data = NULL;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));
    DBG_LOG_PRINT(("<MENU_BT> bluetooth_get_pairingkey_cbk key_type %d\n",bt_pairing_key->key_type));
    DBG_LOG_PRINT(("<MENU_BT> bluetooth_get_pairingkey_cbk pin_code %s\n",bt_pairing_key->pin_code));
    DBG_LOG_PRINT(("<MENU_BT> bluetooth_get_pairingkey_cbk key_value %d\n",bt_pairing_key->key_value));

    c_memcpy(&bt_pairing_key_value, bt_pairing_key, sizeof(pairing_key_value_t));


    t_bt_msg.msg_type = BT_APP_MSG_GET_PAIRING_KEY;
    t_bt_msg.ui4_data_size  = sizeof(pairing_key_value_t);
    t_bt_msg.pv_data = &bt_pairing_key_value;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: send BT_APP_MSG_GET_PAIRING_KEY msg fail\n"));
    }

    return;
}


VOID bluetooth_log_out_cbk(char *log_str)
{
    BT_APP_LOG_ERR(("%s", log_str));

    return;
}

#if 0
/**-----------------------------------------------------------------------------
  * Name          - bluetooth_driver_init_done
  *
  * Description   - check bluetooth driver done
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
BOOL bluetooth_driver_init_done(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));

    while(1)
    {
        if(0 == access("/dev/stpbt", 0))
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> %s, bt_mod_inserted\n",__FUNCTION__));
            return TRUE;
        }
		else
        {
            c_thread_delay(200);
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n",__FUNCTION__));

    return FALSE;
}
#endif
/**---------------------------------------------------------------------------
  * Name          - bt_app_amp_volume_changed_proc
  *
  * Description  - In sink mode and input a2dp connected, press volume up/down from Remote controller, IFCON send STT_TA_volume_data
  *                     Response absolute volume to AVRCP 1.5 supported SRC device for sink mode.
  *                     Set device mute/unmute for SRC mode.
  *
  * Inputs        - u1_absolute_volume_percentage: IFCON absolute volume:range from 0 ~ 100
  *                 - u1_volume_ctrl_type: volumte mute/unmute
  *
  *---------------------------------------------------------------------------*/
 INT32 bt_app_amp_volume_changed_proc(VOID)
{
	INT32 i4_ret = -1;
    INT16   tmp_volume=0;

    i4_ret = a_tv_get_vol(ui2_vol_id, &tmp_volume);
    BT_APP_LOG_ERR(("<BT_APP>tmp_volume=%d,i2_volume=%d\n",tmp_volume,i2_volume));

    /* Only response current platform volume value to AVRCP V1.5 supported SRC device */
    if (bt_app_output_a2dp_connected()&&bt_app_avrcp_connected())
    {

        if ((tmp_volume > i2_volume)||(tmp_volume == 100))
        {
            //should input address.
            i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_VOL_UP, BT_AVRCP_KEY_STATE_PRESS);
            BT_APP_LOG_ON_FAIL(i4_ret);
            BT_APP_LOG_ERR(("<BT_APP>BT_CMD_TYPE_VOLUME_UP= \n"));
            c_thread_delay(10);

            i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_VOL_UP, BT_AVRCP_KEY_STATE_RELEASE);
            BT_APP_LOG_ON_FAIL(i4_ret);
    	}
        else if ((tmp_volume < i2_volume)||(tmp_volume == 0))
        {
            i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_VOL_DOWN, BT_AVRCP_KEY_STATE_PRESS);
            BT_APP_LOG_ON_FAIL(i4_ret);
            BT_APP_LOG_ERR(("<BT_APP>BT_CMD_TYPE_VOLUME_DOWN= \n"));
            c_thread_delay(10);

            i4_ret = a_mtkapi_avrcp_send_passthrough_cmd(NULL, BT_AVRCP_CMD_TYPE_VOL_DOWN, BT_AVRCP_KEY_STATE_RELEASE);
            BT_APP_LOG_ON_FAIL(i4_ret);
        }
        else
        {

        }

    }

    i2_volume = tmp_volume;
    return BT_APPR_OK;
}

static  VOID _cfg_vol_chg_nfy_fct(
    UINT16     ui2_nfy_id,
    VOID*      pv_tag,
    UINT16     ui2_id)
{
    INT32 i4_ret = 0;
    BT_APP_MSG_T t_bt_msg = {0};

    if(ui2_acfg_gl_nfy != ui2_nfy_id)
    {
        return;
    }


    if( ui2_vol_id == ui2_id )
    {
        t_bt_msg.msg_type = BT_APP_MSG_NFY_AMP_VOLUME_CHGD;

        i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
        if (i4_ret != PBR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: send play status update msg fail\n"));
        }

    }
}

INT32 bluetooth_volctrl_init(VOID)
{
    INT32 i4_ret = 0;

    if(0==ui2_acfg_gl_nfy)
    {
        i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_AUDIO,
                                  NULL,
                                  _cfg_vol_chg_nfy_fct,
                                  &ui2_acfg_gl_nfy);
        if (i4_ret != PBR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: bluetooth_volctrl_init fail %d\n", i4_ret));
            return PBR_FAIL;
        }
        a_tv_get_vol(ui2_vol_id, &i2_volume);
    }

    return i4_ret;
}
extern void a_mtk_bt_service_init(void);

/**-----------------------------------------------------------------------------
  * Name          - bluetooth_init
  *
  * Description  - init bluetooth
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bluetooth_init(VOID)
{
    INT32 i4_ret = 0;
    //UINT8 ui1_value = 0;
    MTKRPCAPI_BT_APP_CB_FUNC p_cbk_func = {0};
    char pv_tag[2]={0};


    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n",__FUNCTION__));
#if 1
    chmod("/tmp/mtk_bt_service", S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IWGRP|S_IXGRP|S_IROTH|S_IWOTH|S_IXOTH);

    /***      RPC init      ***/
    BT_APP_LOG_DEFAULT(("<BT_APP> ---------IPC/RPC initialize----------- \r\n"));
    DBG_LOG_PRINT(("YZ before into a_mtk_bt_service_init\n"));
    a_mtk_bt_service_init();
    sleep(3);
    BT_APP_LOG_DEFAULT(("<BT_APP> ---------IPC/RPC init Done!!!--------- \r\n"));
#endif

    // attach bluetooth command cli
    //bluetooth_cli_attach_cmd_tbl();

    memset(&p_cbk_func, 0, sizeof(MTKRPCAPI_BT_APP_CB_FUNC));

    // Insert Bluetooth ko and start Blueangel
    //i4_ret = bt_insert_ko_and_start_blueangel();
    //BT_APP_CHK_FAIL(i4_ret, i4_ret);

    // init Bluetooth Manager / MW
    p_cbk_func.bt_event_cb            = _bluetooth_gap_event_cbk_fct;
    //p_cbk_func.bt_play_change_cb      = _bluetooth_play_state_chg_cbk_fct;
   // p_cbk_func.bt_volume_change_cb    = _bluetooth_volume_chg_cbk_fct;
    //p_cbk_func.bt_track_change_cb     = _bluetooth_track_chg_cbk_fct;
    //p_cbk_func.bt_media_playstatus_cb = _bluetooth_mediainfo_play_status_cbk;
    //p_cbk_func.bt_spp_cb              = _bluetooth_spp_cbk;
    //p_cbk_func.bt_hid_cb              = bluetooth_hid_event_cbk;
    //p_cbk_func.bt_absolute_volume_cb  = bluetooth_absolute_volume_cmd_cbk;
    //p_cbk_func.bt_avrcp_cmd_cb        = bluetooth_avrcp_cmd_cbk;
    //p_cbk_func.bt_upload_info_cb      = bluetooth_upload_info_cbk;
    //p_cbk_func.bt_get_play_status_cb  = bluetooth_src_get_play_status_cbk;
    //p_cbk_func.bt_playback_ctrl_cb    = bluetooth_src_play_ctrl_cbk;
    //p_cbk_func.bt_reset_audio_cb	  = a2dp_connect_audio_reset_cbk;
    p_cbk_func.bt_get_pairing_key_cb  = bluetooth_get_pairingkey_cbk;
    p_cbk_func.bt_dev_info_cb  = _bt_app_a2dp_snk_inquiry_response_cbk_fct; //
    //p_cbk_func.bt_app_log_cb  = bluetooth_log_out_cbk;

    //BT_APP_LOG_DEFAULT(("<BT_APP> %s, sleep 2s.\n",__FUNCTION__));
    //sleep(2);

    i4_ret = a_mtkapi_gap_bt_base_init(&p_cbk_func,(void*)pv_tag);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: a_mtkapi_gap_bt_base_init fail %d\n", i4_ret));
        return PBR_FAIL;
    }

    //Register A2DP profile
    i4_ret = a_mtkapi_a2dp_register_callback(bluetooth_a2dp_event_cbk,(void*)pv_tag);
    a_mtkapi_a2dp_sink_enable(1);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: a_mtkapi_a2dp_register_callback fail %d\n", i4_ret));
        return PBR_FAIL;
    }

    //Register HID Host profile
    i4_ret = a_mtkapi_hidh_register_callback(bluetooth_hid_event_cbk,(void*)pv_tag);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: a_mtkapi_hidh_register_callback fail %d\n", i4_ret));
        return PBR_FAIL;
    }

    //Register AVRCP/SPP/...

    BT_APP_LOG_DEFAULT(("<BT_APP> ERR: a_mtkapi_spp_register_callback in \n"));
    a_mtkapi_spp_register_callback(_bluetooth_spp_cbk, NULL);
    BT_APP_LOG_DEFAULT(("<BT_APP> ERR: a_mtkapi_spp_register_callback out\n"));


    i4_ret = bluetooth_progress_timer_bar_initial();
    BT_APP_CHK_FAIL(i4_ret, i4_ret);

    // create semaphore for spp data buffer
    //i4_ret = bt_spp_sema_create();
    //BT_APP_CHK_FAIL(i4_ret, i4_ret);

    // create semaphore for bt connection/disconnection control
    i4_ret = bt_a2dp_disconnection_sema_create();
    BT_APP_CHK_FAIL(i4_ret, i4_ret);

    // Auto start bt function when power on function is bt, need to wait dongle ready
    i4_ret = bt_app_dongle_attach_sema_create();
    BT_APP_CHK_FAIL(i4_ret, i4_ret);

    // register to removable deivice
    i4_ret = a_rmv_dev_reg_monitor(_bt_dev_notify_fct,NULL,(UINT32*)(&e_g_bt_nfy_id));

    bt_app_sema_create();
    bluetooth_volctrl_init();

    // Create and start bluetooth msg proc thread
    //bt_create_bluetooth_thread();

    fg_bt_app_has_init = TRUE;

    i4_ret = PLAYBACKR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));

    return i4_ret;
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_init
  *
  * Description   - BT APP init.
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32  a_bt_init(VOID)
{
    INT32 i4_ret;
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    #if 0

    INT32 i4_ret = PBR_OK;

    i4_ret = x_thread_create(&h_bluetooth_init_thread,
                             BLUETOOTH_INIT_THREAD_NAME,
                             BLUETOOTH_INIT_STACK_SIZE,
                             BLUETOOTH_INIT_THREAD_PRIORITY,
                             _bluetooth_init_thread,
                             0,
                             NULL);

    //BT_APP_MSG_T t_bt_msg = {0};

    //t_bt_msg.msg_type = BT_APP_MSG_INIT;

    //i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send GAP event fail\n"));
    }
    #endif
    i4_ret = a_rmv_dev_reg_monitor(_bt_dev_notify_fct,NULL,(UINT32*)(&e_g_bt_nfy_id));

    if(RMVR_OK != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("a_rmv_dev_reg_monitor() failed. i4_ret = %d.\r\n", i4_ret));
    }
#ifdef VIZIO_FUSION_SUPPORT
    bt_create_bluetooth_thread();
#endif
    BT_APP_LOG_DEFAULT(("<BT_APP> before sleep:%s\n",__FUNCTION__));
    // sleep 5s.
    sleep(5);

    BT_APP_LOG_DEFAULT(("<BT_APP> after sleep:%s\n",__FUNCTION__));

    i4_ret = _bt_send_bt_dongle_attach_remove_nfy(BT_PLUG);

    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: _bt_send_bt_dongle_attach_nfy fail, %d\n", i4_ret));
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return PBR_OK;
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_app_has_init
  *
  * Description   - BT APP has been initialized or not.
  *
  * Returns       - TRUE: BT APP has been initialized, FALSE: BT APP has not been initialized
  *
  *---------------------------------------------------------------------------*/
BOOL a_bt_app_has_init(VOID)
{
    return fg_bt_app_has_init;
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_app_set_poweron_sequence_finish
  *
  * Description   -
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
VOID a_bt_app_set_poweron_sequence_finish(BOOL b_finish)
{
    fg_bt_poweron_sequence_finish = b_finish;
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_app_is_poweron_sequence_finish
  *
  * Description   - Is BT APP finish power on event
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
BOOL a_bt_app_is_poweron_sequence_finish(VOID)
{
    return fg_bt_poweron_sequence_finish;
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_app_set_system_power_state
  *
  * Description   -
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
VOID a_bt_app_set_system_power_state(BOOL b_poweron)
{
    fg_system_power_state = b_poweron;
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_app_is_system_power_on
  *
  * Description  -
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
BOOL a_bt_app_is_system_power_on(VOID)
{
    return fg_system_power_state;
}
#if 0
/**-----------------------------------------------------------------------------
  * Name          - bt_insert_ko_and_start_blueangel
  *
  * Description  - Insert Bluetooth ko and start Blueangel
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 bt_insert_ko_and_start_blueangel(VOID)
{
    INT32 i4_ret = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> insert bluetooth ko and Start Blueangel\n"));

    a_bt_app_load_bluetooth_data();

    // start Blueangel
//    i4_ret = c_btm_btlaunch_blueangel();
    if (0 != i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: Start Blueangel failed, %d\n", i4_ret));
    }

    return i4_ret;
}
#endif

/**-----------------------------------------------------------------------------
  * Name          - a_bt_req_bt_enable_disable
  *
  * Description  - send request to set bluetooth enable/disable
  *
  * Inputs        -
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_req_bt_enable_disable(BOOL b_enable)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, send bt %s req\n",__FUNCTION__, (b_enable ? "enable" : "disable")));

    if(b_enable)
    {
        t_bt_msg.msg_type = BT_APP_MSG_REQ_ENABLE_BT;
    }
    else
    {
        t_bt_msg.msg_type = BT_APP_MSG_REQ_DISABLE_BT;
    }

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send bt enable/disable req fail, %d\n", i4_ret));
    }

    return i4_ret;
}

INT32 a_bt_pre_suspend_exit(VOID)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s\n",__FUNCTION__));

    t_bt_msg.msg_type = BT_APP_MSG_PRE_SUSPEND_EXIT;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send bt enable/disable req fail, %d\n", i4_ret));
    }

    return i4_ret;
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_enable_disable
  *
  * Description  - 1. set priority of blueangle
  *                    2. set RF of bluetooth
  *                    3. set local device name
  *                    4. active/inactive a2dp/avrcp
  *                    5. set pairable/connectable/discoverable
  *                    6. set codec
  *
  * Inputs        -
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_enable_disable(BOOL b_enable)
{
    INT32 i4_ret = PBR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s: %s bluetooth\n", __FUNCTION__, (b_enable ? "Enable" : "Disable")));

    if(fg_bt_app_bluetooth_enable == b_enable)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Bluetooth RF no need change\n"));
        return PBR_OK;
    }

    // Check if bluetooth dongle exist or not.
    if(!_bt_check_bt_device())
    {
        BT_APP_LOG_ERR(("<BT_APP> No bluetooth device attached\n"));
        return PBR_FAIL;
    }

    if(b_enable)
    {
        i4_ret = a_mtkapi_bt_gap_on_off(TRUE);
    }
    else
    {
        i4_ret = a_mtkapi_bt_gap_on_off(FALSE);
    }

    if (i4_ret == 0)
    {
        fg_bt_app_bluetooth_enable = b_enable;
    }
    else
    {
        BT_APP_CHK_FAIL(i4_ret, i4_ret);
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s, fg_bt_app_bluetooth_enable[%d]\n", __FUNCTION__, fg_bt_app_bluetooth_enable));

    return i4_ret;
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_is_bluetooth_enabled
  *
  * Description  - Is bluetooth enabled or disabled
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
BOOL a_bt_is_bluetooth_enabled(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Currently Bluetooth is %s\n", (fg_bt_app_bluetooth_enable ? "Enabled" : "Disabled")));

    return fg_bt_app_bluetooth_enable;
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_is_bt_standby_enable
  *
  * Description  - check if bluetooth standby is enable, and set bluetooth standby bit of STT_DVD_status
  *                    If ON, set 1, if OFF set 0
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
BOOL a_bt_is_bt_standby_enable(VOID)
{
    #if 0
    INT32 i4_ret = BT_APPR_OK;
    UINT8 u1_paired_dev_num = 0;
    UINT8 u1_bt_standby = CFG_BLUETOOTH_STANDBY_OFF;
    UINT8 u1_bt_mode = CFG_BLUETOOTH_MODE_RECEIVER;
    BOOL  b_bt_standby_enable = FALSE;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n", __FUNCTION__));

    i4_ret = a_cfg_get_bluetooth_standby(&u1_bt_standby);

    i4_ret = a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

    // paired device including source and sink device
    u1_paired_dev_num = a_bt_app_get_paired_sink_device_num() + a_bt_app_get_paired_src_device_num();

    if ((CFG_BLUETOOTH_STANDBY_ON == u1_bt_standby)
        && (APP_CFG_BLUETOOTH_SWITCH_OFF != u1_bt_mode)
        && (0 != u1_paired_dev_num))
    {
        // only paired devices, including src and snk device, can boot up platform
        b_bt_standby_enable = TRUE;
    }
    else
    {
        b_bt_standby_enable = FALSE;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s: paired dev num[%d], bt_standby_setting[%d], bt_mode[%d], bluetooth standby status[%s]\n",  \
        __FUNCTION__, u1_paired_dev_num, u1_bt_standby, u1_bt_mode, (b_bt_standby_enable ? "TRUE" : "FALSE")));

    return b_bt_standby_enable;
    #endif
    return FALSE;
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_setup_bt_standby
  *
  * Description  - 1. send bluetooth standby status to IFCON
  *                    2. save bluetooth standby status to REGISTER
  *                    Bluetooth standby status is different with bluetooth standby setting.
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
VOID a_bt_setup_bt_standby(BOOL b_register_save)
{
    #if 0
    BOOL    b_bt_standby_status = FALSE;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s : b_register_save[%d]\n",__FUNCTION__, b_register_save));

    b_bt_standby_status = a_bt_is_bt_standby_enable();

    // set bluetooth wakeup function enable/disable to driver
    c_btm_wakeup_enable(b_bt_standby_status);

    // send the status to IFCON, IFCON control WIFI-BT dongle power according to bluetooth standby status & WOL status
    d_ifcon_set_wo_bt_standby(b_bt_standby_status);

    // only when system power off normally, save bluetooth standby status to register, to avoid AC OFF abnormal case
    // because when AC OFF, paired device info not save to flash
    if (b_register_save)
    {
        // REGISTER define value: ON = 0, OFF = 1
        b_bt_standby_status = !b_bt_standby_status;

        //store the status to register, when system AC ON, will use it
        d_rw_registry(REGISTER_BLUETOOTH_STANDBY_STATE, &b_bt_standby_status, 1, FALSE, TRUE);
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));
    #endif
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_power_setting_is_on
  *
  * Description  - bluetooth power setting is on or off
  *
  * Returns       - TRUE: bluetooth power setting is on, FALSE: bluetooth power setting is off
  *
  *---------------------------------------------------------------------------*/
BOOL a_bt_power_setting_is_on(VOID)
{
    #if 0
    UINT8 ui1_value = 0;

    a_cfg_get_bluetooth_power(&ui1_value);
    if(ui1_value == CFG_BLUETOOTH_POWER_ON)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
    #endif
    return TRUE;
}


/**-----------------------------------------------------------------------------------------------------------
  * Name          - a_bt_disable_bt_in_network_playback
  *
  * Description  - WiFi-BT priority can't change during connected, as for A2DP SRC mode, it is spec restriction.
  *                    But for A2DP sink mode(only used for Bluetooth AUDIO function and SongPal, SongPal need to keep A2DP connection in other than BT function),
  *                    should assure WIFI performance in network playback.
  *                    This API is used for disconnect bluetooth(including A2DP and SPP) when start network content/Miracast.
  *                    When exit network function/Miracast, need to recover bt RF by a_bt_enable_disable_recovery
  *                    Network connect including:HOME network, music services and Airplay<STR>
  *
  * Returns       -
  *
  *-----------------------------------------------------------------------------------------------------------*/
VOID a_bt_disable_bt_in_network_playback(BOOL b_disable_bt)
{
    #if 0
    UINT8 u1_bt_mode = 0;
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s, b_disable_bt[%d]\n",__FUNCTION__, b_disable_bt));

    //read bluetooth mode setting from flash
    a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

    if((CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode)
        && a_bt_is_bluetooth_enabled())
    {
        if (bt_app_input_a2dp_connected())
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Func %s: Disconnect a2dp\n",__FUNCTION__));

            // set flag to indicate whether need to turn off bluetooth RF when a2dp disconnect
            bt_app_set_flag_disable_bt_after_disconnect(b_disable_bt);

            i4_ret = c_btm_stop(FALSE,FALSE);
            if (i4_ret != BT_APPR_OK)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_stop fail, %d\n", i4_ret));
            }
        }
        else
        {
            if (TRUE == b_disable_bt)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> Func %s: Turn off BT RF\n",__FUNCTION__));

                bt_app_set_flag_disable_bt_after_disconnect(FALSE);

                a_bt_enable_disable(FALSE);
            }
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return;
    #endif
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_enable_disable_recovery
  *
  * Description  -
  *
  * Input         - b_sync: synchronous or asynchronous
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
VOID a_bt_enable_disable_recovery(BOOL b_sync)
{
    #if 0
    BOOL   b_bt_enabled = TRUE;
    UINT8  u1_bt_mode = 0;

    b_bt_enabled = a_bt_is_bluetooth_enabled();

    a_cfg_get_bluetooth_switch_status(&u1_bt_mode);

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func: %s, b_sync[%d], b_bt_enabled[%d], u1_bt_mode[%d]\n",__FUNCTION__, b_sync, b_bt_enabled, u1_bt_mode));

    if (b_bt_enabled)
    {
        // current bt RF is ON, set RF off
        if ((APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_mode)
            || ((CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode) && (a_bt_app_get_paired_src_device_num() == 0)))
        {
            if (b_sync)
            {
                a_bt_enable_disable(FALSE);
            }
            else
            {
                a_bt_req_bt_enable_disable(FALSE);
            }
        }
    }
    else
    {
        // current bt RF is OFF, set RF on
        if (((CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode) && (a_bt_app_get_paired_src_device_num() > 0))
            || (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode))
        {
            if (b_sync)
            {
                a_bt_enable_disable(TRUE);
            }
            else
            {
                a_bt_req_bt_enable_disable(TRUE);
            }
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func: %s\n",__FUNCTION__));
    #endif
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_bluetooth_mode_set
  *
  * Description  -  Set bluetooth mode internally
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
VOID a_bt_bluetooth_mode_set(UINT8 u1_bt_mode)
{
    INT32 i4_ret = BT_APPR_OK;
	UINT8 u1_bt_status = 0;
	a_cfg_get_bluetooth_switch_status(&u1_bt_status);
	BT_APP_LOG_ERR(("<BT_APP> a_bt_bluetooth_mode_set Bluetooth mode is  %d, \n",u1_bluetooth_mode));

    if (u1_bluetooth_mode == u1_bt_mode)
    {
        BT_APP_LOG_ERR(("<BT_APP> Bluetooth mode is already set to %d, no need change\n",u1_bluetooth_mode));
        return;
    }

    if (!a_bt_is_bluetooth_enabled() && (APP_CFG_BLUETOOTH_SWITCH_OFF != u1_bt_status))
    {
        BT_APP_LOG_ERR(("<BT_APP> Bluetooth is disabled, can't set bluetooth mode to %d.\n",u1_bt_mode));
        return;
    }

    if (APP_CFG_BLUETOOTH_SWITCH_SOURCE == u1_bt_mode)
    {
    	BT_APP_LOG_ERR(("<BT_APP> a_mtkapi_bt_gap_source_sink_on_off SOURCE %d, mode \n",u1_bt_mode));
        //i4_ret = a_mtkapi_a2dp_source_sink_on_off(TRUE, FALSE);
        i4_ret = a_mtkapi_a2dp_sink_enable(FALSE);
        i4_ret = a_mtkapi_a2dp_src_enable(TRUE);
    }
	else if(APP_CFG_BLUETOOTH_MODE_RECEIVER == u1_bt_mode)
	{
		BT_APP_LOG_ERR(("<BT_APP> c_btm_source_sink_on_off REVCEVIE %d, mode \n",u1_bt_mode));
		//i4_ret = a_mtkapi_a2dp_source_sink_on_off(FALSE,TRUE);
        i4_ret = a_mtkapi_a2dp_src_enable(FALSE);
        i4_ret = a_mtkapi_a2dp_sink_enable(TRUE);
    }
	else
	{
		i4_ret = BT_APPR_FAIL;
	}

    if (BT_APPR_OK != i4_ret)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: Set bluetooth mode %d failed, i4_ret:%d\n",u1_bt_mode, i4_ret));
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> Set bluetooth mode to %d, current mode is %d\n",u1_bt_mode, u1_bluetooth_mode));
        u1_bluetooth_mode = u1_bt_mode;
    }

}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_bluetooth_mode_get
  *
  * Description  -
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
UINT8 a_bt_bluetooth_mode_get(VOID)
{
    return u1_bluetooth_mode;
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_send_bt_setting_mode_chg_nfy
  *
  * Description  - Notify the event that bluetooth mode is changed in setup
  *
  * Inputs        - bt_mode_cfg: bt mode in setup
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_send_bt_setting_mode_chg_nfy(UINT8 bt_mode_cfg)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Notify: bt mode is changed in setup, %d\n", bt_mode_cfg));

    t_bt_msg.msg_type = BT_APP_MSG_NFY_BT_MODE_CHG;
    t_bt_msg.ui4_msg_id = bt_mode_cfg;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send bt mode req fail, %d\n", i4_ret));
    }

    return i4_ret;
}
#if 0
/**-----------------------------------------------------------------------------
  * Name          - a_bt_send_bt_dongle_attach_nfy
  *
  * Description  - Notify the event that bluetooth dongle is attached
  *
  * Inputs        -
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_send_bt_dongle_attach_nfy(VOID)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Notify: bluetooth dongle is attached\n"));

    t_bt_msg.msg_type = BT_APP_MSG_NFY_BT_DONGLE_ATTACH;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send BT_APP_MSG_NFY_BT_DONGLE_ATTACH fail, %d\n", i4_ret));
    }

    return i4_ret;
}
#endif
/**-----------------------------------------------------------------------------
  * Name          - a_bt_send_bt_tx_device_list_req
  *
  * Description  - IFCON send request to get specific sink device information.
  *
  * Inputs        - u1_bt_snk_dev_index: which index in the sink device list
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_send_bt_tx_device_list_req(UINT8 u1_bt_snk_dev_index)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> send bt tx device list req, index:%d\n", u1_bt_snk_dev_index));

    t_bt_msg.msg_type = BT_APP_MSG_REQ_BT_TX_DEV_LIST;
    t_bt_msg.ui4_msg_id = u1_bt_snk_dev_index;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send bt tx device list req fail, %d\n", i4_ret));
    }

    return i4_ret;
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_send_data_sync_ifcon_bt_cmd_nfy
  *
  * Description  - IFCON send bluetooth command
  *
  * Inputs        - e_bt_cmd_type:
  *                 COM_DVD_BT_bt_mode
  *                 COM_DVD_BT_bt_standby
  *                 COM_DVD_BT_bt_aac
  *                 COM_DVD_BT_bt_ldac
  *                 COM_DVD_BT_bt_transmission_quality
  *                 COM_DVD_BT_scan
  *                 COM_DVD_BT_tx_device_list
  *                 COM_DVD_BT_rx_a2dp_connect_disconnect
  *                 COM_DVD_BT_tx_a2dp_connect_disconnect
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_send_data_sync_ifcon_bt_cmd_nfy(BT_APP_DATA_SYNC_BT_CMD_E e_bt_cmd_type, UINT8 u1_data)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> send data sync ifcon bt command:%d\n", e_bt_cmd_type));

    t_bt_msg.msg_type   = BT_APP_MSG_IFCON_DATA_SYNC_BT_CMD;
    t_bt_msg.ui4_msg_id = e_bt_cmd_type;
    t_bt_msg.ui4_data1  = u1_data;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send data sync ifcon bt command fail, %d\n", i4_ret));
    }

    return i4_ret;
}

#if 0
/**-----------------------------------------------------------------------------
  * Name          - a_bt_send_src_mode_pbc_stt_nfy
  *
  * Description  - notify playback status to bluetooth when BT TX is connected state
  *
  * Inputs        -
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_send_src_mode_pbc_stt_nfy(PB_PBC_STT_E ePBCStt)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    if (bt_app_output_a2dp_connected())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> BT TX connected, pbc status change to: %d\n", ePBCStt));

        t_bt_msg.msg_type   = BT_APP_MSG_NFY_SRC_MODE_PBC_STT;
        t_bt_msg.ui4_msg_id = ePBCStt;

        i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
        if (i4_ret != PBR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: BT_APP_MSG_NFY_SRC_MODE_PBC_STT fail, %d\n", i4_ret));
        }
    }

    return i4_ret;
}
#endif

/**---------------------------------------------------------------------------
  * Name          - a_bt_system_bootup_sequence_init
  *
  * Description  -    1. enable/disable bluetooth
  *                       2. set bluetooth internal mode
  *                       3. auto connect to last paired sink device
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_system_bootup_sequence_init(VOID)
{
    INT32 i4_ret = BT_APPR_OK;
    UINT8 u1_bt_mode = 0;
	UINT8 u1_bt_switch_status = 0;

    //read bluetooth mode setting from flash
    a_cfg_get_bluetooth_switch_status(&u1_bt_switch_status);
	a_cfg_get_bluetooth_mode_status(&u1_bt_mode);

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if (_bt_check_bt_device()
        && (a_bt_app_has_init())
        && (!a_bt_app_is_poweron_sequence_finish()))
    {
        /* If dongle not attach, this process will be done when receive dongle attach notify */

        // Enable bluetooth condition, here default enable bluetooth
        // 1. bluetooth mode = Receiver and paired src device existed
        // 2. bluetooth mode = Transmitter
        if (!a_bt_is_bluetooth_enabled())
        {
            i4_ret = a_bt_enable_disable(TRUE);
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }

        // set bluetooth local device name and send it to IFCon
        // must do after bluetooth enabled
        a_bt_app_set_local_device_name("PanasonicTv_BT");

        if ((!bt_app_nfc_detected())
            && (!bt_app_input_a2dp_connected())
            && (!bt_app_output_a2dp_connected()))
        {
            // initialized the bluetooth mode must be set after bt power on
            if (a_bt_bluetooth_mode_get() != u1_bt_mode)
            {
                a_bt_bluetooth_mode_set(u1_bt_mode);
            }

            // Judge below condition to disable bluetooth
            if((APP_CFG_BLUETOOTH_SWITCH_OFF == u1_bt_switch_status)&&(a_bt_is_bluetooth_enabled()))
            {
                i4_ret = a_bt_enable_disable(FALSE);
                BT_APP_CHK_FAIL(i4_ret, i4_ret);
            }
        }

        a_bt_app_set_poweron_sequence_finish(TRUE);

        if (APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_switch_status)
        {
            i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(TRUE, TRUE);
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }
        else
        {
            i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(FALSE, FALSE);
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }

        // in transmitter mode, if there is paired sink device, need to auto link to it when power on
        if ((a_bt_app_is_system_power_on())
            && (a_bt_app_is_poweron_sequence_finish())
            && (!bt_app_nfc_detected())
            && (!bt_app_input_a2dp_connected())
            && (!bt_app_output_a2dp_connected())
            && (APP_CFG_BLUETOOTH_SWITCH_SOURCE == u1_bt_mode)
            && (0 != a_bt_app_get_paired_sink_device_num())
            )
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> System power on, auto connect to last paired sink device\n"));

            i4_ret = bt_app_connect_with_sink_dev(TRUE, NULL);
            BT_APP_CHK_FAIL(i4_ret, i4_ret);
        }
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_power_off_post_proc
  *
  * Description  -    this API run for BT module post processs during power off
  *                       - WOBT enabled:
  *                        1. normal standby mode(AC ON/POWER OFF): remove bt ko to trigger suspend function, unload ko will enable connectable again
  *                        2. quick standby mode: pairable/connectable/discoverable set as OFF when recevier AM power off msg,
  *                            here need to set connectable ON before enter quick standby completely.
  *                       - WOBT disabled:
  *                         disable bt when power off
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_power_off_post_proc(VOID)
{
    INT32 i4_ret = PBR_OK;
    #if 0
    UINT16 u2_wol = 0;
    UINT8 u1_system_sty_setting = 0;
    UINT8 u1_bt_standby_status = 0;
    BT_TARGET_DEV_INFO r_target_dev_info = {0,0,{0},{0}};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n", __FUNCTION__));

    // get remote start setting
    i4_ret = a_cfg_get_remotestart(&u2_wol);
    BT_APP_LOG_ON_FAIL(i4_ret);

    // get system standby mode
    i4_ret = a_cfg_get_standby(&u1_system_sty_setting);
    BT_APP_LOG_ON_FAIL(i4_ret);

    // read bluetooth standby status from flash : 0-ON, 1-OFF
    d_rw_registry(REGISTER_BLUETOOTH_STANDBY_STATE, &u1_bt_standby_status, 1, TRUE, FALSE);
    u1_bt_standby_status = !u1_bt_standby_status;

    BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s : system standby mode[%d], wol[%d], wobt[%d]\n", __FUNCTION__, u1_system_sty_setting, u2_wol, u1_bt_standby_status));

    if (bt_app_input_a2dp_connected() || bt_app_output_a2dp_connected())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d, wait for BT disconnect\n", __FUNCTION__, __LINE__));

        /* Get connected device MAC info */
        i4_ret = c_btm_get_target_info(&r_target_dev_info);
        if (BT_APPR_OK == i4_ret)
        {
            if (CFG_STANDBY_NORMAL == u1_system_sty_setting)
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s : Normal standby qucik disconnect, Device:%s, Name:%s\n", __FUNCTION__, r_target_dev_info.bdAddr, r_target_dev_info.name));

                i4_ret = c_btm_do_gap_quick_disconnect(r_target_dev_info.bdAddr);
            }
            else
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s : Quick standby normal disconnect, Device:%s, Name:%s\n", __FUNCTION__, r_target_dev_info.bdAddr, r_target_dev_info.name));

                if (bt_app_input_a2dp_connected())
                {
                    i4_ret = c_btm_stop(FALSE,FALSE);
                    if (i4_ret != BT_APPR_OK)
                    {
                        BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_stop fail, %d\n", i4_ret));
                    }
                }
                else if (bt_app_output_a2dp_connected())
                {
                    bt_app_disconnect_with_sink_dev();
                }
            }
        }
        else
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s : No BT connection exist\n",__FUNCTION__));
        }

        c_thread_delay(200);
    }

    if (TRUE == u1_bt_standby_status)
    {
        /* bluetooth standby mode, need to enable bt */
        if (!a_bt_is_bluetooth_enabled())
        {
            a_bt_enable_disable(TRUE);
        }

        if ((CFG_STANDBY_NORMAL == u1_system_sty_setting)
#if CONFIG_SUSPEND_TO_RAM
        &&!str_mode_is_on()
#endif
            )
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d, remove bt ko\n", __FUNCTION__, __LINE__));

            // delay to make sure blueangel detach success
            bt_app_delay(3000);

            if (CFG_REMOTE_START_OFF == u2_wol)
            {
                i4_ret = ipcd_exec(BLUETOOTH_WOW_OFF_ENABLE_WOBT_CMD, NULL);
            }
            else
            {
                i4_ret = ipcd_exec(BLUETOOTH_WOW_ON_ENABLE_WOBT_CMD, NULL);
            }

            if(i4_ret != 0)
            {
                BT_APP_LOG_ERR(("<BT_APP> ERR: Remove bluetooth ko failed, %d\n", i4_ret));
            }
        }
        else if (CFG_STANDBY_QUICKSTART == u1_system_sty_setting)
        {
            //BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d, Set pairable/connectable ON, discoverable OFF\n", __FUNCTION__, __LINE__));
            //c_btm_set_pairable_sync(TRUE);
            a_mtkapi_bt_gap_stop_inquiry_scan(TRUE, TRUE);
        }
    }
    else
    {
        /* bluetooth standby disabled, need to disable BT */
        if (a_bt_is_bluetooth_enabled())
        {
            a_bt_enable_disable(FALSE);

            // delay to make sure bt disable success
            bt_app_delay(500);
        }
    }

    // bt power off sequence finished, set flag to enable bt connection
    bt_app_set_BtConnectable(TRUE);

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n", __FUNCTION__));
    #endif
    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bluetooth_system_power_on_proc
  *
  * Description  - When the system is going to be power-on, call this API to do some process:
  *                       1. Send local bluetooth MAC and name to  IFCon
  *                       2. Turn on bluetooth device if bluetooth power setting is ON.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 bluetooth_system_power_on_proc(VOID)
{
    INT32 i4_ret = PBR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    // system power on, set the state flag
    a_bt_app_set_system_power_state(TRUE);

    // set bluetooth standby on/off to IFCON, remote start and bluetooth standby shall be independent
    a_bt_setup_bt_standby(FALSE);

    // do power on sequence init
    i4_ret = a_bt_system_bootup_sequence_init();

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_system_power_on_proc
  *
  * Description  - When the system is going to be power-on, call this API to do some process:
  *                       1. Send local bluetooth MAC and name to  IFCon
  *                       2. Turn on bluetooth device if bluetooth power setting is ON.
  *
  * Returns       -
  *---------------------------------------------------------------------------*/
INT32 a_bt_system_power_on_proc(VOID)
{
    INT32 i4_ret = PBR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    i4_ret = bluetooth_system_power_on_proc();
    BT_APP_CHK_FAIL(i4_ret, i4_ret);

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - a_bt_system_power_off_proc
  *
  * Description  - When the system is going to be power-off, call this API to do some process:
  *                       1. Exit Bluetooth screen and disconnect connected device.
  *                       2. Turn off local Bluetooth device.
  *                       3. Save Bluetooth data to NAND, including paired devices.
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_system_power_off_proc(VOID)
{
    INT32 i4_ret = PBR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
#if 0
    // power off ,clear power on init flag
    a_bt_app_set_poweron_sequence_finish(FALSE);

    // system power off, set the state flag
    a_bt_app_set_system_power_state(FALSE);

    // set connectable OFF during system power off sequence
    //bt_app_set_BtConnectable(FALSE); mkt10963

    /* if bluetooth is enabled, set pairable/connectable/discoverable all OFF, to make sure no device can connect to set during power off */
    if (a_bt_is_bluetooth_enabled())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Power OFF: Set Connectable/Discoverable OFF\n"));

        a_mtkapi_bt_gap_stop_inquiry_scan(FALSE, FALSE);

        BT_APP_LOG_DEFAULT(("<BT_APP> Power OFF: Set Pairable OFF\n"));

        //c_btm_set_pairable_sync(FALSE);
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Power OFF: Stop Bluetooth Audio function\n"));

    // only for exit bluetooth function, no need stop btm
    i4_ret = bt_app_stop_bluetooth();
#endif

    // only for exit bluetooth function, no need stop btm
    i4_ret = bt_app_stop_bluetooth();
    BT_APP_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(FALSE, FALSE);
    BT_APP_CHK_FAIL(i4_ret, i4_ret);

    /* disconnect output a2dp when power off */
    if (bt_app_output_a2dp_connected())
    {
        BT_APP_LOG_INFO(("<BT_APP> Power OFF: Start to disconnect output a2dp connection\n"));

        bt_app_disconnect_with_sink_dev();
    }

    /* disconnect HID when power off */
    if(bt_app_hid_connected())
    {
        BT_APP_LOG_INFO(("<BT_APP> Power OFF: Start to disconnect HID connection\n"));

        bt_app_hid_disconnect_all();
    }
#if 0
    /* Exit sink device list */
    if (bt_app_is_sink_dev_list_start()
        ||bt_app_is_audio_output_dev_list_start())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Power OFF: Close sink device list\n"));

        i4_ret = bt_app_close_sink_device_list();
    }
#endif
    // Save Bluetooth data to NAND, including paired devices
//    a_bt_app_save_bluetooth_data();

    // setup bluetooth standby status
    //a_bt_setup_bt_standby(TRUE);

    // delay 200ms to make sure blueangel disconnection complete
    //bt_app_delay(300);

    if (a_bt_is_bluetooth_enabled())
    {
        i4_ret = a_bt_enable_disable(FALSE);
        BT_APP_CHK_FAIL(i4_ret, i4_ret);
    }


    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_set_aac_enable
  *
  * Description  - set aac codec enable/disable to MW
  *
  * Inputs        - 0: AAC, 1: SBC
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_set_aac_enable(UINT8 u1_aac_cfg)
{
    #if 0
    BOOL b_aacenable = FALSE;

    b_aacenable = (u1_aac_cfg == CFG_BLUETOOTH_AUDIO_AAC1_ON) ? TRUE : FALSE;
    BT_APP_LOG_DEFAULT(("<BT_APP> Set BT audio aac codec: %s to MW\n", b_aacenable?"enable":"disable"));

    c_btm_set_aac_enable(b_aacenable);
    #endif

    return BT_APPR_OK;
}

/**-----------------------------------------------------------------------------
  * Name          - a_bt_set_ldac_enable
  *
  * Description  - set LDAC codec enable/disable to MW
  *
  * Inputs        - 0: disable, 1: enable
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_set_ldac_enable(UINT8 u1_ldac_cfg)
{
    #if 0
    BOOL b_ldacenable = FALSE;

    b_ldacenable = (u1_ldac_cfg == CFG_BLUETOOTH_AUDIO_LDAC_ON) ? TRUE : FALSE;
    BT_APP_LOG_DEFAULT(("<BT_APP> Set BT audio ldac codec: %s to MW\n", b_ldacenable?"enable":"disable"));

    c_btm_set_ldac_enable(b_ldacenable);
    #endif

    return BT_APPR_OK;
}


/**-----------------------------------------------------------------------------
  * Name          - a_bt_set_transmitter_quality
  *
  * Description  - set Transmitter quality to MW
  *
  * Inputs        - Auto/Sound quality/Standard/Connection
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 a_bt_set_transmitter_quality(UINT8 u1_qua_cfg)
{
    #if 0
    BT_AUDIO_QUALITY e_audio_quality = BT_QUALITY_UNKONW;
    char *quality = NULL;

    switch (u1_qua_cfg)
    {
        case CFG_BLUETOOTH_TRANSMITTER_QUALITY_AUTO:
            e_audio_quality = BT_QUALITY_AUTO;
            quality = "Auto";
            break;

        case CFG_BLUETOOTH_TRANSMITTER_QUALITY_SOUND_QUALITY:
            e_audio_quality = BT_QUALITY_SOUND_QUALITY;
            quality = "Sound";
            break;

        case CFG_BLUETOOTH_TRANSMITTER_QUALITY_STANDARD:
            e_audio_quality = BT_QUALITY_STANDARD;
            quality = "Standard";
            break;

        case CFG_BLUETOOTH_TRANSMITTER_QUALITY_CONNECTION:
            e_audio_quality = BT_QUALITY_CONNECTON;
            quality = "Connection";
            break;

        default:
            e_audio_quality = BT_QUALITY_UNKONW;
            quality = "Unknown";
            break;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Set BT transmitter quality: %s to MW\n", quality));

    c_btm_set_playback_quality(e_audio_quality);
    #endif

    return BT_APPR_OK;
}

INT32 a_bt_set_media_information(VOID)
{
    #if 0
    INT32 media_type = 0;
    UINT8 dsee_value = CFG_DSEE_HX_OFF;
    DM_DEV_MED_DISC_TYPE_T physic_type;

    physic_type = a_get_disc_physic_type();

    if(DM_DEV_MED_DISC_TYPE_DVD_R == physic_type
        ||DM_DEV_MED_DISC_TYPE_DVD_RW == physic_type
        ||DM_DEV_MED_DISC_TYPE_BD_RE == physic_type
        ||DM_DEV_MED_DISC_TYPE_BD_RW == physic_type
        ||MEDIA_IS_SACD(_e_med_type))
    {
        media_type = 1;
    }
    else
    {
        media_type = 2;
    }

    c_btm_current_media_type_sample_rate(media_type, 0);

    a_cfg_get_dsee_hx(&dsee_value);

    c_btm_get_DSEE_status(dsee_value);
    #endif

    return BT_APPR_OK;
}
/**---------------------------------------------------------------------------
  * Name          - bt_app_in_playing_mode
  *
  * Description  - Check if BDV is playing Bluetooth audio as a Bluetooth A2DP SNK device.
  *
  * Returns       - TRUE: BDV is playing Bluetooth audio, FALSE:
  *
  *---------------------------------------------------------------------------*/
BOOL bt_app_in_playing_mode(VOID)
{
#if 0
    if(bt_app_is_bluetooth_audio_function_start() &&
        (BT_MODE_PLAYING == a_mtkapi_bt_gap_get_mode()))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
#endif
    return FALSE;
}

/**---------------------------------------------------------------------------
  * Name          - _bt_app_bluetooth_mode_prepare
  *
  * Description  - Do preparation to start Bluetooth mode (show bluetooth screen).
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_bluetooth_mode_prepare()
{
    INT32 i4_ret = BT_APPR_OK;


    BT_APP_LOG_DEFAULT(("<BT_APP> API: %s\n", __FUNCTION__));

    if(bt_app_is_bluetooth_audio_function_start())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Bluetooth AUDIO function has been started\n"));
        return BT_APPR_OK;
    }

    // 1. turn on bluetooth RF
    if(!a_bt_is_bluetooth_enabled())
    {
        a_bt_enable_disable(TRUE);
    }

    // 2. set bluetooth mode to Receiver mode, must be set after set bt power on
    a_bt_bluetooth_mode_set(APP_CFG_BLUETOOTH_MODE_RECEIVER);

    //uetooth_stop_all_media_engine();

    //_med_type = PB_MEDIA_BLUETOOTH_AUDIO;
    _e_bluetooth_state = BLUETOOTH_ENABLE_STATE;

    // set flag to indicate bluetooth audio function started
    bt_app_set_bluetooth_audio_function_start(TRUE);

    //_ret = playback_view_show();
    //if (i4_ret != PBR_OK)
    //{
    //    BT_APP_LOG_DEFAULT(("<BT_APP> ERR: playback_view_show fail %d\n", i4_ret));
    //    return PBR_FAIL;
    //}

    // clear media info
    bt_app_clear_media_info();

    //ifcon_set_gui_display(GUI_NORMAL_DISP);

    //amb_resume_app(PLAYBACK_APP_NAME);


    return i4_ret;
}

/**-----------------------------------------------------------------------------
  * Name          - _bt_app_enter_pairing_mode
  *
  * Description  - Enter Bluetooth PAIRING MODE
  *                     In PAIRING MODE, the unit becomes ''discoverable", "bondable(=pairable)", and "connectable".
  *                     Other Bluetooth devices can find this unit and start pairing/connection.
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_enter_pairing_mode(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s, PAIRING mode\n", __FUNCTION__));

    // clear flag
    //_e_pbui_state = NORMAL_STATE;
    _e_bluetooth_state = BLUETOOTH_ENABLE_STATE;
    bt_app_set_running_status(AVRCP_PLAY_STATUS_MAX);
    bt_app_set_flag_input_a2dp_connected(FALSE);
    bt_app_set_flag_avrcp_connected(FALSE);
    bt_app_set_flag_a2dp_avrcp_is_notified(FALSE);

    // clear playback time
    bt_app_clear_playback_time();

    if(!a_bt_is_bluetooth_enabled())
    {
        a_bt_enable_disable(TRUE);
    }

    i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(TRUE, TRUE);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: set connectable and discoverable fail %d\n", i4_ret));
        return BT_APPR_FAIL;
    }

    return i4_ret;
}

/**-----------------------------------------------------------------------------
  * Name          - _bt_app_enter_playing_mode
  *
  * Description  - Enter Bluetooth PLAYING MODE
  *                     In PLAYING MODE, BDV is playing Bluetooth audio as a Bluetooth A2DP SNK device.
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_enter_playing_mode(VOID)
{
    INT32 i4_ret = PBR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s, PLAYING mode\n", __FUNCTION__));

    _e_bluetooth_state = BLUETOOTH_ENABLE_STATE;
    bt_app_set_playstatus_ready_flag(FALSE);
    bt_app_set_running_status(AVRCP_PLAY_STATUS_MAX);

    // clear playback time
    bt_app_clear_playback_time();

    //i4_ret = a_mtkapi_bt_gap_btstart("PLAYING", 0);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: a_mtkapi_bt_gap_btstart : PLAYING fail %d\n", i4_ret));
        return PBR_FAIL;
    }

    // send request to get meta data from SRC.
    i4_ret = bt_app_send_req_to_get_meta_data();
    if(PBR_OK != i4_ret)
    {
        // AVRCP connection may not been established at this time, request will fail,
        // we need send it again when AVRCP 1.3 connection success.
        bt_app_set_flag_meta_data_req_need_send_again(TRUE);

        BT_APP_LOG_INFO(("<BT_APP> Hasn't create AVRCP, send request later\n"));
    }

    // Start the timer to monitor and update signal strength of connected SRC device.
    bt_app_ui_restart_rssi_update_timer();

    bluetooth_progress_timer_bar_start();

    return i4_ret;
}

/**-----------------------------------------------------------------------------
  * Name          - bt_app_enter_connecting_mode
  *
  * Description  - Enter Bluetooth CONNECTING MODE
  *                     If enterring CONNECTING MODE, BDV start to connect the last connected device from BDV's side.
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32 bt_app_enter_connecting_mode(VOID)
{
    INT32  i4_ret = BT_APPR_OK;
    BT_TARGET_DEV_INFO t_device = {0,0,{0},{0}};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s, CONNECTING mode\n", __FUNCTION__));

    // clear flag
    //_e_pbui_state = NORMAL_STATE;
    //_e_bluetooth_state = BLUETOOTH_ENABLE_STATE;
    bt_app_set_running_status(AVRCP_PLAY_STATUS_MAX);
    bt_app_set_flag_input_a2dp_connected(FALSE);
    bt_app_set_flag_avrcp_connected(FALSE);
    bt_app_set_flag_a2dp_avrcp_is_notified(FALSE);

    // clear playback time
    bt_app_clear_playback_time();

    if(!a_bt_is_bluetooth_enabled())
    {
        a_bt_enable_disable(TRUE);
    }

    i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(TRUE, TRUE);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : CONNECTING fail %d\n", i4_ret));
        return BT_APPR_FAIL;
    }

    // connect to the latest paired device
    i4_ret = bt_app_get_latest_paired_src_device(&t_device);
    if(i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> no paired device\n"));
        return BT_APPR_OK;
    }

    //indicate input a2dp connection is triggered by platform itself
    bt_app_set_flag_input_a2dp_initiator(TRUE);

    bt_app_connect(t_device.bdAddr);

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_start_bluetooth
  *
  * Description  - Start Bluetooth screen (Start Bluetooth mode).
  *                     When Bluetooth screen is shown, the unit is in Bluetooth mode.
  *                     There are three different Bluetooth mode:
  *                        1. Pairing Mode.
  *                        2. Connecting Mode.
  *                        3. Playing Mode.
  *                     If it have been in Bluetooth mode and this API is called again, it will change
  *                     to the new mode.
  *
  * Inputs        - e_mode: Bluetooth APP mode <Pairing mode, Connecting mode, Playing mode>
  *
  *---------------------------------------------------------------------------*/
INT32 bt_app_start_bluetooth(BT_APP_MODE_E e_mode)
{
    UINT32  u4PairedNum;

    BT_APP_LOG_DEFAULT(("<BT_APP> API: %s, %d\n", __FUNCTION__, e_mode));

    // If bluetooth audio function is not started, then do the preparation
    if(FALSE == bt_app_is_bluetooth_audio_function_start())
    {
        _bt_app_bluetooth_mode_prepare();
    }

    switch (e_mode)
    {
        case BT_APP_MODE_PAIRING:   // Pairing mode
        {
            _bt_app_enter_pairing_mode();
            break;
        }
        case BT_APP_MODE_CONNECT:   // Connecting mode
        {
            u4PairedNum = a_bt_app_get_paired_src_device_num();
            if (u4PairedNum > 0)
            {
                /* Paired device exist, then auto link to last connected device */
                BT_APP_LOG_INFO(("<BT_APP> Connect mode : paired device exist, start auto link\n"));
                bt_app_enter_connecting_mode();
            }
            else
            {
                /* If there is no paired device, process is same as PAIR */
                BT_APP_LOG_INFO(("<BT_APP> Connect mode : no paired device, enter pairing mode.\n"));
                _bt_app_enter_pairing_mode();
            }
            break;
        }
        case BT_APP_MODE_PLAY:      // Playing mode
        {
            if(bt_app_input_a2dp_connected())
            {
                bt_app_set_flag_wait_x2_start_playback(FALSE);
                _bt_app_enter_playing_mode();
            }
            else    // If there is no connected device, enter Pairing mode.
            {
                BT_APP_LOG_DEFAULT(("<BT_APP> No connected device\n"));
                _bt_app_enter_pairing_mode();
            }
            break;
        }
    }

	return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_stop_bluetooth
  *
  * Description  - Close Bluetooth screen (stop Bluetooth mode).
  *
  * Inputs         - b_resume_home: specify whether Home is resumed after closing Bluetooth screen.
  *                                              If not, next screen will be shown by the caller.
  *                     e_reason: the reason to resume Home, this argument is used only when b_resume_home is TRUE.
  *---------------------------------------------------------------------------*/
INT32 bt_app_stop_bluetooth(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n", __FUNCTION__));

    BT_APP_LOG_DEFAULT(("<BT_APP> Stop BTM\n"));
    //i4_ret = a_mtkapi_bt_gap_stop(FALSE,FALSE);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: a_mtkapi_bt_gap_stop fail, %d\n", i4_ret));
    }

    if (bt_app_is_bluetooth_audio_function_start())
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d, BT function is started\n", __FUNCTION__, __LINE__));

        // clear flag and some info
        bt_app_set_running_status(AVRCP_PLAY_STATUS_MAX);
        bt_app_clear_media_info();
        bt_app_clear_playback_time();

        // stop timer
        bluetooth_progress_timer_bar_stop();
        bt_app_ui_stop_rssi_update_timer();

        _e_bluetooth_state = BLUETOOTH_BT_INVALID_STATE;

        // set flag to indicate bluetooth audio function exit
        bt_app_set_bluetooth_audio_function_start(FALSE);

        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d, exit BT function\n", __FUNCTION__, __LINE__));

    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Func:%s, Line:%d, BT function is NOT started\n", __FUNCTION__, __LINE__));
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n", __FUNCTION__));

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_connect
  *
  * Description  - try to connect the remote Bluetooth device
  *
  * Inputs         - ps_bt_mac: specify which device will be connected.
  *---------------------------------------------------------------------------*/
INT32 bt_app_connect(CHAR* ps_bt_mac)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_A2DP_ROLE local_role = BT_A2DP_ROLE_SRC;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if(NULL == ps_bt_mac)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return BT_APPR_INV_ARG;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Connect to: %s\n", ps_bt_mac));

    i4_ret = a_mtkapi_a2dp_connect(ps_bt_mac, local_role);

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_disconnect_with_src_dev
  *
  * Description  - disconnect A2DP connection from BDV, enter wait pair window after disconnected.
  *---------------------------------------------------------------------------*/
INT32 bt_app_disconnect_with_src_dev(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP> Func: %s\n", __FUNCTION__));

    // enter PAIRING mode
    //i4_ret = a_mtkapi_bt_gap_btstart("PAIRING", 300);
    BT_APP_LOG_ON_FAIL(i4_ret);

    return BT_APPR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_disconnect_with_sink_dev
  *
  * Description  - disconnect Output A2DP connection from BDV
  *---------------------------------------------------------------------------*/
INT32 bt_app_disconnect_with_sink_dev(VOID)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_TARGET_DEV_INFO r_target_dev_info = {0,0,{0},{0}};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func: %s\n",__FUNCTION__));

    /* Before disconnect, stop scaning */
    if (bt_app_is_sink_dev_scaning())
    {
        BT_APP_LOG_API(("<BT_APP><Sink_list> Stop scaning before disconnect sink device\n"));

        /* stop scan timer */
        bt_app_stop_sink_device_scan_timer();

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }

        bt_app_set_flag_sink_dev_scaning(FALSE);
    }

    /* Get connected device MAC info */
    //i4_ret = a_mtkapi_bt_gap_get_target_info(&r_target_dev_info);

    if (BT_APPR_OK == i4_ret)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Disconnect sink device:%s, MAC:%s\n", \
            r_target_dev_info.name, r_target_dev_info.bdAddr));

        // disconnect with sink device, both avrcp and a2dp
        i4_ret = a_mtkapi_a2dp_disconnect(r_target_dev_info.bdAddr);
        BT_APP_LOG_ON_FAIL(i4_ret);

        // enter PAIRING mode
        //i4_ret = a_mtkapi_bt_gap_btstart("PAIRING", 300);
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> No BT connection exist\n"));
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func: %s\n",__FUNCTION__));

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_connect_with_sink_dev
  *
  * Description  - connect with sink device from BDV
  *
  * Input          - b_auto_connection:
  *                     TRUE: connect to the last paired sink device
  *                     FALSE: connect to the selected sink device in sink device list
  *---------------------------------------------------------------------------*/
INT32 bt_app_connect_with_sink_dev(BOOL b_auto_connection, BT_TARGET_DEV_INFO* pt_target_device)
{
    INT32   i4_ret = BT_APPR_OK;
    BT_TARGET_DEV_INFO t_device = {0,0,{0},{0}};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    c_memset(&t_device, 0, sizeof(BT_TARGET_DEV_INFO));

    /* Before start connecting, stop scaning */
    if (bt_app_is_sink_dev_scaning())
    {
        BT_APP_LOG_API(("<BT_APP><Sink_list> Stop scaning before start connecting\n"));

        /* stop scan timer */
        bt_app_stop_sink_device_scan_timer();

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }

        bt_app_set_flag_sink_dev_scaning(FALSE);
    }

    /* Before new connection, stop previous connection */
    if (bt_app_output_a2dp_connected())
    {
        BT_APP_LOG_API(("<BT_APP><Sink_list> Stop previous connection before start new connection\n"));

        bt_app_set_flag_start_2nd_sink_connect(TRUE);

        bt_app_disconnect_with_sink_dev();

        BT_APP_LOG_API(("<BT_APP><Sink_list> New connection should be triggered after disconnect success\n"));

        //return i4_ret;
    }

    /* Get connected device MAC info */
    if (TRUE == b_auto_connection)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, Auto connect\n",__FUNCTION__));

        // connect to the latest paired sink device
        i4_ret = bt_app_get_latest_paired_sink_device(&t_device);
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> no paired sink device, exit auto connection\n"));
            return BT_APPR_TX_AUTO_CONNECTION_FAIL;
        }
        else
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Last paired sink device exist, start auto connection\n"));
        }
    }
    else
    {
        if (NULL == pt_target_device)
        {
            BT_APP_LOG_ERR(("<BT_APP> %s, invalid arg\n",__FUNCTION__));
            return BT_APPR_INV_ARG;
        }

        c_memcpy(&t_device, pt_target_device, sizeof(BT_TARGET_DEV_INFO));
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, t_device Mac address: %s\n",__FUNCTION__, t_device.bdAddr));
    }

    /* Start connecting mode before connect to device */
    //i4_ret = c_btm_btstart("CONNECTING", 15);
    if (i4_ret != BT_APPR_OK)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: c_btm_btstart : CONNECTING fail %d\n", i4_ret));
        return BT_APPR_FAIL;
    }

    /* Hide sink device list first, BLUETOOTH_BT_INVALID_STATE */
    if (bt_app_is_sink_dev_list_start()
        ||bt_app_is_audio_output_dev_list_start())
    {
        _e_bluetooth_state = BLUETOOTH_CONNECTING_STATE;
    }

    //indicate current connection triggered by platform is NOT input a2dp
    bt_app_set_flag_input_a2dp_initiator(FALSE);

    /* Connect to target device */
    i4_ret = bt_app_connect(t_device.bdAddr);

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_notify_input_a2dp_connect_to_x2
  *
  * Description  - Notify the event of receiving Input A2DP connection to  X2
  *---------------------------------------------------------------------------*/
VOID bt_app_notify_input_a2dp_connect_to_x2(VOID)
{
    if(pf_input_a2dp_connected_cbk_fct == NULL)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> pf_input_a2dp_connected_cbk_fct not reg\n"));
        return;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> notify X2: Input A2DP connect\n"));
    pf_input_a2dp_connected_cbk_fct();
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_notify_input_a2dp_disconnect_to_x2
  *
  * Description  - Notify the event of receiving Input A2DP disconnection to  X2
  *---------------------------------------------------------------------------*/
VOID bt_app_notify_input_a2dp_disconnect_to_x2(VOID)
{
    if(pf_input_a2dp_disconnected_cbk_fct == NULL)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> pf_input_a2dp_disconnected_cbk_fct not reg\n"));
        return;
    }

    pf_input_a2dp_disconnected_cbk_fct();
    BT_APP_LOG_DEFAULT(("<BT_APP> notify X2 iAPService: Input A2DP disconnect\n"));
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_notify_input_a2dp_avrcp_connect_to_x2
  *
  * Description  - Notify the event that A2DP and AVRCP are established to  X2
  *---------------------------------------------------------------------------*/
VOID bt_app_notify_input_a2dp_avrcp_connect_to_x2(VOID)
{
    if(pf_input_a2dp_avrcp_connected_cbk_fct == NULL)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> pf_input_a2dp_avrcp_connected_cbk_fct not reg\n"));
        return;
    }

    if(!bt_app_a2dp_avrcp_is_notified())
    {
        // Set flag
        bt_app_set_flag_a2dp_avrcp_is_notified(TRUE);

        BT_APP_LOG_DEFAULT(("<BT_APP> notify X2: Input A2DP and AVRCP connect\n"));
        pf_input_a2dp_avrcp_connected_cbk_fct();
    }
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_notify_output_a2dp_connect_to_x2
  *
  * Description  - Notify the event of receiving Output A2DP connection to  X2
  *---------------------------------------------------------------------------*/
VOID bt_app_notify_output_a2dp_connect_to_x2(VOID)
{
    BT_TARGET_DEV_INFO r_target_dev_info = {0,0,{0},{0}};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    //a_mtkapi_bt_gap_get_target_info(&r_target_dev_info);

    c_memset(ac_output_a2dp_target_name, 0, MAX_NAME_LEN);
    c_strncpy(ac_output_a2dp_target_name, r_target_dev_info.name, MAX_NAME_LEN-1);

    if (NULL != pf_output_a2dp_connected_cbk_fct)
    {
        pf_output_a2dp_connected_cbk_fct(ac_output_a2dp_target_name);
        BT_APP_LOG_DEFAULT(("<BT_APP> Notify X2: Output a2dp connect, Device name:%s\n",ac_output_a2dp_target_name));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Callback is unreg: Output a2dp connect, Device name:%s\n",ac_output_a2dp_target_name));
    }
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_notify_output_a2dp_disconnect_to_x2
  *
  * Description  - Notify the event of receiving Output A2DP disconnection to  X2
  *---------------------------------------------------------------------------*/
VOID bt_app_notify_output_a2dp_disconnect_to_x2(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if (NULL != pf_output_a2dp_disconnected_cbk_fct)
    {
        pf_output_a2dp_disconnected_cbk_fct(ac_output_a2dp_target_name);
        BT_APP_LOG_DEFAULT(("<BT_APP> Notify X2: Output a2dp disconnect, Device name:%s\n",ac_output_a2dp_target_name));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> Callback is unreg: Output a2dp disconnect, Device name:%s\n",ac_output_a2dp_target_name));
    }
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_notify_nfc_detected_to_x2
  *
  * Description  - Notify the event of NFC touch
  *---------------------------------------------------------------------------*/
VOID bt_app_notify_nfc_detected_to_x2(VOID)
{
    if (NULL != pf_nfc_detected_cbk_fct)
    {
        pf_nfc_detected_cbk_fct();
        BT_APP_LOG_DEFAULT(("<BT_APP> notify X2: NFC touch is detected, X2 need to change bluetooth mode setting to Receiver if current mode is Transmitter\n"));
    }
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_notify_bt_cmd_key_to_x2
  *
  * Description  - Notify the event that PAIRING/CONNECTION key is pressed
  *---------------------------------------------------------------------------*/
VOID bt_app_notify_bt_cmd_key_to_x2(UINT8 u1_bt_cmd)
{

    if (NULL != pf_bt_cmd_cbk_fct)
    {
        pf_bt_cmd_cbk_fct(u1_bt_cmd);
        BT_APP_LOG_DEFAULT(("<BT_APP> notify X2: bluetoothCommand:%d\n",u1_bt_cmd));
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> mtkstub_bluetooth_command_cbk_fct is not registered\n"));
    }
}


/**---------------------------------------------------------------------------
  * Name          - _bt_app_sink_device_list_init
  *
  * Description  -
  *---------------------------------------------------------------------------*/
static INT32 _bt_app_sink_device_list_init()
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_DEFAULT(("<BT_APP><Sink_list> API: %s\n", __FUNCTION__));

    /* Check if bluetooth dongle exist or not */
    if(!_bt_check_bt_device())
    {
        BT_APP_LOG_ERR(("<BT_APP> No bluetooth device attached\n"));
        return BT_APPR_FAIL;
    }

    /* Turn on bluetooth RF */
    if(!a_bt_is_bluetooth_enabled())
    {
        a_bt_enable_disable(TRUE);
    }

    /* Set bluetooth mode to Transmitter mode */
    a_bt_bluetooth_mode_set(APP_CFG_BLUETOOTH_SWITCH_SOURCE);

    return i4_ret;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_sink_device_list_mode_selector
  *
  * Description  -
  *---------------------------------------------------------------------------*/
static INT32 bt_app_sink_device_list_mode_selector()
{
    INT32 i4_ret = BT_APPR_OK;

    //BT_MODE_TYPE e_mode = 0;

    //e_mode = a_mtkapi_bt_gap_get_mode();

    //BT_APP_LOG_API(("<BT_APP><Sink_list> Enter %s, e_mode:%d\n", __FUNCTION__, e_mode));
    BT_APP_LOG_API(("<BT_APP><Sink_list> Enter %s\n", __FUNCTION__));

    if (0) //(BT_MODE_CONNECTING == e_mode))
    {
        BT_APP_LOG_INFO(("<BT_APP><Sink_list> Connecting mode is selected\n"));
    }
    else
    {
        // if not connecting state, start scaning by default
        BT_APP_LOG_INFO(("<BT_APP><Sink_list> Pairing mode is selected\n"));

        // start pairing mode
        i4_ret = a_mtkapi_bt_gap_set_connectable_and_discoverable(TRUE, TRUE);
        if (i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: a_mtkapi_bt_gap_btstart : PAIRING fail %d\n", i4_ret));
            return BT_APPR_FAIL;
        }

        _e_bluetooth_state = BLUETOOTH_SINK_DEVICE_LIST_STATE;

        /* Start to scan sink device list */
        bt_app_start_a2dp_snk_inquiry_scan(TIME_OUT_SINK_DEVICE_GUI_SCAN);
    }

    return i4_ret;
}

/**-----------------------------------------------------------------------------------------
  * Name          - bt_app_start_sink_device_list
  *
  * Description  -
  *
  * Inputs         -
  *----------------------------------------------------------------------------------------*/
INT32 bt_app_start_sink_device_list(BT_DEVICE_LIST_TYPE_E list_type)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_API(("<BT_APP><Sink_list> Enter Func:%s, list_type:%d\n", __FUNCTION__, list_type));

    if(BT_DEVICE_LIST_TYPE_SINK == list_type)
    {
        BT_APP_LOG_API(("<BT_APP><Sink_list> Open sink device list is starting...\n"));
        bt_app_set_flag_sink_dev_list_start(TRUE);
    }
    else if(BT_DEVICE_LIST_TYPE_AUDIO_OUTPUT == list_type)
    {
        BT_APP_LOG_API(("<BT_APP><Sink_list> Open audio output device list is starting...\n"));
        bt_app_set_flag_audio_output_dev_list_start(TRUE);
    }

    /* Do the preparation setup for sink device list */
    _bt_app_sink_device_list_init();

    /* Clear sink device list information */
    bt_app_ui_sink_device_list_info_init();

    /* Select the correct mode */
    bt_app_sink_device_list_mode_selector();

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

/**-----------------------------------------------------------------------------------------
  * Name          - bt_app_close_sink_device_list
  *
  * Description  -
  *
  * Inputs         -
  *----------------------------------------------------------------------------------------*/
INT32 bt_app_close_sink_device_list(VOID)
{
    INT32 i4_ret = BT_APPR_OK;
    CHAR pre_appname[APP_NAME_MAX_LEN+1] = {0};

    BT_APP_LOG_API(("<BT_APP><Sink_list> Close sink device list is starting...\n"));

    /* If scaning is going, then stop it before exit sink device list */
    if (bt_app_is_sink_dev_scaning())
    {
        BT_APP_LOG_API(("<BT_APP><Sink_list> Stop scaning before exit sink device list\n"));

        /* stop scan timer */
        bt_app_stop_sink_device_scan_timer();

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }

        bt_app_set_flag_sink_dev_scaning(FALSE);
    }

    // set discoverable OFF when exit sink device list
    a_mtkapi_bt_gap_set_connectable_and_discoverable(TRUE, FALSE);

    _e_bluetooth_state = BLUETOOTH_BT_INVALID_STATE;

    /* Free unpaired sink device list */
    _bt_app_free_a2dp_snk_dev_list();

    bt_app_get_pre_appname(pre_appname);

    /* Clear flag when exit sink device list */
    if(bt_app_is_sink_dev_list_start())
    {
        bt_app_set_flag_sink_dev_list_start(FALSE);
    }

    if(bt_app_is_audio_output_dev_list_start())
    {
        bt_app_set_flag_audio_output_dev_list_start(FALSE);
    }

    if(bt_app_is_bluetooth_key_start())
    {
        bt_app_set_flag_start_list_by_bluetooth_key(FALSE);
    }

    return i4_ret;
}

/**-----------------------------------------------------------------------------------------
  * Name          - bt_app_system_key_proc
  *
  * Description  -
  *
  * Inputs         -
  *----------------------------------------------------------------------------------------*/
INT32 bt_app_system_key_proc(VOID)
{
    INT32 i4_ret = BT_APPR_OK;

    BT_APP_LOG_API(("<BT_APP> Enter %s\n", __FUNCTION__));

    if (bt_app_is_sink_dev_list_start()
        ||bt_app_is_audio_output_dev_list_start())
    {
        /* For bluetooth setting - sink device list */
        i4_ret = bt_app_close_sink_device_list();
    }
    else if (bt_app_is_bluetooth_audio_function_start())
    {
        /* For Bluetooth AUDIO function */
        i4_ret = bt_app_stop_bluetooth();
        BT_APP_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        BT_APP_LOG_ERR(("<BT_APP> %s, error case\n", __FUNCTION__));
    }

    return i4_ret;
}

INT32 bt_app_audio_output_dev_list_start(void)
{
    INT32 i4_ret = BT_APPR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter bt_app_audio_output_dev_list_start\n"));

    t_bt_msg.msg_type = BT_APP_MSG_REQ_START_SINK_DEVICE_LIST;
    t_bt_msg.ui4_data1= BT_DEVICE_LIST_TYPE_AUDIO_OUTPUT;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        return BT_APPR_FAIL;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit bt_app_audio_output_dev_list_start\n"));

    return i4_ret;
}

/*! \brief Start Bluetooth audio output device list screen
*
*  \retval ERRORCODE_OK is success.
*  \retval ERRORCODE_NORMAL_ERROR is error.
*
*/
ErrorCode bluetooth_audio_output_device_list_start(void)
{
    INT32 i4_ret = ERRORCODE_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter bluetooth_audio_output_device_list_start\n"));

    t_bt_msg.msg_type = BT_APP_MSG_REQ_START_SINK_DEVICE_LIST;
    t_bt_msg.ui4_data1= BT_DEVICE_LIST_TYPE_SINK;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        return ERRORCODE_NORMAL_ERROR;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit bluetooth_audio_output_device_list_start\n"));

    return ERRORCODE_OK;
}

/*! \brief Close Bluetooth audio output device list screen
*
*  \retval ERRORCODE_OK is success.
*  \retval ERRORCODE_NORMAL_ERROR is error.
*
*/
ErrorCode bluetooth_audio_output_device_list_close(void)
{
    INT32 i4_ret = ERRORCODE_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter bluetooth_audio_output_device_list_close\n"));

    t_bt_msg.msg_type = BT_APP_MSG_REQ_CLOSE_SINK_DEVICE_LIST;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        return ERRORCODE_NORMAL_ERROR;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit bluetooth_audio_output_device_list_close\n"));

    return ERRORCODE_OK;
}


/*! \brief Connect to the device with bt_addr
 *         If bt_addr is NULL, connect to the last device.
 *
 * \arg[in] bt_addr length=BLUETOOTH_DEVICE_ADDR_LEN
 *
 * \return true : success, false : error
 */
 BOOL bluetooth_audio_input_a2dp_connect(char* bt_addr)
{
    INT32 i4_ret = ERRORCODE_OK;
    BT_APP_MSG_T t_bt_msg = {0};
    UINT32   u1_addr_length = 0;
    CHAR *  pc_bt_addr = NULL;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    if (NULL != bt_addr)
    {
        // length validation
        u1_addr_length = c_strlen(bt_addr);
        if (BLUETOOTH_DEVICE_ADDR_LEN - 1 != u1_addr_length)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: %s, bt_addr length error:%d\n", __FUNCTION__, u1_addr_length));
            return FALSE;
        }
        else
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> %s, bt_addr: %s\n", __FUNCTION__, bt_addr));
        }

        // allocate memory for bt addr
        pc_bt_addr = (CHAR *)c_mem_alloc(BLUETOOTH_DEVICE_ADDR_LEN);
        if (NULL == pc_bt_addr)
        {
            BT_APP_LOG_ERR(("<BT_APP> ERR: alloc mem for bt_addr fail\n"));
            return FALSE;
        }
        else
        {
            c_memset(pc_bt_addr, 0, BLUETOOTH_DEVICE_ADDR_LEN);

            c_strncpy(pc_bt_addr, bt_addr, BLUETOOTH_DEVICE_ADDR_LEN - 1);

            t_bt_msg.ui4_data_size = BLUETOOTH_DEVICE_ADDR_LEN;
            t_bt_msg.pv_data = pc_bt_addr;

            BT_APP_LOG_INFO(("<BT_APP> Allocate mem for bt_addr success\n"));
        }
    }
    else
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> %s, bt_addr is NULL, connect to the last device\n", __FUNCTION__));
    }

    t_bt_msg.msg_type = BT_APP_MSG_REQ_INPUT_A2DP_CONNECT_DISCONNECT;
    t_bt_msg.ui4_msg_id = TRUE;//means connect a2dp

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        return FALSE;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));

    return TRUE;
}

/*! \brief Disconnect current device
*
* \return true : success, false : error
*/
BOOL bluetooth_audio_input_a2dp_disconnect()
{
    INT32 i4_ret = ERRORCODE_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter %s\n", __FUNCTION__));

    t_bt_msg.msg_type = BT_APP_MSG_REQ_INPUT_A2DP_CONNECT_DISCONNECT;
    t_bt_msg.ui4_msg_id = FALSE;//means disconnect a2dp

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        return FALSE;
    }

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit %s\n", __FUNCTION__));

    return TRUE;
}

/*! \brief Register to allow notifying which bluetoothCommand should be sent to mtk
*
* \arg[in] fct is callback to notify bluetoothCommand
* \return true : success, false : error
*
* Notify when PAIRING key or CONNECT key is pressed in some special condition.\n
*/
BOOL bluetooth_command_cbk_reg(mtkstub_bluetooth_command_cbk_fct fct)
{
    if (NULL != fct)
    {
        pf_bt_cmd_cbk_fct = fct;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*! \brief Unregister to stop notifying which bluetoothCommand should be sent to mtk
 *
 * \return true : success, false : error
 *
 */
 BOOL bluetooth_command_cbk_unreg(void)
{
    pf_bt_cmd_cbk_fct = NULL;

    return TRUE;
}

BOOL bluetooth_get_capability_cnt(unsigned char* cnt)
{
    INT32 i4_ret = PBR_OK;
    if (NULL == cnt)
    {
        DBG_ERROR_PLAYBACK(("<BT APP>bluetooth_get_capability_cnt, invalid argument\n"));
        return FALSE;
    }

    // TODO: houxian/damon porting
    //i4_ret = a_cfg_get_capability_cnt((UINT8*)cnt);
    if (PBR_OK != i4_ret)
    {
        DBG_ERROR_PLAYBACK(("<BT APP>bluetooth_get_capability_cnt failed\n"));
        return FALSE;
    }
    DBG_DEFAULT_PLAYBACK(("<BT APP>bluetooth_get_capability_cnt, cnt:%d\n",*cnt));

    return TRUE;
}

BOOL bluetooth_set_capability_cnt(unsigned char cnt)
{
    INT32 i4_ret = PBR_OK;

    DBG_DEFAULT_PLAYBACK(("<BT APP>bluetooth_set_capability_cnt, cnt:%d\n",cnt));

    // TODO: houxian/damon porting
    //i4_ret = a_cfg_set_capability_cnt((UINT8)cnt);
    if (PBR_OK != i4_ret)
    {
        DBG_ERROR_PLAYBACK(("<BT APP>bluetooth_set_capability_cnt failed\n"));
        return FALSE;
    }
    return TRUE;
}

ErrorCode bluetooth_audio_output_connect_start(void)
{
    CHAR current_appname[APP_NAME_MAX_LEN+1] = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> API: %s\n", __FUNCTION__));

    if(0 != a_bt_app_get_paired_sink_device_num())
    {
        if(bt_app_output_a2dp_connected())
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Last paired sink device exist, disconnect\n"));

            a_am_get_active_app(current_appname);
            bt_app_save_pre_appname(current_appname);

            bt_app_delay(300);

            bt_app_set_flag_start_2nd_sink_connect(FALSE);
            bt_app_disconnect_with_sink_dev();
        }
        else
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> Last paired sink device exist, connect\n"));
            bt_app_set_flag_start_list_by_bluetooth_key(TRUE);
            bt_app_connect_with_sink_dev(TRUE, NULL);
            bt_app_audio_output_dev_list_start();
        }
    }
    else
    {
        bt_app_set_flag_start_list_by_bluetooth_key(TRUE);
        bt_app_audio_output_dev_list_start();
    }

    return ERRORCODE_OK;
}

ErrorCode bluetooth_audio_output_connect_close(void)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> API: %s\n", __FUNCTION__));
    bt_app_set_flag_start_list_by_bluetooth_key(FALSE);
    bt_app_close_sink_device_list();

    return ERRORCODE_OK;
}


BOOL bluetooth_audio_output_a2dp_is_connected(void)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if(bt_app_output_a2dp_connected())
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

INT32  a_bt_register(bt_nfy_fct pf_nfy, VOID* pv_tag, UINT32* pui4_nfy_id)
{
    BT_MW_UTIL_NFY_CLIENT_T*        pt_bt_nfy    = t_g_bt_nfy;
    BT_MW_UTIL_NFY_CLIENT_T*        pt_client    = NULL;
    INT32                           i4_ret       = 0;
    UINT16                          ui2_i        = 0;
    BOOL                            b_found      = FALSE;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if (pf_nfy == NULL || pui4_nfy_id == NULL)
    {
        return BTR_INV_ARG;
    }

    bt_app_sema_lock();
    BT_APP_LOG_DEFAULT(("[BT]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        /* Find a free slot. */
        for (ui2_i = 0 ;
             ui2_i < (UINT16)BT_MAX_NUM_NOTIFY_CLIENT ;
             ui2_i++)
        {
            if (pt_bt_nfy[ui2_i].pf_notify == NULL)
            {
                b_found = TRUE;
                break;
            }
        }

        /* Not Found */
        if (!b_found)
        {
            i4_ret = BTR_FAIL;
            break;
        }

        /* Save the information into the slot. */
        pt_client = &(pt_bt_nfy[ui2_i]);

        /* usage flag */
        pt_client->pf_notify   = pf_nfy;
        pt_client->pv_tag      = pv_tag;
        pt_client->ui4_nfy_id  = ui2_i;

        /* return out the id */
        *pui4_nfy_id = (UINT32)ui2_i;

        /* Done */
        i4_ret = BTR_OK;
    } while(0);

    bt_app_sema_unlock();
    BT_APP_LOG_DEFAULT(("[BT]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

INT32  a_bt_unregister(UINT32 ui4_nfy_id)
{
    BT_MW_UTIL_NFY_CLIENT_T*        pt_bt_nfy    = t_g_bt_nfy;
    BT_MW_UTIL_NFY_CLIENT_T*        pt_client    = NULL;
    INT32                           i4_ret       = 0;

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    BT_APP_LOG_DEFAULT(("[BT]Unregister the id_%d notify.\r\n", ui4_nfy_id));

    if(ui4_nfy_id >= (UINT32)BT_MAX_NUM_NOTIFY_CLIENT)
    {
        return BTR_INV_ARG;
    }

    bt_app_sema_lock();
    BT_APP_LOG_DEFAULT(("[BT]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        /* Defeult is fail */
        i4_ret = BTR_FAIL;

        /* Load the client's information */
        pt_client = &(pt_bt_nfy[ui4_nfy_id]);

        /* Check usable. */
        if (pt_client->pf_notify == NULL)
        {
            i4_ret = BTR_FAIL;
            break;
        }

        /* Set it to unregister */
        pt_client->pf_notify = NULL;

        /* Done */
        i4_ret = BTR_OK;
    } while(0);

    bt_app_sema_unlock();
    BT_APP_LOG_DEFAULT(("[BT]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

BOOL a_bt_check_bt_device(VOID)
{
    return _bt_check_bt_device();
}

INT32 a_bt_status(BT_STATUS_T* pe_bt_status )
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    //BT_APP_LOG_DEFAULT(("[BT]Get current bt status.\r\n"));

    if (pe_bt_status == NULL)
    {
        return BTR_INV_ARG;
    }

    //BT_APP_LOG_DEFAULT(("[BT]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
    //bt_app_sema_lock();

    //_bt_check_bt_device();
    t_g_bt_status = BT_PLUG;
    *pe_bt_status = t_g_bt_status;

    //bt_app_sema_unlock();
    //BT_APP_LOG_DEFAULT(("[BT]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return BTR_OK;
}

INT32 a_bt_app_start_sink_device_list(BT_DEVICE_LIST_TYPE_E list_type)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    return bt_app_start_sink_device_list(list_type);
}

INT32 a_bt_app_connect_with_sink_dev(BOOL b_auto_connection, BT_TARGET_DEV_INFO* pt_target_device)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    return bt_app_connect_with_sink_dev(b_auto_connection, pt_target_device);

}

INT32 a_bt_app_connect_with_hid_dev(char* bt_mac)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    INT32 i4_ret       = 0;

    if (bt_mac == NULL)
    {
        return BTR_INV_ARG;
    }
    /* Before start connecting, stop scaning */
    if (bt_app_is_sink_dev_scaning())
    {
        BT_APP_LOG_API(("<BT_APP><> Stop scaning before start connecting\n"));

        /* stop scan timer */
        bt_app_stop_sink_device_scan_timer();

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }

        bt_app_set_flag_sink_dev_scaning(FALSE);
    }
    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return a_mtkapi_hidh_connect(bt_mac);
}
INT32 a_bt_app_disconnect_with_hid_dev(char* bt_mac)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    INT32 i4_ret       = 0;
    if (bt_mac == NULL)
    {
        return BTR_INV_ARG;
    }
    /* Before start connecting, stop scaning */
    if (bt_app_is_sink_dev_scaning())
    {
        BT_APP_LOG_API(("<BT_APP><> Stop scaning before start connecting\n"));

        /* stop scan timer */
        bt_app_stop_sink_device_scan_timer();

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }

        bt_app_set_flag_sink_dev_scaning(FALSE);
    }
    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return a_mtkapi_hidh_disconnect(bt_mac);


}
void a_bt_app_stop_scaning(void)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));
    INT32 i4_ret       = 0;

    /* if scaning, stop scaning */
    if (bt_app_is_sink_dev_scaning())
    {
        BT_APP_LOG_API(("<BT_APP><> Stop scaning before start connecting\n"));

        /* stop scan timer */
        bt_app_stop_sink_device_scan_timer();

        i4_ret = a_mtkapi_bt_gap_stop_inquiry_scan();
        if(i4_ret != BT_APPR_OK)
        {
            BT_APP_LOG_ERR(("<BT_APP><Sink_list> ERR: stop sink inquiry fail, %d\n", i4_ret));
        }

        bt_app_set_flag_sink_dev_scaning(FALSE);
    }
    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return;
}

INT32 a_bt_app_disconnect_with_sink_dev(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    return bt_app_disconnect_with_sink_dev();

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));
}

INT32 a_bt_app_on_off_proc(VOID)
{
    INT32 i4_ret = PBR_OK;
    BT_APP_MSG_T t_bt_msg = {0};

    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    t_bt_msg.msg_type = BT_APP_MSG_ON_OFF_PROC;

    i4_ret = bt_app_send_bt_msg_to_playback(&t_bt_msg);
    if (i4_ret != PBR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: send BT_APP_MSG_ON_OFF_PROC fail\n"));
    }

    return i4_ret;
}
INT32 a_bluetooth_pbk_audio_input_start(bluetoothAudioInputMode mode, UINT32 tosec)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    return bluetooth_pbk_audio_input_start(mode,tosec);

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));
}
INT32 a_bt_app_send_req_to_get_meta_data(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    return bt_app_send_req_to_get_meta_data();

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));
}
INT32 a_bt_app_send_req_to_get_playstatus(VOID)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    return bt_app_send_req_to_get_playstatus();

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));
}
INT32 a_bt_app_write_pin_code(CHAR *remote_bd_addr, pairing_key_value_t pin, int len)
{
    BT_APP_LOG_DEFAULT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    return 0; //c_btm_write_pin_code(remote_bd_addr,pin,len);

    BT_APP_LOG_DEFAULT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));
}

#ifdef APP_BLE_SUPPORT

/**-----------------------------------------------------------------------------
  * Name          - a_bt_app_set_suspend_mode
  *
  * Description  - Notify BT dongle to enter suspend/wakeup mode.
  *
  *
  *
  * Inputs        - 1 : enter suspend mode, 0 - entern wakeup mode.
  *
  * Returns       -
  *
  *---------------------------------------------------------------------------*/
INT32  a_bt_app_set_suspend_mode(BT_APP_SET_DONGLE_MODE_E e_bt_set_mode)
{
    return BT_APPR_OK;
}
#endif

BOOL bluetooth_driver_init_done(VOID)
{
    DBG_LOG_PRINT(("<BT_APP> Enter %s\n",__FUNCTION__));

    for(int i = 0; i < 600; i++)
    {
        if(0 == access("/tmp/bt_mod_inserted", 0) && _bt_check_bt_device())
        {
            DBG_LOG_PRINT(("<BT_APP> %s, bt_mod_inserted: %d\n",__FUNCTION__, i));
            return TRUE;
        }

        usleep(50000);
    }

    DBG_LOG_PRINT(("<BT_APP> Exit %s\n",__FUNCTION__));

    return FALSE;
}

BOOL a_bluetooth_driver_init_done(VOID)
{
    return bluetooth_driver_init_done();
}

INT32 a_bt_app_init(VOID)
{
    INT32   i4_ret = BT_APPR_OK;

    DBG_LOG_PRINT(("<BT_APP> Enter Func:%s\n",__FUNCTION__));

    if(TRUE == bluetooth_driver_init_done())
    {
        i4_ret = bluetooth_init();
        BT_APP_LOG_ON_FAIL(i4_ret);

        i4_ret = bluetooth_system_power_on_proc();
        BT_APP_LOG_ON_FAIL(i4_ret);

        bt_aud_sendmsg_to_ble_gatt(BT_MSG_TO_GATT_APP);
    }
    else
    {
        DBG_LOG_PRINT(("<BT_APP> %s, bluetooth_driver_init_done fail.\n",__FUNCTION__));
        i4_ret =  BT_APPR_FAIL;
    }

    DBG_LOG_PRINT(("<BT_APP> Exit Func:%s\n",__FUNCTION__));

    return i4_ret;
}

#endif

