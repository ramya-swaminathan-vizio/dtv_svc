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
 * $RCSfile: network_custom.h,v $
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

#ifndef _A_NETWORK_CUSTOM_H_
#define _A_NETWORK_CUSTOM_H_

#ifdef __cplusplus              /* __cplusplus */
extern          "C" {
#endif                          /* __cplusplus */
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "app_util/a_common.h"
#include "app_util/network/network.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define NW_FREQ_2_4_MIN 2401
#define NW_FREQ_2_4_MAX 2495
#define NW_FREQ_5_MIN 5030
#define NW_FREQ_5_MAX 5990
#define NW_FREQ_6_MIN 5945
#define NW_FREQ_6_MAX 6425
#define NW_FREQ_5_6_OVERLAP_MIN 5945
#define NW_FREQ_5_6_OVERLAP_MAX 5990

typedef enum _NW_WLAN_BAND_T
{
    NW_WLAN_FREQ_2_4_BAND,         /** connected to 2.4G wifi router */
    NW_WLAN_FREQ_5_BAND,           /** connected to 5G wifi router */
    NW_WLAN_FREQ_6_BAND,           /** connected to 6G wifi router */
    NW_WLAN_FREQ_UNKNOWN
}NW_WLAN_BAND_T;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32   nw_custom_set_network_enable(BOOL b_enable);
extern INT32   nw_custom_get_network_enable(BOOL* pb_enable);

#ifdef APP_NET_DLNA_SUPPORT
extern INT32   nw_custom_set_dlna_enable(BOOL b_enable);
extern INT32   nw_custom_get_dlna_enable(BOOL* pb_enable);
#ifdef APP_DMR_SUPPORT
extern INT32   nw_custom_set_dlna_dmr_enable(BOOL b_enable);
extern INT32   nw_custom_get_dlna_dmr_enable(BOOL* pb_enable);
#endif
#endif

extern INT32   nw_custom_set_auto_ip_config(BOOL b_enable);
extern INT32   nw_custom_get_auto_ip_config(BOOL* pb_enable);
extern INT32   nw_custom_set_dhcp_status(UINT8 ui1_dhcp_status);
extern INT32   nw_custom_get_dhcp_status(UINT8* pui1_dhcp_status);
extern INT32   nw_custom_set_ip_addr_config(const NW_IP_INFO_T* pt_ip_info);
extern INT32   nw_custom_get_ip_addr_config(NW_IP_INFO_T* pt_ip_info);

extern INT32   nw_custom_set_auto_ip_config_by_iface(BOOL b_enable, const UINT8 ui1_iface);
extern INT32   nw_custom_get_auto_ip_config_by_iface(BOOL* pb_enable, const UINT8 ui1_iface);
extern INT32   nw_custom_set_dhcp_status_by_iface(UINT8 ui1_dhcp_status, const UINT8 ui1_iface);
extern INT32   nw_custom_get_dhcp_status_by_iface(UINT8* pui1_dhcp_status, const UINT8 ui1_iface);
extern INT32   nw_custom_set_ip_addr_config_by_iface(const NW_IP_INFO_T* pt_ip_info, const UINT8 ui1_iface);
extern INT32   nw_custom_get_ip_addr_config_by_iface(NW_IP_INFO_T* pt_ip_info, const UINT8 ui1_iface);

extern VOID    nw_custom_set_speed(DOUBLE u4_speed);
extern DOUBLE  nw_custom_get_speed(VOID);


#ifdef APP_NETWORK_WIFI_SUPPORT
extern INT32   nw_custom_set_network_interface(UINT8 ui1_interface);
extern INT32   nw_custom_get_network_interface(UINT8* pui1_interface);
extern INT32   nw_custom_set_wlan_bssid(NET_802_11_BSSID_T*          pt_Bssid);
extern INT32   nw_custom_get_wlan_bssid(NET_802_11_BSSID_T*          pt_Bssid);
extern INT32   nw_custom_set_wlan_ssid(NET_802_11_SSID_T*           pt_Ssid);
extern INT32   nw_custom_get_wlan_ssid(NET_802_11_SSID_T*           pt_Ssid);
extern INT32   nw_custom_set_wlan_assoc_case(NET_802_11_ASSOC_CASE_T     e_AssocCase);
extern INT32   nw_custom_get_wlan_assoc_case(NET_802_11_ASSOC_CASE_T*     pe_AssocCase);
extern INT32   nw_custom_set_wlan_auth_mode(NET_802_11_AUTH_MODE_T      e_AuthMode);
extern INT32   nw_custom_get_wlan_auth_mode(NET_802_11_AUTH_MODE_T*      pe_AuthMode);
extern INT32   nw_custom_set_wlan_auth_cipher(NET_802_11_AUTH_CIPHER_T    e_AuthCipher);
extern INT32   nw_custom_get_wlan_auth_cipher(NET_802_11_AUTH_CIPHER_T*    pe_AuthCipher);
extern INT32   nw_custom_set_wlan_key(NET_802_11_KEY_T*        	pt_Key);
extern INT32   nw_custom_get_wlan_key(NET_802_11_KEY_T*        	pt_Key);
extern INT32   nw_custom_set_associate(NET_802_11_ASSOCIATE_T *pAssociate);
extern INT32   nw_custom_get_associate(NET_802_11_ASSOCIATE_T *pAssociate);
extern BOOL    nw_custom_is_lock_ap(NET_802_11_AUTH_MODE_T e_AuthMode, NET_802_11_AUTH_CIPHER_T e_AuthCipher);

#endif

#ifdef APP_NET_NEIGHBOR_SUPPORT
extern INT32   nw_custom_set_my_net_pls_enable(BOOL b_enable);
extern INT32   nw_custom_get_my_net_pls_enable(BOOL* pb_enable);
#endif

extern INT32   nw_custom_init(NW_UTIL_T*    pt_nw);

extern VOID a_nw_custom_disable_interface_change(BOOL   b_disable);
extern BOOL a_nw_custom_is_get_ip_addr(VOID);
extern BOOL a_nw_custom_is_IP_exist(UINT32     ui4_address);
extern BOOL a_nw_custom_nw_wifi_start(VOID);
extern BOOL a_nw_custom_is_eth0_enable(VOID);
extern INT32  a_nw_set_mac_addr(const CHAR *psz_name,UINT8 *pMacAddr);
extern INT32 a_nw_custom_wlan_disassociate(VOID);

extern INT16 a_nw_custom_wifi_signal_remapping(const INT16 i2_level);

extern INT32 a_nw_custom_get_ip_info(NW_IP_INFO_T *pt_ip_info);

extern INT32 a_nw_custom_get_http_url_for_acr(BOOL b_accept);
extern NW_WLAN_BAND_T a_nw_custom_wifi_frequency_band();

#ifdef __cplusplus              /* __cplusplus */
}
#endif                          /* __cplusplus */

#endif /* _A_NETWORK_CUSTOM_H_ */

#endif /* APP_NETWORK_SUPPORT */

