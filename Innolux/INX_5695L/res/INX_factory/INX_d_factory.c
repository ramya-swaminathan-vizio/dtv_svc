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
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdarg.h>
#include <unistd.h>	
#include <stdlib.h>
#include <dirent.h>

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
#include "INX_d_factory.h"

#include  "menu2/menu_mtktvapi.h"//truedano

#include "res/menu2/menu_custom.h"//truedano
#include "app_util/mtktvapi/a_mtktvapi_cec.h"//truedano
#include "menu2/menu_dbg.h"//truedano
#include "rest/a_rest_event.h"//truedano
#include "wizard_anim/wzd.h"		//mind 20160512
#include "wizard_anim/a_wzd.h"

#include "u_drv_cust.h"
#include "c_rm.h"
#include "u_rm_dev_types.h"
#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"
#include "INX_fac_menu/INX_fac.h"
#include "INX_fac_mlm.h"
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
#include "c_cecm.h"//truedano
#include "nav/cec2/nav_cec.h"//truedano
#include "nav/cec2/a_nav_cec.h"//truedano
#endif
#endif
#endif
#include "INX_fac_camera.h"
#include "app_util/config/acfg_cust_factory.h"  

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
//#define HDMI_EDID_DATA 256
//#define VGA_EDID_DATA 128
extern const UINT8 ui1_INX_color_eep_offset[COLOR_TUNER_FAC_TEMP_NUM][COLOR_TUNER_FAC_PLAY_CONTENT_NUM];
static UINT32		ui4_dynamic_address = 0;
static INT16		i2_clr_temp = 0;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/


//yshu add set hdr max nits 20180809
/*-----------------------------------------------------------------------------
* Name a_cfg_custom_set_HDR_panel_nits
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern INT32 a_cfg_custom_set_HDR_panel_nits(UINT32 u2Panelnist) 
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

    return i4_ret;
}

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
* Name a_cfg_custom_get_EXT_GAMMA_CHECK_ADDR
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_get_EXT_GAMMA_CHECK_ADDR(UINT32 *pui4_exit_gamma_index)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(pui4_exit_gamma_index);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_Get_EXIT_GAMMA_ADDR;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_exit_gamma_index;
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
* Name a_cfg_custom_set_ELCS_Control
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_set_ELCS_Control(MISC_TYPE_SIF_ADVANCED_T *ui4_mtk_cust_elcs)
{
    INT32   i4_ret = 0;

#ifdef NEVER
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui4_mtk_cust_elcs);
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_OPERATION_TYPE_SIF_WRITE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)ui4_mtk_cust_elcs;
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
#endif /* NEVER */
    
    return i4_ret;
}


/*-----------------------------------------------------------------------------
* Name: a_cfg_custom_Set_Factory_PQbypass_OnOff
* Description: enable/disable PQ bypss
* Input arguments: 0: disable, 1: enable
* Output arguments: N/A
* Returns: N/A
*---------------------------------------------------------------------------*/
extern VOID a_cfg_custom_Set_Factory_PQbypass_OnOff(BOOL bOnOff)  //Ben 20180416
{
	int TconLessFlag = 0;
	TconLessFlag = a_cfg_cust_info_get_ini_item_integer("/config/board.ini","DispoutConfig", "m_bTconOutput", 0);
	if(TconLessFlag == 1)
	{
 		// MTK reference code for PQ requirement: ELCS and WT(panel gamma) are not bypassed for TCON-less
		INT32 i4_ret=0;
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
		DBG_LOG_PRINT(("[INX_d_factory.c] %s,i4_ret :%d\r\n",__FUNCTION__,i4_ret));

	}
	else
	{
		// normal TCON PQ bypass
		a_cfg_cust_drv_set_pq_bypass((UINT8)bOnOff);
	}
}


/*-----------------------------------------------------------------------------
* Name a_cfg_custom_set_MTK_CUST_ADDR
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 a_cfg_custom_set_MTK_CUST_ADDR(UINT32 ui4_mtk_cust_addr)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size = sizeof(ui4_mtk_cust_addr);
    
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_CUST_SPEC_Set_MTK_CUST_ADDR;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&ui4_mtk_cust_addr;
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
* Name _a_cfg_custom_get_MTK_CUST_ADDR
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 _a_cfg_custom_get_MTK_CUST_ADDR(UINT32 *pui4_mtk_cust_addr)
{
    INT32   i4_ret;
    DRV_CUST_OPERATION_INFO_T    t_op_info={0};
    SIZE_T      z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T      z_size = sizeof(pui4_mtk_cust_addr);

    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_Get_MTK_CUST_ADDR;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = (VOID *)pui4_mtk_cust_addr;
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
* Name a_cfg_custom_get_MTK_CUST_ADDR
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern VOID a_cfg_custom_get_MTK_CUST_ADDR(DRV_CUSTOM_MTK_CUST_ADDR_T addr,UINT32 *pui4_mtk_cust_addr)
{
    a_cfg_custom_set_MTK_CUST_ADDR(addr);
    _a_cfg_custom_get_MTK_CUST_ADDR(pui4_mtk_cust_addr);
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
    inx_system("sync; sync; sync");
    a_cfg_store();
	
    return i4_ret;
}
/*-----------------------------------------------------------------------------
* Name INX_d_get_RJ45_addr
* Description
* Input arguments
* Output arguments
* Returns
* 
*---------------------------------------------------------------------------*/
extern UINT32 INX_d_get_RJ45_addr(UINT32 *pui4_mac_addr) //ke_vizio_20160428
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

/*----------------------------------------------------------------------------
 * Name: _set_aud_speaker_idx_inx_AT
 *
 * Description: 
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *          
 ----------------------------------------------------------------------------*/
extern VOID _set_aud_speaker_idx_inx_AT(UINT16 ui2_idx)
{
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_OUT_PORT);
    UINT16          ui2_aud_out_mask;
    INT16           i2_val;
    INT32           i4_ret = 0;
    UINT8           ui1_icl_val = ICL_CEC_SAC_STATUS_OFF;
    SIZE_T          z_size = sizeof(UINT8);
    UINT8           ui1_sac_func = 0;

    a_cfg_av_get(ui2_id, &i2_val);
    ui2_aud_out_mask = (UINT16)i2_val;

    i4_ret = a_cfg_get_cec_sac_func(&ui1_sac_func);
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_LOG_PRINT(("%s,%d get cec sac func fail i4_ret=%d \r\n",__FUNCTION__,__LINE__,i4_ret));
        return ;
    }

    if(ui2_idx == 2)
    {
        /* Off */
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);
	#if defined(APP_CEC_SUPPORT) && defined(APP_CEC2_SUPPORT)		
        #ifdef APP_ARC_ONLY

        UINT8 ui1_cec_func=0;

        a_cfg_get_cec_func (&ui1_cec_func);
        if((ui1_cec_func != APP_CFG_CEC_OFF) && (ui1_sac_func == APP_CFG_CEC_OFF))
        {
            /* Turn on CEC SAC */
            a_cfg_set_cec_sac_func(1);
        }

        #endif
	#endif
	    a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_OFF);
             rest_event_notify("tv_settings/audio/tv_speakers",0 ,"Off");
    }
    else if(ui2_idx == 1)
    {
        /* On */
        ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);
    #if defined(APP_CEC_SUPPORT) && defined(APP_CEC2_SUPPORT)
        /* Turn off CEC SAC */
        if(ui1_sac_func == APP_CFG_CEC_ON)
        {
            a_cfg_set_cec_sac_func(0);
        }
        #ifdef APP_ARC_ONLY
        /*power off CEC audio receiver/ soundbar when turn on speaker*/
        c_cecm_set_standby(nav_cec_get_mw_handle(), CECM_LOG_ADDR_AUD_SYS);
        DBG_LOG_PRINT(("%s,%d c_cecm_set_standby\n\r",__FUNCTION__,__LINE__));

        CECM_SYS_AUD_CTRL_T t_sys_aud_ctrl;
        t_sys_aud_ctrl.e_aud_ctrl = CECM_SYS_AUD_STS_OFF;
        c_cecm_set_system_audio_mode_request(nav_cec_get_mw_handle(), &t_sys_aud_ctrl);
        DBG_LOG_PRINT(("%s,%d c_cecm_set_system_audio_mode_request\n\r",__FUNCTION__,__LINE__));

        NAV_CEC_EX_CTRL_PARAM_T t_param;
        NAV_CEC_EX_CTRL_RESULT_T t_result;
        t_param.e_cmd = NAV_CEC_EX_CTRL_CMD_SET_SAM_STATUS_OFF;
        i4_ret = a_nav_cec_do_ex_ctrl(&t_param, &t_result);
        DBG_LOG_PRINT(("%s,%d a_nav_cec_do_ex_ctrl NAV_CEC_EX_CTRL_CMD_SET_SAM_STATUS_OFF ret %d\n\r",__FUNCTION__,__LINE__, i4_ret));
        #endif
    #endif

        a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_ON);
        rest_event_notify("tv_settings/audio/tv_speakers",0 ,"On");
    }
    else if(ui2_idx == 0)
    {
        // get is or not cec device connected
        z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
        i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                           &ui1_icl_val,
                           &z_size);
        if(i4_ret != ICLR_OK)
        {
            DBG_INFO((" [tv speaker] get sac status icl fail \n"));
        }

        if(ui1_sac_func == APP_CFG_CEC_OFF)
        {
            a_cfg_set_cec_sac_func(1);
        }

        DBG_LOG_PRINT(("%s,%d [tv speaker] icl_sac_status=%d \n",__FUNCTION__,__LINE__,ui1_icl_val));
        if(ICL_CEC_SAC_STATUS_ON == ui1_icl_val)
        {
            // set_aud_speaker_status(0), Just like set tv speaker off
            ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask & ~SCC_AUD_OUT_PORT_SPEAKER);
        }
        else
        {
            //AMP is disconnected. Just like set tv speaker on, tv speake audio, but sac set to 1.
            ui2_aud_out_mask = (UINT16)(ui2_aud_out_mask | SCC_AUD_OUT_PORT_SPEAKER);
        }
        a_cfg_custom_set_speakers_out(APP_CFG_AUD_AD_SPEAKER_AUTO);
        rest_event_notify("tv_settings/audio/tv_speakers",0 ,"Auto");
    }

    a_cfg_av_set(ui2_id, (INT16)ui2_aud_out_mask);
    a_cfg_av_update(ui2_id);
}
extern void a_cfg_custom_set_tconless_elcs_control_enable(UINT8 enable)
{
	INT32                        i4_ret = 0;
	DRV_CUST_OPERATION_INFO_T    t_op_info;
	SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
	SIZE_T 						 z_size = sizeof(enable);

	printf("%s:%d\n",__func__,__LINE__);
	c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info.u.t_cust_spec_set_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_ENHANCED_VIEWING_ANGLE;
    t_op_info.u.t_cust_spec_set_info.pv_set_info = (VOID *)&enable;
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
}
extern void a_cfg_custom_set_ELCS_Control_enable(UINT8 enable)
{
    INT32       i4_ret   = 0;
    MISC_TYPE_SIF_ADVANCED_T t_info;
    UINT8 u8Data[]        = {0xFE , 0xEA , 0x51 , enable};

    c_memset(&t_info, 0, sizeof(t_info));
    t_info.ui1_channel    = 0;
    t_info.ui2_clkdiv     = 0x10E; //100k
    t_info.ui4_addr       = 0xC2; //TCON Addr
    t_info.ui1_offset_len = 0;
    t_info.ui1_data_len   = 4;
    c_memcpy(t_info.pui1_data, u8Data, 4);

    //write sif data
    i4_ret = a_cfg_cust_set_sif_data(&t_info,sizeof(t_info));
    printf("[ACFG] %s,%d, enable=%d, i4_ret=%d\r\n",__FUNCTION__, __LINE__, enable, i4_ret);

}
extern void a_cfg_custom_control_ELCS(UINT8 enable)
{
	int TconLessFlag = 0;
	INT16   i2_pre_val = 0;
	TconLessFlag = a_cfg_cust_info_get_ini_item_integer("/config/board.ini","DispoutConfig", "m_bTconOutput", 0);
	if(TconLessFlag == 1)
	{
		// sync with UI
		a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), &i2_pre_val);
		a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), (INT16)enable);
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));
		if (i2_pre_val != enable)
    	{   
        	set_preset_pic_mode_chg_status(TRUE);
    	}
		a_cfg_custom_set_tconless_elcs_control_enable(enable);
	}
	else
    	a_cfg_custom_set_ELCS_Control_enable(enable);
}

