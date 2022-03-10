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
 * $RCSfile: wzd_network.c,v $
 * $Revision$
 * $Date$
 * $Author$
 *
 * Description:
 *---------------------------------------------------------------------------*/
#ifdef APP_NETWORK_SUPPORT
/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "c_dbg.h"
#include "c_fm.h"
#include "c_txt.h"
#include "u_btn_map.h"
#include "wdk/a_vkb.h"
#include "wdk/vkb/vkb.h"

//#include "project-mtk-api.h"

#include "res/wizard/wzd_cfg.h"
#include "res/wizard/wzd_mlm.h"
#include "res/wizard/wzd_img.h"
#include "res/wdk/wdk_img.h"
#include "res/wdk/a_vkb_custom.h"

#include "app_util/a_network.h"
#include "app_util/download_util/a_download_util.h"

#include "res/app_util/network/network_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/acfg_custom.h"

#include "wizard/wzd.h"
#include "wizard/page/wzd_page_nw_setup.h"
#include "wizard/wzd_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define WZD_NW_PAGE_ID              (0x20)
#define WZD_WIFI_SSID_SCAN_COUNT    (10)

typedef enum
{
    WZD_NW_DLG_1 = 0,
    WZD_NW_DLG_2,
    WZD_NW_DLG_3

}WZD_NW_DLG_T;

static WZD_NW_T             t_wzd_nw;
static NW_SETUP_STATE       e_g_nw_setup_state = NW_SETUP_STATE_BEGIN;
static NW_SETUP_STATE       e_g_nw_setup_pre_state = NW_SETUP_STATE_BEGIN;
static UINT16               ui2_g_ssid_scan_count = 0;

#ifdef WZD_NW_TEST_CONNECTION
static UINT32          		ui4_g_wzd_test_connection_tag = 0;
static UINT32          		ui4_g_wzd_test_connection_nfy_id = 0;
#endif

static WZD_SEL_BOX_BTN_INDEX_T	e_sb_pre_focused_box = WZD_SEL_BOX_BTN_01;
static WZD_FOOTER_BTN_INDEX_T	e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;

/* 0: default; 1: accept tos; -1: reject tos */
static INT8					i1_tos_is_accept = 0;
static BOOL				    b_reg_info_is_store = FALSE;

static BOOL					b_nw_ready_to_show = FALSE;
/*-----------------------------------------------------------------------------
                    function prototypes
 ----------------------------------------------------------------------------*/

static INT32 _wzd_nw_go(
                    NW_SETUP_STATE	e_nw_setup_state,
                    BOOL            b_repaint);

static INT32 _wzd_nw_leave_this_page(VOID);

static INT32 _wzd_nw_store_ap_list_data(VOID);

static VOID _wzd_nw_timer_start(
                    VOID*           pv_data,
                    SIZE_T          z_data_size);

static VOID _wzd_nw_protocol_text_show_nfy_cb(
                    HANDLE_T                    h_handle,
                    const VOID*                 pv_pt_txt,
                    TXT_ASYNC_COND_T            e_event,
                    const VOID*                 pv_data);

static INT32 _wzd_nw_conn_lan_or_wifi(VOID);

static INT32 _wzd_nw_wifi_conn(VOID);

static INT32 _wzd_nw_wifi_scan(VOID);

static INT32 _wzd_nw_footer_btn_focus(VOID);

/* associate wifi with ssid and password */
static INT32 _wzd_nw_ssid_wifi_assoc(VOID);

static INT32 _wzd_nw_wifi_scan_with_ssid(VOID);

static INT32 _wzd_nw_test_connection(VOID);

static INT32 _wzd_nw_conn_is_connected(
                    BOOL*           pb_is_connected);

static INT32 _wzd_page_nw_setup_hide(
                    UINT32          ui4_sub_page_id);

static INT32 _wzd_nw_help_lst_update (
                    NW_SETUP_STATE	e_nw_setup_state,
                    BOOL            b_repaint);

static BOOL _wzd_nw_is_ssid_scan_success(VOID);

static INT32 _wzd_nw_wps_associate(VOID);

static INT32 _wzd_nw_assoc_dlg_create (VOID);

/* select box */
static INT32 _wzd_page_nw_setup_create_sel_box (VOID);

static VOID _wzd_page_nw_setup_sel_box_nfy(
					UINT32   		ui4_msg,
					VOID*    		pv_param1,
					VOID*    		pv_param2);

static INT32 _wzd_page_nw_setup_sb_btn_img(
					UINT8 			ui1_btn,
					UINT32 			ui4_idx,
					WGL_HIMG_TPL_T	t_img_tpl);

static INT32 _wzd_page_nw_setup_sel_box_initial_theme (const UINT32 ui4_btn_idx);
static INT32 _wzd_page_nw_setup_sel_box_hl_theme (const UINT32 ui4_btn_idx);

static INT32 _wzd_page_nw_setup_sel_box_left_shift (const UINT32 ui4_btn_idx);
static INT32 _wzd_page_nw_setup_sel_box_right_shift (const UINT32 ui4_btn_idx);

static INT32 _wzd_nw_get_associate_data(NET_802_11_ASSOCIATE_T** ppt_associate);
static INT32 _wzd_nw_info_check_box_proc_fct(HANDLE_T   h_widget,
                                             UINT32     ui4_msg,
                                             VOID*      param1,
    										 VOID*		param2);

static INT32 _wzd_nw_protocol_text_show_prev_row(HANDLE_T     h_text_widget,
                                                 HANDLE_T     h_text);
static INT32 _wzd_nw_protocol_text_show_next_row(HANDLE_T     h_text_widget,
                                                 HANDLE_T     h_text);

static INT32 _wzd_nw_float_prompt_create(HANDLE_T h_parent);
static INT32 _wzd_nw_float_prompt_show(VOID);
static INT32 _wzd_nw_float_prompt_hide(VOID);
static INT32 _wzd_nw_float_prompt_repaint(VOID);
static INT32 _wzd_nw_float_prompt_set_text(UTF16_T* pw2s_text);
static INT32 _wzd_nw_reg_info_update_eb_content(UINT8 ui1_item_idx);

/* open protocol text */
static INT32 _wzd_nw_protocol_text_frame_show(VOID);
static INT32 _wzd_nw_protocol_text_open(VOID);
static INT32 _wzd_nw_protocol_timer_start (VOID);

#ifdef APP_DYNAMIC_TOS_SUPPORT
static TOS_TYPE_T _wzd_tos_get_type (VOID);
#endif

/*-----------------------------------------------------------------------------
                    function implement
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_notify_handler
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    WZD_NW_NFY_DATA_T* pt_nw_nfy_data = (WZD_NW_NFY_DATA_T *)pv_data;

    switch(pt_nw_nfy_data->e_nfy_id)
    {
    case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
    {
		DBG_LOG_PRINT(("[WZD][NW] --- DHCP started successfully and get IPV4. %d\n",__LINE__));

        if (WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param))
        {
        	t_wzd_nw.b_timer_result = TRUE;
        }
    }
        break;
    case NW_NFY_ID_DHCP_SUCCESS_LINKLOCAL:
    {
		DBG_LOG_PRINT(("[WZD][NW] --- DHCP started successfully but get link local IP. %d\n",__LINE__));

        if (WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param))
        {
            t_wzd_nw.b_timer_result = FALSE;
        }
    }
        break;
    case NW_NFY_ID_ADDRESS_CHANGED:
    case NW_NFY_ID_ADDRESS_EXPIRED:
    case NW_NFY_ID_DHCP_FAILURE_LINKLOCAL:
    case NW_NFY_ID_DHCP_STOPPED:
        break;
    case NW_NFY_ID_ETHERNET_PLUGIN:
    case NW_NFY_ID_ETHERNET_UNPLUG:
		DBG_LOG_PRINT(("[WZD][NW] --- ETHERNET PLUGIN or UNPLUG. %d\n",__LINE__));
		_wzd_nw_conn_lan_or_wifi();
        break;
    case NW_NFY_ID_INTERN_CT_RESULT:
    {
		DBG_LOG_PRINT(("[WZD][NW] --- Internet connection test result. %d\n",__LINE__));

        if (0 == (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param))
        {
            t_wzd_nw.b_timer_result = FALSE;
        }
        else
        {
            t_wzd_nw.b_timer_result = TRUE;
        }
    }
        break;
#ifdef APP_NETWORK_WIFI_SUPPORT
    case NW_NFY_ID_WLAN_ASSOCIATE:
    case NW_NFY_ID_WLAN_WPS_ASSOCIATE:
    {
        DBG_LOG_PRINT(("[WZD][NW] --- WLAN ASSOCIATE . %d\n",__LINE__));

        if (WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param))
        {
            BOOL    b_connected = FALSE;

            _wzd_nw_conn_is_connected(&b_connected);
            if (b_connected)
            {
                t_wzd_nw.b_timer_result = TRUE;
            }
        }
        else
        {
            t_wzd_nw.b_timer_result = FALSE;
        }
    }
        break;
    case NW_NFY_ID_WLAN_START_IND:
    {
		DBG_LOG_PRINT(("[WZD][NW] --- WLAN START INIT. %d\n",__LINE__));

        if (WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param))
        {
            /* if wifi module is initial then scan immediately */
            if (FALSE == t_wzd_nw.t_choice_connect.b_is_wlan_ind)
            {
                a_nw_wlan_scan();

				t_wzd_nw.t_choice_connect.b_is_wlan_ind = TRUE;
            }
            DBG_LOG_PRINT(("[WZD][NW] --- %s, %d. ---\n", __FUNCTION__, __LINE__));
        }
        else
        {
            /* if wifi module is not initial, we will not invoke wifi scan */
            t_wzd_nw.t_choice_connect.b_is_wlan_ind = FALSE;
        }
    }
        break;
    case NW_NFY_ID_WLAN_SCAN:
    {
		DBG_LOG_PRINT(("[WZD][NW] --- WLAN scan result notification. %d\n",__LINE__));

        if (WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param))
        {
            if ((WZD_NW_TIMER_WIFI_SCAN == t_wzd_nw.e_wzd_nw_timer)
                ||(WZD_NW_TIMER_WIFI_SSID_SCAN == t_wzd_nw.e_wzd_nw_timer))
            {
                t_wzd_nw.b_timer_result = TRUE;
            }
            else
            {
                t_wzd_nw.b_timer_result = FALSE;
            }
        }
        else
        {
            t_wzd_nw.b_timer_result = FALSE;
        }
    }
        break;
#endif
    default:
        break;
    }
    return;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_notify_callback
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    WZD_NW_NFY_DATA_T 	t_nw_nfy_data;
	UINT16  			ui2_status;
    UINT8   			ui2_page_idx;

	/* if network page is NOT ready to show */
    if (!b_nw_ready_to_show)
    {
        return;
    }

	/* if NOT on network setup page, should not handler network notify msg */
    a_cfg_get_wzd_status (&ui2_status);
    ui2_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);
    if(ui2_page_idx != WZD_PAGE_INDEX_NW_SETUP)
    {
    	return;
    }

	/* do NOT handler network notify msg */
	if (e_g_nw_setup_state == NW_SETUP_STATE_PROTOCOL
		|| e_g_nw_setup_state == NW_SETUP_STATE_INFO_REG)
	{
		return;
	}

    c_memset(&t_nw_nfy_data, 0, sizeof(WZD_NW_NFY_DATA_T));
    t_nw_nfy_data.pv_tag       = pv_tag;
    t_nw_nfy_data.e_nfy_id     = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    wzd_async_invoke(_wzd_nw_notify_handler,
                     &t_nw_nfy_data,
                     (SIZE_T)sizeof(WZD_NW_NFY_DATA_T),
                     TRUE);

    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_timer_icon_update
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_timer_icon_update(HANDLE_T   h_widget)
{
    INT32                i4_ret;
    WGL_IMG_INFO_T       t_img_info;
	BOOL 				 b_visible = FALSE;

	i4_ret = c_wgl_get_visibility (h_widget, &b_visible);
	RET_ON_ERR(i4_ret);

    if (FALSE == b_visible)
    {
		return WZDR_OK;
    }

	/* not busying, not need icon update any more */
	if (!t_wzd_nw.b_is_busying)
	{
		return WZDR_OK;
	}

	WGL_HIMG_TPL_T       ah_g_searching_icon[12] =
    {
        h_g_wdk_img_loading_icon_1,
        h_g_wdk_img_loading_icon_2,
        h_g_wdk_img_loading_icon_3,
        h_g_wdk_img_loading_icon_4,
        h_g_wdk_img_loading_icon_5,
        h_g_wdk_img_loading_icon_6,
        h_g_wdk_img_loading_icon_7,
        h_g_wdk_img_loading_icon_8,
        h_g_wdk_img_loading_icon_9,
        h_g_wdk_img_loading_icon_10,
        h_g_wdk_img_loading_icon_11,
        h_g_wdk_img_loading_icon_12
    };

    if(t_wzd_nw.t_choice_connect.ui1_icon_step >= ((sizeof(ah_g_searching_icon) / sizeof(WGL_HIMG_TPL_T)) -1))
    {
        t_wzd_nw.t_choice_connect.ui1_icon_step = 0;
    }
    else
    {
        t_wzd_nw.t_choice_connect.ui1_icon_step++;
    }

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = ah_g_searching_icon[t_wzd_nw.t_choice_connect.ui1_icon_step];
    t_img_info.u_img_data.t_standard.t_disable   = ah_g_searching_icon[t_wzd_nw.t_choice_connect.ui1_icon_step];
    t_img_info.u_img_data.t_standard.t_highlight = ah_g_searching_icon[t_wzd_nw.t_choice_connect.ui1_icon_step];


    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(h_widget, NULL, TRUE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_full_screen_icon_update
 *
 * Description:
 *
 * Inputs: b_repaint           Repaint or not.
 *
 * Outputs:
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_full_screen_icon_update(BOOL b_repaint)
{
	BOOL				b_is_show = FALSE;
    INT32 				i4_ret = WZDR_OK;
	WGL_HIMG_TPL_T		ah_g_searching_icon[12] =
    {
        h_g_wdk_img_loading_icon_1,
        h_g_wdk_img_loading_icon_2,
        h_g_wdk_img_loading_icon_3,
        h_g_wdk_img_loading_icon_4,
        h_g_wdk_img_loading_icon_5,
        h_g_wdk_img_loading_icon_6,
        h_g_wdk_img_loading_icon_7,
        h_g_wdk_img_loading_icon_8,
        h_g_wdk_img_loading_icon_9,
        h_g_wdk_img_loading_icon_10,
        h_g_wdk_img_loading_icon_11,
        h_g_wdk_img_loading_icon_12
    };

	b_is_show = wzd_view_full_screen_dlg_is_show();
	if (FALSE == b_is_show)
	{
		t_wzd_nw.ui1_icon_step = 0;
	}
	else
	{
		if(t_wzd_nw.ui1_icon_step >= ((sizeof(ah_g_searching_icon) / sizeof(WGL_HIMG_TPL_T)) -1))
		{
		    t_wzd_nw.ui1_icon_step = 0;
		}
		else
		{
		    t_wzd_nw.ui1_icon_step++;
		}
	}

	i4_ret = wzd_view_full_screen_dlg_set_icon (
					ah_g_searching_icon[t_wzd_nw.ui1_icon_step],
					b_repaint);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_text_set_text
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_text_set_text (HANDLE_T  h_widget,
                                    UINT32    ui4_msg_id)
{
    INT32   i4_ret;

    i4_ret = c_wgl_do_cmd (h_widget,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (WZD_TEXT(ui4_msg_id)),
                      WGL_PACK (c_uc_w2s_strlen (WZD_TEXT(ui4_msg_id))));
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_wifi_scan_timeout
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_wifi_scan_timeout (VOID)
{
    INT32   i4_ret;

	/* if wlan scan be quit, should stop flow */
	if (!t_wzd_nw.b_is_busying)
	{
		t_wzd_nw.ui4_start_time = 0;
		return WZDR_OK;
	}

    t_wzd_nw.b_is_busying = FALSE;
    t_wzd_nw.ui4_start_time = 0;

#if 0
	DBG_LOG_PRINT(("[WZD][NW] --- %s, WLAN disassociate.\n", __FUNCTION__));
    i4_ret = a_nw_custom_wlan_disassociate();
    RET_ON_ERR(i4_ret);
#endif

    i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(t_wzd_nw.h_timer_icon, NULL, TRUE);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_go(NW_SETUP_STATE_NONE_CONN, TRUE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_wifi_scan_result_timeout
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_wifi_scan_result(VOID)
{
    INT32   		i4_ret;

    DBG_LOG_PRINT(("[WZD][NW] --- wzd nw wifi scan result. \n"));

	/* if wlan scan be quit, should stop flow */
	if (!t_wzd_nw.b_is_busying)
	{
		t_wzd_nw.ui4_start_time = 0;
		return WZDR_OK;
	}

    i4_ret = _wzd_nw_store_ap_list_data();
    if (WZDR_OK != i4_ret || t_wzd_nw.t_choice_connect.ui1_visiable_ap_num <= 0)
    {
        return _wzd_nw_wifi_scan_timeout();
    }

	t_wzd_nw.b_is_busying = FALSE;
    t_wzd_nw.ui4_start_time = 0;

#if 0
	DBG_LOG_PRINT(("[WZD][NW] --- %s, WLAN disassociate.\n", __FUNCTION__));
    i4_ret = a_nw_custom_wlan_disassociate();
    RET_ON_ERR(i4_ret);
#endif

	i4_ret = _wzd_nw_go(NW_SETUP_STATE_WIRELESS_SCAN_RESULT, TRUE);
	RET_ON_ERR(i4_ret);

    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_wifi_assoc_timeout
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_wifi_assoc_timeout (VOID)
{
    INT32       i4_ret;

	DBG_LOG_PRINT(("[WZD][NW] --- %s %d, WIFI ASSOC TIMEOUT.\n", __FUNCTION__,__LINE__));

    t_wzd_nw.b_is_busying = FALSE;
    t_wzd_nw.ui4_start_time = 0;

    if (a_nw_custom_nw_wifi_start())
    {
    	DBG_LOG_PRINT(("[WZD][NW] --- %s, WLAN disassociate.\n", __FUNCTION__));
        i4_ret = a_nw_custom_wlan_disassociate();
        SHOW_ON_ERR(i4_ret);
    }
    else
    {
        DBG_LOG_PRINT(("[WZD][NW] --- %s, WIFI not ready.\n", __FUNCTION__));
    }

	/* hide circular motion icon */
	c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_HIDE);

	/* hide full screen dialog */
	wzd_view_full_screen_dlg_hide();

	/* show associate fail dialog */
	_wzd_nw_assoc_dlg_create();

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_lan_assoc_result
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_lan_assoc_result (VOID)
{
	DBG_LOG_PRINT(("[WZD][NW] --- %s %d, ASSOC RESULT.\n", __FUNCTION__,__LINE__));

    INT32   i4_ret;

    t_wzd_nw.ui4_start_time = 0;
    t_wzd_nw.b_is_busying = FALSE;

	/* show full screen dialog */
	RET_ON_ERR (wzd_view_full_screen_dlg_set_icon (
					h_g_wzd_img_checkmark_white_dialog,
					FALSE));

	RET_ON_ERR (wzd_view_full_screen_dlg_set_text (
					WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTED_TO_ETHERNET),
					FALSE));

	RET_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));

	/* test connection */
    i4_ret = _wzd_nw_test_connection();
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_wifi_assoc_result
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_wifi_assoc_result (VOID)
{
    INT32   				i4_ret;
	UTF16_T     			w2s_ssid [WZD_NW_SSID_MAX_LEN+1] = {0};
	UTF16_T                 w2s_msg [127+1] = {0};
    NET_802_11_ASSOCIATE_T*	pt_associate = NULL;

	DBG_LOG_PRINT(("[WZD][NW] --- %s %d, ASSOC RESULT.\n", __FUNCTION__,__LINE__));

    t_wzd_nw.ui4_start_time = 0;
    t_wzd_nw.b_is_busying = FALSE;

	/* get associate ap information */
	i4_ret = _wzd_nw_get_associate_data(&pt_associate);
    RET_ON_ERR(i4_ret);

    if(pt_associate == NULL)
    {
        return WZDR_OK;
    }

    c_uc_ps_to_w2s(pt_associate->t_Ssid.ui1_aSsid, w2s_ssid, pt_associate->t_Ssid.ui4_SsidLen);
    w2s_ssid[pt_associate->t_Ssid.ui4_SsidLen]= (UTF16_T)0;

	DBG_LOG_PRINT(("[WZD][NW] --- ASSOC RESULT SSID: %s.\n", w2s_ssid));

	if (NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE == e_g_nw_setup_state)
	{
		c_uc_w2s_strcat (w2s_msg, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTED_TO_WPS));
	}
	else if (c_uc_w2s_strlen(w2s_ssid) == 0)
	{
		/* ssid length is 0 */
		c_uc_w2s_strcat (w2s_msg, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTED_TO_NETWORK));
	}
	else
	{
		c_uc_w2s_strcat (w2s_msg, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTED_TO));
		c_uc_w2s_strcat (w2s_msg, w2s_ssid);
	}

	/* update full screen dialog content */
	RET_ON_ERR (wzd_view_full_screen_dlg_set_icon (
					h_g_wzd_img_checkmark_white_dialog,
					FALSE));

	RET_ON_ERR (wzd_view_full_screen_dlg_set_text (
					w2s_msg,
					FALSE));

	RET_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));


    i4_ret = _wzd_nw_test_connection();
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_test_conn_timeout
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_test_conn_timeout (VOID)
{
    INT32       i4_ret = WZDR_OK;

    t_wzd_nw.b_is_busying = FALSE;
    t_wzd_nw.ui4_start_time = 0;

    RET_ON_ERR (wzd_view_full_screen_dlg_hide());

    i4_ret = wzd_view_main_frm_repaint();
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_test_conn_result
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_test_conn_result (VOID)
{
    UINT8   ui1_reg_info = 0;

    t_wzd_nw.b_is_busying = FALSE;
    t_wzd_nw.ui4_start_time = 0;

	RET_ON_ERR (wzd_view_full_screen_dlg_hide());

	a_cfg_cust_get_cust_nw_register_status(&ui1_reg_info);
	DBG_LOG_PRINT(("\na_cfg_get_nw_register_status ui1_reg_info=%d\n", ui1_reg_info));

    if ((i1_tos_is_accept != 1) &&
		(a_tv_custom_get_tos() == FALSE ||a_tv_custom_get_privacy() == FALSE))
    {
        RET_ON_ERR(_wzd_nw_go(NW_SETUP_STATE_PROTOCOL, TRUE));
    }
	else if(!a_wzd_is_resume_from_menu_setup())
    {
        RET_ON_ERR(_wzd_nw_go(NW_SETUP_STATE_INFO_REG, TRUE));
    }
    else
    {
        RET_ON_ERR(_wzd_nw_leave_this_page());
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_do_timer_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_do_timer_nfy(VOID* pv_data,
                                 SIZE_T  z_data_size)
{
    UINT32  ui4_curr_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
    UINT32  ui4_period_time = ui4_curr_time - (t_wzd_nw.ui4_start_time);

    WZD_NW_TIMER_E e_wzd_nw_timer = *(WZD_NW_TIMER_E*)pv_data;

	/* update timer icon first */
	if (WZD_NW_TIMER_WIFI_SCAN == e_wzd_nw_timer ||
		WZD_NW_TIMER_WIFI_WPS_ASSOC == e_wzd_nw_timer)
	{
    	_wzd_nw_timer_icon_update(t_wzd_nw.h_timer_icon);
	}
	else if(WZD_NW_TIMER_WIFI_ASSOC == e_wzd_nw_timer ||
			WZD_NW_TIMER_WIFI_SSID_SCAN == e_wzd_nw_timer ||
			WZD_NW_TIMER_WIFI_PWD_ASSOC == e_wzd_nw_timer ||
			WZD_NW_TIMER_LAN_ASSOC == e_wzd_nw_timer)
	{
		_wzd_nw_full_screen_icon_update(TRUE);
	}
	else
	{
		/* do nothing */
	}

	/* special case WPS ASSOC*/
	if (WZD_NW_TIMER_WIFI_WPS_ASSOC == e_wzd_nw_timer)
    {
        if(ui4_period_time > WZD_NW_WLAN_WPS_ASSOC_TIMEOUT)
        {
            _wzd_nw_wifi_assoc_timeout();
            return;
        }

        if(TRUE == t_wzd_nw.b_timer_result)
        {
            _wzd_nw_wifi_assoc_result();
            return;
        }

        _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);
        return;
    }

	/* handle timeout */
    if(ui4_period_time > WZD_NW_WLAN_TIMEOUT)
    {
        switch(e_wzd_nw_timer)
        {
            case WZD_NW_TIMER_LAN_ASSOC:
            {
                _wzd_nw_wifi_conn();
            }
                break;
            case WZD_NW_TIMER_WIFI_SCAN:
            {
                _wzd_nw_wifi_scan_timeout();
            }
                break;
            case WZD_NW_TIMER_WIFI_SSID_SCAN:
            case WZD_NW_TIMER_WIFI_ASSOC:
			case WZD_NW_TIMER_WIFI_PWD_ASSOC:
			{
            	_wzd_nw_wifi_assoc_timeout();
			}
				break;
            case WZD_NW_TIMER_TEST_CONN:
            {
                _wzd_nw_test_conn_timeout();
            }
                break;
            default:
                break;
        }
        return;
    }

	/* handle task complete */
    switch(e_wzd_nw_timer)
    {
        case WZD_NW_TIMER_LAN_ASSOC:
        {
            BOOL b_wired_plug = FALSE;
      		a_nw_get_ethernet_connect_info(&b_wired_plug);

            if (TRUE == b_wired_plug && a_wzd_is_resume_from_menu_setup())/*enter from menu*/
            {
        		_wzd_nw_lan_assoc_result();
				return;
            }
            if(TRUE == t_wzd_nw.b_timer_result)
            {
                _wzd_nw_lan_assoc_result();
                return;
            }
        }
            break;
        case WZD_NW_TIMER_WIFI_SCAN:
        {
            if(TRUE == t_wzd_nw.b_timer_result)
            {
				_wzd_nw_wifi_scan_result();
                return;
            }
        }
            break;
        case WZD_NW_TIMER_WIFI_SSID_SCAN:
        {
            if(TRUE == t_wzd_nw.b_timer_result)
            {
                if (_wzd_nw_is_ssid_scan_success())
                {
                    t_wzd_nw.ui4_start_time = 0;
                    t_wzd_nw.b_is_busying = FALSE;
                    _wzd_nw_ssid_wifi_assoc();
                    return;
                }
                else
                {
                    if (ui2_g_ssid_scan_count >= WZD_WIFI_SSID_SCAN_COUNT)
                    {
                        _wzd_nw_wifi_assoc_timeout();
                        return;
                    }
					else
					{
	                    t_wzd_nw.b_timer_result = FALSE;
	                    ui2_g_ssid_scan_count++;

	                    a_nw_wlan_scan_with_ssid(t_wzd_nw.s_ssid_buf,
									c_strlen(t_wzd_nw.s_ssid_buf));
					}
                }
            }
        }
            break;
        case WZD_NW_TIMER_WIFI_ASSOC:
        case WZD_NW_TIMER_WIFI_PWD_ASSOC:
		{
			if(TRUE == t_wzd_nw.b_timer_result)
	        {
	            _wzd_nw_wifi_assoc_result();
	            return;
	        }
		}
			break;
        case WZD_NW_TIMER_TEST_CONN:
        {
            if(TRUE == t_wzd_nw.b_timer_result)
            {
                _wzd_nw_test_conn_result();
                return;
            }
        }
            break;
        default:
            break;
    }

    _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);

    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_timer_notify_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_timer_notify_fct(HANDLE_T  pt_tm_handle,
                                     VOID*     pv_tag)
{
    UINT16  ui2_status;
    UINT8  ui2_page_idx;
    //UINT8  ui2_state;

    a_cfg_get_wzd_status (& ui2_status);

    //ui2_state   = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui2_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);

    if(ui2_page_idx == WZD_PAGE_INDEX_NW_SETUP)
    {
        wzd_async_invoke(_wzd_nw_do_timer_nfy, pv_tag, (SIZE_T)sizeof(WZD_NW_TIMER_E), TRUE);
    }

    return;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_timer_start
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_timer_start (VOID* pv_data,
                                 SIZE_T  z_data_size)
{
     c_timer_start(t_wzd_nw.t_choice_connect.h_timer,
                   1000,
                   X_TIMER_FLAG_ONCE,
                   _wzd_nw_timer_notify_fct,
                   pv_data);
    return ;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_update_curr_connect_status
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_update_curr_connect_status (VOID)
{
    NET_802_11_BSS_INFO_T   t_CurrBss;
    INT32                   i4_ret;

	/* get current connected bss info */
	c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    if(i4_ret != NWR_OK)
    {
        c_memset(t_CurrBss.t_Bssid, 0, sizeof(t_CurrBss.t_Bssid));
        t_CurrBss.t_Ssid.ui4_SsidLen = 0;
    }
	if ((t_CurrBss.t_Ssid.ui4_SsidLen > 0)
        &&((UINT8)WLAN_WPA_COMPLETED == t_CurrBss.u8_wpa_status))
    {
        t_wzd_nw.t_choice_connect.b_connected = TRUE;
    }
	else
	{
		t_wzd_nw.t_choice_connect.b_connected = FALSE;
	}

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_title_text_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_title_text_create (HANDLE_T  		h_parent,
	                                   GL_RECT_T*		pt_rect,
	                                   WGL_COLOR_INFO_T*	pt_color_fg,
	                                   HANDLE_T* 		ph_txt)
{
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

	/* create widget */
	RET_ON_ERR (c_wgl_create_widget(h_parent,
								HT_WGL_WIDGET_TEXT,
								WGL_CONTENT_TEXT_DEF,
								WGL_BORDER_NULL,
								pt_rect,
								NULL,
								255,
								(VOID*)( WGL_STL_TEXT_MAX_2048 |
								      WGL_STL_TEXT_MULTILINE |
								      WGL_STL_TEXT_MAX_DIS_10_LINE),
								NULL,
								ph_txt));

	/* set font size */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

	RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (&t_fnt_info),
                              NULL));

    /* set content inset */
	t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

	RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              &t_inset,
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_CENTER_CENTER),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
	t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (&t_clr_info.u_color_data.t_standard.t_enable,    &t_g_wzd_color_network_frame_bk);
    COLOR_COPY (&t_clr_info.u_color_data.t_standard.t_disable,   &t_g_wzd_color_network_frame_bk);
    COLOR_COPY (&t_clr_info.u_color_data.t_standard.t_highlight, &t_g_wzd_color_network_frame_bk);
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (&t_clr_info)));

    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (pt_color_fg)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (*ph_txt, WGL_SW_HIDE));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_frm_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_frm_create(HANDLE_T              h_parent,
                                UINT16                ui2_left,
                                UINT16                ui2_top,
                                UINT16                ui2_width,
                                UINT16                ui2_height,
                                wgl_widget_proc_fct   pf_wgl_nfy_fct,
                                HANDLE_T*             ph_frame)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     ui2_left,
                     ui2_top,
                     ui2_width,
                     ui2_height);

    /* create widget */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wgl_nfy_fct,
                                 255,
                                 (VOID*) WGL_STL_GL_NO_IMG_UI,
                                 0,
                                 ph_frame);
    RET_ON_ERR(i4_ret);

    /* set theme */
    c_memset(&t_color_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_network_frame_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_network_frame_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_network_frame_bk);

    i4_ret= c_wgl_do_cmd(*ph_frame,
                         WGL_CMD_GL_SET_COLOR,
                         WGL_PACK (WGL_CLR_BK), /* background color */
                         WGL_PACK (&t_color_info));
    RET_ON_ERR(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility (*ph_frame, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_network_info_reg_check_box_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_network_info_reg_check_box_create (HANDLE_T  h_parent,
			                                         INT32     i4_left,
			                                         INT32     i4_top,
			                                         HANDLE_T* ph_widget)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_INSET_T                 t_inset_border;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      i4_top,
                      WZD_NW_INFO_REG_CB_W,
                      WZD_NW_INFO_REG_CB_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 _wzd_nw_info_check_box_proc_fct,
                                 255,
                                 (void*)(WGL_STL_BTN_CHECKBOX),
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* Set Insets */
    c_memset(&t_inset_border, 0, sizeof(WGL_INSET_T));
    t_inset_border.i4_left     = 0;
    t_inset_border.i4_right    = 0;
    t_inset_border.i4_top      = 0;
    t_inset_border.i4_bottom   = 0;

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    RET_ON_ERR(i4_ret);


    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* set background image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_disable            = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push               = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info) );
    RET_ON_ERR(i4_ret);

    /* set foreground image */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_wzd_img_checkbox;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_wzd_img_checkbox;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_checkbox_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_wzd_img_checkbox_hlt;
    t_img_info.u_img_data.t_extend.t_push               = h_g_wzd_img_checkbox_check_hlt;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_wzd_img_checkbox_check;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info) );
    RET_ON_ERR(i4_ret);

    /* Set Border colors and images */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_network_txt_nor;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_network_txt_nor;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_network_txt_nor;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    RET_ON_ERR(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size  = 15;
    /* Set Border Title */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      0,
                      0,
                      2 * WZD_UI_RATIO_W,
                      2 * WZD_UI_RATIO_W);

    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    RET_ON_ERR(i4_ret);

	/* Create text widget for check box title*/
	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      WZD_NW_INFO_REG_CB_TITLE_X,
                      WZD_NW_INFO_REG_CB_TITLE_Y,
                      WZD_NW_INFO_REG_CB_TITLE_W,
                      WZD_NW_INFO_REG_CB_TITLE_H);

	i4_ret = c_wgl_create_widget(
					   h_parent,
					   HT_WGL_WIDGET_TEXT,
					   WGL_CONTENT_TEXT_DEF,
					   WGL_BORDER_UNIFORM,
					   &t_rect,
					   NULL,
					   255,
					   (VOID *)(WGL_STL_GL_NO_IMG_UI |
							    WGL_STL_TEXT_MULTILINE|
							    WGL_STL_TEXT_MULTISTRING|
							    WGL_STL_TEXT_MAX_2048),
					   NULL,
					   &(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title));
	RET_ON_ERR(i4_ret);

	c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title, WGL_SW_NORMAL);

	/* Set font of text */
	c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strncpy (t_fnt_info.a_c_font_name, WZD_FONT_S_NAME, WGL_MAX_FONT_NAME-1);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size  = 25;

	i4_ret = c_wgl_do_cmd(
					t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title,
					WGL_CMD_GL_SET_FONT,
					(VOID*)&t_fnt_info,
					NULL);
	RET_ON_ERR(i4_ret);

	/* Set text color of text */
	c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_network_txt_hlt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_network_txt_hlt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_network_txt_hlt;
	i4_ret = c_wgl_do_cmd(
					t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title,
					WGL_CMD_GL_SET_COLOR,
					WGL_PACK(WGL_CLR_TEXT),
					WGL_PACK(&t_clr_info));
	RET_ON_ERR(i4_ret);

	/* Set the alignment of string */
	i4_ret = c_wgl_do_cmd(
					t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title,
					WGL_CMD_TEXT_SET_ALIGN,
					(VOID*)WGL_AS_LEFT_CENTER,
					NULL);
	RET_ON_ERR(i4_ret);

	/* Create text widget for check box title1*/
	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      WZD_NW_INFO_REG_CB_TITLE1_X,
                      WZD_NW_INFO_REG_CB_TITLE1_Y,
                      WZD_NW_INFO_REG_CB_TITLE1_W,
                      WZD_NW_INFO_REG_CB_TITLE1_H);

	i4_ret = c_wgl_create_widget(
					   h_parent,
					   HT_WGL_WIDGET_TEXT,
					   WGL_CONTENT_TEXT_DEF,
					   WGL_BORDER_UNIFORM,
					   &t_rect,
					   NULL,
					   255,
					   (VOID *)(WGL_STL_GL_NO_IMG_UI |
							    WGL_STL_TEXT_MULTILINE|
							    WGL_STL_TEXT_MULTISTRING|
							    WGL_STL_TEXT_MAX_2048),
					   NULL,
					   &(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title1));
	RET_ON_ERR(i4_ret);

	c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title1, WGL_SW_NORMAL);

	/* Set font of text */
	c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strncpy (t_fnt_info.a_c_font_name, WZD_FONT_S_NAME, WGL_MAX_FONT_NAME-1);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size  = 20;

	i4_ret = c_wgl_do_cmd(
					t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title1,
					WGL_CMD_GL_SET_FONT,
					(VOID*)&t_fnt_info,
					NULL);
	RET_ON_ERR(i4_ret);

	/* Set text color of text */
	c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_network_txt_nor;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_network_txt_nor;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_network_txt_nor;
	i4_ret = c_wgl_do_cmd(
					t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title1,
					WGL_CMD_GL_SET_COLOR,
					WGL_PACK(WGL_CLR_TEXT),
					WGL_PACK(&t_clr_info));
	RET_ON_ERR(i4_ret);

	/* Set the alignment of string */
	i4_ret = c_wgl_do_cmd(
					t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title1,
					WGL_CMD_TEXT_SET_ALIGN,
					(VOID*)WGL_AS_LEFT_CENTER,
					NULL);
	RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_show_first_page
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _wzd_nw_protocol_text_show_first_page(VOID* pv_data,
                                                  SIZE_T  z_data_size)
{
    WZD_NW_TEXT_T*    ph_protocol_text = (WZD_NW_TEXT_T*)pv_data;

    if (ph_protocol_text->h_text != NULL_HANDLE)
    {
        c_txt_get_page_data(ph_protocol_text->h_text,
                            (UINT32)1,
                            _wzd_nw_protocol_text_show_nfy_cb,
                            NULL);
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_show_nfy_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_protocol_text_show_nfy_cb(
                            HANDLE_T                    h_handle,
                            const VOID*                 pv_pt_txt,
                            TXT_ASYNC_COND_T            e_event,
                            const VOID*                 pv_data)
{
    UINT16      ui2_rows;

    switch(e_event)
    {
        case TXT_ASYNC_COND_SCANING:
            t_wzd_nw.t_protocol.ui4_pro_total_page = (UINT32)pv_data;

            if (1 == t_wzd_nw.t_protocol.ui4_pro_total_page)
            {
                c_txt_get_page_rows(h_handle, &ui2_rows);
                t_wzd_nw.t_protocol.ui4_pre_page_rows = ui2_rows;
                t_wzd_nw.t_protocol.ui4_pro_cur_rows = t_wzd_nw.t_protocol.ui4_pre_page_rows;
                t_wzd_nw.t_protocol.ui4_pro_total_rows = 100;   /* this value is just for enable down icon when scanning text*/
                if (t_wzd_nw.t_protocol.t_protocol_terms.h_text == h_handle)
                {
                    wzd_async_invoke(_wzd_nw_protocol_text_show_first_page,(VOID*)(&t_wzd_nw.t_protocol.t_protocol_terms),sizeof(WZD_NW_TEXT_T),TRUE);
                }
                else
                {
                    wzd_async_invoke(_wzd_nw_protocol_text_show_first_page,(VOID*)(&t_wzd_nw.t_protocol.t_protocol_policy),sizeof(WZD_NW_TEXT_T),TRUE);
                }
            }

             break;
        case TXT_ASYNC_COND_SCAN_FINISH:
            t_wzd_nw.t_protocol.ui4_pro_total_page = (UINT32)pv_data;
            t_wzd_nw.t_protocol.ui4_pro_total_rows = t_wzd_nw.t_protocol.ui4_pre_page_rows * (t_wzd_nw.t_protocol.ui4_pro_total_page - 1);
            c_txt_get_last_page_rows(h_handle,&ui2_rows);
            t_wzd_nw.t_protocol.ui4_pro_total_rows = t_wzd_nw.t_protocol.ui4_pro_total_rows + ui2_rows;
            break;
        case TXT_ASYNC_COND_GET_DATA:
            if (t_wzd_nw.t_protocol.t_protocol_terms.h_text == h_handle)
            {
                c_wgl_repaint(t_wzd_nw.t_protocol.t_protocol_terms.h_text_widget,NULL,TRUE);
            }
            else
            {
                c_wgl_repaint(t_wzd_nw.t_protocol.t_protocol_policy.h_text_widget,NULL,TRUE);
            }
            break;
        case TXT_ASYNC_COND_GET_DATA_FAIL:
            break;
        case TXT_ASYNC_COND_MAX:
            break;
        case TXT_ASYNC_COND_SCAN_ABORT:
            break;
    }
    return;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_show_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  _wzd_nw_protocol_text_show_open(const CHAR*     ps_filename,
                                              HANDLE_T*       ph_widget,
                                              HANDLE_T*       ph_text)
{
    INT32           i4_ret;
    TXT_SET_CMD_T   pt_cmd[1];
    INT16           ui2_idx;

    do
    {
        /* open txt file */
        i4_ret = c_txt_open(ps_filename,
                            c_strlen(ps_filename),
                            TXT_RW_FILE_MODE,
                            _wzd_nw_protocol_text_show_nfy_cb,
                            NULL,
                            ph_text,
                            TXT_FILE_SRC_TYPE);
        if (i4_ret != WZDR_OK)
        {
            *ph_text = NULL_HANDLE;
            break;
        }

        /* Set attribute to mw */

        /* Set ecode */
        ui2_idx = 0;
        pt_cmd[ui2_idx].e_set_attr_type   = TXT_SET_ENCODE;
#ifdef APP_DYNAMIC_TOS_SUPPORT
        pt_cmd[ui2_idx].pv_param          = (VOID*)TXT_ECODE_UTF8;
#else
        pt_cmd[ui2_idx].pv_param          = (VOID*)TXT_ECODE_UNICODE;
#endif
        i4_ret = c_txt_set_attr(*ph_text, 1,pt_cmd);
        if (i4_ret != WZDR_OK)
        {
            c_txt_close(*ph_text);
            *ph_text = NULL_HANDLE;
            break;
        }

        /* Set font */
        pt_cmd[ui2_idx].e_set_attr_type   = TXT_SET_WGL_HANDLE;
        pt_cmd[ui2_idx].pv_param          = (VOID*)ph_widget;

        i4_ret = c_txt_set_attr(*ph_text, 1, pt_cmd);
        if (i4_ret != WZDR_OK)
        {
            c_txt_close(*ph_text);
            *ph_text = NULL_HANDLE;
            break;
        }

		return WZDR_OK;

    }while(0);

    return WZDR_FAIL;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_show_cancel_scan
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  _wzd_nw_protocol_text_show_cancel_scan(HANDLE_T*    ph_text)
{
    INT32   i4_ret;

    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_cancel_scan(*ph_text);
        RET_ON_ERR(i4_ret);
    }
    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_show_start_scan
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  _wzd_nw_protocol_text_show_start_scan(HANDLE_T*    ph_text)
{
    INT32   i4_ret;

    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_scan(*ph_text,UI4_TXT_INVALUED,_wzd_nw_protocol_text_show_nfy_cb,NULL);
        RET_ON_ERR(i4_ret);
    }
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_show_close
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_show_close(HANDLE_T* ph_text)
{
    INT32   i4_ret;
    if (*ph_text != NULL_HANDLE)
    {
        i4_ret = c_txt_close(*ph_text);
        RET_ON_ERR(i4_ret);
        *ph_text = NULL_HANDLE;
    }
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_text_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_text_create (HANDLE_T  h_parent,
                                  INT32     i4_left,
                                  INT32     i4_top,
                                  INT32     i4_width,
                                  INT32     i4_height,
                                  HANDLE_T  h_normal_bk,
                                  HANDLE_T  h_highlight_bk,
                                  HANDLE_T* ph_widget)
{

    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      i4_top,
                      i4_width,
                      i4_height);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)( WGL_STL_TEXT_MAX_2048 |
                                          WGL_STL_TEXT_MULTILINE |
                                          WGL_STL_TEXT_MAX_DIS_10_LINE),
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK (WGL_AS_LEFT_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);


    t_inset.i4_left     = WZD_NW_LEFT_INSET;
    t_inset.i4_right    = WZD_NW_RIGHT_INSET;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          (VOID*)(INT32)(0),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size  = 15;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    RET_ON_ERR(i4_ret);

    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_wzd_color_network_txt_nor);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_wzd_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_wzd_color_network_txt_nor);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_icon_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_icon_proc_fct (HANDLE_T   h_widget,
 	                                              UINT32     ui4_msg,
 	                                              VOID*      param1,
 	                                              VOID*      param2)
{
    UINT32 ui4_keycode = (UINT32)param1;

    /* respond repeat msg for select button */
    if (WGL_MSG_KEY_REPEAT == ui4_msg && BTN_SELECT == ui4_keycode)
    {
        ui4_msg = WGL_MSG_KEY_DOWN;
    }

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        switch (ui4_keycode)
        {
            case BTN_SELECT:
                if (h_widget == t_wzd_nw.t_protocol.t_protocol_terms.h_icon_up)
				{
					_wzd_nw_protocol_text_show_prev_row(t_wzd_nw.t_protocol.t_protocol_terms.h_text_widget,
						                         		t_wzd_nw.t_protocol.t_protocol_terms.h_text);
				}
				else if (h_widget == t_wzd_nw.t_protocol.t_protocol_terms.h_icon_down)
				{
					_wzd_nw_protocol_text_show_next_row(t_wzd_nw.t_protocol.t_protocol_terms.h_text_widget,
					              						t_wzd_nw.t_protocol.t_protocol_terms.h_text);
				}
				else if (h_widget == t_wzd_nw.t_protocol.t_protocol_policy.h_icon_up)
				{
					_wzd_nw_protocol_text_show_prev_row(t_wzd_nw.t_protocol.t_protocol_policy.h_text_widget,
						                         		t_wzd_nw.t_protocol.t_protocol_policy.h_text);
				}
				else if (h_widget == t_wzd_nw.t_protocol.t_protocol_policy.h_icon_down)
				{
					_wzd_nw_protocol_text_show_next_row(t_wzd_nw.t_protocol.t_protocol_policy.h_text_widget,
					              						t_wzd_nw.t_protocol.t_protocol_policy.h_text);
				}

                return WZDR_OK;

            case BTN_CURSOR_UP:
				if (h_widget == t_wzd_nw.t_protocol.t_protocol_terms.h_icon_down)
				{
					RET_ON_ERR (c_wgl_float(t_wzd_nw.t_protocol.t_protocol_terms.h_icon_up, TRUE, FALSE));
					RET_ON_ERR (c_wgl_set_focus(t_wzd_nw.t_protocol.t_protocol_terms.h_icon_up, WGL_SYNC_AUTO_REPAINT));
				}
				else if (h_widget == t_wzd_nw.t_protocol.t_protocol_policy.h_icon_down)
				{
					RET_ON_ERR (c_wgl_float(t_wzd_nw.t_protocol.t_protocol_policy.h_icon_up, TRUE, FALSE));
					RET_ON_ERR (c_wgl_set_focus(t_wzd_nw.t_protocol.t_protocol_policy.h_icon_up, WGL_SYNC_AUTO_REPAINT));
				}

                return WZDR_OK;

            case BTN_CURSOR_DOWN:
				RET_ON_ERR (c_wgl_float(h_widget, FALSE, FALSE));

				if (h_widget == t_wzd_nw.t_protocol.t_protocol_terms.h_icon_up)
				{
					RET_ON_ERR (c_wgl_float(t_wzd_nw.t_protocol.t_protocol_terms.h_icon_down, TRUE, FALSE));
					RET_ON_ERR (c_wgl_set_focus(t_wzd_nw.t_protocol.t_protocol_terms.h_icon_down, WGL_SYNC_AUTO_REPAINT));
				}
				else if (h_widget == t_wzd_nw.t_protocol.t_protocol_terms.h_icon_down)
				{
					RET_ON_ERR (_wzd_nw_footer_btn_focus());
				}
				else if (h_widget == t_wzd_nw.t_protocol.t_protocol_policy.h_icon_up)
				{
					RET_ON_ERR (c_wgl_float(t_wzd_nw.t_protocol.t_protocol_policy.h_icon_down, TRUE, FALSE));
					RET_ON_ERR (c_wgl_set_focus(t_wzd_nw.t_protocol.t_protocol_policy.h_icon_down, WGL_SYNC_AUTO_REPAINT));
				}
				else if (h_widget == t_wzd_nw.t_protocol.t_protocol_policy.h_icon_down)
				{
					RET_ON_ERR (_wzd_nw_footer_btn_focus());
				}

                return WZDR_OK;

        default:
            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

#ifdef APP_DYNAMIC_TOS_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_error_msg_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_error_msg_create(HANDLE_T h_parent)
{
    INT32     			i4_ret;
	WGL_FONT_INFO_T		t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;

	i4_ret = _wzd_nw_text_create(
                         h_parent,
                         WZD_NW_FRAME_X,
                         WZD_NW_TXT_CNT_Y,
                         WZD_NW_FRAME_W,
                         WZD_NW_TXT_CNT_H,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &t_wzd_nw.t_protocol.h_error_text
                         );
    RET_ON_ERR(i4_ret);

	/* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());
	t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (t_wzd_nw.t_protocol.h_error_text,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_wzd_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_wzd_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_wzd_color_network_txt_hlt);
    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_protocol.h_error_text,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    /* set alignment */
	i4_ret = c_wgl_do_cmd(t_wzd_nw.t_protocol.h_error_text,
     					  WGL_CMD_TEXT_SET_ALIGN,
     					  WGL_PACK(WGL_AS_CENTER_CENTER),
     					  NULL);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.t_protocol.h_error_text, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_error_msg_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_error_msg_show(VOID)
{
    INT32     		i4_ret;
    UTF16_T*        pw2s_text = NULL;
    TOS_TYPE_T      e_tos_type = TOS_TYPE_LAST_VALID_ITEM;

    e_tos_type = _wzd_tos_get_type();

    if (e_tos_type <= TOS_TYPE_TOS_SPA)
    {
        pw2s_text = WZD_TEXT(MLM_WZD_KEY_NW_SETUP_TERMS_DOWNLOAD_FAILED);
    }
    else
    {
        pw2s_text = WZD_TEXT(MLM_WZD_KEY_NW_SETUP_POLICY_DOWNLOAD_FAILED);
    }

    i4_ret = c_wgl_do_cmd (t_wzd_nw.t_protocol.h_error_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.t_protocol.h_error_text, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(t_wzd_nw.t_protocol.h_protocol_frame, NULL, TRUE);
	RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_error_msg_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_error_msg_hide(VOID)
{
    INT32     		i4_ret;

    i4_ret = c_wgl_do_cmd (t_wzd_nw.t_protocol.h_error_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          (VOID*)NULL,
                          (VOID*)0);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.t_protocol.h_error_text, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_icon_create(HANDLE_T  h_parent,
                                               INT32     i4_left,
                                               INT32     i4_top,
                                               INT32     i4_width,
                                               INT32     i4_height,
                                               HANDLE_T  h_normal_bk,
                                               HANDLE_T  h_highlight_bk,
                                               HANDLE_T* ph_widget)
{
    INT32   i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     i4_left,
                     i4_top,
                     i4_width,
                     i4_height);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _wzd_nw_protocol_text_icon_proc_fct,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,
                                 WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_show_prev_row
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_show_prev_row(HANDLE_T     h_text_widget,
                                                 HANDLE_T     h_text)
{
    if (t_wzd_nw.t_protocol.ui4_pro_cur_rows > t_wzd_nw.t_protocol.ui4_pre_page_rows)
    {
        t_wzd_nw.t_protocol.ui4_pro_cur_rows -= 1;
    }

    if (h_text != NULL_HANDLE)
    {
        c_txt_scroll_up_row(h_text,(UINT16)1);
    }
    c_wgl_repaint(h_text_widget,NULL,TRUE);
    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _protocol_text_show_next_page
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_show_next_row(HANDLE_T     h_text_widget,
                                                 HANDLE_T     h_text)
{
    if (t_wzd_nw.t_protocol.ui4_pro_cur_rows < t_wzd_nw.t_protocol.ui4_pro_total_rows)
    {
        t_wzd_nw.t_protocol.ui4_pro_cur_rows += 1;
    }

    if (h_text != NULL_HANDLE)
    {
        c_txt_scroll_down_row(h_text,(UINT16)1);
    }
    c_wgl_repaint(h_text_widget,NULL,TRUE);
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_show_exit_scan
 *
 * Description:
 *
 * Inputs:	-
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_show_exit_scan(VOID)
{
	c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame, WGL_SW_HIDE_RECURSIVE);
	c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame, WGL_SW_NORMAL);

	c_wgl_set_visibility(t_wzd_nw.t_protocol.t_protocol_terms.h_widget, WGL_SW_NORMAL);
	c_wgl_set_visibility(t_wzd_nw.t_protocol.t_protocol_policy.h_widget, WGL_SW_NORMAL);

    if (WZD_NW_PROTOCOL_SCAN_TERMS == t_wzd_nw.t_protocol.e_scan_text)
    {
        _wzd_nw_protocol_text_show_cancel_scan(&t_wzd_nw.t_protocol.t_protocol_terms.h_text);
		_wzd_nw_text_set_text(t_wzd_nw.t_protocol.t_protocol_terms.h_text_widget, MLM_WZD_KEY_EMPTY);
    }
    else if(WZD_NW_PROTOCOL_SCAN_POLICY == t_wzd_nw.t_protocol.e_scan_text)
    {
        _wzd_nw_protocol_text_show_cancel_scan(&t_wzd_nw.t_protocol.t_protocol_policy.h_text);
		_wzd_nw_text_set_text(t_wzd_nw.t_protocol.t_protocol_policy.h_text_widget, MLM_WZD_KEY_EMPTY);
    }

	t_wzd_nw.t_protocol.e_scan_text = WZD_NW_PROTOCOL_SCAN_NULL;

	/* update protocol state footer */
    _wzd_nw_help_lst_update(NW_SETUP_STATE_PROTOCOL, FALSE);

	/* set focus to "I accept" button */
	RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE));

	RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_TITLE_TOS_AND_POLICY), NULL_HANDLE));
	RET_ON_ERR (wzd_view_main_frm_repaint());

	return WZDR_OK;
}

#ifdef ________________________________________________________JUST_FOR_DIVISION
#endif
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_assoc_dlg_data_chg
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
VOID _wzd_nw_assoc_dlg_data_chg (VOID*    pv_tag,
	                             UINT32   ui4_msg,
	                             VOID*    pv_param1,
	                             VOID*    pv_param2)
{
	NW_SETUP_STATE e_temp_pre_state = NW_SETUP_STATE_BEGIN;

    switch( ui4_msg )
    {
        case WZD_DLG_MSG_BTN_FOCUSED:
            DBG_LOG_PRINT(( "[WZD][DLG] WZD_DLG_MSG_BTN_FOCUSED received, btn index =%d\n", (UINT32)pv_param1 ));
            break;

        case WZD_DLG_MSG_KEY_INPUT:
            if( BTN_SELECT == (UINT32)pv_param1 )
            {
                DBG_LOG_PRINT(( "[WZD][DLG] WZD_DLG_MSG_KEY_INPUT received, btn index =%d\n", (UINT32)pv_param1 ));

				/* Try another network */
                if (WZD_DLG_BTN_TYPE_01 == (WZD_DLG_BTN_TYPE_T)(UINT32)pv_param2)
                {
                	if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE)
                	{
                		/* reset flags */
                        e_g_nw_setup_pre_state = NW_SETUP_STATE_BEGIN;
                        e_g_nw_setup_state = NW_SETUP_STATE_BEGIN;
                	}

                    if (t_wzd_nw.t_choice_connect.ui1_visiable_ap_num <= 0)
					{
						_wzd_nw_conn_lan_or_wifi();
					}
					else
					{
						/* back wlan result page */
                		_wzd_nw_go(NW_SETUP_STATE_WIRELESS_SCAN_RESULT, TRUE);
					}
                }
                else    /* Try again */
				{
					/* hide dialog */
                    wzd_dlg_hide(t_wzd_nw.h_dlg);

					/* current associate ap is NOT lock ap */
					if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCAN_RESULT)
                	{
                		NET_802_11_ASSOCIATE_T* 	pt_associate = NULL;

						SHOW_ON_ERR (_wzd_nw_get_associate_data(&pt_associate));
						if(pt_associate == NULL)
					    {
					        return;
					    }

						SHOW_ON_ERR (a_nw_custom_wlan_disassociate());
						SHOW_ON_ERR (a_nw_wlan_associate(pt_associate));

			            t_wzd_nw.b_is_busying = TRUE;
			            t_wzd_nw.b_timer_result = FALSE;
			            t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

						SHOW_ON_ERR (_wzd_nw_full_screen_icon_update(FALSE));

						SHOW_ON_ERR (wzd_view_full_screen_dlg_set_text (
										WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTING_NETWORK),
										FALSE));

						SHOW_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));

			            t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_WIFI_ASSOC;
			            _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);
                	}
					else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE)
                	{
                		/* store previous state */
						e_temp_pre_state = e_g_nw_setup_pre_state;

						/* start WPS */
						_wzd_nw_wps_associate();

						/* restore previous state */
						e_g_nw_setup_pre_state = e_temp_pre_state;
                	}
					else
					{
						if (t_wzd_nw.h_last_focused_wdg != NULL_HANDLE)
						{
			            	c_wgl_set_focus(t_wzd_nw.h_last_focused_wdg, TRUE);
						}
					}
                }

				t_wzd_nw.h_last_focused_wdg = NULL_HANDLE;
            }
            break;

        case WZD_DLG_MSG_DLG_HIDED:
            DBG_LOG_PRINT(( "[WZD][DLG] WZD_DLG_MSG_DLG_HIDED received\n" ));
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_nw_assoc_dlg_create
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_nw_assoc_dlg_create (VOID)
{
    WZD_DLG_INIT_T      t_dlg_init;
    HANDLE_T            h_layout_frm = NULL_HANDLE;
	UTF16_T     	    w2s_ssid [WZD_NW_SSID_MAX_LEN+1] = {0};
	UTF16_T             w2s_msg [127+1] = {0};
    UTF16_T*            pw2s_dlg_text = NULL;
    UTF16_T*            pw2s_dlg_btn1_text = NULL;
    UTF16_T*            pw2s_dlg_btn2_text = NULL;
	NET_802_11_ASSOCIATE_T*	pt_associate = NULL;

	DBG_LOG_PRINT(("[WZD][NW] --- ASSOC FAILED SSID: %s.\n", w2s_ssid));

    c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.ui4_hide_timer = 10*1000;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;
    t_dlg_init.pf_fct = _wzd_nw_assoc_dlg_data_chg;
	t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_AUTO_HIDE;

	/* previous state is ssid input, should show ssid name */
	if (NW_SETUP_STATE_WIRELESS_SSID_INPUT == e_g_nw_setup_state)
	{
		DBG_LOG_PRINT(("[WZD][NW] --- current state: SSID_INPUT! : %s.\n", w2s_ssid));
		c_uc_w2s_strncpy(w2s_ssid, t_wzd_nw.aw2s_ssid_context, WZD_NW_SSID_MAX_LEN);
	}
	else
	{
		/* get associate ap information */
		_wzd_nw_get_associate_data(&pt_associate);
	    if(pt_associate == NULL)
	    {
	    	DBG_LOG_PRINT(("[WZD][NW] --- %s %d, WIFI ASSOC DATA is NULL.\n", __FUNCTION__,__LINE__));
			return WZDR_FAIL;
	    }

		c_uc_ps_to_w2s(pt_associate->t_Ssid.ui1_aSsid, w2s_ssid, pt_associate->t_Ssid.ui4_SsidLen);
    	w2s_ssid[pt_associate->t_Ssid.ui4_SsidLen]= (UTF16_T)0;
	}

#if 0
	if (NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE == e_g_nw_setup_state)
	{
		c_uc_w2s_strcat (w2s_msg, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_WPS_CONN_FAIL));
	}
	else if (c_uc_w2s_strlen(w2s_ssid) == 0)
	{
		/* ssid length is 0 */
		c_uc_w2s_strcat (w2s_msg, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_NETWORK_CONN_FAIL));
	}
	else
	{
		c_uc_w2s_strcat (w2s_msg, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_UNABLE_JOIN));
		c_uc_w2s_strcat (w2s_msg, w2s_ssid);
	}
