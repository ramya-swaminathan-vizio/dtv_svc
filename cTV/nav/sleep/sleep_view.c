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
 * $RCSfile: sleep_view.c,v $
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
#include "nav/sleep/sleep.h"
#include "nav/nav_common.h"
#include "res/nav/sleep/sleep_view_rc.h"

#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "app_util/a_tv.h"
#include "mmp/a_mmp.h"
#include "c_iom.h"
#include "menu2/menu_page.h"
#include "am/a_am.h"
#include "nav/scrn_blank/a_nav_scrn_blank.h"
#include "wdk/a_wdk.h"

#ifdef APP_TTS_SUPPORT
#include "c_tts.h"
#endif
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)

#ifdef APP_TTS_SUPPORT
#define SLEEP_VIEW_PLAYER_TTS_DELAY_TIME       (450) /* ms */
#endif

typedef struct _NAV_SLEEP_VIEW_T
{
    NAV_SLEEP_T*                pt_ctrl;
    HANDLE_T                    h_frame;
    HANDLE_T                    h_msg;
    HANDLE_T                    h_button;
    BOOL                        b_show;
    HANDLE_T                    h_pre_focus;
    SLEEP_VIEW_RC_T             t_rc;

#ifdef APP_TTS_SUPPORT
    HANDLE_T                    h_tts_sound;        /* for voice prompt */
    TTS_STRING_T                t_sound_content;    /* store sound content to output. */
    HANDLE_T                    h_tts_timer;        /* for tts timer*/
#endif

} NAV_SLEEP_VIEW_T;

static WDK_OSD_TOAST_T      t_g_wdk_view = {0};

static BOOL b_g_sleep_set_OSD_appear;
static HANDLE_T h_iom;
static BOOL b_g_sleep_warnmessage_appear=FALSE;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_SLEEP_VIEW_T t_g_nav_sleep_view = {0};
static NAV_SLEEP_VIEW_T t_g_nav_sleep_prompt_view = {0};
static BOOL ab_g_sleep_prompt[STIMER_NFY_SRC_CNT] = {0};
static VOID _nav_sleep_view_prompt_nfy_fct(VOID* pv_tag1,
                                            VOID* pv_tag2,
                                            VOID* pv_tag3);
