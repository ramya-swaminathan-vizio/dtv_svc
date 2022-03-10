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
 * $RCSfile: scrn_svr.h,v $
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
#ifndef _SCRN_SVR_H_
#define _SCRN_SVR_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_gl.h"

#include "wdk/a_wdk.h"
#include "app_util/toast_widget/a_toast.h"

#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef APP_NO_SIGNAL_IDLE_SET_DISP_BG
#ifndef DISP_NORMAL_BG_RED
#define DISP_NORMAL_BG_RED          (0x00)
#endif
#ifndef DISP_NORMAL_BG_GREEN
#define DISP_NORMAL_BG_GREEN        (0x00)
#endif
#ifndef DISP_NORMAL_BG_BLUE
#define DISP_NORMAL_BG_BLUE         (0x00)
#endif
#ifndef DISP_NO_SIGNAL_BG_RED
#define DISP_NO_SIGNAL_BG_RED       (0x00)
#endif
#ifndef DISP_NO_SIGNAL_BG_GREEN
#define DISP_NO_SIGNAL_BG_GREEN     (0x00)
#endif
#ifndef DISP_NO_SIGNAL_BG_BLUE
#define DISP_NO_SIGNAL_BG_BLUE      (0xff)
#endif
#endif

typedef struct _SCRN_SVR_VIEW_T
{
    HANDLE_T                    h_canvas;
    HANDLE_T                    h_toast_no_signal;
    HANDLE_T                    h_toast_no_signal_2;
    HANDLE_T                    h_toast_warning_view;
    HANDLE_T                    h_toast_warning_view_with_title;
    HANDLE_T                    h_toast_signal_acquire;
    UTF16_T                     w2s_err_title[MAX_ERR_MSG_SIZE+1];
} SCRN_SVR_VIEW_T;

typedef enum {
    SCRN_SVR_MSG_TYPE_UNKNOWN = 0,
    SCRN_SVR_MSG_TYPE_MSG_ID,
    SCRN_SVR_MSG_TYPE_MLM_KEY
} SCRN_SVR_MSG_TYPE_T;

typedef struct _SCRN_SVR_MSG_T
{
    SCRN_SVR_MSG_TYPE_T         e_type;

    union {
        MSG_STR_ID_T            e_msg_id;
        UINT16                  ui2_mlm_key;
    } u;

} SCRN_SVR_MSG_T;

typedef struct _SCRN_SVR_T
{
    SCRN_SVR_VIEW_T             t_view;
    BOOL                        b_is_on;
    BOOL                        b_msg_visible;
    UINT32                      ui4_timeout;
    HANDLE_T                    h_timer;
    TV_WIN_ID_T                 e_focus_tv_win_id;
    SCRN_SVR_MSG_T              t_msgs[TV_WIN_ID_LAST_VALID_ENTRY];
    BOOL                        b_delay_to_activate;
    BOOL                        b_enable;
    BOOL                        b_need_delay_show_network_lost;
    HANDLE_T                    h_main_svctx;
    TOAST_STYLE_T               e_toast_style;
    UINT32                      ui4_nw_nfy_id;
    UINT16                      ui2_icl_nfy_id;
	UINT16                      ui2_icl_nfy_id_mmp;
} SCRN_SVR_T;
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
/* view */
extern INT32 scrn_svr_view_init(
                    SCRN_SVR_T*                 pt_this,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    );
extern INT32 scrn_svr_view_deinit(
                    SCRN_SVR_VIEW_T*            pt_view
                    );
extern INT32 scrn_svr_view_show(
                    SCRN_SVR_VIEW_T*            pt_view,
                    UTF16_T*                    pw2s_string,
                    TOAST_STYLE_T               e_toast_style
                    );
extern INT32 scrn_svr_view_hide(
                    SCRN_SVR_VIEW_T*            pt_view,
                    TOAST_STYLE_T               e_toast_style
                    );
extern INT32 scrn_svr_view_move(
                    SCRN_SVR_VIEW_T*            pt_view,
                    BOOL                        b_first_time,
                    BOOL                        b_repaint
                    );
extern BOOL a_scrn_svr_check_err_msg_for_format_not_support(VOID);

extern INT32 scrn_svr_set_str_id_to_empty(VOID);

extern INT32 scrn_svr_view_hide_signal_acquire(VOID);

#endif /* _SCRN_SVR_H_ */
