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
 * $RCSfile: menu_page_vchip_ca_fr.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *      This file implements the Canadian VChip french ratings.
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

#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_atsc/menu_atsc.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "menu2/menu_dbg.h"

#ifdef ATSC_VCHIP_CA_FR_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define _RATING_NUM_    5

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_vchip_ca_fr;

static  HANDLE_T    h_cnt_frm;
static  HANDLE_T    h_lb_rating;
static  HANDLE_T    h_lb_indicator;
static  BOOL        b_created = FALSE;
static  UTF16_T*    aw2s_rating_str[_RATING_NUM_] =
{
    _TEXT("G"),
    _TEXT("8 ans+"),
    _TEXT("13 ans+"),
    _TEXT("16 ans+"),
    _TEXT("18 ans+")
};

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _widgets_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            /* set highlight of quick_operation & focus on it */
            c_wgl_do_cmd(h_lb_rating,
                         WGL_CMD_LB_HLT_ELEM ,
                         WGL_PACK(0) ,
                         NULL);
            c_wgl_set_focus(h_lb_rating, WGL_SYNC_AUTO_REPAINT);

            menu_hide_help_tip();
            break;

        case BTN_CURSOR_UP:
            menu_set_focus_on_homebar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_SELECT:
            menu_nav_go_home_menu();
            return WGLR_OK;

        case BTN_CURSOR_UP :
            /* set highlight of quick_operation & focus on it */
