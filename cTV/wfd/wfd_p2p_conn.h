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
 * $RCSfile: wfd_view.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: cheng.shen $
 * $MD5HEX: 8ebc2c7a2c0fc209f18ef9bd3ccc4afd $
 *
 * Description: 
 *         This header file contains public interfaces, constant and type 
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/



#ifndef WFD_P2P_CONN_H_
#define WFD_P2P_CONN_H_


#include "wfd.h"
#ifdef APP_WFD_SUPPORT
#include "wfd_client_export.h"
#endif

INT32 wfd_p2p_assign_VIZIO_param_for_forceGO(CHAR* s_ssid, CHAR* s_psk);


#if 0
/** P2P events */
private static final String P2P_EVENT_PREFIX_STR = "P2P";

/* P2P-DEVICE-FOUND fa:7b:7a:42:02:13 p2p_dev_addr=fa:7b:7a:42:02:13 pri_dev_type=1-0050F204-1
   name='p2p-TEST1' config_methods=0x188 dev_capab=0x27 group_capab=0x0 */
private static final String P2P_DEVICE_FOUND_STR = "P2P-DEVICE-FOUND";

/* P2P-DEVICE-LOST p2p_dev_addr=42:fc:89:e1:e2:27 */
private static final String P2P_DEVICE_LOST_STR = "P2P-DEVICE-LOST";

/* P2P-GO-NEG-REQUEST 42:fc:89:a8:96:09 dev_passwd_id=4 */
private static final String P2P_GO_NEG_REQUEST_STR = "P2P-GO-NEG-REQUEST";

private static final String P2P_GO_NEG_SUCCESS_STR = "P2P-GO-NEG-SUCCESS";

private static final String P2P_GO_NEG_FAILURE_STR = "P2P-GO-NEG-FAILURE";

private static final String P2P_GROUP_FORMATION_SUCCESS_STR =
        "P2P-GROUP-FORMATION-SUCCESS";

private static final String P2P_GROUP_FORMATION_FAILURE_STR =
        "P2P-GROUP-FORMATION-FAILURE";

/* P2P-GROUP-STARTED p2p-wlan0-0 [client|GO] ssid="DIRECT-W8" freq=2437
   [psk=2182b2e50e53f260d04f3c7b25ef33c965a3291b9b36b455a82d77fd82ca15bc|passphrase="fKG4jMe3"]
   go_dev_addr=fa:7b:7a:42:02:13 */
private static final String P2P_GROUP_STARTED_STR = "P2P-GROUP-STARTED";

/* P2P-GROUP-REMOVED p2p-wlan0-0 [client|GO] reason=REQUESTED */
private static final String P2P_GROUP_REMOVED_STR = "P2P-GROUP-REMOVED";

/* P2P-INVITATION-RECEIVED sa=fa:7b:7a:42:02:13 go_dev_addr=f8:7b:7a:42:02:13
    bssid=fa:7b:7a:42:82:13 unknown-network */
private static final String P2P_INVITATION_RECEIVED_STR = "P2P-INVITATION-RECEIVED";

/* P2P-INVITATION-RESULT status=1 */
private static final String P2P_INVITATION_RESULT_STR = "P2P-INVITATION-RESULT";

/* P2P-PROV-DISC-PBC-REQ 42:fc:89:e1:e2:27 p2p_dev_addr=42:fc:89:e1:e2:27
   pri_dev_type=1-0050F204-1 name='p2p-TEST2' config_methods=0x188 dev_capab=0x27
   group_capab=0x0 */
private static final String P2P_PROV_DISC_PBC_REQ_STR = "P2P-PROV-DISC-PBC-REQ";
/* P2P-PROV-DISC-ENTER-PIN 42:fc:89:e1:e2:27 p2p_dev_addr=42:fc:89:e1:e2:27
   pri_dev_type=1-0050F204-1 name='p2p-TEST2' config_methods=0x188 dev_capab=0x27
   group_capab=0x0 */
private static final String P2P_PROV_DISC_ENTER_PIN_STR = "P2P-PROV-DISC-ENTER-PIN";
/* P2P-PROV-DISC-SHOW-PIN 42:fc:89:e1:e2:27 44490607 p2p_dev_addr=42:fc:89:e1:e2:27
   pri_dev_type=1-0050F204-1 name='p2p-TEST2' config_methods=0x188 dev_capab=0x27
   group_capab=0x0 */
