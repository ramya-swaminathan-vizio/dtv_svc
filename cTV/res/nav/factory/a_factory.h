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
 * $RCSfile: a_factory.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_FACTORY_H_
#define _A_FACTORY_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "amb/a_amb.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#ifdef DBG_INFO
#undef DBG_INFO
#define DBG_INFO(x) DBG_LOG_PRINT(x)
#endif

#define FACTORY_NAME                                      "factory"

/* Frankie add */
#define CMD_LEN_Maximum            270//135


typedef enum
{
    FACTORY_CMD_SET_MODEL_INDEX,
    FACTORY_CMD_GET_MODEL_INDEX,
    FACTORY_CMD_SET_MODEL_NAME,
    FACTORY_CMD_GET_MODEL_NAME,
    FACTORY_CMD_SET_SERIAL_NUMBER,
    FACTORY_CMD_GET_SERIAL_NUMBER,
    FACTORY_CMD_GET_KEY_HASH,
    FACTORY_CMD_SET_MAC_ADDRESS,
    FACTORY_CMD_GET_MAC_ADDRESS,
    FACTORY_CMD_SET_IP_ADDRESS,
    FACTORY_CMD_GET_IP_ADDRESS,
    FACTORY_CMD_GET_VERSION,
    FACTORY_CMD_SET_POWER_STATUS,
    FACTORY_CMD_GET_POWER_STATUS,
    FACTORY_CMD_SET_STANDBY_DISABLE,
    FACTORY_CMD_GET_STANDBY_DISABLE,
    FACTORY_CMD_SET_BURNING_MODE,
    FACTORY_CMD_GET_BURNING_MODE,
    FACTORY_CMD_SET_TIMER_STATUS,
    FACTORY_CMD_GET_TIMER_STATUS,
    FACTORY_CMD_SET_TIMER_VALUE,
    FACTORY_CMD_GET_TIMER_VALUE,
    FACTORY_CMD_SET_INPUT_SOURCE,
    FACTORY_CMD_GET_INPUT_SOURCE,
    FACTORY_CMD_DO_CHANNEL_PRESET,
    FACTORY_CMD_GET_CHANNEL_FREQ,
    FACTORY_CMD_SET_CHANNEL,
    FACTORY_CMD_GET_CHANNEL,
    FACTORY_CMD_DO_CHANNEL_CLEAN,
    FACTORY_CMD_GET_ADC_CALIBRATION_FLAG,
    FACTORY_CMD_DO_ADC_CALIBRATION,
    FACTORY_CMD_CLEAR_ADC_RESULT,
    FACTORY_CMD_SET_ADC_DATA,
    FACTORY_CMD_GET_ADC_DATA,
    FACTORY_CMD_SET_ADC_DATA_BUNDLE,
    FACTORY_CMD_GET_ADC_DATA_BUNDLE,
    FACTORY_CMD_SET_AUDIO_OUT,
    FACTORY_CMD_GET_AUDIO_OUT,
    FACTORY_CMD_SET_SOUND_MODE,
    FACTORY_CMD_GET_SOUND_MODE,
    FACTORY_CMD_SET_VOLUME,
    FACTORY_CMD_GET_VOLUME,
    FACTORY_CMD_SET_PICTURE_MODE,
    FACTORY_CMD_GET_PICTURE_MODE,
    FACTORY_CMD_SET_PICTURE_PROPERTY,
    FACTORY_CMD_GET_PICTURE_PROPERTY,
    FACTORY_CMD_SET_LOCAL_DIMMING,
    FACTORY_CMD_GET_LOCAL_DIMMING,
    FACTORY_CMD_SET_CLEAR_ACTION,
    FACTORY_CMD_GET_CLEAR_ACTION,
    FACTORY_CMD_SET_CT_MODE,
    FACTORY_CMD_GET_CT_MODE,
    FACTORY_CMD_SET_CT_VALUE,
    FACTORY_CMD_GET_CT_VALUE,
    FACTORY_CMD_SET_CT_VALUE_BUNDLE,
    FACTORY_CMD_GET_CT_VALUE_BUNDLE,
    FACTORY_CMD_SET_TEST_PATTERN,
    FACTORY_CMD_GET_TEST_PATTERN,
    FACTORY_CMD_DO_SETTING_RESET,
    FACTORY_CMD_GET_POWERON_TIME,
    FACTORY_CMD_DO_REBOOT,
    FACTORY_CMD_GET_EDID,
    FACTORY_CMD_DO_SKIP_OOBE,    
    FACTORY_CMD_SET_IR_KEYPAD_BLOCK,
    FACTORY_CMD_GET_IR_KEYPAD_BLOCK,
    FACTORY_CMD_INJECT_KEY_EVENT,
    FACTORY_CMD_CAPTURE_KEY_EVENT,
    FACTORY_CMD_SET_SOUND_BALANCE,
    FACTORY_CMD_GET_SOUND_BALANCE,
    FACTORY_CMD_DO_SOUND_TONE_TEST,
    FACTORY_CMD_SET_FACTORY_RECORD,
    FACTORY_CMD_GET_FACTORY_RECORD,
    FACTORY_CMD_SET_LED_ONOFF,
    FACTORY_CMD_GET_LED_ONOFF,
    FACTORY_CMD_SET_FACTORY_CONTINUE,
    FACTORY_CMD_GET_FACTORY_CONTINUE,   
    FACTORY_CMD_DO_BT_PAIR,
    FACTORY_CMD_GET_BT_RSSI,
	FACTORY_CMD_DO_WIFI_CONNECT,
    FACTORY_CMD_DO_WIFI_TEST,
    FACTORY_CMD_GET_WIFI_RSSI,
    FACTORY_CMD_DO_ETH_TEST,
    FACTORY_CMD_WRITE_I2C,
    FACTORY_CMD_READ_I2C,
    FACTORY_CMD_GET_LIGHTSENSOR_VALUE,
    FACTORY_CMD_SET_IPERF_ACTIVE,   
    FACTORY_CMD_GET_IPERF_ACTIVE,  
    FACTORY_CMD_DO_USB_TEST,
    FACTORY_CMD_SET_11POINT_GAMMA,    
    FACTORY_CMD_GET_11POINT_GAMMA,
    FACTORY_CMD_SET_CEC,
    FACTORY_CMD_GET_CEC,
    FACTORY_CMD_SET_SOUND_AQBYPASS,
    FACTORY_CMD_GET_SOUND_AQBYPASS,
    FACTORY_CMD_SET_SOUND_PQBYPASS,
    FACTORY_CMD_GET_SOUND_PQBYPASS,
    FACTORY_CMD_PROGRAM_KEY_DATA_NETWORK,
    FACTORY_CMD_PROGRAM_KEY_DATA_USB,
	FACTORY_SET_CMD_CONTEXT_SWITCH,
	FACTORY_CMD_INVALID,

} FACTORY_SET_CMD_TYPE_T;

