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
#include "app_util/config/_acfg.h"

#include "Foxconn_factory/Foxconn_d_factory.h"
#include "Foxconn_factory/Foxconn_fac_parser/Cus_Fac_foxconn.h";

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdlib.h>
#include <stdio.h>
#endif


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
UINT8 ui1_3d_support_def = (UINT8)TRUE;
UINT8 ui1_pip_support_def = (UINT8)FALSE;
UINT8 ui1_bt_support_def = (UINT8)FALSE;
UINT8 ui1_custom_plf_opt_def = 0;
/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: acfg_cust_plf_opt_pre_init
 *
 * Description:
 *      Pre initialiation. You can do following thing here:
 *  1. Override the default value
 *  2. Put some config in EEPROM
 *  3. Remove some configs by setting them as b_enable=FALSE
 *  4. Change the value in at_acfg_descr
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_plf_opt_pre_init(VOID)
{
    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_3D_SUPPORT, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_3D_SUPPORT,
                  CFG_8BIT_T,       1,     &ui1_3d_support_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_PIP_SUPPORT, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_PIP_SUPPORT,
                  CFG_8BIT_T,       1,     &ui1_pip_support_def, 1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);
    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_BT_SUPPORT, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_BT_SUPPORT,
                  CFG_8BIT_T,       1,     &ui1_bt_support_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);
    
    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_04, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_04,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_05, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_05,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_06, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_06,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_07, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_07,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_08, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_08,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_09, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_09,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_10, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_10,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_11, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_11,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_PLF_OPT_12, APP_CFG_GRPID_CUSTOM_PLF_OPT_BASE, APP_CFG_RECID_CUSTOM_PLF_OPT_12,
                  CFG_8BIT_T,       1,     &ui1_custom_plf_opt_def,  1,
                  NULL,             NULL,  ACFG_ACCESS_PUBLIC);
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_plf_opt_post_init
 *
 * Description:
 *      Post initialiation. You can do following thing here:
 *  1. Update the middleware component in accordance with config value.
 *  2. Always set a config to a specific value.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_plf_opt_post_init(VOID)
{
    return APP_CFGR_OK;
}

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/
INT32 a_cfg_custom_plf_opt_set_3d_support (BOOL b_support)
{
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_plf_opt_get_3d_support (BOOL* pb_support)
{
    if (!pb_support)
    {
        return APP_CFGR_INV_ARG;
    }

    *pb_support = FALSE;
    
    return APP_CFGR_OK;
}

INT32 a_cfg_custom_plf_opt_set_pip_support (BOOL b_support)
{
    INT16 i2_val = (INT16) b_support;
    return acfg_set(IDX_CUSTOM_PLF_OPT_PIP_SUPPORT, &i2_val, 1);
}
INT32 a_cfg_custom_plf_opt_get_pip_support (BOOL* pb_support)
{
    SIZE_T          z_size;
    INT32 i4_ret;
    INT64 i8_val = 0;

    if (!pb_support)
    {
        return APP_CFGR_INV_ARG;
    }
    i4_ret = acfg_get (IDX_CUSTOM_PLF_OPT_PIP_SUPPORT, &i8_val , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pb_support = (BOOL) i8_val;
    
    return APP_CFGR_OK;
}
INT32 a_cfg_custom_plf_opt_set_bt_support (BOOL b_support)
{
    INT16 i2_val = (INT16) b_support;
    return acfg_set(IDX_CUSTOM_PLF_OPT_BT_SUPPORT, &i2_val, 1);
}
INT32 a_cfg_custom_plf_opt_get_bt_support (BOOL* pb_support)
{
    SIZE_T          z_size;
    INT32 i4_ret;
    INT64 i8_val = 0;

    if (!pb_support)
    {
        return APP_CFGR_INV_ARG;
    }
    i4_ret = acfg_get (IDX_CUSTOM_PLF_OPT_BT_SUPPORT, &i8_val , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pb_support = (BOOL) i8_val;
    
    return APP_CFGR_OK;
}
INT32 a_cfg_custom_plf_opt_get_model_name (CHAR* s_str, UINT8 ui1_len)
{
    CHAR s_model_name[16] = {0};
    INT32 i4_ret = 0;
    
    if (!s_str || ui1_len < PLF_OPT_MODEL_NAME_LEN)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = a_cfg_custom_get_cur_model_name(s_model_name);
    Foxconn_LOG_ON_FAIL(i4_ret);

    c_strncpy(s_str, s_model_name, PLF_OPT_MODEL_NAME_LEN);

    return APP_CFGR_OK;
}

#ifdef APP_MJC_SUPPORT
INT32 a_cfg_custom_plf_opt_get_model_memc_flag(UINT32 *pui4_memc_flag)
{
    INT32   i4_ret = APP_CFGR_OK;

    //i4_ret = API_DRV_CUST_GET_COMP((DRV_CUSTOM_CUST_SPEC_TYPE_T)(DRV_CUSTOM_CUST_SPEC_TYPE_MODEL_INDEX_MEMC_FLAG), pui4_memc_flag, sizeof(UINT32));
    
    return i4_ret;
}
#endif

INT32 a_cfg_custom_get_is_support_local_dimming(BOOL *pb_support)
{
	if (!pb_support)
    {
        return APP_CFGR_INV_ARG;
    }
    
	*pb_support = FALSE;

	return APP_CFGR_OK;
}

BOOL a_cfg_custom_plf_opt_is_analog_aud_out_support(UINT8 *pui1_audio_output_type)
{
    *pui1_audio_output_type = AUDIO_OUTPUT_TYPE_LINE_OUT;
    return TRUE;
}

BOOL a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(UINT32 *ui4_dynamic_address)//FXN_PQ_180730
{
#if 1    //#ifdef EEP_COLOR_TUNER_VALUE_BEGIN
    *ui4_dynamic_address = EEP_COLOR_TUNER_VALUE_BEGIN;
#else
    *ui4_dynamic_address = 0;
#endif
    return TRUE;
}


UINT8 a_cfg_custom_plf_opt_get_usb_num(VOID)
{
    UINT8 ui1_usb_num = 4;
	
    return ui1_usb_num;
}

UINT8 C_Get_YPbPr_flag(void)
{
    return (UINT8)FALSE;
}

INT32 a_cfg_custom_plf_opt_set_cc_onoff(UINT32 ui4_onoff)
{    
    return 0;
}

INT32 a_cfg_custom_plf_opt_get_device_class (CHAR* ps_str)
{    
    return APP_CFGR_OK;    
}

INT32 a_cfg_custom_EEPROM_get_datelen (UINT8 * ui_value);

UINT8 ar_init[32]=                  /* EEPROM default value,perform special_init if the value is 0xFF ,that  */
{      0,                           /* EEP_FACTORY_DATA_CHKSUM */
       FOX_EEPROM_FAC_MAX ,         /* EEP_FACTORY_AVAIABLE_DATA_LEN */
       0,                           /* EEP_FACTORY_GAMMA_SWITCH */   
       0xFF,                        /* FOX_EEPROM_FAC_VCOM_VALUE */   

       0xFE,                        /* EEP_FACTORY_END */
};

INT32 a_cfg_custom_VCOM_check (VOID)
{
	UINT8	ui_eep_buf, ui_real_buf;
	UINT8	ui_vcom_max, ui_vcom_min;
    UINT32	ui4_written = 0;
	INT32	i4_ret = 0;
#ifdef MT5691_MODEL		//Tommy 20210723
	UINT32	ui4_model_index = 0;  //Tommy 20210505

	a_cfg_custom_get_model_index(&ui4_model_index);
	Printf("Model Index = %d \n", ui4_model_index);
	if (
		((ui4_model_index >= 24) && (ui4_model_index <= 25)) || //V705	20210528
		((ui4_model_index >= 40) && (ui4_model_index <= 41)) || //V705x
		((ui4_model_index >= 30) && (ui4_model_index <= 33)) || //V756
		((ui4_model_index >= 34) && (ui4_model_index <= 37)) || //M75Q7
		((ui4_model_index >= 42) && (ui4_model_index <= 45)) || //V756x
		((ui4_model_index >= 50) && (ui4_model_index <= 53))) 	//M75Q6
	{
		Printf("Don't need check Vcom Value \n");
		return APP_CFGR_OK;
	}
#else	//MT5695_MODEL
		Printf("Not MG304, Don't need check Vcom Value \n");
		return APP_CFGR_OK;
#endif
	DBG_LOG_PRINT(("Tommy ---a_cfg_custom_plf_opt_special_init Vcom eep init---\n"));
	i4_ret = a_cfg_custom_EEPROM_get(FOX_EEPROM_FAC_VCOM_VALUE, &ui_eep_buf);
	if(i4_ret!=APP_CFGR_OK) 
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom eep read fail---\n"));
	}
	DBG_LOG_PRINT(("ui_eep_buf = 0x%X \n", ui_eep_buf));

	i4_ret = a_cfg_fac_sif_x_read(1, 0xC8, 0xE8, 1, 1, &ui_real_buf, 1);
	if(i4_ret!=APP_CFGR_OK) 
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom chip read fail---\n"));
	}
	DBG_LOG_PRINT(("ui_real_buf = 0x%X \n", ui_real_buf));

#if 1
	ui_vcom_max = VCOM_MAX_1;
	ui_vcom_min = VCOM_MIN_1;
#else
	i4_ret = a_cfg_fac_sif_x_read(1, 0xC8, 0xE8, 1, 3, &ui_vcom_max, 1);
	if(i4_ret!=APP_CFGR_OK) 
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom get MAX fail---\n"));
	}
	else
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom get MAX =0x%X \n", ui_vcom_max));
	}

	i4_ret = a_cfg_fac_sif_x_read(1, 0xC8, 0xE8, 1, 4, &ui_vcom_min, 1);
	if(i4_ret!=APP_CFGR_OK) 
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom get MIN fail---\n"));
	}
	else
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom get MIN =0x%X \n", ui_vcom_min));
	}
