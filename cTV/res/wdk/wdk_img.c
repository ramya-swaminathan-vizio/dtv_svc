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
 * $RCSfile: wdk_img.c,v $
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
#include "app_util/a_common.h"
#include "res/wdk/wdk_img.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"

#if defined(APP_COLOR_MODE_PALLET)
    #if !defined(APP_OSD_640x360)
    #else
        #error Not implemented
    #endif
#else /* 444 mode */
     #include "res/wdk/wdk_img_v2.i"
     #include "res/wdk/wdk_img_2013.i"
#endif
#include "res/wdk/wdk_img_oled.i"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define RET_ON_ERR(_expr) if(_expr != 0){return -1;}

/* Share */

/* VKB (Virtual KeyBoard) related */
WGL_HIMG_TPL_T             h_g_wdk_vkb_main_frm_background_img = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_vkb_keypad_hlt_img = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_vkb_big_keypad_hlt_img = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_vkb_space_keypad_hlt_img = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_vkb_keypad_bar_img = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_vkb_keypad_bar_hlt_img = NULL_HANDLE;

WGL_HIMG_TPL_T             h_g_wdk_img_Bar = NULL_HANDLE;


/*loading animation*/
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_1;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_2;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_3;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_4;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_5;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_6;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_7;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_8;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_9;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_10;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_11;
WGL_HIMG_TPL_T             h_g_wdk_img_loading_icon_12;
/*loading BT animation*/
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_1;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_2;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_3;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_4;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_5;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_6;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_7;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_8;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_9;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_10;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_11;
WGL_HIMG_TPL_T             h_g_wdk_img_bt_loading_icon_12;
WGL_HIMG_TPL_T             h_g_wdk_img_signal_icon_1 = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_img_signal_icon_2 = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_img_signal_icon_3 = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_img_signal_icon_4 = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_img_signal_icon_5 = NULL_HANDLE;

/*cnt indctr*/
WGL_HIMG_TPL_T              h_g_wdk_cnt_indctr_img[4] ;

/*vkb*/
WGL_HIMG_TPL_T             h_g_wdk_vkb_edit_img = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_vkb_edit_bk = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_vkb_edit_hlt_bk = NULL_HANDLE;
WGL_HIMG_TPL_T             h_g_wdk_vkb_capslock_keypad_img;
WGL_HIMG_TPL_T             h_g_wdk_vkb_capslock_keypad_hlt_img;
WGL_HIMG_TPL_T             h_g_wdk_vkb_capslock_keypad_dis_img;
WGL_HIMG_TPL_T             h_g_wdk_vkb_delete_keypad_img;
WGL_HIMG_TPL_T             h_g_wdk_vkb_delete_keypad_hlt_img;
WGL_HIMG_TPL_T             h_g_wdk_vkb_eb_clear;
WGL_HIMG_TPL_T             h_g_wdk_vkb_eb_clear_hlt;
WGL_HIMG_TPL_T             h_g_wdk_img_key_hlt;
WGL_HIMG_TPL_T             h_g_wdk_img_key_spa_hlt;
WGL_HIMG_TPL_T             h_g_wdk_img_key_symb_hlt;
WGL_HIMG_TPL_T             h_g_wdk_img_key_board;
WGL_HIMG_TPL_T             h_g_wdk_img_key_carat_passcode;
WGL_HIMG_TPL_T             h_g_wdk_img_key_character_shift;
WGL_HIMG_TPL_T             h_g_wdk_img_key_character_shift_hlt;
WGL_HIMG_TPL_T             h_g_wdk_img_key_character_back;
WGL_HIMG_TPL_T             h_g_wdk_img_key_character_back_hlt;

WGL_HIMG_TPL_T             h_g_wdk_img_key_back_highlight;
WGL_HIMG_TPL_T             h_g_wdk_img_key_back_unhighlight;
WGL_HIMG_TPL_T             h_g_wdk_img_key_shift_highlight;
WGL_HIMG_TPL_T             h_g_wdk_img_key_shift_unhighlight;
WGL_HIMG_TPL_T             h_g_wdk_img_key_shift_gray;
WGL_HIMG_TPL_T             h_g_wdk_img_delete_gray;

