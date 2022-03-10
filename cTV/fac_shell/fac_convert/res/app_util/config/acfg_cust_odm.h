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
 * $Revision: #7 $
 * $Date: 2014/08/25 $
 * $Author: heyi.wang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_COMMON_H_FAC_SHELL_
#define _ACFG_CUST_COMMON_H_FAC_SHELL_

#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
//#include "acfg_cust_plf_opt.h"
#include "res/app_util/config/acfg_cust_video.h"

#include "a_gluelayer_comm.h"
#include "a_gluelayer.h"

//ACFG_UPDATE_REASON_T  e_reason_xxx;
/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern APP_CFG_CUSTOM_PQ_TBL_T at_pq_def_tbl [][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM];
extern APP_CFG_CUSTOM_PQ_TBL_T at_pro_pq_def_tbl[][ACFG_CUST_VIDEO_PRO_PQ_DFT_TBL_MAX_NUM];
extern APP_CFG_CUSTOM_PQ_TBL_T at_pq_hdr_hlg_def_tbl [][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM];
extern APP_CFG_CUSTOM_PQ_TBL_T at_pq_dobly_version_def_tbl [][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM];
extern APP_CFG_CUSTOM_PQ_TBL_T at_pq_hlg_def_tbl [][ACFG_CUST_VIDEO_PQ_DFT_TBL_MAX_NUM];


extern INT32 (*a_cfg_custom_set_light_sensor_GAMMA_index_fac)( INT16 i2_value);
extern INT32 (*a_cfg_custom_check_xvYCC_fac)(VOID);
extern INT32 (*a_cfg_reset_clr_tmp_default_fac)(UINT8   ui1_mask);

extern INT32 (*acfg_cust_odm_video_update_fac)( UINT16  ui2_id);
extern INT32 (*acfg_cust_odm_audio_update_fac)( UINT16  ui2_id);
extern INT32 (*acfg_cust_odm_vga_update_fac)( UINT16  ui2_id);
extern VOID  (*acfg_cust_odm_overwrite_3d_pq_default_fac)(VOID);
extern VOID  (*acfg_cust_odm_overwrite_pq_default_fac)(VOID);
extern BOOL  (*a_cfg_custom_odm_is_emanual_support_fac)(VOID);
extern INT32 (*acfg_custom_odm_update_smart_dimming_fac)(UINT16 ui2_idx);
extern BOOL  (*a_cfg_custom_odm_is_lightsensor_support_fac)(VOID);
extern BOOL  (*a_cfg_custom_odm_is_dcr_support_fac)(VOID);
extern INT32 (*a_cfg_custom_set_aud_srs_bypass_fac)(BOOL b_is_on);
extern BOOL  (*a_cfg_custom_get_aud_srs_bypass_fac)(VOID);
extern INT32 (*a_cfg_custom_copy2all_usr_clr_temp_fac)(VOID);//okis@20130130
extern INT32 (*a_cfg_custom_backup_usr_clr_temp_fac)(VOID);//okis@20130130
extern INT32 (*a_cfg_custom_recall_usr_clr_temp_fac)(VOID);//okis@20130130

extern INT32 (*a_cfg_custom_get_srcid_com_or_av_fac)(UINT8* pSrcId);

extern BOOL (*a_cfg_custom_get_spdif_support_fac)(VOID);
extern BOOL (*a_cfg_custom_get_wifi_remote_support_fac)(VOID);
extern BOOL (*a_cfg_custom_get_wfd_support_fac)(VOID);
extern INT32 (*a_cfg_custom_get_rgb_on_off_fac)( UINT8* pu1ROnOff,UINT8* pu1GOnOff,UINT8* pu1BOnOff);
extern INT32 (*a_cfg_custom_set_rgb_on_off_fac)( UINT8 u1ROnOff,UINT8 u1GOnOff, UINT8 u1BOnOff);
extern INT32 (*a_cfg_custom_set_pq_exp_color_fac)(UINT8 ui1_color, UINT8 ui1_module, UINT8 ui1_value, UINT8 ui1_offset);
extern INT32 (*a_cfg_custom_get_pq_exp_color_fac)(UINT8* pui1_color,UINT8* pui1_module,UINT8* pui1_value,UINT8* pui1_offset);
extern VOID (*acfg_cust_odm_overwrite_aq_default_fac)(VOID);
extern BOOL (*a_cfg_custom_get_OPTICAL_support_fac)(VOID);
extern BOOL (*a_cfg_custom_get_lcdim_used_fac)(VOID);
extern INT32 (*a_cfg_odm_update_reduce_blur_fac)(UINT8 ui1_value);
extern INT32 (*a_cfg_odm_set_reduce_blur_fac)(UINT8 ui1_status);
extern INT32 (*acfg_cust_odm_clear_fac_setting_fac)(VOID);
//extern INT32 (*acfg_custom_odm_update_all_fac)(ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
//extern INT32 (*acfg_custom_odm_pre_update_all_fac)( ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
extern INT32  (*acfg_cust_odm_current_default_hdr_panel_nits_fac)(UINT16 *pui2_val);


