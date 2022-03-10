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

#include "acfg_cust_factory.h"
#include "acfg_cust_factory_vizio.h"
#include "u_dm.h" //Denny 2011/12/21 add for DEFINE used in _fac_reg_usb_vbus_oc_nfy()

#include "TPV_factory/TPV_d_factory.h"  //ke_vizio_20160908 add

#include "TPV_factory/TPV_fac_menu/TPV_fac.h"	// Ben 20170412

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"	//mind 20160912
#include "app_util/a_rating.h"				//mind 20160912
#include "res/menu2/menu_custom.h"			//mind 20160912
#include "menu2/menu_common/menu_common.h"  // Ben 10280130
#endif
#include "rest/a_rest_event.h"  // Ben 20171222
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
static UINT32   ui4_cust_fac_def                 = APP_CFG_CUST_FAC_DEF;
static UINT16    ui2_cust_set_lang_def         = 0;
static UINT32   ui4_cust_fac_panel_type     = 0;
static UINT8  ui1_cust_vga_backlt_min_def = 0;//= APP_CFG_RECID_CUST_PWM_MIN_DEF; //Emerson modify 2008-1007
static UINT8  ui1_cust_vga_backlt_max_def = 0xff;//= APP_CFG_RECID_CUST_PWM_MAX_DEF;//Emerson modify 2008-1007
static UINT32  ui4_cust_fac_backlt_lifetime = 0;
static UINT8    ui1_cust_hdcp_crc_def         = 0;
#define HDMI_EDID_DATA 256
#define VGA_EDID_DATA 128

//kyo_20110307 modify
static INT16 aai2_clr_gain_delta[ACFG_CLR_GAIN_ELEM_NUM][6] =
{
    /* R,  G,  B*/
    /* Group 0: TV */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},       /* Cool */

    /* Group 1: CVBS, S-Video */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},      /* Cool */

    /* Group 2: YPBPR */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},       /* Cool */

    /* Group 3: HDMI1  */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},      /* Cool */

	/* Group 4: HDMI2  */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},      /* Cool */

	/* Group 5: HDMI3  */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},      /* Cool */

	/* Group 6: HDMI4  */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},      /* Cool */

	/* Group 7: VGA  */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},      /* Cool */
    
    /* Group 8: MMP  */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0},       /* Cool */

	/* Group 9: VTRL  */
    {  0,  0,  0,  0,  0,  0},      /* Custom */
    {  0,  0,  0,  0,  0,  0},      /* Medium */
    {  0,  0,  0,  0,  0,  0},      /* Warm */
    {  0,  0,  0,  0,  0,  0}       /* Cool */	
};

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static HANDLE_T     h_fac_usb_oc_nfy = NULL_HANDLE; //Denny 2011/12/21 add
static UINT8        ui1_fac_usb_vbus_fail_check = 0; //Denny 2011/12/21 add

static UINT32 ui4_g_keypad_read = 0; //Denny 2014/02/17 add
static UINT32 ui4_urc_flag = 0; //Denny 2015/09/15 add
/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/
static INT32 a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_T   e_spec_type,
                              VOID*                         pv_get_info,
                              SIZE_T*                       pz_size);

static VOID _fac_vbus_oc_nfy_status (DM_EVT_T t_evt, VOID* pv_data, VOID* pv_tag);							  
/*-----------------------------------------------------------------------------
 * external methods declarations
 *---------------------------------------------------------------------------*/
extern INT32 a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);   //ke_vizio_20130606 add
extern INT32 a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_T e_op_type, VOID* pv_data);   //ke_vizio_20130606 add

