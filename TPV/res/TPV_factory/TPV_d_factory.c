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
 * $Revision: #4 $
 * $Date: 2014/10/21 $
 * $Author: teresa.zhang $
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
#include <unistd.h>	
#include <stdlib.h>		

#include "c_pcl.h"
#include "c_rm.h"
#include "c_tsl.h"
#include "u_pcl.h"
#include "u_drv_cust.h"
#include "u_rm_dev_types.h"

#include "u_dm.h" 
#include "c_dm.h"

#include "c_net_config.h"

#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_sleep_timer.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "nav/fav_lst/a_fav_lst.h"
//#include "factory/a_factory.h"
#include "agent/a_agent.h"

#include "app_util/config/acfg_cust_factory_vizio.h"
#include "TPV_d_factory.h"

#include "intertaca_api.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "res/app_util/config/acfg_custom.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
//#define HDMI_EDID_DATA 256
//#define VGA_EDID_DATA 128
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/
//static INT32 a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_T   e_spec_type,
//                              VOID*                         pv_get_info,
//                              SIZE_T*                       pz_size);
#if 0
/*-----------------------------------------------------------------------------
 * Name: _nav_fac_handle_msg
 * Description: handle the message from navigater controller
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
INT32 a_cfg_cust_fac_clear_ch_table(VOID)
{
    INT32 i4_ret;
    
    /* clean air svl */
    if (h_g_acfg_svl_air != NULL_HANDLE)
    {
        i4_ret = c_svl_clean(h_g_acfg_svl_air);
        if (i4_ret != SBR_OK)
        {
            return SBR_NOT_INIT;
        }
    }

    /* clean cable svl */
    if (h_g_acfg_svl_cable != NULL_HANDLE)
    {
        i4_ret = c_svl_clean(h_g_acfg_svl_cable);
        if (i4_ret != SBR_OK)
        {
            return SBR_NOT_INIT;
        }
    }

    /* clean air tsl */
    if (h_g_acfg_tsl_air != NULL_HANDLE)
    {
        i4_ret = c_tsl_clean(h_g_acfg_tsl_air);
        if (i4_ret != SBR_OK)
        {
            return SBR_NOT_INIT;
        }
    }

    /* clean cable tsl */
    if (h_g_acfg_tsl_cable != NULL_HANDLE)
    {
        i4_ret = c_tsl_clean(h_g_acfg_tsl_cable);
        if (i4_ret != SBR_OK)
        {
            return SBR_NOT_INIT;
        }
    }

    a_cfg_ch_lst_store();
    
    return APP_CFGR_OK;
}



/*---------------------------------------------------------------------------
 * Name: a_cfg_fac_c_rm_get_comp_cust_spec
 *Description:  get cust setting by RM API - DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET
 *Inputs:
 *
 * Outputs:
 *
 * Returns:
*-----------------------------------------------------------------------------*/
static INT32 a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_T   e_spec_type,
                              VOID*                         pv_get_info,
                              SIZE_T*                       pz_size)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = e_spec_type;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pv_get_info;
    t_op_info.u.t_cust_spec_get_info.pz_size = pz_size;    

     /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    if(i4_ret != RMR_OK)
    {
        //Printf("!!!!%s : Get value fail\n", __func__);
        return i4_ret;
    }

    return i4_ret;
}


INT32 C_GetHDMI1InternalEdidData(VOID* pv_data)
{
    INT32 i4_ret = 0;
   	volatile UINT8 ui1_hdmi_edid_data[HDMI_EDID_DATA]={0};
	SIZE_T z_size;
	z_size= sizeof(ui1_hdmi_edid_data) / sizeof(ui1_hdmi_edid_data[0]);
	
	i4_ret = a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI1_INTERNAL_EDID, pv_data, &z_size);
	return i4_ret;
}

INT32 C_GetHDMI2InternalEdidData(VOID* pv_data)
{
    INT32 i4_ret = 0;
    volatile UINT8 ui1_hdmi_edid_data[HDMI_EDID_DATA]={0};
	SIZE_T z_size;
	z_size= sizeof(ui1_hdmi_edid_data) / sizeof(ui1_hdmi_edid_data[0]);
	
	i4_ret = a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI2_INTERNAL_EDID, pv_data, &z_size);
	return i4_ret;
}

INT32 C_GetHDMI3InternalEdidData(VOID* pv_data)
{
    INT32 i4_ret = 0;
    volatile UINT8 ui1_hdmi_edid_data[HDMI_EDID_DATA]={0};
	SIZE_T z_size;
	z_size= sizeof(ui1_hdmi_edid_data) / sizeof(ui1_hdmi_edid_data[0]);
	
	i4_ret = a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI3_INTERNAL_EDID, pv_data, &z_size);
	return i4_ret;
}

INT32 C_GetHDMI4InternalEdidData(VOID* pv_data)   //ke_vizio_20130306 add
{
    INT32 i4_ret = 0;
    volatile UINT8 ui1_hdmi_edid_data[HDMI_EDID_DATA]={0};
	SIZE_T z_size;
	z_size= sizeof(ui1_hdmi_edid_data) / sizeof(ui1_hdmi_edid_data[0]);
	
	i4_ret = a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI4_INTERNAL_EDID, pv_data, &z_size);
	return i4_ret;
}

INT32 C_GetVGAEdidData(VOID* pv_data)
{
	volatile UINT8 ui1_vga_edid_data[VGA_EDID_DATA]={0};
	SIZE_T z_size;
	z_size= sizeof(ui1_vga_edid_data); 
	
	a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_EEP_READ_VGA_EDID, pv_data, &z_size);
	return APP_CFGR_OK;
}




INT32 a_cfg_fac_reset(VOID)
{

    INT32 i4_ret;
    UINT32		ui4_fac_rc_val;

    /* To avoid the temporary state of AV in factory reset. */
    a_tv_stop_all_svc(h_g_acfg_svctx_main, h_g_acfg_svctx_sub);

    /* reset settings */
    a_tv_net_send_cmd(":dtv_app_mtk,am,:unblock_3rd\n");
    //Emerson 2008-0923 : keep ColorTemp data in the User reset if AOC factory mode enable.    
    a_cfg_custom_reset_factory();
 
    a_cfg_cust_fac_clear_ch_table();


#if 1	// Ben 20140825, clear 3rd_rw always in case that data lost by AC drop
	system("/basic/bin/mke2fs -t ext4 /dev/mmcblk0p10");
	system("mount -t ext4 /dev/mmcblk0p10 /3rd_rw");
#endif

#if 1 //Larry 2012 0412, for factory reset should remove 3rd party data.
	a_tv_net_reset_3rd_ap_data(APP_TV_NET_RESET_ITEM_ALL);
   	a_tv_custom_set_tos(FALSE);
   	a_tv_custom_set_privacy(FALSE);

#endif

#if 1 //Larry 2014 1020 for modify CEC default change to "Disable" after factory reset. issue : TF1014VIZUSMTKO1-1446
	/*CEC default setting:ARC only/sac on*/
	a_cfg_set_cec_func (APP_CFG_CEC_ARC_ONLY);
	a_cfg_set_cec_sac_func(1);
#endif

	//nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, FALSE); //willy 2012 0229 fix btn_rst  ac/on can not standby

#if 1  //ke_vizio_20130621 add : TF1014VIZUSMTKO0-42
    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
#endif
    
    a_sleep_timer_stop();
    a_cfg_set_time_zone_data(-5*3600 , FALSE);	//kyo_20111128 reset daylight saving to off
    /* turn off URC */
	i4_ret = a_cfg_cust_fac_get(&ui4_fac_rc_val);
	ACFG_LOG_ON_FAIL(i4_ret);
	
	ui4_fac_rc_val = ui4_fac_rc_val & 0x0f;
	
	i4_ret =a_cfg_cust_fac_set(ui4_fac_rc_val);
	ACFG_LOG_ON_FAIL(i4_ret);

    return APP_CFGR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_reset_factory
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
INT32  a_cfg_custom_reset_factory(VOID)
{
    UINT16 ui2_i;
   // UINT8       ui1_i;

    //ke_vizio_20131021 add
    //Before reset, reset at_acfg_descr for user's temperature.
    BOOL b_update = TRUE;
    a_cfg_cust_factory_clr_temp_def_update(&b_update);
    
    for(ui2_i=0; ui2_i<IDX_MAX; ui2_i++)
    {
        //ke_vizio_20121114 modify
        if(ui2_i == IDX_CLR_FAC_GAIN_R   ||
           ui2_i == IDX_CLR_FAC_GAIN_G   ||
           ui2_i == IDX_CLR_FAC_GAIN_B   ||
           ui2_i == IDX_CLR_FAC_OFFSET_R ||
           ui2_i == IDX_CLR_FAC_OFFSET_G ||
           ui2_i == IDX_CLR_FAC_OFFSET_B ||
           ui2_i == IDX_CUST_FAC_BACKLIGHT_LIFETIME ||
		   ui2_i == IDX_CUSTOM_ULPK_FLAG||               // willy 20110324 fix do factory 3d icon and  ulpk can change  for  xm issue MTK5395_VIZIO_CTV-8
		   #if 0    //sam 121028
		   ui2_i == IDX_CUSTOM_PLF_OPT_05|| 		/* //sam 120813 use 0x592 to record "BT remote select" */
		   #endif
		   ui2_i == IDX_CUSTOM_PLF_OPT_3D_SUPPORT||	
		   ui2_i == IDX_CUSTOM_PLF_OPT_BT_SUPPORT|| 	/*//sam 110510 fix factory reset will clear BT control byte*/
		   ui2_i == IDX_CUSTOM_PLF_OPT_PIP_SUPPORT|| 
         //TOP Denny 2009/01/17 add to prevent from reseting HDCP CRC.
           ui2_i == IDX_CUST_HDCP_CRC)
        {
            continue;
        }

        if(at_acfg_descr[ui2_i].b_enable)
        {
            acfg_set_default(ui2_i);
        }
    }

    acfg_lock();
    acfg_custom_update_all(ACFG_UPDATE_REASON_RESET, NULL);
    a_cfg_unlock();
#ifdef  APP_BLUETOOTH_SUPPORT
	//a_cfg_custom_unpair_all_bluetooth_devices(); //sam 110615 for XM issue "MTK5395_VIZIO_CTV-302"
#endif
#ifndef APP_LARGE_EEPROM_SUPPORT
	a_cfg_filesys_clear_user_data();	// Ben 20131212, clear custom data for TF1014VIZUSMTKO1-376.
#endif

    return APP_CFGR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_get
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_cust_fac_get (UINT32* pui4_fac_bits)
{
    SIZE_T  z_size;

    if (pui4_fac_bits == NULL)
    {
        return APP_CFGR_INV_ARG;
    }
    return acfg_get(IDX_CUST_FAC, pui4_fac_bits , &z_size);
}


INT32 a_cfg_cust_fac_set (
        UINT32                  ui4_fac_bits
        )
{
    return acfg_set(IDX_CUST_FAC, &ui4_fac_bits , 1);
}


/*----------------------------------------------------------------------------
 * Name
 *      a_cfg_cust_factory_clr_temp_def_update
 * Description
 *
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      None
 *----------------------------------------------------------------------------*/
INT32 a_cfg_cust_factory_clr_temp_def_update(BOOL *b_update)
{
    INT32   i4_ret;
    UINT16   ui2_i = 0, ui2_j = 0; ;   
    INT16 i2_val = 0;    

    if(*b_update == FALSE)
    {
        return APP_CFGR_NO_ACTION;
    }

    /* Overwrite the Color gain/offset by TPV default value */
    /* This has to be done after _acfg_check_color_temperture() */
    for(ui2_i = 0; ui2_i < ACFG_CLR_GAIN_ELEM_NUM; ui2_i++)  
    {       
        if(ui2_i != (ACFG_CLR_TEMP_NUM*ACFG_CUST_INPUT_GRP_VGA+ui2_j))
        {   //load YPbpr part.
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_R, ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_G, ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_G].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_B, ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_B].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_G].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_B].pt_def_value + ui2_i) = i2_val;
        }
        else
        {   //load VGA part.
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_R, ACFG_CLR_TEMP_NUM + ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_R].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_G, ACFG_CLR_TEMP_NUM + ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_G].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_GAIN_B, ACFG_CLR_TEMP_NUM + ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_GAIN_B].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_R, ACFG_CLR_TEMP_NUM + ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_R].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_G, ACFG_CLR_TEMP_NUM + ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_G].pt_def_value + ui2_i) = i2_val;
            
            i4_ret = acfg_get_int16_by_idx(IDX_CLR_FAC_OFFSET_B, ACFG_CLR_TEMP_NUM + ui2_j, &i2_val);
            ACFG_CHK_FAIL(i4_ret, i4_ret);
            *((UINT8*)at_acfg_descr[IDX_CLR_OFFSET_B].pt_def_value + ui2_i) = i2_val;
        }

        ui2_j++;
        if(ui2_j == ACFG_CLR_TEMP_NUM)
        {
            ui2_j = 0;
        }

    }

    *b_update = FALSE;
    return APP_CFGR_OK;
}



