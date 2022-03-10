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
 * $RCSfile: page_template.c,v $
 * $Revision: #1 $
z * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_rating.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_device/menu_device.h"
#include "menu2/menu_network_phase1/menu_tos_dialog.h"

#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest_event.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "mdns/a_mdns.h"
#endif

#include "wdk/a_vkb.h"
#include "wdk/vkb/vkb.h"
#include "res/wdk/a_vkb_custom.h"
#include "nav/input_src/a_input_src.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define MENU_DLG_BTN_TEXT_CLR                   ((GL_COLOR_T){255, {255}, {255}, {255}})

#define NAME_INPUT_LST_VISIBLE_ELEM             (9)
#define NAME_INPUT_LST_X                        (0 * GRID_W)
#define NAME_INPUT_LST_Y                        (0 * GRID_H)
#define NAME_INPUT_LST_W                        (CONTENT_W)
#define NAME_INPUT_LST_H                        (NAME_INPUT_LST_VISIBLE_ELEM * GRID_H)

#define NAME_INPUT_COL0_W                       (110 )
#define NAME_INPUT_COL1_W                       (NAME_INPUT_LST_W - NAME_INPUT_COL0_W)

#define MAX_INP_REC                             (16)
#define MAX_LBL_REC                             NAME_INPUT_PREDEF_LBL_LAST_ENTRY

#define VKB_MAX_CHAR_NUM                        (32)

#define NAME_INPUT_ITEM_EDIT_BOX_IDX            (1)

#ifndef  MAX_TV_NAME_LEN
#define MAX_TV_NAME_LEN                         (32)
#endif

typedef struct _TV_NAME_T
{
    UINT32                      ui4_page_id;
    CHAR                        s_cust_lbl[MAX_TV_NAME_LEN + 1];

    HANDLE_T        h_cnt_frm;
    HANDLE_T        h_item_edit;
    HANDLE_T        h_vkb;
} TV_NAME_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_page_tv_name;

