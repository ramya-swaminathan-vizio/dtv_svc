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
 * $RCSfile: acfg_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *      This file implements the APP CFG APIs. APP CFG is a utility library which
 * encapsulates the definition of config database and builds a facade for the
 * application developer.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_common.h"
#include "c_svctx.h"

#include "app_util/a_cfg.h"
#include "a_gluelayer.h"
#include "app_util/config/_acfg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/

static INT32 _acfg_cust_fac_eep_field_assign(VOID)
{
    /* Explicit offset settings  */
    typedef struct _IDX_OFF_MAP_ENTRY_T
    {
        UINT16  ui2_idx;
        UINT32  ui4_offset;
    }   IDX_OFF_MAP_ENTRY_T;

    INT32 *ap_ui4_idx[] =
    {
        &IDX_FAC_CUST_RESERV_0 ,
        &IDX_FAC_CUST_RESERV_1 ,
        &IDX_FAC_CUST_RESERV_2 ,
        &IDX_FAC_CUST_RESERV_3 ,
        &IDX_FAC_CUST_RESERV_4 ,
        &IDX_FAC_CUST_RESERV_5 ,
        &IDX_FAC_CUST_RESERV_6 ,
        &IDX_FAC_CUST_RESERV_7 ,
        &IDX_FAC_CUST_RESERV_8 ,
        &IDX_FAC_CUST_RESERV_9 ,
        &IDX_FAC_CUST_RESERV_10,
        &IDX_FAC_CUST_RESERV_11,
        &IDX_FAC_CUST_RESERV_12,
        &IDX_FAC_CUST_RESERV_13,
        &IDX_FAC_CUST_RESERV_14,
        &IDX_FAC_CUST_RESERV_15,
        &IDX_FAC_CUST_RESERV_16,
        &IDX_FAC_CUST_RESERV_17,
        &IDX_FAC_CUST_RESERV_18,
        &IDX_FAC_CUST_RESERV_19,
        &IDX_FAC_CUST_RESERV_20,
        &IDX_FAC_CUST_RESERV_21,

        &IDX_FAC_CUST_RESERV_2_0,
        &IDX_FAC_CUST_RESERV_2_1,
        &IDX_FAC_CUST_RESERV_2_2,
        &IDX_FAC_CUST_RESERV_2_3,
        &IDX_FAC_CUST_RESERV_4_0,
        &IDX_FAC_CUST_RESERV_4_1,

#if defined(APP_ODM_ONE_IMG_SUPPORT) || defined(APP_CFG_FAC_CLR_TEMP)
        &IDX_CLR_FAC_GAIN_R  ,
        &IDX_CLR_FAC_GAIN_G  ,
        &IDX_CLR_FAC_GAIN_B  ,
        &IDX_CLR_FAC_OFFSET_R,
        &IDX_CLR_FAC_OFFSET_G,
        &IDX_CLR_FAC_OFFSET_B,
#endif
    } ;

    IDX_OFF_MAP_ENTRY_T  at_eep_off_map_fac[] =
    {
        {IDX_FAC_CUST_RESERV_0          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_0)},
        {IDX_FAC_CUST_RESERV_1          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_1)},
        {IDX_FAC_CUST_RESERV_2          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2)},
        {IDX_FAC_CUST_RESERV_3          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_3)},
        {IDX_FAC_CUST_RESERV_4          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_4)},
        {IDX_FAC_CUST_RESERV_5          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_5)},
        {IDX_FAC_CUST_RESERV_6          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_6)},
        {IDX_FAC_CUST_RESERV_7          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_7)},
        {IDX_FAC_CUST_RESERV_8          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_8)},
        {IDX_FAC_CUST_RESERV_9          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_9)},
        {IDX_FAC_CUST_RESERV_10         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_10)},
        {IDX_FAC_CUST_RESERV_11         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_11)},
        {IDX_FAC_CUST_RESERV_12         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_12)},
        {IDX_FAC_CUST_RESERV_13         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_13)},
        {IDX_FAC_CUST_RESERV_14         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_14)},
        {IDX_FAC_CUST_RESERV_15         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_15)},
        {IDX_FAC_CUST_RESERV_16         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_16)},
        {IDX_FAC_CUST_RESERV_17         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_17)},
        {IDX_FAC_CUST_RESERV_18         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_18)},
        {IDX_FAC_CUST_RESERV_19         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_19)},
        {IDX_FAC_CUST_RESERV_20         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_20)},
        {IDX_FAC_CUST_RESERV_21         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_21)},

        {IDX_FAC_CUST_RESERV_2_0        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2_0)},
        {IDX_FAC_CUST_RESERV_2_1        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2_1)},
        {IDX_FAC_CUST_RESERV_2_2        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2_2)},
        {IDX_FAC_CUST_RESERV_2_3        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2_3)},
        {IDX_FAC_CUST_RESERV_4_0        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_4_0)},
        {IDX_FAC_CUST_RESERV_4_1        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_4_1)},