#endif
	if ((ui_eep_buf == ui_real_buf) && ((ui_eep_buf >= ui_vcom_min) && (ui_eep_buf <= ui_vcom_max)))
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom eep same with VCOM chip ---\n"));
		return APP_CFGR_OK;
	}
		
	if ((ui_eep_buf >= ui_vcom_min) && (ui_eep_buf <= ui_vcom_max))
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom use eep data ---\n"));
		i4_ret = a_cfg_fac_sif_x_write(1, 0xC8, 0xE8, 1, 1, &ui_eep_buf, 1);
		ui_real_buf = 0x0A;
		i4_ret = a_cfg_fac_sif_x_write(1, 0xC8, 0xE8, 1, 0, &ui_real_buf, 1);
		if(i4_ret!=APP_CFGR_OK) 
			DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom chip read fail---\n"));
	}
	else if ((ui_real_buf >= ui_vcom_min) && (ui_real_buf <= ui_vcom_max))
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom use chip data ---\n"));
		i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_DATA_EEPROM_BEGIN + FOX_EEPROM_FAC_VCOM_VALUE, &ui_real_buf, 1, &ui4_written);
		if(i4_ret!=APP_CFGR_OK) 
			DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom eep Write fail---\n"));
	}
	else
	{
		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom use (ui_vcom_max - ui_vcom_min)/2 + ui_vcom_min ---\n"));
		ui_eep_buf = (ui_vcom_max - ui_vcom_min)/2 + ui_vcom_min;
		i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_DATA_EEPROM_BEGIN + FOX_EEPROM_FAC_VCOM_VALUE, &ui_eep_buf, 1, &ui4_written);
		if(i4_ret!=APP_CFGR_OK) 
			DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom eep Write fail---\n"));
		
		i4_ret = a_cfg_fac_sif_x_write(1, 0xC8, 0xE8, 1, 1, &ui_eep_buf, 1);
		ui_real_buf = 0x0A;
		i4_ret = a_cfg_fac_sif_x_write(1, 0xC8, 0xE8, 1, 0, &ui_real_buf, 1);
		if(i4_ret!=APP_CFGR_OK) 
			DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init Vcom chip read fail---\n"));
	}

    return i4_ret;
}


