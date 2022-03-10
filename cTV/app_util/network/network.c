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
 * $RCSfile: network.c,v $
 * $Revision: #4 $
 * $Date: 2015/10/26 $
 * $Author: heyi.wang $
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
 * @brief This file implements the API of network.
 *
 * @author
 */
#ifdef APP_NETWORK_SUPPORT

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef APP_NETWORK_WIFI_SUPPORT
#include <unistd.h>
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include <pthread.h>
#endif
#include <string.h>

#include "c_os.h"
#include "c_aee.h"

#include "c_net_config.h"
#include "u_dhcpc_api.h"
#include "u_net_common.h"
#include "u_net_ni_if.h"
#include "u_net_oid.h"
#include "u_net_socket.h"
#include "c_net_socket.h"
#include "c_dm_dlna.h"

#include "u_net_util.h"

#include "agent/agent.h"
#include "app_util/a_network.h"
#include "app_util/network/network.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "app_util/a_cfg.h"
#include "bgm/mtk_comp/bgm_cast_c4tv/a_bgm_cast_c4tv.h"

#ifdef APP_DMR_SUPPORT
#include "c_dlna_dmr.h"
#include "mmp/a_mmp.h"
#include "mmp/dmr/a_mmp_dmr.h"
#include "mmp/dmr/mmp_dmr.h"
#endif

#ifdef APP_DMS_SUPPORT
#include "c_dlna_dms_api.h"
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
#include "c_dm_smb.h"
#include "c_fm_smb.h"
#endif
#include "c_pcl.h"

#ifdef APP_MMP_DMR_CUSTOMER_RULE
#include "res/app_util/a_network_custom.h"
#endif

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

#define DEBUG_NW_MSG(x)     // x

#define DEBUG_NW_STATUS(x)  // x

#define DEBUG_NW_FLOW(x)    // x

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/
#define NORMALIZED_SIGNAL_MIN     5
#define NORMALIZED_SIGNAL_MAX   100
#define WEAK_SIGNAL_STRENGTH     -85
#define STRONG_SIGNAL_STRENGTH   -50

#define UDP_SERVER_THREAD_NAME          "NETWORK_UDP_SERVER"
#define UDP_SERVER_THREAD_STACK_SIZE    (1024)
#define UDP_SERVER_THREAD_PRIORITY      (200)

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/
#ifdef LINUX_TURNKEY_SOLUTION
extern int __res_init(void);
#endif
extern INT32 c_net_ni_enable(const CHAR *psz_name, INT8 u1EnableNi);
extern INT32 c_net_suspend_poweroff();
extern INT32 c_net_suspend_resume();
static VOID    _nw_msg_brdcast(NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);
static VOID    _mw_send_msg_process(VOID* pv_data, SIZE_T z_data_len);
static VOID    _nw_send_event_msg (NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);
static VOID    _mw_dhcpc_nfy_hdlr(VOID* pv_data, SIZE_T z_data_len);
static VOID    _nw_dhcpc_nfy_fct (DLNA_DHCPC_EV_T e_event,char* dev_name);
static VOID    _nw_ip_ni_notify_hdlr(VOID* pv_data, SIZE_T z_data_len);
static VOID    _nw_ip_ni_notify_fct(VOID *pParam);
static INT32   _nw_enable_network_connection(BOOL b_is_init);
static INT32   _nw_disable_network_connection(BOOL b_is_init);
static INT32   _nw_manual_ip_config(const NW_IP_INFO_T* pt_ip_info);

static INT32  _nw_validate_ipv6_config(NW_IPV6_INFO_T_NO_DNS * p_tip_info);
static INT32  _nw_manual_ipv6_nodns_config(CHAR *psz_name, NW_IPV6_INFO_T_NO_DNS * p_tip_info);
static INT32  _nw_manual_ipv6_config(CHAR *psz_name, NW_IPV6_INFO_T * p_tip_info);
static INT32  _nw_set_ipv6_all_config(VOID);

static INT32   _nw_start_dhcp_ip_config(VOID);
static INT32   _nw_stop_dhcp_ip_config(VOID);

#ifndef DISABLE_TV_WORLD_NW_SETTING
static INT32   _nw_clean_ip_dns(const UINT8 ui1_iface);
#endif
static INT32  _nw_validate_ip_config(const NW_IP_INFO_T* pt_ip_info);

#ifdef APP_NET_DLNA_SUPPORT
static INT32   _nw_start_dlna(VOID);
static INT32   _nw_stop_dlna(VOID);
#endif

#ifdef APP_DMS_SUPPORT
static INT32   _nw_dlna_dms_start(VOID);
static INT32   _nw_dlna_dms_stop(VOID);
#endif
#ifdef APP_DMR_SUPPORT
static INT32   _nw_dlna_dmr_start(VOID);
static INT32   _nw_dlna_dmr_stop(VOID);
static INT32   _nw_dlna_dmr_update(CHAR *ifname);
#endif

static INT32   _nw_get_ethernet_connect_info(BOOL* pb_is_plug);
static INT32   _mw_lock(VOID);
static INT32   _mw_unlock(VOID);

#ifdef APP_NETWORK_WIFI_SUPPORT
static INT32 _nw_wlan_start(VOID);
static INT32 _nw_wlan_stop(VOID);
static VOID _nw_wlan_notify_hdlr(VOID* pv_data, SIZE_T z_data_len);
static INT32 _nw_wlan_associate(NET_802_11_ASSOCIATE_T *pAssociate);
static INT32 _nw_wlan_disassociate(VOID);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
static INT32   _nw_my_net_pls_start(void);
static INT32   _nw_my_net_pls_stop(void);
#endif

static INT32 _nw_start_ip_assoc(const UINT8 ui1_iface);
static CHAR* _nw_get_interface_name(const UINT8 ui1_iface);

#ifdef SUPPORT_2_DONGLES
static CHAR* _nw_get_old_interface_name(VOID);
#endif

static BOOL     b_g_nw_udp_server_start = FALSE;
static HANDLE_T _nw_udp_server = NULL_HANDLE;
static BOOL     b_con_test = FALSE;     //Add for check update when network connect
#ifdef MT5583_MODEL
static UINT16   m_startDriverRetryTime = 0;
#endif
/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/
static UINT16       ui2_nw_dbg_level;  /**<  debug level. */
static NW_UTIL_T    t_g_nw_util = {0};
static BOOL         b_g_nw_init = FALSE;
#ifdef APP_NETWORK_WIFI_SUPPORT
static BOOL         b_g_nw_wifi_disassociating = FALSE;
#endif
typedef struct _nw_ni_lx_monitor_st
{
    char              if_stdname[16];
    NI_DRV_EV_T       e_event;
    ni_ev_notify_fnct pf_notify;
    int               need_notify;
}nw_ni_lx_monitor_st;
/*-----------------------------------------------------------------------------
                    private function implementations
-----------------------------------------------------------------------------*/
static VOID _nw_udp_server_process(VOID* pv_arg)
{
    INT32 i4_ret  = 0;
    INT32 n, i, j, k = 0;
    INT32 sockfd_0 = -1, sockfd_7 = -1, sockfd_9 = -1, maxfdp = -1;
    struct sockaddr_in servaddr, cliaddr;
    //struct timeval sel_timeout;
    fd_set readfds;
    socklen_t len = 0;
    CHAR mesg[256];
    CHAR s_ethernet_address[18] = {0};
    CHAR s_wireless_address[18] = {0};
    CHAR s_target_address[18] = {0};
    INT32 yes = 1;
    BOOL b_socket_finish = FALSE;
    BOOL b_wired_plug = FALSE;
    NW_WLAN_STATE_T e_wlan_state = NW_WLAN_UNPLUG;

    if (NULL == pv_arg)
    {
        DBG_LOG_PRINT(("[NW] <%s, %d> arg is NULL!\n", __FUNCTION__, __LINE__));
        //return;
    }

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

    do{
        sockfd_0 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (-1 == sockfd_0)
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> socket Error! sockfd: %d.\n", __FUNCTION__, __LINE__, sockfd_0));
            break;
        }
        if (setsockopt(sockfd_0, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
        {
            break;
        }
        servaddr.sin_port=htons(0);
        i4_ret = bind(sockfd_0, (struct sockaddr *)&servaddr, sizeof(servaddr));
        if (-1 == i4_ret)
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> bind Error! i4_ret: %d.\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        sockfd_7 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (-1 == sockfd_7)
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> socket Error! sockfd: %d.\n", __FUNCTION__, __LINE__, sockfd_7));
            break;
        }
        if (setsockopt(sockfd_7, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
        {
            break;
        }
        servaddr.sin_port=htons(7);
        i4_ret = bind(sockfd_7, (struct sockaddr *)&servaddr, sizeof(servaddr));
        if (-1 == i4_ret)
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> bind Error! i4_ret: %d.\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        sockfd_9 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (-1 == sockfd_9)
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> socket Error! sockfd: %d.\n", __FUNCTION__, __LINE__, sockfd_9));
            break;
        }
        if (setsockopt(sockfd_9, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
        {
            break;
        }
        servaddr.sin_port=htons(9);
        i4_ret = bind(sockfd_9, (struct sockaddr *)&servaddr, sizeof(servaddr));
        if (-1 == i4_ret)
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> bind Error! i4_ret: %d.\n", __FUNCTION__, __LINE__, i4_ret));
            break;
        }

        b_socket_finish = TRUE;

    }while(0);

    if (!b_socket_finish)
    {
        DBG_LOG_PRINT(("[NW] <%s, %d> socket create Error!\n", __FUNCTION__, __LINE__));
        goto UDP_SERVER_HELL;
    }

    c_memset(s_wireless_address, 0, 18);
    a_nw_get_mac_addr_string (NI_WIRELESS_0, s_wireless_address);

    c_memset(s_ethernet_address, 0, 18);
    a_nw_get_mac_addr_string (NI_ETHERNET_0, s_ethernet_address);

    len = sizeof(cliaddr);

    DBG_LOG_PRINT(("[NW] <%s, %d> socket create ok now start to wait for magic pckage!\n", __FUNCTION__, __LINE__));

    for (;;)
    {
        FD_ZERO(&readfds);
        FD_SET(sockfd_0, &readfds);
        FD_SET(sockfd_7, &readfds);
        FD_SET(sockfd_9, &readfds);
        maxfdp = sockfd_0>sockfd_7?sockfd_0:sockfd_7;
        maxfdp = sockfd_9>maxfdp?sockfd_9:maxfdp;

        /* 0.5 sec */
        //sel_timeout.tv_sec = 0;
        //sel_timeout.tv_usec = 500000;
        //i4_ret = select(maxfdp+1, &readfds, NULL, NULL, &sel_timeout);

        i4_ret = select(maxfdp+1, &readfds, NULL, NULL, NULL);
        if (-1 == i4_ret)
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> select Error! i4_ret: %d.\n", __FUNCTION__, __LINE__, i4_ret));
            goto UDP_SERVER_HELL;
        }

        c_memset(mesg, 0, 256);
        bzero(&cliaddr, len);

        if (FD_ISSET(sockfd_0, &readfds))
        {
            n = recvfrom(sockfd_0, mesg, 256, 0, (struct sockaddr *)&cliaddr, &len);
            if (-1 == n)
            {
                DBG_LOG_PRINT(("[NW] <%s, %d> recvfrom Error!\n", __FUNCTION__, __LINE__));
                continue;
            }
        }
        else if (FD_ISSET(sockfd_7, &readfds))
        {
            n = recvfrom(sockfd_7, mesg, 256, 0, (struct sockaddr *)&cliaddr, &len);
            if (-1 == n)
            {
                DBG_LOG_PRINT(("[NW] <%s, %d> recvfrom Error!\n", __FUNCTION__, __LINE__));
                continue;
            }
        }
        else if (FD_ISSET(sockfd_9, &readfds))
        {
            n = recvfrom(sockfd_9, mesg, 256, 0, (struct sockaddr *)&cliaddr, &len);
            if (-1 == n)
            {
                DBG_LOG_PRINT(("[NW] <%s, %d> recvfrom Error!\n", __FUNCTION__, __LINE__));
                continue;
            }
        }
        else
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> no data!\n", __FUNCTION__, __LINE__));
            continue;
        }

        /* The magic packet size: 6 + 16*6 = 102 bytes  */
        if (n != 102)
        {
            DBG_LOG_PRINT(("[NW] <%s, %d> Not magic packet! n: %d.\n", __FUNCTION__, __LINE__, n));
            continue;
        }

        DBG_LOG_PRINT(("[NW]Received the message from [%s:%d]\n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port)));

        /* check magic packet header 6 bytes */
        for (i = 0; i < 6; i++)
        {
            if ((UINT8)mesg[i] != 0xff)
            {
                break;
            }
        }
        if (i != 6)
        {
            DBG_LOG_PRINT(("[NW] Magic packet header is incorrect, break at: %d!\n", i));
            continue;
        }

        /* check magic packet body 16*6 bytes */
        for (j = 0; j < 6; j++)
        {
            for (k = 1; k < 6; k++)
            {
                if (mesg[i+j] != mesg[i+j+k*6])
                {
                    break;
                }
            }
            if (k != 6)
            {
                break;
            }
        }
        if (k !=6 || j != 6)
        {
            DBG_LOG_PRINT(("[NW] Magic packet body is incorrect, break at: %d!\n", i+j+k*6));
            continue;
        }

        /* get mac addr from magic packet body */
        c_memset(s_target_address, 0, 18);
        c_sprintf(s_target_address, "%02X:%02X:%02X:%02X:%02X:%02X\0",
                (UINT8)mesg[i+0],
                (UINT8)mesg[i+1],
                (UINT8)mesg[i+2],
                (UINT8)mesg[i+3],
                (UINT8)mesg[i+4],
                (UINT8)mesg[i+5]
                );
        a_nw_get_ethernet_connect_info(&b_wired_plug);
        a_nw_wlan_status(&e_wlan_state);
        DBG_LOG_PRINT(("[NW]Received mac address:[%s] b_wired_plug:%s e_wlan_state:%s\n", s_target_address, b_wired_plug ? "plug" : "unplug", e_wlan_state==4 ? "associate" : "disassociate"));

        if(b_wired_plug)
        {
            /* FIXME: depend on current network iface */
            if (0 == c_strcasecmp(s_ethernet_address, "ba:d0:00:ba:d0:00"))
            {
                a_nw_get_mac_addr_string (NI_ETHERNET_0, s_ethernet_address);
            }
            DBG_LOG_PRINT(("[NW]Current Ethernet address:[%s]\n", s_ethernet_address));

            if (0 == c_strcasecmp(s_ethernet_address, s_target_address))
            {
                if (a_bgm_cast_c4tv_wol_enabled())
                {
                    DBG_LOG_PRINT(("[NW] <%s, %d> WOL now!!!\n", __FUNCTION__, __LINE__));
                    a_bgm_exit_active_standby_with_wakeup_reason(PCL_WAKE_UP_REASON_ETHERNET);
                }
                else
                {
                    continue;
                }
                goto UDP_SERVER_HELL;
            }
        }

        if(e_wlan_state == NW_WLAN_ASSOCIATE)
        {
            if (0 == c_strcasecmp(s_wireless_address, "ba:d0:00:ba:d0:00"))
            {
                a_nw_get_mac_addr_string (NI_WIRELESS_0, s_wireless_address);
            }
            DBG_LOG_PRINT(("[NW] Current Wireless address:[%s]\n", s_wireless_address));

            if (0 == c_strcasecmp(s_wireless_address, s_target_address))
            {
                if (a_bgm_cast_c4tv_wol_enabled())
                {
                    DBG_LOG_PRINT(("[NW] <%s, %d> WOW now!!!\n", __FUNCTION__, __LINE__));
                    a_bgm_exit_active_standby_with_wakeup_reason(PCL_WAKE_UP_REASON_WIFI);
                }
                else
                {
                    continue;
                }
                goto UDP_SERVER_HELL;
            }
        }
    }

UDP_SERVER_HELL:
    if (sockfd_9 != -1)
    {
        close(sockfd_9);
    }
    if (sockfd_7 != -1)
    {
        close(sockfd_7);
    }
    if (sockfd_0 != -1)
    {
        close(sockfd_0);
    }

    b_g_nw_udp_server_start = FALSE;

    return;
}

static INT32 _nw_udp_server_init(VOID)
{
    INT32           i4_ret  = 0;
    UINT16          ui2_id  = 0;

    DBG_LOG_PRINT(("[NW] <%s, %d> Enter.\n", __FUNCTION__, __LINE__));

    if (b_g_nw_udp_server_start)
    {
        DBG_LOG_PRINT(("[NW] <%s, %d> nw udp server is already started.\n", __FUNCTION__, __LINE__));
        return NWR_OK;
    }

    i4_ret = c_aee_thread_create(&_nw_udp_server,
                        UDP_SERVER_THREAD_NAME,
                        UDP_SERVER_THREAD_STACK_SIZE,
                        UDP_SERVER_THREAD_PRIORITY,
                        _nw_udp_server_process,
                        sizeof(UINT16),
                        &ui2_id);
    if (i4_ret != AEER_OK)
    {
        DBG_LOG_PRINT(("[NW] <%s, %d> Error! i4_ret: %d.\n", __FUNCTION__, __LINE__, i4_ret));
        return NWR_FAIL;
    }

    b_g_nw_udp_server_start = TRUE;

    return NWR_OK;
}

/**
 * @brief   Let other features to invoke notify functions.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static VOID  _nw_msg_brdcast(NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    NW_UTIL_T*               pt_nw     = &t_g_nw_util;
    UINT16                   ui2_i     = 0;
    MW_UTIL_NFY_CLIENT_T*    pt_client = NULL;

    DEBUG_NW_MSG( DBG_LOG_PRINT(("[NW]Brdcast the msg  -> %d\n", e_nfy_id)); );

    /* Collect all notify clients in to sort structure. */
    for (ui2_i = 0;
         ui2_i < (UINT16)NW_MAX_NUM_NOTIFY_CLIENT;
         ui2_i ++)
    {
        /* Load the client/ */
        pt_client =  &(pt_nw->at_notify_client[ui2_i]);

        /* Check match the group. */
        if (pt_client->pf_notify == NULL)
        {
            continue;
        }

        pt_client->pf_notify(pt_client->pv_tag, e_nfy_id, pv_nfy_param);
    }

    return;
}
/**
 * @brief   Process send msg.
 * @param
 * @retval  VOID.
 */
static VOID _mw_send_msg_process(VOID* pv_data, SIZE_T z_data_len)
{
    MW_UTIL_MSG_T*    pt_msg = (MW_UTIL_MSG_T*)pv_data;

    DBG_INFO(("[NW]send meg:\r\n\n"));
    _nw_msg_brdcast(pt_msg->e_msg_id, pt_msg->pv_nfy_param);

    return;
}
/**
 * @brief   To send a event msg.
 * @param   .
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
static VOID  _nw_send_event_msg (NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    MW_UTIL_MSG_T    t_msg;

    DBG_INFO(("[NW]Send the event msg -> %d\n", e_nfy_id));

    t_msg.e_msg_id = e_nfy_id;
    t_msg.pv_nfy_param = pv_nfy_param;

    a_agent_async_invoke( _mw_send_msg_process,
                         (VOID*)&t_msg,
                         sizeof(MW_UTIL_MSG_T)
                         );

    return;
}
/**
 * @brief   Handle the DHCP notify.
 * @param
 * @retval  VOID.
 */
static VOID _mw_dhcpc_nfy_hdlr(VOID* pv_data, SIZE_T z_data_len)
{
    DLNA_DHCPC_EV_T e_event = *((DLNA_DHCPC_EV_T*)pv_data);
    NW_NFY_ID_T e_nfy_id = NW_NFY_ID_UNKNOWN;
    NW_UTIL_T*  pt_nw  = &t_g_nw_util;

    DBG_LOG_PRINT(("[NW]Handle the  DHCP notify -> %d\n", e_event));

    _mw_lock();

    switch(e_event)
    {
        case DHCPC_EVENT_NEW_ADDRESS_DHCPv4:
        case DHCPC_EVENT_SUCCESS_DHCPv4:
        {
            DBG_INFO(("[NW]DHCPC_EVENT_NEW_ADDRESS_DHCPv4 or DHCPC_EVENT_NEW_ADDRESS_DHCPv4"));
            e_nfy_id = NW_NFY_ID_DHCP_SUCCESS_DHCPv4;
            pt_nw->e_dhcp_state = NW_DHCP_STARTED;
            break;
        }
        case DHCPC_EVENT_SUCCESS_LINKLOCAL:
            DBG_INFO(("[NW]DHCPC_EVENT_SUCCESS_LINKLOCAL"));
            e_nfy_id = NW_NFY_ID_DHCP_SUCCESS_LINKLOCAL;
            pt_nw->e_dhcp_state = NW_DHCP_STARTED_LOCAL;
            break;
        case DHCPC_EVENT_FAILURE_DHCPv4:
        case DHCPC_EVENT_FAILURE_LINKLOCAL:
            DBG_INFO(("[NW]DHCPC_EVENT_FAILURE_DHCPv4 or DHCPC_EVENT_FAILURE_LINKLOCAL"));
            e_nfy_id = NW_NFY_ID_DHCP_FAILURE_LINKLOCAL;
            pt_nw->e_dhcp_state = NW_DHCP_FAILED;
            break;
        default:
            _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
            return;
    }

    _mw_unlock();

    _nw_msg_brdcast(e_nfy_id, NULL);

    return;
}
/**
 * @brief   DHCP notify callback.
 * @param
 * @retval  VOID.
 */
static VOID _nw_dhcpc_nfy_fct (DLNA_DHCPC_EV_T e_event,char* dev_name)
{
    DBG_INFO(("[NW]Received DHCP notify -> %d\n", e_event));

    a_agent_async_invoke( _mw_dhcpc_nfy_hdlr,
                          (VOID*)&e_event,
                          sizeof(DLNA_DHCPC_EV_T)
                          );
    return;
}

#ifndef DISABLE_TV_WORLD_NW_SETTING
/**
 * @brief   _nw_ethernet_plugin_even_hdlr.
 * @param
 * @retval  VOID.
 */
static INT32 _nw_ethernet_plugin_event_hdlr(VOID)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32         i4_ret            = 0;

    if(!pt_nw->b_nw_enabled)
    {
        /*When the Network Connection is disable,do nothing.*/
        return NWR_OK;
    }

    /* handle ethernet plugin msg and start ip associate in network custom part */
    if (0)
    {
        i4_ret = _nw_start_ip_assoc(NW_NET_INTERFACE_ETH0);
        NW_CHK_FAIL(i4_ret);
    }

    return NWR_OK;

}
/**
 * @brief   _nw_ethernet_unplug_even_hdlr.
 * @param
 * @retval  VOID.
 */
static INT32 _nw_ethernet_unplug_event_hdlr(VOID)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32         i4_ret            = NWR_OK;

    if(!pt_nw->b_nw_enabled)
    {
        /*When the Network Connection is disable,do nothing.*/
        return NWR_OK;
    }

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
    i4_ret = _nw_dlna_dmr_stop();
    NW_CHK_FAIL(i4_ret);
#endif
    i4_ret = _nw_stop_dlna();
    NW_CHK_FAIL(i4_ret);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    i4_ret = _nw_my_net_pls_stop();
    NW_CHK_FAIL(i4_ret);
#endif
#ifndef DISABLE_TV_WORLD_NW_SETTING    //clear ip by android
    i4_ret = _nw_clean_ip_dns(NW_NET_INTERFACE_ETH0);
    NW_CHK_FAIL(i4_ret);

#ifdef MW_IPV6_SUPPORT
    i4_ret = c_net_ip_v6_disable(_nw_get_interface_name(NW_NET_INTERFACE_ETH0));/*clear ipv6 address*/
    NW_CHK_FAIL(i4_ret);
#endif
#endif //DISABLE_TV_WORLD_NW_SETTING
    return i4_ret;

}
#endif

/**
 * @brief   _nw_ethernet_unplug_even_hdlr.
 * @param
 * @retval  VOID.
 */
static INT32 _nw_address_chg_event_hdlr(VOID* param)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32         i4_ret            = NWR_OK;


#ifdef APP_NET_DLNA_SUPPORT
    BOOL          b_dlna_enable     = FALSE;
#ifdef APP_DMR_SUPPORT
    BOOL          b_dlna_dmr_enable = FALSE;
#endif
#endif

#ifdef APP_DMS_SUPPORT
    BOOL          b_dlna_dms_enable = FALSE;
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    BOOL          b_my_net_pls_enable = FALSE;
#endif

    if(!pt_nw->b_nw_enabled)
    {
        DBG_LOG_PRINT(("[NW]!!!! Error the nw state.\r\n"));
        return NWR_OK;
    }

#ifdef APP_NET_DLNA_SUPPORT
    i4_ret = nw_custom_get_dlna_enable(&b_dlna_enable);
    NW_CHK_FAIL(i4_ret);

    if (b_dlna_enable)
    {
        i4_ret = _nw_stop_dlna();
        NW_CHK_FAIL(i4_ret);

        i4_ret = _nw_start_dlna();
        NW_CHK_FAIL(i4_ret);
    }
#ifdef APP_DMR_SUPPORT
    CHAR *ifname = (CHAR *)param;
    i4_ret = nw_custom_get_dlna_dmr_enable(&b_dlna_dmr_enable);
    NW_CHK_FAIL(i4_ret);

    if (b_dlna_dmr_enable)
    {
        i4_ret = _nw_dlna_dmr_update(ifname);

        NW_CHK_FAIL(i4_ret);
    }
#endif
#endif

#ifdef APP_DMS_SUPPORT
    i4_ret = nw_custom_get_dlna_dms_enable(&b_dlna_dms_enable);
    NW_CHK_FAIL(i4_ret);

    if (b_dlna_dms_enable)
    {
        i4_ret = _nw_dlna_dms_stop();
        NW_CHK_FAIL(i4_ret);

        i4_ret = _nw_dlna_dms_start();
        NW_CHK_FAIL(i4_ret);
    }
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    i4_ret = nw_custom_get_my_net_pls_enable(&b_my_net_pls_enable);
    NW_CHK_FAIL(i4_ret);

    if (b_my_net_pls_enable)
    {
        i4_ret = _nw_my_net_pls_start();
        NW_CHK_FAIL(i4_ret);
    }
