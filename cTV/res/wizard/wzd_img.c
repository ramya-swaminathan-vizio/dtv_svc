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
 * $RCSfile: wzd_img.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/8 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 99817b43420e3612064fa174fbcb27af $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "res/wizard/wzd_img.h"
#include "wizard/wzd_dbg.h"

/* image definitions */
#if defined(APP_COLOR_MODE_PALLET)
    #include "res/wizard/wzd_img_p.i"
#else /* 444 mode */
    #if defined(APP_OSD_640x720)
        #include "res/wizard/wzd_img_640x720_16bits.i"
    #else /* 1280 x 720 */
        #if defined(APP_OSD_960x540)
            #include "res/wizard/wzd_img_960x540_8888.i"
        #else
            #include "res/wizard/wzd_img_2013.i"
        #endif
    #endif
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
WGL_HIMG_TPL_T      h_g_wzd_img_error_iocn;
WGL_HIMG_TPL_T      h_g_wzd_divider_dotted;
WGL_HIMG_TPL_T      h_g_wzd_input_box_square;
WGL_HIMG_TPL_T      h_g_wzd_dlg_btn_icon_off;
WGL_HIMG_TPL_T      h_g_wzd_dlg_btn_icon_on;

WGL_HIMG_TPL_T      h_g_wzd_img_button_off_0;
WGL_HIMG_TPL_T      h_g_wzd_img_button_on_0;
WGL_HIMG_TPL_T      h_g_wzd_img_button_on_1;
WGL_HIMG_TPL_T      h_g_wzd_img_button_off_1;

WGL_HIMG_TPL_T      h_g_wzd_img_bk = NULL_HANDLE;       /* background */
WGL_HIMG_TPL_T      h_g_wzd_img_hl_bk = NULL_HANDLE;    /* highlight background */
WGL_HIMG_TPL_T      h_g_wzd_img_right_panel;
WGL_HIMG_TPL_T      h_g_wzd_img_trans = NULL_HANDLE;    /* fully transparent image */

WGL_HIMG_TPL_T      h_g_wzd_img_scan_bar_bk;       		/* scan bar background */
WGL_HIMG_TPL_T      h_g_wzd_img_scan_bar_level;    		/* scan bar level */

WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_up;
WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_down;
WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lb_bg;
WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lb_ht;
WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lb_icon_ht;
WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lb_icon;
WGL_HIMG_TPL_T      h_g_wzd_img_con_tv_lang_lb_bg;
WGL_HIMG_TPL_T      h_g_wzd_img_tv_setup_small_frm_bg;
WGL_HIMG_TPL_T      h_g_wzd_img_tv_setup_small_frm_bg_ht;
WGL_HIMG_TPL_T      h_g_wzd_img_tv_setup_green_check;

/* useless: bt and device setup */
WGL_HIMG_TPL_T      h_g_wzd_remote_control_red;
WGL_HIMG_TPL_T      h_g_wzd_remote_control_green;
WGL_HIMG_TPL_T      h_g_wzd_use_dev_pwr;
WGL_HIMG_TPL_T      h_g_wzd_dev_pwr;

WGL_HIMG_TPL_T      h_g_wzd_dropdown_bkg;
WGL_HIMG_TPL_T      h_g_wzd_dropdown_hlt;
WGL_HIMG_TPL_T      h_g_wzd_drop_down_arrow_up_on;
WGL_HIMG_TPL_T      h_g_wzd_drop_down_arrow_down_on;
WGL_HIMG_TPL_T      h_g_wzd_wps_logo;

/* common icons */
WGL_HIMG_TPL_T      h_g_wzd_img_background;        		/* Wizard background */
WGL_HIMG_TPL_T      h_g_wzd_img_background_with_box;

WGL_HIMG_TPL_T    	h_g_wzd_img_title_dash;
WGL_HIMG_TPL_T		h_g_wzd_img_full_screen_dialog;
WGL_HIMG_TPL_T		h_g_wzd_img_energystar_logo;
WGL_HIMG_TPL_T   	h_g_wzd_img_dialog;
WGL_HIMG_TPL_T    	h_g_wzd_img_button;
WGL_HIMG_TPL_T     	h_g_wzd_img_button_highlight;
WGL_HIMG_TPL_T    	h_g_wzd_img_checkbox_checked;
WGL_HIMG_TPL_T      h_g_wzd_img_checkbox_no_check;
WGL_HIMG_TPL_T  	h_g_wzd_img_checkmark_white_dialog;
WGL_HIMG_TPL_T		h_g_wzd_img_warning_icon;
WGL_HIMG_TPL_T		h_g_wzd_img_text_box;
WGL_HIMG_TPL_T		h_g_wzd_img_text_box_hlt;
WGL_HIMG_TPL_T		h_g_wzd_img_text_box_cursor;
WGL_HIMG_TPL_T		h_g_wzd_img_text_box_asterisk;

