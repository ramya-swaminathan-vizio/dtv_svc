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
 * $RCSfile: _3d_setting_view.c,v $
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

#include "3d_setting.h"
/* view */
#include "app_util/a_ui.h"
#include "res/app_util/app_tv/a_tv_custom.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

#define NAV_3D_SETTING_YES_NO_DLG_TIMER     (0)
#define NAV_3D_SETTING_OK_DLG_TIMER         (1)

typedef struct _NAV_3D_SETTING_VIEW_T
{
    NAV_3D_SETTING_T*           pt_ctrl;
    HANDLE_T                    h_main_frame;
    HANDLE_T                    h_msg;
    HANDLE_T                    h_dialog_yes_no;
    HANDLE_T                    h_dialog_ok;
    HANDLE_T                    h_hide_timer;
    UINT32                      ui4_timer_delay;
} NAV_3D_SETTING_VIEW_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_3D_SETTING_VIEW_T t_g_nav_3d_setting_view = {0};

extern BOOL b_g_is_3RD_3d;

static INT32 _nav_3d_setting_view_hide(VOID);
static VOID _nav_3d_setting_timer_cb_fct(HANDLE_T  pt_tm_handle,
                                   VOID*     pv_tag);
static VOID _nav_3d_setting_view_dialog_no_action(VOID);
static VOID _nav_3d_setting_view_dialog_yes_action(VOID);
static INT32 _nav_3d_setting_view_warning_dialog_hide(VOID);

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_change_mode_dialog_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_change_mode_dialog_hide(VOID)
{

    a_ui_simple_dialog_hide(t_g_nav_3d_setting_view.h_dialog_yes_no);
    c_wgl_repaint(t_g_nav_3d_setting_view.h_dialog_yes_no, NULL, TRUE);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_warning_dialog_show
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_warning_dialog_show(VOID)
{
    NAV_3D_SETTING_VIEW_T*  pt_view = &t_g_nav_3d_setting_view;
    INT32                   i4_ret = NAVR_OK;

	/* Update the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_view->h_dialog_ok, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_X_3D_SETTING_VIEW_WARNING));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_view->h_dialog_ok, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_OK));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    a_ui_simple_dialog_show(pt_view->h_dialog_ok);
    a_ui_simple_dialog_set_focus(pt_view->h_dialog_ok, FALSE);

    i4_ret = c_wgl_repaint(pt_view->h_dialog_ok, NULL, TRUE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    c_timer_start(pt_view->h_hide_timer,
                5000,
                X_TIMER_FLAG_ONCE,
                _nav_3d_setting_timer_cb_fct,
                (VOID*)NAV_3D_SETTING_OK_DLG_TIMER);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_timer_handler_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_3d_setting_timer_handler_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3)
{
    if (NAV_3D_SETTING_YES_NO_DLG_TIMER == (UINT32)pv_tag1)
    {
        _nav_3d_setting_view_dialog_yes_action();

    }
    else if (NAV_3D_SETTING_OK_DLG_TIMER == (UINT32)pv_tag1)
    {
		_nav_3d_setting_view_warning_dialog_hide();
		_nav_3d_setting_view_hide();
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_timer_cb_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_3d_setting_timer_cb_fct(HANDLE_T  pt_tm_handle,
                                   VOID*     pv_tag)
{
    nav_request_context_switch(_nav_3d_setting_timer_handler_fct, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_dialog_no_action
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_3d_setting_view_dialog_no_action(VOID)
{
    DBG_LOG_PRINT(("\n[nav 3D setting view] --- reconfig 2D mode\n"));

    c_timer_stop(t_g_nav_3d_setting_view.h_hide_timer);
    _nav_3d_setting_view_change_mode_dialog_hide();

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                 (INT16)APP_CFG_3D_MODE_AUTO);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

    /* 3D to 2D*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
             (INT16 )APP_CFG_3D_TO_2D_LEFT);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

    _nav_3d_setting_view_hide();
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_dialog_yes_action
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_3d_setting_view_dialog_yes_action(VOID)
{
    c_timer_stop(t_g_nav_3d_setting_view.h_hide_timer);
    _nav_3d_setting_view_change_mode_dialog_hide();

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                 (INT16)APP_CFG_3D_MODE_AUTO);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

    /* 3D to 2D*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
             (INT16 )APP_CFG_3D_TO_2D_OFF);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

    DBG_LOG_PRINT(("\n[nav 3D setting view] --- reconfig 3D mode\n"));

    a_cfg_set_3d_display(a_tv_custom_is_3D_mode_playing ());

    _nav_3d_setting_view_warning_dialog_show();
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_dialog_ok_action
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _nav_3d_setting_view_dialog_ok_action(VOID)
{
    c_timer_stop(t_g_nav_3d_setting_view.h_hide_timer);

	_nav_3d_setting_view_warning_dialog_hide();
    _nav_3d_setting_view_hide();
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_yes_no_dialog_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_yes_no_dialog_create(VOID)
{
    NAV_3D_SETTING_VIEW_T*          pt_view = &t_g_nav_3d_setting_view;
    UI_SIMPLE_DIALOG_INIT_T         t_simple_dialog_init;
    INT32                           i4_ret;
    GL_POINT_T                      t_offset = {-55, 0};


    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_view->h_main_frame;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = _nav_3d_setting_view_dialog_no_action;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _nav_3d_setting_view_dialog_yes_action;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = FALSE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                              &pt_view->h_dialog_yes_no);
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_view->h_dialog_yes_no, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_X_3D_SETTING_DETECT_WARNING));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_view->h_dialog_yes_no, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_YES));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_no_text(pt_view->h_dialog_yes_no, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_NO));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_ok_dialog_create
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_ok_dialog_create(VOID)
{
    NAV_3D_SETTING_VIEW_T*          pt_view = &t_g_nav_3d_setting_view;
    UI_SIMPLE_DIALOG_INIT_T         t_simple_dialog_init;
    INT32                           i4_ret;
    GL_POINT_T                      t_offset = {-55, 0};

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_view->h_main_frame;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _nav_3d_setting_view_dialog_ok_action;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;

    a_ui_simple_dialog_create(&t_simple_dialog_init,
                                  &pt_view->h_dialog_ok);

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_view->h_dialog_ok, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_X_3D_SETTING_VIEW_WARNING));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_view->h_dialog_ok, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_OK));
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_3d_setting_warning_dialog_hide
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_warning_dialog_hide(VOID)
{
    /*for ok action, if b_g_is_3RD_3d==FALSE, dialog hide by timer already, need do nothing*/
    /*for timer, if b_g_is_3RD_3d==FALSE, dialog hide by ok action already, need do nothing*/
    if (TRUE == b_g_is_3RD_3d)
    {
        b_g_is_3RD_3d = FALSE;
    }

	a_ui_simple_dialog_hide(t_g_nav_3d_setting_view.h_dialog_ok);
    c_wgl_repaint(t_g_nav_3d_setting_view.h_dialog_ok, NULL, TRUE);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
* Name
*      _nav_3d_setting_view_hide
* Description
* Input arguments
* Output arguments
* Returns
*---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_hide(VOID)
{
    nav_hide_component(NAV_COMP_ID_3D_SETTING);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_activate
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_activate(UINT32 ui4_key_code)
{
    NAV_3D_SETTING_VIEW_T*      pt_view = &(t_g_nav_3d_setting_view);
    INT32               i4_ret;

    DBG_LOG_PRINT(("\n[nav 3D setting view] --- _nav_3d_setting_view_activate\n"));

    /*3RD play 3d content show OSD*/
    if (b_g_is_3RD_3d == TRUE)
    {
        _nav_3d_setting_view_warning_dialog_show();
    }
    else
    {
    	/* Update the attribute */
	    i4_ret = a_ui_simple_dialog_set_text(pt_view->h_dialog_yes_no, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_X_3D_SETTING_DETECT_WARNING));
	    if(i4_ret != APP_UIR_OK){
	        return NAVR_FAIL;
	    }

	    i4_ret = a_ui_simple_dialog_set_yes_text(pt_view->h_dialog_yes_no, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_YES));
	    if(i4_ret != APP_UIR_OK){
	        return NAVR_FAIL;
	    }

	    i4_ret = a_ui_simple_dialog_set_no_text(pt_view->h_dialog_yes_no, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_NO));
	    if(i4_ret != APP_UIR_OK){
	        return NAVR_FAIL;
	    }

        a_ui_simple_dialog_show(pt_view->h_dialog_yes_no);
        a_ui_simple_dialog_set_answer(pt_view->h_dialog_yes_no, TRUE);
        a_ui_simple_dialog_set_focus(pt_view->h_dialog_yes_no, FALSE);

        i4_ret = c_wgl_repaint(pt_view->h_dialog_yes_no, NULL, TRUE);
        if (i4_ret != WGLR_OK)
        {
            return NAVR_FAIL;
        }

        c_timer_start(pt_view->h_hide_timer,
                    5000,
                    X_TIMER_FLAG_ONCE,
                    _nav_3d_setting_timer_cb_fct,
                    (VOID*)NAV_3D_SETTING_YES_NO_DLG_TIMER);
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_init(
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset)
{
    NAV_3D_SETTING_VIEW_T*      pt_view = &(t_g_nav_3d_setting_view);

    if (c_handle_valid(pt_view->h_hide_timer) == TRUE) {
        c_timer_delete(pt_view->h_hide_timer);
    }

    pt_view->h_hide_timer = NULL_HANDLE;
    pt_view->h_main_frame = h_canvas;

    /*create timer*/
    c_timer_create(&pt_view->h_hide_timer);

    /* Create dialog */
    _nav_3d_setting_view_yes_no_dialog_create();
    _nav_3d_setting_view_ok_dialog_create();
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_3d_setting_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_3d_setting_view_deinit(VOID)
{
    NAV_3D_SETTING_VIEW_T* pt_view = &t_g_nav_3d_setting_view;

    c_timer_delete(pt_view->h_hide_timer);

    a_ui_simple_dialog_destory(pt_view->h_dialog_yes_no);

    c_wgl_destroy_widget(pt_view->h_main_frame);

    pt_view->pt_ctrl         = NULL;
    pt_view->h_main_frame    = NULL_HANDLE;
    pt_view->h_dialog_yes_no = NULL_HANDLE;
    pt_view->ui4_timer_delay = 0;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_3d_setting_view_register_default_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_3d_setting_view_register_default_hdlr(
                    NAV_3D_SETTING_VIEW_HDLR_T*      pt_view_hdlr)
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_3d_setting_view_init;
    pt_view_hdlr->pf_deinit         = _nav_3d_setting_view_deinit;
    pt_view_hdlr->pf_is_key_handler = NULL;
    pt_view_hdlr->pf_activate       = _nav_3d_setting_view_activate;
    pt_view_hdlr->pf_hide           = _nav_3d_setting_view_hide;

    return NAVR_OK;
}

