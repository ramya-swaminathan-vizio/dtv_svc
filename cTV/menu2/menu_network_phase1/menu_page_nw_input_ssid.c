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
 * $RCSfile: menu_page_nw_input_ssid.c,v $
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

#include "wdk/a_vkb.h"
#include "wdk/a_wdk.h"
#include "res/wdk/a_vkb_custom.h"
#include "wdk/vkb/vkb.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/network/network_custom.h"

#include "menu_network.h"
#include "menu2/menu_dbg.h"

#ifdef APP_NETWORK_WIFI_SUPPORT
/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define WLAN_SCANNING_TIMEOUT         (15)   /*about 90 s*/
#define WLAN_CONNECTING_TIMEOUT       (5)    /*about 30 s*/

#define NW_SSID_MAX_LEN           (32+1)

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
    HANDLE_T     h_check_timer;

    HANDLE_T     h_timer;

    HANDLE_T     h_cnt_frm;

    HANDLE_T     h_txt_suggest;

    HANDLE_T     h_action_connect;
    HANDLE_T     h_action_show_vkb;

    HANDLE_T     h_vkb;
    BOOL         b_vkb_showed;
    HANDLE_T     h_vkb_last_focus;

    BOOL         b_connec_timer;
    BOOL         b_finish;
    BOOL         b_timer_result;

    UINT8        ui1_animation_count;

    CHAR         s_input_buf[NW_SSID_MAX_LEN+1];

    UINT32       ui4_nw_nfy_id;

    BOOL         b_this_page_show;

}NW_INP_SSID_PAGE_DATA_T;

static UINT8        ui1_g_ssid_check_count = 0;

static UINT8        ui1_g_ssid_scan_count = 0;

static BOOL         b_connect_btn_enable = TRUE;
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_common_page_nw_input_ssid;
static  NW_INP_SSID_PAGE_DATA_T    t_nw_input_ssid_page_data;

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static INT32 _anim_cb_fct(HANDLE_T                h_widget,
                      UINT16                  ui2_anim_type,
                      WGL_ANIM_COND_INF_T     e_anim_cond,
                      VOID*                   pv_tag);
static INT32 _show_wifi_ssid_vkb(BOOL b_repaint);

static INT32 _check_scan_result(VOID);

static INT32 _wifi_associate_special_ssid(VOID);

static BOOL _menu_nw_is_ssid_scan_success(VOID);

static INT32 _wifi_ssid_update_connect_btn(BOOL b_enable, BOOL b_repaint);

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
    _NW_NFY_DATA*            pt_nw_nfy_data = (_NW_NFY_DATA*)pv_data;
    NW_INP_SSID_PAGE_DATA_T* pt_page_data   = &t_nw_input_ssid_page_data;
    BOOL                     b_nw_connect;

    switch(pt_nw_nfy_data->e_nfy_id)
    {
        case NW_NFY_ID_WLAN_ASSOCIATE:
        {
            WLAN_NOTIFY_MSG_T e_result = (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param);
            DBG_LOG_PRINT(("[%s %s %d] NW_NFY_ID_WLAN_ASSOCIATE result = %d\n",
                       __FILE__,
                       __FUNCTION__,
                       __LINE__,
                       e_result));

            if(pt_page_data->b_connec_timer == FALSE)
            {
                break;
            }

            if (e_result == WLAN_NFY_MSG_OK)
            {
                pt_page_data->b_finish = TRUE;
                pt_page_data->b_timer_result = TRUE;

            }
            else if (e_result == WLAN_NFY_MSG_PSK_INCORRECT)
            {
                pt_page_data->b_finish = TRUE;
                pt_page_data->b_timer_result = FALSE;
            }

            break;
        }
        case NW_NFY_ID_WLAN_SCAN:
        {
            WLAN_NOTIFY_MSG_T e_result = (WLAN_NOTIFY_MSG_T)(UINT32)(pt_nw_nfy_data->pv_nfy_param);
            DBG_LOG_PRINT(("[%s %s %d], NW_NFY_ID_WLAN_SCAN pt_page_data->b_finish:%d,pt_page_data->b_connec_timer=%d\n",
                       __FILE__,
                       __FUNCTION__,
                       __LINE__,
                       pt_page_data->b_finish,
                       pt_page_data->b_connec_timer));

            if(pt_page_data->b_connec_timer)
            {
                break;
            }

            /* if already finish, like timeout, just break */
            if (pt_page_data->b_finish)
            {
                break;
            }

            pt_page_data ->b_timer_result = FALSE;
            if ( WLAN_NFY_MSG_OK == e_result)
            {
                ui1_g_ssid_check_count = 0;
                _check_scan_result();
            }
            else
            {
                DBG_LOG_PRINT(("\n\n\r~~~~%s, %s, %d, e_result =%d\n\n\r~~~~",
                           __FILE__,
                           __FUNCTION__,
                           __LINE__,
                           e_result));

                pt_page_data ->b_finish = TRUE;
                pt_page_data ->b_timer_result = FALSE;
            }
            break;
        }
        case NW_NFY_ID_ETHERNET_PLUGIN:
        {
            menu_nav_go_home_menu();
            break;
        }
        case NW_NFY_ID_INTERN_CT_RESULT:
            b_nw_connect = (BOOL)(UINT32)(pt_nw_nfy_data->pv_nfy_param);

            DBG_LOG_PRINT(("\n\n\r %s, %s, %d, connect result is %d",
                        __FILE__,
                        __FUNCTION__,
                        __LINE__,
                        (UINT32)(pt_nw_nfy_data->pv_nfy_param)));

            pt_page_data->b_finish = TRUE;

            if (b_nw_connect)
            {
                if (pt_page_data->b_finish == FALSE)
                {
                    pt_page_data->b_timer_result = TRUE;
                }
            }
            else
            {
                if (pt_page_data->b_finish == FALSE)
                {
                    pt_page_data->b_timer_result = FALSE;
                }
            }

            break;

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

    if(!t_nw_input_ssid_page_data.b_this_page_show)
    {
        return;
    }

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    menu_async_invoke(_nw_notify_handler,&t_nw_nfy_data,sizeof(_NW_NFY_DATA),TRUE);
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
static INT32 _set_suggest_txt(VOID)
{
    INT32       i4_ret;

    i4_ret = c_wgl_do_cmd(t_nw_input_ssid_page_data.h_txt_suggest,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NW_INP_AP_TIT)),
                        WGL_PACK(0xff));
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
    UTF16_T     w2s_str[NW_SSID_MAX_LEN+1] = {0};
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    GL_RECT_T          t_rect = {0};
    HANDLE_T           h_menu_animation = NULL_HANDLE;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     0 + 5,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT*3);
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

    #if 0
    i4_ret = menu_action_chg_lang(pt_page_data->h_action_show_vkb,
                                 MLM_MENU_KEY_NW_SHOW_KB,
                                 MLM_MENU_KEY_EMPTY);
    #endif
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _set_suggest_txt();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _show_wifi_ssid_vkb(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);


    /* update connect button state */
    a_vkb_do_cmd(pt_page_data->h_vkb,
                 VKB_CMD_GET_EB_CONTENT,
                 (VOID *)w2s_str,
                 (VOID*)(NW_SSID_MAX_LEN+1));

    if (c_uc_w2s_strlen(w2s_str) == 0)
    {
        b_connect_btn_enable = FALSE;
    }
    else
    {
        b_connect_btn_enable = TRUE;
    }
    _wifi_ssid_update_connect_btn(b_connect_btn_enable, FALSE);

    SET_RECT_BY_SIZE(&t_rect,
                 CONTENT_X + (CONTENT_W -ICON_ANIMATION_W)/2,
                 CONTENT_Y + MENU_ITEM_V_HEIGHT * 3 - ICON_ANIMATION_H - 20,
                 ICON_ANIMATION_W,
                 ICON_ANIMATION_H);

    i4_ret =  menu_page_animation_get_handle(&h_menu_animation);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_move(h_menu_animation, &t_rect, FALSE);
    menu_page_animation_set_callback_fct(_anim_cb_fct, NULL);

    return MENUR_OK;

}

