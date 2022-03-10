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

#ifndef _MENU_DEVICE_H_
#define _MENU_DEVICE_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "menu2/menu.h"
#include "menu2/menu_page.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum _MENU_DEVICE_PAGE_NAV_TYPE_T
{
    NAV_ROOT_MENU_FROM_ANY_PAGE = 0,
    NAV_PREV_PAGE_FROM_CURRENT_PAGE,
    NAV_DEVICE_SETTING_PAGE_FROM_STATUS_INFO_PAGE,
    NAV_INFO_STATUS_PAGE_FROM_DEVICE_SETTING_PAGE,
    NAV_DEVICE_SETTING_PAGE_FROM_PAIR_WIFI_DEVICE_PAGE,
    NAV_PAIR_WIFI_DEVICE_PAGE_FROM_INFO_STATUS_PAGE,
    NAV_NAME_INPUT_PAGE_FROM_INFO_STATUS_PAGE,
    NAV_ADD_NEW_DEVICE_PAGE_FROM_DEVICE_SETTING_PAGE,
    NAV_DEVICE_SETTING_PAGE_FROM_NAME_INPUT_PAGE,
    NAV_DEVICE_SETTING_PAGE_FROM_INPUT_OPE_LST_PAGE,
    NAV_TYPE_LAST_ENTRY
}MENU_DEVICE_PAGE_NAV_TYPE_T;

typedef enum _MENU_DEVICE_TYPE_T
{
    MENU_DEVICE_TYPE_REMOTE = 0,
    MENU_DEVICE_TYPE_INPUT,
    MENU_DEVICE_TYPE_MIRACAST,
    MENU_DEVICE_TYPE_SOUNDBAR,
    MENU_DEVICE_TYPE_CEC_DEV,
    MENU_DEVICE_TYPE_LAST_ENTRY
}MENU_DEVICE_TYPE_T;

typedef enum _MENU_DEVICE_PAGE_TYPE_T
{
    MENU_DEVICE_PAGE_DEVICE_SETTING = 0,
    MENU_DEVICE_PAGE_PAIR_WIFI_DEVICE,
    MENU_DEVICE_PAGE_ADD_NEW_DEVICE
}MENU_DEVICE_PAGE_TYPE_T;

typedef struct _MENU_DEVICE_REMOTE_DATA_T
{
    UINT8 ui1_remote_idx;
}MENU_DEVICE_REMOTE_DATA_T;

typedef struct _MENU_DEVICE_INPUT_DATA_T
{
    UINT8    ui1_input_src_idx;
    UTF16_T* pw2s_user_name;
    UTF16_T* pw2s_disp_name;
}MENU_DEVICE_INPUT_DATA_T;

typedef struct _MENU_DEVICE_MIRACAST_DATA_T
{
    UINT8 ui1_miracast_idx;
}MENU_DEVICE_MIRACAST_DATA_T;

typedef struct _MENU_DEVICE_SOUNDBAR_DATA_T
{
    UINT8 ui1_soundbar_idx;
}MENU_DEVICE_SOUNDBAR_DATA_T;

#ifdef APP_CEC_MENU
typedef struct _MENU_DEVICE_CEC_DATA_T
{
    UINT8 ui1_cec_dev_idx;
    UTF16_T* pw2s_cec_osd_name;
}MENU_DEVICE_CEC_DATA_T;
#endif

typedef struct _MENU_DEVICE_PAGE_DEVICE_INFO_T
{
    MENU_DEVICE_TYPE_T e_current_device_type;
    union
    {
        MENU_DEVICE_REMOTE_DATA_T t_remote;
        MENU_DEVICE_INPUT_DATA_T t_input;
        MENU_DEVICE_MIRACAST_DATA_T t_miracast;
        MENU_DEVICE_SOUNDBAR_DATA_T t_soundbar;
    #ifdef APP_CEC_MENU
    	MENU_DEVICE_CEC_DATA_T t_cec_dev;
    #endif
    }u_device_data;
}MENU_DEVICE_PAGE_DEVICE_INFO_T;

#define MENU_DEVICE_NAME_MAX_LEN         (32)

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
extern MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_device_setting;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_mobile_device;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_device_status_info;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_pair_wifi_device;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_add_new_device;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_name_input;
extern UINT32 ui4_g_menu_page_inp_naming;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_input_ope_list;
extern UINT32 ui4_g_page_input;
/*KASI*/
extern MENU_PAGE_FCT_TBL_T  t_g_menu_device_page_bt_device;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_item_page_other_devices;
extern MENU_PAGE_FCT_TBL_T  t_g_menu_item_page_forget_paired_devices;

extern MENU_PAGE_FCT_TBL_T t_g_menu_user_manual;
/*-----------------------------------------------------------------------------
                    function declaraions
 ----------------------------------------------------------------------------*/
extern INT32 menu_device_init(VOID);
extern INT32 menu_device_page_device_setting_init(VOID);
extern INT32 menu_device_page_mobile_device_init(VOID);
extern INT32 menu_user_manual_page_init(VOID);
extern VOID mobile_device_delete_paired_device(VOID);
extern INT32 mobile_device_get_mobile_dev_name(UTF16_T * p_dev_name);
extern INT32 menu_user_manual_page_init(VOID);
extern INT32 menu_device_page_device_setting_init_no_wifi_remote(VOID);
extern INT32 menu_device_page_device_status_info_init(VOID);
extern INT32 menu_device_page_pair_wifi_device_init(VOID);
extern INT32 menu_device_page_add_new_device_init(VOID);
extern INT32 menu_device_page_name_input_init(VOID);
extern INT32 menu_device_page_nav_go(MENU_DEVICE_PAGE_NAV_TYPE_T e_page_nav_type,
                                                 MENU_PAGE_HINT_T* pt_hint);
extern INT32 menu_device_page_nav_go_no_wifi_remote(MENU_DEVICE_PAGE_NAV_TYPE_T e_page_nav_type,
                                                 MENU_PAGE_HINT_T* pt_hint);
extern INT32 menu_device_get_device_info(MENU_DEVICE_PAGE_DEVICE_INFO_T* pt_device_info);
extern INT32 menu_device_get_device_info_no_wifi_remote(MENU_DEVICE_PAGE_DEVICE_INFO_T* pt_device_info);
extern UINT32 menu_device_get_pageid(MENU_DEVICE_PAGE_TYPE_T e_page_type);
extern UINT8 menu_device_cec_list_idx_to_cfg_idx(UINT8 ui1_idx);
extern UINT8 menu_device_cec_cfg_idx_to_list_idx(UINT8 ui1_idx);
extern UINT8 menu_device_cec_list_idx_to_cfg_idx_no_wifi_remote(UINT8 ui1_idx);
extern UINT8 menu_device_cec_cfg_idx_to_list_idx_no_wifi_remote(UINT8 ui1_idx);
extern INT32 menu_input_ope_lst_init(VOID);

#endif /* _MENU_DEVICE_H_ */