#endif


    return i4_ret;
}
/**
 * @brief   _nw_address_expired_event_hdlr.
 * @param
 * @retval  VOID.
 */
static INT32 _nw_address_expired_event_hdlr(VOID)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32         i4_ret            = NWR_OK;

    if(!pt_nw->b_nw_enabled)
    {
        DBG_LOG_PRINT(("[NW]!!!! Error the nw state.\r\n"));
        return NWR_OK;
    }

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
    i4_ret = _nw_dlna_dmr_stop();
    NW_CHK_FAIL(i4_ret);
#endif
    i4_ret = _nw_stop_dlna();
    NW_CHK_FAIL(i4_ret);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    i4_ret = _nw_my_net_pls_stop();
    NW_CHK_FAIL(i4_ret);
#endif

    return i4_ret;
}

/**
 * @brief   Handle the ni notify.
 * @param
 * @retval  VOID.
 */
static VOID _nw_ip_ni_notify_hdlr(VOID* pv_data, SIZE_T z_data_len)
{
    nw_ni_lx_monitor_st *inParam = (nw_ni_lx_monitor_st*)pv_data;
    NI_DRV_EV_T e_ev = inParam->e_event;
    NW_NFY_ID_T e_nfy_id = NW_NFY_ID_UNKNOWN;

    NW_UTIL_T*  pt_nw  = &t_g_nw_util;

    DBG_LOG_PRINT(("[NW]Handle the ni notify -> %d\n", e_ev));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    switch(e_ev)
    {
    case NI_DRV_EV_ETHERNET_PLUGIN:
    {
        DBG_INFO(("[NW_NOTIFY]NI_DRV_EV_ETHERNET_PLUGIN\n"));
        e_nfy_id = NW_NFY_ID_ETHERNET_PLUGIN;
        pt_nw->b_nw_ethernet_plugin = TRUE;
#ifndef DISABLE_TV_WORLD_NW_SETTING
        _nw_ethernet_plugin_event_hdlr();/*for multiinterface no need handle*/
#endif
        break;
    }
    case NI_DRV_EV_ETHERNET_UNPLUG:
    {
        DBG_INFO(("[NW_NOTIFY]NI_DRV_EV_ETHERNET_UNPLUG\n"));
        e_nfy_id = NW_NFY_ID_ETHERNET_UNPLUG;
        pt_nw->b_nw_ethernet_plugin = FALSE;
#ifndef DISABLE_TV_WORLD_NW_SETTING
        _nw_ethernet_unplug_event_hdlr(); /*for multiinterface no need handle*/
#endif
        break;
    }
    case NI_DRV_EV_IP_ADDRESS_CHANGED:
    {
        DBG_INFO(("[NW_NOTIFY]NI_DRV_EV_IP_ADDRESS_CHANGED\n"));
        e_nfy_id = NW_NFY_ID_ADDRESS_CHANGED;
        _nw_address_chg_event_hdlr(inParam->if_stdname);
        break;
    }
    case NI_DRV_EV_IP_ADDRESS_EXPIRED:
    {
        DBG_INFO(("[NW_NOTIFY]NI_DRV_EV_IP_ADDRESS_EXPIRED\n"));
        e_nfy_id = NW_NFY_ID_ADDRESS_EXPIRED;
        _nw_address_expired_event_hdlr();
        break;
    }
    default:
        _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
        return;
    }

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    _nw_msg_brdcast(e_nfy_id, NULL);

    return;
}
/**
 * @brief   Ni notify callback.
 * @param
 * @retval  VOID.
 */


static VOID _nw_ip_ni_notify_fct(VOID* pParam)
{
    nw_ni_lx_monitor_st tmp;
    memcpy(&tmp, pParam, 20);
    DBG_INFO(("[NW]Received ni notify -> %d\n", tmp.e_event));

    a_agent_async_invoke( _nw_ip_ni_notify_hdlr,
                          (void*)&tmp,
                          20
                          );
    return;
}


/**
 * @brief   check the TV whether or not link a router.
 * @param
 * @retval  VOID.
 */
static BOOL _nw_is_tv_link_router(VOID)
{
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;

    if (a_nw_is_ethernet_plugin())
    {
        return TRUE;
    }

#ifdef APP_NETWORK_WIFI_SUPPORT
    if (pt_nw->e_wlan_status == NW_WLAN_ASSOCIATE)
    {
        return TRUE;
    }
    else
#endif
    {
        return pt_nw->b_nw_ethernet_plugin;
    }
}

/**
 * @brief   Enable network connection.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_enable_network_connection(BOOL b_is_init)
{
    INT32         i4_ret = 0;
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;

    if (pt_nw->b_nw_enabled)
    {
        return NWR_OK;
    }

    i4_ret = c_net_enable();
    NW_CHK_FAIL(i4_ret);

#ifdef APP_NETWORK_WIFI_SUPPORT
    if (FALSE == a_nw_is_ethernet_plugin())
    {
        i4_ret = c_net_set_if_type(IF_TYPE_IEEE80211);
        NW_CHK_FAIL(i4_ret);

        /*DON'T start wlan during init network*/
        if (b_g_nw_init == TRUE)
        {
            i4_ret = _nw_wlan_start();
            NW_CHK_FAIL(i4_ret);

            pt_nw->b_nw_enabled = TRUE;
        }
        return NWR_OK;
    }
    else
    {
        i4_ret = c_net_set_if_type(IF_TYPE_ETHERNET);
        NW_CHK_FAIL(i4_ret);
    }
#endif

    if (!b_is_init)
    {
        if (pt_nw->b_nw_ethernet_plugin == FALSE)
        {
            return NWR_OK;
        }

        i4_ret = _nw_start_ip_assoc(NW_NET_INTERFACE_ETH0);
        NW_CHK_FAIL(i4_ret);
    }

    pt_nw->b_nw_enabled = TRUE;
    return NWR_OK;
}

/**
 * @brief   Disable network connection.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_disable_network_connection(BOOL b_is_init)
{
    INT32         i4_ret = 0;
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;

    if (!b_is_init)
    {
        if (!pt_nw->b_nw_enabled)
        {
            return NWR_OK;
        }


#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
        if (pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
        {
            if (pt_nw->e_built_in_wlan_status == NW_WLAN_ASSOCIATE
                ||pt_nw->e_built_in_wlan_status == NW_WLAN_START_DISASSOC)
            {
                i4_ret = _nw_wlan_stop();
                NW_CHK_FAIL(i4_ret);
                pt_nw->e_built_in_wlan_status = NW_WLAN_PLUG_STOP;
            }

            i4_ret = c_net_disable();
            NW_CHK_FAIL(i4_ret);

            return NWR_OK;
        }
        if (pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)
        {
            if (pt_nw->e_out_wlan_status == NW_WLAN_ASSOCIATE
                ||pt_nw->e_out_wlan_status == NW_WLAN_START_DISASSOC)
            {
                i4_ret = _nw_wlan_stop();
                NW_CHK_FAIL(i4_ret);
                pt_nw->e_out_wlan_status = NW_WLAN_PLUG_STOP;
            }

            i4_ret = c_net_disable();
            NW_CHK_FAIL(i4_ret);

            return NWR_OK;
        }
#else
        if (pt_nw->ui1_interface == NW_NET_INTERFACE_WIFI)
        {
            if (pt_nw->e_wlan_status == NW_WLAN_ASSOCIATE
                ||pt_nw->e_wlan_status == NW_WLAN_START_DISASSOC)
            {
                _nw_wlan_stop();
                pt_nw->e_wlan_status = NW_WLAN_PLUG_STOP;
            }
        }
#endif
#endif
        if(pt_nw->e_dhcp_state != NW_DHCP_STOPPED)
        {
            i4_ret = _nw_stop_dhcp_ip_config();
            NW_CHK_FAIL(i4_ret);
        }
        else
        {
            NW_IP_INFO_T t_ip_info;

            c_memset(&t_ip_info, 0,sizeof(NW_IP_INFO_T));

            t_ip_info.ui4_netmask = (UINT32)0xFFFFFFFF;

            i4_ret = _nw_manual_ip_config(&t_ip_info);
            NW_CHK_FAIL(i4_ret);
        }

#ifdef MW_IPV6_SUPPORT
        NW_IPV6_INFO_T t_ipv6_info;

        c_memset(&t_ipv6_info, 0,sizeof(NW_IPV6_INFO_T));

        i4_ret = _nw_manual_ipv6_config(_nw_get_interface_name(pt_nw->ui1_interface), &t_ipv6_info);
        NW_CHK_FAIL(i4_ret);

#endif

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
        i4_ret = _nw_dlna_dmr_stop();
        NW_CHK_FAIL(i4_ret);
#endif
        i4_ret = _nw_stop_dlna();
        NW_CHK_FAIL(i4_ret);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
        i4_ret = _nw_my_net_pls_stop();
        NW_CHK_FAIL(i4_ret);
#endif

    }

    pt_nw->b_nw_enabled = FALSE;

    i4_ret = c_net_disable();
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}
/**
 * @brief   Enable the internet connection manually.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_manual_ip_config(const NW_IP_INFO_T* pt_ip_info)
{
    INT32 i4_ret;
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;

    c_net_clean_dns_cache();

    i4_ret = c_net_ip_config(
                         _nw_get_interface_name(pt_nw->ui1_interface),
                         pt_ip_info->ui4_address,
                         pt_ip_info->ui4_netmask,
                         pt_ip_info->ui4_gw
                         );
    NW_CHK_FAIL(i4_ret);

    i4_ret = c_net_dns_config(pt_ip_info->ui4_1st_dns, pt_ip_info->ui4_2nd_dns);
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}
/**
 * @brief   _mw_connection_test_process.
 * @param
 * @retval  VOID.
 */
static VOID _mw_connection_test_process(VOID* pv_data, SIZE_T z_data_len)
{
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;
    NW_NFY_ID_T   e_nfy_id = NW_NFY_ID_UNKNOWN;
    BOOL          b_test_result = FALSE;
    CHAR*         s_test_hostname = NULL;
    int           af_family = *((int *)pv_data);
    int           ret = 0;
  //  const int     TCP_TEST_PORT = 80;

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

   do
   {
        if(pt_nw->s_test_hostname == NULL)
        {
           break;
        }

        s_test_hostname = (CHAR*)c_mem_alloc(sizeof(CHAR)*(c_strlen(pt_nw->s_test_hostname)+1));
        if(s_test_hostname != NULL)
        {
            c_strcpy(s_test_hostname, pt_nw->s_test_hostname);

            c_mem_free(pt_nw->s_test_hostname);
            pt_nw->s_test_hostname = NULL;
        }
        else
        {
            DBG_LOG_PRINT(("[NW]_mw_connection_test_process mem alloc fail!\r\n"));
        }
    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    if (s_test_hostname == NULL)
    {
        return;
    }

#ifdef LINUX_TURNKEY_SOLUTION
    __res_init();
#endif


    if(af_family == AF_INET)
    {

#ifdef LINUX_TURNKEY_SOLUTION
        const int     TCP_TEST_PORT1 = 80;
        ret = c_net_tcp_connect_test_v4(s_test_hostname, TCP_TEST_PORT1);
#else
        struct hostent *pt_hostnet = NULL;
        pt_hostnet = gethostbyname(s_test_hostname);
        if(NULL != pt_hostnet)
        {
            ret = 0;
            x_net_free_hostent(pt_hostnet);
        }
        else
            ret = -1;
#endif

        e_nfy_id = NW_NFY_ID_INTERN_CT_RESULT;
    }
    else
    {
#ifdef MW_IPV6_SUPPORT
        const int     TCP_TEST_PORT2 = 80;
        ret = c_net_tcp_connect_test_v6(s_test_hostname, TCP_TEST_PORT2);
#else
        ret = -1;
#endif

        e_nfy_id = NW_NFY_ID_INTERN_CT_RESULTv6;
    }

    if (!ret)
    {
        DBG_INFO(("[NW]The Connection test is success!.\r\n"));
        b_test_result = TRUE;
        b_con_test = TRUE;
    }
    else
    {
        DBG_INFO(("[NW]The Connection test is fail!.\r\n"));
        b_test_result = FALSE;
        b_con_test = FALSE;
    }

    c_mem_free(s_test_hostname);
    s_test_hostname = NULL;

    _nw_msg_brdcast(e_nfy_id, (VOID*)(UINT32)b_test_result);

    return;
}

/**
 * @brief   Enable the internet connection automatically(DHCP).
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_start_dhcp_ip_config (VOID)
{
    INT32 i4_ret = NWR_OK;
    NW_UTIL_T* pt_nw = &t_g_nw_util;

    c_net_clean_dns_cache();
    if(pt_nw->e_dhcp_state == NW_DHCP_STOPPED)
    {
        i4_ret = c_dhcpc_init();
        NW_CHK_FAIL(i4_ret);

        i4_ret = c_dhcpc_start(_nw_get_interface_name(pt_nw->ui1_interface), _nw_dhcpc_nfy_fct);
        NW_CHK_FAIL(i4_ret);

        pt_nw->e_dhcp_state = NW_DHCP_STARTING;
    }
    else
    {
        i4_ret = c_dhcpc_restart(_nw_get_interface_name(pt_nw->ui1_interface));
        NW_CHK_FAIL(i4_ret);
    }

    return NWR_OK;
}
/**
 * @brief   stop dhcp.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_stop_dhcp_ip_config(VOID)
{
    INT32 i4_ret = NWR_OK;
    NW_UTIL_T* pt_nw = &t_g_nw_util;

    pt_nw->e_dhcp_state = NW_DHCP_STOPPED;
#ifdef SUPPORT_2_DONGLES
    i4_ret = c_dhcpc_stop(_nw_get_old_interface_name());
    NW_CHK_FAIL(i4_ret);
#else
    i4_ret = c_dhcpc_stop(_nw_get_interface_name(pt_nw->ui1_interface));
    NW_CHK_FAIL(i4_ret);
#endif
    i4_ret = c_dhcpc_deinit();
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   set the ip/netmask/gateway/dns to full zero.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
#ifndef DISABLE_TV_WORLD_NW_SETTING
static INT32  _nw_clean_ip_dns(const UINT8 ui1_iface)
{
    INT32 i4_ret = NWR_OK;

    DBG_LOG_PRINT(("[KK] %s, LINE: %d, i4_ret: %d\n", __FUNCTION__, __LINE__, i4_ret));

    //c_net_clean_dns_cache();

    i4_ret = c_net_ip_config(_nw_get_interface_name(ui1_iface), 0, 0, 0);
    NW_CHK_FAIL(i4_ret);

    //i4_ret = c_net_dns_config(0, 0);
    //NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}
#endif
/**
 * @brief   validate the ip config info(exp. host number shoud not be full zero and 1) .
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_validate_ip_config(const NW_IP_INFO_T* pt_ip_info)
{

     /*need check the ip setting.*/
     if (((pt_ip_info->ui4_address & pt_ip_info->ui4_netmask) == pt_ip_info->ui4_address) ||
          ((pt_ip_info->ui4_address | (~pt_ip_info->ui4_netmask)) == pt_ip_info->ui4_address))
     {
         return  NWR_INV_ARG;
     }

     /*need check the gateway.*/
     if (pt_ip_info->ui4_gw != 0)
     {
         if(((pt_ip_info->ui4_gw & pt_ip_info->ui4_netmask) == pt_ip_info->ui4_gw) ||
             ((pt_ip_info->ui4_gw | ~pt_ip_info->ui4_netmask) == pt_ip_info->ui4_gw))
          {
              return  NWR_INV_ARG;
          }

         if( (pt_ip_info->ui4_address & pt_ip_info->ui4_netmask) != (pt_ip_info->ui4_gw & pt_ip_info->ui4_netmask))
         {
             return  NWR_INV_ARG;
         }
     }

    return NWR_OK;
}

#ifdef APP_DMS_SUPPORT
/**
 * @brief   Enable DLNA.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_dlna_dms_start(VOID)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    if (pt_nw->e_dlna_dms_state == NW_DLNA_DMS_STOPPED)
    {
        DBG_INFO(("[NW]%s\n", __func__));
        c_dlna_dms_start();
    }
    pt_nw->e_dlna_dms_state = NW_DLNA_DMS_STARTED;

    return NWR_OK;
}
/**
 * @brief   Disable DLNA.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_dlna_dms_stop(VOID)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret;

    if (NW_DLNA_DMS_STARTED == pt_nw->e_dlna_dms_state)
    {
        i4_ret = c_dlna_dms_stop();
        DBG_INFO(("[NW]%s ret(%d)\n", __func__, i4_ret));
        if (NWR_OK != i4_ret)
        {
            return NWR_FAIL;
        }

        pt_nw->e_dlna_dms_state = NW_DLNA_DMS_STOPPED;
    }

    return NWR_OK;
}
#endif

#ifdef APP_NET_DLNA_SUPPORT
/**
 * @brief   Enable DLNA.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_start_dlna(VOID)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;

    if (pt_nw->e_dlna_state == NW_DLNA_STOPPED)
    {
        DBG_INFO(("[NW]Start DLNA func.\r\n"));

        c_dm_dlna_dmp_start();
    }

    pt_nw->e_dlna_state = NW_DLNA_STARTED;

    return NWR_OK;
}
/**
 * @brief   Disable DLNA.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_stop_dlna(VOID)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;

    if (pt_nw->e_dlna_state == NW_DLNA_STARTED)
    {
        DBG_INFO(("[NW]Stop DLNA func.\r\n"));

        c_dm_dlna_dmp_stop();

        pt_nw->e_dlna_state = NW_DLNA_STOPPED;

    }

    return NWR_OK;
}
#endif

#ifdef APP_DMR_SUPPORT
/**
 * @brief   DMR callback to play media file.
 * @param
 * @retval
 * @retval
 */
#ifdef APP_MMP_DMR_CUSTOMER_RULE
//assignment from incompatible pointer type
static VOID _nw_dlna_dmr_cb_play(E_DMR_PLAYER_PLAYSPEED tPlayspeed)
{
    DBG_LOG_PRINT(("(+) DMR (+) >> request to play.\n"));
    a_mmp_dmr_set_during_enter_flag(TRUE);
    a_mmp_request_operation(MMP_REQ_OP_DMR_START);
    DBG_LOG_PRINT(("(+) DMR (+) << request to play.\n"));
}

#else
static VOID _nw_dlna_dmr_cb_play(E_DMR_PLAYER_PLAYSPEED tPlayspeed)
{
    DBG_LOG_PRINT(("(+) DMR (+) >> request to play.\n"));
#ifdef APP_MMP_SUPPORT
    a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_START, (VOID*)(INT32)tPlayspeed);
#endif

    DBG_LOG_PRINT(("(+) DMR (+) << request to play.\n"));
}
#endif
/**
 * @brief   DMR callback to pause media file.
 * @param
 * @retval
 * @retval
 */
static VOID _nw_dlna_dmr_cb_pause(VOID)
{
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    nw_dlna_dmr_cb_pause_cust();
#else
    DBG_LOG_PRINT(("(+) DMR (+) >> request to pause.\n"));
#ifdef APP_MMP_SUPPORT
    a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_PAUSE, NULL);
#endif

    DBG_LOG_PRINT(("(+) DMR (+) << request to pause.\n"));
#endif
}

/**
 * @brief   DMR callback to resume media file.
 * @param
 * @retval
 * @retval
 */
#ifdef APP_MMP_DMR_CUSTOMER_RULE
static VOID _nw_dlna_dmr_cb_resume(E_DMR_PLAYER_PLAYSPEED tPlayspeed)
{
    nw_dlna_dmr_cb_resume_cust();
}
#else
static VOID _nw_dlna_dmr_cb_resume(E_DMR_PLAYER_PLAYSPEED tPlayspeed)
{
    DBG_LOG_PRINT(("(+) DMR (+) >> request to resume.\n"));
#ifdef APP_MMP_SUPPORT
    a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_RESUME, (VOID*)(INT32)tPlayspeed);
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to resume.\n"));
}
#endif
/**
 * @brief   DMR callback to stop media file.
 * @param
 * @retval
 * @retval
 */
static VOID _nw_dlna_dmr_cb_stop(VOID)
{
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    nw_dlna_dmr_cb_stop_cust();
#else
    DBG_LOG_PRINT(("(+) DMR (+) >> request to stop.\n"));
#ifdef APP_MMP_SUPPORT
    a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_STOP, NULL);
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to stop.\n"));
#endif
}

/**
 * @brief   DMR callback to get current vol.
 * @param
 * @retval
 * @retval
 */
static VOID _nw_dlna_dmr_cb_get_vol(UINT8* pui1_vol)
{
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    nw_dlna_dmr_cb_get_vol_cust(pui1_vol);
#else
    DBG_LOG_PRINT(("(+) DMR (+) >> request to get vol.\n"));
#ifdef APP_MMP_SUPPORT
    a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_GET_VOL, (VOID*)pui1_vol);
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to get vol.\n"));
#endif
}

/**
 * @brief   DMR callback to set vol.
 * @param
 * @retval
 * @retval
 */
static INT8 _nw_dlna_dmr_cb_set_vol(UINT8 ui1_vol)
{

    INT32   i4_ret = 0;
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    i4_ret = nw_dlna_dmr_cb_set_vol_cust(ui1_vol);
#else
    DBG_LOG_PRINT(("(+) DMR (+) >> request to set vol.\n"));
#ifdef APP_MMP_SUPPORT
    i4_ret = a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_SET_VOL, (VOID*)((UINT32)ui1_vol));
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to set vol.\n"));
#endif

    return (INT8)i4_ret;
}

/**
 * @brief   DMR callback to get current mute state.
 * @param
 * @retval
 * @retval
 */
static VOID _nw_dlna_dmr_cb_get_mute(BOOL* pb_mute)
{
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    nw_dlna_dmr_cb_get_mute_cust(pb_mute);
#else
    DBG_LOG_PRINT(("(+) DMR (+) >> request to get mute.\n"));
#ifdef APP_MMP_SUPPORT
    a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_GET_MUTE, (VOID*)pb_mute);
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to get mute.\n"));
#endif
}

/**
 * @brief   DMR callback to set mute.
 * @param
 * @retval
 * @retval
 */
static INT8 _nw_dlna_dmr_cb_set_mute(BOOL b_mute)
{

    INT32   i4_ret = 0;
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    i4_ret = nw_dlna_dmr_cb_set_mute_cust(b_mute);
#else
    DBG_LOG_PRINT(("(+) DMR (+) >> request to set mute.\n"));
#ifdef APP_MMP_SUPPORT
    i4_ret = a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_SET_MUTE, (VOID*)((UINT32)b_mute));
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to set mute.\n"));
#endif

    return (INT8)i4_ret;
}

/**
 * @brief   DMR callback to get current progress and duration.
 * @param
 * @retval
 * @retval
 */
static VOID _nw_dlna_dmr_cb_get_progress(UINT64*  pui8_pos, UINT64* pui8_dur)
{
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    nw_dlna_dmr_cb_get_progress_cust(pui8_pos, pui8_dur);
#else
#ifdef APP_MMP_SUPPORT
    MMP_DMR_PROGRESS_T    t_progress = {0};
    INT32                 i4_ret     = -1;

    i4_ret = a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_GET_PROGRESS, (VOID*)(&t_progress));
    if(0 == i4_ret)
    {
        *pui8_pos = t_progress.ui8_pos;
        *pui8_dur = t_progress.ui8_dur;
    }
    else
    {
        *pui8_pos = 0;
        *pui8_dur = 0;
    }
#endif
    return;
#endif
}

/**
 * @brief   DMR callback to seek the media.
 * @param
 * @retval
 * @retval
 */
static VOID _nw_dlna_dmr_cb_seek(UINT64 ui8_seek)
{
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    nw_dlna_dmr_cb_seek_cust(ui8_seek);
#else
#ifdef APP_MMP_SUPPORT
    UINT64       ui8_temp = ui8_seek;

    DBG_LOG_PRINT(("(+) DMR (+) >> request to seek.\n"));

    a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_SEEK, (VOID*)(&ui8_temp));
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to seek.\n"));
#endif
}

/**
 * @brief   DMR callback to do fast forward.
 * @param
 * @retval
 * @retval
 */
static INT8 _nw_dlna_dmr_cb_fast_forward(VOID)
{

    INT32   i4_ret = 0;
#ifdef APP_MMP_DMR_CUSTOMER_RULE
    i4_ret = nw_dlna_dmr_cb_fast_forward_cust();
#else
    DBG_LOG_PRINT(("(+) DMR (+) >> request to fast forward.\n"));
#ifdef APP_MMP_SUPPORT
    i4_ret = a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_FAST_FORWARD, (VOID*)NULL);
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to fast forward.\n"));
#endif

    return (INT8)i4_ret;
}

/**
 * @brief   DMR callback to do fast rewind.
 * @param
 * @retval
 * @retval
 */
static INT8 _nw_dlna_dmr_cb_fast_rewind(VOID)
{

    INT32   i4_ret = 0;
#ifdef APP_MMP_DMR_CUSTOMER_RULE
        nw_dlna_dmr_cb_fast_rewind_cust();
#else
    DBG_LOG_PRINT(("(+) DMR (+) >> request to fast rewind.\n"));

#ifdef APP_MMP_SUPPORT
    i4_ret = a_mmp_dmr_request_operation(MMP_DMR_REQ_OP_DMR_FASK_REWIND, (VOID*)NULL);
#endif
    DBG_LOG_PRINT(("(+) DMR (+) << request to fast rewind.\n"));
#endif

    return (INT8)i4_ret;
}