UINT32 a_cfg_cust_fac_get_burning_mode_flag(VOID* pv_data)
{

    INT32 i4_ret = 0;
	UINT8 flag = 0;
	SIZE_T z_size = sizeof(flag);

	i4_ret = a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE_FLAG, pv_data, &z_size);
	
	return i4_ret;
	
}



INT32 a_cfg_custom_reset_all_source_pic_settings (VOID)
{
	INT32   i4_ret;
	UINT8   pt_values[ACFG_MAX_REC_SIZE] = {0};
	UINT16  ui2_off = 0;
	SIZE_T  z_size = ACFG_CUST_SET_PIC_MODE_NUM;	
	
	for (int j = 0; j < ACFG_CUST_INPUT_GRP_MAX; j++)
	{
		for (int i = 0; i < ACFG_PRE_SET_PIC_MODE_NUM; i++)
		{
			acfg_get(IDX_PRE_PIC_CHG,(VOID*)pt_values,&z_size);
			ui2_off = j*ACFG_PRE_SET_PIC_MODE_NUM + i;
			pt_values[ui2_off] = 0;
    		acfg_set(IDX_PRE_PIC_CHG,(VOID*)pt_values,z_size);	
		}
	}	
	acfg_set_default(IDX_PIC_MODE);
	acfg_set_default(IDX_DISP_BACK_LIGHT);
	acfg_set_default(IDX_CUSTOM_LIGHT_SENSOR_IDX);
	acfg_set_default(IDX_VID_BRI);
	acfg_set_default(IDX_VID_CNT);
	acfg_set_default(IDX_VID_SAT);
	acfg_set_default(IDX_VID_HUE);				
	acfg_set_default(IDX_VID_SHP);
	acfg_set_default(IDX_VID_3D_NR);				
	acfg_set_default(IDX_VID_NR);
	acfg_set_default(IDX_VID_MPEG_NR);				
	acfg_set_default(IDX_VID_FT);
	acfg_set_default(IDX_VID_LUMA);
	acfg_set_default(IDX_CUSTOM_DCR_IDX);
	acfg_set_default(IDX_CUSTOM_DIMMING);
	acfg_set_default(IDX_CLR_TEMP);
	acfg_set_default(IDX_VID_DI_FILM_MODE);
	acfg_set_default(IDX_VID_POS_H);
	acfg_set_default(IDX_VID_POS_V);
	acfg_set_default(IDX_CUSTOM_H_SIZE);				
	acfg_set_default(IDX_CUSTOM_V_SIZE);				
    acfg_set_default(IDX_VID_ETI);
    acfg_set_default(IDX_VID_DEBLOCKING);	
    acfg_set_default(IDX_DISP_ADP_BACK_LIGHT);
	acfg_set_default(IDX_VID_GAME_MODE);//
	acfg_set_default(IDX_CUST_GAMMA);//

    #ifdef APP_MJC_SUPPORT
    acfg_set_default(IDX_VID_MJC_EFFECT);
    acfg_set_default(IDX_VID_MJC_MODE);
    #endif			

	acfg_set_default(IDX_CLR_HUE_R);
	acfg_set_default(IDX_CLR_HUE_G);
	acfg_set_default(IDX_CLR_HUE_B);
	acfg_set_default(IDX_CLR_HUE_C);
	acfg_set_default(IDX_CLR_HUE_M);
	acfg_set_default(IDX_CLR_HUE_Y);	
	acfg_set_default(IDX_CLR_SAT_R);
	acfg_set_default(IDX_CLR_SAT_G);
	acfg_set_default(IDX_CLR_SAT_B);
	acfg_set_default(IDX_CLR_SAT_C);
	acfg_set_default(IDX_CLR_SAT_M);
	acfg_set_default(IDX_CLR_SAT_Y);	
	acfg_set_default(IDX_CLR_BRI_R);
	acfg_set_default(IDX_CLR_BRI_G);
	acfg_set_default(IDX_CLR_BRI_B);
	acfg_set_default(IDX_CLR_BRI_C);
	acfg_set_default(IDX_CLR_BRI_M);
	acfg_set_default(IDX_CLR_BRI_Y);	
	acfg_set_default(IDX_CUST_CLR_GAIN_R);
	acfg_set_default(IDX_CUST_CLR_GAIN_G);
	acfg_set_default(IDX_CUST_CLR_GAIN_B);
	acfg_set_default(IDX_CUST_CLR_OFFSET_R);
	acfg_set_default(IDX_CUST_CLR_OFFSET_G);
	acfg_set_default(IDX_CUST_CLR_OFFSET_B);	
	
	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_BACK_LIGHT));	//Backlight		
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));	//Backlight		
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));		//Brightness
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT));		//Contrast	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT));		//Saturation	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE));		//HUE	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP));		//Sharpness	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));		//3D NR 	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));		//Noise Reduction	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR));	//MPEG Noise Reduction	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_FLESH_TONE));	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LUMA));			
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));	
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H));
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V));
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE));
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE));
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, IDX_VID_ETI));
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, IDX_VID_DEBLOCKING));
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_ADP_BACK_LIGHT));	//Backlight	
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_VID_GAME_MODE));	//Game mode		
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_VID_CUST_GAMMA));	//Gamma	
	ACFG_CHK_FAIL(i4_ret, i4_ret);		
	
    #ifdef APP_MJC_SUPPORT
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_MODE));
    #endif

    A_TV_SET_VIDEO_MUTE(VIDEO_MUTE_ID_FACTORY, h_g_acfg_svctx_main, TV_VIDEO_MUTE_MASK_RESET, FALSE);
    A_TV_SET_VIDEO_MUTE(VIDEO_MUTE_ID_FACTORY, h_g_acfg_svctx_sub, TV_VIDEO_MUTE_MASK_RESET, FALSE);

	acfg_vga_reset();
	a_cfg_vga_auto_clk_phs_pos();

	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_R)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_G)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_B)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_C)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_M)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_HUE_Y)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);		
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_R)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_G)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_B)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_C)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_M)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_SAT_Y)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);		
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_R)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_G)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_B)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_C)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_M)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);	
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CLR_BRI_Y)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);			
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_R)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);		
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_G)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);		
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_GAIN_B)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);		
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);		
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_G)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);		
	i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_CLR_OFFSET_B)); 
	ACFG_CHK_FAIL(i4_ret, i4_ret);		

	
	return APP_CFGR_OK;
}




UINT32 a_cfg_cust_fac_get_factory_record(VOID* pv_data)
{

    INT32 i4_ret = 0;
	UINT8 record[16]={0};
	SIZE_T z_size;
	z_size= sizeof(record) / sizeof(record[0]);

	i4_ret = a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_GET_FACTORY_RECORD, pv_data, &z_size);
	
	return i4_ret;
	
}
#endif
INT32 a_cfg_custom_get_cur_model_name(CHAR *s_model_name)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    CHAR s_name[16]= {0};
    SIZE_T      z_size = sizeof(s_name);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_MODEL_NAME;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)s_name;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_LOG_PRINT(("!!!!%s Get Fail i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }
    c_strncpy(s_model_name, s_name, 16);
    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name a_cfg_custom_get_cur_panelID
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *     TVR_OK 
 *---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_get_cur_panelID(VOID)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
        
    UINT32      i4_panel_id = 0;
    SIZE_T      z_size_panel = sizeof(UINT32);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_DISP_TYPE_PANEL_ID;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)(&i4_panel_id);
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size_panel;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    if(i4_ret != RMR_OK)
    {
        //return at_panel_data[0].ui2_panel_id;
        return 0;
    }
    return i4_panel_id;
}
/*-----------------------------------------------------------------------------
 * Name a_cfg_custom_get_cur_panel_name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *     TVR_OK 
 *---------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_get_cur_panel_name(CHAR* pt_name)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    CHAR s_name[35]={0};
    SIZE_T      z_size = sizeof(s_name);

    
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_DISP_TYPE_PANEL_NAME;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = s_name;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;


     /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    if(i4_ret != RMR_OK)
    {
        c_sprintf(pt_name, "Get Panel Name Fail");
        return i4_ret;
    }
    
    c_strcpy(pt_name, s_name);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
* Name a_cfg_custom_get_model_index
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_get_model_index(UINT32 *pui4_model_index)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(pui4_model_index);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_GetModelIndexID;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_model_index;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_set_model_index
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_set_model_index(UINT32 ui4_model_index)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui4_model_index);
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_MODEL_INDEX;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui4_model_index;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        z_size_drv
                        );
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name TPV_d_get_RJ45_addr
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 TPV_d_get_RJ45_addr(UINT32 *pui4_mac_addr) //ke_vizio_20160428
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(pui4_mac_addr);
    

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_RJ45_ADDR;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_mac_addr;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info,
                 &z_size_drv
                 );
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_get_odm_index
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_get_odm_index(UINT8 *pui1_odm_index)  //ke_vizio_20160908 add
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(pui1_odm_index);


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_ODM_INDEX;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_odm_index;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_set_odm_index
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_set_odm_index(UINT8 ui1_odm_index)  //ke_vizio_20160908 add
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T z_size = sizeof(ui1_odm_index);
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_ODM_INDEX;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_odm_index;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* Set from driver */
    i4_ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
    }
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_get_model_group
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_get_model_group(UINT16 *pui1_model_group)  //ke_vizio_20160929 add
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(pui1_model_group);


    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_MODEL_GROUP;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui1_model_group;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_set_odm_index
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_set_model_group(UINT16 ui1_model_group)  //ke_vizio_20160929 add
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T z_size = sizeof(ui1_model_group);
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_MODEL_GROUP;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_model_group;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* Set from driver */
    i4_ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
    }
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_Disable_MS12_PCMR
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern VOID a_cfg_custom_Set_MS12_PCMR_OnOff(BOOL bOnOff)  //Ben 20161006
{
	INT32	i4_ret;
	DRV_CUST_OPERATION_INFO_T	  t_op_info;
	SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	SIZE_T z_size = sizeof(bOnOff);
	
	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
	t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_MS12_PCMR_ONOFF;
	t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&bOnOff;
	t_op_info.u.t_cust_spec_set_info.z_size = z_size;
	t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

		 /* set to driver */
    i4_ret = c_rm_set_comp(
						 DRVT_CUST_DRV,
						 DRV_CUST_COMP_ID,
						 FALSE,
						 ANY_PORT_NUM,
						 0,
						 &t_op_info,
						 z_size_drv
						 );

    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
    }
}