/*-----------------------------------------------------------------------------
 * Name: acfg_custom_pre_init
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
extern INT32 acfg_custom_tpv_fac_pre_init(VOID)
{
    DECLARE_FIELD(IDX_CUST_FAC,             APP_CFG_GRPID_CUSTOM_BASE,      APP_CFG_RECID_CUST_BASE_FAC,
                  CFG_32BIT_T,      1,          &ui4_cust_fac_def,          1,
                  NULL,             NULL,       ACFG_ACCESS_FACTORY);
    DECLARE_FIELD(IDX_CUST_FAC_DEFAULT_LANG,   APP_CFG_GRPID_CUSTOM_BASE,      APP_CFG_RECID_CUST_BASE_DEFAULT_LANG,
                  CFG_16BIT_T,       1,          &ui2_cust_set_lang_def,       1,
                  NULL,             NULL,       ACFG_ACCESS_FACTORY);
    DECLARE_FIELD(IDX_CUST_FAC_PANEL_TYPE,   APP_CFG_GRPID_CUSTOM_BASE,      APP_CFG_RECID_CUST_BASE_PANEL_TYPE,
                  CFG_32BIT_T,       1,          &ui4_cust_fac_panel_type,       1,
                  NULL,             NULL,       ACFG_ACCESS_FACTORY);	
                  
    //a_cfg_custom_get_panel_backlight_HiLo(&ui1_cust_vga_backlt_max_def,&ui1_cust_vga_backlt_min_def);

    DECLARE_FIELD(IDX_CUST_VGA_PWM_MIN, 		 APP_CFG_GRPID_CUSTOM_BASE, 	APP_CFG_RECID_CUST_BASE_VGA_PWM_MIN,
                  CFG_8BIT_T,		1,	&ui1_cust_vga_backlt_min_def,	1,
                  NULL, 			NULL,		ACFG_ACCESS_FACTORY);
    DECLARE_FIELD(IDX_CUST_VGA_PWM_MAX, 		 APP_CFG_GRPID_CUSTOM_BASE, 	APP_CFG_RECID_CUST_BASE_VGA_PWM_MAX,
                  CFG_8BIT_T,		1,	&ui1_cust_vga_backlt_max_def,	 1,
                  NULL, 			NULL,		ACFG_ACCESS_FACTORY);
    DECLARE_FIELD(IDX_CUST_FAC_BACKLIGHT_LIFETIME, 		 APP_CFG_GRPID_CUSTOM_BASE, 	APP_CFG_RECID_CUST_BASE_BLT_LT,
                  CFG_32BIT_T,		1,	&ui4_cust_fac_backlt_lifetime,	1,
                  NULL, 			NULL,		ACFG_ACCESS_FACTORY); 	
    DECLARE_FIELD(IDX_CUST_HDCP_CRC,   APP_CFG_GRPID_CUSTOM_BASE,    APP_CFG_RECID_CUST_BASE_HDCP_CRC,
//TOP Louis 20090115
                  CFG_16BIT_T,      1,      &ui1_cust_hdcp_crc_def,      1,
                  NULL,             NULL,   ACFG_ACCESS_FACTORY);				  

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_custom_post_init
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
extern INT32 acfg_custom_tpv_fac_post_init(VOID)
{
    UINT32         ui4_fac_rc_val;
    /*INT32    i4_ret;

     UINT8 ui_hi, ui_low;
     a_cfg_custom_get_panel_backlight_HiLo(&ui_hi, &ui_low);
     
     i4_ret = acfg_set(IDX_CUST_VGA_PWM_MAX, &ui_hi , 1);
     if (i4_ret != APP_CFGR_OK){
         return i4_ret;
     }
     
     i4_ret = acfg_set(IDX_CUST_VGA_PWM_MIN, &ui_low , 1);
     if (i4_ret != APP_CFGR_OK){
         return i4_ret;
     }*/
    //Turn off URC when power on.
    a_cfg_cust_fac_get(&ui4_fac_rc_val);
    //ui4_fac_rc_val = ui4_fac_rc_val & 0x0f;//jeff 20090309  modify
    ui4_fac_rc_val = ui4_fac_rc_val & (~APP_CFG_CUST_FAC_RC_ON);  //ke_vizio_20130911 modify
    a_cfg_cust_fac_set(ui4_fac_rc_val);
    

    //ke_vizio_20110420
    /*i4_ret = _acfg_custom_tpv_check_eep();
    ACFG_LOG_ON_FAIL(i4_ret);*/
    
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_get_default_lang
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern INT16 a_cfg_cust_fac_get_panel_type(
        INT16*                 pui2_fac_panel_type
        )
{
    SIZE_T  z_size;

    if (pui2_fac_panel_type == NULL)
    {
        return APP_CFGR_INV_ARG;
    }
    return acfg_get(IDX_CUST_FAC_PANEL_TYPE, pui2_fac_panel_type , &z_size);
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_set_panel_type
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern INT16 a_cfg_cust_fac_set_panel_type (
        UINT16                  pui2_fac_panel_type
        )
{
    return acfg_set(IDX_CUST_FAC_PANEL_TYPE, &pui2_fac_panel_type , 1);
}
/*-----------------------------------------------------------------------------
 * Name: _nav_fac_handle_msg
 * Description: handle the message from navigater controller
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_get_backlight_lifetime
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_fac_get_backlight_lifetime(
        INT32*                 pi4_fac_backlight_lifetime
        )
{
    SIZE_T  z_size;

    if (pi4_fac_backlight_lifetime == NULL)
    {
        return APP_CFGR_INV_ARG;
    }
    return acfg_get(IDX_CUST_FAC_BACKLIGHT_LIFETIME, pi4_fac_backlight_lifetime , &z_size);
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_set_default_lang
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern UINT32 a_cfg_cust_fac_set_backlight_lifetime (
        UINT32                  pui4_fac_backlight_lifetime
        )
{
    return acfg_set(IDX_CUST_FAC_BACKLIGHT_LIFETIME, &pui4_fac_backlight_lifetime , 1);
}
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
    if(i4_ret != 0)
    {
        //Printf("!!!!%s : Get value fail\n", __func__);
        return i4_ret;
    }

    return i4_ret;
}


//ke_vizio_20130520
INT32 a_cfg_cust_get_image_bank_bit(UINT8 *ui1_image_bank_bit)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_GET_INFO_T t_get_info = {0};
    UINT8 ui1_bit = 0;
    SIZE_T      z_size = sizeof(ui1_bit);
    
    t_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_IMAGE_BANK_BIT;
    t_get_info.pv_get_info = (VOID *)&ui1_bit;
    t_get_info.pz_size = &z_size;
    i4_ret = a_cfg_get_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET,(VOID *)&t_get_info);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("%s a_cfg_cust_get_image_bank_bit fail\n", __FUNCTION__));
        return i4_ret;
    }

    *ui1_image_bank_bit = ui1_bit; 
    return APP_CFGR_OK;
}
INT32 a_cfg_cust_set_image_bank_bit(UINT8 ui1_image_bank_bit)
{
    INT32 i4_ret = 0;
    CUST_SPEC_TYPE_SET_INFO_T t_cust_set_info = {0};
    UINT8      ui1_bit = ui1_image_bank_bit;
    SIZE_T      z_size = sizeof(ui1_bit);
    
    t_cust_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_SET_IMAGE_BANK_BIT;
    t_cust_set_info.pv_set_info = (VOID *)&ui1_bit;
    t_cust_set_info.z_size = z_size;
    t_cust_set_info.b_store = TRUE;
    i4_ret = a_cfg_set_drv_comp(DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET,(VOID *)&t_cust_set_info);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("%s : a_cfg_cust_set_image_bank_bit fail\n", __FUNCTION__));
        return i4_ret;
    }
    return APP_CFGR_OK;
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


/*-----------------------------------------------------------------------------
 * Name: a_cfg_ping_ip_v4
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_ping_ip_v4(CHAR* ps_ip, INT16 i2_wait_time, VOID (*notify_fn)(INT16 i2_rsp_time))
{
    c_net_ping_v4(ps_ip, 64, i2_wait_time, notify_fn);
	return 0;
}



INT32 a_cfg_fac_reset(VOID)
{

    INT32 i4_ret;
    UINT32		ui4_fac_rc_val;

    // 5691, 5695 unpair all BT devices
    DBG_INFO(("\n[TPV factory] unpair all BT devices start!!!! \n"));
    AP_SYSTEM_CALL("chroot /proc/`pidof bluetoothd`/root /bin/bash -c 'LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_unpair'");
    DBG_INFO(("\n[TPV factory] unpair all BT devices end!!!! \n"));

    /* To avoid the temporary state of AV in factory reset. */
    a_tv_stop_all_svc(h_g_acfg_svctx_main, h_g_acfg_svctx_sub);

    /* reset settings */
    a_tv_net_send_cmd(":dtv_app_mtk,am,:unblock_3rd\n");
    //Emerson 2008-0923 : keep ColorTemp data in the User reset if AOC factory mode enable.    
    a_cfg_custom_reset_factory();
 
    a_cfg_cust_fac_clear_ch_table();   

#if 0	// Ben 20140825, clear 3rd_rw always in case that data lost by AC drop
	system("/basic/bin/mke2fs.static -t ext4 /dev/mmcblk0p12");
	system("mount -t ext4 /dev/mmcblk0p12 /3rd_rw");
#endif

#if 0 //20180518 call menu_clear_memory_ex to do  
    //Larry 2012 0412, for factory reset should remove 3rd party data.
	a_tv_net_reset_3rd_ap_data(APP_TV_NET_RESET_ITEM_ALL);
   	a_tv_custom_set_tos(FALSE);
   	a_tv_custom_set_privacy(FALSE);

#endif

#if 0 //20180518 call menu_clear_memory_ex to do   
    //Larry 2014 1020 for modify CEC default change to "Disable" after factory reset. issue : TF1014VIZUSMTKO1-1446
	/*CEC default setting:ARC only/sac on*/
	//a_cfg_set_cec_func (APP_CFG_CEC_ARC_ONLY);           Ben 20171212 /* change CEC default setting from ARC only to Enable, follow UI spec4.1 4.9.5 */
	a_cfg_set_cec_sac_func(1);
#endif

	nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, FALSE); //willy 2012 0229 fix btn_rst  ac/on can not standby	// Ben 20170412

