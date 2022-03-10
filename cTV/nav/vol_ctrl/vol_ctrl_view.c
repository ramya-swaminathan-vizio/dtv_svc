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
 *                                                                             *
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
 * $RCSfile: vol_ctrl_view.c,v $
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
#include "c_iom.h"
#include "c_wgl_rect.h"

#include "app_util/a_cfg.h"
#include "nav/vol_ctrl/vol_ctrl.h"
#include "nav/nav_common.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "res/nav/vol_ctrl/vol_ctrl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "app_util/a_ui.h"
#include "rest/a_rest_event.h"

#include "menu2/menu_vizio/menu_page_bt_devices.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#define DBG_INFO DBG_LOG_PRINT

#define TXT_HL_CLR_TXTT           COLOR_whitee
#define TXT_HL_CLR_TXT_bann       COLOR_ban_whitee

const GL_COLOR_T COLOR_whitee =
{
    255, {255}, {255}, {255}
};

const GL_COLOR_T COLOR_ban_whitee =
{
    0, {0}, {0}, {0}
};

#ifdef LINUX_TURNKEY_SOLUTION
#include "msgconvert/a_msgconvert.h"
#endif

//#if APP_CEC_SAC_VOL_SUPPORT
#include "res/app_util/ui/ui_custom.h" /* Add for _vol_ctrl_view_init_cec_sac_volume() */
#include "wizard/wzd.h"
//#endif

#include "res/nav/nav_dbg.h"

#ifdef APP_VOLUME_CTRL
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                         (TRUE)
#define VOL_CTRL_VIEW_AUD_SYS_TITLE_W           (100)

typedef struct _VOL_CTRL_VIEW_T
{
    VOL_CTRL_T*             pt_ctrl;

    HANDLE_T                h_volume_frame;
    BOOL                    b_mute_repeat;
    BOOL                    b_mute_release;
    HANDLE_T                h_iom;
#ifdef APP_MUTE_DISP_AS_TEXT
    HANDLE_T                h_mute_text;
    VOL_CTRL_MUTE_RC_T      t_rc;
    HANDLE_T                h_gui_lang_cfg_nfy;
    #ifdef APP_CC_WITH_SOLE_OSD_PLANE
    HANDLE_T                h_mute_text_mib;
  #endif
#else
    HANDLE_T                h_mute_icon;
    WGL_HIMG_TPL_T          h_img_mute;
  #ifdef APP_CC_WITH_SOLE_OSD_PLANE
    HANDLE_T                h_mute_icon_mib;
  #endif
#endif
#ifndef APP_PROGRESSBAR_FAST_MODE_DISABLE
    UINT32                  ui4_fm_last_tick;      /* Fast Mode: Last tick */
    UINT8                   ui1_fm_delta_idx;      /* Fast Mode: Delta Index */
    BOOL                    b_repaint_vol_ctrl;
#endif

//#if APP_CEC_SAC_VOL_SUPPORT
    HANDLE_T                h_volume_frame_ex;
    HANDLE_T                h_volume_txt_title;
    WGL_HIMG_TPL_T          h_volume_frame_ex_img_bk;
//#endif

#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
	HANDLE_T                h_volume_ctrl_off_frm;
	HANDLE_T                h_volume_ctrl_off_icon;
	HANDLE_T                h_volume_ctrl_off_icon_inactive;
	HANDLE_T                h_volume_ctrl_off_zoom_icon_inactive;
	HANDLE_T                h_volume_ctrl_off_txt;
	HANDLE_T				h_volume_ctrl_off_timer;
	WGL_HIMG_TPL_T          h_volume_ctrl_off_frm_bk;
	WGL_HIMG_TPL_T          h_volume_ctrl_off_icon_bk;
	WGL_HIMG_TPL_T          h_volume_ctrl_off_icon_inactive_bk;
	WGL_HIMG_TPL_T          h_volume_ctrl_off_zoom_icon_inactive_bk;
	BOOL                    b_is_need_show_vol_off;
	UINT16                 	ui2_cfg_nfy_id_audio;    		/* The ACFG audio notify id */
	UINT16                 	ui2_cfg_nfy_id_ana_aud_out;   	/* The ACFG analog audio out notify id */
	UINT16                  ui2_cfg_nfy_id_tv_speaker;
#endif

} VOL_CTRL_VIEW_T;

#ifndef APP_PROGRESSBAR_FAST_MODE_DISABLE
  #ifndef VOL_CTRL_FAST_MODE_ARRAY
    #define VOL_CTRL_FAST_MODE_ARRAY    { 1,1,1,2,2,2,4,4,4,8 }
  #endif
static UINT8 aui1_g_fast_mode_deltas[]   = VOL_CTRL_FAST_MODE_ARRAY;
static const UINT8 ui1_g_fast_mode_deltas_size = (UINT8)(sizeof(aui1_g_fast_mode_deltas)/sizeof(UINT8));
#endif

#ifdef APP_PROGRESSBAR_FAST_MODE_DISABLE
  #define _VOL_CTRL_VIEW_RCU_KEY_HANDLER(p1, p2) _vol_ctrl_view_rcu_key_handler(p1, p2)
#else
    static VOID _vol_ctrl_view_reset_fast_mode(
                        VOL_CTRL_VIEW_T*            pt_view
                        );
  #define _VOL_CTRL_VIEW_RCU_KEY_HANDLER(p1, p2) _vol_ctrl_view_rcu_key_fast_mode(p1, p2)
#endif
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static VOL_CTRL_VIEW_T t_g_vol_ctrl_view = {0};

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
//#if APP_CEC_SAC_VOL_SUPPORT
static INT32 _vol_ctrl_view_init_cec_sac_volume(
                    VOL_CTRL_VIEW_T*            pt_view,
                    HANDLE_T                    h_canvas
                    );
static INT32 _vol_ctrl_view_deinit_cec_sac_volume(
                    VOL_CTRL_VIEW_T*            pt_view
                    );
//#endif

#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
static INT32 _vol_ctrl_view_init_vol_off(
                    VOL_CTRL_VIEW_T*            pt_view,
                    HANDLE_T                    h_canvas
                    );
static INT32 _vol_ctrl_view_deinit_vol_off(
                    VOL_CTRL_VIEW_T*            pt_view
                    );
static INT32 _vol_ctrl_view_show_vol_off(VOID);
#endif

/*-----------------------------------------------------------------------------
 * handle submenu in vol +/-
 *---------------------------------------------------------------------------*/

static BOOL vol_activate_is_on = FALSE;

