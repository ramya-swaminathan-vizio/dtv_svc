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
 * $RCSfile: audio_player.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                     include files
-----------------------------------------------------------------------------*/
#include "c_iom.h"
#include "c_scc.h"
#include "c_svctx.h"
#include "c_img.h"
#include "c_dbg.h"


#include "app_util/a_cfg.h"

#include "audio_player.h"
#include "a_audio_player.h"
#include "u_irrc_btn_def.h"
#include "res/mmp/img/mmp_img.h"
#include "mmp/file_browser/file_browser.h"
#include "audio_player_cli.h"
#include "mmp/common_ui2/mmp_com_ui_info_handler.h"
#include "mmp/common_ui2/mmp_common_ui_toolbar.h"
#include "mmp/common_ui2/mmp_common_ui_detail_page.h"
#include "mmp/common_ui2/mmp_info_bar.h"
#include "mmp/app/mmp_main.h"
#include "mmp/video_engine/video_engine_cli.h"
#include "app_util/a_tv.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#include "mmp/eq_spectrum/a_mmp_eq_viewer.h"
#include "res/mmp/eq_spectrum/mmp_eq_rc.h"
#include "mmp/listmode2/listmode.h"
#include "app_util/option_list/a_optl.h"
#include "mmp/listmode2/listmode_view.h"
#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
#include "mmp/dmr/mmp_dmr.h"
#endif

/*-----------------------------------------------------------------------------
 * macros, typedefs, enums
 *---------------------------------------------------------------------------*/
#define MMP_AP_AV_NTFY_EMPTY               ((UINT16)0x0000)
#define MMP_AP_AV_NTFY_AUDIO_NOT_SUPPORT   ((UINT16)0x0001)
#define MMP_AP_AV_NTFY_OTHER               ((UINT16)0x0002)

#define MMP_AP_FLAG_AUD_ONLY               MAKE_BIT_MASK_32(0)
#define MMP_AP_FLAG_ACTIVATE               MAKE_BIT_MASK_32(1)
#define MMP_AP_FLAG_SEEKING                MAKE_BIT_MASK_32(2)
#define MMP_AP_FLAG_SEEKING_BEGIN          MAKE_BIT_MASK_32(3)
#define MMP_AP_FLAG_PLAY_BEFORE_SEEK       MAKE_BIT_MASK_32(4)
#define MMP_AP_FLAG_STOPING                MAKE_BIT_MASK_32(5)
#define MMP_AP_FLAG_OPTION_LIST_SHOW       MAKE_BIT_MASK_32(6)
#define MMP_AP_FLAG_LYRIC_LIST_SHOW        MAKE_BIT_MASK_32(7)


/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum
{
    _MMP_AP_LAST_OPEN_ELM_RET_NORMAL = 0,
    _MMP_AP_LAST_OPEN_ELM_RET_FAILED,
    _MMP_AP_LAST_OPEN_ELM_RET_CORRUPT

}   _MMP_AP_LAST_OPEN_ELM_RET_T;

/******************************************************************************
*******************************************************************************
                                audio  Player Viewer
*******************************************************************************
******************************************************************************/

typedef struct
{
    HANDLE_T                     h_canvas;
    HANDLE_T                     h_frm_main;

    MMP_VE_PLAY_INST_PTR_T       pv_engine_inst;
    MMP_TOOLBAR_INST_PTR_T       pv_toolbar_inst;
    MMP_COM_UI_DP_VIEW_PTR_T     pv_detail_page_inst;

    MMP_AP_CTRL_PANEL_INST_T     pv_ctrl_panel_inst;
    MMP_COM_FP_INFO_UI_TYPE_T    e_ctrl_panel_type;

    MMP_FOCUS_INFO_INST_T        pv_focus_info_inst;
    MMP_COM_FP_INFO_UI_TYPE_T    e_focus_info_type;
    HANDLE_T                     h_mmp_fb_eq;

    HANDLE_T                     h_option_list;
    HANDLE_T                     h_lyric_option;

    HANDLE_T                     h_iom;
    HANDLE_T                     h_svctx;

    HANDLE_T                     h_timer_invaid_file_msg;
    HANDLE_T                     h_timer_timeout;
    HANDLE_T                     h_timer_msg;
    HANDLE_T                     h_timer_load_file_cover;
    MMP_REPEAT_MODE_T            e_repeat_mode;
    MMP_SHUFFLE_MODE_T           e_shuffle_mode;
    MMP_VE_CTNT_RPT_TYPE_T       e_repeat_ab;
    MMP_AP_DETAIL_PAGE_STATUS_T  e_detail_page;
    MMP_VE_PLAY_STAT_T           e_player_status;

    mmp_fp_show_nfy_fct          pf_fp_show_nfy_fct;
    mmp_fp_info_nfy_fct          pf_info_nfy_fct;

    VOID*                        pv_mmp_tag;
    VOID*                        pv_info_tag;

    UINT8                        ui1_speed;
    UINT8                        ui1_step;

    UINT16                       ui2_lang;

    UINT32                       ui4_mmc_ver;
    UINT32                       ui4_total_file_num;
    UINT32                       ui4_cur_file_idx;
    UINT32                       ui4_flag;

    UINT64                       ui8_duration;
    UINT64                       ui8_position;
    UINT64                       ui8_last_seek_position;

    BOOL                         b_crt_play_invalid_file;
    BOOL                         b_code_not_support;
    BOOL                         b_has_cover_pic;
    BOOL                         b_ctrl_panel_show;
    BOOL                         b_msg_show;
    BOOL                         b_end_of_list;

    _MMP_AP_LAST_OPEN_ELM_RET_T  e_last_open_elm_ret;

#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
    HANDLE_T                     h_eq_viewer;
    BOOL                         b_eq_viewer_show;
#endif

#ifdef    _MMP_VERC_PLAY_COVER_SUPPORT
    HANDLE_T                     h_transparent_list;
#endif
    HANDLE_T                     h_audio_play_img_fr;

}   AUDIO_PLAYER_VIEW_T;


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static AUDIO_PLAYER_VIEW_T    t_g_audio_view = {0};

static UINT32 ui4_g_filted_btns[] = MMP_AP_RC_GET_FILTED_BTN();

static UTF16_T w2s_g_file[MMP_AP_RC_FILE_MAX_LEN] = {0}; /* current file's name */
static UTF16_T w2s_g_file_next[MMP_AP_RC_FILE_MAX_LEN] = {0}; /* next file's name    */
static UTF16_T w2s_g_album[MMP_AP_INFO_MAX_STR_LEN] = {0}; /* current album name */
static UTF16_T w2s_g_artist[MMP_AP_INFO_MAX_STR_LEN] = {0}; /* current artist name */

static MM_SBTL_DISP_MODE_T         t_disp_mode    = MM_SBTL_DISP_MODE_MULTI_LINE;
static MM_SBTL_TIME_OFST_T         t_time_mode    = MM_SBTL_TIME_OFST_AUTO;
static MM_SBTL_FONT_ENC_T          t_encode_mode  = MM_SBTL_FONT_ENC_AUTO;

/*-----------------------------------------------------------------------------
                    Function declarations
-----------------------------------------------------------------------------*/
static VOID  _audio_player_timer_nfy_fct(
                    HANDLE_T                        h_timer,
                    VOID*                           pv_tag
                    );
static INT32 _audio_player_opt_select_set_item (VOID);

static INT32 _audio_player_info_handle_get_custom_info (VOID);

static INT32 _audio_player_info_handle_update_custom_info(BOOL b_repaint);

static INT32 _audio_player_view_update_pos(UINT64  ui8_day_sec, BOOL b_repaint);

INT32 a_mmp_audio_show_playback_info(BOOL b_show);

