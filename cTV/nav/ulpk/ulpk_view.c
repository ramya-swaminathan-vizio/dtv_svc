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
 * $RCSfile: ulpk_view.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
 
#ifdef APP_USB_INSTALL_ULPK_SUPPORT
#ifdef APP_537X_SUPPORT
#include "u_common.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_svctx.h"

#include "app_util/a_sleep_timer.h"
#include "nav/ulpk/ulpk.h"
#include "nav/nav_common.h"
#include "res/nav/ulpk/ulpk_view_rc.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

typedef struct _NAV_ULPK_VIEW_T
{
    NAV_ULPK_T*                pt_ctrl;
    HANDLE_T                    h_frame;
    HANDLE_T                    h_msg;
    
    ULPK_VIEW_RC_T             t_rc;
} NAV_ULPK_VIEW_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_ULPK_VIEW_T t_g_nav_ulpk_view = {0};
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_view_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_ulpk_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    switch (ui4_key_code) {
    case BTN_RED:
        return TRUE;
    default:
        return FALSE;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_view_show
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_view_show(
                    NAV_ULPK_VIEW_T*           pt_view,
                    NAV_ULPK_STATE_ID_T        t_ulpk_state
                    )
{
    UTF16_T  w2s_string[512+1]       = {0};
    SIZE_T   z_len  ;
    INT32    i4_ret;

    switch (t_ulpk_state)
    {
        case NAV_ULPK_STATE_ID_PLUG_USB_STICK:
            c_uc_w2s_strcpy(w2s_string,L" Please plug a factory USB stick to install ULPK ---");
            break;
        case NAV_ULPK_STATE_ID_INSTALL_ULPK:
            c_uc_w2s_strcpy(w2s_string,L" Do not power off TV , installation in progress ---");
            break;
        case NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL:
            c_uc_w2s_strcpy(w2s_string,L" Installation fail !");
            break;
        case NAV_ULPK_STATE_ID_INSTALL_COMPLETE_SUCCESS:
            c_uc_w2s_strcpy(w2s_string,L" Installation success !");
            break;
        default:
            c_uc_w2s_strcpy(w2s_string,L"");
            break;
    }
    z_len       = c_uc_w2s_strlen((UTF16_T *)(w2s_string));
    i4_ret = c_wgl_do_cmd(pt_view->h_msg, WGL_CMD_TEXT_SET_TEXT, (VOID*)w2s_string, (VOID*)z_len);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_view_activate
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_ULPK_VIEW_T* pt_view        = &t_g_nav_ulpk_view;
    INT32             i4_ret;
    NAV_ULPK_STATE_ID_T t_ulpk_state = NAV_ULPK_STATE_ID_NONE;
    nav_get_ulpk_state(&t_ulpk_state);
    i4_ret = _nav_ulpk_view_show(pt_view, t_ulpk_state);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
    
    i4_ret = c_wgl_set_focus(pt_view->h_frame, WGL_NO_AUTO_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#if 0
    nav_ulpk_reset_timer(pt_view->pt_ctrl, ULPK_TIMEOUT);   
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_view_hide(
                    VOID
                    )
{
    NAV_ULPK_VIEW_T* pt_view = &t_g_nav_ulpk_view;
    INT32             i4_ret;

    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_view_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_ulpk_view_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    switch(ui4_key_code) {
    case BTN_RED:
        {
            NAV_ULPK_STATE_ID_T t_ulpk_state = NAV_ULPK_STATE_ID_NONE;
            nav_get_ulpk_state(&t_ulpk_state);
            if (NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL == t_ulpk_state)
            {
                NAV_ULPK_USB_STATE_ID_T t_usb_state = NAV_ULPK_USB_STATE_ID_NONE;
                nav_get_usb_state(&t_usb_state);
                if (NAV_ULPK_USB_STATE_ID_IN == t_usb_state)
                {
                    nav_set_ulpk_state(NAV_ULPK_STATE_ID_INSTALL_ULPK); 
                    nav_return_activation(NAV_COMP_ID_ULPK);
                    nav_hide_component(NAV_COMP_ID_ULPK); 
                    nav_ulpk_activate(NULL,BTN_RED);
                    nav_ulpk_install_process();
                }
                else if (NAV_ULPK_USB_STATE_ID_OUT == t_usb_state)
                {
                    nav_set_ulpk_state(NAV_ULPK_STATE_ID_PLUG_USB_STICK); 
                    nav_return_activation(NAV_COMP_ID_ULPK);
                    nav_hide_component(NAV_COMP_ID_ULPK); 
                    nav_ulpk_activate(NULL,BTN_RED);
                }
                else
                {
                    /* do nothing*/
                }
            }
            break;
        }
    default:
        nav_set_ulpk_state(NAV_ULPK_STATE_ID_NONE);
        nav_rcu_key_handler(ui4_key_code);
        break;
    }
}
/*---------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_view_frame_nfy_fct(
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_view_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:
        _nav_ulpk_view_rcu_key_handler((UINT32)pv_param1);  /* key code */
        break;
    default:
        break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _screen_mode_view_set_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_view_set_skin(
                    NAV_ULPK_VIEW_T*           pt_view
                    )
{
    WGL_COLOR_INFO_T t_clr_info;
    WGL_IMG_INFO_T   t_img_info;
    WGL_INSET_T      t_inset;
    INT32            i4_ret;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->t_rc.h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->t_rc.h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->t_rc.h_img_bk;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frame,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set message color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_standard.t_enable    = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_standard.t_highlight = pt_view->t_rc.t_msg_fg;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set msg font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)pt_view->t_rc.pt_msg_font,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    
    
    /* set event title inset */
    t_inset.i4_left   = ULPK_MSG_LEFT_INSET;
    t_inset.i4_right  = ULPK_MSG_RIGHT_INSET;
    t_inset.i4_top    = ULPK_MSG_TOP_INSET;
    t_inset.i4_bottom = ULPK_MSG_BOTTOM_INSET;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg,
                    WGL_CMD_TEXT_SET_CNT_INSET,
                    (VOID*)&t_inset,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set title align */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)ULPK_MSG_ALIGNMENT,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_view_init(
                    NAV_ULPK_T*                pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset
                    )
{
    NAV_ULPK_VIEW_T* pt_view = &t_g_nav_ulpk_view;
    GL_RECT_T         t_rect;
    INT32             i4_ret;

    pt_view->pt_ctrl = pt_ctrl;

    i4_ret = ulpk_view_init_rc(&pt_view->t_rc);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* create frame */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    100,
                    100,
                    620,
                    160
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _nav_ulpk_view_frame_nfy_fct,
                    DEFAULT_BK_ALPHA,
                    NULL,
                    NULL,
                    &pt_view->h_frame
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* create text */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    0,
                    0,
                    620,
                    160
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_512|WGL_STL_TEXT_MULTILINE|WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_msg
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = _nav_ulpk_view_set_skin(pt_view);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_show(pt_view->h_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }


    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_view_deinit(
                    VOID
                    )
{
    NAV_ULPK_VIEW_T* pt_view = &t_g_nav_ulpk_view;

    c_wgl_destroy_widget(pt_view->h_frame);
    c_wgl_destroy_widget(pt_view->h_msg);
    ulpk_view_deinit_rc(&pt_view->t_rc);

    pt_view->pt_ctrl  = NULL;
    pt_view->h_frame  = NULL_HANDLE;
    pt_view->h_msg    = NULL_HANDLE;
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ulpk_view_register_default_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ulpk_view_register_default_hdlr(
                    NAV_ULPK_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_ulpk_view_init;
    pt_view_hdlr->pf_deinit         = _nav_ulpk_view_deinit;
    pt_view_hdlr->pf_is_key_handler = _nav_ulpk_view_is_key_handler;
    pt_view_hdlr->pf_activate       = _nav_ulpk_view_activate;
    pt_view_hdlr->pf_hide           = _nav_ulpk_view_hide;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
#endif
#endif
