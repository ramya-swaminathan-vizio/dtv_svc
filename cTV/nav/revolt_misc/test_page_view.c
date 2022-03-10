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
 * $RCSfile: test_page_view.c,v $
 * $Revision: #1 $
 * $Date: 2016/02/22 $
 * $Author: sin_fangyuan $
 * $CCRevision:  $
 * $SWAuthor: $
 * $MD5HEX:  $
 *
 * Description:
 *       test page
 *
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <stdlib.h>

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_common.h"
#include "u_sys_name.h"
#include "u_sm_audio_hdlr.h"
#include "u_svl.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "u_wgl_sets.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_bdr_uniform.h"
#include "u_wgl_bdr_raised.h"
#include "u_wgl_tools.h"
#include "u_dbg.h"
#include "u_pcl.h"
#include "u_gl.h"
#include "u_net_wlan.h"

#include "c_common.h"
#include "c_os.h"
#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl_image.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_dbg.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "c_tsl.h"
#include "c_wgl.h"
#include "c_pcl.h"

#include "app_util/a_key_seq.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "app_util/a_network.h"
//#include "wizard/wzd_util.h"

#include "nav/nav_common.h"
#include "nav/dialog/nav_dialog.h"
#include "nav/revolt_misc/revolt_misc.h"
#include "nav/revolt_misc/revolt_misc_view.h"
#include "nav/revolt_misc/test_page_view.h"
#include "nav/pop/a_pop.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "wdk/widget/wdk_widget.h"

#include "res/nav/nav_mlm.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_colors.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/network/network_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

#define RET_ON_ERR(_expr)  \
{ \
    INT32 expr = _expr; \
    if(expr != 0)\
    {\
        DBG_LOG_PRINT(("<TEST_PAGE_VIEW> ERR: file = %s, line = %d\n\r", __FILE__, __LINE__)); \
        return expr;\
    } \
}

typedef struct _PAGE_TEST_VIEW_T
{
    HANDLE_T        h_canvas;

    HANDLE_T        h_app;
    /* widget */
    HANDLE_T        h_frame;   /* Main frame */
    HANDLE_T        h_cnt_text;
    HANDLE_T        h_left_text_1;
    HANDLE_T        h_left_text_2;
    HANDLE_T        h_left_text_3;
    HANDLE_T        h_right_text_1;
    HANDLE_T        h_right_text_2;
    HANDLE_T        h_right_text_3;

    HANDLE_T        h_signal_lvl_timer;

    wgl_widget_proc_fct     pf_frame_proc;
    WGL_HIMG_TPL_T          h_bk_img_tpl;
} PAGE_TEST_VIEW_T;

#define TEST_MENU_WIDTH                     (613)
#define TEST_MENU_HEIGHT                    (234)
#define TEST_MENU_X                         (600)
#define TEST_MENU_Y                         (400)

#define MENU_TEXT_WIDTH                     (200)
#define MENU_TEXT_HEIGHT                    (40)
#define MENU_TEXT_X                         (200)
#define MENU_TEXT_Y                         (60)

#define IPERF_TEXT_WIDTH                     (200)
#define IPERF_TEXT_HEIGHT                    (30)
#define IPERF_TEXT_X                         (150)
#define IPERF_TEXT_Y                         (110)

#define RSSI_TEXT_WIDTH                     (220)
#define RSSI_TEXT_HEIGHT                    (30)
#define RSSI_TEXT_X                         (150)
#define RSSI_TEXT_Y                         (140)

#define IPERF_LAUNCH_WIDTH                     (200)
#define IPERF_LAUNCH_HEIGHT                    (40)
#define IPERF_LAUNCH_X                         (200)
#define IPERF_LAUNCH_Y                         (80)

#define IPERF_PORT_WIDTH                     (420)
#define IPERF_PORT_HEIGHT                    (40)
#define IPERF_PORT_X                         (100)
#define IPERF_PORT_Y                         (120)

#define RSSI_MENU_WIDTH                     (220)
#define RSSI_MENU_HEIGHT                    (16)
#define RSSI_MENU_X                         (200)
#define RSSI_MENU_Y                         (30)

#define RSSI_LTEXT_WIDTH                     (208)
#define RSSI_LTEXT_HEIGHT                    (36)
#define RSSI_LTEXT_X                         (60)
#define RSSI_LTEXT_Y                         (86)

#define RSSI_RTEXT_WIDTH                     (208)
#define RSSI_RTEXT_HEIGHT                    (36)
#define RSSI_RTEXT_X                         (345)
#define RSSI_RTEXT_Y                         (86)

