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
 * $RCSfile: wfd.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: ----------$
 * $SWAuthor: hs_mingmingzhang $
 * $MD5HEX: --------- $
 *
 * Description:
 *         This header file contains public interfaces, constant and type
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/

#include "wfd.h"
#include "wfd_cli.h"
#include "wfd_view/wfd_view.h"

#include "c_svctx.h"
#include "c_handle.h"
#include "c_scc.h"
#include "c_rm.h"

#include "c_net_config.h"
#include "u_dhcpc_api.h"
#include "u_net_common.h"
#include "u_drv_cust.h"

#include "u_net_util.h"
#include "wfd_p2p_conn.h"
#include "wfd_rtsp_conn.h"
#include "wfd_dev_list.h"
#include "menu2/a_menu.h"
#include "app_util/a_tv.h"
#include "res/app_util/config/a_cfg_custom.h"

#define WFD_CONN_TIMEOUT (UINT32)120

static UINT16 ui2_dbg_level = 0;//DBG_INIT_LEVEL_APP_WFD;
static WFD_MAIN_T t_g_wfd_main;
INT32 i4_get_ip_count = 0;
INT32 i4_start_rtsp = 0;
BOOL b_rtsp_start = FALSE;
BOOL b_log = TRUE;
BOOL b_pause_tv = FALSE;
#ifdef APP_MENU_WFD_COEXIST
BOOL b_input_src_show = FALSE;
#endif

static INT32 i4_timeout = -1;

extern BOOL b_g_resume_wfd_directly;


static VOID _wfd_app_timer_nfy_fct(HANDLE_T h_timer, VOID* pv_tag);
INT32 wfd_set_device_remove_listen(VOID);
INT32 wfd_reg_icl(VOID);
static VOID wfd_app_time_out_timer_nfy_func(HANDLE_T h_timer, VOID* pv_tag);

static VOID _wfd_icl_nfy_hdlr(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4);
static INT32 _wfd_app_send_msg( HANDLE_T                    h_app,
                                UINT32                      ui4_type,
                                VOID*                       pv_msg,
                                SIZE_T                      z_msg_size,
                                WFD_SEND_RETRY_TYPE_T       e_retry_type);

BOOL wfd_get_log(VOID)
{
    return b_log;
}

BOOL wfd_set_log(BOOL b_yes)
{
    return b_log = b_yes;
}

static INT32 _wfd_nfy_wgl(
        UINT32                  ui4_msg,
        VOID*                   pv_param1,
        VOID*                   pv_param2)
{
    /* Note: this callback function is executed in IO MAnager's thread
     * context. It should not process any heavy job in the callbacks
    */
    WFD_WIDGET_MSG_T   t_msg;
    t_msg.ui4_msg   = ui4_msg;
    t_msg.pv_param1 = pv_param1;
    t_msg.pv_param2 = pv_param2;

    _wfd_app_send_msg(t_g_wfd_main.h_app,WFD_MSG_WGL_NFY, (VOID*)&t_msg, sizeof(WFD_WIDGET_MSG_T),WFD_SEND_RETRY_TYPE_ONCE);

    return WGLR_OK;
}

static INT32 _wfd_app_send_msg( HANDLE_T                    h_app,
                                UINT32                      ui4_type,
                                VOID*                       pv_msg,
                                SIZE_T                      z_msg_size,
                                WFD_SEND_RETRY_TYPE_T       e_retry_type)
{
    INT32        i4_retry, i4_ret, i;

    switch(e_retry_type)
    {
    case WFD_SEND_RETRY_TYPE_CRITICAL:
        i4_retry = 20;
        break;

    case WFD_SEND_RETRY_TYPE_IMPORTANT:
        i4_retry = 10;
        break;

    case WFD_SEND_RETRY_TYPE_NORMAL:
        i4_retry = 5;
        break;

    case WFD_SEND_RETRY_TYPE_ONCE:
    default:
        i4_retry = 1;
        break;
    }

    i4_ret = WFDR_OK;
    for(i = 0; i < i4_retry; i++)
    {
        i4_ret = c_app_send_msg(h_app, ui4_type, pv_msg, z_msg_size, NULL, NULL);
        if(AEER_OK == i4_ret)
        {
            return WFDR_OK;
        }
        else if(AEER_INV_HANDLE == i4_ret)
        {
            WFD_DBG_ERR(i4_ret);

            return WFDR_FAIL;
        }

        DBG_LOG_PRINT(("c_app_send_msg() failed. i4_ret = %d. retry = %d\r\n", i4_ret,i4_retry));
    }

    return WFDR_FAIL;
}

static INT32 _wfd_init_svctx(VOID)
{
    return WFDR_OK;
    INT32                       i4_ret;
    /* open main service context */
    i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &t_g_wfd_main.h_main_svctx);
    if(SVCTXR_OK != i4_ret)
    {
        return WFDR_FAIL;
    }

    /* open sub service context */
    i4_ret = c_svctx_open(SVCTX_NAME_SUB, &t_g_wfd_main.h_sub_svctx);
    if(SVCTXR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__, i4_ret));

        t_g_wfd_main.h_sub_svctx = NULL_HANDLE;
    }

#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
    /**/

    i4_ret = c_svctx_open(SVCTX_NAME_MONITOR_BYPASS, &t_g_wfd_main.h_mnbypass_svctx);
    if(SVCTXR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__, i4_ret));
        t_g_wfd_main.h_mnbypass_svctx = NULL_HANDLE;
    }

    i4_ret = c_svctx_open(SVCTX_NAME_TV_BYPASS, &t_g_wfd_main.h_tvbypass_svctx);
    if(SVCTXR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__, i4_ret));
        t_g_wfd_main.h_tvbypass_svctx = NULL_HANDLE;
    }
#endif

#ifdef APP_NAV_REC_SUPPORT
    /**/
    i4_ret = c_svctx_open(SVCTX_NAME_REC_TV, &t_g_wfd_main.h_rec_svctx);
    if(SVCTXR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__, i4_ret));
        t_g_wfd_main.h_rec_svctx = NULL_HANDLE;
    }
#endif

    return WFDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _wfd_iom_nfy_fct (VOID*             pv_nfy_tag,
                              IOM_NFY_COND_T    e_nfy_cond,
                              UINT32            ui4_evt_code,
                              UINT32            ui4_data)
{
    if(e_nfy_cond == IOM_NFY_COND_BTN_DOWN &&
    (IOM_GET_EVT_GRP_ID(ui4_evt_code) == BTN_WIDGET))
    {
        if(wfd_view_get_current_view()!=WFD_VIEW_PLAY)
        {
            wfd_app_amb_pause();
        }
    }

    return;
}
static INT32 wfd_app_init_fct(const CHAR* ps_name, HANDLE_T h_app)
{
    IRRC_SETTING_T  t_irrc_setting;
    if(t_g_wfd_main.e_wfd_cond != WFD_COND_NOT_INIT)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    if(_wfd_init_svctx() != WFDR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }

    int i4_ret = WFDR_FAIL;

    c_memset(&t_g_wfd_main, 0, sizeof(WFD_MAIN_T));
    t_g_wfd_main.h_app = h_app;

    /* init wfd lib */
    i4_ret = a_wfd_device_info_init();
    if(i4_ret != WFDR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__, i4_ret));
        return WFDR_FAIL;
    }

    /* register widget callback function */
    i4_ret = c_wgl_register(_wfd_nfy_wgl);
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return AEER_FAIL;
    }
    /* set widget MSG delay */
    i4_ret = c_wgl_set_delay_tolerance(MAX_WIDGET_MSG_DELAY_TOLERANCE);

    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return AEER_FAIL;
    }

    /* init the widgets */
    i4_ret = wfd_view_init();
    if(i4_ret != AEER_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return AEER_FAIL;
    }
    wfd_p2p_init();
    t_g_wfd_main.connect_idx = -1;
    t_g_wfd_main.e_p2p_conn_sta = WFD_P2P_CONN_END;
    t_g_wfd_main.e_rtsp_conn_sta = WFD_RTSP_CONN_END;
    t_g_wfd_main.e_p2p_sta = WFD_P2P_END;
    t_g_wfd_main.e_wfd_cond = WFD_COND_PAUSE;
    t_g_wfd_main.b_enable = FALSE;
    t_g_wfd_main.b_ip_get = FALSE;

    wfd_reg_icl();
    wfd_set_device_remove_listen(); //temp remove for resume will see connect
    i4_ret = c_timer_create(&t_g_wfd_main.h_ip_timer);
    WFD_DBG_ERR_EX(i4_ret,OSR_OK);
    /* Register IOM */
    c_memset (& t_irrc_setting, 0, sizeof (IRRC_SETTING_T));
    t_irrc_setting.ui8_evt_grp_mask         = KEY_GROUP_ALL;  /* All key */
    t_irrc_setting.t_rpt_evt_itvl.ui2_1st   = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
    t_irrc_setting.t_rpt_evt_itvl.ui2_other = IOM_ZERO_RPT_EVT_ITVL; /* No repeat key */
    t_irrc_setting.b_notify_raw_data        = TRUE;
    i4_ret = c_iom_open (IOM_DEV_TYPE_IN_IRRC,
                         IOM_DEV_ID_ANY,
                         NULL,
                         (VOID*) &t_irrc_setting,
                         NULL,
                         _wfd_iom_nfy_fct,
                         &t_g_wfd_main.h_iom);

    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    return 0;
}

