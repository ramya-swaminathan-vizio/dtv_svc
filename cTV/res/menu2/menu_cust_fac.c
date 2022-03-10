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
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_lnk_list.h"
#include "u_drv_cust.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_scc.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_wgl_image.h"
#include "c_fe.h"
#include "c_version.h"
#include "u_wgl_rect.h"

#include "amb/a_amb.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "app_util/a_drv_interface.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "menu_cust_define.h"
#include "res/menu2/menu_config.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_common/menu_common.h"
#include "nav/burning_mode/burning_mode.h"
#include "nav/input_src/a_input_src.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
#if 0 //Amtran Mark here
MENU_ITEM_T     t_g_menu_custom_item_fac_adc_gain_r;
MENU_ITEM_T     t_g_menu_custom_item_fac_adc_gain_g;
MENU_ITEM_T     t_g_menu_custom_item_fac_adc_gain_b;
MENU_ITEM_T     t_g_menu_custom_item_fac_adc_offset_r;
MENU_ITEM_T     t_g_menu_custom_item_fac_adc_offset_g;
MENU_ITEM_T     t_g_menu_custom_item_fac_adc_offset_b;

static BOOL     b_custom_ver_show_curr;
static UINT16   ui2_custom_ver_key_list_ptr;
static UINT32   aui4_custom_ver_key_list[VERSION_KEY_LIST_SIZE];
static UINT32   aui4_custom_ver_key_list_pattern[VERSION_KEY_LIST_SIZE] = {BTN_DIGIT_3, BTN_DIGIT_4, BTN_DIGIT_8, BTN_DIGIT_1};                      

/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    static functions implementation
 ----------------------------------------------------------------------------*/

static VOID _set_fac_adc_gain_r_val(INT32 i4_val)
{
}

static INT32 _get_fac_adc_gain_r_val(VOID)
{
    return 0;
}
static VOID _set_fac_adc_gain_g_val(INT32 i4_val)
{
}
static INT32 _get_fac_adc_gain_g_val(VOID)
{
    return 0;
}
static VOID _set_fac_adc_gain_b_val(INT32 i4_val)
{
}

static INT32 _get_fac_adc_gain_b_val(VOID)
{
    return 0;
}
static VOID _set_fac_adc_offset_r_val(INT32 i4_val)
{
}

static INT32 _get_fac_adc_offset_r_val(VOID)
{
    return 0;
}
static VOID _set_fac_adc_offset_g_val(INT32 i4_val)
{
}

static INT32 _get_fac_adc_offset_g_val(VOID)
{
    return 0;
}
static VOID _set_fac_adc_offset_b_val(INT32 i4_val)
{
}

static INT32 _get_fac_adc_offset_b_val(VOID)
{
    return 0;
}

static BOOL _version_put_key(
    UINT32 ui4_key
)
{
    UINT32  ui4_i, ui4_j;
    BOOL    b_show = TRUE;

    /* Make Klocwork happy */
    if(ui2_custom_ver_key_list_ptr >= VERSION_KEY_LIST_SIZE)
    {
        return FALSE;
    }

    aui4_custom_ver_key_list[ui2_custom_ver_key_list_ptr++] = ui4_key;
    ui2_custom_ver_key_list_ptr %= VERSION_KEY_LIST_SIZE;
    
    for(ui4_i = 0, ui4_j = ui2_custom_ver_key_list_ptr; 
        ui4_i<VERSION_KEY_LIST_SIZE;
        ui4_i++, ui4_j=(ui4_j+1)%VERSION_KEY_LIST_SIZE)
    {
        if(aui4_custom_ver_key_list[ui4_j] !=  aui4_custom_ver_key_list_pattern[ui4_i])
        {
            b_show = FALSE;
            break;
        }
    }

    return b_show;
}


/*-----------------------------------------------------------------------------
                    public functions implementation
 ----------------------------------------------------------------------------*/
