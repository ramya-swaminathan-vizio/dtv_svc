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
 * $RCSfile: network_custom.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/**
 * @file network.c
 *
 * @brief This file implements the custom part API of network.
 *
 * @author
 */
#ifdef APP_NETWORK_SUPPORT

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "c_os.h"
#include "c_net_config.h"
#include "u_dhcpc_api.h"
#include "u_net_common.h"
#include "u_net_ni_if.h"
#include "u_net_oid.h"
#include "u_net_socket.h"
#include "c_net_socket.h"
#include "c_net_p2p_ctl.h"
#ifdef APP_WFD_SUPPORT
#include "wfd_client_export.h"
#endif

#include "agent/agent.h"
#include "wizard_anim/a_wzd.h"
#include "app_util/a_tv.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_network.h"
#include "app_util/network/network.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "rest/a_rest_event.h"
#include "rest/a_rest_api.h"

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdlib.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <string.h>
#include <errno.h>
#endif

extern int close (int __fd);

#if 1
char * wifi_ifname = NULL;//haifei add for support multi dongle.

#define WIFI_DEV_NUM 4

char * if_name_dev[WIFI_DEV_NUM]={"wifi0","rea0","ra0",NULL};
#endif

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/
/**
 * @brief This structure declares the network util custom info.
 */
typedef struct _NW_UTIL_CUSTOM_T
{
    NW_UTIL_T*             pt_nw;
    BOOL                   b_interface_chg_disable;
    DOUBLE                 u4_nw_speed;
    UINT32                 ui4_nw_nfy_id;
}NW_UTIL_CUSTOM_T;

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/
NW_UTIL_CUSTOM_T    t_nw_util_custom = {0};

/*-----------------------------------------------------------------------------
                    private function implementations
-----------------------------------------------------------------------------*/
static INT32 _nw_custom_notify_connection_status(BOOL b_connect)
{
    if (b_connect)
    {
        DBG_LOG_PRINT(("[Jundi][%s %d]notify network status:connected\n",__FUNCTION__,__LINE__));
        rest_event_notify("tv_settings/network/connection_status", 1, "Connected");

        BOOL b_accept = TRUE;
        //if (TRUE == a_tv_custom_get_viewing_data_show() &&
        if(TVR_OK == a_tv_custom_get_http_url_status(&b_accept))
        {
            a_nw_custom_get_http_url_for_acr(b_accept);
        }
    }
    else
    {
        DBG_LOG_PRINT(("[Jundi][%s %d]notify network_status :disconnected\n",__FUNCTION__,__LINE__));
        rest_event_notify("tv_settings/network/connection_status", 0, "");
    }
    return NWR_OK;
}

static BOOL _nw_custom_check_connection_status(VOID)
{
    BOOL            b_connected  = FALSE;
    BOOL            b_dhcp       = FALSE;
    NW_DHCP_STATE_T e_dhcp_state = NW_DHCP_FAILED;

    nw_custom_get_auto_ip_config(&b_dhcp);
    if (!b_dhcp)
    {
        b_connected = TRUE;
    }
    else
    {
        a_nw_get_dhcp_status(&e_dhcp_state);
        if ((NW_DHCP_STARTED == e_dhcp_state))
        {
            b_connected = TRUE;
        }
    }
    DBG_LOG_PRINT(("[NW][%s][%d] Enter,b_connected=%d\n", __FUNCTION__, b_connected));
    return b_connected;
}

static INT32 _nw_custom_update_tv_network_info(VOID)
{
    INT32 i4_ret = NWR_OK;
    INT32 i = 0;

    BOOL            b_is_plug    = FALSE;
    i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
    NW_CHK_FAIL(i4_ret);

    if (b_is_plug)
    {
        return _nw_custom_notify_connection_status(_nw_custom_check_connection_status());
    }

 #ifdef APP_NETWORK_WIFI_SUPPORT
    NW_WLAN_STATE_T e_wlan_state = NW_WLAN_UNPLUG;
    a_nw_wlan_status(&e_wlan_state);
    if (e_wlan_state == NW_WLAN_ASSOCIATE)
    {
        NET_802_11_BSS_INFO_T   t_bss_info;
        c_memset (&t_bss_info, 0, sizeof(t_bss_info));
        i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
        if(i4_ret != NWR_OK)
        {
            while(i++<5)
               {
                    c_thread_delay(100);
                    i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
                   if(i4_ret == NWR_OK)
                   {
                        DBG_LOG_PRINT(("[NW][%s][%d] fail\n", __FUNCTION__, __LINE__));
                        break;
                   }
               }
            if(i>= 5)
            {
                c_memset(t_bss_info.t_Bssid, 0, sizeof(t_bss_info.t_Bssid));
                t_bss_info.t_Ssid.ui4_SsidLen = 0;
                NW_LOG_ON_FAIL(i4_ret);
            }
        }

        if ((t_bss_info.t_Ssid.ui4_SsidLen > 0)/*wifi has been connected*/
            &&((UINT8)WLAN_WPA_COMPLETED == t_bss_info.u8_wpa_status))
        {
            DBG_LOG_PRINT(("[Jundi][NW][%s][%d]wifi has been connected \n", __FUNCTION__, __LINE__));
            //return _nw_custom_notify_connection_status(_nw_custom_check_connection_status());
            return _nw_custom_notify_connection_status(TRUE);
        }
    }
 #endif
    DBG_LOG_PRINT(("[Jundi][NW][%s][%d] end \n", __FUNCTION__, __LINE__));

    return _nw_custom_notify_connection_status(FALSE);
}

/*----------------------------------------------------------------------------
 * Name: _nw_custom_notify_handler
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nw_custom_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    NW_NFY_ID_T e_nfy_id = *((NW_NFY_ID_T*)pv_data);
    DBG_LOG_PRINT(("[Jundi][%s %d]e_nfy_id : %d\n",__FUNCTION__,__LINE__,e_nfy_id));

    if(NW_NFY_ID_DHCP_SUCCESS_DHCPv4 == e_nfy_id ||
       NW_NFY_ID_WLAN_ASSOCIATE == e_nfy_id)
    {
        _nw_custom_update_tv_network_info();
        return;/* no need set network interface */
    }

    if(NW_NFY_ID_ETHERNET_UNPLUG == e_nfy_id)
    {
        _nw_custom_notify_connection_status(FALSE);
    }