BOOL vol_banber_is_show_state(VOID)
{
	VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;

	if (pt_view->pt_ctrl->b_is_volume_on == TRUE)
	{
		return TRUE;
	}
	/*fisrt press +/- key*/
	else
	{
		if (vol_activate_is_on == TRUE)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*
static INT32 _get_vol_base_frame_top(VOID)
{
	INT32 i_top = (INT32)UI_VOL_BAR_BASE_FRM_Y;

	if (a_mmp_is_video_full_screen())
	{
		i_top = i_top - (INT32)((UI_THIN_GRID_H)* 9);
	}

	return i_top;
}
*/

#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
static BOOL _get_aud_speaker_state(VOID)
{
    UINT16  ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16  ui2_aud_out_mask;
    INT16   i2_val;

    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

    return (BOOL)(ui2_aud_out_mask & SCC_AUD_OUT_PORT_SPEAKER);
}

static BOOL _get_ana_aud_out_fixed (VOID)
{
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;

    a_cfg_custom_get_ana_audio_out(&e_aud_out);
    if(e_aud_out == A_CFG_CUSTOM_ANALOG_AUD_OUT_FIXED)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_view_vol_off_cfg_chg_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _vol_ctrl_view_vol_off_cfg_chg_cb(
					UINT16			ui2_nfy_id,
					VOID*			pv_tag,
					UINT16			ui2_id
					)
{
	VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
	UINT16      ui2_aud_out_id = CFG_GET_SETTING(ui2_id);

	if(pt_view->ui2_cfg_nfy_id_audio != ui2_nfy_id &&
	   pt_view->ui2_cfg_nfy_id_ana_aud_out != ui2_nfy_id)
	{
		return;
	}

	if((APP_CFG_RECID_AUD_OUT_PORT == ui2_aud_out_id) ||
       (APP_CFG_RECID_CUSTOM_ANALOG_AUD_OUT == ui2_aud_out_id))
    {
    	if (FALSE == _get_aud_speaker_state() && _get_ana_aud_out_fixed())
		{
			pt_view->b_is_need_show_vol_off = TRUE;

			/* hide pre vol osd first */
			nav_hide_component(NAV_COMP_ID_VOL_CTRL);
		}
		else
		{
			pt_view->b_is_need_show_vol_off = FALSE;

			/* hide vol off osd */
			c_wgl_set_visibility(pt_view->h_volume_ctrl_off_frm, WGL_SW_HIDE);
			c_wgl_repaint(pt_view->h_volume_ctrl_off_frm, NULL, TRUE);
		}

		if((FALSE == _get_aud_speaker_state()) && (_get_ana_aud_out_fixed() == FALSE))
	    {
	        pt_view->pt_ctrl->b_is_aud_sys_visible = TRUE;
	    }
	    else
	    {
	        pt_view->pt_ctrl->b_is_aud_sys_visible = FALSE;
	    }
    }

	return;
}

#endif

static VOID _vol_ctrl_view_tv_speaker_cfg_chg_cb(
					UINT16			ui2_nfy_id,
					VOID*			pv_tag,
					UINT16			ui2_id
					)
{
    UINT16           ui2_aud_out_id = CFG_GET_SETTING(ui2_id);
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;

    if(pt_view->ui2_cfg_nfy_id_tv_speaker != ui2_nfy_id)
	{
		return;
	}

    if(APP_CFG_RECID_AUD_OUT_PORT == ui2_aud_out_id)
    {
        if((FALSE == _get_aud_speaker_state()) && (_get_ana_aud_out_fixed() == FALSE))
	    {
	        pt_view->pt_ctrl->b_is_aud_sys_visible = TRUE;
	    }
	    else
	    {
	        pt_view->pt_ctrl->b_is_aud_sys_visible = FALSE;
	    }
    }

    return;
}

#ifdef APP_MUTE_DISP_AS_TEXT
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_set_visibility_and_repaint
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_set_visibility_and_repaint(
                    HANDLE_T                    h_widget,
                    WGL_SW_CMD_T                e_sw_cmd
                    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_widget, e_sw_cmd);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(h_widget, NULL, IS_SYNC_REPAINT);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_rcu_key_handler(
                    VOL_CTRL_VIEW_T*            pt_view,
                    UINT32                      ui4_key_code
                    )
{
    INT32 i4_ret = NAVR_OK;

    switch(ui4_key_code) {
#if 0 /*for displaying Input Source concurrently.*/
    case BTN_CURSOR_DOWN:
//#if APP_CEC_SAC_VOL_SUPPORT
        if (vol_ctrl_is_cec_sac_mode())
        {
            return NAVR_OK;
        }
//#endif
        i4_ret = vol_ctrl_next_audio_channel(pt_view->pt_ctrl);
        break;
    case BTN_CURSOR_UP:
//#if APP_CEC_SAC_VOL_SUPPORT
        if (vol_ctrl_is_cec_sac_mode())
        {
            return NAVR_OK;
        }
//#endif
        i4_ret = vol_ctrl_prev_audio_channel(pt_view->pt_ctrl);
        break;
#endif
    case BTN_VOL_UP:
        if (!pt_view->b_mute_release)
        {
            if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
            {
                i4_ret = vol_ctrl_increase_volume(pt_view->pt_ctrl);
            }
            else
            {
                i4_ret = bt_vol_ctrl_increase_volume(pt_view->pt_ctrl);
            }
        }
        break;
    case BTN_VOL_DOWN:
        if (!pt_view->b_mute_release)
        {
            if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
            {
                i4_ret = vol_ctrl_decrease_volume(pt_view->pt_ctrl);
            }
            else
            {
                i4_ret = bt_vol_ctrl_decrease_volume(pt_view->pt_ctrl);
            }
        }
        break;
    case BTN_SHOW_VOL_BAR:
        i4_ret = vol_ctrl_update_volume(pt_view->pt_ctrl);
        break;
    case BTN_MUTE:
        if (!pt_view->b_mute_release)
        {
            if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
            {
                i4_ret = vol_ctrl_mute(pt_view->pt_ctrl);
            }
            else
            { 
                i4_ret = bt_vol_ctrl_set_mute(pt_view->pt_ctrl);
            }
        }
        break;
#ifdef LINUX_TURNKEY_SOLUTION
    /*
     *  If NAV is paused, hide vol_ctrl when EXIT is pressed.
     */
    case BTN_EXIT:
        nav_hide_component(NAV_COMP_ID_VOL_CTRL);
        break;
#endif
    case BTN_PRG_DOWN:
    case BTN_PRG_UP:
    case BTN_PREV_PRG:
    {
        TV_WIN_ID_T e_focus_win = TV_WIN_ID_MAIN;
        ISL_REC_T   t_isl_rec = {0};


        nav_get_focus_id(&e_focus_win);
        nav_get_isl_rec(e_focus_win, &t_isl_rec);
        DBG_INFO(("<vol view> %s,%d,type:%d\n\r",__FILE__,__LINE__,t_isl_rec.e_src_type ));
        if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
        {
             nav_rcu_key_handler(ui4_key_code);
        }

    }
        return NAVR_OK;
    default:
        nav_rcu_key_handler(ui4_key_code);
        return NAVR_OK;
    }

    if (i4_ret == NAVR_OK) {
        vol_ctrl_reset_timer(pt_view->pt_ctrl);
    }

    return i4_ret;
}
#ifndef APP_PROGRESSBAR_FAST_MODE_DISABLE
/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_view_increase_delta_idx
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _vol_ctrl_view_increase_delta_idx(
                    UINT8*                      pui1_fm_delta_idx
                    )
{
    /* same logic as the one in menu_page_tree.c _increase_delta_idx */
    if((++(*pui1_fm_delta_idx)) >= ui1_g_fast_mode_deltas_size) {
        *pui1_fm_delta_idx = (UINT8)(ui1_g_fast_mode_deltas_size-1);
    }
}
/*----------------------------------------------------------------------------
 * Name: _vol_ctrl_view_get_delta_by_delta_idx
 *
 * Description: Fast mode supporting function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_get_delta_by_delta_idx(UINT8   ui1_fm_delta_idx)
{
    /* same logic as the one in menu_page_tree.c _get_delta_by_delta_idx */

    if (ui1_fm_delta_idx >= ui1_g_fast_mode_deltas_size)
    {
        ui1_fm_delta_idx = (UINT8) (ui1_g_fast_mode_deltas_size-1);
    }

    return (INT32) aui1_g_fast_mode_deltas[ui1_fm_delta_idx];
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_rcu_key_fast_mode
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_view_rcu_key_fast_mode(
                    VOL_CTRL_VIEW_T*            pt_view,
                    UINT32                      ui4_key_code
                    )
{
    /* same logic as the one in menu_page_tree.c _get_delta_by_delta_idx */
    INT32  i4_time;          /* Fast mode: iteration */
    INT32  i4_do_times = 1;  /* Fast mode: do how many times, if BTN_MUTE, always do one time */
    UINT32 ui4_cur_tick;     /* Fast mode: current tick */
    UINT32 ui4_delta_tick;   /* Fast mode: tick delta */
    INT32 i4_ret;

    if(ui4_key_code == BTN_VOL_UP || ui4_key_code == BTN_VOL_DOWN) {
        if(pt_view->ui4_fm_last_tick == 0) {
            pt_view->ui4_fm_last_tick = c_os_get_sys_tick();
            i4_do_times = 1;
        } else { /* ui4_fm_last_tick != 0 */
            ui4_cur_tick   = c_os_get_sys_tick();
            ui4_delta_tick = ui4_cur_tick - pt_view->ui4_fm_last_tick;
            if(ui4_delta_tick < 200) { /* ? 200 */
                _vol_ctrl_view_increase_delta_idx(&pt_view->ui1_fm_delta_idx);
            } else {
                pt_view->ui1_fm_delta_idx = 0;
            }
            pt_view->ui4_fm_last_tick = ui4_cur_tick;
        }
        i4_do_times = _vol_ctrl_view_get_delta_by_delta_idx(pt_view->ui1_fm_delta_idx);
    }

    for(i4_time = 0 ; i4_time < i4_do_times ; i4_time++) {
        if( i4_time == (i4_do_times - 1)) {
            /* Last iteration */
            pt_view->b_repaint_vol_ctrl = TRUE;
        } else {
            /* Not last iteration */
            pt_view->b_repaint_vol_ctrl = FALSE;
        }
        i4_ret = _vol_ctrl_view_rcu_key_handler(pt_view, ui4_key_code);

        if (i4_ret == NAVR_NO_ACTION) {
            /* This is caused by Vol+/- unmute. Reset fast mode. */
            _vol_ctrl_view_reset_fast_mode (pt_view);
            break;
        }
    }
}
/*---------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_reset_fast_mode
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_view_reset_fast_mode(
                    VOL_CTRL_VIEW_T*            pt_view
                    )
{
    /* Reset the tick & delta_idx */
    pt_view->ui4_fm_last_tick   = 0;
    pt_view->ui1_fm_delta_idx   = 0;
    pt_view->b_repaint_vol_ctrl = TRUE;
}
#else
#define _vol_ctrl_view_reset_fast_mode(p1)
#endif
/*---------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_volume_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_volume_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:
        _VOL_CTRL_VIEW_RCU_KEY_HANDLER(pt_view, (UINT32)pv_param1);
        break;
    case WGL_MSG_KEY_UP:
        _vol_ctrl_view_reset_fast_mode(pt_view);
        pt_view->b_mute_release = FALSE;
        break;
    default:
        break;
    }

    return a_ui_slider_bar_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2,
                    pt_view->pt_ctrl->b_is_bt_headphones_active);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_init_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_init_volume(
                    VOL_CTRL_VIEW_T*            pt_view,
                    HANDLE_T                    h_canvas
                    )
{
    UI_SLIDER_BAR_INIT_T t_slider_bar_init;
    WGL_PG_KEY_MAP_T     t_key_map;
    INT32                i4_ret;

    t_slider_bar_init.e_style                          = UI_SLIDER_BAR_STYLE_VOL;
    t_slider_bar_init.h_parent                         = h_canvas;
    t_slider_bar_init.pf_wdgt_proc                     = _vol_ctrl_view_volume_nfy_fct;
    t_slider_bar_init.pt_begin_offset                  = NULL;
    t_slider_bar_init.pf_ui_slider_bar_pos_chg_nfy_fct = NULL;
    t_slider_bar_init.pf_ui_slider_bar_get_pos_cb_fct  = NULL;

    i4_ret = a_ui_vol_ctrl_view_create (&t_slider_bar_init, &pt_view->h_volume_frame);
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_VOLUME_CTRL_CUSTOMIZED_BK_IMAGE
    i4_ret = vol_ctrl_custom_set_image(pt_view->h_volume_frame);
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }
#endif

    i4_ret = a_ui_slider_bar_set_alpha(
                    pt_view->h_volume_frame,
                    UI_SLIDER_BAR_COMP_ID_FRAME,
                    DEFAULT_BK_ALPHA
                    );
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_ui_slider_bar_set_alpha(
                    pt_view->h_volume_frame,
                    UI_SLIDER_BAR_COMP_ID_PGBAR,
                    DEFAULT_BK_ALPHA
                    );
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_float (pt_view->h_volume_frame, TRUE, FALSE);
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

    /* Set Key Map */
    c_memset(&t_key_map, 0, sizeof(WGL_PG_KEY_MAP_T));
    i4_ret = a_ui_slider_bar_set_key_map(pt_view->h_volume_frame, &t_key_map);
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

#ifdef APP_MUTE_DISP_AS_TEXT
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_set_mute_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_set_mute_skin(
                    VOL_CTRL_VIEW_T*            pt_view
                    )
{
    WGL_COLOR_INFO_T t_clr_info;
    WGL_INSET_T      t_inset;
    INT32            i4_ret;

    if (pt_view->t_rc.h_img_bk != NULL_HANDLE) {
        WGL_IMG_INFO_T t_img_info;

        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_view->t_rc.h_img_bk;
        t_img_info.u_img_data.t_standard.t_highlight = pt_view->t_rc.h_img_bk;
        t_img_info.u_img_data.t_standard.t_disable   = pt_view->t_rc.h_img_bk;

        i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
        if(i4_ret != WGLR_OK){
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_alpha(pt_view->h_mute_text, DEFAULT_BK_ALPHA);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
        i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text_mib,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
        if(i4_ret != WGLR_OK){
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_alpha(pt_view->h_mute_text_mib, DEFAULT_BK_ALPHA);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
#endif
    }

    /* set message color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = pt_view->t_rc.t_text_fg;
    t_clr_info.u_color_data.t_standard.t_enable    = pt_view->t_rc.t_text_fg;
    t_clr_info.u_color_data.t_standard.t_highlight = pt_view->t_rc.t_text_fg;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set msg font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)pt_view->t_rc.pt_text_font,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    /* set message color */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text_mib,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set msg font */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text_mib,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)pt_view->t_rc.pt_text_font,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif

    /* set event title inset */
    t_inset.i4_left   = MUTE_MSG_LEFT_INSET;
    t_inset.i4_right  = MUTE_MSG_RIGHT_INSET;
    t_inset.i4_top    = MUTE_MSG_TOP_INSET;
    t_inset.i4_bottom = MUTE_MSG_BOTTOM_INSET;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text,
                    WGL_CMD_TEXT_SET_CNT_INSET,
                    (VOID*)&t_inset,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set title align */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)MUTE_MSG_ALIGNMENT,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text_mib,
                    WGL_CMD_TEXT_SET_CNT_INSET,
                    (VOID*)&t_inset,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set title align */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text_mib,
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)MUTE_MSG_ALIGNMENT,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_init_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_init_mute(
                    VOL_CTRL_VIEW_T*            pt_view,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset
                    )
{
    GL_RECT_T t_rect;
    INT32     i4_ret;

    i4_ret = vol_ctrl_mute_init_rc(&pt_view->t_rc);
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* create text */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    MUTE_FRAME_LEFT + i4_frame_x_offset,
                    MUTE_FRAME_TOP  + i4_frame_y_offset,
                    MUTE_FRAME_WIDTH,
                    MUTE_FRAME_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32|WGL_STL_TEXT_SMART_CUT),
                    NULL,
                    &pt_view->h_mute_text
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_create_widget(
                    nav_get_context()->t_gui_res.h_cc_plane,
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32|WGL_STL_TEXT_SMART_CUT),
                    NULL,
                    &pt_view->h_mute_text_mib
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
#endif

    /* load mute frame skin */
    i4_ret = _vol_ctrl_view_set_mute_skin(pt_view);
    if(NAVR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    /*
       [CR00014884] We should float text widget instead of frame widget.
       Otherwise, text widget will be covered up.
    */
    i4_ret = c_wgl_float(
                    pt_view->h_mute_text,
                    TRUE,
                    FALSE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_show(pt_view->h_mute_text, WGL_SW_HIDE);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_ignore_visibility_detect(
                    pt_view->h_mute_text,
                    TRUE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_float(
                    pt_view->h_mute_text_mib,
                    TRUE,
                    FALSE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_show(pt_view->h_mute_text_mib, WGL_SW_HIDE);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_deinit_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_deinit_mute(
                    VOL_CTRL_VIEW_T*            pt_view
                    )
{
    INT32 i4_ret;

    vol_ctrl_mute_deinit_rc(&pt_view->t_rc);

    i4_ret = c_wgl_destroy_widget(pt_view->h_mute_text);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_destroy_widget(pt_view->h_mute_text_mib);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_show_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_show_mute(
                    BOOL    b_is_mute
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
    UTF16_T*         pw2s_string;
    INT32            i4_ret;

    pw2s_string = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_VOLUME_MUTING);
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)pw2s_string,
                    (VOID*)(c_uc_w2s_strlen(pw2s_string))
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _vol_ctrl_view_set_visibility_and_repaint(pt_view->h_mute_text, WGL_SW_RECURSIVE);
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_text_mib,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)pw2s_string,
                    (VOID*)(c_uc_w2s_strlen(pw2s_string))
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _vol_ctrl_view_set_visibility_and_repaint(pt_view->h_mute_text_mib, WGL_SW_RECURSIVE);
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_hide_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_hide_mute(
                    VOID
                    )
{
    VOL_CTRL_VIEW_T* pt_view  = &t_g_vol_ctrl_view;
    INT32            i4_ret;

    i4_ret = _vol_ctrl_view_set_visibility_and_repaint(pt_view->h_mute_text, WGL_SW_HIDE);
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = _vol_ctrl_view_set_visibility_and_repaint(pt_view->h_mute_text_mib, WGL_SW_HIDE);
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }
#endif

    return NAVR_OK;
}
#else
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_set_mute_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_set_mute_skin(
                    VOL_CTRL_VIEW_T*            pt_view
                    )
{
    WGL_COLOR_INFO_T t_clr_info;
    WGL_IMG_INFO_T   t_img_info;
    INT32            i4_ret;

    /* set mute icon bgcolor */
    t_clr_info.u_color_data.t_standard.t_disable.a   = 0;
    t_clr_info.u_color_data.t_standard.t_enable.a    = 0;
    t_clr_info.u_color_data.t_standard.t_highlight.a = 0;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_icon,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set mute icon image buffer*/
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_img_mute;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_img_mute;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_img_mute;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_icon,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info)
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set mute icon index alignment */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_icon,
                    WGL_CMD_ICON_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_icon_mib,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_icon_mib,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info)
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_mute_icon_mib,
                    WGL_CMD_ICON_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_init_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_init_mute(
                    VOL_CTRL_VIEW_T*            pt_view,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset
                    )
{
    GL_RECT_T t_rect;
    INT32     i4_ret;

    /* create mute icon */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    MUTE_FRAME_LEFT   + MUTE_ICON_LEFT + i4_frame_x_offset,
                    MUTE_FRAME_TOP    + MUTE_ICON_TOP  + i4_frame_y_offset,
                    MUTE_FRAME_WIDTH  + MUTE_ICON_WIDTH,
                    MUTE_FRAME_HEIGHT + MUTE_ICON_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_mute_icon
                    );
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_float(
                    pt_view->h_mute_icon,
                    TRUE,
                    FALSE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_ignore_visibility_detect(
                    pt_view->h_mute_icon,
                    TRUE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_create_widget(
                    nav_get_context()->t_gui_res.h_cc_plane,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_mute_icon_mib
                    );
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_float(
                    pt_view->h_mute_icon_mib,
                    TRUE,
                    FALSE
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif
#if 0
//APP_LACK_PICTURES
    i4_ret = c_wgl_img_tpl_create(
                    WGL_IMG_ST_NO_SEGMENT,
                    &t_g_app_mute_img,
                    &pt_view->h_img_mute
                    );
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
#endif

    /* load mute frame skin */
    i4_ret = _vol_ctrl_view_set_mute_skin(pt_view);
    if(NAVR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_deinit_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_deinit_mute(
                    VOL_CTRL_VIEW_T*            pt_view
                    )
{
    INT32 i4_ret;

    i4_ret = c_wgl_img_tpl_destroy(pt_view->h_img_mute);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_destroy_widget(pt_view->h_mute_icon);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_destroy_widget(pt_view->h_mute_icon_mib);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_show_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_show_mute(
                    BOOL    b_is_mute
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;

    nav_set_mute (b_is_mute);
    a_ui_show_slider_bar_by_mute(pt_view->h_volume_frame, b_is_mute, pt_view->pt_ctrl->b_is_bt_headphones_active);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_hide_mute
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_hide_mute(
                    VOID
                    )
{
#if 0
    VOL_CTRL_VIEW_T* pt_view  = &t_g_vol_ctrl_view;
    INT32            i4_ret;

    i4_ret = _vol_ctrl_view_set_visibility_and_repaint(
                    pt_view->h_mute_icon,
                    WGL_SW_HIDE
                    );
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = _vol_ctrl_view_set_visibility_and_repaint(
                    pt_view->h_mute_icon_mib,
                    WGL_SW_HIDE
                    );
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }
#endif
#endif

    return NAVR_OK;
}
#endif /* end of APP_MUTE_DISP_AS_TEXT */

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _vol_ctrl_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
    BOOL             b_reset_visible = FALSE;

#ifdef APP_VOLUME_CTRL_WITH_CUSTOMIZED_IS_KEY_HANDLER    /* nav_variant.h */

    BOOL    b_processed  = FALSE;
    BOOL    b_result     = FALSE;

    vol_ctrl_view_custom_is_key_handler(ui4_key_code,
                                        &b_processed,
                                        &b_result);

    if (b_processed)
    {
        DBG_LOG_PRINT(("#### %s b_result=%d \n", __FILE__, b_result));
        return b_result;
    }

#endif /* APP_VOLUME_CTRL_WITH_CUSTOMIZED_IS_KEY_HANDLER */

//#if APP_CEC_SAC_VOL_SUPPORT
    if (vol_ctrl_is_cec_sac_mode())
	{
#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
		pt_view->b_is_need_show_vol_off = TRUE;
#endif
        DBG_LOG_PRINT(("#### %s line %d \n", __FILE__, __LINE__ ));
        return FALSE;
    }
//#endif

    if (ui4_key_code & KEY_SRC_FRONT_PANEL)
    {
        ui4_key_code = ui4_key_code & ~KEY_SRC_FRONT_PANEL;
    }


#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
	if (BTN_VOL_UP == ui4_key_code ||
		BTN_VOL_DOWN == ui4_key_code ||
		BTN_SHOW_VOL_BAR == ui4_key_code ||
		BTN_MUTE == ui4_key_code)
	{
		if (FALSE == _get_aud_speaker_state() && _get_ana_aud_out_fixed())
		{
		    UINT8	ui1_vol_dis_flag = ACFG_CUSTOM_VOL_SLIDER_DIS_OFF;
            DBG_LOG_PRINT(("#### %s line %d \n", __FILE__, __LINE__ ));
		    a_cfg_cust_get_vol_control_dis_flag(&ui1_vol_dis_flag);
		    if(pt_view->pt_ctrl->b_is_need_show_speaker_off)
		    {
		        pt_view->b_is_need_show_vol_off = TRUE;
		    }

			if (pt_view->b_is_need_show_vol_off && (ui1_vol_dis_flag == ACFG_CUSTOM_VOL_SLIDER_DIS_ON))
			{
				pt_view->b_is_need_show_vol_off = FALSE;
				pt_view->pt_ctrl->b_is_need_show_speaker_off = FALSE;
				_vol_ctrl_view_show_vol_off();
			}
			return FALSE;
		}
		else
		{
		    DBG_LOG_PRINT(("#### %s line %d \n", __FILE__, __LINE__ ));
			pt_view->b_is_need_show_vol_off = TRUE;
		}
	}
#endif

    switch(ui4_key_code) {
    case BTN_VOL_UP:
    case BTN_VOL_DOWN:
	case BTN_SHOW_VOL_BAR:
#ifdef LINUX_TURNKEY_SOLUTION
        if (a_tv_net_get_tv_svc_status () == APP_TV_NET_SVC_STATUS_PAUSED)
#endif
        {
            if (nav_is_active() == FALSE && pt_view->pt_ctrl->b_is_volume_visible == TRUE) {
                /* if nav is not active, recevie the Vol+/- key, just handle it in background*/
                b_reset_visible = TRUE;
            }
        }

        if (pt_view->pt_ctrl->b_is_volume_visible == TRUE) {
            /* Check if the volume bar is being displayed */
            if (pt_view->pt_ctrl->b_is_volume_on == TRUE) {
                /* Set focus to volume bar */
                a_ui_slider_bar_set_focus(pt_view->h_volume_frame, FALSE);

                _VOL_CTRL_VIEW_RCU_KEY_HANDLER(pt_view, ui4_key_code);

                /* Restart timer to hide volume component */
                pt_view->pt_ctrl->b_is_volume_visible = TRUE;

                vol_ctrl_reset_timer(pt_view->pt_ctrl);

                return FALSE;
            }
            return TRUE;
        }

        _VOL_CTRL_VIEW_RCU_KEY_HANDLER(pt_view, ui4_key_code);

        if (b_reset_visible == TRUE) {
            pt_view->pt_ctrl->b_is_volume_visible = TRUE;
        }
 
        return FALSE;
    case BTN_MUTE:
        return TRUE;
    default:
        break;
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_activate
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_activate(
                    UINT32                      ui4_key_code
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
    BOOL             b_mute  = FALSE;

    if (ui4_key_code & KEY_SRC_FRONT_PANEL)
    {
        ui4_key_code = ui4_key_code & ~KEY_SRC_FRONT_PANEL;
    }

    switch(ui4_key_code) {
    case BTN_VOL_UP:
		vol_activate_is_on = TRUE;
    	nav_get_mute (&b_mute);
        pt_view->pt_ctrl->t_view_hdlr.pf_show_mute(FALSE);
        if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
        {
        	vol_ctrl_increase_volume(pt_view->pt_ctrl);
        }
        else
        {
        	bt_vol_ctrl_increase_volume(pt_view->pt_ctrl);
        }
        vol_ctrl_show_volume (pt_view->pt_ctrl);
        if (b_mute)
        {
           a_tts_play_vol_value();
        }
        break;
    case BTN_VOL_DOWN:
		vol_activate_is_on = TRUE;
        if (a_tv_get_mute() == FALSE)
        {
            pt_view->pt_ctrl->t_view_hdlr.pf_show_mute(FALSE);
        }
        else
        {
            pt_view->pt_ctrl->t_view_hdlr.pf_show_mute(TRUE);
        }
        if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
        {
        	vol_ctrl_decrease_volume(pt_view->pt_ctrl);
        }
        else
        {
        	bt_vol_ctrl_decrease_volume(pt_view->pt_ctrl);
        }
        vol_ctrl_show_volume (pt_view->pt_ctrl);
        break;
    case BTN_SHOW_VOL_BAR:
        // If volume is configured via speach
        // config is saved and we get BTN_SHOW_VOL_BAR, we will use this to send set volume notif to btdaemon
        if(pt_view->pt_ctrl->b_is_bt_headphones_active == TRUE)
        {
            if( pt_view->pt_ctrl->b_is_volume_event == FALSE )
            {
                UINT16 ui2_vol_ch_id = 0;
                INT32 i4_ret = vol_ctrl_get_vol_cfg_id( pt_view->pt_ctrl->ui1_crnt_au_ch_idx, &ui2_vol_ch_id);
                if (i4_ret != NAVR_OK) 
                {
                    return i4_ret;
                }

                INT16 i2_volume  = 0;
                i4_ret = a_cfg_av_get( ui2_vol_ch_id, &i2_volume);
                if (i4_ret != APP_CFGR_OK) 
                {
                    return NAVR_FAIL;
                }
                DBG_LOG_PRINT(("BT_HEADPHONES_NAV : [%s,%s(),%d] : i2_volume: %d", __FILE__, __FUNCTION__, __LINE__, i2_volume));

                bt_vol_ctrl_set_volume( pt_view->pt_ctrl, i2_volume );
                //bt_vol_ctrl_increase_volume( pt_view->pt_ctrl );
                return NAVR_OK;
            }
        }
        
        vol_ctrl_show_volume (pt_view->pt_ctrl);
        break;
    case BTN_MUTE:
        vol_ctrl_reset_timer(pt_view->pt_ctrl);
        if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
        {
            vol_ctrl_mute(pt_view->pt_ctrl);
        }
        else
        { 
            bt_vol_ctrl_set_mute(pt_view->pt_ctrl);
        }
        vol_ctrl_show_volume(pt_view->pt_ctrl);
        break;
    default:
        break;
    }

	_vol_ctrl_view_reset_fast_mode(pt_view);
	//Add for spec change of semaphore
	rest_event_notify("tv_settings/audio/volume_selector",1 ,"");
    return NAVR_OK;
}

VOID _vol_ctrl_view_context_switch_nfy_fct(
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    vol_ctrl_mute (t_g_vol_ctrl_view.pt_ctrl);
}


static VOID _vol_ctrl_view_iom_nfy_fct (
                          VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data)
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
#if 0
    if (IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_MUTE)
    {
        if (IOM_NFY_COND_BTN_DOWN == e_nfy_cond)
        {
            if (pt_view->b_mute_release)
            {
                nav_request_context_switch(_vol_ctrl_view_context_switch_nfy_fct, NULL, NULL, NULL);
            }
            pt_view->b_mute_release = FALSE;
            pt_view->b_mute_repeat = FALSE;
        }
        else if (IOM_NFY_COND_BTN_REPEAT == e_nfy_cond)
        {
            pt_view->b_mute_repeat = TRUE;
            pt_view->b_mute_release = FALSE;
        }
        else if (IOM_NFY_COND_BTN_UP == e_nfy_cond)
        {
            if (pt_view->b_mute_repeat)
            {
                pt_view->b_mute_repeat = FALSE;
                pt_view->b_mute_release = TRUE;
            }
        }
    }
#endif

    if (IOM_NFY_COND_BTN_DOWN == e_nfy_cond ||
        IOM_NFY_COND_BTN_REPEAT == e_nfy_cond)
    {
        if(pt_view->pt_ctrl->b_is_bt_headphones_active == TRUE)
        {
            if(IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_VOL_UP)
            {
                bt_vol_ctrl_increase_volume(pt_view->pt_ctrl);
            }
            else 
            if(IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_VOL_DOWN)
            {
                bt_vol_ctrl_decrease_volume(pt_view->pt_ctrl);
            }
            else 
            if(IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_MUTE)
            {
                bt_vol_ctrl_set_mute(pt_view->pt_ctrl);
            }
        }
    }

    /* WLG cannot indentify KEY_DOWN msg is BTN_DOWN or BTN_REPEAT, and WGL KEY_DOWN/KEY_REPEAT msg dispatched faster then IOM notify fct,
       but KEY_UP msg is slower then IOM. so set a repeat flay if current is KEY_REPEAT, and if current is repeat, a release flay shoule be set */
    if (IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_MUTE
        || IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_VOL_UP
        || IOM_GET_EVT_GRP_ID (ui4_evt_code) == BTN_VOL_DOWN)
    {
        if (IOM_NFY_COND_BTN_DOWN == e_nfy_cond)
        {
            pt_view->b_mute_release = FALSE;
            pt_view->b_mute_repeat = FALSE;
            DBG_INFO(("[VOLUME IOM]--IOM_NFY_COND_BTN_DOWN--\n"));
        }
        else if (IOM_NFY_COND_BTN_REPEAT == e_nfy_cond)
        {
            pt_view->b_mute_repeat = TRUE;
            pt_view->b_mute_release = FALSE;
            DBG_INFO(("[VOLUME IOM]--IOM_NFY_COND_BTN_REPEAT--\n"));
        }
        else if (IOM_NFY_COND_BTN_UP == e_nfy_cond)
        {
            if (pt_view->b_mute_repeat)
            {
                pt_view->b_mute_repeat = FALSE;
                pt_view->b_mute_release = TRUE;
            }
            DBG_INFO(("[VOLUME IOM]--IOM_NFY_COND_BTN_UP--\n"));
        }
    }

}

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_init(
                    VOL_CTRL_T*                 pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
    INT32 i4_ret;
    IRRC_SETTING_T          t_irrc_setting;
    pt_view->b_mute_release = FALSE;
    pt_view->b_mute_repeat = FALSE;

    /* Register to IOM in order to receive raw data. */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));

    t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_TO_MASK(KEY_GROUP_AUD_CTRL);
    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = 50;
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = 20;

    i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                         IOM_DEV_ID_ANY,
                         NULL,
                         (VOID*) & t_irrc_setting,
                         NULL,
                         _vol_ctrl_view_iom_nfy_fct,
                         &pt_view->h_iom);
    if (i4_ret != IOMR_OK)
    {
        return NAVR_FAIL;
    }

    pt_view->pt_ctrl = pt_ctrl;

    _vol_ctrl_view_reset_fast_mode(pt_view);

    i4_ret = _vol_ctrl_view_init_volume(
                    pt_view,
                    h_canvas
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _vol_ctrl_view_init_mute(
                    pt_view,
                    h_canvas,
                    i4_frame_x_offset,
                    i4_frame_y_offset
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

//#if APP_CEC_SAC_VOL_SUPPORT
    i4_ret = _vol_ctrl_view_init_cec_sac_volume(
                    pt_view,
                    h_canvas
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
//#endif

#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
	i4_ret = _vol_ctrl_view_init_vol_off(
                    pt_view,
                    h_canvas
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

	/* Register to ACFG to listen Audio change notify */
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_AUDIO,
                              NULL,
                              _vol_ctrl_view_vol_off_cfg_chg_cb,
                              &pt_view->ui2_cfg_nfy_id_audio);
	if(APP_CFGR_OK != i4_ret)
	{
		pt_view->ui2_cfg_nfy_id_audio = APP_CFG_NOTIFY_NULL_ID;
		return NAVR_FAIL;
	}

	i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_CUSTOM_BASE,
                              NULL,
                              _vol_ctrl_view_vol_off_cfg_chg_cb,
                              &pt_view->ui2_cfg_nfy_id_ana_aud_out);
	if(APP_CFGR_OK != i4_ret)
	{
		pt_view->ui2_cfg_nfy_id_ana_aud_out = APP_CFG_NOTIFY_NULL_ID;
		return NAVR_FAIL;
	}

	/* Register to ACFG to listen tv speaker notify */
    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_AUDIO,
                              NULL,
                              _vol_ctrl_view_tv_speaker_cfg_chg_cb,
                              &pt_view->ui2_cfg_nfy_id_tv_speaker);
	if(APP_CFGR_OK != i4_ret)
	{
		pt_view->ui2_cfg_nfy_id_tv_speaker = APP_CFG_NOTIFY_NULL_ID;
		return NAVR_FAIL;
	}

#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_deinit(
                    VOID
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
    INT32 i4_ret;

    i4_ret = a_ui_vol_ctrl_view_destroy (pt_view->h_volume_frame);
    if(i4_ret != APP_UIR_OK){
        return NAVR_FAIL;
    }

    i4_ret = _vol_ctrl_view_deinit_mute(pt_view);
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }

//#if APP_CEC_SAC_VOL_SUPPORT
    i4_ret = _vol_ctrl_view_deinit_cec_sac_volume(pt_view);
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }
//#endif

#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
	if(APP_CFG_NOTIFY_NULL_ID != pt_view->ui2_cfg_nfy_id_audio)
    {
        a_cfg_notify_unreg(pt_view->ui2_cfg_nfy_id_audio);
        pt_view->ui2_cfg_nfy_id_audio = APP_CFG_NOTIFY_NULL_ID;
    }
	if(APP_CFG_NOTIFY_NULL_ID != pt_view->ui2_cfg_nfy_id_ana_aud_out)
    {
        a_cfg_notify_unreg(pt_view->ui2_cfg_nfy_id_ana_aud_out);
        pt_view->ui2_cfg_nfy_id_ana_aud_out = APP_CFG_NOTIFY_NULL_ID;
    }

	i4_ret = _vol_ctrl_view_deinit_vol_off(pt_view);
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }
#endif
	if(APP_CFG_NOTIFY_NULL_ID != pt_view->ui2_cfg_nfy_id_tv_speaker)
    {
        a_cfg_notify_unreg(pt_view->ui2_cfg_nfy_id_tv_speaker);
        pt_view->ui2_cfg_nfy_id_tv_speaker = APP_CFG_NOTIFY_NULL_ID;
    }

    if (pt_view->h_iom != NULL_HANDLE)
    {
        c_iom_close(pt_view->h_iom);
        pt_view->h_iom = NULL_HANDLE;
    }

    pt_view->pt_ctrl = NULL;

    return NAVR_OK;
}
static INT32 _vol_ctrl_view_zoom_mode_enable(VOID)
{
    UINT8           ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;
    WGL_FONT_INFO_T t_fnt_info;
    GL_RECT_T       t_rect;
    INT32           i4_ret;

    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;

    /*set the font and pos of "Audio System" when zoom on/off.*/
    i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
    NAV_CHK_FAIL(i4_ret);

    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;

    if(ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        /* Set Font */
        t_fnt_info.ui1_custom_size = 27*2;

        i4_ret = c_wgl_do_cmd(pt_view->h_volume_txt_title,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK(&t_fnt_info),
                              NULL);
        if(i4_ret != WGLR_OK)
        {
            return NAVR_FAIL;
        }

        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_X,
                         UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_Y - UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_H/2,
                         UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_W,
                         UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_H + 30);
    }
    else
    {
        t_fnt_info.ui1_custom_size = 27;

        i4_ret = c_wgl_do_cmd(pt_view->h_volume_txt_title,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK(&t_fnt_info),
                              NULL);
        if(i4_ret != WGLR_OK)
        {
            return NAVR_FAIL;
        }
        /*set pos*/
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_X,
                         UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_W,
                         UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_H);
    }

    i4_ret = c_wgl_move(pt_view->h_volume_txt_title,
                         &t_rect,
                         WGL_NO_AUTO_REPAINT);
    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_update_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_update_volume(
                    INT16                       i2_volume
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
    GL_RECT_T        t_rect;
    GL_RECT_T        t_rect_vol_frm;
    GL_RECT_T        t_rect_aud_title_frm;
    HANDLE_T         h_canvas = NULL_HANDLE;
    INT32            i4_ret;
    UINT8	         ui1_vol_dis_flag = ACFG_CUSTOM_VOL_SLIDER_DIS_OFF;
    UTF16_T*         w2s_title;

    i4_ret = a_ui_slider_bar_set_pos(
                    pt_view->h_volume_frame,
                    (INT32)i2_volume,
                    pt_view->pt_ctrl->b_is_bt_headphones_active);
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = a_cfg_cust_get_vol_control_dis_flag(&ui1_vol_dis_flag);
    if (i4_ret != APP_UIR_OK) {
        DBG_ERROR(("%s,%d vol get dis flag fail  \r\n",__FUNCTION__,__LINE__));
        return NAVR_FAIL;
    }
#ifdef APP_TTS_SUPPORT
    if(TTS_STR_ST_PLAYING == a_app_tts_get_string_state())
    {
        a_app_tts_stop(APP_TTS_STOP_FORCE);
    }
#endif
//#if APP_CEC_SAC_VOL_SUPPORT
    if (vol_ctrl_is_cec_sac_mode() || (pt_view->pt_ctrl->b_is_bt_headphones_active == TRUE))
    {
		CHAR s_app_name[APP_NAME_MAX_LEN + 1];

        /*Move the volume bar top, to show the 'Audio System' title*/

        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);
        c_wgl_move(pt_view->h_volume_frame, &t_rect, FALSE);

        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);

        c_wgl_move(pt_view->h_volume_frame_ex, &t_rect, FALSE);
        c_wgl_float(pt_view->h_volume_frame_ex, TRUE, FALSE);

		a_am_get_active_app(s_app_name);

	    if (c_strcmp (s_app_name, "wizard") == 0)
	    {
			if(t_g_wzd.b_g_is_vol_key_enable)
			{
				if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
				{
					i4_ret = a_ui_slider_bar_show(pt_view->h_volume_frame, FALSE);
				}
				else
				{
					i4_ret = a_ui_slider_bar_show(pt_view->h_volume_frame, TRUE);
				}

				DBG_WARN(("\n%s(%d)after a_ui_slider_bar_show,return[%d]\n",__FUNCTION__,__LINE__,i4_ret));
			    if (i4_ret != APP_UIR_OK) {
			        return NAVR_FAIL;
			    }

		    }
	    }
	    else
	    {
    		if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
			{
				i4_ret = a_ui_slider_bar_show(pt_view->h_volume_frame, FALSE);
			}
			else
			{
				i4_ret = a_ui_slider_bar_show(pt_view->h_volume_frame, TRUE);
			}

		    if (i4_ret != APP_UIR_OK) {
		        return NAVR_FAIL;
		    }

	    }
    }
    else if(ui1_vol_dis_flag != ACFG_CUSTOM_VOL_SLIDER_DIS_OFF)
    {
        SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);
        /*Move the volume bar back to center*/
        c_wgl_move(pt_view->h_volume_frame, &t_rect, TRUE);

        if(pt_view->pt_ctrl->b_is_aud_sys_visible == TRUE)
        {
            SET_RECT_BY_SIZE(&t_rect,
                             UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                             UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                             UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                             UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);

            c_wgl_move(pt_view->h_volume_frame_ex, &t_rect, FALSE);
            c_wgl_float(pt_view->h_volume_frame_ex, TRUE, FALSE);

            c_wgl_insert (pt_view->h_volume_frame_ex,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);

            c_wgl_set_visibility(pt_view->h_volume_frame_ex, WGL_SW_RECURSIVE);
	    }
        if(pt_view->pt_ctrl->b_is_bt_headphones_active == FALSE)
        {
            i4_ret = a_ui_slider_bar_show(pt_view->h_volume_frame, FALSE);
        }
        else
        {
            i4_ret = a_ui_slider_bar_show(pt_view->h_volume_frame, TRUE);
        }
	    if (i4_ret != APP_UIR_OK) {
	        return NAVR_FAIL;
	    }
    }
    else
    {
        DBG_INFO(("%s,%d VOL control dis off do not show vol ui \r\n",__FUNCTION__,__LINE__));
    }
