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
#include "app_util/config/acfg_cust_plf_opt.h"

#include "nav/fav_lst/a_fav_lst.h"
//#include "factory/a_factory.h"
#include "agent/a_agent.h"

#include "app_util/config/acfg_cust_factory_vizio.h"
#include "Foxconn_d_factory.h"
//Tommy 20191009  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#include "intertaca_api.h"
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//Tommy 20191009  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
extern INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);
extern INT32 a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);

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
#ifdef APP_FAC_TUNER_SELECTION //sam 091229
           ui2_i == IDX_CUST_FAC_TUNER_TYPE ||
#endif
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

    /* Overwrite the Color gain/offset by Foxconn default value */
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
        DBG_INFO(("!!!!%s fail i4_ret : 0x%x \n", __func__, i4_ret));
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
    INT32						i4_ret;
    DRV_CUST_OPERATION_INFO_T	t_op_info;
    SIZE_T						z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T						z_size = sizeof(ui4_model_index);
    
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
* Name Foxconn_d_get_RJ45_addr
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 Foxconn_d_get_RJ45_addr(UINT32 *pui4_mac_addr) //ke_vizio_20160428
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
#ifndef MST_HDCP		//Tommy 20191009
    UINT8 ui1_key_buffer[HDCP2x_MAX_LEN] = {0};
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
//Tommy 20191009  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#else
	UINT8 	ui1_key_buffer[HDCP2x_MAX_LEN] = {0};
	CHAR    s_filename_reserve[512 + 64] = {0};
	INT32   i4_ret = 0;  

	SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);
	struct stat st = {0};
	FILE *pFile2;
	size_t z_size_wirte = 0;
    
    c_memcpy(ui1_key_buffer, pui1_key, z_size);

    i4_ret=TEEC_Key2TA("8", 1, ui1_key_buffer, sizeof(ui1_key_buffer));
    Foxconn_LOG_ON_FAIL(i4_ret);
    
	c_sprintf(s_filename_reserve, Foxconn_HDCP_PATH_BACKUP"%s", Foxconn_HDCP2x_FILENAME);
	DBG_LOG_PRINT(("HDCP 2.X backup path : %s", s_filename_reserve));


	if (stat(Foxconn_HDCP_PATH_BACKUP, &st) == -1) {
		mkdir(Foxconn_HDCP_PATH_BACKUP, S_IRWXU);
	}
    
    // Key backup
	pFile2 = fopen(s_filename_reserve,"wb");
	if(pFile2 == NULL){
		DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename_reserve));
		i4_ret = -1;
	}
	else
	{
		z_size_wirte = fwrite(ui1_key_buffer,1,sizeof(ui1_key_buffer),pFile2);
		DBG_LOG_PRINT(("HDCP 2.X wirte : %d\n", z_size_wirte));
		fclose(pFile2);
	}
    
#endif
 //Tommy 20191009  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
   
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
#ifndef MST_HDCP		//Tommy 20191009
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
    
