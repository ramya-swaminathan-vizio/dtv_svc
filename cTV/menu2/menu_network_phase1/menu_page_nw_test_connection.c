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
 * $RCSfile: menu_page_ip_setting.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>


#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "c_svctx.h"
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
#include "app_util/a_cfg.h"
#include "app_util/a_network.h"
#include "c_speedtest_async.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/config/acfg_custom.h"
/* show animation */
#include "menu2/menu_common/menu_page_animation.h"
#include "res/wdk/wdk_img.h"

#include "menu_network.h"
#include "menu2/menu_dbg.h"

//#define APP_MENU_NW_MANUAL_SETUP

#define COMMON_NW_TEST_TIMEOUT          (15000) /* the gethostbyname timout time.*/
#define COMMON_NW_TEST_ANIMATION_STEP   5


#define NW_TEST_INFO_TEXT_Y         (0)
#define NW_TEST_INFO_TEXT_H         (130*4/3)

#define NW_TEST_RETEST_Y            (NW_TEST_INFO_TEXT_Y + NW_TEST_INFO_TEXT_H)
#define NW_TEST_RETEST_H            (MENU_ITEM_V_HEIGHT)

#define NW_TEST_MANUAL_Y            (NW_TEST_RETEST_Y + NW_TEST_RETEST_H)
#define NW_TEST_MANUAL_H            (MENU_ITEM_V_HEIGHT)

#define NW_TEST_ANIMATION_IMG_MAX_NUM       (12)
#define NW_TEST_TIMEROUT                    (45)

static WGL_INSET_T t_status_inset_border = {
    FRAME_LEFT_RIGHT_INTV,
    0,
    8,
    0};

static WGL_INSET_T t_info_inset_border = {
    FRAME_LEFT_RIGHT_INTV,
    0,
    5,
    0};

typedef enum
{
    NW_TEST_CONNECT_TEST,
    NW_TEST_SPEED_TEST,
    NW_TEST_END
}NW_CONN_TEST_STATUS;
typedef struct __NW_NFY_DATA
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
}_NW_NFY_DATA;

typedef struct _PAGE_TEST_CONN_T
{
    HANDLE_T    h_cnt_frm;
    HANDLE_T    h_conn_info;
    HANDLE_T    h_signal_img;
    HANDLE_T    h_retest;
    HANDLE_T    h_manual;

    UINT32      ui4_nw_tag;
    UINT32      ui4_nw_nfy_id;

    BOOL        b_nw_is_connect;

    NW_CONN_TEST_STATUS     e_nw_test_status;
}PAGE_TEST_CONN_T;


/*data declaration*/
MENU_PAGE_FCT_TBL_T    t_g_menu_common_nw_test_connection;
PAGE_TEST_CONN_T       t_page_nw_test_conn;
static HANDLE_T        h_g_nw_test_img_icon;
static UINT8           ui1_g_img_idx = 0;
static HANDLE_T        h_timer;
static UINT8           ui1_timer_count = 0;
static UINT32          ui4_g_test_connection_tag = 0;
static UINT32          ui4_g_test_connection_nfy_id = 0;


/* function */
static INT32 _page_nw_test_test_finish_fail(VOID);
static INT32 _page_nw_test_test_finish_success(VOID);
static INT32 _page_nw_test_connection_info_clear(BOOL b_repaint);
static VOID _page_nw_test_SpeedtestNtyFct(INT32      i4Status,
                                                DOUBLE      u4Speed);
static VOID _page_nw_test_show_fail_test_speed(VOID*  pv_data,
                                                    SIZE_T  z_data_size);
static INT32 _page_nw_test_unknown_connection_show();
static VOID _nw_test_timer_cb_fct (HANDLE_T  pt_tm_handle,
                               VOID*     pv_tag);
static VOID _nw_test_img_animation_hide(BOOL     b_repaint);
static VOID _nw_test_img_animation_show(BOOL     b_repaint);

static WGL_HIMG_TPL_T       h_g_nw_test_img_animation[NW_TEST_ANIMATION_IMG_MAX_NUM];


#define COMMON_VER_INFO_ELEM_SIZE              (36) //(44)
#define COMMON_VER_INOF_ELEM_NUM               (21)

#define COMMON_VER_ARROW_WIDTH                 (20*4/3)
#define COMMON_VER_ARROW_HEIGHT                (9*4/3)

#define COMMON_VER_INFO_LB_X                   (0)
#define COMMON_VER_INFO_LB_Y                   (COMMON_VER_ARROW_HEIGHT)
#define COMMON_VER_INFO_LB_W                   MENU_ITEM_V_WIDE //(CONTENT_W - 15*4/3)
#define COMMON_VER_INFO_LB_H                   (COMMON_VER_INFO_ELEM_SIZE * COMMON_VER_INOF_ELEM_NUM)

#define COMMON_VER_INFO_INSET_L                (8*4/3)
#define COMMON_VER_INFO_INSET_R                (8*4/3)

#define COMMON_VER_INFO_LB_COL_W               (COMMON_VER_INFO_LB_W)
#define COMMON_VER_INFO_LB_ALIGN               (WGL_AS_LEFT_CENTER)

#define COMMON_VER_INFO_FONT_SIZE              FE_FNT_SIZE_SMALL


#define WEAKEST_SIGNAL_STRENGTH     -85
#define STRONGEST_SIGNAL_STRENGTH   -50
#define MAX_SIGNAL_STRENGTH(a,b)    ((a > b) ? a : b)

#define NET_INFO_REFRESH_TIMER  (10000)

#define NETWORK_SPEED_LEN       (16)

/*Jundi add for network information*/

typedef struct _PAGE_NET_INFO_CONN_T
{
    HANDLE_T    h_cnt_frm;
    HANDLE_T    h_lb_net_info;

    BOOL        b_this_page_show;

}PAGE_NET_INFO_CONN_T;


MENU_PAGE_FCT_TBL_T        t_g_menu_common_nw_info;
PAGE_NET_INFO_CONN_T       t_page_nw_info_conn;

typedef enum _NET_INFO_ROWNUM
{
    NET_INFO_ROW_SSID = 0,

    NET_INFO_ROW_WIFI_STRENGTH,
    NET_INFO_ROW_IP_TYPE,
    NET_INFO_ROW_IP_ADDR,
    NET_INFO_ROW_DEF_GATEWAY,
    NET_INFO_ROW_SUB_MASK,
    NET_INFO_ROW_IPV6_ADDR,
    NET_INFO_ROW_IPV6_DEF_GATEWAY,
    NET_INFO_ROW_IPV6_PREFIX_LENGTH,
    NET_INFO_ROW_PREF_DNS,
    NET_INFO_ROW_ALT_DNS,
#ifndef MT5583_MODEL
    NET_INFO_ROW_RJ45_MAC,
#else
    NET_INFO_ROW_ID_MAC,
#endif
    NET_INFO_ROW_WLAN_MAC,
    NET_INFO_ROW_CONNECTION_TYPE,
    NET_INFO_ROW_SECURITY_TYPE,
    NET_INFO_ROW_WIFI_MODE,
#if 0
    NET_INFO_ROW_DOWN_SPEED,
    NET_INFO_ROW_RSSI,
    NET_INFO_ROW_WIFI_CHANNEL,
#endif

    NET_INFO_ROW_LAST_NUM
}NET_INFO_ROWNUM;


typedef struct _NET_INFO_ITEM
{
     NET_INFO_ROWNUM   e_row_idx;
     UINT16  ui2_mlm_idx;
}NET_INFO_ITEM;

static NET_INFO_ITEM    t_g_net_info_items [NET_INFO_ROW_LAST_NUM] =
{
   { NET_INFO_ROW_SSID,               MLM_MENU_KEY_SYS_INFO_SSID},
   { NET_INFO_ROW_WIFI_STRENGTH,      MLM_MENU_KEY_SYS_INFO_WIFI_STRENGTH},
   { NET_INFO_ROW_IP_TYPE,            MLM_MENU_KEY_SYS_INFO_IP_TYPE},
   { NET_INFO_ROW_IP_ADDR,            MLM_MENU_KEY_SYS_INFO_IP_ADDR},
   { NET_INFO_ROW_DEF_GATEWAY,        MLM_MENU_KEY_SYS_INFO_DEF_GATEWAY},
   { NET_INFO_ROW_SUB_MASK,           MLM_MENU_KEY_SYS_INFO_SUB_MASK},
   { NET_INFO_ROW_IPV6_ADDR,          MLM_MENU_KEY_SYS_INFO_IPV6_ADDR},
   { NET_INFO_ROW_IPV6_DEF_GATEWAY,   MLM_MENU_KEY_SYS_INFO_IPV6_DEF_GATEWAY},
   { NET_INFO_ROW_IPV6_PREFIX_LENGTH, MLM_MENU_KEY_SYS_INFO_IPV6_PREFIX_LENGTH},
   { NET_INFO_ROW_PREF_DNS,           MLM_MENU_KEY_SYS_INFO_PREF_DNS},
   { NET_INFO_ROW_ALT_DNS,            MLM_MENU_KEY_SYS_INFO_ALT_DNS},
#ifndef MT5583_MODEL
   { NET_INFO_ROW_RJ45_MAC,           MLM_MENU_KEY_SYS_INFO_RJ45_MAC},
#else
   { NET_INFO_ROW_ID_MAC,             MLM_MENU_KEY_SYS_INFO_ID_MAC},
#endif
   { NET_INFO_ROW_WLAN_MAC,           MLM_MENU_KEY_SYS_INFO_WLAN_MAC},
   { NET_INFO_ROW_CONNECTION_TYPE,    MLM_MENU_KEY_SYS_INFO_CONNECTION_TYPE},
   { NET_INFO_ROW_SECURITY_TYPE,      MLM_MENU_KEY_SYS_INFO_SECURITY_TYPE},
   { NET_INFO_ROW_WIFI_MODE,          MLM_MENU_KEY_SYS_INFO_WIFI_MODE},
#if 0
   { NET_INFO_ROW_DOWN_SPEED,         MLM_MENU_KEY_SYS_INFO_DOWNLOAD_SPEED},
   { NET_INFO_ROW_RSSI,               MLM_MENU_KEY_SYS_INFO_RSSI},
   { NET_INFO_ROW_WIFI_CHANNEL,       MLM_MENU_KEY_SYS_INFO_WIFI_CHANNEL},
#endif
   { NET_INFO_ROW_LAST_NUM,           MLM_MENU_KEY_EMPTY}
};

static HANDLE_T     h_refresh_timer;
static UINT16       a_g_net_info_idx[NET_INFO_ROW_LAST_NUM+1] = {0};