extern INT32 a_cfg_custom_I2C_write(
UINT8 busID,UINT16 clk,UINT32 addr,UINT8 offset_len,
UINT32 offset,UINT8 data_len,UINT8 u8Data[])
{
    MISC_TYPE_SIF_ADVANCED_T t_info;
    UINT32 i;
    INT32 i4_ret;
    
    c_memset(&t_info, 0, sizeof(t_info));
    t_info.ui1_channel    = busID; //Bus ID
    t_info.ui2_clkdiv     = clk;   //Clock
    t_info.ui4_addr       = addr;  //Dev Addr
    t_info.ui1_offset_len = offset_len;
    t_info.ui4_offset     = offset;
    t_info.ui1_data_len   = data_len;
    c_memcpy(t_info.pui1_data, u8Data, data_len);

    //write sif data
    i4_ret = a_cfg_cust_set_sif_data(&t_info,sizeof(t_info));
    printf("I2C_write : busID=0x%x\n",busID);
    printf("I2C_write : clk=0x%x\n",clk);
    printf("I2C_write : addr=0x%x\n",addr);
    printf("I2C_write : offset_len=0x%x\n",offset_len);
    printf("I2C_write : offset=0x%x\n",offset);
    printf("I2C_write : data_len=%d\n",data_len);
    printf("I2C_write : u8Data=");
    for(i=0;i<data_len;i++){
        printf("%x ",u8Data[i]);
    }
    printf("\n");
    printf("I2C_write : i4_ret=%d\n",i4_ret);
    return i4_ret;
}

extern INT32 a_cfg_custom_I2C_read(
UINT8 busID,UINT16 clk,UINT32 addr,UINT8 offset_len,
UINT32 offset,UINT8 data_len,UINT8 u8Data[])
{
    MISC_TYPE_SIF_ADVANCED_T t_info;
    UINT32 i;
    INT32 i4_ret;
    
    c_memset(&t_info, 0, sizeof(t_info));
    t_info.ui1_channel    = busID; //Bus ID
    t_info.ui2_clkdiv     = clk;   //Clock
    t_info.ui4_addr       = addr;  //Dev Addr
    t_info.ui1_offset_len = offset_len;
    t_info.ui4_offset     = offset;
    t_info.ui1_data_len   = data_len;

    //write sif data
    i4_ret = a_cfg_cust_get_sif_data(&t_info,sizeof(t_info));
    printf("I2C_read : busID=0x%x\n",busID);
    printf("I2C_read : clk=0x%x\n",clk);
    printf("I2C_read : addr=0x%x\n",addr);
    printf("I2C_read : offset_len=0x%x\n",offset_len);
    printf("I2C_read : offset=0x%x\n",offset);
    printf("I2C_read : data_len=%d\n",data_len);
    c_memcpy(u8Data, t_info.pui1_data, data_len);
    printf("I2C_read : u8Data=");
    for(i=0;i<data_len;i++){
        printf("%x ",u8Data[i]);
    }
    printf("\n");
    printf("I2C_read : i4_ret=%d\n",i4_ret);
    return i4_ret;
}

/*-----------------------------------------------------------------------------
* Name a_cfg_custom_factory_reset_ex
* Description  :  Excute the command of factory reset.
* Input arguments  : void
* Output arguments : 
* Returns : "1" is returned for true,"0" is returned for false.
* 
*---------------------------------------------------------------------------*/
extern UINT8 a_cfg_custom_factory_reset_ex()
{
    INT32   i4_ret = 1;
    UINT32 ui4_eep_address = COMMON_EEP_INX_SELF_MAKE_BURNING_MODE_FLAG;
    UINT8 close_aging[1] = {0};
	UINT32 ui4_written;
	close_aging[0] = 0x00;
	i4_ret =  a_cfg_eep_raw_write(ui4_eep_address, close_aging, 1, &ui4_written);
	if(i4_ret !=0)
	{
		DBG_INFO(("!!!!%s a_cfg_eep_raw_write fail\n", __func__));
		return 0;
	}
	UINT32 ui4_written_on;
	ui4_eep_address = COMMON_EEP_INX_POWER_MODE_FLAG;
	UINT8 close_auto_on[1] = {0};
	i4_ret =  a_cfg_eep_raw_write(ui4_eep_address, close_auto_on, 1, &ui4_written_on);
	if(i4_ret !=0)
	{
		DBG_INFO(("!!!!%s a_cfg_eep_raw_write fail\n", __func__));
		return 0;
	}

    //Del At cmd log enable and file
    INX_AtCmdSetEnable(FALSE);
    INX_AtCmdDelLogFile();

    _nav_set_bluetooth_unpair();

    //camera motor down , if motor is up
    a_cam_mtk_motor_dlopen();
    a_cam_mtk_motor_down(CAM_MOTOR_MS);
    a_cam_mtk_motor_dlclose();

    i4_ret =  a_cfg_fac_reset();
	if(i4_ret !=0)
	{
		DBG_INFO(("!!!!%s a_cfg_eep_raw_write fail\n", __func__));
		return 0;
	}

#ifdef APP_C4TV_SUPPORT
	a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));	//mind 20160601
#endif
    a_cfg_store();
    
    menu_clear_memory_ex(FALSE);    // Ben 20180129
		
	// apply another MTK API to turn on backlight, MVV-7148, 20201116
	//a_cfg_cust_backlight_onoff(TRUE); 
	a_cfg_cust_unblank_screen();

	INX_nav_fac_urc_dialog_show(MLM_FAC_KEY_MSG_SHUT_DOWN);// show "turn off the power" on the screen display

    return 1;
}

/*-----------------------------------------------------------------------------
* Name a_cfg_custom_factory_reset
* Description  :  Excute the command of factory reset.
* Input arguments  : void
* Output arguments : 
* Returns : "1" is returned for true,"0" is returned for false.
* 
*---------------------------------------------------------------------------*/
extern UINT8 a_cfg_custom_factory_reset()
{
    INT32   i4_ret = 1;
    UINT32 ui4_eep_address = COMMON_EEP_INX_SELF_MAKE_BURNING_MODE_FLAG;
    UINT8 close_aging[1] = {0};
	UINT32 ui4_written;
	close_aging[0] = 0x00;
	i4_ret =  a_cfg_eep_raw_write(ui4_eep_address, close_aging, 1, &ui4_written);
	if(i4_ret !=0)
	{
		DBG_INFO(("!!!!%s a_cfg_eep_raw_write fail\n", __func__));
		return 0;
	}
	UINT32 ui4_written_on;
	ui4_eep_address = COMMON_EEP_INX_POWER_MODE_FLAG;
	UINT8 close_auto_on[1] = {0};
	i4_ret =  a_cfg_eep_raw_write(ui4_eep_address, close_auto_on, 1, &ui4_written_on);
	if(i4_ret !=0)
	{
		DBG_INFO(("!!!!%s a_cfg_eep_raw_write fail\n", __func__));
		return 0;
	}

    //Del At cmd log enable and file
    INX_AtCmdSetEnable(FALSE);
    INX_AtCmdDelLogFile();

    _nav_set_bluetooth_unpair();

    //camera motor down , if motor is up
    a_cam_mtk_motor_dlopen();
    a_cam_mtk_motor_down(CAM_MOTOR_MS);
    a_cam_mtk_motor_dlclose();
    
    i4_ret =  a_cfg_fac_reset();
	if(i4_ret !=0)
	{
		DBG_INFO(("!!!!%s a_cfg_eep_raw_write fail\n", __func__));
		return 0;
	}

#ifdef APP_C4TV_SUPPORT
	a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));	//mind 20160601
#endif
    a_cfg_store();
    
    menu_clear_memory_ex(TRUE);    // Ben 20180129

    return 1;
}

extern int a_cfg_custom_eep_write(UINT32 address,UINT8 value[],UINT32 size)
{
    UINT32 ui4_read;

    return a_cfg_eep_raw_write(address, value, size, & ui4_read);
}

