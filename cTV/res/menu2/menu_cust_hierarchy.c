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
 * $RCSfile: menu_hierarchy.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/21 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 1433fe1fd8b5fe1dfc2a58820b53a685 $
 *
 * Description:
 *         This file contains all the customizable code in menu.
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_irrc_btn_def.h"
#include "u_sm_video_hdlr.h"

#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_svl.h"
#include "c_cfg.h"
#include "c_tsl.h"
#include "c_svctx.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_ui.h"
#include "app_util/a_tv.h"
#include "app_util/a_isl.h"
#include "app_util/a_sleep_timer.h"
#include "app_util/a_rating.h"
#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "menu2/menu_page_tree.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_cust_define.h"

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/acfg_cust_factory.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
#if 0  //AmTRAN Mark here

static UINT32 ui4_page_fac;
static UINT32 ui4_page_reset_fac;
static UINT32 ui4_page_fac_clr_tmp;
static UINT32 ui4_page_auto_color;
static UINT32 ui4_page_fac_more;
static UINT32 ui4_page_fac_audio;
static UINT32 ui4_page_auto_phase;

static MENU_ITEM_T t_menu_item_page_reset_fac;

static MENU_ITEM_T t_menu_item_page_fac_more;
static MENU_ITEM_T t_menu_item_page_fac_audio;
static MENU_ITEM_T t_menu_item_page_fac_clr_tmp;
static MENU_ITEM_T t_menu_item_page_fac_auto_phase;

/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    static functions implementation
 ----------------------------------------------------------------------------*/


static BOOL _is_vga_hidden(VOID)
{
    ISL_REC_T   t_isl_rec;

    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
       t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}



static BOOL _is_adv_vid_hidden(VOID)
{
    return !_is_vga_hidden();
}

static VOID _clean_svl_and_tsl(VOID)
{
    INT32 i4_ret = 0;

    /* clean air svl */
    if (t_g_menu_common.h_svl_air != NULL_HANDLE)
    {
        i4_ret = c_svl_clean(t_g_menu_common.h_svl_air);
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Failed to clean Air SVL in the memory. [i4_ret = %d]\r\n", i4_ret));
        }

        t_g_menu_common.b_svl_air_dirty = TRUE;
    }

    /* clean cable svl */
    if (t_g_menu_common.h_svl_cable != NULL_HANDLE)
    {
        i4_ret = c_svl_clean(t_g_menu_common.h_svl_cable);
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Failed to clean Cable SVL in the memory. [i4_ret = %d]\r\n", i4_ret));
        }

        t_g_menu_common.b_svl_cable_dirty = TRUE;
    }

    /* clean air tsl */
    if (t_g_menu_common.h_tsl_air != NULL_HANDLE)
    {
        i4_ret = c_tsl_clean(t_g_menu_common.h_tsl_air);
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Failed to clean Air SVL in the memory. [i4_ret = %d]\r\n", i4_ret));
        }

        t_g_menu_common.b_tsl_air_dirty = TRUE;
    }

    /* clean cable tsl */
    if (t_g_menu_common.h_tsl_cable != NULL_HANDLE)
    {
        i4_ret = c_tsl_clean(t_g_menu_common.h_tsl_cable);
        if (i4_ret != SBR_OK)
        {
            DBG_ERROR(("<MENU>Failed to clean Cable SVL in the memory. [i4_ret = %d]\r\n", i4_ret));
        }

        t_g_menu_common.b_tsl_cable_dirty = TRUE;
    }
}

static VOID _reset_fac(VOID)
{
    _clean_svl_and_tsl();

    a_sleep_timer_stop();

    a_rating_atsc_storage(FALSE);

    menu_custom_chg_lang();
}