/**
 * @brief   Enalbe DLNA DMR.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_dlna_dmr_start(VOID)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    static DMR_PLAYER_T t_dmr_player;
    INT32 i4_ret;

    if (NW_DLNA_DMR_STOPPED == pt_nw->e_dlna_dmr_state)
    {
        c_memset(&t_dmr_player, 0, sizeof(DMR_PLAYER_T));

        t_dmr_player.pf_play   = _nw_dlna_dmr_cb_play;
        t_dmr_player.pf_pause  = _nw_dlna_dmr_cb_pause;
        t_dmr_player.pf_resume = _nw_dlna_dmr_cb_resume;
        t_dmr_player.pf_stop   = _nw_dlna_dmr_cb_stop;
        t_dmr_player.pf_get_volume     = _nw_dlna_dmr_cb_get_vol;
        t_dmr_player.pf_set_volume     = _nw_dlna_dmr_cb_set_vol;
        t_dmr_player.pf_get_mute       = _nw_dlna_dmr_cb_get_mute;
        t_dmr_player.pf_set_mute       = _nw_dlna_dmr_cb_set_mute;
        t_dmr_player.pf_get_progress   = _nw_dlna_dmr_cb_get_progress;
        t_dmr_player.pf_seek           = _nw_dlna_dmr_cb_seek;
        t_dmr_player.pf_fast_forward   = _nw_dlna_dmr_cb_fast_forward;
        t_dmr_player.pf_fast_rewind    = _nw_dlna_dmr_cb_fast_rewind;
#ifdef APP_MMP_DMR_CUSTOMER_RULE
        t_dmr_player.pf_is_dmc_allowed = a_dmr_player_is_dmc_allowed_fct;
        t_dmr_player.pf_is_status_ok   = a_dmr_player_is_status_ok_fct;
#endif
        i4_ret = c_dmr_register_player(&t_dmr_player);
        if (DMRR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("(x) DMR (x) >> c_dmr_register_player() returns %d.\n", i4_ret));
            return NWR_FAIL;
        }

        i4_ret = c_dmr_start();
        if (DMRR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("(x) DMR (x) >> c_dmr_start() returns %d.\n", i4_ret));
            return NWR_FAIL;
        }


        pt_nw->e_dlna_dmr_state = NW_DLNA_DMR_STARTED;
    }

    return NWR_OK;
}

static INT32 _nw_dlna_dmr_update(CHAR* ifname)
{
    c_dmr_update_interface(ifname);
    _nw_dlna_dmr_start();
    return NWR_OK;
}
/**
 * @brief   Disable DLNA DMR.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_dlna_dmr_stop(VOID)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret;

    if (NW_DLNA_DMR_STARTED == pt_nw->e_dlna_dmr_state)
    {
        i4_ret = c_dmr_stop();
        if (DMRR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("(x) DMR (x) >> c_dmr_stop() returns %d.\n", i4_ret));
            return NWR_FAIL;
        }

        pt_nw->e_dlna_dmr_state = NW_DLNA_DMR_STOPPED;
    }

    return NWR_OK;
}
#endif /* APP_DMR_SUPPORT */

#ifdef APP_NET_NEIGHBOR_SUPPORT
/**
 * @brief  my network places start/on
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_my_net_pls_start(void)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;
    DBG_INFO(("[NW]Start network my places.\r\n"));

    _mw_lock();
    do
    {
        if (pt_nw->e_my_net_pls_state == NW_MY_NET_PLS_STOPPED)
        {
            DBG_INFO(("[NW]Start MY_NET_PLS func.\r\n"));
            c_dm_smb_start();
        }
        pt_nw->e_my_net_pls_state = NW_MY_NET_PLS_STARTED;

    }while(0);

    _mw_unlock();
    return i4_ret;
}


/**
 * @brief  my network places stop/off
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_my_net_pls_stop(void)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;

    if (pt_nw->e_my_net_pls_state == NW_MY_NET_PLS_STARTED)
    {
        DBG_INFO(("[NW]Stop MY_NET_PLS func.\r\n"));

        c_dm_smb_stop();

        pt_nw->e_my_net_pls_state = NW_MY_NET_PLS_STOPPED;

    }

    return NWR_OK;
}

#endif


/**
 * @brief   Get the ethernect is plugin or unplug.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_get_ethernet_connect_info(BOOL* pb_is_plug)
{
    INT32 i4_ret  = NWR_OK;
    UINT32 ui4_status = 0;

    DEBUG_NW_FLOW( DBG_LOG_PRINT(("[NW]{%s,%d} Enter \n", __FUNCTION__, __LINE__ )); );

    i4_ret = c_net_ni_get(NI_ETHERNET_0, OID_CMN_IF_CONNECT_STATUS, (VOID *) &ui4_status);
    NW_CHK_FAIL(i4_ret);

    switch (ui4_status)
    {
    case NI_DRV_EV_ETHERNET_PLUGIN:
        *pb_is_plug = TRUE;
        break;
    case NI_DRV_EV_ETHERNET_UNPLUG:
        *pb_is_plug = FALSE;
        break;
    default:
        return NWR_FAIL;
    }

    return NWR_OK;
}

/**
 * @brief   Manual start sntp process.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_manual_start_sntp (VOID)
{
    INT32       i4_ret = 0;
    if(access("3rd/bin/sntp",0) == 0)
    {
        AP_SYSTEM_CALL("/3rd/bin/sntp &");
    }
    else
    {
        AP_SYSTEM_CALL("/basic/bin/sntp &");
    }

    DBG_INFO(("[NW] manual start sntp at FUNC: %s.\n", __FUNCTION__));

    return NWR_OK;
}

/**
 * @brief   Start ip address association process.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_start_ip_assoc(const UINT8 ui1_iface)
{
    INT32         i4_ret            = 0;
    BOOL          b_auto_ip_config  = FALSE;


#ifdef APP_NET_DLNA_SUPPORT
    BOOL          b_dlna_enable     = FALSE;
#ifdef APP_DMR_SUPPORT
    BOOL          b_dlna_dmr_enable = FALSE;
#endif
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    BOOL          b_my_net_pls_enable = FALSE;
#endif
    DBG_INFO(("[NW]Call %s, line is %d\n", __FUNCTION__, __LINE__));

    NW_UTIL_T*    pt_nw  = &t_g_nw_util;
    //UINT8         ui1_old_interface = pt_nw->ui1_interface;

    pt_nw->ui1_interface = ui1_iface;
    DBG_INFO(("[NW][%s %d]pt_nw->ui1_interface == %d\n",__FUNCTION__,__LINE__,pt_nw->ui1_interface));
    DBG_INFO(("[NW][%s %d]pt_nw->ui1_old_interface == %d\n",__FUNCTION__,__LINE__,pt_nw->ui1_old_interface));

    do
    {
    #ifdef APP_NET_DLNA_SUPPORT
        i4_ret = nw_custom_get_dlna_enable(&b_dlna_enable);
        NW_BREAK_ON_FAIL(i4_ret);
    #ifdef APP_DMR_SUPPORT
        i4_ret = nw_custom_get_dlna_dmr_enable(&b_dlna_dmr_enable);
        NW_BREAK_ON_FAIL(i4_ret);
    #endif
    #endif

    #ifdef APP_NET_NEIGHBOR_SUPPORT
        i4_ret = nw_custom_get_my_net_pls_enable(&b_my_net_pls_enable);
        NW_BREAK_ON_FAIL(i4_ret);
    #endif

    #ifndef DISABLE_TV_WORLD_NW_SETTING  /*do ip setting by android*/
    #ifdef MW_IPV6_SUPPORT
        /*If IP is manual, set IP address*/

        i4_ret = _nw_set_ipv6_all_config();
        NW_BREAK_ON_FAIL(i4_ret);
    #endif

        i4_ret = nw_custom_get_auto_ip_config_by_iface(&b_auto_ip_config, pt_nw->ui1_interface);
        NW_BREAK_ON_FAIL(i4_ret);

        if (b_auto_ip_config)
        {
            i4_ret = _nw_start_dhcp_ip_config();
            NW_BREAK_ON_FAIL(i4_ret);
        }
        else
        {
            NW_IP_INFO_T t_ip_info;
            c_memset(&t_ip_info, 0,sizeof(NW_IP_INFO_T));

            i4_ret = nw_custom_get_ip_addr_config_by_iface(&t_ip_info, pt_nw->ui1_interface);
            NW_BREAK_ON_FAIL(i4_ret);

            i4_ret = _nw_manual_ip_config(&t_ip_info);
            NW_BREAK_ON_FAIL(i4_ret);

            i4_ret = _nw_manual_start_sntp();
            NW_BREAK_ON_FAIL(i4_ret);

    #endif //DISABLE_TV_WORLD_NW_SETTING

    #ifdef APP_NET_DLNA_SUPPORT
            if (b_dlna_enable)
            {
                i4_ret = _nw_start_dlna();
                NW_BREAK_ON_FAIL(i4_ret);
            }
    #endif

    #ifdef APP_NET_NEIGHBOR_SUPPORT
            if (b_my_net_pls_enable)
            {
                i4_ret = _nw_my_net_pls_start();
                NW_BREAK_ON_FAIL(i4_ret);
            }
    #endif
    #ifndef DISABLE_TV_WORLD_NW_SETTING  /*do ip setting by android*/
        }
    #endif
    } while(0);

    //pt_nw->ui1_interface = ui1_old_interface;

    return NWR_OK;
}
#ifdef SUPPORT_2_DONGLES
/**
 * @brief   get the last interface name.
 */
static CHAR* _nw_get_old_interface_name(VOID)
{
#ifdef APP_NETWORK_WIFI_SUPPORT
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;


    if (pt_nw->ui1_old_interface == NW_NET_INTERFACE_ETH0)
    {
        return NI_ETHERNET_0;

    }
    else if (pt_nw->ui1_old_interface == NW_NET_INTERFACE_OUT_WIFI)
    {
        return NI_WIRELESS_1;
    }
    else
    {
        return NI_WIRELESS_0;
    }
#else

    return NI_IP_0;
#endif

}
/**
 * @brief   get current interface name.
 */
static CHAR* _nw_get_interface_name(const UINT8 ui1_iface)
{
#ifdef APP_NETWORK_WIFI_SUPPORT
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;

    if (pt_nw->ui1_interface == NW_NET_INTERFACE_ETH0)
    {
        return NI_ETHERNET_0;

    }
    else if (pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)
    {
        return NI_WIRELESS_1;
    }
    else
    {
        return NI_WIRELESS_0;
    }
#else

    return NI_IP_0;
#endif

}
#else
/**
 * @brief   get current interface name.
 */
static CHAR* _nw_get_interface_name(const UINT8 ui1_iface)
{
#ifdef APP_NETWORK_WIFI_SUPPORT
    if (NW_NET_INTERFACE_WIFI == ui1_iface)
    {
        return NI_WIRELESS_0;
    }
    else
    {
        return NI_ETHERNET_0;
    }
#else
    return NI_ETHERNET_0;
#endif
}

#endif
/**
 * @brief   Lock func.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _mw_lock(VOID)
{
    NW_UTIL_T*     pt_nw = &t_g_nw_util;

    return c_sema_lock(pt_nw->h_api_mtx, X_SEMA_OPTION_WAIT) == OSR_OK ?
                       NWR_OK : NWR_FAIL;
}
/**
 * @brief   Unlock func.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _mw_unlock(VOID)
{
    NW_UTIL_T*     pt_nw = &t_g_nw_util;

    return c_sema_unlock(pt_nw->h_api_mtx) == OSR_OK ?
                    NWR_OK : NWR_FAIL;
}

#ifdef APP_NETWORK_WIFI_SUPPORT


/**
 * @brief   The notify callback of wlan
 * @param [in]  i4CallbackId - callback ID
 * @param [in]  pParam - parameter
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_wlan_driver_notify_fct(INT32 i4CallbackId, VOID *pParam)
{
    NW_WLAN_NTY_T t_wlan_nty;

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, i4CallbackId: %d\n", __FUNCTION__, __LINE__, i4CallbackId));

    t_wlan_nty.i4_msg_id = i4CallbackId;

    if(WLAN_NOTIFY_DRIVER_START_IND == t_wlan_nty.i4_msg_id||
    WLAN_NOTIFY_DRIVER_START_FAILED == t_wlan_nty.i4_msg_id)
    {
        t_wlan_nty.i4_data = *((INT32*)pParam);
        a_agent_async_invoke( _nw_wlan_notify_hdlr,
                             (VOID*)&t_wlan_nty,
                             sizeof(NW_WLAN_NTY_T));
    }

    return NWR_OK;
}

/**
 * @brief   Start wifi driver.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_wlan_start_driver(VOID)
{
    INT32         i4_ret = NWR_OK;
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, b_wlan_drv_init: %d\n", __FUNCTION__, __LINE__, pt_nw->b_wlan_drv_init));

    i4_ret = c_net_wlan_start_driver(_nw_wlan_driver_notify_fct);

    if(i4_ret != NWR_OK)
    {
        pt_nw->b_wlan_drv_init = FALSE;
    }

    return i4_ret;
}

/**
 * @brief   Start ip address association process.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_wlan_start(VOID)
{
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;
    INT32         i4_ret = NWR_OK;

#ifdef SUPPORT_2_DONGLES
    DBG_LOG_PRINT(("[NW] Start to set device name --->%s,%d\n",__FUNCTION__, __LINE__));
    i4_ret =a_nw_set_device_name( _nw_get_interface_name());
    NW_LOG_ON_FAIL(i4_ret);
#endif

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, b_wlan_drv_init: %d, b_wlan_started: %d.\n", __FUNCTION__, __LINE__, pt_nw->b_wlan_drv_init,pt_nw->b_wlan_started));

    if ((!pt_nw->b_wlan_drv_init))
    {
        DBG_LOG_PRINT(("[NW] wifi is uninited  now start to init \n"));
        NW_LOG_ON_FAIL(_nw_wlan_start_driver());
        return NWR_OK;
    }

    if (!pt_nw->b_wlan_started)
    {
        i4_ret = c_net_wlan_open_connection(NULL);
        NW_CHK_FAIL(i4_ret);

        pt_nw->b_wlan_started = TRUE;

        NW_LOG_ON_FAIL(i4_ret);
    }

    ACFG_COUNTRY_CODE_T t_country = ACFG_COUNTRY_CODE_US;
    a_cfg_custom_get_country_code(&t_country);
    DBG_LOG_PRINT(("[Jundi][%s %d]t_country:%d\n",__FUNCTION__,__LINE__,t_country));

    //set country code
    switch (t_country)
    {
        case ACFG_COUNTRY_CODE_UNKNOWN:
//#ifdef MT5583_MODEL
//            system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=5");
//#else
            system("wpa_cli -i wlan0 set country=WW");
//#endif
            break;
        case ACFG_COUNTRY_CODE_MEX:
//#ifdef MT5583_MODEL
//            system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=2");
//#else
            system("wpa_cli -i wlan0 set country=MX");
//#endif
            break;
        case ACFG_COUNTRY_CODE_CA:
//#ifdef MT5583_MODEL
//            system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=1");
//#else
            system("wpa_cli -i wlan0 set country=CA");
//#endif
            break;
        case ACFG_COUNTRY_CODE_US:
//#ifdef MT5583_MODEL
//            system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=1");
//#else
            system("wpa_cli -i wlan0 set country=US");
//#endif
            break;
        default:
            DBG_LOG_PRINT(("[Jundi][%s %d]No match country\n",__FUNCTION__,__LINE__));
//#ifdef MT5583_MODEL
//            system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=5");
//#else
            system("wpa_cli -i wlan0 set country=WW");
//#endif
            break;
    }

    /*send the WLAN_NOTIFY_START_IND message*/
    NW_WLAN_NTY_T t_wlan_nty;
    t_wlan_nty.i4_msg_id = WLAN_NOTIFY_START_IND;
    t_wlan_nty.i4_data = 0;


    i4_ret = a_agent_async_invoke( _nw_wlan_notify_hdlr,
                          (VOID*)&t_wlan_nty,
                          sizeof(NW_WLAN_NTY_T)
                          );
    NW_LOG_ON_FAIL(i4_ret);

    return NWR_OK;
}

/**
 * @brief   Stop the wifi.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_wlan_stop(VOID)
{
    INT32         i4_ret = NWR_OK;
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;

    /*need do disassociating before close connection*/
    DBG_LOG_PRINT(("%s %d calling disassociate\n",__FUNCTION__,__LINE__));
    i4_ret = c_net_wlan_disassociate();
    NW_LOG_ON_FAIL(i4_ret);

    i4_ret = c_net_wlan_close_connection();
    NW_LOG_ON_FAIL(i4_ret);

    {
        /*send the WLAN_NOTIFY_DEINIT_IND message*/
        NW_WLAN_NTY_T t_wlan_nty;
        t_wlan_nty.i4_msg_id = WLAN_NOTIFY_DEINIT_IND;
        t_wlan_nty.i4_data = 0;

        i4_ret = a_agent_async_invoke( _nw_wlan_notify_hdlr,
                              (VOID*)&t_wlan_nty,
                              sizeof(NW_WLAN_NTY_T)
                              );
        NW_CHK_FAIL(i4_ret);
    }

    pt_nw->b_wlan_started = FALSE;

    return NWR_OK;
}


#ifndef DISABLE_TV_WORLD_NW_SETTING
/**
 * @brief   _nw_ethernet_plugin_even_hdlr.
 * @param
 * @retval  VOID.
 */
static INT32 _nw_wirless_plugin_event_hdlr(VOID)
{
    INT32         i4_ret = NWR_OK;
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;

    if(!pt_nw->b_nw_enabled)
    {
        /*When the Network Connection is disable,do nothing.*/
        return NWR_OK;
    }

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, _nw_wlan_start. i4_ret: %d,pt_nw->b_wlan_drv_init %d\n", __FUNCTION__, __LINE__, 0, pt_nw->b_wlan_drv_init));
    if(pt_nw->b_wlan_drv_init)
    {
        i4_ret = c_net_wlan_stop_driver(_nw_wlan_driver_notify_fct);
        pt_nw->b_wlan_drv_init = FALSE;
		NW_CHK_FAIL(i4_ret);
    }
    i4_ret = _nw_wlan_start();
    NW_CHK_FAIL(i4_ret);

    return NWR_OK;
}
/**
 * @brief   _nw_ethernet_unplug_even_hdlr.
 * @param
 * @retval  VOID.
 */
static INT32 _nw_wirless_unplug_event_hdlr(VOID)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32         i4_ret            = 0;

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, b_wlan_drv_init: %d\n", __FUNCTION__, __LINE__, pt_nw->b_wlan_drv_init));

    if (!pt_nw->b_nw_enabled)
    {
        /*When the Network Connection is disable,do nothing.*/
        return NWR_OK;
    }

    {
        c_net_wlan_open_connection(NULL);
        i4_ret = c_net_wlan_stop_driver(_nw_wlan_driver_notify_fct);
        pt_nw->b_wlan_drv_init = FALSE;
        NW_CHK_FAIL(i4_ret);
        i4_ret = c_net_wlan_close_connection();
        NW_CHK_FAIL(i4_ret);
        pt_nw->b_wlan_started = FALSE;
    }

#ifndef DISABLE_TV_WORLD_NW_SETTING
    i4_ret = _nw_clean_ip_dns(NW_NET_INTERFACE_WIFI);
    NW_CHK_FAIL(i4_ret);
#endif

#ifdef MW_IPV6_SUPPORT
    i4_ret = c_net_ip_v6_disable(_nw_get_interface_name(NW_NET_INTERFACE_WIFI));/*clear ipv6 address*/
    NW_CHK_FAIL(i4_ret);
#endif
    return NWR_OK;
}
#endif

/**
 * @brief   Handle the ni notify.
 * @param
 * @retval  VOID.
 */