#ifdef NEVER
    if (NW_NFY_ID_DHCP_SUCCESS_DHCPv4 == e_nfy_id
#ifdef APP_NETWORK_WIFI_SUPPORT
        || NW_NFY_ID_WLAN_ASSOCIATE == e_nfy_id
#endif
        )
    {
        return; /* no need set network interface */
    }
#endif

    if(t_nw_util_custom.b_interface_chg_disable)
    {
        return;
    }

#ifdef APP_NETWORK_WIFI_SUPPORT
    UINT8    ui1_new_interface = NW_NET_INTERFACE_ETH0;

    if(e_nfy_id == NW_NFY_ID_ETHERNET_UNPLUG)
    {
        a_tv_custom_set_conn_type(FALSE);
        ui1_new_interface = NW_NET_INTERFACE_WIFI;
    }
    else
    {
        a_tv_custom_set_conn_type(TRUE);
        ui1_new_interface = NW_NET_INTERFACE_ETH0;
    }

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, ui1_new_interface: %d\n", __FUNCTION__, __LINE__, ui1_new_interface));

    a_nw_chg_network_interface(ui1_new_interface);
#endif
    return;
}
/*----------------------------------------------------------------------------
 * Name: _nw_notify_callback
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _nw_custom_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    switch(e_nfy_id)
    {
    case NW_NFY_ID_ETHERNET_UNPLUG:
        DBG_LOG_PRINT(("[Jundi][%s %d]NW_NFY_ID_ETHERNET_UNPLUG\n",__FUNCTION__,__LINE__));
        break;
    case NW_NFY_ID_ETHERNET_PLUGIN:
        DBG_LOG_PRINT(("[Jundi][%s %d]NW_NFY_ID_ETHERNET_PLUGIN\n",__FUNCTION__,__LINE__));
        break;
    case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
        DBG_LOG_PRINT(("[Jundi][%s %d]NW_NFY_ID_DHCP_SUCCESS_DHCPv4\n",__FUNCTION__,__LINE__));
        break;
#ifdef APP_NETWORK_WIFI_SUPPORT
    case NW_NFY_ID_WLAN_ASSOCIATE:
#endif
    {
        DBG_LOG_PRINT(("[Jundi][%s %d]NW_NFY_ID_WLAN_ASSOCIATE\n",__FUNCTION__,__LINE__));
        break;
    }

    default:
        return;
    }


    a_agent_async_invoke( _nw_custom_notify_handler,
                         (VOID*)&e_nfy_id,
                         sizeof(NW_NFY_ID_T)
                         );

}

/**
 * @brief   _nw_custom_update_interface.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
VOID _nw_custom_update_interface(VOID)
{
#ifdef APP_NETWORK_WIFI_SUPPORT
    BOOL  b_eth_plug = FALSE;

    UINT8    ui1_cur_interface = NW_NET_INTERFACE_ETH0;
    UINT8    ui1_new_interface = NW_NET_INTERFACE_ETH0;

    nw_custom_get_network_interface(&ui1_cur_interface);

    a_nw_get_ethernet_connect_info(&b_eth_plug);

    if(b_eth_plug)
    {
        ui1_new_interface = APP_CFG_NET_INTERFACE_ETH0;
    }
    else
    {
        ui1_new_interface = APP_CFG_NET_INTERFACE_WIFI;
    }

    if(ui1_new_interface != ui1_cur_interface)
    {
        DBG_LOG_PRINT(("\n<Network> --- %s, %d. ---\n", __FUNCTION__, __LINE__));
        a_nw_chg_network_interface(ui1_new_interface);
    }
#endif
}
/*-----------------------------------------------------------------------------
 *                  public methods implementations
 *---------------------------------------------------------------------------*/
/**
 * @brief   Set the network enable config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_network_enable(BOOL b_enable)
{
    INT32    i4_ret = 0;

    i4_ret = a_cfg_set_network_enable(b_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
}
/**
 * @brief   Get the network enable config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_network_enable(BOOL* pb_enable)
{
    INT32    i4_ret = 0;

    i4_ret = a_cfg_get_network_enable(pb_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
}

#ifdef APP_NET_DLNA_SUPPORT
/**
 * @brief   Set the DLNA enable config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_dlna_enable(BOOL b_enable)
{
    INT32    i4_ret = 0;

    i4_ret = a_cfg_set_DLNA_enable(b_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
}
/**
 * @brief   Get the DLNA enable config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_dlna_enable(BOOL* pb_enable)
{
    INT32    i4_ret = 0;

    i4_ret = a_cfg_get_DLNA_enable(pb_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
}

#ifdef APP_DMR_SUPPORT
/**
 * @brief   Set the DLNA DMR enable config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_dlna_dmr_enable(BOOL b_enable)
{
    INT32    i4_ret = 0;

    i4_ret = a_cfg_set_DLNA_DMR_enable(b_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
}

/**
 * @brief   Get the DLNA DMR enable config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_dlna_dmr_enable(BOOL* pb_enable)
{
#if 0
    /* for disable DMR feature manually */
    *pb_enable = 0;
#else
    INT32    i4_ret = 0;

    i4_ret = a_cfg_get_DLNA_DMR_enable(pb_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }
#endif

    return NWR_OK;
}
#endif
#endif

