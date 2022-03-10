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
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *      This file is the internal header file for APP CFG
 *---------------------------------------------------------------------------*/
#ifndef _ACFG_CUST_PLF_OPT_H_
#define _ACFG_CUST_PLF_OPT_H_

#include "Foxconn_factory/a_Foxconn_factory.h"

#define AUDIO_OUTPUT_TYPE_LINE_OUT      (UINT8)0
#define AUDIO_OUTPUT_TYPE_HEADPHONE     (UINT8)1
#define AUDIO_OUTPUT_TYPE_BOTH          (UINT8)2
#define AUDIO_OUTPUT_TYPE_END           (UINT8)3
/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/ 
#define PLF_OPT_MODEL_NAME_LEN (16 + 1) /**< plus 1 '\0' */


#define     EEP_OFFSET_FAC_FFA					(EEP_OFFSET_END + 5)					//(0x1A001 + 4) 	   
#define     EEP_OFFSET_FAC_FFA_END				(EEP_OFFSET_FAC_FFA+0x10 - 1)			 //(16byte)	
#define     EEP_OFFSET_FAC_PR_SAMPLE_KEY		(EEP_OFFSET_FAC_FFA_END + 1)			//(0x1A001 + 20) 	    //(2byte)
#define     EEP_OFFSET_FAC_PR_SAMPLE_KEY_END	(EEP_OFFSET_FAC_PR_SAMPLE_KEY + 1)	    //(2byte)

#define    EEP_MODEL_NAME						(EEP_OFFSET_FAC_PR_SAMPLE_KEY_END + 1)   //0x1A001,    /* 16 bytes */
#define    EEP_MODEL_NAME_END					(EEP_MODEL_NAME+0x10-1)  //0x1A010,

    /* Serial Number */
#define		EEP_SERIAL_NUMBER					(EEP_MODEL_NAME_END + 1) //0x1A011,      /* 16 bytes */    // Denny 2009/11/02 //0x7D0  //Emerson 2009-01-13 : store 16 bytes serial number in EEPROM
#define		EEP_SERIAL_NUMBER_END				(EEP_SERIAL_NUMBER+0x10-1) //0x1A020,  //Emerson 2009-01-13 : store 16 bytes serial number in EEPROM

#define		EEP_EEPROM_VER_MAIN					(EEP_SERIAL_NUMBER_END + 1)  //0x1A021,       /* 1 byte */
#define		EEP_EEPROM_VER_SUB					(EEP_EEPROM_VER_MAIN + 1) //0x1A022,         /* 1 byte */


#ifdef APP_Foxconn_DFT_WIFI_AUTO_DETECTION 
#define		EEP_WIFI_SSID_ON					(EEP_EEPROM_VER_SUB + 1) //0x1A023  /* 1 byte */ //ke_vizio_20170523

#ifdef Foxconn_2K19_DFM // Ben 20181227
#define		EEP_FACTORY_CHECK_FLAG				(EEP_WIFI_SSID_ON + 1)  //0x1A004  /* 7 byte */  
#define		EEP_FACTORY_CHECK_FLAG_END			(EEP_FACTORY_CHECK_FLAG + 6) //0x1A00A

#define		EEP_COLOR_TUNER_VALUE_BEGIN			(EEP_FACTORY_CHECK_FLAG_END + 1) //0x1A00B    /* 514 byte */  
#define		EEP_COLOR_TUNER_VALUE_END			(EEP_COLOR_TUNER_VALUE_BEGIN + 1008) // 0x1A20C    /* 8* 57 + 46 + 11=513 bytes*/
#else
#define		EEP_COLOR_TUNER_VALUE_BEGIN			(EEP_WIFI_SSID_ON + 1) //0x1A024 
#define		EEP_COLOR_TUNER_VALUE_END			(EEP_COLOR_TUNER_VALUE_BEGIN + 1008) // 0x1A225    /* 8* 57 + 46 + 11=513 bytes*/
#endif
#else

#ifdef Foxconn_2K19_DFM // Ben 20181227
#define		EEP_FACTORY_CHECK_FLAG				(EEP_EEPROM_VER_SUB + 1)  //0x1A004  /* 7 byte */  
#define		EEP_FACTORY_CHECK_FLAG_END			(EEP_FACTORY_CHECK_FLAG + 6) //0x1A00A

#define		EEP_COLOR_TUNER_VALUE_BEGIN			(EEP_FACTORY_CHECK_FLAG_END + 1) //0x1A00B    /* 514 byte */  
#define		EEP_COLOR_TUNER_VALUE_END			(EEP_COLOR_TUNER_VALUE_BEGIN + 1008) // 0x1A20C    /* 8* 57 + 46 + 11=513 bytes*/
#else
#define		EEP_COLOR_TUNER_VALUE_BEGIN			(EEP_EEPROM_VER_SUB + 1) //0x1A024 
#define		EEP_COLOR_TUNER_VALUE_END			(EEP_COLOR_TUNER_VALUE_BEGIN + 1008) // 0x1A225    /* 8* 57 + 46 + 11=513 bytes*/
#endif
#endif