#if 0	//def MST_HDCP		//Tommy 20191009
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
#elif 1
    UINT8 _au1HDCP[] = 
    {
#if 1 //Foxconn Test
		0xE8, 0xE2, 0xC7, 0x93, 0xC4, 0x00, 0xA9, 0x5A, 0x57, 0x90, 0x7A, 0xA0, 0x96, 0x6C, 0x5D, 0x6F,
		0x7A, 0x4E, 0x0D, 0xF5, 0x1F, 0xE8, 0x98, 0xA4, 0x24, 0xCD, 0x1F, 0x3D, 0x01, 0x94, 0x2C, 0x4D,
		0xFA, 0xB7, 0x1D, 0x84, 0x9C, 0x4D, 0xA9, 0xE2, 0xC2, 0x45, 0xF6, 0x95, 0x04, 0xAD, 0xE2, 0x44,
		0x09, 0xC3, 0xBD, 0xCE, 0x06, 0x85, 0x3B, 0xE1, 0x8A, 0xD4, 0x6F, 0x5A, 0xF5, 0xD8, 0x9E, 0x2A,
		0xC5, 0xA7, 0x65, 0x59, 0xF1, 0x03, 0x65, 0x6F, 0x10, 0x73, 0xAE, 0x47, 0x38, 0x6E, 0xA8, 0xEE,
		0x00, 0x3C, 0x9D, 0x79, 0xE2, 0x51, 0x6E, 0x3A, 0x9C, 0x7A, 0xB6, 0x59, 0xE1, 0x81, 0x22, 0x2B,
		0xE5, 0xD0, 0x93, 0xCC, 0x04, 0x5A, 0x03, 0xA1, 0xE1, 0x65, 0x60, 0x93, 0x82, 0xE0, 0x84, 0x64,
		0x9A, 0xAA, 0x56, 0x9E, 0xA1, 0x4A, 0x51, 0x69, 0x17, 0x83, 0xF3, 0x59, 0x5F, 0x7B, 0x80, 0x65,
		0xA0, 0xB5, 0x9F, 0x2E, 0x9F, 0x22, 0x29, 0xF0, 0x59, 0x56, 0x41, 0x93, 0x37, 0x1F, 0x5E, 0xC0,
		0x3B, 0x45, 0xFB, 0xC8, 0x1A, 0x91, 0x90, 0xD2, 0x3A, 0xB9, 0x5A, 0xC7, 0x61, 0xA1, 0x16, 0x0C,
		0x77, 0xDD, 0x98, 0x72, 0xC8, 0x59, 0x89, 0xA2, 0x7E, 0xC4, 0xB5, 0xC6, 0x08, 0x1E, 0x47, 0x5C,
		0x56, 0x8A, 0xB7, 0x51, 0x39, 0xDB, 0xE9, 0xAF, 0x63, 0x6B, 0xE2, 0x06, 0xEA, 0xA3, 0x48, 0x8A,
		0xF3, 0xB7, 0x13, 0xA3, 0xF7, 0x2A, 0x7A, 0x35, 0x61, 0xC0, 0x67, 0xA7, 0xDD, 0xA5, 0xD0, 0xCB,
		0x9A, 0x08, 0xC4, 0x46, 0x5C, 0x43, 0xF7, 0x81, 0x18, 0xB1, 0x82, 0x0E, 0x1B, 0xE7, 0x5F, 0xE7,
		0x10, 0xE0, 0x62, 0x49, 0x37, 0x2E, 0xD0, 0x7B, 0xAD, 0xCE, 0x5B, 0x73, 0x30, 0x05, 0xA5, 0x10,
		0xE4, 0xBC, 0xEE, 0x5F, 0x64, 0x9D, 0xB2, 0xBC, 0x87, 0xF8, 0x78, 0x28, 0x32, 0x6F, 0xAD, 0x2B,
		0x6A, 0xC1, 0x3B, 0xF5, 0x91, 0x51, 0x60, 0xB2, 0xDA, 0x06, 0xD8, 0x1D, 0x01, 0x59, 0x23, 0xB3,
		0x98, 0xFD, 0xF9, 0x54, 0x3B, 0xDF, 0x52, 0xE3, 0xBD, 0x4C, 0xFB, 0x95, 0x4A, 0x3E, 0xED, 0xAE,
		0x81, 0x00, 0x00, 0x02, 0x45, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

#else
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
#endif
    };

    UINT8 _au1HDCP_2X[] =
    {
#ifdef MT5691_MODEL
		0x0A, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 
		0x4D, 0x53, 0x54, 0x41, 0x52, 0x5F, 0x53, 0x45, 0x43, 0x55, 0x52, 0x45, 0x5F, 0x53, 0x54, 0x4F, 
		0x52, 0x45, 0x5F, 0x46, 0x49, 0x4C, 0x45, 0x5F, 0x4D, 0x41, 0x47, 0x49, 0x43, 0x5F, 0x49, 0x44, 
		0x4B, 0xB5, 0x0D, 0x71, 0x84, 0xFE, 0xA8, 0xAF, 0xFD, 0x01, 0x4E, 0x5D, 0xC9, 0xF1, 0xFD, 0x67, 
		0x46, 0x9C, 0xEF, 0x17, 0xED, 0xEF, 0x70, 0xE5, 0xA0, 0xC5, 0x6A, 0x9B, 0x08, 0x87, 0x43, 0x39, 
		0x5A, 0xED, 0x84, 0x45, 0x84, 0xF9, 0xFB, 0xA8, 0x08, 0x69, 0x88, 0xA1, 0x57, 0x9E, 0x3B, 0x9A, 
		0xE7, 0xF2, 0x95, 0x7C, 0xBD, 0x63, 0x97, 0xC7, 0x0C, 0x05, 0xA6, 0xD7, 0x7A, 0x17, 0xE0, 0x44, 
		0x4A, 0xE9, 0xE9, 0x7B, 0xF7, 0x25, 0xE8, 0xD1, 0x9C, 0x65, 0xF8, 0x00, 0x6F, 0x5F, 0xAA, 0xC6, 
		0xEE, 0x6D, 0x76, 0x32, 0x37, 0x25, 0x7F, 0x6A, 0x59, 0xA8, 0xFE, 0xBE, 0xBB, 0xCD, 0x81, 0x31, 
		0xF3, 0x37, 0xC1, 0x6A, 0x42, 0xA1, 0xE7, 0x50, 0x90, 0xAB, 0xB2, 0xA8, 0x4C, 0x38, 0x1B, 0x5B, 
		0x8C, 0x4D, 0xB4, 0xCD, 0x71, 0xE5, 0x0B, 0x9A, 0xF6, 0x15, 0xAA, 0x27, 0x99, 0xF9, 0xAD, 0xFB, 
		0xA8, 0x75, 0xB0, 0x75, 0xF4, 0xCF, 0x2D, 0x00, 0x16, 0x79, 0xE7, 0xE3, 0x11, 0xE9, 0xE0, 0xB7, 
		0x99, 0x24, 0xE1, 0x5B, 0xBD, 0x4E, 0xA7, 0x0D, 0x58, 0xE0, 0x03, 0xCC, 0xFB, 0x54, 0xF2, 0x0D, 
		0x5B, 0x04, 0xEA, 0x0F, 0xEC, 0xE3, 0x0B, 0x52, 0x58, 0xD4, 0xEF, 0xD6, 0xBF, 0xEB, 0x1D, 0x44, 
		0x5E, 0x89, 0x23, 0x64, 0x30, 0xAB, 0xFB, 0x2D, 0xBA, 0xDC, 0x33, 0xAD, 0x51, 0x29, 0x3A, 0xA3, 
		0x50, 0xA7, 0xFB, 0x7A, 0x04, 0xD0, 0x62, 0x1D, 0xCC, 0x81, 0xB7, 0xD7, 0xD3, 0xD1, 0x41, 0x6E, 
		0x54, 0xB8, 0x80, 0xDB, 0x94, 0xB3, 0x51, 0xE6, 0x73, 0xD9, 0x36, 0x3D, 0x37, 0x57, 0xD5, 0x66, 
		0xC0, 0x7E, 0xEE, 0x52, 0x8A, 0x0E, 0xEF, 0x04, 0xBD, 0x2A, 0x61, 0xDB, 0x55, 0xCD, 0xC1, 0x09, 
		0x70, 0x60, 0x50, 0xBF, 0x08, 0xA5, 0x36, 0xBF, 0x40, 0xB6, 0xA7, 0x80, 0x5F, 0x01, 0xF8, 0x74, 
		0x0F, 0xC2, 0x47, 0x86, 0x24, 0x5C, 0x6A, 0x12, 0x1A, 0xC6, 0xF9, 0x99, 0xB4, 0xEF, 0xDE, 0x2B, 
		0x28, 0x46, 0x7A, 0x44, 0xB7, 0x1E, 0x26, 0x78, 0x19, 0x58, 0x30, 0xE7, 0xDF, 0x20, 0x87, 0x14, 
		0xB5, 0x7C, 0xDE, 0x0A, 0x44, 0xE7, 0x73, 0xF7, 0x10, 0x8C, 0x34, 0x9C, 0xDC, 0x3A, 0xD9, 0x5F, 
		0x15, 0x6E, 0xB0, 0xB0, 0x0C, 0xA5, 0xB6, 0x3D, 0xC0, 0xB4, 0xF8, 0xCD, 0x4B, 0xBC, 0x56, 0x64, 
		0xB0, 0x88, 0x56, 0x50, 0x63, 0x8D, 0xFA, 0xD5, 0xAD, 0xB5, 0x40, 0x7A, 0x3C, 0xA8, 0x01, 0x0F, 
		0x96, 0x6E, 0x47, 0x05, 0x51, 0x7E, 0xB9, 0x87, 0x8F, 0x83, 0x54, 0x8E, 0x22, 0x01, 0x09, 0xA5, 
		0xF8, 0x9C, 0xBB, 0x14, 0xAF, 0xB9, 0x2C, 0xAB, 0x95, 0xCA, 0xA0, 0x86, 0x88, 0x52, 0xF7, 0x57, 
		0x68, 0xF1, 0x26, 0xC1, 0xEF, 0xFA, 0x10, 0x29, 0x0C, 0x13, 0x41, 0xF0, 0x50, 0x30, 0x8E, 0x1C, 
		0x03, 0x05, 0x91, 0x26, 0x40, 0x68, 0x2E, 0xB0, 0x82, 0x46, 0x64, 0xAE, 0x68, 0xB6, 0xE3, 0x7D, 
		0x36, 0xC3, 0x4A, 0xA6, 0xF9, 0x9B, 0x5F, 0x7F, 0x5B, 0x7B, 0x01, 0xF4, 0xD2, 0x10, 0x60, 0xB9, 
		0x1A, 0x01, 0xD0, 0x1E, 0x4B, 0xB3, 0xB7, 0x9B, 0xDF, 0x12, 0xBC, 0x92, 0x31, 0x65, 0xE9, 0xE2, 
		0xF0, 0xB2, 0x53, 0x71, 0x42, 0xFD, 0x4A, 0x10, 0x66, 0x8D, 0x6D, 0x79, 0x44, 0x27, 0xFF, 0x8E, 
		0x86, 0xE2, 0xD3, 0x9A, 0x24, 0xEC, 0x93, 0x31, 0x1B, 0x57, 0x69, 0x95, 0x95, 0x6A, 0xB3, 0x71, 
		0x80, 0xEB, 0x36, 0x22, 0xC1, 0xBB, 0x45, 0x3C, 0xA2, 0xFF, 0x89, 0x6C, 0xD9, 0x83, 0x32, 0xDC, 
		0xD7, 0x41, 0x1E, 0xB5, 0x86, 0xC9, 0xAA, 0xF1, 0x8A, 0xD3, 0x9C, 0x18, 0x1D, 0x79, 0x30, 0xCA, 
		0xCC, 0x31, 0xEF, 0xF8, 0x54, 0x84, 0x1E, 0xF1, 0x0D, 0x66, 0x42, 0x94, 0x82, 0x8D, 0x1E, 0xE5, 
		0xD2, 0xE0, 0x04, 0x9F, 0xD6, 0xD4, 0xEA, 0x97, 0x00, 0xFA, 0x01, 0xA1, 0xC5, 0xD9, 0x1F, 0x8C, 
		0x9E, 0x6C, 0x1A, 0x4C, 0x19, 0x6C, 0x13, 0xBA, 0xDE, 0xED, 0xA2, 0xC9, 0x5B, 0x45, 0xBF, 0x9C, 
		0x43, 0x93, 0x74, 0x74, 0x17, 0x57, 0xCF, 0x6E, 0x91, 0x65, 0xF9, 0xB1, 0xA5, 0x1A, 0x6E, 0xFE, 
		0x25, 0xC7, 0xDA, 0x77, 0x27, 0x70, 0x95, 0x7B, 0x7C, 0x19, 0x49, 0x19, 0xDA, 0x97, 0xE6, 0x30, 
		0xE7, 0x9A, 0x1B, 0x19, 0xBB, 0xD8, 0x77, 0x5A, 0x52, 0x61, 0x2A, 0x32, 0x91, 0x4E, 0x77, 0xAC, 
		0x04, 0xE3, 0xFC, 0x0C, 0x45, 0x46, 0x51, 0x1D, 0xCB, 0x15, 0x57, 0x9A, 0x43, 0xBB, 0xDE, 0x1F, 
		0x91, 0x98, 0xA6, 0x59, 0x20, 0xF5, 0x41, 0x60, 0x89, 0x2E, 0xD7, 0x24, 0xCB, 0x59, 0x29, 0xB6, 
		0x5C, 0x75, 0x83, 0x12, 0x2E, 0xB9, 0x62, 0x9F, 0xFA, 0xE6, 0x32, 0x09, 0x0F, 0xE2, 0xA8, 0xD1, 
		0x94, 0x93, 0x40, 0xA5, 0x96, 0x22, 0x1C, 0x79, 0xDB, 0x98, 0xBA, 0x0F, 0x62, 0xE7, 0xD2, 0x5A, 
		0x55, 0xF1, 0x84, 0x66, 0x92, 0xBC, 0x62, 0xBA, 0x47, 0xC2, 0x02, 0x35, 0xCB, 0x56, 0x06, 0xFD, 
		0x65, 0x92, 0x6B, 0xE1, 0x17, 0x69, 0x97, 0x8F, 0xA9, 0x39, 0xB4, 0x50, 0x75, 0xFE, 0x6A, 0x2B, 
		0xA1, 0x05, 0x5E, 0x02, 0x25, 0xA7, 0x38, 0x69, 0xFF, 0x22, 0xB7, 0xFD, 0xE0, 0x57, 0x1D, 0xC3, 
		0x96, 0x5D, 0xBA, 0xB0, 0x36, 0x4C, 0x10, 0xBF, 0x1E, 0x86, 0x81, 0x35, 0xE1, 0x90, 0xA7, 0x6A, 
		0x27, 0xE6, 0xDB, 0x8E, 0x56, 0xD6, 0x14, 0x34, 0x50, 0x12, 0x83, 0xC3, 0x51, 0x3E, 0x7A, 0x6F, 
		0x8B, 0x2E, 0xC0, 0x9C, 0x16, 0x0E, 0xFF, 0x38, 0xB6, 0x4D, 0xAB, 0x8D, 0x7A, 0xB3, 0x3B, 0xA2, 
		0x6D, 0xF3, 0x2C, 0x73, 0x77, 0x14, 0x21, 0x5C, 0x16, 0xE2, 0x32, 0x33, 0xEC, 0x8C, 0x96, 0x83, 
		0x4D, 0x94, 0xF2, 0x44, 0x14, 0xE0, 0xC2, 0x1B, 0x4C, 0x05, 0xF8, 0x14, 0xAF, 0x12, 0x1D, 0x12, 
		0x3B, 0x06, 0x14, 0x76, 0xBF, 0xCF, 0xAB, 0x50, 0x65, 0x7F, 0x0C, 0x9B, 0x67, 0xDE, 0x4C, 0x13, 
		0xBC, 0xC4, 0x5A, 0x15, 0x45, 0x54, 0x85, 0xC3, 0x4E, 0xBA, 0x65, 0x8F, 0x39, 0x3A, 0xF6, 0x39,
		0x4E, 0x1F, 0xAC, 0xF7, 0xAB, 0x0C, 0xAD, 0xE8, 0xB5, 0x0E, 0x8D, 0x2C, 0xD8, 0x73, 0x17, 0xDD, 
		0x4D, 0x83, 0xEA, 0x9F, 0x2C, 0xC0, 0xA8, 0xFE, 0xED, 0x55, 0xF7, 0x96, 0x75, 0x2E, 0xAD, 0x11, 
		0xE1, 0xC6, 0xED, 0x7E, 0x18, 0xCE, 0xE0, 0x92, 0x83, 0x2F, 0xAF, 0x36, 0xE6, 0x82, 0x23, 0x2C, 
		0xAC, 0xE0, 0x38, 0xD3, 0x6E, 0xD9, 0x4C, 0x1B, 0x90, 0x56, 0x89, 0xBD, 0xF7, 0x3A, 0xA7, 0xE1, 
		0x7C, 0x55, 0x73, 0x6A, 0xE9, 0x7A, 0xD4, 0xCD, 0x8E, 0x8B, 0xAA, 0xF7, 0x6F, 0x24, 0x51, 0x97, 
		0x52, 0xE1, 0x51, 0xC1, 0x56, 0x8E, 0xE1, 0xFC, 0x39, 0x7F, 0x44, 0x51, 0xFC, 0xE4, 0x87, 0x42, 
		0x16, 0x99, 0x60, 0x46, 0x1C, 0xAD, 0xF2, 0x9D, 0x39, 0xF6, 0xC2, 0x50, 0xF0, 0x51, 0x05, 0x70, 
		0x6A, 0x4A, 0xD3, 0xD1, 0x57, 0x13, 0xAE, 0x33, 0xDE, 0xBB, 0x94, 0x78, 0xA9, 0xC7, 0x16, 0x34, 
		0x0E, 0xE1, 0xB5, 0xA4, 0xCA, 0x82, 0x91, 0xC4, 0x57, 0xD8, 0xAF, 0x98, 0xAD, 0xFA, 0x9D, 0x96, 
		0xE3, 0xB2, 0x56, 0x1F, 0xF2, 0x33, 0x75, 0xED, 0x0E, 0x02, 0x7A, 0x98, 0x86, 0x4A, 0xB8, 0xE2, 
		0xCB, 0x27, 0xBC, 0xBD
#elif defined(MT5695_MODEL)	
        0x0a, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x4d, 0x53, 0x54, 0x41, 0x52, 0x5f, 0x53, 0x45, 0x43, 0x55, 0x52, 0x45, 0x5f, 0x53, 0x54, 0x4f,
        0x52, 0x45, 0x5f, 0x46, 0x49, 0x4c, 0x45, 0x5f, 0x4d, 0x41, 0x47, 0x49, 0x43, 0x5f, 0x49, 0x44,
		0x0f, 0xe2, 0xb9, 0xbe, 0xfb, 0xa1, 0xb7, 0x43, 0xe2, 0x56, 0x51, 0xae, 0x53, 0xe7, 0xcc, 0x2b,
		0x64, 0x4c, 0xb2, 0x1e, 0x41, 0xd4, 0x4c, 0xb5, 0x88, 0x73, 0x35, 0xd8, 0x69, 0xee, 0x76, 0x7d,
		0x63, 0xf7, 0xdb, 0x6f, 0x4e, 0xc1, 0xba, 0xee, 0x39, 0x3f, 0x3f, 0x53, 0xd5, 0x06, 0x94, 0xef,
		0xa1, 0x4a, 0x00, 0x1d, 0xc3, 0xd8, 0xa8, 0x1e, 0x6c, 0xa1, 0x8b, 0x8a, 0x87, 0xc3, 0x18, 0x7b,
		0x4a, 0x02, 0xeb, 0xe8, 0x65, 0x80, 0xc6, 0xdb, 0x54, 0xa4, 0xb7, 0xd5, 0x0a, 0x8f, 0x0f, 0x0b,
		0x5a, 0x63, 0xa7, 0x91, 0x7b, 0x74, 0xc1, 0xe7, 0xe6, 0xac, 0xdc, 0x55, 0x10, 0xf5, 0x7b, 0xa5,
		0xb3, 0xbd, 0x22, 0xe2, 0x49, 0x85, 0xdf, 0xb0, 0x1e, 0x26, 0x06, 0xa2, 0x90, 0x43, 0x40, 0xb9,
		0xfe, 0x1e, 0xfb, 0x29, 0xc3, 0xcf, 0x5f, 0xfb, 0x15, 0xe2, 0x8c, 0x3e, 0xa8, 0x4a, 0x18, 0x71,
		0x45, 0xa0, 0x4c, 0x82, 0x8a, 0x01, 0xeb, 0x5d, 0xa5, 0x38, 0x51, 0x92, 0xa6, 0x21, 0x0e, 0xca,
		0xd1, 0x3a, 0xc5, 0x62, 0x72, 0x6f, 0x9b, 0x20, 0x41, 0x62, 0x8c, 0xe7, 0x65, 0x30, 0x5a, 0x21,
		0x21, 0xc5, 0x3e, 0xa3, 0x22, 0xb0, 0x6f, 0xe1, 0xd7, 0x38, 0xf1, 0xb8, 0xc5, 0xad, 0xf4, 0x38,
		0x82, 0xd9, 0xe0, 0xa3, 0x6c, 0x89, 0x77, 0xe5, 0x89, 0xd7, 0x34, 0x91, 0x2e, 0x37, 0xb5, 0xf0,
		0xe2, 0xd3, 0x1a, 0x36, 0xed, 0xf5, 0x6d, 0x52, 0x1b, 0xbe, 0xfe, 0x9e, 0xb1, 0xd7, 0x13, 0x84,
		0x7b, 0x66, 0xf0, 0x36, 0x4f, 0x88, 0x82, 0x0d, 0x2c, 0xf0, 0x36, 0xc7, 0x4a, 0x1f, 0xc3, 0x0f,
		0xb6, 0x6a, 0x8e, 0x62, 0xca, 0x8b, 0x0d, 0x88, 0x8d, 0x90, 0x2e, 0x95, 0x7b, 0x5d, 0x27, 0x40,
		0x31, 0x6b, 0x5a, 0xc3, 0x5b, 0x84, 0xe6, 0x0c, 0x91, 0x6d, 0x21, 0xcf, 0x71, 0x48, 0xb8, 0x1e,
		0x01, 0x22, 0x84, 0x93, 0x6a, 0x74, 0x2d, 0x23, 0x22, 0xef, 0x4e, 0x1f, 0x37, 0xf0, 0x2b, 0x73,
		0x76, 0x64, 0xc5, 0x70, 0xb0, 0xc5, 0xc6, 0x19, 0x98, 0xba, 0xe2, 0x89, 0xf4, 0x00, 0x8d, 0x55,
		0x9b, 0x4f, 0xf3, 0x4d, 0xb6, 0xd2, 0x51, 0xd9, 0x3f, 0x4b, 0x1f, 0xa6, 0x4a, 0x01, 0xcd, 0x08,
		0x1a, 0xe4, 0x84, 0x6e, 0xdd, 0x95, 0x42, 0xdf, 0x36, 0x71, 0x4b, 0xf6, 0x78, 0xf7, 0x9d, 0x56,
		0x94, 0xd0, 0xcd, 0x1f, 0xfc, 0xdd, 0x0e, 0x18, 0x7f, 0x03, 0x30, 0x77, 0x03, 0x7f, 0x93, 0x50,
		0x24, 0xc3, 0x05, 0xc4, 0x89, 0xe6, 0x4f, 0x66, 0x59, 0xe2, 0x53, 0xdd, 0x1c, 0xfe, 0xad, 0xa9,
		0xfb, 0x3c, 0xcd, 0x2f, 0x04, 0x76, 0xf7, 0xba, 0xc4, 0x0d, 0x95, 0x5b, 0x54, 0xa9, 0x3c, 0x08,
		0x1b, 0x45, 0x68, 0x3c, 0x67, 0x72, 0x2c, 0x69, 0xc4, 0xb3, 0x59, 0xaf, 0xc9, 0xb3, 0x58, 0xdc,
		0x80, 0x2e, 0x8c, 0x09, 0xc5, 0x68, 0x20, 0x96, 0x39, 0x02, 0xf7, 0xcb, 0xd0, 0x9a, 0x92, 0xf1,
		0xca, 0x93, 0x53, 0x45, 0xc7, 0xca, 0xc6, 0xae, 0x2a, 0xda, 0xd1, 0x5b, 0x72, 0x8a, 0x02, 0x9b,
		0x10, 0xaa, 0x7a, 0x76, 0xf9, 0xf0, 0x7d, 0xdc, 0x42, 0x79, 0x38, 0x41, 0x4b, 0x63, 0x55, 0xd7,
		0x01, 0x6b, 0x22, 0xdd, 0xb3, 0x46, 0x4d, 0x15, 0x82, 0xe8, 0xec, 0xf9, 0xe8, 0x23, 0x26, 0xc3,
		0xb2, 0x0c, 0xae, 0xeb, 0xd5, 0x62, 0xac, 0xd5, 0xe0, 0x96, 0xc0, 0x2c, 0x03, 0x89, 0xad, 0xb3,
		0x45, 0x24, 0xcb, 0x9c, 0xff, 0x9f, 0xdb, 0x1d, 0x0e, 0xa5, 0x72, 0x6f, 0xa4, 0xba, 0x69, 0xa4,
		0xb2, 0x51, 0xe4, 0x94, 0x4e, 0xf0, 0x2d, 0xe8, 0xe0, 0xaa, 0xf7, 0xfd, 0x32, 0x71, 0xe0, 0x18,
		0xda, 0x1e, 0x65, 0xc6, 0x06, 0xc0, 0x74, 0x01, 0x46, 0xec, 0x48, 0x72, 0x65, 0x4a, 0x70, 0x22,
		0x0b, 0xf0, 0xa9, 0xc7, 0x56, 0x66, 0xd5, 0xeb, 0x80, 0x59, 0x4d, 0x0d, 0x4c, 0xc9, 0x03, 0xa2,
		0x0c, 0xef, 0xd5, 0x13, 0xf5, 0xeb, 0xcf, 0x29, 0x94, 0xe8, 0xe8, 0x2c, 0x2e, 0x48, 0x95, 0x7b,
		0x98, 0x37, 0xe6, 0x8c, 0xe9, 0x11, 0xac, 0x1d, 0xc9, 0xf9, 0xa1, 0x7f, 0x58, 0xc8, 0xd0, 0x70,
		0x2d, 0x8f, 0xe3, 0x34, 0x6f, 0xff, 0xd7, 0xe6, 0xb9, 0x1c, 0xa9, 0x31, 0x01, 0xc8, 0xb8, 0xff,
		0x5f, 0x27, 0x64, 0x8e, 0x7c, 0x8e, 0xb1, 0x25, 0x1f, 0xb9, 0x21, 0xaf, 0x6e, 0x0c, 0x9b, 0x4b,
		0xf8, 0x48, 0x03, 0x32, 0x4a, 0xb0, 0x65, 0xf3, 0xbc, 0x01, 0x31, 0x16, 0xd8, 0x02, 0xa4, 0xd3,
		0xd8, 0xe3, 0x0c, 0x11, 0x62, 0x56, 0xb8, 0xc8, 0xfa, 0xba, 0xc8, 0xe7, 0x03, 0x80, 0x51, 0xe6,
		0xab, 0xaa, 0xca, 0x77, 0x59, 0xf5, 0xb2, 0xe1, 0xa6, 0xd9, 0xbb, 0xb6, 0xe0, 0xd8, 0x27, 0x55,
		0x2d, 0x25, 0x1f, 0x11, 0xd3, 0xa0, 0x88, 0xd9, 0xbf, 0x3c, 0x44, 0x2b, 0x4e, 0x25, 0xda, 0x9a,
		0x9b, 0xce, 0x2a, 0x1b, 0x3d, 0x9a, 0x9f, 0x95, 0xc1, 0x5c, 0x86, 0x82, 0x29, 0x46, 0x2c, 0x89,
		0x95, 0x6a, 0x0d, 0xc5, 0x29, 0xbc, 0xc4, 0xed, 0xb6, 0xbb, 0x4e, 0xf0, 0xc8, 0xd2, 0xe4, 0x78,
		0x0e, 0x1f, 0x0a, 0x36, 0xbb, 0x02, 0x87, 0x83, 0xc1, 0x28, 0xf9, 0x22, 0x70, 0xbe, 0x48, 0xfb,
		0x21, 0xa9, 0x18, 0x21, 0x8c, 0x6c, 0x9a, 0x44, 0xa1, 0x15, 0x24, 0xd4, 0x19, 0x02, 0xf5, 0x80,
		0x79, 0xdb, 0x54, 0x1b, 0x54, 0x3d, 0x45, 0x47, 0x57, 0xcf, 0x9f, 0xbe, 0xd6, 0xfa, 0xde, 0xe8,
		0x1f, 0x2b, 0x01, 0x5d, 0x80, 0x49, 0x0c, 0x24, 0x17, 0x0b, 0x88, 0x49, 0xe1, 0x70, 0x93, 0x1e,
		0x87, 0x9e, 0xee, 0x79, 0xa7, 0xd8, 0xc5, 0xa0, 0xcb, 0x49, 0x4f, 0x10, 0xd6, 0x5d, 0x7a, 0x50,
		0xde, 0x7f, 0xad, 0xa2, 0xb0, 0x5c, 0xf4, 0x9b, 0xb5, 0x58, 0x94, 0xf2, 0x53, 0xd4, 0x59, 0x87,
		0x6d, 0xc1, 0x8f, 0xf5, 0x1a, 0x67, 0xad, 0xd6, 0x42, 0xaa, 0x9f, 0x39, 0x6a, 0xd0, 0x8b, 0xb8,
		0x68, 0xf4, 0x7e, 0x59, 0xaf, 0x21, 0x0f, 0x5e, 0xec, 0xdf, 0x98, 0x37, 0x85, 0x97, 0xe4, 0xa1,
		0x14, 0x0e, 0x2d, 0xe2, 0xb5, 0xbf, 0x70, 0x21, 0x58, 0x5d, 0x67, 0x6a, 0x8c, 0x72, 0xc9, 0xd3,
		0x7f, 0x75, 0xee, 0xbe, 0x1e, 0x66, 0x4a, 0xa6, 0x86, 0xb1, 0xf5, 0x3c, 0x04, 0x4c, 0xfc, 0xb4,
		0xbe, 0xc8, 0x78, 0x81, 0x6a, 0x48, 0x1c, 0xa1, 0xcc, 0xe8, 0xfb, 0x4b, 0x5b, 0x73, 0x4e, 0x11,
		0x79, 0xd8, 0x6a, 0xee, 0xc3, 0xc9, 0x94, 0x5e, 0x77, 0xc1, 0xb1, 0x17, 0xed, 0x99, 0x39, 0x92,
		0xaa, 0x9c, 0xd0, 0x6b, 0xaa, 0x1d, 0xc7, 0x45, 0x7e, 0x98, 0xc8, 0xda, 0x7b, 0xac, 0xf4, 0xe7,
		0x41, 0x04, 0x3a, 0x73, 0x80, 0x84, 0x58, 0x73, 0x2f, 0x15, 0xea, 0x4c, 0x65, 0x07, 0x9c, 0x8b,
		0x71, 0x99, 0x38, 0xac, 0x85, 0x00, 0x36, 0x5b, 0x8f, 0x9d, 0xaf, 0x1e, 0xa8, 0x94, 0xc7, 0x19,
		0x18, 0xcc, 0xf5, 0x83, 0x25, 0x52, 0x08, 0x9b, 0x7b, 0x7f, 0x59, 0xde, 0x55, 0xe3, 0xa0, 0x5d,
		0x4b, 0x12, 0x2d, 0x2e, 0x2c, 0xae, 0x91, 0x35, 0x54, 0x1d, 0xec, 0xfd, 0x6a, 0x34, 0x73, 0xe9,
		0x6c, 0xf4, 0xc9, 0x70, 0x75, 0x53, 0x86, 0xb1, 0x14, 0xc1, 0x80, 0x1f, 0xf6, 0x3d, 0xdc, 0x36,
		0xcf, 0x59, 0xc2, 0x27
#endif
    };
    
    DBG_LOG_PRINT(("\n %s Line: %d\n", __FUNCTION__, __LINE__));
    #if 0
    i4_ret=TEEC_SetIniPath("/vendor/tvconfig/config/foxconn/ModelGroup304/ModelIndex1/drm/");
    Foxconn_LOG_ON_FAIL(i4_ret);
    i4_ret=TEEC_SendData2TA("8", 1);  //HDCP 2.X
    Foxconn_LOG_ON_FAIL(i4_ret);
    #endif

    i4_ret=TEEC_Key2TA("8", 1, _au1HDCP_2X, sizeof(_au1HDCP_2X));
    Foxconn_LOG_ON_FAIL(i4_ret);
    
    i4_ret=TEEC_Key2TA("21", 0, _au1HDCP, sizeof(_au1HDCP));
    Foxconn_LOG_ON_FAIL(i4_ret);
