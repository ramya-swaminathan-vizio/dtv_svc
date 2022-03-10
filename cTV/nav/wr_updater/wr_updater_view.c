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

#ifdef APP_WR_UPDATER_UI_SUPPORT
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

#include "nav/wr_updater/wr_updater.h"
#include "nav/nav_common.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "app_util/a_ui.h"
#include "res/app_util/ui/ui_custom.h"
#include "res/nav/nav_dbg.h"


/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define NAV_WR_UPDATER_MAIN_FRM_X          (0)
#define NAV_WR_UPDATER_MAIN_FRM_Y          (0)
#define NAV_WR_UPDATER_MAIN_FRM_W          (1280)
#define NAV_WR_UPDATER_MAIN_FRM_H          (720)

#define IS_SYNC_REPAINT                     TRUE

typedef struct _NAV_WR_UPDATER_VIEW_T
{
    NAV_WR_UPDATER_T*                pt_ctrl;
    HANDLE_T                         h_frame;
    HANDLE_T                         h_dialog_start_up;
    HANDLE_T                         h_dialog_msg;
} NAV_WR_UPDATER_VIEW_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_WR_UPDATER_VIEW_T t_g_nav_wr_updater_view = {0};

extern INT32 nav_view_set_focus(VOID);

static INT32 _nav_wr_updater_view_hide(
                    VOID
                    );


/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_view_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_wr_updater_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
#if 0
    switch (ui4_key_code) {
    case BTN_RED:
        return TRUE;
    default:
        return FALSE;
    }