/*-----------------------------------------------------------------------------
* Name a_cfg_cust_odm_write_HDCP_2_2
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_odm_write_HDCP_2_2(UINT8 * pui1_key)
{
    #if 0
    UINT8 ui1_key_buffer[880] = {0};
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32                        i4_ret = APP_CFGR_OK;  
    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);
    
    c_memcpy(ui1_key_buffer, pui1_key, z_size);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDCP_2_2;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_key_buffer;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(ui1_key_buffer);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size_drv
                            );
                                
    if (i4_ret < 0)
    {
        DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    #else
    UINT8 ui1_key_buffer[TPV_HDCP2X_SIZE] = {0};
    CHAR    s_filename_reserve[512 + 64] = {0};
    INT32   i4_ret = 0;  

    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);
    struct stat st = {0};
    FILE *pFile2;
    size_t z_size_wirte = 0;
    
    c_memcpy(ui1_key_buffer, pui1_key, z_size);

    i4_ret=TEEC_Key2TA("8", 1, (char *)ui1_key_buffer, sizeof(ui1_key_buffer));
    TPV_LOG_ON_FAIL(i4_ret);
    
    c_sprintf(s_filename_reserve, TPV_HDCP_PATH_BACKUP"%s", "/hdcp2_key.bin");
    DBG_LOG_PRINT(("HDCP 2.X reserve path : %s", s_filename_reserve));

    if (stat(TPV_HDCP_PATH_BACKUP, &st) == -1) {
        TPV_LOG_ON_FAIL(mkdir(TPV_HDCP_PATH_BACKUP, S_IRWXU));
    }

    // Key backup
    pFile2 = fopen(s_filename_reserve,"wb");
    if(pFile2 == NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename_reserve));
    }
    else
    {
        z_size_wirte = fwrite(ui1_key_buffer,1,sizeof(ui1_key_buffer),pFile2);
        DBG_LOG_PRINT(("HDCP 2.X wirte : %d\n", z_size_wirte));
        fclose(pFile2);
    }

    AP_SYSTEM_CALL("sync");

    //i4_ret=TEEC_SendData2TA("8", 1);  //HDCP 2.X
    //TPV_LOG_ON_FAIL(i4_ret);
    
    #endif
    
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name a_cfg_custom_HDCPX_vaild
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *     TVR_OK 
 *---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_HDCPX_vaild(UINT8 ui1_HdcpX)
{
    #if 0
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
        
    UINT8      ui1_HDCPX = ui1_HdcpX;
    SIZE_T      size = sizeof(ui1_HDCPX);
 
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDCPX_vaild;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)(&ui1_HDCPX);
    t_op_info.u.t_cust_spec_get_info.pz_size = &size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    if(i4_ret != RMR_OK)
    {
        DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    return ui1_HDCPX;
    #else
    INT32 i4_ret = 0; 
    if(ui1_HdcpX == 0x00){
        i4_ret = TEEC_CheckKey("21");  // HDCP 1.x : Return 0 Success, 1 Fail
        DBG_LOG_PRINT(("HDCP 1.X valid %s", (i4_ret==0?"PASS":"FAIL")));
    }
    else if(ui1_HdcpX == 0x0A )
    {
        i4_ret = TEEC_CheckKey("8");  // HDCP 2.X
        DBG_LOG_PRINT(("HDCP 2.X valid %s", (i4_ret==0?"PASS":"FAIL")));
    }
    
    return i4_ret;
    #endif
    
    
}
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_set_odm_index
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_set_HDCP_DEF(BOOL b_on)  //ke_vizio_20170927 add
{
    INT32   i4_ret = 0;
    UINT8 _au1HDCP[] = 
    {
        0xf0, 0xd4, 0xef, 0x12, 0x26, 0x00, 0xc3, 0x01, 0x38, 0x2c, 0xea, 0x53, 0x74, 0x46, 0xbd, 0x58, 
        0x63, 0x7e, 0xdb, 0x63, 0x5f, 0x0a, 0xbe, 0x08, 0x68, 0xa9, 0x74, 0x72, 0xc3, 0x53, 0x44, 0x15, 
        0x63, 0x5c, 0x8b, 0x02, 0xb0, 0xc6, 0x58, 0xbc, 0xa9, 0xd6, 0xc2, 0xc5, 0x23, 0x77, 0x17, 0x24, 
        0x64, 0xc3, 0x6d, 0x10, 0x5c, 0x41, 0xed, 0x71, 0x38, 0x43, 0x39, 0x85, 0x59, 0x26, 0x83, 0x12, 
        0x7f, 0xac, 0xdb, 0x27, 0xf8, 0x82, 0xac, 0xcc, 0xe4, 0x63, 0x2b, 0xba, 0x17, 0xde, 0x3a, 0x04, 
        0x58, 0xf5, 0xcf, 0xb2, 0x44, 0x2c, 0x0f, 0xd7, 0xb9, 0xde, 0x89, 0xc3, 0x6d, 0x18, 0x65, 0xf5, 
        0x84, 0xd3, 0x24, 0xc7, 0x72, 0xaa, 0x1e, 0xda, 0x0e, 0x9d, 0xef, 0xa5, 0xf1, 0x8b, 0xc5, 0xce, 
        0x02, 0x4e, 0x6b, 0x44, 0x3a, 0x76, 0xe5, 0x8b, 0x84, 0xd3, 0xb0, 0x76, 0x90, 0x38, 0x8a, 0xeb, 
        0x77, 0xaf, 0x26, 0x5b, 0x21, 0xcf, 0xd3, 0xd8, 0xab, 0xb4, 0x45, 0xb8, 0xcb, 0x9f, 0x8d, 0x6c, 
        0xe6, 0xdc, 0xa8, 0x00, 0x4b, 0x8f, 0x62, 0x79, 0xee, 0xf5, 0xea, 0xca, 0xd9, 0x57, 0xb8, 0x16, 
        0x20, 0x05, 0xb4, 0xb9, 0x40, 0xa9, 0x47, 0x9b, 0x27, 0x53, 0xf0, 0xd2, 0x5a, 0x92, 0x6d, 0xa2, 
        0x2e, 0x2b, 0x0b, 0xae, 0x9f, 0x96, 0x24, 0x6a, 0x23, 0xaf, 0x8e, 0xd9, 0xe9, 0x45, 0x9f, 0xc2, 
        0x32, 0xfb, 0xbd, 0x7a, 0x5c, 0x21, 0x59, 0x0c, 0x71, 0x4f, 0xce, 0x66, 0x76, 0x4f, 0x37, 0x54, 
        0xf9, 0xa1, 0xc3, 0x22, 0x36, 0x82, 0xf8, 0xb2, 0x00, 0x33, 0x14, 0xa9, 0x3f, 0x65, 0x9c, 0x28, 
        0x56, 0x40, 0xb8, 0xe7, 0x73, 0x0e, 0xb6, 0x7e, 0x94, 0x8a, 0xcb, 0x97, 0x84, 0x03, 0x62, 0x2d, 
        0xd9, 0x1d, 0xc9, 0xaf, 0x4d, 0x5f, 0x11, 0xed, 0xb3, 0x70, 0x76, 0x0c, 0x44, 0x41, 0xa5, 0x21, 
        0x5b, 0x2e, 0x36, 0xfb, 0x3e, 0xe7, 0xb0, 0x63, 0x04, 0x2e, 0x45, 0x0d, 0x37, 0x48, 0x3c, 0x0d, 
        0xe0, 0xeb, 0x9b, 0xd5, 0x88, 0x63, 0xf8, 0x1f, 0x40, 0xe5, 0x9f, 0x6c, 0x75, 0xeb, 0x4b, 0xd4, 
        0xf4, 0x00, 0x00, 0x02, 0x45, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

#ifdef  MT5691_MODEL
    UINT8 _au1HDCP_2X[] =
    {
        0x0a, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x4d, 0x53, 0x54, 0x41, 0x52, 0x5f, 0x53, 0x45, 0x43, 0x55, 0x52, 0x45, 0x5f, 0x53, 0x54, 0x4f,
        0x52, 0x45, 0x5f, 0x46, 0x49, 0x4c, 0x45, 0x5f, 0x4d, 0x41, 0x47, 0x49, 0x43, 0x5f, 0x49, 0x44,
        0x4b, 0xb5, 0x0d, 0x71, 0x84, 0xfe, 0xa8, 0xaf, 0xfd, 0x01, 0x4e, 0x5d, 0xc9, 0xf1, 0xfd, 0x67,
        0x46, 0x9c, 0xef, 0x17, 0xed, 0xef, 0x70, 0xe5, 0xa0, 0xc5, 0x6a, 0x9b, 0x08, 0x87, 0x43, 0x39,
        0x5a, 0xed, 0x84, 0x45, 0x84, 0xf9, 0xfb, 0xa8, 0x08, 0x69, 0x88, 0xa1, 0x57, 0x9e, 0x3b, 0x9a,
        0xe7, 0xf2, 0x95, 0x7c, 0xbd, 0x63, 0x97, 0xc7, 0x0c, 0x05, 0xa6, 0xd7, 0x7a, 0x17, 0xe0, 0x44,
        0xb2, 0xfb, 0x1c, 0xa0, 0x8f, 0xea, 0x77, 0x25, 0x6d, 0xbb, 0x8f, 0xee, 0x37, 0xac, 0x15, 0xcb,
        0xbd, 0xb0, 0x4c, 0xc6, 0x8e, 0x40, 0xa2, 0x4f, 0x70, 0x6c, 0xa9, 0x86, 0x3f, 0x8b, 0xab, 0xa6,
        0xaf, 0x69, 0x5c, 0x7f, 0x9b, 0x10, 0x13, 0x90, 0x31, 0x0a, 0xbb, 0x01, 0x4d, 0x55, 0x93, 0x22,
        0xbd, 0xc7, 0x0b, 0x34, 0x26, 0x72, 0xaa, 0x39, 0x6d, 0x02, 0x8e, 0x0a, 0x37, 0xa2, 0xea, 0xfe,
        0xe9, 0x70, 0x5f, 0x34, 0x8b, 0xd4, 0xfe, 0xd7, 0x2d, 0x09, 0xee, 0xe7, 0x49, 0x41, 0x05, 0xbb,
        0x5c, 0xac, 0xd2, 0xa3, 0x11, 0xa5, 0x36, 0xef, 0xa6, 0xaa, 0x01, 0x20, 0x78, 0x8f, 0x54, 0xec,
        0xf3, 0x83, 0x99, 0xb1, 0x4c, 0x03, 0x41, 0x51, 0x0e, 0x41, 0x06, 0x1c, 0xfe, 0xf1, 0x48, 0xa4,
        0x67, 0x95, 0x87, 0x7e, 0x24, 0x97, 0x05, 0xc1, 0x03, 0xf4, 0x02, 0x43, 0xa5, 0x7e, 0x05, 0xbe,
        0x3d, 0x20, 0x83, 0xce, 0x39, 0x61, 0x0c, 0x8a, 0xda, 0xbc, 0xbe, 0x9b, 0x05, 0xfc, 0xd3, 0x8b,
        0xfd, 0x23, 0x4e, 0xcd, 0xd6, 0xbb, 0xd4, 0x2e, 0xdc, 0xf7, 0xbd, 0x9c, 0x2e, 0xd8, 0x67, 0x98,
        0x06, 0x45, 0x10, 0xcc, 0x4d, 0x04, 0xc8, 0xe5, 0xe0, 0xdc, 0x73, 0xab, 0xe2, 0x57, 0x63, 0x26,
        0x1d, 0x4c, 0xa6, 0x0f, 0xdc, 0xe0, 0x86, 0xf3, 0x02, 0x14, 0xaa, 0x29, 0x0a, 0x0f, 0x63, 0xe3,
        0x9e, 0xdd, 0xc0, 0x1b, 0x90, 0x99, 0x69, 0x40, 0x40, 0x4c, 0x42, 0x52, 0xcb, 0x38, 0xe4, 0x34,
        0x5d, 0xc5, 0xf0, 0x2c, 0xeb, 0x56, 0xad, 0xd2, 0x1a, 0x7e, 0x5a, 0x34, 0x70, 0x47, 0x66, 0x5f,
        0xc7, 0x7b, 0x6a, 0x4c, 0x85, 0x35, 0x90, 0x16, 0xa9, 0xd5, 0x90, 0xbd, 0x33, 0x81, 0x2f, 0x33,
        0xc5, 0x4b, 0x2b, 0x1c, 0x98, 0x67, 0xce, 0x9e, 0xb7, 0x3c, 0xe7, 0xca, 0x8b, 0xa9, 0x7a, 0xfc,
        0xe6, 0x23, 0x88, 0x93, 0xc3, 0xb5, 0xa5, 0xb5, 0x7e, 0x16, 0xda, 0xea, 0x53, 0xeb, 0x5f, 0xf0,
        0x06, 0x13, 0xce, 0xcb, 0x6b, 0x5f, 0x0a, 0x22, 0x80, 0x7a, 0x39, 0xf9, 0x21, 0xec, 0x68, 0x61,
        0x02, 0x16, 0xcc, 0xeb, 0x11, 0x3c, 0x27, 0xb8, 0xab, 0x39, 0x3e, 0xf6, 0x08, 0x94, 0x1a, 0xc2,
        0x2f, 0xf5, 0x4b, 0x82, 0xac, 0x6a, 0xe7, 0xe7, 0x2b, 0x7b, 0x9f, 0xd9, 0x26, 0x14, 0xbc, 0x6c,
        0x8e, 0x4b, 0x32, 0xd4, 0x04, 0x62, 0xbf, 0xb0, 0x96, 0x7a, 0xd3, 0xeb, 0xa9, 0x5e, 0x35, 0xf9,
        0xe9, 0x5c, 0x72, 0x3e, 0x27, 0x43, 0xd4, 0x0b, 0x45, 0x1e, 0xad, 0x6b, 0x69, 0x2e, 0x57, 0x72,
        0x53, 0x61, 0x63, 0xac, 0xf7, 0x34, 0xf2, 0x50, 0x9b, 0xd1, 0x9a, 0x70, 0xf7, 0x8f, 0xe2, 0x5c,
        0xd2, 0x3a, 0xe1, 0xb0, 0x53, 0xbc, 0x0e, 0x11, 0x5c, 0xc6, 0xe5, 0xa4, 0x9d, 0x6a, 0xe9, 0xfb,
        0x29, 0x42, 0x53, 0xb6, 0xb4, 0xcb, 0x17, 0xc2, 0xf1, 0x20, 0xd1, 0xb8, 0xf1, 0x74, 0xbd, 0xa9,
        0x73, 0x2e, 0x29, 0xbd, 0x8e, 0xac, 0x7b, 0xe3, 0x9b, 0xae, 0xd8, 0x0a, 0x6b, 0xa3, 0x8f, 0x75,
        0xb0, 0xa6, 0xe8, 0x1e, 0x09, 0xa3, 0x16, 0x94, 0xb5, 0x4d, 0x27, 0xf9, 0x4e, 0x56, 0xde, 0x3d,
        0x95, 0xb3, 0xd5, 0xe9, 0x49, 0xb8, 0xff, 0x4d, 0xb6, 0x60, 0x33, 0x10, 0x0e, 0xb0, 0x84, 0xf7,
        0xc0, 0x97, 0x74, 0xd1, 0xb6, 0xe0, 0x03, 0x70, 0x71, 0xf7, 0x31, 0x0b, 0x08, 0xb0, 0xcc, 0x42,
        0xa5, 0x02, 0xd9, 0x80, 0x7b, 0xb3, 0xfe, 0x99, 0x52, 0x49, 0x39, 0xb1, 0x54, 0xee, 0x3c, 0x1f,
        0x5b, 0xac, 0xeb, 0xb9, 0x91, 0xf9, 0xc2, 0x09, 0xad, 0x4d, 0x0c, 0xef, 0xe0, 0x42, 0xc7, 0x86,
        0x23, 0x86, 0xd9, 0x64, 0x3f, 0x61, 0xbf, 0x60, 0x08, 0x9f, 0xad, 0x83, 0xb1, 0x4c, 0x5f, 0x61,
        0xe1, 0x27, 0xa7, 0xe4, 0xb5, 0x85, 0x08, 0x01, 0x95, 0x0b, 0xb0, 0x99, 0x6c, 0xae, 0x28, 0xfd,
        0xc0, 0x01, 0x0c, 0xf6, 0xe6, 0x7a, 0xad, 0xf2, 0x24, 0xaf, 0x7b, 0x8e, 0x5d, 0x34, 0x1c, 0xf9,
        0xea, 0x9c, 0x1c, 0x34, 0xd5, 0xaa, 0xa3, 0x0b, 0xcf, 0xf2, 0xa4, 0x24, 0x7d, 0x0a, 0x93, 0xeb,
        0x1d, 0x07, 0xb1, 0xa1, 0x49, 0x45, 0xb2, 0xff, 0xbd, 0x90, 0x85, 0x61, 0xb4, 0x70, 0xfb, 0x80,
        0x05, 0xde, 0x75, 0x0d, 0xaf, 0xac, 0xf0, 0xd6, 0x40, 0x37, 0x7c, 0xc4, 0xe6, 0x91, 0xc6, 0xe4,
        0xfa, 0x75, 0x18, 0xf2, 0x31, 0xf4, 0x54, 0xc3, 0x2a, 0x54, 0x30, 0xc9, 0xe5, 0x10, 0x82, 0x53,
        0xc5, 0x61, 0xcf, 0xae, 0x6f, 0x9a, 0xb0, 0x4f, 0x44, 0x2a, 0xa1, 0xe7, 0xea, 0x1c, 0x21, 0xdd,
        0x17, 0x0b, 0x5b, 0x4c, 0x3b, 0x1d, 0x98, 0x68, 0x3f, 0x1c, 0x3b, 0xf6, 0x8c, 0x3c, 0x07, 0x89,
        0x44, 0x69, 0x3e, 0x4f, 0x6f, 0x14, 0x84, 0xe7, 0x36, 0xfa, 0xa3, 0x3e, 0xab, 0xcf, 0xde, 0xb2,
        0x46, 0xf6, 0x0c, 0x84, 0x1e, 0x89, 0x8e, 0x19, 0x93, 0x87, 0xba, 0x24, 0x21, 0x4a, 0xf1, 0x6a,
        0x4b, 0x7c, 0x3c, 0x41, 0x4c, 0x0b, 0x9b, 0xf1, 0xb3, 0x56, 0xd9, 0xfb, 0xd9, 0x5e, 0xd4, 0x33,
        0x9a, 0x35, 0xc8, 0x4c, 0x21, 0x63, 0xb4, 0xd3, 0x1f, 0x6c, 0x80, 0xbe, 0xce, 0xb2, 0xf1, 0xd4,
        0x08, 0xce, 0xe6, 0x4d, 0xec, 0x03, 0xe3, 0x38, 0xb8, 0xf7, 0x6c, 0x94, 0x44, 0x9d, 0x4e, 0xb0,
        0xa3, 0x6d, 0xe1, 0x78, 0xd1, 0x4c, 0x19, 0xe5, 0x15, 0x54, 0x35, 0x60, 0x47, 0x1b, 0x95, 0x9d,
        0xb5, 0x09, 0x72, 0x65, 0xd9, 0x3c, 0xee, 0xfa, 0x49, 0xce, 0x0b, 0x39, 0x0b, 0x7c, 0xa2, 0x41,
        0xc8, 0x8e, 0x4f, 0xf9, 0xca, 0x3d, 0x3d, 0xa8, 0xb3, 0x6e, 0x69, 0x0b, 0x13, 0x31, 0xbb, 0x7a,
        0xa6, 0x2a, 0xa5, 0x2c, 0x17, 0x6e, 0x92, 0x89, 0x4c, 0x00, 0xd7, 0xf1, 0x71, 0x0a, 0x8a, 0x5f,
        0x32, 0x29, 0xd4, 0x85, 0x50, 0xf1, 0xf5, 0x60, 0x38, 0x03, 0xe8, 0x3b, 0x86, 0xf4, 0x00, 0x97,
        0xff, 0xdf, 0xc2, 0x9c, 0xed, 0x20, 0xd0, 0x8e, 0xa6, 0x16, 0xac, 0x5d, 0x8e, 0xfd, 0xc2, 0x01,
        0xcf, 0xcf, 0x8e, 0x94, 0x08, 0x6f, 0x46, 0xf5, 0x8d, 0x92, 0xc8, 0xd6, 0x7c, 0x85, 0x30, 0xd7,
        0x28, 0x9d, 0x51, 0x8a, 0x3c, 0xed, 0xef, 0xe6, 0x8a, 0xbf, 0x45, 0x2d, 0xaf, 0xda, 0x26, 0x3e,
        0xf6, 0x52, 0x90, 0xbb, 0x03, 0x54, 0x42, 0x26, 0xc1, 0xc2, 0xf1, 0xbd, 0x78, 0xd9, 0xc9, 0x2b,
        0xb2, 0x6e, 0x27, 0xeb, 0xa0, 0x29, 0x50, 0x76, 0x7b, 0x81, 0xb7, 0x7c, 0x2f, 0x3c, 0xd0, 0x65,
        0x99, 0x09, 0xb2, 0xda, 0x7b, 0x50, 0xdf, 0xdc, 0x51, 0x40, 0xef, 0xe7, 0xc7, 0x9a, 0xb2, 0x13,
        0xdd, 0x9b, 0x6d, 0xcc, 0x89, 0xc5, 0xc7, 0xa2, 0x65, 0x6a, 0x6c, 0xaa, 0xc0, 0xd9, 0x6f, 0x13,
        0x32, 0x61, 0xec, 0x5d
    };
#elif defined(MT5695_MODEL)
    UINT8 _au1HDCP_2X[] =
    {
        0x0a, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x4d, 0x53, 0x54, 0x41, 0x52, 0x5f, 0x53, 0x45, 0x43, 0x55, 0x52, 0x45, 0x5f, 0x53, 0x54, 0x4f,
        0x52, 0x45, 0x5f, 0x46, 0x49, 0x4c, 0x45, 0x5f, 0x4d, 0x41, 0x47, 0x49, 0x43, 0x5f, 0x49, 0x44,
        0x0f, 0xe2, 0xb9, 0xbe, 0xfb, 0xa1, 0xb7, 0x43, 0xe2, 0x56, 0x51, 0xae, 0x53, 0xe7, 0xcc, 0x2b,
        0x64, 0x4c, 0xb2, 0x1e, 0x41, 0xd4, 0x4c, 0xb5, 0x88, 0x73, 0x35, 0xd8, 0x69, 0xee, 0x76, 0x7d,
        0x63, 0xf7, 0xdb, 0x6f, 0x4e, 0xc1, 0xba, 0xee, 0x39, 0x3f, 0x3f, 0x53, 0xd5, 0x06, 0x94, 0xef,
        0xa1, 0x4a, 0x00, 0x1d, 0xc3, 0xd8, 0xa8, 0x1e, 0x6c, 0xa1, 0x8b, 0x8a, 0x87, 0xc3, 0x18, 0x7b,
        0x19, 0xe5, 0xed, 0x89, 0xa4, 0x99, 0x0b, 0x34, 0x17, 0x34, 0x3b, 0x1f, 0x20, 0xdc, 0x92, 0x9a,
        0x50, 0x28, 0xb3, 0xb7, 0x90, 0x0b, 0x8f, 0x05, 0xd2, 0x2c, 0x2c, 0x21, 0x5d, 0x5a, 0x90, 0xaa,
        0x84, 0x91, 0xb0, 0xde, 0x77, 0x5b, 0x08, 0xe9, 0xae, 0x95, 0x26, 0x4a, 0x49, 0xed, 0xab, 0x0a,
        0x17, 0xd4, 0x75, 0xfd, 0x25, 0x88, 0xd2, 0x22, 0x12, 0xf3, 0x9c, 0xa6, 0x90, 0x52, 0xb8, 0x5d,
        0xa5, 0xb8, 0x4d, 0xac, 0x15, 0x02, 0x39, 0x04, 0x85, 0x6b, 0x4f, 0xc2, 0xfd, 0x94, 0x63, 0x42,
        0x13, 0xd5, 0x82, 0x54, 0x4d, 0x12, 0x25, 0x65, 0x90, 0xb3, 0xb9, 0xcf, 0x37, 0xa5, 0xb1, 0x88,
        0xa8, 0xee, 0x39, 0x66, 0x4b, 0x48, 0xc0, 0x12, 0xbf, 0x80, 0x75, 0x99, 0x22, 0x78, 0xc1, 0xc9,
        0xa0, 0x8c, 0x1f, 0x77, 0xa8, 0xa0, 0xae, 0xbb, 0x27, 0x30, 0x43, 0x2b, 0x1b, 0x3e, 0x87, 0x66,
        0x9f, 0x27, 0xb3, 0xdd, 0x39, 0x7b, 0x77, 0x2b, 0x74, 0x2e, 0x1f, 0xa6, 0x3a, 0x7c, 0xfc, 0x3d,
        0xf3, 0xd2, 0xfa, 0x14, 0x96, 0x72, 0x40, 0x63, 0x0e, 0x1d, 0x91, 0x71, 0x81, 0x46, 0x0c, 0xf8,
        0xfc, 0xf1, 0xc1, 0xc9, 0xe2, 0x06, 0x02, 0x03, 0x06, 0x2c, 0x5a, 0xd2, 0xf0, 0x4b, 0x80, 0x85,
        0x31, 0xbb, 0x4a, 0x5c, 0x01, 0x47, 0x33, 0x5b, 0x59, 0xa2, 0xb1, 0xf7, 0xe1, 0xea, 0xad, 0xf8,
        0xd8, 0xfb, 0x42, 0x8a, 0x4b, 0x64, 0xab, 0xef, 0x90, 0x01, 0xbd, 0xa6, 0x8a, 0x88, 0x4c, 0x7b,
        0x4a, 0x97, 0xe6, 0x38, 0x49, 0xff, 0x44, 0x23, 0x55, 0x62, 0xbb, 0xd8, 0x95, 0xea, 0x33, 0x58,
        0xb8, 0x13, 0x98, 0xd6, 0xff, 0x1e, 0x00, 0xca, 0xd7, 0x60, 0x3e, 0x78, 0x45, 0x77, 0x0d, 0x0b,
        0xa8, 0xff, 0x8a, 0xb7, 0x0c, 0x60, 0x7a, 0xdd, 0x4e, 0x0d, 0x73, 0x21, 0xdc, 0xc2, 0xca, 0x3d,
        0x72, 0xb7, 0x21, 0x9c, 0x20, 0x06, 0xf0, 0xef, 0x1a, 0x2f, 0x8d, 0xa7, 0xb2, 0x84, 0xf7, 0xce,
        0x65, 0xa5, 0xcf, 0x73, 0x3b, 0xdd, 0xd7, 0xab, 0x44, 0x7a, 0x5e, 0x6a, 0x53, 0xa7, 0xd0, 0x91,
        0x2e, 0xd0, 0x10, 0xd2, 0xf0, 0xd6, 0xcd, 0x0c, 0xdd, 0x3c, 0x37, 0xa9, 0x66, 0xb9, 0x5a, 0xae,
        0x80, 0x61, 0x0e, 0x1d, 0xd5, 0x48, 0xe4, 0x84, 0xcb, 0x5c, 0x11, 0xbc, 0x73, 0x74, 0x53, 0x9c,
        0xe7, 0x79, 0x0f, 0xfc, 0x00, 0x2b, 0xae, 0x91, 0x75, 0x2a, 0x72, 0x60, 0x41, 0xac, 0x58, 0xfa,
        0x38, 0xb1, 0x6f, 0x64, 0x00, 0xe7, 0x1b, 0x22, 0x8b, 0x19, 0xd1, 0x91, 0xf9, 0xd7, 0x30, 0x3b,
        0x0b, 0xd8, 0x90, 0x8f, 0xb6, 0x14, 0x63, 0xf0, 0x05, 0x2a, 0xfd, 0x4c, 0x3c, 0x13, 0x6a, 0xf6,
        0xae, 0x2a, 0xb7, 0xb5, 0x0e, 0xc7, 0x58, 0x78, 0x98, 0xe4, 0xd3, 0x4b, 0x3e, 0x06, 0x8f, 0xae,
        0xb0, 0x39, 0x44, 0x43, 0x9b, 0x3e, 0x9a, 0xe4, 0x1e, 0x90, 0x9e, 0x04, 0x89, 0xee, 0xba, 0x4e,
        0xc4, 0xa1, 0x6a, 0xb1, 0x57, 0xd7, 0xd5, 0xe6, 0x14, 0xcb, 0x8a, 0x3b, 0xd1, 0x56, 0xdf, 0x18,
        0xc6, 0x8f, 0x5c, 0xd2, 0x11, 0x19, 0xa5, 0x55, 0xd0, 0x71, 0x6f, 0xff, 0xc7, 0x54, 0xa9, 0x8d,
        0x11, 0x8f, 0xab, 0xe5, 0x3e, 0xfa, 0x48, 0x35, 0x2b, 0xf2, 0x75, 0x2a, 0xa1, 0x5b, 0xa9, 0xe1,
        0xcd, 0x8b, 0xa3, 0xbd, 0x74, 0x00, 0xa9, 0xff, 0x6f, 0x3f, 0xe6, 0x62, 0x5d, 0x80, 0x21, 0x2b,
        0x12, 0xd5, 0x5c, 0x91, 0x59, 0x52, 0x8d, 0x8a, 0x0a, 0x9d, 0x8a, 0x62, 0x24, 0xb0, 0x36, 0xc8,
        0x65, 0xb0, 0x80, 0x08, 0x03, 0xd9, 0xfc, 0x72, 0xb1, 0xde, 0x86, 0xc0, 0x20, 0xfe, 0x48, 0xce,
        0xda, 0x35, 0x07, 0xc4, 0xff, 0x95, 0x68, 0x03, 0xf0, 0x69, 0xe1, 0x1d, 0x30, 0xb4, 0x45, 0xcc,
        0xae, 0x9c, 0x5f, 0xae, 0x9e, 0x58, 0xda, 0x82, 0x89, 0x94, 0x38, 0xea, 0x96, 0x91, 0xfe, 0xc3,
        0x73, 0x1b, 0xa4, 0x2e, 0x44, 0x29, 0xed, 0x8a, 0x56, 0x33, 0xd0, 0x63, 0xac, 0xdc, 0xa8, 0x02,
        0x94, 0xfa, 0xc3, 0x34, 0xc7, 0x99, 0x53, 0x9d, 0x58, 0x8f, 0x36, 0x1d, 0xd8, 0xfb, 0x40, 0x60,
        0x6a, 0x82, 0x6e, 0x14, 0x7b, 0x70, 0x0c, 0x48, 0x6d, 0x54, 0x08, 0x02, 0x96, 0x99, 0x31, 0xb9,
        0xa6, 0xf4, 0xd9, 0xda, 0x6d, 0x31, 0x52, 0x27, 0xd5, 0xfd, 0xfa, 0x59, 0xdd, 0xcb, 0x92, 0x54,
        0xff, 0xc6, 0xe5, 0xd5, 0x19, 0xcd, 0x83, 0x89, 0x66, 0xb1, 0x3b, 0x2e, 0x01, 0xa5, 0x41, 0xa2,
        0x10, 0x72, 0xb3, 0x4b, 0xbb, 0x71, 0xf7, 0x39, 0xa2, 0x3c, 0x9f, 0x58, 0x71, 0x79, 0xad, 0x96,
        0x07, 0x73, 0xf4, 0x3c, 0x0b, 0x28, 0x30, 0xab, 0x47, 0xb0, 0x7b, 0x0e, 0x81, 0xa8, 0x86, 0xb1,
        0xc0, 0x75, 0xe0, 0xab, 0x39, 0x92, 0x57, 0xda, 0xc8, 0xde, 0xd4, 0x77, 0x20, 0x35, 0xe4, 0x6a,
        0x60, 0xe5, 0x8f, 0x6d, 0xc3, 0x49, 0x9b, 0x42, 0x5f, 0x6c, 0xac, 0x54, 0xb9, 0xbf, 0x9f, 0x0c,
        0xfa, 0x56, 0x93, 0x93, 0x16, 0x70, 0xd1, 0x52, 0xe0, 0x77, 0xed, 0x32, 0xcf, 0xb4, 0xa4, 0xd3,
        0xab, 0xfe, 0x5f, 0x70, 0x1b, 0x0b, 0xfe, 0xcf, 0xcf, 0x9a, 0xcf, 0x1b, 0x6a, 0x30, 0xb0, 0xab,
        0x44, 0x7f, 0x1e, 0x9f, 0xc6, 0xbf, 0x64, 0x99, 0xc5, 0x43, 0x43, 0xf3, 0x1d, 0xee, 0x1d, 0x25,
        0x0c, 0x94, 0x20, 0xd0, 0xc6, 0xba, 0x8b, 0x09, 0x87, 0xa3, 0xe3, 0xfd, 0x8a, 0x63, 0x4a, 0x4e,
        0x42, 0x73, 0x06, 0x50, 0x67, 0x4b, 0xc5, 0x85, 0x83, 0x02, 0x18, 0xb7, 0xaf, 0x83, 0x33, 0x6f,
        0xbf, 0x79, 0x24, 0xa0, 0xb7, 0xcb, 0x80, 0x91, 0xeb, 0x07, 0x84, 0x7e, 0x3d, 0x48, 0x98, 0x10,
        0x4f, 0x7e, 0xe7, 0xfe, 0x59, 0x41, 0x2a, 0x66, 0xd7, 0x22, 0xe0, 0x6a, 0x80, 0xfe, 0x2d, 0xa5,
        0x52, 0x33, 0xeb, 0x46, 0xf3, 0x6b, 0x8c, 0x32, 0xca, 0xcd, 0x02, 0x84, 0x1e, 0x41, 0x39, 0x1c,
        0xf5, 0x56, 0x77, 0x31, 0x1a, 0x4d, 0x66, 0xf3, 0xaa, 0x0d, 0xf7, 0x2c, 0xb5, 0xbd, 0xab, 0x47,
        0x16, 0x73, 0x40, 0x2c, 0x6f, 0x36, 0x5d, 0x0c, 0xdf, 0x4c, 0x7c, 0xfd, 0x99, 0x93, 0xe8, 0x97,
        0xdc, 0xfc, 0x89, 0x10, 0xe9, 0x97, 0xdd, 0x36, 0x10, 0x06, 0xe9, 0xfa, 0x83, 0xed, 0x51, 0x7f,
        0x41, 0xda, 0x75, 0x27, 0x1f, 0x2e, 0x31, 0x51, 0xde, 0x93, 0x69, 0xff, 0x74, 0xe1, 0xcc, 0xb5,
        0x27, 0x6d, 0xf4, 0x3a, 0xc9, 0xb3, 0x38, 0xdb, 0x4b, 0x05, 0xca, 0xef, 0x2c, 0x57, 0xc4, 0x5a,
        0x0d, 0x8c, 0x3c, 0x26, 0xe8, 0x16, 0x45, 0x8d, 0x1d, 0xa6, 0x81, 0x08, 0xfa, 0x4f, 0xbf, 0x39,
        0x4e, 0xef, 0x19, 0x7a, 0xb8, 0xcb, 0x29, 0x49, 0xea, 0x81, 0x35, 0x0b, 0x51, 0x25, 0xab, 0xfd,
        0x8d, 0x01, 0xf4, 0xba
    };
#elif defined(MT5583_MODEL)
    // 5583 don't need HDCP 2.x
    UINT8 _au1HDCP_2X[] =
    {
        0x0a, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x4d, 0x53, 0x54, 0x41, 0x52, 0x5f, 0x53, 0x45, 0x43, 0x55, 0x52, 0x45, 0x5f, 0x53, 0x54, 0x4f,
        0x52, 0x45, 0x5f, 0x46, 0x49, 0x4c, 0x45, 0x5f, 0x4d, 0x41, 0x47, 0x49, 0x43, 0x5f, 0x49, 0x44,
        0x4b, 0xb5, 0x0d, 0x71, 0x84, 0xfe, 0xa8, 0xaf, 0xfd, 0x01, 0x4e, 0x5d, 0xc9, 0xf1, 0xfd, 0x67,
        0x46, 0x9c, 0xef, 0x17, 0xed, 0xef, 0x70, 0xe5, 0xa0, 0xc5, 0x6a, 0x9b, 0x08, 0x87, 0x43, 0x39,
        0x5a, 0xed, 0x84, 0x45, 0x84, 0xf9, 0xfb, 0xa8, 0x08, 0x69, 0x88, 0xa1, 0x57, 0x9e, 0x3b, 0x9a,
        0xe7, 0xf2, 0x95, 0x7c, 0xbd, 0x63, 0x97, 0xc7, 0x0c, 0x05, 0xa6, 0xd7, 0x7a, 0x17, 0xe0, 0x44,
        0xb2, 0xfb, 0x1c, 0xa0, 0x8f, 0xea, 0x77, 0x25, 0x6d, 0xbb, 0x8f, 0xee, 0x37, 0xac, 0x15, 0xcb,
        0xbd, 0xb0, 0x4c, 0xc6, 0x8e, 0x40, 0xa2, 0x4f, 0x70, 0x6c, 0xa9, 0x86, 0x3f, 0x8b, 0xab, 0xa6,
        0xaf, 0x69, 0x5c, 0x7f, 0x9b, 0x10, 0x13, 0x90, 0x31, 0x0a, 0xbb, 0x01, 0x4d, 0x55, 0x93, 0x22,
        0xbd, 0xc7, 0x0b, 0x34, 0x26, 0x72, 0xaa, 0x39, 0x6d, 0x02, 0x8e, 0x0a, 0x37, 0xa2, 0xea, 0xfe,
        0xe9, 0x70, 0x5f, 0x34, 0x8b, 0xd4, 0xfe, 0xd7, 0x2d, 0x09, 0xee, 0xe7, 0x49, 0x41, 0x05, 0xbb,
        0x5c, 0xac, 0xd2, 0xa3, 0x11, 0xa5, 0x36, 0xef, 0xa6, 0xaa, 0x01, 0x20, 0x78, 0x8f, 0x54, 0xec,
        0xf3, 0x83, 0x99, 0xb1, 0x4c, 0x03, 0x41, 0x51, 0x0e, 0x41, 0x06, 0x1c, 0xfe, 0xf1, 0x48, 0xa4,
        0x67, 0x95, 0x87, 0x7e, 0x24, 0x97, 0x05, 0xc1, 0x03, 0xf4, 0x02, 0x43, 0xa5, 0x7e, 0x05, 0xbe,
        0x3d, 0x20, 0x83, 0xce, 0x39, 0x61, 0x0c, 0x8a, 0xda, 0xbc, 0xbe, 0x9b, 0x05, 0xfc, 0xd3, 0x8b,
        0xfd, 0x23, 0x4e, 0xcd, 0xd6, 0xbb, 0xd4, 0x2e, 0xdc, 0xf7, 0xbd, 0x9c, 0x2e, 0xd8, 0x67, 0x98,
        0x06, 0x45, 0x10, 0xcc, 0x4d, 0x04, 0xc8, 0xe5, 0xe0, 0xdc, 0x73, 0xab, 0xe2, 0x57, 0x63, 0x26,
        0x1d, 0x4c, 0xa6, 0x0f, 0xdc, 0xe0, 0x86, 0xf3, 0x02, 0x14, 0xaa, 0x29, 0x0a, 0x0f, 0x63, 0xe3,
        0x9e, 0xdd, 0xc0, 0x1b, 0x90, 0x99, 0x69, 0x40, 0x40, 0x4c, 0x42, 0x52, 0xcb, 0x38, 0xe4, 0x34,
        0x5d, 0xc5, 0xf0, 0x2c, 0xeb, 0x56, 0xad, 0xd2, 0x1a, 0x7e, 0x5a, 0x34, 0x70, 0x47, 0x66, 0x5f,
        0xc7, 0x7b, 0x6a, 0x4c, 0x85, 0x35, 0x90, 0x16, 0xa9, 0xd5, 0x90, 0xbd, 0x33, 0x81, 0x2f, 0x33,
        0xc5, 0x4b, 0x2b, 0x1c, 0x98, 0x67, 0xce, 0x9e, 0xb7, 0x3c, 0xe7, 0xca, 0x8b, 0xa9, 0x7a, 0xfc,
        0xe6, 0x23, 0x88, 0x93, 0xc3, 0xb5, 0xa5, 0xb5, 0x7e, 0x16, 0xda, 0xea, 0x53, 0xeb, 0x5f, 0xf0,
        0x06, 0x13, 0xce, 0xcb, 0x6b, 0x5f, 0x0a, 0x22, 0x80, 0x7a, 0x39, 0xf9, 0x21, 0xec, 0x68, 0x61,
        0x02, 0x16, 0xcc, 0xeb, 0x11, 0x3c, 0x27, 0xb8, 0xab, 0x39, 0x3e, 0xf6, 0x08, 0x94, 0x1a, 0xc2,
        0x2f, 0xf5, 0x4b, 0x82, 0xac, 0x6a, 0xe7, 0xe7, 0x2b, 0x7b, 0x9f, 0xd9, 0x26, 0x14, 0xbc, 0x6c,
        0x8e, 0x4b, 0x32, 0xd4, 0x04, 0x62, 0xbf, 0xb0, 0x96, 0x7a, 0xd3, 0xeb, 0xa9, 0x5e, 0x35, 0xf9,
        0xe9, 0x5c, 0x72, 0x3e, 0x27, 0x43, 0xd4, 0x0b, 0x45, 0x1e, 0xad, 0x6b, 0x69, 0x2e, 0x57, 0x72,
        0x53, 0x61, 0x63, 0xac, 0xf7, 0x34, 0xf2, 0x50, 0x9b, 0xd1, 0x9a, 0x70, 0xf7, 0x8f, 0xe2, 0x5c,
        0xd2, 0x3a, 0xe1, 0xb0, 0x53, 0xbc, 0x0e, 0x11, 0x5c, 0xc6, 0xe5, 0xa4, 0x9d, 0x6a, 0xe9, 0xfb,
        0x29, 0x42, 0x53, 0xb6, 0xb4, 0xcb, 0x17, 0xc2, 0xf1, 0x20, 0xd1, 0xb8, 0xf1, 0x74, 0xbd, 0xa9,
        0x73, 0x2e, 0x29, 0xbd, 0x8e, 0xac, 0x7b, 0xe3, 0x9b, 0xae, 0xd8, 0x0a, 0x6b, 0xa3, 0x8f, 0x75,
        0xb0, 0xa6, 0xe8, 0x1e, 0x09, 0xa3, 0x16, 0x94, 0xb5, 0x4d, 0x27, 0xf9, 0x4e, 0x56, 0xde, 0x3d,
        0x95, 0xb3, 0xd5, 0xe9, 0x49, 0xb8, 0xff, 0x4d, 0xb6, 0x60, 0x33, 0x10, 0x0e, 0xb0, 0x84, 0xf7,
        0xc0, 0x97, 0x74, 0xd1, 0xb6, 0xe0, 0x03, 0x70, 0x71, 0xf7, 0x31, 0x0b, 0x08, 0xb0, 0xcc, 0x42,
        0xa5, 0x02, 0xd9, 0x80, 0x7b, 0xb3, 0xfe, 0x99, 0x52, 0x49, 0x39, 0xb1, 0x54, 0xee, 0x3c, 0x1f,
        0x5b, 0xac, 0xeb, 0xb9, 0x91, 0xf9, 0xc2, 0x09, 0xad, 0x4d, 0x0c, 0xef, 0xe0, 0x42, 0xc7, 0x86,
        0x23, 0x86, 0xd9, 0x64, 0x3f, 0x61, 0xbf, 0x60, 0x08, 0x9f, 0xad, 0x83, 0xb1, 0x4c, 0x5f, 0x61,
        0xe1, 0x27, 0xa7, 0xe4, 0xb5, 0x85, 0x08, 0x01, 0x95, 0x0b, 0xb0, 0x99, 0x6c, 0xae, 0x28, 0xfd,
        0xc0, 0x01, 0x0c, 0xf6, 0xe6, 0x7a, 0xad, 0xf2, 0x24, 0xaf, 0x7b, 0x8e, 0x5d, 0x34, 0x1c, 0xf9,
        0xea, 0x9c, 0x1c, 0x34, 0xd5, 0xaa, 0xa3, 0x0b, 0xcf, 0xf2, 0xa4, 0x24, 0x7d, 0x0a, 0x93, 0xeb,
        0x1d, 0x07, 0xb1, 0xa1, 0x49, 0x45, 0xb2, 0xff, 0xbd, 0x90, 0x85, 0x61, 0xb4, 0x70, 0xfb, 0x80,
        0x05, 0xde, 0x75, 0x0d, 0xaf, 0xac, 0xf0, 0xd6, 0x40, 0x37, 0x7c, 0xc4, 0xe6, 0x91, 0xc6, 0xe4,
        0xfa, 0x75, 0x18, 0xf2, 0x31, 0xf4, 0x54, 0xc3, 0x2a, 0x54, 0x30, 0xc9, 0xe5, 0x10, 0x82, 0x53,
        0xc5, 0x61, 0xcf, 0xae, 0x6f, 0x9a, 0xb0, 0x4f, 0x44, 0x2a, 0xa1, 0xe7, 0xea, 0x1c, 0x21, 0xdd,
        0x17, 0x0b, 0x5b, 0x4c, 0x3b, 0x1d, 0x98, 0x68, 0x3f, 0x1c, 0x3b, 0xf6, 0x8c, 0x3c, 0x07, 0x89,
        0x44, 0x69, 0x3e, 0x4f, 0x6f, 0x14, 0x84, 0xe7, 0x36, 0xfa, 0xa3, 0x3e, 0xab, 0xcf, 0xde, 0xb2,
        0x46, 0xf6, 0x0c, 0x84, 0x1e, 0x89, 0x8e, 0x19, 0x93, 0x87, 0xba, 0x24, 0x21, 0x4a, 0xf1, 0x6a,
        0x4b, 0x7c, 0x3c, 0x41, 0x4c, 0x0b, 0x9b, 0xf1, 0xb3, 0x56, 0xd9, 0xfb, 0xd9, 0x5e, 0xd4, 0x33,
        0x9a, 0x35, 0xc8, 0x4c, 0x21, 0x63, 0xb4, 0xd3, 0x1f, 0x6c, 0x80, 0xbe, 0xce, 0xb2, 0xf1, 0xd4,
        0x08, 0xce, 0xe6, 0x4d, 0xec, 0x03, 0xe3, 0x38, 0xb8, 0xf7, 0x6c, 0x94, 0x44, 0x9d, 0x4e, 0xb0,
        0xa3, 0x6d, 0xe1, 0x78, 0xd1, 0x4c, 0x19, 0xe5, 0x15, 0x54, 0x35, 0x60, 0x47, 0x1b, 0x95, 0x9d,
        0xb5, 0x09, 0x72, 0x65, 0xd9, 0x3c, 0xee, 0xfa, 0x49, 0xce, 0x0b, 0x39, 0x0b, 0x7c, 0xa2, 0x41,
        0xc8, 0x8e, 0x4f, 0xf9, 0xca, 0x3d, 0x3d, 0xa8, 0xb3, 0x6e, 0x69, 0x0b, 0x13, 0x31, 0xbb, 0x7a,
        0xa6, 0x2a, 0xa5, 0x2c, 0x17, 0x6e, 0x92, 0x89, 0x4c, 0x00, 0xd7, 0xf1, 0x71, 0x0a, 0x8a, 0x5f,
        0x32, 0x29, 0xd4, 0x85, 0x50, 0xf1, 0xf5, 0x60, 0x38, 0x03, 0xe8, 0x3b, 0x86, 0xf4, 0x00, 0x97,
        0xff, 0xdf, 0xc2, 0x9c, 0xed, 0x20, 0xd0, 0x8e, 0xa6, 0x16, 0xac, 0x5d, 0x8e, 0xfd, 0xc2, 0x01,
        0xcf, 0xcf, 0x8e, 0x94, 0x08, 0x6f, 0x46, 0xf5, 0x8d, 0x92, 0xc8, 0xd6, 0x7c, 0x85, 0x30, 0xd7,
        0x28, 0x9d, 0x51, 0x8a, 0x3c, 0xed, 0xef, 0xe6, 0x8a, 0xbf, 0x45, 0x2d, 0xaf, 0xda, 0x26, 0x3e,
        0xf6, 0x52, 0x90, 0xbb, 0x03, 0x54, 0x42, 0x26, 0xc1, 0xc2, 0xf1, 0xbd, 0x78, 0xd9, 0xc9, 0x2b,
        0xb2, 0x6e, 0x27, 0xeb, 0xa0, 0x29, 0x50, 0x76, 0x7b, 0x81, 0xb7, 0x7c, 0x2f, 0x3c, 0xd0, 0x65,
        0x99, 0x09, 0xb2, 0xda, 0x7b, 0x50, 0xdf, 0xdc, 0x51, 0x40, 0xef, 0xe7, 0xc7, 0x9a, 0xb2, 0x13,
        0xdd, 0x9b, 0x6d, 0xcc, 0x89, 0xc5, 0xc7, 0xa2, 0x65, 0x6a, 0x6c, 0xaa, 0xc0, 0xd9, 0x6f, 0x13,
        0x32, 0x61, 0xec, 0x5d
    };
#endif

    
    #if 0
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T z_size = sizeof(b_on);
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDCP_DEF;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&b_on;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* Set from driver */
    i4_ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
    }
    #else
    
    DBG_LOG_PRINT(("\n %s Line: %d\n", __FUNCTION__, __LINE__));
    #if 0
  #ifdef  MT5691_MODEL
    i4_ret=TEEC_SetIniPath("/vendor/tvconfig/config/tpv/ModelGroup302/ModelIndex1/drm/");
  #else
    i4_ret=TEEC_SetIniPath("/vendor/tvconfig/config/tpv/ModelGroup312/ModelIndex1/drm/");
  #endif
    TPV_LOG_ON_FAIL(i4_ret);
    i4_ret=TEEC_SendData2TA("8", 1);  //HDCP 2.X
    TPV_LOG_ON_FAIL(i4_ret);
    #endif