static VOID _wfd_app_timer_notify_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3, VOID* pv_tag4)
{
    UINT32 ui4_temp = (UINT32)pv_tag1;
    if(ui4_temp == 0)
    {
        if(wfd_p2p_try_to_find_ip() != WFDR_OK && i4_get_ip_count < 20)
        {
            WFD_DBG_LOG_EX("app_timer get_ip",i4_get_ip_count);
            i4_get_ip_count++;
            c_timer_start (t_g_wfd_main.h_ip_timer,
                           1000,
                           X_TIMER_FLAG_ONCE,
                           _wfd_app_timer_nfy_fct,
                           NULL);
            return;
        }

        if(i4_get_ip_count == 20)
        {
            wfd_p2p_disconnect();
        }
        i4_get_ip_count = 0;
        c_timer_stop(t_g_wfd_main.h_ip_timer);
    }
    else if(ui4_temp == 1)
    {
        i4_start_rtsp++;
        if(i4_start_rtsp < 5 && b_rtsp_start == FALSE)
        {
            WFD_CMD_CONT_T t_cmd;
            t_cmd.e_cmd = WFD_CMD_START_RTSP;
            t_cmd.pv_param = NULL;
            wfd_view_send_cmd(t_cmd);
        }
    }
    return;
}

static VOID _wfd_app_timer_nfy_fct(HANDLE_T h_timer, VOID* pv_tag)
{
    if (h_timer == t_g_wfd_main.h_ip_timer)
    {
        wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_app_timer_notify_hdlr, pv_tag,
                        NULL,NULL,NULL);
    }

    return;
}


static VOID _wfd_deinit_svctx(VOID)
{
    return;
    /* close main service context */
    if(t_g_wfd_main.h_main_svctx)
    {
        c_svctx_close(t_g_wfd_main.h_main_svctx);
        t_g_wfd_main.h_main_svctx = NULL_HANDLE;
    }

    /* close sub service context */
    if(t_g_wfd_main.h_sub_svctx)
    {
        c_svctx_close(t_g_wfd_main.h_sub_svctx);

        t_g_wfd_main.h_sub_svctx = NULL_HANDLE;
    }

#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
    /**/

    if(t_g_wfd_main.h_mnbypass_svctx)
    {
        c_svctx_close(t_g_wfd_main.h_mnbypass_svctx);
        t_g_wfd_main.h_mnbypass_svctx = NULL_HANDLE;
    }

    if(t_g_wfd_main.h_tvbypass_svctx)
    {
        c_svctx_close(t_g_wfd_main.h_tvbypass_svctx);

        t_g_wfd_main.h_tvbypass_svctx = NULL_HANDLE;
    }
#endif

#ifdef APP_NAV_REC_SUPPORT
    /**/
    if(t_g_wfd_main.h_rec_svctx)
    {
        c_svctx_close(t_g_wfd_main.h_rec_svctx);

        t_g_wfd_main.h_rec_svctx = NULL_HANDLE;
    }
#endif

}

static INT32 wfd_app_exit_fct(HANDLE_T h_app, APP_EXIT_MODE_T e_exit_mode)
{
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));

    if(t_g_wfd_main.e_wfd_cond == WFD_COND_NOT_INIT)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_UNKNOWN_MSG;
    }
    if(t_g_wfd_main.h_iom!=NULL_HANDLE)
    {
        c_iom_close (t_g_wfd_main.h_iom);
        t_g_wfd_main.h_iom=NULL_HANDLE;
    }
    WFD_RET_ON_ERR(wfd_view_deinit());
    _wfd_deinit_svctx();
    c_memset(&t_g_wfd_main, 0, sizeof(WFD_MAIN_T));
    return 0;
}

WFD_COND_T wfd_app_get_wfd_cond(VOID)
{
   return  t_g_wfd_main.e_wfd_cond;
}

extern VOID wfd_app_disconnect_rtsp(VOID)
{
    wfd_rtsp_stop();
    wfd_view_toggle_show_view(wfd_view_get_current_view(),FALSE,FALSE);
    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);
}

static INT32 wfd_app_pause_fct(HANDLE_T h_app)
{
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
#ifdef APP_MENU_WFD_COEXIST
    b_input_src_show = FALSE;

    CHAR                        s_app_name[APP_NAME_MAX_LEN] = {0};
    INT32                       i4_ret;
    i4_ret = a_am_get_next_active_app (s_app_name);
    if ((AMR_OK == i4_ret) && (0 == c_strcmp (s_app_name, MENU_NAME)))
    {
        wfd_view_toggle_show_view(wfd_view_get_current_view(),FALSE,FALSE);
        t_g_wfd_main.e_wfd_cond = WFD_COND_PAUSED_WAIT_SVC;
        a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);
        return WFDR_OK;
    }
#endif
    b_g_resume_wfd_directly = FALSE;
    wfd_rtsp_stop();
    wfd_view_toggle_show_view(wfd_view_get_current_view(),FALSE,FALSE);
    t_g_wfd_main.e_wfd_cond = WFD_COND_PAUSE;
    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);
    return WFDR_OK;
}

static INT32 wfd_app_resume_fct(HANDLE_T h_app)
{
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,e_wfd_cond=%d,rtsp_sta=%d\n",
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                t_g_wfd_main.e_wfd_cond,
                wfd_app_get_rtsp_conn_sta()));
#ifdef APP_MENU_WFD_COEXIST
    b_input_src_show = FALSE;
    if(WFD_COND_PAUSED_WAIT_SVC == t_g_wfd_main.e_wfd_cond)
    {
        if ((WFD_RTSP_CONN_START != wfd_app_get_rtsp_conn_sta())
            &&(WFD_RTSP_CONN_PLAY != wfd_app_get_rtsp_conn_sta()))
        {
            t_g_wfd_main.e_wfd_cond = WFD_COND_PAUSE;
            return a_amb_resume_app("navigator");
        }

        b_input_src_show = TRUE;
        wfd_view_set_current_view(WFD_VIEW_PLAY);
        WFD_RET_ON_ERR(wfd_view_toggle_show_view(wfd_view_get_current_view(),TRUE,TRUE));
        a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, TRUE);
        t_g_wfd_main.e_wfd_cond = WFD_COND_RESUME;
    }
    else
#endif
    {
        /* miracast connect from other app which like navigator */
        if (b_g_resume_wfd_directly)
        {
            wfd_view_set_current_view(WFD_VIEW_PLAY);
            WFD_RET_ON_ERR(wfd_view_toggle_show_view(wfd_view_get_current_view(),TRUE,TRUE));
            a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, TRUE);
            t_g_wfd_main.e_wfd_cond = WFD_COND_RESUME;
            return 0;
        }

        wfd_view_main_set_refind(TRUE);
        WFD_RET_ON_ERR(wfd_view_toggle_show_view(WFD_VIEW_MAIN,TRUE,TRUE));
        a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, TRUE);
        t_g_wfd_main.e_wfd_cond = WFD_COND_RESUME;
        if(TRUE == wfd_p2p_get_auto_conn_status())
        {
            wfd_p2p_set_auto_conn_status(FALSE);

            /* DTV00535523 */
            /* #if 0 --> Don't display the confirm dialog(Yes/Exit) when the same WFD device second time connect to TV. */
            /* #if 1 --> Still display the confirm dialog(Yes/Exit) when the same WFD device second time connect to TV. */
            #if 0
            wfd_main_send_msg_to_view(WFD_MSG_P2P_NEG_REQ, NULL);
            #else
            {
                WFD_CMD_CONT_T t_cmd;
                t_cmd.e_cmd = WFD_CMD_PBC_ACCEPT;
                t_cmd.pv_param = NULL;
                wfd_view_send_cmd(t_cmd);
            }
            #endif
        }
    }

    return WFDR_OK;
}

#ifdef APP_MENU_WFD_COEXIST
/*----------------------------------------------------------------------------
 * Name
 *      wfd_app_system_key_fct
 * Description
 *      The API is used to override the default RCU key handler. If pf_handler
 *      is NULL, it will change to use system default key handler.
 * Input arguments
 *      pf_handler      the key handler
 * Output arguments
 *      None
 * Returns
 *      NAVR_OK
 *      NAVR_FAIL
 *----------------------------------------------------------------------------*/