/*----------------------------------------------------------------------------
 * Name: _page_nw_test_timeout
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
static VOID _page_nw_test_timeout(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    PAGE_TEST_CONN_T*  pt_page_data = &t_page_nw_test_conn;

    DBG_LOG_PRINT(("\n%s,%s,%d,e_nw_test_status=%d\n",
                __FILE__, __FUNCTION__, __LINE__, (UINT32)pt_page_data->e_nw_test_status));

    if (pt_page_data->e_nw_test_status == NW_TEST_CONNECT_TEST)
    {
        _page_nw_test_test_finish_fail();
    }
    else if (pt_page_data->e_nw_test_status == NW_TEST_SPEED_TEST)
    {
        _nw_test_img_animation_hide(TRUE);

        c_speedtest_cancel();
        _page_nw_test_show_fail_test_speed(NULL,0);
    }
}

/*----------------------------------------------------------------------------
 * Name: _page_nw_test_show_error_code
 *
 * Description: show the error code of test connection
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_nw_test_show_error_code(BOOL b_success)
{
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;
    INT32               i4_ret = 0;
    UTF16_T             w2s_data[32] = {0};
    CHAR                s_data[32] = {0};

    c_memset(w2s_data, 0, 32 * sizeof(UTF16_T));
    c_memset(s_data, 0, 32);

    if (b_success)
    {
        i4_ret = c_wgl_do_cmd(t_page_nw_test_conn.h_conn_info,
                      WGL_CMD_TEXT_APPEND_TEXT,
                      WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_INTERNET)),
                      WGL_PACK(c_uc_w2s_strlen(
                      MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_INTERNET))));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(t_page_nw_test_conn.h_conn_info,
                      WGL_CMD_TEXT_APPEND_TEXT,
                      WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_WIR_CON)),
                      WGL_PACK(c_uc_w2s_strlen(
                      MENU_TEXT(MLM_MENU_KEY_NET_WIR_CON))));
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_do_cmd(t_page_nw_test_conn.h_conn_info,
                      WGL_CMD_TEXT_APPEND_TEXT,
                      WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_INTERNET)),
                      WGL_PACK(c_uc_w2s_strlen(
                      MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_INTERNET))));
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(t_page_nw_test_conn.h_conn_info,
                      WGL_CMD_TEXT_APPEND_TEXT,
                      WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_WIR_DISCON)),
                      WGL_PACK(c_uc_w2s_strlen(
                      MENU_TEXT(MLM_MENU_KEY_NET_WIR_DISCON))));
        MENU_LOG_ON_FAIL(i4_ret);
    }

    c_wgl_repaint(t_page_nw_test_conn.h_conn_info, NULL, TRUE);
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_nw_test_show_speed_success
 *
 * Description: when get download speed, show these info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _page_nw_test_show_success_test_speed(VOID*  pv_data,
                                                            SIZE_T  z_data_size)
{
    INT32      i4_ret = MENUR_OK;
    DOUBLE     *p_u4Speed = (DOUBLE*)pv_data;
    /*kbit/s, middleware return data is bytes/s, so need data*8/1024 */
    INT32    i4_speed = (INT32)(*p_u4Speed/128);
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;

    DBG_LOG_PRINT(("\n%s,%s,%d,speed=%f,i4_speed=%d\n",__FILE__, __FUNCTION__, __LINE__, *p_u4Speed, i4_speed));

    t_page_nw_test_conn.e_nw_test_status = NW_TEST_END;

    _nw_test_img_animation_hide(TRUE);
    _page_nw_test_show_error_code(TRUE);
}