//	i4_ret=TEEC_SendData2TA("21", 0); //HDCP 1.X
//	Foxconn_LOG_ON_FAIL(i4_ret);
    
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
#ifndef MST_HDCP		//Tommy 20191009
    UINT8 ui1_key_buffer[HDCP1x_MAX_LEN] = {0};
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
//Tommy 20191009  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#else
    CHAR ui1_key_buffer[HDCP1x_MAX_LEN] = {0};
//    CHAR    s_filename[512 + 64] = {0};
    CHAR    s_filename_reserve[512 + 64] = {0};
    INT32   i4_ret = 0;  
    SIZE_T z_size = sizeof(ui1_key_buffer)/sizeof(ui1_key_buffer[0]);
    struct stat st = {0};
    FILE *pFile2;
    size_t z_size_wirte = 0;
    c_memcpy(ui1_key_buffer, pui1_key, z_size);
	
    i4_ret=TEEC_Key2TA("21", 0, ui1_key_buffer, sizeof(ui1_key_buffer));
    Foxconn_LOG_ON_FAIL(i4_ret);
    
    c_sprintf(s_filename_reserve, Foxconn_HDCP_PATH_BACKUP"%s", Foxconn_HDCP1x_FILENAME);
    
    DBG_LOG_PRINT(("HDCP 1.X backup path : %s", s_filename_reserve));


    if (stat(Foxconn_HDCP_PATH_BACKUP, &st) == -1) {
        mkdir(Foxconn_HDCP_PATH_BACKUP, S_IRWXU);
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

    
#endif
 //Tommy 20191009  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
   return i4_ret;
}

