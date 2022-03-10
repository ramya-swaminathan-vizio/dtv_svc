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
 * $RCSfile: bluetooth_global_vatiables.c,v $
 * $Revision: #2 $
 * $Date: 2015/10/24 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *       This file implements global variables.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

#include "u_common.h"
#include "u_bt_mw_gap.h"
#include "u_bt_mw_avrcp.h"

#include "bluetooth.h"
#include "bluetooth_global_variables.h"

#include "amb/a_amb.h"

// The flag specify whether Input A2DP is established or not.
static BOOL fg_bt_input_a2dp_connected = FALSE;

// The flag specify whether AVRCP is established, or not.
static BOOL fg_bt_avrcp_connected = FALSE;

// The flag specify whether the event that both A2DP and AVRCP are established has been notified to  X2.
static BOOL fg_bt_a2dp_avrcp_is_notified = FALSE;

// The flag specify whether playstatus has been ready in BT Manager
static BOOL fg_bt_play_status_is_ready = FALSE;

// The flag specify whether meta data has been ready
static BOOL fg_bt_meta_data_is_ready = FALSE;

// The flag specify whether it is necessary to send meta data request to SRC again.
// When playback starting, we need send requestion to SRC to get meta data.
// But, AVRCP connection may not been established at that time, 
// Then, request will fail, we need send it again when AVRCP 1.3 connection success.
static BOOL fg_need_send_meta_data_req_again = FALSE;

// The flag specify whether a bt device has been detected by NFC touch.
static BOOL _fg_bt_nfc_detected = FALSE;

// The flag specify whether detect PAIRING key
static BOOL _fg_bt_pairing_key_detected = FALSE;

// The flag specify whether bluetooth setting mode changed
static BOOL _fg_bt_setting_mode_changed = FALSE;

// Specify bluetooth playback running status (PLAY, PAUSE,  ...)
static BT_AVRCP_PLAY_STATUS _e_bt_running_status = AVRCP_PLAY_STATUS_MAX;

// The flag specify whether playback time is valid or not
static BOOL _fg_bt_playback_time_valid = FALSE;

// store media info for the current playing file
static BT_AVRCP_MEDIA_INFO tg_bt_mediainfo;

// When A2DP connected, MTK notify A2DP_CONNECTED to  X2, X2 will start playback after receiving it.
// This flag specify whether it is waiting X2 start playback. 
static BOOL _fg_bt_wait_x2_start_playback = FALSE;

// For receiver mode, SPP is connected after A2DP connect, some data is exchanged via SPP
// X2 judge the device is TV or not, if yes, bluetooth_audio_input_set_delay() would be called, if delay time > 0, then the device is TV.
static BOOL _fg_bt_input_a2dp_connected_with_TV = FALSE;

// This flag indicates that Bluetooth AUDIO function is started or not
static BOOL _fg_bt_bluetooth_audio_function_start = FALSE;

// This flag indicates that sink device list is started or not
static BOOL _fg_bt_sink_dev_list_start = FALSE;

// This flag indicates that audio output list is started or not
static BOOL _fg_bt_audio_output_dev_list_start = FALSE;

// This flag indicates that bluetooth key is started or not
static BOOL _fg_bt_bluetooth_key_start = FALSE;

// This flag indicates that sink device scaning is going or not
static BOOL _fg_bt_sink_dev_scaning = FALSE;

// The flag specify whether Output A2DP is established or not.
static BOOL fg_bt_output_a2dp_connected = FALSE;

// The flag specify whether HID is established or not.
static BOOL fg_bt_hid_connected = FALSE;

// The flag specify whether keyboadr&mouse is established or not.
static BOOL fg_bt_keyboard_mouse_connected = FALSE;

// This flag indicates that need to disconnect connected device and start to connect new device
static BOOL _fg_bt_new_connect_to_sink = FALSE;

// This flag indicates that whether need to show disconnec message when sink device disconnected
static BOOL _fg_bt_show_disconnect_message = TRUE;

// The flag specify whether our platform is initiator for current input a2dp connection
// TRUE: our platform is initiator for input a2dp connection, FALSE: our platform is acceptor
static BOOL fg_bt_input_a2dp_initiator = FALSE;

// The flag specify target device support SCMS-T or not
static BOOL fg_bt_target_support_scms_t = FALSE;