//---------- FOX factory EEPROM ---------------------------------------------------------------------------------------
#define     EEP_FACTORY_DATA_MAX                32

#define		EEP_FACTORY_DATA_EEPROM_BEGIN		(EEP_COLOR_TUNER_VALUE_END + 1)  
#define		EEP_FACTORY_DATA_EEPROM_END			(EEP_FACTORY_DATA_EEPROM_BEGIN + EEP_FACTORY_DATA_MAX -1)                /* total 32 bytes*/

typedef enum /* EEPROM index */
{
    FOX_EEPROM_FAC_DATA_CHKSUM = 0,
    FOX_EEPROM_FAC_AVAIABLE_DATA_LEN,    
    FOX_EEPROM_FAC_GAMMA_SWITCH,
    FOX_EEPROM_FAC_VCOM_VALUE,

    /* Don't remove this */
    FOX_EEPROM_FAC_MAX
} FOX_EEPROM_FAC_ITEM_T;

/* ------------------------- FACTORY EEPROM DATA -------------------------  */
#define         EEP_FACTORY_DATA_CHKSUM		(EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_DATA_CHKSUM)
#define     EEP_FACTORY_AVAIABLE_DATA_LEN        (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_AVAIABLE_DATA_LEN)     
#define         EEP_FACTORY_GAMMA_SWITCH	(EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_GAMMA_SWITCH)       /* 0:panel.ini , 1:eeprom */
#define         EEP_FACTORY_VCOM_VALUE		(EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_VCOM_VALUE)       
#define     EEP_FACTORY_RESERVE_1                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_1) 
#define     EEP_FACTORY_RESERVE_2                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_2) 
#define     EEP_FACTORY_RESERVE_3                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_3) 
#define     EEP_FACTORY_RESERVE_4                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_4) 
#define     EEP_FACTORY_RESERVE_5                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_5) 
#define     EEP_FACTORY_RESERVE_6                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_6) 
#define     EEP_FACTORY_RESERVE_7                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_7) 
#define     EEP_FACTORY_RESERVE_8                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_8) 
#define     EEP_FACTORY_RESERVE_9                (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_9) 
#define     EEP_FACTORY_RESERVE_10               (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_10) 
#define     EEP_FACTORY_RESERVE_11               (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_11) 
#define     EEP_FACTORY_RESERVE_12               (EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_RESERVE_12) 
#define         EEP_FACTORY_END				(EEP_FACTORY_DATA_EEPROM_BEGIN+FOX_EEPROM_FAC_MAX)  

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_plf_opt_pre_init (VOID);
extern INT32 acfg_cust_plf_opt_post_init (VOID);
extern INT32 a_cfg_custom_plf_opt_get_3d_support (BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_get_pip_support (BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_get_bt_support (BOOL* pb_support);
extern INT32 a_cfg_custom_plf_opt_set_3d_support (BOOL b_support);
extern INT32 a_cfg_custom_plf_opt_set_pip_support (BOOL b_support);
extern INT32 a_cfg_custom_plf_opt_set_bt_support (BOOL b_support);
extern INT32 a_cfg_custom_plf_opt_get_model_name (CHAR* s_str, UINT8 ui1_len);
extern INT32 a_cfg_custom_plf_opt_get_model_memc_flag(UINT32 *pui4_memc_flag);
extern INT32 a_cfg_custom_get_is_support_local_dimming(BOOL *pb_support);
extern BOOL  a_cfg_custom_plf_opt_is_analog_aud_out_support(UINT8 *pui1_audio_output_type);
extern BOOL  a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(UINT32 *ui4_dynamic_address); //FXN_PQ_180724
extern UINT8 a_cfg_custom_plf_opt_get_usb_num(VOID);
extern UINT8 C_Get_YPbPr_flag( void);
extern INT32 a_cfg_custom_plf_opt_set_cc_onoff(UINT32 ui4_onoff);
extern INT32 a_cfg_custom_plf_opt_get_device_class (CHAR* ps_str);

extern INT32 a_cfg_custom_EEPROM_reset (VOID);
extern INT32 a_cfg_custom_EEPROM_load (UINT8 * ui_value,UINT8 * ui_datalen);
extern INT32 a_cfg_custom_EEPROM_set (UINT8 ui_index,UINT8 ui_len,UINT8  *ui_value);
extern INT32 a_cfg_custom_EEPROM_get (UINT8 ui_index,UINT8  *ui_value);

extern INT32 a_cfg_custom_EEPROM_update_chksum (VOID);
extern BOOL a_cfg_custom_EEPROM_cmp_chksum (VOID);
extern INT32 a_cfg_custom_plf_opt_special_init (UINT8 ui_index);	/* special init check */
extern INT32 a_cfg_custom_plf_opt_fac_init (VOID);

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_PLF_OPT_H_ */
