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
 * $Revision: #1 $
 * $Date: 2014/08/29 $
 * $Author: dtvbm11 $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _TPV_d_FACTORY_H_
#define _TPV_d_FACTORY_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "app_util/config/_acfg.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "app_util/a_bluetooth.h"

#include "TPV_factory/a_TPV_factory.h"

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define FAC_MENU_PANEL_TYPE_SELECT	// Ben 20160901

#define TPV_HDCP1X_SIZE 304
#define TPV_HDCP2X_SIZE 1044
#define TPV_HDCP_PATH_BACKUP "/data/hdcp"

#if 0
#define IDX_CUST_FAC                    IDX_CUSTOM_93
#define IDX_CUST_VGA_PWM_MAX            IDX_CUSTOM_94
#define IDX_CUST_VGA_PWM_MIN            IDX_CUSTOM_95
#define IDX_CUST_FAC_DEFAULT_LANG       IDX_CUSTOM_96
#define IDX_CUST_FAC_PANEL_TYPE         IDX_CUSTOM_97
#define IDX_CUST_FAC_BACKLIGHT_LIFETIME IDX_CUSTOM_98
#define IDX_CUST_HDCP_CRC               IDX_CUSTOM_99  
#endif

#if 0 //ke_vizio_20160929 unuse anymore.
#define PANEL_TPT500J1_HVN07_U    201  
#define PANEL_TPT320B5_FHBN0_K_49P2T 202    
#define PANEL_TPM236WH2_WHBN00_K 203    
#endif
/*-----------------------------------------------------------------------------
                    Custom field
-----------------------------------------------------------------------------*/ 

