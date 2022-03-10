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
 * $RCSfile: a_wzd.h,v $
 * $Revision: #2 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/4 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: cedbdb40d27bde1235b27f82667dff7d $
 *
 * Description:
 *         This header file contains Wizard's specific definitions, which
 *         are exported.
 *---------------------------------------------------------------------------*/

#ifndef _A_WZD_H_
#define _A_WZD_H_

#include "amb/a_amb.h"
#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
#include "res/app_util/config/a_cfg_custom.h"
#endif

#ifndef APP_WZD_TIME_ZONE_ENABLE
#define APP_WZD_TIME_ZONE_ENABLE
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define  WZD_NAME                  "wizard"

/* WZD API's return values */
#define  WZDR_OK                   ((INT32)    0)
#define  WZDR_FAIL                 ((INT32)   -1)
#define  WZDR_INV_ARG              ((INT32)   -2)
#define  WZDR_UNKNOWN_MSG          ((INT32)   -3)
#define  WZDR_OUT_OF_MEM           ((INT32)   -4)

typedef enum _WZD_PAGE_INDEX_T
{
#ifdef APP_2K12_RETAIL_DEMO_MODE
    WZD_PAGE_INDEX_CHO_MODE = 0,
    WZD_PAGE_INDEX_LANG,
#else
    WZD_PAGE_INDEX_LANG = 0,
#endif
    WZD_PAGE_INDEX_COUNTRY,
#ifdef APP_WZD_TIME_ZONE_ENABLE
    WZD_PAGE_INDEX_TIME_ZONE,
#endif
    WZD_PAGE_INDEX_WIFI_REMOTE_PARING,

    WZD_PAGE_INDEX_NW_SETUP,
    WZD_PAGE_INDEX_TV_SETUP,
    WZD_PAGE_TV_REMOTE_DEVICE_SETUP,
    WZD_PAGE_TV_NAME_INPUT,
    WZD_PAGE_INDEX_COMPLETE,
    WZD_PAGE_INDEX_LAST_VALID_ITEM
}WZD_PAGE_INDEX_T;

/*-----------------------------------------------------------------------------
                    functions declarations
 ----------------------------------------------------------------------------*/
extern VOID  a_wzd_init (AMB_REGISTER_INFO_T* pt_reg);
extern VOID  a_wzd_send_sim_key (UINT32  ui4_key_code);

extern BOOL  a_wzd_is_resume (VOID);

extern BOOL  a_wzd_is_show (VOID);

extern INT32 a_wzd_resume_network_setting (VOID);

extern INT32 a_wzd_resume_tv_setup (VOID);

extern BOOL a_wzd_is_resume_from_menu_setup (VOID);

extern BOOL a_wzd_is_resume_from_wifi_unpairing(VOID);
extern INT32 a_wzd_resume_tv_remote_device_setup (VOID);
extern INT32 a_wzd_resume_tv_remote_pairing_setup(VOID);

extern BOOL  a_wzd_is_keep_mute (VOID);

#endif /* _A_WZD_H_ */
