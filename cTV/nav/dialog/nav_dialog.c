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
 * $RCSfile: clock.c,v $
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
#ifdef APP_537X_SUPPORT

#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_handle.h"
#include "c_wgl.h"

#include "nav/a_navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"

#include "nav/dialog/nav_dialog.h"
#include "nav/dialog/a_nav_dialog.h"
#include "res/nav/dialog/nav_dialog_config.h"

/* view */
#include "app_util/a_ui.h"
#include "app_util/a_tv.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef struct
{
    HANDLE_T        h_canvas;
    HANDLE_T        h_dialog;
    HANDLE_T        h_yes_no_dialog;
    HANDLE_T        h_hide_timer;
    UINT32          ui4_timer_delay;
    NAV_DIALOG_ID_T e_dialog_id;
}   NAV_DIALOG_T;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_DIALOG_T t_g_nav_dialog;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_hide_timer_start(
    UINT32    ui4_time);

static INT32 _nav_dialog_hide_timer_stop(
    VOID);

static VOID _nav_dialog_hide_timer_nfy (
    HANDLE_T  h_timer,
    VOID*     pv_tag);

static VOID _nav_dialog_timeout_to_hide(
    VOID*     pv_tag,
    VOID*     pv_tag2,
    VOID*     pv_tag3);