#if 0	//mind 20160511 move to acfg_cust_factory_vizio.h
//#ifndef APP_CFG_CUST_FAC_ON
// Flag of bits field defined
#define APP_CFG_CUST_FAC_ON                     MAKE_BIT_MASK_32 (0)
#define APP_CFG_CUST_FAC_OAD_ENABLE             MAKE_BIT_MASK_32 (1)/*0: OAD disable 1: OAD Enable*/
#define APP_CFG_CUST_FAC_AUTOCLR_RST      		MAKE_BIT_MASK_32 (2)/*0: Auto-color value didn't need initial  1: Reload Auto-Color default value */
#define APP_CFG_CUST_FAC_VGA_SWITCH             MAKE_BIT_MASK_32 (3)/*0: RX/TX  1: EDID_SDA / TX*/
#define APP_CFG_CUST_FAC_RC_ON            		MAKE_BIT_MASK_32 (4)//jeff 20090107 add		//FACTORY_URC
#define APP_CFG_CUST_FAC_PATTEN_RED       		MAKE_BIT_MASK_32 (5)
#define APP_CFG_CUST_FAC_PATTEN_GREEN     		MAKE_BIT_MASK_32 (6)
#define APP_CFG_CUST_FAC_PATTEN_BLUE      		MAKE_BIT_MASK_32 (7)
#define APP_CFG_CUST_FAC_PATTEN_WHITE     		MAKE_BIT_MASK_32 (8)
#define APP_CFG_CUST_FAC_PATTEN_BLACK     		MAKE_BIT_MASK_32 (9)
#define APP_CFG_CUST_FAC_RC_CHECK         		MAKE_BIT_MASK_32 (10)//jeff 20090310 add for URC duable check
#define APP_CFG_CUST_FAC_DC_ON_RESET            MAKE_BIT_MASK_32 (11)//ke_vizio_20130911 add
#endif

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
#if 0
INT32 a_cfg_cust_fac_clear_ch_table(VOID);
INT32 C_GetHDMI1InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI2InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI3InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI4InternalEdidData(VOID* pv_data);
INT32 C_GetVGAEdidData(VOID* pv_data);
INT32 a_cfg_fac_reset(VOID);
INT32 a_cfg_custom_reset_factory(VOID);
INT32 a_cfg_cust_fac_get (UINT32* pui4_fac_bits);
INT32 a_cfg_cust_fac_set (UINT32 ui4_fac_bits);	
INT32 a_cfg_cust_factory_clr_temp_def_update(BOOL *b_update);	
UINT32 a_cfg_cust_fac_get_burning_mode_flag(VOID* pv_data);
INT32 a_cfg_custom_reset_all_source_pic_settings (VOID);
UINT32 a_cfg_cust_fac_get_factory_record(VOID* pv_data);
#endif
extern INT32 a_cfg_custom_get_cur_model_name(CHAR *s_model_name);
extern UINT32 a_cfg_custom_get_cur_panelID(VOID);
extern INT32 a_cfg_custom_get_cur_panel_name(CHAR * pt_name);
extern UINT32 a_cfg_custom_get_model_index(UINT32 *ui4_model_index);
extern UINT32 a_cfg_custom_set_model_index(UINT32 ui4_model_index);  //ke_vizio_20121115
extern UINT32 TPV_d_get_RJ45_addr(UINT32 *pui4_mac_addr); //ke_vizio_20160428
extern UINT32 a_cfg_custom_get_odm_index(UINT8 *pui1_odm_index);  //ke_vizio_20160908 add
extern UINT32 a_cfg_custom_set_odm_index(UINT8 ui1_odm_index);  //ke_vizio_20160908 add
extern UINT32 a_cfg_custom_get_model_group(UINT16 *pui1_model_group);  //ke_vizio_20160929 add
extern UINT32 a_cfg_custom_set_model_group(UINT16 ui1_model_group);  //ke_vizio_20160929 add
extern VOID a_cfg_custom_Set_MS12_PCMR_OnOff(BOOL bOnOff);  //Ben 20161006
extern INT32 a_cfg_cust_odm_write_HDCP_2_2(UINT8 * pui1_key);  //ke_vizio_20170922
extern INT32 a_cfg_cust_odm_write_HDCP_1_X(UINT8 * pui1_key);  //ke_vizio_20170928
extern INT32 a_cfg_cust_odm_get_HDCP_1_X_KSV(UINT8 * pui1_key);
extern INT32 a_cfg_cust_odm_get_HDCP_2_X_RECEIVE_ID(UINT8 * pui1_key);
extern UINT32 a_cfg_custom_set_HDCP_DEF(BOOL b_on);  //ke_vizio_20170927
extern VOID a_cfg_custom_reset_GAMMA_key(VOID);  //ke_vizio_20171109
extern INT32 a_cfg_custom_Set_Factory_GAMMA_OnOff(BOOL bOnOff);  //Ben 20180410
extern INT32 a_cfg_custom_Get_Factory_GAMMA_OnOff(BOOL *bOnOff);  // Ben 20180410
//extern INT32 a_cfg_custom_Set_Factory_PQbypass_OnOff(BOOL bOnOff);   // Ben 20180416
extern VOID a_cfg_custom_Set_Lcdim_Scrolling_OnOff(BOOL bOnOff);  //Ben 20180413
//extern INT32 a_cfg_custom_Set_Internal_RGB_Pattern(UINT8 * pui1_RGB_para); //Ben 20190125
extern INT32 a_cfg_custom_Set_Internal_RGB_Pattern_OnOff(BOOL bOnOff);  //Ben 20190125
extern INT32 a_cfg_custom_Set_Flat_pattern(UINT8 ui1_idx);
extern INT32 a_cfg_custom_get_RGB_output_status(UINT16 ui2_x_pos, 
                                                UINT16 ui2_y_pos, 
                                                UINT16 *pui2_RGB);   //ke_vizio_20190318
extern INT32 a_cfg_custom_get_HDMI_color_dep(UINT8* ui1_color_dep);  //ke_vizio_20190318
extern INT32 a_cfg_fac_sif_x_read(UINT8 u1CHannelID, UINT16 u2ClkDiv,
                                UINT8 u1DevAddr, INT8 u1WordAddrNum,
                                UINT32 u4WordAddr, UINT8 * pu1Buf, UINT16 u2ByteCnt);
extern INT32 a_cfg_fac_sif_x_write(UINT8 u1CHannelID, UINT16 u2ClkDiv,
                                  UINT8 u1DevAddr, INT8 u1WordAddrNum,
                                  UINT32 u4WordAddr, UINT8 * pu1Buf, UINT16 u2ByteCnt);
extern UINT32 a_cfg_custom_HDCPX_vaild(UINT8 ui1_HdcpX);


#endif /* _TPV_d_FACTORY_H_ */
