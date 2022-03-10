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
#include "mmp_common_ui_toolbar.h"
#include "c_fe.h"
#include "mmp/util/mmp_util.h"

#define MMP_TB_STRING_SIZE     128

#define MMP_TB_FORMAT_DURATION "%02u:%02u:%02u"
#define MMP_TB_FORMAT_ZOOM     "%dX"
#define MMP_TB_FORMAT_FF_FR    "%dx"
#define MMP_TB_FORMAT_PLAY     "1/%dx"
#define MMP_TB_FORMAT_SUB      "%u/%u"
#define MMP_TB_FORMAT_MTS      "%u/%u"

#include "u_irrc_btn_def.h"

typedef enum
{
    MMP_TB_FORMAT_TYPE_DURATION = 0,
    MMP_TB_FORMAT_TYPE_ZOOM,
    MMP_TB_FORMAT_TYPE_FF_FR,
    MMP_TB_FORMAT_TYPE_PLAY,
    MMP_TB_FORMAT_TYPE_SUB,
    MMP_TB_FORMAT_TYPE_MTS,
    MMP_TB_FORMAT_TYPE_TOTAL_COUNT
} MMP_TB_FORMAT_TYPE_T;

typedef enum
{
    MMP_TOOLBAR_HIDE = 0,
    MMP_TOOLBAR_SHOW
} MMP_TOOLBAR_STATUS_T;

typedef INT32 (*mmp_common_ui_toolbar_cmd_do_fct)(
                           MMP_TB_CMD_ID_T e_cmd_id,
                           VOID*        pv_cmd_param,
                           MMP_TB_REPAINT_TYPE_T         e_repaint_type);
typedef INT32 (*mmp_common_ui_toolbar_view_active_fct)(MMP_TB_REPAINT_TYPE_T e_repaint_type);
typedef INT32 (*mmp_common_ui_toolbar_view_inactive_fct)(MMP_TB_REPAINT_TYPE_T e_repaint_type);

typedef struct _MMP_PLAYER_TB_VIEW_T
{
    MMP_TB_PLAYER_TYPE_T                    e_player_type;
    MMP_TOOLBAR_STATUS_T                    e_toolbar_status;
    mmp_common_ui_toolbar_cmd_do_fct        pf_cmd_do_fct;
    mmp_common_ui_toolbar_view_active_fct   pf_view_active_fct;
    mmp_common_ui_toolbar_view_inactive_fct pf_view_inactive_fct;
} MMP_PLAYER_TB_VIEW_T;

typedef struct _MMP_PP_TB_PLAYER_BAR_T
{
    HANDLE_T                    h_player_hint;
    HANDLE_T                    h_repeat_icon;
    HANDLE_T                    h_repeat_hint;
    HANDLE_T                    h_zoom_icon;
    HANDLE_T                    h_zoom_hint;
    HANDLE_T                    h_effect_icon;
    HANDLE_T                    h_effect_hint;
    HANDLE_T                    h_shuffle_icon;
    HANDLE_T                    h_duration_icon;
    HANDLE_T                    h_duration_hint;
    HANDLE_T                    h_fileidx_icon;
    HANDLE_T                    h_fileidx_hint;
    HANDLE_T                    h_filename_icon;
    HANDLE_T                    h_filename_hint;
} MMP_PP_TB_PLAYER_BAR_T;

typedef struct _MMP_PP_TB_INFO_BAR_T
{
    HANDLE_T                    h_menu_icon;
    HANDLE_T                    h_menu_hint;
    HANDLE_T                    h_select_icon;
    HANDLE_T                    h_select_hint;
    HANDLE_T                    h_enter_icon;
    HANDLE_T                    h_enter_hint;
} MMP_PP_TB_INFO_BAR_T;

typedef struct _MMP_PP_TB_VIEW_T
{
    HANDLE_T                    h_parent;
    HANDLE_T                    h_main_frm;
    HANDLE_T                    h_top_bar;
    HANDLE_T                    h_player_bar;
    HANDLE_T                    h_info_bar;
    HANDLE_T                    h_play_icon;
    HANDLE_T                    h_repeat_ab_icon;

    MMP_PP_TB_PLAYER_BAR_T      t_player_bar;
    MMP_PP_TB_INFO_BAR_T        t_info_bar;
} MMP_PP_TB_VIEW_T;

typedef struct _MMP_VP_TB_PLAYER_BAR_T
{
    HANDLE_T                    h_elapse_time_hint;
    HANDLE_T                    h_progress_bar;
    HANDLE_T                    h_remain_time_hint;
    HANDLE_T                    h_set_sec_box;
    mmp_tb_time_box_cb          pt_time_box_cb;
    GL_COLOR_T                  t_clr_fg_crnt;
    GL_COLOR_T                  t_clr_fg_prev;

}MMP_VP_TB_PLAYER_BAR_T;

typedef struct _MMP_VP_TB_VIEW_T
{
    HANDLE_T                    h_parent;
    HANDLE_T                    h_main_frm;
    HANDLE_T                    h_top_bar;
    HANDLE_T                    h_player_bar;
    HANDLE_T                    h_info_bar;
    HANDLE_T                    h_play_icon;
    HANDLE_T                    h_last_focus_widget;

    MMP_VP_TB_PLAYER_BAR_T      t_player_bar;
} MMP_VP_TB_VIEW_T;

typedef struct _MMP_AP_TB_PLAYER_BAR_T
{
    HANDLE_T                    h_player_hint;
    HANDLE_T                    h_repeat_icon;
    HANDLE_T                    h_repeat_hint;
    HANDLE_T                    h_shuffle_icon;
    HANDLE_T                    h_dura_cur_hint;
    HANDLE_T                    h_duration_bar;
    HANDLE_T                    h_dura_total_hint;
    HANDLE_T                    h_fileidx_icon;
    HANDLE_T                    h_fileidx_hint;
    HANDLE_T                    h_volinfo_icon;
    HANDLE_T                    h_volinfo_bar;
    HANDLE_T                    h_filename_icon;
    HANDLE_T                    h_filename_hint;
} MMP_AP_TB_PLAYER_BAR_T;

typedef struct _MMP_AP_TB_INFO_BAR_T
{
    HANDLE_T                    h_menu_icon;
    HANDLE_T                    h_menu_hint;
    HANDLE_T                    h_select_icon;
    HANDLE_T                    h_select_hint;
    HANDLE_T                    h_enter_icon;
    HANDLE_T                    h_enter_hint;
} MMP_AP_TB_INFO_BAR_T;

typedef struct _MMP_AP_TB_VIEW_T
{
    HANDLE_T                    h_parent;
    HANDLE_T                    h_main_frm;
    HANDLE_T                    h_top_bar;
    HANDLE_T                    h_player_bar;
    HANDLE_T                    h_info_bar;
    HANDLE_T                    h_play_icon;
    HANDLE_T                    h_times_hint;
    HANDLE_T                    h_repeat_ab_icon;

    MMP_AP_TB_PLAYER_BAR_T      t_player_bar;
    MMP_AP_TB_INFO_BAR_T        t_info_bar;
} MMP_AP_TB_VIEW_T;

typedef struct _MMP_TP_TB_PLAYER_BAR_T
{
    HANDLE_T                    h_player_hint;
    HANDLE_T                    h_repeat_icon;
    HANDLE_T                    h_repeat_hint;
    HANDLE_T                    h_shuffle_icon;
    HANDLE_T                    h_pageidx_icon;
    HANDLE_T                    h_pageidx_hint;
    HANDLE_T                    h_fileidx_icon;
    HANDLE_T                    h_fileidx_hint;
    HANDLE_T                    h_filename_icon;
    HANDLE_T                    h_filename_hint;
} MMP_TP_TB_PLAYER_BAR_T;

typedef struct _MMP_TP_TB_INFO_BAR_T
{
    HANDLE_T                    h_page_up_icon;
    HANDLE_T                    h_page_up_hint;
    HANDLE_T                    h_page_down_icon;
    HANDLE_T                    h_page_down_hint;
    HANDLE_T                    h_next_file_icon;
    HANDLE_T                    h_next_file_hint;
    HANDLE_T                    h_prev_file_icon;
    HANDLE_T                    h_prev_file_hint;
} MMP_TP_TB_INFO_BAR_T;


typedef struct _MMP_TP_TB_VIEW_T
{
    HANDLE_T                    h_parent;
    HANDLE_T                    h_main_frm;
    HANDLE_T                    h_top_bar;
    HANDLE_T                    h_player_bar;
    HANDLE_T                    h_info_bar;
    HANDLE_T                    h_play_icon;

    MMP_TP_TB_PLAYER_BAR_T      t_player_bar;
    MMP_TP_TB_INFO_BAR_T        t_info_bar;
} MMP_TP_TB_VIEW_T;

typedef enum
{
    _MMP_VP_SEEK_STAT_UNUSED = 0,
    _MMP_VP_SEEK_STAT_SETTING,
    _MMP_VP_SEEK_STAT_SEEKING

}   _MMP_VP_SEEK_STAT_T;

typedef struct _MMP_VP_TB_PLAYER_BAR_TIME_T
{
    /* The following variables are used for setting playing position             */

     _MMP_VP_SEEK_STAT_T  e_g_seek_stat;

    /* ui1_lb_cursor_col means which column the user is operating on             */
    /* ui1_lb_cursor_col's possible valid values are 0(HH), 2(MM), 4(SS)         */
     UINT8 ui1_g_lb_cursor_col;

    /* ui1_lb_hh_char_num means how many chars the user may input to the HH col  */
    /* ui1_lb_hh_char_num's possible valid values are 0, 1, 2                    */
    /* if the value is 2, the next char will input into the MM col               */
    /* and ui1_lb_mm_char_num's value will be set to 1                           */
    /* user no need to set into HH col 2 chars, 0 char or 1 char are both OK     */
    /* once user move the cursor to the next/previous col, this value will be 2  */
    /* and the next/previous col's char number will be always set to 0           */
     UINT8 ui1_g_lb_hh_char_num;
     UINT8 ui1_g_lb_mm_char_num;
     UINT8 ui1_g_lb_ss_char_num;

     UINT8 ui1_g_lb_hh_disp_val;
     UINT8 ui1_g_lb_mm_disp_val;
     UINT8 ui1_g_lb_ss_disp_val;

     HFONT_T h_g_font;

} MMP_VP_TB_PLAYER_BAR_TIME_T;


static MMP_PP_TB_VIEW_T     t_pp_tb_view;
static MMP_VP_TB_VIEW_T     t_vp_tb_view;
static MMP_AP_TB_VIEW_T     t_ap_tb_view;
static MMP_TP_TB_VIEW_T     t_tp_tb_view;
static UINT16               ui2_g_lang;
static BOOL                 b_g_vol_bar_hide = FALSE;

//static MMP_VP_TB_PLAYER_BAR_TIME_T t_vp_tb_time_view;

/* The following variables are used for setting playing position             */

/* ui1_lb_cursor_col means which column the user is operating on             */
/* ui1_lb_cursor_col's possible valid values are 0(HH), 2(MM), 4(SS)         */
static UINT8 ui1_g_lb_cursor_col  = 0;

/* ui1_lb_hh_char_num means how many chars the user may input to the HH col  */
/* ui1_lb_hh_char_num's possible valid values are 0, 1, 2                    */
/* if the value is 2, the next char will input into the MM col               */
/* and ui1_lb_mm_char_num's value will be set to 1                           */
/* user no need to set into HH col 2 chars, 0 char or 1 char are both OK     */
/* once user move the cursor to the next/previous col, this value will be 2  */
/* and the next/previous col's char number will be always set to 0           */
static UINT8 ui1_g_lb_hh_char_num = 0;
static UINT8 ui1_g_lb_mm_char_num = 0;
static UINT8 ui1_g_lb_ss_char_num = 0;

static UINT8 ui1_g_lb_hh_disp_val = 0;
static UINT8 ui1_g_lb_mm_disp_val = 0;
static UINT8 ui1_g_lb_ss_disp_val = 0;

static HFONT_T h_g_font = NULL_HANDLE;



static INT32 _mmp_pp_tb_ui_init(HANDLE_T h_parent);
static INT32 _mmp_vp_tb_ui_init(HANDLE_T h_parent);
static INT32 _mmp_ap_tb_ui_init(HANDLE_T h_parent);
static INT32 _mmp_tp_tb_ui_init(HANDLE_T h_parent);

static INT32 _mmp_pp_tb_ui_deinit(VOID);
static INT32 _mmp_vp_tb_ui_deinit(VOID);
static INT32 _mmp_ap_tb_ui_deinit(VOID);
static INT32 _mmp_tp_tb_ui_deinit(VOID);