// The flag specify whether need to show W-EI03 "This content is not playable" in playback screen
static BOOL fg_bt_ui_need_show_content_protect_warn = FALSE;

// The flag indicate whether need to turn off BT RF after a2dp disconnect
static BOOL fg_bt_disable_bt_after_disconnect = FALSE;

// The flag indicate whether need to disconnect all spp after a2dp disconnect
static BOOL fg_bt_need_disconnect_all_spp = FALSE;

// the semaphore for bt connection/disconnection
static HANDLE_T h_sema_bt_a2dp_connect_disconnect = NULL_HANDLE;

// the semaphore for bt dongle attach
static HANDLE_T h_sema_bt_dongle_attach = NULL_HANDLE;

// The flag specify bt connection is allowed or not
static BOOL fg_bt_connectable = TRUE;

//mtk10963
static BOOL fg_bt_vol_tmp_display = FALSE;

static HANDLE_T h_sema_bt_app = NULL_HANDLE;

CHAR fg_bt_pre_appname[APP_NAME_MAX_LEN+1] = {0};

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_input_a2dp_connected
  *
  * Description  - set the flag which specify whether A2DP is established or not.
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_input_a2dp_connected(BOOL b_a2dp_connected)
{
    fg_bt_input_a2dp_connected = b_a2dp_connected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_input_a2dp_connected
  *
  * Description  - specify whether A2DP is established or not.
  *---------------------------------------------------------------------------*/
BOOL bt_app_input_a2dp_connected(VOID)
{
    return fg_bt_input_a2dp_connected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_output_a2dp_connected
  *
  * Description  - set the flag which specify whether Output A2DP is established or not.
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_output_a2dp_connected(BOOL b_a2dp_connected)
{
    fg_bt_output_a2dp_connected = b_a2dp_connected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_output_a2dp_connected
  *
  * Description  - specify whether Output A2DP is established or not.
  *---------------------------------------------------------------------------*/
BOOL bt_app_output_a2dp_connected(VOID)
{
    return fg_bt_output_a2dp_connected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_hid_connected
  *
  * Description  - set the flag which specify whether HID is established or not.
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_hid_connected(BOOL b_hid_connected)
{
    fg_bt_hid_connected = b_hid_connected;
}

BOOL bt_app_keyboard_mouse_connected(VOID)
{
    return fg_bt_keyboard_mouse_connected;
}

VOID bt_app_set_flag_keyboard_mouse_connected(BOOL b_keyboard_mouse_connected)
{
    fg_bt_keyboard_mouse_connected = b_keyboard_mouse_connected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_hid_connected
  *
  * Description  - specify whether HID is established or not.
  *---------------------------------------------------------------------------*/
BOOL bt_app_hid_connected(VOID)
{
    return fg_bt_hid_connected;
}

/*! \brief Get audio input a2dp connect status
 *
 * \return true : connected, false : disconnected
 *
 */
 BOOL bluetooth_audio_input_a2dp_is_connected(void)
{
    return fg_bt_input_a2dp_connected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_avrcp_connected
  *
  * Description  - set the flag which specify whether AVRCP is established or not.
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_avrcp_connected(BOOL b_avrcp_connected)
{
    fg_bt_avrcp_connected = b_avrcp_connected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_avrcp_connected
  *
  * Description  - specify whether AVRCP is established or not.
  *---------------------------------------------------------------------------*/
BOOL bt_app_avrcp_connected(VOID)
{
    return fg_bt_avrcp_connected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_a2dp_avrcp_is_notified
  *
  * Description  - when both A2DP and AVRCP are established, MTK need notify this event to  X2.
  *                     This API set the flag which specify whether this event has been notified to  X2.
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_a2dp_avrcp_is_notified(BOOL b_notified)
{
    fg_bt_a2dp_avrcp_is_notified = b_notified;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_a2dp_avrcp_is_notified
  *
  * Description  - when both A2DP and AVRCP are established, MTK need notify this event to  X2.
  *                     This API specify whether this event has been notified to  X2.
  *---------------------------------------------------------------------------*/
BOOL bt_app_a2dp_avrcp_is_notified(VOID)
{
    return fg_bt_a2dp_avrcp_is_notified;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_playstatus_ready_flag
  *
  * Description  - set the flag which specify whether play status has been ready in BT Manager
  *---------------------------------------------------------------------------*/
VOID bt_app_set_playstatus_ready_flag(BOOL b_play_status_is_ready)
{
    fg_bt_play_status_is_ready = b_play_status_is_ready;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_playstatus_is_ready
  *
  * Description  - specify whether play status has been ready in BT Manager
  *---------------------------------------------------------------------------*/
BOOL bt_app_playstatus_is_ready(VOID)
{
    return fg_bt_play_status_is_ready;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_meta_data_ready_flag
  *
  * Description  - set the flag which specify whether play status has been ready
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_meta_data_ready(BOOL b_meta_data_is_ready)
{
    fg_bt_meta_data_is_ready = b_meta_data_is_ready;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_meta_data_is_ready
  *
  * Description  - specify whether play status has been ready
  *---------------------------------------------------------------------------*/
BOOL bt_app_meta_data_is_ready(VOID)
{
    return fg_bt_meta_data_is_ready;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_meta_data_req_need_send_again
  *
  * Description  - set the flag which specify whether it is necessary to send meta data requestion 
  *                     to SRC again.
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_meta_data_req_need_send_again(BOOL b_meta_data_req_need_send_again)
{
    fg_need_send_meta_data_req_again = b_meta_data_req_need_send_again;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_meta_data_req_need_send_again
  *
  * Description  - specify whether it is necessary to send meta data requestion to SRC again.
  *---------------------------------------------------------------------------*/
BOOL bt_app_meta_data_req_need_send_again(VOID)
{
    return fg_need_send_meta_data_req_again;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_nfc_detected
  *
  * Description  - set the flag which specify whether a bt device has been detected by NFC touch.
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_nfc_detected(BOOL b_nfc_detected)
{
    _fg_bt_nfc_detected = b_nfc_detected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_nfc_detected
  *
  * Description  - specify whether a bt device has been detected by NFC touch.
  *---------------------------------------------------------------------------*/
BOOL bt_app_nfc_detected(VOID)
{
    return _fg_bt_nfc_detected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_pairing_key_detected
  *
  * Description  - Set flag specify whether detect PAIRING key
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_pairing_key_detected(BOOL b_pairing_key_detected)
{
    _fg_bt_pairing_key_detected = b_pairing_key_detected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_pairing_key_detected
  *
  * Description  - The flag specify whether detect PAIRING key
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_pairing_key_detected(VOID)
{
    return _fg_bt_pairing_key_detected;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_setting_mode_changed
  *
  * Description  - Set flag specify whether bluetooth mode is changed in setting
  *---------------------------------------------------------------------------*/
VOID bt_app_set_setting_mode_changed(BOOL b_change_setting)
{
    _fg_bt_setting_mode_changed = b_change_setting;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_setting_mode_changed
  *
  * Description  - The flag specify whether bluetooth mode is changed in setting
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_setting_mode_changed(VOID)
{
    return _fg_bt_setting_mode_changed;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_get_running_status
  *
  * Description  - set bluetooth playback running status (PLAY, PAUSE, STOP, ...)
  *---------------------------------------------------------------------------*/
INT32 bt_app_set_running_status(BT_AVRCP_PLAY_STATUS e_status)
{
    //bt_app_sema_lock();
    _e_bt_running_status = e_status;
    //bt_app_sema_unlock();

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_get_running_status
  *
  * Description  - get bluetooth playback running status (PLAY, PAUSE, STOP, ...)
  *---------------------------------------------------------------------------*/
BT_AVRCP_PLAY_STATUS bt_app_get_running_status(VOID)
{
    BT_AVRCP_PLAY_STATUS e_status = AVRCP_PLAY_STATUS_MAX;

    //bt_app_sema_lock();
    e_status = _e_bt_running_status;
    //bt_app_sema_unlock();
    
    return e_status;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_playback_time_valid
  *
  * Description  - specify whether playback time is valid.
  *---------------------------------------------------------------------------*/
BOOL bt_app_playback_time_valid(VOID)
{
    return _fg_bt_playback_time_valid;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_clear_playback_time
  *
  * Description  - clear playback time
  *---------------------------------------------------------------------------*/
VOID bt_app_clear_playback_time(VOID)
{
    // clear flag
    _fg_bt_playback_time_valid = FALSE;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_save_media_info
  *
  * Description  - save the media info for current playing file
  *---------------------------------------------------------------------------*/
INT32 bt_app_save_media_info(BT_AVRCP_MEDIA_INFO *pt_mediainfo)
{
    if(NULL == pt_mediainfo)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }
    
    bt_app_set_flag_meta_data_ready(TRUE);
    
    c_memcpy(&tg_bt_mediainfo, pt_mediainfo, sizeof(BT_AVRCP_MEDIA_INFO));

    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_clear_media_info
  *
  * Description  - clear media info
  *---------------------------------------------------------------------------*/
VOID bt_app_clear_media_info(VOID)
{
    // clear flag
    bt_app_set_flag_meta_data_ready(FALSE);
    bt_app_set_flag_meta_data_req_need_send_again(FALSE);

    // clear media info
    c_memset(&tg_bt_mediainfo, 0, sizeof(BT_AVRCP_MEDIA_INFO));
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_load_media_info
  *
  * Description  - get media info
  *---------------------------------------------------------------------------*/
INT32 bt_app_load_media_info(BT_AVRCP_MEDIA_INFO *pt_mediainfo)
{
    if(NULL == pt_mediainfo)
    {
        BT_APP_LOG_ERR(("<BT_APP> ERR: %s, invalid arg\n", __FUNCTION__));
        return PBR_INV_ARG;
    }
    
    c_memcpy(pt_mediainfo, &tg_bt_mediainfo, sizeof(BT_AVRCP_MEDIA_INFO));
    
    return PBR_OK;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_wait_x2_start_playback
  *
  * Description  - set the flag which specify whether it is waiting X2 start BT playback. 
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_wait_x2_start_playback(BOOL b_wait_x2_start_playback)
{
    BT_APP_LOG_INFO(("<BT_APP> %s(%s)\n",__FUNCTION__, (b_wait_x2_start_playback ? "TRUE" : "FALSE")));
    
    _fg_bt_wait_x2_start_playback = b_wait_x2_start_playback;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_wait_x2_start_playback
  *
  * Description  - specify whether it is waiting X2 start BT playback. 
  *                     This API is added for BDP00390512. 
  *                     If it is waiting X2 start BT playback, Vudu/Netflix/Browser must be stopped anyway.
  *---------------------------------------------------------------------------*/
BOOL bt_app_wait_x2_start_playback(VOID)
{
    return _fg_bt_wait_x2_start_playback;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_input_a2dp_connection_with_TV
  *
  * Description  - Set flag a2dp connected with TV or not in receiver mode.
  *       
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_input_a2dp_connection_with_TV(BOOL b_connect_with_TV)
{
    _fg_bt_input_a2dp_connected_with_TV = b_connect_with_TV;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_input_a2dp_connection_with_TV
  *
  * Description  - Return the flag indicate current a2dp connected with TV or not.
  *       
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_input_a2dp_connection_with_TV(VOID)
{
    return _fg_bt_input_a2dp_connected_with_TV;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_sink_dev_list_start
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_sink_dev_list_start(BOOL b_sink_list_start)
{
    _fg_bt_sink_dev_list_start = b_sink_list_start;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_sink_dev_list_start
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_sink_dev_list_start(VOID)
{
    return _fg_bt_sink_dev_list_start;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_audio_output_dev_list_start
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_audio_output_dev_list_start(BOOL b_audio_output_list_start)
{
    _fg_bt_audio_output_dev_list_start = b_audio_output_list_start;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_audio_output_dev_list_start
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_audio_output_dev_list_start(VOID)
{
    return _fg_bt_audio_output_dev_list_start;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_start_list_by_bluetooth_key
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_start_list_by_bluetooth_key(BOOL b_bluetooth_key_start)
{
    _fg_bt_bluetooth_key_start = b_bluetooth_key_start;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_bluetooth_key_start
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_bluetooth_key_start(VOID)
{
    return _fg_bt_bluetooth_key_start;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_bluetooth_audio_function_start
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
VOID bt_app_set_bluetooth_audio_function_start(BOOL b_bt_function_start)
{
    _fg_bt_bluetooth_audio_function_start = b_bt_function_start;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_bluetooth_audio_function_start
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_bluetooth_audio_function_start(VOID)
{
    return _fg_bt_bluetooth_audio_function_start;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_sink_dev_scaning
  *
  * Description  - Set flag sink device scaning is going.
  *       
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_sink_dev_scaning(BOOL b_scaning)
{
    _fg_bt_sink_dev_scaning = b_scaning;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_sink_dev_scaning
  *
  * Description  - Return the flag indicate sink device scaning state.
  *       
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_sink_dev_scaning(VOID)
{
    return _fg_bt_sink_dev_scaning;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_start_2nd_sink_connect
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_start_2nd_sink_connect(BOOL b_2nd_connect)
{
    _fg_bt_new_connect_to_sink = b_2nd_connect;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_is_2nd_sink_connect
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
BOOL bt_app_is_2nd_sink_connect(VOID)
{
    return _fg_bt_new_connect_to_sink;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_set_flag_show_disconnect_message
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
VOID bt_app_set_flag_show_disconnect_message(BOOL b_show_message)
{
    _fg_bt_show_disconnect_message = b_show_message;
}

/**---------------------------------------------------------------------------
  * Name          - bt_app_need_show_disconnect_message
  *
  * Description  - 
  *       
  *---------------------------------------------------------------------------*/
BOOL bt_app_need_show_disconnect_message(VOID)
{
    return _fg_bt_show_disconnect_message;
}

VOID bt_app_set_flag_input_a2dp_initiator(BOOL b_initiator)
{
    BT_APP_LOG_INFO(("<BT_APP> set input a2dp initiator:%d\n",b_initiator));
    
    fg_bt_input_a2dp_initiator = b_initiator;
}

BOOL bt_app_is_input_a2dp_initiator(VOID)
{
    return fg_bt_input_a2dp_initiator;
}

VOID bt_app_set_flag_target_support_scms_t(BOOL b_support_scms_t)
{   
    fg_bt_target_support_scms_t = b_support_scms_t;
}

BOOL bt_app_is_target_support_scms_t(VOID)
{
    return fg_bt_target_support_scms_t;
}

VOID bt_app_set_flag_show_content_protect_warn(BOOL b_show_warn)
{   
    fg_bt_ui_need_show_content_protect_warn = b_show_warn;
}

BOOL bt_app_need_show_content_protect_warn(VOID)
{
    return fg_bt_ui_need_show_content_protect_warn;
}

VOID bt_app_set_flag_disable_bt_after_disconnect(BOOL b_need_disable)
{
    BT_APP_LOG_INFO(("<BT_APP> %s:%d\n",__FUNCTION__, b_need_disable));
    
    fg_bt_disable_bt_after_disconnect = b_need_disable;
}

BOOL bt_app_need_disable_bt_after_disconnect(VOID)
{
    return fg_bt_disable_bt_after_disconnect;
}

VOID bt_app_set_flag_disconnect_all_spp(BOOL b_disconnect_spp)
{   
    fg_bt_need_disconnect_all_spp = b_disconnect_spp;
}

BOOL bt_app_need_disconnect_all_spp(VOID)
{
    return fg_bt_need_disconnect_all_spp;
}

// this mtkstub api will be called by x2 after bluetooth_audio_input_a2dp_connected_cbk_fct is called
BOOL bluetooth_audio_input_is_initiator(void)
{
    return fg_bt_input_a2dp_initiator;
}

INT32 bt_a2dp_disconnection_sema_create(VOID)
{
    INT32 i4_ret = OSR_OK;
    
    if (NULL_HANDLE == h_sema_bt_a2dp_connect_disconnect)
    {
        i4_ret = c_sema_create(&h_sema_bt_a2dp_connect_disconnect,
                               X_SEMA_TYPE_BINARY,
                               X_SEMA_STATE_LOCK);
        if(i4_ret != OSR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: create h_sema_bt_a2dp_connect_disconnect sema fail, %d\n", i4_ret));
        }
    }

    return i4_ret;
}

VOID bt_a2dp_disconnection_sema_lock(VOID)
{
    INT32 i4_ret = OSR_OK;

    if (NULL_HANDLE == h_sema_bt_a2dp_connect_disconnect)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: has not create h_sema_bt_a2dp_connect_disconnect sema\n"));
        return;
    }

    i4_ret = c_sema_lock(h_sema_bt_a2dp_connect_disconnect, X_SEMA_OPTION_WAIT);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: lock h_sema_bt_a2dp_connect_disconnect sema fail, %d\n", i4_ret));
    }
}

VOID bt_a2dp_disconnection_sema_unlock(VOID)
{
    INT32 i4_ret = 0;

    if (NULL_HANDLE == h_sema_bt_a2dp_connect_disconnect)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: has not create h_sema_bt_a2dp_connect_disconnect sema\n"));
        return;
    }

    i4_ret = c_sema_unlock(h_sema_bt_a2dp_connect_disconnect);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: unlock h_sema_bt_a2dp_connect_disconnect fail, %d\n", i4_ret));
    }
}

INT32 bt_app_dongle_attach_sema_create(VOID)
{
    INT32 i4_ret = OSR_OK;
    
    if (NULL_HANDLE == h_sema_bt_dongle_attach)
    {
        i4_ret = c_sema_create(&h_sema_bt_dongle_attach,
                               X_SEMA_TYPE_BINARY,
                               X_SEMA_STATE_LOCK);
        if(i4_ret != OSR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: create h_sema_bt_dongle_attach sema fail, %d\n", i4_ret));
        }
    }

    return i4_ret;
}

VOID bt_app_dongle_attach_sema_lock(VOID)
{
    INT32 i4_ret = OSR_OK;

    if (NULL_HANDLE == h_sema_bt_dongle_attach)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: has not create h_sema_bt_dongle_attach sema\n"));
        return;
    }

    i4_ret = c_sema_lock(h_sema_bt_dongle_attach, X_SEMA_OPTION_WAIT);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: lock h_sema_bt_dongle_attach sema fail, %d\n", i4_ret));
    }
}

VOID bt_app_dongle_attach_sema_unlock(VOID)
{
    INT32 i4_ret = 0;

    if (NULL_HANDLE == h_sema_bt_dongle_attach)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: has not create h_sema_bt_dongle_attach sema\n"));
        return;
    }

    i4_ret = c_sema_unlock(h_sema_bt_dongle_attach);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: unlock h_sema_bt_dongle_attach fail, %d\n", i4_ret));
    }
}

VOID bt_app_set_BtConnectable(BOOL b_connectalbe)
{   
    fg_bt_connectable = b_connectalbe;
}

BOOL bt_app_is_BtConnectable(VOID)
{
    return fg_bt_connectable;
}

VOID bt_app_set_vol_tmp_display(BOOL b_flag)
{   
    fg_bt_vol_tmp_display = b_flag;
}

BOOL bt_app_is_vol_tmp_display(VOID)
{
    return fg_bt_vol_tmp_display;
}

VOID bt_app_save_pre_appname(CHAR* current_appname)
{
    c_strncpy (fg_bt_pre_appname,current_appname,APP_NAME_MAX_LEN);
}

VOID bt_app_get_pre_appname(CHAR* pre_appname)
{
    c_strncpy (pre_appname,fg_bt_pre_appname,APP_NAME_MAX_LEN);
}

VOID bt_app_sema_create(VOID)
{
    INT32 i4_ret = OSR_OK;
    
    if (NULL_HANDLE == h_sema_bt_app)
    {
        i4_ret = c_sema_create(&h_sema_bt_app,
                               X_SEMA_TYPE_MUTEX,
                               X_SEMA_STATE_UNLOCK);
        if(i4_ret != OSR_OK)
        {
            BT_APP_LOG_DEFAULT(("<BT_APP> ERR: create app sema fail, %d\n", i4_ret));
        }
    }

    return;
}

VOID bt_app_sema_lock(VOID)
{
    INT32 i4_ret = OSR_OK;

    if (NULL_HANDLE == h_sema_bt_app)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: has not create spp buf sema\n"));
        return;
    }

    i4_ret = c_sema_lock(h_sema_bt_app, X_SEMA_OPTION_WAIT);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: lock spp buf sema fail, %d\n", i4_ret));
    }
	return;
}

VOID bt_app_sema_unlock(VOID)
{
    INT32 i4_ret = 0;

    if (NULL_HANDLE == h_sema_bt_app)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: has not create app sema\n"));
        return;
    }

    i4_ret = c_sema_unlock(h_sema_bt_app);
    if (i4_ret != OSR_OK)
    {
        BT_APP_LOG_DEFAULT(("<BT_APP> ERR: unlock app sema fail, %d\n", i4_ret));
    }
}

BOOL a_bt_app_output_a2dp_connected(VOID)
{
    return bt_app_output_a2dp_connected();
}

BOOL a_bt_app_keyboard_mouse_connected(VOID)
{
    return bt_app_keyboard_mouse_connected();
}

#endif