/**
 * @brief   Set the network IP is auto(DHCP) config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_auto_ip_config(BOOL b_enable)
{
    INT32       i4_ret = 0;
    UINT32      ui1_idx = 0;
    BOOL        b_is_plug = FALSE;

    i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
    NW_CHK_FAIL(i4_ret);

    if (b_is_plug)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_set_auto_ip_config(b_enable, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}
/**
 * @brief   Get the network IP is auto(DHCP) config
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_auto_ip_config(BOOL* pb_enable)
{
    INT32       i4_ret = 0;
    UINT32      ui1_idx = 0;
    BOOL        b_is_plug = FALSE;

    i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
    NW_CHK_FAIL(i4_ret);

    if (b_is_plug)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_get_auto_ip_config(pb_enable, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   Set the network DHCP settings.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_dhcp_status(UINT8 ui1_dhcp_status)
{
    INT32       i4_ret = 0;
    UINT32      ui1_idx = 0;
    BOOL        b_is_plug = FALSE;

    i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
    NW_CHK_FAIL(i4_ret);

    if (b_is_plug)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_set_dhcp_status(ui1_dhcp_status, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}
/**
 * @brief   Get the network DHCP settings.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_dhcp_status(UINT8* pui1_dhcp_status)
{
    INT32       i4_ret = 0;
    UINT32      ui1_idx = 0;
    BOOL        b_is_plug = FALSE;

    i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
    NW_CHK_FAIL(i4_ret);

    if (b_is_plug)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_get_dhcp_status(pui1_dhcp_status, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   Set the network IP config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_ip_addr_config(const NW_IP_INFO_T* pt_ip_info)
{
    INT32       i4_ret = 0;
    UINT8       ui1_idx = 0;
    UINT8       ui1_interface;

    i4_ret = nw_custom_get_network_interface(&ui1_interface);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    if (NW_NET_INTERFACE_ETH0 == ui1_interface)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_set_ip_addr(pt_ip_info->ui4_address, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_subnet_mask(pt_ip_info->ui4_netmask, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_default_gateway(pt_ip_info->ui4_gw, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_1st_dns(pt_ip_info->ui4_1st_dns, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_2nd_dns(pt_ip_info->ui4_2nd_dns, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}
/**
 * @brief   Set the network IP config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_ip_addr_config(NW_IP_INFO_T* pt_ip_info)
{
    INT32       i4_ret = 0;
    UINT32      ui1_idx = 0;
	BOOL        b_is_plug = FALSE;

	i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
	if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

	if (b_is_plug)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_get_ip_addr(&pt_ip_info->ui4_address, ui1_idx);
    NW_CHK_FAIL(i4_ret);

#if 0
    DBG_LOG_PRINT(("\n[NW]%s,%d,ui4_address=%x,ui1_idx=%d\n",
               __FUNCTION__, __LINE__,
               pt_ip_info->ui4_address, ui1_idx));
#endif

    i4_ret = a_cfg_custom_get_subnet_mask(&pt_ip_info->ui4_netmask, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_default_gateway(&pt_ip_info->ui4_gw, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_1st_dns(&pt_ip_info->ui4_1st_dns, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_2nd_dns(&pt_ip_info->ui4_2nd_dns, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   Set the network IP is auto(DHCP) config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_set_auto_ip_config_by_iface(BOOL b_enable, const UINT8 ui1_iface)
{
    INT32       i4_ret = 0;
    UINT8       ui1_idx = 0;

    if (NW_NET_INTERFACE_ETH0 == ui1_iface)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_set_auto_ip_config(b_enable, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   Get the network IP is auto(DHCP) config
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_get_auto_ip_config_by_iface(BOOL* pb_enable, const UINT8 ui1_iface)
{
    INT32       i4_ret = 0;
    UINT8       ui1_idx = 0;

    if (NW_NET_INTERFACE_ETH0 == ui1_iface)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_get_auto_ip_config(pb_enable, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   Set the network DHCP settings.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_set_dhcp_status_by_iface(UINT8 ui1_dhcp_status, const UINT8 ui1_iface)
{
    INT32       i4_ret = 0;
    UINT8       ui1_idx = 0;

    if (NW_NET_INTERFACE_ETH0 == ui1_iface)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_set_dhcp_status(ui1_dhcp_status, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   Get the network DHCP settings.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_get_dhcp_status_by_iface(UINT8* pui1_dhcp_status, const UINT8 ui1_iface)
{
    INT32       i4_ret = 0;
    UINT8       ui1_idx = 0;

    if (NW_NET_INTERFACE_ETH0 == ui1_iface)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    i4_ret = a_cfg_custom_get_dhcp_status(pui1_dhcp_status, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   Set the network IP config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_ip_addr_config_by_iface(const NW_IP_INFO_T* pt_ip_info, const UINT8 ui1_iface)
{
    INT32       i4_ret = 0;
    UINT8       ui1_idx = 0;

    if (NW_NET_INTERFACE_ETH0 == ui1_iface)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, ui1_idx: %u\n", __FUNCTION__, __LINE__, ui1_idx));

    i4_ret = a_cfg_custom_set_ip_addr(pt_ip_info->ui4_address, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_subnet_mask(pt_ip_info->ui4_netmask, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_default_gateway(pt_ip_info->ui4_gw, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_1st_dns(pt_ip_info->ui4_1st_dns, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_set_2nd_dns(pt_ip_info->ui4_2nd_dns, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}
/**
 * @brief   Set the network IP config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_ip_addr_config_by_iface(NW_IP_INFO_T* pt_ip_info, const UINT8 ui1_iface)
{
    INT32       i4_ret = 0;
    UINT32      ui1_idx = 0;

    if (NW_NET_INTERFACE_ETH0 == ui1_iface)
    {
        ui1_idx = 0;
    }
    else
    {
        ui1_idx = 1;
    }

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, ui1_idx: %u\n", __FUNCTION__, __LINE__, ui1_idx));

    i4_ret = a_cfg_custom_get_ip_addr(&pt_ip_info->ui4_address, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_subnet_mask(&pt_ip_info->ui4_netmask, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_default_gateway(&pt_ip_info->ui4_gw, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_1st_dns(&pt_ip_info->ui4_1st_dns, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_2nd_dns(&pt_ip_info->ui4_2nd_dns, ui1_idx);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

#ifdef APP_NET_NEIGHBOR_SUPPORT

/**
 * @brief   Set the net my_net_pls enable config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_my_net_pls_enable(BOOL b_enable)
{
    INT32    i4_ret = 0;

    i4_ret = a_cfg_set_my_net_pls_enable(b_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
}
/**
 * @brief   Get the net my_net_pls enable config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_my_net_pls_enable(BOOL* pb_enable)
{
    INT32    i4_ret = 0;

    i4_ret = a_cfg_get_my_net_pls_enable(pb_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
}

#endif

#ifdef APP_NETWORK_WIFI_SUPPORT
/**
 * @brief   Set the network interface.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_set_network_interface(UINT8 ui1_interface)
{
    INT32    i4_ret = 0;

    /* reset speed value */
    nw_custom_set_speed(0);