#define NW_FREQ_2_4             ((UINT8)0)
#define NW_FREQ_5_0             ((UINT8)1)
#define IEEE80211_CAP_IBSS      (0x0002)
#define MAC2STR(a) (a)[0], (a)[1], (a)[2], (a)[3], (a)[4], (a)[5]
#define MACSTR "%02x:%02x:%02x:%02x:%02x:%02x"

#define COLS_WIDTH              (36)

static PAGE_TEST_VIEW_T             tg_test_view = {0};
static PAGE_TEST_VIEW_T             tg_iperf_view = {0};
static PAGE_TEST_VIEW_T             tg_rssi_view = {0};



static WDK_TOAST_PARAM_T       tg_toast_param;

static HANDLE_T         h_timer_show = NULL_HANDLE;

static BOOL             b_receive = FALSE;

static UINT16           ui2_port_value = 8200;
static UINT8            i1_g_freq = NW_FREQ_2_4;
static WDK_OSD_TOAST_T  	t_g_wdk_view={0} ;



static INT32 _test_page_view_hide (VOID);

static INT32 _test_page_string_toast_view(HANDLE_T h_canvas,
                                                UTF16_T* w2s_txt);
static INT32 _test_page_text_create(PAGE_TEST_VIEW_T* tg_view,
                                        GL_RECT_T* t_rect,
                                        INT32    f_size,
                                        UTF16_T* w2s_txt);


static INT32 _test_page_rssi_frame_create (VOID);

static INT32 _test_page_rssi_text_create(VOID);

static INT32 _test_page_rssi_view_hide (VOID);

static INT32 _test_page_rssi_view_create (VOID);

static INT32 _test_page_iperf_frame_create (VOID);

static INT32 _test_page_iperf_text_create(VOID);

static INT32 _test_page_iperf_view_create (VOID);




/*----------------------------------------------------------------------------
* Name:  _start_iperf
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static INT32 _start_iperf (VOID)
{
    INT32       i4_ret = 0;
    CHAR        s_cmd_buffer[128] = {0};

    c_sprintf(s_cmd_buffer, "/basic/iperf -s -i 1 -p %d &", ui2_port_value);

    i4_ret = system(s_cmd_buffer);
    if (i4_ret != 0)
    {
       DBG_ERROR(("<TEST PAGE> start iPerf error:%s:%d:%d\r\n",
                    __FILE__, __LINE__, i4_ret));
    }

    DBG_LOG_PRINT(("[EST PAGE] start iPerf cmd: %s.\n", s_cmd_buffer));

    return NAV_OK;
}

/*----------------------------------------------------------------------------
* Name:  _test_page_show_signal_lvl_update
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static INT32 _test_page_show_signal_lvl_update(VOID)
{
    INT32                       i4_ret  = NAV_OK;
    CHAR                        s_buffer[128] = {0};
    UTF16_T                     w2s_tmp_str[128];
    UTF16_T                     w2s_str[128];
    NET_802_11_WIFI_RSSI_T      t_rssi;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_buffer,0,sizeof(CHAR)*128);

    c_memset (&t_rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));
    i4_ret = a_nw_wlan_get_rssi(&t_rssi);
    RET_ON_ERR(i4_ret);

    DBG_LOG_PRINT(("\n\n------------- Current RSSI info: -------------\n"));
    DBG_LOG_PRINT(("i4Rssi_a:\t\t %d\n", t_rssi.i4Rssi_a));
    DBG_LOG_PRINT(("i4Rssi_b:\t\t %d\n", t_rssi.i4Rssi_b));
    DBG_LOG_PRINT(("i4Rssi_c:\t\t %d\n", t_rssi.i4Rssi_c));

    /* i2_Freq == 0, check i2_Channel */
    if (i1_g_freq == NW_FREQ_2_4)
    {
        if (t_rssi.i4Rssi_b > -99)
        {
            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "2.4-1: %d dBm", t_rssi.i4Rssi_a);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_1,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "2.4-2: %d dBm", t_rssi.i4Rssi_b);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_2,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "Combo: %d dBm", (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_3,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);
        }
        else
        {
            //c_sprintf(s_buffer, "RSSI Power Levels \n\n 2.4-1: %d dBm", t_rssi.i4Rssi_a);
            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "2.4-1: %d dBm", t_rssi.i4Rssi_a);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_1,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);
        }
    }
    else if(i1_g_freq == NW_FREQ_5_0)
    {
        /* 5.0GHz */

        if (t_rssi.i4Rssi_b > -99)
        {
            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "5.0-1: %d dBm", t_rssi.i4Rssi_a);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_1,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "5.0-2: %d dBm", t_rssi.i4Rssi_b);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_2,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "Combo: %d dBm", (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_3,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);
        }
        else
        {
            //c_sprintf(s_buffer, "RSSI Power Levels \n\n 5.0-1: %d dBm", t_rssi.i4Rssi_a);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "5.0-1: %d dBm", t_rssi.i4Rssi_a);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_right_text_1,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);
        }
    }

    i4_ret = c_wgl_repaint(tg_rssi_view.h_frame,NULL,TRUE);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*----------------------------------------------------------------------------