//#endif

	if((FALSE == _get_aud_speaker_state()) && (_get_ana_aud_out_fixed() == FALSE))
    {
        pt_view->pt_ctrl->b_is_aud_sys_visible = TRUE;
    }
    else
    {
        pt_view->pt_ctrl->b_is_aud_sys_visible = FALSE;
    }

    if ((vol_ctrl_is_cec_sac_mode()) || (pt_view->pt_ctrl->b_is_aud_sys_visible == TRUE))
    {
        _vol_ctrl_view_zoom_mode_enable();

        /* Set Title Text */
        w2s_title = MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                 MLM_NAV_KEY_CEC_DEV_AUDIO);

        c_wgl_do_cmd(pt_view->h_volume_txt_title,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK(w2s_title),
                      WGL_PACK(c_uc_w2s_strlen(w2s_title)));
    }
    else
    {
        _vol_ctrl_view_zoom_mode_enable();

        /* Set Title Text */
        w2s_title = MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                                 MLM_NAV_KEY_EMPTY);

        c_wgl_do_cmd(pt_view->h_volume_txt_title,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK(w2s_title),
                      WGL_PACK(c_uc_w2s_strlen(w2s_title)));
    }

    if (pt_view->pt_ctrl->b_is_bt_headphones_active == TRUE)
    {
        _vol_ctrl_view_zoom_mode_enable();

        /* Set bluetooth headphones Text */
        UTF16_T w2s_data[256] = {0};
        get_connected_audio_device_from_jsondb(w2s_data);

        INT32 i4_ret = c_wgl_do_cmd(pt_view->h_volume_txt_title,
                                WGL_CMD_TEXT_SET_TEXT,
                                WGL_PACK(w2s_data),
                                WGL_PACK(c_uc_w2s_strlen(w2s_data)));
        MENU_CHK_FAIL(i4_ret);
    }

