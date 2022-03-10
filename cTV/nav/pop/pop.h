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
 * $RCSfile: pop.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/54 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e2d2b1a79d31b7290e162f409db02988 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _POP_H_
#define _POP_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#include "nav/nav_common.h"
#include "app_util/a_tv.h"
#include "u_irrc_btn_def.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define CUSTOM_BTN_FOCUS                    ((UINT32)(KEY_GROUP_MAX | 0x0000f070))
#define CUSTOM_BTN_PIP_PREV_SIZE            ((UINT32)(KEY_GROUP_MAX | 0x0000f071))
#define CUSTOM_BTN_PIP_NEXT_SIZE            ((UINT32)(KEY_GROUP_MAX | 0x0000f072))
#define CUSTOM_BTN_PIP_PREV_POS             ((UINT32)(KEY_GROUP_MAX | 0x0000f073))
#define CUSTOM_BTN_PIP_NEXT_POS             ((UINT32)(KEY_GROUP_MAX | 0x0000f074))
#define CUSTOM_BTN_POP_PREV_SIZE            ((UINT32)(KEY_GROUP_MAX | 0x0000f075))
#define CUSTOM_BTN_POP_NEXT_SIZE            ((UINT32)(KEY_GROUP_MAX | 0x0000f076))
#define CUSTOM_BTN_NULL                     ((UINT32)(KEY_GROUP_MAX | 0x0000ffff))

typedef enum _POP_RECT_BG_CMD_T
{
    POP_RECT_BG_CMD_SHOW,
    POP_RECT_BG_CMD_HIDE,
    POP_RECT_BG_CMD_BLACK  
} POP_RECT_BG_CMD_T;

struct _POP_T;
/* view handler */
typedef INT32 (*pop_view_init_fct)(
                    struct _POP_T*              pt_this,
                    HANDLE_T                    h_canvas,
                    UINT32                      ui4_canvas_width,
                    UINT32                      ui4_canvas_height
                    );
typedef INT32 (*pop_view_deinit_fct)(
                    VOID
                    );
typedef INT32 (*pop_view_hide_fct)(
                    BOOL                        b_tmp_hide
                    );
typedef INT32 (*pop_view_show_fct)(
                    VOID
                    );
typedef BOOL (*pop_view_is_key_handler_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*pop_view_activate_fct)(
                    TV_WIN_ID_T                 e_focus_id,
                    TV_WIN_ID_T                 e_blur_id,
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*pop_view_set_alpha_fct)(
                    UINT8                       ui1_alpha
                    );
typedef INT32 (*pop_view_update_win_rect_fct)(
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    GL_RECT_T*                  pt_win_rect,
                    BOOL                        b_repaint
                    );
typedef INT32 (*pop_view_set_focus_fct)(
                    TV_WIN_ID_T                 e_focus_id,
                    TV_WIN_ID_T                 e_blur_id,
                    BOOL                        b_repaint
                    );
typedef INT32 (*pop_view_show_win_rect_bg_fct)(
                    TV_WIN_ID_T                 e_tv_win_id,
                    TV_MODE_T                   e_tv_mode,
                    POP_RECT_BG_CMD_T           e_cmd,
                    BOOL                        b_repaint
                    );
typedef INT32 (*pop_view_show_frames)(
                    BOOL                        b_show
                    );
typedef INT32 (*pop_view_hide_msg_fct)(
                    VOID
                    );
typedef INT32 (*pop_view_update_no_video_fct)(
                    TV_MODE_T                   e_tv_mode
                    );
typedef struct _POP_VIEW_HDLR_T
{
    pop_view_init_fct                   pf_init;
    pop_view_deinit_fct                 pf_deinit;
    pop_view_hide_fct                   pf_hide;
    pop_view_show_fct                   pf_show;
    pop_view_is_key_handler_fct         pf_is_key_handler;
    pop_view_activate_fct               pf_activate;
    pop_view_set_alpha_fct              pf_set_alpha;
    pop_view_update_win_rect_fct        pf_update_win_rect;
    pop_view_set_focus_fct              pf_set_focus;
    pop_view_show_win_rect_bg_fct       pf_show_win_rect_bg;
    pop_view_show_frames                pf_show_frames;
    pop_view_hide_msg_fct               pf_hide_msg;
    pop_view_update_no_video_fct        pf_update_no_video_msg;
} POP_VIEW_HDLR_T;

typedef struct _POP_AUDIO_T
{
    SCDB_REC_TYPE_T           e_type;
    STREAM_COMP_ID_T          t_comp_id;
    SCDB_AUDIO_MPEG_T         t_mpeg;
} POP_AUDIO_T;

typedef enum _POP_VIDEO_STATUS_T
{
    POP_VIDEO_STATUS_UNKNOWN = 0,
    POP_VIDEO_STATUS_NOT_VISIBLE,
    POP_VIDEO_STATUS_VISIBLE
} POP_VIDEO_STATUS_T;

typedef struct _POP_VIDEO_T
{
    POP_VIDEO_STATUS_T        e_status; 
} POP_VIDEO_T;

