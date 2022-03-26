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
 * $RCSfile: wzd.c,v $
 * $Revision: #3 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/83 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: eb4ae9a8652dff0d32b151035a33837c $
 *
 * Description:
 *         This file contains the implementation of the API's of Wizard.
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "agent/agent.h"
#include "c_scc.h"
#include "wizard_anim/wzd.h"
#ifdef APP_DVBC_SUPPORT
#include "wizard_anim/page/wzd_page_dvbc.h"
#endif
#include "wizard_anim/page/wzd_page_nw_setup.h"
#include "wizard_anim/page/wzd_page_tv_remote_device_setup.h"
#include "wizard_anim/page/wzd_page_tv_name_input.h"
#include "wizard_anim/page/wzd_page_tv_setup.h"
#include "menu2/menu_common/menu_common.h"

#ifdef APP_2K12_RETAIL_DEMO_MODE
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "wizard_anim/page/wzd_page_choose_mode.h"
#endif

#ifdef APP_DVBS_SUPPORT
#include "c_satl.h"
#endif

#include "res/app_util/a_custom_log.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "app_util/config/_acfg.h"

#include "res/app_util/network/network_custom.h"

#include "nav/updater/a_nav_updater.h"

#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#include "c_cecm.h"
#include "nav/cec2/nav_cec.h"
#include "res/nav/cec2/nav_cec_custom.h"
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#endif

#include "rest/a_rest_event.h"
#include "rest/rest.h"
#include "res/app_util/icl/a_icl_custom.h"

#ifdef APP_C4TV_SUPPORT
#define APP_ID "BBA3248B"
#include "rest/a_rest_api.h"
#endif

#include "wzd_dbg.h"

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
/* global wizard variable */
WZD_T t_g_wzd = {0} ;

UINT8 ui1_launch_count = 0;
UINT8 ui1_launch_count_threshold = 5;
UINT8 ui1_launch_oobe_start_status = 0; /* OOBE start page status, bit0~6: counter, bit7:started */
BOOL ui1_launch_oobe_sucess = TRUE; 


HANDLE_T            gh_dlg = NULL_HANDLE;

static BOOL         b_g_small_video_enable = FALSE;

static BOOL         b_g_is_mute = FALSE;
static BOOL         b_g_is_wzd_startup_first_time = TRUE;
static BOOL         b_g_is_need_power_off_dlg_show = FALSE;
static BOOL         b_g_is_need_animation = FALSE;

static SCC_AUD_SPDIF_FMT_T e_g_spdif_value = SCC_AUD_SPDIF_FMT_PCM_24;

#ifndef APP_C4TV_SUPPORT
/* power off dialog previous focus handle */
static HANDLE_T h_pre_btn_focus = NULL_HANDLE;
#endif

static WZD_PAGE_NAVI_T e_g_navi = WZD_PAGE_NAVI_LAST_VALID_ITEM;




/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/
/* AEE lifecycle callback functions */
static INT32 _wzd_app_init_fct (const CHAR* ps_name, HANDLE_T h_app);
static INT32 _wzd_app_resume_fct (HANDLE_T h_app);
static INT32 _wzd_app_pause_fct (HANDLE_T h_app);
static INT32 _wzd_app_exit_fct (HANDLE_T h_app, APP_EXIT_MODE_T e_exit_mode);
static INT32 _wzd_app_process_msg_fct (HANDLE_T h_app, UINT32 ui4_type, const VOID* pv_msg, SIZE_T z_msg_len, BOOL b_paused);

/* Power sequence callback function */
static BOOL  _wzd_app_power_seq_cb (VOID);

/* Send message notification function */
static BOOL  _wzd_app_nfy_fct (HANDLE_T h_app, VOID* pv_tag, APP_NFY_REASON_T e_nfy_reason);

/* middleware notification functions */
static INT32 _wzd_nfy_wgl (UINT32 ui4_msg, VOID* pv_param1, VOID* pv_param2);
#ifdef APP_WZD_AUTO_PAUSE
static VOID  _wzd_nfy_timer (HANDLE_T h_timer, VOID* pv_tag);
#endif
static VOID  _wzd_nfy_scan_timer (HANDLE_T h_timer, VOID* pv_tag);

/* page functions */
static INT32 _wzd_btn_select (VOID);
static INT32 _wzd_btn_return (VOID);
static INT32 _wzd_btn_exit (VOID);
static INT32 _wzd_btn_cursor_up (VOID);
static INT32 _wzd_btn_cursor_down (VOID);
static INT32 _wzd_btn_cursor_left (VOID);
static INT32 _wzd_btn_cursor_right (VOID);
static INT32 _wzd_btn_change_focus (VOID);
static INT32 _wzd_page_anim_finish (VOID);

static INT32 _wzd_page_lst_get_page_entry (UINT8 ui1_page_idx, WZD_PAGE_INFO_T** ppt_crnt_page);

/* setting list functions */
/*static INT32 _wzd_seti_lst_nfy_sel (WZD_MSG_CUSTOM_T* pt_ret_msg);*/
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
static INT32 _wzd_code_box_nfy_sel (WZD_MSG_CUSTOM_T* pt_ret_msg);
#endif
static INT32 _wzd_seti_lst_clean (VOID);
static INT32 _wzd_seti_lst_update (WZD_PAGE_INFO_T* pt_page, BOOL b_repaint);

/* setting icon function */
static INT32 _wzd_seti_icon_update (WZD_PAGE_INFO_T* pt_page, BOOL b_repaint);

/* title list function */
static INT32 _wzd_title_lst_update (WZD_PAGE_INFO_T* pt_page, BOOL b_repaint);

/* help list function */
static INT32 _wzd_help_lst_update (WZD_PAGE_INFO_T* pt_page, BOOL b_repaint);
static INT32 _wzd_scan_help_lst_update (BOOL b_stop, BOOL b_repaint);

/* description text function */
static INT32 _wzd_desc_txt_update (WZD_PAGE_INFO_T* pt_page, BOOL b_repaint);
#if 0
static INT32 _wzd_scan_desc_txt_update(UINT16 ui2_txt_key, BOOL b_step, BOOL b_repaint);
#endif

/* wrapper function for pages of the template layout. */
static INT32 _wzd_show_update(UINT8 ui1_page_idx, BOOL b_repaint);

#ifndef APP_C4TV_SUPPORT
static INT32 _wzd_show_clean(VOID);
#endif

/* scan functions */
static INT32 _wzd_scan_start (VOID);
static INT32 _wzd_scan_progress (SB_NFY_MSG_T* pt_sb_nfy);
static INT32 _wzd_scan_end (VOID);

/* wizard status stored in acfg */
static INT32 _wzd_set_status (VOID);
static INT32 _wzd_get_status (VOID);

/* svl & config */
static INT32 _wzd_store_svl_and_config (VOID);

#ifndef APP_C4TV_SUPPORT
static INT32 _wzd_enable_tv_src (BOOL b_enable);
#endif

#ifdef APP_DVBT_SUPPORT
static INT32 wzd_get_nwl_info(VOID);
#endif

//static INT32 _wzd_reset_lightsensor_and_backlight(VOID);

#ifndef APP_C4TV_SUPPORT
static VOID _wzd_show_power_off_dlg (VOID);
static VOID _wzd_show_power_off_dlg_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3);
#endif

extern INT32 a_c4tv_apron_suspend_cast(c4tv_apron_custom_nfy_fct pf_nfy,C4TV_APRON_SUSPEND_REASON e_suspend_reason);
extern INT32 a_c4tv_apron_register_launch_nfy(c4tv_apron_custom_nfy_fct pf_nfy);
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

VOID _wzd_dlg_data_chg(VOID*    pv_tag,
                                 UINT32   ui4_msg,
                                 VOID*    pv_param1,
                                 VOID*    pv_param2)
{

    switch( ui4_msg )
    {
        case WZD_DLG_MSG_BTN_FOCUSED:
            DBG_INFO(( "[WZD][DLG CLI Test] WZD_DLG_MSG_BTN_FOCUSED received, btn index =%d\n", (UINT32)pv_param1 ));
            break;

        case WZD_DLG_MSG_KEY_INPUT:
            DBG_INFO(( "[WZD][DLG CLI Test] WZD_DLG_MSG_KEY_INPUT received, keycode =%d\n", (UINT32)pv_param1 ));
            if( (BTN_SELECT == (UINT32)pv_param1) || (BTN_EXIT == (UINT32)pv_param1) )
            {
                wzd_dlg_hide( gh_dlg );
            }
            break;

        case WZD_DLG_MSG_HIDE_TIMEOUT:
            DBG_INFO(( "[WZD][DLG CLI Test] WZD_DLG_MSG_HIDE_TIMEOUT received\n" ));
            wzd_dlg_hide( gh_dlg );
            break;

        case WZD_DLG_MSG_DLG_HIDED:
            DBG_INFO(( "[WZD][DLG CLI Test] WZD_DLG_MSG_DLG_HIDED received\n" ));
            break;

        default:
            break;
    }

}

/*----------------------------------------------------------------------------
 * Name:    _wzd_cli_resume_app
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_create_dialog (VOID)
{
    WZD_DLG_INIT_T      t_dlg_init;
    HANDLE_T            h_layout_frm = NULL_HANDLE;

    c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_AUTO_HIDE;
    t_dlg_init.pf_fct = _wzd_dlg_data_chg;
    t_dlg_init.pv_tag = NULL;
    t_dlg_init.ui4_hide_timer = 10*1000;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;

    wzd_dlg_create( &t_dlg_init, &gh_dlg );

    wzd_dlg_set_text( gh_dlg, L"aaaa\nbbbbbbbbbbbbbb\nccccccccccccccccccccc\nddd", TRUE );

    wzd_dlg_set_btn_text( gh_dlg, WZD_DLG_BTN_TYPE_01, L"OK", TRUE );

    wzd_dlg_set_btn_text( gh_dlg, WZD_DLG_BTN_TYPE_02, L"Cancel", TRUE );

    wzd_dlg_show(gh_dlg , TRUE);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_cli_resume_app
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_destroy_dialog (VOID)
{
    HANDLE_T            h_layout_frm = NULL_HANDLE;

    if( gh_dlg )
    {
        wzd_dlg_hide( gh_dlg );
    }

    wzd_dlg_destroy( gh_dlg );

    wzd_view_get_layout_frm(&h_layout_frm);

    if( h_layout_frm )
    {
        c_wgl_set_focus(h_layout_frm, TRUE);
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_get_prev_page
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_get_prev_page (
    UINT8                       ui1_page_idx ,
    UINT8*                      pui1_prv_pg_idx
    )
{
    if (!pui1_prv_pg_idx || ui1_page_idx >= t_g_wzd.ui1_page_num)
    {
        return WZDR_INV_ARG ;
    }

    if (0 == ui1_page_idx)
    {
        /* already in first page */
        *pui1_prv_pg_idx = ui1_page_idx ;
    }
#if defined(APP_DVBC_SUPPORT) || defined(APP_DVBS_SUPPORT)
    else if (t_g_wzd.ui1_page_num -1 == ui1_page_idx)
    {
        /* skip all scan pages (prepare_data_for_dvbc page and scan/skip page) */
        ASSERT_APPL (0 ,t_g_wzd.ui1_page_num >= 4 ,("total page is less than 4,cannot use these code!!!\r\n")) ;
        *pui1_prv_pg_idx = ui1_page_idx - 3 ;
    }
#endif
    else
    {
        *pui1_prv_pg_idx = (UINT8)(ui1_page_idx - 1) ;

		if (!a_cfg_custom_get_wifi_remote_support())
		{
			if ( WZD_PAGE_INDEX_WIFI_REMOTE_PARING == *pui1_prv_pg_idx )
			{
			#ifdef APP_WZD_TIME_ZONE_ENABLE
				*pui1_prv_pg_idx = WZD_PAGE_INDEX_TIME_ZONE;
			#else
				*pui1_prv_pg_idx = WZD_PAGE_INDEX_COUNTRY;
			#endif
			}
			else if (WZD_PAGE_TV_REMOTE_DEVICE_SETUP == *pui1_prv_pg_idx)
			{
				*pui1_prv_pg_idx = WZD_PAGE_INDEX_TV_SETUP;
			}
		}
    }

    return WZDR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_get_next_page
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_get_next_page (
    UINT8                       ui1_page_idx ,
    UINT8*                      pui1_prv_pg_idx
    )
{
    if (!pui1_prv_pg_idx || ui1_page_idx >= t_g_wzd.ui1_page_num)
    {
        return WZDR_INV_ARG ;
    }

    if (t_g_wzd.ui1_page_num - 1 == ui1_page_idx) /* already in last page */
    {
        *pui1_prv_pg_idx = ui1_page_idx ;
    }
    else
    {
        *pui1_prv_pg_idx = (UINT8)(ui1_page_idx + 1) ;

        if (!a_cfg_custom_get_wifi_remote_support())
        {
            if ( WZD_PAGE_INDEX_WIFI_REMOTE_PARING == *pui1_prv_pg_idx )
            {
                *pui1_prv_pg_idx = WZD_PAGE_INDEX_NW_SETUP;
            }
            else if (WZD_PAGE_TV_REMOTE_DEVICE_SETUP == *pui1_prv_pg_idx)
            {
                *pui1_prv_pg_idx = WZD_PAGE_TV_NAME_INPUT;
            }
        }
    }

    return WZDR_OK ;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_app_nfy_fct
 *
 * Description: This function is called in the thread context of the Wizard
 *              application when a message is received, and when a message is
 *              processed. When a message is received, this API will be called
 *              with one of the APP_NFY_PRE_* notifiction reasons. In that case,
 *              this API should return TRUE if the message is to be ignored, or
 *              FALSE if the message is to be processed. If the message is
 *              processed, then this API will be called again, this time after
 *              the message is processed, with one of the APP_NFY_*_OK or
 *              APP_NFY_*_FAILED notification reasons.
 *
 * Inputs:  h_app               Contains the application handle.
 *          pv_tag              References a tag value. An asynchronous call is
 *                              made if pv_tag is NULL, or a synchronous call is
 *                              made if pv_tag is not a NULL pointer.
 *          e_nfy_reason        Contains the notification reason.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_app_nfy_fct (HANDLE_T           h_app,
                             VOID*               pv_tag,
                             APP_NFY_REASON_T    e_nfy_reason)
{
    /*
    TRUE  = ignore message
    FALSE = process message
    */

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_app_init_fct
 *
 * Description: This function is called in the context of the Wizard
 *              application when the application starts.
 *
 * Inputs:  ps_name             References the application's name.
 *          h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_app_init_fct (const CHAR*    ps_name,
                                HANDLE_T       h_app)
{
    DBG_INFO (("<WZD> initializing Wizard (application handle = %d)\n\r", h_app));

    /* reset variables */
    c_memset (& t_g_wzd, 0, sizeof (WZD_T));

    /* copy handle */
    t_g_wzd.h_wzd = h_app;

    /* eable the button select. Now, the arrow_right also works as btn_select */
    t_g_wzd.b_btn_select = TRUE;

    /* long press panel key flag is false */
    t_g_wzd.b_g_is_panel_key_long_press = FALSE;

#ifdef APP_C4TV_SUPPORT
    /* create timer to check oobe process status */
    RET_ON_ERR (c_timer_create (& t_g_wzd.h_timer_oobe));
    t_g_wzd.b_g_is_oobe_recovery = FALSE;
#ifdef APP_WZD_AUTO_PAUSE
    /* create auto-pause timer */
    RET_ON_ERR (c_timer_create (& t_g_wzd.h_timer_pause));
#endif
#else
    /* customized prev-init fct */
    RET_ON_ERR (wzd_custom_prev_init ());

    /* Open Service Context */
    RET_ON_ERR (c_svctx_open(SVCTX_NAME_MAIN, & t_g_wzd.h_svctx));

    /* initialize utility */
    RET_ON_ERR (wzd_util_init ());

    /* initialize cli */
    RET_ON_ERR (wzd_cli_init ());

    /* register to Widget Library */
    RET_ON_ERR (c_wgl_register (_wzd_nfy_wgl));

    /* set delay tolerance - in milliseconds */
    RET_ON_ERR (c_wgl_set_delay_tolerance (WGL_MSG_MAX_DELAY));

    /* initialize view */
    RET_ON_ERR (wzd_view_init ());

    /* initialize animation */
    RET_ON_ERR (wzd_anim_init());

#ifdef APP_WZD_AUTO_PAUSE
    /* create auto-pause timer */
    RET_ON_ERR (c_timer_create (& t_g_wzd.h_timer_pause));
#endif
    /* create animation scan timer */
    RET_ON_ERR (c_timer_create (& t_g_wzd.h_timer_scan));

	/* create dialog auto hide timer */
    RET_ON_ERR (c_timer_create (& t_g_wzd.h_timer_dlg));

    /* create the SVL/TSL/NWL/LOL of the Air */
    RET_ON_ERR (c_svl_open (LST_TER_SVL_ID, NULL, NULL, & t_g_wzd.h_air_svl));
    RET_ON_ERR (c_tsl_open (LST_TER_TSL_ID, NULL, NULL, & t_g_wzd.h_air_tsl));
#ifndef APP_LOL_NWL_DISABLE
    RET_ON_ERR (c_nwl_open (LST_TER_NWL_ID, NULL, NULL, & t_g_wzd.h_air_nwl));
    RET_ON_ERR (c_lol_open (LST_TER_LOL_ID, NULL, NULL, & t_g_wzd.h_air_lol));
#endif

    /* create the SVL/TSL/NWL/LOL of the Cable */
    RET_ON_ERR (c_svl_open (LST_CAB_SVL_ID, NULL, NULL, & t_g_wzd.h_cab_svl));
    RET_ON_ERR (c_tsl_open (LST_CAB_TSL_ID, NULL, NULL, & t_g_wzd.h_cab_tsl));
#ifndef APP_LOL_NWL_DISABLE
    RET_ON_ERR (c_nwl_open (LST_CAB_NWL_ID, NULL, NULL, & t_g_wzd.h_cab_nwl));
    RET_ON_ERR (c_lol_open (LST_CAB_LOL_ID, NULL, NULL, & t_g_wzd.h_cab_lol));
#endif

#ifdef APP_DVBS_SUPPORT
    /* create the SVL/TSL/NWL/LOL of the Satellite */
    RET_ON_ERR (c_satl_open(LST_SAT_SATL_ID,NULL, NULL, & t_g_wzd.h_satl)) ;
    RET_ON_ERR (c_svl_open (LST_SAT_SVL_ID, NULL, NULL, & t_g_wzd.h_sat_svl));
    RET_ON_ERR (c_tsl_open (LST_SAT_TSL_ID, NULL, NULL, & t_g_wzd.h_sat_tsl));
    RET_ON_ERR (c_nwl_open (LST_SAT_NWL_ID, NULL, NULL, & t_g_wzd.h_sat_nwl));
    RET_ON_ERR (c_lol_open (LST_SAT_LOL_ID, NULL, NULL, & t_g_wzd.h_sat_lol));
#endif

    /* customized init fct */
    RET_ON_ERR (wzd_custom_init ());
#endif

    /* set the default svl builder type */
    t_g_wzd.ui2_scanning_type = WZD_SB_SCANNING_AIR;

    /* reset variables */
    t_g_wzd.b_scanning   = FALSE;

    /* turn on paused flag */
    t_g_wzd.b_pause = TRUE;

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_turn_on_off_analog_audio_by_mute
 *
 * Description:
		 *  Turn on/off the analog audio
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
INT32 wzd_turn_on_off_analog_audio_by_mute(BOOL   b_on)
{
    SM_COMMAND_T            at_scc_cmds [5];
    SCC_AUD_VOLUME_INFO_T   t_volume_info_left;
    SCC_AUD_VOLUME_INFO_T   t_volume_info_right;

    c_memset(at_scc_cmds, 0, sizeof(at_scc_cmds));

    /* Mute/Unmute line_out audio */
    c_memset(&t_volume_info_left, 0, sizeof(SCC_AUD_VOLUME_INFO_T));
    c_memset(&t_volume_info_right, 0, sizeof(SCC_AUD_VOLUME_INFO_T));
    t_volume_info_left.e_out_port   = SCC_AUD_OUT_PORT_2_CH_BY_PASS;
    t_volume_info_left.e_ch         = SCC_AUD_CHANNEL_FRONT_LEFT;
    t_volume_info_left.ui1_volumn   = (UINT8)(b_on ? 100 : 0);
    t_volume_info_right.e_out_port  = SCC_AUD_OUT_PORT_2_CH_BY_PASS;
    t_volume_info_right.e_ch        = SCC_AUD_CHANNEL_FRONT_RIGHT;
    t_volume_info_right.ui1_volumn  = (UINT8)(b_on ? 100 : 0);
    at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
    at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_AUDIO;
    at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
    at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
    at_scc_cmds [2].e_code       = SCC_CMD_CODE_AUDIO_VOLUME;
    at_scc_cmds [2].u.pv_data    = (VOID*)&t_volume_info_left;
    at_scc_cmds [3].e_code       = SCC_CMD_CODE_AUDIO_VOLUME;
    at_scc_cmds [3].u.pv_data    = (VOID*)&t_volume_info_right;
    at_scc_cmds [4].e_code       = SM_CMD_CODE_END;
    at_scc_cmds [4].u.ui4_data   = 0;
    c_scc_comp_grp_set(at_scc_cmds);

    return APP_CFGR_OK;
}

#ifdef APP_C4TV_SUPPORT
#define WZD_LAUNCH_APP_MAX_RETRY_NUM 60

static INT32 _wzd_rest_launch_static_app(VOID)
{
    INT32     i4_ret = 0;
    UINT16    ui2_retry = WZD_LAUNCH_APP_MAX_RETRY_NUM;

    ui1_launch_oobe_start_status = 0;

    do
    {
        i4_ret = a_rest_launch_static_app();

        if(RESTR_TOKEN_NOT_READY == i4_ret)
        {
            if(0 < ui2_retry)
            {
                DBG_ERROR(("[WZD_C4TV] a_rest_launch_static_app ERR (session token is not ready!)\r\n"));
                DBG_ERROR(("[WZD_C4TV] Wait for 1 sec & retry! Trial #: %d\r\n", (WZD_LAUNCH_APP_MAX_RETRY_NUM - ui2_retry)));
                c_thread_delay(1000);
                ui2_retry--;
            }
            else
            {
                DBG_ERROR(("[WZD_C4TV] a_rest_launch_static_app ERR (session token is not ready!)\r\n"));
                DBG_ERROR(("[WZD_C4TV] Give up! Trial #: %d\r\n", (WZD_LAUNCH_APP_MAX_RETRY_NUM - ui2_retry)));
                return -1;
            }
        }
        else if (0 > i4_ret)
        {
            DBG_ERROR(("[WZD_C4TV] a_rest_launch_static_app ERR: %d\r\n", i4_ret));
            return -1;
        }
        else
        {
            break;
        }
    } while (TRUE);

    return 0;
}
#if 1
static VOID _wzd_cast_launch_fail_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    DBG_LOG_PRINT(("[WZD_C4TV] _wzd_cast_launch_fail_nfy\r\n"));
    ui1_launch_oobe_sucess = FALSE;
}

static VOID _wzd_relaunch_OOBE_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
        DBG_LOG_PRINT(("[WZD_C4TV] after exit,relaunch oobe app\r\n"));
        a_amb_enable_system_key(TRUE);
        a_rest_app_launch_cast_to_conjure_apps();
}

static VOID _wzd_oobe_expired_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    DIR *p_dir;
    struct dirent *p_dirent;
    FILE *p_file;

    INT32 i4_buf_size = 10240;
    char buffer[i4_buf_size];
    char cmd_line_buf[i4_buf_size / 5];
    char cmd_buf[128];

    memset(buffer, 0, i4_buf_size);
    memset(cmd_line_buf, 0, i4_buf_size / 5);
    memset(cmd_buf, 0, 128);

    /* scan "/proc" folder and get all "cast_shell" cmdline */
    p_dir = opendir("/proc");
    while((p_dirent = readdir(p_dir)) != NULL) {
        sprintf(cmd_buf, "/proc/%s/cmdline", p_dirent->d_name);
        if(access(cmd_buf, R_OK) == 0) {
            p_file = fopen(cmd_buf, "r");
            if(p_file != NULL) {
                fgets(cmd_line_buf, 2048, p_file);
                if(strstr(cmd_line_buf, "cast_shell") != NULL) {
                    strncat(buffer, cmd_line_buf, (i4_buf_size-strlen(buffer))-1);
                }
                fclose(p_file);
            }
        }
    }
    closedir(p_dir);
    RET_ON_ERR (_wzd_get_status ());
    /* Check if t_g_wzd.state is WZD_STATE_RESUME_C4TV. */
    if (t_g_wzd.b_g_is_oobe_recovery == FALSE || t_g_wzd.ui1_state != WZD_STATE_RESUME_C4TV || t_g_wzd.ui1_page_idx == WZD_PAGE_INDEX_C4TV_STORE_DEMO)
    {
        DBG_LOG_PRINT(("[WZD_C4TV] stop oobe timer......\r\n"));
        c_timer_stop(t_g_wzd.h_timer_oobe);
        return;
    }
    
#ifdef APP_RETAIL_MODE_SUPPORT
	NAV_RETAIL_MODE_STATUS_T e_retail_status = NAV_RETAIL_MODE_INITIAL;
	a_nav_retail_mode_get_status(&e_retail_status);
	if (NAV_RETAIL_MODE_RUNNING == e_retail_status)
	{
	    DBG_LOG_PRINT(("[WZD_C4TV] demo is running,stop oobe timer......\r\n"));
		c_timer_stop(t_g_wzd.h_timer_oobe);
		return TRUE;
	}
#endif

    /* No cast_shell case */
    if (strstr(buffer, "cast_shell") == NULL) {
        DBG_WARN(("[WZD_C4TV] no cast_shell is running, do nothing.\n"));
    }else if(ui1_launch_oobe_sucess == FALSE)
   {
        DBG_LOG_PRINT(("[WZD_C4TV] cast shell launch oobe fail\r\n"));
        ui1_launch_count = 0;
        ui1_launch_count_threshold = 5;
        ui1_launch_oobe_sucess = TRUE;
        a_c4tv_apron_stop_current_app();
        a_c4tv_apron_force_revoke_exit_cast(_wzd_relaunch_OOBE_nfy);
   }
    /* OOBE is running case */
    else if (strstr(buffer, "--last-launched-app=BBA3248B") != NULL) {
        DBG_WARN(("[WZD_C4TV] oobe is running normally\n"));
    }
    /* EurekaErrorScreen is running case */
    else if (strstr(buffer, "--last-launched-app=EurekaErrorScreen") != NULL) {
        if (strstr(buffer, "--previous-app=BBA3248B") != NULL) { /* oobe crash */
            DBG_ERROR(("[WZD_C4TV] we're stuck in hang on a second, relaunching oobe app\r\n"));
            a_c4tv_apron_stop_current_app();
            
            a_c4tv_apron_force_revoke_exit_cast(_wzd_relaunch_OOBE_nfy);
            _wzd_rest_launch_static_app(); // just for notify and generate index.html
        } else { /* non-oobe crash */
            DBG_WARN(("[WZD_C4TV] cast_shell crashed but previous app isn't oobe, do nothing\r\n"));
        }
    }
    /* Backdrop is running case */
    else if (strstr(buffer, "--last-launched-app=E8C28D3C") != NULL) {
        DBG_ERROR(("[WZD_C4TV] expect oobe but backdrop is running\r\n"));
        ui1_launch_count_threshold = 1;
        ui1_launch_count ++;
        if (ui1_launch_count > ui1_launch_count_threshold)
        {
            DBG_ERROR(("[WZD_C4TV] relaunching oobe app\r\n"));
            ui1_launch_count = 0;
            ui1_launch_count_threshold = 5;
            ui1_launch_oobe_start_status = 0;
            a_c4tv_apron_stop_current_app();
            a_c4tv_apron_force_revoke_exit_cast(_wzd_relaunch_OOBE_nfy);

        }
    }
    /* Other case */
    else {
        DBG_LOG_PRINT(("[WZD_C4TV] something_wrong with cast_shell but oobe isn't launched\r\n"));
        DBG_LOG_PRINT(("[WZD_C4TV] state should be %d(WZD_STATE_RESUME_C4TV=%d), page should be %d(WZD_PAGE_INDEX_C4TV_START_OOBE=%d,WZD_PAGE_INDEX_C4TV_DEVICE_PAIR=%d)\r\n",
                       t_g_wzd.ui1_state, WZD_STATE_RESUME_C4TV, t_g_wzd.ui1_page_idx, WZD_PAGE_INDEX_C4TV_START_OOBE, WZD_PAGE_INDEX_C4TV_DEVICE_PAIR));

        if (t_g_wzd.ui1_page_idx == WZD_PAGE_INDEX_C4TV_START_OOBE ||
            t_g_wzd.ui1_page_idx == WZD_PAGE_INDEX_C4TV_DEVICE_PAIR) {
            DBG_ERROR(("[WZD_C4TV] shall restart cast_shell\r\n"));
            ui1_launch_count ++;
            if (ui1_launch_count > ui1_launch_count_threshold) {
                DBG_LOG_PRINT(("[WZD_C4TV_WO] relaunching oobe app\r\n"));
                ui1_launch_count = 0;
                ui1_launch_count_threshold = 5;
                a_c4tv_apron_stop_current_app();
                a_c4tv_apron_force_revoke_exit_cast(_wzd_relaunch_OOBE_nfy);
            }
        }

    }
#if 0 /* Disabled due to OOBE's behavior changing. */
    /* Check if OOBE start page is ready */
    if( (ui1_launch_oobe_start_status & WZD_STATE_OOBE_STARTED) != WZD_STATE_OOBE_STARTED ) {
        DBG_LOG_PRINT(("[WZD_C4TV] %s() %d: ui1_launch_oobe_start_status = %d\n\r", __FUNCTION__, __LINE__, ui1_launch_oobe_start_status));
        if((ui1_launch_oobe_start_status & ~WZD_STATE_OOBE_STARTED) >= (30 * 1000 / WZD_OOBE_INTERVAL)) {
            DBG_ERROR(("[WZD_C4TV] we're stuck in OOBE starting page about 30s, relaunching\r\n"));
            ui1_launch_count = 0;
            ui1_launch_count_threshold = 2;
            ui1_launch_oobe_start_status = 0;
            a_c4tv_apron_stop_current_app();
            a_rest_launch_static_app(); // just for notify and generate index.html
            a_c4tv_apron_launch_app(APP_ID);
        } else {
            ui1_launch_oobe_start_status ++;
        }
    }
#endif
}
#endif