#else
	if (c_uc_w2s_strlen(w2s_ssid) == 0)
	{
		/* ssid length is 0 */
		c_uc_w2s_strcat (w2s_msg, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_NETWORK_CONN_FAIL));
	}
	else
	{
		c_uc_w2s_strcat (w2s_msg, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_UNABLE_JOIN));
		c_uc_w2s_strcat (w2s_msg, w2s_ssid);
	}
#endif

    pw2s_dlg_text = w2s_msg;
	pw2s_dlg_btn1_text = WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_TRY_ANOTHER_NW);
    pw2s_dlg_btn2_text = WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_TRY_AGAIN);

    wzd_dlg_create( &t_dlg_init, &t_wzd_nw.h_dlg );

    wzd_dlg_set_text( t_wzd_nw.h_dlg, pw2s_dlg_text, FALSE );
    wzd_dlg_set_btn_text( t_wzd_nw.h_dlg, WZD_DLG_BTN_TYPE_01,
                          pw2s_dlg_btn1_text, FALSE );
    wzd_dlg_set_btn_text( t_wzd_nw.h_dlg, WZD_DLG_BTN_TYPE_02,
                          pw2s_dlg_btn2_text, FALSE );

    wzd_dlg_show( t_wzd_nw.h_dlg , TRUE );

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_leave_this_page
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_leave_this_page(VOID)
{
	UINT16  	ui2_status = APP_CFG_WZD_STATUS_INIT;

    e_g_nw_setup_state = NW_SETUP_STATE_BEGIN;
    e_g_nw_setup_pre_state = NW_SETUP_STATE_BEGIN;

	a_cfg_get_wzd_status(&ui2_status);
    ui2_status = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    if (ui2_status == 0xFFFF ||
        ui2_status == APP_CFG_WZD_STATUS_INIT ||
        ui2_status == WZD_STATE_START_SETUP)
    {
        wzd_page_goto(WZD_PAGE_NAVI_NEXT_PAGE);
    }
    else if (a_wzd_is_resume_from_menu_setup())
    {
        a_wzd_exit();
    }
    else
    {
        wzd_page_goto( WZD_PAGE_NAVI_LAST_VALID_ITEM );
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _skip_confirm_dlg_reg_back_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _skip_confirm_dlg_reg_back_proc_fct(VOID*      pv_tag,
                                          UINT32     ui4_msg,
                                          VOID*      param1,
                                          VOID*      param2)
{
    INT32  i4_ret;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
				i4_ret = wzd_dlg_hide(t_wzd_nw.h_dlg);
				SHOW_ON_ERR(i4_ret);

				if (e_g_nw_setup_state == NW_SETUP_STATE_NONE_CONN)
				{
					i4_ret = wzd_view_footer_set_focus(WZD_FOOTER_BTN_03, FALSE);
					SHOW_ON_ERR(i4_ret);
				}
                else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCANNING)
                {
                    _wzd_nw_conn_lan_or_wifi();
                }
				else
				{
					i4_ret = wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, FALSE);
					SHOW_ON_ERR(i4_ret);
				}

				i4_ret = wzd_view_main_frm_repaint();
				SHOW_ON_ERR(i4_ret);
            }
            break;
        default:
            break;
        }
    }
    default:
        break;
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _skip_confirm_dlg_reg_skip_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _skip_confirm_dlg_reg_skip_proc_fct(VOID*      pv_tag,
	                                            UINT32     ui4_msg,
	                                            VOID*      param1,
	                                            VOID*      param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
				_wzd_nw_leave_this_page();
            }
            break;
        default:
            break;
        }
    }
    default:
        break;
    }

    return;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_skip_dlg_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_skip_dlg_proc_fct(VOID*      pv_tag,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    static wzd_dlg_data_change_nfy_fct  pf_fct = NULL;

    if(WZD_DLG_MSG_BTN_FOCUSED == ui4_msg)
    {
        WZD_DLG_BTN_TYPE_T  t_btn_id = (WZD_DLG_BTN_TYPE_T)(UINT32)param1;
        WZD_NW_DLG_T        t_dlg_type = (WZD_NW_DLG_T)(UINT32)pv_tag;

        switch (t_dlg_type)
        {
            case WZD_NW_DLG_1:
			case WZD_NW_DLG_2:
            case WZD_NW_DLG_3:
		        if(WZD_DLG_BTN_TYPE_01 == t_btn_id)
		        {
		            pf_fct = _skip_confirm_dlg_reg_back_proc_fct;
		        }
		        else
		        {
		            pf_fct = _skip_confirm_dlg_reg_skip_proc_fct;
		        }
		        break;
        }
    }
    else if(pf_fct && WZD_DLG_MSG_KEY_INPUT == ui4_msg)
    {
        pf_fct(pv_tag, WGL_MSG_KEY_DOWN, param1, param2);
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_nw_skip_dlg_create
 * Description:
 * Input arguments:  -
 * Output arguments: -
 * Returns:
 *----------------------------------------------------------------------------*/
static INT32 _wzd_nw_skip_dlg_create (WZD_NW_DLG_T t_dlg_type)
{
    WZD_DLG_INIT_T      t_dlg_init;
    HANDLE_T            h_layout_frm = NULL_HANDLE;
    UTF16_T*            pw2s_dlg_text = NULL;
	UTF16_T*            pw2s_dlg_desc_text = NULL;
    UTF16_T*            pw2s_dlg_btn1_text = NULL;
    UTF16_T*            pw2s_dlg_btn2_text = NULL;
	ISO_639_LANG_T      s639_lang;

    c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.ui4_hide_timer = 10*1000;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;
    t_dlg_init.pf_fct = _wzd_nw_skip_dlg_proc_fct;
    t_dlg_init.pv_tag = (VOID*)(UINT32)t_dlg_type;

    switch(t_dlg_type)
    {
        case WZD_NW_DLG_1:
			t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_AUTO_HIDE | WZD_DLG_STYLE_MASK_WITH_DESC;
            pw2s_dlg_text = WZD_TEXT(MLM_WZD_KEY_NETWORK_SKIP_PROMPT_TEXT);
			pw2s_dlg_desc_text = WZD_TEXT(MLM_WZD_KEY_NETWORK_SKIP_PROMPT_TEXT_DESC);

			a_cfg_get_gui_lang(s639_lang);
			if (c_strncmp (s639_lang, s639_app_cfg_lang_fre, ISO_639_LANG_LEN) == 0 ||
			 	c_strncmp(s639_lang, s639_app_cfg_lang_fra, ISO_639_LANG_LEN) == 0)
			{
				/* Set Font */
				c_strcpy (t_dlg_init.t_fnt_info.a_c_font_name, wzd_view_get_font_name());
				t_dlg_init.t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
				t_dlg_init.t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
				t_dlg_init.t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
				t_dlg_init.t_fnt_info.ui1_custom_size = 19;
			}
            break;

        case WZD_NW_DLG_2:
        {
			t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_AUTO_HIDE | WZD_DLG_STYLE_MASK_WITH_DESC;
			pw2s_dlg_text = WZD_TEXT(MLM_WZD_KEY_NETWORK_SKIP_PROMPT_TEXT_TOS);
			pw2s_dlg_desc_text = WZD_TEXT(MLM_WZD_KEY_NETWORK_SKIP_PROMPT_TEXT_DESC);
            a_cfg_get_gui_lang(s639_lang);
            if (c_strncmp(s639_lang, s639_app_cfg_lang_spa, ISO_639_LANG_LEN) == 0 ||
				c_strncmp(s639_lang, s639_app_cfg_lang_esl, ISO_639_LANG_LEN) == 0)
            {
                /* Set Font */
                c_strcpy (t_dlg_init.t_fnt_info.a_c_font_name, wzd_view_get_font_name());
                t_dlg_init.t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
                t_dlg_init.t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
                t_dlg_init.t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
            	t_dlg_init.t_fnt_info.ui1_custom_size = 20;
             }
             else if (c_strncmp (s639_lang, s639_app_cfg_lang_fre, ISO_639_LANG_LEN) == 0 ||
			 	c_strncmp(s639_lang, s639_app_cfg_lang_fra, ISO_639_LANG_LEN) == 0)
             {
                    /* Set Font */
                    c_strcpy (t_dlg_init.t_fnt_info.a_c_font_name, wzd_view_get_font_name());
                    t_dlg_init.t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
                    t_dlg_init.t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
                    t_dlg_init.t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
                	t_dlg_init.t_fnt_info.ui1_custom_size = 20;
             }
        }
            break;

        case WZD_NW_DLG_3:
			t_dlg_init.ui4_style_mask = WZD_DLG_STYLE_MASK_2_BTN | WZD_DLG_STYLE_MASK_AUTO_HIDE;
            pw2s_dlg_text = WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_DLG_MSG);
            break;
    }
	pw2s_dlg_btn1_text = WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_DLG_BACK);
    pw2s_dlg_btn2_text = WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_DLG_SKIP);

    wzd_dlg_create( &t_dlg_init, &t_wzd_nw.h_dlg );

    wzd_dlg_set_text( t_wzd_nw.h_dlg, pw2s_dlg_text, FALSE );
	wzd_dlg_set_desc_text( t_wzd_nw.h_dlg, pw2s_dlg_desc_text, FALSE );
    wzd_dlg_set_btn_text( t_wzd_nw.h_dlg, WZD_DLG_BTN_TYPE_01,
                          pw2s_dlg_btn1_text, FALSE );
    wzd_dlg_set_btn_text( t_wzd_nw.h_dlg, WZD_DLG_BTN_TYPE_02,
                          pw2s_dlg_btn2_text, FALSE );

    wzd_dlg_show( t_wzd_nw.h_dlg , TRUE );

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_is_valid_email_addr
 *
 * Description: check the E-mail addr data is valid or not.
 *              missing "@" or "." is not valid.
 *
 * Inputs: CHAR* str: user enterd E-mail str
 *         UINT8 ui1_str_len: the lenth of E-mail str
 *
 * Outputs:
 *
 * Returns: TRUE:  the E_mail addr str is valid.
 *          FALSE: the E_mail addr str is not valid.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_reg_info_is_valid_email_addr(CHAR* s_str, UINT8 ui1_str_len)
{
    if ( NULL == s_str)
    {
        return FALSE;
    }
    if (0 == ui1_str_len)
    {
        /* not data entered, no need to display the warning dialog */
        return TRUE;
    }
    if ((NULL == c_strstr(s_str, WZD_NW_REG_INFO_AT))||
        (NULL == c_strstr(s_str, WZD_NW_REG_INFO_DOT)))
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_is_valid_name
 *
 * Description:check the name(fist name and last name) data is valid or not.
 *             letters only and at least 2 characters
 *
 * Inputs: CHAR* str: user enterd name
 *         UINT8 ui1_str_len: the lenth of name
 *
 * Outputs:
 *
 * Returns: TRUE:  the name str is valid.
 *          FALSE: the name str is not valid.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_reg_info_is_valid_name(CHAR* s_str, UINT8 ui1_str_len)
{
    UINT8                   ui1_idx = 0;

    if ( NULL == s_str)
    {
        return FALSE;
    }
    if (0 == ui1_str_len)
    {
        /* not data entered, no need to display the warning dialog */
        return TRUE;
    }
    else if (ui1_str_len < WZD_NW_REG_INFO_NAME_MIN_LEN)
    {
        return FALSE;
    }
    else
    {
        for(ui1_idx = 0; ui1_idx < ui1_str_len; ui1_idx++)
        {
            if ((s_str[ui1_idx] >='a' && s_str[ui1_idx] <='z') ||
                (s_str[ui1_idx] >='A' && s_str[ui1_idx] <='Z'))
            {
                continue;
            }
            else
            {
                return FALSE;

            }

        }
        return TRUE;

    }
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_is_valid_phone_num
 *
 * Description:check the phone num data is valid or not.
 *             no alpha characters and at least 10 characters and max of 16.
 *
 * Inputs: CHAR* str: user enterd phone num
 *         UINT8 ui1_str_len: the lenth of phone num
 *
 * Outputs:
 *
 * Returns: TRUE:  the phone num str is valid.
 *          FALSE: the phone num str is not valid.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_reg_info_is_valid_phone_num(CHAR* s_str, UINT8 ui1_str_len)
{
    UINT8                   ui1_idx = 0;

    if ( NULL == s_str)
    {
        return FALSE;
    }
    if (0 == ui1_str_len)
    {
        /* not data entered, no need to display the warning dialog */
        return TRUE;
    }
    else if ((ui1_str_len < WZD_NW_REG_INFO_PHONE_NUM_MIN_LEN) ||
             (ui1_str_len > WZD_NW_REG_INFO_PHONE_NUM_MAX_LEN))
    {
        return FALSE;
    }
    else
    {
        for(ui1_idx = 0; ui1_idx < ui1_str_len; ui1_idx++)
        {
            if ((s_str[ui1_idx] >='a' && s_str[ui1_idx] <='z') ||
                (s_str[ui1_idx] >='A' && s_str[ui1_idx] <='Z'))
            {
                return FALSE;
            }

        }
        return TRUE;

    }
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_is_valid_zip_code
 *
 * Description:check the zip code data is valid or not.
 *             digits only or letters followed by digits,
 *             and atleast 5 characters and max of
 *
 * Inputs: CHAR* str: user enterd zip code
 *         UINT8 ui1_str_len: the lenth of zip code
 *
 * Outputs:
 *
 * Returns: TRUE:  the zip code str is valid.
 *          FALSE: the zip code str is not valid.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_reg_info_is_valid_zip_code(CHAR* s_str, UINT8 ui1_str_len)
{
    UINT8                   ui1_idx = 0;
    UINT8                   ui1_loop = 0;

    if ( NULL == s_str)
    {
        return FALSE;
    }
    if (0 == ui1_str_len)
    {
        /* not data entered, no need to display the warning dialog */
        return TRUE;
    }
    else if ((ui1_str_len < WZD_NW_REG_INFO_ZIP_CODE_MIN_LEN) ||
             (ui1_str_len > WZD_NW_REG_INFO_ZIP_CODE_MAX_LEN))
    {
        return FALSE;
    }
    else
    {
        for (ui1_idx = 0; ui1_idx < ui1_str_len; ui1_idx++)
        {
            if ((s_str[ui1_idx] >='a' && s_str[ui1_idx] <='z') ||
                (s_str[ui1_idx] >='A' && s_str[ui1_idx] <='Z') ||
                (s_str[ui1_idx] >='0' && s_str[ui1_idx] <='9'))
            {
                continue;
            }
            else
            {
                return FALSE;
            }

        }
        /* only include: 0-9,a-z,A-Z */
        for (ui1_idx = 0; ui1_idx < ui1_str_len; ui1_idx++)
        {
            if (s_str[ui1_idx] >='0' && s_str[ui1_idx] <='9')
            {
                continue;
            }
            else
            {
                break;
            }
        }
        /* only digits */
        if (ui1_idx == ui1_str_len)
        {
            return TRUE;
        }
        /* digits and letters combine*/
        else
        {
            for (ui1_idx = 0; ui1_idx < ui1_str_len; ui1_idx++)
            {
                if ((s_str[ui1_idx] >='a' && s_str[ui1_idx] <='z') ||
                    (s_str[ui1_idx] >='A' && s_str[ui1_idx] <='Z'))
                {
                   continue;
                }
                else
                {
                    break;
                }
            }
            /* only letters or the first character is digit */
            if ((ui1_idx == ui1_str_len) || (0 == ui1_idx))
            {
                return FALSE;
            }
            else
            {
                for (ui1_loop = ui1_idx; ui1_loop < ui1_str_len; ui1_loop++)
                {
                    if (s_str[ui1_loop] >='0' && s_str[ui1_loop] <='9')
                    {
                        continue;
                    }
                    else
                    {
                        return FALSE;
                    }
                }

                return TRUE;
            }
        }
    }
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_is_valid
 *
 * Description: check the reg info data is valid or not.
 *              including: E-mail, first name, last nme, phone num and zip code.
 *
 * Inputs: CHAR* str: user enterd reg info
 *         UINT8 ui1_str_len: the lenth of reg info
 *
 * Outputs:
 *
 * Returns: TRUE:  the reg info is valid.
 *          FALSE: the reg info is not valid.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_reg_info_is_valid(CHAR* s_str, UINT8 ui1_str_len)
{
    BOOL                        b_is_valid = FALSE;
    if ( NULL == s_str)
    {
        return FALSE;
    }
    if (0 == ui1_str_len)
    {
        /* not data entered, no need to display the warning dialog */
        return TRUE;
    }

    switch (t_wzd_nw.t_info_reg.e_current_item)
    {
        case WZD_NW_REG_INFO_MAIL:
        {
            b_is_valid = _wzd_nw_reg_info_is_valid_email_addr(s_str,c_strlen(s_str));
            break;
        }
        case WZD_NW_REG_INFO_FIRST_NAME:
        case WZD_NW_REG_INFO_LAST_NAME:
        {
            b_is_valid = _wzd_nw_reg_info_is_valid_name(s_str,c_strlen(s_str));
            break;
        }
        case WZD_NW_REG_INFO_PHONE_NUM:
        {
            b_is_valid = _wzd_nw_reg_info_is_valid_phone_num(s_str,c_strlen(s_str));
            break;
        }
        case WZD_NW_REG_INFO_ZIP_CODE:
        {
            b_is_valid = _wzd_nw_reg_info_is_valid_zip_code(s_str,c_strlen(s_str));
            break;
        }
        default:
        {
            break;
        }
    }

    return b_is_valid;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_warning_dlg_proc_fct
 *
 * Description:reg info warning dialog process function.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_reg_info_warning_dlg_proc_fct(VOID*      pv_tag,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    INT32                       i4_ret = WZDR_OK;

    switch (ui4_msg)
    {
        case WZD_DLG_MSG_KEY_INPUT:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    i4_ret = wzd_dlg_hide(t_wzd_nw.h_dlg);
                    SHOW_ON_ERR(i4_ret);

                    i4_ret = c_wgl_set_focus(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item], TRUE);
                    SHOW_ON_ERR(i4_ret);

                    i4_ret = wzd_view_main_frm_repaint();
                    SHOW_ON_ERR(i4_ret);

                    break;
                }
                default:
                {
                    break;
                }
            }
        }
        default:
        {
            break;
        }
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name:    _wzd_nw_reg_info_warning_dlg_create
 *
 * Description:create and show warning dialog for registration info data verification
 *
 * Input arguments: current item: E_mial, first_name, last_name, phone_num, zip_code
 *
 * Output arguments: -
 *
 * Returns:0                      Successful.
 *         Any other values       Failed.
 *
 *----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_warning_dlg_create (WZD_NW_INFO_REG_FOCUS_E e_current_item)
{
    WZD_DLG_INIT_T          t_dlg_init;
    HANDLE_T                h_layout_frm = NULL_HANDLE;
    UTF16_T*                pw2s_dlg_text = NULL;
    UTF16_T*                pw2s_dlg_btn1_text = NULL;

    c_memset(&t_dlg_init, 0 , sizeof(WZD_DLG_INIT_T));
    wzd_view_get_layout_frm(&h_layout_frm);
    t_dlg_init.h_parent = h_layout_frm;
    t_dlg_init.e_default_focus_btn = WZD_DLG_BTN_TYPE_01;
    t_dlg_init.pf_fct = _wzd_nw_reg_info_warning_dlg_proc_fct;
    t_dlg_init.pv_tag = NULL;

    pw2s_dlg_btn1_text = WZD_TEXT(MLM_WZD_KEY_DLG_OK);

    pw2s_dlg_text = WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_EMAIL_DLG_TXT + e_current_item );

    wzd_dlg_create( &t_dlg_init, &t_wzd_nw.h_dlg );

    wzd_dlg_set_text( t_wzd_nw.h_dlg, pw2s_dlg_text, FALSE );
    wzd_dlg_set_btn_text( t_wzd_nw.h_dlg, WZD_DLG_BTN_TYPE_01,
                          pw2s_dlg_btn1_text, FALSE );

    wzd_dlg_show( t_wzd_nw.h_dlg , TRUE );

    t_wzd_nw.t_info_reg.b_warning_dlg_is_show[t_wzd_nw.t_info_reg.e_current_item] = TRUE;

    return WZDR_OK;
}

#ifdef ________________________________________________________JUST_FOR_DIVISION
#endif


/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_get_associate_data
 *
 * Description:
 *          get associate data.
 * Inputs: -
 *
 * Outputs:
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 *-----------------------------------------------------------------------------*/
static INT32 _wzd_nw_get_associate_data(NET_802_11_ASSOCIATE_T** ppt_associate)
{
    if (ppt_associate == NULL)
    {
        return WZDR_INV_ARG;
    }

    *ppt_associate = &t_wzd_nw.t_choice_connect.t_associate;

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_get_ap_by_idx
 *
 * Description:
 *          get ap by index.
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static NET_802_11_ESS_INFO_T*  _wzd_nw_get_ap_by_idx(UINT16     ui2_idx)
{

    if((ui2_idx < t_wzd_nw.t_choice_connect.ui1_visiable_ap_num)&&
       (ui2_idx < WLAN_AP_LB_MAX_NUM))
    {
        return &t_wzd_nw.t_choice_connect.t_essList.p_EssInfo[t_wzd_nw.t_choice_connect.aui1_ap_map[ui2_idx]];
    }
    else
    {
        return NULL;
    }
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_is_valid_hex_string
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_is_valid_hex_string(CHAR*      s_input,
                                        UINT8      ui1_length)
{
    BOOL  b_valid = TRUE;
    UINT8 ui1_idx = 0;

    for(ui1_idx=0; ui1_idx<ui1_length; ui1_idx++)
    {
        if( (s_input[ui1_idx] >='0' &&  s_input[ui1_idx] <='9') ||
            (s_input[ui1_idx] >='a' &&  s_input[ui1_idx] <='f') ||
            (s_input[ui1_idx] >='A' &&  s_input[ui1_idx] <='F')
          )
        {
            continue;
        }

        b_valid = FALSE;
        break;
    }

    return b_valid;

}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_is_valid_wep_input_key
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_is_valid_wep_input_key(
                            NET_802_11_AUTH_CIPHER_T    e_AuthCipher,
                            CHAR*                       s_input,
                            BOOL*                       pb_IsAscii)
{
    BOOL b_valid = TRUE;
    *pb_IsAscii = TRUE;

    UINT8 ui1_length = (UINT8)c_strlen(s_input);

    switch(e_AuthCipher)
    {
    case IEEE_802_11_AUTH_CIPHER_WEP40:
    {
        if(ui1_length == 5)
        {
            b_valid     = TRUE;
            *pb_IsAscii = TRUE;
        }
        else if(ui1_length == 10)
        {
            *pb_IsAscii = FALSE;
            b_valid = _wzd_nw_is_valid_hex_string(s_input, ui1_length);

        }
        else
        {
            b_valid     = FALSE;
            *pb_IsAscii = TRUE;

        }

        break;
    }
    case IEEE_802_11_AUTH_CIPHER_WEP104:
    {
        if(ui1_length == 13)
        {
            b_valid = TRUE;
            *pb_IsAscii = TRUE;
        }
        else if(ui1_length == 26)
        {
            *pb_IsAscii = FALSE;

            b_valid = _wzd_nw_is_valid_hex_string(s_input, ui1_length);
        }
        else
        {
            b_valid = FALSE;
        }

        break;
    }
    default:
        break;
    }

    return b_valid;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_is_valid_input_key
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_is_valid_input_key(NET_802_11_ASSOCIATE_T*    pt_associate,
                                       CHAR*                      s_input,
                                       BOOL*                      pb_IsAscii)
{
    BOOL b_valid = TRUE;

    *pb_IsAscii = TRUE;

    switch(pt_associate->e_AuthMode)
    {
    case IEEE_802_11_AUTH_MODE_NONE:
    case IEEE_802_11_AUTH_MODE_OPEN:
    case IEEE_802_11_AUTH_MODE_WPA_OWE:
    case IEEE_802_11_AUTH_MODE_WPA2_OWE:
    case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE:
        break;
    case IEEE_802_11_AUTH_MODE_SHARED:
    case IEEE_802_11_AUTH_MODE_WEPAUTO:
    {
        /*WEP authCipher maybe  IEEE_802_11_AUTH_CIPHER_WEP104 or IEEE_802_11_AUTH_CIPHER_WEP40 .*/
        b_valid = _wzd_nw_is_valid_wep_input_key (
                                IEEE_802_11_AUTH_CIPHER_WEP40,
                                s_input,
                                pb_IsAscii);
        if(b_valid)
        {
            pt_associate->e_AuthCipher = IEEE_802_11_AUTH_CIPHER_WEP40;
        }
        else
        {

            b_valid = _wzd_nw_is_valid_wep_input_key (
                                IEEE_802_11_AUTH_CIPHER_WEP104,
                                s_input,
                                pb_IsAscii);
            if(b_valid)
            {
                pt_associate->e_AuthCipher = IEEE_802_11_AUTH_CIPHER_WEP104;
            }
        }

        break;
    }
    case IEEE_802_11_AUTH_MODE_WPA:
    case IEEE_802_11_AUTH_MODE_WPA_PSK:
    case IEEE_802_11_AUTH_MODE_WPA2:
    case IEEE_802_11_AUTH_MODE_WPA2_PSK:
    case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
    {   /*check wpa input key*/

        UINT8 ui1_length = (UINT8)c_strlen(s_input);

        if(ui1_length < 8 || ui1_length > 64)
        {
            b_valid = FALSE;
        }
        else if(ui1_length == 64)
        {
            *pb_IsAscii = FALSE;

            b_valid = _wzd_nw_is_valid_hex_string(s_input, ui1_length);
        }
        else
        {
            /*b_valid = TRUE; *pb_IsAscii = TRUE;*/
        }

        break;
    }
        break;
    default:
        break;
    }

    return b_valid;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_is_lock_ap
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_is_lock_ap(NET_802_11_AUTH_MODE_T          e_AuthMode,
                               NET_802_11_AUTH_CIPHER_T        e_AuthCipher)
{
    if ((e_AuthMode== IEEE_802_11_AUTH_MODE_NONE ||
         e_AuthMode == IEEE_802_11_AUTH_MODE_OPEN) &&
         e_AuthCipher == IEEE_802_11_AUTH_CIPHER_NONE)
    {
        return FALSE;
    }
    else if (e_AuthMode == IEEE_802_11_AUTH_MODE_WPA_OWE ||
             e_AuthMode == IEEE_802_11_AUTH_MODE_WPA2_OWE ||
             e_AuthMode == IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE)
    {
        return FALSE;
    }

    return TRUE;

}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_is_ssid_scan_success
 *
 * Description:
 *          _wzd_nw_is_ssid_scan_success.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_is_ssid_scan_success(VOID)
{
    INT32       i4_ret;
    INT8        ui1_idx = 0;
    BOOL        b_found   = FALSE;

    NET_802_11_ASSOCIATE_T* pt_associate = NULL;
    NET_802_11_ESS_LIST_T   t_essList;
    NET_802_11_ESS_INFO_T*  p_essInfo = NULL;
    UINT8                   ui1_max_ap_num = WLAN_AP_LB_ELEM_NUM;

    i4_ret = _wzd_nw_get_associate_data(&pt_associate);
    RET_ON_ERR(i4_ret);

    if(pt_associate == NULL)
    {
        return WZDR_FAIL;
    }

    c_memset(&t_essList, 0 , sizeof(NET_802_11_ESS_LIST_T));
    i4_ret =  a_nw_wlan_get_ess_list(&t_essList);
    RET_ON_ERR(i4_ret);

    if(t_essList.ui4_NumberOfItems == 0)
    {
        return WZDR_FAIL;
    }

    if(ui1_max_ap_num > (UINT8)t_essList.ui4_NumberOfItems)
    {
        ui1_max_ap_num = (UINT8)t_essList.ui4_NumberOfItems;
    }

    for (ui1_idx = 0; ui1_idx < ui1_max_ap_num; ui1_idx ++)
    {
        p_essInfo = &t_essList.p_EssInfo[ui1_idx];

        if(p_essInfo->t_Ssid.ui4_SsidLen == 0)
        {
            continue;
        }

        if(c_strncmp(p_essInfo->t_Ssid.ui1_aSsid, t_wzd_nw.s_ssid_buf, NET_802_11_MAX_LEN_SSID ) != 0)
        {
            continue;
        }

        b_found = TRUE;

        c_memset(pt_associate, 0, sizeof(NET_802_11_ASSOCIATE_T));
        pt_associate->t_Ssid      = p_essInfo->t_Ssid;
        c_memcpy(pt_associate->t_Bssid,p_essInfo->t_Bssid, sizeof(NET_802_11_BSSID_T));

        pt_associate->e_AuthMode  = p_essInfo->e_AuthMode;
        pt_associate->e_AuthCipher= p_essInfo->e_AuthCipher;

        pt_associate->t_Key.b_IsAscii = FALSE;

		DBG_LOG_PRINT(("[WZD][NW] --- %s %d, ssid scan success.\n", __FUNCTION__,__LINE__));

        break;
    }

   return b_found;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_ssid_wifi_assoc
 *
 * Description:
 *          associate wifi connection by inputing ssid and password.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_ssid_wifi_assoc(VOID)
{
    INT32       			i4_ret = WZDR_OK;
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;

    i4_ret = _wzd_nw_get_associate_data(&pt_associate);
    RET_ON_ERR(i4_ret);

    if(pt_associate == NULL)
    {
        return WZDR_FAIL;
    }

	/* if do not need input passcode, associate directly */
    if (FALSE == _wzd_nw_is_lock_ap(pt_associate->e_AuthMode,pt_associate->e_AuthCipher))
    {
    	DBG_LOG_PRINT(("[WZD][NW] --- %s %d, start SSID WLAN associate.\n", __FUNCTION__,__LINE__));
		i4_ret = a_nw_custom_wlan_disassociate();
		RET_ON_ERR(i4_ret);

        i4_ret = a_nw_wlan_associate(pt_associate);
        RET_ON_ERR(i4_ret);

		t_wzd_nw.b_is_busying = TRUE;
	    t_wzd_nw.b_timer_result = FALSE;
	    t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

	    t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_WIFI_ASSOC;
	    _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);
    }
    else
    {
    	i4_ret = _wzd_nw_go(NW_SETUP_STATE_WIRELESS_PWD_INPUT, TRUE);
		RET_ON_ERR(i4_ret);
    }

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_lan_conn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_lan_conn(VOID)
{
    INT32           i4_ret;
    BOOL            b_connected  = FALSE;

    /* always return connected if ethernet is plugin  */
#if 0
    i4_ret = _wzd_nw_conn_is_connected(&b_connected);
    RET_ON_ERR(i4_ret);
#else
    b_connected = TRUE;
#endif

    if (b_connected)
    {
    	i4_ret = _wzd_nw_go(NW_SETUP_STATE_BEGIN, TRUE);
        RET_ON_ERR(i4_ret);

        /* show ethernet connection info */
        i4_ret = _wzd_nw_lan_assoc_result();
        RET_ON_ERR(i4_ret);
    }
    else
    {
        i4_ret = _wzd_nw_go(NW_SETUP_STATE_BEGIN, TRUE);
        RET_ON_ERR(i4_ret);

        t_wzd_nw.b_is_busying = TRUE;
        t_wzd_nw.b_timer_result = FALSE;
        t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

		RET_ON_ERR (_wzd_nw_full_screen_icon_update(FALSE));

		RET_ON_ERR (wzd_view_full_screen_dlg_set_text (
						WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTING_NETWORK),
						FALSE));

		/* store focused handle */
        c_wgl_get_focus( &t_wzd_nw.h_last_focused_wdg );

		RET_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));

        t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_LAN_ASSOC;
        _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);

    }

    return WZDR_OK;
}

#ifdef APP_NETWORK_WIFI_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_wifi_conn
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_wifi_conn(VOID)
{
    INT32           i4_ret;
    UINT8           ui1_count = 0;

    DBG_LOG_PRINT(("\n[WZD][NW] --- %s,%d.\n", __FUNCTION__, __LINE__));

	/* Network Init Not ready, waiting... */
    while (!a_nw_custom_nw_wifi_start() && (ui1_count < 5))
    {
        DBG_LOG_PRINT(("\n[WZD][NW] --- waiting...\n"));
        c_thread_delay(1000);
        ui1_count ++;
    }
	if (!a_nw_custom_nw_wifi_start())
	{
		i4_ret = _wzd_nw_go(NW_SETUP_STATE_NONE_CONN, TRUE);
		RET_ON_ERR(i4_ret);

        return WZDR_OK;
	}

	i4_ret = _wzd_nw_go(NW_SETUP_STATE_WIRELESS_SCANNING, TRUE);
	RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_wifi_scan();
    if(WZDR_OK != i4_ret)
    {
    	DBG_LOG_PRINT(("[WZD][NW] --- wifi can not start scanning... \n"));

        i4_ret = _wzd_nw_wifi_scan_timeout();
        RET_ON_ERR(i4_ret);
    }

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_wifi_scan
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_wifi_scan(VOID)
{
    INT32  i4_ret;
	NET_802_11_ASSOCIATE_T* pt_associate = NULL;

	/* reset associate data */
	i4_ret = _wzd_nw_get_associate_data(&pt_associate);
	RET_ON_ERR(i4_ret);

	if(pt_associate)
	{
		c_memset(pt_associate, 0, sizeof(NET_802_11_ASSOCIATE_T));
	}

	/* reset visiable ap num */
	t_wzd_nw.t_choice_connect.ui1_visiable_ap_num = 0;

    if (a_nw_custom_nw_wifi_start())
    {
        NW_WLAN_STATE_T e_wlan_state = NW_WLAN_UNPLUG;
        a_nw_wlan_status(&e_wlan_state);

        if (NW_WLAN_PLUG_STOP == e_wlan_state)
        {
            a_nw_chg_network_interface(NW_NET_INTERFACE_WIFI);
        }

        c_thread_delay(500);
        i4_ret = a_nw_wlan_scan();
        if (WZDR_OK != i4_ret)
        {
            /* if wifi module is not initial, we will not invoke wifi scan */
            t_wzd_nw.t_choice_connect.b_is_wlan_ind = FALSE;
        }
        else
        {
            t_wzd_nw.t_choice_connect.b_is_wlan_ind = TRUE;
        }
    }
    else
    {
        DBG_LOG_PRINT(("[WZD][NW] --- %s, WIFI not ready.\n", __FUNCTION__));
        /* if wifi module is not initial, we will not invoke wifi scan */
        t_wzd_nw.t_choice_connect.b_is_wlan_ind = FALSE;
    }

    t_wzd_nw.b_is_busying = TRUE;
    t_wzd_nw.b_timer_result = FALSE;
    t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

	t_wzd_nw.t_choice_connect.ui1_icon_step = WZD_NW_TIMER_ICON_STEP;

    i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

	/* Set to topmost */
    i4_ret = c_wgl_insert(t_wzd_nw.h_timer_icon,
						NULL_HANDLE,
						WGL_INSERT_TOPMOST,
						WGL_NO_AUTO_REPAINT);
	RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_timer_icon_update(t_wzd_nw.h_timer_icon);
    RET_ON_ERR(i4_ret);

    t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_WIFI_SCAN;
    _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);

    return WZDR_OK;
}
#endif

#ifdef WZD_NW_TEST_CONNECTION
/*----------------------------------------------------------------------------
 * Name: _wzd_test_connection_notify_handler
 *
 * Description:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_test_connection_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    WZD_NW_NFY_DATA_T* pt_nw_nfy_data = (WZD_NW_NFY_DATA_T*)pv_data;

    if ((UINT32)pt_nw_nfy_data->pv_tag == ui4_g_wzd_test_connection_tag)
    {
        switch(pt_nw_nfy_data->e_nfy_id)
        {
            case NW_NFY_ID_INTERN_CT_RESULT_ASYNC:
            {
				BOOL b_nw_is_connect = (BOOL)(UINT32)(pt_nw_nfy_data->pv_nfy_param);
				if (b_nw_is_connect)
	            {
	                t_wzd_nw.b_timer_result = TRUE;
	            }

                a_nw_unregister(ui4_g_wzd_test_connection_nfy_id);
                ui4_g_wzd_test_connection_nfy_id = 0;
            }
                break;
            default:
                return;
        }
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_test_connection_notify_callback
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_test_connection_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    WZD_NW_NFY_DATA_T t_nw_nfy_data;

	if ( !wzd_is_show() )   /* If wizard not active, should not handler network notify msg*/
    {
        return ;
    }

	c_memset(&t_nw_nfy_data, 0, sizeof(WZD_NW_NFY_DATA_T));
    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    wzd_async_invoke(_wzd_test_connection_notify_handler,
                     &t_nw_nfy_data,
                     (SIZE_T)sizeof(WZD_NW_NFY_DATA_T),
                     TRUE);
}
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_test_connection
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_test_connection(VOID)
{
    INT32  i4_ret;
    NW_DHCP_STATE_T     e_dhcp_state;

    t_wzd_nw.b_is_busying = TRUE;

	/* UGLY hack: set timer result to TURE directly */
	#if 0
    t_wzd_nw.b_timer_result = FALSE;
	#else
	t_wzd_nw.b_timer_result = TRUE;
	#endif
    t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
    t_wzd_nw.t_choice_connect.ui1_icon_step = WZD_NW_TIMER_ICON_STEP;

#if 0
    i4_ret = c_wgl_insert(t_wzd_nw.h_timer_icon,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          FALSE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_timer_icon_update(t_wzd_nw.h_timer_icon);
    RET_ON_ERR(i4_ret);
#endif

    t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_TEST_CONN;
    _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);

    /* get the dhcp status, if current dhcp is "on" and not get ip addr, should return test fail */
    i4_ret = a_nw_get_dhcp_status(&e_dhcp_state);
    RET_ON_ERR(i4_ret);

    if ((NW_DHCP_STARTED_LOCAL == e_dhcp_state )||
        (NW_DHCP_FAILED == e_dhcp_state))
    {
        nw_custom_set_auto_ip_config(TRUE);
    }
    else if ((NW_DHCP_STARTED == e_dhcp_state) ||
             (NW_DHCP_STOPPED == e_dhcp_state))
    {
    #ifdef WZD_NW_TEST_CONNECTION
        i4_ret = a_nw_connection_test_async((CHAR*)"www.google.com");
    	RET_ON_ERR(i4_ret);

		ui4_g_wzd_test_connection_tag++;
	    i4_ret = a_nw_register(_wzd_test_connection_notify_callback,
	                           (VOID*)ui4_g_wzd_test_connection_tag, &ui4_g_wzd_test_connection_nfy_id);
	    RET_ON_ERR(i4_ret);
	#endif
    }

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_conn_is_connected
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_conn_is_connected(BOOL* pb_is_connected)
{
    INT32           i4_ret;
    BOOL            b_connected  = FALSE;
    BOOL            b_dhcp       = FALSE;
    NW_DHCP_STATE_T e_dhcp_state = NW_DHCP_FAILED;

    if (NULL == pb_is_connected)
    {
        return WZDR_INV_ARG;
    }

    i4_ret = nw_custom_get_auto_ip_config(&b_dhcp);
    SHOW_ON_ERR(i4_ret);
    if ((WZDR_OK == i4_ret)&&
        !b_dhcp)
    {
        b_connected = TRUE;
    }
    else
    {
        i4_ret = a_nw_get_dhcp_status(&e_dhcp_state);
        SHOW_ON_ERR(i4_ret);

        if ((WZDR_OK == i4_ret)&&
            (NW_DHCP_STARTED == e_dhcp_state))
        {
            b_connected = TRUE;
        }
    }

    DBG_INFO(("\n[WZD][NW]%s,%s,%d,b_dhcp=%d,e_dhcp_state=%d,b_connected=%d\n",
               __FILE__, __FUNCTION__, __LINE__,
               b_dhcp, e_dhcp_state, b_connected));

    /*if ( WZDR_OK != a_nw_connection_test((CHAR*)"www.google.com") )
    {
        b_connected = FALSE;
        DBG_LOG_PRINT(("<WZD Network> --- %s, %d. Network connection fail! ---", __FUNCTION__, __LINE__));
    }*/

    *pb_is_connected = b_connected;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_conn_lan_or_wifi
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_conn_lan_or_wifi(VOID)
{
    INT32           i4_ret;
    BOOL            b_wired_plug = FALSE;
    UINT8           ui1_count = 0;

    /* reset flags */
    e_g_nw_setup_pre_state = NW_SETUP_STATE_BEGIN;
    e_g_nw_setup_state = NW_SETUP_STATE_BEGIN;

    t_wzd_nw.b_is_busying = FALSE;
    t_wzd_nw.b_timer_result = TRUE;
    t_wzd_nw.ui4_start_time = 0;


    /* check the network init status first */
    while ((NWR_FAIL == a_get_nw_init_status())&& (ui1_count < 10))
    {
        DBG_LOG_PRINT(("\n[WZD][NW] --- waiting network initial ...\n"));
        c_thread_delay(1000);
        ui1_count ++;
    }

    i4_ret = a_nw_get_ethernet_connect_info(&b_wired_plug);
    SHOW_ON_ERR(i4_ret);

    if ((i4_ret == WZDR_OK) &&
        (TRUE == b_wired_plug))
    {
        DBG_LOG_PRINT(("\n[WZD][NW] --- %s,%d.\n", __FUNCTION__, __LINE__));
        i4_ret = _wzd_nw_lan_conn();
        RET_ON_ERR(i4_ret);
    }
    else
    {
        DBG_LOG_PRINT(("\n[WZD][NW] --- %s,%d.\n", __FUNCTION__, __LINE__));
        i4_ret = _wzd_nw_wifi_conn();
        RET_ON_ERR(i4_ret);
    }
    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_wifi_scan_with_ssid
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_wifi_scan_with_ssid(VOID)
{
    INT32       i4_ret;
    UINT32      ui4_len;
	NET_802_11_ASSOCIATE_T* pt_associate = NULL;

	/* reset associate data */
	i4_ret = _wzd_nw_get_associate_data(&pt_associate);
	RET_ON_ERR(i4_ret);

	if(pt_associate)
	{
		c_memset(pt_associate, 0, sizeof(NET_802_11_ASSOCIATE_T));
	}

	ui2_g_ssid_scan_count = 0;

    c_memset(t_wzd_nw.s_ssid_buf, 0, sizeof(CHAR)*(WZD_NW_SSID_MAX_LEN));
    i4_ret  = c_uc_w2s_to_ps(t_wzd_nw.aw2s_ssid_context, t_wzd_nw.s_ssid_buf, WZD_NW_SSID_MAX_LEN);
    RET_ON_ERR(i4_ret);

    ui4_len = c_strlen(t_wzd_nw.s_ssid_buf);

    if (ui4_len > 0 && ui4_len <= NET_802_11_MAX_LEN_SSID)
    {
        t_wzd_nw.t_choice_connect.b_associate_complete = FALSE;
        if (a_nw_custom_nw_wifi_start())
        {
            i4_ret = a_nw_wlan_scan_with_ssid(t_wzd_nw.s_ssid_buf, ui4_len);
            if (WZDR_OK != i4_ret)
            {
                /* do something else */
            }
        }
        else
        {
            DBG_LOG_PRINT(("[WZD][NW] --- %s, WIFI not ready.\n", __FUNCTION__));
        }
        t_wzd_nw.b_is_busying = TRUE;
        t_wzd_nw.b_timer_result = FALSE;
        t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

		/* unfloat h_eb_clr first */
		c_wgl_float(t_wzd_nw.t_eb_pwd.h_eb_clr, FALSE, FALSE);

		/* store focused handle */
        c_wgl_get_focus( &t_wzd_nw.h_last_focused_wdg );

		RET_ON_ERR (_wzd_nw_full_screen_icon_update(FALSE));
		RET_ON_ERR (wzd_view_full_screen_dlg_set_text (
						WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTING_NETWORK),
						FALSE));
		RET_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));

        t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_WIFI_SSID_SCAN;
        _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);
    }
    else
    {
        /* store focused handle */
        c_wgl_get_focus( &t_wzd_nw.h_last_focused_wdg );

		/* show associate fail dialog */
		RET_ON_ERR (_wzd_nw_assoc_dlg_create());

        return WZDR_OK;
    }

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_pwd_wifi_assoc
 *
 * Description:
 *          associate wifi connection by inputing password.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_pwd_wifi_assoc(VOID)
{
    INT32       i4_ret;
    BOOL        b_valid = TRUE;
    BOOL        b_IsAscii = FALSE;
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;

    i4_ret = _wzd_nw_get_associate_data(&pt_associate);
    RET_ON_ERR(i4_ret);

    if(pt_associate == NULL)
    {
        return WZDR_OK;
    }

	c_memset(t_wzd_nw.s_pwd_buf, 0, sizeof(CHAR)*(WZD_NW_KEY_MAX_LEN+1));
    i4_ret = c_uc_w2s_to_ps(t_wzd_nw.aw2s_key_context, t_wzd_nw.s_pwd_buf, WZD_NW_KEY_MAX_LEN);
    RET_ON_ERR(i4_ret);

    b_valid = _wzd_nw_is_valid_input_key(pt_associate,
                                  t_wzd_nw.s_pwd_buf,
                                  &b_IsAscii);

    if (b_valid)
    {
        pt_associate->t_Key.b_IsAscii = b_IsAscii;
        pt_associate->t_Key.pui1_PassPhrase = t_wzd_nw.s_pwd_buf;

		DBG_LOG_PRINT(("[WZD][NW] --- %s %d, start WLAN disassociate.\n", __FUNCTION__,__LINE__));
		i4_ret = a_nw_custom_wlan_disassociate();
		RET_ON_ERR(i4_ret);

        DBG_LOG_PRINT(("[WZD][NW] --- %s %d, start WLAN associate.\n", __FUNCTION__,__LINE__));
        i4_ret = a_nw_wlan_associate(pt_associate);
        RET_ON_ERR(i4_ret);

        t_wzd_nw.b_is_busying = TRUE;
        t_wzd_nw.b_timer_result = FALSE;
        t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

		/* unfloat h_eb_clr first */
		c_wgl_float(t_wzd_nw.t_eb_pwd.h_eb_clr, FALSE, FALSE);

        /* store focused handle */
        c_wgl_get_focus( &t_wzd_nw.h_last_focused_wdg );

		RET_ON_ERR (_wzd_nw_full_screen_icon_update(FALSE));
		RET_ON_ERR (wzd_view_full_screen_dlg_set_text (
						WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTING_NETWORK),
						FALSE));
		RET_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));

        t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_WIFI_PWD_ASSOC;
        _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);
    }
    else
    {
    	DBG_LOG_PRINT(("[WZD][NW] --- %s %d, key is invalid.\n", __FUNCTION__,__LINE__));

		/* store focused handle */
        c_wgl_get_focus( &t_wzd_nw.h_last_focused_wdg );

		/* show associate fail dialog */
		RET_ON_ERR (_wzd_nw_assoc_dlg_create());
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_is_filter_out_ssid
 *
 * Description: ui skip the ssid which end with "VIZIOTV"
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                     Successful.
 *          FALSE       			 Failed.
 ----------------------------------------------------------------------------*/
static BOOL _wzd_nw_is_filter_out_ssid(CHAR* pssid)
{
    CHAR s_temp_string[10] = {0};
    UINT8 ui1_i = 0;

    if (c_strlen(pssid) < 7)
    {
        return FALSE;
    }

    for (ui1_i = 0; ui1_i < 7; ui1_i++)
    {
        s_temp_string[ui1_i] = pssid[c_strlen(pssid)-1-ui1_i];
    }

    if (0 == c_strcmp(s_temp_string, "VTOIZIV"))
    {
        DBG_INFO(("[WZD][NW] --- filter out VIZIOTV. FUNC: %s LINE: %d\n",
                    __FUNCTION__, __LINE__));
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_store_ap_list_data
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_store_ap_list_data(VOID)
{
	INT32				    i4_ret;
	UINT8                   ui1_idx = 0;
    UINT8                   ui1_idx_2 = 0;

	NET_802_11_ESS_LIST_T   t_essList;
	NET_802_11_ESS_INFO_T*  p_essInfo = NULL;
	NET_802_11_BSS_INFO_T   t_CurrBss;
	NET_802_11_ESS_INFO_T   t_Ess_tmp;

	UINT8				    ui1_max_ap_num = WLAN_AP_LB_MAX_NUM;
	UINT8				    ui1_visiable_ap_num = 0;

	/* reset ap list data */
	t_wzd_nw.t_choice_connect.b_connected = FALSE;
	t_wzd_nw.t_choice_connect.ui1_visiable_ap_num = 0;
	t_wzd_nw.t_choice_connect.t_essList.ui4_NumberOfItems = 0;
	c_memset(t_wzd_nw.t_choice_connect.aui1_ap_map, 0 , sizeof(t_wzd_nw.t_choice_connect.aui1_ap_map));

	c_memset(&t_essList, 0 , sizeof(NET_802_11_ESS_LIST_T));
	i4_ret =  a_nw_wlan_get_ess_list(&t_essList);
	RET_ON_ERR(i4_ret);

	/* get current connected bss info */
	c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    if(i4_ret != NWR_OK)
    {
        c_memset(t_CurrBss.t_Bssid, 0, sizeof(t_CurrBss.t_Bssid));
        t_CurrBss.t_Ssid.ui4_SsidLen = 0;
    }
	if ((t_CurrBss.t_Ssid.ui4_SsidLen > 0)
        &&((UINT8)WLAN_WPA_COMPLETED == t_CurrBss.u8_wpa_status))
    {
        t_wzd_nw.t_choice_connect.b_connected = TRUE;
    }

	if (t_essList.ui4_NumberOfItems == 0)
	{
		return WZDR_OK;
	}

	/* sort wlan ap list  */
	do
    {
        if (FALSE == t_wzd_nw.t_choice_connect.b_connected)
        {
            break;
        }

        if (t_essList.p_EssInfo[0].t_Ssid.ui4_SsidLen == t_CurrBss.t_Ssid.ui4_SsidLen &&
            0 == c_strncmp(t_essList.p_EssInfo[0].t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen))
        {
            break;
        }

        for (ui1_idx = 1; ui1_idx < (UINT8)t_essList.ui4_NumberOfItems; ui1_idx ++)
        {
            if (t_essList.p_EssInfo[ui1_idx].t_Ssid.ui4_SsidLen == t_CurrBss.t_Ssid.ui4_SsidLen &&
                0 == c_strncmp(t_essList.p_EssInfo[ui1_idx].t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen))
            {
                /* use bubble algorithm to sort. */
                for (ui1_idx_2 = ui1_idx; ui1_idx_2 > 0; ui1_idx_2--)
                {
                    c_memcpy(&t_Ess_tmp,
                             &(t_essList.p_EssInfo[ui1_idx_2]),
                             sizeof(NET_802_11_ESS_INFO_T));

                    c_memcpy(&(t_essList.p_EssInfo[ui1_idx_2]),
                             &(t_essList.p_EssInfo[ui1_idx_2-1]),
                             sizeof(NET_802_11_ESS_INFO_T));

                    c_memcpy(&(t_essList.p_EssInfo[ui1_idx_2-1]),
                             &t_Ess_tmp,
                             sizeof(NET_802_11_ESS_INFO_T));
                }

                break;
            }
        }
    }while(0);

	if (ui1_max_ap_num > (UINT8)t_essList.ui4_NumberOfItems )
	{
		ui1_max_ap_num = (UINT8)t_essList.ui4_NumberOfItems;
	}

	t_wzd_nw.t_choice_connect.t_essList.ui4_NumberOfItems = ui1_max_ap_num;
	if (t_wzd_nw.t_choice_connect.t_essList.p_EssInfo != NULL)
	{
		c_mem_free(t_wzd_nw.t_choice_connect.t_essList.p_EssInfo);
	}

	t_wzd_nw.t_choice_connect.t_essList.p_EssInfo = (NET_802_11_ESS_INFO_T*)c_mem_alloc((sizeof(NET_802_11_ESS_INFO_T))*ui1_max_ap_num);
	if (t_wzd_nw.t_choice_connect.t_essList.p_EssInfo == NULL)
	{
		return WZDR_OUT_OF_MEM;
	}

	c_memcpy(t_wzd_nw.t_choice_connect.t_essList.p_EssInfo, t_essList.p_EssInfo, (sizeof(NET_802_11_ESS_INFO_T))*(ui1_max_ap_num));

	for (ui1_idx = 0; ui1_idx < ui1_max_ap_num; ui1_idx ++)
	{
		p_essInfo = &t_essList.p_EssInfo[ui1_idx];

		if (p_essInfo->t_Ssid.ui4_SsidLen == 0 ||
            p_essInfo->t_Ssid.ui1_aSsid[0] == 0)
		{
			continue;
		}

		if (_wzd_nw_is_filter_out_ssid(p_essInfo->t_Ssid.ui1_aSsid))
        {
            continue;
        }

		/* re-map visiable ap list */
		if (p_essInfo->i4_isConnected != 0 && t_wzd_nw.t_choice_connect.b_connected)
        {
            t_wzd_nw.t_choice_connect.aui1_ap_map[0] = ui1_idx;
        }
		else
		{
			t_wzd_nw.t_choice_connect.aui1_ap_map[ui1_visiable_ap_num] = ui1_idx;
		}

		ui1_visiable_ap_num ++;
	}

	t_wzd_nw.t_choice_connect.ui1_visiable_ap_num = ui1_visiable_ap_num;

	DBG_LOG_PRINT(("[WZD][NW] --- total AP num: %d. visiable AP num: %d.\n",
				ui1_max_ap_num,
				ui1_visiable_ap_num));

	return WZDR_OK;
}

#if 0
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_vkb_set_suggest_txt
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_vkb_set_suggest_txt(VOID)
{
	UINT16  				ui2_mlm;
    INT32       			i4_ret;
	NET_802_11_ASSOCIATE_T* pt_associate = NULL;

	i4_ret = _wzd_nw_get_associate_data(&pt_associate);
	RET_ON_ERR(i4_ret);

	if(pt_associate == NULL)
    {
        return WZDR_OK;
    }

    switch(pt_associate->e_AuthMode)
    {
    case IEEE_802_11_AUTH_MODE_OPEN:
    case IEEE_802_11_AUTH_MODE_SHARED:
    case IEEE_802_11_AUTH_MODE_WEPAUTO:
        ui2_mlm = MLM_WZD_KEY_NETWORK_PWS_TIT_WEP;
        break;
    case IEEE_802_11_AUTH_MODE_WPA2:
    case IEEE_802_11_AUTH_MODE_WPA2_PSK:
        ui2_mlm = MLM_WZD_KEY_NETWORK_PWS_TIT_WPA2;
        break;

    case IEEE_802_11_AUTH_MODE_WPA:
    case IEEE_802_11_AUTH_MODE_WPA_PSK:
    case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
        ui2_mlm = MLM_WZD_KEY_NETWORK_PWS_TIT_WPA;
        break;
    default:
        ui2_mlm = MLM_WZD_KEY_EMPTY;
        break;
    }

	t_wzd_nw.t_vkb.t_title.ui2_msg_idx = ui2_mlm;
    i4_ret = _wzd_nw_text_set_text(t_wzd_nw.t_vkb.t_title.h_widget,
                                   t_wzd_nw.t_vkb.t_title.ui2_msg_idx);

    RET_ON_ERR(i4_ret);

	return WZDR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_vkb_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_vkb_show(HANDLE_T              h_widget,
                              WZD_NW_VKB_STYLE_E    e_vkb_style)
{
    INT32  i4_ret;

    switch(e_vkb_style)
    {
    case WZD_NW_VKB_INFO_REG:
    {
        UINT8       ui1_loop;
        UTF16_T     pw2s_content[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
        for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY; ui1_loop++)
        {
            if(t_wzd_nw.t_info_reg.ah_editbox[ui1_loop] == h_widget)
            {
                 t_wzd_nw.t_info_reg.e_current_item = ui1_loop;
            }
        }
        i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_info,
                              VKB_CMD_CLEAR_TEXT,
                              (VOID*)NULL,
                              (VOID*)NULL);
        RET_ON_ERR(i4_ret);
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_EB_GET_TEXT,
                              WGL_PACK(pw2s_content),
                              WGL_PACK(WZD_NW_EB_TXT_MAX_LEN));
        RET_ON_ERR(i4_ret);

        c_uc_w2s_strncpy(t_wzd_nw.t_info_reg.aw2s_editbox_context[t_wzd_nw.t_info_reg.e_current_item], pw2s_content, WZD_NW_EB_TXT_MAX_LEN);

        i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_info,
                              VKB_CMD_SET_INITIAL_TEXT,
                              (VOID*)pw2s_content,
                              (VOID*)0XFF);
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_info_reg_frm, WGL_SW_RECURSIVE);
        RET_ON_ERR(i4_ret);

        i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_info, TRUE);
        RET_ON_ERR(i4_ret);
    }
        break;
    case WZD_NW_VKB_MANU_SSID:
    {
        i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_ssid,
                              VKB_CMD_CLEAR_TEXT,
                              (VOID*)NULL,
                              (VOID*)NULL);
        RET_ON_ERR(i4_ret);

		i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_ssid, TRUE);
        RET_ON_ERR(i4_ret);
    }
        break;
    case WZD_NW_VKB_PWD_INPUT:
    {
        i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_pwd,
                              VKB_CMD_CLEAR_TEXT,
                              (VOID*)NULL,
                              (VOID*)NULL);
        RET_ON_ERR(i4_ret);

		i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_pwd, TRUE);
        RET_ON_ERR(i4_ret);
    }
        break;

    default :
        break;
    }

    t_wzd_nw.t_vkb.e_vkb_style = e_vkb_style;
    t_wzd_nw.t_vkb.b_vkb_show = TRUE;

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_store_idx_to_ui_idx(UINT8 ui1_idx)
 *
 * Description:convett the store index of e_mail,first name,last name,zip code and offer contact to ui idx.
 *
 * Inputs:store index
 *
 * Outputs:ui index
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_store_idx_to_ui_idx(UINT8 ui1_idx)
{
    switch (ui1_idx)
    {
        /*zip code*/
        case 0:
            ui1_idx=4;
            break;
        /*phone num*/
        case 1:
            ui1_idx=3;
            break;
        /*first name*/
        case 2:
            ui1_idx=1;
            break;
        /*last name*/
        case 3:
            ui1_idx=2;
            break;
         /*e-mail*/
        case 4:
            ui1_idx=0;
            break;
        /*offer contact*/
        case 5:
            ui1_idx=5;
            break;

        default:
            ui1_idx=0;
            break;
    }

    return ui1_idx;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_json_merge
 *
 * Description:merge reg info:e_mail,first name,last name,zip code and offer contact into one group.
 *             add: serial num, mac address,firmware version and data time
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_json_merge(CHAR **pstr_in, CHAR **pstr_out)
{
    CHAR    s_sn[WZD_NW_REG_INFO_SN_LEN+1] = {0};
    CHAR    s_sn_json[WZD_NW_REG_INFO_SN_JSON_LEN+1] = {0};
    CHAR    s_mac[WZD_NW_REG_INFO_MAC_LEN+1] = {0};
    CHAR    s_mac_json[WZD_NW_REG_INFO_MAC_JSON_LEN+1] = {0};
    CHAR    s_vn_json[WZD_NW_REG_INFO_VN_JSON_LEN+1] = {0};
    CHAR    s_dt[WZD_NW_REG_INFO_DT_LEN+1] = {0};
    CHAR    s_dt_json[WZD_NW_REG_INFO_DT_JSON_LEN+1] = {0};
    DTG_T   t_dtg = {0};
    UINT32  ui4_buff_len = sizeof(s_sn);
    INT32   i4_ret = WZDR_OK;
    BOOL    b_is_get_time = FALSE;
    UINT8	ui1_loop = 0;

    if(NULL == pstr_in)
    {
        DBG_LOG_PRINT(("\n%s(%d)#### invalid arg\n",__FUNCTION__,__LINE__));
        return WZDR_INV_ARG;
    }

    /*get and convert serial num*/
    i4_ret = WZDR_FAIL;//a_uli_get_serial_number((UINT8 *)s_sn, &ui4_buff_len);
    if(WZDR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s(%d)#### a_uli_get_serial_number FAIL return[%d], ui4_buff_len=%d\n",__FUNCTION__,__LINE__,i4_ret,ui4_buff_len));
    }
    else
    {
        c_base64_encode(s_sn,c_strlen(s_sn),s_sn_json,WZD_NW_REG_INFO_SN_JSON_LEN);
    }

    /*get and convert mac address*/
    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac);
    c_base64_encode(s_mac,c_strlen(s_mac),s_mac_json,WZD_NW_REG_INFO_MAC_JSON_LEN);

    /*get and convert firmware version*/
    c_base64_encode(sys_cust_get_usb_upg_version(),c_strlen(sys_cust_get_usb_upg_version()),s_vn_json,WZD_NW_REG_INFO_VN_JSON_LEN);

    /*get and convert data time*/
    b_is_get_time = a_dst_get_local_time(&t_dtg);
    if(TRUE == b_is_get_time)
    {
        /*format:yr-mo-day hr:min:sec*/
        c_sprintf(s_dt,"%d-%d-%d %d:%d:%d",t_dtg.ui2_yr,t_dtg.ui1_mo,t_dtg.ui1_day,t_dtg.ui1_hr,t_dtg.ui1_min,t_dtg.ui1_sec);
    }

    c_base64_encode(s_dt,c_strlen(s_dt),s_dt_json,WZD_NW_REG_INFO_DT_JSON_LEN);

    /*merge str and the sequence is: MA->VN->DT->ZC->PH->FN->LN->EM->OC->SN*/

    /*merge MA:mac address str*/
    c_strcat(pstr_out[0],WZD_NW_MAC_JSON_KEY);
    c_strcat(pstr_out[0],s_mac_json);
    c_strcat(pstr_out[0],"',");

    /*merge VN:firmware version str*/
    c_strcat(pstr_out[0],WZD_NW_VN_JSON_KEY);
    c_strcat(pstr_out[0],s_vn_json);
    c_strcat(pstr_out[0],"',");

    /*merge DT:data time str*/
    c_strcat(pstr_out[0],WZD_NW_DT_JSON_KEY);
    c_strcat(pstr_out[0],s_dt_json);
    c_strcat(pstr_out[0],"',");

    do
    {
        ui1_loop=0;
        /*merge zip code str*/
        c_strcat(pstr_out[0],WZD_NW_ZIP_CODE_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[_wzd_nw_reg_info_store_idx_to_ui_idx(ui1_loop++)]);
        c_strcat(pstr_out[0],"',");

        /*merge phone num str*/
        c_strcat(pstr_out[0],WZD_NW_PHONE_NUM_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[_wzd_nw_reg_info_store_idx_to_ui_idx(ui1_loop++)]);
        c_strcat(pstr_out[0],"',");

        /*merge first name str*/
        c_strcat(pstr_out[0],WZD_NW_FIRST_NAME_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[_wzd_nw_reg_info_store_idx_to_ui_idx(ui1_loop++)]);
        c_strcat(pstr_out[0],"',");

        /*merge last name str*/
        c_strcat(pstr_out[0],WZD_NW_LAST_NAME_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[_wzd_nw_reg_info_store_idx_to_ui_idx(ui1_loop++)]);
        c_strcat(pstr_out[0],"',");

        /*merge email str*/
        c_strcat(pstr_out[0],WZD_NW_EMAIL_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[_wzd_nw_reg_info_store_idx_to_ui_idx(ui1_loop++)]);
        c_strcat(pstr_out[0],"',");

        /*merge offer contact str*/
        c_strcat(pstr_out[0],WZD_NW_OFFER_CONTACT_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[_wzd_nw_reg_info_store_idx_to_ui_idx(ui1_loop)]);
        c_strcat(pstr_out[0],"',");
    }
    while (0);

    /*merge SN:serial num str*/
    c_strcat(pstr_out[0],WZD_NW_SN_JSON_KEY);
    c_strcat(pstr_out[0],s_sn_json);
    c_strcat(pstr_out[0],"'}");

    DBG_LOG_PRINT(("\n%s(%d)####pstr=%s\n",__FUNCTION__,__LINE__,pstr_out[0]));

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_set
 *
 * Description: set nw reg info to /3rd_rw/wzd_reg_info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_set(VOID)
{
	UINT8	ui1_loop = 0;
	CHAR 	*p_reg_info[WZD_NW_REG_INFO_LAST_ENTRY];

    for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY; ui1_loop++)
    {
    	p_reg_info[ui1_loop] = (CHAR *)c_mem_alloc((WZD_NW_EB_TXT_MAX_LEN + 1)*sizeof(CHAR));
		if(NULL == p_reg_info[ui1_loop])
		{
			return WZDR_FAIL;
		}
		c_memset(p_reg_info[ui1_loop], 0, (WZD_NW_EB_TXT_MAX_LEN + 1)*sizeof(CHAR));
    	c_uc_w2s_to_ps(t_wzd_nw.t_info_reg.aw2s_editbox_context[ui1_loop],p_reg_info[ui1_loop], WZD_NW_EB_TXT_MAX_LEN);
    }

    /*store reg info--email/first name/last name/phone num/zip code to file*/
    a_cfg_custom_set_reg_info(p_reg_info,WZD_NW_REG_INFO_LAST_ENTRY);

	/* free memory*/
	for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY; ui1_loop++)
	{
		if (p_reg_info[ui1_loop] != NULL)
		{
    	    c_mem_free(p_reg_info[ui1_loop]);
		}
    }

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_info_reg_store_user_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_info_reg_store_user_info(VOID)
{
    INT32	i4_ret;
	UINT8	ui1_loop = 0;
	BOOL   	b_mail_pushed = FALSE;
	CHAR 	*apszRegStoreValues[WZD_NW_REG_INFO_LAST_ENTRY + 1];
    CHAR 	*pstr_json[WZD_NW_REG_INFO_LAST_ENTRY + 1];
    CHAR 	*pstr_json_merge[WZD_NW_REG_INFO_GROUP_NUM];

	/* get user data */
    for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY; ui1_loop++)
    {
    	apszRegStoreValues[ui1_loop] = (CHAR *)c_mem_alloc((WZD_NW_EB_TXT_MAX_LEN + 1)*sizeof(CHAR));
		if(NULL == apszRegStoreValues[ui1_loop])
		{
			return WZDR_FAIL;
		}
		c_memset(apszRegStoreValues[ui1_loop], 0, (WZD_NW_EB_TXT_MAX_LEN + 1)*sizeof(CHAR));
    	c_uc_w2s_to_ps(t_wzd_nw.t_info_reg.aw2s_editbox_context[ui1_loop],apszRegStoreValues[ui1_loop], WZD_NW_EB_TXT_MAX_LEN);
    }

	/* get checkbox info */
	apszRegStoreValues[WZD_NW_REG_INFO_LAST_ENTRY] = (CHAR *)c_mem_alloc((WZD_NW_EB_TXT_MAX_LEN + 1)*sizeof(CHAR));
	if(NULL == apszRegStoreValues[WZD_NW_REG_INFO_LAST_ENTRY])
	{
		return WZDR_FAIL;
	}
	c_memset(apszRegStoreValues[WZD_NW_REG_INFO_LAST_ENTRY], 0, (WZD_NW_EB_TXT_MAX_LEN + 1)*sizeof(CHAR));
    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.h_mail_accept_checkbox,
                         WGL_CMD_BTN_GET_PUSHED,
                         &b_mail_pushed,
                         NULL);
    if(b_mail_pushed)
	{
		c_strncpy(apszRegStoreValues[WZD_NW_REG_INFO_LAST_ENTRY], "yes", WZD_NW_EB_TXT_MAX_LEN);
	}
	else
	{
		c_strncpy(apszRegStoreValues[WZD_NW_REG_INFO_LAST_ENTRY], "no", WZD_NW_EB_TXT_MAX_LEN);
	}
    /*convert string to json data format base 64 encode*/
     for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY + 1; ui1_loop++)
     {
         pstr_json[ui1_loop] = (CHAR *)c_mem_alloc((WZD_NW_REG_INFO_JSON_TXT_MAX_LEN + 1)*sizeof(CHAR));

         if(NULL == pstr_json[ui1_loop])
         {
             DBG_LOG_PRINT(("\n%s(%d)#### alloc memory fail\n",__FUNCTION__,__LINE__));
             return WZDR_FAIL;
         }

         c_memset(pstr_json[ui1_loop], 0, (WZD_NW_REG_INFO_JSON_TXT_MAX_LEN + 1)*sizeof(CHAR));

         i4_ret = c_base64_encode(apszRegStoreValues[ui1_loop],c_strlen(apszRegStoreValues[ui1_loop]),pstr_json[ui1_loop],WZD_NW_REG_INFO_JSON_TXT_MAX_LEN);
         DBG_LOG_PRINT(("\n%s(%d)####string=%s,json=%s,ui1_json_len=%d\n",__FUNCTION__,__LINE__,apszRegStoreValues[ui1_loop],pstr_json[ui1_loop],i4_ret));
    }

    /*alloc memory for merged str*/
	for(ui1_loop = 0; ui1_loop < WZD_NW_REG_INFO_GROUP_NUM; ui1_loop++)
    {
        pstr_json_merge[ui1_loop] = (CHAR *)c_mem_alloc((WZD_NW_REG_INFO_JSON_TXT_GROUP_MAX_LEN + 1)*sizeof(CHAR));

		if(NULL == pstr_json_merge[ui1_loop])
		{
            DBG_LOG_PRINT(("\n%s(%d)#### alloc memory fail\n",__FUNCTION__,__LINE__));
			return WZDR_FAIL;
		}

        c_memset(pstr_json_merge[ui1_loop], 0, (WZD_NW_REG_INFO_JSON_TXT_GROUP_MAX_LEN + 1)*sizeof(CHAR));
    }

    /*merge reg info to one group*/
    i4_ret = _wzd_nw_reg_info_json_merge(pstr_json,pstr_json_merge);
    RET_ON_ERR(i4_ret);

	/* call ULI api to store user info */
    /*i4_ret = a_uli_project_reg_store_user_info (
                             (UINT8**)pstr_json_merge,
                             (UINT8) WZD_NW_REG_INFO_GROUP_NUM);*/
	/* free memory*/
	for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY + 1; ui1_loop++)
	{
		if (apszRegStoreValues[ui1_loop] != NULL)
		{
    	    c_mem_free(apszRegStoreValues[ui1_loop]);
		}

		if (pstr_json[ui1_loop] != NULL)
		{
    	    c_mem_free(pstr_json[ui1_loop]);
		}
    }

	for(ui1_loop = 0; ui1_loop < WZD_NW_REG_INFO_GROUP_NUM; ui1_loop++)
    {
        if (pstr_json_merge[ui1_loop]!= NULL)
        {
            c_mem_free(pstr_json_merge[ui1_loop]);
        }
    }

    if (0 != i4_ret)
    {
        DBG_LOG_PRINT(("<WZD Network> ---  failed, return_value=%d\n", i4_ret));
        return WZDR_FAIL;
    }

	return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_info_eb_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_info_eb_proc_fct(HANDLE_T   h_widget,
                                      UINT32     ui4_msg,
                                      VOID*      param1,
                                      VOID*      param2)
{
    UINT8        ui1_loop = 0;
    INT32        i4_ret;
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        UTF16_T     pw2s_content[WZD_NW_KEY_MAX_LEN+1] = {0};

        for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY; ui1_loop++)
        {
           if(t_wzd_nw.t_info_reg.ah_editbox[ui1_loop] == h_widget)
           {
               c_uc_w2s_strncpy(pw2s_content, t_wzd_nw.t_info_reg.aw2s_editbox_context[ui1_loop], WZD_NW_KEY_MAX_LEN);
               break;
           }
        }

	    i4_ret = c_wgl_do_cmd (h_widget,
                               WGL_CMD_EB_SET_TEXT,
                               WGL_PACK(pw2s_content),
                               WGL_PACK(c_uc_w2s_strlen(pw2s_content)));
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_EB_SET_CURSOR_POS,
                              WGL_PACK(c_uc_w2s_strlen(pw2s_content)),
                              NULL);
        RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_do_cmd (h_widget,
                               WGL_CMD_EB_ENABLE_CURSOR_HT,
                               WGL_PACK(TRUE),
                               NULL);
        RET_ON_ERR(i4_ret);

    }
        break;
    case WGL_MSG_LOSE_FOCUS:
    {
        UTF16_T     pw2s_content[WZD_NW_KEY_MAX_LEN+1] = {0};

        for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY; ui1_loop++)
        {
             if(t_wzd_nw.t_info_reg.ah_editbox[ui1_loop] == h_widget)
             {
                i4_ret = c_wgl_do_cmd(h_widget,
                                      WGL_CMD_EB_GET_TEXT,
                                      WGL_PACK(pw2s_content),
                                      WGL_PACK(WZD_NW_KEY_MAX_LEN));
                RET_ON_ERR(i4_ret);
                c_uc_w2s_strncpy(t_wzd_nw.t_info_reg.aw2s_editbox_context[ui1_loop], pw2s_content, WZD_NW_KEY_MAX_LEN);
                break;
             }
        }
    }
        break;
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        UTF16_T     w2s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
        UINT32      ui4_len = 0;

        for(UINT8 ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY; ui1_loop++)
        {
            if(t_wzd_nw.t_info_reg.ah_editbox[ui1_loop] == h_widget)
            {
                 t_wzd_nw.t_info_reg.e_current_item = ui1_loop;
            }
        }
        if (((BTN_DIGIT_0 <= ui4_keycode) && (BTN_DIGIT_9 >= ui4_keycode)) ||
        	((BTN_KB_NULL <= ui4_keycode) && (BTN_KB_HYPER >= ui4_keycode)))
        {
			 WGL_IMG_INFO_T              t_img_info;
			 e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;
			if(t_wzd_nw.t_info_reg.e_current_item == WZD_NW_REG_INFO_MAIL)
	        {
				i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL],
	                                  WGL_CMD_EB_GET_TEXT,
	                                  WGL_PACK (w2s_str),
	                                  WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
		        RET_ON_ERR(i4_ret);
		        ui4_len = c_uc_w2s_strlen(w2s_str);
		        if(ui4_len > 0)
		        {
		            RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
	            }
	            else
	            {
		            RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
	            }
	        }
	        /* Set background images */
		    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
		    t_img_info.e_type = WGL_IMG_SET_STANDARD;
		    t_img_info.u_img_data.t_standard.t_enable       = h_g_wzd_img_textBox_register;
		    t_img_info.u_img_data.t_standard.t_highlight	= h_g_wzd_img_textBox_register_highlight;

		    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
		                          WGL_CMD_GL_SET_IMAGE,
		                          WGL_PACK(WGL_IMG_BK),
		                          WGL_PACK(&t_img_info));
			RET_ON_ERR(i4_ret);

			/* Set icon before the editbox */
			c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
		    t_img_info.e_type = WGL_IMG_SET_EXTEND;
		    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
		    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
		    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
		                          WGL_CMD_BDR_TIMG_SET_ICON,
		                          WGL_PACK(&t_img_info),
		                          WGL_PACK(NULL) );
		    RET_ON_ERR(i4_ret);

		    _wzd_nw_reg_info_update_eb_content(t_wzd_nw.t_info_reg.e_current_item);
		    DBG_LOG_PRINT(("\n####[wzd_reg_info%s(%d)]\n",__FUNCTION__,__LINE__));

	        i4_ret = wzd_view_main_frm_repaint();
	        RET_ON_ERR(i4_ret);
        }

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        case BTN_CURSOR_RIGHT:
        {
	        WGL_IMG_INFO_T              t_img_info;

			_wzd_nw_vkb_show(h_widget, WZD_NW_VKB_INFO_REG);
			i4_ret = a_vkb_set_focus(t_wzd_nw.t_vkb.h_vkb_info);
	        RET_ON_ERR(i4_ret);

			/* Set icon before the editbox */
			c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
		    t_img_info.e_type = WGL_IMG_SET_EXTEND;
		    t_img_info.u_img_data.t_extend.t_enable             = h_g_wzd_img_text_focus;
		    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
		    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
		                          WGL_CMD_BDR_TIMG_SET_ICON,
		                          WGL_PACK(&t_img_info),
		                          WGL_PACK(NULL) );
		    RET_ON_ERR(i4_ret);

			i4_ret = wzd_view_main_frm_repaint();
	    	RET_ON_ERR(i4_ret);
        }
            return WZDR_OK;
        case BTN_CURSOR_LEFT:
        case BTN_KB_CURSOR_LEFT:
        case BTN_KB_BACKSPACE:
        {
			UTF16_T     w2s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
	        UINT32      ui4_len = 0;

            c_wgl_default_msg_proc(h_widget, ui4_msg, (VOID*)BTN_KB_BACKSPACE, param2);

			e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;
			if(t_wzd_nw.t_info_reg.e_current_item == WZD_NW_REG_INFO_MAIL)
	        {
				i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_EB_GET_TEXT,
                              WGL_PACK (w2s_str),
                              WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
		        RET_ON_ERR(i4_ret);
		        ui4_len = c_uc_w2s_strlen(w2s_str);
		        if(ui4_len > 0)
		        {
		            RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
	            }
		        else
		        {
		            RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
		        }
	        }
            i4_ret = wzd_view_main_frm_repaint();
	    	RET_ON_ERR(i4_ret);
        }
            return WZDR_OK;
        case BTN_CURSOR_DOWN:
        {
			UTF16_T     w2s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
            CHAR        s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};

            i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_EB_GET_TEXT,
                              WGL_PACK (w2s_str),
                              WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
	        RET_ON_ERR(i4_ret);

            c_uc_w2s_to_ps(w2s_str,s_str,WZD_NW_EB_TXT_MAX_LEN+1);

            if ((_wzd_nw_reg_info_is_valid(s_str,c_strlen(s_str))) ||
                (t_wzd_nw.t_info_reg.b_warning_dlg_is_show[t_wzd_nw.t_info_reg.e_current_item]))
            {
                if (WZD_NW_REG_INFO_ZIP_CODE == t_wzd_nw.t_info_reg.e_current_item)
                {
                    i4_ret = c_wgl_set_focus(t_wzd_nw.t_info_reg.h_mail_accept_checkbox, TRUE);
                    RET_ON_ERR(i4_ret);
                }
                else
                {
                    i4_ret = c_wgl_set_focus(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item+1], TRUE);
                    RET_ON_ERR(i4_ret);
                }
            }
            else
            {
                _wzd_nw_reg_info_warning_dlg_create(t_wzd_nw.t_info_reg.e_current_item);
            }

            break;
        }
        default:
        {
            UINT32      ui4_input_limit = 0;
            UTF16_T     w2s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
            UINT32      ui4_len = 0;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_EB_GET_INPUT_LIMIT,
                                  WGL_PACK(&ui4_input_limit),
                                  NULL);
            RET_ON_ERR(i4_ret);

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_EB_GET_TEXT,
                                  WGL_PACK (w2s_str),
                                  WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
            RET_ON_ERR(i4_ret);

            ui4_len = c_uc_w2s_strlen(w2s_str);
            if (ui4_len >= ui4_input_limit-1)
            {
                return WGLR_OK;
            }

            if (((BTN_DIGIT_0 <= ui4_keycode) && (BTN_DIGIT_9 >= ui4_keycode)) ||
	        	((BTN_KB_NULL <= ui4_keycode) && (BTN_KB_HYPER >= ui4_keycode)))
	        {
				 e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;
				if(t_wzd_nw.t_info_reg.e_current_item == WZD_NW_REG_INFO_MAIL)
		        {
					i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL],
	                                  WGL_CMD_EB_GET_TEXT,
	                                  WGL_PACK (w2s_str),
	                                  WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
			        RET_ON_ERR(i4_ret);
			        ui4_len = c_uc_w2s_strlen(w2s_str);
			        if(ui4_len > 0)
			        {
			            RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
			        }
			        else
			        {
			            RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
			        }
				}
			}

        }
            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_vkb_edit_box_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_vkb_edit_box_create(
										HANDLE_T             h_parent,
										GL_RECT_T*           pt_rect,
										UINT32               ui4_left_inset,
										UINT32               ui4_right_inset,
										UINT32               ui4_style,
										wgl_widget_proc_fct  pf_wdgt_proc,
										HANDLE_T*            ph_widget
										)
{
    INT32                       i4_ret = WZDR_OK;
    WGL_INSET_T                 t_inset;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_EB_KEY_MAP_T            t_eb_key_map;
    GL_RECT_T                   t_rect;
    WGL_BDR_TIMG_ICON_INFO_T    t_title_icon_info;

    /* create editbox */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 pt_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = ui4_left_inset;
    t_inset.i4_right    = ui4_right_inset;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Cnt Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left = 20 * WZD_UI_RATIO_W;
	t_inset.i4_right = 80 * WZD_UI_RATIO_W;
	t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

#if 0
	t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size = WZD_EB_TXT_FNT_SIZE;
#else
	t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
#endif

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    /* Set txt color */
    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_edt_enable_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_edt_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_edt_enable_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_ENABLE_CURSOR_HT,
                           WGL_PACK (TRUE),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_wzd_color_edt_enable_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_wzd_color_edt_enable_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_wzd_color_edt_hlt_txt;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_EB_CURSOR),
                           WGL_PACK(& t_clr_info));
    RET_ON_ERR(i4_ret);

    /* Set background images */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = h_g_wzd_img_text_box;
    t_img_info.u_img_data.t_standard.t_highlight    = h_g_wzd_img_text_box_hlt;
    t_img_info.u_img_data.t_standard.t_disable      = h_g_wzd_img_text_box;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

	/* Set Border Icon */
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      ui4_left_inset - WZD_NW_EDIT_BOX_HL_ICON_W,
                      (WZD_NW_PWD_EB_H - WZD_NW_EDIT_BOX_HL_ICON_H)/2,
                      WZD_NW_EDIT_BOX_HL_ICON_W,
                      WZD_NW_EDIT_BOX_HL_ICON_H);
    c_memset(&t_title_icon_info, 0, sizeof(WGL_BDR_TIMG_ICON_INFO_T));
    t_title_icon_info.t_rc_ref  = t_rect;
    t_title_icon_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_ICON_INFO,
                          WGL_PACK(&t_title_icon_info),
                          WGL_PACK(NULL));
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_disable            = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push               = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_ICON,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL) );
    RET_ON_ERR(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_ALWAYS_HT),
                          WGL_PACK(WGL_EB_ALWAYS_HT));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS));
    RET_ON_ERR(i4_ret);

    /* Set Char support */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_CHAR_SUPPORT),
                          WGL_PACK(WGL_EB_CHAR_SUPPORT));
    RET_ON_ERR(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_backsapce = BTN_KB_BACKSPACE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_info_reg_edit_box_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_info_reg_edit_box_create(
										HANDLE_T             h_parent,
										UINT32               ui4_top,
										UINT32               ui4_left_inset,
										UINT32               ui4_right_inset,
										UINT32               ui4_style,
										wgl_widget_proc_fct  pf_wdgt_proc,
										HANDLE_T*            ph_widget
										)
{
    INT32                       i4_ret = WZDR_OK;
    WGL_INSET_T                 t_inset;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_EB_KEY_MAP_T            t_eb_key_map;
    GL_RECT_T                   t_rect;
    WGL_BDR_TIMG_ICON_INFO_T    t_title_icon_info;
    /* underline */
    UTF16_T                     w2s_cursor =(UTF16_T) 0x005F;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE (&t_rect,
                      WZD_NW_INFO_REG_EDIT_BOX_X,
                      ui4_top,
                      WZD_NW_INFO_REG_EDIT_BOX_W,
                      WZD_NW_INFO_REG_EDIT_BOX_H);
    /* create editbox */
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_EDIT_BOX,
                                 WGL_CONTENT_EDIT_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = ui4_left_inset;
    t_inset.i4_right    = ui4_right_inset;
    t_inset.i4_top      = WZD_NW_EDIT_BOX_TOP_INSET;
    t_inset.i4_bottom   = WZD_NW_EDIT_BOX_BOTTOM_INSET + (8 * WZD_UI_RATIO);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Cnt Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left = 18 * WZD_UI_RATIO_W;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

    /* Set txt color */
    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_seti_lst_col_dis_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_seti_lst_col_dis_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));

    /* Set the cursor highlight */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_ENABLE_CURSOR_HT,
                           WGL_PACK (TRUE),
                           NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_EB_SET_CURSOR_CHAR,
                           (VOID*)(&w2s_cursor),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_wzd_color_seti_lst_col_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_wzd_color_seti_lst_col_hlt_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_wzd_color_seti_lst_col_txt;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_EB_CURSOR),
                           WGL_PACK(& t_clr_info));
    RET_ON_ERR(i4_ret);

    /* Set background images */
    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable       = h_g_wzd_img_textBox_register;
    t_img_info.u_img_data.t_standard.t_highlight    = h_g_wzd_img_textBox_register_highlight;
    t_img_info.u_img_data.t_standard.t_disable      = h_g_wzd_img_textBox_register;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      ui4_left_inset - WZD_NW_EDIT_BOX_HL_ICON_W,
                      (WZD_NW_INFO_REG_EDIT_BOX_H - WZD_NW_EDIT_BOX_HL_ICON_H)/2,
                      WZD_NW_EDIT_BOX_HL_ICON_W,
                      WZD_NW_EDIT_BOX_HL_ICON_H);
    c_memset(&t_title_icon_info, 0, sizeof(WGL_BDR_TIMG_ICON_INFO_T));
    t_title_icon_info.t_rc_ref  = t_rect;
    t_title_icon_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_ICON_INFO,
                          WGL_PACK(&t_title_icon_info),
                          WGL_PACK(NULL));
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_wzd_img_text_focus;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push               = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_ICON,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL) );
    RET_ON_ERR(i4_ret);

    /* Set pos style */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_CURSOR_CHAR,
                          (VOID*)WZD_CUSTOM_TEXT("|"),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Auto Edit */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING),
                          WGL_PACK(WGL_EB_EA_AUTO_EDITING));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS),
                          WGL_PACK(WGL_EB_KEEP_CURSOR_POS));
    RET_ON_ERR(i4_ret);

    /* Set Char support */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_EXT_ATTR,
                          WGL_PACK(WGL_EB_CHAR_SUPPORT),
                          WGL_PACK(WGL_EB_CHAR_SUPPORT));
    RET_ON_ERR(i4_ret);

    /* Set Key Map */
    c_memset(&t_eb_key_map, 0, sizeof(WGL_EB_KEY_MAP_T));
    t_eb_key_map.ui4_backsapce = BTN_KB_BACKSPACE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_EB_SET_KEY_MAP,
                          WGL_PACK(&t_eb_key_map),
                          NULL);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_create(HANDLE_T      h_parent,
                                          INT32     i4_left,
                                          INT32     i4_top,
                                          INT32     i4_width,
                                          INT32     i4_height,
                                          HANDLE_T  h_normal_bk,
                                          HANDLE_T  h_highlight_bk,
                                          HANDLE_T* ph_widget)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      i4_left,
                      i4_top,
                      i4_width,
                      i4_height);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)( WGL_STL_TEXT_MULTISTRING |
                                 WGL_STL_TEXT_MAX_DIS_40_LINE   |
                                 WGL_STL_TEXT_IGNORE_NEWLINE),
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* set alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK (WGL_AS_LEFT_TOP),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);


    t_inset.i4_left     = 10 * WZD_UI_RATIO_W;
    t_inset.i4_right    = 10 * WZD_UI_RATIO_W;
    t_inset.i4_top      = 2 * WZD_UI_RATIO_W;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, wzd_view_get_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    RET_ON_ERR(i4_ret);

    /* txt info */
    c_memset(&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_enable   ,&t_g_wzd_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_highlight,&t_g_wzd_color_network_txt_hlt);
    COLOR_COPY(&t_clr_info.u_color_data.t_standard.t_disable  ,&t_g_wzd_color_network_txt_hlt);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_normal_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_highlight_bk;
    t_img_info.u_img_data.t_standard.t_disable   = h_normal_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          WGL_PACK ((INT32) 1),
                          NULL);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_btn_widget_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_btn_widget_proc_fct(HANDLE_T   h_widget,
		                                 UINT32     ui4_msg,
		                                 VOID*      param1,
		                                 VOID*      param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        	case BTN_CURSOR_DOWN:
            {
				if (h_widget == t_wzd_nw.t_protocol.t_protocol_policy.h_widget)
                {
                	RET_ON_ERR(_wzd_nw_footer_btn_focus());
				}
            }
            break;
            case BTN_SELECT:
            {
                if (WZD_NW_PROTOCOL_SCAN_NULL == t_wzd_nw.t_protocol.e_scan_text)
                {
					if (h_widget == t_wzd_nw.t_protocol.t_protocol_terms.h_widget)
					{
						t_wzd_nw.t_protocol.e_scan_text = WZD_NW_PROTOCOL_SCAN_TERMS;
					}
					else if (h_widget == t_wzd_nw.t_protocol.t_protocol_policy.h_widget)
					{
						t_wzd_nw.t_protocol.e_scan_text = WZD_NW_PROTOCOL_SCAN_POLICY;
					}

					_wzd_nw_protocol_text_frame_show();

					return WZDR_OK;
                }
            }
                break;
            case BTN_EXIT:
                return WZDR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_btn_widget_create
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
static INT32 _wzd_nw_btn_widget_create(
    HANDLE_T                    h_parent,
    UTF16_T*                    ws_text,
    const GL_RECT_T*            pt_rect,
    wgl_widget_proc_fct         pf_wdgt_proc,
    HANDLE_T*                   ph_btn)
{
    WGL_IMG_INFO_T   	t_img_info;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_FONT_INFO_T     t_fnt_info;
	WGL_INSET_T         t_inset = {0};

    RET_ON_ERR (c_wgl_create_widget(h_parent,
                         HT_WGL_WIDGET_BUTTON,
                         WGL_CONTENT_BUTTON_DEF,
                         WGL_BORDER_NULL,
                         pt_rect,
                         pf_wdgt_proc,
                         255,
                         (VOID*)0,
                         NULL,
                         ph_btn));


	/* set color info */
	t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_footer_enable_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_footer_disable_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_footer_hlt_txt);

    RET_ON_ERR (c_wgl_do_cmd(
    					*ph_btn,
    					WGL_CMD_GL_SET_COLOR,
    					WGL_PACK(WGL_CLR_TEXT),
    					WGL_PACK(&t_color_info)));

    RET_ON_ERR (c_wgl_do_cmd(
                        *ph_btn,
                        WGL_CMD_BTN_SET_ALIGN,
                        WGL_PACK(WGL_AS_CENTER_CENTER),
                        NULL));

    c_memset(&t_inset, 0, sizeof(t_inset));

    /*content inset*/
    RET_ON_ERR (c_wgl_do_cmd(*ph_btn,
						WGL_CMD_BTN_SET_CNT_INSET,
						WGL_PACK(&t_inset),
						NULL));


	/* set font info */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd(
    					*ph_btn,
    					WGL_CMD_GL_SET_FONT,
    					&t_fnt_info,
    					NULL));

    /*text*/
    if(ws_text)
    {
        RET_ON_ERR (c_wgl_do_cmd(
						*ph_btn,
						WGL_CMD_BTN_SET_TEXT,
						WGL_PACK(ws_text),
						WGL_PACK((UINT16)0xFFFF)));
    }

    /* background image */
    t_img_info.e_type                                   = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_wzd_img_button;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_wzd_img_button;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_button_highlight;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_wzd_img_button;
    t_img_info.u_img_data.t_extend.t_push               = h_g_wzd_img_button;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_wzd_img_button;

    RET_ON_ERR (c_wgl_do_cmd(
						*ph_btn,
						WGL_CMD_GL_SET_IMAGE,
						WGL_PACK(WGL_IMG_BK),
						WGL_PACK(&t_img_info)));

    return WZDR_OK;
}