static INT32 _nw_wlan_assoc_event_hdlr(WLAN_NOTIFY_MSG_T   e_nty_msg)
{
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;
    INT32         i4_ret = NWR_OK;
    //UINT8         ui1_iface = pt_nw->ui1_interface;

    switch(e_nty_msg)
    {
    case WLAN_NFY_MSG_ALREADY_ASSOCIATED:
        break;
    case WLAN_NFY_MSG_DISCONNECTED:
    {
        DBG_LOG_PRINT(("[KK][NW] %s, %d, WLAN_NFY_MSG_DISCONNECTED, e_wlan_status: %d, e_dhcp_state: %d\n", __FUNCTION__, __LINE__, pt_nw->e_wlan_status, pt_nw->e_dhcp_state));
#ifndef DISABLE_TV_WORLD_NW_SETTING
        if(pt_nw->e_dhcp_state != NW_DHCP_STOPPED && pt_nw->ui1_interface != NW_NET_INTERFACE_ETH0)
        {
            DBG_LOG_PRINT(("[KK][NW] Start NW_DHCP_STOPPED, LINE: %d.\r\n", __LINE__));
            //pt_nw->ui1_interface = NW_NET_INTERFACE_WIFI;
            i4_ret = _nw_stop_dhcp_ip_config();
            NW_LOG_ON_FAIL(i4_ret);
            //pt_nw->ui1_interface = ui1_iface;
        }
#endif
        pt_nw->e_wlan_status = NW_WLAN_START_DISASSOC;

        break;
    }
    case WLAN_NFY_MSG_OK:
    {
        DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, WLAN_NFY_MSG_OK, e_wlan_status: %d\n", __FUNCTION__, __LINE__, pt_nw->e_wlan_status));

    #ifdef SUPPORT_2_DONGLES
        if (pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
        {
            pt_nw->e_built_in_wlan_status = NW_WLAN_ASSOCIATE;
        }
        if (pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)
        {
            pt_nw->e_out_wlan_status = NW_WLAN_ASSOCIATE;
        }
    #else
        pt_nw->e_wlan_status = NW_WLAN_ASSOCIATE;
    #endif

        if(!a_nw_is_ethernet_plugin())
        {
            i4_ret = _nw_start_ip_assoc(NW_NET_INTERFACE_WIFI);
            NW_BREAK_ON_FAIL(i4_ret);
        }

        break;
    }
    default:

#ifdef SUPPORT_2_DONGLES
        if (pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
        {
            DBG_INFO(("[NW] change status line=%d\r\n", __LINE__));
            if(pt_nw->e_built_in_wlan_status != NW_WLAN_UNPLUG)
            {
                pt_nw->e_built_in_wlan_status = NW_WLAN_START_DISASSOC;
            }
        }
        if (pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)
        {
            DBG_INFO(("[NW] change status line=%d\r\n", __LINE__));
            if(pt_nw->e_out_wlan_status != NW_WLAN_UNPLUG)
            {
                pt_nw->e_out_wlan_status = NW_WLAN_START_DISASSOC;
            }
        }
#else
        pt_nw->e_wlan_status = NW_WLAN_START_DISASSOC;
#endif

break;
    }

    return i4_ret;
}

/**
 * @brief   Handle the ni notify.
 * @param
 * @retval  VOID.
 */
static VOID _nw_wlan_notify_hdlr(VOID* pv_data, SIZE_T z_data_len)
{
    NW_UTIL_T*    pt_nw  = &t_g_nw_util;
    INT32         i4_ret = NWR_OK;

    BOOL         b_brd_msg = TRUE;
    VOID*        pv_nfy_param = NULL;
    NW_NFY_ID_T   e_nfy_id = NW_NFY_ID_UNKNOWN;

    NW_WLAN_NTY_T t_wlan_nty = *((NW_WLAN_NTY_T*)pv_data);


    DEBUG_NW_MSG( DBG_LOG_PRINT(("[NW][%s %d]Handle the wlan msg  -> %d\n",__FUNCTION__,__LINE__,t_wlan_nty.i4_msg_id)); );

    _mw_lock();
    DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    switch(t_wlan_nty.i4_msg_id)
    {
        case WLAN_NOTIFY_START_IND:
            DBG_LOG_PRINT(("[NW_NOTIFY]WLAN_NOTIFY_START_IND(%d)\n",WLAN_NOTIFY_START_IND));

            e_nfy_id = NW_NFY_ID_WLAN_START_IND;
            pv_nfy_param = (VOID*)t_wlan_nty.i4_data;

            if (pt_nw->e_wlan_status == NW_WLAN_ASSOCIATE)
            {
                NW_LOG_ON_FAIL(_nw_start_ip_assoc(NW_NET_INTERFACE_WIFI));
            }
            else
            {
                NET_802_11_ASSOCIATE_T t_Associate;

                CHAR  s_key[65];

                c_memset(&t_Associate, 0, sizeof(NET_802_11_ASSOCIATE_T));
#ifdef SUPPORT_2_DONGLES
                if ( pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
                {
                    pt_nw->e_built_in_wlan_status = NW_WLAN_START_DISASSOC;
                }
                if ( pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)
                {
                    pt_nw->e_out_wlan_status = NW_WLAN_START_DISASSOC;
                }
#else
                pt_nw->e_wlan_status = NW_WLAN_START_DISASSOC;
#endif
                c_memset(s_key, 0, sizeof(CHAR)*65);
                t_Associate.t_Key.pui1_PassPhrase = s_key;

                NW_LOG_ON_FAIL(nw_custom_get_associate(&t_Associate));

                t_Associate.e_AssocCase = IEEE_802_11_PWR_ON_ASSOC;

                /* connect only if ssid is provided */
                if (t_Associate.t_Ssid.ui4_SsidLen != 0 && strlen(t_Associate.t_Ssid.ui1_aSsid))
                {
                    NW_LOG_ON_FAIL(_nw_wlan_associate(&t_Associate));
                }
                else
                {
                    DBG_LOG_PRINT(("[NW]No saved WLAN setting, do not connect!\n"));
                }
            }
            break;

        case WLAN_NOTIFY_INIT_IND:
            DBG_INFO(("[NW_NOTIFY]WLAN_NOTIFY_INIT_IND\n"));
            e_nfy_id = NW_NFY_ID_WLAN_INIT_IND;
            pv_nfy_param = (VOID*)t_wlan_nty.i4_data;

            if (pt_nw->ui1_interface != NW_NET_INTERFACE_ETH0)
            {
                i4_ret = _nw_wlan_start();
                NW_BREAK_ON_FAIL(i4_ret);
            }

            break;
        case WLAN_NOTIFY_DEINIT_IND:
            DBG_LOG_PRINT(("[NW_NOTIFY]WLAN_NOTIFY_DEINIT_IND(%d)\n",WLAN_NOTIFY_DEINIT_IND));
            e_nfy_id = NW_NFY_ID_WLAN_DEINIT_IND;
            pv_nfy_param = (VOID*)t_wlan_nty.i4_data;
            pt_nw->b_wlan_started = FALSE;

#ifdef SUPPORT_2_DONGLES
            if (( pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)&&(pt_nw->e_built_in_wlan_status!= NW_WLAN_UNPLUG))
            {
                pt_nw->e_built_in_wlan_status = NW_WLAN_PLUG_STOP;
            }
            if (( pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)&&(pt_nw->e_out_wlan_status!= NW_WLAN_UNPLUG))
            {
                pt_nw->e_out_wlan_status = NW_WLAN_PLUG_STOP;
            }
#else
            if (pt_nw->e_wlan_status!= NW_WLAN_UNPLUG)
            {
                pt_nw->e_wlan_status = NW_WLAN_PLUG_STOP;
            }
#endif
            break;
        case WLAN_NOTIFY_SCAN:
            DEBUG_NW_MSG( DBG_LOG_PRINT(("[NW_NOTIFY]WLAN_NOTIFY_SCAN(%d)\n",WLAN_NOTIFY_SCAN)); );
            e_nfy_id = NW_NFY_ID_WLAN_SCAN;
            pv_nfy_param = (VOID*)t_wlan_nty.i4_data;
            break;
        case WLAN_NOTIFY_ASSOCIATE:
        {
            DBG_LOG_PRINT(("[NW_NOTIFY]WLAN_NOTIFY_ASSOCIATE(%d)\n",WLAN_NOTIFY_ASSOCIATE));
            e_nfy_id = NW_NFY_ID_WLAN_ASSOCIATE;

            /* do nothing when wifi is disassociating*/
            if (FALSE == b_g_nw_wifi_disassociating)
            {
                _nw_wlan_assoc_event_hdlr((WLAN_NOTIFY_MSG_T)t_wlan_nty.i4_data);
            }

            pv_nfy_param = (VOID*)t_wlan_nty.i4_data;

            break;
        }
        case WLAN_NOTIFY_WPS_ASSOC_SETTING:
            DBG_LOG_PRINT(("[NW_NOTIFY]WLAN_NOTIFY_WPS_ASSOC_SETTING(%d)\n",WLAN_NOTIFY_WPS_ASSOC_SETTING));
            e_nfy_id = NW_NFY_ID_WLAN_WPS_ASSOC_SETTING;
            break;
        case WLAN_NOTIFY_WPS_STATE:
            DBG_LOG_PRINT(("[NW_NOTIFY]WLAN_NOTIFY_WPS_STATE(%d)\n",WLAN_NOTIFY_WPS_STATE));
            e_nfy_id = NW_NFY_ID_WLAN_WPS_STATE;
            pv_nfy_param = (VOID*)t_wlan_nty.i4_data;
            break;
        case WLAN_NOTIFY_WPS_ASSOCIATE:
            DBG_INFO(("[NW_NOTIFY]WLAN_NOTIFY_WPS_ASSOCIATE\n"));
            e_nfy_id = NW_NFY_ID_WLAN_WPS_ASSOCIATE;
            pv_nfy_param = (VOID*)t_wlan_nty.i4_data;

            /* do nothing when wifi is disassociating*/
            if (FALSE == b_g_nw_wifi_disassociating)
            {
                _nw_wlan_assoc_event_hdlr((WLAN_NOTIFY_MSG_T)t_wlan_nty.i4_data);
            }

            break;
        case WLAN_NOTIFY_DRIVER_START_IND:
            DBG_LOG_PRINT(("[NW_NOTIFY]WLAN_NOTIFY_DRIVER_START_IND(%d)\n",WLAN_NOTIFY_DRIVER_START_IND));
            if(FALSE ==  pt_nw->b_wlan_drv_init)
            {
                c_net_ni_enable (NI_WIRELESS_0, 1);

                e_nfy_id = NW_NFY_ID_WLAN_DRIVER_START_IND;
                pv_nfy_param = (VOID*)t_wlan_nty.i4_data;

                pt_nw->b_wlan_drv_init = TRUE;
                NW_BREAK_ON_FAIL(_nw_wlan_start());
            }
            break;

        case WLAN_NOTIFY_DRIVER_START_FAILED:
            DBG_LOG_PRINT(("[NW_NOTIFY]WLAN_NOTIFY_DRIVER_START_FAILED(%d)\n",WLAN_NOTIFY_DRIVER_START_FAILED));
            e_nfy_id = NW_NFY_ID_WLAN_DRIVER_START_FAILED;
            pv_nfy_param = (VOID*)t_wlan_nty.i4_data;
            pt_nw->b_wlan_drv_init = FALSE;
#ifdef MT5583_MODEL
            DBG_LOG_PRINT(("m_startDriverRetryTime=%d\n",m_startDriverRetryTime));
            if(m_startDriverRetryTime < 5)
            {
                //WIFI_RESET  ( GPIO10_PM ), GPIO index is 15, needs +1
                c_pcl_set_gpio(16, PCL_GPIO_STATUS_LOW);
                c_thread_delay(20);
                c_pcl_set_gpio(16, PCL_GPIO_STATUS_HIGH);
                m_startDriverRetryTime++;
            }
#endif
            break;
        default:
            _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
            return;
    }

    _mw_unlock();
    DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    DEBUG_NW_MSG( DBG_LOG_PRINT(("[NW]_nw_wlan_notify_hdlr end.\n")); );

    if (b_brd_msg)
    {
        _nw_msg_brdcast(e_nfy_id, (VOID*)pv_nfy_param);
    }

    return;
}

/**
 * @brief   The notify callback of wlan
 * @param [in]  i4CallbackId - callback ID
 * @param [in]  pParam - parameter
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_wlan_notify_fct(INT32 i4CallbackId, VOID *pParam)
{

    NW_UTIL_T*    pt_nw  = &t_g_nw_util;
    NW_WLAN_NTY_T t_wlan_nty;

    if (!pt_nw->b_nw_enabled)
    {
        return NWR_OK;
    }

    t_wlan_nty.i4_msg_id = i4CallbackId;

    switch(t_wlan_nty.i4_msg_id)
    {
        case WLAN_NOTIFY_START_IND:
        case WLAN_NOTIFY_INIT_IND:
        case WLAN_NOTIFY_DEINIT_IND:
        case WLAN_NOTIFY_SCAN:
        case WLAN_NOTIFY_ASSOCIATE:
        case WLAN_NOTIFY_WPS_STATE:
        case WLAN_NOTIFY_WPS_ASSOCIATE:
        {
            t_wlan_nty.i4_data = *((INT32*)pParam);
            break;
        }
        case WLAN_NOTIFY_WPS_ASSOC_SETTING:
        {
            INT32         i4_ret = NWR_OK;
            i4_ret = nw_custom_set_associate((NET_802_11_ASSOCIATE_T*)pParam);
            NW_LOG_ON_FAIL(i4_ret);

            t_wlan_nty.i4_data = i4_ret;

            break;
        }
        default:
            return NWR_OK;
    }

    a_agent_async_invoke( _nw_wlan_notify_hdlr,
                          (VOID*)&t_wlan_nty,
                          sizeof(NW_WLAN_NTY_T)
                          );

    return NWR_OK;
}

#ifdef SUPPORT_2_DONGLES
/**
 * @brief   Handle the wifi notify and only transfer the notify to the UI layer.
 * @param
 * @retval  VOID.
 */
static VOID _nw_ip_ni_wlan_notify_hdlr_only_notify(VOID* pv_data, SIZE_T z_data_len)
{
    NW_WLAN_NTY_T t_wlan_nty = *((NW_WLAN_NTY_T*)pv_data);
    NW_NFY_ID_T e_nfy_id = NW_NFY_ID_UNKNOWN;

    DBG_LOG_PRINT(("Handle the ni wifi notify -> %d\n", t_wlan_nty.i4_msg_id));

    switch(t_wlan_nty.i4_msg_id)
    {
        case NI_DRV_EV_WLAN_ASSOC:
        {
            e_nfy_id = NW_NFY_ID_WIRLESS_PLUGIN;
            break;
        }
        case NI_DRV_EV_WLAN_DISASSOC:
        {
            e_nfy_id = NW_NFY_ID_WIRLESS_UNPLUG;
            break;
        }
        default:
            return;
    }

    _nw_msg_brdcast(e_nfy_id, (VOID *)t_wlan_nty.i4_data);

    return;
}


/**
 * @brief   Handle the wifi notify.
 * @param
 * @retval  VOID.
 */
static VOID _nw_ip_ni_wlan_notify_hdlr(VOID* pv_data, SIZE_T z_data_len)
{
    NW_WLAN_NTY_T t_wlan_nty = *((NW_WLAN_NTY_T*)pv_data);

    NW_NFY_ID_T e_nfy_id = NW_NFY_ID_UNKNOWN;

    DBG_LOG_PRINT(("Handle the ni wifi notify -> %d\n",t_wlan_nty.i4_msg_id));

    switch(t_wlan_nty.i4_msg_id)
    {
        case NI_DRV_EV_WLAN_ASSOC:
        {
#ifdef MT5583_MODEL
            m_startDriverRetryTime = 0;
#endif
            e_nfy_id = NW_NFY_ID_WIRLESS_PLUGIN;
#ifndef DISABLE_TV_WORLD_NW_SETTING
           _nw_wirless_plugin_event_hdlr(); /*for multiinterface no need handle*/
#endif
            break;
        }
        case NI_DRV_EV_WLAN_DISASSOC:
        {
            e_nfy_id = NW_NFY_ID_WIRLESS_UNPLUG;
#ifndef DISABLE_TV_WORLD_NW_SETTING
            _nw_wirless_unplug_event_hdlr();/*for multiinterface no need handle*/
#endif
            break;
        }
        default:
            return;
    }

    _nw_msg_brdcast(e_nfy_id, (VOID *)t_wlan_nty.i4_data);

    return;
}
/**
 * @brief   Ni notify callback for built in dongle.
 * @param
 * @retval  VOID.
 */
static VOID _nw_ip_ni_built_in_wlan_notify_fct(NI_DRV_EV_T e_ev)
{
    NW_UTIL_T*  pt_nw  = &t_g_nw_util;
    BOOL        built_enable = TRUE;
    INT32             i4_ret   = NWR_OK;

    NW_WLAN_NTY_T t_wlan_nty = {0};

    t_wlan_nty.i4_msg_id = (INT32)e_ev;
    t_wlan_nty.i4_data = NW_NET_INTERFACE_BUILT_IN_WIFI;

    DBG_LOG_PRINT(("Received built in ni wifi notify -> %d\n", e_ev));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    switch(e_ev)
    {
        case NI_DRV_EV_WLAN_ASSOC:
        {
            pt_nw->e_built_in_wlan_status = NW_WLAN_PLUG_STOP;
            break;
        }
        case NI_DRV_EV_WLAN_DISASSOC:
        {
            pt_nw->e_built_in_wlan_status = NW_WLAN_UNPLUG;
            break;
        }
        default:
           _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
           return;
    }

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    /*get the built_in dongle's enable state*/
    i4_ret = a_cfg_custom_get_built_in_wireless_lan(&built_enable);
    if (NWR_OK != i4_ret)
    {
        DBG_INFO(("[NW]a_cfg_custom_get_built_in_wireless_lan failed! function %s, line is %d\n", __FUNCTION__, __LINE__));
    }

    if (( pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI )&&(TRUE == built_enable))
    {
        DBG_INFO(("handle the notify NW_NET_INTERFACE_BUILT_IN_WIFI do something.\n"));

        a_agent_async_invoke( _nw_ip_ni_wlan_notify_hdlr,
                        (VOID*)&t_wlan_nty,
                        sizeof(NW_WLAN_NTY_T)
                      );
    }
    else
    {
        DBG_INFO(("handle the notify NW_NET_INTERFACE_BUILT_IN_WIFI do nothing.\n"));

        a_agent_async_invoke( _nw_ip_ni_wlan_notify_hdlr_only_notify,
                        (VOID*)&t_wlan_nty,
                        sizeof(NW_WLAN_NTY_T)
                      );
    }

    return;

}

/**
 * @brief   Ni notify callback for out dongle.
 * @param
 * @retval  VOID.
 */
static VOID _nw_ip_ni_out_wlan_notify_fct(NI_DRV_EV_T e_ev)
{

    NW_UTIL_T*  pt_nw  = &t_g_nw_util;

    NW_WLAN_NTY_T t_wlan_nty = {0};

    t_wlan_nty.i4_msg_id = (INT32)e_ev;
    t_wlan_nty.i4_data = NW_NET_INTERFACE_OUT_WIFI;

     DBG_LOG_PRINT(("Received out ni wifi notify -> %d\n", e_ev));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    switch(e_ev)
    {
        case NI_DRV_EV_WLAN_ASSOC:
        {
            pt_nw->e_out_wlan_status = NW_WLAN_PLUG_STOP;
            break;
        }
        case NI_DRV_EV_WLAN_DISASSOC:
        {
            pt_nw->e_out_wlan_status = NW_WLAN_UNPLUG;
            break;
        }
        default:
           _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
           return;
    }

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));


    if ( pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI )
    {
        DBG_INFO(("handle the notify NW_NET_INTERFACE_OUT_WIFI do something.\n"));
        a_agent_async_invoke( _nw_ip_ni_wlan_notify_hdlr,
                          (VOID*)&t_wlan_nty,
                          sizeof(NW_WLAN_NTY_T)
                      );
    }
    else
    {
        DBG_INFO(("handle the notify NW_NET_INTERFACE_OUT_WIFI do nothing.\n"));

        a_agent_async_invoke( _nw_ip_ni_wlan_notify_hdlr_only_notify,
                        (VOID*)&t_wlan_nty,
                        sizeof(NW_WLAN_NTY_T)

                      );
    }

    return;
}


/**
 * @brief   Change the network interface.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static VOID  _nw_chg_network_interface( VOID* pv_data, SIZE_T z_data_len )
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32         i4_ret            = NWR_OK;
    UINT8 ui1_interface = *((UINT8 *)pv_data);

    BOOL b_auto_ip_config = TRUE;

    DBG_LOG_PRINT(("[NW][%s %d] change the network interface to -> %d\n",__FUNCTION__,__LINE__, ui1_interface));

    if(!pt_nw->b_nw_enabled)
    {
        /*When the Network Connection is disable,do nothing.*/
        return ;
    }

    i4_ret = nw_custom_get_auto_ip_config_(&b_auto_ip_config);
    NW_CHK_FAIL_VOID(i4_ret);

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
    i4_ret = _nw_dlna_dmr_stop();
    NW_CHK_FAIL_VOID(i4_ret);
#endif
    i4_ret = _nw_stop_dlna();
    NW_CHK_FAIL_VOID(i4_ret);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    i4_ret = _nw_my_net_pls_stop();
    NW_CHK_FAIL_VOID(i4_ret);
#endif

    if (b_auto_ip_config && (pt_nw->e_dhcp_state != NW_DHCP_STOPPED))
    {
        i4_ret = _nw_stop_dhcp_ip_config();
        NW_CHK_FAIL_VOID(i4_ret);
    }

    /* just close  connection if change interface  from wifi to eth0*/
    if ((pt_nw->ui1_old_interface != NW_NET_INTERFACE_ETH0)&&(ui1_interface == NW_NET_INTERFACE_ETH0))
    {
        _nw_wlan_stop();
    }

    /* stop wifi driver and  close  connection if change interface between built_in dongle and usb dongle*/
    if ((pt_nw->ui1_old_interface != NW_NET_INTERFACE_ETH0)&&(ui1_interface != NW_NET_INTERFACE_ETH0)&&(pt_nw->ui1_old_interface != ui1_interface))
    {
        extern INT32 c_net_wlan_stop_driver(x_net_wlan_notify_fct pfNotify);
        i4_ret = c_net_wlan_stop_driver(_nw_wlan_driver_notify_fct);
        pt_nw->b_wlan_drv_init = FALSE;
        NW_CHK_FAIL_VOID(i4_ret);
        i4_ret = c_net_wlan_close_connection();
        NW_CHK_FAIL_VOID(i4_ret);

        pt_nw->b_wlan_started = FALSE;

        /* delay 2 secs */
        sleep(2);
    }

    pt_nw->ui1_old_interface = pt_nw->ui1_interface;
    pt_nw->ui1_interface = ui1_interface;

    if (pt_nw->ui1_interface != NW_NET_INTERFACE_ETH0)
    {
        i4_ret = c_net_set_if_type(IF_TYPE_IEEE80211);
        NW_CHK_FAIL_VOID(i4_ret);

        i4_ret = _nw_wlan_start();
        NW_CHK_FAIL_VOID(i4_ret);

        return ;
    }

    if( pt_nw->e_built_in_wlan_status == NW_WLAN_ASSOCIATE
        || pt_nw->e_built_in_wlan_status == NW_WLAN_START_DISASSOC
        || pt_nw->e_built_in_wlan_status == NW_WLAN_ASSOCIATING )
    {
        pt_nw->e_built_in_wlan_status = NW_WLAN_PLUG_STOP;
    }
    if( pt_nw->e_out_wlan_status == NW_WLAN_ASSOCIATE
        || pt_nw->e_out_wlan_status == NW_WLAN_START_DISASSOC
        || pt_nw->e_out_wlan_status == NW_WLAN_ASSOCIATING )
    {
        pt_nw->e_out_wlan_status = NW_WLAN_PLUG_STOP;
    }

    i4_ret = c_net_set_if_type(IF_TYPE_ETHERNET);
    NW_CHK_FAIL_VOID(i4_ret);

    if (pt_nw->b_nw_ethernet_plugin == FALSE)
    {
        return ;
    }

    i4_ret = _nw_start_ip_assoc(NW_NET_INTERFACE_ETH0);
    NW_CHK_FAIL_VOID(i4_ret);

    return ;
}
#else
/**
 * @brief   Handle the ni notify.
 * @param
 * @retval  VOID.
 */
static VOID _nw_ip_ni_wlan_notify_hdlr(VOID* pv_data, SIZE_T z_data_len)
{
    NI_DRV_EV_T e_ev = *((NI_DRV_EV_T*)pv_data);
    NW_NFY_ID_T e_nfy_id = NW_NFY_ID_UNKNOWN;

    NW_UTIL_T*  pt_nw  = &t_g_nw_util;

    DBG_LOG_PRINT(("[NW][%s %d]Handle the ni wifi notify -> %d\n",__FUNCTION__,__LINE__, e_ev));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    switch(e_ev)
    {
        case NI_DRV_EV_WLAN_ASSOC:
        {
            DBG_LOG_PRINT(("[NW_NOTIFY]NI_DRV_EV_WLAN_ASSOC\n"));
            pt_nw->e_wlan_status = NW_WLAN_PLUG_STOP;

            e_nfy_id = NW_NFY_ID_WIRLESS_PLUGIN;
#ifndef DISABLE_TV_WORLD_NW_SETTING
            _nw_wirless_plugin_event_hdlr(); /*for multiinterface no need handle*/
#endif
            break;
        }
        case NI_DRV_EV_WLAN_DISASSOC:
        {
            DBG_LOG_PRINT(("[NW_NOTIFY]NI_DRV_EV_WLAN_DISASSOC\n"));
            pt_nw->e_wlan_status = NW_WLAN_UNPLUG;

            e_nfy_id = NW_NFY_ID_WIRLESS_UNPLUG;
#ifndef DISABLE_TV_WORLD_NW_SETTING
            _nw_wirless_unplug_event_hdlr(); /*for multiinterface no need handle*/
#endif
            break;
        }
        default:
            _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
            return;
    }

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    _nw_msg_brdcast(e_nfy_id, NULL);

    return;
}
/**
 * @brief   Ni notify callback.
 * @param
 * @retval  VOID.
 */
static VOID _nw_ip_ni_wlan_notify_fct(NI_DRV_EV_T e_ev)
{
    DBG_INFO(("[NW]Received ni wifi notify -> %d\n", e_ev));

    a_agent_async_invoke( _nw_ip_ni_wlan_notify_hdlr,
                          (VOID*)&e_ev,
                          sizeof(NI_DRV_EV_T)
                          );
    return;
}

/**
 * @brief   Change the network interface.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_chg_network_interface(UINT8 ui1_interface)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32         i4_ret            = NWR_OK;

    BOOL b_auto_ip_config = TRUE;
    UINT8         ui1_old_interface = pt_nw->ui1_interface;

    DBG_LOG_PRINT(("[NW][%s %d]change the network interface to -> %d b_nw_enabled = %d\n",__FUNCTION__,__LINE__, ui1_interface,pt_nw->b_nw_enabled));

    if(!pt_nw->b_nw_enabled)
    {
        /*When the Network Connection is disable,do nothing.*/
        return NWR_OK;
    }

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
    i4_ret = _nw_dlna_dmr_stop();
    NW_CHK_FAIL(i4_ret);
#endif

    i4_ret = _nw_stop_dlna();
    NW_CHK_FAIL(i4_ret);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    i4_ret = _nw_my_net_pls_stop();
    NW_CHK_FAIL(i4_ret);
#endif

    i4_ret = nw_custom_get_auto_ip_config_by_iface(&b_auto_ip_config, pt_nw->ui1_interface);
    NW_CHK_FAIL(i4_ret);

    if (b_auto_ip_config && (pt_nw->e_dhcp_state != NW_DHCP_STOPPED))
    {
        i4_ret = _nw_stop_dhcp_ip_config();
        NW_CHK_FAIL(i4_ret);
    }

    pt_nw->ui1_interface = ui1_interface;
    pt_nw->ui1_old_interface = ui1_old_interface;

    /* just close  connection if change interface  from wifi to eth0*/
    if ((pt_nw->ui1_old_interface != NW_NET_INTERFACE_ETH0)&&(ui1_interface == NW_NET_INTERFACE_ETH0))
    {
		/*Solution for DTV02870221*/
		if (a_wzd_is_oobe_mode() == TRUE)
		{
		    i4_ret = _nw_wlan_disassociate();
    		NW_LOG_ON_FAIL(i4_ret);
		}
		else
		{
			_nw_wlan_stop();
		}

    }

    if (pt_nw->ui1_interface == NW_NET_INTERFACE_WIFI)
    {
        i4_ret = c_net_set_if_type(IF_TYPE_IEEE80211);
        NW_CHK_FAIL(i4_ret);

        /* only start wlan driver after wireless plugin */
        if (pt_nw->e_wlan_status != NW_WLAN_UNPLUG)
        {
			/*Solution for DTV02870221*/
			if (a_wzd_is_oobe_mode() != TRUE)
			{
			    i4_ret = _nw_wlan_start();
                NW_CHK_FAIL(i4_ret);
			}
        }
    }
    else
    {
        i4_ret = c_net_set_if_type(IF_TYPE_ETHERNET);
        NW_CHK_FAIL(i4_ret);

        if (pt_nw->b_nw_ethernet_plugin == FALSE)
        {
            return NWR_OK;
        }

        i4_ret = _nw_start_ip_assoc(NW_NET_INTERFACE_ETH0);
        NW_CHK_FAIL(i4_ret);
    }

    return NWR_OK;
}
#endif

/**
 *  @brief Associate with a wireless network.
 *  @param pAssociate [in] association settings
 *  @param cbk [in] callback function to notify the association status.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine triggers attempts of connecting to a wireless network according
 *  to the specified settings. After calling this routine, the WLAN
 *  software continues to maintain a network connection according
 *  to the specified settings until c_net_wlan_disassociate() is called.
 */
static INT32 _nw_wlan_associate(NET_802_11_ASSOCIATE_T *pAssociate)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32  i4_ret = NWR_OK;

    NET_802_11_BSSID_T          t_Bssid;
    c_memset(t_Bssid, 0,sizeof(NET_802_11_BSSID_T));

    if (c_memcmp(pAssociate->t_Bssid,t_Bssid,sizeof(NET_802_11_BSSID_T)) == 0)
    {
        DBG_LOG_PRINT(("\n[NW][%s, %s, %d] Wlan associate return\n", __FILE__, __FUNCTION__, __LINE__));
        return NWR_FAIL;
    }
    c_memset(pAssociate->t_Bssid ,0xFF,sizeof(NET_802_11_BSSID_T));

    i4_ret = c_net_wlan_associate(pAssociate,_nw_wlan_notify_fct);
    NW_CHK_FAIL(i4_ret);

#ifdef SUPPORT_2_DONGLES
    if ( pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
    {
        pt_nw->e_built_in_wlan_status = NW_WLAN_ASSOCIATING;
    }
    if ( pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)
    {
        pt_nw->e_out_wlan_status = NW_WLAN_ASSOCIATING;
    }
#else
    pt_nw->e_wlan_status = NW_WLAN_ASSOCIATING;
#endif

    return i4_ret;

}

/**
 *  @brief Disassociate a wireless network connection.
 *  @retval 0 on success, otherwise is failure
 *
 */
static INT32 _nw_wlan_disassociate(VOID)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32  i4_ret = NWR_OK;

#ifndef DISABLE_TV_WORLD_NW_SETTING
    i4_ret = _nw_clean_ip_dns(NW_NET_INTERFACE_WIFI);
    NW_CHK_FAIL(i4_ret);
#endif

#ifdef MW_IPV6_SUPPORT
    i4_ret = c_net_ip_v6_disable(_nw_get_interface_name(NW_NET_INTERFACE_WIFI));/*clear ipv6 address*/
    NW_CHK_FAIL(i4_ret);
#endif
    DBG_LOG_PRINT(("%s %d calling disassociate\n",__FUNCTION__,__LINE__));
    i4_ret = c_net_wlan_disassociate();
    NW_CHK_FAIL(i4_ret);

#ifdef SUPPORT_2_DONGLES
    if ( pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
    {
        DBG_INFO(("[NW] change status line=%d\r\n", __LINE__));
        if(pt_nw->e_built_in_wlan_status != NW_WLAN_UNPLUG)
        {
            pt_nw->e_built_in_wlan_status = NW_WLAN_START_DISASSOC;
        }
    }
    if ( pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)
    {
        DBG_INFO(("[NW] change status line=%d\r\n", __LINE__));
        if(pt_nw->e_out_wlan_status != NW_WLAN_UNPLUG)
        {
            pt_nw->e_out_wlan_status = NW_WLAN_START_DISASSOC;
        }
    }
#else
    pt_nw->e_wlan_status = NW_WLAN_START_DISASSOC;
#endif

    return i4_ret;
}

/**
 *  @brief Cancel WPS registration process.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine tiriggers cancellation of WPS registration process.
 */
INT32 _nw_wlan_wps_cancel(void)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;