static INT32 _wzd_rest_launch_conjure_app(VOID)
{
    INT32     i4_ret = 0;
    UINT16    ui2_retry = WZD_LAUNCH_APP_MAX_RETRY_NUM;

    ui1_launch_oobe_start_status = 0;

    do
    {
        i4_ret = a_rest_app_launch_cast_to_conjure_apps();

        if(RESTR_TOKEN_NOT_READY == i4_ret)
        {
            if(0 < ui2_retry)
            {
                DBG_ERROR(("[WZD_C4TV] a_rest_app_launch_cast_to_conjure_apps ERR (session token is not ready!)\r\n"));
                DBG_ERROR(("[WZD_C4TV] Wait for 1 sec & retry! Trial #: %d\r\n", (WZD_LAUNCH_APP_MAX_RETRY_NUM - ui2_retry)));
                c_thread_delay(1000);
                ui2_retry--;
            }
            else
            {
                DBG_ERROR(("[WZD_C4TV] a_rest_app_launch_cast_to_conjure_apps ERR (session token is not ready!)\r\n"));
                DBG_ERROR(("[WZD_C4TV] Give up! Trial #: %d\r\n", (WZD_LAUNCH_APP_MAX_RETRY_NUM - ui2_retry)));
                return -1;
            }
        }
        else if (0 > i4_ret)
        {
            DBG_ERROR(("[WZD_C4TV] a_rest_app_launch_cast_to_conjure_apps ERR: %d\r\n", i4_ret));
            return -1;
        }
        else
        {
            break;
        }
    } while (TRUE);

    return 0;
}

static VOID _wzd_start_suspend_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    KK_LOG(KK_LOG_LVL_KEY, "[WZD_C4TV]", "launch oobe app.\n");
    a_amb_enable_system_key(TRUE);
    _wzd_rest_launch_conjure_app();
}

static VOID _wzd_start_revoke_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    KK_LOG(KK_LOG_LVL_API, "[WZD_C4TV]", "Enter.\n");
    a_c4tv_apron_suspend_cast(_wzd_start_suspend_nfy, C4TV_APRON_USER_SUSPEND_REASON_LOCALAPP);
}

static VOID _wzd_start_c4tv (VOID)
{
    KK_LOG(KK_LOG_LVL_API, "[WZD_C4TV]", "Enter.\n");

    /* because of c4tv_apron doesn't create test_c4tv_apron_first_setup_ok after OOBE,
       so DTV00732206, DTV00762013, DTV00761306 */
    if ((access((const char*)"/data/test_c4tv_apron_first_setup_ok", F_OK)) != 0 )
    {
        INT32  i4_fd = -1;
        i4_fd = open("/data/test_c4tv_apron_first_setup_ok", O_CREAT | O_RDWR, 0777);
        DBG_LOG_PRINT(("create /data/test_c4tv_apron_first_setup_ok %s\r\n", (i4_fd != -1) ? "successful" : "fail"));
        close(i4_fd);
    }

    /* Always suspend cast when in OOBE */
    a_c4tv_apron_force_revoke_exit_cast(_wzd_start_revoke_nfy);
}

static VOID _c4tv_apron_nfy_fct(C4TV_APRON_CAST_STATE    e_cast_state,
                                VOID*                    pv_param1,
                                VOID*                    pv_param2,
                                VOID*                    pv_param3)
{
    KK_LOG(KK_LOG_LVL_API, "[WZD_C4TV]", "Enter.\n");

    UINT32 ui4_control_connect = 0;
    ui4_control_connect = (UINT32)pv_param1;

    if (1 == ui4_control_connect)
    {
        _wzd_start_c4tv();

        a_c4tv_apron_unregister_nfy_cb(_c4tv_apron_nfy_fct);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_app_resume_c4tv_fct
 *
 * Description: This function is called in the context of the Wizard
 *              application when the application is resumed.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_app_resume_c4tv_fct ()
{
    if (t_g_wzd.ui1_state != WZD_STATE_RESUME_C4TV)
    {
        KK_LOG(KK_LOG_LVL_ERR, "[WZD_C4TV]", "t_g_wzd.ui1_state != WZD_STATE_RESUME_C4TV !!!\n");
        return 0;
    }

    KK_LOG(KK_LOG_LVL_API, "[WZD_C4TV]", "oobe [state= %d] [page= %d].\n\r",
                    (INT32)t_g_wzd.ui1_state, (INT32)t_g_wzd.ui1_page_idx);

    /* disable the system keys except the POWER key */
    a_amb_enable_system_key(FALSE);

    _wzd_start_suspend_nfy(NULL, NULL, NULL);
    return 0;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _wzd_app_resume_fct
 *
 * Description: This function is called in the context of the Wizard
 *              application when the application is resumed.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_app_resume_fct (HANDLE_T    h_app)
{
#ifdef APP_WZD_SUPPORT

#ifdef APP_C4TV_SUPPORT

    /* reset flag */
    b_g_is_need_power_off_dlg_show = FALSE;

    t_g_wzd.b_g_is_panel_key_long_press = FALSE;
    t_g_wzd.b_cfg_dirty = FALSE;
    t_g_wzd.b_svl_dirty = FALSE;
    t_g_wzd.b_scanning  = FALSE;
    t_g_wzd.b_next_key  = TRUE;

    /* Get the wizard status */
    RET_ON_ERR (_wzd_get_status ());

    /* update gui language */
    ISO_639_LANG_T      s639_lang;
    RET_ON_ERR (a_cfg_get_gui_lang (s639_lang));
    RET_ON_ERR (wzd_set_gui_lang (s639_lang));

    if (t_g_wzd.ui1_state != WZD_STATE_RESUME_C4TV)
    {
        t_g_wzd.ui1_state = WZD_STATE_RESUME_C4TV;
        t_g_wzd.ui1_page_idx = WZD_PAGE_INDEX_C4TV_DEVICE_PAIR;

        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx));
        rest_event_notify("oobe/currentstate", 0, "DEVICE_PAIR");
    }

    if (t_g_wzd.ui1_page_idx != WZD_PAGE_INDEX_C4TV_LINK_START)
    {
    	a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY,0);
	}

    _wzd_app_resume_c4tv_fct();

    /* turn off paused flag */
    t_g_wzd.b_pause = FALSE;
#else
    ISO_639_LANG_T      s639_lang;
    WZD_PAGE_INFO_T*    pt_page = NULL;
    UINT8               ui1_icl_scart_excl_ap_status = ICL_SCART_EXCL_AP_STATUS_RESUME;
    UINT8               ui1_icl_initial_setup_status = ICL_INITIAL_SETUP_STATUS_RUNNING;
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
    CECM_ARC_CTRL_T             t_arc_ctrl;
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

    DBG_INFO (("<WZD> resume Wizard (handle = %d)\n\r", h_app));

    /* reset flag */
    b_g_is_need_power_off_dlg_show = FALSE;

    /* reset the variables */
    {
        t_g_wzd.b_g_is_panel_key_long_press = FALSE;

        t_g_wzd.b_cfg_dirty = FALSE;
        t_g_wzd.b_svl_dirty = FALSE;
        t_g_wzd.b_scanning  = FALSE;
        t_g_wzd.b_next_key  = TRUE;

        /* get first entry */
        pt_page = DLIST_HEAD (& t_g_wzd.t_page_lst);
        while (pt_page != NULL)     /* traverse page list */
        {
            pt_page->ui2_sel_idx = 0;
            pt_page = DLIST_NEXT (pt_page, t_page_link); /* get next entry */
        }
    }

    /* Get the wizard status */
    RET_ON_ERR (_wzd_get_status ());

    /* update gui language */
    RET_ON_ERR (a_cfg_get_gui_lang (s639_lang));
    RET_ON_ERR (wzd_set_gui_lang (s639_lang));

    /* before wzd UI show, get focus back from 3rd AP */
    a_tv_net_OSD_appear();

    /* Get SPDIF status*/
    a_cfg_get_spdif_type(&e_g_spdif_value);

    /* Set the SPDIF to config immediately */
    a_cfg_set_spdif_type(SCC_AUD_SPDIF_FMT_PCM_16);
    a_cfg_update_spdif_type();

    /* get mute status */
    b_g_is_mute = a_tv_get_mute();

    /* set vol mute */
    a_tv_set_mute (TRUE);

    // If current state is resume C4TV, then launch html5 instead of show page.
    DBG_LOG_PRINT(("[WZD] %s, %d\n\r", __FUNCTION__, __LINE__));

    /* refresh the page according to the view type */
    b_g_is_need_animation = FALSE;
    RET_ON_ERR (_wzd_show_update (t_g_wzd.ui1_page_idx, FALSE));

    /* enable control keys of setting list */
    RET_ON_ERR (wzd_view_seti_lst_enable_control_key (TRUE));

    /* customized resume fct */
    RET_ON_ERR (wzd_custom_resume ());


#ifdef APP_WZD_AUTO_PAUSE
    /* start auto-pause timer */
    RET_ON_ERR (c_timer_start (t_g_wzd.h_timer_pause,
                               TIMER_PAUSE_DELAY,
                               X_TIMER_FLAG_ONCE,
                               _wzd_nfy_timer,
                               NULL));
#endif


    // If current state is resume C4TV, then launch html5 instead of show fame.
    DBG_LOG_PRINT(("[WZD] %s, %d\n\r", __FUNCTION__, __LINE__));

    /* show main frame */
    RET_ON_ERR (wzd_view_main_frm_show (TRUE));

    if(t_g_wzd.ui1_page_idx != WZD_PAGE_TV_REMOTE_DEVICE_SETUP)
    {
        if(a_wzd_is_resume_from_menu_setup() == TRUE)
        {
            // SPDIF off temporarily if resume from MENU.
            c_scc_aud_set_spdif_fmt(h_g_acfg_scc_main_aud, SCC_AUD_SPDIF_FMT_OFF);

            // analog audio off temporarily if resume from MENU.
            wzd_turn_on_off_analog_audio_by_mute(0);

            /*disable ARC*/
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
            c_memset(&t_arc_ctrl, 0, sizeof(CECM_ARC_CTRL_T));
            t_arc_ctrl.b_enable = FALSE;
            c_cecm_arc_ctrl(nav_cec_get_mw_handle(), &t_arc_ctrl);
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT
        }
    }

    t_g_wzd.b_g_is_vol_key_enable = FALSE;

    /* temporarily enable the TV source */
    RET_ON_ERR (_wzd_enable_tv_src (TRUE));

    /* disable the system keys except the POWER key */
    a_amb_enable_system_key(FALSE);

    /* turn off paused flag */
    t_g_wzd.b_pause = FALSE;

    /* set icl status */
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_SCART_EXCL_AP, ICL_RECID_SCART_EXCL_AP_STATUS),
              (VOID*) &ui1_icl_scart_excl_ap_status,
              ICL_RECID_SCART_EXCL_AP_STATUS_SIZE);
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_INITIAL_SETUP, ICL_RECID_INITIAL_SETUP_STATUS),
              (VOID*) &ui1_icl_initial_setup_status,
              ICL_RECID_INITIAL_SETUP_STATUS_SIZE);

    /* handle keyroute */
    a_tv_net_disable_keyroute(TRUE);

    /* enter WZD from RetailMode, need enable dtv_svc key handle */
    a_tv_net_send_cmd(":dtv_app_mtk,am,:enablekey=dtv_app_mtk\n");

#endif

    return  0;
#else
    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
    return WZDR_FAIL;
#endif
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_app_pause_fct
 *
 * Description: This function is called in the context of the Wizard
 *              application when the application is paused.
 *
 * Inputs:  h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_app_pause_fct (HANDLE_T    h_app)
{
#ifdef APP_C4TV_SUPPORT
    DBG_LOG_PRINT(("[WZD] %s, %d\n\r", __FUNCTION__, __LINE__));

    /* turn on paused flag */
    t_g_wzd.b_pause = TRUE;
    
    t_g_wzd.b_g_is_oobe_recovery = FALSE;
    ui1_launch_count = 0;
    ui1_launch_count_threshold = 5;
    ui1_launch_oobe_start_status = 0;

#if 0
#if defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
    if (a_c4tv_apron_check_cast_state())
    {
        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);
    }
#endif
#endif

    /* explicitly exit wizard for saving memory */
#ifdef WZD_PAUSE_WITH_FREE_RESOURCE
    RET_ON_ERR (a_amb_exit_app (WZD_NAME));
#endif

#else
    UINT8               ui1_icl_status = ICL_SCART_EXCL_AP_STATUS_PAUSE;
    UINT8               ui1_icl_initial_setup_status = ICL_INITIAL_SETUP_STATUS_OFF;
    ACFG_COUNTRY_CODE_T t_country = ACFG_COUNTRY_CODE_LAST_ENTRY;
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
    CECM_ARC_CTRL_T             t_arc_ctrl;
#endif//APP_CEC2_SUPPORT
#endif//APP_CEC_SUPPORT

    DBG_INFO (("<WZD> pause Wizard (handle = %d)\n\r", h_app));

	/* Handle keyroute */
	a_tv_net_disable_keyroute(FALSE);

    /* turn on paused flag */
    t_g_wzd.b_pause = TRUE;

    /* enable the system keys */
    a_amb_enable_system_key(TRUE);

    /* Rollback the settings of the TV source */
    RET_ON_ERR (_wzd_enable_tv_src (FALSE));

    if (wzd_is_scan_active ())
    {
    	if(t_g_wzd.b_g_is_rf_scan)
		{
			wzd_page_tv_setup_set_scan_status (WZD_SB_STATUS_CANCEL);
		}
		else
		{
	        wzd_util_set_scan_status (WZD_SB_STATUS_CANCEL);
		}
        RET_ON_ERR (wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0));
    }

    /* hide main frame */
    RET_ON_ERR (wzd_view_main_frm_show (FALSE));

    /* reset default background img */
    RET_ON_ERR (wzd_view_set_main_frm_bg(h_g_wzd_img_background, FALSE));

    /* update country code in /tmp/cfg_country */
	a_cfg_custom_get_country_code(&t_country);
	a_tv_custom_set_country((UINT16)t_country);

    /* if be changed mute state, do nothing */
    a_tv_set_mute (b_g_is_mute);

	/* Set the SPDIF to config immediately */
    a_cfg_set_spdif_type(e_g_spdif_value);
    a_cfg_update_spdif_type();

    // analog audio on if wzd pause.
    wzd_turn_on_off_analog_audio_by_mute(1);

	/*enable ARC*/
#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
    c_memset(&t_arc_ctrl, 0, sizeof(CECM_ARC_CTRL_T));
    t_arc_ctrl.b_enable = TRUE;
    c_cecm_arc_ctrl(nav_cec_get_mw_handle(), &t_arc_ctrl);
#endif
#endif

    /* stop CLI commands */
    wzd_cli_stop ();

    /* clean the page */
    RET_ON_ERR (_wzd_show_clean ());

    /* disable control keys of setting list */
    RET_ON_ERR (wzd_view_seti_lst_enable_control_key (FALSE));

#ifdef APP_WZD_AUTO_PAUSE
    /* stop auto-pause timer */
    RET_ON_ERR (c_timer_stop (t_g_wzd.h_timer_pause));
#endif
    /* customized pause fct */
    RET_ON_ERR (wzd_custom_pause ());

    /* Set the wizard status */
    RET_ON_ERR (_wzd_set_status ());

    /* async store the config and svls */
    RET_ON_ERR (wzd_app_send_msg (WZD_MSG_PAUSE_ASYNC_STORE, NULL, 0));

    /* explicitly exit wizard for saving memory */
#ifdef WZD_PAUSE_WITH_FREE_RESOURCE
    RET_ON_ERR (a_amb_exit_app (WZD_NAME));
#endif

	/* Resume Video size */
    RET_ON_ERR (wzd_set_stream_play_region( FALSE, TRUE ));

    /* Set icl status */
    a_icl_set(ICL_MAKE_ID(ICL_GRPID_SCART_EXCL_AP, ICL_RECID_SCART_EXCL_AP_STATUS),
              (VOID*) &ui1_icl_status,
              ICL_RECID_SCART_EXCL_AP_STATUS_SIZE);

    a_icl_set(ICL_MAKE_ID(ICL_GRPID_INITIAL_SETUP, ICL_RECID_INITIAL_SETUP_STATUS),
              (VOID*) &ui1_icl_initial_setup_status,
              ICL_RECID_INITIAL_SETUP_STATUS_SIZE);

    /* info AM when wzd UI hide */
    a_tv_net_OSD_disapper();
#endif

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_app_exit_fct
 *
 * Description: This function is called in the context of the Wizard
 *              application when the application quits. This API should be
 *              responsible for saving data, clean-up, etc.
 *
 * Inputs:  h_app               Contains the application handle.
 *          e_exit_mode         Contains the exit mode.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_app_exit_fct (HANDLE_T           h_app,
                                APP_EXIT_MODE_T    e_exit_mode)
{
#ifndef APP_C4TV_SUPPORT
    WZD_PAGE_INFO_T*    pt_page_info = NULL ;

    DBG_LOG_PRINT (("<WZD> exit Wizard (handle = %d)\n\r", h_app));

    /* customized exit fct */
    RET_ON_ERR (wzd_custom_exit ());
    
    t_g_wzd.b_g_is_oobe_recovery = FALSE;
    ui1_launch_count = 0;
    ui1_launch_count_threshold = 5;
    ui1_launch_oobe_start_status = 0;

    /* destory all page items */
    DLIST_FOR_EACH(pt_page_info, & t_g_wzd.t_page_lst, t_page_link)
    {
        if (WZD_PAGE_TYPE_CUST_PAGE == pt_page_info->pt_page_data->t_page_type)
        {
            SHOW_ON_ERR (pt_page_info->pt_page_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory ()) ;
        }
    }

	/* destroy widget handles */
    RET_ON_ERR (wzd_view_destroy ());

#ifdef APP_WZD_AUTO_PAUSE
    /* free timer handles */
    if (t_g_wzd.h_timer_pause != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete (t_g_wzd.h_timer_pause));
    }
#endif
    if (t_g_wzd.h_timer_scan != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete (t_g_wzd.h_timer_scan));
    }
	if (t_g_wzd.h_timer_dlg != NULL_HANDLE)
    {
        RET_ON_ERR (c_timer_delete (t_g_wzd.h_timer_dlg));
    }