WGL_HIMG_TPL_T              h_g_vkb_keyboard_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboard_backspace_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboard_capital_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboard_clear_all_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboard_highlight_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboard_special_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboard_symbols_v2;
WGL_HIMG_TPL_T              h_g_vkb_text_entry_v2;
WGL_HIMG_TPL_T              h_g_vkb_text_entry_highlight;
WGL_HIMG_TPL_T              h_g_vkb_text_entry_clear_all_v2;
WGL_HIMG_TPL_T              h_g_vkb_text_entry_cursor_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboad_backspace_hlt_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboard_backspace_normal_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboad_cap_hlt_v2;
WGL_HIMG_TPL_T              h_g_vkb_keyboard_cap_normal_v2;
WGL_HIMG_TPL_T              h_g_vkb_text_entry_clear_all_hlt_v2;

WGL_HIMG_TPL_T			   h_g_wdk_gradient_btm;
WGL_HIMG_TPL_T			   h_g_wdk_gradient_center;
WGL_HIMG_TPL_T			   h_g_wdk_gradient_top;
WGL_HIMG_TPL_T				h_g_wdk_toast_box;
WGL_HIMG_TPL_T				h_g_wdk_toast_box_settings;
WGL_HIMG_TPL_T				h_g_wdk_toast_box_vol;
WGL_HIMG_TPL_T				h_g_wdk_track_cap_left;
WGL_HIMG_TPL_T				h_g_wdk_track_cap_right;
WGL_HIMG_TPL_T				h_g_wdk_track_fill;
WGL_HIMG_TPL_T				h_g_wdk_warning;

WGL_HIMG_TPL_T				h_g_wdk_eq_hash_mark;

WGL_HIMG_TPL_T              h_g_wdk_content_box;


/*wdk toast img*/
WGL_HIMG_TPL_T			    h_g_wdk_single_select_list;
WGL_HIMG_TPL_T			    h_g_setting_slider;
WGL_HIMG_TPL_T			    h_g_string_toast;
WGL_HIMG_TPL_T			    h_g_warning_toast;
WGL_HIMG_TPL_T              h_g_energy_star;
WGL_HIMG_TPL_T              h_g_energy_star_gray;
WGL_HIMG_TPL_T              h_g_zoom_energy_star;
WGL_HIMG_TPL_T              h_g_zoom_energy_star_gray;
WGL_HIMG_TPL_T              h_g_dolby_vision_icon;

WGL_HIMG_TPL_T              h_g_nav_selected;
WGL_HIMG_TPL_T              h_g_nav_unselected;

WGL_HIMG_TPL_T              h_g_nav_spinner_1;
WGL_HIMG_TPL_T              h_g_nav_spinner_2;
WGL_HIMG_TPL_T              h_g_nav_spinner_3;
WGL_HIMG_TPL_T              h_g_nav_spinner_4;
WGL_HIMG_TPL_T              h_g_nav_spinner_5;
WGL_HIMG_TPL_T              h_g_nav_spinner_6;
WGL_HIMG_TPL_T              h_g_nav_spinner_7;
WGL_HIMG_TPL_T              h_g_nav_spinner_8;
WGL_HIMG_TPL_T              h_g_nav_spinner_9;
WGL_HIMG_TPL_T              h_g_nav_spinner_10;
WGL_HIMG_TPL_T              h_g_nav_spinner_11;
WGL_HIMG_TPL_T              h_g_nav_spinner_12;

/* image init flag */
static BOOL                 b_img_init = FALSE;
static BOOL                 b_oled = FALSE;
/*-----------------------------------------------------------------------------
                    static function declaraions
-----------------------------------------------------------------------------*/
static INT32 _wdk_image_create_share_tpl            (VOID);
static INT32 _wdk_image_create_vkb_tpl              (VOID);


