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
 * $RCSfile: menu_page_network.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

#ifdef APP_NETWORK_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_dt.h"

#include "menu2/menu_util2.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_common/menu_page_animation.h"
#include "menu_network_com_ui.h"

#include "res/menu2/menu_custom.h"
#include "res/menu2/menu_img.h"
#include "res/menu2/menu_custom_dialog.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"

#include "c_time_msrt.h"
#include "u_time_msrt_name.h"
#include <sys/time.h>

#include "res/wdk/wdk_img.h"
#include "res/app_util/network/network_custom.h"

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdlib.h>
#include <stdio.h>
#endif

#include "menu_network.h"
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif

#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define NW_ITEM_V_HEIGHT                (MENU_ITEM_V_HEIGHT)
#define NW_AP_CON_COL0_W                (FRAME_LEFT_RIGHT_INTV + 29 + 15)
#define NW_AP_CON_COL1_W                (MENU_ITEM_V_WIDE - NW_AP_CON_COL0_W - NW_AP_CON_COL2_W - NW_AP_CON_COL3_W)
#define NW_AP_CON_COL2_W                ((17 + 16)*4/3)
#define NW_AP_CON_COL3_W                (FRAME_LEFT_RIGHT_INTV + 45 - 8)

#define NW_DIALOG_FRAM_X                ((SCREEN_W - NW_DIALOG_FRAM_W)/2)
#define NW_DIALOG_FRAM_Y                ((SCREEN_H - NW_DIALOG_FRAM_H)/2)
#define NW_DIALOG_FRAM_W                (613)
#define NW_DIALOG_FRAM_H                (234)

#define NW_DIALOG_ICON_X                (0)
#define NW_DIALOG_ICON_Y                (10)
#define NW_DIALOG_ICON_W                (NW_DIALOG_FRAM_W)
#define NW_DIALOG_ICON_H                (52)

#define NW_DIALOG_TITLE_X               (0)
#define NW_DIALOG_TITLE_Y               (NW_DIALOG_ICON_Y + NW_DIALOG_ICON_H + 10)
#define NW_DIALOG_TITLE_W               (NW_DIALOG_FRAM_W)
#define NW_DIALOG_TITLE_H               (MENU_ITEM_V_HEIGHT*2-NW_DIALOG_ICON_H)

#define NW_DIALOG_TRY_AGAIN_X           (NW_DIALOG_FRAM_W-NW_DIALOG_TRY_ANOTHER_X-NW_DIALOG_TRY_ANOTHER_W)
#define NW_DIALOG_TRY_AGAIN_Y           (NW_DIALOG_FRAM_H - NW_DIALOG_TRY_AGAIN_H - 32)
#define NW_DIALOG_TRY_AGAIN_W           (164)
#define NW_DIALOG_TRY_AGAIN_H           (33)

#define NW_DIALOG_TRY_ANOTHER_X         ((NW_DIALOG_FRAM_W-(NW_DIALOG_TRY_ANOTHER_W*2))/3)
#define NW_DIALOG_TRY_ANOTHER_Y         (NW_DIALOG_TRY_AGAIN_Y)
#define NW_DIALOG_TRY_ANOTHER_W         (NW_DIALOG_TRY_AGAIN_W)
#define NW_DIALOG_TRY_ANOTHER_H         (NW_DIALOG_TRY_AGAIN_H)


/*For timer*/
#define WLAN_SCANNING_TIMEOUT           (40)
#define WLAN_CONNECTING_TIMEOUT         (30)   /*about 30 s*/
#define WLAN_WPS_CONNECTING_TIMEOUT     (120)

#define WLAN_AP_LB_MAX_NUM              (128)
#define WLAN_PWD_KEY_MAX_LEN            (128)

#define NW_ANIMATION_IMG_MAX_NUM        (12)

#define WLAN_AP_LB_ELEM_NUM             (5)

#define BTN_MORE_ACCESS_POINTS_IDX      ((UINT8)6)

#ifdef APP_NW_WPS_SUPPORT
#define BTN_WPS_IDX                     ((UINT8)7)
#define BTN_MANUAL_SETUP_IDX            ((UINT8)8)
#define BTN_HIDDEN_NETWORK_IDX          ((UINT8)9)
#define BTN_TEST_CONNECTION_IDX         ((UINT8)10)
#define BTN_NET_INFO_IDX                ((UINT8)11)

#else
#define BTN_WPS_IDX                     ((UINT8)7)
#define BTN_MANUAL_SETUP_IDX            ((UINT8)7)
#define BTN_HIDDEN_NETWORK_IDX          ((UINT8)8)
#define BTN_TEST_CONNECTION_IDX         ((UINT8)9)
#define BTN_NET_INFO_IDX                ((UINT8)10)

#endif

#define ARRY_NW_PAGE_ITEM_IDX_1         \
{                                       \
    BTN_MORE_ACCESS_POINTS_IDX,         \
    BTN_MANUAL_SETUP_IDX,               \
    BTN_HIDDEN_NETWORK_IDX,             \
    BTN_TEST_CONNECTION_IDX,            \
    BTN_NET_INFO_IDX                    \
}

#define ARRY_NW_PAGE_ITEM_IDX_2         \
{                                       \
    0, 1, 0, 2, 3                          \
}

static UTF16_T     w2s_empty[] = {0};
static WGL_INSET_T t_g_inset_border = {
    FRAME_LEFT_RIGHT_INTV + MENU_ITEM_V_TITLE_W,
    FRAME_LEFT_RIGHT_INTV,
    0,
    0};
static GL_RECT_T   t_g_rect_border_title = {
    FRAME_LEFT_RIGHT_INTV,
    0,
    MENU_ITEM_V_TITLE_W,
    NW_ITEM_V_HEIGHT};

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef struct __NW_NFY_DATA
{
    VOID*               pv_tag;
    NW_NFY_ID_T         e_nfy_id;
    VOID*               pv_nfy_param;
}_NW_NFY_DATA;

typedef struct _MENU_NW_ITEM_T
{
    HANDLE_T            h_subpage;
    UINT16              ui2_msgid_title;
    UINT16              ui2_msgid_desc;
    UINT32              ui4_subpage_id;
} MENU_NW_ITEM_T;

typedef struct _NW_PAGE_DATA_T
{
    HANDLE_T            h_cnt_frm;

    HANDLE_T            h_txt_connection;

    HANDLE_T            h_txt_ap_list_tit;
    HANDLE_T            h_lb_ap_list;
    HANDLE_T            h_wps;

    MENU_NW_ITEM_T      at_item[NW_PAGE_ID_LAST_ENTRY];

    BOOL                b_page_back;
    BOOL                b_page_connect_success_back;


    BOOL                b_connec_timer;
    BOOL                b_finish;
    BOOL                b_timer_result;
    BOOL                b_wps_associate;

    UINT8               ui1_animation_count;


    UINT8               aui1_ap_map[WLAN_AP_LB_MAX_NUM];
    UINT8               ui1_ap_num;

    HANDLE_T            h_confirm_dialog_frm;
    HANDLE_T            h_warning_icon;
    HANDLE_T            h_confirm_dialog_title;
    HANDLE_T            h_confirm_dialog_try_again;
    HANDLE_T            h_confirm_dialog_try_another;

    HANDLE_T            h_timer;
    HANDLE_T            h_retest_timer;

    UINT32              ui4_nw_nfy_id;
    UINT32              b_wired_plug;

    HANDLE_T            h_last_focus;

    UINT32              ui4_pwd_page_id;

    BOOL                b_this_page_show;

    NET_802_11_ESS_LIST_T   t_essList;
    NET_802_11_ASSOCIATE_T  t_associate;
}NW_PAGE_DATA_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_network;

static NW_PAGE_DATA_T       t_nw_page_data;

static WGL_HIMG_TPL_T       h_g_img_animation[NW_ANIMATION_IMG_MAX_NUM];
static UINT8                ui1_g_img_idx = 0;
static HANDLE_T             h_g_img_icon;
BOOL b_g_wps_is_associating = FALSE;
BOOL b_ipv6_only = FALSE;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _update_network_wired_connection(VOID);
static INT32 _update_all_items(VOID);
static INT32 _update_ap_list(VOID);
static INT32 _update_ap_list_with_local_buf(VOID);
static INT32 _menu_page_network_timer_finish(BOOL b_success, BOOL b_timeout);
static VOID _nw_confirm_dialog_try_again_cb_fct(UINT32 ui4_key_code);
static VOID _nw_confirm_dialog_try_another_cb_fct(UINT32 ui4_key_code);
static VOID _nw_timer_cb_fct (HANDLE_T  pt_tm_handle,
                               VOID*     pv_tag);
static BOOL _is_lock_ap(NET_802_11_AUTH_MODE_T          e_AuthMode,
                       NET_802_11_AUTH_CIPHER_T        e_AuthCipher);
static VOID _wps_cb_fct(UINT32 ui4_keycode);

/*-----------------------------------------------------------------------------
                    function implementation
----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _nw_img_animation_hide
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
static VOID _nw_img_animation_hide(BOOL     b_repaint)
{
    c_wgl_set_visibility(h_g_img_icon, WGL_SW_HIDE);

    if (b_repaint)
    {
        c_wgl_repaint( h_g_img_icon, NULL, TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _nw_img_animation_show
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
static VOID _nw_img_animation_show(BOOL     b_repaint)
{
    c_wgl_set_visibility(h_g_img_icon, WGL_SW_NORMAL);

    if (b_repaint)
    {
        c_wgl_repaint( h_g_img_icon, NULL, TRUE);
    }
}

/*----------------------------------------------------------------------------
 * Name: _menu_page_network_nw_notify_handler
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
static VOID _menu_page_network_nw_notify_handler(VOID*      pv_data,
                                                 SIZE_T     z_data_size)
{
    _NW_NFY_DATA* pt_nw_nfy_data = (_NW_NFY_DATA*)pv_data;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    DBG_LOG_PRINT(("[MENU][%s %d]Handle the wifi notify -> %d\n",__FUNCTION__,__LINE__, pt_nw_nfy_data->e_nfy_id));

    switch(pt_nw_nfy_data->e_nfy_id)
    {
        case NW_NFY_ID_ETHERNET_UNPLUG:
        case NW_NFY_ID_ETHERNET_PLUGIN:
        {
            menu_nav_go_home_menu();
            break;
        }
        case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
        case NW_NFY_ID_DHCP_SUCCESS_LINKLOCAL:
        {
            if (pt_page_data->b_finish == FALSE && pt_page_data->b_connec_timer)
            {
                BOOL      b_wired_plug = FALSE;
                a_nw_get_ethernet_connect_info(&b_wired_plug);
                if (!b_wired_plug)
                {
                    _menu_page_network_timer_finish(TRUE, FALSE);
                }

                break;
            }
        }
        case NW_NFY_ID_ADDRESS_CHANGED:
        case NW_NFY_ID_ADDRESS_EXPIRED:
        case NW_NFY_ID_DHCP_FAILURE_LINKLOCAL:
        case NW_NFY_ID_DHCP_STOPPED:
        {
            if(t_nw_page_data.b_wired_plug)
            {
                _update_network_wired_connection();
                c_wgl_repaint(t_nw_page_data.h_txt_connection, NULL, FALSE);
            }

            break;
        }
#ifdef APP_NETWORK_WIFI_SUPPORT
        case NW_NFY_ID_WLAN_ASSOCIATE:
        {
            WLAN_NOTIFY_MSG_T e_result = (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param);
            DBG_LOG_PRINT(("[NW][%s %d %d ]NW_NFY_ID_WLAN_ASSOCIATE b_finish=%d,b_connec_timer=%d,result =%d\n",
                         __FILE__, __FUNCTION__, __LINE__,
                         pt_page_data->b_finish,
                         pt_page_data->b_connec_timer,
                         e_result));


            if (e_result == WLAN_NFY_MSG_OK)
            {
                BOOL          b_auto_ip_config  = FALSE;
                nw_custom_get_auto_ip_config_by_iface(&b_auto_ip_config, NW_NET_INTERFACE_WIFI);
                if(b_auto_ip_config)
                {
                    pt_page_data->b_finish       = TRUE;
                    pt_page_data->b_timer_result = TRUE;
                }

                menu_network_simple_dialog_hide(TRUE);

                if (b_g_wps_is_associating)
                {
                    c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
                    b_g_wps_is_associating = FALSE;
                }

                pt_page_data->b_finish        = FALSE;
                pt_page_data->b_connec_timer  = FALSE;
                pt_page_data->b_timer_result  = FALSE;
                pt_page_data->b_wps_associate = FALSE;
            }
            else if (e_result == WLAN_NFY_MSG_PSK_INCORRECT ||
                     e_result == WLAN_NFY_MSG_WPS_CREDENTIAL_INVALID)
            {
                pt_page_data->b_finish = TRUE;
                pt_page_data->b_timer_result = FALSE;
            }
            a_nw_wlan_scan();
            break;
        }
        case NW_NFY_ID_WLAN_SCAN:
        {
            WLAN_NOTIFY_MSG_T e_result = (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param);
            DBG_LOG_PRINT(("[NW][%s %s %d ]NW_NFY_ID_WLAN_SCAN b_finish=%d,b_connec_timer=%d,result =%d\n",
                         __FILE__, __FUNCTION__, __LINE__,
                         pt_page_data->b_finish,
                         pt_page_data->b_connec_timer,
                         e_result));

            if(pt_page_data->b_finish || pt_page_data->b_connec_timer)
            {
                break;
            }

            c_timer_stop( pt_page_data->h_timer);
            _nw_img_animation_hide(TRUE);

            pt_page_data->b_finish = TRUE;

            if ( WLAN_NFY_MSG_OK == (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param))
            {
                pt_page_data->b_timer_result = TRUE;
                _menu_page_network_timer_finish(pt_page_data->b_timer_result, FALSE);
            }
            else
            {
                pt_page_data->b_timer_result = FALSE;
            }

            break;
        }
        case NW_NFY_ID_WLAN_START_IND:
        {
            DBG_LOG_PRINT(("[%s,%s,%d],b_finish=%d,b_connec_timer=%d\n",
                       __FILE__, __FUNCTION__, __LINE__,
                       pt_page_data->b_finish, pt_page_data->b_connec_timer));

            if (a_nw_custom_nw_wifi_start())
            {
                MENU_LOG_ON_FAIL(a_nw_wlan_scan());
            }
            else
            {
                DBG_LOG_PRINT(("\n<MENU NW>wifi driver not ready, wait...\n"));
            }

            if(pt_page_data->b_finish && pt_page_data->b_connec_timer)
            {
                break;
            }

            /* init the animation count as 0*/
            pt_page_data->ui1_animation_count = 0;

            break;
        }
#endif
        case NW_NFY_ID_INTERN_CT_RESULT:
            break;

        default:
            return;
    }

    return;
}