INT32 a_cfg_custom_EEPROM_reset (VOID)
{
    INT32 i4_ret = 0;

    //DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_reset---\n"));
    
    i4_ret= a_cfg_custom_plf_opt_fac_init();
    return i4_ret;
}

INT32 a_cfg_custom_EEPROM_load (UINT8 * ui_value,UINT8 * ui_datalen)
{
	UINT8	ui_load,ui_max;
	UINT32	ui4_written = 0;     
	INT32	i4_ret = 0;

	DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_load ---\n"));

	if(a_cfg_custom_EEPROM_cmp_chksum()==FALSE)
		a_cfg_custom_plf_opt_fac_init();
	else if (a_cfg_custom_VCOM_check() == APP_CFGR_OK)	//20200204 Tommy Check VCOM value
		i4_ret = a_cfg_custom_EEPROM_update_chksum();

	i4_ret=a_cfg_custom_EEPROM_get_datelen(&ui_max);
	if(i4_ret!=APP_CFGR_OK) 
	{
		DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_load get_datelen fail---\n"));
		return i4_ret;
	}

	
	for(ui_load=0;ui_load<ui_max;ui_load++)
	{
		i4_ret = a_cfg_eep_raw_read(EEP_FACTORY_DATA_EEPROM_BEGIN+ui_load, ui_value+ui_load, 1, &ui4_written);

		if(i4_ret!=APP_CFGR_OK) 
		{
			DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_load read fail---\n"));
			return i4_ret;
		}
       DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_load [%d]=%x---\n",ui_load,*(ui_value+ui_load)));
    }

    *ui_datalen=ui_max;
    //DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_load len=%d---\n",*ui_datalen));
    return i4_ret;
}

