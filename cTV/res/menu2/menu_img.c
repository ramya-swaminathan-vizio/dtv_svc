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
 * $RCSfile: menu_img.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 3044c0dbc8a484b578f67fad31e6a60e $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "c_wgl_image.h"

#include "app_util/a_common.h"

#include "res/menu2/menu_img.h"
#include "res/menu2/menu_config.h"

/* image definition file */
#ifdef APP_COLOR_MODE_PALLET
    #include "res/menu2/menu_img_p.i"
#else
    #include "res/menu2/menu_img_2013.i"
#endif

#include "res/menu2/menu_img_v2.i"
#include "res/menu2/menu_img_2020_main_page.i"
#include "res/menu2/menu_images_oled.i"

#ifdef APP_HDR_SUPPORT
    #include "res/menu2/images_2021/dolby_vision_icon/dolby_vision_icon.i"
#endif

#include "res/menu2/images_2021/bt_common/menu_img_bt_common.i"

#include "menu2/menu_dbg.h"
#include "menu2/menu.h"

#define RET_ON_ERR(_expr) if(_expr != 0){return -1;}

/* external definition */
WGL_HIMG_TPL_T  h_g_menu_img_btn_red;               /* red button */
WGL_HIMG_TPL_T  h_g_menu_img_btn_green;             /* green button */
WGL_HIMG_TPL_T  h_g_menu_img_btn_yellow;            /* yellow button */
WGL_HIMG_TPL_T  h_g_menu_img_btn_blue;              /* blue button */
WGL_HIMG_TPL_T  h_g_menu_img_btn_enter;             /* enter button */
WGL_HIMG_TPL_T  h_g_menu_img_btn_exit;              /* exit button */
WGL_HIMG_TPL_T  h_g_menu_img_btn_select;            /* select button */
WGL_HIMG_TPL_T  h_g_menu_img_btn_ok;                /* ok buttern */

WGL_HIMG_TPL_T  h_g_menu_img_arrow_left;
WGL_HIMG_TPL_T  h_g_menu_img_arrow_right;
WGL_HIMG_TPL_T  h_g_menu_img_arrow_up;
WGL_HIMG_TPL_T  h_g_menu_img_arrow_down;

WGL_HIMG_TPL_T  h_g_menu_img_item_lr;
WGL_HIMG_TPL_T  h_g_menu_img_item_lr_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_item_lr_disable;
WGL_HIMG_TPL_T  h_g_menu_img_item_enter;
WGL_HIMG_TPL_T  h_g_menu_img_item_enter_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_item_enter_disable;
WGL_HIMG_TPL_T  h_g_menu_img_item_edit;
WGL_HIMG_TPL_T  h_g_menu_img_item_edit_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_item_edit_disable;
WGL_HIMG_TPL_T  h_g_menu_img_item_disable;

WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_2d;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_2d_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_3d;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_3d_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_exit;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_exit_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_sbs;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_sbs_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_sensio;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_sensio_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_tb;
WGL_HIMG_TPL_T  h_g_menu_img_3d_setting_tb_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_3D_content_mode_bkg;
WGL_HIMG_TPL_T  h_g_menu_img_3D_output_mode_bkg;
WGL_HIMG_TPL_T  h_g_menu_img_back_bar_bk_main;
WGL_HIMG_TPL_T  h_g_menu_img_homebar_main;



WGL_HIMG_TPL_T  h_g_menu_3d_setting_bk;
WGL_HIMG_TPL_T  h_g_menu_3d_setting_bk_hlt;

WGL_HIMG_TPL_T  h_g_menu_img_lock;
WGL_HIMG_TPL_T  h_g_menu_img_lock_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_unlock;
WGL_HIMG_TPL_T  h_g_menu_img_unlock_hlt;

WGL_HIMG_TPL_T  h_g_menu_img_skip;
WGL_HIMG_TPL_T  h_g_menu_img_skip_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_unskip;
WGL_HIMG_TPL_T  h_g_menu_img_unskip_hlt;

WGL_HIMG_TPL_T  h_g_menu_img_fav;
WGL_HIMG_TPL_T  h_g_menu_img_fav_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_nfav;
WGL_HIMG_TPL_T  h_g_menu_img_nfav_hlt;

WGL_HIMG_TPL_T  h_g_menu_img_wide_43;
WGL_HIMG_TPL_T  h_g_menu_img_wide_43_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_wide_169;
WGL_HIMG_TPL_T  h_g_menu_img_wide_169_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_wide_zoom1;
WGL_HIMG_TPL_T  h_g_menu_img_wide_zoom1_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_wide_zoom2;
WGL_HIMG_TPL_T  h_g_menu_img_wide_pan_scan;
WGL_HIMG_TPL_T  h_g_menu_img_wide_pan_scan_hlt;


WGL_HIMG_TPL_T  h_g_menu_img_bk0;
WGL_HIMG_TPL_T  h_g_menu_img_bk0_ex;
WGL_HIMG_TPL_T  h_g_menu_img_bk1;
WGL_HIMG_TPL_T  h_g_menu_img_bk2;
WGL_HIMG_TPL_T  h_g_menu_img_bk3;

WGL_HIMG_TPL_T  h_g_menu_img_pb_bk;
WGL_HIMG_TPL_T  h_g_menu_img_pb_bk_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_pb_bk_disable;

WGL_HIMG_TPL_T  h_g_menu_img_pb_bar;
WGL_HIMG_TPL_T  h_g_menu_img_pb_bar_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_pb_bar_disable;

WGL_HIMG_TPL_T  h_g_menu_img_pb_point;
WGL_HIMG_TPL_T  h_g_menu_img_pb_point_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_pb_point_disable;

WGL_HIMG_TPL_T  h_g_menu_img_home_img;
WGL_HIMG_TPL_T  h_g_menu_img_home_bar;
WGL_HIMG_TPL_T  h_g_menu_img_home_bar_hlt;

WGL_HIMG_TPL_T  h_g_menu_img_tv_home_bar_bk;
WGL_HIMG_TPL_T  h_g_menu_img_tv_home_bar_focs;
WGL_HIMG_TPL_T  h_g_menu_img_text_entry;
WGL_HIMG_TPL_T  h_g_menu_img_text_entry_large;
WGL_HIMG_TPL_T  h_g_menu_img_text_entry_small;
WGL_HIMG_TPL_T  h_g_menu_img_text_entry_small_1;



