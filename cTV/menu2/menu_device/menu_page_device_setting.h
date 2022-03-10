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
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/

#ifndef _MENU_PAGE_DEVICE_SETTING_H_
#define _MENU_PAGE_DEVICE_SETTING_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "menu_device.h"
#include "wfd/wfd_dev_list.h"

/*-----------------------------------------------------------------------------
                    custmizable macros
 ----------------------------------------------------------------------------*/
#define MENU_DEVICE_SETTING_INPUT_RGB_NAME              ("RGB")

#define MENU_DEVICE_SETTING_REMOTE_NAME_LEN (32)

/* Add Remode BTN  && Add Device BTN */
#define MENU_DEVICE_SETTING_REMOTE_BTN_NUM (2)
/* Add Miracast BTN */
#define MENU_DEVICE_SETTING_WFD_BTN_NUM (1)

#define MENU_DEVICE_SETTING_DEV_DISP_NAME_ALIGN        (WGL_AS_LEFT_CENTER)
#define MENU_DEVICE_SETTING_DEV_DISP_NAME_MAX_TEXT_LEN (MENU_DEVICE_NAME_MAX_LEN)
#define MENU_DEVICE_SETTING_DEV_DISP_NAME_COL_WIDTH    (MENU_ITEM_V_WIDE/2)

#define MENU_DEVICE_SETTING_DEV_USER_NAME_ALIGN        (WGL_AS_RIGHT_CENTER)
#define MENU_DEVICE_SETTING_DEV_USER_NAME_MAX_TEXT_LEN (MENU_DEVICE_NAME_MAX_LEN)
#define MENU_DEVICE_SETTING_DEV_USER_NAME_COLUMN_WIDTH (MENU_ITEM_V_WIDE   \
                                                        -MENU_DEVICE_SETTING_DEV_DISP_NAME_COL_WIDTH)

#define MENU_DEVICE_SETTING_MAX_DEVICE_NUM               (8)

#define MENU_DEVICE_SETTING_DEV_LIST_X           (MENU_ITEM_V_INSET_L)
#define MENU_DEVICE_SETTING_DEV_LIST_Y           (0)
#define MENU_DEVICE_SETTING_DEV_LIST_W           (MENU_ITEM_V_WIDE)
#define MENU_DEVICE_SETTING_DEV_LIST_H           (44*8)
#define MENU_DEVICE_SETTING_DEV_LIST_ELEM_HEIGHT      (44)

#define MENU_DEVICE_SETTING_LB_INSET_LEFT      (10)
#define MENU_DEVICE_SETTING_LB_INSET_RIGHT     (10)

#define MENU_DEVICE_SETTING_ADD_NEW_DEVICE_BTN_X         (0)
#define MENU_DEVICE_SETTING_ADD_NEW_DEVICE_BTN_Y         (MENU_DEVICE_SETTING_DEV_LIST_ELEM_HEIGHT    \
                                                          *MENU_DEVICE_SETTING_MAX_DEVICE_NUM)
#define MENU_DEVICE_SETTING_ADD_NEW_DEVICE_BTN_W         (MENU_ITEM_V_WIDE)
#define MENU_DEVICE_SETTING_ADD_NEW_DEVICE_BTN_H         (44)

#define MENU_DEVICE_SETTING_ADD_MIRACAST_DEVICE_BTN_X    (0)
#define MENU_DEVICE_SETTING_ADD_MIRACAST_DEVICE_BTN_Y    (MENU_DEVICE_SETTING_DEV_LIST_ELEM_HEIGHT   \
                                                          *MENU_DEVICE_SETTING_MAX_DEVICE_NUM)
#define MENU_DEVICE_SETTING_ADD_MIRACAST_DEVICE_BTN_W    (MENU_ITEM_V_WIDE)
#define MENU_DEVICE_SETTING_ADD_MIRACAST_DEVICE_BTN_H    (44)

#define MENU_DEVICE_SETTING_PAGE_BTN_INSET_LEFT          (10)
#define MENU_DEVICE_SETTING_PAGE_BTN_INSET_RIGHT         (10)


#define MENU_DEVICE_SETTING_BTN_ALIGN                    (WGL_AS_LEFT_CENTER)

#define MENU_DEVICE_SETTING_INPUT_USER_NAME_LEN   (32)
#define MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN   (32)

#define MENU_DEVICE_SETTING_CEC_DISCOVERY_DEVICE_NUM   (16)

#define MENU_DEVICE_SETTING_MIRACAST_DEVICE_NAME_LEN (DEVICE_INFO_MAX_NAME_LEN)

typedef struct _MENU_DEVICE_SETTING_CEC_DEV_DATA_T
{
	UTF16_T w2s_dev_osd_name[MENU_DEVICE_SETTING_CEC_DISCOVERY_DEVICE_NUM][MENU_DEVICE_SETTING_INPUT_DISP_NAME_LEN];
	UINT8   dev_num;
}MENU_DEVICE_SETTING_CEC_DEV_DATA_T;

extern UINT16 MENU_DEVICE_TYPE_IDX_ADD_REMOTE;
extern UINT16 MENU_DEVICE_TYPE_IDX_ADD_DEVICE;
extern UINT16 MENU_DEVICE_TYPE_IDX_MIRACAST;
extern UINT16 MENU_DEVICE_TYPE_IDX_UNPAIR;
extern UINT16 MENU_DEVICE_TYPE_IDX_NAME;
extern UINT16 MENU_DEVICE_TYPE_IDX_INPUT_SOURCE;
extern UINT16 MENU_DEVICE_TYPE_IDX_DEVICE_TYPE;
extern UINT16 MENU_DEVICE_TYPE_IDX_DEVICE_BRAND;
extern UINT16 MENU_DEVICE_TYPE_IDX_DEVICE_MODEL;
extern UINT16 MENU_DEVICE_TYPE_IDX_CONFIRM_IR;
extern UINT16 MENU_DEVICE_TYPE_IDX_DEVICE_MIRACAST_NAME_4_DEV;
extern UINT16 MENU_DEVICE_TYPE_IDX_EMPTY;
#endif /* _MENU_PAGE_DEVICE_SETTING_H_ */