BOOL   menu_custom_version_key_filter(UINT32    ui4_keycode)
{
    BOOL    b_ver_show_next;
    BOOL    b_processed;
    UINT32      ui4_page_crnt, ui4_page_id;
    HANDLE_T    h_focus, h_btn;
    BOOL        b_one_tab_mode;

    /* put the key into the key list */
    b_ver_show_next = _version_put_key(ui4_keycode);

    //DBG_LOG_PRINT ((" ## b_custom_ver_show_curr = %d  \n", b_custom_ver_show_curr));
    //DBG_LOG_PRINT ((" ## b_custom_ver_show_next = %d  \n", b_ver_show_next));

    /* Check condition */
    c_wgl_get_focus(&h_focus);
    menu_nav_get_crnt_page( &ui4_page_crnt);
    menu_version_tab_info( &b_one_tab_mode, &ui4_page_id, &h_btn);

    //DBG_LOG_PRINT (" ## b_custom_b_one_tab_mode = %d  \n", b_one_tab_mode);
    //DBG_LOG_PRINT (" ## b_custom_ui4_page_crnt  = %d  \n", ui4_page_crnt);
    //DBG_LOG_PRINT (" ## b_custom_ui4_page_id    = %d  \n", ui4_page_id);
    //DBG_LOG_PRINT (" ## b_custom_h_focus        = %d  \n", h_focus);
    //DBG_LOG_PRINT (" ## b_custom_h_btn          = %d  \n", h_btn);

    if(b_one_tab_mode)
    {
        /* if in one tab mode, open when in the first page */
        if(ui4_page_crnt != ui4_page_id)
        {
            b_ver_show_next = FALSE;
        }
    }
    else
    {
        /* check if the focus is the first tab */
        if(h_focus != h_btn)
        {
            b_ver_show_next = FALSE;
        }
    }


    /* show or hide the version information */
    if(!b_custom_ver_show_curr && b_ver_show_next)
    {
        if( ui4_page_factory != (UINT32)0xFFFFFFFF)
        {
            UINT8	ui1_fac_mode = APP_CFG_FAC_MODE_NORMAL;
            a_cfg_get_factory_mode(&ui1_fac_mode);

            if(ui1_fac_mode == APP_CFG_FAC_MODE_NORMAL)
            {
                ui1_fac_mode = APP_CFG_FAC_MODE_FACTORY; 
                /* If it is not in factory mode, enter factory mode */
                a_cfg_set_factory_mode(ui1_fac_mode);

                a_cfg_update_factory_mode();

                /* flush the settings to storage right away */
                a_cfg_store();
            }
            menu_show_version(TRUE, FALSE);
            menu_nav_go(ui4_page_factory, NULL);
            menu_show_backbar(TRUE,FALSE);
        }
        else
        {
            menu_show_version(TRUE, TRUE);
        }
        b_processed = TRUE;
    }
    else if(b_custom_ver_show_curr && b_ver_show_next)
    {
        menu_show_version(FALSE, TRUE);
        menu_nav_go(ui4_g_menu_page_main_menu, NULL);
        b_processed = TRUE;
    }
    else if(b_custom_ver_show_curr && !b_ver_show_next)
    {
        menu_show_version(FALSE, TRUE);
        b_processed = FALSE;
    }
    else
    {
        /* no-op */
        b_processed = FALSE;
    }
    
    b_custom_ver_show_curr = b_ver_show_next;

    return b_processed;
}

INT32  menu_cust_fac_init(VOID)
{
    return MENUR_OK;
}