private static final String P2P_PROV_DISC_SHOW_PIN_STR = "P2P-PROV-DISC-SHOW-PIN";

private static final String HOST_AP_EVENT_PREFIX_STR = "AP";
/* AP-STA-CONNECTED 42:fc:89:a8:96:09 */
private static final String AP_STA_CONNECTED_STR = "AP-STA-CONNECTED";
/* AP-STA-DISCONNECTED 42:fc:89:a8:96:09 */
private static final String AP_STA_DISCONNECTED_STR = "AP-STA-DISCONNECTED";

// These definitions match the ones in wpa_supplicant
/* WPS config methods supported */
private static final int WPS_CONFIG_DISPLAY         = 0x0008;
private static final int WPS_CONFIG_PUSHBUTTON      = 0x0080;
private static final int WPS_CONFIG_KEYPAD          = 0x0100;

/* Device Capability bitmap */
private static final int DEVICE_CAPAB_SERVICE_DISCOVERY         = 1;
private static final int DEVICE_CAPAB_CLIENT_DISCOVERABILITY    = 1<<1;
private static final int DEVICE_CAPAB_CONCURRENT_OPER           = 1<<2;
private static final int DEVICE_CAPAB_INFRA_MANAGED             = 1<<3;
private static final int DEVICE_CAPAB_DEVICE_LIMIT              = 1<<4;
private static final int DEVICE_CAPAB_INVITATION_PROCEDURE      = 1<<5;

/* Group Capability bitmap */
private static final int GROUP_CAPAB_GROUP_OWNER                = 1;
private static final int GROUP_CAPAB_PERSISTENT_GROUP           = 1<<1;
private static final int GROUP_CAPAB_GROUP_LIMIT                = 1<<2;
private static final int GROUP_CAPAB_INTRA_BSS_DIST             = 1<<3;
private static final int GROUP_CAPAB_CROSS_CONN                 = 1<<4;
private static final int GROUP_CAPAB_PERSISTENT_RECONN          = 1<<5;
private static final int GROUP_CAPAB_GROUP_FORMATION            = 1<<6;

/**
 * WPS config methods supported
 * @hide
 */
public int wpsConfigMethodsSupported;

/**
 * Device capability
 * @hide
 */
public int deviceCapability;

/**
 * Group capability
 * @hide
 */
public int groupCapability;

public static final int CONNECTED   = 0;
public static final int INVITED     = 1;
public static final int FAILED      = 2;
public static final int AVAILABLE   = 3;
public static final int UNAVAILABLE = 4;

/** Device connection status */
public int status = UNAVAILABLE;

public WifiP2pDevice() {
}

/**
 * @param string formats supported include
 *  P2P-DEVICE-FOUND fa:7b:7a:42:02:13 p2p_dev_addr=fa:7b:7a:42:02:13
 *  pri_dev_type=1-0050F204-1 name='p2p-TEST1' config_methods=0x188 dev_capab=0x27
 *  group_capab=0x0
 *
 *  P2P-DEVICE-LOST p2p_dev_addr=fa:7b:7a:42:02:13
 *
 *  fa:7b:7a:42:02:13
 *
 *  P2P-PROV-DISC-PBC-REQ 42:fc:89:e1:e2:27 p2p_dev_addr=42:fc:89:e1:e2:27
 *  pri_dev_type=1-0050F204-1 name='p2p-TEST2' config_methods=0x188 dev_capab=0x27
 *  group_capab=0x0
 *
 *  P2P-PROV-DISC-ENTER-PIN 42:fc:89:e1:e2:27 p2p_dev_addr=42:fc:89:e1:e2:27
 *  pri_dev_type=1-0050F204-1 name='p2p-TEST2' config_methods=0x188 dev_capab=0x27
 *  group_capab=0x0
 *
 *  P2P-PROV-DISC-SHOW-PIN 42:fc:89:e1:e2:27 44490607 p2p_dev_addr=42:fc:89:e1:e2:27
 *  pri_dev_type=1-0050F204-1 name='p2p-TEST2' config_methods=0x188 dev_capab=0x27
 *  group_capab=0x0
 *
 *  Note: The events formats can be looked up in the wpa_supplicant code
 * @hide
 */
    /** Returns true if WPS push button configuration is supported */
    public boolean wpsPbcSupported() {
        return (wpsConfigMethodsSupported & WPS_CONFIG_PUSHBUTTON) != 0;
    }

    /** Returns true if WPS keypad configuration is supported */
    public boolean wpsKeypadSupported() {
        return (wpsConfigMethodsSupported & WPS_CONFIG_KEYPAD) != 0;
    }

    /** Returns true if WPS display configuration is supported */
    public boolean wpsDisplaySupported() {
        return (wpsConfigMethodsSupported & WPS_CONFIG_DISPLAY) != 0;
    }

    /** Returns true if the device is capable of service discovery */
    public boolean isServiceDiscoveryCapable() {
        return (deviceCapability & DEVICE_CAPAB_SERVICE_DISCOVERY) != 0;
    }

    /** Returns true if the device is a group owner */
    public boolean isGroupOwner() {
        return (groupCapability & GROUP_CAPAB_GROUP_OWNER) != 0;
    }