/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _wdk_image_create_share_tpl (VOID)
{
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_1,
               &h_g_nav_spinner_1));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_2,
               &h_g_nav_spinner_2));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_3,
               &h_g_nav_spinner_3));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_4,
               &h_g_nav_spinner_4));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_5,
               &h_g_nav_spinner_5));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_6,
               &h_g_nav_spinner_6));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_7,
               &h_g_nav_spinner_7));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_8,
               &h_g_nav_spinner_8));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_9,
               &h_g_nav_spinner_9));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_10,
               &h_g_nav_spinner_10));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_11,
               &h_g_nav_spinner_11));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_spinner_12,
               &h_g_nav_spinner_12));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_selected,
               &h_g_nav_selected));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_nav_unselected,
               &h_g_nav_unselected));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist1_OLED : &t_g_wdk_img_loading_icon_1,
               &h_g_wdk_img_loading_icon_1));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist2_OLED : &t_g_wdk_img_loading_icon_2,
               &h_g_wdk_img_loading_icon_2));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist3_OLED : &t_g_wdk_img_loading_icon_3,
               &h_g_wdk_img_loading_icon_3));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist4_OLED : &t_g_wdk_img_loading_icon_4,
               &h_g_wdk_img_loading_icon_4));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist5_OLED : &t_g_wdk_img_loading_icon_5,
               &h_g_wdk_img_loading_icon_5));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist6_OLED : &t_g_wdk_img_loading_icon_6,
               &h_g_wdk_img_loading_icon_6));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist7_OLED : &t_g_wdk_img_loading_icon_7,
               &h_g_wdk_img_loading_icon_7));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist8_OLED : &t_g_wdk_img_loading_icon_8,
               &h_g_wdk_img_loading_icon_8));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist9_OLED : &t_g_wdk_img_loading_icon_9,
               &h_g_wdk_img_loading_icon_9));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist10_OLED : &t_g_wdk_img_loading_icon_10,
               &h_g_wdk_img_loading_icon_10));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist11_OLED : &t_g_wdk_img_loading_icon_11,
               &h_g_wdk_img_loading_icon_11));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_spinnerlist12_OLED : &t_g_wdk_img_loading_icon_12,
               &h_g_wdk_img_loading_icon_12));

    /* BT sidebar menu --begin */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist1_OLED : &t_g_wdk_img_bt_loading_icon_1,
               &h_g_wdk_img_bt_loading_icon_1));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist2_OLED : &t_g_wdk_img_bt_loading_icon_2,
               &h_g_wdk_img_bt_loading_icon_2));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist3_OLED : &t_g_wdk_img_bt_loading_icon_3,
               &h_g_wdk_img_bt_loading_icon_3));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist4_OLED : &t_g_wdk_img_bt_loading_icon_4,
               &h_g_wdk_img_bt_loading_icon_4));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist5_OLED : &t_g_wdk_img_bt_loading_icon_5,
               &h_g_wdk_img_bt_loading_icon_5));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist6_OLED : &t_g_wdk_img_bt_loading_icon_6,
               &h_g_wdk_img_bt_loading_icon_6));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist7_OLED : &t_g_wdk_img_bt_loading_icon_7,
               &h_g_wdk_img_bt_loading_icon_7));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist8_OLED : &t_g_wdk_img_bt_loading_icon_8,
               &h_g_wdk_img_bt_loading_icon_8));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist9_OLED : &t_g_wdk_img_bt_loading_icon_9,
               &h_g_wdk_img_bt_loading_icon_9));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist10_OLED : &t_g_wdk_img_bt_loading_icon_10,
               &h_g_wdk_img_bt_loading_icon_10));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist11_OLED : &t_g_wdk_img_bt_loading_icon_11,
               &h_g_wdk_img_bt_loading_icon_11));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_bt_spinnerlist12_OLED : &t_g_wdk_img_bt_loading_icon_12,
               &h_g_wdk_img_bt_loading_icon_12));
    /* BT sidebar menu --end */

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_signal_icon_1,
               &h_g_wdk_img_signal_icon_1));
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_signal_icon_2,
               &h_g_wdk_img_signal_icon_2));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_signal_icon_3,
               &h_g_wdk_img_signal_icon_3));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_signal_icon_4,
               &h_g_wdk_img_signal_icon_4));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_signal_icon_5,
               &h_g_wdk_img_signal_icon_5));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_cnt_indctr_up_img,
               &h_g_wdk_cnt_indctr_img[0]));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_cnt_indctr_down_img,
               &h_g_wdk_cnt_indctr_img[1]));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_cnt_indctr_left_img,
               &h_g_wdk_cnt_indctr_img[2]));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_cnt_indctr_right_img,
               &h_g_wdk_cnt_indctr_img[3]));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_cnt_indctr_right_img,
               &h_g_wdk_cnt_indctr_img[3]));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_gradient_btm,
               &h_g_wdk_gradient_btm));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_gradient_center,
               &h_g_wdk_gradient_center));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_single_select_list,
               &h_g_wdk_single_select_list));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_setting_slider,
               &h_g_setting_slider));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_string_toast,
               &h_g_string_toast));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_warning_toast,
               &h_g_warning_toast));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_energy_star,
               &h_g_energy_star));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_gradient_top,
               &h_g_wdk_gradient_top));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_toast_box,
               &h_g_wdk_toast_box));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_toast_box_settings,
               &h_g_wdk_toast_box_settings));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_toast_box_vol,
               &h_g_wdk_toast_box_vol));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_track_cap_left_oled : &t_g_wdk_track_cap_left,
               &h_g_wdk_track_cap_left));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_track_cap_right_oled : &t_g_wdk_track_cap_right,
               &h_g_wdk_track_cap_right));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_track_fill_oled : &t_g_wdk_track_fill,
               &h_g_wdk_track_fill));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_warning_OLED : &t_g_wdk_warning,
               &h_g_wdk_warning));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_eq_hash_mark,
               &h_g_wdk_eq_hash_mark));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_HV,
               &t_g_wdk_content_box_bk_img,
               &h_g_wdk_content_box));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_energy_star_gray,
               &h_g_energy_star_gray));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_zoom_energy_star,
               &h_g_zoom_energy_star));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_zoom_energy_star_gray,
               &h_g_zoom_energy_star_gray));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_dolby_vision_vert_icon,
               &h_g_dolby_vision_icon));

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _wdk_image_create_vkb_tpl (VOID)
{
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_main_frm_background_img,
               &h_g_wdk_vkb_main_frm_background_img));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_keypad_hlt_img,
               &h_g_wdk_vkb_keypad_hlt_img));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_big_keypad_hlt_img,
               &h_g_wdk_vkb_big_keypad_hlt_img));


    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_space_keypad_hlt_img,
               &h_g_wdk_vkb_space_keypad_hlt_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_keypad_bar_hlt_img,
               &h_g_wdk_vkb_keypad_bar_hlt_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_text_entry_large,
               &h_g_wdk_vkb_edit_img));

	RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
	               &t_g_wdk_img_Bar,
	               &h_g_wdk_img_Bar));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_capslock_keypad_img,
               &h_g_wdk_vkb_capslock_keypad_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_capslock_keypad_hlt_img,
               &h_g_wdk_vkb_capslock_keypad_hlt_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_capslock_keypad_dis_img,
               &h_g_wdk_vkb_capslock_keypad_dis_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_delete_keypad_img,
               &h_g_wdk_vkb_delete_keypad_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_vkb_delete_keypad_hlt_img,
               &h_g_wdk_vkb_delete_keypad_hlt_img));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_eb_clear,
               &h_g_wdk_vkb_eb_clear));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_eb_clear_hlt,
               &h_g_wdk_vkb_eb_clear_hlt));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_hlt,
               &h_g_wdk_img_key_hlt));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_spa_hlt,
               &h_g_wdk_img_key_spa_hlt));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_symb_hlt,
               &h_g_wdk_img_key_symb_hlt));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_board,
               &h_g_wdk_img_key_board));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_carat_passcode,
               &h_g_wdk_img_key_carat_passcode));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_character_shift,
               &h_g_wdk_img_key_character_shift));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_character_shift_hlt,
               &h_g_wdk_img_key_character_shift_hlt));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_character_back,
               &h_g_wdk_img_key_character_back));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_character_back_hlt,
               &h_g_wdk_img_key_character_back_hlt));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_back_highlight,
               &h_g_wdk_img_key_back_highlight));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_back_unhighlight,
               &h_g_wdk_img_key_back_unhighlight));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_shift_highlight,
               &h_g_wdk_img_key_shift_highlight));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_shift_unhighlight,
               &h_g_wdk_img_key_shift_unhighlight));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_key_shift_gray,
               &h_g_wdk_img_key_shift_gray));

    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_wdk_img_delete_gray,
               &h_g_wdk_img_delete_gray));

    /* UI3.1 */
    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_keyboard_v2,
                                    &h_g_vkb_keyboard_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_keyboard_backspace_v2,
                                    &h_g_vkb_keyboard_backspace_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_keyboard_capital_v2,
                                    &h_g_vkb_keyboard_capital_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_keyboard_clear_all_v2,
                                    &h_g_vkb_keyboard_clear_all_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_HV,
                                    b_oled ? &t_g_keyboard_highlight_oled : &t_g_vkb_keyboard_highlight_v2,
                                    &h_g_vkb_keyboard_highlight_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_keyboard_special_v2,
                                    &h_g_vkb_keyboard_special_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_keyboard_symbols_v2,
                                    &h_g_vkb_keyboard_symbols_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_text_entry_oled : &t_g_vkb_text_entry_v2,
                                    &h_g_vkb_text_entry_v2));


    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_text_entry_highlight_oled : &t_g_vkb_text_entry_highlight,
                                    &h_g_vkb_text_entry_highlight));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_text_entry_clear_all_v2,
                                    &h_g_vkb_text_entry_clear_all_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_text_entry_cursor_v2,
                                    &h_g_vkb_text_entry_cursor_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_keyboad_backspace_hlt_oled : &t_g_vkb_keyboad_backspace_hlt_v2,
                                    &h_g_vkb_keyboad_backspace_hlt_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_keyboard_backspace_normal_v2,
                                    &h_g_vkb_keyboard_backspace_normal_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_keyboad_cap_hlt_oled : &t_g_vkb_keyboad_cap_hlt_v2,
                                    &h_g_vkb_keyboad_cap_hlt_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    &t_g_vkb_keyboard_cap_normal_v2,
                                    &h_g_vkb_keyboard_cap_normal_v2));

    RET_ON_ERR (c_wgl_img_tpl_create (WGL_IMG_ST_NO_SEGMENT,
                                    b_oled ? &t_g_text_entry_clear_all_hlt_oled : &t_g_vkb_text_entry_clear_all_hlt_v2,
                                    &h_g_vkb_text_entry_clear_all_hlt_v2));
    return 0;
}

