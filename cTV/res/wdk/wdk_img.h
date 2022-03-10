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
 * $RCSfile: wdk_img.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 80d824ab48f4d49e3d38d28c8fc07509 $
 *
 * Description:
 *      This file contains the images used by the Menu application.
 *---------------------------------------------------------------------------*/
#ifndef _WDK_IMG_H_
#define _WDK_IMG_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_gl_nc.h"
#include "u_wgl_sets.h"

#include "c_handle.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_rect.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define ENG_PIC_POPUP_BACKGROUND   (0)
#define ESP_PIC_POPUP_BACKGROUND   (1)
#define FRE_PIC_POPUP_BACKGROUND   (2)
#define ENG_PW_POPUP_BACKGROUND    (3)
#define ESP_PW_POPUP_BACKGROUND    (4)
#define FRE_PW_POPUP_BACKGROUND    (5)
#define PP_POPUP_BUTTON_GRAY       (6)
#define PP_POPUP_BUTTON_TEAL       (7)
#define PP_POPUP_IMG_NUM           (8)

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
/* Share */

/* VKB (Virtual KeyBoard) related */
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_main_frm_background_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_keypad_hlt_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_big_keypad_hlt_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_space_keypad_hlt_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_keypad_bar_img;
extern WGL_HIMG_TPL_T             h_g_wdk_img_Bar;

extern WGL_HIMG_TPL_T             h_g_wdk_vkb_keypad_bar_hlt_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_capslock_keypad_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_capslock_keypad_hlt_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_capslock_keypad_dis_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_delete_keypad_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_delete_keypad_hlt_img;

extern WGL_HIMG_TPL_T             h_g_wdk_vkb_edit_img;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_edit_bk;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_edit_hlt_bk;

extern WGL_HIMG_TPL_T             h_g_wdk_vkb_eb_clear;
extern WGL_HIMG_TPL_T             h_g_wdk_vkb_eb_clear_hlt;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_hlt;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_spa_hlt;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_symb_hlt;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_board;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_carat_passcode;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_character_shift;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_character_shift_hlt;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_character_back;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_character_back_hlt;

extern WGL_HIMG_TPL_T             h_g_wdk_img_key_back_highlight;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_back_unhighlight;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_shift_highlight;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_shift_unhighlight;
extern WGL_HIMG_TPL_T             h_g_wdk_img_key_shift_gray;
extern WGL_HIMG_TPL_T             h_g_wdk_img_delete_gray;

extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_backspace_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_capital_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_clear_all_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_highlight_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_special_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_symbols_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_text_entry_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_text_entry_highlight;
extern WGL_HIMG_TPL_T             h_g_vkb_text_entry_clear_all_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_text_entry_cursor_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboad_backspace_hlt_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_backspace_normal_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboad_cap_hlt_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_keyboard_cap_normal_v2;
extern WGL_HIMG_TPL_T             h_g_vkb_text_entry_clear_all_hlt_v2;

/*anamition*/
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_1;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_2;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_3;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_4;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_5;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_6;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_7;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_8;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_9;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_10;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_11;
extern WGL_HIMG_TPL_T           h_g_wdk_img_loading_icon_12;

/*Animation in BT sidebar menu*/
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_1;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_2;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_3;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_4;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_5;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_6;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_7;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_8;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_9;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_10;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_11;
extern WGL_HIMG_TPL_T           h_g_wdk_img_bt_loading_icon_12;

extern WGL_HIMG_TPL_T           h_g_wdk_img_signal_icon_1;
extern WGL_HIMG_TPL_T           h_g_wdk_img_signal_icon_2;
extern WGL_HIMG_TPL_T           h_g_wdk_img_signal_icon_3;
extern WGL_HIMG_TPL_T           h_g_wdk_img_signal_icon_4;
extern WGL_HIMG_TPL_T           h_g_wdk_img_signal_icon_5;

extern WGL_HIMG_TPL_T           h_g_wdk_cnt_indctr_img[4] ;

extern WGL_HIMG_TPL_T			h_g_wdk_gradient_btm;
extern WGL_HIMG_TPL_T			h_g_wdk_gradient_center;
extern WGL_HIMG_TPL_T			h_g_wdk_gradient_top;
extern WGL_HIMG_TPL_T			h_g_wdk_toast_box;
extern WGL_HIMG_TPL_T			h_g_wdk_toast_box_settings;
extern WGL_HIMG_TPL_T			h_g_wdk_toast_box_vol;
extern WGL_HIMG_TPL_T			h_g_wdk_track_cap_left;
extern WGL_HIMG_TPL_T			h_g_wdk_track_cap_right;
extern WGL_HIMG_TPL_T			h_g_wdk_track_fill;
extern WGL_HIMG_TPL_T			h_g_wdk_warning;
extern WGL_HIMG_TPL_T			h_g_wdk_eq_hash_mark;
extern WGL_HIMG_TPL_T           h_g_wdk_content_box;

/*toast img*/
extern WGL_HIMG_TPL_T			h_g_wdk_single_select_list;
extern WGL_HIMG_TPL_T		    h_g_setting_slider;
extern WGL_HIMG_TPL_T			h_g_string_toast;
extern WGL_HIMG_TPL_T		    h_g_warning_toast;
extern WGL_HIMG_TPL_T           h_g_energy_star;
extern WGL_HIMG_TPL_T           h_g_energy_star_gray;
extern WGL_HIMG_TPL_T           h_g_zoom_energy_star;
extern WGL_HIMG_TPL_T           h_g_zoom_energy_star_gray;

extern WGL_HIMG_TPL_T           h_g_dolby_vision_icon;

extern WGL_HIMG_TPL_T              h_g_nav_selected;
extern WGL_HIMG_TPL_T              h_g_nav_unselected;

extern WGL_HIMG_TPL_T              h_g_nav_spinner_1;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_2;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_3;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_4;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_5;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_6;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_7;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_8;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_9;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_10;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_11;
extern WGL_HIMG_TPL_T              h_g_nav_spinner_12;

/* API's */
extern INT32 a_wdk_image_init (VOID);
extern INT32 a_wdk_create_pp_popup_img_tpl(
                     WGL_HIMG_TPL_T*             ph_img_tpl,
                     UINT32                      ui4_idx
                     );

#endif /* _WDK_IMG_H_ */

