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
#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdint.h>
#include <signal.h>
#include <sys/time.h>

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

#include "INX_factory/INX_d_factory.h"
#include "INX_factory/INX_fac_menu/INX_fac.h"

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"	//mind 20160912
#include "app_util/a_rating.h"				//mind 20160912
#include "res/menu2/menu_custom.h"			//mind 20160912
#endif
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
static UINT32 inx_ui4_g_ir_read = 0; //joe.zy 2019/02/21 add
static UINT32 inx_ui4_ir_key_flag = 0;//joe.zy 2019/02/21 add
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
    
#if defined(FAC_MENU_MODEL_NAME_SELECT) && defined(APP_READ_MODEL_NAME_FROM_EEPROM) //Denny 2009/12/11 add
        
    UINT32      ui4_read_byte;
    CHAR        s_data_r[MODEL_NAME_LENGTH];

    c_memset(s_data_r, 0, sizeof(s_data_r));
    a_cfg_eep_raw_read(EEP_MODEL_NAME, s_data_r, MODEL_NAME_LENGTH, &ui4_read_byte);

    if(nav_fac_model_name_is_valid(s_data_r) == FALSE)
    {
        nav_fac_model_name_write_default_model_name();
    }
        
#endif

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

    DBG_LOG_PRINT(("%s(), i4_ret=%d\n", __func__, i4_ret));

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

    /* To avoid the temporary state of AV in factory reset. */
    a_tv_stop_all_svc(h_g_acfg_svctx_main, h_g_acfg_svctx_sub);

    /* reset settings */
    a_tv_net_send_cmd(":dtv_app_mtk,am,:unblock_3rd\n");
    //Emerson 2008-0923 : keep ColorTemp data in the User reset if AOC factory mode enable.    
    a_cfg_custom_reset_factory();
 
    a_cfg_cust_fac_clear_ch_table();

#if 0	// Ben 20140825, clear 3rd_rw always in case that data lost by AC drop
	system("/basic/bin/mke2fs -t ext4 /dev/mmcblk0p10");
	system("mount -t ext4 /dev/mmcblk0p10 /3rd_rw");
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
			//a_cfg_set_cec_func (APP_CFG_CEC_ARC_ONLY);		   Ben 20171212 /* change CEC default setting from ARC only to Enable, follow UI spec4.1 4.9.5 */
			a_cfg_set_cec_sac_func(1);
#endif


    nav_fac_set_setup_value(NAV_FAC_MENU_BURN_IN, FALSE); //willy 2012 0229 fix btn_rst  ac/on can not standby  // Ben 20170412


#if 0 //20180518 call menu_clear_memory_ex to do
		//ke_vizio_20130621 add : TF1014VIZUSMTKO0-42
		a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
	
