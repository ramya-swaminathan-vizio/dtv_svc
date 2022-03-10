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
 * $RCSfile: nav_dialog.c,v $
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

#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_handle.h"
#include "c_wgl.h"

#include "nav/a_navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_mlm.h"

#include "nav/viewport/nav_viewport.h"
#include "nav/viewport/a_nav_viewport.h"

/* view */
#include "app_util/a_ui.h"
#include "app_util/a_tv.h"

#include "app_util/a_icl.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#ifdef VIEWPORT_SUPPORT

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define _VIEWPORT_DISPLAY_STATUS_CHANGE_TIMEOUT (5000)
#define VIEWPORT_MSG_TIMEOUT                    (3000)

typedef struct
{
    HANDLE_T        h_canvas;
    HANDLE_T        h_viewport_msg;
    HANDLE_T        h_hide_timer;
    BOOL            b_is_show;
    UINT16          ui2_icl_nfy;
}   NAV_VIEWPORT_T;

#define RET_ON_ERR(_expr)  \
{ \
INT32 expr = _expr; \
if(expr != 0)\
{\
    DBG_ERROR (("<NAV_VIEWPORT> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
    return expr;\
} \
}

#define LOG_ON_ERR(_expr)  \
if(_expr != 0)\
{\
    DBG_ERROR (("<NAV_VIEWPORT> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
}

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_VIEWPORT_T t_g_nav_viewport = {0};
static BOOL           b_is_create = FALSE;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32  _nav_viewport_show_msg_nfy(UINT16  ui2_nfy_id,
                                        VOID*   pv_tag,
                                        ICL_NOTIFY_DATA_T*  pt_notify_data);
static INT32 _nav_viewport_msg_hide(VOID);
static INT32 _nav_viewport_msg_show(VOID);
static INT32 _nav_viewport_hide_timer_start(VOID);
static VOID  _nav_viewport_hide_timer_nfy (
                        HANDLE_T        h_timer,
                        VOID*           pv_tag);
static VOID _nav_viewport_reset_hide_timer(VOID);
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_init
 * Description:
 *      
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_viewport_init(NAV_CONTEXT_T*        pt_ctx)
{
    NAV_VIEWPORT_T*            pt_this = &t_g_nav_viewport;    
    INT32                      i4_ret = NAVR_OK;
    
    c_memset(&t_g_nav_viewport, 0, sizeof(NAV_VIEWPORT_T));

    pt_this->h_canvas = pt_ctx->t_gui_res.h_canvas;
    pt_this->b_is_show = FALSE;

    i4_ret = c_timer_create(&pt_this->h_hide_timer);
    RET_ON_ERR(i4_ret);
    
    i4_ret = a_icl_notify_reg(ICL_GRPID_VIEWPORT,
                              ICL_RECID_VIEWPORT_LAST_REQ_STS,
                              NULL,
                              NULL,
                              _nav_viewport_show_msg_nfy,
                              &pt_this->ui2_icl_nfy); 

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_deinit
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
static INT32 _nav_viewport_deinit(VOID)
{
    NAV_VIEWPORT_T* pt_this = &t_g_nav_viewport;
    INT32           i4_ret = NAVR_OK;

    if (NULL_HANDLE != pt_this->h_viewport_msg)
    {
        i4_ret = a_ui_simple_dialog_destory(pt_this->h_viewport_msg);
        RET_ON_ERR(i4_ret);
    }

    c_memset(&t_g_nav_viewport, 0, sizeof(NAV_VIEWPORT_T));

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_is_key_handler
 * Description:
 *
 * Input arguments:
 *      pt_ctx
 *      ui4_key_code
 * Output arguments:
 *      None
 * Returns:
 *      FALSE
 *      TRUE
 *---------------------------------------------------------------------------*/
static BOOL _nav_viewport_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code)
{
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_activate
 * Description:
 *
 * Input arguments:
 *      pt_ctx
 *      ui4_key_code
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_viewport_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code)
{
    INT32             i4_ret = NAVR_OK;

    i4_ret = _nav_viewport_msg_show();
    RET_ON_ERR(i4_ret);
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_inactivate
 * Description:
 *
 * Input arguments:
 *      pt_ctx
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_viewport_inactivate(NAV_CONTEXT_T*      pt_ctx)
{
    INT32           i4_ret = NAVR_OK;

    i4_ret = _nav_viewport_msg_hide();
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_handle_msg
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
static INT32 _nav_viewport_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1)
{
    return NAVR_OK;
}

static INT32 _nav_viewport_msg_show(VOID)
{
    INT32                      i4_ret = NAVR_OK;
    NAV_VIEWPORT_T*            pt_this = &t_g_nav_viewport;
    UI_SIMPLE_DIALOG_INIT_T    t_warning_msg_init;

    if (b_is_create == FALSE)
    {
        c_memset(&t_warning_msg_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

        /* Initial the UI Simple Dialog */
        t_warning_msg_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_WARNING_MSG;
        t_warning_msg_init.h_parent                       = pt_this->h_canvas;
        t_warning_msg_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
        t_warning_msg_init.pf_ui_simple_dialog_yes_cb_fct = NULL;
        t_warning_msg_init.pf_wdgt_proc                   = NULL;
        t_warning_msg_init.pt_begin_offset                = NULL;
        t_warning_msg_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;

        a_ui_simple_dialog_create(&t_warning_msg_init, 
                                  &pt_this->h_viewport_msg);
        b_is_create = TRUE;
    }

    if ((FALSE == pt_this->b_is_show)&&
        (NULL_HANDLE != pt_this->h_viewport_msg))
    {
        TV_MODE_T   e_tv_mode = TV_MODE_TYPE_NORMAL;
        BOOL        b_is_3D_playing = FALSE;

        i4_ret = a_tv_get_mode(&e_tv_mode);
        if ((i4_ret == 0)&&(e_tv_mode != TV_MODE_TYPE_NORMAL))
        {
            a_ui_simple_dialog_set_text(pt_this->h_viewport_msg, 
                MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_WARNING_MSG_VIEWPORT_IN_PIP));
        }

        b_is_3D_playing = a_tv_custom_is_3D_mode_playing();
        if (b_is_3D_playing == TRUE)
        {
            a_ui_simple_dialog_set_text(pt_this->h_viewport_msg, 
                MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_WARNING_MSG_VIEWPORT_IN_3D));
        }
		
	  if ((b_is_3D_playing == FALSE) && (e_tv_mode == TV_MODE_TYPE_NORMAL))
	  {
	  	return NAVR_OK;
	  }
	  
        i4_ret = a_ui_simple_dialog_show(pt_this->h_viewport_msg);
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_repaint(pt_this->h_viewport_msg, NULL, TRUE);
        RET_ON_ERR(i4_ret);

        pt_this->b_is_show = TRUE;

        _nav_viewport_hide_timer_start();
    }

    if (TRUE == pt_this->b_is_show)
    {
        _nav_viewport_reset_hide_timer();
    }
    
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_msg_hide
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
static INT32 _nav_viewport_msg_hide(VOID)
{
    NAV_VIEWPORT_T*   pt_this = &t_g_nav_viewport;
    INT32             i4_ret = NAVR_OK;

    if ((TRUE == pt_this->b_is_show)&&
        (NULL_HANDLE != pt_this->h_viewport_msg))
    {
        i4_ret = a_ui_simple_dialog_hide(pt_this->h_viewport_msg);
        RET_ON_ERR(i4_ret);

        i4_ret = a_ui_simple_dialog_repaint(pt_this->h_viewport_msg);
        RET_ON_ERR(i4_ret);

        pt_this->b_is_show = FALSE;

        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

static VOID _viewport_show_nfy(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _nav_viewport_msg_show();
}

static INT32 _nav_viewport_show_msg_nfy(UINT16  ui2_nfy_id,
                                       VOID*   pv_tag,
                                       ICL_NOTIFY_DATA_T*  pt_notify_data)
{
    INT32   i4_ret;
    UINT8   ui1_icl_val;
    SIZE_T  z_size = ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                           &ui1_icl_val,
                           &z_size);
    if ((i4_ret==0) && (ui1_icl_val==ICL_VIEWPORT_LAST_REQ_FAIL))
    {
        i4_ret = nav_request_context_switch(
                            _viewport_show_nfy,
                            NULL,
                            NULL,
                            NULL
                            );

        RET_ON_ERR(i4_ret);
    }
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_hide_timer_start
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
static INT32 _nav_viewport_hide_timer_start(VOID)
{
    INT32             i4_ret = NAVR_OK;
    NAV_VIEWPORT_T*   pt_this = &t_g_nav_viewport;

    if(NULL_HANDLE != pt_this->h_hide_timer)
    {
        i4_ret = c_timer_start(pt_this->h_hide_timer,
                              VIEWPORT_MSG_TIMEOUT,
                              X_TIMER_FLAG_ONCE,
                              _nav_viewport_hide_timer_nfy,
                              NULL);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

static VOID _nav_viewport_reset_hide_timer(VOID)
{
    NAV_VIEWPORT_T* pt_this = &t_g_nav_viewport;
    INT32 i4_ret;

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    LOG_ON_ERR(i4_ret);

    if (i4_ret == NAVR_OK)
    {
        i4_ret = c_timer_start(
                        pt_this->h_hide_timer,
                        VIEWPORT_MSG_TIMEOUT,
                        X_TIMER_FLAG_ONCE,
                        _nav_viewport_hide_timer_nfy,
                        NULL
                        );
        LOG_ON_ERR(i4_ret);
    }
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_viewport_hide_timer_nfy
 * Description:
 *
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_viewport_hide_timer_nfy (
                        HANDLE_T        h_timer,
                        VOID*           pv_tag)
{
    _nav_viewport_msg_hide();
}

static VOID _viewport_hide_nfy(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _nav_viewport_msg_hide();
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      a_nav_viewport_hide
 * Description:
 *      The registration function of the NAV Dialog.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
extern INT32 a_nav_viewport_hide(VOID)
{
    INT32           i4_ret = NAVR_OK;

    i4_ret = nav_request_context_switch_in_sync(
                            _viewport_hide_nfy,
                            NULL,
                            NULL,
                            NULL,
                            _VIEWPORT_DISPLAY_STATUS_CHANGE_TIMEOUT
                            );
    RET_ON_ERR(i4_ret);
    return NAVR_OK;
}

extern INT32 a_nav_viewport_hide_async(VOID)
{
    _nav_viewport_msg_hide();
    return NAVR_OK;
}

extern INT32 a_nav_viewport_register(VOID)
{
    NAV_COMP_T      t_comp;
    INT32           i4_ret = NAVR_OK;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_DIALOG */
    t_comp.pf_init           = _nav_viewport_init;
    t_comp.pf_deinit         = _nav_viewport_deinit;
    t_comp.pf_is_key_handler = _nav_viewport_is_key_handler;
    t_comp.pf_activate       = _nav_viewport_activate;
    t_comp.pf_inactivate     = _nav_viewport_inactivate;
    t_comp.pf_handle_msg     = _nav_viewport_handle_msg;

    i4_ret = nav_register_component(
                        NAV_COMP_ID_VIEWPORT,
                        &t_comp,
                        COMP_EXC_SET_VIEWPORT);
    RET_ON_ERR(i4_ret);

    return NAVR_OK;
}

#endif /* VIEWPORT_SUPPORT */

