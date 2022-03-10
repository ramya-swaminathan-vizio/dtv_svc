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
 * $RCSfile: video_player.c,v $
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
#include "u_drv_cust.h"
#include "video_player.h"
#include "a_video_player.h"
#include "u_irrc_btn_def.h"
#include "res/mmp/img/mmp_img.h"
#include "mmp/file_browser/file_browser.h"
#include "video_player_cli.h"
#include MMP_COM_UI_HEADER_FILE
#include "mmp/app/mmp_main.h"
#include "mmp/video_engine/video_engine_cli.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#include "c_dbg.h"

#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_screen_mode.h"
#include "app_util/option_list/a_optl.h"
#include "res/mmp/gen/mmp_lm_focus_layout.h"

#ifdef APP_CAPTURE_LOGO_SUPPORT
#include "app_util/capture_logo/a_capture_logo.h"
#endif

#ifdef MMP_GUI_AUTHORING
#include "res/mmp/gen/mmp_vp_layout.h"
#endif

#include "mmp/common_ui2/mmp_common_ui_detail_page.h"
#include "mmp/common_ui2/mmp_common_ui_toolbar.h"
#include "mmp/common_ui2/mmp_com_ui_info_handler.h"
#include "mmp/common_ui2/mmp_divx_dlg.h"
#include "mmp/common_ui2/mmp_info_bar.h"
#include "mmp/video_engine/_mmp_ve_type.h"
#include "mmp/listmode2/listmode.h"

#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "menu2/a_menu.h"

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
#include "mmp/dmr/mmp_dmr.h"
#endif

#include "nav/scrn_blank/a_nav_scrn_blank.h"
#include "nav/link_mode/link_mode.h"
#include "mmp/a_mmp.h"
#include "res/mmp/listmode/mmp_listmode_rc.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

#include "res/menu2/menu_custom.h"
/*-----------------------------------------------------------------------------
 * macros, typedefs, enums
 *---------------------------------------------------------------------------*/
extern UINT32             ui4_g_play_idx;
static INT32 _mmp_vp_close(VOID);

#define MMP_VP_SYNC_REPAINT                (FALSE)
#define MAX_PROGRAM_NUM                     (16)

#ifndef MMP_VP_RPT_KEY_PERIOD
#define MMP_VP_RPT_KEY_PERIOD              ((UINT32) 400) /* To fix DTV00089784 */
#endif

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MMP_VP_AV_NTFY_EMPTY               ((UINT16)0x0000)
#define MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT   ((UINT16)0x0001)
#define MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT   ((UINT16)0x0002)
#define MMP_VP_AV_NTFY_HD_NOT_SUPPORT      ((UINT16)0x0004)
#define MMP_VP_AV_NTFY_DRM_NOT_SUPPORT     ((UINT16)0x0008)
#define MMP_VP_AV_NTFY_HAS_NO_CONTENT      ((UINT16)0x0010)
#define MMP_VP_AV_NTFY_FRM_NOT_SUPPORT     ((UINT16)0x0020)
#define MMP_VP_AV_NTFY_RES_NOT_SUPPORT     ((UINT16)0x0040)
#define MMP_VP_AV_NTFY_FILE_NOT_SUPPORT    ((UINT16)0x0080)
#define MMP_VP_AV_NTFY_FILE_AUDIO_ONLY     ((UINT16)0x0100)
#define MMP_VP_AV_NTFY_FILE_VIDEO_ONLY     ((UINT16)0x0200)
#define MMP_VP_AV_NTFY_OTHER               ((UINT16)0x8000)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MMP_VP_AV_STAT_AUDIO_NONE          (MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT | \
                                            MMP_VP_AV_NTFY_HD_NOT_SUPPORT    | \
                                            MMP_VP_AV_NTFY_DRM_NOT_SUPPORT   | \
                                            MMP_VP_AV_NTFY_RES_NOT_SUPPORT)

#define MMP_VP_AV_STAT_VIDEO_NONE          (MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT | \
                                            MMP_VP_AV_NTFY_HD_NOT_SUPPORT    | \
                                            MMP_VP_AV_NTFY_DRM_NOT_SUPPORT   | \
                                            MMP_VP_AV_NTFY_RES_NOT_SUPPORT)

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MMP_VP_OPTL_SCR_MODE_NUM   (9)
#define MMP_VP_SEEK_STEP 10  //10s

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

#define MLM_MMP_VP_TEXT(key) MLM_MMP_TEXT(t_g_video_view.ui2_lang, (key))
#define CHECK_RET(RET, VALUE)\
{\
    if( RET != VALUE)\
    {\
            DBG_LOG_PRINT(("\033[33m%s %d [Check Ret Fail! Ret=%d]\033[m\n", __FUNCTION__, __LINE__, RET));  \
    }\
}

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

typedef enum
{
    _MMP_VP_LAST_OPEN_ELM_RET_NORMAL = 0,
    _MMP_VP_LAST_OPEN_ELM_RET_FAILED,
    _MMP_VP_LAST_OPEN_ELM_RET_NODATA,
    _MMP_VP_LAST_OPEN_ELM_RET_CORRUPT

}   _MMP_VP_LAST_OPEN_ELM_RET_T;

typedef enum
{
    _MMP_VP_SEEK_STAT_UNUSED = 0,
    _MMP_VP_SEEK_STAT_SETTING,
    _MMP_VP_SEEK_STAT_SEEKING

}   _MMP_VP_SEEK_STAT_T;

typedef enum
{
    _MMP_VP_DLG_TIME_ERROR_DONE,
    _MMP_VP_DLG_TIME_ERROR_YESNO

}   _MMP_VP_DLG_TIME_ERROR_T;

typedef enum
{
    _MMP_VP_PROG_BAR_TYPE_TIME,
    _MMP_VP_PROG_BAR_TYPE_FILE

}   _MMP_VP_PROG_BAR_TYPE_T;

typedef enum
{
    _MMP_VP_OPTL_LST_STAT_HIDE = 0,
    _MMP_VP_OPTL_LST_STAT_SHOW

}   _MMP_VP_OPTL_LST_STAT_T;

typedef enum
{
    MMP_VP_SCR_FMT_4_3_NORMAL = 0,
    MMP_VP_SCR_FMT_4_3_LETTERBOX,
    MMP_VP_SCR_FMT_4_3_PAN_SCAN,
    MMP_VP_SCR_FMT_4_3_USER_DEFINED,
    MMP_VP_SCR_FMT_4_3_NON_LINEAR_ZOOM,
    MMP_VP_SCR_FMT_4_3_DOT_BY_DOT,
    MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_0,
    MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_1,
    MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_2,
    MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_3,
    MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_4,
    MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_5,
    MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_6,
    MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_7,
    MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_0,
    MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_1,
    MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_2,
    MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_3,
    MMP_VP_SCR_FMT_16_9_NORMAL,
    MMP_VP_SCR_FMT_16_9_LETTERBOX,
    MMP_VP_SCR_FMT_16_9_PAN_SCAN,
    MMP_VP_SCR_FMT_16_9_USER_DEFINED,
    MMP_VP_SCR_FMT_16_9_NON_LINEAR_ZOOM,
    MMP_VP_SCR_FMT_16_9_DOT_BY_DOT,
    MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_0,
    MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_1,
    MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_2,
    MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_3,
    MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_4,
    MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_5,
    MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_6,
    MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_7,
    MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_0,
    MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_1,
    MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_2,
    MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_3,
    MMP_VP_SCR_FMT_NO_ADJUST,            /* not adjustable */
    MMP_VP_SCR_FMT_LAST_VALID_ENTRY
}   MMP_VP_SCR_FMT_T;

typedef struct
{
    UINT32                       ui4_key_code;
    UINT32                       ui4_sys_tick;
} MMP_VP_RPT_KEY_TICK_T;

typedef struct {
   BOOL b_is_seek;
   BOOL b_is_mute_before_seek;
} MMP_VP_SEEK_STATUS;


static MMP_COM_UI_DP_VIEW_PTR_T pt_vdp_inst;
static VOID*                    pt_vtb_inst;

static MMP_COM_FP_INFO_UI_TYPE_T e_ui_type;

/******************************************************************************
*******************************************************************************
                                Video  Player Viewer
*******************************************************************************
******************************************************************************/
/*
   View structure.
*/
typedef struct
{
    MMP_VP_IFNO_INST_T           pv_video_info_inst;
    HANDLE_T                     h_canvas;
    HANDLE_T                     h_frm_main;               /* Main frame */
    MMP_VP_STAT_T                e_vp_stat;

    MMP_VP_INFO_HDLR_T           t_info_hdlr;
    MMP_VP_TOOLBAR_T             t_toolbar;
    HANDLE_T                     h_txt_loading;
    HANDLE_T                     h_opt_list;
    _MMP_VP_OPTL_LST_STAT_T      e_opt_stat;

#ifdef APP_CAST_TV_MMP
    HANDLE_T                     h_iom;
    BOOL                         b_is_icl_exit_video;
    UINT16                       ui2_icl_nfy_id;
    BOOL                         b_is_res_not_support;
    BOOL                         b_is_next_preload_end;
#endif

    HANDLE_T                     h_timer_hide_msg;
    HANDLE_T                     h_timer_timeout;
    HANDLE_T                     h_timer_viewer;
    HANDLE_T                     h_timer_reset_icon;
    HANDLE_T                     h_timer_loading;
    HANDLE_T                     h_timer_cec_sac;

    MMP_REPEAT_MODE_T            e_repeat_mode;
    MMP_VP_DETAIL_PAGE_STATUS_T  e_detail_page;
    MMP_VP_PIC_MODE_STATUS_T     e_pic_mode;

    MMP_VE_PLAY_STAT_T           e_player_status;
    UINT8                        ui1_step;
    MMP_VP_VIEWER_STATUS_T       e_viewer_status;

    mmp_fp_show_nfy_fct          pf_fp_show_nfy_fct;
    mmp_fp_info_nfy_fct          pf_info_nfy_fct;
    VOID*                        pv_mmp_tag;
    MMP_VE_PLAY_INST_PTR_T       pt_engine_inst;
    VOID*                        pv_info_tag;
    UINT32                       ui4_mmc_ver;

    _MMP_VP_PROG_BAR_TYPE_T      e_prog_bar_type;
    UINT64                       ui8_duration;
    UINT64                       ui8_position;             /* To fix DTV00209704 */

    MMP_VE_DRM_TYPE_T            t_drm_type;

    MMP_VE_VID_INFO_T            t_vid_info;
    MMP_VE_AUD_INFO_T            t_aud_info;
    MMP_VE_SUB_INFO_T            t_sub_info;
    MMP_VE_PROGRAM_INFO_T        t_program_info;

    /* Audio and Video status */
    UINT16                       ui2_av_ntfy;

    /*Temporary keep language.MMP should provide language*/
    UINT16                       ui2_lang;

    _MMP_VP_LAST_OPEN_ELM_RET_T  e_last_open_elm_ret;
    BOOL                         b_crt_play_invalid_file;

    SCC_VID_SCREEN_MODE_T        t_optl_scr_mode[MMP_VP_OPTL_SCR_MODE_NUM];

    UINT32                       ui4_cur_file_idx;
    UINT32                       ui4_total_file_num;

    VOID*                        pv_cap_logo;

    //seek status
    MMP_VP_SEEK_STATUS           t_seek_status;

}   VIDEO_PLAYER_VIEW_T;
#if NEVER
extern INT32 a_banner_show_hdr_info(BOOL b_show);
#else
INT32 a_mmp_show_hdr_info(BOOL b_show);
#endif
static INT32 _mmp_vp_main_frm_proc_fct(
                    HANDLE_T            h_frm_main,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    );

static INT32 _mmp_vp_view_update_file_repeat(
                    BOOL                            b_repaint
                    );

static INT32 _mmp_vp_optl_set_repeat(
                    VOID*                           pv_param
                    );

static INT32 _mmp_vp_view_toggle_detail_page(
                    VOID*                           pv_param
                    );

static INT32 _mmp_vp_view_toggle_viewer(
                    BOOL                            b_repaint
                    );

static VOID  _mmp_vp_timer_nfy_fct(
                    HANDLE_T                        h_timer,
                    VOID*                           pv_tag
                    );

static VOID  _mmp_vp_engine_nfy_fct(
                    MMP_VE_NFY_CODE_T               e_code,
                    VOID*                           pv_param
                    );

static VOID  _mmp_vp_update_vol_info(
                    BOOL                            b_repaint,
                    VOID*                           pv_msg_param
                    );

static INT32 _mmp_vp_view_update_codec(
                    UINT16                          ui2_codec,
                    BOOL                            b_repaint
                    );

static INT32 _mmp_vp_ib_show(
                    MMP_IB_MSG_CLASS_T          e_msg_class,
                    UTF16_T*                    ws_msg
                    );

static INT32 _mmp_vp_not_support(VOID);
static INT32 _mmp_vp_pause(VOID);
static INT32 _mmp_vp_play(VOID);

static INT32 _mmp_vp_deinit(VOID);

static INT32 _mmp_vp_view_activate(
                    VIDEO_PLAYER_VIEW_T*            pt_this
                    );

static INT32 _mmp_vp_update_status(
                    BOOL                            b_repaint
                    );

static VOID  _mmp_vp_update_pos(VOID*                           pv_tag1,
                                VOID*                           pv_tag2,
                                VOID*                           pv_tag3,
                                VOID*                           pv_tag4);

static VOID _mmp_vp_hide_viewer(
                    VOID*                           pv_tag1,
                    VOID*                           pv_tag2,
                    VOID*                           pv_tag3,
                    VOID*                           pv_tag4
                    );

static VOID _mmp_vp_reset_icon(
                    VOID*                           pv_tag1,
                    VOID*                           pv_tag2,
                    VOID*                           pv_tag3,
                    VOID*                           pv_tag4
                    );

#ifndef APP_CAST_TV_MMP
static INT32 _mmp_vp_view_swap_filename(
                    BOOL                            b_repaint
                    );
#endif

static INT32 _mmp_vp_view_ctnt_repeat(
                    BOOL                            b_repaint
                    );

static INT32 _mmp_vp_view_mts(
                    BOOL                            b_repaint
                    );

static INT32 _mmp_vp_view_zoom(
                    BOOL                            b_repaint
                    );

static INT32 _mmp_vp_optl_show(VOID);

static VOID  _mmp_vp_optl_hide(
                    VOID*                           pv_param1,
                    VOID*                           pv_param2,
                    VOID*                           pv_param3,
                    VOID*                           pv_param4
                    );

static INT32 _mmp_vp_view_reset(
                    BOOL b_clear_all,
                    BOOL b_repaint);

static INT32 _mmp_vp_view_update_pos(UINT64     ui8_day_sec,
                                     BOOL       b_repaint);
static BOOL  _video_player_is_playing(VOID);

//#ifdef APP_MMP_NO_VIDEO_AUDIO_SUPPORT
static INT32 _mmp_vp_stop(VOID);
//#endif
static VOID _mmp_vp_update_play_status();

static INT32 _video_player_get_audio_fmt_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    ASH_AUDIO_INFO_T*            pt_audio_info       /* out */
                    );
static BOOL _mmp_videoplay_get_disp_handle(MI_HANDLE *phDisp,UINT16 ui2_idx);

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static VIDEO_PLAYER_VIEW_T  t_g_video_view = {0};

/* The following variables are used for setting playing position             */
static _MMP_VP_SEEK_STAT_T  e_g_seek_stat = _MMP_VP_SEEK_STAT_UNUSED;

static const UINT32 ui4_rpt_keys[] = MMP_VP_RC_GET_FILTED_BTN();
static const UINT16 ui2_rpt_keys_num = sizeof(ui4_rpt_keys) / sizeof(UINT32);
static MMP_VP_RPT_KEY_TICK_T at_rpt_key_tick[MMP_VP_RC_FILTED_BTN_NUM];

static UTF16_T w2s_g_file[MMP_VP_RC_FILE_MAX_LEN] = {0}; /* current file's name */
static UTF16_T w2s_g_next[MMP_VP_RC_FILE_MAX_LEN] = {0}; /* next file's name    */

/*message for screen mode*/
static UTF16_T* apw2s_g_scr_msg[MMP_VP_SCR_FMT_LAST_VALID_ENTRY] = {0};

static GL_COLOR_T t_g_mmp_transparent = {0,{0},{0},{0}};
static GL_COLOR_T t_g_mmp_gray_v      = {0xff, {0x2c}, {0x2c}, {0x2c}};
static GL_COLOR_T t_g_mmp_black       = {0xff, {0},{0},{0}};
/*----------------------------------------------------------------------------
 * Name: _convert_time_day_sec_to_hh_mm_ss
 *
 * Description: Convert ui4_day_sec => ui1_hour/ui1_minute/ui1_second
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _convert_time_day_sec_to_hh_mm_ss(UINT32  ui4_day_sec,   /* in */
                                              UINT8*  pui1_hour,     /* out */
                                              UINT8*  pui1_minute,   /* out */
                                              UINT8*  pui1_sec)      /* out */
{
    UINT32  ui4_left_sec;
    UINT8   ui1_hour;
    UINT8   ui1_minute;
    UINT8   ui1_sec;

    ui4_left_sec = ui4_day_sec;
    ui1_hour = (UINT8) (ui4_left_sec / 3600);
    ui4_left_sec -= ui1_hour*3600;
    ui1_minute = (UINT8) (ui4_left_sec / 60);
    ui4_left_sec -= ui1_minute*60;
    ui1_sec = (UINT8) ui4_left_sec;

    *pui1_hour   = ui1_hour;
    *pui1_minute = ui1_minute;
    *pui1_sec    = ui1_sec;
}

