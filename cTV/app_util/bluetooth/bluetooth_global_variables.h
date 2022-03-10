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
 * $RCSfile: bluetooth_global_variables.h,v $
 * $Revision: #1 $
 * $Date: 2015/10/17 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *      This file is the internal header file for bluetooth variables.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

#ifndef _BLUETOOTH_GLOBAL_VARIABLES_H_
#define _BLUETOOTH_GLOBAL_VARIABLES_H_

#include "u_common.h"
//#include "u_bluetooth.h"

extern VOID  bt_app_set_flag_input_a2dp_connected(BOOL b_a2dp_connected);
extern BOOL  bt_app_input_a2dp_connected(VOID);

extern VOID bt_app_set_flag_output_a2dp_connected(BOOL b_a2dp_connected);
extern BOOL bt_app_output_a2dp_connected(VOID);

extern VOID bt_app_set_flag_hid_connected(BOOL b_hid_connected);
extern BOOL bt_app_hid_connected(VOID);

extern VOID bt_app_set_flag_output_a2dp_mute(BOOL b_output_a2dp_mute);
extern BOOL bt_app_output_a2dp_mute(VOID);


extern VOID  bt_app_set_flag_avrcp_connected(BOOL b_avrcp_connected);
extern BOOL  bt_app_avrcp_connected(VOID);

extern VOID  bt_app_set_flag_a2dp_avrcp_is_notified(BOOL b_notified);
extern BOOL  bt_app_a2dp_avrcp_is_notified(VOID);

extern VOID  bt_app_set_playstatus_ready_flag(BOOL b_play_status_is_ready);
extern BOOL  bt_app_playstatus_is_ready(VOID);

extern VOID  bt_app_set_flag_meta_data_ready(BOOL b_meta_data_is_ready);
extern BOOL  bt_app_meta_data_is_ready(VOID);

extern VOID  bt_app_set_flag_meta_data_req_need_send_again(BOOL b_meta_data_req_need_send_again);
extern BOOL  bt_app_meta_data_req_need_send_again(VOID);

extern VOID  bt_app_set_flag_nfc_detected(BOOL b_nfc_detected);
extern BOOL  bt_app_nfc_detected(VOID);

extern VOID bt_app_set_flag_pairing_key_detected(BOOL b_pairing_key_detected);
extern BOOL bt_app_is_pairing_key_detected(VOID);

extern VOID bt_app_set_setting_mode_changed(BOOL b_change_setting);
extern BOOL bt_app_is_setting_mode_changed(VOID);

extern INT32 bt_app_set_running_status(BT_AVRCP_PLAY_STATUS e_status);

extern BOOL  bt_app_playback_time_valid(VOID);
extern VOID  bt_app_clear_playback_time(VOID);

extern INT32 bt_app_save_media_info(BT_AVRCP_MEDIA_INFO *pt_mediainfo);
extern VOID  bt_app_clear_media_info(VOID);
extern INT32 bt_app_load_media_info(BT_AVRCP_MEDIA_INFO *pt_mediainfo);

extern VOID  bt_app_set_flag_wait_x2_start_playback(BOOL b_wait_x2_start_playback);

extern VOID bt_app_set_flag_input_a2dp_connection_with_TV(BOOL b_connect_with_TV);
extern BOOL bt_app_is_input_a2dp_connection_with_TV(VOID);

extern VOID bt_app_set_flag_sink_dev_list_start(BOOL b_sink_list_start);
extern BOOL bt_app_is_sink_dev_list_start(VOID);

extern VOID bt_app_set_flag_audio_output_dev_list_start(BOOL b_audio_output_list_start);
extern BOOL bt_app_is_audio_output_dev_list_start(VOID);

extern VOID bt_app_set_flag_start_list_by_bluetooth_key(BOOL b_bluetooth_key_start);
extern BOOL bt_app_is_bluetooth_key_start(VOID);

extern VOID bt_app_set_bluetooth_audio_function_start(BOOL b_bt_function_start);
extern BOOL bt_app_is_bluetooth_audio_function_start(VOID);

extern VOID bt_app_set_flag_sink_dev_scaning(BOOL b_scaning);
extern BOOL bt_app_is_sink_dev_scaning(VOID);

extern VOID bt_app_set_flag_start_2nd_sink_connect(BOOL b_2nd_connect);
extern BOOL bt_app_is_2nd_sink_connect(VOID);

extern VOID bt_app_set_flag_show_disconnect_message(BOOL b_show_message);
extern BOOL bt_app_need_show_disconnect_message(VOID);

extern VOID bt_app_set_flag_input_a2dp_initiator(BOOL b_initiator);
extern BOOL bt_app_is_input_a2dp_initiator(VOID);

extern VOID bt_app_set_flag_target_support_scms_t(BOOL b_support_scms_t);
extern BOOL bt_app_is_target_support_scms_t(VOID);

extern VOID bt_app_set_flag_show_content_protect_warn(BOOL b_show_warn);
extern BOOL bt_app_need_show_content_protect_warn(VOID);

extern VOID bt_app_set_flag_disable_bt_after_disconnect(BOOL b_need_disable);
extern BOOL bt_app_need_disable_bt_after_disconnect(VOID);

extern VOID bt_app_set_flag_disconnect_all_spp(BOOL b_disconnect_spp);
extern BOOL bt_app_need_disconnect_all_spp(VOID);

extern INT32 bt_a2dp_disconnection_sema_create(VOID);
extern VOID bt_a2dp_disconnection_sema_lock(VOID);
extern VOID bt_a2dp_disconnection_sema_unlock(VOID);

extern INT32 bt_app_dongle_attach_sema_create(VOID);
extern VOID bt_app_dongle_attach_sema_lock(VOID);
extern VOID bt_app_dongle_attach_sema_unlock(VOID);

extern VOID bt_app_set_BtConnectable(BOOL b_connectalbe);
extern BOOL bt_app_is_BtConnectable(VOID);

extern VOID bt_app_set_vol_tmp_display(BOOL b_flag);
extern BOOL bt_app_is_vol_tmp_display(VOID);

extern VOID bt_app_save_pre_appname(CHAR* current_appname);
extern VOID bt_app_get_pre_appname(CHAR* pre_appname);

extern VOID bt_app_sema_create(VOID);
extern VOID bt_app_sema_lock(VOID);
extern VOID bt_app_sema_unlock(VOID);
extern BOOL bt_app_keyboard_mouse_connected(VOID);
extern BOOL bt_app_is_sink_dev_scaning(VOID);
extern VOID bt_app_set_flag_keyboard_mouse_connected(BOOL b_keyboard_mouse_connected);

#endif

#endif