#ifdef MST_HDCP		//Tommy 20191009
/*-----------------------------------------------------------------------------
* Name a_cfg_cust_odm_get_HDCP_1_X_KSV
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_odm_get_HDCP_1_X_KSV(UINT8 * pui1_key)  //Tommy 20191009
{
    UINT8 ui1_ksv_buffer[5] = {0};
    CHAR    s_filename[512 + 64] = {0};
    INT32   i4_ret = 0;  
    FILE *pFile;
    
    //c_memcpy(ui1_key_buffer, pui1_key, z_size);
    
    //c_sprintf(s_filename,"/vendor/tvconfig/config/Foxconn/ModelGroup192/ModelIndex1/hdcp/hdcp_key.bin");
    c_sprintf(s_filename, Foxconn_HDCP_PATH_BACKUP"%s", Foxconn_HDCP1x_FILENAME); //colby@191204
    DBG_LOG_PRINT(("HDCP 1.X path : %s", s_filename));

    pFile = fopen(s_filename,"rb" );
    if(pFile == NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
        i4_ret = APP_CFGR_CANT_INIT;
        return i4_ret;
    }
    else
    {
        fseek(pFile, SEEK_SET, 0);
        i4_ret = fread((void *)ui1_ksv_buffer, sizeof(ui1_ksv_buffer), 1, pFile);
		if (i4_ret != 1) //Tommy 20200110
			i4_ret = APP_CFGR_NO_ACTION;
		else
			i4_ret = APP_CFGR_OK;
        DBG_LOG_PRINT(("HDCP 1.X read : %d\n", i4_ret));
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
extern INT32 a_cfg_cust_odm_get_HDCP_2_X_RECEIVE_ID(UINT8 * pui1_key) //Tommy 20191009
{
    UINT8 ui1_ksv_buffer[5] = {0};
    CHAR    s_filename[512 + 64] = {0};
    INT32   i4_ret = APP_CFGR_OK;  
    FILE *pFile;
    
    //c_memcpy(ui1_key_buffer, pui1_key, z_size);
    
    //c_sprintf(s_filename,"/vendor/tvconfig/config/Foxconn/ModelGroup192/ModelIndex1/hdcp/hdcp_key.bin");
    c_sprintf(s_filename, Foxconn_HDCP_PATH_BACKUP"%s", Foxconn_HDCP2x_FILENAME); //colby@191204
    DBG_LOG_PRINT(("HDCP 2.X path : %s", s_filename));

    pFile = fopen(s_filename,"rb" );
    if(pFile == NULL){
        DBG_LOG_PRINT(("fopen Can't open : %s\n", s_filename));
        i4_ret = -1;
        return APP_CFGR_CANT_INIT;
    }
    else
    {
        fseek(pFile, SEEK_SET, 0);
        i4_ret = fread((void *)ui1_ksv_buffer, sizeof(ui1_ksv_buffer), 1, pFile);
		if (i4_ret != 1) //Tommy 20200110
			i4_ret = APP_CFGR_NO_ACTION;
		else
			i4_ret = APP_CFGR_OK;
        DBG_LOG_PRINT(("HDCP 2.X read : %d\n", i4_ret));
        fclose(pFile);
    }
    
    c_memcpy(pui1_key, ui1_ksv_buffer, sizeof(ui1_ksv_buffer));
    
    return i4_ret;
}
#endif
/*-----------------------------------------------------------------------------
* Name a_cfg_cust_odm_get_HDCP
* Description
* Input arguments :ui_type , pui1_key
*   ui_type:HDCP type 0:1.4 1:2.x , *pui1_key :data buffer
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_odm_get_HDCP(UINT8 ui_type,UINT8 * pui1_key) //colby@191204
{
    UINT16 ui2_filelen = 0;
    CHAR    s_file[128] = {0};
    INT32   i4_ret = APP_CFGR_OK;  
    FILE *pFile;

    if(ui_type==0)  /* HDCP 1.x */
        c_sprintf(s_file, Foxconn_HDCP_PATH_BACKUP"%s", Foxconn_HDCP1x_FILENAME);
    else            /* HDCP 2.x */
        c_sprintf(s_file, Foxconn_HDCP_PATH_BACKUP"%s", Foxconn_HDCP2x_FILENAME);

    DBG_LOG_PRINT(("a_cfg_cust_odm_get_HDCP path : %s \n", s_file));

    pFile = fopen(s_file,"rb" );
   
    if(pFile == NULL)
	{
        DBG_LOG_PRINT(("fopen Can't open HDCP file: %s\n", s_file));
        i4_ret = APP_CFGR_CANT_INIT;
    }
    else
    {
        fseek(pFile,0,SEEK_END); //get file size
        ui2_filelen=ftell(pFile);

        DBG_LOG_PRINT(("ui2_filelen:= %d \n", ui2_filelen));

        if(((ui_type==0)&&(ui2_filelen==HDCP1x_MAX_LEN))||
            ((ui_type==1)&&(ui2_filelen==HDCP2x_MAX_LEN)))
        {
            fseek(pFile, SEEK_SET, 0);
			if (fread(pui1_key, ui2_filelen, 1, pFile)) //colby@191220
				i4_ret = APP_CFGR_OK;
			else
				i4_ret = APP_CFGR_NO_ACTION;
        }
		else
           i4_ret = APP_CFGR_CANT_INIT;

        DBG_LOG_PRINT(("HDCP read Result: %d\n", i4_ret));
        fclose(pFile);
    }
    
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name a_cfg_cust_odm_get_HDMI_EDID
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_odm_get_HDMI_EDID(UINT8 model_idx,UINT8 ui_port,UINT8 * pui1_key) //colby@20191216
{
    UINT16 ui2_filelen = 0;
    CHAR    s_file[128] = {0};
    INT32   i4_ret = APP_CFGR_OK;  
    FILE *pFile;

#if defined(MT5691_MODEL)
    if ((model_idx >= 6) && (model_idx <= 9))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V605H3_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V605H3_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V605H3_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 10) && (model_idx <= 13))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M706xH3_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M706xH3_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M706xH3_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 14) && (model_idx <= 17))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705xH3_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705xH3_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705xH3_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 18) && (model_idx <= 21))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V706J03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V706J03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V706J03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 22) && (model_idx <= 25))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705J03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705J03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705J03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 26) && (model_idx <= 29))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q7J03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q7J03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q7J03_EDID3_FILENAME);
                break;

            case 0x03:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q7J03_EDID4_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 30) && (model_idx <= 33))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V756J03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V756J03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V756J03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 34) && (model_idx <= 37))	//Tommy 20200619 //update WT 20200724
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q7J03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q7J03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q7J03_EDID3_FILENAME);
                break;

            case 0x03:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q7J03_EDID4_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 38) && (model_idx <= 41))	//Tommy 20200619  //WT@@ 20201106
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V706xJ03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V706xJ03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V706xJ03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 42) && (model_idx <= 45))	//Tommy 20200619 //WT@20201106
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V756xJ03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V756xJ03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V756xJ03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 46) && (model_idx <= 49))	//WT 20201207
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6J03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6J03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6J03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 50) && (model_idx <= 53))	//WT 20201207
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6J03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6J03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6J03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }	
    else if ((model_idx >= 54) && (model_idx <= 57))	//WT 20210409
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705GOAJ03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705GOAJ03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705GOAJ03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 58) && (model_idx <= 61))	//WT 20210526
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705MK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705MK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705MK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }		
    else if ((model_idx >= 62) && (model_idx <= 65))	//WT 20210526
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V755MK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V755MK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V755MK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 66) && (model_idx <= 69))	//WT 20210607
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V655MK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V655MK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V655MK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 70) && (model_idx <= 73))	//WT 20210607
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6MK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6MK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6MK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 74) && (model_idx <= 77))	//WT 20210607
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6MK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6MK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6MK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 78) && (model_idx <= 81))	//WT 20210730
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705PK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705PK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705PK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }		
    else if ((model_idx >= 82) && (model_idx <= 85))	//WT 20210730
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V755PK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V755PK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V755PK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 86) && (model_idx <= 89))	//WT 20210730
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V655PK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V655PK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V655PK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 90) && (model_idx <= 93))	//WT 20210730
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6MK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6MK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70Q6MK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 94) && (model_idx <= 97))	//WT 20210730
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6MK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6MK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75Q6MK03_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
	else
	{
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705H3_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705H3_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", V705H3_EDID3_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
#elif defined(MT5695_MODEL)	
    if ((model_idx >= 6) && (model_idx <= 9))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70QXMK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70QXMK03_EDID1_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70QXMK03_EDID1_FILENAME);
                break;

            case 0x03:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M70QXMK03_EDID4_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 10) && (model_idx <= 13))	//Tommy 20200619
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M65QXMK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M65QXMK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M65QXMK03_EDID3_FILENAME);
                break;

            case 0x03:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M65QXMK03_EDID4_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }
    else if ((model_idx >= 14) && (model_idx <= 17))	//WT @20210817
    {
        switch(ui_port)
        {
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M65QXPK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M65QXPK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M65QXPK03_EDID3_FILENAME);
                break;

            case 0x03:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M65QXPK03_EDID4_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
        }
    }	
	else
	{
		switch(ui_port)
		{
            case 0x00:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75QXMK03_EDID1_FILENAME);
                break;

            case 0x01:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75QXMK03_EDID2_FILENAME);
                break;

            case 0x02:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75QXMK03_EDID3_FILENAME);
                break;

            case 0x03:
                c_sprintf(s_file, Foxconn_EDID_PATH"%s", M75QXMK03_EDID4_FILENAME);
                break;

            default:
                i4_ret = -1;
                return i4_ret;
		}
	}
