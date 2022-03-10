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
 * $RCSfile: vol_ctrl.c,v $
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
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_cfg.h"

#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "nav/a_navigator.h"
#include "nav/core/_nav_view.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "nav/vol_ctrl/vol_ctrl.h"
#include "mmp/app/mmp_main.h"
#include "wizard_anim/a_wzd.h"
#include "nav/retail_mode/nav_retail_mode.h"
#include "res/app_util/mtktvapi/a_mtktvapi_volctrl_custom.h"
#ifdef SYS_MTKTVAPI_SUPPORT
#include "app_util/mtktvapi/a_mtktvapi_volctrl.h"
#endif
#include "res/menu2/menu_custom.h"
#include "menu2/menu_vizio/menu_page_bt_devices.h"
#include "menu2/menu_vizio/menu_page_bt_json_db.h"
#include "rest/vzipc/vzIpcServer.h"

#ifdef APP_TTS_SUPPORT
#include "c_tts.h"
#endif
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif
#include "res/nav/nav_dbg.h"

#ifdef APP_VOLUME_CTRL
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/* Volume UP or Volume DOWN */
#define MIN_VOLUME 0
#define MAX_VOLUME 100
#define BT_MIN_VOLUME 0
#define BT_MAX_VOLUME 127
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
VOL_CTRL_T t_g_vol_ctrl;
#ifndef LINUX_TURNKEY_SOLUTION
#define VOL_CTRL_VOLUME_UI_SHOW    (0x01)
#define VOL_CTRL_MUTE_UI_SHOW      (0x02)
#define VOL_CTRL_BT_CTRL_UI        (0x04)
#define VOL_CTRL_TV_CTRL_UI        (0x08)
extern NAV_MODEL_T     t_g_navigator;
static HANDLE_T h_g_mmp_focus = NULL_HANDLE;
static UINT8    ui1_g_mmp_app_order = 0;
static UINT8    ui1_g_ui_attr = 0;
#else
extern NAV_MODEL_T     t_g_navigator;
#endif
extern BOOL b_edid_change_mute_process;
static BOOL b_tts_mute_key_status = FALSE;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_hide_mute(
                    VOL_CTRL_T*             pt_this,
                    BOOL                    b_hide
                    );

static INT32 _vol_ctrl_hide_mute_ex(
                    VOL_CTRL_T*             pt_this,
                    BOOL                    b_hide,
                    BOOL                    b_discard_sac_sts
                    );

static INT32 _vol_ctrl_on_nav_resume(
                    VOL_CTRL_T*                 pt_this
                    );

//#if APP_CEC_SAC_VOL_SUPPORT
static INT32 _vol_ctrl_handle_cec_sac_mode(
                    VOL_CTRL_T*                pt_this,
                    NAV_UI_MSG_VOL_CHG_INFO_T* pt_vol_info
                    );
//#endif

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
#ifdef APP_CEC_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_handle_cec_sac_change
 *
 * Description: Handle the situation that CEC SAC config is changed.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

extern BOOL nav_cec_get_arc_status(void);


static VOID _vol_ctrl_handle_cec_sac_change(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32 i4_ret;
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    ICL_ID_TYPE e_id = (ICL_ID_TYPE)((UINT32)pv_tag1);
    UINT8 ui1_sac_sts;
    SIZE_T z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;

    _vol_ctrl_on_nav_resume (pt_this);

    i4_ret = a_icl_get(e_id, &ui1_sac_sts, &z_size);
    if (i4_ret != ICLR_OK || ui1_sac_sts == ICL_CEC_SAC_STATUS_OFF)
    {
        if (pt_this->b_is_volume_on == TRUE)
        {
            nav_hide_component(NAV_COMP_ID_VOL_CTRL);
        }
        pt_this->b_is_sam_on = FALSE;
    }
    else
    {
        pt_this->b_is_sam_on = TRUE;
    }
}
/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_cec_sac_icl_nfy_fct
 *
 * Description: A notify function if CEC SAC config is changed.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _vol_ctrl_cec_sac_icl_nfy_fct(
                    UINT16                      ui2_nfy_id,
                    VOID*                       pv_tag,
                    ICL_NOTIFY_DATA_T*          pt_notify_data
                    )
{
    INT32 i4_ret;
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    ICL_RECID_TYPE e_rec_id = ICL_GET_REC (pt_notify_data->pe_id[0]);

    if (e_grp_id != ICL_GRPID_CEC || e_rec_id != ICL_RECID_CEC_SAC_STATUS)
    {
        return ICLR_FAIL;
    }

    i4_ret = nav_request_context_switch(
                _vol_ctrl_handle_cec_sac_change,
                (VOID*)((UINT32)pt_notify_data->pe_id[0]),
                NULL,
                NULL
                );
    if (i4_ret != NAVR_OK)
    {
        return ICLR_FAIL;
    }

    return ICLR_OK;
}
#endif
#ifdef APP_MUTE_DISP_AS_TEXT
/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_handle_gui_lang_change
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _vol_ctrl_handle_gui_lang_change(
                    VOID*                       pv_rrctx,
                    VOID*                       pv_nfy_tag,
                    VOID*                       pv_reason
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;

    if (pt_this->b_is_mute_on == TRUE) {
        pt_this->t_view_hdlr.pf_show_mute(TRUE);
    }
}
/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_cfg_nfy_fct
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _vol_ctrl_cfg_nfy_fct(
                    UINT16                      ui2_nfy_id,
                    VOID*                       pv_tag,
                    UINT16                      ui2_cfg_id
                    )
{
    if (CFG_GET_SETTING(ui2_cfg_id) == APP_CFG_RECID_GUI_LANG) {
        nav_request_context_switch(
                    _vol_ctrl_handle_gui_lang_change,
                    NULL,
                    NULL,
                    NULL
                    );
    }
}
/*----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_cfg_notify_init
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _vol_ctrl_cfg_notify_init (
                    VOL_CTRL_T*                 pt_this
                    )
{
    INT32 i4_ret;

    pt_this->ui2_gui_lang_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;

    i4_ret = a_cfg_notify_reg(
                    APP_CFG_GRPID_GUI_LANG,
                    NULL,
                    _vol_ctrl_cfg_nfy_fct,
                    &pt_this->ui2_gui_lang_cfg_nfy
                    );
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif
#ifndef APP_HIDE_MUTE_AS_PAUSED
/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_handle_reset_volume_change
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _vol_ctrl_handle_reset_volume_change(
                    VOID*                       pv_rrctx,
                    VOID*                       pv_nfy_tag,
                    VOID*                       pv_reason
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;

    if (pt_this->b_is_mute_on == TRUE && nav_is_active() == FALSE) {
        BOOL b_mute = TRUE;

        if (nav_get_mute(&b_mute) == NAVR_OK && b_mute == FALSE) {
            _vol_ctrl_hide_mute(
                    pt_this,
                    TRUE
                    );
        }
    }
}
/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_cfg_audio_nfy_fct
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _vol_ctrl_cfg_audio_nfy_fct(
                    UINT16                      ui2_nfy_id,
                    VOID*                       pv_tag,
                    UINT16                      ui2_cfg_id
                    )
{
    UINT16 ui2_recid = CFG_GET_SETTING(ui2_cfg_id);

    /* tricky - unmute is executed before VGA reset
     * This strange logic is to solve to "Reset Default,
     * mute icon is still on, but audio is unmuted"
     */
    if (ui2_recid == APP_CFG_RECID_VGA_LRU) {
        nav_request_context_switch(
                    _vol_ctrl_handle_reset_volume_change,
                    NULL,
                    NULL,
                    NULL
                    );
    }
}
/*----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_cfg_audio_notify_init
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
static INT32 _vol_ctrl_cfg_audio_notify_init (
                    VOL_CTRL_T*                 pt_this
                    )
{
    INT32 i4_ret;

    pt_this->ui2_audio_cfg_nfy = APP_CFG_NOTIFY_NULL_ID;

    i4_ret = a_cfg_notify_reg(
                    APP_CFG_GRPID_VGA, /* unmute is executed before VGA reset */
                    NULL,
                    _vol_ctrl_cfg_audio_nfy_fct,
                    &pt_this->ui2_audio_cfg_nfy
                    );
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_stop_mute_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_stop_mute_timer(
                    VOL_CTRL_T*                 pt_this
                    )
{
#ifdef MUTE_TIMER_DELAY
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_mute_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_mute_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop vol_ctrl::h_mute_hide_timer failed!"));
    }
