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
 * $RCSfile: bluetooth_device.h,v $
 * $Revision: #1 $
 * $Date: 2015/10/17 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *      This file is the internal header file for bluetooth device.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

#ifndef _BLUETOOTH_DEVICE_H_
#define _BLUETOOTH_DEVICE_H_

#include "a_bluetooth.h"

#include "u_common.h"
//#include "u_bluetooth.h"

typedef struct _BT_APP_REMOTE_DEVICE       // the structure for remote device
{
    BT_APP_DEVICE_INFO_T    r_bt_device_info; // structure for bluetooth device info
    struct _BT_APP_REMOTE_DEVICE* pt_next;   // another remote device.
}BT_APP_REMOTE_DEV_T;

typedef struct _BT_APP_REMOTE_DEVICE_LIST // Remote device list, it is a singly linked list.
{
    UINT32 ui4_num;                    // Specify how many devices in the device list.
    BT_APP_REMOTE_DEV_T* pt_first_dev; // Points to first device, NULL for empty list.
}BT_APP_REMOTE_DEVICE_LIST;

extern INT32 bt_app_get_latest_paired_src_device(BT_TARGET_DEV_INFO *pt_device);
extern INT32 bt_app_get_latest_paired_sink_device(BT_TARGET_DEV_INFO *pt_device);
extern INT32 bt_app_set_rssi_map_table(INT32 ai4_rssi_map_table[], UINT8 ui1_len);
extern INT32 bt_app_get_rssi_map_table(INT32 *pi4_rssi_map_table);
extern INT32 bt_app_get_src_rssi_level(UINT8 *pui1_rssi_level);
extern VOID  bt_app_insert_a2dp_snk_dev(BT_APP_REMOTE_DEV_T* pt_a2dp_snk_dev);
extern UINT32 bt_app_get_a2dp_snk_dev_num(VOID);
extern UINT32 bt_app_get_all_a2dp_snk_devs(BT_APP_REMOTE_DEV_T *pt_devs, UINT32 ui4_num);
extern INT32 bt_app_start_a2dp_snk_inquiry_scan(UINT32 time_out);
extern INT32 bt_app_stop_a2dp_snk_inquiry_scan(VOID);
extern INT32 _bt_app_init_a2dp_snk_dev_list(VOID);
extern INT32 _bt_app_free_a2dp_snk_dev_list(VOID);
extern VOID bt_app_set_pts_enable(BOOL flag);
extern INT32 bt_app_remove_one_from_dev_list(char* bt_addr);

#endif
#endif

