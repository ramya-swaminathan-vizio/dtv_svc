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
 * $RCSfile: menu_page_test_speical_param,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
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
#include "c_tsl.h"
#include "c_wgl_sets.h"
#include "c_version.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_util2.h"
#include "app_util/a_cfg.h"
#include "app_util/a_network.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/network/network_custom.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_network_phase1/menu_network_com_ui.h"
#include "menu2/menu_network_phase1/menu_network.h"
#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest_event.h"
#endif

#include "u_drv_cust.h"
#include "c_rm.h"

#define NW_FREQ_2_4             ((UINT8)0)
#define NW_FREQ_5_0             ((UINT8)1)

#define NW_HIDE_BTN_IPERF       ((UINT8)0)
#define NW_HIDE_BTN_RSSI        ((UINT8)1)
#define MENU_XX_SIZE            (17)

#define NW_ITEM_V_HEIGHT                (32*4/3)

#ifndef MAC2STR
#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"
#endif

#ifndef IEEE80211_CAP_IBSS
#define IEEE80211_CAP_IBSS  0x0002
#endif

typedef struct _PAGE_NW_HIDE_T
{
    HANDLE_T    h_cnt_frm;
    HANDLE_T    h_iperf;
    HANDLE_T    h_rssi;
    HANDLE_T    h_vlog;
    HANDLE_T    h_memc;
    HANDLE_T    h_ota_test;
    HANDLE_T    h_provisions_btn;
    HANDLE_T    h_xx_list_box;
    HANDLE_T    h_force_log_upload;
    HANDLE_T    h_signal_lvl_dlg;
    HANDLE_T    h_signal_lvl_timer;
    HANDLE_T    h_oled_off_rs;
    HANDLE_T    h_oled_jb;
    HANDLE_T    h_audio_dbginfo;
    HANDLE_T    h_hdmi_dbginfo;
    UINT16      ui2_xx_idx;
    BOOL        b_is_dlg_show;
}PAGE_NW_HIDE_T;

/*data declaration*/
MENU_PAGE_FCT_TBL_T     t_g_menu_common_test_special_param;
static PAGE_NW_HIDE_T   t_page_nw_hide;

#ifdef APP_WIFI_SIGNAL_LVL_SUPPORT
static UINT8       i1_g_freq = NW_FREQ_2_4;
#endif

static UINT8 ui1_tts_idx_last = 0;

enum
{
     LOG_LEVEL_ENABLE_ALL    = 0xaf,  //enable all log
     LOG_LEVEL_DRIVER_OFF    = 0x5f   //disable driver log after power on
};
static INT32 _menu_test_xx_list_box_show(VOID);

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
    PAGE_NW_HIDE_T*     pt_this = &t_page_nw_hide;

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
            return MENUR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
            MENU_LOG_ON_FAIL (menu_nav_back());
            return MENUR_OK ;

        case BTN_CURSOR_RIGHT :
        case BTN_CURSOR_DOWN:
            MENU_LOG_ON_FAIL (c_wgl_set_focus (pt_this->h_iperf, WGL_SYNC_AUTO_REPAINT));
            return MENUR_OK;

        case BTN_CURSOR_UP:
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            break;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
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
            MENU_LOG_ON_FAIL(menu_nav_go_home_menu());
            return MENUR_OK ;

        case BTN_RETURN:
            MENU_LOG_ON_FAIL(menu_nav_back());
            return MENUR_OK ;

        case BTN_CURSOR_UP :
            break ;

        case BTN_CURSOR_DOWN :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

#ifdef APP_IPERF_SUPPORT

