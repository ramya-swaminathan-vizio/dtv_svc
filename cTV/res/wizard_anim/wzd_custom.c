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
 * $RCSfile: wzd_custom.c,v $
 * $Revision: #3 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/21 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 1433fe1fd8b5fe1dfc2a58820b53a685 $
 *
 * Description:
 *         This file contains all the customizable code in Wizard application.
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "app_util/a_cfg.h"

#include "wizard_anim/wzd.h"
#ifdef APP_USE_BDF_FONT
#include "res/fonts/a_font_tiresias.h"
#endif

#ifdef APP_GUI_TIME_ZONE_SELECTION
#include "res/theme/theme_img.h"
#endif

#include "wizard_anim/page/wzd_page_connected_tv.h"
#include "wizard_anim/page/wzd_page_nw_setup.h"
#include "wizard_anim/page/wzd_page_tv_setup.h"
#include "wizard_anim/page/wzd_page_complete.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "wizard_anim/page/wzd_page_wifi_remote_paring.h"
#include "wizard_anim/page/wzd_page_tv_remote_device_setup.h"
#include "wizard_anim/page/wzd_page_tv_name_input.h"

#ifdef APP_2K12_RETAIL_DEMO_MODE
#include "wizard_anim/page/wzd_page_choose_mode.h"
#endif
#ifndef APP_ADD_COUNTRY_CODE_SUPPORT
#include "wizard_anim/page/wzd_page_connected_tv.h"
#else
#include "wizard_anim/page/wzd_page_connected_tv_country_code.h"
#endif

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
#ifdef APP_2K12_RETAIL_DEMO_MODE
static WZD_PAGE_INFO_DATA_T     t_wzd_page_cho_mode;
#endif

static WZD_PAGE_INFO_DATA_T     t_wzd_page_lang_setting;
static WZD_PAGE_INFO_DATA_T     t_wzd_page_country_setting;

#ifdef APP_WZD_TIME_ZONE_ENABLE
static WZD_PAGE_INFO_DATA_T     t_wzd_page_time_zone;
#endif

static WZD_PAGE_INFO_DATA_T     t_wzd_wifi_remote_paring;
static WZD_PAGE_INFO_DATA_T     t_wzd_tv_remote_device_setup;

#ifdef APP_NETWORK_SUPPORT
static WZD_PAGE_INFO_DATA_T     t_wzd_page_nw_setup;
#endif
static WZD_PAGE_INFO_DATA_T     t_wzd_page_tv_setup;

static WZD_PAGE_INFO_DATA_T     t_wzd_page_tv_name_input;

#if 1
static WZD_PAGE_INFO_DATA_T     t_wzd_page_comp;
#endif

extern INT32 wzd_lang_setting_page_get_page_info_data(WZD_PAGE_INFO_DATA_T* pt_info_data);
extern INT32 wzd_lang_setting_page_nfy_sel(UINT16       ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg);
extern INT32 wzd_country_setting_page_get_page_info_data(WZD_PAGE_INFO_DATA_T* pt_info_data);
extern INT32 wzd_country_setting_page_nfy_sel(UINT16    ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg);

#ifdef APP_WZD_TIME_ZONE_ENABLE
extern INT32 wzd_time_zone_page_get_page_info_data(WZD_PAGE_INFO_DATA_T* pt_info_data);
extern INT32 wzd_time_zone_page_nfy_sel (UINT16         ui2_sel_idx,
                                  VOID*                 pv_data,
                                  WZD_MSG_CUSTOM_T*     pt_ret_msg);
#endif

/*-----------------------------------------------------------------------------
                    functions implementation
 ----------------------------------------------------------------------------*/
INT32 wzd_custom_prev_init (VOID)
{
    INT32 i4_ret;

    /* set wizard's font */
    if(!c_fe_has_font(WZD_FONT_NAME, FE_FNT_STYLE_UNIFORM))
    {
#if !defined(APP_USE_BDF_FONT)
        i4_ret = c_fe_add_mem_font(WZD_FONT_NAME,
                                   &(font_file_default [4]),
                                   GET_UINT32_FROM_PTR_BIG_END (&(font_file_default [0])),
                                   WZD_FONT_SIZE_SMALL,
                                   WZD_FONT_SIZE_MEDIUM,
                                   WZD_FONT_SIZE_LARGE);
#else
        i4_ret = c_fe_add_combine_bmp_mem_font(WZD_FONT_NAME,
                                       &(font_file_tiresias_bdf_20 [4]),
                                       GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_20 [0])),
                                       &(font_file_tiresias_bdf_24 [4]),
                                       GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_24 [0])),
                                       &(font_file_tiresias_bdf_32 [4]),
                                       GET_UINT32_FROM_PTR_BIG_END (&(font_file_tiresias_bdf_32 [0])));
#endif
        if(i4_ret != FER_OK)
        {
            return WZDR_FAIL;
        }
    }

    return WZDR_OK;
}

INT32 wzd_custom_init (VOID)
{
    /* Set gui language */
    ISO_639_LANG_T   s639_lang;

    RET_ON_ERR (a_cfg_get_gui_lang (s639_lang));
    RET_ON_ERR (wzd_set_gui_lang (s639_lang));

#ifdef APP_2K12_RETAIL_DEMO_MODE
	/* [Vizio] choose mode page */
    wzd_page_choose_mode_get_page_info_data(&t_wzd_page_cho_mode);
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_page_cho_mode, wzd_page_choose_mode_nfy_sel));
#endif

    /* [Vizio] lang setting page */
    wzd_lang_setting_page_get_page_info_data( &t_wzd_page_lang_setting );
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_page_lang_setting, wzd_lang_setting_page_nfy_sel));

    /* [Vizio] country setting page */
    wzd_country_setting_page_get_page_info_data( &t_wzd_page_country_setting );
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_page_country_setting, wzd_country_setting_page_nfy_sel));

