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
 * $RCSfile: menu_page_nw_ap_list.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/
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

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_page_animation.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"

#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"

#include "res/wdk/wdk_img.h"
#include "res/app_util/network/network_custom.h"

#include "menu_network.h"
#include "menu2/menu_dbg.h"

#ifdef APP_NETWORK_WIFI_SUPPORT
/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
/*For timer*/
#define WLAN_CONNECTING_TIMEOUT     (3)   /*about 30 s*/

#define NW_AP_CON_COL0_W                      (8 + FRAME_LEFT_RIGHT_INTV)
#define NW_AP_CON_COL1_W                      (MENU_ITEM_V_WIDE - NW_AP_CON_COL0_W - NW_AP_CON_COL2_W - NW_AP_CON_COL3_W)
#define NW_AP_CON_COL2_W                      ((17 + 16)*4/3)
#define NW_AP_CON_COL3_W                      (FRAME_LEFT_RIGHT_INTV + 45 - 8)

#define WLAN_AP_LB_MAX_NUM                   (128)

#define WLAN_AP_LB_VISIABLE_NUM              (9)

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

typedef struct __NW_NFY_DATA
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}_NW_NFY_DATA;

typedef struct _NW_PAGE_DATA
{
    HANDLE_T     h_timer;
    HANDLE_T     h_cnt_frm;

    HANDLE_T     h_lb_ap_list;
    HANDLE_T     h_icon_up;
    HANDLE_T     h_icon_down;

    BOOL              b_finish;
    BOOL              b_timer_result;

    UINT8             ui1_animation_count;

    UINT32       ui4_nw_nfy_id;

    BOOL         b_this_page_show;

}NW_AP_LIST_PAGE_DATA_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_ap_list;
static  NW_AP_LIST_PAGE_DATA_T    t_nw_ap_list_page_data;

