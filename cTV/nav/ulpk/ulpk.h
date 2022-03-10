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
 * $RCSfile: ulpk.h,v $
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
 
#ifdef APP_USB_INSTALL_ULPK_SUPPORT
#ifndef _NAV_ULPK_H_
#define _NAV_ULPK_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_scc.h"
#include "u_wgl_image.h"

#include "nav/ulpk/a_ulpk.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
struct _NAV_ULPK_T;

typedef INT32 (*ulpk_view_init_fct)(
                    struct _NAV_ULPK_T*        pt_ctrl,
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset
                    );
typedef INT32 (*ulpk_view_deinit_fct)(
                    VOID
                    );
typedef BOOL (*ulpk_view_is_key_handler_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*ulpk_view_activate_fct)(
                    UINT32                      ui4_key_code
                    );
typedef INT32 (*ulpk_view_hide)(
                    VOID
                    );

typedef enum _NAV_ULPK_STATE_ID_T
{
    NAV_ULPK_STATE_ID_NONE = 0,
    NAV_ULPK_STATE_ID_PLUG_USB_STICK,
    NAV_ULPK_STATE_ID_INSTALL_ULPK,
    NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL,
    NAV_ULPK_STATE_ID_INSTALL_COMPLETE_SUCCESS
} NAV_ULPK_STATE_ID_T;
typedef enum _NAV_ULPK_USB_STATE_ID_T
{
    NAV_ULPK_USB_STATE_ID_NONE = 0,
    NAV_ULPK_USB_STATE_ID_IN,
    NAV_ULPK_USB_STATE_ID_OUT
} NAV_ULPK_USB_STATE_ID_T;


typedef struct _NAV_ULPK_VIEW_HDLR_T
{
    ulpk_view_init_fct              pf_init;
    ulpk_view_deinit_fct            pf_deinit;
    ulpk_view_is_key_handler_fct    pf_is_key_handler;
    ulpk_view_activate_fct          pf_activate;
    ulpk_view_hide                  pf_hide;
} NAV_ULPK_VIEW_HDLR_T;

typedef struct _NAV_ULPK_T
{
    HANDLE_T                    h_hide_timer;
    BOOL                        b_is_on;
    NAV_ULPK_VIEW_HDLR_T        t_view_hdlr;
    NAV_ULPK_STATE_ID_T         t_ulpk_state;
    NAV_ULPK_USB_STATE_ID_T     b_usb_state;
} NAV_ULPK_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 nav_ulpk_view_register_default_hdlr(
                    NAV_ULPK_VIEW_HDLR_T*      pt_view_hdlr
                    );
extern VOID nav_ulpk_reset_timer(
                    NAV_ULPK_T*                pt_this,
                    UINT32                      ui4_timeout
                    );
extern VOID nav_set_ulpk_state(NAV_ULPK_STATE_ID_T t_ulpk_state);
extern VOID nav_get_ulpk_state(NAV_ULPK_STATE_ID_T* pt_ulpk_state);
extern VOID nav_set_usb_state(NAV_ULPK_USB_STATE_ID_T t_usb_state);
extern VOID nav_get_usb_state(NAV_ULPK_USB_STATE_ID_T* pt_usb_state);
extern INT32 nav_ulpk_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    );
extern INT32 nav_ulpk_install_process(VOID);
#endif /* _NAV_ULPK_H_ */
#endif