#ifdef SUPPORT_2_DONGLES
    if ( pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
    {
        pt_nw->e_built_in_wlan_status = NW_WLAN_START_DISASSOC;
    }
    if ( pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI)
    {
        pt_nw->e_out_wlan_status = NW_WLAN_START_DISASSOC;
    }

#else
    pt_nw->e_wlan_status = NW_WLAN_START_DISASSOC;
#endif

    return c_net_wlan_wps_cancel();
}

#endif

static BOOL disable_nw=0;
INT32 a_nw_disable_network_setting(BOOL flag)
{
     INT32 i4_ret = NWR_OK;
     if(flag==TRUE)
     {
      disable_nw=1;
     }
     else
     {
      disable_nw=0;
     }
     return i4_ret;
}

/**
 * @brief   The network util init.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_init(VOID)
{
    INT32 i4_ret  = NWR_OK;
    NW_UTIL_T*    pt_nw = &t_g_nw_util;
    BOOL          b_network_enabled = FALSE;
    BOOL          b_network_wol_enable = FALSE;

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, b_g_nw_init: %d\n", __FUNCTION__, __LINE__, b_g_nw_init));

    if (b_g_nw_init)
    {
        return NWR_OK;
    }

#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
    pt_nw->e_built_in_wlan_status = NW_WLAN_UNPLUG;
    pt_nw->e_out_wlan_status = NW_WLAN_UNPLUG;
#else
    pt_nw->e_wlan_status = NW_WLAN_UNPLUG;
#endif

    /*Get the interface setting.*/
    i4_ret = nw_custom_get_network_interface(&pt_nw->ui1_interface);
    NW_CHK_FAIL(i4_ret);

#ifdef APP_C4TV_SUPPORT
    /*if user disable wifi, should changed to ethernet only,
      turnkey didn't support now*/
    AP_SYSTEM_CALL("touch /tmp/wifi_enabled");
#endif

#ifndef DISABLE_TV_WORLD_NW_SETTING
    /*register the callback fucntion to wpa.*/
    i4_ret = c_net_wlan_wpa_reg_cbk(_nw_wlan_notify_fct);
    NW_CHK_FAIL(i4_ret);
    /*Init the wlan driver*/
    i4_ret = c_net_wlan_task_create();
    NW_CHK_FAIL(i4_ret);
#endif
#endif

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, i4_ret: %d\n", __FUNCTION__, __LINE__, i4_ret));

    /*get the network info*/
    i4_ret = nw_custom_get_network_enable(&b_network_enabled);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_get_wake_on_lan_enable(&b_network_wol_enable);
    NW_LOG_ON_FAIL(i4_ret);

    if (b_network_enabled)
    {
        pt_nw->b_nw_enabled = TRUE;
    }

    if(b_network_wol_enable)
    {
        c_pcl_set_ethernet_wol_ctrl(PCL_ETHERNET_WOL_ENABLE);
        DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d   set wol to enable \n", __FUNCTION__, __LINE__));
        c_pcl_set_wifi_wol_ctrl(PCL_WIFI_WOL_ENABLE);
        DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d   set wow to enable \n", __FUNCTION__, __LINE__));
    }

    /*init the network MW*/
    i4_ret = c_net_network_init();
    NW_CHK_FAIL(i4_ret);

    /* allocate API mutex */
    i4_ret = c_sema_create(&pt_nw->h_api_mtx,
                        X_SEMA_TYPE_MUTEX,
                        X_SEMA_STATE_UNLOCK);
    if(i4_ret != OSR_OK)
    {
        DBG_LOG_PRINT(("<NW>Can't create API mutex,return %d.\r\n", i4_ret));
        return i4_ret;
    }

    if (0 == disable_nw)
    {
        /*register the callback function.*/
        i4_ret = c_net_ni_reg_ev_notify_ifname(NI_ETHERNET_0, NI_DRV_EV_IP_ADDRESS_CHANGED, _nw_ip_ni_notify_fct);
        NW_CHK_FAIL(i4_ret);
#ifndef DISABLE_TV_WORLD_NW_SETTING
        i4_ret = c_net_ni_reg_ev_notify_ifname(NI_ETHERNET_0, NI_DRV_EV_IP_ADDRESS_EXPIRED, _nw_ip_ni_notify_fct);
        NW_CHK_FAIL(i4_ret);
#endif
        i4_ret = c_net_ni_reg_ev_notify_ifname(NI_ETHERNET_0, NI_DRV_EV_ETHERNET_PLUGIN, _nw_ip_ni_notify_fct);
        NW_CHK_FAIL(i4_ret);
        i4_ret = c_net_ni_reg_ev_notify_ifname(NI_ETHERNET_0, NI_DRV_EV_ETHERNET_UNPLUG, _nw_ip_ni_notify_fct) ;
        NW_CHK_FAIL(i4_ret);
    }

#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
    /* register the notify function for built_int dongle */
    i4_ret = c_net_ni_reg_ev_notify_ifname(NI_WIRELESS_0, NI_DRV_EV_IP_ADDRESS_CHANGED, _nw_ip_ni_notify_fct);
    NW_CHK_FAIL(i4_ret);
#ifndef DISABLE_TV_WORLD_NW_SETTING
    i4_ret = c_net_ni_reg_ev_notify_ifname(NI_WIRELESS_0, NI_DRV_EV_IP_ADDRESS_EXPIRED, _nw_ip_ni_notify_fct);
    NW_CHK_FAIL(i4_ret);
#endif
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_0, NI_DRV_EV_WLAN_ASSOC, _nw_ip_ni_built_in_wlan_notify_fct);
    NW_CHK_FAIL(i4_ret);
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_0, NI_DRV_EV_WLAN_DISASSOC, _nw_ip_ni_built_in_wlan_notify_fct) ;
    NW_CHK_FAIL(i4_ret);

    /* register the notify function for out dongle */
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_1, NI_DRV_EV_IP_ADDRESS_CHANGED, _nw_ip_ni_notify_fct);
    NW_CHK_FAIL(i4_ret);
#ifndef DISABLE_TV_WORLD_NW_SETTING
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_1, NI_DRV_EV_IP_ADDRESS_EXPIRED, _nw_ip_ni_notify_fct);
    NW_CHK_FAIL(i4_ret);

#endif
    i4_ret = c_net_ni_reg_ev_notify_ifname(NI_WIRELESS_1, NI_DRV_EV_WLAN_ASSOC, _nw_ip_ni_out_wlan_notify_fct);
    NW_CHK_FAIL(i4_ret);
    i4_ret = c_net_ni_reg_ev_notify_ifname(NI_WIRELESS_1, NI_DRV_EV_WLAN_DISASSOC, _nw_ip_ni_out_wlan_notify_fct)
    NW_CHK_FAIL(i4_ret);

#else
    i4_ret = c_net_ni_reg_ev_notify_ifname(NI_WIRELESS_0, NI_DRV_EV_IP_ADDRESS_CHANGED, _nw_ip_ni_notify_fct);
    NW_CHK_FAIL(i4_ret);
#ifndef DISABLE_TV_WORLD_NW_SETTING
    i4_ret = c_net_ni_reg_ev_notify_ifname(NI_WIRELESS_0, NI_DRV_EV_IP_ADDRESS_EXPIRED, _nw_ip_ni_notify_fct);
    NW_CHK_FAIL(i4_ret);
#endif
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_0, NI_DRV_EV_WLAN_ASSOC, _nw_ip_ni_wlan_notify_fct);
    NW_CHK_FAIL(i4_ret);
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_0, NI_DRV_EV_WLAN_DISASSOC, _nw_ip_ni_wlan_notify_fct) ;
    NW_CHK_FAIL(i4_ret);
#endif

    i4_ret = c_net_ni_reg_ev_notify_ifname(NI_P2P_0, NI_DRV_EV_IP_ADDRESS_CHANGED, _nw_ip_ni_notify_fct);
    NW_CHK_FAIL(i4_ret);
#ifndef DISABLE_TV_WORLD_NW_SETTING
    i4_ret = c_net_ni_reg_ev_notify_ifname(NI_P2P_0, NI_DRV_EV_IP_ADDRESS_EXPIRED, _nw_ip_ni_notify_fct);
    NW_CHK_FAIL(i4_ret);
#endif
#endif

    pt_nw ->e_dhcp_state = NW_DHCP_STOPPED;

#ifdef APP_NET_DLNA_SUPPORT
    pt_nw ->e_dlna_state = NW_DLNA_STOPPED;
#ifdef APP_DMR_SUPPORT
    pt_nw->e_dlna_dmr_state = NW_DLNA_STOPPED;
#endif
#endif

#ifdef APP_DMS_SUPPORT
    pt_nw->e_dlna_dms_state = NW_DLNA_DMS_STOPPED;
#endif

    DBG_LOG_PRINT(("[KK] %s, LINE: %d, is_ethernet_plugin: %d\n", __FUNCTION__, __LINE__, a_nw_is_ethernet_plugin()));

    /* Network custom init.*/
    i4_ret = nw_custom_init(pt_nw);
    NW_CHK_FAIL(i4_ret);

    /*init the network cli*/
    ui2_nw_dbg_level = DBG_LEVEL_ERROR | DBG_LEVEL_INFO /*DBG_INIT_LEVEL*/;

    i4_ret = nw_cli_init();
    NW_CHK_FAIL(i4_ret);

    b_g_nw_init  = TRUE;

    if (0)
    {
        /*after init network,need to enable network connection*/
        i4_ret = _nw_enable_network_connection(FALSE);
        NW_CHK_FAIL(i4_ret);
    }

    _nw_msg_brdcast(NW_NFY_ID_INITED, NULL);

    DBG_INFO(("[NW]End to init the network\n"));


#ifndef SYS_NETWORK_LAZY_INIT
    // init wifi directly when network init is not delayed
    i4_ret = _nw_wlan_start();
    NW_CHK_FAIL(i4_ret);
#endif

    return NWR_OK;
}

#ifdef SYS_NETWORK_LAZY_INIT
/**
 * @brief   he network delay notify handle.
 * @param
 * @retval  VOID.
 */
static VOID _nw_delay_init_notify_fct(VOID* pv_data, SIZE_T z_data_len)
{
    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, i4_ret: %d\n", __FUNCTION__, __LINE__, 0));
    _nw_init();

    return;
}
/**
 * @brief   The network delay notify callback.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 _network_status_nfy(UINT32 ui4_tag,  NET_COND_T e_cond)
{
    DBG_INFO(("[NW]Received NET_COND_T -> %d\n", e_cond));

    a_agent_async_invoke( _nw_delay_init_notify_fct,
                            (VOID*)&e_cond,
                            sizeof(NET_COND_T)
                          );
    return NWR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 *                  public methods implementations
 *---------------------------------------------------------------------------*/
/**
 * @brief   register network notify callback.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_register( nw_nfy_fct pf_nfy, VOID* pv_tag, UINT32* pui4_nfy_id )
{
    NW_UTIL_T*        pt_nw    = &t_g_nw_util;
    INT32             i4_ret   = 0;
    UINT16            ui2_i    = 0;
    BOOL              b_found  = FALSE;

    MW_UTIL_NFY_CLIENT_T* pt_client = NULL;

    if (pf_nfy == NULL || pui4_nfy_id == NULL)
    {
        return NWR_INV_ARG;
    }

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        /* Find a free slot. */
        for (ui2_i = 0 ;
             ui2_i < (UINT16)NW_MAX_NUM_NOTIFY_CLIENT ;
             ui2_i++)
        {
            if (pt_nw->at_notify_client[ui2_i].pf_notify == NULL)
            {
                b_found = TRUE;
                break;
            }
        }

        /* Not Found */
        if (!b_found)
        {
            i4_ret = NWR_FAIL;
            break;
        }

        /* Save the information into the slot. */
        pt_client = &(pt_nw->at_notify_client[ui2_i]);

        /* usage flag */
        pt_client->pf_notify   = pf_nfy;
        pt_client->pv_tag      = pv_tag;
        pt_client->ui4_nfy_id  = ui2_i;

        /* return out the id */
        *pui4_nfy_id = (UINT32)ui2_i;

        /* Done */
        i4_ret = NWR_OK;
    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
    DBG_LOG_PRINT(("[NW]register the id %d notify.\r\n", *pui4_nfy_id));
    return i4_ret;
}
/**
 * @brief   Unregister a network notify callback which id is ui4_nfy_id.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_unregister( UINT32 ui4_nfy_id )
{
    NW_UTIL_T*             pt_nw     = &t_g_nw_util;
    INT32                  i4_ret    = 0;
    MW_UTIL_NFY_CLIENT_T*  pt_client = NULL;

    DBG_LOG_PRINT(("[NW]Unregister the id %d notify.\r\n", ui4_nfy_id));

    if(ui4_nfy_id >= (UINT32)NW_MAX_NUM_NOTIFY_CLIENT)
    {
        return NWR_INV_ARG;
    }

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        /* Defeult is fail */
        i4_ret = NWR_FAIL;

        /* Load the client's information */
        pt_client = &(pt_nw->at_notify_client[ui4_nfy_id]);

        /* Check usable. */
        if (pt_client->pf_notify == NULL)
        {
            i4_ret = NWR_FAIL;
            break;
        }

        /* Set it to unregister */
        pt_client->pf_notify = NULL;

        /* Done */
        i4_ret = NWR_OK;
    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}

/**
 * @brief   Enable the network.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_enable_network_connection(VOID)
{
    INT32         i4_ret       = 0;
#ifndef DISABLE_TV_WORLD_NW_SETTING
    NW_NFY_ID_T   e_nfy_id     = NW_NFY_ID_UNKNOWN;
    VOID*         pv_nfy_param = NULL;
    NW_UTIL_T*             pt_nw     = &t_g_nw_util;

    DBG_INFO(("[NW]Enable network connection.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        i4_ret = _nw_enable_network_connection(FALSE);
        NW_BREAK_ON_FAIL(i4_ret);

        pt_nw->b_nw_enabled = TRUE;

        i4_ret = nw_custom_set_network_enable(TRUE);
        NW_BREAK_ON_FAIL(i4_ret);

        e_nfy_id = NW_NFY_ID_NETWORK_CONN_ENABLED;

    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    if(i4_ret == NWR_OK)
    {
        _nw_send_event_msg(e_nfy_id, pv_nfy_param);
    }


#endif
    return i4_ret;
}
/**
 * @brief   Disable the network.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_disable_network_connection(VOID)
{
    INT32         i4_ret       = 0;
#ifndef DISABLE_TV_WORLD_NW_SETTING
    NW_NFY_ID_T   e_nfy_id     = NW_NFY_ID_UNKNOWN;
    VOID*         pv_nfy_param = NULL;
    NW_UTIL_T*             pt_nw     = &t_g_nw_util;

    DBG_INFO(("[NW]Disable network connection.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        i4_ret = _nw_disable_network_connection(FALSE);
        NW_BREAK_ON_FAIL(i4_ret);

        pt_nw->b_nw_enabled = FALSE;

        i4_ret = nw_custom_set_network_enable(FALSE);
        NW_BREAK_ON_FAIL(i4_ret);

        e_nfy_id = NW_NFY_ID_NETWORK_CONN_DISABLED;

    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    if(i4_ret == NWR_OK)
    {
        _nw_send_event_msg(e_nfy_id, pv_nfy_param);
    }


#endif
    return i4_ret;
}
/**
 * @brief   Enable the internet connection manually.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_manual_ip_config(const NW_IP_INFO_T* pt_ip_info)
{
    INT32 i4_ret  = NWR_OK;
    BOOL b_auto_ip_config = TRUE;
    NW_UTIL_T* pt_nw    = &t_g_nw_util;

#ifdef APP_NET_DLNA_SUPPORT
    BOOL          b_dlna_enable     = FALSE;
#ifdef APP_DMR_SUPPORT
 //   BOOL          b_dlna_dmr_enalbe = FALSE;
#endif
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
    BOOL          b_my_net_pls_enable = FALSE;
#endif

    if (pt_ip_info == NULL)
    {
        return NWR_INV_ARG;
    }

    DBG_LOG_PRINT(("[NW]Manual ip config setting.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        if (!pt_nw->b_nw_enabled)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }

        i4_ret = _nw_validate_ip_config( pt_ip_info);
        NW_BREAK_ON_FAIL(i4_ret);

        DBG_LOG_PRINT(("[NW]_nw_validate_ip_config OK\r\n"));

        i4_ret = nw_custom_get_auto_ip_config_by_iface(&b_auto_ip_config, pt_nw->ui1_interface);
        NW_BREAK_ON_FAIL(i4_ret);

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
        i4_ret = _nw_dlna_dmr_stop();
        NW_BREAK_ON_FAIL(i4_ret);
#endif
        i4_ret = _nw_stop_dlna();
        NW_BREAK_ON_FAIL(i4_ret);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
        i4_ret = _nw_my_net_pls_stop();
        NW_BREAK_ON_FAIL(i4_ret);
#endif

        if (b_auto_ip_config && (pt_nw->e_dhcp_state != NW_DHCP_STOPPED))
        {
            i4_ret = _nw_stop_dhcp_ip_config();
            NW_BREAK_ON_FAIL(i4_ret);
        }

        i4_ret = _nw_manual_ip_config(pt_ip_info);
        NW_LOG_ON_FAIL(i4_ret);
        //TODO: NW_BREAK_ON_FAIL(i4_ret);

#ifdef APP_NET_DLNA_SUPPORT
        i4_ret = nw_custom_get_dlna_enable(&b_dlna_enable);
        NW_BREAK_ON_FAIL(i4_ret);

        if (b_dlna_enable)
        {
            i4_ret = _nw_start_dlna();
            NW_BREAK_ON_FAIL(i4_ret);
        }
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
        i4_ret = nw_custom_get_my_net_pls_enable(&b_my_net_pls_enable);
        NW_BREAK_ON_FAIL(i4_ret);

        if (b_my_net_pls_enable)
        {
            i4_ret = _nw_my_net_pls_start();
            NW_BREAK_ON_FAIL(i4_ret);
        }
#endif

        i4_ret = nw_custom_set_auto_ip_config_by_iface(FALSE, pt_nw->ui1_interface);
        NW_BREAK_ON_FAIL(i4_ret);

        i4_ret = nw_custom_set_ip_addr_config_by_iface(pt_ip_info, pt_nw->ui1_interface);
        NW_BREAK_ON_FAIL(i4_ret);

    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}

/**
 * @brief   Enable the internet connection automatically(DHCP).
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_start_dhcp_ip_config (VOID)
{
    INT32 i4_ret = NWR_OK;
    NW_UTIL_T* pt_nw = &t_g_nw_util;

    DBG_INFO(("[NW]Start DHCP.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        if (!pt_nw->b_nw_enabled)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }

        if (_nw_is_tv_link_router() == FALSE)
        {
            i4_ret = nw_custom_set_auto_ip_config_by_iface(TRUE, pt_nw->ui1_interface);
            NW_BREAK_ON_FAIL(i4_ret);
        }
        else
        {
#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
            i4_ret = _nw_dlna_dmr_stop();
            NW_BREAK_ON_FAIL(i4_ret);
#endif
            i4_ret = _nw_stop_dlna();
            NW_BREAK_ON_FAIL(i4_ret);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
            i4_ret = _nw_my_net_pls_stop();
            NW_BREAK_ON_FAIL(i4_ret);
#endif

            i4_ret = _nw_start_dhcp_ip_config();
            NW_BREAK_ON_FAIL(i4_ret);

            i4_ret = nw_custom_set_auto_ip_config_by_iface(TRUE, pt_nw->ui1_interface);
            NW_BREAK_ON_FAIL(i4_ret);
        }
    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}
/**
 * @brief   Diable DHCP.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_stop_dhcp_ip_config(VOID)
{
    INT32 i4_ret = NWR_OK;
    NW_NFY_ID_T   e_nfy_id     = NW_NFY_ID_UNKNOWN;
    VOID*         pv_nfy_param = NULL;
    NW_UTIL_T* pt_nw = &t_g_nw_util;

    DBG_INFO(("[NW]Stop DHCP.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        if (!pt_nw->b_nw_enabled)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }

#ifdef APP_NET_DLNA_SUPPORT
#ifdef APP_DMR_SUPPORT
        i4_ret = _nw_dlna_dmr_stop();
        NW_BREAK_ON_FAIL(i4_ret);
#endif
        i4_ret = _nw_stop_dlna();
        NW_BREAK_ON_FAIL(i4_ret);
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
        i4_ret = _nw_my_net_pls_stop();
        NW_BREAK_ON_FAIL(i4_ret);
#endif

        if(pt_nw->e_dhcp_state != NW_DHCP_STOPPED)
        {
            i4_ret = _nw_stop_dhcp_ip_config();
            NW_BREAK_ON_FAIL(i4_ret);
        }

        e_nfy_id = NW_NFY_ID_DHCP_STOPPED;
    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    if(i4_ret == NWR_OK)
    {
        _nw_send_event_msg(e_nfy_id, pv_nfy_param);
    }

    return i4_ret;
}

#define DUMP_ADDR(prefix,addr) \
do{\
    DBG_LOG_PRINT(("%s:%d.%d.%d.%d\n",prefix,(addr&0xff),(addr&0xff00)>>8,(addr&0xff0000)>>16,(addr&0xff000000)>>24));\
}while(0)


INT32 a_nw_get_ip_info(NW_IP_INFO_T* pt_ip_info, CHAR* ps_if_name)
{
    NW_UTIL_T*          pt_nw = &t_g_nw_util;
    INT32               i4_ret = NWR_OK;
    MT_DHCP4_INFO_T     t_dhcp_info = {0};
    UINT8               ui1_iface = 0;

    if (pt_ip_info == NULL || ps_if_name == NULL)
    {
        return NWR_INV_ARG;
    }

    DBG_INFO(("[NW]Get current IP info.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    if (0 == c_strcmp(ps_if_name, NI_ETHERNET_0))
    {
        ui1_iface = NW_NET_INTERFACE_ETH0;
    }
    else
    {
        ui1_iface = NW_NET_INTERFACE_WIFI;
    }

    memset(pt_ip_info, 0, sizeof(NW_IP_INFO_T));

#ifndef DISABLE_TV_WORLD_NW_SETTING
    do
    {
        BOOL  b_auto_ip_config = FALSE;
        i4_ret = nw_custom_get_auto_ip_config_by_iface(&b_auto_ip_config, ui1_iface);
        NW_BREAK_ON_FAIL(i4_ret);

        if (b_auto_ip_config)
        {
            if (!pt_nw->b_nw_enabled)
            {
                i4_ret = NWR_DHCP_NO_ADDR;
                break;
            }

            if (_nw_is_tv_link_router() == FALSE)
            {
                i4_ret = NWR_DHCP_NO_ADDR;
                break;
            }

            memset(&t_dhcp_info, 0, sizeof(MT_DHCP4_INFO_T));
            i4_ret = c_dhcpc_get_info(ps_if_name, &t_dhcp_info);
            if(i4_ret != NWR_OK)
            {
                i4_ret = NWR_DHCP_NO_ADDR;
                break;
            }

            pt_ip_info->ui4_address = t_dhcp_info.ui4_ipaddr;
            pt_ip_info->ui4_netmask = t_dhcp_info.ui4_subnet;
            pt_ip_info->ui4_gw      = t_dhcp_info.ui4_router;
            pt_ip_info->ui4_1st_dns = t_dhcp_info.ui4_dns1;
            pt_ip_info->ui4_2nd_dns = t_dhcp_info.ui4_dns2;
            DBG_INFO(("[NW]Auto Ip info is : ip %d  - mask %d - dns1 - %d - dns2 -%d of interface %s\n",
                pt_ip_info->ui4_address,pt_ip_info->ui4_netmask,pt_ip_info->ui4_1st_dns,pt_ip_info->ui4_2nd_dns,ps_if_name));
        }
        else
        {
            i4_ret = nw_custom_get_ip_addr_config_by_iface(pt_ip_info, ui1_iface);
            DBG_INFO(("[NW]Manual Ip info is : ip %d  - mask %d - dns1 - %d - dns2 -%d of interface %s\n",
                pt_ip_info->ui4_address,pt_ip_info->ui4_netmask,pt_ip_info->ui4_1st_dns,pt_ip_info->ui4_2nd_dns,ps_if_name));
            NW_BREAK_ON_FAIL(i4_ret);
        }

    } while(0);
    #else
    memset(&t_dhcp_info, 0, sizeof(MT_DHCP4_INFO_T));
    i4_ret = c_dhcpc_get_info(ps_if_name, &t_dhcp_info);
    if(i4_ret != NWR_OK)
    {
        i4_ret = NWR_DHCP_NO_ADDR;
    }

    pt_ip_info->ui4_address = t_dhcp_info.ui4_ipaddr;
    pt_ip_info->ui4_netmask = t_dhcp_info.ui4_subnet;
    pt_ip_info->ui4_gw      = t_dhcp_info.ui4_router;
    pt_ip_info->ui4_1st_dns = t_dhcp_info.ui4_dns1;
    pt_ip_info->ui4_2nd_dns = t_dhcp_info.ui4_dns2;
    DBG_INFO(("[NW]Auto Ip info is : ip %d  - mask %d - dns1 - %d - dns2 -%d of interface %s\n",
        pt_ip_info->ui4_address,pt_ip_info->ui4_netmask,pt_ip_info->ui4_1st_dns,pt_ip_info->ui4_2nd_dns,ps_if_name));
    #endif

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
 }

/**
 * @brief   Get current IP info.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_get_crnt_ip_info( NW_IP_INFO_T* pt_ip_info )
{
    NW_UTIL_T*          pt_nw = &t_g_nw_util;
    INT32               i4_ret = NWR_OK;
    MT_DHCP4_INFO_T     t_dhcp_info = {0};

    if (pt_ip_info == NULL)
    {
        return NWR_INV_ARG;
    }

    DBG_LOG_PRINT(("[NW]Get current IP info.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
    memset(pt_ip_info, 0, sizeof(NW_IP_INFO_T));
#ifndef DISABLE_TV_WORLD_NW_SETTING
    do
    {
        BOOL  b_auto_ip_config = FALSE;
        i4_ret = nw_custom_get_auto_ip_config_by_iface(&b_auto_ip_config, pt_nw->ui1_interface);
        NW_BREAK_ON_FAIL(i4_ret);
        DBG_LOG_PRINT(("[NW]Get current IP info  b_auto_ip_config : %d,ui1_interface : %d.\r\n",b_auto_ip_config,pt_nw->ui1_interface));

        if (b_auto_ip_config)
        {
            if (!pt_nw->b_nw_enabled)
            {
                i4_ret = NWR_DHCP_NO_ADDR;
                break;
            }

            if (_nw_is_tv_link_router() == FALSE)
            {
                i4_ret = NWR_DHCP_NO_ADDR;
                break;
            }

            memset(&t_dhcp_info, 0, sizeof(MT_DHCP4_INFO_T));
            i4_ret = c_dhcpc_get_info(_nw_get_interface_name(pt_nw->ui1_interface), &t_dhcp_info);
            if(i4_ret != NWR_OK)
            {
                i4_ret = NWR_DHCP_NO_ADDR;
                break;
            }

            pt_ip_info->ui4_address = t_dhcp_info.ui4_ipaddr;
            pt_ip_info->ui4_netmask = t_dhcp_info.ui4_subnet;
            pt_ip_info->ui4_gw      = t_dhcp_info.ui4_router;
            pt_ip_info->ui4_1st_dns = t_dhcp_info.ui4_dns1;
            pt_ip_info->ui4_2nd_dns = t_dhcp_info.ui4_dns2;
            DBG_LOG_PRINT(("[NW]Auto Ip info is :  interface %s\n",_nw_get_interface_name(pt_nw->ui1_interface)));

            DUMP_ADDR("ip",pt_ip_info->ui4_address);
            DUMP_ADDR("mask",pt_ip_info->ui4_netmask);
            DUMP_ADDR("gateway",pt_ip_info->ui4_gw);
            DUMP_ADDR("dns1",pt_ip_info->ui4_1st_dns);
            DUMP_ADDR("dns2",pt_ip_info->ui4_2nd_dns);
            nw_custom_set_ip_addr_config_by_iface(pt_ip_info,pt_nw->ui1_interface);
        }
        else
        {
            i4_ret = nw_custom_get_ip_addr_config_by_iface(pt_ip_info, pt_nw->ui1_interface);
            DBG_LOG_PRINT(("[NW]Manual Ip info is : of interface %s\n",_nw_get_interface_name(pt_nw->ui1_interface)));
            DUMP_ADDR("ip",pt_ip_info->ui4_address);
            DUMP_ADDR("mask",pt_ip_info->ui4_netmask);
            DUMP_ADDR("gateway",pt_ip_info->ui4_gw);
            DUMP_ADDR("dns1",pt_ip_info->ui4_1st_dns);
            DUMP_ADDR("dns2",pt_ip_info->ui4_2nd_dns);
            NW_BREAK_ON_FAIL(i4_ret);
        }

    } while(0);
#else
    memset(&t_dhcp_info, 0, sizeof(MT_DHCP4_INFO_T));
    i4_ret = c_dhcpc_get_info(_nw_get_interface_name(pt_nw->ui1_interface), &t_dhcp_info);
    if(i4_ret != NWR_OK)
    {
        i4_ret = NWR_DHCP_NO_ADDR;
    }

    pt_ip_info->ui4_address = t_dhcp_info.ui4_ipaddr;
    pt_ip_info->ui4_netmask = t_dhcp_info.ui4_subnet;
    pt_ip_info->ui4_gw      = t_dhcp_info.ui4_router;
    pt_ip_info->ui4_1st_dns = t_dhcp_info.ui4_dns1;
    pt_ip_info->ui4_2nd_dns = t_dhcp_info.ui4_dns2;
    DBG_INFO(("[NW]Auto Ip info is : ip %d  - mask %d - dns1 - %d - dns2 -%d of interface %s\n",
        pt_ip_info->ui4_address,pt_ip_info->ui4_netmask,pt_ip_info->ui4_1st_dns,pt_ip_info->ui4_2nd_dns,_nw_get_interface_name(pt_nw->ui1_interface)));
#endif
    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}
/**
 * @brief   Get current DHCP status..
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_get_dhcp_status( NW_DHCP_STATE_T* pe_dhcp_state )
{
    DBG_INFO(("[NW]Get current DHCP status.\r\n"));

    if (pe_dhcp_state == NULL)
    {
        return NWR_INV_ARG;
    }

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    *pe_dhcp_state = t_g_nw_util.e_dhcp_state;

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return NWR_OK;
}

#ifdef LINUX_TURNKEY_SOLUTION
/**
 * @brief   _mw_connect_test_thread.
 * @param
 * @retval  VOID.
 * @entry of _mw_connection_test_process_async
 */