static UINT8    aui1_ap_idx[WLAN_AP_LB_MAX_NUM];
static UINT8    ui1_ap_num;
/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _lb_ap_list_proc_fct(
                        HANDLE_T    h_widget,
                        UINT32      ui4_msg,
                        VOID*       param1,
                        VOID*       param2);

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _set_icon_img
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
static INT32 _set_icon_img (HANDLE_T h_icon, HANDLE_T h_img_tpl)
{
    WGL_IMG_INFO_T                  t_img_info;
    INT32                           i4_ret;

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = h_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = h_img_tpl;

    i4_ret = c_wgl_do_cmd(h_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
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
            menu_netowrk_nav_back();
            return WMPR_DONE;
        default:
            break;
        }
    }
    case WGL_MSG_NOTIFY:
    {
        HANDLE_T h_source = (HANDLE_T)param1;
        WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;
        NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

        if( h_source == pt_page_data->h_lb_ap_list
            && pt_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_HLT)
        {
            UINT16            i2_idx = pt_nfy_data->u.t_lb_elem_hlt.ui2_elem_idx;
            BOOL              b_hlt = pt_nfy_data->u.t_lb_elem_hlt.b_is_highlighted;
            UINT16            i2_end_index;

            if(!b_hlt)
            {
                break;
            }

            if(i2_idx == 0)
            {
                _set_icon_img(pt_page_data->h_icon_up, NULL_HANDLE);
                _set_icon_img(pt_page_data->h_icon_down, h_g_menu_arrow_down_v2);
            }
            else
            {
                /* Get the index */
                c_wgl_do_cmd(h_source,
                             WGL_CMD_LB_GET_ELEM_NUM,
                             WGL_PACK(&i2_end_index),
                             NULL);

                i2_end_index -= 1;

                if(i2_idx == i2_end_index)
                {
                    _set_icon_img(pt_page_data->h_icon_up, h_g_menu_arrow_up_v2);
                    _set_icon_img(pt_page_data->h_icon_down, NULL_HANDLE);
                }
                else
                {
                    _set_icon_img(pt_page_data->h_icon_up, h_g_menu_arrow_up_v2);
                    _set_icon_img(pt_page_data->h_icon_down, h_g_menu_arrow_down_v2);
                }
            }

            if(pt_page_data->b_this_page_show)
            {
                c_wgl_repaint(pt_page_data->h_cnt_frm, NULL, FALSE);
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
 * Name: _nw_notify_handler
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
static VOID _nw_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    _NW_NFY_DATA* pt_nw_nfy_data = (_NW_NFY_DATA*)pv_data;
    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;
    INT32                   i4_ret;
    BOOL                    b_nw_connect;

    switch(pt_nw_nfy_data->e_nfy_id)
    {
    case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
    case NW_NFY_ID_DHCP_SUCCESS_LINKLOCAL:
        if (pt_page_data->b_finish == FALSE)
        {
            i4_ret = menu_network_is_DNS_available();
            if (i4_ret != MENUR_OK)
            {
                pt_page_data->b_finish = TRUE;
                pt_page_data->b_timer_result = FALSE;
            }
        }
        break;
    case NW_NFY_ID_WLAN_ASSOCIATE:
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,b_finish=%d,pv_nfy_param=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    pt_page_data->b_finish, (UINT32)(pt_nw_nfy_data->pv_nfy_param)));
        if(pt_page_data->b_finish)
        {
            break;
        }

        if ((WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param) == WLAN_NFY_MSG_OK)
        {
            BOOL          b_auto_ip_config  = FALSE;

            nw_custom_get_auto_ip_config_by_iface(&b_auto_ip_config, NW_NET_INTERFACE_WIFI);

            /*Only finish when associate OK.*/
            if(b_auto_ip_config)
            {
                /*for DHCP , to check dhcp*/
                pt_page_data->b_finish = TRUE;
                pt_page_data->b_timer_result = TRUE;
            }
            else
            {
                i4_ret = menu_network_is_DNS_available();
                if (i4_ret != MENUR_OK)
                {
                    pt_page_data->b_finish = TRUE;
                    pt_page_data->b_timer_result = FALSE;
                }
            }

        }
        else if ((WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param) == WLAN_NFY_MSG_PSK_INCORRECT)
        {
            pt_page_data->b_finish = TRUE;
            pt_page_data->b_timer_result = FALSE;
        }
        break;
    }
    case NW_NFY_ID_ETHERNET_PLUGIN:
    {
        menu_nav_go_home_menu();
        break;
    }
    case NW_NFY_ID_INTERN_CT_RESULT:
    {
        b_nw_connect = (BOOL)(UINT32)(pt_nw_nfy_data->pv_nfy_param);

        DBG_LOG_PRINT(("\n%s,%s,%d,b_finish=%d,b_nw_connect=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    pt_page_data->b_finish, b_nw_connect));

        if (pt_page_data->b_finish == FALSE)
        {
            pt_page_data->b_finish = TRUE;
            pt_page_data->b_timer_result = TRUE;
        }

        break;
    }

    default:
        return;
    }

    return;
}
/*----------------------------------------------------------------------------
 * Name: _nw_notify_callback
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

static VOID _nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    _NW_NFY_DATA t_nw_nfy_data;

    if(!t_nw_ap_list_page_data.b_this_page_show)
    {
        return;
    }

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    menu_async_invoke(_nw_notify_handler,&t_nw_nfy_data,sizeof(_NW_NFY_DATA),TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _nw_confirm_dialog_cb_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _nw_ap_list_confirm_dialog_try_again_cb_fct(UINT32 ui4_key_code)
{
    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    if ((BTN_CURSOR_LEFT == ui4_key_code)
        || BTN_CURSOR_RIGHT == ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_another();
    }
    else if (BTN_SELECT == ui4_key_code)
    {
        menu_network_hide_confirm_dialog(TRUE);
        c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_ASYNC_AUTO_REPAINT);
        _lb_ap_list_proc_fct(pt_page_data->h_lb_ap_list,
                             WGL_MSG_KEY_DOWN, (VOID*)BTN_SELECT, NULL);
    }
    else
    {
        menu_network_hide_confirm_dialog(TRUE);
        c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_ASYNC_AUTO_REPAINT);
    }
}

static VOID _nw_ap_list_confirm_dialog_try_another_cb_fct(UINT32 ui4_key_code)
{
    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    if ((BTN_CURSOR_LEFT == ui4_key_code)
        || BTN_CURSOR_RIGHT == ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_again();
    }
    else
    {
        menu_network_hide_confirm_dialog(TRUE);
        c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_ASYNC_AUTO_REPAINT);
    }
}

/*----------------------------------------------------------------------------
 * Name: _menu_page_nw_ap_list_timer_finish
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
static INT32 _menu_page_nw_ap_list_timer_finish(BOOL b_success)
{
    INT32    i4_ret = MENUR_OK;
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;
    UTF16_T w2s_ssid[32+1] = {0};
    UTF16_T w2s_title[128+1] = {0};
    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    DBG_LOG_PRINT(("\n%s,%s,%d,b_finish=%d,b_timer_result=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                pt_page_data->b_finish, pt_page_data->b_timer_result));

    pt_page_data->b_finish = TRUE;
    pt_page_data->b_timer_result = TRUE;

    c_timer_stop(pt_page_data->h_timer);

    /* stop animation */
    i4_ret = menu_page_animation_stop();
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_success)
    {
        i4_ret = menu_netowrk_nav_go(NW_PAGE_ID_ROOT,NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
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
                                            _nw_ap_list_confirm_dialog_try_again_cb_fct,
                                            _nw_ap_list_confirm_dialog_try_another_cb_fct,
                                            TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_pm_repaint();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return i4_ret;
}

static VOID _ap_list_do_timer_nfy(
    VOID*   pv_data,
    SIZE_T  z_data_size)
{
    INT32               i4_ret = 0;
    BOOL                b_success = FALSE;
    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    if (FALSE == pt_page_data->b_this_page_show)
    {
        c_timer_stop(pt_page_data->h_timer);
        return;
    }

    if (pt_page_data->b_finish)
    {
        b_success = pt_page_data->b_timer_result;;

        i4_ret = _menu_page_nw_ap_list_timer_finish(b_success);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

static VOID _ap_list_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                   VOID*     pv_tag)
{
    menu_async_invoke(_ap_list_do_timer_nfy, NULL, 0, TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _menu_page_nw_ap_list_do_timer_nfy
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
static VOID _menu_page_nw_ap_list_do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{

    INT32    i4_ret = MENUR_OK;

    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    BOOL    b_success = pt_page_data->b_timer_result;
    UINT8  ui1_timeout_count = WLAN_CONNECTING_TIMEOUT;

    if (FALSE == pt_page_data->b_this_page_show)
    {
        c_timer_stop(pt_page_data->h_timer);

        /* stop animation */
        i4_ret = menu_page_animation_stop();
        MENU_LOG_ON_FAIL(i4_ret);

        return;
    }

    if (pt_page_data->b_finish)
    {
        i4_ret = _menu_page_nw_ap_list_timer_finish(b_success);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(pt_page_data->ui1_animation_count > ui1_timeout_count)
    {
        i4_ret = _menu_page_nw_ap_list_timer_finish(FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        menu_page_animation_start(1, FALSE);
        pt_page_data->ui1_animation_count += 1;
    }

    return;
}
/*----------------------------------------------------------------------------
 * Name: _menu_page_nw_ap_list_anim_cb_fct
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
static INT32 _menu_page_nw_ap_list_anim_cb_fct(HANDLE_T                h_widget,
                      UINT16                  ui2_anim_type,
                      WGL_ANIM_COND_INF_T     e_anim_cond,
                      VOID*                   pv_tag)
{
    if (_ANIM_TOTAL_END(&e_anim_cond))
    {
        menu_async_invoke(_menu_page_nw_ap_list_do_timer_nfy, NULL, 0, TRUE);
    }

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
    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;
    INT16           i2_new_level = 0;

    UTF16_T         w2s_ssid[33] = {0};
    WGL_LB_ITEM_T   at_items[4];

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

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _update_ui
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
static INT32 _update_ui(VOID)
{
    INT32       i4_ret;

    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;
    UINT16                  ui2_ap_num = 0;
    GL_RECT_T               t_rect = {0};
    HANDLE_T                h_last_shadow_item = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd (pt_page_data->h_lb_ap_list,
                      WGL_CMD_LB_GET_ELEM_NUM,
                      WGL_PACK (&ui2_ap_num),
                      NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if(ui2_ap_num > WLAN_AP_LB_VISIABLE_NUM)
    {
        i4_ret = c_wgl_set_visibility(pt_page_data->h_icon_up,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_page_data->h_icon_down,
                                      WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_visibility(pt_page_data->h_icon_up,
                                      WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_set_visibility(pt_page_data->h_icon_down,
                                      WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* adjust last shadow position */
    menu_pm_get_last_shadow_item(&h_last_shadow_item);
    if (h_last_shadow_item != NULL_HANDLE)
    {
        t_rect.i4_left = CONTENT_X;
        t_rect.i4_right = CONTENT_X + CONTENT_H;

        if (ui2_ap_num < WLAN_AP_LB_VISIABLE_NUM)
        {
            t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui2_ap_num+1) + CONTENT_Y + 20;
        }
        else
        {
            t_rect.i4_top = MENU_ITEM_V_HEIGHT * 10 + CONTENT_Y + 30;
        }
        t_rect.i4_bottom = t_rect.i4_top + MENU_ITEM_V_HEIGHT;

        i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return MENUR_OK;
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
    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        if (pt_page_data->b_this_page_show)
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_AP_LIST));
        }
        else
        {
            menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_AP_LIST));
        }

    #ifdef APP_TTS_SUPPORT
        INT32  i4_ret = MENUR_OK;
        UINT16 ui2_idx = 0;
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
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        if(pt_page_data->b_finish == FALSE)
        {
            return WGLR_OK;
        }

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
                }
                else
                {
                    i4_ret = c_wgl_do_cmd (h_widget,
                                      WGL_CMD_LB_HLT_PREV_ELEM,
                                      WGL_PACK (FALSE),
                                      NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

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
                    MENU_LOG_ON_FAIL (menu_help_tip_keytip_set_focus(h_widget, 0 , FALSE));
                    menu_pm_repaint();
                }
                else
                {
                    i4_ret = c_wgl_do_cmd (h_widget,
                                      WGL_CMD_LB_HLT_NEXT_ELEM,
                                      WGL_PACK (FALSE),
                                      NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

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

                NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;
                NET_802_11_ASSOCIATE_T* pt_associate = NULL;
                NET_802_11_ESS_INFO_T  *p_essInfo = NULL;

                if(ui4_msg == WGL_MSG_KEY_REPEAT)
                {
                    return WGLR_OK;
                }
                DBG_LOG_PRINT(("[MENU][%s %d]BTN_SELECT \n",__FUNCTION__,__LINE__));
                i4_ret = c_wgl_do_cmd (h_widget,
                                  WGL_CMD_LB_GET_HLT_INDEX,
                                  WGL_PACK (&ui2_idx),
                                  NULL);
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = menu_network_get_associate_data(&pt_associate);
                MENU_LOG_ON_FAIL(i4_ret);

                if(pt_associate == NULL)
                {
                    DBG_ERROR(("[MENU][%s %d]pt_associate is null,return now\n",__FUNCTION__,__LINE__));
                    return MENUR_OK;
                }

                /* klockwork issue*/
                if (ui2_idx > (WLAN_AP_LB_MAX_NUM - 1))
                {
                    DBG_ERROR(("[MENU][%s %d]ap index is out of range,return now\n",__FUNCTION__,__LINE__));
                    return MENUR_OK;
                }

                p_essInfo = menu_network_get_ap_by_idx(aui1_ap_idx[ui2_idx]);
                if(p_essInfo == NULL)
                {
                    DBG_ERROR(("[MENU][%s %d] failed to get network ess info,return now\n",__FUNCTION__,__LINE__));
                    return MENUR_OK;
                }

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

                    /* init the animation count as 0*/
                    pt_page_data->ui1_animation_count = 0;
                    i4_ret = menu_page_animation_start(1, FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_timer_stop(pt_page_data->h_timer);

                    i4_ret = c_timer_start(pt_page_data->h_timer,
                            200,
                            X_TIMER_FLAG_REPEAT,
                            _ap_list_timer_cb_fct,
                            NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = a_nw_custom_wlan_disassociate();
                    if (i4_ret != NWR_OK)
                    {
                        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d,b_finish=%d,b_timer_result=%d\n",
                                    __FILE__, __FUNCTION__, __LINE__, i4_ret,
                                    pt_page_data->b_finish, pt_page_data->b_timer_result));

                        pt_page_data->b_finish = TRUE;
                    }

                    i4_ret = a_nw_wlan_associate(pt_associate);
                    if (i4_ret != NWR_OK)
                    {
                        DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d,b_finish=%d,b_timer_result=%d\n",
                                    __FILE__, __FUNCTION__, __LINE__, i4_ret,
                                    pt_page_data->b_finish, pt_page_data->b_timer_result));

                        pt_page_data->b_finish = TRUE;
                    }
                }
                else
                {
                    menu_netowrk_nav_go(NW_PAGE_ID_PWD, NULL);
                }

                return WGLR_OK;
            }
            case BTN_EXIT:
                menu_nav_go_home_menu();
            case BTN_PREV_PRG:
            case BTN_RETURN:
                menu_netowrk_nav_back();
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
            menu_netowrk_nav_back();
            return MENUR_OK;
        case BTN_CURSOR_DOWN:
            c_wgl_set_focus(t_nw_ap_list_page_data.h_lb_ap_list, WGL_ASYNC_AUTO_REPAINT);
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
 * Name: menu_text_chg_lang
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
            menu_netowrk_nav_back();
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
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
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

    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    /* Create LB */
    at_cols[0].e_col_type       = LB_COL_TYPE_IMG;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
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

    t_lb_init.ui2_max_elem_num  = WLAN_AP_LB_MAX_NUM;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 4;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT* WLAN_AP_LB_VISIABLE_NUM);

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
 * Name: _icon_arrow_up_creat
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _icon_arrow_up_creat (VOID)
{
    INT32  i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T    t_img_info;

    WGL_INSET_T t_inset_border = {
        FRAME_LEFT_RIGHT_INTV,
        FRAME_LEFT_RIGHT_INTV,
        0,
        4};

    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     0 ,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(
                    pt_page_data->h_cnt_frm,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_TIMG,
                    &t_rect,
                    NULL,
                    255,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_page_data->h_icon_up);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(pt_page_data->h_icon_up,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_page_data->h_icon_up,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_BOTTOM,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_icon_up,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _icon_arrow_down_creat
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _icon_arrow_down_creat (VOID)
{
    INT32  i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T    t_img_info;

    WGL_INSET_T t_inset_border = {
        FRAME_LEFT_RIGHT_INTV,
        FRAME_LEFT_RIGHT_INTV,
        4,
        0};

    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT * 10 ,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

    i4_ret = c_wgl_create_widget(
                    pt_page_data->h_cnt_frm,
                    HT_WGL_WIDGET_ICON,
                    WGL_CONTENT_ICON_DEF,
                    WGL_BORDER_TIMG,
                    &t_rect,
                    NULL,
                    255,
                    (VOID*)(WGL_STL_GL_NO_BK),
                    NULL,
                    &pt_page_data->h_icon_down);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(pt_page_data->h_icon_down,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset_border,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_page_data->h_icon_down,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_TOP,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_icon_down,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
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

    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    c_memset(pt_page_data, 0, sizeof(NW_AP_LIST_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    /*   */
    i4_ret = _lb_ap_list_creat();
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = _icon_arrow_up_creat();
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = _icon_arrow_down_creat();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id, _widgets_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&(pt_page_data->h_timer));
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(aui1_ap_idx, 0, sizeof(UINT8)*WLAN_AP_LB_MAX_NUM);
    ui1_ap_num = 0;

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;

    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    GL_RECT_T          t_rect = {0};
    HANDLE_T           h_menu_animation = NULL_HANDLE;


    i4_ret = a_nw_register(_nw_notify_callback, (VOID*)pt_page_data, &pt_page_data->ui4_nw_nfy_id );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _update_ui();
    MENU_LOG_ON_FAIL(i4_ret);

    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_NET_AP_LIST_TIT_AP);
    menu_help_tip_keytip_show(FALSE);

    SET_RECT_BY_SIZE(&t_rect,
                 CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                 CONTENT_Y + MENU_ITEM_V_HEIGHT * 4 - ICON_ANIMATION_H/2,
                 ICON_ANIMATION_W,
                 ICON_ANIMATION_H);

    i4_ret =  menu_page_animation_get_handle(&h_menu_animation);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_move(h_menu_animation, &t_rect, FALSE);
    menu_page_animation_set_callback_fct(_menu_page_nw_ap_list_anim_cb_fct, NULL);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;

    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    if(pt_page_data->b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }

    i4_ret = a_nw_unregister(pt_page_data->ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_help_tip_keytip_show(TRUE);
    menu_network_hide_confirm_dialog(FALSE);

    pt_page_data->b_this_page_show = FALSE;
    pt_page_data->b_finish = TRUE;

    if(menu_timer_is_enabled()== FALSE)
    {
    }

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    NW_AP_LIST_PAGE_DATA_T* pt_page_data = &t_nw_ap_list_page_data;

    c_wgl_set_focus(pt_page_data->h_lb_ap_list, WGL_NO_AUTO_REPAINT);

    pt_page_data->b_this_page_show = TRUE;

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    /* set callback function for backbar */
    menu_set_backbar_proc(NULL) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    /* stop animation */
    menu_page_animation_stop();

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
extern INT32 menu_common_page_nw_ap_list_init(VOID)
{
    t_g_menu_common_page_nw_ap_list.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_nw_ap_list.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_nw_ap_list.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_nw_ap_list.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_nw_ap_list.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_nw_ap_list.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_nw_ap_list.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_ap_list_page_add_ap
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_ap_list_page_add_ap(NET_802_11_ESS_INFO_T* p_essInfo,
                                                 UINT8                  ui1_idx,
                                                 BOOL                   b_wireless_connected)
{
    INT32       i4_ret = MENUR_OK;

    if ((0 == ui1_idx) && b_wireless_connected)
    {
        DBG_ERROR(("%s,%s,%d,ui1_idx=%d,b_wireless_connected=%d\n",
                    __FILE__, __FUNCTION__, __LINE__, ui1_idx, b_wireless_connected));
        return MENUR_OK;
    }

    /* klockwork issue*/
    if (ui1_ap_num > (WLAN_AP_LB_MAX_NUM - 1))
    {
        return MENUR_OK;
    }

    aui1_ap_idx[ui1_ap_num] = ui1_idx;
    ui1_ap_num ++;

    i4_ret = _add_ap_list_elem(FALSE,
                      &p_essInfo->t_Ssid,
                      p_essInfo->i2_Level,
                      p_essInfo->e_AuthMode,
                      p_essInfo->e_AuthCipher);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_ap_list_page_clean_ap_list
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_ap_list_page_clean_ap_list(VOID)
{
    INT32       i4_ret;

    c_memset(aui1_ap_idx, 0, sizeof(UINT8)*WLAN_AP_LB_MAX_NUM);
    ui1_ap_num = 0;

    i4_ret = c_wgl_do_cmd(t_nw_ap_list_page_data.h_lb_ap_list,
                           WGL_CMD_LB_DEL_ALL,
                           NULL,
                           NULL );

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}
#endif /* APP_NETWORK_WIFI_SUPPORT */
