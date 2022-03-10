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
 * $RCSfile: pop.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT

#ifdef LINUX_SOLUTION
#define APP_NAV_POP_MOVE_OSD_FIRST
#endif

#include "u_common.h"
#include "c_cfg.h"
#include "u_irrc_btn_def.h"

#include "c_handle.h"
#include "c_wgl.h"

#include "app_util/a_common.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/a_cfg.h"
#include "am/a_am.h"
#include "menu2/a_menu.h"
#include "mmp/a_mmp.h"
#include "nav/nav_common.h"
#include "nav/pop/pop.h"
#include "res/nav/nav_variant.h"
#include "res/nav/pop/pop_custom.h"

#ifdef APP_NAV_FRZ_SUPPORT
#include "nav/freeze/nav_frz.h"
#endif
#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#if (defined(MW_PIP_POP_SUPPORT) && defined (MW_TV_AV_BYPASS_SUPPORT))
    #define _APP_NAV_POP_SCARTOUT_COEXIST_SUPPORT 
#endif
#if 0
#undef  DBG_ERROR
#define DBG_ERROR(_stmt)    DBG_LOG_PRINT (_stm)t
#endif
#if 0
#undef  DBG_API
#define DBG_API(_stmt)      DBG_LOG_PRINT (_stmt)
#endif
#if 0
#undef  DBG_INFO
#define DBG_INFO(_stmt)     DBG_LOG_PRINT (_stmt)
#endif

#ifndef POP_FRAMES_TIMEOUT
#define POP_FRAMES_TIMEOUT  (20000)
#endif

#ifndef POP_SWAP_TIMEOUT
#define POP_SWAP_TIMEOUT    (500)
#endif

#define _POP_TV_NORMAL_MODE_CHANGE_TIMEOUT          (10000)

#define HIDE_OSD_FRAMES         FALSE
#define SHOW_OSD_FRAMES         TRUE
#define CFG_ID_SCREEN_MODE      CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE)
#define CFG_ID_VID_BLUE_MUTE    CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE)
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
POP_T t_g_pop = {0};
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static VOID _pop_reset_timer(
                    POP_T*                      pt_this
                    );
static INT32 _pop_swap_post_handler(
                    POP_T*                      pt_this
                    );
static INT32 _pop_handle_rect_bg_per_av_status(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode
                    );
static INT32 _pop_update_pip_sub_win_rect_to_final(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    TV_WIN_ID_T                 e_tv_win_id
                    );
static INT32 _pop_change_win_region(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    TV_WIN_ID_T                 e_tv_win_id,
                    VSH_REGION_INFO_T*          pt_video_region,
                    BOOL                        b_repaint
                    );
static INT32 _pop_update_win_osd_rect(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    TV_WIN_ID_T                 e_tv_win_id,
                    VSH_REGION_INFO_T*          pt_video_region,
                    BOOL                        b_repaint
                    );
static INT32 _pop_enter_pop_mode(
                    POP_T*                      pt_this,
                    BOOL                        b_from_acfg
                    );
static INT32 _pop_enter_pip_mode(
                    POP_T*                      pt_this,
                    BOOL                        b_from_acfg
                    );
static INT32 _pop_enter_normal_mode(
                    POP_T*                      pt_this,
                    BOOL                        b_from_acfg
                    );
static INT32 _pop_select_audio_stream(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id,
                    BOOL                        b_force_select
                    );
static VOID _pop_store_last_main_sub_source(
                    POP_T*                      pt_this
                    );
static BOOL _pop_need_resize_disp_region(
                    TV_WIN_ID_T                 e_tv_win_id
                    );
static INT32 _pop_select_tv_window(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    TV_WIN_ID_T                 e_tv_win_id,
                    ISL_REC_T*                  pt_isl_rec,
                    SNK_DESC_T*                 pt_snk_desc,
                    BOOL                        b_blank,
                    BOOL                        b_repaint
                    );
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