#endif

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_app_process_msg_fct
 *
 * Description: This function is called in the context of the Wizard
 *              application when a message is processed.
 *
 * Inputs:  h_app               Contains the application handle.
 *          ui4_type            Contains the type of the data contained in
 *                              pv_msg, or simple a request type. Values are
 *                              defined by the application.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *          b_paused            Sepcifies whether the application is currently
 *                              paused.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_app_process_msg_fct (HANDLE_T       h_app,
                                       UINT32         ui4_type,
                                       const VOID*    pv_msg,
                                       SIZE_T         z_msg_len,
                                       BOOL           b_paused)
{
    INT32            i4_rc = WZDR_OK;

    switch (ui4_type)
    {
        case WZD_MSG_CLI_CHANGE_PAGE:
        {
            WZD_PAGE_NAVI_T e_page_navi = *(WZD_PAGE_NAVI_T*)pv_msg;
            wzd_page_goto( e_page_navi );
        }
            break;

        case WZD_MSG_CLI_CREATE_DLG:
            _wzd_create_dialog();
            break;

        case WZD_MSG_CLI_DESTROY_DLG:
            _wzd_destroy_dialog();
            break;

        case WZD_MSG_WGL_NFY: /* widget notifications */
        {
            WZD_WIDGET_MSG_T*    pt_wgl_msg;

            pt_wgl_msg = (WZD_WIDGET_MSG_T*) pv_msg;

            /* ignore the message if page changed */
            if (t_g_wzd.ui1_page_idx == pt_wgl_msg->ui1_cur_pg_idx)
            {
	            /* dispatch message to Widget Library */
	            i4_rc = c_wgl_dispatch_event (pt_wgl_msg->ui4_msg,
	                                          pt_wgl_msg->pv_param1,
	                                          pt_wgl_msg->pv_param2);

	            if ((i4_rc != WGLR_OK) && (i4_rc != WGLR_EVENT_IGNORED))
	            {
	                DBG_ERROR (("<WZD> ERR: dispatch event to wgl failed = %d\n\r", i4_rc));
	            }
            }
#ifdef APP_WZD_AUTO_PAUSE
            /* restart auto-pause timer */
            RET_ON_ERR (c_timer_start (t_g_wzd.h_timer_pause,
                                       TIMER_PAUSE_DELAY,
                                       X_TIMER_FLAG_ONCE,
                                       _wzd_nfy_timer,
                                       NULL));
#endif
        }
        break;

        case WZD_MSG_BTN_SELECT: /* select button is pressed */
        {
            if (t_g_wzd.b_btn_select)
            {
                RET_ON_ERR (_wzd_btn_select ());
            }
        }
        break;

        case WZD_MSG_BTN_EXIT: /* exit button is pressed */
        {
            if (t_g_wzd.ui1_page_idx == 0)   /* exit when it's first page. */
            {
#ifdef APP_2K12_RETAIL_DEMO_MODE
                wzd_page_choose_mode_stop_timer();
#endif
                wzd_page_goto( WZD_PAGE_NAVI_LAST_VALID_ITEM );
            }
#ifdef APP_2K12_RETAIL_DEMO_MODE
            if (t_g_wzd.ui1_page_idx == 1) /* exit when it's getting start page*/
            {
                 wzd_page_goto( WZD_PAGE_NAVI_LAST_VALID_ITEM );
            }
#endif
            RET_ON_ERR (_wzd_btn_exit());
        }
        break;

		case WZD_MSG_BTN_RETURN: /* return button is pressed */
        {
        	RET_ON_ERR (_wzd_btn_return ());
        }
        break;

        case WZD_MSG_BTN_CURSOR_UP: /* cursor_up button is pressed */
        {
            RET_ON_ERR (_wzd_btn_cursor_up ());
        }
        break;

        case WZD_MSG_BTN_CURSOR_DOWN: /* cursor_down button is pressed */
        {
            RET_ON_ERR (_wzd_btn_cursor_down ());
        }
        break;

        case WZD_MSG_BTN_CURSOR_LEFT: /* cursor_left button is pressed */
        {
            t_g_wzd.b_next_key = FALSE;
            i4_rc = _wzd_btn_cursor_left ();
            t_g_wzd.b_next_key = TRUE;
        }
        break;

        case WZD_MSG_BTN_CURSOR_RIGHT: /* cursor_right button is pressed */
        {
            t_g_wzd.b_next_key = FALSE;
            i4_rc = _wzd_btn_cursor_right ();
            t_g_wzd.b_next_key = TRUE;
        }
        break;

        case WZD_MSG_SCAN_TIMER_EXPIRED: /* animation scan timer expired. update the scanning text. */
        {
            if (wzd_is_scan_active ())
            {
                /*When scanning, should not update description text*/
                //SHOW_ON_ERR (_wzd_scan_desc_txt_update (MLM_WZD_KEY_SCAN_PROGRESS, TRUE, TRUE));
            }
        }
        break;

        case WZD_MSG_PAUSE_ASYNC_STORE: /* store the config and svl */
        {
            RET_ON_ERR (_wzd_store_svl_and_config ());
        }
        break;

        case WZD_MSG_RMK_CLIENT_KEY: /* remote client key is pressed*/
        {
            WZD_WIDGET_MSG_T*    pt_wgl_msg;

            pt_wgl_msg = (WZD_WIDGET_MSG_T*) pv_msg;
            RET_ON_ERR(a_amb_default_key_handler_ex(pt_wgl_msg->ui4_msg, pt_wgl_msg->pv_param1, NULL));
        }
        break;

        case WZD_MSG_PAUSE_TIMER_EXPIRED: /* timer expired */
        {
            if (wzd_is_scan_active () == FALSE)
            {
                RET_ON_ERR (a_wzd_exit()); /*Exit Wizard*/
            }
        }
        break;

        case WZD_MSG_PAUSE_BY_WZD:        /* setup complete */
        {
            ACFG_RETAIL_MODE_T	t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

            #ifdef APP_RETAIL_MODE_SUPPORT
            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            #endif

            if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
                /* Start Retail Demo Mode Page */
				a_nav_retail_mode_set_resume_from_app(NAV_RETAIL_MODE_RESUME_FROM_WZD);
                a_amb_default_key_handler (WGL_MSG_KEY_DOWN,
                                          (VOID*) (BTN_FUNCTION_1),
                                           NULL);
            }
            else
            {
                RET_ON_ERR (a_wzd_exit()); /*Exit Wizard*/
            }
        }
        break;

        case WZD_MSG_SB_SCAN_START: /* scanning start */
        {
#ifdef APP_WZD_AUTO_PAUSE
            /* stop auto-pause timer */
            RET_ON_ERR (c_timer_stop (t_g_wzd.h_timer_pause));
#endif
            if (_wzd_scan_start () != WZDR_OK)
            {
                RET_ON_ERR (wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0));
            }
        }
        break;

#if defined(APP_DVBC_SUPPORT) || defined(APP_DVBT_SUPPORT) || defined(APP_DVBS_SUPPORT)
        case WZD_MSG_SB_SCAN_START_NEXT: /* scanning start (next) */
        {
            if (wzd_util_scan_start_next () != WZDR_OK)
            {
                RET_ON_ERR (wzd_app_send_msg (WZD_MSG_SB_SCAN_END, NULL, 0));
            }
        }
        break;
#endif

        case WZD_MSG_SB_SCAN_PROGRESS: /* scanning progress */
        {
            if (t_g_wzd.b_been_cancel == FALSE)
            {
                RET_ON_ERR (_wzd_scan_progress ((SB_NFY_MSG_T*) pv_msg));
            }
        }
        break;

        case WZD_MSG_SB_SCAN_END: /* scanning complete, cancel, or abort */
        {
#ifdef APP_WZD_AUTO_PAUSE
            /* start auto-pause timer */
            RET_ON_ERR (c_timer_start (t_g_wzd.h_timer_pause,
                                       TIMER_PAUSE_DELAY,
                                       X_TIMER_FLAG_ONCE,
                                       _wzd_nfy_timer,
                                       NULL));
#endif

            RET_ON_ERR (_wzd_scan_end ());
        }
        break;

#ifdef APP_DVBC_SUPPORT

#if (defined(APP_ANAS_SUPPORT) && !defined(APP_TWN_SUPPORT))
        case WZD_MSG_SB_SCAN_ANAS_NFY:  /* used for sorting the analog channels */
        {
            RET_ON_ERR (wzd_util_scan_anas_putback ((SB_PAL_SECAM_ANAS_NFY_DATA*) pv_msg));
        }
        break;
#endif

#else

#ifdef APP_DVBT_SUPPORT
#if (defined(APP_ANAS_SUPPORT) && !defined(APP_TWN_SUPPORT))
        case WZD_MSG_SB_SCAN_ANAS_NFY:  /* used for sorting the analog channels */
  {
            RET_ON_ERR (wzd_util_scan_anas_putback ((SB_PAL_SECAM_ANAS_NFY_DATA*) pv_msg));
  }
  break;
#endif
#endif

#endif

  case WZD_MSG_WGL_SETI_LST_ELEM_HLT:
        {
            RET_ON_ERR (_wzd_btn_change_focus());
        }
        break;

#ifdef APP_ACI_SUPPORT
        case WZD_MSG_SB_SCAN_ACI_NFY:           /* ACI Notify: used for ACI notification */
        case WZD_MSG_SB_SCAN_ACI_TIMER_EXPIRED:
        case WZD_MSG_ACI_SELECTION:
        {
            /* Send to util first. */
            RET_ON_ERR (wzd_util_msg_handler (ui4_type, pv_msg, z_msg_len));
            break;
        }
#endif

        case WZD_MSG_ASYNC_INVOKE:
        {
            WZD_MSG_ASYNC_INVOKE_T* pt_msg_async =
                (WZD_MSG_ASYNC_INVOKE_T*)pv_msg;
            if(z_msg_len <= 4)
            {
                pt_msg_async->pf_async_func(NULL, 0);
            }
            else
            {
                pt_msg_async->pf_async_func(pt_msg_async->aui1_data,
                                            z_msg_len - 4);
            }

            break;
        }

        case WZD_REQ_CTX_SWITCH_EVENT:
        {
            WZD_EVN_T*    pt_event = (WZD_EVN_T*)pv_msg;
            wzd_context_switch_nfy_fct pf_fct  = (wzd_context_switch_nfy_fct)pt_event->ui4_data1;
            VOID*                      pv_tag  = (VOID*)pt_event->ui4_data2;
            VOID*                      pv_tag2 = (VOID*)pt_event->ui4_data3;
            VOID*                      pv_tag3 = (VOID*)pt_event->ui4_data4;

            if (pf_fct != NULL) {
                pf_fct(pv_tag, pv_tag2, pv_tag3);
            }

            break;
        }

        default: /* unknown messages */
        {
            /* handle AM's broadcast messages */
            switch (ui4_type)
            {
            #ifdef APP_C4TV_SUPPORT
            case AM_BRDCST_MSG_PRE_POWER_OFF:
                DBG_INFO(("[WZD] _wzd_app_process_msg_fct receiving AM_BRDCST_MSG_POWER_OFF.\n"));
                RET_ON_ERR (a_tv_stop(t_g_wzd.h_svctx));
                DBG_INFO(("[WZD] a_tv_stop after receive AM_BRDCST_MSG_POWER_OFF.\n"));
                break;

            case AM_BRDCST_MSG_POWER_OFF :  /* user press the "POWER" to close TV. */
                DBG_INFO(("[WZD] _wzd_app_process_msg_fct receiving AM_BRDCST_MSG_POWER_OFF.\n"));
#ifdef APP_C4TV_SUPPORT
                /* Stop and reset oobe related timer and variables. */
                t_g_wzd.b_g_is_oobe_recovery = FALSE;
                ui1_launch_count = 0;
                ui1_launch_count_threshold = 5;
                ui1_launch_oobe_start_status = 0;
                if(t_g_wzd.ui1_state == WZD_STATE_RESUME_C4TV) {
                    a_wzd_stop_c4tv(NULL);
                    t_g_wzd.ui1_state = WZD_STATE_RESUME_C4TV_END;
                    t_g_wzd.ui1_page_idx = WZD_PAGE_INDEX_C4TV_END;
                }
#endif
                RET_ON_ERR (_wzd_store_svl_and_config ());
                break;
            #endif
            default: /* unknown messages */
                i4_rc = WZDR_UNKNOWN_MSG;
                break;
            }
        }
        break;
    }

    return (i4_rc == 0) ? AEER_OK : AEER_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *		wzd_chg_inp_src_to_hdmi
 * Description	change input source to HDMI
 * Input		-
 * Output		-
 * Returns		-
 *---------------------------------------------------------------------------*/
INT32 wzd_chg_inp_src_to_hdmi(VOID)
{
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    UINT8           ui1_src_index = 0;

    DBG_INFO(("[WZD] change input source to HDMI!\n"));

    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if (i4_ret != APP_CFGR_OK)
        {
            return WZDR_FAIL;
        }

        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_AV) &&
            (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI ||
             t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI))
        {
            ui1_src_index = ui1_index;
            break;
        }
    }

    if (ui1_src_index < ui1_src_num)
    {
        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
    }

    return WZDR_OK;
}

static BOOL  _wzd_app_system_key_cb (UINT32 ui4_evt_code)
{
#ifndef APP_C4TV_SUPPORT
	UINT32	ui4_key_code = IOM_GET_EVT_GRP_ID(ui4_evt_code);
    UINT8	ui1_val = WIFI_REMOTE_PAIR_STATUS_UNKNOWN;

    if (BTN_POWER == ui4_key_code &&
        IOM_GET_EVT_SRC(ui4_evt_code) == KEY_SRC_FRONT_PANEL)
    {
		if (a_cfg_custom_get_wifi_remote_support())
        {
            a_cfg_custom_get_wifi_remote_pair_status(&ui1_val);
        }

        /* for DTV00592979, change source to HDMI and exit WZD. */
		if ((WIFI_REMOTE_PAIR_STATUS_PAIRED != ui1_val) &&
            (!a_wzd_is_resume_from_menu_setup()))
        {
            DBG_INFO(("[WZD]long press power from FRONT PANEL!\n"));

            t_g_wzd.b_g_is_panel_key_long_press = TRUE;

			/*stop scan if wzd is scanning*/
			wzd_app_send_msg (WZD_MSG_BTN_SELECT, NULL, 0);

            wzd_page_goto(WZD_PAGE_NAVI_LAST_VALID_ITEM);
            wzd_chg_inp_src_to_hdmi();

            return FALSE;
        }
        else
        {
            t_g_wzd.b_g_is_panel_key_long_press = FALSE;
        }
    }

#ifdef APP_WZD_EXIT_ON_MENU_KEY
    if(ui4_key_code == BTN_MENU)
    {
        a_wzd_exit();   /*Exit Wizard*/
        return FALSE;
    }
#endif

	/* show power off warning dialog */
	if (BTN_POWER == ui4_key_code
		&& b_g_is_need_power_off_dlg_show)
	{
		wzd_request_context_switch(_wzd_show_power_off_dlg_hdlr,
		                           NULL,
		                           NULL,
		                           NULL);
		return FALSE;
	}
#endif

    return TRUE;
}

#ifdef APP_C4TV_SUPPORT
static void _wzd_set_page_process(VOID)
{
    UINT16                  ui2_status  = APP_CFG_WZD_STATUS_INIT;
    UINT16                  ui2_real_status = APP_CFG_WZD_STATUS_INIT;
    UINT8                   ui1_page_index = 0;
    UINT8                   ui1_bootup_assist = ACFG_BOOTUP_ASSISTANT_NONE;

    if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
    {
        a_cfg_custom_get_bootup_assistant_flag(&ui1_bootup_assist);

        ui2_real_status = WZD_UTIL_GET_STATUS_STATE( ui2_status );
        ui1_page_index  = WZD_UTIL_GET_STATUS_IDX  ( ui2_status );
        DBG_LOG_PRINT(( "[WZD] %s() %d: ui2_status= %d, ui2_real_status= %d, ui1_page_index=%d, ui1_bootup_assist=%d\n",
                        __FUNCTION__, __LINE__,
                        ui2_status, ui2_real_status, ui1_page_index, ui1_bootup_assist));

        UINT8   ui1_idx_ir_modee = 0;
        a_cfg_cust_get_oobe_ir_mode(&ui1_idx_ir_modee);
        DBG_LOG_PRINT(("[WZD] %s() %d: Cast TV, IR Mode status is %d.\n\r", __FUNCTION__, __LINE__, ui1_idx_ir_modee));

        if (ui2_real_status == APP_CFG_WZD_STATUS_INIT ||
            ui2_real_status  & WZD_STATE_START_SETUP)
        {
            DBG_LOG_PRINT(("[WZD] %s() %d: Cast TV, set to be WZD_PAGE_INDEX_C4TV_START_OOBE\n\r", __FUNCTION__, __LINE__));
            a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));
            rest_event_notify("oobe/currentstate", 0, "START_OOBE");
        }
        else if(ui2_real_status == (UINT16)WZD_STATE_RESUME_C4TV)
        {
            UINT8 ui1_sys_upgrade_status = 0;
            a_cfg_cust_get_wzd_sys_upgrade_status (&ui1_sys_upgrade_status);

            if (APP_CFG_CUST_WZD_SYS_UPDATE_COMPLETE == ui1_sys_upgrade_status)
            {
                DBG_LOG_PRINT(("[WZD] %s() %d: Cast TV, ui1_sys_upgrade_status == APP_CFG_CUST_WZD_SYS_UPDATE_COMPLETE.\n\r", __FUNCTION__, __LINE__));
                DBG_LOG_PRINT(("[WZD] %s() %d: Cast TV, set to be WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST.\n\r", __FUNCTION__, __LINE__));

                UINT8   ui1_idx_ir_mode = WZD_OOBE_IR_MODE;
                a_cfg_cust_get_oobe_ir_mode(&ui1_idx_ir_mode);
                if(ui1_idx_ir_mode == WZD_OOBE_IR_MODE) {
                    DBG_LOG_PRINT(("[WZD] %s() %d: After upgrade, IR Mode status is WZD_OOBE_IR_MODE.\n\r", __FUNCTION__, __LINE__));
                } else if(ui1_idx_ir_mode == WZD_OOBE_SC_MODE) {
                    DBG_LOG_PRINT(("[WZD] %s() %d: After upgrade, IR Mode status is WZD_OOBE_SC_MODE.\n\r", __FUNCTION__, __LINE__));
                } else {
                    DBG_LOG_PRINT(("[WZD] %s() %d: After upgrade, IR Mode status is UNKNOWN.\n\r", __FUNCTION__, __LINE__));
                }

                a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST));
                if(ui1_idx_ir_mode == WZD_OOBE_IR_MODE)
                {
                    rest_event_notify("oobe/currentstate", 0, "UPDATING_SMARTCAST_IR");
                }
                else
                {
                    rest_event_notify("oobe/currentstate", 0, "UPDATING_SMARTCAST");
                }

                DBG_LOG_PRINT(("[WZD] %s() %d: After reboot, set oobe upgrade finished status to be TRUE.\n\r", __FUNCTION__, __LINE__));
                a_nav_updater_uli_set_oobe_update_finished(TRUE);

                a_cfg_cust_set_wzd_sys_upgrade_status (APP_CFG_CUST_WZD_SYS_UPDATE_INIT);
            }
        }
    }
    else
    {
        DBG_LOG_PRINT(( "[WZD]%s() %d: ERROR!\n", __FUNCTION__, __LINE__));
    }
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _wzd_app_power_seq_cb
 *
 * Description: The callback function is called by the AEE.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static BOOL  _wzd_app_power_seq_cb (VOID)
{
    BOOL    b_resume = FALSE;

	/* if need launching retail mode, should NOT enter wizard any more */
#ifdef APP_RETAIL_MODE_SUPPORT
    UINT32  ui4_model_idx = 0;
    ACFG_RETAIL_MODE_T	t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    UINT8                   ui1_mode = 0;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode ||
		ACFG_RETAIL_MODE_NO_PLAYING == t_retail_mode)
    {
        /* check burning mode */
        a_cfg_get_factory_mode(&ui1_mode);
        a_cfg_custom_get_model_idx(&ui4_model_idx);

        if (0 == ui4_model_idx
            || (APP_CFG_FAC_MODE_BURNING_MASK & ui1_mode))
        {
            /* First boot up for facotry, and no eep init
            *  disable retail mode.
            */
            DBG_LOG_PRINT(("<WZD> eep not init, disable retail mode.\n"));
            a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
            return FALSE;
        }

    #ifdef APP_HOTKEY_WAKEUP_SUPPORT
        c_pcl_set_hotkey_active(FALSE); /*launch retailmode during startup, discard hotkey*/
        a_tv_custom_set_hotkey_wakeup_active(WAKEUP_AP_RETAILMODE_SET);
    #endif

        /* reset to normal */
        a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_NORMAL);
    }
#endif

#ifdef APP_C4TV_SUPPORT
    _wzd_set_page_process();
#endif

#ifdef WZD_CUSTOM_POWER_SEQ_CB
    b_resume = wzd_custom_power_seq_cb ();
#endif
    if (b_resume == FALSE)
    {
        b_resume = a_wzd_is_resume ();
    }

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    if (b_resume)
    {
        c_pcl_set_hotkey_active(FALSE); /*launch wizard during startup, discard hotkey*/
        a_tv_custom_set_hotkey_wakeup_active(WAKEUP_AP_WZD_SET);   /*set */
    }
    else
    {
        a_tv_custom_set_hotkey_wakeup_active(WAKEUP_AP_NONE);   /*set no AP resume in startup */
    }