* Name: _do_update_wlan_signal_level
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static VOID _do_update_wlan_signal_level(VOID* pv_data1,
                                            VOID* pv_data2,
                                            VOID* pv_data3)
{
    _test_page_show_signal_lvl_update();
}

/*----------------------------------------------------------------------------
* Name: _timer_wlan_signal_nfy_fct
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static VOID _timer_wlan_signal_nfy_fct(HANDLE_T h_timer,VOID* pv_tag)
{
    nav_request_context_switch(_do_update_wlan_signal_level, NULL, NULL, NULL);
}


/*----------------------------------------------------------------------------
* Name:  _test_page_show_signal_lvl_show
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static INT32 _test_page_show_signal_lvl_show(VOID)
{
    INT32                       i4_ret  = NAV_OK;
    CHAR                        s_buffer[128] = {0};
    UTF16_T                     w2s_tmp_str[128];
    UTF16_T                     w2s_str[128];
    NET_802_11_BSS_INFO_T       t_CurrBss;
    NET_802_11_WIFI_RSSI_T      t_rssi;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_buffer,0,sizeof(CHAR)*128);

    c_memset (&t_rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));
    i4_ret = a_nw_wlan_get_rssi(&t_rssi);
    RET_ON_ERR(i4_ret);

    DBG_LOG_PRINT(("\n\n------------- Current RSSI info: -------------\n"));
    DBG_LOG_PRINT(("i4Rssi_a:\t\t %d\n", t_rssi.i4Rssi_a));
    DBG_LOG_PRINT(("i4Rssi_b:\t\t %d\n", t_rssi.i4Rssi_b));
    DBG_LOG_PRINT(("i4Rssi_c:\t\t %d\n", t_rssi.i4Rssi_c));

    c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);
    if(i4_ret < 0)
    {
        DBG_LOG_PRINT(("<RSSI,get curr bass fail\n"));
    }

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
            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "2.4-1: %d dBm", t_rssi.i4Rssi_a);
            c_uc_ps_to_w2s(s_buffer,  w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_1,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "2.4-2: %d dBm", t_rssi.i4Rssi_b);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_2,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "Combo: %d dBm", (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
            c_uc_ps_to_w2s(s_buffer, w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_3,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);
        }

        else
        {
            //c_sprintf(s_buffer, "RSSI Power Levels \n\n 2.4-1: %d dBm", t_rssi.i4Rssi_a);
            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "2.4-1: %d dBm", t_rssi.i4Rssi_a);
            c_uc_ps_to_w2s(s_buffer,  w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_1,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);
        }
    }

    else
    {
        /* 5.0GHz */
        i1_g_freq = NW_FREQ_5_0;

        if (t_rssi.i4Rssi_b > -99)
        {
            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "5.0-1: %d dBm", t_rssi.i4Rssi_a);
            c_uc_ps_to_w2s(s_buffer,  w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_1,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "5.0-2: %d dBm", t_rssi.i4Rssi_b);
              c_uc_ps_to_w2s(s_buffer,  w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_2,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "Combo: %d dBm", (t_rssi.i4Rssi_a + t_rssi.i4Rssi_b)/2);
            c_uc_ps_to_w2s(s_buffer,  w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_3,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);
        }
        else
        {
            //c_sprintf(s_buffer, "RSSI Power Levels \n\n 5.0-1: %d dBm", t_rssi.i4Rssi_a);

            c_memset(s_buffer,0,sizeof(CHAR)*128);
            c_sprintf(s_buffer, "5.0-1: %d dBm", t_rssi.i4Rssi_a);
            c_uc_ps_to_w2s(s_buffer,  w2s_tmp_str, c_strlen(s_buffer));
            i4_ret = c_wgl_do_cmd(tg_rssi_view.h_right_text_1,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_tmp_str),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_tmp_str)));
            RET_ON_ERR(i4_ret);
        }

    }
    i4_ret = c_wgl_repaint(tg_rssi_view.h_frame,NULL,TRUE);
    RET_ON_ERR(i4_ret);

    /* start repeat timer */
    i4_ret = c_timer_start(tg_rssi_view.h_signal_lvl_timer,
                      1000,
                      X_TIMER_FLAG_REPEAT,
                      _timer_wlan_signal_nfy_fct,
                      NULL);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*----------------------------------------------------------------------------
