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
 * $RCSfile: pwd_dlg.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#include "c_wgl.h"
#include "u_irrc_btn_def.h"
#include "c_uc_str.h"
#include "c_handle.h"

#include "app_client.h"
#include "am/a_am.h"
#include "app_util/a_cfg.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "menu2/a_menu.h"
#include "nav/pwd_dlg/pwd_dlg.h"
#include "res/nav/nav_variant.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "msgconvert/msgconvert.h"

#include "res/menu2/menu_custom.h"
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif
#include "nav/twinkle_msg/scrn_svr.h"


#ifndef APP_NO_PWD_DLG

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#ifndef NAV_PWD_DLG_CHK_TIMER_DELAY
#define NAV_PWD_DLG_CHK_TIMER_DELAY 800
#endif

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
PWD_DLG_T t_g_pwd_dlg;
static BOOL b_is_tmp_unlock = FALSE;
static BOOL b_is_handle_timeout = FALSE;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_hide_widget(
                    PWD_DLG_T*                  pt_this
                    );
static INT32 _pwd_dlg_show_pwd_box(
                    PWD_DLG_T*                  pt_this
                    );
static BOOL _pwd_dlg_check_pwd(
                    UTF16_T*                    w2s_pwd
                    );
static VOID _pwd_dlg_stop_timer(
                    PWD_DLG_T*                  pt_this
                    );
static VOID _pwd_dlg_reset_timer(
                    PWD_DLG_T*                  pt_this
                    );
static VOID _pwd_dlg_handle_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
static VOID _pwd_dlg_handle_chk_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
static VOID _pwd_dlg_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    );
static BOOL _pwd_is_able_to_activate(VOID);

