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
 * $RCSfile: network.h,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 40bc7a05c376b5fe4913d179a321d474 $
 *
 * Description:
 *      This file is the internal header file for APP NETWORK
 *---------------------------------------------------------------------------*/
#ifdef APP_NETWORK_SUPPORT

#ifndef _NETWORK_H_
#define _NETWORK_H_

#include "app_util/a_common.h"
#include "app_util/a_network.h"

#ifdef APP_NETWORK_WIFI_SUPPORT
#include "c_net_wlan_ctl.h"
#endif

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
/* Debug */
#undef DBG_INIT_LEVEL
#ifdef DBG_INIT_LEVEL_APP_NETWORK
    #define DBG_INIT_LEVEL              DBG_INIT_LEVEL_APP_NETWORK
#else
    #define DBG_INIT_LEVEL              DBG_LEVEL_NONE
#endif

#ifdef DBG_LEVEL_MODULE
#undef DBG_LEVEL_MODULE
#endif
#define DBG_LEVEL_MODULE                nw_get_dbg_level()

#ifdef DBG_MODULE_NAME_PREFIX
#undef DBG_MODULE_NAME_PREFIX
#endif
#define DBG_MODULE_NAME_PREFIX    nw_get_log_prefix()
/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/
/* Return on error */
#define NW_CHK_FAIL(_ret)  \
do{ \
    if (_ret < 0)   \
    {   \
        DBG_ERROR(("[NW] Return fail:%s:%s:%d:%d\r\n", __FILE__, __FUNCTION__, __LINE__, _ret)); \
        return _ret;  \
    }   \
}while(FALSE)

#define NW_CHK_FAIL_VOID(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_ERROR(("[NW] Return fail:%s:%s:%d:%d\r\n", __FILE__, __FUNCTION__, __LINE__, _ret)); \
    return ;  \
}   \
}while(FALSE)

#define NW_LOG_ON_FAIL(_ret)  \
do{ \
    if (_ret < 0)   \
    {   \
        DBG_ERROR(("[NW] Return fail:%s:%s:%d:%d\r\n", __FILE__, __FUNCTION__, __LINE__, _ret)); \
    }   \
}while(FALSE)

#define NW_BREAK_ON_FAIL(_ret)  \
if (_ret < 0)   \
{   \
    DBG_ERROR(("[NW] Return fail:%s:%s:%d:%d\r\n", __FILE__, __FUNCTION__, __LINE__, _ret)); \
    break;  \
}

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/
#define NW_MAX_NUM_NOTIFY_CLIENT                (16)
/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/
/**
 * @brief This structure declares the network monitor info.
 */
typedef struct _MW_UTIL_NFY_CLIENT_T
{
    nw_nfy_fct               pf_notify;
    VOID*                    pv_tag;
    UINT32                   ui4_nfy_id;
} MW_UTIL_NFY_CLIENT_T;
/**
 * @brief This structure declares the network internal message.
 */
typedef struct
{
    NW_NFY_ID_T    e_msg_id;       /**< The message ID. */
    VOID*          pv_nfy_param;    /**< Message specific data. */
} MW_UTIL_MSG_T;

#ifdef APP_NETWORK_WIFI_SUPPORT

/**
 * @brief This structure stores wlan notify data.
 */
typedef struct _NW_WLAN_NTY_T
{
    INT32 i4_msg_id;

    INT32 i4_data;

}NW_WLAN_NTY_T;

#endif





/**
 * @brief This structure declares the network util info.
 */
typedef struct _NW_UTIL_T
{
    BOOL                   b_nw_enabled;            /**< Determine the Network Connection. */
    BOOL                   b_nw_ethernet_plugin;    /*< Determine the Ethernet is plugin. */

    NW_DHCP_STATE_T 	   e_dhcp_state;	        /**< Determine the DHCP state. */
    //TODO: for ethernet and wifi

#ifdef APP_DMS_SUPPORT
    NW_DLNA_DMS_STATE_T        e_dlna_dms_state;    /**< Determine the DLNA state. */
#endif

#ifdef APP_NET_DLNA_SUPPORT
    NW_DLNA_STATE_T        e_dlna_state;            /**< Determine the DLNA state. */
#endif

#ifdef APP_DMR_SUPPORT
    NW_DLNA_DMR_STATE_T    e_dlna_dmr_state;        /**< Determine the DLNA DMR state. */
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    NW_MY_NET_PLS_STATE_T  e_my_net_pls_state;      /**< Determine the My Network Places state. */
#endif

    HANDLE_T               h_api_mtx;               /**< API mutex. */
    CHAR*                  s_test_hostname;

#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
    UINT8                  ui1_interface;           /*< Determine current network interface. */
	UINT8				   ui1_old_interface;		/*< Determine last network interface. */
    NW_WLAN_STATE_T        e_wlan_status;           /*< Determine  Associate with a wireless network for support the single dongle system. */

    NW_WLAN_STATE_T        e_built_in_wlan_status;  /*< Determine built-in dongle Associate with a wireless network. */
    NW_WLAN_STATE_T        e_out_wlan_status;       /*< Determine out dongle Associate with a wireless network. */
#else
	BOOL                   b_wlan_started;
   UINT8                   ui1_interface;           /*< Determine current network interface. */
   UINT8                   ui1_old_interface;       /*< Determine last network interface. */
   NW_WLAN_STATE_T         e_wlan_status;
#endif     /*< Determine Associate with a wireless network. */
	BOOL                   b_wlan_drv_init;

#endif

    MW_UTIL_NFY_CLIENT_T   at_notify_client[NW_MAX_NUM_NOTIFY_CLIENT];/**< Array list of the notify functions. */

}NW_UTIL_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
-----------------------------------------------------------------------------*/
extern VOID    nw_set_dbg_level(UINT16 ui2_dbg_level);
extern UINT16  nw_get_dbg_level(VOID);
extern CHAR* nw_get_log_prefix(VOID);
extern INT32   nw_cli_init(VOID);

#endif /* _NETWORK_H_ */

#endif /* APP_NETWORK_SUPPORT */