#endif			

    DBG_LOG_PRINT(("a_cfg_cust_odm_get_HDMI_EDID path : %s \n", s_file)); //colby@191220

    pFile = fopen(s_file,"rb" );
   
    if(pFile == NULL){
        DBG_LOG_PRINT(("fopen Can't open HDMI_EDID: %s\n", s_file));
        i4_ret = -1;
        return i4_ret;
    }
    else
    {
        fseek(pFile,0,SEEK_END); //get file size
        ui2_filelen=ftell(pFile);

        if(ui2_filelen==256)
        {
            fseek(pFile, SEEK_SET, 0);
            i4_ret=fread(pui1_key, ui2_filelen, 1, pFile); //colby@191220
	        fclose(pFile);
			if (i4_ret != 1) //Tommy 20200110
				i4_ret = APP_CFGR_NO_ACTION;
			else
				i4_ret = APP_CFGR_OK;
        }
        else if(ui2_filelen==512)//WT@20210122
        {
            fseek(pFile, SEEK_SET, 0);
            i4_ret=fread(pui1_key, ui2_filelen, 1, pFile); //colby@191220
	        fclose(pFile);
			if (i4_ret != 1) //Tommy 20200110
				i4_ret = APP_CFGR_NO_ACTION;
			else
				i4_ret = APP_CFGR_OK;
        }		
		else
           i4_ret = APP_CFGR_CANT_INIT;

		DBG_LOG_PRINT(("HDMI_EDID read Result: %d\n", i4_ret));
    }
    
    return i4_ret;

}

