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
 * $RCSfile: scrn_blank.h,v $
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
#ifndef _SCRN_BLANK_H_
#define _SCRN_BLANK_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_gl.h"

#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define NAV_SCRN_BLANK_STATE_TIMER_PHASE1               ((UINT16)0)
#define NAV_SCRN_BLANK_STATE_TIMER_PHASE2               ((UINT16)1)
#define NAV_SCRN_BLANK_STATE_BLANK                      ((UINT16)2)
#define NAV_SCRN_BLANK_STATE_UNKNOW                     ((UINT16)0xFFFF)

typedef struct _SCRN_BLANK_VIEW_T
{
    HANDLE_T                    h_frame;
    HANDLE_T                    h_title;
    GL_RECT_T                   t_orig_rect;
    BOOL                        b_show;
} SCRN_BLANK_VIEW_T;

typedef enum {
    SCRN_BLANK_MSG_TYPE_UNKNOWN = 0,
    SCRN_BLANK_MSG_TYPE_MSG_ID,
    SCRN_BLANK_MSG_TYPE_MLM_KEY
} SCRN_BLANK_MSG_TYPE_T;

typedef struct _SCRN_BLANK_MSG_T
{
    SCRN_BLANK_MSG_TYPE_T         e_type;

    union {
        MSG_STR_ID_T            e_msg_id;
        UINT16                  ui2_mlm_key;
    } u;

} SCRN_BLANK_MSG_T;

typedef struct _SCRN_BLANK_T
{
    SCRN_BLANK_VIEW_T           t_view;
    BOOL                        b_is_on;    //TRUE:timer is started
    BOOL                        b_msg_visible;
    UINT32                      ui4_timeout;
    HANDLE_T                    h_timer;
    TV_WIN_ID_T                 e_focus_tv_win_id;
    SCRN_BLANK_MSG_T            t_msgs[TV_WIN_ID_LAST_VALID_ENTRY];
    BOOL                        b_delay_to_activate;
    BOOL                        b_enable;   //TRUE:timer need be restart
    HANDLE_T                    h_main_svctx;
    BOOL                        b_phase1;
} SCRN_BLANK_T;
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
/* view */
extern INT32 scrn_blank_view_init(
                    SCRN_BLANK_T*                 pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
extern INT32 scrn_blank_view_deinit(
                    SCRN_BLANK_VIEW_T*            pt_view
                    );
extern INT32 scrn_blank_view_show(
                    SCRN_BLANK_VIEW_T*            pt_view,
                    UTF16_T*                    pw2s_string
                    );
extern INT32 scrn_blank_view_hide(
                    SCRN_BLANK_VIEW_T*            pt_view
                    );
extern INT32 a_scrn_blank_reset(VOID);

extern UINT16 a_scrn_blank_get_state(VOID);

extern INT32 a_scrn_blank_am_msg_proc(VOID);
#endif /* _SCRN_BLANK_H_ */