#if 0 //20180518 call menu_clear_memory_ex to do   
    //ke_vizio_20130621 add : TF1014VIZUSMTKO0-42
    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);

#ifdef APP_C4TV_SUPPORT
	a_c4tv_apron_reset_default();	//mind 20160912
    a_rating_atsc_storage(FALSE);	//mind 20160912
    menu_custom_chg_lang();			//mind 20160912
#endif
#endif

    a_sleep_timer_stop();
    a_cfg_set_time_zone_data(-8*3600 , FALSE);	//kyo_20111128 reset daylight saving to off
    /* turn off URC */
	i4_ret = a_cfg_cust_fac_get(&ui4_fac_rc_val);
	ACFG_LOG_ON_FAIL(i4_ret);
	
	ui4_fac_rc_val = ui4_fac_rc_val & 0x0f;
	
	i4_ret =a_cfg_cust_fac_set(ui4_fac_rc_val);
	ACFG_LOG_ON_FAIL(i4_ret);

    //ke_vizio_20161205 add : TF1016VIZUSMTK03-796
#ifdef APP_NETWORK_SUPPORT
    c_pcl_set_ethernet_wol_ctrl(PCL_ETHERNET_WOL_DISABLE);
    c_pcl_set_wifi_wol_ctrl(PCL_WIFI_WOL_DISABLE);
