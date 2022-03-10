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
 * $RCSfile: network_cli.c,v $
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
#ifdef APP_NETWORK_SUPPORT

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "stdlib.h"
#include "string.h"

#include "c_os.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_cli.h"

#if 0
#include "c_net_config.h"
#include "u_dhcpc_api.h"
#include "u_net_common.h"
#include "u_net_ni_if.h"
#include "u_net_oid.h"
#include "u_net_socket.h"
#include "c_net_socket.h"

#include "u_net_util.h"
#endif
#include "app_util/a_cli_app.h"
#include "agent/agent.h"

#include "app_util/a_network.h"
#include "app_util/network/network.h"

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/
#ifdef CLI_SUPPORT

static INT32 _nw_cli_network_set_connection(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_get_ip_info(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_start_dhcp(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_stop_dhcp(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_set_ip_manual(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_random_test(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_set_mac(INT32  i4_argc, const CHAR** pps_argv);
#ifdef MW_IPV6_SUPPORT
static INT32 _nw_cli_set_ipv6_nodns_config(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_get_ipv6_config(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_ip_v6_config(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_ip_v6_auto(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_dns_v6_config(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_dns_v6_auto(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_ping_v6(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_get_v6_info(INT32  i4_argc, const CHAR** pps_argv);
#endif /* APP_UTIL_IPV6_SUPPORT */

#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
static INT32 _nw_cli_enable_device(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_set_device_name(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_get_wifi_status(INT32  i4_argc, const CHAR** pps_argv);
#endif
#endif
#ifdef APP_NET_DLNA_SUPPORT
static INT32 _nw_cli_network_set_dlna(INT32  i4_argc, const CHAR** pps_argv);
#endif

#ifdef APP_NETWORK_WIFI_SUPPORT
static INT32 _nw_cli_wlan_chg_interface(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_wlan_drv_start(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_wlan_drv_stop(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_wlan_scan(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_wlan_wps_get_pin(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_wlan_assoc(INT32  i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_wlan_disassoc(INT32  i4_argc, const CHAR** pps_argv);
#endif
static INT32 _nw_cli_get_dbg_level(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_set_dbg_level(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _nw_cli_attach_cmd_tbl(VOID);
static INT32 _nw_cli_speedtest(INT32 i4_argc,const CHAR** pps_argv);
static VOID _nw_cli_test_SpeedtestNtyFct(INT32 i4Status, DOUBLE u4Speed);

/*-----------------------------------------------------------------------------
                    data, variable declarations
-----------------------------------------------------------------------------*/
static CLI_EXEC_T at_nw_cmd_tbl[] =
{
    {"Set Connection",      "snc",  _nw_cli_network_set_connection,   NULL,       "Set network connection",   CLI_ACCESS_RIGHT_APP_NW},
    {"Get ip info",         "info", _nw_cli_get_ip_info,              NULL,       "Get network IP info",      CLI_ACCESS_RIGHT_APP_NW},
    {"Start DHCP",    "dhcp_start", _nw_cli_start_dhcp,               NULL,       "Start DHCP",               CLI_ACCESS_RIGHT_APP_NW},
    {"Stop  DHCP",    "dhcp_stop",  _nw_cli_stop_dhcp,                NULL,       "Stop DHCP",                CLI_ACCESS_RIGHT_APP_NW},
    {"Set IP Manually",  "ip_man",  _nw_cli_set_ip_manual,            NULL,       "Set IP Manually",          CLI_ACCESS_RIGHT_APP_NW},
    {"Random Test",      "r_test",  _nw_cli_random_test,              NULL,       "Random test",              CLI_ACCESS_RIGHT_APP_NW},
    {"Set MAC",          "smac",    _nw_cli_set_mac,                  NULL,       "Set MAC",                  CLI_ACCESS_RIGHT_APP_NW},

#ifdef MW_IPV6_SUPPORT
    {"Write ipv6_nodns",   "w6ip",   _nw_cli_set_ipv6_nodns_config,   NULL,       "Write ipv6 without dns to eeprom",   CLI_ACCESS_RIGHT_APP_NW},
    {"Read ipv6 info",     "r6ip",   _nw_cli_get_ipv6_config,         NULL,       "Read IPv6 info from eeprom",         CLI_ACCESS_RIGHT_APP_NW},
    {"Set ipv6",           "s6ip",   _nw_cli_ip_v6_config,            NULL,       "Set ipv6 without dns",               CLI_ACCESS_RIGHT_APP_NW},
    {"Set ipv6_dns ",      "sdns",   _nw_cli_dns_v6_config,           NULL,       "Set ipv6's dns",                      CLI_ACCESS_RIGHT_APP_NW},
    {"Set ipv6 auto",      "s6auto",   _nw_cli_ip_v6_auto,            NULL,      "Setthe ipv6 to auto or manual",       CLI_ACCESS_RIGHT_APP_NW},
     {"Enable v6dns auto",  "e6dns", _nw_cli_dns_v6_auto,            NULL,       "Enable or disable the ipv6's dns auto state",   CLI_ACCESS_RIGHT_APP_NW},
    {"ping ipv6",          "ping6",  _nw_cli_ping_v6,                 NULL,       "Ping the ipv6 addr",                  CLI_ACCESS_RIGHT_APP_NW},
    {"Get ipv6 info",      "g6ip",   _nw_cli_get_v6_info,             NULL,       "Get the ipv6's info with dns info",       CLI_ACCESS_RIGHT_APP_NW},
#endif /* APP_UTIL_IPV6_SUPPORT */
#ifdef APP_NET_DLNA_SUPPORT
	{"Set DLNA",           "sdlna", _nw_cli_network_set_dlna,         NULL,       "Set dlna setting",         CLI_ACCESS_RIGHT_APP_NW},
#endif
#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
    {"Enable Device",      "en_dev",  _nw_cli_enable_device,          NULL,       "Enable Device",            CLI_ACCESS_RIGHT_APP_NW},
	{"Get status",        "g_st", _nw_cli_get_wifi_status,			  NULL, 	  "Get wifi status(built_in/out)", CLI_ACCESS_RIGHT_APP_NW},
    {"Set Device Name",     "s_nam",  _nw_cli_set_device_name,  NULL,       "Set Device Name",      CLI_ACCESS_RIGHT_APP_NW},
#endif
#endif

#ifdef APP_NETWORK_WIFI_SUPPORT
    {"Change interface",  "if",     _nw_cli_wlan_chg_interface,       NULL,       "Change interface",         CLI_ACCESS_RIGHT_APP_NW},
    {"Wlan driver start", "wd_start", _nw_cli_wlan_drv_start,         NULL,       "wlan driver start",        CLI_ACCESS_RIGHT_APP_NW},
    {"Wlan driver stop",  "wd_stop",  _nw_cli_wlan_drv_stop,          NULL,       "wlan driver stop",         CLI_ACCESS_RIGHT_APP_NW},
    {"Wlan scan AP",      "w_scan", _nw_cli_wlan_scan,                NULL,       "wlan Scan Ap",             CLI_ACCESS_RIGHT_APP_NW},
    {"Get WPS pin",       "g_pin",  _nw_cli_wlan_wps_get_pin,         NULL,       "Get Wlan WPS pin",         CLI_ACCESS_RIGHT_APP_NW},
	{"Wlan assoc",	      "w_assoc", _nw_cli_wlan_assoc,			  NULL, 	  "WPA associatie", 		  CLI_ACCESS_RIGHT_APP_NW},
	{"Wlan dis assoc",	  "d_assoc", _nw_cli_wlan_disassoc,			  NULL, 	  "Dis associatie", 		  CLI_ACCESS_RIGHT_APP_NW},
#endif
    {CLI_GET_DBG_LVL_STR,   NULL,   _nw_cli_get_dbg_level,            NULL,       CLI_GET_DBG_LVL_HELP_STR,   CLI_ACCESS_RIGHT_APP_NW},
    {CLI_SET_DBG_LVL_STR,   NULL,   _nw_cli_set_dbg_level,            NULL,       CLI_SET_DBG_LVL_HELP_STR,   CLI_ACCESS_RIGHT_APP_NW},
    {"Test WIFI speed",   "st",     _nw_cli_speedtest,                NULL,       "Run speedtest 1:default 2:other",CLI_ACCESS_RIGHT_APP_NW},
    END_OF_CLI_CMD_TBL
};

/* ICL root command table */
static CLI_EXEC_T at_nw_root_cmd_tbl[] =
{
    {"nw",                 NULL,     NULL,                          at_nw_cmd_tbl,     "Network commands",     CLI_ACCESS_RIGHT_APP_NW},
    END_OF_CLI_CMD_TBL
};

/*-----------------------------------------------------------------------------
                    function implementations
-----------------------------------------------------------------------------*/
/**
 * @brief   Convert a number string to a number.
 * @param   ps     [in] null ('\0') terminated character string
 * @retval  INT32      Sum of the number string.
 */
static INT32 _atoi( const CHAR* ps )
{
    INT32  i4_total;

    i4_total = 0;
    while ( *ps != 0 )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            /* accumulate digit */
            i4_total = 10 * i4_total + (*ps - '0');
            ps++; /* get next char */
        }
        else /* not a digit char */
        {
            return (-1);
        }
    }

    return i4_total;
}
/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_network_set_connection(INT32  i4_argc, const CHAR** pps_argv)
{
    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("Set Network connection. 0:off 1: on"));
        return CLIR_OK;
    }
    #if 1
    if (_atoi(pps_argv[1])>0)
    {
        if (a_nw_enable_network_connection() != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: Enable the network connection fail.\n\r"));
        }
    }
    else
    {
        if (a_nw_disable_network_connection() != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: Disable the network connection fail.\n\r"));
        }
    }

    #else
    DBG_LOG_PRINT((" [NW_CLI]: Enable the network connection %d.\n\r",_atoi(pps_argv[1])));

    /*c_net_ni_set(NI_ETHERNET_0, OID_CMN_IF_ADMIN_STATUS, (VOID*)(_atoi(pps_argv[1])));*/
    c_net_ni_set(NI_IP_0, OID_CMN_IF_ADMIN_STATUS,(VOID*)(_atoi(pps_argv[1])));

    #endif
    return CLIR_OK;
}
/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_get_ip_info(INT32  i4_argc, const CHAR** pps_argv)
{
    NW_IP_INFO_T t_ip_info;

    if (a_nw_get_crnt_ip_info(&t_ip_info) != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: Get ip info fail.\n\r"));
    }
    DBG_LOG_PRINT((" The IP inifo is :\r\n"));

    DBG_LOG_PRINT((" IP Address is : 0x%08x.\r\n", t_ip_info.ui4_address));
    DBG_LOG_PRINT((" IP netmask is : 0x%08x.\r\n", t_ip_info.ui4_netmask));
    DBG_LOG_PRINT((" IP gateway is : 0x%08x.\r\n", t_ip_info.ui4_gw));
    DBG_LOG_PRINT((" IP 1st DNS is : 0x%08x.\r\n", t_ip_info.ui4_1st_dns));
    DBG_LOG_PRINT((" IP 2nd DNS is : 0x%08x.\r\n", t_ip_info.ui4_2nd_dns));

    return CLIR_OK;
}
/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_start_dhcp(INT32  i4_argc, const CHAR** pps_argv)
{
    if (a_nw_start_dhcp_ip_config() != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: Start dhcp config fail.\n\r"));
    }
    return CLIR_OK;
}
/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_stop_dhcp(INT32  i4_argc, const CHAR** pps_argv)
{
    if (a_nw_stop_dhcp_ip_config() != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: Stop dhcp config fail.\n\r"));
    }
    return CLIR_OK;
}
/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */

static INT32 _nw_cli_set_ip_manual(INT32  i4_argc, const CHAR** pps_argv)
{
    NW_IP_INFO_T t_ip_info;

    t_ip_info.ui4_address = 0x1d721aac; /*172.26.114.29*/
    t_ip_info.ui4_netmask = 0x00ffffff; /*255.255.255.0*/
    t_ip_info.ui4_gw      = 0xfe721aac; /*72.26.114.254*/
    t_ip_info.ui4_1st_dns = 0x0c671aac; /*172.26.103.12*/
    t_ip_info.ui4_2nd_dns = 0x0b671aac; /*172.26.103.11*/

    if (a_nw_manual_ip_config(&t_ip_info) != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: Stop dhcp config fail.\n\r"));
    }
    return CLIR_OK;
}
/**
 * @brief   _mw_connection_test_process.
 * @param
 * @retval  VOID.
 */
static VOID _mw_cli_random_test_process(VOID* pv_data, SIZE_T z_data_len)
{
    INT32    i4_ret = CLIR_OK;
    UINT32   ui4_loop_num  = *((UINT32*)pv_data);
    BOOL     b_infinite = ui4_loop_num>0? FALSE:TRUE;
    UINT32   ui4_test_num = 0;

    while (b_infinite || ui4_loop_num>0 )
    {
        ui4_loop_num --;
        ui4_test_num ++;

        DBG_LOG_PRINT(("This is the %d times the random test process\r\n",ui4_test_num));

        switch(rand()%6)
        {
        case 0:
            if (a_nw_disable_network_connection() != NWR_OK)
            {
                DBG_LOG_PRINT((" [NW_CLI]: Disable the network connection fail.\n\r"));
            }
            break;
        case 1:
            if (a_nw_enable_network_connection() != NWR_OK)
            {
                DBG_LOG_PRINT((" [NW_CLI]: Enable the network connection fail.\n\r"));
            }
            break;
        case 2:
            i4_ret = a_nw_connection_test((CHAR*)"www.mediatek.com");
            if(i4_ret != NWR_OK)
            {
                DBG_LOG_PRINT((" [NW_CLI]: connection tst fail.\n\r"));
            }
            break;
        case 3:
            if (a_nw_start_dhcp_ip_config() != NWR_OK)
            {
                DBG_LOG_PRINT((" [NW_CLI]: Start dhcp config fail.\n\r"));
            }
            break;
        case 4:
        {
            NW_IP_INFO_T t_ip_info;

            t_ip_info.ui4_address = 0x1d721aac; /*172.26.114.29*/
            t_ip_info.ui4_netmask = 0x00ffffff; /*255.255.255.0*/
            t_ip_info.ui4_gw      = 0xfe721aac; /*72.26.114.254*/
            t_ip_info.ui4_1st_dns = 0x0c671aac; /*172.26.103.12*/
            t_ip_info.ui4_2nd_dns = 0x0b671aac; /*172.26.103.11*/

            if (a_nw_manual_ip_config(&t_ip_info) != NWR_OK)
            {
                DBG_LOG_PRINT((" [NW_CLI]: Stop dhcp config fail.\n\r"));
            }
        }
            break;
        case 5:
        {
            NW_IP_INFO_T t_ip_info;

            if (a_nw_get_crnt_ip_info(&t_ip_info) != NWR_OK)
            {
                DBG_LOG_PRINT((" [NW_CLI]: Get ip info fail.\n\r"));
            }
            DBG_LOG_PRINT((" The IP inifo is :\r\n"));

            DBG_LOG_PRINT((" IP Address is : 0x%08x.\r\n", t_ip_info.ui4_address));
            DBG_LOG_PRINT((" IP netmask is : 0x%08x.\r\n", t_ip_info.ui4_netmask));
            DBG_LOG_PRINT((" IP gateway is : 0x%08x.\r\n", t_ip_info.ui4_gw));
            DBG_LOG_PRINT((" IP 1st DNS is : 0x%08x.\r\n", t_ip_info.ui4_1st_dns));
            DBG_LOG_PRINT((" IP 2nd DNS is : 0x%08x.\r\n", t_ip_info.ui4_2nd_dns));
            break;
        }
        default:
            break;
        }

        c_thread_delay (((rand()%7) +1)*500);

    }

    return;
}
/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_random_test(INT32  i4_argc, const CHAR** pps_argv)
{
    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("Usage: r_test test_loop_num(0: infinite)\n"));
        return CLIR_OK;
    }

    UINT32 ui4_loop_num = _atoi (pps_argv[1]);

    if(a_agent_async_invoke( _mw_cli_random_test_process,(VOID*)&ui4_loop_num, sizeof(UINT32)) != AGENTR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: Random test fail.\n\r"));
    }

    return CLIR_OK;
}

/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_set_mac(INT32  i4_argc, const CHAR** pps_argv)
{
    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("Usage: setmac eth0 xx:xx:xx:xx:xx:xx \n"));
        return CLIR_OK;
    }

    a_nw_save_mac_addr_string ((CHAR*) pps_argv[1], (CHAR*) pps_argv[2]);

    return CLIR_OK;
}

#ifdef MW_IPV6_SUPPORT
extern INT32 a_nw_set_ip_v6_config(INT32 ip_type, INT32 dns_type, NW_IPV6_INFO_T *p_tip_info);
static INT32 _nw_cli_set_ipv6_nodns_config(INT32  i4_argc, const CHAR** pps_argv)
{
	NW_IPV6_INFO_T t_info;
	memset(&t_info,0,sizeof(NW_IPV6_INFO_T));

	c_strncpy(t_info.ac_v6ip, "2001:b030:7005:ff01:20c:e7ff:fe06:9085", 40);
	c_strncpy(t_info.ac_v6gw, "2001:b030:7005:ff01:20c:e7ff:fe06:90ff", 40);
	t_info.ui4_prefix = 64;

    if ((a_nw_set_ip_v6_config(0,1, &t_info)) != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: set ip no dns to eeprom fail.\n\r"));
    }

    return CLIR_OK;
}
static INT32 _nw_cli_get_ipv6_config(INT32  i4_argc, const CHAR** pps_argv)
{
	NW_IPV6_INFO_T t_info;
	memset(&t_info,0,sizeof(NW_IPV6_INFO_T));

    if (a_nw_get_ipv6_config(&t_info) != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: get ip info from eeprom fail.\n\r"));
    }

	DBG_LOG_PRINT(("The ipv6 addr is %s.\n\r",t_info.ac_v6ip));
	DBG_LOG_PRINT(("The ipv6 gateway is %s.\n\r",t_info.ac_v6gw));
	DBG_LOG_PRINT(("The ipv6 prefix is %d.\n\r",t_info.ui4_prefix));
	DBG_LOG_PRINT(("The ipv6 dns1 is %s.\n\r",t_info.ac_dns1));
	DBG_LOG_PRINT(("The ipv6 dns2 is %s.\n\r",t_info.ac_dns2));

	return CLIR_OK;

}
static INT32 _nw_cli_ip_v6_config(INT32  i4_argc, const CHAR** pps_argv)
{
	NW_IPV6_INFO_T t_info;
	memset(&t_info,0,sizeof(NW_IPV6_INFO_T));

	c_strncpy(t_info.ac_v6ip, "2001:b030:7005:ff01:20c:e7ff:fe06:9085", INET6_ADDRSTRLEN);
	c_strncpy(t_info.ac_v6gw, "2001:b030:7005:ff01:20c:e7ff:fe06:90ff", INET6_ADDRSTRLEN);
	t_info.ui4_prefix = 64;

    if (a_nw_set_ip_v6_config(0,1,&t_info) != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: set ip no dns manually failed.\n\r"));
    }

    return CLIR_OK;
}
static INT32 _nw_cli_dns_v6_config(INT32  i4_argc, const CHAR** pps_argv)
{
	CHAR	ac_dns1[MAX_IPV6_IP_LENGTH] = {0};
    CHAR    ac_dns2[MAX_IPV6_IP_LENGTH] = {0};

	c_strncpy(ac_dns1, "2001:b030:7005:ff01:20c:e7ff:fe06:8877", INET6_ADDRSTRLEN-1);
	c_strncpy(ac_dns2, "2001:b030:7005:ff01:20c:e7ff:fe06:8899", INET6_ADDRSTRLEN-1);

	if (a_nw_dns_v6_config(ac_dns1, ac_dns2) != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: set ip dns manually failed.\n\r"));
    }

    return CLIR_OK;
}

static INT32 _nw_cli_ip_v6_auto(INT32  i4_argc, const CHAR** pps_argv)
{
	int enable = TRUE;

	if ((i4_argc != 2) ||(pps_argv == NULL))
	{
		DBG_LOG_PRINT(("nw.s6auto 0/1 0=disable 1=enable\n\r"));
		return CLIR_INV_CMD_USAGE;
	}

	enable = _atoi(pps_argv[1]);

	if (a_nw_ip_v6_auto(enable,1) != NWR_OK)
	{
		DBG_LOG_PRINT((" [NW_CLI]: Enable the ipv6's state failed!!!.\n\r"));
	}

	return CLIR_OK;
}

static INT32 _nw_cli_dns_v6_auto(INT32  i4_argc, const CHAR** pps_argv)
{
	BOOL enable = TRUE;

	if ((i4_argc != 2) ||(pps_argv == NULL))
	{
		DBG_LOG_PRINT(("nw.e6dns 0/1 0=disable 1=enable\n\r"));
		return CLIR_INV_CMD_USAGE;
	}

	enable = (BOOL)_atoi(pps_argv[1]);

	if (a_nw_dns_v6_auto(enable) != NWR_OK)
	{
		DBG_LOG_PRINT((" [NW_CLI]: Enable the ipv6 dns's state failed!!!!\n\r"));
	}

	return CLIR_OK;
}
static INT32 _nw_cli_ping_v6(INT32  i4_argc, const CHAR** pps_argv)
{
	a_nw_ping_v6("eth0", 128,3,NULL);

	return CLIR_OK;
}
static INT32 _nw_cli_get_v6_info(INT32  i4_argc, const CHAR** pps_argv)
{
    NW_IPV6_INFO_T t_info;
    memset(&t_info,0,sizeof(NW_IPV6_INFO_T));

    if (a_nw_get_v6_info(&t_info) != NWR_OK)
    {
        DBG_LOG_PRINT((" [NW_CLI]: get ip info from eeprom fail.\n\r"));
        return NWR_FAIL;
    }
    else
    {
        DBG_LOG_PRINT(("The ipv6 addr is %s.\n\r",t_info.ac_v6ip));
        DBG_LOG_PRINT(("The ipv6 gateway is %s.\n\r",t_info.ac_v6gw));
        DBG_LOG_PRINT(("The ipv6 prefix is %d.\n\r",t_info.ui4_prefix));
        DBG_LOG_PRINT(("The ipv6 dns1 is %s.\n\r",t_info.ac_dns1));
        DBG_LOG_PRINT(("The ipv6 dns2 is %s.\n\r",t_info.ac_dns2));
        DBG_LOG_PRINT(("The ipv6 ac_v6ip_ll is %s.\n\r",t_info.ac_v6ip_ll));
        DBG_LOG_PRINT(("The ipv6 ui4_prefix_ll is %d.\n\r",t_info.ui4_prefix_ll));
        return CLIR_OK;
    }
}

#endif /* APP_UTIL_IPV6_SUPPORT */

#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_enable_device(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32       i4_ret = NWR_OK;
    INT8  i1_able = 0;

    if (i4_argc < 3)
    {
        DBG_LOG_PRINT(("Usage: en_dev eth0/ath0/athmag0 0/1 \n"));
        return CLIR_OK;
    }

    i1_able = (UINT8)_atoi (pps_argv[2]);

    i4_ret = a_nw_net_ni_enable ((const CHAR *) pps_argv[1], i1_able);
    if (i4_ret != NWR_OK)
    {
        DBG_LOG_PRINT(("a_nw_net_ni_enable failed!! \n"));
    }
    else
    {
        DBG_LOG_PRINT(("a_nw_net_ni_enable successed!! \n"));
    }

    return i4_ret;
}

/**
 * @brief   This API.
 * @param   i4_argc       [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_set_device_name(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32       i4_ret = NWR_OK;

    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("Usage: s_nam eth0/ath0/athmag0\n"));
        return CLIR_OK;
    }

    i4_ret = a_nw_set_device_name ((const CHAR *) pps_argv[1]);
    if (i4_ret != NWR_OK)
    {
        DBG_LOG_PRINT(("a_nw_set_device_name failed!! \n"));
    }
    else
    {
        DBG_LOG_PRINT(("a_nw_set_device_name successed!! \n"));
    }

    return i4_ret;
}
#endif
#endif

#ifdef APP_NET_DLNA_SUPPORT
/**
 * @brief   This API.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_network_set_dlna(INT32  i4_argc, const CHAR** pps_argv)
{
    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("Set DLNA 0:off 1: on"));
        return CLIR_OK;
    }

    if (_atoi(pps_argv[1])>0)
    {
        if (a_nw_enable_dlna() != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: Enable the DLNA fail.\n\r"));
        }
    }
    else
    {
        if (a_nw_disable_dlna() != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: Disable the DLNA Fail.\n\r"));
        }
    }

    return CLIR_OK;
}
#endif

#ifdef APP_NETWORK_WIFI_SUPPORT
#ifdef SUPPORT_2_DONGLES
static INT32 _nw_cli_wlan_chg_interface(INT32  i4_argc, const CHAR** pps_argv)
{
    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("0:Ethernet. 1: Out Wireless. 2: Built_in Wireless.\n"));
        return CLIR_OK;
    }

    if (_atoi(pps_argv[1])== 0)
    {
        if (a_nw_chg_network_interface(NW_NET_INTERFACE_ETH0) != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: a_nw_chg_network_interface() fail.\n\r"));
        }
    }
    else if (_atoi(pps_argv[1])== 1)
    {
        if (a_nw_chg_network_interface(NW_NET_INTERFACE_OUT_WIFI) != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: a_nw_chg_network_interface() Fail.\n\r"));
        }
    }
    else
    {
        if (a_nw_chg_network_interface(NW_NET_INTERFACE_BUILT_IN_WIFI) != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: a_nw_chg_network_interface() Fail.\n\r"));
        }
    }


    return CLIR_OK;
}
#else
static INT32 _nw_cli_wlan_chg_interface(INT32  i4_argc, const CHAR** pps_argv)
{
    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("0:Ethernet. 1: Wirless.\n"));
        return CLIR_OK;
    }
    if (_atoi(pps_argv[1])== 0)
    {
        if (a_nw_chg_network_interface(NW_NET_INTERFACE_ETH0) != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: a_nw_chg_network_interface() fail.\n\r"));
        }
    }
    else
    {
        if (a_nw_chg_network_interface(NW_NET_INTERFACE_WIFI) != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: a_nw_chg_network_interface() Fail.\n\r"));
        }
    }
    return CLIR_OK;
}
#endif
static INT32 _nw_cli_wlan_scan(INT32  i4_argc, const CHAR** pps_argv)
{
    return a_nw_wlan_scan();
}

static INT32 _nw_cli_wlan_drv_start(INT32  i4_argc, const CHAR** pps_argv)
{
    return a_nw_wlan_drv_start();
}

static INT32 _nw_cli_wlan_drv_stop(INT32  i4_argc, const CHAR** pps_argv)
{
    return a_nw_wlan_drv_stop();
}

static INT32 _nw_cli_wlan_wps_get_pin(INT32  i4_argc, const CHAR** pps_argv)
{
    char s_pin[9] = {0};
    UINT32 ui4_len = 9;

    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("0:Get WPS current Pin. 1: Get WPS refresh Pin.\n"));
        return CLIR_OK;
    }

    if (_atoi(pps_argv[1])== 0)
    {
        if (a_nw_wlan_wps_get_pin(s_pin,ui4_len) != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: a_nw_wlan_wps_get_pin() fail.\n\r"));
        }
    }
    else
    {
        if (a_nw_wlan_wps_refresh_pin(s_pin,ui4_len) != NWR_OK)
        {
            DBG_LOG_PRINT((" [NW_CLI]: a_nw_wlan_wps_refresh_pin() Fail.\n\r"));
        }
    }

    DBG_LOG_PRINT(("Pin is %s.\n\r", s_pin));

    return CLIR_OK;

}

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 == *s2) {
		if (*s1 == '\0')
			break;
		s1++;
		s2++;
	}

	return *s1 - *s2;
}

static INT32 _nw_cli_wlan_assoc(INT32  i4_argc, const CHAR** pps_argv)
{
    CHAR  s_input_buf[64];

    NET_802_11_ASSOCIATE_T  t_associate;
    INT32       i4_ret = 0;
    CHAR *auth, *cipher;
    UINT32 ui4_length;

	const CHAR** argv = &pps_argv[1];

    c_memset(&t_associate, 0x00, sizeof(NET_802_11_ASSOCIATE_T));
    t_associate.e_AssocCase = IEEE_802_11_MANUAL_ASSOC;
    t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_NONE;
    t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_NONE;
	t_associate.t_Key.pui1_PassPhrase = s_input_buf;

    c_memset(s_input_buf, 0, sizeof(s_input_buf));
    c_memset(t_associate.t_Bssid, 0xFF, sizeof(t_associate.t_Bssid));

    while(*argv[0] != '\0' && *argv[1] != '\0')
	{
        if(_strcmp(*argv, "ssid") == 0)
		{
            if(c_strlen(*++argv) > NET_802_11_MAX_LEN_SSID)
			{
                i4_ret = -1;
            }
            t_associate.t_Ssid.ui4_SsidLen = c_strlen(*argv);
            c_strncpy(t_associate.t_Ssid.ui1_aSsid, *argv, NET_802_11_MAX_LEN_SSID);
        }
        else if(_strcmp(*argv, "bssid") == 0)
		{
			#if 0
            c_sscanf((*++argv), "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                    t_associate.t_Bssid[0], t_associate.t_Bssid[1], t_associate.t_Bssid[2], t_associate.t_Bssid[3], t_associate.t_Bssid[4], t_associate.t_Bssid[5]);
            #else
            ++argv;
			#endif
		}
        else if(_strcmp((*argv), "auth") == 0)
		{
            auth =(CHAR*)(*(++argv));
            if(_strcmp(auth, "none") == 0)
			{
                t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_NONE;
            }
            else if(_strcmp(auth, "open") == 0)
			{
                t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_OPEN;
            }
            else if(_strcmp(auth, "share") == 0)
			{
                t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_SHARED;
            }
            else if(_strcmp(auth, "wep_auto") == 0)
			{
                t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_WEPAUTO;
            }
            else if(_strcmp(auth, "wpa") == 0)
			{
                t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_WPA_PSK;
            }
            else if(_strcmp(auth, "wpa2") == 0)
			{
                t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_WPA2_PSK;
            }
            else if(_strcmp(auth, "wpa_auto") == 0)
			{
                t_associate.e_AuthMode = IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK;
            }
            else
			{
                i4_ret = -1;
                DBG_LOG_PRINT(("auth: <none|open|share|wep_auto|wpa|wpa2|wpa_auto>\n"));
            }
        }
        else if(_strcmp((*argv), "cipher") == 0)
		{
            cipher = (CHAR*)(*(++argv));
            if(_strcmp(cipher, "none") == 0)
			{
                t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_NONE;
            }
            else if(_strcmp(cipher, "wep") == 0)
			{
                t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_WEP40;
            }
            else if(_strcmp(cipher, "wep104") == 0)
			{
                t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_WEP104;
            }
            else if(_strcmp(cipher, "tkip") == 0)
			{
                t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_TKIP;
            }
            else if(_strcmp(cipher, "aes") == 0)
			{
                t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_AES;
            }
            else if(_strcmp(cipher, "tkip_aes") == 0)
			{
                t_associate.e_AuthCipher = IEEE_802_11_AUTH_CIPHER_AES_OR_TKIP;
            }
            else
			{
                i4_ret = -1;
                DBG_LOG_PRINT(("cipher: <none|wep|tkip|aes|tkip_aes>\n"));
            }
        }
        else if(_strcmp((*argv), "key") == 0)
		{
            if(c_strlen(*++argv) > 64)
			{
                i4_ret = -1;
            }

            t_associate.t_Key.b_IsAscii = TRUE;
            ui4_length = c_strlen(*argv);
            if(t_associate.t_Key.pui1_PassPhrase)
			{
                c_strncpy(t_associate.t_Key.pui1_PassPhrase, *argv, ui4_length);
            }
			else
			{
                t_associate.t_Key.pui1_PassPhrase = (CHAR*)(*argv);
            }

            if(IEEE_802_11_AUTH_MODE_WEPAUTO == t_associate.e_AuthMode
              || IEEE_802_11_AUTH_MODE_OPEN == t_associate.e_AuthMode
              || IEEE_802_11_AUTH_MODE_SHARED == t_associate.e_AuthMode)
            {
                if(10 == ui4_length
                  || 26 == ui4_length
                  || 0 == ui4_length) // '0' for no security mode
                {
                    t_associate.t_Key.b_IsAscii = FALSE;
                }
                else if(ui4_length != 5 && ui4_length != 13)
                {
                    DBG_LOG_PRINT(("wep key length error: ui4_length=%d\n", ui4_length));
                    i4_ret = -1;
                }
            }
            else if (IEEE_802_11_AUTH_MODE_WPA_PSK  == t_associate.e_AuthMode
                     || IEEE_802_11_AUTH_MODE_WPA2_PSK == t_associate.e_AuthMode
                     || IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK == t_associate.e_AuthMode)
            {
                if(64 == ui4_length)
                {
                    t_associate.t_Key.b_IsAscii = FALSE;
                }

                else if(ui4_length < 8 || ui4_length > 64)
                {
                    DBG_LOG_PRINT(("wpa key length error: ui4_length=%d\n", ui4_length));
                    i4_ret = -1;
                }
            }

        }
        else
		{
            i4_ret = -1;
            break;
        }

        argv++;
    }

    if(t_associate.t_Ssid.ui4_SsidLen == 0) {
        i4_ret = -1;
    }

    if (i4_ret == 0)
	{
		if (a_nw_wlan_associate(&t_associate) != NWR_OK)
		{
			DBG_LOG_PRINT((" [NW_CLI]: a_nw_wlan_wps_get_pin() fail.\n\r"));
		}
	}
	else
	{
		DBG_LOG_PRINT(("Ex: w_assoc ssid WIFI cipher tkip auth wpa key 12345678 \n"));
	}

    return CLIR_OK;
}

static INT32 _nw_cli_wlan_disassoc(INT32  i4_argc, const CHAR** pps_argv)
{
    return a_nw_wlan_disassociate();
}
#ifdef SUPPORT_2_DONGLES
/**
 * @brief   This API.
 * @param   i4_argc       [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_get_wifi_status(INT32  i4_argc, const CHAR** pps_argv)
{
    INT32       i4_ret = NWR_OK;
    UINT8 interface_num = 0;
    NW_WLAN_STATE_T       p_wifi_status = NW_WLAN_UNPLUG;

    if (i4_argc < 2)
    {
        DBG_LOG_PRINT(("Usage: g_st 1(out)/2(built_in) \n"));
        return CLIR_OK;
    }

    interface_num = (UINT8)_atoi (pps_argv[1]);


    i4_ret = a_nw_wlan_status_ex (interface_num,&p_wifi_status);
    if (i4_ret != NWR_OK)
    {
        DBG_LOG_PRINT(("a_nw_net_ni_enable failed!! \n"));
    }
    else
    {
        DBG_LOG_PRINT(("The wifi's status is %d \n",p_wifi_status));

        DBG_LOG_PRINT(("a_nw_net_ni_enable successed!! \n"));
    }

    return i4_ret;
}

#endif
#endif
/**
 * @brief   This API gets the current setting of CEC Manager debug level.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_get_dbg_level(INT32        i4_argc,
                                    const CHAR** pps_argv)
{
    c_cli_show_dbg_level (nw_get_dbg_level());
    return CLIR_OK;
}

/**
 * @brief   This API sets the debug level of CEC Manager.
 * @param   i4_argc     [in]        Contains the argument count.
 * @param   pps_argv    [in]        Contains the arguments.
 * @retval  CLIR_OK                 Routine successful.
 * @retval  CLIR_INV_CMD_USAGE      Invalid command usage.
 * @retval  CLIR_CMD_EXEC_ERROR     CLI command execution failed.
 */
static INT32 _nw_cli_set_dbg_level(INT32        i4_argc,
                                    const CHAR** pps_argv)
{
    INT32       i4_return;
    UINT16      ui2_dbg_level;

    /* nw.sdl [level] */

    /* Check arguments */
    if ((i4_argc != 2) ||
        (pps_argv == NULL))
    {
        DBG_LOG_PRINT(("nw.sdl [level]\n\r"));
        DBG_LOG_PRINT(("  [level]: n=none/e=error, a=api, i=info\n\r"));
        return CLIR_INV_CMD_USAGE;
    }

    i4_return = c_cli_parse_dbg_level(i4_argc, pps_argv, &ui2_dbg_level);

    if (i4_return == CLIR_OK)
    {
        nw_set_dbg_level(ui2_dbg_level);
    }
    else
    {
        DBG_LOG_PRINT(("nw.sdl [level]\n\r"));
        DBG_LOG_PRINT(("  [level]: n=none/e=error, a=api, i=info\n\r"));
        return CLIR_INV_CMD_USAGE;
    }

    return i4_return;
}
/**
 * @brief   Init the CLI.
 * @param
 * @retval  CLIR_OK    The function succeded.
 * @retval  Otherwise  The function failed.
 */
static INT32 _nw_cli_attach_cmd_tbl(VOID)
{
    return (c_cli_attach_cmd_tbl(at_nw_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}

#endif /* CLI_SUPPORT */
/*-----------------------------------------------------------------------------
                    export function implementations
-----------------------------------------------------------------------------*/
/**
 * @brief   Init the CLI.
 * @param
 * @retval  NWR_OK     The function succeded.
 * @retval  Otherwise  The function failed.
 */
INT32 nw_cli_init(VOID)
{
#ifdef CLI_SUPPORT
    _nw_cli_attach_cmd_tbl();
#endif

    return NWR_OK;
}

static VOID _nw_cli_test_SpeedtestNtyFct(INT32 i4Status, DOUBLE u4Speed)
{
    DBG_LOG_PRINT(("%s i4Status=%d, u4Speed=%f\n",__FUNCTION__,i4Status,u4Speed));
    return;
}

static INT32 _nw_cli_speedtest(INT32 i4_argc,const CHAR** pps_argv)
{
    if(i4_argc <= 1)
    {
       return NWR_INV_ARG;
    }
    DBG_LOG_PRINT(("Enter %s testcase is %c\n",__FUNCTION__,pps_argv[1][0]));
    c_speedtest_cancel();
    if(pps_argv[1][0]=='1')
    {
        c_speedtest(NULL, _nw_cli_test_SpeedtestNtyFct);
    }
    else if(pps_argv[1][0]=='2')
    {
        c_speedtest("http://speedtest.ftp.otenet.gr/files/test100k.db", _nw_cli_test_SpeedtestNtyFct);
    }
    return NWR_OK;
}

#endif /* APP_NETWORK_SUPPORT */