WGL_HIMG_TPL_T  h_g_menu_img_last_shadow_new;
WGL_HIMG_TPL_T  h_g_menu_img_ethernet_off;
WGL_HIMG_TPL_T  h_g_menu_img_ethernet_on;
WGL_HIMG_TPL_T  h_g_menu_img_keypad_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_keypad_hlt_big;
WGL_HIMG_TPL_T  h_g_menu_img_keypad_hlt_space;
WGL_HIMG_TPL_T  h_g_menu_img_lastshadow_new;
WGL_HIMG_TPL_T  h_g_menu_img_NewKeypad_bg;
WGL_HIMG_TPL_T  h_g_menu_img_TVRating_hlt;
WGL_HIMG_TPL_T  h_g_menu_checkbox_on_hlt;
WGL_HIMG_TPL_T  h_g_menu_x;
WGL_HIMG_TPL_T  h_g_menu_tvrating_bkgd_hlt;
WGL_HIMG_TPL_T  h_g_menu_new_arrow_up;
WGL_HIMG_TPL_T  h_g_menu_new_arrow_down;


/* wifi remote use */
WGL_HIMG_TPL_T  h_g_menu_icon_green;
WGL_HIMG_TPL_T  h_g_menu_icon_record;






#ifdef APP_MJC_SUPPORT
WGL_HIMG_TPL_T  h_g_menu_img_mjc_txt_bk;
WGL_HIMG_TPL_T  h_g_menu_img_mjc_line_bk;
#endif

WGL_HIMG_TPL_T  h_g_menu_img_inp_tv;
WGL_HIMG_TPL_T  h_g_menu_img_inp_av1;
WGL_HIMG_TPL_T  h_g_menu_img_inp_av2;
WGL_HIMG_TPL_T  h_g_menu_img_inp_comp;
WGL_HIMG_TPL_T  h_g_menu_img_inp_hdmi;
WGL_HIMG_TPL_T  h_g_menu_img_inp_pc;

WGL_HIMG_TPL_T  h_g_menu_img_main_menu_icon;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_icon_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_stimer;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_stimer_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_mmp;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_mmp_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_wide;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_wide_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_audio;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_audio_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_tv;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_tv_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_pic;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_pic_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_par;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_par_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_sys;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_sys_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_cc;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_cc_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_photo;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_photo_hlt;

WGL_HIMG_TPL_T  h_g_menu_img_main_menu_input;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_input_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_network;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_network_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_bluetooth;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_bluetooth_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_setting;
WGL_HIMG_TPL_T  h_g_menu_img_main_menu_setting_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_more_item_bk;
WGL_HIMG_TPL_T  h_g_menu_img_more_item_hlt_bk;

WGL_HIMG_TPL_T  h_g_menu_img_item_bk;
WGL_HIMG_TPL_T  h_g_menu_img_item_hlt_bk;
WGL_HIMG_TPL_T  h_g_menu_img_item_bar_plain;
WGL_HIMG_TPL_T  h_g_menu_img_item_bk_large;

WGL_HIMG_TPL_T  h_g_menu_img_pg_blue;
WGL_HIMG_TPL_T  h_g_menu_img_pg_silver;
WGL_HIMG_TPL_T  h_g_menu_img_pg_silver_hlt;

WGL_HIMG_TPL_T  h_g_menu_img_logo;
WGL_HIMG_TPL_T  h_g_menu_back_bar_bk_hlt;
WGL_HIMG_TPL_T  h_g_menu_back_left_arrow;

WGL_HIMG_TPL_T  h_g_menu_back_bar_bk;

WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_bk;
WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_lock;
WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_lock_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_unlock;
WGL_HIMG_TPL_T  h_g_menu_img_tv_rate_unlock_hlt;

WGL_HIMG_TPL_T  h_g_menu_img_msg_background;
WGL_HIMG_TPL_T  h_g_menu_img_not_ava;

WGL_HIMG_TPL_T  h_g_menu_img_clear_memory_bk;
WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_unempty;
WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_unempty_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_empty;
WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_empty_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_clrmem_pwd_fill_num_hlt;

/*network*/
WGL_HIMG_TPL_T  h_g_menu_img_text_sep;
WGL_HIMG_TPL_T  h_g_menu_img_icon_unlock;
WGL_HIMG_TPL_T  h_g_menu_img_icon_lock;
WGL_HIMG_TPL_T  h_g_menu_img_connected_icon;
WGL_HIMG_TPL_T  h_g_menu_img_bar_background;

/*Terms of Service*/
WGL_HIMG_TPL_T  h_g_menu_checkbox_board;
WGL_HIMG_TPL_T  h_g_menu_checkbox_on;
WGL_HIMG_TPL_T  h_g_menu_checkbox_off;
WGL_HIMG_TPL_T  h_g_menu_checkbox_on_hlt_check;

WGL_HIMG_TPL_T  h_g_menu_terms_arrow_up_on;
WGL_HIMG_TPL_T  h_g_menu_terms_arrow_up_off;
WGL_HIMG_TPL_T  h_g_menu_terms_arrow_down_off;
WGL_HIMG_TPL_T  h_g_menu_terms_arrow_down_on;
WGL_HIMG_TPL_T  h_g_menu_terms_box_off;
WGL_HIMG_TPL_T  h_g_menu_terms_box_on;

WGL_HIMG_TPL_T  h_g_menu_img_eq_item_hlt;
WGL_HIMG_TPL_T  h_g_menu_img_eq_item_nor;
WGL_HIMG_TPL_T  h_g_menu_img_eq_item_sel;
WGL_HIMG_TPL_T  h_g_menu_img_eq_item_ind;
WGL_HIMG_TPL_T  h_g_menu_img_eq_background;
WGL_HIMG_TPL_T  h_g_menu_img_eq_level;

WGL_HIMG_TPL_T  h_g_menu_img_list_item_leftarrow;
WGL_HIMG_TPL_T  h_g_menu_img_list_item_rightarrow;

/*For Channel Locks Image*/
WGL_HIMG_TPL_T  h_g_menu_img_lock_with_arrow;
WGL_HIMG_TPL_T  h_g_menu_img_unlock_with_arrow;
WGL_HIMG_TPL_T  h_g_menu_img_ch_lock;
WGL_HIMG_TPL_T  h_g_menu_img_ch_unlock;

WGL_HIMG_TPL_T  h_g_menu_img_ch_lst_arrow_up;
WGL_HIMG_TPL_T  h_g_menu_img_ch_lst_arrow_down;

WGL_HIMG_TPL_T  h_g_menu_title_bar_bk;
WGL_HIMG_TPL_T  h_g_menu_list_elem_bk;

WGL_HIMG_TPL_T  h_g_menu_record_bar;
WGL_HIMG_TPL_T  h_g_menu_green_bar;

WGL_HIMG_TPL_T  h_g_menu_lastshadow_new;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_audio;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_cc;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_devices;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_guided_setup;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_network;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_system;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_timers;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_tuner;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_picture;
WGL_HIMG_TPL_T  h_g_menu_img_settings_icon_user_manual;

WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_audio;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_cc;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_devices;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_guided_setup;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_network;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_system;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_timers;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_tuner;
WGL_HIMG_TPL_T  h_g_menu_settings_icon_hlt_picture;
WGL_HIMG_TPL_T  h_g_menu_img_settings_icon_hlt_user_manual;


WGL_HIMG_TPL_T  h_g_menu_signal_lock;
WGL_HIMG_TPL_T  h_g_menu_signal_1of5;
WGL_HIMG_TPL_T  h_g_menu_signal_2of5;
WGL_HIMG_TPL_T  h_g_menu_signal_3of5;
WGL_HIMG_TPL_T  h_g_menu_signal_4of5;
WGL_HIMG_TPL_T  h_g_menu_signal_5of5;

/*color tuner*/
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_back;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_button_off;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_button_on;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_digit_arrows;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_digit_hlt;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_grid;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_left_arrow;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_left_arrow_hlt;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_right_arrow;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_right_arrow_hlt;
WGL_HIMG_TPL_T  h_g_menu_passcode_entry;
WGL_HIMG_TPL_T  h_g_menu_passcode_entry_highlight;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_Button_box;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_test_back;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_test_back2;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_Button_box_OFF_mov;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_Button_box_On_mov;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_digit_hlt_new;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_top_hlt;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_top_arrows_hlt;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_RGB_bar;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_ColorOff;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_bottom_right;
WGL_HIMG_TPL_T  h_g_menu_img_ColorTuner_grid_test;
WGL_HIMG_TPL_T  h_g_menu_img_WhiteBalanceTuner_grid;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_with_rgb_back;
WGL_HIMG_TPL_T  h_g_menu_ColorTuner_digit_hlt_arrows;
WGL_HIMG_TPL_T  h_g_menu_color_tuner_2020;
WGL_HIMG_TPL_T  h_g_menu_white_balance_tuner_2020;


/* picture position and size */
WGL_HIMG_TPL_T  h_g_menu_position_size_adjust;
WGL_HIMG_TPL_T  h_g_menu_adjust_position_down;
WGL_HIMG_TPL_T  h_g_menu_adjust_position_up;
WGL_HIMG_TPL_T  h_g_menu_adjust_position_left;
WGL_HIMG_TPL_T  h_g_menu_adjust_position_right;
WGL_HIMG_TPL_T  h_g_menu_adjust_size_vertical_add;
WGL_HIMG_TPL_T  h_g_menu_adjust_size_vertical_minus;
WGL_HIMG_TPL_T  h_g_menu_adjust_size_horizontal_add;
WGL_HIMG_TPL_T  h_g_menu_adjust_size_horizontal_minus;

/*for menu add new device*/
WGL_HIMG_TPL_T  h_g_menu_img_Remote_Key_Device_Power;
WGL_HIMG_TPL_T  h_g_menu_img_Text_clear_all;
WGL_HIMG_TPL_T  h_g_menu_img_Text_clear_all_hlt;
WGL_HIMG_TPL_T  h_g_warning_icon;
WGL_HIMG_TPL_T  h_g_Warning_Bar_button_hlt;
WGL_HIMG_TPL_T  h_g_Warning_Bar_button;

WGL_HIMG_TPL_T  h_g_arrow_bottom;
WGL_HIMG_TPL_T  h_g_arrow_left;
WGL_HIMG_TPL_T  h_g_arrow_right;
WGL_HIMG_TPL_T  h_g_arrow_up;
WGL_HIMG_TPL_T  h_g_ok_key_select;
WGL_HIMG_TPL_T  h_g_pw_enter_small;
WGL_HIMG_TPL_T  h_g_pw_enter_ipt_small;
WGL_HIMG_TPL_T  h_g_pw_enter_small_hlt;
WGL_HIMG_TPL_T  h_g_lock_pic_mode_Bar_big;
WGL_HIMG_TPL_T  h_g_tos_scrollbar;
WGL_HIMG_TPL_T  h_g_tos_scrollbar_indicator;
WGL_HIMG_TPL_T  h_g_menu_energy_Star;
#ifdef APP_HDR_SUPPORT
WGL_HIMG_TPL_T  h_g_menu_dolby_vision_icon;
#endif

WGL_HIMG_TPL_T  h_g_menu_back_bar_bk_hlt_v2;
WGL_HIMG_TPL_T  h_g_menu_arrow_down_v2;
WGL_HIMG_TPL_T  h_g_menu_arrow_right_v2;
WGL_HIMG_TPL_T  h_g_menu_arrow_up_v2;
WGL_HIMG_TPL_T  h_g_menu_arrow_white_v2;
WGL_HIMG_TPL_T  h_g_menu_button_save_cancel_v2;
WGL_HIMG_TPL_T  h_g_menu_button_save_cancel_highlight;

/* MENU COMMON */
WGL_HIMG_TPL_T  h_g_menu_common_back_highlight_v2;
WGL_HIMG_TPL_T  h_g_menu_common_checkbox_background_v2;
WGL_HIMG_TPL_T  h_g_menu_common_checkbox_grey_v2;
WGL_HIMG_TPL_T  h_g_menu_common_checkbox_grey_checked_v2;
WGL_HIMG_TPL_T  h_g_menu_common_checkbox_white_v2;
WGL_HIMG_TPL_T  h_g_menu_common_checkbox_white_checked_v2;
WGL_HIMG_TPL_T  h_g_menu_common_circle_white;
WGL_HIMG_TPL_T  h_g_menu_common_circle_white_checked;
WGL_HIMG_TPL_T  h_g_menu_common_pair_text_eng;
WGL_HIMG_TPL_T  h_g_menu_common_pair_text_spa;
WGL_HIMG_TPL_T  h_g_menu_common_pair_text_fre;
WGL_HIMG_TPL_T  h_g_menu_common_forget_text_eng;
WGL_HIMG_TPL_T  h_g_menu_common_forget_text_spa;
WGL_HIMG_TPL_T  h_g_menu_common_forget_text_fre;

WGL_HIMG_TPL_T  h_g_menu_common_sidebar_background_v2;
WGL_HIMG_TPL_T  h_g_menu_common_sidebar_fullScreen_mask_v2;
WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_v2;
WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_VO_v2;
WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_arrow_left_v2;
WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_arrow_right_v2;
WGL_HIMG_TPL_T  h_g_menu_common_sidebar_highlight_partial_v2;
WGL_HIMG_TPL_T  h_g_menu_common_slider_background_v2;
WGL_HIMG_TPL_T  h_g_menu_common_slider_indicator_v2;