#endif

#ifdef APP_TPV_DFT_WIFI_AUTO_DETECTION 
    {    //ke_vizio_20170523
        // Reset WIFI status
        UINT8 ui1_status = 0xFF;
        UINT32 ui4_wirtten;
        a_cfg_eep_raw_write(EEP_WIFI_SSID_ON, &ui1_status, 1, &ui4_wirtten);
    }
#endif

#if 0 //20180518 call menu_clear_memory_ex to do   
    //ke_vizio_20171220 for MUSC-790(TF1018VIZUS01-868)
    if ((0 == access("/3rd_rw/rest_server/pairedDevices", 0)))
    {
        system("rm -rf /3rd_rw/rest_server/pairedDevices; sync");
    }
    system("rm -rf /3rd_rw/sc-data; sync");
    system("rm -rf /3rd_rw/web_server; sync");
    system("rm -rf /3rd_rw/oobe; sync");
    system("rm -rf /demo/sc; sync");
#endif

#if 0 //20180518 call menu_clear_memory_ex to do
#ifdef APP_C4TV_SUPPORT //20180518 call menu_clear_memory_ex to do
// Ben 20171222, sync from clear memory
    DBG_LOG_PRINT (("<MENU> reset c4tv timezone\n\r"));
    a_c4tv_apron_set_timezone("America/Los_Angeles");
    a_c4tv_apron_set_locale("en");
    a_c4tv_apron_reset_default();
