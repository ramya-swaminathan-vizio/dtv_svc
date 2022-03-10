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
 * $RCSfile: wzd_img.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 80d824ab48f4d49e3d38d28c8fc07509 $
 *
 * Description:
 *      This file contains the images used by the Wizard application.
 *---------------------------------------------------------------------------*/

#ifndef _WZD_IMG_H_
#define _WZD_IMG_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "c_wgl_image.h"

#include "app_util/a_common.h"

#include "res/wizard/wzd_img_cust.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
extern WGL_HIMG_TPL_T      h_g_wzd_img_error_iocn;
extern WGL_HIMG_TPL_T      h_g_wzd_divider_dotted;
extern WGL_HIMG_TPL_T      h_g_wzd_input_box_square;
extern WGL_HIMG_TPL_T      h_g_wzd_dlg_btn_icon_off;
extern WGL_HIMG_TPL_T      h_g_wzd_dlg_btn_icon_on;

extern WGL_HIMG_TPL_T      h_g_wzd_img_button_off_0;
extern WGL_HIMG_TPL_T      h_g_wzd_img_button_on_0;
extern WGL_HIMG_TPL_T      h_g_wzd_img_button_on_1;
extern WGL_HIMG_TPL_T      h_g_wzd_img_button_off_1;

extern WGL_HIMG_TPL_T      h_g_wzd_img_bk;                /* background */
extern WGL_HIMG_TPL_T      h_g_wzd_img_hl_bk;             /* highlight background */

extern WGL_HIMG_TPL_T      h_g_wzd_img_scan_bar_bk;       /* scan bar background */
extern WGL_HIMG_TPL_T      h_g_wzd_img_scan_bar_level;    /* scan bar level */

extern WGL_HIMG_TPL_T      h_g_wzd_img_trans;             /* fully transparent image */

extern WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_up;
extern WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_down;
extern WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lb_bg;
extern WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lb_ht;
extern WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lb_icon_ht;
extern WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lb_icon;
extern WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lang_lb_bg;
extern WGL_HIMG_TPL_T      h_g_wzd_img_tv_setup_small_frm_bg;
extern WGL_HIMG_TPL_T      h_g_wzd_img_tv_setup_small_frm_bg_ht;
extern WGL_HIMG_TPL_T      h_g_wzd_img_tv_setup_green_check;

extern WGL_HIMG_TPL_T      h_g_wzd_img_right_panel;

/* useless: bt and device setup */
extern WGL_HIMG_TPL_T      h_g_wzd_remote_control_red;
extern WGL_HIMG_TPL_T      h_g_wzd_remote_control_green;
extern WGL_HIMG_TPL_T      h_g_wzd_use_dev_pwr;
extern WGL_HIMG_TPL_T      h_g_wzd_dev_pwr;

extern WGL_HIMG_TPL_T      h_g_wzd_dropdown_bkg;
extern WGL_HIMG_TPL_T      h_g_wzd_dropdown_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_drop_down_arrow_up_on;
extern WGL_HIMG_TPL_T      h_g_wzd_drop_down_arrow_down_on;
extern WGL_HIMG_TPL_T      h_g_wzd_wps_logo;

/* common icons */
extern WGL_HIMG_TPL_T      	h_g_wzd_img_energy_star;

extern WGL_HIMG_TPL_T      	h_g_wzd_img_background;        /* Wizard background */
extern WGL_HIMG_TPL_T      	h_g_wzd_img_background_with_box;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_title_dash;
extern WGL_HIMG_TPL_T		h_g_wzd_img_full_screen_dialog;
extern WGL_HIMG_TPL_T		h_g_wzd_img_energystar_logo;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_dialog;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_button;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_button_highlight;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_checkbox_checked;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_checkbox_no_check;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_checkmark_white_dialog;
extern WGL_HIMG_TPL_T		h_g_wzd_img_warning_icon;
extern WGL_HIMG_TPL_T		h_g_wzd_img_text_box;
extern WGL_HIMG_TPL_T		h_g_wzd_img_text_box_hlt;
extern WGL_HIMG_TPL_T		h_g_wzd_img_text_box_cursor;
extern WGL_HIMG_TPL_T		h_g_wzd_img_text_box_asterisk;

/* select box widget */
extern WGL_HIMG_TPL_T  		h_g_wzd_img_select_box;
extern WGL_HIMG_TPL_T		h_g_wzd_img_select_box_highlight;

