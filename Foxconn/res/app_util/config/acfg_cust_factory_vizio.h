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
#ifndef _ACFG_Foxconn_FAC_CUSTOM_H_
#define _ACFG_Foxconn_FAC_CUSTOM_H_
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "app_util/config/_acfg.h"
#include "res/app_util/config/a_cfg_custom.h"

/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/ 
/* Group Custom */
//#define APP_CFG_GRPID_CUSTOM_BASE           ((UINT16)128)
/* define Factory start from 100  */
#define APP_CFG_RECID_CUST_BASE_FAC                      ((UINT16)    100)
#define APP_CFG_RECID_CUST_BASE_DEFAULT_LANG           ((UINT16)  101)
#define APP_CFG_RECID_CUST_BASE_PANEL_TYPE              ((UINT16)   102)
#define APP_CFG_RECID_CUST_BASE_VGA_PWM_MAX            ((UINT8)   103)
#define APP_CFG_RECID_CUST_BASE_VGA_PWM_MIN            ((UINT8)    104)
#define APP_CFG_RECID_CUST_BASE_BLT_LT                    ((UINT16)    105)
#define APP_CFG_RECID_CUST_BASE_HDCP_CRC                 ((UINT16)    106)

/* FAC*/
#define APP_CFG_CUST_FAC_DEF                     ( APP_CFG_CUST_FAC_ON |  \
                                                   APP_CFG_CUST_FAC_OAD_ENABLE | \
                                                   APP_CFG_CUST_FAC_RC_ON )   

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
#define APP_CFG_CUST_FAC_DC_ON_RESET            MAKE_BIT_MASK_32 (11)  //ke_vizio_20130911 add

#define IDX_CUST_FAC                    IDX_CUSTOM_93
#define IDX_CUST_VGA_PWM_MAX            IDX_CUSTOM_94
#define IDX_CUST_VGA_PWM_MIN            IDX_CUSTOM_95
#define IDX_CUST_FAC_DEFAULT_LANG       IDX_CUSTOM_96
#define IDX_CUST_FAC_PANEL_TYPE         IDX_CUSTOM_97
#define IDX_CUST_FAC_BACKLIGHT_LIFETIME IDX_CUSTOM_98
#define IDX_CUST_HDCP_CRC               IDX_CUSTOM_99  
/*-----------------------------------------------------------------------------
                    Custom field
-----------------------------------------------------------------------------*/ 
#define HDMI_KSV_DATA 10
#define MODEL_NAME_LENGTH                   (16)

typedef enum //Denny 2014/02/17 add
{
    ACFG_FAC_KEYPAD_NONE = 0,
    ACFG_FAC_KEYPAD_VOL_INC,
    ACFG_FAC_KEYPAD_VOL_DEC,
    ACFG_FAC_KEYPAD_CH_INC,
    ACFG_FAC_KEYPAD_CH_DEC,
    ACFG_FAC_KEYPAD_INPUT,
    ACFG_FAC_KEYPAD_MENU,
    ACFG_FAC_KEYPAD_POWER,
    ACFG_FAC_KEYPAD_EXIT,
} ACFG_FAC_KEYPAD_T;
/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
INT32 a_cfg_cust_fac_clear_ch_table(VOID);
extern INT32 acfg_custom_Foxconn_fac_pre_init(VOID);
extern INT32 acfg_custom_Foxconn_fac_post_init(VOID);
INT32 C_GetHDMI1InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI2InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI3InternalEdidData(VOID* pv_data);
INT32 C_GetHDMI4InternalEdidData(VOID* pv_data);
INT32 C_GetVGAEdidData(VOID* pv_data);
INT32 a_cfg_ping_ip_v4(CHAR* ps_ip, INT16 i2_wait_time, VOID (*notify_fn)(INT16 i2_rsp_time));
INT32 a_cfg_fac_reset(VOID);
INT32 a_cfg_custom_reset_factory(VOID);
INT32 a_cfg_cust_fac_get (UINT32* pui4_fac_bits);
INT32 a_cfg_cust_fac_set (UINT32 ui4_fac_bits);	
INT32 a_cfg_cust_factory_clr_temp_def_update(BOOL *b_update);	
extern INT32 a_cfg_cust_fac_psm_set(
         UINT8   ui1_input,
         UINT16  ui2_id,
         INT16   i2_val);	
extern INT32 C_GetHDMIKSV(VOID* pv_data);  
extern INT32 C_GetHDMIReceiverID(VOID* pv_data);    // Ben 20171027
extern UINT8 a_cfg_cust_fac_reg_get_usb_vbus_status (VOID);
extern VOID  a_cfg_cust_fac_reg_usb_vbus_oc_nfy (VOID);
#if 0 //Ben 20190904 //TPV disable
extern INT16 a_cfg_cust_fac_get_panel_type(
        INT16*                 pui2_fac_panel_type
        );
extern INT16 a_cfg_cust_fac_set_panel_type (
        UINT16                  pui2_fac_panel_type
        );
#endif
extern INT32 a_cfg_cust_fac_get_backlight_lifetime(
        INT32*                 pi4_fac_backlight_lifetime
        );
extern UINT32 a_cfg_cust_fac_set_backlight_lifetime (
        UINT32                  pui4_fac_backlight_lifetime
        );
//ke_vizio_20130520 add
extern INT32 a_cfg_cust_get_image_bank_bit(UINT8 * ui1_image_bank_bit);
extern INT32 a_cfg_cust_set_image_bank_bit(UINT8 ui1_image_bank_bit);
extern UINT32 a_cfg_cust_fac_get_keypad_status_read(VOID); //Denny 2014/02/17 add
extern VOID a_cfg_cust_fac_set_keypad_status_read(UINT32 ui4_val); //Denny 2014/02/17 add
extern VOID a_cfg_cust_fac_set_urc_flag(UINT32 u4Val); //Denny 2015/09/15 add for URC flag
extern UINT32 a_cfg_cust_fac_get_urc_flag(VOID); //Denny 2015/09/15 add for URC flag
extern INT16 acfg_custom_clr_temp_delta(
                                        UINT16  ui2_id,
                                        UINT8   ui1_input_grp,
                                        INT16   i2_clr_temp,
                                        INT16   i2_val);
extern INT32 a_cfg_fac_eep_init(VOID);  //ke_vizio_20160908 add

extern void a_cfg_fac_set_burning_mode(BOOL bOnOff); // Ben 20190222 //From TPV
#endif /* _ACFG_Foxconn_FAC_CUSTOM_H_ */