#if 0
static VOID _pwd_dlg_delay_show_banner(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
#endif
static VOID _pwd_dlg_cfg_vchip_nfy_fct(
    UINT16                      ui2_nfy_id,
    VOID*                       pv_tag,
    UINT16                      ui2_id);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    PWD_DLG_T* pt_this = &t_g_pwd_dlg;
    INT32      i4_ret;
    b_is_handle_timeout = TRUE;

    pt_this->b_pwd_osd_on              = FALSE;
    pt_this->b_pwd_box_on              = FALSE;
    pt_this->b_delay_return_activation = FALSE;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_create(&(pt_this->h_chk_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = pwd_dlg_view_init(
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    pt_ctx->t_gui_res.e_color_type
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_VCHIP,
                              NULL,
                              _pwd_dlg_cfg_vchip_nfy_fct,
                              &pt_this->ui2_acfg_nfy_id);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_deinit(VOID)
{
    PWD_DLG_T* pt_this = &t_g_pwd_dlg;
    INT32      i4_ret;

    i4_ret = c_timer_delete(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_delete(pt_this->h_chk_timer);
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = pwd_dlg_view_deinit();
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    pt_this->b_pwd_osd_on   = FALSE;
    pt_this->b_pwd_box_on   = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _pwd_dlg_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    switch(ui4_key_code) {
    case BTN_SELECT:
    case BTN_PAUSE:
    case BTN_PLAY:
        switch(nav_get_locked_status(pt_ctx->t_svc_res.e_focus_tv_win_id)) {
        case LOCKED_STATUS_PROGRAM_RATING:
        case LOCKED_STATUS_CHANNEL_LOCKED:
        case LOCKED_STATUS_INP_SRC_LOCKED:
            nav_enable_key_traffic_auto_ctrl(50);
            return TRUE;
        default:
            break;
        }
        break;
    default:
        break;
    }
    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    PWD_DLG_T*          pt_this = &t_g_pwd_dlg;
    INT32               i4_ret;
    ISL_REC_T           pt_isl_rec = {0};
    SVC_BLOCK_COND_T    e_block_cond;
    SIZE_T              z_get_info_size = sizeof(BOOL);
    BOOL                b_is_blocked     = FALSE;

    i4_ret = c_svctx_get(
        menu_get_crnt_svctx(),
        SVCTX_COMMON_GET_TYPE_IS_BLOCK,
        &b_is_blocked,
        &z_get_info_size
    );

    DBG_LOG_PRINT(("<PWD> FUNCTION:%s,LINE:%d,b_is_blocked:%d \n",__FUNCTION__,__LINE__,b_is_blocked));


    if(i4_ret != MENUR_OK)
    {
        DBG_LOG_PRINT((" <PWD> c_svctx_get failed!"));
    }


    pt_this->e_focus_tv_win_id = pt_ctx->t_svc_res.e_focus_tv_win_id;

    if (pt_this->b_pwd_osd_on == TRUE) {
        return NAVR_OK;
    }

    if (b_is_blocked == FALSE)
    {
        return NAVR_OK;
    }


#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_BANNER));
#endif
    pwd_dlg_view_load_msgs(nav_get_mlm_lang_id());

    a_nav_ipts_get_crnt_isl_rec(&pt_isl_rec);
    //if TV source show the password box, if COMP source and have signal show the password box
    if(((a_nav_ipts_is_tv_source(&pt_isl_rec) == TRUE) || (a_nav_ipts_is_comp_source(&pt_isl_rec) == TRUE)) && (nav_is_signal_loss(pt_this->e_focus_tv_win_id) == FALSE))
    {
        DBG_LOG_PRINT(("\n[PASSWORD]only TV source and COMP source can show zhe password box\n"));
        i4_ret = _pwd_dlg_show_pwd_box(pt_this);
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_hide(VOID)
{
    PWD_DLG_T* pt_this = &t_g_pwd_dlg;
    INT32      i4_ret;


    if (pt_this->b_pwd_osd_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    //_pwd_dlg_stop_timer(pt_this);

#ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_BANNER));
#endif
    i4_ret = _pwd_dlg_hide_widget(pt_this);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_timer_start(pt_this->h_chk_timer,
                           NAV_PWD_DLG_CHK_TIMER_DELAY,
                           X_TIMER_FLAG_ONCE,
                           _pwd_dlg_timer_nfy,
                           pt_this);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pwd::h_chk_timer failed!"));
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    PWD_DLG_T*        pt_this = &t_g_pwd_dlg;
    INT32             i4_ret;
    NAV_UI_MSG_ID_T   e_id;

    e_id = pt_ui_msg->e_id;

    if((NAV_UI_MSG_AS_APP_PAUSED == pt_ui_msg->e_id)&&
        (pt_ui_msg->e_id_as_paused == NAV_UI_MSG_PRE_POWER_OFF))
    {
        e_id = pt_ui_msg->e_id_as_paused;
    }

    switch(e_id) {
    case NAV_UI_MSG_NO_SIGNAL:
    case NAV_UI_MSG_LOCKED_CH:
    case NAV_UI_MSG_LOCKED_PROG:
    case NAV_UI_MSG_LOCKED_INP:
    case NAV_UI_MSG_AFTER_SVC_CHANGE:
    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
    case NAV_UI_MSG_EMPTY_SVL:
        if(pt_ctx->t_svc_res.e_focus_tv_win_id == pt_ui_msg->e_tv_win_id)
        {
            if (t_g_pwd_dlg.b_delay_return_activation == FALSE) {
                nav_hide_component(NAV_COMP_ID_PWD_DLG);
            }
        }
        break;
    default:
        break;
    }

    switch(e_id)
    {
        case NAV_UI_MSG_LOCKED_CH:
        case NAV_UI_MSG_LOCKED_PROG:
        case NAV_UI_MSG_LOCKED_INP:
        {
            if(pt_ctx->t_svc_res.e_focus_tv_win_id == pt_ui_msg->e_tv_win_id)
            {
                i4_ret = c_timer_start(pt_this->h_chk_timer,
                                       NAV_PWD_DLG_CHK_TIMER_DELAY,
                                       X_TIMER_FLAG_ONCE,
                                       _pwd_dlg_timer_nfy,
                                       pt_this);
                if (i4_ret != OSR_OK)
                {
                    ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pwd::h_chk_timer failed!"));
                }
            }
        }
        break;
        case NAV_UI_MSG_PRE_POWER_OFF:
        {
            a_pwd_dlg_restore_rating_setting();
        }
        break;
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        case NAV_UI_MSG_APP_PAUSING:
        {
            if(NAV_UI_MSG_BEFORE_SVC_CHANGE == pt_ui_msg->e_id &&
               pt_ctx->t_svc_res.e_focus_tv_win_id != pt_ui_msg->e_tv_win_id)
            {
                break;
            }

            pt_this->b_force_stop_prompt = FALSE;

            i4_ret = c_timer_stop(pt_this->h_chk_timer);
            if (i4_ret != OSR_OK) {
                ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop pwd::h_chk_timer failed!"));
            }
        }
        break;

        case NAV_UI_MSG_BEFORE_TV_MODE_CHANGE:
        {
            pt_this->b_delay_chk_auto_active = TRUE;
        }
        break;

        case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        {
            pt_this->b_delay_chk_auto_active = FALSE;
        }
        break;

        case NAV_UI_MSG_FOCUS_CHANGED:
        {
            nav_request_context_switch(_pwd_dlg_handle_chk_timeout, NULL, NULL, NULL);
        }
        break;

        case NAV_UI_MSG_OTHER_APP_RESUMED:
        {
            if (c_strcmp ((CHAR*)pv_arg1, (CHAR*)MSCVT_NAME) == 0)
            {
                if(pt_ctx->t_svc_res.e_focus_tv_win_id == pt_ui_msg->e_tv_win_id)
                {
                    if (t_g_pwd_dlg.b_delay_return_activation == FALSE)
                    {
                        nav_hide_component(NAV_COMP_ID_PWD_DLG);
                    }
                }
            }
        }
        break;

        default:
            break;
    }

    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: pwd_dlg_alarm_msg_nty_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID pwd_dlg_alarm_msg_nty_fct(
                    PWD_DLG_T*                  pt_this,
                    HANDLE_T                    h_source,
                    WGL_NOTIFY_DATA_T*          pt_nfy_data
                    )
{
    switch(pt_nfy_data->ui4_nc_code){
    case WGL_NC_GL_KEY_DOWN:
    {
        switch (pt_nfy_data->u.t_key.ui4_key_code) {
        case BTN_VOL_UP:
        case BTN_VOL_DOWN:
        case BTN_MUTE:
        case BTN_INPUT_SRC:
        case BTN_PRG_UP:
        case BTN_PRG_DOWN:
        case BTN_PREV_PRG:
        case BTN_FAV_CH:
            nav_rcu_key_handler(pt_nfy_data->u.t_key.ui4_key_code);
            break;
        case BTN_EXIT:
            nav_hide_component(NAV_COMP_ID_PWD_DLG);
            break;
        default:
            _pwd_dlg_show_pwd_box(pt_this);
            break;
        }
        break;
    }
    case WGL_NC_GL_LOSE_FOCUS:
    {
        break;
    }
    default:
        break;
    }
}
/*----------------------------------------------------------------------------
 * Name: pwd_dlg_box_msg_nty_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID pwd_dlg_box_msg_nty_fct(
                    PWD_DLG_T*                  pt_this,
                    HANDLE_T                    h_source,
                    WGL_NOTIFY_DATA_T*          pt_nfy_data
                    )
{
    /* don't do further processing if delay return activation behavior is commited. */
    if (pt_this->b_delay_return_activation)
    {
        return;
    }

    switch(pt_nfy_data->ui4_nc_code){
    case WGL_NC_GL_KEY_DOWN:
    {
        switch (pt_nfy_data->u.t_key.ui4_key_code) {
        case BTN_SELECT:
            pt_this->b_force_stop_prompt = TRUE;
            /*if (_pwd_dlg_check_pwd(pt_this) == FALSE) {
                break;
            }*/

            nav_unlock_service(pt_this->e_focus_tv_win_id);
            break;
        case BTN_EXIT:
            pt_this->b_force_stop_prompt = TRUE;
            nav_hide_component(NAV_COMP_ID_PWD_DLG);
            break;
        default:
            nav_rcu_key_handler(pt_nfy_data->u.t_key.ui4_key_code);
            break;
        }

        break;
    }
    case WGL_NC_GL_LOSE_FOCUS:
    {
        break;
    }
    case WGL_NC_EB_CHANGED:
    {
        UTF16_T w2s_pwd[PASSWORD_BOX_LENGTH+1] = {0};
        INT32   i4_ret;

        _pwd_dlg_reset_timer(pt_this);

        i4_ret = c_wgl_do_cmd(
                        pt_this->h_pwd_box,
                        WGL_CMD_EB_GET_TEXT,
                        (VOID*)w2s_pwd,
                        (VOID*)(PASSWORD_BOX_LENGTH+1)
                        );
        if(WGLR_OK != i4_ret){
            break;
        }

        if(c_uc_w2s_strlen(w2s_pwd) != PASSWORD_LENGTH){
            break;
        }

        /*if (_pwd_dlg_check_pwd(pt_this) == FALSE) {
            break;
        }*/

        nav_unlock_service(pt_this->e_focus_tv_win_id);
        break;
    }
    default:
        break;
    }
}

/*----------------------------------------------------------------------------
 * Name: pwd_dlg_box_msg_nty_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID pwd_dlg_reset_timer(
                    VOID
                    )
{
    PWD_DLG_T* pt_this = &t_g_pwd_dlg;
    _pwd_dlg_reset_timer(pt_this);
}


/*----------------------------------------------------------------------------
 * Name: pwd_dlg_stop_timer
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID pwd_dlg_stop_timer(
                    VOID
                    )
{
    PWD_DLG_T* pt_this = &t_g_pwd_dlg;
    _pwd_dlg_stop_timer(pt_this);

    b_is_handle_timeout = TRUE;
}

 BOOL _tv_is_dual_tuner(VOID)
{
    BOOL b_is_dual_tuner = FALSE;

    if (c_util_source_is_dual(&b_is_dual_tuner) >= 0)
    {
        return b_is_dual_tuner;
    }
    else
    {
        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: pwd_dlg_box_msg_nty_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *
 ----------------------------------------------------------------------------*/
BOOL pwd_dlg_box_chk_pwd(UTF16_T*  w2s_pwd)
{
    PWD_DLG_T* pt_this = &t_g_pwd_dlg;
    HANDLE_T   h_svctx = NULL_HANDLE;
    UINT8      ui1_val;
    SIZE_T     z_size;

    /* don't do further processing if delay return activation behavior is commited. */
    if (pt_this->b_delay_return_activation)
    {
        return FALSE;
    }

    pt_this->b_force_stop_prompt = TRUE;
    if (_pwd_dlg_check_pwd(w2s_pwd) == FALSE)
    {
        return FALSE;
    }

    b_is_tmp_unlock = TRUE;

    ui1_val = RATING_ENABLED_STATUS_OFF;
    z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
              (VOID*)&ui1_val,
              z_size);


    a_rating_enable(FALSE);
    nav_get_svctx_handle(pt_this->e_focus_tv_win_id, &h_svctx);
    c_svctx_unblock_svc(h_svctx, TRUE);
	nav_unlock_service(pt_this->e_focus_tv_win_id);

    return TRUE;

}


/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_handle_return_activation_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pwd_dlg_handle_return_activation_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    t_g_pwd_dlg.b_delay_return_activation = FALSE;
    nav_hide_component(NAV_COMP_ID_PWD_DLG);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_return_activation_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pwd_dlg_return_activation_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_pwd_dlg_handle_return_activation_timeout, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_show_pwd_box
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_show_pwd_box(PWD_DLG_T*    pt_this)
{
    INT32 i4_ret = 0 ;

    i4_ret = scrn_svr_view_hide_signal_acquire();

    if (pt_this->b_pwd_box_on == TRUE) {
        return NAVR_OK;
    }

    /* hide pic mode change toast ui before show pwd dlg ui*/
    a_menu_pic_erengy_change_hide_toast_view();

    if(!b_is_handle_timeout)
    {
        i4_ret = pwd_dlg_view_show_lock_msg_box();
        if (i4_ret != NAVR_OK)
        {
            return i4_ret;
        }
        _pwd_dlg_reset_timer(pt_this);

    }
    else
    {
        i4_ret = pwd_dlg_view_show_box();
        if (i4_ret != NAVR_OK)
        {
            return i4_ret;
        }
        pt_this->b_pwd_box_on   = TRUE;
    }

    pt_this->b_pwd_osd_on   = TRUE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_hide_widget
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_hide_widget(PWD_DLG_T*    pt_this)
{
    INT32 i4_ret;

    i4_ret = pwd_dlg_view_hide_all();
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    pt_this->b_pwd_osd_on   = FALSE;
    pt_this->b_pwd_box_on   = FALSE;

    nav_return_activation(NAV_COMP_ID_PWD_DLG);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_check_pwd
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _pwd_dlg_check_pwd(UTF16_T*    w2s_pwd)
{
    INT32   i4_ret;
    SIZE_T  z_len;
    BOOL    b_pass;
    PWD_DLG_T* pt_this = &t_g_pwd_dlg;

    do {
        z_len = c_uc_w2s_strlen(w2s_pwd);
        if (z_len == 0) {
            nav_hide_component(NAV_COMP_ID_PWD_DLG);
            return FALSE;
        }

        /* delay to waiting for completion of repainting editbox. */
        c_thread_delay(PWD_BOX_WAIT_REPAINT_TIMEOUT);

        i4_ret = a_cfg_chk_password(
                        w2s_pwd,
                        &b_pass
                        );
        if (i4_ret != APP_CFGR_OK || b_pass == FALSE) {
            /*for CRDTV00762435 "Porgram Locked" info page can continue display until press < Play/Pause > key via simple RC. */
            _pwd_dlg_stop_timer(pt_this);
            pt_this->b_force_stop_prompt = FALSE;
            break;
        }

    #if 1
        /* delay to return activation to avoid number key pass to
         * channel banner.
         */
        pt_this->b_delay_return_activation = TRUE;
        pwd_dlg_view_hide_all();
        c_timer_start(
                    pt_this->h_hide_timer,
                    PWD_BOX_DISCART_KEY_TIMEOUT,
                    X_TIMER_FLAG_ONCE,
                    _pwd_dlg_return_activation_timer_nfy,
                    pt_this
                    );
    #else
        nav_hide_component(NAV_COMP_ID_PWD_DLG);
        /* delay to not let key input to pass to other UI component. */
        c_thread_delay(PWD_BOX_DISCART_KEY_TIMEOUT);
    #endif

        return TRUE;
    } while (0);

    /*c_thread_delay(PWD_BOX_WAIT_REPAINT_TIMEOUT);
    c_thread_delay(PWD_BOX_DISCART_KEY_TIMEOUT);*/
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pwd_dlg_stop_timer(PWD_DLG_T*    pt_this)
{
    INT32 i4_ret;

    if (pt_this->b_delay_return_activation == TRUE) {
        return;
    }

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop pwd_dlg::h_hide_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pwd_dlg_reset_timer(PWD_DLG_T*    pt_this)
{
    INT32 i4_ret;

    if (pt_this->b_delay_return_activation == TRUE) {
        return;
    }

    _pwd_dlg_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    PWD_DLG_TIMER_DELAY,
                    X_TIMER_FLAG_ONCE,
                    _pwd_dlg_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start audio_info::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_handle_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pwd_dlg_handle_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    b_is_handle_timeout = TRUE;
    t_g_pwd_dlg.b_force_stop_prompt = TRUE;
//    nav_hide_component(NAV_COMP_ID_PWD_DLG);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_handle_chk_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pwd_dlg_handle_chk_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    PWD_DLG_T*        pt_this = &t_g_pwd_dlg;
    TV_WIN_ID_T       e_tv_win_id;
    LOCKED_STATUS_T   e_locked_status;
    INT32             i4_ret;

    if (NAV_COMP_ID_PWD_DLG == nav_get_active_component())
    {
        DBG_LOG_PRINT(("<PWD>[%s, %d] NAV_COMP_ID_PWD_DLG == nav_get_active_component\n", __FUNCTION__, __LINE__));
        return;
    }

    /* Get Focus Win */
    nav_get_focus_id(&e_tv_win_id);

    /* Get Locked status / signal status */
    e_locked_status = nav_get_locked_status(e_tv_win_id);

    if (nav_is_active() && e_locked_status != LOCKED_STATUS_NONE && FALSE == pt_this->b_force_stop_prompt)
    {
        if (_pwd_is_able_to_activate())
        {
            nav_enable_key_traffic_auto_ctrl(50);
            nav_grab_activation(NAV_COMP_ID_PWD_DLG);
        }
        else
        {
            i4_ret = c_timer_start(pt_this->h_chk_timer,
                                   NAV_PWD_DLG_CHK_TIMER_DELAY,
                                   X_TIMER_FLAG_ONCE,
                                   _pwd_dlg_timer_nfy,
                                   pt_this);
            if (i4_ret != OSR_OK)
            {
                ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pwd::h_chk_timer failed!"));
            }
        }
    }
}


/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pwd_dlg_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    PWD_DLG_T* pt_this = (PWD_DLG_T*)pv_tag;


    //if system ui showing,no need update the pwd dlg next time
    if(msg_convert_custom_system_ui_showing()){
        DBG_LOG_PRINT(("{PWD DLG}->Fun:%s, Ln:%d, system ui showing:%d \n", __FUNCTION__, __LINE__,msg_convert_custom_system_ui_showing()));
        return NAVR_OK;
    }

    /* execute in timer's thread context */
    if (NULL != pt_this && h_timer == pt_this->h_chk_timer){
        nav_request_context_switch(_pwd_dlg_handle_chk_timeout, pv_tag, NULL, NULL);
    }
    else
    {
        nav_request_context_switch(_pwd_dlg_handle_timeout, pv_tag, NULL, NULL);
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_is_able_to_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _pwd_is_able_to_activate(VOID)
{
    PWD_DLG_T*      pt_this = &t_g_pwd_dlg;
    NAV_COMP_ID_T   e_active_comp = nav_get_active_component();
    TV_MODE_T       e_tv_mode;
    NAV_RETAIL_MODE_POPUP_DLG_T e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;

    if (pt_this->b_delay_chk_auto_active)
    {
        return FALSE;
    }

    a_tv_get_mode (& e_tv_mode);

    switch (e_active_comp)
    {
        case NAV_COMP_ID_EPG:
        case NAV_COMP_ID_VOL_CTRL:
        case NAV_COMP_ID_INPUT_SRC:
    #ifdef APP_WR_UPDATER_UI_SUPPORT
        case NAV_COMP_ID_WR_UPDATER:
    #endif
            return FALSE;

        case NAV_COMP_ID_FACTORY:
            return FALSE;

        case NAV_COMP_ID_PICTURE_EFFECT:
        case NAV_COMP_ID_SCREEN_MODE:
            return FALSE;

        case NAV_COMP_ID_RETAIL_MODE:
            a_nav_retail_mode_get_dlg_show(&e_popup_dlg);
            if(NAV_RETAIL_MODE_NO_POPUP_DLG!= e_popup_dlg)
            {
                return FALSE;
            }
            break;

        case NAV_COMP_ID_LAST_VALID_ENTRY:
            if (TV_MODE_TYPE_NORMAL == e_tv_mode)
            {
                if (nav_is_component_visible(NAV_COMP_ID_POWER))
                {
                    return FALSE;
                }

                a_nav_retail_mode_get_dlg_show(&e_popup_dlg);
                if(NAV_RETAIL_MODE_NO_POPUP_DLG!= e_popup_dlg)
                {
                    return FALSE;
                }
                else
                {
                    return TRUE;
                }
            }
            break;

        default:
            break;
    }

    if (nav_any_component_visible() == FALSE ||
        nav_is_component_visible(NAV_COMP_ID_BANNER) ||
        nav_is_component_visible(NAV_COMP_ID_SCREEN_SAVER))
    {
        return TRUE;
    }

    return FALSE;
}

#if 0
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_delay_show_banner
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pwd_dlg_delay_show_banner(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    nav_dispatch_msg_to_component(
                    NAV_COMP_ID_BANNER,
                    NAV_UI_MSG_SHOW_BANNER,
                    NULL
                    );
}

#endif

BOOL pwd_dlg_get_delay_return_activation_status(VOID)
{
    return t_g_pwd_dlg.b_delay_return_activation;
}

static VOID _pwd_dlg_cfg_vchip_nfy_fct(
    UINT16                      ui2_nfy_id,
    VOID*                       pv_tag,
    UINT16                      ui2_id)
{
    PWD_DLG_T*        pt_this = &t_g_pwd_dlg;
    //CHAR              s_app_name[APP_NAME_MAX_LEN];

    if(pt_this->ui2_acfg_nfy_id != ui2_nfy_id)
    {
        return;
    }

    //a_am_get_active_app(s_app_name);

    if(CFG_GET_SETTING(ui2_id) == APP_CFG_RECID_RATING_ENABLED)
    {
        UINT8      ui1_val;
        UINT8      ui1_enabled;
        SIZE_T     z_size;

        a_cfg_get_rating_enabled(&ui1_enabled);

        if (ui1_enabled == APP_CFG_RATING_ENABLED_OFF)
        {
            ui1_val = RATING_ENABLED_STATUS_OFF;
            z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;
            a_icl_set(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
                               (VOID*)&ui1_val,
                               z_size);
        }
        else
        {
            ui1_val = RATING_ENABLED_STATUS_ON;
            z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;
            a_icl_set(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
                               (VOID*)&ui1_val,
                               z_size);
        }
    }

}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_pwd_dlg_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_pwd_dlg_register(VOID)
{
    NAV_COMP_T t_comp;
    INT32      i4_ret;

    c_memset(&t_comp, 0, sizeof(NAV_COMP_T));

    t_comp.pf_init           = _pwd_dlg_init;
    t_comp.pf_deinit         = _pwd_dlg_deinit;
    t_comp.pf_is_key_handler = _pwd_dlg_is_key_handler;
    t_comp.pf_activate       = _pwd_dlg_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _pwd_dlg_hide;
    t_comp.pf_handle_msg     = _pwd_dlg_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_PWD_DLG, &t_comp, COMP_EXC_SET_PWD_DLG);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_PWD_DLG) failed\r\n"));
        return i4_ret;
    }

    return NAVR_OK;
}

INT32 a_pwd_dlg_check_show(VOID)
{
    return 0;
}

INT32 a_pwd_dlg_webui_check_pwd(UTF16_T*    pw2s_pwd)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_pwd_dlg_check_osd_on
 * Description: check pwd osd is on or not
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/

BOOL a_pwd_dlg_check_osd_on(void)
{
    return t_g_pwd_dlg.b_pwd_osd_on;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_pwd_dlg_check_box_on
 * Description: check pwd box is on or not
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/

BOOL a_pwd_dlg_check_box_on(void)
{
    return t_g_pwd_dlg.b_pwd_box_on;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_pwd_dlg_restore_rating_setting
 * Description: reset rating setting for before power down
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
void a_pwd_dlg_restore_rating_setting(void)
{
    UINT8      ui1_val;
    UINT8      ui1_enabled;
    SIZE_T     z_size;

    a_cfg_get_rating_enabled(&ui1_enabled);

    if (ui1_enabled == APP_CFG_RATING_ENABLED_ON)
    {
        ui1_val = RATING_ENABLED_STATUS_ON;
        z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;
        a_icl_set(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
                           (VOID*)&ui1_val,
                           z_size);
    }
    else
    {
        ui1_val = RATING_ENABLED_STATUS_OFF;
        z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;
        a_icl_set(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
                           (VOID*)&ui1_val,
                           z_size);
    }
    /* update rating settings */
    a_cfg_update_rating_settings();
}


#endif // #ifndef APP_NO_PWD_DLG