/*-----------------------------------------------------------------------------
* Name a_cfg_custom_set_HDR_panel_nits
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
#ifdef FAC_PANEL_NITS		//Tommy 20191009
extern INT32 a_cfg_custom_set_HDR_panel_nits(UINT32 u2Panelnist)   //Tommy 20191009 //Ben 20171113
#else
extern VOID a_cfg_custom_set_HDR_panel_nits(UINT32 u2Panelnist)  //Ben 20171113
#endif
{
	INT32	i4_ret;
	DRV_CUST_OPERATION_INFO_T	  t_op_info;
	SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	SIZE_T z_size = sizeof(u2Panelnist);
	
	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
	t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_SET_HDR_PANEL_NITS;
	t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&u2Panelnist;
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

#ifdef MST_HDCP		//Tommy 20191009
    return i4_ret;
#endif
}

#ifdef FAC_PANEL_NITS		//Tommy 20191009
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_get_HDR_panel_nits
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_get_HDR_panel_nits(UINT16 *u2Panelnist)  //Tommy 20191009 // Ben 20180629
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(u2Panelnist);
    

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_HDR_PANEL_NITS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)u2Panelnist;
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
    }

    return i4_ret;
}
#endif

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

//Tommy 20191009  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
#if 1		//Tommy 20191009
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
#endif
#ifdef PQ_BYPASS
/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_Set_Factory_PQbypass_OnOff
* Description: enable/disable PQ bypss
* Input arguments: 0: disable, 1: enable
* Output arguments: N/A
* Returns: N/A
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_Set_Factory_PQbypass_OnOff(BOOL bOnOff)  //Ben 20180416
{
	INT32						i4_ret=0;
	DBG_LOG_PRINT(("Tommy Test a_cfg_custom_Set_Factory_PQbypass_OnOff uOnOff = 0x%X \n", bOnOff));
#if 1
	DRV_CUSTOM_PQ_BYPASS_T t_info;
	c_memset(&t_info, 0, sizeof(t_info));
	
	if(bOnOff)
	{
		t_info.bEnable = TRUE;
	}
	else
	{
		t_info.bEnable = FALSE;
	}
	t_info.u4Val = 0x7FF; //Only Panel Gamma no bypass
	
	
	i4_ret = a_cfg_cust_drv_set_pq_bypass_ex(&t_info,sizeof(t_info));
	DBG_LOG_PRINT(("[Foxconn_d_factory.c] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

#else
	CUST_SPEC_TYPE_SET_INFO_T	t_cust_set_info = {0};
	SIZE_T						z_size = sizeof(UINT16);
	UINT16						uOnOff = (UINT16)bOnOff;


	t_cust_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_VID_PQ_ALL_ONOFF;
	t_cust_set_info.pv_set_info = (VOID *)&uOnOff;
	t_cust_set_info.z_size = z_size;
	t_cust_set_info.b_store = TRUE;

	DBG_LOG_PRINT(("Tommy Test a_cfg_custom_Set_Factory_PQbypass_OnOff t_cust_set_info.pv_set_info = 0x%X \n", *(UINT16 *)t_cust_set_info.pv_set_info));


	i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_cust_set_info);

	if ( i4_ret != RMR_OK )
	{
		DBG_LOG_PRINT(("!!!!%s a_cfg_custom_Set_Factory_PQbypass_OnOff fail\n", __func__));
	}
#endif
	return i4_ret;
}
#endif
//Tommy 20191009 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

#if 0 //libfactory4.so build error 
//Tommy 20180312
extern UINT32 a_cfg_custom_get_cur_model_status(CHAR *s_model_status)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T                      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);

    CHAR s_status[16]= {0};
    SIZE_T      z_size = sizeof(s_status);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_MODEL_STATUS;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)s_status;
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
    c_strncpy(s_model_status, s_status, 16);
    return i4_ret;
}
#endif //libfactory4.so build error 
//Foxconn Tommy 20180326 ADD
extern UINT32 a_cfg_custom_get_cur_keypad_adc(UINT32 *pui4_keypad_status)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T	t_op_info={0};
    SIZE_T						z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T						z_size = sizeof(pui4_keypad_status);

	DBG_LOG_PRINT(("Tommy a_cfg_custom_get_cur_keypad_adc.... \n")); //colby@191220
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_KEYPAD_ADC;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_keypad_status;
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
    }

    return i4_ret;
}

//Foxconn Tommy 20180329 ADD
extern UINT32 a_cfg_custom_get_cur_keypad_power(UINT32 *pui4_keypad_status)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T	t_op_info={0};
    SIZE_T						z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T						z_size = sizeof(pui4_keypad_status);

	DBG_LOG_PRINT(("Tommy a_cfg_custom_get_cur_keypad_adc.... \n")); //colby@191220
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_KEYPAD_POWER;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_keypad_status;
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
    }

    return i4_ret;
}

extern INT32 a_cfg_custom_Set_Lcdim_Scrolling_OnOff(BOOL bOnOff)  //Add FXC_WT@@2018504 From Ben 20180413
{
	CUST_SPEC_TYPE_SET_INFO_T	t_cust_set_info = {0};
	INT32						i4_ret=0;
    UINT32						u4ScrollingParam;
	SIZE_T						z_size = sizeof(u4ScrollingParam);


    if (bOnOff == TRUE)
        u4ScrollingParam = 0x10000FFF; // bit-0~3 light level, bit-7 on/off
    else
        u4ScrollingParam = 0x00000FFF; // bit-0~3 light level, bit-7 on/off

	t_cust_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_LDM_SCROLLING_FUN;
	t_cust_set_info.pv_set_info = (VOID *)&u4ScrollingParam;
	t_cust_set_info.z_size = z_size;
	t_cust_set_info.b_store = TRUE;

	DBG_LOG_PRINT(("Tommy Test a_cfg_custom_Set_Lcdim_Scrolling_OnOff t_cust_set_info.pv_set_info = 0x%X \n", *(UINT32 *)t_cust_set_info.pv_set_info));


	i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_cust_set_info);

	if ( i4_ret != RMR_OK )
	{
		DBG_LOG_PRINT(("!!!!%s a_cfg_custom_Set_Lcdim_Scrolling_OnOff fail\n", __func__));
	}
	return i4_ret;

}
//Tommy 20191009 vvvvvvvvvvvvvvvvvvvvvvvvvvvv
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
        Foxconn_LOG_ON_FAIL(i4_ret);

        t_info.bEnable = FALSE;
        #endif
        
        t_info.u2R = 0;
        t_info.u2G = 0;
        t_info.u2B = 0;
    }
    //Printf("\033[01;31m [Foxconn_FAC] \033[m t_info.bEnable = %d\n", t_info.bEnable);
    //Printf("\033[01;31m [Foxconn_FAC] \033[m R:%d, G:%d, B:%d\n", t_info.u2R, t_info.u2G, t_info.u2B);

    i4_ret = a_cfg_cust_set_rgb_pattern(&t_info,sizeof(t_info));
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_INFO(("!!!!%s : Foxconn_FACTORY_SET_CMD_SET_INTERNAL_PATTERN_GAMMA_ON_OFF fail\n", __func__));
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
#if 1
extern INT32 a_cfg_cust_drv_set_vcom_pattern(VOID* pv_data, SIZE_T z_size_val)
{
    INT32 i4_ret = 0;
    DRV_CUST_OPERATION_INFO_T t_op_info = {0};
	int i;

    if(pv_data == NULL )
    {
		DBG_LOG_PRINT(("[ACFG] a_cfg_cust_drv_set_vcom_pattern is NULL at %s \r\n",__func__));
        return RMR_NOT_INIT;
    }

    c_memset (&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_VID_SET;
    t_op_info.u.t_vid_set_info.e_vid_type = DRV_CUSTOM_VID_TYPE_VCOM_PATTERN;
    t_op_info.u.t_vid_set_info.pv_set_info = (VOID *)pv_data;
    t_op_info.u.t_vid_set_info.z_size = z_size_val;
    t_op_info.u.t_vid_set_info.b_store = TRUE;
	for (i = 0; i < 96; i++)
		DBG_LOG_PRINT(("t_op_info.u.t_vid_set_info.pv_set_info[%d] = %d \n ", i, (INT16 *)(t_op_info.u.t_vid_set_info.pv_set_info + i)));

    /*set value to driver*/
    i4_ret = c_rm_set_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            sizeof(DRV_CUST_OPERATION_INFO_T)
                            );

	if ( i4_ret != RMR_OK )
	    DBG_LOG_PRINT(("%s Return Fail i4_ret :%d \r\n",__func__,i4_ret));

    return i4_ret;
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
	CUST_SPEC_TYPE_GET_INFO_T t_cust_get_info = {0};
	MISC_TYPE_SIF_ADVANCED_T t_get_info;
	SIZE_T  z_size = sizeof(MISC_TYPE_SIF_ADVANCED_T);
	INT32 i4_ret = 0;
	int i;

	t_get_info.ui1_channel = u1CHannelID;
	t_get_info.ui2_clkdiv = u2ClkDiv;
	t_get_info.ui4_addr = (UINT32)u1DevAddr;
	t_get_info.ui1_offset_len = u1WordAddrNum;
	t_get_info.ui4_offset = u4WordAddr;
	t_get_info.ui1_data_len =(UINT8)u2ByteCnt;

	t_cust_get_info.e_cust_spec_type = DRV_CUSTOM_OPERATION_TYPE_SIF_READ;
	t_cust_get_info.pv_get_info = (VOID *)&t_get_info;
	t_cust_get_info.pz_size = &z_size;
	
	i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_cust_get_info);

	if ( i4_ret != RMR_OK )
	{
		DBG_LOG_PRINT(("!!!!%s a_cfg_fac_sif_x_read fail\n", __func__));
		return i4_ret;
	}
	else
	{
		for (i = 0; i < u2ByteCnt; i++)
		{
			pu1Buf[i] = t_get_info.pui1_data[i];
		}
	}
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
	CUST_SPEC_TYPE_SET_INFO_T t_cust_set_info = {0};
	MISC_TYPE_SIF_ADVANCED_T t_set_info;
	SIZE_T  z_size = sizeof(MISC_TYPE_SIF_ADVANCED_T);
	INT32 i4_ret=0;
	int i;

	t_set_info.ui1_channel = u1CHannelID;
	t_set_info.ui2_clkdiv = u2ClkDiv;
	t_set_info.ui4_addr = (UINT32)u1DevAddr;
	t_set_info.ui1_offset_len = u1WordAddrNum;
	t_set_info.ui4_offset = u4WordAddr;
	t_set_info.ui1_data_len =(UINT8)u2ByteCnt;

	t_cust_set_info.e_cust_spec_type = DRV_CUSTOM_OPERATION_TYPE_SIF_WRITE;
	t_cust_set_info.pv_set_info = (VOID *)&t_set_info;
	t_cust_set_info.z_size = z_size;
	t_cust_set_info.b_store = TRUE;

	for (i = 0; i < t_set_info.ui1_data_len ; i++)
	{
		t_set_info.pui1_data[i] = pu1Buf[i];
	}
	
	i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_cust_set_info);

	if ( i4_ret != RMR_OK )
	{
		DBG_LOG_PRINT(("!!!!%s a_cfg_fac_sif_x_write fail\n", __func__));
		return i4_ret;
	}
	return RMR_OK;

 }
 /*-----------------------------------------------------------------------------
  * Name: a_cfg_clear_pic_mode
  * Description: Clear all picture mode change content
  * Inputs:
  * Outputs: NONE
  * Returns:
  ----------------------------------------------------------------------------*/