#if defined(APP_ODM_ONE_IMG_SUPPORT) || defined(APP_CFG_FAC_CLR_TEMP)
        {IDX_CLR_FAC_GAIN_R             ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_GAIN_R)},
        {IDX_CLR_FAC_GAIN_G             ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_GAIN_G)},
        {IDX_CLR_FAC_GAIN_B             ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_GAIN_B)},
        {IDX_CLR_FAC_OFFSET_R           ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_OFFSET_R)},
        {IDX_CLR_FAC_OFFSET_G           ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_OFFSET_G)},
        {IDX_CLR_FAC_OFFSET_B           ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_OFFSET_B)},
#endif
    };

    UINT16  ui2_i;
    UINT16  ui2_idx;
    UINT16  ui2_num = (UINT16)(sizeof(at_eep_off_map_fac) / sizeof(at_eep_off_map_fac[0]));

    /* Setup the eeprom with explict offset */
    for( ui2_i = 0;
         ui2_i < ui2_num;
         ui2_i++)
    {
        at_eep_off_map_fac[ui2_i].ui2_idx = *(ap_ui4_idx[ui2_i]);
        ui2_idx = at_eep_off_map_fac[ui2_i].ui2_idx;

        if(ui2_idx >= IDX_MAX)
        {
            continue;
        }
        at_acfg_descr[ui2_idx].b_eep        = TRUE;
        at_acfg_descr[ui2_idx].ui4_eep_off  = at_eep_off_map_fac[ui2_i].ui4_offset;

        at_acfg_descr[ui2_idx].b_eep_fix    = TRUE;

    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: acfg_cust_eep_field_assign
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_eep_field_assign(VOID)
{
    /* Explicit offset settings  */
    typedef struct _IDX_OFF_MAP_ENTRY_T
    {
        UINT16  ui2_idx;
        UINT32  ui4_offset;
    }   IDX_OFF_MAP_ENTRY_T;

    IDX_OFF_MAP_ENTRY_T  at_eep_off_map[] =
    {
        {IDX_CLR_GAIN_R             ,EEP_OFFSET_REMAP(EEP_OFFSET_CLR_GAIN_R)},
        {IDX_CLR_GAIN_G             ,EEP_OFFSET_REMAP(EEP_OFFSET_CLR_GAIN_G)},
        {IDX_CLR_GAIN_B             ,EEP_OFFSET_REMAP(EEP_OFFSET_CLR_GAIN_B)},
        {IDX_CLR_OFFSET_R           ,EEP_OFFSET_REMAP(EEP_OFFSET_CLR_OFFSET_R)},
        {IDX_CLR_OFFSET_G           ,EEP_OFFSET_REMAP(EEP_OFFSET_CLR_OFFSET_G)},
        {IDX_CLR_OFFSET_B           ,EEP_OFFSET_REMAP(EEP_OFFSET_CLR_OFFSET_B)},
#ifdef APP_CEC_SUPPORT
        {IDX_GL                     ,EEP_OFFSET_REMAP(EEP_OFFSET_GUI_LANG)},
        {IDX_CEC_CEC_FUNC           ,EEP_OFFSET_REMAP(EEP_OFFSET_CEC_FUNC)},
        {IDX_CEC_AUTO_ON            ,EEP_OFFSET_REMAP(EEP_OFFSET_CEC_AUTO_ON)},
#endif
        {IDX_CUSTOM_PLF_OPT_3D_SUPPORT,           EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_00)},
        {IDX_CUSTOM_PLF_OPT_PIP_SUPPORT,          EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_01)},
        {IDX_CUSTOM_PLF_OPT_BT_SUPPORT,           EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_02)},
        {IDX_CUSTOM_PLF_OPT_04,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_03)},
        {IDX_CUSTOM_PLF_OPT_05,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_04)},
        {IDX_CUSTOM_PLF_OPT_06,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_05)},
        {IDX_CUSTOM_PLF_OPT_07,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_06)},
        {IDX_CUSTOM_PLF_OPT_08,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_07)},
        {IDX_CUSTOM_PLF_OPT_09,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_08)},
        {IDX_CUSTOM_PLF_OPT_10,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_09)},
        {IDX_CUSTOM_PLF_OPT_11,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_10)},
        {IDX_CUSTOM_PLF_OPT_12,                   EEP_OFFSET_REMAP(EEP_OFFSET_PLF_OPT_11)},
#ifdef APP_RETAIL_MODE_SUPPORT
		{IDX_CUSTOM_RETAIL_MODE,                  EEP_OFFSET_REMAP(EEP_OFFSET_RETAIL_MODE)},