#if 0
    DBG_LOG_PRINT(("\n<lin.xu>%s,%d,ui1_interface=%d\n",
                   __FUNCTION__, __LINE__,
                   ui1_interface));
#endif

    ui1_interface = ui1_interface== NW_NET_INTERFACE_ETH0?
                    APP_CFG_NET_INTERFACE_ETH0 : APP_CFG_NET_INTERFACE_WIFI;

    i4_ret = a_cfg_set_network_interface(ui1_interface);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
}
/**
 * @brief   Get the network interface.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   nw_custom_get_network_interface(UINT8* pui1_interface)
{
    INT32    i4_ret = 0;

    i4_ret = a_cfg_get_network_interface(pui1_interface);
    DBG_LOG_PRINT(("\n<Network>---%s,%d, i4_ret=%d. ---\n", __FUNCTION__, __LINE__, i4_ret));
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    *pui1_interface = *pui1_interface== APP_CFG_NET_INTERFACE_ETH0?
                      NW_NET_INTERFACE_ETH0 : NW_NET_INTERFACE_WIFI;

#if 0
    DBG_LOG_PRINT(("\n[NW]%s,%d,*pui1_interface=%d\n",
                   __FUNCTION__, __LINE__,
                   *pui1_interface));
#endif

    return NWR_OK;
}
/**
 * @brief   Set current Bssid.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_set_wlan_bssid(NET_802_11_BSSID_T*          pt_Bssid)
{
    if (pt_Bssid == NULL)
    {
        return NWR_INV_ARG;
    }

    return a_cfg_set_wlan_bssid((UINT8*)pt_Bssid);
}
/**
 * @brief   Get current Bssid.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */

INT32 nw_custom_get_wlan_bssid(NET_802_11_BSSID_T*          pt_Bssid)
{
    if (pt_Bssid == NULL)
    {
        return NWR_INV_ARG;
    }

    return a_cfg_get_wlan_bssid((UINT8*)pt_Bssid);
}
/**
 * @brief   Set current Ssid.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */

INT32 nw_custom_set_wlan_ssid(NET_802_11_SSID_T*           pt_Ssid)
{
    if (pt_Ssid == NULL)
    {
        return NWR_INV_ARG;
    }

    if (pt_Ssid->ui4_SsidLen< NET_802_11_MAX_LEN_SSID)
    {
        pt_Ssid->ui1_aSsid[pt_Ssid->ui4_SsidLen] = '\0';
    }
    else if (pt_Ssid->ui4_SsidLen > NET_802_11_MAX_LEN_SSID)
    {
        return NWR_INV_ARG;
    }

    return a_cfg_set_wlan_ssid((UINT8*)pt_Ssid->ui1_aSsid);
}
/**
 * @brief   Get current Ssid.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */

INT32 nw_custom_get_wlan_ssid(NET_802_11_SSID_T*           pt_Ssid)
{
    CHAR s_ssid[NET_802_11_MAX_LEN_SSID+1] = {0};
    INT32    i4_ret = 0;

    if (pt_Ssid == NULL)
    {
        return NWR_INV_ARG;
    }

    i4_ret = a_cfg_get_wlan_ssid((UINT8*)s_ssid);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    s_ssid[NET_802_11_MAX_LEN_SSID] = '\0';

    pt_Ssid->ui4_SsidLen = c_strlen(s_ssid);

    c_memcpy(pt_Ssid->ui1_aSsid, s_ssid, NET_802_11_MAX_LEN_SSID);

    return NWR_OK;
}
/**
 * @brief   Set current associate case.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */

INT32 nw_custom_set_wlan_assoc_case(NET_802_11_ASSOC_CASE_T     e_AssocCase)
{
    return a_cfg_set_wlan_assoc_case((UINT8)e_AssocCase);
}