/*----------------------------------------------------------------------------
 * Name: _page_nw_test_show_fail_test_speed
 *
 * Description: when fail to get download speed, show fail info
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _page_nw_test_show_fail_test_speed(VOID*  pv_data,
                                                    SIZE_T  z_data_size)
{
    INT32   i4_ret = MENUR_OK;

    t_page_nw_test_conn.e_nw_test_status = NW_TEST_END;
    _nw_test_img_animation_hide(TRUE);
    _page_nw_test_show_error_code(FALSE);

}

/*----------------------------------------------------------------------------
 * Name: _page_nw_test_SpeedtestNtyFct
 *
 * Description: when the test process is end or time was expired,this function will be call
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _page_nw_test_SpeedtestNtyFct(
                INT32               i4Status,
                DOUBLE              u4Speed)
{
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;

    DBG_LOG_PRINT(("%s,%s,%d,e_nw_test_status=%d,i4Status=%d,u4Speed=%f\n",
                __FILE__, __FUNCTION__, __LINE__,
                (UINT32)pt_page_data->e_nw_test_status, i4Status, u4Speed));
    /* store speed value */
    nw_custom_set_speed(u4Speed);

    /* test connection speed timeout*/
    if (pt_page_data->e_nw_test_status != NW_TEST_SPEED_TEST)
    {
        return;
    }

    /* speed test is finished */
    pt_page_data->e_nw_test_status = NW_TEST_END;

    if (i4Status == 0)
    {
        /* speed test is success */
        menu_async_invoke(_page_nw_test_show_success_test_speed, &u4Speed, sizeof(DOUBLE), TRUE);
    }
    else
    {
        /* speed test is failed */
        menu_async_invoke(_page_nw_test_show_fail_test_speed, NULL, 0,TRUE);
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _page_nw_test_test_finish_fail
 *
 * Description: when the test process is end or time was expired,this function will be call
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_nw_test_test_finish_fail(VOID)
{
    INT32    i4_ret = MENUR_OK;
    PAGE_TEST_CONN_T*  pt_page_data = &t_page_nw_test_conn;

    pt_page_data->e_nw_test_status = NW_TEST_END;

    DBG_LOG_PRINT(("\n%s,%s,%d,e_nw_test_status=%d\n",
                __FILE__, __FUNCTION__, __LINE__, (UINT32)pt_page_data->e_nw_test_status));

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO_DISCONNECTED)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO_DISCONNECTED))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_APPEND_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL_NA)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL_NA))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_signal_img,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_repaint(pt_page_data->h_conn_info, NULL, TRUE);

    _page_nw_test_show_fail_test_speed(NULL,0);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_test_finish_success
 *
 * Description: when the test process is end or time was expired,this function will be call
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_nw_test_test_finish_success(VOID)
{
    INT32    i4_ret = MENUR_OK;
    PAGE_TEST_CONN_T*  pt_page_data = &t_page_nw_test_conn;
    UTF16_T     w2s_data[20];

    pt_page_data->e_nw_test_status = NW_TEST_SPEED_TEST;

    DBG_LOG_PRINT(("%s,%s,%d,e_nw_test_status=%d\n", __FILE__, __FUNCTION__, __LINE__, (UINT32)pt_page_data->e_nw_test_status));

    i4_ret= c_speedtest(NULL, _page_nw_test_SpeedtestNtyFct);
    if (i4_ret != 0)
    {
        _nw_test_img_animation_hide(TRUE);

        pt_page_data->e_nw_test_status = NW_TEST_END;

         c_speedtest_cancel();

        _page_nw_test_show_fail_test_speed(NULL,0);

        DBG_LOG_PRINT(("%s,%s,%d,e_nw_test_status=%d,i4_ret=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    (UINT32)pt_page_data->e_nw_test_status, i4_ret));
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_nw_notify_handler
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
static VOID _page_nw_test_nw_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    _NW_NFY_DATA* pt_nw_nfy_data = (_NW_NFY_DATA*)pv_data;

    PAGE_TEST_CONN_T*  pt_page_data = &t_page_nw_test_conn;

    switch(pt_nw_nfy_data->e_nfy_id)
    {
    case NW_NFY_ID_ETHERNET_UNPLUG:
    case NW_NFY_ID_ETHERNET_PLUGIN:
        menu_nav_go_home_menu();
        return;
    case NW_NFY_ID_WIRLESS_PLUGIN:
        return;
    case NW_NFY_ID_WIRLESS_UNPLUG:
        return;
    case NW_NFY_ID_DHCP_STOPPED:
    case NW_NFY_ID_NETWORK_CONN_DISABLED:
        pt_page_data->b_nw_is_connect= FALSE;
        pt_page_data->e_nw_test_status = NW_TEST_END;
        _page_nw_test_test_finish_fail();
        break;

    case NW_NFY_ID_INTERN_CT_RESULT:
    {
        DBG_LOG_PRINT(("\n%s,%s,%d,e_nw_test_status=%d,b_nw_is_connect=%d\n",
                    __FILE__, __FUNCTION__, __LINE__,
                    (UINT32)pt_page_data->e_nw_test_status,
                    (UINT32)(pt_nw_nfy_data->pv_nfy_param)));

        if (pt_page_data->e_nw_test_status != NW_TEST_CONNECT_TEST)
        {
            return ;
        }

        pt_page_data->b_nw_is_connect = (BOOL)(UINT32)(pt_nw_nfy_data->pv_nfy_param);

        if (pt_page_data->b_nw_is_connect &&
            menu_network_is_NTP_available())
        {
            pt_page_data->e_nw_test_status = NW_TEST_SPEED_TEST;
            _page_nw_test_test_finish_success();
        }
        else
        {
            pt_page_data->e_nw_test_status = NW_TEST_END;
            _page_nw_test_test_finish_fail();
        }

        break;
    }
    default:
        return;
    }
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_nw_notify_callback
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
static VOID _page_nw_test_nw_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    _NW_NFY_DATA t_nw_nfy_data;

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    menu_async_invoke(_page_nw_test_nw_notify_handler, &t_nw_nfy_data,sizeof(_NW_NFY_DATA),TRUE);
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_ethernet_connection
 *
 * Description:show connection info, ethernet
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  _page_nw_test_ethernet_connection_show(VOID)
{
    INT32   i4_ret;
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                  WGL_CMD_TEXT_SET_TEXT,
                  WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO_ETHERNET)),
                  WGL_PACK(c_uc_w2s_strlen(
                  MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO_ETHERNET))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_APPEND_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL_NA)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL_NA))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_signal_img,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_repaint(pt_page_data->h_conn_info, NULL, TRUE);
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _page_nw_test_wireless_connection_fail
 *
 * Description:fail to connection via wireless
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_nw_test_wireless_connection_fail(VOID)
{
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;
    INT32               i4_ret;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO_DISCONNECTED)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO_DISCONNECTED))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_APPEND_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL_NA)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL_NA))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_signal_img,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    _page_nw_test_show_error_code(FALSE);

    i4_ret = c_wgl_repaint(pt_page_data->h_conn_info,
                           NULL,
                           TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_wireless_connection
 *
 * Description:show conneciont info, wireless
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32  _page_nw_test_wireless_connection_show(VOID)
{
    INT32   i4_ret;
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;
    NET_802_11_BSS_INFO_T t_CurrBss;
    UTF16_T             w2s_data[32+1] = {0};
    CHAR                s_data[32+1] = {0};
    INT32               i4_len = 0;
    WGL_HIMG_TPL_T*     ph_signal_level_img;
    INT16               i2_new_level = 0;

    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));

    i4_ret = a_nw_wlan_get_curr_bss(&t_CurrBss);

    if (0 == t_CurrBss.i2_Level)
    {
        t_CurrBss.i2_Level = a_nw_get_wlan_signal_lvl_from_rssi();
    }

    DBG_LOG_PRINT(("\n%s,%s,%d,i4_ret=%d,ui1_aSsid=%s,ui4_SsidLen=%d,u8_wpa_status=%d, t_CurrBss.i2_Level=%d\n",
                __FILE__, __FUNCTION__, __LINE__, i4_ret,
                t_CurrBss.t_Ssid.ui1_aSsid, t_CurrBss.t_Ssid.ui4_SsidLen,
                t_CurrBss.u8_wpa_status,t_CurrBss.i2_Level));
    if(i4_ret != NWR_OK)
    {
        c_memset(t_CurrBss.t_Bssid, 0, sizeof(t_CurrBss.t_Bssid));
        t_CurrBss.t_Ssid.ui4_SsidLen = 0;
        _page_nw_test_wireless_connection_fail();
        return NWR_FAIL;
    }
    else if ((0 == t_CurrBss.t_Ssid.ui4_SsidLen)
              ||((UINT8)WLAN_WPA_COMPLETED != t_CurrBss.u8_wpa_status))
    {
        _page_nw_test_unknown_connection_show();
        return MENUR_OK;
    }

    c_memset(w2s_data, 0, 32 * sizeof(UTF16_T));
    c_memset(s_data, 0, 32);

    c_strncat(s_data, t_CurrBss.t_Ssid.ui1_aSsid, 32);
    i4_len = c_strlen(s_data);
    if (i4_len > 16)
    {
        s_data[13] = '.';
        s_data[14] = '.';
        s_data[15] = '.';
        s_data[16] = '\0';
        i4_len = 16;
    }

    c_uc_ps_to_w2s(s_data, w2s_data, i4_len);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_APPEND_TEXT,
                          WGL_PACK(w2s_data),
                          WGL_PACK(c_uc_w2s_strlen(w2s_data)));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_APPEND_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL))));
    MENU_LOG_ON_FAIL(i4_ret);

    i2_new_level = a_nw_custom_wifi_signal_remapping(t_CurrBss.i2_Level);

    if((UINT16)i2_new_level > 80)
    {
        ph_signal_level_img = &h_g_wifi_signal_4_v2;
    }
    else if ((UINT16)i2_new_level > 60)
    {
        ph_signal_level_img = &h_g_wifi_signal_3_v2;
    }
    else if ((UINT16)i2_new_level > 40)
    {
        ph_signal_level_img = &h_g_wifi_signal_2_v2;
    }
    else if ((UINT16)i2_new_level > 20)
    {
        ph_signal_level_img = &h_g_wifi_signal_1_v2;
    }
    else
    {
        ph_signal_level_img = &h_g_wifi_signal_half_v2;
    }

    WGL_IMG_INFO_T    t_img_info;
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = *ph_signal_level_img;
    t_img_info.u_img_data.t_standard.t_enable = *ph_signal_level_img;
    t_img_info.u_img_data.t_standard.t_highlight = *ph_signal_level_img;
    i4_ret = c_wgl_do_cmd(pt_page_data->h_signal_img,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_visibility(pt_page_data->h_signal_img,
                         WGL_SW_NORMAL);
    c_wgl_repaint(pt_page_data->h_conn_info, NULL, TRUE);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_unknown_connection_show
 *
 * Description:show connection info, unknown
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_nw_test_unknown_connection_show()
{
    INT32   i4_ret;
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                  WGL_CMD_TEXT_SET_TEXT,
                  WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO_DISCONNECTED)),
                  WGL_PACK(c_uc_w2s_strlen(
                  MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_TO_DISCONNECTED))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_APPEND_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL_NA)),
                          WGL_PACK(c_uc_w2s_strlen(
                          MENU_TEXT(MLM_MENU_KEY_NET_TEST_CONN_SIGNAL_NA))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_signal_img,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    _page_nw_test_show_error_code(FALSE);

    c_wgl_repaint(pt_page_data->h_conn_info, NULL, TRUE);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nw_test_img_animation_hide
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
static VOID _nw_test_img_animation_hide(BOOL     b_repaint)
{
    c_wgl_set_visibility(h_g_nw_test_img_icon, WGL_SW_HIDE);

    if (b_repaint)
    {
        c_wgl_repaint( h_g_nw_test_img_icon, NULL, TRUE);
    }
}
/*----------------------------------------------------------------------------
 * Name: _nw_test_img_animation_show
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
static VOID _nw_test_img_animation_show(BOOL     b_repaint)
{
    c_wgl_set_visibility(h_g_nw_test_img_icon, WGL_SW_NORMAL);

    if (b_repaint)
    {
        c_wgl_repaint( h_g_nw_test_img_icon, NULL, TRUE);
    }
}

static VOID _do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    INT32             i4_ret;
    WGL_IMG_INFO_T    t_img_info;

    if (t_page_nw_test_conn.e_nw_test_status == NW_TEST_END)
    {
        return ;
    }

    if (ui1_timer_count > NW_TEST_TIMEROUT)
    {
        _page_nw_test_timeout(NULL, 0);

    }
    else
    {
        ui1_g_img_idx += 1;
        if (ui1_g_img_idx > (NW_TEST_ANIMATION_IMG_MAX_NUM - 1))
        {
            ui1_g_img_idx = 0;
        }

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_disable = h_g_nw_test_img_animation[ui1_g_img_idx];
        t_img_info.u_img_data.t_standard.t_enable = h_g_nw_test_img_animation[ui1_g_img_idx];
        t_img_info.u_img_data.t_standard.t_highlight = h_g_nw_test_img_animation[ui1_g_img_idx];

        i4_ret = c_wgl_do_cmd(h_g_nw_test_img_icon,
                             WGL_CMD_GL_SET_IMAGE,
                             WGL_PACK(WGL_IMG_FG),
                             WGL_PACK(&t_img_info));
        MENU_LOG_ON_FAIL(i4_ret);
        c_timer_start(h_timer, 1000, X_TIMER_FLAG_ONCE, _nw_test_timer_cb_fct, NULL);
        _nw_test_img_animation_show(TRUE);
        ui1_timer_count += 1;
    }

}
static VOID _nw_test_timer_cb_fct (HANDLE_T  pt_tm_handle,
                               VOID*     pv_tag)
{
    menu_async_invoke(_do_timer_nfy, NULL, 0, TRUE);
}

static VOID _test_connection_notify_handler(VOID* pv_data, SIZE_T  z_data_size)
{
    _NW_NFY_DATA* pt_nw_nfy_data = (_NW_NFY_DATA*)pv_data;
    PAGE_TEST_CONN_T*  pt_page_data = &t_page_nw_test_conn;

    DBG_LOG_PRINT(("\n<MENU NW>%s,%s,%d,ui4_g_test_connection_tag=%d,pv_tag=%d"
                "e_nw_test_status=%d,b_nw_is_connect=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                ui4_g_test_connection_tag, pt_nw_nfy_data->pv_tag,
                (UINT32)pt_page_data->e_nw_test_status,
                (UINT32)pt_nw_nfy_data->pv_nfy_param));

    if ((UINT32)pt_nw_nfy_data->pv_tag == ui4_g_test_connection_tag)
    {
        switch(pt_nw_nfy_data->e_nfy_id)
        {
            case NW_NFY_ID_INTERN_CT_RESULT_ASYNC:
            {
                if (pt_page_data->e_nw_test_status != NW_TEST_CONNECT_TEST)
                {
                    return ;
                }

                pt_page_data->b_nw_is_connect = (BOOL)(UINT32)(pt_nw_nfy_data->pv_nfy_param);

                if (pt_page_data->b_nw_is_connect &&
                    menu_network_is_NTP_available())
                {
                    pt_page_data->e_nw_test_status = NW_TEST_SPEED_TEST;
                    _page_nw_test_test_finish_success();
                }
                else
                {
                    pt_page_data->e_nw_test_status = NW_TEST_END;
                    _page_nw_test_test_finish_fail();
                }
            }
                break;
            default:
                return;
        }
    }
}

static VOID _test_connection_notify_callback(VOID* pv_tag, NW_NFY_ID_T e_nfy_id, VOID* pv_nfy_param)
{
    _NW_NFY_DATA t_nw_nfy_data;
    INT32 i4_ret = MENUR_OK;

    t_nw_nfy_data.pv_tag = pv_tag;
    t_nw_nfy_data.e_nfy_id = e_nfy_id;
    t_nw_nfy_data.pv_nfy_param = pv_nfy_param;

    i4_ret = menu_async_invoke(_test_connection_notify_handler,
                               &t_nw_nfy_data, sizeof(_NW_NFY_DATA), TRUE);
     MENU_LOG_ON_FAIL(i4_ret);
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
static INT32 _page_nw_test_test_connection()
{
    INT32               i4_ret;
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;
    NW_DHCP_STATE_T     e_dhcp_state;
    UINT8               ui1_interface;
    WGL_IMG_INFO_T      t_img_info;

    pt_page_data->e_nw_test_status = NW_TEST_CONNECT_TEST;

    ui1_timer_count = 0;
    /* clean the connection info */
    i4_ret = _page_nw_test_connection_info_clear(TRUE);
    MENU_LOG_ON_FAIL(i4_ret);

    ui1_g_img_idx += 1;
    if (ui1_g_img_idx > (NW_TEST_ANIMATION_IMG_MAX_NUM - 1))
    {
        ui1_g_img_idx = 0;
    }

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable = h_g_nw_test_img_animation[ui1_g_img_idx];
    t_img_info.u_img_data.t_standard.t_enable = h_g_nw_test_img_animation[ui1_g_img_idx];
    t_img_info.u_img_data.t_standard.t_highlight = h_g_nw_test_img_animation[ui1_g_img_idx];

    i4_ret = c_wgl_do_cmd(h_g_nw_test_img_icon,
                         WGL_CMD_GL_SET_IMAGE,
                         WGL_PACK(WGL_IMG_FG),
                         WGL_PACK(&t_img_info));
    MENU_LOG_ON_FAIL(i4_ret);

    _nw_test_img_animation_show(TRUE);

    c_timer_start(h_timer, 1000, X_TIMER_FLAG_ONCE, _nw_test_timer_cb_fct, NULL);
    ui1_timer_count += 1 ;

    i4_ret = nw_custom_get_network_interface(&ui1_interface);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui1_interface == NW_NET_INTERFACE_ETH0)
    {
        /*show ethernet connection info*/
        i4_ret = _page_nw_test_ethernet_connection_show();
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else if (ui1_interface == NW_NET_INTERFACE_WIFI)
    {
        NET_802_11_SSID_T       t_Ssid;

        c_memset (&t_Ssid, 0, sizeof(t_Ssid));

        i4_ret = a_nw_get_wlan_ssid(&t_Ssid);
        MENU_LOG_ON_FAIL(i4_ret);
        if (t_Ssid.ui4_SsidLen > 0)
        {
            /*show wireless conneciont info*/
            i4_ret = _page_nw_test_wireless_connection_show();
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i4_ret = _page_nw_test_test_finish_fail();
            MENU_LOG_ON_FAIL(i4_ret);

            return MENUR_OK;
        }
    }
    else
    {
        /*show unknown connection info*/
        i4_ret = _page_nw_test_unknown_connection_show();
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /*get the dhcp status, if current dhcp is "on" and not get ip addr, should return test fail*/
    i4_ret = a_nw_get_dhcp_status(&e_dhcp_state);
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_LOG_PRINT(("\n%s,%s,%d,ui1_interface=%d,e_dhcp_state=%d,i4_ret=%d\n",
                __FILE__, __FUNCTION__, __LINE__,
                ui1_interface, e_dhcp_state, i4_ret));

    if ((e_dhcp_state != NW_DHCP_STOPPED) && (e_dhcp_state != NW_DHCP_STARTED))
    {
        i4_ret = _page_nw_test_test_finish_fail();
        MENU_LOG_ON_FAIL(i4_ret);

        return MENUR_OK;
    }

    i4_ret = a_nw_connection_test((CHAR*)"www.google.com");
    MENU_LOG_ON_FAIL(i4_ret);
    if (i4_ret != MENUR_OK)
    {
        _nw_test_img_animation_hide(TRUE);

        i4_ret = _page_nw_test_test_finish_fail();
        MENU_LOG_ON_FAIL(i4_ret);

        return MENUR_OK;
    }

    if (ui4_g_test_connection_nfy_id > 0)
    {
        i4_ret = a_nw_unregister(ui4_g_test_connection_nfy_id);
        MENU_LOG_ON_FAIL(i4_ret);
        ui4_g_test_connection_nfy_id = 0;
    }

    ui4_g_test_connection_tag++;
    i4_ret = a_nw_register(_test_connection_notify_callback,
                           (VOID*)ui4_g_test_connection_tag, &ui4_g_test_connection_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

    /* disable the menu timer */
    menu_timer_enable(FALSE);
    menu_timer_stop();

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
    PAGE_TEST_CONN_T*    pt_this = &t_page_nw_test_conn;

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
            menu_netowrk_nav_back ();
            return MENUR_OK ;

        case BTN_CURSOR_RIGHT :
        case BTN_CURSOR_DOWN:
            c_wgl_set_focus (pt_this->h_retest, WGL_SYNC_AUTO_REPAINT);
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
            menu_nav_go_home_menu();
            return MENUR_OK ;

        case BTN_RETURN:
            menu_netowrk_nav_back ();
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
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_connection_text_withbk_proc_fct
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
static INT32 _page_nw_test_connection_text_withbk_proc_fct(
                            HANDLE_T    h_widget,
                            UINT32      ui4_msg,
                            VOID*       param1,
                            VOID*       param2)
{
    PAGE_TEST_CONN_T*    pt_this = &t_page_nw_test_conn;
    INT32    i4_ret;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        if(h_widget == pt_this->h_manual)
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_NETWORK_SET));

        #ifdef APP_TTS_SUPPORT
            a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_NETWORK_SET), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_NETWORK_SET)));
        #endif
        }
        else if (h_widget == pt_this->h_retest)
        {
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_NET_CFG_CONN_RETEST_HELP));

        #ifdef APP_TTS_SUPPORT
            a_app_tts_play(MENU_TTS_TEXT(MLM_MENU_KEY_NET_CFG_CONN_RETEST), c_uc_w2s_strlen(MENU_TTS_TEXT(MLM_MENU_KEY_NET_CFG_CONN_RETEST)));
        #endif
        }
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
        case BTN_SELECT:
            if(h_widget == pt_this->h_manual)
            {
                i4_ret = menu_netowrk_nav_go(NW_PAGE_ID_MAN_SET, NULL);
                MENU_LOG_ON_FAIL(i4_ret);
            }
            else if (h_widget == pt_this->h_retest)
            {
                if (NW_TEST_END == pt_this->e_nw_test_status)
                {
                    _page_nw_test_test_connection();
                }
            }
            return MENUR_OK;
        case BTN_CURSOR_UP:
            if(h_widget == pt_this->h_manual)
            {
                c_wgl_set_focus(pt_this->h_retest, WGL_SYNC_AUTO_REPAINT);
            }
            else
            {
                MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(TRUE));
            }
            return MENUR_OK;
        case BTN_CURSOR_DOWN:

        #ifdef APP_MENU_NW_MANUAL_SETUP
            if(h_widget == pt_this->h_manual)
            {
                i4_ret = menu_help_tip_keytip_set_focus(pt_this->h_manual,0,TRUE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_pm_repaint();
            }
            else
            {
                c_wgl_set_focus(pt_this->h_manual, WGL_SYNC_AUTO_REPAINT);
            }
        #else
            i4_ret = menu_help_tip_keytip_set_focus(h_widget, 0, TRUE);
            MENU_LOG_ON_FAIL(i4_ret);
            menu_pm_repaint();
        #endif
            return MENUR_OK;
        case BTN_RETURN:
            menu_netowrk_nav_back();
            return MENUR_OK;
        default:
            break;
        }
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_connection_cnt_frm_proc_fct
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
static INT32 _page_nw_test_connection_cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
        }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_connection_text_withbk_create
 *
 * Description:create TEXT widgets with Bakground
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_nw_test_connection_text_withbk_create(HANDLE_T h_parent,
                                                        GL_RECT_T*          pt_rect,
                                                        HANDLE_T*           ph_nw_test)
{
    INT32               i4_ret;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_BDR_TIMG_TITLE_INFO_T   t_title_info;
    UINT8               ui1_frame_alpha;
    UINT32              ui4_style;
    WGL_INSET_T         t_inset;
    GL_RECT_T           t_fm_border_title = {
                    FRAME_LEFT_RIGHT_INTV,
                    0,
                    MENU_ITEM_BAR_CNT_INSET_L + MENU_ITEM_ICON_W + MENU_ITEM_TITLE_W,
                    MENU_ITEM_V_HEIGHT};

    i4_ret =    menu_get_osd_alpha(&ui1_frame_alpha);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_style = WGL_STL_GL_BDR_FILL_CNT_BK
                | WGL_STL_TEXT_MAX_128;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_TIMG,//WGL_BORDER_NULL,
                                 pt_rect,
                                 _page_nw_test_connection_text_withbk_proc_fct,
                                 ui1_frame_alpha,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_nw_test);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = FRAME_LEFT_RIGHT_INTV;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_GL_SET_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Border Title */
    c_memset(&t_title_info, 0, sizeof(WGL_BDR_TIMG_TITLE_INFO_T));
    t_title_info.ui2_style = WGL_BDR_TIMG_TITLE_STL_TRANSP_BK;
    c_strncpy(t_title_info.t_font.a_c_font_name, menu_font_name(), WGL_MAX_FONT_NAME);
    t_title_info.t_font.e_font_size  = MENU_ITEM_FNT_SIZE;
    t_title_info.t_font.e_font_style = MENU_ITEM_FNT_STYLE;
    t_title_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_title_info.t_rc_ref = t_fm_border_title;
    t_title_info.ui1_align = WGL_AS_LEFT_CENTER;
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_BDR_TIMG_SET_TITLE_INFO,
                          &t_title_info,
                          NULL);

    /* Set Border colors and images */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable     =t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight  =t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_disable    =t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_GL_SET_BDR_COLOR,
                          WGL_PACK(WGL_CLR_BDR_TIMG_TITLE_TEXT),
                          WGL_PACK(&t_clr_info));
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_img_item_bk;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_BDR_TIMG_SET_BK_IMG,
                          WGL_PACK(&t_img_info),
                          WGL_PACK(NULL));
    MENU_LOG_ON_FAIL(i4_ret);


    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_RIGHT_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL, WGL_MAX_FONT_NAME); //paulfan,100209 Font Size
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE; //paulfan,100209 Font Size
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_nw_test,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_white;
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

     /* Set Cnt Insets */
     t_inset.i4_left     = FRAME_LEFT_RIGHT_INTV;//_EB_INPUT_CNT_INSET_L;
     t_inset.i4_right    = 0;//EB_INPUT_CNT_INSET_L;
     t_inset.i4_top      = 0;//EB_INPUT_CNT_INSET_L;
     t_inset.i4_bottom   = 0;//EB_INPUT_CNT_INSET_L;
     i4_ret = c_wgl_do_cmd(*ph_nw_test,
                           WGL_CMD_TEXT_SET_CNT_INSET,
                           &t_inset,
                           NULL);
     MENU_LOG_ON_FAIL(i4_ret);


    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_connection_text_nobk_create
 *
 * Description: create TEXT widgets without Bakground
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _page_nw_test_connection_text_nobk_create(HANDLE_T h_parent,
                                                        GL_RECT_T*      pt_rect,
                                                        FE_FNT_STYLE    e_font_style,
                                                        WGL_INSET_T*    pt_inset,
                                                        UINT32          ui4_line_gap,
                                                        HANDLE_T*       ph_nw_test)
{
     INT32               i4_ret;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    UINT8               ui1_frame_alpha;
    UINT32              ui4_style;

    i4_ret =    menu_get_osd_alpha(&ui1_frame_alpha);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_style = WGL_STL_GL_NO_IMG_UI
                | WGL_STL_TEXT_MAX_128
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL, //WGL_BORDER_TIMG,
                                 pt_rect,
                                 NULL,
                                 ui1_frame_alpha,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_nw_test);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

     /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_TOP),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strncpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL, WGL_MAX_FONT_NAME);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = e_font_style;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_nw_test,
                            WGL_CMD_GL_SET_FONT,
                            WGL_PACK(&t_fnt_info),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_menu_color_white;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_menu_color_bk2_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                           WGL_CMD_GL_SET_COLOR,
                           WGL_PACK(WGL_CLR_TEXT),
                           WGL_PACK(&t_clr_info ));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Insets */
    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_GL_SET_INSET,
                          pt_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_nw_test,
                          WGL_CMD_TEXT_SET_LINE_GAP,
                          WGL_PACK(ui4_line_gap),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_connection_signal_img_create
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
static INT32 _page_nw_test_connection_signal_img_create(HANDLE_T h_parent,
                                                        HANDLE_T* ph_signal_img)
{
    INT32   i4_ret;
    GL_RECT_T           t_rect;
    UINT8               ui1_frame_alpha;
    UINT32              ui4_style;

    i4_ret =    menu_get_osd_alpha(&ui1_frame_alpha);
    MENU_LOG_ON_FAIL(i4_ret);

    ui4_style = WGL_STL_GL_NO_BK;

    /*
    fuck the rubbish code,
    the screen resolution has been changed from 960*540 to 1280*720,
    so the widget size has been enlarged by ratio,
    but the string's font size is the same as before.
    and the signal icon is set in the relative position.
    so fuck it so much hard code and hard code.
    */
    SET_RECT_BY_SIZE(&t_rect,
                     190,
                     25,
                     40*4/3,
                     20*4/3);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 ui1_frame_alpha,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_signal_img);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_signal_img,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(*ph_signal_img,
                                 WGL_SW_HIDE);
    return MENUR_OK;
}

