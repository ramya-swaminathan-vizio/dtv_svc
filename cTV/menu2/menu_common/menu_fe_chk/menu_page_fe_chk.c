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
 * $RCSfile: menu_page_fe_chk.c,v $
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
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_common/menu_fe_chk/menu_fe_chk_mlm.h"
#include "menu2/menu_dbg.h"

#ifdef COMMON_FE_CHK_ENABLE
/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#ifndef COMMON_FE_CHK_X
    /* size */
    #define COMMON_FE_CHK_X                   (0)
    #define COMMON_FE_CHK_Y                   (0)
    #define COMMON_FE_CHK_W                   (CONTENT_W)
    #define COMMON_FE_CHK_H                   (CONTENT_H)
    /* inset */
    #define COMMON_FE_CHK_CNT_INSET_L         (16)
    #define COMMON_FE_CHK_CNT_INSET_R         (16)
    /* column */
    #define COMMON_FE_CHK_NO_ID_W             (3 * GRID_W)
    #define COMMON_FE_CHK_NO_ID_ALIGN         (WGL_AS_CENTER_CENTER)
    #define COMMON_FE_CHK_LANG_W              (CONTENT_W - COMMON_FE_CHK_NO_ID_W)
    #define COMMON_FE_CHK_LANG_ALIGN          (WGL_AS_CENTER_CENTER)
    #define COMMON_FE_CHK_FONT_SIZE           (FE_FNT_SIZE_SMALL)
    /**/
    #define COMMON_FE_CHK_MAX_ELEM_NUM        (10)
    #define COMMON_FE_CHK_ELEM_NUM_PER_PAGE   (10)
    /**/
    #define COMMON_FE_CHK_COL_IDX_NO_ID       ( 0)
    #define COMMON_FE_CHK_COL_IDX_LANG        ( 1)
#endif    

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/* render commands */
#define MENU_FE_CHK_RENDER_RESET              ((UINT16)  0)
#define MENU_FE_CHK_RENDER_PREV_PAGE          ((UINT16)  1)
#define MENU_FE_CHK_RENDER_NEXT_PAGE          ((UINT16)  2)
#define MENU_FE_CHK_RENDER_PREV_LANG          ((UINT16)  3)
#define MENU_FE_CHK_RENDER_NEXT_LANG          ((UINT16)  4)

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_fe_chk;