static INT32 _nav_sleep_cli_set_sleep_timer
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static CLI_EXEC_T at_g_nav_sleep_cli_cmd_tbl[] =
{
    { "Set_sleep_timer",         "sst", _nav_sleep_cli_set_sleep_timer,              NULL, "Set_sleep_timer",                 NAV_CLI_ACCESS_RIGHT_LVL },
    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T t_g_nav_sleep_cli_cmd_entry =
{
    "nav_sleep", NULL, NULL, at_g_nav_sleep_cli_cmd_tbl, "nav sleep", NAV_CLI_ACCESS_RIGHT_LVL
};

static INT32 _nav_sleep_cli_set_sleep_timer
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    DBG_INFO(("\n[NAV_SLEEP]_nav_sleep_cli_set_sleep_timer\n"));

    a_sleep_timer_start(90);
    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_toast_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_toast_view_init(HANDLE_T  h_canvas)
{
    WDK_TOAST_PARAM_T     t_widget_param;
    INT32                 i4_ret = NAVR_OK;

    c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));

    t_widget_param.e_toast_style = WDK_WARNING_TOAST;

    i4_ret = a_wdk_toast_init(h_canvas, (VOID*)(&t_widget_param), &t_g_wdk_view);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      scrn_svr_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_toast_view_deinit(VOID)
{
    a_wdk_toast_deinit(&t_g_wdk_view);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_toast_view_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_toast_view_show(
                    UTF16_T*                    pw2s_string
                    )
{
    WDK_TOAST_PARAM_T     t_widget_param;
    INT32                 i4_ret = NAVR_OK;
    CHAR                  s_app_name [6] = {0};

    c_memset(&t_widget_param, 0, sizeof(WDK_TOAST_PARAM_T));
    t_widget_param.e_toast_style = WDK_WARNING_TOAST;
    t_widget_param.w2s_str       = (VOID*)pw2s_string;
    t_widget_param.pf_cb         = NULL;

    a_am_get_active_app (s_app_name);
    if (c_strcmp(MMP_NAME, s_app_name) == 0)
    {
       if (c_wgl_float(t_g_wdk_view.h_base_frm, TRUE, FALSE) != WGLR_OK)
        {
            DBG_INFO(("DEBUG!!!c_wgl_float fail!\n"));
        }
    }

    i4_ret = a_wdk_toast_activate(FALSE, (VOID*)(&t_widget_param), &t_g_wdk_view);
    b_g_sleep_warnmessage_appear = TRUE;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_toast_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_toast_view_hide(VOID)
{
    INT32                 i4_ret = NAVR_OK;
    CHAR                  s_app_name [6] = {0};

    a_am_get_active_app (s_app_name);
    if (c_strcmp(MMP_NAME, s_app_name) == 0)
    {
       if (c_wgl_float(t_g_wdk_view.h_base_frm, FALSE, FALSE) != WGLR_OK)
        {
            DBG_INFO(("DEBUG!!!c_wgl_float fail!\n"));
        }
    }

    i4_ret = a_wdk_toast_hide(TRUE, NULL,&t_g_wdk_view);
    b_g_sleep_warnmessage_appear = FALSE;

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_sleep_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    switch (ui4_key_code) {
    default:
        return FALSE;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_show
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_show(
                    NAV_SLEEP_VIEW_T*           pt_view,
                    UINT32                      ui4_time
                    )
{
    UTF16_T  w2s_value_string[16+1] = {0};
    UTF16_T  w2s_string[32+1]       = {0};
    SIZE_T   z_len                  = 32;
    INT32    i4_ret;


    i4_ret = a_sleep_timer_get_text(ui4_time, w2s_value_string, z_len);
    if (i4_ret != STIMERR_OK) {
        return NAVR_FAIL;
    }

    c_uc_w2s_strcat(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_TITLE_SLEEP));
    c_uc_w2s_strcat(w2s_string, w2s_value_string);

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
 *      _nav_sleep_view_activate
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    UINT32            ui4_stimer_reason = 0;
    UINT32        ui4_stimer_nfy_src = 0;
    BOOL          b_stimer = 0;

#if 0
    i4_ret = a_sleep_timer_get_remaining_time(&ui4_sleep_time);
    if (i4_ret != STIMERR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _nav_sleep_view_show(pt_view, ui4_sleep_time);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_view->h_frame, WGL_NO_AUTO_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    nav_sleep_reset_timer(pt_view->pt_ctrl, SLEEP_TIMEOUT);
#endif

    a_nav_sleep_timer_get_sleep_reason(&ui4_stimer_reason,&b_stimer,&ui4_stimer_nfy_src);

    _nav_sleep_view_prompt_nfy_fct((VOID*)(UINT32) ui4_stimer_reason,
                                            (VOID*)(UINT32)NULL,
                                            (VOID*)(UINT32)ui4_stimer_nfy_src);

#ifdef APP_TTS_SUPPORT
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;
    INT32             i4_ret;
      /* get an instance of sound player. */
      if ((pt_view->h_tts_sound) == NULL_HANDLE)
      {
        DBG_INFO(("tts sound %d \n",__LINE__));

          i4_ret = c_tts_open_default_instance_fct(&(pt_view->h_tts_sound));
          if (i4_ret != OSR_OK)
          {
                DBG_INFO(("{sleep}ERROR(%d): c_tts_open_default_instance_fct fail! i4_ret=%d.\n",__LINE__,i4_ret));
                return NAVR_FAIL;
          }
          DBG_INFO(("line = %d, tts sound= %d \n",__LINE__,pt_view->h_tts_sound));

      }
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_hide(
                    VOID
                    )
{
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;
    INT32             i4_ret;

    _warning_toast_view_hide();

    i4_ret = c_wgl_set_visibility(pt_view->h_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
#ifdef APP_MENU_MMP_COEXIST
    if((a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)||
        (a_mmp_get_ap_status() ==MMP_MAIN_AP_STATUS_RESUMED))
#endif
    {
        c_wgl_set_focus(pt_view->h_pre_focus,TRUE);
    }

#ifdef APP_TTS_SUPPORT
    /* stop to read sleep when details hided. */
    c_tts_stop_fct(pt_view->h_tts_sound);
#endif

    pt_view->b_show = FALSE;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _nav_sleep_view_rcu_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    NAV_SLEEP_VIEW_T* pt_view          = &t_g_nav_sleep_view;
    UINT8             ui1_idx          = 0;
    UINT32            ui4_sleep_time   = 0;
    INT32             i4_ret;

    switch(ui4_key_code) {
    case BTN_SLEEP:
        nav_sleep_reset_timer(pt_view->pt_ctrl, SLEEP_TIMEOUT);

        i4_ret = a_sleep_timer_iterate(STIMER_ITERATE_DIR_NEXT, &ui1_idx, &ui4_sleep_time);
        if (i4_ret != STIMERR_OK) {
            break;
        }

        i4_ret = _nav_sleep_view_show(pt_view, ui4_sleep_time);
        if (i4_ret != NAVR_OK) {
            break;
        }
        break;
    default:
        nav_rcu_key_handler(ui4_key_code);
        break;
    }
}
/*---------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_frame_nfy_fct(
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32 i4_ret;

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:
        _nav_sleep_view_rcu_key_handler((UINT32)pv_param1);  /* key code */
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


/*----------------------------------------------------------------------------
 * Name: _nav_sleep_promp_msg_btn_fct
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
 static INT32 _nav_sleep_promp_msg_btn_fct(HANDLE_T  h_widget,
                                                   UINT32      ui4_msg,
                                                   VOID*       pv_param1,
                                                   VOID*       pv_param2)
{
    UINT32      ui4_keycode = (UINT32)pv_param1;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        if (t_g_nav_sleep_prompt_view.b_show)
        {
            a_sleep_timer_stop();
            nav_hide_component(NAV_COMP_ID_SLEEP);
            //nav_return_activation(NAV_COMP_ID_SLEEP);
            nav_rcu_key_handler(ui4_keycode);
        }
    }
    return  c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);

}

/*-----------------------------------------------------------------------------
 * Name
 *      _screen_mode_view_set_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_set_skin(
                    NAV_SLEEP_VIEW_T*           pt_view
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
    t_inset.i4_left   = SLEEP_MSG_LEFT_INSET;
    t_inset.i4_right  = SLEEP_MSG_RIGHT_INSET;
    t_inset.i4_top    = SLEEP_MSG_TOP_INSET;
    t_inset.i4_bottom = SLEEP_MSG_BOTTOM_INSET;

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
                    (VOID*)SLEEP_MSG_ALIGNMENT,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }


    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable   = pt_view->t_rc.h_btn_img_bk_hlt;
    t_img_info.u_img_data.t_extend.t_enable    = pt_view->t_rc.h_btn_img_bk_hlt;
    t_img_info.u_img_data.t_extend.t_highlight = pt_view->t_rc.h_btn_img_bk_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = pt_view->t_rc.h_btn_img_bk_hlt;
    t_img_info.u_img_data.t_extend.t_push = pt_view->t_rc.h_btn_img_bk_hlt;
    t_img_info.u_img_data.t_extend.t_push_unhighlight = pt_view->t_rc.h_btn_img_bk_hlt;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_button,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(i4_ret != WGLR_OK){
        //return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_prompt_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_sleep_view_prompt_nfy_fct(VOID* pv_tag1,
                                            VOID* pv_tag2,
                                            VOID* pv_tag3)
{
    INT32 i4_ret;
    NAV_SLEEP_VIEW_T* pt_prompt_view = &t_g_nav_sleep_prompt_view;
    STIMER_REASON e_reason =  (STIMER_REASON)(UINT32)pv_tag1;
    STIMER_NFY_SRC e_nfy_src = (STIMER_NFY_SRC)(UINT32)pv_tag3;
    char                  ac_app_name[APP_NAME_MAX_LEN] = {0};

    if (e_nfy_src >= STIMER_NFY_SRC_CNT)
    {
        return;
    }

    ab_g_sleep_prompt[e_nfy_src] = (e_reason == STIMER_REASON_EXPIRE_SOON) ? TRUE : FALSE;

    if (ab_g_sleep_prompt[STIMER_NFY_SRC_NAV] ||
        ab_g_sleep_prompt[STIMER_NFY_SRC_AUTO_SLEEP])
    {
        a_scrn_blank_act((VOID*)SCRN_BLANK_CONTEXT_SWITCH_4_RESET,NULL, NULL);

        DBG_INFO(("\n[SLEEP_TEST] _nav_sleep_view_prompt_nfy_fct SLEEP_TIMER_DLG[SHOW CASE1]\n"));
#ifdef APP_MENU_MMP_COEXIST

        if((a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED) &&
           (a_mmp_get_ap_status() != MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC) &&
           (a_mmp_get_ap_status() !=MMP_MAIN_AP_STATUS_RESUMED))
#else
        if(a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
#endif
        {
            a_tv_net_send_cmd("\n:dtv_app_mtk,yahoo,:ui_show=yes\n"); //DTV00598056
            //c_wgl_set_focus(pt_prompt_view->h_button, FALSE);
            //c_wgl_repaint(pt_prompt_view->h_frame, NULL, IS_SYNC_REPAINT);
            DBG_INFO(("\n[SLEEP_TEST] _nav_sleep_view_prompt_nfy_fct tv_svc_status[%d]\n",
                       a_tv_net_get_tv_svc_status()));

            _warning_toast_view_show(MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_SLEEP_TIMER_DLG));

            pt_prompt_view->b_show = TRUE;

            if(a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
            {
                a_tv_net_OSD_appear();
                b_g_sleep_set_OSD_appear = TRUE;
            }
            else
            {
                b_g_sleep_set_OSD_appear = FALSE;
            }

            a_tv_net_disable_keyroute(TRUE);
        }
        else
        {
            a_tv_net_send_cmd("\n:dtv_app_mtk,yahoo,:ui_show=yes\n"); //DTV00598056
            //c_wgl_float(pt_prompt_view->h_frame, TRUE, WGL_SYNC_AUTO_REPAINT);
            c_wgl_get_focus(&pt_prompt_view->h_pre_focus);
            //c_wgl_set_focus(pt_prompt_view->h_button, TRUE);

            DBG_INFO(("\n[SLEEP_TEST] _nav_sleep_view_prompt_nfy_fct SLEEP_TIMER_DLG[SHOW CASE2]\n"));
            _warning_toast_view_show(MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_SLEEP_TIMER_DLG));

            pt_prompt_view->b_show = TRUE;
            if(a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
            {
                i4_ret = a_am_get_active_app (ac_app_name);
                if (i4_ret != WGLR_OK)
                {
                    return;
                }
                /* If menu is showing, when 3rd app fullscreen  and sleep timer dialog show then pause menu. */
                /* Because sleep dialog is nav comp so can't control the two focus on menu and sleep dialog */
                /*And it may have other problem */
                if(0 == c_strcmp(ac_app_name, MENU_NAME))
                {
                    a_amb_pause_app(MENU_NAME);
                }
                a_tv_net_OSD_appear();
                b_g_sleep_set_OSD_appear = TRUE;
            }
            else
            {
                b_g_sleep_set_OSD_appear = FALSE;
            }
            a_tv_net_disable_keyroute(TRUE);
        }
    }
    else
    {
        if (pt_prompt_view->b_show == TRUE)
        {
            i4_ret = c_wgl_set_visibility(pt_prompt_view->h_frame, WGL_SW_HIDE);
            if (i4_ret != WGLR_OK){
                return ;
            }
            a_scrn_blank_act((VOID*)SCRN_BLANK_CONTEXT_SWITCH_4_RESET,NULL, NULL);

            c_wgl_repaint(pt_prompt_view->h_frame, NULL, IS_SYNC_REPAINT);
            pt_prompt_view->b_show = FALSE;

            if(a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
            {
                c_wgl_set_focus(pt_prompt_view->h_pre_focus, TRUE);
            }
            if(b_g_sleep_set_OSD_appear == TRUE)
            {
                a_tv_net_OSD_disapper();
            }
            a_nav_sleep_timer_set_sleep_reason(e_reason,FALSE, e_nfy_src);
            a_tv_net_disable_keyroute(FALSE);
        }
    }
  #ifdef APP_TTS_SUPPORT
  if(e_reason == STIMER_REASON_EXPIRE_SOON)
    {
          UTF16_T*  pw2s_tts_text = NULL;
          pw2s_tts_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_SLEEP_TIMER_DLG);
          a_app_tts_play(pw2s_tts_text, c_uc_w2s_strlen(pw2s_tts_text));
          // _nav_sleep_reset_tts_timer(pt_view, pw2s_text);
    }
#endif

    //c_wgl_img_cache_flush();
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_active_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_sleep_view_active_nfy_fct(VOID* pv_tag1,
                                                VOID* pv_tag2,
                                                VOID* pv_tag3)

{
     DBG_INFO(("\n[SLEEP_TEST] _nav_sleep_view_active_nfy_fct\n"));
#ifdef APP_MENU_MMP_COEXIST

    if((a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED) &&
       (a_mmp_get_ap_status() != MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC) &&
       (a_mmp_get_ap_status() !=MMP_MAIN_AP_STATUS_RESUMED))
#else
    if(a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
#endif
    {
        DBG_INFO(("\n[SLEEP_TEST] _nav_sleep_view_active_nfy_fct [case1]\n"));
        if (FALSE == nav_is_active())
        {

            DBG_INFO(("\n[SLEEP_TEST] _nav_sleep_view_active_nfy_fct [case2]\n"));
            nav_resume_self();
        }
        a_nav_sleep_timer_set_sleep_reason((UINT32)pv_tag1,TRUE,(UINT32)pv_tag3);
        nav_grab_activation(NAV_COMP_ID_SLEEP);
        return;
    }

    DBG_INFO(("\n[SLEEP_TEST] _nav_sleep_view_active_nfy_fct [case3]\n"));

    a_nav_sleep_timer_set_sleep_reason((UINT32)pv_tag1,TRUE,(UINT32)pv_tag3);
    /*just show dialog so no need active the sleep timer comp otherwise it may affect the sleep list box */
    _nav_sleep_view_prompt_nfy_fct((VOID*)(UINT32) pv_tag1,
                                            (VOID*)(UINT32)NULL,
                                            (VOID*)(UINT32)pv_tag3);
    //nav_grab_activation(NAV_COMP_ID_SLEEP);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_timer_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_sleep_view_timer_nfy_fct(HANDLE_T  h_timer,
                                          VOID*     pv_tag)
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_sleep_view_active_nfy_fct,
                               (VOID*)(UINT32)STIMER_REASON_EXPIRE_SOON,
                               pv_tag, (VOID*)(UINT32)STIMER_NFY_SRC_AUTO_SLEEP);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_btn_proc_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_sleep_btn_proc_fct(VOID* pv_tag1,
                                                VOID* pv_tag2,
                                                VOID* pv_tag3)
{
    UINT32         ui4_key_code = IOM_GET_EVT_GRP_ID((UINT32)pv_tag1);

    if (t_g_nav_sleep_prompt_view.b_show)
    {
        DBG_INFO(("\n[NAV_SLEEP] _nav_sleep_btn_proc_fct [KEY]\n"));
        a_nav_sleep_hide_toast_warning();
        a_sleep_timer_stop();

        if((a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_RESUMED)||
            (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC) ||
            (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED))
        {
            return;
        }

        nav_hide_component(NAV_COMP_ID_SLEEP);
#if 0
        //nav_return_activation(NAV_COMP_ID_SLEEP);
        nav_rcu_key_handler(ui4_key_code);
#endif
    }

        switch(ui4_key_code)
        {
             case BTN_VOL_DOWN:
             case BTN_VOL_UP:
             {
                       if(b_g_sleep_warnmessage_appear)
                       {
                          a_sleep_timer_stop();
                          break;
                       }
              }
              break;

              default:
                break;
        }
    return ;
}

/*-----------------------------------------------------------------------------
 * Name: _iom_nfy_fct
 *
 * Description: This callback function will be called by the IO Manager when
 *              system events are triggered from the remote control.
 *
 * Inputs:  pv_nfy_tag      Contains a tag value.
 *          e_nfy_cond      Contains the notify condition.
 *          ui4_evt_code    Contains the event code.
 *          ui4_data        Contains information related to the event.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _iom_nfy_fct (VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data)
{
    if(FALSE == t_g_nav_sleep_prompt_view.b_show)
    {
        return;
    }

    if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
         nav_request_context_switch(_nav_sleep_btn_proc_fct,
                                            (VOID*)ui4_evt_code,
                                            (VOID*)e_nfy_cond,
                                            (VOID*)NULL);
    }
    return;
}



/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_init(
                    NAV_SLEEP_T*                pt_ctrl,
                    HANDLE_T                        h_canvas,
                    INT32                           i4_frame_x_offset,
                    INT32                           i4_frame_y_offset,
                    UINT8                           ui1_elem_num)
{
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;
    NAV_SLEEP_VIEW_T* pt_prompt_view = &t_g_nav_sleep_prompt_view;
    WGL_COLOR_INFO_T t_clr_info;
    GL_RECT_T         t_rect;
    INT32             i4_ret;
    UINT32              ui4_style = 0;
    IRRC_SETTING_T  t_irrc_setting;

    pt_view->pt_ctrl = pt_ctrl;

    i4_ret = sleep_view_init_rc(&pt_view->t_rc);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* create frame */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    i4_frame_x_offset + SLEEP_FRAME_LEFT,
                    i4_frame_y_offset + SLEEP_FRAME_TOP,
                    SLEEP_FRAME_WIDTH,
                    SLEEP_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _nav_sleep_view_frame_nfy_fct,
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
                    SLEEP_MSG_LEFT,
                    SLEEP_MSG_TOP,
                    SLEEP_MSG_WIDTH,
                    SLEEP_MSG_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frame,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32|WGL_STL_TEXT_SMART_CUT|WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_msg
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = _nav_sleep_view_set_skin(pt_view);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_show(pt_view->h_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }



    /* prompt msg*/

    i4_ret = sleep_view_init_rc(&pt_prompt_view->t_rc);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }


    /* create frame */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    i4_frame_x_offset + SLEEP_PROMPT_FRAME_LEFT,
                    i4_frame_y_offset + SLEEP_PROMPT_FRAME_TOP,
                    SLEEP_PROMPT_FRAME_WIDTH,
                    SLEEP_PROMPT_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    NULL,
                    NULL,
                    &pt_prompt_view->h_frame
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* create text */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    SLEEP_PROMPT_MSG_LEFT,
                    SLEEP_PROMPT_MSG_TOP,
                    SLEEP_PROMPT_MSG_WIDTH,
                    SLEEP_PROMPT_MSG_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_prompt_view->h_frame,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_128|WGL_STL_TEXT_SMART_CUT|WGL_STL_GL_NO_IMG_UI|WGL_STL_GL_NO_BK|WGL_STL_TEXT_MULTILINE),
                    NULL,
                    &pt_prompt_view->h_msg
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* create button */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    SLEEP_PROMPT_BTN_LEFT,
                    SLEEP_PROMPT_BTN_TOP,
                    SLEEP_PROMPT_BTN_WIDTH,
                    SLEEP_PROMPT_BTN_HEIGHT
                    );

    i4_ret = c_wgl_create_widget(
                    pt_prompt_view->h_frame,
                    HT_WGL_WIDGET_BUTTON,
                    WGL_CONTENT_BUTTON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _nav_sleep_promp_msg_btn_fct,
                    240,
                    (VOID*)ui4_style,
                    NULL,
                    &pt_prompt_view->h_button
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set button color */
    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable             = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_disable            = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_highlight          = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_push               = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = pt_view->t_rc.t_msg_fg;

    i4_ret = c_wgl_do_cmd(
                    pt_prompt_view->h_button,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }


    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable       = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_disable      = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_highlight    = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_push         = pt_view->t_rc.t_msg_fg;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = pt_view->t_rc.t_msg_fg;

    i4_ret = c_wgl_do_cmd(
                    pt_prompt_view->h_button,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set button font */
    i4_ret = c_wgl_do_cmd(
                    pt_prompt_view->h_button,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)pt_view->t_rc.pt_msg_font,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set title align */
    i4_ret = c_wgl_do_cmd(
                    pt_prompt_view->h_button,
                    WGL_CMD_BTN_SET_ALIGN,
                    WGL_PACK(WGL_AS_CENTER_CENTER),
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = _nav_sleep_view_set_skin(pt_prompt_view);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_show(pt_prompt_view->h_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    _warning_toast_view_init(h_canvas);

    /* IOM Init */
     c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
     t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
     t_irrc_setting.b_notify_raw_data        = TRUE;
     t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
     t_irrc_setting.t_rpt_evt_itvl.ui2_other = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
     i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                          IOM_DEV_ID_ANY,
                          NULL,
                          (VOID*) & t_irrc_setting,
                          NULL,
                          _iom_nfy_fct,
                          &h_iom);

    a_sleep_timer_reg_prompt_nfy(_nav_sleep_view_prompt_nfy_fct,
                                 _nav_sleep_view_timer_nfy_fct);


#ifdef CLI_SUPPORT
        nav_register_comp_cli_entry (&t_g_nav_sleep_cli_cmd_entry);
#endif

#ifdef APP_TTS_SUPPORT
    i4_ret = c_timer_create(&(pt_view->h_tts_timer));
    if (i4_ret != OSR_OK)
    {
        return NAVR_FAIL;
    }
    /* set tts handle to NULL. */
    pt_view->h_tts_sound = NULL_HANDLE;
    pt_view->t_sound_content.ui4_id = 1;    /* init id is 1, then add 1 each time play sound. */
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_sleep_view_deinit(
                    VOID
                    )
{
    NAV_SLEEP_VIEW_T* pt_view = &t_g_nav_sleep_view;

    _warning_toast_view_deinit();

    c_wgl_destroy_widget(pt_view->h_frame);
    c_wgl_destroy_widget(pt_view->h_msg);
    sleep_view_deinit_rc(&pt_view->t_rc);

    pt_view->pt_ctrl  = NULL;
    pt_view->h_frame  = NULL_HANDLE;
    pt_view->h_msg    = NULL_HANDLE;

#ifdef APP_TTS_SUPPORT
    if (c_handle_valid(pt_view->h_tts_timer) == TRUE)
    {
        c_timer_delete(pt_view->h_tts_timer);
    }
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_sleep_view_register_default_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_sleep_view_register_default_hdlr(
                    NAV_SLEEP_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _nav_sleep_view_init;
    pt_view_hdlr->pf_deinit         = _nav_sleep_view_deinit;
    pt_view_hdlr->pf_is_key_handler = _nav_sleep_view_is_key_handler;
    pt_view_hdlr->pf_activate       = _nav_sleep_view_activate;
    pt_view_hdlr->pf_hide           = _nav_sleep_view_hide;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
 VOID a_nav_get_sleep_prompt_dlg_status(BOOL* pb_dlg_show)
{
    NAV_SLEEP_VIEW_T* pt_prompt_view = &t_g_nav_sleep_prompt_view;

    *pb_dlg_show = pt_prompt_view->b_show;
}

VOID a_nav_sleep_hide_toast_warning(VOID)
{
    NAV_SLEEP_VIEW_T* pt_prompt_view = &t_g_nav_sleep_prompt_view;

    if (pt_prompt_view->b_show == TRUE)
    {
          DBG_INFO(("\n[NAV_SLEEP] a_nav_sleep_hide_toast_warning\n"));
         _warning_toast_view_hide();

         a_tv_net_disable_keyroute(FALSE);

         pt_prompt_view->b_show = FALSE;
    }
}

VOID sleep_timer_view_hide(VOID)
{
    _nav_sleep_view_hide();

    return ;
}

#endif
