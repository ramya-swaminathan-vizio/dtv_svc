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
#ifndef MMP_COMMON_UI_TOOLBAR_H
#define MMP_COMMON_UI_TOOLBAR_H

#include "res/mmp/gen/mmp_pp_tb_layout.h"
#include "res/mmp/gen/mmp_vp_tb_layout.h"
#include "res/mmp/gen/mmp_ap_tb_layout.h"
#include "res/mmp/gen/mmp_tp_tb_layout.h"
#include "mmp/app/mmp_main.h"
#include "app_util/a_cfg.h"
#include "mmp_common_ui.h"
#include "mmp/mmp_tools.h"

typedef struct {} *MMP_TOOLBAR_INST_PTR_T;

typedef struct _MMP_TB_DURATION_TYPE_T
{
    UINT8 ui1_hour;
    UINT8 ui1_min;
    UINT8 ui1_sec;
} MMP_TB_DURATION_TYPE_T;

typedef struct _MMP_TB_TIME_TYPE_T
{
    MMP_TB_DURATION_TYPE_T t_time_cur;
    MMP_TB_DURATION_TYPE_T t_time_total;
} MMP_TB_TIME_TYPE_T;

typedef enum
{
    MMP_TB_POS_TYPE_TIME = 0,
    MMP_TB_POS_TYPE_BYTE
} MMP_TB_POS_TYPE_T;

typedef struct
{
    MMP_TB_POS_TYPE_T       e_pos_type;

    union
    {
        UINT64              ui8_byte_dur;
        UINT32              ui4_time_dur;
    } u;

    union
    {
        UINT64              ui8_byte_pos;
        UINT32              ui4_time_pos;
    } v;

} MMP_TB_POS_INFO_T;

typedef struct _MMP_TB_SUB_TYPE_T
{
    UINT16 ui2_sub_total;
    UINT16 ui2_sub_index;
} MMP_TB_SUB_TYPE_T;

typedef struct _MMP_TB_MTS_TYPE_T
{
    UINT16 ui2_mts_total;
    UINT16 ui2_mts_index;
} MMP_TB_MTS_TYPE_T;

typedef enum
{
    MMP_TB_NON_REPAINT = 0,
    MMP_TB_SYNC_REPAINT,
    MMP_TB_ASYNC_REPAINT,
    MMP_TB_REPAINT_TOTAL_COUNT
} MMP_TB_REPAINT_TYPE_T;

typedef enum
{
    MMP_TB_PHOTO_PLAYER = 0,
    MMP_TB_VIDEO_PLAYER,
    MMP_TB_AUDIO_PLAYER,
    MMP_TB_TEXT_PLAYER,
    MMP_TB_PLAYER_TOTAL_COUNT
} MMP_TB_PLAYER_TYPE_T;