static INT32 _nw_test_page_animation_icon_create(VOID)
{
    INT32   i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;

    ui4_style = WGL_STL_GL_NO_BK;

    SET_RECT_BY_SIZE(&t_rect,
                 MENU_ITEM_V_INSET_L + (220+25)*4/3,
                 MENU_ITEM_V_HEIGHT,
                 ICON_ANIMATION_W,
                 ICON_ANIMATION_H);

    i4_ret = c_wgl_create_widget(t_page_nw_test_conn.h_cnt_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_g_nw_test_img_icon);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_g_nw_test_img_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_g_nw_test_img_icon,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_nw_test_connection_info_clear
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
static INT32 _page_nw_test_connection_info_clear(BOOL b_repaint)
{
    INT32   i4_ret;
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_conn_info,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_EMPTY)),
                          WGL_PACK(c_uc_w2s_strlen(
                            MENU_TEXT(MLM_MENU_KEY_EMPTY))));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_signal_img,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_repaint)
    {
        c_wgl_repaint(pt_page_data->h_cnt_frm, NULL, TRUE);
    }

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_connection_chg_lang
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

static INT32 _page_nw_test_connection_chg_lang(VOID)
{
    INT32   i4_ret = MENUR_OK;

    PAGE_TEST_CONN_T* pt_page_data = &t_page_nw_test_conn;

    i4_ret = c_wgl_do_cmd(pt_page_data->h_retest,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NET_CFG_CONN_RETEST)),
                          WGL_PACK(c_uc_w2s_strlen(
                            MENU_TEXT(MLM_MENU_KEY_NET_CFG_CONN_RETEST))));
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_NW_MANUAL_SETUP
    i4_ret = c_wgl_do_cmd(pt_page_data->h_manual,
                          WGL_CMD_BDR_TIMG_SET_TITLE_TEXT,
                          WGL_PACK(MENU_TEXT(MLM_MENU_KEY_NETWORK_SET)),
                          WGL_PACK(c_uc_w2s_strlen(
                            MENU_TEXT(MLM_MENU_KEY_NETWORK_SET))));
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = menu_main_set_title(MLM_MENU_KEY_NET_CFG_CONN_TEST);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_BACK_HELP_TIP));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _page_nw_test_start_test_connection
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
static VOID _page_nw_test_start_test_connection(VOID* pv_data,
                                            SIZE_T  z_data_size)
{
    _page_nw_test_test_connection();
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
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;
    GL_RECT_T           t_rect;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    c_memset(pt_page_data, 0, sizeof(PAGE_TEST_CONN_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &(pt_page_data->h_cnt_frm));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     NW_TEST_INFO_TEXT_Y,
                     MENU_ITEM_V_WIDE,
                     NW_TEST_INFO_TEXT_H);

    i4_ret = _page_nw_test_connection_text_nobk_create(pt_page_data->h_cnt_frm,
                                                    &t_rect,
                                                    FE_FNT_STYLE_REGULAR,
                                                    &t_info_inset_border,
                                                    8,
                                                    &(pt_page_data->h_conn_info));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     NW_TEST_RETEST_Y,
                     MENU_ITEM_V_WIDE,
                     NW_TEST_RETEST_H);

    i4_ret = _page_nw_test_connection_text_withbk_create(pt_page_data->h_cnt_frm, &t_rect, &(pt_page_data->h_retest));
    MENU_LOG_ON_FAIL(i4_ret);

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_ITEM_V_INSET_L,
                     NW_TEST_MANUAL_Y,
                     MENU_ITEM_V_WIDE,
                     NW_TEST_MANUAL_H);