static BOOL wfd_app_system_key_fct(
    UINT32     ui4_evt_code)
{
    UINT32 ui4_key_code = IOM_GET_EVT_GRP_ID (ui4_evt_code);

    if (ui4_key_code == BTN_MENU)
    {
        WFD_WIDGET_MSG_T   t_msg;
        t_msg.ui4_msg   = WGL_MSG_KEY_DOWN;
        t_msg.pv_param1 = (VOID*)BTN_MENU;
        t_msg.pv_param2 = (VOID*)NULL;

        _wfd_nfy_wgl(t_msg.ui4_msg, t_msg.pv_param1, t_msg.pv_param2);

        return FALSE;
    }
    else
    {
        return TRUE;
    }
}
#endif

static INT32 wfd_app_process_msg_fct(HANDLE_T h_app,
    UINT32                      ui4_type,
    const VOID*                 pv_msg,
    SIZE_T                      z_msg_len,
    BOOL                        b_paused)
{
    INT32               i4_ret;

    switch (ui4_type)
    {
        case WFD_MSG_SEND_CONTEXT://send msg
            {
                WFD_SEND_CTX_T*    pt_msg = (WFD_SEND_CTX_T*)pv_msg;

                /*invoke command handler*/
                if(pt_msg->pf_event_handler)
                {
                    pt_msg->pf_event_handler(pt_msg->pv_param1,
                                             pt_msg->pv_param2,
                                             pt_msg->pv_param3,
                                             pt_msg->pv_param4);
                }
            }
            break;

        case WFD_MSG_WGL_NFY: /* widget notifications */
        {
            WFD_WIDGET_MSG_T*    pt_wgl_msg;
            UINT32              ui4_key_code;

            pt_wgl_msg = (WFD_WIDGET_MSG_T*) pv_msg;
            ui4_key_code = (UINT32)pt_wgl_msg->pv_param1;
    #ifdef APP_MENU_WFD_COEXIST
            if(pt_wgl_msg->ui4_msg == WGL_MSG_KEY_DOWN || pt_wgl_msg->ui4_msg == WGL_MSG_KEY_REPEAT)
            {
                switch(ui4_key_code)
                {
                    case BTN_VOL_UP:
                    case BTN_VOL_DOWN:
                    case BTN_MUTE:
                    {
                        WFD_DBG_LOG(ui4_key_code);
                        /* Call default key handler. */
                        a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
                        wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_icl_nfy_hdlr, NULL, NULL,NULL,NULL);
                        return WFDR_OK;
                    }

                    case BTN_MENU:
                    {
                        WFD_DBG_LOG_EX("MENU here",ui4_key_code);

                        if(wfd_view_get_current_view() == WFD_VIEW_PLAY)
                        {
                            a_amb_resume_app(MENU_NAME);
                        }

                        return WFDR_OK;
                    }

                    case BTN_INPUT_SRC:
                    {
                        WFD_DBG_LOG_EX("Input source here\n",ui4_key_code);

                        if(wfd_view_get_current_view() == WFD_VIEW_PLAY)
                        {
                            if(FALSE == b_input_src_show)
                            {
                                b_input_src_show = TRUE;

                                INT32   i4_ret;
                                CHAR    s_app_name[APP_NAME_MAX_LEN];

                                i4_ret = a_am_get_active_app(s_app_name);
                                if (AMR_OK == i4_ret && 0 == c_strcmp (s_app_name, MENU_NAME))
                                {
                                    a_amb_pause_app(MENU_NAME);
                                }
                            }

                            wfd_view_toggle_show_view(wfd_view_get_current_view(),FALSE,FALSE);

                            /* Call default key handler. */
                            a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
                        }
                        return WFDR_OK;
                    }

                    case BTN_CURSOR_UP:
                    case BTN_SELECT:
                    case BTN_CURSOR_DOWN:
                    case BTN_EXIT:
                    {
                        if(wfd_view_get_current_view() == WFD_VIEW_PLAY)
                        {
                            if(TRUE == b_input_src_show)
                            {
                                if(BTN_EXIT == ui4_key_code)
                                {
                                    b_input_src_show = FALSE;
                                }

                                /* Call default key handler. */
                                a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
                                return WFDR_OK;
                            }
                        }
                        break;
                    }

                    default:
                    {
                        break;
                    }
                }
            }
    #else
            if(pt_wgl_msg->ui4_msg == WGL_MSG_KEY_DOWN || pt_wgl_msg->ui4_msg == WGL_MSG_KEY_REPEAT)
            {
               if(ui4_key_code == BTN_VOL_UP || ui4_key_code == BTN_VOL_DOWN || ui4_key_code == BTN_MUTE)
                {
                    WFD_DBG_LOG(ui4_key_code);
                    /* Call default key handler. */
                    a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key_code, NULL);
                     wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_icl_nfy_hdlr, NULL, NULL,NULL,NULL);
                    return WFDR_OK;
                }
            }

            if(pt_wgl_msg->ui4_msg == WGL_MSG_KEY_DOWN || pt_wgl_msg->ui4_msg == WGL_MSG_KEY_REPEAT)
            {
               if(ui4_key_code == BTN_ROOT_MENU)
                {
                    WFD_DBG_LOG_EX("MENU here",ui4_key_code);
                    if(t_g_wfd_main.e_rtsp_conn_sta == WFD_RTSP_CONN_START ||t_g_wfd_main.e_rtsp_conn_sta == WFD_RTSP_CONN_PAUSE )
                    {
                        wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_STOP);
                        wfd_rtsp_stop();
                    }

                    return WFDR_OK;
                }
            }
    #endif

            /* dispatch message to Widget Library */
            i4_ret = c_wgl_dispatch_event (pt_wgl_msg->ui4_msg,
                                           pt_wgl_msg->pv_param1,
                                           pt_wgl_msg->pv_param2);

            if ((i4_ret != WGLR_OK) && (i4_ret != WGLR_EVENT_IGNORED))
            {
                DBG_ERROR(("<WFD> ERR: dispatch event to wgl failed = %d\n\r",i4_ret));
            }
            break;
        }

        default:
            break;
    }
    return WFDR_OK;
}


VOID a_wfd_init(AMB_REGISTER_INFO_T * pt_reg)
{
    int i4_ret = 0;
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
    c_memset(&t_g_wfd_main, 0, sizeof(WFD_MAIN_T));
    /* Application can only use middleware's c_API */
    c_strcpy(pt_reg->s_name,WFD_NAME);

    pt_reg->t_fct_tbl.pf_init                   = wfd_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit                   = wfd_app_exit_fct;
    pt_reg->t_fct_tbl.pf_resume                 = wfd_app_resume_fct;
    pt_reg->t_fct_tbl.pf_pause                  = wfd_app_pause_fct;
    pt_reg->t_fct_tbl.pf_process_msg            = wfd_app_process_msg_fct;
    #ifdef APP_MENU_WFD_COEXIST
    pt_reg->pf_system_key_cb                    = wfd_app_system_key_fct;
    #endif
    pt_reg->t_desc.ui8_flags                    = ~((UINT64)0);
    pt_reg->t_desc.t_thread_desc.z_stack_size   = 8*1024;
    pt_reg->t_desc.t_thread_desc.ui1_priority   = 200;
    pt_reg->t_desc.t_thread_desc.ui2_num_msgs   = 20;
    pt_reg->t_desc.ui4_app_group_id             = 0;
    pt_reg->t_desc.ui4_app_id                   = 0;
    pt_reg->t_desc.t_max_res.z_min_memory       = 0;
    pt_reg->t_desc.t_max_res.z_max_memory       = 1024*16;
    pt_reg->t_desc.t_max_res.ui8_max_files_size = 0;
    pt_reg->t_desc.t_max_res.ui2_max_files      = 0;
    pt_reg->t_desc.t_max_res.ui2_max_handles    = 128;
    pt_reg->t_desc.t_max_res.ui2_max_threads    = 1;
    pt_reg->t_desc.t_max_res.ui2_max_semaphores = 4;
    pt_reg->t_desc.t_max_res.ui2_max_msg_queues = 1;
    pt_reg->t_desc.t_max_res.ui2_max_nb_msgs    = 20;
    pt_reg->t_desc.t_max_res.ui2_max_msg_size   = 64;
    pt_reg->t_desc.ui2_msg_count                = 20;
    pt_reg->t_desc.ui2_max_msg_size             = 64;
    pt_reg->ui2_key_num                         = 0;

    i4_ret = wfd_cli_attach_cmd_tbl();
    if (i4_ret != CLIR_NOT_INIT && i4_ret != CLIR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return ;
    }
}

UINT16 wfd_get_dbg_level(VOID)
{
    if (a_cfg_custom_get_wfd_support()==TRUE)
    {
        return ui2_dbg_level;
    }
    else
    {
        return 0;
    }
}

VOID wfd_set_dbg_level(UINT16   ui2_db_level)
{
    ui2_dbg_level = ui2_db_level;
}

