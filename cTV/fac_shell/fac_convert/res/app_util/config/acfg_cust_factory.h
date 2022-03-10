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
 * $RCSfile: acfg_custom.h,v $
 * $Revision: #6 $
 * $Date: 2014/08/25 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_FACTORY_H_FAC_SHELL_
#define _ACFG_CUST_FACTORY_H_FAC_SHELL_

#include "u_common.h"
#include "a_gluelayer_comm.h"
#include "a_gluelayer.h"
/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 (*acfg_cust_factory_pre_init_fac)(VOID);
extern INT32 (*acfg_cust_factory_post_init_fac)(VOID);
             
extern INT32 (*acfg_cust_fact_get_min_max_fac)(UINT16  ui2_id, INT16*  pi2_min, INT16*  pi2_max);
extern INT32 (*acfg_cust_fact_incr_fac)(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 (*acfg_cust_fact_decr_fac)(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 (*acfg_cust_fact_get_fac)(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 (*acfg_cust_fact_set_fac)(UINT16  ui2_id, INT16   i2_val);
extern INT32 (*acfg_cust_fact_update_fac)( UINT16  ui2_id);
extern INT32 (*a_cfg_custom_reset_fac_fac)(VOID);
extern INT32 (*a_cfg_custom_reset_daylight_saving_setting_fac)(VOID);
extern INT32 (*a_cfg_custom_reset_fac_clr_tmp_fac)(VOID);
extern INT32 (*a_cfg_custom_get_fac_reserv_fac)(UINT16*  pui2_val, SIZE_T* pz_size);
extern INT32 (*a_cfg_custom_set_fac_reserv_fac)(UINT16*  pui2_val, SIZE_T z_size);
extern INT32 (*a_cfg_custom_set_factory_colortemp_fac)(UINT16  ui2_id, INT16 i2_val);
extern INT32 (*a_cfg_custom_reset_factory_colortemp_fac)(VOID);
extern BOOL  (*a_cfg_cust_fac_discrete_key_handler_fct_fac)( UINT32 *ui4_key_code);
extern BOOL  (*a_factory_need_burning_in_fac)(VOID);
extern BOOL  (*a_factory_disable_rtc_wakeup_fac)(VOID);
extern INT32 (*a_nav_flicker_register_fac)(VOID);
////////////////////
extern INT32 acfg_cust_factory_pre_init(VOID);
extern INT32 acfg_cust_factory_post_init(VOID);
             
extern INT32 acfg_cust_fact_get_min_max(UINT16  ui2_id, INT16*  pi2_min, INT16*  pi2_max);
extern INT32 acfg_cust_fact_incr(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 acfg_cust_fact_decr(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 acfg_cust_fact_get(UINT16  ui2_id, INT16*  pi2_val);
extern INT32 acfg_cust_fact_set(UINT16  ui2_id, INT16   i2_val);
extern INT32 acfg_cust_fact_update( UINT16  ui2_id);
extern INT32 a_cfg_custom_reset_fac(VOID);
extern INT32 a_cfg_custom_reset_daylight_saving_setting(VOID);
extern INT32 a_cfg_custom_reset_fac_clr_tmp(VOID);
extern INT32 a_cfg_custom_get_fac_reserv(UINT16*  pui2_val, SIZE_T* pz_size);
extern INT32 a_cfg_custom_set_fac_reserv(UINT16*  pui2_val, SIZE_T z_size);
extern INT32 a_cfg_custom_set_factory_colortemp(UINT16  ui2_id, INT16 i2_val);
extern INT32 a_cfg_custom_reset_factory_colortemp(VOID);
extern BOOL  a_cfg_cust_fac_discrete_key_handler_fct( UINT32 *ui4_key_code);
extern INT32 a_nav_flicker_register(VOID);

/*-----------------------------------------------------------------------------
 * Name: a_factory_need_burning_in
 *
 * Description: Check some conditions to decide to power on and enter burning mode for factory.
 *              Ex.:
 *                  burning in flag is set to ON
 *                  odm index is 0
 *              The conditions how to check is implemented by odm, only the return value is used by common portion
 * Inputs: -
 *
 * Outputs: BOOL true: need enter burning mode directly after power on
 *               false: needn't enter burning mode after power on
 * Returns: -
 *-----------------------------------------------------------------------------*/
extern BOOL  a_factory_need_burning_in(VOID);

/*-----------------------------------------------------------------------------
 * Name: a_factory_disable_rtc_wakeup
 *
 * Description: Check some conditions to decide to need RTC Wakeup or not in ECO mode after 1Min.
 *              The conditions how to check is implemented by odm, only the return value is used by common portion 
 *
 * Inputs: -
 *
 * Outputs: BOOL true: will disable RTC Wakeup in ECO mode after DC Off
 *               false: should not disable RTC Wakeup.
 *
 * Returns: -
 *-----------------------------------------------------------------------------*/
extern BOOL a_factory_disable_rtc_wakeup(VOID);

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_FACTORY_H_FAC_SHELL_ */
