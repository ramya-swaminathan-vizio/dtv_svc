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
 * $RCSfile: nav_zoom_view.h,v $
 * $Revision: #1 $
 * $Date: 2016/09/22 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Screen Mode controller is a signaltone
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_ZOOM_VIEW_H_
#define _NAV_ZOOM_VIEW_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_gl.h"

#include "res/nav/zoom/nav_zoom_custom.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
//extern ZOOM_INDICATE_T   indicate_view;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

#define ZOOM_MODE_INDICATE_TIMER_DELAY (5000)
#define ZOOM_MODE_MSG_TIMER_DELAY (10000)
extern VOID nav_zoom_mode_indicate_icon_hide(
                        VOID*                       pv_tag,
                        VOID*                       pv_tag2,
                        VOID*                       pv_tag3
                        );

extern INT32 nav_zoom_sector_indicate_activate(ZOOM_SECTOR_ITEM e_item);
extern INT32 nav_zoom_mode_indicate_view_init(VOID);
extern INT32 nav_zoom_mode_msg_view_init(VOID);
extern INT32 nav_zoom_mode_msg_show(UINT16 ui2_msg_mlm_idx);
extern INT32 nav_zoom_mode_msg_show_delay_timer(VOID);
extern INT32 nav_zoom_mode_msg_hide(VOID);
extern INT32 nav_zoom_mode_msg_move(INT32 sector_item, BOOL reback);
extern INT32 nav_zoom_mode_send_toast_msg(UINT16 ui2_msg_mlm_idx);

/*--------------------------------------------------------------------------
 * structure, constants, macro definitions
 *------------------------------------------------------------------------*/

typedef struct _ZOOM_INDICATE_T
{
    GL_HSCREEN_T    h_screen;
    GL_HPLANE_T     h_plane;
    GL_HPLANE_T     h_cc_plane;
    HANDLE_T        h_canvas;
    HANDLE_T        h_cc_canvas;
    /* widget */
    HANDLE_T        h_frame_sector;
    HANDLE_T        h_icon_sector;
    HANDLE_T        h_frame_sector_hilite;
    HANDLE_T        h_icon_sector_hilite;

    HANDLE_T        h_frame_msg;
    HANDLE_T        h_text_msg;

    HANDLE_T        h_frame_zoom_msg;
    HANDLE_T        h_text_zoom_msg;

    UINT32          ui4_canvas_width;
    UINT32          ui4_canvas_height;
    HANDLE_T        h_icon_timer_hide;
    UINT32          ui4_icon_timeout;
    HANDLE_T        h_msg_timer_hide;
    UINT32          ui4_msg_timeout;
    BOOL            b_icon_show;//the indicate icon is showing.
    BOOL            b_msg_show;//the zoom mode msg is showing.
} ZOOM_INDICATE_T;

#endif /* _NAV_ZOOM_H_ */

