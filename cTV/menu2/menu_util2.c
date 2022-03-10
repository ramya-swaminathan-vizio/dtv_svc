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
 * $RCSfile: menu_util2.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/23 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 47aa641dbb1c0b2b64f3264199a32d61 $
 *
 * Description:
 *      This file contains the implementation of GUI-related functions of the
 * menu application
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                  include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_bdr_uniform.h"
#include "u_wgl_bdr_timg.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_wgl_sets.h"
#include "c_gl.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_rect.h"
#include "c_fe.h"

#include "app_util/a_common.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_page_tree.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_dbg.h"
#include "app_util/toast_widget/a_toast.h"
#include "c_iom.h"

#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

/*-----------------------------------------------------------------------------
                          Customizable macros
 ----------------------------------------------------------------------------*/
/*

  | +-------------------------------------------------------------+ |
  |1|2|3,icon |     4,title        |        5,value      |6,hint|7|8|
  | +-------------------------------------------------------------+ |

  1 = MENU_ITEM_BAR_INSET_L
  2 = MENU_ITEM_BAR_CNT_INSET_L
  3 = MENU_ITEM_ICON_W
  4 = MENU_ITEM_TITLE_W
  5 = MENU_ITEM_VALUE_W
  6 = MENU_ITEM_HINT_W
  7 = MENU_ITEM_BAR_CNT_INSET_R
  8 = MENU_ITEM_BAR_INSET_R
*/

#ifndef MENU_ITEM_V_WIDE
    #define MENU_ITEM_V_LEFT            (0)
    #define MENU_ITEM_V_WIDE            (295)
    #define MENU_ITEM_V_HEIGHT          (33)

    #define MENU_ITEM_V_CNT_INSET_L     (8)
    #define MENU_ITEM_V_CNT_INSET_R     (7)

    #define MENU_ITEM_V_TITLE_W         (145)
    #define MENU_ITEM_V_VALUE_W         (135)
    #define MENU_ITEM_V_VALUE_W_CH_SCAN (200) //channel scan status width modify

    #define MENU_ITEM_V_RANGE_TITLE_W   (135)
    #define MENU_ITEM_V_INDICATOR_X     (246)
    #define MENU_ITEM_V_INDICATOR_W     (36)

    #define MENU_ITEM_V_LB_ARROW_W      (11)
    #define MENU_ITEM_V_LB_INSET_L      (13)
    #define MENU_ITEM_V_LB_INSET_R      (0)

#endif

#ifndef MENU_ITEM_TEXT_ALIGN
    #define MENU_ITEM_TEXT_ALIGN        (WGL_AS_LEFT_CENTER)
#endif

#define MENU_AUDIO_MODE_LB_L      (0)
#define MENU_AUDIO_MODE_LB_T      (0)
#define MENU_AUDIO_MODE_LB_R      (630)
#define MENU_AUDIO_MODE_LB_B      (114)


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static UTF16_T     w2s_g_empty[] = {0};
static WGL_INSET_T t_inset_border = {
    MENU_ITEM_V_CNT_INSET_L + MENU_ITEM_V_TITLE_W,
    0,
    0,
    0};
static GL_RECT_T   t_rect_border_title = {
    65,
    0,
    MENU_ITEM_V_TITLE_W,
    MENU_ITEM_V_HEIGHT};
static GL_RECT_T   t_rect_border_title_more = {
    8,
    6,
    MENU_ITEM_V_WIDE - 8 - MENU_ITEM_V_CNT_INSET_R - MENU_MORE_ITEM_RIGHT_ARROW,
    MENU_ITEM_V_HEIGHT};

static HANDLE_T    h_arrow_up = NULL_HANDLE;
static HANDLE_T    h_arrow_down = NULL_HANDLE;
static HANDLE_T    _h_g_slider;
static HANDLE_T    h_timer = NULL_HANDLE;
static UINT32      ui4_timer_delay = 5000; //5s