/*----------------------------------------------------------------------------
 * Name: _start_iperf
 *
 * Description: start iPerf server
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _start_iperf (VOID)
{
    INT32       i4_ret = 0;
    CHAR        s_cmd_buffer[128] = {0};
    UINT16      ui2_value = 0;

    ui2_value = menu_network_iperf_dialog_get_data();
    if (ui2_value == 0)
    {
        return MENUR_OK;
    }

    c_sprintf(s_cmd_buffer, "/basic/iperf -s -i 1 -p %d &", ui2_value);

    i4_ret = system(s_cmd_buffer);
    if (i4_ret != 0)
    {
        DBG_ERROR(("<MENU> start iPerf error:%s:%d:%d\r\n",
                    __FILE__, __LINE__, i4_ret));
    }

    DBG_LOG_PRINT(("[NW] start iPerf cmd: %s.\n", s_cmd_buffer));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _iperf_dialog_btn_cb_fct
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
static VOID _iperf_dialog_btn_cb_fct(UINT32 ui4_keycode)
{
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;
    INT32               i4_ret = MENUR_OK;

    if (BTN_SELECT == ui4_keycode)
    {
        _start_iperf ();
    }

    menu_network_simple_dialog_hide(TRUE);

    i4_ret = c_wgl_set_focus(pt_page_data->h_iperf, WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);
}
#endif

#ifdef APP_WIFI_SIGNAL_LVL_SUPPORT
/*----------------------------------------------------------------------------
 * Name: _menu_show_signal_lvl_dlg_hide
 *
 * Description:
 *      Hide the signal level popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_show_signal_lvl_dlg_hide(VOID)
{
    INT32               i4_ret  = MENUR_OK;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;

    /* stop repeat timer */
    i4_ret = c_timer_stop(pt_page_data->h_signal_lvl_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_hide(pt_page_data->h_signal_lvl_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_float(pt_page_data->h_signal_lvl_dlg, FALSE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_is_dlg_show  = FALSE;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_show_signal_lvl_dlg_update
 *
 * Description:
 *      Update the signal level popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_show_signal_lvl_dlg_update(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    CHAR                        s_buffer[128] = {0};
    UTF16_T                     w2s_tmp_str[128];
    UTF16_T                     w2s_str[128];
    NET_802_11_WIFI_RSSI_T      t_rssi;
    PAGE_NW_HIDE_T*             pt_page_data = &t_page_nw_hide;

    if (FALSE == pt_page_data->b_is_dlg_show)
    {
        return MENUR_OK;
    }

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_buffer,0,sizeof(CHAR)*128);

    c_memset (&t_rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));
    i4_ret = a_nw_wlan_get_rssi(&t_rssi);
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("\n\n------------- Current RSSI info: -------------\n"));
    DBG_LOG_PRINT(("i4Rssi_a:\t\t %d\n", t_rssi.i4Rssi_a));
    DBG_LOG_PRINT(("i4Rssi_b:\t\t %d\n", t_rssi.i4Rssi_b));
    DBG_LOG_PRINT(("i4Rssi_c:\t\t %d\n", t_rssi.i4Rssi_c));

    /* i2_Freq == 0, check i2_Channel */
    if (i1_g_freq == NW_FREQ_2_4)
    {
        /* 2.4GHz */
        if (t_rssi.i4Rssi_b > -99)
        {
            c_sprintf(s_buffer, "RSSI Power Levels \n\n 2.4-1: %d dBm\n 2.4-2: %d dBm\n Combo: %d dBm",
                t_rssi.i4Rssi_a,
                t_rssi.i4Rssi_b,
                (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
        }
        else
        {
            c_sprintf(s_buffer, "RSSI Power Levels \n\n 2.4-1: %d dBm", t_rssi.i4Rssi_a);
        }
    }
    else
    {
        /* 5.0GHz */
        if (t_rssi.i4Rssi_b > -99)
        {
            c_sprintf(s_buffer, "RSSI Power Levels \n\n 5.0-1: %d dBm\n 5.0-2: %d dBm\n Combo: %d dBm",
                t_rssi.i4Rssi_a,
                t_rssi.i4Rssi_b,
                (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
        }
        else
        {
            c_sprintf(s_buffer, "RSSI Power Levels \n\n 5.0-1: %d dBm", t_rssi.i4Rssi_a);
        }
    }
    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    i4_ret = a_ui_simple_dialog_set_text(pt_page_data->h_signal_lvl_dlg,
                                         w2s_tmp_str);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_repaint(pt_page_data->h_signal_lvl_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static VOID _do_update_wlan_signal_level(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    _menu_show_signal_lvl_dlg_update();
 }

static VOID _timer_wlan_signal_nfy_fct(HANDLE_T h_timer,VOID* pv_tag)
{
    menu_async_invoke(_do_update_wlan_signal_level, NULL, 0, FALSE);
}

/*----------------------------------------------------------------------------
 * Name: _menu_show_signal_lvl_dlg_show
 *
 * Description:
 *      Show the signal level popup dialog under menu app.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
static INT32 _menu_show_signal_lvl_dlg_show(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    CHAR                        s_buffer[128] = {0};
    UTF16_T                     w2s_tmp_str[128];
    UTF16_T                     w2s_str[128];
    NET_802_11_BSS_INFO_T       t_CurrBss;
    NET_802_11_WIFI_RSSI_T      t_rssi;
    PAGE_NW_HIDE_T*             pt_page_data = &t_page_nw_hide;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_buffer,0,sizeof(CHAR)*128);

    c_memset (&t_rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));
    i4_ret = a_nw_wlan_get_rssi(&t_rssi);
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("\n\n------------- Current RSSI info: -------------\n"));
    DBG_LOG_PRINT(("i4Rssi_a:\t\t %d\n", t_rssi.i4Rssi_a));
    DBG_LOG_PRINT(("i4Rssi_b:\t\t %d\n", t_rssi.i4Rssi_b));
    DBG_LOG_PRINT(("i4Rssi_c:\t\t %d\n", t_rssi.i4Rssi_c));

    c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("\n\n------------- Current BSS info: -------------\n"));
    DBG_LOG_PRINT(("ssid:\t\t %s\n", t_CurrBss.t_Ssid.ui1_aSsid));
    DBG_LOG_PRINT(("bssid:\t "MACSTR"\n", MAC2STR(t_CurrBss.t_Bssid)));
    DBG_LOG_PRINT(("mode:\t\t %s\n", (t_CurrBss.u2_Caps & IEEE80211_CAP_IBSS) ? "IBSS" : "Infrastructure"));
    DBG_LOG_PRINT(("freq:\t\t %dKHz\n", t_CurrBss.i2_Freq));
    DBG_LOG_PRINT(("channel:\t %d\n", t_CurrBss.i2_Channel));
    DBG_LOG_PRINT(("strength:\t %d(normalized)\n", t_CurrBss.i2_Level));
    DBG_LOG_PRINT(("noise:\t %d\n", t_CurrBss.i2_Noise));
    DBG_LOG_PRINT(("quality:\t %d\n", t_CurrBss.i2_Quality));
    DBG_LOG_PRINT(("max rate:\t %dMHz\n", (INT16)(t_CurrBss.i4_MaxRate/1000)));
    DBG_LOG_PRINT(("auth mode:\t %d\n", (INT16)t_CurrBss.e_AuthMode));
    DBG_LOG_PRINT(("auth cipher:\t %d\n", (INT16)t_CurrBss.e_AuthCipher));
    DBG_LOG_PRINT(("wps support:\t %d\n", t_CurrBss.is_wps_support));

    /* i2_Freq == 0, check i2_Channel */
    if (t_CurrBss.i2_Channel >= 1 && t_CurrBss.i2_Channel <= 14)
    {
        /* 2.4GHz */
        i1_g_freq = NW_FREQ_2_4;

        if (t_rssi.i4Rssi_b > -99)
        {
            c_sprintf(s_buffer, "RSSI Power Levels \n\n 2.4-1: %d dBm\n 2.4-2: %d dBm\n Combo: %d dBm",
                t_rssi.i4Rssi_a,
                t_rssi.i4Rssi_b,
                (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
        }
        else
        {
            c_sprintf(s_buffer, "RSSI Power Levels \n\n 2.4-1: %d dBm", t_rssi.i4Rssi_a);
        }
    }
    else
    {
        /* 5.0GHz */
        i1_g_freq = NW_FREQ_5_0;

        if (t_rssi.i4Rssi_b > -99)
        {
            c_sprintf(s_buffer, "RSSI Power Levels \n\n 5.0-1: %d dBm\n 5.0-2: %d dBm\n Combo: %d dBm",
                t_rssi.i4Rssi_a,
                t_rssi.i4Rssi_b,
                (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
        }
        else
        {
            c_sprintf(s_buffer, "RSSI Power Levels \n\n 5.0-1: %d dBm", t_rssi.i4Rssi_a);
        }
    }

    c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));

    i4_ret = a_ui_simple_dialog_set_text(pt_page_data->h_signal_lvl_dlg,
                                         w2s_tmp_str);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_show(pt_page_data->h_signal_lvl_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_float(pt_page_data->h_signal_lvl_dlg, TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_focus(pt_page_data->h_signal_lvl_dlg, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_repaint(pt_page_data->h_signal_lvl_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_is_dlg_show = TRUE;

    /* start repeat timer */
    i4_ret = c_timer_start(pt_page_data->h_signal_lvl_timer,
                      1000,
                      X_TIMER_FLAG_REPEAT,
                      _timer_wlan_signal_nfy_fct,
                      NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _menu_show_signal_lvl_dlg_yes_btn_cb
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
static VOID _menu_show_signal_lvl_dlg_yes_btn_cb()
{
    INT32                       i4_ret  = MENUR_OK;
    PAGE_NW_HIDE_T*             pt_page_data = &t_page_nw_hide;

    i4_ret = _menu_show_signal_lvl_dlg_hide();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_page_data->h_rssi, WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: _menu_show_signal_lvl_dlg_msg_proc
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
static INT32 _menu_show_signal_lvl_dlg_msg_proc (HANDLE_T            h_widget,
                                                 UINT32              ui4_msg,
                                                 VOID*               pv_param1,
                                                 VOID*               pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg &&
        (BTN_SELECT != (UINT32)pv_param1 &&
         BTN_CURSOR_RIGHT != (UINT32)pv_param1 &&
         BTN_CURSOR_LEFT != (UINT32)pv_param1))
    {
        _menu_show_signal_lvl_dlg_yes_btn_cb();
        return MENUR_OK;
    }

    return a_ui_simple_dialog_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _menu_show_signal_lvl_dlg_create
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
static INT32 _menu_show_signal_lvl_dlg_create(VOID)
{
    INT32                       i4_ret  = MENUR_OK;
    PAGE_NW_HIDE_T*             pt_page_data = &t_page_nw_hide;
    UI_SIMPLE_DIALOG_INIT_T     t_simple_dialog_init;
    HANDLE_T                    h_parent = NULL_HANDLE;

    i4_ret = menu_pm_get_root_frm(&h_parent);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = h_parent;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _menu_show_signal_lvl_dlg_yes_btn_cb;
    t_simple_dialog_init.pf_wdgt_proc                   = _menu_show_signal_lvl_dlg_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = NULL;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;

    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                       &pt_page_data->h_signal_lvl_dlg);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_text(pt_page_data->h_signal_lvl_dlg,
                                         MENU_TEXT(MLM_MENU_KEY_EMPTY));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_page_data->h_signal_lvl_dlg, MENU_TEXT(MLM_MENU_KEY_OK));
    MENU_LOG_ON_FAIL(i4_ret);

    pt_page_data->b_is_dlg_show   = FALSE;

    return MENUR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _action_items_proc_fct
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
static INT32 _action_items_proc_fct(
    HANDLE_T    h_widget,
    UINT32      ui4_msg,
    VOID*       param1,
    VOID*       param2)
{
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
        return WGLR_OK;
    }

    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
    {
        UINT32 ui4_keycode = (UINT32)param1;

        if (BTN_CURSOR_UP == ui4_keycode)
        {
            if (pt_page_data->h_iperf == h_widget)
            {
                MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            }
            else if (pt_page_data->h_rssi == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_iperf, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_provisions_btn== h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_vlog, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_force_log_upload == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_provisions_btn, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_audio_dbginfo == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_force_log_upload, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_hdmi_dbginfo == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_audio_dbginfo, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_oled_off_rs == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_hdmi_dbginfo, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_oled_jb == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_oled_off_rs, WGL_SYNC_AUTO_REPAINT);
            }
            else
            {
                /* do nothing */
            }

            return MENUR_OK;
        }
        else if (BTN_CURSOR_DOWN == ui4_keycode)
        {
            if (pt_page_data->h_iperf == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_rssi, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_rssi == h_widget)
            {
                if (menu_common_get_chipset() == CHIPSET_5695)
                {
                    c_wgl_set_focus (pt_page_data->h_memc, WGL_SYNC_AUTO_REPAINT);
                }
                else
                {
                    c_wgl_set_focus (pt_page_data->h_ota_test, WGL_SYNC_AUTO_REPAINT);
                }
            }
            else if (pt_page_data->h_memc == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_ota_test, WGL_SYNC_AUTO_REPAINT);
            }
            else if(pt_page_data->h_vlog == h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_provisions_btn, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_provisions_btn== h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_force_log_upload, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_force_log_upload== h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_audio_dbginfo, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_audio_dbginfo== h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_hdmi_dbginfo, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_hdmi_dbginfo == h_widget && NULL_HANDLE != pt_page_data->h_oled_off_rs)
            {
                c_wgl_set_focus (pt_page_data->h_oled_off_rs, WGL_SYNC_AUTO_REPAINT);
            }
            else if (pt_page_data->h_oled_off_rs== h_widget)
            {
                c_wgl_set_focus (pt_page_data->h_oled_jb, WGL_SYNC_AUTO_REPAINT);
            }
            return MENUR_OK;
        }

        switch (ui4_keycode)
        {
        case BTN_SELECT:
        {
            if (pt_page_data->h_iperf == h_widget)
            {
            #ifdef APP_IPERF_SUPPORT
                /* show iperf dialog */
                MENU_LOG_ON_FAIL( menu_network_iperf_dialog_set_data((UINT16)NW_IPERF_PORT_DEFAULT, FALSE));

                MENU_LOG_ON_FAIL(menu_network_iperf_dialog_show(MLM_MENU_KEY_NW_HELP_IPERF_PORT,
                                                        MLM_MENU_KEY_OK,
                                                        _iperf_dialog_btn_cb_fct,
                                                        TRUE));
                menu_pm_repaint();
            #endif
            }
        #ifdef APP_WIFI_SIGNAL_LVL_SUPPORT
            else if (pt_page_data->h_rssi == h_widget)
            {
                MENU_LOG_ON_FAIL( _menu_show_signal_lvl_dlg_show());
                menu_pm_repaint();
            }
        #endif
            else if (pt_page_data->h_provisions_btn== h_widget)
            {
                _menu_test_xx_list_box_show();
            }
            else if (pt_page_data->h_audio_dbginfo== h_widget)
            {
                menu_nav_go(ui4_g_menu_page_audio_dbginfo,NULL);
            }
            else if (pt_page_data->h_hdmi_dbginfo== h_widget)
            {
                menu_nav_go(ui4_g_menu_page_hdmi_dbginfo,NULL);
            }
            else if (pt_page_data->h_force_log_upload == h_widget)
            {
                AP_SYSTEM_CALL("touch /tmp/remotelogging/forceupload");
            }
            else if (pt_page_data->h_oled_off_rs== h_widget)
            {
                 DBG_LOG_PRINT(("[menu] %s,%d\r\n",__FUNCTION__,__LINE__));
                 a_cfg_cust_set_oled_off_rs(1);
                 a_amb_power_on(FALSE);
            }
            else if (pt_page_data->h_oled_jb== h_widget)
            {
                 DBG_LOG_PRINT(("[menu] %s,%d\r\n",__FUNCTION__,__LINE__));
                 a_cfg_cust_set_oled_jb(1);
                 a_cfg_cust_set_oled_off_rs(1);
                 a_amb_power_on(FALSE);
            }
            else
            {
                /* do nothing */
            }

            return MENUR_OK;
        }
        case BTN_CURSOR_LEFT:
    #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
    #endif

        case BTN_EXIT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_go_home_menu();
            return MENUR_OK;
        default:
            break;
        }

    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

INT32 get_ota_loop_test_value(VOID){
    UINT8 ui1_value = ACFG_VLOG_OFF;
    a_cfg_cust_get_ota_loop_test(&ui1_value);
    DBG_LOG_PRINT(("[VLOG][%s %d] ota loop test %d\n\r",__FUNCTION__,__LINE__,ui1_value));
    return ui1_value;
}

INT32 set_ota_loop_test_value(UINT32 ui1_value){
    a_cfg_cust_set_ota_loop_test(ui1_value);
    DBG_LOG_PRINT(("[VLOG][%s %d] ota loop test %d\n\r",__FUNCTION__,__LINE__,ui1_value));
    return MENUR_OK;
}

INT32 get_memc_value(VOID)
{
    UINT8 ui1_value = ACFG_VLOG_OFF;

    a_cfg_cust_get_memc(&ui1_value);
    DBG_LOG_PRINT(("[MENU][MEMC][%s %d] Get MEMC => value:%d \n",__FUNCTION__,__LINE__,ui1_value));

    return ui1_value;
}

INT32 set_memc_value(UINT32 ui1_value)
{
    DBG_LOG_PRINT(("[MENU][MEMC]{%s,%d} Set MECM value= %d\n",__FUNCTION__,__LINE__,ui1_value));

    a_cfg_cust_set_memc(ui1_value);

#if 1 // Sync ACFG method

 #if(ACFG_CUST_MEMC_NEW_METHOD)
    if( ui1_value )
    {
        // MEMC ...
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION));
    }
    else
    {
    #ifdef APP_MJC_SUPPORT
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT));
    #endif
    }

 #else
  #ifdef APP_MJC_SUPPORT
   a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT));
  #endif
 #endif

#else
    SM_COMMAND_T        at_sm_cmds[3];
    HANDLE_T            h_scc = NULL_HANDLE;
    SCC_VID_MJC_T       t_mjc;


    c_memset(&t_mjc, 0, sizeof(SCC_VID_MJC_T));
    DBG_LOG_PRINT(("[VLOG][%s %d] value= %d\n\r",__FUNCTION__,__LINE__,ui1_value));
    /* create the scc handles */
    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;
    c_scc_comp_open(at_sm_cmds, &h_scc);
    t_mjc.e_effect = ui1_value == 0 ? SCC_VID_MJC_EFFECT_OFF : SCC_VID_MJC_EFFECT_HIGH;
    c_scc_vid_set_mjc(h_scc, &t_mjc);
#endif

    return MENUR_OK;
}

#define SWITCH_OFF 0
#define SWITCH_ON  1

INT32 _menu_memc_fct(HANDLE_T            h_widget,
                           UINT32              ui4_msg,
                           VOID*               pv_param1,
                           VOID*               pv_param2)
{
    UINT32              ui4_value;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;

    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        ui4_value = get_memc_value();
        DBG_LOG_PRINT(("[MENU][TEST][%s %d] get current ui4_value => %x\n",__FUNCTION__,__LINE__,ui4_value));
        MENU_LOG_ON_FAIL(menu_list_set_idx(h_widget,(ui4_value == 0 ? SWITCH_OFF : SWITCH_ON )));
        MENU_LOG_ON_FAIL(menu_list_adjust_rect(pt_page_data->h_ota_test));
        menu_set_and_show_help_tip(L"<- or -> to switch to OFF/ON");
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            switch ((UINT32)pv_param1)
            {
                case BTN_CURSOR_RIGHT:
                case BTN_CURSOR_LEFT:
                {
                    ui4_value = get_memc_value();
                    DBG_LOG_PRINT(("[MENU][TEST][%s %d] before ui4_value => %x\n",__FUNCTION__,__LINE__,ui4_value));
                    if(ui4_value == 0) {
                        ui4_value = 1;
                    } else {
                        ui4_value = 0;
                    }
                    MENU_LOG_ON_FAIL(set_memc_value(ui4_value));
                    ui4_value = get_memc_value();
                    DBG_LOG_PRINT(("[MENU][TEST][%s %d] after ui4_value => %x\n",__FUNCTION__,__LINE__,ui4_value));
                    c_wgl_repaint(h_widget, NULL, TRUE);
                    break;
                }
                case BTN_CURSOR_UP:
                    c_wgl_set_focus (pt_page_data->h_rssi, WGL_SYNC_AUTO_REPAINT);
                    break;
                case BTN_CURSOR_DOWN:
                    c_wgl_set_focus (pt_page_data->h_ota_test, WGL_SYNC_AUTO_REPAINT);
                    break;
                case BTN_EXIT:
                case BTN_PREV_PRG:
                case BTN_RETURN:
                    menu_nav_go_home_menu();
                    return MENUR_OK;
                default:
                    break;
            }
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}


INT32 _menu_ota_loop_test_fct(HANDLE_T           h_widget,
                                  UINT32              ui4_msg,
                                  VOID*               pv_param1,
                                  VOID*               pv_param2)
{
    UINT32               ui4_ota_loop_test_value;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;

    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        ui4_ota_loop_test_value = get_ota_loop_test_value();
        DBG_LOG_PRINT(("[MENU][TEST][%s %d] get current ui4_ota_loop_test_value => %x\n",__FUNCTION__,__LINE__,ui4_ota_loop_test_value));
        MENU_LOG_ON_FAIL(menu_list_set_idx(h_widget,(ui4_ota_loop_test_value == 0 ? SWITCH_OFF : SWITCH_ON )));
        MENU_LOG_ON_FAIL(menu_list_adjust_rect(pt_page_data->h_ota_test));
        menu_set_and_show_help_tip(L"<- or -> to switch to OFF/ON");
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            switch ((UINT32)pv_param1)
            {
                case BTN_CURSOR_RIGHT:
                case BTN_CURSOR_LEFT:
                {
                    ui4_ota_loop_test_value = get_ota_loop_test_value();
                    DBG_LOG_PRINT(("[MENU][TEST][%s %d] before ui4_ota_loop_test_value => %x\n",__FUNCTION__,__LINE__,ui4_ota_loop_test_value));
                    if(ui4_ota_loop_test_value == 0) {
                        ui4_ota_loop_test_value = 1;
                        a_cfg_custom_set_oobe_mode(TRUE);
                    } else {
                        ui4_ota_loop_test_value = 0;
                        a_cfg_custom_set_oobe_mode(FALSE);
                    }
                    MENU_LOG_ON_FAIL(set_ota_loop_test_value(ui4_ota_loop_test_value));
                    ui4_ota_loop_test_value = get_ota_loop_test_value();
                    DBG_LOG_PRINT(("[MENU][TEST][%s %d] after ui4_ota_loop_test_value => %x\n",__FUNCTION__,__LINE__,ui4_ota_loop_test_value));
                    c_wgl_repaint(h_widget, NULL, TRUE);
                    break;
                }
                case BTN_CURSOR_UP:
                    if (menu_common_get_chipset() == CHIPSET_5695)
                    {
                        c_wgl_set_focus (pt_page_data->h_memc, WGL_SYNC_AUTO_REPAINT);
                    }
                    else
                    {
                        c_wgl_set_focus (pt_page_data->h_rssi, WGL_SYNC_AUTO_REPAINT);
                    }
                    break;
                case BTN_CURSOR_DOWN:
                    c_wgl_set_focus (pt_page_data->h_vlog, WGL_SYNC_AUTO_REPAINT);
                    break;
                case BTN_EXIT:
                case BTN_PREV_PRG:
                case BTN_RETURN:
                    menu_nav_go_home_menu();
                    return MENUR_OK;
                default:
                    break;
            }
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}


INT32 _menu_vlog_test_fct(HANDLE_T            h_widget,
                              UINT32              ui4_msg,
                              VOID*               pv_param1,
                              VOID*               pv_param2)
{
    // Fix coverity-4643632 Uninitialized scalar variable
    UINT8               ui1_log_level = LOGLEVEL_OFF;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;

    if(WGL_MSG_GET_FOCUS == ui4_msg)
    {
        a_cfg_cust_get_log_level(&ui1_log_level);
        DBG_LOG_PRINT(("[MENU][TEST][%s %d] get current log level => %x\n",__FUNCTION__,__LINE__,ui1_log_level));
        MENU_LOG_ON_FAIL(menu_list_set_idx(h_widget, (UINT16)ui1_log_level));
        menu_set_and_show_help_tip(L"Set log level:\n"\
            "->Off: Disable all log for better performance\n"\
            "->APP ONLY: print app log only\n"\
            "->KERNEL ONLY : print kernel/driver log only\n"\
            "->ALL: print kernel/driver/app log\n"\
        );
    }
    else if (WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            switch ((UINT32)pv_param1)
            {
                case BTN_CURSOR_RIGHT:
                case BTN_CURSOR_LEFT:
                {
                    UINT16 ui2_current_index = 0;
                    MENU_LOG_ON_FAIL(menu_list_get_idx(h_widget, &ui2_current_index));

                    if((UINT32)pv_param1 == BTN_CURSOR_RIGHT) {
                        if (ui2_current_index == 3){
                            ui2_current_index = 0;
                        }  else {
                            ui2_current_index += 1;
                        }
                    } else {
                        if (ui2_current_index == 0){
                            ui2_current_index = 3;
                        }  else {
                            ui2_current_index -= 1;
                        }
                    }

                    switch(ui2_current_index){
                        case 0: // OFF
                            ui1_log_level = LOGLEVEL_OFF; break;
                        case 1: // APP_ONLY
                            ui1_log_level = LOGLEVEL_APP_ONLY; break;
                        case 2: // KERNEL_ONLY
                            ui1_log_level = LOGLEVEL_KERNEL_ONLY; break;
                        case 3: // ALL (APP and Kernel)
                            ui1_log_level = LOGLEVEL_ALL; break;
                        default:
                            break;
                    }
                    menu_set_and_show_help_tip(MENU_TEXT(ui2_current_index + MLM_MENU_KEY_VLOG_OFF));
                    a_cfg_cust_set_log_level(ui1_log_level);
                    break;
                }
                case BTN_CURSOR_UP:
                    c_wgl_set_focus (pt_page_data->h_ota_test, WGL_SYNC_AUTO_REPAINT);
                    break;
                case BTN_CURSOR_DOWN:
                    c_wgl_set_focus (pt_page_data->h_provisions_btn, WGL_SYNC_AUTO_REPAINT);
                    break;
                case BTN_EXIT:
                case BTN_PREV_PRG:
                case BTN_RETURN:
                    menu_nav_go_home_menu();
                    return MENUR_OK;
                default:
                    break;
            }
            menu_list_adjust_rect(h_widget);    //CID:4643636
            break;
        }
        case WGL_MSG_PAINT:
        {
             DBG_LOG_PRINT(("[MENU][TEST][%s %d]WGL_MSG_PAINT\n",__FUNCTION__,__LINE__));
             menu_list_adjust_rect(h_widget);
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static INT32 _menu_test_main_page_hide(VOID)
{
    INT32 i4_ret = 0;
    PAGE_NW_HIDE_T * pt_this = &t_page_nw_hide;

    i4_ret = c_wgl_set_visibility(pt_this->h_iperf,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_rssi,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_memc,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);


    i4_ret = c_wgl_set_visibility(pt_this->h_ota_test,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_vlog,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_provisions_btn,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_force_log_upload,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);


    return i4_ret;
}


static INT32 _menu_test_xx_list_box_show(VOID)
{
    PAGE_NW_HIDE_T*     pt_this = &t_page_nw_hide;
    INT16   ui2_elem_num;
    INT16   ui2_i = 0;
    INT32   i4_ret;
    ui2_elem_num = MENU_XX_SIZE;
    i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ELEM_NUM,
                        WGL_PACK(ui2_elem_num),
                        NULL);
    MENU_CHK_FAIL(i4_ret);


    if (access("/certificate/drmp/GCast_Cert", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"GCast_Cert"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/GCast_key", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"GCast_key"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/NetFlix", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"NetFlix"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/WideVine", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"widevine"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/playready25_bgroup_cert", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"py_bgroup_cert"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/playready25_zgpriv", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"py25_zgpriv"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }

    if (access("/certificate/drmp/playready3_cert", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"py3_cert"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/playread3_key", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"py3_key"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/airplay_mfi", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"airplay_mfi"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/airplay_fps", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"airplay_fps"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/iot_cert", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"iot_cert"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/iot_key", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"iot_key"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/iot_truststore", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"iot_truststore"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/iotv2_cert", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"iotv2_cert"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/iotv2_key", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"iotv2_key"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/vizio_key", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"vizio_key"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }
    if (access("/certificate/drmp/vizio_cert", F_OK) == 0)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2 (ui2_i, 0),
                        WGL_PACK(L"vizio_cert"));
        MENU_CHK_FAIL(i4_ret);
        ui2_i++;
    }

    i4_ret = _menu_test_main_page_hide();
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_visibility(pt_this->h_xx_list_box, WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = c_wgl_set_focus(pt_this->h_xx_list_box, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);
    c_wgl_repaint(pt_this->h_cnt_frm, NULL, TRUE);
    return i4_ret;
}

static INT32 _menu_test_main_page_show(VOID)
{
    INT32            i4_ret = 0;
    UINT8            ui1_log_level;

    PAGE_NW_HIDE_T * pt_this = &t_page_nw_hide;

    i4_ret = c_wgl_set_visibility(pt_this->h_iperf,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_rssi,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (menu_common_get_chipset() == CHIPSET_5695)
    {

        i4_ret = c_wgl_set_visibility(pt_this->h_memc,
                                     WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_set_visibility(pt_this->h_memc,
                                     WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_this->h_ota_test,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    a_cfg_cust_get_log_level(&ui1_log_level);
    DBG_LOG_PRINT(("[MENU][TEST][%s %d] get current log level => %d\n",__FUNCTION__,__LINE__,ui1_log_level));
    MENU_LOG_ON_FAIL( menu_list_set_idx(pt_this->h_vlog, (UINT16)ui1_log_level));
    i4_ret = c_wgl_set_visibility(pt_this->h_vlog,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_provisions_btn,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_this->h_force_log_upload,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);


    return MENUR_OK;
}

static INT32 _menu_test_xx_list_box_nav_back(VOID)
{
    INT32 i4_ret = 0;
    PAGE_NW_HIDE_T * pt_this = &t_page_nw_hide;

    i4_ret = c_wgl_set_visibility(pt_this->h_xx_list_box, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _menu_test_main_page_show();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_this->h_provisions_btn, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    menu_pm_repaint();

    return MENUR_OK;
}




static INT32 _menu_test_xx_list_box_proc_fct(HANDLE_T            h_widget,
                                        UINT32              ui4_msg,
                                        VOID*               pv_param1,
                                        VOID*               pv_param2)
{
    INT32    i4_ret;
    PAGE_NW_HIDE_T * pt_this = &t_page_nw_hide;

    if(WGL_MSG_LOSE_FOCUS == ui4_msg)
    {
        UINT16   ui2_crnt_ht;
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                              WGL_CMD_LB_UNHLT_ELEM,
                              WGL_PACK(ui2_crnt_ht),
                              NULL);
        MENU_CHK_FAIL(i4_ret);
    }
    else if(WGL_MSG_KEY_DOWN == ui4_msg)
    {
        i4_ret = c_wgl_do_cmd(pt_this->h_xx_list_box,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&pt_this->ui2_xx_idx),
                              NULL);
        MENU_CHK_FAIL(i4_ret);

        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT:
                {
                    i4_ret = _menu_test_xx_list_box_nav_back();
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            case BTN_RETURN:
                {
                    i4_ret = _menu_test_xx_list_box_nav_back();
                    MENU_CHK_FAIL(i4_ret);
                }
                break;
            case BTN_CURSOR_UP:
              /*
                       if (pt_this->ui2_xx_idx == 0)
                       {
                           pt_this->ui2_xx_idx == 0;

                           pt_this->i2_hlt_idx = -1;
                           i4_ret = _ope_lst_update_focus(TRUE);
                           MENU_CHK_FAIL(i4_ret);

                           return MENUR_OK;

                       } */
                break;
            case BTN_CURSOR_DOWN:
                break;
            default:
                break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}



static INT32 _menu_test_xx_list_box_on_create(VOID)
{

    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;
    INT32  i4_ret;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    GL_RECT_T                 t_rect = {0};

    /* Listbox */
    {
        at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
        at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
        at_cols[0].ui2_max_text_len = 64;
        at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

        t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                      WGL_STL_LB_NO_SCROLL;

        t_lb_init.ui2_max_elem_num  = 32;
        t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
        t_lb_init.ui2_elem_distance = 0;
        t_lb_init.ui1_col_num       = 1;
        t_lb_init.at_cols           = at_cols;

        SET_RECT_BY_SIZE (&t_rect,
                          0,
                          0,
                          CONTENT_W,
                          CONTENT_H);

        i4_ret = menu_list2_create(pt_page_data->h_cnt_frm,
                                   &t_rect,
                                   _menu_test_xx_list_box_proc_fct,
                                   &t_lb_init,
                                   NULL,
                                   &pt_page_data->h_xx_list_box);
        MENU_CHK_FAIL(i4_ret);
    }
    /* WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE */
    {
        t_img_elem.h_normal             = h_g_menu_img_item_bk;
        t_img_elem.h_disable            = h_g_menu_img_item_bk;
        t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
        t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
        t_img_elem.h_pushed             = h_g_menu_img_item_bk;
        t_img_elem.h_selected           = h_g_menu_img_item_bk;
        t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
        i4_ret = c_wgl_do_cmd (pt_page_data->h_xx_list_box,
                               WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                               WGL_PACK(& t_img_elem),
                               NULL);
        MENU_CHK_FAIL(i4_ret);
    }
    /* WGL_CMD_LB_SET_COL_COLOR */
    {
        t_lb_color.t_normal = t_g_menu_color_white;
        t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
        t_lb_color.t_highlight = t_g_menu_color_white;
        t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
        t_lb_color.t_pushed = t_g_menu_color_white;
        t_lb_color.t_selected = t_g_menu_color_white;
        t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

        i4_ret = c_wgl_do_cmd(pt_page_data->h_xx_list_box,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2(0, WGL_CLR_TEXT),
                              WGL_PACK(&t_lb_color) );
        MENU_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_set_visibility(pt_page_data->h_xx_list_box, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret == WGLR_OK ? MENUR_OK : i4_ret);

    return MENUR_OK;

}


static INT32 _menu_test_provisions_btn_create(const INT32 i4_index)
{

    INT32               i4_ret;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;

    /* add xx */
    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)i4_index,
                                _action_items_proc_fct,
                                &pt_page_data->h_provisions_btn);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_provisions_btn,
                                 MLM_MENU_KEY_MENU_TEST_XX_TITLE,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

extern BOOL a_is_oled_compensation_support();

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
    INT32               i4_ret;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;
    INT32               i4_index = 0;
    /* add iPerf */
    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)i4_index,
                                _action_items_proc_fct,
                                &pt_page_data->h_iperf);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_iperf,
                                 MLM_MENU_KEY_IPERF,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_index++;

    /* add RSSI */
    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)i4_index,
                                _action_items_proc_fct,
                                &pt_page_data->h_rssi);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_rssi,
                                 MLM_MENU_KEY_RSSI,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_index++;

    /* add h_memc test */
    MENU_LOG_ON_FAIL(menu_list_create(pt_page_data->h_cnt_frm,
                                      (INT32)i4_index,
                                       2,
                                       _menu_memc_fct,
                                       &pt_page_data->h_memc));
    i4_ret=menu_list_chg_lang(pt_page_data->h_memc,
                              MLM_MENU_KEY_TEST_MEMC,
                              MLM_MENU_KEY_OFF,
                              MLM_MENU_KEY_ON);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_list_adjust_rect(pt_page_data->h_memc);
    if (menu_common_get_chipset() == CHIPSET_5695)
    {
        i4_index++;
    }


    /* add test ota loop test */
    MENU_LOG_ON_FAIL(menu_list_create(pt_page_data->h_cnt_frm,
                                      (INT32)i4_index,
                                       2,
                                       _menu_ota_loop_test_fct,
                                       &pt_page_data->h_ota_test));
    i4_ret=menu_list_chg_lang(pt_page_data->h_ota_test,
                              MLM_MENU_KEY_TEST_OTA_LOOP_TEST,
                              MLM_MENU_KEY_OFF,
                              MLM_MENU_KEY_ON);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_list_adjust_rect(pt_page_data->h_ota_test);

    i4_index++;
    /* add  V Logo*/
    MENU_LOG_ON_FAIL(menu_list_create(pt_page_data->h_cnt_frm,
                                      (INT32)i4_index,
                                       4,
                                       _menu_vlog_test_fct,
                                       &pt_page_data->h_vlog));
    i4_ret=menu_list_chg_lang(pt_page_data->h_vlog,
                              MLM_MENU_KEY_VLOG,
                              MLM_MENU_KEY_VLOG_OFF,
                              MLM_MENU_KEY_VLOG_ALL);
    MENU_LOG_ON_FAIL(i4_ret);
    menu_list_adjust_rect(pt_page_data->h_vlog);
    i4_index++;

    _menu_test_provisions_btn_create(i4_index);
    _menu_test_xx_list_box_on_create();

    i4_index++;
    /* add iPerf */
    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)i4_index,
                                _action_items_proc_fct,
                                &pt_page_data->h_force_log_upload);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_action_chg_lang(pt_page_data->h_force_log_upload,
                                 MLM_MENU_KEY_TEST_FORCE_UPLOAD_LOG,
                                 MLM_MENU_KEY_EMPTY);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_index++;
    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)i4_index,
                                _action_items_proc_fct,
                                &pt_page_data->h_audio_dbginfo);
    MENU_LOG_ON_FAIL(i4_ret);
    {
        UTF16_T w2s_str_tmp[128];
        c_memset(w2s_str_tmp, 0, 128);
        c_uc_w2s_strcat (w2s_str_tmp, L"Audio Status\0");
        /* Set Title language */
        i4_ret = c_wgl_do_cmd(pt_page_data->h_audio_dbginfo,
                              WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                              WGL_PACK(w2s_str_tmp),
                              WGL_PACK(c_uc_w2s_strlen(
                                  w2s_str_tmp)));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    i4_index++;
    i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                (INT32)i4_index,
                                _action_items_proc_fct,
                                &pt_page_data->h_hdmi_dbginfo);
    MENU_LOG_ON_FAIL(i4_ret);
    {
        UTF16_T w2s_str_tmp[128];
        c_memset(w2s_str_tmp, 0, 128);
        c_uc_w2s_strcat (w2s_str_tmp, L"HDMI Status\0");
        /* Set Title language */
        i4_ret = c_wgl_do_cmd(pt_page_data->h_hdmi_dbginfo,
                              WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                              WGL_PACK(w2s_str_tmp),
                              WGL_PACK(c_uc_w2s_strlen(
                                  w2s_str_tmp)));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if(a_is_oled_compensation_support())
    {
        i4_index++;
        /* add off-rs */
        i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                    (INT32)i4_index,
                                    _action_items_proc_fct,
                                    &pt_page_data->h_oled_off_rs);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_action_chg_lang(pt_page_data->h_oled_off_rs,
                                     MLM_MENU_KEY_SETTING_OFF_RS_ENTRY,
                                     MLM_MENU_KEY_EMPTY);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_index++;
        /* add oled jb */
        i4_ret = menu_action_create(pt_page_data->h_cnt_frm,
                                    (INT32)i4_index,
                                    _action_items_proc_fct,
                                    &pt_page_data->h_oled_jb);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = menu_action_chg_lang(pt_page_data->h_oled_jb,
                                     MLM_MENU_KEY_SETTING_OLED_JB_ENTRY,
                                     MLM_MENU_KEY_EMPTY);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _on_page_create
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
static INT32 _on_page_create(UINT32 ui4_page_id,
                                VOID * pv_create_data)
{
    INT32               i4_ret;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;

    c_memset(pt_page_data, 0, sizeof(PAGE_NW_HIDE_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &(pt_page_data->h_cnt_frm));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _subpage_item_create();
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_WIFI_SIGNAL_LVL_SUPPORT
    i4_ret = _menu_show_signal_lvl_dlg_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_timer_create(&pt_page_data->h_signal_lvl_timer);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_destroy
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
static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
#ifdef APP_WIFI_SIGNAL_LVL_SUPPORT
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;
    INT32               i4_ret = MENUR_OK;

    if (NULL_HANDLE != pt_page_data->h_signal_lvl_dlg)
    {
        i4_ret = a_ui_simple_dialog_destory(pt_page_data->h_signal_lvl_dlg);
        MENU_LOG_ON_FAIL(i4_ret);

        pt_page_data->b_is_dlg_show = FALSE;
    }

    if(TRUE == c_handle_valid(pt_page_data->h_signal_lvl_timer))
    {
        i4_ret = c_timer_delete(pt_page_data->h_signal_lvl_timer);
        MENU_LOG_ON_FAIL(i4_ret);
    }
#endif

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_show
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
static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32               i4_ret = MENUR_OK;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;
    GL_RECT_T           t_rect={0};
    UINT8               ui1_log_level = 0;
    UINT32              i4_item_count = 0;
    /* Change the menu title */
    menu_main_set_title(MLM_MENU_KEY_VIZIO_NETWORK_TEST);

    i4_ret = menu_show_backbar(TRUE, FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_iperf,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_item_count++;
    i4_ret = c_wgl_set_visibility(pt_page_data->h_rssi,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_item_count++;
    if (menu_common_get_chipset() == CHIPSET_5695)
    {
        MENU_LOG_ON_FAIL( menu_list_set_idx(pt_page_data->h_memc, get_memc_value() == 0 ? SWITCH_OFF : SWITCH_ON));
        i4_ret = c_wgl_set_visibility(pt_page_data->h_memc,
                                     WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_item_count++;
    }
    else
    {
        i4_ret = c_wgl_set_visibility(pt_page_data->h_memc,
                                     WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    MENU_LOG_ON_FAIL( menu_list_set_idx(pt_page_data->h_ota_test,get_ota_loop_test_value() == 0 ? SWITCH_OFF : SWITCH_ON));
    i4_ret = c_wgl_set_visibility(pt_page_data->h_ota_test,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_item_count++;

    a_cfg_cust_get_log_level(&ui1_log_level);
    DBG_LOG_PRINT(("[MENU][TEST][%s %d] get current log level => %d\n",__FUNCTION__,__LINE__,ui1_log_level));
    MENU_LOG_ON_FAIL( menu_list_set_idx(pt_page_data->h_vlog, (UINT16)ui1_log_level));
    i4_ret = c_wgl_set_visibility(pt_page_data->h_vlog,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    menu_list_adjust_rect(pt_page_data->h_vlog);
    i4_item_count++;

    i4_ret = c_wgl_set_visibility(pt_page_data->h_provisions_btn,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_item_count++;

    i4_ret = c_wgl_set_visibility(pt_page_data->h_force_log_upload,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_item_count++;

    i4_ret = c_wgl_set_visibility(pt_page_data->h_audio_dbginfo,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_item_count++;

    i4_ret = c_wgl_set_visibility(pt_page_data->h_hdmi_dbginfo,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_item_count++;

    if(a_is_oled_compensation_support())
    {
        i4_ret = c_wgl_set_visibility(pt_page_data->h_oled_off_rs,
                                     WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_item_count++;
        i4_ret = c_wgl_set_visibility(pt_page_data->h_oled_jb,
                                     WGL_SW_NORMAL);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_item_count++;
    }

    i4_ret = c_wgl_set_visibility(pt_page_data->h_xx_list_box, WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left    = CONTENT_X;
    t_rect.i4_right   = CONTENT_X + CONTENT_H;
    t_rect.i4_top     = i4_item_count* MENU_ITEM_V_HEIGHT + CONTENT_Y + 25;
    t_rect.i4_bottom  = t_rect.i4_top + 150;

    i4_ret = c_wgl_move(h_last_shadow_item,&t_rect,WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item,WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

#if 0
    UINT8          ui1_tts_idx = 0;
    i4_ret = a_cfg_get_tts_switch_status(&ui1_tts_idx);
    ui1_tts_idx_last = ui1_tts_idx;
    if (ui1_tts_idx == 1)
    {
        a_cfg_set_tts_switch_status((UINT8)0);
        a_cfg_update_tts_switch_status();
        rest_event_notify("app/tts/enabled", 0, "Off");

    }
#endif
    c_wgl_repaint(pt_page_data->h_cnt_frm,NULL,TRUE);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_hide
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
static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32               i4_ret;
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;
    HANDLE_T            h_last_shadow_item = NULL_HANDLE;

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_get_last_shadow_item(&h_last_shadow_item);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);
#if 0
    if(ui1_tts_idx_last == 1)
    {
        a_cfg_set_tts_switch_status((UINT8)1);
        a_cfg_update_tts_switch_status();
        rest_event_notify("app/tts/enabled", 0, "On");
        ui1_tts_idx_last = 0;
    }
#endif
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_get_focus
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
static INT32 _on_page_get_focus(
                                    UINT32 ui4_page_id,
                                    MENU_PAGE_HINT_T* pt_hint)
{
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;

    /* set callback function for backbar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc(_backbar_proc_fct));

    /* set callback function for homebar */
    MENU_LOG_ON_FAIL (menu_set_homebar_proc(_homebar_proc_fct));

    MENU_LOG_ON_FAIL (c_wgl_set_focus (pt_page_data->h_iperf, WGL_NO_AUTO_REPAINT));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_lose_focus
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
static INT32 _on_page_lose_focus(
                                    UINT32 ui4_page_id)
{
    /* clean callback function of backbar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc(NULL));

    /* set callback function for homebar */
    MENU_LOG_ON_FAIL (menu_set_homebar_proc(NULL));

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_page_update
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
static INT32 _on_page_update(
                                UINT32 ui4_page_id,
                                UINT32 ui4_update_mask)
{
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_common_page_nw_hide_init
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
INT32 menu_common_page_test_special_param_init(VOID)
{
    t_g_menu_common_test_special_param.pf_menu_page_create     = _on_page_create;
    t_g_menu_common_test_special_param.pf_menu_page_destroy    = _on_page_destroy;
    t_g_menu_common_test_special_param.pf_menu_page_show       = _on_page_show;
    t_g_menu_common_test_special_param.pf_menu_page_hide       = _on_page_hide;
    t_g_menu_common_test_special_param.pf_menu_page_get_focus  = _on_page_get_focus;
    t_g_menu_common_test_special_param.pf_menu_page_lose_focus = _on_page_lose_focus;
    t_g_menu_common_test_special_param.pf_menu_page_update     = _on_page_update;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_menu_test_page_osd_hide
 *
 * Description:
 *      Hide the test page osd.
 * Inputs:
 *      None
 * Outputs:
 *      None
 * Returns:
 *      MENUR_OK        Success
 *      Ohers           Fail
 ----------------------------------------------------------------------------*/
INT32 a_menu_test_page_osd_hide(VOID)
{
#ifdef APP_WIFI_SIGNAL_LVL_SUPPORT
    PAGE_NW_HIDE_T*     pt_page_data = &t_page_nw_hide;
    if (pt_page_data->b_is_dlg_show)
    {
        _menu_show_signal_lvl_dlg_hide();
    }
#endif

#ifdef APP_IPERF_SUPPORT
    menu_network_simple_dialog_hide(FALSE);
#endif

    return MENUR_OK;
}
