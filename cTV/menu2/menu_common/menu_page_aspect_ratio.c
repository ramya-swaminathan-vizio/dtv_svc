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
 * $RCSfile: menu_page_inp_lst.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
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
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_isl.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/tts/a_tts_custom.h"
#include "app_util/a_screen_mode.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define SCRM_MAX_NUM     (6)
typedef INT32 (*ope_lb2_proc_fct)(HANDLE_T            h_widget,
                                     UINT32              ui4_msg,
                                     VOID*               pv_param1,
                                     VOID*               pv_param2);
typedef struct {
    SCC_VID_SCREEN_MODE_T  e_screen_mode;
    UINT8                  ui1_index;
} MENU_SCRM_T;

MENU_PAGE_FCT_TBL_T     t_g_menu_page_aspect_ratio;
static HANDLE_T         h_aspect_ratio;
static MENU_SCRM_T      arr_scrm[SCRM_MAX_NUM];
static BOOL             b_from_backbar = FALSE;
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret=  MENUR_OK;
    return i4_ret;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _aspect_ratio_lb2_create(HANDLE_T h_parent, HANDLE_T *ph_wgt, VOID * pf_proc_fct)
{
    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    ope_lb2_proc_fct pf_lb2_proc_fct = NULL;

    pf_lb2_proc_fct = (ope_lb2_proc_fct)pf_proc_fct;
    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    i4_ret = menu_list2_create(h_parent,
                               &t_rect,
                               pf_lb2_proc_fct,
                               &t_lb_init,
                               NULL,
                               ph_wgt);
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (*ph_wgt,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(*ph_wgt,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static VSH_SRC_ASPECT_RATIO_T _get_src_asp_ratio(VOID)
{
    INT32 i4_ret;
    CHAR  s_disp_name[SYS_NAME_LEN + 1];
    VSH_SRC_RESOLUTION_INFO_T  t_timing = {0};
    VSH_SRC_ASPECT_RATIO_T     e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_av_get_timing(s_disp_name, &t_timing);
    MENU_LOG_ON_FAIL(i4_ret);

    e_src_asp_ratio = a_sml_get_src_asp_ratio(&t_timing);

    if(e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_UNKNOWN) {
        e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;
    }

    return e_src_asp_ratio;
}

static SCC_VID_SCREEN_MODE_T  _get_scr_mode(
        VSH_SRC_ASPECT_RATIO_T e_src_asp_ratio,
        SCC_VID_SCREEN_MODE_T* pe_screen_mode,
        SML_ITERATE_T e_dir)
{
    return a_sml_iterate_rec(e_src_asp_ratio,
                               e_dir,
                               pe_screen_mode);
}

static UINT16 _get_scr_mode_mlm_idx(SCC_VID_SCREEN_MODE_T e_screen_mode)
{
    UINT16  ui2_idx;

    switch (e_screen_mode)
    {
        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:    /* Zoom */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_ZOOM;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:    /* Wide */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_WIDE;
            break;

        case SCC_VID_SCREEN_MODE_NORMAL:          /* Normal */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_NORMAL;
            break;

        case SCC_VID_SCREEN_MODE_LETTERBOX:       /* Stretch */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_STRETCH;
            break;

        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM: /* Panoramic */
            ui2_idx = MLM_MENU_KEY_SCREEN_MODE_PANORAMIC;
            break;

        default:                                  /* unknown screen mode? */
            ui2_idx = MLM_MENU_KEY_EMPTY;
            break;
    }

    return ui2_idx;

}

static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    INT32 i4_ret;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
        menu_pm_repaint();
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
            case BTN_RETURN :
            case BTN_SELECT :
            {
                menu_nav_back();
                break;
            }
            case BTN_CURSOR_DOWN:
            {
                b_from_backbar = TRUE;
                i4_ret = c_wgl_set_focus(h_aspect_ratio, WGL_NO_AUTO_REPAINT);
                MENU_CHK_FAIL(i4_ret);
                break;
            }
            default :
                break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static VOID _aspect_ratio_move_help_tip(UINT8 ui1_row_num)
{
    INT32 i4_ret;
    GL_RECT_T t_rect;
    HANDLE_T  h_last_shadow_item;

    /* move help tip text */
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui1_row_num + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

}

static INT32 _aspect_ratio_lb2_proc_fct(HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32   i4_ret;
    UINT16  ui2_crnt_ht;
    INT16   i2_value = 0;
    BOOL    b_is_asp_key_press = FALSE;

    if(WGL_MSG_KEY_UP == ui4_msg)
    {
        if((UINT32)pv_param1 == BTN_ASPECT)
        {
            b_is_asp_key_press = TRUE;
            ui4_msg = WGL_MSG_KEY_DOWN;
            pv_param1 = BTN_CURSOR_DOWN;
        }
    }

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        if (b_from_backbar)
        {
            b_from_backbar = FALSE;

            i4_ret=c_wgl_do_cmd(h_aspect_ratio,
                                WGL_CMD_LB_HLT_ELEM,
                                WGL_PACK(0),
                                NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), &i2_value);
            MENU_CHK_FAIL(i4_ret);

            for (UINT8 ui1_idx=0; ui1_idx < SCRM_MAX_NUM; ++ui1_idx)
            {
                if (arr_scrm[ui1_idx].e_screen_mode == (SCC_VID_SCREEN_MODE_T)i2_value)
                {
                    i4_ret=c_wgl_do_cmd(h_aspect_ratio,
                                WGL_CMD_LB_HLT_ELEM,
                                WGL_PACK(ui1_idx),
                                NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
                   UTF16_T*  pt_w2s = NULL;
                   pt_w2s = MENU_TEXT(_get_scr_mode_mlm_idx(arr_scrm[ui1_idx].e_screen_mode));
                   a_app_tts_play(pt_w2s, c_uc_w2s_strlen(pt_w2s));
#endif
                    break;
                }
            }
        }

        menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ASPECT_RATIO_HELP_TEXT));
        menu_pm_repaint();
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
        i4_ret = c_wgl_do_cmd(h_aspect_ratio,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT:
            {
                i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),
                                     (INT16)(arr_scrm[ui2_crnt_ht].e_screen_mode));
                MENU_CHK_FAIL(i4_ret);

                i4_ret = a_cfg_update_screen_mode_ex();
                MENU_CHK_FAIL(i4_ret);
                // pass through
            }
            case BTN_RETURN:
                i4_ret = c_wgl_set_visibility(h_aspect_ratio, WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_nav_back();
                break;
            case BTN_CURSOR_UP:
                if (ui2_crnt_ht == 0)
                {
                    i4_ret = c_wgl_do_cmd(h_aspect_ratio,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_set_focus_on_backbar(FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
                break;
            case BTN_CURSOR_DOWN:
                break;
            default:
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP==ui4_msg)
    {
        UINT32  ui4_crnt_page;
        UTF16_T*  pt_w2s = NULL;

        i4_ret = menu_nav_get_crnt_page(&ui4_crnt_page);
        MENU_CHK_FAIL(i4_ret);

        if (ui4_crnt_page == ui4_g_menu_page_aspect_ratio)
        {
            i4_ret = c_wgl_do_cmd(h_aspect_ratio,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_w2s = MENU_TEXT(_get_scr_mode_mlm_idx(arr_scrm[ui2_crnt_ht].e_screen_mode));

            a_app_tts_play(pt_w2s, c_uc_w2s_strlen(pt_w2s));
        }
    }
#endif

    c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);

    if(b_is_asp_key_press)
    {
        i4_ret = c_wgl_do_cmd(h_aspect_ratio,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE),
                                     (INT16)(arr_scrm[ui2_crnt_ht].e_screen_mode));
        MENU_CHK_FAIL(i4_ret);

        i4_ret = a_cfg_update_screen_mode_ex();
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}


static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32  i4_ret;
    HANDLE_T  h_cnt_frm;
    VSH_SRC_ASPECT_RATIO_T  e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;
    SCC_VID_SCREEN_MODE_T   e_screen_mode;
    UINT8  ui1_num = 0;
    UINT8  ui1_idx = 0;

    /* set title */
    menu_main_set_title(MLM_MENU_KEY_MENU_ASPECT_RATIO);

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct);

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _aspect_ratio_lb2_create(h_cnt_frm, &h_aspect_ratio, _aspect_ratio_lb2_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    e_src_asp_ratio = _get_src_asp_ratio();
    if (VSH_SRC_ASPECT_RATIO_UNKNOWN == e_src_asp_ratio)
    {
        MENU_CHK_FAIL(-1);
    }

    i4_ret = a_sml_get_num_rec(e_src_asp_ratio, &ui1_num);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_aspect_ratio,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK(ui1_num),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    c_memset(arr_scrm, 0, sizeof(arr_scrm));

    i4_ret = _get_scr_mode(e_src_asp_ratio, &e_screen_mode, SML_ITERATE_DIR_FIRST);
    MENU_CHK_FAIL(i4_ret);

    do {
        i4_ret = c_wgl_do_cmd(h_aspect_ratio,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (ui1_idx, 0),
                          WGL_PACK(MENU_TEXT(_get_scr_mode_mlm_idx(e_screen_mode)))
                          );
        MENU_LOG_ON_FAIL(i4_ret);

        arr_scrm[ui1_idx].e_screen_mode = e_screen_mode;
        arr_scrm[ui1_idx].ui1_index     = ui1_idx;

        i4_ret = _get_scr_mode(e_src_asp_ratio, &e_screen_mode, SML_ITERATE_DIR_NEXT);
        MENU_LOG_ON_FAIL(i4_ret);
    } while(ui1_idx++ < ui1_num);

    c_wgl_set_visibility(h_aspect_ratio, WGL_SW_NORMAL);
    c_wgl_set_focus(h_aspect_ratio, WGL_NO_AUTO_REPAINT);

    _aspect_ratio_move_help_tip(ui1_num);
    menu_pm_repaint();

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32  i4_ret;

    i4_ret = c_wgl_set_visibility(h_aspect_ratio, WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_destroy_widget(h_aspect_ratio);
    MENU_LOG_ON_FAIL(i4_ret);

    h_aspect_ratio = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

INT32 menu_page_aspec_ratio_init(VOID)
{
    MENU_DEBUG_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][ASPECT]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    t_g_menu_page_aspect_ratio.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_aspect_ratio.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_aspect_ratio.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_aspect_ratio.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_aspect_ratio.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_aspect_ratio.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_aspect_ratio.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