INT32 a_cfg_clear_pic_mode(VOID)//colby@191220  w
{
    INT16  i2_pic_mode = 0;
    INT32  i4_ret = 0;

    for(i2_pic_mode=0;i2_pic_mode<=ACFG_PRE_SET_PIC_MODE_NUM;i2_pic_mode++)
    {
        a_cfg_reset_preset_pic_mode_ex(i2_pic_mode);

        /* set the pq chg status*/
        a_cfg_set_preset_pic_mode_chg_status(i2_pic_mode, FALSE);
    }

    i4_ret = a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
	if ( i4_ret != RMR_OK )
	{
		DBG_LOG_PRINT(("---a_cfg_clear_pic_mode---\n"));
		return i4_ret;
	}

    return APP_CFGR_OK;

}
 /*-----------------------------------------------------------------------------
  * Name: a_cfg_gamma_table_get
  * Description: get gamma table index
  * Inputs:
  * Outputs: NONE
  * Returns:
  ----------------------------------------------------------------------------*/
/*
    306 = 3 group(R/G/B) x 17 point x 2 byte x 3 color tempeture
*/
extern INT32 a_cfg_cust_get_gamma_table(VOID* pv_data, SIZE_T z_size_val);

INT32 a_cfg_gamma_table_get(UINT8* pv_data, UINT8 ui_index)
{
    INT32 i4_ret = 0;
    UINT8 gamma[306]={0};
    UINT16 ui2_count;

    i4_ret=a_cfg_cust_get_gamma_table(&gamma,sizeof(gamma));

    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("%s : a_cfg_cust_get_gamma_table fail\n", __FUNCTION__));
        return i4_ret;
    }

    for(ui2_count=0;ui2_count<GAMMA_MAX_LEN;ui2_count++)
    {
        *(pv_data+ui2_count)=gamma[ui2_count+GAMMA_MAX_LEN*ui_index];
        DBG_LOG_PRINT(("102 data=  [%d]=%x   \n",ui2_count,*(pv_data+ui2_count)));            
    }
    
    return APP_CFGR_OK;
} 
 /*-----------------------------------------------------------------------------
  * Name: a_cfg_gamma_enable_off
  * Description: enable gamma flag set off
  * Inputs:
  * Outputs: NONE
  * Returns:
  ----------------------------------------------------------------------------*/
INT32 a_cfg_gamma_enable_off(VOID) //colby@200110
{
    BOOL fgamma_onoff;
    INT32  i4_ret = 0; 

    i4_ret=a_cfg_custom_Get_Factory_GAMMA_OnOff(&fgamma_onoff);
    if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
    {
		DBG_LOG_PRINT(("---a_cfg_custom_Get_Factory_GAMMA_OnOff get fail---\n"));
		return i4_ret;
    }

    if(fgamma_onoff==TRUE)
        i4_ret=a_cfg_custom_Set_Factory_GAMMA_OnOff(FALSE);    

    return i4_ret;
}

 /*-----------------------------------------------------------------------------
  * Name: a_cfg_gamma_enable_warm
  * Description: enable eeprom gamma warm
  * Inputs:
  * Outputs: NONE
  * Returns:
  ----------------------------------------------------------------------------*/