void* _connect_test_async_thread(void* pv_data)
{
    pthread_detach(pthread_self());
    _mw_connection_test_process(pv_data, 0);
    return NULL;
}

/**
 * @brief   _mw_connection_test_process_async.
 * @param
 * @retval  VOID.
 * @create a thread to do _mw_connection_test_process
 */
static VOID _mw_connection_test_async(VOID* pv_data, SIZE_T z_data_len)
{
    int           ret = 0;
    pthread_t h_thread = {0};


    ret = pthread_create(&h_thread,NULL,_connect_test_async_thread, pv_data);
    if(ret != 0)
        DBG_LOG_PRINT(("[NW]--- create thread fail, reason : %d \n----", ret));
    return;
}

#endif
/**
 * @brief   To test the network connection.
 * @param   af_family :
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  _nw_connection_test(CHAR* hostname, int af_family)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;
    int v_af_family = af_family;

    if((af_family == AF_INET)||(af_family == AF_INET6))
        v_af_family = af_family;
    else
        v_af_family = AF_INET;

    DBG_INFO(("[NW]Connection test, family = %d\r\n", af_family));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        if (!pt_nw->b_nw_enabled)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }

#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
        if (( pt_nw->ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI
             && pt_nw->e_built_in_wlan_status != NW_WLAN_ASSOCIATE )
             ||(pt_nw->ui1_interface == NW_NET_INTERFACE_OUT_WIFI
             && pt_nw->e_out_wlan_status != NW_WLAN_ASSOCIATE))
        {
                i4_ret = NWR_WIFI_UNASOCCIATE;
                break;
        }
        else
#else
        if (pt_nw->ui1_interface != NW_NET_INTERFACE_ETH0 && FALSE == a_nw_is_ethernet_plugin())
        {
            if (pt_nw->e_wlan_status != NW_WLAN_ASSOCIATE)
            {
                i4_ret = NWR_WIFI_UNASOCCIATE;
                break;
            }
        }
        else
#endif
#endif
        {
            if (!pt_nw->b_nw_ethernet_plugin)
            {
                i4_ret = NWR_ETHERNET_UNPLUG;
                break;
            }
        }


        if (hostname == NULL)
        {
            i4_ret = NWR_INV_ARG;
            break;
        }

        if(pt_nw->s_test_hostname != NULL)
        {
            c_mem_free(pt_nw->s_test_hostname);
            pt_nw->s_test_hostname = NULL;
        }
        pt_nw->s_test_hostname = (CHAR*)c_mem_alloc(sizeof(CHAR)*(c_strlen(hostname)+1));
        if(pt_nw->s_test_hostname != NULL)
        {
            c_strcpy(pt_nw->s_test_hostname, hostname);
#ifdef LINUX_TURNKEY_SOLUTION
            i4_ret = a_agent_async_invoke( _mw_connection_test_async,&v_af_family, sizeof(int));
#else
            i4_ret = a_agent_async_invoke( _mw_connection_test_process,&v_af_family, sizeof(int));
#endif
            if (i4_ret!= AGENTR_OK)
            {
                c_mem_free(pt_nw->s_test_hostname);
                pt_nw->s_test_hostname = NULL;
            }
        }

    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}

INT32  a_nw_connection_test(CHAR* hostname)
{
    return _nw_connection_test(hostname, AF_INET);
}

INT32  a_nw_connection_test6(CHAR* hostname)
{
    return _nw_connection_test(hostname, AF_INET6);
}


INT32  a_nw_set_ipv6_all_config()
{
#ifdef MW_IPV6_SUPPORT
    return _nw_set_ipv6_all_config();
#else
    return NWR_FAIL;
#endif
}


INT32  a_nw_no_ipv6_config()
{
#ifdef MW_IPV6_SUPPORT
    return c_net_ni_rmv6config_all(_nw_get_interface_name(t_g_nw_util.ui1_interface));
#else
    return NWR_FAIL;
#endif
}



INT32   _nw_set_ipv6_all_config()
{
#ifdef MW_IPV6_SUPPORT
    BOOL          b_ipv6_auto_enable = TRUE;
    BOOL          b_ipv6_dns_enable = TRUE;
    BOOL          b_ipv6_prefer = TRUE;
    BOOL          i4_ret = TRUE;
    NW_IPV6_INFO_T t_ipv6_info;
    DBG_INFO(("[NW]%s - %d.\r\n", __FUNCTION__,__LINE__));
    i4_ret = c_net_ni_rmv6config_all(_nw_get_interface_name(t_g_nw_util.ui1_interface));
    NW_CHK_FAIL(i4_ret);
    i4_ret = a_cfg_get_ipv6_prefer(&b_ipv6_prefer);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }
    i4_ret = c_net_set_prefer_v6(b_ipv6_prefer);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }
    i4_ret = a_cfg_get_ipv6_state_config(&b_ipv6_auto_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }
    i4_ret = a_cfg_get_ipv6_auto_dns_config(&b_ipv6_dns_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }
    c_memset(&t_ipv6_info, 0,sizeof(NW_IPV6_INFO_T));
    i4_ret = a_nw_get_ipv6_config(&t_ipv6_info);
    NW_CHK_FAIL(i4_ret);
    if (IPV6_CONFIG_MANUAL == b_ipv6_auto_enable)
    {
        i4_ret = _nw_manual_ipv6_nodns_config(_nw_get_interface_name(t_g_nw_util.ui1_interface), (NW_IPV6_INFO_T_NO_DNS *)&t_ipv6_info);
        NW_CHK_FAIL(i4_ret);
    }
    else if(IPV6_CONFIG_RA == b_ipv6_auto_enable)
    {
        i4_ret = c_net_ip_v6_auto(_nw_get_interface_name(t_g_nw_util.ui1_interface),1,1);
        NW_CHK_FAIL(i4_ret);
    }
    else if(IPV6_CONFIG_STATEFUL == b_ipv6_auto_enable)
    {
        i4_ret = c_net_ip_v6_dhcp(_nw_get_interface_name(t_g_nw_util.ui1_interface),1, b_ipv6_dns_enable);
        NW_CHK_FAIL(i4_ret);
    }
    if(IPV6_CONFIG_MANUAL == b_ipv6_dns_enable)
    {
        i4_ret = c_net_dns_v6_config(t_ipv6_info.ac_dns1, t_ipv6_info.ac_dns2);
        NW_CHK_FAIL(i4_ret);
    }
    return NWR_OK;
#else
    return NWR_FAIL;
#endif
}
/**
 * @brief   validate the ip config info(exp. host number shoud not be full zero and 1) .
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_validate_ipv6_config(NW_IPV6_INFO_T_NO_DNS * p_tip_info)
{
    return NWR_OK;
}

/**
 * @brief   Enable the internet  ipv6 without dns connection manually.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_manual_ipv6_nodns_config(CHAR *psz_name, NW_IPV6_INFO_T_NO_DNS * p_tip_info)
{
#ifdef MW_IPV6_SUPPORT
    INT32 i4_ret;

    i4_ret = _nw_validate_ipv6_config(p_tip_info);
    NW_CHK_FAIL(i4_ret);
    i4_ret = c_net_ip_v6_config(psz_name, p_tip_info->ui4_prefix,p_tip_info->ac_v6ip,p_tip_info->ac_v6gw);
    NW_CHK_FAIL(i4_ret);

    return i4_ret;
#else
    return NWR_FAIL;
#endif
}
/**
 * @brief   Enable the internet  ipv6 without dns connection manually.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32  _nw_manual_ipv6_config(CHAR *psz_name, NW_IPV6_INFO_T * p_tip_info)
{
#ifdef MW_IPV6_SUPPORT
    INT32 i4_ret;

    i4_ret = c_net_ip_v6_config(psz_name, p_tip_info->ui4_prefix,p_tip_info->ac_v6ip,p_tip_info->ac_v6gw);
    NW_CHK_FAIL(i4_ret);

    i4_ret = a_nw_dns_v6_config(p_tip_info->ac_dns1, p_tip_info->ac_dns2);
    NW_CHK_FAIL(i4_ret);

    return i4_ret;
#else
    return NWR_FAIL;
#endif
}


/**
 * @brief   Set the network IPV6 without dns config (write the eeprom).
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  _nw_set_ipv6_nodns_acfg(const NW_IPV6_INFO_T_NO_DNS *p_tip_info)
{
#ifdef MW_IPV6_SUPPORT
    INT32    i4_ret = 0;

    if (p_tip_info == NULL)
    {
        return NWR_INV_ARG;
    }

    i4_ret = a_cfg_set_ipv6_addr((UINT8*)p_tip_info->ac_v6ip);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    i4_ret = a_cfg_set_ipv6_gw((UINT8*)p_tip_info->ac_v6gw);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    i4_ret = a_cfg_set_ipv6_prefix((UINT8)p_tip_info->ui4_prefix);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
#else
    return NWR_FAIL;
#endif
}

/**
 * @brief   Set the network IPV6 with dns info config (read the eeprom).
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32   a_nw_get_ipv6_config(NW_IPV6_INFO_T* pt_ip_info)
{
#ifdef MW_IPV6_SUPPORT
    INT32    i4_ret = 0;
    CHAR tem_str[MAX_IPV6_IP_LENGTH] = {0};

    if (pt_ip_info == NULL)
    {
        return NWR_INV_ARG;
    }

    //ipv6 info
    memset(tem_str,0,MAX_IPV6_IP_LENGTH);
    i4_ret = a_cfg_get_ipv6_addr((UINT8*)tem_str);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }
    c_strncpy(pt_ip_info->ac_v6ip, tem_str, MAX_IPV6_IP_LENGTH);


    //ipv6 gateway
    memset(tem_str,0,MAX_IPV6_IP_LENGTH);
    i4_ret = a_cfg_get_ipv6_gw((UINT8*)tem_str);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }
    c_strncpy(pt_ip_info->ac_v6gw, tem_str, MAX_IPV6_IP_LENGTH);

    //ipv6 dns1
    memset(tem_str,0,MAX_IPV6_IP_LENGTH);
    i4_ret = a_cfg_get_ipv6_dns1((UINT8*)tem_str);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }
    c_strncpy(pt_ip_info->ac_dns1, tem_str, MAX_IPV6_IP_LENGTH-1);


    //ipv6 dns2
    memset(tem_str,0,MAX_IPV6_IP_LENGTH);
    i4_ret = a_cfg_get_ipv6_dns2((UINT8*)tem_str);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }
    c_strncpy(pt_ip_info->ac_dns2, tem_str, MAX_IPV6_IP_LENGTH-1);
    DBG_LOG_PRINT(("After c_strncpy @@@@@@@@@@@@@:get dns2: %45s\n",pt_ip_info->ac_dns2));

    //ipv6 prefix
    i4_ret = a_cfg_get_ipv6_prefix((UINT8 *)(&(pt_ip_info->ui4_prefix)));
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return NWR_OK;
#else
    return NWR_FAIL;
#endif
}
/*!
 * @brief manually configure IPv6 address and default gateway
 *
 */
INT32 a_nw_ip_v6_config(NW_IPV6_INFO_T_NO_DNS *p_tip_info)
{
    return 0;
}

INT32 a_nw_set_ip_v6_config(INT32 ip_type, INT32 dns_type, NW_IPV6_INFO_T *p_tip_info)
{
#ifdef MW_IPV6_SUPPORT
    INT32 i4_ret  = NWR_OK;

    i4_ret = c_net_ni_rmv6config_all(_nw_get_interface_name(t_g_nw_util.ui1_interface));
    NW_CHK_FAIL(i4_ret);


    DBG_INFO(("[NW]Manual ipv6 config setting.\r\n"));



    if (IPV6_CONFIG_MANUAL == ip_type)
    {
            if(NULL == p_tip_info)
                return NWR_INV_ARG;
            i4_ret = _nw_manual_ipv6_nodns_config(_nw_get_interface_name(t_g_nw_util.ui1_interface), (NW_IPV6_INFO_T_NO_DNS *)p_tip_info);

            NW_CHK_FAIL(i4_ret);

            _nw_set_ipv6_nodns_acfg((NW_IPV6_INFO_T_NO_DNS*)p_tip_info);



            if(IPV6_CONFIG_MANUAL != dns_type)
                a_nw_dns_v6_auto(dns_type);

    }
    else if(IPV6_CONFIG_RA == ip_type)
    {
        i4_ret = c_net_ip_v6_auto(_nw_get_interface_name(t_g_nw_util.ui1_interface),1,dns_type);
        NW_CHK_FAIL(i4_ret);

    }
    else if(IPV6_CONFIG_STATEFUL == ip_type)
    {


        i4_ret = c_net_ip_v6_dhcp(_nw_get_interface_name(t_g_nw_util.ui1_interface),1, dns_type);
        NW_CHK_FAIL(i4_ret);

     }

    if(IPV6_CONFIG_MANUAL == dns_type)
    {
        if(NULL == p_tip_info)
            return NWR_INV_ARG;
        i4_ret = a_nw_dns_v6_config(p_tip_info->ac_dns1, p_tip_info->ac_dns2);
        NW_CHK_FAIL(i4_ret);
     }

    a_cfg_set_ipv6_state_config(ip_type);

    a_cfg_set_ipv6_auto_dns_config(dns_type);

    return i4_ret;
#else
    return NWR_FAIL;
#endif
}


/*!
 * @brief manually configure IPv6 DNS
 *
 */
INT32 a_nw_dns_v6_config(CHAR* pc_dns1, CHAR* pc_dns2)
{
#ifdef MW_IPV6_SUPPORT
    INT32 i4_ret  = NWR_OK;

    if ((pc_dns1 == NULL)||(pc_dns2 == NULL))
    {
        return NWR_INV_ARG;
    }
    DBG_INFO(("[NW]call %s - %d,dns %s - %s\n", __FUNCTION__, __LINE__, pc_dns1,pc_dns2));

    if(!strlen(pc_dns1) && !strlen(pc_dns2))
        return NWR_OK;

    c_net_clean_dns_cache();

    i4_ret = c_net_dns_v6_config(pc_dns1,  pc_dns2);
    NW_CHK_FAIL(i4_ret);

    //write the dns info to eeprom
    i4_ret = a_cfg_set_ipv6_dns1((UINT8*)pc_dns1);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }
    i4_ret = a_cfg_set_ipv6_dns2((UINT8*)pc_dns2);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    i4_ret = a_cfg_set_ipv6_auto_dns_config(FALSE);
    NW_CHK_FAIL(i4_ret);

    return i4_ret;
#else
    return NWR_FAIL;
#endif
}
/*!
 * @brief set IPv6 address type ( [manual/stateless/stateful]  IP autoconfiguration)
 *
 */
INT32 a_nw_ip_v6_auto(int type, BOOL b_restart_if)
{
#ifdef MW_IPV6_SUPPORT
    INT32 i4_ret  = NWR_OK;
    DBG_INFO(("[NW]Call %s, line is %d -- %d - %d\n", __FUNCTION__, __LINE__,type, b_restart_if));

    i4_ret = c_net_ni_rmv6config_all(_nw_get_interface_name(t_g_nw_util.ui1_interface));
        NW_CHK_FAIL(i4_ret);

    if(type == IPV6_CONFIG_RA)
    {
        i4_ret = c_net_ip_v6_auto(_nw_get_interface_name(t_g_nw_util.ui1_interface), 1, b_restart_if);
        NW_CHK_FAIL(i4_ret);
    }
    else if(type == IPV6_CONFIG_STATEFUL)
    {
        i4_ret = c_net_ip_v6_dhcp(_nw_get_interface_name(t_g_nw_util.ui1_interface), 1, 1);
        NW_CHK_FAIL(i4_ret);
    }

    //write the ipv6 auto config to eeprom
    i4_ret = a_cfg_set_ipv6_state_config(type);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return i4_ret;
#else
    return NWR_FAIL;
#endif
}
/*!
 * @brief enable/disable DHCPv6 to require IPv6 address (stateful autoconfiguration)
 *
 */
INT32 a_nw_ip_v6_dhcp(BOOL b_enable)
{
#ifdef MW_IPV6_SUPPORT
    INT32 i4_ret  = NWR_OK;
    DBG_INFO(("[NW]Call %s, line is %d -- %d\n", __FUNCTION__, __LINE__, b_enable));

    i4_ret = c_net_ip_v6_dhcp(_nw_get_interface_name(t_g_nw_util.ui1_interface), 1, 1);
    NW_CHK_FAIL(i4_ret);

    return i4_ret;
#else
    return NWR_FAIL;
#endif
}

/*!
 * @brief enable/disable auto DNS)
 *
 */
INT32 a_nw_dns_v6_auto(BOOL b_enable)
{
#ifdef MW_IPV6_SUPPORT
    INT32 i4_ret  = NWR_OK;
    DBG_INFO(("[NW]call %s - %d,enable %d\n", __FUNCTION__, __LINE__, b_enable));
    i4_ret = c_net_dns_v6_auto(_nw_get_interface_name(t_g_nw_util.ui1_interface), b_enable);
    NW_CHK_FAIL(i4_ret);

    //write the ipv6 auto config to eeprom
    i4_ret = a_cfg_set_ipv6_auto_dns_config(b_enable);
    if(i4_ret != APP_CFGR_OK)
    {
        return NWR_FAIL;
    }

    return i4_ret;
#else
    return NWR_FAIL;
#endif
}
/*!
 * @brief ping utility, user may use this API to verify remote host is online or not.
 * @param in ps_ip     - dot format IPv4 address string, ex "192.168.1.1"
 * @param in i2_len    - payload size (send data size)
 * @param in i2_wait   - maximum wait time (in seconds)
 * @param in notify_fn - notify callback
 */
VOID a_nw_ping_v6(CHAR * ps_ip,
                          INT32  i4_len,
                          INT16  i2_wait,
                          VOID (*notify_fn) (INT16 i2_rsp_time))
{
#ifdef MW_IPV6_SUPPORT
    if (ps_ip == NULL)
    {
        DBG_INFO(("[NW]The pingv6's ip is invalid!!.\r\n"));
        return ;
    }

    c_net_ping_v6(ps_ip, i4_len,i2_wait,notify_fn);
#else
#endif
}

INT32 a_nw_get_v6_info(NW_IPV6_INFO_T *pt_info)
{
#ifdef MW_IPV6_SUPPORT

    if (pt_info == NULL)
    {
        return NWR_INV_ARG;
    }

    return c_net_get_v6_info(_nw_get_interface_name(t_g_nw_util.ui1_interface), (MT_IPV6_INFO_T *)pt_info);
#else
    return NWR_FAIL;
#endif
}

INT32 a_nw_set_prefer_v6(BOOL b_isv6)
{
#ifdef MW_IPV6_SUPPORT
    int i4_ret =0;
    //write the ipv6 auto config to eeprom
    DBG_INFO(("[NW]Call %s, line is %d\n", __FUNCTION__, __LINE__));

    i4_ret =  c_net_set_prefer_v6(b_isv6);
  if(i4_ret != APP_CFGR_OK)
  {
        DBG_ERROR(("[NW] %s fail, line is %d\n", __FUNCTION__, __LINE__));
      return NWR_FAIL;
  }
    return a_cfg_set_ipv6_prefer(b_isv6);
#else
    return NWR_FAIL;
#endif
}


#ifdef APP_DMS_SUPPORT
/**
 * @brief   Enable DLNA DMS.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_enable_dlna_dms(VOID)
{
    //NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;

    DBG_INFO(("[NW]Enable DMS.\n"));

    _mw_lock();
    DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        if (_nw_is_tv_link_router() != FALSE)
        {
            i4_ret = _nw_dlna_dms_start();
            NW_BREAK_ON_FAIL(i4_ret);
        }
        DBG_INFO(("[NW]%s %d\n", __func__, __LINE__));
        i4_ret = nw_custom_set_dlna_dms_enable(TRUE);
        NW_BREAK_ON_FAIL(i4_ret);
        DBG_INFO(("[NW]%s %d\n", __func__, __LINE__));
    }while(0);

    _mw_unlock();
    DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}

/**
 * @brief   Disable DLNA DMR.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_disable_dlna_dms(VOID)
{
    INT32 i4_ret = NWR_OK;

    DBG_INFO(("[NW]Disable DMS.\n"));

    _mw_lock();
    DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        i4_ret = _nw_dlna_dms_stop();
        NW_BREAK_ON_FAIL(i4_ret);
        DBG_INFO(("[NW]%s %d\n", __func__, __LINE__));
        i4_ret = nw_custom_set_dlna_dms_enable(FALSE);
        NW_BREAK_ON_FAIL(i4_ret);
        DBG_INFO(("[NW]%s %d\n", __func__, __LINE__));
    }while(0);

    _mw_unlock();
    DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}
#endif

#ifdef APP_NET_DLNA_SUPPORT
/**
 * @brief   Enable DLNA.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_enable_dlna(VOID)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;
    DBG_INFO(("[NW]Enable the DLNA.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        /**
         * When the network connection is off,can not enalbe the DLNA. So:
         * case 1: return NWR_CONNECT_DISABLE;
         * case 2: Set the value to ACFG,when enable the Connection,to do this action.
         **/

        if (!pt_nw->b_nw_enabled)
        {
            #if 0
            i4_ret = NWR_CONNECT_DISABLE;
            break;
            #else

            #endif
        }
        if (_nw_is_tv_link_router() == FALSE)
        {

        }
        else
        {
            i4_ret = _nw_start_dlna();
            NW_BREAK_ON_FAIL(i4_ret);
        }

        i4_ret = nw_custom_set_dlna_enable(TRUE);
        NW_BREAK_ON_FAIL(i4_ret);

    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}