#ifdef APP_MENU_NW_MANUAL_SETUP
    i4_ret = _page_nw_test_connection_text_withbk_create(pt_page_data->h_cnt_frm, &t_rect, &(pt_page_data->h_manual));
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = _page_nw_test_connection_signal_img_create(pt_page_data->h_conn_info, &(pt_page_data->h_signal_img));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_set_proc_func(ui4_page_id,
                                     _page_nw_test_connection_cnt_frm_proc_fct);
    MENU_LOG_ON_FAIL(i4_ret);

    _nw_test_page_animation_icon_create();

    h_g_nw_test_img_animation[0] = h_g_wdk_img_loading_icon_1;
    h_g_nw_test_img_animation[1] = h_g_wdk_img_loading_icon_2;
    h_g_nw_test_img_animation[2] = h_g_wdk_img_loading_icon_3;
    h_g_nw_test_img_animation[3] = h_g_wdk_img_loading_icon_4;
    h_g_nw_test_img_animation[4] = h_g_wdk_img_loading_icon_5;
    h_g_nw_test_img_animation[5] = h_g_wdk_img_loading_icon_6;
    h_g_nw_test_img_animation[6] = h_g_wdk_img_loading_icon_7;
    h_g_nw_test_img_animation[7] = h_g_wdk_img_loading_icon_8;
    h_g_nw_test_img_animation[8] = h_g_wdk_img_loading_icon_9;
    h_g_nw_test_img_animation[9] = h_g_wdk_img_loading_icon_10;
    h_g_nw_test_img_animation[10] = h_g_wdk_img_loading_icon_11;
    h_g_nw_test_img_animation[11] = h_g_wdk_img_loading_icon_12;

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
    PAGE_TEST_CONN_T*   pt_page_data = &t_page_nw_test_conn;

    i4_ret = _page_nw_test_connection_chg_lang();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_conn_info,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_retest,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

#ifdef APP_MENU_NW_MANUAL_SETUP
    i4_ret = c_wgl_set_visibility(pt_page_data->h_manual,
                                 WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = c_wgl_set_visibility(pt_page_data->h_signal_img,
                                 WGL_SW_HIDE);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Adjust last shadow position*/
#ifdef APP_MENU_NW_MANUAL_SETUP
    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->h_manual,
                    FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
#else
    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->h_retest,
                    FALSE);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    i4_ret = c_timer_create(&h_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = a_nw_register(_page_nw_test_nw_notify_callback, (VOID*)&pt_page_data->ui4_nw_tag, &pt_page_data->ui4_nw_nfy_id );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_async_invoke( _page_nw_test_start_test_connection,NULL, 0, TRUE);
    MENU_LOG_ON_FAIL(i4_ret);
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
    INT32    i4_ret;
    PAGE_TEST_CONN_T* pt_page_data = &t_page_nw_test_conn;

    i4_ret = a_nw_unregister(pt_page_data->ui4_nw_nfy_id);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui4_g_test_connection_nfy_id > 0)
    {
        i4_ret = a_nw_unregister(ui4_g_test_connection_nfy_id);
        MENU_LOG_ON_FAIL(i4_ret);
        ui4_g_test_connection_nfy_id = 0;
    }

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_HIDE_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _page_nw_test_connection_info_clear(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    if (h_timer != NULL_HANDLE)
    {
        c_timer_delete(h_timer);
        h_timer = NULL_HANDLE;
    }

    i4_ret = menu_network_last_shadow_hide(FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

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
    PAGE_TEST_CONN_T* pt_page_data = &t_page_nw_test_conn;

    /* set callback function for backbar */
    menu_set_backbar_proc (_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

#ifdef APP_MENU_NW_MANUAL_SETUP
    if (pt_hint)
    {
        if (MENU_PAGE_HT_BACK == pt_hint->e_hint_type)
        {
            c_wgl_set_focus(pt_page_data->h_manual, WGL_NO_AUTO_REPAINT);
        }
        else
        {
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(FALSE));
        }
    }
    else
    {
        MENU_LOG_ON_FAIL(menu_set_focus_on_backbar(FALSE));
    }
#else
    c_wgl_set_focus(pt_page_data->h_retest, WGL_NO_AUTO_REPAINT);
#endif
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
    c_speedtest_cancel();

    /* stop animation */
    menu_page_animation_stop();

    /* clean callback function of backbar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc (NULL)) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

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
 * Name: menu_common_page_nw_test_init
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
extern INT32 menu_common_page_nw_test_init(VOID)
{
    t_g_menu_common_nw_test_connection.pf_menu_page_create = _on_page_create;
    t_g_menu_common_nw_test_connection.pf_menu_page_destroy = _on_page_destroy;
    t_g_menu_common_nw_test_connection.pf_menu_page_show= _on_page_show;
    t_g_menu_common_nw_test_connection.pf_menu_page_hide = _on_page_hide;
    t_g_menu_common_nw_test_connection.pf_menu_page_get_focus = _on_page_get_focus;
    t_g_menu_common_nw_test_connection.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_nw_test_connection.pf_menu_page_update = _on_page_update;

    return MENUR_OK;
}



/*Jundi add for network info */
static INT32 _net_info_backbar_proc_fct (
                                                    HANDLE_T    h_widget,
                                                    UINT32      ui4_msg,
                                                    VOID*       param1,
                                                    VOID*       param2
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
            c_wgl_set_focus(t_page_nw_info_conn.h_lb_net_info, WGL_ASYNC_AUTO_REPAINT);
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

static INT32 _net_info_homebar_proc_fct (
                                                    HANDLE_T    h_widget,
                                                    UINT32      ui4_msg,
                                                    VOID*       param1,
                                                    VOID*       param2
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


extern UINT32 sys_cust_get_cc_width( VOID );
extern UINT32 sys_cust_get_cc_height( VOID );


static INT32 _net_info_nw_get_ssid(UTF16_T *pw2s_ssid)
{
    INT32                   i4_ret = MENUR_OK;
    INT32                   i4_len = 0;
    BOOL                    b_wireless_connected = FALSE;
    NW_WLAN_STATE_T         e_wlan_state;
    NET_802_11_BSS_INFO_T   t_bss_info;
    CHAR                    s_data[NET_802_11_MAX_LEN_SSID+1] = {0};

    c_memset (&t_bss_info, 0, sizeof(t_bss_info));

    i4_ret = a_nw_wlan_status(&e_wlan_state);
    MENU_LOG_ON_FAIL(i4_ret);

    if (e_wlan_state == NW_WLAN_ASSOCIATE)  /* has associate with wifi*/
    {
        i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
        if(i4_ret != MENUR_OK)
        {
            MENU_LOG_ON_FAIL(i4_ret);
            c_memset(t_bss_info.t_Bssid, 0, sizeof(t_bss_info.t_Bssid));
            t_bss_info.t_Ssid.ui4_SsidLen = 0;
        }
        if ((c_strlen(t_bss_info.t_Ssid.ui1_aSsid) > 0) /*wifi has been connected*/
            &&((UINT8)WLAN_WPA_COMPLETED == t_bss_info.u8_wpa_status))
        {
            b_wireless_connected = TRUE;
        }

        DBG_INFO(("\n%s,%d,from middleware:u8_wpa_status=%d,"
                    "t_CurrBss.t_Ssid.ui4_SsidLen=%d,t_CurrBss.t_Ssid.ui1_aSsid=%s,\n",
                   __FUNCTION__, __LINE__,
                   t_bss_info.u8_wpa_status,
                   t_bss_info.t_Ssid.ui4_SsidLen,
                   t_bss_info.t_Ssid.ui1_aSsid));

        if (a_nw_custom_is_get_ip_addr()&& b_wireless_connected)
        {
            if (c_strlen(t_bss_info.t_Ssid.ui1_aSsid) != 0)
            {
                c_memset(s_data, 0, NET_802_11_MAX_LEN_SSID+1);

                c_strncat(s_data, t_bss_info.t_Ssid.ui1_aSsid, NET_802_11_MAX_LEN_SSID);

                i4_len = c_strlen(s_data);
                c_uc_ps_to_w2s(s_data, pw2s_ssid, i4_len);
            }
        }
        else
        {
            DBG_INFO(("\n%s,%d,from middleware:u8_wpa_status=%d,"
                        "t_CurrBss.t_Ssid.ui4_SsidLen=%d,t_CurrBss.t_Ssid.ui1_aSsid=%s,\n",
                       __FUNCTION__, __LINE__,
                       t_bss_info.u8_wpa_status,
                       t_bss_info.t_Ssid.ui4_SsidLen,
                       t_bss_info.t_Ssid.ui1_aSsid));

        }
    }
    else if (e_wlan_state == NW_WLAN_ASSOCIATING)
    {
        DBG_INFO(("\n%s,%d,from middleware:u8_wpa_status=%d,"
                    "t_CurrBss.t_Ssid.ui4_SsidLen=%d,t_CurrBss.t_Ssid.ui1_aSsid=%s,\n",
                   __FUNCTION__, __LINE__,
                   t_bss_info.u8_wpa_status,
                   t_bss_info.t_Ssid.ui4_SsidLen,
                   t_bss_info.t_Ssid.ui1_aSsid));
    }
    else    /* not associate with wifi*/
    {
        DBG_INFO(("\n%s,%d,from middleware:u8_wpa_status=%d,"
                    "t_CurrBss.t_Ssid.ui4_SsidLen=%d,t_CurrBss.t_Ssid.ui1_aSsid=%s,\n",
                   __FUNCTION__, __LINE__,
                   t_bss_info.u8_wpa_status,
                   t_bss_info.t_Ssid.ui4_SsidLen,
                   t_bss_info.t_Ssid.ui1_aSsid));
    }

    return i4_ret;
}

static INT32 _net_info_nw_get_security_type(UTF16_T *pw2s_sec_type)
{
    INT32                   i4_ret = RMR_OK;
    NW_WLAN_STATE_T         e_wlan_state;
    NET_802_11_BSS_INFO_T   t_bss_info = {0};
    CHAR                    string[33] = "N/A";
    UTF16_T                 w2s_tmp_str[128] = {0};

    i4_ret = a_nw_wlan_status(&e_wlan_state);
    MENU_LOG_ON_FAIL(i4_ret);

    if (e_wlan_state == NW_WLAN_ASSOCIATE)
    {
        c_memset(&t_bss_info, 0, sizeof(t_bss_info));
        i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    switch(t_bss_info.e_AuthMode)
    {
        case IEEE_802_11_AUTH_MODE_NONE:
        case IEEE_802_11_AUTH_MODE_OPEN:
        {
            c_strncpy(string, "Open", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_SHARED:
        {
            c_strncpy(string, "WEP Shared", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WEPAUTO:
        {
            c_strncpy(string, "WEPAUTO", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA:
        {
            if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_TKIP)
            {
                c_strncpy(string, "WPA TKIP", 32);
            }
            else if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_AES)
            {
                c_strncpy(string, "WPA AES", 32);
            }
            else
            {
                c_strncpy(string, "WPA", 32);
            }
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_PSK:
        {
            c_strncpy(string, "WPA/PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2:
        {
            if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_TKIP)
            {
                c_strncpy(string, "WPA2 TKIP", 32);
            }
            else if(t_bss_info.e_AuthCipher == IEEE_802_11_AUTH_CIPHER_AES)
            {
                c_strncpy(string, "WPA2 AES", 32);
            }
            else
            {
                c_strncpy(string, "WPA2", 32);
            }
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2_PSK:
        {
            c_strncpy(string, "WPA2/PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPAPSK_OR_WPA2PSK:
        {
            c_strncpy(string, "WPAPSK/WPA2PSK", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA2_PSK_SHA256_AES:
        {
            c_strncpy(string, "WPA2PSK-SHA256AES", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_SAE:
        case IEEE_802_11_AUTH_MODE_WPA2_SAE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2SAE:
        {
            c_strncpy(string, "WPA3 SAE", 32);
            break;
        }

        case IEEE_802_11_AUTH_MODE_WPA_OWE:
        case IEEE_802_11_AUTH_MODE_WPA2_OWE:
        case IEEE_802_11_AUTH_MODE_WPA_OR_WPA2OWE:
        {
            c_strncpy(string, "WPA3 Open Enhanced", 32);
            break;
        }

        default:
            break;
    }
    c_uc_ps_to_w2s(string, w2s_tmp_str,127);
    c_uc_w2s_strcpy(pw2s_sec_type, w2s_tmp_str);
    return i4_ret;
}
static VOID _net_info_int_to_w2s(UTF16_T* w2s_dst,
                                          INT32 i4_src,
                                          UINT32 ui4_dst_len)
{
    CHAR    s_buf[32];
    c_sprintf(s_buf, "%d",  i4_src);
    c_uc_ps_to_w2s(s_buf, w2s_dst, ui4_dst_len);
}
static INT32 _net_info_get_wifi_remote_channel(UTF16_T* pw2s_channel)
{
    UINT8       ui1_ch = 0;
    CHAR        ac_channel[4] = {0};
    INT32       i4_ret = 0;
    NET_802_11_BSS_INFO_T CurrBss;

    //a_cfg_custom_get_last_p2p0_op_channel(&ui1_ch);
    c_memset(&CurrBss, 0, sizeof(CurrBss));
    i4_ret = a_nw_wlan_get_curr_bss(&CurrBss);
    MENU_LOG_ON_FAIL(i4_ret);
    if (c_strlen(CurrBss.t_Ssid.ui1_aSsid) > 0)
    {
        ui1_ch = CurrBss.i2_Channel;
    }
    DBG_LOG_PRINT(("%s,%d [sys info]wifi chanel:%d.\r\n",__FUNCTION__,__LINE__,CurrBss.i2_Channel));

    c_sprintf(ac_channel, "%d", ui1_ch);
    c_uc_ps_to_w2s(ac_channel, pw2s_channel, c_strlen(ac_channel));

    return MENUR_OK;
}

static INT32 i4_g_speed = 0;

static VOID _net_info_show_download_speed(VOID*  pv_data1,
                                                      VOID*  pv_data2,
                                                      VOID*  pv_data3)
{
#if 0
    INT32 i4_ret;
    CHAR        string[64]      ={'\0'};
    UTF16_T     w2s_str[128]  = {0};
    UTF16_T     w2s_tmp_str[128]     = {0};

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));

    c_snprintf(string, NETWORK_SPEED_LEN-1, "%.2f Kb/s",(DOUBLE)i4_g_speed);
    c_uc_ps_to_w2s(string,w2s_tmp_str,c_strlen(string));


    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_DOWN_SPEED],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_DOWN_SPEED],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_pm_refresh();
    menu_pm_repaint();
#endif
    return ;
}

static VOID net_info_download_speed_callback(INT32 i4Status,DOUBLE  u4Speed)
{
    if (i4Status == 0)
    {
        /* kbit/s, middleware return data is bytes/s, so need data*8/1024 */
        i4_g_speed = u4Speed/128;
    }
    else
    {
        /* speed test is failed */
        i4_g_speed = 0;
    }

    menu_request_context_switch(_net_info_show_download_speed, NULL, NULL, NULL);

    return;
}

static INT32 _net_ver_info_nw_info_update(VOID)
{
    INT32           i4_ret = MENUR_OK;

    NW_IP_INFO_T    t_net_ip_info;
    NW_IPV6_INFO_T  t_net_ipv6_info;
    CHAR *          s_tmp_str;
    CHAR            s_ip_str[16];
    CHAR            s_mac_str[64];
    CHAR            s_model_name[ACFG_CUSTOM_WIFI_MODULE_NAME_LEN] = {0};
    CHAR            tmp[32] = {0};
    UTF16_T         w2s_tmp_str[129];
    UTF16_T         w2s_str[129];
    BOOL            b_plug = FALSE;

    /*Connection Type*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = a_nw_get_ethernet_connect_info(&b_plug);
    if(i4_ret)
    {
        s_tmp_str = "UNKNOWN";
    }
    else
    {
        if(b_plug)
        {
            s_tmp_str = "Wired Connection";
        }
        else
        {
            NW_WLAN_BAND_T i4_freq_band = NW_WLAN_FREQ_UNKNOWN;
            i4_freq_band = a_nw_custom_wifi_frequency_band();
            if(i4_freq_band == NW_WLAN_FREQ_2_4_BAND)
            {
                s_tmp_str = "Wi-Fi 2.4GHz";
            }
            else if(i4_freq_band == NW_WLAN_FREQ_5_BAND)
            {
                s_tmp_str = "Wi-Fi 5GHz";
            }
            else if(i4_freq_band == NW_WLAN_FREQ_6_BAND)
            {
                s_tmp_str = "Wi-Fi 6GHz";
            }
            else
            {
                s_tmp_str = "Wi-Fi";
            }

        }
    }

    c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_CONNECTION_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_CONNECTION_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /* SSID */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if (!b_plug)
    {
       // _ver_info_nw_get_ssid(w2s_tmp_str);
       _net_info_nw_get_ssid(w2s_tmp_str);
    }

    if (c_uc_w2s_strlen(w2s_tmp_str) == 0)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SSID],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SSID],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if (!b_plug)
    {
       // _ver_info_nw_get_security_type(w2s_tmp_str);
       _net_info_nw_get_security_type(w2s_tmp_str);
    }

    if (c_uc_w2s_strlen(w2s_tmp_str) == 0)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SECURITY_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SECURITY_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv4 IP Address*/
    c_memset(&t_net_ip_info, 0, sizeof(t_net_ip_info));
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    i4_ret = a_nw_get_crnt_ip_info(&t_net_ip_info);
    MENU_LOG_ON_FAIL(i4_ret);

    if(0 == t_net_ip_info.ui4_address)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }
    else
    {
        a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_address);
        c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IP_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IP_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv4 Default Gateway*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_gw);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);


    /*IPv4 Subnet Mask*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_netmask);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SUB_MASK],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SUB_MASK],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv4 Pref. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_1st_dns);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_PREF_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_PREF_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv4 Alt. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_2nd_dns);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ALT_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ALT_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv6 Address*/
    c_memset(&t_net_ipv6_info, 0, sizeof(t_net_ipv6_info));
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = a_nw_get_v6_info(&t_net_ipv6_info);
    MENU_LOG_ON_FAIL(i4_ret);

    if(0 == c_strlen(t_net_ipv6_info.ac_v6ip))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }
    else
    {
        c_uc_ps_to_w2s(t_net_ipv6_info.ac_v6ip, w2s_tmp_str,c_strlen(t_net_ipv6_info.ac_v6ip));
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IPV6_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IPV6_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv6 Default Gateway*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if(0 == c_strlen(t_net_ipv6_info.ac_v6gw))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }
    else
    {
        c_uc_ps_to_w2s(t_net_ipv6_info.ac_v6gw, w2s_tmp_str,c_strlen(t_net_ipv6_info.ac_v6gw));
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IPV6_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IPV6_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv6 Prefix Length*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    if(0 == t_net_ipv6_info.ui4_prefix)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }
    else
    {
        _net_info_int_to_w2s(w2s_tmp_str, t_net_ipv6_info.ui4_prefix, 4);
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IPV6_PREFIX_LENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IPV6_PREFIX_LENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IPv6 Pref. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if(0 != c_strlen(t_net_ipv6_info.ac_dns1))
    {
        c_uc_ps_to_w2s(t_net_ipv6_info.ac_dns1, w2s_tmp_str,c_strlen(t_net_ipv6_info.ac_dns1));
        i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_PREF_DNS],0),
                    w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str, L", ", c_uc_w2s_strlen(w2s_str));
        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_PREF_DNS],0),
                    w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /*IPv6 Alt. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if(0 != c_strlen(t_net_ipv6_info.ac_dns2))
    {
        c_uc_ps_to_w2s(t_net_ipv6_info.ac_dns2, w2s_tmp_str,c_strlen(t_net_ipv6_info.ac_dns2));
        i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ALT_DNS],0),
                    w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_uc_w2s_strncat(w2s_str, L", ", c_uc_w2s_strlen(w2s_tmp_str));
        c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

        i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                        WGL_CMD_LB_SET_ITEM_TEXT,
                        WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ALT_DNS],0),
                        w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    /* IP Type */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if((c_strlen(t_net_ipv6_info.ac_v6ip) != 0) && (t_net_ip_info.ui4_address != 0))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" IPv6 & IPv4 ");
    }
    else if((c_strlen(t_net_ipv6_info.ac_v6ip) != 0) && (t_net_ip_info.ui4_address == 0))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" IPv6 ");
    }
    else if((c_strlen(t_net_ipv6_info.ac_v6ip) == 0) && (t_net_ip_info.ui4_address != 0))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" IPv4 ");
    }
    else if((c_strlen(t_net_ipv6_info.ac_v6ip) == 0) && (t_net_ip_info.ui4_address == 0))
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IP_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IP_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);


    /*Download Speed*/