*/
#endif

typedef struct _WFD_P2P_INFO_T
{
    BOOL b_is_start;
    BOOL b_is_auto_conn;
    BOOL b_set_miracast;
    BOOL b_set_force_go;
    BOOL b_is_go;
    CHAR pin_for_show[DEVICE_INFO_ARR_LEN];
    CHAR pin_for_enter[DEVICE_INFO_ARR_LEN];
    CHAR p_wait_connect_mac[DEVICE_INFO_ARR_LEN];
    CHAR p_connect_mac[DEVICE_INFO_ARR_LEN];
    CHAR p_request_connect_mac[DEVICE_INFO_ARR_LEN];
    CHAR interface_name[DEVICE_INFO_ARR_LEN];
}WFD_P2P_INFO_T;

extern WFD_P2P_INFO_T t_g_wfd_p2p_info;

INT32 wfd_p2p_init(VOID);

BOOL wfd_p2p_get_auto_conn_status(VOID);

void wfd_p2p_set_auto_conn_status(BOOL b_status);

void wfd_p2p_enable_auto_conn_by_device(WFD_MSG_T e_msg, VOID * param);

INT32 wfd_enable_wifi_display(VOID);

INT32 wfd_disable_wifi_display(VOID);

INT32 wfd_p2p_request_as_keypad_of(INT32 i4_index);

INT32 wfd_p2p_get_devicenumber(VOID);

INT32 wfd_p2p_get_wfdDevType(INT32 index);

INT32 wfd_p2p_get_rssi(INT32 index);

INT32 wfd_p2p_get_device_info(WFD_DEV_INFO_TYPE_T e_type,void* pv_param,INT32 index);

INT32 wfd_p2p_connect_pbc(INT32 index);
//call enter pin before
INT32 wfd_p2p_connect_pin(INT32 index);

INT32 wfd_p2p_forced_GO_connect_pbc(INT32 index);

INT32 wfd_p2p_forced_GO_connect_pin(INT32 index);

INT32 wfd_p2p_disconnect(VOID);

INT32 wfd_p2p_enable_force_go(VOID);

INT32 wfd_p2p_disable_force_go(VOID);

INT32 wfd_p2p_enable_miracast(VOID);

INT32 wfd_p2p_disable_miracast(VOID);

INT32 wfd_p2p_connect_cancel(VOID);

INT32 wfd_p2p_disconnect_device(const char* mac);

//ok - connect fail false
INT32 wfd_p2p_is_connected(INT32 index);

INT32 wfd_p2p_find(VOID);

INT32 wfd_p2p_stop_find(VOID);

INT32 wfd_p2p_try_to_find_ip(VOID);

INT32 wfd_p2p_get_connect_ip( char* ps_ip);

char* wfd_p2p_get_pin_to_show(VOID);

INT32 wfd_p2p_set_enter_pin(char* pincode);

INT32 wfd_p2p_request_as_keypad_of(INT32 index);

INT32 wfd_p2p_request_as_display_of(INT32 index);

INT32 wfd_p2p_get_req_name(char * name);

//return index -1 is fail
INT32 wfd_p2p_get_req_index(VOID);
//return index -1 is fail
INT32 wfd_p2p_get_connect_index(VOID);
//call befor do find again
INT32 wfd_p2p_clean_list(VOID);

INT32 wfd_p2p_pin_display_accept(VOID);
INT32 wfd_p2p_disable_wifi_display(VOID);
INT32 wfd_p2p_enable_wifi_display(VOID);
INT32 wfd_p2p_pbc_request_accept();

#endif