typedef enum _MMP_TB_CMD_ID_T
{
    MMP_PP_TB_CMD_SET_PLAY_STATUS = 0x1100,
    MMP_PP_TB_CMD_SET_REPEAT_AB,
    MMP_PP_TB_CMD_SET_ZOOM,
    MMP_PP_TB_CMD_SET_REPEAT,
    MMP_PP_TB_CMD_SET_EFFECT,
    MMP_PP_TB_CMD_SET_SHUFFLE,
    MMP_PP_TB_CMD_SET_DURATION,
    MMP_PP_TB_CMD_SET_FILEIDX,
    MMP_PP_TB_CMD_SET_FILENAME,
    MMP_PP_TB_CMD_SET_TOPBAR,
    MMP_PP_TB_CMD_SET_CLEAR,
    MMP_PP_TB_CMD_TOTAL_COUNT,

    MMP_VP_TB_CMD_SET_PLAY_STATUS = 0x1200,
    MMP_VP_TB_CMD_SET_FF,
    MMP_VP_TB_CMD_SET_FR,
    MMP_VP_TB_CMD_SET_SLOW_PALY,
    MMP_VP_TB_CMD_SET_REPEAT_AB,
    MMP_VP_TB_CMD_SET_ZOOM,
    MMP_VP_TB_CMD_SET_MTS,
    MMP_VP_TB_CMD_SET_REPEAT,
    MMP_VP_TB_CMD_SET_SUBTITLE,
    MMP_VP_TB_CMD_SET_TIME,
    MMP_VP_TB_CMD_SET_FILEIDX,
    MMP_VP_TB_CMD_SET_VOL_MUTE,
    MMP_VP_TB_CMD_SET_VOL_PG,
    MMP_VP_TB_CMD_SET_VOL_BAR_VISBI,
    MMP_VP_TB_CMD_SET_FILENAME,
    MMP_VP_TB_CMD_SET_TOPBAR,
    MMP_VP_TB_CMD_SET_CLEAR,
    MMP_VP_TB_CMD_ACTIVE_TIME_BOX,
    MMP_VP_TB_CMD_INACTIVE_TIME_BOX,
    MMP_VP_TB_CMD_TOTAL_COUNT,

    MMP_AP_TB_CMD_SET_PLAY_STATUS = 0x1300,
    MMP_AP_TB_CMD_SET_FF,
    MMP_AP_TB_CMD_SET_FR,
    MMP_AP_TB_CMD_SET_REPEAT_AB,
    MMP_AP_TB_CMD_SET_REPEAT,
    MMP_AP_TB_CMD_SET_SHUFFLE,
    MMP_AP_TB_CMD_SET_TIME,
    MMP_AP_TB_CMD_SET_FILEIDX,
    MMP_AP_TB_CMD_SET_VOL_MUTE,
    MMP_AP_TB_CMD_SET_VOL_PG,
    MMP_AP_TB_CMD_SET_VOL_BAR_VISBI,
    MMP_AP_TB_CMD_SET_FILENAME,
    MMP_AP_TB_CMD_SET_TOPBAR,
    MMP_AP_TB_CMD_SET_CLEAR,
    MMP_AP_TB_CMD_TOTAL_COUNT,

    MMP_TP_TB_CMD_SET_PLAY_STATUS = 0x1400,
    MMP_TP_TB_CMD_SET_REPEAT,
    MMP_TP_TB_CMD_SET_SHUFFLE,
    MMP_TP_TB_CMD_SET_LANG,
    MMP_TP_TB_CMD_SET_PAGEIDX,
    MMP_TP_TB_CMD_SET_FILEIDX,
    MMP_TP_TB_CMD_SET_FILENAME,
    MMP_TP_TB_CMD_SET_TOPBAR,
    MMP_TP_TB_CMD_SET_CLEAR,
    MMP_TP_TB_CMD_TOTAL_COUNT
} MMP_TB_CMD_ID_T;

enum
{
    MMP_PP_TB_STATUS_PLAY = 0x2100,
    MMP_PP_TB_STATUS_PAUSE,
    MMP_PP_TB_STATUS_NONE,
    MMP_PP_TB_STATUS_REPEAT_AB_NONE,
    MMP_PP_TB_STATUS_REPEAT_AB_A,
    MMP_PP_TB_STATUS_REPEAT_AB_AB,
    MMP_PP_TB_STATUS_REPEAT_AB,
    MMP_PP_TB_STATUS_ZOOM_1X,
    MMP_PP_TB_STATUS_ZOOM_2X,
    MMP_PP_TB_STATUS_ZOOM_4X,
    MMP_PP_TB_STATUS_REPEAT_NONE,
    MMP_PP_TB_STATUS_REPEAT_ONE,
    MMP_PP_TB_STATUS_REPEAT_ALL,
    MMP_PP_TB_STATUS_EFFECT_NONE,
    MMP_PP_TB_STATUS_EFFECT_DISSOLVE,
    MMP_PP_TB_STATUS_EFFECT_WP_R,
    MMP_PP_TB_STATUS_EFFECT_WP_L,
    MMP_PP_TB_STATUS_EFFECT_WP_U,
    MMP_PP_TB_STATUS_EFFECT_WP_D,
    MMP_PP_TB_STATUS_EFFECT_BX_IN,
    MMP_PP_TB_STATUS_EFFECT_BX_OUT,
    MMP_PP_TB_STATUS_EFFECT_RANDOM,
    MMP_PP_TB_STATUS_SHUFFLE_MODE_SEQUENTIAL,
    MMP_PP_TB_STATUS_SHUFFLE_MODE_SHUFFLE,
    MMP_PP_TB_STATUS_DURATION_SHORT,
    MMP_PP_TB_STATUS_DURATION_MEDIUM,
    MMP_PP_TB_STATUS_DURATION_LONG,
    MMP_PP_TB_STATUS_TOPBAR_HIDE,
    MMP_PP_TB_STATUS_TOPBAR_SHOW,
    MMP_PP_TB_STATUS_TOTAL_COUNT,