/* choose mode page */
extern WGL_HIMG_TPL_T      	h_g_wzd_simple_dialog_bk;
extern WGL_HIMG_TPL_T      	h_g_wzd_simple_dialog_btn_selected;
extern WGL_HIMG_TPL_T      	h_g_wzd_simple_dialog_btn_unselected;

/* remote setup page */
extern WGL_HIMG_TPL_T		h_g_wzd_img_remote;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_remote_pairing;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_remote_pairing_hands;
extern WGL_HIMG_TPL_T      	h_g_wzd_img_remote_pairing_with_hands;

/* network setup page */
extern WGL_HIMG_TPL_T	   	h_g_wzd_img_network_lock;
extern WGL_HIMG_TPL_T      	h_g_wzd_signal_1of5_bits;
extern WGL_HIMG_TPL_T      	h_g_wzd_signal_2of5_bits;
extern WGL_HIMG_TPL_T      	h_g_wzd_signal_3of5_bits;
extern WGL_HIMG_TPL_T      	h_g_wzd_signal_4of5_bits;
extern WGL_HIMG_TPL_T     	h_g_wzd_signal_5of5_bits;
extern WGL_HIMG_TPL_T      	h_g_wzd_tos_scroll_down;
extern WGL_HIMG_TPL_T      	h_g_wzd_tos_scroll_down_highlight;
extern WGL_HIMG_TPL_T      	h_g_wzd_tos_scroll_up;
extern WGL_HIMG_TPL_T      	h_g_wzd_tos_scroll_up_highlight;

/* registration page */
extern WGL_HIMG_TPL_T      h_g_wzd_img_textBox_register;
extern WGL_HIMG_TPL_T      h_g_wzd_img_textBox_register_highlight;
extern WGL_HIMG_TPL_T      h_g_wzd_img_text_focus;
extern WGL_HIMG_TPL_T      h_g_wzd_img_checkbox;
extern WGL_HIMG_TPL_T      h_g_wzd_img_checkbox_check;
extern WGL_HIMG_TPL_T      h_g_wzd_img_checkbox_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_checkbox_check_hlt;

/* device setup page */
extern WGL_HIMG_TPL_T      h_g_wzd_img_icon_comp_gray;
extern WGL_HIMG_TPL_T      h_g_wzd_img_icon_hdmi_gray;
extern WGL_HIMG_TPL_T      h_g_wzd_img_icon_comp_white;
extern WGL_HIMG_TPL_T      h_g_wzd_img_icon_hdmi_white;
extern WGL_HIMG_TPL_T      h_g_wzd_img_selectbox_small;
extern WGL_HIMG_TPL_T      h_g_wzd_img_selectbox_small_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_selectbox_small_1;
extern WGL_HIMG_TPL_T      h_g_wzd_img_checkmark_green_small;
extern WGL_HIMG_TPL_T      h_g_wzd_img_checkmark_green_large;
extern WGL_HIMG_TPL_T      h_g_wzd_img_Remote_Key_Device_Power;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_bluray;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_bluray_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_cable;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_cable_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_computer;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_computer_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_dvd;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_dvd_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_dvr;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_dvr_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_game;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_game_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_sat;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_sat_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_vcr;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_vcr_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_avr;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_avr_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_soundbar;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_soundbar_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_dropdown_brand_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_drop_down_background;
extern WGL_HIMG_TPL_T      h_g_wzd_img_dropdown_brand;
extern WGL_HIMG_TPL_T      h_g_wzd_img_dropdown_brand_scrollbar;

/*tv signal*/
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_cableBox;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_cableBox_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_satellite;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_satellite_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_antenna;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_antenna_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_coax;
extern WGL_HIMG_TPL_T      h_g_wzd_img_device_coax_hlt;
extern WGL_HIMG_TPL_T      h_g_wzd_img_scan_background;
extern WGL_HIMG_TPL_T      h_g_wzd_img_scan_progressBar;
extern WGL_HIMG_TPL_T      h_g_wzd_OK_key_select;

/*cable box RF*/
extern WGL_HIMG_TPL_T      h_g_wzd_input_icon_RF;
extern WGL_HIMG_TPL_T      h_g_wzd_input_icon_rf_white;

/* API's */
extern INT32 wzd_image_init (VOID);

#endif /* _WZD_IMG_H_ */
