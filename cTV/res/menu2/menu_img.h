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
 * $RCSfile: menu_img.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/4 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 3107d9e5056853ce751ff70872439fe6 $
 *
 * Description:
 *      This file contains the images used by the MENU application.
 *---------------------------------------------------------------------------*/
#ifndef _menu_img_h_
#define _menu_img_h_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_sets.h"

#include "menu_config.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
extern WGL_HIMG_TPL_T  h_g_menu_img_btn_red;
extern WGL_HIMG_TPL_T  h_g_menu_img_btn_green;
extern WGL_HIMG_TPL_T  h_g_menu_img_btn_yellow;
extern WGL_HIMG_TPL_T  h_g_menu_img_btn_blue;
extern WGL_HIMG_TPL_T  h_g_menu_img_btn_enter;
extern WGL_HIMG_TPL_T  h_g_menu_img_btn_exit;
extern WGL_HIMG_TPL_T  h_g_menu_img_btn_select;
extern WGL_HIMG_TPL_T  h_g_menu_img_btn_ok;

extern WGL_HIMG_TPL_T  h_g_menu_img_arrow_left;
extern WGL_HIMG_TPL_T  h_g_menu_img_arrow_right;
extern WGL_HIMG_TPL_T  h_g_menu_img_arrow_up;
extern WGL_HIMG_TPL_T  h_g_menu_img_arrow_down;

extern WGL_HIMG_TPL_T  h_g_menu_img_item_lr;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_lr_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_lr_disable;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_enter;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_enter_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_enter_disable;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_edit;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_edit_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_edit_disable;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_disable;

extern WGL_HIMG_TPL_T  h_g_menu_img_lock;
extern WGL_HIMG_TPL_T  h_g_menu_img_lock_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_unlock;
extern WGL_HIMG_TPL_T  h_g_menu_img_unlock_hlt;

extern WGL_HIMG_TPL_T  h_g_menu_img_skip;
extern WGL_HIMG_TPL_T  h_g_menu_img_skip_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_unskip;
extern WGL_HIMG_TPL_T  h_g_menu_img_unskip_hlt;

extern WGL_HIMG_TPL_T  h_g_menu_img_fav;
extern WGL_HIMG_TPL_T  h_g_menu_img_fav_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_nfav;
extern WGL_HIMG_TPL_T  h_g_menu_img_nfav_hlt;

extern WGL_HIMG_TPL_T  h_g_menu_img_wide_43;
extern WGL_HIMG_TPL_T  h_g_menu_img_wide_43_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_wide_169;
extern WGL_HIMG_TPL_T  h_g_menu_img_wide_169_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_wide_zoom1;
extern WGL_HIMG_TPL_T  h_g_menu_img_wide_zoom1_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_wide_zoom2;
extern WGL_HIMG_TPL_T  h_g_menu_img_wide_pan_scan;
extern WGL_HIMG_TPL_T  h_g_menu_img_wide_pan_scan_hlt;

extern WGL_HIMG_TPL_T  h_g_menu_img_bk0;
extern WGL_HIMG_TPL_T  h_g_menu_img_bk0_ex;
extern WGL_HIMG_TPL_T  h_g_menu_img_bk1;
extern WGL_HIMG_TPL_T  h_g_menu_img_bk2;
extern WGL_HIMG_TPL_T  h_g_menu_img_bk3;

extern WGL_HIMG_TPL_T  h_g_menu_img_pb_bk;
extern WGL_HIMG_TPL_T  h_g_menu_img_pb_bk_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_pb_bk_disable;

extern WGL_HIMG_TPL_T  h_g_menu_img_pb_bar;
extern WGL_HIMG_TPL_T  h_g_menu_img_pb_bar_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_pb_bar_disable;

extern WGL_HIMG_TPL_T  h_g_menu_img_pb_point;
extern WGL_HIMG_TPL_T  h_g_menu_img_pb_point_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_pb_point_disable;

extern WGL_HIMG_TPL_T  h_g_menu_img_home_img;
extern WGL_HIMG_TPL_T  h_g_menu_img_home_bar;
extern WGL_HIMG_TPL_T  h_g_menu_img_home_bar_hlt;

#ifdef APP_MJC_SUPPORT
extern WGL_HIMG_TPL_T  h_g_menu_img_mjc_txt_bk;
extern WGL_HIMG_TPL_T  h_g_menu_img_mjc_line_bk;
#endif

extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_icon;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_icon_hlt;

extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_stimer;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_stimer_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_mmp;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_mmp_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_wide;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_wide_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_audio;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_audio_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_tv;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_tv_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_pic;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_pic_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_par;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_par_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_sys;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_sys_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_cc;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_cc_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_photo;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_photo_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_logo;

extern WGL_HIMG_TPL_T  h_g_menu_img_item_bk;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_hlt_bk;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_bar_plain;
extern WGL_HIMG_TPL_T  h_g_menu_img_lt_arrow;
extern WGL_HIMG_TPL_T  h_g_menu_img_rt_arrow;
extern WGL_HIMG_TPL_T  h_g_menu_img_pg_blue;
extern WGL_HIMG_TPL_T  h_g_menu_img_pg_silver;
extern WGL_HIMG_TPL_T  h_g_menu_img_pg_silver_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_item_bk_large;

extern WGL_HIMG_TPL_T  h_g_menu_back_bar_bk_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_back_left_arrow;
extern WGL_HIMG_TPL_T  h_g_menu_back_bar_bk;

extern WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_bk;
extern WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_lock;
extern WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_lock_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_unlock;
extern WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_unlock_hlt;

extern WGL_HIMG_TPL_T  h_g_menu_img_msg_background;


extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_input;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_input_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_network;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_network_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_bluetooth;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_bluetooth_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_setting;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_menu_setting_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_more_item_bk;
extern WGL_HIMG_TPL_T  h_g_menu_img_more_item_hlt_bk;

extern WGL_HIMG_TPL_T  h_g_menu_lastshadow_new;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_audio;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_cc;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_devices;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_guided_setup;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_network;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_system;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_timers;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_tuner;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_picture;
extern WGL_HIMG_TPL_T  h_g_menu_img_settings_icon_user_manual;

extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_audio;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_cc;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_devices;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_guided_setup;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_network;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_system;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_timers;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_tuner;
extern WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_picture;
extern WGL_HIMG_TPL_T  h_g_menu_img_settings_icon_hlt_user_manual;


extern WGL_HIMG_TPL_T  h_g_menu_signal_lock;
extern WGL_HIMG_TPL_T  h_g_menu_signal_1of5;
extern WGL_HIMG_TPL_T  h_g_menu_signal_2of5;
extern WGL_HIMG_TPL_T  h_g_menu_signal_3of5;
extern WGL_HIMG_TPL_T  h_g_menu_signal_4of5;
extern WGL_HIMG_TPL_T  h_g_menu_signal_5of5;



extern  WGL_HIMG_TPL_T  h_g_menu_img_not_ava;

extern WGL_HIMG_TPL_T  h_g_menu_img_clear_memory_bk;
extern WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_unempty;
extern WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_unempty_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_empty;
extern WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_empty_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_fill_num_hlt;

/*3D setting*/
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_2d;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_2d_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_3d;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_3d_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_exit;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_exit_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_sbs;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_sbs_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_sensio;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_sensio_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_tb;
extern WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_tb_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_3D_output_mode_bkg;
extern WGL_HIMG_TPL_T  h_g_menu_img_3D_content_mode_bkg;
extern WGL_HIMG_TPL_T  h_g_menu_img_back_bar_bk_main;
extern WGL_HIMG_TPL_T  h_g_menu_img_homebar_main;

extern WGL_HIMG_TPL_T  h_g_menu_3d_setting_bk;
extern WGL_HIMG_TPL_T  h_g_menu_3d_setting_bk_hlt;

extern WGL_HIMG_TPL_T  h_g_menu_img_icon_unlock;
extern WGL_HIMG_TPL_T  h_g_menu_img_icon_lock;
extern WGL_HIMG_TPL_T  h_g_menu_img_connected_icon;
extern WGL_HIMG_TPL_T  h_g_menu_img_text_sep;
extern WGL_HIMG_TPL_T  h_g_menu_img_bar_background;