INT32 a_cfg_custom_EEPROM_set (UINT8 ui_index,UINT8 ui_len,UINT8  *ui_value)
{
    UINT32 ui4_written = 0;     
    INT32 i4_ret = 0;
    UINT8 ui_max,ui_count;

	DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_set = %d ,%d---\n",ui_index,ui_len));

    i4_ret=a_cfg_custom_EEPROM_get_datelen(&ui_max);
    if(i4_ret!=APP_CFGR_OK) 
    {
    	DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_load get_datelen fail---\n"));
    	return i4_ret;
    }
    
    if((ui_index<=FOX_EEPROM_FAC_AVAIABLE_DATA_LEN)||((ui_index+ui_len)>ui_max))
    {
        DBG_LOG_PRINT(("--- EEPROM_set can not set checksum or avaiable data len ---\n"));
        return -1;
    }

    if(a_cfg_custom_EEPROM_cmp_chksum()==FALSE)
        a_cfg_custom_plf_opt_fac_init();

    for(ui_count=0;ui_count<ui_len;ui_count++)
    {
        i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_DATA_EEPROM_BEGIN+ui_index+ui_count, ui_value+ui_count, 1, &ui4_written);
           
        if(i4_ret!=APP_CFGR_OK) 
        {
       		DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_load read fail---\n"));
       		return i4_ret;
        }
   		//DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_set data[%d]=%x---\n",ui_count,*(ui_value+ui_count)));        
    }

    i4_ret = a_cfg_custom_EEPROM_update_chksum();
    if(i4_ret!=APP_CFGR_OK) 
    {
   		DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_update_chksum  fail---\n"));
   		return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_custom_EEPROM_get (UINT8 ui_index,UINT8  *ui_value)
{
	UINT32	ui4_written = 0;     
	INT32	i4_ret = 0;

	i4_ret = a_cfg_eep_raw_read(EEP_FACTORY_DATA_EEPROM_BEGIN+ui_index, ui_value, 1, &ui4_written);

	if(i4_ret!=APP_CFGR_OK) 
	{
		DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_get read fail---\n"));
		return i4_ret;
	}


    return i4_ret;
}

INT32 a_cfg_custom_EEPROM_cal_checksum(UINT8 * ui_value) //colby@191220
{
	UINT32 ui4_checksum=0;
    UINT32 ui4_written = 0;    
    INT32 i4_ret = 0;
	UINT16 loop;
    UINT8 ar_buf[FOX_EEPROM_FAC_MAX]={0};
    UINT8 ui_avaiable_len=0;

    i4_ret = a_cfg_custom_EEPROM_get_datelen(&ui_avaiable_len);
    if(i4_ret!=APP_CFGR_OK) 
    {
        DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_cal_checksum get_datelen fail---\n"));
        return i4_ret;
    }

    for(loop = 0;loop < (ui_avaiable_len-1);loop++)
	{
       i4_ret = a_cfg_eep_raw_read(EEP_FACTORY_AVAIABLE_DATA_LEN+loop, &ar_buf[loop], 1, &ui4_written);
       
       if(i4_ret!=APP_CFGR_OK) 
       {
    		DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_checksum read fail---\n"));
    		return i4_ret;
       }

       if(ar_buf[loop]==0xFE) /* 0xFE skip flag */
            break; 
    
	   ui4_checksum += ar_buf[loop];
	}
    
	ui4_checksum = (0xff-(UINT8)ui4_checksum);

	//DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_cal_checksum=%d---\n",ui4_checksum));  

    *ui_value=ui4_checksum;

	return i4_ret;
}

INT32 a_cfg_custom_EEPROM_set_chksum (UINT8 * ui_value)
{
    UINT32 ui4_written = 0;    
    INT32 i4_ret = 0;

    i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_DATA_CHKSUM, ui_value, 1, &ui4_written);

	//DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_set_chksum=%d , i4_ret=%d---\n",*ui_value,i4_ret));    
    return i4_ret;
}