static INT32 _mmp_pp_tb_cmd_do(MMP_TB_CMD_ID_T e_cmd_id,
                                      VOID* pv_cmd_param,
                                      MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_vp_tb_cmd_do(MMP_TB_CMD_ID_T e_cmd_id,
                                      VOID* pv_cmd_param,
                                      MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_ap_tb_cmd_do(MMP_TB_CMD_ID_T e_cmd_id,
                                      VOID* pv_cmd_param,
                                      MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_tp_tb_cmd_do(MMP_TB_CMD_ID_T e_cmd_id,
                                      VOID* pv_cmd_param,
                                      MMP_TB_REPAINT_TYPE_T e_repaint_type);

static INT32 _mmp_pp_tb_view_active(MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_vp_tb_view_active(MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_ap_tb_view_active(MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_tp_tb_view_active(MMP_TB_REPAINT_TYPE_T e_repaint_type);

static INT32 _mmp_pp_tb_view_inactive(MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_vp_tb_view_inactive(MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_ap_tb_view_inactive(MMP_TB_REPAINT_TYPE_T e_repaint_type);
static INT32 _mmp_tp_tb_view_inactive(MMP_TB_REPAINT_TYPE_T e_repaint_type);

static INT32 _mmp_tb_widget_show(HANDLE_T h_widget, MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_widget, WGL_SW_NORMAL);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (e_repaint_type == MMP_TB_SYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (e_repaint_type == MMP_TB_ASYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(h_widget, NULL, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

static INT32 _mmp_tb_widget_hide(HANDLE_T h_widget, MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_widget, WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (e_repaint_type == MMP_TB_SYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (e_repaint_type == MMP_TB_ASYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(h_widget, NULL, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

static INT32 _mmp_tb_frame_show(HANDLE_T                h_frame,
                                HANDLE_T                h_hidden_widget,
                                MMP_TB_REPAINT_TYPE_T   e_repaint_type)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_frame, WGL_SW_RECURSIVE);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (h_hidden_widget != NULL_HANDLE)
    {
        i4_ret = c_wgl_set_visibility(h_hidden_widget, WGL_SW_HIDE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    if (e_repaint_type == MMP_TB_SYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(h_frame, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (e_repaint_type == MMP_TB_ASYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(h_frame, NULL, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

static INT32 _mmp_tb_frame_hide(HANDLE_T h_frame, MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;

    i4_ret = c_wgl_set_visibility(h_frame, WGL_SW_HIDE);
    MMPR_LOG_ON_FAIL(i4_ret);

    if (e_repaint_type == MMP_TB_SYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(h_frame, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else if (e_repaint_type == MMP_TB_ASYNC_REPAINT)
    {
        i4_ret = c_wgl_repaint(h_frame, NULL, FALSE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

static INT32 _mmp_tb_load_icon(HANDLE_T             h_icon,
                            WGL_HIMG_TPL_T        h_img_tpl,
                            MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;
    WGL_IMG_INFO_T t_img_info;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = h_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = h_img_tpl;
    i4_ret = c_wgl_do_cmd(h_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info)
                          );
    MMPR_LOG_ON_FAIL(i4_ret);

    if (e_repaint_type == MMP_TB_SYNC_REPAINT)
    {
        c_wgl_repaint(h_icon,NULL,TRUE);
    }
    else if (e_repaint_type == MMP_TB_ASYNC_REPAINT)
    {
        c_wgl_repaint(h_icon,NULL,FALSE);
    }

    return i4_ret ;
}

static INT32 _mmp_tb_set_text(HANDLE_T           h_txt,
                        UTF16_T*              w2s_text,
                        MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_text),
                          WGL_PACK((UINT16)0xFFFF));
    MMPR_LOG_ON_FAIL(i4_ret);


    if (e_repaint_type == MMP_TB_SYNC_REPAINT)
    {
        c_wgl_repaint(h_txt,NULL,TRUE);
    }
    else if (e_repaint_type == MMP_TB_ASYNC_REPAINT)
    {
        c_wgl_repaint(h_txt,NULL,FALSE);
    }

    return i4_ret;
}

static UINT16 _mmp_tb_get_mlm_lang_id(VOID)
{
    INT32                       i4_ret;
    ISO_639_LANG_T              s639_lang;
    UINT16                      ui2_lang_id;

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    MMPR_LOG_ON_FAIL(i4_ret);

    if(i4_ret != APP_CFGR_OK)
    {
        ui2_lang_id =0;
    }
    else
    {
        ui2_lang_id = mlm_mmp_s639_to_langidx(s639_lang);
    }

    return ui2_lang_id;
}

static INT32 _mmp_tb_calc_progress(MMP_TB_POS_INFO_T *pt_time)
{
    INT32 i4_progress = 0;

    if (pt_time != NULL)
    {
        if (MMP_TB_POS_TYPE_BYTE == pt_time->e_pos_type)
        {
            if (0 == pt_time->u.ui8_byte_dur)
            {
                i4_progress = 0;
            }
            else
            {
                i4_progress = (INT32)(pt_time->v.ui8_byte_pos * 100 / pt_time->u.ui8_byte_dur);
            }
        }
        else
        {
            if (0 == pt_time->u.ui4_time_dur)
            {
                i4_progress = 0;
            }
            else
            {
                i4_progress = (INT32)(pt_time->v.ui4_time_pos * 100 / pt_time->u.ui4_time_dur);
            }
        }
    }

    return i4_progress;
}

static INT32 _mmp_tb_set_progress(HANDLE_T h_bar,
                        INT32      i4_progress,
                        MMP_TB_REPAINT_TYPE_T       e_repaint_type)
{
    INT32 i4_ret;

    i4_ret = c_wgl_do_cmd(h_bar,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK(i4_progress),
                          NULL);
    MMPR_LOG_ON_FAIL(i4_ret);

#if NEVER
    if(e_repaint_type)
#else
    if((MMP_TB_ASYNC_REPAINT == e_repaint_type) ||
       (MMP_TB_SYNC_REPAINT == e_repaint_type))    
#endif
    {
        i4_ret = c_wgl_repaint(h_bar, NULL, TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

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

/*----------------------------------------------------------------------------
 * Name: _convert_time_day_hh_mm_ss_to_sec
 *
 * Description: Convert ui1_hour/ui1_minute/ui1_second => ui4_day_sec
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _convert_time_day_hh_mm_ss_to_sec(UINT8   ui1_hour,       /* in  */
                                              UINT8   ui1_minute,     /* in  */
                                              UINT8   ui1_sec,        /* in  */
                                              UINT32* pui4_day_sec)   /* out */
{
    UINT32 ui4_left_sec = (UINT32)0;

    ui4_left_sec  = (UINT32)ui1_hour * 3600;
    ui4_left_sec += (UINT32)ui1_minute * 60;
    ui4_left_sec += (UINT32)ui1_sec;

    *pui4_day_sec = ui4_left_sec;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_reset_cursor
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
static INT32 _mmp_vp_reset_cursor(
    UINT8                       ui1_crnt_lb_col,
    BOOL                        b_update_osd)
{
    GL_COLOR_T t_clr_fg_crnt;
    GL_COLOR_T t_clr_fg_prev;
    WGL_LB_COLOR_ELEM_SET_T t_lb_color;
    UINT8       ui1_i = 0;
    INT32      i4_ret;

    ui1_g_lb_cursor_col = ui1_crnt_lb_col;

    t_clr_fg_prev = t_vp_tb_view.t_player_bar.t_clr_fg_prev;
    t_clr_fg_crnt = t_vp_tb_view.t_player_bar.t_clr_fg_crnt;

    /* set font */
    for(ui1_i = 0; ui1_i < 5; ++ui1_i)
    {
        if(ui1_i == ui1_crnt_lb_col)
        {

            /* reset the current text color */
            t_lb_color.t_normal            = t_clr_fg_crnt;
            t_lb_color.t_disable           = t_clr_fg_crnt;
            t_lb_color.t_highlight         = t_clr_fg_crnt;
            t_lb_color.t_highlight_unfocus = t_clr_fg_crnt;
            t_lb_color.t_pushed            = t_clr_fg_crnt;
            t_lb_color.t_selected          = t_clr_fg_crnt;
            t_lb_color.t_selected_disable  = t_clr_fg_crnt;

        }
        else
        {
            /* reset the previous text color */
            t_lb_color.t_normal            = t_clr_fg_prev;
            t_lb_color.t_disable           = t_clr_fg_prev;
            t_lb_color.t_highlight         = t_clr_fg_prev;
            t_lb_color.t_highlight_unfocus = t_clr_fg_prev;
            t_lb_color.t_pushed            = t_clr_fg_prev;
            t_lb_color.t_selected          = t_clr_fg_prev;
            t_lb_color.t_selected_disable  = t_clr_fg_prev;

        }

        i4_ret =c_wgl_do_cmd(t_vp_tb_view.t_player_bar.h_set_sec_box,
                             WGL_CMD_LB_SET_COL_COLOR,
                             WGL_PACK_2(ui1_i, WGL_CLR_TEXT),
                             WGL_PACK(&t_lb_color));
        MMPR_LOG_ON_FAIL(i4_ret);


    }

    if(b_update_osd)
    {
        i4_ret = c_wgl_repaint(t_vp_tb_view.t_player_bar.h_set_sec_box,
                              NULL,
                              TRUE);
        MMPR_LOG_ON_FAIL(i4_ret);

    }

    return MMPR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _mmp_vp_move_cursor_between
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
static INT32 _mmp_vp_move_cursor_between(
    UINT8                       ui1_prev_lb_col,
    UINT8                       ui1_crnt_lb_col,
    BOOL                        b_update_osd)
{
    INT32      i4_ret=0;
    GL_COLOR_T t_clr_fg_crnt;
    GL_COLOR_T t_clr_fg_prev;
    WGL_LB_COLOR_ELEM_SET_T t_lb_color;
    UTF16_T    w2s_col[4] = {0};
    UTF16_T    w2s_tmp[4] = {0};

    c_memset(&t_clr_fg_crnt,0,sizeof(GL_COLOR_T));
    c_memset(&t_clr_fg_prev,0,sizeof(GL_COLOR_T));

    t_clr_fg_prev = t_vp_tb_view.t_player_bar.t_clr_fg_prev;
    t_clr_fg_crnt = t_vp_tb_view.t_player_bar.t_clr_fg_crnt;

    if(0 == ui1_crnt_lb_col)                /* crnt : HH */
    {
        if(2 == ui1_prev_lb_col)            /* prev : MM */
        {
            ui1_g_lb_mm_char_num = 2;
        }
        else if(4 == ui1_prev_lb_col)       /* prev : SS */
        {
            ui1_g_lb_ss_char_num = 2;
        }
        else
        {
            return MMPR_INV_ARG;
        }

        ui1_g_lb_hh_char_num = 0;
    }
    else if(2 == ui1_crnt_lb_col)           /* crnt : MM */
    {
        if(4 == ui1_prev_lb_col)            /* prev : SS */
        {
            ui1_g_lb_ss_char_num = 2;
        }
        else if(0 == ui1_prev_lb_col)       /* prev : HH */
        {
            ui1_g_lb_hh_char_num = 2;
        }
        else
        {
            return MMPR_INV_ARG;
        }

        ui1_g_lb_mm_char_num = 0;
    }
    else if(4 == ui1_crnt_lb_col)           /* crnt : SS */
    {
        if(0 == ui1_prev_lb_col)            /* prev : HH */
        {
            ui1_g_lb_hh_char_num = 2;
        }
        else if(2 == ui1_prev_lb_col)       /* prev : MM */
        {
            ui1_g_lb_mm_char_num = 2;
        }
        else
        {
            MMPR_LOG_ON_FAIL(MMPR_INV_ARG);
            return MMPR_INV_ARG;
        }

        ui1_g_lb_ss_char_num = 0;
    }
    else
    {
        MMPR_LOG_ON_FAIL(MMPR_INV_ARG);
        return MMPR_INV_ARG;
    }

    i4_ret=c_wgl_do_cmd(
              t_vp_tb_view.t_player_bar.h_set_sec_box,
              WGL_CMD_LB_GET_ITEM_TEXT,
              WGL_PACK_2(0, ui1_prev_lb_col),
              WGL_PACK(w2s_tmp)
              );
    MMPR_LOG_ON_FAIL(i4_ret);

    if(1 == c_uc_w2s_strlen(w2s_tmp))
    {
        c_uc_ps_to_w2s("0", w2s_col, 4);
        c_uc_w2s_strcat(w2s_col, w2s_tmp);

        i4_ret=c_wgl_do_cmd(
              t_vp_tb_view.t_player_bar.h_set_sec_box,
              WGL_CMD_LB_SET_ITEM_TEXT,
              WGL_PACK_2(0, ui1_prev_lb_col),
              WGL_PACK(w2s_col)
              );
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    /* reset the previous text color */
    t_lb_color.t_normal            = t_clr_fg_prev;
    t_lb_color.t_disable           = t_clr_fg_prev;
    t_lb_color.t_highlight         = t_clr_fg_prev;
    t_lb_color.t_highlight_unfocus = t_clr_fg_prev;
    t_lb_color.t_pushed            = t_clr_fg_prev;
    t_lb_color.t_selected          = t_clr_fg_prev;
    t_lb_color.t_selected_disable  = t_clr_fg_prev;

    i4_ret=c_wgl_do_cmd(
              t_vp_tb_view.t_player_bar.h_set_sec_box,
              WGL_CMD_LB_SET_COL_COLOR,
              WGL_PACK_2(ui1_prev_lb_col, WGL_CLR_TEXT),
              WGL_PACK(&t_lb_color)
              );
    MMPR_LOG_ON_FAIL(i4_ret);

    /* reset the previous bk color */
    i4_ret=c_wgl_do_cmd(
              t_vp_tb_view.t_player_bar.h_set_sec_box,
              WGL_CMD_LB_SET_COL_COLOR,
              WGL_PACK_2(ui1_prev_lb_col, WGL_CLR_BK),
              WGL_PACK(NULL)
              );
    MMPR_LOG_ON_FAIL(i4_ret);

    if(TRUE == b_update_osd)
    {
        /* set the cursor text color */
        t_lb_color.t_normal            = t_clr_fg_crnt;
        t_lb_color.t_disable           = t_clr_fg_crnt;
        t_lb_color.t_highlight         = t_clr_fg_crnt;
        t_lb_color.t_highlight_unfocus = t_clr_fg_crnt;
        t_lb_color.t_pushed            = t_clr_fg_crnt;
        t_lb_color.t_selected          = t_clr_fg_crnt;
        t_lb_color.t_selected_disable  = t_clr_fg_crnt;

        i4_ret=c_wgl_do_cmd(
                  t_vp_tb_view.t_player_bar.h_set_sec_box,
                  WGL_CMD_LB_SET_COL_COLOR,
                  WGL_PACK_2(ui1_crnt_lb_col, WGL_CLR_TEXT),
                  WGL_PACK(&t_lb_color)
                  );
        MMPR_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        /* set the cursor text color */
        t_lb_color.t_normal            = t_clr_fg_prev;
        t_lb_color.t_disable           = t_clr_fg_prev;
        t_lb_color.t_highlight         = t_clr_fg_prev;
        t_lb_color.t_highlight_unfocus = t_clr_fg_prev;
        t_lb_color.t_pushed            = t_clr_fg_prev;
        t_lb_color.t_selected          = t_clr_fg_prev;
        t_lb_color.t_selected_disable  = t_clr_fg_prev;

        i4_ret=c_wgl_do_cmd(
                  t_vp_tb_view.t_player_bar.h_set_sec_box,
                  WGL_CMD_LB_SET_COL_COLOR,
                  WGL_PACK_2(ui1_crnt_lb_col, WGL_CLR_TEXT),
                  WGL_PACK(&t_lb_color)
                  );
        MMPR_LOG_ON_FAIL(i4_ret);

        /* set the cursor bk color */
        i4_ret=c_wgl_do_cmd(
                  t_vp_tb_view.t_player_bar.h_set_sec_box,
                  WGL_CMD_LB_SET_COL_COLOR,
                  WGL_PACK_2(ui1_crnt_lb_col, WGL_CLR_BK),
                  WGL_PACK(NULL)
                  );
        MMPR_LOG_ON_FAIL(i4_ret);
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_start_to_set_time(UINT32  ui4_position)
{
    UINT8             ui1_hh, ui1_mm, ui1_ss;
    UTF16_T           w2s_str[12] = {0};
    CHAR              s_str[12] = {0};
    INT32             i4_ret;

    /* show duration and current position */
    _convert_time_day_sec_to_hh_mm_ss(
                      (UINT32)ui4_position,
                      &ui1_hh,
                      &ui1_mm,
                      &ui1_ss
                      );

    /* HH */
    c_sprintf(s_str, "%02d", ui1_hh);
    c_uc_ps_to_w2s(s_str, w2s_str, 12);
    i4_ret = c_wgl_do_cmd(
                      t_vp_tb_view.t_player_bar.h_set_sec_box,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(0, 0),
                      WGL_PACK(w2s_str)
                      );
    MMPR_LOG_ON_FAIL(i4_ret);

    /* MM */
    c_sprintf(s_str, "%02d", ui1_mm);
    c_uc_ps_to_w2s(s_str, w2s_str, 12);
    i4_ret = c_wgl_do_cmd(
                      t_vp_tb_view.t_player_bar.h_set_sec_box,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(0, 2),
                      WGL_PACK(w2s_str)
                      );
    MMPR_LOG_ON_FAIL(i4_ret);

    /* SS */
    c_sprintf(s_str, "%02d", ui1_ss);
    c_uc_ps_to_w2s(s_str, w2s_str, 12);
    i4_ret = c_wgl_do_cmd(
                      t_vp_tb_view.t_player_bar.h_set_sec_box,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(0, 4),
                      WGL_PACK(w2s_str)
                      );
    MMPR_LOG_ON_FAIL(i4_ret);

    /* save HH/MM/SS as dispalying value */
    ui1_g_lb_hh_disp_val = ui1_hh;
    ui1_g_lb_mm_disp_val = ui1_mm;
    ui1_g_lb_ss_disp_val = ui1_ss;

    ui1_g_lb_hh_char_num = (UINT8)0;
    ui1_g_lb_mm_char_num = (UINT8)0;
    ui1_g_lb_ss_char_num = (UINT8)0;

    i4_ret = _mmp_vp_reset_cursor(0, FALSE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(
                      t_vp_tb_view.t_player_bar.h_set_sec_box,
                      WGL_SW_NORMAL
                      );
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_get_focus(&t_vp_tb_view.h_last_focus_widget);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_insert (t_vp_tb_view.t_player_bar.h_set_sec_box,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(
                      t_vp_tb_view.t_player_bar.h_set_sec_box,
                      WGL_NO_AUTO_REPAINT
                      );
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(
                      t_vp_tb_view.t_player_bar.h_set_sec_box,
                      NULL,
                      TRUE
                      );
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_vp_stop_to_set_time(
    BOOL                        b_exchange_widget
    )
{
    INT32 i4_ret=0;

    i4_ret=c_wgl_set_visibility(
              t_vp_tb_view.t_player_bar.h_set_sec_box,
              WGL_SW_HIDE
              );
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret=c_wgl_repaint(t_vp_tb_view.t_player_bar.h_set_sec_box,
                  NULL,
                  TRUE);
    MMPR_LOG_ON_FAIL(i4_ret);

    i4_ret=c_wgl_set_focus(
              t_vp_tb_view.h_last_focus_widget,
              WGL_NO_AUTO_REPAINT
              );
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_lb_set_time_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_lb_set_time_proc_fct(
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       pv_param1,
    VOID*                       pv_param2)
{
    typedef enum
    {
        _MMP_VP_KEY_TYPE_INVAL = 0,      /* unused key here         */
        _MMP_VP_KEY_TYPE_DIGIT,          /* digital key             */
        _MMP_VP_KEY_TYPE_ARROW_LR,       /* left or right arrow key */
        _MMP_VP_KEY_TYPE_ARROW_UD,       /* up or down arrow key    */
        _MMP_VP_KEY_TYPE_SELECT,         /* select key              */
        _MMP_VP_KEY_TYPE_EXIT            /* exit key                */

    }   _MMP_VP_KEY_TYPE_T;

    UINT8              ui1_lb_prev_col = 0;
    UINT8              ui1_col_max_val = 0;
    UINT8*             pui1_lb_char_num = NULL;
    UINT8*             pui1_lb_disp_val = NULL;
    CHAR               s_col[4] = {0};
    UTF16_T            w2s_col[4] = {0};
    _MMP_VP_KEY_TYPE_T t_key_type = _MMP_VP_KEY_TYPE_INVAL;
    INT8               i1_key_val = -1;
    UINT32             ui4_time_sec = 0;

    if(WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch((UINT32)pv_param1)
        {
            case BTN_DIGIT_0:
                i1_key_val = 0;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_1:
                i1_key_val = 1;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_2:
                i1_key_val = 2;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_3:
                i1_key_val = 3;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_4:
                i1_key_val = 4;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_5:
                i1_key_val = 5;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_6:
                i1_key_val = 6;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_7:
                i1_key_val = 7;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_8:
                i1_key_val = 8;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_DIGIT_9:
                i1_key_val = 9;
                t_key_type = _MMP_VP_KEY_TYPE_DIGIT;
                break;

            case BTN_CURSOR_LEFT:
            {
                ui1_lb_prev_col = ui1_g_lb_cursor_col;
                ui1_g_lb_cursor_col = ((0 == ui1_g_lb_cursor_col) ? (UINT8)6 : ui1_g_lb_cursor_col) - (UINT8)2;
                _mmp_vp_move_cursor_between(ui1_lb_prev_col, ui1_g_lb_cursor_col, TRUE);
                t_key_type = _MMP_VP_KEY_TYPE_ARROW_LR;
                break;
            }

            case BTN_CURSOR_RIGHT:
            {
                ui1_lb_prev_col = ui1_g_lb_cursor_col;
                ui1_g_lb_cursor_col = (ui1_g_lb_cursor_col + (UINT8)2) % (UINT8)6;
                _mmp_vp_move_cursor_between(ui1_lb_prev_col, ui1_g_lb_cursor_col, TRUE);
                t_key_type = _MMP_VP_KEY_TYPE_ARROW_LR;
                break;
            }

            case BTN_CURSOR_UP:
            {
                if(0 == ui1_g_lb_cursor_col)
                {
                    pui1_lb_disp_val = &ui1_g_lb_hh_disp_val;
                    ui1_col_max_val = 99;
                }
                else if(2 == ui1_g_lb_cursor_col)
                {
                    pui1_lb_disp_val = &ui1_g_lb_mm_disp_val;
                    ui1_col_max_val = 59;
                }
                else
                {
                    pui1_lb_disp_val = &ui1_g_lb_ss_disp_val;
                    ui1_col_max_val = 59;
                }

                if(ui1_col_max_val == (*pui1_lb_disp_val))
                {
                    *pui1_lb_disp_val = 0;
                }
                else
                {
                    *pui1_lb_disp_val += 1;
                }

                t_key_type = _MMP_VP_KEY_TYPE_ARROW_UD;
                break;
            }

            case BTN_CURSOR_DOWN:
            {
                if(0 == ui1_g_lb_cursor_col)
                {
                    pui1_lb_disp_val = &ui1_g_lb_hh_disp_val;
                    ui1_col_max_val = 99;
                }
                else if(2 == ui1_g_lb_cursor_col)
                {
                    pui1_lb_disp_val = &ui1_g_lb_mm_disp_val;
                    ui1_col_max_val = 59;
                }
                else
                {
                    pui1_lb_disp_val = &ui1_g_lb_ss_disp_val;
                    ui1_col_max_val = 59;
                }

                if(0 == (*pui1_lb_disp_val))
                {
                    *pui1_lb_disp_val = ui1_col_max_val;
                }
                else
                {
                    *pui1_lb_disp_val -= 1;
                }

                t_key_type = _MMP_VP_KEY_TYPE_ARROW_UD;
                break;
            }

            case BTN_SELECT:
            {
                _convert_time_day_hh_mm_ss_to_sec(
                                   ui1_g_lb_hh_disp_val,
                                   ui1_g_lb_mm_disp_val,
                                   ui1_g_lb_ss_disp_val,
                                   &ui4_time_sec);

                t_vp_tb_view.t_player_bar.pt_time_box_cb(MMP_VP_TB_TIME_BOX_STATUS_SELELCT,ui4_time_sec);

                break;
            }

            case BTN_EXIT:
            {
                t_vp_tb_view.t_player_bar.pt_time_box_cb(MMP_VP_TB_TIME_BOX_STATUS_EXIT,0);

                t_key_type = _MMP_VP_KEY_TYPE_EXIT;
                _mmp_vp_stop_to_set_time(TRUE);
                break;
            }

            default:
                t_key_type = _MMP_VP_KEY_TYPE_INVAL;
                break;
        }

        if(_MMP_VP_KEY_TYPE_DIGIT == t_key_type)
        {
            if(0 == ui1_g_lb_cursor_col)       /* HH */
            {
                if(2 == ui1_g_lb_hh_char_num)
                {
                    _mmp_vp_move_cursor_between(0, 2, TRUE); /* move cursor from HH to MM */
                    ui1_g_lb_cursor_col = 2;
                    ui1_g_lb_mm_disp_val = (UINT8)i1_key_val;
                    pui1_lb_char_num = &ui1_g_lb_mm_char_num;
                    pui1_lb_disp_val = &ui1_g_lb_mm_disp_val;
                }
                else
                {
                    if(0 == ui1_g_lb_hh_char_num)
                    {
                        ui1_g_lb_hh_disp_val = (UINT8)i1_key_val;
                    }
                    else
                    {
                        ui1_g_lb_hh_disp_val = ui1_g_lb_hh_disp_val * (UINT8)10 + (UINT8)i1_key_val;
                    }

                    pui1_lb_char_num = &ui1_g_lb_hh_char_num;
                    pui1_lb_disp_val = &ui1_g_lb_hh_disp_val;
                }
            }
            else if(2 == ui1_g_lb_cursor_col)  /* MM */
            {
                if(2 == ui1_g_lb_mm_char_num)
                {
                    _mmp_vp_move_cursor_between(2, 4, TRUE); /* move cursor from MM to SS */
                    ui1_g_lb_cursor_col = 4;
                    ui1_g_lb_ss_disp_val = (UINT8)i1_key_val;
                    pui1_lb_char_num = &ui1_g_lb_ss_char_num;
                    pui1_lb_disp_val = &ui1_g_lb_ss_disp_val;
                }
                else
                {
                    if(0 == ui1_g_lb_mm_char_num)
                    {
                        ui1_g_lb_mm_disp_val = (UINT8)i1_key_val;
                    }
                    else
                    {
                        ui1_g_lb_mm_disp_val = ui1_g_lb_mm_disp_val * (UINT8)10 + (UINT8)i1_key_val;
                    }

                    pui1_lb_char_num = &ui1_g_lb_mm_char_num;
                    pui1_lb_disp_val = &ui1_g_lb_mm_disp_val;
                }
            }
            else if(4 == ui1_g_lb_cursor_col)  /* SS */
            {
                if(2 == ui1_g_lb_ss_char_num)
                {
                    _mmp_vp_move_cursor_between(4, 0, TRUE); /* move cursor from SS to HH */
                    ui1_g_lb_cursor_col = 0;
                    ui1_g_lb_hh_disp_val = (UINT8)i1_key_val;
                    pui1_lb_char_num = &ui1_g_lb_hh_char_num;
                    pui1_lb_disp_val = &ui1_g_lb_hh_disp_val;
                }
                else
                {
                    if(0 == ui1_g_lb_ss_char_num)
                    {
                        ui1_g_lb_ss_disp_val = (UINT8)i1_key_val;
                    }
                    else
                    {
                        ui1_g_lb_ss_disp_val = ui1_g_lb_ss_disp_val * (UINT8)10 + (UINT8)i1_key_val;
                    }

                    pui1_lb_char_num = &ui1_g_lb_ss_char_num;
                    pui1_lb_disp_val = &ui1_g_lb_ss_disp_val;
                }
            }
            else
            {
                return MMPR_INV_ARG;
            }

            /* change the text value */
            c_sprintf(s_col, "%02d", *pui1_lb_disp_val);
            c_uc_ps_to_w2s(s_col, w2s_col, 4);

            /* set text back to upper column */
            c_wgl_do_cmd(
                    t_vp_tb_view.t_player_bar.h_set_sec_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(0, ui1_g_lb_cursor_col),
                    WGL_PACK(w2s_col)
                    );

            (*pui1_lb_char_num)++;
        }
        else if(_MMP_VP_KEY_TYPE_ARROW_UD == t_key_type)
        {
            c_sprintf(s_col, "%02d", *pui1_lb_disp_val);
            c_uc_ps_to_w2s(s_col, w2s_col, 4);

            c_wgl_do_cmd(
                    t_vp_tb_view.t_player_bar.h_set_sec_box,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(0, ui1_g_lb_cursor_col),
                    WGL_PACK(w2s_col)
                    );
        }

        if(_MMP_VP_KEY_TYPE_INVAL != t_key_type)
        {
            c_wgl_repaint(
                    t_vp_tb_view.t_player_bar.h_set_sec_box,
                    NULL,
                    FALSE
                    );
            return MMPR_OK;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _mmp_vp_view_create_icon_widget
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _mmp_vp_view_create_lb_set_time(
    HANDLE_T                    h_parent,
    wgl_widget_proc_fct         pf_wdgt_proc,
    HANDLE_T*                   ph_widget)
{
#define _MMP_VP_LB_SET_TIME_MAX_COL ((UINT8)6)

    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[_MMP_VP_LB_SET_TIME_MAX_COL];
    WGL_INSET_T                 t_inset;
    GL_RECT_T                   t_rect;
    GL_COLOR_T                  t_fg_color;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    UTF16_T                     w2s_tmp[4] = {0};
    UINT32                      ui4_width_1, ui4_width_2;
    UINT32                      ui4_height;
    INT32                       i4_ret;
    UINT8                       i = 0;

    WGL_COLOR_INFO_T            t_clr_info;
    GL_COLOR_T                  t_clr_fg_crnt = MMP_COM_UI_TIME_BOX_GET_CLR_BK();

    WGL_FONT_INFO_T             t_font_info;
    WGL_FONT_INFO_T*            pt_font;

    SET_RECT_BY_SIZE(&t_rect, 200, 200, 500, 200);

    /* set text font */
    c_memset(& t_font_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_font_info.a_c_font_name,SN_FONT_DEFAULT);
    t_font_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_font_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_font_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    pt_font = &t_font_info;

    i4_ret = c_wgl_do_cmd(t_vp_tb_view.t_player_bar.h_elapse_time_hint,
                        WGL_CMD_GL_GET_COLOR,
                        WGL_PACK(WGL_CLR_TEXT),
                        WGL_PACK(&t_clr_info));
    MMPR_LOG_ON_FAIL(i4_ret);

    c_memcpy(&t_vp_tb_view.t_player_bar.t_clr_fg_prev,
             &t_clr_info.u_color_data,
             sizeof(GL_COLOR_T));

    c_memcpy(&t_vp_tb_view.t_player_bar.t_clr_fg_crnt,
             &t_clr_fg_crnt,
             sizeof(GL_COLOR_T));

    t_fg_color = t_vp_tb_view.t_player_bar.t_clr_fg_prev;


    if(NULL_HANDLE == h_g_font)
    {
        i4_ret = c_fe_create_font(
                        pt_font->a_c_font_name,
                        pt_font->e_font_size,
                        pt_font->e_font_style,
                        pt_font->e_font_cmap,
                        &h_g_font);
        if(MMPR_OK != i4_ret)
        {
            return MMPR_FAIL;
        }
    }

    c_uc_ps_to_w2s("00", w2s_tmp, 4);
    i4_ret = c_fe_get_string_size(
                    h_g_font,
                    w2s_tmp,
                    (INT32)c_uc_w2s_strlen(w2s_tmp),
                    (INT32*)&ui4_width_1,
                    (INT32*)&ui4_height);
    if(MMPR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    c_uc_ps_to_w2s(":", w2s_tmp, 4);
    i4_ret = c_fe_get_string_size(
                    h_g_font,
                    w2s_tmp,
                    (INT32)c_uc_w2s_strlen(w2s_tmp),
                    (INT32*)&ui4_width_2,
                    (INT32*)&ui4_height);
    if(MMPR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    for(i = 0; i < _MMP_VP_LB_SET_TIME_MAX_COL - 1; ++i)
    {
        at_cols[i].e_col_type        = LB_COL_TYPE_TEXT;
        at_cols[i].ui1_align         = WGL_AS_RIGHT_CENTER;
        at_cols[i].ui2_width         = (UINT16)((i % 2) ? ui4_width_2 : ui4_width_1);
        at_cols[i].ui2_max_text_len  = 3;
    }

    at_cols[_MMP_VP_LB_SET_TIME_MAX_COL - 1].e_col_type        = LB_COL_TYPE_TEXT;
    at_cols[_MMP_VP_LB_SET_TIME_MAX_COL - 1].ui1_align         = WGL_AS_LEFT_CENTER;
    at_cols[_MMP_VP_LB_SET_TIME_MAX_COL - 1].ui2_width         = (UINT16)(RECT_W(&t_rect) - ui4_width_1 * 3 - ui4_width_2 * 2);
    at_cols[_MMP_VP_LB_SET_TIME_MAX_COL - 1].ui2_max_text_len  = 12;

    t_lb_init.ui4_style          = WGL_STL_LB_NO_SCROLL
                                   | WGL_STL_LB_FORCE_HLT
                                   | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num   = 1;
    t_lb_init.ui2_elem_size      = RECT_H(&t_rect);
    t_lb_init.ui2_elem_distance  = 0;
    t_lb_init.ui1_col_num        = _MMP_VP_LB_SET_TIME_MAX_COL;
    t_lb_init.at_cols            = at_cols;

    /* create widget */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);

    /* set font */
    for(i = 0; i < _MMP_VP_LB_SET_TIME_MAX_COL; ++i)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                      WGL_CMD_LB_SET_COL_FONT,
                      WGL_PACK(i),
                      WGL_PACK(pt_font));
    }

    /* set content inset */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                      WGL_CMD_LB_SET_CNT_INSET,
                      WGL_PACK(&t_inset),
                      NULL);

    /* set element inset */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                      WGL_CMD_LB_SET_ELEM_INSET,
                      WGL_PACK(&t_inset),
                      NULL);

    /* set column inset */
    for(i = 0; i < _MMP_VP_LB_SET_TIME_MAX_COL; ++i)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                      WGL_CMD_LB_SET_COL_INSET,
                      WGL_PACK(i),
                      WGL_PACK(&t_inset));
    }

    /* set text color */
    t_lb_color.t_normal            = t_fg_color;
    t_lb_color.t_disable           = t_fg_color;
    t_lb_color.t_highlight         = t_fg_color;
    t_lb_color.t_highlight_unfocus = t_fg_color;
    t_lb_color.t_pushed            = t_fg_color;
    t_lb_color.t_selected          = t_fg_color;
    t_lb_color.t_selected_disable  = t_fg_color;

    for(i = 0; i < _MMP_VP_LB_SET_TIME_MAX_COL; ++i)
    {
        i4_ret = c_wgl_do_cmd(*ph_widget,
                      WGL_CMD_LB_SET_COL_COLOR,
                      WGL_PACK_2(i, WGL_CLR_TEXT),
                      WGL_PACK(&t_lb_color));
    }

    /* set text align */
    for(i = 0; i < _MMP_VP_LB_SET_TIME_MAX_COL; ++i)
    {
        c_wgl_do_cmd (*ph_widget,
                      WGL_CMD_LB_SET_COL_ALIGN,
                      WGL_PACK (i),
                      WGL_PACK (WGL_AS_LEFT_TOP));
    }

    /* set element number */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                      WGL_CMD_LB_SET_ELEM_NUM,
                      (VOID*)1,
                      NULL);

    /* set the unchangeable text */
    c_uc_ps_to_w2s(":", w2s_tmp, 4);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(0, 1),
                      WGL_PACK(w2s_tmp));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                      WGL_CMD_LB_SET_ITEM_TEXT,
                      WGL_PACK_2(0, 3),
                      WGL_PACK(w2s_tmp));

    i4_ret = c_wgl_set_visibility(
                      *ph_widget,
                      WGL_SW_HIDE
                      );
    if(WGLR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    return MMPR_OK;
}
static INT32 _mmp_tb_format_string(MMP_TB_FORMAT_TYPE_T e_format_type,
                                        UTF16_T              *ws_display,
                                        VOID                 *pv_param)
{
    INT32  i4_ret = 0;
    CHAR   s_buf[MMP_TB_STRING_SIZE];
    UINT32 z_buf_size = 0;

    if (ws_display == NULL)
    {
        MMPR_LOG_ON_FAIL(MMPR_INV_ARG);
        return MMPR_INV_ARG;
    }

    switch (e_format_type)
    {
        case MMP_TB_FORMAT_TYPE_DURATION:
            {
                UINT32 ui4_time_sec = (UINT32)pv_param;
                MMP_UTIL_TIME_HMS_T t_time_hms = {0};

                i4_ret = mmp_util_devide_time_code(ui4_time_sec, &t_time_hms);
                MMPR_LOG_ON_FAIL(i4_ret);

                c_sprintf(s_buf, MMP_TB_FORMAT_DURATION, t_time_hms.ui2_hh, t_time_hms.ui2_mm, t_time_hms.ui2_ss);
            }
            break;

        case MMP_TB_FORMAT_TYPE_ZOOM:
            {
                INT32 i4_zoom = (INT32)pv_param;

                c_sprintf(s_buf, MMP_TB_FORMAT_ZOOM, i4_zoom);
            }
            break;

        case MMP_TB_FORMAT_TYPE_FF_FR:
            {
                INT32 i4_ff_fr = (INT32)pv_param;

                c_sprintf(s_buf, MMP_TB_FORMAT_FF_FR, i4_ff_fr);
            }
            break;

        case MMP_TB_FORMAT_TYPE_PLAY:
            {
                INT32 i4_play = (INT32)pv_param;

                c_sprintf(s_buf, MMP_TB_FORMAT_PLAY, i4_play);
            }
            break;

        case MMP_TB_FORMAT_TYPE_SUB:
            {
                MMP_TB_SUB_TYPE_T *pt_sub = (MMP_TB_SUB_TYPE_T *)pv_param;

                c_sprintf(s_buf, MMP_TB_FORMAT_SUB, pt_sub->ui2_sub_index, pt_sub->ui2_sub_total);
            }
            break;

        case MMP_TB_FORMAT_TYPE_MTS:
            {
                MMP_TB_MTS_TYPE_T *pt_mts = (MMP_TB_MTS_TYPE_T *)pv_param;

                c_sprintf(s_buf, MMP_TB_FORMAT_MTS, pt_mts->ui2_mts_index, pt_mts->ui2_mts_total);
            }
            break;

        default:
            MMPR_LOG_ON_FAIL(MMPR_INV_ARG);
            return MMPR_INV_ARG;
    }

    i4_ret = c_uc_ps_to_w2s(s_buf, ws_display, MMP_TB_STRING_SIZE);
    if(UCR_OK != i4_ret)
    {
        ws_display = NULL;
    }
    else
    {
        z_buf_size = c_strlen(s_buf);
        ws_display[z_buf_size] = (UTF16_T)0;
    }

    return MMPR_OK;
}

static INT32 _mmp_pp_tb_ui_init(HANDLE_T h_parent)
{
    INT32            i4_ret;
    MMP_PP_TB_VIEW_T *pt_this = &t_pp_tb_view;

    c_memset(pt_this, 0, sizeof(MMP_PP_TB_VIEW_T));
    pt_this->h_parent = h_parent;

    i4_ret = mmp_pp_tb_create_ui(pt_this->h_parent);
    MMPR_LOG_ON_FAIL(i4_ret);
    if(WDKR_OK != i4_ret)
    {
        pt_this->h_main_frm = NULL_HANDLE;
        return MMPR_FAIL;
    }

    i4_ret = mmp_pp_tb_update_text(ui2_g_lang);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (WDKR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    pt_this->h_main_frm       = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_FRM_MAIN_FRM);
    pt_this->h_top_bar        = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_FRM_TOP_BAR);
    pt_this->h_player_bar     = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_FRM_PLAYER_BAR);
    pt_this->h_info_bar       = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_FRM_INFO_BAR);
    pt_this->h_play_icon      = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_PLAY_ICON);
    pt_this->h_repeat_ab_icon = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_REPEAT_AB_ICON);

    pt_this->t_player_bar.h_player_hint   = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_PLAYER_HINT);
    pt_this->t_player_bar.h_repeat_icon   = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_REPEAT_ICON);
    pt_this->t_player_bar.h_repeat_hint   = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_REPEAT_HINT);
    pt_this->t_player_bar.h_zoom_icon     = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_ZOOM_ICON);
    pt_this->t_player_bar.h_zoom_hint     = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_ZOOM_HINT);
    pt_this->t_player_bar.h_effect_icon   = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_EFFECT_ICON);
    pt_this->t_player_bar.h_effect_hint   = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_EFFECT_HINT);
    pt_this->t_player_bar.h_shuffle_icon  = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_SHUFFLE_ICON);
    pt_this->t_player_bar.h_duration_icon = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_DURA_ICON);
    pt_this->t_player_bar.h_duration_hint = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_DURA_HINT);
    pt_this->t_player_bar.h_fileidx_icon  = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_FILEIDX_ICON);
    pt_this->t_player_bar.h_fileidx_hint  = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_FILEIDX_HINT);
    pt_this->t_player_bar.h_filename_icon = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_FILENAME_ICON);
    pt_this->t_player_bar.h_filename_hint = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_FILENAME_HINT);

    pt_this->t_info_bar.h_menu_icon   = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_MENU_ICON);
    pt_this->t_info_bar.h_menu_hint   = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_MENU_HINT);
    pt_this->t_info_bar.h_select_icon = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_SELECT_ICON);
    pt_this->t_info_bar.h_select_hint = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_SELECT_HINT);
    pt_this->t_info_bar.h_enter_icon  = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_ICON_ENTER_ICON);
    pt_this->t_info_bar.h_enter_hint  = mmp_pp_tb_get_wgt_hdl(WID_MMP_PP_TB_TXT_ENTER_HINT);

    return MMPR_OK;
}

static INT32 _mmp_vp_tb_ui_init(HANDLE_T h_parent)
{
    INT32            i4_ret;
    MMP_VP_TB_VIEW_T *pt_this = &t_vp_tb_view;

    c_memset(pt_this, 0, sizeof(MMP_VP_TB_VIEW_T));
    pt_this->h_parent = h_parent;

    i4_ret = mmp_vp_tb_create_ui(pt_this->h_parent);
    MMPR_LOG_ON_FAIL(i4_ret);
    if(WDKR_OK != i4_ret)
    {
        pt_this->h_main_frm = NULL_HANDLE;
        return MMPR_FAIL;
    }

    i4_ret = mmp_vp_tb_update_text(ui2_g_lang);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (WDKR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    pt_this->h_main_frm       = mmp_vp_tb_get_wgt_hdl(WID_MMP_VP_TB_FRM_MAIN_FRM);
    pt_this->h_top_bar        = mmp_vp_tb_get_wgt_hdl(WID_MMP_VP_TB_FRM_TOP_BAR);
    pt_this->h_player_bar     = mmp_vp_tb_get_wgt_hdl(WID_MMP_VP_TB_FRM_PLAYER_BAR);
    pt_this->h_play_icon      = mmp_vp_tb_get_wgt_hdl(WID_MMP_VP_TB_ICON_PLAY_ICON);

    pt_this->t_player_bar.h_elapse_time_hint   = mmp_vp_tb_get_wgt_hdl(WID_MMP_VP_TB_TXT_ELAPSE_TIME_HINT);
    pt_this->t_player_bar.h_progress_bar    = mmp_vp_tb_get_wgt_hdl(WID_MMP_VP_TB_PB_PROGRESS_BAR);
    pt_this->t_player_bar.h_remain_time_hint = mmp_vp_tb_get_wgt_hdl(WID_MMP_VP_TB_TXT_REMAIN_TIME_HINT);

    i4_ret = _mmp_vp_view_create_lb_set_time(pt_this->h_parent,
                                             _mmp_vp_lb_set_time_proc_fct,
                                             &pt_this->t_player_bar.h_set_sec_box);

    return MMPR_OK;
}

static INT32 _mmp_ap_tb_ui_init(HANDLE_T h_parent)
{
    INT32            i4_ret;
    MMP_AP_TB_VIEW_T *pt_this = &t_ap_tb_view;

    c_memset(pt_this, 0, sizeof(MMP_AP_TB_VIEW_T));
    pt_this->h_parent = h_parent;

    i4_ret = mmp_ap_tb_create_ui(pt_this->h_parent);
    MMPR_LOG_ON_FAIL(i4_ret);
    if(WDKR_OK != i4_ret)
    {
        pt_this->h_main_frm = NULL_HANDLE;
        return MMPR_FAIL;
    }

    i4_ret = mmp_ap_tb_update_text(ui2_g_lang);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (WDKR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    pt_this->h_main_frm       = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_FRM_MAIN_FRM);
    pt_this->h_top_bar        = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_FRM_TOP_BAR);
    pt_this->h_player_bar     = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_FRM_PLAYER_BAR);
    pt_this->h_info_bar       = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_FRM_INFO_BAR);
    pt_this->h_play_icon      = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_PLAY_ICON);
    pt_this->h_times_hint     = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_TIMES_HINT);
    pt_this->h_repeat_ab_icon = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_REPEAT_AB_ICON);

    pt_this->t_player_bar.h_player_hint     = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_PLAYER_HINT);
    pt_this->t_player_bar.h_repeat_icon     = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_REPEAT_ICON);
    pt_this->t_player_bar.h_repeat_hint     = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_REPEAT_HINT);
    pt_this->t_player_bar.h_shuffle_icon    = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_SHUFFLE_ICON);
    pt_this->t_player_bar.h_dura_cur_hint   = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_DURA_CUR_HINT);
    pt_this->t_player_bar.h_duration_bar    = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_PB_DURA_BAR);
    pt_this->t_player_bar.h_dura_total_hint = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_DURA_TOTAL_HINT);
    pt_this->t_player_bar.h_fileidx_icon    = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_FILEIDX_ICON);
    pt_this->t_player_bar.h_fileidx_hint    = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_FILEIDX_HINT);
    pt_this->t_player_bar.h_volinfo_icon    = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_VOL_ICON);
    pt_this->t_player_bar.h_volinfo_bar     = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_PB_VOL_BAR);
    pt_this->t_player_bar.h_filename_icon   = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_FILENAME_ICON);
    pt_this->t_player_bar.h_filename_hint   = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_FILENAME_HINT);

    pt_this->t_info_bar.h_menu_icon   = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_MENU_ICON);
    pt_this->t_info_bar.h_menu_hint   = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_MENU_HINT);
    pt_this->t_info_bar.h_select_icon = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_SELECT_ICON);
    pt_this->t_info_bar.h_select_hint = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_SELECT_HINT);
    pt_this->t_info_bar.h_enter_icon  = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_ICON_ENTER_ICON);
    pt_this->t_info_bar.h_enter_hint  = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_TXT_ENTER_HINT);

    return MMPR_OK;
}