#if 0
    if(i4_g_speed == 0)
    {
        i4_ret= c_speedtest(NULL,net_info_download_speed_callback);
        if (i4_ret != 0)
        {
            c_speedtest_cancel();
        }
    }
    else
    {
        _net_info_show_download_speed(NULL, NULL, NULL);
    }
#endif

    /*WIFI Strength*/
    INT32   i2_Level = 80;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));

    i2_Level = a_nw_get_wlan_signal_lvl_from_rssi();

    //_int_to_w2s(w2s_tmp_str,i2_Level,4);
     _net_info_int_to_w2s(w2s_tmp_str,i2_Level,4);

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_STRENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_STRENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*RSSI*/
#if 0
    INT32                       i4Rssi_avg = 0;
    NET_802_11_WIFI_RSSI_T      t_rssi;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));
    c_memset (&t_rssi,    0, sizeof(NET_802_11_WIFI_RSSI_T));

    i4_ret = a_nw_wlan_get_rssi(&t_rssi);
    if (i4_ret == 0)
    {
        i4Rssi_avg = t_rssi.i4Rssi_a;
        if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_a)&&(t_rssi.i4Rssi_a < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_a);

        if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_b)&&(t_rssi.i4Rssi_b < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_b);

        if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_c)&&(t_rssi.i4Rssi_c < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_c);
    }
    DBG_LOG_PRINT(("[TEST][%s]:[%d]i4Rssi_avg=%d\n",__FILE__,__LINE__,i4Rssi_avg));

    _int_to_w2s(w2s_tmp_str,i4Rssi_avg,4);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_RSSI],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_RSSI],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*WIFI Channel*/