static VOID _mmp_ap_update_play_status()
{
    UINT32 ui4_sel_idx;

    if(MMPR_OK == mmp_mc_list_get_idx(MMP_GROUND_MODE_BACK,MMP_PL_IDX_TYPE_CRNT_PLAY,&ui4_sel_idx))
    {
        a_mmp_audio_show_playback_info(TRUE);
        mmp_lm_update_file_status(ui4_sel_idx);
    }
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_show_msg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_show_msg(UTF16_T*    ws_msg)
{
    INT32 i4_ret = 0;

    i4_ret = mmp_info_bar_set_status_msg(MMP_IB_MSG_CLASS_INFO,
                                         MMP_IB_STATUS_MSG_TYPE_FILE_STATUS,
                                         MMP_IB_STATUS_MSG_ID_FILE_STATUS,
                                         ws_msg);
    MMPR_LOG_ON_FAIL(i4_ret);

    t_g_audio_view.b_msg_show = TRUE;

    i4_ret = c_timer_start(t_g_audio_view.h_timer_msg,
                           MMP_AP_TIMER_HIDE_MSG,
                           X_TIMER_FLAG_ONCE,
                           _audio_player_timer_nfy_fct,
                           NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_play_pause
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_play_pause(VOID)
{
    INT32                  i4_ret;

    t_g_audio_view.e_player_status = video_engine_get_state(
                                                t_g_audio_view.pv_engine_inst
                                                );


    if (MMP_VE_PLAY_STAT_PLAY != t_g_audio_view.e_player_status &&
        MMP_VE_PLAY_STAT_PAUSE != t_g_audio_view.e_player_status&&
        MMP_VE_PLAY_STAT_STOP != t_g_audio_view.e_player_status &&
        MMP_VE_PLAY_STAT_FAST_FWD != t_g_audio_view.e_player_status &&
        MMP_VE_PLAY_STAT_FAST_RWD != t_g_audio_view.e_player_status)
    {
        DBG_LOG_PRINT(("File status not support this operation%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
        return MMPR_OK;
    }

#ifdef NEVER
    if(t_g_audio_view.b_crt_play_invalid_file)
    {
        if(MMP_VE_PLAY_STAT_STOP != t_g_audio_view.e_player_status)
        {
            DBG_LOG_PRINT(("File not play normal, not support %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
            return MMPR_OK;
        }
    }

    if(MMP_AP_FLAG_SEEKING&t_g_audio_view.ui4_flag)
    {
        DBG_LOG_PRINT(("Invalide key while Seeking%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
        return MMPR_OK;
    }
#endif /* NEVER */

    if(t_g_audio_view.b_msg_show)
    {
        t_g_audio_view.b_msg_show = FALSE;
        i4_ret = mmp_info_bar_hide();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    switch (t_g_audio_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_PLAY:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T  w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif
            i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_BACK);
            if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PAUSED)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_VE_PLAY_STAT_PAUSE:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T  w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

            i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_BACK, MMP_PLAY_IDX_CURRENT);
            if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PLAYED)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        default:
        {
          #ifdef APP_TTS_SUPPORT
            UTF16_T  w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
          #endif

            i4_ret =  mmp_mc_list_play(MMP_GROUND_MODE_BACK, MMP_PLAY_IDX_CURRENT);
            if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PLAYED)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }

        break;
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_play_pause_process
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_play_pause_process(BOOL   b_play_key)
{
    INT32                  i4_ret;

    if (MMP_VE_PLAY_STAT_PLAY != t_g_audio_view.e_player_status &&
        MMP_VE_PLAY_STAT_PAUSE != t_g_audio_view.e_player_status&&
        MMP_VE_PLAY_STAT_STOP != t_g_audio_view.e_player_status &&
        MMP_VE_PLAY_STAT_FAST_FWD != t_g_audio_view.e_player_status &&
        MMP_VE_PLAY_STAT_FAST_RWD != t_g_audio_view.e_player_status)
    {
        DBG_LOG_PRINT(("File status not support this operation%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
        return MMPR_OK;
    }

    if(t_g_audio_view.b_crt_play_invalid_file)
    {
        if(MMP_VE_PLAY_STAT_STOP != t_g_audio_view.e_player_status)
        {
            DBG_LOG_PRINT(("File not play normal, not support %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
            return MMPR_OK;
        }
    }

    if(MMP_AP_FLAG_SEEKING&t_g_audio_view.ui4_flag)
    {
        DBG_LOG_PRINT(("Invalide key while Seeking%s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
        return MMPR_OK;
    }

    if(t_g_audio_view.b_msg_show)
    {
        t_g_audio_view.b_msg_show = FALSE;
        i4_ret = mmp_info_bar_hide();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    switch (t_g_audio_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_PLAY:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T  w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif
            i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_BACK);
            if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PAUSED)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_VE_PLAY_STAT_PAUSE:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T  w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif
            i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_BACK, MMP_PLAY_IDX_CURRENT);
            if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PLAYED)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_VE_PLAY_STAT_FAST_FWD:
        case MMP_VE_PLAY_STAT_FAST_RWD:
        {
            if(b_play_key)
            {
                i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_BACK, MMP_PLAY_IDX_CURRENT);
            }
            else
            {
                i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_BACK);
            }
            if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PAUSED)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
            break;

        default:
        {
            i4_ret =  mmp_mc_list_play(MMP_GROUND_MODE_BACK, MMP_PLAY_IDX_CURRENT);
            if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PLAYED)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }

        break;
    }
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_get_info_type
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_get_info_type(MMP_DP_LBL_ID_T e_id,
                                    MMP_VE_INFO_ID_PTR_T  pe_type)
{
    switch(e_id)
    {
        case MMP_AP_RC_DP_LBL_ID_TITLE:
            *pe_type = MMP_VE_INFO_ID_TITLE;
            break;

        case MMP_AP_RC_DP_LBL_ID_ARTIST:
            *pe_type = MMP_VE_INFO_ID_ARTIST;
            break;

        case MMP_AP_RC_DP_LBL_ID_ALBUM:
            *pe_type = MMP_VE_INFO_ID_ALBUM;
            break;

        case MMP_AP_RC_DP_LBL_ID_GENRE:
            *pe_type = MMP_VE_INFO_ID_GENRE;
            break;

        case MMP_AP_RC_DP_LBL_ID_YEAR:
            *pe_type = MMP_VE_INFO_ID_YEAR;
            break;

        case MMP_AP_RC_DP_LBL_ID_DURATION:
            *pe_type = MMP_VE_INFO_ID_DURATION;
            break;

        case MMP_AP_RC_DP_LBL_ID_NEXT:
            *pe_type = MMP_VE_INFO_ID_INVAL;
            break;
        default:
            break;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_view_set_fileidx
 *
 * Description: update the file index on the status bar.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_set_fileidx(BOOL b_repaint)
{
    INT32            i4_ret = 0;
    UTF16_T          w2s_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
    CHAR             sz_info[MMP_AP_INFO_MAX_STR_LEN]={0};

    /*File num*/
    c_memset(w2s_info, 0, sizeof(w2s_info));
    c_memset(sz_info, 0, sizeof(sz_info));

    i4_ret = mmp_util_get_full_item_count(MMP_GROUND_MODE_BACK,
                                         &(t_g_audio_view.ui4_total_file_num) );
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_util_get_full_item_idx(MMP_GROUND_MODE_BACK,
                                        MMP_PL_IDX_TYPE_CRNT_PLAY,
                                        &(t_g_audio_view.ui4_cur_file_idx));
    MMPR_LOG_ON_FAIL(i4_ret);

    /*Begin is zero*/
    t_g_audio_view.ui4_cur_file_idx++;

    if(t_g_audio_view.ui4_cur_file_idx>t_g_audio_view.ui4_total_file_num)
    {
        t_g_audio_view.ui4_cur_file_idx = t_g_audio_view.ui4_total_file_num;
    }

    c_sprintf(sz_info,
              "%d/%d",
              (t_g_audio_view.ui4_cur_file_idx),
              t_g_audio_view.ui4_total_file_num );

    c_uc_ps_to_w2s(sz_info, w2s_info, MMP_AP_INFO_MAX_STR_LEN);

    i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                       MMP_AP_TB_CMD_SET_FILEIDX,
                                       (VOID*)w2s_info,
                                       (b_repaint?MMP_TB_SYNC_REPAINT:MMP_TB_NON_REPAINT));
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_manaul_next
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_manaul_next(VOID)
{
    MMP_PL_CMD_NEXT_PARAM_T t_param = {MMP_GROUND_MODE_BACK, TRUE};

    if((MMP_VE_PLAY_STAT_OPEN == t_g_audio_view.e_player_status) ||
       (MMP_VE_PLAY_STAT_NEXT == t_g_audio_view.e_player_status))
    {
        return MMPR_OK;
    }

    MMPR_LOG_ON_FAIL( mmp_mc_file_stop( MMP_GROUND_MODE_BACK));
    _mmp_ap_update_play_status();
    return mmp_mc_list_next_ex(&t_param);
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_manaul_prev
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_manaul_prev(VOID)
{
    MMP_PL_CMD_NEXT_PARAM_T t_param = {MMP_GROUND_MODE_BACK, TRUE};

    if((MMP_VE_PLAY_STAT_OPEN == t_g_audio_view.e_player_status) ||
       (MMP_VE_PLAY_STAT_NEXT == t_g_audio_view.e_player_status))
    {
        return MMPR_OK;
    }

    MMPR_LOG_ON_FAIL( mmp_mc_file_stop( MMP_GROUND_MODE_BACK));
    _mmp_ap_update_play_status();
    return mmp_mc_list_previous_ex(&t_param);
}

#if 1
/*----------------------------------------------------------------------------
 * Name: _audio_player_seek_begin
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_seek_begin(BOOL b_fseek, BOOL b_repeat)
{
    INT32            i4_ret = 0;

    if(t_g_audio_view.b_crt_play_invalid_file)
    {
        DBG_LOG_PRINT(("File not play normal, not support seek\n"));
        return MMPR_OK;
    }

    if(t_g_audio_view.e_player_status != MMP_VE_PLAY_STAT_PLAY &&
       t_g_audio_view.e_player_status != MMP_VE_PLAY_STAT_PAUSE )
    {
        DBG_LOG_PRINT(("Play status not support seek\n"));
        return MMPR_OK;
    }

    if(MMP_VE_CTNT_RPT_TYPE_NONE != t_g_audio_view.e_repeat_ab)
    {
        DBG_LOG_PRINT(("Rpeat AB, not support seek\n"));
        return MMPR_OK;
    }

    /*Seek not ready, can't seek again*/
    if(MMP_AP_FLAG_SEEKING&t_g_audio_view.ui4_flag)
    {
        DBG_LOG_PRINT(("Seek not ready, can't seek again\n"));
        return MMPR_OK;
    }

    /*Play and End of File*/
    if(t_g_audio_view.ui8_duration == t_g_audio_view.ui8_position &&
       t_g_audio_view.e_player_status == MMP_VE_PLAY_STAT_PLAY)
    {
        DBG_LOG_PRINT(("End of file, can't seek\n"));
        return MMPR_OK;
    }

    /*Turn on flag*/
    t_g_audio_view.ui4_flag |= MMP_AP_FLAG_SEEKING_BEGIN;

    /* stop h_timer_timeout */
    i4_ret = c_timer_stop(t_g_audio_view.h_timer_timeout);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*When seek:if it is play -> Pause it*/
    if(MMP_VE_PLAY_STAT_PLAY==t_g_audio_view.e_player_status)
    {
        /*Turn on flag*/
        t_g_audio_view.ui4_flag |= MMP_AP_FLAG_PLAY_BEFORE_SEEK;

        i4_ret = _audio_player_play_pause();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if(b_fseek)
    {
        t_g_audio_view.ui8_position = t_g_audio_view.ui8_position + MMP_AP_SEEK_DUR;
        if(t_g_audio_view.ui8_position>t_g_audio_view.ui8_duration)
        {
            t_g_audio_view.ui8_position = t_g_audio_view.ui8_duration;
        }
    }
    else
    {
        if(t_g_audio_view.ui8_position>=MMP_AP_SEEK_DUR)
        {
            t_g_audio_view.ui8_position = t_g_audio_view.ui8_position - MMP_AP_SEEK_DUR;
        }
        else
        {
            t_g_audio_view.ui8_position = 0;
        }
    }

    MMP_DBG_INFO(("View pos:%lld\n", t_g_audio_view.ui8_position));

    i4_ret = _audio_player_view_update_pos(t_g_audio_view.ui8_position, TRUE);
    IS_MMPR_OK(i4_ret);

    return MMPR_OK;
}
#endif
/*----------------------------------------------------------------------------
 * Name: _audio_player_seek_end
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_seek_end(BOOL b_fseek)
{
    INT32            i4_ret = 0;
    BOOL             b_reset = FALSE;

    do
    {
        if(t_g_audio_view.b_crt_play_invalid_file)
        {
            DBG_LOG_PRINT(("File not play normal, not support seek\n"));
            b_reset = TRUE;
            break;
        }

        if(t_g_audio_view.e_player_status != MMP_VE_PLAY_STAT_PLAY &&
           t_g_audio_view.e_player_status != MMP_VE_PLAY_STAT_PAUSE )
        {
            DBG_LOG_PRINT(("File status not support seek\n"));
            b_reset = TRUE;
            break;
        }

        if(MMP_AP_FLAG_SEEKING&t_g_audio_view.ui4_flag)
        {
            DBG_LOG_PRINT(("Seeking not support seek again\n"));
            b_reset = FALSE;
            break;
        }

        if(t_g_audio_view.ui8_position!=0 &&
           t_g_audio_view.ui8_last_seek_position==t_g_audio_view.ui8_position)
        {
            DBG_LOG_PRINT(("Seeking position is same with last seek\n"));
            b_reset = TRUE;
            break;
        }

        if(MMP_VE_CTNT_RPT_TYPE_NONE!=t_g_audio_view.e_repeat_ab)
        {
            DBG_LOG_PRINT(("Repeat AB not support seek\n"));
            b_reset = TRUE;
            break;
        }

    }while(0);

    if(b_reset)
    {
             /*Keep before status when seek ready*/
        if(MMP_AP_FLAG_PLAY_BEFORE_SEEK&t_g_audio_view.ui4_flag)
        {
            if(MMP_VE_PLAY_STAT_PAUSE == t_g_audio_view.e_player_status)
            {
                i4_ret = _audio_player_play_pause();
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }

        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_SEEKING
                                     |MMP_AP_FLAG_SEEKING_BEGIN
                                     |MMP_AP_FLAG_PLAY_BEFORE_SEEK);
        return MMPR_OK;
    }


    t_g_audio_view.ui8_last_seek_position = t_g_audio_view.ui8_position;

    /*Turn on flag*/
    t_g_audio_view.ui4_flag |= MMP_AP_FLAG_SEEKING;

    MMP_DBG_INFO(("MW seek pos :%lld\n", t_g_audio_view.ui8_position));

    i4_ret = video_engine_seek(t_g_audio_view.pv_engine_inst,
                               (UINT32)t_g_audio_view.ui8_position);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _audio_player_view_set_ab_repeat(BOOL    b_reset,
                                              BOOL    b_repaint)
{
    UINT32 ui4_param = (UINT32)0;
    INT32 i4_ret = 0;

    if(b_reset)
    {
        t_g_audio_view.e_repeat_ab = MMP_VE_CTNT_RPT_TYPE_NONE;
    }
    else
    {
    i4_ret = video_engine_get_ctnt_repeat(
                    t_g_audio_view.pv_engine_inst,
                    &(t_g_audio_view.e_repeat_ab));
    MMPR_LOG_ON_FAIL(i4_ret);
    }


    if(t_g_audio_view.b_ctrl_panel_show)
    {
        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_AB,
                                             (VOID*)t_g_audio_view.e_repeat_ab,
                                             TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
        return MMPR_OK;
    }
    else
    {
        switch(t_g_audio_view.e_repeat_ab)
        {
            case MMP_VE_CTNT_RPT_TYPE_NONE:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_REPEAT_AB_NONE;
            }
            break;

            case MMP_VE_CTNT_RPT_TYPE_PT_A:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_REPEAT_AB_A;
            }
            break;

            case MMP_VE_CTNT_RPT_TYPE_PT_B:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_REPEAT_AB_AB;
            }
            break;

            default:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_REPEAT_AB_NONE;
            }
            break;
        }

        i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                              MMP_AP_TB_CMD_SET_REPEAT_AB,
                                              (VOID*)ui4_param,
                                              b_repaint?MMP_TB_SYNC_REPAINT:MMP_TB_NON_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_manaul_next
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_set_play_status(BOOL b_reset,
                                                BOOL b_repaint)
{
    UINT32 ui4_param = 0;
    INT32  i4_ret = 0;
    BOOL    b_fast_status=FALSE;

    if(b_reset)
    {
        t_g_audio_view.e_player_status = MMP_VE_PLAY_STAT_BLANK;
    }
    else
    {
        t_g_audio_view.e_player_status = video_engine_get_state(
                                                    t_g_audio_view.pv_engine_inst
                                                    );
    }


    switch(t_g_audio_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_PLAY:
        {
            if(t_g_audio_view.b_crt_play_invalid_file)
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_DEFAULT;
            }
            else
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_PLAY;
            }
        }
        break;

        case MMP_VE_PLAY_STAT_PAUSE:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_PAUSE;
        }
        break;

        case MMP_VE_PLAY_STAT_STOP:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_STOP;

            i4_ret = _audio_player_view_set_ab_repeat(TRUE, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = _audio_player_view_update_pos(0, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);

            if(t_g_audio_view.b_msg_show)
            {
                t_g_audio_view.b_msg_show = FALSE;
                i4_ret = mmp_info_bar_hide();
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_VE_PLAY_STAT_OPEN:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_DEFAULT;
        }
        break;

        case MMP_VE_PLAY_STAT_NEXT:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_DEFAULT;
        }
        break;

        case MMP_VE_PLAY_STAT_UNSUP:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_DEFAULT;
        }
        break;

        case MMP_VE_PLAY_STAT_BLANK:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_DEFAULT;
        }
        break;

        case MMP_VE_PLAY_STAT_FAST_FWD:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_FAST_FOR;
            b_fast_status = TRUE;

            i4_ret = mmp_common_ui_toolbar_cmd_do(
                    t_g_audio_view.pv_toolbar_inst,
                    MMP_AP_TB_CMD_SET_FF,
                    (VOID*)(UINT32)t_g_audio_view.ui1_step,
                    (b_repaint ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT)
                    );
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        case MMP_VE_PLAY_STAT_FAST_RWD:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_FAST_REW;
            b_fast_status = TRUE;

            i4_ret = mmp_common_ui_toolbar_cmd_do(
                    t_g_audio_view.pv_toolbar_inst,
                    MMP_AP_TB_CMD_SET_FR,
                    (VOID*)(UINT32)t_g_audio_view.ui1_step,
                    (b_repaint ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT)
                    );
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        case MMP_VE_PLAY_STAT_CLOSE:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_DEFAULT;
        }
        break;
        default:
        {
            ui4_param = (UINT32)MMP_AP_TB_STATUS_DEFAULT;
        }
        break;
    }

    if(!b_fast_status)
    {
        i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                              MMP_AP_TB_CMD_SET_PLAY_STATUS,
                                              (VOID*)ui4_param,
                                              (b_repaint?MMP_TB_SYNC_REPAINT:MMP_TB_NON_REPAINT));
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_view_repeat_icon_update
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_repeat_icon_update(BOOL b_repaint)
{
    UINT32       ui4_param = 0;
    INT32        i4_ret = 0;

    if(t_g_audio_view.b_ctrl_panel_show)
    {
        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_REPEAT,
                                             (VOID*)t_g_audio_view.e_repeat_mode,
                                             b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);
        return MMPR_OK;
    }
    else
    {
        switch(t_g_audio_view.e_repeat_mode)
        {
            case MMP_REPEAT_MODE_NONE:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_REPEAT_NONE;
            }
            break;

            case MMP_REPEAT_MODE_ONE:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_REPEAT_ONE;
            }
            break;

            case MMP_REPEAT_MODE_ALL:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_REPEAT_ALL;
            }
            break;

            default:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_REPEAT_NONE;
            }
            break;
        }

        i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                              MMP_AP_TB_CMD_SET_REPEAT,
                                              (VOID*)ui4_param,
                                              (b_repaint?MMP_TB_SYNC_REPAINT:MMP_TB_NON_REPAINT));
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_is_repeated_btn
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _audio_player_is_repeated_btn(UINT32     ui4_key_code,
                                          UINT32     ui4_key_tick)
{
    INT32 i = 0;
    BOOL  b_repeated = FALSE;
    UINT32 ui4_tick_period = 0;
    UINT32 ui4_tm_old = 0;
    UINT32 ui4_tm_new = 0;

    if(0 == ui4_key_tick)
    {
        return FALSE;
    }

    for(i = 0; 0 != ui4_g_filted_btns[i]; ++i)
    {
        if(ui4_key_code == ui4_g_filted_btns[i])
        {
            /**/
            ui4_tick_period = c_os_get_sys_tick_period();
            ui4_tm_old = ui4_tick_period * ui4_key_tick;
            ui4_tm_new = ui4_tick_period * c_os_get_sys_tick();

            if ((ui4_tm_new - ui4_tm_old)> 50)
            {
                b_repeated = TRUE;
            }
        }
    }
    return b_repeated;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_view_shuffle_icon_update
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_shuffle_icon_update(BOOL b_repaint)
{
    UINT32  ui4_param = 0;
    INT32   i4_ret = 0;

    if(t_g_audio_view.b_ctrl_panel_show)
    {
        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_SHUFFLE,
                                             (VOID*)t_g_audio_view.e_shuffle_mode,
                                             b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);
        return MMPR_OK;
    }
    else
    {
        switch(t_g_audio_view.e_shuffle_mode)
        {
            case MMP_SHUFFLE_MODE_SEQUENTIAL:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_SHUFFLE_MODE_SEQUENTIAL;
            }
            break;

            case MMP_SHUFFLE_MODE_SHUFFLE:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_SHUFFLE_MODE_SHUFFLE;
            }
            break;

            default:
            {
                ui4_param = (UINT32)MMP_AP_TB_STATUS_SHUFFLE_MODE_SEQUENTIAL;
            }
            break;
        }

        i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                              MMP_AP_TB_CMD_SET_SHUFFLE,
                                              (VOID*)ui4_param,
                                              (b_repaint?MMP_TB_SYNC_REPAINT:MMP_TB_NON_REPAINT));
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _disable_key
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32  _disable_key(VOID)
{
    SIZE_T z_info_len = 0;
    UINT64 ui8_evt_src = 0;
    /* Disable Remote control. */
    z_info_len = sizeof (UINT64);
    c_iom_get (t_g_audio_view.h_iom,
               IOM_GET_IRRC_EVT_SRC_MASK,
               (VOID*)& ui8_evt_src,
               & z_info_len);

    ui8_evt_src &= ~(IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL) |
                     IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL));

    c_iom_set (t_g_audio_view.h_iom,
               IOM_SET_IRRC_EVT_SRC_MASK,
               (VOID*)& ui8_evt_src,
               sizeof (UINT64));

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_aud_only
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_aud_only (VOID* pv_tag)
{
    INT32 i4_ret = 0;

    SM_COMMAND_T     at_scc_cmds [4];

    c_memset(at_scc_cmds, 0, sizeof(at_scc_cmds));

    DBG_LOG_PRINT(("Turn off backlight & LVDS \n"));
     /* Turn off backlight & LVDS */
    at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
    at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_DISP;
    at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
    at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
    at_scc_cmds [2].e_code      = SCC_CMD_CODE_DISP_CTRL;
    at_scc_cmds [2].u.ui4_data  = SCC_DISP_CTRL_DISABLE;

    at_scc_cmds [3].e_code      = SM_CMD_CODE_END;
    c_scc_comp_grp_set (at_scc_cmds);

    c_svctx_set_video_plane (t_g_audio_view.h_svctx, SCC_VID_NORMAL);

    /*Turn on flag*/
    t_g_audio_view.ui4_flag |= MMP_AP_FLAG_AUD_ONLY;

    i4_ret = _disable_key();
    MMPR_LOG_ON_FAIL(i4_ret);

    /*Turn off flag*/
    t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;
    i4_ret = a_optl_hide(t_g_audio_view.h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main, WGL_NO_AUTO_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_view_refresh_detail_page
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_refresh_detail_page(BOOL b_repaint)
{
    CHAR     sz_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
    UTF16_T  w2s_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
    SIZE_T   z_buf_len = 0;
    MMP_VE_INFO_ID_T  e_info_type = MMP_VE_INFO_ID_INVAL;
    UINT8    ui1_hh = 0, ui1_mm = 0, ui1_ss = 0;
    UINT8    ui1_indx = 0;
    INT32    i4_ret = 0;

    i4_ret = mmp_com_ui_dp_set_text_ex(t_g_audio_view.pv_detail_page_inst,
                                     MMP_AP_RC_DP_LBL_ID_NEXT,
                                     w2s_g_file_next,
                                     COM_UI_NON_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    for(ui1_indx = 0; ui1_indx < MMP_AP_RC_DP_LBL_COUNT; ui1_indx++)
    {
        i4_ret = _audio_player_get_info_type((MMP_DP_LBL_ID_T)(ui1_indx + MMP_AP_RC_DP_LBL_ID_TITLE),
                                            &e_info_type);
        MMPR_LOG_ON_FAIL(i4_ret);

        c_memset(w2s_info, 0, sizeof(w2s_info));

        if(MMP_VE_INFO_ID_INVAL == e_info_type)
        {
           continue;
        }
        if(MMP_VE_INFO_ID_DURATION == e_info_type)
        {
            /*Not support*/
            if(0==t_g_audio_view.ui8_duration)
            {
                c_strncpy(sz_info, "N/A", MMP_AP_INFO_MAX_STR_LEN);
            }
            else
            {
                i4_ret = mmp_util_sec_to_hh_mm_ss(t_g_audio_view.ui8_duration,
                                                 &ui1_hh,
                                                 &ui1_mm,
                                                 &ui1_ss);
                MMPR_LOG_ON_FAIL(i4_ret);

                c_sprintf(sz_info,
                          "%02u:%02u:%02u",
                          ui1_hh,
                          ui1_mm,
                          ui1_ss);
            }

            i4_ret =c_uc_ps_to_w2s(sz_info, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
            i4_ret = video_engine_get_dtl_info(
                              t_g_audio_view.pv_engine_inst,
                              e_info_type,
                              w2s_info,
                              &z_buf_len);
            MMPR_LOG_ON_FAIL(i4_ret);
            if(MMPR_OK != i4_ret ||
               0 == z_buf_len ||
               0==w2s_info[0])
            {
                c_uc_ps_to_w2s("N/A", w2s_info, MMP_AP_INFO_MAX_STR_LEN);
            }
        }

        i4_ret = mmp_com_ui_dp_set_text_ex(t_g_audio_view.pv_detail_page_inst,
                               (MMP_DP_LBL_ID_T)(ui1_indx + MMP_AP_RC_DP_LBL_ID_TITLE),
                               w2s_info,
                               COM_UI_SYNC_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);

    }

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(t_g_audio_view.h_frm_main, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_show_detail
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_show_detail(VOID* pv_tag)
{
    INT32 i4_ret = 0;

    if(MMP_AP_DETAIL_PAGE_OFF==t_g_audio_view.e_detail_page)
    {
        t_g_audio_view.e_detail_page = MMP_AP_DETAIL_PAGE_ON;

        i4_ret = _audio_player_view_refresh_detail_page(FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_com_ui_dp_view_active_ex(t_g_audio_view.pv_detail_page_inst,
                                            COM_UI_NON_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret)
    }
    else
    {
        t_g_audio_view.e_detail_page = MMP_AP_DETAIL_PAGE_OFF;

        i4_ret = mmp_com_ui_dp_view_inactive_ex(t_g_audio_view.pv_detail_page_inst,
                                           COM_UI_NON_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret)
    }
    /*Turn off flag*/
    t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;

    i4_ret = c_wgl_set_visibility(t_g_audio_view.h_option_list,
                                 WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_g_audio_view.h_frm_main, NULL, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main,
                             WGL_NO_AUTO_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_audio_repeat_setting
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_audio_repeat_setting(VOID* pv_tag)
{
    MMP_PL_ATTR_T           at_attr[2];
    UINT32                  ui4_index=(UINT32)pv_tag;
    INT32                   i4_ret = 0;

    c_memset(at_attr, 0, sizeof(at_attr));

    switch(ui4_index)
    {
        case 0:
            t_g_audio_view.e_repeat_mode = MMP_REPEAT_MODE_NONE;
            break;
        case 1:
            t_g_audio_view.e_repeat_mode = MMP_REPEAT_MODE_ONE;
            break;
        case 2:
            t_g_audio_view.e_repeat_mode = MMP_REPEAT_MODE_ALL;
            break;
        default:
            MMP_ASSERT(0);
            break;
    }

    at_attr[0].e_id = MMP_PL_ATTR_ID_BK_REPEAT;
    at_attr[0].pv_param = (VOID*) t_g_audio_view.e_repeat_mode;
    at_attr[1].e_id = MMP_PL_ATTR_ID_BK_SHUFFLE;
    at_attr[1].pv_param = (VOID*) t_g_audio_view.e_shuffle_mode;

    i4_ret =  mmp_mc_list_set_attr(2, at_attr);
    if(MMPR_OK != i4_ret && MMPR_IS_PRELOADED != i4_ret)
    {
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret =  _audio_player_view_repeat_icon_update(TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*Refresh deatil in next preload*/
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_shuffle_setting
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_shuffle_setting(VOID* pv_tag)
{
    MMP_PL_ATTR_T           at_attr[2];
    INT32                   i4_ret = 0;
    UINT16                  ui2_hlt_idx_1 = 0, ui2_hlt_idx_2 = 0;

    c_memset(at_attr, 0, sizeof(at_attr));

    if(MMP_SHUFFLE_MODE_SEQUENTIAL == t_g_audio_view.e_shuffle_mode)/*On*/
    {
        t_g_audio_view.e_shuffle_mode = MMP_SHUFFLE_MODE_SHUFFLE;
    }
    else
    {
        t_g_audio_view.e_shuffle_mode = MMP_SHUFFLE_MODE_SEQUENTIAL;
    }

    at_attr[0].e_id = MMP_PL_ATTR_ID_BK_REPEAT;
    at_attr[0].pv_param = (VOID*) t_g_audio_view.e_repeat_mode;
    at_attr[1].e_id = MMP_PL_ATTR_ID_BK_SHUFFLE;
    at_attr[1].pv_param = (VOID*) t_g_audio_view.e_shuffle_mode;

    i4_ret =  mmp_mc_list_set_attr(2, at_attr);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_view_shuffle_icon_update(FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_get_hlt_index(t_g_audio_view.h_option_list,
                         &ui2_hlt_idx_1,
                         &ui2_hlt_idx_2);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_opt_select_set_item();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_hlt_index(t_g_audio_view.h_option_list,
                         ui2_hlt_idx_1,
                         ui2_hlt_idx_2);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_g_audio_view.h_frm_main, NULL, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);
    /*Turn on flag*/
    t_g_audio_view.ui4_flag |= MMP_AP_FLAG_OPTION_LIST_SHOW;
    i4_ret = a_optl_show(t_g_audio_view.h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);
    return MMPR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_opt_select_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_opt_select_show (VOID)
{
    INT32   i4_ret = 0;

    if(MMP_VE_PLAY_STAT_PLAY != t_g_audio_view.e_player_status &&
       MMP_VE_PLAY_STAT_PAUSE != t_g_audio_view.e_player_status &&
       MMP_VE_PLAY_STAT_STOP != t_g_audio_view.e_player_status &&
       MMP_VE_PLAY_STAT_FAST_FWD != t_g_audio_view.e_player_status &&
       MMP_VE_PLAY_STAT_FAST_RWD != t_g_audio_view.e_player_status)
    {
        DBG_LOG_PRINT(("File status not support option list \n"));
        return MMPR_OK;
    }

    if(t_g_audio_view.b_crt_play_invalid_file)
    {
        DBG_LOG_PRINT(("Music not play,not support this key\n"));
        return MMPR_OK;
    }

    if(t_g_audio_view.b_msg_show)
    {
        t_g_audio_view.b_msg_show = FALSE;
       i4_ret = mmp_info_bar_hide();
       MMPR_LOG_ON_FAIL(i4_ret);
    }

    /*Turn on flag*/
    t_g_audio_view.ui4_flag |= MMP_AP_FLAG_OPTION_LIST_SHOW;

    if(MMP_AP_DETAIL_PAGE_ON==t_g_audio_view.e_detail_page)
    {
        t_g_audio_view.e_detail_page = MMP_AP_DETAIL_PAGE_OFF;

        i4_ret = mmp_com_ui_dp_view_inactive(t_g_audio_view.pv_detail_page_inst);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret =  _audio_player_opt_select_set_item();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_visibility(t_g_audio_view.h_option_list, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_hlt_index(t_g_audio_view.h_option_list,
                                  0,
                                  0);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_focus(t_g_audio_view.h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_repaint(t_g_audio_view.h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_g_audio_view.h_frm_main, NULL, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);
    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_update_status
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_update_status(BOOL b_repaint)
{
    INT32                     i4_ret = 0;

    t_g_audio_view.e_player_status = video_engine_get_state(
                                                t_g_audio_view.pv_engine_inst
                                                );

    DBG_INFO(("t_g_audio_view.e_player_status %d\n", t_g_audio_view.e_player_status));

    switch (t_g_audio_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_PLAY:
        case MMP_VE_PLAY_STAT_FAST_FWD:
        case MMP_VE_PLAY_STAT_FAST_RWD:
        {
            /*Turn off flag*/
            t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_SEEKING
                                       |MMP_AP_FLAG_SEEKING_BEGIN);

            MMP_DBG_INFO(("c_timer_start h_timer_timeout Line%d\n", __LINE__));

#if 0
                        /* Never show time code for DMR */
#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
            if (FALSE == a_mmp_dmr_is_active())
#endif
#endif
            {
                c_timer_start(t_g_audio_view.h_timer_timeout,
                              MMP_AP_TIMER_TIMEOUT_DELAY,
                              X_TIMER_FLAG_REPEAT,
                              _audio_player_timer_nfy_fct,
                              NULL);
            }
            _mmp_ap_update_play_status();
        }
        break;

        default:
        {
            MMP_DBG_INFO(("c_timer_stop h_timer_timeout %d\n", __LINE__));
            c_timer_stop(t_g_audio_view.h_timer_timeout);
        }
        break;
    }

    /*Ctrl panel*/
    if(t_g_audio_view.b_ctrl_panel_show &&
       t_g_audio_view.pv_ctrl_panel_inst)
    {
        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                            MMP_AP_CUR_PLAY_INFO_PLAY_STATUS,
                                           (VOID*)t_g_audio_view.e_player_status,
                                           TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

        if(MMP_VE_PLAY_STAT_STOP == t_g_audio_view.e_player_status)
        {
            i4_ret = _audio_player_view_set_ab_repeat(TRUE, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = _audio_player_view_update_pos(0, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
            _mmp_ap_update_play_status();
        }

        return MMPR_OK;
    }
    else
    {
        i4_ret = _audio_player_view_set_play_status(FALSE, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_play_pause_setting
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_play_pause_setting(VOID* pv_tag)
{
    INT32                  i4_ret = 0;

    i4_ret = _audio_player_play_pause();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_opt_select_show();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_update_status(TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_get_repeat_hlt_idx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_get_repeat_hlt_idx(VOID* pv_tag, UINT16* pui2_repeat_idx)
{

    switch(t_g_audio_view.e_repeat_mode)
    {
        case MMP_REPEAT_MODE_NONE:
            *pui2_repeat_idx = 0;
            break;
        case MMP_REPEAT_MODE_ONE:
            *pui2_repeat_idx = 1;
            break;
        case MMP_REPEAT_MODE_ALL:
            *pui2_repeat_idx = 2;
            break;
        default:
            return MMPR_FAIL;
    }

    return MMPR_OK;
}
#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _audio_player_spectrum_effect_toggle
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_spectrum_effect_toggle(VOID* pv_tag)
{
    INT32 i4_ret = 0;
    UINT16 ui2_hlt_idx_1 = 0, ui2_hlt_idx_2 = 0;

    if(t_g_audio_view.b_eq_viewer_show)
    {
        t_g_audio_view.b_eq_viewer_show = FALSE;
        i4_ret = a_mmp_eq_show(t_g_audio_view.h_eq_viewer, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        t_g_audio_view.b_eq_viewer_show = TRUE;
        i4_ret = a_mmp_eq_show(t_g_audio_view.h_eq_viewer, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret =  a_optl_get_hlt_index(t_g_audio_view.h_option_list,
                         &ui2_hlt_idx_1,
                         &ui2_hlt_idx_2);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_opt_select_set_item();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_hlt_index(t_g_audio_view.h_option_list,
                         ui2_hlt_idx_1,
                         ui2_hlt_idx_2);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_g_audio_view.h_frm_main, NULL, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*Turn on flag*/
    t_g_audio_view.ui4_flag |= MMP_AP_FLAG_OPTION_LIST_SHOW;

    i4_ret = a_optl_show(t_g_audio_view.h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_get_line
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_get_line(VOID* pv_tag, UINT16* pui2_line_idx)
{
    switch(t_disp_mode)
    {
        case MM_SBTL_DISP_MODE_OFF:
            *pui2_line_idx = 0;
            break;
        case MM_SBTL_DISP_MODE_SINGLE_LINE:
            *pui2_line_idx = 1;
            break;
        case MM_SBTL_DISP_MODE_MULTI_LINE:
            *pui2_line_idx = 2;
            break;
        default:
            return MMPR_FAIL;
    }

    return MMPR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_get_time
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_get_time(VOID* pv_tag, UINT16* pui2_time_idx)
{
    MM_SBTL_TIME_OFST_T         e_mode=t_time_mode;

    switch(e_mode)
    {
        case MM_SBTL_TIME_OFST_OFF:
            *pui2_time_idx = 0;
            break;
        case MM_SBTL_TIME_OFST_AUTO:
            *pui2_time_idx = 1;
            break;
        case MM_SBTL_TIME_OFST_USER_DEF:
            *pui2_time_idx = 2;
            break;
        default:
            return MMPR_FAIL;
    }

    return MMPR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_get_encode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_get_encode(VOID* pv_tag, UINT16* pui2_encode_idx)
{
    MM_SBTL_FONT_ENC_T       e_mode = t_encode_mode;

    switch(e_mode)
    {
        case MM_SBTL_FONT_ENC_AUTO:
            *pui2_encode_idx = 0;
            break;
        case MM_SBTL_FONT_ENC_GB:
            *pui2_encode_idx = 1;
            break;
        case MM_SBTL_FONT_ENC_BIG5:
            *pui2_encode_idx = 2;
            break;
        case MM_SBTL_FONT_ENC_UTF8:
            *pui2_encode_idx = 3;
            break;
        case MM_SBTL_FONT_ENC_UTF16:
            *pui2_encode_idx = 4;
            break;
        default:
            return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_set_rect
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_set_rect(VOID* pv_tag)
{
    MMP_VE_SBTL_ATTR_T          t_sbtl_attr;
    MM_SVC_SBTL_DISP_ATTR_T*    pt_nrml_attr = &t_sbtl_attr.u.t_nrml_attr;
    GL_RECT_T*                  pt_sbtl_rect = &pt_nrml_attr->t_disp_rect;
    INT32                       i4_ret = 0;

    c_memset(&t_sbtl_attr, 0, sizeof(MMP_VE_SBTL_ATTR_T));

    t_sbtl_attr.t_attr_type = MMP_VE_SBTL_SET_NRML_ATTR;

    pt_nrml_attr->t_attr_field = MM_SBTL_ATTR_DISP_RECT;

    SET_RECT_BY_SIZE (pt_sbtl_rect,
                      MMP_AP_RC_LYRIC_X,
                      MMP_AP_RC_LYRIC_Y,
                      MMP_AP_RC_LYRIC_W,
                      MMP_AP_RC_LYRIC_H);

    i4_ret = video_engine_set_sub_attr(
                        t_g_audio_view.pv_engine_inst,
                        &t_sbtl_attr
                        );
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_set_line
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_set_line(VOID* pv_tag)
{
    MMP_VE_SBTL_ATTR_T          t_sbtl_attr;
    MM_SVC_SBTL_DISP_MODE_T*    pt_disp_mode = &t_sbtl_attr.u.t_disp_mode;
    INT32                       i4_ret = 0;
    UINT32                      ui4_tmp=0;

    c_memset(&t_sbtl_attr, 0, sizeof(MMP_VE_SBTL_ATTR_T));
    t_sbtl_attr.t_attr_type = MMP_VE_SBTL_SET_DISP_MODE;

    switch ((UINT32)pv_tag)
    {
        case 0:
        {
            ui4_tmp = 0;
            pt_disp_mode->e_disp_mode = MM_SBTL_DISP_MODE_OFF;
            //pt_disp_mode->pv_param = (VOID*)&ui4_tmp;
        }
            break;

        case 1:
        {
            ui4_tmp = 1;
            pt_disp_mode->e_disp_mode = MM_SBTL_DISP_MODE_SINGLE_LINE;
            //pt_disp_mode->pv_param = (VOID*)&ui4_tmp;
        }
            break;

        case 2:
        {
            ui4_tmp = 6;
            pt_disp_mode->e_disp_mode = MM_SBTL_DISP_MODE_MULTI_LINE;
            //pt_disp_mode->pv_param = (VOID*)&ui4_tmp;
        }
            break;

        default:
            MMP_ASSERT(0);
            return MMPR_INV_ARG;
    }

    DBG_INFO(("ui4_tmp=%d\n", ui4_tmp));

    t_disp_mode = pt_disp_mode->e_disp_mode;

    i4_ret = video_engine_set_sub_attr(
                        t_g_audio_view.pv_engine_inst,
                        &t_sbtl_attr
                        );
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_set_time
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_set_time(VOID* pv_tag)
{
    MMP_VE_SBTL_ATTR_T          t_sbtl_attr;
    MM_SVC_SBTL_TIME_OFST_T*    pt_time_ofst = &t_sbtl_attr.u.t_time_ofst;
    INT32                       i4_ret = 0;

    c_memset(&t_sbtl_attr, 0, sizeof(MMP_VE_SBTL_ATTR_T));
    t_sbtl_attr.t_attr_type = MMP_VE_SBTL_SET_TIME_OFST;

    switch ((UINT32)pv_tag)
    {
        case 0:
            pt_time_ofst->e_time_ofst = MM_SBTL_TIME_OFST_OFF;
            pt_time_ofst->ui4_ofst_value = (UINT32)0;
            break;

        case 1:
            pt_time_ofst->e_time_ofst = MM_SBTL_TIME_OFST_AUTO;
            pt_time_ofst->ui4_ofst_value = (UINT32)0;
            break;

        case 2:
            pt_time_ofst->e_time_ofst = MM_SBTL_TIME_OFST_USER_DEF;
            pt_time_ofst->ui4_ofst_value = (UINT32)10000;
            break;

        default:
            MMP_ASSERT(0);
            return MMPR_INV_ARG;
    }
    t_time_mode =pt_time_ofst->e_time_ofst;
    i4_ret = video_engine_set_sub_attr(
                        t_g_audio_view.pv_engine_inst,
                        &t_sbtl_attr
                        );
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_set_font
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_set_font(MM_SBTL_FONT_ENC_T e_fnt)
{
    MMP_VE_SBTL_ATTR_T          t_sbtl_attr;
    MM_SVC_SBTL_DISP_ATTR_T*    pt_nrml_attr = &t_sbtl_attr.u.t_nrml_attr;
    WGL_FONT_INFO_T*            pt_font_info = &pt_nrml_attr->t_font_info;
    INT32                       i4_ret = 0;

    c_memset(&t_sbtl_attr, 0, sizeof(MMP_VE_SBTL_ATTR_T));

    t_sbtl_attr.t_attr_type = MMP_VE_SBTL_SET_NRML_ATTR;

    pt_nrml_attr->t_attr_field = MM_SBTL_ATTR_FNT_INFO;
#if NEVER
    if(MM_SBTL_FONT_ENC_AUTO == e_fnt||
       MM_SBTL_FONT_ENC_UTF8 == e_fnt)
    {
        c_strncpy(pt_font_info->a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    }
    else
    {
        c_strncpy(pt_font_info->a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);
    }
#else
    c_strncpy(pt_font_info->a_c_font_name, SN_FONT_DEFAULT, WGL_MAX_FONT_NAME);

#endif
    pt_font_info->e_font_cmap  = FE_CMAP_ENC_UNICODE;
    pt_font_info->e_font_size  = FE_FNT_SIZE_LARGE;
    pt_font_info->e_font_style = FE_FNT_STYLE_REGULAR;
    pt_font_info->i2_width     = (INT16)0;

    i4_ret = video_engine_set_sub_attr(
                        t_g_audio_view.pv_engine_inst,
                        &t_sbtl_attr
                        );
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_set_encode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_set_encode(VOID* pv_tag)
{
    MMP_VE_SBTL_ATTR_T          t_sbtl_attr;
    MM_SVC_SBTL_FONT_ENC_T*     pt_font_enc = &t_sbtl_attr.u.t_font_enc;
    INT32                       i4_ret = 0;

    c_memset(&t_sbtl_attr, 0, sizeof(MMP_VE_SBTL_ATTR_T));
    t_sbtl_attr.t_attr_type = MMP_VE_SBTL_SET_FONT_ENC;

    switch ((UINT32)pv_tag)
    {
        case 0:
            pt_font_enc->e_enc_type = MM_SBTL_FONT_ENC_AUTO;
            break;

        case 1:
            pt_font_enc->e_enc_type = MM_SBTL_FONT_ENC_GB;
            break;

        case 2:
            pt_font_enc->e_enc_type = MM_SBTL_FONT_ENC_BIG5;
            break;

        case 3:
            pt_font_enc->e_enc_type = MM_SBTL_FONT_ENC_UTF8;
            break;

        case 4:
            pt_font_enc->e_enc_type = MM_SBTL_FONT_ENC_UTF16;
            break;

        default:
            pt_font_enc->e_enc_type = MM_SBTL_FONT_ENC_AUTO;
            break;
    }

    t_encode_mode = pt_font_enc->e_enc_type;

    i4_ret = video_engine_set_sub_attr(
                        t_g_audio_view.pv_engine_inst,
                        &t_sbtl_attr
                        );
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_lyric_set_font(pt_font_enc->e_enc_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _audio_lyric_opt_select_set_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_opt_select_set_item (VOID)
{
    OPTL_ITEM_DEF_T         t_optl_item_def;
    OPTL_ITEM_T             t_optl_item[6];
    OPTL_SUBITEM_T          t_sub_item_line[3];
    OPTL_SUBITEM_T          t_sub_item_time[3];
    OPTL_SUBITEM_T          t_sub_item_encode[5];

    UINT8                   ui2_cnt = 0, ui1_index = 0;
    UINT16                  line_id[] = {MLM_MMP_KEY_LYRIC_LINE_OFF,
                                         MLM_MMP_KEY_LYRIC_LINE_SINGLE,
                                         MLM_MMP_KEY_LYRIC_LINE_MULTI};

    UINT16                  time_id[] = {MLM_MMP_KEY_LYRIC_TIME_OFF,
                                         MLM_MMP_KEY_LYRIC_TIME_AUTO,
                                         MLM_MMP_KEY_LYRIC_TIME_USER};

    UINT16                  encode_id[ ]= {MLM_MMP_KEY_LYRIC_ENCODE_AUTO,
                                           MLM_MMP_KEY_LYRIC_ENCODE_GB,
                                           MLM_MMP_KEY_LYRIC_ENCODE_BIG5,
                                           MLM_MMP_KEY_LYRIC_ENCODE_UTF8,
                                           MLM_MMP_KEY_LYRIC_ENCODE_UTF16};

    c_memset(&t_optl_item_def, 0, sizeof(OPTL_ITEM_DEF_T));

    c_memset(t_optl_item, 0, sizeof(t_optl_item));
    c_memset(t_sub_item_line, 0, sizeof(t_sub_item_line));
    c_memset(t_sub_item_time, 0, sizeof(t_sub_item_time));
    c_memset(t_sub_item_encode, 0, sizeof(t_sub_item_encode));

    /*sub item line mode*/
    for(ui1_index = 0; ui1_index < 3; ui1_index++)
    {
        t_sub_item_line[ui1_index].pf_fct = _audio_lyric_set_line;
        t_sub_item_line[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
        t_sub_item_line[ui1_index].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, line_id[ui1_index]);
    }

    /*sub item time mode*/
    for(ui1_index = 0; ui1_index < 3; ui1_index++)
    {
        t_sub_item_time[ui1_index].pf_fct = _audio_lyric_set_time;
        t_sub_item_time[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
        t_sub_item_time[ui1_index].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, time_id[ui1_index]);
    }

    /*sub item encode mode*/
    for(ui1_index = 0; ui1_index < 5; ui1_index++)
    {
        t_sub_item_encode[ui1_index].pf_fct = _audio_lyric_set_encode;
        t_sub_item_encode[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
        t_sub_item_encode[ui1_index].pw2s_text =
            MLM_MMP_TEXT(t_g_audio_view.ui2_lang, encode_id[ui1_index]);
    }

    if (!t_g_audio_view.b_crt_play_invalid_file)
    {
        /*line*/
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
        t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_LYRIC_OPT_LINE);
        t_optl_item[ui2_cnt].u.t_subopt_list.ui2_num_of_sub_items = 3;
        t_optl_item[ui2_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_line;
        t_optl_item[ui2_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _audio_lyric_get_line;
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        ui2_cnt++;

        /*time*/
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
        t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_LYRIC_OPT_TIME);
        t_optl_item[ui2_cnt].u.t_subopt_list.ui2_num_of_sub_items = 3;
        t_optl_item[ui2_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_time;
        t_optl_item[ui2_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _audio_lyric_get_time;
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        ui2_cnt++;

        /*encode*/
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
        t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_LYRIC_OPT_ENCODE);
        t_optl_item[ui2_cnt].u.t_subopt_list.ui2_num_of_sub_items = 5;
        t_optl_item[ui2_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_encode;
        t_optl_item[ui2_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _audio_lyric_get_encode;
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        ui2_cnt++;

    }


    /*main list*/
    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = ui2_cnt;

    IS_MMPR_OK (a_optl_set_option_items(t_g_audio_view.h_lyric_option,
                 &t_optl_item_def));
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_lyric_opt_select_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_lyric_opt_select_show (VOID)
{
    INT32 i4_ret = 0;

    if(MMP_VE_PLAY_STAT_PLAY != t_g_audio_view.e_player_status &&
       MMP_VE_PLAY_STAT_PAUSE != t_g_audio_view.e_player_status &&
       MMP_VE_PLAY_STAT_STOP != t_g_audio_view.e_player_status &&
       MMP_VE_PLAY_STAT_FAST_FWD != t_g_audio_view.e_player_status &&
       MMP_VE_PLAY_STAT_FAST_RWD != t_g_audio_view.e_player_status)
    {
        DBG_LOG_PRINT(("File status not support option list \n"));
        return MMPR_OK;
    }
    /*Turn on flag*/
    t_g_audio_view.ui4_flag |= MMP_AP_FLAG_LYRIC_LIST_SHOW;

    if(MMP_AP_DETAIL_PAGE_ON==t_g_audio_view.e_detail_page)
    {
        t_g_audio_view.e_detail_page = MMP_AP_DETAIL_PAGE_OFF;

        i4_ret = mmp_com_ui_dp_view_inactive(t_g_audio_view.pv_detail_page_inst);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret =  _audio_lyric_opt_select_set_item();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_visibility(t_g_audio_view.h_lyric_option, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_hlt_index(t_g_audio_view.h_lyric_option,
                                0,
                                0);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_set_focus(t_g_audio_view.h_lyric_option);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_repaint(t_g_audio_view.h_lyric_option);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(t_g_audio_view.h_frm_main, NULL, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_lyric_opt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_lyric_opt (VOID* pv_tag)
{
    /*Hide option list*/
    if(MMP_AP_FLAG_OPTION_LIST_SHOW & t_g_audio_view.ui4_flag)
    {
        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;
        a_optl_hide(t_g_audio_view.h_option_list);
    }

    return _audio_lyric_opt_select_show();
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_opt_select_set_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_opt_select_set_item (VOID)
{
    INT32                  i4_ret = 0;
    OPTL_ITEM_T             t_optl_item[7];
    OPTL_SUBITEM_T          t_sub_item_repeat[3];
    SVC_MM_SBTL_LYRIC_INFO_T t_lyric_info;
    OPTL_ITEM_DEF_T         t_optl_item_def;
    UINT8                   ui2_cnt = 0,ui1_index=0;
    UINT16                  aui2_id[] = {MLM_MMP_KEY_AUD_OPT_REPEAT_NONE,
                                         MLM_MMP_KEY_AUD_OPT_REPEAT_ONE,
                                         MLM_MMP_KEY_AUD_OPT_REPEAT_ALL};

    c_memset(t_optl_item, 0, sizeof(t_optl_item));
    c_memset(t_sub_item_repeat, 0, sizeof(t_sub_item_repeat));
    c_memset(&t_lyric_info, 0, sizeof(SVC_MM_SBTL_LYRIC_INFO_T));
    c_memset(&t_optl_item_def, 0, sizeof(OPTL_ITEM_DEF_T));

    i4_ret = video_engine_get_lyric_info(t_g_audio_view.pv_engine_inst,
                                       &t_lyric_info);
    MMPR_LOG_ON_FAIL(i4_ret);


    /*sub item repeat mode*/
    for(ui1_index = 0; ui1_index < 3; ui1_index++)
    {
        t_sub_item_repeat[ui1_index].pf_fct = _mmp_audio_repeat_setting;
        t_sub_item_repeat[ui1_index].pv_tag = (VOID*)(UINT32)ui1_index;
        t_sub_item_repeat[ui1_index].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, aui2_id[ui1_index]);
    }

    if (!t_g_audio_view.b_crt_play_invalid_file)
    {
        /*play/pause*/
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        if(MMP_VE_PLAY_STAT_PLAY == t_g_audio_view.e_player_status)
        {
            t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_PAUSE);
        }
        else
        {
            t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_PLAY);
        }
        t_optl_item[ui2_cnt].u.t_action.pv_tag = NULL;
        t_optl_item[ui2_cnt].u.t_action.pf_fct = _audio_player_play_pause_setting;
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        ui2_cnt++;

        /*repeat*/
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
        t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_REPEAT);
        t_optl_item[ui2_cnt].u.t_subopt_list.ui2_num_of_sub_items = 3;
        t_optl_item[ui2_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_repeat;
        t_optl_item[ui2_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _audio_player_get_repeat_hlt_idx;
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        ui2_cnt++;

        /*shuffle*/
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        if(MMP_SHUFFLE_MODE_SEQUENTIAL == t_g_audio_view.e_shuffle_mode)
        {
            t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_SHUFF_ON);
        }
        else
        {
            t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_SHUFF_OFF);
        }
        t_optl_item[ui2_cnt].u.t_action.pv_tag = NULL;
        t_optl_item[ui2_cnt].u.t_action.pf_fct = _audio_player_shuffle_setting;
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        ui2_cnt++;
    }

    /*show info*/
    if (!t_g_audio_view.b_crt_play_invalid_file)
    {
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        if(MMP_AP_DETAIL_PAGE_OFF==t_g_audio_view.e_detail_page)
        {
            t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_SHOW_INFO);
        }
        else
        {
            t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_HIDE_INFO);
        }
        t_optl_item[ui2_cnt].u.t_action.pv_tag = NULL;
        t_optl_item[ui2_cnt].u.t_action.pf_fct = _audio_player_show_detail;
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        ui2_cnt++;
    }
#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
    /*spectrum effect*/
    if (!t_g_audio_view.b_crt_play_invalid_file)
    {
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        if(t_g_audio_view.b_eq_viewer_show)
        {
            t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_HIDE_SPECT);
        }
        else
        {
            t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_AUD_OPT_SHOW_SPECT);
        }
        t_optl_item[ui2_cnt].u.t_action.pv_tag = NULL;
        t_optl_item[ui2_cnt].u.t_action.pf_fct = _audio_player_spectrum_effect_toggle;
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        ui2_cnt++;
    }
#endif

    /*Lyric Option*/
    if (!t_g_audio_view.b_crt_play_invalid_file)
    {
        t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_LYRIC_OPT_ITEM);
        t_optl_item[ui2_cnt].u.t_action.pv_tag = NULL;
        t_optl_item[ui2_cnt].u.t_action.pf_fct = _audio_player_lyric_opt;

        if(t_lyric_info.b_has_lyric)
        {
        t_optl_item[ui2_cnt].b_is_disable = FALSE;
        }
        else
        {
            t_optl_item[ui2_cnt].b_is_disable = TRUE;
        }
        ui2_cnt++;
    }

    /*Audio only*/
    t_optl_item[ui2_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
    t_optl_item[ui2_cnt].pw2s_text = MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_VP_AUDIO_ONLY);
    t_optl_item[ui2_cnt].u.t_action.pv_tag = NULL;
    t_optl_item[ui2_cnt].u.t_action.pf_fct = _audio_player_aud_only;
    t_optl_item[ui2_cnt].b_is_disable = FALSE;
    ui2_cnt++;

    /*main list*/
    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = ui2_cnt;

    IS_MMPR_OK (a_optl_set_option_items(t_g_audio_view.h_option_list,
                &t_optl_item_def));
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_key_down_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_key_down_proc_fct(UINT32              ui4_msg,
                                             VOID*               pv_param1,
                                             VOID*               pv_param2)
{
    INT32   i4_ret = 0;
    UINT32  ui4_key_code = (UINT32)pv_param1;
    MMP_PL_CMD_TRICK_PARAM_T t_trick_param;

    c_memset(&t_trick_param, 0, sizeof(t_trick_param));

    t_trick_param.e_mode = MMP_GROUND_MODE_BACK;
    t_trick_param.e_option = MMP_PL_CMD_TRICK_OPTION_RESUME_AFTER_TRICK;

    DBG_LOG_PRINT(("[MMP][%s %d]ui4_key_code = 0x%x\n",__FUNCTION__,__LINE__,ui4_key_code));
    if(0)/*For Linux Issue*/
    {
        if(_audio_player_is_repeated_btn(ui4_key_code,
                                         (UINT32)pv_param2))
        {
            DBG_LOG_PRINT(("Repeated btn return %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
            return MMPR_OK;
        }
    }

    switch (ui4_key_code)
    {
        case AUDIO_PLAYER_BTN_PLAY_PAUSE_2:
        case AUDIO_PLAYER_BTN_PLAY_PAUSE:
        {
            i4_ret = _audio_player_play_pause();
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
        case AUDIO_PLAYER_BTN_PLAY:
        {
            i4_ret = _audio_player_play_pause_process(TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
        case AUDIO_PLAYER_BTN_PAUSE:
        {
            i4_ret = _audio_player_play_pause_process(FALSE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
            break;
        case AUDIO_PLAYER_BTN_STOP_2:
        case AUDIO_PLAYER_BTN_STOP:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T  w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_STOP));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

            if(t_g_audio_view.b_crt_play_invalid_file)
            {
                DBG_LOG_PRINT(("File not play normal, Operation not support\n"));
                return MMPR_OK;
            }

            i4_ret = mmp_mc_list_stop(MMP_GROUND_MODE_BACK);
            if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
            {
                IS_MMPR_OK(i4_ret);
            }
        }
        break;

        case AUDIO_PLAYER_BTN_NEXT_2:
        case AUDIO_PLAYER_BTN_NEXT:
        {
            i4_ret = _audio_player_manaul_next();
            IS_MMPR_OK(i4_ret);
        }
        break;

        case AUDIO_PLAYER_BTN_PREV_2:
        case AUDIO_PLAYER_BTN_PREV:
        {
            i4_ret = _audio_player_manaul_prev();
            IS_MMPR_OK(i4_ret);
        }
        break;

        case AUDIO_PLAYER_BTN_INFO:
        {
#if 0
            if(t_g_audio_view.b_ctrl_panel_show)
            {
                return MMPR_OK;
            }

            i4_ret = _audio_player_show_detail(NULL);
            IS_MMPR_OK(i4_ret);
#endif
        }
        break;

        case AUDIO_PLAYER_BTN_REPEAT_2:
        {
#if 0
            if(t_g_audio_view.b_ctrl_panel_show)
            {
                i4_ret = _audio_player_view_toggle_repeat(TRUE);
                IS_MMPR_OK(i4_ret);
            }
#endif
        }
        break;

        case AUDIO_PLAYER_BTN_REPEAT:
        {
#if 0
            i4_ret = _audio_player_view_toggle_repeat(TRUE);
            IS_MMPR_OK(i4_ret);
#endif
        }
        break;

        case AUDIO_PLAYER_BTN_SHUFFLE:
        {
#if 0
            if(t_g_audio_view.b_ctrl_panel_show)
            {
                i4_ret = _audio_player_toggle_shuffle(TRUE);
                IS_MMPR_OK(i4_ret);
            }
#endif
        }
        break;

        case AUDIO_PLAYER_BTN_EXIT:
        {
#if 0
            if(t_g_audio_view.b_ctrl_panel_show)
            {
                return MMPR_OK;
            }

            i4_ret = mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
            IS_MMPR_OK(i4_ret);
#endif
        }
        break;

        case AUDIO_PLAYER_BTN_OPTION:
        {
#if 0
            if(t_g_audio_view.b_ctrl_panel_show)
            {
                return MMPR_OK;
            }

            IS_MMPR_OK(_audio_player_opt_select_show());
#endif
        }
        break;

        case AUDIO_PLAYER_BTN_FF:
        {
#ifdef APP_TTS_SUPPORT
                UTF16_T  w2s_str[128] = {0};
                c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_FAST_FORWARD));
                a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif
            if(MMP_VE_CTNT_RPT_TYPE_NONE!=t_g_audio_view.e_repeat_ab)
            {
                DBG_LOG_PRINT(("Rpeat AB, not support Fast Forward\n"));
                return MMPR_OK;
            }

            i4_ret = mmp_mc_list_fast_forward(&t_trick_param);
            if(MMPR_OK != i4_ret && MMPR_IS_FAST_FORWARDED != i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case AUDIO_PLAYER_BTN_FSEEK:
        {
#if 1
            IS_MMPR_OK(_audio_player_seek_begin(TRUE, TRUE));
#endif
        }
        break;

        case AUDIO_PLAYER_BTN_FR:
        {
#ifdef APP_TTS_SUPPORT
            UTF16_T  w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_REWIND));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
#endif

            if(MMP_VE_CTNT_RPT_TYPE_NONE!=t_g_audio_view.e_repeat_ab)
            {
                DBG_LOG_PRINT(("Rpeat AB, not support Fast Rewind\n"));
                return MMPR_OK;
            }

            i4_ret = mmp_mc_list_fast_rewind(&t_trick_param);
            if(MMPR_OK != i4_ret && MMPR_IS_FAST_REWINDED != i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case AUDIO_PLAYER_BTN_BSEEK:
        {
#if 1
            IS_MMPR_OK(_audio_player_seek_begin(FALSE, TRUE));
#endif
        }
        break;

        case AUDIO_PLAYER_BTN_AB_REPEAT:
        {
#if 0
            i4_ret = _audio_player_ab_repeat();
            MMPR_LOG_ON_FAIL(i4_ret);
#endif
        }
        break;

        default:
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        {
            i4_ret = mmp_mc_key_handler(ui4_key_code, WGL_MSG_KEY_DOWN);
            if(i4_ret == MMPR_NO_DATA)
            {
                break;
            }
            else
            {
                return i4_ret;
            }
        }
#else
            break;
#endif
    }

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_key_up_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_key_up_proc_fct(UINT32              ui4_msg,
                                           VOID*               pv_param1,
                                           VOID*               pv_param2)
{
    INT32 i4_ret = 0;

    UINT32 ui4_key_code = (UINT32)pv_param1;

    switch (ui4_key_code)
    {
        case AUDIO_PLAYER_BTN_FF:
        case AUDIO_PLAYER_BTN_FSEEK:
        {
            i4_ret = _audio_player_seek_end(TRUE);
            IS_MMPR_OK(i4_ret);
        }
        break;

        case AUDIO_PLAYER_BTN_FR:
        case AUDIO_PLAYER_BTN_BSEEK:
        {
            i4_ret = _audio_player_seek_end(FALSE);
            IS_MMPR_OK(i4_ret);
        }
        break;
        default:
            break;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_main_frm_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_main_frm_proc_fct(HANDLE_T            h_frm_main,
                                             UINT32              ui4_msg,
                                             VOID*               pv_param1,
                                             VOID*               pv_param2)
{
    INT32 i4_ret = 0;

    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        i4_ret = _audio_player_key_down_proc_fct(ui4_msg,
                                                 pv_param1,
                                                 pv_param2);
        IS_MMPR_OK(i4_ret);
    }
    else if(ui4_msg == WGL_MSG_KEY_UP)
    {
        i4_ret = _audio_player_key_up_proc_fct(ui4_msg,
                                               pv_param1,
                                               pv_param2);
        IS_MMPR_OK(i4_ret);
    }

   return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_view_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_deinit( AUDIO_PLAYER_VIEW_T*      pt_this)
{
    INT32                       i4_ret = 0;

    /* Release Timer */
    if(NULL_HANDLE != t_g_audio_view.h_timer_invaid_file_msg)
    {
        i4_ret = c_timer_delete (t_g_audio_view.h_timer_invaid_file_msg);
        MMPR_LOG_ON_FAIL(i4_ret);
        t_g_audio_view.h_timer_invaid_file_msg = NULL_HANDLE;
    }

    /* Release Timer */
    if(NULL_HANDLE != t_g_audio_view.h_timer_timeout)
    {
        i4_ret = c_timer_delete (t_g_audio_view.h_timer_timeout);
        MMPR_LOG_ON_FAIL(i4_ret);
        t_g_audio_view.h_timer_timeout = NULL_HANDLE;
    }

    /* Release Timer */
    if(NULL_HANDLE != t_g_audio_view.h_timer_msg)
    {
        i4_ret = c_timer_delete (t_g_audio_view.h_timer_msg);
        MMPR_LOG_ON_FAIL(i4_ret);
        t_g_audio_view.h_timer_msg = NULL_HANDLE;
    }

#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
    if(NULL_HANDLE != pt_this->h_eq_viewer)
       {
        i4_ret = a_mmp_eq_destroy(pt_this->h_eq_viewer);
           MMPR_LOG_ON_FAIL(i4_ret);

        pt_this->h_eq_viewer = NULL_HANDLE;
       }
#endif

    if(NULL_HANDLE != pt_this->h_option_list)
    {
        i4_ret = a_optl_destroy(pt_this->h_option_list);
        MMPR_LOG_ON_FAIL(i4_ret);

        pt_this->h_option_list = NULL_HANDLE;
    }

    if(NULL_HANDLE != pt_this->h_lyric_option)
    {
        i4_ret = a_optl_destroy(pt_this->h_lyric_option);
        MMPR_LOG_ON_FAIL(i4_ret);

        pt_this->h_lyric_option = NULL_HANDLE;
    }

#ifdef   _MMP_VERC_PLAY_COVER_SUPPORT
    if(NULL_HANDLE != pt_this->h_transparent_list)
    {
        i4_ret = c_wgl_delete_transparent_list(pt_this->h_transparent_list);
        MMPR_LOG_ON_FAIL(i4_ret);

        pt_this->h_transparent_list = NULL_HANDLE;
    }
#endif

    /*  destroy the audio play img fr*/
    if(NULL_HANDLE != t_g_audio_view.h_audio_play_img_fr)
    {
        i4_ret = c_wgl_destroy_widget(t_g_audio_view.h_audio_play_img_fr);
        MMPR_LOG_ON_FAIL(i4_ret);

        t_g_audio_view.h_audio_play_img_fr = NULL_HANDLE;
    }

    if(NULL!=t_g_audio_view.pv_detail_page_inst)
    {
        i4_ret = mmp_com_ui_dp_destroy(t_g_audio_view.pv_detail_page_inst);
        MMPR_LOG_ON_FAIL(i4_ret);
        t_g_audio_view.pv_detail_page_inst = NULL;
    }

    if(NULL!=pt_this->pv_toolbar_inst)
    {
        i4_ret = mmp_common_ui_toolbar_deinit(pt_this->pv_toolbar_inst);
        MMPR_LOG_ON_FAIL(i4_ret);
        pt_this->pv_toolbar_inst = NULL;
    }

    i4_ret = mmp_img_deinit();
    MMPR_LOG_ON_FAIL(i4_ret);

    if(NULL_HANDLE != pt_this->h_frm_main)
    {
        i4_ret = c_wgl_destroy_widget_ex(pt_this->h_frm_main, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);

        pt_this->h_frm_main = NULL_HANDLE;
    }

    c_memset(&t_g_audio_view, 0, sizeof(AUDIO_PLAYER_VIEW_T));
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_option_list_time_out
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _audio_player_option_list_time_out(VOID*      pv_tag1,
                                               VOID*      pv_tag2,
                                               VOID*      pv_tag3,
                                               VOID*      pv_tag4)
{
    INT32 i4_ret = 0;

    /*Turn off flag*/
    t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;
    i4_ret = a_optl_hide(t_g_audio_view.h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_opt_select_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static VOID _audio_player_opt_select_proc_fct(VOID*    pv_tag,
                                              UINT32   ui4_msg,
                                              VOID*    pv_param1,
                                              VOID*    pv_param2)
{
    INT32 i4_ret = 0;

    /*Not in palyer*/
    if(!(t_g_audio_view.ui4_flag & MMP_AP_FLAG_ACTIVATE))
    {
        return ;
    }

    if (OPTL_MSG_CANCELLED==ui4_msg)
    {
        /* Set focus and repaint main frame */
        i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main,
                               WGL_NO_AUTO_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);

        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;
    }
    else if(OPTL_MSG_HIDE_TIMEOUT==ui4_msg)
    {
        /* Set focus and repaint main frame */
        i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main, WGL_NO_AUTO_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret =mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_player_option_list_time_out,
                                    NULL, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if(OPTL_MSG_KEY_INPUT==ui4_msg)
    {
        UINT32 ui4_key_code = (UINT32)pv_param1;
        if(AUDIO_PLAYER_BTN_OPTION==ui4_key_code)
        {
            /* Set focus and repaint main frame */
            i4_ret =c_wgl_set_focus(t_g_audio_view.h_frm_main, WGL_NO_AUTO_REPAINT);
            MMPR_LOG_ON_FAIL(i4_ret);
            i4_ret =mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                        _audio_player_option_list_time_out,
                                        NULL, NULL, NULL, NULL);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        else
        {
            i4_ret = mmp_mc_key_handler(ui4_key_code, WGL_MSG_KEY_DOWN);
            if(MMPR_OK == i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
                /*Turn off flag*/
                t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;
                i4_ret =a_optl_hide(t_g_audio_view.h_option_list);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
#endif
    }
}


/*----------------------------------------------------------------------------
 * Name: _audio_lyric_option_list_time_out
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _audio_lyric_option_list_time_out(VOID*      pv_tag1,
                                              VOID*      pv_tag2,
                                              VOID*      pv_tag3,
                                              VOID*      pv_tag4)
{
    INT32 i4_ret = 0;
    /*Turn off flag*/
    t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_LYRIC_LIST_SHOW;
    i4_ret = a_optl_hide(t_g_audio_view.h_lyric_option);
    MMPR_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _audio_lyric_opt_select_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static VOID _audio_lyric_opt_select_proc_fct(VOID*    pv_tag,
                                             UINT32   ui4_msg,
                                             VOID*    pv_param1,
                                             VOID*    pv_param2)
{
    INT32 i4_ret = 0;

    if (OPTL_MSG_CANCELLED==ui4_msg)
    {
        /* Set focus and repaint main frame */
        i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main , WGL_NO_AUTO_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);

        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_LYRIC_LIST_SHOW;
    }
    else if(OPTL_MSG_HIDE_TIMEOUT==ui4_msg)
    {

        /* Set focus and repaint main frame */
        i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main, WGL_NO_AUTO_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_lyric_option_list_time_out,
                                    NULL, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if(OPTL_MSG_KEY_INPUT==ui4_msg)
    {
        UINT32 ui4_key_code = (UINT32)pv_param1;
        if(AUDIO_LYRIC_BTN_OPTION==ui4_key_code)
        {
            /* Set focus and repaint main frame */
            i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main, WGL_NO_AUTO_REPAINT);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                        _audio_lyric_option_list_time_out,
                                        NULL, NULL, NULL, NULL);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        else
        {
            i4_ret = mmp_mc_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
            if(MMPR_OK == i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
                /*Turn off flag*/
                t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_LYRIC_LIST_SHOW;
                i4_ret = a_optl_hide(t_g_audio_view.h_lyric_option);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
#endif
    }

}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_view_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_init(AUDIO_PLAYER_VIEW_T *      pt_this)
{
    INT32            i4_ret = 0;
    OPTL_INIT_T      t_optl_init = {0};
    GL_RECT_T t_rect = {0};
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
    MMP_MC_PLAYER_SETTING_T  t_play_setting;
#endif

    /*get canvas*/
    pt_this->h_canvas = mmp_main_get_canvas();

    do
    {
        /*init image*/
        i4_ret = mmp_img_init();
        if(MMPR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        /*create timer for invalid file*/
        i4_ret = c_timer_create(&pt_this->h_timer_invaid_file_msg);
        if(OSR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            pt_this->h_timer_invaid_file_msg = NULL_HANDLE;
            break;
        }

        /*create timer for updating position*/
        i4_ret = c_timer_create(&pt_this->h_timer_timeout);
        if(OSR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            pt_this->h_timer_timeout = NULL_HANDLE;
            break;
        }

        i4_ret = c_timer_create(&pt_this->h_timer_msg);
        if(OSR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            pt_this->h_timer_msg = NULL_HANDLE;
            break;
        }

        if(OSR_OK != (i4_ret = c_timer_create(&pt_this->h_timer_load_file_cover)))
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            pt_this->h_timer_load_file_cover = NULL_HANDLE;
            break;
        }

        /*create main frm*/
        i4_ret = mmp_com_ui_create_player_frm(pt_this->h_canvas,
                                              _audio_player_main_frm_proc_fct,
                                              255,
                                              &pt_this->h_frm_main);
        if(MMPR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }

        /* Create tool bar */
        i4_ret = mmp_common_ui_toolbar_init(MMP_TB_AUDIO_PLAYER,
                                            pt_this->h_frm_main,
                                            (VOID **)&(pt_this->pv_toolbar_inst));
        if(MMPR_OK != i4_ret)
        {
            MMPR_LOG_ON_FAIL(i4_ret);
            pt_this->pv_toolbar_inst = NULL;
            break;
        }

        i4_ret = mmp_com_ui_create_detail_page_new(pt_this->h_frm_main,
                                                   COM_UI_DTL_PG_AUDIO,
                                                   (VOID *)&(pt_this->pv_detail_page_inst));
        if(WGLR_OK != i4_ret)
        {
            pt_this->pv_detail_page_inst = NULL;
            MMPR_LOG_ON_FAIL(i4_ret);
            break;
        }


        /* Create option list widget */
        t_optl_init.h_parent            = pt_this->h_frm_main;
        t_optl_init.t_gui_rc.i4_left    = OPTION_LIST_LEFT;
        t_optl_init.t_gui_rc.i4_top     = OPTION_LIST_TOP;
        t_optl_init.ui4_style_mask      = OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT;
        t_optl_init.pv_tag              = NULL;
        t_optl_init.pf_fct              = _audio_player_opt_select_proc_fct;
        t_optl_init.pf_get_key_src_fct  = NULL;
        t_optl_init.ui4_custom_flag     = 0;
        t_optl_init.ui4_sleep_time      = MMP_AP_TIMER_OPTION_LIST;

        i4_ret =a_optl_create(&t_optl_init,
                &pt_this->h_option_list);

        if(MMPR_OK != i4_ret)
        {
            pt_this->h_option_list = NULL_HANDLE;
            break;
        }

        /* Create lyric option widget */
        t_optl_init.h_parent            = pt_this->h_frm_main;
        t_optl_init.t_gui_rc.i4_left    = OPTION_LIST_LEFT;
        t_optl_init.t_gui_rc.i4_top     = OPTION_LIST_TOP;
        t_optl_init.ui4_style_mask      = OPTL_STYLE_MASK_DEFAULT_HIDE_TIMEOUT;
        t_optl_init.pv_tag              = NULL;
        t_optl_init.pf_fct              = _audio_lyric_opt_select_proc_fct;
        t_optl_init.pf_get_key_src_fct  = NULL;
        t_optl_init.ui4_custom_flag     = 0;
        t_optl_init.ui4_sleep_time      = MMP_AP_TIMER_OPTION_LIST;

        i4_ret = a_optl_create(&t_optl_init, &pt_this->h_lyric_option);

        if(MMPR_OK != i4_ret)
        {
            pt_this->h_lyric_option = NULL_HANDLE;
            break;
        }
#if NEVER
#ifdef   _MMP_VERC_PLAY_COVER_SUPPORT
        c_memset(&t_rect,0,sizeof(t_rect));
        SET_RECT_BY_SIZE (&t_rect,
                          MMP_AP_RC_COV_PIC_X,
                          MMP_AP_RC_COV_PIC_Y,
                          MMP_AP_RC_COV_PIC_W,
                          MMP_AP_RC_COV_PIC_H);

        i4_ret = c_wgl_create_transparent_list(pt_this->h_canvas,
                                               &t_rect,
                                               1,
                                               &pt_this->h_transparent_list);
        if(MMPR_OK != i4_ret)
        {
            pt_this->h_transparent_list = NULL_HANDLE;
            break;
        }
        i4_ret = c_wgl_enable_transparent_list(pt_this->h_transparent_list,
                                               FALSE,
                                               FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
#endif
        c_memset(&t_rect,0,sizeof(t_rect));
        SET_RECT_BY_SIZE (&t_rect,
                          MMP_AP_INFO_HANDLE_COV_PIC_X,
                          MMP_AP_INFO_HANDLE_COV_PIC_Y,
                          MMP_AP_INFO_HANDLE_COV_PIC_W,
                          MMP_AP_INFO_HANDLE_COV_PIC_H);

        i4_ret = c_wgl_create_widget(pt_this->h_canvas,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     0,
                                     (VOID*)(WGL_STL_GL_NO_BK),
                                     NULL,
                                     &(t_g_audio_view.h_audio_play_img_fr));
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(t_g_audio_view.h_audio_play_img_fr, WGL_SW_NORMAL);
        MMPR_LOG_ON_FAIL(i4_ret);
#endif
#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
        MMP_EQ_INIT_T   t_eq_init = {0};

        SET_RECT_BY_SIZE (&t_eq_init.t_rect,
                          MMP_EQ_X,
                          MMP_EQ_Y,
                          MMP_EQ_W,
                          MMP_EQ_H);

        t_eq_init.h_parent = pt_this->h_frm_main;
        t_eq_init.ui1_alpha = 255;
        t_eq_init.ui4_style = 0;
        t_eq_init.t_bk_clr = t_g_mmp_color_transp;
        t_eq_init.t_bar_low_clr= t_g_mmp_color_bar_low;
        t_eq_init.t_bar_mid_clr= t_g_mmp_color_bar_mid;
        t_eq_init.t_bar_high_clr= t_g_mmp_color_bar_high;

        t_eq_init.ui2_bar_element_height =  MMP_EQ_ELE_H;
        t_eq_init.ui2_bar_element_width= MMP_EQ_ELE_W;
        t_eq_init.ui2_bar_element_insert =  MMP_EQ_ELE_INSERT;
        t_eq_init.ui2_bar_insert =  MMP_EQ_BAR_INSERT;

        i4_ret = a_mmp_eq_create (&t_eq_init,
                                &pt_this->h_eq_viewer);
        if(MMPR_OK != i4_ret)
        {
            pt_this->h_eq_viewer = NULL_HANDLE;
            break;
        }
#endif
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        c_memset(&t_play_setting, 0, sizeof(t_play_setting));
        t_play_setting.ui4_mask = MMP_MC_PLYR_SETTING_MSK_DEF_FCS_WGT;
        t_play_setting.h_def_focus_widget = pt_this->h_frm_main;
        i4_ret = mmp_mc_set_player_setting(MMP_MEDIA_TYPE_AUDIO,
                                       &t_play_setting);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
#endif
        return MMPR_OK;
    } while(0);

    i4_ret = _audio_player_view_deinit(pt_this);
    MMPR_LOG_ON_FAIL(i4_ret);
    return MMPR_FAIL;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_view_swap_filename
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_swap_filename(BOOL b_repaint)
{
    INT32   i4_ret = 0;

    if(!t_g_audio_view.b_ctrl_panel_show)
    {
        i4_ret = mmp_com_ui_dp_set_text_ex(t_g_audio_view.pv_detail_page_inst,
                                      MMP_AP_RC_DP_LBL_ID_NEXT,
                                      NULL,
                                      (t_g_audio_view.e_detail_page == MMP_AP_DETAIL_PAGE_ON)? COM_UI_SYNC_REPAINT: COM_UI_NON_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _audio_player_view_set_fileidx(TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                            MMP_AP_TB_CMD_SET_FILENAME,
                                            (VOID*)w2s_g_file_next,
                                            (b_repaint?MMP_TB_SYNC_REPAINT:MMP_TB_NON_REPAINT));
        MMPR_LOG_ON_FAIL(i4_ret);
    }


    /*Keep current file*/
    c_uc_w2s_strncpy(w2s_g_file, w2s_g_file_next, MMP_AP_RC_FILE_MAX_LEN-1);
    w2s_g_file[MMP_AP_RC_FILE_MAX_LEN-1]= 0;

    /*Reset next*/
    c_uc_ps_to_w2s("", w2s_g_file_next, MMP_AP_RC_FILE_MAX_LEN);

    /*After next will preload next*/
    if(t_g_audio_view.b_ctrl_panel_show)
    {
        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_FILE_NAME,
                                             (VOID*)w2s_g_file,
                                             b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_update_vol_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_update_vol_info (BOOL b_repaint,VOID* pv_msg_param)
{
    INT32               i4_ret = 0;
    MMP_VOL_UPD_INFO_T  *pt_vol_inf = NULL;
    UINT16              i2_vol = 0, ui2_mlm_id = 0;
    BOOL                b_cec_sac = FALSE, b_mute = a_tv_get_mute();
    UINT8               ui1_icl_val=0;
    SIZE_T              z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
    BOOL                b_show_bar=TRUE;

    if(!t_g_audio_view.b_ctrl_panel_show &&
       !(t_g_audio_view.ui4_flag &MMP_AP_FLAG_ACTIVATE))
    {
        return MMPR_OK;
    }

    if(NULL!=pv_msg_param)
    {
        pt_vol_inf = (MMP_VOL_UPD_INFO_T*)pv_msg_param;
    }

    /*Check CEC SAC status*/
    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                       &ui1_icl_val,
                       &z_size);
    if ((ICLR_OK == i4_ret && ui1_icl_val == ICL_CEC_SAC_STATUS_ON) ||
        (pt_vol_inf && pt_vol_inf->b_cec_sac))
    {
        b_cec_sac = TRUE;
    }
#if 0/*Test only*/
    b_cec_sac = TRUE;
#endif
    if (b_cec_sac)
    {
        if(t_g_audio_view.b_ctrl_panel_show)
        {
            i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                 MMP_AP_CUR_PLAY_INFO_VOL_BAR_SHOW,
                                                 (VOID*)(UINT32)b_mute,
                                                 b_repaint);
            MMPR_LOG_ON_FAIL(i4_ret);

        }
        else
        {
            if(b_mute &&
               t_g_audio_view.b_msg_show)
            {
                t_g_audio_view.b_msg_show = FALSE;
                i4_ret = mmp_info_bar_hide();
                MMPR_LOG_ON_FAIL(i4_ret);
            }

            i4_ret = mmp_common_ui_toolbar_cmd_do(
                        t_g_audio_view.pv_toolbar_inst,
                        MMP_AP_TB_CMD_SET_VOL_MUTE,
                        (VOID*)(UINT32)(b_mute ? MMP_AP_TB_STATUS_VOL_MUTE : MMP_AP_TB_STATUS_VOL_NORMAL),
                        MMP_TB_NON_REPAINT);
            MMPR_LOG_ON_FAIL(i4_ret);

            b_show_bar=FALSE;

            i4_ret = mmp_common_ui_toolbar_cmd_do(
                        t_g_audio_view.pv_toolbar_inst,
                        MMP_AP_TB_CMD_SET_VOL_BAR_VISBI,
                        (VOID*)(UINT32)b_show_bar,
                        (b_repaint ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT));
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = mmp_common_ui_toolbar_view_active(t_g_audio_view.pv_toolbar_inst,
                                                    (b_repaint ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT));
            MMPR_LOG_ON_FAIL(i4_ret);

            if (NULL != pt_vol_inf && (pt_vol_inf->b_volume_up || pt_vol_inf->b_volume_down))
            {
                ui2_mlm_id = pt_vol_inf->b_volume_up ? (UINT16)MLM_MMP_KEY_VOL_AMP_INCREASE : (UINT16)MLM_MMP_KEY_VOL_AMP_DECREASE;

                i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, ui2_mlm_id));
                MMPR_LOG_ON_FAIL(i4_ret);
           }
        }
    }
    else
    {
         i4_ret = a_tv_get_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                      (INT16*)&i2_vol);
         MMPR_LOG_ON_FAIL(i4_ret);

         if(t_g_audio_view.b_ctrl_panel_show)
         {
            /*Ctrl Panel Mute Icon Issue*/
             i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                  MMP_AP_CUR_PLAY_INFO_PG_VOL,
                                                  (VOID*)(UINT32)i2_vol,
                                                  b_repaint);
             MMPR_LOG_ON_FAIL(i4_ret);

             i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                  MMP_AP_CUR_PLAY_INFO_MUTE,
                                                  (VOID*)(UINT32)b_mute,
                                                  b_repaint);
             MMPR_LOG_ON_FAIL(i4_ret);

             return MMPR_OK;
         }
         else
         {
             b_show_bar=TRUE;

             i4_ret = mmp_common_ui_toolbar_cmd_do(
                         t_g_audio_view.pv_toolbar_inst,
                         MMP_AP_TB_CMD_SET_VOL_BAR_VISBI,
                         (VOID*)(UINT32)b_show_bar,
                         (b_repaint ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT)
                         );

             i4_ret = mmp_common_ui_toolbar_cmd_do(
                         t_g_audio_view.pv_toolbar_inst,
                         MMP_AP_TB_CMD_SET_VOL_PG,
                         (VOID*)(UINT32)i2_vol,
                         (b_repaint ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT)
                         );
             MMPR_LOG_ON_FAIL(i4_ret);

             i4_ret = mmp_common_ui_toolbar_cmd_do(
                         t_g_audio_view.pv_toolbar_inst,
                         MMP_AP_TB_CMD_SET_VOL_MUTE,
                         (VOID*)(UINT32)(b_mute ? MMP_AP_TB_STATUS_VOL_MUTE : MMP_AP_TB_STATUS_VOL_NORMAL),
                         (b_repaint ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT)
                         );
             MMPR_LOG_ON_FAIL(i4_ret);
         }
    }


    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_end_of_lst_proc
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_end_of_lst_proc (VOID)
{
    INT32 i4_ret = 0;

    if(t_g_audio_view.b_ctrl_panel_show &&
       t_g_audio_view.pv_ctrl_panel_inst)
    {
        t_g_audio_view.e_player_status = MMP_VE_PLAY_STAT_STOP;
        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_PLAY_STATUS,
                                             (VOID*)t_g_audio_view.e_player_status,
                                             TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _audio_player_view_set_ab_repeat(TRUE, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _audio_player_view_update_pos(0, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_skip_invalid_file
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _audio_player_skip_invalid_file (VOID* pv_param1, VOID* pv_param2,
                                             VOID* pv_param3, VOID* pv_param4)
{
    INT32 i4_ret = 0;
    MMP_FP_SHOW_NFY_COMMON_PARAM_T t_nfy_data;
    mmp_fp_show_nfy_fct show_nfy_fct = t_g_audio_view.pf_fp_show_nfy_fct;
    MMP_FP_SHOW_NFY_ID_T e_nfy_id;

    c_memset(&t_nfy_data, 0, sizeof(t_nfy_data));

    if(MMP_VE_PLAY_STAT_CLOSE == t_g_audio_view.e_player_status)
    {
        return; /* timer is out of date */
    }
    else if(MMP_VE_PLAY_STAT_NEXT == t_g_audio_view.e_player_status)
    {
        e_nfy_id = MMP_FP_SHOW_NFY_ID_NEXT_RESULT;
    }
    else
    {
        e_nfy_id = MMP_FP_SHOW_NFY_ID_START_RESULT;
    }

    DBG_LOG_PRINT(("_audio_player_skip_invalid_file\n"));

    t_g_audio_view.b_crt_play_invalid_file = TRUE;

    if(t_g_audio_view.b_msg_show)
    {
        t_g_audio_view.b_msg_show = FALSE;
        i4_ret = mmp_info_bar_hide();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    t_nfy_data.b_result = TRUE;
    t_nfy_data.e_crnt_state = MMP_PLAY_STATE_PLAYED;

    /*Change MMC status*/
    show_nfy_fct(t_g_audio_view.pv_mmp_tag,
                 t_g_audio_view.ui4_mmc_ver,
                 e_nfy_id,
                 (VOID*)&t_nfy_data);

    /*MMC END*/
    show_nfy_fct(t_g_audio_view.pv_mmp_tag,
                 t_g_audio_view.ui4_mmc_ver,
                 MMP_FP_SHOW_NFY_ID_PLAY_END,
                 (VOID*)&t_nfy_data);
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_handle_invalid_file
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _audio_player_handle_invalid_file (VOID* pv_param1, VOID* pv_param2,
                                               VOID* pv_param3, VOID* pv_param4)
{
    INT32 i4_ret = 0;
    MMP_FP_SHOW_NFY_COMMON_PARAM_T  t_nfy_data;
    mmp_fp_show_nfy_fct  show_nfy_fct = t_g_audio_view.pf_fp_show_nfy_fct;

    MMP_FP_SHOW_NFY_ID_T e_nfy_id = MMP_FP_SHOW_NFY_ID_OPEN_RESULT;

    c_memset(&t_nfy_data, 0, sizeof(t_nfy_data));

    if(MMP_VE_PLAY_STAT_CLOSE == t_g_audio_view.e_player_status)
    {
        return; /* timer is out of date */
    }
    else if(MMP_VE_PLAY_STAT_NEXT == t_g_audio_view.e_player_status)
    {
        e_nfy_id = MMP_FP_SHOW_NFY_ID_NEXT_RESULT;
    }
    else
    {
        e_nfy_id = MMP_FP_SHOW_NFY_ID_START_RESULT;
    }

    t_g_audio_view.b_crt_play_invalid_file = TRUE;

    if(MMP_AP_DETAIL_PAGE_ON == t_g_audio_view.e_detail_page)
    {
        _audio_player_view_refresh_detail_page(TRUE);
    }

    i4_ret = c_timer_stop (t_g_audio_view.h_timer_timeout);
    MMPR_LOG_ON_FAIL(i4_ret);

    t_g_audio_view.e_player_status = MMP_VE_PLAY_STAT_PLAY;

    i4_ret = _audio_player_view_update_pos(0, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_view_set_play_status(FALSE, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    if(t_g_audio_view.b_msg_show)
    {
        t_g_audio_view.b_msg_show = FALSE;
        i4_ret = mmp_info_bar_hide();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if(_MMP_AP_LAST_OPEN_ELM_RET_FAILED == t_g_audio_view.e_last_open_elm_ret)
    {
        if(t_g_audio_view.ui4_flag & MMP_AP_FLAG_ACTIVATE)
        {
            i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }
    else if(_MMP_AP_LAST_OPEN_ELM_RET_CORRUPT == t_g_audio_view.e_last_open_elm_ret)
    {
        if(t_g_audio_view.ui4_flag & MMP_AP_FLAG_ACTIVATE)
        {
            i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }

    t_nfy_data.b_result = TRUE;
    t_nfy_data.e_crnt_state = MMP_PLAY_STATE_PLAYED;
    show_nfy_fct(t_g_audio_view.pv_mmp_tag,
                 t_g_audio_view.ui4_mmc_ver,
                 e_nfy_id,
                 (VOID*)&t_nfy_data);

    i4_ret = c_timer_start (t_g_audio_view.h_timer_invaid_file_msg,
                   MMP_AP_TIMER_INVALID_FILE_MSG_DELAY,
                   X_TIMER_FLAG_ONCE,
                   _audio_player_timer_nfy_fct,
                   NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

        /*Hide it first*/
#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
        if(t_g_audio_view.b_eq_viewer_show)
        {
            t_g_audio_view.b_eq_viewer_show = FALSE;
            i4_ret = a_mmp_eq_show(t_g_audio_view.h_eq_viewer, FALSE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
#endif
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_update_pos
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _audio_player_update_pos(VOID*                       pv_tag1,
                                     VOID*                       pv_tag2,
                                     VOID*                       pv_tag3,
                                     VOID*                       pv_tag4)
{
    INT32   i4_ret = 0;

    if(t_g_audio_view.b_crt_play_invalid_file)
    {
        MMP_DBG_INFO(("return %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
        return;
    }
    if(t_g_audio_view.ui4_flag & MMP_AP_FLAG_SEEKING_BEGIN)
    {
        DBG_LOG_PRINT(("b_seek_begin can't update pos\n"));
        return ;
    }
    i4_ret = video_engine_get_position(t_g_audio_view.pv_engine_inst,
                                       MMP_VE_POS_TYPE_TIME,
                                      &t_g_audio_view.ui8_position);
    MMPR_LOG_ON_FAIL(i4_ret);
#if 0
    if(MMPR_OK != i4_ret)
    {
        /*End of File*/
        i4_ret = c_timer_stop(t_g_audio_view.h_timer_timeout);
        MMPR_LOG_ON_FAIL(i4_ret);
        return ;
    }
#endif

#ifdef DEBUG
    DBG_LOG_PRINT(("\n%s,%s,%d,ui8_position=%llu,ui8_duration=%llu\n",
                __FILE__, __FUNCTION__, __LINE__,
                t_g_audio_view.ui8_position, t_g_audio_view.ui8_duration));
#endif

    /*In Audio Player*/
    if(0 != t_g_audio_view.ui8_duration)
    {
        i4_ret = _audio_player_view_update_pos(t_g_audio_view.ui8_position,
                                               TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
}

static INT32 _audio_player_view_update_play_info(VOID)
{
    INT32      i4_ret = 0;
    //UTF16_T    w2s_info[MMP_AP_INFO_MAX_STR_LEN] = {0};

    APPL_SPLAYER_MUSIC_INFO_T tInfo;
    WGL_IMG_INFO_T          t_img_info;
    MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this = NULL;

    c_memset(&tInfo, 0, sizeof(tInfo));
    i4_ret =  video_engine_get_music_info(&tInfo);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
#if NEVER
    c_memset(w2s_info, 0, sizeof(w2s_info));
    c_uc_ps_to_w2s(tInfo.szMetadataTitle, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_TITLE,
                                         (VOID*)w2s_info,
                                         TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_info, 0, sizeof(w2s_info));
    c_uc_ps_to_w2s(tInfo.szMetadataArtist, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_ARTIST,
                                         (VOID*)w2s_info,
                                         TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_info, 0, sizeof(w2s_info));
    c_uc_ps_to_w2s(tInfo.szMetadataAlbum, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_ALBUM,
                                         (VOID*)w2s_info,
                                         TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_info, 0, sizeof(w2s_info));
    c_uc_ps_to_w2s(tInfo.szMetadataGenre, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_GERNER,
                                         (VOID*)w2s_info,
                                         TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_info, 0, sizeof(w2s_info));
    c_uc_ps_to_w2s(tInfo.szYear, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_YEAR,
                                         (VOID*)w2s_info,
                                         TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);
#else
    pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)t_g_audio_view.pv_ctrl_panel_inst;

    c_memset (&t_img_info, 0, sizeof(t_img_info)) ;
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = tInfo.h_cover_img;
    t_img_info.u_img_data.t_standard.t_disable = tInfo.h_cover_img;
    t_img_info.u_img_data.t_standard.t_highlight = tInfo.h_cover_img;

    i4_ret = c_wgl_do_cmd(pt_this->h_audio_play_img_fr,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed1\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_insert(pt_this->h_main_frm,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT);
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed2\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_insert(pt_this->h_audio_play_img_fr,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT);
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed3\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_audio_play_img_fr, WGL_SW_NORMAL);
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed5\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }
    i4_ret = c_wgl_repaint(pt_this->h_audio_play_img_fr,  NULL, TRUE);
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed4\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }
    i4_ret = c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed5\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm, WGL_SW_NORMAL);
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed6\n",__FUNCTION__,__LINE__));
        return MMPR_FAIL;
    }
#endif
    return MMPR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _audio_player_view_update_pos
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_update_pos(UINT64  ui8_day_sec, BOOL b_repaint)
{
    INT32      i4_ret = 0;
    UINT32     ui4_pb_pos = 0;

    /* set Pb position */
    if (t_g_audio_view.ui8_duration == 0 )
    {
        ui4_pb_pos = 0;
    }
    else
    {
        ui4_pb_pos = (UINT32)(t_g_audio_view.ui8_position*100 / t_g_audio_view.ui8_duration);
        ui4_pb_pos = ((t_g_audio_view.ui8_position*100) % t_g_audio_view.ui8_duration > 0) ?
        ui4_pb_pos+1 : ui4_pb_pos;
    }

#ifdef DEBUG
    DBG_LOG_PRINT(("\n%s,%s,%d,b_ctrl_panel_show=%d,ui8_position=%llu,ui8_duration=%llu,ui4_pb_pos=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                t_g_audio_view.b_ctrl_panel_show, t_g_audio_view.ui8_position,
                t_g_audio_view.ui8_duration, ui4_pb_pos));
#endif

    if(t_g_audio_view.b_ctrl_panel_show)
    {
        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_CUR_TIME,
                                             (VOID*)(UINT32)(t_g_audio_view.ui8_position),
                                             b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_TOTAL_TIME,
                                             (VOID*)(UINT32)(t_g_audio_view.ui8_duration),
                                             b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_ELAPSE_TIME,
                                             (VOID*)(UINT32)(t_g_audio_view.ui8_position),
                                             b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_REMAIN_TIME,
                                             (VOID*)(UINT32)(t_g_audio_view.ui8_duration - t_g_audio_view.ui8_position),
                                             b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_PG_POS,
                                             (VOID*)ui4_pb_pos,
                                             b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);

        return MMPR_OK;
    }
    else
    {
        MMP_TB_POS_INFO_T t_time_type;

        c_memset(&t_time_type, 0, sizeof(MMP_TB_POS_INFO_T));

        t_time_type.e_pos_type = MMP_TB_POS_TYPE_TIME;
        t_time_type.u.ui4_time_dur = (UINT32)t_g_audio_view.ui8_duration;
        t_time_type.v.ui4_time_pos = (UINT32)t_g_audio_view.ui8_position;

        i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                              MMP_AP_TB_CMD_SET_TIME,
                                              (VOID*)&t_time_type,
                                              (b_repaint? MMP_TB_SYNC_REPAINT:MMP_TB_NON_REPAINT));
       MMPR_LOG_ON_FAIL(i4_ret);
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_hide_msg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _audio_player_hide_msg(VOID* pv_tag1,
                                 VOID* pv_tag2,
                                 VOID* pv_tag3,
                                 VOID* pv_tag4)
{
    INT32 i4_ret = 0;

    if(t_g_audio_view.b_msg_show)
    {
        t_g_audio_view.b_msg_show = FALSE;
        i4_ret = mmp_info_bar_hide();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

}
/*-----------------------------------------------------------------------------
 * Name: _audio_player_timer_nfy_fct
 *
 * Description: This callback function is called when timers expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _audio_player_timer_nfy_fct (HANDLE_T h_timer, VOID* pv_tag)
{
    INT32 i4_ret = 0;

    if (h_timer == t_g_audio_view.h_timer_invaid_file_msg)
    {
        i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_player_skip_invalid_file,
                                    &h_timer, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (h_timer == t_g_audio_view.h_timer_timeout)
    {
        i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_player_update_pos,
                                    &h_timer, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (h_timer == t_g_audio_view.h_timer_msg)
    {
        i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_player_hide_msg,
                                    &h_timer, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_play
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_play(VOID)
{
    INT32 i4_ret_1 =0;
    INT32 i4_ret =0;

    /*When replay, reset flag*/
    if(MMP_VE_PLAY_STAT_OPEN == t_g_audio_view.e_player_status||
       MMP_VE_PLAY_STAT_STOP == t_g_audio_view.e_player_status||
       MMP_VE_PLAY_STAT_CLOSE == t_g_audio_view.e_player_status)
    {
        t_g_audio_view.b_code_not_support =FALSE;
        /*Always set to invalide file*/
        t_g_audio_view.b_crt_play_invalid_file = TRUE;

        t_g_audio_view.ui8_position = (UINT32)0;
        t_g_audio_view.ui8_duration = (UINT32)0;
    }


    i4_ret_1 = video_engine_play(t_g_audio_view.pv_engine_inst, NULL);
#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if ((MMPR_OK != i4_ret_1) && (MMPR_IS_PLAYED != i4_ret_1))
    {
        if (a_mmp_dmr_is_active())
        {
            c_dmr_submit_player_status(
                        PLAYER_MEDIATYPE_AUDIO,
                        PLAYER_NFYCODE_FILE_NOT_SUPPORT
                        );
        }
    }
#endif
    if(MMPR_IS_PLAYED == i4_ret_1)
    {
        i4_ret = _audio_player_update_status(TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

        return MMPR_IS_PLAYED;
    }
    else if(MMPR_NOT_SUPPORT == i4_ret_1)
    {
        t_g_audio_view.e_last_open_elm_ret = _MMP_AP_LAST_OPEN_ELM_RET_FAILED;
        i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_player_handle_invalid_file,
                                    NULL, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
        return MMPR_OK;
    }
    else if(MMPR_INTERNAL_ERROR == i4_ret_1)
    {
        t_g_audio_view.e_last_open_elm_ret = _MMP_AP_LAST_OPEN_ELM_RET_CORRUPT;
        i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_player_handle_invalid_file,
                                    NULL, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
        return MMPR_IS_PLAYED;
    }

    return i4_ret_1;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_pause
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_pause(VOID)
{
    INT32                       i4_ret = 0,i4_ret_1 = 0;

    i4_ret_1 = video_engine_pause(t_g_audio_view.pv_engine_inst);
    if(MMPR_OK != i4_ret_1 && MMPR_IS_PAUSED != i4_ret_1)
    {
        MMPR_LOG_ON_FAIL(i4_ret);
        if(!t_g_audio_view.b_crt_play_invalid_file)
        {
            i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }

    _audio_player_update_pos(NULL, NULL, NULL, NULL);

    i4_ret = _audio_player_update_status(TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret_1;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_stop
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_stop(VOID)
{
    INT32 i4_ret = 0;

    i4_ret = video_engine_stop(t_g_audio_view.pv_engine_inst);
    if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        MMPR_LOG_ON_FAIL(i4_ret);
        return i4_ret;
    }

    i4_ret = _audio_player_update_status(TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_IS_STOPPED;
}
/*-----------------------------------------------------------------------------
 * Name: _audio_player_stop_cover
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_stop_cover(VOID)
{
#if defined(_MMP_VERC_PLAY_COVER_SUPPORT)

    if(t_g_audio_view.b_has_cover_pic)
    {
        BOOL b_is_show = FALSE;
        MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                     MMP_AP_CUR_PLAY_INFO_COVER,
                                                     (VOID*)&b_is_show,
                                                     FALSE));
        MMPR_LOG_ON_FAIL( video_engine_cover_stop(t_g_audio_view.pv_engine_inst));
        MMPR_LOG_ON_FAIL(c_wgl_repaint(t_g_audio_view.h_frm_main, NULL, TRUE));
    }

    t_g_audio_view.b_has_cover_pic= FALSE;
#endif
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_next
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_next(VOID)
{
    INT32 i4_ret_1 = 0;
    INT32 i4_ret = 0;

    t_g_audio_view.b_code_not_support =FALSE;
    /*Always set to invalide file*/
    t_g_audio_view.b_crt_play_invalid_file = TRUE;

    t_g_audio_view.ui8_position = (UINT32)0;
    t_g_audio_view.ui8_duration = (UINT32)0;

    i4_ret = _audio_player_view_set_ab_repeat(TRUE, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    if(!t_g_audio_view.b_ctrl_panel_show)
    {
        /*Stop basic cover pic first*/
         i4_ret = _audio_player_stop_cover();
         MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = c_timer_stop(t_g_audio_view.h_timer_invaid_file_msg);
        MMPR_LOG_ON_FAIL(i4_ret);

        if(t_g_audio_view.b_msg_show)
        {
            t_g_audio_view.b_msg_show = FALSE;
            i4_ret = mmp_info_bar_hide();
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        /*Refresh option list*/
        if(MMP_AP_FLAG_OPTION_LIST_SHOW & t_g_audio_view.ui4_flag)
        {
            /*Turn off flag*/
            t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;

            i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main, WGL_NO_AUTO_REPAINT);
            MMPR_LOG_ON_FAIL(i4_ret);
            i4_ret = a_optl_hide(t_g_audio_view.h_option_list);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        if(MMP_AP_FLAG_LYRIC_LIST_SHOW & t_g_audio_view.ui4_flag)
        {
            /*Turn off flag*/
            t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_LYRIC_LIST_SHOW;

            i4_ret = c_wgl_set_focus(t_g_audio_view.h_frm_main, WGL_NO_AUTO_REPAINT);
            MMPR_LOG_ON_FAIL(i4_ret);

            i4_ret = a_optl_hide(t_g_audio_view.h_lyric_option);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        i4_ret = _audio_player_view_update_pos(t_g_audio_view.ui8_position, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    /*Dont't change follow code sequence*/
    i4_ret = video_engine_next(t_g_audio_view.pv_engine_inst, NULL);
    i4_ret_1=_audio_player_update_status(FALSE);
    MMPR_LOG_ON_FAIL(i4_ret_1);

    i4_ret_1=_audio_player_view_swap_filename(TRUE);
    MMPR_LOG_ON_FAIL(i4_ret_1);

    i4_ret_1 = _audio_player_info_handle_update_custom_info(TRUE);
    MMPR_LOG_ON_FAIL(i4_ret_1);

    if(MMPR_NOT_SUPPORT == i4_ret)
    {
        t_g_audio_view.e_last_open_elm_ret = _MMP_AP_LAST_OPEN_ELM_RET_FAILED;
        i4_ret_1=mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_player_handle_invalid_file,
                                    NULL, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret_1);
        return MMPR_IS_PLAYED;
    }
    else if(MMPR_INTERNAL_ERROR == i4_ret)
    {
        t_g_audio_view.e_last_open_elm_ret = _MMP_AP_LAST_OPEN_ELM_RET_CORRUPT;
        i4_ret_1=mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _audio_player_handle_invalid_file,
                                    NULL, NULL, NULL, NULL);
        MMPR_LOG_ON_FAIL(i4_ret_1);
        return MMPR_IS_PLAYED;
    }
    else if(MMPR_OK == i4_ret)
    {
    #if NEVER
            t_g_video_view.t_drm_type = e_divx_cert.t_drm_type;
    
            if(MMP_VE_DRM_TYPE_NORMAL != e_divx_cert.t_drm_type)
            {
                mmp_dc_dlg_show(
                        t_g_video_view.h_frm_main,
                        &e_divx_cert,
                        _mmp_vp_dc_btn_act_cb_fct
                        );
                return MMPR_IS_PLAYED;
            }
    #endif
            return MMPR_IS_PLAYED;
    }

    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK ;
}
/*-----------------------------------------------------------------------------
 * Name: _audio_player_preview_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_preview_activate(const MMP_FP_PREVIEW_INFO_T* pt_info)
{
    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_preview_inactivate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_preview_inactivate(VOID)
{
    INT32 i4_ret = 0;

    i4_ret = _audio_player_stop_cover();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_fast_forward
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_fast_forward(VOID)
{
    MMP_VE_FAST_FWD_TYPE_T      e_speed=MMP_VE_FAST_FWD_TYPE_2X;
    INT32                       i4_ret = 0;


    switch (t_g_audio_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_FAST_FWD:
        {
            t_g_audio_view.ui1_step <<= 1 ;

            if(t_g_audio_view.ui1_step > 32)
            {
                t_g_audio_view.ui1_step = 1;

                i4_ret = _audio_player_play();
                if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                {
                    return i4_ret;
                }

                i4_ret = _audio_player_update_status(TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                switch(t_g_audio_view.ui1_step)
                {
                    case 2:
                        e_speed = MMP_VE_FAST_FWD_TYPE_2X;
                        break;
                    case 4:
                        e_speed = MMP_VE_FAST_FWD_TYPE_4X;
                        break;
                    case 8:
                        e_speed = MMP_VE_FAST_FWD_TYPE_8X;
                        break;
                    case 16:
                        e_speed = MMP_VE_FAST_FWD_TYPE_16X;
                        break;
                    case 32:
                        e_speed = MMP_VE_FAST_FWD_TYPE_32X;
                        break;
                    default:
                        e_speed = MMP_VE_FAST_FWD_TYPE_2X;
                        break;
                }

                i4_ret = video_engine_fast_forward(t_g_audio_view.pv_engine_inst, e_speed);
                MMPR_LOG_ON_FAIL(i4_ret);
                if(MMPR_NOT_SUPPORT==i4_ret)
                {
                    if(!t_g_audio_view.b_crt_play_invalid_file)
                    {
                        i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                }

                i4_ret = _audio_player_update_status(TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_VE_PLAY_STAT_PLAY:
        case MMP_VE_PLAY_STAT_PAUSE:
        case MMP_VE_PLAY_STAT_FAST_RWD:
        case MMP_VE_PLAY_STAT_SLOW_FWD:
        case MMP_VE_PLAY_STAT_SLOW_RWD:
        {
            t_g_audio_view.ui1_step = 2;

            e_speed = MMP_VE_FAST_FWD_TYPE_2X;

            i4_ret = video_engine_fast_forward(t_g_audio_view.pv_engine_inst, e_speed);
            if(MMPR_NOT_SUPPORT==i4_ret)
            {
                if(!t_g_audio_view.b_crt_play_invalid_file)
                {
                    i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }

            i4_ret = _audio_player_update_status(TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        default:
            break;
    }

    return MMPR_IS_FAST_FORWARDED;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_fast_rewind
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_fast_rewind(VOID)
{
    MMP_VE_FAST_RWD_TYPE_T      e_speed=MMP_VE_FAST_RWD_TYPE_1X;
    INT32                i4_ret = 0;

    switch (t_g_audio_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_FAST_RWD:
        {
            t_g_audio_view.ui1_step <<= 1 ;

            if(t_g_audio_view.ui1_step > 32)
            {
                t_g_audio_view.ui1_step = 1;

                i4_ret = _audio_player_play();
                if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                {
                  return i4_ret;
                }

                i4_ret = _audio_player_update_status(TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                switch(t_g_audio_view.ui1_step)
                {
                    case 2:
                        e_speed = MMP_VE_FAST_RWD_TYPE_2X;
                        break;
                    case 4:
                        e_speed = MMP_VE_FAST_RWD_TYPE_4X;
                        break;
                    case 8:
                        e_speed = MMP_VE_FAST_RWD_TYPE_8X;
                        break;
                    case 16:
                        e_speed = MMP_VE_FAST_RWD_TYPE_16X;
                        break;
                    case 32:
                        e_speed = MMP_VE_FAST_RWD_TYPE_32X;
                        break;
                    default:
                        e_speed = MMP_VE_FAST_RWD_TYPE_2X;
                        break;
                }

                i4_ret = video_engine_fast_rewind(t_g_audio_view.pv_engine_inst, e_speed);
                if(MMPR_NOT_SUPPORT==i4_ret)
                {
                    if(!t_g_audio_view.b_crt_play_invalid_file)
                    {
                        i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
                        MMPR_LOG_ON_FAIL(i4_ret);
                    }
                }

                i4_ret = _audio_player_update_status(TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_VE_PLAY_STAT_PLAY:
        case MMP_VE_PLAY_STAT_PAUSE:
        case MMP_VE_PLAY_STAT_FAST_FWD:
        case MMP_VE_PLAY_STAT_SLOW_FWD:
        case MMP_VE_PLAY_STAT_SLOW_RWD:
        {
            t_g_audio_view.ui1_step = 2;

            e_speed = MMP_VE_FAST_RWD_TYPE_2X;

            i4_ret = video_engine_fast_rewind(t_g_audio_view.pv_engine_inst, e_speed);
            if(MMPR_NOT_SUPPORT==i4_ret)
            {
                if(!t_g_audio_view.b_crt_play_invalid_file)
                {
                    i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }

            i4_ret = _audio_player_update_status(TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        default:
            break;
    }

    return MMPR_IS_FAST_REWINDED;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _enable_key
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32  _enable_key(VOID)
{
    SIZE_T  z_info_len=0;
    UINT64  ui8_evt_src=0;
    /* Disable Remote control. */
    z_info_len = sizeof (UINT64);
    c_iom_get (t_g_audio_view.h_iom,
               IOM_GET_IRRC_EVT_SRC_MASK,
                (VOID*)& ui8_evt_src,
                & z_info_len);

    ui8_evt_src |= IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL) |
                   IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL);

    c_iom_set (t_g_audio_view.h_iom,
               IOM_SET_IRRC_EVT_SRC_MASK,
               (VOID*)& ui8_evt_src,
               sizeof (UINT64));

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _aud_only_key_process
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _aud_only_key_process(VOID*                       pv_tag1,
                                  VOID*                       pv_tag2,
                                  VOID*                       pv_tag3,
                                  VOID*                       pv_tag4)
{
    UINT32         ui4_key_code = IOM_GET_EVT_GRP_ID((UINT32)pv_tag1);
    switch(ui4_key_code) {
        case BTN_POWER:
            a_amb_power_on(FALSE);
            break;

        default:
            if((MMP_AP_FLAG_AUD_ONLY&t_g_audio_view.ui4_flag))
            {
                SM_COMMAND_T     at_scc_cmds [4];

                DBG_LOG_PRINT(("Turn on backlight & LVDS \n"));

                /* Turn on backlight & LVDS */
                at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
                at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_DISP;
                at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
                at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
                at_scc_cmds [2].e_code      = SCC_CMD_CODE_DISP_CTRL;
                at_scc_cmds [2].u.ui4_data  = SCC_DISP_CTRL_ENABLE;

                at_scc_cmds [3].e_code      = SM_CMD_CODE_END;
                c_scc_comp_grp_set (at_scc_cmds);

                /*Turn off flag*/
                t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_AUD_ONLY;

                _enable_key();
            }
            break;
        }
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
    INT32 i4_ret = 0;
    BOOL b_aud_only=FALSE;

    b_aud_only = (BOOL)(MMP_AP_FLAG_AUD_ONLY&t_g_audio_view.ui4_flag);

    if(b_aud_only &&
      (e_nfy_cond == IOM_NFY_COND_BTN_DOWN ||
       e_nfy_cond == IOM_NFY_COND_BTN_REPEAT))
    {
        i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                    _aud_only_key_process,
                                    (VOID*)ui4_evt_code,
                                    (VOID*)e_nfy_cond,
                                    (VOID*)NULL,
                                    (VOID*)NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
}
/*-----------------------------------------------------------------------------
 * Name: _audio_player_load_cover
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_load_cover(VOID)
{
    SIZE_T  z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
        UTF16_T w2s_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
        CHAR ps[MMP_AP_INFO_MAX_STR_LEN] = {0};
        INT32   i4_ret = 0;
        APPL_SPLAYER_MUSIC_COVER_T tMusicCoverInfo;
        WGL_IMG_INFO_T          t_img_info;
    
        c_memset(&tMusicCoverInfo, 0, sizeof(tMusicCoverInfo));
    
         MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this = NULL;
         pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)t_g_audio_view.pv_ctrl_panel_inst;
         //close the last music's cover
         i4_ret = c_wgl_set_visibility(pt_this->h_audio_play_img_fr, WGL_SW_HIDE_RECURSIVE);
         if(i4_ret != WGLR_OK)
         {
             DBG_LOG_PRINT(("[Jundi][%s %d] close the last music cover\n",__FUNCTION__,__LINE__));
             return MMPR_FAIL;
         }
    
 
         {
             i4_ret = video_engine_get_music_cover(&tMusicCoverInfo);
             if(MMPR_OK != i4_ret)
             {
                DBG_LOG_PRINT(("[%s %d]video_engine_get_music_cover FAILED\n",__FUNCTION__,__LINE__));
             }
             else
             {
                if(tMusicCoverInfo.b_pic_exist == TRUE)//show the cover
                {
                    DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
                    c_memset (&t_img_info, 0, sizeof(t_img_info)) ;
                    t_img_info.e_type = WGL_IMG_SET_STANDARD;
                    t_img_info.u_img_data.t_standard.t_enable = tMusicCoverInfo.h_cover_img;
                    t_img_info.u_img_data.t_standard.t_disable = tMusicCoverInfo.h_cover_img;
                    t_img_info.u_img_data.t_standard.t_highlight = tMusicCoverInfo.h_cover_img;
    
                    i4_ret = c_wgl_do_cmd(pt_this->h_audio_play_img_fr,
                                              WGL_CMD_GL_SET_IMAGE,
                                              WGL_PACK(WGL_IMG_FG),
                                              WGL_PACK(&t_img_info));
                    if(i4_ret != WGLR_OK)
                    {
                        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed1\n",__FUNCTION__,__LINE__));
                    }
    
                    i4_ret = c_wgl_insert(pt_this->h_main_frm,
                                          NULL_HANDLE,
                                          WGL_INSERT_TOPMOST,
                                          WGL_NO_AUTO_REPAINT);
                    if(i4_ret != WGLR_OK)
                    {
                        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed2\n",__FUNCTION__,__LINE__));
                    }
    
                    i4_ret = c_wgl_insert(pt_this->h_audio_play_img_fr,
                                          NULL_HANDLE,
                                          WGL_INSERT_TOPMOST,
                                          WGL_NO_AUTO_REPAINT);
                    if(i4_ret != WGLR_OK)
                    {
                        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed3\n",__FUNCTION__,__LINE__));
                    }
    
                    i4_ret = c_wgl_set_visibility(pt_this->h_audio_play_img_fr, WGL_SW_NORMAL);
                    if(i4_ret != WGLR_OK)
                    {
                        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed5\n",__FUNCTION__,__LINE__));
                    }
                    i4_ret = c_wgl_repaint(pt_this->h_audio_play_img_fr,  NULL, TRUE);
                    if(i4_ret != WGLR_OK)
                    {
                        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed4\n",__FUNCTION__,__LINE__));
                    }
#ifdef NEVER
                    i4_ret = c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);
                    if(i4_ret != WGLR_OK)
                    {
                        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed5\n",__FUNCTION__,__LINE__));
                    }
    
                    i4_ret = c_wgl_set_visibility(pt_this->h_main_frm, WGL_SW_NORMAL);
                    if(i4_ret != WGLR_OK)
                    {
                        DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed6\n",__FUNCTION__,__LINE__));
                    }
#endif
                }
                else
                {
                    DBG_LOG_PRINT(("[%s %d]the music no cover\n",__FUNCTION__,__LINE__));
                }
            }
        }
        return MMPR_OK;

}

static VOID mmp_event_load_file_cover_fct(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    GL_RECT_T              t_rect = {0};
    MMP_FP_THUMB_COORDS_T  e_coord = MMP_FP_THUMB_COORDS_CANVAS;
    BOOL                   b_is_show = FALSE;

    SET_RECT_BY_SIZE (&t_rect,
                      MMP_AP_INFO_HANDLE_COV_PIC_X,
                      MMP_AP_INFO_HANDLE_COV_PIC_Y,
                      MMP_AP_INFO_HANDLE_COV_PIC_W,
                      MMP_AP_INFO_HANDLE_COV_PIC_H);

    CHAR * ps_file_name = (CHAR*)pv_param1;
    DBG_LOG_PRINT(("[MMP][%s %d] %s \n",__FUNCTION__,__LINE__,ps_file_name));
    if(MMPR_OK == video_engine_file_cover_load(ps_file_name,&t_rect,e_coord))
    {
        b_is_show = TRUE;
        MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                     MMP_AP_CUR_PLAY_INFO_COVER,
                                                     (VOID*)&b_is_show,
                                                     TRUE));

        MMPR_LOG_ON_FAIL(c_wgl_repaint(t_g_audio_view.h_audio_play_img_fr,  NULL, FALSE));
    }
    else
    {
        b_is_show = FALSE;
        MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                     MMP_AP_CUR_PLAY_INFO_COVER,
                                                     (VOID*)&b_is_show,
                                                     TRUE));
        t_g_audio_view.b_has_cover_pic = FALSE;
        MMPR_LOG_ON_FAIL(c_wgl_repaint(t_g_audio_view.h_audio_play_img_fr,  NULL, FALSE));
    }

    c_mem_free(ps_file_name);
    MMPR_LOG_ON_FAIL(c_wgl_repaint(t_g_audio_view.h_frm_main, NULL, TRUE));
}

static VOID _audio_load_file_cover(HANDLE_T h_timer,VOID* param)
{
    mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                mmp_event_load_file_cover_fct,
                                param, NULL, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name: _audio_player_load_cover
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_load_focus_file_cover(CHAR*  ps_file_name)
{
#if defined(_MMP_VERC_PLAY_COVER_SUPPORT)

    if (TRUE == t_g_audio_view.b_has_cover_pic)
    {
        MMPR_LOG_ON_FAIL(_audio_player_stop_cover());
    }

    t_g_audio_view.b_has_cover_pic = FALSE;
    MMPR_LOG_ON_FAIL(video_engine_file_has_cover_pic(ps_file_name,
                                                    &t_g_audio_view.b_has_cover_pic));
    DBG_LOG_PRINT(("[MMP][%s %d] %s b_has_cover_pic = %d\n",__FUNCTION__,__LINE__,ps_file_name,t_g_audio_view.b_has_cover_pic));
    if(!t_g_audio_view.b_has_cover_pic)
    {
        return MMPR_OK;
    }
    SIZE_T len = c_strlen(ps_file_name);
    CHAR* ps_file_path = c_mem_alloc(len + 1);
    if(ps_file_path)
    {
        c_memcpy(ps_file_path,ps_file_name,len);
        ps_file_path[len] = '\0';
        c_timer_stop(t_g_audio_view.h_timer_load_file_cover);
        c_timer_start(t_g_audio_view.h_timer_load_file_cover,
                      1500,
                      X_TIMER_FLAG_ONCE,
                      _audio_load_file_cover,
                      ps_file_path);
    }
#endif
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_info_handle_get_custom_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_handle_get_custom_info (VOID)
{
    INT32      i4_ret = 0;
    SIZE_T     z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
    UTF16_T    w2s_info[MMP_AP_INFO_MAX_STR_LEN] = {0};

    c_memset(w2s_info, 0, sizeof(w2s_info));
    z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
    i4_ret = video_engine_get_dtl_info(t_g_audio_view.pv_engine_inst,
                                       MMP_VE_INFO_ID_ALBUM,
                                       w2s_info,
                                       &z_buf_len);
    MMPR_LOG_ON_FAIL(i4_ret);
    if(MMPR_OK != i4_ret ||
       0 == z_buf_len ||
       0 == w2s_info[0])
    {
        c_uc_ps_to_w2s("N/A", w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    }

    c_uc_w2s_strncpy(w2s_g_album, w2s_info, MMP_AP_INFO_MAX_STR_LEN-1);
    w2s_g_album[MMP_AP_INFO_MAX_STR_LEN - 1] = 0;

    c_memset(w2s_info, 0, sizeof(w2s_info));
    z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
    i4_ret = video_engine_get_dtl_info(t_g_audio_view.pv_engine_inst,
                                       MMP_VE_INFO_ID_ARTIST,
                                       w2s_info,
                                       &z_buf_len);
    MMPR_LOG_ON_FAIL(i4_ret);
    if(MMPR_OK != i4_ret ||
       0 == z_buf_len ||
       0 == w2s_info[0])
    {
        c_uc_ps_to_w2s("N/A", w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    }

    c_uc_w2s_strncpy(w2s_g_artist, w2s_info, MMP_AP_INFO_MAX_STR_LEN-1);
    w2s_g_artist[MMP_AP_INFO_MAX_STR_LEN - 1] = 0;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_info_handle_update_custom_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_handle_update_custom_info(BOOL b_repaint)
{
    if(!t_g_audio_view.b_ctrl_panel_show)
    {
        return MMPR_FAIL;
    }

    MMPR_LOG_ON_FAIL( _audio_player_info_handle_get_custom_info());

    /*After next will preload next*/
    if(t_g_audio_view.b_ctrl_panel_show)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] \n",__FUNCTION__,__LINE__));
        MMPR_LOG_ON_FAIL( mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                      MMP_AP_CUR_PLAY_INFO_ALBUM,
                                                      (VOID*)w2s_g_album,
                                                      b_repaint));

        MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                     MMP_AP_CUR_PLAY_INFO_ARTIST,
                                                     (VOID*)w2s_g_artist,
                                                     b_repaint));
       //_audio_player_load_cover();
    }

    return MMPR_OK;
}

static INT32 _audio_player_info_basic(VOID*   pv_cmd_param)
{
    SIZE_T  z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
    UTF16_T w2s_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
    CHAR ps[MMP_AP_INFO_MAX_STR_LEN] = {0};
    INT32   i4_ret = 0;
    APPL_SPLAYER_MUSIC_COVER_T tMusicCoverInfo;
    WGL_IMG_INFO_T          t_img_info;

    c_memset(&tMusicCoverInfo, 0, sizeof(tMusicCoverInfo));

     MMP_COM_AP_PLAY_INFO_VIEW_T*  pt_this = NULL;
     pt_this = (MMP_COM_AP_PLAY_INFO_VIEW_T*)t_g_audio_view.pv_ctrl_panel_inst;
     //close the last music's cover
     i4_ret = c_wgl_set_visibility(pt_this->h_audio_play_img_fr, WGL_SW_HIDE_RECURSIVE);
     if(i4_ret != WGLR_OK)
     {
         DBG_LOG_PRINT(("[Jundi][%s %d] close the last music cover\n",__FUNCTION__,__LINE__));
         return MMPR_FAIL;
     }

     /*MMP_FP_INFO_TYPE_NAME*/
     {
         c_memset(w2s_info, 0, sizeof(w2s_info));
         z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_NAME,
                         &z_buf_len,
                         w2s_info
                         );
         if(MMPR_OK != i4_ret ||
            0 == z_buf_len||
            0 == w2s_info[0])
         {
             MMPR_LOG_ON_FAIL(i4_ret);
             c_uc_w2s_strcpy(w2s_info, L"-");
         }
         c_uc_w2s_to_ps(w2s_info,ps,MMP_AP_INFO_MAX_STR_LEN);
          MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                          MMP_AP_CUR_PLAY_INFO_FILE_NAME,
                                                          (VOID*)w2s_info,
                                                          TRUE));
#ifdef NEVER
         {
             CHAR    s_file_path[MMP_BE_MAX_PATH_LEN] = {0};

             if(MMPR_OK == mmp_lm_view_get_focus_item_full_path(s_file_path))
             {
                 _audio_player_load_focus_file_cover(s_file_path);
                 DBG_LOG_PRINT(("[MMP][%s %d][MMP_FP_INFO_TYPE_NAME] %s \n", __FUNCTION__, __LINE__,s_file_path));
             }
         }
#endif
     }

     /*MMP_FP_INFO_TYPE_ARTIST*/
     {
         c_memset(w2s_info, 0, sizeof(w2s_info));
         z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_ARTIST,
                         &z_buf_len,
                         w2s_info
                         );
         if(MMPR_OK != i4_ret ||
            0 == z_buf_len||
            0 == w2s_info[0])
         {
             MMPR_LOG_ON_FAIL(i4_ret);
             c_uc_w2s_strcpy(w2s_info, L"-");
         }
         c_uc_w2s_to_ps(w2s_info,ps,MMP_AP_INFO_MAX_STR_LEN);
         DBG_LOG_PRINT(("[MMP][%s %d][MMP_FP_INFO_TYPE_ARTIST] %s \n", __FUNCTION__, __LINE__,ps));

         MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                          MMP_AP_CUR_PLAY_INFO_ARTIST,
                                          (VOID*)w2s_info,
                                          TRUE));
     }

     /*MMP_FP_INFO_TYPE_ALBUM*/
     {
         c_memset(w2s_info, 0, sizeof(w2s_info));
         z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_ALBUM,
                         &z_buf_len,
                         w2s_info
                         );
         if(MMPR_OK != i4_ret ||
            0 == z_buf_len||
            0 == w2s_info[0])
         {
             MMPR_LOG_ON_FAIL(i4_ret);
             c_uc_w2s_strcpy(w2s_info,L"-");
         }
         c_uc_w2s_to_ps(w2s_info,ps,MMP_AP_INFO_MAX_STR_LEN);
         DBG_LOG_PRINT(("[MMP][%s %d][MMP_FP_INFO_TYPE_ALBUM] %s \n", __FUNCTION__, __LINE__,ps));

         MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                          MMP_AP_CUR_PLAY_INFO_ALBUM,
                                          (VOID*)w2s_info,
                                          TRUE));
     }

     /*MMP_FP_INFO_TYPE_DURATION*/
     {
         UINT64    ui8_duration = 0;
         SIZE_T    z_buf_len = sizeof(UINT64);
         UINT8     ui1_hh,ui1_mm,ui1_ss;

         i4_ret = mmp_ve_info_get(
                     t_g_audio_view.pv_engine_inst,
                     pv_cmd_param,
                     MMP_FP_INFO_TYPE_DURATION,
                     &z_buf_len,
                     &ui8_duration
                     );
         MMPR_LOG_ON_FAIL(i4_ret);
         mmp_util_sec_to_hh_mm_ss(ui8_duration, &ui1_hh, &ui1_mm, &ui1_ss);
         c_sprintf(ps, "%02u:%02u:%02u", ui1_hh, ui1_mm, ui1_ss);
         c_uc_ps_to_w2s(ps,w2s_info,MMP_AP_INFO_MAX_STR_LEN);
         DBG_LOG_PRINT(("[MMP][%s %d][MMP_FP_INFO_TYPE_DURATION] %s \n", __FUNCTION__, __LINE__,ps));
         MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                          MMP_AP_CUR_PLAY_INFO_DURATION,
                                          (VOID*)w2s_info,
                                          TRUE));
     }

     /*MMP_FP_INFO_TYPE_GENRE*/
     {
         c_memset(w2s_info, 0, sizeof(w2s_info));
         z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_GENRE,
                         &z_buf_len,
                         w2s_info
                         );
         if(MMPR_OK != i4_ret ||
            0 == z_buf_len||
            0 == w2s_info[0])
         {
             MMPR_LOG_ON_FAIL(i4_ret);
             c_uc_w2s_strcpy(w2s_info, L"-");
         }

          MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                          MMP_AP_CUR_PLAY_INFO_GERNER,
                                          (VOID*)w2s_info,
                                          TRUE));
     }

     /*MMP_FP_INFO_TYPE_YEAR*/
     {
         z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_YEAR,
                         &z_buf_len,
                         w2s_info);
         if(MMPR_OK != i4_ret ||
           0 == z_buf_len||
           0 == w2s_info[0])
         {
             c_uc_w2s_strcpy(w2s_info,L"-");
         }

         MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_YEAR,
                                         (VOID*)w2s_info,
                                         TRUE));
     }

     /*MMP_FP_INFO_TYPE_SIZE*/
     {
         CHAR    sz_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
         UINT64  ui8_duration = 0;

         c_memset(w2s_info, 0, sizeof(w2s_info));

         z_buf_len = sizeof(UINT64);
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_SIZE,
                         &z_buf_len,
                         &ui8_duration
                         );
         if(MMPR_OK!=i4_ret ||
            0 == z_buf_len||
            0 == ui8_duration)
         {
             MMPR_LOG_ON_FAIL(i4_ret);
             c_uc_w2s_strcpy(w2s_info,L"-");
         }
         else if (1024 * 1024 <= ui8_duration)
         {
             c_sprintf(sz_info,
                       "%.2fM",
                       (ui8_duration*1.0)/(1024*1024));
         }
         else if (1024 <= ui8_duration)
         {
             c_sprintf(sz_info,
                       "%.2fK",
                       (ui8_duration*1.0)/(1024));
         }
         else
         {
             c_sprintf(sz_info,
                       "%dB",
                       ui8_duration);
         }

         i4_ret = c_uc_ps_to_w2s(sz_info, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
         MMPR_LOG_ON_FAIL(i4_ret);

          MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_FILE_SIZE,
                                         (VOID*)w2s_info,
                                         TRUE));
     }

     /*MMP_VE_INFO_ID_PROTECT*/
     {
         BOOL    b_protected = FALSE;

         z_buf_len             = sizeof(b_protected);
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_PROTECT,
                         &z_buf_len,
                         &b_protected
                         );
         MMPR_LOG_ON_FAIL(i4_ret);

         MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_PROTECT,
                                         (VOID*)MLM_MMP_TEXT(t_g_audio_view.ui2_lang, b_protected ? MLM_MMP_KEY_YES : MLM_MMP_KEY_NO),
                                         TRUE));
     }

     /*MMP_FP_INFO_TYPE_TITLE*/
     {
         z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_TITLE,
                         &z_buf_len,
                         w2s_info);
         if(MMPR_OK != i4_ret ||
           0 == z_buf_len||
           0 == w2s_info[0])
         {
             c_uc_w2s_strcpy(w2s_info,L"-");
         }

         MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_TITLE,
                                         (VOID*)w2s_info,
                                         TRUE));
     }

     /*MMP_FP_INFO_TYPE_DIRECTOR*/
     {
         z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_DIRECTOR,
                         &z_buf_len,
                         w2s_info);
         if(MMPR_OK != i4_ret ||
           0 == z_buf_len||
           0 == w2s_info[0])
         {
             c_uc_w2s_strcpy(w2s_info,L"-");
         }

         MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_DIRECTOR,
                                         (VOID*)w2s_info,
                                         TRUE));
     }

     /*MMP_FP_INFO_TYPE_DIRECTOR*/
     {
         z_buf_len = MMP_AP_INFO_MAX_STR_LEN;
         i4_ret = mmp_ve_info_get(
                         t_g_audio_view.pv_engine_inst,
                         pv_cmd_param,
                         MMP_FP_INFO_TYPE_PRODUCER,
                         &z_buf_len,
                         w2s_info);
         if(MMPR_OK != i4_ret ||
           0 == z_buf_len||
           0 == w2s_info[0])
         {
             c_uc_w2s_strcpy(w2s_info,L"-");
         }

         MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_PRODUCER,
                                         (VOID*)w2s_info,
                                         TRUE));
     }
     {
         i4_ret = video_engine_get_music_cover(&tMusicCoverInfo);
         if(MMPR_OK != i4_ret)
         {
            DBG_LOG_PRINT(("[%s %d]video_engine_get_music_cover FAILED\n",__FUNCTION__,__LINE__));
         }
         else
         {
            if(tMusicCoverInfo.b_pic_exist == TRUE)//show the cover
            {
                DBG_LOG_PRINT(("[%s %d]\n",__FUNCTION__,__LINE__));
                c_memset (&t_img_info, 0, sizeof(t_img_info)) ;
                t_img_info.e_type = WGL_IMG_SET_STANDARD;
                t_img_info.u_img_data.t_standard.t_enable = tMusicCoverInfo.h_cover_img;
                t_img_info.u_img_data.t_standard.t_disable = tMusicCoverInfo.h_cover_img;
                t_img_info.u_img_data.t_standard.t_highlight = tMusicCoverInfo.h_cover_img;

                i4_ret = c_wgl_do_cmd(pt_this->h_audio_play_img_fr,
                                          WGL_CMD_GL_SET_IMAGE,
                                          WGL_PACK(WGL_IMG_FG),
                                          WGL_PACK(&t_img_info));
                if(i4_ret != WGLR_OK)
                {
                    DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed1\n",__FUNCTION__,__LINE__));
                }

                i4_ret = c_wgl_insert(pt_this->h_main_frm,
                                      NULL_HANDLE,
                                      WGL_INSERT_TOPMOST,
                                      WGL_NO_AUTO_REPAINT);
                if(i4_ret != WGLR_OK)
                {
                    DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed2\n",__FUNCTION__,__LINE__));
                }

                i4_ret = c_wgl_insert(pt_this->h_audio_play_img_fr,
                                      NULL_HANDLE,
                                      WGL_INSERT_TOPMOST,
                                      WGL_NO_AUTO_REPAINT);
                if(i4_ret != WGLR_OK)
                {
                    DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed3\n",__FUNCTION__,__LINE__));
                }

                i4_ret = c_wgl_set_visibility(pt_this->h_audio_play_img_fr, WGL_SW_NORMAL);
                if(i4_ret != WGLR_OK)
                {
                    DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed5\n",__FUNCTION__,__LINE__));
                }
                i4_ret = c_wgl_repaint(pt_this->h_audio_play_img_fr,  NULL, TRUE);
                if(i4_ret != WGLR_OK)
                {
                    DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed4\n",__FUNCTION__,__LINE__));
                }
#ifdef NEVER
                i4_ret = c_wgl_repaint(pt_this->h_main_frm, NULL, TRUE);
                if(i4_ret != WGLR_OK)
                {
                    DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed5\n",__FUNCTION__,__LINE__));
                }

                i4_ret = c_wgl_set_visibility(pt_this->h_main_frm, WGL_SW_NORMAL);
                if(i4_ret != WGLR_OK)
                {
                    DBG_LOG_PRINT(("[Jundi][%s %d] create cover failed6\n",__FUNCTION__,__LINE__));
                }
#endif
            }
            else
            {
                DBG_LOG_PRINT(("[%s %d]the music no cover\n",__FUNCTION__,__LINE__));
            }
        }
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_info_handle_update_play_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_handle_update_play_item(
                                    VOID*                       pv_info_hdlr_inst,
                                    MMP_FP_INFO_HDLR_CMD_ID_T   e_cmd,
                                    VOID*                       pv_cmd_param)
{
    INT32      i4_ret = 0;
    UINT32     ui4_pb_pos = 0;
    BOOL       b_repaint = FALSE;;
    ISO_639_LANG_T  s639_lang = {0};

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<MMP AP>Can't init lanugage \r\n"));
        t_g_audio_view.ui2_lang =0;
    }
    else
    {
        t_g_audio_view.ui2_lang = mlm_mmp_s639_to_langidx(s639_lang);
    }

    if(NULL == t_g_audio_view.pv_ctrl_panel_inst ||
       pv_info_hdlr_inst != (VOID*)t_g_audio_view.pv_ctrl_panel_inst )
    {
        MMPR_LOG_ON_FAIL(MMPR_FAIL);
        return MMPR_OK;
    }

    t_g_audio_view.b_ctrl_panel_show = TRUE;
    a_mmp_audio_show_playback_info(TRUE);

    do
    {
        _audio_player_info_basic(pv_cmd_param);

        /*For repaint issue*/
        if(0 != t_g_audio_view.ui8_duration)
        {
            i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                                 MMP_AP_CUR_PLAY_INFO_REMAIN_TIME,
                                                 (VOID*)(UINT32)(t_g_audio_view.ui8_duration - t_g_audio_view.ui8_position),
                                                 b_repaint);
            if(MMPR_OK != i4_ret)
            {
                break;
            }
        }

        /* set Pb position */
        if (t_g_audio_view.ui8_duration == 0)
        {
            ui4_pb_pos = 0;
        }
        else
        {
            ui4_pb_pos = (UINT32)(t_g_audio_view.ui8_position*100/t_g_audio_view.ui8_duration);
        }

        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_PG_POS,
                                             (VOID*)ui4_pb_pos,
                                             b_repaint);
        if(MMPR_OK!=i4_ret)
        {
            break;
        }

        i4_ret = mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                             MMP_AP_CUR_PLAY_INFO_FILE_NAME,
                                             (VOID*)w2s_g_file,
                                             b_repaint);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        i4_ret = _audio_player_info_handle_update_custom_info(b_repaint);
        MMPR_LOG_ON_FAIL(i4_ret);

        /* Please don't change follow sequence for UI issue */
        i4_ret = mmp_com_ui_ap_info_frm_active(t_g_audio_view.pv_ctrl_panel_inst,
                                               t_g_audio_view.ui2_lang,
                                               TRUE);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
    }while(0);

    /*Please don't change flow*/
    if(NULL_HANDLE != t_g_audio_view.h_mmp_fb_eq)
    {
        i4_ret = a_mmp_eq_show(t_g_audio_view.h_mmp_fb_eq, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_info_handle_update_focus_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_handle_update_focus_item(
                            VOID*                       pv_info_hdlr_inst,
                            MMP_FP_INFO_HDLR_CMD_ID_T   e_cmd,
                            VOID*                       pv_cmd_param)
{
    if(NULL == t_g_audio_view.pv_ctrl_panel_inst)
    {
        MMPR_LOG_ON_FAIL(MMPR_FAIL);
        return MMPR_OK;
    }

    if ((MMP_COM_FP_INFO_UI_TYPE_TM == t_g_audio_view.e_focus_info_type) ||
        (MMP_COM_FP_INFO_UI_TYPE_LM == t_g_audio_view.e_focus_info_type))
    {
        _audio_player_info_basic(pv_cmd_param);

        /* Please don't change follow sequence for UI issue */
        MMPR_LOG_ON_FAIL(mmp_com_ui_ap_info_frm_active(t_g_audio_view.pv_ctrl_panel_inst,
                                                       t_g_audio_view.ui2_lang,
                                                       TRUE));
    }
    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_info_handle_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_handle_show(VOID*                       pv_info_hdlr_inst,
                                            MMP_FP_INFO_HDLR_CMD_ID_T   e_cmd,
                                            VOID*                       pv_cmd_param)
{
    if(pv_info_hdlr_inst == (VOID*)t_g_audio_view.pv_ctrl_panel_inst)
    {
        MMPR_LOG_ON_FAIL( _audio_player_info_handle_update_play_item(pv_info_hdlr_inst,
                                                                     e_cmd,
                                                                     pv_cmd_param));
    }
    return MMPR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _audio_player_info_handle_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_handle_hide(VOID* pv_info_hdlr_inst,
                                            MMP_FP_INFO_HDLR_CMD_ID_T e_cmd,
                                            VOID* pv_cmd_param)
{
    INT32      i4_ret = 0;

    if(pv_info_hdlr_inst == (VOID*)t_g_audio_view.pv_ctrl_panel_inst)
    {
        /*Hide Ctrl Panel*/
        if(NULL_HANDLE != t_g_audio_view.h_mmp_fb_eq)
        {
            i4_ret = a_mmp_eq_show(t_g_audio_view.h_mmp_fb_eq,FALSE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        if(NULL != t_g_audio_view.pv_ctrl_panel_inst)
        {
            i4_ret = mmp_com_ui_ap_info_frm_inactive(t_g_audio_view.pv_ctrl_panel_inst,
                                                     TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        t_g_audio_view.b_ctrl_panel_show = FALSE;
    }
    else
    {
        /*Hide Focus info*/
        if(NULL != t_g_audio_view.pv_focus_info_inst)
        {
            i4_ret = mmp_com_ui_focus_info_frm_inactive(t_g_audio_view.pv_focus_info_inst,
                                                        (BOOL)(UINT32)pv_cmd_param);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
    }

    return MMPR_OK;
}

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
static VOID _mmp_ap_nfy_for_dmr(MMP_VE_NFY_CODE_T e_code)
{
    E_PLAYER_NFY_CODE e_dmr_code;

    if (FALSE == a_mmp_dmr_is_active())
    {
        return;
    }

    switch (e_code)
    {
        case MMP_VE_NFY_CODE_MEDIA_PLAY_HAS_NO_CONTENT:
            e_dmr_code = PLAYER_NFYCODE_NO_CONTENT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_ONLY_SVC:
            e_dmr_code = PLAYER_NFYCODE_AUDIO_ONLY;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_NOT_SUPPORT:
            e_dmr_code = PLAYER_NFYCODE_AUDIO_NOT_SUPPORT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_FMT_UPDATE:
            e_dmr_code = PLAYER_NFYCODE_AUDIO_PLAYED;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_DRM_NOT_SUPPORT:
            e_dmr_code = PLAYER_NFYCODE_DRM_NOT_SUPPORT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_STOP_END:
            e_dmr_code = PLAYER_NFYCODE_STOPPED;
            break;

        case MMP_VE_NFY_CODE_MEDIA_STOP_EOS:
            e_dmr_code = PLAYER_NFYCODE_END_OF_MEDIA;
            break;

        default:
            return;
    }

    c_dmr_submit_player_status(
                PLAYER_MEDIATYPE_AUDIO,
                e_dmr_code
                );
}
#endif

extern INT32 mmp_listmode_play_next();
static VOID _mmp_ap_play_next()
{
    MMPR_LOG_ON_FAIL(mmp_listmode_play_next());
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_engine_nfy_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK             Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/

static VOID _audio_player_engine_nfy_fct(
                    MMP_VE_NFY_CODE_T               e_code,
                    VOID*                           pv_param)
{
    DBG_LOG_PRINT(("[Jundi][%s %d]\n",__FUNCTION__,__LINE__));
    MMP_FP_SHOW_NFY_COMMON_PARAM_T t_nfy_data;
    INT32    i4_ret = MMPR_OK;
    UINT32   ui4_item_num;

    UINT32         ui4_dir_num = 0;
    UINT32         ui4_file_num = 0;



    c_memset(&t_nfy_data, 0, sizeof(t_nfy_data));

    t_nfy_data.b_result = TRUE;
    t_nfy_data.e_crnt_state = MMP_PLAY_STATE_PLAYED;

    mmp_fp_show_nfy_fct show_nfy_fct = t_g_audio_view.pf_fp_show_nfy_fct;

    if (show_nfy_fct == NULL )
    {
        return;
    }
    DBG_LOG_PRINT(("[MMP][%s %d] e_code = %d\n",__FUNCTION__,__LINE__,e_code));
#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    _mmp_ap_nfy_for_dmr(e_code);
#endif

    if((MMP_VE_NFY_CODE_MEDIA_OPEN_ERR == e_code) ||
       (MMP_VE_NFY_CODE_MEDIA_OPEN_END == e_code))
    {
        mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_BROWSER, MMP_MSG_ID_AUDIO_PLAYED, NULL);
        i4_ret = _audio_player_play();
        MMPR_LOG_ON_FAIL(i4_ret);
        return;
    }

    if(MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_NOT_SUPPORT == e_code||
       MMP_VE_NFY_CODE_MEDIA_PLAY_DRM_NOT_SUPPORT == e_code||
       MMP_VE_NFY_CODE_MEDIA_PLAY_HD_NOT_SUPPORT == e_code ||
       MMP_VE_NFY_CODE_MEDIA_PLAY_HAS_NO_CONTENT == e_code)
    {
        DBG_LOG_PRINT(("_AUDIO_NOT_SUPPORT %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
        //MMPR_LOG_ON_FAIL(a_lbw_get_elem_num(t_g_listmode_view.h_file_lb,&ui4_item_num));

        i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT,
                            &ui4_dir_num,
                            &ui4_file_num);
        MMPR_LOG_ON_FAIL(i4_ret);
        ui4_item_num = ui4_dir_num + ui4_file_num;

        t_g_audio_view.b_crt_play_invalid_file = TRUE;
        t_g_audio_view.b_code_not_support =TRUE;
#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
        if(t_g_audio_view.b_eq_viewer_show)
        {
            t_g_audio_view.b_eq_viewer_show = FALSE;

            i4_ret = a_mmp_eq_show(t_g_audio_view.h_eq_viewer, FALSE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
#endif
        /*Hide option list*/
        if(MMP_AP_FLAG_OPTION_LIST_SHOW & t_g_audio_view.ui4_flag)
        {
            /*Turn off flag*/
            t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;
            a_optl_hide(t_g_audio_view.h_option_list);
        }

        /*Hide option list*/
        if(MMP_AP_FLAG_LYRIC_LIST_SHOW & t_g_audio_view.ui4_flag)
        {
            /*Turn off flag*/
            t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_LYRIC_LIST_SHOW;
            a_optl_hide(t_g_audio_view.h_lyric_option);
        }

        i4_ret = _audio_player_view_set_play_status(TRUE, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

    #ifdef MMP_ACTIVATE_AUDIO_PLAYER
        if(t_g_audio_view.ui4_flag & MMP_AP_FLAG_ACTIVATE)
    #endif
        {
            if(!t_g_audio_view.b_msg_show)
            {
                i4_ret = _audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
                MMPR_LOG_ON_FAIL(i4_ret);

                t_g_audio_view.b_msg_show = TRUE;
            }
        }

        i4_ret = c_timer_start(t_g_audio_view.h_timer_invaid_file_msg,
                               MMP_AP_TIMER_INVALID_FILE_MSG_DELAY,
                               X_TIMER_FLAG_ONCE,
                               _audio_player_timer_nfy_fct,
                               NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
        
        c_timer_stop (t_g_audio_view.h_timer_invaid_file_msg);
        if(ui4_item_num > 1)
        {
            _mmp_ap_play_next();
        }

        return;
    }

    if(MMP_VE_NFY_CODE_MEDIA_PLAY_SUBTITLE_UPDATE == e_code)
    {
        i4_ret = _audio_lyric_set_rect(NULL);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if(MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL == e_code)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d]MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL\n",__FUNCTION__,__LINE__));
#if NEVER
        t_g_audio_view.ui8_last_seek_position=0;
        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_SEEKING
                                     |MMP_AP_FLAG_SEEKING_BEGIN
                                     |MMP_AP_FLAG_PLAY_BEFORE_SEEK);

        if(MMP_AP_DETAIL_PAGE_ON == t_g_audio_view.e_detail_page)
        {
            i4_ret = _audio_player_view_refresh_detail_page(TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        if(MMP_AP_FLAG_ACTIVATE & t_g_audio_view.ui4_flag)
        {
            MMP_VE_SUB_INFO_T t_sub_info;

            i4_ret = video_engine_get_sub_info(t_g_audio_view.pv_engine_inst, &t_sub_info);
            if (MMPR_OK == i4_ret && 0 < t_sub_info.ui2_sub_num)
            {
                t_sub_info.ui2_sel_idx = 1;

                i4_ret = video_engine_sub(t_g_audio_view.pv_engine_inst, &t_sub_info);
                if (MMPR_OK != i4_ret)
                {
                    DBG_LOG_PRINT(("video_engine_sub() returns %d.\n", i4_ret));
                }
            }

#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
            t_g_audio_view.b_eq_viewer_show = TRUE;
            i4_ret = a_mmp_eq_show(t_g_audio_view.h_eq_viewer, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
#endif
        }

       switch(t_g_audio_view.e_player_status)
       {
           case MMP_VE_PLAY_STAT_OPEN:
           case MMP_VE_PLAY_STAT_STOP:
           {
               t_g_audio_view.pf_fp_show_nfy_fct(
                                t_g_audio_view.pv_mmp_tag,
                                t_g_audio_view.ui4_mmc_ver,
                                MMP_FP_SHOW_NFY_ID_START_RESULT,
                                (VOID*)&t_nfy_data
                                );
           }
           break;

           case MMP_VE_PLAY_STAT_NEXT:
           {
               t_g_audio_view.pf_fp_show_nfy_fct(
                                t_g_audio_view.pv_mmp_tag,
                                t_g_audio_view.ui4_mmc_ver,
                                MMP_FP_SHOW_NFY_ID_NEXT_RESULT,
                                (VOID*)&t_nfy_data
                                );
           }
           break;

           case MMP_VE_PLAY_STAT_FAST_RWD:
           {
               /* For changing MMC's state to PLAY when FR to begining and replay */
               i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_BACK, MMP_PLAY_IDX_CURRENT);
               if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
               {
                   MMP_DBG_ERROR(("mmp_mc_list_play() fail. i4_ret = %d.\r\n", i4_ret));
               }
           }
           break;

           default:
               break;
       }

       if(t_g_audio_view.b_code_not_support)
       {
           t_g_audio_view.b_crt_play_invalid_file = TRUE;
       }
       else
       {
           t_g_audio_view.b_crt_play_invalid_file = FALSE;

           i4_ret = _audio_player_update_status(TRUE);
           MMPR_LOG_ON_FAIL(i4_ret);
       }
#else
        t_g_audio_view.ui8_last_seek_position=0;
        /*Turn off flag*/
        DBG_LOG_PRINT(("[Jundi][%s %d]t_g_audio_view.ui4_flag == %d\n",__FUNCTION__,__LINE__,t_g_audio_view.ui4_flag));
        DBG_LOG_PRINT(("[Jundi][%s %d]t_g_audio_view.e_detail_page == %d\n",__FUNCTION__,__LINE__,t_g_audio_view.e_detail_page));
        t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_SEEKING
                                     |MMP_AP_FLAG_SEEKING_BEGIN
                                     |MMP_AP_FLAG_PLAY_BEFORE_SEEK);

        if(MMP_AP_DETAIL_PAGE_ON == t_g_audio_view.e_detail_page)
        {
            i4_ret = _audio_player_view_refresh_detail_page(TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        if(MMP_AP_FLAG_ACTIVATE & t_g_audio_view.ui4_flag)
        {
            MMP_VE_SUB_INFO_T t_sub_info = {0,0,0,{-1,0},0,0,0,0};
            memset(&t_sub_info, 0, sizeof(t_sub_info));
            i4_ret = video_engine_get_sub_info(t_g_audio_view.pv_engine_inst, &t_sub_info);
            if (MMPR_OK == i4_ret && 0 < t_sub_info.ui2_sub_num)
            {
                t_sub_info.ui2_sel_idx = 1;

                i4_ret = video_engine_sub(t_g_audio_view.pv_engine_inst, &t_sub_info);
                if (MMPR_OK != i4_ret)
                {
                    DBG_LOG_PRINT(("video_engine_sub() returns %d.\n", i4_ret));
                }
            }

#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
            t_g_audio_view.b_eq_viewer_show = TRUE;
            i4_ret = a_mmp_eq_show(t_g_audio_view.h_eq_viewer, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
#endif
        }
        DBG_LOG_PRINT(("[Jundi][%s %d]t_g_audio_view.e_player_status == %d\n",__FUNCTION__,__LINE__,t_g_audio_view.e_player_status));

        if(t_g_audio_view.b_code_not_support)
        {
            t_g_audio_view.b_crt_play_invalid_file = TRUE;
        }
        else
        {
            t_g_audio_view.b_crt_play_invalid_file = FALSE;

            i4_ret = _audio_player_update_status(TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);
            i4_ret = video_engine_get_duration(
                                            t_g_audio_view.pv_engine_inst,
                                            MMP_VE_DUR_TYPE_TIME,
                                            &t_g_audio_view.ui8_duration
                                            );
            MMPR_LOG_ON_FAIL(i4_ret);

            MMPR_LOG_ON_FAIL( _audio_player_view_update_pos(t_g_audio_view.ui8_position, TRUE));

            /*For duration*/
            if(MMP_AP_DETAIL_PAGE_ON == t_g_audio_view.e_detail_page)
            {
                MMPR_LOG_ON_FAIL(_audio_player_view_refresh_detail_page(TRUE));
            }
            _mmp_ap_update_play_status();
            
            //when play normal,show the cover again
            //first check the current browser is audio player or not. If not (photo player), don't show the info
            UINT8                       ui1_crnt_browser;
            BOOL                        b_is_shown;

            /*get active browser id*/
            i4_ret = mmp_mc_browse_get_active(&ui1_crnt_browser, &b_is_shown);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_mc_browse_get_active() failed. i4_ret = %d.\r\n", i4_ret));
            }
            DBG_LOG_PRINT(("[%s %d]ui1_crnt_browser == %d\n",__FUNCTION__,__LINE__,ui1_crnt_browser));
            /*check the browser is audio player*/
            if(ui1_crnt_browser != MMP_APP_RESUME_INFO_NONE)//0 stand for photo, 1 stand for other
            {
                _audio_player_load_cover();
            }
            
            return;
        }     
#endif
    }

    if(MMP_VE_NFY_CODE_MEDIA_PLAYING_INIT_OK == e_code)
    {
        DBG_LOG_PRINT(("[%s %d]MMP_VE_NFY_CODE_MEDIA_PLAYING_INIT_OK\n",__FUNCTION__,__LINE__));
#ifdef NEVER
        //first check the current browser is audio player or not. If not (photo player), don't show the info
        UINT8                       ui1_crnt_browser;
        BOOL                        b_is_shown;

        /*get active browser id*/
        i4_ret = mmp_mc_browse_get_active(&ui1_crnt_browser, &b_is_shown);
        if(MMPR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("mmp_mc_browse_get_active() failed. i4_ret = %d.\r\n", i4_ret));
        }
        DBG_LOG_PRINT(("[%s %d]ui1_crnt_browser == %d\n",__FUNCTION__,__LINE__,ui1_crnt_browser));
        /*check the browser is audio player*/
        if(ui1_crnt_browser != MMP_APP_RESUME_INFO_NONE)//0 stand for photo, 1 stand for other
        {
            MMPR_LOG_ON_FAIL(_audio_player_view_update_play_info());
        }
#endif
        return;
    }

    if(MMP_VE_NFY_CODE_MEDIA_PLAY_DURATION_UPDATE == e_code)
    {
        /*FIXME  update duration here*/
        i4_ret = video_engine_get_duration(
                                t_g_audio_view.pv_engine_inst,
                                MMP_VE_DUR_TYPE_TIME,
                                &t_g_audio_view.ui8_duration
                                );
        MMPR_LOG_ON_FAIL(i4_ret);

    #ifdef DEBUG
        DBG_LOG_PRINT(("\n%s,%s,%d,ui8_duration=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    t_g_audio_view.ui8_duration));
    #endif

        MMPR_LOG_ON_FAIL( _audio_player_view_update_pos(t_g_audio_view.ui8_position, TRUE));

        /*For duration*/
        if(MMP_AP_DETAIL_PAGE_ON == t_g_audio_view.e_detail_page)
        {
            MMPR_LOG_ON_FAIL(_audio_player_view_refresh_detail_page(TRUE));
        }
        _mmp_ap_update_play_status();
        return;
    }

    if (MMP_VE_NFY_CODE_MEDIA_PLAY_SPEED_UPDATE == e_code)
    {
        if (MMP_VE_PLAY_STAT_PLAY != t_g_audio_view.e_player_status)
        {
            mmp_mc_list_play(MMP_GROUND_MODE_BACK, MMP_PLAY_IDX_CURRENT);
        }
    }

    if(MMP_VE_NFY_CODE_MEDIA_PLAY_SEEK_READY == e_code)
    {
        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_SEEKING
                                     |MMP_AP_FLAG_SEEKING_BEGIN);

        t_g_audio_view.ui8_last_seek_position = t_g_audio_view.ui8_duration+1;

        /*Keep before status when seek ready*/
        if(MMP_AP_FLAG_PLAY_BEFORE_SEEK & t_g_audio_view.ui4_flag)
        {
            /*Turn off flag*/
            t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_PLAY_BEFORE_SEEK;

            if(MMP_VE_PLAY_STAT_PAUSE == t_g_audio_view.e_player_status)
            {
                i4_ret = _audio_player_play_pause();
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }

        i4_ret = _audio_player_view_update_pos(t_g_audio_view.ui8_position,
                                               TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

        i4_ret = _audio_player_update_status(TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if(MMP_VE_NFY_CODE_MEDIA_STOP_BGN == e_code)
    {
        t_g_audio_view.b_crt_play_invalid_file = TRUE;
        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_SEEKING
                                     |MMP_AP_FLAG_SEEKING_BEGIN
                                     |MMP_AP_FLAG_PLAY_BEFORE_SEEK);

        /*Turn ON flag*/
        t_g_audio_view.ui4_flag |= MMP_AP_FLAG_STOPING ;
    }

    if(MMP_VE_NFY_CODE_MEDIA_STOP_EOS == e_code)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] EOS OF MUSIC PLAY\n",__FUNCTION__,__LINE__));
        t_g_audio_view.b_crt_play_invalid_file = TRUE;
        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_SEEKING
                                     |MMP_AP_FLAG_SEEKING_BEGIN
                                     |MMP_AP_FLAG_PLAY_BEFORE_SEEK);

        if(t_g_audio_view.ui8_position < t_g_audio_view.ui8_duration)
        {
            /*To fill position*/
            i4_ret = _audio_player_view_update_pos(t_g_audio_view.ui8_duration, TRUE);
            MMPR_LOG_ON_FAIL(i4_ret);

            c_thread_delay(200);
        }

        if(MMP_VE_PLAY_STAT_PAUSE == t_g_audio_view.e_player_status)
        {
            i4_ret = _audio_player_play_pause();
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        if(t_g_audio_view.b_end_of_list)
        {
            i4_ret = _audio_player_end_of_lst_proc ();
            MMPR_LOG_ON_FAIL(i4_ret);
        }

        t_g_audio_view.pf_fp_show_nfy_fct(
                    t_g_audio_view.pv_mmp_tag,
                    t_g_audio_view.ui4_mmc_ver,
                    MMP_FP_SHOW_NFY_ID_PLAY_END,
                    NULL
                    );
        _mmp_ap_update_play_status();
        _mmp_ap_play_next();
    }

    if(MMP_VE_NFY_CODE_MEDIA_STOP_END == e_code)
    {
        t_g_audio_view.b_crt_play_invalid_file = TRUE;
        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_SEEKING
                                     |MMP_AP_FLAG_SEEKING_BEGIN
                                     |MMP_AP_FLAG_PLAY_BEFORE_SEEK
                                     |MMP_AP_FLAG_STOPING);
    }
    if(MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_FMT_UPDATE == e_code)
    {
        _mmp_ap_update_play_status();
    }
    return;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_view_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_activate(AUDIO_PLAYER_VIEW_T*      pt_this)
{
    INT32           i4_ret = 0;
    SIZE_T          z_size = 0;
    MMP_PL_ATTR_T   at_attr[1];
    ISO_639_LANG_T  s639_lang = {0};

    c_memset(at_attr, 0, sizeof(at_attr));

    t_g_audio_view.b_ctrl_panel_show  = FALSE;
    t_g_audio_view.b_has_cover_pic    = FALSE;
    t_g_audio_view.b_code_not_support =FALSE;

    /*Init*/
    t_g_audio_view.ui4_flag = 0;
    /*Turn on flag*/
    t_g_audio_view.ui4_flag |= MMP_AP_FLAG_ACTIVATE;
    /*Turn off flag*/
    t_g_audio_view.ui4_flag &= ~(MMP_AP_FLAG_AUD_ONLY
                               |MMP_AP_FLAG_SEEKING
                               |MMP_AP_FLAG_SEEKING_BEGIN
                               |MMP_AP_FLAG_PLAY_BEFORE_SEEK
                               |MMP_AP_FLAG_OPTION_LIST_SHOW
                               |MMP_AP_FLAG_LYRIC_LIST_SHOW);

    t_g_audio_view.b_crt_play_invalid_file = TRUE;

    /*Stop cover pic*/
    i4_ret = _audio_player_stop_cover();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<MMP AP>Can't init lanugage \r\n"));
        t_g_audio_view.ui2_lang =0;
    }
    else
    {
        t_g_audio_view.ui2_lang = mlm_mmp_s639_to_langidx(s639_lang);
    }

    t_g_audio_view.ui8_duration = (UINT64)0;
    t_g_audio_view.ui8_position = (UINT64)0;
    t_g_audio_view.ui8_last_seek_position = 0;
    t_g_audio_view.b_end_of_list = FALSE;

    /*Repeat Parts*/
    z_size = sizeof(MMP_REPEAT_MODE_T);
    i4_ret = mmp_mc_list_get_attr(MMP_PL_ATTR_ID_BK_REPEAT,
                                  &z_size,
                                  &t_g_audio_view.e_repeat_mode);
    MMPR_LOG_ON_FAIL(i4_ret);
    if(MMP_REPEAT_MODE_ONE == t_g_audio_view.e_repeat_mode)
    {
        t_g_audio_view.e_repeat_mode = MMP_REPEAT_MODE_NONE;
    }
    at_attr[0].e_id = MMP_PL_ATTR_ID_BK_REPEAT;
    at_attr[0].pv_param = (VOID*)t_g_audio_view.e_repeat_mode;
    i4_ret = mmp_mc_list_set_attr(1, at_attr);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_view_repeat_icon_update(FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*Shuffle Parts*/
    z_size = sizeof(MMP_SHUFFLE_MODE_T);
    i4_ret = mmp_mc_list_get_attr(MMP_PL_ATTR_ID_BK_SHUFFLE,
                                  &z_size,
                                  &t_g_audio_view.e_shuffle_mode);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_view_shuffle_icon_update(FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);


    i4_ret = _audio_player_view_update_pos(t_g_audio_view.ui8_position, FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_view_set_play_status(TRUE, FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_view_set_ab_repeat(TRUE, FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                          MMP_AP_TB_CMD_SET_FILENAME,
                                          (VOID*)NULL,
                                          MMP_TB_NON_REPAINT
                                          );
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_dp_set_text_ex(t_g_audio_view.pv_detail_page_inst,
                              MMP_AP_RC_DP_LBL_ID_NEXT,
                              NULL,
                              COM_UI_NON_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);
    i4_ret =mmp_com_ui_dp_view_inactive(t_g_audio_view.pv_detail_page_inst);
    MMPR_LOG_ON_FAIL(i4_ret);
    t_g_audio_view.e_detail_page = MMP_AP_DETAIL_PAGE_OFF;

    /* Never show time code for DMR */
#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if (FALSE == a_mmp_dmr_is_active())
#endif
    {
        i4_ret = mmp_common_ui_toolbar_view_active(pt_this->pv_toolbar_inst, MMP_TB_SYNC_REPAINT);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    /*Hide option list*/
    i4_ret = a_optl_hide(t_g_audio_view.h_option_list);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = a_optl_hide(t_g_audio_view.h_lyric_option);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*vol bar*/
    i4_ret = _audio_player_update_vol_info (FALSE,NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    /**/
    i4_ret = c_wgl_set_visibility(pt_this->h_frm_main, WGL_SW_NORMAL);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_frm_main, TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _audio_player_view_inactive
 *
 * Description: This API hides view.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK             Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_view_inactive (VOID)
{
    INT32 i4_ret = 0;

    if (MMP_VE_PLAY_STAT_FAST_FWD == t_g_audio_view.e_player_status ||
        MMP_VE_PLAY_STAT_FAST_RWD == t_g_audio_view.e_player_status)
    {
       i4_ret = _audio_player_play_pause();
       MMPR_LOG_ON_FAIL(i4_ret);
    }

    /*Stop cover pic*/
    i4_ret = _audio_player_stop_cover();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = video_engine_stop_lyric(t_g_audio_view.pv_engine_inst);
    IS_MMPR_OK(i4_ret);

#ifdef APP_MMP_EQ_AUD_PLAYER_SUPPORT
    if(t_g_audio_view.b_eq_viewer_show)
    {
        t_g_audio_view.b_eq_viewer_show =FALSE;
        i4_ret = a_mmp_eq_show(t_g_audio_view.h_eq_viewer,FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
#endif

    /*Hide option list*/
    if(MMP_AP_FLAG_OPTION_LIST_SHOW & t_g_audio_view.ui4_flag)
    {
        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_OPTION_LIST_SHOW;
        i4_ret = a_optl_hide(t_g_audio_view.h_option_list);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if(MMP_AP_FLAG_LYRIC_LIST_SHOW & t_g_audio_view.ui4_flag)
    {
        /*Turn off flag*/
        t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_LYRIC_LIST_SHOW;
        i4_ret = a_optl_hide(t_g_audio_view.h_lyric_option);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if(t_g_audio_view.b_msg_show)
    {
        t_g_audio_view.b_msg_show = FALSE;
        i4_ret = mmp_info_bar_hide();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = mmp_common_ui_toolbar_view_inactive(t_g_audio_view.pv_toolbar_inst,
                                                 MMP_TB_SYNC_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*Turn off flag*/
    t_g_audio_view.ui4_flag &= ~MMP_AP_FLAG_ACTIVATE;


    i4_ret = c_wgl_show(t_g_audio_view.h_frm_main, WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);
    return  MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_open
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_open(const CHAR*         ps_filename,
                                mmp_fp_show_nfy_fct pf_nfy,
                                VOID*               pv_tag,
                                UINT32              ui4_ver)
{
    INT32    i4_ret = 0;
    CHAR *   pc_str = NULL;
    UTF16_T  w2s_filename[MMP_AP_RC_FILE_MAX_LEN]={0};

    /* Set mmc_ver */
    t_g_audio_view.ui4_mmc_ver        = ui4_ver;
    t_g_audio_view.pf_fp_show_nfy_fct = pf_nfy;
    t_g_audio_view.pv_mmp_tag         = pv_tag;

    i4_ret = _audio_lyric_set_rect(NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*FIXME*/
    i4_ret = video_engine_open(t_g_audio_view.pv_engine_inst,ps_filename);
    MMPR_LOG_ON_FAIL(i4_ret);

    /*set StatusBar file name*/
    pc_str = c_strrchr(ps_filename, MMP_AP_RC_FILE_PATH_DIV_CHAR);
    if(pc_str != NULL)
    {
        /*remove prefix*/
        pc_str = mmp_util_trim_path_prefix(ps_filename,
                                           pc_str + 1);

        i4_ret = c_uc_ps_to_w2s(pc_str,
                                w2s_filename,
                                MMP_AP_RC_FILE_MAX_LEN);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_uc_ps_to_w2s(ps_filename,
                                w2s_filename,
                                MMP_AP_RC_FILE_MAX_LEN);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    c_uc_w2s_strncpy(w2s_g_file, w2s_filename, MMP_AP_RC_FILE_MAX_LEN-1);
    w2s_g_file[MMP_AP_RC_FILE_MAX_LEN - 1] = 0;

    i4_ret = mmp_common_ui_toolbar_cmd_do(t_g_audio_view.pv_toolbar_inst,
                                          MMP_AP_TB_CMD_SET_FILENAME,
                                          (VOID*)w2s_filename,
                                          MMP_TB_SYNC_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_view_set_fileidx(TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_update_status(FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_IS_OPENED;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_close
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_close(VOID)
{
    INT32    i4_ret = 0;

    i4_ret = video_engine_close(t_g_audio_view.pv_engine_inst);
    MMPR_LOG_ON_FAIL(i4_ret);

    _audio_player_update_status(FALSE);

    return MMPR_IS_CLOSED;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_next_preload
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_next_preload(const CHAR* ps_filename)
{
    INT32    i4_ret = 0;
    CHAR *   pc_str = NULL;
    UTF16_T  w2s_next[MMP_AP_RC_FILE_MAX_LEN] = {0};

    i4_ret = video_engine_next_preload(t_g_audio_view.pv_engine_inst, ps_filename);
    DBG_LOG_PRINT(("[%s %d]i4_ret == %d\n",__FUNCTION__,__LINE__,i4_ret));
    if(MMPR_OK != i4_ret && MMPR_IS_PRELOADED != i4_ret)
    {
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    /*If filename is null, close previous "preloaded file"*/
    if (NULL != ps_filename)
    {
        /*set DetailPage next*/
        pc_str = c_strrchr(ps_filename, MMP_AP_RC_FILE_PATH_DIV_CHAR);
        if(pc_str != NULL)
        {
            pc_str = mmp_util_trim_path_prefix(ps_filename, pc_str + 1);
            c_uc_ps_to_w2s(pc_str, w2s_next, MMP_AP_RC_FILE_MAX_LEN);
        }
        else
        {
            c_uc_ps_to_w2s(ps_filename, w2s_next, MMP_AP_RC_FILE_MAX_LEN);
        }
    }

    c_uc_w2s_strncpy(w2s_g_file_next, w2s_next, MMP_AP_RC_FILE_MAX_LEN-1);
    w2s_g_file_next[MMP_AP_RC_FILE_MAX_LEN - 1] = 0;

    i4_ret = mmp_com_ui_dp_set_text_ex(
                        t_g_audio_view.pv_detail_page_inst,
                        MMP_AP_RC_DP_LBL_ID_NEXT,
                        w2s_g_file_next,
                        (t_g_audio_view.e_detail_page == MMP_AP_DETAIL_PAGE_ON)? COM_UI_SYNC_REPAINT: COM_UI_NON_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

#if 1/*Log For Linux CR*/
    CHAR    as_str_1[MMP_AP_RC_FILE_MAX_LEN]={0};
    c_uc_w2s_to_ps(w2s_g_file_next, as_str_1, MMP_AP_RC_FILE_MAX_LEN-1);

    DBG_LOG_PRINT(("Next:%s \n", as_str_1));
#endif

    return MMPR_IS_PRELOADED;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_next_attr_set
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_next_attr_set (UINT32 ui4_attr_count, const MMP_FP_SHOW_ATTR_T* at_show_attr)
{
    return video_engine_next_attr_set(t_g_audio_view.pv_engine_inst, ui4_attr_count, at_show_attr);
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_attr_set
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_attr_set (UINT32 ui4_attr_count, const MMP_FP_SHOW_ATTR_T* at_show_attr)
{
    return video_engine_attr_set(t_g_audio_view.pv_engine_inst, ui4_attr_count, at_show_attr);
}

/*----------------------------------------------------------------------------
 * Name: mmp_ap_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 mmp_ap_cmd_do(MMP_FP_SHOW_CMD_ID_T e_cmd_id, VOID* pv_cmd_param)
{
    INT32   i4_ret = 0;

    DBG_LOG_PRINT(("[MMP][%s %d] show cmd <=%s=> \n",__FUNCTION__,__LINE__,SHOW_CMD(e_cmd_id)));

    switch (e_cmd_id)
    {
        case MMP_FP_SHOW_CMD_ID_START:
        {
            UINT32 ui4_pb_pos = 0;
            i4_ret = _audio_player_play();
            MMPR_LOG_ON_FAIL(mmp_com_ui_ap_set_play_info(t_g_audio_view.pv_ctrl_panel_inst,
                                         MMP_AP_CUR_PLAY_INFO_PG_POS,
                                         (VOID*)ui4_pb_pos,
                                         TRUE));
            MMPR_LOG_ON_FAIL(a_mmp_audio_show_playback_info(TRUE));
            if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_PAUSE:
        {
            i4_ret = _audio_player_pause();
            _mmp_ap_update_play_status();
            if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_STOP:
        {
            i4_ret = _audio_player_stop();
            if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;
        case MMP_FP_SHOW_CMD_ID_STOPED:
        {
            _mmp_ap_update_play_status();
            break;
        }
        case MMP_FP_SHOW_CMD_ID_ACTIVATE:
        {
            i4_ret = _audio_player_view_activate(&t_g_audio_view);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        case MMP_FP_SHOW_CMD_ID_INACTIVATE:
        {
            i4_ret = _audio_player_view_inactive();
            MMPR_LOG_ON_FAIL(i4_ret);

            if(TRUE == (BOOL)(UINT32)pv_cmd_param)
            {
                i4_ret = _audio_player_stop();
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_NEXT:
        case MMP_FP_SHOW_CMD_ID_NEXT_EX:
        {
            t_g_audio_view.ui4_mmc_ver = (e_cmd_id == MMP_FP_SHOW_CMD_ID_NEXT_EX ?  ((MMP_FP_SHOW_NEXT_PARAM_T*)pv_cmd_param)->ui4_ver : (UINT32)pv_cmd_param);
            //MMPR_LOG_ON_FAIL(_audio_player_next());
            i4_ret =_audio_player_next();
            DBG_LOG_PRINT(("[%s %d]i4_ret == %d\n",__FUNCTION__,__LINE__,i4_ret));
            if(MMPR_OK != i4_ret)
            {
                 MMP_DBG_ERROR(("_mmp_vp_next() fail. i4_ret = %d.\r\n", i4_ret));
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_PREVIEW_ACTIVATE:
        {
            i4_ret = _audio_player_preview_activate((MMP_FP_PREVIEW_INFO_T*)pv_cmd_param);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        case MMP_FP_SHOW_CMD_ID_PREVIEW_INACTIVATE:
        {
            if(TRUE == (BOOL)(UINT32)pv_cmd_param)
            {
                i4_ret = video_engine_stop(t_g_audio_view.pv_engine_inst);
                if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
                {
                    MMPR_LOG_ON_FAIL(i4_ret);
                    return i4_ret;
                }
            }

            i4_ret = _audio_player_preview_inactivate();
            if(MMPR_OK != i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
                return i4_ret;
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_FAST_FORWARD:
        {
            i4_ret = _audio_player_fast_forward();
            if(MMPR_OK != i4_ret && MMPR_IS_FAST_FORWARDED != i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_FAST_REWIND:
        {
            i4_ret = _audio_player_fast_rewind();
            if(MMPR_OK != i4_ret && MMPR_IS_FAST_REWINDED != i4_ret)
            {
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        default:
        {
            i4_ret = MMPR_INV_ARG;
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_deinit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_deinit(VOID)
{
    INT32 i4_ret = 0;
    /* Close video_engine */
    i4_ret = c_iom_close(t_g_audio_view.h_iom);
    IS_MMPR_OK(i4_ret);

    i4_ret = c_svctx_close(t_g_audio_view.h_svctx);
    IS_MMPR_OK(i4_ret);

    video_engine_destroy(t_g_audio_view.pv_engine_inst);

    t_g_audio_view.pv_engine_inst = NULL;

    _audio_player_view_deinit(&t_g_audio_view);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_init(VOID)
{
    INT32           i4_ret = 0;
    IRRC_SETTING_T  t_irrc_setting;

    /* Reset view data. */
    c_memset (&t_g_audio_view, 0, sizeof (AUDIO_PLAYER_VIEW_T));

    /* init engine */
    i4_ret = video_engine_create(_audio_player_engine_nfy_fct, &t_g_audio_view.pv_engine_inst);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = _audio_player_view_init(&t_g_audio_view);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_svctx_open(SVCTX_NAME_MAIN,
                          &t_g_audio_view.h_svctx);
    MMPR_LOG_ON_FAIL(i4_ret);

    /* IOM Init */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
    t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;
    t_irrc_setting.b_notify_raw_data        = TRUE;

    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = IOM_HOTKEY_RPT_EVT_ITVL_FST; /* 1st repeat key */
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = IOM_HOTKEY_RPT_EVT_ITVL_OTHER; /* other repeat key */
    i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                         IOM_DEV_ID_ANY,
                         NULL,
                         (VOID*) & t_irrc_setting,
                         NULL,
                         _iom_nfy_fct,
                         &t_g_audio_view.h_iom);
    MMPR_LOG_ON_FAIL(i4_ret);


#ifdef CLI_SUPPORT
    i4_ret = mmp_audio_player_cli_init ();
    if(MMPR_OK != i4_ret)
    {
        MMPR_LOG_ON_FAIL(i4_ret);
        _audio_player_deinit();
        return i4_ret;
    }
#endif /* CLI_SUPPORT */

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_handle_msg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_handle_msg(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param)
{
    INT32                    i4_ret = 0;

    switch(e_msg_id)
    {
        case MMP_MSG_ID_APP_RESUMED:
        {
            /* Disable SCART bypass assocation */
            a_tv_set_scart_bypass_association(FALSE, FALSE);
        }
        break;

        case MMP_MSG_ID_VOL_INFO_UPD:
        {
            i4_ret = _audio_player_update_vol_info (TRUE, pv_msg_param);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        case MMP_MSG_ID_APP_PAUSED:
        case MMP_MSG_ID_MEDIA_REMOVED:
        {
            if(MMP_AP_FLAG_AUD_ONLY & t_g_audio_view.ui4_flag)
            {
                _aud_only_key_process(NULL,NULL,NULL,NULL);
            }
        }
        break;

        case MMP_MSG_ID_END_OF_PLAYLIST:
        {
            t_g_audio_view.b_end_of_list = TRUE;

            i4_ret = _audio_player_end_of_lst_proc ();
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        default:
            break;
    }

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_is_type_of
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_is_type_of(const CHAR* ps_filename, MMP_MEDIA_TYPE_T* pe_type)
{
    if(NULL == ps_filename || NULL == pe_type)
    {
        return MMPR_INV_ARG;
    }

    if(mmp_util_filter_fct_by_ext(ps_filename, (CHAR*) as_g_audio_ext, ui2_g_audio_ext_count))
    {
        *pe_type = MMP_MEDIA_TYPE_AUDIO;
    }
    else
    {
        *pe_type = MMP_MEDIA_TYPE_UNKNOWN;
    }

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_info_open
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_open(const CHAR*            ps_filename,
                                     mmp_fp_info_nfy_fct    pf_nfy,
                                     VOID*                  pv_tag,
                                     VOID**                 ppv_info_inst)
{
    return mmp_ve_info_open(t_g_audio_view.pv_engine_inst,
                            ps_filename,
                            pf_nfy,
                            pv_tag,
                            (MMP_VE_INFO_INST_PTR_T*)ppv_info_inst );
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_info_close
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_close(VOID* pv_info_inst)
{
    return mmp_ve_info_close(t_g_audio_view.pv_engine_inst, pv_info_inst);
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_info_get
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 _audio_player_info_get(VOID*              pv_info_inst,
                             MMP_FP_INFO_TYPE_T e_type,
                             SIZE_T*            pz_size,
                             UINT8*             pui1_buf)
{
    CHAR    sz_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
    UTF16_T w2s_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
    SIZE_T  z_buf_len = 0;
    MM_TM_T t_date = {0};
    UINT64  ui8_duration = 0;
    UINT8   ui1_hh = 0, ui1_mm = 0, ui1_ss = 0;
    INT32   i4_ret = 0;

    c_memset(&t_date,0,sizeof(t_date));

    if(MMP_FP_INFO_TYPE_DATE == e_type)
    {
        z_buf_len = sizeof(MM_TM_T);

        i4_ret = mmp_ve_info_get(
                        t_g_audio_view.pv_engine_inst,
                        pv_info_inst,
                        e_type,
                        &z_buf_len,
                        &t_date
                        );
        if(MMPR_OK != i4_ret || 0 == t_date.ui2_year || 1904 == t_date.ui2_year)
        {
            c_strncpy(sz_info, "-", MMP_AP_INFO_MAX_STR_LEN);
        }
        else
        {
            c_sprintf(sz_info, "%04u-%02u-%02u %02u:%02u:%02u",
                      t_date.ui2_year, t_date.ui1_month, t_date.ui1_day,
                      t_date.ui1_hour, t_date.ui1_min, t_date.ui1_sec);
        }

        c_uc_ps_to_w2s(sz_info, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    }
    else if(MMP_FP_INFO_TYPE_DURATION == e_type)
    {
        z_buf_len = sizeof(UINT64);

        i4_ret = mmp_ve_info_get(
                        t_g_audio_view.pv_engine_inst,
                        pv_info_inst,
                        e_type,
                        &z_buf_len,
                        &ui8_duration
                        );
        if(MMPR_OK != i4_ret || ui8_duration == 0)
        {
            ui1_hh = ui1_mm = ui1_ss =0;
            //c_strncpy(sz_info, "-", MMP_AP_INFO_MAX_STR_LEN);
            c_sprintf(sz_info, "%02u:%02u:%02u", ui1_hh, ui1_mm, ui1_ss);
        }
        else
        {
            mmp_util_sec_to_hh_mm_ss(ui8_duration, &ui1_hh, &ui1_mm, &ui1_ss);
            c_sprintf(sz_info, "%02u:%02u:%02u", ui1_hh, ui1_mm, ui1_ss);
        }

        c_uc_ps_to_w2s(sz_info, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
    }
    else
    {
        z_buf_len = MMP_AP_INFO_MAX_STR_LEN;

        i4_ret = mmp_ve_info_get(
                        t_g_audio_view.pv_engine_inst,
                        pv_info_inst,
                        e_type,
                        &z_buf_len,
                        w2s_info
                        );
        if(MMPR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d,z_buf_len=%d,e_type=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        i4_ret, z_buf_len, e_type));
            return MMPR_FAIL;
        }
        if(0 == z_buf_len)
        {
            c_strncpy(sz_info, "N/A", MMP_AP_INFO_MAX_STR_LEN);
            c_uc_ps_to_w2s(sz_info, w2s_info, MMP_AP_INFO_MAX_STR_LEN);
        }
    }
    z_buf_len = (c_uc_w2s_strlen(w2s_info) + 1) * 2;
    if(z_buf_len < *pz_size)
    {
        if(z_buf_len < MMP_AP_INFO_MAX_STR_LEN)
        {
            c_memcpy(pui1_buf, w2s_info, z_buf_len);
        }
    }
    else
    {
        if(*pz_size < MMP_AP_INFO_MAX_STR_LEN)
        {
            c_memcpy(pui1_buf, w2s_info, *pz_size);
        }
    }

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_info_set
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_set(VOID* pv_info_inst,
                              MMP_FP_INFO_TYPE_T e_type,
                              SIZE_T* pz_size,
                              UINT8* pui1_buf)
{
    return  mmp_ve_info_set(t_g_audio_view.pv_engine_inst,
                            pv_info_inst,
                            e_type,
                            pz_size,
                            pui1_buf);
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_info_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_cmd_do(VOID* pv_info_inst,
                                 MMP_FP_INFO_CMD_ID_T e_cmd,
                                 VOID* pv_cmd_param)
{
    return mmp_ve_info_cmd_do(t_g_audio_view.pv_engine_inst,
                              pv_info_inst,
                              e_cmd,
                              pv_cmd_param);
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_info_cmd_res_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_cmd_res_init(VOID)
{
    return mmp_ve_info_cmd_res_init(t_g_audio_view.pv_engine_inst);
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_info_cmd_res_reset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_cmd_res_reset(VOID)
{
    return mmp_ve_info_cmd_res_reset(t_g_audio_view.pv_engine_inst);
}
/*----------------------------------------------------------------------------
 * Name: _audio_player_info_cmd_res_deinit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_cmd_res_deinit(VOID)
{
    return mmp_ve_info_cmd_res_deinit(t_g_audio_view.pv_engine_inst);
}

/*----------------------------------------------------------------------------
 * Name: _audio_player_info_hdlr_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _audio_player_info_hdlr_init(MMP_FP_INFO_HDLR_INIT_PARAM_T*    pt_param,
                                          VOID**                            ppv_info_hdlr_inst)
{
    MMP_EQ_INIT_T   t_eq_init = {0};
    INT32           i4_ret = 0;
    UINT16          ui2_elem_h = 0;
    UINT16          ui2_elem_w = 0;
    UINT16          ui2_elem_insert = 0;
    UINT16          ui2_bar_insert = 0;
    MMP_COM_FP_INFO_UI_TYPE_T e_ui_type=MMP_COM_FP_INFO_UI_TYPE_LAST;

    MMP_DBG_INFO(("_audio_player_info_hdlr_init Type:%d \n",pt_param->e_ui_type));

    /*Player Activate, not deal with ctrl panel case*/
    if(MMP_AP_FLAG_ACTIVATE & t_g_audio_view.ui4_flag)
    {
        t_g_audio_view.b_ctrl_panel_show = FALSE;
        return MMPR_OK;
    }
    else
    {
        t_g_audio_view.b_ctrl_panel_show = TRUE;
    }

    /*Ctrl Panel Parts*/
    if(MMP_FP_INFO_HDLR_UI_TYPE_TM_ACT_BK == pt_param->e_ui_type)
    {
        e_ui_type = MMP_COM_FP_INFO_UI_TYPE_TM;
    }
    else if(MMP_FP_INFO_HDLR_UI_TYPE_LM_ACT_BK == pt_param->e_ui_type ||
            MMP_FP_INFO_HDLR_UI_TYPE_LM_FOCUS  == pt_param->e_ui_type)
    {
        e_ui_type = MMP_COM_FP_INFO_UI_TYPE_LM;
    }
    else
    {
        e_ui_type = MMP_COM_FP_INFO_UI_TYPE_LAST;
    }

    if(e_ui_type!= MMP_COM_FP_INFO_UI_TYPE_LAST &&
       (NULL == t_g_audio_view.pv_ctrl_panel_inst))
    {
        t_g_audio_view.e_ctrl_panel_type = e_ui_type;
        i4_ret = mmp_com_ui_ap_info_frm_create(pt_param->h_parent,
                                               t_g_audio_view.e_ctrl_panel_type,
                                               (VOID *)&(t_g_audio_view.pv_ctrl_panel_inst));
        MMPR_LOG_ON_FAIL(i4_ret);

        *ppv_info_hdlr_inst = (t_g_audio_view.pv_ctrl_panel_inst);
     }

    /*EQ Parts*/
    if(MMP_FP_INFO_HDLR_UI_TYPE_TM_ACT_BK == pt_param->e_ui_type &&
       NULL_HANDLE == t_g_audio_view.h_mmp_fb_eq)
    {
        ui2_elem_h      = MMP_EQ_ELE_T_H;
        ui2_elem_w      = MMP_EQ_ELE_T_W;
        ui2_elem_insert = MMP_EQ_ELE_T_INSERT;
        ui2_bar_insert  = MMP_EQ_BAR_T_INSERT;

        t_eq_init.t_rect.i4_left    = pt_param->pt_rect->i4_left+MMP_EQ_TM_OFFSET_X;
        t_eq_init.t_rect.i4_top     = pt_param->pt_rect->i4_top+MMP_EQ_TM_OFFSET_Y;
        t_eq_init.t_rect.i4_right   = pt_param->pt_rect->i4_right;
        t_eq_init.t_rect.i4_bottom  = pt_param->pt_rect->i4_bottom+MMP_EQ_TM_OFFSET_Y;

        t_eq_init.h_parent          = pt_param->h_parent;
        t_eq_init.ui1_alpha         = 255;
        t_eq_init.ui4_style         = 0;
        t_eq_init.t_bk_clr          = t_g_mmp_color_transp;
        t_eq_init.t_bar_low_clr     = t_g_mmp_color_bar_low;
        t_eq_init.t_bar_mid_clr     = t_g_mmp_color_bar_mid;
        t_eq_init.t_bar_high_clr    = t_g_mmp_color_bar_high;

        t_eq_init.ui2_bar_element_height    = ui2_elem_h;
        t_eq_init.ui2_bar_element_width     = ui2_elem_w;
        t_eq_init.ui2_bar_element_insert    = ui2_elem_insert;
        t_eq_init.ui2_bar_insert            = ui2_bar_insert;

        i4_ret = a_mmp_eq_create(&t_eq_init,
                                 &t_g_audio_view.h_mmp_fb_eq);
        MMPR_LOG_ON_FAIL(i4_ret);

        if(MMPR_OK != i4_ret &&
           NULL_HANDLE != t_g_audio_view.h_mmp_fb_eq)
        {
            i4_ret = a_mmp_eq_destroy(t_g_audio_view.h_mmp_fb_eq);
            MMPR_LOG_ON_FAIL(i4_ret);
            t_g_audio_view.h_mmp_fb_eq = NULL_HANDLE;
        }
    }

   /*Focus Info hanlder Parts*/
    if (MMP_FP_INFO_HDLR_UI_TYPE_TM_FOCUS == pt_param->e_ui_type)
    {
        e_ui_type = MMP_COM_FP_INFO_UI_TYPE_TM;
    }
    else if(MMP_FP_INFO_HDLR_UI_TYPE_LM_FOCUS == pt_param->e_ui_type)
    {
        e_ui_type = MMP_COM_FP_INFO_UI_TYPE_LM;
    }
    else
    {
        e_ui_type = MMP_COM_FP_INFO_UI_TYPE_LAST;
    }

    if(e_ui_type!=MMP_COM_FP_INFO_UI_TYPE_LAST &&
       NULL == t_g_audio_view.pv_focus_info_inst)

    {
        t_g_audio_view.e_focus_info_type = e_ui_type;

        i4_ret = mmp_com_ui_focus_info_frm_create(pt_param->h_parent,
                                                  e_ui_type,
                                                  MMP_COM_INFO_FP_TYPE_AP,
                                                  (VOID **)&(t_g_audio_view.pv_focus_info_inst));
        MMPR_LOG_ON_FAIL(i4_ret);

        *ppv_info_hdlr_inst = (t_g_audio_view.pv_focus_info_inst);
    }

    return i4_ret;
}

static INT32 _audio_player_info_hdlr_deinit(VOID* pv_info_hdlr_inst)
{
    INT32                i4_ret = 0;

    MMP_DBG_INFO(("_audio_player_info_hdlr_deinit \n"));

    t_g_audio_view.b_ctrl_panel_show = FALSE;
    /*This is Must */
    if(NULL_HANDLE != t_g_audio_view.h_mmp_fb_eq)
    {
        i4_ret = a_mmp_eq_destroy(t_g_audio_view.h_mmp_fb_eq);
        MMPR_LOG_ON_FAIL(i4_ret);

        t_g_audio_view.h_mmp_fb_eq = NULL_HANDLE;
    }

    if (t_g_audio_view.pv_ctrl_panel_inst)
    {
        i4_ret = mmp_com_ui_ap_info_frm_destroy(t_g_audio_view.e_ctrl_panel_type,
                                                t_g_audio_view.pv_ctrl_panel_inst);
        MMPR_LOG_ON_FAIL(i4_ret);

        t_g_audio_view.pv_ctrl_panel_inst = NULL;
    }

    if (TRUE == t_g_audio_view.b_has_cover_pic)
    {
        i4_ret = video_engine_cover_stop(t_g_audio_view.pv_engine_inst);
        MMPR_LOG_ON_FAIL(i4_ret);

        t_g_audio_view.b_has_cover_pic = FALSE;
    }

    if (t_g_audio_view.pv_focus_info_inst &&
        pv_info_hdlr_inst == t_g_audio_view.pv_focus_info_inst)
    {
        i4_ret = mmp_com_ui_focus_info_frm_destroy(t_g_audio_view.e_focus_info_type,
                                                   MMP_COM_INFO_FP_TYPE_AP,
                                                   t_g_audio_view.pv_focus_info_inst);
        MMPR_LOG_ON_FAIL(i4_ret);

        t_g_audio_view.pv_focus_info_inst = NULL;
    }

    if(t_g_audio_view.b_msg_show)
    {
        t_g_audio_view.b_msg_show = FALSE;
        i4_ret = mmp_info_bar_hide();
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: mmp_ap_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
 static INT32 _audio_player_info_hdlr_cmd_do(VOID*                      pv_info_hdlr_inst,
                                             MMP_FP_INFO_HDLR_CMD_ID_T  e_cmd,
                                             VOID*                      pv_cmd_param)
{
    INT32           i4_ret = MMPR_OK;
    MMP_KEY_INFO*   pt_key_info = (MMP_KEY_INFO*)pv_cmd_param;

    /*Player Activate, not deal with ctrl panel case*/
    if(MMP_AP_FLAG_ACTIVATE & t_g_audio_view.ui4_flag)
    {
        return MMPR_OK;
    }

    switch (e_cmd)
    {
        case MMP_FP_INFO_HDLR_CMD_ID_SHOW:
        {
            DBG_LOG_PRINT(("_audio_player_info_hdlr_cmd_do MMP_FP_INFO_HDLR_CMD_ID_SHOW \n"));
            i4_ret = _audio_player_info_handle_show(pv_info_hdlr_inst,
                                                    e_cmd,
                                                    pv_cmd_param);
            MMPR_LOG_ON_FAIL(i4_ret);

        }
        break;

        case MMP_FP_INFO_HDLR_CMD_ID_HIDE:
        {
            DBG_LOG_PRINT(("_audio_player_info_hdlr_cmd_do MMP_FP_INFO_HDLR_CMD_ID_HIDE \n"));
            i4_ret = _audio_player_info_handle_hide(pv_info_hdlr_inst,
                                                    e_cmd,
                                                    pv_cmd_param);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        case MMP_FP_INFO_HDLR_CMD_ID_UPDATE_FOCUS_ITEM:
        {
            DBG_LOG_PRINT(("[MMP] _audio_player_info_hdlr_cmd_do MMP_FP_INFO_HDLR_CMD_ID_UPDATE_FOCUS_ITEM \n"));
            i4_ret = _audio_player_info_handle_update_focus_item(pv_info_hdlr_inst,
                                                                 e_cmd,
                                                                 pv_cmd_param);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        break;

        case MMP_FP_INFO_HDLR_CMD_ID_UPDATE_PLAY_ITEM:
        {
            DBG_LOG_PRINT(("_audio_player_info_hdlr_cmd_do MMP_FP_INFO_HDLR_CMD_ID_UPDATE_PLAY_ITEM \n"));
            i4_ret = _audio_player_info_handle_update_play_item(pv_info_hdlr_inst,
                                                                e_cmd,
                                                                pv_cmd_param);
            MMPR_LOG_ON_FAIL(i4_ret);
            if(MMPR_OK!=i4_ret)
            {
                i4_ret = MMPR_OK;
            }
        }
        break;

        case MMP_FP_INFO_HDLR_CMD_ID_RESET:
        {
#if 0
            if(t_g_audio_view.pv_focus_info_inst &&
               (VOID*)t_g_audio_view.pv_focus_info_inst == pv_info_hdlr_inst)
            {
                i4_ret = mmp_com_ui_focus_info_frm_inactive(t_g_audio_view.pv_focus_info_inst,
                                                            TRUE);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
#endif
        }
        break;

        case MMP_FP_INFO_HDLR_CMD_ID_HANDLE_KEY:
        {
            if(t_g_audio_view.pv_ctrl_panel_inst)
            {
                t_g_audio_view.b_ctrl_panel_show = TRUE;

                i4_ret = _audio_player_main_frm_proc_fct(NULL_HANDLE,
                                                         pt_key_info->ui4_keystatus,
                                                         (VOID*)pt_key_info->ui4_keycode,
                                                         NULL);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
        }
        break;

        default:
        {

        }
        break;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_audio_player_register
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_mmp_audio_player_register(VOID)
{
    INT32                   i4_ret = 0;
    MMP_FILE_PLAYER_INTF_T  t_intf;

    c_memset(&t_intf, 0, sizeof(MMP_FILE_PLAYER_INTF_T));

    t_intf.t_show_intf.pf_open          = _audio_player_open;
    t_intf.t_show_intf.pf_close         = _audio_player_close;
    t_intf.t_show_intf.pf_next_preload  = _audio_player_next_preload;
    t_intf.t_show_intf.pf_next_attr_set = _audio_player_next_attr_set;
    t_intf.t_show_intf.pf_attr_set      = _audio_player_attr_set;
    t_intf.t_show_intf.pf_cmd_do        = mmp_ap_cmd_do;

    t_intf.t_media_intf.pf_init         =  _audio_player_init;
    t_intf.t_media_intf.pf_deinit       =  _audio_player_deinit;
    t_intf.t_media_intf.pf_handle_msg   =  _audio_player_handle_msg;
    t_intf.t_media_intf.pf_is_type_of   =  _audio_player_is_type_of;

    t_intf.t_info_intf.pf_open              = _audio_player_info_open;
    t_intf.t_info_intf.pf_close             = _audio_player_info_close;
    t_intf.t_info_intf.pf_get               = _audio_player_info_get;
    t_intf.t_info_intf.pf_set               = _audio_player_info_set;
    t_intf.t_info_intf.pf_cmd_do            = _audio_player_info_cmd_do;
    t_intf.t_info_intf.pf_cmd_res_init      = _audio_player_info_cmd_res_init;
    t_intf.t_info_intf.pf_cmd_res_reset     = _audio_player_info_cmd_res_reset;
    t_intf.t_info_intf.pf_cmd_res_deinit    = _audio_player_info_cmd_res_deinit;

    /*file info handler interface*/
    t_intf.t_info_hdlr_intf.pf_init         = _audio_player_info_hdlr_init;
    t_intf.t_info_hdlr_intf.pf_deinit       = _audio_player_info_hdlr_deinit;
    t_intf.t_info_hdlr_intf.pf_cmd_do       = _audio_player_info_hdlr_cmd_do;


    MMP_MC_FILE_PLAYER_PROPERTY_T t_prop;
    t_prop.e_type       = MMP_MEDIA_TYPE_AUDIO;
    t_prop.e_excl_type  = MMP_MEDIA_TYPE_VIDEO;

    i4_ret = mmp_mc_reg_file_player(&t_intf, &t_prop);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: audio_player_get_duration_and_position
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 audio_player_get_duration_and_position(UINT64 *pui8_duration,
                                       UINT64 *pui8_position)
{
    *pui8_duration = t_g_audio_view.ui8_duration;

    *pui8_position = t_g_audio_view.ui8_position;

#ifdef DEBUG
	DBG_LOG_PRINT(("\n%s,%d,ui8_duration=%lu,ui8_position=%lu\n",
		           __FUNCTION__, __LINE__,
		           t_g_audio_view.ui8_duration,
		           t_g_audio_view.ui8_position));
#endif

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: audio_player_seek
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 audio_player_seek(UINT64 ui8_seek_pos)
{
	INT32			 i4_ret=0;

	/*Seek View part*/
	if(t_g_audio_view.b_crt_play_invalid_file)
	{
		return MMPR_OK;
	}

	if(t_g_audio_view.e_player_status!=MMP_VE_PLAY_STAT_PLAY &&
	   t_g_audio_view.e_player_status!=MMP_VE_PLAY_STAT_PAUSE )
	{
		DBG_LOG_PRINT(("Play status not support seek\n"));
		return MMPR_OK;
	}

	/*Seek not ready, can't seek again*/
	if(t_g_audio_view.ui8_duration==t_g_audio_view.ui8_position &&
	   MMP_VE_PLAY_STAT_PLAY==t_g_audio_view.e_player_status)
	{
		DBG_LOG_PRINT(("End of file, can't seek\n"));
		return MMPR_OK;
	}



	/*Not support Seek,show message*/
	if(!video_engine_seek_enable(t_g_audio_view.pv_engine_inst))
	{
		i4_ret=_audio_player_show_msg(MLM_MMP_TEXT(t_g_audio_view.ui2_lang, MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
		MMPR_LOG_ON_FAIL(i4_ret);
		return MMPR_OK;
	}

	/* stop h_timer_timeout */
	c_timer_stop(t_g_audio_view.h_timer_timeout);

	/*When seek:if it is play -> Pause it*/
	if(MMP_VE_PLAY_STAT_PLAY==t_g_audio_view.e_player_status)
	{
		/*Turn on flag*/
		t_g_audio_view.ui4_flag |=MMP_AP_FLAG_PLAY_BEFORE_SEEK;

		i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_BACK);
		DBG_LOG_PRINT(("================before status is play: mmp_mc_list_pause================\n"));
		if(i4_ret!=MMPR_OK&&
		  i4_ret!=MMPR_IS_PAUSED)
		{
			MMPR_LOG_ON_FAIL(i4_ret);
		}
	}

	t_g_audio_view.ui8_position = ui8_seek_pos;

	i4_ret=_audio_player_view_update_pos(t_g_audio_view.ui8_position,TRUE);
	MMPR_LOG_ON_FAIL(i4_ret);

	/*Seek end part*/
	/*For seek at same position:CR69447*/
	if(t_g_audio_view.ui8_position!=0 &&
	   t_g_audio_view.ui8_last_seek_position==t_g_audio_view.ui8_position)
	{
		DBG_LOG_PRINT(("Seek position is same with last seek\n"));
			 /*Keep before status when seek ready*/
		if(MMP_VE_PLAY_STAT_PAUSE==t_g_audio_view.e_player_status)
		{
			i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_BACK,MMP_PLAY_IDX_CURRENT);
			DBG_LOG_PRINT(("==============seek ready mmp_mc_list_play already=============\n"));
			if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PLAYED)
			{
				MMPR_LOG_ON_FAIL(i4_ret);
			}
		}
		return MMPR_OK;
	}

	t_g_audio_view.ui8_last_seek_position = t_g_audio_view.ui8_position;

	DBG_LOG_PRINT(("MW seek pos :%lld\n",t_g_audio_view.ui8_position));

	i4_ret=video_engine_seek(t_g_audio_view.pv_engine_inst,
							  t_g_audio_view.ui8_position);
	DBG_LOG_PRINT(("==============video_engine_seek already=============\n"));
	MMPR_LOG_ON_FAIL(i4_ret);

	/*Seek fail, replay it*/
	if(i4_ret<MMPR_OK)
	{
		if(MMP_VE_PLAY_STAT_PAUSE==t_g_audio_view.e_player_status)
		{
			DBG_LOG_PRINT(("mmp_mc_list_play %s:%s:%d\n", __FILE__, __FUNCTION__, __LINE__));
			i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_BACK,MMP_PLAY_IDX_CURRENT);
			if(i4_ret != MMPR_OK && i4_ret != MMPR_IS_PLAYED)
			{
				MMPR_LOG_ON_FAIL(i4_ret);
			}
		}
	}
	return MMPR_OK;
}

extern INT32 mmp_com_ui_ap_info_update_text(VOID*       pv_ap_inst,
                                                  UINT16      ui2_lang);
INT32 a_mmp_update_ap_info_frm_by_lang_change(VOID)
{
    ISO_639_LANG_T           s639_lang = {0};
    INT32                    i4_ret = 0;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<MMP AP>Can't init lanugage \r\n"));
        t_g_audio_view.ui2_lang =0;
    }
    else
    {
        t_g_audio_view.ui2_lang = mlm_mmp_s639_to_langidx(s639_lang);
    }

    return mmp_com_ui_ap_info_update_text(t_g_audio_view.pv_ctrl_panel_inst,
                                      t_g_audio_view.ui2_lang);
}

INT32 a_mmp_audio_show_playback_info(BOOL b_show)
{
    return mmp_com_ui_ap_info_show_process_bar(t_g_audio_view.pv_ctrl_panel_inst,b_show,TRUE);
}