#ifdef APP_C4TV_SUPPORT
			a_c4tv_apron_reset_default();	//mind 20160912
		a_rating_atsc_storage(FALSE);		//mind 20160912
		menu_custom_chg_lang(); 					//mind 20160912
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

    /* Overwrite the Color gain/offset by INX default value */
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
 * Name: inx_cfg_cust_fac_get_read_ir_key_status
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
UINT32 inx_cfg_cust_fac_get_read_ir_key_status(VOID) //joe.zy.chen 2019/02/21
{
    return inx_ui4_g_ir_read;
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
 * Name: a_cfg_cust_fac_set_ir_key_status_read
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *-----------------------------------------------------------------------------*/
VOID inx_cfg_cust_fac_set_ir_key_status_read(UINT32 ui4_val) //joe.zy.chen 2019/02/21
{
    inx_ui4_g_ir_read = ui4_val;
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
 * Name: a_cfg_cust_fac_set_ir_key_flag
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
VOID inx_cfg_cust_fac_set_ir_key_flag(UINT32 u4Val) //joe.zy.chen 2019/02/21
{
    inx_ui4_ir_key_flag = u4Val;
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
/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_fac_get_ir_key_flag
 * Description: 
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/
UINT32 inx_cfg_cust_fac_get_ir_key_flag(VOID) //joe.zy.chen 2019/02/21
{
    return inx_ui4_ir_key_flag;
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

typedef void* pinifile_data;

struct inifile_entry
{
    const char* entry_name;
    const char* entry_value;
    struct inifile_entry* next_entry;
};

struct inifile_section
{
    const char* section_name;
    struct inifile_entry* first_entry;
    struct inifile_section* next_section;
};

struct inifile_data
{
    struct inifile_section* first_section;
};

void close_ini_file(pinifile_data inidb)
{
    struct inifile_data* pinidb = (struct inifile_data*)inidb;
    if(pinidb == NULL)
        return;

    struct inifile_section* pnext_s = NULL, * pcur_s = NULL;
    struct inifile_entry* pnext_e = NULL, * pcur_e = NULL;

    pcur_s = pinidb->first_section;
    while(pcur_s != NULL)
    {
        pnext_s = pcur_s->next_section;

        pcur_e = pcur_s->first_entry;
        while(pcur_e != NULL)
        {
            pnext_e = pcur_e->next_entry;
            if(pcur_e->entry_name != NULL)
                free((void*)pcur_e->entry_name);
            if(pcur_e->entry_value != NULL)
                free((void*)pcur_e->entry_value);
            free((void*)pcur_e);
            pcur_e = pnext_e;
        }
        if(pcur_s->section_name != NULL)
            free((void*)pcur_s->section_name); 
        free((void*)pcur_s);
        pcur_s = pnext_s;
    }
    free((void*)pinidb);
}

void init_section(struct inifile_section* psection)
{
    psection->section_name = NULL;
    psection->first_entry = NULL;
    psection->next_section = NULL;
}

void init_entry(struct inifile_entry* pentry)
{
    pentry->entry_name = NULL;
    pentry->entry_value = NULL;
    pentry->next_entry = NULL;
}

enum parser_states
{
    comment = 0,
    linestart,
    sectionentry,
    entryname,
    entryvalue,
    states_number,
    end_of_file=255
};

#define MAX_BUFFER_SIZE 256

struct parser_state
{
    struct inifile_data context;
    struct inifile_section* section_cursor;
    struct inifile_entry* entry_cursor;
    char buffer[MAX_BUFFER_SIZE];
    int buffer_cursor;
};

typedef enum parser_states (*ini_file_state_transition)(char next_char, struct parser_state* pastate);

enum parser_states comment_state(char next_char, struct parser_state* pastate)
{
    if(next_char == '\n')
    {
        pastate->buffer_cursor = 0;
        return linestart;
    }
    return comment;
}

enum parser_states linestart_state(char next_char, struct parser_state* pastate)
{
    if(next_char == '\n')
    {
        pastate->buffer_cursor = 0;
        return linestart;
    }

    if(next_char == ';' || next_char == '#')
    {
        pastate->buffer_cursor = 0;
        return comment;
    }
    if(next_char == ']' || next_char == '=')
    {
        // this is error, discard the string
        pastate->buffer_cursor = 0;
        return comment;
    }

    if(isspace(next_char))
        return linestart;

    if(next_char == '[')
    {
        pastate->buffer_cursor = 0;
        return sectionentry;
    }
    // in all other cases, start of entry
    if(pastate->section_cursor == NULL)
    {
        //entries without section are not considered
        pastate->buffer_cursor = 0;
        return comment;
    }
    pastate->buffer[pastate->buffer_cursor++] = next_char;
    return entryname;
}

enum parser_states sectionentry_state(char next_char, struct parser_state* pastate)
{
    if(next_char == '\n')
    {
        // this is an error; data are discarded
        pastate->buffer_cursor = 0;
        return linestart;
    }

    if(next_char == '[' || next_char == ';' || next_char == '#')
        return comment;

    if(next_char != ']')
        pastate->buffer[pastate->buffer_cursor++] = next_char;
    // protection from buffer overflow
    if(next_char == ']' || pastate->buffer_cursor >= MAX_BUFFER_SIZE)
    {
        // this is section name's end
        // if we have non-empty name, create new section
        if(pastate->buffer_cursor > 0)
        {
            // prepare next section
            if(pastate->section_cursor == NULL)
            {
                // make first section
                pastate->context.first_section = (struct inifile_section*)malloc(sizeof(struct inifile_section));
                init_section(pastate->context.first_section);
                pastate->section_cursor = pastate->context.first_section;
            }
            else
            {
                pastate->section_cursor->next_section = (struct inifile_section*)malloc(sizeof(struct inifile_section));
                init_section(pastate->section_cursor->next_section);
                pastate->section_cursor = pastate->section_cursor->next_section;
            }
            pastate->entry_cursor = NULL;
            pastate->section_cursor->section_name = (char*)malloc(pastate->buffer_cursor + 1);
            memcpy((void*)pastate->section_cursor->section_name, pastate->buffer, pastate->buffer_cursor);
            *(char*)(pastate->section_cursor->section_name + pastate->buffer_cursor) = '\0';
        }
        // discard the rest of the string
        return comment;
    }

    return sectionentry;
}

enum parser_states entryname_state(char next_char, struct parser_state* pastate)
{
    if(next_char == '\n')
    {
        // this is an error; data are discarded
        pastate->buffer_cursor = 0;
        return linestart;
    }
    if(next_char == ';' || next_char == '[' || next_char == ']' || next_char == '#')
    {
        // this is an error; data are discarded
        pastate->buffer_cursor = 0;
        return comment;
    }
    if(next_char != '=')
        pastate->buffer[pastate->buffer_cursor++] = next_char;
    // protection from buffer overflow
    if(pastate->buffer_cursor >= MAX_BUFFER_SIZE)
    {
        // too long, discard everything
        pastate->buffer_cursor = 0;
        return comment;
    }

    if(next_char == '=')
    {
        // make new entry
        if(pastate->entry_cursor == NULL)
        {
            // make first entry
            pastate->section_cursor->first_entry = (struct inifile_entry*)malloc(sizeof(struct inifile_entry));
            init_entry(pastate->section_cursor->first_entry);
            pastate->entry_cursor = pastate->section_cursor->first_entry;
        }
        else
        {
            pastate->entry_cursor->next_entry = (struct inifile_entry*)malloc(sizeof(struct inifile_entry));
            init_entry(pastate->entry_cursor->next_entry);
            pastate->entry_cursor = pastate->entry_cursor->next_entry;
        }
        pastate->entry_cursor->entry_name = (char*)malloc(pastate->buffer_cursor + 1);
        
        // remove redundant space of entry_name, zl
        //memcpy((void*)pastate->entry_cursor->entry_name, pastate->buffer, pastate->buffer_cursor);
		char *token = strtok(pastate->buffer, " ");
		memcpy((void*)pastate->entry_cursor->entry_name, token, pastate->buffer_cursor);        					
        *(char*)(pastate->entry_cursor->entry_name + pastate->buffer_cursor) = '\0';
        pastate->buffer_cursor = 0;
        return entryvalue;
    }
    return entryname;
}

enum parser_states entryvalue_state(char next_char, struct parser_state* pastate)
{
    enum parser_states res = entryvalue;
    //printf("%d, next_char='%c'(0x%02X)\n", __LINE__, next_char, next_char);
    if(next_char == '\n')
    {
        res = linestart;
    }
    else if(next_char == EOF)
    {
        // handle the last entry without newline
        res = end_of_file;
    }
    else if(next_char == ';' || next_char == '#')
    {
        res = comment;
    }
    else
    {
        pastate->buffer[pastate->buffer_cursor++] = next_char;
        if(pastate->buffer_cursor >= MAX_BUFFER_SIZE)
            res = comment;
    }
    if(res != entryvalue)
    {
        pastate->entry_cursor->entry_value = (char*)malloc(pastate->buffer_cursor + 1);
        memcpy((void*)pastate->entry_cursor->entry_value, pastate->buffer, pastate->buffer_cursor);
        *(char*)(pastate->entry_cursor->entry_value + pastate->buffer_cursor) = '\0';
        pastate->buffer_cursor = 0;
    }

    return res;
}

int open_ini_file(const char* fname, pinifile_data* pinidb)
{
    if(fname == NULL || pinidb == NULL)
        return 2;

    FILE* fstream = fopen(fname, "r");
    if(!fstream)
        return 1;

    struct parser_state context;
    memset(&context, 0, sizeof(struct parser_state));
    int character = 0;
    enum parser_states state_index = linestart;
    ini_file_state_transition parse_functions_table[] = {
        comment_state,
        linestart_state,
        sectionentry_state,
        entryname_state,
        entryvalue_state
    };
    do
    {
        character = fgetc(fstream);
        if(character != EOF)
        {
            state_index = parse_functions_table[state_index](character, &context);
        }
        else{
            // handle last entry without newline, zlhuang, 20210610
            if(state_index == entryvalue){
                state_index = entryvalue_state(character, &context);
            }           
        }
    } while(!(feof(fstream) || ferror(fstream)));
    fclose(fstream);

    *pinidb = malloc(sizeof(struct inifile_data));
    // here we are copying a pointer, yes
    memcpy(*pinidb, &context.context, sizeof(struct inifile_data));

    return 0;    
}

const char* get_value(const pinifile_data inidb, const char* section, const char* entry)
{
    struct inifile_data* pinidb = (struct inifile_data*)inidb;
    if(pinidb == NULL || section == NULL || entry == NULL)
        return NULL;

    struct inifile_section* pcur_s = NULL;
    struct inifile_entry* pcur_e = NULL;

    pcur_s = pinidb->first_section;
    while(pcur_s != NULL)
    {
        pcur_e = pcur_s->first_entry;

        if(!strcmp(section, pcur_s->section_name)){
            while(pcur_e != NULL)
            {
                if(!strcmp(entry, pcur_e->entry_name)){
					// remove spaces and double quotes(") of entry_value, zl
					//return pcur_e->entry_value;
					char *token = strtok(pcur_e->entry_value, " \"");
                    return token;
                }    
                
                pcur_e = pcur_e->next_entry;
            }
        }
        pcur_s = pcur_s->next_section;
    }
    return NULL;

}

pinifile_data create_inidb()
{
    void* result = malloc(sizeof(struct inifile_data));
    memset(result, 0, sizeof(struct inifile_data));
    return result;
}

INT32 a_cfg_cust_info_get_customer_ini_root(CHAR * ps_str)
{
    //INT32       i4_ret       = 0;
    //UINT32      ui4_group_id = 0;
    //UINT32      ui4_model_id = 0;
    //CHAR        s_str[MI_INI_FILE_PATH_LEN+1] = {0};
    
   
	c_strncpy(ps_str,MI_INI_CONFIG_PATH,MI_INI_FILE_PATH_LEN);

    return APP_CFGR_OK;
}

char* a_cfg_cust_info_get_ini_item_value(CHAR * iniFile,CHAR * iniSectionName,CHAR * iniItemName)
{
    UINT32    i4_ret = 0;
    static char ret_str[MI_INI_FILE_PATH_LEN+1];
    char ini_root_path[MI_INI_FILE_PATH_LEN+1]={};
    char ini_full_path[MI_INI_FILE_PATH_LEN+1]={};

    //init
    memset(ret_str,0,MI_INI_FILE_PATH_LEN+1);

    //get ini path
    a_cfg_cust_info_get_customer_ini_root(ini_root_path);
    c_sprintf(ini_full_path,"%s%s",ini_root_path,iniFile);
    DBG_LOG_PRINT(("[ACFG] %s(),%d: ini_full_path=%s\r\n", __FUNCTION__, __LINE__, ini_full_path));

    //read item from ini file
    pinifile_data inidb;
    i4_ret =open_ini_file(ini_full_path, &inidb);
    DBG_LOG_PRINT(("[ACFG] %s(),%d\r\n", __FUNCTION__, __LINE__));
    if(i4_ret != 0){
        return NULL;
    }
    DBG_LOG_PRINT(("[ACFG] %s(),%d\r\n", __FUNCTION__, __LINE__));
    const char *ps_value = get_value(inidb, iniSectionName, iniItemName);
    if(ps_value == NULL){
    	close_ini_file(inidb);
	return NULL;
    }

    c_strncpy(ret_str,ps_value,MI_INI_FILE_PATH_LEN);
    DBG_LOG_PRINT(("[ACFG] %s(),%d\r\n", __FUNCTION__, __LINE__));
    close_ini_file(inidb);
    return ret_str;
}

char* a_cfg_cust_info_get_ini_panel_name(void)
{
    char *tmp_p;
    UINT32 ui4_model_index;
    char model_index_buf[32]={};

    a_cfg_custom_get_model_index(&ui4_model_index);
    c_sprintf(model_index_buf,"innolux_modelIndex%d",ui4_model_index);
    tmp_p = a_cfg_cust_info_get_ini_item_value("panel_name.ini","panel_name",model_index_buf);

    return tmp_p;
}

void a_cfg_cust_info_get_ini_item_string(CHAR * ini_full_path, CHAR * iniSectionName,CHAR * iniItemName, CHAR *str_default, CHAR *str_buf, INT32 str_len)
{
    UINT32    i4_ret = 0;

    //read item from ini file
    pinifile_data inidb;
    i4_ret =open_ini_file(ini_full_path, &inidb);
    if(i4_ret != 0){
		printf("[ACFG] %s(),%d\r\n", __FUNCTION__, __LINE__);
        c_strncpy(str_buf, str_default, strlen(str_default));
	    return;
    }
    const char *ps_value = get_value(inidb, iniSectionName, iniItemName);
    if(ps_value == NULL){
		printf("[ACFG] %s(),%d\r\n", __FUNCTION__, __LINE__);
   	   	close_ini_file(inidb);
        	c_memset(str_buf, 0, str_len); //init 
   	   	c_strncpy(str_buf, str_default, strlen(str_default));
	    return;
    }

    c_strncpy(str_buf, ps_value, str_len);
    close_ini_file(inidb);
}

INT32 a_cfg_cust_info_get_ini_item_integer(CHAR * ini_full_path, CHAR * iniSectionName, CHAR * iniItemName, INT32 integer_default)
{
    UINT32    i4_ret = 0;

    //read item from ini file
    pinifile_data inidb;
    i4_ret =open_ini_file(ini_full_path, &inidb);
    if(i4_ret != 0){
		printf("[ACFG] %s(),%d\r\n", __FUNCTION__, __LINE__);
        return integer_default;
    }

	const char* evalue = get_value(inidb, iniSectionName, iniItemName);
	if(!evalue){
		printf("[ACFG] %s(),%d\r\n", __FUNCTION__, __LINE__);
   	   	close_ini_file(inidb);
	    return integer_default;
	}
	
    i4_ret = strtol(evalue, NULL, 10);
    close_ini_file(inidb);
	return i4_ret;

}

char* a_cfg_cust_info_get_all_ini_item_value(CHAR * iniFile,CHAR * iniSectionName,CHAR * iniItemName)
{
    UINT32    i4_ret = 0;
    static char ret_str[MI_INI_FILE_PATH_LEN+1];

    //init
    memset(ret_str,0,MI_INI_FILE_PATH_LEN+1);

    //read item from ini file
    pinifile_data inidb;
    i4_ret =open_ini_file(iniFile, &inidb);
    if(i4_ret != 0){
        return NULL;
    }
    
    const char *ps_value = get_value(inidb, iniSectionName, iniItemName);
    if(ps_value == NULL){
    	close_ini_file(inidb);
	    return NULL;
    }

    c_strncpy(ret_str,ps_value,MI_INI_FILE_PATH_LEN);
    close_ini_file(inidb);
    return ret_str;
}

////////////////////////////////////////////////////////////////////////////////

//tftp server///////////////////////////////////////////////////////////////////
#define RECV_TIMEOUT 5
#define RECV_RETRIES 5

/* tftp opcode mnemonic */
enum opcode {
     RRQ=1,
     WRQ,
     DATA,
     ACK,
     ERROR
};

/* tftp transfer mode */
enum mode {
     NETASCII=1,
     OCTET
};

/* tftp message structure */
typedef union {

     uint16_t opcode;

     struct {
          uint16_t opcode; /* RRQ or WRQ */             
          uint8_t filename_and_mode[514];
     } request;     

     struct {
          uint16_t opcode; /* DATA */
          uint16_t block_number;
          uint8_t data[512];
     } data;

     struct {
          uint16_t opcode; /* ACK */             
          uint16_t block_number;
     } ack;

     struct {
          uint16_t opcode; /* ERROR */     
          uint16_t error_code;
          uint8_t error_string[512];
     } error;

} tftp_message;

/* base directory */
char *base_directory;

/* pthread global var */
pthread_t tftps_pthread;

/* tftp server socket */
int tftps_sock;

void cld_handler(int sig) {
     int status;
     wait(&status);
}

ssize_t tftp_send_data(int s, uint16_t block_number, uint8_t *data,
                       ssize_t dlen, struct sockaddr_in *sock, socklen_t slen)
{
     tftp_message m;
     ssize_t c;

     m.opcode = htons(DATA);
     m.data.block_number = htons(block_number);
     memcpy(m.data.data, data, dlen);

     if ((c = sendto(s, &m, 4 + dlen, 0,
                     (struct sockaddr *) sock, slen)) < 0) {
          perror("server: sendto()");
     }

     return c;
}

ssize_t tftp_send_ack(int s, uint16_t block_number,
                      struct sockaddr_in *sock, socklen_t slen)
{
     tftp_message m;
     ssize_t c;

     m.opcode = htons(ACK);
     m.ack.block_number = htons(block_number);

     if ((c = sendto(s, &m, sizeof(m.ack), 0,
                     (struct sockaddr *) sock, slen)) < 0) {
          perror("server: sendto()");
     }

     return c;
}

void tftp_send_error(int s, int error_code, char *error_string,
                        struct sockaddr_in *sock, socklen_t slen)
{
     tftp_message m;
     ssize_t c;

     if(strlen(error_string) >= 512) {
          fprintf(stderr, "server: tftp_send_error(): error string too long\n");
          //return -1;
	      return;
     }

     m.opcode = htons(ERROR);
     m.error.error_code = error_code;
     strcpy(m.error.error_string, error_string);

     if ((c = sendto(s, &m, 4 + strlen(error_string) + 1, 0,
                     (struct sockaddr *) sock, slen)) < 0) {
          perror("server: sendto()");
     }

     //return c;
     return;
}

ssize_t tftp_recv_message(int s, tftp_message *m, struct sockaddr_in *sock, socklen_t *slen)
{
     ssize_t c;

     if ((c = recvfrom(s, m, sizeof(*m), 0, (struct sockaddr *) sock, slen)) < 0
          && errno != EAGAIN) {
          perror("server: recvfrom()");
     }

     return c;
}

void tftp_handle_request(tftp_message *m, ssize_t len,
                         struct sockaddr_in *client_sock, socklen_t slen)
{
     int s;
     struct protoent *pp;
     struct timeval tv;

     char *filename, *mode_s, *end;
     FILE *fd;

     int mode;
     uint16_t opcode;

     /* open new socket, on new port, to handle client request */

     if ((pp = getprotobyname("udp")) == 0) {
          fprintf(stderr, "server: getprotobyname() error\n");
          return;
     }

     if ((s = socket(AF_INET, SOCK_DGRAM, pp->p_proto)) == -1) {
          perror("server: socket()");
          return;
     }

     tv.tv_sec  = RECV_TIMEOUT;
     tv.tv_usec = 0;

     if(setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
          perror("server: setsockopt()");
          goto out;
     }

     /* parse client request */

     filename = m->request.filename_and_mode;
     end = &filename[len - 2 - 1];

     if (*end != '\0') {
          printf("%s.%u: invalid filename or mode\n",
                 inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
          tftp_send_error(s, 0, "invalid filename or mode", client_sock, slen);
          goto out;
     }

     mode_s = strchr(filename, '\0') + 1; 

     if (mode_s > end) {
          printf("%s.%u: transfer mode not specified\n",
                 inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
          tftp_send_error(s, 0, "transfer mode not specified", client_sock, slen);
          goto out;
     }

     if(strncmp(filename, "../", 3) == 0 || strstr(filename, "/../") != NULL ||
        (filename[0] == '/' && strncmp(filename, base_directory, strlen(base_directory)) != 0)) {
          printf("%s.%u: filename outside base directory\n",
                 inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
          tftp_send_error(s, 0, "filename outside base directory", client_sock, slen);
          goto out;
     }

     opcode = ntohs(m->opcode);
     fd = fopen(filename, opcode == RRQ ? "r" : "w"); 

     if (fd == NULL) {
          perror("server: fopen()");
          tftp_send_error(s, errno, strerror(errno), client_sock, slen);
          goto out;
     }

     mode = strcasecmp(mode_s, "netascii") ? NETASCII :
          strcasecmp(mode_s, "octet")    ? OCTET    :
          0;

     if (mode == 0) {
          printf("%s.%u: invalid transfer mode\n",
                 inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
          tftp_send_error(s, 0, "invalid transfer mode", client_sock, slen);
          goto out1;
     }

     printf("%s.%u: request received: %s '%s' %s\n", 
            inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port),
            ntohs(m->opcode) == RRQ ? "get" : "put", filename, mode_s);

     // TODO: add netascii handling

     if (opcode == RRQ) {
          tftp_message m;
          uint8_t data[512];
          ssize_t dlen, c;
          uint16_t block_number = 0;
          int countdown;
          int to_close = 0;

          while (!to_close) {
               dlen = fread(data, 1, sizeof(data), fd);
               block_number++;

               if (dlen < 512) { // last data block to send
                    to_close = 1;
               }

               for (countdown = RECV_RETRIES; countdown; countdown--) {
                    c = tftp_send_data(s, block_number, data, dlen, client_sock, slen);
                    if (c < 0) {
                         printf("%s.%u: transfer killed\n",
                                inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                         goto out1;
                    }

                    c = tftp_recv_message(s, &m, client_sock, &slen);
                    if (c >= 0 && c < 4) {
                         printf("%s.%u: message with invalid size received\n",
                                inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                         tftp_send_error(s, 0, "invalid request size", client_sock, slen);
                         goto out1;
                    }

                    if (c >= 4) {
                         break;
                    }

                    if (errno != EAGAIN) {
                         printf("%s.%u: transfer killed\n",
                                inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                         goto out1;
                    }
               }

               if (!countdown) {
                    printf("%s.%u: transfer timed out\n",
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                    goto out1;
               }

               if (ntohs(m.opcode) == ERROR)  {
                    printf("%s.%u: error message received: %u %s\n",
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port),
                           ntohs(m.error.error_code), m.error.error_string);
                    goto out1;
               }

               if (ntohs(m.opcode) != ACK)  {
                    printf("%s.%u: invalid message during transfer received\n",
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                    tftp_send_error(s, 0, "invalid message during transfer", client_sock, slen);
                    goto out1;
               }

               if (ntohs(m.ack.block_number) != block_number) { // the ack number is too high
                    printf("%s.%u: invalid ack number received\n",
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                    tftp_send_error(s, 0, "invalid ack number", client_sock, slen);
                    goto out1;
               }
          }
     } else if (opcode == WRQ) {
          tftp_message m;
          ssize_t c;
          uint16_t block_number = 0;
          int countdown;
          int to_close = 0;

          c = tftp_send_ack(s, block_number, client_sock, slen);
          if (c < 0) {
               printf("%s.%u: transfer killed\n",
                      inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
               goto out1;
          }

          while (!to_close) {
               for (countdown = RECV_RETRIES; countdown; countdown--) {
                    c = tftp_recv_message(s, &m, client_sock, &slen);
                    if (c >= 0 && c < 4) {
                         printf("%s.%u: message with invalid size received\n",
                                inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                         tftp_send_error(s, 0, "invalid request size", client_sock, slen);
                         goto out1;
                    }

                    if (c >= 4) {
                         break;
                    }

                    if (errno != EAGAIN) {
                         printf("%s.%u: transfer killed\n",
                                inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                         goto out1;
                    }

                    c = tftp_send_ack(s, block_number, client_sock, slen);
                    if (c < 0) {
                         printf("%s.%u: transfer killed\n",
                                inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                         goto out1;
                    }
               }

               if (!countdown) {
                    printf("%s.%u: transfer timed out\n",
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                    goto out1;
               }
               block_number++;

               if (c < sizeof(m.data)) {
                    to_close = 1;
               }

               if (ntohs(m.opcode) == ERROR)  {
                    printf("%s.%u: error message received: %u %s\n",
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port),
                           ntohs(m.error.error_code), m.error.error_string);
                    goto out1;
               }

               if (ntohs(m.opcode) != DATA)  {
                    printf("%s.%u: invalid message during transfer received\n",
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                    tftp_send_error(s, 0, "invalid message during transfer", client_sock, slen);
                    goto out1;
               }

               if (ntohs(m.ack.block_number) != block_number) {
                    printf("%s.%u: invalid block number received\n", 
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                    tftp_send_error(s, 0, "invalid block number", client_sock, slen);
                    goto out1;
               }

               c = fwrite(m.data.data, 1, c - 4, fd);
               if (c < 0) {
                    perror("server: fwrite()");
                    goto out1;
               }

               c = tftp_send_ack(s, block_number, client_sock, slen);
               if (c < 0) {
                    printf("%s.%u: transfer killed\n",
                           inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
                    goto out1;
               }
          }
     }
     printf("%s.%u: transfer completed\n",
            inet_ntoa(client_sock->sin_addr), ntohs(client_sock->sin_port));
out1:
     fclose(fd);
out:
     close(s);
     return;
}

int a_cfg_cust_pthread_tftps_main(int argc, char *argv[])
{
    uint16_t port = 0;
    struct protoent *pp;
    struct servent *ss;
    struct sockaddr_in server_sock;

    if (argc < 2) {
        printf("usage:\n\t%s [base directory] [port]\n", argv[0]);
        pthread_exit(NULL);
    }

    base_directory = argv[1];
    printf("%s() : dir : %s\n",__func__,base_directory);

    if (chdir(base_directory) < 0) {
        perror("server: chdir()");
        pthread_exit(NULL);
    }

    if (argc > 2) {
        if (sscanf(argv[2], "%hu", &port)) {
            port = htons(port);
        } else {
            fprintf(stderr, "error: invalid port number\n");
            pthread_exit(NULL);
        }
    } else {
        if ((ss = getservbyname("tftp", "udp")) == 0) {
            fprintf(stderr, "server: getservbyname() error\n");
            pthread_exit(NULL);
        }
        port = ss->s_port;
    }

    // just in case the port is invalid, zl
    if (port == 0) {
        fprintf(stderr, "server: port config error\n");
        pthread_exit(NULL);
    }

    if ((pp = getprotobyname("udp")) == 0) {
        fprintf(stderr, "server: getprotobyname() error\n");
        pthread_exit(NULL);
    }

    if ((tftps_sock = socket(AF_INET, SOCK_DGRAM, pp->p_proto)) == -1) {
        perror("server: socket() error");
        pthread_exit(NULL);
    }

    // fix 'already in use' when socket binding, zl
    int option = 1;
    int sock_ret;//truedano add : fix mtk warning
    sock_ret = setsockopt(tftps_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    if( sock_ret != 0 ){//truedano add : fix mtk warning
        perror("server: setsockopt() error");
        pthread_exit(NULL);
    }

    server_sock.sin_family = AF_INET;
    server_sock.sin_addr.s_addr = htonl(INADDR_ANY);
    server_sock.sin_port = port;

    if (bind(tftps_sock, (struct sockaddr *) &server_sock, sizeof(server_sock)) == -1) {
        perror("server: bind()");
        close(tftps_sock);
        pthread_exit(NULL);
    }

    signal(SIGCLD, (void *) cld_handler) ;

    printf("tftp server: listening on %d\n", ntohs(server_sock.sin_port));

    while (1) {
        struct sockaddr_in client_sock;
        socklen_t slen = sizeof(client_sock);
        ssize_t len;

        tftp_message message;
        uint16_t opcode;

        if ((len = tftp_recv_message(tftps_sock, &message, &client_sock, &slen)) < 0) {
            continue;
        }

        if (len < 4) { 
           printf("%s.%u: request with invalid size received\n",
                  inet_ntoa(client_sock.sin_addr), ntohs(client_sock.sin_port));
           tftp_send_error(tftps_sock, 0, "invalid request size", &client_sock, slen);
           continue;
        }

        opcode = ntohs(message.opcode);

        if (opcode == RRQ || opcode == WRQ) {

           /* spawn a child process to handle the request */

           //if (fork() == 0) {
                tftp_handle_request(&message, len, &client_sock, slen);
           //     exit(0);
           //}

        }

        else {
           printf("%s.%u: invalid request received: opcode %d\n", 
                  inet_ntoa(client_sock.sin_addr), ntohs(client_sock.sin_port),
                  opcode);
           tftp_send_error(tftps_sock, 0, "invalid opcode", &client_sock, slen);
        }

    }

    close(tftps_sock);

    pthread_exit(NULL);
}

void a_cfg_cust_pthread_tftps_child(void* data)
{
    int argc = 3;
    char *argv[]={"tftpserv","/","1234"};
    
    a_cfg_cust_pthread_tftps_main(argc,argv);
    
}

void a_cfg_cust_pthread_tftps_create(void)
{
    printf("%s() : pthread : %ld\n",__func__,tftps_pthread);
    if( tftps_pthread == 0 ){
        pthread_create(&tftps_pthread, NULL, a_cfg_cust_pthread_tftps_child, "tftp server child");
        printf("%s() : pthread_create\n",__func__);
    }
}

void a_cfg_cust_pthread_tftps_cancel(void)
{
    int p_ret;
    
    printf("%s() : pthread : %ld\n",__func__,tftps_pthread);
    if( tftps_pthread ){
        p_ret = pthread_cancel(tftps_pthread);
        tftps_pthread = 0;
        close(tftps_sock);
        printf("%s() : close sock : %d\n",__func__,tftps_sock);
        if( p_ret != 0 ){
            printf("%s() : pthread_cancel error : %d\n",__func__,p_ret);
            return;
        }
    }
}
//tftp server///////////////////////////////////////////////////////////////////
      
void a_cfg_cust_get_format_time(CHAR *buf)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p=localtime(&timep);

    sprintf (buf, "%d%02d%02d%02d%02d", 
        (1900+p->tm_year),( 1+p->tm_mon), p->tm_mday,p->tm_hour, p->tm_min);
    //return buf;
}

void a_cfg_cust_get_format_time_at_cmd_log(CHAR *buf)
{
    time_t timep;
    struct tm *p;
    time(&timep);
    p=localtime(&timep);
    struct timeval te;
    gettimeofday(&te, NULL);
    long long msec = te.tv_sec*1000LL + te.tv_usec/1000;

    sprintf (buf, "%d/%02d/%02d %02d:%02d:%02d.%d%d%d",
        (1900+p->tm_year),( 1+p->tm_mon), p->tm_mday,p->tm_hour, p->tm_min, p->tm_sec, (int)(msec/100%10), (int)(msec/10%10), (int)(msec%10) );
    //return buf;
}
/*-----------------------------------------------------------------------------
 * Name: a_cfg_cust_disp_screen
 * Description: This function can set flag to 0xFFE0B = 1
 * Inputs: -
 * Outputs: -
 * Returns:
 ----------------------------------------------------------------------------*/

void a_cfg_cust_disp_screen(void)
{
	INT32 i4_Ret;
	DRV_CUST_OPERATION_INFO_T    t_op_info;
    UINT16 ui2_Burn_idx = 1;
    SIZE_T z_size = sizeof(ui2_Burn_idx);
    SIZE_T z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T); 
	c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));

	t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_TYPE_INFO_BURNIN_MODE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui2_Burn_idx;
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
        DBG_INFO(("<fac_parser> Set BurnIn mode failed !\n"));
    }
}