#endif

    return b_resume;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nfy_wgl
 *
 * Description: The callback function is called by the widget library.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nfy_wgl (UINT32    ui4_msg,
                           VOID*     pv_param1,
                           VOID*     pv_param2)
{
    WZD_WIDGET_MSG_T  t_msg;
    UINT32            ui4_key_code;

    t_msg.ui4_msg   = ui4_msg;
    t_msg.pv_param1 = pv_param1;
    t_msg.pv_param2 = pv_param2;

#ifdef APP_C4TV_SUPPORT
    if (WZD_STATE_RESUME_C4TV == t_g_wzd.ui1_state)
    {
        // Do nothing since no available page info for Cast OOBE.
        DBG_LOG_PRINT(("[WZD] %s, %d\n\r", __FUNCTION__, __LINE__));
        return 0;
    }
#endif

    switch(t_msg.ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {

#ifdef WZD_REMAPPING_KEY
            wzd_custom_remapping_key (& t_msg);
#endif

            /* get key code */
            ui4_key_code = (UINT32)t_msg.pv_param1;

            /* convert front panels into rc keys */
            if (ui4_key_code & KEY_SRC_FRONT_PANEL)
            {
                ui4_key_code &= (~KEY_SRC_FRONT_PANEL);
                switch (ui4_key_code)
                {
                case BTN_PRG_UP:
                    ui4_key_code = BTN_CURSOR_UP;
                    break;
                case BTN_PRG_DOWN:
                    ui4_key_code = BTN_CURSOR_DOWN;
                    break;
                case BTN_VOL_UP:
                    ui4_key_code = BTN_CURSOR_RIGHT;
                    break;
                case BTN_VOL_DOWN:
                    ui4_key_code = BTN_CURSOR_LEFT;
                    break;
                case BTN_INPUT_SRC:
                    ui4_key_code = BTN_SELECT;
                    break;
                }
                t_msg.pv_param1 = (VOID*)ui4_key_code;
            }

            if (ui4_key_code == BTN_CUSTOM_1 ||
                ui4_key_code == BTN_KB_ENTER)
            {
                ui4_key_code = (UINT32)BTN_SELECT;
                t_msg.pv_param1 = (VOID*)(UINT32)BTN_SELECT;
            }
            /* store current page id */

            /* if current page is custom page ,
             * it will process all key (except BTN_SELECT & BTN_EXIT) down/repeat message itself.
             * The BTN_SELECT and BTN_EXIT will be processed "pf_nfy_sel"
             */
            WZD_PAGE_INFO_T*  pt_page_info = NULL ;

            _wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx ,&pt_page_info) ;
            if (WZD_PAGE_TYPE_CUST_PAGE == pt_page_info->pt_page_data->t_page_type
                &&
                BTN_SELECT != ui4_key_code
                &&
                BTN_EXIT != ui4_key_code
                &&
                BTN_RETURN != ui4_key_code)
            {
                /* Deal with WGL_MSG_KEY_REPEAT as WGL_MSG_KEY_DOWN.
                 * The message will be dispatched to Widget Manager by using Wizard's thread
                 */

                /* disable netflix/vudu/yahoo/M-GO/Amazon hotkey */
                if ( BTN_WIDGET == ui4_key_code ||
                     BTN_NETFLIX == ui4_key_code ||
                     BTN_AMAZON == ui4_key_code ||
                     BTN_MGO == ui4_key_code ||
                     BTN_VUDU == ui4_key_code ||
                     BTN_IHEART_RADIO == ui4_key_code ||
                     BTN_CUSTOM_11 == ui4_key_code ||
                     BTN_WATCHFREE == ui4_key_code ||
                     BTN_REDBOX == ui4_key_code ||
                     BTN_HAYSTACK == ui4_key_code )
                {
                    return WZDR_OK;
                }

                /* use vol+/- mute in on-boarding */
                if (BTN_VOL_DOWN == ui4_key_code ||
                    BTN_VOL_UP == ui4_key_code ||
                    BTN_MUTE == ui4_key_code )
                {
                    if (!t_g_wzd.b_g_is_vol_key_enable)
                    {
                        return WZDR_OK;
                    }
                    wzd_app_send_msg(WZD_MSG_RMK_CLIENT_KEY, &t_msg, sizeof(WZD_WIDGET_MSG_T));

                    /* change vol mute state */
                    if(BTN_MUTE == ui4_key_code)
                    {
                        b_g_is_mute = !b_g_is_mute;
                    }
                    else if(BTN_VOL_UP == ui4_key_code && b_g_is_mute)
                    {
                        b_g_is_mute = FALSE;
                    }
                    return WZDR_OK;
                }

                t_msg.ui4_msg = WGL_MSG_KEY_DOWN ;
                t_msg.ui1_cur_pg_idx = t_g_wzd.ui1_page_idx ;
                wzd_app_send_msg (WZD_MSG_WGL_NFY, & t_msg, sizeof (WZD_WIDGET_MSG_T));
                return WZDR_OK ;
            }

#ifndef APP_ACI_SUPPORT


            /* send key message to Wizard */
            switch (ui4_key_code)
            {
                case BTN_CURSOR_UP:
                    if (t_msg.ui4_msg == WGL_MSG_KEY_REPEAT)
                    {
                        t_msg.ui4_msg = WGL_MSG_KEY_DOWN;
                    }
                    wzd_app_send_msg (WZD_MSG_BTN_CURSOR_UP, NULL, 0);

                    break;

                case BTN_CURSOR_DOWN:
                    if (t_msg.ui4_msg == WGL_MSG_KEY_REPEAT)
                    {
                        t_msg.ui4_msg = WGL_MSG_KEY_DOWN;
                    }
                    wzd_app_send_msg (WZD_MSG_BTN_CURSOR_DOWN, NULL, 0);

                    break;

                case BTN_CURSOR_LEFT:
                    if (!t_g_wzd.b_next_key)
                    {
                        return WZDR_OK;
                    }
                    wzd_app_send_msg (WZD_MSG_BTN_CURSOR_LEFT, NULL, 0);

                    break;

                case BTN_CURSOR_RIGHT:
                    if (!t_g_wzd.b_next_key)
                    {
                        return WZDR_OK;
                    }
                    wzd_app_send_msg (WZD_MSG_BTN_CURSOR_RIGHT, NULL, 0);

                    break;

                case BTN_SELECT:
                    /* When is scanning, BTN_SELECT will should stop scanning */
                    if (t_msg.ui4_msg == WGL_MSG_KEY_REPEAT)
                    {
                       break;
                    }

                    if (wzd_is_scan_active ())
                    {
                        break;
                    }
                    wzd_app_send_msg (WZD_MSG_BTN_SELECT, NULL, 0);
                    break;

                case BTN_EXIT:
                    /* When is scanning, BTN_EXIT should stop scanning */
                    if (wzd_is_scan_active ())
                    {
                        t_g_wzd.b_been_cancel = TRUE;
                        wzd_app_send_msg (WZD_MSG_BTN_SELECT, NULL, 0);
                        break;
                    }
                    wzd_app_send_msg (WZD_MSG_BTN_EXIT, NULL, 0);
                    break;

                case BTN_RETURN:
                    if (t_msg.ui4_msg == WGL_MSG_KEY_REPEAT)
                    {
                        t_msg.ui4_msg = WGL_MSG_KEY_DOWN;
                    }
                    wzd_app_send_msg (WZD_MSG_BTN_RETURN, NULL, 0);
                    break;

                case BTN_VOL_DOWN:
                case BTN_VOL_UP:
                case BTN_MUTE:
                    /* useless code */
                    wzd_app_send_msg(WZD_MSG_RMK_CLIENT_KEY, &t_msg, sizeof(WZD_WIDGET_MSG_T));
                    return WZDR_OK;

                default:
                    break;
            }

#else
            BOOL b_aci_selecting = FALSE, b_aci_detected = FALSE;;

            wzd_util_get_aci_status(&b_aci_selecting, &b_aci_detected);

            /* send key message to Wizard */
            if (!b_aci_selecting)
            {
                switch (ui4_key_code)
                {
                    case BTN_CURSOR_UP:
                        if (t_msg.ui4_msg == WGL_MSG_KEY_REPEAT)
                        {
                            t_msg.ui4_msg = WGL_MSG_KEY_DOWN;
                        }
                        wzd_app_send_msg (WZD_MSG_BTN_CURSOR_UP, NULL, 0);

                        break;

                    case BTN_CURSOR_DOWN:
                        if (t_msg.ui4_msg == WGL_MSG_KEY_REPEAT)
                        {
                            t_msg.ui4_msg = WGL_MSG_KEY_DOWN;
                        }
                        wzd_app_send_msg (WZD_MSG_BTN_CURSOR_DOWN, NULL, 0);

                        break;

                    case BTN_CURSOR_LEFT:
                        if (!t_g_wzd.b_next_key)
                        {
                            return WZDR_OK;
                        }
                        wzd_app_send_msg (WZD_MSG_BTN_CURSOR_LEFT, NULL, 0);

                        break;

                    case BTN_CURSOR_RIGHT:
                        if (!t_g_wzd.b_next_key)
                        {
                            return WZDR_OK;
                        }
                        wzd_app_send_msg (WZD_MSG_BTN_CURSOR_RIGHT, NULL, 0);

                        break;

                    case BTN_SELECT:
                        if (t_msg.ui4_msg == WGL_MSG_KEY_REPEAT)
                        {
                           break;
                        }

                        if (wzd_is_scan_active ())  /* When is scanning, BTN_SELECT will should stop scanning */
                        {
                            break;
                        }
                        wzd_app_send_msg (WZD_MSG_BTN_SELECT, NULL, 0);

                        break;

                    case BTN_EXIT:
                        /* When is scanning, BTN_EXIT should stop scanning */
                        if (wzd_is_scan_active ())
                        {
                            t_g_wzd.b_been_cancel = TRUE;
                            wzd_app_send_msg (WZD_MSG_BTN_SELECT, NULL, 0);

                            break;
                        }
                        wzd_app_send_msg (WZD_MSG_BTN_EXIT, NULL, 0);

                        break;

                    default:
                        break;
                }
            }
            else
            {
                wzd_app_send_msg(WZD_MSG_ACI_SELECTION, &ui4_key_code, sizeof(UINT32));
            }

#endif
            break;
        }
        case WGL_MSG_ANIMATION_TICK:
        {
            break;
        }
#ifdef APP_ZOOM_MODE_SUPPORT
        case WGL_MSG_NOTIFY_HL_AREA:
        {
            return WZDR_OK;
        }
#endif
        default:
        {
            break;
        }
    }

    /* the message will be dispatched to Widget Manager by using Wizard's thread */

    t_msg.ui1_cur_pg_idx = t_g_wzd.ui1_page_idx ;

    wzd_app_send_msg (WZD_MSG_WGL_NFY, & t_msg, sizeof (WZD_WIDGET_MSG_T));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nfy_timer
 *
 * Description: This callback function is called when a timer expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
#ifdef APP_WZD_AUTO_PAUSE
static VOID _wzd_nfy_timer (HANDLE_T    h_timer,
                            VOID*       pv_tag)
{
    DBG_INFO (("<WZD> auto-pause timer expired\n\r"));

    if (h_timer == t_g_wzd.h_timer_pause) /* auto-pause timer */
    {
        /* set a timer-expired message to Wizard's message queue */
        wzd_app_send_msg (WZD_MSG_PAUSE_TIMER_EXPIRED, NULL, 0);
    }
}
#endif
/*-----------------------------------------------------------------------------
 * Name: _wzd_nfy_scan_timer
 *
 * Description: This callback function is called when a scan timer expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _wzd_nfy_scan_timer (HANDLE_T    h_timer,
                                 VOID*       pv_tag)
{
    if (h_timer == t_g_wzd.h_timer_scan) /* update the scanning text */
    {
        /* set a timer-expired message to Wizard's message queue */
        wzd_app_send_msg (WZD_MSG_SCAN_TIMER_EXPIRED, NULL, 0);
    }
}

#ifndef APP_C4TV_SUPPORT
 /*----------------------------------------------------------------------------
  * Name: _wzd_page_compl_finished_btn_do_show_dlg_timer
  *
  * Description:
  *
  * Inputs:  -
  *
  * Outputs: -
  *
  * Returns:
  ----------------------------------------------------------------------------*/
 static VOID _wzd_nfy_dlg_timer_hdlr(VOID* pv_data,
                                     SIZE_T  z_data_size)
{
    HANDLE_T    h_timer = *(HANDLE_T*)pv_data;

    if (h_timer == t_g_wzd.h_timer_dlg)
    {
        wzd_view_full_screen_dlg_hide();

        if (h_pre_btn_focus != NULL_HANDLE)
        {
            c_wgl_set_focus(h_pre_btn_focus, FALSE);
            h_pre_btn_focus = NULL_HANDLE;
        }

        wzd_view_main_frm_repaint();
    }
}


/*-----------------------------------------------------------------------------
 * Name: _wzd_nfy_dlg_timer
 *
 * Description: This callback function is called when a dlg timer expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _wzd_nfy_dlg_timer (HANDLE_T    h_timer,
                                VOID*       pv_tag)
{
    wzd_async_invoke(_wzd_nfy_dlg_timer_hdlr, &h_timer, sizeof(HANDLE_T), FALSE);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_full_screen_dlg_btn_nfy
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_power_off_dlg_btn_nfy(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32                 i4_ret = WZDR_OK;

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:

        if( BTN_SELECT == (UINT32)pv_param1 )
        {
            wzd_view_full_screen_dlg_hide();

            if (h_pre_btn_focus != NULL_HANDLE)
            {
                c_wgl_set_focus(h_pre_btn_focus, FALSE);
                h_pre_btn_focus = NULL_HANDLE;
            }

            wzd_view_main_frm_repaint();

            c_timer_stop(t_g_wzd.h_timer_dlg);
        }
        return WZDR_OK;

    default:
        break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    return i4_ret;

}

/*-----------------------------------------------------------------------------
 * Name: _wzd_show_power_off_dlg
 *
 * Description: This callback function is called when a dlg timer expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _wzd_show_power_off_dlg (VOID)
{
	/* store previous focus handle */
	c_wgl_get_focus(&h_pre_btn_focus);

	wzd_view_full_screen_dlg_set_icon (
					NULL_HANDLE,
					FALSE);

	wzd_view_full_screen_dlg_set_text (
					WZD_TEXT(MLM_WZD_KEY_POWER_OFF_WARNING),
					FALSE);

    wzd_view_full_screen_dlg_set_btn_proc_fct(_wzd_power_off_dlg_btn_nfy);

	wzd_view_full_screen_dlg_show(TRUE);

	/* enable the power off dialog timer */
    c_timer_start (t_g_wzd.h_timer_dlg,
				   3000,
				   X_TIMER_FLAG_ONCE,
				   _wzd_nfy_dlg_timer,
				   NULL);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_show_power_off_dlg_hdlr
 *
 * Description: This callback function is called when a dlg timer expired.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _wzd_show_power_off_dlg_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
	/* pre focus not NULL,  current power off dialog is popup */
	if (h_pre_btn_focus != NULL_HANDLE)
	{
		return;
	}

	_wzd_show_power_off_dlg();
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _wzd_btn_select
 *
 * Description: The function handles the condition when the SELECT button is
 *              pressed.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_btn_select (VOID)
{
    if (wzd_is_scan_active ())
    {
		if(t_g_wzd.b_g_is_rf_scan)
		{

			if (wzd_page_tv_setup_is_scanning())
	        {   /* perform cancel-scan task */
	            RET_ON_ERR (wzd_page_tv_setup_scan_cancel ());
	        }
            else
	        {   /* change status: scanning -> cancel scanning. */
	            wzd_page_tv_setup_set_scan_status (WZD_SB_STATUS_CANCEL);
	            RET_ON_ERR (_wzd_scan_end ());
	        }
		}
		else
		{
			if (wzd_util_is_scanning (t_g_wzd.ui2_scanning_type))
	        {   /* perform cancel-scan task */
	            RET_ON_ERR (wzd_util_scan_cancel (t_g_wzd.ui2_scanning_type));
	        }
            else
	        {   /* change status: scanning -> cancel scanning. */
	            wzd_util_set_scan_status (WZD_SB_STATUS_CANCEL);
	            RET_ON_ERR (_wzd_scan_end ());
	        }
		}
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_btn_return
 *
 * Description: The function handles the condition when the RETURN button is
 *              pressed.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_btn_return (VOID)
{
	WZD_PAGE_INFO_T*    pt_page = NULL;

    RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));
    if (NULL != pt_page->pt_page_data->pf_return_nfy_fct)
    {
        pt_page->pt_page_data->pf_return_nfy_fct();
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_anim_finish
 *
 * Description: The function handles the condition when the current page
 *              show animation is finish.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_anim_finish (VOID)
{
	WZD_PAGE_INFO_T*    pt_page = NULL;

    RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));
    if (NULL != pt_page->pt_page_data->pf_anim_finish_nfy_fct)
    {
        pt_page->pt_page_data->pf_anim_finish_nfy_fct();
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_anim_finish_hdlr
 *
 * Description: This callback function is called when page anim is finish.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _wzd_page_anim_finish_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
	_wzd_page_anim_finish();
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_btn_exit
 *
 * Description: The function handles the condition when the EXIT button is
 *              pressed.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_btn_exit (VOID)
{
	WZD_PAGE_INFO_T*    pt_page = NULL;

    RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));
    if (NULL != pt_page->pt_page_data->pf_exit_nfy_fct)
    {
        pt_page->pt_page_data->pf_exit_nfy_fct();
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_btn_cursor_up
 *
 * Description: The function handles the condition when the CURSOR_UP button is
 *              pressed.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_btn_cursor_up (VOID)
{
    /* change focus to previous item */
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_btn_cursor_down
 *
 * Description: The function handles the condition when the CURSOR_DOWN button is
 *              pressed.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_btn_cursor_down (VOID)
{
    /* change focus to next item */
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_btn_cursor_left
 *
 * Description: The function handles the condition when the CURSOR_LEFT button is
 *              pressed.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_btn_cursor_left (VOID)
{
    UINT8           ui1_prv_pg_idx = 0 ;

    RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_prv_pg_idx)) ;

#if 0


    if (!wzd_is_scan_active ())
    {
#ifndef APP_WIZARD_CODE_INPUT_SUPPORT
        if (t_g_wzd.ui1_page_idx > 0)
        {   /* show the previous page */
#ifdef APP_DVBT_SUPPORT
            if(FALSE == wzd_is_nwl_page_show_able() &&
                t_g_wzd.ui1_page_idx == (t_g_wzd.ui1_page_num -1))
            {
                RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_prv_pg_idx)) ;
                RET_ON_ERR (_wzd_get_prev_page (ui1_prv_pg_idx ,&ui1_prv_pg_idx)) ;
                RET_ON_ERR (_wzd_show_update (ui1_prv_pg_idx, TRUE));
            }
            else
            {
            RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_prv_pg_idx)) ;
            RET_ON_ERR (_wzd_show_update (ui1_prv_pg_idx, TRUE));
        }
#else
            RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_prv_pg_idx)) ;
            RET_ON_ERR (_wzd_show_update (ui1_prv_pg_idx, TRUE));
#endif

        }
#else
        WZD_PAGE_INFO_T*    pt_page     = NULL;

        /* get the current page entry */
        RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));

        if (pt_page->pt_page_data->t_page_type != WZD_PAGE_TYPE_CODE_INPUT)
        {
            if (t_g_wzd.ui1_page_idx > 0)
            {   /* show the previous page */
#ifdef APP_DVBT_SUPPORT
                if(FALSE == wzd_is_nwl_page_show_able() &&
                   t_g_wzd.ui1_page_idx == (t_g_wzd.ui1_page_num -1))
                {
                    RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_prv_pg_idx)) ;
                    RET_ON_ERR (_wzd_get_prev_page (ui1_prv_pg_idx ,&ui1_prv_pg_idx)) ;
                    RET_ON_ERR (_wzd_show_update (ui1_prv_pg_idx, TRUE));
                }
                else
                {
                RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_prv_pg_idx)) ;
                RET_ON_ERR (_wzd_show_update (ui1_prv_pg_idx, TRUE));
            }
#else
                RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_prv_pg_idx)) ;
                RET_ON_ERR (_wzd_show_update (ui1_prv_pg_idx, TRUE));
#endif
            }
        }
        else
        {
            if (wzd_view_code_box_set_focus_prev_digit () != WZDR_OK)
            {
                if (t_g_wzd.ui1_page_idx > 0)
                {   /* show the previous page */
                    RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_prv_pg_idx)) ;
                    RET_ON_ERR (_wzd_show_update (ui1_prv_pg_idx, TRUE));
                }
            }
            else
            {
                wzd_view_code_txt_clear_text(TRUE);
            }
        }
#endif
    }
#endif
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_btn_cursor_right
 *
 * Description: The function handles the condition when the CURSOR_RIGHT button is
 *              pressed.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_btn_cursor_right (VOID)
{
#if 0
#ifndef APP_WIZARD_CODE_INPUT_SUPPORT
    /* treat cursor right as btn_select */
    return _wzd_btn_select ();
#else
    WZD_PAGE_INFO_T*    pt_page     = NULL;

    /* get the current page entry */
    RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));

    if (pt_page->pt_page_data->t_page_type != WZD_PAGE_TYPE_CODE_INPUT)
    {
        /* treat cursor right as btn_select */
        return _wzd_btn_select ();
    }
    else
    {
        if (wzd_view_code_box_set_focus_next_digit () != WZDR_OK)
        {
            /* treat cursor right as btn_select */
            return _wzd_btn_select ();
        }
        else
        {
            wzd_view_code_txt_clear_text(TRUE);
        }
    }
    return WZDR_OK;
#endif
#endif
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_btn_change_focus
 *
 * Description: The function handles the condition when the CURSOR_UP and
 *              CURSOR_DOWN is pressed.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_btn_change_focus (VOID)
{
    WZD_PAGE_INFO_T*            pt_page     = NULL;
    WZD_PAGE_INFO_ICON_DATA*    pt_icon_data = NULL;
    UINT16                      ui2_hlt_idx = 0;

    /* get the current page entry, only handle WZD_PAGE_TYPE_DESC_LIST_WITH_ICON type */
    RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));

    if (pt_page == NULL ||
        pt_page->pt_page_data->t_page_type != WZD_PAGE_TYPE_DESC_LIST_WITH_ICON ||
        pt_page->pt_page_data->pv_data == NULL)
    {
        return WZDR_OK;
    }

    pt_icon_data = (WZD_PAGE_INFO_ICON_DATA*)pt_page->pt_page_data->pv_data;

    /* get highlighted index */
    RET_ON_ERR (wzd_view_seti_lst_get_hlt_idx (& ui2_hlt_idx));

    /* load icon image according to highlight index*/
    RET_ON_ERR (wzd_view_seti_icon_load_img (pt_icon_data, ui2_hlt_idx));

    RET_ON_ERR (wzd_view_seti_icon_repaint ());

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_lst_get_page_entry
 *
 * Description: The function gets the current page entry.
 *
 * Inputs:  The entry index requested.
 *
 * Outputs: The entry pointer.
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_lst_get_page_entry(UINT8              ui1_page_idx,
                                          WZD_PAGE_INFO_T**  ppt_crnt_page)
{
    WZD_PAGE_INFO_T*    pt_page;

    if (ppt_crnt_page == NULL)
    {
        return WZDR_INV_ARG;
    }

    if ( NULL           != t_g_wzd.pt_page_info &&
         ui1_page_idx   == t_g_wzd.pt_page_info->ui1_page_idx)
    {   /* the catch entry */
        *ppt_crnt_page = t_g_wzd.pt_page_info;
    }
    else
    {   /* search entry by index */
        if (DLIST_IS_EMPTY (& t_g_wzd.t_page_lst))
        {
            return WZDR_FAIL;
        }

        /* get first entry */
        pt_page = DLIST_HEAD (& t_g_wzd.t_page_lst);

        /* traverse page list */
        while (pt_page != NULL)
        {
            if (ui1_page_idx == pt_page->ui1_page_idx)
            {
                t_g_wzd.pt_page_info = pt_page;     /* catch the entry */
                *ppt_crnt_page       = pt_page;
                break;
            }

            pt_page = DLIST_NEXT (pt_page, t_page_link); /* get next entry */
        }

        /* no match entry */
        if (pt_page == NULL)
        {
            return WZDR_FAIL;
        }
    }

    return WZDR_OK;
}