static BOOL b_g_toast_range = FALSE;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static VOID do_menu_util_hide_notify(VOID* pv_data,
                                    SIZE_T  z_data_size)
{
    INT32 i4_ret;

    i4_ret = c_timer_stop(h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    if(menu_get_toast_range_flag() == TRUE)
    {
        i4_ret = c_iom_send_evt(BTN_RETURN,100);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}
static VOID menu_range_timer_nfy_fct(HANDLE_T  pt_tm_handle,
                                        VOID*     pv_tag)
{
    INT32 i4_ret = -1;
    i4_ret = menu_async_invoke(do_menu_util_hide_notify,NULL,0,FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
}


/*----------------------------------------------------------------------------
 * Name: menu_list_arrow_show_up
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
INT32 menu_list_up_arrow_show(BOOL b_show, BOOL b_repaint)
{
    c_wgl_float(h_arrow_up, TRUE, FALSE);
    c_wgl_set_visibility(h_arrow_up, b_show == TRUE ? WGL_SW_NORMAL : WGL_SW_HIDE);
    if (b_repaint)
    {
        c_wgl_repaint(h_arrow_up, NULL, FALSE);
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_arrow_show_down
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
INT32 menu_list_down_arrow_show(BOOL b_show, BOOL b_repaint)
{
    BOOL b_showing;
    c_wgl_get_visibility(h_arrow_down, &b_showing);
    if (b_show == b_showing)
    {
        return MENUR_OK;
    }
    c_wgl_float(h_arrow_down, TRUE, FALSE);
    c_wgl_set_visibility(h_arrow_down, b_show == TRUE ? WGL_SW_NORMAL : WGL_SW_HIDE);

    if (b_repaint)
    {
        c_wgl_repaint(h_arrow_down, NULL, FALSE);
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_arrow_hide
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
INT32 menu_list_arrow_hide(BOOL b_repaint)
{
    c_wgl_float(h_arrow_up, FALSE, FALSE);
    c_wgl_float(h_arrow_down, FALSE, FALSE);
    c_wgl_set_visibility(h_arrow_up, WGL_SW_HIDE);
    c_wgl_set_visibility(h_arrow_down, WGL_SW_HIDE);

    if (b_repaint)
    {
        c_wgl_repaint(h_arrow_up, NULL, FALSE);
        c_wgl_repaint(h_arrow_down, NULL, FALSE);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_arrow_move
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
INT32 menu_list_arrow_move(GL_RECT_T *pt_list_rect, BOOL b_repaint)
{
    GL_RECT_T t_rect = {0};

    if (pt_list_rect != NULL)
    {
        t_rect.i4_left= pt_list_rect->i4_left;
        t_rect.i4_top = pt_list_rect->i4_top;
        t_rect.i4_right= pt_list_rect->i4_right;
        t_rect.i4_bottom = pt_list_rect->i4_top + 12;

        c_wgl_move(h_arrow_up, &t_rect, (b_repaint ? WGL_ASYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT));

        t_rect.i4_left= pt_list_rect->i4_left;
        t_rect.i4_top = pt_list_rect->i4_bottom + 12 + 2;
        t_rect.i4_right= pt_list_rect->i4_right;
        t_rect.i4_bottom = t_rect.i4_top + 12;
        c_wgl_move(h_arrow_down, &t_rect, (b_repaint ? WGL_ASYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT));
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_arrow_state_update
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
INT32 menu_list_arrow_state_update(HANDLE_T h_list, UINT32 ui4_keycode, BOOL b_repaint)
{
    INT32   i4_ret = 0;
    UINT32  ui4_elem_num = 0;
    UINT32  ui4_hlt_idx = 0;
    INT32   i4_first_visible = 0;
    INT32   i4_last_visible = 0;
    WGL_SW_CMD_T  e_wgl_cmd_up = WGL_SW_HIDE;
    WGL_SW_CMD_T  e_wgl_cmd_down = WGL_SW_HIDE;

    if (BTN_CURSOR_UP != ui4_keycode
        && BTN_CURSOR_DOWN != ui4_keycode
        && BTN_INVALID != ui4_keycode)
    {
        return MENUR_OK;
    }

    i4_ret = c_wgl_do_cmd(h_list,
                            WGL_CMD_LB_GET_ELEM_NUM,
                            WGL_PACK(&ui4_elem_num),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui4_elem_num <= 10)
    {
        c_wgl_set_visibility(h_arrow_up, WGL_SW_HIDE);
        c_wgl_set_visibility(h_arrow_down, WGL_SW_HIDE);
        return MENUR_OK;
    }

    i4_ret = c_wgl_do_cmd(h_list,
                            WGL_CMD_LB_GET_HLT_INDEX,
                            WGL_PACK(&ui4_hlt_idx),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_list,
                            WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                            WGL_PACK(&i4_first_visible),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_list,
                            WGL_CMD_LB_GET_LAST_VISIBLE_INDEX,
                            WGL_PACK(&i4_last_visible),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (BTN_CURSOR_UP == ui4_keycode)
    {
        if (ui4_hlt_idx == i4_first_visible)
        {
            i4_last_visible = i4_first_visible > 0 ? i4_last_visible - 1 : i4_last_visible;
            i4_first_visible = i4_first_visible > 0 ? i4_first_visible - 1 : 0;
        }
    }
    if (BTN_CURSOR_DOWN == ui4_keycode)
    {
        if (ui4_hlt_idx == i4_last_visible)
        {
            i4_first_visible = i4_last_visible >= ui4_elem_num-1 ? i4_first_visible : i4_first_visible + 1;
            i4_last_visible = i4_last_visible >= ui4_elem_num-1 ? i4_last_visible : i4_last_visible + 1;
        }
    }

    e_wgl_cmd_up = (i4_first_visible > 0) ? WGL_SW_NORMAL : WGL_SW_HIDE;
    e_wgl_cmd_down = (i4_last_visible < ui4_elem_num - 1) ? WGL_SW_NORMAL : WGL_SW_HIDE;

    i4_ret = c_wgl_float(h_arrow_up, TRUE, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_float(h_arrow_down, TRUE, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_visibility(h_arrow_up, e_wgl_cmd_up);
    c_wgl_set_visibility(h_arrow_down, e_wgl_cmd_down);

    if (b_repaint)
    {
        c_wgl_repaint(h_arrow_up, NULL, FALSE);
        c_wgl_repaint(h_arrow_down, NULL, FALSE);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_arrow_create
 *
 * Description:
 *
 * Inputs:  h_parent
 *          pt_rect is listbox rect
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_list_arrow_create(HANDLE_T h_parent, GL_RECT_T *pt_rect)
{
    INT32               i4_ret = MENUR_OK;
    GL_RECT_T           t_rect = {0};
    WGL_IMG_INFO_T      t_img_info = {0};

    /* pt_rect is the listbox rect */
    if (NULL_HANDLE == h_arrow_up)
    {
        /* arrow up */
        t_rect.i4_left= pt_rect->i4_left;
        t_rect.i4_top = pt_rect->i4_top;
        t_rect.i4_right= pt_rect->i4_right;
        t_rect.i4_bottom = pt_rect->i4_top + 12;

        i4_ret = c_wgl_create_widget(h_parent,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_GL_NO_BK),
                                     NULL,
                                     &h_arrow_up);

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_arrow_up;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_arrow_up;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_arrow_up;
        i4_ret = c_wgl_do_cmd(h_arrow_up,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_FG),
                              WGL_PACK(&t_img_info));

        i4_ret = c_wgl_do_cmd(h_arrow_up,
                            WGL_CMD_ICON_SET_ALIGN,
                            WGL_PACK(WGL_AS_CENTER_CENTER),
                            NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(h_arrow_up, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_float(h_arrow_up, TRUE, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if (NULL_HANDLE == h_arrow_down)
    {
        /* arrow down */
        t_rect.i4_left= pt_rect->i4_left;
        t_rect.i4_top = pt_rect->i4_bottom + 12 + 2;
        t_rect.i4_right= pt_rect->i4_right;
        t_rect.i4_bottom = t_rect.i4_top + 12;

        i4_ret = c_wgl_create_widget(h_parent,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_GL_NO_BK),
                                     NULL,
                                     &h_arrow_down);

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_arrow_down;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_arrow_down;
        t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_arrow_down;
        i4_ret = c_wgl_do_cmd(h_arrow_down,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_FG),
                              WGL_PACK(&t_img_info));

        if (i4_ret < 0)
        {
            return MENUR_CANT_CREATE_WIDGET;
        }

         i4_ret = c_wgl_do_cmd(h_arrow_down,
                            WGL_CMD_ICON_SET_ALIGN,
                            WGL_PACK(WGL_AS_CENTER_CENTER),
                            NULL);
        MENU_LOG_ON_FAIL(i4_ret);



        i4_ret = c_wgl_set_visibility(h_arrow_down, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);


        i4_ret = c_wgl_float(h_arrow_down, TRUE, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}
INT32 menu_help_tip_last_shadow_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_LB_ITEM_T               at_items[1];
    //WGL_LB_COLOR_ELEM_SET_T     t_lb_color;


    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = MENU_ITEM_V_VALUE_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     (MENU_ITEM_V_WIDE - 4),
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 3;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_g_empty;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set  images */
    WGL_IMG_INFO_T  t_img_info;
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_lastshadow_new;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_lastshadow_new;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_lastshadow_new;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

INT32 menu_audio_eq_list_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    UINT16      ui2_max_elem_num,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[3];
    WGL_LB_ITEM_T               at_items[3];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_left;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_right;
    UINT16                      ui2_i;
    WGL_IMG_INFO_T              t_img_info;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_width        = MENU_ITEM_V_LB_ARROW_W;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = (MENU_ITEM_V_VALUE_W - MENU_ITEM_V_LB_ARROW_W*2 - MENU_ITEM_V_LB_INSET_L);

    at_cols[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[2].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[2].ui2_width        = MENU_ITEM_V_LB_ARROW_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = ui2_max_elem_num;
    t_lb_init.ui2_elem_size     = 114;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 3;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_AUDIO_MODE_LB_L,
                     MENU_AUDIO_MODE_LB_T * i4_index,
                     MENU_AUDIO_MODE_LB_R,
                     MENU_AUDIO_MODE_LB_B);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

     /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* element inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* column inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    for (ui2_i=0; ui2_i<3; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK(ui2_i),
                              WGL_PACK(&t_inset));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = 24;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(1),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_white;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(1, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui2_i=0; ui2_i<3; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui2_i, WGL_CLR_BK),
                              WGL_PACK(&t_lb_color) );
        MENU_LOG_ON_FAIL(i4_ret);
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_left.h_highlight          = h_g_menu_img_list_item_leftarrow;
    t_img_suit_left.h_selected_highlight = h_g_menu_img_list_item_leftarrow;

    c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_right.h_highlight          = h_g_menu_img_list_item_rightarrow;
    t_img_suit_right.h_selected_highlight = h_g_menu_img_list_item_rightarrow;

    for (ui2_i=0; ui2_i<ui2_max_elem_num; ui2_i++)
    {
        at_items[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[0].data.pt_img_suit = &t_img_suit_left;

        at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text   = w2s_g_empty;

        at_items[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[2].data.pt_img_suit = &t_img_suit_right;

        i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_common_audio_mode_v2;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_chg_lang
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
INT32 menu_list_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    UINT16      ui2_max_elem_num,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[3];
    WGL_LB_ITEM_T               at_items[3];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_left;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_right;
    UINT16                      ui2_i;
    WGL_IMG_INFO_T              t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /*=======================================*
     | Title                |   | option |   |      ---   normal
     | Title                | < | option | > |      ---   highlight
     *=======================================*/

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[0].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[0].ui2_width        = MENU_ITEM_V_LB_ARROW_W;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = (MENU_ITEM_V_VALUE_W - MENU_ITEM_V_LB_ARROW_W*2 - MENU_ITEM_V_LB_INSET_L);

    at_cols[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[2].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[2].ui2_width        = MENU_ITEM_V_LB_ARROW_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = ui2_max_elem_num;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 3;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = MENU_ITEM_V_LB_INSET_L;
    t_inset.i4_right    = MENU_ITEM_V_LB_INSET_R;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* element inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* column inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    for (ui2_i=0; ui2_i<3; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK(ui2_i),
                              WGL_PACK(&t_inset));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(1),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;/*t_g_menu_color_white;*/
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(1, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui2_i=0; ui2_i<3; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui2_i, WGL_CLR_BK),
                              WGL_PACK(&t_lb_color) );
        MENU_LOG_ON_FAIL(i4_ret);
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_left.h_highlight          = h_g_menu_img_list_item_leftarrow;
    t_img_suit_left.h_selected_highlight = h_g_menu_img_list_item_leftarrow;

    c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit_right.h_highlight          = h_g_menu_img_list_item_rightarrow;
    t_img_suit_right.h_selected_highlight = h_g_menu_img_list_item_rightarrow;

    for (ui2_i=0; ui2_i<ui2_max_elem_num; ui2_i++)
    {
        at_items[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[0].data.pt_img_suit = &t_img_suit_left;

        at_items[1].e_col_type       = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text   = w2s_g_empty;

        at_items[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
        at_items[2].data.pt_img_suit = &t_img_suit_right;

        i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk2_txt_disable;/*t_g_menu_color_white;*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    UINT32 ui4_text_style = 0;
	ui4_text_style |= WGL_STL_BDR_TIMG_NO_SMART_CUT;
    c_wgl_do_cmd(*ph_widget,
                  WGL_CMD_BDR_TIMG_SET_STYLE,
                  WGL_PACK(ui4_text_style),
                  WGL_PACK(NULL));

    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_chg_lang
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
INT32 menu_list_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title,
    UINT16      ui2_msgid_elem_first,
    UINT16      ui2_msgid_elem_last)
{
    INT32   i4_ret;
    UINT16  ui2_i;

    if (ui2_msgid_elem_first == MLM_MENU_KEY_ON ||
        ui2_msgid_elem_first == MLM_MENU_KEY_OFF)
    {
        WGL_INSET_T     t_inset;
        UINT16          ui2_menu_item_v_lb_inset_l;

        if (ui2_g_menu_curr_lang == MLM_MENU_LANG_SPA)
        {
            ui2_menu_item_v_lb_inset_l = 40;
        }
        else
        {
            ui2_menu_item_v_lb_inset_l = 55;
        }

        /* Set Insets */
        t_inset.i4_left     = ui2_menu_item_v_lb_inset_l;
        t_inset.i4_right    = 0;
        t_inset.i4_top      = 0;
        t_inset.i4_bottom   = 0;
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_SET_CNT_INSET,
                              &t_inset,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_SET_COL_WIDTH,
                          WGL_PACK((UINT8)1),
                          WGL_PACK(MENU_ITEM_V_VALUE_W - MENU_ITEM_V_LB_ARROW_W*2 - ui2_menu_item_v_lb_inset_l));
        MENU_LOG_ON_FAIL(i4_ret);
    }

	UTF16_T w2s_str_tmp[128];
    c_memset(w2s_str_tmp, 0, 128);
	c_uc_w2s_strcpy(w2s_str_tmp, MENU_TEXT(ui2_msgid_title));

#if 0    //CID:4491975 ---> w2s_str_tmp impossible is "NULL"
	if (w2s_str_tmp != NULL)
	{
		c_uc_w2s_strcat (w2s_str_tmp, L" \0") ;
	}
#endif
    c_uc_w2s_strcat (w2s_str_tmp, L" \0") ;

    /* Set Title language */
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(w2s_str_tmp),
                          WGL_PACK(c_uc_w2s_strlen(
                              w2s_str_tmp)));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set elements language */
    for (ui2_i = ui2_msgid_elem_first; ui2_i <= ui2_msgid_elem_last; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2(ui2_i - ui2_msgid_elem_first, 1),
                              WGL_PACK(MENU_TEXT(ui2_i)));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_get_idx
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
INT32 menu_list_get_idx(
    HANDLE_T    h_widget,
    UINT16*     pui2_idx)
{
    INT32 i4_ret;
    UINT16 ui2_idx;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK(&ui2_idx),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    *pui2_idx = ui2_idx;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_set_idx
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
INT32 menu_list_set_idx(
    HANDLE_T    h_widget,
    UINT16      ui2_idx)
{
    /* Because the listbox has WGL_STL_LB_AUTO_SEL style,
       It will select the element at the same time. */
    return c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_idx),
                          WGL_PACK(0));
}

/*----------------------------------------------------------------------------
 * Name: menu_list_set_title_text
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
INT32 menu_list_set_title_text(
    HANDLE_T    h_widget,
    UTF16_T*    w2s_str)
{
    INT32   i4_ret;
    UINT32 ui4_text_style = 0;


	ui4_text_style |= WGL_STL_BDR_TIMG_NO_SMART_CUT;
    c_wgl_do_cmd(h_widget,
                 WGL_CMD_BDR_TIMG_SET_STYLE,
                 WGL_PACK(ui4_text_style),
                 WGL_PACK(NULL));

	UTF16_T w2s_str_tmp[128];
    c_memset(w2s_str_tmp, 0, 128);

    if( w2s_str != NULL )
    {
	    c_uc_w2s_strcpy(w2s_str_tmp, w2s_str);
    }

    // Fix coverity-4491260: Array compared against 0
	//if (w2s_str_tmp != NULL)
	{
		c_uc_w2s_strcat (w2s_str_tmp, L" \0");
	}

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(w2s_str_tmp),
                          WGL_PACK(c_uc_w2s_strlen(w2s_str_tmp)));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_set_text
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
INT32 menu_list_set_text(
    HANDLE_T    h_widget,
    UINT16      ui2_idx,
    UTF16_T*    w2s_str)
{
    return c_wgl_do_cmd(h_widget,
                  WGL_CMD_LB_SET_ITEM_TEXT,
                  WGL_PACK_2(ui2_idx,1),
                  WGL_PACK(w2s_str));
}


/*----------------------------------------------------------------------------
 * Name: menu_action_create
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
INT32 menu_action_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_LB_ITEM_T               at_items[1];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_enter;
    WGL_IMG_INFO_T    t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = MENU_ITEM_V_VALUE_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_white;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    c_memset(&t_img_suit_enter, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit_enter.h_normal                       = NULL_HANDLE;
    t_img_suit_enter.h_disable                      = NULL_HANDLE;
    t_img_suit_enter.h_highlight                    = NULL_HANDLE;
    t_img_suit_enter.h_highlight_unfocus            = NULL_HANDLE;
    t_img_suit_enter.h_pushed                       = NULL_HANDLE;
    t_img_suit_enter.h_selected                     = NULL_HANDLE;
    t_img_suit_enter.h_selected_disable             = NULL_HANDLE;
    t_img_suit_enter.h_selected_highlight           = NULL_HANDLE;
    t_img_suit_enter.h_selected_highlight_unfocus   = NULL_HANDLE;
    t_img_suit_enter.h_selected_pushed              = NULL_HANDLE;

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_g_empty;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_bk2_txt_disable;/*t_g_menu_color_white;*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);
    UINT32 ui4_text_style = 0;
	ui4_text_style |= WGL_STL_BDR_TIMG_NO_SMART_CUT;
    c_wgl_do_cmd(*ph_widget,
                  WGL_CMD_BDR_TIMG_SET_STYLE,
                  WGL_PACK(ui4_text_style),
                  WGL_PACK(NULL));

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}



/*----------------------------------------------------------------------------
 * Name: menu_action_create
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
INT32 menu_more_item_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_LB_ITEM_T               at_items[1];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_enter;
    WGL_IMG_INFO_T              t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = 10;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_white;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    c_memset(&t_img_suit_enter, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit_enter.h_normal                       = NULL_HANDLE;
    t_img_suit_enter.h_disable                      = NULL_HANDLE;
    t_img_suit_enter.h_highlight                    = NULL_HANDLE;
    t_img_suit_enter.h_highlight_unfocus            = NULL_HANDLE;
    t_img_suit_enter.h_pushed                       = NULL_HANDLE;
    t_img_suit_enter.h_selected                     = NULL_HANDLE;
    t_img_suit_enter.h_selected_disable             = NULL_HANDLE;
    t_img_suit_enter.h_selected_highlight           = NULL_HANDLE;
    t_img_suit_enter.h_selected_highlight_unfocus   = NULL_HANDLE;
    t_img_suit_enter.h_selected_pushed              = NULL_HANDLE;

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_g_empty;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title_more;
    t_title_info.ui1_align = WGL_AS_RIGHT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_action_chg_lang
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
INT32 menu_action_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title,
    UINT16      ui2_msgid_action)
{
    INT32   i4_ret;

	UTF16_T w2s_str_tmp[128];
    c_memset(w2s_str_tmp, 0, 128);
	c_uc_w2s_strcpy(w2s_str_tmp, MENU_TEXT(ui2_msgid_title));
#if 0    //CID:4491727 --->w2s_str_tmp impossible is "NULL"
	if (w2s_str_tmp != NULL)
	{
		c_uc_w2s_strcat (w2s_str_tmp, L" \0");
	}
#endif
    c_uc_w2s_strcat (w2s_str_tmp, L" \0");
    /* Set Title language */
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(w2s_str_tmp),
                          WGL_PACK(c_uc_w2s_strlen(
                              w2s_str_tmp)));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set action language */
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(0,0),
                          WGL_PACK(MENU_TEXT(ui2_msgid_action)));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_range_create
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
INT32 menu_range_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    INT32       i4_min,
    INT32       i4_max,
    MENU_RANGE_STYLE_T  e_style,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    UINT32          ui4_style;
    WGL_INSET_T     t_inset;
    GL_RECT_T       t_rect;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;
    WGL_PG_IDR_LOC_T      t_pg_idr_loc;
    WGL_INSET_T           t_range_inset_border = t_inset_border;

    /* hardcode style*/
    e_style = MENU_RANGE_STYLE_BAR;

#if 0    //CID:4491382
    if(e_style == MENU_RANGE_STYLE_BAR)
    {
        ui4_style = WGL_STL_GL_NO_BK | WGL_STL_GL_BDR_FILL_CNT_BK;
    }

    else
    {
        ui4_style = WGL_STL_GL_NO_BK | WGL_STL_GL_BDR_FILL_CNT_BK | WGL_STL_PG_POINT;
    }
#endif
    ui4_style = WGL_STL_GL_NO_BK | WGL_STL_GL_BDR_FILL_CNT_BK;

    /* Create progress bar */
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_range_inset_border.i4_left = MENU_ITEM_V_CNT_INSET_L + MENU_ITEM_V_RANGE_TITLE_W + 13;
    t_range_inset_border.i4_top = 8;

    /* Inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_range_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 220;
    t_inset.i4_right    = MENU_ITEM_V_INDICATOR_W+130;
    t_inset.i4_top      = 30;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_BAR_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Border Title Info */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.t_rc_ref.i4_right = MENU_ITEM_V_RANGE_TITLE_W;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    UINT32 ui4_text_style = 0;
	ui4_text_style |= WGL_STL_BDR_TIMG_NO_SMART_CUT;
    c_wgl_do_cmd(*ph_widget,
                  WGL_CMD_BDR_TIMG_SET_STYLE,
                  WGL_PACK(ui4_text_style),
                  WGL_PACK(NULL));

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk2_txt_disable;/*t_g_menu_color_white;*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Display mode */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_PG_SET_DISPLAY_MODE,
                          WGL_PACK(0),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size  = 24;

    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Range */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK(i4_min),
                           WGL_PACK(i4_max));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Block */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_BLK_PT_SIZE,
                           WGL_PACK(MENU_ITEM_RNG_BLK_PT_SIZE_W),
                           WGL_PACK(MENU_ITEM_RNG_BLK_PT_SIZE_H));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Min Size */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_BAR_MIN_SIZE,
                           WGL_PACK(0),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Indicator */
    SET_RECT_BY_SIZE(&t_pg_idr_loc.t_loc_rect,
                     MENU_ITEM_V_INDICATOR_X-10,
                     0,
                     MENU_ITEM_V_INDICATOR_W,
                     MENU_ITEM_V_HEIGHT);
    t_pg_idr_loc.ui1_align = WGL_AS_RIGHT_CENTER;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_IDR_LOC,
                           WGL_PACK(WGL_PG_CNT_ILT_POS),
                           WGL_PACK(&t_pg_idr_loc));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Levels */
    t_pg_levels.a_boundary[0] = i4_max;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* pb progress */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_bk2_txt_disable;/*t_g_menu_color_white;*/
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pg_silver;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pg_silver;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pg_silver;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_BODY),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