/*
            c_wgl_do_cmd(h_lb_rating,
                         WGL_CMD_LB_HLT_ELEM,
                         WGL_PACK((_RATING_NUM_-1)),
                         NULL);
            c_wgl_set_focus(h_lb_rating, WGL_SYNC_AUTO_REPAINT);

            menu_hide_help_tip();
*/
            break;

        case BTN_CURSOR_DOWN:
            menu_set_focus_on_backbar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break ;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _page_create
 *
 * Description:
 *      Create the U.S. movie rating page.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _page_create(VOID)
{
    INT32       i4_ret;
    UINT32      ui4_i;
    WGL_LB_ITEM_T               at_items[2];
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit;

    i4_ret = menu_atsc_rating_lst_create(h_cnt_frm,
                                         _RATING_NUM_,
                                         _widgets_proc_fct,
                                         &h_lb_rating);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_atsc_rating_indicator_create(h_cnt_frm,
                                               7,
                                               &h_lb_indicator);
    MENU_CHK_FAIL(i4_ret);

    for(ui4_i = 0; ui4_i < _RATING_NUM_; ui4_i++)
    {
        c_memset(&t_img_suit, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
        t_img_suit.h_normal                     = h_g_unlock_white_v2;
        t_img_suit.h_disable                    = NULL_HANDLE;
        t_img_suit.h_highlight                  = h_g_unlock_white_hlt_v2;
        t_img_suit.h_highlight_unfocus          = h_g_unlock_white_v2;
        t_img_suit.h_pushed                     = NULL_HANDLE;
        t_img_suit.h_selected                   = h_g_lock_white_v2;
        t_img_suit.h_selected_disable           = NULL_HANDLE;
        t_img_suit.h_selected_highlight         = h_g_lock_white_hlt_v2;
        t_img_suit.h_selected_highlight_unfocus = h_g_lock_white_v2;
        t_img_suit.h_selected_pushed            = NULL_HANDLE;

        at_items[0].e_col_type          = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text      = aw2s_rating_str[ui4_i];
        at_items[1].e_col_type          = LB_COL_TYPE_IMG_SUIT;
        at_items[1].data.pt_img_suit    = &t_img_suit;

        i4_ret = c_wgl_do_cmd(h_lb_rating,
                              WGL_CMD_LB_APPEND_ELEM,
                              WGL_PACK(at_items),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(h_lb_rating,
                                  WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_indicator,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_refresh
 *
 * Description:
 *      Refresh the state of each element according to current vchip settings
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_refresh(VOID)
{
    INT32   i4_ret;
    UINT8   ui1_en_rating;
    UINT8   ui1_fr_rating;
    UINT16  ui2_i;

    i4_ret = a_cfg_get_vchip_ca(&ui1_en_rating,
                                &ui1_fr_rating);
    if(i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }

    for(ui2_i = 0; ui2_i<_RATING_NUM_; ui2_i++)
    {
        if(ui2_i+1 < ui1_fr_rating)
        {
            /* unlock */
            c_wgl_do_cmd(h_lb_rating,
                         WGL_CMD_LB_DESEL_ELEM,
                         WGL_PACK((UINT16)ui2_i),
                         NULL);
        }
        else
        {
            /* lock */
            c_wgl_do_cmd(h_lb_rating,
                         WGL_CMD_LB_SEL_ELEM,
                         WGL_PACK((UINT16)ui2_i),
                         NULL);
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _sel_index
 *
 * Description:
 *      Select/Unselect the given index.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _sel_index(UINT16 ui2_idx)
{
    INT32   i4_ret;
    UINT8   ui1_en_rating = 0;
    UINT8   ui1_fr_rating = 0;

    a_cfg_lock();

    a_cfg_get_vchip_ca(&ui1_en_rating,
                       &ui1_fr_rating);

    if(ui2_idx+1 < ui1_fr_rating)
    {
        /* unlock -> lock */
        ui1_fr_rating = (UINT8)(ui2_idx + 1);
    }
    else
    {
        /* lock -> unlock */
        ui1_fr_rating = (UINT8)(ui2_idx + 2);
    }

    a_cfg_set_vchip_ca(ui1_en_rating,
                       ui1_fr_rating);

    a_cfg_unlock();

    i4_ret = _page_refresh();
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
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
static INT32 _widgets_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    UINT32  ui4_keycode = 0;
    UINT16  ui2_idx = 0;

#ifdef APP_TTS_SUPPORT
    BOOL    b_is_sel = 0;
    UTF16_T w2s_tts_content[32] = {0};
#endif

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        c_wgl_do_cmd(h_lb_rating,
                     WGL_CMD_LB_GET_HLT_INDEX,
                     WGL_PACK(&ui2_idx),
                     NULL);

#ifdef APP_TTS_SUPPORT
                    c_wgl_do_cmd(h_lb_rating,
                                 WGL_CMD_LB_IS_INDEX_SEL,
                                 WGL_PACK(ui2_idx),
                                 WGL_PACK(&b_is_sel) );
                    c_uc_w2s_strcpy(w2s_tts_content, aw2s_rating_str[ui2_idx]);
                    c_uc_w2s_strcat(w2s_tts_content, (b_is_sel) ? L" Locked" : L" Unlocked");
                    a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
#endif

        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_RATE_FRE_G+ui2_idx));
        break;
    }

    case WGL_MSG_KEY_DOWN:
    {
        ui4_keycode = (UINT32)pv_param1;
        switch (ui4_keycode)
        {
        case BTN_SELECT:
            c_wgl_do_cmd(h_lb_rating,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);

            _sel_index(ui2_idx);

#ifdef APP_TTS_SUPPORT
                                c_wgl_do_cmd(h_lb_rating,
                                             WGL_CMD_LB_IS_INDEX_SEL,
                                             WGL_PACK(ui2_idx),
                                             WGL_PACK(&b_is_sel) );
                                c_memset(w2s_tts_content, 0, sizeof(w2s_tts_content));
                                c_uc_w2s_strcpy(w2s_tts_content, (b_is_sel) ? L"Locked" : L"Unlocked");
                                a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
#endif

            c_wgl_repaint(h_lb_rating, NULL, TRUE);
            return WMPR_DONE;

        case BTN_CURSOR_UP:
            c_wgl_do_cmd(h_lb_rating,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);
            /* first item */
            if (ui2_idx == 0)
            {
                menu_set_focus_on_backbar(TRUE);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            }
            else
            {
#ifdef APP_TTS_SUPPORT
                                        c_wgl_do_cmd(h_lb_rating,
                                                     WGL_CMD_LB_IS_INDEX_SEL,
                                                     WGL_PACK(ui2_idx - 1),
                                                     WGL_PACK(&b_is_sel) );
                                        c_memset(w2s_tts_content, 0, sizeof(w2s_tts_content));

                                        c_uc_w2s_strcpy(w2s_tts_content, aw2s_rating_str[ui2_idx - 1]);
                                        c_uc_w2s_strcat(w2s_tts_content, (b_is_sel) ? L" locked" : L" unlocked");
                                        a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
#endif

                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_RATE_FRE_G+ui2_idx-1));
            }
            break;

        case BTN_CURSOR_DOWN:
            c_wgl_do_cmd(h_lb_rating,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         NULL);
            /* last item */
            if (ui2_idx == (_RATING_NUM_ - 1))
            {
                menu_help_tip_keytip_set_focus(h_lb_rating,3,FALSE);
                menu_pm_repaint();
            }
            else
            {
#ifdef APP_TTS_SUPPORT
                                        c_wgl_do_cmd(h_lb_rating,
                                                     WGL_CMD_LB_IS_INDEX_SEL,
                                                     WGL_PACK(ui2_idx + 1),
                                                     WGL_PACK(&b_is_sel) );
                                        c_memset(w2s_tts_content, 0, sizeof(w2s_tts_content));

                                        c_uc_w2s_strcpy(w2s_tts_content, aw2s_rating_str[ui2_idx + 1]);
                                        c_uc_w2s_strcat(w2s_tts_content, (b_is_sel) ? L" locked" : L" unlocked");
                                        a_app_tts_play(w2s_tts_content, c_uc_w2s_strlen(w2s_tts_content));
#endif

                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_RATE_FRE_G+ui2_idx+1));
            }
            break;

        case BTN_CURSOR_LEFT:
            #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return MENUR_OK;
            #endif
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WMPR_DONE;

        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32       i4_ret;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    if(b_g_menu_lazy_init_support)
    {
        b_created = FALSE;
    }
    else
    {
        _page_create();
        b_created = TRUE;
    }

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    if(!b_created)
    {
        /* lazy creation */
        _page_create();
        b_created = TRUE;
    }

    _page_refresh();

    menu_main_set_title(MLM_MENU_KEY_VCHIP_CA_FR);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    /* use help tip instead of menu's help list */
    #if 0
    MENU_HELP_LST_BUCKET_T at_help_lst[] =
    {
        {h_g_menu_img_btn_enter,    MLM_MENU_KEY_HELP_SET},
        {h_g_menu_img_btn_select,   MLM_MENU_KEY_HELP_SELECT},
        {h_g_menu_img_btn_exit,     MLM_MENU_KEY_HELP_BACK}
    };

    menu_main_set_help(at_help_lst,
                       (UINT16)(sizeof(at_help_lst)/ sizeof(at_help_lst[0])));
    #endif

    MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_lb_indicator, WGL_SW_NORMAL));

    c_wgl_set_focus(h_lb_rating, WGL_NO_AUTO_REPAINT);

    c_wgl_do_cmd(h_lb_rating,
                 WGL_CMD_LB_HLT_ELEM,
                 WGL_PACK(0),
                 NULL);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_RATE_FRE_G));

    menu_set_backbar_proc(_backbar_proc_fct);

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    menu_set_backbar_proc(NULL);

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        menu_atsc_rating_indicator_chg_lang(h_lb_indicator);
    }

    return MENUR_OK;
}

extern INT32 menu_atsc_page_vchip_ca_fr_init(VOID)
{
    t_g_menu_atsc_page_vchip_ca_fr.pf_menu_page_create      = _on_page_create;
    t_g_menu_atsc_page_vchip_ca_fr.pf_menu_page_destroy     = _on_page_destroy;
    t_g_menu_atsc_page_vchip_ca_fr.pf_menu_page_show        = _on_page_show;
    t_g_menu_atsc_page_vchip_ca_fr.pf_menu_page_hide        = _on_page_hide;
    t_g_menu_atsc_page_vchip_ca_fr.pf_menu_page_get_focus   = _on_page_get_focus;
    t_g_menu_atsc_page_vchip_ca_fr.pf_menu_page_lose_focus  = _on_page_lose_focus;
    t_g_menu_atsc_page_vchip_ca_fr.pf_menu_page_update      = _on_page_update;

    return MENUR_OK;
}

#endif /* ATSC_VCHIP_CA_FR_ENABLE */