/**
 * @brief   Get current associate case.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_get_wlan_assoc_case(NET_802_11_ASSOC_CASE_T*     pe_AssocCase)
{
    if (pe_AssocCase == NULL)
    {
        return NWR_INV_ARG;
    }

    return a_cfg_get_wlan_assoc_case((UINT8*)pe_AssocCase);
}
/**
 * @brief   Set current auth mdoe.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_set_wlan_auth_mode(NET_802_11_AUTH_MODE_T      e_AuthMode)
{
    return a_cfg_set_wlan_auth_mode((UINT8)e_AuthMode);
}
/**
 * @brief   Get current auth mode.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_get_wlan_auth_mode(NET_802_11_AUTH_MODE_T*      pe_AuthMode)
{
    if (pe_AuthMode == NULL)
    {
        return NWR_INV_ARG;
    }

    return a_cfg_get_wlan_auth_mode((UINT8*)pe_AuthMode);
}
/**
 * @brief   Set current auth cipher.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_set_wlan_auth_cipher(NET_802_11_AUTH_CIPHER_T    e_AuthCipher)
{
    return a_cfg_set_wlan_auth_cipher((UINT8)e_AuthCipher);
}
/**
 * @brief   Get current auth cipher.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_get_wlan_auth_cipher(NET_802_11_AUTH_CIPHER_T*    pe_AuthCipher)
{
    if (pe_AuthCipher == NULL)
    {
        return NWR_INV_ARG;
    }

    return a_cfg_get_wlan_auth_cipher((UINT8*)pe_AuthCipher);
}
/**
 * @brief   Set current auth key.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_set_wlan_key(NET_802_11_KEY_T*          pt_Key)
{
    if (pt_Key == NULL)
    {
        return NWR_INV_ARG;
    }

    if (pt_Key->pui1_PassPhrase == NULL)
    {
        return NWR_INV_ARG;
    }

    return a_cfg_set_wlan_key((UINT8*)pt_Key->pui1_PassPhrase);
}
/**
 * @brief   Get current auth key.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_get_wlan_key(NET_802_11_KEY_T*          pt_Key)
{
    if (pt_Key == NULL)
    {
        return NWR_INV_ARG;
    }

    if (pt_Key->pui1_PassPhrase == NULL)
    {
        return NWR_INV_ARG;
    }

    pt_Key->b_IsAscii = TRUE;

    return a_cfg_get_wlan_key((UINT8*)pt_Key->pui1_PassPhrase);
}

/**
 * @brief   Set current associate.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_set_associate(NET_802_11_ASSOCIATE_T *pAssociate)
{
    INT32    i4_ret = 0;

    /*BSSID*/
    i4_ret = a_cfg_set_wlan_bssid((UINT8*)pAssociate->t_Bssid);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_set_wlan_ssid((UINT8*)pAssociate->t_Ssid.ui1_aSsid);
    NW_CHK_FAIL(i4_ret);

    /*Auth Mode*/
    i4_ret = a_cfg_set_wlan_auth_mode((UINT8)pAssociate->e_AuthMode);
    NW_CHK_FAIL(i4_ret);

    /*Auth Cipher*/
    i4_ret = a_cfg_set_wlan_auth_cipher((UINT8)pAssociate->e_AuthCipher);
    NW_CHK_FAIL(i4_ret);

    /*key*/
    if (nw_custom_is_lock_ap(pAssociate->e_AuthMode,pAssociate->e_AuthCipher))
    {
        i4_ret = a_cfg_set_wlan_key((UINT8*)pAssociate->t_Key.pui1_PassPhrase);
        NW_CHK_FAIL(i4_ret);
    }

    return NWR_OK;
}
/**
 * @brief   Set current associate.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_get_associate(NET_802_11_ASSOCIATE_T *pAssociate)
{
    INT32    i4_ret = 0;
    CHAR s_ssid[NET_802_11_MAX_LEN_SSID+1] = {0};

    /*BSSID*/
    i4_ret = a_cfg_get_wlan_bssid((UINT8*)pAssociate->t_Bssid);
    NW_CHK_FAIL(i4_ret);

    {
        NET_802_11_BSSID_T                      t_Bssid;
        c_memset(t_Bssid, 0,sizeof(NET_802_11_BSSID_T));

        if (c_memcmp(pAssociate->t_Bssid,t_Bssid,sizeof(NET_802_11_BSSID_T)) != 0)
        {
            c_memset(pAssociate->t_Bssid, 0xff, sizeof(NET_802_11_BSSID_T));
        }
    }
    /*SSID*/
    i4_ret = a_cfg_get_wlan_ssid((UINT8*)s_ssid);
    NW_CHK_FAIL(i4_ret);

    s_ssid[NET_802_11_MAX_LEN_SSID] = '\0';

    pAssociate->t_Ssid.ui4_SsidLen = c_strlen(s_ssid);
    c_memcpy(pAssociate->t_Ssid.ui1_aSsid, s_ssid, NET_802_11_MAX_LEN_SSID);


    /*Auth Mode*/
    i4_ret = a_cfg_get_wlan_auth_mode((UINT8*)&pAssociate->e_AuthMode);
    NW_CHK_FAIL(i4_ret);

    /*Auth Cipher*/
    i4_ret = a_cfg_get_wlan_auth_cipher((UINT8*)&pAssociate->e_AuthCipher);
    NW_CHK_FAIL(i4_ret);

    /*key*/
    if (nw_custom_is_lock_ap(pAssociate->e_AuthMode,pAssociate->e_AuthCipher))
    {
        i4_ret = a_cfg_get_wlan_key((UINT8*)pAssociate->t_Key.pui1_PassPhrase);
        NW_CHK_FAIL(i4_ret);
    }

    pAssociate->t_Key.b_IsAscii = TRUE;

    switch(pAssociate->e_AuthMode)
    {
    case IEEE_802_11_AUTH_MODE_NONE:
    case IEEE_802_11_AUTH_MODE_OPEN:
    case IEEE_802_11_AUTH_MODE_WPA_OWE:
    case IEEE_802_11_AUTH_MODE_WPA2_OWE:
    case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE:
        break;
    case IEEE_802_11_AUTH_MODE_SHARED:
    case IEEE_802_11_AUTH_MODE_WEPAUTO:
    {   /*check wep input key*/

        UINT8 ui1_length = (UINT8)c_strlen(pAssociate->t_Key.pui1_PassPhrase);

        if(ui1_length == 10 || ui1_length == 26)
        {
            pAssociate->t_Key.b_IsAscii = FALSE;
        }

        break;
    }
    case IEEE_802_11_AUTH_MODE_WPA:
    case IEEE_802_11_AUTH_MODE_WPA_PSK:
    case IEEE_802_11_AUTH_MODE_WPA2:
    case IEEE_802_11_AUTH_MODE_WPA2_PSK:
    case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
    {   /*check wpa input key*/

        UINT8 ui1_length = (UINT8)c_strlen(pAssociate->t_Key.pui1_PassPhrase);

        if(ui1_length == 64)
        {
            pAssociate->t_Key.b_IsAscii = FALSE;
        }
        break;
    }
    default:
        break;
    }

    return NWR_OK;
}

BOOL nw_custom_is_lock_ap(NET_802_11_AUTH_MODE_T e_AuthMode, NET_802_11_AUTH_CIPHER_T e_AuthCipher)
{
    if ((e_AuthMode== IEEE_802_11_AUTH_MODE_NONE ||
         e_AuthMode == IEEE_802_11_AUTH_MODE_OPEN) &&
         e_AuthCipher == IEEE_802_11_AUTH_CIPHER_NONE)
    {
        return FALSE;
    }
    else if (e_AuthMode == IEEE_802_11_AUTH_MODE_WPA_OWE ||
             e_AuthMode == IEEE_802_11_AUTH_MODE_WPA2_OWE ||
             e_AuthMode == IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE)
    {
        return FALSE;
    }

    return TRUE;
}

#endif