static VOID _menu_page_network_nw_notify_callback (VOID* pv_tag,
                                                   NW_NFY_ID_T e_nfy_id,
                                                   VOID* pv_nfy_param)
{
    _NW_NFY_DATA t_nw_nfy_data;

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    menu_async_invoke(_menu_page_network_nw_notify_handler,
                      &t_nw_nfy_data,sizeof(_NW_NFY_DATA),TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _widgets_proc_fct
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
static INT32 _widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_EXIT:
            menu_nav_go_home_menu();
            return WMPR_DONE;
        default:
            break;
        }
    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _get_top_focus_handle
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
static HANDLE_T _get_top_focus_handle(VOID)
{

    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    if(pt_page_data->b_wired_plug)
    {
        return pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage;
    }
    else if(pt_page_data->ui1_ap_num != 0)
    {
        return pt_page_data->h_lb_ap_list;
    }
    else
    {
    #ifdef APP_NW_WPS_SUPPORT
        return pt_page_data->h_wps;
    #else
        return pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage;
    #endif
    }
}

/*----------------------------------------------------------------------------
 * Name: _set_connection_txt_title
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
static INT32 _set_connection_txt_title (UINT16 ui2_msgid_title)
{
    INT32    i4_ret = MENUR_OK;

    /* Set Title language */
    i4_ret = c_wgl_do_cmd(t_nw_page_data.h_txt_connection,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _set_connection_txt_text
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
static INT32 _set_connection_txt_text (UINT16 ui2_msgid_title)
{
    INT32   i4_ret;

    i4_ret = c_wgl_do_cmd(t_nw_page_data.h_txt_connection,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _set_ap_list_title_text
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
static INT32 _set_ap_list_title_text (UINT16 ui2_msgid_title)
{
    INT32   i4_ret;

    i4_ret = c_wgl_do_cmd(t_nw_page_data.h_txt_ap_list_tit,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(ui2_msgid_title)),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _menu_page_network_show_ap_list_empty_dlg
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
static INT32 _menu_page_network_show_ap_list_empty_dlg (VOID)
{
    INT32           i4_ret = MENUR_OK;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    HANDLE_T        h_frm_main = NULL_HANDLE;

    i4_ret = menu_network_show_confirm_dialog_ex(MENU_TEXT(MLM_MENU_KEY_NW_NO_NETWORK_FOUND),
                                        MENU_TEXT(MLM_MENU_KEY_CNCL),
                                        MENU_TEXT(MLM_MENU_KEY_NW_WIFI_TRY_AGAIN),
                                        _nw_confirm_dialog_try_again_cb_fct,
                                        _nw_confirm_dialog_try_another_cb_fct,
                                        FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_page_data->h_confirm_dialog_try_another, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_pm_get_root_frm(&h_frm_main);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(h_frm_main,  NULL, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_page_data->h_confirm_dialog_frm,  NULL, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[256] = {0};

    c_uc_w2s_strcpy(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_NW_NO_NETWORK_FOUND));
    c_uc_w2s_strcat(w2s_str, _TEXT("."));
    c_uc_w2s_strcat(w2s_str, MENU_TTS_TEXT(MLM_MENU_KEY_NW_WIFI_TRY_AGAIN));

    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_page_network_timer_finish
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
static INT32 _menu_page_network_timer_finish (BOOL b_success, BOOL b_timeout)
{
    INT32                   i4_ret           = MENUR_OK;
    NET_802_11_ASSOCIATE_T* pt_associate     = NULL;
    UTF16_T                 w2s_ssid[32+1]   = {0};
    UTF16_T                 w2s_title[128+1] = {0};
    NW_PAGE_DATA_T*         pt_page_data     = &t_nw_page_data;

    DBG_LOG_PRINT(("\n%s,%s,%d,b_finish=%d,b_success=%d,b_connec_timer=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_page_data->b_finish,
                b_success, pt_page_data->b_connec_timer));

    if (pt_page_data->b_connec_timer)
    {
        if (b_timeout || (!b_success))
        {
            i4_ret = a_nw_custom_wlan_disassociate();
            MENU_LOG_ON_FAIL(i4_ret);

            menu_network_get_associate_data(&pt_associate);
            if (pt_associate != NULL)
            {
                c_uc_ps_to_w2s(pt_associate->t_Ssid.ui1_aSsid, w2s_ssid, 32);
            }

            c_uc_w2s_strcpy(w2s_title, MENU_TEXT(MLM_MENU_KEY_NW_CON_FAIL));
            c_uc_w2s_strcat(w2s_title, w2s_ssid);

            i4_ret = menu_network_show_confirm_dialog_ex(w2s_title,
                                                MENU_TEXT(MLM_MENU_KEY_NW_WIFI_TRY_AGAIN),
                                                MENU_TEXT(MLM_MENU_KEY_NW_WIFI_TRY_ANOTHER),
                                                _nw_confirm_dialog_try_again_cb_fct,
                                                _nw_confirm_dialog_try_another_cb_fct,
                                                TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i4_ret = _update_ap_list();
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_repaint(pt_page_data->h_cnt_frm,  NULL, FALSE);
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }
    else
    {
        if (b_success)
        {
            MENU_LOG_ON_FAIL(_update_ap_list());

            DBG_LOG_PRINT(("\n%s,%d --- AP NUM: %d. \n",
                    __FILE__, __LINE__, pt_page_data->ui1_ap_num));

            if (pt_page_data->ui1_ap_num <= 0)
            {
                _menu_page_network_show_ap_list_empty_dlg();
            }
            else
            {
                i4_ret = c_wgl_repaint(pt_page_data->h_cnt_frm,  NULL, FALSE);
                MENU_LOG_ON_FAIL(i4_ret);
                //jundi for DTV02310779, after update wifi list, set the cursor on the first wifi ap item.
                i4_ret = c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            _menu_page_network_show_ap_list_empty_dlg();
        }
    }

    pt_page_data->b_finish = TRUE;
    pt_page_data->b_timer_result = TRUE;
    i4_ret = c_timer_stop(pt_page_data->h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    _nw_img_animation_hide(TRUE);

    return i4_ret;
}

static VOID _menu_page_network_do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{

    INT32    i4_ret = MENUR_OK;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    BOOL    b_success;
    UINT8  ui1_timeout_count;
    WGL_IMG_INFO_T    t_img_info;
    INT32 i4_progress = 0;

    if (pt_page_data->b_wps_associate)
    {
        if (pt_page_data->ui1_animation_count >= WLAN_WPS_CONNECTING_TIMEOUT)
        {
            _wps_cb_fct(0);
        }
        else
        {
            c_timer_start(pt_page_data->h_timer, 1000,
                          X_TIMER_FLAG_ONCE,
                          _nw_timer_cb_fct,
                          NULL);
            pt_page_data->ui1_animation_count += 1;

            i4_progress = pt_page_data->ui1_animation_count * 100 / WLAN_WPS_CONNECTING_TIMEOUT;

            i4_ret = menu_network_wps_dialog_set_progress(i4_progress, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        return;
    }

    if (pt_page_data->b_connec_timer)
    {
        ui1_timeout_count = WLAN_CONNECTING_TIMEOUT;
    }
    else
    {
        ui1_timeout_count = WLAN_SCANNING_TIMEOUT;
    }

    b_success = pt_page_data->b_timer_result;

#ifdef DEBUG
    DBG_LOG_PRINT(("\n%s,%s,%d,b_finish=%d,b_success=%d,ui1_animation_count=%d,ui1_timeout_count=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_page_data->b_finish,
                b_success, pt_page_data->ui1_animation_count, ui1_timeout_count));
#endif

    if (pt_page_data->b_finish)
    {
        i4_ret = _menu_page_network_timer_finish(b_success, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(pt_page_data->ui1_animation_count > ui1_timeout_count)
    {
        i4_ret = _menu_page_network_timer_finish(TRUE, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        ui1_g_img_idx += 1;
        if (ui1_g_img_idx > (NW_ANIMATION_IMG_MAX_NUM - 1))
        {
            ui1_g_img_idx = 0;
        }

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_disable = h_g_img_animation[ui1_g_img_idx];
        t_img_info.u_img_data.t_standard.t_enable = h_g_img_animation[ui1_g_img_idx];
        t_img_info.u_img_data.t_standard.t_highlight = h_g_img_animation[ui1_g_img_idx];

        c_wgl_do_cmd(h_g_img_icon,
                             WGL_CMD_GL_SET_IMAGE,
                             WGL_PACK(WGL_IMG_FG),
                             WGL_PACK(&t_img_info));

        _nw_img_animation_show(TRUE);

        c_timer_start(pt_page_data->h_timer, 1000, X_TIMER_FLAG_ONCE, _nw_timer_cb_fct, NULL);
        pt_page_data->ui1_animation_count += 1;
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nw_timer_cb_fct
 *
 * Description:timer callback function
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nw_timer_cb_fct (HANDLE_T  pt_tm_handle,
                               VOID*     pv_tag)
{
    menu_async_invoke(_menu_page_network_do_timer_nfy,
                      NULL, 0, TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _update_network_wired_connection
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
static INT32 _update_network_wired_connection(VOID)
{
    INT32           i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    BOOL b_wired_plug       = FALSE;
    BOOL  b_wired_connected = FALSE;

    i4_ret= a_nw_get_ethernet_connect_info(&b_wired_plug);

    if(i4_ret == MENUR_OK && b_wired_plug)
    {
        if (NWR_OK == a_get_nw_init_status())
        {
            b_wired_connected = TRUE;
        }
    }

    pt_page_data->b_wired_plug = b_wired_plug;

    if (b_wired_connected)
    {
        i4_ret = _set_connection_txt_text(MLM_MENU_KEY_NET_WIR_CON);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = _set_connection_txt_text(MLM_MENU_KEY_NET_WIR_DISCON);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_enable(pt_page_data->h_txt_connection, b_wired_plug);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _is_lock_ap
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
static BOOL _is_lock_ap(NET_802_11_AUTH_MODE_T          e_AuthMode,
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
 * Name: _add_ap_list_elem
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
static INT32 _add_ap_list_elem( BOOL                            b_connected,
                              NET_802_11_SSID_T*              pt_Ssid,
                              INT16                           i2_Level,
                              NET_802_11_AUTH_MODE_T          e_AuthMode,
                              NET_802_11_AUTH_CIPHER_T        e_AuthCipher
                              )
{
    INT32           i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    INT16           i2_new_level = 0;

    UTF16_T w2s_ssid[33] = {0};
    WGL_LB_ITEM_T       at_items[4];

    HANDLE_T    at_img_signal_icon[5] =
    {
        h_g_wifi_signal_half_v2,
        h_g_wifi_signal_1_v2,
        h_g_wifi_signal_2_v2,
        h_g_wifi_signal_3_v2,
        h_g_wifi_signal_4_v2
    };

    BOOL    b_lock = _is_lock_ap(e_AuthMode, e_AuthCipher);

    c_uc_ps_to_w2s(pt_Ssid->ui1_aSsid,w2s_ssid, pt_Ssid->ui4_SsidLen);
    w2s_ssid[pt_Ssid->ui4_SsidLen]= (UTF16_T)0;

    DBG_LOG_PRINT(("[%s %d] add ssid:%s, b_connected = %d,i2_Level = %d,e_AuthMode = %d,e_AuthCipher = %d\n",
                  __FUNCTION__,__LINE__,
                  pt_Ssid->ui1_aSsid,
                  b_connected,
                  i2_Level,
                  e_AuthMode,
                  e_AuthCipher));
    at_items[0].e_col_type = LB_COL_TYPE_IMG;
    at_items[0].data.h_img = b_connected? h_g_wifi_connected_v2: NULL_HANDLE;
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_ssid;
    at_items[2].e_col_type = LB_COL_TYPE_IMG;
    at_items[2].data.h_img = b_lock ? h_g_lock_white_v2 : h_g_unlock_white_v2;
    at_items[3].e_col_type = LB_COL_TYPE_IMG;

    i2_new_level = a_nw_custom_wifi_signal_remapping(i2_Level);

    if((UINT16)i2_new_level > 80)
    {
        at_items[3].data.h_img = at_img_signal_icon[4];
    }
    else if((UINT16)i2_new_level <= 20)
    {
        at_items[3].data.h_img = at_img_signal_icon[0];
    }
    else
    {
        at_items[3].data.h_img = at_img_signal_icon[(((UINT16)(i2_new_level -1)) /20)%5];
    }

    i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _wlan_update_associate
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
static INT32 _wlan_update_associate(VOID)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    INT32           i4_ret = MENUR_OK;
    NW_WLAN_STATE_T  e_wlan_state = NW_WLAN_UNPLUG;

    if(pt_page_data->b_wired_plug)
    {
        return MENUR_OK;
    }

    /* just update first ap status, connected or not */
    i4_ret = a_nw_wlan_status(&e_wlan_state);
    MENU_LOG_ON_FAIL(i4_ret);

    if(e_wlan_state != NW_WLAN_ASSOCIATE)
    {
        i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list,
                              WGL_CMD_LB_SET_ITEM_IMAGE,
                              WGL_PACK_2(0,0),
                              WGL_PACK(NULL_HANDLE));
        MENU_LOG_ON_FAIL(i4_ret);

    }
    else
    {
        NET_802_11_ESS_INFO_T* p_essInfo = NULL;
        NET_802_11_BSS_INFO_T t_CurrBss;
        NET_802_11_ESS_LIST_T* pt_essList = &pt_page_data->t_essList;
        UINT16 ui2_idx = 0;

        c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
        i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
        if(i4_ret != NWR_OK)
        {
            c_memset(t_CurrBss.t_Bssid, 0, sizeof(t_CurrBss.t_Bssid));
            t_CurrBss.t_Ssid.ui4_SsidLen = 0;
        }

        if(t_CurrBss.t_Ssid.ui4_SsidLen == 0)
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list,
                                  WGL_CMD_LB_SET_ITEM_IMAGE,
                                  WGL_PACK_2(0,0),
                                  WGL_PACK(NULL_HANDLE));
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }

        if(pt_essList->ui4_NumberOfItems == 0)
        {
            return MENUR_OK;
        }

        ui2_idx = pt_page_data->aui1_ap_map[0];

        if((UINT32)ui2_idx > pt_essList->ui4_NumberOfItems)
        {
            DBG_INFO(("\n%s,%d,pt_essList->ui4_NumberOfItems=%d,ui2_idx=%d\n",
                      __FILE__, __LINE__,
                      pt_essList->ui4_NumberOfItems,
                      ui2_idx));
            return MENUR_ITEM_NOT_FOUND;
        }

        p_essInfo = &pt_essList->p_EssInfo[ui2_idx];

        if(c_strncmp(p_essInfo->t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui1_aSsid, NET_802_11_MAX_LEN_SSID ) != 0)
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list,
                                  WGL_CMD_LB_SET_ITEM_IMAGE,
                                  WGL_PACK_2(0,0),
                                  WGL_PACK(NULL_HANDLE));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }
    return i4_ret;
}

/* ui skip the ssid which end with "VIZIOTV" */
static BOOL _is_filter_out_ssid(CHAR* pssid)
{
    CHAR s_temp_string[10] = {0};
    UINT8 ui1_i = 0;

    if (c_strlen(pssid) < 7)
    {
        return FALSE;
    }

    for (ui1_i=0; ui1_i<7; ui1_i++)
    {
        s_temp_string[ui1_i] = pssid[c_strlen(pssid)-1-ui1_i];
    }

    if (0 == c_strcmp(s_temp_string, "VTOIZIV"))
    {
        DBG_INFO(("%s,%s,%s,%s,%d,s_temp_string=%s\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    s_temp_string));
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*----------------------------------------------------------------------------
 * Name: _update_ap_list
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
static INT32 _update_ap_list(VOID)
{
    INT32           i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    UINT8               ui1_idx = 0;

    NET_802_11_ESS_LIST_T t_essList_tmp;

    NET_802_11_ESS_INFO_T* p_essInfo = NULL;
    NET_802_11_BSS_INFO_T t_CurrBss;

    UINT8   ui1_max_ap_num = WLAN_AP_LB_MAX_NUM;
    UINT8   ui1_visiable_ap_num = WLAN_AP_LB_ELEM_NUM;
    GL_RECT_T   t_rect;
    NET_802_11_ESS_INFO_T   t_Ess_tmp;
    BOOL                    b_wireless_connected = FALSE;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list, WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_ap_list_page_clean_ap_list();
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(pt_page_data->aui1_ap_map, 0 , sizeof(pt_page_data->aui1_ap_map));
    pt_page_data->ui1_ap_num = 0;

    i4_ret = c_wgl_set_visibility(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset (&t_essList_tmp, 0, sizeof(t_essList_tmp));
    i4_ret = a_nw_wlan_get_ess_list(&t_essList_tmp);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    if(i4_ret != NWR_OK)
    {
        MENU_LOG_ON_FAIL(i4_ret);
        c_memset(t_CurrBss.t_Bssid, 0, sizeof(t_CurrBss.t_Bssid));
        t_CurrBss.t_Ssid.ui4_SsidLen = 0;
    }

    if ((t_CurrBss.t_Ssid.ui4_SsidLen > 0 || c_strlen(t_CurrBss.t_Ssid.ui1_aSsid) > 0)
        &&((UINT8)WLAN_WPA_COMPLETED == t_CurrBss.u8_wpa_status))
    {
        b_wireless_connected = TRUE;
    }

    DBG_LOG_PRINT(("\n%s,%d,from middleware:t_essList_tmp.ui4_NumberOfItems=%d,u8_wpa_status=%d,"
                "t_CurrBss.t_Ssid.ui4_SsidLen=%d,t_CurrBss.t_Ssid.ui1_aSsid=%s,\n",
               __FUNCTION__, __LINE__,
               t_essList_tmp.ui4_NumberOfItems, t_CurrBss.u8_wpa_status,
               t_CurrBss.t_Ssid.ui4_SsidLen, t_CurrBss.t_Ssid.ui1_aSsid));

    if(t_essList_tmp.ui4_NumberOfItems == 0)
    {
        return MENUR_OK;
    }

    do
    {
        DBG_LOG_PRINT(("[MENU][%s %d] b_wireless_connected = %d\n",__FUNCTION__,__LINE__,b_wireless_connected));
        if (FALSE == b_wireless_connected)
        {
            break;
        }

        if (0 == c_strcmp(t_essList_tmp.p_EssInfo[0].t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui1_aSsid))
        {
            break;
        }

        for (ui1_idx = 1; ui1_idx < t_essList_tmp.ui4_NumberOfItems; ui1_idx ++)
        {
            if (0 == c_strcmp(t_essList_tmp.p_EssInfo[ui1_idx].t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui1_aSsid))
            {
                #if 0
                /* use bubble algorithm to sort. */
                for (ui1_idx_2 = ui1_idx; ui1_idx_2 > 0; ui1_idx_2--)
                {
                    c_memcpy(&t_Ess_tmp,
                             &(t_essList_tmp.p_EssInfo[ui1_idx_2]),
                             sizeof(NET_802_11_ESS_INFO_T));
                    c_memcpy(&(t_essList_tmp.p_EssInfo[ui1_idx_2]),
                             &(t_essList_tmp.p_EssInfo[ui1_idx_2-1]),
                             sizeof(NET_802_11_ESS_INFO_T));
                    c_memcpy(&(t_essList_tmp.p_EssInfo[ui1_idx_2-1]),
                             &t_Ess_tmp,
                             sizeof(NET_802_11_ESS_INFO_T));
                }
               #else
                    /*swap the current ssid to be 1th*/
                    c_memcpy(&t_Ess_tmp,
                             &(t_essList_tmp.p_EssInfo[0]),
                             sizeof(NET_802_11_ESS_INFO_T));
                    c_memcpy(&(t_essList_tmp.p_EssInfo[0]),
                             &(t_essList_tmp.p_EssInfo[ui1_idx]),
                             sizeof(NET_802_11_ESS_INFO_T));
                    c_memcpy(&(t_essList_tmp.p_EssInfo[ui1_idx]),
                             &t_Ess_tmp,
                             sizeof(NET_802_11_ESS_INFO_T));
               #endif
               DBG_LOG_PRINT(("[MENU][%s %d] ssid[0] = %s\n",__FUNCTION__,__LINE__,t_essList_tmp.p_EssInfo[0].t_Ssid.ui1_aSsid));
                break;
            }
        }
    }while(0);

    if(ui1_max_ap_num > (UINT8)t_essList_tmp.ui4_NumberOfItems)
    {
        ui1_max_ap_num = (UINT8)t_essList_tmp.ui4_NumberOfItems;
    }

    pt_page_data->t_essList.ui4_NumberOfItems = t_essList_tmp.ui4_NumberOfItems;
    if(pt_page_data->t_essList.p_EssInfo != NULL)
    {
        c_mem_free(pt_page_data->t_essList.p_EssInfo);
    }

    pt_page_data->t_essList.p_EssInfo = (NET_802_11_ESS_INFO_T*)c_mem_alloc(sizeof(NET_802_11_ESS_INFO_T)*(t_essList_tmp.ui4_NumberOfItems));

    if(pt_page_data->t_essList.p_EssInfo == NULL)
    {
        DBG_ERROR(("%s,%d,c_mem_alloc() for device fail!\n",
                    __FILE__, __LINE__));
        return MENUR_OUT_OF_MEMORY;
    }

    c_memcpy(pt_page_data->t_essList.p_EssInfo, t_essList_tmp.p_EssInfo, sizeof(NET_802_11_ESS_INFO_T)*(t_essList_tmp.ui4_NumberOfItems));

    for (ui1_idx = 0; ui1_idx < ui1_max_ap_num; ui1_idx++)
    {
        p_essInfo = &t_essList_tmp.p_EssInfo[ui1_idx];

        if(p_essInfo->t_Ssid.ui1_aSsid[0] == 0)
        {
            DBG_WARN(("%s,%d,ui1_idx=%d,SsidLen=%d,aSsid =%s.Skip this Ssid\n",
                       __FILE__, __LINE__,
                       ui1_idx,
                       p_essInfo->t_Ssid.ui4_SsidLen,
                       p_essInfo->t_Ssid.ui1_aSsid));
            continue;
        }

        if (_is_filter_out_ssid(p_essInfo->t_Ssid.ui1_aSsid))
        {
            continue;
        }

        if(p_essInfo->i4_isConnected != 0 && b_wireless_connected)
        {
            pt_page_data->aui1_ap_map[0] = ui1_idx;
            continue;
        }

        if(pt_page_data->ui1_ap_num < ui1_visiable_ap_num - 1)
        {
            if (0 == ui1_idx)
            {
                MENU_LOG_ON_FAIL(_add_ap_list_elem(b_wireless_connected,
                                                   &p_essInfo->t_Ssid,
                                                   p_essInfo->i2_Level,
                                                   p_essInfo->e_AuthMode,
                                                   p_essInfo->e_AuthCipher));
            }
            else
            {
               MENU_LOG_ON_FAIL( _add_ap_list_elem(FALSE,
                                                   &p_essInfo->t_Ssid,
                                                   p_essInfo->i2_Level,
                                                   p_essInfo->e_AuthMode,
                                                   p_essInfo->e_AuthCipher));
            }

            MENU_LOG_ON_FAIL(menu_ap_list_page_add_ap(p_essInfo,
                                              ui1_idx,
                                              b_wireless_connected));

            pt_page_data->aui1_ap_map[pt_page_data->ui1_ap_num] = ui1_idx;
            pt_page_data->ui1_ap_num++;
        }
        else if(pt_page_data->ui1_ap_num == ui1_visiable_ap_num -1)
        {
            /*Find the 5th AP*/
            pt_page_data->aui1_ap_map[pt_page_data->ui1_ap_num] = ui1_idx;
            pt_page_data->ui1_ap_num++;
        }
        else
        {
            /*More than than 5 AP*/
            break;
        }
    }

    if (ui1_idx < ui1_max_ap_num)
    {
        CHIPSET chipset = menu_common_get_chipset();
        /*More than than 5 AP*/
        if ((chipset == CHIPSET_5691) || (chipset == CHIPSET_5695) || (chipset == CHIPSET_5695L))
        {
            SET_RECT_BY_SIZE(&t_rect,
                             MENU_ITEM_V_INSET_L,
                             NW_ITEM_V_HEIGHT * 2,
                             MENU_ITEM_V_WIDE,
                             NW_ITEM_V_HEIGHT* (WLAN_AP_LB_ELEM_NUM -1));
        }
        else if (chipset == CHIPSET_5583)
        {
            SET_RECT_BY_SIZE(&t_rect,
                            MENU_ITEM_V_INSET_L,
                            NW_ITEM_V_HEIGHT,
                            MENU_ITEM_V_WIDE,
                            NW_ITEM_V_HEIGHT* (WLAN_AP_LB_ELEM_NUM -1));
        }

        i4_ret = c_wgl_move(pt_page_data->h_lb_ap_list,&t_rect,WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        /*add date to More Access Point page. current only search the connected idx.*/

        /*The 5th AP*/
        p_essInfo = &t_essList_tmp.p_EssInfo[pt_page_data->aui1_ap_map[ui1_visiable_ap_num -1]];
        i4_ret = menu_ap_list_page_add_ap(p_essInfo,
                                          pt_page_data->aui1_ap_map[ui1_visiable_ap_num -1],
                                          b_wireless_connected);
        MENU_LOG_ON_FAIL(i4_ret);

        for (ui1_idx = ui1_idx; ui1_idx < ui1_max_ap_num; ui1_idx++)
        {
            p_essInfo = &t_essList_tmp.p_EssInfo[ui1_idx];

            if(p_essInfo->t_Ssid.ui4_SsidLen == 0)
            {
                continue;
            }

            if (_is_filter_out_ssid(p_essInfo->t_Ssid.ui1_aSsid))
            {
                continue;
            }

            if(p_essInfo->i4_isConnected != 0)
            {
                pt_page_data->aui1_ap_map[0] = ui1_idx;
                continue;
            }

            i4_ret = menu_ap_list_page_add_ap(p_essInfo,
                                              ui1_idx,
                                              b_wireless_connected);
            MENU_LOG_ON_FAIL(i4_ret);

            if (pt_page_data->ui1_ap_num > (WLAN_AP_LB_MAX_NUM-1))  /*Fix Klocwork warning*/
            {
                break;
            }

            pt_page_data->aui1_ap_map[pt_page_data->ui1_ap_num] = ui1_idx;
            pt_page_data->ui1_ap_num++;
        }

        i4_ret = c_wgl_set_visibility(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(ui1_max_ap_num >= ui1_visiable_ap_num)
    {
        if(pt_page_data->ui1_ap_num == ui1_visiable_ap_num)
        {
            /*Only 5 AP*/
            p_essInfo = &t_essList_tmp.p_EssInfo[pt_page_data->aui1_ap_map[ui1_visiable_ap_num -1]];
            i4_ret = _add_ap_list_elem(FALSE,
                              &p_essInfo->t_Ssid,
                              p_essInfo->i2_Level,
                              p_essInfo->e_AuthMode,
                              p_essInfo->e_AuthCipher);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        i4_ret = c_wgl_set_visibility(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                      WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        CHIPSET chipset = menu_common_get_chipset();
        if ((chipset == CHIPSET_5691) || (chipset == CHIPSET_5695) || (chipset == CHIPSET_5695L))
        {
            SET_RECT_BY_SIZE(&t_rect,
                             MENU_ITEM_V_INSET_L,
                             NW_ITEM_V_HEIGHT * 2,
                             MENU_ITEM_V_WIDE,
                             NW_ITEM_V_HEIGHT* WLAN_AP_LB_ELEM_NUM);
        }
        else if (chipset == CHIPSET_5583)
        {
            SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                             NW_ITEM_V_HEIGHT,
                             MENU_ITEM_V_WIDE,
                             NW_ITEM_V_HEIGHT* WLAN_AP_LB_ELEM_NUM);
        }

        i4_ret = c_wgl_move(pt_page_data->h_lb_ap_list,&t_rect,WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_page_data->h_lb_ap_list,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _update_ap_list_with_local_buf
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
static INT32 _update_ap_list_with_local_buf(VOID)
{
    INT32                   i4_ret;
    NW_PAGE_DATA_T*         pt_page_data = &t_nw_page_data;

    UINT8                   ui1_idx = 0;

    NET_802_11_ESS_INFO_T*  p_essInfo = NULL;
    NET_802_11_BSS_INFO_T   t_CurrBss;

    UINT8                   ui1_max_ap_num = WLAN_AP_LB_MAX_NUM;
    UINT8                   ui1_visiable_ap_num = WLAN_AP_LB_ELEM_NUM;
    GL_RECT_T               t_rect;
    BOOL                    b_wireless_connected = FALSE;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list, WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_ap_list_page_clean_ap_list();
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(pt_page_data->aui1_ap_map, 0 , sizeof(pt_page_data->aui1_ap_map));
    pt_page_data->ui1_ap_num = 0;

    i4_ret = c_wgl_set_visibility(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    if(i4_ret != NWR_OK)
    {
        MENU_LOG_ON_FAIL(i4_ret);
        c_memset(t_CurrBss.t_Bssid, 0, sizeof(t_CurrBss.t_Bssid));
        t_CurrBss.t_Ssid.ui4_SsidLen = 0;
    }

    if ((t_CurrBss.t_Ssid.ui4_SsidLen > 0)
        &&((UINT8)WLAN_WPA_COMPLETED == t_CurrBss.u8_wpa_status))
    {
        b_wireless_connected = TRUE;
    }

    DBG_LOG_PRINT(("\n%s,%d,from middleware:pt_page_data->t_essList.ui4_NumberOfItems=%d,u8_wpa_status=%d,"
                "t_CurrBss.t_Ssid.ui4_SsidLen=%d,t_CurrBss.t_Ssid.ui1_aSsid=%s,\n",
               __FUNCTION__, __LINE__,
               pt_page_data->t_essList.ui4_NumberOfItems, t_CurrBss.u8_wpa_status,
               t_CurrBss.t_Ssid.ui4_SsidLen, t_CurrBss.t_Ssid.ui1_aSsid));

    if (pt_page_data->t_essList.ui4_NumberOfItems == 0 ||
        pt_page_data->t_essList.p_EssInfo == NULL)
    {
        return MENUR_OK;
    }

    if (ui1_max_ap_num > (UINT8)pt_page_data->t_essList.ui4_NumberOfItems)
    {
        ui1_max_ap_num = (UINT8)pt_page_data->t_essList.ui4_NumberOfItems;
    }

    for (ui1_idx = 0; ui1_idx < ui1_max_ap_num; ui1_idx++)
    {
        p_essInfo = &pt_page_data->t_essList.p_EssInfo[ui1_idx];

        if (p_essInfo->t_Ssid.ui4_SsidLen == 0 ||
            p_essInfo->t_Ssid.ui1_aSsid[0] == 0)
        {
            DBG_LOG_PRINT(("\n%s,%d,ui1_idx=%d,SsidLen=%d,aSsid =%s.Skip this Ssid\n",
                       __FILE__, __LINE__,
                       ui1_idx,
                       p_essInfo->t_Ssid.ui4_SsidLen,
                       p_essInfo->t_Ssid.ui1_aSsid));
            continue;
        }

        if (_is_filter_out_ssid(p_essInfo->t_Ssid.ui1_aSsid))
        {
            continue;
        }

        if (p_essInfo->i4_isConnected != 0 && b_wireless_connected)
        {
            pt_page_data->aui1_ap_map[0] = ui1_idx;
            continue;
        }

        if (pt_page_data->ui1_ap_num < ui1_visiable_ap_num -1)
        {
            if (0 == ui1_idx)
            {
                i4_ret = _add_ap_list_elem(b_wireless_connected,
                                           &p_essInfo->t_Ssid,
                                           p_essInfo->i2_Level,
                                           p_essInfo->e_AuthMode,
                                           p_essInfo->e_AuthCipher);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = _add_ap_list_elem(FALSE,
                                           &p_essInfo->t_Ssid,
                                           p_essInfo->i2_Level,
                                           p_essInfo->e_AuthMode,
                                           p_essInfo->e_AuthCipher);
                MENU_LOG_ON_FAIL(i4_ret);
            }

            i4_ret = menu_ap_list_page_add_ap(p_essInfo,
                                              ui1_idx,
                                              b_wireless_connected);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_page_data->aui1_ap_map[pt_page_data->ui1_ap_num] = ui1_idx;
            pt_page_data->ui1_ap_num++;
        }
        else if(pt_page_data->ui1_ap_num == ui1_visiable_ap_num -1)
        {
            /*Find the 5th AP*/
            pt_page_data->aui1_ap_map[pt_page_data->ui1_ap_num] = ui1_idx;
            pt_page_data->ui1_ap_num++;
        }
        else
        {
            /*More than than 5 AP*/
            break;
        }
    }

    if (ui1_idx < ui1_max_ap_num)
    {
        /*More than than 5 AP*/
        SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_INSET_L,
                         NW_ITEM_V_HEIGHT * 2,
                         MENU_ITEM_V_WIDE,
                         NW_ITEM_V_HEIGHT* (WLAN_AP_LB_ELEM_NUM -1));

        i4_ret = c_wgl_move(pt_page_data->h_lb_ap_list,&t_rect,WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);

        /*add date to More Access Point page. current only search the connected idx.*/

        /*The 5th AP*/
        p_essInfo = &pt_page_data->t_essList.p_EssInfo[pt_page_data->aui1_ap_map[ui1_visiable_ap_num -1]];
        i4_ret = menu_ap_list_page_add_ap(p_essInfo,
                                          pt_page_data->aui1_ap_map[ui1_visiable_ap_num -1],
                                          b_wireless_connected);
        MENU_LOG_ON_FAIL(i4_ret);

        for (ui1_idx = ui1_idx; ui1_idx < ui1_max_ap_num; ui1_idx++)
        {
            p_essInfo = &pt_page_data->t_essList.p_EssInfo[ui1_idx];

            if(p_essInfo->t_Ssid.ui4_SsidLen == 0)
            {
                continue;
            }

            if (_is_filter_out_ssid(p_essInfo->t_Ssid.ui1_aSsid))
            {
                continue;
            }

            if(p_essInfo->i4_isConnected != 0)
            {
                pt_page_data->aui1_ap_map[0] = ui1_idx;
                continue;
            }

            i4_ret = menu_ap_list_page_add_ap(p_essInfo,
                                              ui1_idx,
                                              b_wireless_connected);
            MENU_LOG_ON_FAIL(i4_ret);

            if (pt_page_data->ui1_ap_num > (WLAN_AP_LB_MAX_NUM-1))  /*Fix Klocwork warning*/
            {
                break;
            }

            pt_page_data->aui1_ap_map[pt_page_data->ui1_ap_num] = ui1_idx;
            pt_page_data->ui1_ap_num++;
        }

        i4_ret = c_wgl_set_visibility(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if (ui1_max_ap_num >= ui1_visiable_ap_num)
    {
        if (pt_page_data->ui1_ap_num == ui1_visiable_ap_num)
        {
            /*Only 5 AP*/
            p_essInfo = &pt_page_data->t_essList.p_EssInfo[pt_page_data->aui1_ap_map[ui1_visiable_ap_num -1]];
            i4_ret = _add_ap_list_elem(FALSE,
                              &p_essInfo->t_Ssid,
                              p_essInfo->i2_Level,
                              p_essInfo->e_AuthMode,
                              p_essInfo->e_AuthCipher);
            MENU_LOG_ON_FAIL(i4_ret);
        }

        i4_ret = c_wgl_set_visibility(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                      WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_INSET_L,
                         NW_ITEM_V_HEIGHT * 2,
                         MENU_ITEM_V_WIDE,
                         NW_ITEM_V_HEIGHT* WLAN_AP_LB_ELEM_NUM);

        i4_ret = c_wgl_move(pt_page_data->h_lb_ap_list,&t_rect,WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_page_data->h_lb_ap_list,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _start_scan_ap
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
static INT32 _start_scan_ap(VOID)
{
    INT32           i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    NW_WLAN_STATE_T e_wlan_state = NW_WLAN_UNPLUG;
    WGL_IMG_INFO_T  t_img_info;

    pt_page_data->b_finish = FALSE;
    pt_page_data->b_connec_timer = FALSE;
    pt_page_data->b_timer_result = FALSE;
    pt_page_data->b_wps_associate = FALSE;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list, WGL_CMD_LB_DEL_ALL, NULL, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_ap_list_page_clean_ap_list();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->ui1_ap_num = 0;
    if(pt_page_data->t_essList.p_EssInfo != NULL)
    {
        c_mem_free(pt_page_data->t_essList.p_EssInfo);

        pt_page_data->t_essList.p_EssInfo = NULL;
        pt_page_data->t_essList.ui4_NumberOfItems = 0;
    }

    MENU_LOG_ON_FAIL(a_nw_wlan_status(&e_wlan_state));

    DBG_LOG_PRINT(("\n%s,%s,%d,e_wlan_state=%d,wifi_start=%d\n",
               __FILE__, __FUNCTION__, __LINE__, e_wlan_state,
               (UINT32)a_nw_custom_nw_wifi_start()));

    if (NW_WLAN_PLUG_STOP == e_wlan_state)
    {
        a_nw_chg_network_interface(NW_NET_INTERFACE_WIFI);
    }

    if((e_wlan_state == NW_WLAN_START_DISASSOC)||
       (e_wlan_state == NW_WLAN_ASSOCIATE)||
       (e_wlan_state == NW_WLAN_ASSOCIATING))
    {
        /* to judge supplicant is ready or not. if not ready, do not start wlan scan. */
        if (a_nw_custom_nw_wifi_start())
        {
            MENU_LOG_ON_FAIL(a_nw_wlan_scan());
        }
    }

    /* disable the menu timer */
    menu_timer_enable(FALSE);
    menu_timer_stop();

    /* init the animation count as 0*/
    pt_page_data->ui1_animation_count = 0;

    ui1_g_img_idx += 1;
    if (ui1_g_img_idx > (NW_ANIMATION_IMG_MAX_NUM - 1))
    {
        ui1_g_img_idx = 0;
    }

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_g_img_animation[ui1_g_img_idx];
    t_img_info.u_img_data.t_standard.t_enable = h_g_img_animation[ui1_g_img_idx];
    t_img_info.u_img_data.t_standard.t_highlight = h_g_img_animation[ui1_g_img_idx];

    i4_ret = c_wgl_do_cmd(h_g_img_icon,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    _nw_img_animation_show(TRUE);

    c_timer_start(pt_page_data->h_timer, 1000, X_TIMER_FLAG_ONCE, _nw_timer_cb_fct, NULL);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _update_all_items
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
static INT32 _update_all_items(VOID)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    UINT32       ui4_i;

    UINT8       aui1_item_idx_1[NW_PAGE_ID_LAST_ENTRY] = ARRY_NW_PAGE_ITEM_IDX_1;
    UINT8       aui1_item_idx_2[NW_PAGE_ID_LAST_ENTRY] = ARRY_NW_PAGE_ITEM_IDX_2;
    UINT8*      paui1_item_idx = &aui1_item_idx_1[0];
    GL_RECT_T   t_rect;

    CHIPSET chipset = menu_common_get_chipset();
    if ((chipset == CHIPSET_5691) || (chipset == CHIPSET_5695) || (chipset == CHIPSET_5695L))
    {
        MENU_LOG_ON_FAIL(_set_connection_txt_title(MLM_MENU_KEY_NET_WIR_CON_TIT));
        MENU_LOG_ON_FAIL(_update_network_wired_connection());
    }

    if(pt_page_data->b_wired_plug)
    {
        paui1_item_idx = &aui1_item_idx_2[0];

        MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_data->h_txt_ap_list_tit,
                                              WGL_SW_HIDE));

        MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_data->h_lb_ap_list,
                                              WGL_SW_HIDE));

        MENU_LOG_ON_FAIL( c_wgl_set_visibility(pt_page_data->h_wps,
                                      WGL_SW_HIDE));
    }
    else
    {
        MENU_LOG_ON_FAIL(_set_ap_list_title_text(MLM_MENU_KEY_NET_AP_LIST_TIT_AP));

        MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_data->h_txt_ap_list_tit,
                                              WGL_SW_NORMAL));

#ifdef APP_NW_WPS_SUPPORT
        MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_data->h_wps,
                                              WGL_SW_NORMAL));
#else
        MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_data->h_wps,
                                              WGL_SW_HIDE));
#endif
    }

    for(ui4_i = 0; ui4_i<NW_PAGE_ID_LAST_ENTRY; ui4_i++ )
    {
        if(paui1_item_idx[ui4_i]!= 0)
        {
            if ((chipset == CHIPSET_5691) || (chipset == CHIPSET_5695) || (chipset == CHIPSET_5695L))
            {
                SET_RECT_BY_SIZE(&t_rect,
                                 MENU_ITEM_V_INSET_L,
                                 NW_ITEM_V_HEIGHT * paui1_item_idx[ui4_i],
                                 MENU_ITEM_V_WIDE,
                                 NW_ITEM_V_HEIGHT);
            }
            else if (chipset == CHIPSET_5583)
            {
                SET_RECT_BY_SIZE(&t_rect,
                                 MENU_ITEM_V_INSET_L,
                                 NW_ITEM_V_HEIGHT * (paui1_item_idx[ui4_i]-1),
                                 MENU_ITEM_V_WIDE,
                                 NW_ITEM_V_HEIGHT);
            }

            MENU_LOG_ON_FAIL(c_wgl_move(pt_page_data->at_item[ui4_i].h_subpage,&t_rect,WGL_NO_AUTO_REPAINT));

            MENU_LOG_ON_FAIL(menu_action_chg_lang(pt_page_data->at_item[ui4_i].h_subpage,
                                         pt_page_data->at_item[ui4_i].ui2_msgid_title,
                                         MLM_MENU_KEY_EMPTY));

            if(ui4_i != NW_PAGE_ID_AP_LST)
            {
                MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_data->at_item[ui4_i].h_subpage,
                                                      WGL_SW_NORMAL));
                if(ui4_i == NW_PAGE_ID_MAN_SET)
                {
                    INT32 i4_ret = MENUR_OK;
                    NW_IP_INFO_T t_net_ip_info;
                    NW_IPV6_INFO_T  t_net_ipv6_info;
                    c_memset(&t_net_ip_info, 0, sizeof(t_net_ip_info));
                    c_memset(&t_net_ipv6_info, 0, sizeof(t_net_ipv6_info));

                    /* Get IPv4 Info */
                    i4_ret = a_nw_get_crnt_ip_info(&t_net_ip_info);
                    MENU_LOG_ON_FAIL(i4_ret);

                    /* Get Ipv6 Info */
                    i4_ret = a_nw_get_v6_info(&t_net_ipv6_info);
                    MENU_LOG_ON_FAIL(i4_ret);

                    if(0 == t_net_ip_info.ui4_address && 0 != c_strlen(t_net_ipv6_info.ac_v6ip))
                    {
                        c_wgl_enable(pt_page_data->at_item[NW_PAGE_ID_MAN_SET].h_subpage, FALSE);
                        b_ipv6_only = TRUE;
                        DBG_LOG_PRINT(("%s %d Grayout manual setup item\n",__FUNCTION__,__LINE__));
                    }
                    else
                    {
                        c_wgl_enable(pt_page_data->at_item[NW_PAGE_ID_MAN_SET].h_subpage, TRUE);
                        b_ipv6_only = FALSE;
                        DBG_LOG_PRINT(("%s %d Enable manual setup item\n",__FUNCTION__,__LINE__));
                    }
                }
            }
        }
        else
        {
            MENU_LOG_ON_FAIL(c_wgl_set_visibility(pt_page_data->at_item[ui4_i].h_subpage,
                                                  WGL_SW_HIDE));
        }
    }

    /* update last shadow position after all item update complete */
    MENU_LOG_ON_FAIL(menu_network_last_shadow_update_position(
                    pt_page_data->at_item[NW_PAGE_ID_NET_INFO].h_subpage,
                    FALSE));

    if(!pt_page_data->b_wired_plug)
    {
        /*force show the page before the anim icon show.*/
        MENU_LOG_ON_FAIL(c_wgl_repaint(pt_page_data->h_cnt_frm, NULL, FALSE));
        MENU_LOG_ON_FAIL(_start_scan_ap());
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _item_subpage_handle_cursor_up_and_dow
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_subpage_handle_cursor_up_and_dow(HANDLE_T    h_widget,
                                                    BOOL        b_cursor_up)
{
    INT32           i4_ret;
    UINT32          ui4_item_id = 0;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(&ui4_item_id),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    if(ui4_item_id >= NW_PAGE_ID_LAST_ENTRY)
    {
        return MENUR_INV_STATE;
    }

    if(pt_page_data->b_wired_plug)
    {
        if(b_cursor_up)
        {
            if(ui4_item_id == (UINT32)NW_PAGE_ID_TEST)
            {
                MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            }
            else if(ui4_item_id == (UINT32)NW_PAGE_ID_NET_INFO)
            {
                if(b_ipv6_only == TRUE)
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage,
                                             WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_MAN_SET].h_subpage,
                                             WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
            else
            {
                i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            if(ui4_item_id == (UINT32)NW_PAGE_ID_NET_INFO)
            {
                MENU_LOG_ON_FAIL (menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE));

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(ui4_item_id == (UINT32)NW_PAGE_ID_TEST)
            {
                if(b_ipv6_only == TRUE)
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_NET_INFO].h_subpage,
                                             WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_MAN_SET].h_subpage,
                                             WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            }
            else
            {
                i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_NET_INFO].h_subpage,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);

            }
        }
    }
    else
    {
        if(b_cursor_up)
        {
            if(ui4_item_id == NW_PAGE_ID_AP_LST)
            {
                i4_ret = c_wgl_set_focus(pt_page_data->h_lb_ap_list,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(ui4_item_id == (UINT32)NW_PAGE_ID_MAN_SET && pt_page_data->ui1_ap_num == 0)
            {
                MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            }
            else if(ui4_item_id == NW_PAGE_ID_TEST)
            {
            #ifdef APP_NW_WPS_SUPPORT
                i4_ret = c_wgl_set_focus(pt_page_data->h_wps,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            #else
                if(pt_page_data->ui1_ap_num > WLAN_AP_LB_ELEM_NUM )
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                        WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    i4_ret = c_wgl_set_focus(pt_page_data->h_lb_ap_list,
                                         WGL_SYNC_AUTO_REPAINT);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            #endif
            }
            else if(ui4_item_id == NW_PAGE_ID_NET_INFO && b_ipv6_only == TRUE)
            {
                i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_AP_NAME].h_subpage,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_set_focus(pt_page_data->at_item[ui4_item_id - 1].h_subpage,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
        else
        {
            if(ui4_item_id == NW_PAGE_ID_NET_INFO) //add network info
            {
                MENU_LOG_ON_FAIL (menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE));

                i4_ret = menu_pm_repaint();
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if(ui4_item_id == NW_PAGE_ID_AP_LST)
            {
            #ifdef APP_NW_WPS_SUPPORT
                i4_ret = c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
            #else
                i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage, WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            #endif
            }
            else if(ui4_item_id == NW_PAGE_ID_AP_NAME && b_ipv6_only == TRUE)
            {
                i4_ret = c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_NET_INFO].h_subpage,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else
            {
                i4_ret = c_wgl_set_focus(pt_page_data->at_item[ui4_item_id + 1].h_subpage,
                                         WGL_SYNC_AUTO_REPAINT);
                MENU_LOG_ON_FAIL(i4_ret);
            }
        }
    }

    return i4_ret;
}

//dolphin 20200401 export forget ssid
INT32 a_menu_network_forget_temporary_ssid(VOID)
{
    INT32  i4_ret=-1;
#ifdef APP_NETWORK_WIFI_SUPPORT
    do{
        i4_ret = a_nw_custom_wlan_disassociate();
        if (i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n", __FILE__, __FUNCTION__, __LINE__, i4_ret));
            break;
        }
        _wlan_update_associate();
    }while(0);
#endif
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _nw_pwd_confirm_dialog_forget_cb_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nw_forget_network_confirm_dialog_forget_cb_fct(UINT32 ui4_key_code)
{
    INT32           i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    #ifdef NEVER
    if ((BTN_CURSOR_LEFT  == ui4_key_code) ||
    BTN_CURSOR_RIGHT == ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_another();
    }
    #endif
    if(BTN_CURSOR_LEFT == ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_another();
    }
    else if(BTN_CURSOR_RIGHT== ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_again();
    }
    else if(BTN_SELECT  == ui4_key_code)
    {
        #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
        #endif
        menu_network_hide_confirm_dialog(TRUE);

        #ifdef APP_NETWORK_WIFI_SUPPORT
        i4_ret = a_nw_custom_wlan_disassociate();
        if (i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d\n",
            __FILE__, __FUNCTION__, __LINE__, i4_ret));
        }
        #endif
        _wlan_update_associate();
        c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_SYNC_AUTO_REPAINT);
    }
    else
    {
        #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
        #endif

        menu_network_hide_confirm_dialog(TRUE);
        c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_SYNC_AUTO_REPAINT);
    }
}
/*----------------------------------------------------------------------------
 * Name: _nw_pwd_confirm_dialog_cancel_cb_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nw_forget_network_confirm_dialog_cancel_cb_fct(UINT32 ui4_key_code)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    if(BTN_CURSOR_LEFT == ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_another();
    }
    else if(BTN_CURSOR_RIGHT== ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_again();
    }

    else
    {
        #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
        #endif

        menu_network_hide_confirm_dialog(TRUE);
        c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_SYNC_AUTO_REPAINT);
    }
}
/*----------------------------------------------------------------------------
 * Name: _lb_ap_list_is_index_wifi_connect
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static BOOL _lb_ap_list_is_index_wifi_connect(UINT16 ui2_idx)
{
    NW_WLAN_STATE_T  e_wlan_state = NW_WLAN_UNPLUG;
    WGL_HIMG_TPL_T   h_img = NULL_HANDLE;
    INT32  i4_ret = MENUR_OK;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    if(ui2_idx == 0)
    {
        i4_ret = a_nw_wlan_status(&e_wlan_state);
        MENU_LOG_ON_FAIL(i4_ret);

        if(e_wlan_state == NW_WLAN_ASSOCIATE)
        {
            i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list,
                                WGL_CMD_LB_GET_ITEM_IMAGE,
                                WGL_PACK_2(0, 0),
                                WGL_PACK(&h_img));

            if(i4_ret == WGLR_OK && h_img != NULL_HANDLE)
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        return FALSE;
    }
}
/*----------------------------------------------------------------------------
 * Name: _lb_ap_list_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _lb_ap_list_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    ISO_639_LANG_T          s639_lang;
    UINT16                  ui2_lang_idx = 0;
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        INT32  i4_ret = MENUR_OK;
        UINT16 ui2_idx = 0;

        i4_ret = c_wgl_do_cmd (h_widget,
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK (&ui2_idx),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        if(_lb_ap_list_is_index_wifi_connect(ui2_idx))
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_FORGET_NETWORK_HELP_TEXT));
        }
        else
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_AP_LIST));
        }

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_text[128] = {0};

        i4_ret = c_wgl_do_cmd(h_widget,
                         WGL_CMD_LB_GET_ITEM_TEXT,
                         WGL_PACK_2(ui2_idx, 1),
                         WGL_PACK(w2s_text));
        MENU_LOG_ON_FAIL(i4_ret);

        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    #endif

        return WGLR_OK;
    }
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_UP:
        {
            INT32  i4_ret = MENUR_OK;
            UINT16 ui2_idx = 0;

            i4_ret = c_wgl_do_cmd (h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK (&ui2_idx),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui2_idx == 0)
            {
                MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
                return WGLR_OK;
            }
            else
            {
                i4_ret = c_wgl_do_cmd (h_widget,
                                  WGL_CMD_LB_HLT_PREV_ELEM,
                                  WGL_PACK (TRUE),
                                  NULL);
                MENU_LOG_ON_FAIL(i4_ret);
                if(_lb_ap_list_is_index_wifi_connect(ui2_idx-1))
                {
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_FORGET_NETWORK_HELP_TEXT));
                }
                else
                {
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_AP_LIST));
                }
            }

        #ifdef APP_TTS_SUPPORT
            UTF16_T w2s_text[128] = {0};

            i4_ret = c_wgl_do_cmd (h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK (&ui2_idx),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(h_widget,
                             WGL_CMD_LB_GET_ITEM_TEXT,
                             WGL_PACK_2(ui2_idx, 1),
                             WGL_PACK(w2s_text));
            MENU_LOG_ON_FAIL(i4_ret);

            a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
        #endif

            return WGLR_OK;
        }
        case BTN_CURSOR_DOWN:
        {
            INT32  i4_ret = MENUR_OK;
            UINT16 ui2_ap_num = 0;
            UINT16 ui2_idx = 0;

            i4_ret = c_wgl_do_cmd (h_widget,
                              WGL_CMD_LB_GET_ELEM_NUM,
                              WGL_PACK (&ui2_ap_num),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd (h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK (&ui2_idx),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui2_idx == ui2_ap_num - 1)
            {
                if(pt_page_data->ui1_ap_num > WLAN_AP_LB_ELEM_NUM )
                {
                    c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_AP_LST].h_subpage, WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
                #ifdef APP_NW_WPS_SUPPORT
                    c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
                #else
                    c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage, WGL_SYNC_AUTO_REPAINT);
                #endif
                }
            }
            else
            {
                i4_ret = c_wgl_do_cmd (h_widget,
                                  WGL_CMD_LB_HLT_NEXT_ELEM,
                                  WGL_PACK (TRUE),
                                  NULL);
                MENU_LOG_ON_FAIL(i4_ret);
                if(_lb_ap_list_is_index_wifi_connect(ui2_idx))
                {
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_AP_LIST));
                }

            #ifdef APP_TTS_SUPPORT
                UTF16_T w2s_text[128] = {0};

                i4_ret = c_wgl_do_cmd (h_widget,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK (&ui2_idx),
                                  NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_wgl_do_cmd(h_widget,
                                 WGL_CMD_LB_GET_ITEM_TEXT,
                                 WGL_PACK_2(ui2_idx, 1),
                                 WGL_PACK(w2s_text));
                MENU_LOG_ON_FAIL(i4_ret);

                a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
            #endif
            }

            return WGLR_OK;
        }
        case BTN_SELECT:
        {
            INT32  i4_ret = MENUR_OK;
            UINT16 ui2_idx = 0;
            WGL_IMG_INFO_T    t_img_info;

            NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
            NET_802_11_ASSOCIATE_T* pt_associate = &pt_page_data->t_associate;
            NET_802_11_ESS_LIST_T* pt_essList = &pt_page_data->t_essList;

            NET_802_11_ESS_INFO_T  *p_essInfo = NULL;
            NW_WLAN_STATE_T  e_wlan_state = NW_WLAN_UNPLUG;
            WGL_HIMG_TPL_T   h_img = NULL_HANDLE;
            UTF16_T w2s_title[128+1] = {0};
            UTF16_T w2s_ssid[2*NET_802_11_MAX_LEN_SSID + 1] = {0};

            if(ui4_msg == WGL_MSG_KEY_REPEAT)
            {
                return WGLR_OK;
            }

            i4_ret = c_wgl_do_cmd (h_widget,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK (&ui2_idx),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui2_idx > pt_page_data->ui1_ap_num)
            {
                DBG_INFO(("\n%s,%d,ui1_ap_num=%d,ui2_idx= %d\n",
                          __FILE__, __LINE__,
                          pt_page_data->ui1_ap_num,
                          ui2_idx));
                return MENUR_ITEM_NOT_FOUND;
            }
            i4_ret = a_cfg_get_gui_lang(s639_lang);
            if(i4_ret != APP_CFGR_OK)
            {
                DBG_INFO(("[%s,%d]a_cfg_get_gui_lang failed\n",__FILE__, __LINE__));
            }
            if(c_strncmp(s639_lang,"eng",3) ==0)
            {
                ui2_lang_idx = 0; /*ENG*/
            }
            else if(c_strncmp(s639_lang,"fre",3) ==0)
            {
                ui2_lang_idx = 1; /*FRE*/
            }
            else if(c_strncmp(s639_lang,"spa",3) ==0)
            {
                ui2_lang_idx = 2; /*SPA*/
            }
            else
            {
                ui2_lang_idx = 0; /*ENG*/
            }

            /* 1st ap is associated */
            if(ui2_idx == 0)
            {
                i4_ret = a_nw_wlan_status(&e_wlan_state);
                MENU_LOG_ON_FAIL(i4_ret);

                if(e_wlan_state == NW_WLAN_ASSOCIATE)
                {
                    i4_ret = c_wgl_do_cmd(pt_page_data->h_lb_ap_list,
                                          WGL_CMD_LB_GET_ITEM_IMAGE,
                                          WGL_PACK_2(0, 0),
                                          WGL_PACK(&h_img));

                    if(i4_ret == WGLR_OK && h_img != NULL_HANDLE)
                    {
                        ui2_idx = pt_page_data->aui1_ap_map[ui2_idx];
                        p_essInfo = &pt_essList->p_EssInfo[ui2_idx];
                        c_uc_w2s_strncpy(w2s_title, MLM_MENU_TEXT(ui2_lang_idx,MLM_MENU_KEY_FORGET_NETWORK_TITLE),128);

                        c_uc_ps_to_w2s(p_essInfo->t_Ssid.ui1_aSsid,w2s_ssid, 2*NET_802_11_MAX_LEN_SSID);
                        c_uc_w2s_strncat(w2s_title, w2s_ssid,(128 - c_uc_w2s_strlen(MLM_MENU_TEXT(ui2_lang_idx,MLM_MENU_KEY_FORGET_NETWORK_TITLE))));//MENU_TEXT(MLM_MENU_KEY_FORGET_NETWORK_TITLE)
                        i4_ret = menu_network_show_confirm_dialog_ex(w2s_title,
                                                                    MLM_MENU_TEXT(ui2_lang_idx,MLM_MENU_KEY_FORGET_NETWORK_CANCEL),   //MENU_TEXT(MLM_MENU_KEY_FORGET_NETWORK_FORGET),
                                                                    MLM_MENU_TEXT(ui2_lang_idx,MLM_MENU_KEY_FORGET_NETWORK_FORGET),   //MENU_TEXT(MLM_MENU_KEY_FORGET_NETWORK_CANCEL),
                                                                    _nw_forget_network_confirm_dialog_cancel_cb_fct,
                                                                    _nw_forget_network_confirm_dialog_forget_cb_fct,
                                                                    TRUE);
                        break;
                    }
                }
            }

            ui2_idx = pt_page_data->aui1_ap_map[ui2_idx];

            if((UINT32)ui2_idx >pt_essList->ui4_NumberOfItems)
            {
                DBG_INFO(("\n%s,%d,ui4_NumberOfItems=%d, ui2_idx=%d\n",
                          __FILE__, __LINE__,
                          pt_essList->ui4_NumberOfItems,
                          ui2_idx));
                return MENUR_ITEM_NOT_FOUND;
            }

            p_essInfo = &pt_essList->p_EssInfo[ui2_idx];

            c_memset(pt_associate,0, sizeof(NET_802_11_ASSOCIATE_T));

            pt_associate->t_Ssid      = p_essInfo->t_Ssid;
            c_memcpy(pt_associate->t_Bssid,p_essInfo->t_Bssid, sizeof(NET_802_11_BSSID_T));

            pt_associate->e_AuthMode  = p_essInfo->e_AuthMode;
            pt_associate->e_AuthCipher= p_essInfo->e_AuthCipher;

            pt_associate->t_Key.b_IsAscii = FALSE;

            if (FALSE == _is_lock_ap(pt_associate->e_AuthMode, pt_associate->e_AuthCipher))
            {
                /*do action*/
                pt_page_data->b_finish = FALSE;
                pt_page_data->b_timer_result = FALSE;
                pt_page_data->b_connec_timer = TRUE;
                pt_page_data->b_wps_associate = FALSE;

                DBG_LOG_PRINT(("\n%s,%s,%d,b_finish=%d,b_timer_result=%d,b_connec_timer=%d\n",
                            __FILE__, __FUNCTION__, __LINE__,
                            pt_page_data->b_finish, pt_page_data->b_timer_result,
                            pt_page_data->b_connec_timer));

                /* init the animation count as 0*/
                pt_page_data->ui1_animation_count = 0;

                ui1_g_img_idx += 1;
                if (ui1_g_img_idx > (NW_ANIMATION_IMG_MAX_NUM - 1))
                {
                    ui1_g_img_idx = 0;
                }

                t_img_info.e_type = WGL_IMG_SET_STANDARD;
                t_img_info.u_img_data.t_standard.t_disable = h_g_img_animation[ui1_g_img_idx];
                t_img_info.u_img_data.t_standard.t_enable = h_g_img_animation[ui1_g_img_idx];
                t_img_info.u_img_data.t_standard.t_highlight = h_g_img_animation[ui1_g_img_idx];

                i4_ret = c_wgl_do_cmd(h_g_img_icon,
                                     WGL_CMD_GL_SET_IMAGE,
                                     WGL_PACK(WGL_IMG_FG),
                                     WGL_PACK(&t_img_info));
                MENU_LOG_ON_FAIL(i4_ret);

                _nw_img_animation_show(TRUE);

                c_timer_start(pt_page_data->h_timer, 1000, X_TIMER_FLAG_ONCE, _nw_timer_cb_fct, NULL);

                /* disable the menu timer */
                menu_timer_enable(FALSE);
                menu_timer_stop();

            #ifdef APP_NETWORK_WIFI_SUPPORT
                i4_ret = a_nw_custom_wlan_disassociate();
                if (i4_ret != NWR_OK)
                {
                    DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d,b_finish=%d,b_timer_result=%d,b_connec_timer=%d\n",
                                __FILE__, __FUNCTION__, __LINE__, i4_ret,
                                pt_page_data->b_finish, pt_page_data->b_timer_result,
                                pt_page_data->b_connec_timer));

                    pt_page_data->b_finish = TRUE;
                }

                i4_ret = a_nw_wlan_associate(&pt_page_data->t_associate);
                if (i4_ret != NWR_OK)
                {
                    DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d,b_finish=%d,b_timer_result=%d,b_connec_timer=%d\n",
                                __FILE__, __FUNCTION__, __LINE__, i4_ret,
                                pt_page_data->b_finish, pt_page_data->b_timer_result,
                                pt_page_data->b_connec_timer));

                    pt_page_data->b_finish = TRUE;
                }
            #endif
            }
            else
            {
                pt_page_data->h_last_focus = pt_page_data->h_lb_ap_list;
                menu_netowrk_nav_go(NW_PAGE_ID_PWD, NULL);
            }

            return WGLR_OK;
        }
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_go_home_menu();
            return WGLR_OK;
        default:
            break;
        }

    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _nw_confirm_dialog_try_again_cb_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nw_confirm_dialog_try_again_cb_fct(UINT32 ui4_key_code)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    BOOL b_visible = FALSE;

    c_wgl_get_visibility(pt_page_data->h_confirm_dialog_try_another,
                          &b_visible);

    if ((BTN_CURSOR_LEFT == ui4_key_code)
        || BTN_CURSOR_RIGHT == ui4_key_code)
    {
        if (b_visible)
        {
            c_wgl_set_focus(pt_page_data->h_confirm_dialog_try_another,
                        WGL_SYNC_AUTO_REPAINT);

        #ifdef APP_TTS_SUPPORT
            UTF16_T    w2s_text[128];

            c_wgl_do_cmd (pt_page_data->h_confirm_dialog_try_another,
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_text),
                          WGL_PACK (128));

            a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
        #endif
        }
    }
    else if (BTN_SELECT == ui4_key_code)
    {
        menu_network_simple_dialog_hide(TRUE);
        menu_network_hide_confirm_dialog(TRUE);

        if (FALSE == pt_page_data->b_connec_timer)
        {
        #ifdef APP_NW_WPS_SUPPORT
            /* scan ap failed and cancel , set focus to WPS btn */
            c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
        #else
            c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage, WGL_SYNC_AUTO_REPAINT);
        #endif
        }
        else if (b_visible)
        {
            /* retry to connect previous ap */
            c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_SYNC_AUTO_REPAINT);

            _lb_ap_list_proc_fct(pt_page_data->h_lb_ap_list,
                             WGL_MSG_KEY_DOWN, (VOID*)BTN_SELECT, NULL);
        }
        else
        {
        #ifdef APP_NW_WPS_SUPPORT
            /* WPS ok button, set focus to WPS btn */
            c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
        #else
            c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage, WGL_SYNC_AUTO_REPAINT);
        #endif
        }
    }
    else if (BTN_RETURN == ui4_key_code)
    {
    #ifdef APP_NW_WPS_SUPPORT
        c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
    #else
        c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage, WGL_SYNC_AUTO_REPAINT);
    #endif
        menu_network_hide_confirm_dialog(TRUE);
    }
    else
    {
        c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_SYNC_AUTO_REPAINT);
        menu_network_simple_dialog_hide(TRUE);
    }
}

VOID nw_confirm_dialog_set_focus_try_again(VOID)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    c_wgl_set_focus(pt_page_data->h_confirm_dialog_try_again,
                        WGL_SYNC_AUTO_REPAINT);

#ifdef APP_TTS_SUPPORT
    UTF16_T    w2s_text[128];

    c_wgl_do_cmd (pt_page_data->h_confirm_dialog_try_again,
                  WGL_CMD_TEXT_GET_TEXT,
                  WGL_PACK (w2s_text),
                  WGL_PACK (128));

    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif

}

VOID nw_confirm_dialog_set_focus_try_another(VOID)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    c_wgl_set_focus(pt_page_data->h_confirm_dialog_try_another,
                        WGL_SYNC_AUTO_REPAINT);

#ifdef APP_TTS_SUPPORT
    UTF16_T    w2s_text[128];

    c_wgl_do_cmd (pt_page_data->h_confirm_dialog_try_another,
                  WGL_CMD_TEXT_GET_TEXT,
                  WGL_PACK (w2s_text),
                  WGL_PACK (128));

    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
#endif

}

static VOID _nw_confirm_dialog_try_another_cb_fct(UINT32 ui4_key_code)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    if (BTN_CURSOR_LEFT  == ui4_key_code||
        BTN_CURSOR_RIGHT == ui4_key_code)
    {
        c_wgl_set_focus(pt_page_data->h_confirm_dialog_try_again,
                        WGL_SYNC_AUTO_REPAINT);

    #ifdef APP_TTS_SUPPORT
        UTF16_T    w2s_text[128];

        c_wgl_do_cmd (pt_page_data->h_confirm_dialog_try_again,
                      WGL_CMD_TEXT_GET_TEXT,
                      WGL_PACK (w2s_text),
                      WGL_PACK (128));

        a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
    #endif
    }
    else if (BTN_SELECT == ui4_key_code ||
             BTN_RETURN == ui4_key_code)
    {
        menu_network_hide_confirm_dialog(TRUE);

        if (FALSE == pt_page_data->b_connec_timer)
        {
#ifdef APP_NW_WPS_SUPPORT
            c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
#else
            c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage, WGL_SYNC_AUTO_REPAINT);
#endif
        }
        else
        {
            c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_SYNC_AUTO_REPAINT);
        }

        /* scan ap failed and try again */
        _start_scan_ap();
    }
    else
    {
        menu_network_hide_confirm_dialog(TRUE);

    #ifdef APP_NW_WPS_SUPPORT
        c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
    #else
        c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage, WGL_SYNC_AUTO_REPAINT);
    #endif
    }
}

/*----------------------------------------------------------------------------
 * Name: _confirm_dialog_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _confirm_dialog_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
        case BTN_CURSOR_LEFT:
        case BTN_CURSOR_RIGHT:
        {
            nw_dialog_cb_fct  pf_back = NULL;
            INT32           i4_ret;

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&pf_back),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(pf_back != NULL)
            {
                pf_back(ui4_keycode);
            }

            return WGLR_OK;
        }
        default:
            break;
        }

        break;
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _item_subpage_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _item_subpage_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    INT32           i4_ret;
    UINT32          ui4_item_id = 0;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_GL_GET_ATTACH_DATA,
                              WGL_PACK(&ui4_item_id),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        if(ui4_item_id >= NW_PAGE_ID_LAST_ENTRY)
        {
            return MENUR_INV_STATE;
        }

        i4_ret = menu_set_and_show_help_tip(MENU_TEXT(pt_page_data->at_item[ui4_item_id].ui2_msgid_desc));
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        a_app_tts_play(MENU_TTS_TEXT(pt_page_data->at_item[ui4_item_id].ui2_msgid_title), c_uc_w2s_strlen(MENU_TTS_TEXT(pt_page_data->at_item[ui4_item_id].ui2_msgid_title)));
    #endif

        return WGLR_OK;
    }
    case WGL_MSG_LOSE_FOCUS:
    {
        i4_ret = c_wgl_do_cmd(h_widget,
                              WGL_CMD_GL_GET_ATTACH_DATA,
                              WGL_PACK(&ui4_item_id),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        if(ui4_item_id >= NW_PAGE_ID_LAST_ENTRY)
        {
            return MENUR_INV_STATE;
        }

        return WGLR_OK;
    }
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        if (BTN_CURSOR_UP == ui4_keycode)
        {
            _item_subpage_handle_cursor_up_and_dow(h_widget, TRUE);
            return 0;
        }
        else if (BTN_CURSOR_DOWN == ui4_keycode)
        {
            _item_subpage_handle_cursor_up_and_dow(h_widget, FALSE);
            return 0;
        }
        if (BTN_RETURN == ui4_keycode)
        {
            menu_nav_go_home_menu();
            return 0;
        }

        if(t_nw_page_data.b_finish == FALSE)
        {
            return WGLR_OK;
        }

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        {
            INT32           i4_ret;
            UINT32          ui4_item_id = 0;
            NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

            if(ui4_msg == WGL_MSG_KEY_REPEAT)
            {
                return WGLR_OK;
            }

            i4_ret = c_wgl_do_cmd(h_widget,
                                  WGL_CMD_GL_GET_ATTACH_DATA,
                                  WGL_PACK(&ui4_item_id),
                                  NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui4_item_id >= NW_PAGE_ID_LAST_ENTRY)
            {
                return MENUR_INV_STATE;
            }

            pt_page_data->h_last_focus = pt_page_data->at_item[ui4_item_id].h_subpage;
            menu_nav_go(pt_page_data->at_item[ui4_item_id].ui4_subpage_id, NULL);

            return WGLR_OK;
        }
        case BTN_CURSOR_LEFT:
    #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
    #endif

        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_go_home_menu();
            return WGLR_OK;
        default:
            break;
        }

    }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
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
static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            c_wgl_set_focus(_get_top_focus_handle(), WGL_SYNC_AUTO_REPAINT);
            break ;
        case BTN_CURSOR_UP:
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            break;
        default:
            break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
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
static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HOME_HELP_TIP));
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;
        case BTN_RETURN:
            menu_nav_go_home_menu();
            return MENUR_OK;
        case BTN_CURSOR_DOWN :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _connection_text_create
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
static INT32 _connection_text_create(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;

    WGL_IMG_INFO_T              t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    WGL_INSET_T t_inset_border = {
        FRAME_LEFT_RIGHT_INTV + MENU_ITEM_V_TITLE_W,
        FRAME_LEFT_RIGHT_INTV,
        0,
        0};
    GL_RECT_T   t_rect_border_title = {
        FRAME_LEFT_RIGHT_INTV,
        0,
        MENU_ITEM_V_TITLE_W,
        NW_ITEM_V_HEIGHT};

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     MENU_ITEM_V_WIDE,
                     NW_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32 |WGL_STL_GL_NO_BK),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_RIGHT_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bar_plain;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _ap_list_title_create
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
static INT32 _ap_list_title_create(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;

    WGL_IMG_INFO_T              t_img_info;

    WGL_INSET_T t_inset = {
        FRAME_LEFT_RIGHT_INTV,
        FRAME_LEFT_RIGHT_INTV,
        3*4/3,
        0};

    CHIPSET chipset = menu_common_get_chipset();
    if ((chipset == CHIPSET_5691) || (chipset == CHIPSET_5695) || (chipset == CHIPSET_5695L))
    {
        SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_INSET_L,
                         NW_ITEM_V_HEIGHT,
                         MENU_ITEM_V_WIDE,
                         NW_ITEM_V_HEIGHT);
    }
    else if (chipset == CHIPSET_5583)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_INSET_L,
                         0,
                         MENU_ITEM_V_WIDE,
                         NW_ITEM_V_HEIGHT);
    }

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_bk2_txt_disable;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk2_txt_disable;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bar_plain;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bar_plain;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bar_plain;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _list_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _list_create(
    HANDLE_T                h_parent,
    const GL_RECT_T*        pt_rect,
    wgl_widget_proc_fct     pf_wdgt_proc,
    const WGL_LB_INIT_T*    pt_lb_init,
    VOID*                   pv_tag,
    HANDLE_T*               ph_lb)
{
    INT32 i4_ret;
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    UINT8                       ui1_col;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_clr_elem;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_LIST_BOX,
                                  WGL_CONTENT_LIST_BOX_DEF,
                                  WGL_BORDER_TRANSP,
                                  pt_rect,
                                  pf_wdgt_proc,
                                  255,
                                  (VOID*)pt_lb_init,
                                  pv_tag,
                                  ph_lb);
    if (i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_FONT,
                                   WGL_PACK((UINT16)ui1_col),
                                   WGL_PACK(&t_fnt_info));
            MENU_LOG_ON_FAIL(i4_ret);
        }
   }

    /* Set Inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_GL_SET_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_ELEM_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left   = 0;
    t_inset.i4_right  = 8;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd (*ph_lb,
                               WGL_CMD_LB_SET_COL_INSET,
                               WGL_PACK((UINT16)ui1_col),
                               WGL_PACK(&t_inset));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_lb,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_elem.t_normal             = t_g_menu_color_transp;
    t_clr_elem.t_disable            = t_g_menu_color_transp;
    t_clr_elem.t_highlight          = t_g_menu_color_transp;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_transp;
    t_clr_elem.t_pushed             = t_g_menu_color_transp;
    t_clr_elem.t_selected           = t_g_menu_color_transp;
    t_clr_elem.t_selected_disable   = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_SET_ELEM_COLOR,
                           WGL_PACK(WGL_CLR_BK),
                           WGL_PACK(& t_clr_elem));
    MENU_LOG_ON_FAIL(i4_ret);

    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        i4_ret = c_wgl_do_cmd (*ph_lb,
                               WGL_CMD_LB_SET_COL_COLOR,
                               WGL_PACK_2(ui1_col, WGL_CLR_BK),
                               WGL_PACK(& t_clr_elem));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    t_clr_elem.t_normal             = t_g_menu_color_white;
    t_clr_elem.t_disable            = t_g_menu_color_white;
    t_clr_elem.t_highlight          = t_g_menu_color_white;
    t_clr_elem.t_highlight_unfocus  = t_g_menu_color_white;
    t_clr_elem.t_pushed             = t_g_menu_color_white;
    t_clr_elem.t_selected           = t_g_menu_color_white;
    t_clr_elem.t_selected_disable   = t_g_menu_color_white;
    for(ui1_col=0; ui1_col < pt_lb_init->ui1_col_num; ui1_col++)
    {
        if(pt_lb_init->at_cols[ui1_col].e_col_type == LB_COL_TYPE_TEXT)
        {
            i4_ret = c_wgl_do_cmd (*ph_lb,
                                   WGL_CMD_LB_SET_COL_COLOR,
                                   WGL_PACK_2(ui1_col, WGL_CLR_TEXT),
                                   WGL_PACK(& t_clr_elem));
            MENU_LOG_ON_FAIL(i4_ret);
        }
    }

    /* Set background image */
    t_img_elem.h_normal             = NULL_HANDLE;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (*ph_lb,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set long text scroll effect */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (*ph_lb,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lb_ap_list_creat
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _lb_ap_list_creat (VOID)
{
    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[4];
    GL_RECT_T           t_rect;

    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[0].ui1_align        = WGL_AS_RIGHT_CENTER;
    at_cols[0].ui2_width        = NW_AP_CON_COL0_W;

    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[1].ui2_max_text_len = 32;
    at_cols[1].ui2_width        = NW_AP_CON_COL1_W;

    at_cols[2].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[2].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[2].ui2_width        = NW_AP_CON_COL2_W;

    at_cols[3].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[3].ui1_align        = WGL_AS_LEFT_CENTER;
    at_cols[3].ui2_width        = NW_AP_CON_COL3_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = WLAN_AP_LB_ELEM_NUM;
    t_lb_init.ui2_elem_size     = NW_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 4;
    t_lb_init.at_cols           = at_cols;

    CHIPSET chipset = menu_common_get_chipset();
    if ((chipset == CHIPSET_5691) || (chipset == CHIPSET_5695) || (chipset == CHIPSET_5695L))
    {
        SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_INSET_L,
                         NW_ITEM_V_HEIGHT * 2,
                         MENU_ITEM_V_WIDE,
                         NW_ITEM_V_HEIGHT* WLAN_AP_LB_ELEM_NUM);
    }
    else if (chipset == CHIPSET_5583)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         MENU_ITEM_V_INSET_L,
                         NW_ITEM_V_HEIGHT,
                         MENU_ITEM_V_WIDE,
                         NW_ITEM_V_HEIGHT * WLAN_AP_LB_ELEM_NUM);
    }

    i4_ret = _list_create(pt_page_data->h_cnt_frm,
                               &t_rect,
                               _lb_ap_list_proc_fct,
                               &t_lb_init,
                               NULL,
                               &pt_page_data->h_lb_ap_list);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _menu_network_action_create
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
static INT32 _menu_network_action_create(
    HANDLE_T    h_parent,
    INT32       i4_index,
    wgl_widget_proc_fct pf_wdgt_proc,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_INSET_T                 t_inset;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_LB_ITEM_T               at_items[1];
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_KEY_MAP_T            t_lb_key_map;
    WGL_FONT_INFO_T             t_fnt_info;
    WGL_LB_ITEM_IMG_SUIT_T      t_img_suit_enter;
    WGL_IMG_INFO_T    t_img_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 32;
    at_cols[0].ui2_width        = MENU_ITEM_V_VALUE_W;

    t_lb_init.ui4_style         = WGL_STL_GL_NO_BK
                                  | WGL_STL_GL_BDR_FILL_CNT_BK
                                  | WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_NO_SMART_CUT
                                  | WGL_STL_LB_ELEM_NO_PUSH;

    t_lb_init.ui2_max_elem_num  = 1;
    t_lb_init.ui2_elem_size     = NW_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     NW_ITEM_V_HEIGHT* i4_index,
                     MENU_ITEM_V_WIDE,
                     NW_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_LIST_BOX,
                                 WGL_CONTENT_LIST_BOX_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 &t_lb_init,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_INSET,
                          &t_g_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_right    = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.ui1_custom_size = 24;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_transp;
    t_lb_color.t_pushed = t_g_menu_color_transp;
    t_lb_color.t_selected = t_g_menu_color_transp;
    t_lb_color.t_selected_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_LB_TITLE_FG),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set LB elements */
    c_memset(&t_img_suit_enter, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit_enter.h_normal                       = NULL_HANDLE;
    t_img_suit_enter.h_disable                      = NULL_HANDLE;
    t_img_suit_enter.h_highlight                    = NULL_HANDLE;
    t_img_suit_enter.h_highlight_unfocus            = NULL_HANDLE;
    t_img_suit_enter.h_pushed                       = NULL_HANDLE;
    t_img_suit_enter.h_selected                     = NULL_HANDLE;
    t_img_suit_enter.h_selected_disable             = NULL_HANDLE;
    t_img_suit_enter.h_selected_highlight           = NULL_HANDLE;
    t_img_suit_enter.h_selected_highlight_unfocus   = NULL_HANDLE;
    t_img_suit_enter.h_selected_pushed              = NULL_HANDLE;

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_empty;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_APPEND_ELEM, at_items, NULL );
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_RIGHT;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_LEFT;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    i4_ret = c_wgl_do_cmd(*ph_widget, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    t_title_info.t_font = t_fnt_info;
    t_title_info.t_rc_ref = t_g_rect_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _subpage_item_create
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
static INT32 _subpage_item_create( VOID )
{
    INT32       i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    UINT32      ui4_i;
    UINT8       aui1_item_idx[NW_PAGE_ID_LAST_ENTRY] = ARRY_NW_PAGE_ITEM_IDX_1;

    /* create Enter access point name page*/
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_nw_ap_list,
                                 NULL,
                                 &pt_page_data->at_item[NW_PAGE_ID_AP_LST].ui4_subpage_id);
    MENU_LOG_ON_FAIL(i4_ret);
    pt_page_data->at_item[NW_PAGE_ID_AP_LST].ui2_msgid_title = MLM_MENU_KEY_NET_MORE_AP;
    pt_page_data->at_item[NW_PAGE_ID_AP_LST].ui2_msgid_desc  = MLM_MENU_KEY_NW_HELP_MORE_AP;

    /* create manual setup page */
    i4_ret = menu_pm_page_create(&t_g_menu_common_ip_setting,
                                 NULL,
                                 &pt_page_data->at_item[NW_PAGE_ID_MAN_SET].ui4_subpage_id);
    MENU_LOG_ON_FAIL(i4_ret);
    pt_page_data->at_item[NW_PAGE_ID_MAN_SET].ui2_msgid_title = MLM_MENU_KEY_NETWORK_SET;
    pt_page_data->at_item[NW_PAGE_ID_MAN_SET].ui2_msgid_desc  = MLM_MENU_KEY_TAB_HELP_NETWORK_SET;

    /* create Hiden network/Enter access point name page*/
    i4_ret = menu_pm_page_create(&t_g_menu_common_page_nw_input_ssid,
                                 NULL,
                                 &pt_page_data->at_item[NW_PAGE_ID_AP_NAME].ui4_subpage_id);
    MENU_LOG_ON_FAIL(i4_ret);
    pt_page_data->at_item[NW_PAGE_ID_AP_NAME].ui2_msgid_title = MLM_MENU_KEY_NET_INP_AP_NAME;
    pt_page_data->at_item[NW_PAGE_ID_AP_NAME].ui2_msgid_desc  = MLM_MENU_KEY_NW_HELP_INP_AP_NAME;

    /* Create test connection page */
    i4_ret = menu_pm_page_create(&t_g_menu_common_nw_test_connection,
                                 NULL,
                                 &pt_page_data->at_item[NW_PAGE_ID_TEST].ui4_subpage_id);
    MENU_LOG_ON_FAIL(i4_ret);
    pt_page_data->at_item[NW_PAGE_ID_TEST].ui2_msgid_title = MLM_MENU_KEY_NET_CFG_CONN_TEST;
    pt_page_data->at_item[NW_PAGE_ID_TEST].ui2_msgid_desc  = MLM_MENU_KEY_NW_HELP_TEST;

    /*Jundi add create network information page*/
    i4_ret = menu_pm_page_create(&t_g_menu_common_nw_info,
                                  NULL,
                                  &pt_page_data->at_item[NW_PAGE_ID_NET_INFO].ui4_subpage_id);
    MENU_LOG_ON_FAIL(i4_ret);
    pt_page_data->at_item[NW_PAGE_ID_NET_INFO].ui2_msgid_title = MLM_MENU_KEY_SYS_INFO_NETWORK;
    pt_page_data->at_item[NW_PAGE_ID_NET_INFO].ui2_msgid_desc  = MLM_MENU_KEY_NW_INFO_HELP;

    for(ui4_i = 0; ui4_i<NW_PAGE_ID_LAST_ENTRY; ui4_i++ )
    {
        i4_ret = _menu_network_action_create(pt_page_data->h_cnt_frm,
                                    (INT32)aui1_item_idx[ui4_i],
                                    _item_subpage_proc_fct,
                                    &pt_page_data->at_item[ui4_i].h_subpage);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_page_data->at_item[ui4_i].h_subpage,
                              WGL_CMD_GL_SET_ATTACH_DATA,
                              WGL_PACK(ui4_i),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_page_data->at_item[ui4_i].h_subpage,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_nw_pwd,
                                 NULL,
                                 &pt_page_data->ui4_pwd_page_id);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wps_cb_fct
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
static VOID _wps_cb_fct(UINT32 ui4_keycode)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    INT32       i4_ret = MENUR_OK;

    /* end of wps associating weather it is success or fail */
    b_g_wps_is_associating = FALSE;

    /* stop timer first */
    i4_ret = c_timer_stop(pt_page_data->h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;
    pt_page_data->b_timer_result = TRUE;
    pt_page_data->b_wps_associate = FALSE;

    i4_ret = a_nw_custom_wlan_disassociate();
    MENU_LOG_ON_FAIL(i4_ret);

    menu_network_simple_dialog_hide(FALSE);

    i4_ret = _update_ap_list_with_local_buf();
    MENU_LOG_ON_FAIL(i4_ret);

    _update_all_items();

    i4_ret = menu_pm_repaint();
    MENU_LOG_ON_FAIL(i4_ret);

    if (pt_page_data->ui1_animation_count >= WLAN_WPS_CONNECTING_TIMEOUT)
    {
        menu_network_show_confirm_dialog(MENU_TEXT(MLM_MENU_KEY_NW_CON_FAIL_2),
                                         MENU_TEXT(MLM_MENU_KEY_OK),
                                         _nw_confirm_dialog_try_again_cb_fct,
                                         TRUE);
    }
    else
    {
        i4_ret = c_wgl_set_focus(pt_page_data->h_wps, WGL_SYNC_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

/*----------------------------------------------------------------------------
 * Name: _action_item_wps_proc_fct
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
static INT32 _action_item_wps_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_NET_WPS));

    #ifdef APP_TTS_SUPPORT
        a_app_tts_play(L"WPS", 3);
    #endif

        return WGLR_OK;
    }

    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

        if (BTN_CURSOR_UP == ui4_keycode)
        {
            if (0 == pt_page_data->ui1_ap_num)
            {
                MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            }
            else if(pt_page_data->ui1_ap_num <= WLAN_AP_LB_ELEM_NUM)
            {
                c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_SYNC_AUTO_REPAINT);
            }
            else
            {
                c_wgl_set_focus(t_nw_page_data.at_item[NW_PAGE_ID_AP_LST].h_subpage,
                                WGL_SYNC_AUTO_REPAINT);
            }

            return 0;
        }
        else if (BTN_CURSOR_DOWN == ui4_keycode)
        {
            c_wgl_set_focus(t_nw_page_data.at_item[NW_PAGE_ID_TEST].h_subpage,
                            WGL_SYNC_AUTO_REPAINT);

            return 0;
        }

        if(t_nw_page_data.b_finish == FALSE)
        {
            return WGLR_OK;
        }

        switch (ui4_keycode)
        {
            case BTN_SELECT:
            {
                INT32       i4_ret = MENUR_OK;
                NET_802_11_WPS_ASSOC_MODE_T e_wps_associate_mode = IEEE_802_11_PBC_SETUP;

                /* wps associate */
                i4_ret = a_nw_custom_wlan_disassociate();
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = a_nw_wlan_wps_associate(e_wps_associate_mode);
                MENU_LOG_ON_FAIL(i4_ret);

                pt_page_data->b_finish = FALSE;
                pt_page_data->b_timer_result = FALSE;
                pt_page_data->b_connec_timer = TRUE;
                pt_page_data->b_wps_associate = TRUE;
                pt_page_data->ui1_animation_count = 0;

                i4_ret = menu_network_wps_dialog_set_progress(0, FALSE);
                MENU_LOG_ON_FAIL(i4_ret);

                /* indicate is wps associating */
                b_g_wps_is_associating = TRUE;
                i4_ret = menu_network_wps_dialog_show(0xFFEE,
                                                      MLM_MENU_KEY_CNCL,
                                                      _wps_cb_fct,
                                                      FALSE);
                MENU_LOG_ON_FAIL(i4_ret);

                menu_pm_repaint();

                c_timer_start(pt_page_data->h_timer, 1000,
                              X_TIMER_FLAG_ONCE,
                              _nw_timer_cb_fct,
                              NULL);

                return WGLR_OK;
            }
            case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
                return WGLR_OK;
        #endif

            case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
                menu_nav_go_home_menu();
                return WGLR_OK;
            default:
                break;
        }

    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _action_item_wps_create
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
static INT32 _action_item_wps_create()
{
    INT32       i4_ret = MENUR_OK;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    i4_ret = _menu_network_action_create(pt_page_data->h_cnt_frm,
                                        (INT32)BTN_WPS_IDX,
                                        _action_item_wps_proc_fct,
                                        &pt_page_data->h_wps);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_wps,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(L"WPS"),
                          WGL_PACK(0xFF));
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _confirm_dialog_create
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
static INT32 _confirm_dialog_create(VOID)
{
    INT32       i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    GL_RECT_T           t_rect;

    HANDLE_T     h_root_frm;

    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;

    WGL_IMG_INFO_T    t_img_info;

    WGL_INSET_T t_inset = {
        8*4/3,
        8*4/3,
        3*4/3,
        0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      NW_DIALOG_FRAM_X,
                      NW_DIALOG_FRAM_Y,
                      NW_DIALOG_FRAM_W,
                      NW_DIALOG_FRAM_H);

    /* create widget */
    i4_ret = c_wgl_create_widget (h_root_frm,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 & t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 0,
                                 &pt_page_data->h_confirm_dialog_frm);
    MENU_LOG_ON_FAIL(i4_ret);

     t_img_info.e_type = WGL_IMG_SET_STANDARD;
     t_img_info.u_img_data.t_standard.t_enable = h_g_dialog_box_v2;
     t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_box_v2;
     t_img_info.u_img_data.t_standard.t_disable = h_g_dialog_box_v2;
     i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_frm,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                      NW_DIALOG_ICON_X,
                      NW_DIALOG_ICON_Y,
                      NW_DIALOG_ICON_W,
                      NW_DIALOG_ICON_H);

    i4_ret = c_wgl_create_widget(pt_page_data->h_confirm_dialog_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &pt_page_data->h_warning_icon);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_rect.i4_left      = 0;
    t_rect.i4_right     = 0;
    t_rect.i4_top       = 0;
    t_rect.i4_bottom    = 0;
    i4_ret = c_wgl_do_cmd (pt_page_data->h_warning_icon,
                           WGL_CMD_GL_SET_INSET,
                           &t_rect,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_warning_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_warning_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_warning_icon;
    i4_ret = c_wgl_do_cmd(pt_page_data->h_warning_icon,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_FG),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(pt_page_data->h_warning_icon,
                           WGL_CMD_ICON_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_CENTER,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     SET_RECT_BY_SIZE(&t_rect,
                      NW_DIALOG_TITLE_X,
                      NW_DIALOG_TITLE_Y,
                      NW_DIALOG_TITLE_W,
                      NW_DIALOG_TITLE_H);

     i4_ret = c_wgl_create_widget(pt_page_data->h_confirm_dialog_frm,
                                  HT_WGL_WIDGET_TEXT,
                                  WGL_CONTENT_TEXT_DEF,
                                  WGL_BORDER_TRANSP,
                                  &t_rect,
                                  NULL,
                                  255,
                                  (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE),
                                  NULL,
                                  &pt_page_data->h_confirm_dialog_title);
     if (i4_ret < 0)
     {
         return MENUR_CANT_CREATE_WIDGET;
     }

     /* Set Insets */
     i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_title,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);


     /* Set Alignment */
     i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_title,
                           WGL_CMD_TEXT_SET_ALIGN,
                           (VOID*)WGL_AS_CENTER_TOP,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     /* Set Font */
     c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
     c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);

     t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
     t_fnt_info.ui1_custom_size = 24;
     t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
     t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
     i4_ret = c_wgl_do_cmd (pt_page_data->h_confirm_dialog_title,
                            WGL_CMD_GL_SET_FONT,
                            (void*)&t_fnt_info,
                            NULL);
     MENU_LOG_ON_FAIL(i4_ret);

     t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
     t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
     t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
     i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_title,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info) );
     MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     NW_DIALOG_TRY_AGAIN_X,
                     NW_DIALOG_TRY_AGAIN_Y,
                     NW_DIALOG_TRY_AGAIN_W,
                     NW_DIALOG_TRY_AGAIN_H);

    i4_ret = c_wgl_create_widget(pt_page_data->h_confirm_dialog_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _confirm_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &pt_page_data->h_confirm_dialog_try_again);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_again,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_page_data->h_confirm_dialog_try_again,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_again,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_dialog_button_gray_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_button_highlight_v2;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_dialog_button_gray_v2;
    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_again,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     NW_DIALOG_TRY_ANOTHER_X,
                     NW_DIALOG_TRY_ANOTHER_Y,
                     NW_DIALOG_TRY_ANOTHER_W,
                     NW_DIALOG_TRY_ANOTHER_H);

    i4_ret = c_wgl_create_widget(pt_page_data->h_confirm_dialog_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 _confirm_dialog_proc_fct,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 &pt_page_data->h_confirm_dialog_try_another);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_another,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_page_data->h_confirm_dialog_try_another,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_another,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_dialog_button_gray_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_dialog_button_highlight_v2;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_dialog_button_gray_v2;
    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_another,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
     MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility (pt_page_data->h_confirm_dialog_frm, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility (pt_page_data->h_confirm_dialog_frm, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _nw_page_animation_icon_create(VOID)
{
    INT32   i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;

    ui4_style = WGL_STL_GL_NO_BK;

    SET_RECT_BY_SIZE(&t_rect,
                 MENU_ITEM_V_INSET_L + (MENU_ITEM_V_WIDE - ICON_ANIMATION_W)/2,
                 NW_ITEM_V_HEIGHT * 3 - ICON_ANIMATION_H/2,
                 ICON_ANIMATION_W,
                 ICON_ANIMATION_H);

    i4_ret = c_wgl_create_widget(t_nw_page_data.h_cnt_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_g_img_icon);
    if (i4_ret != MENUR_OK)
    {
        DBG_ERROR(("%s,%dFailed to create icon\n",
                   __FILE__, __LINE__));
    }
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_g_img_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_g_img_icon,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret;

    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    c_memset(pt_page_data, 0, sizeof(NW_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    CHIPSET chipset = menu_common_get_chipset();
    if ((chipset == CHIPSET_5691) || (chipset == CHIPSET_5695) || (chipset == CHIPSET_5695L))
    {
        i4_ret = _connection_text_create(pt_page_data->h_cnt_frm,
                                     &pt_page_data->h_txt_connection);//create "Wired Connection" widget
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = _ap_list_title_create(pt_page_data->h_cnt_frm,
                                   &pt_page_data->h_txt_ap_list_tit);//create "Wired Access Points" widget
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _lb_ap_list_creat();//create 4 wifi items list widget
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _subpage_item_create();//create other widget
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _action_item_wps_create();//nothing
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _confirm_dialog_create();//confirm dialog
    MENU_LOG_ON_FAIL(i4_ret);

    /* ipref page */
    i4_ret = menu_network_com_ui_init();
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;

    i4_ret = menu_page_set_proc_func(ui4_page_id, _widgets_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    _nw_page_animation_icon_create();

    h_g_img_animation[0] = h_g_wdk_img_loading_icon_1;
    h_g_img_animation[1] = h_g_wdk_img_loading_icon_2;
    h_g_img_animation[2] = h_g_wdk_img_loading_icon_3;
    h_g_img_animation[3] = h_g_wdk_img_loading_icon_4;
    h_g_img_animation[4] = h_g_wdk_img_loading_icon_5;
    h_g_img_animation[5] = h_g_wdk_img_loading_icon_6;
    h_g_img_animation[6] = h_g_wdk_img_loading_icon_7;
    h_g_img_animation[7] = h_g_wdk_img_loading_icon_8;
    h_g_img_animation[8] = h_g_wdk_img_loading_icon_9;
    h_g_img_animation[9] = h_g_wdk_img_loading_icon_10;
    h_g_img_animation[10] = h_g_wdk_img_loading_icon_11;
    h_g_img_animation[11] = h_g_wdk_img_loading_icon_12;

    pt_page_data->h_timer = NULL_HANDLE;
    pt_page_data->h_retest_timer = NULL_HANDLE;

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    if(pt_page_data->t_essList.p_EssInfo != NULL)
    {
        c_mem_free(pt_page_data->t_essList.p_EssInfo);
    }

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    i4_ret = a_nw_register(_menu_page_network_nw_notify_callback,
                           NULL,
                           &pt_page_data->ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("[%s %d] pt_page_data->ui4_nw_nfy_id = %d\n",__FUNCTION__,__LINE__,pt_page_data->ui4_nw_nfy_id));
    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_MAIN_MENU_NETWORK);
    menu_help_tip_keytip_show(FALSE);

    if (NULL_HANDLE == pt_page_data->h_timer)
    {
        c_timer_create(&pt_page_data->h_timer);
    }

    if (NULL_HANDLE == pt_page_data->h_retest_timer)
    {
        c_timer_create(&pt_page_data->h_retest_timer);
    }

    i4_ret = c_wgl_float( h_g_img_icon, TRUE, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_MMP_COEXIST
    HANDLE_T h_frm_main = NULL_HANDLE;

    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        i4_ret = menu_pm_get_main_frm(&h_frm_main);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_float(h_frm_main, FALSE, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif

    _nw_img_animation_hide(FALSE);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32           i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    i4_ret = a_nw_unregister(pt_page_data->ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);
    DBG_LOG_PRINT(("[%s %d] pt_page_data->ui4_nw_nfy_id = %d\n",__FUNCTION__,__LINE__,pt_page_data->ui4_nw_nfy_id));
    pt_page_data->ui4_nw_nfy_id = 0;

    b_g_wps_is_associating = FALSE;

    if(pt_page_data->b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }

    if (NULL_HANDLE != pt_page_data->h_timer)
    {
        c_timer_delete(pt_page_data->h_timer);
        pt_page_data->h_timer = NULL_HANDLE;
    }

    if (NULL_HANDLE != pt_page_data->h_retest_timer)
    {
        c_timer_delete(pt_page_data->h_retest_timer);
        pt_page_data->h_retest_timer = NULL_HANDLE;
    }

    pt_page_data->b_this_page_show = FALSE;

    pt_page_data->b_finish = TRUE;

    menu_help_tip_keytip_show(TRUE);

    menu_network_hide_confirm_dialog(FALSE);

    menu_network_simple_dialog_hide(FALSE);

    i4_ret = menu_network_last_shadow_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    INT32           i4_ret;
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    b_ipv6_only = FALSE;
    //Jundi modify the flow for DTV02300533
    /* update last shadow position */
    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->at_item[NW_PAGE_ID_NET_INFO].h_subpage,
                    FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_this_page_show = TRUE;

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);
    if (pt_page_data->b_page_connect_success_back)
    {
        _update_ap_list();
    }
    else
    {
        _update_all_items();
    }
    if (pt_page_data->b_page_back)
    {
        _wlan_update_associate();

        c_wgl_set_focus(pt_page_data->h_last_focus, WGL_NO_AUTO_REPAINT);
    }
    else
    {
#ifdef APP_NW_WPS_SUPPORT
        if (pt_page_data->b_wired_plug)
        {
            c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage,
                            WGL_NO_AUTO_REPAINT);
        }
        else
        {
            c_wgl_set_focus(pt_page_data->h_wps, WGL_NO_AUTO_REPAINT);
        }
#else
        c_wgl_set_focus(pt_page_data->at_item[NW_PAGE_ID_TEST].h_subpage, WGL_NO_AUTO_REPAINT);
#endif
    }


    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    /* set callback function for backbar */
    menu_set_backbar_proc(NULL) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

#ifdef APP_MENU_MMP_COEXIST
    HANDLE_T h_frm_main = NULL_HANDLE;

    if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
    {
        MENU_LOG_ON_FAIL(menu_pm_get_main_frm(&h_frm_main));

        MENU_LOG_ON_FAIL(c_wgl_float(h_frm_main, FALSE, WGL_NO_AUTO_REPAINT));
    }
#endif

    c_wgl_float( h_g_img_icon, FALSE, WGL_NO_AUTO_REPAINT);

    _nw_img_animation_hide(FALSE);

    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                    global function implementation
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: menu_netowrk_nav_back
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
INT32 menu_netowrk_nav_back(VOID)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    pt_page_data->b_page_back = TRUE;
    menu_nav_back();
    pt_page_data->b_page_back = FALSE;

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_netowrk_nav_back
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
INT32 menu_netowrk_connect_success_back(VOID)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    pt_page_data->b_page_connect_success_back = TRUE;
    menu_netowrk_nav_go(NW_PAGE_ID_ROOT,NULL);
    pt_page_data->b_page_connect_success_back = FALSE;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_network_is_page_back
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
BOOL menu_network_is_page_back(VOID)
{
    return t_nw_page_data.b_page_back;
}
/*----------------------------------------------------------------------------
 * Name: menu_netowrk_nav_go
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
INT32 menu_netowrk_nav_go(
    UINT32 ui4_network_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    UINT32 ui4_page_id = 0;

    if(ui4_network_page_id == NW_PAGE_ID_ROOT)
    {
        UINT32 aui4_pages[]={ui4_g_menu_page_main_menu,
                             ui4_g_menu_page_nw
                            };

        /* hide usb dialog first */
        menu_custom_dialog_hide(MENU_CUSTOM_DIALOG_ID_USB_POPUP);

        /* Navigate to network root page */
        return menu_nav_go_direct(0,
                                  aui4_pages,
                                  sizeof(aui4_pages)/sizeof(aui4_pages[0]),
                                  NULL);
    }

    switch(ui4_network_page_id)
    {
        case NW_PAGE_ID_AP_LST:
        case NW_PAGE_ID_MAN_SET:
        case NW_PAGE_ID_AP_NAME:
        case NW_PAGE_ID_TEST:
        case NW_PAGE_ID_NET_INFO:
            ui4_page_id = pt_page_data->at_item[ui4_network_page_id].ui4_subpage_id;
            break;
        case NW_PAGE_ID_PWD:
            ui4_page_id = pt_page_data->ui4_pwd_page_id;
            break;
        default:
            return MENUR_INV_ARG;
    }

    return menu_nav_go(ui4_page_id, pt_hint);
}

/*----------------------------------------------------------------------------
 * Name: menu_network_show_confirm_dialog
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
INT32 menu_network_show_confirm_dialog (UTF16_T*            pw2s_msg_text,
                                        UTF16_T*            pw2s_btn_text,
                                        nw_dialog_cb_fct    pf_back_try_again,
                                        BOOL                b_repaint)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    INT32 i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    #ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
    #endif

    if (NULL == pw2s_msg_text || NULL == pw2s_btn_text)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_again,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_try_again),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_text),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_again,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_btn_text),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     (NW_DIALOG_FRAM_W-NW_DIALOG_TRY_AGAIN_W)/2,
                     NW_DIALOG_TRY_AGAIN_Y,
                     NW_DIALOG_TRY_AGAIN_W,
                     NW_DIALOG_TRY_AGAIN_H);

    c_wgl_move(pt_page_data->h_confirm_dialog_try_again, &t_rect, WGL_NO_AUTO_REPAINT);

    c_wgl_set_focus(pt_page_data->h_confirm_dialog_try_again, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_confirm_dialog_try_another,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_confirm_dialog_frm,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        HANDLE_T  h_frm_main = NULL_HANDLE;

        i4_ret = menu_pm_get_root_frm(&h_frm_main);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(h_frm_main,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(pt_page_data->h_confirm_dialog_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

#ifdef APP_TTS_SUPPORT
    UTF16_T w2s_str[256] = {0};

    c_uc_w2s_strcpy(w2s_str, pw2s_msg_text);
    c_uc_w2s_strcat(w2s_str, _TEXT("."));
    c_uc_w2s_strcat(w2s_str, pw2s_btn_text);

    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
#endif

    return MENUR_OK;
}

INT32 menu_network_show_confirm_dialog_ex(
                                    UTF16_T*            pw2s_msg_text,
                                    UTF16_T*            pw2s_btn_try_again,//cancel
                                    UTF16_T*            pw2s_btn_try_another,//forget
                                    nw_dialog_cb_fct    pf_back_try_again,
                                    nw_dialog_cb_fct    pf_back_try_another,
                                    BOOL                b_repaint
                                    )
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    INT32 i4_ret = MENUR_OK;
    GL_RECT_T           t_rect;
    #ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
    #endif

    if (NULL == pw2s_msg_text || NULL == pw2s_btn_try_again || NULL == pw2s_btn_try_another)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_again,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_try_again),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_another,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pf_back_try_another),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_title,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_msg_text),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_again,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_btn_try_again),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_confirm_dialog_try_another,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_btn_try_another),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     NW_DIALOG_TRY_AGAIN_X,
                     NW_DIALOG_TRY_AGAIN_Y,
                     NW_DIALOG_TRY_AGAIN_W,
                     NW_DIALOG_TRY_AGAIN_H);

    c_wgl_move(pt_page_data->h_confirm_dialog_try_again, &t_rect, WGL_NO_AUTO_REPAINT);
    c_wgl_set_focus(pt_page_data->h_confirm_dialog_try_again, WGL_NO_AUTO_REPAINT);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_confirm_dialog_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_page_data->h_confirm_dialog_frm,  NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

    #ifdef APP_TTS_SUPPORT
        UTF16_T w2s_str[256] = {0};

        c_uc_w2s_strcpy(w2s_str, pw2s_msg_text);
        c_uc_w2s_strcat(w2s_str, _TEXT("."));
        c_uc_w2s_strcat(w2s_str, pw2s_btn_try_again);

        a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));
    #endif
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_network_hide_confirm_dialog
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
INT32 menu_network_hide_confirm_dialog(BOOL  b_repaint)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;
    INT32 i4_ret = MENUR_OK;
    #ifdef APP_ZOOM_MODE_SUPPORT
    a_zoom_mode_set_sector_id(ZOOM_HIDE_MAKE_ID(ZOOM_APP_GRPID_MENU, ZOOM_APP_RECID_MENU_DIALOG));
    #endif

    i4_ret = c_wgl_set_visibility(pt_page_data->h_confirm_dialog_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if(b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_page_data->h_confirm_dialog_frm,  NULL, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      menu_network_last_shadow_update_position
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 menu_network_last_shadow_update_position(HANDLE_T h_item, BOOL b_repaint)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect = {0};
    GL_RECT_T           t_rect_item = {0};
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

    if (NULL_HANDLE == h_item)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_get_coords(h_item,
                              WGL_COORDS_SCREEN,
                              &t_rect_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_top = t_rect_item.i4_bottom;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(h_last_shadow_item, NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      menu_network_last_shadow_hide
 * Description:
 *
 * Input arguments:
 *
 * Output arguments:
 *      None
 * Returns:
 *      MENUR_OK    Successful
 *      Others      Fail
 *---------------------------------------------------------------------------*/
INT32 menu_network_last_shadow_hide(BOOL b_repaint)
{
    INT32               i4_ret = 0;
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(h_last_shadow_item, NULL, TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
* Name: menu_netowrk_set_associate_data
*
* Description: store network my_net_pls info to flash
*
* Inputs:
*      BOOL: TURE:Enable / FALSE:Disable
*
* Outputs: -
*
* Returns:
*      APP_CFGR_OK             - Successful
*      APP_CFGR_NOT_INIT       - Not Initiated
*      APP_CFGR_INTERNAL_ERR   - Internal Error
*--------------------------------------------------------------------------*/
extern INT32 menu_netowrk_set_associate_data(NET_802_11_ASSOCIATE_T* pt_associate)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    if (pt_associate == NULL)
    {
        return MENUR_INV_ARG;
    }

    c_memcpy(pt_associate, &pt_page_data->t_associate, sizeof(NET_802_11_ASSOCIATE_T));

    /*Not save the pui1_PassPhrase*/
    pt_page_data->t_associate.t_Key.pui1_PassPhrase = NULL;

    return MENUR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: menu_network_get_associate_data
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern INT32  menu_network_get_associate_data(NET_802_11_ASSOCIATE_T** ppt_associate)
{

    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    if (ppt_associate == NULL)
    {
        return MENUR_INV_ARG;
    }

    *ppt_associate = &pt_page_data->t_associate;

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_network_get_ap_by_idx
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *      APP_CFGR_OK             - Successful
 *      APP_CFGR_NOT_INIT       - Not Initiated
 *      APP_CFGR_INV_ARG     - Invalid argrument
 *      APP_CFGR_INTERNAL_ERR   - Internal Error
 *-----------------------------------------------------------------------------*/
extern NET_802_11_ESS_INFO_T*  menu_network_get_ap_by_idx(UINT16     ui2_idx)
{
    NW_PAGE_DATA_T* pt_page_data = &t_nw_page_data;

    if (ui2_idx < pt_page_data->t_essList.ui4_NumberOfItems)
    {
        return &pt_page_data->t_essList.p_EssInfo[ui2_idx];
    }
    else
    {
        return NULL;
    }
}

/*-----------------------------------------------------------------------------
 * Name: menu_network_is_DNS_available
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
*
 *-----------------------------------------------------------------------------*/
extern INT32 menu_network_is_DNS_available(VOID)
{
    return a_nw_connection_test((CHAR*)"www.google.com");
}

/*-----------------------------------------------------------------------------
 * Name: menu_network_is_NTP_available
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
* TRUE: NTP is available
* FALSE: NTP is not available
 *-----------------------------------------------------------------------------*/
extern BOOL menu_network_is_NTP_available(VOID)
{
    struct      timeval tv;
    struct      timezone tz;
    DTG_T       t_loc_dtg;
    INT64       sec;

    c_memset(&t_loc_dtg, 0, sizeof(DTG_T));
    if (gettimeofday(&tv, &tz) == 0)
    {
    #ifdef DEBUG
        DBG_LOG_PRINT(("\n<MENU NW>tv.tv_sec=%ld,tz.tz_dsttime=%ld,tz.tz_minuteswest=%ld\n",
                    tv.tv_sec, tz.tz_dsttime, tz.tz_minuteswest));
    #endif

        sec = (INT64)tv.tv_sec;
        c_dt_utc_sec_to_loc_dtg(sec, &t_loc_dtg);

        DBG_INFO(("[year,mon,day,hour,min] =[%d-%d-%d-%d-%d] \n ",
                 t_loc_dtg.ui2_yr,
                 t_loc_dtg.ui1_mo,
                 t_loc_dtg.ui1_day,
                 t_loc_dtg.ui1_hr,
                 t_loc_dtg.ui1_min));

        if (((t_loc_dtg.ui2_yr == 0) && (t_loc_dtg.ui1_mo == 0)) ||
            (t_loc_dtg.ui2_yr == 1970))
        {
            return FALSE;
        }

        return TRUE;
    }

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: menu_common_page_network_init
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
extern INT32 menu_common_page_network_init(VOID)
{
    t_g_menu_common_page_network.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_network.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_network.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_network.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_network.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_network.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_network.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

BOOL menu_page_is_network_manual_setup_page(UINT32 ui4_page_id)
{
     return t_nw_page_data.at_item[NW_PAGE_ID_MAN_SET].ui4_subpage_id == ui4_page_id;
}
#endif /* APP_NETWORK_SUPPORT */