typedef enum
{
    FACTORY_GET_CMD_SET_ADAPTIVE_LUMA,              /* Output: INT16 */
} FACTORY_GET_CMD_TYPE_T;

typedef enum
{
    FACTORY_COND_OK,
    FACTORY_COND_INV_CMD,
    FACTORY_COND_INV_ARG,
    FACTORY_COND_NOT_INIT,
    FACTORY_COND_FAIL,
} FACTORY_COND_TYPE_T;


typedef enum
{
    FACTORY_VIZIO_CMD_SUCCESS = 0x00,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_01 = 0x01,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_02 = 0x02,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_03 = 0x03,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_04 = 0x04,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_05 = 0x05,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_06 = 0x06,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_07 = 0x07,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_08 = 0x08,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_09 = 0x09,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0A = 0x0A,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0B = 0x0B,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0C = 0x0C,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0D = 0x0D,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0E = 0x0E,  
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_0F = 0x0F,
    FACTORY_VIZIO_CMD_INTERNAL_ERROR_20 = 0x20,
    FACTORY_VIZIO_CMD_INCORRECT_CHECKSUM = 0x81,
    FACTORY_VIZIO_CMD_INVALID_MSG_TYPE = 0x82,
    FACTORY_VIZIO_CMD_INCORRECT_DATASIZE = 0x83, 
    FACTORY_VIZIO_CMD_INVALID_COMMAND_TYPE = 0x84, 
    FACTORY_VIZIO_CMD_INVALID_COMMAND_CODE = 0x85,  
    FACTORY_VIZIO_CMD_INVALID_PARAMETER = 0x86,
    FACTORY_VIZIO_CMD_MAX  
} FACTORY_VIZIO_GET_CMD_TYPE_T;


/* return values */
#define FACTORYR_OK                 ((INT32)    0)
#define FACTORYR_NOT_INIT           ((INT32)  - 1)
#define FACTORYR_OUT_OF_MEMORY      ((INT32)  - 2)
#define FACTORYR_FAIL               ((INT32)  - 3)

typedef VOID (*factory_custom_init_fct) (VOID);

typedef VOID (*factory_set_cmd_nfy_fct) (
                VOID*                           pv_tag,
                VOID*                           pv_val
                );

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern VOID a_factory_set_registration(
                AMB_REGISTER_INFO_T*            pt_reg,
                factory_custom_init_fct         pf_init_fct
                );

extern INT32 a_factory_set_cmd(
                FACTORY_SET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_cmd_val,
                factory_set_cmd_nfy_fct         pf_nfy_fct,
                VOID*                           pv_nfy_tag
                );

extern FACTORY_COND_TYPE_T a_factory_get_cmd(
                FACTORY_GET_CMD_TYPE_T          t_cmd_type,
                VOID*                           pv_buf,
                SIZE_T                          z_buflen
                );
extern VOID a_fact_parser_init(VOID);

VOID fact_vizio_ret_uart_ack(UINT8 error_code, BOOL b_clear_cmd_buf);

VOID fact_vizio_ret_uart_ack_data(UINT8 * pui1_val, UINT8 error_code ,UINT8 ui1_ack_len, BOOL b_clear_cmd_buf);
#endif /* _A_FACTORY_H_ */
