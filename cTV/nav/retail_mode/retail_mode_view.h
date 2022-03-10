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
 * $RCSfile: retail_mode_view.h,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/11 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: e4fca22a35d115b284d4931487730df1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _RETAIL_MODE_VIEW_H_
#define _RETAIL_MODE_VIEW_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define OOBE_DEVICE_PAIR_TIMEOUT                        (15*60*1000)/* 15 min */
#define RETAIL_MODE_POWNER_ON_NOTIFICATION_TIMEOUT      (60*1000)   /* 60 sec */
#define RETAIL_MODE_NORMAL_NOTIFICATION_TIMEOUT         (15*1000)   /* 15 sec */

#define LOGO_FRAME_X         (0)   /*  */
#define LOGO_FRAME_Y         (0)   /*  */
#define LOGO_FRAME_W         (224)   /*  224*/
#define LOGO_FRAME_H         (152)   /*  152*/

#define IS_SYNC_REPAINT                         (TRUE)

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
typedef enum
{
    RETAIL_MODE_VIEW_TIMER_STOP = 0,
    RETAIL_MODE_VIEW_TIMER_DEVICE_PAIR,
    RETAIL_MODE_VIEW_TIMER_NOTIFICATION
} RETAIL_MODE_VIEW_TIMER_T;

typedef struct _RETAIL_MODE_VIEW_T
{
    BOOL            b_is_init;
    BOOL            b_is_on;

    HANDLE_T        h_canvas;
    HANDLE_T        h_toast_view;

    HANDLE_T        h_frame_logo;
    HANDLE_T        h_icon_logo;
    BOOL            b_is_logo_on;

    HANDLE_T        h_timer;
    UINT32          ui4_timeout;
    UINT16          ui2_timer_count; /* ui2_timer_count*1000 <= ui4_timeout */
    RETAIL_MODE_VIEW_TIMER_T    e_timer_status;
    BOOL            b_is_pair_page;

    UINT16          ui2_cfg_nfy_id;
} RETAIL_MODE_VIEW_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 retail_mode_view_init(HANDLE_T h_canvas);
extern INT32 retail_mode_view_deinit(VOID);
extern INT32 retail_mode_view_show(UTF16_T*  pw2s_string);
extern INT32 retail_mode_view_hide(VOID);
extern BOOL  retail_mode_view_show_fift_minute(VOID);
extern INT32 retail_mode_view_timer_start(
                        RETAIL_MODE_VIEW_TIMER_T    e_timer_status,
                        UINT32  ui4_timeout);
extern INT32 retail_mode_view_timer_restart(VOID);
extern INT32 retail_mode_view_timer_stop(VOID);

extern BOOL  retail_mode_view_is_on(VOID);


extern INT32 retail_mode_view_logo_init(HANDLE_T h_canvas);
extern INT32 retail_mode_view_logo_show(VOID);
extern INT32 retail_mode_view_logo_hide(VOID);
extern INT32 retail_mode_view_check_logo(VOID);
extern BOOL  retail_mode_view_logo_is_show(VOID);
extern VOID clear_count_timer_status(VOID);

#endif /* _RETAIL_MODE_VIEW_H_ */
