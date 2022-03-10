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
 * $RCSfile: menu_page_burn.c,v $
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
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_gl.h"

#include "app_util/a_ui.h"
#include "app_util/a_cfg.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_dbg.h"

#ifdef COMMON_BURN_ENABLE

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_burn;

static  BOOL        b_created       = FALSE;
static  HANDLE_T    h_frm_burn      = NULL_HANDLE;
static  HANDLE_T    h_timer         = NULL_HANDLE;
static  UINT8       ui1_osd_alpha;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static VOID _do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    c_wgl_repaint(h_frm_burn, NULL, TRUE);
}

static VOID _timer_notify_fct(
    HANDLE_T  pt_tm_handle,
    VOID*     pv_tag)
{
    menu_async_invoke(_do_timer_nfy, NULL, 0, FALSE);
}

INT32 _frm_burn_paint(
    GL_HGRAPHICS_T  h_graphics)
{
    static UINT8        ui1_step = 0;
    static GL_COLOR_T   at_color[] =
    {
        {255, {  0}, {  0}, {255}},
        {255, {255}, {  0}, {  0}},
        {255, {255}, {255}, {255}},
        {255, {  0}, {255}, {  0}},
        {255, {255}, {255}, {  0}},
        {255, {255}, {  0}, {255}},
        {255, {  0}, {255}, {255}},
        {255, {  0}, {  0}, {  0}}
    };

    INT32           i4_ret;
    GL_RECT_T       t_rect;

    SET_RECT_BY_SIZE(&t_rect, 0, 0, SCREEN_W, SCREEN_H);

    i4_ret = c_gl_set_color(h_graphics, &at_color[ui1_step]);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_gl_fill_rect(h_graphics, &t_rect);
    MENU_CHK_FAIL(i4_ret);

    ui1_step = (ui1_step + 1) % (sizeof(at_color) / sizeof(at_color[0]));

    return MENUR_OK;
}

static INT32 _frm_burn_proc_fct(
    HANDLE_T                        h_widget,
    UINT32                          ui4_msg,
    VOID*                           pv_param1,
    VOID*                           pv_param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_PAINT:
        _frm_burn_paint((GL_HGRAPHICS_T)pv_param1);
        return WGLR_OK;
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;
        switch (ui4_keycode)
        {
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget,ui4_msg,pv_param1,pv_param2);
}

static _page_create()
{
    INT32       i4_ret;
    HANDLE_T    h_frm_root;
    GL_RECT_T   t_rect;

    i4_ret = menu_pm_get_root_frm(&h_frm_root);
    MENU_CHK_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect, 0, 0, SCREEN_W, SCREEN_H);

    i4_ret = c_wgl_create_widget(h_frm_root,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _frm_burn_proc_fct,
                                 255,
                                 (VOID*)0,
                                 0,
                                 &h_frm_burn);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_timer_create(&h_timer);
    MENU_CHK_FAIL(i4_ret);

    b_created = TRUE;

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
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
    INT32   i4_ret;
    if(!b_created)
    {
        i4_ret = _page_create();
        MENU_CHK_FAIL(i4_ret);
    }

    /* Hide the main menu */
    menu_main_set_visibility(FALSE);

    /* Show the burn frame */
    c_wgl_set_visibility(h_frm_burn, WGL_SW_NORMAL);

    /* Change OSD alpha */
    menu_get_osd_alpha(&ui1_osd_alpha);
    menu_set_osd_alpha(255);

    /* disable the menu timer */
    menu_timer_stop();
    menu_timer_enable(FALSE);

    /* start timer */
    c_timer_start(h_timer, 3000, X_TIMER_FLAG_REPEAT, _timer_notify_fct, NULL);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    /* Show the main menu */
    menu_main_set_visibility(TRUE);

    /* Hide the burn frame */
    c_wgl_set_visibility(h_frm_burn, WGL_SW_HIDE);

    /* Change OSD alpha */
    menu_set_osd_alpha(ui1_osd_alpha);

    /* Enable the menu timer */
    menu_timer_start();
    menu_timer_enable(TRUE);

    /* Start timer */
    c_timer_stop(h_timer);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    c_wgl_set_focus(h_frm_burn, WGL_NO_AUTO_REPAINT);
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

INT32 menu_common_page_burn_init(VOID)
{

    t_g_menu_common_page_burn.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_burn.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_burn.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_burn.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_burn.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_burn.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_burn.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
#endif /* COMMON_BURN_ENABLE */