BOOL wfd_app_is_active(VOID)
{
    CHAR s_app_name[APP_NAME_MAX_LEN+1] = {'\0'};
    int i4_ret = 0;
    i4_ret = a_am_get_active_app(s_app_name);
    if (i4_ret == AMBR_OK && c_strcmp(s_app_name, WFD_NAME) == 0)
        return   TRUE;
    return FALSE;
}

WFD_P2P_STA_T  wfd_app_get_p2p_sta(VOID)
{
    return t_g_wfd_main.e_p2p_sta;
}

WFD_P2P_CONN_STA_T  wfd_app_get_p2p_conn_sta(VOID)
{
    return t_g_wfd_main.e_p2p_conn_sta;
}

WFD_RTSP_CONN_STA_T  wfd_app_get_rtsp_conn_sta(VOID)
{
    return t_g_wfd_main.e_rtsp_conn_sta;
}


INT32  wfd_app_get_conn_idx(VOID)
{
    return t_g_wfd_main.connect_idx;
}


VOID  wfd_app_set_p2p_sta(WFD_P2P_STA_T e_sta)
{
     t_g_wfd_main.e_p2p_sta = e_sta;
     return;
}

VOID  wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_STA_T e_sta)
{
     t_g_wfd_main.e_p2p_conn_sta = e_sta;
      return;
}

VOID  wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_STA_T e_sta)
{
     t_g_wfd_main.e_rtsp_conn_sta = e_sta;
      return;
}


INT32 wfd_app_get_conn_device_info(WFD_DEVICE_INFO_T * pt_info)
{
    if(t_g_wfd_main.connect_idx <0 || pt_info == NULL)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_FAIL;
    }
    WFD_RET_ON_ERR(wfd_p2p_get_device_info(WFD_DEV_ALL, (void *)pt_info, t_g_wfd_main.connect_idx));
    WFD_RET_ON_ERR(wfd_p2p_get_connect_ip(pt_info->ps_device_ip));
    return WFDR_OK;
}

INT32 wfd_app_get_device_info(WFD_DEVICE_INFO_T * pt_info,UINT32 index)
{
    WFD_DBG_LOG(index);
    WFD_RET_ON_ERR(wfd_p2p_get_device_info(WFD_DEV_ALL, (void *)pt_info, (INT32)index));
    return WFDR_OK;
}

VOID wfd_main_cmd_do(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    WFD_CMD_T e_cmd = (WFD_CMD_T)(UINT32)pv_param1;
    INT32 i4_ret;
    WFD_DBG_LOG(e_cmd);
    switch(e_cmd)
    {

        case WFD_CMD_VIEW_DO_MSG:
        {
             WFD_MSG_T e_msg = (WFD_MSG_T)(UINT32)pv_param2;
            wfd_main_send_msg_to_view(e_msg,NULL);
            break;
        }

        case WFD_CMD_RESUME:
        {
            if(wfd_app_get_wfd_cond() == WFD_COND_PAUSE)
            {
                wfd_app_amb_resume();
            }
            break;
        }

        case WFD_CMD_PAUSE:
        {
            WFD_VIEW_MSG_T e_view_sub_msg=(WFD_VIEW_MSG_T)(UINT32)(pv_param2);

            if(wfd_app_get_wfd_cond() == WFD_COND_RESUME)
            {
                wfd_app_amb_pause();
            }

            if (a_cfg_custom_get_wifi_remote_support())
            {
                if( e_view_sub_msg== WFD_VIEW_MSG_EXIT_WFD )
                {
                    if (a_cfg_custom_get_wifi_remote_support())
                    {
                      a_menu_shortcut_link(MENU_SHORT_CUT_DEVICE_SETTING);
                    }
                }
            }

            break;
        }
        case WFD_CMD_ENABLE:
        {
            wfd_app_set_p2p_sta(WFD_P2P_ENABLING);
            wfd_main_send_msg_to_view(WFD_MSG_P2P_START_ENABLE,NULL);
            i4_ret = wfd_p2p_enable_wifi_display();
            if(i4_ret < 0)
            {
                wfd_app_set_p2p_sta(WFD_P2P_DISABLED);
                wfd_main_send_msg_to_view(WFD_MSG_P2P_ENABLE_FAILED,NULL);
            }

            break;
        }

        case WFD_CMD_DISABLE:
        {
            wfd_app_set_p2p_sta(WFD_P2P_DISABLING);
            wfd_main_send_msg_to_view(WFD_MSG_P2P_START_DISABLE,NULL);
            i4_ret = wfd_p2p_disable_wifi_display();
            if(i4_ret != WFDR_OK)
            {
                DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                            __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
            }
            wfd_app_set_p2p_sta(WFD_P2P_DISABLED);
            wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_DISCONNECT);
            t_g_wfd_main.connect_idx = -1;
            wfd_main_send_msg_to_view(WFD_MSG_P2P_DISABLED,NULL);

            break;
         }

        case WFD_CMD_FIND:
        {
            i4_ret = wfd_p2p_find();

            if(i4_ret == WFDR_OK)
            {
                wfd_main_send_msg_to_view(WFD_MSG_FIND,NULL);
            }

            break;
         }

        case WFD_CMD_STOP_FIND:
        {
            i4_ret = wfd_p2p_stop_find();
            if(i4_ret == WFDR_OK)
            {
                wfd_main_send_msg_to_view(WFD_MSG_STOP_FIND,NULL);
            }

            break;
        }

        case WFD_CMD_PBC:
        {
            INT32 index = wfd_view_return_connect_idx();
            i4_ret = wfd_p2p_connect_pbc(index);
            if(i4_ret == WFDR_OK)
            {
                t_g_wfd_main.e_p2p_conn_sta = WFD_P2P_CONN_CONNECTING;

                c_timer_start(t_g_wfd_view_main.h_timer_time_out,
                              1000,
                              X_TIMER_FLAG_ONCE,
                              wfd_app_time_out_timer_nfy_func,
                              NULL);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_TO_STA,NULL);
            }
            else
            {
                WFD_DBG_LOG_EX("CONN_FAIL",i4_ret);

                wfd_main_send_msg_to_view(WFD_MSG_VIEW_MSG_TRY_CONN_FAIL,NULL);
            }
            break;
        }

        case WFD_CMD_PBC_ACCEPT:
        {
            i4_ret = wfd_p2p_pbc_request_accept();
            if(i4_ret == WFDR_OK)
            {
                t_g_wfd_main.e_p2p_conn_sta = WFD_P2P_CONN_CONNECTING;

                c_timer_start(t_g_wfd_view_main.h_timer_time_out,
                              1000,
                              X_TIMER_FLAG_ONCE,
                              wfd_app_time_out_timer_nfy_func,
                              NULL);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_TO_STA,NULL);
            }
            else
            {
                WFD_DBG_LOG_EX("CONN_FAIL",i4_ret);

                wfd_main_send_msg_to_view(WFD_MSG_VIEW_MSG_TRY_CONN_FAIL,NULL);
            }
            break;
        }

        case WFD_CMD_SHOW_PIN:
        {
            INT32 index = wfd_view_return_connect_idx();
            i4_ret = wfd_p2p_request_as_display_of(index);
            if(i4_ret == WFDR_OK)
            {
                t_g_wfd_main.e_p2p_conn_sta = WFD_P2P_CONN_CONNECTING;

                c_timer_start(t_g_wfd_view_main.h_timer_time_out,
                              1000,
                              X_TIMER_FLAG_ONCE,
                              wfd_app_time_out_timer_nfy_func,
                              NULL);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_SHOW_TO_PIN,NULL);
            }
            else
            {
                WFD_DBG_LOG_EX("CONN_FAIL",i4_ret);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_MSG_TRY_CONN_FAIL,NULL);
            }

            break;
        }
        case WFD_CMD_ENTER_PIN:
        {
            INT32 index = wfd_view_return_connect_idx();
            i4_ret = wfd_p2p_request_as_keypad_of(index);
            if(i4_ret == WFDR_OK)
            {
                t_g_wfd_main.e_p2p_conn_sta = WFD_P2P_CONN_CONNECTING;

                c_timer_start(t_g_wfd_view_main.h_timer_time_out,
                              1000,
                              X_TIMER_FLAG_ONCE,
                              wfd_app_time_out_timer_nfy_func,
                              NULL);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_ENTER_TO_PIN,NULL);
            }

            else
            {
                WFD_DBG_LOG_EX("CONN_FAIL",i4_ret);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_MSG_TRY_CONN_FAIL,NULL);
            }
            break;
        }
        case WFD_CMD_CANCEL_CONNECT:
        {
            wfd_main_send_msg_to_view(WFD_MSG_VIEW_DISCONNECT_P2P,NULL);
            wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_DISCONNECTING);
            i4_ret = wfd_p2p_connect_cancel();

            if(i4_ret == WFDR_OK)
            {
                wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_DISCONNECT);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_DISCONNECT_P2P_OK,NULL);
            }
            else
            {
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_DISCONNECT_P2P_FAIL,NULL);
            }

            break;
        }

        case WFD_CMD_DISCONNECT_P2P:
        {
            wfd_main_send_msg_to_view(WFD_MSG_VIEW_DISCONNECT_P2P,NULL);
            wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_DISCONNECTING);
            i4_ret = wfd_p2p_disconnect();

            if(i4_ret == WFDR_OK)
            {
                wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_DISCONNECT);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_DISCONNECT_P2P_OK,NULL);
            }
            else
            {
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_DISCONNECT_P2P_FAIL,NULL);
            }

            break;
        }
        case WFD_CMD_STOP_TIMER:
        {
            c_timer_stop(t_g_wfd_main.h_ip_timer);
            break;
        }
        case WFD_CMD_STOP_RTSP:
        {
            wfd_main_send_msg_to_view(WFD_MSG_VIEW_STOP_RTSP,NULL);
            wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_STOP);
            i4_ret = wfd_rtsp_stop();
            c_timer_stop(t_g_wfd_main.h_ip_timer);
            if(i4_ret == WFDR_OK)
            {
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_STOP_RTSP_OK,NULL);
            }
            else
            {
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_STOP_RTSP_FAIL,NULL);
            }

            break;
        }

        case WFD_CMD_START_RTSP:
        {
            _wfd_view_do_msg((VOID*)(UINT32)WFD_MSG_VIEW_START_RTSP,NULL,NULL,NULL);
            i4_ret = wfd_rtsp_start_rtsp();
            if(i4_ret == WFDR_OK)
            {
                b_rtsp_start = TRUE;
                wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_START);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_START_RTSP_OK,NULL);
                c_timer_stop(t_g_wfd_main.h_ip_timer);
            }
            else
            {
                b_rtsp_start = FALSE;
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_START_RTSP_FAIL,NULL);
 /*               c_timer_start(t_g_wfd_main.h_ip_timer,
                               3000,
                               X_TIMER_FLAG_ONCE,
                               _wfd_app_timer_nfy_fct,
                               (VOID*)(UINT32)1);*/
            }

            break;
        }

        case WFD_CMD_PIN_CONNECT:
        {
            INT32 index = wfd_view_return_connect_idx();
            wfd_p2p_set_enter_pin((CHAR*)pv_param2);
            i4_ret = wfd_p2p_connect_pin(index);
            if(i4_ret == WFDR_OK)
            {
                t_g_wfd_main.e_p2p_conn_sta = WFD_P2P_CONN_CONNECTING;
                c_timer_start(t_g_wfd_view_main.h_timer_time_out,
                              1000,
                              X_TIMER_FLAG_ONCE,
                              wfd_app_time_out_timer_nfy_func,
                              NULL);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_TO_STA,NULL);
            }

            break;
        }

        case WFD_CMD_PIN_GET:
        {
            t_g_wfd_main.e_p2p_conn_sta = WFD_P2P_CONN_CONNECTING;
            c_timer_start(t_g_wfd_view_main.h_timer_time_out,
                          1000,
                          X_TIMER_FLAG_ONCE,
                          wfd_app_time_out_timer_nfy_func,
                          NULL);
            wfd_main_send_msg_to_view(WFD_MSG_VIEW_TO_STA,NULL);
            break;
        }

        case WFD_CMD_PAUSE_RTSP:
        {
            i4_ret = wfd_rtsp_pause();
            if(i4_ret == WFDR_OK)
            {
                wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_PAUSE);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_MSG_PAUSED,NULL);
            }
            else
            {
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_MSG_PAUSE_FAIL,NULL);
            }
            break;
        }

        case WFD_CMD_PLAY:
        {
            i4_ret = wfd_rtsp_play();
            if(i4_ret == WFDR_OK)
            {
                wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_PLAY);
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_MSG_PLAYD,NULL);
            }
            else
            {
                wfd_main_send_msg_to_view(WFD_MSG_VIEW_MSG_PLAY_FAIL,NULL);
            }
            break;
        }
        default:
            break;
    }
    return;
}