/* select box widget */
WGL_HIMG_TPL_T  	h_g_wzd_img_select_box;
WGL_HIMG_TPL_T		h_g_wzd_img_select_box_highlight;

/* choose mode page */
WGL_HIMG_TPL_T    	h_g_wzd_img_energy_star;
WGL_HIMG_TPL_T    	h_g_wzd_simple_dialog_bk;
WGL_HIMG_TPL_T    	h_g_wzd_simple_dialog_btn_selected;
WGL_HIMG_TPL_T    	h_g_wzd_simple_dialog_btn_unselected;

/* remote setup page */
WGL_HIMG_TPL_T		h_g_wzd_img_remote;
WGL_HIMG_TPL_T 		h_g_wzd_img_remote_pairing;
WGL_HIMG_TPL_T     	h_g_wzd_img_remote_pairing_hands;
WGL_HIMG_TPL_T      h_g_wzd_img_remote_pairing_with_hands;

/* network page */
WGL_HIMG_TPL_T      h_g_wzd_img_network_lock;
WGL_HIMG_TPL_T      h_g_wzd_signal_1of5_bits;
WGL_HIMG_TPL_T      h_g_wzd_signal_2of5_bits;
WGL_HIMG_TPL_T      h_g_wzd_signal_3of5_bits;
WGL_HIMG_TPL_T      h_g_wzd_signal_4of5_bits;
WGL_HIMG_TPL_T      h_g_wzd_signal_5of5_bits;
WGL_HIMG_TPL_T      h_g_wzd_tos_scroll_down;
WGL_HIMG_TPL_T      h_g_wzd_tos_scroll_down_highlight;
WGL_HIMG_TPL_T      h_g_wzd_tos_scroll_up;
WGL_HIMG_TPL_T      h_g_wzd_tos_scroll_up_highlight;

/* select box widget */
WGL_HIMG_TPL_T    	h_g_wzd_img_select_box;
WGL_HIMG_TPL_T      h_g_wzd_img_select_box_highlight;

/* registration page */
WGL_HIMG_TPL_T      h_g_wzd_img_textBox_register;
WGL_HIMG_TPL_T      h_g_wzd_img_textBox_register_highlight;
WGL_HIMG_TPL_T      h_g_wzd_img_text_focus;
WGL_HIMG_TPL_T      h_g_wzd_img_checkbox;
WGL_HIMG_TPL_T      h_g_wzd_img_checkbox_check;
WGL_HIMG_TPL_T      h_g_wzd_img_checkbox_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_checkbox_check_hlt;

/* device setup page */
WGL_HIMG_TPL_T      h_g_wzd_img_icon_comp_gray;
WGL_HIMG_TPL_T      h_g_wzd_img_icon_hdmi_gray;
WGL_HIMG_TPL_T      h_g_wzd_img_icon_comp_white;
WGL_HIMG_TPL_T      h_g_wzd_img_icon_hdmi_white;
WGL_HIMG_TPL_T      h_g_wzd_img_selectbox_small;
WGL_HIMG_TPL_T      h_g_wzd_img_selectbox_small_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_selectbox_small_1;
WGL_HIMG_TPL_T      h_g_wzd_img_checkmark_green_small;
WGL_HIMG_TPL_T      h_g_wzd_img_checkmark_green_large;
WGL_HIMG_TPL_T      h_g_wzd_img_Remote_Key_Device_Power;
WGL_HIMG_TPL_T      h_g_wzd_img_device_bluray;
WGL_HIMG_TPL_T      h_g_wzd_img_device_bluray_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_cable;
WGL_HIMG_TPL_T      h_g_wzd_img_device_cable_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_computer;
WGL_HIMG_TPL_T      h_g_wzd_img_device_computer_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_dvd;
WGL_HIMG_TPL_T      h_g_wzd_img_device_dvd_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_dvr;
WGL_HIMG_TPL_T      h_g_wzd_img_device_dvr_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_game;
WGL_HIMG_TPL_T      h_g_wzd_img_device_game_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_sat;
WGL_HIMG_TPL_T      h_g_wzd_img_device_sat_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_vcr;
WGL_HIMG_TPL_T      h_g_wzd_img_device_vcr_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_avr;
WGL_HIMG_TPL_T      h_g_wzd_img_device_avr_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_soundbar;
WGL_HIMG_TPL_T      h_g_wzd_img_device_soundbar_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_dropdown_brand_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_drop_down_background;
WGL_HIMG_TPL_T      h_g_wzd_img_dropdown_brand;
WGL_HIMG_TPL_T      h_g_wzd_img_dropdown_brand_scrollbar;