/*----------------------------------------------------------------------------
 * Name: _show_wifi_ssid_vkb
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
static INT32 _show_wifi_ssid_vkb(BOOL b_repaint)
{
    NW_INP_SSID_PAGE_DATA_T*    pt_page_data = &t_nw_input_ssid_page_data;
    INT32                       i4_ret = MENUR_OK;
    GL_RECT_T                   t_rect = {0};
    UTF16_T                     w2s_star_txt[NW_SSID_MAX_LEN +1] = {0};

    /* set max char num to MAX_LBL_NAME_LEN */
    a_vkb_do_cmd (pt_page_data->h_vkb,
                   VKB_CMD_SET_MAX_CHAR_NUM,
                   (VOID*) NW_SSID_MAX_LEN,
                   NULL);

    c_memset(w2s_star_txt, 0, sizeof(w2s_star_txt));
    c_uc_ps_to_w2s (pt_page_data->s_input_buf, w2s_star_txt, NW_SSID_MAX_LEN);

    /* set initial editbox text */
    a_vkb_do_cmd (pt_page_data->h_vkb,
                  VKB_CMD_SET_INITIAL_TEXT,
                  (VOID*) w2s_star_txt,
                  (VOID*) 0xFF);

    a_vkb_set_focus(pt_page_data->h_vkb);

    menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    i4_ret=  a_vkb_set_visibility(pt_page_data->h_vkb, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     0,
                     MENU_ITEM_V_WIDE,
                     GRID_H*3);
    MENU_LOG_ON_FAIL (c_wgl_move(pt_page_data->h_txt_suggest,&t_rect, FALSE));

    SET_RECT_BY_SIZE (& t_rect,
                     MENU_ITEM_V_INSET_L,
                     GRID_H*11 - MENU_ITEM_V_HEIGHT,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT) ;
    MENU_LOG_ON_FAIL (c_wgl_move(pt_page_data->h_action_connect,&t_rect, FALSE));

    i4_ret = menu_network_last_shadow_update_position(pt_page_data->h_action_connect, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_vkb_showed = TRUE;

    if (b_repaint)
    {
        c_wgl_repaint(pt_page_data->h_cnt_frm, NULL, TRUE);
    }

    return WDKR_OK;
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
static VOID _nw_confirm_dialog_cb_fct(UINT32 ui4_key_code)
{
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

#ifdef APP_TTS_SUPPORT
    a_app_tts_stop(APP_TTS_STOP_FORCE);
#endif

    menu_network_hide_confirm_dialog(TRUE);

    /* set focus to vkb delete icon , same behavior with password page */
    a_vkb_set_focus_ctrl_del(pt_page_data->h_vkb, TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _menu_page_nw_input_ssid_timer_finish
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
static INT32 _menu_page_nw_input_ssid_timer_finish(BOOL b_success)
{
    INT32       i4_ret = MENUR_OK;
    UTF16_T     w2s_str[NW_SSID_MAX_LEN+1];
    UTF16_T     w2s_msg[128+1] = {0};
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    pt_page_data->b_finish = TRUE;

    c_timer_stop(pt_page_data->h_timer);
    c_timer_stop(pt_page_data->h_check_timer);

    /* stop animation */
    menu_page_animation_stop();

    if (b_success)
    {
        if( pt_page_data->b_connec_timer)
        {
            menu_netowrk_nav_go(NW_PAGE_ID_ROOT,NULL);
        }
        else
        {
            DBG_LOG_PRINT(("\n\n\r~~~~%s, %s, %d, enter into ssid page to input ssid.~~~~",
                        __FILE__,
                        __FUNCTION__,
                        __LINE__));

            menu_netowrk_nav_go(NW_PAGE_ID_PWD, NULL);
        }
    }
    else
    {
        c_memset(w2s_str, 0, sizeof(UTF16_T)*(NW_SSID_MAX_LEN +1));
        c_memset(w2s_msg, 0, sizeof(UTF16_T)*(128+1));

        c_uc_ps_to_w2s(pt_page_data->s_input_buf, w2s_str, NW_SSID_MAX_LEN);

        c_uc_w2s_strcpy(w2s_msg, MENU_TEXT(MLM_MENU_KEY_NW_CON_FAIL));
        c_uc_w2s_strcat(w2s_msg, w2s_str);

        i4_ret = menu_network_show_confirm_dialog(w2s_msg,
                                                  MENU_TEXT(MLM_MENU_KEY_NW_WIFI_TRY_AGAIN),
                                                  _nw_confirm_dialog_cb_fct,
                                                  TRUE);
        MENU_LOG_ON_FAIL(i4_ret);

        menu_pm_repaint();
    }

    return MENUR_OK;
}

static VOID _nw_ssid_do_timer_nfy(
    VOID*   pv_data,
    SIZE_T  z_data_size)
{
    INT32               i4_ret = 0;
    BOOL                b_success = FALSE;
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    if (FALSE == pt_page_data->b_this_page_show)
    {
        c_timer_stop(pt_page_data->h_timer);
        return;
    }

    if (pt_page_data->b_finish)
    {
        b_success = pt_page_data->b_timer_result;

        i4_ret = _menu_page_nw_input_ssid_timer_finish(b_success);
        MENU_LOG_ON_FAIL(i4_ret);
    }
}

static VOID _nw_ssid_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                  VOID*      pv_tag)
{
    menu_async_invoke(_nw_ssid_do_timer_nfy, NULL, 0, TRUE);
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

    INT32                    i4_ret = MENUR_OK;
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;
    BOOL                     b_success = FALSE;
    UINT8                    ui1_timeout_count = 0;

    if (FALSE == pt_page_data->b_this_page_show)
    {
        c_timer_stop(pt_page_data->h_check_timer);
        c_timer_stop(pt_page_data->h_timer);

        /* stop animation */
        i4_ret = menu_page_animation_stop();
        MENU_LOG_ON_FAIL(i4_ret);

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

    DBG_LOG_PRINT(("\n\n\r %s, %s, %d, pt_page_data->b_finish=%d, pt_page_data ->ui1_animation_count=%d, b_success=%d",
                __FILE__,
                __FUNCTION__,
                __LINE__,
                (UINT32)pt_page_data->b_finish,
                (UINT32)pt_page_data ->ui1_animation_count,
                (UINT32)b_success));

    if (pt_page_data->b_finish)
    {
        i4_ret = _menu_page_nw_input_ssid_timer_finish(b_success);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if(pt_page_data ->ui1_animation_count > ui1_timeout_count)
    {
        DBG_LOG_PRINT(("\n\n\r %s, %s, %d, timeout.\n",
                    __FILE__,
                    __FUNCTION__,
                    __LINE__));

        pt_page_data->b_finish = TRUE;

        i4_ret = _menu_page_nw_input_ssid_timer_finish(FALSE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        menu_page_animation_start(1, FALSE);
        pt_page_data ->ui1_animation_count += 1;
    }

    return;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_test_connection
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

static BOOL _menu_nw_is_ssid_scan_success(VOID)
{
    INT8        ui1_idx = 0;
    BOOL        b_found   = FALSE;

    NET_802_11_ESS_LIST_T   t_essList;
    NET_802_11_ESS_INFO_T*  p_essInfo = NULL;
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    c_memset(&t_essList, 0 , sizeof(NET_802_11_ESS_LIST_T));
    a_nw_wlan_get_ess_list(&t_essList);

    if(t_essList.ui4_NumberOfItems == 0)
    {
        DBG_LOG_PRINT(("\n\n\r %s, %s, %d, ess list is empty.\n",
                    __FILE__,
                    __FUNCTION__,
                    __LINE__));
        return FALSE;
    }

    for (ui1_idx = 0; ui1_idx < (UINT8)t_essList.ui4_NumberOfItems; ui1_idx ++)
    {
        p_essInfo = &t_essList.p_EssInfo[ui1_idx];

        if(p_essInfo->t_Ssid.ui4_SsidLen == 0)
        {
            continue;
        }

        if(c_strncmp(p_essInfo->t_Ssid.ui1_aSsid, pt_page_data->s_input_buf, NET_802_11_MAX_LEN_SSID ) != 0)
        {
            continue;
        }

        b_found = TRUE;
    }

   return b_found;
}


static VOID _nw_check_do_timer_nfy(
    VOID*   pv_data,
    SIZE_T  z_data_size)
{
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    if (FALSE == pt_page_data->b_this_page_show)
    {
        c_timer_stop(pt_page_data->h_check_timer);
        return;
    }

    _check_scan_result();
}

static VOID _nw_check_timer_cb_fct (HANDLE_T  pt_tm_handle,
                                  VOID*      pv_tag)
{
    menu_async_invoke(_nw_check_do_timer_nfy, NULL, 0, TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _check_scan_result
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
static INT32 _check_scan_result(VOID)
{
    INT32       i4_ret = 0;
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    DBG_LOG_PRINT(("\n\n\r~~~~%s, %s, %d, ui1_g_ssid_scan_count = %d, check again...\n\n\r~~~~",
                   __FILE__,
                   __FUNCTION__,
                   __LINE__,
                   ui1_g_ssid_check_count));

    if (_menu_nw_is_ssid_scan_success())
    {
        _wifi_associate_special_ssid();
    }
    else
    {
        if (ui1_g_ssid_check_count >= 5)
        {
            DBG_LOG_PRINT(("\n\n\r~~~~%s, %s, %d, ui1_g_ssid_check_count = %d, check complete.\n\n\r~~~~",
                __FILE__,
                __FUNCTION__,
                __LINE__,
                ui1_g_ssid_check_count));

            c_timer_stop(pt_page_data->h_check_timer);

            pt_page_data ->b_finish = FALSE;
            a_nw_wlan_scan_with_ssid(pt_page_data->s_input_buf, c_strlen(pt_page_data->s_input_buf));
        }
        else
        {
            c_timer_stop(pt_page_data->h_check_timer);
            i4_ret = c_timer_start(pt_page_data->h_check_timer,
                            1000,
                            X_TIMER_FLAG_ONCE,
                            _nw_check_timer_cb_fct,
                            NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            ui1_g_ssid_check_count++;
        }
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _wifi_associate_special_ssid
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
static INT32 _wifi_associate_special_ssid(VOID)
{
    INT32       i4_ret;
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    UTF16_T     w2s_str[NW_SSID_MAX_LEN+1] = {0};
    UTF16_T     w2s_msg[128+1] = {0};
    UINT32      ui4_len;
    NET_802_11_ASSOCIATE_T* pt_associate = NULL;

    UINT8              ui1_idx = 0;
    NET_802_11_ESS_LIST_T t_essList;
    NET_802_11_ESS_INFO_T* p_essInfo = NULL;

    c_memset(w2s_str, 0, sizeof(UTF16_T)*(NW_SSID_MAX_LEN +1));

    if (pt_page_data->b_vkb_showed)
    {
        /* retrieve the new channel name. */
        i4_ret = a_vkb_do_cmd(pt_page_data->h_vkb,
                     VKB_CMD_GET_EB_CONTENT,
                     WGL_PACK (w2s_str),
                     WGL_PACK (NW_SSID_MAX_LEN));
        MENU_LOG_ON_FAIL(i4_ret);
        c_memset(pt_page_data->s_input_buf,0,sizeof(pt_page_data->s_input_buf));
        i4_ret = c_uc_w2s_to_ps(w2s_str, pt_page_data->s_input_buf, NW_SSID_MAX_LEN);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    ui4_len= c_strlen(pt_page_data->s_input_buf);

    if (ui4_len > 0 && ui4_len <= NET_802_11_MAX_LEN_SSID)
    {
        pt_page_data->b_finish = FALSE;
        pt_page_data->b_timer_result = FALSE;
        pt_page_data->b_connec_timer = TRUE;

        /* init the animation count as 0*/
        pt_page_data ->ui1_animation_count = 0;
        i4_ret = menu_page_animation_start(1, FALSE);
        MENU_LOG_ON_FAIL(i4_ret);

        c_timer_stop(pt_page_data->h_timer);
        i4_ret = c_timer_start(pt_page_data->h_timer,
                        200,
                        X_TIMER_FLAG_REPEAT,
                        _nw_ssid_timer_cb_fct,
                        NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        /* disable the menu timer */
        menu_timer_enable(FALSE);
        menu_timer_stop();

        i4_ret = menu_network_get_associate_data(&pt_associate);
        if(NULL == pt_associate)
        {
            DBG_ERROR((" %s, %s, %d, pt_associate=%d",
                        __FILE__,
                        __FUNCTION__,
                        __LINE__,
                        pt_associate));
            return MENUR_OK;
        }

        c_memset(&t_essList, 0, sizeof(t_essList));

        i4_ret = a_nw_wlan_get_ess_list(&t_essList);
        MENU_LOG_ON_FAIL(i4_ret);

        for (ui1_idx = 0; ui1_idx < (UINT8)t_essList.ui4_NumberOfItems; ui1_idx ++)
        {
            DBG_LOG_PRINT(("%s, %s, %d, idx=%d, i2_Level=%d,e_AuthMode = %d SsidLen=%d, aSsid=%s. ----,connected = %d\n",
                       __FILE__,
                       __FUNCTION__,
                       __LINE__,
                       ui1_idx,
                       t_essList.p_EssInfo[ui1_idx].i2_Level,
                       t_essList.p_EssInfo[ui1_idx].e_AuthMode,
                       t_essList.p_EssInfo[ui1_idx].t_Ssid.ui4_SsidLen,
                       t_essList.p_EssInfo[ui1_idx].t_Ssid.ui1_aSsid,
                       t_essList.p_EssInfo[ui1_idx].i4_isConnected));
        }

        for (ui1_idx = 0;ui1_idx<(UINT8)t_essList.ui4_NumberOfItems; ui1_idx ++)
        {
            p_essInfo = &t_essList.p_EssInfo[ui1_idx];

            if(p_essInfo->t_Ssid.ui4_SsidLen == 0)
            {
                continue;
            }

            if(c_strncmp(p_essInfo->t_Ssid.ui1_aSsid, pt_page_data->s_input_buf,NET_802_11_MAX_LEN_SSID ) != 0)
            {
                continue;
            }

            c_memset(pt_associate,0, sizeof(NET_802_11_ASSOCIATE_T));

            pt_associate->t_Ssid      = p_essInfo->t_Ssid;
            c_memcpy(pt_associate->t_Bssid,p_essInfo->t_Bssid, sizeof(NET_802_11_BSSID_T));

            pt_associate->e_AuthMode  = p_essInfo->e_AuthMode;
            pt_associate->e_AuthCipher= p_essInfo->e_AuthCipher;

            pt_associate->t_Key.b_IsAscii = FALSE;

            if (FALSE == nw_custom_is_lock_ap(pt_associate->e_AuthMode,pt_associate->e_AuthCipher))
            {
                /*do action*/
                pt_page_data->b_finish = FALSE;
                pt_page_data->b_timer_result = FALSE;
                pt_page_data->b_connec_timer = TRUE;

                pt_page_data->ui1_animation_count = 0;

                DBG_LOG_PRINT(("\n\n\r~~~~%s, %s, %d, pt_page_data->b_finish=%d, is unencrypted wifi AP, to disassociate prev AP.~~~~",
                            __FILE__,
                            __FUNCTION__,
                            __LINE__,
                            (UINT32)pt_page_data->b_finish));

                i4_ret = a_nw_custom_wlan_disassociate();
                if (i4_ret != NWR_OK)
                {
                    DBG_LOG_PRINT(("\n\n\r %s, %s, %d, wlan disassociate fail, i4_ret=%d",
                                __FILE__,
                                __FUNCTION__,
                                __LINE__,
                                i4_ret));
                    pt_page_data->b_finish = TRUE;
                }

                i4_ret = a_nw_wlan_associate(pt_associate);
                if (i4_ret != NWR_OK)
                {
                    DBG_LOG_PRINT(("\n\n\r %s, %s, %d, wlan associate fail, i4_ret=%d",
                                __FILE__,
                                __FUNCTION__,
                                __LINE__,
                                i4_ret));
                    pt_page_data->b_finish = TRUE;
                }
            }
            else
            {
                DBG_LOG_PRINT(("\n\n\r~~~~%s, %s, %d, is encrypt wifi AP, enter into pwd page to input pwd.~~~~",
                            __FILE__,
                            __FUNCTION__,
                            __LINE__));

                pt_page_data->b_connec_timer = FALSE;
                pt_page_data->b_finish = TRUE;
                pt_page_data->b_timer_result = TRUE;
            }

            return MENUR_OK;
        }

        DBG_LOG_PRINT(("\n\n\r~~~~%s, %s, %d, input ssid = %s, start to scan it.\n\n\r~~~~",
                       __FILE__,
                       __FUNCTION__,
                       __LINE__,
                       pt_page_data->s_input_buf));

        pt_page_data->b_finish = FALSE;
        pt_page_data->b_timer_result = FALSE;
        pt_page_data->b_connec_timer = FALSE;
        i4_ret = a_nw_wlan_scan_with_ssid(pt_page_data->s_input_buf, ui4_len);
        if(i4_ret != NWR_OK)
        {
            DBG_LOG_PRINT(("\n\n\r %s, %s, %d, a_nw_wlan_scan_with_ssid fail, i4_ret=%d",
                        __FILE__,
                        __FUNCTION__,
                        __LINE__,
                        i4_ret));
            pt_page_data->b_finish = TRUE;
        }
    }
    else
    {
        pt_page_data->b_finish = TRUE;

        DBG_LOG_PRINT(("\n\n\r~~~~%s, %s, %d, ui4_len = %d, input ssid is incorrect.\n\n\r~~~~",
                   __FILE__,
                   __FUNCTION__,
                   __LINE__,
                   ui4_len));

        c_memset(w2s_str, 0, sizeof(UTF16_T)*(NW_SSID_MAX_LEN +1));
        c_memset(w2s_msg, 0, sizeof(UTF16_T)*(128+1));

        c_uc_ps_to_w2s(pt_page_data->s_input_buf, w2s_str, NW_SSID_MAX_LEN);

        c_uc_w2s_strcpy(w2s_msg, MENU_TEXT(MLM_MENU_KEY_NW_CON_FAIL));
        c_uc_w2s_strcat(w2s_msg, w2s_str);

        i4_ret = menu_network_show_confirm_dialog(w2s_msg,
                                                  MENU_TEXT(MLM_MENU_KEY_NW_WIFI_TRY_AGAIN),
                                                  _nw_confirm_dialog_cb_fct,
                                                  TRUE);
        MENU_LOG_ON_FAIL(i4_ret);
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
            UTF16_T             w2s_str[NW_SSID_MAX_LEN+1] = {0};
            INT32               i4_ret = MENUR_OK;

            if(t_nw_input_ssid_page_data.b_vkb_showed)
            {
                /* retrieve the new channel name. */
                i4_ret = a_vkb_do_cmd(t_nw_input_ssid_page_data.h_vkb,
                             VKB_CMD_GET_TEXT,
                             WGL_PACK (w2s_str),
                             WGL_PACK (NW_SSID_MAX_LEN));
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret = c_uc_w2s_to_ps(w2s_str, t_nw_input_ssid_page_data.s_input_buf,NW_SSID_MAX_LEN);
                MENU_LOG_ON_FAIL(i4_ret);

                //i4_ret = _update_ui();
                //MENU_LOG_ON_FAIL(i4_ret);
            }
            //else
            {
                menu_netowrk_nav_back();
            }

            menu_pm_repaint();
            return MENUR_OK;
        }

        case BTN_CURSOR_DOWN:
            a_vkb_set_focus_ex(t_nw_input_ssid_page_data.h_vkb);
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
        if(t_nw_input_ssid_page_data.b_finish == FALSE)
        {
            return WGLR_OK;
        }

        switch ((UINT32)pv_param1)
        {
        case BTN_SELECT :

            DBG_INFO(("~~~~%s, %s, %d, start to scan hidden ap.\n\n\r~~~~",
                       __FILE__,
                       __FUNCTION__,
                       __LINE__));
            ui1_g_ssid_scan_count = 0;
            _wifi_associate_special_ssid();
            return WGLR_OK;

        case BTN_CURSOR_UP :
            if(t_nw_input_ssid_page_data.b_vkb_showed)
            {
                c_wgl_set_focus(t_nw_input_ssid_page_data.h_vkb_last_focus, WGL_SYNC_AUTO_REPAINT);
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
                c_wgl_repaint(t_nw_input_ssid_page_data.h_cnt_frm, NULL, TRUE);
            }
            return WGLR_OK;

        case BTN_CURSOR_DOWN :
            if(t_nw_input_ssid_page_data.b_vkb_showed)
            {
                menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
                // menu_pm_repaint();
            }
            else
            {
                c_wgl_set_focus(t_nw_input_ssid_page_data.h_action_show_vkb, WGL_SYNC_AUTO_REPAINT);
            }
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
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_CON_SSID));

    #ifdef APP_TTS_SUPPORT
        a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_NW_CON), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_NW_CON)));
    #endif
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        //menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));

    #ifdef APP_TTS_SUPPORT
        a_app_tts_stop(APP_TTS_STOP_FORCE);
    #endif
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _action_show_vkb_proc_fct
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
static INT32 _action_show_vkb_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)pv_param1)
        {
        case BTN_SELECT :
            _show_wifi_ssid_vkb(TRUE);
            return WGLR_OK;
        case BTN_CURSOR_UP :
            c_wgl_set_focus(t_nw_input_ssid_page_data.h_action_connect, WGL_SYNC_AUTO_REPAINT);
            return WGLR_OK;

        case BTN_CURSOR_DOWN :
            menu_help_tip_keytip_set_focus(h_widget, 0, FALSE);
            menu_pm_repaint();
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
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_SHOW_KB));
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _wifi_ssid_update_connect_btn
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
static INT32 _wifi_ssid_update_connect_btn(BOOL b_enable, BOOL b_repaint)
{
    INT32               i4_ret       = WDKR_OK;
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    i4_ret = c_wgl_enable(pt_page_data->h_action_connect, b_enable);
    WDK_CHK_FAIL(i4_ret);

    if (b_repaint)
    {
        i4_ret = c_wgl_repaint(pt_page_data->h_action_connect, NULL, TRUE);
        WDK_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wifi_ssid_vbk_data_change_nfy
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
static INT32 _wifi_ssid_vbk_data_change_nfy (
    VOID*    pv_tag,
    UINT32   ui4_msg,
    VOID*    pv_param1,
    VOID*    pv_param2)
{
    INT32               i4_ret       = WDKR_OK;
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    if (ui4_msg == VKB_MSG_DLG_KEY_INPUT)
    {
        UINT32*  pui4_key_code = (UINT32*) pv_param1;
        BOOL     b_is_top_bottom = FALSE;
        UTF16_T             w2s_str[NW_SSID_MAX_LEN+1] = {0};
        VKB_CONTROL_LOGIC_T *pt_vkb_ctrl = NULL;
        SIZE_T              z_len = 0;

        switch(*pui4_key_code)
        {
            case BTN_EXIT:
            case BTN_PREV_PRG:
            case BTN_RETURN:
            {
                if (pt_page_data->b_vkb_showed)
                {
                    /* retrieve the new channel name. */
                    i4_ret = a_vkb_do_cmd(pt_page_data->h_vkb,
                                 VKB_CMD_GET_TEXT,
                                 WGL_PACK (w2s_str),
                                 WGL_PACK (NW_SSID_MAX_LEN));
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = c_uc_w2s_to_ps(w2s_str, pt_page_data->s_input_buf, NW_SSID_MAX_LEN);
                    MENU_LOG_ON_FAIL(i4_ret);
                }

                menu_netowrk_nav_back();
                menu_pm_repaint();
                break;
            }
            case BTN_KB_BACKSPACE:
            case BTN_CURSOR_LEFT:
            {
                c_wgl_do_cmd(pt_page_data->h_vkb,
                             WGL_CMD_GL_GET_ATTACH_DATA,
                             (VOID *)&pt_vkb_ctrl,
                             NULL);
                if (pt_vkb_ctrl
                    && pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_EDIT_BOX)
                {
                    c_memset(w2s_str, 0, sizeof(w2s_str));
                    a_vkb_do_cmd(pt_page_data->h_vkb,
                                 VKB_CMD_GET_EB_CONTENT,
                                 (VOID *)w2s_str,
                                 (VOID*)NW_SSID_MAX_LEN);

                    z_len = c_uc_w2s_strlen(w2s_str);

                    if (z_len <= 1)
                    {
                        b_connect_btn_enable = FALSE;
                    }
                    else
                    {
                        b_connect_btn_enable = TRUE;
                    }

                    _wifi_ssid_update_connect_btn(b_connect_btn_enable, TRUE);
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
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }
                if(TRUE == b_is_top_bottom)
                {
                    if (b_connect_btn_enable)
                    {
                        c_wgl_set_focus(pt_page_data->h_action_connect, WGL_SYNC_AUTO_REPAINT);
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NW_HELP_CON_SSID));
                        i4_ret = WDK_NO_ACTION;
                    }
                    else
                    {
                        menu_help_tip_keytip_set_focus(pt_page_data->h_vkb_last_focus, 0, FALSE);
                        i4_ret = WDK_NO_ACTION;
                    }
                }
            }
                break;
            case BTN_SELECT:
            {
                i4_ret = a_vkb_current_is_top_row(pt_page_data->h_vkb,&b_is_top_bottom);
                if(i4_ret != WDKR_OK)
                {
                    return WDKR_OK;
                }

                if (TRUE == b_is_top_bottom && pt_page_data->b_vkb_showed)
                {
                    if (b_connect_btn_enable)
                    {
                        ui1_g_ssid_scan_count = 0;
                        _wifi_associate_special_ssid();
                    }
                    i4_ret = WDK_NO_ACTION;
                }
                else
                {
                    c_wgl_do_cmd(pt_page_data->h_vkb,
                                 WGL_CMD_GL_GET_ATTACH_DATA,
                                 (VOID *)&pt_vkb_ctrl,
                                 NULL);

                    if (pt_vkb_ctrl)
                    {
                        c_memset(w2s_str, 0, sizeof(w2s_str));
                        a_vkb_do_cmd(pt_page_data->h_vkb,
                                     VKB_CMD_GET_TEXT,
                                     (VOID *) w2s_str,
                                     (VOID *) MAX_TV_NAME_LEN);

                        z_len = c_uc_w2s_strlen(w2s_str);

                        b_connect_btn_enable = (z_len > 0)? TRUE : FALSE;

                        if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_CTRL_KEY)
                        {
                            if (pt_vkb_ctrl->t_focus_item.t_ctrl_key.ui1_focus_idx == VKB_KEYPAD_CTRL_DEL_KEY_IDX)
                            {
                                if (b_connect_btn_enable)
                                {
                                    b_connect_btn_enable = (z_len - 1 > 0)? TRUE : FALSE;
                                }
                            }
                            else if (VKB_KEYPAD_CTRL_SPACE_KEY_IDX == pt_vkb_ctrl->t_focus_item.t_ctrl_key.ui1_focus_idx)
                            {
                                b_connect_btn_enable = TRUE;
                            }
                        }
                        else if (pt_vkb_ctrl->t_focus_item.e_type == VKB_FOCUS_WIDGET_KEYPAD_NORMAL_KEY)
                        {
                            UINT8 ui1_key_idx = 0;
                            UINT8 ui1_elem_idx = 0;

                            ui1_key_idx = pt_vkb_ctrl->ui1_cur_latin_key_idx;
                            ui1_elem_idx = pt_vkb_ctrl->t_focus_item.t_normal_key.ui1_focus_idx_col
                                            - pt_vkb_ctrl->at_keypad_latin_key[ui1_key_idx].ui1_col_offset;

                            if (TRUE == pt_vkb_ctrl->b_latin_lock
                                && FALSE == pt_vkb_ctrl->b_latin_expand)
                            {
                                //do nothing
                            }
                            else if (TRUE == pt_vkb_ctrl->b_latin_lock
                                    && TRUE == pt_vkb_ctrl->b_latin_expand
                                    && ui1_elem_idx >= pt_vkb_ctrl->at_keypad_latin_key[ui1_key_idx].ui1_elem_num)
                            {
                                //do nothing
                            }
                            else
                            {
                                b_connect_btn_enable = TRUE;
                            }
                        }
                        _wifi_ssid_update_connect_btn(b_connect_btn_enable, TRUE);
                    }
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
 * Name: _wifi_ssid_vbk_frm_proc_fct
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
static INT32 _wifi_ssid_vbk_frm_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       pv_param1,
    VOID*       pv_param2)
{
    UTF16_T     w2s_str[NW_SSID_MAX_LEN+1] = {0};
    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;
    //HANDLE_T    h_eb = NULL_HANDLE;

    if (WGL_MSG_NOTIFY == ui4_msg)
    {
        //h_eb = (HANDLE_T)pv_param1;
        WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)pv_param2;

        if (WGL_NC_EB_CHANGED == pt_nfy_data->ui4_nc_code)
        {
            c_memset(w2s_str, 0, sizeof(w2s_str));

            a_vkb_do_cmd(pt_page_data->h_vkb,
                         VKB_CMD_GET_EB_CONTENT,
                         (VOID *)w2s_str,
                         (VOID*)(NW_SSID_MAX_LEN+1));

            w2s_str[NW_SSID_MAX_LEN] = 0;

            if (c_uc_w2s_strlen(w2s_str) == 0)
            {
                b_connect_btn_enable = FALSE;
            }
            else
            {
                b_connect_btn_enable = TRUE;
            }

            _wifi_ssid_update_connect_btn(b_connect_btn_enable, TRUE);

            return WGLR_OK;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
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
                     0,
                     MENU_ITEM_V_WIDE,
                     MENU_ITEM_V_HEIGHT*3);

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
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_menu_color_white;
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
 * Name: _wifi_ssid_vkb_create
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
static INT32 _wifi_ssid_vkb_create(VOID)
{
    INT32       i4_ret;

    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;
    VKB_INIT_T           t_init_data;

    /* Create Virtual key board */
    t_init_data.h_parent            = pt_page_data->h_cnt_frm;
    t_init_data.ui4_style_mask      = VKB_STYLE_MASK_WIFI_SSID | VKB_STYLE_MASK_NO_COM_KEY | VKB_STYLE_MASK_WITH_EB_CLEAR;
    t_init_data.t_gui_rc.i4_left    = FRAME_LEFT_RIGHT_INTV;
    t_init_data.t_gui_rc.i4_top     = (GRID_H*3 - 15*4/3 - MENU_ITEM_V_HEIGHT);
    t_init_data.pf_data_change_fct  = _wifi_ssid_vbk_data_change_nfy;
    t_init_data.pv_tag              = NULL;

    i4_ret = a_vkb_create(&t_init_data,&pt_page_data->h_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_widget_proc(pt_page_data->h_vkb,_wifi_ssid_vbk_frm_proc_fct);
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

    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    c_memset(pt_page_data, 0, sizeof(NW_INP_SSID_PAGE_DATA_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &pt_page_data->h_cnt_frm);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)4,
                                _action_connect_proc_fct,
                                &pt_page_data->h_action_connect);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)5,
                                _action_show_vkb_proc_fct,
                                &pt_page_data->h_action_show_vkb);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _txt_suggest_create(pt_page_data->h_cnt_frm,
                                &pt_page_data->h_txt_suggest);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id, _widgets_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _wifi_ssid_vkb_create();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&(pt_page_data->h_timer));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&(pt_page_data->h_check_timer));
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_finish = TRUE;

    /* set visibility */
    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

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

    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    i4_ret = a_nw_register(_nw_notify_callback, (VOID*)pt_page_data, &pt_page_data->ui4_nw_nfy_id );
    MENU_LOG_ON_FAIL(i4_ret);

    /* shit. */
    pt_page_data->b_finish = TRUE;

    /*update the network info data*/
    pt_page_data->b_this_page_show = TRUE;
    if(menu_network_is_page_back() == FALSE)
    {
        c_memset(pt_page_data->s_input_buf, 0, sizeof(CHAR)*(NW_SSID_MAX_LEN+1));
    }

    i4_ret = _update_ui();
    MENU_LOG_ON_FAIL(i4_ret);
    c_wgl_set_visibility(pt_page_data->h_cnt_frm,WGL_SW_RECURSIVE);
    c_wgl_repaint(pt_page_data->h_cnt_frm,NULL,TRUE);
    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_NET_INP_ENTER_ACCESS_POINT);
    menu_help_tip_keytip_show(FALSE);

    if(menu_timer_is_enabled() == TRUE)
    {
        /* disable the menu timer */
        menu_timer_enable(FALSE);
        menu_timer_stop();
    }

#ifdef APP_TTS_SUPPORT
    a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_NW_INP_AP_TIT), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_NW_INP_AP_TIT)));
#endif

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32       i4_ret;

    NW_INP_SSID_PAGE_DATA_T* pt_page_data = &t_nw_input_ssid_page_data;

    if(pt_page_data->b_this_page_show == FALSE)
    {
        return MENUR_OK;
    }

    i4_ret = a_nw_unregister(pt_page_data->ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_help_tip_keytip_show(TRUE);
    menu_network_hide_confirm_dialog(FALSE);

    i4_ret = menu_network_last_shadow_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_this_page_show = FALSE;
    pt_page_data->b_finish = TRUE;

    a_vkb_set_visibility(pt_page_data->h_vkb, FALSE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
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
extern INT32 menu_common_page_nw_input_ssid(VOID)
{
    t_g_menu_common_page_nw_input_ssid.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_nw_input_ssid.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_nw_input_ssid.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_nw_input_ssid.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_nw_input_ssid.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_nw_input_ssid.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_nw_input_ssid.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

#endif /* APP_NETWORK_WIFI_SUPPORT */