/**
 * @brief   Disable DLNA.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_disable_dlna(VOID)
{
    INT32 i4_ret = NWR_OK;
    DBG_INFO(("[NW]Disnable the DLNA.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        i4_ret = _nw_stop_dlna();
        NW_BREAK_ON_FAIL(i4_ret);

        i4_ret = nw_custom_set_dlna_enable(FALSE);
        NW_BREAK_ON_FAIL(i4_ret);

    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}

#ifdef APP_DMR_SUPPORT
/**
 * @brief   Enable DLNA DMR.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_enable_dlna_dmr(VOID)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;

    DBG_INFO(("[NW]Enable the DMR.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        /**
         * When the network connection is off,can not enalbe the DLNA. So:
         * case 1: return NWR_CONNECT_DISABLE;
         * case 2: Set the value to ACFG,when enable the Connection,to do this action.
         **/

        if (!pt_nw->b_nw_enabled)
        {
            #if 0
            i4_ret = NWR_CONNECT_DISABLE;
            break;
            #else

            #endif
        }

        if (_nw_is_tv_link_router() == FALSE)
        {

        }
        else
        {
            i4_ret = _nw_dlna_dmr_start();
            NW_BREAK_ON_FAIL(i4_ret);
        }

        i4_ret = nw_custom_set_dlna_dmr_enable(TRUE);
        NW_BREAK_ON_FAIL(i4_ret);

    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}

/**
 * @brief   Disable DLNA DMR.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_disable_dlna_dmr(VOID)
{
    INT32 i4_ret = NWR_OK;

    DBG_INFO(("[NW]Disnable the DMR.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        i4_ret = _nw_dlna_dmr_stop();
        NW_BREAK_ON_FAIL(i4_ret);

        i4_ret = nw_custom_set_dlna_dmr_enable(FALSE);
        NW_BREAK_ON_FAIL(i4_ret);

    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}
#endif
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT

INT32 a_nw_my_net_pls_enable(void)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;
    DBG_INFO(("[NW]Enable network my places.\r\n"));

    _mw_lock();

    do
    {
        /**
         * When the network connection is off,can not enalbe the myplace. So:
         * case 1: return NWR_CONNECT_DISABLE;
         * case 2: Set the value to ACFG,when enable the Connection,to do this action.
         **/

        if (!pt_nw->b_nw_enabled)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }
        if (!pt_nw->b_nw_ethernet_plugin)
        {

        }
        else
        {
            i4_ret = _nw_my_net_pls_start();
            NW_BREAK_ON_FAIL(i4_ret);
        }
        i4_ret = nw_custom_set_my_net_pls_enable(TRUE);
        NW_BREAK_ON_FAIL(i4_ret);

    }while(0);

    _mw_unlock();
    return i4_ret;
}


/**
 * @brief  my network places stop/off
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_my_net_pls_disable(void)
{
    INT32 i4_ret = NWR_OK;
    DBG_INFO(("[NW]Disable network my_net_pls.\r\n"));

    _mw_lock();

    do
    {
        i4_ret = _nw_my_net_pls_stop();
        NW_BREAK_ON_FAIL(i4_ret);

        i4_ret = nw_custom_set_my_net_pls_enable(FALSE);
        NW_BREAK_ON_FAIL(i4_ret);
    }while(0);

    _mw_unlock();
    return i4_ret;
}

/**
 * @brief  my network places refresh
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_my_net_pls_refresh(void)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;
    DBG_INFO(("[NW]Refresh network my places.\r\n"));

    _mw_lock();

    do
    {
        /**
         * When the network connection is off,can not enalbe the myplace. So:
         * case 1: return NWR_CONNECT_DISABLE;
         * case 2: Set the value to ACFG,when enable the Connection,to do this action.
         **/

        if (!pt_nw->b_nw_enabled)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }
        if (!pt_nw->b_nw_ethernet_plugin)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }
        if (pt_nw->e_my_net_pls_state != NW_MY_NET_PLS_STARTED)
        {
            i4_ret = NWR_FAIL;
            break;
        }
        else
        {
            c_dm_smb_refresh ();
        }

    }while(0);

    _mw_unlock();
    return i4_ret;
}


/**
 * @brief  my network places refresh
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_my_net_pls_set_perm (const CHAR* ps_path,
                        const CHAR* ps_user,
                        const CHAR* ps_passwd)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;
    DBG_INFO(("[NW]Set Permameter for network my places.\r\n"));

    _mw_lock();

    do
    {
        /**
         * When the network connection is off,can not enalbe the myplace. So:
         * case 1: return NWR_CONNECT_DISABLE;
         * case 2: Set the value to ACFG,when enable the Connection,to do this action.
         **/

        if (!pt_nw->b_nw_enabled)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }
        if (!pt_nw->b_nw_ethernet_plugin)
        {
            i4_ret = NWR_CONNECT_DISABLE;
            break;
        }
        else
        {
            i4_ret = c_fm_smb_set_perm(ps_path, ps_user, ps_passwd);
            NW_BREAK_ON_FAIL(i4_ret);
        }

    }while(0);

    _mw_unlock();
    return i4_ret;
}
#endif


/**
 * @brief   Get the ethernect is plugin or unplug.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_get_ethernet_connect_info(BOOL* pb_is_plug)
{
    DEBUG_NW_FLOW( DBG_LOG_PRINT(("[NW]{%s,%d} Enter \n", __FUNCTION__, __LINE__ )); );

    if (pb_is_plug == NULL)
    {
        return NWR_INV_ARG;
    }

    return _nw_get_ethernet_connect_info(pb_is_plug);
}

static BOOL _nw_check_connection_status(VOID)
{
    UINT32  ui1_idx = 0;
    INT32   i4_ret = NWR_OK;
    BOOL    b_is_plug = FALSE;
    BOOL    b_connected  = FALSE;
    BOOL    b_dhcp = FALSE;
    NW_DHCP_STATE_T e_dhcp_state = NW_DHCP_FAILED;

    i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
    NW_CHK_FAIL(i4_ret);

    ui1_idx = b_is_plug ? 0 : 1;

    i4_ret = a_cfg_custom_get_auto_ip_config(&b_dhcp, ui1_idx);
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
    DBG_LOG_PRINT(("[NW][%s][%d] Enter,b_connected=%d\n", __FUNCTION__, __LINE__, b_connected));

    return b_connected;
}

/**
 * @brief   Get the network is connected or not.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_is_network_connected(BOOL* pb_is_connected)
{
    DEBUG_NW_FLOW( DBG_LOG_PRINT(("[NW]{%s,%d} Enter \n", __FUNCTION__, __LINE__ )); );

    INT32 i4_ret = NWR_OK;
    INT32 i = 0;
    *pb_is_connected = FALSE;

    BOOL b_is_plug    = FALSE;
    i4_ret = a_nw_get_ethernet_connect_info(&b_is_plug);
    NW_CHK_FAIL(i4_ret);

    DEBUG_NW_STATUS( DBG_LOG_PRINT(("[NW]{%s,%d} b_is_plug:%d \n", __FUNCTION__, __LINE__, b_is_plug )); );

    if (b_is_plug)
    {
        *pb_is_connected = _nw_check_connection_status();
        return NWR_OK;
    }

#ifdef APP_NETWORK_WIFI_SUPPORT
    NW_WLAN_STATE_T e_wlan_state = NW_WLAN_UNPLUG;

    a_nw_wlan_status(&e_wlan_state);
    DEBUG_NW_STATUS( DBG_LOG_PRINT(("[NW]{%s,%d} e_wlan_state:%d \n", __FUNCTION__, __LINE__, e_wlan_state )); );

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
            *pb_is_connected = _nw_check_connection_status();
        }
    }
#endif
    //DBG_LOG_PRINT(("[NW][%s][%d] End connect=%d\n", __FUNCTION__, __LINE__,*pb_is_connected));

    return NWR_OK;
}

BOOL a_nw_is_ethernet_plugin(VOID)
{
    INT32 i4_ret = NWR_OK;
    BOOL b_is_plug = FALSE;

    DEBUG_NW_FLOW( DBG_LOG_PRINT(("[NW]{%s,%d} Enter \n", __FUNCTION__, __LINE__ )); );

    i4_ret = _nw_get_ethernet_connect_info(&b_is_plug);
    NW_LOG_ON_FAIL(i4_ret);

    return b_is_plug;
}

/**
 * @brief   convert a 32bits network byte address into dot string format.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_ntoa(char * ps_ip_str, UINT32 ui4_ip)
{
    c_sprintf ( ps_ip_str,
                ("%d.%d.%d.%d\0"),
                (ui4_ip)    &0x000000FF,
                (ui4_ip>>8) &0x0000FF,
                (ui4_ip>>16)&0x00FF,
                (ui4_ip>>24)
               );

    /* we shall not to all inet_ntoa(),because it is not solid*/
    #if 0
    struct in_addr t_addr;
    char* ps_temp = NULL;

    if (ps_ip_str == NULL)
    {
        return NWR_INV_ARG;
    }

    t_addr.s_addr = (in_addr_t)ui4_ip;
    ps_temp = inet_ntoa(t_addr);

    c_strcpy(ps_ip_str,ps_temp);
    #endif

    return NWR_OK;
}
/**
 * @brief   convert address string to 32bits network order byte value.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_aton(UINT32* pui4_ip, char * ps_ip_str)
{
    CHAR* ps = ps_ip_str;

    UINT32  aui4_ip_addr[4] = {0,0,0,0};
    UINT32* pui4_ip_addr = &aui4_ip_addr[0];

    if (ps_ip_str == NULL || pui4_ip == NULL)
    {
        return NWR_INV_ARG;
    }

    while ( *ps != '\0' )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            /* accumulate digit */
            *pui4_ip_addr = 10 * (*pui4_ip_addr) + (*ps - '0');
        }
        else if( *ps == '.')
        {
            pui4_ip_addr ++;
        }
        else
        {
            return NWR_INV_ARG;
        }

        ps++; /* get next char */
    }

    aui4_ip_addr[1] = (aui4_ip_addr[1]<<8) & 0xFF00;
    aui4_ip_addr[2] = (aui4_ip_addr[2]<<16)& 0xFF0000;
    aui4_ip_addr[3] = (aui4_ip_addr[3]<<24)& 0xFF000000;

    *pui4_ip = aui4_ip_addr[0] + aui4_ip_addr[1]
               + aui4_ip_addr[2]+ aui4_ip_addr[3];

#if 0  /*the inet_aton() is not correct in linux.*/
    struct in_addr t_addr;

    if (ps_ip_str == NULL || pui4_ip == NULL)
    {
        return NWR_INV_ARG;
    }

    i4_ret = inet_aton(ps_ip_str, &t_addr);
    NW_CHK_FAIL(i4_ret);

    *pui4_ip = (UINT32)t_addr.s_addr;
#endif

    return NWR_OK;
}
/**
 * @brief   Get ethernet mac address in binary form.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_get_mac_addr(CHAR *psz_name,UINT8 *pMacAddr)
{
    if (psz_name == NULL || pMacAddr == NULL)
    {
        return NWR_INV_ARG;
    }

    return c_net_ni_get_mac(psz_name, (CHAR*)pMacAddr);
}
/**
 * @brief   Get ethernet mac address in char form.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_get_mac_addr_string(CHAR *psz_name, char * ps_mac_str)
{
    UINT8 mac[6] = {0};
    CHAR  c_default_mac[18] = {0};

    if (psz_name == NULL || ps_mac_str == NULL)
    {
        return NWR_INV_ARG;
    }

    /* init default MAC string */
    c_strncpy(c_default_mac, "ba:d0:00:ba:d0:00", 17);
    c_sscanf(c_default_mac, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &(mac[0]),
           &(mac[1]),
           &(mac[2]),
           &(mac[3]),
           &(mac[4]),
           &(mac[5]));

    if (c_net_ni_get_mac(psz_name, (CHAR*)mac) != 0)
    {
        DBG_INFO(("[NW] get mac string ERROR %s, line is %d\n", __FUNCTION__, __LINE__));
    }

    return c_sprintf ( ps_mac_str,
                    "%02X:%02X:%02X:%02X:%02X:%02X\0",
                    mac[0],
                    mac[1],
                    mac[2],
                    mac[3],
                    mac[4],
                    mac[5]
                   );
}

/**
 * @brief   Set ethernet mac address in binary form.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_save_mac_addr(const CHAR *psz_name,UINT8 *pMacAddr)
{
#ifdef LINUX_TURNKEY_SOLUTION
    if (psz_name == NULL || pMacAddr == NULL)
    {
        return NWR_INV_ARG;
    }

    c_net_ni_save_mac(psz_name, (UINT8*)pMacAddr);
#endif
    return NWR_OK;
}

/**
 * @brief   Set ethernet mac address in binary form.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_save_mac_addr_string(CHAR *psz_name, char * ps_mac_str)
{
    MAC_ADDRESS_T           t_MacAddress = {0};

    if (psz_name == NULL || ps_mac_str == NULL)
    {
        return NWR_INV_ARG;
    }
#ifdef LINUX_TURNKEY_SOLUTION
    c_sscanf(ps_mac_str, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
           &(t_MacAddress[0]),
           &(t_MacAddress[1]),
           &(t_MacAddress[2]),
           &(t_MacAddress[3]),
           &(t_MacAddress[4]),
           &(t_MacAddress[5]));

      if (c_net_ni_set_mac((CHAR*)psz_name, (VOID *)(&t_MacAddress)) == NET_OK)
      {
          /* write config (eeprom) */
          if (c_strcmp ((CHAR*)psz_name, NI_ETHERNET_0) == 0)
          {
              if (c_net_ni_save_mac (NI_ETHERNET_0, (UINT8*)&t_MacAddress) != 0)
              {
                  DBG_LOG_PRINT(("[INET] write mac config error\n"));
                  return NWR_FAIL;
              }
          }
      }
      c_net_ni_get_mac(psz_name, (CHAR*)(&t_MacAddress));
#endif
      DBG_LOG_PRINT(("Ethernet MAC = %02x:%02x:%02x:%02x:%02x:%02x\n", t_MacAddress[0],t_MacAddress[1],t_MacAddress[2],t_MacAddress[3],t_MacAddress[4],t_MacAddress[5]));
      return CLIR_OK;
}

/**
 * @brief   enable or disable the interface device.
 * @param ifname [in] device's name
 * @param u1EnableNi [in]  1 ---up  0-----down
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_net_ni_enable( const CHAR *ifname, INT8 u1EnableNi )
{
    if ((NULL == ifname)||(u1EnableNi<0)||(u1EnableNi>1))
    {
        return NWR_INV_ARG;
    }
#ifdef LINUX_TURNKEY_SOLUTION
    #ifndef ANDROID_TWO_WORLDS
    char *s_cmd = "iwpriv ra0 mac 1400=15f97";
    if(u1EnableNi)
    {
        s_cmd = "iwpriv ra0 mac 1400=15f97";
    }
    else
    {
        s_cmd = "iwpriv ra0 mac 1400=15fd7";
    }
    AP_SYSTEM_CALL(s_cmd);
    #endif

    return  c_net_ni_enable(ifname, u1EnableNi);
#else
    if(u1EnableNi)
        return c_net_enable();
    else
        return c_net_disable();
#endif
}

#ifdef APP_NETWORK_WIFI_SUPPORT

INT32 a_nw_get_wlan_signal_lvl_from_rssi(VOID)
{
    INT32   signal = 0;
    NET_802_11_WIFI_RSSI_T rssi;

    c_memset (&rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));

    if (a_nw_wlan_get_rssi(&rssi) != NET_WLAN_OK)
    {
        DBG_WARN(("Get rssi info fail!!\n"));
        return 0;
    }

    DBG_INFO(("%s() Rssi info: a,b,c=[%d, %d, %d]\r\n", __FUNCTION__,
                                                        rssi.i4Rssi_a,
                                                        rssi.i4Rssi_b,
                                                        rssi.i4Rssi_c));

        /* 0 means no signal*/
    if (rssi.i4Rssi_a == 0) rssi.i4Rssi_a = WEAK_SIGNAL_STRENGTH;
    if (rssi.i4Rssi_b == 0) rssi.i4Rssi_b = WEAK_SIGNAL_STRENGTH;
    if (rssi.i4Rssi_c == 0) rssi.i4Rssi_c = WEAK_SIGNAL_STRENGTH;

    if (rssi.i4Rssi_a > rssi.i4Rssi_b)
    {
        signal = (rssi.i4Rssi_a > rssi.i4Rssi_c) ? rssi.i4Rssi_a : rssi.i4Rssi_c;

    }
    else
    {
        signal = (rssi.i4Rssi_b > rssi.i4Rssi_c) ? rssi.i4Rssi_b : rssi.i4Rssi_c;
    }

    if ((rssi.i4Rssi_a == rssi.i4Rssi_b) && (rssi.i4Rssi_a == rssi.i4Rssi_c) &&(rssi.i4Rssi_a == 0))
    {
        /* The three wifi antenna are no signal */
        signal = WEAK_SIGNAL_STRENGTH;
    }

    //if(signal == 0) return signal;
    if(signal <= WEAK_SIGNAL_STRENGTH)   return 0;
    if(signal > STRONG_SIGNAL_STRENGTH) signal = STRONG_SIGNAL_STRENGTH;

    return  NORMALIZED_SIGNAL_MIN +
            (NORMALIZED_SIGNAL_MAX - NORMALIZED_SIGNAL_MIN) * (signal - WEAK_SIGNAL_STRENGTH)
             / (STRONG_SIGNAL_STRENGTH - WEAK_SIGNAL_STRENGTH);
}

/**
 * @brief   Change the network interface.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_chg_network_interface(UINT8 ui1_interface)
{
    INT32 i4_ret = NWR_OK;

    /*
        IF_TYPE_ETHERNET
        IF_TYPE_IEEE80211
    */

    _mw_lock();

    do
    {
#ifdef SUPPORT_2_DONGLES
        a_agent_async_invoke( _nw_chg_network_interface,
                          (VOID*)&ui1_interface,
                          sizeof(UINT8)
                          );
#else
        i4_ret = _nw_chg_network_interface(ui1_interface);
        NW_BREAK_ON_FAIL(i4_ret);
#endif
        i4_ret = nw_custom_set_network_interface(ui1_interface);
        NW_BREAK_ON_FAIL(i4_ret);

    }while(0);

    _mw_unlock();

    return i4_ret;
}

/**
 * @brief   Set current Bssid.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_set_wlan_bssid(NET_802_11_BSSID_T*          pt_Bssid)
{
    return nw_custom_set_wlan_bssid(pt_Bssid);
}
/**
 * @brief   Get current Bssid.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */

INT32 a_nw_get_wlan_bssid(NET_802_11_BSSID_T*          pt_Bssid)
{
    return nw_custom_get_wlan_bssid(pt_Bssid);
}
/**
 * @brief   Set current Ssid.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */

INT32 a_nw_set_wlan_ssid(NET_802_11_SSID_T*           pt_Ssid)
{
    return nw_custom_set_wlan_ssid(pt_Ssid);
}
/**
 * @brief   Get current Ssid.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */

INT32 a_nw_get_wlan_ssid(NET_802_11_SSID_T*           pt_Ssid)
{
    return nw_custom_get_wlan_ssid(pt_Ssid);
}
/**
 * @brief   Set current associate case.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */

INT32 a_nw_set_wlan_assoc_case(NET_802_11_ASSOC_CASE_T     e_AssocCase)
{
    return nw_custom_set_wlan_assoc_case(e_AssocCase);
}

/**
 * @brief   Get current associate case.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_get_wlan_assoc_case(NET_802_11_ASSOC_CASE_T*     pe_AssocCase)
{
    return nw_custom_get_wlan_assoc_case(pe_AssocCase);
}
/**
 * @brief   Set current auth mdoe.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_set_wlan_auth_mode(NET_802_11_AUTH_MODE_T      e_AuthMode)
{
    return nw_custom_set_wlan_auth_mode(e_AuthMode);
}
/**
 * @brief   Get current auth mode.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_get_wlan_auth_mode(NET_802_11_AUTH_MODE_T*     pe_AuthMode)
{
    return nw_custom_get_wlan_auth_mode(pe_AuthMode);
}
/**
 * @brief   Set current auth cipher.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_set_wlan_auth_cipher(NET_802_11_AUTH_CIPHER_T    e_AuthCipher)
{
    return nw_custom_set_wlan_auth_cipher(e_AuthCipher);
}
/**
 * @brief   Get current auth cipher.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_get_wlan_auth_cipher(NET_802_11_AUTH_CIPHER_T*  pe_AuthCipher)
{
    return nw_custom_get_wlan_auth_cipher(pe_AuthCipher);
}
/**
 * @brief   Set current auth key.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_set_wlan_key(NET_802_11_KEY_T*           pt_Key)
{
    return nw_custom_set_wlan_key(pt_Key);
}
/**
 * @brief   Get current auth key.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_get_wlan_key(NET_802_11_KEY_T*           pt_Key)
{
    return nw_custom_get_wlan_key(pt_Key);
}
/**
 * @brief Refresh WPS PIN code.
 * @param pin [out] buffer of PIN code
 * @param len [in]  length of the buffer
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 *
 *  This routine refreshes WPS PIN code.
 */
INT32 a_nw_wlan_wps_refresh_pin(char *s_pin, UINT32 ui4_len)
{
    INT32 i4_ret = NWR_OK;

    if (ui4_len < 9 || s_pin == NULL)
    {
        return NWR_INV_ARG;
    }

    i4_ret = c_net_wlan_wps_refresh_pin();
    NW_CHK_FAIL(i4_ret);

    s_pin[8] = '\0';
    return c_net_wlan_wps_get_pin(s_pin, ui4_len);
}

/**
 * @brief Get WPS PIN code.
 * @param pin [out] buffer of PIN code
 * @param len [in]  length of the buffer
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 *
 *  This routine gets WPS PIN code. The PIN code is not refreshed
 *  by calling this routine.
 */
INT32 a_nw_wlan_wps_get_pin(char *s_pin, UINT32 ui4_len)
{
    if (ui4_len < 9 || s_pin == NULL)
    {
        return NWR_INV_ARG;
    }

    s_pin[8] = '\0';
    return c_net_wlan_wps_get_pin(s_pin, ui4_len);
}

/**
 *  @brief get raw signal level of connected AP.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine get the raw signal level of connected AP
 */
INT32 a_nw_wlan_get_raw_signal_level(INT32 * pi4_signal)
{
    if (pi4_signal == NULL)
    {
        return NWR_INV_ARG;
    }

    return NWR_OK;//c_net_wlan_get_raw_signal_level(pi4_signal);
}

/**
 *  @brief Scan network.
 *  @param cbk [in] callback function to notify scan completion.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine scans infrastructure and adhoc networks.
*/
INT32 a_nw_wlan_drv_start(VOID)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;

    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, b_wlan_drv_init: %d\n", __FUNCTION__, __LINE__, t_g_nw_util.b_wlan_drv_init));

    pt_nw->b_nw_enabled = TRUE;

    if (pt_nw->b_wlan_drv_init)
    {
        return NWR_OK;
    }

    return _nw_wlan_start_driver();
}

/**
 *  @brief Scan network.
 *  @param cbk [in] callback function to notify scan completion.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine scans infrastructure and adhoc networks.
*/
INT32 a_nw_wlan_drv_stop(VOID)
{
    NW_UTIL_T*    pt_nw             = &t_g_nw_util;
    INT32         i4_ret            = NWR_OK;

    DBG_LOG_PRINT(("%s %d b_wlan_drv_init=%d, b_wlan_started=%d\n", __FUNCTION__, __LINE__, t_g_nw_util.b_wlan_drv_init,pt_nw->b_wlan_started));

    if (pt_nw->b_wlan_started)
    {
        /*need do disassociating before close connection*/
        i4_ret = c_net_wlan_disassociate();
        NW_LOG_ON_FAIL(i4_ret);

        i4_ret = c_net_wlan_close_connection();
        NW_LOG_ON_FAIL(i4_ret);
        pt_nw->b_wlan_started = FALSE;

        /*send the WLAN_NOTIFY_DEINIT_IND message*/
        NW_WLAN_NTY_T t_wlan_nty;
        t_wlan_nty.i4_msg_id = WLAN_NOTIFY_DEINIT_IND;
        t_wlan_nty.i4_data = 0;

        i4_ret = a_agent_async_invoke( _nw_wlan_notify_hdlr,
                              (VOID*)&t_wlan_nty,
                              sizeof(NW_WLAN_NTY_T)
                              );
        NW_CHK_FAIL(i4_ret);
    }
    if (pt_nw->b_wlan_drv_init)
    {
        i4_ret = c_net_wlan_stop_driver(_nw_wlan_driver_notify_fct);
        NW_LOG_ON_FAIL(i4_ret);
        pt_nw->b_wlan_drv_init = FALSE;
    }

#ifndef DISABLE_TV_WORLD_NW_SETTING
    i4_ret = _nw_clean_ip_dns(NW_NET_INTERFACE_WIFI);
    NW_LOG_ON_FAIL(i4_ret);
#endif
    c_net_ni_enable (NI_WIRELESS_0, 0);

    pt_nw->e_wlan_status = NW_WLAN_PLUG_STOP;

    pt_nw->b_nw_enabled = FALSE;

#ifdef MW_IPV6_SUPPORT
    i4_ret = c_net_ip_v6_disable(_nw_get_interface_name(NW_NET_INTERFACE_WIFI));/*clear ipv6 address*/
    NW_CHK_FAIL(i4_ret);
#endif

    return i4_ret;
}

/**
 *  @brief get RSSI of connected AP.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine get the RSSI info of connected AP
 */
INT32 a_nw_wlan_get_rssi(NET_802_11_WIFI_RSSI_T *pt_rssi)
{
    if (pt_rssi == NULL)
    {
        return NWR_INV_ARG;
    }
    CHAR s_model_name[ACFG_CUSTOM_WIFI_MODULE_NAME_LEN] = {0};
    a_cfg_cust_get_wifi_model_name(s_model_name, ACFG_CUSTOM_WIFI_MODULE_NAME_LEN);
    return c_net_wlan_get_rssi(pt_rssi, atoi(s_model_name));
}

/**
 *  @brief Scan network.
 *  @param cbk [in] callback function to notify scan completion.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine scans infrastructure and adhoc networks.
*/
INT32 a_nw_wlan_scan(VOID)
{
    return c_net_wlan_scan(_nw_wlan_notify_fct);
}