#if 0 // remove, 5583 k model need HDCP 22
#ifdef  MT5691_MODEL
    i4_ret=TEEC_Key2TA("8", 1, (char *)_au1HDCP_2X, sizeof(_au1HDCP_2X));
    TPV_LOG_ON_FAIL(i4_ret);
#elif defined(MT5695_MODEL)
    i4_ret=TEEC_Key2TA("8", 1, (char *)_au1HDCP_2X, sizeof(_au1HDCP_2X));
    TPV_LOG_ON_FAIL(i4_ret);
#elif defined(MT5583_MODEL) 
    ; // 5583 don't need HDCP 2.x
#endif
#endif
    i4_ret=TEEC_Key2TA("8", 1, (char *)_au1HDCP_2X, sizeof(_au1HDCP_2X));
    TPV_LOG_ON_FAIL(i4_ret);
    
    i4_ret=TEEC_Key2TA("21", 0, (char *)_au1HDCP, sizeof(_au1HDCP));
    TPV_LOG_ON_FAIL(i4_ret);
    //i4_ret=TEEC_SendData2TA("21", 0); //HDCP 1.X
    //TPV_LOG_ON_FAIL(i4_ret);
    
    #endif
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_cust_odm_write_HDCP_1_X
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_odm_write_HDCP_1_X(UINT8 * pui1_key)
{
    #if 0
    UINT8 ui1_key_buffer[304] = {0};
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32                        i4_ret = APP_CFGR_OK;  
    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);
    
    c_memcpy(ui1_key_buffer, pui1_key, z_size);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDCP_1_X;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_key_buffer;
    t_op_info.u.t_cust_spec_set_info.z_size = sizeof(ui1_key_buffer);
    t_op_info.u.t_cust_spec_set_info.b_store = FALSE; 
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size_drv
                            );
                                
    if (i4_ret < 0)
    {
        DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    #else
    UINT8 ui1_key_buffer[TPV_HDCP1X_SIZE] = {0};
    CHAR    s_filename[512 + 64] = {0};
    CHAR    s_filename_reserve[512 + 64] = {0};
    INT32   i4_ret = 0;  
    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);
    struct stat st = {0};
    FILE *pFile2;
    size_t z_size_wirte = 0;

    c_memcpy(ui1_key_buffer, pui1_key, z_size);
    
    i4_ret = TEEC_Key2TA("21", 0, (char *)ui1_key_buffer, sizeof(ui1_key_buffer));
    TPV_LOG_ON_FAIL(i4_ret);

    c_sprintf(s_filename_reserve, TPV_HDCP_PATH_BACKUP"%s", "/hdcp_key.bin");
    
    DBG_LOG_PRINT(("HDCP 1.X path : %s", s_filename));

    if (stat(TPV_HDCP_PATH_BACKUP, &st) == -1) {
        TPV_LOG_ON_FAIL(mkdir(TPV_HDCP_PATH_BACKUP, S_IRWXU));
    }

    // Key backup
    pFile2 = fopen(s_filename_reserve,"wb");
    if(pFile2 == NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename_reserve));
    }
    else
    {
        z_size_wirte = fwrite(ui1_key_buffer,1,sizeof(ui1_key_buffer),pFile2);
        DBG_LOG_PRINT(("HDCP 1.X wirte : %d\n", z_size_wirte));
        fclose(pFile2);
    }

    AP_SYSTEM_CALL("sync");

    //i4_ret=TEEC_SendData2TA("21", 0); //HDCP 1.X
    //TPV_LOG_ON_FAIL(i4_ret);
    
    #endif
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_cust_odm_get_HDCP_1_X_KSV
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_odm_get_HDCP_1_X_KSV(UINT8 * pui1_key)
{
    UINT8 ui1_ksv_buffer[5] = {0};
    CHAR    s_filename[512 + 64] = {0};
    INT32   i4_ret = 0;  
    FILE *pFile;
    size_t z_size_read = 0;
    
    //c_memcpy(ui1_key_buffer, pui1_key, z_size);
    
    //c_sprintf(s_filename,"/vendor/tvconfig/config/tpv/ModelGroup192/ModelIndex1/hdcp/hdcp_key.bin");
    c_sprintf(s_filename, TPV_HDCP_PATH_BACKUP"%s", "/hdcp_key.bin");
    DBG_LOG_PRINT(("HDCP 1.X path : %s", s_filename));

    pFile = fopen(s_filename,"rb" );
    if(pFile == NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
        i4_ret = -1;
        return i4_ret;
    }
    else
    {
        fseek(pFile, SEEK_SET, 0);
        z_size_read = fread((void *)ui1_ksv_buffer, sizeof(ui1_ksv_buffer), 1, pFile);
        DBG_LOG_PRINT(("HDCP 1.X read : %d\n", z_size_read));
        fclose(pFile);
    }
    
    c_memcpy(pui1_key, ui1_ksv_buffer, sizeof(ui1_ksv_buffer));
    
    return i4_ret;
}