static TV_NAME_T     t_g_tv_name;
static BOOL          b_ok_btn_enable = TRUE;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static BOOL _tv_name_is_space (UTF16_T* w2s_text)
{
    UINT8  ui1_i = 0;
    UINT16 ui2_len = 0;

    if (NULL == w2s_text)
    {
        return TRUE;
    }

    ui2_len = c_uc_w2s_strlen(w2s_text);

    for(ui1_i = 0; ui1_i< ui2_len; ui1_i++)
    {
        if(w2s_text[ui1_i] != 0x20)
        {
            break;
        }
    }

    if(ui1_i<ui2_len)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

static VOID _menu_tv_name_dialog_btn_cb_fct(UINT32 ui4_key_code)
{
    a_vkb_show(t_g_tv_name.h_vkb);
    a_vkb_set_focus(t_g_tv_name.h_vkb);
    menu_pm_repaint();
}

/*----------------------------------------------------------------------------
 * Name: _tv_name_vbk_data_change_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tv_name_vbk_data_change_nfy (
    VOID*    pv_tag,
                                       UINT32   ui4_msg,
                                       VOID*    pv_param1,
                                       VOID*    pv_param2)
{
    INT32               i4_ret       = WDKR_OK;

    if (ui4_msg == VKB_MSG_DLG_CANCEL)
    {
        menu_nav_back();
    }
    else if (ui4_msg == VKB_MSG_DLG_FINISHED)
    {
        UTF16_T    w2s_new_ch_name[MAX_TV_NAME_LEN + 1] = {0};
        CHAR        s_cust_lbl[MAX_TV_NAME_LEN + 1] = {0};

        a_vkb_do_cmd(t_g_tv_name.h_vkb,
                      VKB_CMD_GET_TEXT,
                      (VOID*) w2s_new_ch_name,
                         (VOID*) (UINT32) MAX_TV_NAME_LEN);

        c_uc_w2s_to_ps(w2s_new_ch_name,
                       s_cust_lbl,
                       MAX_TV_NAME_LEN);

        c_strcpy(t_g_tv_name.s_cust_lbl, s_cust_lbl);
        a_cfg_custom_set_tv_name(s_cust_lbl);
#ifdef A_C4TV_APRON_CAST_NAME
        a_c4tv_apron_set_cast_name(s_cust_lbl);
#else
        a_cfg_custom_set_tv_name(s_cust_lbl);
#endif
        a_mdns_stop();
        a_mdns_start();

        rest_event_notify("tv_settings/cast/device_name", 0, s_cust_lbl);

        menu_nav_back();
    }
    else if (ui4_msg == VKB_MSG_DLG_KEY_EB_CLEAR)
    {
        if (BTN_SELECT == *((UINT32*)pv_param1))
        {
            b_ok_btn_enable = FALSE;
            a_vkb_enable_ok_btn(t_g_tv_name.h_vkb, b_ok_btn_enable);
        }
    }
    else if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        UINT32*  pui4_key_code = (UINT32*) pv_param1;
        BOOL     b_is_top_bottom = FALSE;
        BOOL     b_is_cancel_button = FALSE;
        VKB_CONTROL_LOGIC_T *pt_vkb_ctrl = NULL;
        UTF16_T     w2s_str[MAX_TV_NAME_LEN + 1] = {0};
        SIZE_T      z_len=0;

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_RETURN:
                menu_nav_back();
                i4_ret = WDKR_OK;
                break;
            case BTN_KB_BACKSPACE:
            case BTN_CURSOR_LEFT:
            {
                c_wgl_do_cmd(t_g_tv_name.h_vkb,
                             WGL_CMD_GL_GET_ATTACH_DATA,
                             (VOID *)&pt_vkb_ctrl,
                             NULL);
                if (pt_vkb_ctrl
                    && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_EDIT_BOX)
                {
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    a_vkb_do_cmd(t_g_tv_name.h_vkb,
                                 VKB_CMD_GET_EB_CONTENT,
                                 (VOID *)w2s_str,
                                 (VOID*)MAX_TV_NAME_LEN);

                    z_len = c_uc_w2s_strlen(w2s_str);

                    if (z_len > 0)
                    {
                        w2s_str[z_len-1] = 0;
                        b_ok_btn_enable = !_tv_name_is_space(w2s_str);

                    }

                    a_vkb_enable_ok_btn(t_g_tv_name.h_vkb, b_ok_btn_enable);
                }
                break;
            }
            case BTN_CURSOR_UP:
                i4_ret = a_vkb_current_is_top_row(t_g_tv_name.h_vkb,&b_is_top_bottom);
                c_wgl_do_cmd(t_g_tv_name.h_vkb,
                                 WGL_CMD_GL_GET_ATTACH_DATA,
                                 (VOID *)&pt_vkb_ctrl,
                                 NULL);
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }

                if ((pt_vkb_ctrl && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_OK)
                     &&(b_ok_btn_enable))
                {
                    if (TRUE == pt_vkb_ctrl->b_latin_lock &&
                        TRUE == pt_vkb_ctrl->b_latin_expand)
                    {
                        pt_vkb_ctrl->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
                        a_vkb_set_focus_to_current_btn(t_g_tv_name.h_vkb, FALSE);
                        i4_ret = WDK_NO_ACTION;
                    }
                    else
                    {
                        pt_vkb_ctrl->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
                        a_vkb_set_focus_to_current_btn(t_g_tv_name.h_vkb, FALSE);
                        i4_ret = WDK_NO_ACTION;
                    }
                }
                if ((pt_vkb_ctrl
                        && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL)
                        &&(b_ok_btn_enable))
                {
                    pt_vkb_ctrl->t_focus_item.e_type = VKB_FOCUS_WIDGET_BTN_OK;
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
                    a_vkb_set_focus_to_ok(t_g_tv_name.h_vkb);
                    i4_ret = WDK_NO_ACTION;
                }
                if(TRUE == b_is_top_bottom)
                {
                    menu_set_focus_on_backbar(TRUE);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));

                    i4_ret = WDK_NO_ACTION;
                }
                else if ((pt_vkb_ctrl
                        && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_CANCEL)
                        &&(!b_ok_btn_enable))
                {
                    if (TRUE == pt_vkb_ctrl->b_latin_lock
                            && TRUE == pt_vkb_ctrl->b_latin_expand)
                    {
                        pt_vkb_ctrl->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY;
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
                        a_vkb_set_focus_to_current_btn(t_g_tv_name.h_vkb, FALSE);
                        i4_ret = WDK_NO_ACTION;
                    }
                    else
                    {
                        pt_vkb_ctrl->t_focus_item.e_type = VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY;
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
                        a_vkb_set_focus_to_current_btn(t_g_tv_name.h_vkb, FALSE);
                        i4_ret = WDK_NO_ACTION;
                    }
                }
                break;
            case BTN_CURSOR_DOWN:
                {
                    HANDLE_T h_temp = NULL_HANDLE;
                    i4_ret = a_vkb_current_is_bottom_row(t_g_tv_name.h_vkb,&h_temp,&b_is_top_bottom);
                    c_wgl_do_cmd(t_g_tv_name.h_vkb,
                                 WGL_CMD_GL_GET_ATTACH_DATA,
                                 (VOID *)&pt_vkb_ctrl,
                                 NULL);
                    if(i4_ret != WDKR_OK)
                    {
                        return WDKR_OK;
                    }
                    if ((pt_vkb_ctrl
                        && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_BTN_OK)
                        &&(b_ok_btn_enable))
                    {
                        a_vkb_set_focus_to_cancel(t_g_tv_name.h_vkb);
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_CANCEL));
                        i4_ret = WDK_NO_ACTION;
                    }
                    if ((pt_vkb_ctrl
                        && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY)
                        &&(b_ok_btn_enable))
                    {
                        a_vkb_set_focus_to_ok(t_g_tv_name.h_vkb);
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
                        i4_ret = WDK_NO_ACTION;
                    }
                    if ((pt_vkb_ctrl
                        && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                        &&(TRUE == pt_vkb_ctrl->b_latin_lock
                            && TRUE == pt_vkb_ctrl->b_latin_expand)
                            &&(b_ok_btn_enable))
                    {
                        a_vkb_set_focus_to_ok(t_g_tv_name.h_vkb);
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
                        i4_ret = WDK_NO_ACTION;
                    }

                    if(TRUE == b_is_top_bottom)
                    {
                        menu_help_tip_keytip_set_focus(h_temp, 0, FALSE);
                        i4_ret = WDK_NO_ACTION;
                    }
                    else if (!b_ok_btn_enable)
                    {

                        if (pt_vkb_ctrl
                            && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY)
                        {
                            a_vkb_set_focus_to_cancel(t_g_tv_name.h_vkb);
                            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_CANCEL));
                            i4_ret = WDK_NO_ACTION;
                        }
                        else if ((pt_vkb_ctrl
                            && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                            &&(TRUE == pt_vkb_ctrl->b_latin_lock
                            && TRUE == pt_vkb_ctrl->b_latin_expand))
                        {
                            a_vkb_set_focus_to_cancel(t_g_tv_name.h_vkb);
                            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_CANCEL));
                            i4_ret = WDK_NO_ACTION;
                        }
                    }
                }
                break;
			case BTN_SELECT:
                i4_ret = a_vkb_current_is_cancel_btn(t_g_tv_name.h_vkb,
													&b_is_cancel_button);
				if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }
				if(TRUE == b_is_cancel_button)
                {
                	menu_nav_back ();
					return WDK_NO_ACTION;
                }

                c_wgl_do_cmd(t_g_tv_name.h_vkb,
                             WGL_CMD_GL_GET_ATTACH_DATA,
                             (VOID *)&pt_vkb_ctrl,
                             NULL);

                if (pt_vkb_ctrl)
                {
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    a_vkb_do_cmd(t_g_tv_name.h_vkb,
                                 VKB_CMD_GET_TEXT,
                                 (VOID *) w2s_str,
                                 (VOID *) MAX_TV_NAME_LEN);

                    z_len = c_uc_w2s_strlen(w2s_str);

                    b_ok_btn_enable = !_tv_name_is_space(w2s_str) ? TRUE : FALSE;

                    if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY
                        && pt_vkb_ctrl->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_DEL_KEY_IDX)
                    {
                        if (b_ok_btn_enable && z_len > 0)
                        {
                            w2s_str[z_len-1] = 0;
                            b_ok_btn_enable = !_tv_name_is_space(w2s_str) ? TRUE : FALSE;
                        }
                    }
                    else if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                    {
                        UINT8 ui1_key_idx = 0;
                        UINT8 ui1_elem_idx = 0;

                        ui1_key_idx = pt_vkb_ctrl->ui1_cur_latin_key_idx;
                        ui1_elem_idx = pt_vkb_ctrl->t_focus_item.t_normal_key.ui1_focus_idx_col
                                        - pt_vkb_ctrl->at_keypad_latin_key[ui1_key_idx].ui1_col_offset;
                        if(z_len >= MAX_TV_NAME_LEN)
                        {
                            menu_tos_dialog_show(MLM_MENU_KEY_ITEM_TV_NAME,
                                                 MLM_MENU_KEY_LENGTH_OF_CHARACTER_IS_TOO_LARGER,
                                                 MLM_MENU_KEY_OK,
                                                 _menu_tv_name_dialog_btn_cb_fct,
                                                 TRUE);
                            return WDK_NO_ACTION;
                        }
                        else if (TRUE == pt_vkb_ctrl->b_latin_lock
                            && FALSE == pt_vkb_ctrl->b_latin_expand)
                        {
                            //DO Nothing
                        }
                        else if (TRUE == pt_vkb_ctrl->b_latin_lock
                                && TRUE == pt_vkb_ctrl->b_latin_expand
                                && ui1_elem_idx >= pt_vkb_ctrl->at_keypad_latin_key[ui1_key_idx].ui1_elem_num)
                        {
                            //DO Nothing
                        }
                        else
                        {
                            b_ok_btn_enable = TRUE;
                        }

                    }

                    a_vkb_enable_ok_btn(t_g_tv_name.h_vkb, b_ok_btn_enable);
                   // a_vkb_repaint(t_g_tv_name.h_vkb);
                }
				break;
            case BTN_DIGIT_0:
            case BTN_DIGIT_1:
            case BTN_DIGIT_2:
            case BTN_DIGIT_3:
            case BTN_DIGIT_4:
            case BTN_DIGIT_5:
            case BTN_DIGIT_6:
            case BTN_DIGIT_7:
            case BTN_DIGIT_8:
            case BTN_DIGIT_9:
                c_memset(w2s_str, 0, sizeof(w2s_str));
                a_vkb_do_cmd(t_g_tv_name.h_vkb,
                             VKB_CMD_GET_TEXT,
                             (VOID *) w2s_str,
                             (VOID *) MAX_TV_NAME_LEN);

                z_len = c_uc_w2s_strlen(w2s_str);
                if(z_len >= MAX_TV_NAME_LEN)
                {
                    menu_tos_dialog_show(MLM_MENU_KEY_ITEM_TV_NAME,
                                         MLM_MENU_KEY_LENGTH_OF_CHARACTER_IS_TOO_LARGER,
                                         MLM_MENU_KEY_OK,
                                         _menu_tv_name_dialog_btn_cb_fct,
                                         TRUE);
                    return WDK_NO_ACTION;
                }
                break;
            default:

                break;
        }
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _name_input_homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tv_name_homebar_proc_fct (
    HANDLE_T                    h_widget,
                               UINT32      ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2)
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;
        case BTN_CURSOR_DOWN :
            menu_set_focus_on_backbar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            return WGLR_OK;
        case BTN_EXIT:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _name_input_backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tv_name_backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2)
{
    if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32  ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT :
        case BTN_EXIT:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        case BTN_CURSOR_UP:
            menu_set_focus_on_homebar(TRUE);
            return WGLR_OK;
        case BTN_CURSOR_DOWN:
            a_vkb_set_focus_ex(t_g_tv_name.h_vkb);
            return WGLR_OK;
        default:
            break;
        }

    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _tv_name_item_edit_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tv_name_item_frm_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    CHAR        s_cust_lbl[MAX_TV_NAME_LEN+1];
    UTF16_T     w2s_str[MAX_TV_NAME_LEN + 1];
    //HANDLE_T    h_eb = NULL_HANDLE;

    if (WGL_MSG_NOTIFY == ui4_msg)
    {
        //h_eb = (HANDLE_T)pv_param1;
        WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)pv_param2;

        if (WGL_NC_EB_CHANGED == pt_nfy_data->ui4_nc_code)
        {
            c_memset(s_cust_lbl, 0, sizeof(s_cust_lbl));
            c_memset(w2s_str, 0, sizeof(w2s_str));

            a_vkb_do_cmd(t_g_tv_name.h_vkb,
                         VKB_CMD_GET_EB_CONTENT,
                         (VOID *)w2s_str,
                         (VOID*)(MAX_TV_NAME_LEN+1));

            w2s_str[MAX_TV_NAME_LEN] = 0;
            c_uc_w2s_to_ps(w2s_str, s_cust_lbl, MAX_TV_NAME_LEN);

            b_ok_btn_enable = !_tv_name_is_space(w2s_str) ? TRUE : FALSE;
            a_vkb_enable_ok_btn(t_g_tv_name.h_vkb, b_ok_btn_enable);

            menu_pm_repaint();

            return WGLR_OK;
        }
    }
    /*else if (WGL_MSG_COMMAND == ui4_msg)
    {
        if (WGL_CMD_EB_SET_CHANGE_FLAG == (UINT32)pv_param1)
        {
            c_memset(s_cust_lbl, 0, sizeof(s_cust_lbl));
            c_memset(w2s_str, 0, sizeof(w2s_str));

            a_vkb_do_cmd(t_g_tv_name.h_vkb,
                         VKB_CMD_GET_TEXT,
                         (VOID *) w2s_str,
                         (VOID *) MAX_TV_NAME_LEN);
            b_ok_btn_enable = !_tv_name_is_space(w2s_str);
            a_vkb_enable_ok_btn(t_g_tv_name.h_vkb, b_ok_btn_enable);

            menu_pm_repaint();
        }
    }*/

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _tv_name_page_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _tv_name_page_create(VOID)
{
    INT32               i4_ret = MENUR_OK;
    VKB_INIT_T          t_init_data;

    /* Create Virtual key board */
    t_init_data.h_parent            = t_g_tv_name.h_cnt_frm;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_MENU|VKB_STYLE_MASK_WITH_EB_CLEAR;
    t_init_data.t_gui_rc.i4_left    = FRAME_LEFT_RIGHT_INTV;

    t_init_data.t_gui_rc.i4_top     = 0;
    t_init_data.pf_data_change_fct  = _tv_name_vbk_data_change_nfy;
    t_init_data.pv_tag              = NULL;
    i4_ret = a_vkb_create(&t_init_data,&(t_g_tv_name.h_vkb));

    a_vkb_do_cmd(t_g_tv_name.h_vkb,
                 VKB_CMD_SET_MAX_CHAR_NUM,
                 (VOID*) (25),  //  MAX_TV_NAME_LEN+1
                 NULL);

    c_wgl_set_visibility(t_g_tv_name.h_cnt_frm, WGL_SW_HIDE);

    return i4_ret;
}

INT32 _tv_name_page_help_tip_cb(
                HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2,
                BOOL*               pb_processed)
{
    *pb_processed = TRUE;
    menu_nav_back();

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 *
 *  Page Lifecycle callback functions
 *
 ----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32               i4_ret       = MENUR_FAIL;
    HANDLE_T            h_cnt_frm;
    T_HELP_TIP_REG      t_help_tip_reg;

    do
    {
        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        c_memset(&t_g_tv_name, 0, sizeof(TV_NAME_T));
        t_g_tv_name.ui4_page_id = ui4_page_id;
        t_g_tv_name.h_cnt_frm   = h_cnt_frm;

        _tv_name_page_create();

        menu_page_set_data(ui4_page_id, &t_g_tv_name);

        c_wgl_set_widget_proc(t_g_tv_name.h_vkb,_tv_name_item_frm_proc_fct);

        /* Register help tip back key processer */
        t_help_tip_reg.ui4_page_id = ui4_page_id;
        t_help_tip_reg.p_fct = _tv_name_page_help_tip_cb;
        menu_help_tip_key_reg(E_HELP_TIP_CB_PAGE_TV_NAME,  &t_help_tip_reg);

    } while(0);

    return i4_ret;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    menu_tos_dialog_hide(FALSE);
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    GL_RECT_T t_rect;
    HANDLE_T h_last_shadow_item = NULL_HANDLE;
    UTF16_T w2s_str[MAX_TV_NAME_LEN+1] = {0};
    UINT32  ui4_len = MAX_TV_NAME_LEN;

    a_cfg_custom_get_tv_name(t_g_tv_name.s_cust_lbl,&ui4_len);
    DBG_LOG_PRINT (("\n[menu_tv_name] _on_page_get_focus() s_cust_lbl[%s],ui4_len[%d]\n",t_g_tv_name.s_cust_lbl,ui4_len));

    //c_strcpy(t_g_tv_name.s_cust_lbl, APP_CFG_CUSTOM_TV_NAME_DFT);

    DBG_LOG_PRINT(("%s() %d: s_cust_lbl=[%s]\n\n", __FUNCTION__, __LINE__, t_g_tv_name.s_cust_lbl));
    c_uc_ps_to_w2s(t_g_tv_name.s_cust_lbl, w2s_str, MAX_TV_NAME_LEN);

    a_vkb_do_cmd(t_g_tv_name.h_vkb,
                 VKB_CMD_SET_INITIAL_TEXT,
                 (VOID *)w2s_str,
                 (VOID *)0xFF);

    menu_main_set_title(MLM_MENU_KEY_ITEM_TV_NAME);
    menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_NAME_TV_OK));
    menu_set_backbar_proc (_tv_name_backbar_proc_fct) ;
    menu_set_homebar_proc(_tv_name_homebar_proc_fct);

    c_wgl_set_visibility(t_g_tv_name.h_cnt_frm, WGL_SW_NORMAL);

    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = VKB_MAIN_FRAME_H + CONTENT_Y + 35;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    a_vkb_show(t_g_tv_name.h_vkb);
    a_vkb_set_focus(t_g_tv_name.h_vkb);

    b_ok_btn_enable = !_tv_name_is_space(w2s_str) ? TRUE : FALSE;
    a_vkb_enable_ok_btn(t_g_tv_name.h_vkb, b_ok_btn_enable);
    c_wgl_repaint(t_g_tv_name.h_cnt_frm,NULL,TRUE);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    c_wgl_set_visibility(t_g_tv_name.h_cnt_frm, WGL_SW_HIDE);

    menu_set_backbar_proc(NULL);
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        External functions
-----------------------------------------------------------------------------*/
extern INT32 menu_page_tv_name_init(VOID)
{
    t_g_menu_page_tv_name.pf_menu_page_create      = _on_page_create;
    t_g_menu_page_tv_name.pf_menu_page_destroy     = _on_page_destroy;
    t_g_menu_page_tv_name.pf_menu_page_show        = _on_page_show;
    t_g_menu_page_tv_name.pf_menu_page_hide        = _on_page_hide;
    t_g_menu_page_tv_name.pf_menu_page_get_focus   = _on_page_get_focus;
    t_g_menu_page_tv_name.pf_menu_page_lose_focus  = _on_page_lose_focus;
    t_g_menu_page_tv_name.pf_menu_page_update      = _on_page_update;

    return MENUR_OK;
}