static BOOL _pop_is_select_default_when_focus_chg(TV_WIN_ID_T e_tv_win_id)
{
	return a_icl_get_running_sts(e_tv_win_id, ICL_CHANNEL_RUNNING_STS_SPDIF_TYPE_CHANGE);
}
static INT32 _pop_update_audio_focus_icl (TV_WIN_ID_T e_audio_focus_win)
{
    SIZE_T                      z_size;

    z_size = sizeof(TV_WIN_ID_T);
    return a_icl_set (ICL_MAKE_ID(ICL_GRPID_PIP_POP, ICL_RECID_AUDIO_FOCUS), &e_audio_focus_win, z_size);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_lock
 * Description
 *      The API is to lock the global data used in the module
 * Input arguments
 *      -
 * Output arguments
 *      -
 * Returns
 *      -
 *---------------------------------------------------------------------------*/
static VOID _pop_lock(VOID)
{
    c_sema_lock(t_g_pop.h_lock, X_SEMA_OPTION_WAIT);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_unlock
 * Description
 *      The API is to unlock the global data used in the module
 * Input arguments
 *      -
 * Output arguments
 *      -
 * Returns
 *      -
 *---------------------------------------------------------------------------*/
static VOID _pop_unlock(VOID)
{
    c_sema_unlock(t_g_pop.h_lock);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_last_tv_mode
 * Description
 * Input arguments
 *      None
 * Output arguments
 *      pe_last_tv_mode
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_get_last_tv_mode(
                    TV_MODE_T*                  pe_last_tv_mode
                    )
{
    ASSERT_APPL(0, pe_last_tv_mode != NULL, ("pe_last_tv_mode = NULL\r\n"));

    _pop_lock();
    *pe_last_tv_mode = t_g_pop.e_last_tv_mode;
    _pop_unlock();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_set_last_tv_mode
 * Description
 * Input arguments
 *      e_last_tv_mode
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_set_last_tv_mode(
                    TV_MODE_T                   e_last_tv_mode
                    )
{
    _pop_lock();
    t_g_pop.e_last_tv_mode = e_last_tv_mode;
    _pop_unlock();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_set_audio_stream_type_data
 * Description
 * Input arguments
 *      e_last_tv_mode
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_set_audio_stream_type_data(
                    TV_WIN_ID_T                 e_tv_win_id,
                    SCDB_REC_TYPE_T             e_type
                    )
{
    ASSERT_APPL(0, e_tv_win_id != TV_WIN_ID_LAST_VALID_ENTRY, ("e_tv_win_id = TV_WIN_ID_LAST_VALID_ENTRY\r\n"));

    _pop_lock();
    t_g_pop.t_audios[e_tv_win_id].e_type = e_type;
    _pop_unlock();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_reset_might_single_rf_scan
 * Description
 * Input arguments
 *      e_last_tv_mode
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _pop_reset_might_single_rf_scan(
                    VOID
                    )
{
    _pop_lock();
    t_g_pop.b_might_single_rf_scan[TV_WIN_ID_MAIN] = FALSE;
    t_g_pop.b_might_single_rf_scan[TV_WIN_ID_SUB]  = FALSE;
    _pop_unlock();
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_set_might_single_rf_scan
 * Description
 * Input arguments
 *      e_last_tv_mode
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_set_might_single_rf_scan(
                    TV_WIN_ID_T                 e_tv_win_id,
                    BOOL                        b_enable
                    )
{
    if (e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY) {
        return NAVR_INV_ARG;
    }
    
    _pop_lock();
    t_g_pop.b_might_single_rf_scan[e_tv_win_id] = b_enable;
    _pop_unlock();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_might_single_rf_scan
 * Description
 * Input arguments
 *      e_last_tv_mode
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_get_might_single_rf_scan(
                    TV_WIN_ID_T                 e_tv_win_id,
                    BOOL*                       pb_enable
                    )
{
    if (e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY || pb_enable == NULL) {
        return NAVR_INV_ARG;
    }
    
    _pop_lock();
    *pb_enable = t_g_pop.b_might_single_rf_scan[e_tv_win_id];
    _pop_unlock();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_set_audio_stream_data_by_rec
 * Description
 * Input arguments
 *      e_last_tv_mode
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_set_audio_stream_data_by_rec(
                    TV_WIN_ID_T                 e_tv_win_id,
                    STREAM_COMP_ID_T*           pt_comp_id,
                    SCDB_REC_T*                 pt_scdb_rec
                    )
{
    ASSERT_APPL(0, e_tv_win_id != TV_WIN_ID_LAST_VALID_ENTRY, ("e_tv_win_id = TV_WIN_ID_LAST_VALID_ENTRY\r\n"));
    ASSERT_APPL(0, pt_comp_id != NULL, ("pt_comp_id = NULL\r\n"));
    ASSERT_APPL(0, pt_scdb_rec != NULL, ("pt_scdb_rec = NULL\r\n"));

    _pop_lock();
    t_g_pop.t_audios[e_tv_win_id].e_type    = pt_scdb_rec->e_rec_type;
    t_g_pop.t_audios[e_tv_win_id].t_comp_id = *pt_comp_id;
    if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG) {
        t_g_pop.t_audios[e_tv_win_id].t_mpeg = pt_scdb_rec->u.t_audio_mpeg;
    }
    _pop_unlock();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_set_audio_stream_data
 * Description
 * Input arguments
 *      e_last_tv_mode
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_set_audio_stream_data(
                    TV_WIN_ID_T                 e_tv_win_id,
                    POP_AUDIO_T*                pt_audio_strema_data
                    )
{
    ASSERT_APPL(0, e_tv_win_id != TV_WIN_ID_LAST_VALID_ENTRY, ("e_tv_win_id = TV_WIN_ID_LAST_VALID_ENTRY\r\n"));
    ASSERT_APPL(0, pt_audio_strema_data != NULL, ("pt_audio_strema_data = NULL\r\n"));

    _pop_lock();
    t_g_pop.t_audios[e_tv_win_id] = *pt_audio_strema_data;
    _pop_unlock();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_audio_stream_data
 * Description
 * Input arguments
 *      e_last_tv_mode
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_get_audio_stream_data(
                    TV_WIN_ID_T                 e_tv_win_id,
                    POP_AUDIO_T*                pt_audio_strema_data
                    )
{
    ASSERT_APPL(0, e_tv_win_id != TV_WIN_ID_LAST_VALID_ENTRY, ("e_tv_win_id = TV_WIN_ID_LAST_VALID_ENTRY\r\n"));
    ASSERT_APPL(0, pt_audio_strema_data != NULL, ("pt_audio_strema_data = NULL\r\n"));

    _pop_lock();
    *pt_audio_strema_data = t_g_pop.t_audios[e_tv_win_id];
    _pop_unlock();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_enable_default_video_plane_mode
 * Description
 *      The API is to enable or disable video plane
 * Input arguments
 *      -
 * Output arguments
 *      -
 * Returns
 *      -
 *---------------------------------------------------------------------------*/
static INT32 _pop_enable_default_video_plane_mode(
                    TV_WIN_ID_T                 e_tv_win_id,
                    BOOL                        b_enable
                    )
{
    HANDLE_T h_svctx;

    /* delay to select audio until video plane is enabled to avoid av not sync */
    if (b_enable == TRUE 
            && e_tv_win_id == t_g_pop.e_audio_focus_id
            && nav_is_audio_comp_playing(e_tv_win_id) == FALSE) {
        _pop_select_audio_stream(&t_g_pop, e_tv_win_id, FALSE);
    }

    nav_get_svctx_handle (e_tv_win_id, &h_svctx);

    /* Enable means unmute. Hence, reverse it. */
    APPTV_DEBUG_WHO_CALL_MUTE(e_tv_win_id, TV_VIDEO_MUTE_MASK_PIP, (!b_enable) );
    return A_TV_SET_VIDEO_MUTE (VIDEO_MUTE_ID_POP, h_svctx, TV_VIDEO_MUTE_MASK_PIP, !b_enable);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_is_crnt_input_source_blocked
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _pop_is_crnt_input_source_blocked(
                    TV_WIN_ID_T                 e_win_id
                    )
{
    ISL_REC_T t_isl_rec;
    INT32     i4_ret;
    
    
    i4_ret = a_tv_get_isl_rec_by_win_id(e_win_id, &t_isl_rec);
    if (i4_ret != ISLR_OK) {
        return FALSE;
    }
    
    return a_tv_is_input_source_blocked(t_isl_rec.ui1_id);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_show_win_rect_bg
 * Description
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_show_win_rect_bg(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    POP_RECT_BG_CMD_T           e_bg_cmd,
                    BOOL                        b_repaint
                    )
{
/*  disable to avoid lighter video mute color bars as no video in PIP.sub
    INT32 i4_ret;

    if (e_tv_win_id == TV_WIN_ID_SUB
            && e_bg_cmd == POP_RECT_BG_CMD_SHOW
            && e_tv_mode == TV_MODE_TYPE_PIP) {
        VSH_REGION_INFO_T t_sub_video_region  = {0};

        i4_ret = pop_get_pip_sub_region_info(
                    WIN_POS_DIR_CRNT,
                    WIN_SIZE_DIR_CRNT,
                    &t_sub_video_region
                    );
        if (i4_ret == NAVR_OK) {
            _pop_update_win_osd_rect(
                    pt_this,
                    e_tv_mode,
                    TV_WIN_ID_SUB,
                    &t_sub_video_region,
                    FALSE
                    );
        }
    }
*/
    
    if (e_bg_cmd == POP_RECT_BG_CMD_SHOW) {
        BOOL b_enable = FALSE;
        
        if (_pop_get_might_single_rf_scan(e_tv_win_id, &b_enable) == NAVR_OK 
                && b_enable == TRUE) {
            return NAVR_OK;
        }
    } else if (e_bg_cmd == POP_RECT_BG_CMD_BLACK) {
        if (_pop_is_crnt_input_source_blocked(e_tv_win_id) == TRUE) {
            e_bg_cmd = POP_RECT_BG_CMD_SHOW;
        }
    }
                
    return pt_this->t_view_hdlr.pf_show_win_rect_bg(
                    e_tv_win_id,
                    e_tv_mode,
                    e_bg_cmd,
                    b_repaint
                    );
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_audio_strm_comp_filter
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *-----------------------------------------------------------------------------*/
static BOOL _pop_audio_strm_comp_filter (
                    UINT16                      ui2_num_recs,
                    UINT16                      ui2_idx,
                    const STREAM_COMP_ID_T*     pt_comp_id,
                    const SCDB_REC_T*           pt_scdb_rec,
                    VOID*                       pv_tag
                    )
{
    POP_AUDIO_T* pt_audio = (POP_AUDIO_T*)pv_tag;

    if (pt_scdb_rec->e_rec_type == SCDB_REC_TYPE_AUDIO_MPEG) {
        if (pt_audio != NULL && pt_audio->e_type == SCDB_REC_TYPE_AUDIO_MPEG) {
            if (TRUE == a_aud_is_same_audio_mpeg_stream (
                                    pt_scdb_rec->u.t_audio_mpeg,
                                    pt_audio->t_mpeg)) {
                return TRUE;
            }

            if (ui2_idx < ui2_num_recs) {
                /* if not the last chance (ui2_idx == ui2_num_recs),
                 * just to iterate to next.
                 */
                return FALSE;
            } else {
                /* if last chance, just select this one */
                return TRUE;
            }
        }
    }

    return nav_default_audio_strm_comp_filter(
                    ui2_num_recs,
                    ui2_idx,
                    pt_comp_id,
                    pt_scdb_rec
                    );
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_swap_audio_steam_data
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_swap_audio_steam_data(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode
                    )
{
    POP_AUDIO_T      t_tmp_audios[TV_WIN_ID_LAST_VALID_ENTRY];
    SCDB_REC_T       t_scdb_rec;
    STREAM_COMP_ID_T t_comp_id;
    INT32            i4_ret;

	c_memset(&t_scdb_rec, 0, sizeof(SCDB_REC_T));

    _pop_get_audio_stream_data(TV_WIN_ID_MAIN, &(t_tmp_audios[TV_WIN_ID_MAIN]));
    _pop_get_audio_stream_data(TV_WIN_ID_SUB, &(t_tmp_audios[TV_WIN_ID_SUB]));

    /* store main's audio pip as sub's */
    _pop_set_audio_stream_type_data(TV_WIN_ID_SUB, SCDB_REC_TYPE_UNKNOWN);
    i4_ret = nav_get_using_strm_data(
                    TV_WIN_ID_MAIN,
                    ST_AUDIO,
                    &t_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
        _pop_set_audio_stream_data_by_rec(TV_WIN_ID_SUB, &t_comp_id, &t_scdb_rec);
    } else {
        _pop_set_audio_stream_data(TV_WIN_ID_SUB, &(t_tmp_audios[TV_WIN_ID_MAIN]));
    }

    /* store sub's audio pip as main's */
    _pop_set_audio_stream_type_data(TV_WIN_ID_MAIN, SCDB_REC_TYPE_UNKNOWN);
    i4_ret = nav_get_using_strm_data(
                    TV_WIN_ID_SUB,
                    ST_AUDIO,
                    &t_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
        _pop_set_audio_stream_data_by_rec(TV_WIN_ID_MAIN, &t_comp_id, &t_scdb_rec);
    } else {
        _pop_set_audio_stream_data(TV_WIN_ID_MAIN, &(t_tmp_audios[TV_WIN_ID_SUB]));
    }

    pt_this->b_using_pip_audio_strm_filter = TRUE;

    /* set main's audio pid stream filter */
    i4_ret = nav_set_default_strm_filter(
                    TV_WIN_ID_MAIN,
                    ST_AUDIO,
                    _pop_audio_strm_comp_filter,
                    &pt_this->t_audios[TV_WIN_ID_MAIN]
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /*
     *  From the request of SVCTX.
     *  If current or incoming tv mode is normal, do not set audio stream filter.
     *  This can forbid SVCTX to set the pv_filter_fct and pv_tag to SUB's.
     *  This is for CR 136542.
     */
    if (e_tv_mode != TV_MODE_TYPE_NORMAL)
    {
        /* set sub's audio pid stream filter */
        i4_ret = nav_set_default_strm_filter(
                        TV_WIN_ID_SUB,
                        ST_AUDIO,
                        _pop_audio_strm_comp_filter,
                        &pt_this->t_audios[TV_WIN_ID_SUB]
                        );
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_update_audio_steam_data
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_update_audio_steam_data(
                    POP_T*                      pt_this
                    )
{
    SCDB_REC_T       t_scdb_rec;
    STREAM_COMP_ID_T t_comp_id;
    INT32            i4_ret;

	c_memset(&t_scdb_rec, 0, sizeof(SCDB_REC_T));

    /* store main's audio pip as sub's */
    i4_ret = nav_get_using_strm_data(
                    TV_WIN_ID_MAIN,
                    ST_AUDIO,
                    &t_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
        _pop_set_audio_stream_data_by_rec(TV_WIN_ID_MAIN, &t_comp_id, &t_scdb_rec);
    }

    /* store sub's audio pip as main's */
    i4_ret = nav_get_using_strm_data(
                    TV_WIN_ID_SUB,
                    ST_AUDIO,
                    &t_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
        _pop_set_audio_stream_data_by_rec(TV_WIN_ID_SUB, &t_comp_id, &t_scdb_rec);
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_set_main_video_mute_via_pmx_bg
 * Description
 *      The API will set the pmx bg enable flag and also set PMX directly.
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_set_main_video_mute_via_pmx_bg(
                    BOOL                        b_enable
                    )
{
    HANDLE_T h_svctx;
    INT32    i4_ret;

    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_svctx_set(
                    h_svctx,
                    SVCTX_COMMON_SET_VIDEO_MUTE_VIA_PMX_BG,
                    (VOID*)&b_enable,
                    sizeof(BOOL)
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_set_screen_status
 * Description
 *      The API will set the screen status of a window.
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_set_screen_status(
                    TV_WIN_ID_T                 e_tv_win_id,
                    SVCTX_SCREEN_STATUS_T       e_scrn_mode
                    )
{
    HANDLE_T h_svctx;
    INT32    i4_ret;

    i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_svctx_set(
                    h_svctx,
                    SVCTX_COMMON_SET_SCREEN_STATUS,
                    (VOID*)&e_scrn_mode,
                    sizeof(SVCTX_SCREEN_STATUS_T)
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_hide_wins
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_hide_wins(
                    POP_T*                      pt_this
                    )
{
    INT32 i4_ret;

    i4_ret = pt_this->t_view_hdlr.pf_hide(FALSE);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    pt_this->b_frames_shown = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_is_mmp_running
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _pop_is_mmp_running(
                    VOID
                    )
{
    CHAR  s_app_name[APP_NAME_MAX_LEN+1] = {'\0'};
    INT32 i4_ret;

    if (nav_is_active() == TRUE) {
        return FALSE;
    }

    i4_ret = a_am_get_next_active_app(s_app_name);
    if (i4_ret != AMBR_OK) {
        return FALSE;
    }

    if (c_strcmp(MMP_NAME, s_app_name) == 0) {
        return TRUE;
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_is_cooperative_app
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _pop_is_cooperative_app(
                    VOID
                    )
{
    CHAR  s_app_name[APP_NAME_MAX_LEN+1] = {'\0'};
    INT32 i4_ret;

    if (nav_is_active() == TRUE) {
        return TRUE;
    }

    i4_ret = a_am_get_active_app(s_app_name);
    if (i4_ret != AMBR_OK) {
        return FALSE;
    }

    if (c_strcmp(MENU_NAME, s_app_name) == 0) {
        return TRUE;
    }

    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_force_audio_stream_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_force_audio_stream_mode (TV_WIN_ID_T e_audio_focus_id)
{
    UINT32 ui4_stream_mode = 0;

    /* set blue win to have NOT audio stream */
    nav_get_stream_mode(e_audio_focus_id, &ui4_stream_mode);
    nav_set_stream_mode(e_audio_focus_id, ui4_stream_mode |ST_MASK_AUDIO);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_update_tv_wins_audio_stream_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_update_tv_wins_audio_stream_mode(
                    TV_WIN_ID_T                 e_focus_id,
                    TV_WIN_ID_T                 e_blur_id
                    )
{
    UINT32 ui4_stream_mode = 0;

    /* set blue win to have NOT audio stream */
    nav_get_stream_mode(e_blur_id, &ui4_stream_mode);
    nav_set_stream_mode(e_blur_id, ui4_stream_mode & ~ST_MASK_AUDIO);

    /* set focus win to have audio stream */
    nav_get_stream_mode(e_focus_id, &ui4_stream_mode);
    nav_set_stream_mode(e_focus_id, ui4_stream_mode|ST_MASK_AUDIO);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_unfreeze
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_unfreeze(
                    TV_WIN_ID_T                 e_win_id
                    )
{
#ifdef APP_NAV_FRZ_SUPPORT
    nav_frz_freeze(e_win_id, FALSE);
#else
    HANDLE_T h_svctx = NULL_HANDLE;
    BOOL     b_is_frozen = FALSE;
    INT32    i4_ret;

    i4_ret = nav_get_svctx_handle(e_win_id, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_svctx_is_frozen(h_svctx, &b_is_frozen);
    if (i4_ret < SVCTXR_OK) {
        return NAVR_FAIL;
    }

    if (b_is_frozen == FALSE) {
        return NAVR_OK;
    }

    i4_ret = c_svctx_unfreeze(h_svctx);
    if (i4_ret < SVCTXR_OK) {
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_show_osd_frames
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_show_osd_frames(
                    POP_T*                      pt_this,
                    BOOL                        b_show
                    )
{
    INT32 i4_ret;

    if (b_show == TRUE) {
        _pop_reset_timer(pt_this);
    }

    if (b_show == pt_this->b_frames_shown) {
        return NAVR_NO_ACTION;
    }

    i4_ret = pt_this->t_view_hdlr.pf_show_frames(b_show);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    pt_this->b_frames_shown = b_show;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    POP_T* pt_this = (POP_T*)pv_tag;

    _pop_show_osd_frames(pt_this, HIDE_OSD_FRAMES);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_pop_timeout_to_hide, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_update_pip_sub_screen_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_update_pip_sub_screen_mode(
                    BOOL                        b_with_video
                    )
{
    SCC_VID_SCREEN_MODE_T e_scr_mod = SCC_VID_SCREEN_MODE_UNKNOWN;
    HANDLE_T              h_svctx;
    INT32                 i4_ret = NAVR_OK;    
    TV_WIN_ID_T           e_focus_id;

    i4_ret = nav_get_focus_id(&e_focus_id);
    if (i4_ret != NAVR_OK) {
        return;
    }
    /* In PAL&Secam scanning, it will show the video. In this case,
       don't update the video  */
    if (nav_is_channel_scan_active ())
    {
        return;
    }
    if (b_with_video == TRUE) {
        a_cfg_lock();
        do
        {
            if (e_focus_id == TV_WIN_ID_MAIN) {
                /* in order to let a_cfg_av_update() to force to get SUB's SCREEN_MODE */
                i4_ret = a_cfg_av_set_disp_name(SN_PRES_SUB_DISPLAY);
                if (i4_ret != APP_CFGR_OK) {
                    break;
                }
            }
            
            a_cfg_get_screen_mode(&e_scr_mod);
        
            if (e_focus_id == TV_WIN_ID_MAIN) {
                /* restore back */
                i4_ret = a_cfg_av_set_disp_name(SN_PRES_MAIN_DISPLAY);
                if (i4_ret != APP_CFGR_OK) {
                    break;
                }
            }
        }while(0);
        a_cfg_unlock();
    }
    
    /* force to re-caculate the final disp region - left-align or right-align */
    i4_ret = nav_get_svctx_handle(TV_WIN_ID_SUB, &h_svctx);
    if (i4_ret == NAVR_OK) {
        c_svctx_set_screen_mode(h_svctx, e_scr_mod);
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_update_pip_sub_win_rect_for_aspect_ratio
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_update_pip_sub_win_rect_for_aspect_ratio(
                    POP_T*                      pt_this
                    )
{
    TV_MODE_T   e_tv_mode = TV_MODE_TYPE_NORMAL;
    INT32       i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK || e_tv_mode != TV_MODE_TYPE_PIP) {
        return;
    }
    
    _pop_update_pip_sub_win_rect_to_final(
                    pt_this,
                    TV_MODE_TYPE_PIP,
                    TV_WIN_ID_SUB
                    );
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_stop_timer(
                    POP_T*                      pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop pop::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_reset_timer(
                    POP_T*                      pt_this
                    )
{
    INT32 i4_ret;

    if (pt_this->ui4_hide_timeout == 0) {
        return;
    }

    _pop_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    pt_this->ui4_hide_timeout,
                    X_TIMER_FLAG_ONCE,
                    _pop_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pop::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_timeout_to_swap
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_timeout_to_swap(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    POP_T* pt_this = (POP_T*)pv_tag;
    
    _pop_swap_post_handler(pt_this);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_swap_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_swap_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_pop_timeout_to_swap, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_stop_swap_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_stop_swap_timer(
                    POP_T*                      pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_swap_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_swap_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop pop::h_swap_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_reset_swap_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_reset_swap_timer(
                    POP_T*                      pt_this
                    )
{
    INT32 i4_ret;

    nav_update_src_info(TV_WIN_ID_MAIN);
    nav_update_src_info(TV_WIN_ID_SUB);

    nav_brdcst_msg_from_component(
                    TV_WIN_ID_LAST_VALID_ENTRY,
                    NAV_UI_MSG_AFTER_SVCS_SWAP,
                    NULL
                    );

    _pop_stop_swap_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_swap_timer,
                    POP_SWAP_TIMEOUT,
                    X_TIMER_FLAG_ONCE,
                    _pop_swap_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pop::h_swap_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_win_rect
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_get_win_rect(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    VSH_REGION_INFO_T*          pt_video_region,
                    GL_RECT_T*                  pt_win_rect
                    )
{
    pt_win_rect->i4_left   = (INT32)(pt_video_region->ui4_x * pt_this->ui4_canvas_width  / VSH_REGION_MAX_WIDTH);
    pt_win_rect->i4_top    = (INT32)(pt_video_region->ui4_y * pt_this->ui4_canvas_height / VSH_REGION_MAX_HEIGHT);
    pt_win_rect->i4_right  = pt_win_rect->i4_left + (INT32)(pt_video_region->ui4_width  * pt_this->ui4_canvas_width  / VSH_REGION_MAX_WIDTH);
    pt_win_rect->i4_bottom = pt_win_rect->i4_top  + (INT32)(pt_video_region->ui4_height * pt_this->ui4_canvas_height / VSH_REGION_MAX_HEIGHT);

    /* in order to compensate 1/1000 video region inaccuracy */
    if (pt_win_rect->i4_top != 0) {
        pt_win_rect->i4_top -= 2;
    }

    if (e_tv_mode == TV_MODE_TYPE_PIP && pt_win_rect->i4_left != 0) {
        pt_win_rect->i4_left -= 2;
    }

    /* in order to compensate 1/1000 video region inaccuracy */
    if (pt_win_rect->i4_bottom != ((INT32)pt_this->ui4_canvas_height)) {
        pt_win_rect->i4_bottom += 2;
    }

    if (e_tv_mode == TV_MODE_TYPE_PIP && pt_win_rect->i4_right != ((INT32)pt_this->ui4_canvas_width)) {
        pt_win_rect->i4_right += 2;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_hide(
                    VOID
                    )
{
    POP_T* pt_this = &t_g_pop;

    pt_this->t_view_hdlr.pf_hide_msg();
    nav_return_activation(NAV_COMP_ID_PIP_POP);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_check_to_show_win_rect_bg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_check_to_show_win_rect_bg (
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    BOOL                        b_repaint
                    )
{
    if (nav_is_svl_empty(e_tv_win_id) == TRUE
                    || nav_is_signal_loss(e_tv_win_id) == TRUE
                    || nav_get_locked_status(e_tv_win_id) != LOCKED_STATUS_NONE
                    || nav_get_video_timing_type(e_tv_win_id) == VSH_SRC_TIMING_NOT_SUPPORT) {
        return _pop_show_win_rect_bg(
                    pt_this,
                    e_tv_win_id,
                    e_tv_mode,
                    POP_RECT_BG_CMD_SHOW,
                    b_repaint
                    );
    } else {
        return _pop_handle_rect_bg_per_av_status(
                    pt_this,
                    e_tv_win_id,
                    e_tv_mode
                    );
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_handle_blue_mute_cfg_update
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_handle_blue_mute_cfg_update(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode
                    )
{
    INT32 i4_ret;

    i4_ret = _pop_check_to_show_win_rect_bg (
                    pt_this,
                    TV_WIN_ID_MAIN,
                    e_tv_mode,
                    TRUE
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _pop_check_to_show_win_rect_bg (
                    pt_this,
                    TV_WIN_ID_SUB,
                    e_tv_mode,
                    TRUE
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_select_audio_stream
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_select_audio_stream(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id,
                    BOOL                        b_force_select
                    )
{
    STREAM_COMP_ID_T t_using_comp_id;
    SCDB_REC_T       t_using_scdb_rec;
    INT32            i4_ret;

	c_memset(&t_using_scdb_rec, 0, sizeof(SCDB_REC_T));

    if (nav_is_channel_scan_active() == TRUE) {
        return NAVR_OK;
    }

    if (e_tv_win_id == TV_WIN_ID_LAST_VALID_ENTRY) {
        return NAVR_OK;
    }

    if (!b_force_select)
    {
        if (pt_this->ui1_swap_selecting_tv_win_bits > 0) {
            return NAVR_OK;
        }
    }

    i4_ret = nav_get_using_strm_data(
                    e_tv_win_id,
                    ST_AUDIO,
                    &t_using_comp_id,
                    &t_using_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
        _pop_set_audio_stream_data_by_rec(e_tv_win_id, &t_using_comp_id, &t_using_scdb_rec);
    } else {
        POP_AUDIO_T t_audio_strema_data;

        if (_pop_is_select_default_when_focus_chg (e_tv_win_id))
        {
            i4_ret = nav_select_default_audio_stream(e_tv_win_id, &t_using_comp_id);
        }
        else
        {
            /* try to play the stored one */
            _pop_get_audio_stream_data(e_tv_win_id, &t_audio_strema_data);
            if (t_audio_strema_data.e_type != SCDB_REC_TYPE_UNKNOWN) {
                i4_ret = nav_get_stream_comp_id(
                            e_tv_win_id,
                            ST_AUDIO,
                            _pop_audio_strm_comp_filter,
                            &t_audio_strema_data,
                            &t_using_comp_id,
                            &t_using_scdb_rec
                            );
                if (i4_ret == NAVR_OK) {
                    i4_ret = nav_select_stream(e_tv_win_id, &t_using_comp_id);
                }
            }
    
            if (i4_ret != NAVR_OK) {
                /* still cannot find comp_id, try to play the default one */
                i4_ret = nav_select_default_audio_stream(e_tv_win_id, &t_using_comp_id);
            }
        }
    }
    
    if (i4_ret == NAVR_NOT_EXIST) {
        NAV_STREAM_NOTIFY_DATA_T t_nfy_data;

        t_nfy_data.e_strm_type = ST_AUDIO;
        t_nfy_data.e_type      = NAV_SNT_STREAM_NOT_FOUND;
        
        nav_brdcst_msg_from_component(
                    e_tv_win_id,
                    NAV_UI_MSG_STREAM_NOTIFY,
                    (VOID*)&t_nfy_data
                    );
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_select_audio_stream_for_focus_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_select_audio_stream_for_focus_change(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id
                    )
{
    INT32 i4_ret;
    UINT32        ui4_scrambled_strm = 0;

    if (pt_this->b_audio_focus_changing == FALSE) {
        return NAVR_OK;
    }
    
    pt_this->e_audio_focus_id = e_tv_win_id;
    _pop_update_audio_focus_icl (e_tv_win_id);

    do
    {
        /* 
         *  If the focus win is scrambled channel, force to select audio stream
         *  to make "Scrambled Audio" to be displayed ASAP.
         */
        i4_ret = nav_get_ca_status(e_tv_win_id, &ui4_scrambled_strm);
        if (i4_ret == NAVR_OK)
        {
            if ((ui4_scrambled_strm & MAKE_BIT_MASK_32(ST_VIDEO)) > 0)
            {
                _pop_select_audio_stream(pt_this, e_tv_win_id, TRUE);
                break;
            }
        }
        /* Normal case. */
        i4_ret = _pop_select_audio_stream(pt_this, e_tv_win_id, FALSE);
    } while (0);

    
    if (i4_ret == NAVR_OK || i4_ret == NAVR_NOT_EXIST) {
        pt_this->b_audio_focus_changing = FALSE;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_start_focus_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_start_focus_change(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_focus_id
                    )
{
    STREAM_COMP_ID_T  t_blur_audio_comp_id;
    TV_WIN_ID_T       e_blur_id = NAV_GET_BLUR_ID(e_focus_id);
    SCDB_REC_T        t_scdb_rec;
    INT32             i4_ret;
    POP_AUDIO_T      t_tmp_audio;

	c_memset(&t_scdb_rec, 0, sizeof(SCDB_REC_T));

    _pop_get_audio_stream_data(e_blur_id, &t_tmp_audio);
#ifdef APP_DVBT_SUPPORT
    HANDLE_T          h_svctx;

    i4_ret = nav_get_svctx_handle(e_blur_id, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = a_tv_update_scart_out_attr(h_svctx);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = nav_get_svctx_handle(e_focus_id, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = a_tv_update_scart_out_attr(h_svctx);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif
    pt_this->e_audio_focus_id       = e_focus_id;
    pt_this->b_audio_focus_changing = TRUE;
    _pop_update_audio_focus_icl (pt_this->e_audio_focus_id);

    _pop_set_audio_stream_type_data(e_blur_id, SCDB_REC_TYPE_UNKNOWN);
    i4_ret = nav_get_using_strm_data(
                    e_blur_id,
                    ST_AUDIO,
                    &t_blur_audio_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
         _pop_set_audio_stream_data_by_rec(
                    e_blur_id,
                    &t_blur_audio_comp_id,
                    &t_scdb_rec
                    );
        i4_ret = nav_stop_stream(e_blur_id, ST_AUDIO);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    } else {
        /* even blur win has no audio, still need to change the stream mode in
         * service context.
         */
        i4_ret = nav_stop_stream(e_blur_id, ST_AUDIO);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        /* Rollback audio data. */
        _pop_set_audio_stream_data(e_blur_id, &t_tmp_audio);

        _pop_select_audio_stream_for_focus_change(pt_this, pt_this->e_audio_focus_id);
    }

    pt_this->t_view_hdlr.pf_set_focus(pt_this->e_audio_focus_id, e_blur_id, TRUE);

    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _pop_handle_tv_mode_change
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pop_handle_tv_mode_change (
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    BOOL                        b_from_acfg
                    )
{
    TV_MODE_T e_last_tv_mode;
    INT32     i4_ret;

    i4_ret = _pop_get_last_tv_mode(&e_last_tv_mode);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (e_last_tv_mode == e_tv_mode) {
        return NAVR_OK;
    }

    switch(e_tv_mode) {
    case TV_MODE_TYPE_NORMAL:
        i4_ret = _pop_enter_normal_mode(pt_this, b_from_acfg);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        break;
    case TV_MODE_TYPE_PIP:
        i4_ret = _pop_enter_pip_mode(pt_this, b_from_acfg);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        if (nav_is_active() == FALSE) {
            _pop_stop_timer(pt_this);
        }
        break;
    case TV_MODE_TYPE_POP:
        i4_ret = _pop_enter_pop_mode(pt_this, b_from_acfg);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        if (nav_is_active() == FALSE) {
            _pop_stop_timer(pt_this);
        }
        break;
    default:
        break;
    }
    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _pop_handle_pip_sub_pos_size_cfg_update
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _pop_handle_pip_sub_pos_size_cfg_update (
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode
                    )
{
#ifdef APP_NAV_LISTEN_PIP_SUB_POS_SIZE_CFG_CHANGE
    TV_PIP_SUB_POSITION_T e_pos_id;
    TV_PIP_SUB_SIZE_T     e_size_id;
    VSH_REGION_INFO_T     t_video_region;
    INT32                 i4_ret;

    if (e_tv_mode != TV_MODE_TYPE_PIP) {
        return NAVR_OK;
    }

    i4_ret = a_tv_get_pip_sub_position(&e_pos_id);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_get_pip_sub_size(&e_size_id);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = pop_get_pip_sub_region_info_by_id(
                    e_pos_id,
                    e_size_id,
                    &t_video_region
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = _pop_change_win_region(
                    pt_this,
                    e_tv_mode,
                    TV_WIN_ID_SUB,
                    &t_video_region,
                    TRUE
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }
#endif
    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _pop_handle_sync_request
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _pop_handle_sync_request (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    APP_TV_NET_SVC_STATUS e_svc_state = a_tv_net_get_tv_svc_status();
    
    if (e_svc_state == APP_TV_NET_SVC_STATUS_RESUMED)
    {
        nav_hide_component(NAV_COMP_ID_PIP_POP);
    }
}
/*----------------------------------------------------------------------------
 * Name: _pop_handle_cfg_nfy
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _pop_handle_cfg_nfy (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    POP_T*    pt_this        = &t_g_pop;
    UINT16    ui2_group_id   = (UINT16)(UINT32)pv_tag2;
    UINT16    ui2_setting_id = (UINT16)(UINT32)pv_tag3;
    TV_MODE_T e_tv_mode      = (TV_MODE_T)(UINT32)pv_tag1;
    INT32     i4_ret;

    switch(ui2_group_id) {
    case APP_CFG_GRPID_NAV:
        i4_ret = nav_get_tv_mode(&e_tv_mode);
        if (i4_ret != NAVR_OK) {
            break;
        }

        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }
        /* Input source changed. Update stored main/sub input source. */
        if ((ui2_setting_id == APP_CFG_RECID_INPUT_MAIN) || (ui2_setting_id == APP_CFG_RECID_INPUT_SUB))
        {
            _pop_store_last_main_sub_source(pt_this);
        }
        break;
    case APP_CFG_GRPID_VIDEO:
        switch(ui2_setting_id) {
        case APP_CFG_RECID_VID_BLUE_MUTE:
            /* as reset default in Menu, the following cfg will be reset
             * 1. Blue mute
             * 2. TV mode
             * 3. focus win, position, size, ...
             *
             * As receiving APP_CFG_RECID_VID_BLUE_MUTE in navigator's thread,
             * the TV mode is changed, so the e_tv_mode passed from _pop_cfg_nfy_fct
             * is not correct.
             */
            i4_ret = nav_get_tv_mode(&e_tv_mode);
            if (i4_ret != NAVR_OK) {
                break;
            }

            if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
                break;
            }

            a_cfg_av_update(CFG_ID_VID_BLUE_MUTE);

            i4_ret = _pop_handle_blue_mute_cfg_update(pt_this, e_tv_mode);
            break;
        default:
            break;
        }
        break;
    case APP_CFG_GRPID_PIP_POP:
        if (_pop_is_cooperative_app() == FALSE) {
            break;
        }
        switch(ui2_setting_id) {
        case APP_CFG_RECID_TV_MODE:
            if (nav_is_active() == FALSE) {
                if (e_tv_mode == TV_MODE_TYPE_PIP || e_tv_mode == TV_MODE_TYPE_POP) {
                    nav_set_bg_svctx_listening(TRUE);
                } else {
                    /*
                     *  This is for CR 216021.
                     *  When TV mode is changed to normal, set the disp_region of SUB to 0.
                     *  This code segment must be put before a_tv_before_mode_change ().
                     *  In a_tv_before_mode_change (), driver will reallocate buffer.
                     *  If we do not set the disp_region before this, green garbage will occur.
                     */
                    if (_pop_need_resize_disp_region(TV_WIN_ID_SUB) == TRUE) {
                         VSH_REGION_INFO_T t_dsp_region = {0};
                    
                         /* set main svctx to full display region */
                         t_dsp_region.ui4_x      = 0;
                         t_dsp_region.ui4_y      = 0;
                         t_dsp_region.ui4_width  = 0;
                         t_dsp_region.ui4_height = 0;
                    
                         i4_ret = nav_set_stream_attr(
                                     TV_WIN_ID_SUB,
                                     ST_VIDEO,
                                     SM_VSH_SET_TYPE_DISP_REGION,
                                     &t_dsp_region,
                                     sizeof(VSH_REGION_INFO_T)
                                     );
                         if (i4_ret != NAVR_OK) {
                             break;
                         }
                    }
                    nav_set_bg_svctx_listening(FALSE);
                }

                a_tv_before_mode_change(e_tv_mode);
            }
            _pop_handle_tv_mode_change(pt_this, e_tv_mode, TRUE);
            pt_this->e_tv_mode_in_changing = TV_MODE_TYPE_LAST_VALID_ENTRY;
            break;
        case APP_CFG_RECID_TV_FOCUS_WIN:
            if (e_tv_mode == TV_MODE_TYPE_PIP || e_tv_mode == TV_MODE_TYPE_POP) {
                TV_WIN_ID_T e_focus_id;

                i4_ret = nav_get_focus_id(&e_focus_id);
                if (i4_ret == NAVR_OK) {
                    /* the logic is similiar as pop_start_focus_change() */
                    nav_set_focus_id(e_focus_id, TRUE);
                    _pop_start_focus_change(pt_this, e_focus_id);
                }
            }
            break;
        case APP_CFG_RECID_PIP_POSITION:
        case APP_CFG_RECID_PIP_SIZE:
            i4_ret = _pop_handle_pip_sub_pos_size_cfg_update(
                            pt_this,
                            e_tv_mode
                            );
            break;
        default:
            break;
        }
        break;
    case APP_CFG_GRPID_GUI_LANG:
        switch(ui2_setting_id) {
        case APP_CFG_RECID_GUI_LANG:
            nav_view_reload_multi_lang_messages();
            pt_this->t_view_hdlr.pf_update_no_video_msg(e_tv_mode);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_store_last_main_sub_source
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_store_last_main_sub_source(
                    POP_T*                      pt_this
                    )
{
    ISL_REC_T t_main_isl_rec;
    ISL_REC_T t_sub_isl_rec;
    INT32     i4_ret;
    
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_main_isl_rec);
    if (i4_ret != TVR_OK) {
        return;
    }
    
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_SUB, &t_sub_isl_rec);
    if (i4_ret != TVR_OK) {
        return;
    }
    
    /* If ISLs of main/sub are the same, do not override the old ones. */
    if (t_main_isl_rec.ui1_id == t_sub_isl_rec.ui1_id)
    {
        return;
    }
    
    if ((t_main_isl_rec.t_avc_info.e_video_type & DEV_VTRL) != DEV_VTRL)
    {
        pt_this->ui1_src_ids[TV_WIN_ID_MAIN] = t_main_isl_rec.ui1_id;
    }
    if ((t_sub_isl_rec.t_avc_info.e_video_type & DEV_VTRL) != DEV_VTRL)
    {
        pt_this->ui1_src_ids[TV_WIN_ID_SUB]  = t_sub_isl_rec.ui1_id;    
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_reset_stream_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_reset_stream_mode (TV_WIN_ID_T e_tv_win)
{
    INT32 i4_ret;
    UINT32   ui4_stream_mode = ST_MASK_AUDIO | ST_MASK_VIDEO;
    HANDLE_T h_svctx;
    
    i4_ret = nav_get_svctx_handle(e_tv_win, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
    nav_set_stream_mode(e_tv_win, ui4_stream_mode);
    
    i4_ret = c_svctx_set(
                    h_svctx,
                    SVCTX_COMMON_SET_ADD_STREAM_MODE_BIT,
                    (VOID*)&ui4_stream_mode,
                    sizeof(UINT32)
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_select_main_svc_if_necessary
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_select_main_svc_if_necessary (VOID)
{
    INT32 i4_ret;
    /*
     *  If next running AP is not MMP, select SVC if necessary.
     *  This is used to forbid when triggering MMP with the focus on SUB.
     *  POP will select service again when MMP issues stop service and causes SVCTX timeout
     *  Hence, we do not select SVC again if next running AP is MMP.
     */
    if (!_pop_is_mmp_running ())
    {
        ISL_REC_T  t_main_isl_rec_in_config;
        BOOL       b_is_current_input_src = TRUE;
    
        /* check the MAIN's setting,
           if app_config's input src id != navigator main window's input src id,
           it should reselect current TV/AV source. */
    
        i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_main_isl_rec_in_config);
        if (i4_ret != TVR_OK) 
        {
            return NAVR_FAIL;
        }
       
        i4_ret =  nav_is_crnt_input_src(
                       TV_WIN_ID_MAIN,
                       & t_main_isl_rec_in_config,
                       & b_is_current_input_src
                       );
        if (i4_ret != TVR_OK)
        {
           return NAVR_FAIL;        
        }
       
        /* The sources are not the same, should correct. Reselect it. */
        if (b_is_current_input_src == FALSE)
        {
           nav_change_av_inp_by_id (TV_WIN_ID_MAIN,
                                    t_main_isl_rec_in_config.ui1_id,
                                    NULL);
        }          
    }
    
    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _pop_handle_exit_pip_pop_by_other_app_nfy
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _pop_handle_exit_pip_pop_by_other_app_nfy (
                    VOID*                       pv_tag1,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    BOOL      b_need_select_svc_after_ctx_switch = (BOOL) (UINT32) pv_tag1;

    _pop_store_last_main_sub_source(&t_g_pop);

    nav_set_focus_id(TV_WIN_ID_MAIN, TRUE);

    /* unregister key monitor if the exit PIP/POP is from other app */
    nav_unregister_key_monitor_nty_fct(NAV_COMP_ID_PIP_POP);
    nav_before_tv_mode_change(TV_MODE_TYPE_NORMAL);

    _pop_reset_stream_mode (TV_WIN_ID_MAIN);

    if (b_need_select_svc_after_ctx_switch)
    {
        _pop_select_main_svc_if_necessary ();
    }
    
    /* Force the swap flag to be FALSE. This is for CR 208233. */
    if (nav_is_pop_pip_swapping() == TRUE) {
        nav_set_pop_pip_swapping(FALSE);
    }

    nav_set_tv_mode (TV_MODE_TYPE_NORMAL);
    /* Reset audio focus id. */
    t_g_pop.e_audio_focus_id = TV_WIN_ID_LAST_VALID_ENTRY;
    _pop_update_audio_focus_icl (TV_WIN_ID_LAST_VALID_ENTRY);

    nav_hide_component(NAV_COMP_ID_PIP_POP);
    /* Reset bit masks while PIP/POP is exited. */
    t_g_pop.ui1_swap_selecting_tv_win_bits = 0;
    t_g_pop.ui1_swap_stopping_tv_win_bits = 0;
}
/*----------------------------------------------------------------------------
 * Name: _pop_cfg_nfy_fct
 *
 * Description:
 * Inputs:
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _pop_cfg_nfy_fct(
                    UINT16                      ui2_nfy_id,
                    VOID*                       pv_tag,
                    UINT16                      ui2_cfg_id
                    )
{

    UINT16    ui2_group_id;
    UINT16    ui2_setting_id;
    TV_MODE_T e_tv_mode;
    TV_MODE_T e_last_tv_mode;
    INT32     i4_ret;
    BOOL      b_need_select_svc_after_ctx_switch = TRUE;

    ui2_group_id   = CFG_GET_GROUP(ui2_cfg_id);
    ui2_setting_id = CFG_GET_SETTING(ui2_cfg_id);

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return;
    }

    switch(ui2_group_id) {
    case APP_CFG_GRPID_NAV:
        break;
    case APP_CFG_GRPID_VIDEO:
        switch(ui2_setting_id) {
        case APP_CFG_RECID_VID_BLUE_MUTE:
            break;
        case APP_CFG_RECID_SCREEN_MODE:
            if (nav_is_active() == FALSE) {
                if (e_tv_mode == TV_MODE_TYPE_PIP) {
                    /* aspect ratio change - update SUB's frame size */
                    _pop_update_pip_sub_win_rect_for_aspect_ratio(&t_g_pop);
                }
            }
            return;
        default:
            return;
        }
        break;
    case APP_CFG_GRPID_PIP_POP:
        switch(ui2_setting_id) {
        case APP_CFG_RECID_TV_MODE:
            i4_ret = _pop_get_last_tv_mode(&e_last_tv_mode);
            if (i4_ret != NAVR_OK) {
                return;
            }
            if (!t_g_pop.b_is_power_on_received)
            {
                /* Do nothing if POWER_ON is not received. */
                return;
            }
            if (nav_is_active() == TRUE && e_tv_mode == e_last_tv_mode) {
                return;
            }

            switch(e_tv_mode) {
            case TV_MODE_TYPE_NORMAL:
                /* in order to hide the OSD frames as soon as the
                 * mode change if enable by other applications
                 */
                /* 1. if request if from non-cooperative App
                 * 2. if request is from Other as active App is "Navigator"
                 */
                if (_pop_is_cooperative_app() == FALSE
                        || (nav_is_active() == TRUE && e_tv_mode != e_last_tv_mode)) {
                    HANDLE_T    h_sub_svctx = NULL_HANDLE;
                    HANDLE_T    h_main_svctx = NULL_HANDLE;
                    ISL_REC_T   t_focus_isl_rec;
                    ISL_REC_T   t_blur_isl_rec;
                    TV_WIN_ID_T e_focus_id;
                    TV_WIN_ID_T e_blur_id;
                    TV_WIN_ID_T e_ori_focus_id;

#ifdef _APP_NAV_POP_SCARTOUT_COEXIST_SUPPORT        
                    /* Stop exclusion for SCART OUT when entering normal mode. */
                    {
                        HANDLE_T h_svctx;
                
                        nav_get_svctx_handle(TV_WIN_ID_SUB, &h_svctx);
                        c_svctx_stop_exclusion(h_svctx, (SRC_TYPE_T)0);
                    }
#endif
                    /* Mute Main. */
                    i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, FALSE);
                    if (i4_ret != NAVR_OK) {
                        return;
                    }

                    /* Mute Sub. */
                    i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, FALSE);
                    if (i4_ret != NAVR_OK) {
                        return;
                    }

                    /*
                     *  For CR 139358, set disp region to 0 in order to avoid
                     *  transit state.
                     */
                    do
                    {
                        /* set sub to (0, 0, 0, 0) */
                        if (_pop_need_resize_disp_region(TV_WIN_ID_SUB) == TRUE) {
                            VSH_REGION_INFO_T t_dsp_region = {0};
                    
                            t_dsp_region.ui4_x      = 0;
                            t_dsp_region.ui4_y      = 0;
                            t_dsp_region.ui4_width  = 0;
                            t_dsp_region.ui4_height = 0;
                    
                            i4_ret = nav_set_stream_attr(
                                        TV_WIN_ID_SUB,
                                        ST_VIDEO,
                                        SM_VSH_SET_TYPE_DISP_REGION,
                                        &t_dsp_region,
                                        sizeof(VSH_REGION_INFO_T)
                                        );
                            if (i4_ret != NAVR_OK) {
                                break;
                            }
                        }
                    } while (0);

                    i4_ret = nav_get_focus_id(&e_focus_id);
                    if (i4_ret != NAVR_OK) {
                        return;
                    }
                    e_ori_focus_id = e_focus_id;
                    e_blur_id = NAV_GET_BLUR_ID(e_focus_id);

                    /* Swap stored audio stream data if focus on SUB. */
                    if (e_blur_id == TV_WIN_ID_MAIN) {
                        _pop_swap_audio_steam_data(&t_g_pop, TV_MODE_TYPE_NORMAL);
                    }

                    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_focus_isl_rec);
                    if (i4_ret != TVR_OK) {
                        return;
                    }

                    i4_ret = a_tv_get_isl_rec_by_win_id(e_blur_id, &t_blur_isl_rec);
                    if (i4_ret != TVR_OK) {
                        return;
                    }

                    /* Hide music notes. */
                    i4_ret = _pop_hide_wins(&t_g_pop);
                    if (i4_ret < TVR_OK) {
                        return;
                    }

                    if (e_blur_id == TV_WIN_ID_MAIN) {
                        /* swap main & sub input source id */
                        a_tv_set_input_src_id(TV_WIN_ID_SUB, t_blur_isl_rec.ui1_id);
                        a_tv_set_input_src_id(TV_WIN_ID_MAIN, t_focus_isl_rec.ui1_id);
                        a_tv_swap_tmp_unlock_info(TV_MODE_TYPE_NORMAL);
                    }

                    /* stop sub svctx */
                    i4_ret = a_tv_open(SVCTX_NAME_SUB, NULL, NULL, &h_sub_svctx);
                    if (i4_ret < TVR_OK) {
                        return;
                    }

                    a_tv_before_mode_change(e_tv_mode);

            	    do {
                        i4_ret = a_tv_set_focus_win(TV_WIN_ID_MAIN);
                        if (i4_ret < TVR_OK) {
                            break;
                        }

                        i4_ret = a_tv_stop(h_sub_svctx);
                        if (i4_ret < TVR_OK) {
                            break;
                        }
                    } while (0);

                    a_tv_close(h_sub_svctx);

                    if (e_blur_id == TV_WIN_ID_MAIN) {
                        /* stop main svctx */
                        i4_ret = a_tv_open(SVCTX_NAME_MAIN, NULL, NULL, &h_main_svctx);
                        if (i4_ret < TVR_OK) {
                            return;
                        }
                	    do {
                            i4_ret = a_tv_stop(h_main_svctx);
                            if (i4_ret < TVR_OK) {
                                break;
                            }
                        } while (0);

                        a_tv_close(h_main_svctx);
                    }
                    i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, TRUE);
                    if (i4_ret != NAVR_OK) {
                        return;
                    }

                    i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, TRUE);
                    if (i4_ret != NAVR_OK) {
                        return;
                    }

                    _pop_view_set_screen_status(TV_WIN_ID_MAIN, SVCTX_SCREEN_STATUS_SINGLE);
                    _pop_view_set_screen_status(TV_WIN_ID_SUB,  SVCTX_SCREEN_STATUS_UNKNOWN);
                    _pop_set_last_tv_mode(TV_MODE_TYPE_NORMAL);

                    _pop_reset_stream_mode (TV_WIN_ID_MAIN);
                    {
                        VSH_REGION_INFO_T t_dsp_region = {0};
                    
                        /* If in EPG , don't reset the disp_region. */
                        if (nav_is_component_visible(NAV_COMP_ID_EPG) == FALSE)
                        {
                            /* set main svctx to full display region */
                            t_dsp_region.ui4_x      = 0;
                            t_dsp_region.ui4_y      = 0;
                            t_dsp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
                            t_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT;
                    
                            i4_ret = nav_set_stream_attr(
                                        TV_WIN_ID_MAIN,
                                        ST_VIDEO,
                                        SM_VSH_SET_TYPE_DISP_REGION,
                                        &t_dsp_region,
                                        sizeof(VSH_REGION_INFO_T)
                                        );
                            if (i4_ret != NAVR_OK) {
                                return;
                            }
                        }
                        else
                        {
                            /* Next active component is EPG. */
                            if (e_tv_mode == TV_MODE_TYPE_NORMAL &&
                                e_ori_focus_id == TV_WIN_ID_SUB)
                            {
                                nav_brdcst_msg_from_component(
                                        TV_WIN_ID_LAST_VALID_ENTRY,
                                        NAV_UI_MSG_BEFORE_SVCS_SWAP,
                                        NULL
                                        );
                                nav_brdcst_msg_from_component(
                                        TV_WIN_ID_LAST_VALID_ENTRY,
                                        NAV_UI_MSG_AFTER_SVCS_SWAP,
                                        NULL
                                        );
                            }
                            
                            b_need_select_svc_after_ctx_switch = FALSE;
                            _pop_select_main_svc_if_necessary ();
                        }
                    }
#ifdef _APP_NAV_POP_SCARTOUT_COEXIST_SUPPORT
                    {
                        /*
                         *  For CR 139082.
                         *  Re-select TV scart will cause TVE enable. After TVE is enabled,
                         *  we can not issue any control to SUB.
                         */
                        HANDLE_T h_svl;

                        if (!_pop_is_mmp_running ())
                        {
                            nav_get_focus_id (&e_focus_id);
                            nav_get_svl_handle (e_focus_id, &h_svl);
                        
                            i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_focus_isl_rec);
                            if (i4_ret != TVR_OK) {
                                i4_ret = NAVR_FAIL;
                                return;
                            }
                            if (t_focus_isl_rec.e_src_type == INP_SRC_TYPE_AV)
                            {
                                a_tv_update (TV_UPDATE_SCART_BYPASS_RESELECT_TV_SCART, (VOID*)h_svl, NULL, NULL);
                            }
                            /* Force to re-select Main to make SCART out work. */
                            _pop_select_tv_window(
                                            &t_g_pop,
                                            TV_MODE_TYPE_NORMAL,
                                            TV_WIN_ID_MAIN,
                                            &t_focus_isl_rec,
                                            NULL,
                                            FALSE,
                                            TRUE
                                            );
                        }
                    }
#endif
                    nav_request_context_switch(
                            _pop_handle_exit_pip_pop_by_other_app_nfy,
                            (VOID*)(UINT32)b_need_select_svc_after_ctx_switch,
                            NULL,
                            NULL
                            );
                } else {
                    nav_request_context_switch_in_sync(
                            _pop_handle_cfg_nfy,
                            (VOID*)(UINT32)e_tv_mode,
                            (VOID*)(UINT32)ui2_group_id,
                            (VOID*)(UINT32)ui2_setting_id,
                            _POP_TV_NORMAL_MODE_CHANGE_TIMEOUT
                            );
                }
                return;
            default:
                break;
            }

            break;
        case APP_CFG_RECID_TV_FOCUS_WIN:
        case APP_CFG_RECID_PIP_POSITION:
        case APP_CFG_RECID_PIP_SIZE:
            if (nav_is_active() == TRUE) {
                return;
            }
            break;
        default:
            return;
        }
        break;
    case APP_CFG_GRPID_GUI_LANG:
        break;
    default:
        return;
    }

    nav_request_context_switch(
                _pop_handle_cfg_nfy,
                (VOID*)(UINT32)e_tv_mode,
                (VOID*)(UINT32)ui2_group_id,
                (VOID*)(UINT32)ui2_setting_id
                );
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_handle_update_pip_sub_win_ntfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_handle_update_pip_sub_win_ntfy(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _pop_update_pip_sub_win_rect_for_aspect_ratio(&t_g_pop);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_svctx_nfy_fct
 * Description
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _pop_svctx_nfy_fct(
                    HANDLE_T                        h_svctx,
                    SVCTX_COND_T                    e_nfy_cond,
                    SVCTX_NTFY_CODE_T               e_code,
                    STREAM_TYPE_T                   e_stream_type,
                    VOID*                           pv_nfy_tag
                    )
{
    POP_T*                    pt_this     = &t_g_pop;
    TV_WIN_ID_T               e_tv_win_id = TV_WIN_ID_MAIN;
    TV_MODE_T                 e_last_tv_mode;
    VSH_SRC_RESOLUTION_INFO_T t_video_res;

    c_memset (&t_video_res, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));

    /* Draw black/blue screen in advance to avoid the side-effect
     * as changing channel in menu. However, this is a tricky
     * solution to draw it in SVCTX's thread context.
     *
     * The correct solution is to use video plane's background
     * as the black/blue screen even no video stream are
     * started.
     *
     * 5/22/2007 Weider Chang (wait better solution to replace this)
     */

    if (_pop_is_cooperative_app() == FALSE) {
        if (nav_get_tv_mode(&e_last_tv_mode) != NAVR_OK) {
            return;
        }
    } else {
        if (_pop_get_last_tv_mode(&e_last_tv_mode) != NAVR_OK) {
            return;
        }
    }

    if (!(e_last_tv_mode == TV_MODE_TYPE_PIP || e_last_tv_mode == TV_MODE_TYPE_POP)) {
        return;
    }

    if (h_svctx == pt_this->h_sub_svctx) {
        e_tv_win_id = TV_WIN_ID_SUB;
    }

    switch(e_code) {
    case SVCTX_NTFY_CODE_SERVICE_BLOCKED:
        /* disable the flag to let simulated Blue Mute to be function */
        _pop_set_might_single_rf_scan(e_tv_win_id, FALSE);
        break;
    case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE:
        /* When unblock a channel or source, svctx will send SVCTX_NTFY_CODE_SERVICE_UNBLOCKED
         * and then SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE.
         * 
         * As POP receiving the SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE in svctx's thread,
         * the navigator's locked status is still not updated, and 
         * invoking nav_get_crnt_video_res_info() will return NAVR_FAIL. This will cause
         * the video to be shown, but the OSD blue mute is still on. The overlap between
         * OSD blue mute between Menu is clean to see video since the graphic frame buffer is 
         * only 2 (in order to reduce the memory consumption, i.e. cannot have the
         * alpha-composition on the OSD overlap part)
         * 
         * In this case, the locked status check can be ignored since
         * svctx will only send SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE as it is not blocked.
         * weiderchang 2008/12/17
         */
        if (nav_get_crnt_video_res_info_ignore_locked_status(e_tv_win_id, &t_video_res) == NAVR_OK) {
            if (t_video_res.e_timing_type == VSH_SRC_TIMING_VIDEO
                    || t_video_res.e_timing_type == VSH_SRC_TIMING_GRAPHIC) {
                if (e_last_tv_mode == TV_MODE_TYPE_PIP && e_tv_win_id == TV_WIN_ID_SUB) {
        			nav_request_context_switch(
                        _pop_handle_update_pip_sub_win_ntfy, 
                        NULL, 
                        NULL, 
                        NULL
                        );
                }
                break;
            }
        }
        return;
    case SVCTX_NTFY_CODE_STREAM_STARTED_AS_BLOCKED:
        /* the pip frame is still needed to adjust in this case */
        if (e_stream_type != ST_VIDEO) {
            return;
        }
        /* on purpose to without break */    
    case SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE_AS_BLOCKED:
        if (e_last_tv_mode == TV_MODE_TYPE_PIP && e_tv_win_id == TV_WIN_ID_SUB) {
            nav_request_context_switch(
                        _pop_handle_update_pip_sub_win_ntfy, 
                        NULL, 
                        NULL, 
                        NULL
                        );            
        }
        return;
    default:
        return;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_init
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    POP_T* pt_this = &t_g_pop;
    INT32  i4_ret;

    pt_this->ui1_swap_selecting_tv_win_bits         = 0;
    pt_this->ui1_swap_stopping_tv_win_bits          = 0;
    pt_this->t_audios[TV_WIN_ID_MAIN].e_type        = SCDB_REC_TYPE_UNKNOWN;
    pt_this->t_audios[TV_WIN_ID_SUB].e_type         = SCDB_REC_TYPE_UNKNOWN;
    pt_this->t_videos[TV_WIN_ID_MAIN].e_status      = POP_VIDEO_STATUS_UNKNOWN;
    pt_this->t_videos[TV_WIN_ID_SUB].e_status       = POP_VIDEO_STATUS_UNKNOWN;
    pt_this->ui1_src_ids[TV_WIN_ID_MAIN]            = INVALID_INPUT_SRC_ID;
    pt_this->ui1_src_ids[TV_WIN_ID_SUB]             = INVALID_INPUT_SRC_ID;
    pt_this->h_hide_timer                           = NULL_HANDLE;
    pt_this->h_swap_timer                           = NULL_HANDLE;
    pt_this->ui4_hide_timeout                       = POP_FRAMES_TIMEOUT;
    pt_this->b_frames_shown                         = FALSE;
    pt_this->e_audio_focus_id                       = TV_WIN_ID_LAST_VALID_ENTRY;
    pt_this->b_under_ex_ctrl                        = FALSE;
    pt_this->e_last_tv_mode                         = TV_MODE_TYPE_NORMAL;
    pt_this->e_tv_mode_in_changing                  = TV_MODE_TYPE_LAST_VALID_ENTRY;
    pt_this->b_audio_focus_changing                 = FALSE;
    pt_this->ui2_misc_cfg_nfy                       = APP_CFG_NOTIFY_NULL_ID;
    pt_this->ui2_pip_pop_cfg_nfy                    = APP_CFG_NOTIFY_NULL_ID;
    pt_this->ui2_gui_lang_cfg_nfy                   = APP_CFG_NOTIFY_NULL_ID;
    pt_this->h_main_svctx                           = NULL_HANDLE;
    pt_this->h_sub_svctx                            = NULL_HANDLE;
    pt_this->b_using_pip_audio_strm_filter          = FALSE;
    pt_this->h_lock                                 = NULL_HANDLE;
    pt_this->b_might_single_rf_scan[TV_WIN_ID_MAIN] = FALSE;
    pt_this->b_might_single_rf_scan[TV_WIN_ID_SUB]  = FALSE;
    
    _pop_update_audio_focus_icl (TV_WIN_ID_LAST_VALID_ENTRY);
    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_create(&(pt_this->h_swap_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_sema_create(
                    &pt_this->h_lock,
                    X_SEMA_TYPE_MUTEX,
                    X_SEMA_STATE_UNLOCK
                    );
    if(i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_open(
                    SVCTX_NAME_MAIN,
                    _pop_svctx_nfy_fct,
                    NULL,
                    &pt_this->h_main_svctx
                    );
    if(i4_ret != TVR_OK){
        return NAVR_FAIL;
    }

    i4_ret = a_tv_open(
                    SVCTX_NAME_SUB,
                    _pop_svctx_nfy_fct,
                    NULL,
                    &pt_this->h_sub_svctx
                    );
    if(i4_ret != TVR_OK){
        return NAVR_FAIL;
    }

    i4_ret = nav_get_ui_canvas_size(
                    &pt_this->ui4_canvas_width,
                    &pt_this->ui4_canvas_height
                    );
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }

    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_this->ui4_canvas_width,
                    pt_this->ui4_canvas_height
                    );
    if(i4_ret != NAVR_OK){
        return NAVR_FAIL;
    }

    i4_ret = a_cfg_notify_reg(
                    APP_CFG_GRPID_VIDEO,
                    pt_this,
                    _pop_cfg_nfy_fct,
                    &pt_this->ui2_misc_cfg_nfy
                    );
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_cfg_notify_reg(
                    APP_CFG_GRPID_NAV,
                    pt_this,
                    _pop_cfg_nfy_fct,
                    &pt_this->ui2_nav_cfg_nfy
                    );
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_cfg_notify_reg(
                    APP_CFG_GRPID_PIP_POP,
                    pt_this,
                    _pop_cfg_nfy_fct,
                    &pt_this->ui2_pip_pop_cfg_nfy
                    );
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }
#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
    i4_ret = a_cfg_notify_reg(
                    APP_CFG_GRPID_GUI_LANG,
                    pt_this,
                    _pop_cfg_nfy_fct,
                    &pt_this->ui2_gui_lang_cfg_nfy
                    );
    if (i4_ret != APP_CFGR_OK) {
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_deinit(
                    VOID
                    )
{
    POP_T* pt_this = &t_g_pop;

    _pop_hide();

    if (pt_this->ui2_nav_cfg_nfy != APP_CFG_NOTIFY_NULL_ID) {
        a_cfg_notify_unreg(pt_this->ui2_nav_cfg_nfy);
    }

    if (pt_this->ui2_misc_cfg_nfy != APP_CFG_NOTIFY_NULL_ID) {
        a_cfg_notify_unreg(pt_this->ui2_misc_cfg_nfy);
    }

    if (pt_this->ui2_pip_pop_cfg_nfy != APP_CFG_NOTIFY_NULL_ID) {
        a_cfg_notify_unreg(pt_this->ui2_pip_pop_cfg_nfy);
    }

#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
    if (pt_this->ui2_gui_lang_cfg_nfy != APP_CFG_NOTIFY_NULL_ID) {
        a_cfg_notify_unreg(pt_this->ui2_gui_lang_cfg_nfy);
    }
#endif

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    if (c_handle_valid(pt_this->h_swap_timer) == TRUE) {
        c_timer_delete(pt_this->h_swap_timer);
    }

    if (c_handle_valid(pt_this->h_lock) == TRUE) {
        c_sema_delete(pt_this->h_lock);
    }

    a_tv_close(pt_this->h_main_svctx);
    a_tv_close(pt_this->h_sub_svctx);

    pt_this->t_view_hdlr.pf_deinit();

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->h_swap_timer = NULL_HANDLE;
    pt_this->h_lock       = NULL_HANDLE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _pop_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    POP_T* pt_this = &t_g_pop;

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI) == TRUE) {
        return FALSE;
    }

    return pt_this->t_view_hdlr.pf_is_key_handler(
                    ui4_key_code
                    );
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_key_monitor_nty
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_key_monitor_nty (
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2,
                    VOID*                       pv_tag
                    )
{
    POP_T* pt_this = &t_g_pop;
    INT32  i4_ret = NAVR_OK;
    TV_MODE_T e_mode;

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
        nav_get_tv_mode (&e_mode);
        if ((e_mode == TV_MODE_TYPE_PIP) || (e_mode == TV_MODE_TYPE_POP))
        {
            i4_ret = _pop_show_osd_frames(pt_this, SHOW_OSD_FRAMES);
        }
        if (i4_ret == NAVR_OK) {
            if (pt_this->t_view_hdlr.pf_is_key_handler((UINT32)pv_param1) == FALSE) {
                nav_rcu_key_handler((UINT32)pv_param1);
            }
            return NAVR_DO_NOT_CONTINUE;
        }
        break;
    default:
        break;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_chk_active
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static BOOL _pop_chk_active(UINT32 ui4_key_code)
{
    INT32   i4_ret; 
    SIZE_T  z_size;
    UINT32  ui4_disable_mask = 0;
    ICL_PIP_POP_REFUSED_INFO_T  t_pip_pop_info;
	
    z_size = ICL_RECID_PIP_POP_DISABLE_MASK_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_PIP_POP, ICL_RECID_PIP_POP_DISABLE_MASK),
                       &ui4_disable_mask,
                       &z_size);
    if(i4_ret != ICLR_OK)
    {
		return TRUE;
    }

	if (ui4_disable_mask == 0)
	{
		return TRUE;
	}

	c_memset(&t_pip_pop_info, 0 , sizeof(ICL_PIP_POP_REFUSED_INFO_T));
	t_pip_pop_info.ui4_refused_key_code = ui4_key_code;

    z_size = ICL_RECID_PIP_POP_REFUSED_INFO_SIZE;
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_PIP_POP, ICL_RECID_PIP_POP_REFUSED_INFO),
              &t_pip_pop_info,
              z_size);
 
    return  FALSE;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _pop_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    POP_T*      pt_this = &t_g_pop;
    TV_WIN_ID_T e_focus_id;
    TV_WIN_ID_T e_blur_id;
    INT32       i4_ret;

    if (_pop_chk_active(ui4_key_code) == FALSE)
	{
		return NAVR_NO_ACTION;
	}

    i4_ret = nav_register_key_monitor_nty_fct(
                    NAV_COMP_ID_PIP_POP,
                    _pop_key_monitor_nty,
                    pt_this
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = nav_get_focus_id(&e_focus_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    e_blur_id = NAV_GET_BLUR_ID(e_focus_id);

    i4_ret = pt_this->t_view_hdlr.pf_activate(e_focus_id, e_blur_id, ui4_key_code);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_update_status_as_power_off
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_update_status_as_power_off(
                    VOID
                    )
{
#ifndef APP_NAV_RESTORE_PIP_POP_AFTER_POWER_ON
    ISL_REC_T   t_focus_isl_rec = {0};
    ISL_REC_T   t_blur_isl_rec  = {0};
    TV_WIN_ID_T e_focus_id;
    TV_WIN_ID_T e_blur_id;
    INT32       i4_ret;

    i4_ret = nav_get_focus_id(&e_focus_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    e_blur_id = NAV_GET_BLUR_ID(e_focus_id);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_focus_isl_rec);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_get_isl_rec_by_win_id(e_blur_id, &t_blur_isl_rec);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_set_input_src_id(TV_WIN_ID_MAIN, t_focus_isl_rec.ui1_id);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_set_input_src_id(TV_WIN_ID_SUB, t_blur_isl_rec.ui1_id);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = nav_set_focus_id(TV_WIN_ID_MAIN, TRUE);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_update_status_as_power_on
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_update_status_as_power_on(
                    VOID
                    )
{
#ifndef APP_NAV_RESTORE_PIP_POP_AFTER_POWER_ON
    INT32 i4_ret;

    _pop_set_last_tv_mode(TV_MODE_TYPE_NORMAL);

    i4_ret = nav_before_tv_mode_change(TV_MODE_TYPE_NORMAL);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = nav_set_tv_mode(TV_MODE_TYPE_NORMAL);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = nav_set_focus_id(TV_WIN_ID_MAIN, TRUE);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#else
    _pop_set_last_tv_mode(TV_MODE_TYPE_LAST_VALID_ENTRY);
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_need_resize_disp_region
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _pop_need_resize_disp_region(
                    TV_WIN_ID_T                 e_tv_win_id
                    )
{

#ifndef APP_NAV_PIP_POP_NOT_RESIZE_DISP_REGION
    return TRUE;
#else
    HANDLE_T        h_svctx;
    SIGNAL_STATUS_T e_status;
    SIZE_T          z_size;
    INT32           i4_ret;

    i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return FALSE;
    }

    z_size = sizeof(SIGNAL_STATUS_T);
    i4_ret = c_svctx_get(
                    h_svctx,
                    SVCTX_COMMON_GET_SIGNAL_STATUS,
                    (VOID*)&e_status,
                    &z_size
                    );
    if (i4_ret != SVCTXR_OK) {
        return FALSE;
    }

    if (e_status == SIGNAL_STATUS_UNKNOWN
            || e_status == SIGNAL_STATUS_LOSS
            || nav_get_locked_status(e_tv_win_id) != LOCKED_STATUS_NONE) {
        return TRUE;
    } else {
        return FALSE;
    }
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_update_win_osd_rect
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_update_win_osd_rect(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    TV_WIN_ID_T                 e_tv_win_id,
                    VSH_REGION_INFO_T*          pt_video_region,
                    BOOL                        b_repaint
                    )
{
    GL_RECT_T t_win_rect = {0};
    INT32     i4_ret;

    _pop_get_win_rect(pt_this, e_tv_mode, pt_video_region, &t_win_rect);

    i4_ret = pt_this->t_view_hdlr.pf_update_win_rect(
                    e_tv_win_id,
                    e_tv_mode,
                    &t_win_rect,
                    b_repaint
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_select_tv_window
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_select_tv_window(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    TV_WIN_ID_T                 e_tv_win_id,
                    ISL_REC_T*                  pt_isl_rec,
                    SNK_DESC_T*                 pt_snk_desc,
                    BOOL                        b_enable_blank, /* Determine whether to enable blank or not. */
                    BOOL                        b_repaint
                    )
{
    BOOL  b_is_same_src = FALSE;
    BOOL  b_empty_svl   = nav_is_svl_empty(e_tv_win_id);
    INT32 i4_ret        = NAVR_OK;

    i4_ret = nav_is_crnt_input_src(e_tv_win_id, pt_isl_rec, &b_is_same_src);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (nav_is_signal_loss(e_tv_win_id) == TRUE
            || nav_get_locked_status(e_tv_win_id) != LOCKED_STATUS_NONE
            || b_empty_svl == TRUE
            || nav_get_video_timing_type(e_tv_win_id) == VSH_SRC_TIMING_NOT_SUPPORT) {
        if (e_tv_mode == TV_MODE_TYPE_NORMAL) {
            if (b_empty_svl == TRUE) {
                  /* force to select svc to triggert to send notification EMPTY SVL
                   * to other component - CR DTV000105124
                   * -- exit pip/pop to normal
                   */
                 b_is_same_src = FALSE;
            }
            if (b_enable_blank)
            {
                _pop_enable_default_video_plane_mode(e_tv_win_id, b_empty_svl == TRUE ? TRUE : FALSE);
            }
        } else {
            if (nav_is_pop_pip_swapping() == TRUE && b_empty_svl == TRUE) {
                b_is_same_src = FALSE;
            }

            if (e_tv_mode == TV_MODE_TYPE_PIP && e_tv_win_id == TV_WIN_ID_MAIN) {
                i4_ret = _pop_view_set_main_video_mute_via_pmx_bg(TRUE);
                if (i4_ret != NAVR_OK) {
                    return NAVR_FAIL;
                }
            }
        }


        if (b_is_same_src == TRUE && b_empty_svl == TRUE) {
            TV_MODE_T e_prev_tv_mode;

            i4_ret = nav_get_tv_mode(&e_prev_tv_mode);
            if (i4_ret == NAVR_OK && e_prev_tv_mode != e_tv_mode) {
                if (e_prev_tv_mode == TV_MODE_TYPE_NORMAL) {
                    /* force to select svc to triggert to send notification EMPTY SVL
                     * to other component - CR DTV000105124
                     * from normal to enter pip/pop
                     */
                    b_is_same_src = FALSE;
                }
            }
        }
    }

    if ((b_empty_svl == FALSE) || (b_is_same_src == FALSE)) {
        if (pt_snk_desc != NULL && pt_snk_desc->pt_disp_region != NULL) {
            i4_ret = _pop_update_win_osd_rect(
                    pt_this,
                    e_tv_mode,
                    e_tv_win_id,
                    pt_snk_desc->pt_disp_region,
                    FALSE
                    );
            if (i4_ret != NAVR_OK) {
                return NAVR_FAIL;
            }
        }

        _pop_show_win_rect_bg(
                    pt_this,
                    e_tv_win_id,
                    e_tv_mode,
                    POP_RECT_BG_CMD_BLACK,
                    b_repaint
                    );

        /*
         *  For CR 138247.
         *  When AP call c_svctx_select_svc (), SVCTX will blank and unblank immediately in 
         *  svctx_set_video_stream_attrs ().
         *  When user keeps to press PIP key, sometimes driver will unblank before SVCTX
         *  unblank, this will cause video blank.
         *  Hence, PIP blank video before selecting SVC to avoid this.
         */
        if (b_enable_blank)
        {
            _pop_enable_default_video_plane_mode(e_tv_win_id, b_empty_svl == TRUE ? TRUE : FALSE);
        }
        i4_ret = nav_change_av_inp_by_rec(
                    e_tv_win_id,
                    pt_isl_rec,
                    pt_snk_desc
                    );
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        return NAVR_OK;
    }

    if (pt_snk_desc != NULL && pt_snk_desc->pt_disp_region != NULL) {
        if (_pop_need_resize_disp_region(e_tv_win_id) == TRUE) {
            i4_ret = nav_set_stream_attr(
                        e_tv_win_id,
                        ST_VIDEO,
                        SM_VSH_SET_TYPE_DISP_REGION,
                        pt_snk_desc->pt_disp_region,
                        sizeof(VSH_REGION_INFO_T)
                        );
            if (i4_ret != NAVR_OK) {
                return NAVR_FAIL;
            }
        }

        i4_ret = _pop_update_win_osd_rect(
                        pt_this,
                        e_tv_mode,
                        e_tv_win_id,
                        pt_snk_desc->pt_disp_region,
                        FALSE
                        );
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = _pop_check_to_show_win_rect_bg (
                        pt_this,
                        e_tv_win_id,
                        e_tv_mode,
                        b_repaint
                        );
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    } else {
        if (e_tv_mode != TV_MODE_TYPE_NORMAL) {
            i4_ret = _pop_check_to_show_win_rect_bg (
                        pt_this,
                        e_tv_win_id,
                        e_tv_mode,
                        TRUE
                        );
            if (i4_ret != NAVR_OK) {
                return NAVR_FAIL;
            }
        }
    }

    if (pt_snk_desc != NULL && pt_snk_desc->pt_video_plane_order != NULL) {
        i4_ret = nav_set_stream_attr(
                        e_tv_win_id,
                        ST_VIDEO,
                        SM_VSH_SET_TYPE_PLANE_ORDER,
                        pt_snk_desc->pt_video_plane_order,
                        sizeof(VSH_SET_PLANE_ORDER_INFO_T)
                        );
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}
/* This is for CR 77346. */
#if 0
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_clean_tv_wins_audio_stream_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_clean_tv_wins_audio_stream_mode(
                    VOID
                    )
{
    UINT32 ui4_stream_mode = 0;

    /* set blue win to have NOT audio stream */
    nav_get_stream_mode(TV_WIN_ID_MAIN, &ui4_stream_mode);
    nav_set_stream_mode(TV_WIN_ID_MAIN, ui4_stream_mode & ~ST_MASK_AUDIO);

    /* set focus win to have audio stream */
    nav_get_stream_mode(TV_WIN_ID_SUB, &ui4_stream_mode);
    nav_set_stream_mode(TV_WIN_ID_SUB, ui4_stream_mode & ~ST_MASK_AUDIO);

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_swap_post_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_swap_post_handler(
                    POP_T*                      pt_this
                    )
{
    ISL_REC_T   t_main_isl_rec = {0};
    ISL_REC_T   t_sub_isl_rec  = {0};
    TV_WIN_ID_T e_focus_id;
    TV_MODE_T   e_tv_mode;
    INT32       i4_ret;

    do {
        i4_ret = nav_get_tv_mode(&e_tv_mode);
        if (i4_ret != NAVR_OK) {
            break;
        }

        if (e_tv_mode == TV_MODE_TYPE_NORMAL) {
            i4_ret = NAVR_OK;
            break;
        }
        
        _pop_stop_swap_timer(pt_this);
        
        pt_this->ui1_swap_selecting_tv_win_bits = 0;
        
        i4_ret = nav_get_focus_id(&e_focus_id);
        if (i4_ret != NAVR_OK) {
            break;
        }
        
        i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_main_isl_rec);
        if (i4_ret != TVR_OK) {
            break;
        }
        
        i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_SUB, &t_sub_isl_rec);
        if (i4_ret != TVR_OK) {
            break;
        }
        
        if (nav_get_locked_status(TV_WIN_ID_MAIN) != LOCKED_STATUS_INP_SRC_LOCKED) {
            /* LOCKED_STATUS_INP_SRC_LOCKED is known before the _pop_swap_post_handler() */
            pt_this->ui1_swap_selecting_tv_win_bits |= MAKE_BIT_MASK_8(TV_WIN_ID_MAIN);
        }
        
        if (nav_get_locked_status(TV_WIN_ID_SUB) != LOCKED_STATUS_INP_SRC_LOCKED) {
            /* LOCKED_STATUS_INP_SRC_LOCKED is known before the _pop_swap_post_handler() */
            pt_this->ui1_swap_selecting_tv_win_bits |= MAKE_BIT_MASK_8(TV_WIN_ID_SUB);
        }
        
        /* remove the start SWAP request  
         * nav_set_pop_pip_swapping(TRUE);
         */
        
        /* This is for CR 77346. */
        /* set stream mode to "no audio" to avoid AV not sync issue */
        //_pop_clean_tv_wins_audio_stream_mode();
        _pop_force_audio_stream_mode (pt_this->e_audio_focus_id);

        nav_cancel_delay_change(TV_WIN_ID_MAIN);
        i4_ret = _pop_select_tv_window(
                        pt_this,
                        e_tv_mode,
                        TV_WIN_ID_MAIN,
                        &t_main_isl_rec,
                        NULL,
                        TRUE,
                        FALSE
                        );
        if (i4_ret != NAVR_OK) {
            pt_this->ui1_swap_selecting_tv_win_bits &= ~MAKE_BIT_MASK_8(TV_WIN_ID_MAIN);
        } else {
            if (nav_is_svl_empty(TV_WIN_ID_MAIN) == TRUE) {
                pt_this->ui1_swap_selecting_tv_win_bits &= ~MAKE_BIT_MASK_8(TV_WIN_ID_MAIN);
            }
        }
        
        nav_cancel_delay_change(TV_WIN_ID_SUB);
        i4_ret = _pop_select_tv_window(
                        pt_this,
                        e_tv_mode,
                        TV_WIN_ID_SUB,
                        &t_sub_isl_rec,
                        NULL,
                        TRUE,
                        FALSE
                        );
        if (i4_ret != NAVR_OK) {
            pt_this->ui1_swap_selecting_tv_win_bits &= ~MAKE_BIT_MASK_8(TV_WIN_ID_SUB);
        } else {
            if (nav_is_svl_empty(TV_WIN_ID_SUB) == TRUE) {
                pt_this->ui1_swap_selecting_tv_win_bits &= ~MAKE_BIT_MASK_8(TV_WIN_ID_SUB);
            }
        }

        /* Unmute video. This is for CR 77346. */
        i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, TRUE);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        
        i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, TRUE);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        pt_this->t_view_hdlr.pf_show();
        
        _pop_update_tv_wins_audio_stream_mode(pt_this->e_audio_focus_id, NAV_GET_BLUR_ID(pt_this->e_audio_focus_id));
    } while (0);
    
    nav_set_pop_pip_swapping(FALSE);

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_normal_mode_post_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_normal_mode_post_handler(
                    POP_T*                      pt_this
                    )
{
    INT32 i4_ret = NAVR_OK;

    if (pt_this->e_audio_focus_id == TV_WIN_ID_SUB) {
        _pop_update_tv_wins_audio_stream_mode(TV_WIN_ID_MAIN, TV_WIN_ID_SUB);
        i4_ret = _pop_select_audio_stream_for_focus_change(pt_this, TV_WIN_ID_MAIN);
    }

    if (i4_ret == NAVR_OK || i4_ret == NAVR_NOT_EXIST) {
        pt_this->e_audio_focus_id = TV_WIN_ID_LAST_VALID_ENTRY;
        _pop_update_audio_focus_icl (TV_WIN_ID_LAST_VALID_ENTRY);
    }

    _pop_stop_timer(pt_this);
    i4_ret = nav_unregister_key_monitor_nty_fct(NAV_COMP_ID_PIP_POP);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    _pop_show_win_rect_bg(
                    pt_this,
                    TV_WIN_ID_MAIN,
                    TV_MODE_TYPE_NORMAL,
                    POP_RECT_BG_CMD_HIDE,
                    FALSE
                    );
    _pop_show_win_rect_bg(
                    pt_this,
                    TV_WIN_ID_SUB,
                    TV_MODE_TYPE_NORMAL,
                    POP_RECT_BG_CMD_HIDE,
                    FALSE
                    );

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_handle_rect_bg_per_av_status
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_handle_rect_bg_per_av_status(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode
                    )
{
    switch(nav_get_av_status(e_tv_win_id)){
    case NAV_AV_STATUS_AUDIO_ONLY:
    case NAV_AV_STATUS_NO_AUDIO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_AUDIO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_AUDIO_NO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_VIDEO_CLEAR_AUDIO:
    case NAV_AV_STATUS_SCRAMBLED_VIDEO_NO_AUDIO:
        _pop_show_win_rect_bg(
                    pt_this,
                    e_tv_win_id,
                    e_tv_mode,
                    POP_RECT_BG_CMD_SHOW,
                    TRUE
                    );
        break;
    case NAV_AV_STATUS_VIDEO_ONLY:
    case NAV_AV_STATUS_AUDIO_VIDEO:
    case NAV_AV_STATUS_SCRAMBLED_AUDIO_CLEAR_VIDEO:
        _pop_show_win_rect_bg(
                    pt_this,
                    e_tv_win_id,
                    e_tv_mode,
                    POP_RECT_BG_CMD_HIDE,
                    TRUE
                    );
        if (pt_this->ui1_swap_selecting_tv_win_bits == 0) {
            pop_set_disable_audio_focus (FALSE);
            _pop_enable_default_video_plane_mode(e_tv_win_id, TRUE);
        }
        break;
    case NAV_AV_STATUS_UNKNOWN:
        /* when main is audio source, and focus is sub. Main svctx's av status will
         * be unknown. And don't remove the OSD frame as in PIP,
         * this main's OSD frame will cover sub's video
         */
        if (e_tv_mode == TV_MODE_TYPE_PIP
                && e_tv_win_id == TV_WIN_ID_MAIN
                && pt_this->e_audio_focus_id == TV_WIN_ID_SUB) {
            _pop_show_win_rect_bg(
                    pt_this,
                    e_tv_win_id,
                    e_tv_mode,
                    POP_RECT_BG_CMD_HIDE,
                    TRUE
                    );
        }
        break;
    default:
        break;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_change_win_region
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_change_win_region(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    TV_WIN_ID_T                 e_tv_win_id,
                    VSH_REGION_INFO_T*          pt_video_region,
                    BOOL                        b_repaint
                    )
{
    INT32 i4_ret;

#ifdef APP_NAV_POP_MOVE_OSD_FIRST
    /*
     *  Move the music note first and then the video window.
     *  This is for the request from MW Vincent to reduce the transit state
     *  when moving the PIP window.
     */
    i4_ret = _pop_update_win_osd_rect(
                    pt_this,
                    e_tv_mode,
                    e_tv_win_id,
                    pt_video_region,
                    b_repaint
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif

    if (_pop_need_resize_disp_region(e_tv_win_id) == TRUE) {
        nav_set_stream_attr(
                    e_tv_win_id,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_DISP_REGION,
                    pt_video_region,
                    sizeof(VSH_REGION_INFO_T)
                    );
    }

    if (e_tv_mode == TV_MODE_TYPE_PIP && e_tv_win_id == TV_WIN_ID_SUB) {
        SIZE_T z_size = sizeof(VSH_REGION_INFO_T);
        
        _pop_update_pip_sub_screen_mode(nav_is_video_content_playing(TV_WIN_ID_SUB));
        
        nav_get_stream_attr(
                    e_tv_win_id,
                    ST_VIDEO,
                    SM_VSH_GET_TYPE_FINAL_DISP_REGION,
                    pt_video_region,
                    &z_size
                    );
    }

#ifndef APP_NAV_POP_MOVE_OSD_FIRST
    i4_ret = _pop_update_win_osd_rect(
                    pt_this,
                    e_tv_mode,
                    e_tv_win_id,
                    pt_video_region,
                    b_repaint
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_update_pip_sub_win_rect_to_final
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_update_pip_sub_win_rect_to_final(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode,
                    TV_WIN_ID_T                 e_tv_win_id
                    )
{
    VSH_REGION_INFO_T t_video_region;
    INT32             i4_ret;

    i4_ret = pop_get_pip_sub_region_info(
                    WIN_POS_DIR_CRNT,
                    WIN_SIZE_DIR_CRNT,
                    &t_video_region
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = _pop_change_win_region(
                    pt_this,
                    e_tv_mode,
                    e_tv_win_id,
                    &t_video_region,
                    TRUE
                    );
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_handle_no_video_related_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_handle_no_video_related_msg(
                    POP_T*                      pt_this,
                    NAV_UI_MSG_ID_T             e_msg_id,
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode
                    )
{
    if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP
            && pt_this->e_tv_mode_in_changing != TV_MODE_TYPE_PIP
            && pt_this->e_tv_mode_in_changing != TV_MODE_TYPE_POP) {
        return NAVR_NO_ACTION;
    }

    if (pt_this->e_tv_mode_in_changing == TV_MODE_TYPE_PIP
            || pt_this->e_tv_mode_in_changing == TV_MODE_TYPE_POP) {
        e_tv_mode = pt_this->e_tv_mode_in_changing;
    }

    _pop_show_win_rect_bg(
                    pt_this,
                    e_tv_win_id,
                    e_tv_mode,
                    POP_RECT_BG_CMD_SHOW,
                    TRUE
                    );
    if (e_msg_id == NAV_UI_MSG_NO_SIGNAL) {
        _pop_select_audio_stream_for_focus_change(pt_this, pt_this->e_audio_focus_id);
    } else if (e_msg_id == NAV_UI_MSG_EMPTY_SVL) {
        if (e_tv_mode == TV_MODE_TYPE_PIP && e_tv_win_id == TV_WIN_ID_MAIN) {
            _pop_view_set_main_video_mute_via_pmx_bg(TRUE);
        }
    }

    _pop_enable_default_video_plane_mode(e_tv_win_id, FALSE);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_restore_default_strm_filter
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_restore_default_strm_filter(
                    POP_T*                      pt_this
                    )
{
    INT32 i4_ret = NAVR_OK;

    if (pt_this->b_using_pip_audio_strm_filter == FALSE) {
        return NAVR_OK;
    }

    pt_this->b_using_pip_audio_strm_filter = FALSE;

    /* restore to default one */
    i4_ret = nav_restore_default_strm_filter(TV_WIN_ID_MAIN, ST_AUDIO);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    /* restore to default one */
    i4_ret = nav_restore_default_strm_filter(TV_WIN_ID_SUB, ST_AUDIO);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_check_to_enable_default_video_plane_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _pop_check_to_enable_default_video_plane_mode(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id
                    )
{
    if (pt_this->ui1_swap_selecting_tv_win_bits > 0) {
        pt_this->ui1_swap_selecting_tv_win_bits &= ~MAKE_BIT_MASK_8(e_tv_win_id);
    
        if (pt_this->ui1_swap_selecting_tv_win_bits == 0) {
            pop_set_disable_audio_focus (FALSE);
            _pop_select_audio_stream(pt_this, pt_this->e_audio_focus_id, FALSE);
            _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, TRUE);
            _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, TRUE);
        }
    } else {
        _pop_select_audio_stream(pt_this, pt_this->e_audio_focus_id, FALSE);
        _pop_enable_default_video_plane_mode(e_tv_win_id, TRUE);
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_check_to_play_audio_stream_for_focus_window_as_no_video
 * Description
 *      This API is used to check to play audio stream in focus window
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _pop_check_to_play_audio_stream_for_focus_window_as_no_video(
                    POP_T*                      pt_this,
                    TV_WIN_ID_T                 e_tv_win_id
                    )
{
    if (e_tv_win_id != pt_this->e_audio_focus_id
            || nav_is_audio_comp_playing(pt_this->e_audio_focus_id) == TRUE
            || pt_this->t_videos[e_tv_win_id].e_status != POP_VIDEO_STATUS_NOT_VISIBLE) {
        return;
    }
    
    _pop_select_audio_stream(pt_this, pt_this->e_audio_focus_id, FALSE);
 }
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    POP_T*          pt_this  = &t_g_pop;
    NAV_UI_MSG_ID_T e_msg_id = pt_ui_msg->e_id;
    TV_MODE_T       e_tv_mode;
    TV_MODE_T       e_last_tv_mode;
    INT32           i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    if (e_msg_id == NAV_UI_MSG_AS_APP_PAUSED) {
        /* handle the following message when Navigator in paused if in PIP/POP */
        switch (pt_ui_msg->e_id_as_paused) {
        case NAV_UI_MSG_NO_SIGNAL:
        case NAV_UI_MSG_WITH_SIGNAL:
#ifdef APP_DVBT_SUPPORT
            if ((e_tv_mode == TV_MODE_TYPE_PIP || e_tv_mode == TV_MODE_TYPE_POP)
                    && nav_get_src_type(pt_ui_msg->e_tv_win_id) == INP_SRC_TYPE_TV
                    && nav_is_channel_scan_active() == TRUE
                    && nav_is_active() == FALSE) {
                /* dirty trick as without video plane as background in scanning */
                if (pt_ui_msg->e_id_as_paused == NAV_UI_MSG_NO_SIGNAL 
                        && pt_ui_msg->e_tv_win_id == TV_WIN_ID_SUB
                        && e_tv_mode == TV_MODE_TYPE_PIP) {
                    _pop_update_pip_sub_win_rect_for_aspect_ratio(pt_this);
                }
                
                _pop_show_win_rect_bg(
                        pt_this,
                        pt_ui_msg->e_tv_win_id,
                        e_tv_mode,
                        POP_RECT_BG_CMD_HIDE,
                        TRUE
                        );
                return NAVR_OK;
            }
#endif
            e_msg_id = pt_ui_msg->e_id_as_paused;
            break;
        case NAV_UI_MSG_LOCKED_INP:
        case NAV_UI_MSG_LOCKED_CH:
        case NAV_UI_MSG_LOCKED_PROG:
        case NAV_UI_MSG_EMPTY_SVL:
        case NAV_UI_MSG_UNLOCKED:
        case NAV_UI_MSG_BEFORE_TV_MODE_CHANGE:
        case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
            if (nav_is_channel_scan_active() == TRUE
                    && nav_is_active() == FALSE) {
                return NAVR_OK;
            }
            e_msg_id = pt_ui_msg->e_id_as_paused;
            break;
        case NAV_UI_MSG_CA:
        case NAV_UI_MSG_AV_STATUS_NOTIFY:
        case NAV_UI_MSG_AFTER_SVC_CHANGE:
        case NAV_UI_MSG_STREAM_NOTIFY:
        case NAV_UI_MSG_SVC_STOPPED:
        case NAV_UI_MSG_SCDB_UPDATE:
            e_msg_id = pt_ui_msg->e_id_as_paused;
            break;
        default:
            return NAVR_OK;
        }
    }

    switch(e_msg_id) {
    case NAV_UI_MSG_CA:
      {
        STREAM_TYPE_T e_strm_type = (STREAM_TYPE_T)(UINT32)pv_arg1;
        UINT32        ui4_scrambled_strm = 0;
    
        if (nav_get_locked_status(pt_ui_msg->e_tv_win_id) == LOCKED_STATUS_INP_SRC_LOCKED)
        {
            break;
        }
    
        i4_ret = nav_get_ca_status(pt_ui_msg->e_tv_win_id, &ui4_scrambled_strm);
        if (i4_ret != NAVR_OK) {
            break;
        }
    
        switch(e_strm_type) {
        case ST_VIDEO:
            /*
             *  If TV detects that the video is scrambled in this channel, force to 
             *  select the audio to make "Scrambled Audio" on banner can be displayed
             *  ASAP.
             */
            if ((ui4_scrambled_strm & MAKE_BIT_MASK_32(e_strm_type)) > 0) {
                TV_WIN_ID_T e_focus_win;
                
                nav_get_focus_id (&e_focus_win);
                if (pt_ui_msg->e_tv_win_id == e_focus_win)
                {
                    _pop_select_audio_stream(pt_this, pt_ui_msg->e_tv_win_id, TRUE);
                }
                _pop_check_to_enable_default_video_plane_mode(
                        pt_this,
                        pt_ui_msg->e_tv_win_id
                        );
            }
            break;
        default:
            break;
        }
        break;
      }
    case NAV_UI_MSG_SCDB_UPDATE:
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }

        _pop_check_to_play_audio_stream_for_focus_window_as_no_video(
                    pt_this,
                    pt_ui_msg->e_tv_win_id
                    );
        break;
    case NAV_UI_MSG_STREAM_NOTIFY:
      {
        NAV_STREAM_NOTIFY_DATA_T* pt_data = (NAV_STREAM_NOTIFY_DATA_T*)pv_arg1;

        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }

        switch (pt_data->e_strm_type) {
        case ST_AUDIO:
            if (pt_data->e_type == NAV_SNT_STREAM_STOPPED) {
                /* focus change - select focus's audio */
                _pop_select_audio_stream_for_focus_change(pt_this, pt_this->e_audio_focus_id);
            }
            else if (pt_data->e_type == NAV_SNT_STREAM_STARTED)
            {
                /* Update buffered audio stream data. */
                if (e_tv_mode == TV_MODE_TYPE_PIP && pt_ui_msg->e_tv_win_id == TV_WIN_ID_SUB)
                {
                    _pop_update_audio_steam_data(pt_this);
                }
            }
            break;
        case ST_VIDEO:
            switch(pt_data->e_type) {
#if 0
            case NAV_SNT_STREAM_STARTED:
                if (e_tv_mode == TV_MODE_TYPE_PIP && pt_ui_msg->e_tv_win_id == TV_WIN_ID_SUB) {
                    /* update SUB's frame size to handle the video show before video format update notification */
                    _pop_update_pip_sub_win_rect_for_aspect_ratio(pt_this);
                }
                break;
#endif
            case NAV_SNT_STREAM_UPDATED:
                if (pt_ui_msg->e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY) {
                    break;
                }
                pt_this->t_videos[pt_ui_msg->e_tv_win_id].e_status = POP_VIDEO_STATUS_VISIBLE;
                if (e_tv_mode == TV_MODE_TYPE_PIP && pt_ui_msg->e_tv_win_id == TV_WIN_ID_SUB) {
                    /* aspect ratio change - update SUB's frame size */
                    _pop_update_pip_sub_win_rect_for_aspect_ratio(pt_this);
                }

                _pop_show_win_rect_bg(
                        pt_this,
                        pt_ui_msg->e_tv_win_id,
                        e_tv_mode,
                        POP_RECT_BG_CMD_HIDE,
                        TRUE
                        );
                
                _pop_check_to_enable_default_video_plane_mode(
                        pt_this,
                        pt_ui_msg->e_tv_win_id
                        );

                _pop_select_audio_stream(pt_this, pt_this->e_audio_focus_id, FALSE);
                break;
            case NAV_SNT_STREAM_NOT_FOUND:
                if (pt_ui_msg->e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY) {
                    break;
                }
                pt_this->t_videos[pt_ui_msg->e_tv_win_id].e_status = POP_VIDEO_STATUS_NOT_VISIBLE;
                _pop_check_to_play_audio_stream_for_focus_window_as_no_video(
                        pt_this,
                        pt_ui_msg->e_tv_win_id
                        );
                _pop_check_to_enable_default_video_plane_mode(
                                        pt_this,
                                        pt_ui_msg->e_tv_win_id
                                        );
                break;
            case NAV_SNT_STREAM_NOT_SUPPORT:
                if (pt_ui_msg->e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY) {
                    break;
                }
                pt_this->t_videos[pt_ui_msg->e_tv_win_id].e_status = POP_VIDEO_STATUS_NOT_VISIBLE;
                _pop_handle_no_video_related_msg(
                        pt_this,
                        e_msg_id,
                        pt_ui_msg->e_tv_win_id,
                        e_tv_mode
                        );
                _pop_check_to_enable_default_video_plane_mode(
                                        pt_this,
                                        pt_ui_msg->e_tv_win_id
                                        );
                break;
            default:
                break;
            }
            break;
        default:
            break;
        }
        break;
      }
    case NAV_UI_MSG_AFTER_ASPECT_RATIO_CHANGE:
        if (e_tv_mode == TV_MODE_TYPE_PIP && pt_ui_msg->e_tv_win_id == TV_WIN_ID_SUB) {
            /* aspect ratio change - update SUB's frame size */
            _pop_update_pip_sub_win_rect_to_final(
                        pt_this,
                        e_tv_mode,
                        pt_ui_msg->e_tv_win_id
                        );
        }
        break;
    case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        pt_this->b_under_ex_ctrl = FALSE;

        if (pt_this->e_tv_mode_in_changing != TV_MODE_TYPE_LAST_VALID_ENTRY) {
            e_tv_mode = pt_this->e_tv_mode_in_changing;
        }

        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }
        
        if (pt_ui_msg->e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY) {
            break;
        }
        
        pt_this->t_videos[pt_ui_msg->e_tv_win_id].e_status = POP_VIDEO_STATUS_UNKNOWN;

        /*if (e_tv_mode == TV_MODE_TYPE_PIP && pt_ui_msg->e_tv_win_id == TV_WIN_ID_SUB)*/
        {
            NAV_XNG_SRC_TRGT_T* pt_xng_info = (NAV_XNG_SRC_TRGT_T*)pv_arg1;
            BOOL                b_same = FALSE;
            BOOL                b_trgt_is_blocked = FALSE;

            if (nav_is_running(pt_ui_msg->e_tv_win_id) == TRUE) {
                if (pt_xng_info->e_type == INP_SRC_TYPE_TV) {
                    b_same = nav_is_same_channel(
                                pt_xng_info->u.t_tv.ui2_crnt_svl_id,
                                pt_xng_info->u.t_tv.ui2_crnt_svl_rec_id,
                                pt_xng_info->u.t_tv.ui4_crnt_channel_id,
                                pt_xng_info->u.t_tv.ui2_trgt_svl_id,
                                pt_xng_info->u.t_tv.ui2_trgt_svl_rec_id,
                                pt_xng_info->u.t_tv.ui4_trgt_channel_id
                                );
                } else if (pt_xng_info->e_type == INP_SRC_TYPE_AV) {
                    if (pt_xng_info->u.t_av.ui1_crnt_inp_src_id == pt_xng_info->u.t_av.ui1_trgt_inp_src_id) {
                        b_same = TRUE;
                    } else {
                        b_same = FALSE;
                        b_trgt_is_blocked = a_tv_is_input_source_blocked(pt_xng_info->u.t_av.ui1_trgt_inp_src_id);
                    }
                }
            } else if (nav_is_svl_empty(pt_ui_msg->e_tv_win_id) == TRUE) {
                b_same = TRUE;
            }
            
            if (pt_xng_info->e_type == INP_SRC_TYPE_AV) {
                /* if source type is INP_SRC_TYPE_AV, but if ui1_trgt_inp_src_id is 
                 * still a INP_SRC_TYPE_TV, should not reset the might_single_rf_scan flag
                 */
                ISL_REC_T t_isl_rec;
                
                i4_ret = a_isl_get_rec_by_id(pt_xng_info->u.t_av.ui1_trgt_inp_src_id, &t_isl_rec);
                if (i4_ret == TVR_OK && t_isl_rec.e_src_type != INP_SRC_TYPE_TV) {
                    _pop_set_might_single_rf_scan(pt_ui_msg->e_tv_win_id, FALSE);
                }
            }

            if (b_same == FALSE) {
                /* When change to different channel, reset the buffered audio data. */
                if (pt_xng_info->e_type == INP_SRC_TYPE_TV)
                {
                    _pop_set_audio_stream_type_data(pt_ui_msg->e_tv_win_id, SCDB_REC_TYPE_UNKNOWN);
                }
                _pop_enable_default_video_plane_mode(pt_ui_msg->e_tv_win_id, FALSE);
                /* if next source is input source locked, show the VIDEO mute OSD */
                _pop_show_win_rect_bg(
                            pt_this,
                            pt_ui_msg->e_tv_win_id,
                            e_tv_mode,
                            b_trgt_is_blocked ? POP_RECT_BG_CMD_SHOW : POP_RECT_BG_CMD_BLACK,
                            TRUE
                            );
            }
        }

        /* 
         *  This is for CR 77346. 
         *  Because we do not make A/V can be played together after SWAP,
         *  we don't need to do the followings.
         */
#if 0
        if (pt_this->ui1_swap_selecting_tv_win_bits == 0) {
            TV_WIN_ID_T e_focus_win;

            pop_set_disable_audio_focus (FALSE);
            nav_get_focus_id (&e_focus_win);
            if (e_focus_win == pt_ui_msg->e_tv_win_id)
            {
                _pop_set_audio_stream_type_data(pt_ui_msg->e_tv_win_id, SCDB_REC_TYPE_UNKNOWN);
            }
        } else {
            /*pt_this->ui1_swap_selecting_tv_win_bits &= ~MAKE_BIT_MASK_8(pt_ui_msg->e_tv_win_id);*/
        }
#endif
        break;
    case NAV_UI_MSG_LOCKED_INP:
    case NAV_UI_MSG_LOCKED_CH:
    case NAV_UI_MSG_LOCKED_PROG:
    case NAV_UI_MSG_EMPTY_SVL:
        /* disable the flag to let simulated Blue Mute to be function */
        _pop_set_might_single_rf_scan(pt_ui_msg->e_tv_win_id, FALSE);
        /* on purpose to without break */
    case NAV_UI_MSG_NO_SIGNAL:
        if (pt_ui_msg->e_tv_win_id >= TV_WIN_ID_LAST_VALID_ENTRY) {
            break;
        }
        pt_this->t_videos[pt_ui_msg->e_tv_win_id].e_status = POP_VIDEO_STATUS_NOT_VISIBLE;
        
        if (_pop_handle_no_video_related_msg(
                    pt_this,
                    e_msg_id,
                    pt_ui_msg->e_tv_win_id,
                    e_tv_mode
                    ) != NAVR_OK) {
            break;
        }

        _pop_check_to_enable_default_video_plane_mode(
                    pt_this,
                    pt_ui_msg->e_tv_win_id
                    );
        
        if (pt_this->e_tv_mode_in_changing == TV_MODE_TYPE_LAST_VALID_ENTRY) { /* no changing */
            if (e_tv_mode == TV_MODE_TYPE_PIP && pt_ui_msg->e_tv_win_id == TV_WIN_ID_SUB) {
                /* aspect ratio change - update SUB's frame size */
                _pop_update_pip_sub_win_rect_to_final(
                        pt_this,
                        e_tv_mode,
                        pt_ui_msg->e_tv_win_id
                        );
            }
        }
        break;
    case NAV_UI_MSG_WITH_SIGNAL:
        _pop_set_might_single_rf_scan(pt_ui_msg->e_tv_win_id, FALSE);
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            /* Re-select audio again. */
            if (pt_this->b_resel_audio)
            {
                _pop_select_audio_stream(pt_this, TV_WIN_ID_MAIN, FALSE);
                pt_this->b_resel_audio = FALSE;
            }
            break;
        }

        if (nav_is_digital_tv(pt_ui_msg->e_tv_win_id) == FALSE
                && nav_get_locked_status(pt_ui_msg->e_tv_win_id) == LOCKED_STATUS_NONE) {
            /* Remove the OSD simulated Blue/Black screen early for analog source */
            _pop_show_win_rect_bg(
                        pt_this,
                        pt_ui_msg->e_tv_win_id,
                        e_tv_mode,
                        POP_RECT_BG_CMD_HIDE,
                        TRUE
                        );
        }

        _pop_select_audio_stream_for_focus_change(pt_this, pt_this->e_audio_focus_id);
        break;
    case NAV_UI_MSG_UNLOCKED:
    case NAV_UI_MSG_AFTER_SVC_CHANGE:
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            if (e_msg_id == NAV_UI_MSG_AFTER_SVC_CHANGE) {
                _pop_restore_default_strm_filter(pt_this);
                if (e_tv_mode == TV_MODE_TYPE_NORMAL
                        && pt_this->e_audio_focus_id != TV_WIN_ID_LAST_VALID_ENTRY) {
                    i4_ret = _pop_select_audio_stream_for_focus_change(pt_this, TV_WIN_ID_MAIN);
    				if (i4_ret == NAVR_OK) {
                        pt_this->e_audio_focus_id = TV_WIN_ID_LAST_VALID_ENTRY;
                        _pop_update_audio_focus_icl (TV_WIN_ID_LAST_VALID_ENTRY);
                    }
                }
            }
            break;
        }

        if (e_msg_id == NAV_UI_MSG_AFTER_SVC_CHANGE) {
            _pop_select_audio_stream_for_focus_change(pt_this, pt_this->e_audio_focus_id);
        }

        if (e_tv_mode == TV_MODE_TYPE_PIP
                && pt_ui_msg->e_tv_win_id == TV_WIN_ID_SUB
                && nav_is_digital_tv(TV_WIN_ID_SUB) == FALSE) {
            /* aspect ratio change - update SUB's frame size */
            _pop_update_pip_sub_win_rect_to_final(
                        pt_this,
                        e_tv_mode,
                        pt_ui_msg->e_tv_win_id
                        );
        }

        _pop_handle_rect_bg_per_av_status(
                        pt_this,
                        pt_ui_msg->e_tv_win_id,
                        e_tv_mode
                        );
        break;
    case NAV_UI_MSG_AV_STATUS_NOTIFY:
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }

        _pop_handle_rect_bg_per_av_status(
                        pt_this,
                        pt_ui_msg->e_tv_win_id,
                        e_tv_mode
                        );
        break;
    case NAV_UI_MSG_SVC_STOPPED:
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }

        if (pt_this->ui1_swap_stopping_tv_win_bits == 0) {
            /* service stoped not caused from swap, it could be from Menu - Scan channel
             * so, it needs to use OSD to create a simulated black screen
             */
            _pop_show_win_rect_bg(
                        pt_this,
                        pt_ui_msg->e_tv_win_id,
                        e_tv_mode,
                        POP_RECT_BG_CMD_BLACK,
                        TRUE
                        );
            break;
        }

        pt_this->ui1_swap_stopping_tv_win_bits &= ~MAKE_BIT_MASK_8(pt_ui_msg->e_tv_win_id);

        if (pt_this->ui1_swap_stopping_tv_win_bits == 0) {
            _pop_reset_swap_timer(pt_this);
        }
        break;
    case NAV_UI_MSG_BEFORE_TV_MODE_CHANGE:
        pt_this->e_tv_mode_in_changing = ((NAV_TV_MODE_XNG_INFO_T*)pv_arg1)->e_new_tv_mode;
        break;
    case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        pt_this->e_tv_mode_in_changing = TV_MODE_TYPE_LAST_VALID_ENTRY;
        _pop_handle_tv_mode_change(pt_this, (TV_MODE_T)(UINT32)pv_arg1, FALSE);
        break;
    case NAV_UI_MSG_APP_RESUMED:
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }

        nav_set_bg_svctx_listening(FALSE);

        _pop_show_osd_frames(pt_this, SHOW_OSD_FRAMES);
        
        nav_grab_activation(NAV_COMP_ID_PIP_POP);
        break;
    case NAV_UI_MSG_APP_PAUSING:
    {
        APP_TV_NET_SVC_STATUS e_svc_state = a_tv_net_get_tv_svc_status();

        _pop_reset_might_single_rf_scan();
        
        if (e_svc_state == APP_TV_NET_SVC_STATUS_RESUMED)
        {
            nav_hide_component(NAV_COMP_ID_PIP_POP);
        }
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }
        
        nav_set_bg_svctx_listening(TRUE);
        
        pt_this->b_under_ex_ctrl = FALSE;
        if (e_tv_mode == TV_MODE_TYPE_PIP)
        {
            _pop_show_osd_frames(pt_this, SHOW_OSD_FRAMES);
        }
        else
        {
            _pop_show_osd_frames(pt_this, HIDE_OSD_FRAMES);
        }
        _pop_stop_timer(pt_this);
        break;
    }
    case NAV_UI_MSG_POWER_OFF:
        pt_this->b_is_power_on_received = FALSE;
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }

        _pop_hide_wins(pt_this);
        pt_this->b_under_ex_ctrl = FALSE;
        i4_ret = _pop_update_status_as_power_off();
        pop_enter_normal_mode (pt_this);
        {
            VSH_REGION_INFO_T t_dsp_region = {0};

            /* set sub svctx to zero display region */
            t_dsp_region.ui4_x      = 0;
            t_dsp_region.ui4_y      = 0;
            t_dsp_region.ui4_width  = 0;
            t_dsp_region.ui4_height = 0;

            nav_set_stream_attr(
                        TV_WIN_ID_SUB,
                        ST_VIDEO,
                        SM_VSH_SET_TYPE_DISP_REGION,
                        &t_dsp_region,
                        sizeof(VSH_REGION_INFO_T)
                        );
        }
        break;
    case NAV_UI_MSG_EXTERNAL_CTRL_BEGIN:
        if (pt_this->b_under_ex_ctrl == TRUE) {
            break;
        }

        pt_this->b_under_ex_ctrl = TRUE;

        i4_ret = _pop_get_last_tv_mode(&e_last_tv_mode);
        if (i4_ret != NAVR_OK || e_last_tv_mode == TV_MODE_TYPE_NORMAL) {
            break;
        }

        i4_ret = pop_enter_normal_mode(pt_this);
        break;
    case NAV_UI_MSG_EXTERNAL_CTRL_END:
        pt_this->b_under_ex_ctrl = FALSE;
        break;
    case NAV_UI_MSG_POWER_ON:
        pt_this->b_is_power_on_received = TRUE;
        i4_ret = _pop_update_status_as_power_on();
        break;
    case NAV_UI_MSG_MIGHT_START_RF_SCAN:
        /* should NOT check TV mode */
        _pop_set_might_single_rf_scan(pt_ui_msg->e_tv_win_id, TRUE);
        break;
    case NAV_UI_MSG_CH_SCANNING:
    {
        BOOL b_in_scanning = (BOOL)(UINT32)pv_arg1;
        
        if (b_in_scanning == TRUE) {
            if (nav_get_src_type(TV_WIN_ID_MAIN) == INP_SRC_TYPE_TV) {
                _pop_set_might_single_rf_scan(TV_WIN_ID_MAIN, FALSE);
            } else if (nav_get_src_type(TV_WIN_ID_SUB) == INP_SRC_TYPE_TV) {
                _pop_set_might_single_rf_scan(TV_WIN_ID_SUB, FALSE);
            }
        }
        
        if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
            break;
        }

        if (b_in_scanning == TRUE) {
            /* hide main */
            if (nav_get_src_type(TV_WIN_ID_MAIN) == INP_SRC_TYPE_TV) {
                _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, TRUE);
            }

            if (nav_get_src_type(TV_WIN_ID_SUB) == INP_SRC_TYPE_TV) {
                _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, TRUE);
            }
        } else {
            if (nav_get_src_type(TV_WIN_ID_SUB) == INP_SRC_TYPE_TV) {
                if (e_tv_mode == TV_MODE_TYPE_PIP) {
                    _pop_update_pip_sub_win_rect_for_aspect_ratio(pt_this);
                }
            }
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
 *      _pop_is_able_to_enable
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _pop_is_able_to_enable(
                    VOID
                    )
{
#ifdef APP_CLRQAM_SUPPORT
    BOOL b_rating_enabled = FALSE;

    if (a_cfg_get_rating_enabled(&b_rating_enabled) == APP_CFGR_OK) {
        if (b_rating_enabled == TRUE) {
            return FALSE;
        }
    }
#endif
    return TRUE;
}
#ifdef APP_VOG_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      pop_get_isl_recs
 * Description
 *      The API is the Video On Grapic version. i.e. Main = VGA, Sub = TV
 * Input arguments
 *      None
 * Output arguments
 *      pt_main_rec     the main isl record
 *      pt_sub_rec      the sub isl record
 * Returns
 *      NAVR_OK
 *      NAVR_FAIL
 *---------------------------------------------------------------------------*/
INT32 pop_get_isl_recs(
                    ISL_REC_T*                  pt_main_rec,
                    ISL_REC_T*                  pt_sub_rec
                    )
{
    BOOL      b_is_same_grp = TRUE;
    ISL_REC_T t_crnt_main_rec;
    INT32     i4_ret;

    if (_pop_is_able_to_enable() == FALSE) {
        return NAVR_FAIL;
    }

    i4_ret = a_isl_get_rec_by_dev_type(
                    DEV_AVC_VGA,
                    0,
                    pt_main_rec
                    );
    if (i4_ret != ISLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_isl_get_rec_by_type(
                    INP_SRC_TYPE_TV,
                    0,
                    pt_sub_rec
                    );
    if (i4_ret != ISLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_isl_is_same_group(pt_main_rec, pt_sub_rec, &b_is_same_grp);
    if (i4_ret != ISLR_OK || b_is_same_grp == TRUE) {
        return NAVR_FAIL;
    }

    if (pt_main_rec->e_src_type == INP_SRC_TYPE_VTRL || pt_sub_rec->e_src_type == INP_SRC_TYPE_VTRL)
    {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_crnt_main_rec);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    if (t_crnt_main_rec.ui1_id != pt_main_rec->ui1_id) {
        nav_sync_stop_service(TV_WIN_ID_MAIN);
    }

    return NAVR_OK;
}
#else
/*-----------------------------------------------------------------------------
 * Name
 *      pop_get_isl_recs
 * Description
 *      The API is the generic version to get proper source for Main and Sub
 * Input arguments
 *      None
 * Output arguments
 *      pt_main_rec     the main isl record
 *      pt_sub_rec      the sub isl record
 * Returns
 *      NAVR_OK
 *      NAVR_FAIL
 *---------------------------------------------------------------------------*/
INT32 pop_get_isl_recs(
                    ISL_REC_T*                  pt_main_rec,
                    ISL_REC_T*                  pt_sub_rec
                    )
{
    POP_T*      pt_this       = &t_g_pop;
    BOOL        b_is_same_grp = TRUE;
    TV_WIN_ID_T e_focus_id;
    UINT8       ui1_num_recs;
    UINT8       ui1_idx;
    INT32       i4_ret;

    if (_pop_is_able_to_enable() == FALSE) {
        return NAVR_FAIL;
    }

    i4_ret = nav_get_focus_id(&e_focus_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, pt_main_rec);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_SUB,  pt_sub_rec);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }
    
    /* try to use last store main-sub pair first */
    if (e_focus_id == TV_WIN_ID_MAIN) {
        /* check sub could be last one */
        if (pt_main_rec->ui1_id == pt_this->ui1_src_ids[TV_WIN_ID_MAIN]) {
            if (pt_sub_rec->ui1_id != pt_this->ui1_src_ids[TV_WIN_ID_SUB]) {
                a_isl_get_rec_by_id(pt_this->ui1_src_ids[TV_WIN_ID_SUB], pt_sub_rec);
            }
        } else if (pt_main_rec->ui1_id == pt_this->ui1_src_ids[TV_WIN_ID_SUB]) {
            if (pt_sub_rec->ui1_id != pt_this->ui1_src_ids[TV_WIN_ID_MAIN]) {
                a_isl_get_rec_by_id(pt_this->ui1_src_ids[TV_WIN_ID_MAIN], pt_sub_rec);
            }
        }
    } else if (e_focus_id == TV_WIN_ID_SUB) {
        /* check main could be last one */
        if (pt_sub_rec->ui1_id == pt_this->ui1_src_ids[TV_WIN_ID_SUB]) {
            if (pt_main_rec->ui1_id != pt_this->ui1_src_ids[TV_WIN_ID_MAIN]) {
                a_isl_get_rec_by_id(pt_this->ui1_src_ids[TV_WIN_ID_MAIN], pt_main_rec);
            }
        } else if (pt_sub_rec->ui1_id == pt_this->ui1_src_ids[TV_WIN_ID_MAIN]) {
            if (pt_main_rec->ui1_id != pt_this->ui1_src_ids[TV_WIN_ID_SUB]) {
                a_isl_get_rec_by_id(pt_this->ui1_src_ids[TV_WIN_ID_SUB], pt_main_rec);
            }
        }
    }

    i4_ret = a_isl_get_num_rec(&ui1_num_recs);
    if (i4_ret != ISLR_OK) {
        return NAVR_FAIL;
    }

    for (ui1_idx = 0; ui1_idx < ui1_num_recs; ui1_idx++) {
        i4_ret = a_isl_is_same_group(pt_main_rec, pt_sub_rec, &b_is_same_grp);
        if (i4_ret != ISLR_OK) {
            return NAVR_FAIL;
        }

        if (pt_main_rec->e_src_type == INP_SRC_TYPE_VTRL || pt_sub_rec->e_src_type == INP_SRC_TYPE_VTRL)
        {
            b_is_same_grp = TRUE;
        }

        if (b_is_same_grp == FALSE) {
            return NAVR_OK;
        }

        /* should iterate the non-focused one, not the sub one */
        if (e_focus_id == TV_WIN_ID_MAIN) {
            i4_ret = a_isl_iterate_rec(pt_sub_rec->ui1_id,  TV_ITERATE_DIR_NEXT, pt_sub_rec);
            if (i4_ret != ISLR_OK) {
                return NAVR_FAIL;
            }
        } else if (e_focus_id == TV_WIN_ID_SUB) {
            i4_ret = a_isl_iterate_rec(pt_main_rec->ui1_id, TV_ITERATE_DIR_NEXT, pt_main_rec);
            if (i4_ret != ISLR_OK) {
                return NAVR_FAIL;
            }
        } else {
            return NAVR_FAIL;
        }
    }

    return NAVR_FAIL;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_handle_swap_request
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_handle_swap_request(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    TV_MODE_T e_tv_mode;
    INT32     i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return;
    }

    if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
        return;
    }

    pop_start_swap(&t_g_pop, e_tv_mode);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_enter_normal_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_enter_normal_mode(
                    POP_T*                      pt_this,
                    BOOL                        b_from_acfg
                    )
{
    ISL_REC_T   t_focus_isl_rec = {0};
    ISL_REC_T   t_blur_isl_rec  = {0};
    TV_WIN_ID_T e_focus_id;
    TV_WIN_ID_T e_blur_id;
    INT32       i4_ret;
#ifdef _APP_NAV_POP_SCARTOUT_COEXIST_SUPPORT        
    HANDLE_T    h_svl = NULL_HANDLE;

    /* Stop exclusion for SCART OUT when entering normal mode. */
    {
        HANDLE_T h_svctx;

        nav_get_svctx_handle(TV_WIN_ID_SUB, &h_svctx);
        c_svctx_stop_exclusion(h_svctx, (SRC_TYPE_T)0);
    }
#endif

    if (pt_this->ui1_swap_stopping_tv_win_bits > 0) {
        pt_this->ui1_swap_stopping_tv_win_bits = 0;
        nav_brdcst_msg_from_component(
                    TV_WIN_ID_LAST_VALID_ENTRY,
                    NAV_UI_MSG_AFTER_SVCS_SWAP,
                    NULL
                    );
    }
    
    if (nav_is_pop_pip_swapping() == TRUE) {
        nav_set_pop_pip_swapping(FALSE);
    }

    _pop_hide_wins(pt_this);
    nav_before_tv_mode_change(TV_MODE_TYPE_NORMAL);
    _pop_view_set_screen_status(TV_WIN_ID_MAIN, SVCTX_SCREEN_STATUS_SINGLE);
    _pop_view_set_screen_status(TV_WIN_ID_SUB,  SVCTX_SCREEN_STATUS_UNKNOWN);

    do {
        /* Blank Main/Sub to prevent transit state. */
        i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, FALSE);
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, FALSE);
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        pt_this->ui1_swap_stopping_tv_win_bits   = 0;
        pt_this->ui1_swap_selecting_tv_win_bits  = 0;
        
        i4_ret = nav_get_focus_id(&e_focus_id);
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        e_blur_id = NAV_GET_BLUR_ID(e_focus_id);
        
        i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_focus_isl_rec);
        if (i4_ret != TVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        i4_ret = a_tv_get_isl_rec_by_win_id(e_blur_id, &t_blur_isl_rec);
        if (i4_ret != TVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        a_tv_update_tuner_out_attr(
                        TV_MODE_TYPE_NORMAL,
                        &t_focus_isl_rec,
                        NULL
                        );
        
        if (pt_this->b_under_ex_ctrl == FALSE) {
            if (e_blur_id == TV_WIN_ID_MAIN) {
                nav_set_pop_pip_swapping(TRUE);

                nav_brdcst_msg_from_component(
                        TV_WIN_ID_LAST_VALID_ENTRY,
                        NAV_UI_MSG_BEFORE_SVCS_SWAP,
                        NULL
                        );
                nav_sync_stop_service(e_blur_id);
                nav_sync_stop_service(e_focus_id);
                _pop_swap_audio_steam_data(pt_this, TV_MODE_TYPE_NORMAL);
                a_tv_set_input_src_id(TV_WIN_ID_SUB, t_blur_isl_rec.ui1_id);
                a_tv_set_input_src_id(TV_WIN_ID_MAIN, t_focus_isl_rec.ui1_id);
                nav_update_src_info(TV_WIN_ID_MAIN);
                nav_update_src_info(TV_WIN_ID_SUB);
                a_tv_swap_tmp_unlock_info(TV_MODE_TYPE_NORMAL);
            } else {
                nav_sync_stop_service(e_blur_id);
                a_tv_reset_tmp_unlock_info(TV_WIN_ID_SUB);
                _pop_restore_default_strm_filter(pt_this);
            }
        }
        
        _pop_store_last_main_sub_source(pt_this);
        
        if (_pop_is_cooperative_app() == TRUE) {
            VSH_SET_PLANE_ORDER_INFO_T t_vsp_order  = {VSH_PLANE_ORDER_CTRL_BOTTOM, {0}};
        
            if (_pop_need_resize_disp_region(TV_WIN_ID_MAIN) == TRUE) {
                VSH_REGION_INFO_T t_dsp_region = {0};
        
                /* set main svctx to full display region */
                t_dsp_region.ui4_x      = 0;
                t_dsp_region.ui4_y      = 0;
                t_dsp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
                t_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT;
        
                i4_ret = nav_set_stream_attr(
                            TV_WIN_ID_MAIN,
                            ST_VIDEO,
                            SM_VSH_SET_TYPE_DISP_REGION,
                            &t_dsp_region,
                            sizeof(VSH_REGION_INFO_T)
                            );
                if (i4_ret != NAVR_OK) {
                    break;
                }
            }
        
            if (_pop_need_resize_disp_region(TV_WIN_ID_SUB) == TRUE) {
                VSH_REGION_INFO_T t_dsp_region = {0};
        
                /* set main svctx to full display region */
                t_dsp_region.ui4_x      = 0;
                t_dsp_region.ui4_y      = 0;
                t_dsp_region.ui4_width  = 0;
                t_dsp_region.ui4_height = 0;
        
                i4_ret = nav_set_stream_attr(
                            TV_WIN_ID_SUB,
                            ST_VIDEO,
                            SM_VSH_SET_TYPE_DISP_REGION,
                            &t_dsp_region,
                            sizeof(VSH_REGION_INFO_T)
                            );
                if (i4_ret != NAVR_OK) {
                    break;
                }
            }
                        /* set main svctx's video plane to BOTTOM */
            i4_ret = nav_set_stream_attr(
                        TV_WIN_ID_MAIN,
                        ST_VIDEO,
                        SM_VSH_SET_TYPE_PLANE_ORDER,
                        &t_vsp_order,
                        sizeof(VSH_SET_PLANE_ORDER_INFO_T)
                        );
            if (i4_ret != NAVR_OK) {
                break;
            }
        }
        
        if (pt_this->e_audio_focus_id == TV_WIN_ID_SUB) {
            pt_this->b_audio_focus_changing = TRUE;
        }
#ifdef _APP_NAV_POP_SCARTOUT_COEXIST_SUPPORT
        /* This code must be placed after SUB is stopped. */        
        /*
         *  For CR 139082.
         *  Re-select TV scart will cause TVE enable. After TVE is enabled,
         *  we can not issue any control to SUB.
         */
        if (t_focus_isl_rec.e_src_type == INP_SRC_TYPE_AV)
        {
            nav_get_svl_handle (e_focus_id, &h_svl);
            a_tv_update (TV_UPDATE_SCART_BYPASS_RESELECT_TV_SCART, (VOID*)h_svl, NULL, NULL);
        }
#endif
        
        _pop_stop_timer(pt_this);
        _pop_stop_swap_timer(pt_this);
        /* must put before nav_set_tv_mode() is invoked */
        _pop_set_last_tv_mode(TV_MODE_TYPE_NORMAL);
        /* 
         *  Must set focus id first. Because this will set ACFG disp name.
         *  Therefore, the subsequent ACFG operations will be set to Main.
         */
        nav_set_focus_id(TV_WIN_ID_MAIN, TRUE);
        if (b_from_acfg == FALSE) {
            nav_set_tv_mode(TV_MODE_TYPE_NORMAL);
        }
        nav_return_activation(NAV_COMP_ID_PIP_POP);
        
        if (pt_this->b_under_ex_ctrl == FALSE) {
            if (e_blur_id == TV_WIN_ID_MAIN) {
                /* Remove for CR 139721. */
//                nav_set_pop_pip_swapping(TRUE);
        
                nav_brdcst_msg_from_component(
                        TV_WIN_ID_LAST_VALID_ENTRY,
                        NAV_UI_MSG_AFTER_SVCS_SWAP,
                        NULL
                        );
            }
        
            if (pt_this->e_audio_focus_id == TV_WIN_ID_SUB) {
                _pop_update_tv_wins_audio_stream_mode(TV_WIN_ID_MAIN, TV_WIN_ID_SUB);
            }
        
            i4_ret = _pop_select_tv_window(
                        pt_this,
                        TV_MODE_TYPE_NORMAL,
                        TV_WIN_ID_MAIN,
                        &t_focus_isl_rec,
                        NULL,
                        TRUE,
                        TRUE
                        );
        
            if (e_blur_id == TV_WIN_ID_MAIN) {
                nav_set_pop_pip_swapping(FALSE);
            }
        
            if (i4_ret != NAVR_OK) {
                i4_ret = NAVR_FAIL;
                break;
            }
        }
        /*
         *  Remove for CR 137438.
         *  Because SVCTX will set blue mute on video plane. Hence, it's not
         *  necessary to set the PMX blue mute when entering normal mode.
         */
#if 0
        /* Delay for a while to make sure DISP_REG has been changed. */
        c_thread_delay(50);

        /* Set PMX blue mute here to make sure the DISP_REG has been changed to prevent transit state. */
        i4_ret = _pop_view_set_main_video_mute_via_pmx_bg(TRUE);
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
#endif
    } while (0);

    i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, TRUE);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, TRUE);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* don't move this statement, it avoid screen saver to show */
    nav_hide_component(NAV_COMP_ID_PIP_POP);
    
    /* Reset audio focus id. */
    t_g_pop.e_audio_focus_id = TV_WIN_ID_LAST_VALID_ENTRY;
    _pop_update_audio_focus_icl (TV_WIN_ID_LAST_VALID_ENTRY);

    /* Try to select an audio stream for Main. */
    i4_ret = _pop_select_audio_stream (pt_this, TV_WIN_ID_MAIN, FALSE);
    if (i4_ret == NAVR_NOT_EXIST)
    {
        /* If failed, re-select again when signal is locked. */
        pt_this->b_resel_audio = TRUE;
    }
    return _pop_normal_mode_post_handler(pt_this);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_enter_pip_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_enter_pip_mode(
                    POP_T*                      pt_this,
                    BOOL                        b_from_acfg
                    )
{
    VSH_SET_PLANE_ORDER_INFO_T t_main_vsp_order    = {VSH_PLANE_ORDER_CTRL_BOTTOM, {0}};
    VSH_REGION_INFO_T          t_main_video_region = {0};
    VSH_REGION_INFO_T          t_sub_video_region  = {0};
    SNK_DESC_T                 t_snk_desc          = {0};
    ISL_REC_T                  t_main_isl_rec      = {0};
    ISL_REC_T                  t_sub_isl_rec       = {0};
    INT32                      i4_ret;

    if (pt_this->ui1_swap_stopping_tv_win_bits > 0) {
        pt_this->ui1_swap_stopping_tv_win_bits = 0;
        nav_brdcst_msg_from_component(
                    TV_WIN_ID_LAST_VALID_ENTRY,
                    NAV_UI_MSG_AFTER_SVCS_SWAP,
                    NULL
                    );
    }
    _pop_update_audio_steam_data(pt_this);
#ifdef _APP_NAV_POP_SCARTOUT_COEXIST_SUPPORT
    /* Start exclusion for SCART OUT when entering PIP/POP. */
    {
        HANDLE_T h_svctx;

        nav_get_svctx_handle(TV_WIN_ID_SUB, &h_svctx);
        c_svctx_start_exclusion(h_svctx, (SRC_TYPE_T)0);
    }
#endif

    if (pt_this->e_audio_focus_id == TV_WIN_ID_LAST_VALID_ENTRY) {
        i4_ret = nav_get_focus_id(&pt_this->e_audio_focus_id);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        _pop_update_audio_focus_icl (pt_this->e_audio_focus_id);
    }

    pt_this->t_view_hdlr.pf_hide(TRUE);

    i4_ret = pop_get_isl_recs(&t_main_isl_rec, &t_sub_isl_rec);
    if (i4_ret != NAVR_OK) {
        nav_unregister_key_monitor_nty_fct(NAV_COMP_ID_PIP_POP);
        return NAVR_FAIL;
    }
    _pop_store_last_main_sub_source(pt_this);

    nav_before_tv_mode_change(TV_MODE_TYPE_PIP);
    _pop_view_set_screen_status(TV_WIN_ID_MAIN, SVCTX_SCREEN_STATUS_MULTIPLE_FULL);
    _pop_view_set_screen_status(TV_WIN_ID_SUB,  SVCTX_SCREEN_STATUS_MULTIPLE_PART);

    a_tv_update_tuner_out_attr(
                    TV_MODE_TYPE_PIP,
                    &t_main_isl_rec,
                    &t_sub_isl_rec
                    );
    _pop_set_last_tv_mode(TV_MODE_TYPE_PIP);
    /* set main window */
    nav_update_tv_win_status(TV_WIN_ID_MAIN, &t_main_isl_rec);

    i4_ret = pop_get_pip_main_region_info(&t_main_video_region);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    t_snk_desc.pt_video_region      = NULL;
    t_snk_desc.pt_disp_region       = &t_main_video_region;
    t_snk_desc.pt_video_plane_order = &t_main_vsp_order;
    t_snk_desc.ps_snk_grp_name      = NULL;

    i4_ret = _pop_select_tv_window(
                    pt_this,
                    TV_MODE_TYPE_PIP,
                    TV_WIN_ID_MAIN,
                    &t_main_isl_rec,
                    &t_snk_desc,
                    TRUE,
                    FALSE
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _pop_view_set_main_video_mute_via_pmx_bg(TRUE);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* set sub window */
    nav_update_tv_win_status(TV_WIN_ID_SUB, &t_sub_isl_rec);

    i4_ret = pop_get_pip_sub_region_info(
                    WIN_POS_DIR_CRNT,
                    WIN_SIZE_DIR_CRNT,
                    &t_sub_video_region
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    t_snk_desc.pt_video_region      = NULL;
    t_snk_desc.pt_disp_region       = &t_sub_video_region;
    t_snk_desc.pt_video_plane_order = NULL;
    t_snk_desc.ps_snk_grp_name      = NULL;

    i4_ret = _pop_select_tv_window(
                    pt_this,
                    TV_MODE_TYPE_PIP,
                    TV_WIN_ID_SUB,
                    &t_sub_isl_rec,
                    &t_snk_desc,
                    TRUE,
                    FALSE
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    pt_this->t_view_hdlr.pf_show();
    /* must put before nav_set_tv_mode() is invoked */
    if (b_from_acfg == FALSE) {
        nav_set_tv_mode(TV_MODE_TYPE_PIP);
    }
    nav_grab_activation(NAV_COMP_ID_PIP_POP);
    nav_set_component_visible(NAV_COMP_ID_PIP_POP);
    _pop_show_osd_frames(pt_this, SHOW_OSD_FRAMES);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_enter_pop_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_enter_pop_mode(
                    POP_T*                      pt_this,
                    BOOL                        b_from_acfg
                    )
{
    VSH_SET_PLANE_ORDER_INFO_T t_main_vsp_order    = {VSH_PLANE_ORDER_CTRL_BOTTOM, {0}};
    VSH_REGION_INFO_T          t_main_video_region = {0};
    VSH_REGION_INFO_T          t_sub_video_region  = {0};
    SNK_DESC_T                 t_snk_desc          = {0};
    ISL_REC_T                  t_main_isl_rec      = {0};
    ISL_REC_T                  t_sub_isl_rec       = {0};
    INT32                      i4_ret;
    HANDLE_T                   h_main_svctx        = NULL_HANDLE;
    HANDLE_T                   h_sub_svctx         = NULL_HANDLE;
    SVCTX_VIDEO_MUTE_INFO_T t_video_mute_info;
    BOOL b_blue_mute_enable = FALSE;

    _pop_update_audio_steam_data(pt_this);
#ifdef _APP_NAV_POP_SCARTOUT_COEXIST_SUPPORT
    /* Start exclusion for SCART OUT when entering PIP/POP. */
    {
        HANDLE_T h_svctx;

        nav_get_svctx_handle(TV_WIN_ID_SUB, &h_svctx);
        c_svctx_start_exclusion(h_svctx, (SRC_TYPE_T)0);
    }
#endif
    i4_ret = a_cfg_get_blue_mute (&b_blue_mute_enable);
    if (i4_ret != APP_CFGR_OK)
    {
        b_blue_mute_enable = FALSE;
    }
    i4_ret = _pop_view_set_main_video_mute_via_pmx_bg(FALSE);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    if (b_blue_mute_enable)
    {
        /* 
         *  Mute Main & Sub video first.
         *  This avoids the situation that Main is playing video and Sub is no signal
         *  with blue mute. When entering POP, the blue mute of SUB disappeared first.
         */
        _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, FALSE);
        _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, FALSE);
        
        /*
         *  Disable blue to avoid transit state which occurred when SUB with no signal
         *  is moved and enlarged.
         */
        t_video_mute_info.b_enable          = FALSE;
        t_video_mute_info.t_color.ui1_red   = 0;
        t_video_mute_info.t_color.ui1_green = 0;
        t_video_mute_info.t_color.ui1_blue  = 0;
        
        nav_get_svctx_handle (TV_WIN_ID_MAIN, &h_main_svctx);
        nav_get_svctx_handle (TV_WIN_ID_SUB, &h_sub_svctx);
        
        i4_ret = c_svctx_set(h_main_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        i4_ret = c_svctx_set(h_sub_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        /* Delay for a while to make sure blue mute takes effect. */
        c_thread_delay (50);
    }

    do
    {
        if (pt_this->ui1_swap_stopping_tv_win_bits > 0) {
            pt_this->ui1_swap_stopping_tv_win_bits = 0;
            nav_brdcst_msg_from_component(
                        TV_WIN_ID_LAST_VALID_ENTRY,
                        NAV_UI_MSG_AFTER_SVCS_SWAP,
                        NULL
                        );
        }
        
        if (pt_this->e_audio_focus_id == TV_WIN_ID_LAST_VALID_ENTRY) {
            i4_ret = nav_get_focus_id(&pt_this->e_audio_focus_id);
            if (i4_ret != NAVR_OK) {
                break;
            }
        }
        
        pt_this->t_view_hdlr.pf_hide(TRUE);
        
        i4_ret = pop_get_isl_recs(&t_main_isl_rec, &t_sub_isl_rec);
        if (i4_ret != NAVR_OK) {
            nav_unregister_key_monitor_nty_fct(NAV_COMP_ID_PIP_POP);
            break;
        }
        
        _pop_store_last_main_sub_source(pt_this);
        nav_before_tv_mode_change(TV_MODE_TYPE_POP);
        _pop_view_set_screen_status(TV_WIN_ID_MAIN, SVCTX_SCREEN_STATUS_MULTIPLE_PART);
        _pop_view_set_screen_status(TV_WIN_ID_SUB,  SVCTX_SCREEN_STATUS_MULTIPLE_PART);
        a_tv_update_tuner_out_attr(
                        TV_MODE_TYPE_POP,
                        &t_main_isl_rec,
                        &t_sub_isl_rec
                        );
        
        i4_ret = pop_get_pop_region_infos(
                        WIN_POS_DIR_CRNT,
                        &t_main_video_region,
                        &t_sub_video_region
                        );
        if (i4_ret != NAVR_OK && i4_ret != NAVR_NO_ACTION) {
            break;
        }
        
        _pop_set_last_tv_mode(TV_MODE_TYPE_POP);
        
        /* main */
        nav_update_tv_win_status(TV_WIN_ID_MAIN, &t_main_isl_rec);
        
        t_snk_desc.pt_video_region      = NULL;
        t_snk_desc.pt_disp_region       = &t_main_video_region;
        t_snk_desc.pt_video_plane_order = &t_main_vsp_order;
        t_snk_desc.ps_snk_grp_name      = NULL;
        
        i4_ret = _pop_select_tv_window(
                        pt_this,
                        TV_MODE_TYPE_POP,
                        TV_WIN_ID_MAIN,
                        &t_main_isl_rec,
                        &t_snk_desc,
                        TRUE,
                        FALSE
                        );
        if (i4_ret != NAVR_OK) {
            break;
        }
        
        /* sub */
        nav_update_tv_win_status(TV_WIN_ID_SUB, &t_sub_isl_rec);
        
        t_snk_desc.pt_video_region      = NULL;
        t_snk_desc.pt_disp_region       = &t_sub_video_region;
        t_snk_desc.pt_video_plane_order = NULL;
        t_snk_desc.ps_snk_grp_name      = NULL;
        
        i4_ret = _pop_select_tv_window(
                        pt_this,
                        TV_MODE_TYPE_POP,
                        TV_WIN_ID_SUB,
                        &t_sub_isl_rec,
                        &t_snk_desc,
                        TRUE,
                        FALSE
                        );
        if (i4_ret != NAVR_OK) {
            break;
        }
        
        pt_this->t_view_hdlr.pf_show();
        /* must put before nav_set_tv_mode() is invoked */
        if (b_from_acfg == FALSE) {
            nav_set_tv_mode(TV_MODE_TYPE_POP);
        }
        nav_grab_activation(NAV_COMP_ID_PIP_POP);
        nav_set_component_visible(NAV_COMP_ID_PIP_POP);
        _pop_show_osd_frames(pt_this, SHOW_OSD_FRAMES);
    } while (0);

    if (b_blue_mute_enable)
    {
        t_video_mute_info.b_enable          = TRUE;
        t_video_mute_info.t_color.ui1_red   = 0;
        t_video_mute_info.t_color.ui1_green = 0;
        t_video_mute_info.t_color.ui1_blue  = 0xFF;
        
        c_thread_delay (150);
        c_svctx_set(h_main_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        c_svctx_set(h_sub_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, TRUE);
        _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, TRUE);
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      pop_enter_normal_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 pop_enter_normal_mode(
                    POP_T*                      pt_this
                    )
{
    return _pop_enter_normal_mode(pt_this, FALSE);
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_enter_pip_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 pop_enter_pip_mode(
                    POP_T*                      pt_this
                    )
{
    return _pop_enter_pip_mode(pt_this, FALSE);
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_enter_pip_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 pop_enter_pop_mode(
                    POP_T*                      pt_this
                    )
{
    return _pop_enter_pop_mode(pt_this, FALSE);
}
INT32 pop_set_disable_audio_focus (BOOL b_disable)
{
    POP_T*            pt_this            = &t_g_pop;
		
		pt_this->b_disable_audio_focus_chg = b_disable;
		
		return NAVR_OK;
}
INT32 pop_get_disable_audio_focus (BOOL* pb_disable)
{
    POP_T*            pt_this            = &t_g_pop;
		
		if (!pb_disable)
		{
			return NAVR_INV_ARG;
		}
		*pb_disable = pt_this->b_disable_audio_focus_chg;

		return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_change_pip_sub_region
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
INT32 pop_change_pip_sub_region(
                    WIN_POS_DIR_T           e_pos_dir,
                    WIN_SIZE_DIR_T          e_size_dir
                    )
{
    VSH_REGION_INFO_T t_sub_video_region = {0};
    POP_T*            pt_this            = &t_g_pop;
    INT32             i4_ret;

    if (e_pos_dir != WIN_POS_DIR_CRNT) {
        i4_ret = _pop_unfreeze(TV_WIN_ID_SUB);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    }

    if (e_size_dir != WIN_SIZE_DIR_CRNT) {
        i4_ret = _pop_unfreeze(TV_WIN_ID_SUB);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    }

    i4_ret = pop_get_pip_sub_region_info(
                    e_pos_dir,
                    e_size_dir,
                    &t_sub_video_region
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = _pop_change_win_region(
                    pt_this,
                    TV_MODE_TYPE_PIP,
                    TV_WIN_ID_SUB,
                    &t_sub_video_region,
                    TRUE
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_change_pop_regions
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 pop_change_pop_regions(
                    WIN_POS_DIR_T           e_pos_dir
                    )
{
    VSH_REGION_INFO_T t_main_video_region = {0};
    VSH_REGION_INFO_T t_sub_video_region  = {0};
    POP_T*            pt_this             = &t_g_pop;
    INT32             i4_ret;

    i4_ret = pop_get_pop_region_infos(
                    e_pos_dir,
                    &t_main_video_region,
                    &t_sub_video_region
                    );
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = _pop_unfreeze(TV_WIN_ID_MAIN);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = _pop_unfreeze(TV_WIN_ID_SUB);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (e_pos_dir == WIN_POS_DIR_NEXT) {
        i4_ret = _pop_change_win_region(
                    pt_this,
                    TV_MODE_TYPE_POP,
                    TV_WIN_ID_SUB,
                    &t_sub_video_region,
                    FALSE
                    );
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = _pop_change_win_region(
                    pt_this,
                    TV_MODE_TYPE_POP,
                    TV_WIN_ID_MAIN,
                    &t_main_video_region,
                    FALSE
                    );
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    } else {
        i4_ret = _pop_change_win_region(
                    pt_this,
                    TV_MODE_TYPE_POP,
                    TV_WIN_ID_MAIN,
                    &t_main_video_region,
                    FALSE
                    );
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = _pop_change_win_region(
                    pt_this,
                    TV_MODE_TYPE_POP,
                    TV_WIN_ID_SUB,
                    &t_sub_video_region,
                    FALSE
                    );
        if (i4_ret != NAVR_OK) {
            return NAVR_FAIL;
        }
    }

    pt_this->t_view_hdlr.pf_show();

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_start_swap
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pop_start_swap(
                    POP_T*                      pt_this,
                    TV_MODE_T                   e_tv_mode
                    )
{
    ISL_REC_T t_main_isl_rec = {0};
    ISL_REC_T t_sub_isl_rec  = {0};
    INT32     i4_ret         = NAVR_FAIL;

    nav_set_pop_pip_swapping(TRUE);
    do {
        pop_set_disable_audio_focus (TRUE);
        i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_MAIN, FALSE);
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        i4_ret = _pop_enable_default_video_plane_mode(TV_WIN_ID_SUB, FALSE);
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_main_isl_rec);
        if (i4_ret != TVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_SUB, &t_sub_isl_rec);
        if (i4_ret != TVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        i4_ret = nav_brdcst_msg_from_component(
                        TV_WIN_ID_LAST_VALID_ENTRY,
                        NAV_UI_MSG_BEFORE_SVCS_SWAP,
                        NULL
                        );
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        pt_this->ui1_swap_stopping_tv_win_bits  = 0;
        
        i4_ret = _pop_swap_audio_steam_data(pt_this, e_tv_mode);
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        _pop_stop_swap_timer(pt_this);
        
        /* stop main */
        i4_ret = nav_stop_service(TV_WIN_ID_MAIN);
        if (i4_ret == NAVR_ALREADY_STOPPED) {
            /*pt_this->ui1_swap_stopping_tv_win_bits &= ~MAKE_BIT_MASK_8(TV_WIN_ID_MAIN);*/
        } else if (i4_ret == NAVR_OK) {
            pt_this->ui1_swap_stopping_tv_win_bits |= MAKE_BIT_MASK_8(TV_WIN_ID_MAIN);
        }
        
        i4_ret = _pop_show_win_rect_bg(
                        pt_this,
                        TV_WIN_ID_MAIN,
                        e_tv_mode,
                        POP_RECT_BG_CMD_BLACK,
                        TRUE
                        );
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        /* stop sub */
        i4_ret = nav_stop_service(TV_WIN_ID_SUB);
        if (i4_ret == NAVR_ALREADY_STOPPED) {
            /*pt_this->ui1_swap_stopping_tv_win_bits &= ~MAKE_BIT_MASK_8(TV_WIN_ID_SUB);*/
        } else if (i4_ret == NAVR_OK) {
            pt_this->ui1_swap_stopping_tv_win_bits |= MAKE_BIT_MASK_8(TV_WIN_ID_SUB);
        }
        
        i4_ret = _pop_show_win_rect_bg(
                        pt_this,
                        TV_WIN_ID_SUB,
                        e_tv_mode,
                        POP_RECT_BG_CMD_BLACK,
                        TRUE
                        );
        if (i4_ret != NAVR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }
        
        /* should put after nav_stop_service() to avoid wrong video attributes setting. */
        a_tv_set_input_src_id(TV_WIN_ID_MAIN, t_sub_isl_rec.ui1_id);
        a_tv_set_input_src_id(TV_WIN_ID_SUB,  t_main_isl_rec.ui1_id);
        a_tv_swap_tmp_unlock_info(e_tv_mode);
        
        if (pt_this->ui1_swap_stopping_tv_win_bits == 0) {
            _pop_reset_swap_timer(pt_this);
        }
        
        return NAVR_OK;
    } while (0);
        
    nav_set_pop_pip_swapping(FALSE);
    pop_set_disable_audio_focus (FALSE);
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_start_focus_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pop_start_focus_change(
                    POP_T*                      pt_this
                    )
{
    TV_WIN_ID_T e_blur_id;
    TV_WIN_ID_T e_focus_id;
    INT32       i4_ret;

    i4_ret = nav_get_focus_id(&e_blur_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    e_focus_id = NAV_GET_FOCUS_ID(e_blur_id);

    a_cfg_lock();
    i4_ret = nav_set_focus_id(e_focus_id, TRUE);
    if (i4_ret != NAVR_OK) {
        a_cfg_unlock();
        return i4_ret;
    }
    a_cfg_unlock();
    i4_ret = _pop_start_focus_change(pt_this, e_focus_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_get_audio_focus_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pop_get_audio_focus_id(
                    POP_T*                  pt_this,
                    TV_WIN_ID_T*            pe_focus_id
                    )
{
    INT32 i4_ret;

    if (pt_this->e_audio_focus_id == TV_WIN_ID_LAST_VALID_ENTRY) {
        i4_ret = nav_get_focus_id(pe_focus_id);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    } else {
        *pe_focus_id = pt_this->e_audio_focus_id;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_start_audio_focus_change
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pop_start_audio_focus_change(
                    POP_T*                      pt_this
                    )
{
    STREAM_COMP_ID_T t_blur_audio_comp_id;
    SCDB_REC_T       t_scdb_rec;
    TV_WIN_ID_T      e_blur_id;
    INT32            i4_ret;

	c_memset(&t_scdb_rec, 0, sizeof(SCDB_REC_T));

    if (pt_this->e_audio_focus_id == TV_WIN_ID_LAST_VALID_ENTRY) {
        i4_ret = nav_get_focus_id(&pt_this->e_audio_focus_id);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    }

    pt_this->b_audio_focus_changing = TRUE;
    e_blur_id                       = pt_this->e_audio_focus_id;
    pt_this->e_audio_focus_id       = NAV_GET_FOCUS_ID(e_blur_id);
    _pop_update_tv_wins_audio_stream_mode(pt_this->e_audio_focus_id, e_blur_id);
    _pop_update_audio_focus_icl (pt_this->e_audio_focus_id);

    _pop_set_audio_stream_type_data(e_blur_id, SCDB_REC_TYPE_UNKNOWN);
    i4_ret = nav_get_using_strm_data(
                    e_blur_id,
                    ST_AUDIO,
                    &t_blur_audio_comp_id,
                    &t_scdb_rec
                    );
    if (i4_ret == NAVR_OK) {
        _pop_set_audio_stream_data_by_rec(
                    e_blur_id,
                    &t_blur_audio_comp_id,
                    &t_scdb_rec
                    );

        i4_ret = nav_stop_stream(e_blur_id, ST_AUDIO);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
    } else {
        /* even blur win has no audio, still need to change the stream mode in
         * service context.
         */
        i4_ret = nav_stop_stream(e_blur_id, ST_AUDIO);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }

        _pop_select_audio_stream_for_focus_change(pt_this, pt_this->e_audio_focus_id);
    }

    return NAVR_OK;
}
#ifdef CLI_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      pop_print_self
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID pop_print_self(
                    VOID
                    )
{
    POP_T* pt_this = &t_g_pop;
    UINT32 ui4_stream_mode;
  
    DBG_INFO(("------------------- POP status -----------\r\n"));
    DBG_INFO(("ui1_swap_stopping_tv_win_bits   - 0x%x\r\n", pt_this->ui1_swap_stopping_tv_win_bits));
    DBG_INFO(("ui1_swap_selecting_tv_win_bits  - 0x%x\r\n", pt_this->ui1_swap_selecting_tv_win_bits));
    DBG_INFO(("ui4_canvas_width                - %d\r\n", pt_this->ui4_canvas_width));
    DBG_INFO(("ui4_canvas_height               - %d\r\n", pt_this->ui4_canvas_height));
    DBG_INFO(("ui2_misc_cfg_nfy                - %d\r\n", pt_this->ui2_misc_cfg_nfy));
    DBG_INFO(("ui2_nav_cfg_nfy                 - %d\r\n", pt_this->ui2_nav_cfg_nfy));
    DBG_INFO(("ui2_pip_pop_cfg_nfy             - %d\r\n", pt_this->ui2_pip_pop_cfg_nfy));
    DBG_INFO(("ui2_gui_lang_cfg_nfy            - %d\r\n", pt_this->ui2_gui_lang_cfg_nfy));
    DBG_INFO(("h_main_svctx                    - %d\r\n", pt_this->h_main_svctx));
    DBG_INFO(("h_sub_svctx                     - %d\r\n", pt_this->h_sub_svctx));
    DBG_INFO(("h_hide_timer                    - %d\r\n", pt_this->h_hide_timer));
    DBG_INFO(("h_swap_timer                    - %d\r\n", pt_this->h_swap_timer));
    DBG_INFO(("b_frames_shown                  - %s\r\n",(pt_this->b_frames_shown ? "Y" : "N")));
    DBG_INFO(("ui4_hide_timeout                - %d\r\n", pt_this->ui4_hide_timeout));
    DBG_INFO(("e_audio_focus_id                - %d\r\n", pt_this->e_audio_focus_id));
    DBG_INFO(("b_audio_focus_changing          - %s\r\n",(pt_this->b_audio_focus_changing ? "Y" : "N")));
    DBG_INFO(("b_under_ex_ctrl                 - %s\r\n",(pt_this->b_under_ex_ctrl ? "Y" : "N")));
    DBG_INFO(("e_last_tv_mode                  - %d\r\n", pt_this->e_last_tv_mode));
    DBG_INFO(("e_tv_mode_in_changing           - %d\r\n", pt_this->e_tv_mode_in_changing));
    DBG_INFO(("h_lock                          - %d\r\n", pt_this->h_lock));
    DBG_INFO(("b_using_pip_audio_strm_filter   - %s\r\n",(pt_this->b_using_pip_audio_strm_filter ? "Y" : "N")));
    DBG_INFO(("b_might_single_rf_scan[MAIN]    - %s\r\n",(pt_this->b_might_single_rf_scan[TV_WIN_ID_MAIN] ? "Y" : "N")));
    DBG_INFO(("b_might_single_rf_scan[SUB]     - %s\r\n",(pt_this->b_might_single_rf_scan[TV_WIN_ID_SUB] ? "Y" : "N")));
    DBG_INFO(("t_audios[MAIN].e_type           - %d\r\n", pt_this->t_audios[TV_WIN_ID_MAIN].e_type));
    DBG_INFO(("t_audios[MAIN].t_comp_id.e_type - %d\r\n", pt_this->t_audios[TV_WIN_ID_MAIN].t_comp_id.e_type));
    DBG_INFO(("t_audios[MAIN].t_mpeg.ui2_pid   - %d\r\n", pt_this->t_audios[TV_WIN_ID_MAIN].t_mpeg.ui2_pid));
    DBG_INFO(("t_audios[SUB].e_type            - %d\r\n", pt_this->t_audios[TV_WIN_ID_SUB].e_type));
    DBG_INFO(("t_audios[SUB].t_comp_id.e_type  - %d\r\n", pt_this->t_audios[TV_WIN_ID_SUB].t_comp_id.e_type));
    DBG_INFO(("t_audios[SUB].t_mpeg.ui2_pid    - %d\r\n", pt_this->t_audios[TV_WIN_ID_SUB].t_mpeg.ui2_pid));
    DBG_INFO(("t_videos[MAIN].e_status         - %d\r\n", pt_this->t_videos[TV_WIN_ID_MAIN].e_status));
    DBG_INFO(("t_videos[SUB].e_status          - %d\r\n", pt_this->t_videos[TV_WIN_ID_SUB].e_status));
    nav_get_stream_mode(TV_WIN_ID_MAIN, &ui4_stream_mode);
    DBG_INFO(("TV_WIN_ID_MAIN.ui4_stream_mode  - %d\r\n", ui4_stream_mode));
    nav_get_stream_mode(TV_WIN_ID_SUB, &ui4_stream_mode);
    DBG_INFO(("TV_WIN_ID_SUB.ui4_stream_mode   - %d\r\n", ui4_stream_mode));
    
}
#endif
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_pop_register(
                    POP_VIEW_HDLR_T*            pt_view_hdlr
                    )
{
    POP_T*     pt_this = &t_g_pop;
    NAV_COMP_T t_comp;
    INT32      i4_ret;

    c_memset (&t_comp, 0, sizeof (NAV_COMP_T));

    t_comp.pf_init           = _pop_init;
    t_comp.pf_deinit         = _pop_deinit;
    t_comp.pf_is_key_handler = _pop_is_key_handler;
    t_comp.pf_activate       = _pop_activate;
    t_comp.pf_inactivate     = NULL;
    t_comp.pf_hide           = _pop_hide;
    t_comp.pf_handle_msg     = _pop_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_PIP_POP, &t_comp, COMP_EXEC_SET_PIP_POP);
    if (i4_ret != NAVR_OK) {
        DBG_ERROR((_ERROR_HEADER"nav_register_component(NAV_COMP_ID_PIP_POP) failed\r\n"));
        return i4_ret;
    }

    if (pt_view_hdlr == NULL) {
        pop_view_register_default_hdlr(&pt_this->t_view_hdlr);
    } else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }

    nav_pop_cli_register_cmd_tbl();

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_request_swap
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
BOOL a_pop_request_swap(VOID)
{
    TV_MODE_T e_tv_mode;
    INT32     i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return FALSE;
    }

    if (e_tv_mode != TV_MODE_TYPE_PIP && e_tv_mode != TV_MODE_TYPE_POP) {
        return FALSE;
    }

    nav_request_context_switch(_pop_handle_swap_request, NULL, NULL, NULL);

    return TRUE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_update_pip_sub_win
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
BOOL a_pop_update_pip_sub_win(VOID)
{
    TV_MODE_T e_tv_mode;
    INT32     i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK || e_tv_mode != TV_MODE_TYPE_PIP) {
        return FALSE;
    }

    _pop_update_pip_sub_win_rect_to_final(
                    &t_g_pop,
                    TV_MODE_TYPE_PIP,
                    TV_WIN_ID_SUB
                    );

    return TRUE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_start_audio_focus_change
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_pop_start_audio_focus_change(VOID)
{
    return pop_start_audio_focus_change (&t_g_pop);
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_get_audio_focus
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_pop_get_audio_focus(VOID)
{
    TV_WIN_ID_T e_focus_id;

    pop_get_audio_focus_id(&t_g_pop, &e_focus_id);
    return e_focus_id;
}

/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_get_audio_focus_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 a_pop_get_audio_focus_id(
                    TV_WIN_ID_T*            pe_focus_id
                    )
{
    return pop_get_audio_focus_id (&t_g_pop, pe_focus_id);
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_set_osd_audio_focus
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
VOID a_pop_set_osd_audio_focus(TV_WIN_ID_T e_focus_id)
{
    t_g_pop.e_audio_focus_id = (e_focus_id==TV_WIN_ID_MAIN ? TV_WIN_ID_SUB : TV_WIN_ID_MAIN);
    _pop_update_audio_focus_icl (t_g_pop.e_audio_focus_id);
    pop_start_audio_focus_change (&t_g_pop);
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_sync_set_tv_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_pop_sync_set_tv_mode (TV_MODE_T e_tv_mode)
{
    TV_MODE_T e_mode;
    nav_get_tv_mode(&e_mode);

    if (e_mode == e_tv_mode)
    {
        return NAVR_OK;
    }
    

    nav_request_context_switch_in_sync(
            _pop_handle_cfg_nfy,
            (VOID*)(UINT32)e_tv_mode,
            (VOID*)(UINT32)APP_CFG_GRPID_PIP_POP,
            (VOID*)(UINT32)APP_CFG_RECID_TV_MODE,
            _POP_TV_NORMAL_MODE_CHANGE_TIMEOUT
            );
    a_tv_set_mode (TV_MODE_TYPE_NORMAL);
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_pop_sync_hide_warning_osd
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_pop_sync_hide_warning_osd (VOID)
{
    nav_request_context_switch_in_sync(
            _pop_handle_sync_request,
            NULL,
            NULL,
            NULL,
            5000
            );
    return NAVR_OK;
}

#ifdef SYS_MTKTVAPI_SUPPORT

INT32 a_pop_start_focus_change(VOID)
{
    return NAVR_OK;
}

INT32 a_pop_get_crnt_video_region(VSH_REGION_INFO_T  *pt_main_video_region,
                                  VSH_REGION_INFO_T  *pt_sub_video_region)
{
    return NAVR_OK;
}

INT32 a_pop_get_crnt_win_rec_by_video_region(
                    VSH_REGION_INFO_T*      pt_video_region,
                    INT16 *                 pi2_x,
                    INT16 *                 pi2_y,
                    INT16 *                 pi2_w,
                    INT16 *                 pi2_h
                    )
{
    return NAVR_OK;
}

#endif

#endif /*APP_PIP_POP_CTRL*/
#endif /*APP_537X_SUPPORT*/