INT32 menu_cust_fac_settings_init(VOID)
{
    INT32 i4_ret;

    i4_ret = menu_page_tree_range_item(&t_g_menu_custom_item_fac_adc_gain_r,
                                       MLM_MENU_KEY_VID_CLR_GAIN_R,
                                       MLM_MENU_KEY_VID_CLR_GAIN_R,
                                       0,
                                       254,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                       _set_fac_adc_gain_r_val,
                                       _get_fac_adc_gain_r_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_custom_item_fac_adc_gain_r.u.t_range.pf_incr = NULL;
    t_g_menu_custom_item_fac_adc_gain_r.u.t_range.pf_decr = NULL;

    i4_ret = menu_page_tree_range_item(&t_g_menu_custom_item_fac_adc_gain_g,
                                       MLM_MENU_KEY_VID_CLR_GAIN_G,
                                       MLM_MENU_KEY_VID_CLR_GAIN_G,
                                       0,
                                       254,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                        _set_fac_adc_gain_g_val,
                                        _get_fac_adc_gain_g_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_custom_item_fac_adc_gain_g.u.t_range.pf_incr = NULL;
    t_g_menu_custom_item_fac_adc_gain_g.u.t_range.pf_decr = NULL;	

    i4_ret = menu_page_tree_range_item(&t_g_menu_custom_item_fac_adc_gain_b,
                                       MLM_MENU_KEY_VID_CLR_GAIN_B,
                                       MLM_MENU_KEY_VID_CLR_GAIN_B,
                                       0,
                                       254,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                        _set_fac_adc_gain_b_val,
                                        _get_fac_adc_gain_b_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_custom_item_fac_adc_gain_b.u.t_range.pf_incr = NULL;
    t_g_menu_custom_item_fac_adc_gain_b.u.t_range.pf_decr = NULL;	

    i4_ret = menu_page_tree_range_item(&t_g_menu_custom_item_fac_adc_offset_r,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_R,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_R,
                                       0,
                                       254,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                        _set_fac_adc_offset_r_val,
                                        _get_fac_adc_offset_r_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_custom_item_fac_adc_offset_r.u.t_range.pf_incr = NULL;
    t_g_menu_custom_item_fac_adc_offset_r.u.t_range.pf_decr = NULL;	

    i4_ret = menu_page_tree_range_item(&t_g_menu_custom_item_fac_adc_offset_g,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_G,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_G,
                                       0,
                                       254,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                        _set_fac_adc_offset_g_val,
                                        _get_fac_adc_offset_g_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_custom_item_fac_adc_offset_g.u.t_range.pf_incr = NULL;
    t_g_menu_custom_item_fac_adc_offset_g.u.t_range.pf_decr = NULL;	

    i4_ret = menu_page_tree_range_item(&t_g_menu_custom_item_fac_adc_offset_b,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_B,
                                       MLM_MENU_KEY_VID_CLR_OFFSET_B,
                                       0,
                                       254,
                                       MENU_ITEM_RANGE_STYLE_BAR,
                                        _set_fac_adc_offset_b_val,
                                        _get_fac_adc_offset_b_val);
    MENU_CHK_FAIL(i4_ret);
    t_g_menu_custom_item_fac_adc_offset_b.u.t_range.pf_incr = NULL;
    t_g_menu_custom_item_fac_adc_offset_b.u.t_range.pf_decr = NULL;

    return MENUR_OK;
}

#else//AmTRAN start here

BOOL   (*menu_custom_version_key_filter_fac)(UINT32    ui4_keycode);
INT32  (*menu_cust_fac_settings_init_fac)(VOID);
INT32  (*menu_cust_fac_init_fac)(VOID);

INT32  menu_cust_fac_init(VOID)
{
	if (menu_cust_fac_init_fac != NULL)
	{
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__));
		menu_cust_fac_init_fac();
	}
    return MENUR_OK;
}

BOOL   menu_custom_version_key_filter(UINT32    ui4_keycode)
{
    BOOL    b_processed;
	if ( menu_custom_version_key_filter_fac != NULL)
	{
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__));
		b_processed = menu_custom_version_key_filter_fac(ui4_keycode);
	}
	else
    {
        /* no-op */
        b_processed = FALSE;
    }
	return b_processed;
}
INT32 menu_cust_fac_settings_init(VOID)
{
	if (menu_cust_fac_settings_init_fac != NULL)
	{
		DBG_LOG_PRINT(("[cTV][%s] %s() %d:========= \r\n", __FILE__, __FUNCTION__, __LINE__));
		menu_cust_fac_settings_init_fac();
	}
	return MENUR_OK;
}
#endif //AmTRAN