WGL_HIMG_TPL_T  h_g_lock_grey_v2;
WGL_HIMG_TPL_T  h_g_lock_white_v2;
WGL_HIMG_TPL_T  h_g_unlock_grey_v2;
WGL_HIMG_TPL_T  h_g_unlock_white_v2;
WGL_HIMG_TPL_T  h_g_lock_white_hlt_v2;
WGL_HIMG_TPL_T  h_g_unlock_white_hlt_v2;

WGL_HIMG_TPL_T  h_g_ethernet_v2;
WGL_HIMG_TPL_T  h_g_wifi_signal_half_v2;
WGL_HIMG_TPL_T  h_g_wifi_signal_1_v2;
WGL_HIMG_TPL_T  h_g_wifi_signal_2_v2;
WGL_HIMG_TPL_T  h_g_wifi_signal_3_v2;
WGL_HIMG_TPL_T  h_g_wifi_signal_4_v2;
WGL_HIMG_TPL_T  h_g_wifi_signal_error_v2;

WGL_HIMG_TPL_T  h_g_wifi_25_grey_v2;
WGL_HIMG_TPL_T  h_g_wifi_25_white_v2;
WGL_HIMG_TPL_T  h_g_wifi_50_grey_v2;
WGL_HIMG_TPL_T  h_g_wifi_50_white_v2;
WGL_HIMG_TPL_T  h_g_wifi_75_grey_v2;
WGL_HIMG_TPL_T  h_g_wifi_75_white_v2;
WGL_HIMG_TPL_T  h_g_wifi_100_grey_v2;
WGL_HIMG_TPL_T  h_g_wifi_100_white_v2;
WGL_HIMG_TPL_T  h_g_wifi_connected_v2;

WGL_HIMG_TPL_T  h_g_dialog_box_v2;
WGL_HIMG_TPL_T  h_g_dialog_button_gray_v2;
WGL_HIMG_TPL_T  h_g_dialog_button_highlight_v2;

WGL_HIMG_TPL_T  h_g_pic_color_tuner_digit_highligh_v2;
WGL_HIMG_TPL_T  h_g_pic_test_pattern_enable_highlight_v2;
WGL_HIMG_TPL_T  h_g_pic_color_tuner_top_highlight_v2;
WGL_HIMG_TPL_T  h_g_pic_size_pos_background_v2;
WGL_HIMG_TPL_T  h_g_pic_size_pos_remote_arrows_v2;
WGL_HIMG_TPL_T  h_g_pic_pos_remote_down_v2;
WGL_HIMG_TPL_T  h_g_pic_pos_remote_left_v2;
WGL_HIMG_TPL_T  h_g_pic_pos_remote_right_v2;
WGL_HIMG_TPL_T  h_g_pic_pos_remote_up_v2;
WGL_HIMG_TPL_T  h_g_pic_size_remote_horizontal_res_v2;
WGL_HIMG_TPL_T  h_g_pic_size_remote_horizontal_add_v2;
WGL_HIMG_TPL_T  h_g_pic_size_remote_vertical_res_v2;
WGL_HIMG_TPL_T  h_g_pic_size_remote_vertical_add_v2;
WGL_HIMG_TPL_T  h_g_pic_color_tuner_top_highlight_ex_v2;
WGL_HIMG_TPL_T  h_g_pic_color_tuner_right_arrow_v2;
WGL_HIMG_TPL_T  h_g_pic_color_tuner_left_arrow_v2;

WGL_HIMG_TPL_T  h_g_menu_system_pin_box_v2;
WGL_HIMG_TPL_T  h_g_menu_system_pin_box_highlight_v2;
WGL_HIMG_TPL_T  h_g_menu_system_pin_box_pwd_v2;
WGL_HIMG_TPL_T  h_g_menu_system_pin_box_pushed_v2;
WGL_HIMG_TPL_T  h_g_menu_system_pin_box_active_v2;
WGL_HIMG_TPL_T  h_g_menu_system_pin_box_inactive_v2;


WGL_HIMG_TPL_T  h_g_menu_common_select_hlt_v2;
WGL_HIMG_TPL_T  h_g_menu_common_item_hlt_v2;
WGL_HIMG_TPL_T  h_g_menu_common_eq_bk_v2;
WGL_HIMG_TPL_T  h_g_menu_common_audio_mode_v2;
WGL_HIMG_TPL_T  h_g_menu_common_white_progress_bar_v2;

WGL_HIMG_TPL_T  h_g_menu_ratings_bk_icon_v2;
WGL_HIMG_TPL_T  h_g_menu_ratings_lock_icon_v2;
WGL_HIMG_TPL_T  h_g_menu_ratings_unlock_icon_v2;
WGL_HIMG_TPL_T  h_g_pin_no_match_bkg;

WGL_HIMG_TPL_T  h_g_menu_img_main_bt_headphones;
WGL_HIMG_TPL_T  h_g_menu_img_main_accessiblity;
WGL_HIMG_TPL_T  h_g_menu_img_main_admin;
WGL_HIMG_TPL_T  h_g_menu_img_main_audio;
WGL_HIMG_TPL_T  h_g_menu_img_main_channels;
WGL_HIMG_TPL_T  h_g_menu_img_main_network;
WGL_HIMG_TPL_T  h_g_menu_img_main_picture;
WGL_HIMG_TPL_T  h_g_menu_img_main_system;
WGL_HIMG_TPL_T  h_g_menu_img_main_user_manual;

WGL_HIMG_TPL_T  h_g_menu_img_main_tv_channels_grayed_out;


static BOOL b_oled;

/*----------------------------------------------------------------------------
 * Name: _menu_init_image_2k20
 *
 * Description:
 *      Initiate the images for menu.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *  0 - Successful
 *  -1- Failed
 ----------------------------------------------------------------------------*/
static INT32 _menu_init_image_2k20(VOID)
{
    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_headphone : &t_g_menu_img_main_headphone,
                                    &h_g_menu_img_main_bt_headphones));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_accessiblity_oled : &t_g_menu_img_main_accessiblity,
                                    &h_g_menu_img_main_accessiblity));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_admin_oled : &t_g_menu_img_main_admin,
                                    &h_g_menu_img_main_admin));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_audio_oled : &t_g_menu_img_main_audio,
                                    &h_g_menu_img_main_audio));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_channels_oled : &t_g_menu_img_main_channels,
                                    &h_g_menu_img_main_channels));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_network_oled : &t_g_menu_img_main_network,
                                    &h_g_menu_img_main_network));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_picture_oled : &t_g_menu_img_main_picture,
                                    &h_g_menu_img_main_picture));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_system_oled : &t_g_menu_img_main_system,
                                    &h_g_menu_img_main_system));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_menu_img_main_user_manual_oled : &t_g_menu_img_main_user_manual,
                                    &h_g_menu_img_main_user_manual));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_img_main_tv_channels_grayed_out,
                                    &h_g_menu_img_main_tv_channels_grayed_out));

    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _menu_init_image_v2
 *
 * Description:
 *      Initiate the images for menu.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *  0 - Successful
 *  -1- Failed
 ----------------------------------------------------------------------------*/