static INT32 _wzd_nw_wps_associate(VOID)
{
    INT32    i4_ret;
	NET_802_11_WPS_ASSOC_MODE_T e_wps_associate_mode = IEEE_802_11_PBC_SETUP;

	i4_ret = _wzd_nw_go(NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE, TRUE);
	RET_ON_ERR(i4_ret);

	/* wps associate */
	i4_ret = a_nw_custom_wlan_disassociate();
    RET_ON_ERR(i4_ret);

	i4_ret = a_nw_wlan_wps_associate(e_wps_associate_mode);
	RET_ON_ERR(i4_ret);

	t_wzd_nw.b_is_busying = TRUE;
	t_wzd_nw.b_timer_result = FALSE;
	t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

	i4_ret = c_wgl_insert(t_wzd_nw.h_timer_icon,
	                      NULL_HANDLE,
	                      WGL_INSERT_TOPMOST,
	                      FALSE);
	RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_NORMAL);
	RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_timer_icon_update(t_wzd_nw.h_timer_icon);
	RET_ON_ERR(i4_ret);

	t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_WIFI_WPS_ASSOC;
	_wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);

	return WZDR_OK;
}

static INT32 _wzd_nw_wps_associate_cancel(VOID)
{
    INT32    i4_ret;

	DBG_LOG_PRINT(("[WZD][NW] --- Cancel WPS. %s %d \n", __FUNCTION__,__LINE__));

	/* cancel wps associate */
	a_nw_wlan_wps_cancel();

	c_timer_stop(t_wzd_nw.t_choice_connect.h_timer);

	t_wzd_nw.b_is_busying = FALSE;
    t_wzd_nw.ui4_start_time = 0;


	i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_HIDE);
	RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_go(NW_SETUP_STATE_WIRELESS_PWD_INPUT, TRUE);
	RET_ON_ERR(i4_ret);

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_info_next_btn_select_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_info_next_btn_select_proc_fct()
{
    UINT8   ui1_reg_info = 1;

	/* register and restore user info */
	_wzd_nw_info_reg_store_user_info();

    /*set reg info to /3rd_rw/reg_info*/
    _wzd_nw_reg_info_set();

    a_cfg_cust_set_cust_nw_register_status(ui1_reg_info);

	_wzd_nw_leave_this_page();

    return WZDR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_nw_info_check_box_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_info_check_box_proc_fct(HANDLE_T   h_widget,
                                             UINT32     ui4_msg,
                                             VOID*      param1,
    										 VOID*		param2)
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_CURSOR_DOWN:
                {
                    RET_ON_ERR(_wzd_nw_footer_btn_focus());
                }
                    break;

                default:
                    break;
            }
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_searching_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_searching_icon_create(HANDLE_T  h_parent,
                                           HANDLE_T* ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_NW_SEARCHING_ICON_X,
                     WZD_NW_SEARCHING_ICON_Y,
                     WZD_NW_SEARCHING_ICON_W,
                     WZD_NW_SEARCHING_ICON_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                HT_WGL_WIDGET_ICON,
                                WGL_CONTENT_ICON_DEF,
                                WGL_BORDER_TIMG,
                                &t_rect,
                                NULL,
                                255,
                                (VOID *)0,
                                NULL,
                                ph_widget);
    RET_ON_ERR(i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* make icon invisible */
    i4_ret = c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_warning_icon_create
 *
 * Description:
 *          create warning icon.
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_warning_icon_create(HANDLE_T     h_parent,
                                       	 GL_RECT_T*   pt_rect,
                                       	 HANDLE_T*    ph_widget)
{
    INT32               i4_ret;
    WGL_IMG_INFO_T      t_img_info;
    WGL_INSET_T         t_inset;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)WGL_STL_GL_NO_IMG_UI,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_ICON_SET_CNT_INSET,
                            WGL_PACK (& t_inset),
                            NULL);

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_warning_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_warning_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_warning_icon;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    RET_ON_ERR(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility (*ph_widget, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

   return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_set_nav
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_set_nav(VOID)
{
    INT32   i4_ret;
    WGL_KEY_LINK_T  at_key_lnk[1];
    c_memset(&at_key_lnk, 0 , sizeof(WGL_KEY_LINK_T));

    at_key_lnk[0].ui4_key  = BTN_CURSOR_DOWN;
    at_key_lnk[0].h_widget = t_wzd_nw.t_protocol.t_protocol_policy.h_widget;
    i4_ret = c_wgl_set_navigation(t_wzd_nw.t_protocol.t_protocol_terms.h_widget, 1, at_key_lnk);
    RET_ON_ERR(i4_ret);

    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = t_wzd_nw.t_protocol.t_protocol_terms.h_widget;
    i4_ret = c_wgl_set_navigation(t_wzd_nw.t_protocol.t_protocol_policy.h_widget, 1, at_key_lnk);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_info_reg_set_nav
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_info_reg_set_nav(VOID)
{
    INT32   i4_ret;
    WGL_KEY_LINK_T  at_key_lnk[1];
	WGL_IMG_INFO_T	t_img_info;

    c_memset(&at_key_lnk, 0 , sizeof(WGL_KEY_LINK_T)*1);

    /*set first name nav*/
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL];
    i4_ret = c_wgl_set_navigation(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_FIRST_NAME], 1, at_key_lnk);
    RET_ON_ERR(i4_ret);

	/* Set icon before the editbox */
	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_FIRST_NAME],
                          WGL_CMD_BDR_TIMG_SET_ICON,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL) );
    RET_ON_ERR(i4_ret);

    /*set last name nav*/
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_FIRST_NAME];
    i4_ret = c_wgl_set_navigation(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_LAST_NAME], 1, at_key_lnk);
    RET_ON_ERR(i4_ret);

	/* Set icon before the editbox */
	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_LAST_NAME],
                          WGL_CMD_BDR_TIMG_SET_ICON,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    RET_ON_ERR(i4_ret);

    /*set phone num nav*/
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_LAST_NAME];
    i4_ret = c_wgl_set_navigation(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_PHONE_NUM], 1, at_key_lnk);
    RET_ON_ERR(i4_ret);

	/* Set icon before the editbox */
	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_PHONE_NUM],
                          WGL_CMD_BDR_TIMG_SET_ICON,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL) );
    RET_ON_ERR(i4_ret);

    /*set zip code nav*/
    at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_PHONE_NUM];
    i4_ret = c_wgl_set_navigation(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_ZIP_CODE], 1, at_key_lnk);
    RET_ON_ERR(i4_ret);

	/* Set icon before the editbox */
	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_ZIP_CODE],
                          WGL_CMD_BDR_TIMG_SET_ICON,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL) );
    RET_ON_ERR(i4_ret);

	at_key_lnk[0].ui4_key  = BTN_CURSOR_UP;
    at_key_lnk[0].h_widget = t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_ZIP_CODE];
    i4_ret = c_wgl_set_navigation(t_wzd_nw.t_info_reg.h_mail_accept_checkbox, 1, at_key_lnk);
    RET_ON_ERR(i4_ret);
    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_do_timer_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_protocol_do_timer_nfy (VOID*    pv_data,
                                           SIZE_T   z_data_size)
{
#ifdef APP_DYNAMIC_TOS_SUPPORT
    INT32           i4_ret;
#endif

	if (t_wzd_nw.t_protocol.ui1_circle_step == 0)
	{
		c_timer_stop(t_wzd_nw.t_protocol.h_timer);

		t_wzd_nw.b_is_busying = FALSE;

		c_wgl_show (t_wzd_nw.h_timer_icon, WGL_SW_HIDE_RECURSIVE);

	#ifdef APP_DYNAMIC_TOS_SUPPORT
        if (!a_tv_custom_is_3rd_rw_ready())
        {
            _wzd_nw_protocol_timer_start();
        }
        else if (FALSE == t_wzd_nw.t_protocol.b_is_file_opened)
        {
    		i4_ret = _wzd_nw_protocol_text_open();
            if (WZDR_OK != i4_ret)
        	{
        		_wzd_nw_protocol_timer_start();
        	}
            else
            {
                t_wzd_nw.t_protocol.b_is_file_opened = TRUE;
            }
        }
	#else
		_wzd_nw_protocol_text_open();
	#endif
	}
	else
	{

    	_wzd_nw_timer_icon_update(t_wzd_nw.h_timer_icon);

		t_wzd_nw.t_protocol.ui1_circle_step--;
	}

    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_timer_notify_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_protocol_timer_notify_fct(HANDLE_T  h_timer,
                                     		  VOID*     pv_tag)
{
    UINT16  ui2_status;
    UINT8  ui2_page_idx;
    //UINT8  ui2_state;

    a_cfg_get_wzd_status (& ui2_status);

    //ui2_state   = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui2_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);

    if (ui2_page_idx == WZD_PAGE_INDEX_NW_SETUP &&
		h_timer == t_wzd_nw.t_protocol.h_timer)
    {
        wzd_async_invoke(_wzd_nw_protocol_do_timer_nfy, NULL, (0), TRUE);
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_timer_start
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_timer_start (VOID)
{
	INT32   i4_ret;

	/* 5 sec = 10*500 */
	t_wzd_nw.t_protocol.ui1_circle_step = 10;

	/* circling initial */
	t_wzd_nw.b_is_busying = TRUE;
	t_wzd_nw.t_choice_connect.ui1_icon_step = WZD_NW_TIMER_ICON_STEP;

	/* show circle */
    i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_insert(t_wzd_nw.h_timer_icon,
						NULL_HANDLE,
						WGL_INSERT_TOPMOST,
						WGL_NO_AUTO_REPAINT);
	RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_timer_icon_update(t_wzd_nw.h_timer_icon);
    RET_ON_ERR(i4_ret);

	i4_ret = c_timer_start(t_wzd_nw.t_protocol.h_timer,
						500,
						X_TIMER_FLAG_REPEAT,
						_wzd_nw_protocol_timer_notify_fct,
						NULL);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_open
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_open(VOID)
{
    INT32   		i4_ret;

	if (0 == c_strlen(t_wzd_nw.t_protocol.s_file_path))
    {
        return WZDR_FAIL;
    }

	if (WZD_NW_PROTOCOL_SCAN_TERMS == t_wzd_nw.t_protocol.e_scan_text)
	{
		i4_ret = _wzd_nw_protocol_text_show_open(t_wzd_nw.t_protocol.s_file_path,
									&t_wzd_nw.t_protocol.t_protocol_terms.h_text_widget,
									&t_wzd_nw.t_protocol.t_protocol_terms.h_text);
		RET_ON_ERR(i4_ret);

		c_wgl_set_visibility(t_wzd_nw.t_protocol.t_protocol_terms.h_text_widget, WGL_SW_RECURSIVE);
		c_wgl_set_visibility(t_wzd_nw.t_protocol.t_protocol_terms.h_icon_frm, WGL_SW_RECURSIVE);

		i4_ret = _wzd_nw_protocol_text_show_start_scan(&t_wzd_nw.t_protocol.t_protocol_terms.h_text);
		RET_ON_ERR(i4_ret);
	}
	else if (WZD_NW_PROTOCOL_SCAN_POLICY == t_wzd_nw.t_protocol.e_scan_text)
	{
		i4_ret = _wzd_nw_protocol_text_show_open(t_wzd_nw.t_protocol.s_file_path,
									&t_wzd_nw.t_protocol.t_protocol_policy.h_text_widget,
									&t_wzd_nw.t_protocol.t_protocol_policy.h_text);
		RET_ON_ERR(i4_ret);

		c_wgl_set_visibility(t_wzd_nw.t_protocol.t_protocol_policy.h_text_widget, WGL_SW_RECURSIVE);
		c_wgl_set_visibility(t_wzd_nw.t_protocol.t_protocol_policy.h_icon_frm, WGL_SW_RECURSIVE);

		i4_ret = _wzd_nw_protocol_text_show_start_scan(&t_wzd_nw.t_protocol.t_protocol_policy.h_text);
		RET_ON_ERR(i4_ret);
	}
	else
	{
		return WZDR_FAIL;
	}

	i4_ret = c_wgl_repaint(t_wzd_nw.t_protocol.h_protocol_frame, NULL, TRUE);
	RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_text_frame_show
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_text_frame_show(VOID)
{
	INT32   		i4_ret;

#ifdef APP_DYNAMIC_TOS_SUPPORT
    TOS_TYPE_T      e_tos_type = TOS_TYPE_LAST_VALID_ITEM;
    CHAR            s_buf_path[255] = {0};

    t_wzd_nw.t_protocol.b_is_file_opened = FALSE;
#endif

	c_memset(t_wzd_nw.t_protocol.s_file_path, 0, sizeof(CHAR)*(128));

	i4_ret = c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame, WGL_SW_HIDE_RECURSIVE);
	RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame, WGL_SW_NORMAL);
	RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_repaint(t_wzd_nw.t_protocol.h_protocol_frame, NULL, TRUE);
	RET_ON_ERR(i4_ret);

#ifdef APP_DYNAMIC_TOS_SUPPORT
    /* update title */
    if (WZD_NW_PROTOCOL_SCAN_TERMS == t_wzd_nw.t_protocol.e_scan_text)
    {
        RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_TITLE_TOS), NULL_HANDLE));
    }
    else if (WZD_NW_PROTOCOL_SCAN_POLICY == t_wzd_nw.t_protocol.e_scan_text)
    {
        RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_TITLE_POLICY), NULL_HANDLE));
    }
    else
    {
        /* do nothing */
    }

    /* start to download and open tos file */
    e_tos_type = _wzd_tos_get_type ();

    if (!a_tv_custom_is_3rd_rw_ready())
    {
        DBG_INFO(("[WZD][TOS] 3rd_rw partition is now ready. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));
        c_strcpy(t_wzd_nw.t_protocol.s_file_path, "");
    }
    else if (a_tos_is_file_exist(e_tos_type))
    {
        DBG_INFO(("[WZD][TOS] open file directly. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

        a_tos_get_file_path(e_tos_type, s_buf_path);
        c_strncpy(t_wzd_nw.t_protocol.s_file_path, s_buf_path, 127);
    }
    else
    {
        DBG_INFO(("[WZD][TOS] start to download. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

        a_tos_download_util_file(e_tos_type);
        c_strcpy(t_wzd_nw.t_protocol.s_file_path, "");
    }
#else
	if (WZD_NW_PROTOCOL_SCAN_TERMS == t_wzd_nw.t_protocol.e_scan_text)
	{
		/* copy terms text path */
		if (MLM_WZD_LANG_FRE == t_wzd_nw.ui2_lang_id)
		{
			c_strcpy(t_wzd_nw.t_protocol.s_file_path, "/3rd/yahoo_tos_in_fre.txt");
		}
		else if (MLM_WZD_LANG_SPA == t_wzd_nw.ui2_lang_id)
		{
			c_strcpy(t_wzd_nw.t_protocol.s_file_path, "/3rd/yahoo_tos_in_spa.txt");
		}
		else
		{
			c_strcpy(t_wzd_nw.t_protocol.s_file_path, "/3rd/yahoo_tos_in_eng.txt");
		}

		/* update title */
		RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_TITLE_TOS), NULL_HANDLE));
	}
	else if (WZD_NW_PROTOCOL_SCAN_POLICY == t_wzd_nw.t_protocol.e_scan_text)
	{
		/* copy privacy text path */
		if (MLM_WZD_LANG_FRE == t_wzd_nw.ui2_lang_id)
		{
			c_strcpy(t_wzd_nw.t_protocol.s_file_path, "/3rd/yahoo_privacy_policy_in_fre.txt");
		}
		else if (MLM_WZD_LANG_SPA == t_wzd_nw.ui2_lang_id)
		{
			c_strcpy(t_wzd_nw.t_protocol.s_file_path, "/3rd/yahoo_privacy_policy_in_spa.txt");
		}
		else
		{
			c_strcpy(t_wzd_nw.t_protocol.s_file_path, "/3rd/yahoo_privacy_policy_in_eng.txt");
		}

		/* update title */
		RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_TITLE_POLICY), NULL_HANDLE));
	}
	else
	{
		/* do nothing */
	}