#endif
#endif

#if 0  //20180518 call menu_clear_memory_ex to do
 // Ben 20171222, sync from clear memory. 
    a_tv_custom_set_tos(FALSE);
    rest_event_notify("tv_settings/cast/tos_accepted", 0, "");
    a_tv_custom_set_privacy(FALSE);
    a_tv_custom_clear_tos_version();
    a_tv_custom_clear_http_url_status();
	a_cfg_set_tts_switch_status(0);
	a_cfg_update_tts_switch_status();
    /* reset viewing data to not showed. */
    a_tv_custom_set_viewing_data_show(FALSE);

    if (a_tv_stop(menu_get_crnt_svctx()) != TVR_OK)
    {
        DBG_ERROR (("<MENU> Stop service failed! \n\r"));
    }
    a_tv_net_send_cmd(":dtv_app_mtk,am,:unblock_3rd\n");
#endif
    
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
           ui2_i == IDX_CUST_HDCP_CRC  ||
           (ui2_i >= IDX_CUSTOM_FAC_CUST_11_POINT_RED && ui2_i <= IDX_CUSTOM_FAC_CUST_CLR_TUNER_BRI_Y)
           )
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
#ifdef APP_BLUETOOTH_SUPPORT
#ifdef FAC_BLUETOOTH_SUPPORT // Ben 20180126
	//a_cfg_custom_unpair_all_bluetooth_devices(); //sam 110615 for XM issue "MTK5395_VIZIO_CTV-302"
#endif
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


/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_reset_factory
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
extern INT32 a_cfg_cust_fac_psm_set(
    UINT8   ui1_input,
    UINT16  ui2_id,
    INT16   i2_val)
{
    INT32       i4_ret;
    UINT16      ui2_elem_idx;

    i4_ret = acfg_custom_get_elem_index(ui2_id, ui1_input, &ui2_elem_idx);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    i4_ret = acfg_set_int16_by_idx(IDX_PIC_MODE, ui2_elem_idx, i2_val);
    ACFG_CHK_FAIL(i4_ret, i4_ret);

    return APP_CFGR_OK;
}



INT32 C_GetHDMIKSV(VOID* pv_data) 
{
	volatile UINT8 ui1_hdmi_ksv[HDMI_KSV_DATA]={0};
	SIZE_T z_size;
	z_size= sizeof(ui1_hdmi_ksv) / sizeof(ui1_hdmi_ksv[0]); 
	
	a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDMI_KSV_VALUE, pv_data, &z_size);
	return APP_CFGR_OK;
}