INT32 a_cfg_gamma_enable_warm(BOOL        f_gEnable)//colby@200115
{
    INT32  i4_ret = 0;  
   GAMMA_ONOFF_INFO_T t_info;
   
   c_memset(&t_info, 0, sizeof(t_info));

   i4_ret=a_cfg_gamma_enable_off();
   if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
   {
	    DBG_LOG_PRINT(("---a_cfg_custom_set_Factory_GAMMA_OnOff fail---\n"));
		return i4_ret;
   }

   t_info.bEnable=f_gEnable;
   t_info.u1ColTemp = 0;   /* set warm gamma flag */
   i4_ret = a_cfg_cust_set_gamma_enable_by_temp(&t_info,sizeof(t_info));

   if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
   {
	    DBG_LOG_PRINT(("---a_cfg_cust_set_gamma_enable_by_temp false fail---\n"));
		return i4_ret;
   }

    return i4_ret;
}

 /*-----------------------------------------------------------------------------
  * Name: a_cfg_gamma_enable_by_temp
  * Description: enable eeprom gamma index
  * Inputs:
  * Outputs: NONE
  * Returns:
  ----------------------------------------------------------------------------*/
INT32 a_cfg_gamma_enable_by_temp(INT16 i2_temp) //colby@200110
{
    INT32  i4_ret = 0;    
    GAMMA_ONOFF_INFO_T t_info;
    c_memset(&t_info, 0, sizeof(t_info));

    i4_ret=a_cfg_gamma_enable_off();
    if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
    {
		DBG_LOG_PRINT(("---a_cfg_custom_set_Factory_GAMMA_OnOff fail---\n"));
		return i4_ret;
    }

    /*
        when gamma_onoff set "FALSE",will check a_cfg_cust_set_gamma_enable_by_temp function setting

        a_cfg_cust_set_gamma_enable_by_temp setting will toggle
    */

{ //toggle setting will be update
   t_info.bEnable=FALSE;
   t_info.u1ColTemp = 1;   /* clear cool flag */
   i4_ret = a_cfg_cust_set_gamma_enable_by_temp(&t_info,sizeof(t_info));
   if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
   {
	    DBG_LOG_PRINT(("---a_cfg_cust_set_gamma_enable_by_temp cool fail---\n"));
		return i4_ret;
   }

   t_info.u1ColTemp = 2;  /* clear normal flag */
   i4_ret = a_cfg_cust_set_gamma_enable_by_temp(&t_info,sizeof(t_info));
   if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
   {
	    DBG_LOG_PRINT(("---a_cfg_cust_set_gamma_enable_by_temp normal fail---\n"));
		return i4_ret;
   }

   t_info.u1ColTemp = i2_temp;
   i4_ret = a_cfg_cust_set_gamma_enable_by_temp(&t_info,sizeof(t_info));
   if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
   {
	    DBG_LOG_PRINT(("---a_cfg_cust_set_gamma_enable_by_temp warm fail---\n"));
		return i4_ret;
   }

   t_info.bEnable=TRUE;
   i4_ret = a_cfg_cust_set_gamma_enable_by_temp(&t_info,sizeof(t_info));
   if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
   {
		DBG_LOG_PRINT(("---a_cfg_cust_set_gamma_enable_by_temp fail---\n"));
		return i4_ret;
   }

   i4_ret =a_cfg_fac_data_eeprom_set_fac_gamma(t_info.bEnable);
   if(i4_ret!=NAVR_OK) 
   {
		DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_set_fac_gamma fail---\n"));
		return i4_ret;
   }
#if 0   
/* check EEPROM value */
{
    BOOL f_temp;
    
   a_cfg_fac_data_eeprom_get_fac_gamma(&f_temp);
   DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_get_fac_gamma=%d---\n",f_temp));   
} 
#endif
}

    return APP_CFGR_OK;
} 
  /*-----------------------------------------------------------------------------
  * Name: a_cfg_fac_data_eeprom_set_fac_gamma
  * Description: set fac gamma setting
  * Inputs:
  * Outputs: NONE
  * Returns:
  ----------------------------------------------------------------------------*/
INT32 a_cfg_fac_data_eeprom_set_fac_gamma(UINT8 ui_value)
{
    INT32 i4_ret = 0;
    UINT32 ui4_written = 0;

    //DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_set_fac_gamma=%d---\n",ui_value));
    if(a_cfg_custom_EEPROM_cmp_chksum()==FALSE)
        a_cfg_custom_plf_opt_fac_init(); 

    i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_GAMMA_SWITCH, &ui_value, 1, &ui4_written);
    if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
    {
	    DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_set_fac_gamma fail---\n"));
		return i4_ret;
    }

    i4_ret = a_cfg_custom_EEPROM_update_chksum();
    return i4_ret;
}

  /*-----------------------------------------------------------------------------
  * Name: a_cfg_fac_data_eeprom_get_fac_gamma
  * Description: set fac warm gamma setting
  * Inputs:
  * Outputs: NONE
  * Returns:
  ----------------------------------------------------------------------------*/
INT32 a_cfg_fac_data_eeprom_get_fac_gamma(BOOL *f_value)
{
    INT32 i4_ret = 0;
    UINT32 ui4_written = 0;
    UINT8 ui_data=0;

    //DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_get_fac_gamma ---\n"));

    if(a_cfg_custom_EEPROM_cmp_chksum()==FALSE)
        a_cfg_custom_plf_opt_fac_init(); 

   i4_ret=a_cfg_eep_raw_read(EEP_FACTORY_GAMMA_SWITCH, &ui_data, 1, &ui4_written);

   //DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_get_fac_gamma get i4_ret=%u ---\n",i4_ret));

   if(i4_ret!=NAVR_OK) //colby@200120 check gamma on off status
   {
	    DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_get_fac_gamma get fail---\n"));
		return i4_ret;
   }

    //DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_get_fac_gamma 11 =%x---\n",ui_data));

    if(ui_data>1) /* 0:panel.ini 1:eeprom */
    {
	    DBG_LOG_PRINT(("---fac_gamma get data over range,reset to 0---\n"));    
        ui_data=0;
        a_cfg_eep_raw_write(EEP_FACTORY_GAMMA_SWITCH, &ui_data, 1, &ui4_written);
    }
    //DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_get_fac_gamma=%x---\n",ui_data));

    if(ui_data==0)
        *f_value=FALSE;
    else    
        *f_value=TRUE;

    return i4_ret;
}

   /*-----------------------------------------------------------------------------
   * Name: a_cfg_fac_data_eeprom_set_fac_vcom
   * Description: Save fac Vcom Value
   * Inputs:
   * Outputs: NONE
   * Returns:
   ----------------------------------------------------------------------------*/
INT32 a_cfg_fac_data_eeprom_set_fac_vcom(UINT8 ui_value)
{
	INT32 i4_ret = 0;
#if 0
	UINT32 ui4_written = 0;

	//DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_set_fac_gamma=%d---\n",ui_value));
	if(a_cfg_custom_EEPROM_cmp_chksum()==FALSE)
		a_cfg_custom_plf_opt_fac_init(); 

	i4_ret = a_cfg_eep_raw_write(EEP_FACTORY_VCOM_VALUE, &ui_value, 1, &ui4_written);
	if(i4_ret != NAVR_OK) //colby@200120 check gamma on off status
	{
		DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_set_fac_vcom fail---\n"));
		return i4_ret;
	}

	i4_ret = a_cfg_custom_EEPROM_update_chksum();
#else
	i4_ret = a_cfg_custom_EEPROM_set(FOX_EEPROM_FAC_VCOM_VALUE, 1, &ui_value);
#endif
	return i4_ret;
}
 
   /*-----------------------------------------------------------------------------
   * Name: a_cfg_fac_data_eeprom_get_fac_vcom
   * Description: Get fac Vcom Value
   * Inputs:
   * Outputs: NONE
   * Returns:
   ----------------------------------------------------------------------------*/
INT32 a_cfg_fac_data_eeprom_get_fac_vcom(UINT8 ui_value)
{
	INT32 i4_ret = 0;
#if 0
	UINT32 ui4_written = 0;

	//DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_get_fac_vcom ---\n"));

	if(a_cfg_custom_EEPROM_cmp_chksum()==FALSE)
		a_cfg_custom_plf_opt_fac_init(); 

	i4_ret=a_cfg_eep_raw_read(EEP_FACTORY_VCOM_VALUE, &ui_value, 1, &ui4_written);

	if(i4_ret != NAVR_OK) //colby@200120 check gamma on off status
	{
		DBG_LOG_PRINT(("---a_cfg_fac_data_eeprom_get_fac_vcom get fail---\n"));
	}
#else
	i4_ret = a_cfg_custom_EEPROM_get(FOX_EEPROM_FAC_VCOM_VALUE, &ui_value);
#endif

	return i4_ret;
}
 
#endif
 //Tommy 20191009 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
