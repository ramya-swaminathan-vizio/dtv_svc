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
 * $RCSfile: menu_page_lct_code.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/26 $
 * $SWAuthor: Jerry Fan $
 * $MD5HEX: 30507e5e42ff5e3da3828ba91305ea5e $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"

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

#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_dbg.h"

#ifdef ATSC_LCT_CODE_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_lct_code;

/* idx 0 for state code , idx 1 for county code */
static CHAR          as_digits[2][APP_CFG_MAX_LCT_LEN];

static HANDLE_T      h_cnt_frm;
/* state code and county code */
static HANDLE_T      h_eb_code_st;
static HANDLE_T      h_eb_code_ct;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _frm_lct_code_proc_fct(HANDLE_T    h_widget,
                                    UINT32      ui4_msg,
                                    VOID*       param1,
                                    VOID*       param2);

static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2);


/*----------------------------------------------------------------------------
 * Name: _eb_update_value
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
static INT32 _eb_update_value(HANDLE_T h_widget)
{
    INT32   i4_ret;
    UINT16  ui2_lct_idx, ui2_digit_idx;
    UTF16_T w2s_buf[APP_CFG_MAX_LCT_LEN];

    if (h_widget == h_eb_code_st)
    {
        ui2_lct_idx   = APP_CFG_RECID_LCT_ST;
        ui2_digit_idx = 0;
    }
    else
    {
        ui2_lct_idx   = APP_CFG_RECID_LCT_CT;
        ui2_digit_idx = 1;
    }

    c_memset(w2s_buf, 0, sizeof(w2s_buf));
    i4_ret = a_cfg_get_lct_code(ui2_lct_idx,
                                w2s_buf,
                                APP_CFG_MAX_LCT_LEN);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF));
    MENU_CHK_FAIL(i4_ret);

    c_uc_w2s_to_ps(w2s_buf, as_digits[ui2_digit_idx], APP_CFG_MAX_LCT_LEN);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _eb_set_value
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
static INT32 _eb_set_value(HANDLE_T    h_widget,
                           UINT16      ui2_value)
{
    INT32 i4_ret, i4_i;
    UINT16  ui2_idx      = (h_widget == h_eb_code_st) ? 0 : 1;
    UINT16  ui2_last_idx = (h_widget == h_eb_code_st) ? (2-1) : (3-1);
    UTF16_T w2s_buf[APP_CFG_MAX_LCT_LEN];

    c_memset(w2s_buf, 0, sizeof(w2s_buf));

    /* shift codes, origin "12" input "3" -> "23" */
    for(i4_i = 0; i4_i < ui2_last_idx; i4_i++)
    {
        as_digits[ui2_idx][i4_i] = as_digits[ui2_idx][i4_i+1];
    }
    as_digits[ui2_idx][ui2_last_idx] = (char)(ui2_value+'0');

    c_uc_ps_to_w2s(as_digits[ui2_idx], w2s_buf, APP_CFG_MAX_LCT_LEN);
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_EB_SET_TEXT,
                          WGL_PACK(w2s_buf),
                          WGL_PACK(0xFF));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _init_eb
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
static INT32 _init_eb(
    HANDLE_T    h_parent,
    UINT8       ui1_idx,
    UINT16      ui2_input_limit,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    WGL_EB_KEY_MAP_T    t_eb_key_map;

    i4_ret = menu_edit_create(h_parent,
                              ui1_idx,
                              FALSE,
                              _widgets_proc_fct,
                              ph_widget);
    MENU_CHK_FAIL(i4_ret);


    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK(ui2_input_limit),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_enter_editing = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _set_nav
 *
 * Description: Set the navigation
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _set_nav(VOID)
{
    /* All navigation is controlled by application*/
    INT32               i4_ret       = 0;
    INT32               i4_chain_len = 0;
    INT32               i4_i         = 0;
    WGL_KEY_LINK_T      at_key_lnk[4];
    HANDLE_T            ah_chain[5];

    ah_chain[i4_chain_len++] = h_eb_code_st;
    ah_chain[i4_chain_len++] = h_eb_code_ct;

    for (i4_i = 0; i4_i < i4_chain_len; i4_i++)
    {
        at_key_lnk[0].ui4_key = BTN_CURSOR_UP;
        at_key_lnk[0].h_widget = ah_chain[i4_i == 0 ? i4_chain_len-1: i4_i-1];
        at_key_lnk[1].ui4_key = BTN_CURSOR_DOWN;
        at_key_lnk[1].h_widget = ah_chain[i4_i == i4_chain_len-1 ? 0: i4_i+1];
        i4_ret = c_wgl_set_navigation(ah_chain[i4_i], 2, at_key_lnk);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _chg_lang
 *
 * Description: This function is called when the language is changed
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _chg_lang(VOID)
{
    INT32   i4_ret = 0;

    i4_ret = menu_edit_chg_lang(h_eb_code_ct, MLM_MENU_KEY_LOC_CODE_COUNTY);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_edit_chg_lang(h_eb_code_st, MLM_MENU_KEY_LOC_CODE_STATE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_eb_state_notify
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
static INT32 _on_eb_state_notify(WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_GL_GET_FOCUS:
        {
        }
    default:
        break;
    }
    return WMPR_DONE;
}

/*----------------------------------------------------------------------------
 * Name: _on_eb_county_notify
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
static INT32 _on_eb_county_notify(WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_GL_GET_FOCUS:
        {
        }
    default:
        break;
    }
    return WMPR_DONE;
}

/*----------------------------------------------------------------------------
 * Name: _frm_lct_code_proc_fct
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
static INT32 _frm_lct_code_proc_fct(HANDLE_T    h_widget,
                                    UINT32      ui4_msg,
                                    VOID*       param1,
                                    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;
            if (h_source == h_eb_code_st)
            {
                return _on_eb_state_notify(pt_nfy_data);
            }
            else if (h_source == h_eb_code_ct)
            {
                return _on_eb_county_notify(pt_nfy_data);
            }
            break;
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _widgets_proc_fct
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
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
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
                {
                    UINT16 ui2_input = ui4_keycode - BTN_DIGIT_0;
                    _eb_set_value(h_widget,ui2_input);
                    c_wgl_repaint(h_widget, NULL, TRUE);
                    return WMPR_DONE;
                }
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;
            default:
                break;
            }
        }
    case WGL_MSG_KEY_UP:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
            case BTN_SELECT:
                return WMPR_DONE;
            default:
                break;
            }
            break;
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32   i4_ret = 0;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _init_eb(h_cnt_frm,
                      0,    /* Index */
                      2,    /* Input Limit */
                      _widgets_proc_fct,
                      &h_eb_code_st);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _init_eb(h_cnt_frm,
                      1,    /* Index */
                      3,    /* Input Limit */
                      _widgets_proc_fct,
                      &h_eb_code_ct);
    MENU_CHK_FAIL(i4_ret);

    /**********/
    /* others */
    /**********/
    i4_ret = _chg_lang();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _set_nav();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id,
                                     _frm_lct_code_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    _eb_update_value(h_eb_code_st);
    _eb_update_value(h_eb_code_ct);

    menu_main_set_title(MLM_MENU_KEY_LOC_CODE);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    UTF16_T w2s_buf[APP_CFG_MAX_LCT_LEN];

    /* store state code */
    c_memset(w2s_buf, 0, sizeof(w2s_buf));
    c_uc_ps_to_w2s(as_digits[0], w2s_buf, APP_CFG_MAX_LCT_LEN);
    a_cfg_set_lct_code(APP_CFG_RECID_LCT_ST, w2s_buf);

    /* store county code */
    c_memset(w2s_buf, 0, sizeof(w2s_buf));
    c_uc_ps_to_w2s(as_digits[1], w2s_buf, APP_CFG_MAX_LCT_LEN);
    a_cfg_set_lct_code(APP_CFG_RECID_LCT_CT, w2s_buf);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32            ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    c_wgl_set_focus(h_eb_code_st, WGL_NO_AUTO_REPAINT);

    menu_common_help_show_back();

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    INT32 i4_ret;
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        i4_ret = _chg_lang();
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

extern INT32 menu_atsc_page_lct_code_init(VOID)
{
    t_g_menu_atsc_page_lct_code.pf_menu_page_create =    _on_page_create;
    t_g_menu_atsc_page_lct_code.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_atsc_page_lct_code.pf_menu_page_show=       _on_page_show;
    t_g_menu_atsc_page_lct_code.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_atsc_page_lct_code.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_atsc_page_lct_code.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_atsc_page_lct_code.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif /* ATSC_LCT_CODE_ENABLE */