VOID wfd_main_handle_msg(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    WFD_MSG_T e_msg = (WFD_MSG_T)(UINT32)pv_param1;
    VOID * param = NULL;
    DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,e_msg=%d\n",
                __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                e_msg));
    switch(e_msg)
    {
        case WFD_MSG_P2P_DEVICE_FOUND:
        {
           t_g_wfd_main.connect_idx = wfd_p2p_get_connect_index();
           if(t_g_wfd_main.connect_idx < 0)
           {
               DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,connect_idx=%d\n",
                            __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                            t_g_wfd_main.connect_idx));
           }
           break;
        }
        case WFD_MSG_P2P_DEVICE_LOST:
        {
            t_g_wfd_main.connect_idx = wfd_p2p_get_connect_index();
            if( t_g_wfd_main.connect_idx < 0)
            {
                DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,connect_idx=%d\n",
                            __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                            t_g_wfd_main.connect_idx));
                return;
            }
            break;
        }
        case WFD_MSG_AP_STA_CONNECTED:
        {
            wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_CONNECTED);
            t_g_wfd_main.connect_idx = wfd_p2p_get_connect_index();
            if( t_g_wfd_main.connect_idx < 0)
            {
                DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,connect_idx=%d\n",
                            __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                            t_g_wfd_main.connect_idx));
                return;
            }

            c_timer_start (t_g_wfd_main.h_ip_timer,
                           1000,
                           X_TIMER_FLAG_ONCE,
                           _wfd_app_timer_nfy_fct,
                           (VOID*)(UINT32)0);
            break;
        }
        case WFD_MSG_AP_STA_DISCONNECTED:
        {
            wfd_rtsp_stop();
            wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_DISCONNECT);
            t_g_wfd_main.b_ip_get = FALSE;
            t_g_wfd_main.connect_idx = -1;
            break;
        }
        case WFD_MSG_P2P_IP_GET:
        {
            t_g_wfd_main.b_ip_get = TRUE;
            i4_get_ip_count = 0;
            c_timer_stop(t_g_wfd_main.h_ip_timer);

            WFD_CMD_CONT_T t_cmd;
            t_cmd.e_cmd = WFD_CMD_START_RTSP;
            t_cmd.pv_param = NULL;
            wfd_view_send_cmd(t_cmd);
            i4_start_rtsp = 0;
            break;
        }
        case WFD_MSG_P2P_ENABLE_OK:
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
            wfd_app_set_p2p_sta(WFD_P2P_ENABLED);
            wfd_main_send_msg_to_view(WFD_MSG_P2P_ENABLE_OK,NULL);
            break;
        }
        case WFD_MSG_P2P_ENABLE_FAILED:
        {
            wfd_app_set_p2p_sta(WFD_P2P_DISABLED);
            wfd_main_send_msg_to_view(WFD_MSG_P2P_ENABLE_FAILED,NULL);
            break;
        }
        case WFD_MSG_P2P_SHOW_PIN_REQ:
        case WFD_MSG_P2P_SHOW_PIN:
        {
            param = pv_param2;//pin code
            break;
        }

        case WFD_MSG_RTSP_TEARDOWN:
        {
            wfd_rtsp_stop();
            wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_STOP);
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
            break;
        }

        case WFD_MSG_P2P_NEG_REQ:
        {
            wfd_p2p_enable_auto_conn_by_device(e_msg, NULL);
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
            return ;
        }

        case WFD_MSG_P2P_PBC_REQ://no need to accept request pcb notify.
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
            return ;
        }
        default:
        {
            break;
        }
    }
    wfd_main_send_msg_to_view(e_msg, param);
    return;
}

static INT32 _wfd_icl_nfy_fct(UINT16              ui2_nfy_id,
                              VOID*               pv_tag,
                              ICL_NOTIFY_DATA_T*  pt_notify_data)
{
    wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_icl_nfy_hdlr, NULL, NULL,NULL,NULL);
    return WFDR_OK;
}


INT32 wfd_reg_icl(VOID)
{
    INT32 i4_ret;
    i4_ret = a_icl_notify_reg(ICL_GRPID_CEC,
                              ICL_PRIORITY_DEFAULT,
                              NULL,
                              NULL,
                              _wfd_icl_nfy_fct,
                              &t_g_wfd_main.ui2_icl_nfy_id);
    if (i4_ret != ICLR_OK)
    {
        return i4_ret;
    }
    return WFDR_OK;
}

INT32 wfd_unreg_icl(VOID)
{

    a_icl_notify_unreg(t_g_wfd_main.ui2_icl_nfy_id);

    return WFDR_OK;
}