#endif

	/* repaint title */
	RET_ON_ERR (wzd_view_title_txt_repaint());

	/* update footer */
	RET_ON_ERR (wzd_view_footer_set_btn_num(1));
	RET_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, WZD_TEXT(MLM_WZD_KEY_NETWORK_TOS_BACK)));
	RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
	RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, FALSE));
	RET_ON_ERR (wzd_view_footer_update_btn_navigation());
	RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE));
	RET_ON_ERR (wzd_view_footer_frm_repaint());

	t_wzd_nw.t_protocol.ui4_pro_cur_page = 1;

	i4_ret = _wzd_nw_protocol_text_open();

#ifdef APP_DYNAMIC_TOS_SUPPORT
    if (WZDR_OK != i4_ret)
    {
        _wzd_nw_protocol_timer_start();
    }
    else
    {
        t_wzd_nw.t_protocol.b_is_file_opened = TRUE;
    }
#else
    if (WZDR_OK != i4_ret)
    {
        _wzd_nw_protocol_timer_start();
    }
#endif

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_protocol_page_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_protocol_page_create(HANDLE_T h_parent)
{
    INT32               i4_ret;
	GL_RECT_T           t_rect;

    i4_ret = _wzd_nw_frm_create (h_parent,
                                 WZD_NW_FRAME_X,
                                 WZD_NW_FRAME_Y,
                                 WZD_NW_FRAME_W,
                                 WZD_NW_FRAME_H,
                                 NULL,
                                 &t_wzd_nw.t_protocol.h_protocol_frame);
    RET_ON_ERR(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

#ifdef APP_DYNAMIC_TOS_SUPPORT
    /* Error msg text */
    _wzd_nw_protocol_error_msg_create(t_wzd_nw.t_protocol.h_protocol_frame);
#endif

	/* Terms of service */
    SET_RECT_BY_SIZE(&t_rect,
                     WZD_TERMS_BTN_X,
                     WZD_TERMS_BTN_Y,
                     WZD_TERMS_BTN_W,
                     WZD_TERMS_BTN_H);

	i4_ret = _wzd_nw_btn_widget_create(
						t_wzd_nw.t_protocol.h_protocol_frame,
						WZD_TEXT(MLM_WZD_KEY_NW_SETUP_BTN_TOS),
						&t_rect,
						_wzd_nw_btn_widget_proc_fct,
						&t_wzd_nw.t_protocol.t_protocol_terms.h_widget
						);
	RET_ON_ERR (i4_ret);

    i4_ret = _wzd_nw_protocol_text_create(
                         t_wzd_nw.t_protocol.h_protocol_frame,
                         WZD_NW_TXT_CNT_X,
                         WZD_NW_TXT_CNT_Y,
                         WZD_NW_TXT_CNT_W,
                         WZD_NW_TXT_CNT_H,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &t_wzd_nw.t_protocol.t_protocol_terms.h_text_widget);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_frm_create (t_wzd_nw.t_protocol.h_protocol_frame,
                                 WZD_NW_TEXT_ICON_FRM_X,
                                 WZD_NW_TEXT_ICON_FRM_Y,
                                 WZD_NW_TEXT_ICON_FRM_W,
                                 WZD_NW_TEXT_ICON_FRM_H,
                                 NULL,
                                 &t_wzd_nw.t_protocol.t_protocol_terms.h_icon_frm);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_protocol_text_icon_create(
                         t_wzd_nw.t_protocol.t_protocol_terms.h_icon_frm,
                         0,
                         0,
                         WZD_NW_TEXT_ICON_W,
                         WZD_NW_TEXT_ICON_H,
                         h_g_wzd_tos_scroll_up,
                         h_g_wzd_tos_scroll_up_highlight,
                         &t_wzd_nw.t_protocol.t_protocol_terms.h_icon_up);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_protocol_text_icon_create(
                         t_wzd_nw.t_protocol.t_protocol_terms.h_icon_frm,
                         0,
                         WZD_NW_TEXT_ICON_H - 34 * WZD_UI_RATIO,
                         WZD_NW_TEXT_ICON_W,
                         WZD_NW_TEXT_ICON_H,
                         h_g_wzd_tos_scroll_down,
                         h_g_wzd_tos_scroll_down_highlight,
                         &t_wzd_nw.t_protocol.t_protocol_terms.h_icon_down);
    RET_ON_ERR(i4_ret);


	/* Privacy Policy */
	SET_RECT_BY_SIZE(&t_rect,
                     WZD_POLICY_BTN_X,
                     WZD_POLICY_BTN_Y,
                     WZD_POLICY_BTN_W,
                     WZD_POLICY_BTN_H);

	i4_ret = _wzd_nw_btn_widget_create(
						t_wzd_nw.t_protocol.h_protocol_frame,
						WZD_TEXT(MLM_WZD_KEY_NW_SETUP_BTN_POLICY),
						&t_rect,
						_wzd_nw_btn_widget_proc_fct,
						&t_wzd_nw.t_protocol.t_protocol_policy.h_widget
						);
	RET_ON_ERR (i4_ret);

    i4_ret = _wzd_nw_protocol_text_create(
                         t_wzd_nw.t_protocol.h_protocol_frame,
                         WZD_NW_TXT_CNT_X,
                         WZD_NW_TXT_CNT_Y,
                         WZD_NW_TXT_CNT_W,
                         WZD_NW_TXT_CNT_H,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &t_wzd_nw.t_protocol.t_protocol_policy.h_text_widget);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_frm_create (t_wzd_nw.t_protocol.h_protocol_frame,
                                 WZD_NW_TEXT_ICON_FRM_X,
                                 WZD_NW_TEXT_ICON_FRM_Y,
                                 WZD_NW_TEXT_ICON_FRM_W,
                                 WZD_NW_TEXT_ICON_FRM_H,
                                 NULL,
                                 &t_wzd_nw.t_protocol.t_protocol_policy.h_icon_frm);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_protocol_text_icon_create(
                         t_wzd_nw.t_protocol.t_protocol_policy.h_icon_frm,
                         0,
                         0,
                         WZD_NW_TEXT_ICON_W,
                         WZD_NW_TEXT_ICON_H,
                         h_g_wzd_tos_scroll_up,
                         h_g_wzd_tos_scroll_up_highlight,
                         &t_wzd_nw.t_protocol.t_protocol_policy.h_icon_up);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_protocol_text_icon_create(
                         t_wzd_nw.t_protocol.t_protocol_policy.h_icon_frm,
                         0,
                         WZD_NW_TEXT_ICON_H - 34 * WZD_UI_RATIO,
                         WZD_NW_TEXT_ICON_W,
                         WZD_NW_TEXT_ICON_H,
                         h_g_wzd_tos_scroll_down,
                         h_g_wzd_tos_scroll_down_highlight,
                         &t_wzd_nw.t_protocol.t_protocol_policy.h_icon_down);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_protocol_set_nav();
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame,WGL_SW_HIDE_RECURSIVE);
    RET_ON_ERR(i4_ret);

	i4_ret = c_timer_create(&t_wzd_nw.t_protocol.h_timer);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_none_conn_page_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_none_conn_page_create(HANDLE_T h_parent)
{
    INT32     			i4_ret;
    GL_RECT_T 			t_rect;
    WGL_COLOR_INFO_T  	t_color_info_fg;

    i4_ret = _wzd_nw_frm_create(h_parent,
                         WZD_NW_FRAME_X,
                         WZD_NW_FRAME_Y,
                         WZD_NW_FRAME_W,
                         WZD_NW_FRAME_H,
                         NULL,
                         &t_wzd_nw.t_none_conn.h_none_conn_frame);
    RET_ON_ERR(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
		                 WZD_NW_NONE_CONN_WARNING_ICON_X,
		                 WZD_NW_NONE_CONN_WARNING_ICON_Y,
		                 WZD_NW_NONE_CONN_WARNING_ICON_W,
		                 WZD_NW_NONE_CONN_WARNING_ICON_H);

    i4_ret = _wzd_nw_warning_icon_create(
                        t_wzd_nw.t_none_conn.h_none_conn_frame,
                        &t_rect,
                        &t_wzd_nw.t_none_conn.h_warning_icon);
    RET_ON_ERR(i4_ret);

	/* create title */
    SET_RECT_BY_SIZE(&t_rect,
		                 WZD_NW_NONE_CONN_TITLE_X,
		                 WZD_NW_NONE_CONN_TITLE_Y,
		                 WZD_NW_NONE_CONN_TITLE_W,
		                 WZD_NW_NONE_CONN_TITLE_H);

	t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (&t_color_info_fg.u_color_data.t_standard.t_enable,    &t_g_wzd_color_network_txt_hlt);
    COLOR_COPY (&t_color_info_fg.u_color_data.t_standard.t_disable,   &t_g_wzd_color_network_txt_hlt);
    COLOR_COPY (&t_color_info_fg.u_color_data.t_standard.t_highlight, &t_g_wzd_color_network_txt_hlt);

    i4_ret = _wzd_nw_title_text_create(
                         t_wzd_nw.t_none_conn.h_none_conn_frame,
                         &t_rect,
                         &t_color_info_fg,
                         &t_wzd_nw.t_none_conn.t_title.h_widget);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_do_cmd (t_wzd_nw.t_none_conn.t_title.h_widget,
						WGL_CMD_TEXT_SET_TEXT,
						WGL_PACK (WZD_TEXT(MLM_WZD_KEY_NW_SETUP_NO_NETWORK_FOUND)),
						WGL_PACK ((UINT16)0xFFFF));
	RET_ON_ERR(i4_ret);

	/* create desc text */
    SET_RECT_BY_SIZE(&t_rect,
		                 WZD_NW_NONE_CONN_DESC_X,
                         WZD_NW_NONE_CONN_DESC_Y,
                         WZD_NW_NONE_CONN_DESC_W,
                         WZD_NW_NONE_CONN_DESC_H);

	t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (&t_color_info_fg.u_color_data.t_standard.t_enable,    &t_g_wzd_color_network_txt_nor);
    COLOR_COPY (&t_color_info_fg.u_color_data.t_standard.t_disable,   &t_g_wzd_color_network_txt_nor);
    COLOR_COPY (&t_color_info_fg.u_color_data.t_standard.t_highlight, &t_g_wzd_color_network_txt_nor);

    i4_ret = _wzd_nw_title_text_create(
                         t_wzd_nw.t_none_conn.h_none_conn_frame,
                         &t_rect,
                         &t_color_info_fg,
                         &t_wzd_nw.t_none_conn.t_desc_txt.h_widget);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_do_cmd (t_wzd_nw.t_none_conn.t_desc_txt.h_widget,
						WGL_CMD_TEXT_SET_TEXT,
						WGL_PACK (WZD_TEXT(MLM_WZD_KEY_EMPTY)),
						WGL_PACK ((UINT16)0xFFFF));
	RET_ON_ERR(i4_ret);


    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_none_conn.h_none_conn_frame, WGL_SW_HIDE_RECURSIVE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_float_prompt_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_float_prompt_create(HANDLE_T h_parent)
{
    INT32     			i4_ret;
	WGL_FONT_INFO_T		t_fnt_info;

	i4_ret = _wzd_nw_text_create(
                         h_parent,
                         WZD_NW_PWD_EB_X + WZD_NW_PWD_EB_LEFT_INSET + (40 * WZD_UI_RATIO),
                         WZD_NW_PWD_EB_Y + (4 * WZD_UI_RATIO),
                         WZD_NW_PWD_EB_W - (100 * WZD_UI_RATIO),
                         WZD_NW_PWD_EB_H,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &t_wzd_nw.h_prompt_text
                         );
    RET_ON_ERR(i4_ret);

	/* Set Font */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

#if 0
	t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size = WZD_EB_TXT_FNT_SIZE;
#else
	t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
#endif

    i4_ret = c_wgl_do_cmd (t_wzd_nw.h_prompt_text,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.h_prompt_text, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_float_prompt_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_float_prompt_show(VOID)
{
    INT32     			i4_ret;

	/* Set to topmost */
    i4_ret = c_wgl_insert (t_wzd_nw.h_prompt_text,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.h_prompt_text, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_float_prompt_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_float_prompt_hide(VOID)
{
    return c_wgl_set_visibility (t_wzd_nw.h_prompt_text, WGL_SW_HIDE);;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_float_prompt_repaint
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_float_prompt_repaint(VOID)
{
    return c_wgl_repaint (t_wzd_nw.h_prompt_text, NULL, TRUE);;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_float_prompt_set_text
 *
 * Description: This API sets text to the description text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_float_prompt_set_text(UTF16_T* pw2s_text)
{
    return  c_wgl_do_cmd (t_wzd_nw.h_prompt_text,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_mac_addr_create
 *
 * Description:
 *
 * Inputs:	-
 *
 * Outputs: -
 *
 * Returns: 0					   Successful.
 *			Any other values	   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_mac_addr_create(HANDLE_T h_parent)
{
	INT32				i4_ret;
	WGL_FONT_INFO_T 	t_fnt_info;

	i4_ret = _wzd_nw_text_create(
						 h_parent,
						 WZD_NW_MAC_ADDR_X,
						 WZD_NW_MAC_ADDR_Y,
						 WZD_NW_MAC_ADDR_W,
						 WZD_NW_MAC_ADDR_H,
						 NULL_HANDLE,
						 NULL_HANDLE,
						 &t_wzd_nw.h_mac_addr
						 );
	RET_ON_ERR(i4_ret);

	/* set alignment */
    i4_ret = c_wgl_do_cmd(t_wzd_nw.h_mac_addr,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK (WGL_AS_RIGHT_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

	/* Set Font */
	c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
	c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());
	t_fnt_info.e_font_size	= FE_FNT_SIZE_CUSTOM;
	t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	t_fnt_info.e_font_cmap	= FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size = 15;

	i4_ret = c_wgl_do_cmd (t_wzd_nw.h_mac_addr,
						   WGL_CMD_GL_SET_FONT,
						   WGL_PACK(&t_fnt_info),
						   NULL);
	RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.h_mac_addr, WGL_SW_HIDE);
	RET_ON_ERR(i4_ret);

	return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_mac_addr_update
 *
 * Description: update wlan mac address text.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_mac_addr_update(VOID)
{
	INT32				i4_ret;
	CHAR            	s_mac_str[64];
    UTF16_T         	w2s_tmp_str[128];
    UTF16_T         	w2s_str[128];

	c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);

    a_nw_get_mac_addr_string(NI_WIRELESS_0, s_mac_str);
    c_uc_ps_to_w2s(s_mac_str, w2s_tmp_str, c_strlen(s_mac_str));

	c_uc_w2s_strncat(w2s_str, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_MAC_ADDRESS), c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_MAC_ADDRESS)));
    c_uc_w2s_strncat(w2s_str, w2s_tmp_str, c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd (t_wzd_nw.h_mac_addr,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (w2s_str),
                      WGL_PACK (c_uc_w2s_strlen (w2s_str)));
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.h_mac_addr, WGL_SW_NORMAL);
	RET_ON_ERR(i4_ret);

	return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_update_footer_btn_with_eb_content
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_update_footer_btn_with_eb_content(VOID)
{
	INT32               i4_ret = WDKR_OK;
	UTF16_T             w2s_text[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
    VKB_CMD_TYPE_T      e_vkb_type = VKB_CMD_GET_STYLE_MASK;
    HANDLE_T            h_focus = NULL_HANDLE;

    /* store previous focus handle */
	c_wgl_get_focus(&h_focus);

    if (h_focus == t_wzd_nw.t_eb_pwd.h_eb ||
        h_focus == t_wzd_nw.t_eb_ssid.h_eb)
    {
        e_vkb_type = VKB_CMD_GET_EB_CONTENT;
    }
    else
    {
        e_vkb_type = VKB_CMD_GET_TEXT;
    }

	if (WZD_NW_VKB_PWD_INPUT == t_wzd_nw.t_vkb.e_vkb_style)
	{
		i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_pwd,
	                          e_vkb_type,
	                          (VOID*) w2s_text,
	                          (VOID*) (UINT32) WZD_NW_EB_TXT_MAX_LEN);
	    RET_ON_ERR(i4_ret);
	}
	else
	{
		i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_ssid,
	                          e_vkb_type,
	                          (VOID*) w2s_text,
	                          (VOID*) (UINT32) WZD_NW_EB_TXT_MAX_LEN);
		RET_ON_ERR(i4_ret);
	}

	if (c_uc_w2s_strlen(w2s_text) == 0)
	{
		DBG_LOG_PRINT(("[WZD][EB] --- EMPTY. %s %d \n", __FUNCTION__,__LINE__));

		/* show float prompt */
		if (t_wzd_nw.b_need_show_prompt_text)
		{
			RET_ON_ERR (_wzd_nw_float_prompt_show());
			RET_ON_ERR (_wzd_nw_float_prompt_repaint());
		}

		if (TRUE == wzd_view_footer_get_enable(WZD_FOOTER_BTN_01))
		{
			/* update footer btn and navi */
			RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
		    RET_ON_ERR (wzd_view_footer_update_btn_navigation());
			RET_ON_ERR (wzd_view_footer_frm_repaint());
		}
	}
	else
	{
		DBG_LOG_PRINT(("[WZD][EB] --- NO EMPTY. %s %d \n", __FUNCTION__,__LINE__));

		/* hide float prompt */
		if (t_wzd_nw.b_need_show_prompt_text)
		{
			t_wzd_nw.b_need_show_prompt_text = FALSE;
			RET_ON_ERR (_wzd_nw_float_prompt_hide());
			RET_ON_ERR (_wzd_nw_float_prompt_repaint());
		}

		if (FALSE == wzd_view_footer_get_enable(WZD_FOOTER_BTN_01))
		{
			e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;

			/* update footer btn and navi */
			RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
		    RET_ON_ERR (wzd_view_footer_update_btn_navigation());
			RET_ON_ERR (wzd_view_footer_frm_repaint());
		}
	}

	return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_eb_clear_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_eb_clear_icon_create (HANDLE_T   h_parent,
                                           HANDLE_T*  ph_widget)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;

	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
	                 WZD_NW_PWD_EB_X + WZD_NW_PWD_EB_W - 100 * WZD_UI_RATIO,
	                 WZD_NW_PWD_EB_Y,
	                 80 * WZD_UI_RATIO,
	                 WZD_NW_PWD_EB_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wdk_vkb_eb_clear;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wdk_vkb_eb_clear_hlt;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wdk_vkb_eb_clear;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    RET_ON_ERR(c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_eb_focus_icon_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_eb_focus_icon_create (HANDLE_T   h_parent,
                                           HANDLE_T*  ph_widget)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;

	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
	                 WZD_NW_PWD_EB_X - WZD_NW_EDIT_BOX_HL_ICON_W - 12 * WZD_UI_RATIO,
	                 WZD_NW_PWD_EB_Y,
	                 WZD_NW_EDIT_BOX_HL_ICON_W,
	                 WZD_NW_PWD_EB_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_text_focus;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_text_focus;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_text_focus;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    RET_ON_ERR(c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_eb_frm_nfy
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
static INT32 _wzd_nw_eb_frm_nfy(HANDLE_T    h_widget,
  	                            UINT32      ui4_msg,
  	                            VOID*       pv_param1,
  	                            VOID*       pv_param2)
{
	BOOL 					b_visible = FALSE;
    HANDLE_T				h_cb_widget;
    WGL_NOTIFY_DATA_T*		pt_wgl_nfy_data;

    h_cb_widget     = (HANDLE_T) pv_param1;
    pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

	if (t_wzd_nw.t_eb_ssid.h_eb == h_cb_widget ||
		t_wzd_nw.t_eb_pwd.h_eb == h_cb_widget)
	{
		RET_ON_ERR (c_wgl_get_visibility(h_cb_widget, &b_visible));
		if (!b_visible)
		{
			return WZDR_OK;
		}
	}

    if (ui4_msg == WGL_MSG_NOTIFY)
    {
        if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_EB_CHANGED) /* Password edit gets input. */
        {
        	DBG_LOG_PRINT(("[WZD][EB] --- CONTENT CHANGED. %s %d \n", __FUNCTION__,__LINE__));
			RET_ON_ERR (_wzd_nw_update_footer_btn_with_eb_content());
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_pwd_eb_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_pwd_eb_create (HANDLE_T h_parent)
{
    INT32               i4_ret = 0;
	UINT32              ui4_style;
    GL_RECT_T           t_rect;
	WGL_INSET_T         t_inset;
	VKB_EB_ATTACH_DATE 	t_attach_data;
	WGL_FONT_INFO_T		t_fnt_info;
	WGL_IMG_INFO_T      t_img_info;

	ui4_style = WGL_STL_EB_MAX_CHAR_256 | WGL_STL_EB_PASSWORD_ESC_LAST | WGL_STL_EB_SHOW_LAST_CHARACTERS;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

	i4_ret = _wzd_nw_frm_create(
						h_parent,
						WZD_NW_FRAME_X,
						WZD_NW_FRAME_Y,
						WZD_NW_FRAME_W,
						WZD_NW_FRAME_H,
						_wzd_nw_eb_frm_nfy,
						&t_wzd_nw.t_eb_pwd.h_eb_frm);
    RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_eb_focus_icon_create(t_wzd_nw.t_eb_pwd.h_eb_frm, &t_wzd_nw.t_eb_pwd.h_eb_focus);
	RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_eb_clear_icon_create(t_wzd_nw.t_eb_pwd.h_eb_frm, &t_wzd_nw.t_eb_pwd.h_eb_clr);
	RET_ON_ERR(i4_ret);

    SET_RECT_BY_SIZE (&t_rect,
                      WZD_NW_PWD_EB_X,
                      WZD_NW_PWD_EB_Y,
                      WZD_NW_PWD_EB_W,
                      WZD_NW_PWD_EB_H);

    i4_ret = _wzd_nw_vkb_edit_box_create(
                        t_wzd_nw.t_eb_pwd.h_eb_frm,
                        &t_rect,
                        WZD_NW_PWD_EB_LEFT_INSET,
                        WZD_NW_PWD_EB_RIGHT_INSET,
                        ui4_style,
                        NULL,
                        &t_wzd_nw.t_eb_pwd.h_eb);
    RET_ON_ERR(i4_ret);

    /* Set Cnt Insets */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left = 22 * WZD_UI_RATIO_W;
	t_inset.i4_right = 70 * WZD_UI_RATIO_W;
    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_eb_pwd.h_eb,
                          WGL_CMD_EB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    RET_ON_ERR(i4_ret);

	/* Set Fixed Font SIZE */
    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

#if 0
	t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	t_fnt_info.ui1_custom_size = WZD_EB_TXT_FNT_SIZE;
#else
	t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
#endif
	t_fnt_info.i2_width     = WZD_EB_TXT_FNT_WIDTH;

    i4_ret = c_wgl_do_cmd (t_wzd_nw.t_eb_pwd.h_eb,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    RET_ON_ERR(i4_ret);

	/* Set the cursor focus status */
    i4_ret = c_wgl_do_cmd (t_wzd_nw.t_eb_pwd.h_eb,
                           WGL_CMD_EB_SET_FOCUS_STATUS,
                           WGL_PACK (TRUE),
                           NULL);
    RET_ON_ERR(i4_ret);

	/* Set the cursor image */
	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_text_box_cursor;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_text_box_cursor;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_text_box_cursor;

	i4_ret = c_wgl_do_cmd (t_wzd_nw.t_eb_pwd.h_eb,
						   WGL_CMD_EB_SET_CURSOR_IMG,
						   WGL_PACK(WGL_IMG_BK),
						   WGL_PACK(&t_img_info));
	RET_ON_ERR(i4_ret);

	/* set editbox string length limit */
    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_eb_pwd.h_eb,
                           WGL_CMD_EB_SET_INPUT_LIMIT,
                           WGL_PACK((UINT16)(WZD_NW_KEY_MAX_LEN+1)),
                           NULL);
    RET_ON_ERR(i4_ret);

	/* attach pwd editbox to vkb */
	c_memset(&t_attach_data, 0 , sizeof(VKB_EB_ATTACH_DATE));

	t_attach_data.h_edit_box = t_wzd_nw.t_eb_pwd.h_eb;
	t_attach_data.h_eb_clr = t_wzd_nw.t_eb_pwd.h_eb_clr;
	t_attach_data.b_need_eb_clr = TRUE;

	i4_ret = a_vkb_attach_eb (t_wzd_nw.t_vkb.h_vkb_pwd, &t_attach_data);
	RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_eb_pwd.h_eb_frm, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_ssid_eb_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_ssid_eb_create (HANDLE_T h_parent)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
	VKB_EB_ATTACH_DATE 	t_attach_data;
    #ifdef APP_PORTING
	WGL_IMG_INFO_T      t_img_info;
    #endif
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));

	i4_ret = _wzd_nw_frm_create(
						h_parent,
						WZD_NW_FRAME_X,
						WZD_NW_FRAME_Y,
						WZD_NW_FRAME_W,
						WZD_NW_FRAME_H,
						_wzd_nw_eb_frm_nfy,
						&t_wzd_nw.t_eb_ssid.h_eb_frm);
    RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_eb_focus_icon_create(t_wzd_nw.t_eb_ssid.h_eb_frm, &t_wzd_nw.t_eb_ssid.h_eb_focus);
	RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_eb_clear_icon_create(t_wzd_nw.t_eb_ssid.h_eb_frm, &t_wzd_nw.t_eb_ssid.h_eb_clr);
	RET_ON_ERR(i4_ret);

    SET_RECT_BY_SIZE (&t_rect,
                      WZD_NW_SSID_EB_X,
                      WZD_NW_SSID_EB_Y,
                      WZD_NW_SSID_EB_W,
                      WZD_NW_SSID_EB_H);

    i4_ret = _wzd_nw_vkb_edit_box_create(
                        t_wzd_nw.t_eb_ssid.h_eb_frm,
                        &t_rect,
                        WZD_NW_SSID_EB_LEFT_INSET,
                        WZD_NW_SSID_EB_RIGHT_INSET,
                        WGL_STL_EB_MAX_CHAR_64,
                        NULL,
                        &t_wzd_nw.t_eb_ssid.h_eb);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_eb_ssid.h_eb,
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(WZD_NW_SSID_MAX_LEN+1)),
                          NULL);
    RET_ON_ERR(i4_ret);
#ifdef APP_PORTING
	/* Set the cursor image */
	c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_text_box_cursor;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_text_box_cursor;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_text_box_cursor;

	i4_ret = c_wgl_do_cmd (t_wzd_nw.t_eb_ssid.h_eb,
						   WGL_CMD_EB_SET_CURSOR_IMG,
						   WGL_PACK(WGL_IMG_BK),
						   WGL_PACK(&t_img_info));
	RET_ON_ERR(i4_ret);
#endif
	/* attach ssid editbox to vkb */
	c_memset(&t_attach_data, 0 , sizeof(VKB_EB_ATTACH_DATE));

	t_attach_data.h_edit_box = t_wzd_nw.t_eb_ssid.h_eb;
	t_attach_data.h_eb_clr = t_wzd_nw.t_eb_ssid.h_eb_clr;
	t_attach_data.b_need_eb_clr = TRUE;

	i4_ret = a_vkb_attach_eb (t_wzd_nw.t_vkb.h_vkb_ssid, &t_attach_data);
	RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_eb_ssid.h_eb_frm, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_float_prompt_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_float_prompt_create(HANDLE_T h_parent)
{
    INT32     			i4_ret;
	WGL_FONT_INFO_T		t_fnt_info;
	WGL_COLOR_INFO_T	t_clr_info;

	for(UINT8 ui1_loop=0;ui1_loop<WZD_NW_REG_INFO_LAST_ENTRY;ui1_loop++)
	{
		i4_ret = _wzd_nw_text_create(
	                         h_parent,
	                         WZD_NW_INFO_REG_EDIT_BOX_X + WZD_NW_INFO_REG_EB_LEFT_INSET + (15 * WZD_UI_RATIO),
	                         WZD_NW_EMAIL_EB_Y + (ui1_loop * WZD_NW_EMAIL_EB_GAP)- (2 * WZD_UI_RATIO),
	                         WZD_NW_INFO_REG_EDIT_BOX_W - WZD_NW_INFO_REG_EB_RIGHT_INSET,
	                         WZD_NW_INFO_REG_EDIT_BOX_H,
	                         NULL_HANDLE,
	                         NULL_HANDLE,
	                         &t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_loop]
	                         );
	    RET_ON_ERR(i4_ret);

		/* Set Font */
	    c_memset (&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
	    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());
	    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

	    i4_ret = c_wgl_do_cmd (t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_loop],
	                           WGL_CMD_GL_SET_FONT,
	                           WGL_PACK(&t_fnt_info),
	                           NULL);
	    RET_ON_ERR(i4_ret);

	    /* Set txt color */
	    c_memset (&t_clr_info, 0, sizeof(WGL_COLOR_INFO_T));
	    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
	    t_clr_info.u_color_data.t_standard.t_enable     = t_g_wzd_color_seti_lst_col_dis_txt;
	    t_clr_info.u_color_data.t_standard.t_highlight  = t_g_wzd_color_seti_lst_col_hlt_txt;
	    t_clr_info.u_color_data.t_standard.t_disable    = t_g_wzd_color_seti_lst_col_dis_txt;
	    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_loop],
	                          WGL_CMD_GL_SET_COLOR,
	                          WGL_PACK(WGL_CLR_TEXT),
	                          WGL_PACK(&t_clr_info ));

		i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_loop], WGL_SW_HIDE);
	    RET_ON_ERR(i4_ret);
	}
    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_float_prompt_show_current_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_float_prompt_show_current_item(UINT8 ui1_item_idx)
{
    INT32     			i4_ret;

	/* Set to topmost */
    i4_ret = c_wgl_insert (t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_item_idx],
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_item_idx], WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_float_prompt_show_all_item
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_float_prompt_show_all_item(VOID)
{
    INT32     			i4_ret;

	/* Set to topmost */
	for(UINT8 ui1_loop=0;ui1_loop<WZD_NW_REG_INFO_LAST_ENTRY;ui1_loop++)
	{
	    i4_ret = c_wgl_insert (t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_loop],
	                           NULL_HANDLE,
	                           WGL_INSERT_TOPMOST,
	                           WGL_NO_AUTO_REPAINT);
	    RET_ON_ERR(i4_ret);

		i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[WZD_NW_REG_INFO_MAIL+ui1_loop], WGL_SW_NORMAL);
	    RET_ON_ERR(i4_ret);
	}
    return WZDR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_float_prompt_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_float_prompt_hide(UINT8 ui1_item_idx)
{
    return c_wgl_set_visibility (t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_item_idx], WGL_SW_HIDE);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_float_prompt_set_text
 *
 * Description: This API sets text to the description text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_float_prompt_set_text(void)
{
	for(UINT8 ui1_loop=0;ui1_loop<WZD_NW_REG_INFO_LAST_ENTRY;ui1_loop++)
	{

	    c_wgl_do_cmd (t_wzd_nw.t_info_reg.h_reg_eb_prompt_text[ui1_loop],
	                          WGL_CMD_TEXT_SET_TEXT,
	                          WGL_PACK (MLM_WZD_TEXT(t_wzd_nw.ui2_lang_id, MLM_WZD_KEY_NETWORK_REG_INFO_EMAIL+ ui1_loop)),
	                          WGL_PACK (c_uc_w2s_strlen (MLM_WZD_TEXT(t_wzd_nw.ui2_lang_id, MLM_WZD_KEY_NETWORK_REG_INFO_EMAIL+ ui1_loop))));
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_update_reg_info_eb_content
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_reg_info_update_eb_content(UINT8 ui1_item_idx)
{
	INT32               i4_ret = WDKR_OK;
	UTF16_T             w2s_text[WZD_NW_EB_TXT_MAX_LEN] = {0};

	i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[ui1_item_idx],
                          WGL_CMD_EB_GET_TEXT,
                          (VOID*) w2s_text,
                          (VOID*) (UINT32) WZD_NW_EB_TXT_MAX_LEN);
	RET_ON_ERR(i4_ret);

	if (c_uc_w2s_strlen(w2s_text) == 0)
	{
		/* show float prompt */
		RET_ON_ERR (_wzd_nw_reg_info_float_prompt_show_current_item(ui1_item_idx));
	}
	else
	{
		/* hide float prompt */
		RET_ON_ERR (_wzd_nw_reg_info_float_prompt_hide(ui1_item_idx));
	}

	return WDKR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_reg_info_eb_frm_nfy
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
static INT32 _wzd_nw_reg_info_eb_frm_nfy(HANDLE_T    h_widget,
  	                            UINT32      ui4_msg,
  	                            VOID*       pv_param1,
  	                            VOID*       pv_param2)
{
    //HANDLE_T				h_cb_widget;
    WGL_NOTIFY_DATA_T*		pt_wgl_nfy_data;

    //h_cb_widget     = (HANDLE_T) pv_param1;
    pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if (ui4_msg == WGL_MSG_NOTIFY)
    {
        if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_EB_CHANGED) /* reg info edit gets input. */
        {
        	DBG_LOG_PRINT(("####[WZD][EB] --- CONTENT CHANGED. %s %d \n", __FUNCTION__,__LINE__));
			RET_ON_ERR (_wzd_nw_reg_info_update_eb_content(t_wzd_nw.t_info_reg.e_current_item));
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_info_reg_page_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_info_reg_page_create(HANDLE_T h_parent)
{
    INT32     i4_ret;

    i4_ret = _wzd_nw_frm_create(h_parent,
                                     WZD_NW_FRAME_X,
                                     WZD_NW_FRAME_Y,
                                     WZD_NW_FRAME_W,
                                     WZD_NW_FRAME_H,
                                     _wzd_nw_reg_info_eb_frm_nfy,
                                     &t_wzd_nw.t_info_reg.h_info_reg_frm);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_reg_info_float_prompt_create(h_parent);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_info_reg_edit_box_create(
                         t_wzd_nw.t_info_reg.h_info_reg_frm,
                         WZD_NW_EMAIL_EB_Y,
                         WZD_NW_INFO_REG_EB_LEFT_INSET,
                         WZD_NW_INFO_REG_EB_RIGHT_INSET,
                         WGL_STL_EB_MAX_CHAR_256,
                         _wzd_nw_info_eb_proc_fct,
                         &t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL]);
    RET_ON_ERR(i4_ret);


    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL],
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(WZD_NW_EMAIL_MAX_LEN+1)),
                          NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_info_reg_edit_box_create(
                         t_wzd_nw.t_info_reg.h_info_reg_frm,
                         WZD_NW_FIRST_NAME_EB_Y,
                         WZD_NW_INFO_REG_EB_LEFT_INSET,
                         WZD_NW_INFO_REG_EB_RIGHT_INSET,
                         WGL_STL_EB_MAX_CHAR_256,
                         _wzd_nw_info_eb_proc_fct,
                         &t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_FIRST_NAME]);
    RET_ON_ERR(i4_ret);


    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_FIRST_NAME],
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(WZD_NW_FIRST_NAME_MAX_LEN+1)),
                          NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_info_reg_edit_box_create(
                         t_wzd_nw.t_info_reg.h_info_reg_frm,
                         WZD_NW_LAST_NAME_EB_Y,
                         WZD_NW_INFO_REG_EB_LEFT_INSET,
                         WZD_NW_INFO_REG_EB_RIGHT_INSET,
                         WGL_STL_EB_MAX_CHAR_256,
                         _wzd_nw_info_eb_proc_fct,
                         &t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_LAST_NAME]);
    RET_ON_ERR(i4_ret);


    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_LAST_NAME],
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(WZD_NW_LAST_NAME_MAX_LEN+1)),
                          NULL);
    RET_ON_ERR(i4_ret);

    /*create phone num item*/
    i4_ret = _wzd_nw_info_reg_edit_box_create(
                         t_wzd_nw.t_info_reg.h_info_reg_frm,
                         WZD_NW_PHONE_NUM_EB_Y,
                         WZD_NW_INFO_REG_EB_LEFT_INSET,
                         WZD_NW_INFO_REG_EB_RIGHT_INSET,
                         WGL_STL_EB_MAX_CHAR_256,
                         _wzd_nw_info_eb_proc_fct,
                         &t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_PHONE_NUM]);
    RET_ON_ERR(i4_ret);


    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_PHONE_NUM],
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(WZD_NW_PHONE_NUM_MAX_LEN+1)),
                          NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_info_reg_edit_box_create(
                         t_wzd_nw.t_info_reg.h_info_reg_frm,
                         WZD_NW_ZIP_CODE_EB_Y,
                         WZD_NW_INFO_REG_EB_LEFT_INSET,
                         WZD_NW_INFO_REG_EB_RIGHT_INSET,
                         WGL_STL_EB_MAX_CHAR_256,
                         _wzd_nw_info_eb_proc_fct,
                         &t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_ZIP_CODE]);
    RET_ON_ERR(i4_ret);


    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_ZIP_CODE],
                          WGL_CMD_EB_SET_INPUT_LIMIT,
                          WGL_PACK((UINT16)(WZD_NW_ZIP_CODE_MAX_LEN+1)),
                          NULL);
    RET_ON_ERR(i4_ret);

	i4_ret = _wzd_network_info_reg_check_box_create(
                         t_wzd_nw.t_info_reg.h_info_reg_frm,
                         WZD_NW_EMAIL_CB_X,
                         WZD_NW_EMAIL_CB_Y,
                         &t_wzd_nw.t_info_reg.h_mail_accept_checkbox);
    RET_ON_ERR(i4_ret);
    i4_ret = _wzd_nw_info_reg_set_nav();
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_info_reg_frm,WGL_SW_HIDE_RECURSIVE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_vkb_data_ch_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_vkb_data_ch_nfy (VOID*    pv_tag,
                                      UINT32   ui4_msg,
                                      VOID*    pv_param1,
                                      VOID*    pv_param2)
{
    INT32               i4_ret = WDKR_OK;
    UTF16_T             w2s_text[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
	HANDLE_T            h_btn_focus = NULL_HANDLE;

	if (ui4_msg == VKB_MSG_DLG_KEY_EB_CLEAR)
	{
		if ((WZD_NW_VKB_PWD_INPUT == t_wzd_nw.t_vkb.e_vkb_style ||
			 WZD_NW_VKB_MANU_SSID == t_wzd_nw.t_vkb.e_vkb_style) &&
			(wzd_view_footer_get_enable(WZD_FOOTER_BTN_01)))
		{
			/* update footer btn and navi */
			RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
		    RET_ON_ERR (wzd_view_footer_update_btn_navigation());
			RET_ON_ERR (wzd_view_footer_frm_repaint());
		}
		if (WZD_NW_VKB_INFO_REG == t_wzd_nw.t_vkb.e_vkb_style)
        {
			RET_ON_ERR(_wzd_nw_reg_info_update_eb_content(t_wzd_nw.t_info_reg.e_current_item));
			DBG_LOG_PRINT(("\n####[wzd_reg_info%s(%d)]\n",__FUNCTION__,__LINE__));
		}
	}
    else if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        UINT32*  pui4_key_code = (UINT32*) pv_param1;
        BOOL     b_is_top_or_bottom = FALSE;
		BOOL     b_need_update_footer = FALSE;
        HANDLE_T h_vkb_next_entry = NULL_HANDLE;

		/* update footer enable status */
		RET_ON_ERR (c_wgl_get_focus(&h_btn_focus));
		if (t_wzd_nw.t_eb_ssid.h_eb == h_btn_focus ||
			t_wzd_nw.t_eb_pwd.h_eb == h_btn_focus)
		{
			b_need_update_footer = FALSE;
		}
		else
		{
			b_need_update_footer = TRUE;
		}

		if (BTN_RETURN == *pui4_key_code)
		{
			b_need_update_footer =  FALSE;
		}

		if (b_need_update_footer &&
		   (WZD_NW_VKB_PWD_INPUT == t_wzd_nw.t_vkb.e_vkb_style ||
			WZD_NW_VKB_MANU_SSID == t_wzd_nw.t_vkb.e_vkb_style))
        {
        	RET_ON_ERR (_wzd_nw_update_footer_btn_with_eb_content());
        }

        if (WZD_NW_VKB_INFO_REG == t_wzd_nw.t_vkb.e_vkb_style)
        {
			RET_ON_ERR(_wzd_nw_reg_info_update_eb_content(t_wzd_nw.t_info_reg.e_current_item));
			DBG_LOG_PRINT(("\n####[wzd_reg_info%s(%d)]\n",__FUNCTION__,__LINE__));
		}

        switch(*pui4_key_code)
        {
            case BTN_CURSOR_UP:
                switch(t_wzd_nw.t_vkb.e_vkb_style)
                {
                case WZD_NW_VKB_INFO_REG:
                {
                    i4_ret = a_vkb_current_is_top_row(t_wzd_nw.t_vkb.h_vkb_info, &b_is_top_or_bottom);
                    RET_ON_ERR(i4_ret);
                    if (b_is_top_or_bottom)
					{
						return WDK_NO_ACTION;
					}
					else
                    {
                        return WDKR_OK;
                    }
                }
                    break;
                case WZD_NW_VKB_MANU_SSID:
                {
					i4_ret = a_vkb_current_is_top_row(t_wzd_nw.t_vkb.h_vkb_ssid, &b_is_top_or_bottom);
                    RET_ON_ERR(i4_ret);

					if (b_is_top_or_bottom)
					{
						return WDK_NO_ACTION;
					}
					else
                    {
                        return WDKR_OK;
                    }
                }
                    break;
				case WZD_NW_VKB_PWD_INPUT:
                {
                    i4_ret = a_vkb_current_is_top_row(t_wzd_nw.t_vkb.h_vkb_pwd, &b_is_top_or_bottom);
                    RET_ON_ERR(i4_ret);

					if (b_is_top_or_bottom)
					{
						return WDK_NO_ACTION;
					}
					else
                    {
                        return WDKR_OK;
                    }
                }
                    break;
                default:
                    break;
                }
                break;
			case BTN_CURSOR_DOWN:
            {
                switch(t_wzd_nw.t_vkb.e_vkb_style)
                {
                    BOOL b_is_bottom_btn = FALSE;
                    case WZD_NW_VKB_MANU_SSID:
                    {
						i4_ret = a_vkb_current_is_bottom_row(t_wzd_nw.t_vkb.h_vkb_ssid,
                                                             &h_vkb_next_entry,
                                                             &b_is_bottom_btn);
                        if(i4_ret != WDKR_OK)
                        {
                            return WDKR_OK;
                        }

                        if (b_is_bottom_btn)
                        {
                            i4_ret = WDK_NO_ACTION;
                        }
                        else
                        {
                            return WDKR_OK;
                        }
                    }
                        break;
					case WZD_NW_VKB_PWD_INPUT:
                    {
                        i4_ret = a_vkb_current_is_bottom_row(t_wzd_nw.t_vkb.h_vkb_pwd,
                                                             &h_vkb_next_entry,
                                                             &b_is_bottom_btn);
                        if(i4_ret != WDKR_OK)
                        {
                            return WDKR_OK;
                        }

                        if (b_is_bottom_btn)
                        {
                            i4_ret = WDK_NO_ACTION;
                        }
                        else
                        {
                            return WDKR_OK;
                        }
                    }
                        break;
                    case WZD_NW_VKB_INFO_REG:
                    {
                        i4_ret = a_vkb_current_is_bottom_row(t_wzd_nw.t_vkb.h_vkb_info,
                                                             &h_vkb_next_entry,
                                                             &b_is_top_or_bottom);
                        if(i4_ret != WDKR_OK)
                        {
                            return WDKR_OK;
                        }

                        if (b_is_top_or_bottom)
                        {
							WGL_IMG_INFO_T	t_img_info;

							/* Set icon before the editbox */
							c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
						    t_img_info.e_type = WGL_IMG_SET_EXTEND;
						    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
						    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
						    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
						                          WGL_CMD_BDR_TIMG_SET_ICON,
						                          WGL_PACK(&t_img_info),
						                          WGL_PACK(NULL) );
						    RET_ON_ERR(i4_ret);

						    RET_ON_ERR(wzd_view_main_frm_repaint());

                            i4_ret = WDK_NO_ACTION;
                        }
                        else
                        {
                            return WDKR_OK;
                        }

                    }
                        break;
                    default:
                        return i4_ret;
                }

                if (WDK_NO_ACTION == i4_ret)
                {
                    _wzd_nw_footer_btn_focus();
                }
            }
                break;
            case BTN_SELECT:
            {
                switch(t_wzd_nw.t_vkb.e_vkb_style)
                {
                    case WZD_NW_VKB_INFO_REG:
                    {
						UINT32 		ui4_len = 0;
						UTF16_T     w2s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
                        i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_info,
                                              VKB_CMD_GET_TEXT,
                                              (VOID*) w2s_text,
                                              (VOID*) (UINT32) WZD_NW_EB_TXT_MAX_LEN);
                        RET_ON_ERR(i4_ret);

                        if (WZD_NW_REG_INFO_ZIP_CODE == t_wzd_nw.t_info_reg.e_current_item)
                        {
                            if (c_uc_w2s_strlen(w2s_text) > (WZD_NW_ZIP_CODE_MAX_LEN))
                            {
                                break;
                            }
                        }

                        if (WZD_NW_REG_INFO_PHONE_NUM == t_wzd_nw.t_info_reg.e_current_item)
                        {
                            if (c_uc_w2s_strlen(w2s_text) > (WZD_NW_PHONE_NUM_MAX_LEN))
                            {
                                break;
                            }
                        }
                        if(t_wzd_nw.t_info_reg.e_current_item < WZD_NW_REG_INFO_LAST_ENTRY)
                        {
                            c_memset(&t_wzd_nw.t_info_reg.aw2s_editbox_context[t_wzd_nw.t_info_reg.e_current_item], 0,
                                 sizeof(t_wzd_nw.t_info_reg.aw2s_editbox_context[t_wzd_nw.t_info_reg.e_current_item]));

                            c_uc_w2s_strncpy(t_wzd_nw.t_info_reg.aw2s_editbox_context[t_wzd_nw.t_info_reg.e_current_item],
                                             w2s_text, WZD_NW_EB_TXT_MAX_LEN);


                            i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
                                                  WGL_CMD_EB_SET_TEXT,
                                                  WGL_PACK(t_wzd_nw.t_info_reg.aw2s_editbox_context[t_wzd_nw.t_info_reg.e_current_item]),
                                                  WGL_PACK(c_uc_w2s_strlen(t_wzd_nw.t_info_reg.aw2s_editbox_context[t_wzd_nw.t_info_reg.e_current_item])));
                            RET_ON_ERR(i4_ret);

                            i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
                                                  WGL_CMD_EB_SET_CURSOR_POS,
                                                  WGL_PACK(c_uc_w2s_strlen(t_wzd_nw.t_info_reg.aw2s_editbox_context[t_wzd_nw.t_info_reg.e_current_item])),
                                                  NULL);
                            RET_ON_ERR(i4_ret);
                            RET_ON_ERR(_wzd_nw_reg_info_update_eb_content(t_wzd_nw.t_info_reg.e_current_item));
                            DBG_LOG_PRINT(("\n####[wzd_reg_info%s(%d)]\n",__FUNCTION__,__LINE__));

                            if(t_wzd_nw.t_info_reg.e_current_item == WZD_NW_REG_INFO_MAIL)
				            {
								i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL],
					                                  WGL_CMD_EB_GET_TEXT,
					                                  WGL_PACK (w2s_str),
					                                  WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
						        RET_ON_ERR(i4_ret);
						        ui4_len = c_uc_w2s_strlen(w2s_str);
				            	e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;
						        if(ui4_len > 0)
						        {
					                RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
				                }
				                else
				                {
					                RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
				                }
				            }

				            i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_info_reg_frm, WGL_SW_NORMAL);
                            RET_ON_ERR(i4_ret);

                            i4_ret = c_wgl_repaint(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item], NULL, TRUE);
                            RET_ON_ERR(i4_ret);

                        }
                    }
                        break;
                    case WZD_NW_VKB_MANU_SSID:
                    {
						RET_ON_ERR (c_wgl_get_focus(&h_btn_focus));
						if (t_wzd_nw.t_eb_ssid.h_eb == h_btn_focus)
						{
						#if 0
							/* save ssid from vkb */
							RET_ON_ERR (a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_ssid,
						                          VKB_CMD_GET_TEXT,
						                          (VOID*) w2s_text,
						                          (VOID*) (UINT32) WZD_NW_EB_TXT_MAX_LEN));
							c_uc_w2s_strncpy(t_wzd_nw.aw2s_ssid_context, w2s_text, WZD_NW_SSID_MAX_LEN);

							/* select encryption */
							RET_ON_ERR (_wzd_nw_go(NW_SETUP_STATE_WIRELESS_PWD_INPUT, TRUE));

							return WDK_NO_ACTION;
						#else
							_wzd_nw_footer_btn_focus();

							return WDK_NO_ACTION;
						#endif
						}
                    }
                        break;

                    case WZD_NW_VKB_PWD_INPUT:
                    {
						RET_ON_ERR (c_wgl_get_focus(&h_btn_focus));
						if (t_wzd_nw.t_eb_pwd.h_eb == h_btn_focus)
						{
						#if 0
							/* save password from vkb */
							RET_ON_ERR (a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_pwd,
						                          VKB_CMD_GET_TEXT,
						                          (VOID*) w2s_text,
						                          (VOID*) (UINT32) WZD_NW_EB_TXT_MAX_LEN));
							c_uc_w2s_strncpy(t_wzd_nw.aw2s_key_context, w2s_text, WZD_NW_KEY_MAX_LEN);

							/* start associate */
							if (e_g_nw_setup_pre_state == NW_SETUP_STATE_WIRELESS_SSID_INPUT)
							{
								RET_ON_ERR (_wzd_nw_wifi_scan_with_ssid());
							}
							else
							{
								RET_ON_ERR (_wzd_nw_pwd_wifi_assoc());
							}

							return WDK_NO_ACTION;
						#else
							_wzd_nw_footer_btn_focus();

							return WDK_NO_ACTION;
						#endif
						}
                    }
                        break;
                    default:
                        break;
                }
            }
                break;
            case BTN_CURSOR_LEFT:
            {
				UINT32			ui4_len = 0;
				UTF16_T     w2s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
                if (WZD_NW_VKB_INFO_REG == t_wzd_nw.t_vkb.e_vkb_style)
                {
	                if(t_wzd_nw.t_info_reg.e_current_item < WZD_NW_REG_INFO_LAST_ENTRY)
	                {
	                    if(a_vkb_current_get_col_index(t_wzd_nw.t_vkb.h_vkb_info) == 0)
	                    {
	                        i4_ret = c_wgl_set_focus(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item], TRUE);
	                        RET_ON_ERR(i4_ret);

	                        i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_info_reg_frm, WGL_SW_NORMAL);
	                        RET_ON_ERR(i4_ret);

	                        i4_ret = c_wgl_repaint(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item], NULL, TRUE);
	                        RET_ON_ERR(i4_ret);

	                        if(t_wzd_nw.t_info_reg.e_current_item == WZD_NW_REG_INFO_MAIL)
				            {
								i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL],
					                                  WGL_CMD_EB_GET_TEXT,
					                                  WGL_PACK (w2s_str),
					                                  WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
						        RET_ON_ERR(i4_ret);
						        ui4_len = c_uc_w2s_strlen(w2s_str);
						        e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;
						        if(ui4_len > 0)
						        {
					                RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
				                }
				                else
				                {
					                RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
				                }
				            }

				            WGL_IMG_INFO_T	t_img_info;

							/* Set icon before the editbox */
							c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
						    t_img_info.e_type = WGL_IMG_SET_EXTEND;
						    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
						    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
						    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
						                          WGL_CMD_BDR_TIMG_SET_ICON,
						                          WGL_PACK(&t_img_info),
						                          WGL_PACK(NULL) );
						    RET_ON_ERR(i4_ret);

	                        return WDK_NO_ACTION;
	                    }
	                }
                }
            }
                break;
			case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
                break;
            default :
            {
				UINT32			ui4_len = 0;
				UTF16_T     w2s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
                if (WZD_NW_VKB_INFO_REG == t_wzd_nw.t_vkb.e_vkb_style
                    && (t_wzd_nw.t_info_reg.e_current_item < WZD_NW_REG_INFO_LAST_ENTRY))
                {
                    if (((BTN_DIGIT_0 <= *pui4_key_code) && (BTN_DIGIT_9 >= *pui4_key_code)) ||
                        ((BTN_KB_NULL <= *pui4_key_code) && (BTN_KB_HYPER >= *pui4_key_code)))
                    {
                        i4_ret = c_wgl_set_focus(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item], TRUE);
                        RET_ON_ERR(i4_ret);

                        i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_info_reg_frm, WGL_SW_NORMAL);
                        RET_ON_ERR(i4_ret);

                        i4_ret = c_wgl_repaint(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item], NULL, TRUE);
                        RET_ON_ERR(i4_ret);

                        if(t_wzd_nw.t_info_reg.e_current_item == WZD_NW_REG_INFO_MAIL)
			            {
							i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL],
					                                  WGL_CMD_EB_GET_TEXT,
					                                  WGL_PACK (w2s_str),
					                                  WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
					        RET_ON_ERR(i4_ret);
					        ui4_len = c_uc_w2s_strlen(w2s_str);
					        e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;
					        if(ui4_len > 0)
					        {
				                RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, TRUE));
			                }
			                else
			                {
				                RET_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, FALSE));
			                }
			            }

                        c_wgl_default_msg_proc(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
                                                WGL_MSG_KEY_DOWN,
                                                (VOID*)(*pui4_key_code),
                                                NULL);

						WGL_IMG_INFO_T	t_img_info;

						/* Set icon before the editbox */
						c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
						t_img_info.e_type = WGL_IMG_SET_EXTEND;
						t_img_info.u_img_data.t_extend.t_enable 			= NULL_HANDLE;
						t_img_info.u_img_data.t_extend.t_highlight			= h_g_wzd_img_text_focus;
						i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
											  WGL_CMD_BDR_TIMG_SET_ICON,
											  WGL_PACK(&t_img_info),
											  WGL_PACK(NULL) );
						RET_ON_ERR(i4_ret);

                        return WDK_NO_ACTION;
                    }
                }

                break;
            }
        }
    }
    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_vkb_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_vkb_create(HANDLE_T h_parent)
{
    INT32              i4_ret;
    VKB_INIT_T         t_init_data;

	i4_ret = _wzd_nw_text_create(
                         h_parent,
                         WZD_NW_VKB_TITLE_X,
                         WZD_NW_VKB_TITLE_Y,
                         WZD_NW_VKB_TITLE_W,
                         WZD_NW_VKB_TITLE_H,
                         NULL_HANDLE,
                         NULL_HANDLE,
                         &t_wzd_nw.t_vkb.t_title.h_widget);
    RET_ON_ERR(i4_ret);

    t_wzd_nw.t_vkb.t_title.ui2_msg_idx = MLM_WZD_KEY_EMPTY;

    i4_ret = _wzd_nw_text_set_text(t_wzd_nw.t_vkb.t_title.h_widget,
                                   t_wzd_nw.t_vkb.t_title.ui2_msg_idx);
    RET_ON_ERR(i4_ret);

	/* create wizard normal vkb */
    c_memset(&t_init_data, 0 , sizeof(VKB_INIT_T));
    t_init_data.h_parent           = h_parent;
    t_init_data.pf_data_change_fct = _wzd_nw_vkb_data_ch_nfy;
    t_init_data.ui4_style_mask     = VKB_STYLE_MASK_FULL_SCREEN;
    t_init_data.pv_tag             = NULL;
    t_init_data.t_gui_rc.i4_left   = WZD_NW_INFO_VKB_FRAME_X;
    t_init_data.t_gui_rc.i4_top    = WZD_NW_INFO_VKB_FRAME_Y;

    i4_ret = a_vkb_create(&t_init_data,
                          &t_wzd_nw.t_vkb.h_vkb_info);
    RET_ON_ERR(i4_ret);

	i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_info,
                                  VKB_CMD_SET_MAX_CHAR_NUM,
                                  (VOID*)WZD_NW_SSID_MAX_LEN,
                                  NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_info,
                          VKB_CMD_SET_STYLE_MASK,
                          (VOID*)VKB_STYLE_MASK_FULL_SCREEN,
                          (VOID*)NULL);
    RET_ON_ERR(i4_ret);

	/* create wizard password vkb */
    c_memset(&t_init_data, 0 , sizeof(VKB_INIT_T));
    t_init_data.h_parent           = h_parent;
    t_init_data.pf_data_change_fct = _wzd_nw_vkb_data_ch_nfy;
    t_init_data.ui4_style_mask     = VKB_STYLE_MASK_FULL_SCREEN | VKB_STYLE_MASK_WITH_EB_CLEAR;
    t_init_data.pv_tag             = NULL;
    t_init_data.t_gui_rc.i4_left   = WZD_NW_PWD_VKB_FRAME_X;
    t_init_data.t_gui_rc.i4_top    = WZD_NW_PWD_VKB_FRAME_Y;

    i4_ret = a_vkb_create(&t_init_data,
                          &t_wzd_nw.t_vkb.h_vkb_pwd);
    RET_ON_ERR(i4_ret);

	i4_ret = a_vkb_do_cmd (t_wzd_nw.t_vkb.h_vkb_pwd,
                               VKB_CMD_SET_MAX_CHAR_NUM,
                               (VOID*)(WZD_NW_KEY_MAX_LEN+1),
                               NULL);
    RET_ON_ERR(i4_ret);

	/* create wizard ssid vkb */
    c_memset(&t_init_data, 0 , sizeof(VKB_INIT_T));
    t_init_data.h_parent           = h_parent;
    t_init_data.pf_data_change_fct = _wzd_nw_vkb_data_ch_nfy;
    t_init_data.ui4_style_mask     = VKB_STYLE_MASK_FULL_SCREEN | VKB_STYLE_MASK_WITH_EB_CLEAR;
    t_init_data.pv_tag             = NULL;
    t_init_data.t_gui_rc.i4_left   = WZD_NW_SSID_VKB_FRAME_X;
    t_init_data.t_gui_rc.i4_top    = WZD_NW_SSID_VKB_FRAME_Y;

    i4_ret = a_vkb_create(&t_init_data,
                          &t_wzd_nw.t_vkb.h_vkb_ssid);
    RET_ON_ERR(i4_ret);

	i4_ret = a_vkb_do_cmd (t_wzd_nw.t_vkb.h_vkb_ssid,
                               VKB_CMD_SET_MAX_CHAR_NUM,
                               (VOID*)(WZD_NW_SSID_MAX_LEN+1),
                               NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_info, FALSE);
    RET_ON_ERR(i4_ret);

    i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_pwd, FALSE);
    RET_ON_ERR(i4_ret);

	i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_ssid, FALSE);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