#if 0
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));

    i4_ret = _get_wifi_remote_channel(w2s_tmp_str);

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WIFI_CHANNEL],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(h_lb_ver_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_ver_info_idx[VER_INFO_ROW_WIFI_CHANNEL],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*RJ45 MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);
#ifndef MT5583_MODEL
    //Get the RJ45 Mac
    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac_str);

    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_RJ45_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_RJ45_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#else
    //Get the ID Mac
    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac_str);

    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ID_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ID_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    /*WLAN MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);

    a_nw_get_mac_addr_string(NI_WIRELESS_0,s_mac_str);
    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WLAN_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WLAN_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*WiFi Module*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    a_cfg_cust_get_wifi_model_name(s_model_name, ACFG_CUSTOM_WIFI_MODULE_NAME_LEN);
    DBG_LOG_PRINT((" %s, %d line, wifi_nodule_name: %s\n", __FILE__, __LINE__, s_model_name));

    c_uc_ps_to_w2s(s_model_name,w2s_tmp_str,c_strlen(s_model_name));
     i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_MODE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_MODE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _network_info_nw_info_update(VOID)
{
#if 0
    INT32           i4_ret = MENUR_OK;

    NW_IP_INFO_T    t_net_ip_info;
    CHAR *          s_tmp_str;
    CHAR            s_ip_str[16];
    CHAR            s_mac_str[64];
    CHAR            s_model_name[64] = {0};

    UTF16_T         w2s_tmp_str[128];
    UTF16_T         w2s_str[128];
    BOOL            b_plug = FALSE;
    CHAR            tmp[32] = {0};

    /*Connection Type*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    i4_ret = a_nw_get_ethernet_connect_info(&b_plug);
    DBG_LOG_PRINT(("[%s %d]i4_ret == %d\n",__FUNCTION__,__LINE__,i4_ret));
    if(i4_ret)
    {
        s_tmp_str = "UNKNOWN";
    }
    else
    {
        if(b_plug)
        {
            s_tmp_str = "Wired Connection";
        }
        else
        {
            s_tmp_str = "WIFI";
        }
    }

    c_uc_ps_to_w2s(s_tmp_str,w2s_tmp_str,c_strlen(s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_CONNECTION_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_CONNECTION_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /* SSID */
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if (!b_plug)
    {
        _net_info_nw_get_ssid(w2s_tmp_str);
    }

    if (c_uc_w2s_strlen(w2s_tmp_str) == 0)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SSID],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SSID],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));

    if (!b_plug)
    {
        _net_info_nw_get_security_type(w2s_tmp_str);
    }

    if (c_uc_w2s_strlen(w2s_tmp_str) == 0)
    {
        c_uc_w2s_strcpy(w2s_tmp_str, L" N/A ");
    }

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SECURITY_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SECURITY_TYPE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*IP Address*/
    c_memset(&t_net_ip_info, 0, sizeof(t_net_ip_info));
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    i4_ret = a_nw_get_crnt_ip_info(&t_net_ip_info);
    MENU_LOG_ON_FAIL(i4_ret);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_address);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IP_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_IP_ADDR],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Default Gateway*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_gw);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_DEF_GATEWAY],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);


    /*Subnet Mask*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_netmask);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SUB_MASK],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_SUB_MASK],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Pref. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_1st_dns);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_PREF_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_PREF_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Alt. DNS Server*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_ip_str,0,sizeof(CHAR)*16);

    a_nw_ntoa(s_ip_str,t_net_ip_info.ui4_2nd_dns);
    c_uc_ps_to_w2s(s_ip_str,w2s_tmp_str,c_strlen(s_ip_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ALT_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ALT_DNS],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*Download Speed*/
    #ifdef NEVER
    if(i4_g_speed == 0)
    {
        i4_ret= c_speedtest(NULL,net_info_download_speed_callback);
        if (i4_ret != 0)
        {
            c_speedtest_cancel();
        }
    }
    else
    {
        _net_info_show_download_speed(NULL, NULL, NULL);
    }
    #endif

    i4_ret= c_speedtest(NULL,net_info_download_speed_callback);
    if (i4_ret != 0)
    {

        c_speedtest_cancel();
    }

    /*WIFI Strength*/
    INT32   i2_Level = 80;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));

    i2_Level = a_nw_get_wlan_signal_lvl_from_rssi();
    _net_info_int_to_w2s(w2s_tmp_str,i2_Level,4);

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_STRENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_STRENGTH],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*RSSI*/
    INT32                       i4Rssi_avg = 0;
    NET_802_11_WIFI_RSSI_T      t_rssi;

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));
    c_memset (&t_rssi,    0, sizeof(NET_802_11_WIFI_RSSI_T));

    i4_ret = a_nw_wlan_get_rssi(&t_rssi);
    if (i4_ret == 0)
    {
    i4Rssi_avg = t_rssi.i4Rssi_a;
    if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_a)&&(t_rssi.i4Rssi_a < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_a);

        if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_b)&&(t_rssi.i4Rssi_b < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_b);

        if ((WEAKEST_SIGNAL_STRENGTH <= t_rssi.i4Rssi_c)&&(t_rssi.i4Rssi_c < 0))
            i4Rssi_avg = MAX_SIGNAL_STRENGTH(i4Rssi_avg,t_rssi.i4Rssi_c);
    }
    DBG_LOG_PRINT(("[TEST][%s]:[%d]i4Rssi_avg=%d\n",__FILE__,__LINE__,i4Rssi_avg));

    _net_info_int_to_w2s(w2s_tmp_str,i4Rssi_avg,4);

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_RSSI],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_RSSI],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);


    /*WIFI Channel*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str,     0, sizeof(w2s_str));

    i4_ret = _net_info_get_wifi_remote_channel(w2s_tmp_str);

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_CHANNEL],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_CHANNEL],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*RJ45 MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);
#ifndef MT5583_MODEL
    //Get the RJ45 Mac
    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac_str);

    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_RJ45_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_RJ45_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#else
    //Get the ID Mac
    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac_str);

    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ID_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_ID_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#endif

    /*WLAN MAC*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_mac_str,0,sizeof(CHAR)*64);

    a_nw_get_mac_addr_string(NI_WIRELESS_0,s_mac_str);
    c_uc_ps_to_w2s(s_mac_str,w2s_tmp_str,c_strlen(s_mac_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WLAN_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WLAN_MAC],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    /*WiFi Module*/
    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(s_model_name,0,sizeof(CHAR)*64);

    FILE * fl = popen("iwpriv wlan0  driver  \"get_mcr 0x8000000c \"", "r");
    if (fl == NULL)
        return 0;

    fgets(tmp, 32, fl);
    pclose(fl);
    c_strncpy(s_model_name, tmp + (c_strlen(tmp) - 6), 4);

    DBG_LOG_PRINT((" %s, %d line, wifi_nodule_name: %s\n", __FILE__, __LINE__, s_model_name));
    c_uc_ps_to_w2s(s_model_name,w2s_tmp_str,c_strlen(s_model_name));
     i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_MODE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);

    c_uc_w2s_strncat(w2s_str,w2s_tmp_str,c_uc_w2s_strlen(w2s_tmp_str));

    i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_SET_ITEM_TEXT,
                    WGL_PACK_2(a_g_net_info_idx[NET_INFO_ROW_WIFI_MODE],0),
                    w2s_str);
    MENU_LOG_ON_FAIL(i4_ret);
#endif
    return MENUR_OK;
}

static VOID _net_info_idx_remapping(VOID)
{
    UINT16      ui2_tmp_idx = 0;
    UINT16      ui2_i = 0;

    c_memset(a_g_net_info_idx,0,sizeof(UINT16)*NET_INFO_ROW_LAST_NUM);

    ui2_tmp_idx = 0;

    for (ui2_i = 0; ui2_i < sizeof(t_g_net_info_items)/sizeof(t_g_net_info_items[0]); ui2_i++)
    {
        a_g_net_info_idx[t_g_net_info_items[ui2_i].e_row_idx] = ui2_tmp_idx++;
    }

    a_g_net_info_idx[NET_INFO_ROW_LAST_NUM]     = ui2_tmp_idx;
    c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                 WGL_CMD_LB_SET_ELEM_NUM,
                 WGL_PACK(ui2_tmp_idx),
                 NULL);
}

static INT32 _net_info_chg_lang(VOID)
{
    INT32               i4_ret;
    UINT8               ui1_i;
    UTF16_T             w2s_tmp_str[128];
    UTF16_T             w2s_str[128];
    static UTF16_T      w2s_g_sq[128];
    const CHAR*         s_tmp_str;

    c_memset(w2s_g_sq, 0, sizeof(w2s_g_sq));

    s_tmp_str = "  ";

    /* Change the menu title */
    i4_ret = menu_main_set_title(MLM_MENU_KEY_SYS_INFO_NETWORK);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    c_memset(w2s_str, 0, sizeof(w2s_str));
    c_memset(w2s_g_sq, 0, sizeof(w2s_g_sq));


    for (ui1_i = 0; ui1_i < NET_INFO_ROW_LAST_NUM; ui1_i ++)
    {
        c_uc_w2s_strcpy(w2s_str,MENU_TEXT(t_g_net_info_items[ui1_i].ui2_mlm_idx));

        c_uc_ps_to_w2s(s_tmp_str, w2s_tmp_str, c_strlen(s_tmp_str));
        c_uc_w2s_strcat(w2s_str,w2s_tmp_str);
        i4_ret = c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                              WGL_CMD_LB_SET_ITEM_TEXT,
                              WGL_PACK_2(a_g_net_info_idx[ui1_i],0),
                              w2s_str);
        MENU_LOG_ON_FAIL(i4_ret);

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
        c_memset(w2s_str, 0, sizeof(w2s_str));
    }
    c_uc_ps_to_w2s(s_tmp_str, w2s_tmp_str, c_strlen(s_tmp_str));

    c_uc_w2s_strcat(w2s_g_sq,w2s_tmp_str);

    return MENUR_OK;
}

static INT32 _refresh_net_info(VOID)
{
    INT32 i4_ret = MENUR_OK;

    _net_info_idx_remapping();
    _net_info_chg_lang();

    //i4_ret = _network_info_nw_info_update();
    i4_ret = _net_ver_info_nw_info_update();
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}
static VOID _net_info_timer_animation_fct(HANDLE_T h_timer,VOID* pv_tag);

static VOID _net_info_do_animation_timer(VOID* pv_data,
                                                    SIZE_T  z_data_size)
{
    INT32 i4_ret = 0;

    _refresh_net_info();
    c_wgl_repaint(t_page_nw_info_conn.h_lb_net_info, NULL, TRUE);

    i4_ret=c_timer_stop(h_refresh_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_start(h_refresh_timer,
                  NET_INFO_REFRESH_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _net_info_timer_animation_fct,
                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);
}


static VOID _net_info_timer_animation_fct(HANDLE_T h_timer,
                                                      VOID*     pv_tag)
{
    menu_async_invoke(_net_info_do_animation_timer, NULL, 0, FALSE);
}

static VOID _net_info_reset_timer(VOID)
{
    INT32 i4_ret = 0;
    DBG_LOG_PRINT((" [menu] %s,%d\r\n",__FUNCTION__,__LINE__));


    i4_ret=c_timer_stop(h_refresh_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret=c_timer_start(h_refresh_timer,
                          NET_INFO_REFRESH_TIMER,
                          X_TIMER_FLAG_ONCE,
                          _net_info_timer_animation_fct,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

}

static INT32 _net_info_widget_proc_fct(HANDLE_T    h_widget,
                                                   UINT32      ui4_msg,
                                                   VOID*       param1,
                                                   VOID*       param2)
{
    UINT32      ui4_keycode = (UINT32)param1;
#ifdef APP_TTS_SUPPORT
    UTF16_T     w2s_str[128+1] = {0};
    CHAR        info_srting[128+1] = {0};

#endif

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32      ui4_hlt_idx = 0;
            UINT16      ui2_tmp = 0;

            /*reset timer first */
            _net_info_reset_timer();
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                {
                    return WMPR_DONE;
                }

                case BTN_EXIT:
                case BTN_RETURN:
                    menu_netowrk_nav_back();
                    return MENUR_OK;

                case BTN_CURSOR_UP:
                    c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                                    WGL_CMD_LB_GET_HLT_INDEX,
                                    WGL_PACK(&ui4_hlt_idx),
                                    NULL);
                    ui2_tmp = (UINT16)ui4_hlt_idx;
                    if (ui2_tmp <= a_g_net_info_idx[NET_INFO_ROW_SSID])
                    {
                        menu_set_focus_on_backbar(TRUE);
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                    }
                    break;

                case BTN_CURSOR_DOWN:
                    c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                                WGL_CMD_LB_GET_HLT_INDEX,
                                WGL_PACK(&ui4_hlt_idx),
                                NULL);
                    ui2_tmp = (UINT16)ui4_hlt_idx;
                    if (ui2_tmp == (a_g_net_info_idx[NET_INFO_ROW_LAST_NUM]-1))
                    {
                        menu_help_tip_keytip_set_focus(t_page_nw_info_conn.h_lb_net_info,ui2_tmp,FALSE);
                        menu_pm_repaint();
                    }
                    break;

                default:
                    break;
            }
            break;
        }

        case WGL_MSG_KEY_UP:
        {
            if( ui4_keycode == BTN_PRG_UP ||
                ui4_keycode == BTN_PRG_DOWN ||
                ui4_keycode == BTN_PREV_PRG)
            {
                _refresh_net_info();
                menu_pm_repaint();
                return WMPR_DONE;
            }
        }