#endif
        {IDX_CUSTOM_LED_LOGO_CTRL,                EEP_OFFSET_REMAP(EEP_OFFSET_LED_CTRL)},
        {IDX_CUSTOM_COUNTRY_CODE,                 EEP_OFFSET_REMAP(EEP_OFFSET_COUNTRY_CODE)},

        {IDX_WZD_STA,                             EEP_OFFSET_REMAP(EEP_OFFSET_WZD_STATUS)},
        {IDX_CUST_BOOTUP_ASSISTANT,               EEP_OFFSET_REMAP(EEP_OFFSET_BOOTUP_ASSISTANT_FLAG)},
        {IDX_CUSTOM_FAC_CUST_11_POINT_RED,        EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_11_POINT_RED)},
        {IDX_CUSTOM_FAC_CUST_11_POINT_GREEN,      EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_11_POINT_GREEN)},
        {IDX_CUSTOM_FAC_CUST_11_POINT_BLUE,       EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_11_POINT_BLUE)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_R,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_R)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_G,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_G)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_B,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_B)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_C,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_C)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_M,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_M)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_HUE_Y,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_HUE_Y)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_R,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_R)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_G,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_G)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_B,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_B)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_C,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_C)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_M,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_M)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_SAT_Y,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_SAT_Y)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_R,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_R)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_G,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_G)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_B,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_B)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_C,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_C)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_M,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_M)},
        {IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_Y,     EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_CLR_TUNER_BRI_Y)},

#if 0
        {IDX_FAC_CUST_RESERV_0          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_0)},
        {IDX_FAC_CUST_RESERV_1          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_1)},
        {IDX_FAC_CUST_RESERV_2          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2)},
        {IDX_FAC_CUST_RESERV_3          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_3)},
        {IDX_FAC_CUST_RESERV_4          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_4)},
        {IDX_FAC_CUST_RESERV_5          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_5)},
        {IDX_FAC_CUST_RESERV_6          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_6)},
        {IDX_FAC_CUST_RESERV_7          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_7)},
        {IDX_FAC_CUST_RESERV_8          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_8)},
        {IDX_FAC_CUST_RESERV_9          ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_9)},
        {IDX_FAC_CUST_RESERV_10         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_10)},
        {IDX_FAC_CUST_RESERV_11         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_11)},
        {IDX_FAC_CUST_RESERV_12         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_12)},
        {IDX_FAC_CUST_RESERV_13         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_13)},
        {IDX_FAC_CUST_RESERV_14         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_14)},
        {IDX_FAC_CUST_RESERV_15         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_15)},
        {IDX_FAC_CUST_RESERV_16         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_16)},
        {IDX_FAC_CUST_RESERV_17         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_17)},
        {IDX_FAC_CUST_RESERV_18         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_18)},
        {IDX_FAC_CUST_RESERV_19         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_19)},
        {IDX_FAC_CUST_RESERV_20         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_20)},
        {IDX_FAC_CUST_RESERV_21         ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_21)},

        {IDX_FAC_CUST_RESERV_2_0        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2_0)},
        {IDX_FAC_CUST_RESERV_2_1        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2_1)},
        {IDX_FAC_CUST_RESERV_2_2        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2_2)},
        {IDX_FAC_CUST_RESERV_2_3        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_2_3)},
        {IDX_FAC_CUST_RESERV_4_0        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_4_0)},
        {IDX_FAC_CUST_RESERV_4_1        ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CUST_4_1)},

#if defined(APP_ODM_ONE_IMG_SUPPORT) || defined(APP_CFG_FAC_CLR_TEMP)
        {IDX_CLR_FAC_GAIN_R             ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_GAIN_R)},
        {IDX_CLR_FAC_GAIN_G             ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_GAIN_G)},
        {IDX_CLR_FAC_GAIN_B             ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_GAIN_B)},
        {IDX_CLR_FAC_OFFSET_R           ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_OFFSET_R)},
        {IDX_CLR_FAC_OFFSET_G           ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_OFFSET_G)},
        {IDX_CLR_FAC_OFFSET_B           ,EEP_OFFSET_REMAP(EEP_OFFSET_FAC_CLR_OFFSET_B)},
#endif
#endif
    };

    UINT16  ui2_i;
    UINT16  ui2_idx;
    UINT16  ui2_num = (UINT16)(sizeof(at_eep_off_map) / sizeof(at_eep_off_map[0]));

    /* Setup the eeprom with explict offset */
    for( ui2_i = 0;
         ui2_i < ui2_num;
         ui2_i++)
    {
        ui2_idx = at_eep_off_map[ui2_i].ui2_idx;

        if(ui2_idx >= IDX_MAX)
        {
            continue;
        }
        at_acfg_descr[ui2_idx].b_eep        = TRUE;
        at_acfg_descr[ui2_idx].ui4_eep_off  = at_eep_off_map[ui2_i].ui4_offset;

        /* If the b_eep_fix is TRUE, it would not reset this settings even though
           the eeprom schema changes. It is usually used to preserve the video
           adjustment settings at prior run phase.*/
        at_acfg_descr[ui2_idx].b_eep_fix    = TRUE;

    }

    _acfg_cust_fac_eep_field_assign();

    /* Put all other settings sequentially from the offset EEP_OFFSET_ACFG_MISC. */
    acfg_eep_quick_set_offset3( EEP_OFFSET_REMAP(EEP_OFFSET_ACFG_MISC) );

    return APP_CFGR_OK;
}

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/