extern int a_cfg_custom_set_eep_init(void)
{
    UINT8 wirte_buf[16] = {};
    INT32  i4_ret;
    wirte_buf[0] = 0x01;
    i4_ret = a_cfg_custom_eep_write(COMMON_EEP_INX_SELF_MAKE_BURNING_MODE_FLAG,wirte_buf,1);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }


    wirte_buf[0] = 0x00;
    i4_ret = a_cfg_custom_eep_write(EEP_CVTE_BURNING_MODE_FLAG,wirte_buf,1);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    wirte_buf[0] = 0x01;
    i4_ret = a_cfg_custom_eep_write(COMMON_EEP_INX_POWER_MODE_FLAG,wirte_buf,1);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    wirte_buf[0] = 0x00;
    i4_ret = a_cfg_custom_eep_write(EEP_PANEL_NITS_BY_DEFAULT,wirte_buf,1);
    if(i4_ret != APP_CFGR_OK)
    {
        return i4_ret;
    }

    //set gamma to off
    a_cfg_cust_set_gamma_on_off(FALSE);
 
    //set eeprom 0xFFe0B=1 to work with 0x1A05E=1 (COMMON_EEP_INX_POWER_MODE_FLAG) 
    a_cfg_cust_disp_screen();

    //set clean ch table
    i4_ret = inx_clean_ch_table();
    if (RMVR_OK != i4_ret)
    {
        return i4_ret;
    }

	// clear demura partition to check if MTK demura function works correctly
	inx_clear_demura_partition();

    //set VLOG off
    a_cfg_cust_set_log_level(LOGLEVEL_OFF);

	// reboot
	a_amb_reboot();
    return i4_ret;
}

extern int a_cfg_custom_get_mnt_path(CHAR *s_mount_point)
{
    INT32 i4_ret=RMVR_OK;
    UINT32 ui4_mnt_count=0,ui4_mnt_point_idx=0,ui4_usb_idx=0;
    RMV_DEV_DEVICE_STATUS_T  e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    SIZE_T    t_mount_point_size   = 511;

    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if( i4_ret != 0 ){
        return i4_ret;
    }

    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /*query mount point status*/
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(
                                    ui4_mnt_point_idx,
                                    &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status)))
        {
            continue;
        }
        break;
        
    }

    i4_ret = a_rmv_dev_set_active_mnt_pnt(ui4_mnt_point_idx);
    if( i4_ret != 0 ){
        return i4_ret;
    }

    i4_ret = a_rmv_dev_get_active_mnt_pnt(
								&ui4_usb_idx, 
								&t_mount_point_size, 
								s_mount_point);
    if(i4_ret == RMVR_NO_DEVICE){
        DBG_LOG_PRINT(("!!!NO USB DEVICE\n"));
        return i4_ret;
    }

    return i4_ret;
}

extern INT32 a_cfg_custom_read_file(UINT8 * fpath, UINT8 * fbuf, UINT32 fbuf_size)
{
    FILE *fp;
    UINT32 fread_size=0,nmemb=0,fsize=0;

    //check file exist
    if( access( fpath, F_OK ) == -1 ) {
        DBG_LOG_PRINT(("%s(): file(%s) does not exist\n", __func__, fpath));
        return -1;
    }

    fp=fopen(fpath,"r");
    if( fp == NULL ) {
        DBG_LOG_PRINT(("%s(): fopen(%s) failed\n", __func__, fpath));
        return -2;
    }

    //get file size
    fseek(fp, 0, SEEK_END); // seek to end of file
    fsize = ftell(fp); // get current file pointer
    fseek(fp, 0, SEEK_SET); // seek back to beginning of file

    //check file size
    if( fsize > fbuf_size ) {
        DBG_LOG_PRINT(("%s(): check file size failed (%d, %d)\n", __func__, fsize, fbuf_size));
        fclose(fp);
	return -3;
    }

    //read file buffer
    nmemb = fread(fbuf,fsize,1,fp);
    fread_size = fsize * nmemb;

    fclose(fp);
    return (INT32)fread_size;
}

extern UINT32 a_cfg_custom_write_file(UINT8 * fpath, UINT8 * fbuf, UINT32 fbuf_size)
{
    FILE *fp;
    UINT32 fwrite_size;

    fp=fopen(fpath,"w");
    if( fp == NULL ) {
        printf("%s fopen fail\n", __func__);
        return -2;
    }

    //write file buffer
    fwrite_size = fwrite(fbuf,1,fbuf_size,fp);

    fclose(fp);
    return fwrite_size;
}

extern VOID a_cfg_custom_set_local_contrast_pic_mode(UINT16 ui2_idx)
{
	UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST);
    INT16   ui2_pre_idx = 0;

	a_cfg_av_get(ui2_id, &ui2_pre_idx);
    a_cfg_av_set(ui2_id, ui2_idx);
    a_cfg_av_update(ui2_id);
}

extern UINT16 a_cfg_custom_get_local_contrast_pic_mode()
{
    UINT16 i2_val = 0; 
	//i2_val = _get_vid_gamma_idx();
	UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_LOCAL_CONTRAST);

    a_cfg_av_get(ui2_id, &i2_val);

    return (UINT16)(i2_val);
	//return i2_val;
}


/*******************************************************************
* Name : a_cfg_custom_set_gamma_in_pic_mode
* Description : Set gamma value in picture mode.
* Args : 1 parameter , value :
* ACFG_CUST_GAMMA_1_8
* ACFG_CUST_GAMMA_2_0
* ACFG_CUST_GAMMA_2_1
* ACFG_CUST_GAMMA_2_2
* ACFG_CUST_GAMMA_2_4
* retern : void 
*******************************************************************/


extern VOID a_cfg_custom_set_gamma_in_pic_mode(UINT16 ui2_idx)
{
    //_set_vid_gamma_idx(ui2_idx);
    UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA);
    INT16   ui2_pre_idx = 0;

    a_cfg_av_get(ui2_id, &ui2_pre_idx);
    a_cfg_av_set(ui2_id, ui2_idx);
    a_cfg_av_update(ui2_id);
/*	
    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
*/    
}

/*******************************************************************
* Name : a_cfg_custom_get_gamma_in_pic_mode
* Description : get gamma value in picture mode.
* Args : void
* retern : gamma value
* ACFG_CUST_GAMMA_1_8
* ACFG_CUST_GAMMA_2_0
* ACFG_CUST_GAMMA_2_1
* ACFG_CUST_GAMMA_2_2
* ACFG_CUST_GAMMA_2_4
*******************************************************************/

extern UINT16 a_cfg_custom_get_gamma_in_pic_mode()
{
    UINT16 i2_val = 0; 
	//i2_val = _get_vid_gamma_idx();
	UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA);

    a_cfg_av_get(ui2_id, &i2_val);

    return (UINT16)(i2_val);
	//return i2_val;
}

/*******************************************************************
* Name : a_cfg_custom_set_backlight_control
* Description : Set bc value in picture mode.
* Args : 1 parameter , value : 1 => on , 0 => off
* retern : void 
*******************************************************************/


extern VOID a_cfg_custom_set_backlight_control(UINT16 ui2_idx)
{
    //_set_vid_gamma_idx(ui2_idx);
    UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR);
    INT16   ui2_pre_idx = 0;

    a_cfg_av_get(ui2_id, &ui2_pre_idx);
    a_cfg_av_set(ui2_id, ui2_idx);
    a_cfg_av_update(ui2_id);
/*	
    if (ui2_pre_idx != ui2_idx)
    {
        set_preset_pic_mode_chg_status(TRUE);
    }
*/    
}

/*******************************************************************
* Name : a_cfg_custom_get_backlight_control
* Description : get backlight control .
* Args : void
* retern : value : 1 => on , 0 => off
*******************************************************************/

extern UINT16 a_cfg_custom_get_backlight_control()
{
    UINT16 i2_val = 0; 
	//i2_val = _get_vid_gamma_idx();
	UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR);

    a_cfg_av_get(ui2_id, &i2_val);

    return (UINT16)(i2_val);
	//return i2_val;
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

#if 0 //function rewrite
INT32 a_cfg_cust_inx_get_wifi_module_info(WIFI_DEVICE_INFO* pt_info )
{
    FILE*    pf_out = NULL;
    CHAR     buf[512] = {0};
    CHAR*    ptr = NULL;
    SIZE_T   rlen;
    

    if(!pt_info)
    {
        return APP_CFGR_INV_ARG;
    }
    c_memset(pt_info,0,sizeof(WIFI_DEVICE_INFO));
    inx_system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 driver get_hifl > /tmp/wifi_info");
    if((pf_out = fopen("/tmp/wifi_info","r")))
    {
        fseek(pf_out, 0, SEEK_END);
        unsigned long file_size = ftell(pf_out);
        rewind(pf_out);

        // just in case: check if buffer size is big enough before fread
        if (file_size > 511) 
        {
            DBG_LOG_PRINT(("[%s %d] file_size=%d (>511)\n",__FUNCTION__,__LINE__, file_size));
            file_size = 511;
        }

        rlen = fread(buf,file_size,1,pf_out);
        if (rlen < 0) {
            DBG_LOG_PRINT(("[%s %d] fread failed\n",__FUNCTION__,__LINE__));
            fclose(pf_out);
            return APP_CFGR_INV_ARG;
        }
        buf[file_size] = '\0';
        DBG_LOG_PRINT(("[%s %d] buf = %s\n",__FUNCTION__,__LINE__,buf));
        ptr = strtok(buf,"\r\n");

         while(ptr)
         {
             if(strstr(ptr,"VenderID:"))
             {
                 c_strcpy(pt_info->c_VenderID,ptr + c_strlen("VenderID:") + 1);
             }
             else  if(strstr(ptr,"ProductID:"))
             {
                 c_strcpy(pt_info->c_ProductID,ptr + c_strlen("ProductID:") + 1);
             }
             ptr = strtok(NULL,"\r\n");
         }
         DBG_LOG_PRINT(("[%s %d] VenderID =%s\n",__FUNCTION__,__LINE__,pt_info->c_VenderID));
         DBG_LOG_PRINT(("[%s %d] ProductID =%s\n",__FUNCTION__,__LINE__,pt_info->c_ProductID));
         fclose(pf_out);
         pf_out = NULL;
    }
    else
    {
       if(!pf_out)
       {
           DBG_LOG_PRINT(("[%s %d] fopen failed\n",__FUNCTION__,__LINE__));
       }
    }
    return APP_CFGR_OK;
}