/**
 *  @brief Scan wifi with special SSID.
 *  @param cbk [in] callback function to notify scan completion.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine scans infrastructure and adhoc networks.
*/
INT32 a_nw_wlan_scan_with_ssid(char * ssid, int ssid_len)
{
    return c_net_wlan_scan_with_ssid(_nw_wlan_notify_fct,ssid,ssid_len);
}

/**
 * @brief Get scan result.
 * @param pScanResult [in/out] list of scan result(BSSs)
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 *
 *  This routine is called to get the scan result.
 *  All the found BSSs are listed in the list.
 */
INT32 a_nw_wlan_get_scan_result(NET_802_11_SCAN_RESULT_T *pScanResult)
{
    if (pScanResult == NULL)
    {
        return NWR_INV_ARG;
    }

    return c_net_wlan_get_scan_result(pScanResult);
}

/**
 * @brief Get a list of ESSs.
 * @param pEssList [in/out] list of ESSs
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 *
 *  This routine lists the ESSs enties and sorts in descending order
 *  of the signal strength. The stealth networks are attached the BSSIDs.
 *  Adhoc networks are not listed in the table.
 */
INT32 a_nw_wlan_get_ess_list(NET_802_11_ESS_LIST_T *pEssList)
{
    if (pEssList == NULL)
    {
        return NWR_INV_ARG;
    }

    return c_net_wlan_get_ess_list(pEssList);
}
/**
 *  @brief Associate with a wireless network.
 *  @param pAssociate [in] association settings
 *  @param cbk [in] callback function to notify the association status.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine triggers attempts of connecting to a wireless network according
 *  to the specified settings. After calling this routine, the WLAN
 *  software continues to maintain a network connection according
 *  to the specified settings until c_net_wlan_disassociate() is called.
 */

INT32 a_nw_wlan_associate(NET_802_11_ASSOCIATE_T *pAssociate)
{
    INT32 i4_ret = NWR_OK;
#ifndef DISABLE_TV_WORLD_NW_SETTING
    DBG_LOG_PRINT(("[NW]associate wifi.\r\n"));

    if (pAssociate == NULL)
    {
        return NWR_INV_ARG;
    }

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        i4_ret = _nw_wlan_associate(pAssociate);
        NW_BREAK_ON_FAIL(i4_ret);

        i4_ret = nw_custom_set_associate(pAssociate);
        NW_BREAK_ON_FAIL(i4_ret);

    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
#else
    DBG_WARN(("[NW]implelet function is %s, line is %d\n", __FUNCTION__, __LINE__));
#endif
    return i4_ret;
}
/**
 *  @brief Disassociate a wireless network connection.
 *  @retval 0 on success, otherwise is failure
 *
 */
INT32 a_nw_wlan_disassociate(VOID)
{
    INT32 i4_ret = NWR_OK;
#ifndef DISABLE_TV_WORLD_NW_SETTING
    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        b_g_nw_wifi_disassociating = TRUE;
        i4_ret = _nw_wlan_disassociate();
        NW_BREAK_ON_FAIL(i4_ret);
        b_g_nw_wifi_disassociating = FALSE;

    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
#else
    DBG_WARN(("[NW]implelet  function is %s, line is %d\n", __FUNCTION__, __LINE__));
#endif
    return i4_ret;
}

/**
 *  @brief Get the currently associated BSS information.
 *  @param pCurrBss [in/out] associated BSS information
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine gets the information of the associated BSS.
 *  If this routine is called while connection is not established,
 *  zero-BSSID (00:00:00:00:00:00) is returned.
 */

INT32 a_nw_wlan_get_curr_bss(NET_802_11_BSS_INFO_T *pCurrBss)
{
    if (pCurrBss == NULL)
    {
        return NWR_INV_ARG;
    }

    return c_net_wlan_get_curr_bss(pCurrBss);
}

/**
 *  @brief WPS registration and association.
 *  @param eWpsMode [in] \ref WPSOpMode "WPS Mode" WPS registration method.
 *  @param cbk [in] callback function to notify WPS status.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine obtains association settings from a WPS registrer,
 *  save it in the disk and associate with the network.
 */
INT32 a_nw_wlan_wps_associate(NET_802_11_WPS_ASSOC_MODE_T eWpsMode)
{
    INT32 i4_ret = NWR_OK;
    DBG_LOG_PRINT(("%s %d calling disassociate\n",__FUNCTION__,__LINE__));
    i4_ret = c_net_wlan_disassociate();
    NW_LOG_ON_FAIL(i4_ret);
    return c_net_wlan_wps_associate(eWpsMode,_nw_wlan_notify_fct);
}

/**
 *  @brief Get the status of a WPS process.
 *  @param status [out] \ref WPSStatus "WPS status"
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine gets the current WPS status.
 */
INT32 a_nw_wlan_wps_get_status(INT32 *status)
{
    if (status == NULL)
    {
        return NWR_INV_ARG;
    }

    return c_net_wlan_wps_get_status(status);
}
/**
 *  @brief Cancel WPS registration process.
 *  @retval 0 on success, otherwise is failure
 *
 *  This routine tiriggers cancellation of WPS registration process.
 */
INT32 a_nw_wlan_wps_cancel(void)
{
    INT32 i4_ret = NWR_OK;

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        i4_ret = _nw_wlan_wps_cancel();
        NW_BREAK_ON_FAIL(i4_ret);
    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}

#ifdef SUPPORT_2_DONGLES
/**
 * @brief   Get current WLAN status..
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_wlan_status( NW_WLAN_STATE_T* pe_wlan_state )
{
   UINT8    ui1_interface = 0;
    INT32   i4_ret;

    DBG_INFO(("[NW]Get current wlan status.\r\n"));

    if (pe_wlan_state == NULL)
    {
        return NWR_INV_ARG;
    }
    i4_ret = nw_custom_get_network_interface(&ui1_interface);
    if(i4_ret != NWR_OK)
    {
        return NWR_FAIL;
    }


    return a_nw_wlan_status_ex(ui1_interface, pe_wlan_state);


/*
    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    *pe_wlan_state = t_g_nw_util.e_wlan_status;
    if ( NW_NET_INTERFACE_OUT_WIFI == t_g_nw_util.ui1_interface )
    {
        *pe_wlan_state = t_g_nw_util.e_out_wlan_status;
    }
    else
    {
        return NWR_FAIL;
    }

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return NWR_OK;
*/
}


/**
 * @brief   Get current WLAN status..
 * @param   ui1_interface(in) may be NW_NET_INTERFACE_BUILT_IN_WIFI   or NW_NET_INTERFACE_OUT_WIFI
 * @param   pe_wlan_state(out)  .
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_wlan_status_ex( UINT8 ui1_interface,NW_WLAN_STATE_T* pe_wlan_state )
{
    DBG_INFO(("Get current wlan(Built_in or out dongle) status.\r\n"));

    if ((pe_wlan_state == NULL)||((ui1_interface != NW_NET_INTERFACE_BUILT_IN_WIFI)
    &&(ui1_interface != NW_NET_INTERFACE_OUT_WIFI)))
    {
        return NWR_INV_ARG;
    }

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
#ifndef DISABLE_TV_WORLD_NW_SETTING
    if (ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
    {
        *pe_wlan_state = t_g_nw_util.e_built_in_wlan_status;
    }
    else
    {
        *pe_wlan_state = t_g_nw_util.e_out_wlan_status;
    }
#else
    DBG_LOG_PRINT(("[%s %d] ui1_interface = %d\n",__FUNCTION__,__LINE__,ui1_interface));
    if (ui1_interface == NW_NET_INTERFACE_BUILT_IN_WIFI)
    {
        if((t_g_nw_util.e_built_in_wlan_status==NW_WLAN_UNPLUG)||(t_g_nw_util.e_built_in_wlan_status==NW_WLAN_PLUG_STOP))
        {
            *pe_wlan_state = t_g_nw_util.e_built_in_wlan_status;
        }
        else
        {
            INT32 i4_ret = NWR_OK;
            UINT8 wpa_status;
            NET_802_11_BSS_INFO_T pCurrBss;
            i4_ret=a_nw_wlan_get_curr_bss(&pCurrBss);
            NW_BREAK_ON_FAIL(i4_ret);
            wpa_status=(&pCurrBss)->u8_wpa_status;
            if(wpa_status==WLAN_WPA_DISCONNECTED||wpa_status==WLAN_WPA_INACTIVE||wpa_status==WLAN_WPA_SCANNING)
            {
                *pe_wlan_state=NW_WLAN_START_DISASSOC;

            }
            else if(wpa_status==WLAN_WPA_COMPLETED)
            {
                *pe_wlan_state=NW_WLAN_ASSOCIATE;
            }
            else
            {
                *pe_wlan_state=NW_WLAN_ASSOCIATING;
            }
        }
    }
    else
    {
        if((t_g_nw_util.e_out_wlan_status==NW_WLAN_UNPLUG)||(t_g_nw_util.e_out_wlan_status==NW_WLAN_PLUG_STOP))
        {
            *pe_wlan_state = t_g_nw_util.e_built_in_wlan_status;
        }
        else
        {
            INT32 i4_ret = NWR_OK;
            UINT8 wpa_status;
            NET_802_11_BSS_INFO_T pCurrBss;
            i4_ret=a_nw_wlan_get_curr_bss(&pCurrBss);
            NW_BREAK_ON_FAIL(i4_ret);
            wpa_status=(&pCurrBss)->u8_wpa_status;
            if(wpa_status==WLAN_WPA_DISCONNECTED||wpa_status==WLAN_WPA_INACTIVE||wpa_status==WLAN_WPA_SCANNING)
            {
                *pe_wlan_state=NW_WLAN_START_DISASSOC;

            }
            else if(wpa_status==WLAN_WPA_COMPLETED)
            {
                *pe_wlan_state=NW_WLAN_ASSOCIATE;
            }
            else
            {
                *pe_wlan_state=NW_WLAN_ASSOCIATING;
            }
        }
    }
#endif
    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return NWR_OK;
}

#else
/**
 * @brief   Get current WLAN status..
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_wlan_status( NW_WLAN_STATE_T* pe_wlan_state )
{
    DEBUG_NW_FLOW( DBG_LOG_PRINT(("[NW]{%s,%d} Enter \n", __FUNCTION__, __LINE__ )); );

    if (pe_wlan_state == NULL)
    {
        return NWR_INV_ARG;
    }

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

#ifndef DISABLE_TV_WORLD_NW_SETTING
    *pe_wlan_state = t_g_nw_util.e_wlan_status;
#else
    if((t_g_nw_util.e_wlan_status==NW_WLAN_UNPLUG)||(t_g_nw_util.e_wlan_status==NW_WLAN_PLUG_STOP))
    {
        *pe_wlan_state = t_g_nw_util.e_wlan_status;
    }
    else
    {
        INT32 i4_ret = NWR_OK;
        UINT8 wpa_status = 0;
        NET_802_11_BSS_INFO_T pCurrBss;
        DBG_LOG_PRINT(("[NW]Get current wlan bss.\r\n"));
        i4_ret=a_nw_wlan_get_curr_bss(&pCurrBss);
        NW_CHK_FAIL(i4_ret);
        wpa_status=(&pCurrBss)->u8_wpa_status;
        if(wpa_status==WLAN_WPA_DISCONNECTED||wpa_status==WLAN_WPA_INACTIVE||wpa_status==WLAN_WPA_SCANNING)
        {
        *pe_wlan_state=NW_WLAN_START_DISASSOC;

        }
        else if(wpa_status==WLAN_WPA_COMPLETED)
        {
        *pe_wlan_state=NW_WLAN_ASSOCIATE;
        }
        else
        {
        *pe_wlan_state=NW_WLAN_ASSOCIATING;
        }
    }
#endif

    _mw_unlock();

    DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    DEBUG_NW_STATUS( DBG_LOG_PRINT(("[NW]{%s,%d} Get current wlan status ==> *pe_wlan_state=%d \n", __FUNCTION__, __LINE__, *pe_wlan_state )); );

    return NWR_OK;
}
#endif

/**
 * @brief   Get current WLAN's started state..
 * @param   pe_wlan_state(out)  .
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_wlan_is_started(BOOL* pb_wlan_started )
{
    DBG_INFO(("[NW]Get current wlan started status.\r\n"));

    if (pb_wlan_started == NULL)
    {
        return NWR_INV_ARG;
    }

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    *pb_wlan_started = t_g_nw_util.b_wlan_started;

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return NWR_OK;
}

/**
 * @brief   Get current WLAN drv..
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_get_wlan_driver_init_status( BOOL* b_wlan_drv )
{
    DBG_INFO(("[NW]Get current DHCP status.\r\n"));

    if (b_wlan_drv == NULL)
    {
        return NWR_INV_ARG;
    }

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    *b_wlan_drv = t_g_nw_util.b_wlan_drv_init;

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return NWR_OK;
}
#endif

/**
 * @brief  Get the network init status.
 * @param   VOID
 * @retval  NWR_OK     If  the network has initalized.
 * @retval  Otherwise  The function failed.
 */
INT32  a_get_nw_init_status(VOID)
{
    if ( b_g_nw_init  == TRUE )
    {
        return NWR_OK;
    }
    else
    {
        return NWR_FAIL;
    }
}

/**
 * @brief   The network pre init h_api_mutx when network init is lazy.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_pre_init(VOID)
{
    INT32 i4_ret = NWR_OK;
    NW_UTIL_T*    pt_nw = &t_g_nw_util;

    c_memset( pt_nw, 0, sizeof(NW_UTIL_T) );

    /* allocate API mutex */
    i4_ret = c_sema_create(&pt_nw->h_api_mtx,
                        X_SEMA_TYPE_MUTEX,
                        X_SEMA_STATE_UNLOCK);
    if(i4_ret != OSR_OK)
    {
        DBG_LOG_PRINT(("<NW>Can't create API mutex,return %d.\r\n", i4_ret));
        return i4_ret;
    }

    return NWR_OK;
}


/**
 * @brief   The network init.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_init(VOID)
{
    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, i4_ret: %d\n", __FUNCTION__, __LINE__, 0));

#ifndef DISABLE_TV_WORLD_NW_SETTING
#ifndef SYS_NETWORK_LAZY_INIT
    return _nw_init();
#else
    INT32 i4_ret  = 0;

#ifdef MW_IPV6_SUPPORT
    BOOL          b_ipv6_auto_enable = TRUE;
#endif

#ifdef MW_IPV6_SUPPORT
    i4_ret = a_cfg_get_ipv6_state_config(&b_ipv6_auto_enable);
    NW_CHK_FAIL(i4_ret);

    i4_ret = c_net_network_reg_nfy_ipv6(_network_status_nfy, 0, b_ipv6_auto_enable);
    NW_CHK_FAIL(i4_ret);
#else
    /*Delay init the network*/
    i4_ret = c_net_network_reg_nfy(_network_status_nfy, 0);
    NW_CHK_FAIL(i4_ret);
#endif
    return NWR_OK;
#endif
#else //DISABLE_TV_WORLD_NW_SETTING
return _nw_init();
#endif
}
/**
 * @brief   The network init.
 * @param   VOID
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_init_ex(VOID)
{
    DBG_LOG_PRINT(("[KK][NW] %s, LINE: %d, i4_ret: %d\n", __FUNCTION__, __LINE__, 0));
    return _nw_init();
}

/**
 * @brief   Reset the Default Network Config.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_default_reset_update(VOID)
{
    NW_UTIL_T*    pt_nw = &t_g_nw_util;
    BOOL          b_network_enabled = FALSE;
    NW_NFY_ID_T   e_nfy_id     = NW_NFY_ID_UNKNOWN;
    VOID*         pv_nfy_param = NULL;

    INT32 i4_ret  = 0;
    BOOL  b_send_msg = TRUE;

    DBG_INFO(("[NW]Network reset update.\r\n"));

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        /*get the network info*/
        i4_ret = nw_custom_get_network_enable(&b_network_enabled);
        NW_BREAK_ON_FAIL(i4_ret);

        if(b_network_enabled)
        {
            if (!pt_nw->b_nw_enabled)
            {
                i4_ret = _nw_enable_network_connection(FALSE);
                NW_BREAK_ON_FAIL(i4_ret);

                e_nfy_id = NW_NFY_ID_NETWORK_CONN_ENABLED;
            }
            else if (pt_nw->b_nw_enabled)
            {
                if (_nw_is_tv_link_router() == TRUE)
                {
                    b_send_msg = FALSE;

                    i4_ret = _nw_start_ip_assoc(t_g_nw_util.ui1_interface);
                    NW_BREAK_ON_FAIL(i4_ret);
                }
            }
        }
        else
        {
            if (pt_nw->b_nw_enabled)
            {
                i4_ret = _nw_disable_network_connection(FALSE);
                NW_BREAK_ON_FAIL(i4_ret);

                e_nfy_id = NW_NFY_ID_NETWORK_CONN_DISABLED;
            }
            else
            {
                b_send_msg = FALSE;
            }
        }
    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    if((i4_ret == NWR_OK) && (b_send_msg))
    {
        _nw_send_event_msg(e_nfy_id, pv_nfy_param);
    }

    return NWR_OK;
}
/**
 * @brief   Get Network Debug level.
 * @param   VOID
 * @retval  The Debug level.
 */
UINT16 nw_get_dbg_level(VOID)
{
    return ui2_nw_dbg_level;
}
static CHAR nw_prefix[]="NW_APP";

CHAR* nw_get_log_prefix(VOID)
{
  return nw_prefix;
}

INT32 a_nw_suspend_poweroff(VOID)
{
    DBG_LOG_PRINT(("<zanchen>a_nw_suspend_poweroff---%s: %d\r\n", __func__, __LINE__));
    c_net_suspend_poweroff();
    return NWR_OK;
}
extern INT32 a_icl_custom_get_power_mode (UINT8* pui1_val);
INT32 a_nw_suspend_resume(VOID)
{
    INT32 i4_ret;
    PCL_WIFI_WOL_CTRL_T e_wifi_wol_ctrl = PCL_WIFI_WOL_DISABLE;
    if(strcmp(NI_WIRELESS_0,_nw_get_interface_name(t_g_nw_util.ui1_interface)) == 0)
    {
        DBG_LOG_PRINT(("[NW] NI_WIRELESS_0 \r\n"));
        c_pcl_get_wifi_wol_ctrl(&e_wifi_wol_ctrl);
        if(PCL_WIFI_WOL_ENABLE == e_wifi_wol_ctrl)
        {
            UINT8 ui1_power_mode = 0;

            i4_ret = a_icl_custom_get_power_mode(&ui1_power_mode);
            if (i4_ret == NWR_OK && 1 == ui1_power_mode)
            {
                //QS mode don't restart dhcp
                DBG_LOG_PRINT(("Quick Start mode\n\r"));
            } else {
                DBG_LOG_PRINT(("[NW]run dhcp\r\n"));
                i4_ret = _nw_start_dhcp_ip_config();
                if(NWR_OK != i4_ret){
                    DBG_LOG_PRINT(("[NW]fail to run dhcp\r\n"));
                }
            }
        }
    }
    else
    {
        DBG_LOG_PRINT(("[NW] NI_ETHERNET_0 \r\n"));
        c_net_suspend_resume();
    }
    return NWR_OK;
}
/**
 * @brief   Set Network Debug level.
 * @param   ui2_dbg_level    [in] The Debug level want to set.
 * @retval  None
 */
VOID nw_set_dbg_level(UINT16 ui2_dbg_level)
{
    ui2_nw_dbg_level = ui2_dbg_level;
}

#ifdef APP_UPG_SUPPORT

/**
 * @brief   _mw_connection_test_process_upg.
 * @param
 * @retval  VOID.
 */
static VOID _mw_connection_test_process_upg(VOID* pv_data, SIZE_T z_data_len)
{
    struct hostent *pt_hostnet = NULL;

    NW_UTIL_T*    pt_nw  = &t_g_nw_util;
    NW_NFY_ID_T   e_nfy_id = NW_NFY_ID_UNKNOWN;
    BOOL          b_test_result = FALSE;
    CHAR*         s_test_hostname = NULL;

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));
   do
   {
        if(pt_nw->s_test_hostname == NULL)
        {
           break;
        }

        s_test_hostname = (CHAR*)c_mem_alloc(sizeof(CHAR)*(c_strlen(pt_nw->s_test_hostname)+1));
        if(s_test_hostname != NULL)
        {
            c_strcpy(s_test_hostname, pt_nw->s_test_hostname);

            c_mem_free(pt_nw->s_test_hostname);
            pt_nw->s_test_hostname = NULL;
        }
        else
        {
            DBG_ERROR(("[NW]_mw_connection_test_process mem alloc fail!\r\n"));
        }
    } while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    if (s_test_hostname == NULL)
    {
        return;
    }
#ifdef LINUX_TURNKEY_SOLUTION
    __res_init();
#endif
    pt_hostnet = gethostbyname(s_test_hostname);
    if (pt_hostnet != NULL)
    {
        DBG_INFO(("The Connection test is success!.\r\n"));
        if( ui2_nw_dbg_level & DBG_LEVEL_INFO)/*For Debug*/
        {
            INT32 i4_i = 0;
            DBG_INFO(("CNAME = %s\n", pt_hostnet->h_name));
            while (pt_hostnet->h_addr_list[i4_i] != NULL)
            {
                DBG_INFO(("IP = %s ", inet_ntoa(*( struct in_addr*)( pt_hostnet->h_addr_list[i4_i]))));
                i4_i++;
            }

            DBG_INFO(("\n"));
        }

        c_net_free_hostent(pt_hostnet);
        e_nfy_id = NW_NFY_ID_INTERN_CT_UPG_RESULT;
        b_test_result = TRUE;
    }
    else
    {
        DBG_ERROR(("The Connection test is fail!.\r\n"));
        e_nfy_id = NW_NFY_ID_INTERN_CT_UPG_RESULT;
        b_test_result = FALSE;
    }

    c_mem_free(s_test_hostname);
    s_test_hostname = NULL;

    _nw_msg_brdcast(e_nfy_id, (VOID*)(UINT32)b_test_result);

    return;
}


/**
 * @brief   _connect_test_upg_async_thread.
 * @param
 * @retval  VOID.
 * @entry of _mw_connection_test_process_async
 */

static void* _connect_test_upg_async_thread(void* pv_data)
{
    pthread_detach(pthread_self());
    _mw_connection_test_process_upg(pv_data, 0);
    return NULL;
}

/**
 * @brief   _mw_connection_test_upg_async.
 * @param
 * @retval  VOID.
 * @create a thread to do _mw_connection_test_process
 */
static VOID _mw_connection_test_upg_async(VOID* pv_data, SIZE_T z_data_len)
{
    int         ret = 0;
    pthread_t    h_thread = {0};

    ret = pthread_create(&h_thread, NULL, _connect_test_upg_async_thread, pv_data);
    if(ret != 0)
    {
        DBG_ERROR(("[NW]--- create thread fail, reason : %d \n----", ret));
    }
    return;
}

/**
 * @brief   To test the network connection in net update .
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32  a_nw_connection_test_upg(CHAR* hostname)
{
    NW_UTIL_T* pt_nw = &t_g_nw_util;
    INT32 i4_ret = NWR_OK;

    _mw_lock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    do
    {
        if (hostname == NULL)
        {
            i4_ret = NWR_INV_ARG;
            break;
        }

        if(pt_nw->s_test_hostname != NULL)
        {
            c_mem_free(pt_nw->s_test_hostname);
            pt_nw->s_test_hostname = NULL;
        }
        pt_nw->s_test_hostname = (CHAR*)c_mem_alloc(sizeof(CHAR)*(c_strlen(hostname)+1));
        if(pt_nw->s_test_hostname != NULL)
        {
            c_strcpy(pt_nw->s_test_hostname, hostname);

            i4_ret = a_agent_async_invoke(_mw_connection_test_upg_async,NULL, 0);

            if (i4_ret!= AGENTR_OK)
            {
                c_mem_free(pt_nw->s_test_hostname);
                pt_nw->s_test_hostname = NULL;
            }
        }

    }while(0);

    _mw_unlock(); DBG_INFO(("[NW]change lock status function is %s, line is %d\n", __FUNCTION__, __LINE__));

    return i4_ret;
}
#endif

/**
 * @brief   To start the magic packet monitor
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 a_nw_start_magic_packet_monitor(VOID)
{
    return _nw_udp_server_init();
}

BOOL a_nw_check_network_connect_test(VOID)
{
    return b_con_test;
}

#ifdef MT5583_MODEL
BOOL a_nw_check_resume_connection_status(VOID)
{
    INT32   i4_ret = NWR_OK;
    if(FALSE == a_cfg_cust_Is_CurModel_after_2022_K())
    {
        return FALSE;
    }
    if(t_g_nw_util.ui1_interface != NW_NET_INTERFACE_ETH0 && t_g_nw_util.b_wlan_drv_init == TRUE && t_g_nw_util.b_wlan_started == TRUE)
    {
        FILE *fl;
        CHAR s_status[50] = {0};
        system("/3rd/bin/wpa_supplicant/common/wpa_cli -iwlan0 status | grep wpa_state > /tmp/wpa_status");
        fl = fopen("/tmp/wpa_status","r");
        if(fl != NULL)
        {
            fseek(fl,0,SEEK_END);
            long lsize=ftell(fl);
            rewind(fl);
            if(fread(s_status,sizeof(CHAR),lsize,fl)!=0)
            {
                DBG_LOG_PRINT(("[NW]%s %d wpa_status=%s\n",__FUNCTION__, __LINE__,s_status));
                if(c_strncmp(s_status,"wpa_state=DISCONNECTED",22) == 0)
                {
                    /*send the WLAN_NOTIFY_START_IND message*/
                    DBG_LOG_PRINT(("[NW]%s %d Notify WLAN_NOTIFY_START_IND again.\n",__FUNCTION__, __LINE__));
                    NW_WLAN_NTY_T t_wlan_nty;
                    t_wlan_nty.i4_msg_id = WLAN_NOTIFY_START_IND;
                    t_wlan_nty.i4_data = 0;

                    i4_ret = a_agent_async_invoke( _nw_wlan_notify_hdlr,
                                                     (VOID*)&t_wlan_nty,
                                                    sizeof(NW_WLAN_NTY_T));
                    NW_LOG_ON_FAIL(i4_ret);
                }
            }
            fclose(fl);
        }
    }
    return TRUE;
}
#endif
#endif /* APP_NETWORK_SUPPORT */