static INT32 _menu_init_image_v2(VOID)
{
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_back_highlight_v2_oled : &t_g_menu_back_bar_bk_hlt_v2,
               &h_g_menu_back_bar_bk_hlt_v2));

    RET_ON_ERR(c_wgl_img_tpl_destroy(h_g_menu_back_bar_bk_hlt));
    h_g_menu_back_bar_bk_hlt = h_g_menu_back_bar_bk_hlt_v2;

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_arrow_down_OLED : &t_g_menu_arrow_down_v2,
                                    &h_g_menu_arrow_down_v2));

    RET_ON_ERR (c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_arrow_right_v2,
                                    &h_g_menu_arrow_right_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_arrow_up_OLED : &t_g_menu_arrow_up_v2,
                                    &h_g_menu_arrow_up_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_arrow_white_v2,
                                    &h_g_menu_arrow_white_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_button_save_cancel_v2,
                                    &h_g_menu_button_save_cancel_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_button_save_cancel_highlight_OLED : &t_g_menu_common_sidebar_highlight_v2,
                                    &h_g_menu_button_save_cancel_highlight));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled? &t_g_back_highlight_oled : &t_g_menu_common_back_highlight_v2,
                                    &h_g_menu_common_back_highlight_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled? &t_g_checkbox_background_oled : &t_g_menu_common_checkbox_background_v2,
                                    &h_g_menu_common_checkbox_background_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_checkbox_grey_v2,
                                    &h_g_menu_common_checkbox_grey_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_checkbox_grey_checked_v2,
                                    &h_g_menu_common_checkbox_grey_checked_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_checkbox_white_v2,
                                    &h_g_menu_common_checkbox_white_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_checkbox_white_checked_v2,
                                    &h_g_menu_common_checkbox_white_checked_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_circle_white,
                                    &h_g_menu_common_circle_white));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_circle_white_checked,
                                    &h_g_menu_common_circle_white_checked));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_pair_text_eng,
                                    &h_g_menu_common_pair_text_eng));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_pair_text_spa,
                                    &h_g_menu_common_pair_text_spa));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_pair_text_fre,
                                    &h_g_menu_common_pair_text_fre));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_forget_text_eng,
                                    &h_g_menu_common_forget_text_eng));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_forget_text_spa,
                                    &h_g_menu_common_forget_text_spa));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_forget_text_fre,
                                    &h_g_menu_common_forget_text_fre));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_sidebar_background_v2,
                                    &h_g_menu_common_sidebar_background_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_sidebar_fullScreen_mask_v2,
                                    &h_g_menu_common_sidebar_fullScreen_mask_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_sidebar_highlight_v2_oled : &t_g_menu_common_sidebar_highlight_v2,
                                    &h_g_menu_common_sidebar_highlight_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_V_ONLY,
                                    b_oled ? &t_g_sidebar_highlight_v2_oled_vo : &t_g_menu_common_sidebar_highlight_VO_v2,
                                    &h_g_menu_common_sidebar_highlight_VO_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_sidebar_highlight_arrow_left_v2,
                                    &h_g_menu_common_sidebar_highlight_arrow_left_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_sidebar_highlight_arrow_right_v2,
                                    &h_g_menu_common_sidebar_highlight_arrow_right_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_sidebar_highlight_partial_oled : &t_g_menu_common_sidebar_highlight_partial_v2,
                                    &h_g_menu_common_sidebar_highlight_partial_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_slider_background_v2,
                                    &h_g_menu_common_slider_background_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_slider_indicator_v2,
                                    &h_g_menu_common_slider_indicator_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_lock_grey_v2,
                                    &h_g_lock_grey_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_lock_white_OLED: &t_g_lock_white_v2,
                                    &h_g_lock_white_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_unlock_grey_v2,
                                    &h_g_unlock_grey_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_unlock_white_v2,
                                    &h_g_unlock_white_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_lock_white_hlt_v2,
                                    &h_g_lock_white_hlt_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_unlock_white_hlt_v2,
                                    &h_g_unlock_white_hlt_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_ethernet_v2,
                                    &h_g_ethernet_v2));
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_wifi_25_white_OLED : &t_g_wifi_signal_half_v2,
                                    &h_g_wifi_signal_half_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_wifi_25_white_OLED : &t_g_wifi_signal_1_v2,
                                    &h_g_wifi_signal_1_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_wifi_50_white_OLED : &t_g_wifi_signal_2_v2,
                                    &h_g_wifi_signal_2_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_wifi_75_white_OLED : &t_g_wifi_signal_3_v2,
                                    &h_g_wifi_signal_3_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_wifi_100_white_OLED : &t_g_wifi_signal_4_v2,
                                    &h_g_wifi_signal_4_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_signal_error_v2,
                                    &h_g_wifi_signal_error_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_25_grey_v2,
                                    &h_g_wifi_25_grey_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_25_white_v2,
                                    &h_g_wifi_25_white_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_50_grey_v2,
                                    &h_g_wifi_50_grey_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_50_white_v2,
                                    &h_g_wifi_50_white_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_75_grey_v2,
                                    &h_g_wifi_75_grey_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_75_white_v2,
                                    &h_g_wifi_75_white_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_100_grey_v2,
                                    &h_g_wifi_100_grey_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_wifi_100_white_v2,
                                    &h_g_wifi_100_white_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_wifi_100_white_OLED : &t_g_wifi_connected_v2,
                                    &h_g_wifi_connected_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_dialog_box_v2,
                                    &h_g_dialog_box_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_dialog_button_gray_v2,
                                    &h_g_dialog_button_gray_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_dialog_button_highlight_oled : &t_g_dialog_button_highlight_v2,
                                    &h_g_dialog_button_highlight_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_color_tuner_digit_highlight_oled : &t_g_pic_color_tuner_digit_highligh_v2,
                                    &h_g_pic_color_tuner_digit_highligh_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_color_tuner_test_pattern_enable_highlight_oled : &t_g_pic_test_pattern_enable_highlight_v2,
                                    &h_g_pic_test_pattern_enable_highlight_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_color_tuner_top_highlight_oled : &t_g_pic_color_tuner_top_highlight_v2,
                                    &h_g_pic_color_tuner_top_highlight_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_size_pos_background_v2,
                                    &h_g_pic_size_pos_background_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_size_pos_remote_arrows_v2,
                                    &h_g_pic_size_pos_remote_arrows_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_pos_remote_down_v2,
                                    &h_g_pic_pos_remote_down_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_pos_remote_left_v2,
                                    &h_g_pic_pos_remote_left_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_pos_remote_right_v2,
                                    &h_g_pic_pos_remote_right_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_pos_remote_up_v2,
                                    &h_g_pic_pos_remote_up_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_size_remote_horizontal_res_v2,
                                    &h_g_pic_size_remote_horizontal_res_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_size_remote_horizontal_add_v2,
                                    &h_g_pic_size_remote_horizontal_add_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_size_remote_vertical_res_v2,
                                    &h_g_pic_size_remote_vertical_res_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_size_remote_vertical_add_v2,
                                    &h_g_pic_size_remote_vertical_add_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_color_tuner_top_highlight_ex_v2_oled : &t_g_pic_color_tuner_top_highlight_ex_v2,
                                    &h_g_pic_color_tuner_top_highlight_ex_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_color_tuner_right_arrow_v2,
                                    &h_g_pic_color_tuner_right_arrow_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_pic_color_tuner_left_arrow_v2,
                                    &h_g_pic_color_tuner_left_arrow_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_system_pin_box_v2,
                                    &h_g_menu_system_pin_box_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled? &t_g_system_pin_box_highlight_oled : &t_g_menu_system_pin_box_highlight_v2,
                                    &h_g_menu_system_pin_box_highlight_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                     b_oled? &t_g_system_pin_box_active_oled : &t_g_menu_system_pin_box_active_v2,
                                    &h_g_menu_system_pin_box_active_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                     b_oled? &t_g_system_pin_box_inactive_oled : &t_g_menu_system_pin_box_inactive_v2,
                                    &h_g_menu_system_pin_box_inactive_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_system_pin_box_pwd_v2,
                                    &h_g_menu_system_pin_box_pwd_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_system_pin_box_pushed_v2,
                                    &h_g_menu_system_pin_box_pushed_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_eq_audio_mode_slider_highlight_2_oled : &t_g_menu_common_select_hlt_v2,
                                    &h_g_menu_common_select_hlt_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_eq_audio_item_hlt_oled : &t_g_menu_common_item_hlt_v2,
                                    &h_g_menu_common_item_hlt_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_eq_bk_v2,
                                    &h_g_menu_common_eq_bk_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_eq_highlight_oled : &t_g_menu_common_audio_mode_v2,
                                    &h_g_menu_common_audio_mode_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_common_white_progress_bar_v2,
                                    &h_g_menu_common_white_progress_bar_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_ratings_bk_icon_v2,
                                    &h_g_menu_ratings_bk_icon_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_ratings_lock_icon_v2,
                                    &h_g_menu_ratings_lock_icon_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_ratings_unlock_icon_v2,
                                    &h_g_menu_ratings_unlock_icon_v2));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
					                &t_g_pin_no_match_bkg,
					                &h_g_pin_no_match_bkg));


    //add from here

    return 0;
}
extern BOOL a_is_oled_compensation_support();
/*----------------------------------------------------------------------------
 * Name: menu_init_image
 *
 * Description:
 *      Initiate the images for menu.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *  0 - Successful
 *  -1- Failed
 ----------------------------------------------------------------------------*/