#endif
}
#ifdef MUTE_TIMER_DELAY
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_timeout_to_hide_mute(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _vol_ctrl_hide_mute(&t_g_vol_ctrl, TRUE);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_mute_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_mute_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_vol_ctrl_timeout_to_hide_mute, pv_tag, NULL, NULL);
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_reset_mute_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_reset_mute_timer(
                    VOL_CTRL_T*                 pt_this
                    )
{
#ifdef MUTE_TIMER_DELAY
    INT32 i4_ret;

    i4_ret = c_timer_start(
                    pt_this->h_mute_hide_timer,
                    MUTE_TIMER_DELAY,
                    X_TIMER_FLAG_ONCE,
                    _vol_ctrl_mute_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start vol_ctrl::h_mute_hide_timer failed!"));
    }
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_stop_timer(
                    VOL_CTRL_T*                 pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop vol_ctrl::h_hide_timer failed!"));
    }
}

#if 0
/*-----------------------------------------------------------------------------
 * Name: _vol_ctrl_comp_state_trans_nfy
 *
 * Description: This callback function will be called when the comp switches.
 *
 * Inputs:  e_cond          Contains the transition condition.
 *          ui4_evt_code    Contains the event code.
 *          e_from_comp_id  Current comp ID.
 *          e_to_comp_id    Next comp ID.
 *          ui4_data        Contains information related to the event.
 *          pv_tag          A private tag.
 *
 * Outputs: -
 *
 * Returns: NAVR_OK         This function succeeded.
 *          Otherwise       This function failed.
 ----------------------------------------------------------------------------*/
static INT32 _vol_ctrl_comp_state_trans_nfy (NAV_COMP_STATE_TRANS_COND_T e_cond,
                                             NAV_COMP_ID_T e_from_comp_id,
                                             NAV_COMP_ID_T e_to_comp_id,
                                             UINT32 ui4_data,
                                             VOID* pv_tag)
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;

    if (!nav_is_active() || nav_is_pausing())
    {
        return NAVR_OK;
    }

    if (e_cond == NAV_COMP_STATE_TRANS_BEFORE_ACTIVATION_CHANGE)
    {
		BOOL  b_to_hide = FALSE;

		if(NAV_IS_COMP_SET_NOT_EMPTY(COMP_VIEW_DENY_SET_VOL_CTRL_MUTE))
		{
			if (NAV_IS_COMP_SET_INCLUDE_COMP(COMP_VIEW_DENY_SET_VOL_CTRL_MUTE, e_to_comp_id))
			{
				b_to_hide = TRUE;
			}
		}

		if (b_to_hide == FALSE)
		{
			if(NAV_IS_COMP_SET_NOT_EMPTY(COMP_VIEW_EXC_SET_VOL_CTRL_MUTE))
			{
				if (NAV_IS_COMP_SET_INCLUDE_COMP(COMP_VIEW_EXC_SET_VOL_CTRL_MUTE, e_to_comp_id))
				{
					b_to_hide = TRUE;
				}
			}
		}

        if(b_to_hide && pt_this->b_is_mute_on)
		{
			 return _vol_ctrl_hide_mute (pt_this, TRUE);
		}
    }
	else if (e_cond == NAV_COMP_STATE_TRANS_AFTER_ACTIVATION_CHANGE)
	{
		BOOL  b_is_muted;
		INT32 i4_ret;

		BOOL  b_to_show = TRUE;

	    /*IF the exclusive components hide, show the mute icon*/
		i4_ret = nav_get_mute(&b_is_muted);
		if (i4_ret < NAVR_OK) {
			DBG_ERROR(("[NAV] nav_get_mute failed.\n"));
			return i4_ret;
		}

		if(NAV_IS_COMP_SET_NOT_EMPTY(COMP_VIEW_DENY_SET_VOL_CTRL_MUTE))
		{
			if (NAV_IS_COMP_SET_INCLUDE_COMP(COMP_VIEW_DENY_SET_VOL_CTRL_MUTE, e_to_comp_id))
			{
				b_to_show = FALSE;
			}
		}

		if (b_to_show)
		{
			if(NAV_IS_COMP_SET_NOT_EMPTY(COMP_VIEW_EXC_SET_VOL_CTRL_MUTE))
			{
				if (NAV_IS_COMP_SET_INCLUDE_COMP(COMP_VIEW_EXC_SET_VOL_CTRL_MUTE, e_to_comp_id))
				{
					b_to_show = FALSE;
				}
			}
		}

		if (b_is_muted == TRUE && pt_this->b_is_mute_on == FALSE) {
			if(b_to_show) {
				/* just show muting icon if it is hide */
				i4_ret = _vol_ctrl_hide_mute_ex(pt_this, FALSE, TRUE);
				if (i4_ret != NAVR_OK) {
					return NAVR_FAIL;
				}
			}
		}
	}

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    INT32       i4_ret;

#ifndef LINUX_TURNKEY_SOLUTION
    ui1_g_ui_attr = 0;
#endif

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    pt_this->h_hide_timer        = NULL_HANDLE;
    pt_this->h_mute_hide_timer   = NULL_HANDLE;
    pt_this->b_is_volume_on      = FALSE;
    pt_this->b_is_mute_on        = FALSE;
    pt_this->b_is_volume_visible = TRUE;
#ifdef APP_CEC_SUPPORT
    pt_this->b_is_sam_on         = FALSE;
#endif

    pt_this->b_is_bt_headphones_active = FALSE;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }
#ifdef MUTE_TIMER_DELAY
    i4_ret = c_timer_create(&(pt_this->h_mute_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }
#endif

#ifdef APP_MUTE_DISP_AS_TEXT
    i4_ret = _vol_ctrl_cfg_notify_init(pt_this);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif

#ifdef APP_CEC_SUPPORT
    /* Register notify function of lang */
    pt_this->ui2_cec_sac_icl_nfy = ICL_INVALID_ID;
    i4_ret = a_icl_notify_reg (
                    ICL_GRPID_CEC,
                    ICL_PRIORITY_DEFAULT,
                    NULL,
                    NULL,
                    _vol_ctrl_cec_sac_icl_nfy_fct,
                    &pt_this->ui2_cec_sac_icl_nfy);
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }
#endif

#ifndef APP_HIDE_MUTE_AS_PAUSED
    i4_ret = _vol_ctrl_cfg_audio_notify_init(pt_this);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif
#if 0
    /* Register comp transition nfy. */
    i4_ret = nav_register_comp_state_trans_nty_fct (NAV_COMP_ID_VOL_CTRL,
                                                    _vol_ctrl_comp_state_trans_nfy,
                                                    NULL);
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
#endif

    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset
                    );
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_deinit(VOID)
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    INT32       i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    if (c_handle_valid(pt_this->h_mute_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_mute_hide_timer);
    }

    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    pt_this->h_svctx           = NULL_HANDLE;
    pt_this->h_hide_timer      = NULL_HANDLE;
    pt_this->h_mute_hide_timer = NULL_HANDLE;
    pt_this->b_is_volume_on    = FALSE;
    pt_this->b_is_mute_on      = FALSE;

#ifdef APP_MUTE_DISP_AS_TEXT
    if (pt_this->ui2_gui_lang_cfg_nfy != APP_CFG_NOTIFY_NULL_ID) {
        a_cfg_notify_unreg(pt_this->ui2_gui_lang_cfg_nfy);
    }
