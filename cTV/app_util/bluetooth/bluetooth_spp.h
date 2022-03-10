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
 * $RCSfile: bluetooth_spp.h,v $
 * $Revision: #1 $
 * $Date: 2015/10/17 $
 * $Author: jingjing.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *      This file is the internal header file for bluetooth spp.
 *---------------------------------------------------------------------------*/

#ifdef APP_BLUETOOTH_SUPPORT

#ifndef _BLUETOOTH_SPP_H_
#define _BLUETOOTH_SPP_H_

#include "u_common.h"
#include "u_bt_mw_spp.h"

//#include "c_bt_mw_manager.h"


#define SPP_UUID_LENGTH 64
#define MAX_SPP_DATA_LENGTH_APP 128    // The max data length that APP can receive once.
typedef struct _BT_SPP_RECEIVED_DATA         // the structure for received data via SPP
{
    CHAR   ac_uuid[SPP_UUID_LENGTH];           // which uuid this data is received from
    UINT8  aui1_data[MAX_SPP_DATA_LENGTH_APP]; // SPP data
    UINT32 ui4_data_len;                       // data length
}BT_SPP_RECEIVED_DATA;


/* For iplib */

#define MAX_IPLIB_INFO_LENGTH   16
typedef enum _BT_APP_IPLIB_INFO_TYPE_E
{
    IPLIB_FW_VERSION        = 0,
    IPLIB_HW_VERSION        = 1,
    IPLIB_ACCESSARY_NAME    = 2,
    IPLIB_INFO_MAX,
}BT_APP_IPLIB_INFO_TYPE_E;

typedef struct _BT_APP_IPLIB_INFO_T
{
    BT_APP_IPLIB_INFO_TYPE_E    e_iplib_info_type;
    char                        ac_iplibinfo[MAX_IPLIB_INFO_LENGTH];
} BT_APP_IPLIB_INFO_T;


extern INT32 bt_spp_connect_with_uuid_proc(CHAR* uuid);
extern VOID  bt_spp_disconnect_all_req(VOID);
extern VOID  bt_spp_event_nfy_proc(BT_SPP_EVENT bt_spp_event_type, VOID *pv_data);
extern INT32 bt_spp_sema_create(VOID);
extern VOID  bt_spp_data_buf_lock(VOID);
extern VOID  bt_spp_data_buf_unlock(VOID);
extern VOID  bt_spp_show_spp_data_buf(VOID);
extern VOID  bt_spp_enable_data_log(BOOL f_enable_data_log);
extern INT32 bt_spp_disconnect_with_uuid_proc(CHAR* uuid);
unsigned char checksum(unsigned char *buf, int size);
int app_spp_send_mute(void);
int app_spp_send_vol_down(void);
int app_spp_send_vol_up(void);
int app_spp_send_force_pairing(void);
int app_spp_send_get_pairing_status(void);
int app_spp_send_get_supported_api(void);
int app_spp_send_set_panasonic_tv_buffering(void);
int app_spp_check_ret_supported_api(UINT8 *buf, UINT32 len);
int app_spp_check_get_pairing_status_data(UINT8 *buf, UINT32 len);
int app_spp_check_ret_panasonic_tv_buffering(UINT8 *buf, UINT32 len);
int app_spp_check_ret_supported_api_buffering(UINT8 *buf, UINT32 len);

#endif
#endif