    MMP_VP_TB_STATUS_PLAY = 0x2200,
    MMP_VP_TB_STATUS_PAUSE,
    MMP_VP_TB_STATUS_STOP,
    MMP_VP_TB_STATUS_DEFAULT,
    MMP_VP_TB_STATUS_REPEAT_AB_NONE,
    MMP_VP_TB_STATUS_REPEAT_AB_A,
    MMP_VP_TB_STATUS_REPEAT_AB_AB,
    MMP_VP_TB_STATUS_REPEAT_AB,
    MMP_VP_TB_STATUS_REPEAT_NONE,
    MMP_VP_TB_STATUS_REPEAT_ONE,
    MMP_VP_TB_STATUS_REPEAT_ALL,
    MMP_VP_TB_STATUS_VOL_NORMAL,
    MMP_VP_TB_STATUS_VOL_MUTE,
    MMP_VP_TB_STATUS_TOPBAR_HIDE,
    MMP_VP_TB_STATUS_TOPBAR_SHOW,
    MMP_VP_TB_STATUS_TOTAL_COUNT,

    MMP_AP_TB_STATUS_PLAY = 0x2300,
    MMP_AP_TB_STATUS_PAUSE,
    MMP_AP_TB_STATUS_STOP,
    MMP_AP_TB_STATUS_FAST_FOR,
    MMP_AP_TB_STATUS_FAST_REW,
    MMP_AP_TB_STATUS_DEFAULT,
    MMP_AP_TB_STATUS_REPEAT_AB_NONE,
    MMP_AP_TB_STATUS_REPEAT_AB_A,
    MMP_AP_TB_STATUS_REPEAT_AB_AB,
    MMP_AP_TB_STATUS_REPEAT_AB,
    MMP_AP_TB_STATUS_REPEAT_NONE,
    MMP_AP_TB_STATUS_REPEAT_ONE,
    MMP_AP_TB_STATUS_REPEAT_ALL,
    MMP_AP_TB_STATUS_SHUFFLE_MODE_SEQUENTIAL,
    MMP_AP_TB_STATUS_SHUFFLE_MODE_SHUFFLE,
    MMP_AP_TB_STATUS_VOL_NORMAL,
    MMP_AP_TB_STATUS_VOL_MUTE,
    MMP_AP_TB_STATUS_TOPBAR_HIDE,
    MMP_AP_TB_STATUS_TOPBAR_SHOW,
    MMP_AP_TB_STATUS_TOTAL_COUNT,

    MMP_TP_TB_STATUS_PLAY = 0x2400,
    MMP_TP_TB_STATUS_PAUSE,
    MMP_TP_TB_STATUS_STOP,
    MMP_TP_TB_STATUS_REPEAT_NONE,
    MMP_TP_TB_STATUS_REPEAT_ONE,
    MMP_TP_TB_STATUS_REPEAT_ALL,
    MMP_TP_TB_STATUS_SHUFFLE_MODE_SEQUENTIAL,
    MMP_TP_TB_STATUS_SHUFFLE_MODE_SHUFFLE,
    MMP_TP_TB_STATUS_TOPBAR_HIDE,
    MMP_TP_TB_STATUS_TOPBAR_SHOW,
    MMP_TP_TB_STATUS_TOTAL_COUNT
};

typedef enum
{
    MMP_VP_TB_TIME_BOX_STATUS_SELELCT = 0,
    MMP_VP_TB_TIME_BOX_STATUS_EXIT,

    MMP_VP_TB_TIME_BOX_STATUS_COUNT,

} MMP_VP_TB_TIME_BOX_STATUS_T;

typedef INT32 (*mmp_tb_time_box_cb)(MMP_VP_TB_TIME_BOX_STATUS_T e_status_id, UINT32 ui4_time_set);

extern INT32 mmp_common_ui_toolbar_time_box_reg(const mmp_tb_time_box_cb  pt_time_box_cb,
                                                    VOID* pv_tag);

extern INT32 mmp_common_ui_toolbar_init(MMP_TB_PLAYER_TYPE_T e_player_type,
                                        HANDLE_T h_parent,
                                        VOID     **ppv_tb_inst);
extern INT32 mmp_common_ui_toolbar_deinit(VOID *pv_tb_inst);
extern INT32 mmp_common_ui_toolbar_view_active(VOID *pv_tb_inst,
                                        MMP_TB_REPAINT_TYPE_T e_repaint_type);
extern INT32 mmp_common_ui_toolbar_view_inactive(VOID *pv_tb_inst,
                                        MMP_TB_REPAINT_TYPE_T   e_repaint_type);
extern INT32 mmp_common_ui_toolbar_cmd_do(VOID *pv_tb_inst,
                                        MMP_TB_CMD_ID_T   e_cmd_id,
                                        VOID*             pv_cmd_param,
                                        MMP_TB_REPAINT_TYPE_T b_repaint);

extern INT32 mmp_common_ui_toolbar_get_main_frm(HANDLE_T *ph_handle);
#endif