//
static VOID _wfd_icl_nfy_hdlr(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    WFD_VOL_UPD_INFO_T  t_vol_info;
    UINT8               ui1_icl_val;
    SIZE_T              z_size;
    INT32               i4_ret;

    c_memset(&t_vol_info, 0, sizeof(WFD_VOL_UPD_INFO_T));

    z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                       &ui1_icl_val,
                       &z_size);
    if (ICLR_OK == i4_ret && ui1_icl_val == ICL_CEC_SAC_STATUS_ON)
    {
        t_vol_info.b_cec_sac = TRUE;
    }

    ui1_icl_val = 0;
    i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_AUD_STATUS),
                       &ui1_icl_val,
                       &z_size);
    if (ICLR_OK == i4_ret)
    {
        if(t_g_wfd_main.i1_cec_vol > ui1_icl_val)
        {
            t_vol_info.b_volume_up = FALSE;
            t_vol_info.b_volume_down = TRUE;
            i4_ret=a_tv_get_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                         (INT16*)&t_vol_info.i2_vol);
            WFD_DBG_ERR_EX(i4_ret,TVR_OK)
        }
        else if (t_g_wfd_main.i1_cec_vol < ui1_icl_val)
        {
            t_vol_info.b_volume_up = TRUE;
            t_vol_info.b_volume_down = FALSE;
            i4_ret=a_tv_get_vol(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL),
                         (INT16*)&t_vol_info.i2_vol);
            WFD_DBG_ERR_EX(i4_ret,TVR_OK)
        }
        else
        {
            t_vol_info.b_volume_up = FALSE;
            t_vol_info.b_volume_down = FALSE;
        }
        t_g_wfd_main.i1_cec_vol = ui1_icl_val;
    }

    wfd_main_send_msg_to_view(WFD_MSG_VOL_CHG,(VOID*)&t_vol_info);

    return;
}


INT32 wfd_event_send_context(
    WFD_SEND_RETRY_TYPE_T     e_retry_type,
    wfd_event_handler        pf_event_handler,
    VOID*                       pv_param1,
    VOID*                       pv_param2,
    VOID*                       pv_param3,
    VOID*                       pv_param4)
{
    WFD_SEND_CTX_T     t_swth_msg;

    if(NULL == pf_event_handler)
    {
        WFD_DBG_ERR(("pf_event_handler cannot be NULL.\r\n"));
        return WFDR_INV_ARG;
    }

    t_swth_msg.pf_event_handler = pf_event_handler;
    t_swth_msg.pv_param1 = pv_param1;
    t_swth_msg.pv_param2 = pv_param2;
    t_swth_msg.pv_param3 = pv_param3;
    t_swth_msg.pv_param4 = pv_param4;

    return _wfd_app_send_msg(t_g_wfd_main.h_app, WFD_MSG_SEND_CONTEXT, &t_swth_msg,
        sizeof(WFD_SEND_CTX_T),e_retry_type);
}

static INT32 _wfd_update_blue_mute(BOOL   b_reset)
{
    SVCTX_VIDEO_MUTE_INFO_T t_video_mute_info;
    INT32                   i4_ret;
    INT16                   i2_app_val;
    BOOL                    b_blue_mute;

    if(b_reset)
    {
        t_video_mute_info.b_enable          = TRUE;
        t_video_mute_info.t_color.ui1_red   = 0;
        t_video_mute_info.t_color.ui1_green = 0;
        t_video_mute_info.t_color.ui1_blue  = 0;

        b_blue_mute = TRUE;
    }
    else
    {
        i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE), &i2_app_val);
        if(APP_CFGR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }

        b_blue_mute = (BOOL)i2_app_val;
        if(b_blue_mute)
        {
            t_video_mute_info.b_enable          = TRUE;
            i4_ret = a_cfg_get_blue_mute_color(&t_video_mute_info.t_color.ui1_red,
                                               &t_video_mute_info.t_color.ui1_green,
                                               &t_video_mute_info.t_color.ui1_blue);
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                            __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                            i4_ret));
                return WFDR_FAIL;
            }
        }
    }

    /* blue mute */
    if(b_blue_mute)
    {
        i4_ret = c_svctx_set(t_g_wfd_main.h_main_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE_ATTR,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
        }

        i4_ret = c_svctx_set(t_g_wfd_main.h_sub_svctx,
                             SVCTX_COMMON_SET_VIDEO_MUTE_ATTR,
                             &t_video_mute_info,
                             sizeof(SVCTX_VIDEO_MUTE_INFO_T));
        if(SVCTXR_OK != i4_ret && SVCTXR_TIMEOUT != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
        }
    }

    return WFDR_OK;
}


INT32 wfd_free_video_resource(VOID)
{
    WFD_DBG_LOG(b_pause_tv);
    if(b_pause_tv)
    {
        return WFDR_OK;
    }
    VSH_REGION_INFO_T           t_dsp_region = {0};
    INT32                       i4_ret, i;
    SM_COMMAND_T                at_sm_cmds[4];
    SM_CMD_CODE_T               ae_cmd_code[2] = {SCC_CMD_CODE_VIDEO_NR, SCC_CMD_CODE_VIDEO_3D_NR};

    /*leave PIP/POP mode*/
    i4_ret = a_tv_set_mode(TV_MODE_TYPE_NORMAL);
    if(TVR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return WFDR_FAIL;
    }

    /*resize video to full screen, set main svctx to full display region*/
    t_dsp_region.ui4_width  = VSH_REGION_MAX_WIDTH;
    t_dsp_region.ui4_height = VSH_REGION_MAX_HEIGHT;
    i4_ret = c_svctx_set_stream_attr(t_g_wfd_main.h_main_svctx,
                                     ST_VIDEO,
                                     SM_VSH_SET_TYPE_DISP_REGION,
                                     &t_dsp_region,
                                     sizeof(VSH_REGION_INFO_T));
    if(SVCTXR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
    }

    /*disable NR and 3D NR*/
    at_sm_cmds[0].e_code        = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data    = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code        = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text     = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].u.ui2_data    = 0;        /*OFF*/
    at_sm_cmds[3].e_code        = SM_CMD_CODE_END;
    at_sm_cmds[3].u.ui4_data    = 0;
    for(i = 0; i < 2; i++)
    {
        at_sm_cmds[2].e_code    = ae_cmd_code[i];
        i4_ret = c_scc_comp_grp_set(at_sm_cmds);
        if(SMR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }
    }

    /*stop video*/
    i4_ret = c_svctx_sync_stop_svc(t_g_wfd_main.h_main_svctx, DEFAULT_STOP_SVC_TIMEOUT);
    if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return WFDR_FAIL;
    }

    /*stop video*/
    if(t_g_wfd_main.h_sub_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(t_g_wfd_main.h_sub_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }
    }

    /*stop video*/
#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
    if(t_g_wfd_main.h_mnbypass_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(t_g_wfd_main.h_mnbypass_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }
    }

    if(t_g_wfd_main.h_tvbypass_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(t_g_wfd_main.h_tvbypass_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }
    }
#endif

    /* Disable SCART bypass assocation */
    a_tv_set_scart_bypass_association(FALSE, FALSE);

    /* stop record */
#ifdef APP_NAV_REC_SUPPORT
    if(t_g_wfd_main.h_rec_svctx)
    {
        i4_ret = c_svctx_sync_stop_svc(t_g_wfd_main.h_rec_svctx, DEFAULT_STOP_SVC_TIMEOUT);
        if(SVCTXR_OK != i4_ret && SVCTXR_ALREADY_STOPPED != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            return WFDR_FAIL;
        }
    }
#endif

    /*disable blue mute*/
    _wfd_update_blue_mute(TRUE);

    /*use internal screen mode*/
    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, TRUE);

    /*For fix DTV00140629*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
    b_pause_tv = TRUE;
    return WFDR_OK;
}

static VOID _wfd_deinit_svl()
{
    /**/
    if(t_g_wfd_main.h_cable_svl)
    {
        c_svl_close(t_g_wfd_main.h_cable_svl);
        t_g_wfd_main.h_cable_svl = NULL_HANDLE;
    }

    if(t_g_wfd_main.h_air_svl)
    {
        c_svl_close(t_g_wfd_main.h_air_svl);
        t_g_wfd_main.h_air_svl = NULL_HANDLE;
    }
    return;
}

static INT32 _wfd_init_svl()
{
    INT32                       i4_ret;

    if (NULL_HANDLE == t_g_wfd_main.h_cable_svl)
    {
        i4_ret = c_svl_open(ATSC_CABLE_SVL_ID, NULL, NULL, &t_g_wfd_main.h_cable_svl);
        if(SVLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            t_g_wfd_main.h_cable_svl = NULL_HANDLE;
            return WFDR_FAIL;
        }
    }

    if (NULL_HANDLE == t_g_wfd_main.h_air_svl)
    {
        i4_ret = c_svl_open(ATSC_TRSTRL_SVL_ID, NULL, NULL, &t_g_wfd_main.h_air_svl);
        if(SVLR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
            t_g_wfd_main.h_air_svl = NULL_HANDLE;

            /*free allocated*/
            _wfd_deinit_svl();

            return WFDR_FAIL;
        }
    }

    return WFDR_OK;
}

