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
 * $RCSfile: nav_img.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/8 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: fad6e0fd4edaccd0084a192f40b2c916 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_IMG_H_
#define _NAV_IMG_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_wgl_common.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

extern INT32 nav_img_create_vol_gradient_btm(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );

extern INT32 nav_img_create_vol_inactive(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_vol_zoom_inactive(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );

extern INT32 nav_img_create_vol_toast_box(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );

extern INT32 nav_img_create_hlt_bar_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_pwd_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_ch_list_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_prog_detail_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_ch_detail_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_cc_info_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_cc_info_icon_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_default_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_default_btn_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_default_btn_hlt_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_scr_svr_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_video_sel_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_fav_list_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_pop_music_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_docu_ui_osd_bk(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_signal_1of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_signal_2of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_signal_3of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_signal_4of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_signal_5of5(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_wired_connect(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_network_notconnect(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

#ifdef APP_CEC_SUPPORT
extern INT32 nav_img_cec_create_cmd_list_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_act_src_icon_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_stop_img (
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_play_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_eject_img(
					WGL_HIMG_TPL_T* 			ph_img_tpl
					);
extern INT32 nav_img_cec_create_pause_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_fast_forward_img (
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_fast_reverse_img (
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_skip_forward_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_skip_reverse_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_cec_create_deck_panel_img(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
#endif /* APP_NAV_CEC_SUPPORT */

#if defined (APP_UPG_SUPPORT) || defined (APP_NAV_REC_SUPPORT)
extern INT32 nav_img_create_upg_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_upg_hl_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_upg_back_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_upg_arrow_up_down_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_upg_exit_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_upg_power_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_upg_enter_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_upg_info_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_upg_scan_bar_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_upg_scroll_bar_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_upg_scroll_bar_focus_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_upg_scan_bar_level_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
#endif

#ifdef APP_NAV_REC_TSHIFT_SUPPORT
extern INT32 nav_img_create_1x_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_2x_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_4x_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_8x_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_16x_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_32x_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );

extern INT32 nav_img_create_tshift_scale_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );

extern INT32 nav_img_create_tshift_crnt_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
#endif

#ifdef APP_NAV_REC_PVR_SUPPORT
INT32 nav_img_create_record_icon_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
INT32 nav_img_create_pvr_line_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );

INT32 nav_img_create_pvr_line_littel_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
#endif

INT32 nav_img_create_nav_ib_info_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
INT32 nav_img_create_nav_ib_warning_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
INT32 nav_img_create_nav_ib_urgent_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );

#ifdef APP_NAV_REC_PVR_SCH_SUPPORT

extern INT32 nav_img_create_reminder_bk_img_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_reminder_exit_icon_tpl(
                    WGL_HIMG_TPL_T*             pt_img_tpl
                    );
extern INT32 nav_img_create_reminder_arrow_up_down_icon_tpl(
				   WGL_HIMG_TPL_T*			   pt_img_tpl
				   );
extern INT32 nav_img_create_reminder_add_icon_tpl(
				   WGL_HIMG_TPL_T*             pt_img_tpl
				   );

#endif /*APP_NAV_REC_PVR_SCH_SUPPORT*/

extern INT32 nav_img_create_upg_item_ok_icon_tpl(
                   WGL_HIMG_TPL_T*             pt_img_tpl
                   );
extern INT32 nav_img_create_upg_item_progress_icon_tpl(
                   WGL_HIMG_TPL_T*             pt_img_tpl
                   );
extern INT32 nav_img_create_upg_item_fail_icon_tpl(
                   WGL_HIMG_TPL_T*             pt_img_tpl
                   );
extern INT32 nav_img_create_vol_bar_audsys_bk(
                   WGL_HIMG_TPL_T*             ph_img_tpl
                   );

extern INT32 nav_img_create_vol_ctrl_off_bk(
                   WGL_HIMG_TPL_T*             ph_img_tpl
                   );

extern INT32 nav_img_create_pwd_dlg_bk(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern INT32 nav_img_create_pwd_dlg_input(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern INT32 nav_img_create_pwd_dlg_select(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );
extern INT32 nav_img_create_pop_warning_bk_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );
extern INT32 nav_img_create_pop_warning_btn_img_tpl(
                    WGL_HIMG_TPL_T*             ph_img_tpl
                    );

extern INT32 nav_img_create_revolt_misc_bk(
                   WGL_HIMG_TPL_T*             pt_img_tpl
                   );

extern INT32 nav_img_create_tuner_setup_bg(
                   WGL_HIMG_TPL_T*             pt_img_tpl
                   );

extern INT32 nav_img_create_tuner_track_mute_fill(
                   WGL_HIMG_TPL_T*             pt_img_tpl
                   );

extern INT32 nav_img_create_tuner_pb_bg_fill(
                   WGL_HIMG_TPL_T*             pt_img_tpl
                   );


extern INT32 nav_img_create_pwd_dlg_select_pin_box(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern INT32 nav_img_create_pwd_dlg_bk_white_line(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern INT32 nav_img_create_pwd_dlg_warning_icon(
                      WGL_HIMG_TPL_T*             ph_img_tpl
                      );

extern  INT32 nav_img_create_pwd_dlg_input_pin(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern  INT32 nav_img_create_remote_link_icon(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern  INT32 nav_img_create_remote_input_icon(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern  INT32 nav_img_create_remote_play_pause(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern  INT32 nav_img_create_retail_mode_vizio_logo(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );
extern  INT32 nav_img_create_pwd_dlg_no_match_pic(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );
extern INT32 nav_img_create_pwd_dlg_down_pic(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );
extern INT32 nav_img_create_pwd_dlg_cancel_focus_pic(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );
extern INT32 nav_img_create_pwd_dlg_cancel_inactive_pic(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );
extern INT32 nav_img_create_pwd_dlg_up_pic(
                     WGL_HIMG_TPL_T*             ph_img_tpl
                     );

extern INT32 nav_img_create_arrow_up_down_icon(
                   WGL_HIMG_TPL_T*             ph_img_tpl1,
                   WGL_HIMG_TPL_T*             ph_img_tpl2,
                   WGL_HIMG_TPL_T*             ph_img_tpl3
                   );

#endif /* _NAV_IMG_H_ */