static INT32 _mmp_tp_tb_ui_init(HANDLE_T h_parent)
{
    INT32            i4_ret;
    MMP_TP_TB_VIEW_T *pt_this = &t_tp_tb_view;

    c_memset(pt_this, 0, sizeof(MMP_TP_TB_VIEW_T));
    pt_this->h_parent = h_parent;

    i4_ret = mmp_tp_tb_create_ui(pt_this->h_parent);
    MMPR_LOG_ON_FAIL(i4_ret);
    if(WDKR_OK != i4_ret)
    {
        pt_this->h_main_frm = NULL_HANDLE;
        return MMPR_FAIL;
    }

    i4_ret = mmp_tp_tb_update_text(ui2_g_lang);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (WDKR_OK != i4_ret)
    {
        return MMPR_FAIL;
    }

    pt_this->h_main_frm       = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_FRM_MAIN_FRM);
    pt_this->h_top_bar        = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_FRM_TOP_BAR);
    pt_this->h_player_bar     = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_FRM_PLAYER_BAR);
    pt_this->h_info_bar       = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_FRM_INFO_BAR);
    pt_this->h_play_icon      = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_PLAY_ICON);

    pt_this->t_player_bar.h_player_hint    = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_PLAYER_HINT);
    pt_this->t_player_bar.h_repeat_icon    = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_REPEAT_ICON);
    pt_this->t_player_bar.h_repeat_hint    = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_REPEAT_HINT);
    pt_this->t_player_bar.h_shuffle_icon   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_SHUFFLE_ICON);

    pt_this->t_player_bar.h_pageidx_icon   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_PAGEIDX_ICON);
    pt_this->t_player_bar.h_pageidx_hint   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_PAGEIDX_HINT);
    pt_this->t_player_bar.h_fileidx_icon   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_FILEIDX_ICON);
    pt_this->t_player_bar.h_fileidx_hint   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_FILEIDX_HINT);
    pt_this->t_player_bar.h_filename_icon  = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_FILENAME_ICON);
    pt_this->t_player_bar.h_filename_hint  = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_FILENAME_HINT);

    pt_this->t_info_bar.h_page_up_icon     = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_PAGE_UP_ICON);
    pt_this->t_info_bar.h_page_up_hint     = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_PAGE_UP_HINT);
    pt_this->t_info_bar.h_page_down_icon   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_PAGE_DOWN_ICON);
    pt_this->t_info_bar.h_page_down_hint   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_PAGE_DOWN_HINT);
    pt_this->t_info_bar.h_next_file_icon   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_NEXT_FILE_ICON);
    pt_this->t_info_bar.h_next_file_hint   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_NEXT_FILE_HINT);
    pt_this->t_info_bar.h_prev_file_icon   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_ICON_PREV_FILE_ICON);
    pt_this->t_info_bar.h_prev_file_hint   = mmp_tp_tb_get_wgt_hdl(WID_MMP_TP_TB_TXT_PREV_FILE_HINT);

    return MMPR_OK;
}