INT32 a_wdk_create_pp_popup_img_tpl(
                     WGL_HIMG_TPL_T*             ph_img_tpl,
                     UINT32                      ui4_idx
                     )
{
     INT32 i4_ret;

     if (ph_img_tpl == NULL || ui4_idx >= PP_POPUP_IMG_NUM) {
         return -1;
     }

     static WGL_IMG_T*  arr_pp_wgl_img[] = {
                    &t_g_eng_pic_popup,
                    &t_g_esp_pic_popup,
                    &t_g_fre_pic_popup,
                    &t_g_eng_power_popup,
                    &t_g_esp_power_popup,
                    &t_g_fre_power_popup,
                    &t_g_popup_button_gray,
                    &t_g_popup_button_teal
                    };
     static WGL_IMG_T*  arr_pp_wgl_img_no_energy_standard_pic[] = {
                    &t_g_eng_picmode_popup_no_energy_start_standard,
                    &t_g_esp_picmode_popup_no_energy_start_standard,
                    &t_g_fre_picmode_popup_no_energy_start_standard,
                    &t_g_eng_powermode_popup_no_energy_start,
                    &t_g_esp_powermode_popup_no_energy_start,
                    &t_g_fre_powermode_popup_no_energy_start,
                    &t_g_popup_button_gray,
                    &t_g_popup_button_teal
                    };

      static WGL_IMG_T*  arr_pp_wgl_img_no_support_energy_start_vivid[] = {
                    &t_g_eng_picmode_popup_no_energy_start_vivid,
                    &t_g_esp_picmode_popup_no_energy_start_vivid,
                    &t_g_fre_picmode_popup_no_energy_start_vivid,
                    &t_g_eng_powermode_popup_no_energy_start,
                    &t_g_esp_powermode_popup_no_energy_start,
                    &t_g_fre_powermode_popup_no_energy_start,
                    &t_g_popup_button_gray,
                    &t_g_popup_button_teal
                    };

     if (a_cfg_cust_get_support_energy_start_by_mode_name() == FALSE)
     {
          i4_ret = c_wgl_img_tpl_create(
                          WGL_IMG_ST_NO_SEGMENT,
                          arr_pp_wgl_img_no_support_energy_start_vivid[ui4_idx],
                          ph_img_tpl
                          );
     }
	 else if(a_cfg_cust_get_support_energy_start_by_mode_name())
     {
          i4_ret = c_wgl_img_tpl_create(
                          WGL_IMG_ST_NO_SEGMENT,
                          arr_pp_wgl_img[ui4_idx],
                          ph_img_tpl
                          );
     }
     else
     {
          i4_ret = c_wgl_img_tpl_create(
              			WGL_IMG_ST_NO_SEGMENT,
              			arr_pp_wgl_img_no_energy_standard_pic[ui4_idx],
              			ph_img_tpl
              			);
     }


     if(WGLR_OK != i4_ret){
         return -1;
     }

     return 0;
 }
extern BOOL a_is_oled_compensation_support();
/*-----------------------------------------------------------------------------
 * Name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_wdk_image_init (VOID)
{
    /* check init flag */
    if (b_img_init == TRUE)
    {
        return 0;
    }

    /* turn on init flag */
    b_img_init = TRUE;
    b_oled = a_is_oled_compensation_support();

    /* Create images */
    RET_ON_ERR (_wdk_image_create_share_tpl ());
    RET_ON_ERR (_wdk_image_create_vkb_tpl ());

    return 0;
}