extern WGL_HIMG_TPL_T  h_g_menu_terms_arrow_down_off;
extern WGL_HIMG_TPL_T  h_g_menu_terms_arrow_down_on;
extern WGL_HIMG_TPL_T  h_g_menu_terms_arrow_up_off;
extern WGL_HIMG_TPL_T  h_g_menu_terms_arrow_up_on;
extern WGL_HIMG_TPL_T  h_g_menu_terms_box_off;
extern WGL_HIMG_TPL_T  h_g_menu_terms_box_on;
extern WGL_HIMG_TPL_T  h_g_menu_checkbox_off;
extern WGL_HIMG_TPL_T  h_g_menu_checkbox_board;
extern WGL_HIMG_TPL_T  h_g_menu_checkbox_on;
extern WGL_HIMG_TPL_T  h_g_menu_checkbox_on_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_checkbox_on_hlt_check;




extern WGL_HIMG_TPL_T  h_g_menu_img_eq_item_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_eq_item_nor;
extern WGL_HIMG_TPL_T  h_g_menu_img_eq_item_sel;
extern WGL_HIMG_TPL_T  h_g_menu_img_eq_item_ind;
extern WGL_HIMG_TPL_T  h_g_menu_img_eq_background;
extern WGL_HIMG_TPL_T  h_g_menu_img_eq_level;

extern WGL_HIMG_TPL_T  h_g_menu_img_list_item_leftarrow;
extern WGL_HIMG_TPL_T  h_g_menu_img_list_item_rightarrow;

/*For Channel Locks Image*/
extern WGL_HIMG_TPL_T  h_g_menu_img_lock_with_arrow;
extern WGL_HIMG_TPL_T  h_g_menu_img_unlock_with_arrow;
extern WGL_HIMG_TPL_T  h_g_menu_img_ch_lock;
extern WGL_HIMG_TPL_T  h_g_menu_img_ch_unlock;

extern WGL_HIMG_TPL_T  h_g_menu_img_ch_lst_arrow_up;
extern WGL_HIMG_TPL_T  h_g_menu_img_ch_lst_arrow_down;

extern WGL_HIMG_TPL_T  h_g_menu_title_bar_bk;
extern WGL_HIMG_TPL_T  h_g_menu_list_elem_bk;

extern WGL_HIMG_TPL_T  h_g_menu_record_bar;
extern WGL_HIMG_TPL_T  h_g_menu_green_bar;

extern WGL_HIMG_TPL_T  h_g_menu_img_tv_home_bar_bk;
extern WGL_HIMG_TPL_T  h_g_menu_img_tv_home_bar_focs;
extern WGL_HIMG_TPL_T  h_g_menu_img_text_entry;
extern WGL_HIMG_TPL_T  h_g_menu_img_last_shadow_new;
extern WGL_HIMG_TPL_T  h_g_menu_img_ethernet_off;
extern WGL_HIMG_TPL_T  h_g_menu_img_ethernet_on;
extern WGL_HIMG_TPL_T  h_g_menu_img_keypad_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_keypad_hlt_big;
extern WGL_HIMG_TPL_T  h_g_menu_img_keypad_hlt_space;
extern WGL_HIMG_TPL_T  h_g_menu_img_lastshadow_new;
extern WGL_HIMG_TPL_T  h_g_menu_img_NewKeypad_bg;
extern WGL_HIMG_TPL_T  h_g_menu_img_TVRating_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_img_text_entry_large;
extern WGL_HIMG_TPL_T  h_g_menu_img_text_entry_small;
extern WGL_HIMG_TPL_T  h_g_menu_img_text_entry_small_1;
extern WGL_HIMG_TPL_T  h_g_menu_tvrating_bkgd_hlt;

/* wifi remote use */
extern WGL_HIMG_TPL_T  h_g_menu_icon_green;
extern WGL_HIMG_TPL_T  h_g_menu_icon_record;

/*color tuner*/
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_back;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_button_off;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_button_on;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_digit_arrows;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_digit_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_grid;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_left_arrow;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_left_arrow_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_right_arrow;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_right_arrow_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_passcode_entry;
extern WGL_HIMG_TPL_T  h_g_menu_passcode_entry_highlight;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_Button_box;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_test_back;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_test_back2;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_digit_hlt_new;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_top_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_top_arrows_hlt;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_RGB_bar;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_ColorOff;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_bottom_right;
extern WGL_HIMG_TPL_T  h_g_menu_img_WhiteBalanceTuner_grid;
extern WGL_HIMG_TPL_T  h_g_menu_img_ColorTuner_grid_test;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_with_rgb_back;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_digit_hlt_arrows;

extern WGL_HIMG_TPL_T  h_g_menu_color_tuner_2020;
extern WGL_HIMG_TPL_T  h_g_menu_white_balance_tuner_2020;

extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_Button_box_OFF_mov;
extern WGL_HIMG_TPL_T  h_g_menu_ColorTuner_Button_box_On_mov;

/* picture position and size */
extern WGL_HIMG_TPL_T  h_g_menu_position_size_adjust;
extern WGL_HIMG_TPL_T  h_g_menu_adjust_position_down;
extern WGL_HIMG_TPL_T  h_g_menu_adjust_position_up;
extern WGL_HIMG_TPL_T  h_g_menu_adjust_position_left;
extern WGL_HIMG_TPL_T  h_g_menu_adjust_position_right;
extern WGL_HIMG_TPL_T  h_g_menu_adjust_size_vertical_add;
extern WGL_HIMG_TPL_T  h_g_menu_adjust_size_vertical_minus;
extern WGL_HIMG_TPL_T  h_g_menu_adjust_size_horizontal_add;
extern WGL_HIMG_TPL_T  h_g_menu_adjust_size_horizontal_minus;

/*for menu add new device*/
extern WGL_HIMG_TPL_T  h_g_menu_img_Remote_Key_Device_Power;
extern WGL_HIMG_TPL_T  h_g_menu_img_Text_clear_all;
extern WGL_HIMG_TPL_T  h_g_menu_img_Text_clear_all_hlt;
extern WGL_HIMG_TPL_T  h_g_warning_icon;
extern WGL_HIMG_TPL_T  h_g_Warning_Bar_button_hlt;
extern WGL_HIMG_TPL_T  h_g_Warning_Bar_button;
extern WGL_HIMG_TPL_T  h_g_arrow_bottom;
extern WGL_HIMG_TPL_T  h_g_arrow_left;
extern WGL_HIMG_TPL_T  h_g_arrow_right;
extern WGL_HIMG_TPL_T  h_g_arrow_up;
extern WGL_HIMG_TPL_T  h_g_ok_key_select;
extern WGL_HIMG_TPL_T  h_g_pw_enter_small;
extern WGL_HIMG_TPL_T  h_g_pw_enter_ipt_small;
extern WGL_HIMG_TPL_T  h_g_pw_enter_small_hlt;
extern WGL_HIMG_TPL_T  h_g_lock_pic_mode_Bar_big;
extern WGL_HIMG_TPL_T  h_g_tos_scrollbar;
extern WGL_HIMG_TPL_T  h_g_tos_scrollbar_indicator;
extern WGL_HIMG_TPL_T  h_g_menu_energy_Star;

#ifdef  APP_HDR_SUPPORT
extern WGL_HIMG_TPL_T  h_g_menu_dolby_vision_icon;
#endif

extern WGL_HIMG_TPL_T  h_g_menu_arrow_down_v2;
extern WGL_HIMG_TPL_T  h_g_menu_arrow_right_v2;
extern WGL_HIMG_TPL_T  h_g_menu_arrow_up_v2;
extern WGL_HIMG_TPL_T  h_g_menu_arrow_white_v2;
extern WGL_HIMG_TPL_T  h_g_menu_button_save_cancel_v2;
extern WGL_HIMG_TPL_T  h_g_menu_button_save_cancel_highlight;

/* MENU COMMON */
extern WGL_HIMG_TPL_T  h_g_menu_common_back_highlight_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_checkbox_background_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_checkbox_grey_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_checkbox_grey_checked_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_checkbox_white_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_checkbox_white_checked_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_circle_white;
extern WGL_HIMG_TPL_T  h_g_menu_common_circle_white_checked;
extern WGL_HIMG_TPL_T  h_g_menu_common_pair_text_eng;
extern WGL_HIMG_TPL_T  h_g_menu_common_pair_text_spa;
extern WGL_HIMG_TPL_T  h_g_menu_common_pair_text_fre;
extern WGL_HIMG_TPL_T  h_g_menu_common_forget_text_eng;
extern WGL_HIMG_TPL_T  h_g_menu_common_forget_text_spa;
extern WGL_HIMG_TPL_T  h_g_menu_common_forget_text_fre;


extern WGL_HIMG_TPL_T  h_g_menu_common_sidebar_background_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_sidebar_fullScreen_mask_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_VO_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_arrow_left_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_arrow_right_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_partial_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_slider_background_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_slider_indicator_v2;

