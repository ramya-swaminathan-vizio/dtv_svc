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
 * $RCSfile: pic_mode.h,v $
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
#ifndef _NAV_PIC_MODE_H_
#define _NAV_PIC_MODE_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_scc.h"
#include "u_wgl_image.h"

#include "app_util/a_common.h"
#include "nav/pic_mode/a_pic_mode.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#define NAV_PIC_MODE_LOG_ON_FAIL(_ret)                                        \
if (_ret < 0)                                                                 \
{                                                                             \
    DBG_ERROR(("[NAV] Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
}


struct _NAV_PIC_MODE_T;

typedef INT32 (*pic_mode_view_init_fct)(
                    struct _NAV_PIC_MODE_T*        pt_ctrl,
                    HANDLE_T                       h_canvas,
                    INT32                          i4_frame_x_offset,
                    INT32                          i4_frame_y_offset,
                    UINT16                         ui2_elem_num
                    );
typedef INT32 (*pic_mode_view_deinit_fct)(
                    VOID
                    );
typedef BOOL  (*pic_mode_view_is_key_handler_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*pic_mode_view_activate_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*pic_mode_view_hide)(
                    VOID
                    );

typedef INT32 (*pic_mode_view_set_elem_num)(
                    UINT16                     ui2_elem_num
                    );

typedef INT32 (*pic_mode_view_set_hlt_index)(
                    UINT16                     ui2_idx
                    );

typedef INT32 (*pic_mode_view_set_index_text)(
                    UINT16                     ui2_idx,
                    UTF16_T*                   pw2s_text
                    );


typedef INT32 (*pic_mode_view_set_is_refreshing)(
                    BOOL                       b_is_refreshing
                    );

typedef INT32 (*pic_mode_view_set_title_text)(
                    UTF16_T*                   pw2s_title
                    );

typedef struct _NAV_PIC_MODE_VIEW_HDLR_T
{
    pic_mode_view_init_fct              pf_init;
    pic_mode_view_deinit_fct            pf_deinit;
    pic_mode_view_is_key_handler_fct    pf_is_key_handler;
    pic_mode_view_activate_fct          pf_activate;
    pic_mode_view_hide                  pf_hide;
	pic_mode_view_set_elem_num			pf_set_elem_num;
    pic_mode_view_set_hlt_index         pf_set_hlt_index;
    pic_mode_view_set_index_text        pf_set_index_text;
    pic_mode_view_set_is_refreshing     pf_set_is_refreshing;
    pic_mode_view_set_title_text        pf_set_title_text;
} NAV_PIC_MODE_VIEW_HDLR_T;

typedef struct _NAV_PIC_MODE_T
{
    HANDLE_T                       h_hide_timer;
    HANDLE_T                       h_update_ctrl_timer;
    UINT32                         ui4_timeout;
    BOOL                           b_is_on;
    BOOL                           b_is_view_init;
    BOOL                           b_can_update_pq;
    NAV_PIC_MODE_VIEW_HDLR_T       t_view_hdlr;
    UINT16                         ui2_curr_idx;
    UINT16                         ui2_last_idx;
} NAV_PIC_MODE_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

/* For ListBox Style - pic_mode_view_list.c */
extern INT32 nav_pic_mode_view_register_list_hdlr(
                    NAV_PIC_MODE_VIEW_HDLR_T*          pt_view_hdlr
                    );

/* For Dialog Style  - pic_mode_view_dialog.c */
extern INT32 nav_pic_mode_view_register_dialog_hdlr(
                    NAV_PIC_MODE_VIEW_HDLR_T*          pt_view_hdlr
                    );

/* For Single Select List Style  - pic_mode_view_single_select_list.c */
extern INT32 nav_pic_mode_view_register_single_select_list_hdlr(
                    NAV_PIC_MODE_VIEW_HDLR_T*          pt_view_hdlr
                    );

/* Component Internal */

extern VOID nav_pic_mode_reset_timer(
                    NAV_PIC_MODE_T*                    pt_this
                    );

extern BOOL nav_pic_mode_is_on(VOID);

/* Ctrl's API for Presentation */

extern VOID nav_pic_mode_ctrl_set_index(UINT16       ui2_idx);

extern VOID nav_pic_mode_ctrl_update_index(VOID);


#endif /* _NAV_PIC_MODE_H_ */
