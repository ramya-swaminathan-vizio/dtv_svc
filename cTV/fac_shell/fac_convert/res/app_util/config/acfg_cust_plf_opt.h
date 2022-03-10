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
#ifndef _ACFG_CUST_PLF_OPT_H_FAC_SHELL_
#define _ACFG_CUST_PLF_OPT_H_FAC_SHELL_

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 (*acfg_cust_plf_opt_pre_init_fac) (VOID);
extern INT32 (*acfg_cust_plf_opt_post_init_fac) (VOID);
extern INT32 (*a_cfg_custom_plf_opt_get_3d_support_fac)(BOOL* pb_support);
extern INT32 (*a_cfg_custom_plf_opt_get_pip_support_fac)(BOOL* pb_support);
extern INT32 (*a_cfg_custom_plf_opt_get_bt_support_fac)(BOOL* pb_support);
extern INT32 (*a_cfg_custom_plf_opt_set_3d_support_fac)(BOOL b_support);
extern INT32 (*a_cfg_custom_plf_opt_set_pip_support_fac)(BOOL b_support);
extern INT32 (*a_cfg_custom_plf_opt_set_bt_support_fac)(BOOL b_support);
extern INT32 (*a_cfg_custom_plf_opt_get_model_name_fac)(CHAR* s_str, UINT8 ui1_len);
extern INT32 (*a_cfg_custom_plf_opt_get_pq_version_fac)(CHAR* s_str);
extern INT32 (*a_cfg_custom_plf_opt_set_lightsensor_fac)(UINT16 ui2_idx);
extern INT32 (*a_cfg_custom_plf_opt_set_letterbox_detection_fac)(UINT16 ui2_idx);
extern INT32 (*a_cfg_custom_plf_opt_set_dcr_setting_fac)(UINT16 ui2_idx);
extern INT32 (*a_cfg_custom_plf_opt_get_lightsensor_fac)(void);
extern INT32 (*a_cfg_custom_plf_opt_get_dcr_setting_fac)(void);
extern INT32 (*a_cfg_custom_plf_opt_get_model_memc_flag_fac)(UINT32 *pui4_memc_flag);
extern INT32 (*a_cfg_custom_get_is_support_local_dimming_fac)(BOOL *pb_support);
extern BOOL  (*a_cfg_custom_plf_opt_is_analog_aud_out_support_fac)(UINT8 *pui1_audio_output_type);
extern BOOL  (*a_cfg_custom_plf_opt_get_color_tuner_dynamic_address_fac)(UINT32 *ui4_dynamic_address);
extern INT32 (*a_cfg_custom_plf_opt_set_cc_onoff_fac)(UINT32 ui4_onoff);
extern UINT8 (*a_cfg_custom_plf_opt_get_usb_num_fac)(VOID);
extern UINT8 (*C_Get_YPbPr_flag_fac)( VOID);
extern INT32 (*a_cfg_custom_plf_opt_get_model_id_fac)(VOID);//wayne
extern INT32 (*a_cfg_custom_plf_opt_start_aging_fac)(VOID);
extern INT32 (*a_cfg_custom_plf_opt_end_aging_fac)(VOID);
extern INT32 (*a_cfg_custom_plf_opt_get_aq_version_fac)(CHAR* s_str);//wayne
extern INT32 (*a_cfg_custom_plf_opt_get_device_class_fac)(CHAR* ps_str);
extern BOOL  (*a_cfg_custom_plf_opt_model_name_with_ld_fac)(CHAR* s_model);

extern INT32 acfg_cust_plf_opt_pre_init (VOID);
extern INT32 acfg_cust_plf_opt_post_init (VOID);
extern INT32 a_cfg_custom_plf_opt_get_3d_support(BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_get_pip_support(BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_get_bt_support(BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_set_3d_support(BOOL b_support);
extern INT32 a_cfg_custom_plf_opt_set_pip_support(BOOL b_support);
extern INT32 a_cfg_custom_plf_opt_set_bt_support(BOOL b_support);
extern INT32 a_cfg_custom_plf_opt_get_model_name(CHAR* s_str, UINT8 ui1_len);
extern INT32 a_cfg_custom_plf_opt_get_pq_version(CHAR* s_str);
extern INT32 a_cfg_custom_plf_opt_set_lightsensor(UINT16 ui2_idx);
extern INT32 a_cfg_custom_plf_opt_set_letterbox_detection(UINT16 ui2_idx);
extern INT32 a_cfg_custom_plf_opt_set_dcr_setting(UINT16 ui2_idx);
extern INT32 a_cfg_custom_plf_opt_get_lightsensor(void);
extern INT32 a_cfg_custom_plf_opt_get_dcr_setting(void);
extern INT32 a_cfg_custom_plf_opt_get_model_memc_flag(UINT32 *pui4_memc_flag);
extern INT32 a_cfg_custom_get_is_support_local_dimming(BOOL *pb_support);
extern BOOL  a_cfg_custom_plf_opt_is_analog_aud_out_support(UINT8 *pui1_audio_output_type);
extern BOOL  a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(UINT32 *ui4_dynamic_address);
extern INT32 a_cfg_custom_plf_opt_set_cc_onoff(UINT32 ui4_onoff);
extern UINT8 a_cfg_custom_plf_opt_get_usb_num(VOID);
extern UINT8 C_Get_YPbPr_flag( VOID);
extern INT32 a_cfg_custom_plf_opt_get_model_id(VOID);//wayne
extern INT32 a_cfg_custom_plf_opt_start_aging(VOID);
extern INT32 a_cfg_custom_plf_opt_end_aging(VOID);
extern INT32 a_cfg_custom_plf_opt_get_aq_version(CHAR* s_str);//wayne
extern INT32 a_cfg_custom_plf_opt_get_device_class(CHAR* ps_str);
extern BOOL  a_cfg_custom_plf_opt_model_name_with_ld(CHAR* s_model);
/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_PLF_OPT_H_FAC_SHELL_ */