#ifdef APP_DYNAMIC_TOS_SUPPORT
static TOS_TYPE_T _wzd_tos_get_type (VOID)
{
    TOS_TYPE_T      e_type = TOS_TYPE_LAST_VALID_ITEM;

    if (WZD_NW_PROTOCOL_SCAN_TERMS == t_wzd_nw.t_protocol.e_scan_text)
	{
		if (MLM_WZD_LANG_FRE == t_wzd_nw.ui2_lang_id)
		{
			e_type = TOS_TYPE_TOS_FRE;
		}
		else if (MLM_WZD_LANG_SPA == t_wzd_nw.ui2_lang_id)
		{
			e_type = TOS_TYPE_TOS_SPA;
		}
		else
		{
			e_type = TOS_TYPE_TOS_ENG;
		}
	}
	else if (WZD_NW_PROTOCOL_SCAN_POLICY == t_wzd_nw.t_protocol.e_scan_text)
	{
		if (MLM_WZD_LANG_FRE == t_wzd_nw.ui2_lang_id)
		{
			e_type = TOS_TYPE_PRIVACY_FRE;
		}
		else if (MLM_WZD_LANG_SPA == t_wzd_nw.ui2_lang_id)
		{
			e_type = TOS_TYPE_PRIVACY_SPA;
		}
		else
		{
			e_type = TOS_TYPE_PRIVACY_ENG;
		}
	}
    else
    {
        e_type = TOS_TYPE_PRIVACY_ENG;
    }

    return e_type;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_tos_download_stop_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _wzd_tos_download_stop_nfy (VOID*   pv_data,
                                        SIZE_T  z_data_size)
{
    INT32   		i4_ret;
    CHAR            s_buf_path[255] = {0};
    TOS_TYPE_T      e_tos_type = TOS_TYPE_LAST_VALID_ITEM;

    e_tos_type = _wzd_tos_get_type();

    a_tos_get_file_path(e_tos_type, s_buf_path);
    DBG_INFO(("[WZD][TOS] download path. %s %s\n", __FUNCTION__, s_buf_path));


    /* stop timer and hide cycle icon */
    c_timer_stop(t_wzd_nw.t_protocol.h_timer);
	t_wzd_nw.b_is_busying = FALSE;
	c_wgl_show (t_wzd_nw.h_timer_icon, WGL_SW_HIDE_RECURSIVE);

    if (a_tos_is_file_exist(e_tos_type))
    {
        DBG_INFO(("[WZD][TOS] download success. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));

        c_strncpy(t_wzd_nw.t_protocol.s_file_path, s_buf_path, 127);

        i4_ret = _wzd_nw_protocol_text_open();
    	if (WZDR_OK == i4_ret)
    	{
            t_wzd_nw.t_protocol.b_is_file_opened = TRUE;
    	}
    }
    else
    {
        DBG_INFO(("[WZD][TOS] download failed. FUNC:%s LINE:%d.\n", __FUNCTION__, __LINE__));
    }

    if (FALSE == t_wzd_nw.t_protocol.b_is_file_opened)
    {
        /* just show error msg */
        _wzd_nw_protocol_error_msg_show();
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_tos_download_nfy_cb
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _wzd_tos_download_nfy_cb(UINT16 	ui2_nfy_id,
                                      VOID* 	pv_tag,
                                      ICL_NOTIFY_DATA_T* pt_notify_data)
{
    INT32  				i4_ret;
    ICL_GRPID_TYPE 		e_grp_id;
    SIZE_T 				z_size ;
    UINT8      			ui1_download_status = ICL_TOS_DOWNLOAD_ITEM_STOP;

    /* if network page is NOT ready to show */
    if (!b_nw_ready_to_show)
    {
        return WZDR_OK;
    }

	e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    if (e_grp_id != ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS)
    {
        return WZDR_OK;
    }

	if (NW_SETUP_STATE_PROTOCOL != e_g_nw_setup_state)
	{
		return WZDR_OK;
	}

	/* get download status */
    z_size = ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS, ICL_RECID_TOS_DOWNLOAD_ITEM_STATUS),
                       &ui1_download_status,
                       &z_size);
    if (ICLR_OK != i4_ret)
    {
        return WZDR_FAIL;
    }

    if (ICL_TOS_DOWNLOAD_ITEM_STOP == ui1_download_status)
    {
        wzd_async_invoke(_wzd_tos_download_stop_nfy, NULL, 0, FALSE);
    }

    DBG_INFO(("[WZD] --- tos download status = %d.\n", ui1_download_status));

    return WZDR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_create(HANDLE_T h_parent)
{
    INT32     i4_ret;

    i4_ret = _wzd_nw_protocol_page_create(h_parent);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_none_conn_page_create(h_parent);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_info_reg_page_create(h_parent);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_vkb_create(h_parent);
    RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_float_prompt_create(h_parent);
    RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_pwd_eb_create(h_parent);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_ssid_eb_create(h_parent);
    RET_ON_ERR(i4_ret);

	i4_ret = _wzd_nw_mac_addr_create(h_parent);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_searching_icon_create(h_parent, &t_wzd_nw.h_timer_icon);
    RET_ON_ERR(i4_ret);

    i4_ret = c_timer_create(&t_wzd_nw.t_choice_connect.h_timer);
    RET_ON_ERR(i4_ret);

    i4_ret = a_nw_register(_wzd_nw_notify_callback,
                           (VOID *)&t_wzd_nw.t_choice_connect.ui4_wzd_nw_tag,
                           &t_wzd_nw.t_choice_connect.ui4_wzd_nw_nfy_id );
    RET_ON_ERR(i4_ret);

#ifdef APP_DYNAMIC_TOS_SUPPORT
    i4_ret = a_icl_notify_reg(ICL_GRPID_TOS_DOWNLOAD_ITEM_STATUS,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _wzd_tos_download_nfy_cb,
                              &(t_wzd_nw.t_protocol.ui2_tos_nfy_id));


    if(ICLR_OK != i4_ret)
	{
		t_wzd_nw.t_protocol.ui2_tos_nfy_id = 0;
		return WZDR_FAIL;
	}
#endif

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_help_lst_update
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
static INT32 _wzd_nw_help_lst_update (NW_SETUP_STATE	e_nw_setup_state,
                                      BOOL            	b_repaint)
{
	UINT8		ui1_btn_num = 0;
    BOOL    	b_btn_1st = FALSE;
    BOOL    	b_btn_2nd = FALSE;
	UTF16_T*    pw2s_text_1st = NULL;
	UTF16_T*    pw2s_text_2nd = NULL;

	/* reset previous focused flag */
	e_footer_pre_focused_btn = WZD_FOOTER_BTN_01;

	if (e_nw_setup_state == NW_SETUP_STATE_BEGIN)
	{
		ui1_btn_num = 0;
	}
	else if (e_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCANNING ||
		e_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCAN_RESULT)
	{
		ui1_btn_num		= 2;

		b_btn_1st 		= TRUE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_HIDE_NETWORK);

        b_btn_2nd 		= TRUE;
		pw2s_text_2nd 	= WZD_TEXT(MLM_WZD_KEY_BT_REMOTE_DLG_SKIP);
	}
	else if (e_nw_setup_state == NW_SETUP_STATE_NONE_CONN)
	{
		ui1_btn_num		= 3;

		b_btn_1st 		= TRUE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_TRY_AGAIN);

        b_btn_2nd 		= TRUE;
		pw2s_text_2nd 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_HIDE_NETWORK);

		wzd_view_footer_set_text(WZD_FOOTER_BTN_03, WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_SKIP));
	}
	else if (e_nw_setup_state == NW_SETUP_STATE_WIRELESS_PWD_INPUT)
	{
		ui1_btn_num		= 2;

		b_btn_1st 		= FALSE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_CONNECT);

        b_btn_2nd 		= TRUE;
		pw2s_text_2nd 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_WPS);
	}
	else if (e_nw_setup_state == NW_SETUP_STATE_WIRELESS_SSID_INPUT)
	{
		ui1_btn_num 	= 1;

		b_btn_1st 		= FALSE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_NEXT);
	}
	else if (e_nw_setup_state == NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT)
	{
		ui1_btn_num 	= 0;
	}
	else if (e_nw_setup_state == NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE)
	{
		ui1_btn_num 	= 1;

		b_btn_1st 		= TRUE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_CANCEL);
	}
	else if (e_nw_setup_state == NW_SETUP_STATE_PROTOCOL)
	{
		ui1_btn_num		= 2;

		b_btn_1st 		= TRUE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_ACCEPT);

        b_btn_2nd 		= TRUE;
		pw2s_text_2nd 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_DECLINE);
	}
	else if (e_nw_setup_state == NW_SETUP_STATE_INFO_REG)
	{
		UINT32 			ui4_len = 0;
		UTF16_T    		w2s_str[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
		INT32		    i4_ret = WZDR_OK;

		ui1_btn_num		= 2;
		i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL],
					                                  WGL_CMD_EB_GET_TEXT,
					                                  WGL_PACK (w2s_str),
					                                  WGL_PACK (WZD_NW_EB_TXT_MAX_LEN+1));
        RET_ON_ERR(i4_ret);
        ui4_len = c_uc_w2s_strlen(w2s_str);
        if(ui4_len > 0)
        {
            b_btn_1st 		= TRUE;
        }
        else
        {
            b_btn_1st 		= FALSE;
        }
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_NEXT);

        b_btn_2nd 		= TRUE;
		pw2s_text_2nd 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_SKIP);
	}
	else
	{
		ui1_btn_num 	= 2;

		b_btn_1st 		= TRUE;
		pw2s_text_1st 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_CONNECT);

        b_btn_2nd 		= TRUE;
		pw2s_text_2nd 	= WZD_TEXT(MLM_WZD_KEY_NW_SETUP_FOOTER_SKIP);
	}

	/* set footer frame visibility */
	if (ui1_btn_num == 0)
	{
		SHOW_ON_ERR (wzd_view_footer_set_visibility(FALSE));
	}
	else
	{
		SHOW_ON_ERR (wzd_view_footer_set_visibility(TRUE));
	}

	/* set footer button num */
	SHOW_ON_ERR (wzd_view_footer_set_btn_num(ui1_btn_num));

	/* update 1st footer button */
	SHOW_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_01, pw2s_text_1st));
	SHOW_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_01, b_btn_1st));

	/* update 2nd footer button */
	SHOW_ON_ERR (wzd_view_footer_set_text(WZD_FOOTER_BTN_02, pw2s_text_2nd));
	SHOW_ON_ERR (wzd_view_footer_set_enable(WZD_FOOTER_BTN_02, b_btn_2nd));

	/* update footer button navigation */
    SHOW_ON_ERR (wzd_view_footer_update_btn_navigation());

	if (b_repaint)
	{
		SHOW_ON_ERR (wzd_view_footer_frm_repaint());
	}

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_footer_btn_focus
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_footer_btn_focus(VOID)
{
	UINT8           ui1_i = 0;

	/* deal with previous focus flag first */
	if (wzd_view_footer_get_enable(e_footer_pre_focused_btn))
	{
		RET_ON_ERR (wzd_view_footer_set_focus(e_footer_pre_focused_btn, TRUE));
		return WZDR_OK;
	}

	for (ui1_i = 0; ui1_i < WZD_FOOTER_BTN_COUNT; ui1_i ++)
	{
		if (wzd_view_footer_get_enable(ui1_i))
		{
			RET_ON_ERR (wzd_view_footer_set_focus(ui1_i, TRUE));
			return WZDR_OK;
		}
	}

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_on_footer_nfy
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
static VOID _wzd_page_nw_setup_on_footer_nfy( UINT32   ui4_msg,
                                VOID*    pv_param1,
                                VOID*    pv_param2)
{
	BOOL 		b_visible = FALSE;
	HANDLE_T 	h_sel_box = NULL_HANDLE;
	UTF16_T     w2s_content[WZD_NW_EB_TXT_MAX_LEN+1] = {0};
	NW_SETUP_STATE e_temp_pre_state = NW_SETUP_STATE_BEGIN;

    switch( ui4_msg )
    {
    	case WZD_FOOTER_MSG_ITEM_FOCUSED:
			e_footer_pre_focused_btn = (WZD_FOOTER_BTN_INDEX_T)pv_param1;
			break;
        case WZD_FOOTER_MSG_KEY_INPUT:
            switch((UINT32)pv_param1)
            {
                case BTN_SELECT:
					if( WZD_FOOTER_BTN_01 == (WZD_FOOTER_BTN_INDEX_T)pv_param2 )
	                {
	                	if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCANNING)
		            	{
							t_wzd_nw.b_is_busying = FALSE;
							t_wzd_nw.b_timer_result = TRUE;

							SHOW_ON_ERR (_wzd_nw_go(NW_SETUP_STATE_WIRELESS_SSID_INPUT, TRUE));
		            	}
	                	else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCAN_RESULT)
			        	{
			        		if (t_wzd_nw.b_is_busying == FALSE)
				            {
				            	SHOW_ON_ERR (_wzd_nw_go(NW_SETUP_STATE_WIRELESS_SSID_INPUT, TRUE));
				            }
			        	}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_NONE_CONN)
						{
							SHOW_ON_ERR (_wzd_nw_conn_lan_or_wifi());
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_PWD_INPUT)
						{
							/* save password from vkb */
							SHOW_ON_ERR (a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_pwd,
						                          VKB_CMD_GET_TEXT,
						                          (VOID*) w2s_content,
						                          (VOID*) (UINT32) WZD_NW_EB_TXT_MAX_LEN));
							c_uc_w2s_strncpy(t_wzd_nw.aw2s_key_context, w2s_content, WZD_NW_KEY_MAX_LEN);

							/* start associate */
							SHOW_ON_ERR (_wzd_nw_pwd_wifi_assoc());
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SSID_INPUT)
						{
							/* save ssid from vkb */
							SHOW_ON_ERR (a_vkb_do_cmd(t_wzd_nw.t_vkb.h_vkb_ssid,
						                          VKB_CMD_GET_TEXT,
						                          (VOID*) w2s_content,
						                          (VOID*) (UINT32) WZD_NW_EB_TXT_MAX_LEN));
							c_uc_w2s_strncpy(t_wzd_nw.aw2s_ssid_context, w2s_content, WZD_NW_SSID_MAX_LEN);

							/* NEXT scan with ssid */
							SHOW_ON_ERR (_wzd_nw_wifi_scan_with_ssid());
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE)
						{
							/* store previous state */
							e_g_nw_setup_state = e_g_nw_setup_pre_state;

							/* cancel WPS */
							SHOW_ON_ERR (_wzd_nw_wps_associate_cancel());
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_PROTOCOL)
						{
							if (t_wzd_nw.b_is_busying)
							{
								return;
							}

							if (WZD_NW_PROTOCOL_SCAN_NULL != t_wzd_nw.t_protocol.e_scan_text)
							{
								_wzd_nw_protocol_text_show_exit_scan();
							}
							else
							{
								i1_tos_is_accept = 1;

								/* accept the TOS and Privacy Policy*/
								a_tv_custom_set_tos (TRUE);
			                	a_tv_custom_set_privacy (TRUE);

								SHOW_ON_ERR(a_tv_custom_set_tos_version());
								SHOW_ON_ERR (_wzd_nw_go(NW_SETUP_STATE_INFO_REG, TRUE));
							}
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_INFO_REG)
						{
						    b_reg_info_is_store = TRUE;
							SHOW_ON_ERR (_wzd_nw_info_next_btn_select_proc_fct());
						}
						else
						{
							/* do nothing */
						}
	                }
	                else if( WZD_FOOTER_BTN_02 == (WZD_FOOTER_BTN_INDEX_T)pv_param2 )
	                {
	                	if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCANNING)
		            	{
                            t_wzd_nw.b_is_busying = FALSE;
							c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_HIDE);

                            /* update current connected status */
                            _wzd_nw_update_curr_connect_status();

                            /* no need show skip dialog after network be connected  */
							if (t_wzd_nw.t_choice_connect.b_connected)
							{
							    if ((i1_tos_is_accept != 1) &&
                            		(a_tv_custom_get_tos() == FALSE ||a_tv_custom_get_privacy() == FALSE))
                                {
                                    SHOW_ON_ERR(_wzd_nw_go(NW_SETUP_STATE_PROTOCOL, TRUE));
                                }
                            	else if(!a_wzd_is_resume_from_menu_setup())
                                {
                                    SHOW_ON_ERR(_wzd_nw_go(NW_SETUP_STATE_INFO_REG, TRUE));
                                }
                                else
                                {
                                    SHOW_ON_ERR(_wzd_nw_leave_this_page());
                                }
							}
							else
							{
								/* skip dialog */
		           	 			SHOW_ON_ERR (_wzd_nw_skip_dlg_create(WZD_NW_DLG_1));
							}
		            	}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCAN_RESULT)
						{
							/* no need show skip dialog after network be connected  */
							if (t_wzd_nw.t_choice_connect.b_connected)
							{
								if ((i1_tos_is_accept != 1) &&
                            		(a_tv_custom_get_tos() == FALSE ||a_tv_custom_get_privacy() == FALSE))
                                {
                                    SHOW_ON_ERR(_wzd_nw_go(NW_SETUP_STATE_PROTOCOL, TRUE));
                                }
                            	else if(!a_wzd_is_resume_from_menu_setup())
                                {
                                    SHOW_ON_ERR(_wzd_nw_go(NW_SETUP_STATE_INFO_REG, TRUE));
                                }
                                else
                                {
                                    SHOW_ON_ERR(_wzd_nw_leave_this_page());
                                }
							}
							else
							{
								/* skip dialog */
		           	 			SHOW_ON_ERR (_wzd_nw_skip_dlg_create(WZD_NW_DLG_1));
							}
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_NONE_CONN)
						{
							if(t_wzd_nw.b_is_busying == FALSE)
				            {
				            	SHOW_ON_ERR (_wzd_nw_go(NW_SETUP_STATE_WIRELESS_SSID_INPUT, TRUE));
				            }
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_PWD_INPUT)
						{
							/* store previous state */
							e_temp_pre_state = e_g_nw_setup_pre_state;

							/* start WPS */
							SHOW_ON_ERR (_wzd_nw_wps_associate());

							/* restore previous state */
							e_g_nw_setup_pre_state = e_temp_pre_state;
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_PROTOCOL)
						{
							i1_tos_is_accept = -1;

							/* decline the TOS */
							a_tv_custom_set_tos (FALSE);
			                a_tv_custom_set_privacy (FALSE);

							SHOW_ON_ERR (_wzd_nw_skip_dlg_create(WZD_NW_DLG_2));
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_INFO_REG)
						{
							/* show skip the info reg dlg */
							SHOW_ON_ERR (_wzd_nw_skip_dlg_create(WZD_NW_DLG_3));
						}
						else
						{
							/* do nothing */
						}

						wzd_view_main_frm_repaint();
	                }
					else
					{
						if (e_g_nw_setup_state == NW_SETUP_STATE_NONE_CONN)
		            	{
		            		/* skip dialog */
		           	 		SHOW_ON_ERR (_wzd_nw_skip_dlg_create(WZD_NW_DLG_1));
		            	}
						else
						{
		            		/* no action */
		            	}
					}
                    break;

				case BTN_CURSOR_UP:
					{
	                	if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SCAN_RESULT)
						{
							/* focus to pre select box */
							h_sel_box = wzd_view_sel_box_get_btn_handle (e_sb_pre_focused_box);
							c_wgl_get_visibility(h_sel_box, &b_visible);
					        if (b_visible)
					        {
					            SHOW_ON_ERR (wzd_view_sel_box_set_focus(e_sb_pre_focused_box, FALSE));
					        }
							wzd_view_main_frm_repaint();
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_PWD_INPUT)
						{
							/* focus to pwd vkb */
							SHOW_ON_ERR (a_vkb_set_focus(t_wzd_nw.t_vkb.h_vkb_pwd));
							wzd_view_main_frm_repaint();
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_WIRELESS_SSID_INPUT)
						{
							/* focus to ssid vkb */
							SHOW_ON_ERR (a_vkb_set_focus(t_wzd_nw.t_vkb.h_vkb_ssid));
							wzd_view_main_frm_repaint();
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_PROTOCOL)
						{
							if (WZD_NW_PROTOCOL_SCAN_TERMS == t_wzd_nw.t_protocol.e_scan_text)
							{
							#ifdef APP_DYNAMIC_TOS_SUPPORT
							    if (FALSE == t_wzd_nw.t_protocol.b_is_file_opened)
                                {
                                    return;
                                }
							#endif
								SHOW_ON_ERR (c_wgl_float(t_wzd_nw.t_protocol.t_protocol_terms.h_icon_down, TRUE, FALSE));
								SHOW_ON_ERR (c_wgl_set_focus(t_wzd_nw.t_protocol.t_protocol_terms.h_icon_down, WGL_SYNC_AUTO_REPAINT));
							}
							else if (WZD_NW_PROTOCOL_SCAN_POLICY == t_wzd_nw.t_protocol.e_scan_text)
							{
							#ifdef APP_DYNAMIC_TOS_SUPPORT
							    if (FALSE == t_wzd_nw.t_protocol.b_is_file_opened)
                                {
                                    return;
                                }
							#endif
								SHOW_ON_ERR (c_wgl_float(t_wzd_nw.t_protocol.t_protocol_policy.h_icon_down, TRUE, FALSE));
								SHOW_ON_ERR (c_wgl_set_focus(t_wzd_nw.t_protocol.t_protocol_policy.h_icon_down, WGL_SYNC_AUTO_REPAINT));
							}
							else
							{
								/* focus to Privacy Policy button */
								SHOW_ON_ERR (c_wgl_set_focus(t_wzd_nw.t_protocol.t_protocol_policy.h_widget, WGL_SYNC_AUTO_REPAINT));
							}
						}
						else if (e_g_nw_setup_state == NW_SETUP_STATE_INFO_REG)
						{
							SHOW_ON_ERR (c_wgl_set_focus(t_wzd_nw.t_info_reg.h_mail_accept_checkbox, WGL_SYNC_AUTO_REPAINT));
						}
						else
						{
							/* do nothing */
						}

						return;
	                }
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_return_nfy_cb
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
static VOID _wzd_page_nw_setup_return_nfy_cb(VOID)
{
	BOOL 		b_wired_plug = FALSE;

	/* special case, can return to previous page while wlan scanning ap */
	if (NW_SETUP_STATE_WIRELESS_SCANNING == e_g_nw_setup_state)
	{
		if (a_wzd_is_resume_from_menu_setup())
		{
			_wzd_nw_leave_this_page();
		}
		else
		{
			t_wzd_nw.b_is_busying = FALSE;
			c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_HIDE);
			wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
		}
	}

	if (t_wzd_nw.b_is_busying)
	{
		return;
	}

    switch (e_g_nw_setup_state)
    {
    	case NW_SETUP_STATE_NONE_CONN:
		{
			_wzd_nw_conn_lan_or_wifi();
		}
			break;

        case NW_SETUP_STATE_WIRELESS_PWD_INPUT:
        case NW_SETUP_STATE_WIRELESS_SSID_INPUT:
		{
			if (t_wzd_nw.t_choice_connect.ui1_visiable_ap_num <= 0)
			{
				_wzd_nw_conn_lan_or_wifi();
			}
			else
			{
				_wzd_nw_go(NW_SETUP_STATE_WIRELESS_SCAN_RESULT, TRUE);
			}
		}
			break;

        case NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE:
        {
			_wzd_nw_conn_lan_or_wifi();
        }
            break;

		case NW_SETUP_STATE_PROTOCOL:
        {
			if (WZD_NW_PROTOCOL_SCAN_NULL != t_wzd_nw.t_protocol.e_scan_text)
			{
				_wzd_nw_protocol_text_show_exit_scan();
			}
			else
			{
			    a_nw_get_ethernet_connect_info(&b_wired_plug);
				if (b_wired_plug)
				{
					/* update sub page id */
					wzd_set_subpage_id(WZD_NW_PAGE_ID | NW_SETUP_STATE_BEGIN);

					if (a_wzd_is_resume_from_menu_setup())
					{
						_wzd_nw_leave_this_page();
					}
					else
					{
		            	wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
					}
				}
				else
				{
					_wzd_nw_conn_lan_or_wifi();
				}
			}
        }
            break;

		case NW_SETUP_STATE_INFO_REG:
        {
            if ((i1_tos_is_accept != 1) &&
				(a_tv_custom_get_tos() == FALSE ||a_tv_custom_get_privacy() == FALSE))
		    {
		        _wzd_nw_go(NW_SETUP_STATE_PROTOCOL, TRUE);
		    }
		    else
		    {
			    a_nw_get_ethernet_connect_info(&b_wired_plug);
				if (b_wired_plug)
				{
					/* update sub page id */
					wzd_set_subpage_id(WZD_NW_PAGE_ID | NW_SETUP_STATE_BEGIN);

					if (a_wzd_is_resume_from_menu_setup())
					{
						_wzd_nw_leave_this_page();
					}
					else
					{
		            	wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
					}
				}
				else
				{
					_wzd_nw_conn_lan_or_wifi();
				}
			}
        }
            break;

        case NW_SETUP_STATE_WIRELESS_SCAN_RESULT:
        {
			if (a_wzd_is_resume_from_menu_setup())
			{
				_wzd_nw_leave_this_page();
			}
			else
			{
            	wzd_page_goto(WZD_PAGE_NAVI_PREV_PAGE);
			}
        }
            break;

        default:
            break;
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_network_set_resume_page
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wzd_network_set_resume_page(VOID)
{
    switch (e_g_nw_setup_state)
    {
		case NW_SETUP_STATE_BEGIN:
		case NW_SETUP_STATE_NONE_CONN:
        case NW_SETUP_STATE_WIRELESS_SCANNING:
		case NW_SETUP_STATE_WIRELESS_SCAN_RESULT:
        case NW_SETUP_STATE_WIRELESS_PWD_INPUT:
		case NW_SETUP_STATE_WIRELESS_SSID_INPUT:
		case NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT:
		case NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE:
        {
            wzd_set_subpage_id(WZD_NW_PAGE_ID | NW_SETUP_STATE_BEGIN);
        }
        break;

		case NW_SETUP_STATE_PROTOCOL:
        {
            wzd_set_subpage_id(WZD_NW_PAGE_ID | NW_SETUP_STATE_PROTOCOL);
        }
        break;

        case NW_SETUP_STATE_INFO_REG:
        {
            UINT8   ui1_reg_info = 0;

            a_cfg_cust_get_cust_nw_register_status(&ui1_reg_info);

            if (ui1_reg_info == 0)
            {
                wzd_set_subpage_id(WZD_NW_PAGE_ID | NW_SETUP_STATE_INFO_REG);
            }
            else
            {
                wzd_set_subpage_id(WZD_NW_PAGE_ID | NW_SETUP_STATE_BEGIN);
            }
        }
        break;

        default:
            break;
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_network_get_resume_page
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 _wzd_network_get_resume_page(UINT8* p_ui1_page_id)
{
    UINT8 ui1_page_id;
    RET_ON_ERR (wzd_get_subpage_id(&ui1_page_id));
    if(WZD_NW_PAGE_ID == (ui1_page_id & 0xf0))
    {
        *p_ui1_page_id = ui1_page_id & 0x0f;
    }
    else
    {
        *p_ui1_page_id = 0;
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_go
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_go(NW_SETUP_STATE e_nw_setup_state, BOOL b_repaint)
{
    INT32       				i4_ret = WZDR_OK;
    UINT8       				ui1_loop = 0;
	HANDLE_T                    h_layout_frm = NULL_HANDLE;
	GL_RECT_T           		t_rect = {0};
	ISO_639_LANG_T 				s639_lang;

	/* same state */
	if (e_g_nw_setup_state != e_nw_setup_state)
	{
		/* save network setup state */
		e_g_nw_setup_pre_state = e_g_nw_setup_state;
		e_g_nw_setup_state = e_nw_setup_state;
	}

	t_wzd_nw.b_is_busying = FALSE;
    t_wzd_nw.ui2_lang_id = wzd_get_lang_id();

    RET_ON_ERR (wzd_view_get_layout_frm(&h_layout_frm));

	RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_HIDE_RECURSIVE));
    RET_ON_ERR (c_wgl_set_visibility (h_layout_frm, WGL_SW_NORMAL));

	/* update footer by state */
	SHOW_ON_ERR (_wzd_nw_help_lst_update(e_nw_setup_state, FALSE));

    switch(e_nw_setup_state)
    {
    case NW_SETUP_STATE_BEGIN:
	{
		i4_ret = wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_TITLE_NETWORK_SETUP), NULL_HANDLE);
        RET_ON_ERR(i4_ret);

		/* hide select box */
		RET_ON_ERR (wzd_view_sel_box_show(FALSE));
	}
		break;

    case NW_SETUP_STATE_WIRELESS_SCANNING:
	{
		/* hide full screen dialog first */
		if (wzd_view_full_screen_dlg_is_show())
		{
			wzd_view_full_screen_dlg_hide();
		}

		i4_ret = wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_TITLE_NETWORK_SETUP), NULL_HANDLE);
        RET_ON_ERR(i4_ret);

		i4_ret = _wzd_page_nw_setup_create_sel_box();
		RET_ON_ERR(i4_ret);

    	i4_ret = wzd_view_sel_box_show(TRUE);
		RET_ON_ERR(i4_ret);

		/* Set focus to footer skip button. */
		i4_ret = wzd_view_footer_set_focus(WZD_FOOTER_BTN_02, FALSE);
        RET_ON_ERR(i4_ret);
	}
		break;

	case NW_SETUP_STATE_WIRELESS_SCAN_RESULT:
	{
		i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_HIDE);
    	RET_ON_ERR(i4_ret);

		i4_ret = wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_TITLE_NETWORK_SETUP), NULL_HANDLE);
        RET_ON_ERR(i4_ret);

		i4_ret = _wzd_nw_mac_addr_update();
        RET_ON_ERR(i4_ret);

		i4_ret = _wzd_page_nw_setup_create_sel_box();
		RET_ON_ERR(i4_ret);

    	i4_ret = wzd_view_sel_box_show(TRUE);
		RET_ON_ERR(i4_ret);

		i4_ret = wzd_view_sel_box_set_focus(WZD_SEL_BOX_BTN_01, FALSE);
		RET_ON_ERR(i4_ret);
	}
		break;

    case NW_SETUP_STATE_WIRELESS_WPS_ASSOCIATE:
    {
		i4_ret = wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_TITLE_NETWORK_SETUP), NULL_HANDLE);
        RET_ON_ERR(i4_ret);

		/* update wps connect info */
		i4_ret = c_wgl_do_cmd (t_wzd_nw.t_none_conn.t_title.h_widget,
						WGL_CMD_TEXT_SET_TEXT,
						WGL_PACK (WZD_TEXT(MLM_WZD_KEY_NW_SETUP_WPS_CONN)),
						WGL_PACK ((UINT16)0xFFFF));
		RET_ON_ERR(i4_ret);

		i4_ret = c_wgl_do_cmd (t_wzd_nw.t_none_conn.t_desc_txt.h_widget,
						WGL_CMD_TEXT_SET_TEXT,
						WGL_PACK (WZD_TEXT(MLM_WZD_KEY_NW_SETUP_WPS_CONN_DESC)),
						WGL_PACK ((UINT16)0xFFFF));
		RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_set_visibility(t_wzd_nw.t_none_conn.h_none_conn_frame, WGL_SW_RECURSIVE);
        RET_ON_ERR(i4_ret);

		/* Set focus to cancel button. */
        i4_ret = wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE);
        RET_ON_ERR(i4_ret);

		/* update footer by state */
		SHOW_ON_ERR (_wzd_nw_help_lst_update(e_nw_setup_state, FALSE));
    }
        break;

	case NW_SETUP_STATE_NONE_CONN:
    {
		/* hide full screen dialog first */
		if (wzd_view_full_screen_dlg_is_show())
		{
			wzd_view_full_screen_dlg_hide();
		}

	#if 0
		i4_ret = _wzd_page_nw_setup_create_sel_box();
		RET_ON_ERR(i4_ret);

    	i4_ret = wzd_view_sel_box_show(TRUE);
		RET_ON_ERR(i4_ret);
	#else
		/* hide select box */
		RET_ON_ERR (wzd_view_sel_box_show(FALSE));

		i4_ret = c_wgl_do_cmd (t_wzd_nw.t_none_conn.t_title.h_widget,
						WGL_CMD_TEXT_SET_TEXT,
						WGL_PACK (WZD_TEXT(MLM_WZD_KEY_NW_SETUP_NO_NETWORK_FOUND)),
						WGL_PACK ((UINT16)0xFFFF));
		RET_ON_ERR(i4_ret);

		i4_ret = c_wgl_do_cmd (t_wzd_nw.t_none_conn.t_desc_txt.h_widget,
						WGL_CMD_TEXT_SET_TEXT,
						WGL_PACK (WZD_TEXT(MLM_WZD_KEY_EMPTY)),
						WGL_PACK ((UINT16)0xFFFF));
		RET_ON_ERR(i4_ret);

        i4_ret = c_wgl_set_visibility(t_wzd_nw.t_none_conn.h_none_conn_frame, WGL_SW_RECURSIVE);
        RET_ON_ERR(i4_ret);
	#endif

		/* Set focus to try again btn. */
        i4_ret = wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE);
        RET_ON_ERR(i4_ret);
    }
        break;

	case NW_SETUP_STATE_WIRELESS_PWD_INPUT:
    {
		c_memset(&t_wzd_nw.aw2s_key_context, 0, sizeof(t_wzd_nw.aw2s_key_context));

		UTF16_T     			w2s_ssid [WZD_NW_SSID_MAX_LEN+1] = {0};
	    NET_802_11_ASSOCIATE_T*	pt_associate = NULL;

		/* hide full screen dialog first */
		if (wzd_view_full_screen_dlg_is_show())
		{
			wzd_view_full_screen_dlg_hide();
		}

		if (NW_SETUP_STATE_WIRELESS_SSID_INPUT == e_g_nw_setup_pre_state)
		{
			RET_ON_ERR(wzd_view_title_txt_set_text_ex(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_PW_INPUT), t_wzd_nw.aw2s_ssid_context));
		}
		else
		{
			/* get associate ap information */
			i4_ret = _wzd_nw_get_associate_data(&pt_associate);
		    RET_ON_ERR(i4_ret);

		    if(pt_associate == NULL)
		    {
		        return WZDR_OK;
		    }

			if (pt_associate->t_Ssid.ui4_SsidLen <= 0 && c_uc_w2s_strlen(t_wzd_nw.aw2s_ssid_context) > 0)
			{
				RET_ON_ERR(wzd_view_title_txt_set_text_ex(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_PW_INPUT), t_wzd_nw.aw2s_ssid_context));
			}
			else
			{
			    c_uc_ps_to_w2s(pt_associate->t_Ssid.ui1_aSsid, w2s_ssid, pt_associate->t_Ssid.ui4_SsidLen);
			    w2s_ssid[pt_associate->t_Ssid.ui4_SsidLen]= (UTF16_T)0;

				RET_ON_ERR(wzd_view_title_txt_set_text_ex(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_PW_INPUT), w2s_ssid));
			}
		}
		RET_ON_ERR(c_wgl_set_visibility(t_wzd_nw.t_eb_pwd.h_eb_frm, WGL_SW_NORMAL));
		RET_ON_ERR(c_wgl_set_visibility(t_wzd_nw.t_eb_pwd.h_eb_focus, WGL_SW_NORMAL));

		/* hide select box first */
		wzd_view_sel_box_show(FALSE);

		/* show float prompt */
		t_wzd_nw.b_need_show_prompt_text = TRUE;
		_wzd_nw_float_prompt_set_text(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_PROMPT_PW_INPUT));
		_wzd_nw_float_prompt_show();

		_wzd_nw_vkb_show (NULL_HANDLE, WZD_NW_VKB_PWD_INPUT);

		a_vkb_set_focus(t_wzd_nw.t_vkb.h_vkb_pwd);
		a_vkb_set_focus_ex(t_wzd_nw.t_vkb.h_vkb_pwd);

		RET_ON_ERR(c_wgl_set_visibility(t_wzd_nw.t_eb_pwd.h_eb_clr, WGL_SW_NORMAL));
		c_wgl_float(t_wzd_nw.t_eb_pwd.h_eb_clr, TRUE, FALSE);

		/* update footer by state */
		SHOW_ON_ERR (_wzd_nw_help_lst_update(e_nw_setup_state, FALSE));
    }
        break;

	case NW_SETUP_STATE_WIRELESS_SSID_INPUT:
    {
		i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_HIDE);
    	RET_ON_ERR(i4_ret);

		RET_ON_ERR(wzd_view_title_txt_set_text(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_SSID_INPUT)));
		RET_ON_ERR(c_wgl_set_visibility(t_wzd_nw.t_eb_ssid.h_eb_frm, WGL_SW_NORMAL));
		RET_ON_ERR(c_wgl_set_visibility(t_wzd_nw.t_eb_ssid.h_eb_focus, WGL_SW_NORMAL));

		c_memset(&t_wzd_nw.aw2s_ssid_context, 0, sizeof(t_wzd_nw.aw2s_ssid_context));

		/* hide select box first */
		wzd_view_sel_box_show(FALSE);

		/* show float prompt */
		t_wzd_nw.b_need_show_prompt_text = TRUE;
		_wzd_nw_float_prompt_set_text(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_PROMPT_SSID_INPUT));
		_wzd_nw_float_prompt_show();

		_wzd_nw_vkb_show (NULL_HANDLE, WZD_NW_VKB_MANU_SSID);

		a_vkb_set_focus(t_wzd_nw.t_vkb.h_vkb_ssid);
		a_vkb_set_focus_ex(t_wzd_nw.t_vkb.h_vkb_ssid);

		RET_ON_ERR(c_wgl_set_visibility(t_wzd_nw.t_eb_ssid.h_eb_clr, WGL_SW_NORMAL));
		c_wgl_float(t_wzd_nw.t_eb_ssid.h_eb_clr, TRUE, FALSE);

		/* update footer by state */
		SHOW_ON_ERR (_wzd_nw_help_lst_update(e_nw_setup_state, FALSE));
    }
        break;

	case NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT:
    {
		i4_ret = _wzd_page_nw_setup_create_sel_box();
		RET_ON_ERR(i4_ret);

    	i4_ret = wzd_view_sel_box_show(TRUE);
		RET_ON_ERR(i4_ret);

		i4_ret = wzd_view_sel_box_set_focus(WZD_SEL_BOX_BTN_01, FALSE);
		RET_ON_ERR(i4_ret);
    }
        break;

	case NW_SETUP_STATE_PROTOCOL:
    {
		/* hide select box */
		RET_ON_ERR (wzd_view_sel_box_show(FALSE));

		RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_TITLE_TOS_AND_POLICY), NULL_HANDLE));

		c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame, WGL_SW_HIDE_RECURSIVE);
		c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame, WGL_SW_NORMAL);

		/* update multi-language text */
		RET_ON_ERR (c_wgl_do_cmd(
						t_wzd_nw.t_protocol.t_protocol_terms.h_widget,
						WGL_CMD_BTN_SET_TEXT,
						WGL_PACK(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_BTN_TOS)),
						WGL_PACK((UINT16)0xFFFF)));

		RET_ON_ERR (c_wgl_do_cmd(
						t_wzd_nw.t_protocol.t_protocol_policy.h_widget,
						WGL_CMD_BTN_SET_TEXT,
						WGL_PACK(WZD_TEXT(MLM_WZD_KEY_NW_SETUP_BTN_POLICY)),
						WGL_PACK((UINT16)0xFFFF)));

		c_wgl_set_visibility(t_wzd_nw.t_protocol.t_protocol_terms.h_widget, WGL_SW_NORMAL);
		c_wgl_set_visibility(t_wzd_nw.t_protocol.t_protocol_policy.h_widget, WGL_SW_NORMAL);

        t_wzd_nw.t_protocol.e_scan_text = WZD_NW_PROTOCOL_SCAN_NULL;

		/* set focus to "I accept" button */
		RET_ON_ERR (wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE));
    }
        break;

	case NW_SETUP_STATE_INFO_REG:
    {
        UTF16_T             w2s_text[WZD_NW_EB_TXT_MAX_LEN + 1] = {0};
        WGL_IMG_INFO_T		t_img_info;

		RET_ON_ERR (wzd_view_title_set_htxt(WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_TITLE), NULL_HANDLE));

		/* hide select box */
		RET_ON_ERR (wzd_view_sel_box_show(FALSE));

        i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_info_reg_frm, WGL_SW_RECURSIVE);
        RET_ON_ERR(i4_ret);

		/* Set background images */
	    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
	    t_img_info.e_type = WGL_IMG_SET_STANDARD;
	    t_img_info.u_img_data.t_standard.t_enable       = h_g_wzd_img_textBox_register;
	    t_img_info.u_img_data.t_standard.t_highlight	= h_g_wzd_img_textBox_register_highlight;

	    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
	                          WGL_CMD_GL_SET_IMAGE,
	                          WGL_PACK(WGL_IMG_BK),
	                          WGL_PACK(&t_img_info));
		RET_ON_ERR(i4_ret);

		/* Set icon before the editbox */
		c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
	    t_img_info.e_type = WGL_IMG_SET_EXTEND;
	    t_img_info.u_img_data.t_extend.t_enable             = NULL_HANDLE;
	    t_img_info.u_img_data.t_extend.t_highlight          = h_g_wzd_img_text_focus;
	    i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[t_wzd_nw.t_info_reg.e_current_item],
	                          WGL_CMD_BDR_TIMG_SET_ICON,
	                          WGL_PACK(&t_img_info),
	                          WGL_PACK(NULL) );
	    RET_ON_ERR(i4_ret);

        i4_ret = _wzd_nw_reg_info_float_prompt_set_text();
		RET_ON_ERR(i4_ret);
		i4_ret = _wzd_nw_reg_info_float_prompt_show_all_item();
		RET_ON_ERR(i4_ret);

        for(ui1_loop = WZD_NW_REG_INFO_MAIL; ui1_loop < WZD_NW_REG_INFO_LAST_ENTRY; ui1_loop++)
        {
            c_memset(w2s_text, 0,
                     sizeof(UTF16_T)*WZD_NW_EB_TXT_MAX_LEN);

            i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.ah_editbox[ui1_loop],
                                  WGL_CMD_EB_GET_TEXT,
                                  WGL_PACK(w2s_text),
                                  WGL_PACK(WZD_NW_EB_TXT_MAX_LEN));
            RET_ON_ERR(i4_ret);

            c_uc_w2s_strncpy(t_wzd_nw.t_info_reg.aw2s_editbox_context[ui1_loop],
                                 w2s_text, WZD_NW_EB_TXT_MAX_LEN);
            RET_ON_ERR(i4_ret);

            i4_ret =  _wzd_nw_reg_info_update_eb_content(ui1_loop);
            DBG_LOG_PRINT(("\n####[wzd_reg_info%s(%d)]\n",__FUNCTION__,__LINE__));
            RET_ON_ERR(i4_ret);
        }

		i4_ret = a_cfg_get_gui_lang(s639_lang);
	    if(i4_ret == APP_CFGR_OK)
	    {
	        if(c_strncmp(s639_lang, s639_app_cfg_lang_spa, ISO_639_LANG_LEN) == 0)
	        {

		        /* move check box's position */
				SET_RECT_BY_SIZE(&t_rect,
								WZD_NW_INFO_REG_EB_LEFT_INSET,
								WZD_NW_EMAIL_CB_Y,
								WZD_NW_INFO_REG_CB_W,
								WZD_NW_INFO_REG_CB_H);
				RET_ON_ERR (c_wgl_move(t_wzd_nw.t_info_reg.h_mail_accept_checkbox,
								&t_rect,
								WGL_NO_AUTO_REPAINT));

				/* move check box's title position */
				SET_RECT_BY_SIZE(&t_rect,
								WZD_NW_INFO_REG_EB_LEFT_INSET+WZD_NW_INFO_REG_CB_W,
								WZD_NW_INFO_REG_CB_TITLE_Y,
								WZD_NW_INFO_REG_CB_TITLE_W,
								WZD_NW_INFO_REG_CB_TITLE_H);
				RET_ON_ERR (c_wgl_move(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title,
								&t_rect,
								WGL_NO_AUTO_REPAINT));

		        /* move check box's title1 position */
				SET_RECT_BY_SIZE(&t_rect,
								WZD_NW_INFO_REG_EB_LEFT_INSET+WZD_NW_INFO_REG_CB_W,
								WZD_NW_INFO_REG_CB_TITLE1_Y,
								WZD_NW_INFO_REG_CB_TITLE1_W,
								WZD_NW_INFO_REG_CB_TITLE1_H);
				RET_ON_ERR (c_wgl_move(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title1,
								&t_rect,
								WGL_NO_AUTO_REPAINT));

	        }
	        else
	        {
		        /* back check box's position */
				SET_RECT_BY_SIZE(&t_rect,
								WZD_NW_EMAIL_CB_X,
								WZD_NW_EMAIL_CB_Y,
								WZD_NW_INFO_REG_CB_W,
								WZD_NW_INFO_REG_CB_H);
				RET_ON_ERR (c_wgl_move(t_wzd_nw.t_info_reg.h_mail_accept_checkbox,
								&t_rect,
								WGL_NO_AUTO_REPAINT));

				/* back check box's title position */
				SET_RECT_BY_SIZE(&t_rect,
								WZD_NW_INFO_REG_CB_TITLE_X,
								WZD_NW_INFO_REG_CB_TITLE_Y,
								WZD_NW_INFO_REG_CB_TITLE_W,
								WZD_NW_INFO_REG_CB_TITLE_H);
				RET_ON_ERR (c_wgl_move(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title,
								&t_rect,
								WGL_NO_AUTO_REPAINT));

		        /* back check box's title1 position */
				SET_RECT_BY_SIZE(&t_rect,
								WZD_NW_INFO_REG_CB_TITLE1_X,
								WZD_NW_INFO_REG_CB_TITLE1_Y,
								WZD_NW_INFO_REG_CB_TITLE1_W,
								WZD_NW_INFO_REG_CB_TITLE1_H);
				RET_ON_ERR (c_wgl_move(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title1,
								&t_rect,
								WGL_NO_AUTO_REPAINT));


	        }
        }
		i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title,
			                  WGL_CMD_TEXT_SET_TEXT,
			                  WGL_PACK(WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_EMAIL_ACCEPT)),
			                  WGL_PACK(c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_EMAIL_ACCEPT))));
		RET_ON_ERR(i4_ret);

		i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.h_mail_accept_checkbox_title1,
			                  WGL_CMD_TEXT_SET_TEXT,
			                  WGL_PACK(WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_WEB_ADDS)),
			                  WGL_PACK(c_uc_w2s_strlen(WZD_TEXT(MLM_WZD_KEY_NETWORK_REG_INFO_WEB_ADDS))));
		RET_ON_ERR(i4_ret);

		i4_ret = c_wgl_do_cmd(t_wzd_nw.t_info_reg.h_mail_accept_checkbox,
                              WGL_CMD_BTN_SET_PUSHED,
                              WGL_PACK(TRUE),
                              NULL);
        RET_ON_ERR(i4_ret);

        t_wzd_nw.t_info_reg.b_is_vkb_show = TRUE;

        _wzd_nw_vkb_show(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL], WZD_NW_VKB_INFO_REG);

        i4_ret = c_wgl_set_focus(t_wzd_nw.t_info_reg.ah_editbox[WZD_NW_REG_INFO_MAIL], FALSE);
        RET_ON_ERR(i4_ret);

		/* update footer by state */
		SHOW_ON_ERR (_wzd_nw_help_lst_update(e_nw_setup_state, FALSE));
    }
        break;

       default :
           break;
    }

    i4_ret = _wzd_network_set_resume_page();
    RET_ON_ERR(i4_ret);

    if(b_repaint)
    {
        i4_ret = wzd_view_main_frm_repaint();
        RET_ON_ERR(i4_ret);
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_partition_ready
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 * Any other values            Failed.
 ----------------------------------------------------------------------------*/
static VOID _wzd_nw_partition_ready (VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
#ifdef APP_DYNAMIC_TOS_SUPPORT
    TOS_TYPE_T      e_tos_type = TOS_TYPE_LAST_VALID_ITEM;

    /* start to download tos */
    if (FALSE == t_wzd_nw.t_protocol.b_is_file_opened &&
        e_g_nw_setup_state == NW_SETUP_STATE_PROTOCOL &&
        WZD_NW_PROTOCOL_SCAN_NULL != t_wzd_nw.t_protocol.e_scan_text)
    {
         /* start to download and open tos file */
        e_tos_type = _wzd_tos_get_type ();

        a_tos_download_util_file(e_tos_type);
    }
#endif

    if(TRUE == b_reg_info_is_store)
    {
        _wzd_nw_reg_info_set();
    }

    /* save tos and privacy flags to 3rd_rw */
	if ((i1_tos_is_accept == 1))
	{
		a_tv_custom_set_tos (TRUE);
		a_tv_custom_set_privacy (TRUE);
		SHOW_ON_ERR(a_tv_custom_set_tos_version());
	}
	else if (i1_tos_is_accept == -1)
	{
		a_tv_custom_set_tos (FALSE);
		a_tv_custom_set_privacy (FALSE);
	}
	else
	{
		/* do nothing */
	}

	return;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nw_fm_partition_status_nfy
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
static INT32 _wzd_nw_fm_partition_status_nfy(
        UINT32             ui4_tag,
        FS_PARTITION_T     e_partition)
{
    if (FS_PARTITION_ALL == e_partition)
    {
        DBG_LOG_PRINT(("[WZD][NW] --- FS_PARTITION_ALL mounted. \n"));
		wzd_request_context_switch(_wzd_nw_partition_ready,
		                           NULL,
		                           NULL,
		                           NULL);
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_network_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_create(VOID)
{
    INT32       i4_ret;
    HANDLE_T    h_parent = NULL_HANDLE;

	i4_ret = c_fm_partition_reg_nfy(_wzd_nw_fm_partition_status_nfy, 0);
    RET_ON_ERR(i4_ret);

    i4_ret = wzd_view_get_layout_frm(&h_parent);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_create(h_parent);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_page_nw_setup_hide(0);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_network_destory
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_destory(VOID)
{
    INT32  i4_ret;

    i4_ret = c_timer_stop(t_wzd_nw.t_choice_connect.h_timer);
    RET_ON_ERR(i4_ret);

    i4_ret = c_timer_delete(t_wzd_nw.t_choice_connect.h_timer);
    RET_ON_ERR(i4_ret);

	i4_ret = c_timer_stop(t_wzd_nw.t_protocol.h_timer);
    RET_ON_ERR(i4_ret);

    i4_ret = c_timer_delete(t_wzd_nw.t_protocol.h_timer);
    RET_ON_ERR(i4_ret);

#ifdef APP_DYNAMIC_TOS_SUPPORT
    if (t_wzd_nw.t_protocol.ui2_tos_nfy_id)
    {
        i4_ret = a_icl_notify_unreg(t_wzd_nw.t_protocol.ui2_tos_nfy_id);
        RET_ON_ERR(i4_ret);

        t_wzd_nw.t_protocol.ui2_tos_nfy_id = 0;
    }
#endif

    i4_ret = a_nw_unregister(t_wzd_nw.t_choice_connect.ui4_wzd_nw_nfy_id);
    RET_ON_ERR(i4_ret);

    /*close file handle*/
    i4_ret = _wzd_nw_protocol_text_show_close(&t_wzd_nw.t_protocol.t_protocol_terms.h_text);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_protocol_text_show_close(&t_wzd_nw.t_protocol.t_protocol_policy.h_text);
    RET_ON_ERR(i4_ret);

    b_nw_ready_to_show = FALSE;

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_network_show
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_show(UINT32 ui4_sub_page_id)
{
    UINT16  ui2_status;
    UINT8   ui1_page = NW_SETUP_STATE_BEGIN;

    b_nw_ready_to_show = TRUE;

	RET_ON_ERR (a_cfg_get_wzd_status (&ui2_status));
    ui2_status = WZD_UTIL_GET_STATUS_STATE(ui2_status);

	if (ui2_status == 0xFFFF ||
        ui2_status == APP_CFG_WZD_STATUS_INIT ||
        ui2_status == WZD_STATE_START_SETUP)
    {

	    RET_ON_ERR (_wzd_network_get_resume_page(&ui1_page));

	    if (NW_SETUP_STATE_PROTOCOL == ui1_page)
	    {
	        RET_ON_ERR(_wzd_nw_go(NW_SETUP_STATE_PROTOCOL, FALSE));
	    }
	    /*
	    else if(NW_SETUP_STATE_INFO_REG == ui1_page)
	    {
	        RET_ON_ERR(_wzd_nw_go(NW_SETUP_STATE_INFO_REG, b_repaint));
	    }
	    */
	    else
	    {
	    	RET_ON_ERR(_wzd_nw_conn_lan_or_wifi());
	    }
	}
	else
	{
		RET_ON_ERR(_wzd_nw_conn_lan_or_wifi());
	}

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_hide(UINT32 ui4_sub_page_id)
{
    INT32  i4_ret;

#ifdef WZD_NW_TEST_CONNECTION
	if (ui4_g_wzd_test_connection_nfy_id)
    {
        i4_ret = a_nw_unregister(ui4_g_wzd_test_connection_nfy_id);
        RET_ON_ERR(i4_ret);
        ui4_g_wzd_test_connection_nfy_id = 0;
    }
#endif

 #ifdef APP_DYNAMIC_TOS_SUPPORT
    i4_ret = _wzd_nw_protocol_error_msg_hide();
    RET_ON_ERR(i4_ret);
#endif

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_protocol.h_protocol_frame, WGL_SW_HIDE_RECURSIVE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_none_conn.h_none_conn_frame, WGL_SW_HIDE_RECURSIVE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_info_reg.h_info_reg_frm, WGL_SW_HIDE_RECURSIVE);
    RET_ON_ERR(i4_ret);

	i4_ret = c_wgl_set_visibility(t_wzd_nw.t_eb_pwd.h_eb_frm, WGL_SW_HIDE_RECURSIVE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.t_eb_ssid.h_eb_frm, WGL_SW_HIDE_RECURSIVE);
    RET_ON_ERR(i4_ret);

    i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_info, FALSE);
    RET_ON_ERR(i4_ret);

    i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_pwd, FALSE);
    RET_ON_ERR(i4_ret);

	i4_ret = a_vkb_set_visibility(t_wzd_nw.t_vkb.h_vkb_ssid, FALSE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(t_wzd_nw.h_timer_icon, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);

    /*close file handle*/
    i4_ret = _wzd_nw_protocol_text_show_close(&t_wzd_nw.t_protocol.t_protocol_terms.h_text);
    RET_ON_ERR(i4_ret);

    i4_ret = _wzd_nw_protocol_text_show_close(&t_wzd_nw.t_protocol.t_protocol_policy.h_text);
    RET_ON_ERR(i4_ret);

    b_nw_ready_to_show = FALSE;

    return WZDR_OK;
}

static INT32 _wzd_page_nw_setup_sb_btn_img(
					UINT8 			ui1_btn,
					UINT32 			ui4_idx,
					WGL_HIMG_TPL_T	t_img_tpl)
{
	WGL_IMG_INFO_T              t_img_info;
	HANDLE_T 					h_sb_icon = NULL_HANDLE;

	t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable 	= t_img_tpl;
    t_img_info.u_img_data.t_standard.t_enable = t_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = t_img_tpl;

	if (1 == ui1_btn)
	{
		h_sb_icon = wzd_view_sel_box_get_icon_1_handle(ui4_idx);
	}
	else
	{
		h_sb_icon = wzd_view_sel_box_get_icon_2_handle(ui4_idx);
	}

	RET_ON_ERR (c_wgl_do_cmd (h_sb_icon,
							  WGL_CMD_GL_SET_IMAGE,
	                          WGL_PACK(WGL_IMG_FG),
	                          WGL_PACK(&t_img_info)));

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_nw_add_ap_list_by_idx
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nw_add_ap_list_by_idx(
							UINT32							ui4_sb_idx,
                            NET_802_11_SSID_T*              pt_Ssid,
                            INT16                           i2_Level,
                            NET_802_11_AUTH_MODE_T          e_AuthMode,
                            NET_802_11_AUTH_CIPHER_T        e_AuthCipher)
{
    UTF16_T         w2s_ssid[WZD_NW_SSID_MAX_LEN+1] = {0};
    INT16           i2_new_level = 0;

	BOOL 			b_lock = FALSE;
	WGL_HIMG_TPL_T	h_nw_lock = NULL_HANDLE;

	WGL_HIMG_TPL_T	h_signal_icon = NULL_HANDLE;
    WGL_HIMG_TPL_T  at_img_signal_icon[5] =
    {
        h_g_wzd_signal_1of5_bits,
        h_g_wzd_signal_2of5_bits,
        h_g_wzd_signal_3of5_bits,
        h_g_wzd_signal_4of5_bits,
        h_g_wzd_signal_5of5_bits
    };

	/* get ap information */
    c_uc_ps_to_w2s(pt_Ssid->ui1_aSsid, w2s_ssid, pt_Ssid->ui4_SsidLen);
    w2s_ssid[pt_Ssid->ui4_SsidLen]= (UTF16_T)0;

	b_lock = _wzd_nw_is_lock_ap(e_AuthMode, e_AuthCipher);
	h_nw_lock = b_lock? h_g_wzd_img_network_lock : NULL_HANDLE;

    i2_new_level = a_nw_custom_wifi_signal_remapping(i2_Level);

	if((UINT16)i2_new_level > 80)
    {
        h_signal_icon = at_img_signal_icon[4];
    }
    else if((UINT16)i2_new_level <= 20)
    {
        h_signal_icon = at_img_signal_icon[0];
    }
    else
    {
        h_signal_icon = at_img_signal_icon[(((UINT16)(i2_new_level -1)) /20)%5];
    }

	/* set wifi ap name */
	wzd_view_sel_box_set_text (ui4_sb_idx, w2s_ssid);

	/* set lock icon */
	_wzd_page_nw_setup_sb_btn_img (1, ui4_sb_idx, h_nw_lock);

	/* set signal icon */
	_wzd_page_nw_setup_sb_btn_img (2, ui4_sb_idx, h_signal_icon);


    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_sel_box_left_shift
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx		Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_sel_box_left_shift (const UINT32 ui4_btn_idx)
{
	NET_802_11_ESS_INFO_T*		p_essInfo = NULL;
	UINT8						ui1_loop = 0;
	UINT16				   		ui2_mlm_offset = MLM_WZD_KEY_NW_SECURE_NONE;

	if (NW_SETUP_STATE_WIRELESS_SCANNING == e_g_nw_setup_state)
	{
		/* do nothing */
		return WZDR_OK;
	}
	else if (NW_SETUP_STATE_WIRELESS_SCAN_RESULT == e_g_nw_setup_state)
	{
		/* update all select box button */
		for( ui1_loop = 0; ui1_loop < WZD_SEL_BOX_BTN_COUNT ; ui1_loop++ )
		{
			/* get visiable ap by index */
			p_essInfo = _wzd_nw_get_ap_by_idx((UINT16)(ui4_btn_idx + ui1_loop - 3));
            if(p_essInfo == NULL)
            {
                return WZDR_OK;
            }

			_wzd_nw_add_ap_list_by_idx(ui4_btn_idx + ui1_loop - 3,
									  &p_essInfo->t_Ssid,
									  p_essInfo->i2_Level,
									  p_essInfo->e_AuthMode,
									  p_essInfo->e_AuthCipher);
		}
	}
	else if (NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT == e_g_nw_setup_state)
	{
		/* update all select box button */
		for( ui1_loop = 0; ui1_loop < WZD_SEL_BOX_BTN_COUNT ; ui1_loop++ )
		{
			/* Set encryption by index */
			wzd_view_sel_box_set_text (ui4_btn_idx + ui1_loop,
									  WZD_TEXT(ui2_mlm_offset + ui4_btn_idx + ui1_loop));

		}
	}
	else
	{
		/* do something */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_sel_box_right_shift
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx		Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_sel_box_right_shift (const UINT32 ui4_btn_idx)
{
	NET_802_11_ESS_INFO_T*		p_essInfo = NULL;
	UINT8						ui1_loop = 0;
	UINT16				   		ui2_mlm_offset = MLM_WZD_KEY_NW_SECURE_NONE;

	if (NW_SETUP_STATE_WIRELESS_SCANNING == e_g_nw_setup_state)
	{
		/* do nothing */
		return WZDR_OK;
	}
	else if (NW_SETUP_STATE_WIRELESS_SCAN_RESULT == e_g_nw_setup_state)
	{
		/* update all select box button */
		for( ui1_loop = 0; ui1_loop < WZD_SEL_BOX_BTN_COUNT ; ui1_loop++ )
		{
			/* get visiable ap by index */
			p_essInfo = _wzd_nw_get_ap_by_idx((UINT16)(ui4_btn_idx + ui1_loop - 3));
            if(p_essInfo == NULL)
            {
                return WZDR_OK;
            }

			_wzd_nw_add_ap_list_by_idx(ui4_btn_idx + ui1_loop - 3,
									  &p_essInfo->t_Ssid,
									  p_essInfo->i2_Level,
									  p_essInfo->e_AuthMode,
									  p_essInfo->e_AuthCipher);
		}
	}
	else if (NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT == e_g_nw_setup_state)
	{
		/* update all select box button */
		for( ui1_loop = 0; ui1_loop < WZD_SEL_BOX_BTN_COUNT ; ui1_loop++ )
		{
			/* Set encryption by index */
			wzd_view_sel_box_set_text (ui4_btn_idx - ui1_loop,
									  WZD_TEXT(ui2_mlm_offset + ui4_btn_idx - ui1_loop));
		}
	}
	else
	{
		/* do something */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_sel_box_btn_select
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx		Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_sel_box_btn_select (const UINT32 ui4_btn_idx)
{
	INT32  						i4_ret = WZDR_OK;
	NET_802_11_ESS_INFO_T*		p_essInfo = NULL;
	NET_802_11_ASSOCIATE_T* 	pt_associate = NULL;
	NET_802_11_BSS_INFO_T       t_CurrBss;
	WZD_SEL_BOX_BTN_INDEX_T 	    e_sb_idx = WZD_SEL_BOX_BTN_COUNT;

	if (NW_SETUP_STATE_WIRELESS_SCANNING == e_g_nw_setup_state)
	{
		/* do nothing */
		return WZDR_OK;
	}
	else if (NW_SETUP_STATE_WIRELESS_SCAN_RESULT == e_g_nw_setup_state)
	{
		if((UINT8)ui4_btn_idx > t_wzd_nw.t_choice_connect.ui1_visiable_ap_num)
        {
            return WZDR_FAIL;
        }

        p_essInfo = _wzd_nw_get_ap_by_idx((UINT16)ui4_btn_idx);
        if(p_essInfo == NULL)
        {
            return WZDR_FAIL;
        }

		i4_ret = _wzd_nw_get_associate_data(&pt_associate);
        RET_ON_ERR(i4_ret);

        c_memset(pt_associate, 0, sizeof(NET_802_11_ASSOCIATE_T));
        pt_associate->t_Ssid = p_essInfo->t_Ssid;
        c_memcpy(pt_associate->t_Bssid, p_essInfo->t_Bssid, sizeof(NET_802_11_BSSID_T));

        pt_associate->e_AuthMode  = p_essInfo->e_AuthMode;
        pt_associate->e_AuthCipher= p_essInfo->e_AuthCipher;
        pt_associate->t_Key.b_IsAscii = FALSE;

		/* only the 1st box can be connected */
		e_sb_idx = wzd_view_sel_box_get_btn_idx(ui4_btn_idx);
		if (WZD_SEL_BOX_BTN_01 == e_sb_idx)
		{
			/* is current connected SSID */
			c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
		    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
		    if(i4_ret != NWR_OK)
		    {
		        c_memset(t_CurrBss.t_Bssid, 0, sizeof(t_CurrBss.t_Bssid));
		        t_CurrBss.t_Ssid.ui4_SsidLen = 0;
		    }

			/* current AP be connected, show associate result directly */
			if ((t_CurrBss.t_Ssid.ui4_SsidLen > 0)
		        &&((UINT8)WLAN_WPA_COMPLETED == t_CurrBss.u8_wpa_status))
			{
		        if ((0 == c_strncmp(p_essInfo->t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen))
		            &&(p_essInfo->t_Ssid.ui4_SsidLen == t_CurrBss.t_Ssid.ui4_SsidLen))
		        {
		        #if 0
		        	return _wzd_nw_wifi_assoc_result();
				#else
					return _wzd_nw_test_connection();
				#endif
		        }
		    }
		}

        if (FALSE == _wzd_nw_is_lock_ap(pt_associate->e_AuthMode,pt_associate->e_AuthCipher))
        {
        	DBG_LOG_PRINT(("[WZD][NW] --- %s %d, start WLAN associate.\n", __FUNCTION__,__LINE__));
			i4_ret = a_nw_custom_wlan_disassociate();
			RET_ON_ERR(i4_ret);

            i4_ret = a_nw_wlan_associate(pt_associate);
            RET_ON_ERR(i4_ret);

            t_wzd_nw.b_is_busying = TRUE;
            t_wzd_nw.b_timer_result = FALSE;
            t_wzd_nw.ui4_start_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();

			/* store focused handle */
        	c_wgl_get_focus( &t_wzd_nw.h_last_focused_wdg );

			RET_ON_ERR (_wzd_nw_full_screen_icon_update(FALSE));

			RET_ON_ERR (wzd_view_full_screen_dlg_set_text (
							WZD_TEXT(MLM_WZD_KEY_NW_SETUP_CONNECTING_NETWORK),
							FALSE));

			RET_ON_ERR (wzd_view_full_screen_dlg_show(FALSE));

            t_wzd_nw.e_wzd_nw_timer = WZD_NW_TIMER_WIFI_ASSOC;
            _wzd_nw_timer_start(&t_wzd_nw.e_wzd_nw_timer, 0);
        }
        else
        {
            i4_ret = _wzd_nw_go(NW_SETUP_STATE_WIRELESS_PWD_INPUT, TRUE);
            RET_ON_ERR(i4_ret);
        }
	}
	else if (NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT == e_g_nw_setup_state)
	{
		if (ui4_btn_idx == 0)
		{
			DBG_LOG_PRINT(("[WZD][NW] --- %s %d, Select NONE.\n", __FUNCTION__,__LINE__));
		}
		else
		{
			DBG_LOG_PRINT(("[WZD][NW] --- %s %d, Select other ENCRYPTION.\n", __FUNCTION__,__LINE__));
		}
	}
	else
	{
		/* do something */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_sel_box_initial_theme
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx		Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_sel_box_initial_theme (const UINT32 ui4_btn_idx)
{
	HANDLE_T 					h_sb_txt = NULL_HANDLE;
	HANDLE_T 					h_sb_icon_1st = NULL_HANDLE;
	HANDLE_T 					h_sb_icon_2nd = NULL_HANDLE;
	GL_RECT_T           		t_rect = {0};
	WGL_COLOR_INFO_T  			t_color_txt;
	WGL_FONT_INFO_T    			t_fnt_info;
	WZD_SEL_BOX_BTN_INDEX_T 	e_sb_idx = WZD_SEL_BOX_BTN_COUNT;

	if (NW_SETUP_STATE_WIRELESS_SCANNING == e_g_nw_setup_state)
	{
		/*
			text theme
		*/
		h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						WZD_SEL_BOX_BTN_TXT_X,
						WZD_SEL_BOX_BTN_TXT_Y - (60 * WZD_UI_RATIO_W),
						WZD_SEL_BOX_BTN_TXT_W,
						WZD_SEL_BOX_BTN_TXT_H);
		RET_ON_ERR (c_wgl_move(h_sb_txt,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		/* set alignment */
    	RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_ALIGN,
						WGL_PACK(WGL_AS_CENTER_TOP),
						NULL));

		/* update color */
		t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_COLOR,
						WGL_PACK (WGL_CLR_TEXT),
						WGL_PACK (&t_color_txt)));

		/* update font size */
	    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

	    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_FONT,
						WGL_PACK (&t_fnt_info),
						NULL));
	}
	else if (NW_SETUP_STATE_NONE_CONN == e_g_nw_setup_state)
	{
		/*
			text theme
		*/
		h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						WZD_SEL_BOX_BTN_TXT_X,
						WZD_SEL_BOX_BTN_TXT_Y,
						WZD_SEL_BOX_BTN_TXT_W,
						WZD_SEL_BOX_BTN_TXT_H);
		RET_ON_ERR (c_wgl_move(h_sb_txt,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		/* set alignment */
    	RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_ALIGN,
						WGL_PACK(WGL_AS_CENTER_TOP),
						NULL));

		/* update color */
		t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_COLOR,
						WGL_PACK (WGL_CLR_TEXT),
						WGL_PACK (&t_color_txt)));

		/* update font size */
	    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

	    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_FONT,
						WGL_PACK (&t_fnt_info),
						NULL));

		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						WZD_SEL_BOX_BTN_ICON_2_X,
						WZD_SEL_BOX_BTN_ICON_2_Y,
						WZD_SEL_BOX_BTN_ICON_2_W,
						WZD_SEL_BOX_BTN_ICON_2_H);
		RET_ON_ERR (c_wgl_move(h_sb_icon_2nd,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		RET_ON_ERR (c_wgl_do_cmd(h_sb_icon_2nd,
							  WGL_CMD_ICON_SET_ALIGN,
							  WGL_PACK(WGL_AS_CENTER_CENTER),
							  NULL));
	}
	else if (NW_SETUP_STATE_WIRELESS_SCAN_RESULT == e_g_nw_setup_state)
	{
		/*
			text theme
		*/
		h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						WZD_SEL_BOX_BTN_TXT_X,
						WZD_SEL_BOX_BTN_TXT_Y - (30 * WZD_UI_RATIO_W),
						WZD_SEL_BOX_BTN_TXT_W,
						WZD_SEL_BOX_BTN_TXT_H);
		RET_ON_ERR (c_wgl_move(h_sb_txt,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		/* set alignment */
    	RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_ALIGN,
						WGL_PACK(WGL_AS_CENTER_CENTER),
						NULL));

		/* update color */
		t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_COLOR,
						WGL_PACK (WGL_CLR_TEXT),
						WGL_PACK (&t_color_txt)));

		/* update font size */
	    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

	    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_FONT,
						WGL_PACK (&t_fnt_info),
						NULL));

		/*
			icon theme
		*/
		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						(WZD_SEL_BOX_BTN_W - WZD_SEL_BOX_BTN_ICON_1_W - 254 * WZD_UI_RATIO_W),
						(227 * WZD_UI_RATIO_W),
						WZD_SEL_BOX_BTN_ICON_1_W,
						WZD_SEL_BOX_BTN_ICON_1_H);
		RET_ON_ERR (c_wgl_move(h_sb_icon_1st,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		RET_ON_ERR (c_wgl_do_cmd(h_sb_icon_1st,
							  WGL_CMD_ICON_SET_ALIGN,
							  WGL_PACK(WGL_AS_RIGHT_TOP),
							  NULL));

		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						WZD_SEL_BOX_BTN_ICON_2_X,
						WZD_SEL_BOX_BTN_ICON_2_Y,
						WZD_SEL_BOX_BTN_ICON_2_W,
						WZD_SEL_BOX_BTN_ICON_2_H);
		RET_ON_ERR (c_wgl_move(h_sb_icon_2nd,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		RET_ON_ERR (c_wgl_do_cmd(h_sb_icon_2nd,
							  WGL_CMD_ICON_SET_ALIGN,
							  WGL_PACK(WGL_AS_CENTER_CENTER),
							  NULL));

		/* update plus icon on 1st button by wireless be connected */
		e_sb_idx = wzd_view_sel_box_get_btn_idx(ui4_btn_idx);
		if (t_wzd_nw.t_choice_connect.b_connected && WZD_SEL_BOX_BTN_01 == e_sb_idx)
		{
			RET_ON_ERR (wzd_view_sel_box_set_plus_icon(h_g_wzd_img_checkmark_green_small, FALSE));
		}
	}
	else if (NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT == e_g_nw_setup_state)
	{
		/*
			text theme
		*/
		h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						WZD_SEL_BOX_BTN_TXT_X,
						(WZD_SEL_BOX_BTN_H - WZD_SEL_BOX_BTN_TXT_H)/2,
						WZD_SEL_BOX_BTN_TXT_W,
						WZD_SEL_BOX_BTN_TXT_H);
		RET_ON_ERR (c_wgl_move(h_sb_txt,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		/* set alignment */
    	RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_ALIGN,
						WGL_PACK(WGL_AS_CENTER_CENTER),
						NULL));

		/* update color */
		t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_COLOR,
						WGL_PACK (WGL_CLR_TEXT),
						WGL_PACK (&t_color_txt)));

		/* update font size */
	    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

	    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_FONT,
						WGL_PACK (&t_fnt_info),
						NULL));
	}
	else
	{
		/* todo */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_sel_box_hl_theme
 *
 * Description:
 *
 * Inputs:  ui4_btn_idx		Select box button index
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _wzd_page_nw_setup_sel_box_hl_theme (const UINT32 ui4_btn_idx)
{
	HANDLE_T 					h_sb_txt = NULL_HANDLE;
	HANDLE_T 					h_sb_icon_1st = NULL_HANDLE;
	GL_RECT_T           		t_rect = {0};
	WGL_COLOR_INFO_T  			t_color_txt;
	WGL_FONT_INFO_T    			t_fnt_info;
	WZD_SEL_BOX_BTN_INDEX_T 	    e_sb_idx = WZD_SEL_BOX_BTN_COUNT;

	if (NW_SETUP_STATE_WIRELESS_SCANNING == e_g_nw_setup_state ||
		NW_SETUP_STATE_NONE_CONN == e_g_nw_setup_state)
	{
		/* no highlight */
	}
	else if (NW_SETUP_STATE_WIRELESS_SCAN_RESULT == e_g_nw_setup_state)
	{
		/*
			text theme
		*/
		h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						WZD_SEL_BOX_BTN_TXT_X,
						WZD_SEL_BOX_BTN_TXT_Y - (10 * WZD_UI_RATIO_W),
						WZD_SEL_BOX_BTN_TXT_W,
						WZD_SEL_BOX_BTN_TXT_H);
		RET_ON_ERR (c_wgl_move(h_sb_txt,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		/* set alignment */
    	RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_ALIGN,
						WGL_PACK(WGL_AS_CENTER_CENTER),
						NULL));

		/* update color */
		t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_hlt_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_hlt_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_hlt_txt);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_COLOR,
						WGL_PACK (WGL_CLR_TEXT),
						WGL_PACK (&t_color_txt)));

		/* update font size */
	    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

	    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_FONT,
						WGL_PACK (&t_fnt_info),
						NULL));

		/*
			icon theme
		*/
		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui4_btn_idx);

		/* move position */
		SET_RECT_BY_SIZE(&t_rect,
						(WZD_SEL_BOX_BTN_W - WZD_SEL_BOX_BTN_ICON_1_W - 226 * WZD_UI_RATIO_W),
						(200 * WZD_UI_RATIO_W),
						WZD_SEL_BOX_BTN_ICON_1_W,
						WZD_SEL_BOX_BTN_ICON_1_H);
		RET_ON_ERR (c_wgl_move(h_sb_icon_1st,
						&t_rect,
						WGL_NO_AUTO_REPAINT));

		/* update plus icon on 1st button by wireless be connected */
		e_sb_idx = wzd_view_sel_box_get_btn_idx(ui4_btn_idx);
		if (t_wzd_nw.t_choice_connect.b_connected && WZD_SEL_BOX_BTN_01 == e_sb_idx)
		{
			RET_ON_ERR (wzd_view_sel_box_set_plus_icon(h_g_wzd_img_checkmark_green_large, FALSE));
		}
	}
	else if (NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT == e_g_nw_setup_state)
	{
		/*
			text theme
		*/
		h_sb_txt = wzd_view_sel_box_get_txt_handle(ui4_btn_idx);

		/* update color */
		t_color_txt.e_type = WGL_COLOR_SET_STANDARD;
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_hlt_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_hlt_txt);
		COLOR_COPY (& t_color_txt.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_hlt_txt);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_COLOR,
						WGL_PACK (WGL_CLR_TEXT),
						WGL_PACK (&t_color_txt)));

		/* update font size */
	    c_memset (&t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
	    c_strcpy (t_fnt_info.a_c_font_name, wzd_view_get_font_name());

	    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_GL_SET_FONT,
						WGL_PACK (&t_fnt_info),
						NULL));
	}
	else
	{
		/* todo */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_initial_sel_box_content
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
static INT32 _wzd_page_nw_setup_initial_sel_box_content (VOID)
{
	HANDLE_T 					h_sb_txt = NULL_HANDLE;
	HANDLE_T 					h_sb_icon_1st = NULL_HANDLE;
	HANDLE_T 					h_sb_icon_2nd = NULL_HANDLE;
	WGL_IMG_INFO_T      		t_img_info;

	if (NW_SETUP_STATE_WIRELESS_SCANNING == e_g_nw_setup_state)
	{
		/* initial select box theme */
		RET_ON_ERR (_wzd_page_nw_setup_sel_box_initial_theme(0));

		h_sb_txt = wzd_view_sel_box_get_txt_handle(0);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_TEXT,
						WZD_TEXT(MLM_WZD_KEY_NW_SETUP_LOOKING_NETWORK_2),
						WGL_PACK ((UINT16)0xFFFF)));

		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(0);
		RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_HIDE));

		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(0);
		RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_2nd , WGL_SW_HIDE));
	}
	else if (NW_SETUP_STATE_NONE_CONN == e_g_nw_setup_state)
	{
		/* initial select box theme */
		RET_ON_ERR (_wzd_page_nw_setup_sel_box_initial_theme(0));

		h_sb_txt = wzd_view_sel_box_get_txt_handle(0);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
						WGL_CMD_TEXT_SET_TEXT,
						WGL_PACK ((WZD_TEXT(MLM_WZD_KEY_NW_SETUP_NO_NETWORK_FOUND))),
						WGL_PACK ((UINT16)0xFFFF)));

		h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(0);
		RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_HIDE));

		c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
	    /* set image */
	    t_img_info.e_type = WGL_IMG_SET_STANDARD;
	    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_warning_icon;
	    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_warning_icon;
	    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_warning_icon;
		h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(0);
		RET_ON_ERR (c_wgl_do_cmd (h_sb_icon_2nd,
								  WGL_CMD_GL_SET_IMAGE,
		                          WGL_PACK(WGL_IMG_FG),
		                          WGL_PACK(&t_img_info)));
	}
	else if (NW_SETUP_STATE_WIRELESS_SCAN_RESULT == e_g_nw_setup_state)
	{
		NET_802_11_ESS_INFO_T* p_essInfo = NULL;

		UINT8                  ui1_visiable_ap_num = 0;
		UINT8				   ui1_ap = 0;
		UINT8				   ui1_sel_box = 0;

		ui1_visiable_ap_num = t_wzd_nw.t_choice_connect.ui1_visiable_ap_num;

		DBG_INFO(("[WZD][NW] --- visiable AP num: %d.\n", ui1_visiable_ap_num));

		/* update current connected status */
        _wzd_nw_update_curr_connect_status();

		for (ui1_ap = 0; ui1_ap < ui1_visiable_ap_num; ui1_ap++)
		{
			/* get visiable ap by index */
			p_essInfo = _wzd_nw_get_ap_by_idx((UINT16)ui1_ap);
            if(p_essInfo == NULL)
            {
                continue;
            }

			/* initial select box theme */
			RET_ON_ERR (_wzd_page_nw_setup_sel_box_initial_theme(ui1_sel_box));

			/* add ap list to select box by index */
			_wzd_nw_add_ap_list_by_idx(ui1_sel_box,
									  &p_essInfo->t_Ssid,
                                      p_essInfo->i2_Level,
                                      p_essInfo->e_AuthMode,
                                      p_essInfo->e_AuthCipher);

			ui1_sel_box = ui1_sel_box + 1;
			if (ui1_sel_box >= WZD_SEL_BOX_BTN_COUNT)
			{
				break;
			}
		}
	}
	else if (NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT == e_g_nw_setup_state)
	{
		UINT8				   ui1_idx = 0;
		UINT16				   ui2_mlm_offset = MLM_WZD_KEY_NW_SECURE_NONE;

		for (ui1_idx = 0; ui1_idx < WZD_SEL_BOX_BTN_COUNT; ui1_idx++)
		{
			/* initial select box theme */
			RET_ON_ERR (_wzd_page_nw_setup_sel_box_initial_theme(ui1_idx));

			/* set every box contents */
			h_sb_txt = wzd_view_sel_box_get_txt_handle(ui1_idx);
			RET_ON_ERR (c_wgl_do_cmd (h_sb_txt,
							WGL_CMD_TEXT_SET_TEXT,
							WGL_PACK (WZD_TEXT(ui2_mlm_offset + ui1_idx)),
							WGL_PACK ((UINT16)0xFFFF)));

			h_sb_icon_1st = wzd_view_sel_box_get_icon_1_handle(ui1_idx);
			RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_1st, WGL_SW_HIDE));

			h_sb_icon_2nd = wzd_view_sel_box_get_icon_2_handle(ui1_idx);
			RET_ON_ERR (c_wgl_set_visibility (h_sb_icon_2nd , WGL_SW_HIDE));
		}
	}
	else
	{
		/* do something */
	}

	return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_sel_box_nfy
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
static VOID _wzd_page_nw_setup_sel_box_nfy(
					UINT32   		ui4_msg,
					VOID*    		pv_param1,
					VOID*    		pv_param2)
{
	INT32			i4_ret = WZDR_OK;

    switch (ui4_msg)
    {
		case WZD_SEL_BOX_MSG_ITEM_FOCUSED:
			_wzd_page_nw_setup_sel_box_hl_theme((UINT32)pv_param1);

            break;

		case WZD_SEL_BOX_MSG_ITEM_LOSE_FOCUSED:
			e_sb_pre_focused_box = wzd_view_sel_box_get_btn_idx((UINT32)pv_param1);

			_wzd_page_nw_setup_sel_box_initial_theme((UINT32)pv_param1);

            break;

		case WZD_SEL_BOX_MSG_ITEM_LEFT_SHIFT:
			_wzd_page_nw_setup_sel_box_left_shift((UINT32)pv_param1);

			break;

		case WZD_SEL_BOX_MSG_ITEM_RIGHT_SHIFT:
			_wzd_page_nw_setup_sel_box_right_shift((UINT32)pv_param1);

			break;

        case WZD_SEL_BOX_MSG_KEY_INPUT:
            switch((UINT32)pv_param1)
            {
                case BTN_SELECT:
                    {
						i4_ret = _wzd_page_nw_setup_sel_box_btn_select((UINT32)pv_param2);

						if (WZDR_OK != i4_ret)
						{
							wzd_view_footer_set_focus(WZD_FOOTER_BTN_01, FALSE);    /* Set focus to footer. */
							wzd_view_main_frm_repaint();
						}
                    }
                    break;
				case BTN_CURSOR_DOWN:
                    {
						_wzd_nw_footer_btn_focus();
					}
					break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _wzd_page_nw_setup_create_sel_box
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
static INT32 _wzd_page_nw_setup_create_sel_box (VOID)
{
    WZD_VIEW_SEL_BOX_INFO_T    	t_sel_box_info;

	/* reset previous focused select box button */
	e_sb_pre_focused_box = WZD_SEL_BOX_BTN_01;

    c_memset(&t_sel_box_info, 0 , sizeof(WZD_VIEW_SEL_BOX_INFO_T));

	/* set select box button count and position */
	if (NW_SETUP_STATE_WIRELESS_SCANNING == e_g_nw_setup_state)
	{
		t_sel_box_info.ui4_index_total = 1;
	}
	else if (NW_SETUP_STATE_NONE_CONN == e_g_nw_setup_state)
	{
		t_sel_box_info.ui4_index_total = 1;
	}
	else if (NW_SETUP_STATE_WIRELESS_SCAN_RESULT == e_g_nw_setup_state)
	{
		t_sel_box_info.ui4_index_total = t_wzd_nw.t_choice_connect.ui1_visiable_ap_num;
	}
	else if (NW_SETUP_STATE_WIRELESS_ENCRYPTION_SELECT == e_g_nw_setup_state)
	{
		t_sel_box_info.ui4_index_total = 7;
	}
	else
	{
		t_sel_box_info.ui4_index_total = 3;
	}
    t_sel_box_info.pf_data_chg_nfy = _wzd_page_nw_setup_sel_box_nfy;
    RET_ON_ERR (wzd_view_sel_box_set_info_data (&t_sel_box_info));

	/* initial select box content */
	RET_ON_ERR (_wzd_page_nw_setup_initial_sel_box_content());

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_nw_setup_nfy_sel
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
INT32 wzd_page_nw_setup_nfy_sel(
                UINT16                  ui2_sel_idx,
                VOID*                   pv_data,
                WZD_MSG_CUSTOM_T*       pt_ret_msg)
{
    (*pt_ret_msg)  = WZD_MSG_CUSTOM_NAV_NEXT_PAGE;

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: wzd_page_nw_setup_get_page_info_data
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
INT32 wzd_page_nw_setup_get_page_info_data(
                WZD_PAGE_INFO_DATA_T*   pt_info_data)
{
    c_memset( pt_info_data, 0, sizeof(WZD_PAGE_INFO_DATA_T) );

    pt_info_data->t_page_type              = WZD_PAGE_TYPE_CUST_PAGE;
    pt_info_data->ui2_title_key            = MLM_WZD_KEY_TITLE_NETWORK_SETUP;
    pt_info_data->ui2_desc_text_key        = MLM_WZD_KEY_DESC_TUNER;
    pt_info_data->ui1_elem_num             = 0;
    pt_info_data->pf_get_text              = NULL;
    pt_info_data->pf_footer_data_change    = _wzd_page_nw_setup_on_footer_nfy;
	pt_info_data->pf_return_nfy_fct        = _wzd_page_nw_setup_return_nfy_cb;

    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_create   = _wzd_page_nw_setup_create;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_destory  = _wzd_page_nw_setup_destory;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_show     = _wzd_page_nw_setup_show;
    pt_info_data->t_cust_page_fct_tab.pf_wzd_cust_page_hide     = _wzd_page_nw_setup_hide;

    return WZDR_OK;
}

#endif /* APP_NETWORK_SUPPORT */