#if 0
/*-----------------------------------------------------------------------------
 * Name: _wzd_seti_lst_nfy_sel
 *
 * Description: The function calls the callback function of the current page entry.
 *
 * Inputs:  -
 *
 * Outputs: The entry pointer.
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_seti_lst_nfy_sel(WZD_MSG_CUSTOM_T* pt_ret_msg)
{
    WZD_PAGE_INFO_T*    pt_page     = NULL;
    UINT16              ui2_hlt_idx = 0;

    /* get the current page entry */
    RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));

    /* call the callback function */
    if (pt_ret_msg == NULL ||
        pt_page    == NULL ||
        pt_page->pf_nfy_sel == NULL)
    {
        return WZDR_FAIL;
    }

    /* get highlighted index */
    RET_ON_ERR (wzd_view_seti_lst_get_hlt_idx (& ui2_hlt_idx));

    pt_page->ui2_sel_idx = ui2_hlt_idx;

    RET_ON_ERR( pt_page->pf_nfy_sel (pt_page->ui2_sel_idx, NULL, pt_ret_msg));

    return WZDR_OK;
}
#endif
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _wzd_code_box_nfy_sel
 *
 * Description: The function calls the callback function of the current page entry.
 *
 * Inputs:  -
 *
 * Outputs: The entry pointer.
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_code_box_nfy_sel(WZD_MSG_CUSTOM_T* pt_ret_msg)
{
    WZD_PAGE_INFO_T*    pt_page     = NULL;
    UINT64              ui8_code_num = CODE_NUM_INVALID;

    /* get the current page entry */
    RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));

    /* call the callback function */
    if (pt_ret_msg == NULL ||
        pt_page    == NULL ||
        pt_page->pf_nfy_sel == NULL)
    {
        return WZDR_FAIL;
    }

    /* get highlighted index */
    RET_ON_ERR (wzd_view_code_box_get_code_num (& ui8_code_num));

    pt_page->ui8_code_num = ui8_code_num;

    RET_ON_ERR( pt_page->pf_nfy_sel (0, &ui8_code_num, pt_ret_msg));

    return WZDR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _wzd_seti_lst_clean
 *
 * Description: The function cleans up all the elements of setting list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_seti_lst_clean(VOID)
{
    UINT16  ui2_hlt_idx;

    /* get highlighted index */
    RET_ON_ERR (wzd_view_seti_lst_get_hlt_idx (& ui2_hlt_idx));

    if (ui2_hlt_idx != WGL_LB_NULL_INDEX)
    {
        /* un-highlight element */
        RET_ON_ERR (wzd_view_seti_lst_unhlt_elem (ui2_hlt_idx));
    }

    /* set element number to ELEM_VIEW_SIZE */
    RET_ON_ERR (wzd_view_seti_lst_set_elem_num (0));
    RET_ON_ERR (wzd_view_seti_lst_set_elem_num (SETI_LB_ELEM_NUM));

    /* clean all elements */
    RET_ON_ERR (wzd_view_seti_lst_clr_elems (0, SETI_LB_ELEM_NUM-1));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_seti_lst_update
 *
 * Description: The function updates setting list.
 *
 * Inputs:  pt_page             include the updated information of the setting list
 *          b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_seti_lst_update (WZD_PAGE_INFO_T*     pt_page,
                                   BOOL                 b_repaint)
{
    UINT16              ui2_elem_idx;
    UINT16              ui2_elem_num;
    UTF16_T             w2s_str [64];

    if (!pt_page || !pt_page->pt_page_data)
    {
        return WZDR_INV_ARG ;
    }

    RET_ON_ERR (wzd_view_seti_lst_set_visibility(TRUE));

    /* clean-up the original setting list */
    RET_ON_ERR (_wzd_seti_lst_clean ());

    /* resize the element number */
    if (pt_page->pt_page_data->pf_get_num != NULL)
    {
        ui2_elem_num = pt_page->pt_page_data->pf_get_num();
    }
    else
    {
        ui2_elem_num = pt_page->pt_page_data->ui1_elem_num;
    }

    /* check max element number */
    if (ui2_elem_num >= SETI_LB_ELEM_NUM)
    {
        ui2_elem_num = SETI_LB_ELEM_NUM;
    }

    RET_ON_ERR (wzd_view_seti_lst_set_elem_num (ui2_elem_num));

    /* set element text */
    for (ui2_elem_idx = 0; ui2_elem_idx < ui2_elem_num; ui2_elem_idx++)
    {
        if (pt_page->pt_page_data->pf_get_text != NULL)
        {
            c_memset(w2s_str, 0, sizeof(w2s_str));
            pt_page->pt_page_data->pf_get_text(ui2_elem_idx, w2s_str, 64);
            RET_ON_ERR (wzd_view_seti_lst_set_elem_text (ui2_elem_idx, w2s_str));
        }
        else
        {
            RET_ON_ERR (wzd_view_seti_lst_set_elem_text (
                                ui2_elem_idx,
                                WZD_TEXT (pt_page->pt_page_data->aui2_elem_text_keys[ui2_elem_idx])));
        }
    }

    /* highlight the first element */
    if (pt_page->ui2_sel_idx >= ui2_elem_num)
    {
        pt_page->ui2_sel_idx = 0;
    }

    RET_ON_ERR (wzd_view_seti_lst_hlt_elem (pt_page->ui2_sel_idx));

    /*
       Repaint setting list.
    */
    if (b_repaint)
    {
        RET_ON_ERR (wzd_view_seti_lst_repaint ());
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_seti_icon_update
 *
 * Description: The function updates setting icon.
 *
 * Inputs:  pt_page             include the updated information of the setting list
 *          b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 _wzd_seti_icon_update (WZD_PAGE_INFO_T* pt_page, BOOL b_repaint)
{
    WZD_PAGE_INFO_ICON_DATA*    pt_icon_data = NULL ;

    if (!pt_page || !pt_page->pt_page_data)
    {
        return WZDR_INV_ARG ;
    }

    pt_icon_data = (WZD_PAGE_INFO_ICON_DATA*)pt_page->pt_page_data->pv_data;

    if (pt_icon_data == NULL)
    {
        return -1;
    }

    RET_ON_ERR (wzd_view_seti_icon_load_img (pt_icon_data, pt_page->ui2_sel_idx));

    if (b_repaint)
    {
        RET_ON_ERR (wzd_view_seti_icon_repaint ());
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_title_lst_update
 *
 * Description: The function updates title information.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_title_lst_update (WZD_PAGE_INFO_T*    pt_page,
                                    BOOL                b_repaint)
{
    if (!pt_page)
    {
        return WZDR_INV_ARG ;
    }

    /*Wizard title.*/
    RET_ON_ERR (wzd_view_title_set_htxt (WZD_TEXT (pt_page->pt_page_data->ui2_title_key), NULL_HANDLE));

    /*Repaint title list.*/
    if (b_repaint)
    {
        RET_ON_ERR (wzd_view_title_txt_repaint ());
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_help_lst_update
 *
 * Description: The function updates help information.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_help_lst_update (WZD_PAGE_INFO_T*     pt_page,
                                   BOOL                 b_repaint)
{
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_scan_help_lst_update
 *
 * Description: The function updates scanning help information.
 *
 * Inputs:  b_stop              scanning is stop or not.
 *          b_repaint           repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_scan_help_lst_update (BOOL    b_stop,
                                        BOOL    b_repaint)
{
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_desc_txt_update
 *
 * Description: The function updates description text information.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_desc_txt_update (WZD_PAGE_INFO_T*    pt_page,
                                   BOOL                b_repaint)
{
    if (!pt_page)
    {
        return WZDR_INV_ARG ;
    }

    /*
       Description text.
    */
    RET_ON_ERR (wzd_view_desc_txt_set_text (WZD_TEXT (pt_page->pt_page_data->ui2_desc_text_key)));

    /*
       Repaint title list.
    */
    if (b_repaint)
    {
        RET_ON_ERR (wzd_view_desc_txt_repaint ());
    }

    return  0;
}

#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _wzd_code_box_update
 *
 * Description: The function updates code input setting.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_code_box_update (WZD_PAGE_INFO_T*    pt_page,
                                   BOOL                b_repaint)
{
    if (!pt_page)
    {
        return WZDR_INV_ARG ;
    }

    if (pt_page->pt_page_data->pf_get_code_param != NULL)
    {
        pt_page->pt_page_data->pf_get_code_param(&pt_page->pt_page_data->ui1_code_elem_num,
                                                 pt_page->pt_page_data->aui1_code_style,
                                                 pt_page->pt_page_data->aw2s_code_sep_char,
                                                 &pt_page->ui8_code_num);
    }
    /*
       Code input box.
    */
    RET_ON_ERR (wzd_view_code_box_setup (pt_page->pt_page_data->ui1_code_elem_num,
                                         pt_page->pt_page_data->aui1_code_style,
                                         pt_page->pt_page_data->aw2s_code_sep_char));

    RET_ON_ERR (wzd_view_code_box_set_code_num (pt_page->ui8_code_num, b_repaint));
    RET_ON_ERR (wzd_view_code_box_set_visibility_focus (TRUE));
    /*
       Repaint code box.
    */
    if (b_repaint)
    {
        RET_ON_ERR (wzd_view_code_box_repaint ());
    }

    return  0;
}
#endif


/*-----------------------------------------------------------------------------
 * Name: _wzd_show_update
 *
 * Description: The function updates the title list, setting list, and help information.
 *
 * Inputs:  ui1_page_idx        page entry index.
 *          b_repaint           need repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_show_update (UINT8 ui1_page_idx,
                               BOOL  b_repaint)
{
    WZD_PAGE_INFO_T*            pt_page = NULL;
    HANDLE_T                    h_layout_frm = NULL_HANDLE ;
    WZD_ANIM_MOVE_PAGE_TYPE_T   e_move_hide_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
    WZD_ANIM_MOVE_PAGE_TYPE_T   e_move_show_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;

    if (ui1_page_idx >= t_g_wzd.ui1_page_num)
    {
        return WZDR_INV_ARG;
    }

    DBG_INFO (("<WZD> update page information (idx = %d)\n\r", ui1_page_idx));

    if (!b_g_is_need_animation)
    {
        b_g_is_need_animation = TRUE;

        if (a_wzd_is_resume_from_menu_setup())
        {
            /* ONLY show background */
            RET_ON_ERR (wzd_view_main_frm_show_bg_only ());
            c_thread_delay(500);

            e_move_hide_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;
        }
        else
        {
            e_move_hide_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
            e_move_show_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
        }
    }
    else if (WZD_PAGE_NAVI_PREV_PAGE == e_g_navi ||
        WZD_PAGE_NAVI_FIRST_PAGE == e_g_navi)
    {
        e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_RIGHT;
        e_move_show_type = WZD_ANIM_MOVE_PAGE_LEFT_TO_CENTER;
    }
    else if (WZD_PAGE_NAVI_LAST_FINISHED_PAGE == e_g_navi)
    {
        e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
        e_move_show_type = WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM;
    }
    else
    {
        e_move_hide_type = WZD_ANIM_MOVE_PAGE_CENTER_TO_LEFT;
        e_move_show_type = WZD_ANIM_MOVE_PAGE_RIGHT_TO_CENTER;
    }

    if (WZD_PAGE_NAVI_NEXT_PAGE == e_g_navi &&
        WZD_PAGE_INDEX_LANG == ui1_page_idx)
    {
        /* choose mode page */
        RET_ON_ERR (wzd_page_choose_mode_on_hide(TRUE));
    }
    else
    {
        /* start hide move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_hide_type));

        /* flush image cache when the move page animation is end */
        c_wgl_img_cache_flush();

    }

    /* hide current page */
    if (ui1_page_idx != t_g_wzd.ui1_page_idx)
    {
        RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));
        if (WZD_PAGE_TYPE_CUST_PAGE == pt_page->pt_page_data->t_page_type)
        {
            RET_ON_ERR (pt_page->pt_page_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide (t_g_wzd.ui1_page_idx)) ;
        }
        RET_ON_ERR (wzd_view_set_focus_widget (WZD_FOCUS_WIDGET_SETI_LST)) ;
    }

    /* set all widgets as visible */
    RET_ON_ERR( wzd_view_main_frm_set_visibility(TRUE));
    RET_ON_ERR( wzd_view_demo_txt_show(FALSE, FALSE));
    RET_ON_ERR( wzd_view_right_icon_show(FALSE, FALSE));
	RET_ON_ERR( wzd_view_full_screen_dlg_hide());
	RET_ON_ERR( wzd_view_sel_box_show (WZD_SEL_BOX_SHOW_TYPE_HIDE));

#ifdef APP_2K12_RETAIL_DEMO_MODE
    /* hide choose mode page */
    wzd_page_choose_mode_on_hide(FALSE);
#endif

    /* hide all widget in layout frame */
    RET_ON_ERR (wzd_view_get_layout_frm (&h_layout_frm));
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm ,WGL_SW_HIDE_RECURSIVE)) ;
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm ,WGL_SW_NORMAL)) ;

    /* get the page entry */
    RET_ON_ERR (_wzd_page_lst_get_page_entry (ui1_page_idx, & pt_page));

    /* update the common widgets */
    RET_ON_ERR (_wzd_title_lst_update (pt_page, FALSE));
    RET_ON_ERR (_wzd_help_lst_update (pt_page, FALSE));

    /* do updating according the view type of the template layout */
    switch (pt_page->pt_page_data->t_page_type)
    {
        case WZD_PAGE_TYPE_CUST_PAGE :
        {
            /* show and update widgets uncluded in this layout */
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
            RET_ON_ERR (wzd_view_code_box_set_visibility_focus(FALSE));
#endif
            RET_ON_ERR (wzd_view_desc_txt_set_visibility (FALSE)) ;
            RET_ON_ERR (_wzd_desc_txt_update (pt_page, FALSE));

            /* move the control right to custom page */
            RET_ON_ERR (pt_page->pt_page_data->t_cust_page_fct_tab.pf_wzd_cust_page_show (ui1_page_idx)) ;
        }
        break ;

        case WZD_PAGE_TYPE_ONLY_DESC:
        {
            /* hide widgets that are not included in this layout. */
            RET_ON_ERR (wzd_view_seti_lst_set_visibility(FALSE));
            RET_ON_ERR (wzd_view_scan_bar_set_visibility(FALSE));
            RET_ON_ERR (wzd_view_seti_icon_set_visibility(FALSE));
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
            RET_ON_ERR (wzd_view_code_box_set_visibility_focus(FALSE));
#endif

            /* show and update widgets uncluded in this layout */
            RET_ON_ERR (wzd_view_desc_txt_set_visibility(TRUE)) ;
            RET_ON_ERR (_wzd_desc_txt_update (pt_page, FALSE));
        }
        break;

        case WZD_PAGE_TYPE_DESC_LIST:
        {
            /* hide widgets that are not included in this layout. */
            RET_ON_ERR (wzd_view_scan_bar_set_visibility(FALSE));
            RET_ON_ERR (wzd_view_seti_icon_set_visibility(FALSE));
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
            RET_ON_ERR (wzd_view_code_box_set_visibility_focus(FALSE));
#endif

            /* update widgets uncluded in this layout */
            RET_ON_ERR (wzd_view_desc_txt_set_visibility(TRUE)) ;
            RET_ON_ERR (wzd_view_seti_lst_set_visibility(TRUE)) ;
            RET_ON_ERR (_wzd_seti_lst_update (pt_page, FALSE));
            RET_ON_ERR (_wzd_desc_txt_update (pt_page, FALSE));
        }
        break;

        case WZD_PAGE_TYPE_DESC_LIST_WITH_ICON:
        {
            /* hide widgets that are not included in this layout. */
            RET_ON_ERR (wzd_view_scan_bar_set_visibility(FALSE));
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
            RET_ON_ERR (wzd_view_code_box_set_visibility_focus(FALSE));
#endif

            /* update widgets uncluded in this layout */
            RET_ON_ERR (wzd_view_desc_txt_set_visibility(TRUE)) ;
            RET_ON_ERR (wzd_view_seti_lst_set_visibility(TRUE)) ;
            RET_ON_ERR (wzd_view_seti_icon_set_visibility(TRUE)) ;
            RET_ON_ERR (_wzd_seti_lst_update (pt_page, FALSE));
            RET_ON_ERR (_wzd_seti_icon_update (pt_page, FALSE));
            RET_ON_ERR (_wzd_desc_txt_update (pt_page, FALSE));
        }
        break;

#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
        case WZD_PAGE_TYPE_CODE_INPUT:
        {
            /* hide widgets that are not included in this layout. */
            RET_ON_ERR (wzd_view_seti_lst_set_visibility(FALSE));
            RET_ON_ERR (wzd_view_scan_bar_set_visibility(FALSE));
            RET_ON_ERR (wzd_view_seti_icon_set_visibility(FALSE));

            /* show and update widgets uncluded in this layout */
            RET_ON_ERR (wzd_view_desc_txt_set_visibility(TRUE)) ;
            RET_ON_ERR (_wzd_desc_txt_update (pt_page, FALSE));
            RET_ON_ERR (_wzd_code_box_update (pt_page, FALSE));
        }
        break;
#endif
        case WZD_PAGE_TYPE_SCAN:
        {
            RET_ON_ERR (wzd_view_seti_icon_set_visibility(FALSE));
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
            RET_ON_ERR (wzd_view_code_box_set_visibility_focus(FALSE));
#endif
            /* hide widgets that are not included in this layout. */
                            /* no widgets */

            /* update widgets included in this layout */
            RET_ON_ERR (wzd_view_desc_txt_set_visibility(TRUE)) ;
            RET_ON_ERR (wzd_view_scan_bar_set_visibility(TRUE)) ;
            RET_ON_ERR (_wzd_seti_lst_update (pt_page, FALSE));
            RET_ON_ERR (_wzd_desc_txt_update (pt_page, FALSE));
            RET_ON_ERR (wzd_view_scan_bar_set_pos (0));
        }
        break;

        default:
        {
            DBG_INFO (("<WZD> Unknown view type of the template layout\n\r"));
        }
        break;
    }

    /* set the page index */
    t_g_wzd.ui1_page_idx = ui1_page_idx;

    if (WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM != e_move_show_type)
    {
        /* start show move animation */
        RET_ON_ERR (wzd_anim_start_move_page(e_move_show_type));
    }
    else
    {
        /* add thread delay */
        if (e_move_hide_type != WZD_ANIM_MOVE_PAGE_LAST_VALID_ITEM)
        {
            c_thread_delay(200);
        }

        /* reset base frame rect after animation */
        RET_ON_ERR (wzd_view_reset_base_frm_rect());

        /* repaint main frame recursive */
        if (b_repaint)
        {
            RET_ON_ERR (wzd_view_main_frm_repaint());
        }
    }

    /* send msg after page anim is finish */
    wzd_request_context_switch(_wzd_page_anim_finish_hdlr, NULL, NULL, NULL);

    return  0;
}

#ifndef APP_C4TV_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _wzd_show_clean
 *
 * Description: The function cleans the title list, setting list, and help information.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_show_clean (VOID)
{
    /* clean-up setting list */
    RET_ON_ERR (_wzd_seti_lst_clean ());

    return  0;
}
#endif

#if 0
/*-----------------------------------------------------------------------------
 * Name: _wzd_scan_desc_txt_update
 *
 * Description: The function concatenate the scanning text and update the description
 *              text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_scan_desc_txt_update(UINT16   ui2_txt_key,
                                       BOOL     b_step,
                                       BOOL     b_repaint)
{
    static UINT8 ui1_step=0;
    /* Be careful. In this function, it may occur memory corruption.
       The w2s_str needs the length at least 160. */
    UTF16_T     w2s_str[256];
    BOOL        b_ch_num;

    c_memset(w2s_str, 0, sizeof(w2s_str));
    //'c_uc_w2s_strcpy(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_HEAD));

    switch (ui2_txt_key)
    {
        case MLM_WZD_KEY_SCAN_PROGRESS:
        {
#ifdef APP_ACI_SUPPORT
            BOOL b_aci_detected = FALSE, b_aci_selecting = FALSE;
            wzd_util_get_aci_status(&b_aci_selecting, &b_aci_detected);

            if (!b_aci_detected)
            {
#endif
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_PROGRESS));

            if(ui1_step == 0)
            {
                c_uc_w2s_strcat(w2s_str, (UTF16_T*)(L"."));
            }
            else if(ui1_step == 1)
            {
                c_uc_w2s_strcat(w2s_str, (UTF16_T*)(L".."));
            }
            else
            {
                c_uc_w2s_strcat(w2s_str, (UTF16_T*)(L"..."));
            }

            if(b_step)
            {
                ui1_step = (UINT8)((ui1_step + 1) % 3);
            }

#ifdef APP_ACI_SUPPORT
            }
            else
            {
                c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_ACI_DETEC));
            }
#endif

            b_ch_num = TRUE;
        }
        break;

        case MLM_WZD_KEY_SCAN_COMPLETE:
        {
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_COMPLETE));
            b_ch_num = TRUE;
        }
        break;

        case MLM_WZD_KEY_SCAN_CANCEL:
        {
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_CANCEL));
            b_ch_num = FALSE;
        }
        break;

        case MLM_WZD_KEY_SCAN_ERROR:
        {
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_ERROR));
            b_ch_num = FALSE;
        }
        break;

#ifdef APP_ACI_SUPPORT
        case MLM_WZD_KEY_SCAN_ACI_DETEC:
        {
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_ACI_DETEC));
            b_ch_num = TRUE;
        }
        break;

#endif
        default:    /* Unknown Key */
        {
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_ERROR));
            b_ch_num = FALSE;
        }
        break;
    }

    if (b_ch_num)
    {
        UTF16_T     w2s_atv_num[10];
        UTF16_T     w2s_dtv_num[10];
        CHAR        s_atv_buf[32];
        CHAR        s_dtv_buf[32];

        /* ATV Channel Number & DTV Channel Number */
        c_memset(w2s_atv_num, 0, 10);
        c_memset(w2s_dtv_num, 0, 10);

        c_sprintf(s_atv_buf, "%d",  t_g_wzd.i4_atv_num);
        c_sprintf(s_dtv_buf, "%d",  t_g_wzd.i4_dtv_num);

        c_uc_ps_to_w2s(s_atv_buf, w2s_atv_num, 9);
        c_uc_ps_to_w2s(s_dtv_buf, w2s_dtv_num, 9);

        if (t_g_wzd.ui2_scanning_type != WZD_SB_SCANNING_SAT)
        {
            /* DVB-S has no analog channels */
            c_uc_w2s_strcat(w2s_str, (UTF16_T*)(L"\n"));
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_ANLG_CH));
            c_uc_w2s_strcat(w2s_str, w2s_atv_num);
        }

        if (a_cfg_ftm_is_atv_only_model() == FALSE)
        {
            #if (defined(APP_ISDB_SUPPORT) && defined(APP_ISDB_ANALOG_SUPPORT))
            if (t_g_wzd.ui2_scanning_type == WZD_SB_SCANNING_AIR)
            #endif
            {
                c_uc_w2s_strcat(w2s_str, (UTF16_T*)(L"\n"));
                c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_DIG_CH));
                c_uc_w2s_strcat(w2s_str, w2s_dtv_num);
            }
        }
    }

    /* update the description text widget */
    RET_ON_ERR (wzd_view_desc_txt_set_text (w2s_str));

    if (b_repaint)
    {
        RET_ON_ERR (wzd_view_desc_txt_repaint ());
    }

    return WZDR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _wzd_scan_txt_update
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_scan_txt_update(UINT16 ui2_dtv_num,
                                       UINT16   ui2_atv_num,
                                       BOOL     b_completed,
                                       BOOL     b_repaint)
{
    UTF16_T     w2s_str[256];
    /*INT32       i4_ret = WZDR_OK;*/
    UTF16_T     w2s_atv_num[10];
    UTF16_T     w2s_dtv_num[10];
    CHAR        s_atv_buf[32];
    CHAR        s_dtv_buf[32];
    //static UINT8 ui1_step=0;

    c_memset( w2s_str, 0, sizeof(UTF16_T)*256 );
    c_memset( w2s_atv_num, 0, sizeof(UTF16_T)*10 );
    c_memset( w2s_dtv_num, 0, sizeof(UTF16_T)*10 );
    c_memset( s_atv_buf, 0, sizeof(CHAR)*32 );
    c_memset( s_dtv_buf, 0, sizeof(CHAR)*32 );

    //c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_CH_DETECTED_01));

#if 0
    if( b_completed )
    {
        c_uc_w2s_strcpy(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_COMPLETE));
#if 0
        if( (0 == ui2_dtv_num) && (0 == ui2_atv_num) )
        {
            c_memset( w2s_str, 0, sizeof(UTF16_T)*256 );
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_NO_CH));
        }
        else
        {
            c_sprintf(s_atv_buf, "%d",  ui2_atv_num + ui2_dtv_num);
            c_uc_ps_to_w2s(s_atv_buf, w2s_atv_num, 9);
            c_uc_w2s_strcat(w2s_str, w2s_atv_num);
            c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_CH_DETECTED_04));
        }
#endif
    }
    else

    {


        c_uc_w2s_strcpy(w2s_str, WZD_TEXT(MLM_WZD_KEY_SCAN_PROGRESS));

        if(ui1_step == 0)
        {
            c_uc_w2s_strcat(w2s_str, L".");
        }
        else if(ui1_step == 1)
        {
            c_uc_w2s_strcat(w2s_str, L"..");
        }
        else
        {
            c_uc_w2s_strcat(w2s_str, L"...");
        }

        //if(b_step)
        {
            ui1_step = (ui1_step + 1) % 3;
        }
    }
#endif
        /* ATV Channel Number & DTV Channel Number */
        c_sprintf(s_atv_buf, " %d ",  ui2_atv_num);
        c_sprintf(s_dtv_buf, " %d ",  ui2_dtv_num);

        c_uc_ps_to_w2s(s_atv_buf, w2s_atv_num, 9);
        c_uc_ps_to_w2s(s_dtv_buf, w2s_dtv_num, 9);
        c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_TV_SETUP_CHANNEL_DETECTED));
        c_uc_w2s_strcat(w2s_str, w2s_dtv_num);
		c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_TV_SETUP_AND));
		c_uc_w2s_strcat(w2s_str, w2s_atv_num);
		c_uc_w2s_strcat(w2s_str, WZD_TEXT(MLM_WZD_KEY_TV_SETUP_ANALOG));

