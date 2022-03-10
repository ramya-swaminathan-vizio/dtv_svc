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
 * $RCSfile: via_dlg_view.c,v $
 * $Revision: #2 $
 * $Date: 2015/06/09 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *       USB Plug Detection.
 *
 *---------------------------------------------------------------------------*/

#include "u_common.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_gl.h"
#include "c_os.h"
#include "c_handle.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_svctx.h"

#include "menu2/a_menu.h"

#include "nav/nav_common.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "res/msgconvert/msgconvert_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "nav/via_dlg/nav_via_dlg.h"
#include "nav/via_dlg/nav_via_dlg_view.h"

#include "app_util/a_ui.h"
#include "app_util/a_tv.h"
#include "res/wdk/wdk_img.h"
#include "res/nav/nav_dbg.h"
#include "res/app_util/icl/a_icl_custom.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

typedef struct _NAV_VIA_DLG_VIEW_T
{
    NAV_VIA_DLG_HDLR_T*     pt_ctrl;

    HANDLE_T                h_canvas;
    HANDLE_T                h_frame;
    HANDLE_T                h_anim_frame;
    HANDLE_T                h_warning_dialog;
    HANDLE_T                h_warning_dialog_switch_to_menu_timer;
    HANDLE_T                h_hide_timer;
    HANDLE_T                h_text;
    HANDLE_T                h_anim_timer;

    WGL_HIMG_TPL_T          h_img_bk;
    UINT8                   ui1_lang_id;

    UINT32                  ui4_time_delay;

    BOOL                    b_is_show;
    BOOL                    b_ui_inited;
    BOOL                    b_is_warning_dialog_show;
    UINT16                  ui2_show_msg_id;
} NAV_VIA_DLG_VIEW_T;