#ifdef APP_WZD_TIME_ZONE_ENABLE
	/* [Vizio] time zone setup page */
    wzd_time_zone_page_get_page_info_data( &t_wzd_page_time_zone );
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_page_time_zone, wzd_time_zone_page_nfy_sel));
#endif

    /* [Vizio] wifi remote paring page */
    wzd_page_wifi_remote_paring_get_page_info_data( &t_wzd_wifi_remote_paring );
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_wifi_remote_paring, wzd_page_wifi_remote_paring_nfy_sel));

#ifdef APP_NETWORK_SUPPORT
    /* [Vizio] Network setup page */
    wzd_page_nw_setup_get_page_info_data(&t_wzd_page_nw_setup);
    RET_ON_ERR(wzd_page_lst_add_page(&t_wzd_page_nw_setup, wzd_page_nw_setup_nfy_sel));
#endif

    /* [Vizio] TV setup page. */
    wzd_page_tv_setup_get_page_info_data( &t_wzd_page_tv_setup );
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_page_tv_setup, wzd_page_tv_setup_nfy_sel));

    /* [Vizio] wifi remote device setup page */
    wzd_page_tv_remote_device_setup_get_page_info_data( &t_wzd_tv_remote_device_setup );
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_tv_remote_device_setup, wzd_page_tv_remote_device_setup_nfy_sel));

    /* [Vizio] TV name input page */
    wzd_page_tv_name_input_get_page_info_data( &t_wzd_page_tv_name_input );
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_page_tv_name_input, wzd_page_tv_name_input_nfy_sel));

    /* [Vizio] Setup complete page */
    wzd_page_comp_get_page_info_data( &t_wzd_page_comp );
    RET_ON_ERR(wzd_page_lst_add_page (&t_wzd_page_comp, wzd_page_comp_nfy_sel));

    return WZDR_OK;
}


INT32 wzd_custom_resume (VOID)
{
    INT32  i4_ret;
	UINT8  ui1_wzd_sts = ICL_WIZARD_STATUS_RESUME;

#if 0
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),(INT16)3);
    if(i4_ret != FER_OK)
    {
        return WZDR_FAIL;
    }

#endif
    i4_ret = a_icl_set(
            ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS), 
            (VOID *) &ui1_wzd_sts,
            ICL_RECID_WIZARD_STATUS_SIZE);
            
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
    
    i4_ret = a_cfg_custom_set_dimming_off();
    if (i4_ret != APP_CFGR_OK)
    {
        return WZDR_FAIL;
    }

    return WZDR_OK;
}

INT32 wzd_custom_pause (VOID)
{
    INT32  i4_ret;
	UINT8   ui1_wzd_sts = ICL_WIZARD_STATUS_PAUSE;

    if (a_cfg_custom_get_wifi_remote_support())
    {    
        wzd_page_tv_remote_device_reset_page_show_flag();
    }
    
    i4_ret = a_cfg_custom_update_dimming_idx();
    if (i4_ret != APP_CFGR_OK)
    {
//        return WZDR_FAIL;
        DBG_ERROR(("<WZD> %s, %d Fail=%d\n",__FUNCTION__,__LINE__,i4_ret));

    }
    #if 0
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),(INT16)0);
    if(i4_ret != FER_OK)
    {
    return WZDR_FAIL;
    }
    #endif

    i4_ret = a_icl_set(
            ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS), 
            (VOID *) &ui1_wzd_sts,
            ICL_RECID_WIZARD_STATUS_SIZE);
    
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));

    if (a_wzd_is_resume_from_menu_setup())
    {
        a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:sidebar=guided_setup\n");
    }

    return WZDR_OK;
}

INT32 wzd_custom_exit (VOID)
{
    INT32   i4_ret;
	UINT8   ui1_wzd_sts = ICL_WIZARD_STATUS_PAUSE;

    if (a_cfg_custom_get_wifi_remote_support())
    {   
        wzd_page_tv_remote_device_reset_page_show_flag();
    }

#ifdef APP_GUI_TIME_ZONE_SELECTION
    RET_ON_ERR (theme_img_deinit());
#endif
#if 0
    i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),(INT16)0);
	if(i4_ret != FER_OK)
	{
		return WZDR_FAIL;
	}
#endif
    i4_ret = a_icl_set(
            ICL_MAKE_ID(ICL_GRPID_WIZARD_STATUS, ICL_RECID_WIZARD_STATUS), 
            (VOID *) &ui1_wzd_sts,
            ICL_RECID_WIZARD_STATUS_SIZE);
    DBG_INFO(("i4_ret=%d\n", i4_ret));
    
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
    
    return WZDR_OK;
}

/* wizard status */
INT32 wzd_custom_set_status (UINT8*     pui1_state,
                             UINT8*     pui1_page_idx)
{
    return WZDR_OK;
}


INT32 wzd_custom_get_status (UINT8*     pui1_state,
                             UINT8*     pui1_page_idx)
{
    return WZDR_OK;
}


