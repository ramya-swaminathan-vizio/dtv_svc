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
#include "wizard_anim/wzd.h"

typedef enum DEVICE_SETUP_STATE
{
   DEVICE_SETUP_STATE_HIDE = 0,
   DEVICE_SETUP_CHOOSE_DEVICE,
   DEVICE_SETUP_SELECT_INPUT,
   DEVICE_SETUP_SELECT_BRAND,
   DEVICE_SETUP_SELECT_MODEL,
   DEVICE_SETUP_CODE_CONFIRM,
   DEVICE_SETUP_FINISHED
}DEVICE_SETUP_STATE;

typedef enum _DEVICE_SETUP_ENTER_REASON
{
   DEVICE_SETUP_ENTER_REASON_NONE = 0,
   DEVICE_SETUP_ENTER_REASON_TV_SETUP,
   DEVICE_SETUP_ENTER_REASON_TV_SETUP_ANTENNA_NOT_PAIR,
   DEVICE_SETUP_ENTER_REASON_TV_SETUP_ANTENNA_PAIR,
   DEVICE_SETUP_ENTER_REASON_TV_SETUP_DIRECT_FROM_WALL_PAIR,
   DEVICE_SETUP_ENTER_REASON_TV_SETUP_RF_SCAN_COMPLETE,
   DEVICE_SETUP_ENTER_REASON_LAST_VALID_ITEM
}DEVICE_SETUP_ENTER_REASON;

/* Enum the box of the select box */
typedef enum _TV_DEV_SETUP_SEL_BOX_BTN_INDEX_T
{
    DEV_SETUP_SEL_BOX_BTN_01 = 0,
    DEV_SETUP_SEL_BOX_BTN_02,
    DEV_SETUP_SEL_BOX_BTN_03,
    DEV_SETUP_SEL_BOX_BTN_04,
    DEV_SETUP_SEL_BOX_BTN_05,
    DEV_SETUP_SEL_BOX_BTN_06,
    DEV_SETUP_SEL_BOX_BTN_07,
    DEV_SETUP_SEL_BOX_BTN_COUNT  /* 7 */
}TV_DEV_SETUP_SEL_BOX_BTN_INDEX_T;

extern INT32 wzd_page_tv_remote_device_setup_get_page_info_data( WZD_PAGE_INFO_DATA_T* pt_info_data);
extern INT32 wzd_page_tv_remote_device_setup_nfy_sel(UINT16 ui2_sel_idx, VOID* pv_data, WZD_MSG_CUSTOM_T* pt_ret_msg);
extern INT32 wzd_page_tv_remote_device_setup_unfocus_footer(VOID);
extern INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_setup (UINT32  ui4_dev_type_sel_idx);
extern INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_not_pair_antenna (VOID);
extern INT32 wzd_page_tv_remote_device_setup_back_to_tuner_setup (VOID);
extern INT32 wzd_page_tv_remote_device_reset_page_show_flag (VOID);
extern INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_setup_rf_scan (VOID);
extern INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_pair_antenna (VOID);
extern INT32 wzd_page_tv_remote_device_setup_enter_from_tuner_pair_direct_from_wall (VOID);

