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
 * $RCSfile: a_network.h,v $
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
 * @file a_network.h
 *
 * @brief This file declares public interface of network.
 *
 * @author
 */
#ifdef APP_NETWORK_SUPPORT

#ifndef _A_NETWORK_H_
#define _A_NETWORK_H_

#ifdef __cplusplus              /* __cplusplus */
extern          "C" {
#endif                          /* __cplusplus */
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"

#include "u_net_ni_if.h"

#ifdef APP_NETWORK_WIFI_SUPPORT
#include "u_net_wlan.h"
#endif

#include "app_util/a_common.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/* Return Values */
#define NWR_OK                                              ((INT32) 0)
#define NWR_FAIL                                            ((INT32)-1)
#define NWR_INV_ARG                                         ((INT32)-2)
#define NWR_CONNECT_DISABLE                                 ((INT32)-3)
#define NWR_DHCP_NO_ADDR                                    ((INT32)-4)
#define NWR_ETHERNET_UNPLUG                                 ((INT32)-5)
#define NWR_WIFI_UNASOCCIATE                                ((INT32)-6)

#define NW_DEFAULT_INTERNET_HOSTNAME   "www.mediatek.com"
#ifndef APP_NETWORK_WIFI_SUPPORT
/**
 * @brief This structure stores the network IP base info.
 */
typedef struct _NW_IP_INFO_T
{
    UINT32 ui4_address;     /**< IP address */
    UINT32 ui4_netmask;     /**< Subnet mask */
    UINT32 ui4_gw;         /**< Default gateway */
    UINT32 ui4_1st_dns;     /**< First DNS */
    UINT32 ui4_2nd_dns;     /**< Second DNS */
}NW_IP_INFO_T;
#endif


typedef enum _NW_IPV6_CONFIG_TYPE
{
	IPV6_CONFIG_MANUAL = 0,
	IPV6_CONFIG_RA,
	IPV6_CONFIG_STATELESS,
	IPV6_CONFIG_STATEFUL,
}NW_IPV6_CONFIG_TYPE;


typedef struct _NW_IPV6_INFO_T_NO_DNS
{
    CHAR    ac_v6ip[MAX_IPV6_IP_LENGTH];
    UINT32  ui4_prefix;
    CHAR    ac_v6gw[MAX_IPV6_IP_LENGTH];
}NW_IPV6_INFO_T_NO_DNS;

typedef struct _NW_IPV6_INFO_T
{
    CHAR    ac_v6ip[MAX_IPV6_IP_LENGTH];
    UINT32  ui4_prefix;
    CHAR    ac_v6gw[MAX_IPV6_IP_LENGTH];
    CHAR    ac_dns1[MAX_IPV6_IP_LENGTH];
    CHAR    ac_dns2[MAX_IPV6_IP_LENGTH];
    CHAR    ac_v6ip_ll[MAX_IPV6_IP_LENGTH];
    CHAR*   ac_dhcpAddr;
    UINT32  ui4_prefix_ll;

}NW_IPV6_INFO_T;

/*
typedef enum _NW_CONNECTION_TEST_TYPE_T
{
    NW_CT_INTERNET,
    NW_CT_INTRANET,
    NW_CT_LAST_VALID_ITEM
}NW_CONNECTION_TEST_TYPE_T;
*/

/**
 * @brief This enum lists all DHCP states.
 */
typedef enum _NW_DHCP_STATE_T
{
    NW_DHCP_STOPPED,            /**< DHCP stopped state */
    NW_DHCP_STARTING,           /**< DHCP is still waiting for result callback */
    NW_DHCP_STARTED,            /**< DHCP started and get IPV4 */
    NW_DHCP_STARTED_LOCAL,      /**< DHCP started but only get link local IP */
    NW_DHCP_FAILED              /**<DHCP failed state */
}NW_DHCP_STATE_T;

/**
 * @brief This enum lists all DLNA states.
 */
typedef enum _NW_DLNA_STATE_T
{
    NW_DLNA_STOPPED,            /**< DLNA stopped state */
    NW_DLNA_STARTED,            /**< DLNA started state */
    NW_DLNA_SUSPENDED           /**< DLNA suspended state */
}NW_DLNA_STATE_T;

/**
 * @brief This enum lists all DLNA DMR states.
 */
typedef enum _NW_DLNA_DMR_STATE_T
{
    NW_DLNA_DMR_STOPPED,        /**< DMR stopped state */
    NW_DLNA_DMR_STARTED         /**< DMR started state */
}NW_DLNA_DMR_STATE_T;

#ifdef APP_NET_NEIGHBOR_SUPPORT
/**
 * @brief This enum lists all DLNA states.
 */
typedef enum _NW_MY_NET_PLS_STATE_T
{
    NW_MY_NET_PLS_STOPPED,            /**< MY_NET_PLS stopped state */
    NW_MY_NET_PLS_STARTED,            /**< MY_NET_PLS started state */
    NW_MY_NET_PLS_SUSPENDED           /**< MY_NET_PLS suspended state */
}NW_MY_NET_PLS_STATE_T;

#endif


/**
 * @brief This enum lists all network notify id.
 */
typedef enum _NW_NFY_ID_T
{
    NW_NFY_ID_UNKNOWN = 0,                  /**< Unknowne message */
    NW_NFY_ID_ETHERNET_PLUGIN,              /**< Ethernet cable plugged in, pv_nfy_param: not used */
    NW_NFY_ID_ETHERNET_UNPLUG,              /**< Ethernet cable unplugged, pv_nfy_param: not used */
    NW_NFY_ID_ADDRESS_CHANGED,              /**< IP address changed */
    NW_NFY_ID_ADDRESS_EXPIRED,              /**< IP address expired */
    NW_NFY_ID_DHCP_SUCCESS_DHCPv4,          /**< DHCP started successfully and get IPV4 */
    /*NW_NFY_ID_DHCP_FAILURE_DHCPv4,*/
    /*NW_NFY_ID_NEW_ADDRESS_DHCPv4,*/
    NW_NFY_ID_DHCP_SUCCESS_LINKLOCAL,       /**< DHCP started successfully but get link local IP */
    NW_NFY_ID_DHCP_FAILURE_LINKLOCAL,       /**< DHCP failed */
    NW_NFY_ID_DHCP_STOPPED,                 /**< DHCP stopped */
    NW_NFY_ID_INTERN_CT_RESULT,             /**< Internet connection test result, pv_nfy_param: 0=>Fail; 1=>Success */
#ifdef APP_UPG_SUPPORT
    NW_NFY_ID_INTERN_CT_UPG_RESULT,          /**< Internet connection test result just for netupdate pv_nfy_param: 0=>Fail; 1=>Success */
#endif
    NW_NFY_ID_NETWORK_CONN_ENABLED,         /**< Network connection enabled */
    NW_NFY_ID_NETWORK_CONN_DISABLED,        /**< Network connection diabled */

    NW_NFY_ID_WIRLESS_PLUGIN,               /**< Ethernet cable plugged in, pv_nfy_param: not used */
    NW_NFY_ID_WIRLESS_UNPLUG,            /**< Ethernet cable unplugged, pv_nfy_param: not used */
    NW_NFY_ID_WLAN_INIT_IND,                /**< WLAN module init \ref NotifyMsg "indication" */
    NW_NFY_ID_WLAN_DEINIT_IND,              /**< WLAN module deinit \ref NotifyMsg "indication" */
    NW_NFY_ID_WLAN_START_IND,                /**< WLAN module init \ref NotifyMsg "indication" */
    NW_NFY_ID_WLAN_SCAN,                    /**< Scan result notification \ref NotifyMsg "message" */
    NW_NFY_ID_WLAN_ASSOCIATE,               /**< Association result notification \ref NotifyMsg "message" */
    NW_NFY_ID_WLAN_WPS_ASSOC_SETTING,       /**< WPS association notification \ref NotifyMsg "message" */
    NW_NFY_ID_WLAN_WPS_STATE,               /**< WPS processing \ref WPSStatus "state" */
    NW_NFY_ID_WLAN_WPS_ASSOCIATE,           /**< WPS Association result notification \ref NotifyMsg "message" */

    NW_NFY_ID_WLAN_DRIVER_START_IND,
    NW_NFY_ID_WLAN_DRIVER_START_FAILED,

    NW_NFY_ID_INITED,                       /**< Network initialize completed notify */
	NW_NFY_ID_INTERN_CT_RESULTv6, 			/**< Internet connection test_v6 result, pv_nfy_param: 0=>Fail; 1=>Success */
	NW_NFY_ID_INTERN_CT_RESULT_ASYNC, 			/**< Internet connection test_v6 result, pv_nfy_param: 0=>Fail; 1=>Success */
	NW_NFY_ID_INTERN_CT_RESULTv6_ASYNC, 			/**< Internet connection test_v6 result, pv_nfy_param: 0=>Fail; 1=>Success */

    NW_NFY_ID_LAST_ENTRY                    /**< Only for count*/

}NW_NFY_ID_T;

typedef VOID (*nw_nfy_fct)(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param);


#ifdef APP_NETWORK_WIFI_SUPPORT
#define NW_NET_INTERFACE_ETH0          ((UINT8) 0)
#define NW_NET_INTERFACE_WIFI          ((UINT8) 1)
#define NW_NET_INTERFACE_OUT_WIFI          ((UINT8) 1)
#define NW_NET_INTERFACE_BUILT_IN_WIFI          ((UINT8) 2)


/**
 * @brief This enum lists all Wifi states.
 */
typedef enum _NW_WLAN_STATE_T
{
    NW_WLAN_UNPLUG,          /**wifi suspended state */
    NW_WLAN_PLUG_STOP,           /**wifi started state */
    NW_WLAN_ASSOCIATING,         /* do associating */
    NW_WLAN_START_DISASSOC,              /**< wifi disassociated state */
    NW_WLAN_ASSOCIATE        /**< wifi has associated successfully */
}NW_WLAN_STATE_T;

#endif


/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32  a_nw_register( nw_nfy_fct pf_nfy, VOID* pv_tag, UINT32* pui4_nfy_id );
extern INT32  a_nw_unregister( UINT32 ui4_nfy_id );
extern INT32  a_nw_enable_network_connection(VOID);
extern INT32  a_nw_disable_network_connection(VOID);
extern INT32  a_nw_manual_ip_config(const NW_IP_INFO_T* pt_ip_info);
extern INT32  a_nw_start_dhcp_ip_config(VOID);
extern INT32  a_nw_stop_dhcp_ip_config(VOID);
extern INT32  a_nw_get_crnt_ip_info( NW_IP_INFO_T* pt_ip_info );
extern INT32  a_nw_get_ip_info(NW_IP_INFO_T* pt_ip_info, CHAR* ps_if_name);
extern INT32  a_nw_get_dhcp_status( NW_DHCP_STATE_T* pe_dhcp_state );
extern INT32  a_nw_connection_test(/*NW_CONNECTION_TEST_TYPE_T e_type, */CHAR* hostname);
extern INT32  a_nw_connection_test6(/*NW_CONNECTION_TEST_TYPE_T e_type, */CHAR* hostname);
extern INT32  a_nw_connection_test_async(/*NW_CONNECTION_TEST_TYPE_T e_type, */CHAR* hostname);

#ifdef APP_UPG_SUPPORT
extern INT32  a_nw_connection_test_upg(CHAR* hostname);
#endif

#ifdef APP_NET_DLNA_SUPPORT
extern INT32  a_nw_enable_dlna(VOID);
extern INT32  a_nw_disable_dlna(VOID);
#ifdef APP_DMR_SUPPORT
extern INT32  a_nw_enable_dlna_dmr(VOID);
extern INT32  a_nw_disable_dlna_dmr(VOID);
#endif
#endif

extern INT32  a_nw_get_ethernet_connect_info(BOOL* pb_is_plug);
extern INT32  a_nw_is_network_connected(BOOL* pb_is_connected);
extern INT32  a_nw_ntoa(char * ps_ip_str,UINT32 ui4_ip);
extern INT32  a_nw_aton(UINT32* pui4_ip, char * ps_ip_str);
extern INT32  a_nw_get_mac_addr(CHAR *psz_name,UINT8 *pMacAddr);
extern INT32  a_nw_get_mac_addr_string(CHAR *psz_name, char * ps_mac_str);
extern INT32  a_nw_save_mac_addr(const CHAR *psz_name,UINT8 *pMacAddr);
extern INT32  a_nw_save_mac_addr_string(CHAR *psz_name, char * ps_mac_str);
extern INT32 a_nw_net_ni_enable( const CHAR *ifname, INT8 u1EnableNi );

//write eeprom about ipv6 info without dns
extern INT32 a_nw_set_ipv6_nodns_config(const NW_IPV6_INFO_T_NO_DNS *p_tip_info);

//read eeprom about ipv6 info with dns
extern INT32 a_nw_get_ipv6_config(NW_IPV6_INFO_T* pt_ip_info);

//set the ipv6 info without dns manually
extern INT32 a_nw_ip_v6_config(NW_IPV6_INFO_T_NO_DNS *p_tip_info);

//set the ipv6 dns info
extern INT32 a_nw_dns_v6_config(CHAR* pc_dns1, CHAR* pc_dns2);

//Enable or disable the ipv6's auto state
extern INT32 a_nw_ip_v6_auto(int b_enable, BOOL b_restart_if);

//Enable or disable the ipv6's dhcpc
extern INT32 a_nw_ip_v6_dhcp(BOOL b_enable);

//Enable or disable the ipv6 dns's auto state
extern INT32 a_nw_dns_v6_auto(BOOL b_enable);
extern VOID  a_nw_ping_v6(CHAR * ps_ip,
                          INT32  i4_len,
                          INT16  i2_wait,
                          VOID (*notify_fn) (INT16 i2_rsp_time));
extern INT32 a_nw_get_v6_info(NW_IPV6_INFO_T *pt_info);

extern INT32 a_nw_set_prefer_v6(BOOL b_isv6);
extern INT32 a_nw_set_ipv6_all_config(void);
extern INT32 a_nw_no_ipv6_config(void);

extern INT32 a_nw_set_ip_v6_config(INT32 ip_type, INT32 dns_type, NW_IPV6_INFO_T *p_tip_info);

#ifdef SUPPORT_2_DONGLES
extern INT32 a_nw_set_device_name( const CHAR *ifname );
#endif
#ifdef APP_NETWORK_WIFI_SUPPORT
extern BOOL   a_nw_is_ethernet_plugin(VOID);
extern INT32  a_nw_wlan_drv_start(VOID);
extern INT32  a_nw_wlan_drv_stop(VOID);

extern INT32  a_nw_get_wlan_signal_lvl_from_rssi(VOID);
extern INT32  a_nw_chg_network_interface(UINT8 ui1_interface);
extern INT32  a_nw_set_wlan_bssid(NET_802_11_BSSID_T*          pt_Bssid);
extern INT32  a_nw_get_wlan_bssid(NET_802_11_BSSID_T*          pt_Bssid);
extern INT32  a_nw_set_wlan_ssid(NET_802_11_SSID_T*           pt_Ssid);
extern INT32  a_nw_get_wlan_ssid(NET_802_11_SSID_T*           pt_Ssid);
extern INT32  a_nw_set_wlan_assoc_case(NET_802_11_ASSOC_CASE_T     e_AssocCase);
extern INT32  a_nw_get_wlan_assoc_case(NET_802_11_ASSOC_CASE_T*     pe_AssocCase);
extern INT32  a_nw_set_wlan_auth_mode(NET_802_11_AUTH_MODE_T      e_AuthMode);
extern INT32  a_nw_get_wlan_auth_mode(NET_802_11_AUTH_MODE_T*      pe_AuthMode);
extern INT32  a_nw_set_wlan_auth_cipher(NET_802_11_AUTH_CIPHER_T    e_AuthCipher);
extern INT32  a_nw_get_wlan_auth_cipher(NET_802_11_AUTH_CIPHER_T*    pe_AuthCipher);
extern INT32  a_nw_set_wlan_key(NET_802_11_KEY_T*           pt_Key);
extern INT32  a_nw_get_wlan_key(NET_802_11_KEY_T*           pt_Key);
extern INT32  a_nw_wlan_wps_refresh_pin(char *s_pin, UINT32 ui4_len);
extern INT32  a_nw_wlan_wps_get_pin(char *s_pin, UINT32 ui4_len);

extern INT32 a_nw_wlan_scan(VOID);
extern INT32 a_nw_wlan_scan_with_ssid(char * ssid, int ssid_len);
extern INT32 a_nw_wlan_get_scan_result(NET_802_11_SCAN_RESULT_T *pScanResult);
extern INT32 a_nw_wlan_get_ess_list(NET_802_11_ESS_LIST_T *pEssList);
extern INT32 a_nw_wlan_associate(NET_802_11_ASSOCIATE_T *pAssociate);
extern INT32 a_nw_wlan_disassociate(VOID);
extern INT32 a_nw_wlan_get_curr_bss(NET_802_11_BSS_INFO_T *pCurrBss);
extern INT32 a_nw_wlan_wps_associate(NET_802_11_WPS_ASSOC_MODE_T eWpsMode);
extern INT32 a_nw_wlan_wps_get_status(INT32 *status);
extern INT32 a_nw_wlan_wps_cancel(void);
extern INT32 a_nw_wlan_status( NW_WLAN_STATE_T* pe_wlan_state );
extern INT32 a_nw_wlan_get_rssi(NET_802_11_WIFI_RSSI_T *pt_rssi);

extern INT32 a_nw_wlan_is_started(BOOL* pb_wlan_started );
extern INT32 a_menu_network_forget_temporary_ssid(VOID);

#ifdef SUPPORT_2_DONGLES
extern INT32 a_nw_wlan_status_ex( UINT8 ui1_interface,NW_WLAN_STATE_T* pe_wlan_state );
extern INT32 a_nw_wlan_disable_built_in_dongle( VOID );
#else

extern INT32 a_nw_get_wlan_driver_init_status( BOOL* b_wlan_drv );

#endif
#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
extern INT32  a_nw_my_net_pls_enable(void);
extern INT32  a_nw_my_net_pls_disable(void);
extern INT32  a_nw_my_net_pls_refresh(void);
extern INT32  a_nw_my_net_pls_set_perm (const CHAR* ps_path,
                                        const CHAR* ps_user,
                                        const CHAR* ps_passwd);
#endif

extern INT32  a_get_nw_init_status(VOID);
extern INT32  a_nw_pre_init(VOID);
extern INT32  a_nw_init(VOID);
extern INT32  a_nw_init_ex(VOID);

extern INT32  a_nw_default_reset_update(VOID);

#ifdef SUPPORT_2_DONGLES
extern BOOL a_nw_is_ip_retrieved_in_wifi(VOID);
extern INT32 a_nw_connect_wifi_for_fac(CHAR* s_ssid, UINT32 ui4_type);
#endif

extern INT32 a_nw_start_magic_packet_monitor(VOID);
#ifdef MT5583_MODEL
extern BOOL a_nw_check_resume_connection_status(VOID);
#endif
extern BOOL a_nw_check_network_connect_test(VOID);

#ifdef __cplusplus              /* __cplusplus */
}
#endif                          /* __cplusplus */

#endif /* A_NETWORK_H_ */

#endif /* APP_NETWORK_SUPPORT */