#endif

#ifndef APP_HIDE_MUTE_AS_PAUSED
    if (pt_this->ui2_audio_cfg_nfy != APP_CFG_NOTIFY_NULL_ID) {
        a_cfg_notify_unreg(pt_this->ui2_audio_cfg_nfy);
    }
#endif

#ifdef APP_CEC_SUPPORT
    if (pt_this->ui2_cec_sac_icl_nfy != ICL_INVALID_ID)
    {
        a_icl_notify_unreg(pt_this->ui2_cec_sac_icl_nfy);
    }
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_hide_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_hide_mute(
                    VOL_CTRL_T*             pt_this,
                    BOOL                    b_hide
                    )
{
    return _vol_ctrl_hide_mute_ex(
                            pt_this,
                            b_hide,
                            FALSE);
}

/******************************************************************************/
/**
 * @brief   Show/Hide mute OSD
 * @param   pt_this [in]        The opcode of the notify.
 * @param   b_hide [in]         A pointer to CECM_NFY_T.
 * @param   b_sac_active [in]
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
/******************************************************************************/
static INT32 _vol_ctrl_hide_mute_ex(
                    VOL_CTRL_T*             pt_this,
                    BOOL                    b_hide,
                    BOOL                    b_discard_sac_sts
                    )
{
    INT32 i4_ret;

    if (b_hide == TRUE && pt_this->b_is_mute_on == TRUE) {
        i4_ret = pt_this->t_view_hdlr.pf_hide_mute();
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
        _vol_ctrl_stop_mute_timer(pt_this);
    } else if (b_hide == FALSE && pt_this->b_is_mute_on == FALSE) {
#ifdef APP_CEC_SUPPORT
        if (b_discard_sac_sts == TRUE ||
            vol_ctrl_is_cec_sac_mode () == FALSE)
#endif
        {
            i4_ret = pt_this->t_view_hdlr.pf_show_mute(FALSE);
            if (i4_ret != NAVR_OK) {
                return NAVR_FAIL;
            }
        }
        pt_this->b_is_mute_on = TRUE;
        _vol_ctrl_reset_mute_timer(pt_this);
    }
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _vol_ctrl_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
#ifndef LINUX_TURNKEY_SOLUTION
    CHAR        s_active_app[APP_NAME_MAX_LEN + 1] = {0};
#endif

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_VOLUME_CTRL_UI) == TRUE) {
        return FALSE;
    }
    if (BTN_VOL_UP == ui4_key_code || BTN_VOL_DOWN == ui4_key_code || BTN_MUTE == ui4_key_code)
    {
        if (menu_custom_is_blank_screen() == TRUE && menu_custom_get_blank_scrn_mode() != BLK_SCRN_NORMAL)
        {
            menu_custom_unblank_screen(ui4_key_code);
            return FALSE;
        }
    }

#ifndef LINUX_TURNKEY_SOLUTION
    a_am_get_active_app(s_active_app);

    if (0 != c_strcmp(s_active_app, NAV_NAME))
    {
        if ((ui1_g_ui_attr & VOL_CTRL_VOLUME_UI_SHOW)
            ||(ui1_g_ui_attr & VOL_CTRL_MUTE_UI_SHOW))
        {
            if (BTN_VOL_UP == ui4_key_code)
            {
                ui1_g_ui_attr = 0;
                ui1_g_ui_attr |= VOL_CTRL_VOLUME_UI_SHOW;
                if(pt_this->b_is_bt_headphones_active == FALSE)
                {
                    vol_ctrl_increase_volume(pt_this);
                }
                else
                {
                    bt_vol_ctrl_increase_volume(pt_this);
                }
            }
            else if (BTN_VOL_DOWN == ui4_key_code)
            {
                ui1_g_ui_attr = 0;
                ui1_g_ui_attr |= VOL_CTRL_VOLUME_UI_SHOW;
                if(pt_this->b_is_bt_headphones_active == FALSE)
                {
                    vol_ctrl_decrease_volume(pt_this);
                }
                else
                {
                    bt_vol_ctrl_decrease_volume(pt_this);
                }
            }
            else if (BTN_MUTE == ui4_key_code)
            {
                ui1_g_ui_attr = 0;
                ui1_g_ui_attr |= VOL_CTRL_MUTE_UI_SHOW;
                if(pt_this->b_is_bt_headphones_active == FALSE)
                {
                    vol_ctrl_mute(pt_this);
                }
                else
                { 
                    bt_vol_ctrl_set_mute(pt_this);
                }
            }
        }
        else
        {
            c_wgl_get_focus(&h_g_mmp_focus);
            c_wgl_get_app_order(mmp_main_get_app(), &ui1_g_mmp_app_order);
            c_wgl_set_active_app(t_g_navigator.h_app);
            c_wgl_set_app_order(t_g_navigator.h_app, WGL_APP_TOPMOST);
            vol_ctrl_show_volume(pt_this);
            if ((BTN_VOL_UP == ui4_key_code)
                ||(BTN_VOL_DOWN == ui4_key_code))
            {
                ui1_g_ui_attr = 0;
                ui1_g_ui_attr |= VOL_CTRL_VOLUME_UI_SHOW;
            }
            else if (BTN_MUTE == ui4_key_code)
            {
                ui1_g_ui_attr = 0;
                ui1_g_ui_attr |= VOL_CTRL_MUTE_UI_SHOW;
            }
        }

        if ((BTN_EXIT == ui4_key_code)
            ||(BTN_MENU == ui4_key_code))
        {
            ui1_g_ui_attr = 0;
            _vol_ctrl_hide_volume(pt_this);
            c_wgl_set_focus(h_g_mmp_focus, WGL_SYNC_AUTO_REPAINT);
            c_wgl_set_active_app(mmp_main_get_app());
            c_wgl_set_app_order(mmp_main_get_app(), ui1_g_mmp_app_order);
        }

        return FALSE;
    }
