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
 * $RCSfile: menu_custom.h,v $
 * $Revision: #2 $
 * $Date: 2013/06/21 $
 * $Author: sin_heyiwang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/14 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 530b5f614fc48ad655af79370de4cf1b $
 *
 * Description:
 *         This file contains the declarations of APPLICATION-RELATED functions
 * of the MENU applcation.
 *---------------------------------------------------------------------------*/

#ifndef _MENU_CUST_DEFINE_H_
#define _MENU_CUST_DEFINE_H_


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_sys_name.h"
#include "u_sb.h"
#include "u_time_msrt.h"
#include "u_iom.h"

#include "menu2/menu_page_tree.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#ifndef VERSION_KEY_LIST
#define VERSION_KEY_LIST        {BTN_DIGIT_2, BTN_DIGIT_0, BTN_DIGIT_1, BTN_DIGIT_3};
#endif

#define APP_MENU_CUSTOM_FACTORY_TREE
#define APP_MENU_CUSTOM_IOM_NFY_FCT
/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

#ifdef APP_MENU_CUSTOM_FACTORY_TREE
extern UINT32 ui4_page_cust_fac_ver_info;

extern MENU_PAGE_FCT_TBL_T  t_g_menu_custom_page_fact_ver_info;

extern MENU_ITEM_T     t_g_menu_custom_item_fac_adc_gain_r;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_adc_gain_g;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_adc_gain_b;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_adc_offset_r;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_adc_offset_g;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_adc_offset_b;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_hard_limiter;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_flicker_pattern;
extern MENU_ITEM_T     t_g_menu_custom_item_fact_model;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_burning_mode;
#if 1 // David 20181212, for SSP.
extern MENU_ITEM_T     t_g_menu_custom_item_fac_ssp;
#endif

#if 1//added by Mark
extern MENU_ITEM_T     t_g_menu_custom_item_fac_backlight_check;
#endif

#ifdef APP_SPREAD_SPECTRUM
    extern MENU_ITEM_T     t_g_menu_custom_item_fac_spread_spectrum;
#endif

extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_mode;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_bri_r;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_bri_g;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_bri_b;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_bri_c;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_bri_m;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_bri_y;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_hue_r;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_hue_g;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_hue_b;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_hue_c;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_hue_m;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_hue_y;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_sat_r;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_sat_g;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_sat_b;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_sat_c;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_sat_m;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_sat_y;
extern MENU_ITEM_T     t_g_menu_custom_item_fac_vid_cms_reset;

//extern MENU_ITEM_T t_menu_item_page_cust_fac_pq_bypass;
extern MENU_ITEM_T t_menu_item_page_cust_fac_pure_pattern;
//extern UINT32 ui4_page_sub_cust_fac_pq_bypass;
extern INT32  menu_custom_init_factory_tree(VOID);
extern BOOL   menu_custom_version_key_filter(UINT32    ui4_keycode);
extern INT32  menu_cust_fac_init(VOID);
extern INT32  menu_cust_fac_settings_init(VOID);
extern INT32  menu_cust_fact_exit(VOID);
// andy extern INT32  menu_custom_page_fact_ver_info_init(VOID);
extern BOOL   menu_cust_fact_is_reset_page(UINT32 ui4_page_id);
#endif

#ifdef APP_MENU_CUSTOM_IOM_NFY_FCT
extern VOID    menu_custom_iom_nfy_fct(HANDLE_T         h_app,
                                       IOM_NFY_COND_T   e_nfy_cond,
                                       UINT32           ui4_evt_code);

extern UINT32  menu_custom_fct_process_msg(UINT32       ui4_type,
                                           const VOID*  pv_msg,
                                           SIZE_T       z_msg_len,
                                           BOOL*        pb_processed);
#endif

#endif /* _MENU_CUST_DEFINE_H_ */
