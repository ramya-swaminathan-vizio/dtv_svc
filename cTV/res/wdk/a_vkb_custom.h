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
 * $RCSfile: a_vkb.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: GUI composite component -- Time Entry
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_WDK_VKB_CUSTOM_H_
#define _A_WDK_VKB_CUSTOM_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_wgl.h"
#include "u_wgl_common.h"
#include "app_util/a_common.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/* The style could be changed run-time */
#define VKB_STYLE_MASK_WIFI_PWD      MAKE_BIT_MASK_32(3)
#define VKB_STYLE_MASK_WIFI_SSID     MAKE_BIT_MASK_32(4)
#define VKB_STYLE_MASK_WZD           MAKE_BIT_MASK_32(5)
#define VKB_STYLE_MASK_WZD_PWD       MAKE_BIT_MASK_32(6)
#define VKB_STYLE_MASK_MENU          MAKE_BIT_MASK_32(7)
#define VKB_STYLE_MASK_WZD_DROP_DOWN MAKE_BIT_MASK_32(8)
#define VKB_STYLE_MASK_NO_COM_KEY      MAKE_BIT_MASK_32(9)
#define VKB_STYLE_MASK_FULL_SCREEN                      MAKE_BIT_MASK_32(10)
#define VKB_STYLE_MASK_FULL_SCREEN_WITH_EB              MAKE_BIT_MASK_32(11)
#define VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_OK          MAKE_BIT_MASK_32(12)
#define VKB_STYLE_MASK_FULL_SCREEN_WITH_BTN_CANCLE      MAKE_BIT_MASK_32(13)
#define VKB_STYLE_MASK_WITH_EB_CLEAR                    MAKE_BIT_MASK_32(14)
#define VKB_STYLE_MASK_MENU_NO_EB_NO_BTN                MAKE_BIT_MASK_32(15)
#define VKB_STYLE_MASK_DIGITAL_ONLY                     MAKE_BIT_MASK_32(16)


/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 a_vkb_enable_cancel_btn (HANDLE_T      h_vkb_handle,
                                      BOOL          b_enable);

extern INT32 a_vkb_set_focus_to_ok(HANDLE_T         h_vkb_handle);

extern INT32 a_vkb_set_focus_to_cancel(HANDLE_T     h_vkb_handle);

extern INT32 a_vkb_current_is_top_row(HANDLE_T      h_vkb_handle,
                                      BOOL*         pb_is_top_row);

extern INT32 a_vkb_current_is_ok_btn(HANDLE_T       h_vkb_handle,
                                     BOOL*          pb_is_ok_btn);
extern INT32 a_vkb_current_is_cancel_btn(HANDLE_T  h_vkb_handle,
                              BOOL*     pb_is_cancel_btn);
extern INT32 a_vkb_current_is_bottom_row(HANDLE_T   h_vkb_handle,
                                         HANDLE_T*  ph_cancel_handle,
                                         BOOL*      pb_is_bottom_row);

#endif /* _A_WDK_VKB_CUSTOM_H_ */