#ifndef APP_PROGRESSBAR_FAST_MODE_DISABLE
    if (pt_view->b_repaint_vol_ctrl == TRUE)
    {
        i4_ret = c_wgl_get_coords(pt_view->h_volume_frame,
                         WGL_COORDS_SCREEN,
                         &t_rect_vol_frm);
        if (i4_ret != APP_UIR_OK)
        {
            return NAVR_FAIL;
        }
        i4_ret = c_wgl_get_coords(pt_view->h_volume_frame_ex,
                         WGL_COORDS_SCREEN,
                         &t_rect_aud_title_frm);
        if (i4_ret != APP_UIR_OK)
        {
            return NAVR_FAIL;
        }
        i4_ret = c_wgl_rect_union(&t_rect, &t_rect_vol_frm, &t_rect_aud_title_frm);
        if (i4_ret != APP_UIR_OK)
        {
            return NAVR_FAIL;
        }
        /*
        SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_FRAME_X - VOL_CTRL_VIEW_AUD_SYS_TITLE_W,
                     UI_SLIDER_BAR_DEF_CONTENT_FRAME_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_FRAME_W + 300,
                     UI_SLIDER_BAR_DEF_CONTENT_FRAME_H); */
        h_canvas= nav_get_ui_canvas();
        i4_ret = c_wgl_repaint(h_canvas, &t_rect, TRUE);
        if (i4_ret != APP_UIR_OK) {
            return NAVR_FAIL;
        }
    }