INT32 C_GetHDMIReceiverID(VOID* pv_data) // Ben 20171027
{
	volatile UINT8 ui1_hdmi_ksv[HDMI_KSV_DATA]={0};
	SIZE_T z_size;
	z_size= sizeof(ui1_hdmi_ksv) / sizeof(ui1_hdmi_ksv[0]); 
	
	a_cfg_fac_c_rm_get_cust(DRV_CUSTOM_CUST_SPEC_TYPE_READ_HDCP22_RECEIVERID_VALUE, pv_data, &z_size);
	return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_reg_get_usb_vbus_status
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
UINT8 a_cfg_cust_fac_reg_get_usb_vbus_status (VOID)
{
    return ui1_fac_usb_vbus_fail_check;
}


/*-----------------------------------------------------------------------------
 * Name: _fac_vbus_oc_nfy_status
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _fac_vbus_oc_nfy_status (DM_EVT_T t_evt, VOID* pv_data, VOID* pv_tag)
    {
    switch (t_evt)
    {           
        case DM_BOARD_EVT_USB_ST_NORMAL:         
            ui1_fac_usb_vbus_fail_check = 0;
            break;            
        case DM_BOARD_EVT_USB_ST_OVER_CURRENT:
            ui1_fac_usb_vbus_fail_check = 0x01;
            break;            
        default:        
	        break;            
    }
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_reg_usb_vbus_oc_nfy
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
VOID a_cfg_cust_fac_reg_usb_vbus_oc_nfy (VOID)
{
    DM_EVT_CAT_T    e_usb_vbus_oc_nfy_category = DM_EVT_CAT_BOARD;
    DM_EVT_FILTR_T  t_usb_vbus_oc_nfy_dm_filter;
    DM_COND_T       t_usb_vbus_oc_nfy_dm_cond;

    c_memset(&t_usb_vbus_oc_nfy_dm_filter, 0, sizeof(DM_EVT_FILTR_T));
    c_memset(&t_usb_vbus_oc_nfy_dm_cond, 0, sizeof(DM_COND_T));        
      
    t_usb_vbus_oc_nfy_dm_cond.t_hw_type            = DM_HW_TYPE_USB;
    t_usb_vbus_oc_nfy_dm_cond.t_dev_type           = DM_DEV_UKW_TYPE_UNKNOWN;
    t_usb_vbus_oc_nfy_dm_filter.pt_evt_filtr       = &t_usb_vbus_oc_nfy_dm_cond;
    t_usb_vbus_oc_nfy_dm_filter.ui4_evt_filtr_ns   = 1;

    /* Register usb overcurrent notify function to DM. */                             
    c_dm_reg_nfy_fct(   e_usb_vbus_oc_nfy_category,
                        _fac_vbus_oc_nfy_status,
                        &t_usb_vbus_oc_nfy_dm_filter,
                        NULL,
                        &h_fac_usb_oc_nfy);      
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_get_read_keypad_status
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
UINT32 a_cfg_cust_fac_get_keypad_status_read(VOID) //Denny 2014/02/17 add
{
    return ui4_g_keypad_read;
}


/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_set_read_keypad_status
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
VOID a_cfg_cust_fac_set_keypad_status_read(UINT32 ui4_val) //Denny 2014/02/17 add
{
    ui4_g_keypad_read = ui4_val;
}


/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_set_urc_flag
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
VOID a_cfg_cust_fac_set_urc_flag(UINT32 u4Val) //Denny 2015/09/15 add for URC flag
{
    ui4_urc_flag = u4Val;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_get_urc_flag
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
UINT32 a_cfg_cust_fac_get_urc_flag(VOID) //Denny 2015/09/15 add for URC flag
{
    return ui4_urc_flag;
}


extern INT16 acfg_custom_clr_temp_delta(
                                        UINT16  ui2_id,
                                        UINT8   ui1_input_grp,
                                        INT16   i2_clr_temp,
                                        INT16   i2_val)
{
    #if 1
    UINT16  ui2_cfg_rec = CFG_GET_SETTING(ui2_id);
    UINT8   ui1_i = 0;
    INT16   i2_j = 0;

    switch(ui2_cfg_rec)
    {
        case APP_CFG_RECID_CLR_GAIN_R:
            ui1_i = 0;
            break;
        case APP_CFG_RECID_CLR_GAIN_G:
            ui1_i = 1;
            break;
        case APP_CFG_RECID_CLR_GAIN_B:
            ui1_i = 2;
            break;
        case APP_CFG_RECID_CLR_OFFSET_R:
            ui1_i = 3;
            break;
        case APP_CFG_RECID_CLR_OFFSET_G:
            ui1_i = 4;
            break;
        case APP_CFG_RECID_CLR_OFFSET_B:
            ui1_i = 5;
            break;
    }

    i2_j = aai2_clr_gain_delta[(ui1_input_grp * ACFG_CLR_TEMP_NUM)+i2_clr_temp][ui1_i];
    i2_j += i2_val;
    return i2_j;
    #endif
    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_fac_handle_msg
 * Description: handle the message from navigater controller
 * Inputs: -
 * Outputs: -
 * Returns: NAVR_OK
 ----------------------------------------------------------------------------*/
extern INT32 a_cfg_fac_eep_init(VOID)  //ke_vizio_20160908 add
{
    INT32   i4_ret;
    UINT32  ui4_off     = 0x00;
    UINT32  ui4_written = 0;
    UINT8   aui1_buff[64];
    UINT32 ui4_model_index = 0;  //ke_vizio_20121115
    UINT32   ui4_mac_addr = 0;
            
	TPV_d_get_RJ45_addr(&ui4_mac_addr);

    i4_ret = a_cfg_custom_get_model_index(&ui4_model_index);  //ke_vizio_20121115
    ACFG_LOG_ON_FAIL(i4_ret);
   

#if defined(TPV_FAC_EEPROM_VER)
    /* Read current EEPROM VERSION, Request by P.E. XL LIN */
    UINT32 ui4_read;
    UINT8 ui1_ver_main, ui1_ver_sub;

    a_cfg_eep_raw_read(EEP_EEPROM_VER_MAIN, &ui1_ver_main, 1, &ui4_read);
    a_cfg_eep_raw_read(EEP_EEPROM_VER_SUB, &ui1_ver_sub, 1, &ui4_read);
#endif

/*    Read current MAC, Request by PE yuehua.wu    */ //sam 110623
    UINT8 aui1_faccmd_ret_val_RJ45[CMD_LEN_Maximum] = {0};

    UINT32 ui4_read_RJ45;
    a_cfg_eep_raw_read(ui4_mac_addr, aui1_faccmd_ret_val_RJ45, 14, &ui4_read_RJ45); //total reserve 14 byte for MAC //sam 130621

    c_memset(aui1_buff, 0xFF, 64);

    do
    {
        i4_ret = a_cfg_eep_raw_write(ui4_off, aui1_buff, 64, &ui4_written);
        if(i4_ret != APP_CFGR_OK)
        {
            DBG_LOG_PRINT(("!!!!%s : a_cfg_eep_raw_write fail\n", __func__));
            break;
        }

        ui4_off += ui4_written;
    }while(ui4_written > 0);

#if defined(TPV_FAC_EEPROM_VER)
    /* Wirte the EEPROM VERSION, Request by P.E. XL LIN  */
    a_cfg_eep_raw_write(EEP_EEPROM_VER_MAIN, &ui1_ver_main, sizeof(ui1_ver_main), &ui4_written);
    a_cfg_eep_raw_write(EEP_EEPROM_VER_SUB, &ui1_ver_sub, sizeof(ui1_ver_sub), &ui4_written);
#endif

    //ke_vizio_20121218
/*    restore current MAC, Request by PE yuehua.wu    */ //sam 110623
    UINT32 ui4_written_RJ45;
    i4_ret = a_cfg_eep_raw_write(ui4_mac_addr, aui1_faccmd_ret_val_RJ45, 14, &ui4_written_RJ45); //total reserve 14 byte for MAC //sam 130621

    i4_ret =  a_cfg_custom_set_model_index(ui4_model_index);  //ke_vizio_20121115
    ACFG_LOG_ON_FAIL(i4_ret);

    i4_ret =  a_cfg_custom_set_odm_index(2);
    ACFG_LOG_ON_FAIL(i4_ret);

    a_cfg_eep_cache_reload();  //ke_vizio_20131105 add
    return 0;
}

static VOID _burning_mode_nfy(
                                        VOID* pv_tag1,
                                        VOID* pv_tag2,
                                        VOID* pv_tag3)
{
    BOOL bOnOff = (BOOL)((UINT32)pv_tag1);

    if(bOnOff == 0)
    {
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_WITH_SIGNAL,
                                      NULL
                                      );
    }
    else // bOnOff == 1
    {
        nav_dispatch_msg_to_component(NAV_COMP_ID_BURNING_MODE,
                                      NAV_UI_MSG_NO_SIGNAL,
                                      NULL
                                      );
    }
}

extern void a_cfg_fac_set_burning_mode(BOOL bOnOff) // Ben 20190222
{
    UINT8   ui1_fac_mask;
    DRV_CUST_OPERATION_INFO_T    t_op_info;//added,20110622
    SIZE_T z_size = sizeof(bOnOff);
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);        
    INT32 i4_Ret = 0;
    
    DBG_INFO(("[Factory] a_cfg_fac_set_burning_mode = %d\n",bOnOff));
    a_cfg_get_factory_mode(&ui1_fac_mask);
    if(bOnOff == 0)
    {
        a_cfg_set_factory_mode(ui1_fac_mask & ~APP_CFG_FAC_MODE_BURNING_MASK);
    }
    else // bOnOff == 1
    {
        a_cfg_set_factory_mode(ui1_fac_mask | APP_CFG_FAC_MODE_BURNING_MASK);
    }

    i4_Ret = nav_request_context_switch(_burning_mode_nfy, (VOID*)((UINT32)bOnOff), NULL, NULL);
    if(i4_Ret != RMR_OK)
    {
        DBG_INFO(("(Factory)Set nav_request_context_switch failed\n"));
    }
    
    a_cfg_update_factory_mode();
    a_cfg_store();

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&bOnOff;
    t_op_info.u.t_cust_spec_set_info.z_size = z_size;
    t_op_info.u.t_cust_spec_set_info.b_store = TRUE;

    /* Set from driver */
    i4_Ret = c_rm_set_comp(
                           DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           z_size_drv
                           );
    if (i4_Ret != RMR_OK)
    {
        DBG_INFO(("[Factory] Set BurnIn mode failed !\n"));
    }
}

VOID a_cfg_fac_set_resotre_gamma_default(VOID)
{
    INT32 ui4_idx = 0;
    VID_CUSTOM_TYPE_SET_NVM_GAMMA_T prNVMGamma= {0};
    UINT16 ui2_gamma_def[17] = {0x0000,0x00EF,0x01FF,0x02FF,0x03FF,0x04FF,0x05FF,0x06FF,
                                0x07FF,0x08FF,0x09FF,0x0AFF,0x0BFF,0x0CFF,0x0DFF,0x0EFF,0x0FFF};
    
    memcpy(&prNVMGamma.u2GammaTbl[0][0], &ui2_gamma_def, sizeof(ui2_gamma_def));
    memcpy(&prNVMGamma.u2GammaTbl[1][0], &ui2_gamma_def, sizeof(ui2_gamma_def));
    memcpy(&prNVMGamma.u2GammaTbl[2][0], &ui2_gamma_def, sizeof(ui2_gamma_def));
    
    for(ui4_idx = 0; ui4_idx < 17 ; ui4_idx++)  // NVM_GAMMA_PT : 17
    {
        DBG_INFO(("u2GammaTbl[0][%d]: 0x%x\n", ui4_idx, prNVMGamma.u2GammaTbl[0][ui4_idx]));
    }

    prNVMGamma.u4TblIndex = 0;
    a_cfg_cust_set_Gamma_table(prNVMGamma);
    prNVMGamma.u4TblIndex = 1;
    a_cfg_cust_set_Gamma_table(prNVMGamma);
    prNVMGamma.u4TblIndex = 2;
    a_cfg_cust_set_Gamma_table(prNVMGamma);
    
}