//////////////////////////////////////
extern INT32 a_cfg_custom_set_light_sensor_GAMMA_index( INT16 i2_value);
extern INT32 a_cfg_custom_check_xvYCC(VOID);
extern INT32 a_cfg_reset_clr_tmp_default(UINT8   ui1_mask);

extern INT32 acfg_cust_odm_video_update( UINT16  ui2_id);
extern INT32 acfg_cust_odm_audio_update( UINT16  ui2_id);
extern INT32 acfg_cust_odm_vga_update( UINT16  ui2_id);
extern VOID  acfg_cust_odm_overwrite_3d_pq_default(VOID);
extern VOID  acfg_cust_odm_overwrite_pq_default(VOID);
extern BOOL  a_cfg_custom_odm_is_emanual_support(VOID);
extern INT32 acfg_custom_odm_update_smart_dimming(UINT16 ui2_idx);
extern BOOL  a_cfg_custom_odm_is_lightsensor_support(VOID);
extern BOOL  a_cfg_custom_odm_is_dcr_support(VOID);
extern INT32 a_cfg_custom_set_aud_srs_bypass(BOOL b_is_on);
extern BOOL  a_cfg_custom_get_aud_srs_bypass(VOID);
extern INT32 a_cfg_custom_copy2all_usr_clr_temp(VOID);//okis@20130130
extern INT32 a_cfg_custom_backup_usr_clr_temp(VOID);//okis@20130130
extern INT32 a_cfg_custom_recall_usr_clr_temp(VOID);//okis@20130130
extern INT32 a_cfg_custom_get_srcid_com_or_av(UINT8* pSrcId);
extern BOOL  a_cfg_custom_get_spdif_support(VOID);
extern BOOL  a_cfg_custom_get_wifi_remote_support(VOID);
extern BOOL  a_cfg_custom_get_wfd_support(VOID);
extern INT32 a_cfg_custom_get_rgb_on_off( UINT8* pu1ROnOff,UINT8* pu1GOnOff,UINT8* pu1BOnOff);
extern INT32 a_cfg_custom_set_rgb_on_off( UINT8 u1ROnOff,UINT8 u1GOnOff, UINT8 u1BOnOff);
extern INT32 a_cfg_custom_set_pq_exp_color(UINT8 ui1_color, UINT8 ui1_module, UINT8 ui1_value, UINT8 ui1_offset);
extern INT32 a_cfg_custom_get_pq_exp_color(UINT8* pui1_color,UINT8* pui1_module,UINT8* pui1_value,UINT8* pui1_offset);
extern VOID  acfg_cust_odm_overwrite_aq_default(VOID);
extern BOOL  a_cfg_custom_get_OPTICAL_support(VOID);
extern BOOL  a_cfg_custom_get_lcdim_used(VOID);
extern INT32 a_cfg_odm_update_reduce_blur(UINT8 ui1_value);
extern INT32 a_cfg_odm_set_reduce_blur(UINT8 ui1_status);

extern INT32 acfg_cust_odm_clear_fac_setting(VOID);
//extern INT32 acfg_custom_odm_update_all(ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
//extern INT32 acfg_custom_odm_pre_update_all( ACFG_UPDATE_REASON_T e_update_reason, VOID* pv_data);
extern INT32   acfg_cust_odm_current_default_hdr_panel_nits(UINT16 *pui2_val);

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_COMMON_H_FAC_SHELL_ */