#else
    i4_ret = c_wgl_get_coords(pt_view->h_volume_frame,
                     WGL_COORDS_SCREEN,
                     &t_rect_vol_frm);
    if (i4_ret != APP_UIR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_get_coords(pt_view->h_volume_frame_ex,
                     WGL_COORDS_SCREEN,
                     &t_rect_aud_title_frm);
    if (i4_ret != APP_UIR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_rect_union(&t_rect, &t_rect_vol_frm, &t_rect_aud_title_frm);
    if (i4_ret != APP_UIR_OK)
    {
        return NAVR_FAIL;
    }

    h_canvas= nav_get_ui_canvas();
    i4_ret = c_wgl_repaint(h_canvas, &t_rect, TRUE);
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }
#endif
  
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_show_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_show_volume(
                    UINT8                       ui1_ch_idx,
                    INT16                       i2_min_val,
                    INT16                       i2_max_val,
                    INT16                       i2_volume
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
    INT32            i4_ret;

    /* Set Range */
    i4_ret = a_ui_slider_bar_set_range(
                    pt_view->h_volume_frame,
                    (INT32)i2_min_val,
                    (INT32)i2_max_val
                    );
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

//#if APP_CEC_SAC_VOL_SUPPORT
    if (vol_ctrl_is_cec_sac_mode() || (pt_view->pt_ctrl->b_is_bt_headphones_active == TRUE))
    {
		CHAR s_app_name[APP_NAME_MAX_LEN + 1];

		a_am_get_active_app(s_app_name);

	    if (c_strcmp (s_app_name, "wizard") == 0)
	    {
			if(t_g_wzd.b_g_is_vol_key_enable)
			{
			    c_wgl_insert (pt_view->h_volume_frame_ex,
                               NULL_HANDLE,
                               WGL_INSERT_TOPMOST,
                               WGL_NO_AUTO_REPAINT);
				c_wgl_set_visibility(pt_view->h_volume_frame_ex, WGL_SW_RECURSIVE);
		        }
	    }
	    else
	    {
	        c_wgl_insert (pt_view->h_volume_frame_ex,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
	        c_wgl_set_visibility(pt_view->h_volume_frame_ex, WGL_SW_RECURSIVE);
                i4_ret = a_ui_slider_bar_set_focus(pt_view->h_volume_frame, FALSE);
                if (i4_ret != APP_UIR_OK)
		{
                    return NAVR_FAIL;
		}
	    }
    }
    else
//#endif
    {
        i4_ret = a_ui_slider_bar_set_focus(pt_view->h_volume_frame, FALSE);
        if (i4_ret != APP_UIR_OK) {
            return NAVR_FAIL;
        }
    }
    i4_ret = _vol_ctrl_view_update_volume(
                    i2_volume
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    a_msg_convert_show_dtv_osd();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_hide_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_hide_volume(
                    VOID
                    )
{
    VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;
	GL_RECT_T        t_rect;
    GL_RECT_T        t_rect_vol_frm;
    GL_RECT_T        t_rect_aud_title_frm;
    HANDLE_T         h_canvas = NULL_HANDLE;
	INT32            i4_ret;

	/* Hide */
    i4_ret = a_ui_slider_bar_hide(pt_view->h_volume_frame);
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

//#if APP_CEC_SAC_VOL_SUPPORT
    c_wgl_float(pt_view->h_volume_frame_ex, FALSE, FALSE);
    i4_ret = c_wgl_set_visibility(pt_view->h_volume_frame_ex, WGL_SW_HIDE_RECURSIVE);
    if (i4_ret != APP_UIR_OK)
    {
        DBG_ERROR(("%s,%d c_wgl_set_visibility fail= %d \r\n",__FUNCTION__,__LINE__,i4_ret));
        return NAVR_FAIL;
    }

    c_wgl_repaint(pt_view->h_volume_frame_ex,NULL,TRUE);
    if (i4_ret != APP_UIR_OK)
    {
        DBG_ERROR(("%s,%d c_wgl_repaint fail= %d \r\n",__FUNCTION__,__LINE__,i4_ret));
        return NAVR_FAIL;
    }
//#endif

	/* Repain canvas */
//#if APP_CEC_SAC_VOL_SUPPORT
    if (vol_ctrl_is_cec_sac_mode() || (pt_view->pt_ctrl->b_is_aud_sys_visible == TRUE) || (pt_view->pt_ctrl->b_is_bt_headphones_active == TRUE))
    {
        i4_ret = c_wgl_get_coords(pt_view->h_volume_frame,
                        WGL_COORDS_SCREEN,
                        &t_rect_vol_frm);
        if (i4_ret != APP_UIR_OK)
        {
            return NAVR_FAIL;
        }
        i4_ret = c_wgl_get_coords(pt_view->h_volume_frame_ex,
                        WGL_COORDS_SCREEN,
                        &t_rect_aud_title_frm);
        if (i4_ret != APP_UIR_OK)
        {
            return NAVR_FAIL;
        }
        i4_ret = c_wgl_rect_union(&t_rect, &t_rect_vol_frm, &t_rect_aud_title_frm);
        if (i4_ret != APP_UIR_OK)
        {
            return NAVR_FAIL;
        }

        h_canvas= nav_get_ui_canvas();
        i4_ret = c_wgl_repaint(h_canvas, &t_rect, TRUE);
        if (i4_ret != APP_UIR_OK) {
            return NAVR_FAIL;
        }
    }
//#else
    else
    {
        i4_ret = a_ui_slider_bar_repaint(
                        pt_view->h_volume_frame
                        );
        if (i4_ret != APP_UIR_OK) {
            return NAVR_FAIL;
        }
    }
//#endif

    a_msg_convert_hide_dtv_osd();

    nav_update_pwd_digit_ui();

    vol_activate_is_on = FALSE;

    return NAVR_OK;
}

//#if APP_CEC_SAC_VOL_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_init_cec_sac_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_init_cec_sac_volume(
                    VOL_CTRL_VIEW_T*            pt_view,
                    HANDLE_T                    h_canvas
                    )
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    UINT32            ui4_style = 0;
    WGL_COLOR_INFO_T  t_clr_info;
    WGL_IMG_INFO_T    t_img_info;
    WGL_FONT_INFO_T   t_fnt_info;
    UTF16_T*          w2s_title;
    HANDLE_T          h_parent;
    BOOL              b_image_ui;

#ifdef APP_IMG_UI
    b_image_ui = TRUE;
#else
    b_image_ui = FALSE;
#endif

    /* create cec sac volume frame */

    h_parent = h_canvas;

    if(b_image_ui) {
        ui4_style = 0;
    }
    else {
        ui4_style |= WGL_STL_GL_NO_IMG_UI;
    }

	/* PLUS TODO: system audio bk image */

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);


    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 0,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &(pt_view->h_volume_frame_ex));

    if (i4_ret < 0)
    {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }
    nav_img_create_vol_gradient_btm(&(pt_view->h_volume_frame_ex_img_bk));

    if (b_image_ui) {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_volume_frame_ex_img_bk;
        t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_volume_frame_ex_img_bk;
        t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_volume_frame_ex_img_bk;
        i4_ret = c_wgl_do_cmd(pt_view->h_volume_frame_ex,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
    else {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_bk0;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_ui_color_bk0;
        t_clr_info.u_color_data.t_standard.t_disable   = t_g_ui_color_bk0;
        i4_ret = c_wgl_do_cmd(pt_view->h_volume_frame_ex,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info));
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }

    /* create text for show title - "Amplifier Volume" */

    ui4_style =  WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MAX_128;

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_X,
                     UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_W,
                     UI_SLIDER_BAR_DEF_CONTENT_CEC_TEXT_H);

    i4_ret = c_wgl_create_widget(pt_view->h_volume_frame_ex,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &(pt_view->h_volume_txt_title));
    if (i4_ret < 0) {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 27;

    i4_ret = c_wgl_do_cmd(pt_view->h_volume_txt_title,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = TXT_HL_CLR_TXTT;
    t_clr_info.u_color_data.t_standard.t_highlight = TXT_HL_CLR_TXTT;
    t_clr_info.u_color_data.t_standard.t_disable   = TXT_HL_CLR_TXTT;
    i4_ret = c_wgl_do_cmd(pt_view->h_volume_txt_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = TXT_HL_CLR_TXT_bann;
    t_clr_info.u_color_data.t_standard.t_highlight = TXT_HL_CLR_TXT_bann;
    t_clr_info.u_color_data.t_standard.t_disable   = TXT_HL_CLR_TXT_bann;
    i4_ret = c_wgl_do_cmd(pt_view->h_volume_txt_title,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }


    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_view->h_volume_txt_title,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_TOP),
                          NULL);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set Title Text */
    w2s_title = MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                             MLM_NAV_KEY_CEC_DEV_AUDIO);

    i4_ret = c_wgl_do_cmd(pt_view->h_volume_txt_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_title),
                          WGL_PACK(c_uc_w2s_strlen(w2s_title)));

    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    return (NAVR_OK);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_deinit_cec_sac_volume
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_deinit_cec_sac_volume(
                    VOL_CTRL_VIEW_T*            pt_view
                    )
{
    if (pt_view == NULL) {
        return (NAVR_OK);
    }

    /* Release childs*/
    if (pt_view->h_volume_txt_title != NULL_HANDLE) {
        c_wgl_destroy_widget(pt_view->h_volume_txt_title);
        pt_view->h_volume_txt_title = NULL_HANDLE;
    }

    /* Release parent*/
    if (pt_view->h_volume_frame_ex != NULL_HANDLE) {
        c_wgl_destroy_widget(pt_view->h_volume_frame_ex);
        pt_view->h_volume_frame_ex = NULL_HANDLE;
    }

    /* Release template image */
    if (pt_view->h_volume_frame_ex_img_bk != NULL_HANDLE) {
        c_wgl_img_tpl_destroy (pt_view->h_volume_frame_ex_img_bk);
        pt_view->h_volume_frame_ex_img_bk = NULL_HANDLE;
    }

    return (NAVR_OK);
}