/*-----------------------------------------------------------------------------
* Name a_cfg_cust_odm_get_HDCP_2_X_RECEIVE_ID
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_odm_get_HDCP_2_X_RECEIVE_ID(UINT8 * pui1_key)
{
    UINT8 ui1_ksv_buffer[5] = {0};
    CHAR    s_filename[512 + 64] = {0};
    INT32   i4_ret = APP_CFGR_OK;  
    FILE *pFile;
    size_t z_size_read = 0;
    
    //c_memcpy(ui1_key_buffer, pui1_key, z_size);
    
    //c_sprintf(s_filename,"/vendor/tvconfig/config/tpv/ModelGroup192/ModelIndex1/hdcp/hdcp_key.bin");
    c_sprintf(s_filename, TPV_HDCP_PATH_BACKUP"%s", "/hdcp2_key.bin");
    DBG_LOG_PRINT(("HDCP 2.X path : %s", s_filename));

    pFile = fopen(s_filename,"rb" );
    if(pFile == NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
        i4_ret = -1;
        return i4_ret;
    }
    else
    {
        fseek(pFile, SEEK_SET, 0);
        z_size_read = fread((void *)ui1_ksv_buffer, sizeof(ui1_ksv_buffer), 1, pFile);
        DBG_LOG_PRINT(("HDCP 2.X read : %d\n", z_size_read));
        fclose(pFile);
    }
    
    c_memcpy(pui1_key, ui1_ksv_buffer, sizeof(ui1_ksv_buffer));
    
    return i4_ret;
}

/*-----------------------------------------------------------------------------
* Name a_cfg_custom_reset_GAMMA_key
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern VOID a_cfg_custom_reset_GAMMA_key(VOID)
{
    INT32   i4_ret;
    UINT32   ui4_reset = 0;
    DRV_CUST_OPERATION_INFO_T	  t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui4_reset);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_GAMMA_KEY_RESET;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui4_reset;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size_drv
                            );

    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
    }

}

/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_Set_Factory_GAMMA_OnOff
* Description: enable/disable Factory external gamma
* Input arguments: 0: disable, 1: enable
* Output arguments: N/A
* Returns: N/A
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_Set_Factory_GAMMA_OnOff(BOOL bOnOff)  //Ben 20180410
{
    INT32	i4_ret;
    DRV_CUST_OPERATION_INFO_T	  t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(bOnOff);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_FACTORY_GAMMA_ONOFF;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&bOnOff;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

		 /* set to driver */
    i4_ret = c_rm_set_comp(
						 DRVT_CUST_DRV,
						 DRV_CUST_COMP_ID,
						 FALSE,
						 ANY_PORT_NUM,
						 0,
						 &t_op_info,
						 z_size_drv
						 );

    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    return RMR_OK;
}

