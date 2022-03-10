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
 * $RCSfile: audio_info.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Screen Mode controller is a signaltone
 *
 *---------------------------------------------------------------------------*/
#ifndef _AUDIO_INFO_H_
#define _AUDIO_INFO_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_gl.h"

#include "app_util/a_common.h"
#include "nav/navigator.h"
#include "res/nav/nav_variant.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
typedef struct __AUDIO_INFO_GROUP_DATA_T
{
    HANDLE_T                h_mts;            /*handle for mts operation*/
    BOOL                    b_is_digital;
} _AUDIO_INFO_GROUP_DATA_T;

typedef struct __NAV_AUD_STRM_INFO_T
{
  SCDB_REC_TYPE_T           e_type;
  STREAM_COMP_ID_T          t_comp_id;
  SCDB_AUDIO_MPEG_T         t_mpeg;
} _NAV_AUD_STRM_INFO_T;

typedef struct _NAV_AUD_COMBINED_STEREO_INFO_T {
    SCDB_REC_T*    pt_scdb_rec;
    BOOL           b_dual_1_valid;
    BOOL           b_dual_2_valid;
    CHAR           s_dual_1_lang[ISO_639_LANG_LEN];
    CHAR           s_dual_2_lang[ISO_639_LANG_LEN];
} NAV_AUD_COMBINED_STEREO_INFO_T;

typedef struct _AUDIO_INFO_T
{
    BOOL                      b_is_on;
    HANDLE_T                  h_hide_timer;

    _AUDIO_INFO_GROUP_DATA_T   at_grp[TV_WIN_ID_LAST_VALID_ENTRY];
    TV_WIN_ID_T               e_focus;
    SCC_AUD_MTS_T             e_capacity_backup;
    SCC_AUD_MTS_T             e_crnt_mts;
    UINT16                    ui2_mts_cfg_nfy;          /*id of config field to receive mts setting change*/
    UINT16                    ui2_selectable_audio_count;
    BOOL                      b_is_mts_changed;
    BOOL                      b_is_same_svc_change;
    BOOL                      b_been_reset;
    BOOL                      b_is_audio_info_ready;
    BOOL                      b_reset_mts_in_scan;
    BOOL                      b_from_cfg;

    HANDLE_T                  h_mtx_sema;

    /* For audio pause/resume function */
    _NAV_AUD_STRM_INFO_T      t_paused_aud;
    BOOL                      b_aud_paused;
	BOOL                      b_aud_ch_alg_mts;
} AUDIO_INFO_T;

typedef struct _AUDIO_INFO_VIEW_T
{
    AUDIO_INFO_T*           pt_ctrl;
    HANDLE_T                h_frame;
    HANDLE_T                h_msg;
    HANDLE_T                h_img_bk;
} AUDIO_INFO_VIEW_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
/* Ctrl */
extern INT32 audio_info_get_combined_stereo_info(
                    NAV_AUD_COMBINED_STEREO_INFO_T*  pt_aud_lang_info
                    );

/* view */
extern INT32 audio_info_view_init(
                    AUDIO_INFO_T*               pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );

extern INT32 audio_info_view_deinit(VOID);

extern INT32 audio_info_view_show(
                    VOID
                    );
extern INT32 audio_info_view_hide(
                    VOID
                    );
extern INT32 audio_info_view_draw_digital(
                    ASH_AUDIO_INFO_T*           pt_audio_info,
                    SCDB_REC_T*                 pt_scdb_rec,
                    UINT16                      ui2_total_amount,
                    UINT16                      ui2_order,
                    UINT32                      ui4_scrambled_strm
                    );
extern INT32 audio_info_view_draw_analog(
                    SCC_AUD_MTS_T               e_mts
                    );
extern INT32 audio_info_view_draw_no_feature(
                    VOID
                    );
extern INT32 audio_info_view_clean_msg(
                    VOID
                    );
extern INT32 audio_info_key_handler(
                    AUDIO_INFO_T*               pt_this,
                    TV_WIN_ID_T                 e_grp,
                    UINT32                      ui4_key_code
                    );

extern INT32 a_audio_info_update_ATV_mts(SCC_AUD_MTS_T e_new_mts);


#endif /* _AUDIO_INFO_H_ */