#endif
    return pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;

    nav_get_svctx_handle(pt_ctx->t_svc_res.e_focus_tv_win_id, &pt_this->h_svctx);

    return pt_this->t_view_hdlr.pf_activate(ui4_key_code);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_hide_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_hide_volume(
                    VOL_CTRL_T*                 pt_this
                    )
{
    INT32 i4_ret;

#if !(defined(MT5695_MODEL)&&defined(MT5695_FAMILY_S))
    if (pt_this->b_is_volume_on == FALSE) {
        return NAVR_NO_ACTION;
    }
#endif

    i4_ret = pt_this->t_view_hdlr.pf_hide_volume();
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

	c_wgl_set_app_order(t_g_navigator.h_app, WGL_APP_BOTTOMMOST);

    pt_this->ui1_crnt_au_ch_idx = 0;
    pt_this->b_is_volume_on     = FALSE;

    _vol_ctrl_stop_timer(pt_this);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_on_nav_resume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_on_nav_resume(
                    VOL_CTRL_T*                 pt_this
                    )
{
    BOOL  b_is_muted;
    INT32 i4_ret;

    i4_ret = nav_get_mute(&b_is_muted);
    if (i4_ret < NAVR_OK)  {
        DBG_ERROR(("[NAV] nav_get_mute failed.\n"));
        return i4_ret;
    }

    if (b_is_muted == TRUE) {
        i4_ret = nav_hide_component(NAV_COMP_ID_VOL_CTRL);
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = _vol_ctrl_hide_mute_ex(pt_this, FALSE, FALSE);//i4_ret = _vol_ctrl_hide_mute_ex(pt_this, FALSE, TRUE);
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    } else {
        i4_ret = _vol_ctrl_hide_mute(pt_this, TRUE);
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    INT32       i4_ret;
//#if APP_CEC_SAC_VOL_SUPPORT
    BOOL        b_reset_visible = FALSE;
//#endif
    static BOOL is_hf_connected = FALSE;

    DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Reached _vol_ctrl_handle_msg() pt_ui_msg->e_id=%d \r\n", __FUNCTION__, __LINE__, pt_ui_msg->e_id));

    if (pt_ui_msg->e_id == NAV_UI_MSG_BT_VOL_CTRL)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received Volume UP/INFO/DOWN Event\r\n", __FUNCTION__, __LINE__));
        if (pv_arg1 == NULL)
        {
            return NAVR_FAIL;
        }
        tBtAudio command = BTAPI_MSG_MAX;
        INT32 volume = 0;
        sscanf((char*)pv_arg1, "%d %d", &command, &volume);
        DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received Volume UP/INFO/DOWN Event, Volume : %d\r\n", __FUNCTION__, __LINE__, volume));
        switch (command) {
        case BTAPI_SINK_STREAM_STARTED: {
            is_hf_connected = TRUE;
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received BT headphones start streaming\r\n", __FUNCTION__,__LINE__));
            pt_this->b_is_bt_headphones_active = TRUE;
            nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VIDEO_SEL),
                              NAV_UI_MSG_BT_VOL_CTRL, 
                              &is_hf_connected);
            break;
            }
        case BTAPI_SINK_STREAM_STOPPED: {
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received BT headphones stop streaming\r\n", __FUNCTION__,__LINE__));
            a_vol_ctrl_hide();
            is_hf_connected = FALSE;
            pt_this->b_is_bt_headphones_active = FALSE;
            nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VIDEO_SEL),
                              NAV_UI_MSG_BT_VOL_CTRL, 
                              &is_hf_connected);
            break;
            }
        case BTAPI_VOLUME_INFO: {
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received Volume INFO Event\r\n", __FUNCTION__,__LINE__));
            pt_this->b_is_volume_event = TRUE;
            pt_this->b_is_bt_req_in_progress = FALSE;
            pt_this->i2_volume = (INT16)volume;
            pt_this->t_view_hdlr.pf_activate(BTN_SHOW_VOL_BAR);
            break;
            }
        case BTAPI_VOLUME_UP: {
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received Volume UP Event\r\n", __FUNCTION__,__LINE__));
            pt_this->b_is_volume_event = TRUE;
            pt_this->b_is_bt_req_in_progress = FALSE;
            pt_this->i2_volume = (INT16)volume;
            pt_this->t_view_hdlr.pf_activate(BTN_VOL_UP);
            break;
            }
        case BTAPI_VOLUME_DOWN: {
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received Volume DOWN Event\r\n", __FUNCTION__,__LINE__));
            pt_this->b_is_volume_event = TRUE;
            pt_this->b_is_bt_req_in_progress = FALSE;
            pt_this->i2_volume = (INT16)volume;
            pt_this->t_view_hdlr.pf_activate(BTN_VOL_DOWN);
            break;
            }
        case BTAPI_MUTE_UNMUTE: {
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received MUTE/UNMUTE Event\r\n", __FUNCTION__,__LINE__));
            pt_this->b_is_bt_req_in_progress = FALSE;
            pt_this->b_is_mute_event = TRUE;
            pt_this->b_is_mute_on = volume ? TRUE : FALSE;
            pt_this->t_view_hdlr.pf_activate(BTN_MUTE);
            break;
            }
        default:
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Received Other Event# %d\r\n", __FUNCTION__, __LINE__, pt_ui_msg->e_id));
            pv_arg1 = NULL;
            break;
        }
        /* Free the message allocated by ipvServer Thread here*/
        if(pv_arg1) 
        {
            c_mem_free((char*)pv_arg1);
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%d Message Free Success\r\n", __FUNCTION__,__LINE__));
        }
        return NAVR_OK;
    }

    nav_get_svctx_handle(pt_ctx->t_svc_res.e_focus_tv_win_id, &pt_this->h_svctx);

#ifdef SYS_MTKTVAPI_SUPPORT
    NAV_UI_MSG_ID_T             e_id = NAV_UI_MSG_LAST_VALID_ENTRY;

    e_id = (NAV_UI_MSG_AS_APP_PAUSED == pt_ui_msg->e_id)
         ? pt_ui_msg->e_id_as_paused
         : pt_ui_msg->e_id ;
	if (NAV_UI_MSG_MUTE_STATUS_CHANGED == e_id)
	{
		a_mtktvapi_volctrl_audio_event_do_msg_notify(ACFG_MSG_CHG_MUTE, NULL);
	}