static INT32 _nav_dialog_hide(VOID);


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    c_memset(&t_g_nav_dialog, 0, sizeof(NAV_DIALOG_T));

    t_g_nav_dialog.h_canvas = pt_ctx->t_gui_res.h_canvas;
    t_g_nav_dialog.ui4_timer_delay = NAV_DIALOG_DEFAULT_TIMER_DELAY;

    c_timer_create(&t_g_nav_dialog.h_hide_timer);

    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;

    /* Create the dialog */
    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = t_g_nav_dialog.h_canvas;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = FALSE;
    t_simple_dialog_init.pf_ui_simple_dialog_tts_cb_fct = a_ui_simple_dialog_default_tts_cb_fct;

    NAV_CHK_FAIL(a_ui_simple_dialog_create(&t_simple_dialog_init,
                                           &t_g_nav_dialog.h_yes_no_dialog));

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_deinit(VOID)
{
    NAV_DIALOG_T* pt_this = &t_g_nav_dialog;

    if (NULL_HANDLE != pt_this->h_hide_timer)
    {
        c_timer_delete(pt_this->h_hide_timer);
    }

    if (NULL_HANDLE != pt_this->h_dialog)
    {
        a_ui_simple_dialog_destory(pt_this->h_dialog);
    }
    if (NULL_HANDLE != pt_this->h_yes_no_dialog)
    {
        a_ui_simple_dialog_destory(pt_this->h_yes_no_dialog);
    }

    c_memset(&t_g_nav_dialog, 0, sizeof(NAV_DIALOG_T));

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_dialog_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    if(t_g_nav_dialog.h_yes_no_dialog != NULL_HANDLE)
    {
        DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
        a_ui_simple_dialog_set_focus(t_g_nav_dialog.h_yes_no_dialog,FALSE);
        c_wgl_float(t_g_nav_dialog.h_yes_no_dialog, TRUE, FALSE);
        a_ui_simple_dialog_show(t_g_nav_dialog.h_yes_no_dialog);
    }

    nav_set_component_visible(NAV_COMP_ID_DIALOG);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_handle_msg(
                                          NAV_CONTEXT_T*              pt_ctx,
                                          NAV_UI_MSG_T*               pt_ui_msg,
                                          VOID*                       pv_arg1)
{
    if(pt_ui_msg->e_id == NAV_UI_MSG_REST_NOTIFICATION)
    {
        NAV_DIALOG_INIT_T* pt_init = (NAV_DIALOG_INIT_T*)pv_arg1;
        if(pt_init)
        {
            /* show dialog */
            NAV_LOG_ON_FAIL(nav_dialog_prompt_yes_no_dialog_ex(pt_init->e_id,
                                                               pt_init->p_msg_txt,
                                                               pt_init->p_yes_txt,
                                                               pt_init->p_no_txt,
                                                               pt_init->e_style,
                                                               pt_init->ui2_txt_align_type,
                                                               pt_init->pt_begin_offset,
                                                               pt_init->b_default_answer,
                                                               pt_init->pf_wdgt_proc,
                                                               pt_init->pf_ui_simple_dialog_yes_cb_fct,
                                                               pt_init->pf_ui_simple_dialog_no_cb_fct,
                                                               pt_init->pf_ui_simple_dialog_tts_cb_fct,
                                                               &pt_init->ui4_timeout));
            c_mem_free(pt_init);
            pt_init = NULL;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_hide(VOID)
{
    NAV_DIALOG_T*   pt_this = &t_g_nav_dialog;

    if(pt_this->h_dialog != NULL_HANDLE)
        a_ui_simple_dialog_hide(pt_this->h_dialog);

    if(pt_this->h_yes_no_dialog != NULL_HANDLE)
        a_ui_simple_dialog_hide(pt_this->h_yes_no_dialog);

    /* stop the timer */
    _nav_dialog_hide_timer_stop();

    /* Return activation */
    nav_return_activation(NAV_COMP_ID_DIALOG);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_hide_timer_start
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_hide_timer_start(
    UINT32    ui4_time)
{
    c_timer_start(t_g_nav_dialog.h_hide_timer,
                  ui4_time,
                  X_TIMER_FLAG_ONCE,
                  _nav_dialog_hide_timer_nfy,
                  NULL);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_hide_timer_stop
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_dialog_hide_timer_stop(VOID)
{
    c_timer_stop(t_g_nav_dialog.h_hide_timer);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_dialog_hide_timer_nfy (
    HANDLE_T  h_timer,
    VOID*     pv_tag)
{
    nav_request_context_switch(_nav_dialog_timeout_to_hide,
                               NULL,
                               NULL,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dialog_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_dialog_timeout_to_hide(
    VOID*                       pv_tag,
    VOID*                       pv_tag2,
    VOID*                       pv_tag3)
{
    NAV_DIALOG_T*   pt_this = &t_g_nav_dialog;
    if(pt_this->e_dialog_id != NAV_DIALOG_ID_NULL)
    {
        nav_dialog_hide();
    }
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_prompt_yes_no_dialog
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern INT32 nav_dialog_prompt_yes_no_dialog(
    NAV_DIALOG_ID_T              e_dialog_id,
    UTF16_T*                     pw2s_msg,
    UTF16_T*                     pw2s_yes,
    UTF16_T*                     pw2s_no,
    wgl_widget_proc_fct          pf_wdgt_proc,
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct,
    ui_simple_dialog_no_cb_fct   pf_ui_simple_dialog_no_cb_fct)
{
    return nav_dialog_prompt_yes_no_dialog_ex(
        e_dialog_id,
        pw2s_msg,
        pw2s_yes,
        pw2s_no,
        UI_SIMPLE_DIALOG_STYLE_SMALL,
        WGL_AS_CENTER_CENTER,
        NULL,
        TRUE,
        pf_wdgt_proc,
        pf_ui_simple_dialog_yes_cb_fct,
        pf_ui_simple_dialog_no_cb_fct,
        NULL,
        NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_prompt_yes_no_dialog_ex
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern INT32 nav_dialog_prompt_yes_no_dialog_ex(
    NAV_DIALOG_ID_T              e_dialog_id,
    UTF16_T*                     pw2s_msg,
    UTF16_T*                     pw2s_yes,
    UTF16_T*                     pw2s_no,
    UI_SIMPLE_DIALOG_STYLE_T     e_style,
    UINT16                       ui2_txt_align_type,
    GL_POINT_T*                  pt_begin_offset,
    BOOL                         b_default_answer,
    wgl_widget_proc_fct          pf_wdgt_proc,
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct,
    ui_simple_dialog_no_cb_fct   pf_ui_simple_dialog_no_cb_fct,
    ui_simple_dialog_tts_cb_fct  pf_ui_simple_dialog_tts_cb_fct,
    UINT32*                      pui4_timeout)
{
    NAV_DIALOG_T*               pt_this = &t_g_nav_dialog;

    /* Hide the previous */
    BOOL b_1st_visibile = FALSE;
    c_wgl_get_visibility(pt_this->h_yes_no_dialog,&b_1st_visibile);
    if(b_1st_visibile)
        a_ui_simple_dialog_hide(pt_this->h_yes_no_dialog);

    pt_this->e_dialog_id = e_dialog_id;

    /* Modify the attribute */
    NAV_CHK_FAIL(a_ui_simple_dialog_set_offset(pt_this->h_yes_no_dialog,NULL,pt_begin_offset,e_style));
    NAV_CHK_FAIL(a_ui_simple_dialog_set_text(pt_this->h_yes_no_dialog, pw2s_msg));
    NAV_CHK_FAIL(a_ui_simple_dialog_set_yes_text(pt_this->h_yes_no_dialog, pw2s_yes));
    NAV_CHK_FAIL(a_ui_simple_dialog_set_no_text(pt_this->h_yes_no_dialog, pw2s_no));
    NAV_CHK_FAIL(a_ui_simple_dialog_set_tts_fct(pt_this->h_yes_no_dialog, pf_ui_simple_dialog_tts_cb_fct));
    NAV_CHK_FAIL(a_ui_simple_dialog_set_yes_fct(pt_this->h_yes_no_dialog,pf_ui_simple_dialog_yes_cb_fct));
    NAV_CHK_FAIL(a_ui_simple_dialog_set_no_fct(pt_this->h_yes_no_dialog,pf_ui_simple_dialog_no_cb_fct));
    NAV_CHK_FAIL(a_ui_simple_dialog_set_answer_ex(pt_this->h_yes_no_dialog, b_default_answer));
    NAV_CHK_FAIL(a_ui_simple_dialog_set_default_msg_proc(pt_this->h_yes_no_dialog,pf_wdgt_proc));

    nav_grab_activation(NAV_COMP_ID_DIALOG);

    /* restart the timer */
    t_g_nav_dialog.ui4_timer_delay = (pui4_timeout && *pui4_timeout > 0) ? *pui4_timeout : NAV_DIALOG_DEFAULT_TIMER_DELAY;
    _nav_dialog_hide_timer_start(t_g_nav_dialog.ui4_timer_delay);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_prompt_msg_dialog
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern INT32 nav_dialog_prompt_msg_dialog(
    NAV_DIALOG_ID_T     e_dialog_id,
    UTF16_T*            pw2s_msg,
    UTF16_T*            pw2s_yes,
    GL_POINT_T*         pt_begin_offset,
    wgl_widget_proc_fct pf_wdgt_proc,
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct)
{
    return nav_dialog_prompt_msg_dialog_ex(e_dialog_id,
                                           pw2s_msg,
                                           pw2s_yes,
                                           NULL,
                                           pt_begin_offset,
                                           pf_wdgt_proc,
                                           pf_ui_simple_dialog_yes_cb_fct);
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_prompt_msg_dialog_ex
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern INT32 nav_dialog_prompt_msg_dialog_ex(
    NAV_DIALOG_ID_T     e_dialog_id,
    UTF16_T*            pw2s_msg,
    UTF16_T*            pw2s_yes,
    GL_RECT_T*          pt_rect,
    GL_POINT_T*         pt_begin_offset,
    wgl_widget_proc_fct pf_wdgt_proc,
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct)
{
    INT32                       i4_ret;
    NAV_DIALOG_T*               pt_this = &t_g_nav_dialog;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;

    /* Hide the previous */
    if(pt_this->e_dialog_id != NAV_DIALOG_ID_NULL &&
       pt_this->e_dialog_id != e_dialog_id)
    {
        a_ui_simple_dialog_destory(pt_this->h_dialog);
        pt_this->e_dialog_id = NAV_DIALOG_ID_NULL;
        pt_this->h_dialog    = NULL_HANDLE;
    }

    /* Create the dialog */
    if(pt_this->e_dialog_id != e_dialog_id)
    {
        c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

        t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
        t_simple_dialog_init.h_parent                       = pt_this->h_canvas;
        t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
        t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = pf_ui_simple_dialog_yes_cb_fct;
        t_simple_dialog_init.pf_wdgt_proc                   = pf_wdgt_proc;
        t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
        t_simple_dialog_init.pt_rect                        = pt_rect;
        t_simple_dialog_init.b_one_btn_mode                 = TRUE;
        t_simple_dialog_init.pt_begin_offset                = pt_begin_offset;

        i4_ret = a_ui_simple_dialog_create(
                                &t_simple_dialog_init,
                                &pt_this->h_dialog);
        if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}

        pt_this->e_dialog_id = e_dialog_id;
    }

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dialog, pw2s_msg);
    if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_dialog, pw2s_yes);
    if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}

    /* If the Dialog component is not active componet, Grab activation.
       Otherwise, set focus to current dialog*/
    if(nav_get_active_component() != NAV_COMP_ID_DIALOG)
    {
        nav_grab_activation(NAV_COMP_ID_DIALOG);
    }
    else
    {
        a_ui_simple_dialog_set_focus(pt_this->h_dialog, FALSE);

        a_ui_simple_dialog_show(pt_this->h_dialog);

        c_wgl_repaint(pt_this->h_dialog, NULL, TRUE);
    }

    /* restart the timer */
    t_g_nav_dialog.ui4_timer_delay = NAV_DIALOG_DEFAULT_TIMER_DELAY;
    _nav_dialog_hide_timer_start(t_g_nav_dialog.ui4_timer_delay);

    return NAVR_OK;
}
#ifdef APP_ARC_ONLY
/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_prompt_only_msg_dialog
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_dialog_prompt_only_msg_dialog(
    NAV_DIALOG_ID_T     e_dialog_id,
    UTF16_T*            pw2s_msg,
    GL_RECT_T*          pt_rect,
    GL_POINT_T*         pt_begin_offset,
    wgl_widget_proc_fct pf_wdgt_proc)
{
    INT32                       i4_ret;
    NAV_DIALOG_T*               pt_this = &t_g_nav_dialog;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    GL_RECT_T                  				t_rect;

    /* Hide the previous */
    if(pt_this->e_dialog_id != NAV_DIALOG_ID_NULL &&
       pt_this->e_dialog_id != e_dialog_id)
    {
        a_ui_simple_dialog_destory(pt_this->h_dialog);
        pt_this->e_dialog_id = NAV_DIALOG_ID_NULL;
        pt_this->h_dialog    = NULL_HANDLE;
    }

    /* Create the dialog */
    if(pt_this->e_dialog_id != e_dialog_id)
    {
        c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

        t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY;
        t_simple_dialog_init.h_parent                       = pt_this->h_canvas;
        t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
        //t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = pf_ui_simple_dialog_yes_cb_fct;
        t_simple_dialog_init.pf_wdgt_proc                   = pf_wdgt_proc;
        t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
        t_simple_dialog_init.pt_rect                        = pt_rect;
        t_simple_dialog_init.b_one_btn_mode                 = FALSE;
        t_simple_dialog_init.pt_begin_offset                = pt_begin_offset;

		SET_RECT_BY_SIZE(&t_rect,
						 NAV_DIALOG_ONLY_MSG_FRM_X,
						 NAV_DIALOG_ONLY_MSG_FRM_Y,
						 NAV_DIALOG_ONLY_MSG_FRM_W,
						 NAV_DIALOG_ONLY_MSG_FRM_H);

		t_simple_dialog_init.pt_rect			= &t_rect;

        i4_ret = a_ui_simple_dialog_create(
                                &t_simple_dialog_init,
                                &pt_this->h_dialog);
        if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}

        pt_this->e_dialog_id = e_dialog_id;
    }

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dialog, pw2s_msg);
    if(i4_ret != APP_UIR_OK){return NAVR_FAIL;}

    /* If the Dialog component is not active componet, Grab activation.
       Otherwise, set focus to current dialog*/
    if(nav_get_active_component() != NAV_COMP_ID_DIALOG)
    {
        nav_grab_activation(NAV_COMP_ID_DIALOG);
    }
    else
    {
        a_ui_simple_dialog_set_focus(pt_this->h_dialog, FALSE);

        a_ui_simple_dialog_show(pt_this->h_dialog);

        c_wgl_repaint(pt_this->h_dialog, NULL, TRUE);
    }

    /* restart the timer */
    t_g_nav_dialog.ui4_timer_delay = NAV_DIALOG_DEFAULT_TIMER_DELAY;
    _nav_dialog_hide_timer_start(t_g_nav_dialog.ui4_timer_delay);

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern INT32 nav_dialog_hide(VOID)
{
    nav_hide_component(NAV_COMP_ID_DIALOG);
    /* Return control. */
    nav_return_activation(NAV_COMP_ID_DIALOG);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_set_hide_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern INT32 nav_dialog_set_hide_timer(
    UINT32  ui4_time)
{
    NAV_DIALOG_T*   pt_this = &t_g_nav_dialog;

    pt_this->ui4_timer_delay = ui4_time;

    if(pt_this->e_dialog_id != NAV_DIALOG_ID_NULL)
    {
        _nav_dialog_hide_timer_start(ui4_time);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      nav_dialog_stop_hide_timer
 * Description:
 *
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
extern INT32 nav_dialog_stop_hide_timer(VOID)
{
    NAV_DIALOG_T*   pt_this = &t_g_nav_dialog;
    INT32           i4_ret = NAVR_OK;

    if(NULL_HANDLE != pt_this->h_hide_timer)
    {
        i4_ret = c_timer_stop(pt_this->h_hide_timer);
        if(i4_ret != OSR_OK){return NAVR_FAIL;}
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_default_msg_proc
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern INT32 nav_dialog_default_msg_proc(
    HANDLE_T            h_widget,
    UINT32              ui4_msg,
    VOID*               pv_param1,
    VOID*               pv_param2)
{
    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            _nav_dialog_hide_timer_start(t_g_nav_dialog.ui4_timer_delay);

            switch(ui4_keycode)
            {
            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            case BTN_SELECT:
                break;

            case BTN_EXIT:
                nav_dialog_hide();
                break;
            default:
                nav_rcu_key_handler(ui4_keycode);
                return WGLR_OK;
            }
            break;
        }

        default:
            break;
    }

    return a_ui_simple_dialog_default_msg_proc(h_widget,
                                               ui4_msg,
                                               pv_param1,
                                               pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_dialog_get_crnt_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern NAV_DIALOG_ID_T nav_dialog_get_crnt_id(VOID)
{
    NAV_DIALOG_T*   pt_this = &t_g_nav_dialog;

    return pt_this->e_dialog_id;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_dialog_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_dialog_register(VOID)
{
    NAV_COMP_T      t_comp;
    INT32           i4_ret;

    /* NAV_COMP_ID_DIALOG */
    c_memset (& t_comp, 0, sizeof(NAV_COMP_T));
    t_comp.pf_init           = _nav_dialog_init;
    t_comp.pf_deinit         = _nav_dialog_deinit;
    t_comp.pf_is_key_handler = _nav_dialog_is_key_handler;
    t_comp.pf_activate       = _nav_dialog_activate;
    t_comp.pf_inactivate     = _nav_dialog_inactivate;
    t_comp.pf_hide           = _nav_dialog_hide;
    t_comp.pf_handle_msg     = _nav_dialog_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_DIALOG, &t_comp, COMP_EXEC_SET_DIALOG);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return NAVR_OK;
}

#endif /* APP_537X_SUPPORT */