#else
/*-----------------------------------------------------------------------------
* Name: _get_wifi_vid_pid_data
* Description: Get WIFI module information
* refer to MTK(Frank-CC Kuo)'s mail(2021-09-01 16:47)
** cat /sys/bus/usb/devices/3-1/idVendor => e.g. "0e8d"
** cat /sys/bus/usb/devices/3-1/idProduct => e.g. "7663"
*---------------------------------------------------------------------------*/
UINT8 _get_wifi_module_data(UINT8 *out_buffer, UINT16 buffer_len, CHAR *file_path)
{
    FILE *fp = NULL;
    UINT8 data_len = 0;

    fp = fopen(file_path, "r");
    if (fp)
    {
        (void)fgets((CHAR *)out_buffer, buffer_len, fp);
        (void)strtok((CHAR *)out_buffer, "\n");
        data_len = strlen((CHAR *)out_buffer);
        DBG_LOG_PRINT(("%s(): file_path=%s, buffer='%s'(data_len=%d)\n",__FUNCTION__, file_path, (CHAR *)out_buffer, data_len));
        fclose(fp);
    }
    else
    {
        DBG_LOG_PRINT(("%s(), %d: file(%s) not found!\n",__FUNCTION__,__LINE__, file_path));
    }

    return data_len;
}
#endif



/*-----------------------------------------------------------------------------
* Name: a_INX_dump_frequency_info
* Description: Get frequency information 
* Input arguments: point variable
* Output arguments: N/A
*---------------------------------------------------------------------------*/

extern VOID a_INX_dump_frequency_info(CHAR* frequency)
{
	VSH_SRC_RESOLUTION_INFO_T     	t_res;
	FLOAT                        	f_frame_rate = 0;
	c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_res);
	if((t_res.ui4_frame_rate / 1000 ) > 0)
    {
        f_frame_rate = (FLOAT)t_res.ui4_frame_rate / 100;
        c_sprintf(frequency, "%.2f",  f_frame_rate);
    }
    else
    {
        c_sprintf(frequency, "%d", t_res.ui4_frame_rate);
    }
}
/*-----------------------------------------------------------------------------
* Name: a_INX_dump_resolution_info
* Description: Get resolution information
* Input arguments: point variable
* Output arguments: N/A
*---------------------------------------------------------------------------*/

extern VOID a_INX_dump_resolution_info(CHAR* resolution)
{
	VSH_SRC_RESOLUTION_INFO_T       t_res;
	c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_res);
	c_sprintf (resolution, "%d X %d",
                           t_res.ui4_width,t_res.ui4_height);
}

/*-----------------------------------------------------------------------------
* Name: _get_wifi_status
* Description: Get wifi status information by 'sysfs' according to mail from Frank-CC Kuo(2021-09-23 16:26)
* Input arguments: void
* Output arguments: 1=wifi-connected; 0=wifi-disconnected
*---------------------------------------------------------------------------*/
extern UINT8 _get_wifi_status(VOID)
{
    FILE *fp;
    UINT8 wifi_sta = 0;
    CHAR file_path[] = WIFI_STATUS_PATH;
    CHAR file_buf[8] = {0};
    fp = fopen(file_path, "r");
    if (fp)
    {
        (void)fgets(file_buf, 8, fp);
        //(void)strtok(file_buf, "\n");
        DBG_LOG_PRINT(("%s(): '%s' = '%s'\n", __FUNCTION__, file_path, file_buf));
        wifi_sta = (UINT8)c_strtoll(file_buf, NULL, 10);
        fclose(fp);
    }
    else
    {
        DBG_LOG_PRINT(("%s(), %d: file(%s) not found!\n", __FUNCTION__, __LINE__, file_path));
    }
    return wifi_sta;
}

/*-----------------------------------------------------------------------------
* Name: _get_usb_path
* Description: Get usb path
* Input arguments: point variable
* Output arguments: N/A
*---------------------------------------------------------------------------*/

extern BOOL _get_usb_path(CHAR *path)
{
	UINT8 inx_i = 0;
	CHAR arr[256] = {0};
	unsigned char ch='\0'; // add init value, zl, 20190625
	int return_read = 0;
	FILE *f1;
			inx_system("mount | grep -i mnt | awk '{print $3}' > /tmp/usb_path_catpure");
			f1 = fopen("/tmp/usb_path_catpure","r");
		    //DBG_LOG_PRINT(("\n %s%d osd_path =\n",__FUNCTION__,__LINE__));
			if(f1 != NULL)
			{
				while(!feof(f1))
				{
					return_read = fread(&ch,sizeof(CHAR),1,f1);
					printf("%s(), return_read=%d\n", __func__, return_read);
					arr[inx_i] = ch;
					//DBG_LOG_PRINT(("INX_path[%c]",ch));
					inx_i++;
				}
				INX_AtCmdToCertDir(INX_ATCMD_NONE, "[_get_usb_path] arr[0]=0x%02X\n", arr[0]);
				
				
				if (inx_i > 2) //check for invalid access, zl, 20190625 
					arr[inx_i-2] = '/';
					
				//DBG_LOG_PRINT(("INX_arr[%d] = %c",inx_i,arr[inx_i-2]));
				
				
				if(arr[0] == '\0'){
					fclose(f1);
					return FALSE;
				}
				fclose(f1);		
			}
			c_strncpy((CHAR *)path,(const CHAR *)arr,inx_i-1);
		return TRUE;
}



/*******************************************************************
* Name : inx_cal_excuting_time
* Description : calculate the excuting time for some apis
* Args : id : timer id , start_clk : start time , if 0 , it is first time.
* retern : clock_t end_time
*******************************************************************/
clock_t inx_cal_excuting_time(int id,clock_t start_clk)
{
	double cpu_time_used;
	char debug_msg[256];
	clock_t end_clk = clock();   
	if(start_clk > 0)
	{                                              	
		cpu_time_used = ((double) (end_clk - start_clk)) / CLOCKS_PER_SEC;
		c_sprintf(debug_msg,"timer id = %d , time=%.2fsec\n",id,cpu_time_used);
		DBG_LOG_PRINT(("%s", debug_msg));

	}
	return end_clk;
}

extern int a_cfg_custom_factory_get_demo_file_amount(void)
{
	UINT32 fact_demo_file_cnt = 0;
	
	DIR *d;
    struct dirent *dir;
    d = opendir(DEMO_FILE_PATH);
    if(d)
    {
    	while ((dir = readdir(d)) != NULL)
        {
        	if( strstr(dir->d_name,DEMO_FILE_VICE) ){
            fact_demo_file_cnt++;
        	}
    	}
    	closedir(d);
    }
		
	return fact_demo_file_cnt;
}

INT32 i4_download_speed = 0;

extern VOID fac_download_speed_callback(INT32 i4Status,DOUBLE  u4Speed)
{
    if (i4Status == 0)
    {
        /* kbit/s, middleware return data is bytes/s, so need data*8/1024 */
       i4_download_speed = u4Speed/128;
    }
    else
    {
        /* speed test is failed */
       i4_download_speed = 0;
    }

    return;
}

//check hdcp 1.4
UINT8 a_cfg_custom_factory_check_hdcp1_4(void)
{
    UINT8 pu1ValidFlag;
    UINT8 ret_data[1] = {0};
    pu1ValidFlag = TEEC_CheckKey("21");
    (pu1ValidFlag == 0)?(ret_data[0] = 1):(ret_data[0] = 0);
    return ret_data[0];
}

//check hdcp 2
UINT8 a_cfg_custom_factory_check_hdcp2_2(void)
{
    UINT8 pu1ValidFlag;
    UINT8 ret_data[1] = {0};
    pu1ValidFlag = TEEC_CheckKey("8");
    (pu1ValidFlag == 0)?(ret_data[0] = 1):(ret_data[0] = 0);
    return ret_data[0];
}

//arg system
UINT32 inx_system(const char *format,...)
{
    va_list ap;
    int retval;
    UINT32 cmd_len = c_strlen(format);
    char buffer[cmd_len+256];

    c_memset(buffer,0,cmd_len+256);
    va_start(ap,format);
    retval = c_vsprintf(buffer,format,ap);
    retval = system(buffer);
    va_end(ap);
    return retval;
}

INT32 inx_clean_ch_table(VOID)
{
    INT32 i4_ret;
    i4_ret = a_cfg_cust_fac_clear_ch_table();// for clear channel table
    if(i4_ret != RMR_OK)
    {
    	DBG_LOG_PRINT(("\r\n %s,%d clear ch table fail i4_ret = %d!! \r\n",__FUNCTION__,__LINE__,i4_ret));
		INX_AckStringToFile("\r\n %s,%d clear ch table fail !! \r\n",__FUNCTION__,__LINE__);
		return i4_ret;
    }
	i4_ret = a_cfg_cust_set_ch_scan_progress(0);// back to channel not searched 
	if(i4_ret != RMR_OK)
	{
		DBG_LOG_PRINT(("\r\n %s,%d ch scan progress fail i4_ret = %d!! \r\n",__FUNCTION__,__LINE__,i4_ret));
		INX_AckStringToFile("\r\n %s,%d clear ch table fail !! \r\n",__FUNCTION__,__LINE__);
		return i4_ret;
	}
	i4_ret = a_cfg_set_crnt_channel_id(INVALID_CHANNEL_ID);// back to channel not searched
	if(i4_ret != RMR_OK)
	{
		DBG_LOG_PRINT(("\r\n %s,%d crnt ch id fail i4_ret = %d!! \r\n",__FUNCTION__,__LINE__,i4_ret));
		INX_AckStringToFile("\r\n %s,%d clear ch table fail !! \r\n",__FUNCTION__,__LINE__);
		return i4_ret;
	}
	i4_ret = nav_dispatch_msg_to_component(NAV_COMP_ID_SCREEN_SAVER,NAV_UI_MSG_EMPTY_SVL,NULL); // for enable immediately 
	if(i4_ret != RMR_OK)
	{
		DBG_LOG_PRINT(("\r\n %s,%d dispatch msg to component fail i4_ret = %d!! \r\n",__FUNCTION__,__LINE__,i4_ret));
		INX_AckStringToFile("\r\n %s,%d clear ch table fail !! \r\n",__FUNCTION__,__LINE__);
		return i4_ret;
	}
    return i4_ret;
}