* Name: _do_show_timer
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static VOID _do_show_timer(VOID* pv_data1,
                                 VOID* pv_data2,
                                 VOID* pv_data3)
{
    a_wdk_toast_hide(FALSE,&tg_toast_param,&t_g_wdk_view);
    if(b_receive)
    {
        b_receive = FALSE;
       _test_page_iperf_view_create();
        _start_iperf();
    }

    if (h_timer_show)
    {
        c_timer_delete(h_timer_show);
        h_timer_show = NULL_HANDLE;
     }

}

/*----------------------------------------------------------------------------
* Name: _timer_show_fct
* Description:
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static VOID _timer_show_fct(HANDLE_T  h_timer,
                                  VOID*     pv_tag)
{
    nav_request_context_switch(_do_show_timer,NULL, NULL,NULL);
}

/*----------------------------------------------------------------------------
 * Name: _test_page_string_toast_nfy_fct
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32  _test_page_string_toast_nfy_fct(HANDLE_T            h_widget,
                                                    UINT32              ui4_msg,
                                                    VOID*               pv_param1,
                                                    VOID*               pv_param2 )
{
    INT32     i4_ret;
    UINT32    ui4_keycode = (UINT32)pv_param1;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
                case BTN_DIGIT_4:
                {
                   DBG_LOG_PRINT(("<_test_page_BTN_DIGIT_4>info:file=%s,line=%d\n\r",__FILE__,__LINE__));
                   b_receive = TRUE;
                   nav_rcu_key_handler(ui4_keycode);
                }
                    break;
                default:
                    break;
            }
        }
        default:
        {
            DBG_LOG_PRINT(("<_test_page_default>info:file=%s,line=%d\n\r",__FILE__,__LINE__));
            b_receive = TRUE;
        }
            break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*----------------------------------------------------------------------------
* Name: _test_page_string_toast_view
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static INT32 _test_page_string_toast_view(HANDLE_T h_canvas,UTF16_T* w2s_txt)
{
    INT32   i4_ret;

    tg_toast_param.e_toast_style = WDK_STRING_TOAST;
    tg_toast_param.w2s_str       = (VOID*)w2s_txt;
    tg_toast_param.pf_cb         = _test_page_string_toast_nfy_fct;

    i4_ret = a_wdk_toast_init(h_canvas,&tg_toast_param,&t_g_wdk_view);
    RET_ON_ERR(i4_ret);

    tg_toast_param.h_t_focus_handle = t_g_wdk_view.h_base_frm;

    i4_ret = a_wdk_toast_activate(FALSE,&tg_toast_param,&t_g_wdk_view);
    RET_ON_ERR(i4_ret);

     /* enable the show timer */
    i4_ret = c_timer_start(h_timer_show,
                            3000,
                            X_TIMER_FLAG_ONCE,
                            _timer_show_fct,
                            NULL);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
 }