#if 0    //CID:4491382
    if(e_style == MENU_RANGE_STYLE_BAR)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pg_blue;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pg_blue;
        t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pg_blue;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_PG_LEVEL_1),
                              WGL_PACK(&t_img_info ));
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pb_point;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_point_hlt;
        t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pb_point_disable;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_PG_LEVEL_1),
                              WGL_PACK(&t_img_info ));
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pg_blue;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pg_blue;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pg_blue;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_LEVEL_1),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_range_chg_lang
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
INT32 menu_range_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title)
{
    INT32   i4_ret;

    /* Set Title language */
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(c_uc_w2s_strlen(
                              MENU_TEXT(ui2_msgid_title))));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_range_get_val
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
INT32 menu_range_get_val(
    HANDLE_T    h_widget,
    INT32*      pi4_val)
{
    INT32 i4_ret;
    INT32 i4_val;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_PG_GET_POS,
                          WGL_PACK(&i4_val),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    *pi4_val = i4_val;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_range_set_val
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
INT32 menu_range_set_val(
    HANDLE_T    h_widget,
    INT32       i4_val)
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK(i4_val),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_edit_create
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
INT32 menu_edit_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    BOOL        b_pwd_style,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
){
    INT32               i4_ret = 0;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_EB_KEY_MAP_T    t_eb_key_map;

    /* create editbox */
    if(b_pwd_style)
    {
        ui4_style = WGL_STL_EB_PASSWORD;
    }
    else
    {
        ui4_style = 0;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = t_inset_border.i4_left;
    t_inset.i4_right    = 20;
    t_inset.i4_top      = 5;
    t_inset.i4_bottom   = 5;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_pwd_style)
    {
        c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
        t_inset.i4_left     = 200;
        t_inset.i4_right    = 20;
        t_inset.i4_top      = 5;
        t_inset.i4_bottom   = 5;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_GL_SET_INSET,
                              &t_inset,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
        t_inset.i4_left     = 2;
        t_inset.i4_right    = 2;
        t_inset.i4_top      = 0;
        t_inset.i4_bottom   = 0;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_EB_SET_CNT_INSET,
                              &t_inset,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set EB Alignment */
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_EB_SET_ALIGN,
                              WGL_PACK(MENU_ITEM_PWD_ALIGN),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
        t_fnt_info.e_font_size  = MENU_ITEM_PWD_FNT_SIZE;
        t_fnt_info.e_font_style = MENU_ITEM_PWD_FNT_STYLE;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd (*ph_widget,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        /* Set Cnt Insets */
        c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
        t_inset.i4_left     = 2;
        t_inset.i4_right    = 2;
        t_inset.i4_top      = 0;
        t_inset.i4_bottom   = 0;
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_EB_SET_CNT_INSET,
                              &t_inset,
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set EB Alignment */
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_EB_SET_ALIGN,
                              WGL_PACK(MENU_ITEM_EDIT_ALIGN),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
        t_fnt_info.e_font_size  = MENU_ITEM_EDIT_FNT_SIZE;
        t_fnt_info.e_font_style = MENU_ITEM_EDIT_FNT_STYLE;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd (*ph_widget,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_text_entry_small;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_text_entry_small;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_text_entry_small;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)5),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),  /*Attr mask*/
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING)); /*Attr value*/
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    c_strcpy(t_title_info.t_font.a_c_font_name, menu_font_name());
    t_title_info.t_font.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_title_info.t_font.e_font_style = MENU_ITEM_FNT_STYLE;
    t_title_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    UINT32 ui4_text_style = 0;
	ui4_text_style |= WGL_STL_BDR_TIMG_NO_SMART_CUT;
    c_wgl_do_cmd(*ph_widget,
                  WGL_CMD_BDR_TIMG_SET_STYLE,
                  WGL_PACK(ui4_text_style),
                  WGL_PACK(NULL));

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_enter_editing = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_edit_chg_lang
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
INT32 menu_edit_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title)
{
    INT32   i4_ret;

    /* Set Title language */
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(c_uc_w2s_strlen(
                              MENU_TEXT(ui2_msgid_title))));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

