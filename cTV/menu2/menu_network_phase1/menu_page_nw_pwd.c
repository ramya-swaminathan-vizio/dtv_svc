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
 * $RCSfile: menu_page_nw_pwd.c,v $
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
#include "u_drv_cust.h"

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
#include "app_util/a_drv_interface.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/network/network_custom.h"

#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"
#include "wdk/vkb/vkb.h"

#include "menu_network.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define WLAN_CONNECTING_TIMEOUT     (12)   /*about 120 sec */

#define NW_PWD_KEY_MAX_LEN          (63+1)

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

    HANDLE_T     h_txt_auth_type;

    HANDLE_T     h_txt_suggest;

    HANDLE_T     h_action_connect;
    HANDLE_T     h_vkb;
    BOOL         b_vkb_showed;
    HANDLE_T     h_vkb_last_focus;

    BOOL         b_finish;
    BOOL         b_timer_result;

    UINT8        ui1_animation_count;

    CHAR         s_input_buf[NW_PWD_KEY_MAX_LEN+1];

    UINT32       ui4_nw_nfy_id;

    BOOL         b_this_page_show;

}NW_PSW_PAGE_DATA_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_pwd;
static  NW_PSW_PAGE_DATA_T    t_nw_pwd_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _anim_cb_fct(HANDLE_T                h_widget,
                      UINT16                  ui2_anim_type,
                      WGL_ANIM_COND_INF_T     e_anim_cond,
                      VOID*                   pv_tag);
static INT32 _show_wifi_pwd_vkb(BOOL b_repaint);

static VOID _nw_pwd_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                  VOID*     pv_tag);