INT32 a_cfg_custom_EEPROM_get_chksum (UINT8 * ui_value)
{
    UINT32 ui4_written = 0;    
    INT32 i4_ret = 0;

    i4_ret = a_cfg_eep_raw_read(EEP_FACTORY_DATA_CHKSUM, ui_value, 1, &ui4_written);

	//DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_get_chksum=%d , i4_ret=%d---\n",*ui_value,i4_ret));    
    return i4_ret;
}
INT32 a_cfg_custom_EEPROM_get_datelen (UINT8 * ui_value)
{
    UINT32 ui4_written = 0;    
    INT32 i4_ret = 0;

    i4_ret = a_cfg_eep_raw_read(EEP_FACTORY_AVAIABLE_DATA_LEN, ui_value, 1, &ui4_written);
    if(i4_ret!=APP_CFGR_OK) 
    {
    	DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_get_datelen fail---\n"));
    	return i4_ret;
    }

    //DBG_LOG_PRINT(("---FOX_EEPROM_FAC_AVAIABLE_DATA_LEN=%d---\n",*ui_value));
    return i4_ret;
}

INT32 a_cfg_custom_EEPROM_set_datelen (VOID)
{
    UINT32 ui4_written = 0;    
    INT32 i4_ret = 0;
    UINT8 ui_value=FOX_EEPROM_FAC_MAX;

    //DBG_LOG_PRINT(("---FOX_EEPROM_FAC_MAX=%d---\n",ui_value));

    i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_AVAIABLE_DATA_LEN, &ui_value, 1, &ui4_written);
    if(i4_ret!=APP_CFGR_OK) 
    {
    	DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_set_datelen fail---\n"));
    	return i4_ret;
    }

    return i4_ret;
}

INT32 a_cfg_custom_EEPROM_datelen_update(UINT8 ui_value)
{
    UINT8 ui_count;
    UINT32 ui4_written = 0;    
    INT32 i4_ret = 0;

   	//DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_datelen_update---\n"));    
    
    for(ui_count=ui_value;ui_count<FOX_EEPROM_FAC_MAX;ui_count++)
    {
		if(ar_init[ui_count]==0xFF)	//Tommy 20200204
		{
			i4_ret = a_cfg_custom_plf_opt_special_init(ui_count);
			if(i4_ret!=APP_CFGR_OK) 
			{
				DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init fail---\n"));
				return i4_ret;
			}           
		}
		else
		{        
			i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_DATA_EEPROM_BEGIN+ui_count, &ar_init[ui_count], 1, &ui4_written);        

			if(i4_ret!=APP_CFGR_OK) 
			{
				DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_datelen_update write fail---\n"));
				return i4_ret;
			}
		}
      	DBG_LOG_PRINT(("---EEPROM_datelen_update[%d]=%x---\n",ui_count,ar_init[ui_count])); 
    }

    i4_ret = a_cfg_custom_EEPROM_set_datelen();
    if(i4_ret!=APP_CFGR_OK) 
    {
       	DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_datelen_update write fail---\n"));
       	return i4_ret;
    }
    
    return i4_ret;
}

BOOL a_cfg_custom_EEPROM_datelen_chk(VOID)
{
    UINT8 ui_value=0;

    //DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_datelen_chk---\n"));

    a_cfg_custom_EEPROM_get_datelen(&ui_value);

    if(ui_value<FOX_EEPROM_FAC_MAX) /* have new data update */
    {
       a_cfg_custom_EEPROM_datelen_update(ui_value);
       return TRUE;
    }
    return FALSE;
}

INT32 a_cfg_custom_EEPROM_update_chksum (VOID)
{
    INT32 i4_ret = 0;
    UINT8 ui_checksum=0;

    //DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_update_chksum---\n"));

    i4_ret=a_cfg_custom_EEPROM_cal_checksum(&ui_checksum);
    if(i4_ret!=APP_CFGR_OK) 
    {
    	DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_checksum read fail---\n"));
    	return i4_ret;
    }
   
    i4_ret=a_cfg_custom_EEPROM_set_chksum(&ui_checksum);
    if(i4_ret!=APP_CFGR_OK) 
    {
    	DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_checksum read fail---\n"));
    	return i4_ret;
    }

    return i4_ret;
}