static INT32 _mmp_vp_tb_icon_play(
                    MMP_VE_PLAY_STAT_T              e_play_stat,
                    MMP_TB_REPAINT_TYPE_T           e_repaint_type
                    )
{
    switch (e_play_stat)
    {
        case MMP_VE_PLAY_STAT_PLAY:
        {
            mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_PLAY_STATUS,
                    (VOID*)(UINT32)MMP_VP_TB_STATUS_PLAY,
                    e_repaint_type
                    );
        }
        break;

        case MMP_VE_PLAY_STAT_PAUSE:
        {
            mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_PLAY_STATUS,
                    (VOID*)(UINT32)MMP_VP_TB_STATUS_PAUSE,
                    e_repaint_type
                    );
        }
        break;

        case MMP_VE_PLAY_STAT_STOP:
        {
            mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_PLAY_STATUS,
                    (VOID*)(UINT32)MMP_VP_TB_STATUS_STOP,
                    e_repaint_type
                    );
        }
        break;

        case MMP_VE_PLAY_STAT_FAST_FWD:
        {
            mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_FF,
                    (VOID*)(UINT32)t_g_video_view.ui1_step,
                    e_repaint_type
                    );
        }
        break;

        case MMP_VE_PLAY_STAT_FAST_RWD:
        {
            mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_FR,
                    (VOID*)(UINT32)t_g_video_view.ui1_step,
                    e_repaint_type
                    );
        }
        break;

        case MMP_VE_PLAY_STAT_SLOW_FWD:
        {
            mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_SLOW_PALY,
                    (VOID*)(UINT32)t_g_video_view.ui1_step,
                    e_repaint_type
                    );
        }
        break;

        default:
        {
            mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_PLAY_STATUS,
                    (VOID*)(UINT32)MMP_VP_TB_STATUS_DEFAULT,
                    e_repaint_type
                    );
        }
        break;
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_tb_icon_time(
                    UINT64                          ui8_day_sec,
                    MMP_TB_REPAINT_TYPE_T           e_repaint_type
                    )
{
    MMP_TB_POS_INFO_T t_time_type;
    INT32           i4_ret;

    c_memset(&t_time_type, 0, sizeof(MMP_TB_POS_INFO_T));

    if (_MMP_VP_PROG_BAR_TYPE_TIME == t_g_video_view.e_prog_bar_type)
    {
        t_time_type.e_pos_type = MMP_TB_POS_TYPE_TIME;
        t_time_type.u.ui4_time_dur = (UINT32)t_g_video_view.ui8_duration;
        t_time_type.v.ui4_time_pos = (UINT32)ui8_day_sec;
    }
    else
    {
        t_time_type.e_pos_type = MMP_TB_POS_TYPE_BYTE;
        t_time_type.u.ui8_byte_dur = (UINT64)t_g_video_view.ui8_duration;
        t_time_type.v.ui8_byte_pos = (UINT64)ui8_day_sec;
    }

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_TIME,
                    (VOID*)&t_time_type,
                    e_repaint_type
                    );
    if(MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_TIME) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_icon_zoom(
                    MMP_VE_ZOOM_TYPE_T              t_zoom_crnt,
                    MMP_TB_REPAINT_TYPE_T           t_repaint_type
                    )
{
    UINT32          ui4_zoom_val;
    INT32           i4_ret;

    ui4_zoom_val = (UINT32)1 << (t_zoom_crnt - MMP_VE_ZOOM_TYPE_1X);

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_ZOOM,
                    (VOID*)ui4_zoom_val,
                    t_repaint_type
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_ZOOM) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_icon_audio(
                    MMP_VE_AUD_INFO_T const*        pt_aud_info,
                    MMP_TB_REPAINT_TYPE_T           t_repaint_type
                    )
{
    MMP_TB_MTS_TYPE_T t_mts_type;
    INT32           i4_ret;

    t_mts_type.ui2_mts_total = pt_aud_info->ui2_aud_num;
    t_mts_type.ui2_mts_index = pt_aud_info->ui2_sel_idx + 1;

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_MTS,
                    (VOID*)&t_mts_type,
                    t_repaint_type
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_MTS) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_icon_sbtl(
                    MMP_VE_SUB_INFO_T const*        pt_sub_info,
                    MMP_TB_REPAINT_TYPE_T           t_repaint_type
                    )
{
    MMP_TB_SUB_TYPE_T t_sub_type = {0};
    INT32           i4_ret;

    t_sub_type.ui2_sub_total = pt_sub_info->ui2_sub_num - 1;
    t_sub_type.ui2_sub_index = pt_sub_info->ui2_sel_idx;

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_SUBTITLE,
                    (VOID*)&t_sub_type,
                    t_repaint_type
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_SUBTITLE) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_tb_icon_file_idx
 *
 * Description: update the file index on the status bar.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_tb_icon_file_idx(BOOL b_repaint)
{
    INT32            i4_ret;
    UTF16_T          w2s_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    CHAR             sz_info [MMP_VP_INFO_MAX_STR_LEN+1] = {0};

    /*File num*/
    c_memset(w2s_info, 0, sizeof(w2s_info));
    c_memset(sz_info, 0, sizeof(sz_info));

    i4_ret = mmp_util_get_full_item_count(
                    MMP_GROUND_MODE_FORE,
                    &t_g_video_view.ui4_total_file_num
                    );
    MMPR_LOG_ON_FAIL(i4_ret);

    _mmp_vp_update_play_status();
    /*Begin is zero*/
    t_g_video_view.ui4_cur_file_idx++;

    if (t_g_video_view.ui4_cur_file_idx > t_g_video_view.ui4_total_file_num)
    {
        t_g_video_view.ui4_cur_file_idx = t_g_video_view.ui4_total_file_num;
    }

    c_sprintf(sz_info,
              "%d/%d",
              t_g_video_view.ui4_cur_file_idx,
              t_g_video_view.ui4_total_file_num);

    c_uc_ps_to_w2s(sz_info, w2s_info, MMP_VP_INFO_MAX_STR_LEN);

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_FILEIDX,
                    (VOID*)w2s_info,
                    (b_repaint? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT)
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT (("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_FILEIDX) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_icon_file_name(
                    UTF16_T const*                  ws_file_name,
                    MMP_TB_REPAINT_TYPE_T           e_repaint_type
                    )
{
    INT32           i4_ret;

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_FILENAME,
                    (VOID*)ws_file_name,
                    e_repaint_type
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT (("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_FILENAME) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_icon_repeat(
                    MMP_REPEAT_MODE_T               e_repeat_mode,
                    MMP_TB_REPAINT_TYPE_T           e_repaint_type
                    )
{
    UINT32          ui4_repeat_type;
    INT32           i4_ret;

    switch (e_repeat_mode)
    {
        case MMP_REPEAT_MODE_ALL:
            ui4_repeat_type = MMP_VP_TB_STATUS_REPEAT_ALL;
            break;

        case MMP_REPEAT_MODE_ONE:
            ui4_repeat_type = MMP_VP_TB_STATUS_REPEAT_ONE;
            break;

        case MMP_REPEAT_MODE_NONE:
        default:
            ui4_repeat_type = MMP_VP_TB_STATUS_REPEAT_NONE;
            break;
    }

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_REPEAT,
                    (VOID*)ui4_repeat_type,
                    e_repaint_type
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT (("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_REPEAT) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_icon_repeat_ab(
                    MMP_VE_CTNT_RPT_TYPE_T          e_repeat_type,
                    MMP_TB_REPAINT_TYPE_T           e_repaint_type
                    )
{
    UINT32          ui4_param = (UINT32)0;
    INT32           i4_ret;

    if (MMP_VE_CTNT_RPT_TYPE_PT_A == e_repeat_type)
    {
        ui4_param = (UINT32)MMP_VP_TB_STATUS_REPEAT_AB_A;
    }
    else if (MMP_VE_CTNT_RPT_TYPE_PT_B == e_repeat_type)
    {
        ui4_param = (UINT32)MMP_VP_TB_STATUS_REPEAT_AB_AB;
    }
    else
    {
        ui4_param = (UINT32)MMP_VP_TB_STATUS_REPEAT_AB_NONE;
    }

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_REPEAT_AB,
                    (VOID*)ui4_param,
                    e_repaint_type
                    );
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _mmp_vp_tb_icon_volumn(
                    INT16                           i2_volumn_val,
                    MMP_TB_REPAINT_TYPE_T           e_repaint_type
                    )
{
    INT32           i4_ret;

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_VOL_PG,
                    (VOID*)(UINT32)i2_volumn_val,
                    e_repaint_type
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT (("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_VOL_PG) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_icon_mute(
                    BOOL                            b_mute,
                    MMP_TB_REPAINT_TYPE_T           e_repaint_type
                    )
{
    INT32           i4_ret;

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_VOL_MUTE,
                    (VOID*)(UINT32)(b_mute ? MMP_VP_TB_STATUS_VOL_MUTE : MMP_VP_TB_STATUS_VOL_NORMAL),
                    e_repaint_type
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT (("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_VOL_MUTE) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_init (VOID)
{
    INT32 i4_ret;

    i4_ret = mmp_common_ui_toolbar_init(
                    MMP_TB_VIDEO_PLAYER,
                    t_g_video_view.h_frm_main,
                    &pt_vtb_inst
                    );
    if (MMPR_OK != i4_ret)
    {
        pt_vtb_inst = NULL;
        return i4_ret;
    }

    return i4_ret;
}

static INT32 _mmp_vp_tb_deinit(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_common_ui_toolbar_deinit(pt_vtb_inst);
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_common_ui_toolbar_deinit(MMP_TB_VIDEO_PLAYER) returns %d.\n", i4_ret));
    }
    pt_vtb_inst = NULL;

    return i4_ret;
}

static INT32 _mmp_vp_tb_show(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_common_ui_toolbar_view_active(
                    pt_vtb_inst,
                    MMP_TB_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_common_ui_toolbar_view_active(MMP_TB_VIDEO_PLAYER) returns %d.\n", i4_ret));
        return i4_ret;
    }

    i4_ret = c_timer_start(t_g_video_view.h_timer_viewer,
                           MMP_VP_TIMER_VIERER_HIDE,
                           X_TIMER_FLAG_ONCE,
                           _mmp_vp_timer_nfy_fct, NULL
                           );
    if (OSR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("c_timer_start() returns %d.\n", i4_ret));
        return MMPR_FAIL;
    }

    t_g_video_view.e_viewer_status = MMP_VP_VIEWER_SHOW;

    return MMPR_OK;
}

static INT32 _mmp_vp_tb_hide(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_common_ui_toolbar_view_inactive(
                    pt_vtb_inst,
                    MMP_TB_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_common_ui_toolbar_view_inactive(MMP_TB_VIDEO_PLAYER) returns %d.\n", i4_ret));
    }

    t_g_video_view.e_viewer_status = MMP_VP_VIEWER_HIDE;

    return i4_ret;
}

static INT32 _mmp_vp_tb_reset(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_CLEAR,
                    NULL,
                    MMP_TB_SYNC_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_common_ui_toolbar_cmd_do(MMP_VP_TB_CMD_SET_CLEAR) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_dp_item_title(VOID)
{
    UTF16_T         ws_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    SIZE_T          z_buff_len = MMP_VP_INFO_MAX_STR_LEN;
    INT32           i4_ret;

    i4_ret = video_engine_get_dtl_info(
                    t_g_video_view.pt_engine_inst,
                    MMP_VE_INFO_ID_TITLE,
                    ws_info,
                    &z_buff_len
                    );
    if (MMPR_OK != i4_ret || 0 == z_buff_len)
    {
        c_uc_w2s_strncpy(ws_info, (UTF16_T*)L"-", MMP_VP_INFO_MAX_STR_LEN);
    }

    i4_ret = mmp_com_ui_dp_set_text_ex(
                    pt_vdp_inst,
                    MMP_VP_RC_DP_LBL_ID_TITLE,
                    ws_info,
                    COM_UI_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_set_text() returns %d.\n", i4_ret));
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_dp_item_director(VOID)
{
    UTF16_T         ws_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    SIZE_T          z_buff_len = MMP_VP_INFO_MAX_STR_LEN;
    INT32           i4_ret;

    i4_ret = video_engine_get_dtl_info(
                    t_g_video_view.pt_engine_inst,
                    MMP_VE_INFO_ID_DIRECTOR,
                    ws_info,
                    &z_buff_len
                    );
    if (MMPR_OK != i4_ret || 0 == z_buff_len)
    {
        c_uc_w2s_strcpy(ws_info, (UTF16_T*)L"-");
    }

    i4_ret = mmp_com_ui_dp_set_text_ex(
                    pt_vdp_inst,
                    MMP_VP_RC_DP_LBL_ID_DIRECTOR,
                    ws_info,
                    COM_UI_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_set_text() returns %d.\n", i4_ret));
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_dp_item_cpright(VOID)
{
    UTF16_T         ws_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    SIZE_T          z_buff_len = MMP_VP_INFO_MAX_STR_LEN;
    INT32           i4_ret;

    i4_ret = video_engine_get_dtl_info(
                    t_g_video_view.pt_engine_inst,
                    MMP_VE_INFO_ID_COPYRIGHT,
                    ws_info,
                    &z_buff_len
                    );
    if (MMPR_OK != i4_ret || 0 == z_buff_len)
    {
        c_uc_w2s_strcpy(ws_info, (UTF16_T*)L"-");
    }

    i4_ret = mmp_com_ui_dp_set_text_ex(
                    pt_vdp_inst,
                    MMP_VP_RC_DP_LBL_ID_COPYRIGHT,
                    ws_info,
                    COM_UI_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_set_text() returns %d.\n", i4_ret));
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_dp_item_date(VOID)
{
    MM_TM_T         t_date;
    SIZE_T          z_buff_len = sizeof(MM_TM_T);
    CHAR            cs_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    UTF16_T         ws_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    INT32           i4_ret;

    i4_ret = video_engine_get_dtl_info(
                      t_g_video_view.pt_engine_inst,
                      MMP_VE_INFO_ID_DATE,
                      &t_date,
                      &z_buff_len);
    if (MMPR_OK != i4_ret || 0 == t_date.ui2_year)
    {
        c_strncpy (cs_info, "-", MMP_VP_INFO_MAX_STR_LEN);
    }
    else
    {
        c_sprintf (cs_info, "%04u-%02u-%02u %02u:%02u:%02u",
                   t_date.ui2_year, t_date.ui1_month, t_date.ui1_day,
                   t_date.ui1_hour, t_date.ui1_min, t_date.ui1_sec);
    }

    c_uc_ps_to_w2s (cs_info, ws_info, MMP_VP_INFO_MAX_STR_LEN);

    i4_ret = mmp_com_ui_dp_set_text_ex(
                    pt_vdp_inst,
                    MMP_VP_RC_DP_LBL_ID_DATE,
                    ws_info,
                    COM_UI_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_set_text() returns %d.\n", i4_ret));
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_dp_item_genre(VOID)
{
    UTF16_T         ws_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    SIZE_T          z_buff_len = MMP_VP_INFO_MAX_STR_LEN;
    INT32           i4_ret;

    i4_ret = video_engine_get_dtl_info(
                    t_g_video_view.pt_engine_inst,
                    MMP_VE_INFO_ID_GENRE,
                    ws_info,
                    &z_buff_len
                    );
    if (MMPR_OK != i4_ret || 0 == z_buff_len)
    {
        c_uc_w2s_strcpy(ws_info, (UTF16_T*)L"-");
    }

    i4_ret = mmp_com_ui_dp_set_text_ex(
                    pt_vdp_inst,
                    MMP_VP_RC_DP_LBL_ID_GENRE,
                    ws_info,
                    COM_UI_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_set_text() returns %d.\n", i4_ret));
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_dp_item_duration(VOID)
{
    UINT64          ui8_duration = 0;
    SIZE_T          z_buff_len = sizeof(UINT64);
    UINT8           ui1_hh, ui1_mm, ui1_ss;
    CHAR            cs_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    UTF16_T         ws_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    INT32           i4_ret;

    if(_MMP_VP_PROG_BAR_TYPE_TIME == t_g_video_view.e_prog_bar_type)
    {
        i4_ret = video_engine_get_dtl_info(
                    t_g_video_view.pt_engine_inst,
                    MMP_VE_INFO_ID_DURATION,
                    &ui8_duration,
                    &z_buff_len
                    );
    }
    else
    {
        i4_ret = MMPR_NO_DATA;
    }

    if (MMPR_OK != i4_ret || (UINT64)0 == ui8_duration)
    {
        c_strncpy(cs_info, "-", MMP_VP_INFO_MAX_STR_LEN);
    }
    else
    {
        _convert_time_day_sec_to_hh_mm_ss((UINT32)ui8_duration, &ui1_hh, &ui1_mm, &ui1_ss);
        c_sprintf(cs_info, "%02u:%02u:%02u", ui1_hh, ui1_mm, ui1_ss);
    }

    c_uc_ps_to_w2s(cs_info, ws_info, MMP_VP_INFO_MAX_STR_LEN);

    i4_ret = mmp_com_ui_dp_set_text_ex(
                    pt_vdp_inst,
                    MMP_VP_RC_DP_LBL_ID_DURATION,
                    ws_info,
                    COM_UI_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_set_text() returns %d.\n", i4_ret));
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_dp_item_next(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_com_ui_dp_set_text_ex(
                    pt_vdp_inst,
                    MMP_VP_RC_DP_LBL_ID_NEXT,
                    w2s_g_next,
                    COM_UI_NON_REPAINT
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_set_text() returns %d.\n", i4_ret));
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_dp_init(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_com_ui_create_detail_page_new(
                    t_g_video_view.h_frm_main,
                    COM_UI_DTL_PG_VIDEO,
                    (VOID*)&pt_vdp_inst
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_create_detail_page_new(COM_UI_DTL_PG_VIDEO) returns %d.\n", i4_ret));
        pt_vdp_inst = NULL;
    }

    return i4_ret;
}

static INT32 _mmp_vp_dp_deinit(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_com_ui_dp_destroy(pt_vdp_inst);
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_destroy(COM_UI_DTL_PG_VIDEO) returns %d.\n", i4_ret));
    }

    pt_vdp_inst = NULL;

    return i4_ret;
}

static INT32 _mmp_vp_dp_show(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_com_ui_dp_view_active(pt_vdp_inst);
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_com_ui_dp_view_active(COM_UI_DTL_PG_VIDEO) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_dp_hide(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_com_ui_dp_view_inactive(pt_vdp_inst);
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT (("mmp_com_ui_dp_view_inactive(COM_UI_DTL_PG_VIDEO) returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_dp_update(VOID)
{
    _mmp_vp_dp_item_title();
    _mmp_vp_dp_item_director();
    _mmp_vp_dp_item_cpright();
    _mmp_vp_dp_item_date();
    _mmp_vp_dp_item_genre();
    _mmp_vp_dp_item_duration();
    _mmp_vp_dp_item_next();

    return _mmp_vp_dp_show();
}

static INT32 _mmp_vp_ib_deinit(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_info_bar_deinit();
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_info_bar_deinit() returns %d.\n", i4_ret));
    }

    return i4_ret;
}

static INT32 _mmp_vp_ib_show(
                    MMP_IB_MSG_CLASS_T          e_msg_class,
                    UTF16_T*                    ws_msg
                    )
{
    INT32           i4_ret;

    i4_ret = mmp_info_bar_set_status_msg(
                    e_msg_class,
                    MMP_IB_STATUS_MSG_TYPE_FILE_STATUS,
                    MMP_IB_STATUS_MSG_ID_FILE_STATUS,
                    ws_msg
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_info_bar_set_status_msg() returns %d.\n", i4_ret));
        return i4_ret;
    }

    i4_ret = mmp_info_bar_flush_msg();
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_info_bar_flush_msg() returns %d.\n", i4_ret));
        return i4_ret;
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_ib_hide(VOID)
{
    INT32           i4_ret;

    i4_ret = mmp_info_bar_clear_status_msg(
                    MMP_IB_STATUS_MSG_TYPE_FILE_STATUS,
                    MMP_IB_STATUS_MSG_ID_FILE_STATUS
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_info_bar_clear_status_msg() returns %d.\n", i4_ret));
        return i4_ret;
    }

    i4_ret = mmp_info_bar_hide();
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_info_bar_hide() returns %d.\n", i4_ret));
        return i4_ret;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_is_repeated_btn
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _mmp_vp_is_repeated_btn(
                    UINT32                          ui4_key_code
                    )
{
    UINT32 ui4_sys_tick_last = 0;
    UINT32 ui4_sys_tick_crnt = 0;
    UINT32 ui4_sys_tick_diff = 0;
    UINT16 i = 0;

    for (i = 0; i < ui2_rpt_keys_num; ++i)
    {
        if (ui4_key_code == at_rpt_key_tick[i].ui4_key_code)
        {
            ui4_sys_tick_crnt = c_os_get_sys_tick();
            ui4_sys_tick_last = at_rpt_key_tick[i].ui4_sys_tick;

            ui4_sys_tick_diff = ui4_sys_tick_crnt - ui4_sys_tick_last;

            if((c_os_get_sys_tick_period() * ui4_sys_tick_diff) > MMP_VP_RPT_KEY_PERIOD)
            {
                at_rpt_key_tick[i].ui4_sys_tick = ui4_sys_tick_crnt;
                return FALSE;
            }
            else
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}


/*----------------------------------------------------------------------------
 * Name: _mmp_vp_dc_btn_act_cb_fct
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
VOID  _mmp_vp_dc_btn_act_cb_fct(
                      VOID*                       pv_tag              /* in  */
                      )
{
    MMP_PL_CMD_NEXT_PARAM_T t_param = { MMP_GROUND_MODE_FORE, TRUE };
    BOOL  b_tag = (BOOL)(UINT32)pv_tag;
    INT32 i4_ret;

   DBG_LOG_PRINT(("SELECT B_TAG = %d\n", b_tag));

    mmp_dc_dlg_delete();

    switch (e_divx_dlg_type)
    {
        case MMP_DC_DLG_TYPE_UNAUTH:
        case MMP_DC_DLG_TYPE_EXPIRED:
        {
            switch(t_g_video_view.e_repeat_mode)
            {
                case MMP_REPEAT_MODE_ONE:         /* return to file browser */
                {
                    i4_ret = mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
                    if(MMPR_OK != i4_ret)
                    {
                         MMP_DBG_ERROR(("mmp_mc_list_browse(MMP_BROWSE_ID_LAST) fail. i4_ret = %d.\r\n", i4_ret));
                         return;
                    }
                    break;
                }

                case MMP_REPEAT_MODE_NONE:
                case MMP_REPEAT_MODE_ALL:         /* continue to next file */
                {
                    i4_ret = mmp_mc_list_next_ex(&t_param);
                    if(MMPR_OK != i4_ret)
                    {
                         MMP_DBG_ERROR(("_mmp_vp_manaul_next() fail. i4_ret = %d.\r\n", i4_ret));
                         return;
                    }
                    break;
                }

                default:
                    break;
            }

            break;
        }

        case MMP_DC_DLG_TYPE_RENTAL:
        {
            if(TRUE == b_tag)                     /* user press YES button */
            {
                i4_ret = _mmp_vp_play();
                if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                {
                     MMP_DBG_ERROR(("_mmp_vp_play() fail. i4_ret = %d.\r\n", i4_ret));
                     return;
                }
            }
            else                                  /* user press NO  button */
            {
                i4_ret = mmp_mc_list_next_ex(&t_param);
                if(MMPR_OK != i4_ret)
                {
                     MMP_DBG_ERROR(("_mmp_vp_manaul_next() fail. i4_ret = %d.\r\n", i4_ret));
                     return;
                }
            }

            break;
        }

        case MMP_DC_DLG_TYPE_REG_CODE:
        default:
            break;
    }

    /* no need to call c_wgl_default_msg_proc(), it has already been done. */
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_set_text
 *
 * Description: This function set the text value of a given text widget
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_set_text(HANDLE_T      h_txt,
                                   UTF16_T*      w2s_text,
                                   BOOL          b_repaint)
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_text),
                          WGL_PACK((UINT16)0xFFFF));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(h_txt,NULL,MMP_VP_SYNC_REPAINT);
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_view_create_txt_widget
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_create_txt_widget(
    HANDLE_T                    h_parent,
    UINT32                      ui4_text_style,
    UTF16_T*                    ws_text,
    const GL_RECT_T*            pt_rect,
    const GL_COLOR_T*           pt_clr_fg,
    const WGL_FONT_INFO_T*      pt_font,
    HANDLE_T*                   ph_txt)
{
    WGL_COLOR_INFO_T            t_clr_info;
    INT32                       i4_ret;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)(ui4_text_style),
                                 NULL,
                                 ph_txt);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));

        *ph_txt = NULL_HANDLE;
        return MMPR_FAIL;
    }

    do
    {
        /*foreground color*/
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable = *pt_clr_fg;
        t_clr_info.u_color_data.t_standard.t_disable = *pt_clr_fg;
        t_clr_info.u_color_data.t_standard.t_highlight = *pt_clr_fg;
        i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_GL_SET_COLOR, WGL_PACK(WGL_CLR_TEXT), WGL_PACK(&t_clr_info));
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_COLOR) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        /*font*/
        i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_GL_SET_FONT, (VOID*)pt_font, NULL);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_FONT) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        /*align*/
        i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_TEXT_SET_ALIGN, WGL_PACK(WGL_AS_LEFT_CENTER), NULL);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_ALIGN) fail. i4_ret = %d.\r\n", i4_ret));
            break;
        }

        /*text*/
        if(ws_text)
        {
            i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_TEXT_SET_TEXT, WGL_PACK(ws_text), WGL_PACK((UINT16)0xFFFF));
            if(WGLR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_TEXT) fail. i4_ret = %d.\r\n", i4_ret));
                break;
            }
        }

        return MMPR_OK;

    } while(0);

    /*free widget*/
    i4_ret = c_wgl_destroy_widget(*ph_txt);
    MMP_ASSERT(WGLR_OK == i4_ret);

    *ph_txt = NULL_HANDLE;
    return MMPR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_view_create_txt_loading
 *
 * Description: Display file loading progress.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_create_txt_loading(
    HANDLE_T                                h_parent,
    HANDLE_T *                              ph_txt)
{
    GL_RECT_T                               t_rect = {MMP_VP_RC_TXT_LOADING_X, MMP_VP_RC_TXT_LOADING_Y, MMP_VP_RC_TXT_LOADING_X + MMP_VP_RC_TXT_LOADING_W, MMP_VP_RC_TXT_LOADING_Y+ MMP_VP_RC_TXT_LOADING_H};
    WGL_FONT_INFO_T                         t_font_info = MMP_COM_UI_RC_NFY_GET_TEXT_FONT();
    GL_COLOR_T                              t_color = MMP_COM_UI_RC_NFY_GET_TEXT_COLOR();
    UINT32                                  ui4_style;
    INT32                                   i4_ret;

    ui4_style = MMP_COM_UI_RC_TEXT_STYLE;

    /*check param*/
    if(NULL == ph_txt)
    {
        return MMPR_INV_ARG;
    }

    i4_ret = _mmp_vp_view_create_txt_widget(h_parent,
                                            ui4_style,
                                            NULL,
                                            &t_rect,
                                            &t_color,
                                            &t_font_info,
                                            ph_txt);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));

        return MMPR_FAIL;
    }

    /*overide align*/
    i4_ret = c_wgl_do_cmd(*ph_txt, WGL_CMD_TEXT_SET_ALIGN, WGL_PACK(WGL_AS_CENTER_CENTER), NULL);
    if(WGLR_OK != i4_ret)
    {
        c_wgl_destroy_widget(*ph_txt);
        MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_TEXT_SET_ALIGN) fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_optl_cb_fct
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
static VOID _mmp_vp_optl_cb_fct(
                    VOID*                           pv_tag,
                    UINT32                          ui4_msg,
                    VOID*                           pv_param1,
                    VOID*                           pv_param2
                    )
{
    VIDEO_PLAYER_VIEW_T* pt_this = &t_g_video_view;

    switch(ui4_msg)
    {
        case OPTL_MSG_KEY_INPUT:
        {
            UINT32 ui4_key_code = (UINT32)pv_param1;

            if(VIDEO_PLAYER_BTN_OPTION == ui4_key_code)
            {
                mmp_mc_event_switch_context(
                                MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_vp_optl_hide,
                                NULL,NULL,NULL,NULL
                                );
            }
            else if((BTN_CURSOR_UP    == ui4_key_code) ||
                    (BTN_CURSOR_DOWN  == ui4_key_code) ||
                    (BTN_CURSOR_LEFT  == ui4_key_code) ||
                    (BTN_CURSOR_RIGHT == ui4_key_code))
            {
                c_timer_stop(t_g_video_view.h_timer_viewer);
                c_timer_start(t_g_video_view.h_timer_viewer,
                             MMP_VP_TIMER_VIERER_HIDE,
                             X_TIMER_FLAG_ONCE,
                             _mmp_vp_timer_nfy_fct,
                             NULL
                             );
            }
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
            else
            {
                INT32 i4_ret;

                i4_ret = mmp_mc_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
                if(MMPR_OK == i4_ret)
                {
                    a_optl_hide(pt_this->h_opt_list);
                    pt_this->e_opt_stat = _MMP_VP_OPTL_LST_STAT_HIDE;
                }
                break;
            }
#endif
        }
        break;

        case OPTL_MSG_CANCELLED:
        {
            c_wgl_set_focus(pt_this->h_frm_main, WGL_NO_AUTO_REPAINT);
        }
        break;

        case OPTL_MSG_HIDE_TIMEOUT:
        case OPTL_MSG_ITEM_HIGHLIGHT:
        default:
            break;
    }
}

static INT32 _mmp_vp_optl_play_pause(VOID* param)
{
    INT32 i4_ret;

    switch(t_g_video_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_PLAY:
        {
            i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
            if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_mc_list_pause() fail. i4_ret = %d.\r\n", i4_ret));
                return i4_ret;
            }
        }
        break;

        case MMP_VE_PLAY_STAT_PAUSE:
        case MMP_VE_PLAY_STAT_BLANK:
        case MMP_VE_PLAY_STAT_FAST_FWD:
        case MMP_VE_PLAY_STAT_FAST_RWD:
        case MMP_VE_PLAY_STAT_SLOW_FWD:
        case MMP_VE_PLAY_STAT_SLOW_RWD:
        case MMP_VE_PLAY_STAT_STOP:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T  w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif
            i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
            if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_mc_list_play() fail. i4_ret = %d.\r\n", i4_ret));
                return i4_ret;
            }
        }
        break;

        default:
            return MMPR_INV_ARG;
    }

    _mmp_vp_optl_show();
    _mmp_vp_update_status(TRUE);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_optl_set_repeat
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
static INT32 _mmp_vp_optl_set_repeat(VOID* pv_param)
{
    UINT32 ui4_rpt_idx = (UINT32)pv_param;
    MMP_PL_ATTR_T at_attr[1];
    UTF16_T* pw2s_next = NULL;
    INT32 i4_ret;

    switch (ui4_rpt_idx)
    {
        case 0:
            t_g_video_view.e_repeat_mode = MMP_REPEAT_MODE_NONE;
            pw2s_next = w2s_g_next;
            break;

        case 1:
            t_g_video_view.e_repeat_mode = MMP_REPEAT_MODE_ONE;
            pw2s_next = w2s_g_file;
            break;

        case 2:
            t_g_video_view.e_repeat_mode = MMP_REPEAT_MODE_ALL;
            pw2s_next = w2s_g_next;
            break;

        default:
            return MMPR_INV_ARG;
    }

    at_attr[0].e_id = MMP_PL_ATTR_ID_FG_REPEAT;
    at_attr[0].pv_param = (VOID*) t_g_video_view.e_repeat_mode;

    i4_ret =  mmp_mc_list_set_attr(1, at_attr);
    if(MMPR_OK != i4_ret && MMPR_IS_PRELOADED != i4_ret)
    {
        pw2s_next = NULL;
    }

    i4_ret = _mmp_vp_view_update_file_repeat(TRUE);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    pt_vdp_inst->e_repaint = (t_g_video_view.e_detail_page == MMP_VP_DETAIL_PAGE_ON)? COM_UI_ASYNC_REPAINT: COM_UI_NON_REPAINT;
    mmp_com_ui_dp_set_text(pt_vdp_inst, MMP_VP_RC_DP_LBL_ID_NEXT, pw2s_next);

    return MMPR_OK;
}

static INT32 _mmp_vp_optl_get_repeat(VOID* pv_tag, UINT16* pui2_repeat_idx)
{
    SIZE_T                      z_size;
    MMP_REPEAT_MODE_T           e_repeat_mode;

    z_size = sizeof(MMP_REPEAT_MODE_T);
    mmp_mc_list_get_attr(MMP_PL_ATTR_ID_FG_REPEAT, &z_size, &e_repeat_mode);

    switch(e_repeat_mode)
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

/* Name: _mmp_vp_optl_toggle_program
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
static INT32 _mmp_vp_optl_toggle_program(VOID* pv_param)
{
    UINT32 ui4_program_index = (UINT32)pv_param;
    MMP_VE_PROGRAM_INFO_T   t_program_info = {0};
    INT32  i4_ret            = MMPR_OK;
    MMP_FP_PRESENT_MODE_T t_present_mode = MMP_FP_PRESENT_MODE_FULL;

    if(ui4_program_index >=t_g_video_view.t_program_info.ui1_program_num)
    {
        return MMPR_FAIL;
    }
    if(ui4_program_index == t_g_video_view.t_program_info.ui1_cur_idx)
    {
        return MMPR_OK;
    }

    t_g_video_view.t_program_info.ui1_cur_idx = ui4_program_index;

    t_program_info = t_g_video_view.t_program_info;

    _mmp_vp_view_reset(TRUE,TRUE);

    _mmp_vp_tb_icon_file_name(w2s_g_file, MMP_TB_SYNC_REPAINT);

    _mmp_vp_tb_icon_file_idx(TRUE);

    t_g_video_view.t_program_info = t_program_info;

    i4_ret = video_engine_program_select(t_g_video_view.pt_engine_inst,ui4_program_index);

    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("[Video_engine]: Select program %d returns %d.\n",ui4_program_index,i4_ret));
        return i4_ret;
    }

    mmp_mc_list_get_play_present_mode(&t_present_mode);
    if (MMP_FP_PRESENT_MODE_PREVIEW == t_present_mode)
    {
        return MMPR_OK;
    }

    mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_vp_optl_hide,
                    NULL,NULL,NULL,NULL
                    );

    return MMPR_OK;
}

static INT32 _mmp_vp_optl_get_program_idx(VOID* pv_tag, UINT16* pui2_program_idx)
{
    if (NULL == pui2_program_idx)
    {
        return MMPR_INV_ARG;
    }

    *pui2_program_idx = t_g_video_view.t_program_info.ui1_cur_idx;

    return MMPR_OK;
}

static INT32 _mmp_vp_optl_set_scr_mode(VOID* pv_param)
{
    SCC_VID_SCREEN_MODE_T e_scr_mode = (SCC_VID_SCREEN_MODE_T)(UINT32)pv_param;
    INT32 i4_ret;

    if(SCC_VID_SCREEN_MODE_UNKNOWN == e_scr_mode)
    {
        return MMPR_OK;
    }

    i4_ret = video_engine_set_screen_mode(t_g_video_view.pt_engine_inst, e_scr_mode);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = _mmp_vp_view_zoom(TRUE);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    return MMPR_OK;
}


static INT32 _mmp_vp_optl_get_scr_mode(VOID* pv_tag, UINT16* pui2_repeat_idx)
{
    INT32 i4_ret;
    SCC_VID_SCREEN_MODE_T  t_scr_mode;
    UINT16 i = 0;

    i4_ret = video_engine_get_screen_mode(t_g_video_view.pt_engine_inst, &t_scr_mode);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("video_engine_get_screen_mode fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    for(i = 0; i < MMP_VP_OPTL_SCR_MODE_NUM; i++)
    {
        if(t_scr_mode == t_g_video_view.t_optl_scr_mode[i])
        {
            *pui2_repeat_idx = i;
            return MMPR_OK;
        }
    }

    return MMPR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_optl_set_pic_mode
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
static INT32 _mmp_vp_optl_set_pic_mode(VOID* pv_param)
{
    MMP_VP_PIC_MODE_STATUS_T e_pic_mode = (MMP_VP_PIC_MODE_STATUS_T)(UINT32)pv_param;

    if(t_g_video_view.e_pic_mode == e_pic_mode)
    {
        return MMPR_OK;
    }

    t_g_video_view.e_pic_mode = e_pic_mode;

    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                 (INT16)t_g_video_view.e_pic_mode);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));

    return MMPR_OK;
}

static INT32 _mmp_vp_optl_get_pic_mode(VOID* pv_tag, UINT16* pui2_idx)
{
    INT16       i2_pic_mode;

    switch (t_g_video_view.e_pic_mode)
    {
        case MMP_VP_PIC_MODE_NONE:
        {
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),
                         (INT16 *)&i2_pic_mode);
            *pui2_idx = ((0 <= i2_pic_mode) && (i2_pic_mode <= 4)) ? (UINT16)i2_pic_mode : 0;
        }
        break;

        case MMP_VP_PIC_MODE_USER:
        case MMP_VP_PIC_MODE_CINEMA:
        case MMP_VP_PIC_MODE_SPORT:
        case MMP_VP_PIC_MODE_VIVID:
        case MMP_VP_PIC_MODE_HIBRI:
        {
            *pui2_idx = (UINT16)(t_g_video_view.e_pic_mode - MMP_VP_PIC_MODE_USER);
        }
        break;

        default:
        {
            MMP_DBG_ERROR(("Unknown picture mode(%d).\r\n", t_g_video_view.e_pic_mode));
            return MMPR_INV_ARG;
        }
    }

    return MMPR_OK;
}

static VOID _mmp_vp_optl_scr_mode_load_msg(VOID)
{
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_NORMAL            ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NORMAL);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_LETTERBOX         ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_LETTERBOX);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_PAN_SCAN          ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_PAN_SCAN);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_USER_DEFINED      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_USER_DEFINED);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_NON_LINEAR_ZOOM   ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_DOT_BY_DOT        ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_DOT_BY_DOT);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_0      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_0);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_1      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_1);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_2      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_2);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_3      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_3);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_4      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_4);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_5      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_5);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_6      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_6);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_7      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_7);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_0  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_0);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_1  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_1);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_2  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_2);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_3  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_3);

    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_NORMAL           ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NORMAL);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_LETTERBOX        ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_LETTERBOX);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_PAN_SCAN         ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_PAN_SCAN);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_USER_DEFINED     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_USER_DEFINED);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_NON_LINEAR_ZOOM  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_DOT_BY_DOT       ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_DOT_BY_DOT);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_0     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_0);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_1     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_1);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_2     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_2);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_3     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_3);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_4     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_4);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_5     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_5);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_6     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_6);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_7     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_7);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_0 ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_0);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_1 ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_1);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_2 ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_2);
    apw2s_g_scr_msg [MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_3 ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_3);

    apw2s_g_scr_msg [MMP_VP_SCR_FMT_NO_ADJUST             ] = (UTF16_T*)L"Not Adjustable";
}

static MMP_VP_SCR_FMT_T _mmp_vp_optl_scr_mode_get_scr_fmt(
                    VSH_SRC_ASPECT_RATIO_T          e_src_asp_ratio,
                    SCC_VID_SCREEN_MODE_T           e_scr_mode
                    )
{
    MMP_VP_SCR_FMT_T e_scr_fmt;

    switch (e_scr_mode)
    {
        case SCC_VID_SCREEN_MODE_NORMAL:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_NORMAL : MMP_VP_SCR_FMT_16_9_NORMAL;
            break;

        case SCC_VID_SCREEN_MODE_LETTERBOX:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_LETTERBOX : MMP_VP_SCR_FMT_16_9_LETTERBOX;
            break;

        case SCC_VID_SCREEN_MODE_USER_DEFINED:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_USER_DEFINED : MMP_VP_SCR_FMT_16_9_USER_DEFINED;
            break;

        case SCC_VID_SCREEN_MODE_PAN_SCAN:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_PAN_SCAN : MMP_VP_SCR_FMT_16_9_PAN_SCAN;
            break;

        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_NON_LINEAR_ZOOM : MMP_VP_SCR_FMT_16_9_NON_LINEAR_ZOOM;
            break;

        case SCC_VID_SCREEN_MODE_DOT_BY_DOT:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_DOT_BY_DOT : MMP_VP_SCR_FMT_16_9_DOT_BY_DOT;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_0 : MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_0;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_1 : MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_1;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_2:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_2 : MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_2;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_3:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_3 : MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_3;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_4:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_4 : MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_4;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_5:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_5 : MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_5;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_6:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_6 : MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_6;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_7:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_CUSTOM_DEF_7 : MMP_VP_SCR_FMT_16_9_CUSTOM_DEF_7;
            break;

        case SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_0:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_0 : MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_0;
            break;

        case SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_1:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_0 : MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_1;
            break;

        case SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_2:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_0 : MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_2;
            break;

        case SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_3:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        MMP_VP_SCR_FMT_4_3_NLZ_CUSTOM_DEF_0 : MMP_VP_SCR_FMT_16_9_NLZ_CUSTOM_DEF_3;
            break;

        default:
            e_scr_fmt = MMP_VP_SCR_FMT_NO_ADJUST;
            break;
    }

    return e_scr_fmt;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_optl_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_optl_create(
    HANDLE_T                                h_parent,
    HANDLE_T*                               ph_optl)
{
    INT32                i4_ret = -1;
    OPTL_INIT_T          t_optl_init;

    c_memset(&t_optl_init, 0, sizeof(OPTL_INIT_T));

    t_optl_init.h_parent = h_parent;
    t_optl_init.t_gui_rc.i4_left = OPTION_LIST_LEFT;
    t_optl_init.t_gui_rc.i4_top  = OPTION_LIST_TOP;
    t_optl_init.ui4_style_mask   = 0;
    t_optl_init.pv_tag = NULL;
    t_optl_init.pf_fct = _mmp_vp_optl_cb_fct;
    t_optl_init.pf_get_key_src_fct = NULL;
    t_optl_init.ui4_custom_flag = 0;
    t_optl_init.ui4_sleep_time = 0;

    i4_ret = a_optl_create(&t_optl_init, ph_optl);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    _mmp_vp_optl_scr_mode_load_msg();

    return MMPR_OK;
}

static INT32 _mmp_vp_optl_set_item (VOID)
{
    VIDEO_PLAYER_VIEW_T*        pt_this = &t_g_video_view;
    OPTL_ITEM_DEF_T             t_optl_item_def;
    OPTL_ITEM_T                 t_optl_item[7];
    OPTL_SUBITEM_T              t_sub_item_repeat[3];
    OPTL_SUBITEM_T              t_sub_item_pictur[5];
    OPTL_SUBITEM_T              t_sub_item_screen[9];
    MMP_VE_VID_INFO_T           t_vid_info;
    SCC_VID_SCREEN_MODE_T       e_scr_mode = SCC_VID_SCREEN_MODE_UNKNOWN;
    MMP_VP_SCR_FMT_T            e_scr_fmt;
    UINT32                      aui4_repeat_mlm[3] = {MLM_MMP_KEY_AUD_OPT_REPEAT_NONE,
                                                      MLM_MMP_KEY_AUD_OPT_REPEAT_ONE,
                                                      MLM_MMP_KEY_AUD_OPT_REPEAT_ALL};
    UINT32                      aui4_pictur_mlm[5] = {MLM_MMP_KEY_VP_USER,
                                                      MLM_MMP_KEY_VP_CINEMA,
                                                      MLM_MMP_KEY_VP_SPORT,
                                                      MLM_MMP_KEY_VP_VIVID,
                                                      MLM_MMP_KEY_VP_HI_BRI};
    UINT16                      ui2_elem_num = 0;
    UINT32                      ui4_index;
    UINT8                       ui1_cnt = 0;
    INT32                       i4_ret;
    OPTL_SUBITEM_T              t_sub_item_program[MAX_PROGRAM_NUM];
    CHAR                        cs_temp[32] = { 0 };

    if((MMP_VE_PLAY_STAT_OPEN  == pt_this->e_player_status) ||
       (MMP_VE_PLAY_STAT_CLOSE == pt_this->e_player_status) ||
       (MMP_VE_PLAY_STAT_NEXT  == pt_this->e_player_status))
    {
        return MMPR_NOT_SUPPORT;
    }

    c_memset(t_optl_item, 0, sizeof(t_optl_item));

    /*xxxxxxxxxxxxxxxxx sub item repeat mode xxxxxxxxxxxxxxxxx*/
    for(ui4_index = 0; ui4_index < 3; ui4_index++)
    {
        t_sub_item_repeat[ui4_index].pf_fct = _mmp_vp_optl_set_repeat;
        t_sub_item_repeat[ui4_index].pv_tag = (VOID*)ui4_index;
        t_sub_item_repeat[ui4_index].pw2s_text =
                MLM_MMP_TEXT(pt_this->ui2_lang, aui4_repeat_mlm[ui4_index]);
    }

    /*xxxxxxxxxxxxxxxxx program index mode xxxxxxxxxxxxxxxxx*/
    for(ui4_index = 0; ui4_index < MAX_PROGRAM_NUM; ui4_index++)
    {
        t_sub_item_program[ui4_index].pf_fct = _mmp_vp_optl_toggle_program;
        t_sub_item_program[ui4_index].pv_tag = (VOID*)ui4_index;
        c_sprintf(cs_temp, "Program %d",ui4_index);
        UTF16_T* ws = c_mem_alloc(32*sizeof(UTF16_T));
        if(!ws)break;
        c_uc_ps_to_w2s(cs_temp, ws, 32);
        t_sub_item_program[ui4_index].pw2s_text = ws;
    }

    /*xxxxxxxxxxxxxxxxx sub item screen mode xxxxxxxxxxxxxxxxx*/
    do
    {
        if (MMP_VP_AV_STAT_VIDEO_NONE & pt_this->ui2_av_ntfy)
        {
            break;
        }

        i4_ret = video_engine_get_vid_info(pt_this->pt_engine_inst, &t_vid_info);
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        i4_ret = a_sml_get_num_rec(t_vid_info.e_asp_ratio, (UINT8*) &ui2_elem_num);
        if ((SMLR_OK != i4_ret) || ((UINT16)0 == ui2_elem_num))
        {
            break;
        }

        /* Get first screen mode. */
        a_sml_iterate_rec(t_vid_info.e_asp_ratio, SML_ITERATE_DIR_FIRST, &e_scr_mode);

        /* Get screen format by e_src_asp_ratio & e_scr_mode */
        e_scr_fmt = _mmp_vp_optl_scr_mode_get_scr_fmt(t_vid_info.e_asp_ratio, e_scr_mode);

        pt_this->t_optl_scr_mode[0] = e_scr_mode;

        /* Set the first index-text to screen format */
        t_sub_item_screen[0].pf_fct = _mmp_vp_optl_set_scr_mode;
        t_sub_item_screen[0].pv_tag = (VOID*)(UINT32)e_scr_mode;
        t_sub_item_screen[0].pw2s_text = apw2s_g_scr_msg[e_scr_fmt];

        for(ui4_index = 1; ui4_index < ui2_elem_num; ui4_index++)
        {
            if(9 <= ui4_index)
            {
                break;
            }

            a_sml_iterate_rec(t_vid_info.e_asp_ratio, SML_ITERATE_DIR_NEXT, &e_scr_mode);

            e_scr_fmt = _mmp_vp_optl_scr_mode_get_scr_fmt(t_vid_info.e_asp_ratio, e_scr_mode);

            pt_this->t_optl_scr_mode[ui4_index] = e_scr_mode;

            t_sub_item_screen[ui4_index].pf_fct = _mmp_vp_optl_set_scr_mode;
            t_sub_item_screen[ui4_index].pv_tag = (VOID*)(UINT32)e_scr_mode;
            t_sub_item_screen[ui4_index].pw2s_text = apw2s_g_scr_msg[e_scr_fmt];
        }

    }while(0);

    if((UINT16)0 == ui2_elem_num)
    {
        ui2_elem_num = 1;   /* One for "Not Adjustable" */

        t_sub_item_screen[0].pf_fct = _mmp_vp_optl_set_scr_mode;
        t_sub_item_screen[0].pv_tag = (VOID*)(UINT32)SCC_VID_SCREEN_MODE_UNKNOWN;
        t_sub_item_screen[0].pw2s_text = apw2s_g_scr_msg[MMP_VP_SCR_FMT_NO_ADJUST];
    }

    /*xxxxxxxxxxxxxxxxx sub item picture mode xxxxxxxxxxxxxxxxx*/
    for(ui4_index = 0; ui4_index < 5; ui4_index++)
    {
        t_sub_item_pictur[ui4_index].pf_fct    = _mmp_vp_optl_set_pic_mode;
        t_sub_item_pictur[ui4_index].pv_tag    = (VOID*)(UINT32)ui4_index;
        t_sub_item_pictur[ui4_index].pw2s_text =
                MLM_MMP_TEXT(pt_this->ui2_lang, aui4_pictur_mlm[ui4_index]);
    }

    /*MMMMMMMMMMMMMMMMMMMM item play pause MMMMMMMMMMMMMMMMMMMM*/
    switch(pt_this->e_player_status)
    {
        case MMP_VE_PLAY_STAT_PAUSE:
        case MMP_VE_PLAY_STAT_BLANK:
        case MMP_VE_PLAY_STAT_STOP:
        case MMP_VE_PLAY_STAT_FAST_FWD:
        case MMP_VE_PLAY_STAT_FAST_RWD:
        case MMP_VE_PLAY_STAT_SLOW_FWD:
        case MMP_VE_PLAY_STAT_SLOW_RWD:
        {
            t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(
                                                    pt_this->ui2_lang,
                                                    MLM_MMP_KEY_TB_PLAY
                                                    );
        }
        break;

        case MMP_VE_PLAY_STAT_PLAY:
        {
            t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(
                                                    pt_this->ui2_lang,
                                                    MLM_MMP_KEY_TB_PAUSE
                                                    );
        }
        break;

        default:
        {
            return MMPR_INV_ARG;
        }
    }

    if(FALSE == pt_this->b_crt_play_invalid_file)
    {
        t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_vp_optl_play_pause;
        t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        t_optl_item[ui1_cnt].u.t_action.pv_tag = NULL;
        ui1_cnt++;
    }
    else if((MMP_VP_AV_STAT_AUDIO_NONE & t_g_video_view.ui2_av_ntfy) &&
            (MMP_VP_AV_STAT_VIDEO_NONE & t_g_video_view.ui2_av_ntfy)) /* DTV00214967 */
    {
        t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_vp_optl_play_pause;
        t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
        t_optl_item[ui1_cnt].u.t_action.pv_tag = NULL;
        ui1_cnt++;
    }

    /*MMMMMMMMMMMMMMMMMMMM item repeat mode MMMMMMMMMMMMMMMMMMMM*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_TB_REPEAT);
    t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = 3;
    t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_repeat;
    t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_vp_optl_get_repeat;
    ui1_cnt++;

    /*MMMMMMMMMMMMMMMMMMMMM item program num MMMMMMMMMMMMMMMMMMMM*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
    t_optl_item[ui1_cnt].pw2s_text = (UTF16_T*)L"Program";;
    t_optl_item[ui1_cnt].b_is_disable = FALSE;
    t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items =t_g_video_view.t_program_info.ui1_program_num;
    t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_program;
    t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_vp_optl_get_program_idx;
    ui1_cnt++;

    /*MMMMMMMMMMMMMMMMMMMM item show/hide info MMMMMMMMMMMMMMMMMMMM*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_ACTION;
    if(MMP_VP_DETAIL_PAGE_OFF == pt_this->e_detail_page)
    {
        t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(
                                                    pt_this->ui2_lang,
                                                    MLM_MMP_KEY_AUD_OPT_SHOW_INFO
                                                    );
    }
    else
    {
        t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(
                                                    pt_this->ui2_lang,
                                                    MLM_MMP_KEY_AUD_OPT_HIDE_INFO
                                                    );
    }

    if(FALSE == pt_this->b_crt_play_invalid_file)
    {
        t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)TRUE;
        t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_vp_view_toggle_detail_page;
        ui1_cnt++;
    }
    else if((MMP_VP_AV_STAT_AUDIO_NONE & t_g_video_view.ui2_av_ntfy) &&
            (MMP_VP_AV_STAT_VIDEO_NONE & t_g_video_view.ui2_av_ntfy)) /* DTV00214967 */
    {
        t_optl_item[ui1_cnt].u.t_action.pv_tag = (VOID*)(UINT32)TRUE;
        t_optl_item[ui1_cnt].u.t_action.pf_fct = _mmp_vp_view_toggle_detail_page;
        ui1_cnt++;
    }

    /*MMMMMMMMMMMMMMMMMMMM item zoom MMMMMMMMMMMMMMMMMMMM*/

    /*MMMMMMMMMMMMMMMMMMMM item picture mode MMMMMMMMMMMMMMMMMMMM */
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_VP_PIC_MODE);
    t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = 5;
    t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_pictur;
    t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_vp_optl_get_pic_mode;
    ui1_cnt++;

    /*MMMMMMMMMMMMMMMMMMMM item screen mode MMMMMMMMMMMMMMMMMMMM*/
    t_optl_item[ui1_cnt].e_type = OPTL_ITEM_TYPE_SUBLIST;
    t_optl_item[ui1_cnt].pw2s_text = MLM_MMP_TEXT(pt_this->ui2_lang, MLM_MMP_KEY_VP_SCR_MODE);
    t_optl_item[ui1_cnt].u.t_subopt_list.ui2_num_of_sub_items = ui2_elem_num;
    t_optl_item[ui1_cnt].u.t_subopt_list.pt_sub_item = t_sub_item_screen;
    t_optl_item[ui1_cnt].u.t_subopt_list.pf_get_sub_hlt_idx_fct = _mmp_vp_optl_get_scr_mode;
    ui1_cnt++;

    /*~~~~~~~~~~~~~~~~~~~~~ main item 6 ~~~~~~~~~~~~~~~~~~~~~*/
    t_optl_item_def.pt_opt_item = t_optl_item;
    t_optl_item_def.ui2_num_of_opt_items = ui1_cnt;
    t_optl_item_def.pw2s_title = NULL;

    a_optl_set_option_items(pt_this->h_opt_list, &t_optl_item_def);

    return MMPR_OK;
}

static INT32 _mmp_vp_optl_show (VOID)
{
    if (MMP_VE_PLAY_STAT_BLANK == t_g_video_view.e_player_status)
    {
        return MMPR_OK; /* To fix DTV00215789 */
    }

    if(MMP_VP_DETAIL_PAGE_ON == t_g_video_view.e_detail_page)
    {
        _mmp_vp_view_toggle_detail_page((VOID*)(UINT32)FALSE);
    }

    IS_MMPR_OK(_mmp_vp_optl_set_item ());

    t_g_video_view.e_opt_stat = _MMP_VP_OPTL_LST_STAT_SHOW;
    IS_MMPR_OK(a_optl_set_visibility(t_g_video_view.h_opt_list, TRUE));
    IS_MMPR_OK(a_optl_set_focus(t_g_video_view.h_opt_list));
    a_optl_repaint(t_g_video_view.h_opt_list);

    c_wgl_repaint(t_g_video_view.h_frm_main, NULL, MMP_VP_SYNC_REPAINT);

    return MMPR_OK;
}

static VOID  _mmp_vp_optl_hide(
                    VOID*                           pv_param1,
                    VOID*                           pv_param2,
                    VOID*                           pv_param3,
                    VOID*                           pv_param4
                    )
{
    a_optl_hide(t_g_video_view.h_opt_list);
    t_g_video_view.e_opt_stat = _MMP_VP_OPTL_LST_STAT_HIDE;
    c_wgl_set_focus(t_g_video_view.h_frm_main, WGL_NO_AUTO_REPAINT);
}

#ifdef APP_CAPTURE_LOGO_SUPPORT
static VOID _mmp_vp_logo_do_nfy_fct(
                    VOID*                           pv_host,
                    VOID*                           pv_msg,
                    VOID*                           pv_arg1,
                    VOID*                           pv_arg2
                    )
{
    VIDEO_PLAYER_VIEW_T* pt_this = (VIDEO_PLAYER_VIEW_T*)pv_host;
    UINT32 ui4_msg  = (UINT32)pv_msg;
    UINT32 ui4_arg1 = (UINT32)pv_arg1;
    UINT32 ui4_arg2 = (UINT32)pv_arg2;
    INT32 i4_ret;

    switch (ui4_msg)
    {
        case CAP_MSG_PRE_ACTIVATE:
        {
            if (MMP_VE_PLAY_STAT_PAUSE != t_g_video_view.e_player_status)
            {
                i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
                {
                   DBG_LOG_PRINT(("mmp_mc_list_pause() returns %d.\n", i4_ret));
                    return;
                }
            }

            c_timer_stop(t_g_video_view.h_timer_viewer);
            _mmp_vp_hide_viewer(NULL, NULL, NULL, NULL);

            break;
        }

        case CAP_MSG_POST_INACTIVATE:
        {
            i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE,MMP_PLAY_IDX_CURRENT);
            if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
            {
               DBG_LOG_PRINT(("mmp_mc_list_play() returns %d.\n", i4_ret));
            }
            return; /* must NOT break */
        }

        case CAP_MSG_FAIL:
        {
            a_cap_abort(pt_this->pv_cap_logo);
            return; /* must NOT break */
        }

        default:
            break;
    }

    a_cap_def_msg_process(pt_this->pv_cap_logo, ui4_msg, ui4_arg1, ui4_arg2);
}

static VOID _mmp_vp_logo_proc_fct(
                    VOID*                           pv_tag,
                    UINT32                          ui4_msg,
                    UINT32                          ui4_arg1,
                    UINT32                          ui4_arg2
                    )
{
    mmp_mc_event_switch_context(
                    MMP_MC_CSC_RETRY_TYPE_ONCE,
                    _mmp_vp_logo_do_nfy_fct,
                    pv_tag,
                    (VOID*)ui4_msg,
                    (VOID*)ui4_arg1,
                    (VOID*)ui4_arg2
                    );
}

static INT32 _mmp_vp_logo_create(VOID)
{
    VIDEO_PLAYER_VIEW_T* pt_this = &t_g_video_view;
    CAP_INIT_T t_cap_init;
    INT32 i4_ret;

    c_memset(&t_cap_init, 0, sizeof(CAP_INIT_T));

    t_cap_init.h_parent = pt_this->h_frm_main;
    t_cap_init.e_source = CAP_SRC_TYPE_MM_VIDEO;
    t_cap_init.pf_fct = _mmp_vp_logo_proc_fct;
    t_cap_init.pv_tag = pt_this;

    i4_ret = a_cap_create(&t_cap_init, &pt_this->pv_cap_logo);
    if (ACAPR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_not_support
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
static INT32 _mmp_vp_not_support(VOID)
{
    INT32 i4_ret;

    i4_ret = _mmp_vp_ib_show(
                    MMP_IB_MSG_CLASS_INFO,
                    MLM_MMP_VP_TEXT(MLM_MMP_KEY_FEATURE_NOT_AVAILABLE)
                    );
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    c_timer_start (t_g_video_view.h_timer_reset_icon,
                   2 * 1000,
                   X_TIMER_FLAG_ONCE,
                   _mmp_vp_timer_nfy_fct,
                   NULL);

    return MMPR_OK;
}

static INT32 _mmp_vp_do_next_speed(MMP_FP_SHOW_CMD_ID_T e_cmd)
{
    INT32                   i4_ret = MMPR_OK;
    UINT8                   ui1_limit = 8;//32; Fix DTV00825076
    MMP_VE_PLAY_STAT_T        e_exp_status;
    const    SPLAYER_TrickSpeed_e e_fwd[] = {
                                        SPLAYER_MM_TRICK_SPEED_2X, SPLAYER_MM_TRICK_SPEED_4X,
                                        SPLAYER_MM_TRICK_SPEED_8X , SPLAYER_MM_TRICK_SPEED_16X,
                                        SPLAYER_MM_TRICK_SPEED_32X};
    const    SPLAYER_TrickSpeed_e e_rwd[] = {
                                        SPLAYER_MM_TRICK_SPEED_SLOW_2X,  SPLAYER_MM_TRICK_SPEED_SLOW_4X,
                                        SPLAYER_MM_TRICK_SPEED_SLOW_8X,  SPLAYER_MM_TRICK_SPEED_SLOW_16X,
                                        SPLAYER_MM_TRICK_SPEED_SLOW_32X};

    const    SPLAYER_TrickSpeed_e e_sfwd[] = {
                                        SPLAYER_MM_TRICK_SPEED_1_25X, SPLAYER_MM_TRICK_SPEED_1_5X,
                                        SPLAYER_MM_TRICK_SPEED_1_75X};
   const    SPLAYER_TrickSpeed_e e_srwd[] = {
                                        SPLAYER_MM_TRICK_SPEED_SLOW_1_33X,  SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_2X,
                                        SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_4X,  SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_8X,
                                        SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_16X,SPLAYER_MM_TRICK_SPEED_SLOW_SCAN_32X};

   const   SPLAYER_TrickSpeed_e* pe_sel_speed = NULL;

    if((MMP_VP_AV_STAT_VIDEO_NONE & t_g_video_view.ui2_av_ntfy) ||
        (_video_player_is_playing() == FALSE))
    {
        _mmp_vp_not_support();
        return MMPR_NOT_SUPPORT;
    }

    switch (e_cmd)
    {
        case MMP_FP_SHOW_CMD_ID_FAST_FORWARD:
          e_exp_status = MMP_VE_PLAY_STAT_FAST_FWD;
        pe_sel_speed = e_fwd;
        break;

        case MMP_FP_SHOW_CMD_ID_FAST_REWIND:
        e_exp_status = MMP_VE_PLAY_STAT_FAST_RWD;
        pe_sel_speed = e_rwd;
        break;

        case MMP_FP_SHOW_CMD_ID_SLOW_FORWARD:
        e_exp_status = MMP_VE_PLAY_STAT_SLOW_FWD;
        pe_sel_speed = e_sfwd;
        break;

        case MMP_FP_SHOW_CMD_ID_SLOW_REWIND:
        e_exp_status = MMP_VE_PLAY_STAT_SLOW_RWD;
        pe_sel_speed = e_srwd;
        break;
        default:
            return MMPR_INV_ARG;
    }

    if (t_g_video_view.e_player_status == e_exp_status)
    {
        t_g_video_view.ui1_step <<= 1 ;
        if (t_g_video_view.ui1_step > ui1_limit)
        {
            t_g_video_view.ui1_step = 1;
        }
    }
    else
    {
        t_g_video_view.ui1_step = 2;
    }

    if (t_g_video_view.ui1_step != 1)
    {
        UINT8 ui1_cur = 2;
        while (ui1_cur < t_g_video_view.ui1_step)
        {
            pe_sel_speed++;
            ui1_cur <<= 1;
        }
        i4_ret = video_engine_set_speed(t_g_video_view.pt_engine_inst, *pe_sel_speed);
        if ((i4_ret == MMPR_NOT_SUPPORT || MMPR_TRICK_CHANGE == i4_ret)&&
            t_g_video_view.e_player_status == e_exp_status)
        {
            //when change to next speed but not support change normal
            t_g_video_view.ui1_step = 1;
        }
    }
    if (t_g_video_view.ui1_step == 1)
    {
        i4_ret = _mmp_vp_play();
        if(MMPR_IS_PLAYED != i4_ret)
        {
            /*mark this return code!because if here return OK, it will casue player status became slow forwarding is do slow forward repeatly for special PS file!*/
            //i4_ret = MMPR_OK;
            return i4_ret;
        }
    }
    if (i4_ret < 0)
    {
        _mmp_vp_not_support();
        return i4_ret;
    }
    _mmp_vp_update_status(TRUE);
    return i4_ret;
}

static INT32 _mmp_vp_key_code_check(UINT32 ui4_key_code)
{
    if(MMP_VE_PLAY_STAT_BLANK == t_g_video_view.e_player_status)
    {
        switch (ui4_key_code)
        {
            case VIDEO_PLAYER_BTN_PLAY_PAUSE:
            case VIDEO_PLAYER_BTN_STOP:
                break;

            default:
                return MMPR_NOT_SUPPORT;
        }
    }

    if(t_g_video_view.b_crt_play_invalid_file)
    {
        if((MMP_VP_AV_STAT_AUDIO_NONE & t_g_video_view.ui2_av_ntfy) &&
           (MMP_VP_AV_STAT_VIDEO_NONE & t_g_video_view.ui2_av_ntfy))
        {
            switch (ui4_key_code)
            {
                case VIDEO_PLAYER_BTN_PLAY_PAUSE:
                case VIDEO_PLAYER_BTN_STOP:
                case VIDEO_PLAYER_BTN_SET_TIME:
                case BTN_RECORD:
                case BTN_REPEAT:
                    return MMPR_NOT_SUPPORT;

                default:
                    break;
            }
        }
        else
        {
            switch (ui4_key_code)
            {
                case VIDEO_PLAYER_BTN_PLAY_PAUSE:
                case VIDEO_PLAYER_BTN_STOP:
                case VIDEO_PLAYER_BTN_FF:
                case VIDEO_PLAYER_BTN_FR:
                case VIDEO_PLAYER_BTN_INFO:
                case VIDEO_PLAYER_BTN_MTS:
                case VIDEO_PLAYER_BTN_SUB:
                case VIDEO_PLAYER_BTN_ZOOM:
                case VIDEO_PLAYER_BTN_SET_TIME:
                case BTN_RECORD:
                case BTN_REPEAT:
                    return MMPR_NOT_SUPPORT;

                default:
                    break;
            }
        }
    }

    if (MMP_VP_AV_STAT_VIDEO_NONE & t_g_video_view.ui2_av_ntfy)
    {
        switch (ui4_key_code)
        {
            case VIDEO_PLAYER_BTN_SUB:
            case BTN_RECORD:
                return MMPR_NOT_SUPPORT;

            default:
                break;
        }
    }

    if (BTN_RECORD == ui4_key_code)
    {
        switch (t_g_video_view.e_player_status)
        {
            case MMP_VE_PLAY_STAT_PLAY:
            case MMP_VE_PLAY_STAT_PAUSE:
                break;

            default:
                _mmp_vp_not_support();
                return MMPR_NOT_SUPPORT;
        }
    }

    return MMPR_OK;
}

#ifdef APP_IPCC_SUPPORT

static INT32 _mmp_vp_select_sub(BOOL b_repaint)
{
    MMP_VE_SUB_INFO_T t_sub_info = t_g_video_view.t_sub_info;
    INT32 i4_ret;

   DBG_LOG_PRINT(("sub num is:%d .....................\n", t_g_video_view.t_sub_info.ui2_sub_num));

    if(0 == t_g_video_view.t_sub_info.ui2_sub_num)
    {
        i4_ret = video_engine_get_sub_info(t_g_video_view.pt_engine_inst, &t_g_video_view.t_sub_info);
        return MMPR_OK;
    }
    else if(1 == t_g_video_view.t_sub_info.ui2_sub_num)
    {
        return MMPR_OK;
    }

    t_sub_info.ui2_sel_idx = (t_sub_info.ui2_sel_idx + (UINT16)1) % t_sub_info.ui2_sub_num;

    i4_ret = video_engine_sub(t_g_video_view.pt_engine_inst, &t_sub_info);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("video_engine_sub() fail. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
   DBG_LOG_PRINT(("select sub idx is:%d\n", t_sub_info.ui2_sel_idx));

    t_g_video_view.t_sub_info.ui2_sel_idx = t_sub_info.ui2_sel_idx;

    //_mmp_vp_tb_icon_sbtl(&t_g_video_view.t_sub_info, MMP_TB_SYNC_REPAINT);

    return MMPR_OK;
}
#endif

#if 0
static INT32  _mmp_vp_update_seek_status()
{
    VIDEO_PLAYER_VIEW_T *pt_this  = &t_g_video_view;
    if(pt_this->t_seek_status.b_is_seek  == TRUE)
    {
           a_tv_set_mute(TRUE);
           mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL,
                         MMP_MSG_ID_VOL_INFO_UPD,
                         NULL);
    }
    else
    {
        //update mute
        if(pt_this->t_seek_status.b_is_mute_before_seek == FALSE)
        {
           a_tv_set_mute(FALSE);
           mmp_mc_msg_multicast(MMP_MC_MULTICAST_TYPE_ALL,
                         MMP_MSG_ID_VOL_INFO_UPD,
                         NULL);
        }
    }
    return MMPR_OK;
}

static INT32  _mmp_vp_set_seek_status( MMP_VP_SEEK_STATUS t_seek_param)
{
    VIDEO_PLAYER_VIEW_T *pt_this  = &t_g_video_view;
    pt_this->t_seek_status.b_is_mute_before_seek = t_seek_param.b_is_mute_before_seek;
    pt_this->t_seek_status.b_is_seek = t_seek_param.b_is_seek;
    IS_MMPR_OK(_mmp_vp_update_seek_status());
    return MMPR_OK;
}

static MMP_VP_SEEK_STATUS *  _mmp_vp_get_seek_status()
{
    VIDEO_PLAYER_VIEW_T * pt_this  = &t_g_video_view;
    return &pt_this->t_seek_status;
}
#endif

static INT32 _mmp_vp_key_up_handle(UINT32 ui4_key_code)
{
    switch (ui4_key_code)
    {
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        {
             if(e_g_seek_stat == _MMP_VP_SEEK_STAT_SETTING)
                   e_g_seek_stat = _MMP_VP_SEEK_STAT_SEEKING;
        }
            break;

        default:
            return MMPR_OK;
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_tb_seek_enter(UINT32 ui4_key_code)
{
    INT32               i4_ret;
    UINT32              ui4_new_position = 0;

    if(!video_engine_seek_enable(t_g_video_view.pt_engine_inst))
    {
        _mmp_vp_not_support();
        return MMPR_NOT_SUPPORT;
    }
    MMPR_LOG_ON_FAIL(_mmp_vp_tb_show());
    i4_ret = video_engine_get_position(
                        t_g_video_view.pt_engine_inst,
                        MMP_VE_POS_TYPE_TIME,
                        &t_g_video_view.ui8_position
                        );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("video_engine_get_position() returns %d.\n", i4_ret));
        return i4_ret;
    }

    i4_ret = video_engine_get_duration(t_g_video_view.pt_engine_inst,
                                           MMP_VE_DUR_TYPE_TIME,
                                           &t_g_video_view.ui8_duration);

    if(MMPR_OK != i4_ret || 0 == t_g_video_view.ui8_duration)
    {
        i4_ret = video_engine_get_duration(t_g_video_view.pt_engine_inst,
                                           MMP_VE_DUR_TYPE_BYTE,
                                           &t_g_video_view.ui8_duration);
        if (MMPR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("video_engine_get_duration fail! returns %d.\n", i4_ret));
        }

    }

    if (BTN_CURSOR_LEFT == ui4_key_code)
    {
        if (t_g_video_view.ui8_position > MMP_VP_SEEK_STEP)
        {
            ui4_new_position = (UINT32)(t_g_video_view.ui8_position - MMP_VP_SEEK_STEP);
        }
        else
        {
            ui4_new_position = 0;
        }
    }
    else if (BTN_CURSOR_RIGHT == ui4_key_code)
    {
        if ((t_g_video_view.ui8_position + MMP_VP_SEEK_STEP) >= t_g_video_view.ui8_duration)
        {
            ui4_new_position = (UINT32)t_g_video_view.ui8_duration;
        }
        else
        {
            ui4_new_position = (UINT32)(t_g_video_view.ui8_position + MMP_VP_SEEK_STEP);
        }
    }

    i4_ret = video_engine_seek(
                    t_g_video_view.pt_engine_inst,
                    ui4_new_position
                    );
    if (MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("video_engine_seek() returns %d.\n", i4_ret));
    }

   // e_g_seek_stat = _MMP_VP_SEEK_STAT_UNUSED;

    return MMPR_OK;
}

static INT32 _mmp_vp_key_down_handle(UINT32 ui4_key_code)
{
    MMP_PL_CMD_TRICK_PARAM_T t_trick_param;
    INT32 i4_ret;

    t_trick_param.e_mode = MMP_GROUND_MODE_FORE;
    t_trick_param.e_option = MMP_PL_CMD_TRICK_OPTION_RESUME_AFTER_TRICK;

    switch (ui4_key_code)
    {
#ifdef APP_IPCC_SUPPORT
        case BTN_CC:
        {
            _mmp_vp_select_sub(FALSE);
            break;
        }
        break;
#endif
        case BTN_ASPECT:
        {
        #ifndef APP_CAST_TV_MMP_FG
            if ((a_tv_custom_is_3D_mode_playing() == FALSE) &&
                (a_menu_is_hot_key(ui4_key_code, WGL_MSG_KEY_DOWN)))
        #else
            /* fix DTV00867116,casttv menu not reg BTN_ASPECT hot key */
            if (a_tv_custom_is_3D_mode_playing() == FALSE)
        #endif
            {
                a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID *)BTN_ASPECT, NULL);
            }

            return MMPR_OK;
        }
        #ifdef APP_3D_MODE_SUPPORT
        case BTN_3D:
        {
            if (a_menu_is_hot_key(ui4_key_code, WGL_MSG_KEY_DOWN))
            {
                a_menu_hot_key_handler(ui4_key_code,
                                       WGL_MSG_KEY_DOWN,
                                       NULL);
            }
            return MMPR_OK;
        }
        #endif
        case VIDEO_PLAYER_BTN_PLAY:
        {
            switch (t_g_video_view.e_player_status)
            {
                case MMP_VE_PLAY_STAT_PAUSE:
                case MMP_VE_PLAY_STAT_BLANK:
                case MMP_VE_PLAY_STAT_FAST_FWD:
                case MMP_VE_PLAY_STAT_FAST_RWD:
                case MMP_VE_PLAY_STAT_SLOW_FWD:
                case MMP_VE_PLAY_STAT_SLOW_RWD:
                case MMP_VE_PLAY_STAT_STOP:
                {
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE,MMP_PLAY_IDX_CURRENT);
                    if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_mc_list_play() fail. i4_ret = %d.\r\n", i4_ret));
                    }
                    else
                    {
                        _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
                        _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
                    }
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case VIDEO_PLAYER_BTN_PAUSE:
        {
            switch (t_g_video_view.e_player_status)
            {
                case MMP_VE_PLAY_STAT_PLAY:
                case MMP_VE_PLAY_STAT_PAUSE:
                case MMP_VE_PLAY_STAT_BLANK:
                case MMP_VE_PLAY_STAT_FAST_FWD:
                case MMP_VE_PLAY_STAT_FAST_RWD:
                case MMP_VE_PLAY_STAT_SLOW_FWD:
                case MMP_VE_PLAY_STAT_SLOW_RWD:
                case MMP_VE_PLAY_STAT_STOP:
                {
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif

                    i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                    if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_mc_list_pause() fail. i4_ret = %d.\r\n", i4_ret));
                    }
                    else
                    {
                        _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
                        _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
                    }
                }
                    break;
                default:
                    break;
            }
        }
            break;
        case VIDEO_PLAYER_BTN_PLAY_PAUSE:
        case VIDEO_PLAYER_BTN_PLAY_PAUSE_2:
        {
            switch (t_g_video_view.e_player_status)
            {
                case MMP_VE_PLAY_STAT_PLAY:
                {
                #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PAUSE));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif
                    i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_FORE);
                    if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_mc_list_pause() fail. i4_ret = %d.\r\n", i4_ret));
                    }
                    else
                    {
                        _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
                        _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
                    }
                }
                    break;

                case MMP_VE_PLAY_STAT_PAUSE:
                case MMP_VE_PLAY_STAT_BLANK:
                case MMP_VE_PLAY_STAT_FAST_FWD:
                case MMP_VE_PLAY_STAT_FAST_RWD:
                case MMP_VE_PLAY_STAT_SLOW_FWD:
                case MMP_VE_PLAY_STAT_SLOW_RWD:
                case MMP_VE_PLAY_STAT_STOP:
                {
                  #ifdef APP_TTS_SUPPORT
                    UTF16_T         w2s_str[128] = {0};
                    c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_PLAY));
                    a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
                #endif

                    i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE,MMP_PLAY_IDX_CURRENT);
                    if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                    {
                        MMP_DBG_ERROR(("mmp_mc_list_play() fail. i4_ret = %d.\r\n", i4_ret));
                    }
                    else
                    {
                        _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
                        _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
                    }
                }
                    break;

                default:
                    return MMPR_NO_DATA;
            }
        }
            break;

        case VIDEO_PLAYER_BTN_STOP:
        case VIDEO_PLAYER_BTN_STOP_2:
        case VIDEO_PLAYER_BTN_STOP_3:
        {

        #ifdef APP_TTS_SUPPORT
            UTF16_T         w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_STOP));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

        #ifdef APP_3D_MODE_SUPPORT
            BOOL                    b_3d_support = FALSE;
            a_cfg_custom_plf_opt_get_3d_support(&b_3d_support);
            if(b_3d_support)
            {
                a_cfg_custom_3D_setting_reset_3D_mode();
            }
        #endif
        DBG_LOG_PRINT(("[MMP][%s %d]\n",__FUNCTION__,__LINE__));
           if(MMP_VE_PLAY_STAT_PLAY == t_g_video_view.e_player_status)
                mmp_mc_file_stop(MMP_GROUND_MODE_FORE);
            /* press btn_stop handle same as ben_exit */
            i4_ret = mmp_mc_list_browse(MMP_BROWSE_ID_LAST);
            if(MMPR_OK != i4_ret)
            {
                 MMP_DBG_ERROR(("mmp_mc_list_browse(MMP_BROWSE_ID_LAST) fail. i4_ret = %d.\r\n", i4_ret));
            }

            return MMPR_NO_DATA;
        }
        break;

        case VIDEO_PLAYER_BTN_FF:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T         w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_FAST_FORWARD));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

        #ifdef APP_NET_DLNA_SUPPORT
            if(!video_engine_trick_enable(t_g_video_view.pt_engine_inst))
            {
                _mmp_vp_not_support();
                return MMPR_NOT_SUPPORT;
            }
        #endif

            i4_ret = mmp_mc_list_fast_forward(&t_trick_param);
            if(MMPR_OK != i4_ret && MMPR_IS_FAST_FORWARDED != i4_ret)
            {
                 MMP_DBG_ERROR(("mmp_mc_list_step_forward() fail. i4_ret = %d.\r\n", i4_ret));
            }
            else
            {
                _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
            }
        }
            break;

        case VIDEO_PLAYER_BTN_FR:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T         w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_REWIND));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

        #ifdef APP_NET_DLNA_SUPPORT
            if(!video_engine_trick_enable(t_g_video_view.pt_engine_inst))
            {
                _mmp_vp_not_support();
                return MMPR_NOT_SUPPORT;
            }
        #endif

            i4_ret = mmp_mc_list_fast_rewind(&t_trick_param);
            if(MMPR_OK != i4_ret && MMPR_IS_FAST_REWINDED != i4_ret)
            {
                 MMP_DBG_ERROR(("mmp_mc_list_step_rewind() fail. i4_ret = %d.\r\n", i4_ret));
            }
            else
            {
                _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
            }
        }
            break;

        case VIDEO_PLAYER_BTN_SLOW_FF:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T         w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_SLOW_FAST_FORWARD));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

            i4_ret = mmp_mc_list_slow_forward(&t_trick_param);
            if(MMPR_OK != i4_ret && MMPR_IS_SLOW_FORWARDED != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_mc_list_slow_forward() fail. i4_ret = %d.\r\n", i4_ret));
            }
            else
            {
                _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
            }
        }
        break;

        case VIDEO_PLAYER_BTN_SLOW_FR:
        {
        #ifdef APP_TTS_SUPPORT
            UTF16_T         w2s_str[128] = {0};
            c_uc_w2s_strcpy(w2s_str,MMP_TTS_TEXT(MLM_MMP_KEY_TTS_SLOW_REWIND));
            a_app_tts_play(w2s_str,c_uc_w2s_strlen(w2s_str));
        #endif

            i4_ret = mmp_mc_list_slow_rewind(&t_trick_param);
            if(MMPR_OK != i4_ret && MMPR_IS_SLOW_REWINDED != i4_ret)
            {
                MMP_DBG_ERROR(("mmp_mc_list_slow_rewind() fail. i4_ret = %d.\r\n", i4_ret));
            }
            else
            {
                _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
            }
        }
        break;

        case VIDEO_PLAYER_BTN_EXIT:
        case BTN_RED:
        {
            i4_ret = mmp_be_pause_mmp();
            if(MMPR_OK != i4_ret)
            {
                 MMP_DBG_ERROR(("mmp_be_pause_mmp() fail. i4_ret = %d.\r\n", i4_ret));
            }
            return MMPR_NO_DATA;
        }

        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        {
            e_g_seek_stat = _MMP_VP_SEEK_STAT_SETTING;
            if (MMPR_OK != _mmp_vp_tb_seek_enter(ui4_key_code))
            {
               DBG_LOG_PRINT(("_mmp_vp_tb_seek_enter() returns %d.\n", i4_ret));
            }
            else
            {
                _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
            }

            //c_timer_stop(t_g_video_view.h_timer_viewer);

            return MMPR_NO_DATA;
        }
            break;

        case BTN_MUTE:
        case BTN_VOL_UP:
        case BTN_VOL_DOWN:
        case BTN_CURSOR_DOWN:
        case BTN_CURSOR_UP:
        case BTN_PRG_INFO:
            break;

        default:
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        {
            i4_ret = mmp_mc_key_handler(ui4_key_code,WGL_MSG_KEY_DOWN);
            if(i4_ret == MMPR_NO_DATA)
            {
                return MMPR_NOT_SUPPORT;
            }
            else
            {
                return i4_ret;
            }
        }