#ifdef APP_TTS_SUPPORT
        case WGL_MSG_GET_FOCUS:
        {
            UINT32      ui4_hlt_idx = 0;
            c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                    WGL_CMD_LB_GET_HLT_INDEX,
                    WGL_PACK(&ui4_hlt_idx),
                    NULL);

            c_wgl_do_cmd(t_page_nw_info_conn.h_lb_net_info,
                        WGL_CMD_LB_GET_ITEM_TEXT,
                        WGL_PACK_2(ui4_hlt_idx,0),
                        w2s_str);

            a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));

            c_uc_w2s_to_ps (w2s_str, info_srting, c_uc_w2s_strlen(w2s_str));
            DBG_INFO(("%s,%d [info tts]get focus idx= %d str= %s, \r\n",__FUNCTION__,__LINE__,ui4_hlt_idx,info_srting));
            break;
        }
#endif

        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


static INT32 _lb_net_info_create(
                                         HANDLE_T    h_parent,
                                         HANDLE_T*   ph_widget
                                        )
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_INSET_T         t_inset;

    //WGL_IMG_INFO_T              t_img_info;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols;
    WGL_LB_ITEM_T               at_items;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    WGL_LB_HLT_ELEM_EFFECT_T    t_hlt_elem_effect;

    //const CHAR*         s_tmp_str;
    UTF16_T             w2s_tmp_str[128];

    UINT8 ui1_i;


    /* Column info */
    at_cols.e_col_type       = LB_COL_TYPE_TEXT;
    at_cols.ui1_align        = COMMON_VER_INFO_LB_ALIGN;
    at_cols.ui2_width        = COMMON_VER_INFO_LB_COL_W;
    at_cols.ui2_max_text_len = 128;

    /* listbox init struct */
    t_lb_init.ui4_style         = WGL_STL_LB_NO_WRAP_OVER |
                                  WGL_STL_LB_FORCE_HLT |
                                  WGL_STL_LB_NO_SMART_CUT;

    t_lb_init.ui2_max_elem_num  = NET_INFO_ROW_LAST_NUM;


    t_lb_init.ui2_elem_size     = COMMON_VER_INFO_ELEM_SIZE;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = &at_cols;

    SET_RECT_BY_SIZE(&t_rect,
                     COMMON_VER_INFO_LB_X,
                     COMMON_VER_INFO_LB_Y,
                     COMMON_VER_INFO_LB_W,
                     COMMON_VER_INFO_LB_H);

    i4_ret = c_wgl_create_widget (h_parent,
                                  HT_WGL_WIDGET_LIST_BOX,
                                  WGL_CONTENT_LIST_BOX_DEF,
                                  WGL_BORDER_NULL,
                                  &t_rect,
                                  _net_info_widget_proc_fct, //_net_info_widget_proc_fct
                                  255,
                                  & t_lb_init,
                                  NULL,
                                  ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    if(1366 == (UINT32)sys_cust_get_cc_width() &&
        768 == (UINT32)sys_cust_get_cc_height())
    {
        t_fnt_info.e_font_size    = FE_FNT_SIZE_MEDIUM;
    }
    else
    {
        t_fnt_info.e_font_size    = COMMON_VER_INFO_FONT_SIZE;
    }
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_SET_COL_FONT,
                           WGL_PACK(0),
                           WGL_PACK(&t_fnt_info));
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Inset */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 15;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_CNT_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_INSET,
                          (VOID*)0,
                          &t_inset);
    MENU_LOG_ON_FAIL(i4_ret);

#if 1
    t_inset.i4_left     = COMMON_VER_INFO_INSET_L + 5*4/3;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
#endif

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_ELEM_INSET,
                          &t_inset,
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Color */
    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_disable = t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;//t_g_menu_color_ver_info_text_hlt;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;//t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_pushed = t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_selected = t_g_menu_color_bk1_txt_disable;
    t_lb_color.t_selected_disable = t_g_menu_color_bk1_txt_disable;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color));
    MENU_LOG_ON_FAIL(i4_ret);

    t_lb_color.t_normal = t_g_menu_color_transp;
    t_lb_color.t_disable = t_g_menu_color_transp;
    t_lb_color.t_highlight = t_g_menu_color_transp;//t_g_menu_color_ver_info_bk;
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
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info) );
    MENU_LOG_ON_FAIL(i4_ret);

    t_img_elem.h_normal             = NULL_HANDLE;
    t_img_elem.h_disable            = NULL_HANDLE;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = NULL_HANDLE;
    t_img_elem.h_pushed             = NULL_HANDLE;
    t_img_elem.h_selected           = NULL_HANDLE;
    t_img_elem.h_selected_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_memset (& t_hlt_elem_effect, 0, sizeof (WGL_LB_HLT_ELEM_EFFECT_T));

    /* Set long text scroll effect */
    t_hlt_elem_effect.ui4_style                  = WGL_LB_HEF_STL_SCRL_LONG_TEXT;
    t_hlt_elem_effect.t_text_scrl.ui4_style      = WGL_LB_TEXT_SCRL_STL_TILL_LAST_CHAR |
                                                   WGL_LB_TEXT_SCRL_STL_REPEAT;
    t_hlt_elem_effect.t_text_scrl.ui4_scrl_count = 0;
    t_hlt_elem_effect.t_text_scrl.ui4_ms_delay   = 180;
    t_hlt_elem_effect.t_text_scrl.b_sync         = FALSE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                            WGL_CMD_LB_EXT_SET_HLT_ELEM_EFFECT,
                            WGL_PACK (& t_hlt_elem_effect),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    for (ui1_i = 0; ui1_i < NET_INFO_ROW_LAST_NUM; ui1_i++)
    {
        c_uc_w2s_strcpy(w2s_tmp_str,MENU_TEXT(t_g_net_info_items[ui1_i].ui2_mlm_idx));

        at_items.e_col_type = LB_COL_TYPE_TEXT;
        at_items.data.pw2s_text = w2s_tmp_str;

        i4_ret = c_wgl_do_cmd(*ph_widget,
                                WGL_CMD_LB_APPEND_ELEM,
                                WGL_PACK(&at_items),
                                NULL);
        MENU_LOG_ON_FAIL(i4_ret);

        c_memset(w2s_tmp_str, 0, sizeof(w2s_tmp_str));
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_nw_info_connection_chg_lang
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

static INT32 _page_nw_info_connection_chg_lang(VOID)
{
    INT32   i4_ret = MENUR_OK;
    i4_ret = menu_main_set_title(MLM_MENU_KEY_SYS_INFO_NETWORK);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_nw_info_page_create
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
static INT32 _on_nw_info_page_create(UINT32 ui4_page_id,
                                               VOID * pv_create_data)
{
    PAGE_NET_INFO_CONN_T*   pt_page_data = &t_page_nw_info_conn;
    INT32                   i4_ret;

    _net_info_idx_remapping();

    c_memset(pt_page_data, 0, sizeof(PAGE_NET_INFO_CONN_T));

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &(pt_page_data->h_cnt_frm));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _lb_net_info_create(pt_page_data->h_cnt_frm, &(pt_page_data->h_lb_net_info));
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_timer_create(&h_refresh_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_nw_info_page_destroy
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
static INT32 _on_nw_info_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_nw_info_page_show
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
static INT32 _on_nw_info_page_show(UINT32 ui4_page_id)
{
    INT32               i4_ret = MENUR_OK;
    PAGE_NET_INFO_CONN_T*   pt_page_data = &t_page_nw_info_conn;

    _net_info_idx_remapping();

    i4_ret = _page_nw_info_connection_chg_lang();
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_page_data->h_lb_net_info,
                                  WGL_SW_RECURSIVE);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_page_data->h_lb_net_info,
                            WGL_CMD_LB_HLT_ELEM_VISIBLE,
                            WGL_PACK(0),
                            NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus(pt_page_data->h_lb_net_info,WGL_NO_AUTO_REPAINT);

    i4_ret=c_timer_start(h_refresh_timer,
                  NET_INFO_REFRESH_TIMER,
                  X_TIMER_FLAG_ONCE,
                  _net_info_timer_animation_fct,
                  NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    _net_info_chg_lang();

    //_network_info_nw_info_update();
     _net_ver_info_nw_info_update();

    i4_ret = menu_network_last_shadow_update_position(
                    pt_page_data->h_lb_net_info,
                    FALSE);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_nw_info_page_hide
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
static INT32 _on_nw_info_page_hide(UINT32 ui4_page_id)
{
    INT32    i4_ret;
    i4_ret=c_timer_stop(h_refresh_timer);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_set_backbar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = menu_set_homebar_proc(NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;

}
/*----------------------------------------------------------------------------
 * Name: _on_nw_info_page_get_focus
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
static INT32 _on_nw_info_page_get_focus(
                                                    UINT32            ui4_page_id,
                                                    MENU_PAGE_HINT_T* pt_hint
                                                  )
{
    PAGE_NET_INFO_CONN_T* pt_page_data = &t_page_nw_info_conn;

    c_wgl_set_focus(pt_page_data->h_lb_net_info, WGL_NO_AUTO_REPAINT);

    pt_page_data->b_this_page_show = TRUE;

    /* set callback function for backbar */
    menu_set_backbar_proc(_net_info_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_net_info_homebar_proc_fct);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _on_nw_info_page_lose_focus
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
static INT32 _on_nw_info_page_lose_focus(UINT32 ui4_page_id)
{
    /* stop animation */
    menu_page_animation_stop();

    /* clean callback function of backbar */
    MENU_LOG_ON_FAIL (menu_set_backbar_proc (NULL)) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _on_nw_info_page_update
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
static INT32 _on_nw_info_page_update(
                                              UINT32 ui4_page_id,
                                              UINT32 ui4_update_mask
                                              )
{
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_common_page_nw_info_init
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
extern INT32 menu_common_page_nw_info_init(VOID)
{
    t_g_menu_common_nw_info.pf_menu_page_create = _on_nw_info_page_create;
    t_g_menu_common_nw_info.pf_menu_page_destroy = _on_nw_info_page_destroy;
    t_g_menu_common_nw_info.pf_menu_page_show= _on_nw_info_page_show;
    t_g_menu_common_nw_info.pf_menu_page_hide = _on_nw_info_page_hide;
    t_g_menu_common_nw_info.pf_menu_page_get_focus = _on_nw_info_page_get_focus;
    t_g_menu_common_nw_info.pf_menu_page_lose_focus= _on_nw_info_page_lose_focus;
    t_g_menu_common_nw_info.pf_menu_page_update = _on_nw_info_page_update;

    return MENUR_OK;
}