static HANDLE_T     h_g_cnt_frm   = NULL_HANDLE;
static HANDLE_T     h_g_lb_fe_chk = NULL_HANDLE;
/**/
static UINT16       ui2_g_ttl_page       = 0;
static UINT16       ui2_g_crnt_page_idx  = 0;
static UINT16       ui2_g_crnt_lang_idx  = 0;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _lb_fe_chk_render
 * Description: The fe checking component show the multiple language texts.
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _lb_fe_chk_render(UINT16   ui2_render_cmd,
                               BOOL     b_repaint)
{
    INT32           i4_ret;
    UINT16          ui2_i;
    UINT16          ui2_lang_key;
    CHAR            s_no_id[5];
    UTF16_T         w2s_no_id[5];
    WGL_LB_ITEM_T   at_items[2];

    /* total page number */
    if ((MLM_MENU_FE_CHK_NUM_KEY % COMMON_FE_CHK_ELEM_NUM_PER_PAGE) == 0)
    {
        ui2_g_ttl_page = (MLM_MENU_FE_CHK_NUM_KEY / COMMON_FE_CHK_ELEM_NUM_PER_PAGE);
    }
    else
    {
        ui2_g_ttl_page = (MLM_MENU_FE_CHK_NUM_KEY / COMMON_FE_CHK_ELEM_NUM_PER_PAGE) + 1;
    }

    /**/
    switch (ui2_render_cmd)
    {
    case MENU_FE_CHK_RENDER_RESET:
        ui2_g_crnt_page_idx = 0;
        ui2_g_crnt_lang_idx = 0;
        break;
    case MENU_FE_CHK_RENDER_PREV_PAGE:
        if (ui2_g_crnt_page_idx == 0)
        {
            ui2_g_crnt_page_idx = ui2_g_ttl_page - 1;
        }
        else
        {
            ui2_g_crnt_page_idx--;
        }
        break;
    case MENU_FE_CHK_RENDER_NEXT_PAGE:
        if (ui2_g_crnt_page_idx >= (ui2_g_ttl_page - 1))
        {
            ui2_g_crnt_page_idx = 0;
        }
        else
        {
            ui2_g_crnt_page_idx++;
        }
        break;
    case MENU_FE_CHK_RENDER_PREV_LANG:
        if (ui2_g_crnt_lang_idx == 0)
        {
            ui2_g_crnt_lang_idx = MLM_MENU_FE_CHK_NUM_LANG - 1;
        }
        else
        {
            ui2_g_crnt_lang_idx--;
        }
        break;
    case MENU_FE_CHK_RENDER_NEXT_LANG:
        if (ui2_g_crnt_lang_idx >= (MLM_MENU_FE_CHK_NUM_LANG - 1))
        {
            ui2_g_crnt_lang_idx = 0;
        }
        else
        {
            ui2_g_crnt_lang_idx++;
        }
        break;
    default:
        break;
    }

    /* clear the list */
    i4_ret = c_wgl_do_cmd(h_g_lb_fe_chk, WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_CHK_FAIL(i4_ret);

    /* No ID , Multiple Language String */
    for (ui2_i = 0; ui2_i < COMMON_FE_CHK_ELEM_NUM_PER_PAGE; ui2_i++)
    {
        ui2_lang_key = (ui2_g_crnt_page_idx * COMMON_FE_CHK_ELEM_NUM_PER_PAGE) + ui2_i;
        if (ui2_lang_key >= MLM_MENU_FE_CHK_NUM_KEY)
        {
            break;
        }

        /* No ID */
        c_memset(s_no_id, 0, sizeof(s_no_id));
        c_memset(w2s_no_id, 0, sizeof(w2s_no_id));

        c_sprintf(s_no_id, "%d", ui2_lang_key); 
        c_uc_ps_to_w2s(s_no_id, w2s_no_id, 5);

        /**/
        at_items[0].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[0].data.pw2s_text  = w2s_no_id;
        at_items[1].e_col_type      = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text  = MLM_MENU_FE_CHK_TEXT(ui2_g_crnt_lang_idx, ui2_lang_key);
        i4_ret = c_wgl_do_cmd(h_g_lb_fe_chk, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
        MENU_CHK_FAIL(i4_ret);
    }

    /**/
    if (b_repaint)
    {
        c_wgl_repaint (h_g_lb_fe_chk, NULL, TRUE);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lb_fe_chk_create
 * Description: The fe checking component show the multiple language texts.
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _lb_fe_chk_create(HANDLE_T    h_parent,
                               HANDLE_T*   ph_widget)
{
    INT32                       i4_ret; 
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[2];
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;

    /* Column info */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = COMMON_FE_CHK_NO_ID_ALIGN;
    at_cols[0].ui2_width        = COMMON_FE_CHK_NO_ID_W; 
    at_cols[0].ui2_max_text_len = 3; /* 1 - 999 */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = COMMON_FE_CHK_LANG_ALIGN;
    at_cols[1].ui2_width        = (UINT16)(COMMON_FE_CHK_LANG_W - COMMON_FE_CHK_CNT_INSET_L - COMMON_FE_CHK_CNT_INSET_R); 
    at_cols[1].ui2_max_text_len = 32;

    /* listbox init struct */
    t_lb_init.ui4_style         = 0;
    t_lb_init.ui2_max_elem_num  = COMMON_FE_CHK_MAX_ELEM_NUM;
    t_lb_init.ui2_elem_size     = GRID_H;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 2;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect, 
                     COMMON_FE_CHK_X, 
                     COMMON_FE_CHK_Y, 
                     COMMON_FE_CHK_W, 
                     COMMON_FE_CHK_H);

    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_LIST_BOX,
                                  WGL_CONTENT_LIST_BOX_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  NULL,
                                  255,
                                  & t_lb_init,
                                  NULL,
                                  ph_widget);
    if (i4_ret < WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = COMMON_FE_CHK_FONT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(1),
                           WGL_PACK(&t_fnt_info));
    MENU_CHK_FAIL(i4_ret);

    /* Set Inset */
    t_inset.i4_left     = COMMON_FE_CHK_CNT_INSET_L;
    t_inset.i4_right    = COMMON_FE_CHK_CNT_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          (VOID*)0,
                          &t_inset);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          (VOID*)1,
                          &t_inset);
    MENU_CHK_FAIL(i4_ret);

    /* Set Color */
    t_lb_color.t_normal             = t_g_menu_color_bk1_txt;
    t_lb_color.t_disable            = t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_highlight          = t_g_menu_color_bk1_txt_hlt;
    t_lb_color.t_highlight_unfocus  = t_g_menu_color_bk1_txt;
    t_lb_color.t_pushed             = t_g_menu_color_bk1_txt;
    t_lb_color.t_selected           = t_g_menu_color_bk1_txt;
    t_lb_color.t_selected_disable   = t_g_menu_color_bk1_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(1, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_CHK_FAIL(i4_ret);

    t_lb_color.t_normal             = t_g_menu_color_transp;
    t_lb_color.t_disable            = t_g_menu_color_transp;
    t_lb_color.t_highlight          = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus  = t_g_menu_color_transp;
    t_lb_color.t_pushed             = t_g_menu_color_transp;
    t_lb_color.t_selected           = t_g_menu_color_transp;
    t_lb_color.t_selected_disable   = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(1, WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
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
        case BTN_CURSOR_LEFT:
            _lb_fe_chk_render(MENU_FE_CHK_RENDER_PREV_LANG, TRUE);
            break;
        case BTN_CURSOR_RIGHT:
            _lb_fe_chk_render(MENU_FE_CHK_RENDER_NEXT_LANG, TRUE);
            break;
        case BTN_CURSOR_UP:
            _lb_fe_chk_render(MENU_FE_CHK_RENDER_PREV_PAGE, TRUE);
            break;
        case BTN_CURSOR_DOWN:
            _lb_fe_chk_render(MENU_FE_CHK_RENDER_NEXT_PAGE, TRUE);
            break;
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
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_g_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _lb_fe_chk_create(h_g_cnt_frm, &h_g_lb_fe_chk);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id, _widgets_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(h_g_cnt_frm, WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(h_g_cnt_frm, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    /**/
    _lb_fe_chk_render(MENU_FE_CHK_RENDER_RESET, FALSE);

    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_FE_CHK);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    c_wgl_set_focus(h_g_cnt_frm, WGL_NO_AUTO_REPAINT);

    menu_common_help_show_back();

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

extern INT32 menu_common_page_fe_chk_init(VOID)
{
    t_g_menu_common_page_fe_chk.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_fe_chk.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_fe_chk.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_fe_chk.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_fe_chk.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_fe_chk.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_fe_chk.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_FE_CHK_ENABLE */