INT32 wfd_set_video_srm_mode(SCC_VID_SRM_MODE_T e_mode)
{
    INT32               i4_ret = -1;
    SM_COMMAND_T        at_sm_cmds[3];
    HANDLE_T            h_scc_handle = NULL_HANDLE;

    /* create the scc handles */
    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;
    i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc_handle);
    if(i4_ret != SMR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return WFDR_FAIL;
    }

    i4_ret = c_scc_vid_set_srm_mode (h_scc_handle, e_mode);

    if (NULL_HANDLE != h_scc_handle)
    {
        c_scc_comp_close(h_scc_handle);
    }

    return i4_ret;
}

INT32 wfd_enable_mjc_effect(BOOL b_enable)
{
#ifdef APP_MJC_SUPPORT
    INT32               i4_ret = -1;
    SM_COMMAND_T        at_sm_cmds[3];
    HANDLE_T            h_scc = NULL_HANDLE;
    SCC_VID_MJC_T       t_mjc;
    DRV_CUST_OPERATION_INFO_T   t_op_info;
    SIZE_T                      z_size = sizeof(DRV_CUST_OPERATION_INFO_T), z_bool_size = sizeof(BOOL);
    BOOL                        b_mjc_enable;
    EXTMJC_TYPE_SET_OSD_MODE_T  t_set_osd_mode;

    /* create the scc handles */
    at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
    at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_VIDEO;
    at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
    at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
    at_sm_cmds[2].e_code = SM_CMD_CODE_END;
    at_sm_cmds[2].u.ui4_data = 0;
    i4_ret = c_scc_comp_open(at_sm_cmds, &h_scc);
    if(i4_ret != SMR_OK)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return WFDR_FAIL;
    }

    /*Get current MJC setting, and apply effect according to b_enable*/
    do {
       i4_ret = c_scc_vid_get_mjc(h_scc, &t_mjc);
       if (SMR_OK != i4_ret)
       {
           break;
       }

       if (b_enable)
       {
           i4_ret = a_cfg_av_get (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MJC_EFFECT),
                                  (INT16*)(&t_mjc.e_effect));
           if (APP_CFGR_OK != i4_ret)
           {
               break;
           }
       }
       else
       {
           t_mjc.e_effect = SCC_VID_MJC_EFFECT_OFF;
       }

       i4_ret = c_scc_vid_set_mjc(h_scc, &t_mjc);

    } while (0);

    if (NULL_HANDLE != h_scc)
    {
        c_scc_comp_close(h_scc);
    }

    /*Set OSD mode*/
    do {
        c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_EXTMJC_GET;
        t_op_info.u.t_extmjc_get_info.e_extmjc_type = DRV_CUSTOM_EXTMJC_TYPE_IS_ENABLE;
        t_op_info.u.t_extmjc_get_info.pv_get_info = &b_mjc_enable;
        t_op_info.u.t_extmjc_get_info.pz_size = &z_bool_size;
        i4_ret = c_rm_get_comp(DRVT_CUST_DRV,
                               DRV_CUST_COMP_ID,
                               FALSE,
                               ANY_PORT_NUM,
                               0,
                               &t_op_info,
                               &z_size
                               );
        if (RMR_OK != i4_ret || FALSE == b_mjc_enable)
        {
            break;
        }
        c_memset(&t_set_osd_mode, 0, sizeof(EXTMJC_TYPE_SET_OSD_MODE_T));
        t_set_osd_mode.ui1_osd_mode = b_enable ? DRV_CUSTOM_EXTMJC_OSD_MODE_DMA : DRV_CUSTOM_EXTMJC_OSD_MODE_NORMAL;

        c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
        t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_EXTMJC_SET;
        t_op_info.u.t_extmjc_set_info.e_extmjc_type = DRV_CUSTOM_EXTMJC_TYPE_SET_OSD_MODE;
        t_op_info.u.t_extmjc_set_info.pv_set_info = &t_set_osd_mode;
        t_op_info.u.t_extmjc_set_info.z_size = sizeof(EXTMJC_TYPE_SET_OSD_MODE_T);
        t_op_info.u.t_extmjc_set_info.b_store = TRUE;

        /* set to driver */
        i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                               DRV_CUST_COMP_ID,
                               FALSE,
                               ANY_PORT_NUM,
                               0,
                               &t_op_info,
                               sizeof(DRV_CUST_OPERATION_INFO_T));
        if (RMR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
        }
    } while (0);


    return i4_ret;
#else
    return WFDR_OK;
#endif
}

INT32 wfd_restore_video_resource(VOID)
{
    ISL_REC_T                   t_isl_rec;
    INT32                       i4_ret;
    WFD_DBG_LOG(b_pause_tv);
    if(!b_pause_tv)
    {
        return WFDR_OK;
    }
    if (FALSE == a_am_is_power_on())
    {
        return WFDR_OK;
    }

    /*open svl*/
    i4_ret = _wfd_init_svl();
    if(WFDR_OK != i4_ret)
    {
        return WFDR_FAIL;
    }

    /*reset blue mute*/
    _wfd_update_blue_mute(FALSE);

    /*reset video srm mode*/
    wfd_set_video_srm_mode(SCC_VID_SRM_MODE_OFF);

    /*reset NR and 3D_NR*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));

    /*reset MJC effect*/
    wfd_enable_mjc_effect(TRUE);

    /*reset screen mode*/
    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);

    /*For fix DTV00140629*/
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

    /*reset SVCTX attribute*/
    a_tv_reset_svctx_parameter(t_g_wfd_main.h_main_svctx);

    /*restart tv*/
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
    if(TVR_OK != i4_ret)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
    }
    else /*TVR_OK*/
    {
#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
        UINT16 ui2_svl_id;
        CHAR*  ps_src_name;

        i4_ret = a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_src_name);
        if(APP_CFGR_OK == i4_ret)
        {
            i4_ret = a_tv_update(TV_UPDATE_SCART_BYPASS_RESELECT_TV_SCART,
                                 (VOID*)((ATSC_CABLE_SVL_ID == ui2_svl_id) ?t_g_wfd_main.h_cable_svl : t_g_wfd_main.h_air_svl),
                                 NULL,
                                 NULL);
            if(TVR_OK != i4_ret)
            {
                DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                            __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                            i4_ret));
            }
        }
        else
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
        }
#endif

        i4_ret = a_tv_change_input_src_by_rec(t_g_wfd_main.h_main_svctx, SVCTX_STRM_MODE_AS_LAST, &t_isl_rec, NULL);
        if(TVR_NO_SVL_RECORD == i4_ret)
        {
            /*reset blue mute immediately.*/
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE));
        }
        else if(TVR_OK != i4_ret)
        {
            DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                        __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                        i4_ret));
        }
    }

    /*close svl*/
    _wfd_deinit_svl();
    b_pause_tv = FALSE;
    return WFDR_OK;
}

VOID wfd_app_amb_pause(VOID)
{
    a_amb_pause_app(WFD_NAME);
}

VOID wfd_app_amb_resume(VOID)
{
    a_amb_resume_app(WFD_NAME);
}


static VOID _wfd_device_remove_notify_handler(VOID* param1,VOID* param2,VOID* param3,VOID* param4)
{
    if(!wfd_app_is_active())
    {
        return;
    }
    NI_DRV_EV_T e_ev = (NI_DRV_EV_T)(UINT32)param1;
    switch(e_ev)
    {
        case NI_DRV_EV_ETHERNET_PLUGIN:
        {
            wfd_main_send_msg_to_view(WFD_MSG_DEVICE_PLUG, NULL);
            break;
        }
        case NI_DRV_EV_ETHERNET_UNPLUG:
        {
            //DBG_LOG_PRINT(("<wfd>: NI_DRV_EV_ETHERNET_UNPLUG wfd_app_get_p2p_sta():[%d].%s line(%d)\r\n", t_g_wfd_main.e_p2p_sta, __FUNCTION__, __LINE__));
            if(wfd_app_get_p2p_sta() == WFD_P2P_END)
            {
                //DBG_LOG_PRINT(("<wfd>: NI_DRV_EV_ETHERNET_UNPLUG wfd_app_get_p2p_sta() = WFD_P2P_END %s line(%d)\r\n",__FUNCTION__, __LINE__));
                return;
            }
            wfd_rtsp_stop();
            wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_STOP);

            if(wfd_app_get_p2p_conn_sta() == WFD_P2P_CONN_CONNECTED || wfd_app_get_p2p_conn_sta() == WFD_P2P_CONN_CONNECTING)
            {
                wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_DISCONNECTING);
                WFD_DBG_ERR(wfd_p2p_disconnect());
                wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_DISCONNECT);
            }

            if(wfd_app_get_p2p_sta() == WFD_P2P_ENABLED || wfd_app_get_p2p_sta() == WFD_P2P_ENABLING)
            {
                wfd_app_set_p2p_sta(WFD_P2P_DISABLING);
                WFD_DBG_ERR(wfd_p2p_disable_wifi_display());
                wfd_app_set_p2p_sta(WFD_P2P_DISABLED);
            }
            wfd_main_send_msg_to_view(WFD_MSG_DEVICE_REMOVE, NULL);
            break;
        }
        default:
            break;
    }
    return;
}


