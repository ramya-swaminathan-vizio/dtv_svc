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

#ifndef _WZD_PAGE_TV_SETUP_H_
#define _WZD_PAGE_TV_SETUP_H_

#include "wizard_anim/wzd.h"

#define TV_SETUP_EB_TITILE_X     	(15 * WZD_UI_RATIO_W)
#define TV_SETUP_EB_TITILE_Y        (0 * WZD_UI_RATIO_W)
#define TV_SETUP_EB_TITILE_H        (43 * WZD_UI_RATIO_W)

#define TV_SETUP_EB_TITILE_ICON_W   (20 * WZD_UI_RATIO_W)

#define TV_SETUP_EB_TOP_INSET       (8 * WZD_UI_RATIO_W)
#define TV_SETUP_EB_BOTTOM_INSET    (8 * WZD_UI_RATIO_W)


#define TV_SETUP_EB_LEFT_INSET   	(150 * WZD_UI_RATIO_W)
#define TV_SETUP_EB_RIGHT_INSET  	(20 * WZD_UI_RATIO_W)

/* for move animation */
#define WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_X         WZD_SEL_BOX_BTN_ICON_2_X
#define WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y1        WZD_SEL_BOX_BTN_ICON_2_Y + 20 * WZD_UI_RATIO_W
#define WZD_TV_SETUP_SEL_BOX_BTN_ICON_2_MOVE_DOWN_Y2        WZD_SEL_BOX_BTN_ICON_2_Y - 5 * WZD_UI_RATIO_W + 20 * WZD_UI_RATIO_W

#define WZD_TV_SETUP_SEL_BOX_BTN_TXT_MOVE_DOWN_X            WZD_SEL_BOX_BTN_TXT_X
#define WZD_TV_SETUP_SEL_BOX_BTN_TXT_MOVE_DOWN_Y            WZD_SEL_BOX_BTN_TXT_Y + 1 * WZD_UI_RATIO_W + 20 * WZD_UI_RATIO_W


extern INT32 wzd_page_tv_setup_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data);
extern INT32 wzd_page_tv_setup_nfy_sel(UINT16               ui2_sel_idx,
                                      VOID*                 pv_data,
                                      WZD_MSG_CUSTOM_T*     pt_ret_msg);
extern INT32 wzd_page_tv_setup_on_scan_complete( UINT16 ui2_ch_num );
extern INT32 wzd_page_tv_setup_enter_from_tv_remote_device_setup_rf(UINT32  ui4_dev_type_sel_idx);
extern INT32 wzd_page_tv_setup_enter_from_tv_name_input_rf(UINT32  ui4_dev_type_sel_idx);

extern INT32 wzd_page_tv_setup_rf_scan_start (VOID);
extern INT32 wzd_page_tv_setup_scan_cancel (VOID);
extern UINT16 wzd_page_tv_setup_get_scan_status (VOID);
extern VOID wzd_page_tv_setup_set_scan_status   (UINT16  ui2_scan_status);
extern BOOL wzd_page_tv_setup_is_scanning (VOID);
extern INT32 wzd_page_tv_setup_enter_from_tv_name_input_input(VOID);
extern INT32 wzd_page_tv_setup_enter_from_tv_remote_device_setup_input(VOID);

#endif /* _WZD_PAGE_TV_SETUP_H_ */