/**
 * @brief   Network custom init.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_custom_init(NW_UTIL_T*    pt_nw)
{
    NW_UTIL_CUSTOM_T* pt_nw_custom =&t_nw_util_custom;

    pt_nw_custom->pt_nw = pt_nw;
    pt_nw_custom->b_interface_chg_disable = FALSE;

    if (!pt_nw_custom->b_interface_chg_disable)
    {
        if(pt_nw->b_nw_ethernet_plugin)
        {
            pt_nw->ui1_interface = APP_CFG_NET_INTERFACE_ETH0;
        }
        else
        {
            pt_nw->ui1_interface = APP_CFG_NET_INTERFACE_WIFI;
        }

        nw_custom_set_network_interface(pt_nw->ui1_interface);
    }

    DBG_LOG_PRINT(("\n%s,%s,%d,ui1_interface=%d\n",
               __FILE__, __FUNCTION__, __LINE__,
               pt_nw->ui1_interface));

    a_nw_register(_nw_custom_notify_callback, NULL, &pt_nw_custom->ui4_nw_nfy_id );

    return NWR_OK;
}
#endif /* APP_NETWORK_SUPPORT */
/**
 * @brief   a_nw_custom_disable_interface_change.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
VOID a_nw_custom_disable_interface_change(BOOL   b_disable)
{
    NW_UTIL_CUSTOM_T* pt_nw_custom =&t_nw_util_custom;

    if(pt_nw_custom->b_interface_chg_disable  == b_disable)
    {
        return;
    }

    pt_nw_custom->b_interface_chg_disable  = b_disable;

    if(!b_disable)
    {
        DBG_LOG_PRINT(("\n<Networ> --- %s, %d. ---\n", __FUNCTION__, __LINE__));
        _nw_custom_update_interface();
    }
}
/**
 * @brief   a_nw_custom_disable_interface_change.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
BOOL a_nw_custom_is_get_ip_addr(VOID)
{
    INT32         i4_ret            = 0;

    BOOL          b_network_enabled = FALSE;
    BOOL          b_auto_ip_config  = FALSE;
    NW_DHCP_STATE_T  e_dhcp_state = NW_DHCP_STOPPED;

    /*get the network info*/
    i4_ret = nw_custom_get_network_enable(&b_network_enabled);
    NW_LOG_ON_FAIL(i4_ret);

    if(b_network_enabled == FALSE)
    {
        return FALSE;
    }

    i4_ret = nw_custom_get_auto_ip_config(&b_auto_ip_config);
    NW_LOG_ON_FAIL(i4_ret);

    if(b_auto_ip_config)
    {
        i4_ret = a_nw_get_dhcp_status (&e_dhcp_state);
        NW_LOG_ON_FAIL(i4_ret);

        if (e_dhcp_state != NW_DHCP_STARTED && e_dhcp_state != NW_DHCP_STARTED_LOCAL)
        {
            return FALSE;
        }
    }

    return TRUE;
}

/******************************************************************************/
/**
 * @brief   This function is for setting network test speed
 *
 * @param   u4_speed network test speed
 * @retval  -
 */
/******************************************************************************/
VOID nw_custom_set_speed(DOUBLE u4_speed)
{
    t_nw_util_custom.u4_nw_speed = u4_speed;
}

/******************************************************************************/
/**
 * @brief   This function is for getting network test speed
 *
 * @param   -
 * @retval  network test speed
 */
/******************************************************************************/
DOUBLE nw_custom_get_speed(VOID)
{
    return t_nw_util_custom.u4_nw_speed;
}