INT32 menu_custom_init_factory_tree(VOID)
{
    INT32 i4_ret;

    UINT16 ui2_item_id;

    /*----------------------------------------------------------------*/
    /*                        Create all pages                        */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_create(13,
                                   MLM_MENU_KEY_FACTORY,
                                   &ui4_page_fac);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_MORE,
                                   &ui4_page_fac_audio);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_MORE,
                                   &ui4_page_fac_more);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_create(10,
                                   MLM_MENU_KEY_VID_CLR_TEMP,
                                   &ui4_page_fac_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_auto_color,
                                 NULL,
                                 &ui4_page_auto_color);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_common_page_simple_dialog_create(MLM_MENU_KEY_RESET_CONFIRM,
                                                   MLM_MENU_KEY_YES,
                                                   MLM_MENU_KEY_NO,
                                                   UI_SIMPLE_DIALOG_STYLE_SMALL,
                                                   WGL_AS_CENTER_CENTER,
                                                   FALSE,
                                                   _reset_fac,
                                                   NULL,
                                                   &ui4_page_reset_fac);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                          Subpage Items                         */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_more_item(&t_menu_item_page_fac_more,
                                         MLM_MENU_KEY_VID_MORE,
                                         MLM_MENU_KEY_HELP_VID_MORE,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_fac_more);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_more_item(&t_menu_item_page_fac_audio,
                                         MLM_MENU_KEY_AUD,
                                         MLM_MENU_KEY_AUD,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_fac_audio);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_fac_clr_tmp,
                                         MLM_MENU_KEY_VID_CLR_TEMP,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_fac_clr_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_fac_auto_phase,
                                         MLM_MENU_KEY_VID_AUTO_PHASE,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_auto_phase);
    MENU_LOG_ON_FAIL(i4_ret);	
    
    i4_ret = menu_page_tree_subpage_item(&t_menu_item_page_reset_fac,
                                         MLM_MENU_KEY_RESET_FAC,
                                         MLM_MENU_KEY_EMPTY,
                                         MLM_MENU_KEY_EMPTY,
                                         ui4_page_reset_fac);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                      factory menu item                        */
    /*----------------------------------------------------------------*/

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_audio,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    
    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_clr_tmp,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_auto_phase,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac,
                                &t_menu_item_page_fac_more,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);
    /*----------------------------------------------------------------*/
    /*                          Color Temp. Page                      */
    /*----------------------------------------------------------------*/

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_clr_tmp_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_fac_clr_tmp,
                                          ui2_item_id,
                                          _is_adv_vid_hidden);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_custom_item_vga_clr_tmp_mode,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_set_auto_hide(ui4_page_fac_clr_tmp,
                                          ui2_item_id,
                                          _is_vga_hidden);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_gain_r,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_gain_g,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_gain_b,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_offset_r,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_offset_g,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_tree_add(ui4_page_fac_clr_tmp,
                                &t_g_menu_common_item_vid_fac_clr_offset_b,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /*----------------------------------------------------------------*/
    /*                          Audio. Page                      */
    /*----------------------------------------------------------------*/

    /*----------------------------------------------------------------*/
    /*                          More. Page                      */
    /*----------------------------------------------------------------*/
    i4_ret = menu_page_tree_add(ui4_page_fac_more,
                                &t_menu_item_page_reset_fac,
                                &ui2_item_id);
    MENU_LOG_ON_FAIL(i4_ret);    

    /*----------------------------------------------------------------*/
    /*                          factory menu root page                     */
    /*----------------------------------------------------------------*/
    /* Set the Factory Page */
    i4_ret = menu_factory_set_pageid(ui4_page_fac);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

#ifdef APP_MENU_CUSTOM_FACTORY_TREE
INT32 menu_cust_fact_exit(VOID)
{
    return AEER_OK;
}

BOOL menu_cust_fact_is_reset_page(UINT32 ui4_page_id)
{
    BOOL    b_reset_page = FALSE;

    return b_reset_page;
}
#endif

#else //AmTRAN

INT32  (*menu_custom_init_factory_tree_fac)(VOID);
INT32  (*menu_cust_fact_exit_fac)(VOID);
BOOL   (*menu_cust_fact_is_reset_page_fac)(UINT32 ui4_page_id);

INT32 menu_custom_init_factory_tree(VOID)
{
	if (menu_custom_init_factory_tree_fac != NULL)
	{
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__)); 		
		menu_custom_init_factory_tree_fac();
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__)); 
	}
	return MENUR_OK;
}
INT32 menu_cust_fact_exit(VOID)
{
	if (menu_cust_fact_exit_fac != NULL)
	{
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__)); 		
		menu_cust_fact_exit_fac();
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__)); 
	}
    return AEER_OK;
}

BOOL menu_cust_fact_is_reset_page(UINT32 ui4_page_id)
{
    BOOL    b_reset_page = FALSE;
	if (menu_cust_fact_is_reset_page_fac != NULL)
	{
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__)); 
		menu_cust_fact_is_reset_page_fac(ui4_page_id);
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__)); 
	}
    return b_reset_page;
}

	
#endif  //AmTRAN end

