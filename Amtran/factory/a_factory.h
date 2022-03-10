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
 * $Date: 2013/06/21 $
 * $Author: sin_heyiwang $
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
#define FACTORY_NAME                                      "factory"

typedef enum
{
    FACTORY_SET_CMD_SELECT_INPUT_SOURCE_TV,
    FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMP_VIDEO,
    FACTORY_SET_CMD_SELECT_INPUT_SOURCE_S_VIDEO,
    FACTORY_SET_CMD_SELECT_INPUT_SOURCE_Y_PB_PR,
    FACTORY_SET_CMD_SELECT_INPUT_SOURCE_VGA,
    FACTORY_SET_CMD_SELECT_INPUT_SOURCE_HDMI,
    FACTORY_SET_CMD_SELECT_INPUT_SOURCE_DVI,
    FACTORY_SET_CMD_SELECT_INPUT_SOURCE_COMBI,
    FACTORY_SET_CMD_SELECT_COLOR_TEMP,
    FACTORY_SET_CMD_SELECT_PIC_MODE,
    FACTORY_SET_CMD_SET_BACK_LIGHT,
    FACTORY_SET_CMD_SET_BRIGHTNESS,
    FACTORY_SET_CMD_SET_CONTRAST,
    FACTORY_SET_CMD_SET_COLOR_GAIN_RED,
    FACTORY_SET_CMD_SET_COLOR_GAIN_GREEN,
    FACTORY_SET_CMD_SET_COLOR_GAIN_BLUE,
    FACTORY_SET_CMD_SET_COLOR_OFFSET_RED,
    FACTORY_SET_CMD_SET_COLOR_OFFSET_GREEN,
    FACTORY_SET_CMD_SET_COLOR_OFFSET_BLUE,
    FACTORY_SET_CMD_SET_VOLUME,
    FACTORY_SET_CMD_SET_TREBLE,
    FACTORY_SET_CMD_SET_BASS,
    FACTORY_SET_CMD_SET_MTS,
    FACTORY_SET_CMD_PRESS_MTS_BUTTON,
    FACTORY_SET_CMD_SET_AUTO_CLK_PHS_POS,
    FACTORY_SET_CMD_SET_AUTO_COLOR,
    FACTORY_SET_CMD_SET_ADAPTIVE_LUMA,
    FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_TRSTRL,
    FACTORY_SET_CMD_SINGLE_RF_SCAN_DIG_CABLE,
    FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_TRSTRL,
    FACTORY_SET_CMD_SINGLE_RF_SCAN_ANA_CABLE,
    FACTORY_SET_CMD_SET_SKIP_RF_CHANNEL_TRSTRL,
    FACTORY_SET_CMD_SET_SKIP_RF_CHANNEL_CABLE,
    FACTORY_SET_CMD_CLEAR_SKIP_CHANNELS,
    FACTORY_SET_CMD_SAVE_TO_NVRAM,
    FACTORY_SET_CMD_RESET_NVRAM_PUBLIC_DEFAULT,
    FACTORY_SET_CMD_RESET_NVRAM_PRIVATE_DEFAULT,
    FACTORY_SET_CMD_RESET_NVRAM_FACTORY_DEFAULT,
    FACTORY_SET_CMD_RESET_NVRAM_All_SETTING,
    FACTORY_SET_CMD_PRESS_RCU_BUTTON,
    FACTORY_SET_CMD_CONTEXT_SWITCH,
    FACTORY_GET_MB_DTV_VERSION,
    FACTORY_GET_ADC_VALUE,   //gary adc   
    FACTORY_SET_CMD_SET_SURROUND,       //080523,Add factory command about surround on/off
    FACTORY_SET_CMD_SET_DCR,
    FACTORY_SET_CMD_SET_LIGHTSENSOR,
    FACTORY_SET_CMD_SET_AUD_MODE,
    FACTORY_SET_CMD_SET_SPDIF_MODE,
    FACTORY_SET_CMD_UART_REMOTE_KEYCODE,
    FACTORY_SET_CMD_UART_REMOTE_STATUS,
    FACTORY_CTX_SWITCH,     /**< Context switch to factory AP's thread context. */
    FACTORY_SET_CMD_BACKUP_GAIN_OFFSET,
    FACTORY_SET_CMD_SET_FLESH_TONE,
    FACTORY_SET_CMD_SET_EDID_COMMAND,
    FACTORY_SET_CMD_SET_VGA_DEFAULT_EDID,
    FACTORY_SET_CMD_SET_HDMI_DEFAULT_EDID,
    FACTORY_SET_CMD_SET_SURROUND_AGCVIQ,    
    FACTORY_SET_CMD_SET_END
} FACTORY_SET_CMD_TYPE_T;

typedef enum
{
    FACTORY_GET_CMD_SET_ADAPTIVE_LUMA,              /* Output: INT16 */
    FACTORY_GET_CMD_SET_FLESH_TONE,

    FACTORY_GET_CMD_SET_END
} FACTORY_GET_CMD_TYPE_T;

typedef enum
{
    FACTORY_COND_OK,
    FACTORY_COND_INV_CMD,
    FACTORY_COND_INV_ARG,
    FACTORY_COND_NOT_INIT,
    FACTORY_COND_FAIL,
} FACTORY_COND_TYPE_T;

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
extern VOID a_AMT_fact_parser_init(VOID);
extern VOID a_AMT_factory_set_registration(
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

extern CHAR* a_factory_get_fac_cmd_revision(VOID);
#endif /* _A_FACTORY_H_ */