#else
        return MMPR_NOT_SUPPORT;
#endif
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_main_frm_proc_fct
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
static INT32 _mmp_vp_main_frm_proc_fct(
                    HANDLE_T                        h_frm_main,
                    UINT32                          ui4_msg,
                    VOID*                           pv_param1,
                    VOID*                           pv_param2
                    )
{
    INT32 i4_ret;
    UINT32 ui4_key_code = (UINT32)pv_param1;

    if (WGL_MSG_KEY_UP == ui4_msg)
    {
        _mmp_vp_key_up_handle(ui4_key_code);
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        menu_blank_oled_scrn_timer_refresh();
         if(menu_custom_is_blank_screen())
        {
            menu_custom_unblank_screen(ui4_key_code);
            DBG_LOG_PRINT(("<mmp> it is under blank screen %s,%d\n\r",__FILE__,__LINE__));
            return MMPR_OK;
        }
        do
        {
            if (MMP_VE_PLAY_STAT_PAUSE == t_g_video_view.e_player_status)
            {
                nav_request_context_switch(a_scrn_blank_act,
                                            NULL,
                                            NULL,
                                            NULL);
            }

            if (_mmp_vp_is_repeated_btn(ui4_key_code))
            {
               DBG_LOG_PRINT(("[Info] Repeat Key = 0x%08x.\n", ui4_key_code));
                return MMPR_OK;
            }

            i4_ret = _mmp_vp_key_code_check(ui4_key_code);
            if (MMPR_OK != i4_ret)
            {
                break;
            }

            i4_ret = _mmp_vp_key_down_handle(ui4_key_code);
            if (MMPR_OK != i4_ret)
            {
                break;
            }

            if (MMP_VE_PLAY_STAT_BLANK == t_g_video_view.e_player_status)
            {
                _mmp_vp_hide_viewer(NULL, NULL, NULL, NULL);
            }
            else if (MMP_VP_VIEWER_HIDE == t_g_video_view.e_viewer_status)
            {
                /* if received key is wide key or 3d key, do not toggle viewer. */
                if ((BTN_ASPECT != ui4_key_code)
                    &&(BTN_3D != ui4_key_code))
                {
                    _mmp_vp_view_toggle_viewer(TRUE);
                }
            }

            if ((MMP_VP_VIEWER_SHOW == t_g_video_view.e_viewer_status) &&
                (_MMP_VP_SEEK_STAT_SETTING != e_g_seek_stat))
            {
                c_timer_stop(t_g_video_view.h_timer_viewer);
                c_timer_start(t_g_video_view.h_timer_viewer,
                             MMP_VP_TIMER_VIERER_HIDE,
                             X_TIMER_FLAG_ONCE,
                             _mmp_vp_timer_nfy_fct,
                             NULL
                             );
            }
        }while(0);
    }
    return c_wgl_default_msg_proc(h_frm_main, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_create_main_frm
 *
 * Description: This function creates the main (root) frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_create_main_frm (HANDLE_T    h_canvas,
                                         HANDLE_T*   ph_frm)
{
    INT32               i4_ret;
    UINT32              ui4_canvas_width;
    UINT32              ui4_canvas_height;
    INT32               i4_osd_offset_x;
    INT32               i4_osd_offset_y;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    GL_COLOR_T          t_color_bk = MMP_VP_GET_CLR_BK();

    /* Get canvas size. */
    i4_ret = c_wgl_get_canvas_size (h_canvas,
                                    & ui4_canvas_width,
                                    & ui4_canvas_height);
    if(WGLR_OK != i4_ret)
    {
         MMP_DBG_ERROR(("c_wgl_get_canvas_size() fail. i4_ret = %d.\r\n", i4_ret));
         return i4_ret;
    }

    /* Calculate OSD offsets. */
    i4_osd_offset_x = (INT32)((ui4_canvas_width  - MMP_VP_RC_MAIN_W) / 2);
    i4_osd_offset_y = (INT32)((ui4_canvas_height - MMP_VP_RC_MAIN_H) / 2);

    SET_RECT_BY_SIZE (& t_rect,
                      MMP_VP_RC_MAIN_X + i4_osd_offset_x,
                      MMP_VP_RC_MAIN_Y + i4_osd_offset_y,
                      MMP_VP_RC_MAIN_W,
                      MMP_VP_RC_MAIN_H);

    /* Create widget. */
    i4_ret = c_wgl_create_widget (h_canvas,
                                  HT_WGL_WIDGET_FRAME,
                                  WGL_CONTENT_FRAME_DEF,
                                  WGL_BORDER_NULL,
                                  & t_rect,
                                  _mmp_vp_main_frm_proc_fct,
                                  0,
                                  (VOID*) WGL_STL_GL_NO_IMG_UI,
                                  0,
                                  ph_frm);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_create_widget() fail. i4_ret = %d.\r\n", i4_ret));

        *ph_frm= NULL_HANDLE;
        return MMPR_FAIL;
    }

    /* Set background color. */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_color_bk;
    t_clr_info.u_color_data.t_standard.t_disable   = t_color_bk;
    t_clr_info.u_color_data.t_standard.t_highlight = t_color_bk;

    i4_ret = c_wgl_do_cmd (*ph_frm,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK (WGL_CLR_BK),
                           WGL_PACK (& t_clr_info));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd(WGL_CMD_GL_SET_COLOR) fail. i4_ret = %d.\r\n", i4_ret));

        i4_ret = c_wgl_destroy_widget(*ph_frm);
        MMP_ASSERT(WGLR_OK == i4_ret);

        *ph_frm= NULL_HANDLE;
        return MMPR_FAIL;
    }

    c_wgl_set_visibility(*ph_frm,WGL_SW_HIDE);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_view_deinit
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static HANDLE_T mmp_fullscreen_show_vf_info;
static VOID _mmp_vp_view_deinit( VIDEO_PLAYER_VIEW_T*      pt_this)
{
    INT32                       i4_ret;

    /* Release Timer */
    if(NULL_HANDLE != t_g_video_view.h_timer_hide_msg)
    {
        i4_ret = c_timer_delete (t_g_video_view.h_timer_hide_msg);
        if(OSR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_timer_delete() fail. i4_ret = %d.\r\n", i4_ret));
        }
        t_g_video_view.h_timer_hide_msg = NULL_HANDLE;
    }

    /* Release Timer */
    if(NULL_HANDLE != t_g_video_view.h_timer_timeout)
    {
        i4_ret = c_timer_delete (t_g_video_view.h_timer_timeout);
        if(OSR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_timer_delete() fail. i4_ret = %d.\r\n", i4_ret));
        }
        t_g_video_view.h_timer_timeout = NULL_HANDLE;
    }

    /* Release Timer */
    if(NULL_HANDLE != t_g_video_view.h_timer_viewer)
    {
        i4_ret = c_timer_delete(t_g_video_view.h_timer_viewer);
        if(OSR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_timer_delete() fail. i4_ret = %d.\r\n", i4_ret));
        }
        t_g_video_view.h_timer_viewer = NULL_HANDLE;
    }

    /* Release Timer */
    if(NULL_HANDLE != t_g_video_view.h_timer_reset_icon)
    {
        i4_ret = c_timer_delete (t_g_video_view.h_timer_reset_icon);
        if(OSR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_timer_delete() fail. i4_ret = %d.\r\n", i4_ret));
        }
        t_g_video_view.h_timer_reset_icon = NULL_HANDLE;
    }

    /* Release Timer */
    if(NULL_HANDLE != t_g_video_view.h_timer_loading)
    {
        i4_ret = c_timer_delete (t_g_video_view.h_timer_loading);
        MMP_DBG_ERROR(("c_timer_delete() fail. i4_ret = %d.\r\n", i4_ret));
        t_g_video_view.h_timer_loading = NULL_HANDLE;
    }

    /* CEC SAC volume text hide timer */
    if(NULL_HANDLE != t_g_video_view.h_timer_cec_sac)
    {
        i4_ret = c_timer_delete (t_g_video_view.h_timer_cec_sac);
        MMPR_LOG_ON_FAIL(i4_ret);
        t_g_video_view.h_timer_cec_sac = NULL_HANDLE;
    }

    /* auto hide timer */
    if(NULL_HANDLE != mmp_fullscreen_show_vf_info)
    {
        i4_ret = c_timer_delete (mmp_fullscreen_show_vf_info);
        MMPR_LOG_ON_FAIL(i4_ret);
        mmp_fullscreen_show_vf_info = NULL_HANDLE;
    }

#ifdef APP_CAPTURE_LOGO_SUPPORT
    if(NULL != pt_this->pv_cap_logo)
    {
        i4_ret = a_cap_destroy(pt_this->pv_cap_logo);
        if (ACAPR_OK != i4_ret)
        {
           DBG_LOG_PRINT(("a_cap_destroy() returns %d.\n", i4_ret));
        }
        pt_this->pv_cap_logo = NULL;
    }
#endif

    if(NULL_HANDLE != pt_this->h_opt_list)
    {
        i4_ret = a_optl_destroy(pt_this->h_opt_list);
        if(OPTLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("a_optl_destroy() fail. i4_ret = %d.\r\n", i4_ret));
        }
        pt_this->h_opt_list = NULL_HANDLE;
    }

    _mmp_vp_ib_deinit();
    _mmp_vp_dp_deinit();
    _mmp_vp_tb_deinit();

    if(NULL_HANDLE != pt_this->h_frm_main)
    {
        i4_ret = c_wgl_destroy_widget(pt_this->h_frm_main);
        if(WGLR_OK != i4_ret)
        {
            MMP_DBG_ERROR(("c_wgl_destroy_widget() fail. i4_ret = %d.\r\n", i4_ret));
        }
        pt_this->h_frm_main = NULL_HANDLE;
    }

    mmp_view_rc_destroy_siderbar_ui();
    MMP_EXEC_WITH_ASSERT(mmp_img_deinit(), MMPR_OK);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_view_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_init(VIDEO_PLAYER_VIEW_T *      pt_this)
{
    INT32                           i4_ret;
#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
    MMP_MC_PLAYER_SETTING_T  t_play_setting;
#endif
    UINT32 ui4_sys_tick = 0;
    UINT16 i = 0;

    /*init repeat key tick*/
    ui4_sys_tick = c_os_get_sys_tick();

    for(i = 0; i < ui2_rpt_keys_num; ++i)
    {
        at_rpt_key_tick[i].ui4_key_code = ui4_rpt_keys[i];
        at_rpt_key_tick[i].ui4_sys_tick = ui4_sys_tick;
    }

    /*get canvas*/
    pt_this->h_canvas = mmp_main_get_canvas();

    /*init image*/
    i4_ret = mmp_img_init();
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    /*create timer for invalid file*/
    i4_ret = c_timer_create(&pt_this->h_timer_hide_msg);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_timer_hide_msg = NULL_HANDLE;
        _mmp_vp_view_deinit(pt_this);
        return MMPR_FAIL;
    }

    /*create timer for updating position*/
    i4_ret = c_timer_create(&pt_this->h_timer_timeout);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_timer_timeout = NULL_HANDLE;
        _mmp_vp_view_deinit(pt_this);
        return MMPR_FAIL;
    }

    /*create timer for hide toolbar/statusbar*/
    i4_ret = c_timer_create(&pt_this->h_timer_viewer);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_timer_viewer = NULL_HANDLE;
        _mmp_vp_view_deinit(pt_this);
        return MMPR_FAIL;
    }

    i4_ret = c_timer_create(&pt_this->h_timer_reset_icon);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_timer_reset_icon = NULL_HANDLE;
        _mmp_vp_view_deinit(pt_this);
        return MMPR_FAIL;
    }

    /*create timer for display loading progress*/
    i4_ret = c_timer_create(&pt_this->h_timer_loading);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_timer_loading = NULL_HANDLE;
        _mmp_vp_view_deinit(pt_this);
        return MMPR_FAIL;
    }

    /*create timer for showing the Dolby/HDR10/HLG icon in full screen mode*/
    i4_ret = c_timer_create(&mmp_fullscreen_show_vf_info);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        mmp_fullscreen_show_vf_info = NULL_HANDLE;
        c_timer_delete (mmp_fullscreen_show_vf_info);
        return MMPR_FAIL;
    }

    /*CEC SAC volume text hide timer*/
    i4_ret = c_timer_create(&pt_this->h_timer_cec_sac);
    if(OSR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_create() failed. i4_ret = %d.\r\n", i4_ret));
        pt_this->h_timer_cec_sac = NULL_HANDLE;
        _mmp_vp_view_deinit(pt_this);
        return MMPR_FAIL;
    }

    /*create main frm*/
    i4_ret = _mmp_vp_view_create_main_frm(pt_this->h_canvas, &pt_this->h_frm_main);
    if(MMPR_OK != i4_ret)
    {
        _mmp_vp_view_deinit(pt_this);
        return i4_ret;
    }
    i4_ret = mmp_view_rc_create_siderbar_ui(pt_this->h_frm_main);
    if(MMPR_OK != i4_ret)
    {
        _mmp_vp_view_deinit(pt_this);
        return MMPR_FAIL;
    }
    c_wgl_set_visibility(pt_this->h_frm_main,WGL_SW_HIDE_RECURSIVE);

    do
    {
        i4_ret = _mmp_vp_tb_init();
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        i4_ret = _mmp_vp_dp_init();
        if (MMPR_OK != i4_ret)
        {
            break;
        }

        i4_ret = _mmp_vp_view_create_txt_loading(pt_this->h_frm_main,&pt_this->h_txt_loading);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

        /*create option list*/
        i4_ret = _mmp_vp_optl_create(pt_this->h_frm_main, &pt_this->h_opt_list);
        if(MMPR_OK != i4_ret)
        {
            break;
        }

#ifdef APP_CAPTURE_LOGO_SUPPORT
        i4_ret = _mmp_vp_logo_create();
        if(MMPR_OK != i4_ret)
        {
            break;
        }
#endif

#ifdef APP_VTRL_INP_SRC_MMP_SUPPORT
        t_play_setting.ui4_mask = MMP_MC_PLYR_SETTING_MSK_DEF_FCS_WGT;
        t_play_setting.h_def_focus_widget = pt_this->h_frm_main;
        i4_ret = mmp_mc_set_player_setting(MMP_MEDIA_TYPE_VIDEO,
                                       &t_play_setting);
        if(MMPR_OK != i4_ret)
        {
            break;
        }
#endif
        return MMPR_OK;
    } while(0);

    _mmp_vp_view_deinit(pt_this);
    return MMPR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_update_file_repeat
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
static INT32 _mmp_vp_view_update_file_repeat(BOOL b_repaint)
{
    return _mmp_vp_tb_icon_repeat(
                    t_g_video_view.e_repeat_mode,
                    (b_repaint?MMP_TB_SYNC_REPAINT:MMP_TB_NON_REPAINT)
                    );
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_toggle_detail_page
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
static INT32 _mmp_vp_view_toggle_detail_page(VOID* param)
{
    BOOL b_repaint = (BOOL)(UINT32)param;

    switch (t_g_video_view.e_detail_page)
    {
        case MMP_VP_DETAIL_PAGE_OFF:
        {
            t_g_video_view.e_detail_page = MMP_VP_DETAIL_PAGE_ON;
            _mmp_vp_dp_update();

            _mmp_vp_dp_show();

            t_g_video_view.e_opt_stat = _MMP_VP_OPTL_LST_STAT_HIDE;
            c_wgl_set_visibility(t_g_video_view.h_opt_list, WGL_SW_HIDE);
            c_wgl_set_focus(t_g_video_view.h_frm_main, WGL_NO_AUTO_REPAINT);
        }
        break;

        case MMP_VP_DETAIL_PAGE_ON:
        {
            t_g_video_view.e_detail_page = MMP_VP_DETAIL_PAGE_OFF;

            _mmp_vp_dp_hide();
        }
        break;
    }

    if(b_repaint)
    {
        c_wgl_repaint(t_g_video_view.h_frm_main,NULL,MMP_VP_SYNC_REPAINT);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_toggle_viewer
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
static INT32 _mmp_vp_view_toggle_viewer(BOOL b_repaint)
{
    if (t_g_video_view.e_viewer_status == MMP_VP_VIEWER_HIDE)
    {
        _mmp_vp_update_pos(NULL, NULL, NULL, NULL);

        _mmp_vp_tb_show();

        switch (t_g_video_view.e_player_status)
        {
            case MMP_VE_PLAY_STAT_PLAY:
            case MMP_VE_PLAY_STAT_FAST_FWD:
            case MMP_VE_PLAY_STAT_FAST_RWD:
            case MMP_VE_PLAY_STAT_SLOW_FWD:
            case MMP_VE_PLAY_STAT_SLOW_RWD:
            {
                c_timer_start(t_g_video_view.h_timer_timeout,
                              MMP_VP_TIMER_TIMEOUT_DELAY,
                              X_TIMER_FLAG_REPEAT,
                              _mmp_vp_timer_nfy_fct,
                              NULL);
            }
                break;

            default:
            {
                c_timer_stop(t_g_video_view.h_timer_timeout);
            }
                break;
        }
    }
    else if(MMP_VP_DETAIL_PAGE_OFF == t_g_video_view.e_detail_page)
    {
        _mmp_vp_view_toggle_detail_page((VOID*)(UINT32)FALSE);

        c_timer_stop(t_g_video_view.h_timer_viewer);
        c_timer_start(t_g_video_view.h_timer_viewer,
                       MMP_VP_TIMER_VIERER_HIDE,
                       X_TIMER_FLAG_ONCE,
                       _mmp_vp_timer_nfy_fct,
                       NULL);
    }
    else
    {

        _mmp_vp_tb_hide();
        _mmp_vp_view_toggle_detail_page((VOID*)(UINT32)FALSE);

        c_timer_stop(t_g_video_view.h_timer_viewer);
        c_timer_stop(t_g_video_view.h_timer_timeout);
    }

    if(b_repaint)
    {
        c_wgl_repaint(t_g_video_view.h_frm_main, NULL, MMP_VP_SYNC_REPAINT);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_update_prog
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
static INT32 _mmp_vp_view_update_prog(UINT8 ui1_load_prog, BOOL b_repaint)
{
    CHAR       s_prog_pct[20] = {0};
    UTF16_T    w2s_prog_pct[20] = {0};
    INT32      i4_ret;

    /* set text */
    c_sprintf(s_prog_pct, "Loading %u%%", ui1_load_prog);
    c_uc_ps_to_w2s(s_prog_pct, w2s_prog_pct,20);

    i4_ret = _mmp_vp_view_set_text(t_g_video_view.h_txt_loading, w2s_prog_pct, FALSE);
    if(MMPR_OK != i4_ret)
    {
         MMP_DBG_ERROR(("_mmp_vp_view_set_text() fail. i4_ret = %d.\r\n", i4_ret));
         return i4_ret;
    }

    if(b_repaint)
    {
        c_wgl_repaint(t_g_video_view.h_txt_loading, NULL, MMP_VP_SYNC_REPAINT);
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_update_codec
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
static INT32 _mmp_vp_view_update_codec(UINT16   ui2_codec,
                                       BOOL     b_repaint)
{
    MMP_IB_MSG_CLASS_T t_msg_class;
    UTF16_T ws_osd_msg[MMP_VP_RC_FILE_MAX_LEN] = { 0 };

    if ((MMP_VE_PLAY_STAT_BLANK == t_g_video_view.e_player_status)&&
        (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat))
    {
        c_uc_w2s_strcpy(ws_osd_msg, (UTF16_T*)L"Stop-Resume");
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
        return _mmp_vp_ib_show(t_msg_class, ws_osd_msg);
    }
    DBG_LOG_PRINT(("[MMP][%s %d] ui2_codec = %d\n",__FUNCTION__,__LINE__,ui2_codec));
    /* set the message to be displayed on osd. */
    if (MMP_VP_AV_NTFY_HAS_NO_CONTENT & ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_NFY_FILE_NO_CONTENT));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if ((MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT & ui2_codec) &&
             (MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT & ui2_codec))
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_TEXT(t_g_video_view.ui2_lang, MLM_MMP_KEY_VP_AUDIO_NOT_SUPPORT));
        c_uc_w2s_strcat(ws_osd_msg, (UTF16_T*)L"\n");
        c_uc_w2s_strcat(ws_osd_msg, MLM_MMP_TEXT(t_g_video_view.ui2_lang, MLM_MMP_KEY_VP_VIDEO_NOT_SUPPORT));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if (MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT & ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_VP_AUDIO_NOT_SUPPORT));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if (MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT & ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_VP_VIDEO_NOT_SUPPORT));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if (MMP_VP_AV_NTFY_RES_NOT_SUPPORT & ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_RES_NOT_SUPPORT));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if (MMP_VP_AV_NTFY_DRM_NOT_SUPPORT & ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_VP_DRM_NOT_SUPPORT));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if (MMP_VP_AV_NTFY_HD_NOT_SUPPORT & ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_VP_HD_NOT_SUPPORT));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if(MMP_VP_AV_NTFY_FILE_NOT_SUPPORT == ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if(MMP_VP_AV_NTFY_FILE_AUDIO_ONLY == ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_VP_AUDIO_ONLY));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else if(MMP_VP_AV_NTFY_FILE_VIDEO_ONLY == ui2_codec)
    {
        c_uc_w2s_strcpy(ws_osd_msg, MLM_MMP_VP_TEXT(MLM_MMP_KEY_VP_VIDEO_ONLY));
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }
    else
    {
        t_msg_class = MMP_IB_MSG_CLASS_INFO;
    }

    /* set the widget to be shown or hidden. */
    if (MMP_VP_AV_NTFY_EMPTY == ui2_codec)
    {
        _mmp_vp_ib_hide();
    }
    else
    {
#ifdef APP_TTS_SUPPORT
        a_app_tts_play(ws_osd_msg,c_uc_w2s_strlen(ws_osd_msg));
#endif
        _mmp_vp_ib_show(t_msg_class, ws_osd_msg);
    }

    /* trigger the timer to end this video. */
    if (MMP_VP_AV_NTFY_HAS_NO_CONTENT & ui2_codec)
    {
        c_timer_start(t_g_video_view.h_timer_hide_msg,
                      MMP_VP_TIMER_HIDE_MSG_DELAY,
                      X_TIMER_FLAG_ONCE,
                      _mmp_vp_timer_nfy_fct,
                      NULL);
        t_g_video_view.b_crt_play_invalid_file = TRUE;
    }
    else if ((MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT & ui2_codec) &&
             (MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT & ui2_codec))
    {
        c_timer_start(t_g_video_view.h_timer_hide_msg,
                      MMP_VP_TIMER_HIDE_MSG_DELAY,
                      X_TIMER_FLAG_ONCE,
                      _mmp_vp_timer_nfy_fct,
                      NULL);
        t_g_video_view.b_crt_play_invalid_file = TRUE;
    }
    else if ((MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT & ui2_codec) ||
             (MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT & ui2_codec) ||
             (MMP_VP_AV_NTFY_HD_NOT_SUPPORT & ui2_codec) ||
             (MMP_VP_AV_NTFY_RES_NOT_SUPPORT & ui2_codec))
    {
        c_timer_start(t_g_video_view.h_timer_hide_msg,
                      MMP_VP_TIMER_HIDE_MSG_DELAY,
                      X_TIMER_FLAG_ONCE,
                      _mmp_vp_timer_nfy_fct,
                      NULL);
        t_g_video_view.b_crt_play_invalid_file = FALSE;
    }
    else if (MMP_VP_AV_NTFY_DRM_NOT_SUPPORT & ui2_codec)
    {
        c_timer_start(t_g_video_view.h_timer_hide_msg,
                      MMP_VP_TIMER_HIDE_MSG_DELAY,
                      X_TIMER_FLAG_ONCE,
                      _mmp_vp_timer_nfy_fct,
                      NULL);
        t_g_video_view.b_crt_play_invalid_file = TRUE;
    }
    else
    {
        c_timer_stop(t_g_video_view.h_timer_hide_msg);
        t_g_video_view.b_crt_play_invalid_file = FALSE;
    }

    return MMPR_OK;
}