INT32 menu_init_image(VOID)
{
    b_oled = a_is_oled_compensation_support();

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_menu_back_bar_bk,
                &h_g_menu_back_bar_bk))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_back_bar_bk_hlt,
               &h_g_menu_back_bar_bk_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_connected_icon,
               &h_g_menu_img_connected_icon))


    /* background image */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_bk0,
               &h_g_menu_img_bk0))

    /* item images */
    h_g_menu_img_item_bk        = NULL_HANDLE;
    h_g_menu_img_item_bk_large  = NULL_HANDLE;
    h_g_menu_img_item_bar_plain = NULL_HANDLE;
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_back_arrow_white_OLED : &t_g_menu_back_left_arrow,
               &h_g_menu_back_left_arrow))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_sidebar_highlight_v2_oled : &t_g_menu_common_sidebar_highlight_v2,
               &h_g_menu_img_item_hlt_bk))

    /* skip image */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_skip,
               &h_g_menu_img_skip))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_unskip,
               &h_g_menu_img_unskip))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_checkbox_board,
               &h_g_menu_checkbox_board))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_checkbox_off,
               &h_g_menu_checkbox_off))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_checkbox_on,
               &h_g_menu_checkbox_on))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                   &t_g_menu_checkbox_on_hlt_check,
                   &h_g_menu_checkbox_on_hlt_check))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_menu_img_clrmem_pwd_unempty,
                &h_g_menu_img_clrmem_pwd_unempty))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_menu_img_clrmem_pwd_empty,
                &h_g_menu_img_clrmem_pwd_empty))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_menu_img_clrmem_pwd_empty_hlt,
                &h_g_menu_img_clrmem_pwd_empty_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_img_eq_background,
                                    &h_g_menu_img_eq_background))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_img_eq_item_ind,
                                    &h_g_menu_img_eq_item_ind))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_img_eq_item_hlt,
                                    &h_g_menu_img_eq_item_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_img_eq_item_nor,
                                    &h_g_menu_img_eq_item_nor))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_img_eq_item_sel,
                                    &h_g_menu_img_eq_item_sel))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_menu_img_eq_level,
                                    &h_g_menu_img_eq_level))

    /* home bar */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_home_img,
               &h_g_menu_img_home_img))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_home_bar,
               &h_g_menu_img_home_bar))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_home_bar_hlt,
               &h_g_menu_img_home_bar_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_list_item_leftarrow,
               &h_g_menu_img_list_item_leftarrow))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_pg_blue,
               &h_g_menu_img_pg_blue))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_pg_silver,
               &h_g_menu_img_pg_silver))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_pg_silver_hlt,
               &h_g_menu_img_pg_silver_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_list_item_rightarrow,
               &h_g_menu_img_list_item_rightarrow))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_terms_arrow_down_off,
               &h_g_menu_terms_arrow_down_off))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_terms_arrow_down_on,
               &h_g_menu_terms_arrow_down_on))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_terms_arrow_up_off,
               &h_g_menu_terms_arrow_up_off))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_terms_arrow_up_on,
               &h_g_menu_terms_arrow_up_on))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
               &t_g_menu_terms_box_off,
               &h_g_menu_terms_box_off))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
               &t_g_menu_terms_box_on,
               &h_g_menu_terms_box_on))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_tv_rate_lock,
               &h_g_menu_img_tv_rate_lock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_tv_rate_lock_hlt,
               &h_g_menu_img_tv_rate_lock_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_tv_rate_unlock,
               &h_g_menu_img_tv_rate_unlock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_tv_rate_unlock_hlt,
               &h_g_menu_img_tv_rate_unlock_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_tv_rate_bk,
               &h_g_menu_img_tv_rate_bk))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_tv_home_bar_bk,
               &h_g_menu_img_tv_home_bar_bk))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_icon_lock,
               &h_g_menu_img_icon_lock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_icon_unlock,
               &h_g_menu_img_icon_unlock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_tv_home_bar_focs,
               &h_g_menu_img_tv_home_bar_focs))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_text_entry,
               &h_g_menu_img_text_entry))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_text_entry_large,
               &h_g_menu_img_text_entry_large))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_text_entry_small,
               &h_g_menu_img_text_entry_small))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
                  &t_g_menu_img_text_entry_small_1,
                  &h_g_menu_img_text_entry_small_1))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_last_shadow_new,
               &h_g_menu_img_last_shadow_new))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_ethernet_off,
               &h_g_menu_img_ethernet_off))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_ethernet_on,
               &h_g_menu_img_ethernet_on))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_keypad_hlt,
               &h_g_menu_img_keypad_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_keypad_hlt_big,
               &h_g_menu_img_keypad_hlt_big))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_keypad_hlt_space,
               &h_g_menu_img_keypad_hlt_space))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_lastshadow_new,
               &h_g_menu_img_lastshadow_new))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_NewKeypad_bg,
               &h_g_menu_img_NewKeypad_bg))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
              &t_g_menu_img_TVRating_hlt,
              &h_g_menu_img_TVRating_hlt))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
              b_oled ? &t_g_arrow_up_OLED : &t_g_menu_new_arrow_up,
              &h_g_menu_new_arrow_up))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
              b_oled ? &t_g_arrow_down_OLED : &t_g_menu_new_arrow_down,
              &h_g_menu_new_arrow_down))

    h_g_menu_img_arrow_up = h_g_menu_new_arrow_up;
    h_g_menu_img_arrow_down = h_g_menu_new_arrow_down;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
              &t_g_menu_x,
              &h_g_menu_x))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
              &t_g_menu_checkbox_on_hlt,
              &h_g_menu_checkbox_on_hlt))



    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_ch_lock,
               &h_g_menu_img_ch_lock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_ch_unlock,
               &h_g_menu_img_ch_unlock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_ch_lock_with_arrow,
               &h_g_menu_img_lock_with_arrow))

    h_g_menu_lastshadow_new = NULL_HANDLE;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_audio_v2,
               &h_g_menu_settings_icon_audio))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_hlt_audio_v2,
               &h_g_menu_settings_icon_hlt_audio))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_cc_v2,
               &h_g_menu_settings_icon_cc))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_hlt_cc_v2,
               &h_g_menu_settings_icon_hlt_cc))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_devices_v2,
               &h_g_menu_settings_icon_devices))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_hlt_devices_v2,
               &h_g_menu_settings_icon_hlt_devices))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_guided_setup_v2,
               &h_g_menu_settings_icon_guided_setup))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_hlt_guided_setup_v2,
               &h_g_menu_settings_icon_hlt_guided_setup))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_network_v2,
               &h_g_menu_settings_icon_network))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_hlt_network_v2,
               &h_g_menu_settings_icon_hlt_network))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_system_v2,
               &h_g_menu_settings_icon_system))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_hlt_system_v2,
               &h_g_menu_settings_icon_hlt_system))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_timers_v2,
               &h_g_menu_settings_icon_timers))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_hlt_timers_v2,
               &h_g_menu_settings_icon_hlt_timers))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_tuner_v2,
               &h_g_menu_settings_icon_tuner))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_settings_icon_hlt_tuner_v2,
               &h_g_menu_settings_icon_hlt_tuner))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                   &t_g_menu_settings_icon_picture_v2,
                   &h_g_menu_settings_icon_picture))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                   &t_g_menu_settings_icon_hlt_picture_v2,
                   &h_g_menu_settings_icon_hlt_picture))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                       &t_g_menu_img_settings_icon_user_manual_v2,
                       &h_g_menu_img_settings_icon_user_manual))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                       &t_g_menu_img_settings_icon_hlt_user_manual_v2,
                       &h_g_menu_img_settings_icon_hlt_user_manual))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_signal_lock,
               &h_g_menu_signal_lock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_signal_1of5,
               &h_g_menu_signal_1of5))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_signal_2of5,
               &h_g_menu_signal_2of5))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_signal_3of5,
               &h_g_menu_signal_3of5))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_signal_4of5,
               &h_g_menu_signal_4of5))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_signal_5of5,
               &h_g_menu_signal_5of5))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_2d,
               &h_g_menu_img_3d_setting_2d))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_2d_hlt,
               &h_g_menu_img_3d_setting_2d_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_3d,
               &h_g_menu_img_3d_setting_3d))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_3d_hlt,
               &h_g_menu_img_3d_setting_3d_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_sbs,
               &h_g_menu_img_3d_setting_sbs))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_sbs_hlt,
               &h_g_menu_img_3d_setting_sbs_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_sensio,
               &h_g_menu_img_3d_setting_sensio))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_sensio_hlt,
               &h_g_menu_img_3d_setting_sensio_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_tb,
               &h_g_menu_img_3d_setting_tb))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3d_setting_tb_hlt,
               &h_g_menu_img_3d_setting_tb_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_H_ONLY,
               &t_g_menu_img_3D_content_mode_bkg,
               &h_g_menu_img_3D_content_mode_bkg))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_3D_output_mode_bkg,
               &h_g_menu_img_3D_output_mode_bkg))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_back_bar_bk_main,
               &h_g_menu_img_back_bar_bk_main))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_homebar_main,
               &h_g_menu_img_homebar_main))


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_ch_unlock_with_arrow,
               &h_g_menu_img_unlock_with_arrow))

    /* skip image */

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_unskip_hlt,
               &h_g_menu_img_unskip_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_skip_hlt,
               &h_g_menu_img_skip_hlt))

    /* fav list image */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_skip,
               &h_g_menu_img_fav))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_skip_hlt,
               &h_g_menu_img_fav_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_unskip,
               &h_g_menu_img_nfav))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_unskip_hlt,
               &h_g_menu_img_nfav_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_ch_lst_arrow_up,
               &h_g_menu_img_ch_lst_arrow_up))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_ch_lst_arrow_down,
               &h_g_menu_img_ch_lst_arrow_down))

    /* lock image */

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_lock,
               &h_g_menu_img_lock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_lock_hlt,
               &h_g_menu_img_lock_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_unlock,
               &h_g_menu_img_unlock))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_img_unlock_hlt,
               &h_g_menu_img_unlock_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_title_bar_bk,
               &h_g_menu_title_bar_bk))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_list_elem_bk,
               &h_g_menu_list_elem_bk))

    /* progress bar */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
               &t_g_menu_img_pb_bk,
               &h_g_menu_img_pb_bk))

    h_g_menu_img_pb_bk_hlt          = h_g_menu_img_pb_bk;
    h_g_menu_img_pb_bk_disable      = h_g_menu_img_pb_bk;
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
               b_oled ? &t_g_pb_bar_OLED : &t_g_menu_img_pb_bar,
               &h_g_menu_img_pb_bar))

    h_g_menu_img_pb_point           = h_g_menu_img_pb_bar;
    h_g_menu_img_item_edit          = h_g_menu_img_text_entry_large;
    h_g_menu_img_item_edit_hlt      = h_g_menu_img_text_entry_large;

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                &t_g_menu_img_clear_memory_bk,
                &h_g_menu_img_clear_memory_bk))

    /* wifi remote use */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_icon_green,
               &h_g_menu_icon_green))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_menu_icon_record,
               &h_g_menu_icon_record))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                  &t_g_menu_img_bar_background,
                                  &h_g_menu_img_bar_background))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_back,
                                &h_g_menu_ColorTuner_back))


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_button_off,
                                &h_g_menu_ColorTuner_button_off))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_button_on,
                                &h_g_menu_ColorTuner_button_on))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_digit_arrows,
                                &h_g_menu_ColorTuner_digit_arrows))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                b_oled ? &t_g_color_tuner_digit_highlight_oled : &t_g_menu_ColorTuner_digit_hlt,
                                &h_g_menu_ColorTuner_digit_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_grid_2k20,
                                &h_g_menu_ColorTuner_grid))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_left_arrow,
                                &h_g_menu_ColorTuner_left_arrow))


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_left_arrow_hlt,
                                &h_g_menu_ColorTuner_left_arrow_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_right_arrow,
                                &h_g_menu_ColorTuner_right_arrow))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_right_arrow_hlt,
                                &h_g_menu_ColorTuner_right_arrow_hlt))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_passcode_entry,
                                &h_g_menu_passcode_entry))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_passcode_entry_highlight,
                                &h_g_menu_passcode_entry_highlight))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_Button_box,
                                &h_g_menu_ColorTuner_Button_box))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_test_back,
                                &h_g_menu_ColorTuner_test_back))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_test_back2,
                                &h_g_menu_ColorTuner_test_back2))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_Button_box_OFF_mov,
                                &h_g_menu_ColorTuner_Button_box_OFF_mov))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_Button_box_On_mov,
                                &h_g_menu_ColorTuner_Button_box_On_mov))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_digit_hlt_new,
                                &h_g_menu_ColorTuner_digit_hlt_new))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_top_hlt,
                                &h_g_menu_ColorTuner_top_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_top_arrows_hlt,
                                &h_g_menu_ColorTuner_top_arrows_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_RGB_bar,
                                &h_g_menu_ColorTuner_RGB_bar))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_ColorOff,
                                &h_g_menu_ColorTuner_ColorOff))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_bottom_right,
                                &h_g_menu_ColorTuner_bottom_right))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_img_ColorTuner_grid_test,
                                &h_g_menu_img_ColorTuner_grid_test))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_img_WhiteBalanceTuner_grid_2k20,
                                &h_g_menu_img_WhiteBalanceTuner_grid))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_color_tuner_2020,
                                &h_g_menu_color_tuner_2020))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_white_balance_tuner_2020,
                                &h_g_menu_white_balance_tuner_2020))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_with_rgb_back,
                                &h_g_menu_ColorTuner_with_rgb_back))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_ColorTuner_digit_hlt_arrows,
                                &h_g_menu_ColorTuner_digit_hlt_arrows))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_position_size_adjust,
                                &h_g_menu_position_size_adjust))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_adjust_position_down,
                                &h_g_menu_adjust_position_down))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_adjust_position_up,
                                &h_g_menu_adjust_position_up))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_adjust_position_left,
                                &h_g_menu_adjust_position_left))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_adjust_position_right,
                                &h_g_menu_adjust_position_right))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_adjust_size_vertical_add,
                                &h_g_menu_adjust_size_vertical_add))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_adjust_size_vertical_minus,
                                &h_g_menu_adjust_size_vertical_minus))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_adjust_size_horizontal_add,
                                &h_g_menu_adjust_size_horizontal_add))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_adjust_size_horizontal_minus,
                                &h_g_menu_adjust_size_horizontal_minus))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_img_clrmem_pwd_unempty_hlt,
                                &h_g_menu_img_clrmem_pwd_fill_num_hlt))


    /*for menu add new device*/
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_img_Remote_Key_Device_Power,
                                &h_g_menu_img_Remote_Key_Device_Power))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_img_Text_clear_all,
                                &h_g_menu_img_Text_clear_all))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_menu_img_Text_clear_all_hlt,
                                &h_g_menu_img_Text_clear_all_hlt))


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_warning_icon,
                                &h_g_warning_icon))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_Warning_Bar_button_hlt,
                                &h_g_Warning_Bar_button_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_Warning_Bar_button,
                                &h_g_Warning_Bar_button))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_arrow_bottom,
                                &h_g_arrow_bottom))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_arrow_left,
                                &h_g_arrow_left))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_arrow_right,
                                &h_g_arrow_right))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_arrow_up,
                                &h_g_arrow_up))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_ok_key_select,
                                &h_g_ok_key_select))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_pw_enter_small,
                                &h_g_pw_enter_small))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_pw_enter_ipt_small,
                                &h_g_pw_enter_ipt_small))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_pw_enter_small_hlt,
                                &h_g_pw_enter_small_hlt))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_lock_pic_mode_Bar_big,
                                &h_g_lock_pic_mode_Bar_big))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_tos_scrollbar,
                                &h_g_tos_scrollbar))

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_tos_scrollbar_indicator,
                                &h_g_tos_scrollbar_indicator))
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_energy_Star_Logo_menu_icon,
                                &h_g_menu_energy_Star))

#if 0//def APP_HDR_SUPPORT
	RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
								&t_g_dolby_vision_vert_icon_2k20,
								&h_g_menu_dolby_vision_icon))
#endif
#ifdef APP_HDR_SUPPORT
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
                                &t_g_dolby_vision_vert_icon_2k21_108x45,
                                &h_g_menu_dolby_vision_icon))
#endif

    RET_ON_ERR(_menu_init_image_v2());

    RET_ON_ERR(_menu_init_image_2k20());

    return 0;
}