#define RET_ON_ERR(_expr)  \
if(_expr != 0)\
{\
    DBG_ERROR (("<NAV_VIA_DLG> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
    return _expr;\
}

#define SIMILAR_IPTS 
#define NAV_ANIMATION_IMG_MAX_NUM               12
#define NAV_VIA_DLG_DEFAULT_TIMER_DELAY         5000
#define NAV_VIA_DLG_YAHOO_STATUS_TIMER_DELAY    (60*1000)
#define NAV_VIA_DLG_ANIMA_TIMEOUT               500
#define NAV_VIA_DLG_WARNING_DIALOG_SWITCH_TO_MENU_TIMER_DELAY  (2000)
#define NAV_VIA_DLG_WARNING_DIALOG_SWITCH_TO_NAV_DELAY         (1500)


extern BOOL msg_convert_custom_is_yahoo_ready(VOID);
#ifdef LINUX_TURNKEY_SOLUTION
extern INT32 cmd_convert_send_cmd(CHAR* ps_cmd);
#endif

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
UINT32 ui4_delay_key_code = BTN_INVALID;

static NAV_VIA_DLG_VIEW_T       t_g_nav_via_dlg_view;
static WGL_HIMG_TPL_T           h_g_img_animation[NAV_ANIMATION_IMG_MAX_NUM];
static UINT8                    ui1_g_img_idx = 0;
static HANDLE_T                 h_g_img_icon;
static BOOL                     g_b_dtv_is_resuming = FALSE;
static HANDLE_T                 h_warning_dialog_switch_to_nav_timer = NULL_HANDLE;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_view_deinit (VOID);
static INT32 _nav_via_dlg_view_show (VOID);
static INT32 _nav_via_dlg_view_hide (VOID);
static INT32 _nav_via_dlg_default_msg_proc(HANDLE_T            h_widget,
                                               UINT32              ui4_msg,
                                               VOID*               pv_param1,
                                               VOID*               pv_param2);
static INT32 _nav_via_dlg_anima_timer_stop(VOID);
static INT32 _nav_via_dlg_hide_timer_stop(VOID);
static INT32 _nav_via_dlg_hide_warning_dialog(VOID);

static INT32 _nav_via_dlg_warning_dialog_switch_to_menu_timer_stop(VOID);
static VOID _nav_via_dlg_warning_dialog_switch_to_menu_cb(VOID*        pv_tag1,
                                                                       VOID*        pv_tag2,
                                                                       VOID*        pv_tag3);

static INT32 _nav_via_dlg_warning_dialog_switch_to_nav_timer_stop(VOID);
static VOID _nav_via_dlg_warning_dialog_switch_to_nav_cb(VOID*        pv_tag1,
                                                                     VOID*        pv_tag2,
                                                                     VOID*        pv_tag3);



VOID a_nav_via_dlg_view_dialog_hide(VOID)
{	
    _nav_via_dlg_hide_timer_stop();
    nav_hide_component(NAV_COMP_ID_VIA_DLG);

    _nav_via_dlg_view_hide();

    return;
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_hide_timer_fct
 * Description:
 *      nav usb plugin detection dialog hide timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_via_dlg_hide_timer_fct(VOID*        pv_tag1,
                                            VOID*        pv_tag2,
                                            VOID*        pv_tag3)
{
    _nav_via_dlg_anima_timer_stop();  
    nav_return_activation(NAV_COMP_ID_VIA_DLG);
    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_anima_timer_fct
 * Description:
 *      nav usb plugin detection dialog hide timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_via_dlg_anima_timer_fct(VOID*        pv_tag1,
                                            VOID*        pv_tag2,
                                            VOID*        pv_tag3)
{
    INT32           i4_ret = NAVR_OK;
    WGL_IMG_INFO_T  t_img_info;
    
    ui1_g_img_idx += 1;
    if (ui1_g_img_idx > (NAV_ANIMATION_IMG_MAX_NUM - 1))
    {
        ui1_g_img_idx = 0;
    }

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_g_img_animation[ui1_g_img_idx];
    t_img_info.u_img_data.t_standard.t_enable = h_g_img_animation[ui1_g_img_idx];
    t_img_info.u_img_data.t_standard.t_highlight = h_g_img_animation[ui1_g_img_idx];
    
    i4_ret = c_wgl_do_cmd(h_g_img_icon,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_img_info));
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_g_img_icon, WGL_SW_NORMAL);
    NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_g_img_icon, NULL, TRUE);
    NAV_LOG_ON_FAIL(i4_ret);

    /* Send via key per 6s */
    if (MLM_NAV_KEY_NAV_VIA_DLG_MSG == t_g_nav_via_dlg_view.ui2_show_msg_id
        && ui1_g_img_idx%6 == 0
        && !msg_convert_custom_is_yahoo_ready())
    {
        cmd_convert_send_cmd("\n:dtv_app_mtk,am,:show=yahoo\n");
        cmd_convert_send_cmd("\n:dtv_app_mtk,am,:focus=yahoo\n");
        cmd_convert_send_cmd("\n:dtv_app_mtk,yahoo,:click=WIDGET\n");
    }
    
    return;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_hide_timer_nfy
 * Description:
 *      nav usb plugin detection dialog hide timer notify
 * Input arguments:
 *      h_timer
 *      pv_tag
 * Output arguments:
 *      None
 * Returns:
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_via_dlg_hide_timer_nfy(HANDLE_T        h_timer,
                                            VOID*           pv_tag)
{
    nav_request_context_switch(_nav_via_dlg_hide_timer_fct, NULL, NULL, NULL);

    return;
}

static VOID _nav_via_dlg_anima_timer_nfy(HANDLE_T        h_timer,
                                            VOID*           pv_tag)
{
    nav_request_context_switch(_nav_via_dlg_anima_timer_fct, NULL, NULL, NULL);

    return;
}                                           

static VOID _nav_via_dlg_dlg_warning_dialog_switch_to_menu_nfy(HANDLE_T   h_timer,
                                                                         VOID*           pv_tag)
{
    nav_request_context_switch(_nav_via_dlg_warning_dialog_switch_to_menu_cb, NULL, NULL, NULL);

    return;
}

static VOID _nav_via_dlg_dlg_warning_dialog_switch_to_nav_nfy(HANDLE_T   h_timer,
                                                                         VOID*           pv_tag)
{
    nav_request_context_switch(_nav_via_dlg_warning_dialog_switch_to_nav_cb, NULL, NULL, NULL);

    return;
}


/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_hide_timer_start
 * Description:
 *      start nav usb plugin detection dialog timer
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_hide_timer_start(VOID)
{
    INT32                       i4_ret = NAVR_OK;
    NAV_VIA_DLG_VIEW_T*         pt_view = &t_g_nav_via_dlg_view;

    if (NULL_HANDLE != pt_view->h_hide_timer)
    {
        i4_ret = c_timer_start(pt_view->h_hide_timer,
                               pt_view->ui4_time_delay,
                               X_TIMER_FLAG_ONCE,
                               _nav_via_dlg_hide_timer_nfy,
                               NULL);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

static INT32 _nav_via_dlg_hide_timer_stop(VOID)
{
    NAV_VIA_DLG_VIEW_T*     pt_this = &t_g_nav_via_dlg_view;
    INT32                   i4_ret = NAVR_OK;

    _nav_via_dlg_anima_timer_stop();
    
    if(NULL_HANDLE != pt_this->h_hide_timer)
    {
        i4_ret = c_timer_stop(pt_this->h_hide_timer);
        if(i4_ret != OSR_OK){return NAVR_FAIL;}
    }

    return NAVR_OK;
}

static INT32 _nav_via_dlg_anima_timer_start(VOID)
{
    INT32                       i4_ret = NAVR_OK;
    NAV_VIA_DLG_VIEW_T*         pt_view = &t_g_nav_via_dlg_view;

    if (NULL_HANDLE != pt_view->h_anim_timer)
    {        
        i4_ret = c_timer_start(pt_view->h_anim_timer,
                               NAV_VIA_DLG_ANIMA_TIMEOUT,
                               X_TIMER_FLAG_REPEAT,
                               _nav_via_dlg_anima_timer_nfy,
                               NULL);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

static INT32 _nav_via_dlg_anima_timer_stop(VOID)
{
    NAV_VIA_DLG_VIEW_T*     pt_this = &t_g_nav_via_dlg_view;
    INT32                   i4_ret = NAVR_OK;

    if(NULL_HANDLE != pt_this->h_anim_timer)
    {
        i4_ret = c_timer_stop(pt_this->h_anim_timer);

        NAV_LOG_ON_FAIL(i4_ret);

        c_wgl_set_visibility(h_g_img_icon, WGL_SW_HIDE);
        //c_wgl_float(h_g_img_icon, FALSE, WGL_NO_AUTO_REPAINT);
        c_wgl_repaint( h_g_img_icon, NULL, TRUE);
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_via_dlg_warning_switch_to_menu_cb
 *
 * Description: jump to network setup page
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_via_dlg_warning_dialog_switch_to_menu_cb(VOID*        pv_tag1,
                                                                       VOID*        pv_tag2,
                                                                       VOID*        pv_tag3)
{ 
    
    /* jump to network setup page */
    cmd_convert_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,:click=NETWORK\n");
    
    _nav_via_dlg_warning_dialog_switch_to_menu_timer_stop();    
}

static VOID _nav_via_dlg_warning_dialog_switch_to_nav_cb(VOID*        pv_tag1,
                                                                     VOID*        pv_tag2,
                                                                     VOID*        pv_tag3)
{    
    /* nav resumed */
    g_b_dtv_is_resuming = FALSE;
    _nav_via_dlg_warning_dialog_switch_to_nav_timer_stop();
    
}


/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_warning_dialog_switch_to_menu_timer_start
 * Description:
 *      start warning dialog switch to menu timer
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_warning_dialog_switch_to_menu_timer_start(VOID)
{
    INT32                       i4_ret = NAVR_OK;
    NAV_VIA_DLG_VIEW_T*         pt_view = &t_g_nav_via_dlg_view;

    if (NULL_HANDLE != pt_view->h_warning_dialog_switch_to_menu_timer)
    {
        i4_ret = c_timer_start(pt_view->h_warning_dialog_switch_to_menu_timer,
                               NAV_VIA_DLG_WARNING_DIALOG_SWITCH_TO_MENU_TIMER_DELAY,
                               X_TIMER_FLAG_ONCE,
                               _nav_via_dlg_dlg_warning_dialog_switch_to_menu_nfy,
                               NULL);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

static INT32 _nav_via_dlg_warning_dialog_switch_to_menu_timer_stop(VOID)
{
    NAV_VIA_DLG_VIEW_T*     pt_this = &t_g_nav_via_dlg_view;
    INT32                   i4_ret = NAVR_OK;
    
    if(NULL_HANDLE != pt_this->h_warning_dialog_switch_to_menu_timer)
    {
        i4_ret = c_timer_stop(pt_this->h_warning_dialog_switch_to_menu_timer);
        if(i4_ret != OSR_OK){return NAVR_FAIL;}
    }

    return NAVR_OK;
}

static INT32 _nav_via_dlg_warning_dialog_switch_to_nav_timer_start(VOID)
{
    INT32                       i4_ret = NAVR_OK;

    if (NULL_HANDLE != h_warning_dialog_switch_to_nav_timer)
    {
        i4_ret = c_timer_start(h_warning_dialog_switch_to_nav_timer,
                               NAV_VIA_DLG_WARNING_DIALOG_SWITCH_TO_NAV_DELAY,
                               X_TIMER_FLAG_ONCE,
                               _nav_via_dlg_dlg_warning_dialog_switch_to_nav_nfy,
                               NULL);
        RET_ON_ERR(i4_ret);
    }

    return NAVR_OK;
}

static INT32 _nav_via_dlg_warning_dialog_switch_to_nav_timer_stop(VOID)
{
    INT32                   i4_ret = NAVR_OK;
    
    if(NULL_HANDLE != h_warning_dialog_switch_to_nav_timer)
    {
        i4_ret = c_timer_stop(h_warning_dialog_switch_to_nav_timer);
        if(i4_ret != OSR_OK){return NAVR_FAIL;}
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_via_dlg_warning_dialog_yes_btn_cb
 *
 * Description: jump to network setup page
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_via_dlg_warning_dialog_yes_btn_cb(VOID)
{    
    /* hide OSD */
    nav_return_activation(NAV_COMP_ID_VIA_DLG);
    
    _nav_via_dlg_warning_dialog_switch_to_menu_timer_start();   
	return;
}

/*----------------------------------------------------------------------------
 * Name: _nav_via_dlg_warning_dialog_other_key_cb
 *
 * Description: handle other key 
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static BOOL _nav_via_dlg_warning_dialog_other_key_cb(UINT32 ui4_keycode)
{
    /* ignore other key */
    return TRUE;
}

/*----------------------------------------------------------------------------
 * Name: _nav_via_dlg_warning_dialog_no_btn_cb
 *
 * Description: Close APP.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_via_dlg_warning_dialog_no_btn_cb(VOID)
{
    /* Close APP. */
    nav_return_activation(NAV_COMP_ID_VIA_DLG);
	return;	
}

/*-----------------------------------------------------------------------------
 * Name: _nav_via_dlg_show_warning_dialog
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_show_warning_dialog(
    VOID
)
{
    INT32                   i4_ret  = NAVR_OK;
    NAV_VIA_DLG_VIEW_T*      pt_this = &t_g_nav_via_dlg_view;
    /* set dialog text */
    //c_uc_ps_to_w2s("Your VIZIO TV has been updated for a better experince. The app launcher is easier to use and many applications have been enhanced. You may have to re-enter your username and password for some apps.", w2s_str, 512);
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_warning_dialog, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_VIA_DLG_WRNNG_MSG));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);
    /* set dialog yes button text */
    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_warning_dialog, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_VIA_DLG_WRNNG_OK));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /* set dialog no button text */
    i4_ret = a_ui_simple_dialog_set_no_text(pt_this->h_warning_dialog, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_VIA_DLG_WRNNG_NO));
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /* show dialog */
    i4_ret = a_ui_simple_dialog_show(pt_this->h_warning_dialog);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /* set focus */
    i4_ret = a_ui_simple_dialog_set_focus(pt_this->h_warning_dialog, TRUE);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    /* repaint dialog */
    i4_ret = a_ui_simple_dialog_repaint(pt_this->h_warning_dialog);
    NAV_CHK_FAIL(APP_UIR_OK == i4_ret ? NAVR_OK : i4_ret);

    
    pt_this->b_is_warning_dialog_show = TRUE;


    a_tv_net_disable_keyroute(TRUE);
    i4_ret = a_amb_enable_system_key(FALSE);
    NAV_CHK_FAIL(AMBR_OK == i4_ret ? NAVR_OK : i4_ret);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_uvia_dlg_hide_warning_dialog
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_hide_warning_dialog(
    VOID
)
{    
    NAV_VIA_DLG_VIEW_T*    pt_this = &t_g_nav_via_dlg_view;
    
    /* hide dialog */
    a_ui_simple_dialog_hide(pt_this->h_warning_dialog);

    /* repaint dialog */
    a_ui_simple_dialog_repaint(pt_this->h_warning_dialog);

    /*reset msg_id. */
    pt_this->ui2_show_msg_id = MLM_NAV_KEY_NAV_VIA_DLG_MSG;

    cmd_convert_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,:resume=dtv\n");
    g_b_dtv_is_resuming = TRUE;

    _nav_via_dlg_warning_dialog_switch_to_nav_timer_start();
    
    a_tv_net_disable_keyroute(FALSE);
    a_amb_enable_system_key(TRUE);
   
    pt_this->b_is_warning_dialog_show = FALSE;
    
    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _nav_via_dlg_create_warning_dialog
 *
 * Description: The message process fuction which is warning dialog.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_create_warning_dialog(
    VOID
)
{
    INT32                      i4_ret = NAVR_OK;
    UI_SIMPLE_DIALOG_INIT_T    t_simple_dialog_init;
    NAV_VIA_DLG_VIEW_T*        pt_this = &t_g_nav_via_dlg_view;  
    GL_POINT_T                 t_offset = {(-50*4/3), 0};

    /* create dialog box */
    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

   
    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = pt_this->h_canvas;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _nav_via_dlg_warning_dialog_yes_btn_cb;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = _nav_via_dlg_warning_dialog_no_btn_cb;
    t_simple_dialog_init.pf_ui_simple_dialog_other_key_cb_fct = _nav_via_dlg_warning_dialog_other_key_cb;
    t_simple_dialog_init.b_default_answer               = FALSE;
    
    i4_ret = c_timer_create(&pt_this->h_warning_dialog_switch_to_menu_timer);
    if(OSR_OK != i4_ret)
    {
        NAV_LOG_ON_FAIL(i4_ret);            
        pt_this->h_warning_dialog_switch_to_menu_timer = NULL_HANDLE;

    }
    i4_ret = c_timer_create(&h_warning_dialog_switch_to_nav_timer);
    if(OSR_OK != i4_ret)
    {
        NAV_LOG_ON_FAIL(i4_ret);
        h_warning_dialog_switch_to_nav_timer = NULL_HANDLE;
    }
    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &(pt_this->h_warning_dialog));

    DBG_INFO(("i4_ret=%d\n",i4_ret));
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_default_msg_proc
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
static INT32 _nav_via_dlg_default_msg_proc(HANDLE_T            h_widget,
                                               UINT32              ui4_msg,
                                               VOID*               pv_param1,
                                               VOID*               pv_param2)
{
#ifdef APP_YAHOO_LOADING_SPINNER_SUPPORT
    INT32           i4_ret = NAVR_OK;

    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;

            /* Any key will exit Remote low message, and also continue key's operations */
            if (a_nav_via_dlg_get_show_info() == MLM_NAV_KEY_WIFI_REMOTE_BATTERY_LEVEL)
            {
                nav_return_activation(NAV_COMP_ID_VIA_DLG);
            }

            i4_ret = _nav_via_dlg_hide_timer_start();
            RET_ON_ERR(i4_ret);

            switch(ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                case BTN_SELECT:
                {
                    break;
                }
                case BTN_WIDGET:
                case BTN_AMAZON:
                case BTN_MGO:
                case BTN_NETFLIX:
                case BTN_VUDU:
                case BTN_IHEART_RADIO:
                case BTN_WATCHFREE:
                case BTN_REDBOX:
                case BTN_HAYSTACK:
                {
                    if (!msg_convert_custom_is_yahoo_ready())
                    {
                        a_nav_via_dlg_set_show_info(MLM_NAV_KEY_NAV_VIA_DLG_MSG);
                        _nav_via_dlg_view_show();
                    }
                    break;
                }
                case BTN_EXIT:
                {
                    DBG_INFO(("_nav_via_dlg_default_msg_proc() BTN_EXIT\n"));
                    nav_return_activation(NAV_COMP_ID_VIA_DLG);
                    _nav_via_dlg_hide_timer_stop();
                    
                    break;
                }
                case BTN_INPUT_SRC:
                {
                    nav_return_activation(NAV_COMP_ID_VIA_DLG);
                    _nav_via_dlg_hide_timer_stop();
                    
                    nav_rcu_key_handler(ui4_keycode);
                    return NAVR_OK;
                }
                    
                default:
                    nav_rcu_key_handler(ui4_keycode);
                    return NAVR_OK;
                }
                break;
        }

        default:
            break;
    }
#endif
    return NAVR_OK;
}

static INT32 _nav_via_dlg_animation_icon_create(VOID)
{
    INT32   i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    UINT32              ui4_canvas_h ,ui4_canvas_w;
    WGL_IMG_INFO_T      t_img_info;
    NAV_VIA_DLG_VIEW_T* pt_view = &t_g_nav_via_dlg_view;

    nav_get_ui_canvas_size(&ui4_canvas_w, &ui4_canvas_h);

    ui4_style = WGL_STL_GL_NO_BK;

    /* create animation frame */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      5,
                      (ui4_canvas_h-NAV_VIA_ANIM_FRAME_HEIGHT-5),
                      NAV_VIA_ANIM_FRAME_WIDTH,
                      NAV_VIA_ANIM_FRAME_HEIGHT);

    i4_ret = c_wgl_create_widget(pt_view->h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                                 NULL,
                                 &pt_view->h_anim_frame);
    if(i4_ret < 0)
    {
        DBG_ERROR(("%s(): Fail to create frame. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect, 
                      0,
                      0,
                      NAV_VIA_ANIM_FRAME_WIDTH,
                      NAV_VIA_ANIM_FRAME_HEIGHT);

    i4_ret = c_wgl_create_widget(pt_view->h_anim_frame,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_g_img_icon);
    if (i4_ret != NAVR_OK)
    {
        DBG_ERROR(("\n%s,%dFailed to create icon\n",
                   __FILE__, __LINE__));
    }

    i4_ret = c_wgl_do_cmd(h_g_img_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    NAV_LOG_ON_FAIL(i4_ret);

    h_g_img_animation[0] = h_g_wdk_img_loading_icon_1;
    h_g_img_animation[1] = h_g_wdk_img_loading_icon_2;
    h_g_img_animation[2] = h_g_wdk_img_loading_icon_3;
    h_g_img_animation[3] = h_g_wdk_img_loading_icon_4;
    h_g_img_animation[4] = h_g_wdk_img_loading_icon_5;
    h_g_img_animation[5] = h_g_wdk_img_loading_icon_6;
    h_g_img_animation[6] = h_g_wdk_img_loading_icon_7;
    h_g_img_animation[7] = h_g_wdk_img_loading_icon_8;
    h_g_img_animation[8] = h_g_wdk_img_loading_icon_9;
    h_g_img_animation[9] = h_g_wdk_img_loading_icon_10;
    h_g_img_animation[10] = h_g_wdk_img_loading_icon_11;
    h_g_img_animation[11] = h_g_wdk_img_loading_icon_12;

    c_memset(&t_img_info, 0, sizeof(t_img_info));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_g_img_animation[0];
    t_img_info.u_img_data.t_standard.t_enable = h_g_img_animation[0];
    t_img_info.u_img_data.t_standard.t_highlight = h_g_img_animation[0];
    
    i4_ret = c_wgl_do_cmd(h_g_img_icon,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_img_info));

    i4_ret = c_wgl_set_visibility(h_g_img_icon, WGL_SW_HIDE);
    NAV_LOG_ON_FAIL(i4_ret);

    return NAVR_OK;
}

static INT32 _nav_via_dlg_view_create(NAV_VIA_DLG_VIEW_T* pt_this)
{

    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    GL_COLOR_T          t_color_text = NAV_COLOR(NAV_COLOR_ID_TEXT);
    WGL_FONT_INFO_T     t_fnt_info;
    UINT32              ui4_canvas_w, ui4_canvas_h;
    HANDLE_T            h_canvas = pt_this->h_canvas;

    nav_get_ui_canvas_size(&ui4_canvas_w, &ui4_canvas_h);
    
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      ((ui4_canvas_w - NAV_VIA_DLG_FRAME_WIDTH) / 2),
                      ((ui4_canvas_h - NAV_VIA_DLG_FRAME_HEIGHT) / 2),
                      NAV_VIA_DLG_FRAME_WIDTH,
                      NAV_VIA_DLG_FRAME_HEIGHT
                       );

    /* create dialog frame */
    i4_ret = c_wgl_create_widget(h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _nav_via_dlg_default_msg_proc,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                                 NULL,
                                 &pt_this->h_frame);
    if(i4_ret < 0)
    {
        DBG_ERROR(("%s(): Fail to create frame. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }    
    
    SET_RECT_BY_SIZE(&t_rect, 0, 0, NAV_VIA_DLG_FRAME_WIDTH, NAV_VIA_DLG_FRAME_HEIGHT);

    /* create text */
    i4_ret = c_wgl_create_widget(pt_this->h_frame,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MULTILINE
                                        |WGL_STL_TEXT_MAX_512
                                        |WGL_STL_TEXT_MAX_DIS_5_LINE),
                                 NULL,
                                 &pt_this->h_text);
    NAV_CHK_FAIL(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd (pt_this->h_text,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_CENTER_CENTER),
                              NULL);
    NAV_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(&t_fnt_info, 0, sizeof(t_fnt_info));

    t_fnt_info.e_font_size = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap = FE_CMAP_ENC_UNICODE;
    c_strncpy(&(t_fnt_info.a_c_font_name[0]), NAV_FONT_NORMAL, WGL_MAX_FONT_NAME);
    
    i4_ret = c_wgl_do_cmd (pt_this->h_text,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    NAV_CHK_FAIL(i4_ret);

    /* txt color */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_color_text;
    t_clr_info.u_color_data.t_standard.t_highlight = t_color_text;
    t_clr_info.u_color_data.t_standard.t_disable = t_color_text;
    i4_ret = c_wgl_do_cmd(pt_this->h_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    NAV_CHK_FAIL(i4_ret);

    /* set background image*/
    if (NULL_HANDLE == pt_this->h_img_bk)
    {
        i4_ret = nav_img_create_scr_svr_bk_img_tpl(&pt_this->h_img_bk);
		if(i4_ret < 0)
	    {
	        DBG_ERROR(("%s(): Fail to nav_img_create_scr_svr_bk_img_tpl = %d\r\n", __FUNCTION__, i4_ret));
	    }  
    }

    c_memset (&t_img_info, 0, sizeof(t_img_info));
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_this->h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_this->h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_this->h_img_bk;

    i4_ret = c_wgl_do_cmd(pt_this->h_text,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if(i4_ret < 0)
    {
        DBG_ERROR(("%s(): Fail to set frame's bk-image. i4_ret = %d\r\n", __FUNCTION__, i4_ret));
        return NAVR_FAIL;
    }
        
    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_RECURSIVE);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_frame, WGL_SW_HIDE);
    NAV_CHK_FAIL(i4_ret);

    i4_ret = c_timer_create(&pt_this->h_hide_timer);
	NAV_LOG_ON_FAIL(i4_ret);
    i4_ret = c_timer_create(&pt_this->h_anim_timer);
	NAV_LOG_ON_FAIL(i4_ret);

    i4_ret = _nav_via_dlg_create_warning_dialog();
    NAV_CHK_FAIL(i4_ret);
    
    return NAVR_OK;
}

static INT32 _nav_via_dlg_view_init_ui()
{
    INT32                   i4_ret = NAVR_OK;
    NAV_VIA_DLG_VIEW_T*     pt_view = &t_g_nav_via_dlg_view;

    do {
        i4_ret = _nav_via_dlg_view_create(pt_view);  

        if (i4_ret != 0)
        {
            break;
        }
        
        i4_ret = _nav_via_dlg_animation_icon_create();

        if (NAVR_OK == i4_ret)
        {
            pt_view->b_ui_inited = TRUE;
            return i4_ret;
        }
    }while(0);
    
    _nav_via_dlg_view_deinit();

    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_via_dlg_view_init
 * Description:
 *      usb plugin detection view initialization.
 * Input arguments:
 *      pt_ctrl         pointer to struct _NAV_VIA_DLG_HDLR_T
 *      h_canvas        canvas handle
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_view_init(
                    NAV_VIA_DLG_HDLR_T*         pt_ctrl,
                    HANDLE_T                    h_canvas)
{
    NAV_VIA_DLG_VIEW_T*      pt_view = &t_g_nav_via_dlg_view;

    pt_view->pt_ctrl = pt_ctrl;
    pt_view->h_canvas = h_canvas;
    pt_view->h_img_bk = NULL_HANDLE;
    pt_view->ui4_time_delay = NAV_VIA_DLG_DEFAULT_TIMER_DELAY;
    pt_view->b_is_show = FALSE;
    pt_view->b_ui_inited = FALSE;
    pt_view->ui2_show_msg_id = MLM_NAV_KEY_NAV_VIA_DLG_MSG;
    pt_view->h_anim_timer = NULL_HANDLE;
    pt_view->h_anim_frame = NULL_HANDLE;
    
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_view_deinit
 * Description:
 *      usb plugin detection view deinitialization.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_view_deinit (VOID)
{
    INT32                    i4_ret = NAVR_OK;
    NAV_VIA_DLG_VIEW_T*      pt_this = &t_g_nav_via_dlg_view;

    /*free timer*/
    if (TRUE == c_handle_valid(pt_this->h_hide_timer))
    {
        i4_ret = c_timer_delete(pt_this->h_hide_timer);
        pt_this->h_hide_timer = NULL_HANDLE;
        RET_ON_ERR(i4_ret);
    }    

    /*free timer*/
    if (TRUE == c_handle_valid(pt_this->h_anim_timer))
    {
        i4_ret = c_timer_delete(pt_this->h_anim_timer);
        pt_this->h_anim_timer = NULL_HANDLE;
        RET_ON_ERR(i4_ret);
    }   

    /*free widget*/
    if(TRUE == c_handle_valid(pt_this->h_text))
    {
        c_wgl_destroy_widget(pt_this->h_text);
    }

    /*free frame*/
    if(TRUE == c_handle_valid(pt_this->h_frame))
    {
        c_wgl_destroy_widget(pt_this->h_frame);
    }

    /*free images*/
    if(TRUE == c_handle_valid(pt_this->h_img_bk))
    {
        c_wgl_img_tpl_destroy(pt_this->h_img_bk);
    }

    /* free icon */
    if(TRUE == c_handle_valid(h_g_img_icon))
    {
        c_wgl_destroy_widget(h_g_img_icon);
    }

    /*free frame*/
    if(TRUE == c_handle_valid(pt_this->h_anim_frame))
    {
        c_wgl_destroy_widget(pt_this->h_anim_frame);
    }

    /*free frame*/
    if(TRUE == c_handle_valid(pt_this->h_warning_dialog))
    {
        c_wgl_destroy_widget(pt_this->h_warning_dialog);
    }

    pt_this->b_ui_inited = FALSE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_view_hide
 * Description:
 *      hide UI.
 * Input arguments:
 *      None
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_view_hide (VOID)
{
    INT32                    i4_ret = NAVR_OK;
    NAV_VIA_DLG_VIEW_T*      pt_view = &t_g_nav_via_dlg_view;

    if (pt_view->b_is_show == FALSE)
    {
        return NAVR_OK;
    }

    /*hide ui*/
    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, TRUE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_view->h_anim_frame, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(pt_view->h_anim_frame, NULL, TRUE);
    RET_ON_ERR(i4_ret);

    pt_view->b_is_show = FALSE;

    if (MLM_NAV_KEY_WIFI_REMOTE_BATTERY_LEVEL == pt_view->ui2_show_msg_id)
    {
        pt_view->ui2_show_msg_id = MLM_NAV_KEY_NAV_VIA_DLG_MSG;
        a_tv_net_OSD_disapper();
    }

    
    if (MLM_NAV_KEY_NAV_VIA_DLG_WRNNG_MSG == pt_view->ui2_show_msg_id)
    {
        _nav_via_dlg_hide_warning_dialog();
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_view_show
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _nav_via_dlg_view_show ()
{
    INT32                    i4_ret = NAVR_OK;
    UINT8                    ui1_lang_id;
    UTF16_T                  *w2s_title = NULL;
    NAV_VIA_DLG_VIEW_T*      pt_view = &t_g_nav_via_dlg_view;

    if (FALSE == pt_view->b_ui_inited)
    {
        i4_ret = _nav_via_dlg_view_init_ui();
    }
    
    ui1_lang_id = nav_get_mlm_lang_id();

    if(pt_view->ui1_lang_id != ui1_lang_id)
    {
        /*save current lang_id*/
        pt_view->ui1_lang_id = ui1_lang_id;
    }

    if (MLM_NAV_KEY_WIFI_REMOTE_BATTERY_LEVEL == pt_view->ui2_show_msg_id)
    {
        pt_view->ui4_time_delay = NAV_VIA_DLG_DEFAULT_TIMER_DELAY;
        w2s_title = MLM_NAV_TEXT(ui1_lang_id, pt_view->ui2_show_msg_id/*MLM_NAV_KEY_NAV_VIA_DLG_MSG*/);
        
        /*set text*/
        i4_ret = c_wgl_do_cmd(pt_view->h_text,
                              WGL_CMD_TEXT_SET_TEXT,
                              WGL_PACK(w2s_title),
                              WGL_PACK(c_uc_w2s_strlen(w2s_title)));
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_NORMAL);
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_set_focus(pt_view->h_frame, WGL_NO_AUTO_REPAINT);
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, TRUE);
        RET_ON_ERR(i4_ret);

        a_tv_net_OSD_appear();
    }
    else if (MLM_NAV_KEY_NAV_VIA_DLG_WRNNG_MSG == pt_view->ui2_show_msg_id)
    {
        _nav_via_dlg_show_warning_dialog();
        
        if (FALSE == nav_is_component_visible(NAV_COMP_ID_VIA_DLG))
        {
            nav_set_component_visible(NAV_COMP_ID_VIA_DLG);
        }
        
        pt_view->b_is_show = TRUE;

        return NAVR_OK;
    }
    else
    {
        pt_view->ui4_time_delay = NAV_VIA_DLG_YAHOO_STATUS_TIMER_DELAY;
        i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_HIDE);
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_set_focus(pt_view->h_frame, WGL_NO_AUTO_REPAINT);
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, TRUE);
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_view->h_anim_frame, WGL_SW_RECURSIVE);
        NAV_LOG_ON_FAIL(i4_ret);

        //c_wgl_float(h_g_img_icon, TRUE, WGL_NO_AUTO_REPAINT);
    }

    if (FALSE == nav_is_component_visible(NAV_COMP_ID_VIA_DLG))
    {
        nav_set_component_visible(NAV_COMP_ID_VIA_DLG);
    }

    _nav_via_dlg_hide_timer_stop();
    
    _nav_via_dlg_anima_timer_start();
    _nav_via_dlg_hide_timer_start();

    pt_view->b_is_show = TRUE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _nav_via_dlg_view_is_key_handler
 * Description:
 *
 * Input arguments:
 *      UINT32
 * Output arguments:
 *      None
 * Returns:
 *      TRUE        Successful
 *      FALSE       Fail
 *---------------------------------------------------------------------------*/
static BOOL _nav_via_dlg_view_is_key_handler (UINT32     ui4_key_code)
{
#ifdef APP_YAHOO_LOADING_SPINNER_SUPPORT
    extern BOOL a_msg_convert_is_yahoo_ready(VOID);

    if ((BTN_WIDGET == ui4_key_code
        || BTN_AMAZON == ui4_key_code
        || BTN_MGO == ui4_key_code
        || BTN_NETFLIX == ui4_key_code
        || BTN_VUDU == ui4_key_code
        || BTN_IHEART_RADIO == ui4_key_code
        || BTN_WATCHFREE == ui4_key_code
        || BTN_REDBOX == ui4_key_code
        || BTN_HAYSTACK == ui4_key_code)
        && a_msg_convert_is_yahoo_ready() == FALSE)
    {
        return TRUE;
    }
#endif

    if (BTN_CUSTOM_100 == ui4_key_code)
    {
        DBG_LOG_PRINT(("[NAV]line:%d, recv key %x \n", __LINE__, ui4_key_code));
        a_nav_via_dlg_set_show_info(MLM_NAV_KEY_NAV_VIA_DLG_WRNNG_MSG);
        return TRUE;
    }    
    return FALSE; 
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:
 *      nav_via_dlg_view_register_default_hdlr
 * Description:
 *      usb plugin view register.
 * Input arguments:
 *      NAV_VIA_DLG_VIEW_HDLR_T*
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK     Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 nav_via_dlg_view_register_default_hdlr (NAV_VIA_DLG_VIEW_HDLR_T*      pt_view_hdlr)
{
    if (NULL == pt_view_hdlr)
    {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_via_dlg_view_init;
    pt_view_hdlr->pf_deinit         = _nav_via_dlg_view_deinit;
    pt_view_hdlr->pf_hide           = _nav_via_dlg_view_hide;
    pt_view_hdlr->pf_show           = _nav_via_dlg_view_show;
    pt_view_hdlr->pf_is_key_handler = _nav_via_dlg_view_is_key_handler;

    return NAVR_OK;
}

VOID a_nav_via_dlg_set_show_info(UINT16 ui2_msg_id)
{
    NAV_VIA_DLG_VIEW_T*      pt_view = &t_g_nav_via_dlg_view;

    pt_view->ui2_show_msg_id = ui2_msg_id;
}

UINT16 a_nav_via_dlg_get_show_info(VOID)
{
    NAV_VIA_DLG_VIEW_T*      pt_view = &t_g_nav_via_dlg_view;

    return pt_view->ui2_show_msg_id;
}

BOOL a_nav_via_dlg_is_show_warning_dialog(VOID)
{   
    NAV_VIA_DLG_VIEW_T*      pt_view = &t_g_nav_via_dlg_view;
    
    return pt_view->b_is_warning_dialog_show;
}

BOOL a_nav_via_dlg_is_dtv_resuming(VOID)
{       
    return g_b_dtv_is_resuming;
}

