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
 * $RCSfile: pop_view.c,v $
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
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"
#include "u_sb.h"
#include "u_wgl_rect.h"

#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_handle.h"
#include "c_wgl_rect.h"

#include "app_util/a_tv.h"
#include "msgconvert/a_msgconvert.h"
#include "nav/pop/pop.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "res/nav/pop/pop_custom.h"
#include "res/nav/nav_variant.h"
#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT                 TRUE
#define MOVE_REPAINT_MODE               WGL_SYNC_AUTO_REPAINT
#ifndef POP_MAX_POS_DIFF_THRESHOLD
#define POP_MAX_POS_DIFF_THRESHOLD      (60)
#endif

#ifdef APP_IMG_UI
#define FRAME_STYLE                    (NULL)
#else
#define FRAME_STYLE                    ((VOID*)(WGL_STL_GL_NO_IMG_UI))
#endif

#ifdef POP_ICON_MUSIC_W
#define POP_USE_ICON    (1)
#else
#define POP_USE_ICON    (0)
#endif

typedef enum _RECT_BG_TYPE_T
{
    RECT_BG_TYPE_UNKNOWN = 0,
    RECT_BG_TYPE_SAME_AS_MUTE_COLOR,
    RECT_BG_TYPE_TRANSPARENT_COLOR,
    RECT_BG_TYPE_BLACK_COLOR
} RECT_BG_TYPE_T;

typedef struct _POP_WARNING_MSG_T
{
    HANDLE_T    h_warning_frm;
    HANDLE_T    h_txt_txtinfo;
    HANDLE_T    h_ok_btn;
} POP_WARNING_MSG_T;

typedef struct _POP_VIEW_T
{
    POP_T*                      pt_ctrl;
    HANDLE_T                    h_base_frame;
    POP_WARNING_MSG_T           t_warning_msg;
    HANDLE_T                    h_frames[TV_WIN_ID_LAST_VALID_ENTRY];
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    HANDLE_T                    h_base_frame_mib;
    HANDLE_T                    h_frames_mib[TV_WIN_ID_LAST_VALID_ENTRY];
#endif
    GL_RECT_T                   t_win_rects[TV_WIN_ID_LAST_VALID_ENTRY];
    BOOL                        b_frames_hidden;
    BOOL                        b_in_pop_resizing;
    BOOL                        b_is_size_or_pos_changing;
    HANDLE_T                    h_show_timer;
    RECT_BG_TYPE_T              e_crnt_rect_bg_types[TV_WIN_ID_LAST_VALID_ENTRY];

#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
    POP_VIEW_MSG_RC_T           t_msg_rc;
    HANDLE_T                    h_msg_frame;
    HANDLE_T                    h_msg;
    HANDLE_T                    h_hide_timer;
    BOOL                        b_is_msg_on;
#endif

#ifdef APP_IMG_UI
    WGL_HIMG_TPL_T              h_img_bk;
#endif

#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
    POP_VIEW_REASON_MSG_RC_T    t_nv_reason_msg_rc;
    HANDLE_T                    h_nv_reason_msgs[TV_WIN_ID_LAST_VALID_ENTRY];
    POP_RECT_BG_CMD_T           e_rect_bg_cmd[TV_WIN_ID_LAST_VALID_ENTRY];
  #ifdef APP_CC_WITH_SOLE_OSD_PLANE
    HANDLE_T                    h_nv_reason_msgs_mib[TV_WIN_ID_LAST_VALID_ENTRY];
  #endif
#endif
#if (POP_USE_ICON == 1)
    HANDLE_T    h_img_focus_win;
    HANDLE_T    h_icon_main;
    HANDLE_T    h_icon_sub;
#endif
} POP_VIEW_T;

#define IS_INSET_EMPTY(pt_inset)                                            \
        ( (pt_inset)->i4_left  == 0 || (pt_inset)->i4_right == 0            \
                || (pt_inset)->i4_top  == 0 || (pt_inset)->i4_bottom == 0 )
#define FRAME_DELAY_TO_SHOW_TIMEOUT         (400)
#define WARNING_OSD_TIMEOUT                 (10000)

typedef enum
{
    POP_TIMER_TYPE_FRAME = 0,
    POP_TIMER_TYPE_WARNING_OSD,
    POP_TIMER_TYPE_LAST_ENTRY
} POP_TIMER_TYPE_T;

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
BOOL b_g_pop_ignore_detect = POP_USE_ICON;
static POP_VIEW_T t_g_pop_view = {0};
#ifdef APP_IN_PALETTE_MODE
    const GL_COLOR_T t_g_black_color      = BLACK_COLOR;
    const GL_COLOR_T t_g_transparent      = TRANSPARENT_COLOR;
    const GL_COLOR_T t_g_video_mute_color = VIDEO_MUTE_COLOR;
    const GL_COLOR_T t_g_pop_color_warning_msg_bk = BLACK_COLOR;
    const GL_COLOR_T t_g_pop_color_warning_msg_txt = NAV_COLOR_WHITE; /* white color */
#else
    const GL_COLOR_T t_g_black_color = { 0xff, { 0x00 }, { 0x00 }, { 0x00 } };
    const GL_COLOR_T t_g_transparent = { 0x00, { 0x00 }, { 0x00 }, { 0x00 } };
    const GL_COLOR_T t_g_pop_color_warning_msg_bk = {0, {0 }, {0 }, {0 } };
    const GL_COLOR_T t_g_pop_color_warning_msg_txt = { 255, {255 }, {255 }, {255}}; /* white color */
#endif

