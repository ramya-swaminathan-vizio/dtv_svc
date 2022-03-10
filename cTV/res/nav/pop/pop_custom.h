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
 * $RCSfile: pop_custom.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/7 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 27bad65f0954f3bdb87f20fd6c804eab $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _POP_CUSTOM_H_
#define _POP_CUSTOM_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_sm_video_hdlr.h"
#include "u_common.h"
#include "u_gl.h"
#include "u_wgl_common.h"

#include "res/nav/nav_view.h"
#include "res/nav/nav_colors.h"
#include "app_util/a_tv.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define APP_NAV_LISTEN_PIP_SUB_POS_SIZE_CFG_CHANGE

#define X_POS_INFO_LEFT_EDGE   ((UINT8)0x01)
#define X_POS_INFO_RIGHT_EDGE  ((UINT8)0x02)
#define X_POS_INFO_CENTER      ((UINT8)0x03)
#define X_POS_INFO_MASK        ((UINT8)0x0F)

#define Y_POS_INFO_TOP_EDGE    ((UINT8)0x10)
#define Y_POS_INFO_BOTTOM_EDGE ((UINT8)0x20)
#define Y_POS_INFO_MIDDLE      ((UINT8)0x30)
#define Y_POS_INFO_MASK        ((UINT8)0xF0)

typedef struct _VIDEO_REGION_POS_T
{
    UINT32                  ui4_x;      /* in 1/VSH_REGION_MAX_WIDTH */
    UINT32                  ui4_y;      /* in 1/VSH_REGION_MAX_HEIGHT */
    UINT8                   ui1_pos_info;
} VIDEO_REGION_POS_T;

typedef struct _ASPECT_RATIO_T
{
    UINT8          ui1_width;
    UINT8          ui1_height;
} ASPECT_RATIO_T;

#define INVALID_PIP_MLM_KEY          (0xFFFF)
typedef struct _PIP_SUB_POS_T
{
    TV_PIP_SUB_POSITION_T   e_id;
    UINT16                  ui2_mlm_key;
    VIDEO_REGION_POS_T      t_pos;
} PIP_SUB_POS_T;

typedef struct _PIP_SUB_SIZE_T
{
    TV_PIP_SUB_SIZE_T       e_id;
    UINT16                  ui2_mlm_key;
    UINT32                  ui4_width;
} PIP_SUB_SIZE_T;

typedef struct _POP_REGION_T
{
    VIDEO_REGION_POS_T      t_pos;
    UINT32                  ui4_width;
} POP_REGION_T;

typedef struct _POP_REGION_INFO_T
{
    POP_REGION_T            t_center_region;
    UINT32                  ui4_step_width;
    UINT16                  ui2_num_of_increase_step;
    UINT16                  ui2_num_of_decrease_step;
} POP_REGION_INFO_T;

typedef struct _POP_CUSTOM_KEY_MAP
{
    UINT32                  ui4_original_key;
    UINT8                   ui1_tv_mode_bits;
    UINT32                  ui4_mapped_key;    
} POP_CUSTOM_KEY_MAP;

typedef struct _POP_TV_MODE_TRAN_MAP
{
    TV_MODE_T               e_crnt_mode;
    TV_MODE_T               e_next_mode;
} POP_TV_MODE_TRAN_MAP;
    
#define INVALID_VSH_REGION_POS_X          (VSH_REGION_MAX_WIDTH+1)
#define INVALID_VSH_REGION_POS_Y          (VSH_REGION_MAX_HEIGHT+1)
#define INVALID_VSH_REGION_WIDTH          (VSH_REGION_MAX_WIDTH+1)
#define INVALID_VSH_REGION_HEIGHT         (VSH_REGION_MAX_HEIGHT+1)
#define VIDEO_REGION_POS_END              {INVALID_VSH_REGION_POS_X, INVALID_VSH_REGION_POS_Y, 0}
#define VIDEO_REGION_SIZE_END             INVALID_VSH_REGION_WIDTH
#define IS_VIDEO_REGION_POS_END(pt_x)     ((pt_x)->ui4_x==INVALID_VSH_REGION_POS_X&&(pt_x)->ui4_y==INVALID_VSH_REGION_POS_Y&&(pt_x)->ui1_pos_info==0)
#define IS_VIDEO_REGION_SIZE_END(_width)  (_width==INVALID_VSH_REGION_WIDTH)