//#endif /* APP_CEC_SAC_VOL_SUPPORT */

#ifdef APP_VOLUME_CTRL_TV_SPEAKER_OFF
/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_init_vol_off
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_init_vol_off(
                    VOL_CTRL_VIEW_T*            pt_view,
                    HANDLE_T                    h_canvas
                    )
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    UINT32            ui4_style = 0;
    WGL_COLOR_INFO_T  t_clr_info;
    WGL_IMG_INFO_T    t_img_info;
	WGL_FONT_INFO_T   t_fnt_info;
    HANDLE_T          h_parent;
    BOOL              b_image_ui;
	UTF16_T*          w2s_title;

#ifdef APP_IMG_UI
    b_image_ui = TRUE;
#else
    b_image_ui = FALSE;
#endif

    /* create volume off frame */
    h_parent = h_canvas;

    if(b_image_ui) {
        ui4_style = 0;
    }
    else {
        ui4_style |= WGL_STL_GL_NO_IMG_UI;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &(pt_view->h_volume_ctrl_off_frm));

    if (i4_ret < 0)
    {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }
    nav_img_create_vol_gradient_btm(&(pt_view->h_volume_ctrl_off_frm_bk));

    if (b_image_ui) {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_volume_ctrl_off_frm_bk;
        t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_volume_ctrl_off_frm_bk;
        t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_volume_ctrl_off_frm_bk;
        i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }
    else {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_bk0;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_ui_color_bk0;
        t_clr_info.u_color_data.t_standard.t_disable   = t_g_ui_color_bk0;
        i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info));
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }

    i4_ret = nav_img_create_vol_toast_box(
                    &pt_view->h_volume_ctrl_off_icon_bk);

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_TOAST_X,
                     UI_SLIDER_BAR_DEF_CONTENT_TOAST_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_TOAST_W,
                     UI_SLIDER_BAR_DEF_CONTENT_TOAST_H);

    i4_ret = c_wgl_create_widget(pt_view->h_volume_ctrl_off_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &(pt_view->h_volume_ctrl_off_icon));

    if (i4_ret < 0)
    {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_icon,
                                  WGL_SW_NORMAL);

    /* set icon image buffer */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_volume_ctrl_off_icon_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_volume_ctrl_off_icon_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_volume_ctrl_off_icon_bk;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_volume_ctrl_off_icon,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_FG),
                    WGL_PACK(&t_img_info));

    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_volume_ctrl_off_icon,
                    WGL_CMD_ICON_SET_ALIGN,
                    (VOID*)WGL_AS_CENTER_CENTER,
                    NULL);

    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_vol_inactive(
                &pt_view->h_volume_ctrl_off_icon_inactive_bk);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_OFF_AUDIO_X,
                     UI_SLIDER_BAR_DEF_CONTENT_OFF_AUDIO_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_OFF_AUDIO_W,
                     UI_SLIDER_BAR_DEF_CONTENT_OFF_AUDIO_H);

    i4_ret = c_wgl_create_widget(pt_view->h_volume_ctrl_off_frm,
                             HT_WGL_WIDGET_ICON,
                             WGL_CONTENT_ICON_DEF,
                             WGL_BORDER_NULL,
                             &t_rect,
                             NULL,
                             255,
                             (VOID*)ui4_style,
                             NULL,
                             &(pt_view->h_volume_ctrl_off_icon_inactive));

    if (i4_ret < 0){
        return APP_UIR_WIDGET_CREATE_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_icon_inactive,
                                  WGL_SW_NORMAL);

    /* set icon image buffer */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_volume_ctrl_off_icon_inactive_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_volume_ctrl_off_icon_inactive_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_volume_ctrl_off_icon_inactive_bk;

    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_icon_inactive,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_icon_inactive,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);

    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = nav_img_create_vol_zoom_inactive(
                &pt_view->h_volume_ctrl_off_zoom_icon_inactive_bk);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_ZOOM_OFF_AUDIO_X,
                     UI_SLIDER_BAR_DEF_CONTENT_ZOOM_OFF_AUDIO_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_ZOOM_OFF_AUDIO_W,
                     UI_SLIDER_BAR_DEF_CONTENT_ZOOM_OFF_AUDIO_H);

    i4_ret = c_wgl_create_widget(pt_view->h_volume_ctrl_off_frm,
                             HT_WGL_WIDGET_ICON,
                             WGL_CONTENT_ICON_DEF,
                             WGL_BORDER_NULL,
                             &t_rect,
                             NULL,
                             255,
                             (VOID*)ui4_style,
                             NULL,
                             &(pt_view->h_volume_ctrl_off_zoom_icon_inactive));

    if (i4_ret < 0){
        return APP_UIR_WIDGET_CREATE_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_zoom_icon_inactive,
                                  WGL_SW_NORMAL);

    /* set icon image buffer */
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->h_volume_ctrl_off_zoom_icon_inactive_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->h_volume_ctrl_off_zoom_icon_inactive_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->h_volume_ctrl_off_zoom_icon_inactive_bk;

    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_zoom_icon_inactive,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_zoom_icon_inactive,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);

    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

	/* create text widget - "Speakers are off" */
    ui4_style =  WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MAX_128;

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_OFF_TEXT_X,
                     UI_SLIDER_BAR_DEF_CONTENT_OFF_TEXT_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_OFF_TEXT_W,
                     UI_SLIDER_BAR_DEF_CONTENT_OFF_TEXT_H);

    i4_ret = c_wgl_create_widget(pt_view->h_volume_ctrl_off_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &(pt_view->h_volume_ctrl_off_txt));
    if (i4_ret < 0) {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.ui1_custom_size = 27;

    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_txt,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = TXT_HL_CLR_TXTT;
    t_clr_info.u_color_data.t_standard.t_highlight = TXT_HL_CLR_TXTT;
    t_clr_info.u_color_data.t_standard.t_disable   = TXT_HL_CLR_TXTT;
    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = TXT_HL_CLR_TXT_bann;
    t_clr_info.u_color_data.t_standard.t_highlight = TXT_HL_CLR_TXT_bann;
    t_clr_info.u_color_data.t_standard.t_disable   = TXT_HL_CLR_TXT_bann;
    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_txt,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set Title Text */
    w2s_title = MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                             MLM_NAV_KEY_TV_SPEAKERS_OFF);

    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_title),
                          WGL_PACK(c_uc_w2s_strlen(w2s_title)));

    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

	c_wgl_set_visibility(pt_view->h_volume_ctrl_off_frm, WGL_SW_HIDE);

	/* init vol off timer */
	if (c_handle_valid(pt_view->h_volume_ctrl_off_timer) == TRUE) {
        c_timer_delete(pt_view->h_volume_ctrl_off_timer);
    }
    pt_view->h_volume_ctrl_off_timer = NULL_HANDLE;

	i4_ret = c_timer_create(&(pt_view->h_volume_ctrl_off_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

	pt_view->b_is_need_show_vol_off = TRUE;

    return (NAVR_OK);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_deinit_vol_off
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_deinit_vol_off(
                    VOL_CTRL_VIEW_T*            pt_view
                    )
{
    if (pt_view == NULL) {
        return (NAVR_OK);
    }

	/* Release childs*/
    if (pt_view->h_volume_ctrl_off_txt != NULL_HANDLE) {
        c_wgl_destroy_widget(pt_view->h_volume_ctrl_off_txt);
        pt_view->h_volume_ctrl_off_txt = NULL_HANDLE;
    }

    if (pt_view->h_volume_ctrl_off_icon != NULL_HANDLE) {
        c_wgl_destroy_widget(pt_view->h_volume_ctrl_off_icon);
        pt_view->h_volume_ctrl_off_icon = NULL_HANDLE;
    }

    if (pt_view->h_volume_ctrl_off_icon_inactive!= NULL_HANDLE) {
    c_wgl_destroy_widget(pt_view->h_volume_ctrl_off_icon_inactive);
    pt_view->h_volume_ctrl_off_icon_inactive = NULL_HANDLE;
    }

    if (pt_view->h_volume_ctrl_off_zoom_icon_inactive!= NULL_HANDLE) {
    c_wgl_destroy_widget(pt_view->h_volume_ctrl_off_zoom_icon_inactive);
    pt_view->h_volume_ctrl_off_zoom_icon_inactive = NULL_HANDLE;
    }

    /* Release parent*/
    if (pt_view->h_volume_ctrl_off_frm != NULL_HANDLE) {
        c_wgl_destroy_widget(pt_view->h_volume_ctrl_off_frm);
        pt_view->h_volume_ctrl_off_frm = NULL_HANDLE;
    }

    /* Release template image */
    if (pt_view->h_volume_ctrl_off_frm_bk != NULL_HANDLE) {
        c_wgl_img_tpl_destroy (pt_view->h_volume_ctrl_off_frm_bk);
        pt_view->h_volume_ctrl_off_frm_bk = NULL_HANDLE;
    }

	/* deinit vol off timer */
	if (c_handle_valid(pt_view->h_volume_ctrl_off_timer) == TRUE) {
        c_timer_delete(pt_view->h_volume_ctrl_off_timer);
    }
    pt_view->h_volume_ctrl_off_timer = NULL_HANDLE;

    return (NAVR_OK);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_show_vol_off_timer_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_view_show_vol_off_timer_hdlr(
					VOID* 						pv_tag1,
					VOID* 						pv_tag2,
					VOID* 						pv_tag3)
{
	VOL_CTRL_VIEW_T* pt_view = &t_g_vol_ctrl_view;

	/* hide vol off image */
	c_wgl_set_visibility(pt_view->h_volume_ctrl_off_frm, WGL_SW_HIDE);
	c_wgl_repaint(pt_view->h_volume_ctrl_off_frm,NULL,TRUE);

	return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_show_vol_off_timer_cb
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _vol_ctrl_view_show_vol_off_timer_cb(
					HANDLE_T 					h_timer,
					VOID* 						pv_tag)
{
    nav_request_context_switch(_vol_ctrl_view_show_vol_off_timer_hdlr, NULL, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _vol_ctrl_view_show_vol_off
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _vol_ctrl_view_show_vol_off(VOID)
{
	VOL_CTRL_VIEW_T* 	pt_view = &t_g_vol_ctrl_view;
	UTF16_T*          	w2s_title;
	INT32 				i4_ret = NAVR_OK;
	GL_RECT_T         	t_rect;
	UINT8               ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;
	WGL_FONT_INFO_T     t_fnt_info;

	DBG_INFO(("[VOLUME] FUNC: %s AT LINE: %d\n",__FUNCTION__,__LINE__));

    i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
    if(i4_ret != WGLR_OK){
        DBG_ERROR(("%s,%d vol_ctrl get zoom mode fail= %d \r\n",__FUNCTION__,__LINE__,i4_ret));
    }
	/* update title text */
    w2s_title = MLM_NAV_TEXT(nav_get_mlm_lang_id(),
                             MLM_NAV_KEY_TV_SPEAKERS_OFF);

    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_title),
                          WGL_PACK(c_uc_w2s_strlen(w2s_title)));
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    if(ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_OFF)
    {
        t_fnt_info.ui1_custom_size = 27;
    }
    else {
        t_fnt_info.ui1_custom_size = 27*2;
    }

    i4_ret = c_wgl_do_cmd(pt_view->h_volume_ctrl_off_txt,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

	SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                     UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);
	i4_ret = c_wgl_move(pt_view->h_volume_ctrl_off_frm, &t_rect, FALSE);;
	if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

    /* show vol off image */
	i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_frm, WGL_SW_NORMAL);
	if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

	i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_txt, WGL_SW_NORMAL);
	if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_icon, WGL_SW_NORMAL);
	if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

    if(ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_OFF)
    {
        i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_zoom_icon_inactive, WGL_SW_HIDE);
        i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_icon_inactive, WGL_SW_NORMAL);
    }
    else {
        i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_icon_inactive, WGL_SW_HIDE);
        i4_ret = c_wgl_set_visibility(pt_view->h_volume_ctrl_off_zoom_icon_inactive, WGL_SW_NORMAL);
    }
    if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

	i4_ret = c_wgl_float(pt_view->h_volume_ctrl_off_frm, TRUE, FALSE);
	if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

	i4_ret = c_wgl_repaint(pt_view->h_volume_ctrl_off_frm,NULL,TRUE);
	if (i4_ret != APP_UIR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_start(
                    pt_view->h_volume_ctrl_off_timer,
                    VOLUME_TIMER_DELAY,
                    X_TIMER_FLAG_ONCE,
                    _vol_ctrl_view_show_vol_off_timer_cb,
                    NULL
                    );
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    return (NAVR_OK);
}
#endif

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_view_register_default_hdlr
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_view_register_default_hdlr(
                    VOL_CTRL_VIEW_HDLR_T*       pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init           = _vol_ctrl_view_init;
    pt_view_hdlr->pf_deinit         = _vol_ctrl_view_deinit;
    pt_view_hdlr->pf_show_volume    = _vol_ctrl_view_show_volume;
    pt_view_hdlr->pf_update_volume  = _vol_ctrl_view_update_volume;
    pt_view_hdlr->pf_hide_volume    = _vol_ctrl_view_hide_volume;
    pt_view_hdlr->pf_show_mute      = _vol_ctrl_view_show_mute;
    pt_view_hdlr->pf_hide_mute      = _vol_ctrl_view_hide_mute;
    pt_view_hdlr->pf_is_key_handler = _vol_ctrl_view_is_key_handler;
    pt_view_hdlr->pf_activate       = _vol_ctrl_view_activate;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
#endif /* APP_VOLUME_CTRL */