static VOID _wfd_device_remove_notify_fct(NI_DRV_EV_T e_ev)
{
    wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_device_remove_notify_handler,(VOID*)(UINT32)e_ev,NULL,NULL,NULL);
    return;
}

INT32 wfd_set_device_remove_listen(VOID)
{
    INT32 i4_ret;
/*        maybe use later
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_0, NI_DRV_EV_IP_ADDRESS_CHANGED, _wfd_device_remove_notify_fct);
    WFD_RET_ON_ERR(i4_ret);
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_0, NI_DRV_EV_IP_ADDRESS_EXPIRED, _wfd_device_remove_notify_fct);
    WFD_RET_ON_ERR(i4_ret); */

    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_0, NI_DRV_EV_WLAN_ASSOC, _wfd_device_remove_notify_fct);
    WFD_RET_ON_ERR(i4_ret);
    i4_ret = c_net_ni_reg_ev_notify(NI_WIRELESS_0, NI_DRV_EV_WLAN_DISASSOC, _wfd_device_remove_notify_fct);
    WFD_RET_ON_ERR(i4_ret);

    return WFDR_OK;
}

VOID wfd_app_pin_display_accept(VOID)
{
     wfd_p2p_pin_display_accept();
     return;
}

INT32 wfd_main_send_msg_to_view(WFD_MSG_T e_msg,VOID* param)
{
    WFD_DBG_LOG(e_msg);
    wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE, _wfd_view_do_msg, (VOID* )(UINT32)e_msg,  param, NULL, NULL);
    return WFDR_OK;
}

UINT32 wfd_app_get_timeout(VOID)
{
    return i4_timeout;
}
static VOID _wfd_app_time_out_nfy_hdlr(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3, VOID* pv_tag4)
{

     if(wfd_app_get_p2p_conn_sta() != WFD_P2P_CONN_CONNECTING)
     {
        i4_timeout = -1;
        WFD_DBG_LOG(i4_timeout);
        return ;
     }
     else if(i4_timeout != WFD_CONN_TIMEOUT)
     {
         c_timer_start(t_g_wfd_view_main.h_timer_time_out,
                       1000,
                       X_TIMER_FLAG_ONCE,
                       wfd_app_time_out_timer_nfy_func,
                       NULL);
         i4_timeout++;
     }

     else if(i4_timeout == WFD_CONN_TIMEOUT)
     {
         i4_timeout = -1;
         wfd_p2p_disconnect();
         t_g_wfd_main.e_p2p_conn_sta = WFD_P2P_CONN_DISCONNECT;
         wfd_main_send_msg_to_view(WFD_MSG_CONN_TIME_OUT, NULL);
     }

     return;
}

//use to let finding move
static VOID wfd_app_time_out_timer_nfy_func(HANDLE_T h_timer, VOID* pv_tag)
{
    wfd_event_send_context(WFD_SEND_RETRY_TYPE_ONCE,_wfd_app_time_out_nfy_hdlr, pv_tag, NULL,NULL,NULL);
    return;
}

INT32 a_wfd_wifi_display_show_rtp_statistics(void)
{
    INT32 i4_ret = WFDR_OK;
    WFD_PUSH_PLAYER_STATS_T *rtps = NULL;

    rtps = (WFD_PUSH_PLAYER_STATS_T *)malloc(sizeof(WFD_PUSH_PLAYER_STATS_T));
    if (!rtps)
        return WFDR_FAIL;
    memset(rtps, 0, sizeof(WFD_PUSH_PLAYER_STATS_T));
    i4_ret = wfd_client_get_rtp_stats((char *)rtps, sizeof(WFD_PUSH_PLAYER_STATS_T));
    /* note, the return is true or false */
    if (i4_ret <= 0)
    {
        if (rtps)
            c_mem_free(rtps);
        WFD_DBG_LOG(("Failed to get RTP stats\n"));
        return WFDR_FAIL;
    }
    else
    {
        DBG_LOG_PRINT(("\n[RTP Statistics]\n-------------------------\n"));
        DBG_LOG_PRINT(("Total received bytes:\t\t%u\n", rtps->total_received_size));
        DBG_LOG_PRINT(("Total consumed bytes:\t\t%u\n", rtps->total_consumed_size));
        DBG_LOG_PRINT(("Buf write idx:\t\t\t%d\n", rtps->buf_w_idx));
        DBG_LOG_PRINT(("Buf read idx:\t\t\t%d\n", rtps->buf_r_idx));
        DBG_LOG_PRINT(("Buf write position:\t\t%d\n", rtps->buf_w_start_pos));
        DBG_LOG_PRINT(("Buffered bytes:\t\t\t%d\n", rtps->buffered_size));
        DBG_LOG_PRINT(("Total buffer size:\t\t%d\n", rtps->total_size));
        DBG_LOG_PRINT(("Out-of-buffer count:\t\t%d\n", rtps->oob_count));
        DBG_LOG_PRINT(("CMPB GetBuffer err count:\t%d\n", rtps->cmpb_getbuffer_error_count));
        DBG_LOG_PRINT(("CMPB SendData err count:\t%d\n", rtps->cmpb_senddata_error_count));
        DBG_LOG_PRINT(("CMPB HeaderParse fail count:\t%d\n", rtps->header_parse_fail_count));
        DBG_LOG_PRINT(("Audio PID:\t\t\t%d\n", rtps->audio_pid));
        DBG_LOG_PRINT(("Video PID:\t\t\t%d\n", rtps->video_pid));
        DBG_LOG_PRINT(("Audio codec:\t\t\t%d\n", rtps->audio_codec));
        DBG_LOG_PRINT(("Video codec:\t\t\t%d\n", rtps->video_codec));
        DBG_LOG_PRINT(("Player status:\t\t\t%d\n", rtps->pushplayer_status));
        DBG_LOG_PRINT(("-------------------------\n"));
    }

    if (rtps)
        c_mem_free(rtps);
    return WFDR_OK;


}

INT32 a_wfd_wifi_display_dump_ts_set_path(char *path)
{
    INT32 i4_ret = WFDR_OK;

    if (!path || !strlen(path))
        return WFDR_FAIL;
    i4_ret = wfd_client_dump_ts_set_path(path);
    /* note, the return is true or false */
    if (i4_ret < 0)
        return WFDR_FAIL;
    else
        return WFDR_OK;
}


INT32 a_wfd_wifi_display_dump_ts_set_enable(int enable)
{
    INT32 i4_ret = WFDR_OK;

    i4_ret = wfd_client_dump_ts_set_enable(enable);
    /* note, the return is true or false */
    if (i4_ret < 0)
        return WFDR_FAIL;
    else
        return WFDR_OK;
}

INT32 a_wfd_wifi_display_start_rtsp(char *s_ip, UINT32 ui4_port)
{
    INT32 i4_ret = 0;

    if ((!s_ip)||(ui4_port<0))
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__));
        return WFDR_INV_ARG;
    }

    i4_ret = wfd_client_start_rtsp_ip_port(s_ip,ui4_port);

    if (i4_ret < 0)
    {
        DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
        return WFDR_FAIL;
    }
    else
    {
       DBG_LOG_PRINT(("\n%s,%s,%s,%s,%d,i4_ret=%d\n",
                    __DATE__, __TIME__, __FILE__, __FUNCTION__, __LINE__,
                    i4_ret));
       return WFDR_OK;
    }

}

BOOL a_wfd_is_rtsp_play_status(VOID)
{
    INT32   i4_ret;
    CHAR    s_app_name[APP_NAME_MAX_LEN];


    if (a_cfg_custom_get_wfd_support() == TRUE)
    {
        i4_ret = a_am_get_active_app(s_app_name);
        if (AMR_OK == i4_ret && 0 == c_strcmp (s_app_name, WFD_NAME))
        {
            if(wfd_view_get_current_view() == WFD_VIEW_PLAY)
            {
                return TRUE;
            }
        }
    }

    return FALSE;
}

INT32 a_wfd_get_device_name(UTF16_T* w2s_name)
{
    WFD_DEVICE_INFO_T t_info;

    c_memset(&t_info, 0, sizeof(WFD_DEVICE_INFO_T));

    WFD_RET_ON_ERR(wfd_app_get_conn_device_info(&t_info));

    c_uc_ps_to_w2s(t_info.ps_device_name, w2s_name, DEVICE_INFO_ARR_LEN);
    w2s_name[DEVICE_INFO_ARR_LEN] = 0;

    return WFDR_OK;
}


