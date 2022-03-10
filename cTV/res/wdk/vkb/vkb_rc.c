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
 * $RCSfile: pin_rc.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Dongdong Peng $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_wgl.h"
#include "u_wgl_image.h"
#include "u_irrc_btn_def.h"

#include "wdk/a_vkb.h"

/* Color definition file */
#include "res/wdk/wdk_clr.h"

/* Image definition file */
#include "res/wdk/wdk_img.h"

#include "res/wdk/vkb/vkb_rc.h"

/* Reuse menu resource */
#include "res/menu2/menu_clr.h"

/* Reuse nav resource */
#include "res/nav/nav_colors.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/
#if 0
static GL_COLOR_T t_vkb_text_nml_clr =		/* White */
{
	255, {255}, {255}, {255}
};

static GL_COLOR_T t_vkb_item_nml_clr =		/* GRAY */
{
	255, {100}, {100}, {100}
};
#endif

/* resource init flag */
static BOOL                 b_vkb_rc_init = FALSE;

VKB_RC_CONFIG_DATA_T        t_g_vkb_rc_cfg;
VKB_RC_CONFIG_DATA_T        t_g_vkb_rc_cfg2;

VKB_RC_CONFIG_DATA_T        t_g_vkb_rc_cfg_v2;

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
* Name
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
INT32  vkb_rc_init(VKB_RC_CONFIG_DATA_T** ppt_vkb_rc_cfg)
{
    /* check init flag */
    if (b_vkb_rc_init == TRUE)
    {
        /* save general resource configuration data, shared by all VKB instance */
        *ppt_vkb_rc_cfg = &t_g_vkb_rc_cfg;

        return WDKR_OK;
    }

    /* init wdk resource first */
    a_wdk_image_init();
    a_wdk_color_init();

    /* turn on init flag */
    b_vkb_rc_init = TRUE;

    /* save general resource configuration data, shared by all VKB instance */
    *ppt_vkb_rc_cfg = &t_g_vkb_rc_cfg;

    /* start initialization */
    c_memset(&t_g_vkb_rc_cfg, 0, sizeof(VKB_RC_CONFIG_DATA_T));
    c_memset(&t_g_vkb_rc_cfg2, 0, sizeof(VKB_RC_CONFIG_DATA_T));

    /* init images */
    t_g_vkb_rc_cfg.h_main_frm_bk_img        = h_g_wdk_vkb_main_frm_background_img;

    t_g_vkb_rc_cfg.h_keypad_bk_img          = NULL_HANDLE;
    t_g_vkb_rc_cfg.h_keypad_bk_hlt_img      = h_g_wdk_vkb_keypad_hlt_img;
    t_g_vkb_rc_cfg.h_keypad_big_bk_img      = NULL_HANDLE;
    t_g_vkb_rc_cfg.h_keypad_big_bk_hlt_img  = h_g_wdk_vkb_big_keypad_hlt_img;
    t_g_vkb_rc_cfg.h_keypad_space_bk_img    = NULL_HANDLE;
    t_g_vkb_rc_cfg.h_keypad_space_bk_hlt_img= h_g_wdk_vkb_space_keypad_hlt_img;

    t_g_vkb_rc_cfg.h_keypad_capslock_bk_img    = h_g_wdk_vkb_capslock_keypad_img;
    t_g_vkb_rc_cfg.h_keypad_capslock_bk_hlt_img= h_g_wdk_vkb_capslock_keypad_hlt_img;
    t_g_vkb_rc_cfg.h_keypad_capslock_bk_dis_img= h_g_wdk_img_key_shift_gray;
    t_g_vkb_rc_cfg.h_keypad_delete_bk_img      = h_g_wdk_vkb_delete_keypad_img;
    t_g_vkb_rc_cfg.h_keypad_delete_bk_hlt_img  = h_g_wdk_vkb_delete_keypad_hlt_img;
    t_g_vkb_rc_cfg.h_keypad_delete_bk_dis_img  = h_g_wdk_img_delete_gray;



    t_g_vkb_rc_cfg.h_keypad_bar_bk_img      = h_g_wdk_img_Bar; /* h_g_wdk_vkb_keypad_bar_img */
    t_g_vkb_rc_cfg.h_keypad_bar_bk_hlt_img  = h_g_wdk_vkb_keypad_bar_hlt_img;

    t_g_vkb_rc_cfg.h_keypad_eb_clear_img    = h_g_wdk_vkb_eb_clear;
    t_g_vkb_rc_cfg.h_keypad_eb_clear_img_hlt= h_g_wdk_vkb_eb_clear_hlt;

    /* init color */
    t_g_vkb_rc_cfg.t_label_txt_clr          = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg.t_label_txt_dis_clr      = NAV_COLOR(NAV_COLOR_ID_TEXT);

    t_g_vkb_rc_cfg.t_keypad_key_txt_clr     = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg.t_keypad_key_txt_hlt_clr = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg.t_keypad_key_txt_dis_clr = t_g_menu_color_bk2_txt_disable;//NAV_COLOR(NAV_COLOR_ID_TEXT);

    t_g_vkb_rc_cfg.t_btn_txt_clr            = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg.t_btn_txt_hlt_clr        = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg.t_btn_txt_dis_clr        = t_g_menu_color_bk2_txt_disable;//NAV_COLOR(NAV_COLOR_ID_POP_BLUR);

    t_g_vkb_rc_cfg.t_editbox_txt_clr        = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg.t_editbox_txt_hlt_clr    = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg.t_editbox_txt_dis_clr    = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg.t_editbox_cursor_clr     = NAV_COLOR(NAV_COLOR_ID_TEXT);

    /* init images for phase2 */
    t_g_vkb_rc_cfg2.h_main_frm_bk_img        = h_g_wdk_img_key_board;

    t_g_vkb_rc_cfg2.h_keypad_bk_img          = NULL_HANDLE;
    t_g_vkb_rc_cfg2.h_keypad_bk_hlt_img      = h_g_wdk_img_key_hlt;
    t_g_vkb_rc_cfg2.h_keypad_big_bk_img      = NULL_HANDLE;
    t_g_vkb_rc_cfg2.h_keypad_big_bk_hlt_img  = h_g_wdk_img_key_symb_hlt;
    t_g_vkb_rc_cfg2.h_keypad_space_bk_img    = NULL_HANDLE;
    t_g_vkb_rc_cfg2.h_keypad_space_bk_hlt_img= h_g_wdk_img_key_spa_hlt;

    t_g_vkb_rc_cfg2.h_keypad_capslock_bk_img    = h_g_wdk_img_key_shift_unhighlight;//NULL_HANDLE;
    t_g_vkb_rc_cfg2.h_keypad_capslock_bk_hlt_img= h_g_wdk_img_key_shift_highlight;//h_g_wdk_img_key_symb_hlt;
    t_g_vkb_rc_cfg2.h_keypad_capslock_bk_dis_img= NULL_HANDLE;
    t_g_vkb_rc_cfg2.h_keypad_delete_bk_img      = h_g_wdk_img_key_back_unhighlight;//NULL_HANDLE;
    t_g_vkb_rc_cfg2.h_keypad_delete_bk_hlt_img  = h_g_wdk_img_key_back_highlight;//h_g_wdk_img_key_symb_hlt;



    t_g_vkb_rc_cfg2.h_keypad_bar_bk_img      = h_g_wdk_img_Bar; /* h_g_wdk_vkb_keypad_bar_img */
    t_g_vkb_rc_cfg2.h_keypad_bar_bk_hlt_img  = h_g_wdk_vkb_keypad_bar_hlt_img;

    t_g_vkb_rc_cfg2.h_keypad_eb_clear_img    = h_g_wdk_vkb_eb_clear;
    t_g_vkb_rc_cfg2.h_keypad_eb_clear_img_hlt= h_g_wdk_vkb_eb_clear_hlt;

    /* init color */
    t_g_vkb_rc_cfg2.t_label_txt_clr          = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg2.t_label_txt_dis_clr      = NAV_COLOR(NAV_COLOR_ID_TEXT);

    t_g_vkb_rc_cfg2.t_keypad_key_txt_clr     = NAV_COLOR(NAV_COLOR_ID_TEXT_COMP);
    t_g_vkb_rc_cfg2.t_keypad_key_txt_hlt_clr = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg2.t_keypad_key_txt_dis_clr = t_g_menu_color_bk2_txt_disable;//NAV_COLOR(NAV_COLOR_ID_TEXT_COMP);

    t_g_vkb_rc_cfg2.t_btn_txt_clr            = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg2.t_btn_txt_hlt_clr        = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg2.t_btn_txt_dis_clr        = NAV_COLOR(NAV_COLOR_ID_POP_BLUR);

    t_g_vkb_rc_cfg2.t_editbox_txt_clr        = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg2.t_editbox_txt_hlt_clr    = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg2.t_editbox_txt_dis_clr    = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg2.t_editbox_cursor_clr     = NAV_COLOR(NAV_COLOR_ID_TEXT);

    /* init images for phase2 */
    t_g_vkb_rc_cfg_v2.h_main_frm_bk_img        = NULL_HANDLE;
    t_g_vkb_rc_cfg_v2.h_kb_frm_bk_img          = h_g_vkb_keyboard_v2;

    t_g_vkb_rc_cfg_v2.h_keypad_bk_img          = NULL_HANDLE;
    t_g_vkb_rc_cfg_v2.h_keypad_bk_hlt_img      = h_g_vkb_keyboard_highlight_v2;
    t_g_vkb_rc_cfg_v2.h_keypad_big_bk_img      = NULL_HANDLE;
    t_g_vkb_rc_cfg_v2.h_keypad_big_bk_hlt_img  = h_g_vkb_keyboard_highlight_v2;//h_g_vkb_keyboard_symbols_v2;
    t_g_vkb_rc_cfg_v2.h_keypad_space_bk_img    = NULL_HANDLE;
    t_g_vkb_rc_cfg_v2.h_keypad_space_bk_hlt_img= h_g_vkb_keyboard_highlight_v2;//h_g_wdk_img_key_spa_hlt;

    t_g_vkb_rc_cfg_v2.h_keypad_capslock_bk_img    = h_g_vkb_keyboard_cap_normal_v2;//h_g_vkb_keyboard_capital_v2;//h_g_wdk_img_key_shift_unhighlight;
    t_g_vkb_rc_cfg_v2.h_keypad_capslock_bk_hlt_img= h_g_vkb_keyboad_cap_hlt_v2;//h_g_vkb_keyboard_capital_v2;//h_g_wdk_img_key_shift_highlight;
    t_g_vkb_rc_cfg_v2.h_keypad_capslock_bk_dis_img= NULL_HANDLE;
    t_g_vkb_rc_cfg_v2.h_keypad_delete_bk_img      = h_g_vkb_keyboard_backspace_normal_v2;//h_g_wdk_img_key_back_unhighlight;
    t_g_vkb_rc_cfg_v2.h_keypad_delete_bk_hlt_img  = h_g_vkb_keyboad_backspace_hlt_v2;//h_g_wdk_img_key_back_highlight;



    t_g_vkb_rc_cfg_v2.h_keypad_bar_bk_img      = NULL_HANDLE;//h_g_wdk_img_Bar;
    t_g_vkb_rc_cfg_v2.h_keypad_bar_bk_hlt_img  = h_g_vkb_keyboard_highlight_v2;//h_g_wdk_vkb_keypad_bar_hlt_img;

    t_g_vkb_rc_cfg_v2.h_keypad_eb_clear_img    = h_g_vkb_text_entry_clear_all_v2;//h_g_wdk_vkb_eb_clear;
    t_g_vkb_rc_cfg_v2.h_keypad_eb_clear_img_hlt= h_g_vkb_text_entry_clear_all_hlt_v2;//h_g_vkb_text_entry_clear_all_v2;//h_g_wdk_vkb_eb_clear_hlt;

    /* init color */
    t_g_vkb_rc_cfg_v2.t_label_txt_clr          = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg_v2.t_label_txt_dis_clr      = NAV_COLOR(NAV_COLOR_ID_TEXT);

    t_g_vkb_rc_cfg_v2.t_keypad_key_txt_clr     = NAV_COLOR(NAV_COLOR_ID_TEXT);//(NAV_COLOR_ID_TEXT_COMP);
    t_g_vkb_rc_cfg_v2.t_keypad_key_txt_hlt_clr = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg_v2.t_keypad_key_txt_dis_clr = t_g_menu_color_bk2_txt_disable;//NAV_COLOR(NAV_COLOR_ID_TEXT_COMP);

    t_g_vkb_rc_cfg_v2.t_btn_txt_clr            = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg_v2.t_btn_txt_hlt_clr        = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg_v2.t_btn_txt_dis_clr        = NAV_COLOR(NAV_COLOR_ID_POP_BLUR);

    t_g_vkb_rc_cfg_v2.t_editbox_txt_clr        = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg_v2.t_editbox_txt_hlt_clr    = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg_v2.t_editbox_txt_dis_clr    = NAV_COLOR(NAV_COLOR_ID_TEXT);
    t_g_vkb_rc_cfg_v2.t_editbox_cursor_clr     = NAV_COLOR(NAV_COLOR_ID_TEXT);
    return WDKR_OK;
}

INT32 vkb_rc_chg(UINT8 ui2_chg, VKB_RC_CONFIG_DATA_T** ppt_vkb_rc_cfg)
{
    if (b_vkb_rc_init == FALSE)
    {
        return WDKR_FAIL;
    }

    switch (ui2_chg)
    {
        case 0:
        {
            *ppt_vkb_rc_cfg = &t_g_vkb_rc_cfg;
            break;
        }
        case 1:
        {
            *ppt_vkb_rc_cfg = &t_g_vkb_rc_cfg2;
            break;
        }
        case 2:
        {
            *ppt_vkb_rc_cfg = &t_g_vkb_rc_cfg_v2;
            break;
        }
        default:
            *ppt_vkb_rc_cfg = &t_g_vkb_rc_cfg;
            break;
    }

    return WDKR_OK;
}


