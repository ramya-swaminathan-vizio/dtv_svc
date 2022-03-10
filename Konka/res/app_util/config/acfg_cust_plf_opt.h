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
#define AUDIO_OUTPUT_TYPE_LINE_OUT      (UINT8)0
#define AUDIO_OUTPUT_TYPE_HEADPHONE     (UINT8)1
#define AUDIO_OUTPUT_TYPE_BOTH          (UINT8)2
#define AUDIO_OUTPUT_TYPE_END           (UINT8)3
/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define PLF_OPT_MODEL_NAME_LEN (16 + 1) /**< plus 1 '\0' */

#ifndef APP_LARGE_EEPROM_SUPPORT
#define     EEP_MODEL_NAME              (EEP_OFFSET_PLF_OPT_11+1)   //0x59a,    /* 16 bytes */
#define     EEP_MODEL_NAME_END          (EEP_MODEL_NAME+0x10-1)  //0x5a9,
    // Top Denny 2009/01/17 modify - end

/* Serial Number */
#define     EEP_SERIAL_NUMBER           (EEP_MODEL_NAME_END + 1) //0x5aa,      /* 16 bytes */ //Emerson 2009-01-13 : store 16 bytes serial number in EEPROM
#define     EEP_SERIAL_NUMBER_END       (EEP_SERIAL_NUMBER+0x10-1) //0x5b9,  //Emerson 2009-01-13 : store 16 bytes serial number in EEPROM

#define     EEP_EEPROM_VER_MAIN         (EEP_SERIAL_NUMBER_END + 1)  //0x5ba,       /* 1 byte */
#define     EEP_EEPROM_VER_SUB          (EEP_EEPROM_VER_MAIN + 1) //0x5bb,         /* 1 byte */

#else
#define     EEP_MODEL_NAME                      (EEP_OFFSET_END + 1)                    // 0x1A001  /* 16 bytes */
#define     EEP_MODEL_NAME_END                  (EEP_MODEL_NAME + 0x10 - 1)             // 0x1A010

/* Serial Number */
#define     EEP_SERIAL_NUMBER                   (EEP_MODEL_NAME_END + 1)                // 0x1A011  /* 16 bytes */
#define     EEP_SERIAL_NUMBER_END               (EEP_SERIAL_NUMBER + 0x10 - 1)          // 0x1A020

#define     EEP_EEPROM_VER_MAIN                 (EEP_SERIAL_NUMBER_END + 1)             // 0x1A021
#define     EEP_EEPROM_VER_SUB                  (EEP_EEPROM_VER_MAIN + 1)               // 0x1A022

#define     EEP_CVTE_BURNING_MODE_FLAG          (0x1A023)                               // 0x1A023
#define     EEP_CVTE_RESET_FLAG                 (EEP_CVTE_BURNING_MODE_FLAG + 1)        // 0x1A024
#define     EEP_CVTE_BORCODE                    (EEP_CVTE_RESET_FLAG + 1)               // 0x1A025
#define     EEP_CVTE_BORCODE_END                (EEP_CVTE_BORCODE + 17)                 // 0x1A036

#define     EEP_CVTE_CUMULATIVE_USE_TIME          (0x1A037)                             // 0x1A037
#define     EEP_CVTE_CUMULATIVE_USE_TIME_END      (0x1A038)        						// 0x1A038
//0x1A039 no used
#define     EEP_CVTE_BURNING_MODE_TIME          (0x1A03A)                               // 0x1A03A
#define     EEP_CVTE_BURNING_MODE_TIME_END      (EEP_CVTE_BURNING_MODE_TIME + 4)        // 0x1A03E
#define     EEP_CUS_BORCODE                     (EEP_CVTE_BURNING_MODE_TIME_END + 1)    // 0x1A03F
#define     EEP_CUS_BORCODE_END                 (EEP_CUS_BORCODE + 20)                  // 0x1A053
#define     EEP_CVTE_HDCP_1_X_FILE_ID           (EEP_CUS_BORCODE_END + 1)               // 0x1A054
#define     EEP_CVTE_HDCP_1_X_FILE_ID_END       (EEP_CVTE_HDCP_1_X_FILE_ID + 4)         // 0x1A058
#define     EEP_CVTE_HDCP_2_2_FILE_ID           (EEP_CVTE_HDCP_1_X_FILE_ID_END + 1)     // 0x1A059
#define     EEP_CVTE_HDCP_2_2_FILE_ID_END       (EEP_CVTE_HDCP_2_2_FILE_ID + 4)         // 0x1A05D
#define     EEP_CVTE_POWER_MODE_FLAG            (EEP_CVTE_HDCP_2_2_FILE_ID_END + 1)     // 0x1A05E
#define     EEP_CVTE_CUS_AT_FLAG                (EEP_CVTE_POWER_MODE_FLAG + 1)          // 0x1A05F
#define     EEP_COLOR_TUNER_VALUE_BEGIN         (EEP_CVTE_CUS_AT_FLAG + 1)              // 0x1A060
#define     EEP_COLOR_TUNER_VALUE_END           (EEP_COLOR_TUNER_VALUE_BEGIN + 600)     // 0x1A2B8  /* 57 x 3 x 3 = 513bytes */
#define     EEP_KONKA_KEYPAD_STAT_FLAG          (EEP_COLOR_TUNER_VALUE_END + 1)            // 0x1A2BA
#define     EEP_KONKA_USB_STAT_FLAG             (EEP_KONKA_KEYPAD_STAT_FLAG + 1)        // 0x1A2BB

#define     EEP_CVTE_AC_ON_DISP_FLAG            (0xFFE0B)
#endif

#define    EEP_HDCP_ADDR                       (0x0)    /* HDCP */      /* MG132 0x000 ~ 0x13F */   /* MG128 0x1C9E ~ 0x1DDD*/
#define    EEP_BT_MAC                          (0x232)  /* BT-MAC */    /* MG132 0x232 ~ 0x237 */   /* MG128 0x1C89 ~ 0x1C8E */
#define    EEP_BT_MAC_CKSum                    (0x238)
#define    EEP_WIRED_ETHERNET_MAC_ADDR         (0x214)  /* RJ45-MAC 1st & 2nd*/ /* MG132 0x1C90 ~ 0x1C9D */ /* MG128 0x1C90 ~ 0x1C9D */
#define    EEP_WIRED_ETHERNET_MAC_ADDR_CKSum   (0x21A)

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
extern BOOL  a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(UINT32 *ui4_dynamic_address);
extern UINT8 a_cfg_custom_plf_opt_get_usb_num(VOID);
extern UINT8 C_Get_YPbPr_flag( void);
extern INT32 a_cfg_custom_plf_opt_set_cc_onoff(UINT32 ui4_onoff);
extern INT32 a_cfg_custom_plf_opt_get_device_class (CHAR* ps_str);

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

#endif /* _ACFG_CUST_PLF_OPT_H_ */