/*tv signal*/
WGL_HIMG_TPL_T      h_g_wzd_img_device_cableBox;
WGL_HIMG_TPL_T      h_g_wzd_img_device_cableBox_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_satellite;
WGL_HIMG_TPL_T      h_g_wzd_img_device_satellite_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_antenna;
WGL_HIMG_TPL_T      h_g_wzd_img_device_antenna_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_device_coax;
WGL_HIMG_TPL_T      h_g_wzd_img_device_coax_hlt;
WGL_HIMG_TPL_T      h_g_wzd_img_scan_background;
WGL_HIMG_TPL_T      h_g_wzd_img_scan_progressBar;
WGL_HIMG_TPL_T      h_g_wzd_OK_key_select;

/*cable box RF*/
WGL_HIMG_TPL_T      h_g_wzd_input_icon_RF;
WGL_HIMG_TPL_T      h_g_wzd_input_icon_rf_white;



/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

 /*----------------------------------------------------------------------------
 * Name: wzd_image_init
 *
 * Description: Initiate the images for Wizard application.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:  0                   Successful.
 *          -1                   Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_image_init (VOID)
{
    /* error iocn */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_error_iocn,
                                      & h_g_wzd_img_error_iocn));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_H_ONLY,
                                      & t_g_wzd_divider_dotted,
                                      & h_g_wzd_divider_dotted));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_HV,
                                      & t_g_wzd_input_box_square,
                                      & h_g_wzd_input_box_square));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_dlg_btn_icon_off,
                                      & h_g_wzd_dlg_btn_icon_off));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_dlg_btn_icon_on,
                                      & h_g_wzd_dlg_btn_icon_on));

    /* setting list item button on */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_button_on_0,
                                      & h_g_wzd_img_button_on_0));

    /* setting list item button off */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_button_off_0,
                                      & h_g_wzd_img_button_off_0));

    /* setting list item button on */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_button_on_1,
                                      & h_g_wzd_img_button_on_1));

    /* setting list item button off */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_button_off_1,
                                      & h_g_wzd_img_button_off_1));

    /* scan progress bar */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_scan_bar_bk,
                                      & h_g_wzd_img_scan_bar_bk));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_scan_bar_level,
                                      & h_g_wzd_img_scan_bar_level));

	/* wizard background */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_backgroud,
                                      & h_g_wzd_img_background));
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_background_with_box,
                                      & h_g_wzd_img_background_with_box));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_con_tv_lb_bg,
                                      & h_g_wzd_img_con_tv_lb_bg));       /* listbox background connected tv page */

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_con_tv_lb_ht,
                                      & h_g_wzd_img_con_tv_lb_ht));       /* listbox highlight connected tv page */

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_dlg_btn_icon_on,
                                      & h_g_wzd_img_con_tv_lb_icon_ht));  /* listbox icon highlight connected tv page */

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_dlg_btn_icon_off,
                                      & h_g_wzd_img_con_tv_lb_icon));     /* listbox icon connected tv page */

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_con_tv_lang_lb_bg,
                                      & h_g_wzd_img_con_tv_lang_lb_bg));  /* language listbox background connected tv page */

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_tv_setup_small_frm_off,
                                      & h_g_wzd_img_tv_setup_small_frm_bg));  /* Small frame background */

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_tv_setup_small_frm_on,
                                      & h_g_wzd_img_tv_setup_small_frm_bg_ht));  /* Small frame background */

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_tv_setup_green_check,
                                      & h_g_wzd_img_tv_setup_green_check));  /* Green check icon */

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_remote_control_red,
                                      & h_g_wzd_remote_control_red));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_remote_control_green,
                                      & h_g_wzd_remote_control_green));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_dev_pwr,
                                      & h_g_wzd_dev_pwr));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_simple_dialog_bk,
                                      & h_g_wzd_simple_dialog_bk));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_simple_btn_selected,
                                      & h_g_wzd_simple_dialog_btn_selected));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_simple_btn_unselected,
                                      & h_g_wzd_simple_dialog_btn_unselected));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
                                    &t_g_wzd_dropdown_bkg,
                                    &h_g_wzd_dropdown_bkg));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_dropdown_hlt,
                                    &h_g_wzd_dropdown_hlt));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_drop_down_arrow_up_on,
                                    &h_g_wzd_drop_down_arrow_up_on));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_drop_down_arrow_down_on,
                                    &h_g_wzd_drop_down_arrow_down_on));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_wps_logo,
                                    &h_g_wzd_wps_logo));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_img_energy_star,
                                    &h_g_wzd_img_energy_star));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_img_title_dash,
                                    &h_g_wzd_img_title_dash));  
                                    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_img_remote,
                                    &h_g_wzd_img_remote));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_img_remote_pairing,
                                    &h_g_wzd_img_remote_pairing));  
                                    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_img_remote_pairing_with_hands,
                                    &h_g_wzd_img_remote_pairing_with_hands));   
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wzd_img_remote_pairing_hands,
                                    &h_g_wzd_img_remote_pairing_hands));

    /* common icons */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      &t_g_wzd_img_full_screen_dialog,
                                      &h_g_wzd_img_full_screen_dialog));  
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      &t_g_wzd_img_energystar_logo,
                                      &h_g_wzd_img_energystar_logo));  

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      &t_g_wzd_img_dialog,
                                      &h_g_wzd_img_dialog));  
                                    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      &t_g_wzd_img_button,
                                      &h_g_wzd_img_button));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      &t_g_wzd_img_button_highlight,
                                      &h_g_wzd_img_button_highlight));   
                                    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      &t_g_wzd_img_checkbox_checked,
                                      &h_g_wzd_img_checkbox_checked)); 
                                    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      &t_g_wzd_img_checkbox_no_check,
                                      &h_g_wzd_img_checkbox_no_check));  

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      &t_g_wzd_img_checkmark_white_dialog,
                                      &h_g_wzd_img_checkmark_white_dialog));
       
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_warning_icon,
                                      & h_g_wzd_img_warning_icon));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_text_box,
                                      & h_g_wzd_img_text_box));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_text_box_hlt,
                                      & h_g_wzd_img_text_box_hlt));

	RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_text_box_cursor,
                                      & h_g_wzd_img_text_box_cursor));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_text_box_asterisk,
                                      & h_g_wzd_img_text_box_asterisk));

    /* network page */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_network_lock,
                                      & h_g_wzd_img_network_lock));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_signal_1of5,
                                      & h_g_wzd_signal_1of5_bits));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_signal_2of5,
                                      & h_g_wzd_signal_2of5_bits));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_signal_3of5,
                                      & h_g_wzd_signal_3of5_bits));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_signal_4of5,
                                      & h_g_wzd_signal_4of5_bits));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_signal_5of5,
                                      & h_g_wzd_signal_5of5_bits));

	RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_tos_scroll_down,
                                      & h_g_wzd_tos_scroll_down));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_tos_scroll_down_highlight,
                                      & h_g_wzd_tos_scroll_down_highlight));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_tos_scroll_up,
                                      & h_g_wzd_tos_scroll_up));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_tos_scroll_up_highlight,
                                      & h_g_wzd_tos_scroll_up_highlight));

    /* device setup page */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_select_box,
                                      & h_g_wzd_img_select_box));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_select_box_highlight,
                                      & h_g_wzd_img_select_box_highlight));									 

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_textBox_register,
                                      & h_g_wzd_img_textBox_register));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_textBox_register_highlight,
                                      & h_g_wzd_img_textBox_register_highlight));
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_text_focus,
                                      & h_g_wzd_img_text_focus));   

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_checkbox,
                                      & h_g_wzd_img_checkbox)); 

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_checkbox_check,
                                      & h_g_wzd_img_checkbox_check));   
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_checkbox_hlt,
                                      & h_g_wzd_img_checkbox_hlt)); 
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_checkbox_check_hlt,
                                      & h_g_wzd_img_checkbox_check_hlt));  
                                                                             
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_icon_comp_gray,
                                      & h_g_wzd_img_icon_comp_gray));   

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_icon_hdmi_gray,
                                      & h_g_wzd_img_icon_hdmi_gray)); 
                                                                             
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_icon_comp_white,
                                      & h_g_wzd_img_icon_comp_white));   

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_icon_hdmi_white,
                                      & h_g_wzd_img_icon_hdmi_white)); 

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_selectbox_small,
                                      & h_g_wzd_img_selectbox_small));   
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_selectbox_small_hlt,
                                      & h_g_wzd_img_selectbox_small_hlt)); 
									  
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_selectbox_small_1,
                                      & h_g_wzd_img_selectbox_small_1));
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_checkmark_green_small,
                                      & h_g_wzd_img_checkmark_green_small));  
                                                                           
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_checkmark_green_large,
                                      & h_g_wzd_img_checkmark_green_large));   
                                          
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_Remote_Key_Device_Power,
                                      & h_g_wzd_img_Remote_Key_Device_Power));                                    
                                                                
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_bluray,
                                      & h_g_wzd_img_device_bluray)); 

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_bluray_hlt,
                                      & h_g_wzd_img_device_bluray_hlt));   
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_cable,
                                      & h_g_wzd_img_device_cable)); 
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_cable_hlt,
                                      & h_g_wzd_img_device_cable_hlt));   
                                                                                                                 
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_computer,
                                      & h_g_wzd_img_device_computer));   

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_computer_hlt,
                                      & h_g_wzd_img_device_computer_hlt)); 

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_dvd,
                                      & h_g_wzd_img_device_dvd));   
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_dvd_hlt,
                                      & h_g_wzd_img_device_dvd_hlt));               
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_dvr,
                                      & h_g_wzd_img_device_dvr));  

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_dvr_hlt,
                                      & h_g_wzd_img_device_dvr_hlt));                                                                                                                   

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_game,
                                      & h_g_wzd_img_device_game));                                       

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_game_hlt,
                                      & h_g_wzd_img_device_game_hlt)); 

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_sat,
                                      & h_g_wzd_img_device_sat));   
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_sat_hlt,
                                      & h_g_wzd_img_device_sat_hlt)); 
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_vcr,
                                      & h_g_wzd_img_device_vcr));   
                                                                                                                 
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_vcr_hlt,
                                      & h_g_wzd_img_device_vcr_hlt));   

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_avr,
                                      & h_g_wzd_img_device_avr)); 

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_avr_hlt,
                                      & h_g_wzd_img_device_avr_hlt));   

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_soundbar,
                                      & h_g_wzd_img_device_soundbar)); 
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_soundbar_hlt,
                                      & h_g_wzd_img_device_soundbar_hlt));  
  
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_dropdown_brand_hlt,
                                      & h_g_wzd_img_dropdown_brand_hlt));  
                                      
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_drop_down_background,
                                      & h_g_wzd_img_drop_down_background));      
									  
	RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
								      & t_g_wzd_img_dropdown_brand,
								      & h_g_wzd_img_dropdown_brand));   
	
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_dropdown_brand_scrollbar,
                                      & h_g_wzd_img_dropdown_brand_scrollbar));  

    /*tv signal*/
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_cableBox,
                                      & h_g_wzd_img_device_cableBox)); 
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_cableBox_hlt,
                                      & h_g_wzd_img_device_cableBox_hlt));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_satellite,
                                      & h_g_wzd_img_device_satellite)); 
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_satellite_hlt,
                                      & h_g_wzd_img_device_satellite_hlt));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_antenna,
                                      & h_g_wzd_img_device_antenna));  
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_antenna_hlt,
                                      & h_g_wzd_img_device_antenna_hlt)); 
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_coax,
                                      & h_g_wzd_img_device_coax));  
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_device_coax_hlt,
                                      & h_g_wzd_img_device_coax_hlt));  
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_scan_background,
                                      & h_g_wzd_img_scan_background));  
    
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_img_scan_progressBar,
                                      & h_g_wzd_img_scan_progressBar));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_OK_key_select,
                                      & h_g_wzd_OK_key_select));
	
	/*cable box RF*/
	RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_input_icon_RF,
                                      & h_g_wzd_input_icon_RF));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                      & t_g_wzd_input_icon_rf_white,
                                      & h_g_wzd_input_icon_rf_white));
                                      
    RET_ON_ERR (wzd_image_cust_create());

    return 0;
}
