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
 * $RCSfile: wfd_view.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: hs_mingmingzhang $
 * $MD5HEX: 8ebc2c7a2c0fc209f18ef9bd3ccc4afd $
 *
 * Description:
 *         This header file contains public interfaces, constant and type
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/

#ifndef _WFD_VIEW_
#define _WFD_VIEW_

#include "res/app_util/config/a_cfg_custom.h"
#include "res/wfd/gen/wfd_wfd_main_layout.h"
#include "res/wfd/gen/wfd_wfd_connect_layout.h"
#include "res/wfd/gen/wfd_wfd_status_layout.h"
#include "res/wfd/gen/wfd_wfd_play_layout.h"
#include "res/wfd/gen/wfd_wfd_msg_layout.h"
#include "../wfd.h"
#include "c_uc_str.h"
#include "wfd_view_msg.h"
#include "wfd_view_main.h"
#include "wfd_view_conn.h"
#include "wfd_view_mini.h"
#include "wfd_view_play.h"
#include "wfd_view_pin.h"
#include "wfd_view_sta.h"

typedef enum
{
    WFD_VIEW_MAIN = 0,
    WFD_VIEW_CONN ,
    WFD_VIEW_MINI,
    WFD_VIEW_PIN,
    WFD_VIEW_STATUS,
    WFD_VIEW_PLAY,
    WFD_VIEW_MSG,
    WFD_VIEW_END
}WFD_VIEW_FRM_T;

typedef enum
{
    WFD_VIEW_CMD_PLAY_HIDE_VOL_TXT,
    WFD_VIEW_CMD_PLAY_HIDE,

    WFD_VIEW_CMD_STA_LOAD,
    WFD_VIEW_CMD_END
}WFD_VIEW_CMD_T;


typedef struct _WFD_OSD_CONTENT_T
{
	HANDLE_T	 h_canvas;
	UINT32 		 ui4_canvas_width;
	UINT32 		 ui4_canvas_height;

    WFD_VIEW_FRM_T e_curr_view;
    WFD_VIEW_FRM_T e_last_view;
    UINT16       ui2_lang_id;

	HANDLE_T     h_main_frm;
    HANDLE_T     h_main_device_list;
	HANDLE_T     h_main_find;
	#if 0 /* DTV00535431 */
	HANDLE_T     h_main_show_sta;
    #endif
	HANDLE_T     h_conn_frm;
	HANDLE_T     h_conn_pbc;
	HANDLE_T     h_conn_show_pin;
	HANDLE_T     h_conn_enter_pin;

	HANDLE_T     h_mini_frm;
	HANDLE_T     h_mini_cont;
	HANDLE_T     h_mini_yes;
	HANDLE_T     h_mini_exit;

	HANDLE_T     h_pin_frm;
	HANDLE_T     h_pin_btn;
	HANDLE_T     h_pin_box;
	HANDLE_T     h_pin_btn_1;

	HANDLE_T     h_status_frm;
	HANDLE_T     h_status_btn1;
	HANDLE_T     h_status_btn2;
	HANDLE_T     h_status_back;
	HANDLE_T     h_status_load;
	HANDLE_T     h_status_show;

	HANDLE_T     h_play_frm;
	HANDLE_T     h_play_pause;
	HANDLE_T     h_play_vol_icon;
	HANDLE_T     h_play_vol_bar;
	HANDLE_T     h_play_stop;
	HANDLE_T     h_play_vol_txt;
	HANDLE_T     h_play_status;

    HANDLE_T     h_msg_frm;
    HANDLE_T     h_msg_cont1;
    HANDLE_T     h_msg_cont2;
    HANDLE_T     h_msg_yes;
    HANDLE_T     h_msg_cancel;

    HANDLE_T     h_timer_cec_sac;
    HANDLE_T     h_timer_play_hide;
    HANDLE_T     h_timer_sta_load;
    HANDLE_T     h_timer_time_out;

    HANDLE_T     h_timer_update_mute;
}WFD_OSD_CONTENT_T;

extern WFD_OSD_CONTENT_T t_g_wfd_view_main;

INT32 wfd_view_init(VOID);

INT32 wfd_view_deinit(VOID);

WFD_VIEW_FRM_T wfd_view_get_current_view(VOID);

INT32 wfd_view_send_cmd(WFD_CMD_CONT_T t_cmd);

INT32 wfd_view_toggle_show_view(WFD_VIEW_FRM_T e_view,BOOL b_show,BOOL b_update);

VOID _wfd_view_do_msg(VOID* param1, VOID* pv_msg_param,VOID* param2,VOID* param3);

INT32 wfd_view_return_connect_idx(VOID);

VOID wfd_view_set_current_view(WFD_VIEW_FRM_T e_view);

WFD_VIEW_FRM_T wfd_view_get_last_view(VOID);

#endif
