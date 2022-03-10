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
 * $RCSfile: usb_pld.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *       USB Plug Detection.
 *
 *---------------------------------------------------------------------------*/
#ifndef _NAV_VIA_DLG_H_
#define _NAV_VIA_DLG_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_scc.h"
#include "u_wgl_image.h"

#include "nav/via_dlg/a_nav_via_dlg.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

struct _NAV_VIA_DLG_HDLR_T;

typedef INT32 (*nav_via_dlg_view_init_fct)(
                    struct _NAV_VIA_DLG_HDLR_T*     pt_ctrl,
                    HANDLE_T                        h_canvas);

typedef INT32 (*nav_via_dlg_view_deinit_fct)(VOID);

typedef INT32 (*nav_via_dlg_view_hide_fct)(VOID);

typedef INT32 (*nav_via_dlg_view_show_fct)(VOID);

typedef BOOL (*nav_via_dlg_view_is_key_handler_fct)(UINT32  ui4_key_code);

typedef struct _NAV_VIA_DLG_VIEW_HDLR_T
{
    nav_via_dlg_view_init_fct              pf_init;
    nav_via_dlg_view_deinit_fct            pf_deinit;
    nav_via_dlg_view_hide_fct              pf_hide;
    nav_via_dlg_view_show_fct              pf_show;
    nav_via_dlg_view_is_key_handler_fct    pf_is_key_handler;
} NAV_VIA_DLG_VIEW_HDLR_T;

typedef struct _NAV_VIA_DLG_HDLR_T
{
    HANDLE_T                    h_svctx;
    HANDLE_T                    h_timer_bl;
    NAV_VIA_DLG_VIEW_HDLR_T     t_view_hdlr;
    NAV_CONTEXT_T*              pt_ctx;
    BOOL                        b_is_show;
    BOOL                        b_is_battery_low_level;
    UINT16                      ui2_icl_wifi_remote_battery_status;
    
} NAV_VIA_DLG_HDLR_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 a_nav_via_dlg_register(VOID);
extern INT32 a_nav_via_dlg_stop_cb(VOID);
extern VOID a_nav_via_dlg_set_via_lock(BOOL b_lock);
extern BOOL a_nav_via_dlg_get_via_lock(VOID);
extern INT32 a_nav_via_dlg_get_yahoo_state_cb(VOID);
#endif /* _NAV_VIA_DLG_H_ */