/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_Get_Factory_GAMMA_OnOff
* Description: Get Factory Gamma status
* Input arguments: point variable
* Output arguments: N/A
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_Get_Factory_GAMMA_OnOff(BOOL *bOnOff)  // Ben 20180410
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(bOnOff);
    

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_FACTORY_GAMMA_ONOFF;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)bOnOff;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }
    
    return RMR_OK;
}
#if 0
/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_Set_Factory_PQbypass_OnOff
* Description: enable/disable PQ bypss
* Input arguments: 0: disable, 1: enable
* Output arguments: N/A
* Returns: N/A
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_Set_Factory_PQbypass_OnOff(BOOL bOnOff)  //Ben 20180416
{
    INT32	i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T	  t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(bOnOff);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_VID_PQ_ALL_ONOFF;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&bOnOff;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size_drv
                            );

    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
    }

    return i4_ret;
}
#endif

extern VOID a_cfg_custom_Set_Lcdim_Scrolling_OnOff(BOOL bOnOff)  //Ben 20180413
{
	INT32	i4_ret;
	DRV_CUST_OPERATION_INFO_T	  t_op_info;
	SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    UINT32 u4ScrollingParam;
    SIZE_T z_size = sizeof(u4ScrollingParam);

    if (bOnOff == TRUE)
        u4ScrollingParam = 0x10000FFF; // bit-0~3 light level, bit-7 on/off
    else
        u4ScrollingParam = 0x00000FFF; // bit-0~3 light level, bit-7 on/off
	
	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
	t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_LDM_SCROLLING_FUN;
	t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&u4ScrollingParam;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* set to driver */
    i4_ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );

    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
    }
    //return i4_ret;
}
#if 0
extern INT32 a_cfg_custom_Set_Internal_RGB_Pattern(UINT8 * pui1_RGB_para)   //Ben 20190125
{
    UINT8 ui1_RGB_para_buffer[6]={0};
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    INT32                        i4_ret = APP_CFGR_OK;  
    SIZE_T z_size = sizeof(ui1_RGB_para_buffer);
    
    c_memcpy(ui1_RGB_para_buffer, pui1_RGB_para, z_size);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_GAMMA_RGB;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui1_RGB_para_buffer;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE; 
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size_drv
                            );
                                
    if (i4_ret < 0)
    {
        DBG_ERROR(("\n%s,%s,%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, i4_ret));
    }
    return i4_ret;
}
#endif
extern INT32 a_cfg_custom_Set_Flat_pattern(UINT8 ui1_idx)
{
    INT32 i4_ret = 0;
    ACFG_TYPE_SET_RGB_T t_info;

    switch(ui1_idx)
    {
        case 0:     // 0%
            t_info.bEnable = TRUE;
            t_info.u2R = 0;
            t_info.u2G = 0;
            t_info.u2B = 0;
            break;
        case 1:     // 10%
            t_info.bEnable = TRUE;
            t_info.u2R = 102;
            t_info.u2G = 102;
            t_info.u2B = 102;
            break;
        case 2:     // 20%
            t_info.bEnable = TRUE;
            t_info.u2R = 204;
            t_info.u2G = 204;
            t_info.u2B = 204;
            break;
        case 3:     // 30%
            t_info.bEnable = TRUE;
            t_info.u2R = 307;
            t_info.u2G = 307;
            t_info.u2B = 307;
            break;
        case 4:     // 40%
            t_info.bEnable = TRUE;
            t_info.u2R = 409;
            t_info.u2G = 409;
            t_info.u2B = 409;
            break;
        case 5:     // 50%
            t_info.bEnable = TRUE;
            t_info.u2R = 512;
            t_info.u2G = 512;
            t_info.u2B = 512;
            break;
        case 6:     // 60%
            t_info.bEnable = TRUE;
            t_info.u2R = 614;
            t_info.u2G = 614;
            t_info.u2B = 614;
            break;
        case 7:     // 70%
            t_info.bEnable = TRUE;
            t_info.u2R = 716;
            t_info.u2G = 716;
            t_info.u2B = 716;
            break;
        case 8:     // 80%
            t_info.bEnable = TRUE;
            t_info.u2R = 819;
            t_info.u2G = 819;
            t_info.u2B = 819;
            break;
        case 9:     // 90%
            t_info.bEnable = TRUE;
            t_info.u2R = 921;
            t_info.u2G = 921;
            t_info.u2B = 921;
            break;
        case 10:     // 100%
            t_info.bEnable = TRUE;
            t_info.u2R = 1023;
            t_info.u2G = 1023;
            t_info.u2B = 1023;
            break;
        default:
            break;
    }

    i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
    
    return i4_ret;
}

extern INT32 a_cfg_custom_Set_Internal_RGB_Pattern_OnOff(BOOL bOnOff)  //Ben 20190125
{
    #if 0
    INT32	i4_ret;
    DRV_CUST_OPERATION_INFO_T	  t_op_info;
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(bOnOff);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_GAMMA_RGB_ONOFF;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&bOnOff;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE; 

    /* set to driver */
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_size_drv
                            );

    if (i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    #else
    INT32 i4_ret;
    ACFG_TYPE_SET_RGB_T t_info;

    a_cfg_cust_drv_set_pq_bypass(bOnOff);
    
    t_info.bEnable = (bOnOff == 0?FALSE:TRUE);
    if(t_info.bEnable == TRUE)
    {
        t_info.u2R = 512;
        t_info.u2G = 512;
        t_info.u2B = 512;
    }
    else
    {
        #if 1  //temp solution
        //before off the pattern, it need to set 0 at first.
        t_info.bEnable = TRUE; //(ui2_pattern == 0?FALSE:TRUE);
        t_info.u2R = 0;
        t_info.u2G = 0;
        t_info.u2B = 0;

        i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
        TPV_LOG_ON_FAIL(i4_ret);

        t_info.bEnable = FALSE;
        #endif
        
        t_info.u2R = 0;
        t_info.u2G = 0;
        t_info.u2B = 0;
    }
    //Printf("\033[01;31m [TPV_FAC] \033[m t_info.bEnable = %d\n", t_info.bEnable);
    //Printf("\033[01;31m [TPV_FAC] \033[m R:%d, G:%d, B:%d\n", t_info.u2R, t_info.u2G, t_info.u2B);

    i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_INFO(("!!!!%s : TPV_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_GAMMA_ON_OFF fail\n", __func__));
        return i4_ret;
    }
    #endif
    return RMR_OK;
}
//ke_vizio_20190320
extern INT32 a_cfg_custom_get_RGB_output_status(UINT16 ui2_x_pos, UINT16 ui2_y_pos, UINT16 *pui2_RGB)
{
    INT32 i4_ret = 0;
    UINT16 ui2_data[5] = {0};
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(ui2_data);

    ui2_data[0] = ui2_x_pos;
    ui2_data[1] = ui2_y_pos;

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_DRV_RGB_OUPTUT_STATUS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)ui2_data;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
    
    /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }

    *pui2_RGB = ui2_data[2];
    *(pui2_RGB+1) = ui2_data[3];
    *(pui2_RGB+2) = ui2_data[4];
    
    return RMR_OK;
}