UINT32 a_cfg_custom_dump_eep2usb(VOID)
{
    CHAR s_buf[512]={0};
    CHAR s_path[256] = {0};
    CHAR s_model_name[16] = {0};
    UINT32 ui4_index;
    CHAR s_sw_ver[32];

    if( a_cfg_custom_get_mnt_path(s_path) != 0 )
    {
        INX_AtCmdToCertDir(INX_ATCMD_NONE, "can't find usb device\n");
        return INX_RET_USB_NOT_FOUND;
    }
    a_cfg_custom_get_cur_model_name(s_model_name);
    a_cfg_custom_get_model_index(&ui4_index);
    INX_get_sw_ver(s_sw_ver);
    c_sprintf(s_buf,"/openbox/bin/cat /dev/mmcblk0p20 > %s/eep6_%s_MI%d_%s.bin",s_path,s_model_name,ui4_index,s_sw_ver);
    INX_AtCmdToCertDir(INX_ATCMD_NONE, "s_buf = %s\n",s_buf);
    int cmd_result = inx_system(s_buf);
    INX_AtCmdToCertDir(INX_ATCMD_NONE, "cmd_result = %d\n", cmd_result);

    if (cmd_result == 0){
        cmd_result=system("/openbox/bin/sync");
        return INX_RET_SUCCESS;
    }
    else{
        return INX_RET_SYSTEM_ERROR;
    }
}
extern INT32 a_cfg_custom_SPI_write(UINT8 u8channel,UINT8 data_len,UINT8 u8Data[]) 
{
   INT32 i4_ret;
   char i;
#if 0
   typedef enum
    {
        E_MSPI1,
        E_MSPI2,
        E_MSPI3,
        E_MSPI_MAX,
    }MSPI_CH;
#endif
    MISC_TYPE_SPI_ADVANCED_T t_info_write;
    c_memset(&t_info_write, 0, sizeof(t_info_write));
    t_info_write.ui1_channel = u8channel;
    t_info_write.pui1_data = &u8Data[0];
    t_info_write.ui1_data_len = data_len;

    DRV_CUST_OPERATION_INFO_T    t_op_info_write;
    SIZE_T z_size_drv_write = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size_write = sizeof(t_info_write);
    
    t_op_info_write.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_SET;
    t_op_info_write.u.t_cust_spec_set_info.e_cust_spec_type =  DRV_CUSTOM_OPERATION_TYPE_SPI_WRITE;
    t_op_info_write.u.t_cust_spec_set_info.pv_set_info = (VOID *)&t_info_write;
    t_op_info_write.u.t_cust_spec_set_info.z_size = z_size_write;
    t_op_info_write.u.t_cust_spec_set_info.b_store = TRUE;

    /* set to driver */
    i4_ret   = 0;
    i4_ret = c_rm_set_comp(
                        DRVT_CUST_DRV,
                        DRV_CUST_COMP_ID,
                        FALSE,
                        ANY_PORT_NUM,
                        0,
                        &t_op_info_write,
                        z_size_drv_write
                        );

    printf("SPI_write : u8channel=0x%x\n",u8channel);
    printf("SPI_write : data_len=%d\n",data_len);
    printf("SPI_write : u8Data=");
    for(i=0;i<data_len;i++){
        printf("%x ",u8Data[i]);
    }
    printf("\n");
    printf("SPI_write : i4_ret=%d\n",i4_ret);

    printf("[ACFG] %s,%d, i4_ret=%d",__FUNCTION__, __LINE__, i4_ret);
    if (i4_ret == 0)                 { printf("(OK)\r\n"); }
    else if (i4_ret == 1)          { printf("(INIT_FLOW_ERROR)\r\n"); }
    else if (i4_ret == 2)          { printf("(DCCONFIG_ERROR)\r\n"); }
    else if (i4_ret == 4)          { printf("(CLKCONFIG_ERROR)\r\n"); }
    else if (i4_ret == 8)          { printf("(FRAMECONFIG_ERROR)\r\n"); }
    else if (i4_ret == 0x10)     { printf("(OPERATION_ERROR)\r\n"); }
    else if (i4_ret == 0x20)     { printf("(PARAM_OVERFLOW)\r\n"); }
    else if (i4_ret == 0x40)     { printf("(MMIO_ERROR)\r\n"); }
    else if (i4_ret == 0x80)     { printf("(HW_NOT_SUPPORT)\r\n"); }
    else {printf("(unknown return value)");}
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }
    return i4_ret;
}
extern INT32 a_cfg_custom_SPI_read(UINT8 u8channel,UINT8 wdata_len,UINT8 u8wData[],UINT8 data_len,UINT8 u8Data[])
{ 
    INT32 i4_ret;
    char i;

    MISC_TYPE_SPI_ADVANCED_T t_info_read;
    c_memset(&t_info_read, 0, sizeof(t_info_read));
    t_info_read.ui1_channel = u8channel;
    t_info_read.pui1_wdata = &u8wData[0];
    t_info_read.ui1_wdata_len = wdata_len;
    t_info_read.pui1_data = &u8Data[0];
    t_info_read.ui1_data_len = data_len;

    DRV_CUST_OPERATION_INFO_T    t_op_info_read;
    SIZE_T z_size_drv_read = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T z_size_read = sizeof(t_info_read);
    
    t_op_info_read.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info_read.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_OPERATION_TYPE_SPI_READ;
    t_op_info_read.u.t_cust_spec_get_info.pv_get_info = (VOID *)&t_info_read;
    t_op_info_read.u.t_cust_spec_get_info.pz_size = &z_size_read;

    /* get from driver */
    i4_ret = c_rm_get_comp(
                 DRVT_CUST_DRV,
                 DRV_CUST_COMP_ID,
                 FALSE,
                 ANY_PORT_NUM,
                 0,
                 &t_op_info_read,
                 &z_size_drv_read
                 );
    printf("[ACFG] %s,%d, i4_ret=%d\n",__FUNCTION__, __LINE__, i4_ret);
    for(i=0;i<data_len;i++){
        printf("%x ", u8Data[i]);
    }
    if (i4_ret == 0)                 { printf("(OK)\r\n"); }
    else if (i4_ret == 1)          { printf("(INIT_FLOW_ERROR)\r\n"); }
    else if (i4_ret == 2)          { printf("(DCCONFIG_ERROR)\r\n"); }
    else if (i4_ret == 4)          { printf("(CLKCONFIG_ERROR)\r\n"); }
    else if (i4_ret == 8)          { printf("(FRAMECONFIG_ERROR)\r\n"); }
    else if (i4_ret == 0x10)     { printf("(OPERATION_ERROR)\r\n"); }
    else if (i4_ret == 0x20)     { printf("(PARAM_OVERFLOW)\r\n"); }
    else if (i4_ret == 0x40)     { printf("(MMIO_ERROR)\r\n"); }
    else if (i4_ret == 0x80)     { printf("(HW_NOT_SUPPORT)\r\n"); }
    else {printf("(unknown return value)");}
    if(i4_ret != RMR_OK)
    {
        DBG_INFO(("!!!!%s fail\n", __func__));
        return i4_ret;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Autho: zlhuang, 20200616
 * Name: _nav_fac_get_inx_mboot_ver
 * Description: Get INX build info in mboot partition
 * Inputs:
 * Outputs: INX build info string
 * Returns:
 ----------------------------------------------------------------------------*/
void _nav_fac_get_inx_mboot_ver(char *version, UINT32 version_size){
    FILE *fp = 0;
	unsigned long file_size = 0;
	unsigned long count = 0;
	void *file_buf = 0;
	char *buf_ptr = 0;
	unsigned long return_read = 0;
    fp = fopen("/dev/mmcblk0p1", "rb");
    if( fp == NULL ){
        printf("%s(), %d\n", __func__, __LINE__); 
    }
    else{
		fseek(fp, 0, SEEK_END);
		file_size=ftell(fp);
		printf("%s(): file_size=%lu\n", __func__, file_size);
		file_buf = malloc((SIZE_T)(file_size+1));
		if( file_buf == NULL ){
			printf("%s(), %d\n", __func__, __LINE__); 
			fclose(fp);
		    return;
		}
		bzero(file_buf, (SIZE_T)(file_size+1));
		fseek(fp, 0, SEEK_SET);
        return_read = fread(file_buf, file_size, 1, fp);  
		printf("%s(), return_read=%lu\n", __func__, return_read); 
        fclose(fp);

		buf_ptr = (char *)file_buf;
        while(count < file_size)
  	    {
    	    if(buf_ptr[0] == 'I')
            {
	            //printf("buf_ptr=%s\n", buf_ptr); 
	            //if(strstr(buf_ptr, "INX_BIN_"))
	            if(c_strncmp(buf_ptr, "INX_BIN_", 8) == 0)
                {
                    printf("buf_ptr(0x%lX)=\"INX_BIN_...\"\n", count); 
					//INX_BIN_2020mmddHHMM_1234567, skip "INX_BIN_"
                    memcpy((void *)version, (void *)(buf_ptr+8), version_size);
				    break;
                }
    			buf_ptr+=8;
	    		count+=8;
    	    }
			else
			{
    			buf_ptr++;
			    count++;
			}
		}
        free(file_buf);
    }
    return;
}

/*-----------------------------------------------------------------------------
 * Autho: zlhuang, 20200623
 * Name: _nav_fac_get_gamma_bin_ver
 * Description: Get version info in Gamma bin file, refer to mail from Yuche Szutu(020-06-23 10:48)
 * Inputs:
 * Outputs: 
 * Returns:
 ----------------------------------------------------------------------------*/
void _nav_fac_get_gamma_bin_ver(char *version, UINT32 version_size){
    int version_offset=0x34;
    UINT8 buf[4]={0}; 
    int fd = 0;
	UINT32 u4Ver = 0; 
	UINT16 year=0, month=0, day=0, hour=0, minute=0;
	int return_offset=0, return_read=0;
	
	char gamma_bin_path[]="/config/gamma/panel_gamma.bin";
    fd = open(gamma_bin_path, O_RDONLY);
    if( fd < 0 ){
        printf("%s(): file not found(%s)\n", __func__, gamma_bin_path); 
    }
    else{
        return_offset = lseek(fd, version_offset, SEEK_SET);
		printf("%s(): return_offset=%d\n", __func__, return_offset); 
        return_read = read(fd, buf, sizeof(buf));
		printf("%s(): return_read=%d\n", __func__, return_read); 
  	    u4Ver = *(UINT32 *)buf;
        printf("%s(): version raw data=0x%08X\n", __func__, u4Ver); 
		//4-byte integer, LSB, start from 0x34
        year = 2000 + (u4Ver >> 20);  	//b31~b20 
		month =  (u4Ver >> 16) & 0x000F; //b19~b16
		day =    (u4Ver >> 11) & 0x001F; //b15~b11
		hour =   (u4Ver & 0x07FF) / 60;  //b10~b00:total_minutes => hour = total_minutes / 60
		minute = (u4Ver & 0x07FF) % 60;  //b10~b00:total_minutes => minute = total_minutes % 60 
        snprintf(version, version_size, "%d%02d%02d%02d%02d\0", year, month, day, hour, minute);
        close(fd);
    }
    return;
}

/*-----------------------------------------------------------------------------
 * Autho: zlhuang, 20191031
 * Name: _nav_fac_get_tcon_ver
 * Description: Get version info in TCON bin file
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
void _nav_fac_get_tcon_ver(char *version, UINT32 version_size){
    int version_offset=0x28;
    UINT8 buf[32]={0}; 
    int fd = 0;
	long return_offset=0, return_read=0;

    char *tcon_bin_path;
    tcon_bin_path = a_cfg_cust_info_get_ini_item_value("model/Customer_1.ini", "TCON_BIN", "TCON_FILE");
    if (tcon_bin_path == NULL){
        printf("%s(): no TCON path info\n", __func__); 
        return;
    }

    fd = open(tcon_bin_path, O_RDONLY);
    if( fd < 0 ){
        printf("%s(): TCON bin file not found(%s)\n", __func__, tcon_bin_path); 
    }
    else{
        //printf("%s(): tcon_bin_path=%s\n", __func__, tcon_bin_path); 
        return_offset = lseek(fd, version_offset, SEEK_SET);
		printf("%s(): return_offset=%ld\n", __func__, return_offset); 		
        return_read = read(fd, buf, 32);
		printf("%s(): return_read=%ld\n", __func__, return_read); 

        //printf("%s(): version format=0x%08X\n", __func__, *(UINT32 *)buf); 

        //memcpy((void *)version, (void *)buf, version_size);
        snprintf(version, 6, "%02d.%02d", *buf, *(buf + 1));
        close(fd);
    }
    return;
}

/*-----------------------------------------------------------------------------
 * Name : INX_get_pq_path
 * Description: get pq path
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
VOID INX_get_pq_path(CHAR *ps_str,CHAR *bin_str)
{
	//INT32 i4_ret = 0;
	//UINT32      ui4_group_id = 0;
    //UINT32      ui4_model_id = 0;
	CHAR        s_str[MI_INI_FILE_PATH_LEN+1] = {0};
	

    c_sprintf(s_str,"%s%s%s",MI_INI_CONFIG_PATH,MI_INI_PQ_DIR,bin_str);
	

    c_strncpy(ps_str,s_str,MI_INI_FILE_PATH_LEN);
}

/*-----------------------------------------------------------------------------
 * Modify: truedano 20180921
 * Name: _nav_fac_get_pq_raw 
 * Description: Get PQ raw data
 * Inputs:
 * Outputs: NONE
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _nav_fac_get_pq_raw(UINT32 address,CHAR *bin_file,UINT32 size,void *buf)
{
    char pq_buf[size+1];
	int pq_fd = 0;
	int return_offset=0, return_read=0;    
	CHAR str[MI_INI_FILE_PATH_LEN+1] = {0};
    memset(pq_buf,0,size+1);
	INX_get_pq_path(str,bin_file);
    pq_fd = open(str,O_RDONLY);
    if( pq_fd < 0 )
    {
        return pq_fd;
    }
    else
    {
        return_offset = lseek(pq_fd,address,SEEK_SET);
        printf("%s(): return_offset=%d\n", __func__, return_offset);
        return_read = read(pq_fd,pq_buf,size);
		printf("%s(): return_read=%d\n", __func__, return_read);
        memcpy((void *)buf,(void *)pq_buf,size);
        close(pq_fd);       
    }
    return pq_fd;
}

/*-----------------------------------------------------------------------------
 * Author: zlhuang, 20200103
 * Name: _nav_fac_get_dolby_ver
 * Description: Get version info in DOLBY bin file
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
void _nav_fac_get_dolby_ver(char *version, UINT32 version_size){
    // change according to http://aic.cminl.oa/aic/browse/TVPLT-734
    int version_offset=DOLBY_ADDR;
    UINT8 buf[8]={0}; 
    FILE *fp = 0;
    //int offset=0;
    int file_size=0;
    int return_offset=0, return_read=0;    
    char dolby_bin_path[64]={0};
    c_sprintf(dolby_bin_path, "%s/HDR_BIN/dolby.bin",MI_INI_CONFIG_PATH);
    fp = fopen(dolby_bin_path, "rb");
    if( fp == NULL ){
        printf("%s(): DOLBY bin file not found(%s)\n", __func__, dolby_bin_path); 
    }
    else{
        fseek(fp, 0, SEEK_END);
        file_size=ftell(fp);
        //printf("%s(): file_size=%d\n", __func__, file_size);
        if(file_size < version_offset){
            printf("%s(): DOLBY bin file invalid (size=%d)\n", __func__, file_size);
	}
        else{
            return_offset = fseek(fp, version_offset, SEEK_SET);
			printf("%s(): return_offset=%d\n", __func__, return_offset); 		
	        return_read = fread(buf, 7, 1, fp);
			printf("%s(): return_read=%d\n", __func__, return_read); 		
			
            printf("%s(): [0x%04X]=0x%02X\n", __func__, version_offset, buf[0]); 
            memcpy((void *)version, (void *)buf, version_size);
        }
        fclose(fp);
    }
    return;
}

/*-----------------------------------------------------------------------------
 * Author: yshu, 20200915
 * Name: _nav_fac_get_pq_def_ver
 * Description: Get version info in PQ ini file
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
void _nav_fac_get_pq_def_ver(char *version, UINT32 version_size){
    // change according to http://aic.cminl.oa/aic/browse/TVPLT-734
	DBG_LOG_PRINT((" yshu : (%s)\n", __FUNCTION__));
	CHAR path[64]={0};
	CHAR pq_ver[256]={0};

	c_sprintf(path,PQ_CONFIG_PATH"%s",PQ_DEF_TBL);
	a_cfg_cust_info_get_ini_item_string(path,"Version","PQ_DEFAULT_VER","Unknown",pq_ver,256);
	DBG_LOG_PRINT((" yshu : (%s) %s PQ Ver %s \n\n", __FUNCTION__,path,pq_ver));
	c_strncpy(version,pq_ver,version_size);
    return;
}

UINT16 INX_get_sw_ver(CHAR *s_sw_ver)
{
    CHAR *s_tmp_str;
    UINT16 i,j=0;
    
    s_tmp_str = sys_cust_get_cust_serial();
    c_strncpy(s_sw_ver,s_tmp_str,32);
    for(i = 0;i < strlen(s_sw_ver);i++)
	{
		if(isprint(s_sw_ver[i]))
			j++;
	}
    return j;
}

UINT16 INX_get_vizio_os_ver(CHAR *s_ver)
{
    FILE *fp;
    CHAR tmp[128] = {0};
    UINT16 len=0;
    int i;

    fp = fopen(MTK_OS_RELEASE_PATH,"r");
    if( fp ){
        while (fgets(tmp, 127, fp) != NULL){
            if( !memcmp(tmp,MTK_VIZIO_OS_VER_PREFEX,strlen(MTK_VIZIO_OS_VER_PREFEX)) ){
                strncpy(s_ver,tmp+strlen(MTK_VIZIO_OS_VER_PREFEX),63);
                for(i = 0;i < strlen(s_ver);i++)
                {
                    if(isprint(s_ver[i]))
                        len++;
                }
                break;
            }
        }
    }else{
        DBG_LOG_PRINT((" %s() : %s not found \n\n", __FUNCTION__,MTK_OS_RELEASE_PATH));
    }
    return len;
}


/*-----------------------------------------------------------------------------
 * Author: joe
 * Name: _nav_fac_set_eeprom_flag
 * Description: Set eeprom flag
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
UINT8 _nav_fac_set_eeprom_flag(E_NAV_EEP_ID e_id,UINT8 idx)
{
	INT32 i4_ret;
	UINT32 ui4_written;
	UINT32 u32_eep_address;
	CHAR *c_eep_buf = NULL;
	switch(e_id)
	{
		case INX_EEP_INX_AGING_MODE:
			u32_eep_address = COMMON_EEP_INX_BURNING_MODE_FLAG;
		break;
		case INX_EEP_AUTO_POWERON:
			u32_eep_address = COMMON_EEP_INX_POWER_MODE_FLAG;
		break;
		case INX_EEP_CVTE_AGING_MODE:
			u32_eep_address = EEP_CVTE_BURNING_MODE_FLAG;
		break;
		case INX_EEP_WHITE_BALANCE_MODE:
			c_eep_buf = a_cfg_cust_info_get_ini_item_value("/config/eeprom_layout.ini","EEP_LAYOUT","EEPROM_NPTV_GAMMA_OFFSET");
			c_sscanf(c_eep_buf,"%x",&u32_eep_address);		
		break;
		default:
			return APP_CFGR_INTERNAL_ERR;
		break;
	}
	i4_ret = a_cfg_eep_raw_write(u32_eep_address,(VOID *)&idx,1,&ui4_written);
	if(i4_ret != APP_CFGR_OK)
	{
		DBG_LOG_PRINT((" Write value to eeprom fail !! i4_ret = %d \n",i4_ret));
		return APP_CFGR_INTERNAL_ERR;
	}
	return APP_CFGR_OK;
	
}
/*-----------------------------------------------------------------------------
 * Author: joe
 * Name: _nav_fac_get_eeprom_flag
 * Description: Get eeprom flag
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
UINT8 _nav_fac_get_eeprom_flag(E_NAV_EEP_ID e_id)
{
 	INT32 i4_ret;
	UINT32 ui4_written;
	UINT32 u32_eep_address;
	CHAR *c_eep_buf = NULL;
	UINT8 idx;
	switch(e_id)
	{
		case INX_EEP_INX_AGING_MODE:
			u32_eep_address = COMMON_EEP_INX_BURNING_MODE_FLAG;
		break;
		case INX_EEP_AUTO_POWERON:
			u32_eep_address = COMMON_EEP_INX_POWER_MODE_FLAG;
		break;
		case INX_EEP_CVTE_AGING_MODE:
			u32_eep_address = EEP_CVTE_BURNING_MODE_FLAG;
		break;
		case INX_EEP_WHITE_BALANCE_MODE:
			c_eep_buf = a_cfg_cust_info_get_ini_item_value("/config/eeprom_layout.ini","EEP_LAYOUT","EEPROM_NPTV_GAMMA_OFFSET");
			c_sscanf(c_eep_buf,"%x",&u32_eep_address);
		break;
		default:
			return APP_CFGR_INTERNAL_ERR;
		break;
	}	
	i4_ret = a_cfg_eep_raw_read(u32_eep_address,(VOID *)&idx,1,&ui4_written);
	if(i4_ret != APP_CFGR_OK)
	{
		DBG_LOG_PRINT((" Write value to eeprom fail !! i4_ret = %d \n",i4_ret));
		return APP_CFGR_INTERNAL_ERR;
	}
	return idx;
}

/*-----------------------------------------------------------------------------
 * Author: truedano
 * Name: _nav_fac_get_file_size
 * Description: Get file size
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _nav_fac_get_file_size(CHAR * full_path)
{
    struct stat st;

    if( stat(full_path,&st) == -1){
        return -1;
    }
    return st.st_size;
}

/*-----------------------------------------------------------------------------
 * Author: zlhuang
 * Name: _nav_set_bluetooth_pair
 * Description: Bluetooth pair operation
 * Inputs: remote device MAC
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _nav_set_bluetooth_pair(UINT8 *device_mac, UINT8 mac_length)
{
	int idx;
	int cmd_result;
	CHAR c_mac_buf[64] = {0};	
	CHAR c_cmd_buf[256] = {0};	
	//handle first (n-1) bytes
	for(idx=0; idx<mac_length-1; idx++)
	{
		c_sprintf(c_mac_buf, "%s%02X:", c_mac_buf, device_mac[idx]);
	}
	//handle the last byte
	if(mac_length-1 >= 0)
	{
		c_sprintf(c_mac_buf, "%s%02X", c_mac_buf, device_mac[mac_length-1]);
	}
	
	//e.g. LD_LIBRARY_PATH=/data/app/bluetooth/lib /data/app/bluetooth/bin/bt_cli set_pair A0:22:4E:00:10:B2
	//since [1.20.31][viziOS]: chroot /proc/`pidof bluetoothd`/root /bin/bash -c "LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w <file> set_pair A0:22:4E:00:10:B2"
	c_sprintf(c_cmd_buf, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w /tmp/bt_pair_result set_pair %s\" &", c_mac_buf);
	DBG_LOG_PRINT(("%s() c_cmd_buf=%s\n", __func__, c_cmd_buf));
	cmd_result = inx_system(c_cmd_buf);
    DBG_LOG_PRINT(("%s() cmd_result=%d\n", __func__, cmd_result));
	if (cmd_result != 0)
	{
		return APP_CFGR_INTERNAL_ERR;
	}

	return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Author: zlhuang
 * Name: _nav_set_bluetooth_unpair
 * Description: Bluetooth unpair operation
 * Inputs: 
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _nav_set_bluetooth_unpair(void)
{
    int cmd_result;
	DBG_LOG_PRINT(("%s() start!\n", __func__));
	cmd_result = inx_system("chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli set_unpair\"");
   	DBG_LOG_PRINT(("%s() cmd_result=%d\n", __func__, cmd_result));

#if 0 //20210118, zl
	if (cmd_result != 0)
	{
		return APP_CFGR_INTERNAL_ERR;
	}
#endif

	return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Author: zlhuang
 * Name: _nav_get_bluetooth_rc_mac
 * Description: get Bluetooth paired remote control's MAC
 * Inputs: 
 * Outputs: remote control's MAC "hh:hh:hh:hh:hh:hh"
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _nav_get_bluetooth_rc_mac(CHAR *mac_str)
{
    INT32 i4_result = APP_CFGR_INTERNAL_ERR;
    INT32 cmd_result = 0; 
	CHAR tmp[128] = {0};
	CHAR *p_str_mac = NULL;
	CHAR c_cmd_buf[512] = {0};	
	CHAR bluetooth_data_path[]="/tmp/bluetooth/public/bt_device_list"; //folder path is according to Vizio/MTK rule
	
	//e.g. LD_LIBRARY_PATH=/data/app/bluetooth/lib /data/app/bluetooth/bin/bt_cli get_list | grep XRT | grep PAIRED:Y
	//since [1.20.3.1][viziOS]: chroot /proc/`pidof bluetoothd`/root /bin/bash -c "LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli get_list"
	c_sprintf(c_cmd_buf,"chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_list\"", bluetooth_data_path); 
	
    DBG_LOG_PRINT(("%s() c_cmd_buf=%s\n", __func__, c_cmd_buf));

    cmd_result = system(c_cmd_buf);

    FILE * fl = fopen(bluetooth_data_path, "r");
    if (fl != NULL)
    {
	    DBG_LOG_PRINT(("%s() %d\n", __func__, __LINE__));
		while (fgets(tmp, 127, fl) != NULL)
		{
			DBG_LOG_PRINT(("%s() tmp=%s\n", __func__, tmp));
			//e.g. A0:22:4E:00:10:B2 XRT260v480 PAIRED:Y CONNECTED:Y
			// filter: XRT, PAIRED:Y
		    if(strstr(tmp, "XRT")==NULL || strstr(tmp, "PAIRED:Y")==NULL) continue;
			
			p_str_mac = strtok(tmp, " ");
			DBG_LOG_PRINT(("p_str_mac=%s\n", p_str_mac));
			if(p_str_mac)
			{
				c_strncpy(mac_str, p_str_mac, strlen(p_str_mac));
				i4_result = APP_CFGR_OK;
				break;
			}
		}
	    fclose(fl);
    }
   	DBG_LOG_PRINT(("%s() cmd_result = %d\n", __func__, cmd_result));	
   	DBG_LOG_PRINT(("%s() i4_result = %d\n", __func__, i4_result));
	return i4_result;
}

/*-----------------------------------------------------------------------------
 * Author: zlhuang
 * Name: _nav_get_bluetooth_rssi
 * Description: get rssi of Bluetooth paired remote control
 * Inputs: 
 * Returns: rssi (e.g. -50,-30,etc.)
 * Outputs: 
 ----------------------------------------------------------------------------*/
INT32 _nav_get_bluetooth_rssi(void)
{
    INT32 i4_result = 0xFF; 
	INT32 i4_rssi = 0;
    INT32 cmd_result = 0; 
	INT32 i4_rc_mac_valid = APP_CFGR_INTERNAL_ERR;
	CHAR c_cmd_buf[512] = {0};	
	CHAR mac_str[64] = {0};
	CHAR tmp[128] = {0};
	CHAR *p_str_rssi;
	CHAR bluetooth_data_path[]="/tmp/bluetooth/public/rssi_data"; //folder path is according to Vizio/MTK rule

	//c_sprintf(c_cmd_buf, "rm -f %s", bluetooth_data_path);
	//cmd_result = system(c_cmd_buf);
	
	//get paired remote control's MAC first
	i4_rc_mac_valid = _nav_get_bluetooth_rc_mac(mac_str);
	//e.g. LD_LIBRARY_PATH=/data/app/bluetooth/lib /data/app/bluetooth/bin/bt_cli get_rssi A0:22:4E:00:10:B2
	//since [1.20.3.1][viziOS]: chroot /proc/`pidof bluetoothd`/root /bin/bash -c "LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli get_rssi xxx"
    if (i4_rc_mac_valid == APP_CFGR_OK)
	{
		//get RSSI of paired device
		c_sprintf(c_cmd_buf,"chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_rssi %s\"", bluetooth_data_path,mac_str); 
	}
	else
	{
		//get RSSI of XRT260TEST
		c_sprintf(c_cmd_buf,"chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_rssi XRT260TEST\"", bluetooth_data_path); 
	}
	
    DBG_LOG_PRINT(("%s() c_cmd_buf=%s\n", __func__, c_cmd_buf));

    cmd_result = system(c_cmd_buf);
    
    FILE * fl = fopen(bluetooth_data_path, "r");
    if (fl != NULL)
    {
		DBG_LOG_PRINT(("%s() %d\n", __func__, __LINE__));
		if (fgets(tmp, 127, fl) != NULL)
		{
			//e.g. "RSSI -44"
			strtok(tmp, " ");
			p_str_rssi = strtok(NULL, " ");
			DBG_LOG_PRINT(("p_str_rssi=%s\n", p_str_rssi));
			if(p_str_rssi)
			{
				i4_rssi = c_strtoll(p_str_rssi, NULL, 10);				
				if (i4_rssi == 0) //impossible value
				{
				   	DBG_LOG_PRINT(("%s() %d\n", __func__, __LINE__));
				}
				else
				{
  					i4_result = i4_rssi;
				}
			}
		}
	    fclose(fl);
    }

	//system("whoami"); //test only
   	DBG_LOG_PRINT(("%s() cmd_result = %d\n", __func__, cmd_result));	
   	DBG_LOG_PRINT(("%s() i4_result = %d\n", __func__, i4_result));
	return i4_result;
	
}


/*-----------------------------------------------------------------------------
 * Author: zlhuang
 * Name: _nav_get_bluetooth_rssi_by_mac
 * Description: get rssi of specified device
 * Inputs: 
 * Returns: rssi (e.g. -50,-30,etc.)
 * Outputs: 
 ----------------------------------------------------------------------------*/
INT32 _nav_get_bluetooth_rssi_by_mac(UINT8 *mac_addr)
{
    INT32 i4_result = 0xFF; 
	INT32 i4_rssi = 0;
    INT32 cmd_result = 0; 
	CHAR c_cmd_buf[512] = {0};	
	CHAR tmp[128] = {0};
	CHAR *p_str_rssi;
	CHAR bluetooth_data_path[]="/tmp/bluetooth/public/rssi_data"; //folder path is according to Vizio/MTK rule

	//since [1.20.3.1][viziOS]: chroot /proc/`pidof bluetoothd`/root /bin/bash -c "LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli get_rssi xxx"
	//get RSSI of specified device
	c_sprintf(c_cmd_buf,"chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_rssi %02X:%02X:%02X:%02X:%02X:%02X\"", bluetooth_data_path, mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4],mac_addr[5]); 
    DBG_LOG_PRINT(("%s() c_cmd_buf=%s\n", __func__, c_cmd_buf));
    cmd_result = system(c_cmd_buf);
    
    FILE * fl = fopen(bluetooth_data_path, "r");
    if (fl != NULL)
    {
		//DBG_LOG_PRINT(("%s() %d\n", __func__, __LINE__));
		if (fgets(tmp, 127, fl) != NULL)
		{
			DBG_LOG_PRINT(("file_content=%s\n", tmp));
			//e.g. "RSSI -44"
			strtok(tmp, " ");
			p_str_rssi = strtok(NULL, " ");
			DBG_LOG_PRINT(("p_str_rssi=%s\n", p_str_rssi));
			if(p_str_rssi)
			{
				i4_rssi = c_strtoll(p_str_rssi, NULL, 10);				
				if (i4_rssi == 0) //impossible value
				{
				   	DBG_LOG_PRINT(("%s() %d: something wrong...\n", __func__, __LINE__));
				}
				else
				{
  					i4_result = i4_rssi;
				}
			}
		}
	    fclose(fl);
    }

   	DBG_LOG_PRINT(("%s() cmd_result = %d\n", __func__, cmd_result));	
   	DBG_LOG_PRINT(("%s() i4_result = %d\n", __func__, i4_result));
	return i4_result;
	
}

/*-----------------------------------------------------------------------------
 * Author: zlhuang
 * Name: _nav_get_bluetooth_host_mac
 * Description: get Bluetooth host MAC
 * Inputs: 
 * Outputs: Bluetooth Host MAC 
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 _nav_get_bluetooth_host_mac(UINT8 *host_mac)
{
    INT32 i4_result = APP_CFGR_INTERNAL_ERR;
	INT32 cmd_result = 0;
	CHAR c_cmd_buf[256] = {0};	
	CHAR tmp[128] = {0};
	CHAR *p_str_host_mac;
	CHAR bluetooth_data_path[]="/tmp/bluetooth/public/host_mac_data"; //folder path is according to Vizio/MTK rule

	//c_sprintf(c_cmd_buf, "rm -f %s", bluetooth_data_path);
	//cmd_result = system(c_cmd_buf);

	//LD_LIBRARY_PATH=/data/app/bluetooth/lib /data/app/bluetooth/bin/bt_cli get_mac_address
	// since [1.20.3.1][viziOS]: chroot /proc/`pidof bluetoothd`/root /bin/bash -c "LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli get_mac_address"
	c_sprintf(c_cmd_buf, "chroot /proc/`pidof bluetoothd`/root /bin/bash -c \"LD_LIBRARY_PATH=/app/lib /basic/bin/mtk_launcher bluetooth /app/bin/bt_cli -w %s get_mac_address\"", bluetooth_data_path); 
    DBG_LOG_PRINT(("%s() c_cmd_buf=%s\n", __func__, c_cmd_buf));

    cmd_result = system(c_cmd_buf);
	FILE * fl = fopen(bluetooth_data_path, "r");
    if (fl != NULL)
    {
    	DBG_LOG_PRINT(("%s() %d\n", __func__, __LINE__));
		if (fgets(tmp, 127, fl) != NULL)
		{
			DBG_LOG_PRINT(("file_content=%s\n", tmp));
			//e.g. HOST 2C:64:1F:A9:0C:2B
			strtok(tmp, " ");
			p_str_host_mac = strtok(NULL, " ");
			if(p_str_host_mac)
			{
				c_sscanf(p_str_host_mac,  "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &host_mac[0], &host_mac[1], &host_mac[2], &host_mac[3], &host_mac[4], &host_mac[5]);
				DBG_LOG_PRINT(("host_mac[0]=%02X\n", host_mac[0]));
				DBG_LOG_PRINT(("host_mac[5]=%02X\n", host_mac[5]));
				i4_result = APP_CFGR_OK;
			}
		}
	    fclose(fl);
    }

  	DBG_LOG_PRINT(("%s() cmd_result = %d\n", __func__, cmd_result));
	DBG_LOG_PRINT(("%s() i4_result = %d\n", __func__, i4_result));
	return i4_result;

}

/*-----------------------------------------------------------------------------
 * Author: zlhuang
 * Name: inx_clear_demura_partition
 * Description: clear demura partition
 * Inputs: 
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/ 
#define MT5695L_DEMURA_PARTITION "/dev/mmcblk0p18" //partition size=3MB, refer to partition_layout.txt
void inx_clear_demura_partition(void)
{
    INT32 cmd_result = 0;
	CHAR c_cmd_buf[512] = {0};	

	//c_sprintf(c_cmd_buf, "dd if=/dev/zero of=%s bs=1M count=3 2>&1", MT5695L_DEMURA_PARTITION); => permission denied for access of /dev/zero...
	c_sprintf(c_cmd_buf, "dd if=/dev/zram0 of=%s bs=1M count=3 2>&1", MT5695L_DEMURA_PARTITION); ///dev/zram0 access ok!
    DBG_LOG_PRINT(("%s() c_cmd_buf=%s\n", __func__, c_cmd_buf));

    cmd_result = system(c_cmd_buf);
	DBG_LOG_PRINT(("%s() cmd_result=%d\n", __func__, cmd_result));
}

/*-----------------------------------------------------------------------------
 * Autho: Yanru, 20210401
 * Name: _nav_fac_get_tconless_dc_on_flag
 * Description: Get level shift & vcom_download dc-on flag 
 * Inputs:
 * Outputs: 
 * Returns:
 ----------------------------------------------------------------------------*/
void _nav_fac_get_tconless_dc_on_flag(CHAR * path,char *flag, UINT32 flag_size){    
    FILE *f1;
    const CHAR *status;
    int ret;
    unsigned char read_status=0;

    f1 = fopen(path,"r");
    if(f1 != NULL )
    {
        ret=fread(&read_status,sizeof(CHAR),1,f1);
        if(ret<=0){
            printf("%s(): file not found(/proc/inx_level_shift_flag)\n", __func__); 
        }
        else {
             if(read_status == '0')
             {
                 status = "No";
             }
             else if(read_status == '1')
             {
                 status = "Yes";
             }else{
                 status = "No"; //yshu default value 20210608 
             }

             c_strncpy(flag,status,flag_size);
        }
        fclose(f1);
    }
}

/*-----------------------------------------------------------------------------
 * Autho: 
 * Name: inx_fac_color_tuner_20_point_set_values
 * Description: 
 * Inputs:
 * Outputs: 
 * Returns:
 ----------------------------------------------------------------------------*/
void inx_fac_color_tuner_20_point_set_values(INT8 i1_20_point_values[3][20])
{
    UINT8       ui1_j = 0;
	INT8 i1_R[COLOR_TUNER_FAC_20POINT_NUM] = {0};
	INT8 i1_G[COLOR_TUNER_FAC_20POINT_NUM] = {0};
	INT8 i1_B[COLOR_TUNER_FAC_20POINT_NUM] = {0};
	for (ui1_j = 0; ui1_j < COLOR_TUNER_FAC_20POINT_NUM; ui1_j++)
    {
        i1_R[ui1_j] = i1_20_point_values[0][ui1_j];
        i1_G[ui1_j] = i1_20_point_values[1][ui1_j];
        i1_B[ui1_j] = i1_20_point_values[2][ui1_j];
    }
	
	a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
	UINT32 ui4_written = 0;
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
	UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
	a_cfg_eep_raw_write(
            ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_R,
            (VOID *)&i1_R,
            COLOR_TUNER_FAC_20POINT_NUM,
            &ui4_written); 
	a_cfg_eep_raw_write(
            ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_G,
            (VOID *)&i1_G,
            COLOR_TUNER_FAC_20POINT_NUM,
            &ui4_written);
	a_cfg_eep_raw_write(
            ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + COLOR_TUNER_FAC_ADDRESS_OFFSET_20_POINT_B,
            (VOID *)&i1_B,
            COLOR_TUNER_FAC_20POINT_NUM,
            &ui4_written);

	a_cfg_cust_update_crnt_11_point_value();

	a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_DISP, APP_CFG_RECID_DISP_GAMMA));
}
/*-----------------------------------------------------------------------------
 * Autho: 
 * Name: color_tuner_get_settings
 * Description: 
 * Inputs:
 * Outputs: 
 * Returns:
 ----------------------------------------------------------------------------*/