BOOL a_cfg_custom_EEPROM_cmp_chksum (VOID)
{
    INT32 i4_ret = 0;
    UINT8 ui_chksum,ui_chksum_or;

	//DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_cmp_chksum---\n"));

    i4_ret=a_cfg_custom_EEPROM_data_update(); /* check EEPROM data len update */
    if(i4_ret!=APP_CFGR_OK) 
    {
   		DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_data_update check fail---\n"));
   		return FALSE;
    }  

    i4_ret=a_cfg_custom_EEPROM_get_chksum(&ui_chksum_or);
    if(i4_ret!=APP_CFGR_OK) 
    {
   		DBG_LOG_PRINT(("---EEPROM_checksum get fail---\n"));
   		return FALSE;
    }

    i4_ret=a_cfg_custom_EEPROM_cal_checksum(&ui_chksum);
    if(i4_ret!=APP_CFGR_OK) 
    {
   		DBG_LOG_PRINT(("---EEPROM_checksum cal get fail---\n"));
   		return FALSE;
    }    

    if(ui_chksum==ui_chksum_or)
        return TRUE;
    return FALSE;
}

INT32 a_cfg_custom_EEPROM_data_update (VOID)
{
    INT32 i4_ret = 0;

    //DBG_LOG_PRINT(("---a_cfg_custom_EEPROM_data_update---\n"));

    /* check data len change */
    if(a_cfg_custom_EEPROM_datelen_chk()==TRUE)
        i4_ret=a_cfg_custom_EEPROM_update_chksum();

    return i4_ret;
}

INT32 a_cfg_custom_plf_opt_fun_recover (VOID)
{
    INT32 i4_ret = 0;

    /* EEP_FACTORY_GAMMA_SWITCH */
    i4_ret=a_cfg_gamma_enable_warm(ar_init[FOX_EEPROM_FAC_GAMMA_SWITCH]);
    if(i4_ret!=APP_CFGR_OK) 
    {
   		DBG_LOG_PRINT(("---EEPROM_checksum cal get fail---\n"));
   		return FALSE;
    } 

    return i4_ret;
}
INT32 a_cfg_custom_plf_opt_special_init (UINT8 ui_index)	/* special init check */
{
	INT32	i4_ret = 0;
	
	if (ui_index == FOX_EEPROM_FAC_VCOM_VALUE)	//Tommy 20200204
	{
		i4_ret = a_cfg_custom_VCOM_check();
	}

	return i4_ret;
}

INT32 a_cfg_custom_plf_opt_fac_init (VOID)
{    
    UINT8 ui_count,ui_eep_chksum=0;
    INT32 i4_ret = 0;
    UINT32 ui4_written = 0;

	//DBG_LOG_PRINT(("---do a_cfg_custom_plf_opt_fac_init !!!!!---\n"));
    
	for(ui_count=0;ui_count<FOX_EEPROM_FAC_MAX;ui_count++)
	{
		if(ar_init[ui_count]==0xFF)
		{
			i4_ret = a_cfg_custom_plf_opt_special_init(ui_count);
			if(i4_ret!=APP_CFGR_OK) 
			{
				DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_special_init fail---\n"));
				return i4_ret;
			}           
		}
		else
		{        
			i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_DATA_EEPROM_BEGIN+ui_count, &ar_init[ui_count], 1, &ui4_written);

			if(i4_ret!=APP_CFGR_OK) 
			{
				DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_fac_init fail---\n"));
				return i4_ret;
			}
		}   	   
		DBG_LOG_PRINT(("---EEPROM[%d]=%x---\n",ui_count,ar_init[ui_count]));
	}

    i4_ret=a_cfg_custom_EEPROM_cal_checksum(&ui_eep_chksum);
    if(i4_ret!=APP_CFGR_OK) 
    {
        DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_fac_init get chksum fail---\n"));
    	return i4_ret;
    }

    i4_ret=a_cfg_eep_raw_write(EEP_FACTORY_DATA_CHKSUM, &ui_eep_chksum, 1, &ui4_written);

    if(i4_ret!=APP_CFGR_OK) 
    {
   		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_fac_init fail---\n"));
   		return i4_ret;
    }

    i4_ret=a_cfg_custom_plf_opt_fun_recover();
    if(i4_ret!=APP_CFGR_OK) 
    {
   		DBG_LOG_PRINT(("---a_cfg_custom_plf_opt_fac_init fail---\n"));
   		return i4_ret;
    }

    return APP_CFGR_OK;    
}