extern INT32 a_cfg_custom_get_HDMI_color_dep(UINT8* ui1_color_dep)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(ui1_color_dep);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDMI_COLOR_DEPTH;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)ui1_color_dep;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;
    
    /* get from driver */
    i4_ret = c_rm_get_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info,
                        &z_size_drv
                        );
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("%s i4_ret : %d\n", __func__, i4_ret));
        return i4_ret;
    }
    
    return RMR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_fac_sif_x_read
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 a_cfg_fac_sif_x_read(UINT8 u1CHannelID, UINT16 u2ClkDiv, UINT8 u1DevAddr, INT8 u1WordAddrNum, 
                                    UINT32 u4WordAddr, UINT8 *pu1Buf, UINT16 u2ByteCnt)
{
#ifdef NEVER
    DRV_CUST_OPERATION_INFO_T t_op_info;
    MISC_TYPE_SIF_ADVANCED_T t_get_info;
    SIZE_T  z_info_size = sizeof(t_op_info);
    SIZE_T  z_size = sizeof(MISC_TYPE_SIF_ADVANCED_T);
    INT32 i4_ret;

    t_get_info.ui1_channel = u1CHannelID;
    t_get_info.ui2_clkdiv = u2ClkDiv;
    t_get_info.ui4_addr = (UINT32)u1DevAddr;
    t_get_info.ui1_offset_len = u1WordAddrNum;
    t_get_info.ui4_offset = u4WordAddr;
    t_get_info.ui1_data_len =(UINT8)u2ByteCnt;
    t_get_info.pui1_data = pu1Buf;

    
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_OPERATION_TYPE_SIF_READ;
    t_op_info.u.t_vid_set_info.b_store = FALSE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&t_get_info;
    t_op_info.u.t_vid_set_info.z_size = z_size;

    i4_ret = c_rm_set_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_info_size);

    if ( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_get_comp fail\n", __func__));
        return i4_ret;
    }
