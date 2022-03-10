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
 * $RCSfile: nav_zoom_custom.h,v $
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
#ifndef _NAV_ZOOM_CUSTOM_H_
#define _NAV_ZOOM_CUSTOM_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_gl.h"

#include "app_util/a_common.h"
#include "app_util/a_zoom_mode.h"

#define NAV_ZOOM_TTS_ON L"Zoom mode enabled. Use your number pad to move the focus for zoom mode."\
				"Press the Dash key to stop using digits for zoom mode. Or press and hold the MENU key to use Left, Right, Up"\
				"or Down to move the zoom mode focus."

#define NAV_ZOOM_NO_NUMBER_PAD_TTS_ON L"Zoom mode enabled. Press and hold the Menu key to enable zoom focus navigation using up, down, left and right."

#define NAV_ZOOM_TTS_OFF L"Zoom Mode is off"

#define NAV_ZOOM_ON_TITLE_ADD_IMG	(1)
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define NAV_ZOOM_NAVIGATION_ENABLE      (1) /*dis/enable navigation zoom XRC-260*/
/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 nav_zoom_cust_init(VOID);

extern INT32 nav_zoom_cust_handle_msg (
                NAV_UI_MSG_T*       pt_ui_msg,
                VOID*               pv_arg1
                );

extern INT32 nav_zoom_cust_comp_state_trans_nfy (
                NAV_COMP_STATE_TRANS_COND_T e_cond,
                NAV_COMP_ID_T       e_from_comp_id,
                NAV_COMP_ID_T       e_to_comp_id);

extern BOOL a_nav_zoom_cust_get_num_pad_navi_status (VOID);

extern ZOOM_SECTOR_ITEM nav_zoom_cust_get_default_sector_item(const UINT16 ui2_id);

extern ZOOM_SECTOR_ITEM nav_zoom_cust_get_current_sector_item(VOID);

extern ZOOM_SECTOR_SET_T nav_zoom_cust_get_include_items(const UINT16 ui2_id);

extern VOID a_nav_zoom_cust_select_top_sector (VOID);

extern INT32 a_nav_zoom_cust_select_sector (UINT8 ui1_sector, BOOL b_need_store);
extern VOID nav_zoom_mode_power_on_send_toast_msg(VOID);
extern VOID a_nav_zoom_cust_long_press_menu(BOOL b_zoom_mode);
extern BOOL a_nav_zoom_cust_get_digital_pad_status(VOID);
extern VOID a_nav_zoom_cust_set_digital_pad_status(BOOL b_digit_pad);
extern BOOL a_nav_zoom_cust_get_nav_zoom_status(VOID);
extern UINT32 a_nav_zoom_cust_navigation_num_pad(UINT32 ui4_evt_code);
extern INT32 a_nav_zoom_cust_enable_dash_timer(VOID);
extern BOOL a_nav_zoom_cust_get_digital_timer_status(VOID);
#endif /* _NAV_ZOOM_CUSTOM_H_ */