/*----------------------------------------------------------------------------
* Name: _test_page_text_create
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static INT32 _test_page_text_create(PAGE_TEST_VIEW_T* tg_view,
                                        GL_RECT_T* t_rect,
                                        INT32    f_size,
                                        UTF16_T* w2s_txt)
{
    INT32               i4_ret;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    i4_ret = c_wgl_create_widget(tg_view->h_frame,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                t_rect,
                                NULL,
                                255,
                                (VOID*)WGL_STL_TEXT_MAX_128,
                                tg_view,
                                &(tg_view->h_cnt_text));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_view->h_cnt_text,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_LEFT_CENTER),
                           NULL);
    RET_ON_ERR(i4_ret);

      //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = f_size;

    i4_ret = c_wgl_do_cmd (tg_view->h_cnt_text,
                        WGL_CMD_GL_SET_FONT,
                        WGL_PACK(&t_fnt_info),
                        NULL);
    RET_ON_ERR(i4_ret);

      //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(tg_view->h_cnt_text,
                        WGL_CMD_GL_SET_COLOR,
                        WGL_PACK(WGL_CLR_TEXT),
                        WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_view->h_cnt_text,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_txt),
                        WGL_PACK((UINT16)c_uc_w2s_strlen(w2s_txt)));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_view->h_cnt_text, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _test_page_rssi_frame_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _test_page_rssi_frame_nfy_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{
    INT32     i4_ret;
    UINT32    ui4_keycode = (UINT32)pv_param1;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
            case BTN_SELECT:
                {
                    DBG_LOG_PRINT(("<_test_page_BTN_SELECT>info:file=%s,line=%d\n\r",__FILE__,__LINE__));
                    i4_ret = _test_page_rssi_view_hide();
                    RET_ON_ERR(i4_ret);

                    //nav_rcu_key_handler(ui4_keycode);
                }
                break;
            default:
                break;
            }
            break;
        }
        case WGL_MSG_KEY_UP:
            break;
        default:
            break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}
#if 0
/*----------------------------------------------------------------------------
* Name:  _test_page_right_lvl_text_create
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static INT32 _test_page_right_lvl_text_create(VOID)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      RSSI_RTEXT_X,
                      RSSI_RTEXT_Y,
                      RSSI_RTEXT_WIDTH ,
                      RSSI_RTEXT_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_rssi_view.h_frame,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)WGL_STL_TEXT_MAX_128,
                                &tg_rssi_view,
                                &(tg_rssi_view.h_right_text_1));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_right_text_1,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_LEFT_TOP),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      RSSI_RTEXT_X,
                      RSSI_RTEXT_Y + 36,
                      RSSI_RTEXT_WIDTH ,
                      RSSI_RTEXT_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_rssi_view.h_frame,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)WGL_STL_TEXT_MAX_128,
                                &tg_rssi_view,
                                &(tg_rssi_view.h_right_text_2));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_right_text_2,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_LEFT_CENTER),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      RSSI_RTEXT_X,
                      RSSI_RTEXT_Y + 72,
                      RSSI_RTEXT_WIDTH ,
                      RSSI_RTEXT_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_rssi_view.h_frame,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)WGL_STL_TEXT_MAX_128,
                                &tg_rssi_view,
                                &(tg_rssi_view.h_right_text_3));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_right_text_3,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_LEFT_BOTTOM),
                           NULL);
    RET_ON_ERR(i4_ret);

      //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 21;

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_right_text_1,
                        WGL_CMD_GL_SET_FONT,
                        WGL_PACK(&t_fnt_info),
                        NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_right_text_2,
                        WGL_CMD_GL_SET_FONT,
                        WGL_PACK(&t_fnt_info),
                        NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_right_text_3,
                        WGL_CMD_GL_SET_FONT,
                        WGL_PACK(&t_fnt_info),
                        NULL);
    RET_ON_ERR(i4_ret);

      //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(tg_rssi_view.h_right_text_1,
                        WGL_CMD_GL_SET_COLOR,
                        WGL_PACK(WGL_CLR_TEXT),
                        WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_rssi_view.h_right_text_2,
                        WGL_CMD_GL_SET_COLOR,
                        WGL_PACK(WGL_CLR_TEXT),
                        WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_rssi_view.h_right_text_3,
                        WGL_CMD_GL_SET_COLOR,
                        WGL_PACK(WGL_CLR_TEXT),
                        WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_rssi_view.h_right_text_1, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_rssi_view.h_right_text_2, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_rssi_view.h_right_text_3, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}
#endif
/*----------------------------------------------------------------------------
* Name: _test_page_left_lvl_text_create
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
----------------------------------------------------------------------------*/
static INT32 _test_page_left_lvl_text_create(VOID)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      RSSI_LTEXT_X,
                      RSSI_LTEXT_Y,
                      RSSI_LTEXT_WIDTH ,
                      RSSI_LTEXT_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_rssi_view.h_frame,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)WGL_STL_TEXT_MAX_128,
                                &tg_rssi_view,
                                &(tg_rssi_view.h_left_text_1));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_left_text_1,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_LEFT_TOP),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      RSSI_LTEXT_X,
                      RSSI_LTEXT_Y + 36,
                      RSSI_LTEXT_WIDTH ,
                      RSSI_LTEXT_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_rssi_view.h_frame,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)WGL_STL_TEXT_MAX_128,
                                &tg_rssi_view,
                                &(tg_rssi_view.h_left_text_2));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_left_text_2,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_LEFT_CENTER),
                           NULL);
    RET_ON_ERR(i4_ret);

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      RSSI_LTEXT_X,
                      RSSI_LTEXT_Y + 72,
                      RSSI_LTEXT_WIDTH ,
                      RSSI_LTEXT_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_rssi_view.h_frame,
                                HT_WGL_WIDGET_TEXT,
                                WGL_CONTENT_TEXT_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID*)WGL_STL_TEXT_MAX_128,
                                &tg_rssi_view,
                                &(tg_rssi_view.h_left_text_3));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_left_text_3,
                           WGL_CMD_TEXT_SET_ALIGN,
                           WGL_PACK(WGL_AS_LEFT_BOTTOM),
                           NULL);
    RET_ON_ERR(i4_ret);

      //Set Font
    c_memset(&t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size      = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style     = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap      = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size  = 21;

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_left_text_1,
                        WGL_CMD_GL_SET_FONT,
                        WGL_PACK(&t_fnt_info),
                        NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_left_text_2,
                        WGL_CMD_GL_SET_FONT,
                        WGL_PACK(&t_fnt_info),
                        NULL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd (tg_rssi_view.h_left_text_3,
                        WGL_CMD_GL_SET_FONT,
                        WGL_PACK(&t_fnt_info),
                        NULL);
    RET_ON_ERR(i4_ret);

      //Set Color
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_1,
                        WGL_CMD_GL_SET_COLOR,
                        WGL_PACK(WGL_CLR_TEXT),
                        WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_2,
                        WGL_CMD_GL_SET_COLOR,
                        WGL_PACK(WGL_CLR_TEXT),
                        WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_do_cmd(tg_rssi_view.h_left_text_3,
                        WGL_CMD_GL_SET_COLOR,
                        WGL_PACK(WGL_CLR_TEXT),
                        WGL_PACK(&t_clr_info ));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_rssi_view.h_left_text_1, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_rssi_view.h_left_text_2, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_rssi_view.h_left_text_3, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*----------------------------------------------------------------------------
* Name: _test_page_rssi_text_create
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _test_page_rssi_text_create(VOID)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    UTF16_T             w2s_tmp_str[128] = {0};
    UINT16              ui2_lang = 0;
    ISO_639_LANG_T      s639_lang;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      RSSI_MENU_X,
                      RSSI_MENU_Y,
                      RSSI_MENU_WIDTH,
                      RSSI_MENU_HEIGHT);

    i4_ret = a_cfg_get_gui_lang(s639_lang);
    RET_ON_ERR(i4_ret);

    ui2_lang = mlm_nav_s639_to_langidx(s639_lang);

    c_uc_w2s_strcpy(w2s_tmp_str,MLM_NAV_TEXT(ui2_lang,MLM_NAV_KEY_NAV_RSSI_TITLE));

    i4_ret = _test_page_text_create(&tg_rssi_view,
                                    &t_rect,
                                    21,
                                    w2s_tmp_str);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*-----------------------------------------------------------------------------