static INT32 _mmp_pp_tb_ui_deinit(VOID)
{
    INT32 i4_ret;

    i4_ret = mmp_pp_tb_destroy_ui();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_vp_tb_ui_deinit(VOID)
{
    INT32 i4_ret;

    i4_ret = mmp_vp_tb_destroy_ui();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_ap_tb_ui_deinit(VOID)
{
    INT32 i4_ret;

    i4_ret = mmp_ap_tb_destroy_ui();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_tp_tb_ui_deinit(VOID)
{
    INT32 i4_ret;

    i4_ret = mmp_tp_tb_destroy_ui();
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_pp_tb_cmd_do(MMP_TB_CMD_ID_T e_cmd_id,
                            VOID*        pv_cmd_param,
                            MMP_TB_REPAINT_TYPE_T         e_repaint_type)
{
    MMP_PP_TB_VIEW_T *pt_this   = &t_pp_tb_view;

    switch (e_cmd_id)
    {
        case MMP_PP_TB_CMD_SET_PLAY_STATUS:
            {
                UINT32         ui4_play_status = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T h_img_tpl;

                switch (ui4_play_status)
                {
                    case MMP_PP_TB_STATUS_PAUSE:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_PP_TB_STATUS_NONE:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_PP_TB_STATUS_PLAY:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                _mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_REPEAT_AB:
            {
                UINT32         ui4_repeat_idx = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T h_img_tpl;

                switch (ui4_repeat_idx)
                {
                    case MMP_PP_TB_STATUS_REPEAT_AB:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_PP_TB_STATUS_REPEAT_AB_AB:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_PP_TB_STATUS_REPEAT_AB_A:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_PP_TB_STATUS_REPEAT_AB_NONE:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                _mmp_tb_load_icon(pt_this->h_repeat_ab_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_ZOOM:
            {
                UINT32         ui4_zoom_idx = (UINT32)pv_cmd_param;
                UTF16_T        *ws_zoom_hint;

                switch (ui4_zoom_idx)
                {
                    case MMP_PP_TB_STATUS_ZOOM_2X:
                        ws_zoom_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_ZLB_2);
                        break;
                    case MMP_PP_TB_STATUS_ZOOM_4X:
                        ws_zoom_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_ZLB_4);
                        break;
                    case MMP_PP_TB_STATUS_ZOOM_1X:
                    default:
                        ws_zoom_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_ZLB_1);
                        break;
                }
                _mmp_tb_set_text(pt_this->t_player_bar.h_zoom_hint, ws_zoom_hint, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_REPEAT:
            {
                UINT32         ui4_repeat_idx = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T h_img_tpl;
                UTF16_T        *ws_repeat_hint;

                switch (ui4_repeat_idx)
                {
                    case MMP_PP_TB_STATUS_REPEAT_ONE:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_VP_REPEAT_SINGLE);
                        break;
                    case MMP_PP_TB_STATUS_REPEAT_ALL:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_VP_REPEAT_ALL);
                        break;
                    case MMP_PP_TB_STATUS_REPEAT_NONE:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_EMPTY);
                        break;
                }
                _mmp_tb_load_icon(pt_this->t_player_bar.h_repeat_icon, h_img_tpl, e_repaint_type);
                _mmp_tb_set_text(pt_this->t_player_bar.h_repeat_hint, ws_repeat_hint, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_EFFECT:
            {
                UINT32         ui4_effect_idx = (UINT32)pv_cmd_param;
                UTF16_T        *ws_effect_hint;

                switch (ui4_effect_idx)
                {
                    case MMP_PP_TB_STATUS_EFFECT_DISSOLVE:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_DISSOLVE);
                        break;
                    case MMP_PP_TB_STATUS_EFFECT_WP_R:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_WP_R);
                        break;
                    case MMP_PP_TB_STATUS_EFFECT_WP_L:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_WP_L);
                        break;
                    case MMP_PP_TB_STATUS_EFFECT_WP_U:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_WP_U);
                        break;
                    case MMP_PP_TB_STATUS_EFFECT_WP_D:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_WP_D);
                        break;
                    case MMP_PP_TB_STATUS_EFFECT_BX_IN:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_BX_IN);
                        break;
                    case MMP_PP_TB_STATUS_EFFECT_BX_OUT:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_BX_OUT);
                        break;
                    case MMP_PP_TB_STATUS_EFFECT_RANDOM:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_RANDOM);
                        break;
                    case MMP_PP_TB_STATUS_EFFECT_NONE:
                    default:
                        ws_effect_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_TLB_NONE);
                        break;
                }
                _mmp_tb_set_text(pt_this->t_player_bar.h_effect_hint, ws_effect_hint, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_SHUFFLE:
            {
                UINT32         ui4_shuffle_idx = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T h_img_tpl;

                switch (ui4_shuffle_idx)
                {
                    case MMP_PP_TB_STATUS_SHUFFLE_MODE_SHUFFLE:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_PP_TB_STATUS_SHUFFLE_MODE_SEQUENTIAL:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                _mmp_tb_load_icon(pt_this->t_player_bar.h_shuffle_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_DURATION:
            {
                UINT32         ui4_dura_idx = (UINT32)pv_cmd_param;
                UTF16_T        *ws_dura_hint;

                switch (ui4_dura_idx)
                {
                    case MMP_PP_TB_STATUS_DURATION_MEDIUM:
                        ws_dura_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_DLB_M);
                        break;
                    case MMP_PP_TB_STATUS_DURATION_LONG:
                        ws_dura_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_DLB_L);
                        break;
                    case MMP_PP_TB_STATUS_DURATION_SHORT:
                    default:
                        ws_dura_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_DLB_S);
                        break;
                }
                _mmp_tb_set_text(pt_this->t_player_bar.h_duration_hint, ws_dura_hint, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_FILEIDX:
            {
                UTF16_T *ws_display = (UTF16_T *)pv_cmd_param;

                _mmp_tb_set_text(pt_this->t_player_bar.h_fileidx_hint, ws_display, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_FILENAME:
            {
                UTF16_T *ws_display = (UTF16_T *)pv_cmd_param;

                _mmp_tb_set_text(pt_this->t_player_bar.h_filename_hint, ws_display, e_repaint_type);
            }
            break;

        case MMP_PP_TB_CMD_SET_TOPBAR:
            {
                INT32 i4_topbar_idx = (INT32)pv_cmd_param;

                switch (i4_topbar_idx)
                {
                    case MMP_PP_TB_STATUS_TOPBAR_SHOW:
                        _mmp_tb_frame_show(pt_this->h_top_bar, NULL_HANDLE, e_repaint_type);
                        break;

                    case MMP_PP_TB_STATUS_TOPBAR_HIDE:
                    default:
                        _mmp_tb_frame_hide(pt_this->h_top_bar, e_repaint_type);
                        break;
                }
            }
            break;

        case MMP_PP_TB_CMD_SET_CLEAR:
            {
                _mmp_tb_set_text(pt_this->t_player_bar.h_fileidx_hint, NULL, e_repaint_type);
                _mmp_tb_set_text(pt_this->t_player_bar.h_filename_hint, NULL, e_repaint_type);
            }
            break;

        default:
            break;
    }

    return MMPR_OK;
}

static INT32 _mmp_vp_tb_cmd_do(MMP_TB_CMD_ID_T              e_cmd_id,
                               VOID*                        pv_cmd_param,
                               MMP_TB_REPAINT_TYPE_T        e_repaint_type)
{
    MMP_VP_TB_VIEW_T *pt_this   = &t_vp_tb_view;

    switch (e_cmd_id)
    {
        case MMP_VP_TB_CMD_SET_PLAY_STATUS:
            {
                UINT32         ui4_play_status = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T h_img_tpl = NULL_HANDLE;

                switch (ui4_play_status)
                {
                    case MMP_VP_TB_STATUS_PAUSE:
                        h_img_tpl = h_g_mmp_video_player_pause_icon;
                        break;
                    case MMP_VP_TB_STATUS_STOP:
                        h_img_tpl = h_g_mmp_video_player_play_icon;
                        break;
                    case MMP_VP_TB_STATUS_PLAY:
                        h_img_tpl = h_g_mmp_video_player_play_icon;
                        break;
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                _mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_VP_TB_CMD_SET_FF:
            {

                UINT32          ui4_ff_step = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T  h_img_tpl = NULL_HANDLE;

                if (2 == ui4_ff_step)
                {
                    h_img_tpl = h_g_mmp_video_player_play_ff1_icon;
                }
                else if (4 == ui4_ff_step)
                {
                    h_img_tpl = h_g_mmp_video_player_play_ff2_icon;
                }
                else if (8 == ui4_ff_step)
                {
                    h_img_tpl = h_g_mmp_video_player_play_ff3_icon;
                }
                else
                {
                    h_img_tpl = h_g_mmp_video_player_play_ff1_icon;
                }

                _mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_VP_TB_CMD_SET_FR:
            {
                UINT32          ui4_fr_step = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T  h_img_tpl = NULL_HANDLE;

                if (2 == ui4_fr_step)
                {
                    h_img_tpl = h_g_mmp_video_player_play_rw1_icon;
                }
                else if (4 == ui4_fr_step)
                {
                    h_img_tpl = h_g_mmp_video_player_play_rw2_icon;
                }
                else if (8 == ui4_fr_step)
                {
                    h_img_tpl = h_g_mmp_video_player_play_rw3_icon;
                }
                else
                {
                    h_img_tpl = h_g_mmp_video_player_play_rw1_icon;
                }

                _mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_VP_TB_CMD_SET_SLOW_PALY:
            {
                WGL_HIMG_TPL_T h_img_tpl = h_g_mmp_video_player_play_icon;

                _mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_VP_TB_CMD_SET_REPEAT_AB:
            {
                UINT32         ui4_repeat_idx = (UINT32)pv_cmd_param;

                switch (ui4_repeat_idx)
                {
                    case MMP_VP_TB_STATUS_REPEAT_AB:
                        break;
                    case MMP_VP_TB_STATUS_REPEAT_AB_AB:
                        break;
                    case MMP_VP_TB_STATUS_REPEAT_AB_A:
                        break;
                    case MMP_VP_TB_STATUS_REPEAT_AB_NONE:
                        break;
                    default:
                        break;
                }
            }
            break;

        case MMP_VP_TB_CMD_SET_ZOOM:
            {
            }
            break;

        case MMP_VP_TB_CMD_SET_MTS:
            {
            }
            break;

        case MMP_VP_TB_CMD_SET_REPEAT:
            {
                UINT32         ui4_repeat_idx = (UINT32)pv_cmd_param;

                switch (ui4_repeat_idx)
                {
                    case MMP_VP_TB_STATUS_REPEAT_ONE:
                        break;
                    case MMP_VP_TB_STATUS_REPEAT_ALL:
                        break;
                    case MMP_VP_TB_STATUS_REPEAT_NONE:
                        break;
                    default:
                        break;
                }
            }
            break;

        case MMP_VP_TB_CMD_SET_SUBTITLE:
            {
            }
            break;

        case MMP_VP_TB_CMD_SET_TIME:
            {
                MMP_TB_POS_INFO_T*  pt_time = (MMP_TB_POS_INFO_T *)pv_cmd_param;
                CHAR                s_buf[MMP_TB_STRING_SIZE + 1] = {0};
                UTF16_T             ws_elapse_time_hint[MMP_TB_STRING_SIZE + 1] = {0};
                UTF16_T             ws_remain_time_hint[MMP_TB_STRING_SIZE + 1] = {0};
                MMP_UTIL_TIME_HMS_T t_time_hms = {0};
                INT32               i4_dura_percent = _mmp_tb_calc_progress(pt_time);

                if (MMP_TB_POS_TYPE_TIME == pt_time->e_pos_type)
                {
                    /* set elapse time text */
                    c_memset(&t_time_hms, 0, sizeof(MMP_UTIL_TIME_HMS_T));
                    mmp_util_devide_time_code(pt_time->v.ui4_time_pos, &t_time_hms);

                    c_memset(s_buf, 0, sizeof(s_buf));
                    if(0 == pt_time->v.ui4_time_pos)
                    {
                        c_sprintf(s_buf, "%02d:%02d", t_time_hms.ui2_mm, t_time_hms.ui2_ss);
                    }
                    else if(0 != t_time_hms.ui2_hh)
                    {
                        c_sprintf(s_buf, "%02d:%02d:%02d", t_time_hms.ui2_hh, t_time_hms.ui2_mm, t_time_hms.ui2_ss);
                    }
                    else
                    {
                        c_sprintf(s_buf, "%02d:%02d", t_time_hms.ui2_mm, t_time_hms.ui2_ss);
                    }
                    c_uc_ps_to_w2s(s_buf, ws_elapse_time_hint, MMP_TB_STRING_SIZE);

                    _mmp_tb_set_text(pt_this->t_player_bar.h_elapse_time_hint, ws_elapse_time_hint, e_repaint_type);

                    /* set remain time text */
                    c_memset(&t_time_hms, 0, sizeof(MMP_UTIL_TIME_HMS_T));
                    mmp_util_devide_time_code(pt_time->u.ui4_time_dur - pt_time->v.ui4_time_pos, &t_time_hms);

                    c_memset(s_buf, 0, sizeof(s_buf));
                    if(0 != t_time_hms.ui2_hh)
                    {
                        c_sprintf(s_buf, "%02d:%02d:%02d", t_time_hms.ui2_hh, t_time_hms.ui2_mm, t_time_hms.ui2_ss);
                    }
                    else
                    {
                        c_sprintf(s_buf, "%02d:%02d", t_time_hms.ui2_mm, t_time_hms.ui2_ss);
                    }
                    c_uc_ps_to_w2s(s_buf, ws_remain_time_hint, MMP_TB_STRING_SIZE);

                    _mmp_tb_set_text(pt_this->t_player_bar.h_remain_time_hint, ws_remain_time_hint, e_repaint_type);
                }

                _mmp_tb_set_progress(pt_this->t_player_bar.h_progress_bar, i4_dura_percent, e_repaint_type);
            }
            break;

        case MMP_VP_TB_CMD_SET_FILEIDX:
            {
            }
            break;

        case MMP_VP_TB_CMD_SET_VOL_MUTE:
            {
                INT32             i4_mute_idx = (INT32)pv_cmd_param;

                switch (i4_mute_idx)
                {
                    case MMP_VP_TB_STATUS_VOL_MUTE:
                        break;
                    case MMP_VP_TB_STATUS_VOL_NORMAL:
                        break;
                    default:
                        break;
                }
            }
            break;

        case MMP_VP_TB_CMD_SET_VOL_PG:
            {
            }
            break;

        case MMP_VP_TB_CMD_SET_VOL_BAR_VISBI:
            {
            }
            break;

        case MMP_VP_TB_CMD_SET_FILENAME:
            {
            }
            break;

        case MMP_VP_TB_CMD_SET_TOPBAR:
            {
                INT32 i4_topbar_idx = (INT32)pv_cmd_param;

                switch (i4_topbar_idx)
                {
                    case MMP_VP_TB_STATUS_TOPBAR_SHOW:
                        _mmp_tb_frame_show(pt_this->h_top_bar, NULL_HANDLE, e_repaint_type);
                        break;

                    case MMP_VP_TB_STATUS_TOPBAR_HIDE:
                    default:
                        _mmp_tb_frame_hide(pt_this->h_top_bar, e_repaint_type);
                        break;
                }
            }
            break;

        case MMP_VP_TB_CMD_SET_CLEAR:
            {
                _mmp_tb_set_text(pt_this->t_player_bar.h_elapse_time_hint, NULL, e_repaint_type);
                _mmp_tb_set_text(pt_this->t_player_bar.h_remain_time_hint, NULL, e_repaint_type);
                _mmp_tb_set_progress(pt_this->t_player_bar.h_progress_bar, 0, e_repaint_type);
                _mmp_tb_load_icon(pt_this->h_play_icon, NULL_HANDLE, e_repaint_type);
            }
            break;

        case MMP_VP_TB_CMD_ACTIVE_TIME_BOX:
            {
                UINT32 ui4_position = (UINT32)pv_cmd_param;
                _mmp_vp_start_to_set_time(ui4_position);
            }
            break;

        case MMP_VP_TB_CMD_INACTIVE_TIME_BOX:
            {
                _mmp_vp_stop_to_set_time(TRUE);
            }
            break;

        default:
            break;
    }

    return MMPR_OK;
}

static INT32 _mmp_ap_tb_cmd_do(MMP_TB_CMD_ID_T e_cmd_id,
                            VOID*        pv_cmd_param,
                            MMP_TB_REPAINT_TYPE_T         e_repaint_type)
{
    MMP_AP_TB_VIEW_T *pt_this   = &t_ap_tb_view;
    INT32  i4_ret=0;
    WGL_HIMG_TPL_T h_img_tpl=NULL_HANDLE;
    UTF16_T        ws_times_hint[MMP_TB_STRING_SIZE]={0};

    switch (e_cmd_id)
    {
        case MMP_AP_TB_CMD_SET_PLAY_STATUS:
            {
                UINT32         ui4_play_status = (UINT32)pv_cmd_param;

                switch (ui4_play_status)
                {
                    case MMP_AP_TB_STATUS_PAUSE:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_AP_TB_STATUS_STOP:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_AP_TB_STATUS_PLAY:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                i4_ret=_mmp_tb_set_text(pt_this->h_times_hint, NULL, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret=_mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_FF:
            {
                h_img_tpl = NULL_HANDLE;

                i4_ret=_mmp_tb_format_string(MMP_TB_FORMAT_TYPE_FF_FR, ws_times_hint, pv_cmd_param);
                MMPR_LOG_ON_FAIL(i4_ret);
                i4_ret=_mmp_tb_set_text(pt_this->h_times_hint, ws_times_hint, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
                i4_ret=_mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_FR:
            {
                h_img_tpl = NULL_HANDLE;
                i4_ret=_mmp_tb_format_string(MMP_TB_FORMAT_TYPE_FF_FR, ws_times_hint, pv_cmd_param);
                MMPR_LOG_ON_FAIL(i4_ret);
                i4_ret=_mmp_tb_set_text(pt_this->h_times_hint, ws_times_hint, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
                i4_ret=_mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_REPEAT_AB:
            {
                UINT32         ui4_repeat_idx = (UINT32)pv_cmd_param;

                switch (ui4_repeat_idx)
                {
                    case MMP_AP_TB_STATUS_REPEAT_AB:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_AP_TB_STATUS_REPEAT_AB_AB:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_AP_TB_STATUS_REPEAT_AB_A:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_AP_TB_STATUS_REPEAT_AB_NONE:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                i4_ret=_mmp_tb_load_icon(pt_this->h_repeat_ab_icon, h_img_tpl, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_REPEAT:
            {
                UINT32         ui4_repeat_idx = (UINT32)pv_cmd_param;
                UTF16_T        *ws_repeat_hint=NULL;

                switch (ui4_repeat_idx)
                {
                    case MMP_AP_TB_STATUS_REPEAT_ONE:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_VP_REPEAT_SINGLE);
                        break;
                    case MMP_AP_TB_STATUS_REPEAT_ALL:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_VP_REPEAT_ALL);
                        break;
                    case MMP_AP_TB_STATUS_REPEAT_NONE:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_EMPTY);
                        break;
                }
                i4_ret=_mmp_tb_load_icon(pt_this->t_player_bar.h_repeat_icon, h_img_tpl, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
                i4_ret=_mmp_tb_set_text(pt_this->t_player_bar.h_repeat_hint, ws_repeat_hint, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_SHUFFLE:
            {
                UINT32         ui4_shuffle_idx = (UINT32)pv_cmd_param;

                switch (ui4_shuffle_idx)
                {
                    case MMP_AP_TB_STATUS_SHUFFLE_MODE_SHUFFLE:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_AP_TB_STATUS_SHUFFLE_MODE_SEQUENTIAL:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                i4_ret=_mmp_tb_load_icon(pt_this->t_player_bar.h_shuffle_icon, h_img_tpl, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

         case MMP_AP_TB_CMD_SET_TIME:
            {
                MMP_TB_POS_INFO_T *pt_time = (MMP_TB_POS_INFO_T *)pv_cmd_param;
                UTF16_T            ws_dura_cur_hint[MMP_TB_STRING_SIZE]={0};
                UTF16_T            ws_dura_total_hint[MMP_TB_STRING_SIZE]={0};
                INT32              i4_dura_percent = _mmp_tb_calc_progress(pt_time);

                if (MMP_TB_POS_TYPE_TIME == pt_time->e_pos_type)
                {
                    i4_ret=_mmp_tb_format_string(MMP_TB_FORMAT_TYPE_DURATION,
                                             ws_dura_cur_hint,
                                                 (VOID *)(pt_time->v.ui4_time_pos));
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret=_mmp_tb_set_text(pt_this->t_player_bar.h_dura_cur_hint,
                                        ws_dura_cur_hint,
                                        e_repaint_type);
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret=_mmp_tb_format_string(MMP_TB_FORMAT_TYPE_DURATION,
                                             ws_dura_total_hint,
                                                 (VOID *)(pt_time->u.ui4_time_dur));
                    MMPR_LOG_ON_FAIL(i4_ret);

                    i4_ret=_mmp_tb_set_text(pt_this->t_player_bar.h_dura_total_hint,
                                        ws_dura_total_hint,
                                        e_repaint_type);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }

                i4_ret=_mmp_tb_set_progress(pt_this->t_player_bar.h_duration_bar,
                                            i4_dura_percent,
                                            e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_FILEIDX:
            {
                UTF16_T *ws_display = (UTF16_T *)pv_cmd_param;

                i4_ret=_mmp_tb_set_text(pt_this->t_player_bar.h_fileidx_hint,
                                        ws_display,
                                        e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_VOL_MUTE:
            {
                INT32             i4_mute_idx = (INT32)pv_cmd_param;

                switch (i4_mute_idx)
                {
                    case MMP_AP_TB_STATUS_VOL_MUTE:
                        h_img_tpl = NULL_HANDLE;

                        i4_ret = _mmp_tb_widget_hide(pt_this->t_player_bar.h_volinfo_bar, e_repaint_type);
                        MMPR_LOG_ON_FAIL(i4_ret);
                        break;

                    case MMP_AP_TB_STATUS_VOL_NORMAL:
                    default:
                        h_img_tpl = NULL_HANDLE;

                        if (b_g_vol_bar_hide)
                        {
                            i4_ret = _mmp_tb_widget_hide(pt_this->t_player_bar.h_volinfo_bar, e_repaint_type);
                            MMPR_LOG_ON_FAIL(i4_ret);
                        }
                        else
                        {
                            i4_ret = _mmp_tb_widget_show(pt_this->t_player_bar.h_volinfo_bar, e_repaint_type);
                            MMPR_LOG_ON_FAIL(i4_ret);
                        }

                        break;
                }

                i4_ret = _mmp_tb_load_icon(pt_this->t_player_bar.h_volinfo_icon,
                                           h_img_tpl,
                                           e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_VOL_PG:
            {
                INT32 i4_vol_percent = (INT32)pv_cmd_param;

                i4_ret = _mmp_tb_set_progress(pt_this->t_player_bar.h_volinfo_bar,
                                              i4_vol_percent,
                                              e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_VOL_BAR_VISBI:
            {
                BOOL b_visibility = (INT32)pv_cmd_param;

                b_g_vol_bar_hide = !b_visibility;
                if (b_g_vol_bar_hide)
                {
                    i4_ret = _mmp_tb_widget_hide(pt_this->t_player_bar.h_volinfo_bar, e_repaint_type);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = _mmp_tb_widget_show(pt_this->t_player_bar.h_volinfo_bar, e_repaint_type);
                    MMPR_LOG_ON_FAIL(i4_ret);
                }
            }
            break;

        case MMP_AP_TB_CMD_SET_FILENAME:
            {
                UTF16_T *ws_display = (UTF16_T *)pv_cmd_param;

                i4_ret = _mmp_tb_set_text(pt_this->t_player_bar.h_filename_hint,
                                          ws_display,
                                          e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_AP_TB_CMD_SET_TOPBAR:
            {
                INT32 i4_topbar_idx = (INT32)pv_cmd_param;

                switch (i4_topbar_idx)
                {
                    case MMP_AP_TB_STATUS_TOPBAR_SHOW:
                        i4_ret = _mmp_tb_frame_show(pt_this->h_top_bar,
                                                    NULL_HANDLE,
                                                    e_repaint_type);
                        MMPR_LOG_ON_FAIL(i4_ret);
                        break;

                    case MMP_AP_TB_STATUS_TOPBAR_HIDE:
                    default:
                        i4_ret = _mmp_tb_frame_hide(pt_this->h_top_bar,
                                                    e_repaint_type);
                        MMPR_LOG_ON_FAIL(i4_ret);
                        break;
                }
            }
            break;

        case MMP_AP_TB_CMD_SET_CLEAR:
            {
                i4_ret = _mmp_tb_set_text(pt_this->t_player_bar.h_fileidx_hint,
                                          NULL,
                                          e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = _mmp_tb_set_text(pt_this->t_player_bar.h_filename_hint,
                                          NULL,
                                          e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = _mmp_tb_set_text(pt_this->t_player_bar.h_dura_cur_hint,
                                          NULL,
                                          e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = _mmp_tb_set_text(pt_this->t_player_bar.h_dura_total_hint,
                                          NULL,
                                          e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = _mmp_tb_set_progress(pt_this->t_player_bar.h_duration_bar,
                                              0,
                                              e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = _mmp_tb_set_text(pt_this->h_times_hint, NULL, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);

                i4_ret = _mmp_tb_load_icon(pt_this->h_play_icon, NULL_HANDLE, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        default:
            break;
    }

    return MMPR_OK;
}

static INT32 _mmp_tp_tb_cmd_do(MMP_TB_CMD_ID_T e_cmd_id,
                            VOID*        pv_cmd_param,
                            MMP_TB_REPAINT_TYPE_T         e_repaint_type)
{
    MMP_TP_TB_VIEW_T *pt_this   = &t_tp_tb_view;

    switch (e_cmd_id)
    {
        case MMP_TP_TB_CMD_SET_PLAY_STATUS:
            {
                UINT32         ui4_play_status = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T h_img_tpl;

                switch (ui4_play_status)
                {
                    case MMP_TP_TB_STATUS_PAUSE:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_TP_TB_STATUS_STOP:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_TP_TB_STATUS_PLAY:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                _mmp_tb_load_icon(pt_this->h_play_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_TP_TB_CMD_SET_REPEAT:
            {
                INT32          i4_ret;
                UINT32         ui4_repeat_idx = (UINT32)pv_cmd_param;
                UTF16_T        *ws_repeat_hint=NULL;
                WGL_HIMG_TPL_T h_img_tpl=NULL_HANDLE;

                switch (ui4_repeat_idx)
                {
                    case MMP_TP_TB_STATUS_REPEAT_ONE:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_VP_REPEAT_SINGLE);
                        break;
                    case MMP_TP_TB_STATUS_REPEAT_ALL:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_VP_REPEAT_ALL);
                        break;
                    case MMP_TP_TB_STATUS_REPEAT_NONE:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        ws_repeat_hint = mlm_mmp_get_text(ui2_g_lang, MLM_MMP_KEY_EMPTY);
                        break;
                }
                i4_ret=_mmp_tb_load_icon(pt_this->t_player_bar.h_repeat_icon, h_img_tpl, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
                i4_ret=_mmp_tb_set_text(pt_this->t_player_bar.h_repeat_hint, ws_repeat_hint, e_repaint_type);
                MMPR_LOG_ON_FAIL(i4_ret);
            }
            break;

        case MMP_TP_TB_CMD_SET_SHUFFLE:
            {
                UINT32         ui4_shuffle_idx = (UINT32)pv_cmd_param;
                WGL_HIMG_TPL_T h_img_tpl;

                switch (ui4_shuffle_idx)
                {
                    case MMP_TP_TB_STATUS_SHUFFLE_MODE_SHUFFLE:
                        h_img_tpl = NULL_HANDLE;
                        break;
                    case MMP_TP_TB_STATUS_SHUFFLE_MODE_SEQUENTIAL:
                    default:
                        h_img_tpl = NULL_HANDLE;
                        break;
                }
                _mmp_tb_load_icon(pt_this->t_player_bar.h_shuffle_icon, h_img_tpl, e_repaint_type);
            }
            break;

        case MMP_TP_TB_CMD_SET_LANG:
            {
            }
            break;

        case MMP_TP_TB_CMD_SET_PAGEIDX:
            {
                UTF16_T *ws_display = (UTF16_T *)pv_cmd_param;

                _mmp_tb_set_text(pt_this->t_player_bar.h_pageidx_hint, ws_display, e_repaint_type);
            }
            break;

        case MMP_TP_TB_CMD_SET_FILEIDX:
            {
                UTF16_T *ws_display = (UTF16_T *)pv_cmd_param;

                _mmp_tb_set_text(pt_this->t_player_bar.h_fileidx_hint, ws_display, e_repaint_type);
            }
            break;

        case MMP_TP_TB_CMD_SET_FILENAME:
            {
                UTF16_T *ws_display = (UTF16_T *)pv_cmd_param;

                _mmp_tb_set_text(pt_this->t_player_bar.h_filename_hint, ws_display, e_repaint_type);
            }
            break;

        case MMP_TP_TB_CMD_SET_TOPBAR:
            {
                INT32 i4_topbar_idx = (INT32)pv_cmd_param;

                switch (i4_topbar_idx)
                {
                    case MMP_TP_TB_STATUS_TOPBAR_SHOW:
                        _mmp_tb_frame_show(pt_this->h_top_bar, NULL_HANDLE, e_repaint_type);
                        break;

                    case MMP_TP_TB_STATUS_TOPBAR_HIDE:
                    default:
                        _mmp_tb_frame_hide(pt_this->h_top_bar, e_repaint_type);
                        break;
                }
            }
            break;

        case MMP_TP_TB_CMD_SET_CLEAR:
            {
                _mmp_tb_set_text(pt_this->t_player_bar.h_fileidx_hint, NULL, e_repaint_type);
                _mmp_tb_set_text(pt_this->t_player_bar.h_filename_hint, NULL, e_repaint_type);
                _mmp_tb_set_text(pt_this->t_player_bar.h_pageidx_hint, NULL, e_repaint_type);
            }
            break;

        default:
            break;
    }

    return MMPR_OK;
}

static INT32 _mmp_pp_tb_view_active(MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret=0;
    MMP_PP_TB_VIEW_T *pt_this = &t_pp_tb_view;

    ui2_g_lang = _mmp_tb_get_mlm_lang_id();

    i4_ret = _mmp_tb_frame_show(pt_this->h_main_frm, NULL_HANDLE, e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_vp_tb_view_active(MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32               i4_ret;
    MMP_VP_TB_VIEW_T*   pt_this = &t_vp_tb_view;
    HANDLE_T            h_hidden_widget = NULL_HANDLE;

    ui2_g_lang = _mmp_tb_get_mlm_lang_id();

    i4_ret = _mmp_tb_frame_show(pt_this->h_main_frm, h_hidden_widget, e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_ap_tb_view_active(MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;
    MMP_AP_TB_VIEW_T *pt_this = &t_ap_tb_view;
    HANDLE_T h_hidden_widget = NULL_HANDLE;

    ui2_g_lang = _mmp_tb_get_mlm_lang_id();
    if (b_g_vol_bar_hide)
    {
        h_hidden_widget = pt_this->t_player_bar.h_volinfo_bar;
    }

    i4_ret = _mmp_tb_frame_show(pt_this->h_main_frm, h_hidden_widget, e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_tp_tb_view_active(MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;
    MMP_TP_TB_VIEW_T *pt_this = &t_tp_tb_view;

    ui2_g_lang = _mmp_tb_get_mlm_lang_id();

    i4_ret = _mmp_tb_frame_show(pt_this->h_main_frm, NULL_HANDLE, e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_pp_tb_view_inactive(MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;
    MMP_PP_TB_VIEW_T *pt_this = &t_pp_tb_view;

    i4_ret = _mmp_tb_frame_hide(pt_this->h_main_frm, e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_vp_tb_view_inactive(MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;
    MMP_VP_TB_VIEW_T *pt_this = &t_vp_tb_view;

    i4_ret = _mmp_tb_frame_hide(pt_this->h_main_frm, e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_ap_tb_view_inactive(MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;
    MMP_AP_TB_VIEW_T *pt_this = &t_ap_tb_view;

    i4_ret = _mmp_tb_frame_hide(pt_this->h_main_frm, e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

static INT32 _mmp_tp_tb_view_inactive(MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32 i4_ret;
    MMP_TP_TB_VIEW_T *pt_this = &t_tp_tb_view;

    i4_ret = _mmp_tb_frame_hide(pt_this->h_main_frm, e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);

    return MMPR_OK;
}

INT32 mmp_common_ui_toolbar_init(MMP_TB_PLAYER_TYPE_T e_player_type,
                                        HANDLE_T h_parent,
                                        VOID     **ppv_tb_inst)
{
    MMP_PLAYER_TB_VIEW_T *pt_this = NULL;
    INT32                i4_ret = MMPR_OK;

    ui2_g_lang = _mmp_tb_get_mlm_lang_id();

    pt_this = c_mem_alloc(sizeof(MMP_PLAYER_TB_VIEW_T));
    if (NULL == pt_this)
    {
        return MMPR_OUT_OF_MEM;
    }

    pt_this->e_player_type = e_player_type;
    switch (e_player_type)
    {
        case MMP_TB_PHOTO_PLAYER:
            i4_ret = _mmp_pp_tb_ui_init(h_parent);
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->e_toolbar_status     = MMP_TOOLBAR_HIDE;
            pt_this->pf_cmd_do_fct        = _mmp_pp_tb_cmd_do;
            pt_this->pf_view_active_fct   = _mmp_pp_tb_view_active;
            pt_this->pf_view_inactive_fct = _mmp_pp_tb_view_inactive;
            break;
        case MMP_TB_VIDEO_PLAYER:
            i4_ret = _mmp_vp_tb_ui_init(h_parent);
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->e_toolbar_status     = MMP_TOOLBAR_HIDE;
            pt_this->pf_cmd_do_fct        = _mmp_vp_tb_cmd_do;
            pt_this->pf_view_active_fct   = _mmp_vp_tb_view_active;
            pt_this->pf_view_inactive_fct = _mmp_vp_tb_view_inactive;
            break;
        case MMP_TB_AUDIO_PLAYER:
            i4_ret = _mmp_ap_tb_ui_init(h_parent);
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->e_toolbar_status     = MMP_TOOLBAR_HIDE;
            pt_this->pf_cmd_do_fct        = _mmp_ap_tb_cmd_do;
            pt_this->pf_view_active_fct   = _mmp_ap_tb_view_active;
            pt_this->pf_view_inactive_fct = _mmp_ap_tb_view_inactive;
            break;
        case MMP_TB_TEXT_PLAYER:
            i4_ret = _mmp_tp_tb_ui_init(h_parent);
            MMPR_LOG_ON_FAIL(i4_ret);

            pt_this->e_toolbar_status     = MMP_TOOLBAR_HIDE;
            pt_this->pf_cmd_do_fct        = _mmp_tp_tb_cmd_do;
            pt_this->pf_view_active_fct   = _mmp_tp_tb_view_active;
            pt_this->pf_view_inactive_fct = _mmp_tp_tb_view_inactive;
            break;
        default:
            break;
    }

    if (MMPR_OK != i4_ret)
    {
        if (NULL != pt_this)
        {
            c_mem_free(pt_this);
            return i4_ret;
        }
    }
    *ppv_tb_inst = pt_this;

    return i4_ret;
}

INT32 mmp_common_ui_toolbar_deinit(VOID *pv_tb_inst)
{
    INT32                i4_ret = MMPR_OK;
    MMP_PLAYER_TB_VIEW_T *pt_this = NULL;

    if (NULL == pv_tb_inst)
    {
        MMPR_LOG_ON_FAIL(MMPR_INV_ARG);
        return MMPR_INV_ARG;
    }

    pt_this = (MMP_PLAYER_TB_VIEW_T *)pv_tb_inst;
    switch (pt_this->e_player_type)
    {
        case MMP_TB_PHOTO_PLAYER:
            i4_ret = _mmp_pp_tb_ui_deinit();
            MMPR_LOG_ON_FAIL(i4_ret );
            break;
        case MMP_TB_VIDEO_PLAYER:
            i4_ret = _mmp_vp_tb_ui_deinit();
            MMPR_LOG_ON_FAIL(i4_ret );
            break;
        case MMP_TB_AUDIO_PLAYER:
            i4_ret = _mmp_ap_tb_ui_deinit();
            MMPR_LOG_ON_FAIL(i4_ret );
            break;
        case MMP_TB_TEXT_PLAYER:
            i4_ret = _mmp_tp_tb_ui_deinit();
            MMPR_LOG_ON_FAIL(i4_ret );
            break;
        default:
            break;
    }
    c_mem_free(pt_this);

    return MMPR_OK;
}

INT32 mmp_common_ui_toolbar_view_active(VOID *pv_tb_inst, MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32                i4_ret;
    MMP_PLAYER_TB_VIEW_T *pt_this = NULL;

    if (NULL == pv_tb_inst)
    {
        return MMPR_INV_ARG;
    }

    pt_this = (MMP_PLAYER_TB_VIEW_T *)pv_tb_inst;
    i4_ret = pt_this->pf_view_active_fct(e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    pt_this->e_toolbar_status = MMP_TOOLBAR_SHOW;
    return MMPR_OK;
}

INT32 mmp_common_ui_toolbar_view_inactive(VOID *pv_tb_inst, MMP_TB_REPAINT_TYPE_T e_repaint_type)
{
    INT32                i4_ret;
    MMP_PLAYER_TB_VIEW_T *pt_this = NULL;

    if (NULL == pv_tb_inst)
    {
        return MMPR_INV_ARG;
    }

    pt_this = (MMP_PLAYER_TB_VIEW_T *)pv_tb_inst;
    i4_ret = pt_this->pf_view_inactive_fct(e_repaint_type);
    MMPR_LOG_ON_FAIL(i4_ret);
    if (MMPR_OK != i4_ret)
    {
        return i4_ret;
    }

    pt_this->e_toolbar_status = MMP_TOOLBAR_HIDE;
    return MMPR_OK;
}

INT32 mmp_common_ui_toolbar_cmd_do(VOID *pv_tb_inst,
                           MMP_TB_CMD_ID_T e_cmd_id,
                           VOID*        pv_cmd_param,
                           MMP_TB_REPAINT_TYPE_T         e_repaint_type)
{
    INT32                i4_ret;
    MMP_PLAYER_TB_VIEW_T *pt_this = NULL;

    if (NULL == pv_tb_inst)
    {
        return MMPR_INV_ARG;
    }

    pt_this = (MMP_PLAYER_TB_VIEW_T *)pv_tb_inst;
    if (pt_this->e_toolbar_status == MMP_TOOLBAR_HIDE)
    {
        i4_ret = pt_this->pf_cmd_do_fct(e_cmd_id, pv_cmd_param, MMP_TB_NON_REPAINT);
    }
    else
    {
        i4_ret = pt_this->pf_cmd_do_fct(e_cmd_id, pv_cmd_param, e_repaint_type);
    }
    MMPR_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 mmp_common_ui_toolbar_time_box_reg(const mmp_tb_time_box_cb  pt_time_box_cb,
                                                    VOID* pv_tag)
{
    t_vp_tb_view.t_player_bar.pt_time_box_cb = pt_time_box_cb;

    return MMPR_OK;
}

INT32 mmp_common_ui_toolbar_get_main_frm(HANDLE_T *ph_handle)
{
    *ph_handle = mmp_ap_tb_get_wgt_hdl(WID_MMP_AP_TB_FRM_MAIN_FRM);

    return MMPR_OK;
}