#endif

    switch (pt_ui_msg->e_id) {
    case NAV_UI_MSG_APP_PAUSING:
#ifdef APP_HIDE_MUTE_AS_PAUSED
        i4_ret = _vol_ctrl_hide_mute(pt_this, TRUE);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
#endif
        break;
    case NAV_UI_MSG_OTHER_APP_RESUMED:
#ifndef APP_HIDE_MUTE_AS_PAUSED
        if (vol_ctrl_is_mute_icon_coexist_app((CHAR*)pv_arg1) == FALSE)
        {
            i4_ret = _vol_ctrl_hide_mute(pt_this, TRUE);
            if (i4_ret != NAVR_OK) {
                return i4_ret;
            }
        }
        else
        {
            /* Recheck mute status if mute icon can be co-exist with this APP. */
            i4_ret = _vol_ctrl_on_nav_resume(pt_this);
            if (i4_ret != NAVR_OK) {
                return i4_ret;
            }
        }
#endif
        break;
    case NAV_UI_MSG_APP_RESUMED:
        i4_ret = _vol_ctrl_on_nav_resume(pt_this);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        break;

    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
    {
        NAV_XNG_SRC_TRGT_T* pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;
        BOOL b_is_muted;

        i4_ret = nav_get_mute(&b_is_muted);
        if (i4_ret >= NAVR_OK) {
            if (pt_this->b_is_mute_on == FALSE) {
                /* just show muting icon if it is hide */
                if (b_is_muted == TRUE) {
                    _vol_ctrl_hide_mute(pt_this, FALSE);
                }
            } else {
                _vol_ctrl_reset_mute_timer(pt_this);
            }
        }

        if(NAV_COMP_ID_VOL_CTRL != nav_get_active_component()) {
            break;
        }

        /* in order to avoid the second NAV_UI_MSG_BEFORE_SVC_CHANGE
         * if single RF scan is enabled
         */
        if (pt_xng_info->e_type == INP_SRC_TYPE_TV) {
            if (nav_is_same_channel(
                        pt_xng_info->u.t_tv.ui2_crnt_svl_id,
                        pt_xng_info->u.t_tv.ui2_crnt_svl_rec_id,
                        pt_xng_info->u.t_tv.ui4_crnt_channel_id,
                        pt_xng_info->u.t_tv.ui2_trgt_svl_id,
                        pt_xng_info->u.t_tv.ui2_trgt_svl_rec_id,
                        pt_xng_info->u.t_tv.ui4_trgt_channel_id
                        ) == TRUE) {
                break;
            }
        } else if (pt_xng_info->e_type == INP_SRC_TYPE_AV) {
            if (pt_xng_info->u.t_av.ui1_crnt_inp_src_id == pt_xng_info->u.t_av.ui1_trgt_inp_src_id) {
                 break;
            }
        }

        i4_ret = nav_hide_component(NAV_COMP_ID_VOL_CTRL);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        break;
    }
//#if APP_CEC_SAC_VOL_SUPPORT
    case NAV_UI_MSG_VOLUME_STATUS_CHANGED:
    {
        UINT8   ui1_vol_dis_flag = ACFG_CUSTOM_VOL_SLIDER_DIS_OFF;
        NAV_RETAIL_MODE_STATUS_T retail_status;
		a_nav_retail_mode_get_status(&retail_status);
        i4_ret = a_cfg_cust_get_vol_control_dis_flag(&ui1_vol_dis_flag);
        if (i4_ret != NAVR_OK)
        {
            DBG_ERROR(("%s,%d vol get dis flag fail  \r\n",__FUNCTION__,__LINE__));
        }

        if(pt_this->b_is_bt_headphones_active == TRUE)
        {
            return (NAVR_OK);
        }
        
        if (!vol_ctrl_is_cec_sac_mode()) {

            return (NAVR_OK);
        }

        if(((a_wzd_is_oobe_mode() == TRUE)&&(retail_status!=NAV_RETAIL_MODE_RUNNING)) || (ui1_vol_dis_flag == ACFG_CUSTOM_VOL_SLIDER_DIS_OFF))
        {
            DBG_WARN(("%s,%d.[in oobe mode or vol dis off] \r\n",__FUNCTION__, __LINE__));
            return (NAVR_OK);
        }
#if 0
        if (nav_is_active() == FALSE && pt_this->b_is_volume_visible == TRUE)
        {
            /* if nav is not active, recevie the Vol+/- key, volume isn't showed */
            b_reset_visible = TRUE;
            pt_this->b_is_volume_visible = FALSE;
        }
#endif
        i4_ret  = _vol_ctrl_handle_cec_sac_mode(
                            pt_this,
                            (NAV_UI_MSG_VOL_CHG_INFO_T*)pv_arg1
                            );
        if (b_reset_visible == TRUE)
        {
            pt_this->b_is_volume_visible = TRUE;
        }

        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        break;
    }
//#endif
    case NAV_UI_MSG_POWER_ON:
    case NAV_UI_MSG_SYSTEM_POWER_ON:
    {
        BOOL  b_is_mute;
        INT32 i4_ret;

#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
        pt_this->b_is_need_show_speaker_off = TRUE;
#endif

        i4_ret = nav_get_mute(&b_is_mute);
        if (i4_ret < NAVR_OK)
        {
            DBG_ERROR(("%s,%d[NAV] nav_get_mute failed.\n",__FUNCTION__, __LINE__));
            return i4_ret;
        }

        if(b_is_mute == TRUE)
        {
            pt_this->b_is_mute_on = FALSE;
            nav_set_mute (pt_this->b_is_mute_on);
        }

        break;
    }

    default:
        break;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_hide(
                    VOID
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    INT32       i4_ret;

    i4_ret = _vol_ctrl_hide_volume(pt_this);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    nav_return_activation(NAV_COMP_ID_VOL_CTRL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_vol_ctrl_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

INT32 a_vol_ctrl_hide (VOID)
{
	return _vol_ctrl_hide();
}

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
#ifndef LINUX_TURNKEY_SOLUTION
    CHAR        s_active_app[APP_NAME_MAX_LEN + 1] = {0};
    a_am_get_active_app(s_active_app);
    if (0 == c_strcmp(s_active_app, "mmp"))
    {
        ui1_g_ui_attr = 0;
        _vol_ctrl_hide_volume(&t_g_vol_ctrl);
        c_wgl_set_focus(h_g_mmp_focus, WGL_SYNC_AUTO_REPAINT);
        c_wgl_set_active_app(mmp_main_get_app());
        c_wgl_set_app_order(mmp_main_get_app(), ui1_g_mmp_app_order);
        return;
    }
#endif

    /* execute in navigator's thread context */
    nav_hide_component(NAV_COMP_ID_VOL_CTRL);
#ifdef LINUX_TURNKEY_SOLUTION
    /* Force to hide vol_ctrl because NAV is paused. */
    _vol_ctrl_hide_volume(&t_g_vol_ctrl);
    #if 0    /* Mark for fix CR 329430 */
    if (a_tv_net_get_tv_svc_status () == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        nav_view_set_focus();
    }
    #endif
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_vol_ctrl_timeout_to_hide, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_show_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_show_volume(
                    VOL_CTRL_T*                 pt_this,
                    UINT16                      ui2_vol_ch_id
                    )
{
    INT16 i2_volume  = 0;
    INT16 i2_max_val = 0;
    INT16 i2_min_val = 0;
    INT32 i4_ret;

    i4_ret = a_cfg_av_get(ui2_vol_ch_id, &i2_volume);
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

    DBG_LOG_PRINT(("BT_HEADPHONES_NAV : [%s,%s(),%d] : i2_volume: %d", __FILE__, __FUNCTION__, __LINE__, i2_volume));

    i4_ret = a_cfg_av_get_min_max(ui2_vol_ch_id, &i2_min_val, &i2_max_val);
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

	c_wgl_set_app_order(t_g_navigator.h_app, WGL_APP_TOPMOST);

    i4_ret = pt_this->t_view_hdlr.pf_show_volume(
                    pt_this->ui1_crnt_au_ch_idx,
                    i2_min_val,
                    i2_max_val,
                    i2_volume
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_show_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _bt_vol_ctrl_show_volume(VOL_CTRL_T *pt_this, UINT16 ui2_vol_ch_id )
{
    INT16 i2_volume = 0;
    INT32 i4_ret;

    if(pt_this->b_is_volume_event) {
        i2_volume = pt_this->i2_volume; 
        pt_this->b_is_volume_event = FALSE;
        DBG_LOG_PRINT(("BT_HEADPHONES: static %s,%d Received Volume SHOW Event Volume is : %d \r\n", __FUNCTION__,__LINE__, i2_volume));
    } else {
        i4_ret = a_cfg_av_get(ui2_vol_ch_id, &i2_volume);
        if (i4_ret != APP_CFGR_OK) {
            return NAVR_FAIL;
        }
        DBG_LOG_PRINT(("BT_HEADPHONES_NAV : [%s,%s(),%d] : i2_volume: %d", __FILE__, __FUNCTION__, __LINE__, i2_volume));
    }

    c_wgl_set_app_order(t_g_navigator.h_app, WGL_APP_TOPMOST);

    i4_ret = pt_this->t_view_hdlr.pf_show_volume(
        //pt_this->ui1_crnt_au_ch_idx, MIN_VOLUME, MAX_VOLUME, i2_volume);
        pt_this->ui1_crnt_au_ch_idx, BT_MIN_VOLUME, BT_MAX_VOLUME, i2_volume);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_show_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_show_volume(
                    VOL_CTRL_T*                 pt_this
                    )
{
    UINT16 ui2_vol_ch_id = 0;
    INT32  i4_ret;

    vol_ctrl_reset_timer(pt_this);

    i4_ret = vol_ctrl_get_vol_cfg_id(pt_this->ui1_crnt_au_ch_idx, &ui2_vol_ch_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if(pt_this->b_is_bt_headphones_active == FALSE)
    {
        i4_ret = _vol_ctrl_show_volume(pt_this, ui2_vol_ch_id);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    }
    else
    {
        i4_ret = _bt_vol_ctrl_show_volume(pt_this, ui2_vol_ch_id);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    }

    nav_set_component_visible(NAV_COMP_ID_VOL_CTRL);
    pt_this->b_is_volume_on = TRUE;

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_next_audio_channel
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_next_audio_channel(
                    VOL_CTRL_T*                 pt_this
                    )
{
    UINT16 ui2_vol_ch_id;
    INT32  i4_ret;

    i4_ret = vol_ctrl_next_vol_cfg_id(
                    &pt_this->ui1_crnt_au_ch_idx,
                    &ui2_vol_ch_id
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return _vol_ctrl_show_volume(pt_this, ui2_vol_ch_id);
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_prev_audio_channel
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_prev_audio_channel(
                    VOL_CTRL_T*                 pt_this
                    )
{
    UINT16 ui2_vol_ch_id;
    INT32  i4_ret;

    i4_ret = vol_ctrl_prev_vol_cfg_id(
                    &pt_this->ui1_crnt_au_ch_idx,
                    &ui2_vol_ch_id
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return _vol_ctrl_show_volume(pt_this, ui2_vol_ch_id);
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_set_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_set_mute(
                    VOL_CTRL_T*                 pt_this,
                    BOOL                        b_mute
                    )
{
    INT32 i4_ret;

    if (b_mute == TRUE) {

        i4_ret = nav_set_mute(TRUE);
        if(i4_ret < NAVR_OK)
        {
            return NAVR_FAIL;
        }

        i4_ret = nav_hide_component(NAV_COMP_ID_VOL_CTRL);
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }

        i4_ret =_vol_ctrl_hide_mute(pt_this, FALSE);
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    } else {

        i4_ret = nav_set_mute(FALSE);
        if(i4_ret < NAVR_OK)
        {
            return NAVR_FAIL;
        }

        i4_ret =_vol_ctrl_hide_mute(pt_this, TRUE);
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_set_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_set_mute_ex(
                    VOL_CTRL_T*                 pt_this,
                    BOOL                        b_mute,
                    BOOL                        b_to_show
                    )
{
    INT32 i4_ret;

    if (b_mute == TRUE) {

        i4_ret = nav_set_mute(TRUE);
        if(i4_ret < NAVR_OK)
        {
            return NAVR_FAIL;
        }

        i4_ret = nav_hide_component(NAV_COMP_ID_VOL_CTRL);
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }

		if (b_to_show) {
			nav_hide_components(COMP_VIEW_EXC_SET_VOL_CTRL_MUTE);
	        i4_ret =_vol_ctrl_hide_mute(pt_this, FALSE);
	        if (i4_ret != NAVR_OK) {
	            return NAVR_FAIL;
	        }
		}
    } else {

        i4_ret = nav_set_mute(FALSE);
        if(i4_ret < NAVR_OK)
        {
            return NAVR_FAIL;
        }

        i4_ret =_vol_ctrl_hide_mute(pt_this, TRUE);
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _tts_play_vol_value
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _tts_play_vol_value(VOID)
{
#ifdef APP_TTS_SUPPORT
		VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
		UINT16	ui2_vol_ch_id  = 0;
		INT16	i2_volume	   = 0;
		INT32	i4_ret		   = 0;
		CHAR	s_vol[16+1]    = {0};
		UTF16_T w2s_str[16+1]  = {0};

		i4_ret = vol_ctrl_get_vol_cfg_id(pt_this->ui1_crnt_au_ch_idx, &ui2_vol_ch_id);
		if (i4_ret != NAVR_OK) {
			DBG_ERROR(("%s,%d [vol] get vol cfg id fail \r\n",__FUNCTION__,__LINE__));
		}
		i4_ret = a_cfg_av_get(ui2_vol_ch_id, &i2_volume);
		if (i4_ret != APP_CFGR_OK) {
			DBG_ERROR(("%s,%d [vol] get current vol value fail \r\n",__FUNCTION__,__LINE__));
		}

		c_sprintf(s_vol, "Volume %d", i2_volume);

		c_uc_ps_to_w2s(s_vol, w2s_str, c_strlen(s_vol));

		a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));

		DBG_INFO(("%s,%d [vol] current_vol=%s \r\n",__FUNCTION__,__LINE__,s_vol));
#endif

}

/*-----------------------------------------------------------------------------
 * Name
 *      a_tts_play_vol_value
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID a_tts_play_vol_value(VOID)
{
    _tts_play_vol_value();
}

INT32 bt_vol_ctrl_set_mute(VOL_CTRL_T *pt_this)
{
    if(pt_this->b_is_mute_event)
    {
        DBG_INFO(("[BT_HEADPHONES]: {%s() %d}. receive event from bt stack b_is_muted = %d\n",__FUNCTION__, __LINE__,pt_this->b_is_mute_on));
        pt_this->t_view_hdlr.pf_show_mute(pt_this->b_is_mute_on);
        pt_this->b_is_mute_event = FALSE;
        if(pt_this->b_is_mute_on)
        {
            _tts_play_vol_value();
        }
        else
        {
#ifdef APP_TTS_SUPPORT
            if(TTS_STR_ST_PLAYING == a_app_tts_get_string_state())
            {
                a_app_tts_stop(APP_TTS_STOP_FORCE);
            }
#endif
        }

        a_vol_ctrl_tts_set_mute(pt_this->b_is_mute_on);
    }
    else
    {
        if(pt_this->b_is_bt_req_in_progress == FALSE)
        {
            pt_this->b_is_bt_req_in_progress = TRUE;
            menu_request_context_switch(set_bt_headset_mute, NULL, NULL, NULL);
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%s,%d  bt_vol_ctrl_set_mute() send request to bt stack b_is_mute_on = %d \r\n", __FILE__, __FUNCTION__, __LINE__, pt_this->b_is_mute_on));
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_increase_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

INT32 bt_vol_ctrl_increase_volume(VOL_CTRL_T *pt_this)
{
    INT16 i2_volume = 0;
    INT32 i4_ret;
    BOOL b_mute = FALSE;

    a_mtktvapi_volctrl_set_vol_adjust_reason(MTKTVAPI_VOLCTRL_VOL_ADJUST_REAONS_BY_RCU_KEY);

    if(pt_this->b_is_volume_event)
    {
        i2_volume = pt_this->i2_volume;
        DBG_LOG_PRINT(("%s,%d Received Volume UP Event\r\n", __FUNCTION__,__LINE__));
    }
    else
    {
        if(pt_this->b_is_bt_req_in_progress == FALSE)
        {
            pt_this->b_is_bt_req_in_progress = TRUE;
            menu_request_context_switch(increase_bt_headset_volume, NULL, NULL, NULL);
            /*i2_volume = increase_bt_headset_volume(); */
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%s,%d  increase_bt_headset_volume: %d\r\n", __FILE__, __FUNCTION__, __LINE__, i2_volume));
        }
        return NAVR_OK;
    }

    nav_get_mute(&b_mute);
    if (b_mute)
    {
        _tts_play_vol_value();
        pt_this->t_view_hdlr.pf_show_mute(FALSE);
    }

#ifdef APP_CEC_SUPPORT
    if (pt_this->b_is_volume_visible == TRUE && pt_this->b_is_sam_on == FALSE)
#else
    if (pt_this->b_is_volume_visible == TRUE)
#endif
    {
#ifdef APP_ZOOM_MODE_SUPPORT
        a_zoom_mode_set_sector_id(
            ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_VOL_CTRL));
#endif
        return NAVR_OK;
    }
    else
    {
        _vol_ctrl_hide_mute(pt_this, TRUE);
        return NAVR_NO_ACTION;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_increase_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

INT32 bt_vol_ctrl_set_volume(VOL_CTRL_T *pt_this, int value)
{
    //a_mtktvapi_volctrl_set_vol_adjust_reason(MTKTVAPI_VOLCTRL_VOL_ADJUST_REAONS_BY_RCU_KEY);

    if(pt_this->b_is_bt_req_in_progress == FALSE)
    {
        pt_this->b_is_bt_req_in_progress = TRUE;

        int* data = malloc(sizeof(int));
        if( data != NULL )
        {
            *data = value;
            menu_request_context_switch( set_bt_headset_volume, data, NULL, NULL);
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%s,%d  set_bt_headset_volume: %d\r\n", __FILE__, __FUNCTION__, __LINE__, value));
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_decrease_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 bt_vol_ctrl_decrease_volume(VOL_CTRL_T *pt_this)
{
    INT16 i2_volume = 0;
    INT32 i4_ret;

    a_mtktvapi_volctrl_set_vol_adjust_reason(MTKTVAPI_VOLCTRL_VOL_ADJUST_REAONS_BY_RCU_KEY);

    if(pt_this->b_is_volume_event)
    {
        i2_volume = pt_this->i2_volume;
        DBG_LOG_PRINT(("%s,%d Received Volume DOWN Event\r\n", __FUNCTION__,__LINE__));
    }
    else
    {
        if(pt_this->b_is_bt_req_in_progress == FALSE)
        {
            pt_this->b_is_bt_req_in_progress = TRUE;
            menu_request_context_switch(decrease_bt_headset_volume, NULL, NULL, NULL);
            /*i2_volume = decrease_bt_headset_volume();*/
            DBG_LOG_PRINT(("BT_HEADPHONES: %s,%s,%d  decrease_bt_headset_volume: %d\r\n", __FILE__, __FUNCTION__, __LINE__, i2_volume));
        }
        return NAVR_OK;
    }

#ifdef APP_CEC_SUPPORT
    if (pt_this->b_is_volume_visible == TRUE && pt_this->b_is_sam_on == FALSE)
#else
    if (pt_this->b_is_volume_visible == TRUE)
#endif
    {
#ifdef APP_ZOOM_MODE_SUPPORT
        a_zoom_mode_set_sector_id(
            ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_VOL_CTRL));
#endif
        return NAVR_OK;
    }
    else
    {
        _vol_ctrl_hide_mute(pt_this, TRUE);
        return NAVR_NO_ACTION;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_increase_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_increase_volume(
                    VOL_CTRL_T*                 pt_this
                    )
{
    UINT16 ui2_vol_ch_id;
    INT16  i2_volume = 0;
    INT32  i4_ret;
    BOOL   b_mute = FALSE;

    a_mtktvapi_volctrl_set_vol_adjust_reason(MTKTVAPI_VOLCTRL_VOL_ADJUST_REAONS_BY_RCU_KEY);

    i4_ret = vol_ctrl_get_vol_cfg_id(pt_this->ui1_crnt_au_ch_idx, &ui2_vol_ch_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = a_tv_vol_incr(ui2_vol_ch_id, &i2_volume);
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

	nav_get_mute (&b_mute);
	if (b_mute)
	{
		_tts_play_vol_value();
		pt_this->t_view_hdlr.pf_show_mute(FALSE);
	}


#ifdef APP_CEC_SUPPORT
    if (pt_this->b_is_volume_visible == TRUE &&
        pt_this->b_is_sam_on == FALSE)
#else
    if (pt_this->b_is_volume_visible == TRUE)
#endif
    {
        i4_ret = pt_this->t_view_hdlr.pf_update_volume(i2_volume);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
		#ifdef APP_ZOOM_MODE_SUPPORT
    	a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_VOL_CTRL));
		#endif
        return NAVR_OK;
    } else {
        _vol_ctrl_hide_mute(pt_this, TRUE);
        return NAVR_NO_ACTION;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_decrease_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_decrease_volume(
                    VOL_CTRL_T*                 pt_this
                    )
{
    UINT16 ui2_vol_ch_id;
    INT16  i2_volume = 0;
    INT32  i4_ret;

	a_mtktvapi_volctrl_set_vol_adjust_reason(MTKTVAPI_VOLCTRL_VOL_ADJUST_REAONS_BY_RCU_KEY);

    i4_ret = vol_ctrl_get_vol_cfg_id(pt_this->ui1_crnt_au_ch_idx, &ui2_vol_ch_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = a_tv_vol_decr(ui2_vol_ch_id, &i2_volume);
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CEC_SUPPORT
        if (pt_this->b_is_volume_visible == TRUE &&
            pt_this->b_is_sam_on == FALSE)
#else
        if (pt_this->b_is_volume_visible == TRUE)
#endif
    {
        i4_ret = pt_this->t_view_hdlr.pf_update_volume(i2_volume);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
		#ifdef APP_ZOOM_MODE_SUPPORT
    	a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_VOL_CTRL));
		#endif
        return NAVR_OK;
    } else {
        _vol_ctrl_hide_mute(pt_this, TRUE);
        return NAVR_NO_ACTION;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL a_vol_ctrl_tts_get_mute(VOID)
{
    return b_tts_mute_key_status;
}
BOOL a_vol_ctrl_tts_set_mute(BOOL b_mute)
{
     b_tts_mute_key_status = b_mute;
     return b_tts_mute_key_status;
}

INT32 vol_ctrl_mute(
                    VOL_CTRL_T*                 pt_this
                    )
{
    BOOL    b_is_muted;
    nav_get_mute(&b_is_muted);
    if (b_is_muted==TRUE)
    {
        rest_event_notify("tv_settings/audio/mute",0,"");
        rest_event_notify("audio/volume/mute",0,"");
        pt_this->b_is_mute_on = FALSE;
        pt_this->t_view_hdlr.pf_show_mute(FALSE);
		_tts_play_vol_value();
	}
    else
    {
        rest_event_notify("tv_settings/audio/mute",1 ,"");
        rest_event_notify("audio/volume/mute",1,"");
        pt_this->b_is_mute_on = TRUE;
        pt_this->t_view_hdlr.pf_show_mute(TRUE);
#ifdef APP_TTS_SUPPORT
        if(TTS_STR_ST_PLAYING == a_app_tts_get_string_state())
        {
            a_app_tts_stop(APP_TTS_STOP_FORCE);
        }
#endif
    }
    /*press mute key and record it's status*/
    DBG_INFO(("[mute key tts +++] {%s() %d}. set@ b_is_muted = %d\n",__FUNCTION__, __LINE__,!b_is_muted));
    a_vol_ctrl_tts_set_mute(!b_is_muted);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID vol_ctrl_reset_timer(
                    VOL_CTRL_T*                 pt_this
                    )
{
    INT32 i4_ret;

    _vol_ctrl_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    VOLUME_TIMER_DELAY,
                    X_TIMER_FLAG_ONCE,
                    _vol_ctrl_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start vol_ctrl::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_toggle_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_toggle_mute(
                    VOL_CTRL_T*                 pt_this
                    )
{
    BOOL  b_is_muted;
    INT32 i4_ret;

    i4_ret = nav_get_mute(&b_is_muted);
    if (i4_ret < NAVR_OK) {
        DBG_ERROR(("[NAV] nav_get_mute failed.\n"));
        return i4_ret;
    }

    if (b_is_muted == TRUE && pt_this->b_is_mute_on == FALSE) {
        /* just show muting icon if it is hide */
        i4_ret = _vol_ctrl_hide_mute(pt_this, FALSE);
    } else {
        i4_ret = vol_ctrl_set_mute(pt_this, (b_is_muted == TRUE ? FALSE : TRUE));
    }

    if (i4_ret != NAVR_OK) {
        return NAVR_OK;
    }

    nav_return_activation(NAV_COMP_ID_VOL_CTRL);

    return NAVR_OK;
}

INT32 vol_ctrl_update_volume(
                    VOL_CTRL_T*                 pt_this
                    )
{
    INT32 i4_ret         = 0;

    DBG_INFO(("vol_ctrl_update_volume ====>enter b_is_volume_on:%d\r\n",pt_this->b_is_volume_on));
    UINT16 ui2_vol_ch_id = 0;
   // INT32  i4_ret;

    if( pt_this->b_is_volume_on == TRUE)
    {
    #if 0
        vol_ctrl_reset_timer(pt_this);

        UINT16 ui2_vol_ch_id  = 0;
        INT16 i2_volume      = 0;

        i4_ret = vol_ctrl_get_vol_cfg_id(pt_this->ui1_crnt_au_ch_idx, &ui2_vol_ch_id);
        if (i4_ret != NAVR_OK)
        {
            return NAVR_FAIL;
        }
        i4_ret = a_cfg_av_get(ui2_vol_ch_id, &i2_volume);
        if (i4_ret != APP_CFGR_OK) {
            return NAVR_FAIL;
        }
        i4_ret = pt_this->t_view_hdlr.pf_update_volume(i2_volume);
    #else
       DBG_INFO(("===>current on mode b_is_sam_on:0x%x\r\n",pt_this->b_is_sam_on));
        vol_ctrl_reset_timer(pt_this);
      #ifdef APP_CEC_SUPPORT
        if (pt_this->b_is_sam_on == TRUE)
        {
            return NAVR_OK;
        }
    #endif
#if 0
    #ifndef APP_UNMUTE_AS_INCR_VOL
        i4_ret = vol_ctrl_set_mute(pt_this, FALSE);
        if (i4_ret != NAVR_OK) {
            DBG_ERROR((_ERROR_HEADER"vol_ctrl_set_mute failed! ret = %d\r\n", i4_ret));
            return i4_ret;
        }
    #endif
#endif
        i4_ret = vol_ctrl_get_vol_cfg_id(pt_this->ui1_crnt_au_ch_idx, &ui2_vol_ch_id);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        i4_ret = _vol_ctrl_show_volume(pt_this, ui2_vol_ch_id);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        nav_set_component_visible(NAV_COMP_ID_VOL_CTRL);
        pt_this->b_is_volume_on = TRUE;

    #endif

       }
       else
       {
           DBG_INFO(("{VOL_CTRL}volume bar is not show,show it \r\n"));
           i4_ret =  vol_ctrl_show_volume(pt_this);
       }

       return i4_ret;

}

#ifndef APP_HIDE_MUTE_AS_PAUSED
  #ifndef APP_CUSTOM_DEF_MUTE_ICON_COEXIST_APP
    #include "menu2/a_menu.h"
    #include "epg/a_epg.h"
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_is_mute_icon_coexist_app
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL vol_ctrl_is_mute_icon_coexist_app(
                    CHAR*                       ps_app_name
                    )
{
    if (c_strcmp(MENU_NAME, ps_app_name) == 0) {
        return TRUE;
    }

    if (c_strcmp(EPG_NAME, ps_app_name) == 0) {
        return TRUE;
    }

    return FALSE;
}
  #endif
#endif

//#if APP_CEC_SAC_VOL_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_is_cec_sac_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL vol_ctrl_is_cec_sac_mode(VOID)
{
	UINT8 ui1_icl_val;
	SIZE_T z_size = sizeof(UINT8);
		
	//VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
		
	a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),&ui1_icl_val,&z_size);
	DBG_LOG_PRINT(("%s,%d vol_ctrl_is_cec_sac_mode\r\n", __FUNCTION__, __LINE__));
		
	return ui1_icl_val;
}


static INT32 _vol_ctrl_handle_cec_sac_mode(
                    VOL_CTRL_T*                pt_this,
                    NAV_UI_MSG_VOL_CHG_INFO_T* pt_vol_info
                    )
{
    INT32 i4_ret;

    if (!pt_vol_info || !pt_this) {
        return (NAVR_INV_ARG);
    }

    pt_this->e_cec_sac_vol_info = pt_vol_info->e_info_type;

    switch (pt_vol_info->e_info_type)
    {
    case NAV_VOL_INFO_VOLUME_UP:
    case NAV_VOL_INFO_VOLUME_DOWN:
        if (pt_this->b_is_volume_visible == TRUE)
        {
            nav_grab_activation(NAV_COMP_ID_VOL_CTRL);
            vol_ctrl_reset_timer(pt_this);
            i4_ret = pt_this->t_view_hdlr.pf_show_volume(
                            0,
                            0,
                            100,
                            0
                            );
            if (i4_ret != NAVR_OK) {
                return i4_ret;
            }
            nav_set_component_visible(NAV_COMP_ID_VOL_CTRL);
            pt_this->b_is_volume_on = TRUE;
        }
        break;
    case NAV_VOL_INFO_VOLUME_ONLY:
    case NAV_VOL_INFO_MUTE_ONLY:
    case NAV_VOL_INFO_VOLUME_AND_MUTE:
        if(b_edid_change_mute_process)
        {
            b_edid_change_mute_process = FALSE;//reset b_edid_change_mute_process after process NAV_VOL_INFO_MUTE_ONLY
            break;
        }
        else if (pt_this->b_is_volume_visible == TRUE)
        {
            vol_ctrl_reset_timer(pt_this);
            i4_ret = pt_this->t_view_hdlr.pf_show_mute(pt_vol_info->b_mute);
            if (i4_ret != NAVR_OK) {
                    return i4_ret;
                }
            i4_ret = pt_this->t_view_hdlr.pf_show_volume(
                                0,
                                0,
                                100,
                                (INT16)pt_vol_info->ui1_vol
                                );
            if (i4_ret != NAVR_OK) {
                    return i4_ret;
                }
            nav_set_component_visible(NAV_COMP_ID_VOL_CTRL);
            pt_this->b_is_volume_on = TRUE;
        }
        break;

    default:
        break;
    }

    return (NAVR_OK);
}
//#endif /* APP_CEC_SAC_VOL_SUPPORT */

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_vol_ctrl_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_vol_ctrl_register(
                    VOL_CTRL_VIEW_HDLR_T*       pt_view_hdlr
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    NAV_COMP_T  t_comp;
    INT32       i4_ret;

    c_memset (&t_comp, 0, sizeof (NAV_COMP_T));

    /* NAV_COMP_ID_VOL_CTRL */
    t_comp.pf_init           = _vol_ctrl_init;
    t_comp.pf_deinit         = _vol_ctrl_deinit;
    t_comp.pf_is_key_handler = _vol_ctrl_is_key_handler;
    t_comp.pf_activate       = _vol_ctrl_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _vol_ctrl_hide;
    t_comp.pf_handle_msg     = _vol_ctrl_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_VOL_CTRL, &t_comp, COMP_EXC_SET_VOL_CTRL);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_view_hdlr == NULL) {
        vol_ctrl_view_register_default_hdlr(&pt_this->t_view_hdlr);
    } else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_vol_ctrl_set_visibility
 * Description
 *      let other(components) to set volume change silently (no OSD) or loudly
 *      (with OSD)
 * Input arguments
 *      b_is_volume_visible     TRUE  = loudly
 *                              FALSE = silently
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_vol_ctrl_set_visibility(
                    BOOL                        b_is_volume_visible
                    )
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;

    pt_this->b_is_volume_visible = b_is_volume_visible;

    if (pt_this->b_is_volume_visible == FALSE
            && pt_this->b_is_volume_on == TRUE) {
        nav_hide_component(NAV_COMP_ID_VOL_CTRL);
    }

    return NAVR_OK;

}

#ifndef APP_PORTING //temp add API for build error
INT32 a_vol_ctrl_set_mute_key_up (BOOL b_is_up)
{
    return NAVR_OK;
}
#endif

#ifdef APP_CEC_SUPPORT
BOOL a_vol_ctrl_is_cec_mode(VOID)
{
	 VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
     return pt_this->b_is_sam_on;
}
#endif

INT32 a_vol_ctrl_get_current_audio_channel(UINT16 ui2_vol_ch_id)
{
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    INT32       i4_ret = 0;
    i4_ret = vol_ctrl_get_vol_cfg_id(pt_this->ui1_crnt_au_ch_idx, &ui2_vol_ch_id);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }
    return NAVR_OK;
}

INT32 a_vol_ctrl_prev_audio_channel(VOID)
{
    INT32       i4_ret = 0;
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    i4_ret = vol_ctrl_prev_audio_channel(pt_this);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }
    return NAVR_OK;
}

INT32 a_vol_ctrl_next_audio_channel(VOID)
{
    INT32       i4_ret = 0;
    VOL_CTRL_T* pt_this = &t_g_vol_ctrl;
    i4_ret = vol_ctrl_next_audio_channel(pt_this);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }
    return NAVR_OK;
}

void bt_vol_ctrl_post_bt_event(void *pv_tag1, void *pv_tag2, void *pv_tag3)
{

    DBG_LOG_PRINT(("%s,%d Entry\r\n", __FUNCTION__, __LINE__));
    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_VOL_CTRL),
                              NAV_UI_MSG_BT_VOL_CTRL, 
                              pv_tag1);

    DBG_LOG_PRINT(("%s,%d Exit\r\n", __FUNCTION__, __LINE__));
}

#endif /* APP_VOLUME_CTRL */