* Name:
*     _test_page_rssi_frame_create
* Description:
*      show UI.
* Input arguments:
*      None
* Output arguments:
*      None
* Returns:
*      NAV_OK         Successful
*      Others          Fail
*---------------------------------------------------------------------------*/
static INT32 _test_page_rssi_frame_create (VOID)
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    WGL_IMG_INFO_T    t_img_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     TEST_MENU_X,
                     TEST_MENU_Y,
                     TEST_MENU_WIDTH,
                     TEST_MENU_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_test_view.h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _test_page_rssi_frame_nfy_fct,
                                 255,
                                 NULL,
                                 &(tg_rssi_view),
                                 &(tg_rssi_view.h_frame));

    RET_ON_ERR(i4_ret);

     //get background img
    i4_ret = nav_img_create_revolt_misc_bk(&(tg_rssi_view.h_bk_img_tpl));
    RET_ON_ERR(i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = tg_rssi_view.h_bk_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = tg_rssi_view.h_bk_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = tg_rssi_view.h_bk_img_tpl;
    i4_ret = c_wgl_do_cmd(tg_rssi_view.h_frame,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_rssi_view.h_frame, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
 }

 /*-----------------------------------------------------------------------------
  * Name:
  *      _test_page_rssi_view_hide
  * Description:
  *      show UI.
  * Input arguments:
  *      None
  * Output arguments:
  *      None
  * Returns:
  *      NAVR_OK         Successful
  *      Others          Fail
  *---------------------------------------------------------------------------*/
static INT32 _test_page_rssi_view_hide (VOID)
{
    INT32 i4_ret;

    i4_ret = c_timer_stop(tg_rssi_view.h_signal_lvl_timer);
    RET_ON_ERR(i4_ret);

    if(tg_rssi_view.h_signal_lvl_timer)
    {
        i4_ret = c_timer_delete(tg_rssi_view.h_signal_lvl_timer);
        RET_ON_ERR(i4_ret);
        tg_rssi_view.h_signal_lvl_timer = NULL_HANDLE;
    }

    i4_ret = c_wgl_show(tg_rssi_view.h_frame, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);
#if 0
    i4_ret = c_wgl_destroy_widget_ex(tg_rssi_view.h_frame, FALSE);
    RET_ON_ERR(i4_ret);
#endif
     return NAV_OK;
 }

 /*-----------------------------------------------------------------------------
  * Name:
  *      _test_page_rssi_view_create
  * Description:
  *      show UI.
  * Input arguments:
  *      None
  * Output arguments:
  *      None
  * Returns:
  *      NAVR_OK         Successful
  *      Others          Fail
  *---------------------------------------------------------------------------*/
static INT32 _test_page_rssi_view_create (VOID)
{
    INT32 i4_ret;

    i4_ret =  _test_page_rssi_frame_create();
    RET_ON_ERR(i4_ret);

    i4_ret = _test_page_rssi_text_create();
    RET_ON_ERR(i4_ret);

    i4_ret = _test_page_left_lvl_text_create();
    RET_ON_ERR(i4_ret);
#if 0
    i4_ret = _test_page_right_lvl_text_create();
    RET_ON_ERR(i4_ret);
#endif
    i4_ret = c_timer_create(&tg_rssi_view.h_signal_lvl_timer);
    RET_ON_ERR(i4_ret);

    i4_ret = _test_page_show_signal_lvl_show();
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_focus(tg_rssi_view.h_frame,WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(tg_rssi_view.h_frame,NULL,TRUE);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*----------------------------------------------------------------------------
* Name: test_page_iperf_frame_create
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _test_page_iperf_frame_create (VOID)
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    WGL_IMG_INFO_T    t_img_info;

    tg_iperf_view.h_canvas = tg_test_view.h_canvas;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     TEST_MENU_X,
                     TEST_MENU_Y,
                     TEST_MENU_WIDTH,
                     TEST_MENU_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_iperf_view.h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 NULL,
                                 &(tg_iperf_view),
                                 &(tg_iperf_view.h_frame));
    RET_ON_ERR(i4_ret);

    //get background img
    i4_ret = nav_img_create_revolt_misc_bk(&(tg_iperf_view.h_bk_img_tpl));
    RET_ON_ERR(i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = tg_iperf_view.h_bk_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = tg_iperf_view.h_bk_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = tg_iperf_view.h_bk_img_tpl;
    i4_ret = c_wgl_do_cmd(tg_iperf_view.h_frame,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_iperf_view.h_frame, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*----------------------------------------------------------------------------
* Name: _test_page_iperf_text_creat
* Description:
* Inputs:  -
* Outputs: -
* Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _test_page_iperf_text_create(VOID)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UTF16_T             w2s_tmp_str[128] = {0};
    const char *        s_str;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                      IPERF_LAUNCH_X,
                      IPERF_LAUNCH_Y,
                      IPERF_LAUNCH_WIDTH,
                      IPERF_LAUNCH_HEIGHT);
    s_str = "iPerf Launch";
    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));

    i4_ret = _test_page_text_create(&tg_iperf_view,
                                    &t_rect,
                                    28,
                                    w2s_tmp_str);

    RET_ON_ERR(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     IPERF_PORT_X,
                     IPERF_PORT_Y,
                     IPERF_PORT_WIDTH,
                     IPERF_PORT_HEIGHT);

    s_str = "(Port number: 8200. To Exit,reboot TV)";
    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));

    i4_ret = _test_page_text_create(&tg_iperf_view,
                                    &t_rect,
                                    24,
                                    w2s_tmp_str);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

 /*-----------------------------------------------------------------------------
  * Name:
  *      _test_page_iperf_view_create
  * Description:
  *      show UI.
  * Input arguments:
  *      None
  * Output arguments:
  *      None
  * Returns:
  *      NAVR_OK         Successful
  *      Others          Fail
  *---------------------------------------------------------------------------*/