extern WGL_HIMG_TPL_T  h_g_lock_grey_v2;
extern WGL_HIMG_TPL_T  h_g_lock_white_v2;
extern WGL_HIMG_TPL_T  h_g_unlock_grey_v2;
extern WGL_HIMG_TPL_T  h_g_unlock_white_v2;
extern WGL_HIMG_TPL_T  h_g_lock_white_hlt_v2;
extern WGL_HIMG_TPL_T  h_g_unlock_white_hlt_v2;

extern WGL_HIMG_TPL_T  h_g_ethernet_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_signal_half_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_signal_1_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_signal_2_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_signal_3_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_signal_4_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_signal_error_v2;

extern WGL_HIMG_TPL_T  h_g_wifi_25_grey_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_25_white_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_50_grey_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_50_white_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_75_grey_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_75_white_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_100_grey_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_100_white_v2;
extern WGL_HIMG_TPL_T  h_g_wifi_connected_v2;

extern WGL_HIMG_TPL_T  h_g_dialog_box_v2;
extern WGL_HIMG_TPL_T  h_g_dialog_button_gray_v2;
extern WGL_HIMG_TPL_T  h_g_dialog_button_highlight_v2;

extern WGL_HIMG_TPL_T  h_g_pic_color_tuner_digit_highligh_v2;
extern WGL_HIMG_TPL_T  h_g_pic_test_pattern_enable_highlight_v2;
extern WGL_HIMG_TPL_T  h_g_pic_color_tuner_top_highlight_v2;
extern WGL_HIMG_TPL_T  h_g_pic_size_pos_background_v2;
extern WGL_HIMG_TPL_T  h_g_pic_size_pos_remote_arrows_v2;
extern WGL_HIMG_TPL_T  h_g_pic_pos_remote_down_v2;
extern WGL_HIMG_TPL_T  h_g_pic_pos_remote_left_v2;
extern WGL_HIMG_TPL_T  h_g_pic_pos_remote_right_v2;
extern WGL_HIMG_TPL_T  h_g_pic_pos_remote_up_v2;
extern WGL_HIMG_TPL_T  h_g_pic_size_remote_horizontal_res_v2;
extern WGL_HIMG_TPL_T  h_g_pic_size_remote_horizontal_add_v2;
extern WGL_HIMG_TPL_T  h_g_pic_size_remote_vertical_res_v2;
extern WGL_HIMG_TPL_T  h_g_pic_size_remote_vertical_add_v2;
extern WGL_HIMG_TPL_T  h_g_pic_color_tuner_top_highlight_ex_v2;
extern WGL_HIMG_TPL_T  h_g_pic_color_tuner_right_arrow_v2;
extern WGL_HIMG_TPL_T  h_g_pic_color_tuner_left_arrow_v2;

extern WGL_HIMG_TPL_T  h_g_menu_system_pin_box_v2;
extern WGL_HIMG_TPL_T  h_g_menu_system_pin_box_highlight_v2;
extern WGL_HIMG_TPL_T  h_g_menu_system_pin_box_pwd_v2;
extern WGL_HIMG_TPL_T  h_g_menu_system_pin_box_pushed_v2;
extern WGL_HIMG_TPL_T  h_g_menu_system_pin_box_active_v2;
extern WGL_HIMG_TPL_T  h_g_menu_system_pin_box_inactive_v2;


extern WGL_HIMG_TPL_T  h_g_menu_common_select_hlt_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_item_hlt_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_eq_bk_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_audio_mode_v2;
extern WGL_HIMG_TPL_T  h_g_menu_common_white_progress_bar_v2;

extern WGL_HIMG_TPL_T  h_g_menu_ratings_bk_icon_v2;
extern WGL_HIMG_TPL_T  h_g_menu_ratings_lock_icon_v2;
extern WGL_HIMG_TPL_T  h_g_menu_ratings_unlock_icon_v2;
extern WGL_HIMG_TPL_T  h_g_pin_no_match_bkg;

extern WGL_HIMG_TPL_T  h_g_menu_img_main_bt_headphones;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_accessiblity;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_admin;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_audio;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_channels;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_network;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_picture;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_system;
extern WGL_HIMG_TPL_T  h_g_menu_img_main_user_manual;

extern WGL_HIMG_TPL_T  h_g_menu_img_main_tv_channels_grayed_out;

extern INT32 menu_init_image(VOID);

#endif /* _menu_img_h_ */