#endif /* NEVER */

    return RMR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_fac_sif_x_write
 * Description:
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 a_cfg_fac_sif_x_write(UINT8 u1CHannelID, UINT16 u2ClkDiv, UINT8 u1DevAddr, INT8 u1WordAddrNum, 
                                    UINT32 u4WordAddr, UINT8 *pu1Buf, UINT16 u2ByteCnt)
{
#ifdef NEVER
    DRV_CUST_OPERATION_INFO_T t_op_info;
    MISC_TYPE_SIF_ADVANCED_T t_get_info;
    SIZE_T  z_info_size = sizeof(t_op_info);
    SIZE_T  z_size = sizeof(MISC_TYPE_SIF_ADVANCED_T);
    INT32 i4_ret;

    t_get_info.ui1_channel = u1CHannelID;
    t_get_info.ui2_clkdiv = u2ClkDiv;
    t_get_info.ui4_addr = (UINT32)u1DevAddr;
    t_get_info.ui1_offset_len = u1WordAddrNum;
    t_get_info.ui4_offset = u4WordAddr;
    t_get_info.ui1_data_len =(UINT8)u2ByteCnt;
    t_get_info.pui1_data = pu1Buf;

    
    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_OPERATION_TYPE_SIF_WRITE;
    t_op_info.u.t_vid_set_info.b_store = FALSE;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)&t_get_info;
    t_op_info.u.t_vid_set_info.z_size = z_size;

    i4_ret = c_rm_set_comp( DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            z_info_size);

    if ( i4_ret != RMR_OK )
    {
        DBG_LOG_PRINT(("!!!!%s c_rm_set_comp fail\n", __func__));
        return i4_ret;
    }
#endif /* NEVER */

    return RMR_OK;
    
}