static INT32 _test_page_iperf_view_create (VOID)
{
    INT32 i4_ret;

    i4_ret =  _test_page_iperf_frame_create();
    RET_ON_ERR(i4_ret);

    i4_ret = _test_page_iperf_text_create();
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(tg_iperf_view.h_frame,NULL,TRUE);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}
 /*----------------------------------------------------------------------------

 * Name: _test_page_menu_text_create
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _test_page_menu_text_create(VOID)
{

    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UTF16_T             w2s_tmp_str[128] = {0};
    const char *        s_str;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     MENU_TEXT_X,
                     MENU_TEXT_Y,
                     MENU_TEXT_WIDTH,
                     MENU_TEXT_HEIGHT);
    s_str = "TEST MENU";
    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));

    i4_ret = _test_page_text_create(&tg_test_view,
                                    &t_rect,
                                    32,
                                    w2s_tmp_str);
    RET_ON_ERR(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                    IPERF_TEXT_X,
                    IPERF_TEXT_Y,
                    IPERF_TEXT_WIDTH,
                    IPERF_TEXT_HEIGHT);

    s_str = "1.iPerf";
    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));

    i4_ret = _test_page_text_create(&tg_test_view,
                                    &t_rect,
                                    28,
                                    w2s_tmp_str);
    RET_ON_ERR(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                    RSSI_TEXT_X,
                    RSSI_TEXT_Y,
                    RSSI_TEXT_WIDTH,
                    RSSI_TEXT_HEIGHT);

    s_str = "2.RSSI";
    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));

    i4_ret = _test_page_text_create(&tg_test_view,
                                    &t_rect,
                                    28,
                                    w2s_tmp_str);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

 /*---------------------------------------------------------------------------
 * Name
 *      _test_page_menu_frame_nfy_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _test_page_menu_frame_nfy_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2
                    )
{
    INT32     i4_ret;
    UINT32    ui4_keycode = (UINT32)pv_param1;
    UTF16_T   w2s_tmp_str[128] = {0};
    const char *        s_str;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            switch (ui4_keycode)
            {
            case BTN_DIGIT_1:
                {
                    DBG_LOG_PRINT(("<_test_page_BTN_DIGIT_1>info:file=%s,line=%d\n\r",__FILE__,__LINE__));

                    i4_ret = _test_page_view_hide();
                    RET_ON_ERR(i4_ret);

                    s_str = "input iperf number within 3 sec";
                    c_uc_ps_to_w2s(s_str,w2s_tmp_str,c_strlen(s_str));
                    i4_ret = _test_page_string_toast_view(tg_test_view.h_canvas,w2s_tmp_str);
                    RET_ON_ERR(i4_ret);

                }
                break;
            case BTN_DIGIT_2:
                {
                    DBG_LOG_PRINT(("<_test_page_BTN_DIGIT_2>info:file=%s,line=%d\n\r",__FILE__,__LINE__));
                    i4_ret = _test_page_view_hide();
                    RET_ON_ERR(i4_ret);
                    i4_ret = _test_page_rssi_view_create();
                    RET_ON_ERR(i4_ret);
                }
                break;
            case BTN_EXIT:
               {
                    DBG_LOG_PRINT(("<_test_page_BTN_EXIT>info:file=%s,line=%d\n\r",__FILE__,__LINE__));

                    i4_ret = _test_page_view_hide();
                    RET_ON_ERR(i4_ret);
               }
               break;

            default:
                break;
            }
            break;
        }
        case WGL_MSG_KEY_UP:
            break;
        default:
            break;
    }
    //nav_rcu_key_handler(ui4_keycode);

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *     _test_page_menu_frame_create
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _test_page_menu_frame_create (VOID)
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    WGL_IMG_INFO_T    t_img_info;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     TEST_MENU_X,
                     TEST_MENU_Y,
                     TEST_MENU_WIDTH,
                     TEST_MENU_HEIGHT);

    i4_ret = c_wgl_create_widget(tg_test_view.h_canvas,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _test_page_menu_frame_nfy_fct,
                                 255,
                                 NULL,
                                 &(tg_test_view),
                                 &(tg_test_view.h_frame));
    RET_ON_ERR(i4_ret);

    //get background img
    i4_ret = nav_img_create_revolt_misc_bk(&(tg_test_view.h_bk_img_tpl));
    RET_ON_ERR(i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = tg_test_view.h_bk_img_tpl;
    t_img_info.u_img_data.t_standard.t_highlight = tg_test_view.h_bk_img_tpl;
    t_img_info.u_img_data.t_standard.t_disable   = tg_test_view.h_bk_img_tpl;
    i4_ret = c_wgl_do_cmd(tg_test_view.h_frame,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_visibility(tg_test_view.h_frame, WGL_SW_NORMAL);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      _test_page_view_hide
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
static INT32 _test_page_view_hide (VOID)
{
    INT32 i4_ret;

    i4_ret = c_wgl_show(tg_test_view.h_frame, WGL_SW_HIDE);
    RET_ON_ERR(i4_ret);
#if 0
    i4_ret = c_wgl_destroy_widget_ex(tg_test_view.h_frame, FALSE);
    RET_ON_ERR(i4_ret);
#endif
    return NAV_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *      test_page_view_create
 * Description:
 *      show UI.
 * Input arguments:
 *      None
 * Output arguments:
 *      None
 * Returns:
 *      NAVR_OK         Successful
 *      Others          Fail
 *---------------------------------------------------------------------------*/
 INT32 test_page_view_create (HANDLE_T    h_canvas)
{
    INT32 i4_ret;

    tg_test_view.h_canvas = h_canvas;

    i4_ret = _test_page_menu_frame_create();
    RET_ON_ERR(i4_ret);


    i4_ret = _test_page_menu_text_create();
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_repaint(tg_test_view.h_frame,NULL,TRUE);
    RET_ON_ERR(i4_ret);

    i4_ret = c_wgl_set_focus(tg_test_view.h_frame,WGL_NO_AUTO_REPAINT);
    RET_ON_ERR(i4_ret);

    i4_ret = c_timer_create(&h_timer_show);
    RET_ON_ERR(i4_ret);

    return NAV_OK;
}




