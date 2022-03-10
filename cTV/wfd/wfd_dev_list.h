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
 * $RCSfile: rmv_dev_rc.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision:  $
 * $SWAuthor:  $
 * $MD5HEX:  $
 *
 * Description: 
 *         This header file contains public interfaces, constant and type 
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/
 
#ifndef _WFD_DEV_LIST_H_
#define _WFD_DEV_LIST_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_dm.h"
#include "c_os.h"
#include "c_dbg.h"
#include "agent/a_agent.h"
#include "u_common.h"
#include "wfd.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define DEVICE_INFO_MAX_STORE_NUM       (50)
#define DEVICE_INFO_MAX_NAME_LEN        (20)
#define DEVICE_INFO_MAX_MAC_LEN         (20)
#define DEVICE_INFO_MAX_TYPE_LEN        (20)
#define NAV_WFD_P2P_MAX_DEVICE_INFO_LEN (20)
#define NAV_WFD_P2P_MAX_DEVICE_NUM      (40)
#define DEVICE_INFO_LIST_HEADER         (0)

typedef enum _WFD_DEVICE_INFO_ID_T
{
    GET_WFD_DEVICE_INFO_ID_NAME = 0,            
    GET_WFD_DEVICE_INFO_ID_MAC,            
    GET_WFD_DEVICE_INFO_ID_TYPE,
    GET_WFD_DEVICE_INFO_ID_PERMISSION,
    GET_WFD_DEVICE_INFO_ID_VARY_INDEX,
    GET_WFD_DEVICE_INFO_ID_ALL
} WFD_DEVICE_INFO_ID_T;

typedef enum
{
    E_WFD_DEVICE_PERMISSION_ACCEPT = 0,
    E_WFD_DEVICE_PERMISSION_DECLINE
    
}WFD_DEVICE_PERMISSION_T;

typedef struct _NAV_WFD_DEVICE_INFO_T
{
    UINT8   ui1_index;
    char    s_device_name[DEVICE_INFO_MAX_NAME_LEN]; 
    char    s_device_mac[DEVICE_INFO_MAX_MAC_LEN]; 
    char    s_device_type[DEVICE_INFO_MAX_TYPE_LEN]; 
    WFD_DEVICE_PERMISSION_T e_permission;
    UINT32                  ui4_disconnect_time;

}NAV_WFD_DEVICE_INFO_T;

/*-----------------------------------------------------------------------------
                    functions
 ----------------------------------------------------------------------------*/
extern BOOL  a_wfd_device_info_is_device_register(CHAR * ps_mac_address, UINT32  ui4_mac_len);

extern INT32 a_wfd_device_info_load_list(VOID);

extern INT32 a_wfd_device_info_save_list(VOID);

extern INT32 a_wfd_device_info_show_list(VOID);

extern INT32 a_wfd_device_info_delete_all(VOID);

extern INT32 a_wfd_device_info_delete_by_mac(CHAR * ps_mac_address);

extern INT32 a_wfd_device_info_delete_by_index(UINT8 ui1_index);

extern INT32 a_wfd_device_info_get_device_count(UINT8	* ui1_amount);

extern INT32 a_wfd_device_info_get_accept_device_count(UINT8  * pui1_amount);

extern INT32 a_wfd_device_info_get_decline_device_count(UINT8  * pui1_amount);

extern INT32 a_wfd_device_info_get_device_index(UINT8 * pui1_index,  CHAR * ps_mac_address);

extern INT32 a_wfd_device_info_get_device_info_by_mac(CHAR * ps_mac_address, NAV_WFD_DEVICE_INFO_T * pt_device_info);

extern INT32 a_wfd_device_info_get_device_info_by_index(INT32  ui4_index,  NAV_WFD_DEVICE_INFO_T * pt_device_info);

extern INT32 a_wfd_device_info_set_device_info(UINT8  ui1_index, WFD_DEVICE_INFO_ID_T e_info_id, SIZE_T* pz_size, VOID* pv_param);

extern INT32 a_wfd_device_info_get_longest_disconnect_device(UINT8  * pui1_index, WFD_DEVICE_PERMISSION_T e_permission_id);

extern INT32 a_wfd_device_info_add_device(NAV_WFD_DEVICE_INFO_T * pt_device_info);

extern INT32 a_wfd_device_info_init(VOID);

extern INT32 a_wfd_device_info_update_disconnect_time(CHAR * ps_mac_address);

extern BOOL  a_wfd_device_info_is_device_connected(CHAR * ps_mac_address);

extern INT32 a_wfd_device_info_unpair_device(UINT8 ui1_index);

extern INT32 a_wfd_device_info_store_new_device(WFD_DEVICE_INFO_T* pt_info);

#endif /*_WFD_DEV_LIST_H_*/