typedef struct _POP_T
{
    UINT8                     ui1_swap_stopping_tv_win_bits;
    UINT8                     ui1_swap_selecting_tv_win_bits;
    UINT32                    ui4_canvas_width;
    UINT32                    ui4_canvas_height;
    UINT16                    ui2_nav_cfg_nfy;
    UINT16                    ui2_misc_cfg_nfy;
    UINT16                    ui2_pip_pop_cfg_nfy;
    UINT16                    ui2_gui_lang_cfg_nfy;
    HANDLE_T                  h_main_svctx;
    HANDLE_T                  h_sub_svctx;
    
    HANDLE_T                  h_hide_timer;
    HANDLE_T                  h_swap_timer;
    BOOL                      b_frames_shown;
    UINT32                    ui4_hide_timeout;
    TV_WIN_ID_T               e_audio_focus_id; /* only change audio */
    BOOL                      b_audio_focus_changing;
    BOOL                      b_under_ex_ctrl;  /* for external ctrl: EAS */
    TV_MODE_T                 e_last_tv_mode;
    TV_MODE_T                 e_tv_mode_in_changing;
    HANDLE_T                  h_lock;
    BOOL                      b_might_single_rf_scan[TV_WIN_ID_LAST_VALID_ENTRY];

    POP_AUDIO_T               t_audios[TV_WIN_ID_LAST_VALID_ENTRY];
    POP_VIDEO_T               t_videos[TV_WIN_ID_LAST_VALID_ENTRY];
    UINT8                     ui1_src_ids[TV_WIN_ID_LAST_VALID_ENTRY];
    BOOL                      b_using_pip_audio_strm_filter;
    POP_VIEW_HDLR_T           t_view_hdlr;
    BOOL                      b_resel_audio;    /**< Determine whether to re-select audio. */
    BOOL                      b_is_power_on_received; /**< Determine whether power on event is received from NAV common part. */
    BOOL				  	          b_disable_audio_focus_chg; /**< Determine whether to disable audio focus change or not. */
} POP_T;

typedef enum {
    WIN_POS_DIR_CRNT,
    WIN_POS_DIR_NEXT,
    WIN_POS_DIR_PREV
} WIN_POS_DIR_T;

typedef enum {
    WIN_SIZE_DIR_CRNT,
    WIN_SIZE_DIR_NEXT,
    WIN_SIZE_DIR_PREV
} WIN_SIZE_DIR_T;
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 pop_view_register_default_hdlr(
                    POP_VIEW_HDLR_T*        pt_view_hdlr
                    );
extern INT32 pop_change_pip_sub_region(
                    WIN_POS_DIR_T           e_pos_dir,
                    WIN_SIZE_DIR_T          e_size_dir
                    );
extern INT32 pop_change_pop_regions(
                    WIN_POS_DIR_T           e_pos_dir
                    );
extern INT32 pop_enter_pip_mode(
                    POP_T*                  pt_this
                    );
extern INT32 pop_enter_pop_mode(
                    POP_T*                  pt_this
                    );
extern INT32 pop_enter_normal_mode(
                    POP_T*                  pt_this
                    );
extern INT32 pop_start_swap(
                    POP_T*                  pt_this,
                    TV_MODE_T               e_tv_mode
                    );
extern INT32 pop_start_focus_change(
                    POP_T*                  pt_this
                    );
extern INT32 pop_start_audio_focus_change(
                    POP_T*                  pt_this
                    );
extern INT32 pop_get_audio_focus_id(
                    POP_T*                  pt_this,
                    TV_WIN_ID_T*            pe_focus_id
                    );
extern INT32 pop_get_isl_recs(
                    ISL_REC_T*                  pt_main_rec,
                    ISL_REC_T*                  pt_sub_rec
                    );
extern INT32 pop_set_disable_audio_focus (BOOL b_enable);
extern INT32 pop_get_disable_audio_focus (BOOL* pb_enable);

/* supported by custom's part */
extern INT32 pop_get_pop_region_infos(
                    WIN_POS_DIR_T           e_pos_dir,
                    VSH_REGION_INFO_T*      pt_main_region,
                    VSH_REGION_INFO_T*      pt_sub_region
                    );
extern INT32 pop_get_pip_main_region_info(
                    VSH_REGION_INFO_T*      pt_region_info
                    );
extern INT32 pop_get_pip_sub_region_info(
                    WIN_POS_DIR_T           e_pos_dir,
                    WIN_SIZE_DIR_T          e_size_dir,
                    VSH_REGION_INFO_T*      pt_region_info
                    );
extern VOID pop_custom_rcu_key_pre_handler(
                    UINT32*                 pui4_key_code
                    );
extern TV_MODE_T pop_get_next_tv_mode(
                    TV_MODE_T               e_crnt_mode
                    );
extern INT32 pop_get_pip_sub_region_info_by_id(
                    TV_PIP_SUB_POSITION_T   e_pos_id,
                    TV_PIP_SUB_SIZE_T       e_size_id,
                    VSH_REGION_INFO_T*      pt_region_info
                    );
/* supported by custom's part */
#ifdef CLI_SUPPORT
/*----------------------------------------------------------------------------
 * Name:    nav_pop_cli_register_cmd_tbl
 * Description:
 *      The API is used to register POP table. The API must be invoked
 *      in a_nav_pop_register().
 * Input arguments:
 *      NONE
 * Output arguments:
 *      NONE
 * Returns:
 *      NONE
 *----------------------------------------------------------------------------*/
extern VOID nav_pop_cli_register_cmd_tbl(
                    VOID
                    );
/*-----------------------------------------------------------------------------
 * Name
 *      pop_print_self
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
extern VOID pop_print_self(
                    VOID
                    );
#else
#define nav_pop_cli_register_cmd_tbl()
#define pop_print_self()
#endif
#endif /* _POP_H_ */