static WGL_HIMG_TPL_T              h_g_pop_warning_bk;
static WGL_HIMG_TPL_T              h_g_pop_warning_btn;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_borders
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show_borders(
                    POP_VIEW_T*                 pt_view,
                    BOOL                        b_show
                    )
{
    const WGL_INSET_T t_empty_win_bdr = {0, 0, 0, 0};
    TV_WIN_ID_T       e_focus_id;
    INT32             i4_ret;

    i4_ret = nav_get_focus_id(&e_focus_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames[TV_WIN_ID_MAIN],
                    WGL_CMD_GL_SET_INSET,
                    (b_show == TRUE ? WGL_PACK(e_focus_id == TV_WIN_ID_MAIN ? &t_g_pop_win_focus_bdr : &t_g_pop_win_blur_bdr) : WGL_PACK(&t_empty_win_bdr)),
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames[TV_WIN_ID_SUB],
                    WGL_CMD_GL_SET_INSET,
                    (b_show == TRUE ? WGL_PACK(e_focus_id == TV_WIN_ID_SUB ? &t_g_pop_win_focus_bdr : &t_g_pop_win_blur_bdr) : WGL_PACK(&t_empty_win_bdr)),
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames_mib[TV_WIN_ID_MAIN],
                    WGL_CMD_GL_SET_INSET,
                    (b_show == TRUE ? WGL_PACK(e_focus_id == TV_WIN_ID_MAIN ? &t_g_pop_win_focus_bdr : &t_g_pop_win_blur_bdr) : WGL_PACK(&t_empty_win_bdr)),
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames_mib[TV_WIN_ID_SUB],
                    WGL_CMD_GL_SET_INSET,
                    (b_show == TRUE ? WGL_PACK(e_focus_id == TV_WIN_ID_SUB ? &t_g_pop_win_focus_bdr : &t_g_pop_win_blur_bdr) : WGL_PACK(&t_empty_win_bdr)),
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif

    pt_view->b_frames_hidden = b_show == TRUE ? FALSE : TRUE;

    return NAVR_OK;
}
#if (POP_USE_ICON == 1)
static INT32 _pop_view_show_icon (POP_VIEW_T* pt_view, BOOL b_show_border)
{
    INT32 i4_ret;
    WGL_SW_CMD_T e_sw_cmd_main, e_sw_cmd_sub;
    TV_WIN_ID_T e_focus_win;
    TV_MODE_T e_tv_mode;

    i4_ret = nav_get_tv_mode (&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = nav_get_focus_id(&e_focus_win);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (b_show_border)
    {
        if (e_focus_win == TV_WIN_ID_MAIN)
        {
            i4_ret = c_wgl_insert (pt_view->h_icon_main,
                                   NULL_HANDLE,
                                   WGL_INSERT_TOPMOST,
                                   FALSE);
            if(i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
            e_sw_cmd_main = WGL_SW_NORMAL;
            e_sw_cmd_sub = WGL_SW_HIDE;
        }
        else
        {
            i4_ret = c_wgl_insert (pt_view->h_icon_sub,
                                   NULL_HANDLE,
                                   WGL_INSERT_TOPMOST,
                                   FALSE);
            if(i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
            e_sw_cmd_main = WGL_SW_HIDE;
            e_sw_cmd_sub = WGL_SW_NORMAL;
        }
        /* Do not show icon if TV is power off. */
        if (nav_is_in_power_off ())
        {
            e_sw_cmd_main = WGL_SW_HIDE;
            e_sw_cmd_sub = WGL_SW_HIDE;
        }
    }
    else
    {
        e_sw_cmd_main = WGL_SW_HIDE;
        e_sw_cmd_sub = WGL_SW_HIDE;
    }
    i4_ret = c_wgl_set_visibility (pt_view->h_icon_main, e_sw_cmd_main);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility (pt_view->h_icon_sub, e_sw_cmd_sub);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }


    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_and_repaint_frames
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show_and_repaint_frames(
                    POP_VIEW_T*                 pt_view,
                    WGL_SW_CMD_T                e_sw_cmd,
                    BOOL                        b_show_border,
                    BOOL                        b_repaint,
                    BOOL                        b_shadow_first
                    )
{
    INT32 i4_ret;

    i4_ret = _pop_view_show_borders(pt_view, b_show_border);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    if (b_shadow_first == TRUE) {
        /* hide shadow first */
        i4_ret = c_wgl_set_visibility(pt_view->h_base_frame_mib, e_sw_cmd);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
        
        if (b_repaint == TRUE) {
            i4_ret = c_wgl_repaint(pt_view->h_base_frame_mib, NULL, IS_SYNC_REPAINT);
            if(WGLR_OK != i4_ret) {
                return NAVR_FAIL;
            }
        }
    }
#endif

    /* only set visibility if NOT tmp hide */
    if (!(e_sw_cmd == WGL_SW_HIDE && b_shadow_first == FALSE)) {
        i4_ret = c_wgl_set_visibility(pt_view->h_base_frame, e_sw_cmd);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
    }

#if (POP_USE_ICON == 1)
    /* Update the visibility of icons. DO NOT MOVE THIS TO OTHER WHERE. */
    i4_ret = _pop_view_show_icon (pt_view, b_show_border);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }
#endif

    if (b_repaint == TRUE) {
        i4_ret = c_wgl_repaint(pt_view->h_base_frame, NULL, IS_SYNC_REPAINT);
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    if (b_shadow_first == FALSE) {
        /* show shadow last */
        i4_ret = c_wgl_set_visibility(pt_view->h_base_frame_mib, e_sw_cmd);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
        
        if (b_repaint == TRUE) {
            i4_ret = c_wgl_repaint(pt_view->h_base_frame_mib, NULL, IS_SYNC_REPAINT);
            if(WGLR_OK != i4_ret) {
                return NAVR_FAIL;
            }
        }
    }
#endif
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
static VOID _pop_view_timeout_to_show(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    POP_VIEW_T* pt_view = (POP_VIEW_T*)pv_tag;
    POP_TIMER_TYPE_T e_timer_type = (POP_TIMER_TYPE_T)(UINT32)pv_tag2;

    if (e_timer_type == POP_TIMER_TYPE_FRAME)
    {
        if (pt_view->b_in_pop_resizing == TRUE && pt_view->b_frames_hidden == TRUE) {
            pt_view->b_in_pop_resizing = FALSE;
            _pop_view_show_and_repaint_frames(
                        pt_view,
                        WGL_SW_RECURSIVE,
                        TRUE,
                        TRUE,
                        FALSE
                        );
        }
    }
    else if (e_timer_type == POP_TIMER_TYPE_WARNING_OSD)
    {
        nav_hide_component (NAV_COMP_ID_PIP_POP);
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_show_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_pop_view_timeout_to_show, pv_tag, (VOID*)(UINT32)POP_TIMER_TYPE_FRAME, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_warning_osd_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_warning_osd_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_pop_view_timeout_to_show, pv_tag, (VOID*)(UINT32)POP_TIMER_TYPE_WARNING_OSD, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_stop_show_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_stop_show_timer(
                    POP_VIEW_T*                 pt_view
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_view->h_show_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_view->h_show_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop pop::h_show_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_reset_show_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_reset_show_timer(
                    POP_VIEW_T*                 pt_view
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_view->h_show_timer) == FALSE) {
        return;
    }

    _pop_view_stop_show_timer(pt_view);

    i4_ret = c_timer_start(
                    pt_view->h_show_timer,
                    FRAME_DELAY_TO_SHOW_TIMEOUT,
                    X_TIMER_FLAG_ONCE,
                    _pop_view_show_timer_nfy,
                    pt_view
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pop::h_show_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_reset_show_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_reset_warning_osd_timer(
                    POP_VIEW_T*                 pt_view
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_view->h_show_timer) == FALSE) {
        return;
    }

    _pop_view_stop_show_timer(pt_view);

    i4_ret = c_timer_start(
                    pt_view->h_show_timer,
                    WARNING_OSD_TIMEOUT,
                    X_TIMER_FLAG_ONCE,
                    _pop_view_warning_osd_timer_nfy,
                    pt_view
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pop::h_show_timer failed!"));
    }
}

#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_draw_no_video_message
 * Description
 *      if pw2s_msg_str != NULL, it will draw pw2s_msg_str first.
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_draw_no_video_message(
                    HANDLE_T                    h_nv_reason_msg,
                    POP_VIEW_T*                 pt_view,
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    POP_RECT_BG_CMD_T           e_cmd,
                    UTF16_T*                    pw2s_msg_str,
                    MSG_STR_ID_T                e_msg_str,
                    BOOL                        b_repaint
                    )
{
    WGL_COLOR_INFO_T t_clr_info;
    GL_RECT_T        t_rect;
    INT32            i4_ret;

    switch(e_cmd) {
    case POP_RECT_BG_CMD_SHOW:
        /* set message color */
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_disable   = pt_view->t_nv_reason_msg_rc.t_colors[e_tv_win_id];
        t_clr_info.u_color_data.t_standard.t_enable    = pt_view->t_nv_reason_msg_rc.t_colors[e_tv_win_id];
        t_clr_info.u_color_data.t_standard.t_highlight = pt_view->t_nv_reason_msg_rc.t_colors[e_tv_win_id];

        i4_ret = c_wgl_do_cmd(
                    h_nv_reason_msg,
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_TEXT,
                    &t_clr_info
                    );
        if(i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        switch(e_tv_mode) {
        case TV_MODE_TYPE_PIP:
            i4_ret = c_wgl_do_cmd(
                    h_nv_reason_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)pt_view->t_nv_reason_msg_rc.pt_pip_fonts[e_tv_win_id],
                    NULL
                    );
            if(i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
            break;
        case TV_MODE_TYPE_POP:
            i4_ret = c_wgl_do_cmd(
                    h_nv_reason_msg,
                    WGL_CMD_GL_SET_FONT,
                    (VOID*)pt_view->t_nv_reason_msg_rc.pt_pop_fonts[e_tv_win_id],
                    NULL
                    );
            if(i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
            break;
        default:
            break;
        }

        if (pw2s_msg_str != NULL) {
            i4_ret = c_wgl_do_cmd(
                        h_nv_reason_msg,
                        WGL_CMD_TEXT_SET_TEXT,
                        (VOID*)pw2s_msg_str,
                        (VOID*)(c_uc_w2s_strlen(pw2s_msg_str))
                        );
            if(i4_ret != WGLR_OK){
                return NAVR_FAIL;
            }
        } else {
            i4_ret = nav_draw_message_on_widget(h_nv_reason_msg, e_msg_str);
            if (i4_ret != NAVR_OK) {
                return NAVR_FAIL;
            }
        }

        i4_ret = c_wgl_set_visibility(h_nv_reason_msg, WGL_SW_NORMAL);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        SET_RECT_BY_SIZE(
                    &t_rect,
                    0,
                    0,
                    pt_view->t_win_rects[e_tv_win_id].i4_right  - pt_view->t_win_rects[e_tv_win_id].i4_left,
                    pt_view->t_win_rects[e_tv_win_id].i4_bottom - pt_view->t_win_rects[e_tv_win_id].i4_top
                    );
        i4_ret = c_wgl_move(
                    h_nv_reason_msg,
                    &t_rect,
                    b_repaint == TRUE ? WGL_SYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT
                    );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }
        break;
    case POP_RECT_BG_CMD_HIDE:
    case POP_RECT_BG_CMD_BLACK:
        i4_ret = c_wgl_do_cmd(
                    h_nv_reason_msg,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)NULL,
                    (VOID*)0
                    );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_set_visibility(h_nv_reason_msg, WGL_SW_HIDE);
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        if (b_repaint == TRUE) {
            i4_ret = c_wgl_repaint(
                    h_nv_reason_msg,
                    NULL,
                    IS_SYNC_REPAINT
                    );
            if (i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
        }
        break;
    default:
        break;
    }
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_no_video_message
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show_no_video_message(
                    POP_VIEW_T*                 pt_view,
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    POP_RECT_BG_CMD_T           e_cmd,
                    BOOL                        b_update_cmd,
                    BOOL                        b_repaint
                    )
{
    MSG_STR_ID_T e_msg_str    = MSG_STR_ID_LAST_VALID_ENTRY;
    UTF16_T*     pw2s_msg_str = NULL;
    INT32        i4_ret;

    if (b_update_cmd == TRUE) {
        pt_view->e_rect_bg_cmd[e_tv_win_id] = e_cmd;
    }

#ifdef APP_ONLY_DISP_NO_VIDEO_REASON_FOR_SUB
    if (e_tv_win_id == TV_WIN_ID_MAIN) {
        /* since main's message would be possible to overlap with sub's video
         * and it cannot solve in one OSD plane (with top-most order),
         * so just hide it in this case.
         */
        e_cmd = POP_RECT_BG_CMD_HIDE;
    }
#endif
   
    if (e_cmd == POP_RECT_BG_CMD_SHOW) {
        do {
            LOCKED_STATUS_T           e_lock_status;
            NAV_AV_STATUS_T           e_av_status;
            VSH_SRC_RESOLUTION_INFO_T t_video_resolution;

            e_lock_status = nav_get_locked_status(e_tv_win_id);
            if (e_lock_status == LOCKED_STATUS_INP_SRC_LOCKED) {
                e_msg_str = MSG_STR_ID_LOCKED_INP;
                break;
            }

            if (nav_is_svl_empty(e_tv_win_id) == TRUE) {
                e_msg_str = MSG_STR_ID_SCAN_CH;
                break;
            }

            if (nav_is_signal_loss(e_tv_win_id) == TRUE) {
                e_msg_str = MSG_STR_ID_NO_SIGNAL;
                break;
            }

            if (e_lock_status == LOCKED_STATUS_CHANNEL_LOCKED) {
                e_msg_str = MSG_STR_ID_LOCKED_CH;
                break;
            }

            if (e_lock_status == LOCKED_STATUS_PROGRAM_RATING) {
                e_msg_str = MSG_STR_ID_LOCKED_PROG;
                break;
            }

            if (nav_is_hidden_ch(e_tv_win_id) == TRUE) {
                e_msg_str = MSG_STR_ID_HIDDEN_CH;
                break;
            }
            
            i4_ret = nav_get_crnt_video_res_info(e_tv_win_id, &t_video_resolution);
            if (i4_ret == NAVR_OK && t_video_resolution.e_timing_type == VSH_SRC_TIMING_NOT_SUPPORT) {
#ifdef MLM_NAV_KEY_MSG_SUB_NO_1080P
                if (t_video_resolution.b_is_progressive == TRUE && t_video_resolution.ui4_height == 1080) {
                    pw2s_msg_str = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_MSG_SUB_NO_1080P);
                } else {
                    e_msg_str = MSG_STR_ID_VIDEO_NOT_SUPPORT;
                }
#else
                e_msg_str = MSG_STR_ID_VIDEO_NOT_SUPPORT;
#endif
                break;
            }

            e_av_status = nav_get_av_status(e_tv_win_id);
            if (e_av_status == NAV_AV_STATUS_AUDIO_ONLY) {
                if (nav_is_video_hd_not_support(e_tv_win_id))
                {
                    e_msg_str = MSG_STR_ID_HD_VIDEO_NOT_SUPPORT;
                }
                else
                {
                    e_msg_str = MSG_STR_ID_AUDIO_PROG;
                }
                break;
            }

            if (e_av_status == NAV_AV_STATUS_NO_AUDIO_VIDEO) {
                if (nav_is_video_hd_not_support(e_tv_win_id))
                {
                    e_msg_str = MSG_STR_ID_HD_VIDEO_NOT_SUPPORT;
                }
                else
                {
                    e_msg_str = MSG_STR_ID_NO_AUDIO_VIDEO;
                }
                break;
            }

            return NAVR_FAIL;
        } while (0);
    }
    
    i4_ret = _pop_view_draw_no_video_message(
                    pt_view->h_nv_reason_msgs[e_tv_win_id],
                    pt_view,
                    e_tv_win_id,
                    e_tv_mode,
                    e_cmd,
                    pw2s_msg_str,
                    e_msg_str,
                    b_repaint
                    );
    
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = _pop_view_draw_no_video_message(
                    pt_view->h_nv_reason_msgs_mib[e_tv_win_id],
                    pt_view,
                    e_tv_win_id,
                    e_tv_mode,
                    e_cmd,
                    pw2s_msg_str,
                    e_msg_str,
                    b_repaint
                    );
    
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_pip_main_no_video_msg_as_sub_pos_change
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show_pip_main_no_video_msg_as_sub_pos_change(
                    POP_VIEW_T*                 pt_view,
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    GL_RECT_T*                  pt_win_rect,
                    BOOL                        b_repaint
                    )
{
#ifndef APP_ONLY_DISP_NO_VIDEO_REASON_FOR_SUB
    GL_RECT_T t_msg_rect;
    INT32     i4_width;
    INT32     i4_height;
    INT32     i4_ret;
    BOOL      b_is_overlapped = TRUE;

    if (e_tv_mode != TV_MODE_TYPE_PIP
                || e_tv_win_id != TV_WIN_ID_SUB
                || pt_view->e_rect_bg_cmd[TV_WIN_ID_MAIN] != POP_RECT_BG_CMD_SHOW) {
        return NAVR_OK;
    }

    /* check the sub's frame is cross msg box, if yes, remove the main's wording,
     * if no, restore the main's wording
     */
    i4_width  = pt_view->pt_ctrl->ui4_canvas_width/3;
    i4_height = 80;

    SET_RECT_BY_SIZE(
                    &t_msg_rect,
                    pt_view->pt_ctrl->ui4_canvas_width/2  - i4_width/2,
                    pt_view->pt_ctrl->ui4_canvas_height/2 - i4_height/2,
                    i4_width,
                    i4_height
                    );

    i4_ret = c_wgl_rect_is_cross(
                    &b_is_overlapped,
                    pt_win_rect,
                    &t_msg_rect
                    );
    if (i4_ret != WGLR_OK) {
        b_is_overlapped = TRUE;
    }

    _pop_view_show_no_video_message(
                    pt_view,
                    TV_WIN_ID_MAIN,
                    e_tv_mode,
                    b_is_overlapped == TRUE ? POP_RECT_BG_CMD_HIDE : POP_RECT_BG_CMD_SHOW,
                    FALSE,
                    b_repaint
                    );
#else
    _pop_view_show_no_video_message(
                    pt_view,
                    e_tv_win_id,
                    e_tv_mode,
                    e_tv_win_id == TV_WIN_ID_MAIN ? POP_RECT_BG_CMD_HIDE : POP_RECT_BG_CMD_SHOW,
                    FALSE,
                    b_repaint
                    );
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_create_nv_reason_msgs_mib
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_create_nv_reason_msgs_mib(
                    POP_VIEW_T*                 pt_view,
                    HANDLE_T                    h_canvas
                    )
{
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    GL_RECT_T t_rect = {0};
    INT32     i4_ret;

    /* create message */
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frames_mib[TV_WIN_ID_MAIN],
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32
                          | WGL_STL_TEXT_MULTILINE
                          | WGL_STL_TEXT_SMART_CUT
                          | WGL_STL_GL_NO_IMG_UI
                          | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_nv_reason_msgs_mib[TV_WIN_ID_MAIN]
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set align */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_nv_reason_msgs_mib[TV_WIN_ID_MAIN],
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)POP_NO_VIDEO_MSG_ALIGNMENT,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_create_widget(
                    pt_view->h_frames_mib[TV_WIN_ID_SUB],
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32
                          | WGL_STL_TEXT_MULTILINE
                          | WGL_STL_TEXT_SMART_CUT
                          | WGL_STL_GL_NO_IMG_UI
                          | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_nv_reason_msgs_mib[TV_WIN_ID_SUB]
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set align */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_nv_reason_msgs_mib[TV_WIN_ID_SUB],
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)POP_NO_VIDEO_MSG_ALIGNMENT,
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
 *      _pop_view_create_nv_reason_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_create_nv_reason_msgs(
                    POP_VIEW_T*                 pt_view,
                    HANDLE_T                    h_canvas
                    )
{
    GL_RECT_T t_rect = {0};
    INT32     i4_ret;

    i4_ret = pop_view_init_reason_msg_rc(&pt_view->t_nv_reason_msg_rc);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    /* create message */
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frames[TV_WIN_ID_MAIN],
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32
                          | WGL_STL_TEXT_MULTILINE
                          | WGL_STL_TEXT_SMART_CUT
                          | WGL_STL_GL_NO_IMG_UI
                          | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_nv_reason_msgs[TV_WIN_ID_MAIN]
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set align */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_nv_reason_msgs[TV_WIN_ID_MAIN],
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)POP_NO_VIDEO_MSG_ALIGNMENT,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_create_widget(
                    pt_view->h_frames[TV_WIN_ID_SUB],
                    HT_WGL_WIDGET_TEXT,
                    WGL_CONTENT_TEXT_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_TEXT_MAX_32
                          | WGL_STL_TEXT_MULTILINE
                          | WGL_STL_TEXT_SMART_CUT
                          | WGL_STL_GL_NO_IMG_UI
                          | WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_nv_reason_msgs[TV_WIN_ID_SUB]
                    );
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set align */
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_nv_reason_msgs[TV_WIN_ID_SUB],
                    WGL_CMD_TEXT_SET_ALIGN,
                    (VOID*)POP_NO_VIDEO_MSG_ALIGNMENT,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _pop_view_create_nv_reason_msgs_mib(
                    pt_view,
                    h_canvas
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#else
#define _pop_view_show_no_video_message(p1, p2, p3, p4, p5, p6)
#define _pop_view_show_pip_main_no_video_msg_as_sub_pos_change(p1, p2, p3, p4, p5)
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_is_allow_to_change_pos
 * Description
 *      The purpose of this function is to determine whether the music note & frame rect
 *      can be changed or not. If the position difference of the previous one and the new one
 *      is larger than a specified threhold, we allow the position to be changed.
 *      This is for CR 136364.
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static BOOL _pop_view_is_allow_to_change_pos (POP_VIEW_T* pt_view, GL_RECT_T* pt_old_pos_rect, GL_RECT_T* pt_new_pos_rect)
{
    if ((pt_view->b_is_size_or_pos_changing)||(ABS(((pt_old_pos_rect->i4_right - pt_old_pos_rect->i4_left) / 2) - ((pt_new_pos_rect->i4_right - pt_new_pos_rect->i4_left)/2)) > POP_MAX_POS_DIFF_THRESHOLD))
    {
        return TRUE;
    }
    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_update_win_rect
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_update_win_rect(
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    GL_RECT_T*                  pt_win_rect,
                    BOOL                        b_repaint
                    )
{
    POP_VIEW_T* pt_view = &t_g_pop_view;
    INT32       i4_ret;
    GL_RECT_T   t_old_pos_rect;
    TV_WIN_ID_T e_focus_win;

    nav_get_focus_id (&e_focus_win);
    if (!pt_view->b_frames_hidden && e_tv_win_id == TV_WIN_ID_SUB && e_focus_win == TV_WIN_ID_SUB)
    {
        c_wgl_get_coords (pt_view->h_frames[e_tv_win_id], WGL_COORDS_SCREEN, &t_old_pos_rect);
    }
    i4_ret = c_wgl_set_visibility(pt_view->h_frames[e_tv_win_id], WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_set_visibility(pt_view->h_frames_mib[e_tv_win_id], WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif

    if (pt_win_rect != NULL && !WGL_RECT_IS_EQUAL(&pt_view->t_win_rects[e_tv_win_id], pt_win_rect)) {
        pt_view->t_win_rects[e_tv_win_id] = *pt_win_rect;
#if (POP_USE_ICON == 1)
        if (e_tv_win_id == TV_WIN_ID_MAIN)
        {
            GL_RECT_T t_rect;
        
            SET_RECT_BY_SIZE(&t_rect, ((pt_win_rect->i4_right - pt_win_rect->i4_left)/2), 0, POP_ICON_MUSIC_W, POP_ICON_MUSIC_H);
            i4_ret = c_wgl_move(
                        pt_view->h_icon_main,
                        &t_rect,
                        WGL_NO_AUTO_REPAINT
                        );
        }
        else
        {
            GL_RECT_T t_rect = {0, 0, 0, 0};
        
            SET_RECT_BY_SIZE(&t_rect, ((pt_win_rect->i4_right - pt_win_rect->i4_left)/2), 0, POP_ICON_MUSIC_W, POP_ICON_MUSIC_H);

            if (!pt_view->b_frames_hidden && e_focus_win == TV_WIN_ID_SUB)
            {
                if (_pop_view_is_allow_to_change_pos (pt_view, &t_old_pos_rect, pt_win_rect))
                {
                    i4_ret = c_wgl_move(
                                pt_view->h_icon_sub,
                                &t_rect,
                                WGL_NO_AUTO_REPAINT
                                );
                    if (i4_ret != WGLR_OK) {
                        return NAVR_FAIL;
                    }
                }
            }
            else
            {
                i4_ret = c_wgl_move(
                            pt_view->h_icon_sub,
                            &t_rect,
                            WGL_NO_AUTO_REPAINT
                            );
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }

        }
#endif
        _pop_view_show_pip_main_no_video_msg_as_sub_pos_change(
                    pt_view,
                    e_tv_win_id,
                    e_tv_mode,
                    pt_win_rect,
                    FALSE
                    );
        if (!pt_view->b_frames_hidden && e_focus_win == TV_WIN_ID_SUB)
        {
            if (_pop_view_is_allow_to_change_pos (pt_view, &t_old_pos_rect, pt_win_rect))
            {
                i4_ret = c_wgl_move(
                            pt_view->h_frames[e_tv_win_id],
                            pt_win_rect,
                            (b_repaint == TRUE ? WGL_SYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT)
                            );
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
        }
        else
        {
            i4_ret = c_wgl_move(
                        pt_view->h_frames[e_tv_win_id],
                        pt_win_rect,
                        (b_repaint == TRUE ? WGL_SYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT)
                        );
            if (i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
        }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
        if (!pt_view->b_frames_hidden && e_focus_win == TV_WIN_ID_SUB)
        {
            if (_pop_view_is_allow_to_change_pos (pt_view, &t_old_pos_rect, pt_win_rect))
            {
                i4_ret = c_wgl_move(
                            pt_view->h_frames_mib[e_tv_win_id],
                            pt_win_rect,
                            (b_repaint == TRUE ? WGL_SYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT)
                            );
                if (i4_ret != WGLR_OK) {
                    return NAVR_FAIL;
                }
            }
        }
        else
        {
            i4_ret = c_wgl_move(
                        pt_view->h_frames_mib[e_tv_win_id],
                        pt_win_rect,
                        (b_repaint == TRUE ? WGL_SYNC_AUTO_REPAINT : WGL_NO_AUTO_REPAINT)
                        );
            if (i4_ret != WGLR_OK) {
                return NAVR_FAIL;
            }
        }
#endif
    } else {
#if 0
        if (b_repaint == TRUE) {
            i4_ret = c_wgl_repaint(
                    pt_view->h_frames[e_tv_win_id],
                    NULL,
                    IS_SYNC_REPAINT
                    );
            if(WGLR_OK != i4_ret) {
                return NAVR_FAIL;
            }
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
            i4_ret = c_wgl_repaint(
                    pt_view->h_frames_mib[e_tv_win_id],
                    NULL,
                    IS_SYNC_REPAINT
                    );
            if(WGLR_OK != i4_ret) {
                return NAVR_FAIL;
            }
#endif
        }
#endif
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_frames
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show_frames(
                    BOOL                        b_show
                    )
{
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    if ((!(IS_INSET_EMPTY(&t_g_pop_win_focus_bdr) && IS_INSET_EMPTY(&t_g_pop_win_blur_bdr))) || b_g_pop_ignore_detect) {
        /*
         *  A trick here.
         *  If b_g_pop_ignore_detect == TRUE, it means that there is no border.
         *  If POP_USE_ICON == 0, it means that there is no icon drawn.
         *  If two conditions above are met, it means nothing will be displayed on screen by POP.
         *  Hence, force MW to ignore visibility detect.
         */
        if (b_g_pop_ignore_detect && !POP_USE_ICON)
        {
            b_show = FALSE;
        }
        c_wgl_ignore_visibility_detect(
                    t_g_pop_view.h_base_frame,
                    (b_show == TRUE) ? FALSE : TRUE
                    );
    }
#endif

    return _pop_view_show_and_repaint_frames(
                    &t_g_pop_view,
                    WGL_SW_RECURSIVE,
                    b_show,
                    TRUE,
                    FALSE
                    );
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_set_skin
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_set_skin(
                    POP_VIEW_T*                 pt_view
                    )
{
    WGL_COLOR_INFO_T t_clr_info;
    GL_COLOR_T       t_bg_color = { 0x00, { 0x00 }, { 0x00 }, { 0x00 } };
    INT32            i4_ret;

    t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_highlight = t_bg_color;
    t_clr_info.u_color_data.t_standard.t_enable    = t_bg_color;
    t_clr_info.u_color_data.t_standard.t_disable   = t_bg_color;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames[TV_WIN_ID_MAIN],
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames[TV_WIN_ID_SUB],
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames_mib[TV_WIN_ID_MAIN],
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames_mib[TV_WIN_ID_SUB],
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif

    i4_ret = _pop_view_show_borders(
                    pt_view,
                    TRUE
                    );
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_create_audio_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_create_audio_msg(
                    POP_VIEW_T*                 pt_view,
                    HANDLE_T                    h_canvas
                    )
{
    GL_RECT_T        t_rect;
    WGL_COLOR_INFO_T t_clr_info;
    WGL_IMG_INFO_T   t_img_info;
    WGL_INSET_T      t_inset;
    INT32            i4_ret;

    pt_view->h_hide_timer = NULL_HANDLE;

    i4_ret = c_timer_create(&(pt_view->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(
                    &t_rect,
                    POP_MSG_FRAME_LEFT,
                    POP_MSG_FRAME_TOP,
                    POP_MSG_FRAME_WIDTH,
                    POP_MSG_FRAME_HEIGHT
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
                    &pt_view->h_msg_frame
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* create message */
    SET_RECT_BY_SIZE(
                    &t_rect,
                    POP_MSG_LEFT,
                    POP_MSG_TOP,
                    POP_MSG_WIDTH,
                    POP_MSG_HEIGHT
                    );
    i4_ret = c_wgl_create_widget(
                    pt_view->h_msg_frame,
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

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_view->t_msg_rc.h_img_bk;
    t_img_info.u_img_data.t_standard.t_highlight = pt_view->t_msg_rc.h_img_bk;
    t_img_info.u_img_data.t_standard.t_disable   = pt_view->t_msg_rc.h_img_bk;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg_frame,
                    WGL_CMD_GL_SET_IMAGE,
                    WGL_PACK(WGL_IMG_BK),
                    WGL_PACK(&t_img_info)
                    );
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* set message color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_disable   = pt_view->t_msg_rc.t_msg_fg;
    t_clr_info.u_color_data.t_standard.t_enable    = pt_view->t_msg_rc.t_msg_fg;
    t_clr_info.u_color_data.t_standard.t_highlight = pt_view->t_msg_rc.t_msg_fg;

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
                    (VOID*)pt_view->t_msg_rc.pt_msg_font,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    /* set event title inset */
    t_inset.i4_left   = POP_MSG_LEFT_INSET;
    t_inset.i4_right  = POP_MSG_RIGHT_INSET;
    t_inset.i4_top    = POP_MSG_TOP_INSET;
    t_inset.i4_bottom = POP_MSG_BOTTOM_INSET;

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
                    (VOID*)POP_MSG_ALIGNMENT,
                    NULL
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    pt_view->b_is_msg_on = FALSE;

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_set_focus
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_set_focus(
                    TV_WIN_ID_T                 e_focus_id,
                    TV_WIN_ID_T                 e_blur_id,
                    BOOL                        b_repaint
                    )
{
    POP_VIEW_T*      pt_view = &t_g_pop_view;
    WGL_COLOR_INFO_T t_clr_info;
    INT32            i4_ret;

    t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_pop_win_focus_color;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_pop_win_focus_color;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_pop_win_focus_color;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames[e_focus_id],
                    WGL_CMD_GL_SET_BDR_COLOR,
                    (VOID*)WGL_CLR_BDR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames_mib[e_focus_id],
                    WGL_CMD_GL_SET_BDR_COLOR,
                    (VOID*)WGL_CLR_BDR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif

    t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_pop_win_blur_color;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_pop_win_blur_color;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_pop_win_blur_color;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames[e_blur_id],
                    WGL_CMD_GL_SET_BDR_COLOR,
                    (VOID*)WGL_CLR_BDR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames_mib[e_blur_id],
                    WGL_CMD_GL_SET_BDR_COLOR,
                    (VOID*)WGL_CLR_BDR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif

    return _pop_view_show_and_repaint_frames(
                    pt_view,
                    WGL_SW_RECURSIVE,
                    TRUE,
                    b_repaint,
                    FALSE
                    );
}
#if 0
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_get_video_mute_color
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_get_video_mute_color(
                    TV_WIN_ID_T                 e_tv_win_id,
                    GL_COLOR_T*                 pt_color,
                    RECT_BG_TYPE_T*             pe_rect_bg_type
                    )
{
    HANDLE_T                h_svctx;
    SVCTX_VIDEO_MUTE_INFO_T t_mute_info;
    SIZE_T                  z_size;
    INT32                   i4_ret;

    i4_ret = nav_get_svctx_handle(e_tv_win_id, &h_svctx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    z_size = sizeof(SVCTX_VIDEO_MUTE_INFO_T);
    i4_ret = c_svctx_get(
                    h_svctx,
                    SVCTX_COMMON_GET_VIDEO_MUTE,
                    &t_mute_info,
                    &z_size
                    );
    if (i4_ret != SVCTXR_OK) {
        return NAVR_FAIL;
    }
#ifdef APP_IN_PALETTE_MODE
    if (t_mute_info.b_enable == TRUE) {
        if (t_mute_info.t_color.ui1_red == 0
                && t_mute_info.t_color.ui1_green == 0
                && t_mute_info.t_color.ui1_blue == 0) {
            *pt_color        = t_g_black_color;
            *pe_rect_bg_type = RECT_BG_TYPE_BLACK_COLOR;
        } else {
            *pt_color        = t_g_video_mute_color;
            *pe_rect_bg_type = RECT_BG_TYPE_SAME_AS_MUTE_COLOR;
        }        
    } else {
        *pt_color        = t_g_black_color;
        *pe_rect_bg_type = RECT_BG_TYPE_BLACK_COLOR;
    }
#else
    if (t_mute_info.b_enable == TRUE) {
        pt_color->a      = 0xff;
        pt_color->u1.r   = t_mute_info.t_color.ui1_red;
        pt_color->u2.g   = t_mute_info.t_color.ui1_green;
        pt_color->u3.b   = t_mute_info.t_color.ui1_blue;
        if (t_mute_info.t_color.ui1_red == 0
                && t_mute_info.t_color.ui1_green == 0
                && t_mute_info.t_color.ui1_blue == 0) {
            *pe_rect_bg_type = RECT_BG_TYPE_BLACK_COLOR;
        } else {
            *pe_rect_bg_type = RECT_BG_TYPE_SAME_AS_MUTE_COLOR;
        }        
    } else {
        *pt_color        = t_g_black_color;
        *pe_rect_bg_type = RECT_BG_TYPE_BLACK_COLOR;
    }
#endif

    DBG_INFO((_INFO_HEADER"set %s's OSD bgcolor to (%d, %d, %d, %d)\r\n",
                    (e_tv_win_id == TV_WIN_ID_MAIN ? "MAIN" : "SUB"),
                    pt_color->a,
                    pt_color->u1.r,
                    pt_color->u2.g,
                    pt_color->u3.b
                    ));

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_win_rect_bg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show_win_rect_bg(
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    POP_RECT_BG_CMD_T           e_cmd,
                    BOOL                        b_repaint
                    )
{
#if 0
    POP_VIEW_T*      pt_view    = &t_g_pop_view;
    GL_COLOR_T       t_bg_color = t_g_black_color;
    WGL_COLOR_INFO_T t_clr_info;
    INT32            i4_ret;
    RECT_BG_TYPE_T   e_rect_bg_type;
#endif
    /* show no video msg. should be kept. */
    _pop_view_show_no_video_message(&t_g_pop_view, e_tv_win_id, e_tv_mode, e_cmd, TRUE, FALSE);
    if (e_tv_win_id == TV_WIN_ID_MAIN) {
        _pop_view_show_pip_main_no_video_msg_as_sub_pos_change(
                    &t_g_pop_view,
                    TV_WIN_ID_SUB,
                    e_tv_mode,
                    &(t_g_pop_view.t_win_rects[TV_WIN_ID_SUB]),
                    FALSE
                    );
    }
#if 0
    /* when MAIN in POP, always hide background color */
    if (e_tv_win_id == TV_WIN_ID_MAIN && (e_tv_mode == TV_MODE_TYPE_PIP || e_tv_mode == TV_MODE_TYPE_NORMAL)) {
        e_cmd = POP_RECT_BG_CMD_HIDE;
    }

    switch (e_cmd) {
     case POP_RECT_BG_CMD_SHOW:
        i4_ret = _pop_view_get_video_mute_color(e_tv_win_id, &t_bg_color, &e_rect_bg_type);
        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        break;
    case POP_RECT_BG_CMD_HIDE:
        t_bg_color     = t_g_transparent;
        e_rect_bg_type = RECT_BG_TYPE_TRANSPARENT_COLOR;
        break;
    default:
        /* t_bg_color = black */
        e_rect_bg_type = RECT_BG_TYPE_BLACK_COLOR;
        break;
    }
#ifndef APP_PIP_POP_DISP_NO_VIDEO_REASON
    if (pt_view->e_crnt_rect_bg_types[e_tv_win_id] == e_rect_bg_type) {
        return NAVR_OK;
    }
#endif
    pt_view->e_crnt_rect_bg_types[e_tv_win_id] = e_rect_bg_type;

    t_clr_info.e_type                              = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_highlight = t_bg_color;
    t_clr_info.u_color_data.t_standard.t_enable    = t_bg_color;
    t_clr_info.u_color_data.t_standard.t_disable   = t_bg_color;

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames[e_tv_win_id],
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    if (b_repaint == TRUE) {
        i4_ret = c_wgl_set_visibility(
                    pt_view->h_frames[e_tv_win_id],
                    WGL_SW_NORMAL
                    );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_repaint(
                    pt_view->h_frames[e_tv_win_id],
                    NULL,
                    IS_SYNC_REPAINT
                    );
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_do_cmd(
                    pt_view->h_frames_mib[e_tv_win_id],
                    WGL_CMD_GL_SET_COLOR,
                    (VOID*)WGL_CLR_BK,
                    &t_clr_info
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    if (b_repaint == TRUE) {
        i4_ret = c_wgl_set_visibility(
                    pt_view->h_frames_mib[e_tv_win_id],
                    WGL_SW_NORMAL
                    );
        if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
        }

        i4_ret = c_wgl_repaint(
                    pt_view->h_frames_mib[e_tv_win_id],
                    NULL,
                    IS_SYNC_REPAINT
                    );
        if(WGLR_OK != i4_ret) {
            return NAVR_FAIL;
        }
    }
#endif

    DBG_INFO((_INFO_HEADER"set %s to %s\r\n",
                    (e_tv_win_id == TV_WIN_ID_MAIN ? "MAIN" : "SUB"),
                    (e_cmd == POP_RECT_BG_CMD_SHOW ? "SHOW" : (e_cmd == POP_RECT_BG_CMD_HIDE ? "HIDE" : "BLACK"))
                    ));
#endif
    return NAVR_OK;
}
#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
/*-----------------------------------------------------------------------------
 * Name
 *      __pop_view_stop_audio_msg_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_stop_audio_msg_timer(
                    POP_VIEW_T*                 pt_view
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_view->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_view->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop sleep::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_hide_audio_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_hide_audio_msg(
                    POP_VIEW_T*             pt_view
                    )
{
    INT32 i4_ret;

    if (pt_view->b_is_msg_on == FALSE) {
        return NAVR_OK;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_msg_frame, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_msg_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    pt_view->b_is_msg_on = FALSE;
    _pop_view_stop_audio_msg_timer(pt_view);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_timeout_to_hide_audio_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_timeout_to_hide_audio_msg(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _pop_view_hide_audio_msg((POP_VIEW_T*)pv_tag);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_sleep_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_hide_audio_msg_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_pop_view_timeout_to_hide_audio_msg, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_reset_audio_msg_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_view_reset_audio_msg_timer(
                    POP_VIEW_T*                 pt_view
                    )
{
    INT32 i4_ret;

    _pop_view_stop_audio_msg_timer(pt_view);

    i4_ret = c_timer_start(
                    pt_view->h_hide_timer,
                    POP_MSG_TIMEOUT,
                    X_TIMER_FLAG_ONCE,
                    _pop_view_hide_audio_msg_timer_nfy,
                    pt_view
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start pop::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_audio_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show_audio_msg(
                    POP_VIEW_T*             pt_view
                    )
{
    UTF16_T     w2s_string[48+1] = {0};
    TV_WIN_ID_T e_focus_id;
    UTF16_T*    pw2s_main_sub;
    INT32       i4_ret;

    i4_ret = pop_get_audio_focus_id(pt_view->pt_ctrl, &e_focus_id);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    pw2s_main_sub = MLM_NAV_TEXT(
                    nav_get_mlm_lang_id(),
                    (e_focus_id == TV_WIN_ID_MAIN ? MLM_NAV_KEY_IPTS_VIEW_MAIN : MLM_NAV_KEY_IPTS_VIEW_SUB)
                    );
    c_uc_w2s_strcat(w2s_string, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_TITLE_PIP_AUDIO));
    c_uc_w2s_strcat(w2s_string, pw2s_main_sub);

    i4_ret = c_wgl_do_cmd(
                    pt_view->h_msg,
                    WGL_CMD_TEXT_SET_TEXT,
                    (VOID*)w2s_string,
                    (VOID*)c_uc_w2s_strlen(w2s_string)
                    );
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_visibility(pt_view->h_msg_frame, WGL_SW_RECURSIVE);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_repaint(pt_view->h_msg_frame, NULL, IS_SYNC_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    pt_view->b_is_msg_on = TRUE;

    nav_set_component_visible (NAV_COMP_ID_PIP_POP);

    _pop_view_reset_audio_msg_timer(pt_view);

    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_show_warning_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show_warning_msg (POP_VIEW_T* pt_view, BOOL b_show)
{
    INT32 i4_ret = 0;
    BOOL b_is_displayed = FALSE, b_need_repaint = FALSE;
    
    i4_ret = c_wgl_get_visibility (pt_view->t_warning_msg.h_warning_frm, &b_is_displayed);
    if (i4_ret != WGLR_OK)
    {
        b_is_displayed = FALSE;
    }
    if (b_show)
    {
        if (!b_is_displayed)
        {
            nav_set_component_visible(NAV_COMP_ID_PIP_POP);
            
            c_wgl_set_visibility(pt_view->t_warning_msg.h_warning_frm, WGL_SW_RECURSIVE);
            c_wgl_set_focus(pt_view->t_warning_msg.h_warning_frm, FALSE);
            /* info AM when UI show. */
            a_tv_net_OSD_appear (); 
            b_need_repaint = TRUE;
        }
        _pop_view_reset_warning_osd_timer (pt_view);
    }
    else
    {
        if (b_is_displayed)
        {
            c_wgl_set_visibility(pt_view->t_warning_msg.h_warning_frm, WGL_SW_HIDE_RECURSIVE);
            /* info AM when UI hide. */
            a_tv_net_OSD_disapper();  
            b_need_repaint = TRUE;
            _pop_view_stop_show_timer(pt_view);
        }
    }
    if (b_need_repaint)
    {
        c_wgl_repaint(pt_view->t_warning_msg.h_warning_frm, 
                      NULL,
                      TRUE);
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_create_warning_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 static INT32 _pop_warning_msg_frm_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    POP_VIEW_T*             pt_view = &t_g_pop_view;
    APP_TV_NET_SVC_STATUS   t_svc_state;
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_SELECT:
        case BTN_EXIT:
        {
            nav_hide_component(NAV_COMP_ID_PIP_POP);
            break;
        }
        case BTN_PIP_POP:
        case BTN_PIP:
        case BTN_POP:
        {
            t_svc_state = a_tv_net_get_tv_svc_status();
            if(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
            {
                _pop_view_show_warning_msg (pt_view, TRUE);
                return NAVR_OK;
            }
            break;
        }
        default:
            nav_rcu_key_handler(ui4_keycode);
            return NAVR_OK;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);

}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_create_warning_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 static INT32 _pop_view_create_warning_msg(HANDLE_T h_parent, 
                                           POP_WARNING_MSG_T* pt_widget)
 {
    GL_RECT_T           t_rect;
    GL_RECT_T           t_inset;
    UINT32              ui4_style = 0;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    INT32               i4_ret;

    i4_ret = nav_img_create_pop_warning_bk_img_tpl(&h_g_pop_warning_bk);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = nav_img_create_pop_warning_btn_img_tpl(&h_g_pop_warning_btn);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));    
    SET_RECT_BY_SIZE(&t_rect, POP_VIEW_WARNING_OSD_X, POP_VIEW_WARNING_OSD_Y, POP_VIEW_WARNING_OSD_W, POP_VIEW_WARNING_OSD_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _pop_warning_msg_frm_proc_fct,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_widget->h_warning_frm);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_pop_warning_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_pop_warning_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_pop_warning_bk;
    i4_ret = c_wgl_do_cmd(pt_widget->h_warning_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
    
    ui4_style =  WGL_STL_GL_NO_IMG_UI | WGL_STL_TEXT_MAX_512;
             
    SET_RECT_BY_SIZE(&t_rect, POP_VIEW_WARNING_OSD_TXT_INFO_X, POP_VIEW_WARNING_OSD_TXT_INFO_Y, POP_VIEW_WARNING_OSD_TXT_INFO_W, POP_VIEW_WARNING_OSD_TXT_INFO_H);

    i4_ret = c_wgl_create_widget(pt_widget->h_warning_frm, 
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_widget->h_txt_txtinfo);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
    
    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(pt_widget->h_txt_txtinfo,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
    
    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_pop_color_warning_msg_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_pop_color_warning_msg_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_pop_color_warning_msg_txt;
    i4_ret = c_wgl_do_cmd(pt_widget->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_pop_color_warning_msg_bk;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_pop_color_warning_msg_bk;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_pop_color_warning_msg_bk;
    i4_ret = c_wgl_do_cmd(pt_widget->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
                          
    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_widget->h_txt_txtinfo,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = c_wgl_do_cmd(pt_widget->h_txt_txtinfo,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_PIP_POP_WARNING_MSG)),
                          WGL_PACK(c_uc_w2s_strlen(MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_PIP_POP_WARNING_MSG))));
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    SET_RECT_BY_SIZE(&t_rect, POP_VIEW_WARNING_OSD_BTN_X, POP_VIEW_WARNING_OSD_BTN_Y, POP_VIEW_WARNING_OSD_BTN_W, POP_VIEW_WARNING_OSD_BTN_H);

    i4_ret = c_wgl_create_widget(pt_widget->h_warning_frm,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                NULL,
                                NULL,
                                &pt_widget->h_ok_btn);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(pt_widget->h_ok_btn,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_pop_warning_btn;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_pop_warning_btn;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_pop_warning_btn;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_pop_warning_btn;
    t_img_info.u_img_data.t_extend.t_push               = h_g_pop_warning_btn;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_pop_warning_btn;

    i4_ret = c_wgl_do_cmd(pt_widget->h_ok_btn,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(& t_img_info));
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable = t_g_pop_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_disable = t_g_pop_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_highlight = t_g_pop_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_pop_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_push = t_g_pop_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight = t_g_pop_color_warning_msg_txt;
    i4_ret = c_wgl_do_cmd(pt_widget->h_ok_btn,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(pt_widget->h_ok_btn,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = c_wgl_do_cmd(pt_widget->h_ok_btn,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
    
    i4_ret = c_wgl_do_cmd(pt_widget->h_ok_btn,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_DIALOG_OK)),
                          WGL_PACK(c_uc_w2s_strlen(MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_DIALOG_OK))));
    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }
    
    c_wgl_set_visibility(pt_widget->h_warning_frm, WGL_SW_HIDE);

    return NAVR_OK;

 }
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_hide_audio_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_hide_msg(
                    VOID
                    )
{
    _pop_view_show_warning_msg (&t_g_pop_view, FALSE);

#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
    return _pop_view_hide_audio_msg(&t_g_pop_view);
#else
    return NAVR_OK;
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_hide(
                    BOOL                        b_tmp_hide
                    )
{
    POP_VIEW_T* pt_view = &t_g_pop_view;
    INT32       i4_ret;

#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
    i4_ret = _pop_view_hide_audio_msg(pt_view);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }
#endif

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    if ((!(IS_INSET_EMPTY(&t_g_pop_win_focus_bdr) && IS_INSET_EMPTY(&t_g_pop_win_blur_bdr))) || b_g_pop_ignore_detect) {
        if (b_tmp_hide == TRUE) {
            /*
             *  If b_g_pop_ignore_detect == FALSE, it means that music notes is not shown and
             *  there is no border. In this case, we should always ignore visibility detection.
             */
            if (!b_g_pop_ignore_detect)
            {
                c_wgl_ignore_visibility_detect(pt_view->h_base_frame, FALSE);
            }
        }
    }
#endif

    i4_ret = c_wgl_set_visibility(pt_view->h_frames[TV_WIN_ID_SUB], WGL_SW_HIDE);
    if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility(pt_view->h_frames[TV_WIN_ID_MAIN], WGL_SW_HIDE);
    if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
    }
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_set_visibility(pt_view->h_frames_mib[TV_WIN_ID_SUB], WGL_SW_HIDE);
    if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility(pt_view->h_frames_mib[TV_WIN_ID_MAIN], WGL_SW_HIDE);
    if (i4_ret != WGLR_OK) {
            return NAVR_FAIL;
    }
#endif
    i4_ret = _pop_view_show_and_repaint_frames(
                    pt_view,
                    WGL_SW_HIDE,
                    FALSE,
                    TRUE,
                    b_tmp_hide == TRUE ? FALSE : TRUE
                    );
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_show(
                    VOID
                    )
{
    POP_VIEW_T* pt_view = &t_g_pop_view;
    INT32       i4_ret;
    
    i4_ret = c_wgl_set_visibility(pt_view->h_frames[TV_WIN_ID_SUB], WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility(pt_view->h_frames[TV_WIN_ID_MAIN], WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_set_visibility(pt_view->h_frames_mib[TV_WIN_ID_SUB], WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility(pt_view->h_frames_mib[TV_WIN_ID_MAIN], WGL_SW_NORMAL);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif
    return _pop_view_show_and_repaint_frames(
                    pt_view,
                    WGL_SW_RECURSIVE,
                    (pt_view->b_in_pop_resizing == TRUE) ? FALSE : TRUE,
                    TRUE,
                    FALSE
                    );
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_rcu_key_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static VOID _pop_view_rcu_key_handler(
                    POP_VIEW_T*                 pt_view,
                    UINT32                      ui4_key_code
                    )
{
    APP_TV_NET_SVC_STATUS t_svc_state;
    TV_WIN_ID_T e_focus_id;
    UINT32      ui4_orig_key_code = ui4_key_code;
    TV_MODE_T   e_tv_mode;
    INT32       i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return;
    }

    i4_ret = nav_get_focus_id(&e_focus_id);
    if (i4_ret != NAVR_OK) {
        return;
    }

    pop_custom_rcu_key_pre_handler(&ui4_key_code);

    switch(ui4_key_code) {
    case BTN_PIP_POP:
    case BTN_PIP:
    case BTN_POP:
        t_svc_state = a_tv_net_get_tv_svc_status();
        if(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
        {
            _pop_view_show_warning_msg (pt_view, TRUE);

            i4_ret = nav_unregister_key_monitor_nty_fct(NAV_COMP_ID_PIP_POP);
            if (i4_ret != NAVR_OK) {
                return;
            }

            return;
        }
        _pop_view_stop_show_timer(pt_view);
        switch(pop_get_next_tv_mode(e_tv_mode)) {
        case TV_MODE_TYPE_NORMAL:
            pop_enter_normal_mode(pt_view->pt_ctrl);
            break;
        case TV_MODE_TYPE_PIP:
            pop_enter_pip_mode(pt_view->pt_ctrl);
            break;
        case TV_MODE_TYPE_POP:
            pop_enter_pop_mode(pt_view->pt_ctrl);
            break;
        default:
            break;
        }
        break;
    case BTN_SWAP:
        nav_enable_key_traffic_auto_ctrl(50);
        pop_start_swap(pt_view->pt_ctrl, e_tv_mode);
        break;
#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
    case BTN_PIP_AUDIO:
        nav_enable_key_traffic_auto_ctrl(50);
        if (pt_view->b_is_msg_on == TRUE) {
            pop_start_audio_focus_change(pt_view->pt_ctrl);
        }
        _pop_view_show_audio_msg(pt_view);
        break;
#endif
    case CUSTOM_BTN_FOCUS:
    {
    	  BOOL b_disable = FALSE;

#ifndef APP_POP_ALWAYS_ENABLE_FOCUS_CHG
    	  pop_get_disable_audio_focus (&b_disable);
#endif
    	  if (!b_disable)
    	  {
	        nav_enable_key_traffic_auto_ctrl(50);
	        pop_start_focus_change(pt_view->pt_ctrl);
    	  }
        break;
    }
    case CUSTOM_BTN_PIP_PREV_SIZE:
        pt_view->b_is_size_or_pos_changing = TRUE;
        if (e_tv_mode == TV_MODE_TYPE_PIP) {
            nav_hide_component(NAV_COMP_ID_PIP_POP);
            pop_change_pip_sub_region(WIN_POS_DIR_CRNT, WIN_SIZE_DIR_PREV);
        }
        pt_view->b_is_size_or_pos_changing = FALSE;
        break;
    case BTN_PIP_SIZE:
    case CUSTOM_BTN_PIP_NEXT_SIZE:
        pt_view->b_is_size_or_pos_changing = TRUE;
        if (e_tv_mode == TV_MODE_TYPE_PIP) {
            nav_hide_component(NAV_COMP_ID_PIP_POP);
            pop_change_pip_sub_region(WIN_POS_DIR_CRNT, WIN_SIZE_DIR_NEXT);
        }
        pt_view->b_is_size_or_pos_changing = FALSE;
        break;
    case CUSTOM_BTN_PIP_PREV_POS:
        pt_view->b_is_size_or_pos_changing = TRUE;
        if (e_tv_mode == TV_MODE_TYPE_PIP) {
            nav_hide_component(NAV_COMP_ID_PIP_POP);
            pop_change_pip_sub_region(WIN_POS_DIR_PREV, WIN_SIZE_DIR_CRNT);
        }
        pt_view->b_is_size_or_pos_changing = FALSE;
        break;
    case BTN_PIP_POS:
    case CUSTOM_BTN_PIP_NEXT_POS:
        pt_view->b_is_size_or_pos_changing = TRUE;
        if (e_tv_mode == TV_MODE_TYPE_PIP) {
            nav_hide_component(NAV_COMP_ID_PIP_POP);
            pop_change_pip_sub_region(WIN_POS_DIR_NEXT, WIN_SIZE_DIR_CRNT);
        }
        pt_view->b_is_size_or_pos_changing = FALSE;
        break;
    case CUSTOM_BTN_POP_PREV_SIZE:
        pt_view->b_is_size_or_pos_changing = TRUE;
        if (e_tv_mode == TV_MODE_TYPE_POP) {
            nav_hide_component(NAV_COMP_ID_PIP_POP);
            pt_view->b_in_pop_resizing = TRUE;
            _pop_view_stop_show_timer(pt_view);
            i4_ret = pop_change_pop_regions(e_focus_id == TV_WIN_ID_MAIN ? WIN_POS_DIR_PREV : WIN_POS_DIR_NEXT);
            if (i4_ret != NAVR_OK) {
                pt_view->b_in_pop_resizing = FALSE;
                if (pt_view->b_frames_hidden == TRUE) {
                    _pop_view_show_and_repaint_frames(
                            pt_view,
                            WGL_SW_RECURSIVE,
                            TRUE,
                            TRUE,
                            FALSE
                            );
                }
                if (i4_ret == NAVR_NO_ACTION) {
                    nav_rcu_key_handler(ui4_orig_key_code);
                }
            }
        }
        pt_view->b_is_size_or_pos_changing = FALSE;
        break;
    case CUSTOM_BTN_POP_NEXT_SIZE:
        pt_view->b_is_size_or_pos_changing = TRUE;
        if (e_tv_mode == TV_MODE_TYPE_POP) {
            nav_hide_component(NAV_COMP_ID_PIP_POP);
            pt_view->b_in_pop_resizing = TRUE;
            _pop_view_stop_show_timer(pt_view);
            i4_ret = pop_change_pop_regions(e_focus_id == TV_WIN_ID_MAIN ? WIN_POS_DIR_NEXT : WIN_POS_DIR_PREV);
            if (i4_ret != NAVR_OK) {
                pt_view->b_in_pop_resizing = FALSE;
                if (pt_view->b_frames_hidden == TRUE) {
                    _pop_view_show_and_repaint_frames(
                            pt_view,
                            WGL_SW_RECURSIVE,
                            TRUE,
                            TRUE,
                            FALSE
                            );
                }
                if (i4_ret == NAVR_NO_ACTION) {
                    nav_rcu_key_handler(ui4_orig_key_code);
                }
            }
        }
        pt_view->b_is_size_or_pos_changing = FALSE;
        break;
    default:
        nav_rcu_key_handler(ui4_key_code);
        break;
    }
}
/*---------------------------------------------------------------------------
 * Name
 *      _pop_view_frame_nfy_fct(
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_frame_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    POP_VIEW_T* pt_view = &t_g_pop_view;
    INT32       i4_ret;

    switch(ui4_msg) {
    case WGL_MSG_KEY_DOWN:
        _pop_view_rcu_key_handler(pt_view, (UINT32)pv_param1);  /* key code */
        break;
    case WGL_MSG_KEY_UP:
        if (pt_view->b_in_pop_resizing == TRUE && pt_view->b_frames_hidden == TRUE) {
            _pop_view_reset_show_timer(pt_view);
        }
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
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_init(
                    POP_T*                      pt_this,
                    HANDLE_T                    h_canvas,
                    UINT32                      ui4_canvas_width,
                    UINT32                      ui4_canvas_height
                    )
{
    POP_VIEW_T* pt_view = &t_g_pop_view;
    INT32       i4_ret;
    GL_RECT_T   t_rect;

    c_memset(pt_view, 0, sizeof(POP_VIEW_T));

    if (IS_INSET_EMPTY(&t_g_pop_win_focus_bdr) && IS_INSET_EMPTY(&t_g_pop_win_blur_bdr))
    {
        b_g_pop_ignore_detect = TRUE;
    }

    pt_view->pt_ctrl = pt_this;
    pt_view->b_in_pop_resizing = FALSE;
    pt_view->e_crnt_rect_bg_types[TV_WIN_ID_MAIN] = RECT_BG_TYPE_UNKNOWN;
    pt_view->e_crnt_rect_bg_types[TV_WIN_ID_SUB]  = RECT_BG_TYPE_UNKNOWN;

#if 1
    i4_ret = c_timer_create(&pt_view->h_show_timer);
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }
#else
    if ((!(IS_INSET_EMPTY(&t_g_pop_win_focus_bdr) && IS_INSET_EMPTY(&t_g_pop_win_blur_bdr))) || POP_USE_ICON) {
        pt_view->h_show_timer = NULL_HANDLE;

        i4_ret = c_timer_create(&pt_view->h_show_timer);
        if (i4_ret != OSR_OK) {
            return NAVR_FAIL;
        }
    }
#endif

#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
    i4_ret = pop_view_init_msg_rc(&pt_view->t_msg_rc);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif

    SET_RECT_BY_SIZE(&t_rect, 0, 0, ((INT32)ui4_canvas_width), ((INT32)ui4_canvas_height));
    i4_ret = c_wgl_create_widget(
                    h_canvas,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _pop_view_frame_nfy_fct,
                    0,
                    (VOID*)NULL,
                    NULL,
                    &(pt_view->h_base_frame)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect, 0, 0, 0, 0);
    i4_ret = c_wgl_create_widget(
                    pt_view->h_base_frame,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_UNIFORM,
                    &t_rect,
                    NULL,
                    255,
                    (VOID*)WGL_STL_GL_NO_IMG_UI,
                    NULL,
                    &(pt_view->h_frames[TV_WIN_ID_MAIN])
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect, 0, 0, 0, 0);
    i4_ret = c_wgl_create_widget(
                    pt_view->h_base_frame,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_UNIFORM,
                    &t_rect,
                    NULL,
                    255,
                    (VOID*)WGL_STL_GL_NO_IMG_UI,
                    NULL,
                    &(pt_view->h_frames[TV_WIN_ID_SUB])
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    if ((!(IS_INSET_EMPTY(&t_g_pop_win_focus_bdr) && IS_INSET_EMPTY(&t_g_pop_win_blur_bdr))) || b_g_pop_ignore_detect) {
        c_wgl_ignore_visibility_detect(
                    t_g_pop_view.h_base_frame,
                    TRUE
                    );
    }

    SET_RECT_BY_SIZE(&t_rect, 0, 0, ((INT32)ui4_canvas_width), ((INT32)ui4_canvas_height));
    i4_ret = c_wgl_create_widget(
                    nav_get_context()->t_gui_res.h_cc_plane,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    _pop_view_frame_nfy_fct,
                    0,
                    (VOID*)NULL,
                    NULL,
                    &(pt_view->h_base_frame_mib)
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect, 0, 0, 0, 0);
    i4_ret = c_wgl_create_widget(
                    pt_view->h_base_frame_mib,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_UNIFORM,
                    &t_rect,
                    NULL,
                    255,
                    (VOID*)WGL_STL_GL_NO_IMG_UI,
                    NULL,
                    &(pt_view->h_frames_mib[TV_WIN_ID_MAIN])
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    SET_RECT_BY_SIZE(&t_rect, 0, 0, 0, 0);
    i4_ret = c_wgl_create_widget(
                    pt_view->h_base_frame_mib,
                    HT_WGL_WIDGET_FRAME,
                    WGL_CONTENT_FRAME_DEF,
                    WGL_BORDER_UNIFORM,
                    &t_rect,
                    NULL,
                    255,
                    (VOID*)WGL_STL_GL_NO_IMG_UI,
                    NULL,
                    &(pt_view->h_frames_mib[TV_WIN_ID_SUB])
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#endif

#if (POP_USE_ICON == 1)
    /* Create image tpl. */
    i4_ret = nav_img_create_pop_music_icon_tpl (&pt_view->h_img_focus_win);
    if(i4_ret != WGLR_OK){
        return NAVR_FAIL;
    }

    /* Create icon. */
    SET_RECT_BY_SIZE(&t_rect, 0, 0, POP_ICON_MUSIC_W, POP_ICON_MUSIC_H);
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frames[TV_WIN_ID_MAIN],
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_icon_main
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    /* Create icon. */
    i4_ret = c_wgl_create_widget(
                    pt_view->h_frames[TV_WIN_ID_SUB],
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_NULL,
                    &t_rect,
                    NULL,
                    DEFAULT_BK_ALPHA,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_view->h_icon_sub
                    );
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = nav_set_icon(
                    pt_view->h_icon_main,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_focus_win,
                    pt_view->h_img_focus_win,
                    pt_view->h_img_focus_win,
                    WGL_AS_CENTER_CENTER
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = nav_set_icon(
                    pt_view->h_icon_sub,
                    WGL_IMG_SET_STANDARD,
                    pt_view->h_img_focus_win,
                    pt_view->h_img_focus_win,
                    pt_view->h_img_focus_win,
                    WGL_AS_CENTER_CENTER
                    );
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility (pt_view->h_icon_main, WGL_SW_HIDE);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
    i4_ret = c_wgl_set_visibility (pt_view->h_icon_sub, WGL_SW_HIDE);
    if(i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif
    i4_ret = _pop_view_set_skin(pt_view);
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
    i4_ret = _pop_view_create_audio_msg(pt_view, h_canvas);
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif

#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
    i4_ret = _pop_view_create_nv_reason_msgs(pt_view, h_canvas);
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#endif
    i4_ret = _pop_view_create_warning_msg(h_canvas, &pt_view->t_warning_msg);
    if(i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_deinit(
                    VOID
                    )
{
    POP_VIEW_T* pt_view = &t_g_pop_view;

    c_wgl_destroy_widget(pt_view->h_frames[TV_WIN_ID_MAIN]);
    c_wgl_destroy_widget(pt_view->h_frames[TV_WIN_ID_SUB]);
    c_wgl_destroy_widget(pt_view->h_base_frame);
#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    c_wgl_destroy_widget(pt_view->h_frames_mib[TV_WIN_ID_MAIN]);
    c_wgl_destroy_widget(pt_view->h_frames_mib[TV_WIN_ID_SUB]);
    c_wgl_destroy_widget(pt_view->h_base_frame_mib);
#endif
#ifdef APP_TOGGLE_PIP_POP_AUDIO_ONLY
    pop_view_deinit_msg_rc(&pt_view->t_msg_rc);
    c_timer_delete(pt_view->h_hide_timer);
#endif
    if (pt_view->h_show_timer)
    {
        c_timer_delete (pt_view->h_show_timer);
        pt_view->h_show_timer = NULL_HANDLE;
    }
#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
    pop_view_deinit_reason_msg_rc(&pt_view->t_nv_reason_msg_rc);
    c_wgl_destroy_widget(pt_view->h_nv_reason_msgs[TV_WIN_ID_MAIN]);
    c_wgl_destroy_widget(pt_view->h_nv_reason_msgs[TV_WIN_ID_SUB]);
  #ifdef APP_CC_WITH_SOLE_OSD_PLANE
    c_wgl_destroy_widget(pt_view->h_nv_reason_msgs_mib[TV_WIN_ID_MAIN]);
    c_wgl_destroy_widget(pt_view->h_nv_reason_msgs_mib[TV_WIN_ID_SUB]);
  #endif
#endif
    c_wgl_destroy_widget(pt_view->t_warning_msg.h_warning_frm);
    c_wgl_destroy_widget(pt_view->t_warning_msg.h_txt_txtinfo);
    c_wgl_destroy_widget(pt_view->t_warning_msg.h_ok_btn);  
    
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static BOOL _pop_view_is_key_handler(
                    UINT32                      ui4_key_code
                    )
{
    TV_MODE_T e_tv_mode;
    INT32     i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return FALSE;
    }

    pop_custom_rcu_key_pre_handler(&ui4_key_code);

    switch(ui4_key_code) {
    case BTN_PIP_POP:
    case BTN_PIP:
    case BTN_POP:
        if (e_tv_mode == TV_MODE_TYPE_NORMAL) {
            ISL_REC_T t_main_isl_rec = {0};
            ISL_REC_T t_sub_isl_rec  = {0};

            i4_ret = pop_get_isl_recs(&t_main_isl_rec, &t_sub_isl_rec);
            if (i4_ret != NAVR_OK) {
                return FALSE;
            }
        }
        return TRUE;
    case BTN_SWAP:
    case BTN_PIP_AUDIO:
    case BTN_PIP_SIZE:
    case BTN_PIP_POS:
    case CUSTOM_BTN_FOCUS:
    case CUSTOM_BTN_PIP_PREV_SIZE:
    case CUSTOM_BTN_PIP_NEXT_SIZE:
    case CUSTOM_BTN_PIP_PREV_POS:
    case CUSTOM_BTN_PIP_NEXT_POS:
    case CUSTOM_BTN_POP_PREV_SIZE:
    case CUSTOM_BTN_POP_NEXT_SIZE:
        if (e_tv_mode != TV_MODE_TYPE_NORMAL) {
            return TRUE;
        }
        break;
    default:
        break;
    }
    return FALSE;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_activate(
                    TV_WIN_ID_T                 e_focus_id,
                    TV_WIN_ID_T                 e_blur_id,
                    UINT32                      ui4_key_code
                    )
{
    POP_VIEW_T* pt_view = &t_g_pop_view;
    INT32       i4_ret;


    i4_ret = c_wgl_set_focus(pt_view->h_base_frame, WGL_NO_AUTO_REPAINT);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_insert(
                    pt_view->h_base_frame,
                    NULL_HANDLE,
                    WGL_INSERT_BOTTOMMOST,
                    WGL_NO_AUTO_REPAINT
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_insert(
                    pt_view->h_frames[TV_WIN_ID_SUB],
                    pt_view->h_frames[TV_WIN_ID_MAIN],
                    WGL_INSERT_BEFORE,
                    WGL_NO_AUTO_REPAINT
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_insert(
                    pt_view->h_base_frame_mib,
                    NULL_HANDLE,
                    WGL_INSERT_BOTTOMMOST,
                    WGL_NO_AUTO_REPAINT
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_insert(
                    pt_view->h_frames_mib[TV_WIN_ID_SUB],
                    pt_view->h_frames_mib[TV_WIN_ID_MAIN],
                    WGL_INSERT_BEFORE,
                    WGL_NO_AUTO_REPAINT
                    );
    if(WGLR_OK != i4_ret) {
        return NAVR_FAIL;
    }
#endif
    /*i4_ret = _pop_view_set_focus(e_focus_id, e_blur_id, FALSE);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }*/

    _pop_view_rcu_key_handler(pt_view, ui4_key_code);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_set_alpha
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_set_alpha(
                    UINT8                       ui1_alpha
                    )
{
    POP_VIEW_T* pt_view = &t_g_pop_view;
    INT32       i4_ret;

    i4_ret = c_wgl_set_alpha(pt_view->h_frames[TV_WIN_ID_MAIN], ui1_alpha);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_alpha(pt_view->h_frames[TV_WIN_ID_SUB], ui1_alpha);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

#ifdef APP_CC_WITH_SOLE_OSD_PLANE
    i4_ret = c_wgl_set_alpha(pt_view->h_frames_mib[TV_WIN_ID_MAIN], ui1_alpha);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_wgl_set_alpha(pt_view->h_frames_mib[TV_WIN_ID_SUB], ui1_alpha);
    if (i4_ret != WGLR_OK) {
        return NAVR_FAIL;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_view_update_no_video_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_view_update_no_video_msg(
                    TV_MODE_T                   e_tv_mode
                    )
{
#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
    POP_VIEW_T*  pt_view = &t_g_pop_view;
    TV_WIN_ID_T  e_tv_win_id;
   
  #ifndef APP_ONLY_DISP_NO_VIDEO_REASON_FOR_SUB
    e_tv_win_id = TV_WIN_ID_MAIN;
    if (pt_view->e_rect_bg_cmd[e_tv_win_id] != POP_RECT_BG_CMD_HIDE) {
        _pop_view_show_no_video_message(
                    pt_view, 
                    e_tv_win_id, 
                    e_tv_mode, 
                    pt_view->e_rect_bg_cmd[e_tv_win_id], 
                    FALSE, 
                    TRUE
                    );
    }
  #endif
    e_tv_win_id = TV_WIN_ID_SUB;
    if (pt_view->e_rect_bg_cmd[e_tv_win_id] != POP_RECT_BG_CMD_HIDE) {
        _pop_view_show_no_video_message(
                    pt_view, 
                    e_tv_win_id, 
                    e_tv_mode, 
                    pt_view->e_rect_bg_cmd[e_tv_win_id], 
                    FALSE, 
                    TRUE
                    );
    }
#endif 

    return NAVR_OK;   
}                    
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
INT32 pop_view_register_default_hdlr(
                    POP_VIEW_HDLR_T*            pt_view_hdlr
                    )
{
    if (pt_view_hdlr == NULL) {
        return NAVR_FAIL;
    }

    pt_view_hdlr->pf_init                = _pop_view_init;
    pt_view_hdlr->pf_deinit              = _pop_view_deinit;
    pt_view_hdlr->pf_hide                = _pop_view_hide;
    pt_view_hdlr->pf_show                = _pop_view_show;
    pt_view_hdlr->pf_is_key_handler      = _pop_view_is_key_handler;
    pt_view_hdlr->pf_activate            = _pop_view_activate;
    pt_view_hdlr->pf_set_alpha           = _pop_view_set_alpha;
    pt_view_hdlr->pf_update_win_rect     = _pop_view_update_win_rect;
    pt_view_hdlr->pf_set_focus           = _pop_view_set_focus;
    pt_view_hdlr->pf_show_win_rect_bg    = _pop_view_show_win_rect_bg;
    pt_view_hdlr->pf_show_frames         = _pop_view_show_frames;
    pt_view_hdlr->pf_hide_msg            = _pop_view_hide_msg;
    pt_view_hdlr->pf_update_no_video_msg = _pop_view_update_no_video_msg;
    return NAVR_OK;
}
#endif /*APP_PIP_POP_CTRL*/
#endif /*APP_537X_SUPPORT*/