INT8 color_tuner_get_settings(UINT16 idx)
{
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();
    INT8 i1_val = 0;
    UINT32 ui4_read = 0;

	a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    a_cfg_eep_raw_read(
        ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + idx,
        (VOID *)&i1_val,
        1,
        &ui4_read);
    return i1_val;
}
/*-----------------------------------------------------------------------------
 * Autho: 
 * Name: color_tuner_set_settings
 * Description: 
 * Inputs:
 * Outputs: 
 * Returns:
 ----------------------------------------------------------------------------*/

void color_tuner_set_settings(UINT16 idx, INT8 set_value)
{
    UINT32 ui4_written = 0;
    UINT8 ui1_play_content = a_acfg_cust_get_dynamic_range();

	a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    a_cfg_eep_raw_write(
        ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + idx,
        (VOID *)&set_value,
        1,
        &ui4_written);
}
/*-----------------------------------------------------------------------------
 * Autho: 
 * Name: color_tuner_set_offset_gain_settings
 * Description: 
 * Inputs:
 * Outputs: 
 * Returns:
 ----------------------------------------------------------------------------*/

void color_tuner_set_offset_gain_settings(UINT16 ui2_recid, INT8 set_value)
{
    UINT8 		ui1_play_content = a_acfg_cust_get_dynamic_range();
    UINT32      ui4_written = 0;
    UINT16      ui2_idx = 0;

	a_cfg_custom_plf_opt_get_color_tuner_dynamic_address(&ui4_dynamic_address);
	a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);

    if(ui2_recid == APP_CFG_RECID_VID_FAC_GAIN_R){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_R_GAIN;
    }
    else if(ui2_recid == APP_CFG_RECID_VID_FAC_GAIN_G){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_G_GAIN;
    }
    else if(ui2_recid == APP_CFG_RECID_VID_FAC_GAIN_B){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_B_GAIN;
    }
    else if(ui2_recid == APP_CFG_RECID_VID_FAC_OFFSET_R){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_R_OFFSET;
    }
    else if(ui2_recid == APP_CFG_RECID_VID_FAC_OFFSET_G){
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_G_OFFSET;
    }
    else{  //APP_CFG_RECID_VID_FAC_OFFSET_G
        ui2_idx = COLOR_TUNER_FAC_ADDRESS_OFFSET_B_OFFSET;
    }

    a_cfg_eep_raw_write(
        ui4_dynamic_address + ui1_INX_color_eep_offset[i2_clr_temp][ui1_play_content] * COLOR_TUNER_FAC_PIECE_NUM + ui2_idx,
        (VOID *)&set_value,
        1,
        &ui4_written);
	
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_GAIN_R+(ui2_recid - APP_CFG_RECID_VID_FAC_GAIN_R)));
}