INT32 a_nw_custom_get_ip_info(NW_IP_INFO_T *pt_ip_info)
{
    INT32   i4_ret          = NWR_OK;
    UINT16  ui2_status      = 0;
    UINT8   ui1_page_idx    = 0;

    if (NULL == pt_ip_info)
    {
        return NWR_INV_ARG;
    }

    NW_CHK_FAIL(a_cfg_get_wzd_status(&ui2_status));
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, WZD page index: %u\n", __FUNCTION__, __LINE__, ui1_page_idx));

    if (WZD_PAGE_INDEX_C4TV_CONNECT_WIFI == ui1_page_idx)
    {
        i4_ret = a_nw_get_ip_info(pt_ip_info, NI_WIRELESS_0);
        NW_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = a_nw_get_crnt_ip_info(pt_ip_info);
        NW_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

/******************************************************************************/
/**
 * @brief   This function is for test if one ip address is use by other TV
 *
 * @param
 * @retval  TRUE      this IP is existed in network;
 * @retval  FALSE     current IP is not existed in network ,can set it.
 */
/******************************************************************************/
extern BOOL a_nw_custom_is_IP_exist(UINT32     ui4_address)
{
    INT32       i4_ret;
    CHAR        s_interface_name[20];
    CHAR        s_tmp_str[32];
    CHAR        s_ping_str[64];
    BOOL        b_is_plug = FALSE;

    c_memset (s_interface_name,0, 20*sizeof(CHAR));
    c_memset (s_tmp_str, 0, sizeof(CHAR)*32);
    c_memset (s_ping_str, 0, sizeof(CHAR)*64);

    i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
	if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

	if (b_is_plug)
    {
        c_strncpy(s_interface_name, NI_ETHERNET_0, 19);
    }
    else    /* set wifi ip address*/
    {
        c_strncpy(s_interface_name, "wlan0", 19);
    }

    a_nw_ntoa(s_tmp_str, ui4_address);
    c_sprintf(s_ping_str, "arping -I %s -D %s -w 2", s_interface_name, s_tmp_str);

    DBG_LOG_PRINT(("\n---------%s, %s.-------\n", __FUNCTION__, s_ping_str));
    AP_SYSTEM_CALL_EX(s_ping_str,i4_ret);
    if (i4_ret != 0)
    {
        DBG_LOG_PRINT(("\n<%s> ----recevie reply,can NOT use this ip -------\n",__FUNCTION__));
        return TRUE;
    }
    else
    {
        DBG_LOG_PRINT(("\n<%s> ----no reply, can use this ip -------\n", __FUNCTION__));
        return FALSE;
    }

    return FALSE;
}

/******************************************************************************/
/**
 * @brief
 *
 * @param
 * @retval
 * @retval
 */
/******************************************************************************/
extern BOOL a_nw_custom_nw_wifi_start(VOID)
{

    INT32 i4_ret = NWR_OK;
    BOOL b_wifi_driver_start = FALSE;

    i4_ret = a_nw_get_wlan_driver_init_status(&b_wifi_driver_start);
    NW_LOG_ON_FAIL(i4_ret);

    return b_wifi_driver_start;
}

extern BOOL a_nw_custom_is_eth0_enable(VOID)
{
    struct ifreq ifr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

 //   bzero(&ifr, sizeof(ifr));
    c_memset(&ifr, 0, sizeof(ifr));
    strcpy(ifr.ifr_name, "eth0");

    if (ioctl(sockfd, SIOCGIFFLAGS, &ifr)<0)
    {
        /*x_dbg_stmt ("ioctl flag failed\n");*/
        close (sockfd);
        return FALSE;
    }

    close (sockfd);
    if ( ifr.ifr_flags & IFF_RUNNING )
    {
       return TRUE;
    }

    return FALSE;
}

/**
 * @brief   Set ethernet mac address in binary form.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_set_mac_addr(const CHAR *psz_name,UINT8 *pMacAddr)
{
#ifdef LINUX_TURNKEY_SOLUTION
    if (psz_name == NULL || pMacAddr == NULL)
    {
        return NWR_INV_ARG;
    }
    if (c_net_ni_set_mac((CHAR *)psz_name, (CHAR *)pMacAddr) != NET_OK)
        return NWR_FAIL;
#endif
    return NWR_OK;
}

INT32 a_nw_custom_wlan_disassociate(VOID)
{
    INT32    i4_ret = NWR_OK;
    NET_802_11_SSID_T t_Ssid;

    /* reset speed value */
    nw_custom_set_speed(0);

    i4_ret = a_nw_wlan_disassociate();
    NW_LOG_ON_FAIL(i4_ret);

    c_memset(&t_Ssid, 0, sizeof(t_Ssid));
    i4_ret = a_nw_set_wlan_ssid(&t_Ssid);
    NW_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

#ifdef APP_WIFI_NEW_SIGNAL_MAPPING
#define NORMALIZED_SIGNAL_MIN   5
#define NORMALIZED_SIGNAL_MAX   100
#define SIGNAL_STRENGTH_WEAK    -75
#define SIGNAL_STRENGTH_STRONG  -45
#define SIGNAL_STRENGTH_STEP    -10
#endif

/*
 * new wifi signal mapping example:
 * -45 <= RSSI          SIGNAL >= 80       LVL: 5
 * -45 > RSSI >= -55    SIGNAL < 80        LVL: 4
 * -55 > RSSI >= -65    SIGNAL <= 60       LVL: 3
 * -65 > RSSI >= -75    SIGNAL <= 40       LVL: 2
 * -75 > RSSI           SIGNAL <= 20       LVL: 1
 */
INT16 a_nw_custom_wifi_signal_remapping(const INT16 i2_level)
{
    INT16   i2_new_level = 0;
    INT32   i4_dbm = 0;

#ifdef APP_WIFI_NEW_SIGNAL_MAPPING
    if (i2_level >= NORMALIZED_SIGNAL_MAX)
    {
        i4_dbm = SIGNAL_STRENGTH_STRONG;
        i2_new_level = NORMALIZED_SIGNAL_MAX;
    }
    else
    {
        i4_dbm = (i2_level - NORMALIZED_SIGNAL_MIN) * (SIGNAL_STRENGTH_STRONG - SIGNAL_STRENGTH_WEAK) / (NORMALIZED_SIGNAL_MAX - NORMALIZED_SIGNAL_MIN) + SIGNAL_STRENGTH_WEAK;
        i2_new_level = (INT16)(i4_dbm - SIGNAL_STRENGTH_WEAK - SIGNAL_STRENGTH_STEP) * 2;
    }

    /* should bigger than 1 */
    if (i2_new_level <= 0)
    {
        i2_new_level = 1;
    }
#else
    i2_new_level = i2_level - 15;
#endif

    if (0)
    {
        DBG_INFO(("[NW] i4_dbm: %d, i2_level: %d, i2_new_level: %d.\n", i4_dbm, i2_level, i2_new_level));
    }

    return i2_new_level;
}

#include "c_httpc_api.h"
#include "rest/rest_util.h"

static BOOL b_is_httpc_running = FALSE;
static BOOL b_g_accept_for_acr = FALSE;

static VOID _http_async_get_cb_func(HANDLE_T            h_req,
                                    HTTPC_DATA_T       *pt_data,
                                    VOID               *pv_tag,
                                    HTTPC_ASYNC_COND_T  e_async_cond)
{
    DBG_LOG_PRINT(("[NW] %s - result code = %d\n",__FUNCTION__, e_async_cond));
    BOOL    b_tos_pri_apply = FALSE;

    b_tos_pri_apply = (a_tv_custom_get_tos() && a_tv_custom_get_privacy());

    if(pv_tag != NULL_HANDLE)
        c_httpc_free_session(pv_tag);

    if (pt_data != NULL)
    {
        DBG_LOG_PRINT(("[NW][%s] data len=%d, pac_data=%s\r\n", __FUNCTION__, pt_data->ui4_len, pt_data->pac_data));
        c_httpc_data_free(pt_data);
        c_mem_free(pt_data);
    }

    b_is_httpc_running = FALSE;

    UINT16  ui2_idx = 0;
    a_cfg_custom_get_acr(&ui2_idx);

    BOOL b_accept = (ui2_idx == ACFG_ACR_OFF ? FALSE : TRUE);

    /* re-check the viewing status after httpc runing */
    if (b_g_accept_for_acr != b_tos_pri_apply)
    {
    	if (b_accept)
		{
			DBG_LOG_PRINT(("[NW] %s - result code = %d\n",__FUNCTION__, e_async_cond));
			a_nw_custom_get_http_url_for_acr(b_tos_pri_apply);
		}
    }
    else if (HTTPC_ASYNC_COND_OK != e_async_cond)
    {
        a_tv_custom_set_http_url_status(b_accept);
    }
}

INT32 a_nw_custom_get_http_url_for_acr(BOOL b_accept)
{
    INT32 i4_ret = 0;
    CHAR s_url[256];
    CHAR s_mac_str[64];
    CHAR * ps_mac_hash = NULL;
    BOOL b_success = FALSE;

    /* always try to init httpc module first */
    c_httpc_init_module();

    DBG_LOG_PRINT(("[NW] previous http request is still runningi, b_accept=%d\n\r", b_accept));
    do{
        if (b_is_httpc_running)
        {
            DBG_LOG_PRINT(("[NW] previous http request is still running\n\r"));
            break;
        }

        c_memset (s_mac_str, 0, sizeof(CHAR)*64);
        a_nw_get_mac_addr_string((CHAR*)NI_ETHERNET_0, s_mac_str);

        ps_mac_hash = rest_security_hash_token(s_mac_str);
        if (ps_mac_hash == NULL) {
            DBG_ERROR(("[NW][%s] rest_security_hash_token error\r\n", __FUNCTION__));
            break;
        }

        c_memset (s_url, 0, sizeof(CHAR)*256);
        c_snprintf(s_url, sizeof(s_url), "https://users.tvinteractive.tv/cast_oobe_notification?userid=%s&h=%s&user_response=%s",
                                s_mac_str, ps_mac_hash, b_accept ? "accept" : "skip");

        DBG_LOG_PRINT(("[NW] url=[%s]\n\r", s_url));

        HANDLE_T h_handle = NULL_HANDLE;
        i4_ret = c_httpc_new_session(&h_handle);
        if(i4_ret != HTTPR_OK) {
            DBG_ERROR(("[NW][%s] c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, i4_ret));
            if (h_handle != NULL_HANDLE) {
                c_httpc_free_session(h_handle);
                h_handle = NULL_HANDLE;
            }
            break;
        }

        /* set NO verification */
        INT32 i4_ssl_val = 0;
        i4_ret = c_httpc_set_option(h_handle, HTTP_HANDLE_OPT_SSL_VERIFYPEER, &i4_ssl_val);
        if(i4_ret != HTTPR_OK) {
            DBG_ERROR(("[NW][%s] set ssl verifypeer failed! %d\n", __FUNCTION__, i4_ret));
            if (h_handle != NULL_HANDLE) {
                c_httpc_free_session(h_handle);
                h_handle = NULL_HANDLE;
            }
            break;
        }


        HTTPC_DATA_T* pt_data = NULL;
        pt_data = c_mem_alloc(sizeof(*pt_data));
        if (!pt_data)
        {
            DBG_ERROR(("[NW][%s] c_mem_alloc for HTTPC_DATA error, ret = %d\r\n", __FUNCTION__));
            if (h_handle != NULL_HANDLE) {
                c_httpc_free_session(h_handle);
                h_handle = NULL_HANDLE;
            }
            break;
        }
        c_httpc_data_init(pt_data);

        HANDLE_T h_req = NULL_HANDLE;
        i4_ret = c_httpc_get_async(h_handle, s_url, pt_data, _http_async_get_cb_func, (VOID*)h_handle, &h_req);
        if(i4_ret != HTTPR_OK) {
            DBG_ERROR(("[NW][%s] c_httpc_get_async error, ret = %d\r\n", __FUNCTION__, i4_ret));
            if (h_req != NULL_HANDLE) {
                c_httpc_free_session(h_req);
                h_req = NULL_HANDLE;
            }
            if (h_handle != NULL_HANDLE) {
                c_httpc_free_session(h_handle);
                h_handle = NULL_HANDLE;
            }
            c_httpc_data_free(pt_data);
            c_mem_free(pt_data);
            break;
        }
        DBG_LOG_PRINT(("[NW][%s] c_httpc_get_async, len=%d\r\n", __FUNCTION__, pt_data->ui4_len));

        b_g_accept_for_acr = b_accept;
        b_success = TRUE;
        b_is_httpc_running = TRUE;
    }while(0);

    if (FALSE == b_success)
        a_tv_custom_set_http_url_status(b_accept);
    else
        a_tv_custom_clear_http_url_status();

    return APP_CFGR_OK;
}

NW_WLAN_BAND_T a_nw_custom_wifi_frequency_band()
{
    INT32                   i4_ret = RMR_OK;
    NET_802_11_BSS_INFO_T   t_bss_info = {0};
    NW_WLAN_STATE_T         e_wlan_state;

    i4_ret = a_nw_wlan_status(&e_wlan_state);
    if(i4_ret != NWR_OK)
    {
        DBG_LOG_PRINT(("%s %d a_nw_wlan_status fail ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
        return NW_WLAN_FREQ_UNKNOWN;
    }

    if (e_wlan_state == NW_WLAN_ASSOCIATE)
    {
        c_memset(&t_bss_info, 0, sizeof(t_bss_info));
        i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
        if(i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("%s %d a_nw_wlan_get_curr_bss fail ret=%d\n",__FUNCTION__,__LINE__,i4_ret));
            return NW_WLAN_FREQ_UNKNOWN;
        }

        DBG_LOG_PRINT(("%s %d frequency=%d, Channel=%d\n",__FUNCTION__,__LINE__,t_bss_info.i2_Freq, t_bss_info.i2_Channel));
        if(t_bss_info.i2_Freq >= NW_FREQ_2_4_MIN && t_bss_info.i2_Freq <= NW_FREQ_2_4_MAX)
        {
            /* 2.4GHz frequency 2401 ~ 2495 */
            return NW_WLAN_FREQ_2_4_BAND;
        }
        else if(t_bss_info.i2_Freq >= NW_FREQ_5_MIN && t_bss_info.i2_Freq < NW_FREQ_5_6_OVERLAP_MIN)
        {
            /* 5GHz frequency 5030 ~ 5990 but 5945 ~ 5990 is overlap 6G. Actually, 5905 ~ 5990 is not used. */
            return NW_WLAN_FREQ_5_BAND;
        }
        else if(t_bss_info.i2_Freq >= NW_FREQ_6_MIN && t_bss_info.i2_Freq <= NW_FREQ_6_MAX)
        {
            /* 6GHz frequency 5945 ~ 6425 but 5945 ~ 5990 is overlap 5G which no used around the world.*/
            return NW_WLAN_FREQ_6_BAND;
        }
        else
        {
            DBG_LOG_PRINT(("%s %d Unknown freuency!\n",__FUNCTION__,__LINE__));
            return NW_WLAN_FREQ_UNKNOWN;
        }
    }
    return NW_WLAN_FREQ_UNKNOWN;
}