#endif
    return FALSE;

}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_view_show
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_view_show(
                    NAV_WR_UPDATER_VIEW_T*           pt_view,
                    NAV_WR_UI_STATE_ID_T             t_wr_ui_state
                    )
{
    INT32    i4_ret;

    DBG_LOG_PRINT( ("\nxxx=== the current ui status of wr updater is %d, and show the ui about it !!====xxxxx\n"));

    switch (t_wr_ui_state)
    {
        case NAV_WR_UI_STATE_ID_NONE:
            _nav_wr_updater_view_hide();
            break;
        case NAV_WR_UI_STATE_ID_START_SETUP:
            {
                /* Modify the attribute */
                i4_ret = a_ui_simple_dialog_set_text(pt_view->h_dialog_start_up, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_UPDATE_FW_AND_WIFI_REMOTE));
                if(i4_ret != APP_UIR_OK){
                    return NAVR_FAIL;
                }

                i4_ret = a_ui_simple_dialog_set_yes_text(pt_view->h_dialog_start_up, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_BTN_SETUP));
                if(i4_ret != APP_UIR_OK){
                    return NAVR_FAIL;
                }

                a_ui_simple_dialog_hide(pt_view->h_dialog_msg);
                a_ui_simple_dialog_show(pt_view->h_dialog_start_up);
                a_ui_simple_dialog_set_focus(pt_view->h_dialog_start_up, FALSE);


                i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_NORMAL);
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }

                i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }

                break;
            }
        case NAV_WR_UI_STATE_ID_WR_UPDATER_RUNNING:
            _nav_wr_updater_view_hide();
            break;
        case NAV_WR_UI_STATE_ID_RESULT:
        case NAV_WR_UI_STATE_ID_WR_UPDATER_SUCCESSFUL:
            {
                /* Modify the attribute */
                i4_ret = a_ui_simple_dialog_set_text(pt_view->h_dialog_msg, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_REMOTE_UPDATED));
                if(i4_ret != APP_UIR_OK){
                    return NAVR_FAIL;
                }

                a_ui_simple_dialog_hide(pt_view->h_dialog_start_up);
                a_ui_simple_dialog_show(pt_view->h_dialog_msg);

                /* Let's focus on the frame */
                i4_ret = c_wgl_set_focus(pt_view->h_frame, WGL_NO_AUTO_REPAINT);
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }

                i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_NORMAL);
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }

                i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }

            }
            break;
        default:
            _nav_wr_updater_view_hide();
            break;
    }
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 * _nav_wr_updater_view_activate
 * Description
 * Input arguments
 * Output arguments
 * None
 * Returns
 * None
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    NAV_WR_UPDATER_VIEW_T* pt_view        = &t_g_nav_wr_updater_view;
    INT32                  i4_ret;
    NAV_WR_UI_STATE_ID_T   t_wr_ui_state   = NAV_WR_UI_STATE_ID_NONE;
    nav_get_wr_updater_state(&t_wr_ui_state);

    if (NAV_WR_UI_STATE_ID_NONE == t_wr_ui_state)
    {
        t_wr_ui_state   = NAV_WR_UI_STATE_ID_START_SETUP;
    }
    else if (NAV_WR_UI_STATE_ID_START_SETUP == t_wr_ui_state)
    {
        t_wr_ui_state   = NAV_WR_UI_STATE_ID_WR_UPDATER_RUNNING;
    }
    else if (NAV_WR_UI_STATE_ID_WR_UPDATER_RUNNING == t_wr_ui_state)
    {
        t_wr_ui_state   = NAV_WR_UI_STATE_ID_RESULT;
    }
    else if (NAV_WR_UI_STATE_ID_WR_UPDATER_SUCCESSFUL == t_wr_ui_state)
    {
        t_wr_ui_state   = NAV_WR_UI_STATE_ID_WR_UPDATER_SUCCESSFUL;
    }
    else
    {
        return NAVR_FAIL;
    }

    nav_set_wr_updater_state(t_wr_ui_state);

    i4_ret = _nav_wr_updater_view_show(pt_view, t_wr_ui_state);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_view_hide(
                    VOID
                    )
{
    NAV_WR_UPDATER_VIEW_T* pt_view = &t_g_nav_wr_updater_view;
    INT32             i4_ret;

    a_ui_simple_dialog_hide(pt_view->h_dialog_start_up);
    a_ui_simple_dialog_hide(pt_view->h_dialog_msg);


    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    nav_view_set_focus();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_view_dialog_start_setup_action
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_wr_updater_view_dialog_start_setup_action(VOID)
{
    /**
        * 1. stop the hide time;
        * 2. jump to the wzd wifi pair page;
        */
    nav_wr_updater_start_setup();
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_nfy_frm
 * Description
 *      Retail mode frame key handler callback function.
 * Input arguments
 *      HANDLE_T        Frame handle
 *      UINT32          message
 *      VOID*           argument
 *      VOID*           argument
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Success
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_nfy_frm(
                    HANDLE_T       h_widget,
                    UINT32         ui4_msg,
                    VOID*          pv_param1,
                    VOID*          pv_param2
                    )
{
    UINT32          ui4_key_code;

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        ui4_key_code = (UINT32)pv_param1;

        switch (ui4_key_code)
        {
            default:
                nav_rcu_key_handler(ui4_key_code);
                break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name
 * _nav_wr_updater_view_frame_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_view_frame_create(HANDLE_T  h_canvas)
{
    NAV_WR_UPDATER_VIEW_T*          pt_view = &t_g_nav_wr_updater_view;
    GL_RECT_T                       t_rect;
    INT32                           i4_ret;

    /* Create main frame */
    SET_RECT_BY_SIZE(&t_rect,
                     NAV_WR_UPDATER_MAIN_FRM_X,
                     NAV_WR_UPDATER_MAIN_FRM_Y,
                     NAV_WR_UPDATER_MAIN_FRM_W,
                     NAV_WR_UPDATER_MAIN_FRM_H);

    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_wr_updater_nfy_frm,
                                 DEFAULT_BK_ALPHA,
                                 (VOID*)NULL,
                                 (VOID*)NULL,
                                 &pt_view->h_frame);
    if (WGLR_OK != i4_ret)
    {
        DBG_ERROR(("<wr_updater> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return NAVR_FAIL;
    }
    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_view_start_setup_dialog_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_view_start_setup_dialog_create(HANDLE_T  h_canvas)
{
    NAV_WR_UPDATER_VIEW_T*          pt_view = &t_g_nav_wr_updater_view;
    UI_SIMPLE_DIALOG_INIT_T         t_simple_dialog_init;
    INT32                           i4_ret;
    GL_POINT_T                      t_offset = {-55, 0};
    GL_RECT_T                       t_rect = {0};

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = h_canvas;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _nav_wr_updater_view_dialog_start_setup_action;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;

    a_ui_simple_dialog_create(&t_simple_dialog_init,
                                  &pt_view->h_dialog_start_up);

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_view->h_dialog_start_up, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_UPDATE_FW_AND_WIFI_REMOTE));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_view->h_dialog_start_up, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_BTN_SETUP));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     (UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W - UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W)/2,
                     UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_Y - 20,
                     UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W,
                     UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_H);

    a_ui_simple_dialog_set_yes_no_rect(pt_view->h_dialog_start_up,
                                        TRUE,
                                        &t_rect,
                                        FALSE);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_view_msg_dialog_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_view_msg_dialog_create(HANDLE_T  h_canvas)
{
    NAV_WR_UPDATER_VIEW_T*          pt_view = &t_g_nav_wr_updater_view;
    UI_SIMPLE_DIALOG_INIT_T         t_simple_dialog_init;
    INT32                           i4_ret;
    GL_POINT_T                      t_offset = {-55, 0};

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_WARNING_MSG;
    t_simple_dialog_init.h_parent                       = h_canvas;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = NULL;
    t_simple_dialog_init.pf_wdgt_proc                   = NULL;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;

    a_ui_simple_dialog_create(&t_simple_dialog_init,
                                  &pt_view->h_dialog_msg);

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_view->h_dialog_msg, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_REMOTE_UPDATED));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_view_init(
                    NAV_WR_UPDATER_T*                 pt_ctrl,
                    HANDLE_T                          h_canvas,
                    INT32                             i4_frame_x_offset,
                    INT32                             i4_frame_y_offset
                    )
{
    NAV_WR_UPDATER_VIEW_T*  pt_view = &t_g_nav_wr_updater_view;
    INT32                   i4_ret;

    pt_view->pt_ctrl = pt_ctrl;

    i4_ret = _nav_wr_updater_view_frame_create(h_canvas);
    if (NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT( ("\n[NAV_WR_UPDATER]_nav_wr_updater_view_frame_create() fail !!\n"));
        return i4_ret;
    }

    i4_ret = _nav_wr_updater_view_start_setup_dialog_create(pt_view->h_frame);
    if (NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT( ("\n[NAV_WR_UPDATER]_nav_wr_updater_view_start_setup_dialog_create() fail !!\n"));
        return i4_ret;
    }

    i4_ret = _nav_wr_updater_view_msg_dialog_create(pt_view->h_frame);

    if (NAVR_OK != i4_ret)
    {
        DBG_LOG_PRINT( ("\n[NAV_WR_UPDATER]_nav_wr_updater_view_msg_dialog_create() fail !!\n"));
        return i4_ret;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_wr_updater_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_wr_updater_view_deinit(
                    VOID
                    )
{
    NAV_WR_UPDATER_VIEW_T* pt_view = &t_g_nav_wr_updater_view;

    c_wgl_destroy_widget(pt_view->h_frame);
    a_ui_simple_dialog_destory(pt_view->h_dialog_start_up);
    a_ui_simple_dialog_destory(pt_view->h_dialog_msg);

    pt_view->pt_ctrl              = NULL;
    pt_view->h_frame              = NULL_HANDLE;
    pt_view->h_dialog_start_up    = NULL_HANDLE;
    pt_view->h_dialog_msg         = NULL_HANDLE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_wr_updater_view_register_default_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_wr_updater_view_register_default_hdlr(
                    NAV_WR_UPDATER_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_wr_updater_view_init;
    pt_view_hdlr->pf_deinit         = _nav_wr_updater_view_deinit;
    pt_view_hdlr->pf_is_key_handler = _nav_wr_updater_view_is_key_handler;
    pt_view_hdlr->pf_activate       = _nav_wr_updater_view_activate;
    pt_view_hdlr->pf_hide           = _nav_wr_updater_view_hide;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
#endif
#endif
