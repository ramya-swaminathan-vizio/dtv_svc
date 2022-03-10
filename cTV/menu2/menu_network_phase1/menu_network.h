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
 * $RCSfile: menu_page_adv_scan_rng.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/22 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 223730d1bdc36ed27cb26dea5de9232d $
 *
 * Description:
 *      This scan includes both ATV channel scan and DTV channel scan.
 *---------------------------------------------------------------------------*/
#ifndef _MENU_NETWORK_H_
#define _MENU_NETWORK_H_

#ifdef APP_NETWORK_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "app_util/a_network.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define NW_PAGE_ID_AP_LST                     (UINT32) (0)
#define NW_PAGE_ID_TEST                       (UINT32) (1)
#define NW_PAGE_ID_AP_NAME                    (UINT32) (2)
#define NW_PAGE_ID_MAN_SET                    (UINT32) (3)
#define NW_PAGE_ID_NET_INFO                   (UINT32) (4)
#define NW_PAGE_ID_LAST_ENTRY                 (UINT32) (5)

#define NW_PAGE_ID_PWD                        (NW_PAGE_ID_LAST_ENTRY +1)
#define NW_PAGE_ID_ROOT                       (UINT32) (0xff)

extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_net_info;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_ip_setting;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_ip_setting_dhcp;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_test;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_network;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_pwd;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_input_ssid;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_ap_list;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_common_nw_test_connection;
extern UINT32 ui4_g_menu_page_nw;

//add for net info
extern MENU_PAGE_FCT_TBL_T        t_g_menu_common_nw_info;


typedef VOID (*nw_dialog_cb_fct)(UINT32 ui4_key_code);

typedef struct _MENU_NETWORK_NFY_DATA_T
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}MENU_NETWORK_NFY_DATA_T;

typedef enum _MENU_PROTOCOL_SCAN_E
{
    MENU_PROTOCOL_SCAN_NULL = 0,
    MENU_PROTOCOL_SCAN_SELECT,
    MENU_PROTOCOL_SCAN_TERMS_VIZIO,
    MENU_PROTOCOL_SCAN_POLICY_VIZIO,
    MENU_PROTOCOL_SCAN_TERMS_GOOGLE,
    MENU_PROTOCOL_SCAN_POLICY_GOOGLE,
    MENU_PROTOCOL_SCAN_ACCEPT_ALL,
    MENU_PROTOCOL_SCAN_SMART_CAST_POLICY,
    MENU_PROTOCOL_SCAN_VIEWING_DATA_POLICY,
    MENU_PROTOCOL_SCAN_VIEWING_DATA_OVERVIEW
}MENU_PROTOCOL_SCAN_E;

typedef struct _MENU_NW_TOS_SUB_BASE_DATA_T
{
    MENU_PROTOCOL_SCAN_E    e_scan_text;
    UINT16                  ui2_title_text;
}MENU_NW_TOS_SUB_BASE_DATA_T;

typedef enum _E_MENU_UI_DHCP
{
    MENU_UI_DHCP_ON,
    MENU_UI_DHCP_OFF,
    MENU_UI_DHCP_DNS_ONLY
}E_MENU_UI_DHCP;

extern INT32 menu_netowrk_nav_back(VOID);
extern INT32 menu_netowrk_connect_success_back(VOID);
extern INT32 menu_network_hide_confirm_dialog(BOOL  b_repaint);

/* update last shadow status */
extern INT32 menu_network_last_shadow_update_position(HANDLE_T h_item, BOOL b_repaint);
extern INT32 menu_network_last_shadow_hide(BOOL b_repaint);

extern INT32    menu_network_is_DNS_available(VOID);
extern BOOL     menu_network_is_NTP_available(VOID);
extern INT32 menu_netowrk_nav_go(
                    UINT32 ui4_network_page_id,
                    MENU_PAGE_HINT_T* pt_hint);
extern INT32 menu_network_show_confirm_dialog(UTF16_T* 		pw2s_msg_text,
                                       	UTF16_T* 			pw2s_btn_text,
                                       	nw_dialog_cb_fct 	pf_back_try_again,
                                    	BOOL         		b_repaint
                                    	);
extern INT32 menu_network_show_confirm_dialog_ex(
                                        UTF16_T* 			pw2s_msg_text,
                                        UTF16_T*            pw2s_btn_try_again,
                                        UTF16_T*            pw2s_btn_try_another,
                                        nw_dialog_cb_fct    pf_back_try_again,
                                        nw_dialog_cb_fct    pf_back_try_another,
                                        BOOL                b_repaint
                                        );
extern VOID nw_confirm_dialog_set_focus_try_again(VOID);
extern VOID nw_confirm_dialog_set_focus_try_another(VOID);
extern BOOL  menu_network_is_page_back(VOID);
extern INT32 menu_network_get_associate_data(NET_802_11_ASSOCIATE_T** ppt_associate);
extern NET_802_11_ESS_INFO_T*  menu_network_get_ap_by_idx(UINT16     ui2_idx);
extern INT32 menu_ap_list_page_clean_ap_list(VOID);
extern INT32 menu_ap_list_page_add_ap(NET_802_11_ESS_INFO_T* p_essInfo,
                                                 UINT8                  ui1_idx,
                                                 BOOL                   b_wireless_connected);
extern INT32 menu_common_page_ip_setting_dhcp_init(VOID);
extern INT32 menu_common_page_ip_setting_init(VOID);
extern INT32 menu_common_page_nw_test_init(VOID);
extern INT32 menu_common_page_terms_init(VOID);
extern INT32 menu_common_page_network_init(VOID);
extern INT32 menu_common_page_nw_pwd_init(VOID);
extern INT32 menu_common_page_nw_input_ssid(VOID);
extern INT32 menu_common_page_nw_ap_list_init(VOID);
extern INT32 menu_custom_init(VOID);
extern INT32 menu_network_init(VOID);

//Jundi add for network info
extern INT32 menu_common_page_nw_info_init(VOID);

#endif /* APP_NETWORK_SUPPORT */
#endif /* _MENU_NETWORK_H_ */