/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

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
    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;
    INT32               i4_ret;
    BOOL                b_nw_connect;

    switch(pt_nw_nfy_data->e_nfy_id)
    {
        case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
        case NW_NFY_ID_DHCP_SUCCESS_LINKLOCAL:
        case NW_NFY_ID_DHCP_FAILURE_LINKLOCAL:
        {
            DBG_LOG_PRINT(("%s %d e_nfy_id=%d\n",__FUNCTION__,__LINE__,pt_nw_nfy_data->e_nfy_id));
            if (pt_page_data->b_finish == FALSE)
            {
                pt_page_data->b_finish = TRUE;
                pt_page_data->b_timer_result = TRUE;

                menu_netowrk_nav_go(NW_PAGE_ID_ROOT,NULL);
            }
            break;
        }
        case NW_NFY_ID_WLAN_ASSOCIATE:
        {
            DBG_LOG_PRINT(("%s,%s,%d,pv_nfy_param=%d,b_finish=%d,b_timer_result=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    (UINT32)(pt_nw_nfy_data->pv_nfy_param),
                    pt_page_data->b_finish, pt_page_data->b_timer_result));

            if(pt_page_data->b_finish)
            {
                break;
            }

            DBG_LOG_PRINT(("%s %d param=%d\n",__FUNCTION__,__LINE__,pt_nw_nfy_data->pv_nfy_param));
            if ((WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param) == WLAN_NFY_MSG_OK)
            {
                BOOL b_auto_ip_config  = FALSE;
                nw_custom_get_auto_ip_config_by_iface(&b_auto_ip_config, NW_NET_INTERFACE_WIFI);

                /*Only finish when associate OK.*/
                if(b_auto_ip_config)
                {
                    NET_802_11_ASSOCIATE_T* pt_associate = NULL;
                    menu_network_get_associate_data(&pt_associate);

                    if (pt_associate && IEEE_802_11_AUTH_MODE_WEPAUTO == pt_associate->e_AuthMode)
                    {
                        DBG_LOG_PRINT(("\n%s,%s,%d, IEEE_802_11_AUTH_MODE_WEPAUTO!!!\n",
                            __FILE__, __FUNCTION__, __LINE__));
                    }
                    else
                    {
                        /*for DHCP , to check dhcp*/
                        DBG_LOG_PRINT(("%s %d do nothing and wait for dhcp\n",__FUNCTION__,__LINE__));
                        //pt_page_data->b_finish = TRUE;
                        //pt_page_data->b_timer_result = TRUE;
                    }
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
            else if ((WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param) == WLAN_NFY_MSG_NO_MATCHED_CONFIG)
            {
                DBG_LOG_PRINT(("\n%s,%s,%d, PSK Incorrect!!!\n",
                        __FILE__, __FUNCTION__, __LINE__));

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

            DBG_LOG_PRINT(("%s,%s,%d,pv_nfy_param=%d,b_finish=%d,b_timer_result=%d\n",
                        __FILE__, __FUNCTION__, __LINE__,
                        (UINT32)(pt_nw_nfy_data->pv_nfy_param),
                        pt_page_data->b_finish, pt_page_data->b_timer_result));

            if (b_nw_connect)
            {
                if (pt_page_data->b_finish == FALSE)
                {
                    pt_page_data->b_finish = TRUE;
                    pt_page_data->b_timer_result = TRUE;
                }
            }
            else
            {
                if (pt_page_data->b_finish == FALSE)
                {
                    pt_page_data->b_finish = TRUE;
                    pt_page_data->b_timer_result = FALSE;
                }
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

    if(!t_nw_pwd_page_data.b_this_page_show)
    {
        return;
    }

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    menu_async_invoke(_nw_notify_handler,&t_nw_nfy_data,sizeof(_NW_NFY_DATA),TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _get_wlan_auth_mode_mlm_id
 *
 * Description:
 *
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_wlan_auth_mode_mlm_id(NET_802_11_AUTH_MODE_T  e_AuthMode)
{
    UINT16  ui2_mlm;

    switch(e_AuthMode)
    {
    case IEEE_802_11_AUTH_MODE_OPEN:
    case IEEE_802_11_AUTH_MODE_SHARED:
    case IEEE_802_11_AUTH_MODE_WEPAUTO:
        ui2_mlm = MLM_MENU_KEY_WIFI_AM_WEP;
        break;

    case IEEE_802_11_AUTH_MODE_WPA2:
    case IEEE_802_11_AUTH_MODE_WPA2_PSK:
    case IEEE_802_11_AUTH_MODE_WPA2_PSK_TKIP:
        ui2_mlm = MLM_MENU_KEY_WIFI_AM_WPA2;
        break;

    case IEEE_802_11_AUTH_MODE_WPA:
    case IEEE_802_11_AUTH_MODE_WPA_PSK:
    case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
    case IEEE_802_11_AUTH_MODE_WPA2_PSK_SHA256_AES:
        ui2_mlm = MLM_MENU_KEY_WIFI_AM_WPA;
        break;
    case IEEE_802_11_AUTH_MODE_WPA2_EAP:
        ui2_mlm = MLM_MENU_KEY_WIFI_AM_WPA2;
        break;
    case IEEE_802_11_AUTH_MODE_WPA_EAP:
        ui2_mlm = MLM_MENU_KEY_WIFI_AM_WPA;
        break;
    case IEEE_802_11_AUTH_MODE_WPA_SAE:
    case IEEE_802_11_AUTH_MODE_WPA2_SAE:
    case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2SAE:
        ui2_mlm = MLM_MENU_KEY_WIFI_AM_WPA3_SAE;
        break;
    default:
        ui2_mlm = MLM_MENU_KEY_EMPTY;
        break;
    }

    return ui2_mlm;

}

/*----------------------------------------------------------------------------
 * Name: _ap_list_page_show
 *
 * Description:
 *
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_wlan_auth_cipher_mlm_id(NET_802_11_AUTH_CIPHER_T e_AuthCipher)
{
    UINT16  ui2_mlm;

    switch(e_AuthCipher)
    {
    case IEEE_802_11_AUTH_CIPHER_TKIP:
        ui2_mlm = MLM_MENU_KEY_WIFI_CIPHER_TKIP;
        break;
    case IEEE_802_11_AUTH_CIPHER_AES:
        ui2_mlm = MLM_MENU_KEY_WIFI_CIPHER_AES;
        break;
    case IEEE_802_11_AUTH_CIPHER_AES_OR_TKIP:
        ui2_mlm = MLM_MENU_KEY_WIFI_CIPHER_AES_OR_TKIP;
        break;
    default:
        ui2_mlm = MLM_MENU_KEY_EMPTY;
        break;
    }

    return ui2_mlm;

}
/*----------------------------------------------------------------------------
 * Name: _update_net_info_data
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
static INT32 _set_suggest_txt(NET_802_11_AUTH_MODE_T  e_AuthMode)
{
    UINT16  ui2_mlm;
    INT32       i4_ret;

    switch(e_AuthMode)
    {
        case IEEE_802_11_AUTH_MODE_OPEN:
        case IEEE_802_11_AUTH_MODE_SHARED:
        case IEEE_802_11_AUTH_MODE_WEPAUTO:
            ui2_mlm = MLM_MENU_KEY_NW_PWS_TIT_WEP;
            break;
        case IEEE_802_11_AUTH_MODE_WPA2:
        case IEEE_802_11_AUTH_MODE_WPA2_PSK:
        case IEEE_802_11_AUTH_MODE_WPA2_PSK_TKIP:
            ui2_mlm = MLM_MENU_KEY_NW_PWS_TIT_WPA2;
            break;

        case IEEE_802_11_AUTH_MODE_WPA:
        case IEEE_802_11_AUTH_MODE_WPA_PSK:
        case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
            ui2_mlm = MLM_MENU_KEY_NW_PWS_TIT_WPA;
            break;
        case IEEE_802_11_AUTH_MODE_WPA2_EAP:
            ui2_mlm = MLM_MENU_KEY_NW_PWS_TIT_WPA2;
            break;
        case IEEE_802_11_AUTH_MODE_WPA_EAP:
            ui2_mlm = MLM_MENU_KEY_NW_PWS_TIT_WPA;
            break;
        case IEEE_802_11_AUTH_MODE_WPA_SAE:
        case IEEE_802_11_AUTH_MODE_WPA2_SAE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2SAE:
            ui2_mlm = MLM_MENU_KEY_NW_PWS_TIT_WPA3_SAE;
            break;
        default:
            ui2_mlm = MLM_MENU_KEY_EMPTY;
            break;
    }

    i4_ret = c_wgl_do_cmd(t_nw_pwd_page_data.h_txt_suggest,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(MENU_TEXT(ui2_mlm)),
                        WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(MENU_TTS_TEXT(ui2_mlm), c_uc_w2s_strlen(MENU_TTS_TEXT(ui2_mlm)));
#endif

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

    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;

    NET_802_11_ASSOCIATE_T* pt_associate = NULL;

    GL_RECT_T          t_rect = {0};
    HANDLE_T           h_menu_animation = NULL_HANDLE;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT*2,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT*2);
    MENU_LOG_ON_FAIL (c_wgl_move(pt_page_data->h_txt_suggest,&t_rect, FALSE));

    SET_RECT_BY_SIZE (& t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT*4,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT) ;
    MENU_LOG_ON_FAIL (c_wgl_move(pt_page_data->h_action_connect,&t_rect, FALSE));

    i4_ret = menu_action_chg_lang(pt_page_data->h_action_connect,
                                 MLM_MENU_KEY_NW_CON,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_network_get_associate_data(&pt_associate);

    if(pt_associate == NULL)
    {
        return MENUR_OK;
    }

    i4_ret = c_wgl_do_cmd(pt_page_data->h_txt_auth_type,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(_get_wlan_auth_mode_mlm_id(pt_associate->e_AuthMode))),
                          WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_txt_auth_type,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(MENU_TEXT(_get_wlan_auth_cipher_mlm_id(pt_associate->e_AuthCipher))),
                        WGL_PACK(0xff));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _set_suggest_txt(pt_associate->e_AuthMode);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _show_wifi_pwd_vkb(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_network_last_shadow_update_position(pt_page_data->h_action_connect, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                 CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                 CONTENT_Y + MENU_ITEM_V_HEIGHT * 3 - ICON_ANIMATION_H - 10,
                 ICON_ANIMATION_W,
                 ICON_ANIMATION_H);

    i4_ret =  menu_page_animation_get_handle(&h_menu_animation);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_move(h_menu_animation, &t_rect, FALSE);
    menu_page_animation_set_callback_fct(_anim_cb_fct, NULL);

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _show_wifi_pwd_vkb
 *
 * Description:
 *  Update the cust lbl name to the virtual keyboard UI.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _show_wifi_pwd_vkb(BOOL b_repaint)
{
    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;
    INT32    i4_ret = MENUR_OK;
    GL_RECT_T                      t_rect = {0};
    UTF16_T      w2s_star_txt[NW_PWD_KEY_MAX_LEN +1] = {0};    /* input text value: UTF16_T */

    /* set max char num to MAX_LBL_NAME_LEN */
    a_vkb_do_cmd (pt_page_data->h_vkb,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*)(NW_PWD_KEY_MAX_LEN+1),
                   NULL);

    c_memset(w2s_star_txt, 0, sizeof(w2s_star_txt));
    c_uc_ps_to_w2s (pt_page_data->s_input_buf, w2s_star_txt, NW_PWD_KEY_MAX_LEN);


    /* set initial editbox text */
    a_vkb_do_cmd (pt_page_data->h_vkb,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_star_txt,
                  (VOID*) 0xFF);
    a_vkb_set_focus(pt_page_data->h_vkb);
    menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    i4_ret=  a_vkb_set_visibility(pt_page_data->h_vkb, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT,
                     MENU_ITEM_V_WIDE,
                     GRID_H*8 + 20 - 218 - MENU_ITEM_V_HEIGHT);
    MENU_LOG_ON_FAIL (c_wgl_move(pt_page_data->h_txt_suggest,&t_rect, FALSE));

    SET_RECT_BY_SIZE (& t_rect,
                     MENU_ITEM_V_INSET_L,
                     GRID_H*11 - MENU_ITEM_V_HEIGHT,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT) ;
    MENU_LOG_ON_FAIL (c_wgl_move(pt_page_data->h_action_connect,&t_rect, FALSE));

    pt_page_data->b_vkb_showed = TRUE;

    if (b_repaint)
    {
        c_wgl_repaint(pt_page_data->h_cnt_frm, NULL, TRUE);
    }

    return WDKR_OK;
}

static INT32 _action_connect_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2);

static VOID _nw_pwd_confirm_dialog_try_again_cb_fct(UINT32 ui4_key_code)
{
    if ((BTN_CURSOR_LEFT  == ui4_key_code) ||
         BTN_CURSOR_RIGHT == ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_another();
    }
    else
    {
#ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
#endif
        menu_network_hide_confirm_dialog(TRUE);

        t_nw_pwd_page_data.b_finish = TRUE;
        a_vkb_set_focus_ex(t_nw_pwd_page_data.h_vkb);
    }
}

static VOID _nw_pwd_confirm_dialog_try_another_cb_fct(UINT32 ui4_key_code)
{
    if ((BTN_CURSOR_LEFT  == ui4_key_code) ||
         BTN_CURSOR_RIGHT == ui4_key_code)
    {
        nw_confirm_dialog_set_focus_try_again();
    }
    else
    {
    #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
    #endif

        menu_network_hide_confirm_dialog(TRUE);
        menu_netowrk_nav_back();
    }
}

/*----------------------------------------------------------------------------
 * Name: _menu_page_nw_pwd_timer_finish
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
static INT32 _menu_page_nw_pwd_timer_finish(BOOL b_success)
{
    INT32    i4_ret = MENUR_OK;
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;
    UTF16_T w2s_ssid[32+1] = {0};
    UTF16_T w2s_title[128+1] = {0};
    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;

    pt_page_data->b_finish = TRUE;

    c_timer_stop(pt_page_data->h_timer);

    /* stop animation */
    i4_ret = menu_page_animation_stop();
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_success)
    {
        //i4_ret = menu_netowrk_nav_go(NW_PAGE_ID_ROOT,NULL);
        i4_ret = menu_netowrk_connect_success_back();
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
                                            _nw_pwd_confirm_dialog_try_again_cb_fct,
                                            _nw_pwd_confirm_dialog_try_another_cb_fct,
                                            TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
        c_wgl_repaint(t_nw_pwd_page_data.h_cnt_frm,NULL,TRUE);
    }

    return i4_ret;
}

static VOID _nw_pwd_do_timer_nfy(
    VOID*   pv_data,
    SIZE_T  z_data_size)
{
    INT32               i4_ret = 0;
    BOOL                b_success = FALSE;
    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;

    if (FALSE == pt_page_data->b_this_page_show)
    {
        c_timer_stop(pt_page_data->h_timer);
        return;
    }

    if (pt_page_data->b_finish)
    {
        b_success = pt_page_data->b_timer_result;

        i4_ret = _menu_page_nw_pwd_timer_finish(b_success);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

static VOID _nw_pwd_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                       VOID*     pv_tag)
{
    menu_async_invoke(_nw_pwd_do_timer_nfy, NULL, 0, TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _do_anim_nfy
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
static VOID _do_anim_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{

    INT32    i4_ret = MENUR_OK;

    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;
    BOOL    b_success = FALSE;
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
        b_success = pt_page_data->b_timer_result;

        i4_ret = _menu_page_nw_pwd_timer_finish(b_success);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(pt_page_data->ui1_animation_count > ui1_timeout_count)
    {
        i4_ret = _menu_page_nw_pwd_timer_finish(FALSE);
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
 * Name: _anim_cb_fct
 *
 * Description:test the network status
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _anim_cb_fct(HANDLE_T                h_widget,
                      UINT16                  ui2_anim_type,
                      WGL_ANIM_COND_INF_T     e_anim_cond,
                      VOID*                   pv_tag)
{
    if (_ANIM_TOTAL_END(&e_anim_cond))
    {
        menu_async_invoke(_do_anim_nfy, NULL, 0, TRUE);
    }
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _is_valid_input_key
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
static BOOL _is_valid_hex_string(CHAR*                     s_input,
                             UINT8                     ui1_length)
{
    BOOL b_valid = TRUE;
    UINT8 ui1_idx = 0;

    for(ui1_idx=0; ui1_idx<ui1_length; ui1_idx++)
    {
        if( (s_input[ui1_idx] >='0' &&  s_input[ui1_idx] <='9')
            || (s_input[ui1_idx] >='a' &&  s_input[ui1_idx] <='f')
            || (s_input[ui1_idx] >='A' &&  s_input[ui1_idx] <='F')
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
 * Name: _is_valid_input_key
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
static BOOL _is_valid_wep_input_key(NET_802_11_AUTH_CIPHER_T    e_AuthCipher,
                             CHAR*                      s_input,
                             BOOL*                      pb_IsAscii)
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
            b_valid = TRUE;
            *pb_IsAscii = TRUE;
        }
        else if(ui1_length == 10)
        {
            *pb_IsAscii = FALSE;
            b_valid = _is_valid_hex_string(s_input, ui1_length);
        }
        else
        {
            b_valid = FALSE;
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

            b_valid = _is_valid_hex_string(s_input, ui1_length);
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
 * Name: _is_valid_input_key
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
static BOOL _is_valid_input_key(NET_802_11_ASSOCIATE_T*    pt_associate,
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

        b_valid = _is_valid_wep_input_key (IEEE_802_11_AUTH_CIPHER_WEP40,
                                           s_input,
                                           pb_IsAscii);
        if(b_valid)
        {
            pt_associate->e_AuthCipher = IEEE_802_11_AUTH_CIPHER_WEP40;
        }
        else
        {

            b_valid = _is_valid_wep_input_key (IEEE_802_11_AUTH_CIPHER_WEP104,
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
    case IEEE_802_11_AUTH_MODE_WPA2_PSK_TKIP:
    {   /*check wpa input key*/

        UINT8 ui1_length = (UINT8)c_strlen(s_input);

        if(ui1_length < 8 || ui1_length > 64)
        {
            b_valid = FALSE;
        }
        else if(ui1_length == 64)
        {
            *pb_IsAscii = FALSE;

            b_valid = _is_valid_hex_string(s_input, ui1_length);
        }
        else
        {
            b_valid = TRUE;
            *pb_IsAscii = TRUE;
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
 * Name: _wifi_associate
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
static INT32 _wifi_associate(VOID)
{
    INT32                   i4_ret;
    NW_PSW_PAGE_DATA_T*     pt_page_data                    = &t_nw_pwd_page_data;
    NET_802_11_ASSOCIATE_T* pt_associate                    = NULL;
    UTF16_T                 w2s_ssid[32+1]                  = {0};
    UTF16_T                 w2s_title[128+1]                = {0};
    UTF16_T                 w2s_str[NW_PWD_KEY_MAX_LEN + 1] = {0};
    BOOL                    b_valid                         = TRUE;
    BOOL                    b_IsAscii                       = FALSE;

    i4_ret = menu_network_get_associate_data(&pt_associate);
    MENU_LOG_ON_FAIL(i4_ret);

    if(pt_associate == NULL)
    {
        return MENUR_OK;
    }

    if(pt_page_data->b_vkb_showed)
    {
        /* retrieve the new channel name. */
        i4_ret = a_vkb_do_cmd(pt_page_data->h_vkb,
                     VKB_CMD_GET_EB_CONTENT,
                     WGL_PACK (w2s_str),
                     WGL_PACK (NW_PWD_KEY_MAX_LEN));
        MENU_LOG_ON_FAIL(i4_ret);
        c_memset(t_nw_pwd_page_data.s_input_buf,0,sizeof(t_nw_pwd_page_data.s_input_buf));
        i4_ret = c_uc_w2s_to_ps(w2s_str, t_nw_pwd_page_data.s_input_buf,NW_PWD_KEY_MAX_LEN);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    b_valid = _is_valid_input_key(pt_associate,
                                  t_nw_pwd_page_data.s_input_buf,
                                  &b_IsAscii);

    if (b_valid)
    {
        pt_associate->t_Key.pui1_PassPhrase = t_nw_pwd_page_data.s_input_buf;
        pt_associate->t_Key.b_IsAscii = b_IsAscii;

        pt_page_data->b_finish = FALSE;
        pt_page_data->b_timer_result = FALSE;

        /* init the animation count as 0*/
        pt_page_data->ui1_animation_count = 0;
        i4_ret = menu_page_animation_start(1, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_timer_start(pt_page_data->h_timer,
                               200,
                               X_TIMER_FLAG_REPEAT,
                               _nw_pwd_timer_cb_fct,
                               NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* disable the menu timer */
        menu_timer_enable(FALSE);
        menu_timer_stop();

        i4_ret = a_nw_custom_wlan_disassociate();
        if (i4_ret != NWR_OK)
        {
            pt_page_data->b_finish = TRUE;
        }

        i4_ret = a_nw_wlan_associate(pt_associate);
        if (i4_ret != NWR_OK)
        {
            pt_page_data->b_finish = TRUE;
        }
    }
    else
    {
        c_uc_ps_to_w2s(pt_associate->t_Ssid.ui1_aSsid, w2s_ssid, 32);

        c_uc_w2s_strcpy(w2s_title, MENU_TEXT(MLM_MENU_KEY_NW_CON_FAIL));
        c_uc_w2s_strcat(w2s_title, w2s_ssid);

        i4_ret = menu_network_show_confirm_dialog_ex(w2s_title,
                                            MENU_TEXT(MLM_MENU_KEY_NW_WIFI_TRY_AGAIN),
                                            MENU_TEXT(MLM_MENU_KEY_NW_WIFI_TRY_ANOTHER),
                                            _nw_pwd_confirm_dialog_try_again_cb_fct,
                                            _nw_pwd_confirm_dialog_try_another_cb_fct,
                                            TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
        c_wgl_repaint(t_nw_pwd_page_data.h_cnt_frm,NULL,TRUE);
    }

    return MENUR_OK;
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
        {
            UTF16_T             w2s_str[NW_PWD_KEY_MAX_LEN+1] = {0};
            INT32               i4_ret = MENUR_OK;

            if(t_nw_pwd_page_data.b_vkb_showed)
            {
                /* retrieve the new channel name. */
                i4_ret = a_vkb_do_cmd(t_nw_pwd_page_data.h_vkb,
                             VKB_CMD_GET_TEXT,
                             WGL_PACK (w2s_str),
                             WGL_PACK (NW_PWD_KEY_MAX_LEN));
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_uc_w2s_to_ps(w2s_str, t_nw_pwd_page_data.s_input_buf,NW_PWD_KEY_MAX_LEN);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            //else
            {
                menu_netowrk_nav_back();
            }

            menu_pm_repaint();
            return MENUR_OK;
        }
        case BTN_CURSOR_DOWN:
            a_vkb_set_focus_ex(t_nw_pwd_page_data.h_vkb);
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
 * Name: _action_connect_proc_fct
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
static INT32 _action_connect_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        if(t_nw_pwd_page_data.b_finish == FALSE)
        {
            return WGLR_OK;
        }

        switch ((UINT32)pv_param1)
        {
        case BTN_SELECT :
            _wifi_associate();
            return WGLR_OK;

        case BTN_CURSOR_UP :
            c_wgl_set_focus(t_nw_pwd_page_data.h_vkb_last_focus, WGL_NO_AUTO_REPAINT);
            c_wgl_repaint(t_nw_pwd_page_data.h_cnt_frm, NULL, TRUE);
            return WGLR_OK;
        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_netowrk_nav_back();
            return WGLR_OK;

        default :
            return WGLR_OK;
        }
    }
    else if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
    #ifdef APP_TTS_SUPPORT
        a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_NW_CON), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_NW_CON)));
    #endif
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
    #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
    #endif
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wifi_pwd_vbk_data_change_nfy
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
static INT32 _wifi_pwd_vbk_data_change_nfy (
    VOID*    pv_tag,
    UINT32   ui4_msg,
    VOID*    pv_param1,
    VOID*    pv_param2)
{
    INT32               i4_ret       = WDKR_OK;

    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        UINT32*  pui4_key_code = (UINT32*) pv_param1;
        BOOL     b_is_top_bottom = FALSE;
        NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;

        if (FALSE == pt_page_data->b_finish)
        {
            return WDK_NO_ACTION;
        }

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
            {
                menu_netowrk_nav_back();
                break;
            }

            case BTN_SELECT:
            {
                i4_ret = a_vkb_current_is_top_row(pt_page_data->h_vkb,&b_is_top_bottom);

                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }

                if(TRUE == b_is_top_bottom)
                {
                    _wifi_associate();
                    i4_ret = WDK_NO_ACTION;
                }
                break;
            }
            case BTN_CURSOR_UP:
                i4_ret = a_vkb_current_is_top_row(pt_page_data->h_vkb,&b_is_top_bottom);
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }
                if(TRUE == b_is_top_bottom)
                {
                    menu_set_focus_on_backbar(TRUE);
                    i4_ret = WDK_NO_ACTION;
                }
                break;
            case BTN_CURSOR_DOWN:
            {
                i4_ret = a_vkb_current_is_bottom_row(pt_page_data->h_vkb,&pt_page_data->h_vkb_last_focus,&b_is_top_bottom);

                DBG_INFO(("_wifi_pwd_vbk_data_change_nfy() i4_ret = %d, b_is_top_bottom = %d\n",
                                                                        i4_ret,
                                                                        b_is_top_bottom));
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }
                if(TRUE == b_is_top_bottom)
                {
                    c_wgl_set_focus(pt_page_data->h_action_connect, WGL_SYNC_AUTO_REPAINT);
                    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
                    i4_ret = WDK_NO_ACTION;
                }
            }
                break;
            default :
                break;
        }
    }

    return i4_ret;
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
static INT32 _auth_type_text_create(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;

    WGL_IMG_INFO_T    t_img_info;
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
        MENU_ITEM_V_HEIGHT};

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     0,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT);

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
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
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
static INT32 _txt_suggest_create(
    HANDLE_T    h_parent,
    HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T            t_clr_info;
    WGL_FONT_INFO_T             t_fnt_info;

    WGL_INSET_T t_inset = {
        FRAME_LEFT_RIGHT_INTV,
        FRAME_LEFT_RIGHT_INTV,
        20,
        0};

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     MENU_ITEM_V_HEIGHT,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT*2);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TRANSP,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_128 |WGL_STL_TEXT_MULTILINE|WGL_STL_GL_NO_BK |WGL_STL_GL_NO_IMG_UI),
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
                          (VOID*)WGL_AS_LEFT_TOP,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_fnt_info.e_font_style = MENU_ITEM_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_widget,
                                  WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wifi_pwd_vkb_create
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
static INT32 _wifi_pwd_vkb_create(VOID)
{
    INT32       i4_ret;

    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;
    VKB_INIT_T           t_init_data;

    /* Create Virtual key board */
    t_init_data.h_parent            = pt_page_data->h_cnt_frm;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_WIFI_PWD | VKB_STYLE_MASK_WITH_EB_CLEAR;
    t_init_data.t_gui_rc.i4_left    = FRAME_LEFT_RIGHT_INTV;
    t_init_data.t_gui_rc.i4_top     = GRID_H*9 - 250*4/3 - MENU_ITEM_V_HEIGHT;
    t_init_data.pf_data_change_fct  = _wifi_pwd_vbk_data_change_nfy;
    t_init_data.pv_tag              = NULL;

    i4_ret = a_vkb_create(&t_init_data,&pt_page_data->h_vkb);
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

    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;

    c_memset(pt_page_data, 0, sizeof(NW_PSW_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _auth_type_text_create(pt_page_data->h_cnt_frm, &pt_page_data->h_txt_auth_type);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)4,
                                _action_connect_proc_fct,
                                &pt_page_data->h_action_connect);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _txt_suggest_create(pt_page_data->h_cnt_frm,
                                &pt_page_data->h_txt_suggest);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id, _widgets_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _wifi_pwd_vkb_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&(pt_page_data->h_timer));
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;

    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;

    i4_ret = a_nw_register(_nw_notify_callback, (VOID*)pt_page_data, &pt_page_data->ui4_nw_nfy_id );
    MENU_LOG_ON_FAIL(i4_ret);

    /*update the network info data*/
    pt_page_data->b_this_page_show = TRUE;

    c_memset(pt_page_data->s_input_buf, 0, sizeof(CHAR)*65);

    i4_ret = _update_ui();
    MENU_LOG_ON_FAIL(i4_ret);
    c_wgl_set_visibility(pt_page_data->h_cnt_frm,WGL_SW_RECURSIVE);
    c_wgl_repaint(pt_page_data->h_cnt_frm,NULL,TRUE);
    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_NW_PWD_PAGE_TIT);
    menu_help_tip_keytip_show(FALSE);

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;

    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;

    if(pt_page_data->b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }

    i4_ret = a_nw_unregister(pt_page_data->ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* disassociate wifi immediately */
    if (FALSE == pt_page_data->b_finish)
    {
        i4_ret = a_nw_custom_wlan_disassociate();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = menu_network_last_shadow_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_help_tip_keytip_show(TRUE);
    menu_network_hide_confirm_dialog(FALSE);

    pt_page_data->b_this_page_show = FALSE;
    pt_page_data->b_finish = TRUE;

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    NW_PSW_PAGE_DATA_T* pt_page_data = &t_nw_pwd_page_data;

    a_vkb_set_focus(pt_page_data->h_vkb);

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
extern INT32 menu_common_page_nw_pwd_init(VOID)
{
    t_g_menu_common_page_nw_pwd.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_nw_pwd.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_nw_pwd.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_nw_pwd.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_nw_pwd.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_nw_pwd.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_nw_pwd.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}