#define POP_CUSTOM_KEY_MAP_END            {0, 0, 0}
#define IS_POP_CUSTOM_KEY_MAP_END(pt_x)   ((pt_x)->ui4_original_key == 0 && (pt_x)->ui1_tv_mode_bits == 0 && (pt_x)->ui4_mapped_key == 0)

#define POP_TV_MODE_TRAN_MAP_END          {TV_MODE_TYPE_LAST_VALID_ENTRY, TV_MODE_TYPE_LAST_VALID_ENTRY}
#define IS_POP_TV_MODE_TRAN_MAP_END(pt_x) ((pt_x)->e_crnt_mode == TV_MODE_TYPE_LAST_VALID_ENTRY && (pt_x)->e_next_mode == TV_MODE_TYPE_LAST_VALID_ENTRY)

/*
 * height = _width / VSH_REGION_MAX_WIDTH * (_scrn_asp_numerator / _scrn_asp_denominator) * (_trgt_denominator / _trgt_asp_numerator) * VSH_REGION_MAX_HEIGHT
 * height = 500/1000 * 16/9 * 3/4 * 1000 = 666
 */
#define GET_W_FROM_H(_ui4_width, _pt_scrn_a_ratio, _pt_trgt_a_ratio)     \
            ((UINT32) (((UINT64)(_ui4_width)) * (UINT64)((_pt_scrn_a_ratio)->ui1_width) * (UINT64)((_pt_trgt_a_ratio)->ui1_height) * VSH_REGION_MAX_HEIGHT / VSH_REGION_MAX_WIDTH / (UINT64)((_pt_scrn_a_ratio)->ui1_height) / ((UINT64)(_pt_trgt_a_ratio)->ui1_width)))


extern const GL_COLOR_T  t_g_pop_win_focus_color;
extern const GL_COLOR_T  t_g_pop_win_blur_color;
extern const WGL_INSET_T t_g_pop_win_focus_bdr;
extern const WGL_INSET_T t_g_pop_win_blur_bdr;

#ifdef APP_ONLY_DISP_NO_VIDEO_REASON_FOR_SUB
  #ifndef APP_PIP_POP_DISP_NO_VIDEO_REASON
  #define APP_PIP_POP_DISP_NO_VIDEO_REASON
  #endif
#endif

#ifdef APP_COLOR_MODE_PALLET
    #define APP_IN_PALETTE_MODE
#endif

#ifdef APP_IN_PALETTE_MODE
    #define BLACK_COLOR             NAV_COLOR_BLACK
    #define TRANSPARENT_COLOR       NAV_COLOR_TRANS
    #define VIDEO_MUTE_COLOR        NAV_COLOR_BLUE
#endif

#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
#define POP_NO_VIDEO_MSG_ALIGNMENT        WGL_AS_CENTER_CENTER

typedef struct _POP_VIEW_REASON_MSG_RC_T
{
    GL_COLOR_T          t_colors[TV_WIN_ID_LAST_VALID_ENTRY];
    WGL_FONT_INFO_T*    pt_pip_fonts[TV_WIN_ID_LAST_VALID_ENTRY];
    WGL_FONT_INFO_T*    pt_pop_fonts[TV_WIN_ID_LAST_VALID_ENTRY];
} POP_VIEW_REASON_MSG_RC_T;
#endif

#define POP_VIEW_WARNING_OSD_X  (320)
#define POP_VIEW_WARNING_OSD_Y  (130)
#define POP_VIEW_WARNING_OSD_W  (312)
#define POP_VIEW_WARNING_OSD_H  (77)

#define POP_VIEW_WARNING_OSD_TXT_INFO_X  (0)
#define POP_VIEW_WARNING_OSD_TXT_INFO_Y  (0)
#define POP_VIEW_WARNING_OSD_TXT_INFO_W  (312)
#define POP_VIEW_WARNING_OSD_TXT_INFO_H  (50)

#define POP_VIEW_WARNING_OSD_BTN_X  (8)
#define POP_VIEW_WARNING_OSD_BTN_Y  (52)
#define POP_VIEW_WARNING_OSD_BTN_W  (295)
#define POP_VIEW_WARNING_OSD_BTN_H  (33)
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
extern INT32 pop_view_init_reason_msg_rc(
                    POP_VIEW_REASON_MSG_RC_T*   pt_rc
                    );
extern INT32 pop_view_deinit_reason_msg_rc(
                    POP_VIEW_REASON_MSG_RC_T*   pt_rc
                    );
#endif
#endif /* _POP_CUSTOM_H_ */