extern INT32 menu_list2_create(
    HANDLE_T                h_parent,
    const GL_RECT_T*        pt_rect,
    wgl_widget_proc_fct     pf_wdgt_proc,
    const WGL_LB_INIT_T*    pt_lb_init,
    VOID*                   pv_tag,
    HANDLE_T*               ph_lb)
{
    INT32 i4_ret;
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    UINT8                       ui1_col;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;

    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_LIST_BOX,
                                  WGL_CONTENT_LIST_BOX_DEF,
                                  WGL_BORDER_TRANSP,
                                  pt_rect,
                                  pf_wdgt_proc,
                                  255,
                                  (VOID*)pt_lb_init,
                                  pv_tag,
                                  ph_lb);
    if (i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_FONT,
                                   WGL_PACK((UINT16)ui1_col),
                                   WGL_PACK(&t_fnt_info));
            MENU_LOG_ON_FAIL(i4_ret);
        }
   }

    /* Set Inset */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_GL_SET_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = MENU_ITEM_BAR_CNT_INSET_L;
    t_inset.i4_right  = MENU_ITEM_BAR_CNT_INSET_R;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(ui1_col == 0)
        {
            t_inset.i4_left = 0;
        }
        else
        {
            t_inset.i4_left = 10;
        }

        i4_ret = c_wgl_do_cmd (*ph_lb,
                               WGL_CMD_LB_SET_COL_INSET,
                               WGL_PACK((UINT16)ui1_col),
                               WGL_PACK(&t_inset));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_elem.t_normal            = t_g_menu_color_transp;
    t_clr_elem.t_disable           = t_g_menu_color_transp;
    t_clr_elem.t_highlight         = t_g_menu_color_transp;
    t_clr_elem.t_highlight_unfocus = t_g_menu_color_transp;
    t_clr_elem.t_pushed            = t_g_menu_color_transp;
    t_clr_elem.t_selected          = t_g_menu_color_transp;
    t_clr_elem.t_selected_disable  = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd (*ph_lb,
                               WGL_CMD_LB_SET_COL_COLOR,
                               WGL_PACK_2(ui1_col, WGL_CLR_BK),
                               WGL_PACK(& t_clr_elem));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    t_clr_elem.t_normal            = t_g_menu_color_white;
    t_clr_elem.t_disable           = t_g_menu_color_white;
    t_clr_elem.t_highlight         = t_g_menu_color_white;
    t_clr_elem.t_highlight_unfocus = t_g_menu_color_white;
    t_clr_elem.t_pushed            = t_g_menu_color_white;
    t_clr_elem.t_selected          = t_g_menu_color_white;
    t_clr_elem.t_selected_disable  = t_g_menu_color_white;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_COLOR,
                                   WGL_PACK_2(ui1_col, WGL_CLR_TEXT),
                                   WGL_PACK(& t_clr_elem));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set background image */
    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_text_chg_lang
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
INT32 menu_text_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_LB_ITEM_T               at_items[1];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    UINT16 ui2_i;
    WGL_IMG_INFO_T    t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = MENU_ITEM_TEXT_ALIGN;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = MENU_ITEM_V_VALUE_W_CH_SCAN;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal             = t_g_menu_color_white;
    t_lb_color.t_disable            = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight          = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus  = t_g_menu_color_white;
    t_lb_color.t_pushed             = t_g_menu_color_white;
    t_lb_color.t_selected           = t_g_menu_color_white;
    t_lb_color.t_selected_disable   = t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

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
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui2_i=0; ui2_i<1; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui2_i, WGL_CLR_BK),
                              WGL_PACK(&t_lb_color) );
        MENU_LOG_ON_FAIL(i4_ret);
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_g_empty;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);
    UINT32 ui4_text_style = 0;
	ui4_text_style |= WGL_STL_BDR_TIMG_NO_SMART_CUT;
    c_wgl_do_cmd(*ph_widget,
                  WGL_CMD_BDR_TIMG_SET_STYLE,
                  WGL_PACK(ui4_text_style),
                  WGL_PACK(NULL));

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_text_chg_lang
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
INT32 menu_text_chg_lang(
    HANDLE_T    h_widget,
    UINT16      ui2_msgid_title)
{
    INT32    i4_ret;

    /* Set Title language */
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(ui2_msgid_title))));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_text_set_text
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
INT32 menu_text_set_text(
    HANDLE_T    h_widget,
    UTF16_T*    w2s_str)
{
    INT32   i4_ret;
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2(0,0),
                          WGL_PACK(w2s_str));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_scan_pb_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 menu_scan_pb_create(
                         HANDLE_T   h_parent,
                         INT32      i4_index,
                         wgl_widget_proc_fct pf_wdgt_proc,
                         MENU_SCAN_PB_ITEM_T*   pt_scan_pb )
{
    INT32                 i4_ret;
    GL_RECT_T             t_rect;
    WGL_INSET_T           t_inset;
    WGL_FONT_INFO_T       t_fnt_info;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;
    WGL_PG_IDR_LOC_T      t_pg_idr_loc;
    WGL_COLOR_INFO_T      t_clr_info;
    WGL_IMG_INFO_T        t_img_info;
    WGL_INSET_T           t_range_inset_border = t_inset_border;

    /*Create Frm*/
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_LEFT,
                     MENU_ITEM_V_HEIGHT * (i4_index) + 2,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)(0),
                                 (VOID*)0,
                                 &(pt_scan_pb->h_frm));
    MENU_LOG_ON_FAIL(i4_ret);


    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(pt_scan_pb->h_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /*Create Bar*/
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_SCAN_RNG_PB_X,
                     (MENU_SCAN_RNG_PB_Y),
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT - 42 );
    i4_ret = c_wgl_create_widget(pt_scan_pb->h_frm,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)(NULL),
                                 NULL,
                                 &(pt_scan_pb->h_bar));
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_range_inset_border.i4_left = MENU_ITEM_V_CNT_INSET_L + MENU_ITEM_V_RANGE_TITLE_W + 10;

    /* Inset */
    i4_ret = c_wgl_do_cmd(pt_scan_pb->h_bar,
                          WGL_CMD_GL_SET_INSET,
                          &t_range_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(& t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = MENU_ITEM_V_INDICATOR_W;
    t_inset.i4_top      = 18;
    t_inset.i4_bottom   = 2;

    i4_ret = c_wgl_do_cmd(pt_scan_pb->h_bar,
                          WGL_CMD_PG_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left     = MENU_SCAN_PB_BAR_INSET_L;
    t_inset.i4_right    = MENU_SCAN_PB_BAR_INSET_R;
    t_inset.i4_top      = MENU_SCAN_PB_BAR_INSET_T;
    t_inset.i4_bottom   = MENU_SCAN_PB_BAR_INSET_B;
    i4_ret = c_wgl_do_cmd(pt_scan_pb->h_bar,
                          WGL_CMD_PG_SET_BAR_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_scan_pb->h_bar,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Range */
    i4_ret = c_wgl_do_cmd (pt_scan_pb->h_bar,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK((INT32)0),
                           WGL_PACK((INT32)100));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Levels */
    t_pg_levels.a_boundary[0] = 100;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (pt_scan_pb->h_bar,
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Display Modes */
    i4_ret = c_wgl_do_cmd (pt_scan_pb->h_bar,
                           WGL_CMD_PG_SET_DISPLAY_MODE,
                           WGL_PACK(WGL_PG_DM_PERCENT),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Indicator */
    c_memset(&t_pg_idr_loc, 0, sizeof(WGL_PG_IDR_LOC_T));
    SET_RECT_BY_SIZE(&t_pg_idr_loc.t_loc_rect,
                     MENU_SCAN_PB_CNT_INSET_L,
                     3,
                     MENU_SCAN_PB_VAL_W,
                     MENU_ITEM_V_HEIGHT-32);
    t_pg_idr_loc.ui1_align = WGL_AS_LEFT_CENTER;

    i4_ret = c_wgl_do_cmd (pt_scan_pb->h_bar,
                           WGL_CMD_PG_SET_IDR_LOC,
                           WGL_PACK(WGL_PG_CNT_ILT_POS),
                           WGL_PACK(&t_pg_idr_loc));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_scan_pb->h_bar,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pb_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pb_bk;
    i4_ret = c_wgl_do_cmd(pt_scan_pb->h_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_BODY),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_pb_bar;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_pb_bar;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_pb_bar;
    i4_ret = c_wgl_do_cmd(pt_scan_pb->h_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_PG_LEVEL_1),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(pt_scan_pb->h_bar,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}
/*----------------------------------------------------------------------------
 * Name: menu_edit_create_ex
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
INT32 menu_edit_create_ex(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget
){
    INT32               i4_ret = 0;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_EB_KEY_MAP_T    t_eb_key_map;

    /* create editbox */
    ui4_style = 0;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = t_inset_border.i4_left + 50;
    t_inset.i4_right    = 20;
    t_inset.i4_top      = 5;
    t_inset.i4_bottom   = 5;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Cnt Insets */
    t_inset.i4_left     = 2;
    t_inset.i4_right    = 2;
    t_inset.i4_top      = 5;
    t_inset.i4_bottom   = 5;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = MENU_ITEM_EDIT_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_EDIT_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set txt color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set background images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       =h_g_menu_img_text_entry_small;
    t_img_info.u_img_data.t_standard.t_highlight    =h_g_menu_img_text_entry_small;
    t_img_info.u_img_data.t_standard.t_disable      =h_g_menu_img_text_entry_small;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set EB Input Limit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)5),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    c_strcpy(t_title_info.t_font.a_c_font_name, menu_font_name());
    t_title_info.t_font.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_title_info.t_font.e_font_style = MENU_ITEM_FNT_STYLE;
    t_title_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    UINT32 ui4_text_style = 0;
	ui4_text_style |= WGL_STL_BDR_TIMG_NO_SMART_CUT;
    c_wgl_do_cmd(*ph_widget,
                  WGL_CMD_BDR_TIMG_SET_STYLE,
                  WGL_PACK(ui4_text_style),
                  WGL_PACK(NULL));

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_enter_editing = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_list_create_ex
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
INT32 menu_list_create_ex(
    HANDLE_T    h_parent,
    INT32       i4_index,
    UINT16      ui2_max_elem_num,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[3];
    WGL_LB_ITEM_T               at_items[3];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_left;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_right;
    UINT16                      ui2_i;
    WGL_IMG_INFO_T              t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /*=======================================*
     | Title                |   | option |   |      ---   normal
     | Title                | < | option | > |      ---   highlight
     *=======================================*/

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_width        = MENU_ITEM_V_LB_ARROW_W;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = (MENU_ITEM_V_VALUE_W - MENU_ITEM_V_LB_ARROW_W*2);

    at_cols[2].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[2].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[2].ui2_width        = MENU_ITEM_V_LB_ARROW_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = ui2_max_elem_num;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 3;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT * i4_index,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(0),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(1),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          WGL_PACK(2),
                          WGL_PACK(&t_inset));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(1),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(1, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui2_i=0; ui2_i<3; ui2_i++)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(ui2_i, WGL_CLR_BK),
                              WGL_PACK(&t_lb_color) );
        MENU_LOG_ON_FAIL(i4_ret);
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    c_memset(&t_img_suit_left, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    c_memset(&t_img_suit_right, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit_left.h_normal                      = NULL_HANDLE;
    t_img_suit_left.h_disable                     = NULL_HANDLE;
    t_img_suit_left.h_highlight                   = NULL_HANDLE;
    t_img_suit_left.h_highlight_unfocus           = NULL_HANDLE;
    t_img_suit_left.h_pushed                      = NULL_HANDLE;
    t_img_suit_left.h_selected                    = NULL_HANDLE;
    t_img_suit_left.h_selected_disable            = NULL_HANDLE;
    t_img_suit_left.h_selected_highlight          = NULL_HANDLE;
    t_img_suit_left.h_selected_highlight_unfocus  = NULL_HANDLE;
    t_img_suit_left.h_selected_pushed             = NULL_HANDLE;

    t_img_suit_right.h_normal                      = NULL_HANDLE;
    t_img_suit_right.h_disable                     = NULL_HANDLE;
    t_img_suit_right.h_highlight                   = NULL_HANDLE;
    t_img_suit_right.h_highlight_unfocus           = NULL_HANDLE;
    t_img_suit_right.h_pushed                      = NULL_HANDLE;
    t_img_suit_right.h_selected                    = NULL_HANDLE;
    t_img_suit_right.h_selected_disable            = NULL_HANDLE;
    t_img_suit_right.h_selected_highlight          = NULL_HANDLE;
    t_img_suit_right.h_selected_highlight_unfocus  = NULL_HANDLE;
    t_img_suit_right.h_selected_pushed             = NULL_HANDLE;

    for (ui2_i=0; ui2_i<ui2_max_elem_num; ui2_i++)
    {
        at_items[0].e_col_type = LB_COL_TYPE_IMG_SUIT;
        at_items[0].data.pt_img_suit = &t_img_suit_left;

        at_items[1].e_col_type = LB_COL_TYPE_TEXT;
        at_items[1].data.pw2s_text = w2s_g_empty;

        at_items[2].e_col_type = LB_COL_TYPE_IMG_SUIT;
        at_items[2].data.pt_img_suit = &t_img_suit_right;

        i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
        MENU_LOG_ON_FAIL(i4_ret);
    }


    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_BOTTOM;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

BOOL menu_list_is_overlop(HANDLE_T h_widget)
{
    BOOL    b_ret = FALSE;

    if (h_widget != NULL_HANDLE
        &&(h_widget == h_g_input_source_wgt
            || h_widget == h_g_cc_digital_style_wgt))
    {
        b_ret = TRUE;
    }
    else
    {
        b_ret = FALSE;
    }

    return b_ret;
}

/*----------------------------------------------------------------------------
 * Name: name_input_list_adjust_rect
 *
 * Description: adjust list rect for name input
 *
 * Inputs:
 *
 *
 ----------------------------------------------------------------------------*/
INT32 menu_list_adjust_rect_ex(HANDLE_T h_widget)
{
    INT32          i4_ret = -1;
    UTF16_T        w2s_str[128]    = {0};
    INT32          i4_width_left  = 0;
    INT32          i4_width_right = 0;
    INT32          i4_hight;
    INT32          i4_title_hight = 0;
    INT32          i4_title_width = 0;
    WGL_INSET_T    t_inset;
    INT32          i4_text_width = 0;
    UINT16         ui2_idx = 0;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect_temp;
    WGL_INSET_T                 t_inset_temp;

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_BDR_TIMG_GET_TITLE_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK(sizeof(w2s_str)/sizeof(UTF16_T)-sizeof(UTF16_T)));
    MENU_LOG_ON_FAIL(i4_ret);

    if (MENUR_OK == i4_ret && c_uc_w2s_strlen(w2s_str) > 0)
    {
        i4_ret = c_fe_get_string_size(menu_page_get_font_h(),
                                      w2s_str,
                                      c_uc_w2s_strlen(w2s_str),
                                      (INT32*)&i4_title_width,
                                      (INT32*)&i4_title_hight);

        if(AEER_OK != i4_ret)
        {
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = c_wgl_do_cmd(h_widget,
                           WGL_CMD_LB_GET_HLT_INDEX,
                           WGL_PACK(&ui2_idx),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_GET_ITEM_TEXT,
                          WGL_PACK_2(ui2_idx, 1),
                          WGL_PACK(w2s_str));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_fe_get_string_size(menu_page_get_font_h(),
                      w2s_str,
                      c_uc_w2s_strlen(w2s_str),
                      (INT32*)&i4_text_width,
                      (INT32*)&i4_hight);
    if(AEER_OK != i4_ret)
    {
        return MENUR_FAIL;
    }


    i4_ret = c_wgl_img_tpl_get_size(h_g_menu_img_list_item_leftarrow,(UINT32*)&i4_width_left,(UINT32*)&i4_hight);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_img_tpl_get_size(h_g_menu_img_list_item_rightarrow,(UINT32*)&i4_width_right,(UINT32*)&i4_hight);
    MENU_LOG_ON_FAIL(i4_ret);

    if (i4_title_width + i4_width_left + i4_text_width + i4_width_right > (INT32)(MENU_ITEM_V_WIDE - MENU_ITEM_V_LB_INSET_L - MENU_ITEM_V_CNT_INSET_R)/*(MENU_ITEM_V_VALUE_W - MENU_ITEM_V_LB_ARROW_W*2 - MENU_ITEM_V_LB_INSET_L)*/)
    {
        i4_text_width = MENU_ITEM_V_WIDE - (i4_title_width + i4_width_left + i4_width_right + MENU_ITEM_V_LB_INSET_L + MENU_ITEM_V_CNT_INSET_R);
    }

    c_memset(&t_inset_temp,0, sizeof(WGL_INSET_T));
    c_memcpy(&t_inset_temp,&t_inset_border, sizeof(WGL_INSET_T));
    t_inset_temp.i4_left = MENU_ITEM_V_WIDE - i4_width_left - 15 - i4_text_width - FRAME_LEFT_RIGHT_INTV;

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(h_widget,
                       WGL_CMD_GL_SET_INSET,
                       &t_inset_temp,
                       NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Border Title */
    c_memset(&t_rect_temp, 0, sizeof(GL_RECT_T));
    c_memcpy(&t_rect_temp,&t_rect_border_title, sizeof(GL_RECT_T));

    t_rect_temp.i4_right = t_inset_temp.i4_left - 8;

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_temp;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;                 // Dennis             // wording of list select item ex:on/off item
    i4_ret = c_wgl_do_cmd(h_widget,
                       WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                       &t_title_info,
                       NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(h_widget,
                       WGL_CMD_LB_SET_CNT_INSET,
                       &t_inset,
                       NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = c_wgl_do_cmd(h_widget,
                   WGL_CMD_LB_SET_COL_WIDTH,
                   WGL_PACK((UINT8)0),
                   WGL_PACK(i4_width_left+15));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
                   WGL_CMD_LB_SET_COL_WIDTH,
                   WGL_PACK((UINT8)1),
                   WGL_PACK(i4_text_width));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
                   WGL_CMD_LB_SET_COL_WIDTH,
                   WGL_PACK((UINT8)2),
                   WGL_PACK(i4_width_right+15));
    MENU_LOG_ON_FAIL(i4_ret);


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_list_adjust_rect
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
INT32 menu_list_adjust_rect(HANDLE_T h_widget)
{
    INT32          i4_ret = -1;
    UTF16_T        w2s_str[33]    = {0};
    INT32          i4_width_left  = 0;
    INT32          i4_width_right = 0;
    INT32          i4_hight;
    WGL_INSET_T    t_inset;
    INT32          i4_text_width = 0;
    UINT16         ui2_idx = 0;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect_temp;
    WGL_INSET_T                 t_inset_temp;

    if (TRUE == menu_list_is_overlop(h_widget))
    {
        return menu_list_adjust_rect_ex(h_widget);
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_HLT_INDEX,
                         WGL_PACK(&ui2_idx),
                         WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_LB_GET_ITEM_TEXT,
                          WGL_PACK_2(ui2_idx, 1),
                          WGL_PACK(w2s_str));
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = c_fe_get_string_size(menu_page_get_font_h(),
                          w2s_str,
                          c_uc_w2s_strlen(w2s_str),
                          (INT32*)&i4_text_width,
                          (INT32*)&i4_hight);
     if(AEER_OK != i4_ret)
     {
         return MENUR_FAIL;
     }

     i4_ret = c_wgl_img_tpl_get_size(h_g_menu_img_list_item_leftarrow,(UINT32*)&i4_width_left,(UINT32*)&i4_hight);
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = c_wgl_img_tpl_get_size(h_g_menu_img_list_item_rightarrow,(UINT32*)&i4_width_right,(UINT32*)&i4_hight);
     MENU_LOG_ON_FAIL(i4_ret);

     c_memset(&t_inset_temp,0, sizeof(WGL_INSET_T));
     c_memcpy(&t_inset_temp,&t_inset_border, sizeof(WGL_INSET_T));

     t_inset_temp.i4_left = MENU_ITEM_V_WIDE - i4_width_left - 15 - i4_text_width - FRAME_LEFT_RIGHT_INTV;

     /* Set Insets */
     i4_ret = c_wgl_do_cmd(h_widget,
                           WGL_CMD_GL_SET_INSET,
                           &t_inset_temp,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);


     /* Set Border Title */
     c_memset(&t_rect_temp, 0, sizeof(GL_RECT_T));
     c_memcpy(&t_rect_temp,&t_rect_border_title, sizeof(GL_RECT_T));

     t_rect_temp.i4_right = t_inset_temp.i4_left - 8;

     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
     t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

     c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
     t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
     t_title_info.t_font = t_fnt_info;
     t_title_info.t_rc_ref = t_rect_temp;
     t_title_info.ui1_align = WGL_AS_LEFT_CENTER;                // Dennis           // wording of list select item ex:on/off item
     i4_ret = c_wgl_do_cmd(h_widget,
                           WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                           &t_title_info,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
     i4_ret = c_wgl_do_cmd(h_widget,
                           WGL_CMD_LB_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);


     i4_ret = c_wgl_do_cmd(h_widget,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)0),
                       WGL_PACK(i4_width_left+15));
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = c_wgl_do_cmd(h_widget,
                       WGL_CMD_LB_SET_COL_WIDTH,
                       WGL_PACK((UINT8)1),
                       WGL_PACK(i4_text_width));
     MENU_LOG_ON_FAIL(i4_ret);

     i4_ret = c_wgl_do_cmd(h_widget,
                      WGL_CMD_LB_SET_COL_WIDTH,
                      WGL_PACK((UINT8)2),
                      WGL_PACK(i4_width_right+15));
     MENU_LOG_ON_FAIL(i4_ret);


    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_scan_pb_set_satus
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
INT32 menu_scan_pb_set_satus(HANDLE_T h_widget,BOOL b_is_enable )
{
    INT32                 i4_ret = 0;
    WGL_COLOR_INFO_T      t_clr_info;

    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;

    if(b_is_enable == TRUE)
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_bk1_txt_disable;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk1_txt_disable;
        t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_bk1_txt_disable;
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);


    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_util_create_txt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 menu_util_create_txt(
    HANDLE_T                    h_parent,
    UINT32                      ui4_style,
    const GL_RECT_T*            pt_rect,
    UINT8                       ui1_align,
    HANDLE_T*                   ph_txt)
{
    WGL_COLOR_INFO_T            t_clr_info;
    INT32                       i4_ret;
    WGL_FONT_INFO_T             t_fnt_info;

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)(ui4_style),
                                 NULL,
                                 ph_txt);
    if(WGLR_OK != i4_ret)
    {
        MENU_LOG_ON_FAIL(i4_ret);

        *ph_txt = NULL_HANDLE;
        return MENUR_FAIL;
    }

    do
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_white;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_white;
        i4_ret = c_wgl_do_cmd(*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info));
        if(WGLR_OK != i4_ret)
        {
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }

        /*font*/
        i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_GL_SET_FONT, (VOID*)&t_fnt_info, NULL);
        if(WGLR_OK != i4_ret)
        {
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }

        i4_ret = c_wgl_do_cmd(*ph_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK(ui1_align),
                              NULL);
        if(WGLR_OK != i4_ret)
        {
            MENU_LOG_ON_FAIL(i4_ret);
            break;
        }

        return MENUR_OK;

    } while(0);

    /*free widget*/
    i4_ret = c_wgl_destroy_widget_ex(*ph_txt,FALSE);
    MENU_ASSERT(WGLR_OK == i4_ret);

    *ph_txt = NULL_HANDLE;
    return MENUR_FAIL;
}
/*----------------------------------------------------------------------------
 * Name: menu_util_itoa
 *
 * Description: Interger to string utility function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 menu_util_itoa(UTF16_T* w2s_dst,
                   INT32 i4_src,
                   UINT32 ui4_dst_len)
{
    INT32   i4_ret=0;
    CHAR    s_buf[32]={0};

    c_sprintf(s_buf, "%d",  i4_src);
    i4_ret= c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_util_ch_num_to_str
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
VOID menu_util_ch_num_to_str(UINT16      ui2_major,
                          UINT16      ui2_minor,
                          BOOL        b_one_part_ch,
                          UTF16_T*    w2s_str,
                          UINT32      ui4_dst_len)
{
    CHAR    s_str[64];
    c_memset(s_str, 0, sizeof(s_str));
    if (b_one_part_ch)
    {   /* One part channel number */
        c_sprintf(s_str,
                  "%d",
                  ui2_major);
    }
    else
    {   /* Two part channel number */
        c_sprintf(s_str,
                  CHANNEL_NUMBER_FORMAT,   /* Defined in a_common.h */
                  ui2_major,
                  ui2_minor);
    }
    c_uc_ps_to_w2s(s_str ,w2s_str, ui4_dst_len);
}

/*----------------------------------------------------------------------------
 * Name: menu_toast_range_create(
 *
 * Description:
 *
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID menu_toast_range_create(VOID)
{
    INT32               i4_ret = 0;
    HANDLE_T            h_canvas = NULL_HANDLE;
    TOAST_INIT_PARAM_T  t_toast_param;

        /* Create Timer */
    i4_ret = c_timer_create(&h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_get_canvas(&h_canvas);
    c_memset(&t_toast_param, 0x0 ,sizeof(TOAST_INIT_PARAM_T));
    t_toast_param.e_toast_style = TOAST_STYLE_SETTING_SLIDER;
    t_toast_param.h_canvas = h_canvas;

    i4_ret = a_toast_create(&t_toast_param, &_h_g_slider);
    MENU_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: menu_toast_range_show
 *
 * Description:
 *
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID menu_toast_range_show(HANDLE_T    h_widget,INT32 i4_min_val,INT32 i4_max_val,INT32 i4_val,UINT16 ui2_msgid)
{
    INT32     i4_ret = 0;
    UTF16_T   w2s_txt[128] = {0};
    TOAST_CUSTOMIZATION_DATA_T  t_toast_data = {0};

    DBG_LOG_PRINT(("-toast show %s,%d,min:%d,max:%d,val%d,msgid:%d\n\r",
        __FILE__,__LINE__,i4_min_val,i4_max_val,i4_val,ui2_msgid));

    c_uc_w2s_strcpy(w2s_txt, MENU_TEXT(ui2_msgid));

    if(0 == i4_min_val)
    {
        t_toast_data.u.t_slider_init.e_track_type = TOAST_VOL_TRACK_CENTER;
    }
    else if(i4_min_val < 0)
    {
        t_toast_data.u.t_slider_init.e_track_type = TOAST_VOL_TRACK_HALF;
    }

    t_toast_data.h_focus_handle = h_widget;
    t_toast_data.u.t_slider_init.i4_vol_track_val = i4_val;
    t_toast_data.u.t_slider_init.i4_vol_track_range = i4_max_val;
    t_toast_data.u.t_slider_init.w2s_eq_msg = (VOID*)w2s_txt;

    i4_ret = c_timer_stop(h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    /* fix DTV00863818*/
    c_wgl_float(_h_g_slider, TRUE, FALSE);

    i4_ret = a_toast_show(_h_g_slider, &t_toast_data);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_start(h_timer,
                           ui4_timer_delay,
                           X_TIMER_FLAG_ONCE,
                           menu_range_timer_nfy_fct,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_SLIDER));
#endif
}

/*----------------------------------------------------------------------------
 * Name: menu_toast_range_hide
 *
 * Description:
 *
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID menu_toast_range_hide(VOID)
{
    INT32     i4_ret = 0;

    c_wgl_float(_h_g_slider, FALSE, FALSE);

    i4_ret = a_toast_hide(_h_g_slider);
    MENU_LOG_ON_FAIL(i4_ret);
#ifdef APP_ZOOM_MODE_SUPPORT
        a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_SLIDER));
#endif
}

VOID menu_set_toast_range_flag(BOOL b_toast_range_flag)
{
    b_g_toast_range = b_toast_range_flag;
}

BOOL menu_get_toast_range_flag(VOID)
{
    return b_g_toast_range;
}