//    }

    RET_ON_ERR (wzd_view_scan_txt_set_text( w2s_str ));

    if(b_repaint)
    {
        RET_ON_ERR (wzd_view_scan_txt_repaint());
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_panel_key_is_long_press
 *
 * Description: get the panel pey is long press or not
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
BOOL wzd_panel_key_is_long_press(VOID)
{
	return t_g_wzd.b_g_is_panel_key_long_press;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_set_rf_scan_flag
 *
 * Description: Set rf scan flag
 *
 * Inputs:  b_rf_scan
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID wzd_set_rf_scan_flag(BOOL b_is_rf_scan)
{
	t_g_wzd.b_g_is_rf_scan = b_is_rf_scan;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_scan_start
 *
 * Description: The function performs the scan start and update the related widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_scan_start (VOID)
{
    UINT8   ui1_bs_src;

    if (!wzd_is_scan_active ())
    {
        DBG_INFO (("<WZD> scan start\n\r"));

        t_g_wzd.b_scanning    = TRUE;
        t_g_wzd.b_been_cancel = FALSE;

        /* perform start-scan task */
        RET_ON_ERR (a_cfg_get_tuner_type(APP_CFG_RECID_BS_SRC, & ui1_bs_src));

        switch (ui1_bs_src)
        {
        case APP_CFG_BS_SRC_CABLE:
            t_g_wzd.ui2_scanning_type = WZD_SB_SCANNING_CABLE;
            break;
        case APP_CFG_BS_SRC_SAT:
            t_g_wzd.ui2_scanning_type = WZD_SB_SCANNING_SAT;
            break;
        default:
            t_g_wzd.ui2_scanning_type = WZD_SB_SCANNING_AIR;
            break;
        }

#if defined(APP_DVBC_SUPPORT) || defined(APP_DVBS_SUPPORT)
        /* DVBC/DVBS and PAL SECAM: scan AIR & CABLE */
#else
    #ifdef APP_DVBT_SUPPORT
    #ifndef APP_TWN_SUPPORT
        /* DVBT and PAL SECAM: AIR only */
        if (t_g_wzd.ui2_scanning_type != WZD_SB_SCANNING_AIR)
        {
            return WZDR_FAIL;
        }
    #endif
    #endif
#endif

        /* clean the SVL & TSL */
#ifdef APP_SEPARATE_INP_SRC_FOR_ATV_DTV
        {
            c_svl_clean (t_g_wzd.h_air_svl);
            c_tsl_clean (t_g_wzd.h_air_tsl);
#ifndef APP_LOL_NWL_DISABLE
            c_nwl_clean (t_g_wzd.h_air_nwl);
            c_lol_clean (t_g_wzd.h_air_lol);
#endif

            c_svl_clean (t_g_wzd.h_cab_svl);
            c_tsl_clean (t_g_wzd.h_cab_tsl);
#ifndef APP_LOL_NWL_DISABLE
            c_nwl_clean (t_g_wzd.h_cab_nwl);
            c_lol_clean (t_g_wzd.h_cab_lol);
#endif

            c_svl_clean (t_g_wzd.h_sat_svl);
            c_tsl_clean (t_g_wzd.h_sat_tsl);
            c_nwl_clean (t_g_wzd.h_sat_nwl);
            c_lol_clean (t_g_wzd.h_sat_lol);
        }
#else
        if (t_g_wzd.ui2_scanning_type == WZD_SB_SCANNING_CABLE)
        {
            c_svl_clean (t_g_wzd.h_cab_svl);
            c_tsl_clean (t_g_wzd.h_cab_tsl);
#ifndef APP_LOL_NWL_DISABLE
            c_nwl_clean (t_g_wzd.h_cab_nwl);
            c_lol_clean (t_g_wzd.h_cab_lol);
#endif
        }
        else if (t_g_wzd.ui2_scanning_type == WZD_SB_SCANNING_SAT)
        {
            /* do NOT clean svl/tsl/nwl/lol when source is satllite */
        }
        else    /* WZD_SB_SCANNING_AIR */
        {
            c_svl_clean (t_g_wzd.h_air_svl);
            c_tsl_clean (t_g_wzd.h_air_tsl);
#ifndef APP_LOL_NWL_DISABLE
            c_nwl_clean (t_g_wzd.h_air_nwl);
            c_lol_clean (t_g_wzd.h_air_lol);
#endif
        }
#endif /* APP_SEPARATE_INP_SRC_FOR_ATV_DTV */

        /* stop 3rd process */
        a_tv_net_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,:resume=wizard\n");

        /* stop service context */
        RET_ON_ERR (a_tv_stop_all_svc(t_g_wzd.h_svctx, NULL_HANDLE));

        if(t_g_wzd.b_g_is_rf_scan)
    	{
	        DBG_INFO(("\n####%s(%d)RF SCAN\n",__FUNCTION__,__LINE__));
	        RET_ON_ERR (wzd_page_tv_setup_rf_scan_start());
    	}
		else
		{
			DBG_INFO(("\n####%s(%d)NOT RF SCAN\n",__FUNCTION__,__LINE__));
			RET_ON_ERR (wzd_util_scan_start (t_g_wzd.ui2_scanning_type));
		}

        /* Broadcast the scan avctive message */
        DBG_INFO (("<WZD> Broadcast the scan avtive message. [START]\r\n"));
        a_amb_channel_scan_active(TRUE);

        /* reset related scan config */
        t_g_wzd.b_svl_dirty   = TRUE;
        t_g_wzd.i4_atv_num    = 0;
        t_g_wzd.i4_dtv_num    = 0;

        /* enable the animation scan timer */
        SHOW_ON_ERR (c_timer_start(t_g_wzd.h_timer_scan,
                                   1000,
                                   X_TIMER_FLAG_REPEAT,
                                   _wzd_nfy_scan_timer,
                                   NULL));

        /* hide setting list */
        SHOW_ON_ERR (wzd_view_seti_lst_set_visibility(FALSE));

        /* disable control keys of setting list */
        SHOW_ON_ERR (wzd_view_seti_lst_enable_control_key (FALSE));

        /* reset scan progress bar */
        SHOW_ON_ERR (wzd_view_scan_bar_set_pos (0));

        /* updated to display scanning help list */
        SHOW_ON_ERR (_wzd_scan_help_lst_update (FALSE, FALSE));

        /* Update scan status */
        SHOW_ON_ERR (_wzd_scan_txt_update( 0, 0, FALSE, FALSE ));

        /* repaint */
        SHOW_ON_ERR (wzd_view_main_frm_repaint());
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_scan_progress
 *
 * Description: The function updates the scanning status and the related widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_scan_progress (SB_NFY_MSG_T*      pt_sb_nfy)
{
    if (!pt_sb_nfy)
    {
        return WZDR_INV_ARG ;
    }

    /* update the page if the wizard is still alive and scanning is active. */
    if (wzd_is_show () &&
        wzd_is_scan_active ())
    {
        t_g_wzd.i4_atv_num = pt_sb_nfy->i4_atv_ch_num;
        t_g_wzd.i4_dtv_num = pt_sb_nfy->i4_dtv_ch_num;

        /* update the scanning description text */
        //if (pt_sb_nfy->b_paint_info)
        {
            /* Update scan status */
            SHOW_ON_ERR (_wzd_scan_txt_update( t_g_wzd.i4_dtv_num, t_g_wzd.i4_atv_num, FALSE, FALSE ));
        }

        /* set scan progress bar */
        SHOW_ON_ERR (wzd_view_scan_bar_set_pos (pt_sb_nfy->i4_progress));
        SHOW_ON_ERR (wzd_view_scan_bar_repaint ());
        SHOW_ON_ERR (wzd_view_scan_txt_repaint());

        DBG_INFO (("<WZD> scan progress. [ATV CH: %d] [DTV CH: %d] [PROGRESS: %d]\n\r",
                        t_g_wzd.i4_atv_num, t_g_wzd.i4_dtv_num, pt_sb_nfy->i4_progress));
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_scan_end
 *
 * Description: The function performs the scan stop and update the related widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_scan_end (VOID)
{
    BOOL    b_next_page     = FALSE;
/* DTV00139009	When support DVB-C, after scan complete, should goto the last page directly.  <Brooke  090811>  */
#ifdef APP_DVBC_SUPPORT
    BOOL    b_last_page = FALSE;
#endif

    UINT8   ui1_page_idx    = 0 ;
    UINT16  ui2_scan_status = 0;

	if(t_g_wzd.b_g_is_rf_scan)
	{
		ui2_scan_status = wzd_page_tv_setup_get_scan_status();
	}
	else
	{
		ui2_scan_status = wzd_util_get_scan_status();
	}

    a_cfg_ch_lst_store(); //willy 20110305 fix issue 47813 channel list was cleaned after do Factory Default then AC off/on
    if (t_g_wzd.b_scanning == FALSE)
    {
        return WZDR_OK;
    }
#ifdef APP_DVBT_SUPPORT
    if(WZDR_OK != wzd_get_nwl_info())
    {
        c_dbg_stmt("call wzd_get_nwl_info return fail!\n");
    }
#endif

	if(t_g_wzd.b_g_is_rf_scan)
	{
		/*For RF scan*/
		wzd_page_tv_setup_scan_cancel();
	}
	else
	{
		/* clear all related-scan data and task */
		wzd_util_scan_cancel (t_g_wzd.ui2_scanning_type);
	}

    /* Broadcast the scan avctive message */
    DBG_INFO (("<WZD> Broadcast the scan avtive message. [STOP]\r\n"));
    a_amb_channel_scan_active(FALSE);

    /* disable the animation timer */
    SHOW_ON_ERR (c_timer_stop(t_g_wzd.h_timer_scan));

    /* update channel scan status */
    if (WZD_SB_STATUS_COMPLETE == ui2_scan_status)
    {
        a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_COMPLETED_SCAN);
    }
    else
    {
        a_cfg_cust_set_crnt_ch_scan_status(ACFG_CUST_PARTIAL_SCAN);
    }

    /* update the page if the wizard is still alive. */
    if (wzd_is_show () &&
        wzd_is_scan_active ())
    {
        DBG_INFO (("<WZD> scan stop\n\r"));

        /* display the scanning description text */
        if (ui2_scan_status == WZD_SB_STATUS_COMPLETE)
        {
/* DTV00139009	When support DVB-C, after scan complete, should goto the last page directly.  <Brooke  090811>  */
#ifdef APP_DVBC_SUPPORT
            b_last_page = TRUE;
#else
            b_next_page = FALSE;
#endif
            /* set scan progress bar */
            SHOW_ON_ERR (wzd_view_scan_bar_set_pos (100));
            SHOW_ON_ERR (wzd_view_scan_bar_repaint ());
            SHOW_ON_ERR (_wzd_scan_txt_update( t_g_wzd.i4_dtv_num, t_g_wzd.i4_atv_num, TRUE, FALSE ));
        }
        else if (ui2_scan_status == WZD_SB_STATUS_CANCEL)
        {
        	/* when exit wizard scan ,status bar should be full */
			SHOW_ON_ERR (wzd_view_scan_bar_set_pos (100));
			SHOW_ON_ERR (wzd_view_scan_bar_repaint ());
            SHOW_ON_ERR (_wzd_scan_txt_update( t_g_wzd.i4_dtv_num, t_g_wzd.i4_atv_num, TRUE, FALSE ));
        }
        else /* WZD_SB_STATUS_ERROR & Unknown Errors */
        {
            SHOW_ON_ERR (_wzd_scan_txt_update( t_g_wzd.i4_dtv_num, t_g_wzd.i4_atv_num, TRUE, FALSE ));
        }

        if (b_next_page)
        {
            /* Go to the next page automatically in 2 seconds */
            c_thread_delay ((UINT32) 1000);
#ifdef APP_DVBT_SUPPORT
            /*if the selected country is Norway and the network number is more than 1,goto
          next (network list) page*/
            if(TRUE == wzd_is_nwl_page_show_able())
            {
                RET_ON_ERR (_wzd_get_next_page (t_g_wzd.ui1_page_idx ,&ui1_page_idx));
            }
            else
            {
            RET_ON_ERR (_wzd_get_next_page (t_g_wzd.ui1_page_idx ,&ui1_page_idx)) ;
                RET_ON_ERR (_wzd_get_next_page (ui1_page_idx ,&ui1_page_idx)) ;
            }
#else
            RET_ON_ERR (_wzd_get_next_page (t_g_wzd.ui1_page_idx ,&ui1_page_idx)) ;
#endif
            SHOW_ON_ERR (_wzd_show_update (ui1_page_idx, TRUE));
        }
/* DTV00139009	When support DVB-C, after scan complete, should goto the last page directly.  <Brooke  090811>  */
#ifdef APP_DVBC_SUPPORT
        else if(b_last_page)
        {
            /* Go to the next page automatically in 2 seconds */
            c_thread_delay ((UINT32) 1000);
            RET_ON_ERR (_wzd_show_update ((UINT8)(t_g_wzd.ui1_page_num - 1), TRUE));
        }
#endif
        else
        {
            /* repaint */
            SHOW_ON_ERR (wzd_view_main_frm_repaint());
        }

        /* Notify tv setup page that scan is complete. Can be improved. */
        wzd_page_tv_setup_on_scan_complete( t_g_wzd.i4_dtv_num + t_g_wzd.i4_atv_num );
    }

    /* turn off the scanning flag */
    t_g_wzd.b_scanning    = FALSE;
    t_g_wzd.b_been_cancel = FALSE;

#if 0
    /* unmute */
    if (b_g_is_mute == FALSE)
    {
        a_tv_set_mute (FALSE);
    }
	b_g_is_vol_key_enable = TRUE;
#endif

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_set_status
 *
 * Description: The function sets the wizard status into ACFG.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_set_status (VOID)
{
    WZD_PAGE_INFO_T*    pt_page;

#ifdef APP_RETAIL_MODE_SUPPORT
    ACFG_RETAIL_MODE_T  t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
#endif

    if (DLIST_IS_EMPTY (& t_g_wzd.t_page_lst))
    {
        return WZDR_FAIL;
    }

    /* get last entry */
    pt_page = DLIST_TAIL (& t_g_wzd.t_page_lst);

    if (a_cfg_custom_get_wifi_remote_support())
    {
        if (t_g_wzd.ui1_page_idx == pt_page->ui1_page_idx)
        {   /* the latest page is the last page */
            t_g_wzd.ui1_state = WZD_STATE_COMPLETE;
        }
        else if(( WZD_STATE_RESUME == t_g_wzd.ui1_state ) ||
                ( WZD_STATE_RESUME_WIFI_RC_PARING== t_g_wzd.ui1_state ))
        {
            /* device setup and tv setup page are special page, they can jump each other */
            if ((t_g_wzd.ui1_page_idx == WZD_PAGE_TV_REMOTE_DEVICE_SETUP)
                || (t_g_wzd.ui1_page_idx == WZD_PAGE_INDEX_TV_SETUP)
                || (t_g_wzd.ui1_page_idx == WZD_PAGE_TV_NAME_INPUT))
            {
                /* do nothing */
            }
            else
            {
                /* Wizard is resumed from other APP (Menu.) */
                /* When leaving wizard, set the status to complete and set the page index to last index. */
                t_g_wzd.ui1_page_idx = pt_page->ui1_page_idx;
                t_g_wzd.ui1_state = WZD_STATE_COMPLETE;
            }
        }
        else
        {
    #ifdef APP_RETAIL_MODE_SUPPORT
            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
                t_g_wzd.ui1_state = WZD_STATE_FIRST_PAGE;
            }
            else
	#endif
            {
                /* If current page is not the last page, resume next power on. */
                t_g_wzd.ui1_state = WZD_STATE_START_SETUP;
            }
        }
    }
    else
    {
        if (t_g_wzd.ui1_page_idx == pt_page->ui1_page_idx)
        {   /* the latest page is the last page */
            t_g_wzd.ui1_state = WZD_STATE_COMPLETE;
        }
        else if( WZD_STATE_RESUME == t_g_wzd.ui1_state )
        {
            /* device setup and tv setup page are special page, they can jump each other */
            if ((t_g_wzd.ui1_page_idx == WZD_PAGE_INDEX_TV_SETUP)
                || (t_g_wzd.ui1_page_idx == WZD_PAGE_TV_NAME_INPUT))
            {
                /* do nothing */
            }
            else
            {
                /* Wizard is resumed from other APP (Menu.) */
                /* When leaving wizard, set the status to complete and set the page index to last index. */
                t_g_wzd.ui1_page_idx = pt_page->ui1_page_idx;
                t_g_wzd.ui1_state = WZD_STATE_COMPLETE;
            }
        }
        else
        {
    #ifdef APP_RETAIL_MODE_SUPPORT
            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
            {
                t_g_wzd.ui1_state = WZD_STATE_FIRST_PAGE;
            }
            else
	#endif
            {
                /* If current page is not the last page, resume next power on. */
                t_g_wzd.ui1_state = WZD_STATE_START_SETUP;
            }
        }
    }

    RET_ON_ERR (wzd_custom_set_status (& t_g_wzd.ui1_state, & t_g_wzd.ui1_page_idx));

    DBG_INFO (("<WZD> set wizard status [state = %d] [page = %d]\n\r", t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx));

    RET_ON_ERR (a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx)));

    t_g_wzd.b_cfg_dirty = TRUE;

    return WZDR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _wzd_get_status
 *
 * Description: The function gets the wizard status from ACFG.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_get_status (VOID)
{
    UINT16  ui2_status;

    RET_ON_ERR (a_cfg_get_wzd_status (& ui2_status));

    if (ui2_status == APP_CFG_WZD_STATUS_INIT)
    {
        t_g_wzd.ui1_state    = WZD_STATE_START_SETUP;
        t_g_wzd.ui1_page_idx = 0;
    }
    else if ((ui2_status == APP_CFG_WZD_STATUS_WIFI_UNPAIR)&& a_cfg_custom_get_wifi_remote_support())
    {
        t_g_wzd.ui1_page_idx = WZD_PAGE_INDEX_WIFI_REMOTE_PARING;
        t_g_wzd.ui1_state    = WZD_STATE_RESUME_WIFI_RC_PARING;
        t_g_wzd.ui1_end_idx  = WZD_STATE_RESUME_WIFI_RC_PARING;
    }
    else
    {
        t_g_wzd.ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
        t_g_wzd.ui1_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);

        if ((ui2_status & WZD_STATE_RESUME) &&
            (ui2_status & WZD_STATE_FIRST_PAGE))
        {
            t_g_wzd.ui1_page_idx = 0;
        }
    }

    RET_ON_ERR (wzd_custom_get_status (& t_g_wzd.ui1_state, & t_g_wzd.ui1_page_idx));

    DBG_INFO (("<WZD> get wizard status [state = %d] [page = %d]\n\r", t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_store_svl_and_config
 *
 * Description: The function stores the config and svls.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_store_svl_and_config (VOID)
{
    /* Store the config */
    if (t_g_wzd.b_cfg_dirty)
    {
        DBG_INFO(("<WZD> Begin storing config\n\r"));
        if (a_cfg_store() != APP_CFGR_OK)
        {
            DBG_INFO(("<WZD> Can't store config.\n\r"));
        }
        else
        {
            DBG_INFO(("<WZD> End storing config\n\r"));
        }
    }

    t_g_wzd.b_cfg_dirty = FALSE;

    /* Store the SVL, TSL, NWL, LOL */
    if (t_g_wzd.b_svl_dirty)
    {
        DBG_INFO(("<WZD> Begin storing SVL, TSL, NWL, LOL.\n\r"));
        if (a_cfg_ch_lst_store() != APP_CFGR_OK)
        {
            DBG_INFO(("<WZD> Can't store SVL, TSL, NWL, LOL.\n\r"));
        }
        else
        {
            DBG_INFO(("<WZD> End storing SVL, TSL, NWL, LOL.\n\r"));
        }
    }
    t_g_wzd.b_svl_dirty = FALSE;

    return WZDR_OK;
}

#ifndef APP_C4TV_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _wzd_enable_tv_src
 *
 * Description: The function enable/disable the TV source.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_enable_tv_src (BOOL   b_enable)
{
    UINT8      ui1_idx;
    UINT8      ui1_rec_num;
    ISL_REC_T  t_isl_rec;

    /* get record number */
    RET_ON_ERR (a_isl_get_num_rec (& ui1_rec_num));

    /* iterate */
    for (ui1_idx = 0 ; ui1_idx < ui1_rec_num ; ui1_idx++)
    {
        RET_ON_ERR (a_isl_get_rec_by_idx (ui1_idx, & t_isl_rec));

        if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
        {
            if (b_enable)
            {
                a_cfg_get_input_src_skip (t_isl_rec.ui1_id, & t_g_wzd.b_tv_skip);
                a_cfg_get_input_src_block (t_isl_rec.ui1_id, & t_g_wzd.b_tv_block);

                a_cfg_set_input_src_skip (t_isl_rec.ui1_id, FALSE);
                a_cfg_set_input_src_block (t_isl_rec.ui1_id, FALSE);

                a_cfg_update_input_src_attr ();
            }
            else
            {
                a_cfg_set_input_src_skip (t_isl_rec.ui1_id, t_g_wzd.b_tv_skip);
                a_cfg_set_input_src_block (t_isl_rec.ui1_id, t_g_wzd.b_tv_block);

                a_cfg_update_input_src_attr ();
            }

            t_g_wzd.b_cfg_dirty = TRUE;
            break;
        }
    }

    return WZDR_OK;
}
#endif

#if 0
static INT32 _wzd_reset_lightsensor_and_backlight(VOID)
{
    UINT8           ui1_dcr_def;

    a_cfg_get_dcr_def_value(&ui1_dcr_def);

    /*set backlight control to default*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), (INT16)ui1_dcr_def);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));


    /*set light sensor to default*/
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), (INT16)2);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));

/*Do it in wzd_custom_pause*/
    /*set smart dimming to default*/
    acfg_set_default(IDX_CUSTOM_DIMMING);
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));


    return WZDR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name: wzd_footer_data_change
 *
 * Description: The API sends footer data change message to current page.
 *
 * Inputs:  ui4_msg            Message type.
 *          pv_param1
 *          pv_param2
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_footer_data_change (UINT32    ui4_msg,
                        VOID*    pv_param1,
                        VOID*    pv_param2)
{
    WZD_PAGE_INFO_T*    pt_page = NULL;

    RET_ON_ERR (_wzd_page_lst_get_page_entry (t_g_wzd.ui1_page_idx, & pt_page));
    if( NULL != pt_page->pt_page_data->pf_footer_data_change )
    {
        pt_page->pt_page_data->pf_footer_data_change( ui4_msg, pv_param1, pv_param2 );
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_app_send_msg
 *
 * Description: The API sends a message to Wizard's message queue.
 *
 * Inputs:  ui4_type            Message type.
 *          pv_msg              Message data.
 *          z_msg_len           The length of message data.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_app_send_msg (UINT32         ui4_type,
                        const VOID*    pv_msg,
                        SIZE_T         z_msg_len)
{
    INT32    i4_rc;

    /* send a message to Wizard's message queue */
    i4_rc = c_app_send_msg (t_g_wzd.h_wzd,
                            ui4_type,
                            pv_msg,
                            z_msg_len,
                            _wzd_app_nfy_fct,
                            NULL);

    if (i4_rc != AEER_OK)
    {
        DBG_ERROR (("<WZD> ERR: send message = %d failed = %d\n\r", ui4_type, i4_rc));
    }

    return (i4_rc == AEER_OK) ? WZDR_OK : WZDR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_init
 *
 * Description: This API performs the registration for the Wizard
 *              application.
 *
 * Inputs:  pt_reg       References the registration structure.
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID a_wzd_init (AMB_REGISTER_INFO_T*    pt_reg)
{
    APP_DESC_T  t_wzd_desc = {
                    ~((UINT64)0),   /* ui8_flags */
                    {
                        8 * 1024,   /* z_stack_size */
                        200,        /* ui1_priority */
                        16          /* ui2_num_msgs */
                    },
                    0,              /* ui4_app_group_id */
                    0,              /* ui4_app_id */
                    {
                        16 * 1024,  /* z_min_memory */
                        16 * 1024,  /* z_max_memory */
                        0,          /* ui8_max_files_size */
                        0,          /* ui2_max_files */
                        256,        /* ui2_max_handles */
                        1,          /* ui2_max_threads */
                        2,          /* ui2_max_semaphores */
                        1,          /* ui2_max_msg_queues */
                        64,         /* ui2_max_nb_msgs */
                        64          /* ui2_max_msg_size */
                    },
                    64,             /* ui2_msg_count */
                    64              /* ui2_max_msg_size */
                };

    /* fill registration information */
    c_strcpy (pt_reg->s_name, WZD_NAME);

    /* lifecycle callback functions */
    pt_reg->t_fct_tbl.pf_init        = _wzd_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit        = _wzd_app_exit_fct;
    pt_reg->t_fct_tbl.pf_pause       = _wzd_app_pause_fct;
    pt_reg->t_fct_tbl.pf_resume      = _wzd_app_resume_fct;
    pt_reg->t_fct_tbl.pf_process_msg = _wzd_app_process_msg_fct;

    /* Power sequence callback function */
    pt_reg->pf_power_seq_cb         =  _wzd_app_power_seq_cb;

    /* System key callback */
    pt_reg->pf_system_key_cb        = _wzd_app_system_key_cb;

    /* descriptor */
    pt_reg->t_desc                   = t_wzd_desc;

    /* system keys */
    pt_reg->ui2_key_num              = 0;
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_send_sim_key
 *
 * Description: This API sends a pseudo key to Wizard.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID a_wzd_send_sim_key (UINT32  ui4_key_code)
{
    if (! t_g_wzd.b_pause) /* not in paused mode */
    {
        /* a pseudo call back to the notification of widget */
        _wzd_nfy_wgl (WGL_MSG_KEY_DOWN, (VOID*) ui4_key_code, NULL);
    }
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_is_resume
 *
 * Description: This API checks whether or not resuming the wizard.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
BOOL a_wzd_is_resume (VOID)
{
    BOOL                    b_resume    = FALSE;
    UINT16                  ui2_status  = APP_CFG_WZD_STATUS_INIT;
    UINT16                  ui2_real_status = APP_CFG_WZD_STATUS_INIT;
#ifdef APP_C4TV_SUPPORT
    UINT8                   ui1_page_index = 0;
#endif

    if (a_app_cust_fac())
    {
        UINT32                  ui4_model_idx = 0;
        UINT8                   ui1_mode = 0;

        a_cfg_get_factory_mode(&ui1_mode);
        a_cfg_custom_get_model_idx(&ui4_model_idx);

        DBG_LOG_PRINT(("[WZD] %s() %d: burning mode=0x%x, ui4_model_idx=%u\n",__FUNCTION__, __LINE__, ui1_mode, ui4_model_idx));
        if (0 == ui4_model_idx)
        {
            /* First boot up for facotry, and no eep init
             *  skip oobe to power on directly + turn on burning mode
             */
            DBG_LOG_PRINT(("<WZD> eep not init, skip power on with wzd.\n"));
            a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
            a_cfg_set_factory_mode(APP_CFG_FAC_MODE_BURNING);

            return b_resume;
        }
        else if (APP_CFG_FAC_MODE_BURNING_MASK&ui1_mode)
        {
            DBG_LOG_PRINT(("<WZD> burning mode is on, skip power on with wzd.\n"));
            a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
            return b_resume;
        }
    }
    if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK)
    {
        ui2_real_status = WZD_UTIL_GET_STATUS_STATE( ui2_status );

#ifdef APP_C4TV_SUPPORT
        ui1_page_index  = WZD_UTIL_GET_STATUS_IDX  ( ui2_status );
        DBG_LOG_PRINT(( "[WZD][a_wzd_is_resume] ui2_status= %d, ui2_real_status= %d, ui1_page_index=%d\n",
                        ui2_status, ui2_real_status,  ui1_page_index));
#endif

        if (ui2_real_status == APP_CFG_WZD_STATUS_INIT ||
            ui2_real_status  & WZD_STATE_START_SETUP
#ifdef APP_C4TV_SUPPORT
            || ((ui2_real_status == (UINT16)WZD_STATE_RESUME_C4TV) &&
                (ui1_page_index >= WZD_PAGE_INDEX_C4TV_START_OOBE) &&
                (ui1_page_index <= WZD_PAGE_INDEX_C4TV_END) &&
                ui1_page_index != WZD_PAGE_INDEX_C4TV_STORE_DEMO)
#endif
           )
        {
            b_resume = TRUE;

#ifdef APP_C4TV_SUPPORT
            if (ui2_real_status == APP_CFG_WZD_STATUS_INIT ||
                ui2_real_status  & WZD_STATE_START_SETUP)
            {
                DBG_LOG_PRINT(("[WZD] %s() %d: Cast TV, set to be WZD_PAGE_INDEX_C4TV_START_OOBE.\n\r", __FUNCTION__, __LINE__));
                a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_START_OOBE));
            }
#endif
        }
    }

    DBG_LOG_PRINT(("[WZD] %s() %d: b_resume=%d.\n\r", __FUNCTION__, __LINE__, (INT32)b_resume));

    return b_resume;
}

/*-----------------------------------------------------------------------------
 * Name: a_wzd_is_show
 *
 * Description: The function checks if the Wizard is paused or not.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                   The wizard is shown.
 *          FALSE                  The wizard is paused.
 ----------------------------------------------------------------------------*/
BOOL a_wzd_is_show (VOID)
{
    return wzd_is_show();
}

/*-----------------------------------------------------------------------------
 * Name: wzd_get_lang_id
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
UINT16 wzd_get_lang_id (VOID)
{
    return ((t_g_wzd.ui2_lang_id >= MLM_WZD_NUM_LANG) ? (0) : (t_g_wzd.ui2_lang_id));
}

/*-----------------------------------------------------------------------------
 * Name: wzd_get_validate_key
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
UINT16 wzd_get_validate_key (UINT16 ui2_key)
{
    return ((ui2_key >= MLM_WZD_NUM_KEY) ? ((UINT16)MLM_WZD_KEY_EMPTY) : (ui2_key)) ;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_is_show
 *
 * Description: The function checks if the Wizard is paused or not.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                   The wizard is shown.
 *          FALSE                  The wizard is paused.
 ----------------------------------------------------------------------------*/
BOOL wzd_is_show (VOID)
{
    return  (!t_g_wzd.b_pause);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_is_scan_active
 *
 * Description: The function checks if the Wizard performs scanning or not.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                   Scanning.
 *          FALSE                  No scanning.
 ----------------------------------------------------------------------------*/
BOOL wzd_is_scan_active (VOID)
{
    return  (t_g_wzd.b_scanning);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_set_mute_status
 *
 * Description: set wzd to mute flag
 *
 * Inputs:  b_vol_key_enable		set wzd to mute flag
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID wzd_set_mute_status(BOOL b_mute)
{
	b_g_is_mute = b_mute;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_get_mute_status
 *
 * Description: get wzd mute flag
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: BOOL    wzd mute flag
 *
 ----------------------------------------------------------------------------*/
BOOL wzd_get_mute_status(VOID)
{
	return b_g_is_mute;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_set_startup_first_time
 *
 * Description: wzd start up first time flag
 *
 * Inputs:  b_1st_time		set wzd first time flag
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID wzd_set_startup_first_time(BOOL b_1st_time)
{
	b_g_is_wzd_startup_first_time = b_1st_time;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_get_startup_first_time
 *
 * Description: get wzd start up first time flag
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: BOOL    wzd mute flag
 *
 ----------------------------------------------------------------------------*/
BOOL wzd_get_startup_first_time(VOID)
{
	return b_g_is_wzd_startup_first_time;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_set_power_off_flag
 *
 * Description: set vol key flag to enable
 *
 * Inputs:  b_vol_key_enable		set vol key flag to enable
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID wzd_enable_vol_key(BOOL b_vol_key_enable)
{
    t_g_wzd.b_g_is_vol_key_enable = b_vol_key_enable;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_set_power_off_flag
 *
 * Description: Set show power off warning dialog flag
 *
 * Inputs:  b_show		Need show power off warning dialog
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID wzd_set_power_off_flag(BOOL b_show)
{
	b_g_is_need_power_off_dlg_show = b_show;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_get_crnt_svctx
 *
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
HANDLE_T wzd_get_crnt_svctx (VOID)
{
    return  (t_g_wzd.h_svctx);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_get_crnt_svl
 *
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
HANDLE_T wzd_get_crnt_svl (VOID)
{
    INT32   i4_ret;
    UINT16  ui2_svl_id;

    i4_ret = a_cfg_get_tuner_sync_src (& ui2_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        return NULL_HANDLE;
    }

    if      (ui2_svl_id == LST_CAB_SVL_ID) { return t_g_wzd.h_cab_svl; }
    else if (ui2_svl_id == LST_SAT_SVL_ID) { return t_g_wzd.h_sat_svl; }

    /* default: air svl handle */
    return t_g_wzd.h_air_svl;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_get_crnt_tsl
 *
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
HANDLE_T wzd_get_crnt_tsl (VOID)
{
    INT32   i4_ret;
    UINT16  ui2_svl_id;

    i4_ret = a_cfg_get_tuner_sync_src (& ui2_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        return NULL_HANDLE;
    }

    if      (ui2_svl_id == LST_CAB_TSL_ID) { return t_g_wzd.h_cab_tsl; }
    else if (ui2_svl_id == LST_SAT_TSL_ID) { return t_g_wzd.h_sat_tsl; }

    /* default: air tsl handle */
    return t_g_wzd.h_air_tsl;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_lst_add_page
 *
 * Description: This API is called to customize the page list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32  wzd_page_lst_add_page(
    WZD_PAGE_INFO_DATA_T*       pt_page_data,
    wzd_page_nfy                pf_nfy_sel
    )
{
    DBG_INFO (("<WZD> add %d-th page list entry\n\r", t_g_wzd.ui1_page_num));

    WZD_PAGE_INFO_T*            pt_tmp_page = NULL ;
    WZD_PAGE_INFO_DATA_T*       pt_tmp_page_data = NULL ;

    if (pt_page_data == NULL || pf_nfy_sel == NULL)
    {
        return WZDR_INV_ARG;
    }

    /* if the item is 'page' type ,it should provide 4 call back functon for wizard */
    if (WZD_PAGE_TYPE_CUST_PAGE == pt_page_data->t_page_type)
    {
        if (NULL == pt_page_data->t_cust_page_fct_tab.pf_wzd_cust_page_create
            ||
            NULL == pt_page_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory
            ||
            NULL == pt_page_data->t_cust_page_fct_tab.pf_wzd_cust_page_show
            ||
            NULL == pt_page_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide)
        {
            return WZDR_INV_ARG ;
        }
    }

    /* allocate an page entry */
    pt_tmp_page_data = (WZD_PAGE_INFO_DATA_T*) c_mem_alloc (sizeof (WZD_PAGE_INFO_DATA_T)) ;
    pt_tmp_page = (WZD_PAGE_INFO_T*) c_mem_alloc (sizeof (WZD_PAGE_INFO_T));

    if (!pt_tmp_page || !pt_tmp_page_data)
    {
        if (pt_tmp_page)
        {
            c_mem_free (pt_tmp_page);
        }
        if (pt_tmp_page_data)
        {
            c_mem_free (pt_tmp_page_data);
        }
        DBG_ERROR (("<WZD> ERR: out of memory\n\r"));
        return  WZDR_OUT_OF_MEM;
    }

    /* reset entry */
    c_memset (pt_tmp_page, 0, sizeof(WZD_PAGE_INFO_T));

    /* record the page data to local */
    c_memcpy (pt_tmp_page_data ,pt_page_data ,sizeof(WZD_PAGE_INFO_DATA_T)) ;

    /* set page info */
    pt_tmp_page->ui1_page_idx = t_g_wzd.ui1_page_num;
    pt_tmp_page->pt_page_data = pt_tmp_page_data ;
    pt_tmp_page->ui2_sel_idx  = 0;
    pt_tmp_page->pf_nfy_sel   = pf_nfy_sel;
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
    pt_tmp_page->ui8_code_num = CODE_NUM_INVALID;
#endif

    /* insert the page entry to the tail of Wizard page list */
    DLIST_INSERT_TAIL (pt_tmp_page, & t_g_wzd.t_page_lst, t_page_link);

    /* if the add item is 'page' type ,init this page */
    if (WZD_PAGE_TYPE_CUST_PAGE == pt_page_data->t_page_type)
    {
        RET_ON_ERR (pt_page_data->t_cust_page_fct_tab.pf_wzd_cust_page_create()) ;
    }

    /* increase the number of page list counter */
    t_g_wzd.ui1_page_num++;

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_set_gui_lang
 *
 * Description: The function handles the condition when the gui language is
 *              updated.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_set_gui_lang (ISO_639_LANG_T s639_lang)
{
#ifdef APP_MLM_S639_TO_LANGIDX_SUPPORT
    t_g_wzd.ui2_lang_id = mlm_wzd_s639_to_langidx (s639_lang);
#else
    if (c_strcmp (s639_lang, s639_app_cfg_lang_eng) == 0)
    {
        DBG_INFO (("<WZD> set language to English\n\r"));
        t_g_wzd.ui2_lang_id = 0;
    }
    else if (c_strcmp (s639_lang, s639_app_cfg_lang_spa) == 0 ||
             c_strcmp (s639_lang, s639_app_cfg_lang_esl) == 0)
    {
        DBG_INFO (("<WZD> set language to Spanish\n\r"));
        t_g_wzd.ui2_lang_id = 2;
    }
    else if (c_strcmp (s639_lang, s639_app_cfg_lang_fre) == 0 ||
             c_strcmp (s639_lang, s639_app_cfg_lang_fra) == 0)
    {
        DBG_INFO (("<WZD> set language to French\n\r"));
        t_g_wzd.ui2_lang_id = 1;
    }

#ifdef APP_DVBC_SUPPORT
    else if (c_strcmp (s639_lang, s639_app_cfg_lang_ger) == 0)
    {
        DBG_INFO (("<WZD> set language to Germany\n\r"));
        t_g_wzd.ui2_lang_id = 3;
    }
    else if (c_strcmp (s639_lang, s639_app_cfg_lang_ita) == 0)
    {
        DBG_INFO (("<WZD> set language to Italy\n\r"));
        t_g_wzd.ui2_lang_id = 4;
    }
    else if (c_strcmp (s639_lang, s639_app_cfg_lang_chi) == 0)
    {
        DBG_INFO (("<WZD> set language to Chinese\n\r"));
        t_g_wzd.ui2_lang_id = 5;
    }
#else
#ifdef APP_DVBT_SUPPORT
    else if (c_strcmp (s639_lang, s639_app_cfg_lang_ger) == 0)
    {
        DBG_INFO (("<WZD> set language to Germany\n\r"));
        t_g_wzd.ui2_lang_id = 3;
    }
    else if (c_strcmp (s639_lang, s639_app_cfg_lang_ita) == 0)
    {
        DBG_INFO (("<WZD> set language to Italy\n\r"));
        t_g_wzd.ui2_lang_id = 4;
    }
    else if (c_strcmp (s639_lang, s639_app_cfg_lang_chi) == 0)
    {
        DBG_INFO (("<WZD> set language to Chinese\n\r"));
        t_g_wzd.ui2_lang_id = 5;
    }
#endif
#endif /* APP_DVBC_SUPPORT */
#endif
    return  0;
}

#ifdef APP_ACI_SUPPORT
/*----------------------------------------------------------------------------
 * Name: wzd_set_desc_txt
 *
 * Description: This API is called to customize the page list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 wzd_set_desc_txt
(
    UINT16 ui2_txt_key,
    BOOL   b_step,
    BOOL   b_repaint
)
{
    //return _wzd_scan_desc_txt_update(ui2_txt_key,b_step,b_repaint);
    return 0;
}
#endif

#ifdef APP_DVBT_SUPPORT
/*----------------------------------------------------------------------------
 * Name: wzd_get_nwl_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 wzd_get_nwl_info(VOID)
{
    UINT16                ui2_num_rec = 0;
    UINT32                ui4_ver_id;
    INT32                  i4_pos;
    INT32                  i4_i;
    NWL_REC_T         t_nwl_rec;
    UINT16                ui2_rec_id;
    HANDLE_T            h_nwl_hdl = NULL_HANDLE;
    UINT16 ui2_i = 0;

    c_memset((VOID*)&t_nwl_rec,0,sizeof(t_nwl_rec));
    for(i4_i = 0;i4_i < NWL_CANDIDATE_NUM_MAX;i4_i++)
    {
        t_g_wzd.aui2_nwl_candidate_id[i4_i] = 0;
    }
    t_g_wzd.ui2_nwl_num = 0;

    if (t_g_wzd.ui2_scanning_type == WZD_SB_SCANNING_CABLE)
    {
#ifndef APP_LOL_NWL_DISABLE
        h_nwl_hdl = t_g_wzd.h_cab_nwl;
#else
        h_nwl_hdl = NULL_HANDLE;
#endif
    }
    else if (t_g_wzd.ui2_scanning_type == WZD_SB_SCANNING_SAT)
    {
        h_nwl_hdl = t_g_wzd.h_sat_nwl;
    }
    else
    {
#ifndef APP_LOL_NWL_DISABLE
        h_nwl_hdl = t_g_wzd.h_air_nwl;
#else
        h_nwl_hdl = NULL_HANDLE ;
#endif
    }

    if ((c_nwl_get_num_rec(h_nwl_hdl, &ui2_num_rec, &ui4_ver_id)!=NWLR_OK)||
        (ui2_num_rec == 0))
    {
        DBG_INFO(("NWL record is NULL!\n"));
        return WZDR_OK;
    }
    i4_pos=0;
    ui2_rec_id = 1;
    while (i4_pos < ui2_num_rec)
    {
        if (c_nwl_get_rec(h_nwl_hdl, ui2_rec_id, &t_nwl_rec, &ui4_ver_id)!=NWLR_OK)
        {
            ui2_rec_id++;
            continue;
        }
        if (t_nwl_rec.ui4_nw_mask & SB_NWL_MASK_FAV_CANDIDATE)
        {
            t_g_wzd.aui2_nwl_candidate_id[t_g_wzd.ui2_nwl_num] = t_nwl_rec.ui2_nwl_rec_id;
            t_g_wzd.ui2_nwl_num++;
        }
        ui2_rec_id++;
        i4_pos++;
    }

    DBG_INFO(("Candidate Favorite Network List number: %d\n",t_g_wzd.ui2_nwl_num));
    DBG_INFO(("Candidate Favorite Network List:\n"));
    for(ui2_i = 0; ui2_i < t_g_wzd.ui2_nwl_num;ui2_i++)
    {
        DBG_INFO(("num%d: %d\n",ui2_i,t_g_wzd.aui2_nwl_candidate_id[ui2_i]));
    }

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: wzd_get_nwl_num
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
UINT16 wzd_get_nwl_num(VOID)
{
    return t_g_wzd.ui2_nwl_num;
}
/*----------------------------------------------------------------------------
* Name: wzd_get_nwl_name_text
*
* Description:
*
* Inputs:  -
*
* Outputs: -
*
* Returns: -
----------------------------------------------------------------------------*/
VOID wzd_get_nwl_name_text
(
    UINT16 ui2_idx,
    UTF16_T* w2s_str,
    SIZE_T z_len
)
{
    INT32 i4_ret = -1;
    UINT32 ui4_ver_id = 0;
    HANDLE_T h_nwl_hdl = NULL_HANDLE;
    NWL_REC_T t_nwl_rec;

    c_memset((VOID*)&t_nwl_rec,0,sizeof(t_nwl_rec));


    if (t_g_wzd.ui2_scanning_type == WZD_SB_SCANNING_CABLE)
    {
#ifndef APP_LOL_NWL_DISABLE
        h_nwl_hdl = t_g_wzd.h_cab_nwl;
#else
        h_nwl_hdl = NULL_HANDLE ;
#endif
    }
    else if (t_g_wzd.ui2_scanning_type == WZD_SB_SCANNING_SAT)
    {
        h_nwl_hdl = t_g_wzd.h_sat_nwl;
    }
    else
    {
#ifndef APP_LOL_NWL_DISABLE
        h_nwl_hdl = t_g_wzd.h_air_nwl;
#else
        h_nwl_hdl = NULL_HANDLE ;
#endif
    }

    c_dbg_stmt("In wzd_get_nwl_name_text:ui2_idx = %d\r\n",ui2_idx);
    if(c_nwl_get_rec(h_nwl_hdl,t_g_wzd.aui2_nwl_candidate_id[ui2_idx],&t_nwl_rec,&ui4_ver_id) == NWLR_OK)
    {
        if(NULL != t_nwl_rec.s_nw_name)
        {
            i4_ret = c_uc_ps_to_w2s(t_nwl_rec.s_nw_name,w2s_str,(UINT32)z_len);
            if(i4_ret != 0)
            {
                c_dbg_stmt("call c_uc_ps_to_w2s return fail:%s:%d:%d\r\n", __FILE__, __LINE__,i4_ret);
            }
        }
    }
    else
    {
        c_dbg_stmt("call c_nwl_get_rec return fail:%s:%d:%d\r\n", __FILE__, __LINE__,i4_ret);
    }

    return;
}
/*----------------------------------------------------------------------------
* Name: wzd_get_nwl_name_text
*
* Description:
*
* Inputs:  -
*
* Outputs: -
*
* Returns: -
----------------------------------------------------------------------------*/
INT32 wzd_get_fav_nwl_rec_id(UINT16* pui2_fav_rec_id)
{
    UINT16  ui2_hlt_idx;

    /* get highlighted index */
    RET_ON_ERR (wzd_view_seti_lst_get_hlt_idx (& ui2_hlt_idx));
    *pui2_fav_rec_id = t_g_wzd.aui2_nwl_candidate_id[ui2_hlt_idx];

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
* Name: wzd_is_nwl_page_show_able
*
* Description:
*
* Inputs:  -
*
* Outputs: -
*
* Returns: -
----------------------------------------------------------------------------*/
BOOL wzd_is_nwl_page_show_able(VOID)
{
    ISO_3166_COUNT_T    s3166_country;

    if(APP_CFGR_OK == a_cfg_get_country(s3166_country))
    {
        if(0 == c_strncmp(s3166_country, s3166_app_cfg_count_nor, ISO_3166_COUNT_LEN))
        {
            if(t_g_wzd.ui2_nwl_num > (UINT16)1)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

#endif

/*-----------------------------------------------------------------------------
 * Name: wzd_page_goto
 *
 * Description: -
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 wzd_page_goto( WZD_PAGE_NAVI_T e_navi )
{
    UINT8               ui1_page_idx = 0 ;

    e_g_navi = e_navi;

    if( WZD_PAGE_NAVI_FIRST_PAGE == e_navi )
    {
        RET_ON_ERR (_wzd_show_update (0, TRUE));
    }
    else if( WZD_PAGE_NAVI_LAST_PAGE == e_navi )
    {
        RET_ON_ERR (_wzd_show_update ((UINT8)(t_g_wzd.ui1_page_num - 1), TRUE));
    }
    else if( WZD_PAGE_NAVI_NEXT_PAGE == e_navi )
    {
        RET_ON_ERR (_wzd_get_next_page (t_g_wzd.ui1_page_idx ,&ui1_page_idx)) ;
        RET_ON_ERR (_wzd_show_update (ui1_page_idx, TRUE));
        RET_ON_ERR (_wzd_set_status());
    }
    else if( WZD_PAGE_NAVI_PREV_PAGE == e_navi )
    {
        RET_ON_ERR (_wzd_get_prev_page (t_g_wzd.ui1_page_idx ,&ui1_page_idx)) ;
        RET_ON_ERR (_wzd_show_update (ui1_page_idx, TRUE));
        RET_ON_ERR (_wzd_set_status());
    }
	else if(WZD_PAGE_NAVI_LAST_FINISHED_PAGE == e_navi)
	{
		WZD_PAGE_INFO_T*	pt_page;

		pt_page = DLIST_TAIL (& t_g_wzd.t_page_lst);
		t_g_wzd.ui1_page_idx = pt_page->ui1_page_idx;
		/*WZD_PAGE_INDEX_COMPLETE*/
        RET_ON_ERR (_wzd_show_update (t_g_wzd.ui1_page_idx, TRUE));
        RET_ON_ERR (_wzd_set_status());
	}
	else if( WZD_PAGE_NAVI_LAST_VALID_ITEM == e_navi )
	{
		WZD_PAGE_INFO_T*	pt_page;

		if (DLIST_IS_EMPTY (& t_g_wzd.t_page_lst))
		{
			return WZDR_FAIL;
		}
		/* Set last entry */
		pt_page = DLIST_TAIL (& t_g_wzd.t_page_lst);
		t_g_wzd.ui1_page_idx = pt_page->ui1_page_idx;
        a_cfg_get_spdif_type(&e_g_spdif_value);
        a_cfg_set_spdif_type(e_g_spdif_value);
		a_wzd_exit();   /*Exit wizard*/
	}

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_async_invoke
 *
 * Description:
 *
 * Inputs:
 *      menu_async_func - The asynchronous function to call
 *      pv_data - The data of the the callback function. This parameter could be
 *                NULL, which is used to send NO data.
 *      z_data_len - The data length of pv_data. If the pv_data is NULL,
 *                   the z_data_len is ignored and the actual data len will be
 *                   zero.
 *      b_retry - Retry or not if message queue is full
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 wzd_async_invoke(wzd_async_func   pf_async_func,
                       VOID*            pv_data,
                       SIZE_T           z_data_len,
                       BOOL             b_retry)
{
    INT32                   i4_ret;
    WZD_MSG_ASYNC_INVOKE_T t_msg_async;
    UINT16                  ui2_retry;

    if(pf_async_func == NULL)
    {
        return WZDR_INV_ARG;
    }

    if(b_retry)
    {
        ui2_retry = 30;
    }
    else
    {
        ui2_retry = 0;
    }

    c_memset(&t_msg_async, 0, sizeof(WZD_MSG_ASYNC_INVOKE_T));
    t_msg_async.pf_async_func = pf_async_func;
    if(pv_data != NULL)
    {
        if(z_data_len <= WZD_ASYNC_DATA_THRESHOLD)
        {
            c_memcpy(t_msg_async.aui1_data,
                     pv_data,
                     z_data_len);
        }
        else
        {
            return WZDR_INV_ARG;
        }
    }

    /* Send the message to the wizard message queue. */
    do
    {
        i4_ret = c_app_send_msg(t_g_wzd.h_wzd,
                        WZD_MSG_ASYNC_INVOKE,
                        &t_msg_async,
                        z_data_len + 4,
                        NULL,
                        NULL);
        if(i4_ret != AEER_OK)
        {
            if(ui2_retry > 0)
            {

                c_thread_delay(100);
                ui2_retry--;
            }
            else
            {

                break;
            }
        }
        else
        {
            break;
        }
    } while (TRUE);

    return i4_ret == AEER_OK ? WZDR_OK : WZDR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name
 *      wzd_request_context_switch
 * Description
 *      The API is used to request a function execution in wizard's
 *      thread context.
 * Input arguments
 *      pf_fct          The function to be executed.
 *      pv_tag1         The first argument to pass to pf_fct.
 *      pv_tag2         The second argument to pass to pf_fct.
 *      pv_tag3         The third argument to pass to pf_fct.
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK         the routine is successfully.
 *      NAVR_INV_ARG    The pf_fct is NULL.
 *      NAVR_FAIL       The message queue of Navigator is failed to send message.
 *---------------------------------------------------------------------------*/
INT32 wzd_request_context_switch(
                    wzd_context_switch_nfy_fct      pf_fct,
                    VOID*                           pv_tag1,
                    VOID*                           pv_tag2,
                    VOID*                           pv_tag3
                    )
{
    WZD_EVN_T t_event;

    UINT32       ui4_retry_count = 0;
    INT32        i4_ret;

    if (pf_fct == NULL) {
        return WZDR_INV_ARG;
    }

    t_event.ui4_data1  = (UINT32)pf_fct;
    t_event.ui4_data2  = (UINT32)pv_tag1;
    t_event.ui4_data3  = (UINT32)pv_tag2;
    t_event.ui4_data4  = (UINT32)pv_tag3;

    while (ui4_retry_count < WZD_MSGQ_RESEND_TIMES) {
        i4_ret = c_app_send_msg (
                    t_g_wzd.h_wzd,
                    WZD_REQ_CTX_SWITCH_EVENT,
                    &t_event,
                    sizeof(WZD_EVN_T),
                    NULL,
                    NULL
                    );
        if (i4_ret == AEER_OK) {
            break;
        } else {
            /*c_thread_delay(MSG_RESEND_FAILED_SLEEP_TIME);*/
            ui4_retry_count++;
        }
    }

    if(i4_ret != AEER_OK)
    {
        /*DBG_ERROR((_ERROR_HEADER"c_app_send_msg() failed. i4_ret = %d/r/n.", i4_ret));*/
        DBG_ERROR(("wzd c_app_send_msg(WZD_REQ_CTX_SWITCH_EVENT) failed. i4_ret = %d\n.", i4_ret));
    }

    return i4_ret == AEER_OK ? WZDR_OK : WZDR_FAIL;
}

/*----------------------------------------------------------------------------
 * Name: wzd_get_subpage_id
 *
 * Description:
 *
 * Inputs:
 *      pui1_idx - The subpage index
 *
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 wzd_get_subpage_id( UINT8* pui1_idx )
{
    if( NULL == pui1_idx )
    {
        return WZDR_FAIL;
    }

    a_cfg_custom_get_wzd_subpage_id( pui1_idx );

    DBG_INFO(( "[wzd] Subpage ID = %d\n", *pui1_idx ));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_set_subpage_id
 *
 * Description:
 *
 * Inputs:
 *      ui1_idx - The subpage index
 *
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 wzd_set_subpage_id( UINT8 ui1_idx )
{
    a_cfg_custom_set_wzd_subpage_id( ui1_idx );

    return WZDR_OK;
}

static INT32 _wzd_get_crnt_isl(ISL_REC_T* pt_isl_rec)
{
    INT32           i4_ret;
    TV_WIN_ID_T     t_win_id;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    RET_ON_ERR(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id,
                                        pt_isl_rec);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

static HANDLE_T _wzd_get_crnt_svl(VOID)
{
    INT32  i4_ret;
    UINT16 ui2_crnt_svl_id;

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        return NULL_HANDLE;
    }

    return ((ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID) ?
            t_g_wzd.h_air_svl :
            t_g_wzd.h_cab_svl);
}

INT32 wzd_select_crnt_or_first_channel(BOOL b_skip_fake)
{
    INT32                      i4_ret;
    SVL_REC_T                  t_svl_rec          = {0};
    UINT32                     ui4_channel_id     = 0;
    UINT16                     ui2_crnt_svl_id    = ATSC_TRSTRL_SVL_ID;
    CHAR*                      ps_crnt_tuner_name = ATSC_TRSTRL_TUNER_NAME;
    HANDLE_T                   h_crnt_svl         = t_g_wzd.h_air_svl;
    ISL_REC_T                  t_isl_rec;
    TV_MODE_T                  t_tv_mode;
    TV_WIN_ID_T                t_win_id;
    UINT32                     ui4_g_last_strm_mode = ST_MASK_AUDIO|ST_MASK_VIDEO;

    /* Get current working TV Mode */
    a_tv_get_mode(&t_tv_mode);

    /* Check the input source on FOCUSED WIN */
    _wzd_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        if(t_tv_mode == TV_MODE_TYPE_NORMAL)
        {
            /* TV_MODE = NORMAL */
            /* Input Src != TV, so, change it to TV */

            a_tv_get_focus_win(&t_win_id);

            i4_ret = a_isl_get_rec_by_type(
                        INP_SRC_TYPE_TV,
                        0,
                        &t_isl_rec
                        );
            if (i4_ret != ISLR_OK) {
                return WZDR_FAIL;
            }

            i4_ret = a_tv_set_input_src_id(t_win_id, t_isl_rec.ui1_id);

            if (i4_ret != TVR_OK) {
                return WZDR_FAIL;
            }

        }
        else if(t_tv_mode == TV_MODE_TYPE_PIP ||
                t_tv_mode == TV_MODE_TYPE_POP)
        {
            /* TV_MODE = PIP/POP */
            /* Focus Win Input Src != TV, don't change anything, return directly */
            return WZDR_OK;
        }
        else
        {
            DBG_ERROR(("[WZD]menu_adjust_vplane can't handle.\n"));
        }
     }

    /* ------------------------------------------------- */

    /* The focus win's input src == INP_SRC_TYPE_TV now */

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, &ps_crnt_tuner_name);
    if (i4_ret != APP_CFGR_OK)
    {
        return WZDR_FAIL;
    }
    h_crnt_svl = _wzd_get_crnt_svl();

    if (h_crnt_svl == NULL_HANDLE)
    {
        return WZDR_OK;
    }

    if (t_g_wzd.b_svl_dirty == TRUE)
    {
        i4_ret = a_cfg_set_tuner_sync_src(ui2_crnt_svl_id, ps_crnt_tuner_name);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<WZD>Can't notify DT to sync source in menu_adjust_vplane()\r\n"));
            return WZDR_FAIL;
        }
        t_g_wzd.b_svl_dirty = FALSE;
    }

    /* Try to get a proper playable svl_rec */
    /* b_skip_fake argument is taking from outside */

    i4_ret = a_tv_get_crnt_or_first_svl_rec(h_crnt_svl, b_skip_fake, &t_svl_rec);

    if(i4_ret != TVR_OK)
    {
        i4_ret = a_tv_stop(t_g_wzd.h_svctx);

        if (i4_ret != TVR_OK)
        {
            DBG_ERROR (("<WZD> Stop service failed = %d\n\r", i4_ret));
        }

        return WZDR_OK;
    }
    else
    {
        ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;
    }

    /* Successfully get a playable svl_rec, so play it */
    if(t_tv_mode != TV_MODE_TYPE_NORMAL)
    {
            menu_keep_crnt_stream_mode();
        /* If PIP/POP mode, use the last stream mode. */
        i4_ret = a_tv_change_channel(t_g_wzd.h_svctx,
                                     ui4_g_last_strm_mode,
                                     ui4_channel_id,
                                     NULL);
    }
    else
    {
        /* If normal mode, always play video and audio */
        i4_ret = a_tv_change_channel(t_g_wzd.h_svctx,
                                     ST_MASK_VIDEO | ST_MASK_AUDIO,
                                     ui4_channel_id,
                                     NULL);
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _wzd_set_stream_attr
 * Description
 *      The API is used to set stream attribute through service context to stream
 *      manager(SM) for a specific window.
 * Input arguments
 *      e_tv_win_id     The target TV window ID
 *      e_strm_type     The stream type of the target stream
 *      e_set_type      The SM set type
 *      pv_set_info     The related data structure of the e_set_type
 *      z_set_info_size The actual data structure size of the pv_set_info
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK      the routine is successfully
 *      NAVR_INV_ARG the e_tv_win_id is invalid
 *      NAVR_FAIL    the routine is failed
 *---------------------------------------------------------------------------*/
static INT32 _wzd_set_stream_attr(
                    STREAM_TYPE_T               e_strm_type,
                    SM_SET_TYPE_T               e_set_type,
                    VOID*                       pv_set_info,
                    SIZE_T                      z_set_info_size
                    )
{
    INT32         i4_ret;

    i4_ret = c_svctx_set_stream_attr(
                    t_g_wzd.h_svctx,
                    e_strm_type,
                    e_set_type,
                    pv_set_info,
                    z_set_info_size
                    );
    DBG_INFO(("\n<>---%s, %d. ret:%d. --------\n", __FUNCTION__, __LINE__, i4_ret));
    return (i4_ret == SVCTXR_OK ? WZDR_OK : WZDR_FAIL);
}

INT32 wzd_set_stream_play_region(BOOL b_small_video, BOOL b_tv)
{
    INT32             i4_ret;
    VSH_REGION_INFO_T t_disp_region = {0};

    if (b_small_video)
    {
        /* Specify display region. */

/* OSD resolution */
#if defined(APP_OSD_640x720)
        UINT32 ui4_canvas_width = 640;
        UINT32 ui4_canvas_height= 720;
#elif defined(APP_OSD_960x540)
        UINT32 ui4_canvas_width = 960;
        UINT32 ui4_canvas_height= 540;
#else /* 1280 x 720 */
        UINT32 ui4_canvas_width = 1280;
        UINT32 ui4_canvas_height= 720;

#endif
        t_disp_region.ui4_x             = (UINT32)(((WZD_VIDEO_FRM_X) * VSH_REGION_MAX_WIDTH / ui4_canvas_width + 1) * VSH_REGION_MAX_WIDTH / VSH_REGION_MAX_WIDTH);
        t_disp_region.ui4_y             = (UINT32)(((WZD_VIDEO_FRM_Y) * VSH_REGION_MAX_HEIGHT / ui4_canvas_height + 1) * VSH_REGION_MAX_HEIGHT / VSH_REGION_MAX_HEIGHT);
        t_disp_region.ui4_width         = (UINT32)((WZD_VIDEO_FRM_W * VSH_REGION_MAX_WIDTH / ui4_canvas_width) * VSH_REGION_MAX_WIDTH / VSH_REGION_MAX_WIDTH);
        t_disp_region.ui4_height        = (UINT32)((WZD_VIDEO_FRM_H * VSH_REGION_MAX_HEIGHT / ui4_canvas_height + 1) * VSH_REGION_MAX_HEIGHT / VSH_REGION_MAX_HEIGHT);

        /* Fine tune the display region (in 10000 units.) */
        t_disp_region.ui4_x      = t_disp_region.ui4_x + 0;
        t_disp_region.ui4_y      = t_disp_region.ui4_y + 0;
        t_disp_region.ui4_width  = t_disp_region.ui4_width + 0;
        t_disp_region.ui4_height = t_disp_region.ui4_height + 0;

        i4_ret = _wzd_set_stream_attr(
                ST_VIDEO,
                SM_VSH_SET_TYPE_DISP_REGION,
                &t_disp_region,
                sizeof(VSH_REGION_INFO_T)
                );
        if (i4_ret != WZDR_OK) {
            return WZDR_FAIL;
        }

        if (b_tv)
        {
            wzd_select_crnt_or_first_channel(FALSE);
        }

        b_g_small_video_enable = TRUE;
    }
    else
    {
        /* Full display region. */
        t_disp_region.ui4_x      = 0;
        t_disp_region.ui4_y      = 0;
        t_disp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
        t_disp_region.ui4_height = VSH_REGION_MAX_HEIGHT;
        DBG_INFO(("\n-----%s, %d. %d-%d-%d-%d. ----\n", __FUNCTION__, __LINE__, t_disp_region.ui4_x, t_disp_region.ui4_y, t_disp_region.ui4_width, t_disp_region.ui4_height));
        if (b_g_small_video_enable)
        {
            i4_ret = _wzd_set_stream_attr(
                ST_VIDEO,
                SM_VSH_SET_TYPE_DISP_REGION,
                &t_disp_region,
                sizeof(VSH_REGION_INFO_T)
                );
            if (i4_ret != WZDR_OK) {
                return WZDR_FAIL;
            }
        }

        b_g_small_video_enable = FALSE;
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_resume_network_setting.
 *
 * Description: This API resume wizard in network setting page.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 a_wzd_resume_network_setting (VOID)
{
    t_g_wzd.ui1_state    = WZD_STATE_RESUME;
    t_g_wzd.ui1_page_idx = WZD_PAGE_INDEX_NW_SETUP;
    t_g_wzd.ui1_end_idx  = WZD_PAGE_INDEX_NW_SETUP;

    RET_ON_ERR (a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx)));

    /*Show Wizard UI ASAP*/
    a_amb_resume_app (WZD_NAME);
    a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=wizard\n");

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_resume_tv_setup.
 *
 * Description: This API resume wizard in tv setup page.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 a_wzd_resume_tv_setup (VOID)
{
    t_g_wzd.ui1_state    = WZD_STATE_RESUME;
    t_g_wzd.ui1_page_idx = WZD_PAGE_INDEX_TV_SETUP;
    t_g_wzd.ui1_end_idx = WZD_PAGE_INDEX_TV_SETUP;

    RET_ON_ERR (a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx)));

    /*Show Wizard UI ASAP*/
    a_amb_resume_app (WZD_NAME);
    a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=wizard\n");

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_resume_tv_remote_device_setup.
 *
 * Description: This API resume wizard in tv setup page.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 a_wzd_resume_tv_remote_device_setup (VOID)
{
    t_g_wzd.ui1_state    = WZD_STATE_RESUME;
    t_g_wzd.ui1_page_idx = WZD_PAGE_TV_REMOTE_DEVICE_SETUP;
    t_g_wzd.ui1_end_idx  = WZD_PAGE_TV_REMOTE_DEVICE_SETUP;

    RET_ON_ERR (a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx)));

    /*Show Wizard UI ASAP*/
    a_amb_resume_app (WZD_NAME);
    a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=wizard\n");

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_is_resume_from_menu_setup.
 *
 * Description: resume form MENU->HELP->SETUP.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns:
 *
----------------------------------------------------------------------------*/
BOOL a_wzd_is_resume_from_menu_setup (VOID)
{
    if (t_g_wzd.ui1_state == WZD_STATE_RESUME)  /* resume form MENU->HELP->SETUP*/
    {
        return TRUE;
    }

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_is_resume_from_wifi_unpairing.
 *
 * Description: if wifi unpairing, drv will change the value of eeprom, Ap will get the status after power on.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns:
 *
----------------------------------------------------------------------------*/
BOOL a_wzd_is_resume_from_wifi_unpairing (VOID)
{
    if (t_g_wzd.ui1_state == WZD_STATE_RESUME_WIFI_RC_PARING)
    {
    	DBG_INFO(("<WZD> a_wzd_is_resume_from_wifi_unpairing return true\n"));
        return TRUE;
    }
	DBG_INFO(("<WZD> a_wzd_is_resume_from_wifi_unpairing return false\n"));

    return FALSE;
}
/*----------------------------------------------------------------------------
 * Name: a_wzd_resume_tv_remote_pairing_setup.
 *
 * Description: This API resume wizard in wifi remote pairing page.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 a_wzd_resume_tv_remote_pairing_setup (VOID)
{
    t_g_wzd.ui1_state    = WZD_STATE_RESUME;
    t_g_wzd.ui1_page_idx = WZD_PAGE_INDEX_WIFI_REMOTE_PARING;
    t_g_wzd.ui1_end_idx  = WZD_PAGE_INDEX_WIFI_REMOTE_PARING;

    RET_ON_ERR (a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx)));

    /*Show Wizard UI ASAP*/
    a_amb_resume_app (WZD_NAME);
    a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=wizard\n");

    return WZDR_OK;
}

INT32 a_wzd_exit (VOID)
{
    if (!a_wzd_is_resume_from_menu_setup())
    {
        a_amb_resume_app (NAV_NAME);

    #ifdef APP_HOTKEY_WAKEUP_SUPPORT
        a_tv_custom_set_hotkey_wakeup_active(WAKEUP_AP_WZD_CLEAN);
    #endif

    }

    a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:pause=wizard\n");

#ifdef APP_CEC_SUPPORT
#ifdef APP_CEC2_SUPPORT
#ifdef APP_ARC_ONLY
	if(b_g_is_amp_plug_dlg_show == FALSE)
	{
		nav_cec_custom_amp_plug_dlg_show();
	}
#endif
#endif
#endif
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_wzd_is_keep_mute
 *
 * Description: get mute status under wizard
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: BOOL true is need keep mute
 *
 ----------------------------------------------------------------------------*/
BOOL a_wzd_is_keep_mute(VOID)
{
    if (t_g_wzd.b_g_is_vol_key_enable)
    {
        return b_g_is_mute;
    }
    else
    {
        return TRUE;
    }
}

#ifdef APP_C4TV_SUPPORT
BOOL b_is_privision_update = FALSE;
VOID a_wzd_set_privision_update(BOOL b_update)
{
    DBG_LOG_PRINT(("[WZD_C4TV] a_wzd_set_privision_update b_update: %d\r\n\n", b_update));
    b_is_privision_update = b_update;
}

VOID a_wzd_stop_c4tv (c4tv_apron_custom_nfy_fct pf_nfy)
{
    KK_LOG(KK_LOG_LVL_API, "[WZD_C4TV]", "Enter.\n");

    if (c_timer_stop(t_g_wzd.h_timer_oobe) == OSR_OK) {
        DBG_LOG_PRINT(("[WZD_C4TV] oobe timer stopped successfully\r\n"));
    } else {
        DBG_ERROR(("[WZD_C4TV] a_wzd_stop_c4tv failed to stop oobe timer\r\n"));
    }

    /* enable the system keys */
    a_amb_enable_system_key(TRUE);

    /* wait for cast_shell ready */
    int i = 0;
    UINT8 ui1_val = 0;
    INT32 i4_cast_state = 0;
    i4_cast_state = a_c4tv_apron_get_cast_state();
    a_icl_get_uli_download_status(&ui1_val);
    DBG_LOG_PRINT(("[WZD_C4TV] wait for cast shell ready, i4_cast_state: %d ui1_val: %d b_is_privision_update: %d\r\n\n", i4_cast_state, ui1_val, b_is_privision_update));
    while (b_is_privision_update && 1 == ui1_val && i4_cast_state != 6 && i < 300)
    {
        i++;
        i4_cast_state = a_c4tv_apron_get_cast_state();
        DBG_LOG_PRINT(("[WZD_C4TV] sleep 100ms wait for cast shell ready, i: %d, i4_cast_state: %d ui1_val: %d\r\n\n", i, i4_cast_state, ui1_val));
        usleep(100*1000);
    }
    b_is_privision_update = FALSE;

    if (NULL != pf_nfy)
    {
        DBG_LOG_PRINT(("[WZD_C4TV] %s, pf_nfy\n", __FUNCTION__));
        pf_nfy(NULL, NULL, NULL);
    }
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_resume_c4tv.
 *
 * Description: This API resume wizard in c4tv page.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 a_wzd_resume_c4tv(UINT8 ui1_state, UINT8 ui1_page_idx)
{
    KK_LOG(KK_LOG_LVL_API, "[WZD_C4TV]", "Enter.\n");

    t_g_wzd.ui1_state    = ui1_state;
    t_g_wzd.ui1_page_idx = ui1_page_idx;

    RET_ON_ERR (a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx)));

    /*Show Wizard UI ASAP*/
    a_amb_resume_app (WZD_NAME);
    a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=wizard\n");

    return WZDR_OK;

}

/*----------------------------------------------------------------------------
 * Name: a_wzd_resume_state_only_c4tv
 *
 * Description: This API resumes wizard without showing UI.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 a_wzd_resume_state_only_c4tv(UINT8 ui1_state, UINT8 ui1_page_idx)
{
    KK_LOG(KK_LOG_LVL_API, "[WZD_C4TV]", "Enter.\n");

    t_g_wzd.ui1_state    = ui1_state;
    t_g_wzd.ui1_page_idx = ui1_page_idx;

    RET_ON_ERR (a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(t_g_wzd.ui1_state, t_g_wzd.ui1_page_idx)));
    return WZDR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      a_wzd_is_oobe_mode
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL a_wzd_is_oobe_mode(VOID)
{
    INT32   i4_ret = 0;
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    UINT8   ui1_index     = 0;

    i4_ret = a_cfg_get_wzd_status(&ui2_status);
    if (APP_CFGR_OK != i4_ret)
    {
        return FALSE;
    }
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_index = WZD_UTIL_GET_STATUS_IDX(ui2_status);

#ifdef APP_C4TV_SUPPORT
    if(WZD_STATE_RESUME_C4TV == ui1_state && WZD_PAGE_INDEX_C4TV_STORE_DEMO != ui1_index)
#else
    if (0)
#endif
    {

        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * Name: a_wzd_is_storedemo_mode
 * Description : This API to check whether in storedemo mode or not
 * Input arguments
 * Output arguments
 * Returns: TRUE while in storedemo mode
 *          FALSE while not in storedemo mode
 *---------------------------------------------------------------------------*/
BOOL a_wzd_is_storedemo_mode()
{
    INT32   i4_ret = 0;
    UINT16  ui2_status    = 0;
    UINT8   ui1_index     = 0;
    BOOL    storedemo_mode = FALSE;
    ACFG_RETAIL_MODE_T   t_storedemo_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
    NAV_RETAIL_MODE_STATUS_T   t_storedemo_status;

    a_cfg_custom_get_retail_mode_setting(&t_storedemo_mode);
    a_nav_retail_mode_get_status(&t_storedemo_status);

    i4_ret = a_cfg_get_wzd_status(&ui2_status);
    if (APP_CFGR_OK != i4_ret)
    {
        return FALSE;
    }
    ui1_index = WZD_UTIL_GET_STATUS_IDX(ui2_status);
    if(ACFG_RETAIL_MODE_NORMAL == t_storedemo_mode && NAV_RETAIL_MODE_RUNNING == t_storedemo_status)
    {
       storedemo_mode = TRUE;
    }
    if(WZD_PAGE_INDEX_C4TV_STORE_DEMO == ui1_index || TRUE == storedemo_mode)
    {
        return TRUE;
    }
    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: a_wzd_set_oobe_start_status.
 *
 * Description: This API set oobe start page status.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 a_wzd_set_oobe_started()
{
    KK_LOG(KK_LOG_LVL_API, "[WZD_C4TV]", "Enter.\n");

    ui1_launch_oobe_start_status |= WZD_STATE_OOBE_STARTED;

    return WZDR_OK;
}