#ifndef APP_CAST_TV_MMP
/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_swap_filename
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
static INT32 _mmp_vp_view_swap_filename(BOOL b_repaint)
{
    pt_vdp_inst->e_repaint = (t_g_video_view.e_detail_page == MMP_VP_DETAIL_PAGE_ON)? COM_UI_ASYNC_REPAINT: COM_UI_NON_REPAINT;
    mmp_com_ui_dp_set_text(pt_vdp_inst, MMP_VP_RC_DP_LBL_ID_NEXT, NULL);

    _mmp_vp_tb_icon_file_name(w2s_g_next, MMP_TB_SYNC_REPAINT);
    _mmp_vp_tb_icon_file_idx(TRUE);

    c_uc_w2s_strncpy(w2s_g_file, w2s_g_next, MMP_VP_RC_FILE_MAX_LEN-1);
    c_uc_ps_to_w2s("", w2s_g_next, MMP_VP_RC_FILE_MAX_LEN);
    return MMPR_OK;
}
#endif

static INT32 _mmp_vp_view_ctnt_repeat(
                    BOOL                            b_repaint
                    )
{
    MMP_VE_CTNT_RPT_TYPE_T e_ctnt_rpt_type;
    INT32 i4_ret;

    i4_ret = video_engine_get_ctnt_repeat(
                    t_g_video_view.pt_engine_inst,
                    &e_ctnt_rpt_type
                    );
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    return _mmp_vp_tb_icon_repeat_ab (e_ctnt_rpt_type, MMP_TB_SYNC_REPAINT);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_zoom
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
static INT32 _mmp_vp_view_zoom(BOOL b_repaint)
{
    MMP_VE_VID_INFO_T*      pt_vid_info = &t_g_video_view.t_vid_info;
    INT32                   i4_ret;

    /*update zoom*/
    if(MMP_VE_ZOOM_TYPE_1X < pt_vid_info->t_idx_zoom)
    {
        video_engine_zoom_reset(t_g_video_view.pt_engine_inst);
        pt_vid_info->t_idx_zoom = MMP_VE_ZOOM_TYPE_1X;
    }

    /*judge whether it can zoom*/
    i4_ret = video_engine_get_vid_info(
                    t_g_video_view.pt_engine_inst,
                    pt_vid_info
                    );
    if((MMPR_OK != i4_ret) || (MMP_VE_ZOOM_TYPE_1X > (INT32)pt_vid_info->t_max_zoom))
    {
        MMP_DBG_ERROR(("video_engine_get_vid_info() fail or max_zoom isn't correct. i4_ret = %d, max = %d.\r\n", i4_ret, pt_vid_info->t_max_zoom));

        pt_vid_info->t_max_zoom = MMP_VE_ZOOM_TYPE_1X;
        pt_vid_info->t_idx_zoom = MMP_VE_ZOOM_TYPE_1X;
    }

    _mmp_vp_tb_icon_zoom(
                pt_vid_info->t_idx_zoom,
                MMP_TB_SYNC_REPAINT
                );

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_mts
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
static INT32 _mmp_vp_view_mts(BOOL b_repaint)
{
    INT32                   i4_ret;

    i4_ret = video_engine_get_aud_info(t_g_video_view.pt_engine_inst, &t_g_video_view.t_aud_info);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("video_engine_get_mts_info() fail. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

    _mmp_vp_tb_icon_audio(&t_g_video_view.t_aud_info, MMP_TB_SYNC_REPAINT);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_sub
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
static INT32 _mmp_vp_view_sub(BOOL b_repaint)
{
    INT32                   i4_ret;

    i4_ret = video_engine_get_sub_info(t_g_video_view.pt_engine_inst, &t_g_video_view.t_sub_info);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("video_engine_get_sub_info() fail. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }

    _mmp_vp_tb_icon_sbtl(&t_g_video_view.t_sub_info, MMP_TB_SYNC_REPAINT);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_reset
 *
 * Description:
 *
 * Inputs:  - b_clear_all : TRUE for _mmp_vp_next(); FALSE for _mmp_vp_stop().
 *
 * Outputs: -
 *
 * Returns: MMPR_OK            Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_reset(BOOL b_clear_all, BOOL b_repaint)
{
    MMP_FP_PRESENT_MODE_T t_present_mode = MMP_FP_PRESENT_MODE_FULL;

    /* if current mode is preview, do not reset. */
    mmp_mc_list_get_play_present_mode(&t_present_mode);
    if (MMP_FP_PRESENT_MODE_PREVIEW == t_present_mode)
    {
        return MMPR_OK;
    }

    /* clear scr mode */
    c_memset(t_g_video_view.t_optl_scr_mode,0,MMP_VP_OPTL_SCR_MODE_NUM);

    c_memset(&t_g_video_view.t_program_info,0,sizeof(MMP_VE_PROGRAM_INFO_T));
    t_g_video_view.ui8_position = (UINT64)0;
    t_g_video_view.ui8_duration = (UINT64)0;
    t_g_video_view.e_prog_bar_type = _MMP_VP_PROG_BAR_TYPE_TIME;

    t_g_video_view.ui2_av_ntfy = MMP_VP_AV_NTFY_EMPTY;
    t_g_video_view.t_aud_info.ui2_aud_num = (UINT16)0;
    //t_g_video_view.t_sub_info.ui2_sub_num = (UINT16)0;
    t_g_video_view.t_vid_info.t_max_zoom = MMP_VE_ZOOM_TYPE_1X;

    /* reset toolbar */
    _mmp_vp_tb_reset();

    /* hide message */
    _mmp_vp_ib_hide();

    /* option list */
    t_g_video_view.e_opt_stat = _MMP_VP_OPTL_LST_STAT_HIDE;
    c_wgl_set_visibility(t_g_video_view.h_opt_list, WGL_SW_HIDE);
    c_wgl_set_focus(t_g_video_view.h_frm_main, WGL_NO_AUTO_REPAINT);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_update_vol_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_update_vol_info (BOOL b_repaint, VOID* pv_msg_param)
{
    INT32               i4_ret;
    MMP_VOL_UPD_INFO_T  *pt_vol_inf = NULL;
    UINT16              i2_vol, ui2_mlm_id;
    BOOL                b_cec_sac = FALSE, b_mute = a_tv_get_mute();
    UINT8               ui1_icl_val;
    SIZE_T              z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;

    if (NULL != pv_msg_param)
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

    if (b_cec_sac)
    {
        i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_VOL_BAR_VISBI,
                    (VOID*)(UINT32)FALSE,
                    MMP_TB_NON_REPAINT
                    );
        MMPR_LOG_ON_FAIL(i4_ret);

        if (MMP_VE_PLAY_STAT_BLANK != t_g_video_view.e_player_status)
        {
            if(b_mute)
            {
                i4_ret = mmp_info_bar_hide();
                MMPR_LOG_ON_FAIL(i4_ret);
            }

            i4_ret = mmp_common_ui_toolbar_view_active(
                        pt_vtb_inst,
                        (b_repaint ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT)
                        );
            MMPR_LOG_ON_FAIL(i4_ret);

            if (NULL != pt_vol_inf && (pt_vol_inf->b_volume_up || pt_vol_inf->b_volume_down))
            {
                ui2_mlm_id = pt_vol_inf->b_volume_up ? (UINT16)MLM_MMP_KEY_VOL_AMP_INCREASE : (UINT16)MLM_MMP_KEY_VOL_AMP_DECREASE;
                i4_ret = _mmp_vp_ib_show(
                                MMP_IB_MSG_CLASS_INFO,
                                MLM_MMP_TEXT(t_g_video_view.ui2_lang, ui2_mlm_id)
                                );
                MMPR_LOG_ON_FAIL(i4_ret);

                c_timer_start (t_g_video_view.h_timer_cec_sac,
                               MMP_VP_TIMER_CEC_SAC_VOL,
                               X_TIMER_FLAG_ONCE,
                               _mmp_vp_timer_nfy_fct,
                               NULL);
            }
        }
    }
    else
    {
        i4_ret = mmp_common_ui_toolbar_cmd_do(
                    pt_vtb_inst,
                    MMP_VP_TB_CMD_SET_VOL_BAR_VISBI,
                    (VOID*)(UINT32)(!b_mute),
                    MMP_TB_NON_REPAINT
                    );
        MMPR_LOG_ON_FAIL(i4_ret);

        a_tv_get_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                     (INT16*)&i2_vol);
        _mmp_vp_tb_icon_volumn(i2_vol, MMP_TB_SYNC_REPAINT);
    }

    /* Update mute icon */
    _mmp_vp_tb_icon_mute(b_mute, (MMP_VE_PLAY_STAT_BLANK != t_g_video_view.e_player_status) ? MMP_TB_SYNC_REPAINT : MMP_TB_NON_REPAINT);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_update_status
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
static INT32 _mmp_vp_update_status(BOOL b_repaint)
{
    MMP_VE_PLAY_STAT_T         e_prev_stat;
    MMP_VE_PLAY_STAT_T         e_crnt_stat;

    e_prev_stat = t_g_video_view.e_player_status;
    e_crnt_stat = video_engine_get_state(t_g_video_view.pt_engine_inst);
    t_g_video_view.e_player_status = e_crnt_stat;

    if ((MMP_VE_PLAY_STAT_BLANK == e_prev_stat) ||
        (MMP_VE_PLAY_STAT_BLANK == e_crnt_stat))
    {
        if (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat)
        {
            _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        }
    }

    _mmp_vp_view_ctnt_repeat(TRUE);

    switch (t_g_video_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_PLAY:
        case MMP_VE_PLAY_STAT_FAST_FWD:
        case MMP_VE_PLAY_STAT_FAST_RWD:
        case MMP_VE_PLAY_STAT_SLOW_FWD:
        case MMP_VE_PLAY_STAT_SLOW_RWD:
        {
            c_timer_start(
                    t_g_video_view.h_timer_timeout,
                    MMP_VP_TIMER_TIMEOUT_DELAY,
                    X_TIMER_FLAG_REPEAT,
                    _mmp_vp_timer_nfy_fct,
                    NULL);
        }
        break;

        default:
        {
            c_timer_stop(t_g_video_view.h_timer_timeout);
        }
        break;
    }

    _mmp_vp_tb_icon_play (t_g_video_view.e_player_status, MMP_TB_SYNC_REPAINT);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_hide_viewer
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_hide_viewer(VOID*                       pv_tag1,
                                VOID*                       pv_tag2,
                                VOID*                       pv_tag3,
                                VOID*                       pv_tag4)
{
    if (MMP_VP_STAT_INACTIVE == t_g_video_view.e_vp_stat)
    {
        return; /* timer is out of date */
    }

    c_timer_stop(t_g_video_view.h_timer_timeout);

    t_g_video_view.e_detail_page = MMP_VP_DETAIL_PAGE_OFF;
    t_g_video_view.e_opt_stat = _MMP_VP_OPTL_LST_STAT_HIDE;

    a_optl_set_visibility(t_g_video_view.h_opt_list,FALSE);

    _mmp_vp_tb_hide();
    _mmp_vp_dp_hide();

    if (MMP_VE_DRM_TYPE_NORMAL == t_g_video_view.t_drm_type)
    {
        c_wgl_set_focus(t_g_video_view.h_frm_main, WGL_NO_AUTO_REPAINT);
    }

    c_wgl_repaint(t_g_video_view.h_frm_main, NULL, MMP_VP_SYNC_REPAINT);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_hide_msg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_hide_msg (VOID* pv_param1, VOID* pv_param2,
                              VOID* pv_param3, VOID* pv_param4)
{
    _mmp_vp_ib_hide();
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_handle_invalid_file
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_handle_invalid_file (VOID* pv_param1, VOID* pv_param2,
                                         VOID* pv_param3, VOID* pv_param4)
{
    MMP_FP_SHOW_NFY_COMMON_PARAM_T  t_nfy_data;
    mmp_fp_show_nfy_fct show_nfy_fct = t_g_video_view.pf_fp_show_nfy_fct;
    MMP_FP_SHOW_NFY_ID_T e_nfy_id;

    if (MMP_VP_STAT_INACTIVE == t_g_video_view.e_vp_stat)
    {
        return; /* timer is out of date */
    }

    if(MMP_VE_PLAY_STAT_NEXT == t_g_video_view.e_player_status)
    {
        e_nfy_id = MMP_FP_SHOW_NFY_ID_NEXT_RESULT;
    }
    else
    {
        e_nfy_id = MMP_FP_SHOW_NFY_ID_START_RESULT;
    }

    c_timer_stop(t_g_video_view.h_timer_timeout);

    t_g_video_view.e_player_status = MMP_VE_PLAY_STAT_PLAY;

    if(MMP_VP_DETAIL_PAGE_ON == t_g_video_view.e_detail_page)
    {
        _mmp_vp_dp_update();
    }

    if(_MMP_VP_LAST_OPEN_ELM_RET_NODATA == t_g_video_view.e_last_open_elm_ret)
    {
        _mmp_vp_ib_show(MMP_IB_MSG_CLASS_INFO,
                        MLM_MMP_TEXT(t_g_video_view.ui2_lang,MLM_MMP_KEY_FILE_NOT_FOUND)
                        );
    }
    else if(_MMP_VP_LAST_OPEN_ELM_RET_FAILED == t_g_video_view.e_last_open_elm_ret)
    {
        _mmp_vp_ib_show(MMP_IB_MSG_CLASS_INFO,
                        MLM_MMP_TEXT(t_g_video_view.ui2_lang,MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT)
                        );
    }
    else if(_MMP_VP_LAST_OPEN_ELM_RET_CORRUPT == t_g_video_view.e_last_open_elm_ret)
    {
        _mmp_vp_ib_show(MMP_IB_MSG_CLASS_INFO,
                        MLM_MMP_TEXT(t_g_video_view.ui2_lang,MLM_MMP_KEY_NFY_FILE_IS_CORRUPT)
                        );
    }

    t_nfy_data.b_result = TRUE;
    t_nfy_data.e_crnt_state = MMP_PLAY_STATE_PLAYED;
    show_nfy_fct(t_g_video_view.pv_mmp_tag,t_g_video_view.ui4_mmc_ver,
                 e_nfy_id,(VOID*)&t_nfy_data);

    t_g_video_view.b_crt_play_invalid_file = TRUE;
    c_timer_start (t_g_video_view.h_timer_hide_msg,
                   MMP_VP_TIMER_HIDE_MSG_DELAY,
                   X_TIMER_FLAG_ONCE,
                   _mmp_vp_timer_nfy_fct,
                   NULL);
}


static INT32 _video_player_view_update_play_info(VOID)
{
    INT32      i4_ret = 0;
    CHAR       sz_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    UTF16_T    w2s_info[MMP_AP_INFO_MAX_STR_LEN] = {0};
    WGL_HIMG_TPL_T   h_img = NULL_HANDLE;
    UTF16_T    w2s_str[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
    APPL_SPLAYER_MOVIE_INFO_T tMovieInfo;
    c_memset(&tMovieInfo, 0, sizeof(tMovieInfo));

    i4_ret =mmp_com_ui_vp_update_info_HDR10plus(t_g_video_view.pv_video_info_inst,w2s_str);
    IS_MMPR_OK(i4_ret);
    i4_ret = mmp_com_ui_vp_update_info_dolby_audio(t_g_video_view.pv_video_info_inst,h_img);
    IS_MMPR_OK(i4_ret);
    //i4_ret = mmp_com_ui_vp_update_info_dolby_atmos(t_g_video_view.pv_video_info_inst,h_img);
    //IS_MMPR_OK(i4_ret);
    i4_ret = mmp_com_ui_vp_update_info_dolby_hdr_hlg_vision(t_g_video_view.pv_video_info_inst,h_img);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret =  video_engine_get_movie_info(&tMovieInfo);
    DBG_LOG_PRINT(("[%s %d]tMovieInfo.u32MovieWidth == %d\n",__FUNCTION__,__LINE__,tMovieInfo.u32MovieWidth));
    DBG_LOG_PRINT(("[%s %d]tMovieInfo.u32MovieHeight == %d\n",__FUNCTION__,__LINE__,tMovieInfo.u32MovieHeight));
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
    else
    {
        /*resloution*/
        c_memset(sz_info, 0, sizeof(sz_info));
        c_memset(w2s_info, 0,  sizeof(w2s_info));
        c_sprintf(sz_info,
                  "%d x %d",
                  (tMovieInfo.u32MovieWidth),
                  (tMovieInfo.u32MovieHeight));

        c_uc_ps_to_w2s(sz_info, w2s_info, MMP_VP_INFO_MAX_STR_LEN);
        i4_ret = mmp_com_ui_fp_set_focus_info( t_g_video_view.pv_video_info_inst,
                                      MMP_VP_FOCUS_INFO_ID_RESOLUTION,
                                      MMP_COM_UI_FP_DATA_W2S,
                                      (VOID*)w2s_info,
                                      FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);

        /*audio format*/
        c_uc_ps_to_w2s(tMovieInfo.audioCodec, w2s_info, MMP_VP_INFO_MAX_STR_LEN);
        i4_ret = mmp_com_ui_fp_set_focus_info( t_g_video_view.pv_video_info_inst,
                                      MMP_VP_FOCUS_INFO_ID_AUDIO_FMT,
                                      MMP_COM_UI_FP_DATA_W2S,
                                      (VOID*)w2s_info,
                                      FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
        i4_ret = mmp_com_ui_focus_info_frm_active(t_g_video_view.pv_video_info_inst,
                                         MMP_COM_FP_TYPE_VP,
                                         TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
        /* dolby Vision*/
        {
            SCC_DOVI_INFO_T  t_dolby_vision;
            HANDLE_T         h_scc_comp = NULL_HANDLE;
            CHAR             s_disp_name[ACFG_MAX_DISP_NAME+1];

            c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));

            /* Get SCC handle by display name. */
            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            MMPR_LOG_ON_FAIL(i4_ret == APP_CFGR_OK ? MMPR_OK : i4_ret);

            h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                              h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

            i4_ret = c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision);
            MMPR_LOG_ON_FAIL(i4_ret == SMR_OK ? MMPR_OK : i4_ret);

            if ( t_dolby_vision.ui1_is_doviHDR != FALSE)
            {
                h_img = h_g_mmp_dolbyVision_Vert_white_Banner;
            }
            else
            {
                h_img = NULL_HANDLE;
            }
            i4_ret = mmp_com_ui_vp_update_info_dolby_hdr_hlg_vision(t_g_video_view.pv_video_info_inst,h_img);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
        /* dolby Audio*/
        {
            ASH_AUDIO_INFO_T t_audio_info;

            SCC_AUD_IEC_TYPE_T        e_iec_type;
            i4_ret = a_mmp_get_scc_audio_type_out(&e_iec_type);
            MMPR_LOG_ON_FAIL(i4_ret);
#ifdef NEVER
            i4_ret = _video_player_get_audio_fmt_info(t_g_video_view.pt_engine_inst, &t_audio_info);
            IS_MMPR_OK(i4_ret);
            if (t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_AC3)
            {
                h_img = h_g_mmp_dolbyAudio_Vert_white;
                i4_ret = mmp_com_ui_vp_update_info_dolby_audio(t_g_video_view.pv_video_info_inst,h_img);
                IS_MMPR_OK(i4_ret);
                i4_ret = mmp_com_ui_vp_update_info_dolby_atmos(t_g_video_view.pv_video_info_inst,NULL_HANDLE);
                IS_MMPR_OK(i4_ret);
            }
            else if (t_audio_info.e_aud_fmt == ASH_AUDIO_FMT_E_AC3)
            {
                if (e_iec_type == SCC_AUD_IEC_CFG_DDP_ATMOS)
                {
                    h_img = h_g_mmp_dolbyAtmos_Vert_white;
                    i4_ret = mmp_com_ui_vp_update_info_dolby_audio(t_g_video_view.pv_video_info_inst,NULL_HANDLE);
                    IS_MMPR_OK(i4_ret);
                    i4_ret = mmp_com_ui_vp_update_info_dolby_atmos(t_g_video_view.pv_video_info_inst,h_img);
                    IS_MMPR_OK(i4_ret);
                }
                else
                {
                    h_img = h_g_mmp_dolbyAudio_Vert_white;
                    i4_ret = mmp_com_ui_vp_update_info_dolby_audio(t_g_video_view.pv_video_info_inst,h_img);
                    IS_MMPR_OK(i4_ret);
                    i4_ret = mmp_com_ui_vp_update_info_dolby_atmos(t_g_video_view.pv_video_info_inst,NULL_HANDLE);
                    IS_MMPR_OK(i4_ret);
                }
            }
            else
            {
                h_img = NULL_HANDLE;
                i4_ret = mmp_com_ui_vp_update_info_dolby_audio(t_g_video_view.pv_video_info_inst,h_img);
                IS_MMPR_OK(i4_ret);
                i4_ret = mmp_com_ui_vp_update_info_dolby_atmos(t_g_video_view.pv_video_info_inst,h_img);
                IS_MMPR_OK(i4_ret);
            }
#else
        if((tMovieInfo.eAudioCodec == E_SPLAYER_AUDIO_CODEC_TYPE_AC4) ||
           (tMovieInfo.eAudioCodec == E_SPLAYER_AUDIO_CODEC_TYPE_AC3) ||
           (tMovieInfo.eAudioCodec == E_SPLAYER_AUDIO_CODEC_TYPE_AC3P))
        {
            h_img = h_g_mmp_dolbyAudio_Vert_white;
            i4_ret = mmp_com_ui_vp_update_info_dolby_audio(t_g_video_view.pv_video_info_inst,h_img);
            MMPR_LOG_ON_FAIL(i4_ret);
        }
#endif
        }
        /* HDR10_HLG Vision */
        {
            SCC_VID_HDR_TYPE_T    t_hdr_type;
            HANDLE_T              h_scc_comp1 = NULL_HANDLE;
            CHAR                  s_disp_name1[ACFG_MAX_DISP_NAME+1];

            /* Get SCC handle by display name. */
            i4_ret = a_cfg_av_get_disp_name(s_disp_name1, sizeof(s_disp_name1));
            MMPR_LOG_ON_FAIL(i4_ret == APP_CFGR_OK ? MMPR_OK : i4_ret);

            h_scc_comp1 = (c_strcmp(s_disp_name1, SN_PRES_MAIN_DISPLAY) == 0 ?
                          h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);

            i4_ret = c_scc_vid_get_hdr_type(h_scc_comp1, &t_hdr_type);
            MMPR_LOG_ON_FAIL(i4_ret == SMR_OK ? MMPR_OK : i4_ret);

            if(t_hdr_type == SCC_VID_PQ_HLG)
            {
            	h_img = h_g_mmp_HLG_Vert_white;
				i4_ret = mmp_com_ui_vp_update_info_dolby_hdr_hlg_vision(t_g_video_view.pv_video_info_inst,h_img);
            }
            else if(t_hdr_type == SCC_VID_PQ_HDR10)
            {
            	h_img = h_g_mmp_HDR10_Vert_white;
				i4_ret = mmp_com_ui_vp_update_info_dolby_hdr_hlg_vision(t_g_video_view.pv_video_info_inst,h_img);
            }
            else if(t_hdr_type == SCC_VID_PQ_HDR10PLUS)
            {
                c_uc_w2s_strcpy(w2s_str, (UTF16_T*)L"HDR10+");
				i4_ret = mmp_com_ui_vp_update_info_HDR10plus(t_g_video_view.pv_video_info_inst,w2s_str);
            }
            IS_MMPR_OK(i4_ret);
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_update_pos
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_update_pos(VOID*                           pv_tag1,
                               VOID*                           pv_tag2,
                               VOID*                           pv_tag3,
                               VOID*                           pv_tag4)
{
    INT32   i4_ret = MMPR_OK;
    MMP_DBG_INFO(("[MMP][%s %d]\n",__FUNCTION__,__LINE__));
    i4_ret = video_engine_get_duration(t_g_video_view.pt_engine_inst,
                                       MMP_VE_DUR_TYPE_TIME,
                                       &t_g_video_view.ui8_duration);

    if(MMPR_OK != i4_ret || 0 == t_g_video_view.ui8_duration)
    {
        i4_ret = video_engine_get_duration(t_g_video_view.pt_engine_inst,
                                           MMP_VE_DUR_TYPE_BYTE,
                                           &t_g_video_view.ui8_duration);
        if (MMPR_OK != i4_ret)
        {
            t_g_video_view.ui8_duration = 0;
        }

        t_g_video_view.e_prog_bar_type = _MMP_VP_PROG_BAR_TYPE_FILE;
        MMP_DBG_INFO(("video_engine_get_file_length() : duration = %lu\n", (UINT32)t_g_video_view.ui8_duration));
    }
    else
    {
        t_g_video_view.e_prog_bar_type = _MMP_VP_PROG_BAR_TYPE_TIME;
        MMP_DBG_INFO(("video_engine_get_duration() : duration = %lu\n", (UINT32)t_g_video_view.ui8_duration));
    }

    //ui8_priv_position = t_g_video_view.ui8_position;

    if(_MMP_VP_PROG_BAR_TYPE_TIME == t_g_video_view.e_prog_bar_type)
    {
        i4_ret = video_engine_get_position(
                              t_g_video_view.pt_engine_inst,
                              MMP_VE_POS_TYPE_TIME,
                              &t_g_video_view.ui8_position
                              );
        if (MMPR_OK != i4_ret)
        {
           DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d,ui8_position=%ld\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        i4_ret, t_g_video_view.ui8_position));
        }

        MMP_DBG_INFO(("video_engine_get_position() = %ld : position = %u\n", i4_ret, t_g_video_view.ui8_position));
    }
    else
    {
        i4_ret = video_engine_get_position(
                              t_g_video_view.pt_engine_inst,
                              MMP_VE_POS_TYPE_BYTE,
                              &t_g_video_view.ui8_position
                              );
        if (MMPR_OK != i4_ret)
        {
           MMP_DBG_INFO(("\n%s,%s,%d,i4_ret=%d,ui8_position=%ld\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        i4_ret, t_g_video_view.ui8_position));
        }

        MMP_DBG_INFO(("video_engine_get_file_offset() = %ld : position = %u\n", i4_ret, t_g_video_view.ui8_position));
    }

    _mmp_vp_view_update_pos(t_g_video_view.ui8_position, TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_view_update_pos
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_update_pos(UINT64  ui8_day_sec, BOOL b_repaint)
{
    INT32       i4_ret = MMPR_OK;
    UINT32      ui4_pecentage = 0;
    MMP_FP_PRESENT_MODE_T e_present_mode = MMP_FP_PRESENT_MODE_FULL;

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if (a_mmp_dmr_is_active())
    {
        return MMPR_OK; /* when DMR is active, do not need to show ui. */
    }
#endif

    i4_ret = mmp_mc_list_get_play_present_mode(&e_present_mode);
    if ((MMPR_OK == i4_ret) && (MMP_FP_PRESENT_MODE_FULL == e_present_mode))
    {
        _mmp_vp_tb_icon_time(t_g_video_view.ui8_position, MMP_TB_ASYNC_REPAINT);
        return MMPR_OK;
    }

    /* set Pb position */
    if (t_g_video_view.ui8_duration == 0 )
    {
        ui4_pecentage = 0;
    }
    else
    {
        ui4_pecentage = (UINT32)(t_g_video_view.ui8_position*100 / t_g_video_view.ui8_duration);
        ui4_pecentage = ((t_g_video_view.ui8_position * 100) % t_g_video_view.ui8_duration > 0) ?
        ui4_pecentage+1 : ui4_pecentage;
    }

    if (NULL == t_g_video_view.pv_video_info_inst)
    {
        DBG_LOG_PRINT(("\n%s,%d\n", __FUNCTION__, __LINE__));
        return MMPR_FAIL;
    }

    MMP_DBG_INFO(("<mmp> update pos:%s,%d,tage:%d,pos:%d,pos:%d\n\r",__FILE__,__LINE__,
                ui4_pecentage,t_g_video_view.ui8_position,t_g_video_view.ui8_duration - t_g_video_view.ui8_position,b_repaint));

#ifndef APP_CAST_TV_MMP_FG
    i4_ret = mmp_com_ui_vp_set_play_info(t_g_video_view.pv_video_info_inst,
                                         MMP_VP_CUR_PLAY_INFO_PG_POS,
                                         (VOID*)(UINT32)(ui4_pecentage),
                                         t_g_video_view.e_prog_bar_type,
                                         FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_vp_set_play_info(t_g_video_view.pv_video_info_inst,
                                         MMP_VP_CUR_PLAY_INFO_ELAPSE_TIME,
                                         (VOID*)(UINT32)(t_g_video_view.ui8_position),
                                         t_g_video_view.e_prog_bar_type,
                                         FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_vp_set_play_info(t_g_video_view.pv_video_info_inst,
                                         MMP_VP_CUR_PLAY_INFO_REMAIN_TIME,
                                         (VOID*)(UINT32)(t_g_video_view.ui8_duration - t_g_video_view.ui8_position),
                                         t_g_video_view.e_prog_bar_type,
                                         FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_vp_info_hdlr_frm_repaint(t_g_video_view.pv_video_info_inst,
                                                 b_repaint);
    MMPR_LOG_ON_FAIL(i4_ret);
#else
    /* fix DTV00863818 only repaint video progress bar ,not repaint the frm */
    i4_ret = mmp_com_ui_vp_set_play_info(t_g_video_view.pv_video_info_inst,
                                         MMP_VP_CUR_PLAY_INFO_PG_POS,
                                         (VOID*)(UINT32)(ui4_pecentage),
                                         t_g_video_view.e_prog_bar_type,
                                         b_repaint);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_vp_set_play_info(t_g_video_view.pv_video_info_inst,
                                         MMP_VP_CUR_PLAY_INFO_ELAPSE_TIME,
                                         (VOID*)(UINT32)(t_g_video_view.ui8_position),
                                         t_g_video_view.e_prog_bar_type,
                                         b_repaint);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_vp_set_play_info(t_g_video_view.pv_video_info_inst,
                                         MMP_VP_CUR_PLAY_INFO_REMAIN_TIME,
                                         (VOID*)(UINT32)(t_g_video_view.ui8_duration - t_g_video_view.ui8_position),
                                         t_g_video_view.e_prog_bar_type,
                                         b_repaint);
    MMPR_LOG_ON_FAIL(i4_ret);
#endif

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_update_loading
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_update_loading(VOID*                       pv_tag1,
                                   VOID*                       pv_tag2,
                                   VOID*                       pv_tag3,
                                   VOID*                       pv_tag4)
{
    UINT8 ui1_load_prog = 0;
    INT32 i4_ret;

    if (MMP_VP_STAT_INACTIVE == t_g_video_view.e_vp_stat)
    {
        return;
    }

    i4_ret = video_engine_get_progress(t_g_video_view.pt_engine_inst,&ui1_load_prog);
    if(MMPR_OK != i4_ret)
    {
        return ;
    }

    _mmp_vp_view_update_prog(ui1_load_prog,TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_hide_cec_sac_vol_txt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_hide_cec_sac_vol_txt(VOID* pv_tag1,
                                         VOID* pv_tag2,
                                         VOID* pv_tag3,
                                         VOID* pv_tag4)
{
    INT32 i4_ret;

    if (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat)
    {
        i4_ret = mmp_info_bar_hide();
        if (MMPR_OK != i4_ret)
        {
           DBG_LOG_PRINT(("mmp_info_bar_hide() returns %d.\n", i4_ret));
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_reset_icon
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_reset_icon(VOID*                       pv_tag1,
                               VOID*                       pv_tag2,
                               VOID*                       pv_tag3,
                               VOID*                       pv_tag4)
{
    if (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat)
    {
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_timer_nfy_fct
 *
 * Description: This callback function is called when timers expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _mmp_vp_timer_nfy_fct (HANDLE_T h_timer, VOID* pv_tag)
{
    if (h_timer == t_g_video_view.h_timer_hide_msg)
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_vp_hide_msg,
                                    &h_timer, NULL, NULL, NULL);
    }
    else if (h_timer == t_g_video_view.h_timer_timeout)
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_vp_update_pos,
                                    &h_timer, NULL, NULL, NULL);
    }
    else if (h_timer == t_g_video_view.h_timer_viewer)
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_vp_hide_viewer,
                                    &h_timer, NULL, NULL, NULL);
    }
    else if (h_timer == t_g_video_view.h_timer_reset_icon)
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_vp_reset_icon,
                                    &h_timer, NULL, NULL, NULL);
    }
    else if (h_timer == t_g_video_view.h_timer_loading)
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_vp_update_loading,
                                    &h_timer, NULL, NULL, NULL);
    }
    else if (h_timer == t_g_video_view.h_timer_cec_sac)
    {
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_ONCE,
                                    _mmp_vp_hide_cec_sac_vol_txt,
                                    &h_timer, NULL, NULL, NULL);
    }
}

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
static VOID _mmp_vp_nfy_for_dmr(MMP_VE_NFY_CODE_T e_code)
{
    E_PLAYER_NFY_CODE e_dmr_code;

    if (FALSE == a_mmp_dmr_is_active())
    {
        return;
    }

    switch (e_code)
    {
        case MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_ONLY_SVC:
            e_dmr_code = PLAYER_NFYCODE_AUDIO_ONLY;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_ONLY_SVC:
            e_dmr_code = PLAYER_NFYCODE_VIDEO_ONLY;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_VIDEO_SVC:
            e_dmr_code = PLAYER_NFYCODE_AV_BOTH;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_NOT_SUPPORT:
            e_dmr_code = PLAYER_NFYCODE_AUDIO_NOT_SUPPORT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_NOT_SUPPORT:
            e_dmr_code = PLAYER_NFYCODE_VIDEO_NOT_SUPPORT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_FMT_UPDATE:
            e_dmr_code = PLAYER_NFYCODE_AUDIO_PLAYED;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_FMT_UPDATE:
            e_dmr_code = PLAYER_NFYCODE_VIDEO_PLAYED;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_HD_NOT_SUPPORT:
            e_dmr_code = PLAYER_NFYCODE_HD_NOT_SUPPORT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_DRM_NOT_SUPPORT:
            e_dmr_code = PLAYER_NFYCODE_DRM_NOT_SUPPORT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_HAS_NO_CONTENT:
            e_dmr_code = PLAYER_NFYCODE_NO_CONTENT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_RESOLUTION_NOT_SUPPORT:
            e_dmr_code = PLAYER_NFYCODE_RESOLUTION_NOT_SUPPORT;
            break;

        case MMP_VE_NFY_CODE_MEDIA_PLAY_FRAMERATE_NOT_SUPPORT:
            e_dmr_code = PLAYER_NFYCODE_FRAMERATE_NOT_SUPPORT;
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
                PLAYER_MEDIATYPE_VIDEO,
                e_dmr_code
                );
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_engine_nfy_fct
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
#include "res/mmp/listmode/mmp_listmode_rc.h"
#ifdef MMP_GUI_AUTHORING
#include "res/mmp/gen/mmp_lm_custom_layout.h"
#include "res/mmp/gen/mmp_audio_control_layout.h"
#include "res/mmp/gen/mmp_video_control_layout.h"
#endif

extern INT32 mmp_listmode_play_next();
static VOID _mmp_vp_play_next()
{
    _mmp_vp_update_status(TRUE);
   MMPR_LOG_ON_FAIL( mmp_listmode_play_next());
}

static VOID _mmp_vp_update_play_status()
{
    if(MMPR_OK == mmp_mc_list_get_idx(MMP_GROUND_MODE_FORE,MMP_PL_IDX_TYPE_CRNT_PLAY,&t_g_video_view.ui4_cur_file_idx))
    {
        mmp_lm_update_file_status(t_g_video_view.ui4_cur_file_idx);
    }
}

static VOID _mmp_vp_engine_nfy_fct(MMP_VE_NFY_CODE_T               e_code,
                                         VOID*                           pv_param)
{
    INT32          i4_ret;
    UINT32         ui4_item_num = 0;
    UINT32         ui4_dir_num  = 0;
    UINT32         ui4_file_num = 0;

    if (NULL == t_g_video_view.pf_fp_show_nfy_fct)
    {
        return;
    }

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    _mmp_vp_nfy_for_dmr(e_code);
#endif

    if (MMP_VE_NFY_CODE_MEDIA_OPEN_END == e_code)
    {
        t_g_video_view.e_last_open_elm_ret = _MMP_VP_LAST_OPEN_ELM_RET_NORMAL;
        t_g_video_view.ui2_av_ntfy = MMP_VP_AV_NTFY_EMPTY;
#if 0
        a_banner_show_hdr_info(FALSE);
#else
        a_mmp_show_hdr_info(FALSE);
#endif

        _mmp_vp_play();
        return;
    }
    DBG_LOG_PRINT(("[MMP][%s %d] e_code = %d\n",__FUNCTION__,__LINE__,e_code));
    if (MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_NOT_SUPPORT == e_code)
    {
        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        t_g_video_view.ui2_av_ntfy &= MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT;
        return;
    }
    else if(MMP_VE_NFY_CODE_MEDIA_OPEN_ERR == e_code )
    {
        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_FILE_NOT_SUPPORT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        _mmp_vp_play_next();
        return;
    }
    else if(MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_NOT_SUPPORT == e_code)
    {
    #ifdef APP_CAST_TV_MMP
        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_EMPTY;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        i4_ret = mmp_mc_list_next(MMP_GROUND_MODE_FORE);
        return;
    #endif

        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);

        if(_MMP_VP_OPTL_LST_STAT_SHOW == t_g_video_view.e_opt_stat)
        {
            UINT16 ui2_main_hlt_index = 0;
            UINT16 ui2_sub_hlt_index = 0;

            i4_ret = a_optl_get_hlt_index(
                              t_g_video_view.h_opt_list,
                              &ui2_main_hlt_index,
                              &ui2_sub_hlt_index
                              );
            if(OPTLR_OK != i4_ret)
            {
                return;
            }

            i4_ret = _mmp_vp_optl_set_item();
            if(MMPR_OK != i4_ret)
            {
                return;
            }

            a_optl_set_hlt_index(t_g_video_view.h_opt_list,ui2_main_hlt_index,0);
            a_optl_repaint(t_g_video_view.h_opt_list);
        }
        //_mmp_vp_play_next();
        i4_ret = mmp_be_get_item_num(MMP_BE_FF_IDX_CRT,
                                    &ui4_dir_num,
                                    &ui4_file_num);
        MMPR_LOG_ON_FAIL(i4_ret);
        ui4_item_num = ui4_dir_num + ui4_file_num;
        if(ui4_item_num > 1)
        {
            DBG_LOG_PRINT(("[%s %d]ui4_item_num == %d\n",__FUNCTION__,__LINE__,ui4_item_num));
            DBG_LOG_PRINT(("[%s %d]ui4_g_play_idx == %d\n",__FUNCTION__,__LINE__,ui4_g_play_idx));
            if(ui4_item_num == ui4_g_play_idx + 1)
            {
                i4_ret = _mmp_vp_close();
                if(MMPR_IS_CLOSED != i4_ret)
                    DBG_LOG_PRINT(("[%s %d]close failed\n",__FUNCTION__,__LINE__));
                return;
            }
            t_g_video_view.ui2_av_ntfy &= MMP_VP_AV_NTFY_EMPTY;
            _mmp_vp_play_next();
        }
        return;
    }
    else if(MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_ONLY_SVC == e_code)
    {
    #ifdef APP_CAST_TV_MMP
        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_EMPTY;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        mmp_mc_list_next(MMP_GROUND_MODE_FORE);
        return;
    #endif
        t_g_video_view.ui2_av_ntfy &= ~MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT;
        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_FILE_AUDIO_ONLY;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        return;
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_ONLY_SVC == e_code)
    {
        t_g_video_view.ui2_av_ntfy &= ~MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT;
        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_FILE_VIDEO_ONLY;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        return;
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_VIDEO_SVC == e_code)
    {
        t_g_video_view.ui2_av_ntfy &= ~MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT;
        t_g_video_view.ui2_av_ntfy &= ~MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        return;
    }
    else if(MMP_VE_NFY_CODE_MEDIA_PLAY_NO_AUDIO_VIDEO_SVC == e_code)
    {
        UINT32 index = t_g_video_view.t_program_info.ui1_cur_idx;
        while(index<t_g_video_view.t_program_info.ui1_program_num)
        {
            index++;
            i4_ret = _mmp_vp_optl_toggle_program((void*)index);
            if(MMPR_OK == i4_ret)
            {
                t_g_video_view.ui2_av_ntfy = MMP_VP_AV_NTFY_EMPTY;
                break;
            }
        }
        if(index >= t_g_video_view.t_program_info.ui1_program_num)
        {
            t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_AUDIO_NOT_SUPPORT;
            t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_VIDEO_NOT_SUPPORT;
            _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        }
        return;
    }
    else if(MMP_VE_NFY_CODE_MEDIA_PLAY_VIDEO_FMT_UPDATE == e_code ||
            MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_FMT_UPDATE == e_code)
    {
       if(MMP_VE_NFY_CODE_MEDIA_PLAY_AUDIO_FMT_UPDATE == e_code)
       {
           _mmp_vp_view_mts(TRUE);
       }
       else
       {
       #ifdef DIVX_PLUS_CER
            MMP_FP_PRESENT_MODE_T t_present_mode;

            i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
            if (MMPR_OK == i4_ret &&
                MMP_FP_PRESENT_MODE_FULL == t_present_mode)
            {
                video_engine_square_pixel(t_g_video_view.pt_engine_inst);
            }
       #endif
             _mmp_vp_view_zoom(TRUE);
            _mmp_vp_update_play_status();
       }

        MMP_FP_INFO_HDLR_INIT_PARAM_T   t_param;
        GL_RECT_T                       t_rect = {0};
        HANDLE_T                        h_video_info = NULL_HANDLE;

        SET_RECT_BY_SIZE (&t_rect,
                          LM_FILE_VIDEO_INFO_HANDLE_X,
                          LM_FILE_VIDEO_INFO_HANDLE_Y,
                          LM_FILE_VIDEO_INFO_HANDLE_W,
                          LM_FILE_VIDEO_INFO_HANDLE_H);
        h_video_info = mmp_lm_custom_get_wgt_hdl(WID_MMP_LM_CUSTOM_FRM_LM_VIDEO_INFO);
        c_memset (&t_param, 0, sizeof (MMP_FP_INFO_HDLR_INIT_PARAM_T));
        t_param.e_ui_type = MMP_FP_INFO_HDLR_UI_TYPE_LM_FOCUS;
        t_param.e_media_type = MMP_MEDIA_TYPE_VIDEO;
        t_param.h_parent = h_video_info;
        t_param.pt_rect = &t_rect;
        MMPR_LOG_ON_FAIL(mmp_mc_browse_display_play_item_info(&t_param));
        return;
    }
    else if(MMP_VE_NFY_CODE_MEDIA_PLAY_PROGRAM_INFO_READY == e_code)
    {
        video_engine_get_program_info(t_g_video_view.pt_engine_inst, &t_g_video_view.t_program_info);
        if(t_g_video_view.t_program_info.ui1_program_num > MAX_PROGRAM_NUM)
        {
            t_g_video_view.t_program_info.ui1_program_num = MAX_PROGRAM_NUM;
        }
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_HD_NOT_SUPPORT == e_code)
    {
#ifdef _MMP_VP_DISP_LOAD_PROGRESS
        _mmp_vp_view_update_prog (100, TRUE);
        c_thread_delay(200);
        c_timer_stop (t_g_video_view.h_timer_loading);
        c_wgl_show (t_g_video_view.h_txt_loading, WGL_SW_HIDE);
#endif

        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_HD_NOT_SUPPORT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        _mmp_vp_play_next();
        return;
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_DRM_NOT_SUPPORT == e_code)
    {
#ifdef _MMP_VP_DISP_LOAD_PROGRESS
        _mmp_vp_view_update_prog (100, TRUE);
        c_thread_delay(200);
        c_timer_stop (t_g_video_view.h_timer_loading);
        c_wgl_show (t_g_video_view.h_txt_loading, WGL_SW_HIDE);
#endif

        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_DRM_NOT_SUPPORT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        _mmp_vp_play_next();
        return;
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_RESOLUTION_NOT_SUPPORT == e_code)
    {

    #ifdef APP_CAST_TV_MMP
        MMP_DBG_INFO(("%s,%d,%d\n\r",__FILE__,__LINE__,t_g_video_view.b_is_next_preload_end));

        if(t_g_video_view.b_is_next_preload_end)
        {
            t_g_video_view.b_is_next_preload_end = FALSE;
            t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_EMPTY;
            _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
            mmp_mc_list_next(MMP_GROUND_MODE_FORE);
            return;
        }
        t_g_video_view.b_is_res_not_support = TRUE;
        return;
    #endif

    //#ifdef APP_MMP_NO_VIDEO_AUDIO_SUPPORT
        _mmp_vp_stop();
        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_RES_NOT_SUPPORT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        return;
    //#endif

#ifdef _MMP_VP_DISP_LOAD_PROGRESS
        _mmp_vp_view_update_prog (100, TRUE);
        c_thread_delay(200);
        c_timer_stop (t_g_video_view.h_timer_loading);
        c_wgl_show (t_g_video_view.h_txt_loading, WGL_SW_HIDE);
#endif

        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_RES_NOT_SUPPORT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        _mmp_vp_play_next();
        return;
    }
#ifdef APP_CAST_TV_MMP
    else if(MMP_VE_NFY_CODE_MEDIA_NEXT_OPEN_END == e_code)
    {
        MMP_DBG_INFO(("%s,%d,%d\n\r",__FILE__,__LINE__,t_g_video_view.b_is_res_not_support));

        if(t_g_video_view.b_is_res_not_support)
        {
            t_g_video_view.b_is_res_not_support = FALSE;
            t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_EMPTY;
            _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
            mmp_mc_list_next(MMP_GROUND_MODE_FORE);
            return;
        }
        t_g_video_view.b_is_next_preload_end = TRUE;
        return ;
    }
#endif

    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_HAS_NO_CONTENT == e_code)
    {
        t_g_video_view.ui2_av_ntfy |= MMP_VP_AV_NTFY_HAS_NO_CONTENT;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        _mmp_vp_play_next();
        return;
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL == e_code)
    {
    #ifdef APP_CAST_TV_MMP
        t_g_video_view.b_is_next_preload_end = FALSE;
    #endif
        MMP_FP_SHOW_NFY_COMMON_PARAM_T t_nfy_data;
        MMP_VE_PLAY_STAT_T t_prev_stat = t_g_video_view.e_player_status;

        t_nfy_data.b_result = TRUE;
        t_nfy_data.e_crnt_state = MMP_PLAY_STATE_PLAYED;

        _mmp_vp_update_status(TRUE);

        _mmp_vp_view_mts(TRUE);
        _mmp_vp_view_sub(TRUE);

        /* Update Play info */
        t_g_video_view.ui2_av_ntfy &= MMP_VP_AV_NTFY_EMPTY;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        MMPR_LOG_ON_FAIL( _video_player_view_update_play_info());

#ifdef _MMP_VP_DISP_LOAD_PROGRESS
        _mmp_vp_view_update_prog (100, TRUE);
        c_thread_delay(200);
        c_timer_stop (t_g_video_view.h_timer_loading);
        c_wgl_show (t_g_video_view.h_txt_loading, WGL_SW_HIDE);
#endif

        switch(t_prev_stat)
        {
            case MMP_VE_PLAY_STAT_OPEN:
            case MMP_VE_PLAY_STAT_STOP:
            {
                t_g_video_view.pf_fp_show_nfy_fct(
                        t_g_video_view.pv_mmp_tag,
                        t_g_video_view.ui4_mmc_ver,
                        MMP_FP_SHOW_NFY_ID_START_RESULT,
                        (VOID*)&t_nfy_data
                        );
            }
            break;

            case MMP_VE_PLAY_STAT_NEXT:
            {
                t_g_video_view.pf_fp_show_nfy_fct(
                        t_g_video_view.pv_mmp_tag,
                        t_g_video_view.ui4_mmc_ver,
                        MMP_FP_SHOW_NFY_ID_NEXT_RESULT,
                        (VOID*)&t_nfy_data
                        );
            }
            break;

            case MMP_VE_PLAY_STAT_FAST_RWD:
            {
                /* For changing MMC's state to PLAY when FR to begining and replay */
                i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE,MMP_PLAY_IDX_CURRENT);
                if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_mc_list_play() fail. i4_ret = %d.\r\n", i4_ret));
                }
            }
            break;

            default:
                break;
        }

        if(MMP_VP_DETAIL_PAGE_ON == t_g_video_view.e_detail_page)
        {
            _mmp_vp_dp_update();
        }
    }
    else if(MMP_VE_NFY_CODE_MEDIA_PLAYING_INIT_OK == e_code)
    {
        /* Do nothing ...
           Move original update info to MMP_VE_NFY_CODE_MEDIA_PLAY_NORMAL
           for update dts codec correct */
        return;
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_DURATION_UPDATE == e_code)
    {
        /*FIXME  update duration here*/
        i4_ret = video_engine_get_duration(t_g_video_view.pt_engine_inst,
                                           MMP_VE_DUR_TYPE_TIME,
                                           &t_g_video_view.ui8_duration);
        if(MMPR_OK != i4_ret || 0 == t_g_video_view.ui8_duration)
        {
            video_engine_get_duration(t_g_video_view.pt_engine_inst,
                                      MMP_VE_DUR_TYPE_BYTE,
                                     &t_g_video_view.ui8_duration);
            t_g_video_view.e_prog_bar_type = _MMP_VP_PROG_BAR_TYPE_FILE;
            MMP_DBG_INFO(("video_engine_get_file_length() : duration = %lu\n", (UINT32)t_g_video_view.ui8_duration));
        }
        else
        {
            t_g_video_view.e_prog_bar_type = _MMP_VP_PROG_BAR_TYPE_TIME;
            DBG_LOG_PRINT(("video_engine_get_duration() : duration = %lu\n", (UINT32)t_g_video_view.ui8_duration));
        }
        switch(t_g_video_view.e_player_status)
        {
        case MMP_VE_PLAY_STAT_OPEN:
            t_g_video_view.ui8_position = 0;
            _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
            _mmp_vp_tb_icon_time(t_g_video_view.ui8_position, MMP_TB_SYNC_REPAINT); /* DTV00214965 */
        default:
                break;
        }
        MMP_DBG_INFO(("MMP[%s %d] ui8_duration = %d,pos = %d\n",__FUNCTION__,__LINE__,t_g_video_view.ui8_duration,t_g_video_view.ui8_position));
        return;
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_SPEED_UPDATE == e_code)
    {
        if (MMP_VE_PLAY_STAT_PLAY != t_g_video_view.e_player_status)
        {
            mmp_mc_list_play(MMP_GROUND_MODE_FORE, MMP_PLAY_IDX_CURRENT);
        }
    }
    else if (MMP_VE_NFY_CODE_MEDIA_PLAY_SEEK_READY == e_code)
    {
#if 0
        switch (t_g_video_view.e_player_status)
        {
             case MMP_VE_PLAY_STAT_PAUSE:
             case MMP_VE_PLAY_STAT_BLANK:
             case MMP_VE_PLAY_STAT_FAST_FWD:
             case MMP_VE_PLAY_STAT_FAST_RWD:
             case MMP_VE_PLAY_STAT_SLOW_FWD:
             case MMP_VE_PLAY_STAT_SLOW_RWD:
             case MMP_VE_PLAY_STAT_STOP:
             {
                 i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE,MMP_PLAY_IDX_CURRENT);
                 if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                 {
                     MMP_DBG_ERROR(("mmp_mc_list_play() fail. i4_ret = %d.\r\n", i4_ret));
                 }
                 else
                 {
                     _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
                     _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
                 }
             }
                 break;
             default:
                 break;

         }
#endif
         if(MMP_VE_PLAY_STAT_PAUSE != t_g_video_view.e_player_status)
         {
             /* recover updating time code */
             c_timer_start(t_g_video_view.h_timer_timeout,
                           MMP_VP_TIMER_TIMEOUT_DELAY,
                           X_TIMER_FLAG_REPEAT,
                           _mmp_vp_timer_nfy_fct,
                           NULL
                           );
         }
         _mmp_vp_reset_icon(NULL, NULL, NULL, NULL);
         _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
         e_g_seek_stat          = _MMP_VP_SEEK_STAT_UNUSED;

    }
    else if (MMP_VE_NFY_CODE_MEDIA_STOP_BGN == e_code)
    {
        c_timer_stop(t_g_video_view.h_timer_timeout);
        t_g_video_view.ui2_av_ntfy = MMP_VP_AV_NTFY_EMPTY;
    }
    else if (MMP_VE_NFY_CODE_MEDIA_STOP_EOS == e_code)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] video play end\n",__FUNCTION__,__LINE__));
        t_g_video_view.ui2_av_ntfy &= MMP_VP_AV_NTFY_EMPTY;
        _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
        t_g_video_view.e_player_status = MMP_VE_PLAY_STAT_STOP; /* To fix DTV00081619 */
#if 0
                a_banner_show_hdr_info(FALSE);
#else
                a_mmp_show_hdr_info(FALSE);
#endif

    #ifdef APP_MENU_MMP_COEXIST
        if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
        {
            if (APP_CFG_APP_STATUS_MENU_WIDE_MODE == a_cfg_get_app_status())
            {
                a_amb_resume_app(MMP_NAME);
            }
        }
    #endif
        a_cfg_set_app_status(APP_CFG_APP_STATUS_LAST_ENTRY);

        if(t_g_video_view.ui8_position < t_g_video_view.ui8_duration)
        {
             _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
             _mmp_vp_tb_icon_time(t_g_video_view.ui8_duration, MMP_TB_SYNC_REPAINT);
             c_thread_delay(200);
        }

        if(MMP_VE_PLAY_STAT_PAUSE == t_g_video_view.e_player_status)
        {
            mmp_mc_list_play(MMP_GROUND_MODE_FORE,MMP_PLAY_IDX_CURRENT);
        }

    #ifdef APP_3D_MODE_SUPPORT
        MMP_FP_PRESENT_MODE_T       e_present_mode = MMP_FP_PRESENT_MODE_FULL;
        BOOL                        b_3d_support = FALSE;
        mmp_mc_list_get_play_present_mode(&e_present_mode);
        if (MMP_FP_PRESENT_MODE_FULL == e_present_mode)
        {
            a_cfg_custom_plf_opt_get_3d_support(&b_3d_support);
            if(b_3d_support)
            {
                a_cfg_custom_3D_setting_reset_3D_mode();
            }
        }
    #endif
        _mmp_vp_play_next();
    }

    return;
}

#ifdef APP_CAST_TV_MMP
/*-----------------------------------------------------------------------------
 * Name
 *      _video_only_key_process
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _video_only_key_process(VOID*                       pv_tag1,
                                  VOID*                       pv_tag2,
                                  VOID*                       pv_tag3,
                                  VOID*                       pv_tag4)
{
    UINT32         ui4_key_code = IOM_GET_EVT_GRP_ID((UINT32)pv_tag1);
    INT32          i4_ret = 0;

    switch(ui4_key_code)
    {
        case BTN_SELECT:
        case BTN_PAUSE:
        {
        #ifdef APP_MENU_MMP_COEXIST
            if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                break ;
            }
        #endif

            if(t_g_video_view.e_player_status == MMP_VE_PLAY_STAT_PLAY)
            {
                i4_ret = mmp_mc_list_pause(MMP_GROUND_MODE_FORE);

                if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_mc_list_pause() fail. i4_ret = %d.\r\n", i4_ret));
                }
            }
            else if(t_g_video_view.e_player_status == MMP_VE_PLAY_STAT_PAUSE)
            {
                i4_ret = mmp_mc_list_play(MMP_GROUND_MODE_FORE,MMP_PLAY_IDX_CURRENT);
                if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
                {
                    MMP_DBG_ERROR(("mmp_mc_list_play() fail. i4_ret = %d.\r\n", i4_ret));
                }
            }

        }
        break;
        default:
        break;
    }
}

/*-----------------------------------------------------------------------------
 * Name:  _video_player_iom_nfy_fct
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
static VOID _video_player_iom_nfy_fct (VOID*    pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data)
{
    INT32 i4_ret = 0;

    if(t_g_video_view.e_vp_stat == MMP_VP_STAT_ACTIVE &&
        e_nfy_cond == IOM_NFY_COND_BTN_DOWN)
    {
        DBG_LOG_PRINT(("[MMP][%s %d] ui4_evt_code = 0x%x\n",__FUNCTION__,__LINE__,ui4_evt_code));
        switch(ui4_evt_code)
        {
            case BTN_SELECT:
            case BTN_PAUSE:
            {
                i4_ret = mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                                                    _video_only_key_process,
                                                    (VOID*)ui4_evt_code,
                                                    (VOID*)e_nfy_cond,
                                                    (VOID*)NULL,
                                                    (VOID*)NULL);
                MMPR_LOG_ON_FAIL(i4_ret);
                break;
            }
        #ifdef APP_C4TV_SUPPORT
            case BTN_ASPECT:
            {
                a_nav_link_mode_ui_hide();
                a_amb_default_key_handler_ex(WGL_MSG_KEY_DOWN, (VOID *)ui4_evt_code, NULL);
                break;
            }
        #endif
            case BTN_POWER:
            {
                /* change to last source before power fix DTV00813226*/
                mmp_main_change_last_isl_rec();
                a_mmp_set_power_exit_video_state(TRUE);
                break;
            }
            default:
                break;
        }
    }
}
/*---------------------------------------------------------------------------*/
/**
 * @brief   _mmp_vp_icl_pattern_func
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static VOID _mmp_vp_icl_pattern_func (
            VOID*                       pv_tag1,
            VOID*                       pv_tag2,
            VOID*                       pv_tag3,
            VOID*                       pv_tag4)
{
    ICL_ID_TYPE e_id = (ICL_ID_TYPE) (((UINT32) pv_tag1) & 0x0000FFFF);
    SIZE_T      t_size = ICL_RECID_TEST_PATTERN_STATUS_SIZE;
    INT32       i4_ret = 0;
    UINT8       ui1_state = ICL_RECID_TEST_PATTERN_STATUS_DISABLE;

    if (e_id == ICL_MAKE_ID(ICL_GRPID_TEST_PATTERN_STATUS, ICL_RECID_TEST_PATTERN_STATUS))
    {
        MMP_DBG_INFO(("[mmp] ICL_RECID_TEST_PATTERN_STATUS \n"));

        i4_ret = a_icl_get(e_id,
                           (VOID*)&ui1_state,
                           &t_size);
        if (i4_ret < ICLR_OK)
        {
            MMP_DBG_ERROR(("[mmp]: a_icl_get fail:%s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
            return;
        }

        /* pattern turn off */
        if(ui1_state == ICL_RECID_TEST_PATTERN_STATUS_DISABLE)
        {
            if(t_g_video_view.b_is_icl_exit_video)
            {
                t_g_video_view.b_is_icl_exit_video = FALSE;

                i4_ret = _mmp_vp_play();
                MMP_DBG_INFO(("[mmp]_mmp_be_icl_async_func %s,%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret));
            }
        }
        else /* pattern turn on */
        {
            t_size = ICL_RECID_MMP_RESUME_COND_SIZE;
            a_icl_get(ICL_MAKE_ID(ICL_GRPID_MMP, ICL_RECID_MMP_RESUME_COND),
                                   &ui1_state,
                                   &t_size);
            if(ui1_state == ICL_RECID_MMP_RESUME_COND_OK)
            {
                t_g_video_view.b_is_icl_exit_video = TRUE;
            }
        }
    }

}


/*---------------------------------------------------------------------------*/
/**
 * @brief  _mmp_vp_icl_nfy_fct
 * @param
 * @retval
 * @retval
 */
/*---------------------------------------------------------------------------*/
static INT32 _mmp_vp_icl_nfy_fct(UINT16 ui2_nfy_id, VOID* pv_tag, ICL_NOTIFY_DATA_T* pt_notify_data)
{
    MMP_DBG_INFO(("[mmp] _c4tv_apron_icl_nfy_func \n"));
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);

    switch (e_grp_id)
    {
    case ICL_GRPID_TEST_PATTERN_STATUS:
        mmp_mc_event_switch_context(MMP_MC_CSC_RETRY_TYPE_NORMAL,
                        _mmp_vp_icl_pattern_func,
                        (VOID*)(UINT32) pt_notify_data->pe_id[0],
                        NULL,
                        NULL,
                        NULL);
        break;

    default:
        break;
    }

    return MMPR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_init
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
static INT32 _mmp_vp_init(VOID)
{
    INT32           i4_ret;
    ISO_639_LANG_T  s639_lang;

    /* Reset view data. */
    c_memset (&t_g_video_view, 0, sizeof (VIDEO_PLAYER_VIEW_T));

    /* init engine */
    i4_ret = video_engine_create(_mmp_vp_engine_nfy_fct, &t_g_video_view.pt_engine_inst);
    if(MMPR_OK != i4_ret)
    {
         MMP_DBG_ERROR(("video_engine_open() fail. i4_ret = %d.\r\n", i4_ret));
         return i4_ret;
    }

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<MMP VP>Can't init lanugage \r\n"));
        t_g_video_view.ui2_lang = MLM_MMP_LANG_ENG;
    }
    else
    {
        t_g_video_view.ui2_lang = mlm_mmp_s639_to_langidx(s639_lang);
    }

#ifdef APP_CAST_TV_MMP
    t_g_video_view.b_is_res_not_support = FALSE;
    t_g_video_view.b_is_next_preload_end = FALSE;
    if(NULL_HANDLE == t_g_video_view.h_iom)
    {
        IRRC_SETTING_T  t_irrc_setting;
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
                              _video_player_iom_nfy_fct,
                             &t_g_video_view.h_iom);
        MMPR_LOG_ON_FAIL(i4_ret);

        /* icl notify */
        t_g_video_view.b_is_icl_exit_video = FALSE;

        i4_ret = a_icl_notify_reg(ICL_GRPID_TEST_PATTERN_STATUS,
                                  ICL_PRIORITY_DEFAULT,
                                  NULL,
                                  NULL,
                                  _mmp_vp_icl_nfy_fct,
                                  &t_g_video_view.ui2_icl_nfy_id);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    return MMPR_OK;
#endif

    i4_ret = _mmp_vp_view_init(&t_g_video_view);
    if(MMPR_OK != i4_ret)
    {
         MMP_DBG_ERROR(("_mmp_vp_view_init() fail. i4_ret = %d.\r\n", i4_ret));
         return i4_ret;
    }

#ifdef CLI_SUPPORT
    i4_ret = mmp_video_engine_cli_init ();
    if(MMPR_OK != i4_ret)
    {
         MMP_DBG_ERROR(("mmp_video_engine_cli_init() fail. i4_ret = %d.\r\n", i4_ret));
         _mmp_vp_deinit();
         return i4_ret;
    }

    i4_ret = mmp_video_player_cli_init ();
    if(MMPR_OK != i4_ret)
    {
         MMP_DBG_ERROR(("mmp_video_player_cli_init() fail. i4_ret = %d.\r\n", i4_ret));
         _mmp_vp_deinit();
         return i4_ret;
    }
#endif /* CLI_SUPPORT */

    return MMPR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_vp_deinit
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
static INT32 _mmp_vp_deinit(VOID)
{
#ifdef APP_CAST_TV_MMP
    INT32 i4_ret = 0;
    if(NULL_HANDLE != t_g_video_view.h_iom)
    {
        i4_ret = c_iom_close(t_g_video_view.h_iom);
        MMPR_LOG_ON_FAIL(i4_ret);
        t_g_video_view.h_iom = NULL_HANDLE;
    }
    if(0 != t_g_video_view.ui2_icl_nfy_id)
    {
        i4_ret = a_icl_notify_unreg(t_g_video_view.ui2_icl_nfy_id);
        MMPR_LOG_ON_FAIL(i4_ret);
        t_g_video_view.ui2_icl_nfy_id = 0;
    }
#endif

    /* Close video_engine */
    video_engine_destroy(t_g_video_view.pt_engine_inst);

    t_g_video_view.pt_engine_inst = NULL;

    _mmp_vp_view_deinit(&t_g_video_view);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_lst_set_text
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
static INT32 _mmp_vp_info_lst_set_text(VOID)
{
    INT32     i4_ret = MMPR_OK;
    HANDLE_T  h_info_list = NULL_HANDLE;
    HANDLE_T  h_view_item = NULL_HANDLE;

    h_info_list = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_LB_FILE);

    i4_ret = c_wgl_do_cmd(h_info_list,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (0, 0),
                          WGL_PACK(MLM_MMP_TEXT(t_g_video_view.ui2_lang,MLM_MMP_KEY_THU_MODE_FILE_INFO_NAME)));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;

    }

    i4_ret = c_wgl_do_cmd(h_info_list,
                  WGL_CMD_LB_SET_ITEM_TEXT,
                  WGL_PACK_2 (1, 0),
                  WGL_PACK(MLM_MMP_TEXT(t_g_video_view.ui2_lang,MLM_MMP_KEY_THU_MODE_FILE_INFO_RESOLUTION)));
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_do_cmd() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(h_info_list,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (2, 0),
                            WGL_PACK(L"Audio: "));
    if(WGLR_OK != i4_ret)

    c_wgl_repaint(h_info_list,
                  NULL,
                  TRUE);

    h_view_item = mmp_lm_focus_get_wgt_hdl(WID_MMP_LM_FOCUS_TXT_PRESS_OK_FOR_FULLSCREEN);
    i4_ret = c_wgl_do_cmd (h_view_item,
                           WGL_CMD_TEXT_SET_TEXT,
                           WGL_PACK(MLM_MMP_TEXT(t_g_video_view.ui2_lang,MLM_MMP_KEY_SELECT_FULLSCREEN)),
                           WGL_PACK(c_uc_w2s_strlen(MLM_MMP_TEXT(t_g_video_view.ui2_lang,MLM_MMP_KEY_SELECT_FULLSCREEN))));

    IS_MMPR_OK(i4_ret);

    c_wgl_repaint(h_view_item,
                  NULL,
                  TRUE);

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_handle_msg
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
static INT32 _mmp_vp_handle_msg(MMP_MSG_ID_T e_msg_id, VOID* pv_msg_param)
{
    MMP_MEDIA_TYPE_T         e_media_type = MMP_MEDIA_TYPE_UNKNOWN;
    MMP_BE_STATUS_T          e_status = MMP_BE_STATUS_NONE;
    MMP_FP_PRESENT_MODE_T    e_present_mode;
    INT32                    i4_ret = MMPR_OK;
    ISO_639_LANG_T           s639_lang;

    switch(e_msg_id)
    {
        case MMP_MSG_ID_APP_RESUMED:
        {
            /* Disable SCART bypass assocation */
            a_tv_set_scart_bypass_association(FALSE, FALSE);
        }
        break;

        case MMP_MSG_ID_GUI_LANG_XNG:
        {
            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                            (VOID*)&e_media_type);

            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS,
                            (VOID*)&e_status);

            mmp_mc_list_get_play_present_mode(&e_present_mode);

        #ifdef DEBUG
           DBG_LOG_PRINT(("\n%s,%s,%d,e_media_type=%d,e_status=%d,e_present_mode=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        e_media_type, e_status, e_present_mode));
        #endif

            i4_ret = a_cfg_get_gui_lang(s639_lang);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_ERROR(("<MMP VP>Can't init lanugage \r\n"));
                t_g_video_view.ui2_lang = MLM_MMP_LANG_ENG;
            }
            else
            {
                t_g_video_view.ui2_lang = mlm_mmp_s639_to_langidx(s639_lang);
            }

            if ((MMP_MEDIA_TYPE_VIDEO == e_media_type)&&
                (MMP_BE_STATUS_NORMAL == e_status)&&
                (MMP_FP_PRESENT_MODE_PREVIEW == e_present_mode))
            {
                _mmp_vp_info_lst_set_text();
            }
        }
            break;

        case MMP_MSG_ID_APP_PAUSED:
        {
            video_engine_zoom_reset(t_g_video_view.pt_engine_inst);
        }
        break;

        case MMP_MSG_ID_VOL_INFO_UPD:
        {
            if (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat)
            {
                //_mmp_vp_update_vol_info (TRUE, pv_msg_param);
            }
        }
        break;

        case MMP_MSG_ID_MEDIA_REMOVED:
        {
#ifdef APP_CAPTURE_LOGO_SUPPORT
            a_cap_abort(t_g_video_view.pv_cap_logo);
#endif
        }
        break;
        case MMP_MSG_ID_POWER_OFF:
        {
#ifdef APP_CAPTURE_LOGO_SUPPORT
            a_cap_abort(t_g_video_view.pv_cap_logo);
#endif
        }
        break;
#ifdef APP_MENU_MMP_COEXIST
        case MMP_MSG_ID_APP_STAT_XNG:
        {
            MMP_BE_STATUS_T     e_status = MMP_BE_STATUS_NONE;
            MMP_MEDIA_TYPE_T    e_media_type = MMP_MEDIA_TYPE_UNKNOWN;

            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_FILTER_TYPE,
                            (VOID*)&e_media_type);

            mmp_be_get_info(MMP_BE_INFO_GET_INFO_ID_STATUS,
                            (VOID*)&e_status);

            if ((MMP_BE_STATUS_PLAYER_ACT == e_status)
                &&(MMP_MEDIA_TYPE_VIDEO == e_media_type))
            {
                MMP_STAT_XNG_INFO_T* pt_mmp_stat_info = (MMP_STAT_XNG_INFO_T*)pv_msg_param;
                if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == pt_mmp_stat_info->e_mmp_stat_new)
                {
                    c_timer_stop(t_g_video_view.h_timer_timeout);
                    _mmp_vp_tb_hide();
                }
                else if (MMP_MAIN_AP_STATUS_RESUMED == pt_mmp_stat_info->e_mmp_stat_new)
                {
                    c_thread_delay(20);

                    _mmp_vp_update_status(TRUE);
                    _mmp_vp_update_pos(NULL, NULL, NULL, NULL);

                    _mmp_vp_tb_show();

                    c_timer_start(t_g_video_view.h_timer_timeout,
                                  MMP_VP_TIMER_TIMEOUT_DELAY,
                                  X_TIMER_FLAG_REPEAT,
                                  _mmp_vp_timer_nfy_fct,
                                  NULL);

                    c_wgl_set_focus(t_g_video_view.h_frm_main,
                                    WGL_NO_AUTO_REPAINT);
                }
            }
        }
            break;
#endif

        case MMP_MSG_ID_VEDIO_FILE_NOT_SUPPORT:
        {
            _mmp_vp_ib_show(MMP_IB_MSG_CLASS_INFO,
                            MLM_MMP_TEXT(t_g_video_view.ui2_lang,MLM_MMP_KEY_NFY_FILE_NOT_SUPPORT)
                            );
            c_timer_start (t_g_video_view.h_timer_hide_msg,
                       MMP_VP_TIMER_HIDE_MSG_DELAY,
                       X_TIMER_FLAG_ONCE,
                       _mmp_vp_timer_nfy_fct,
                       NULL);
        }
            break;
        default:
            break;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_is_type_of
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
static INT32 _mmp_vp_is_type_of(const CHAR* ps_filename, MMP_MEDIA_TYPE_T* pe_type)
{
    if(NULL == ps_filename || NULL == pe_type)
    {
        return MMPR_INV_ARG;
    }

    if(mmp_util_filter_fct_by_ext(ps_filename, (CHAR*) as_g_video_ext, ui2_g_video_ext_count))
    {
        *pe_type = MMP_MEDIA_TYPE_VIDEO;
    }
    else
    {
        *pe_type = MMP_MEDIA_TYPE_UNKNOWN;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_set_aud_mode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: MMPR_OK            The function executes successfully.
 *          Otherwise          The function failed.
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_set_aud_mode(SCC_AUD_DOWNMIX_MODE_T e_aud_mode )
{
    SM_COMMAND_T at_sm_cmds[3];
    HANDLE_T h_aud_comp = NULL_HANDLE;
    INT32 i4_ret = MMPR_OK;

    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code     = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;

    i4_ret = c_scc_comp_open(at_sm_cmds, &h_aud_comp);
    if(SMR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_scc_comp_open() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_scc_aud_set_matrix_mode(h_aud_comp, e_aud_mode);
    if(SMR_OK != i4_ret)
    {
       MMP_DBG_ERROR(("c_scc_aud_set_matrix_mode() fail. i4_ret = %d.\r\n", i4_ret));
    }

    c_scc_comp_close(h_aud_comp);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_open
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
static INT32 _mmp_vp_open(const CHAR*           ps_filename,
                          mmp_fp_show_nfy_fct   pf_nfy,
                          VOID*                 pv_tag,
                          UINT32                ui4_ver)
{
    INT32    i4_ret;
    CHAR *   pc_str;
    UTF16_T  w2s_filename[MMP_VP_RC_FILE_MAX_LEN]={0};

    /* Set mmc_ver */
    t_g_video_view.ui4_mmc_ver = ui4_ver;

    t_g_video_view.pf_fp_show_nfy_fct = pf_nfy;
    t_g_video_view.pv_mmp_tag = pv_tag;

    /*FIXME*/
    i4_ret = video_engine_open(t_g_video_view.pt_engine_inst,ps_filename);
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("video_engine_open() fail. i4_ret = %d.\r\n", i4_ret));
    }

    /*set StatusBar file name*/
    pc_str = c_strrchr(ps_filename,MMP_VP_RC_FILE_PATH_DIV_CHAR);
    if(pc_str != NULL)
    {
        /*remove prefix*/
        pc_str = mmp_util_trim_path_prefix(ps_filename, pc_str + 1);
        c_uc_ps_to_w2s(pc_str, w2s_filename, MMP_VP_RC_FILE_MAX_LEN);
    }
    else
    {
        c_uc_ps_to_w2s(ps_filename, w2s_filename, MMP_VP_RC_FILE_MAX_LEN);
    }

    _mmp_vp_tb_icon_file_name(w2s_filename, MMP_TB_SYNC_REPAINT);
    _mmp_vp_tb_icon_file_idx(TRUE);

    c_uc_w2s_strncpy(w2s_g_file, w2s_filename, MMP_VP_RC_FILE_MAX_LEN-1);
    w2s_g_file[MMP_VP_RC_FILE_MAX_LEN-1] = 0;

    _mmp_vp_update_status(FALSE);

#if NEVER
    i4_ret = _mmp_vp_set_aud_mode(SCC_AUD_MATRIX_MODE_DUAL_MIX); /* SCC_AUD_MATRIX_MODE_DUAL_MIX : LR */
    if(MMPR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_vp_set_aud_mode() fail. i4_ret = %d.\r\n", i4_ret));
    }
#endif
    return MMPR_IS_OPENED;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_vp_close
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
static INT32 _mmp_vp_close(VOID)
{
    INT32 i4_ret = 0;

    i4_ret = video_engine_close(t_g_video_view.pt_engine_inst);
    if(MMPR_OK != i4_ret && MMPR_IS_CLOSED != i4_ret)
    {
        MMP_DBG_ERROR(("_mmp_vp_close() fail. i4_ret = %d.\r\n", i4_ret));
    }

    _mmp_vp_update_status(FALSE);

    a_menu_11_point_gain_update();

    return MMPR_IS_CLOSED;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_vp_next_preload
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
static INT32 _mmp_vp_next_preload(const CHAR* ps_filename)
{
    INT32    i4_ret;
    CHAR *   pc_str;
    UTF16_T  w2s_next[MMP_VP_RC_FILE_MAX_LEN]={0};

    i4_ret = video_engine_next_preload(t_g_video_view.pt_engine_inst, ps_filename);
    if(MMPR_OK != i4_ret && MMPR_IS_PRELOADED != i4_ret)
    {
        MMP_DBG_ERROR(("video_engine_next_preload() fail. i4_ret = %d.\r\n", i4_ret));
    }

    /*If filename is null, close previous "preloaded file"*/
    if (NULL != ps_filename)
    {
        /*set DetailPage next*/
        pc_str = c_strrchr(ps_filename,MMP_VP_RC_FILE_PATH_DIV_CHAR);
        if(pc_str != NULL)
        {
            pc_str = mmp_util_trim_path_prefix(ps_filename, pc_str + 1);
            c_uc_ps_to_w2s(pc_str, w2s_next, MMP_VP_RC_FILE_MAX_LEN);
        }
        else
        {
            c_uc_ps_to_w2s(ps_filename, w2s_next, MMP_VP_RC_FILE_MAX_LEN);
        }
    }

    c_uc_w2s_strncpy(w2s_g_next, w2s_next, MMP_VP_RC_FILE_MAX_LEN-1);
    w2s_g_next[MMP_VP_RC_FILE_MAX_LEN-1] = 0;

    return MMPR_IS_PRELOADED;
}
/*----------------------------------------------------------------------------
 * Name: _mmp_vp_next_attr_set
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
static INT32 _mmp_vp_next_attr_set (UINT32 ui4_attr_count, const MMP_FP_SHOW_ATTR_T* at_show_attr)
{
    return video_engine_next_attr_set(t_g_video_view.pt_engine_inst,ui4_attr_count,at_show_attr);
}
/*----------------------------------------------------------------------------
 * Name: _mmp_vp_attr_set
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
static INT32 _mmp_vp_attr_set (UINT32 ui4_attr_count, const MMP_FP_SHOW_ATTR_T* at_show_attr)
{
    return video_engine_attr_set(t_g_video_view.pt_engine_inst,ui4_attr_count,at_show_attr);
}

static INT32 _mmp_vp_apply_3d_setting(VOID)
{
    INT32                      i4_ret = MMPR_OK;
    BOOL                       b_is_3D_content = FALSE;
    VSH_SRC_RESOLUTION_INFO_T  t_video_resolution;

    c_memset(&t_video_resolution, 0, sizeof(t_video_resolution));
    i4_ret = c_svctx_get_video_src_resolution(mmp_main_get_svctx_handle(TV_WIN_ID_MAIN),
                                               &t_video_resolution);
    MMPR_LOG_ON_FAIL(i4_ret);

    switch (t_video_resolution.e_src_tag3d_type)
    {
        case VSH_SRC_TAG3D_2D:
            b_is_3D_content = FALSE;
            return MMPR_OK;
        case VSH_SRC_TAG3D_MVC:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_FS:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_FP:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_REALD:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_TB:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_SBS:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_SENSIO:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_TTDO:
        case VSH_SRC_TAG3D_NOT_SUPPORT:
        default:
            b_is_3D_content = FALSE;
            break;
    }

    if (b_is_3D_content)
    {
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     (INT16)APP_CFG_3D_MODE_AUTO);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

        /* 3D to 2D*/
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                     (INT16 )APP_CFG_3D_TO_2D_OFF);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

       DBG_LOG_PRINT(("\n%s,%s,%d,apply 3d\n",
                    __FILE__, __FUNCTION__, __LINE__));
    }

    return i4_ret;
}

static HANDLE_T         h_mmp_dolhdrhlg_frame = NULL_HANDLE;

VOID mmp_fullscreen_auto_hide_info_fct(HANDLE_T  pt_tm_handle,
                                                     VOID*     pv_tag)
{
     c_wgl_set_visibility(h_mmp_dolhdrhlg_frame,WGL_SW_HIDE_RECURSIVE);
     c_wgl_repaint(h_mmp_dolhdrhlg_frame,NULL,FALSE);
     c_timer_stop(mmp_fullscreen_show_vf_info);
}
INT32 mmp_show_video_icon_fullscreen(MMP_SIDERBAR_HDR e_hdr)
{
    HANDLE_T         visibie_handle        = NULL_HANDLE;
    ISL_REC_T        t_isl_rec             = {0};
    GL_RECT_T        pt_rect_tmp;
    GL_RECT_T*       pt_rect;

    MMP_BE_BROWSER_STATUS_T     e_mmp_browser_status = a_mmp_be_get_browser_status();

    h_mmp_dolhdrhlg_frame = mmp_view_rc_get_siderbar_wgt_hdl(WID_MMP_SIDERBAR_VIEW_RC_FRM_SIDER_BAR);
    //c_wgl_set_visibility(h_mmp_dolhdrhlg_frame, WGL_SW_HIDE_RECURSIVE);

    switch(e_hdr)
    {
        case MMP_HDR_SDR:
            return MMPR_OK;

        case MMP_HDR_HDR10PLUS:
        {
            UTF16_T            w2s_str[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
            c_uc_w2s_strcpy(w2s_str, (UTF16_T*)L"HDR10+");

            visibie_handle = mmp_view_rc_get_siderbar_wgt_hdl(WID_MMP_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR10PLUS);
            c_wgl_float(visibie_handle,TRUE,0);
            c_wgl_do_cmd (visibie_handle,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          (VOID*)c_uc_w2s_strlen (w2s_str));
        }
            break;

		case MMP_HDR_HLG:
		case MMP_HDR_HDR10:
        case MMP_HDR_DOLBY_VISION:
        {

            WGL_IMG_INFO_T    t_img_info = {0};
            WGL_COLOR_INFO_T  t_clr_info = {0};
            HANDLE_T          h_img      = NULL_HANDLE;
            GL_COLOR_T        t_color    = t_g_mmp_transparent;

            if(e_hdr == MMP_HDR_HLG)
            {
                h_img = h_g_mmp_HLG_Vert_white;
            }
            else if(e_hdr == MMP_HDR_HDR10)
            {
                h_img = h_g_mmp_HDR10_Vert_white;
            }
            else if(e_hdr == MMP_HDR_DOLBY_VISION)
            {
                h_img   = h_g_mmp_dolbyVision_Vert_white_Banner;
                t_color = t_g_mmp_black;
            }

            visibie_handle  = mmp_view_rc_get_siderbar_wgt_hdl(WID_MMP_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_HDR_HLG_VISION);
            /* set message color */
            t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
            t_clr_info.u_color_data.t_standard.t_disable   = t_color;
            t_clr_info.u_color_data.t_standard.t_enable    = t_color;
            t_clr_info.u_color_data.t_standard.t_highlight = t_color;

            c_wgl_do_cmd(visibie_handle,
                        WGL_CMD_GL_SET_COLOR,
                        WGL_PACK(WGL_IMG_BK),
                        WGL_PACK(&t_clr_info));

            /* set icon image buffer*/
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
            t_img_info.u_img_data.t_standard.t_enable    = h_img;
            t_img_info.u_img_data.t_standard.t_disable   = h_img;
            t_img_info.u_img_data.t_standard.t_highlight = h_img;

            c_wgl_do_cmd (visibie_handle,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
#if 0
            //get current  frm rect
            pt_rect = mmp_view_rc_get_siderbar_frm_rect();
            if(pt_rect)
            {
                DBG_LOG_PRINT (("[Jundi] frm rect[l= %4d,r = %4d,t = %4d,b = %4d] old\n",pt_rect->i4_left,pt_rect->i4_right,pt_rect->i4_top,pt_rect->i4_bottom)) ;
                //adjust current siderbar frm rect
                pt_rect_tmp = *pt_rect;
                (&pt_rect_tmp)->i4_bottom = pt_rect->i4_bottom + 130;
                (&pt_rect_tmp)->i4_top = pt_rect->i4_top + 130;
                DBG_LOG_PRINT (("[Jundi] frm rect[l= %4d,r = %4d,t = %4d,b = %4d] new\n",(&pt_rect_tmp)->i4_left,(&pt_rect_tmp)->i4_right,(&pt_rect_tmp)->i4_top,(&pt_rect_tmp)->i4_bottom)) ;
                c_wgl_move(h_mmp_dolhdrhlg_frame,&pt_rect_tmp,WGL_NO_AUTO_REPAINT);
            }
#endif
        }
            break;
        case MMP_HDR_DOLBY_AUDIO:
            {
                WGL_IMG_INFO_T     t_img_info = {0};
                HANDLE_T           h_img      = h_g_mmp_dolbyAudio_Vert_white;
                DBG_LOG_PRINT(("[Jundi][%s %d]#####\n",__FUNCTION__,__LINE__));
                visibie_handle  = mmp_view_rc_get_siderbar_wgt_hdl(WID_MMP_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_AUDIO);
                WGL_COLOR_INFO_T  t_clr_info = {0};
                GL_COLOR_T        t_color    = t_g_mmp_black;
                /* set message color */
                t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
                t_clr_info.u_color_data.t_standard.t_disable   = t_color;
                t_clr_info.u_color_data.t_standard.t_enable    = t_color;
                t_clr_info.u_color_data.t_standard.t_highlight = t_color;
    
                c_wgl_do_cmd(visibie_handle,
                            WGL_CMD_GL_SET_COLOR,
                            WGL_PACK(WGL_IMG_BK),
                            WGL_PACK(&t_clr_info));
                /* set icon image buffer*/
                t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
                t_img_info.u_img_data.t_standard.t_enable    = h_img;
                t_img_info.u_img_data.t_standard.t_disable   = h_img;
                t_img_info.u_img_data.t_standard.t_highlight = h_img;

                c_wgl_do_cmd (visibie_handle,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_FG),
                              WGL_PACK(&t_img_info));
                #if 0
                //get current  frm rect
                pt_rect = mmp_view_rc_get_siderbar_frm_rect();
                if(pt_rect)
                {
                    DBG_LOG_PRINT (("[Jundi] frm rect[l= %4d,r = %4d,t = %4d,b = %4d] old\n",pt_rect->i4_left,pt_rect->i4_right,pt_rect->i4_top,pt_rect->i4_bottom)) ;
                    //adjust current siderbar frm rect
                    pt_rect_tmp = *pt_rect;
                    pt_rect_tmp.i4_left = pt_rect->i4_bottom+ 160 ;
                    pt_rect_tmp.i4_top = pt_rect->i4_top+160 ;


                    //pt_rect_tmp.i4_left = pt_rect->i4_left-130;
                    //pt_rect_tmp.i4_right = pt_rect->i4_right-130;
                    DBG_LOG_PRINT (("[Jundi] frm rect[l= %4d,r = %4d,t = %4d,b = %4d] new\n",(&pt_rect_tmp)->i4_left,(&pt_rect_tmp)->i4_right,(&pt_rect_tmp)->i4_top,(&pt_rect_tmp)->i4_bottom)) ;
                    c_wgl_move(h_mmp_dolhdrhlg_frame,&pt_rect_tmp,WGL_NO_AUTO_REPAINT);
                }
                #endif
            }
            break;
        default:
        {
            WGL_IMG_INFO_T     t_img_info = {0};
            visibie_handle = mmp_view_rc_get_siderbar_wgt_hdl(WID_MMP_SIDERBAR_VIEW_RC_TXT_ITM_SIDER_HDR10PLUS);
            c_wgl_do_cmd (visibie_handle,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)L"",
                          (VOID*)0);
            visibie_handle  = mmp_view_rc_get_siderbar_wgt_hdl(WID_MMP_SIDERBAR_VIEW_RC_ICON_ITM_SIDER_DOLBY_HDR_HLG_VISION);

            /* set icon image buffer*/
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD ;
            t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
            t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
            t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
            c_wgl_do_cmd (visibie_handle,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

            c_wgl_set_visibility(h_mmp_dolhdrhlg_frame, WGL_SW_HIDE);
            return NAVR_OK;
        }
            break;

    }

    menu_get_crnt_isl(&t_isl_rec);//get the current source
    c_wgl_float(h_mmp_dolhdrhlg_frame,TRUE,FALSE);

    //check whether it's in fullscreen status
    if((INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type &&
        DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type) &&
        !(e_mmp_browser_status >= MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING &&
        e_mmp_browser_status <= MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING))
    {
        DBG_LOG_PRINT(("[Jundi][MMP][%s %d] mmp is not full screen mode\n",__FUNCTION__,__LINE__));
        return NAVR_OK;
    }
    //show the icon
    c_wgl_set_visibility(visibie_handle,WGL_SW_NORMAL);
    c_wgl_float(visibie_handle,TRUE,FALSE);
    c_wgl_set_visibility (h_mmp_dolhdrhlg_frame,WGL_SW_NORMAL);
    c_wgl_repaint(h_mmp_dolhdrhlg_frame,NULL,TRUE);

    c_timer_start(mmp_fullscreen_show_vf_info,
                  3000,
                  X_TIMER_FLAG_ONCE,
                  mmp_fullscreen_auto_hide_info_fct,
                  NULL);
    return MMPR_OK;

}

INT32 a_mmp_show_hdr_info(BOOL b_show)
{
     MMP_SIDERBAR_HDR video_hdr      = MMP_HDR_SDR;
     UINT32           i4_ret;
     APPL_SPLAYER_MOVIE_INFO_T tMovieInfo;
     c_memset(&tMovieInfo, 0, sizeof(tMovieInfo));
     i4_ret =  video_engine_get_movie_info(&tMovieInfo);
     if (MMPR_OK != i4_ret)
        DBG_LOG_PRINT(("[%s %d]video_engine_get_movie_info FAILED\n",__FUNCTION__,__LINE__));

     if(b_show)
     {
        //get the dolby/HDR10/HLG type

        SCC_DOVI_INFO_T         t_dolby_vision;
        SCC_VID_HDR_TYPE_T      t_hdr_type;

        HANDLE_T                h_scc_comp = NULL_HANDLE;

        CHAR             s_disp_name[ACFG_MAX_DISP_NAME+1];

        c_memset(&t_dolby_vision,0,sizeof(SCC_DOVI_INFO_T));

        /* Get SCC handle by display name. */
        i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        MMPR_LOG_ON_FAIL(i4_ret == APP_CFGR_OK ? MMPR_OK : i4_ret);

        h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0 ?
                              h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid);
        //GET DOLBY TYPE
        i4_ret = c_scc_vid_get_dovi_info(h_scc_comp,&t_dolby_vision);
        MMPR_LOG_ON_FAIL(i4_ret == SMR_OK ? MMPR_OK : i4_ret);
        if ( t_dolby_vision.ui1_is_doviHDR != FALSE)
        {
            video_hdr = MMP_HDR_DOLBY_VISION;
        }
        else
        {

            //GET HDR10/HLG TYPE
            i4_ret = c_scc_vid_get_hdr_type(h_scc_comp, &t_hdr_type);
            MMPR_LOG_ON_FAIL(i4_ret == SMR_OK ? MMPR_OK : i4_ret);
            if(t_hdr_type == SCC_VID_PQ_HLG)
            {
                video_hdr = MMP_HDR_HLG;
            }
            else if(t_hdr_type == SCC_VID_PQ_HDR10)
            {
                video_hdr = MMP_HDR_HDR10;
            }
            else if(t_hdr_type == SCC_VID_PQ_HDR10PLUS)
            {
                video_hdr = MMP_HDR_HDR10PLUS;
            }
        }

        c_timer_stop(mmp_fullscreen_show_vf_info);
        mmp_show_video_icon_fullscreen(video_hdr);

        //dolby audio
        if((tMovieInfo.eAudioCodec == E_SPLAYER_AUDIO_CODEC_TYPE_AC4) ||
           (tMovieInfo.eAudioCodec == E_SPLAYER_AUDIO_CODEC_TYPE_AC3) ||
           (tMovieInfo.eAudioCodec == E_SPLAYER_AUDIO_CODEC_TYPE_AC3P))
        {
            DBG_LOG_PRINT(("[%s %d]dolby audio full screen\n",__FUNCTION__,__LINE__));
            mmp_show_video_icon_fullscreen(MMP_HDR_DOLBY_AUDIO);
        }

    }

    return MMPR_OK;
}

static BOOL _mmp_videoplay_get_disp_handle(MI_HANDLE *phDisp,UINT16 ui2_idx)
{
    char szWinName[32] = {0};
    MI_DISP_QueryHandleParams_t stDispQueryHandleParams = {0};
    MI_DISP_OpenParams_t stDispOpenParams = {E_MI_DISP_VIDWIN_HD, 0};

    c_snprintf(szWinName, sizeof(szWinName), "MI_DISP_HD%d", ui2_idx);

    stDispQueryHandleParams.pszName = (MI_U8*)szWinName;

    if(MI_DISP_GetHandle(&stDispQueryHandleParams, phDisp) != MI_OK)
    {
        stDispOpenParams.pszName = (MI_U8*)szWinName;
        if(MI_DISP_Open(&stDispOpenParams, phDisp) != MI_OK)
        {
            MMP_DBG_ERROR(("Leave, MI_DISP_Open error\n"));
            return FALSE;
        }
    }

    return TRUE;
}

BOOL _mmp_video_equal_proportion_zoom(VOID)
{
	MI_RESULT				   eRet = MI_ERR_FAILED;
	INT32                      i4_ret = MMPR_OK;
	MI_HANDLE			       FullDispHdl;
	MI_DISP_VidWinRect_t       stOutRect;
	SCC_VID_PANEL_INFO_T       t_main_panel_info;
	APPL_SPLAYER_MOVIE_INFO_T  tMovieInfo;
	MI_DISP_ConnectedConds_t   stDispConds = {0};
	MI_U32                     u32ConnectedNum = 0;
	UINT16                     estimate_h;

	c_memset(&tMovieInfo, 0, sizeof(tMovieInfo));

	i4_ret = video_engine_get_movie_info(&tMovieInfo);
	if((MMPR_OK != i4_ret) || (tMovieInfo.u32MovieWidth == 0) || (tMovieInfo.u32MovieHeight ==0))
	{
		tMovieInfo.u32MovieWidth = 3840;
		tMovieInfo.u32MovieHeight = 2160;
	}
	i4_ret = c_scc_vid_get_panel_info(h_g_acfg_scc_main_vid, &t_main_panel_info);
	if(MMPR_OK != i4_ret)
	{
		t_main_panel_info.ui4_PanelWidth = 3840;
		t_main_panel_info.ui4_PanelHeight = 2160;
	}
	DBG_LOG_PRINT(("[chonghuang][%s %d] width = %d, height = %d\n",__FUNCTION__,__LINE__,t_main_panel_info.ui4_PanelWidth,t_main_panel_info.ui4_PanelHeight));
	DBG_LOG_PRINT(("[chonghuang][%s %d]u32MovieWidth = %d, u32MovieHeight = %d\n",__FUNCTION__,__LINE__,tMovieInfo.u32MovieWidth,tMovieInfo.u32MovieHeight));

	if(_mmp_videoplay_get_disp_handle(&FullDispHdl,0) == FALSE)
	{
		MMP_DBG_ERROR(("_mmp_browse_get_disp_handle Fail \r\n"));
	}
	stDispConds.bIsInput = TRUE;
	stDispConds.u32Module = MI_MODULE_TYPE_VIDEO;
	if(MI_DISP_GetConnectedNum(FullDispHdl, &stDispConds, &u32ConnectedNum) != MI_OK)
	{
		MMP_DBG_ERROR((" Fail at h_Disp_Hdl 0x%x!!\n",FullDispHdl));
	}
	MMP_DBG_INFO((" get h_Disp_Hdl : 0x%x \r\n",FullDispHdl));

	estimate_h = t_main_panel_info.ui4_PanelWidth * tMovieInfo.u32MovieHeight / tMovieInfo.u32MovieWidth;
	if (estimate_h > t_main_panel_info.ui4_PanelHeight)
	{
		stOutRect.u16Width = t_main_panel_info.ui4_PanelHeight * tMovieInfo.u32MovieWidth / tMovieInfo.u32MovieHeight;
		stOutRect.u16Height = t_main_panel_info.ui4_PanelHeight;
	}
	else if (estimate_h < t_main_panel_info.ui4_PanelHeight)
	{
		stOutRect.u16Width = t_main_panel_info.ui4_PanelWidth;
		stOutRect.u16Height = estimate_h;
	}
	else if (estimate_h == t_main_panel_info.ui4_PanelHeight)
	{
		stOutRect.u16Width = t_main_panel_info.ui4_PanelWidth;
		stOutRect.u16Height = t_main_panel_info.ui4_PanelHeight;
	}


	stOutRect.u16X = (t_main_panel_info.ui4_PanelWidth - stOutRect.u16Width)/2;
	stOutRect.u16Y = (t_main_panel_info.ui4_PanelHeight - stOutRect.u16Height)/2;
	DBG_LOG_PRINT(("[chonghuang][%s %d] w = %d,h = %d, x = %d, y = %d\n",__FUNCTION__,__LINE__,stOutRect.u16Width,stOutRect.u16Height,stOutRect.u16X,stOutRect.u16Y));

	CHECK_RET(MI_DISP_SetMute(FullDispHdl, E_MI_DISP_MUTE_FLAG_SET_WINDOW),MI_OK);
	CHECK_RET(MI_DISP_SetOutputRect(FullDispHdl, &stOutRect),MI_OK);

	eRet = MI_DISP_ApplySetting(FullDispHdl);
	if(eRet == MI_ERR_NOT_SUPPORT)
	{
		MMP_DBG_ERROR(("Scaling Down Size exceed HW limitation: DEC Rate\n"));
	}
	else
	{
		MMP_DBG_INFO((" eRet:%d, MI_DISP_ApplySetting successed\n",eRet));
	}

	CHECK_RET(MI_DISP_SetUnMute(FullDispHdl, E_MI_DISP_MUTE_FLAG_SET_WINDOW),MI_OK);

	return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_view_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_activate(
    VIDEO_PLAYER_VIEW_T*      pt_this)
{
    INT32                       i4_ret;
    SIZE_T                      z_size;
    MMP_FP_PRESENT_MODE_T       t_present_mode = MMP_FP_PRESENT_MODE_FULL;
    VSH_REGION_INFO_T           t_disp_region;
    _MMP_VE_PLAY_INST_PTR_T pt_this1 = (_MMP_VE_PLAY_INST_PTR_T)t_g_video_view.pt_engine_inst;

    i4_ret = mmp_mc_list_get_play_present_mode(&t_present_mode);
    if (MMPR_OK == i4_ret &&
        MMP_FP_PRESENT_MODE_FULL == t_present_mode)
    {
        /* from preview mode to full screen mode */
        t_disp_region.ui4_x = t_disp_region.ui4_y = 0;
        t_disp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
        t_disp_region.ui4_height = VSH_REGION_MAX_HEIGHT;

        z_size = sizeof(VSH_REGION_INFO_T);
#ifdef NEVER
        i4_ret = c_svctx_set_stream_attr(
                    pt_this1->h_svctx_hdl,
                    ST_VIDEO,
                    SM_VSH_SET_TYPE_DISP_REGION,
                    (VOID*)&t_disp_region,
                    z_size
                    );

#endif
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));

        i4_ret = _mmp_vp_apply_3d_setting();
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
        return MMPR_OK;

    a_cfg_set_skip_viewport_func(FALSE);

    mmp_main_set_video_srm_mode(SCC_VID_SRM_MODE_VIDEO);

#ifdef APP_CAST_TV_MMP
    t_g_video_view.e_vp_stat = MMP_VP_STAT_ACTIVE;

    t_g_video_view.e_repeat_mode = MMP_REPEAT_MODE_ALL;
    {
        MMP_PL_ATTR_T               at_attr[1];
        at_attr[0].e_id = MMP_PL_ATTR_ID_FG_REPEAT;
        at_attr[0].pv_param = (VOID*)t_g_video_view.e_repeat_mode;
        mmp_mc_list_set_attr(1, at_attr);
    }
    return MMPR_OK;
#endif
    t_g_video_view.ui8_position = (UINT64)0;
    t_g_video_view.ui8_duration = (UINT64)0;
    //t_g_video_view.t_sub_info.ui2_sub_num = (UINT16)0;
    t_g_video_view.t_aud_info.ui2_aud_num = (UINT16)0;
    t_g_video_view.e_prog_bar_type = _MMP_VP_PROG_BAR_TYPE_TIME;

    c_memset(pt_this->t_optl_scr_mode,0,MMP_VP_OPTL_SCR_MODE_NUM);
    c_memset(&t_g_video_view.t_program_info,0,sizeof(MMP_VE_PROGRAM_INFO_T));
    c_memset(w2s_g_file, 0, sizeof(w2s_g_file));
    c_memset(w2s_g_next, 0, sizeof(w2s_g_next));

    /* Never show time code for DMR */
#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if (FALSE == a_mmp_dmr_is_active())

    {
        _mmp_vp_tb_reset(); /* To fix DTV00083194 */
        _mmp_vp_tb_show();
    }
#endif

    _mmp_vp_dp_hide();

    /* hdr info*/
#if NEVER
    a_banner_show_hdr_info(TRUE);
#else
    a_mmp_show_hdr_info(TRUE);
#endif

    _mmp_vp_view_update_codec(t_g_video_view.ui2_av_ntfy, TRUE);
    /*option list*/
    pt_this->e_opt_stat = _MMP_VP_OPTL_LST_STAT_HIDE;
    c_wgl_set_visibility(t_g_video_view.h_opt_list,WGL_SW_HIDE);

    /*clear next file name*/
    pt_vdp_inst->e_repaint = COM_UI_NON_REPAINT;
    mmp_com_ui_dp_set_text(pt_vdp_inst, MMP_VP_RC_DP_LBL_ID_NEXT, NULL);

    t_g_video_view.e_detail_page = MMP_VP_DETAIL_PAGE_OFF;

    /*picture mode*/
    t_g_video_view.e_pic_mode = MMP_VP_PIC_MODE_NONE;

    /*flag of playing invalid file*/
    t_g_video_view.b_crt_play_invalid_file = FALSE;

    /*vol bar*/
    _mmp_vp_update_vol_info (FALSE, NULL);

    /**/
    i4_ret = c_wgl_set_visibility(pt_this->h_frm_main, WGL_SW_NORMAL);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_visibility() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_this->h_frm_main, TRUE);
    if(WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_wgl_set_focus() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    t_g_video_view.e_vp_stat = MMP_VP_STAT_ACTIVE;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_view_inactive
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
static INT32 _mmp_vp_view_inactive (VOID)
{
    INT32 i4_ret=0;

    if(t_g_video_view.b_crt_play_invalid_file)
    {
        c_timer_stop(t_g_video_view.h_timer_hide_msg);
        t_g_video_view.b_crt_play_invalid_file = FALSE;
    }

    _mmp_vp_ib_hide();

    _mmp_vp_tb_hide();
    _mmp_vp_tb_reset();

    i4_ret = mmp_info_bar_hide();
    MMPR_LOG_ON_FAIL(i4_ret);
    /* hdr info*/
#if NEVER
    a_banner_show_hdr_info(FALSE);
#else
    a_mmp_show_hdr_info(FALSE);
#endif

    c_timer_stop(t_g_video_view.h_timer_viewer);
    c_timer_stop(t_g_video_view.h_timer_timeout);
    c_timer_stop(t_g_video_view.h_timer_cec_sac);

    c_wgl_show (t_g_video_view.h_frm_main, WGL_SW_HIDE);

    t_g_video_view.e_vp_stat = MMP_VP_STAT_INACTIVE;
    t_g_video_view.ui2_av_ntfy = MMP_VP_AV_NTFY_EMPTY;

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_preview_activate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_preview_activate(const MMP_FP_PREVIEW_INFO_T* pt_info)
{
    return video_engine_preview_activate(t_g_video_view.pt_engine_inst, pt_info);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_preview_inactivate
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_preview_inactivate(VOID)
{
    INT32   i4_ret = MMPR_OK;

    i4_ret = mmp_com_ui_focus_info_frm_inactive(
                            t_g_video_view.pv_video_info_inst,
                            (BOOL)(UINT32)TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);
    t_g_video_view.e_vp_stat = MMP_VP_STAT_INACTIVE;
    return video_engine_preview_inactivate(t_g_video_view.pt_engine_inst);
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_play
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
static INT32 _mmp_vp_play(VOID)
{
    INT32 i4_ret;
    MMP_VE_DIVX_CERT_T e_divx_cert;

    c_memset(&e_divx_cert, 0, sizeof(MMP_VE_DIVX_CERT_T));
    t_g_video_view.t_program_info.ui1_cur_idx = 0;

    i4_ret = video_engine_play(t_g_video_view.pt_engine_inst,&e_divx_cert);
#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if ((MMPR_OK != i4_ret) && (MMPR_IS_PLAYED != i4_ret))
    {
        if (a_mmp_dmr_is_active())
        {
            c_dmr_submit_player_status(
                        PLAYER_MEDIATYPE_VIDEO,
                        PLAYER_NFYCODE_FILE_NOT_SUPPORT
                        );
        }
    }
#endif
    DBG_LOG_PRINT(("[MMP][%s %d]i4_ret = %d\n ",__FUNCTION__,__LINE__,i4_ret));
    switch(i4_ret)
    {
        case MMPR_NOT_SUPPORT:
        {
            //if (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat)
            {
            #ifdef APP_CAST_TV_MMP
                mmp_mc_list_next(MMP_GROUND_MODE_FORE);
            #else
                t_g_video_view.e_last_open_elm_ret = _MMP_VP_LAST_OPEN_ELM_RET_FAILED;
                mmp_mc_event_switch_context(
                                MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_vp_handle_invalid_file,
                                NULL, NULL, NULL, NULL
                                );
            #endif
            }
            return MMPR_IS_PLAYED;
        }

        case MMPR_NO_DATA:
        {
            //if (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat)
            {
                t_g_video_view.e_last_open_elm_ret = _MMP_VP_LAST_OPEN_ELM_RET_NODATA;
                mmp_mc_event_switch_context(
                                MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_vp_handle_invalid_file,
                                NULL, NULL, NULL, NULL
                                );
            }
            return MMPR_IS_PLAYED;
        }

        case MMPR_INTERNAL_ERROR:
        {
            //if (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat)
            {
                t_g_video_view.e_last_open_elm_ret = _MMP_VP_LAST_OPEN_ELM_RET_CORRUPT;
                mmp_mc_event_switch_context(
                                MMP_MC_CSC_RETRY_TYPE_ONCE,
                                _mmp_vp_handle_invalid_file,
                                NULL, NULL, NULL, NULL
                                );
            }
            return MMPR_IS_PLAYED;
        }

        case MMPR_IS_STOPPED:
        {
            return MMPR_IS_PLAYED;
        }

        case MMPR_IS_PLAYED:
        {
            _mmp_vp_update_status(TRUE);

            return MMPR_IS_PLAYED;
        }

        case MMPR_OK:
        {
            _mmp_vp_tb_icon_file_name(w2s_g_file, MMP_TB_SYNC_REPAINT);
            _mmp_vp_tb_icon_file_idx(TRUE); /* To fix DTV00081564 */
            a_menu_11_point_gain_update();
#if NEVER
            t_g_video_view.t_drm_type = e_divx_cert.t_drm_type;

            if((MMP_VE_DRM_TYPE_NORMAL != t_g_video_view.t_drm_type) &&
               (MMP_VP_STAT_ACTIVE == t_g_video_view.e_vp_stat))
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
        break;

        default:
            break;
    }

#ifdef _MMP_VP_DISP_LOAD_PROGRESS
    c_timer_start (t_g_video_view.h_timer_loading,
                   MMP_VP_TIMER_LOAD_PROG_PCT,
                   X_TIMER_FLAG_REPEAT,
                   _mmp_vp_timer_nfy_fct,
                   NULL);
    _mmp_vp_view_update_prog (0, TRUE);
    c_wgl_show (t_g_video_view.h_txt_loading, WGL_SW_NORMAL);
#endif

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_pause
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
static INT32 _mmp_vp_pause(VOID)
{
    INT32                       i4_ret = 0;

    i4_ret = video_engine_pause(t_g_video_view.pt_engine_inst);
    if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
    {
       DBG_LOG_PRINT(("----%s, %s, %d, Feature not support.----\r\n",
                    __FILE__,
                    __FUNCTION__,
                    __LINE__));
        return i4_ret;
    }

#if defined(APP_NET_DLNA_SUPPORT) && defined(APP_DMR_SUPPORT)
    if(a_mmp_dmr_is_active())
    {
        c_dmr_submit_player_status(PLAYER_MEDIATYPE_VIDEO, PLAYER_NFYCODE_PAUSE);
    }
#endif

    _mmp_vp_update_status(TRUE);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_blank
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
static INT32 _mmp_vp_blank(VOID)
{
    INT32                       i4_ret = 0;

#ifdef MMP_VP_BLANK_MUTE
    i4_ret = video_engine_blank(t_g_video_view.pt_engine_inst);
    if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
    {
       DBG_LOG_PRINT(("----%s, %s, %d, Feature not support.----\r\n",
                    __FILE__,
                    __FUNCTION__,
                    __LINE__));
        return i4_ret;
    }
#endif

    _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
    _mmp_vp_update_status(TRUE);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_stop
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
static INT32 _mmp_vp_stop(VOID)
{
    INT32 i4_ret;

    i4_ret = _mmp_vp_view_reset(FALSE, TRUE);
    if(MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = video_engine_stop(t_g_video_view.pt_engine_inst);
    if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
    {
        return i4_ret;
    }
    _mmp_vp_update_status(TRUE);

    a_menu_11_point_gain_update();

    return i4_ret;
}

#if 1
/*----------------------------------------------------------------------------
 * Name: _mmp_vp_next
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
static INT32 _mmp_vp_next(VOID)
{
    INT32 i4_ret = 0;
    MMP_VE_DIVX_CERT_T e_divx_cert;

#ifndef APP_CAST_TV_MMP
    if(_MMP_VP_OPTL_LST_STAT_SHOW==t_g_video_view.e_opt_stat)
    {
        a_optl_hide(t_g_video_view.h_opt_list);
        t_g_video_view.e_opt_stat = _MMP_VP_OPTL_LST_STAT_HIDE;
    }

    i4_ret = c_timer_start(t_g_video_view.h_timer_viewer,
                           MMP_VP_TIMER_VIERER_HIDE,
                           X_TIMER_FLAG_ONCE,
                           _mmp_vp_timer_nfy_fct,
                           NULL
                           );
    if (WGLR_OK != i4_ret)
    {
        MMP_DBG_ERROR(("c_timer_start() fail. i4_ret = %d.\r\n", i4_ret));
        return MMPR_FAIL;
    }

    if (t_g_video_view.b_crt_play_invalid_file)
    {
        c_timer_stop(t_g_video_view.h_timer_hide_msg);
        t_g_video_view.b_crt_play_invalid_file = FALSE;
    }

    _mmp_vp_view_reset(TRUE, TRUE);
    _mmp_vp_view_swap_filename(TRUE);
#endif
    i4_ret = video_engine_next(t_g_video_view.pt_engine_inst,&e_divx_cert);
    t_g_video_view.e_player_status = MMP_VE_PLAY_STAT_NEXT;
    a_menu_11_point_gain_update();

    if(MMPR_NOT_SUPPORT == i4_ret)
    {
    #ifdef APP_CAST_TV_MMP
        mmp_mc_list_next(MMP_GROUND_MODE_FORE);
    #else
        t_g_video_view.e_last_open_elm_ret = _MMP_VP_LAST_OPEN_ELM_RET_FAILED;
        mmp_mc_event_switch_context(
                       MMP_MC_CSC_RETRY_TYPE_ONCE,
                       _mmp_vp_handle_invalid_file,
                       NULL, NULL, NULL, NULL
                       );
    #endif
        return MMPR_IS_PLAYED;
    }
    else if(MMPR_NO_DATA == i4_ret)
    {
        t_g_video_view.e_last_open_elm_ret = _MMP_VP_LAST_OPEN_ELM_RET_NODATA;
        mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_ONCE,
                        _mmp_vp_handle_invalid_file,
                        NULL, NULL, NULL, NULL
                        );
        return MMPR_IS_PLAYED;
    }
    else if(MMPR_INTERNAL_ERROR == i4_ret)
    {
        t_g_video_view.e_last_open_elm_ret = _MMP_VP_LAST_OPEN_ELM_RET_CORRUPT;
        mmp_mc_event_switch_context(
                        MMP_MC_CSC_RETRY_TYPE_ONCE,
                        _mmp_vp_handle_invalid_file,
                        NULL, NULL, NULL, NULL
                        );
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

#ifdef _MMP_VP_DISP_LOAD_PROGRESS
     c_timer_start (t_g_video_view.h_timer_loading,
                    MMP_VP_TIMER_LOAD_PROG_PCT,
                    X_TIMER_FLAG_REPEAT,
                    _mmp_vp_timer_nfy_fct,
                    NULL);
     _mmp_vp_view_update_prog (0, TRUE);
     c_wgl_show (t_g_video_view.h_txt_loading, WGL_SW_NORMAL);
#endif

    return MMPR_OK ;
}
#endif
/*----------------------------------------------------------------------------
 * Name: mmp_vp_cmd_do
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
INT32 mmp_vp_cmd_do(MMP_FP_SHOW_CMD_ID_T e_cmd_id, VOID* pv_cmd_param)
{
    INT32   i4_ret = MMPR_OK;

    DBG_LOG_PRINT(("[MMP][%s %d] show cmd <=%s=> \n",__FUNCTION__,__LINE__,SHOW_CMD(e_cmd_id)));

    switch (e_cmd_id)
    {
        case MMP_FP_SHOW_CMD_ID_START:
        {
            /* init before play. */
            t_g_video_view.ui8_position = 0;

            i4_ret = _mmp_vp_play();
            _mmp_vp_update_pos(NULL, NULL, NULL, NULL);
            if(MMPR_OK != i4_ret && MMPR_IS_PLAYED != i4_ret)
            {
                 MMP_DBG_ERROR(("_mmp_vp_play() fail. i4_ret = %d.\r\n", i4_ret));
            }
            _mmp_vp_update_play_status();
            MMP_FP_PRESENT_MODE_T       t_present_mode = MMP_FP_PRESENT_MODE_FULL;

            if (MMPR_OK == mmp_mc_list_get_play_present_mode(&t_present_mode) &&
                MMP_FP_PRESENT_MODE_FULL == t_present_mode)
            {
                _mmp_vp_view_activate(&t_g_video_view);
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_PAUSE:
        {
            BOOL b_mute = (BOOL)(UINT32)pv_cmd_param;

            if (TRUE == b_mute)
            {
                i4_ret = _mmp_vp_blank();
                return MMPR_OK;
            }
            else
            {
                i4_ret = _mmp_vp_pause();
            }

            if(MMPR_OK != i4_ret && MMPR_IS_PAUSED != i4_ret)
            {
                 MMP_DBG_ERROR(("_mmp_vp_pause() fail. i4_ret = %d.\r\n", i4_ret));
            }
            _mmp_vp_update_play_status();
        }
        break;

        case MMP_FP_SHOW_CMD_ID_FAST_FORWARD:
        case MMP_FP_SHOW_CMD_ID_FAST_REWIND:
        case MMP_FP_SHOW_CMD_ID_SLOW_FORWARD:
        case MMP_FP_SHOW_CMD_ID_SLOW_REWIND:
        {
            i4_ret = _mmp_vp_do_next_speed(e_cmd_id);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("Set speed cmd %d fail: %d\r\n", e_cmd_id, i4_ret));
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_STOP:
        {
            i4_ret = _mmp_vp_stop();
            if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
            {
                 MMP_DBG_ERROR(("_mmp_vp_stop() fail. i4_ret = %d.\r\n", i4_ret));
            }
        }
        break;
        case MMP_FP_SHOW_CMD_ID_STOPED:
        {
            _mmp_vp_update_play_status();
            break;
        }
        case MMP_FP_SHOW_CMD_ID_ACTIVATE:
        case MMP_FP_SHOW_CMD_ID_PREVIEW_ACTIVATE:
        {
            i4_ret = (MMP_FP_SHOW_CMD_ID_ACTIVATE == e_cmd_id) ? _mmp_vp_view_activate(&t_g_video_view) : _mmp_vp_preview_activate((MMP_FP_PREVIEW_INFO_T*)pv_cmd_param);
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("_mmp_vp_preview_activate() fail. i4_ret = %d.\r\n", i4_ret));
                return i4_ret;
            }
            c_wgl_set_visibility(t_g_video_view.h_frm_main,WGL_SW_NORMAL);
        }
        break;
        case MMP_FP_SHOW_CMD_ID_INACTIVATE:
        case MMP_FP_SHOW_CMD_ID_PREVIEW_INACTIVATE:
        {
            if(TRUE == (BOOL)(UINT32)pv_cmd_param)
            {
                i4_ret = video_engine_stop(t_g_video_view.pt_engine_inst);
                if(MMPR_OK != i4_ret && MMPR_IS_STOPPED != i4_ret)
                {
                     MMP_DBG_ERROR(("video_engine_stop() fail. i4_ret = %d.\r\n", i4_ret));
                     return i4_ret;
                }
            }

            i4_ret = (MMP_FP_SHOW_CMD_ID_INACTIVATE == e_cmd_id) ? _mmp_vp_view_inactive() : _mmp_vp_preview_inactivate();
            if(MMPR_OK != i4_ret)
            {
                MMP_DBG_ERROR(("_mmp_vp_preview_inactivate() fail. i4_ret = %d.\r\n", i4_ret));
                return i4_ret;
            }
        }
        break;

        case MMP_FP_SHOW_CMD_ID_NEXT:
        case MMP_FP_SHOW_CMD_ID_NEXT_EX:
        {
            if(MMP_FP_SHOW_CMD_ID_NEXT == e_cmd_id)
                t_g_video_view.ui4_mmc_ver = (UINT32)pv_cmd_param;
            else
                t_g_video_view.ui4_mmc_ver = ((MMP_FP_SHOW_NEXT_PARAM_T*)pv_cmd_param)->ui4_ver;


            i4_ret =_mmp_vp_next();
            if(MMPR_OK != i4_ret)
            {
                 MMP_DBG_ERROR(("_mmp_vp_next() fail. i4_ret = %d.\r\n", i4_ret));
            }

        }
        break;

        default:
        {
            i4_ret = MMPR_INV_ARG;
            MMP_DBG_ERROR(("The argument e_cmd_id of mmp_vp_cmd_do() is invalid.\r\n"));
        }
        break;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_open
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_open(
                    const CHAR*                     ps_filename,
                    mmp_fp_info_nfy_fct             pf_nfy,
                    VOID*                           pv_tag,
                    VOID**                          ppv_info_inst
                    )
{
    return mmp_ve_info_open(
                    t_g_video_view.pt_engine_inst,
                    ps_filename,
                    pf_nfy,
                    pv_tag,
                    (MMP_VE_INFO_INST_PTR_T*)ppv_info_inst
                    );
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_close
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_close(
                    VOID*                           pv_info_inst
                    )
{
    return mmp_ve_info_close(
                    t_g_video_view.pt_engine_inst,
                    pv_info_inst
                    );
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_get
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_get(
                    VOID*                           pv_info_inst,
                    MMP_FP_INFO_TYPE_T              e_type,
                    SIZE_T*                         pz_size,
                    UINT8*                          pui1_buf
                    )
{
    #define _MMP_VP_INFO_MAX_STR_LEN (128)

    CHAR sz_info[_MMP_VP_INFO_MAX_STR_LEN] = {0};
    UTF16_T w2s_info[_MMP_VP_INFO_MAX_STR_LEN] = {0};
    SIZE_T z_buf_len = 0;
    MM_TM_T t_date;
    UINT64 ui8_duration;
    UINT64 ui8_file_size;
    UINT8 ui1_hh, ui1_mm, ui1_ss;
    INT32 i4_ret;

    if(MMP_FP_INFO_TYPE_DATE == e_type)
    {
        z_buf_len = sizeof(MM_TM_T);

        i4_ret = mmp_ve_info_get(
                        t_g_video_view.pt_engine_inst,
                        pv_info_inst,
                        e_type,
                        &z_buf_len,
                        &t_date
                        );
        if(MMPR_OK != i4_ret || 0 == t_date.ui2_year || 1904 == t_date.ui2_year)
        {
            c_strncpy(sz_info, "-", _MMP_VP_INFO_MAX_STR_LEN);
        }
        else
        {
            c_sprintf(sz_info, "%04u-%02u-%02u %02u:%02u:%02u",
                      t_date.ui2_year, t_date.ui1_month, t_date.ui1_day,
                      t_date.ui1_hour, t_date.ui1_min, t_date.ui1_sec);
        }

        c_uc_ps_to_w2s(sz_info, w2s_info, _MMP_VP_INFO_MAX_STR_LEN);
    }
    else if(MMP_FP_INFO_TYPE_DURATION == e_type)
    {
        z_buf_len = sizeof(UINT64);

        i4_ret = mmp_ve_info_get(
                        t_g_video_view.pt_engine_inst,
                        pv_info_inst,
                        e_type,
                        &z_buf_len,
                        &ui8_duration
                        );
        MMPR_LOG_ON_FAIL(i4_ret);
        DBG_LOG_PRINT(("[MMP][%s %d]duration = %llu\n",__FUNCTION__,__LINE__, ui8_duration));
        if(MMPR_OK != i4_ret || ui8_duration == 0)
        {
            //c_strncpy(sz_info, "-", _MMP_VP_INFO_MAX_STR_LEN);
            ui1_hh = ui1_mm = ui1_ss = 0;
            c_sprintf(sz_info, "%02u:%02u:%02u", ui1_hh, ui1_mm, ui1_ss);
        }
        else
        {
            _convert_time_day_sec_to_hh_mm_ss((UINT32)ui8_duration, &ui1_hh, &ui1_mm, &ui1_ss);
            c_sprintf(sz_info, "%02u:%02u:%02u", ui1_hh, ui1_mm, ui1_ss);
        }

        c_uc_ps_to_w2s(sz_info, w2s_info, _MMP_VP_INFO_MAX_STR_LEN);
    }
    else if(MMP_FP_INFO_TYPE_SIZE == e_type)
    {
        z_buf_len = sizeof(UINT64);

        i4_ret = mmp_ve_info_get(
                        t_g_video_view.pt_engine_inst,
                        pv_info_inst,
                        e_type,
                        &z_buf_len,
                        &ui8_file_size
                        );
        if (MMPR_OK != i4_ret || 0 == ui8_file_size)
        {
            c_strncpy(sz_info, "-", _MMP_VP_INFO_MAX_STR_LEN);
        }
        else if (1024 * 1024 * 1024 <= ui8_file_size)
        {
            c_sprintf(sz_info, "%.2fG", (ui8_file_size * 1.0) / (1024 * 1024 * 1024));
        }
        else if (1024 * 1024 <= ui8_file_size)
        {
            c_sprintf(sz_info, "%.2fM", (ui8_file_size * 1.0) / (1024 * 1024));
        }
        else if (1024 <= ui8_file_size)
        {
            c_sprintf(sz_info, "%.2fK", (ui8_file_size * 1.0) / (1024));
        }
        else
        {
            c_sprintf(sz_info, "%dB", ui8_file_size);
        }

        c_uc_ps_to_w2s(sz_info, w2s_info, _MMP_VP_INFO_MAX_STR_LEN);
    }
    else
    {
        z_buf_len = _MMP_VP_INFO_MAX_STR_LEN;

        i4_ret = mmp_ve_info_get(
                        t_g_video_view.pt_engine_inst,
                        pv_info_inst,
                        e_type,
                        &z_buf_len,
                        w2s_info
                        );
        if(MMPR_OK != i4_ret || 0 == z_buf_len)
        {
            c_strncpy(sz_info, "-", _MMP_VP_INFO_MAX_STR_LEN);
            c_uc_ps_to_w2s(sz_info, w2s_info, _MMP_VP_INFO_MAX_STR_LEN);
        }
    }

    z_buf_len = (c_uc_w2s_strlen(w2s_info) + 1) * 2;
    if (z_buf_len < *pz_size)
    {
        if (_MMP_VP_INFO_MAX_STR_LEN > z_buf_len)
        {
            c_memcpy(pui1_buf, w2s_info, z_buf_len);
        }
    }
    else
    {
        if (_MMP_VP_INFO_MAX_STR_LEN > *pz_size)
        {
            c_memcpy(pui1_buf, w2s_info, *pz_size);
        }
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_set
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_set(
                    VOID*                           pv_info_inst,
                    MMP_FP_INFO_TYPE_T              e_type,
                    SIZE_T*                         pz_size,
                    UINT8*                          pui1_buf
                    )
{
    return  mmp_ve_info_set(
                    t_g_video_view.pt_engine_inst,
                    pv_info_inst,
                    e_type,
                    pz_size,
                    pui1_buf
                    );
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_cmd_do(
                    VOID*                           pv_info_inst,
                    MMP_FP_INFO_CMD_ID_T            e_cmd,
                    VOID*                           pv_cmd_param
                    )
{
    return mmp_ve_info_cmd_do(
                    t_g_video_view.pt_engine_inst,
                    pv_info_inst,
                    e_cmd,
                    pv_cmd_param
                    );
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_cmd_res_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_cmd_res_init(VOID)
{
    return mmp_ve_info_cmd_res_init(
                    t_g_video_view.pt_engine_inst
                    );
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_cmd_res_reset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_cmd_res_reset(VOID)
{
    return mmp_ve_info_cmd_res_reset(
                    t_g_video_view.pt_engine_inst
                    );
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_cmd_res_deinit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_cmd_res_deinit(VOID)
{
    return mmp_ve_info_cmd_res_deinit(
                    t_g_video_view.pt_engine_inst
                    );
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_hdlr_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_hdlr_init(
                    MMP_FP_INFO_HDLR_INIT_PARAM_T*  pt_param,
                    VOID**                          ppv_info_hdlr_inst
                    )
{
    INT32                   i4_ret;
    ISO_639_LANG_T          s639_lang;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<MMP VP>Can't init lanugage \r\n"));
        t_g_video_view.ui2_lang = MLM_MMP_LANG_ENG;
    }
    else
    {
        t_g_video_view.ui2_lang = mlm_mmp_s639_to_langidx(s639_lang);
    }

    if (TRUE == t_g_video_view.t_info_hdlr.b_init)
    {
        return MMPR_OK;
    }

    switch (pt_param->e_ui_type)
    {
        case MMP_FP_INFO_HDLR_UI_TYPE_TM_FOCUS:
            e_ui_type = MMP_COM_FP_INFO_UI_TYPE_TM;
            break;

        case MMP_FP_INFO_HDLR_UI_TYPE_LM_FOCUS:
            e_ui_type = MMP_COM_FP_INFO_UI_TYPE_LM;
            break;

        default:
            return MMPR_NOT_SUPPORT;
    }

    i4_ret = mmp_com_ui_focus_info_frm_create(
                        pt_param->h_parent,
                        e_ui_type,
                        MMP_COM_INFO_FP_TYPE_VP,
                        (VOID *)&(t_g_video_view.pv_video_info_inst));
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }
    *ppv_info_hdlr_inst = (t_g_video_view.pv_video_info_inst);

    i4_ret=mmp_com_ui_fp_focus_set_elem_num(
                        *ppv_info_hdlr_inst,
                        MMP_COM_FP_TYPE_VP,
                        FALSE
                        );
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    _mmp_vp_info_lst_set_text();

    t_g_video_view.t_info_hdlr.b_init = TRUE;

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_hdlr_deinit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_hdlr_deinit(
                    VOID*                           pv_info_hdlr_inst
                    )
{
    INT32 i4_ret;

    if (!t_g_video_view.t_info_hdlr.b_init)
    {
        return MMPR_OK;
    }

    i4_ret = _mmp_vp_ib_hide();
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = mmp_com_ui_focus_info_frm_destroy(
                    e_ui_type,
                    MMP_COM_INFO_FP_TYPE_VP,
                    pv_info_hdlr_inst
                    );
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    c_timer_stop(t_g_video_view.h_timer_timeout);
    c_timer_stop(t_g_video_view.h_timer_hide_msg);

    t_g_video_view.t_info_hdlr.b_init = FALSE;

    return MMPR_OK;
}

static INT32 _video_player_get_audio_fmt_info(
                    MMP_VE_PLAY_INST_PTR_T          pt_play_inst,     /* in  */
                    ASH_AUDIO_INFO_T*            pt_audio_info       /* out */
                    )
{
    _MMP_VE_PLAY_INST_PTR_T pt_this = (_MMP_VE_PLAY_INST_PTR_T)pt_play_inst;
    INT32 i4_ret = 0;

    MMP_ASSERT(NULL != pt_this && NULL != pt_audio_info);

    /* default values */
    c_memset(pt_audio_info, 0, sizeof(ASH_AUDIO_INFO_T));

    /* update audio channels info */
    i4_ret = c_svctx_get_audio_info(
                    pt_this->h_svctx_hdl,
                    pt_audio_info
                    );
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _video_player_get_audio_format_info(UTF16_T* pw2s_audio_format)
{
    ASH_AUDIO_INFO_T t_audio_info;
    INT32       i4_ret = 0;

    i4_ret = _video_player_get_audio_fmt_info(t_g_video_view.pt_engine_inst, &t_audio_info);

    switch (t_audio_info.e_aud_fmt)
    {
        case ASH_AUDIO_FMT_MPEG:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"MPEG");
        }
            break;

        case ASH_AUDIO_FMT_AC3:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"Dolby Audio-DD");
        }
            break;

        case ASH_AUDIO_FMT_E_AC3:
        {
            SCC_AUD_IEC_TYPE_T        e_iec_type;
            i4_ret = a_mmp_get_scc_audio_type_out(&e_iec_type);
            MMPR_LOG_ON_FAIL(i4_ret);
            if(e_iec_type != SCC_AUD_IEC_CFG_DDP_ATMOS || i4_ret != MMPR_OK)
            {
                c_uc_w2s_strcpy(pw2s_audio_format, L"Dolby Audio-DD+");
            }
            else
            {
                c_uc_w2s_strcpy(pw2s_audio_format, L"Dolby Atmos");
            }
        }
            break;

        case ASH_AUDIO_FMT_PCM:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"PCM");
        }
            break;

        case ASH_AUDIO_FMT_MP3:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"MP3");
        }
            break;

        case ASH_AUDIO_FMT_AAC:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"AAC");
        }
            break;

        case ASH_AUDIO_FMT_DTS:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"DTS");
        }
            break;

        case ASH_AUDIO_FMT_WMA:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"WMA");
        }
            break;

        case ASH_AUDIO_FMT_RA:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"RA");
        }
            break;

        case ASH_AUDIO_FMT_HDCD:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"HDCD");
        }
            break;

        case ASH_AUDIO_FMT_MLP:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"MLP");
        }
            break;

        case ASH_AUDIO_FMT_MTS:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"MTS");
        }
            break;

        case ASH_AUDIO_FMT_EU_CANAL_PLUS:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"CANAL PLUS");
        }
            break;

        case ASH_AUDIO_FMT_TV_SYS:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"TV SYS");
        }
            break;

        case ASH_AUDIO_FMT_COOK:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"COOK");
        }
            break;

        case ASH_AUDIO_FMT_VORBIS:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"VORBIS");
        }
            break;

        case ASH_AUDIO_FMT_HE_AAC:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"HEAAC");
        }
            break;

        case ASH_AUDIO_FMT_HE_AAC_V2:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"HEAACV2");
        }
            break;

        case ASH_AUDIO_FMT_WMAPRO:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"WMAPRO");
        }
            break;

        case ASH_AUDIO_FMT_WMALOSSLESS:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"WMALOSSLESS");
        }
            break;

        case ASH_AUDIO_FMT_AMR:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"AMR");
        }
            break;

        case ASH_AUDIO_FMT_AWB:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"AWB");
        }
            break;

        case ASH_AUDIO_FMT_FLAC:
        {
            c_uc_w2s_strcpy(pw2s_audio_format, L"FLAC");
        }
            break;

        default:
            break;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_info_hdlr_cmd_do
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_info_hdlr_cmd_do(
                    VOID*                           pv_info_hdlr_inst,
                    MMP_FP_INFO_HDLR_CMD_ID_T       e_cmd,
                    VOID*                           pv_cmd_param
                    )
{
    INT32       i4_ret;
    MMP_KEY_INFO*   pt_key_info = (MMP_KEY_INFO*)pv_cmd_param;

    switch(e_cmd)
    {
        case MMP_FP_INFO_HDLR_CMD_ID_SHOW:
        {
            MMP_PLAY_STATE_T e_fg_state = MMP_PLAY_STATE_CLOSED;
            i4_ret = mmp_mc_file_get_status(MMP_GROUND_MODE_FORE,&e_fg_state);
            MMPR_LOG_ON_FAIL(i4_ret);
            DBG_LOG_PRINT(("_mmp_vp_info_hdlr_cmd_do MMP_FP_INFO_HDLR_CMD_ID_SHOW status = %d\n",e_fg_state));
            if(MMP_PLAY_STATE_CLOSED != e_fg_state)
            {
                mmp_com_ui_focus_info_frm_active(pv_info_hdlr_inst,
                                                 MMP_COM_FP_TYPE_VP,
                                                 TRUE);
            }
        }
        break;

        case MMP_FP_INFO_HDLR_CMD_ID_HIDE:
        {
            mmp_com_ui_focus_info_frm_inactive(
                    pv_info_hdlr_inst,
                    (BOOL)(UINT32)pv_cmd_param
                    );
        }
        break;

        case MMP_FP_INFO_HDLR_CMD_ID_UPDATE_FOCUS_ITEM:
        {
            SIZE_T          z_buff_len = MMP_VP_INFO_MAX_STR_LEN;
            GL_SIZE_T       t_size;
            CHAR            sz_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
            CHAR*           psz_file_name;
            UTF16_T         ws_info[MMP_VP_INFO_MAX_STR_LEN+1] = {0};
           //DBG_LOG_PRINT(("_mmp_vp_info_hdlr_cmd_do MMP_FP_INFO_HDLR_CMD_ID_UPDATE_FOCUS_ITEM \n"));

            /* file name */
            {
                i4_ret = video_engine_get_dtl_info( t_g_video_view.pt_engine_inst,
                                                    MMP_VE_INFO_ID_NAME,
                                                    ws_info,
                                                    &z_buff_len
                                                    );

                if (MMPR_OK != i4_ret || 0 == z_buff_len)
                {
                    c_uc_w2s_strcpy(ws_info, (UTF16_T*)L"");
                }
                else/* get correct file name. */
                {
                    c_uc_w2s_to_ps(ws_info, sz_info, MMP_VP_INFO_MAX_STR_LEN);

                    /* remove prefix. */
                    psz_file_name = mmp_be_get_filtered_item_name(sz_info);

                    c_uc_ps_to_w2s(psz_file_name, ws_info, MMP_VP_INFO_MAX_STR_LEN);
                }
              //  c_uc_w2s_to_ps(ws_info,ps,MMP_VP_INFO_MAX_STR_LEN);
             //   DBG_LOG_PRINT(("[MMP][%s %d] file name : %s,ret = %d\n",__FUNCTION__,__LINE__,ps,i4_ret));
                mmp_com_ui_fp_set_focus_info( pv_info_hdlr_inst,
                                              MMP_VP_FOCUS_INFO_ID_NAME,
                                              MMP_COM_UI_FP_DATA_W2S,
                                              (VOID*)ws_info,
                                              FALSE
                                              );
            }

        }
            break;

        case MMP_FP_INFO_HDLR_CMD_ID_RESET:
        {
            /* title */
            mmp_com_ui_fp_set_focus_info(
                    pv_info_hdlr_inst,
                    MMP_VP_FOCUS_INFO_ID_NAME,
                    MMP_COM_UI_FP_DATA_W2S,
                    (VOID*)NULL,
                    FALSE
                    );

            /* date */
            mmp_com_ui_fp_set_focus_info(
                    pv_info_hdlr_inst,
                    MMP_VP_FOCUS_INFO_ID_TIME,
                    MMP_COM_UI_FP_DATA_W2S,
                    (VOID*)NULL,
                    FALSE
                    );
#if NEVER
            /* duration */
            mmp_com_ui_fp_set_focus_info(
                    pv_info_hdlr_inst,
                    MMP_VP_FOCUS_INFO_ID_DURATION,
                    MMP_COM_UI_FP_DATA_W2S,
                    (VOID*)NULL,
                    FALSE
                    );
#endif
            /* file size */
            mmp_com_ui_fp_set_focus_info(
                    pv_info_hdlr_inst,
                    MMP_VP_FOCUS_INFO_ID_SIZE,
                    MMP_COM_UI_FP_DATA_W2S,
                    (VOID*)NULL,
                    TRUE
                    );
#if NEVER
            mmp_com_ui_fp_set_focus_info(
                    pv_info_hdlr_inst,
                    MMP_VP_FOCUS_INFO_ID_AUDIO_FMT,
                    MMP_COM_UI_FP_DATA_W2S,
                    (VOID*)NULL,
                    FALSE
                    );
#endif
#if 0
            /* repaint */
            mmp_com_ui_focus_info_frm_repaint(
                    pv_info_hdlr_inst,
                    MMP_INFO_SYNC_REPAINT);
#endif
        }
        break;
        case MMP_FP_INFO_HDLR_CMD_ID_UPDATE_PLAY_ITEM:
                    mmp_com_ui_focus_info_frm_repaint(
                    pv_info_hdlr_inst,
                    MMP_INFO_NON_REPAINT
                    );
             break;
        case MMP_FP_INFO_HDLR_CMD_ID_HANDLE_KEY:
        {
            _mmp_vp_main_frm_proc_fct(NULL_HANDLE,
                                     pt_key_info->ui4_keystatus,
                                     (VOID*)pt_key_info->ui4_keycode,
                                     NULL);
        }
        default:
            break;
    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_mmp_video_player_register
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID a_mmp_video_player_register(VOID)
{
    MMP_FILE_PLAYER_INTF_T t_intf;
    MMP_MC_FILE_PLAYER_PROPERTY_T t_prop;
    INT32 i4_ret;

    c_memset(&t_intf, 0, sizeof(MMP_FILE_PLAYER_INTF_T));

    t_intf.t_show_intf.pf_open           = _mmp_vp_open;
    t_intf.t_show_intf.pf_close          = _mmp_vp_close;
    t_intf.t_show_intf.pf_next_preload   = _mmp_vp_next_preload;
    t_intf.t_show_intf.pf_next_attr_set  = _mmp_vp_next_attr_set;
    t_intf.t_show_intf.pf_attr_set       = _mmp_vp_attr_set;
    t_intf.t_show_intf.pf_cmd_do         =  mmp_vp_cmd_do;

    t_intf.t_media_intf.pf_init          = _mmp_vp_init;
    t_intf.t_media_intf.pf_deinit        = _mmp_vp_deinit;
    t_intf.t_media_intf.pf_handle_msg    = _mmp_vp_handle_msg;
    t_intf.t_media_intf.pf_is_type_of    = _mmp_vp_is_type_of;

    t_intf.t_info_intf.pf_open           = _mmp_vp_info_open;
    t_intf.t_info_intf.pf_close          = _mmp_vp_info_close;
    t_intf.t_info_intf.pf_get            = _mmp_vp_info_get;
    t_intf.t_info_intf.pf_set            = _mmp_vp_info_set;
    t_intf.t_info_intf.pf_cmd_do         = _mmp_vp_info_cmd_do;
    t_intf.t_info_intf.pf_cmd_res_init   = _mmp_vp_info_cmd_res_init;
    t_intf.t_info_intf.pf_cmd_res_reset  = _mmp_vp_info_cmd_res_reset;
    t_intf.t_info_intf.pf_cmd_res_deinit = _mmp_vp_info_cmd_res_deinit;

    t_intf.t_info_hdlr_intf.pf_init      = _mmp_vp_info_hdlr_init;
    t_intf.t_info_hdlr_intf.pf_deinit    = _mmp_vp_info_hdlr_deinit;
    t_intf.t_info_hdlr_intf.pf_cmd_do    = _mmp_vp_info_hdlr_cmd_do;

    t_prop.e_type = MMP_MEDIA_TYPE_VIDEO;
    t_prop.e_excl_type = MMP_MEDIA_TYPE_AUDIO;

    i4_ret = mmp_mc_reg_file_player(&t_intf, &t_prop);
    if(MMPR_OK != i4_ret)
    {
       DBG_LOG_PRINT(("mmp_mc_reg_file_player() returns %d.\n", i4_ret));
        MMP_ASSERT (FALSE);
    }
}

INT32 a_mmp_vpfordmr_get_pos_and_dur(UINT64* pu8_pos_time, UINT64* pu8_dur_time)
{
    *pu8_pos_time = t_g_video_view.ui8_position;


    if(0 == t_g_video_view.ui8_duration)
    {
        *pu8_dur_time = 0;
        return MMPR_OK;
    }

     if(_MMP_VP_PROG_BAR_TYPE_TIME != t_g_video_view.e_prog_bar_type)
    {
         *pu8_dur_time = 0;
    }
    else
    {
         *pu8_dur_time = t_g_video_view.ui8_duration;
    }

    return MMPR_OK;
}

INT32 a_mmp_vpfordmr_seek(UINT64 u8_pos)
{
    INT32 i4_ret = 0;

    if(0 == t_g_video_view.ui8_duration)
    {
        return MMPR_FAIL;
    }

    if(_MMP_VP_PROG_BAR_TYPE_TIME == t_g_video_view.e_prog_bar_type)
    {
        if(u8_pos > t_g_video_view.ui8_duration)
        {
            return MMPR_FAIL;
        }
    }

    if(t_g_video_view.e_player_status != MMP_VE_PLAY_STAT_PLAY &&
       t_g_video_view.e_player_status != MMP_VE_PLAY_STAT_PAUSE &&
       t_g_video_view.e_player_status != MMP_VE_PLAY_STAT_FAST_FWD &&
       t_g_video_view.e_player_status != MMP_VE_PLAY_STAT_FAST_RWD)
    {
        MMP_DBG_INFO(("[JY][%d:][Play status not support seek] \n", __FUNCTION__));
        return MMPR_FAIL;
    }

    if(!video_engine_seek_enable(t_g_video_view.pt_engine_inst))
    {
        return MMPR_FAIL;
    }

#ifdef APP_MENU_MMP_COEXIST
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == mmp_main_get_ap_status())
    {
        a_amb_pause_app(MENU_NAME);
    }
#endif

    t_g_video_view.ui8_position= u8_pos;

    i4_ret = video_engine_seek(t_g_video_view.pt_engine_inst, (UINT32)t_g_video_view.ui8_position);
    MMP_DBG_INFO(("[JY][%s][POS]%lld[RET]%d \n", __FUNCTION__, u8_pos, i4_ret));

    return MMPR_OK;
}

INT32 a_mmp_vpfordmr_fast_forward(VOID)
{
    INT32 i4_ret = 0;

    MMP_PL_CMD_TRICK_PARAM_T t_trick_param;

    t_trick_param.e_mode = MMP_GROUND_MODE_FORE;
    t_trick_param.e_option = MMP_PL_CMD_TRICK_OPTION_RESUME_AFTER_TRICK;

    i4_ret = mmp_mc_list_fast_forward(&t_trick_param);
    MMP_DBG_INFO(("[JY][%s][RET][%d] \n", __FUNCTION__, i4_ret));

    if(MMPR_OK != i4_ret && MMPR_IS_FAST_FORWARDED != i4_ret)
    {
       DBG_LOG_PRINT(("<MMP>mmp_mc_list_step_forward %s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}

INT32 a_mmp_vpfordmr_fast_rewind(VOID)
{
    INT32 i4_ret = 0;
    MMP_PL_CMD_TRICK_PARAM_T t_trick_param;

    t_trick_param.e_mode = MMP_GROUND_MODE_FORE;
    t_trick_param.e_option = MMP_PL_CMD_TRICK_OPTION_RESUME_AFTER_TRICK;

    // DTV00356449
    i4_ret = mmp_mc_list_fast_rewind(&t_trick_param);
    MMP_DBG_INFO(("[JY][%s][RET][%d] \n", __FUNCTION__, i4_ret));

    if(MMPR_OK != i4_ret && MMPR_IS_FAST_REWINDED != i4_ret)
    {
       DBG_LOG_PRINT(("<MMP>mmp_mc_list_step_rewind %s:%d:%d\r\n", __FILE__, __LINE__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}

static BOOL  _video_player_is_playing(VOID)
{
    switch (t_g_video_view.e_player_status)
    {
        case MMP_VE_PLAY_STAT_PLAY:
        case MMP_VE_PLAY_STAT_PAUSE:
        case MMP_VE_PLAY_STAT_FAST_FWD:
        case MMP_VE_PLAY_STAT_FAST_RWD:
        case MMP_VE_PLAY_STAT_SLOW_FWD:
        case MMP_VE_PLAY_STAT_SLOW_RWD:
            return TRUE;

        default:
            break;
    }
    return FALSE;
}

static UINT8 _video_play_convert_speed(MM_SPEED_TYPE_T e_speed)
{
    switch(e_speed)
    {
        case MM_SPEED_TYPE_PAUSE:
            return 0;
        case MM_SPEED_TYPE_FORWARD_1X:
        case MM_SPEED_TYPE_REWIND_1X:
            return 1;
        case MM_SPEED_TYPE_REWIND_1_DIV_2X:
        case MM_SPEED_TYPE_FORWARD_1_DIV_2X:
        case MM_SPEED_TYPE_FORWARD_2X:
        case MM_SPEED_TYPE_REWIND_2X:
            return 2;
        case  MM_SPEED_TYPE_REWIND_1_DIV_4X:
        case MM_SPEED_TYPE_FORWARD_1_DIV_4X:
        case MM_SPEED_TYPE_FORWARD_4X:
        case MM_SPEED_TYPE_REWIND_4X:
            return 4;
        case MM_SPEED_TYPE_REWIND_1_DIV_8X:
        case MM_SPEED_TYPE_FORWARD_1_DIV_8X:
        case MM_SPEED_TYPE_FORWARD_8X:
        case MM_SPEED_TYPE_REWIND_8X:
            return 8;
        case MM_SPEED_TYPE_REWIND_1_DIV_16X:
        case MM_SPEED_TYPE_FORWARD_1_DIV_16X:
        case MM_SPEED_TYPE_FORWARD_16X:
        case MM_SPEED_TYPE_REWIND_16X:
            return 16;
        case MM_SPEED_TYPE_REWIND_1_DIV_32X:
        case MM_SPEED_TYPE_FORWARD_1_DIV_32X:
        case MM_SPEED_TYPE_FORWARD_32X:
        case MM_SPEED_TYPE_REWIND_32X:
            return 32;
        case MM_SPEED_TYPE_REWIND_64X:
        case MM_SPEED_TYPE_FORWARD_64X:
            return 64;
        case MM_SPEED_TYPE_REWIND_128X:
        case MM_SPEED_TYPE_FORWARD_128X:
            return 128;
        default:
                break;
    }
    return 0xFF;
}

INT32 a_mmp_vpfordmr_play_with_speed(MM_SPEED_TYPE_T e_speed)
{
#if 1
    INT32           i4_ret = MMPR_OK;

    if (_video_player_is_playing())
    {
        i4_ret = video_engine_set_speed(t_g_video_view.pt_engine_inst, e_speed);
    }
    else
    {
        DBG_LOG_PRINT(("[vid pl] not playing yet!\n"));
        return MMPR_NOT_SUPPORT;
    }

    if(MMPR_OK > i4_ret)
    {
        _mmp_vp_not_support();
        return i4_ret;
    }

    t_g_video_view.ui1_step = _video_play_convert_speed(e_speed);
    _mmp_vp_update_status(TRUE);

    if (MMP_VP_VIEWER_HIDE == t_g_video_view.e_viewer_status)
    {
        _mmp_vp_view_toggle_viewer(TRUE);
    }
#endif
    return MMPR_OK;
}


/******************************************************************************
                               Video Player Viewer End
*******************************************************************************/

