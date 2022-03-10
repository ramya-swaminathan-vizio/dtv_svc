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
 * $RCSfile: bluetooth_msgproc.h,v $
 * $Revision: #1 $
 * $Date: 2015/10/17 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *      This file is the internal header file for bluetooth msgproc.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

#ifndef _BLUETOOTH_MSGPROC_H_
#define _BLUETOOTH_MSGPROC_H_

//#include "u_bluetooth.h"
//#include "c_bt_mw_manager.h"

typedef enum{
    BLUETOOTH_ENABLE_STATE,
    BLUETOOTH_MUSIC_PLAYBACK_STATE,
    BLUETOOTH_WAIT_PAIR_STATE,
    BLUETOOTH_SRC_DEVICE_LIST_STATE,            //src device list window in BT function
    BLUETOOTH_SINK_DEVICE_LIST_STATE,           //sink device list window
    BLUETOOTH_SINK_DEVICE_REMOVE_CONFIRM_STATE, //sink paired device remove confirm window
    BLUETOOTH_CONNECTING_STATE,                 //M-EI04 window
    BLUETOOTH_SRC_PLAYBACK_STATE,               //Represent playback window in source mode
    BLUETOOTH_BT_SRC_CONNECTED_STATE,           //M-EI07 window, when connected sink device success in B-EI05, should show connected msg 5s and return to D-EI06
    BLUETOOTH_BT_SRC_DISCONNECTED_STATE,        //M-EI03 window
    BLUETOOTH_BT_CONNECTION_FAIL_STATE,        //W-EI01 window
    BLUETOOTH_BT_INVALID_STATE
} BLUETOOTH_STATE_T;

extern BLUETOOTH_STATE_T                   _e_bluetooth_state;
extern BOOL   _b_ff_key_press;
extern BOOL   _b_fr_key_press;

extern BT_AVRCP_PLAY_STATUS bt_app_get_running_status(VOID);
extern INT32 bt_app_send_req_to_get_meta_data(VOID);

extern INT32 bt_app_send_req_to_get_playstatus(VOID);

extern INT32 bt_create_bluetooth_thread(VOID);
extern INT32 bluetooth_stop_all_media_engine(VOID);
extern INT32 bluetooth_progress_timer_bar_initial(VOID);
extern INT32 bluetooth_progress_timer_bar_start();
extern INT32 bluetooth_progress_timer_bar_stop();
extern INT32 bluetooth_volume_timer_start(UINT32 ui4_msecond);

extern INT32 bt_app_send_connected_device_name_to_ifcon(VOID);

extern INT32 bt_app_osc_play_select_proc(VOID);
extern INT32 bt_app_osc_stop_select_proc(VOID);

#if CONFIG_PTS_BLUETOOTH
extern VOID  bt_app_set_pts_test_flag(BOOL b_pts_test);
extern BOOL  bt_app_pts_test(VOID);
extern INT32 bt_app_osc_avrcp_connect_select_proc(OP_MENU_HANDLE_T  h_op_menu,
                                                     HANDLE_T          h_menu,
                                                     HANDLE_T          h_parent_menu,
                                                     INT32             i4_tag);
extern INT32 bt_app_osc_avctp_connect_select_proc(OP_MENU_HANDLE_T  h_op_menu,
                                           HANDLE_T          h_menu,
                                           HANDLE_T          h_parent_menu,
                                           INT32             i4_tag);
#endif

extern INT32 bt_app_remove_confirm_msgbox_exit_proc(BOOL b_remove, BOOL b_remove_all);
extern INT32 bt_app_power_confirm_msgbox_exit_proc(BOOL b_power_on);
extern INT32 bt_app_exit_osc_post_proc(VOID);

extern VOID bluetooth_avrcp_cmd_map_sircs_cmd(BT_AVRCP_CMD_TYPE bt_cmd_type,
                                                UINT8 *ui1_high_category_code,
                                                UINT8 *ui1_low_category_code,
                                                UINT8 *ui1_key_code);


#endif
#endif


