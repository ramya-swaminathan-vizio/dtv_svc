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
 * $RCSfile:  $
 * $Revision: #7 $
 * $Date: 2015/07/21 $
 * $Author: jg_lizhuwang $
 * $SWAuthor: Jun Zuo $
 *
 * Description:
 *         This file used to convert the message sent/get from AM stand in/out.
 * functions.
 *---------------------------------------------------------------------------*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "c_aee.h"
#include "c_appman.h"
#include "cmd_convert.h"
#include "u_irrc_btn_def.h"
#include "c_os.h"
#include "c_dbg.h"
#include "c_common.h"
#include "c_handle.h"
#include "c_aee.h"
#include "c_appman.h"
#include "c_wgl.h"
#include "c_iom.h"
#include "c_svctx.h"
#include "c_scc.h"
#include "c_pcl.h"
#include "c_svctx.h"
#include "u_sm_cc_hdlr.h"
#include "c_fm.h"
#include "u_fm.h"
#include "c_reset_3rdapp.h"

#include "amb/a_amb.h"
#include "am/a_am.h"

#include "bgm/a_bgm.h"
#include "bgm/mtk_comp/bgm_cast_c4tv/a_bgm_cast_c4tv.h"
#include "bgm/mtk_comp/bgm_nfx_ar/a_bgm_nfx_ar.h"

#include "menu2/a_menu.h"
#include "menu2/menu.h"

#include "nav/nav_common.h"
#include "nav/a_navigator.h"
#include "nav/pop/a_pop.h"
#include "nav/input_src/a_input_src.h"
#include "nav/twinkle_msg/a_scrn_svr.h"
#include "nav/power/a_nav_power.h"
#include "nav/cc_info/a_cc_info.h"
#include "nav/cc_info/cc_info.h"
#include "nav/revolt_misc/revolt_misc.h"
#include "nav/input_src/a_input_src.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/retail_mode/retail_mode_view.h"
#include "nav/dialog/nav_dialog.h"
#include "nav/navigator.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/cec2/otp/nav_cec_otp.h"
#include "nav/banner2/a_banner.h"
#include "nav/sleep/sleep.h"


#ifdef APP_RETAIL_MODE_SUPPORT
#include "nav/retail_mode/a_nav_retail_mode.h"
#endif
#include "nav/power/a_nav_power.h"
#include "nav/power/nav_power.h"

#include "nav/via_dlg/nav_via_dlg_view.h"
#include "nav/long_press/long_press.h"

#include "mmp/a_mmp.h"
#include "mmp/app/mmp_main.h"
#include "mmp/browse_eng/mmp_browse_eng.h"

#include "a_msgconvert.h"
#include "msgconvert.h"
#include "mscvt_cli.h"
#include "msgconvert/mscvt_cli.h"
#include "msgconvert/msgconvert.h"
#include "msgconvert_custom.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_tv.h"
#include "app_util/a_icl_common.h"
#include "app_util/nfx_ar/a_nfx_ar.h"
#include "app_util/a_tv.h"
#include "app_util/network/network.h"
#include "app_util/mtktvapi/a_mtktvapi_highlevel.h"

#ifdef APP_C4TV_SUPPORT
#include "rest/a_rest.h"
#include "rest/a_rest_api.h"
#include "rest/a_rest_event.h"
#endif
#include "rest/rest.h"
#include "rest/rest_system.h"
#include "rest/vzipc/vzIpcServer.h"
#include "registry/a_registry.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/rmv_dev/a_rmv_dev_custom.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/mtktvapi/mtktvapi_highlevel_custom.h"

#include "res/bgm/bgm_variant.h"

#include "res/app_util/simple_logo/a_simple_logo.h"
#include "res/nav/zoom/nav_zoom_custom.h"
#include "res/nav/nav_mlm.h"

#include "wizard_anim/a_wzd.h"
#ifdef APP_WFD_SUPPORT
#include "wfd/a_wfd.h"
#endif

#include "mtosd.h"

#include "app_client.h"
#include "wfrrc_interface.h"


#include "mi_common.h"
#include "mi_mm.h"
#include "mi_aout.h"
#include "mi_disp.h"
#include "mi_osd.h"
#include "mi_os.h"
#include "mi_sys.h"

//===========================================================================

#define DEBUG_KEY_FLOW(x)   //x

//===========================================================================

#ifdef DBG_LEVEL_MODULE
#undef DBG_LEVEL_MODULE
#endif
#ifdef DBG_MODULE_NAME_PREFIX
#undef DBG_MODULE_NAME_PREFIX
#endif
#define  DBG_LEVEL_MODULE                   _mscvt_get_dbg_level()
#define  DBG_MODULE_NAME_PREFIX             "MSCVT_CUST"
#define  MSCVT_LOG_PREFIX                   "<mscvt_cust> "
#define  MSCVT_CUS_INPUT_THREAD_NAME        ("mscvt_custom_input")
#define  MSCVT_CUS_THREAD_STACK_SIZE        ((SIZE_T)1024 * 8)
#define  MSCVT_CUS_THREAD_PRIORITY          ((UINT8)200)

#define  MSCVT_STOP_NONE             (0)
#define  MSCVT_STOP_NETFLIX          (1)
#define  MSCVT_STOP_YOUTUBE          (2)
#define  MSCVT_STOP_AMAZON           (3)
#define  MSCVT_STOP_BROWSER_CONTORL  (4)
#define  MSCVT_STOP_BROWSER_AIRPLAY  (5)

#define  SYSTEM_UI_SHOW (1)
#define  SYSTEM_UI_HIDE (0)


static HANDLE_T __i_input_thread;

static BOOL                 b_ap_resumed = FALSE;
static BOOL                 _b_recv_pause_cmd = FALSE;
static BOOL                 _b_input_src_change = FALSE;
static BOOL                 _b_netflix_alive = FALSE;
static BOOL                 _b_cobalt_alive = FALSE;
static BOOL                 _b_amazon_alive = FALSE;
static BOOL                 _b_hotkey_netflix_started = FALSE; //This flag is add for AC OFF/ON case,for some special case,netflix launch will be about 4s delay.there will be black screen during vizio logo and netflix
static BOOL                 _b_hotkey_netflix_pressed = FALSE; //This flag is add for confirm the hotket wakeup is netflix or not
static BOOL                 _b_browser_ctrl_alive = FALSE;
static BOOL                 _b_hotkey_pressed = FALSE;
static BOOL                 _b_hotkey_wdg_pressed = FALSE;
static BOOL                 b_browser_starting = FALSE;
static BOOL                 b_cast_wakeup = FALSE;
static BOOL                 b_netflix_pressed = FALSE;
static BOOL                 b_amazon_pressed = FALSE;
static BOOL                 b_cobalt_pressed = FALSE;
static BOOL                 b_widget_pressed = FALSE;
static BOOL                 b_bgm_runing     = FALSE;
static BOOL                 b_browser_airplay_started = FALSE;
static BOOL                 b_wait_power_off = FALSE;
static BOOL                 b_netflix_inited = FALSE;
static BOOL                 _b_appletv_alive = FALSE;
static BOOL                 _b_hbomax_alive = FALSE;
static BOOL                 _b_castcore_alive = FALSE;
static BOOL                 _b_wait_for_3rd_shtdn = FALSE;
static UINT32               ui4_last_stoped_app = MSCVT_STOP_NONE;
static BOOL                 _b_browser_stopped = FALSE;
static BOOL                 _b_system_ui_showing = FALSE;
static BOOL                 b1_power_to_input_flag = FALSE;
static BOOL                 _b_oled_interrupt_off_rs = FALSE;


#ifdef MT5695_MODEL
static UINT8                ui1_oled_error_count = 0;
#endif

#ifdef TVIS_UI_SUPPORT
typedef enum _TVIS_UI_STAT_T
{
    TVIS_UI_STAT_OFF = 0,
    TVIS_UI_STAT_ON,
    TVIS_UI_STAT_LAST_ENTRY
}TVIS_UI_STAT_T;
static BOOL         _b_dtv_getfocus = FALSE;
static TVIS_UI_STAT_T e_g_tvis_ui_status = TVIS_UI_STAT_OFF;
#define TVIS_URL_LEN  (512)
#endif

/*key handle*/
typedef struct _KEY_INFO
{
    KEY_RETURN_TYPE ui4_save_key_type;
    UINT32 ui4_key_symbol;
}_KEY_INFO;


static _KEY_INFO last_key_info;
UINT32 ui4_last_tick  = 0;
UINT32 long_key_symbol= 0x00;
UINT32 ui4_vol_input_symbol = 0x00;

extern int _rest_app_create_virtual_inputs();
extern BOOL a_oled_compensation_is_running();

extern int app_thread_run_launch_app_by_keycode(int keycode, int reason);

static BOOL _g_hotkey_wakeup = FALSE;

static UINT16 ui2_acfg_inp_src_chg_id = 0;  /* Need ugreg this nfy_id when uninit*/

void msg_convert_recv_cmd(INT32 i4_type, const CHAR* s_ack, const CHAR* s_value);

INT32 msg_convert_custom_resume_tv(VOID);
INT32 msg_convert_custom_resume_tv_signal(VOID);
BOOL msg_convert_custom_is_yahoo_started(VOID);
BOOL msg_convert_custom_is_yahoo_ready(VOID);
INT32 msg_convert_custom_resume_navigator(VOID);

static void _mc_app_process_input_thread(void *pv_data);

static BOOL _msg_convert_is_cast_source(CHAR* ps_name);

#define MSCVT_CUST_LOG_ON_FAIL(_ret)  \
do{ \
if (_ret < 0)   \
{   \
    DBG_ERROR((MSCVT_LOG_PREFIX" fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
}   \
}while(FALSE)

VOID _msg_convert_check_power_off()
{
    if(b_wait_power_off)
    {
        a_amb_power_on(FALSE);
    }
}

INT32 cmd_convert_wakeup()
{
    CMD_CONVERT_SEND_CMD_T t_send_cmd;

    t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
    t_send_cmd.s_destination = CMDCVT_MACRO_AM;
    t_send_cmd.s_ack = NULL;
    t_send_cmd.s_command = "wakeup";
    t_send_cmd.s_parameter = "hotkey";
    cmd_convert_send_command(&t_send_cmd);
    return 0;
}

#ifdef TVIS_SUPPORT
/* suspend tvis main when msgconvert resumed, continue tvis main when msgconvert paused*/
/*------------------------------------------------------------------------
 * Name: _check_tvispid(void)
 *
 * Description: This API for check tvis main program's pid is exist or not.
 *              If it is not exist, try to get it or restart it.
 *
 * Inputs:  arg   The argument for this thread set.
 *
 * Outputs: -
 *
 * Returns: -
 -----------------------------------------------------------------------*/
#define TVIS_SETPID_RETRY_COUNT (3)
static unsigned int _check_tvispid(void)
{
    FILE* fp = NULL;

    /* if tvis_main is not started, ignore it. */
    if(access("/tmp/inscape/tvis_state_started",0) != 0)
    {
        DBG_INFO(("\n%s,%s,%d, no /tmp/inscape/tvis_state_started\n", __FILE__, __FUNCTION__, __LINE__));
        return 0;
    }

    for(int i = 0 ; i < TVIS_SETPID_RETRY_COUNT; i++)
    {
        fp = fopen("/tmp/inscape/tvispid", "r");
        if (fp == NULL)
        {
            DBG_INFO((" get tvis pid failed, retry set pid %d\n",i));
            AP_SYSTEM_CALL ("echo 0 > /tmp/inscape/tvispid"); /* prevent fscanf error. */

            /********************************************************************/
            //hongzhao 2020/2/12 add for acr downloadable
            {
                CHAR    target_path[64] = "/data/app/inscape";
                CHAR    link_path[64];
                CHAR    p_cmd_buf[256];

                if (-1 == readlink(target_path, link_path, sizeof(link_path)))
                {
                    memset(target_path, 0, sizeof(target_path));
                    c_sprintf(target_path, "%s", "/3rd/tvis/set_tvispid.sh");
                }
                else
                {
                    c_strcat(target_path, "/set_tvispid.sh");
                    DBG_INFO(("tvis wrapper path is %s\r\n", target_path));
                }

                sprintf(p_cmd_buf,"sh %s",target_path);
                AP_SYSTEM_CALL(p_cmd_buf);
            }
            /********************************************************************/
        }
        else
        {
            unsigned int pid = 0;
            int nreadbyte = fscanf(fp,"%d",&pid);
            fclose(fp);
            if(nreadbyte > 0 && pid > 0)
            {
                DBG_INFO((" tvis pid [%d] \n",pid));
                return pid;
            }
            else
            {
                usleep(10000);

                /********************************************************************/
                //hongzhao 2020/2/12 add for acr downloadable
                {
                    CHAR    target_path[64] = "/data/app/inscape";
                    CHAR    link_path[64];
                    CHAR    p_cmd_buf[256];

                    if (-1 == readlink(target_path, link_path, sizeof(link_path)))
                    {
                        memset(target_path, 0, sizeof(target_path));
                        c_sprintf(target_path, "%s", "/3rd/tvis/set_tvispid.sh");
                    }
                    else
                    {
                        c_strcat(target_path, "/set_tvispid.sh");
                        DBG_INFO(("tvis wrapper path is %s\r\n", target_path));
                    }

                    sprintf(p_cmd_buf,"sh %s",target_path);
                    AP_SYSTEM_CALL(p_cmd_buf);
                }
                /********************************************************************/
            }
        }
    }

    /* add crash state to process the corner case. */
    a_tv_custom_set_tvis_state(TVIS_MAIN_STATE_CRASHED);

    DBG_INFO((" get tvis pid retry failed \n"));
    return 0;
}

/*------------------------------------------------------------------------
 * Name:  _resume_tvis()
 *
 * Description: This API for suspend tvis main program.
 *
 * Inputs:  arg   The argument for this thread set.
 *
 * Outputs: -
 *
 * Returns: -
 -----------------------------------------------------------------------*/
static void _resume_tvis(void)
{
    pid_t pid=0;
    pid = _check_tvispid();
    if (pid > 0)
    {
        kill(pid,SIGCONT);
        if(access("/tmp/inscape/inscape_acr_state_suspend",0)!= 0)
        {
            s_rm("/tmp/inscape/inscape_acr_state_suspend");
        }
    }
}

#endif

#ifdef TVIS_UI_SUPPORT
static BOOL _is_launch_tvis_url(void)
{
    INT32          i4_ret = 0;
    BOOL           b_launch = TRUE;
    char ps_resume_ap[APP_NAME_MAX_LEN+1] = {0};
#ifdef APP_RETAIL_MODE_SUPPORT
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_HOME;
#endif

    i4_ret = a_am_get_active_app(ps_resume_ap);
    if(i4_ret != AEER_OK)
    {
        DBG_ERROR(("\n get active app failed\n"));
        return FALSE;
    }

    do
    {
        /* if current resumed application is not navigator, don't launch */
        if(strncmp(ps_resume_ap,NAV_NAME,strlen(NAV_NAME)) != 0)
        {
            b_launch = FALSE;
            break;
        }

        /* if in retail demo mode, don't launch */
    #ifdef APP_RETAIL_MODE_SUPPORT
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        if (ACFG_RETAIL_MODE_HOME != t_retail_mode)
        {
            b_launch = FALSE;
            break;
        }
    #endif

        /* if dtv isn't the focused process, don't luanch */
        /* to prevent the cases such as Yahoo Gallery is running, navigator is in resumed status but dtv isn't the focus */
        if (FALSE == _b_dtv_getfocus)
        {
            b_launch = FALSE;
            break;
        }

        if (APP_CFG_APP_STATUS_LAST_ENTRY != a_cfg_get_app_status())
        {
            b_launch = FALSE;
            break;
        }
    }while(0);

    return b_launch;
}
#endif

INT32 msg_convert_custom_resume_mscvt()
{
    return 0;
}

INT32 msg_convert_custom_pause_mscvt()
{
    return msg_convert_custom_resume_tv();
}

static INT32 msg_convert_custom_launch_netflix()
{
    CMD_CONVERT_SEND_CMD_T t_send_cmd;
    t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
    t_send_cmd.s_destination = CMDCVT_MACRO_AM;
    t_send_cmd.s_ack = "Netflix Button";
    t_send_cmd.s_command = CMDCVT_MACRO_START;
    t_send_cmd.s_parameter = "[netflix,-Q,source_type=1&additionalDataUrl=http%3A%2F%2Flocalhost%3A56789%2Fapps%2FNetflix%2Fdial_data%3F]";
    return cmd_convert_send_command(&t_send_cmd);
}

static INT32 msg_convert_custom_launch_youtube()
{
    CMD_CONVERT_SEND_CMD_T t_send_cmd;
    t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
    t_send_cmd.s_destination = CMDCVT_MACRO_AM;
    t_send_cmd.s_ack = "";
    t_send_cmd.s_command = CMDCVT_MACRO_START;
    t_send_cmd.s_parameter = "[Cobalt YTTV,--url=https://www.youtube.com/tv?launch=remote&additionalDataUrl=http%3A%2F%2Flocalhost%3A56789%2Fapps%2FYouTube%2Fdial_data%23%2F]";
    return cmd_convert_send_command(&t_send_cmd);
}

static INT32 msg_convert_custom_launch_amazon()
{
    CMD_CONVERT_SEND_CMD_T t_send_cmd;
    t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
    t_send_cmd.s_destination = CMDCVT_MACRO_AM;
    t_send_cmd.s_ack = "";
    t_send_cmd.s_command = CMDCVT_MACRO_START;
    t_send_cmd.s_parameter = "[amazon_ignition,--launch-by-hotkey]";
    return cmd_convert_send_command(&t_send_cmd);
}

static INT32 msg_convert_custom_notify_btsoftmic_result(bool ret, INT32 i4_type)
{
    CMD_CONVERT_SEND_CMD_T t_send_cmd;
    t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
    t_send_cmd.s_destination = "Cobalt YTTV";
    t_send_cmd.s_ack = "";
    t_send_cmd.s_command = NULL;
    if (CMDCVT_MSG_APCMD_SOFT_MIC_BT_START == i4_type)
    {
        t_send_cmd.s_command = "Vizio_BTVoiceStarted";
    }
    else if (CMDCVT_MSG_APCMD_SOFT_MIC_BT_STOP == i4_type)
    {
        t_send_cmd.s_command = "Vizio_BTVoiceStopped";
    }
    t_send_cmd.s_parameter = "false";
    if (ret == true)
    {
        t_send_cmd.s_parameter = "true";
    }
    return cmd_convert_send_command(&t_send_cmd);
}

#ifdef TVIS_SUPPORT
static VOID _msgconvert_svctx_notify_fct(
    HANDLE_T            h_svctx,
    SVCTX_COND_T        e_nfy_cond,
    SVCTX_NTFY_CODE_T   e_code,
    STREAM_TYPE_T       e_stream_type,
    VOID*               pv_nfy_tag)
{
    if (SVCTX_NTFY_CODE_SIGNAL_LOSS == e_code)
    {
        INT32 i4_ret = 0;
        pid_t pid = 0;
        pid = _check_tvispid();
        if (pid > 0)
        {
            i4_ret = kill(pid,SIGTTIN);
            DBG_INFO(("<ACR>lost signal SIGTTIN,i4_ret=%d,errno=%s\n",
                        i4_ret, strerror(i4_ret)));
        }
    }
    else if (SVCTX_NTFY_CODE_VIDEO_FMT_UPDATE == e_code)
    {
        INT32 i4_ret = 0;
        pid_t pid = 0;
        pid = _check_tvispid();
        if (pid > 0)
        {
            i4_ret = kill(pid,SIGTTOU);
            DBG_INFO(("<ACR>have signal SIGTTOU,i4_ret=%d,errno=%s\n",
                       i4_ret, strerror(i4_ret)));
        }
    }
}

#ifdef TVIS_TEST_SUPPORT
static UINT32 ui4_g_tvis_trigger_count = 0;

static VOID _tvis_auto_test(VOID)
{
    CHAR s_cmd[TVIS_URL_LEN+1] = {0};
    CHAR s_url[TVIS_URL_LEN+1] = {0};

    if (FALSE == _is_launch_tvis_url())
    {
        return;
    }

    ui4_g_tvis_trigger_count++;

    if (1 == ui4_g_tvis_trigger_count % 4)
    {
        c_strncpy(s_url, "http://www.sho.com/assets/vendor/itv/shosync-dev.html?platform=Vizio&titleid=3391118", TVIS_URL_LEN);
    }
    else if (2 == ui4_g_tvis_trigger_count % 4)
    {
        c_strncpy(s_url, "https://events2.tvinteractive.tv/events/vizio_qa/acr_sample/index.html", TVIS_URL_LEN);
    }
    else if (3 == ui4_g_tvis_trigger_count % 4)
    {
        c_strncpy(s_url, "https://apps.tvinteractive.tv/acr_sample/index.html", TVIS_URL_LEN);
    }

    c_snprintf(s_cmd, TVIS_URL_LEN,
        "\n:dtv_app_mtk,am,:start_ex=[generic_osd,\"-w 1280 -h 720 -x generic_osd_app -m NO -u %s\"]\n", s_url);
    DBG_INFO(("\n%s,%s,%d,%s\n", __FILE__, __FUNCTION__, __LINE__, s_cmd));
    a_tv_net_send_cmd(s_cmd);

    e_g_tvis_ui_status = TVIS_UI_STAT_ON;
}

/* for TVIS auto test */
static HANDLE_T h_g_tvis_trigger_timer = NULL_HANDLE;
static VOID _tvis_trigger_do_timer_nfy(
    VOID* pv_data,
    SIZE_T  z_data_size)
{
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);
}

static VOID _tvis_trigger_timer_cb_fct (HANDLE_T  pt_handle,
                               VOID*     pv_tag)
{
    menu_async_invoke(_tvis_trigger_do_timer_nfy,
                      NULL, 0, TRUE);
}

static VOID _tvis_auto_test_init(VOID)
{
    if (NULL_HANDLE == h_g_tvis_trigger_timer)
    {
        c_timer_create(&h_g_tvis_trigger_timer);
    }

    c_timer_start(h_g_tvis_trigger_timer, 30*1000, X_TIMER_FLAG_REPEAT,
                  _tvis_trigger_timer_cb_fct, NULL);
}

#endif

#ifdef TVIS_UI_SUPPORT
/* judge to suspend or resume tvis_main program. */
static INT32 _msgsvt_custom_icl_notify (
                    UINT16              ui2_nfy_id,
                    VOID*               pv_tag,
                    ICL_NOTIFY_DATA_T*  pt_notify_data
                    )
{
    ICL_GRPID_TYPE e_grp_id = ICL_GET_GROUP (pt_notify_data->pe_id[0]);
    UINT8          ui1_val;
    SIZE_T         z_size;
    INT32          i4_ret;
#ifdef APP_RETAIL_MODE_SUPPORT
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_HOME;
#endif
    CHAR      s_resume_ap[APP_NAME_MAX_LEN+1] = {0};

    if (e_grp_id != ICL_GRPID_MSGCVT_UI_POPUP)
    {
        return ICLR_OK;
    }

    z_size = ICL_RECID_MSGCVT_IS_UI_POPUP_SIZE;

    i4_ret = a_icl_get(ICL_MAKE_ID(ICL_GRPID_MSGCVT_UI_POPUP, ICL_RECID_MSGCVT_IS_UI_POPUP),
                       &ui1_val,
                       &z_size);

    if (i4_ret != ICLR_OK)
    {
        ui1_val = ICL_MSGCVT_UI_NOT_EXIST;
    }

    /* ignore cases:
         1. if TV UI is off, and if the resumed application is not navigator then ignore the case;
             2. if TV UI is off, and TVIS UI is on then ignore the case;
             3. if TV UI is on, and TVIS UI is off then ignore the case
         */
    if (ui1_val == ICL_MSGCVT_UI_NOT_EXIST)
    {
        i4_ret = a_am_get_active_app(s_resume_ap);
        if ((AMR_OK == i4_ret)
            &&(0 != c_strcmp(s_resume_ap, "navigator")))
        {
            /* ignore directly. */
            return ICLR_OK;
        }
        if (TVIS_UI_STAT_ON == e_g_tvis_ui_status)
        {
            /* ignore directly. */
            return ICLR_OK;
        }
    }

    if (ui1_val == ICL_MSGCVT_UI_EXIST)
    {
        if (TVIS_UI_STAT_OFF == e_g_tvis_ui_status)
        {
            /* ignore directly. */
            return ICLR_OK;
        }
    }

    if (ui1_val == ICL_MSGCVT_UI_NOT_EXIST)
    {
    #ifdef APP_RETAIL_MODE_SUPPORT
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        if (ACFG_RETAIL_MODE_HOME != t_retail_mode)
        {
            return ICLR_OK;
        }
    #endif
        DBG_INFO(("\n<ACR>_resume_tvis\n"));
        //_resume_tvis();
    #ifdef TVIS_TEST_SUPPORT
        _tvis_auto_test();
    #endif
    }
    else if (ui1_val == ICL_MSGCVT_UI_EXIST)
    {
        DBG_INFO(("\n<ACR>_suspend_tvis\n"));
        //_suspend_tvis();
        a_tv_net_send_cmd("\n:dtv_app_mtk,am,:stop=generic_osd\n");
        e_g_tvis_ui_status = TVIS_UI_STAT_OFF;
    }

    return ICLR_OK;
}
#endif

#endif

static VOID _notify_BGM_mode(VOID)
{
    INT32 i4_ret = 0;
    PCL_WAKE_UP_REASON_T    e_wakeup_reason=0;

    /* Get wake-up reason. */
    i4_ret = c_pcl_get_wakeup_reason (& e_wakeup_reason, NULL);
    if ((i4_ret == PCLR_OK) &&
        (e_wakeup_reason == PCL_WAKE_UP_REASON_RTC))
    {
        a_tv_net_send_cmd(":dtv_app_mtk,am,:enter_BGM\n");
    }
}

static VOID _msg_convert_custom_pre_init(VOID)
{
    DBG_INFO(("msgconvert custom: do something before init"));

#ifdef TVIS_SUPPORT
    INT32                       i4_ret;
    HANDLE_T                    h_svctx = NULL_HANDLE;
#endif
    do
    {
        /* DTV02176293 netflix/youtube get screen display region*/
        {
            SCC_DISP_RESOLUTION_T   t_resolution   = {0};
            FILE    *pf_file_netflix      = NULL;
            FILE    *pf_file_cobalt       = NULL;
            INT32    i4_ret               = APP_CFGR_OK;

            #define NETFLIX_PATH        "/tmp/netflix_resolution"
            #define COBALT_PATH         "/tmp/cobalt_resolution"

            i4_ret = a_cfg_custom_get_pannel_resolution(&t_resolution);
            if(APP_CFGR_OK != i4_ret)
            {
                DBG_ERROR((MSCVT_LOG_PREFIX"[resolution +++] {%s %s() %d}. get resolution fail !!\n",__FILE__, __FUNCTION__, __LINE__));
                break;
            }

            /*open or create */
            pf_file_netflix = fopen(NETFLIX_PATH,"w");
            if(NULL == pf_file_netflix)
            {
                DBG_ERROR((MSCVT_LOG_PREFIX"[resolution +++] {%s %s() %d}. open resolution fail !!\n",__FILE__, __FUNCTION__, __LINE__));
                break;
            }

            pf_file_cobalt  = fopen(COBALT_PATH,"w");
            if(NULL == pf_file_cobalt)
            {
                DBG_ERROR((MSCVT_LOG_PREFIX"[resolution +++] {%s %s() %d}. open resolution fail !!\n",__FILE__, __FUNCTION__, __LINE__));
                break;
            }

            /*write */
            fprintf(pf_file_netflix,"%d*%d ",t_resolution.ui2_width,t_resolution.ui2_height);
            fprintf(pf_file_cobalt, "%d*%d ",t_resolution.ui2_width,t_resolution.ui2_height);

            /*close */
            fclose(pf_file_netflix);
            fclose(pf_file_cobalt);
        }

#ifdef TVIS_SUPPORT
        i4_ret = c_svctx_open(SVCTX_NAME_MAIN, &h_svctx);
        if (SVCTXR_OK != i4_ret)
        {
            DBG_ERROR((MSCVT_LOG_PREFIX"\n%s,c_svctx_open failed,i4_ret=%d\n",
                       __FILE__, i4_ret));
        }

        i4_ret = c_svctx_set_listener(h_svctx, _msgconvert_svctx_notify_fct, NULL);
        if (SVCTXR_OK != i4_ret)
        {
            DBG_ERROR((MSCVT_LOG_PREFIX"\n%s,c_svctx_set_listener failed,i4_ret=%d\n",
                       __FILE__, i4_ret));
        }

#ifdef TVIS_UI_SUPPORT
        a_icl_notify_reg(ICL_GRPID_MSGCVT_UI_POPUP,
                         ICL_PRIORITY_DEFAULT,
                         NULL,
                         NULL,
                         _msgsvt_custom_icl_notify,
                         &ui2_g_icl_nfy_id);
        if (i4_ret != ICLR_OK)
        {
            break;
        }
#endif

#ifdef TVIS_TEST_SUPPORT
        _tvis_auto_test_init();
#endif

#endif
    }while(0);

#ifdef TVIS_UI_SUPPORT
    a_icl_notify_unreg(ui2_g_icl_nfy_id);
#endif
}

/* input src changed */
static  VOID _msgcvt_inp_src_chg_nfy_fct(
    UINT16     ui2_nfy_id,
    VOID*      pv_tag,
    UINT16     ui2_id)
{
    CHAR   s_src_name[33] = {0};
    BOOL   b_is_cast = _msg_convert_is_cast_source(s_src_name);

    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s %d] current s_src_name = %s\r\n",__FUNCTION__,__LINE__,s_src_name));

    if(b_is_cast && c_strncmp(s_src_name,"watchfree",9) == 0)
    {
        s_rm("/tmp/inscape/crnt_src_cast");
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[mscvt]Send msg to acr: SIGCONT\n"));
        #ifdef TVIS_SUPPORT
        _resume_tvis();
        INT32 i4_ret = 0;
        pid_t pid = 0;
        pid = _check_tvispid();
        if (pid > 0)
        {
            i4_ret = kill(pid,SIGTTOU);
            DBG_INFO(("<ACR>have signal SIGTTOU,i4_ret=%d,errno=%s\n",
                       i4_ret, strerror(i4_ret)));
        }
        #endif
    }

    if (CFG_MAKE_ID(APP_CFG_GRPID_NAV,APP_CFG_RECID_INPUT_MAIN) == ui2_id)
    {
        if (b_is_cast && c_strncmp(s_src_name,"watchfree",9) != 0)
        {
            //system("touch /tmp/inscape/crnt_src_cast");  //dolphin
            s_touch("/tmp/inscape/crnt_src_cast");
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"Send msg to acr: SIGTSTP\n"));
            //_suspend_tvis();
        }
        else
        {
            //system("rm -f /tmp/inscape/crnt_src_cast");  //dolphin
            s_rm("/tmp/inscape/crnt_src_cast");
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"Send msg to acr: SIGCONT\n"));
            //_resume_tvis();
        }
        _b_input_src_change = TRUE;
    }
}

BOOL _is_browser_ctrl_process_alive()
{
    pid_t pid = 0;
    FILE *fp = fopen("/var/run/browser_ctrl.pid", "r");
    if (fp != NULL) {
        fscanf(fp, "%d", &pid);
        fclose(fp);
    }

    if(pid <= 0 || kill(pid, 0))
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" browser ctrl doesn't exist\n"));
        return FALSE;
    }

    return TRUE;
}

BOOL _is_loki_process_alive()
{
    static pid_t pid = 0;

    if(pid <= 0 || kill(pid, 0))
    {
        //get LOKI pid
        FILE *fp = fopen("/var/run/loki.pid", "r");
        if (fp != NULL) {
            fscanf(fp, "%d", &pid);
            fclose(fp);
        }

        //get new pid then retry.
        if(pid <= 0 || kill(pid, 0))
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" LOKI doesn't exist\n"));
            return FALSE;
        }
    }

    return TRUE;
}

//These keys should send to IOM except special keys.
BOOL _is_system_wise_key(UINT32 ui4_key_symbol)
{
    if (ui4_key_symbol == BTN_POWER        ||
        ui4_key_symbol == BTN_MENU         ||
        ui4_key_symbol == BTN_MIC          ||
        ui4_key_symbol == BTN_VOL_UP       ||
        ui4_key_symbol == BTN_VOL_DOWN     ||
        ui4_key_symbol == BTN_MUTE         ||
        ui4_key_symbol == BTN_CUSTOM_4     || //Mute on key
        ui4_key_symbol == BTN_CUSTOM_5     || //Mute off key
        ui4_key_symbol == BTN_PRG_INFO     ||
        ui4_key_symbol == BTN_INPUT_SRC    ||
        ui4_key_symbol == BTN_P_EFFECT     ||
        ui4_key_symbol == BTN_ASPECT       ||
        ui4_key_symbol == BTN_NETFLIX      ||
        ui4_key_symbol == BTN_YOUTUBE      ||
        ui4_key_symbol == BTN_WIDGET       ||
        ui4_key_symbol == BTN_AMAZON       ||
        ui4_key_symbol == BTN_MGO          ||
        ui4_key_symbol == BTN_VUDU         ||
        ui4_key_symbol == BTN_IHEART_RADIO ||
        ui4_key_symbol == BTN_XUMO         ||
        ui4_key_symbol == BTN_CRACKLE      ||
        ui4_key_symbol == BTN_HULU         ||
        ui4_key_symbol == BTN_WATCHFREE    ||
        ui4_key_symbol == BTN_REDBOX       ||
        ui4_key_symbol == BTN_HAYSTACK     ||
        ui4_key_symbol == (BTN_VOL_UP | KEY_SRC_FRONT_PANEL)     ||
        ui4_key_symbol == (BTN_VOL_DOWN | KEY_SRC_FRONT_PANEL)   ||
        ui4_key_symbol == (KEY_SRC_FRONT_PANEL | BTN_INPUT_SRC)  ||
        ui4_key_symbol == BTN_DISNEY     ||
        ui4_key_symbol == BTN_PARTNER_1  ||
        ui4_key_symbol == BTN_PARTNER_2  ||
        ui4_key_symbol == BTN_PARTNER_3  ||
        ui4_key_symbol == BTN_PARTNER_4  ||
        ui4_key_symbol == BTN_PARTNER_5  ||
        ui4_key_symbol == BTN_PARTNER_6  ||
        ui4_key_symbol == BTN_PARTNER_7  ||
        ui4_key_symbol == BTN_PARTNER_8  ||
        ui4_key_symbol == BTN_PARTNER_9  ||
        ui4_key_symbol == BTN_PARTNER_10 ||
        ui4_key_symbol == BTN_PARTNER_11 ||
        ui4_key_symbol == BTN_PARTNER_12 ||
        ui4_key_symbol == BTN_PARTNER_13 ||
        ui4_key_symbol == BTN_PARTNER_14 ||
        ui4_key_symbol == BTN_PARTNER_15 ||
        ui4_key_symbol == BTN_PARTNER_16 ||
        ui4_key_symbol == BTN_PARTNER_17 ||
        ui4_key_symbol == BTN_PARTNER_18 ||
        ui4_key_symbol == BTN_PARTNER_19 ||
        ui4_key_symbol == BTN_PARTNER_20 ||
        ui4_key_symbol == BTN_PEACOCK ||
        ui4_key_symbol == BTN_TUBI ||
        ui4_key_symbol == BTN_POWER_OFF ||
        ui4_key_symbol == BTN_POWER_ON ||
        ui4_key_symbol == BTN_COMPONENT_1 ||
        ui4_key_symbol == BTN_HDMI_1 ||
        ui4_key_symbol == BTN_HDMI_2 ||
        ui4_key_symbol == BTN_HDMI_3 ||
        ui4_key_symbol == BTN_HDMI_4 ||
        ui4_key_symbol == BTN_HDMI_5 ||
        ui4_key_symbol == BTN_TV )
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
}

VOID _recv_key_event_count(UINT32 ui4_last_tick,UINT32 *ui4_tick_mist_period)
{
    UINT32 ui4_current_tick      = 0;
    UINT32 ui4_tick_period       = 0;

    ui4_tick_period = c_os_get_sys_tick_period();
    ui4_current_tick = c_os_get_sys_tick();

    if (ui4_current_tick >= ui4_last_tick)
    {
        *ui4_tick_mist_period = (ui4_current_tick - ui4_last_tick)*ui4_tick_period;
    }
}
INT32 _msg_convert_check_refresh_blank_scrn( VOID)
{
    INT32 i4_ret  = NAVR_OK;
    CHAR  s_app_name [APP_NAME_MAX_LEN+1] = {0};

    if (menu_custom_blank_oled_scrn_timer_is_start())
    {
        a_am_get_active_app (s_app_name);
        if(c_strcmp ((CHAR*)s_app_name, MSCVT_NAME) == 0)
        {
            i4_ret = menu_blank_oled_scrn_timer_refresh();
            if(i4_ret != NAVR_OK)
            {
                DBG_LOG_PRINT(("[OLED PROTECT] %s %d, timer_refresh failed !!! \n",__FUNCTION__,__LINE__));
                return NAVR_FAIL;
            }
        }
        else
        {
            DBG_ERROR(("[OLED PROTECT] %s %d, is not mscvt !!!\n",__FUNCTION__,__LINE__));
        }
    }

    return i4_ret;
}
UINT32 _get_cur_focus_status(UINT32 ui4_key_symbol,INT32 i4_key_flag )
{
    CHAR        s_focus_name[64] = {0};
    CHAR        s_app_name [APP_NAME_MAX_LEN+1];
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_HOME;

    get_focus_process_app(s_focus_name);
    a_am_get_active_app (s_app_name);
    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s, %d] s_focus_name:%s,s_app_name:%s------\n",__FUNCTION__,__LINE__,s_focus_name,s_app_name));

    // MVV-10940: When browser_ctrl is FG with retail mode, IR keys should be sent to IOM.
    // In this case, even browser_ctrl gets the focus, it will not handle any key events.
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if ((ACFG_RETAIL_MODE_NORMAL == t_retail_mode) && (c_strcmp (s_focus_name, "browser_ctrl") == 0))
    {
        DBG_LOG_PRINT(("[%s, %d]Send key to IOM\n",__FUNCTION__,__LINE__));
        return KEY_TO_IOM;
    }

    if (c_strcmp (s_app_name, MENU_NAME) == 0)
    {
        if( access("/basic/features/VIZIO_FEATURE_SYSTEM_UI", F_OK) == 0
            && access("/3rd_rw/BLOCK_3RD", F_OK) != 0
            && _is_browser_ctrl_process_alive())
        {
            if ( BTN_MIC == ui4_key_symbol       ||
                 BTN_VOL_DOWN == ui4_key_symbol  ||
                 BTN_VOL_UP == ui4_key_symbol    ||
                 BTN_PRG_INFO == ui4_key_symbol  ||
                 BTN_INPUT_SRC == ui4_key_symbol ||
                 BTN_MUTE == ui4_key_symbol      ||
                 BTN_PARTNER_1 == ui4_key_symbol || //camera key
                 BTN_CUSTOM_4 == ui4_key_symbol  || //Mute on key
                 BTN_CUSTOM_5 == ui4_key_symbol  || //Mute off key
                 IOM_GEN_EVT_CODE(BTN_VOL_UP, KEY_SRC_FRONT_PANEL) == ui4_key_symbol     ||
                 IOM_GEN_EVT_CODE(BTN_VOL_DOWN, KEY_SRC_FRONT_PANEL) == ui4_key_symbol   ||
                 IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC) == ui4_key_symbol )
            {
                 if (i4_key_flag & 0x8000) //browser_ctrl return
                 {
                     return KEY_TO_IOM;
                 }
                 else
                 {
                     return KEY_TO_GAM;
                 }
            }
        }
        return KEY_TO_IOM;
    }
    else
    {
        if (_is_system_wise_key(ui4_key_symbol) )//check is KEY_TO_IOM before send key to browser_ctrl
        {
           if( access("/basic/features/VIZIO_FEATURE_SYSTEM_UI", F_OK) == 0
                && access("/3rd_rw/BLOCK_3RD", F_OK) != 0
                && _is_browser_ctrl_process_alive())
           {

                switch(ui4_key_symbol){
                case BTN_VOL_UP:
                case BTN_VOL_DOWN:
                case BTN_MUTE:
                case BTN_PRG_INFO:
                case BTN_INPUT_SRC:
                case BTN_MIC:
                case BTN_PARTNER_1://camera key
                case BTN_CUSTOM_4: //Mute on key
                case BTN_CUSTOM_5: //Mute off key
                case (BTN_VOL_UP | KEY_SRC_FRONT_PANEL):
                case (BTN_VOL_DOWN | KEY_SRC_FRONT_PANEL):
                case (BTN_INPUT_SRC | KEY_SRC_FRONT_PANEL):
                     if (i4_key_flag & 0x8000) //browser_ctrl return
                     {
                         return KEY_TO_IOM;
                     }
                     else
                     {
                         return KEY_TO_GAM;
                     }
                }
            }

            if ( ui4_key_symbol == BTN_NETFLIX && c_strcmp("netflix",s_focus_name) == 0)
            {
                return KEY_TO_GAM;
            }
            else
            {
                return KEY_TO_IOM;
            }
        }
        else if (c_strcmp("dtv_app_mtk",s_focus_name) == 0)
        {

            if ((ui4_key_symbol == BTN_CURSOR_LEFT    ||
                 ui4_key_symbol == BTN_CURSOR_RIGHT   ||
                 ui4_key_symbol == BTN_CURSOR_UP      ||
                 ui4_key_symbol == BTN_CURSOR_DOWN    ||
                 ui4_key_symbol == BTN_SELECT         ||
                 ui4_key_symbol == BTN_RETURN         ||
                 ui4_key_symbol == BTN_EXIT ) &&
                 (_b_system_ui_showing || c_strcmp("wizard",s_app_name) == 0))
            {
                return KEY_TO_GAM;
            }
            else
            {
                return KEY_TO_IOM;
            }

        }

    }

    return KEY_TO_GAM;
}

UINT32 _get_key_dir_by_cur_focus(UINT32 ui4_key_symbol,INT32 i4_key_flag )
{
    CHAR        s_focus_name[64] = {0};
    CHAR        s_app_name [APP_NAME_MAX_LEN+1];
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_HOME;

    get_focus_process_app(s_focus_name);
    a_am_get_active_app (s_app_name);
    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s, %d] s_focus_name:%s,s_app_name:%s------\n",__FUNCTION__,__LINE__,s_focus_name,s_app_name));

    // MVV-10940: When browser_ctrl is FG with retail mode, IR keys should be sent to IOM.
    // In this case, even browser_ctrl gets the focus, it will not handle any key events.
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if ((ACFG_RETAIL_MODE_NORMAL == t_retail_mode) && (c_strcmp (s_focus_name, "browser_ctrl") == 0))
    {
        DBG_LOG_PRINT(("[%s, %d]Send key to IOM\n",__FUNCTION__,__LINE__));
        return KEY_TO_IOM;
    }

    if (c_strcmp (s_app_name, MENU_NAME) == 0)
    {
        if(_is_loki_process_alive())
        {
            if (i4_key_flag & 0x8000)
            {
                return KEY_TO_IOM;
            }
            else
            {
                //return KEY_TO_IOM;//for test in sidebarmenu display in SCH.
                return KEY_TO_GAM;
            }
        }

        return KEY_TO_IOM;
    }
    else
    {
        if(_is_loki_process_alive())
        {
            if (i4_key_flag & 0x8000) //browser_ctrl return
            {
                if (_is_system_wise_key(ui4_key_symbol))//check is KEY_TO_IOM after keys fallback from LOKI
                {
                    if ( ui4_key_symbol == BTN_NETFLIX && c_strcmp("netflix",s_focus_name) == 0)
                    {
                        return KEY_TO_GAM;
                    }
                    else
                    {
                        return KEY_TO_IOM;
                    }
                }
                else if (c_strcmp("dtv_app_mtk",s_focus_name) == 0)
                {
//remove condition for MVV-11935. it is sidebar and system UI are coexist case.
//If sidebar menu and system UI are coexsit, LOKI would send key to sidebar and dtv_svc need handle key(KEY_TO_IOM).
//if only system UI/OOBE showing(without sidebar menu), LOKI should already send key to BR.
#if 0
                    if ((ui4_key_symbol == BTN_CURSOR_LEFT    ||
                         ui4_key_symbol == BTN_CURSOR_RIGHT   ||
                         ui4_key_symbol == BTN_CURSOR_UP      ||
                         ui4_key_symbol == BTN_CURSOR_DOWN    ||
                         ui4_key_symbol == BTN_SELECT         ||
                         ui4_key_symbol == BTN_RETURN         ||
                         ui4_key_symbol == BTN_EXIT ) &&
                         (_b_system_ui_showing || c_strcmp("wizard",s_app_name) == 0))
                    {
                        return KEY_TO_GAM;
                    }
                    else
#endif
                    {
                        return KEY_TO_IOM;
                    }
                }
            }
        }
    }

    return KEY_TO_GAM;
}


static UINT32         ui4_g_last_key_down = 0;

BOOL nav_get_power_to_input_status(VOID)
{
    return b1_power_to_input_flag;
}

VOID nav_set_power_to_input_status(BOOL b1_state)
{
    b1_power_to_input_flag = b1_state;
}

static BOOL  _iom_is_valid_key(UINT32 *ui4_key_symbol,INT32 i4_key_type,INT32 i4_key_flag)
{
    PCL_WAKE_UP_REASON_T        e_wake_up_reason           = PCL_WAKE_UP_REASON_UNKNOWN;
    UINT32                      ui4_wake_up_sub_reason     = 0;
    CHAR        s_focus_name[64] = {0};

    get_focus_process_app(s_focus_name);

    // MVV-11089: block MENU key during OOBE mode.
    // MVV-11204: block Wide/Mic/Picture buttons during OOBE as well
    if (TRUE == a_wzd_is_oobe_mode() || TRUE == a_wzd_is_storedemo_mode())
    {
        switch (*ui4_key_symbol) {
            case BTN_ASPECT:
            case BTN_MENU:
            case BTN_MIC:
            case BTN_P_EFFECT:
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s, %d] block button %d key during OOBE or Storedemo mode\n", __FUNCTION__, __LINE__, *ui4_key_symbol));
                return FALSE;
            default:
                break;
        }
    }

    if (i4_key_type == KEY_STATE_UNUSE || ui4_key_symbol == NULL)
    {
        return FALSE;
    }
#ifdef MT5695_MODEL
    if(((i4_key_type == KEY_STATE_DOWN)||
        (i4_key_type == KEY_STATE_UP))&&
        (ui1_oled_error_count >= 3))
    {
        DBG_ERROR((MSCVT_LOG_PREFIX" OLED ERROR more then 3 times,block \n"));
        return FALSE;
    }

    if(a_oled_compensation_is_running()&& (*ui4_key_symbol & BTN_POWER) != BTN_POWER)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"under screen reflash , should not dispath any key\n"));
        return FALSE;
    }

#endif
    /*power modification display when vizio logo show*/
    if(a_slogo_is_show() && *ui4_key_symbol == BTN_POWER | KEY_SRC_FRONT_PANEL)
    {
         return FALSE;
    }

    if(!a_am_is_power_on())
    {
        if(i4_key_type == KEY_STATE_REPEAT)
        {
            return TRUE;
        }
        /* Get the wakeup reason/sub-reason */
        c_pcl_get_wakeup_reason (&e_wake_up_reason,&ui4_wake_up_sub_reason);

        if((e_wake_up_reason == PCL_WAKE_UP_REASON_AC_POWER && a_bgm_is_running()) || access("/tmp/dtv_svc_is_ready", 0) != 0)
        {
            UINT8 ui1_power_mode = ICL_CUSTOM_POWER_MODE_ECO;
            a_icl_custom_get_power_mode(&ui1_power_mode);
            if(ui1_power_mode == ICL_CUSTOM_POWER_MODE_ECO)
            {
                DBG_ERROR((MSCVT_LOG_PREFIX" under AC ON flow should not dispath any key\n"));
                return FALSE;
            }
        }
    }
    else
    {
        if(!a_am_is_4s_after_power_on() && (*ui4_key_symbol & BTN_POWER) == BTN_POWER)
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s, %d], bypass power key\n", __FUNCTION__, __LINE__));
            return FALSE;
        }

        if(i4_key_type == KEY_STATE_DOWN)
        {
            if((ui4_g_last_key_down == *ui4_key_symbol) &&
               ((ui4_g_last_key_down == BTN_NETFLIX && (_b_hotkey_netflix_started)) ||
                ui4_g_last_key_down == BTN_AMAZON ||
                ui4_g_last_key_down == BTN_YOUTUBE))
           {
                // MVV-11096: if CSP already gets the focus, dispatch the key.
                if (c_strcmp("netflix",s_focus_name) == 0)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"native CSP gets focused, dispatch key\n"));
                    return TRUE;
                }

                if(i4_key_flag & 0x8000)
                {
                    return TRUE;
                }
                else
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"repeat navtive app[0x%x], check focus name\n",*ui4_key_symbol));
                    return FALSE;
                }
           }
        }
    }
    return TRUE;
}

#define  LONG_PRESS_SELECT_BTN_P_EFFECT  FALSE

static INT32  _iom_loki_key_handle_fct(UINT32 *ui4_key_symbol,INT32 i4_key_type,INT32 i4_key_flag)
{
    /*keep*/
    static BOOL                 b_recv_key_down            = false;
    static BOOL                 b1_is_need_key_event       = TRUE; //if need to handle key
    static BOOL                 b1_need_analog_key         = FALSE;
    UINT32                      ui4_key_count              = 0;
    UINT32                      ui4_key_dir                = KEY_TO_UNUSE;
    UINT8                       u1_zoom_status             = APP_CFG_CUST_ZOOM_MODE_OFF ;
    static BOOL                 b1_repeat_to_bro_ctrl_flag = FALSE;
    static BOOL                 b1_save_down_status        = FALSE;
    ACFG_RETAIL_MODE_T          t_retail_mode              = ACFG_RETAIL_MODE_LAST_ENTRY;
    NAV_RETAIL_MODE_STATUS_T    e_retail_status            = NAV_RETAIL_MODE_INITIAL;
    NAV_RETAIL_MODE_POPUP_DLG_T e_popup_dlg                = NAV_RETAIL_MODE_NO_POPUP_DLG;
    UINT32                      ui4_drv_eco                = 0;
    PCL_WAKE_UP_REASON_T        e_wake_up_reason           = PCL_WAKE_UP_REASON_UNKNOWN;
    UINT32                      ui4_wake_up_sub_reason     = 0;
    static UINT32               ui4_long_power_type        = PRESS_KEYPAD_POWER_INVALID;

    if( *ui4_key_symbol )
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" === start == {%s,%d} *ui4_key_symbol:0x%x, i4_key_type:%d, i4_key_flag:%X\n",
                        __FUNCTION__, __LINE__, *ui4_key_symbol, i4_key_type, i4_key_flag ));
    }

    if (!_iom_is_valid_key(ui4_key_symbol,i4_key_type,i4_key_flag))
    {
        return KEY_TO_UNUSE;
    }

    a_cfg_cust_get_zoom_status(&u1_zoom_status);

    if (b1_is_need_key_event == FALSE && i4_key_type != KEY_STATE_DOWN)
    {
        if (b1_need_analog_key == TRUE && i4_key_type == KEY_STATE_REPEAT)
        {
            b1_need_analog_key = FALSE;
            /*send analog up key*/
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] last_key_symbol:%x, last_save_key_type:%d \n",
                        __LINE__, last_key_info.ui4_key_symbol, last_key_info.ui4_save_key_type));
            c_iom_send_evt_single(last_key_info.ui4_key_symbol, FALSE);
        }
        return KEY_TO_UNUSE;
    }

    if(*ui4_key_symbol == BTN_CUSTOM_102 && i4_key_type == KEY_STATE_DOWN)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] media key launch mmp\n", __LINE__));
#ifdef  APP_C4TV_SUPPORT
        a_rest_app_launch_native_app_notify("REST_APP_NAME_NATIVE_MMP");
#endif
        rest_event_notify_current_input("usb");
        a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
        return KEY_TO_UNUSE;
    }

    /*if receive down event*/
    if (i4_key_type == KEY_STATE_DOWN)
    {
         /*check refresh timer or not SCH UI when pressed D-key*/
        _msg_convert_check_refresh_blank_scrn();

        b_recv_key_down    = TRUE;
        b1_is_need_key_event = TRUE;
        ui4_key_dir          = _get_key_dir_by_cur_focus(*ui4_key_symbol,i4_key_flag);
        ui4_last_tick        = c_os_get_sys_tick();
        long_key_symbol      = 0x00;
        ui4_long_power_type  = PRESS_KEYPAD_POWER_INVALID;
        ui4_g_last_key_down  = *ui4_key_symbol;

        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key down : ui4_key_dir: %X, key_symbol:%X, key_flag:%X \n",
                        __LINE__, ui4_key_dir, *ui4_key_symbol, i4_key_flag));

        if (APP_CFG_CUST_ZOOM_MODE_OFF == u1_zoom_status)
        {
            a_nav_zoom_cust_set_digital_pad_status(FALSE);
        }

        if (i4_key_flag & 0x8000) //browser_ctrl return
        {
            DBG_LOG_PRINT(("\n\033[1;33m key down LOKI return %s:%d,\033[m\n", __FUNCTION__, __LINE__));

            b1_save_down_status = TRUE;

            if ( (*ui4_key_symbol == BTN_MUTE) ||
                 (*ui4_key_symbol == BTN_CUSTOM_4) || //Mute on key
                 (*ui4_key_symbol == BTN_CUSTOM_5) || //Mute off key
                 (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)) )
            {
                ui4_key_dir = KEY_TO_UNUSE;
                long_key_symbol = *ui4_key_symbol;
            }

            //suport long key.
            if (*ui4_key_symbol == BTN_P_EFFECT                              ||
       #if (LONG_PRESS_SELECT_BTN_P_EFFECT == TRUE)
             *ui4_key_symbol == BTN_SELECT                                   ||
       #endif
             *ui4_key_symbol == BTN_CC                                       ||
             *ui4_key_symbol == BTN_ASPECT                                   ||  //zoom
             *ui4_key_symbol == BTN_MENU                                     ||
             *ui4_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL)            ||
             *ui4_key_symbol == (BTN_INPUT_AND_VOL_UP | KEY_SRC_FRONT_PANEL) ||
             *ui4_key_symbol == (BTN_INPUT_AND_VOL_DOWN | KEY_SRC_FRONT_PANEL))
            {
                ui4_key_dir = KEY_TO_UNUSE;
                long_key_symbol = *ui4_key_symbol;

                /*need send to gam*/
                if (*ui4_key_symbol == BTN_CC &&  _get_key_dir_by_cur_focus(*ui4_key_symbol,i4_key_flag) == KEY_TO_GAM)
                {
                    ui4_key_dir = KEY_TO_GAM;
                }
            }

            if ( (ui4_key_dir == KEY_TO_IOM) || (KEY_TO_GAM == ui4_key_dir) )
            {
                b1_repeat_to_bro_ctrl_flag = FALSE;
            }
        }
        else
        {
            //zoom mode on
            //handle keys before send to LOKI in zoom mode on case.
            if (APP_CFG_CUST_ZOOM_MODE_ON == u1_zoom_status)
            {
                if (*ui4_key_symbol == BTN_DIGIT_1 || *ui4_key_symbol == BTN_DIGIT_2 || *ui4_key_symbol == BTN_DIGIT_3 ||
                    *ui4_key_symbol == BTN_DIGIT_4 || *ui4_key_symbol == BTN_DIGIT_5 || *ui4_key_symbol == BTN_DIGIT_6 ||
                    *ui4_key_symbol == BTN_DIGIT_7 || *ui4_key_symbol == BTN_DIGIT_8 || *ui4_key_symbol == BTN_DIGIT_9 ||
                    *ui4_key_symbol == BTN_KB_MINUS_SIGN)
                {
                    if (a_nav_zoom_cust_get_digital_pad_status() == FALSE)
                    {
                        ui4_key_dir = KEY_TO_UNUSE;
                    }
                    else
                    {
                        ui4_key_dir = _get_key_dir_by_cur_focus(*ui4_key_symbol, i4_key_flag);
                    }
                }
                else if( *ui4_key_symbol == BTN_CURSOR_LEFT  || *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                         *ui4_key_symbol == BTN_CURSOR_UP    || *ui4_key_symbol == BTN_CURSOR_DOWN)
                {
                    if(a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
                    {
                        ui4_key_dir = KEY_TO_UNUSE;
                    }
                }
                else if (*ui4_key_symbol == BTN_DIGIT_0)
                {
                    ui4_key_dir = KEY_TO_GAM;
                }
            }

            /*dtv_src UI don't show, Send to conjure*/
            if(ui4_key_dir == KEY_TO_GAM)
            {
                if ( (*ui4_key_symbol == BTN_MUTE) ||
                (*ui4_key_symbol == BTN_CUSTOM_4) || //Mute on key
                (*ui4_key_symbol == BTN_CUSTOM_5) || //Mute off key
                (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)) )
                {
                    long_key_symbol = *ui4_key_symbol;
                }

                /*give to browser_ctrl handle this key*/
                b1_repeat_to_bro_ctrl_flag = TRUE;
                ui4_key_dir = KEY_TO_LOKI;
                DBG_LOG_PRINT(("\n\033[1;33m key down to LOKI %s:%d,\033[m\n", __FUNCTION__, __LINE__));
            }
            else
            {
                b1_repeat_to_bro_ctrl_flag = FALSE;
            }
        }

        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} ui4_key_dir:%d, long_key_symbol=0x%x\n, b1_repeat_to_bro_ctrl_flag=%d",
            __FUNCTION__, __LINE__, ui4_key_dir, long_key_symbol, b1_repeat_to_bro_ctrl_flag ));

        // combination of key
        if (ui4_vol_input_symbol != 0x00)
        {
            if ( ( (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP))
                && (ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)) )
               ||
                 ( (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC))
                 &&(ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP)) )
               )
            {
                ui4_key_dir = KEY_TO_UNUSE;
                ui4_last_tick = c_os_get_sys_tick();
                long_key_symbol = BTN_LONG_INPUT_VOL_UP;

                /*send analog null key*/
                c_iom_send_evt_single(0x00, TRUE);
            }
            else if ( ( *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN)
                      &&ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC) )
                    ||
                      ( *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)
                      &&ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN) )
                    )
            {
                ui4_key_dir = KEY_TO_UNUSE;
                ui4_last_tick = c_os_get_sys_tick();
                long_key_symbol =  BTN_LONG_INPUT_VOL_DOWN;

                /*send analog null key*/
                c_iom_send_evt_single(0x00, TRUE);
            }
        }

        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} ui4_key_dir:%d, long_key_symbol=0x%x\n",
                    __FUNCTION__, __LINE__, ui4_key_dir, long_key_symbol ));

        ui4_vol_input_symbol = *ui4_key_symbol;
        last_key_info.ui4_save_key_type = ui4_key_dir;
    }

    /*key down*/
    if (b_recv_key_down == TRUE)
    {
        /*key up*/
        if (i4_key_type == KEY_STATE_UP)
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key up : ui4_key_dir: %X, key_symbol:%x, key_flag:%x \n",
                        __LINE__, ui4_key_dir, *ui4_key_symbol, i4_key_flag));

            b_recv_key_down = FALSE;
            ui4_vol_input_symbol = 0x00;

            //count < 5s
            _recv_key_event_count(ui4_last_tick, &ui4_key_count);

            if (long_key_symbol != 0x00)
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key up(check long key): key_count:%d, key_symbol:%x \n",
                    __LINE__, ui4_key_count, *ui4_key_symbol));

                if ( ( (long_key_symbol != BTN_MUTE) && (long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL))
                     && (ui4_key_count < 5000) )
                   ||(long_key_symbol == BTN_MUTE && ui4_key_count < 2000)
                   ||(long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) && ui4_key_count < 2000)
                   )
                {
                    //short press
                    b1_need_analog_key = TRUE;
                    b1_is_need_key_event = FALSE;
                    ui4_key_dir = KEY_TO_UNUSE;//_get_cur_focus_status(*ui4_key_symbol);

                    /*input and vol+/- no work*/
                    if (long_key_symbol != BTN_LONG_INPUT_VOL_DOWN &&
                        long_key_symbol != BTN_LONG_INPUT_VOL_UP &&
                        long_key_symbol != BTN_MUTE &&
                        long_key_symbol != IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC))
                    {
                        BOOL bSendKey = TRUE;

                #ifdef  MT5583_MODEL
                        if (  a_am_is_power_on() && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                        {
                            nav_set_power_to_input_status(TRUE);
                            *ui4_key_symbol = BTN_INPUT_SRC;
                        }
                        else {
                            nav_set_power_to_input_status(FALSE);
                        }
                 #endif

                        if (is_one_button_model_platform() == TRUE)
                        {
                            if ( a_am_is_power_on() && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) )
                            {
                                nav_set_power_to_input_status(TRUE);
                                *ui4_key_symbol = BTN_INPUT_SRC;
                            }
                            else {
                                nav_set_power_to_input_status(FALSE);
                            }
                        }

                        if (is_one_button_model_platform() == FALSE) // 4 button back panel
                        {
                            if ( a_am_is_power_on() && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL)
                               &&(ui4_key_count > 1000)
                               )
                            {
                                bSendKey = FALSE;
                                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[[%d][4 key][POWER] 2000 > %d > 1000 => IGNORE \n", __LINE__, ui4_key_count));
                            }
                        }

                        /*send analog down key*/
                        if ( bSendKey ) {
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                        }
                    }

                    /*need send to gam*/
                    if (*ui4_key_symbol == BTN_CC &&  _get_key_dir_by_cur_focus(*ui4_key_symbol,i4_key_flag) == KEY_TO_GAM)
                    {
                        ui4_key_dir = KEY_TO_GAM;
                    }
                    /*short mute only need to send to browser_ctrl*/
                    else if ( *ui4_key_symbol == BTN_MUTE ||
                              *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC))
                    {
                         DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] mute key, key_symbol:%x, key_flag:%x, save_down_status:%d \n",
                         __LINE__, *ui4_key_symbol, i4_key_flag, b1_save_down_status));

                        /*need to handle browser_ctrl  return key up*/
                        if (i4_key_flag & 0x8000) //browser_ctrl return
                        {

                            b_recv_key_down = FALSE;
                            b1_save_down_status = FALSE;
                            b1_need_analog_key = TRUE;
                            b1_is_need_key_event = FALSE;
                            last_key_info.ui4_key_symbol = BTN_EXIT;

                            /*send analog down key*/
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                        }
                        else
                        {
                            if (b1_save_down_status == TRUE)
                            {
                                b_recv_key_down = TRUE;
                            }

                            b1_need_analog_key = FALSE;
                            /*need second key up*/
                            b1_is_need_key_event = TRUE;
                            ui4_key_dir =  KEY_TO_LOKI;

                            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

                            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode &&
                                (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)))
                            {
                                b1_need_analog_key = TRUE;
                                b1_is_need_key_event = FALSE;
                                last_key_info.ui4_key_symbol = BTN_EXIT;

                                /*send analog down key*/
                                c_iom_send_evt_single(BTN_EXIT, TRUE);
                            }
                        }
                    }

                    if (b1_save_down_status == FALSE)
                    {
                        ui4_last_tick = 0;
                        long_key_symbol = 0x00;
                    }
                }
                else
                {
                    b1_need_analog_key = TRUE;
                    b1_is_need_key_event = FALSE;
                    ui4_key_dir = KEY_TO_UNUSE;

                    if (is_one_button_model_platform() == TRUE)
                    {
                        if (long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                        {
                            if (ui4_key_count < KEY_TIME_12_SEC)
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_LONG_POWER;
                                DBG_LOG_PRINT ((" [%s][%d] BTN_LONG_POWER \r\n", __FUNCTION__, __LINE__));

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }
                    }
                    else // 4 key
                    {
                        if (long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL)) {
                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[[%d][4 key][POWER] %d => IGNORE \n", __LINE__, ui4_key_count));
                        }
                    }
                }
            }
            /*short symbol*/
            else
            {
                /*key up*/
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] short key up : key_symbol:%x, zoom_status:%d, save_key_type:%d \n",
                __LINE__, *ui4_key_symbol, u1_zoom_status, last_key_info.ui4_save_key_type));

                if (i4_key_flag & 0x8000 || last_key_info.ui4_save_key_type != KEY_TO_LOKI) //LOKI return
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key up LOKI return, key_symbol:%x, key_flag:%X \n", \
                                    __LINE__, *ui4_key_symbol, i4_key_flag));

                    b1_need_analog_key = FALSE;
                    b1_is_need_key_event = FALSE;
                    b_recv_key_down = FALSE;
                    b1_save_down_status = FALSE;
                    ui4_key_dir = last_key_info.ui4_save_key_type;

                    if (APP_CFG_CUST_ZOOM_MODE_ON == u1_zoom_status)
                    {
                        /*check navigation mode*/
                        if(a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
                        {
                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[navigation pad +++] {%s %s() %d}. digital pad key !!! *ui4_key_symbol: 0x%x\n",__FILE__, __FUNCTION__, __LINE__,*ui4_key_symbol));

                            if( *ui4_key_symbol == BTN_CURSOR_LEFT  || *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                                *ui4_key_symbol == BTN_CURSOR_UP    || *ui4_key_symbol == BTN_CURSOR_DOWN)
                            {
                                *ui4_key_symbol = a_nav_zoom_cust_navigation_num_pad(*ui4_key_symbol);
                                /* change the digit kay to special keys defined for Number Pad Zoom Navigation */
                                //*ui4_key_symbol = BTN_GFX_ZOOM_SECTOR_1 + (*ui4_key_symbol - BTN_DIGIT_1);
                                /*send analog down key*/
                                b1_need_analog_key = TRUE;
                                ui4_key_dir = KEY_TO_UNUSE;

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }

                        if (a_nav_zoom_cust_get_digital_pad_status() == FALSE)
                        {
                            if (*ui4_key_symbol >= BTN_DIGIT_1 && *ui4_key_symbol <= BTN_DIGIT_9)
                            {
                                /* change the digit kay to special keys defined for Number Pad Zoom Navigation */
                                *ui4_key_symbol = BTN_GFX_ZOOM_SECTOR_1 + (*ui4_key_symbol - BTN_DIGIT_1);
                                /*send analog down key*/
                                b1_need_analog_key = TRUE;
                                ui4_key_dir = KEY_TO_UNUSE;

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }
                        else
                        {
                            if (*ui4_key_symbol >= BTN_DIGIT_0 && *ui4_key_symbol <= BTN_DIGIT_9)
                            {
                                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s][%d] a_nav_zoom_cust_enable_dash_timer \n",
                                __FUNCTION__, __LINE__));

                                a_nav_zoom_cust_enable_dash_timer();
                            }
                        }

                        BOOL b_digital_timer = a_nav_zoom_cust_get_digital_timer_status();
                        BOOL b_zoom_digit_selection_support = a_cfg_cust_zoom_digit_selection_support();

                        DBG_INFO((MSCVT_LOG_PREFIX"[navigation pad +++] [%s][%d] digital pad key !!! *ui4_key_symbol: 0x%x,digital pad status = %s\n",
                        __FUNCTION__, __LINE__,*ui4_key_symbol,a_nav_zoom_cust_get_digital_pad_status() == TRUE ? "digital pad":"zoom pad"));

                        DBG_INFO(("[ZOOM] Digit selection support : %d\n", b_zoom_digit_selection_support));

                        if (*ui4_key_symbol == BTN_KB_MINUS_SIGN
                            && b_zoom_digit_selection_support == TRUE)
                        {
                            if(b_digital_timer == FALSE)
                            {
                                /* change the Dash kay to special keys defined for Number Pad Zoom Navigation */
                                *ui4_key_symbol = BTN_GFX_ZOOM_NAVIGATION;
                                /*send analog down key*/
                                b1_need_analog_key = TRUE;
                                ui4_key_dir = KEY_TO_UNUSE;

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }
                        else if (*ui4_key_symbol == BTN_DIGIT_0)
                        {
                            /*send analog down key*/
                            b1_need_analog_key = TRUE;
                            ui4_key_dir = KEY_TO_GAM;

                            /*send analog down key*/
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                        }
                    }
                }
                else
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key up to LOKI, key_symbol:%x, key_flag:%x, last_save_key_type:%x \n",
                    __LINE__, *ui4_key_symbol, i4_key_flag, last_key_info.ui4_save_key_type));

                    /*dtv_src UI don`t show,Send to conjure*/
                    if (last_key_info.ui4_save_key_type == KEY_TO_LOKI)
                    {
                        /*give to browser_ctrl  handle this key*/
                        b1_repeat_to_bro_ctrl_flag = FALSE;
                        ui4_key_dir = KEY_TO_LOKI;

                        /*need to handle browser_ctrl  return key up*/
                        if (b1_save_down_status == TRUE)
                        {
                            b_recv_key_down = TRUE;
                        }

                        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
                        if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode &&
                            ( *ui4_key_symbol == BTN_INPUT_SRC))
                        {
                            b1_need_analog_key = TRUE;
                            b1_is_need_key_event = FALSE;
                            last_key_info.ui4_key_symbol = BTN_EXIT;

                            /*send analog down key*/
                            c_iom_send_evt_single(BTN_EXIT, TRUE);
                        }

                    }
                    else
                    {
                        b1_need_analog_key = FALSE;
                        b1_is_need_key_event = FALSE;
                        b_recv_key_down = FALSE;
                        ui4_key_dir = last_key_info.ui4_save_key_type;
                    }
                }
            }
        }
        /*repeat*/
        else if (i4_key_type == KEY_STATE_REPEAT)
        {
            if( *ui4_key_symbol )
            {
                DEBUG_KEY_FLOW(DBG_LOG_PRINT(MSCVT_LOG_PREFIX"[%d] key repeat : ui4_key_dir: %X, key_symbol:%x, key_flag:%x b1_repeat_to_bro_ctrl_flag:%x\n",
                            __LINE__, ui4_key_dir, *ui4_key_symbol, i4_key_flag, b1_repeat_to_bro_ctrl_flag););
            }

            if (long_key_symbol != 0x00)
            {
                _recv_key_event_count(ui4_last_tick, &ui4_key_count);
                /*count > 5s */

                //DBG_LOG_PRINT((" [%d] ui4_key_count: %d \n", __LINE__, ui4_key_count));

                if ( (ui4_key_count >= 5000 && long_key_symbol != BTN_MUTE && long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL))
                   ||(ui4_key_count >= 2000 && long_key_symbol == BTN_MUTE )
                   ||(ui4_key_count >= 2000 && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                   )
                {
                    if ( (long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL) && long_key_symbol != BTN_LONG_INPUT_VOL_DOWN)
                       ||(long_key_symbol == BTN_LONG_INPUT_VOL_DOWN & ui4_key_count > 10000)
                       ||(long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) && ui4_key_count > 12000) )
                    {
                        b1_need_analog_key = TRUE;
                        b1_is_need_key_event = FALSE;
                        ui4_key_dir = KEY_TO_UNUSE;
                        b_recv_key_down = FALSE;
                        ui4_last_tick = 0;

                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key repeat: key_count:%d, key_symbol:%X \n",
                            __LINE__, ui4_key_count, *ui4_key_symbol));
                    }

                    {
                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key repeat: key_count:%d, key_symbol:%x \n",
                            __LINE__, ui4_key_count, *ui4_key_symbol));

                        /*change key value*/
                        if (long_key_symbol == BTN_MUTE)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_BLANK_SCREEN;
                        }
                        else if(long_key_symbol == BTN_CC)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_CC;
                        }
                        else if(long_key_symbol == BTN_P_EFFECT)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_P_EFFECT;

                            DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} *ui4_key_symbol = BTN_LONG_P_EFFECT;\n",
                                                __FUNCTION__, __LINE__ )); );
                        }
                  #if (LONG_PRESS_SELECT_BTN_P_EFFECT == TRUE)
                        else if(long_key_symbol == BTN_SELECT)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_PRESS_SELECT;
                        }
                  #endif
                        else if(long_key_symbol == BTN_ASPECT)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_GFX_ZOOM;
                        }
                        else if(long_key_symbol == BTN_MENU)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_MENU;
                        }
                        else if(long_key_symbol == (BTN_INPUT_SRC | KEY_SRC_FRONT_PANEL))
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_INPUT;
                        }
                        else if(long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                        {
                            if (is_one_button_model_platform() == TRUE)
                            {
                                /*change key symbol*/
                                if ( (ui4_key_count >= KEY_TIME_2_SEC) && (ui4_key_count < KEY_TIME_7_SEC)
                                   &&(ui4_long_power_type != PRESS_KEYPAD_POWER_2_SEC) )
                                {
                                    b1_need_analog_key = FALSE;
                                    ui4_long_power_type = PRESS_KEYPAD_POWER_2_SEC;
                                    DBG_LOG_PRINT ((" [%s][%d] PRESS_KEYPAD_POWER_2_SEC \r\n", __FUNCTION__, __LINE__));
                                    nav_request_context_switch(nav_long_press_power_nfy_timer,
                                                                (VOID*) 3000,
                                                                (VOID*) ui4_long_power_type,
                                                                NULL);

                                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] keypad power key repeat 2 sec \n", __LINE__));
                                }
                                else if ( (ui4_key_count >= KEY_TIME_7_SEC) && (ui4_key_count < KEY_TIME_12_SEC)
                                    &&(ui4_long_power_type != PRESS_KEYPAD_POWER_7_SEC) )
                                {
                                    b1_need_analog_key = FALSE;
                                    ui4_long_power_type = PRESS_KEYPAD_POWER_7_SEC;
                                    DBG_LOG_PRINT ((" [%s][%d] PRESS_KEYPAD_POWER_7_SEC \r\n", __FUNCTION__, __LINE__));
                                    nav_request_context_switch(nav_long_press_power_nfy_timer,
                                                                (VOID*) 3000,
                                                                (VOID*) ui4_long_power_type,
                                                                NULL);
                                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] keypad power key repeat 7 sec \n", __LINE__));
                                 }
                                 else if (ui4_key_count >= 12000)
                                 {
                                     /*change key symbol*/
                                     ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;
                                     *ui4_key_symbol = BTN_LONG_POWER_12S;
                                     DBG_LOG_PRINT ((" [%s][%d] BTN_LONG_POWER_12S \r\n", __FUNCTION__, __LINE__));
                                 }
                            }
                            else // 4 button
                            {
                                if (ui4_key_count >= 5000)
                                {
                                     b1_need_analog_key = TRUE;
                                     b1_is_need_key_event = FALSE;
                                     ui4_key_dir = KEY_TO_UNUSE;
                                     b_recv_key_down = FALSE;
                                     ui4_last_tick = 0;

                                     /*change key symbol*/
                                     ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;
                                     *ui4_key_symbol = BTN_LONG_POWER;
                                     DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[[%d][4 key][POWER] %d \n", __LINE__, ui4_key_count));
                                }
                            }
                        }
                        else if (long_key_symbol == BTN_LONG_INPUT_VOL_UP)
                        {
                            *ui4_key_symbol = BTN_LONG_INPUT_VOL_UP;
                        }
                        else if (long_key_symbol == BTN_LONG_INPUT_VOL_DOWN)
                        {
                             /*change key symbol*/
                             if ( ((ui4_key_count >= KEY_TIME_5_SEC) && (ui4_key_count < KEY_TIME_10_SEC))
                                &&(ui4_long_power_type != PRESS_KEYPAD_VOL_DOWN_AND_INPUT_5_SEC) )
                             {
                                 b1_need_analog_key = FALSE;
                                 ui4_long_power_type = PRESS_KEYPAD_VOL_DOWN_AND_INPUT_5_SEC;

                                 //"Reset to Defaults, from the back panel, press the Input for 10 seconds." is no need.
                                 //nav_request_context_switch(vol_down_input_notify_factory_reset,NULL,NULL,NULL);

                                 *ui4_key_symbol = BTN_LONG_INPUT_VOL_DOWN;

                                 DBG_LOG_PRINT((MSCVT_LOG_PREFIX" input & vol down key repeat 5 sec \n"));
                             }
                             else if (ui4_key_count >= KEY_TIME_10_SEC)
                             {
                                 ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;
                                 *ui4_key_symbol = BTN_LONG_INPUT_VOL_DOWN_10S;

                                 DBG_LOG_PRINT((MSCVT_LOG_PREFIX" input & vol down key repeat 10 sec \n"));
                             }
                        }

                        /*send analog down key*/
                        if (b1_need_analog_key == TRUE)
                        {
                            /*send analog down key*/
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);

                            long_key_symbol = 0x00;
                            ui4_vol_input_symbol = 0x00;
                        }
                    }
                }
                else
                {
                    ui4_key_dir = KEY_TO_IGNORE;
                }
            }
            else if(b1_repeat_to_bro_ctrl_flag == TRUE)
            {
                 ui4_key_dir = KEY_TO_LOKI;
            }
            else
            {
                if (*ui4_key_symbol == BTN_CURSOR_LEFT  ||
                    *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                    *ui4_key_symbol == BTN_CURSOR_UP    ||
                    *ui4_key_symbol == BTN_CURSOR_DOWN )
                {
                    //ui4_key_dir = _get_key_dir_by_cur_focus(*ui4_key_symbol,i4_key_flag);
                    ui4_key_dir = last_key_info.ui4_save_key_type;//send repeat key to last key_dir. It should be same as [key down].
                }
                else
                {
                    ui4_key_dir = KEY_TO_IGNORE;
                }
            }
        }

        last_key_info.ui4_key_symbol = *ui4_key_symbol;
    }

    if (ui4_key_dir == KEY_TO_IOM || ui4_key_dir == KEY_TO_GAM || ui4_key_dir == KEY_TO_LOKI)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" === end == [%s:%d] [%s] key_dir:%d, key_symbol:0x%X \n",
                        __FUNCTION__,
                        __LINE__,
                        i4_key_type == KEY_STATE_DOWN ? "key down" :
                        i4_key_type == KEY_STATE_UP  ? "key up" : "key repeat",
                        ui4_key_dir, *ui4_key_symbol));
    }
    else if (ui4_key_dir == KEY_TO_IGNORE)
    {
        //DBG_LOG_PRINT ((MSCVT_LOG_PREFIX"[%s] IGNORE key_symbol:0x%X \n", __FUNCTION__, *ui4_key_symbol));
    }

    if (ui4_key_dir == KEY_TO_LOKI)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[_iom_loki_key_handle_fct] Reset power off timer for AirPlay\n"));
        nav_pwr_system_ui_key_nfy();
    }

    return ui4_key_dir;
}

static INT32  _iom_system_ui_key_handle_fct(UINT32 *ui4_key_symbol,INT32 i4_key_type,INT32 i4_key_flag)
{
    /*keep*/
    static BOOL                 b_recv_key_down            = false;
    static BOOL                 b1_is_need_key_event       = TRUE; //if need to handle key
    static BOOL                 b1_need_analog_key         = FALSE;
    UINT32                      ui4_key_count              = 0;
    UINT32                      ui4_key_dir                = KEY_TO_UNUSE;
    UINT8                       u1_zoom_status             = APP_CFG_CUST_ZOOM_MODE_OFF ;
    static BOOL                 b1_repeat_to_bro_ctrl_flag = FALSE;
    static BOOL                 b1_save_down_status        = FALSE;
    ACFG_RETAIL_MODE_T          t_retail_mode              = ACFG_RETAIL_MODE_LAST_ENTRY;
    NAV_RETAIL_MODE_STATUS_T    e_retail_status            = NAV_RETAIL_MODE_INITIAL;
    NAV_RETAIL_MODE_POPUP_DLG_T e_popup_dlg                = NAV_RETAIL_MODE_NO_POPUP_DLG;
    UINT32                      ui4_drv_eco                = 0;
    PCL_WAKE_UP_REASON_T        e_wake_up_reason           = PCL_WAKE_UP_REASON_UNKNOWN;
    UINT32                      ui4_wake_up_sub_reason     = 0;
    static UINT32               ui4_long_power_type        = PRESS_KEYPAD_POWER_INVALID;

    if( *ui4_key_symbol )
    {
        DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} *ui4_key_symbol:0x%x, i4_key_type:%d, i4_key_flag:%d\n",
                        __FUNCTION__, __LINE__, *ui4_key_symbol, i4_key_type, i4_key_flag )); );
    }

    if (!_iom_is_valid_key(ui4_key_symbol,i4_key_type,i4_key_flag))
    {
        return KEY_TO_UNUSE;
    }

    a_cfg_cust_get_zoom_status(&u1_zoom_status);

    if (b1_is_need_key_event == FALSE && i4_key_type != KEY_STATE_DOWN)
    {
        if (b1_need_analog_key == TRUE && i4_key_type == KEY_STATE_REPEAT)
        {
            b1_need_analog_key = FALSE;
            /*send analog up key*/
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] last_key_symbol:%x, last_save_key_type:%d \n",
                        __LINE__, last_key_info.ui4_key_symbol, last_key_info.ui4_save_key_type));
            c_iom_send_evt_single(last_key_info.ui4_key_symbol, FALSE);
        }
        return KEY_TO_UNUSE;
    }

    if(*ui4_key_symbol == BTN_CUSTOM_102 && i4_key_type == KEY_STATE_DOWN)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] media key launch mmp\n", __LINE__));
#ifdef  APP_C4TV_SUPPORT
        a_rest_app_launch_native_app_notify("REST_APP_NAME_NATIVE_MMP");
#endif
        rest_event_notify_current_input("usb");
        a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
        return KEY_TO_UNUSE;
    }

    // default setting for one button panel key flag
    //if(nav_get_power_to_input_status() == TRUE)
    {
    //    nav_set_power_to_input_status(FALSE);
    }

    /*if receive down event*/
    if (i4_key_type == KEY_STATE_DOWN)
    {
         /*check refresh timer or not SCH UI when pressed D-key*/
        _msg_convert_check_refresh_blank_scrn();

        b_recv_key_down    = TRUE;
        b1_is_need_key_event = TRUE;
        ui4_key_dir          = _get_cur_focus_status(*ui4_key_symbol,i4_key_flag);
        ui4_last_tick        = c_os_get_sys_tick();
        long_key_symbol      = 0x00;
        ui4_long_power_type  = PRESS_KEYPAD_POWER_INVALID;
        ui4_g_last_key_down  = *ui4_key_symbol;

        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key down : ui4_key_dir: %X, key_symbol:%X, key_flag:%X \n",
                        __LINE__, ui4_key_dir, *ui4_key_symbol, i4_key_flag));

        if (APP_CFG_CUST_ZOOM_MODE_OFF == u1_zoom_status)
        {
            a_nav_zoom_cust_set_digital_pad_status(FALSE);
        }

    #if 0
        /*Group1:only need to send to iom*/
        if ( *ui4_key_symbol == BTN_MIC ||
             *ui4_key_symbol == BTN_VOL_DOWN ||
             *ui4_key_symbol == BTN_VOL_UP ||
             *ui4_key_symbol == BTN_PRG_INFO ||
             *ui4_key_symbol == BTN_INPUT_SRC)
        {
             b1_repeat_to_bro_ctrl_flag = TRUE;
             ui4_key_dir = KEY_TO_BR;
        }
        /*Group2:first, send to iom,and wait for second*/
        else
    #endif
        if ((*ui4_key_symbol == BTN_CURSOR_LEFT    ||
             *ui4_key_symbol == BTN_CURSOR_RIGHT   ||
             *ui4_key_symbol == BTN_CURSOR_UP      ||
             *ui4_key_symbol == BTN_CURSOR_DOWN    ||
           #if (LONG_PRESS_SELECT_BTN_P_EFFECT == FALSE)
             *ui4_key_symbol == BTN_SELECT         ||
           #endif
             *ui4_key_symbol == BTN_RETURN         ||
             *ui4_key_symbol == BTN_EXIT           ||
             *ui4_key_symbol == BTN_MIC            ||
             *ui4_key_symbol == BTN_VOL_DOWN       ||
             *ui4_key_symbol == BTN_VOL_UP         ||
             *ui4_key_symbol == BTN_PRG_INFO       ||
             *ui4_key_symbol == BTN_INPUT_SRC      ||
             *ui4_key_symbol == BTN_MUTE           ||
             *ui4_key_symbol == BTN_PARTNER_1      || //camera key
             *ui4_key_symbol == BTN_CUSTOM_4       || //Mute on key
             *ui4_key_symbol == BTN_CUSTOM_5       || //Mute off key
             *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN) ||
             *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP)   ||
             *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)))
        {
            if (i4_key_flag & 0x8000) //browser_ctrl return
            {
                b1_save_down_status = TRUE;

                if ( (*ui4_key_symbol == BTN_MUTE) ||
                     (*ui4_key_symbol == BTN_CUSTOM_4) || //Mute on key
                     (*ui4_key_symbol == BTN_CUSTOM_5) || //Mute off key
                     (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)) )
                {
                    ui4_key_dir = KEY_TO_UNUSE;
                    long_key_symbol = *ui4_key_symbol;
                }

                if ( (ui4_key_dir == KEY_TO_IOM) || (KEY_TO_GAM == ui4_key_dir) )
                {
                    b1_repeat_to_bro_ctrl_flag = FALSE;
                }
            }
            else
            {
                /*dtv_src UI don't show, Send to conjure*/
                if(ui4_key_dir == KEY_TO_GAM)
                {
                    if ( (*ui4_key_symbol == BTN_MUTE) ||
                         (*ui4_key_symbol == BTN_CUSTOM_4) || //Mute on key
                         (*ui4_key_symbol == BTN_CUSTOM_5) || //Mute off key
                         (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)) )
                    {
                        long_key_symbol = *ui4_key_symbol;
                    }

                    /*give to browser_ctrl handle this key*/
                    b1_repeat_to_bro_ctrl_flag = TRUE;
                    ui4_key_dir = KEY_TO_BR;
                }
                else
                {
                    b1_repeat_to_bro_ctrl_flag = FALSE;
                }
            }
        }
        else if (*ui4_key_symbol == BTN_P_EFFECT                                 ||
               #if (LONG_PRESS_SELECT_BTN_P_EFFECT == TRUE)
                 *ui4_key_symbol == BTN_SELECT                                   ||
               #endif
                 *ui4_key_symbol == BTN_CC                                       ||
                 *ui4_key_symbol == BTN_ASPECT                                   ||  //zoom
                 *ui4_key_symbol == BTN_MENU                                     ||
                 *ui4_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL)            ||
                 *ui4_key_symbol == (BTN_INPUT_AND_VOL_UP | KEY_SRC_FRONT_PANEL) ||
                 *ui4_key_symbol == (BTN_INPUT_AND_VOL_DOWN | KEY_SRC_FRONT_PANEL))
        {
            ui4_key_dir = KEY_TO_UNUSE;
            long_key_symbol = *ui4_key_symbol;

            /*need send to gam*/
            if (*ui4_key_symbol == BTN_CC &&  _get_cur_focus_status(*ui4_key_symbol,i4_key_flag) == KEY_TO_GAM)
            {
                ui4_key_dir = KEY_TO_GAM;
            }

            DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} ui4_key_dir:%d, long_key_symbol=0x%x\n",
                                __FUNCTION__, __LINE__, ui4_key_dir, long_key_symbol )); );


        }

        if (APP_CFG_CUST_ZOOM_MODE_ON == u1_zoom_status)
        {
            if (*ui4_key_symbol == BTN_DIGIT_1 || *ui4_key_symbol == BTN_DIGIT_2 || *ui4_key_symbol == BTN_DIGIT_3 ||
                *ui4_key_symbol == BTN_DIGIT_4 || *ui4_key_symbol == BTN_DIGIT_5 || *ui4_key_symbol == BTN_DIGIT_6 ||
                *ui4_key_symbol == BTN_DIGIT_7 || *ui4_key_symbol == BTN_DIGIT_8 || *ui4_key_symbol == BTN_DIGIT_9 ||
                *ui4_key_symbol == BTN_KB_MINUS_SIGN)
            {
                if (a_nav_zoom_cust_get_digital_pad_status() == FALSE)
                {
                    ui4_key_dir = KEY_TO_UNUSE;
                }
                else
                {
                    ui4_key_dir = _get_cur_focus_status(*ui4_key_symbol, i4_key_flag);
                }
            }
            else if( *ui4_key_symbol == BTN_CURSOR_LEFT  || *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                     *ui4_key_symbol == BTN_CURSOR_UP    || *ui4_key_symbol == BTN_CURSOR_DOWN)
            {
                if(a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
                {
                    ui4_key_dir = KEY_TO_UNUSE;
                }
            }
            else if (*ui4_key_symbol == BTN_DIGIT_0)
            {
                ui4_key_dir = KEY_TO_GAM;
            }
        }

        // combination of key
        if (ui4_vol_input_symbol != 0x00)
        {
            if ( ( (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP))
                && (ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)) )
               ||
                 ( (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC))
                 &&(ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP)) )
               )
            {
                ui4_key_dir = KEY_TO_UNUSE;
                ui4_last_tick = c_os_get_sys_tick();
                long_key_symbol = BTN_LONG_INPUT_VOL_UP;

                /*send analog null key*/
                c_iom_send_evt_single(0x00, TRUE);
            }
            else if ( ( *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN)
                      &&ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC) )
                    ||
                      ( *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)
                      &&ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN) )
                    )
            {
                ui4_key_dir = KEY_TO_UNUSE;
                ui4_last_tick = c_os_get_sys_tick();
                long_key_symbol =  BTN_LONG_INPUT_VOL_DOWN;

                /*send analog null key*/
                c_iom_send_evt_single(0x00, TRUE);
            }
        }

        ui4_vol_input_symbol = *ui4_key_symbol;
        last_key_info.ui4_save_key_type = ui4_key_dir;
    }


    /*key down*/
    if (b_recv_key_down == TRUE)
    {
        /*key up*/
        if (i4_key_type == KEY_STATE_UP)
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key up : ui4_key_dir: %X, key_symbol:%x, key_flag:%x \n",
                        __LINE__, ui4_key_dir, *ui4_key_symbol, i4_key_flag));

            b_recv_key_down = FALSE;
            ui4_vol_input_symbol = 0x00;

            //count < 5s
            _recv_key_event_count(ui4_last_tick, &ui4_key_count);

        #if 0
            /*Group1:only need to send to iom*/
            if ( *ui4_key_symbol == BTN_MIC ||
                 *ui4_key_symbol == BTN_VOL_DOWN ||
                 *ui4_key_symbol == BTN_VOL_UP ||
                 *ui4_key_symbol == BTN_PRG_INFO ||
                 *ui4_key_symbol == BTN_INPUT_SRC)
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" key up of group1,*ui4_key_symbol:%x.\n",*ui4_key_symbol));
                b1_repeat_to_bro_ctrl_flag = FALSE;
                ui4_key_dir = KEY_TO_BR;

                a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
                a_nav_retail_mode_get_status(&e_retail_status);
                a_nav_retail_mode_get_dlg_show(&e_popup_dlg);

                if (TRUE == a_wzd_is_oobe_mode())
                {
                    /*don`t need to handle in oobe*/
                }
                else if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode && e_retail_status == NAV_RETAIL_MODE_RUNNING && e_popup_dlg == NAV_RETAIL_MODE_NO_POPUP_DLG)
                {
                    /*don`t need to handle when demo dialog showing*/
                }
                else
                {
                    b1_need_analog_key = TRUE;
                    b1_is_need_key_event = FALSE;
                    last_key_info.ui4_key_symbol = BTN_EXIT;
                    /*send analog down key*/
                    c_iom_send_evt_single(BTN_EXIT, TRUE);
                }

            }
            /*Group2:first, send to iom,and wait for second*/
            else
        #endif
                if ( ( (*ui4_key_symbol == BTN_CURSOR_LEFT     ||
                        *ui4_key_symbol == BTN_CURSOR_RIGHT    ||
                        *ui4_key_symbol == BTN_CURSOR_UP       ||
                        *ui4_key_symbol == BTN_CURSOR_DOWN)
                     && a_nav_zoom_cust_get_nav_zoom_status() != TRUE ) ||
                   #if (LONG_PRESS_SELECT_BTN_P_EFFECT == FALSE)
                       *ui4_key_symbol == BTN_SELECT                  ||
                   #endif
                       *ui4_key_symbol == BTN_RETURN                  ||
                       *ui4_key_symbol == BTN_EXIT                    ||
                       *ui4_key_symbol == BTN_MIC                     ||
                       *ui4_key_symbol == BTN_VOL_DOWN                ||
                       *ui4_key_symbol == BTN_VOL_UP                  ||
                       *ui4_key_symbol == BTN_PRG_INFO                ||
                       *ui4_key_symbol == BTN_INPUT_SRC               ||
                       *ui4_key_symbol == BTN_PARTNER_1               || //camera key
                       *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN) ||
                       *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP) )
             {
                if (i4_key_flag & 0x8000) //browser_ctrl return
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key1 up of group2, key_symbol:%x, key_flag:%d \n", \
                                    __LINE__, *ui4_key_symbol, i4_key_flag));

                    b1_need_analog_key = FALSE;
                    b1_is_need_key_event = FALSE;
                    b_recv_key_down = FALSE;
                    b1_save_down_status = FALSE;
                    ui4_key_dir = last_key_info.ui4_save_key_type;
                }
                else
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key2 up of group2, key_symbol:%x, key_flag:%x, last_save_key_type:%x \n",
                    __LINE__, *ui4_key_symbol, i4_key_flag, last_key_info.ui4_save_key_type));

                    /*dtv_src UI don`t show,Send to conjure*/
                    if (last_key_info.ui4_save_key_type == KEY_TO_BR)
                    {
                        /*give to browser_ctrl  handle this key*/
                        b1_repeat_to_bro_ctrl_flag = FALSE;
                        ui4_key_dir = KEY_TO_BR;

                        /*need to handle browser_ctrl  return key up*/
                        if (b1_save_down_status == TRUE)
                        {
                            b_recv_key_down = TRUE;
                        }

                        if ( *ui4_key_symbol == BTN_MIC ||
                             *ui4_key_symbol == BTN_VOL_DOWN ||
                             *ui4_key_symbol == BTN_VOL_UP ||
                             *ui4_key_symbol == BTN_PRG_INFO ||
                             *ui4_key_symbol == BTN_INPUT_SRC ||
                             *ui4_key_symbol == BTN_PARTNER_1 || //camera key
                             *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN) ||
                             *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP)   ||
                             *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC))
                        {
                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key up of group1, key_symbol:%x \n",
                                    __LINE__, *ui4_key_symbol));

                            b1_repeat_to_bro_ctrl_flag = FALSE;
                            ui4_key_dir = KEY_TO_BR;

                            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

                            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode &&
                                ( *ui4_key_symbol == BTN_INPUT_SRC))
                            {
                                b1_need_analog_key = TRUE;
                                b1_is_need_key_event = FALSE;
                                last_key_info.ui4_key_symbol = BTN_EXIT;

                                /*send analog down key*/
                                c_iom_send_evt_single(BTN_EXIT, TRUE);
                            }
                        }
                    }
                    else
                    {
                        b1_need_analog_key = FALSE;
                        b1_is_need_key_event = FALSE;
                        b_recv_key_down = FALSE;
                        ui4_key_dir = last_key_info.ui4_save_key_type;
                    }
                }
            }
            else if (long_key_symbol != 0x00)
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] short key up : key_count:%d, key_symbol:%x \n",
                    __LINE__, ui4_key_count, *ui4_key_symbol));

                if ( ( (long_key_symbol != BTN_MUTE) && (long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL))
                     && (ui4_key_count < 5000) )
                   ||(long_key_symbol == BTN_MUTE && ui4_key_count < 2000)
                   ||(long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) && ui4_key_count < 2000)
                   )
                {
                    //short press
                    b1_need_analog_key = TRUE;
                    b1_is_need_key_event = FALSE;
                    ui4_key_dir = KEY_TO_UNUSE;//_get_cur_focus_status(*ui4_key_symbol);

                    /*input and vol+/- no work*/
                    if (long_key_symbol != BTN_LONG_INPUT_VOL_DOWN &&
                        long_key_symbol != BTN_LONG_INPUT_VOL_UP &&
                        long_key_symbol != BTN_MUTE &&
                        long_key_symbol != IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC))
                    {
                        BOOL bSendKey = TRUE;

                    #ifdef  MT5583_MODEL
                        if (  a_am_is_power_on() && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                        {
                            nav_set_power_to_input_status(TRUE);
                            *ui4_key_symbol = BTN_INPUT_SRC;
                        }
                        else {
                            nav_set_power_to_input_status(FALSE);
                        }
                     #endif

                        if (is_one_button_model_platform() == TRUE)
                        {
                            if ( a_am_is_power_on() && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) )
                            {
                                nav_set_power_to_input_status(TRUE);
                                *ui4_key_symbol = BTN_INPUT_SRC;
                            }
                            else {
                                nav_set_power_to_input_status(FALSE);
                            }
                        }

                        if (is_one_button_model_platform() == FALSE) // 4 button back panel
                        {
                            if ( a_am_is_power_on() && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL)
                               &&(ui4_key_count > 1000)
                               )
                            {
                                bSendKey = FALSE;
                                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[[%d][4 key][POWER] 2000 > %d > 1000 => IGNORE \n", __LINE__, ui4_key_count));
                            }
                        }

                        /*send analog down key*/
                        if ( bSendKey ) {
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                        }
                    }

                    /*need send to gam*/
                    if (*ui4_key_symbol == BTN_CC &&  _get_cur_focus_status(*ui4_key_symbol,i4_key_flag) == KEY_TO_GAM)
                    {
                        ui4_key_dir = KEY_TO_GAM;
                    }
                    /*short mute only need to send to browser_ctrl*/
                    else if ( *ui4_key_symbol == BTN_MUTE ||
                              *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC))
                    {
                         DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] mute key, key_symbol:%x, key_flag:%x, save_down_status:%d \n",
                         __LINE__, *ui4_key_symbol, i4_key_flag, b1_save_down_status));

                        /*need to handle browser_ctrl  return key up*/
                        if (i4_key_flag & 0x8000) //browser_ctrl return
                        {

                            b_recv_key_down = FALSE;
                            b1_save_down_status = FALSE;
                            b1_need_analog_key = TRUE;
                            b1_is_need_key_event = FALSE;
                            last_key_info.ui4_key_symbol = BTN_EXIT;

                            /*send analog down key*/
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                        }
                        else
                        {
                            if (b1_save_down_status == TRUE)
                            {
                                b_recv_key_down = TRUE;
                            }

                            b1_need_analog_key = FALSE;
                            /*need second key up*/
                            b1_is_need_key_event = TRUE;
                            ui4_key_dir =  KEY_TO_BR;

                            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

                            if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode &&
                                (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)))
                            {
                                b1_need_analog_key = TRUE;
                                b1_is_need_key_event = FALSE;
                                last_key_info.ui4_key_symbol = BTN_EXIT;

                                /*send analog down key*/
                                c_iom_send_evt_single(BTN_EXIT, TRUE);
                            }
                        }
                    }

                    if (b1_save_down_status == FALSE)
                    {
                        ui4_last_tick = 0;
                        long_key_symbol = 0x00;
                    }
                }
                else
                {
                    b1_need_analog_key = TRUE;
                    b1_is_need_key_event = FALSE;
                    ui4_key_dir = KEY_TO_UNUSE;

                    if (is_one_button_model_platform() == TRUE)
                    {
                        if (long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                        {
                            if (ui4_key_count < KEY_TIME_12_SEC)
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_LONG_POWER;
                                DBG_LOG_PRINT ((" [%s][%d] BTN_LONG_POWER \r\n", __FUNCTION__, __LINE__));

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }
                    }
                    else // 4 key
                    {
                        if (long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL)) {
                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[[%d][4 key][POWER] %d => IGNORE \n", __LINE__, ui4_key_count));
                        }
                    }
                }
            }
            /*short symbol*/
            else
            {
                /*key up*/
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX" short key up : key_symbol:%x, zoom_status:%x, save_key_type:%d \n",
                    __LINE__, *ui4_key_symbol, u1_zoom_status, last_key_info.ui4_save_key_type));

                    b1_need_analog_key = FALSE;
                    b1_is_need_key_event = FALSE;
                    b_recv_key_down = FALSE;
                    ui4_key_dir = last_key_info.ui4_save_key_type;

                    if (APP_CFG_CUST_ZOOM_MODE_ON == u1_zoom_status)
                    {
                         /*check navigation mode*/
                        if(a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
                        {
                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[navigation pad +++] {%s %s() %d}. digital pad key !!! *ui4_key_symbol: 0x%x\n",__FILE__, __FUNCTION__, __LINE__,*ui4_key_symbol));

                            if( *ui4_key_symbol == BTN_CURSOR_LEFT  || *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                                *ui4_key_symbol == BTN_CURSOR_UP    || *ui4_key_symbol == BTN_CURSOR_DOWN)
                            {
                                *ui4_key_symbol = a_nav_zoom_cust_navigation_num_pad(*ui4_key_symbol);
                                /* change the digit kay to special keys defined for Number Pad Zoom Navigation */
                                //*ui4_key_symbol = BTN_GFX_ZOOM_SECTOR_1 + (*ui4_key_symbol - BTN_DIGIT_1);
                                /*send analog down key*/
                                b1_need_analog_key = TRUE;
                                ui4_key_dir = KEY_TO_UNUSE;

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }

                        if (a_nav_zoom_cust_get_digital_pad_status() == FALSE)
                        {
                            if (*ui4_key_symbol >= BTN_DIGIT_1 && *ui4_key_symbol <= BTN_DIGIT_9)
                            {
                                /* change the digit kay to special keys defined for Number Pad Zoom Navigation */
                                *ui4_key_symbol = BTN_GFX_ZOOM_SECTOR_1 + (*ui4_key_symbol - BTN_DIGIT_1);
                                /*send analog down key*/
                                b1_need_analog_key = TRUE;
                                ui4_key_dir = KEY_TO_UNUSE;

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }
                        else
                        {
                            if (*ui4_key_symbol >= BTN_DIGIT_0 && *ui4_key_symbol <= BTN_DIGIT_9)
                            {
                                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s][%d] a_nav_zoom_cust_enable_dash_timer \n",
                                __FUNCTION__, __LINE__));

                                a_nav_zoom_cust_enable_dash_timer();
                            }
                        }

                        BOOL b_digital_timer = a_nav_zoom_cust_get_digital_timer_status();
                        BOOL b_zoom_digit_selection_support = a_cfg_cust_zoom_digit_selection_support();

                        DBG_INFO((MSCVT_LOG_PREFIX"[navigation pad +++] [%s][%d] digital pad key !!! *ui4_key_symbol: 0x%x,digital pad status = %s\n",
                        __FUNCTION__, __LINE__,*ui4_key_symbol,a_nav_zoom_cust_get_digital_pad_status() == TRUE ? "digital pad":"zoom pad"));

                        DBG_INFO(("[ZOOM] Digit selection support : %d\n", b_zoom_digit_selection_support));

                        if (*ui4_key_symbol == BTN_KB_MINUS_SIGN
                            && b_zoom_digit_selection_support == TRUE)
                        {
                            if(b_digital_timer == FALSE)
                            {
                                /* change the Dash kay to special keys defined for Number Pad Zoom Navigation */
                                *ui4_key_symbol = BTN_GFX_ZOOM_NAVIGATION;
                                /*send analog down key*/
                                b1_need_analog_key = TRUE;
                                ui4_key_dir = KEY_TO_UNUSE;

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }
                        else if (*ui4_key_symbol == BTN_DIGIT_0)
                        {
                            /*send analog down key*/
                            b1_need_analog_key = TRUE;
                            ui4_key_dir = KEY_TO_GAM;

                            /*send analog down key*/
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                        }
                    }
                }
            }
        }
        /*repeat*/
        else if (i4_key_type == KEY_STATE_REPEAT)
        {

            if( *ui4_key_symbol )
            {
                DEBUG_KEY_FLOW(DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key repeat : ui4_key_dir: %X, key_symbol:%x, key_flag:%x \n",
                            __LINE__, ui4_key_dir, *ui4_key_symbol, i4_key_flag)));
            }
            /*Group1:only need to send to iom*/
            if ( (*ui4_key_symbol == BTN_MIC          ||
                 *ui4_key_symbol == BTN_VOL_DOWN      ||
                 *ui4_key_symbol == BTN_VOL_UP        ||
                 *ui4_key_symbol == BTN_PRG_INFO      ||
                 *ui4_key_symbol == BTN_CURSOR_LEFT   ||
                 *ui4_key_symbol == BTN_CURSOR_RIGHT  ||
                 *ui4_key_symbol == BTN_CURSOR_UP     ||
                 *ui4_key_symbol == BTN_CURSOR_DOWN   ||
             #if (LONG_PRESS_SELECT_BTN_P_EFFECT == FALSE)
                 *ui4_key_symbol == BTN_SELECT        ||
             #endif
                 *ui4_key_symbol == BTN_RETURN        ||
                 *ui4_key_symbol == BTN_EXIT          ||
                 *ui4_key_symbol == BTN_INPUT_SRC     ||
                 *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP)      ||
                 *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN)    ||
                 *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC) ) &&
                 (b1_repeat_to_bro_ctrl_flag == TRUE) )
            {
                 ui4_key_dir = KEY_TO_BR;
            }
            else if (long_key_symbol != 0x00)
            {
                _recv_key_event_count(ui4_last_tick, &ui4_key_count);
                /*count > 5s */

                //DBG_LOG_PRINT((" [%d] ui4_key_count: %d \n", __LINE__, ui4_key_count));

                if ( (ui4_key_count >= 5000 && long_key_symbol != BTN_MUTE && long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL))
                   ||(ui4_key_count >= 2000 && long_key_symbol == BTN_MUTE )
                   ||(ui4_key_count >= 2000 && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                   )
                {
                    if ( (long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL) && long_key_symbol != BTN_LONG_INPUT_VOL_DOWN)
                       ||(long_key_symbol == BTN_LONG_INPUT_VOL_DOWN & ui4_key_count > 10000)
                       ||(long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) && ui4_key_count > 12000) )
                    {
                        b1_need_analog_key = TRUE;
                        b1_is_need_key_event = FALSE;
                        ui4_key_dir = KEY_TO_UNUSE;
                        b_recv_key_down = FALSE;
                        ui4_last_tick = 0;

                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key repeat: key_count:%d, key_symbol:%X \n",
                            __LINE__, ui4_key_count, *ui4_key_symbol));
                    }

                    {
                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] key repeat: key_count:%d, key_symbol:%x \n",
                            __LINE__, ui4_key_count, *ui4_key_symbol));

                        /*change key value*/
                        if (long_key_symbol == BTN_MUTE)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_BLANK_SCREEN;
                        }
                        else if(long_key_symbol == BTN_CC)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_CC;
                        }
                        else if(long_key_symbol == BTN_P_EFFECT)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_P_EFFECT;

                            DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} *ui4_key_symbol = BTN_LONG_P_EFFECT;\n",
                                                __FUNCTION__, __LINE__ )); );

                        }
                      #if (LONG_PRESS_SELECT_BTN_P_EFFECT == TRUE)
                        else if(long_key_symbol == BTN_SELECT)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_PRESS_SELECT;
                        }
                      #endif
                        else if(long_key_symbol == BTN_ASPECT)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_GFX_ZOOM;
                        }
                        else if(long_key_symbol == BTN_MENU)
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_MENU;
                        }
                        else if(long_key_symbol == (BTN_INPUT_SRC | KEY_SRC_FRONT_PANEL))
                        {
                            /*change key symbol*/
                            *ui4_key_symbol = BTN_LONG_INPUT;
                        }
                        else if(long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                        {
                            if (is_one_button_model_platform() == TRUE)
                            {
                                /*change key symbol*/
                                if ( (ui4_key_count >= KEY_TIME_2_SEC) && (ui4_key_count < KEY_TIME_7_SEC)
                                   &&(ui4_long_power_type != PRESS_KEYPAD_POWER_2_SEC) )
                                {
                                    b1_need_analog_key = FALSE;
                                    ui4_long_power_type = PRESS_KEYPAD_POWER_2_SEC;
                                    DBG_LOG_PRINT ((" [%s][%d] PRESS_KEYPAD_POWER_2_SEC \r\n", __FUNCTION__, __LINE__));
                                    nav_request_context_switch(nav_long_press_power_nfy_timer,
                                                                (VOID*) 3000,
                                                                (VOID*) ui4_long_power_type,
                                                                NULL);

                                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] keypad power key repeat 2 sec \n", __LINE__));
                                }
                                else if ( (ui4_key_count >= KEY_TIME_7_SEC) && (ui4_key_count < KEY_TIME_12_SEC)
                                    &&(ui4_long_power_type != PRESS_KEYPAD_POWER_7_SEC) )
                                {
                                    b1_need_analog_key = FALSE;
                                    ui4_long_power_type = PRESS_KEYPAD_POWER_7_SEC;
                                    DBG_LOG_PRINT ((" [%s][%d] PRESS_KEYPAD_POWER_7_SEC \r\n", __FUNCTION__, __LINE__));
                                    nav_request_context_switch(nav_long_press_power_nfy_timer,
                                                                (VOID*) 3000,
                                                                (VOID*) ui4_long_power_type,
                                                                NULL);
                                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] keypad power key repeat 7 sec \n", __LINE__));
                                 }
                                 else if (ui4_key_count >= 12000)
                                 {
                                     /*change key symbol*/
                                     ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;
                                     *ui4_key_symbol = BTN_LONG_POWER_12S;
                                     DBG_LOG_PRINT ((" [%s][%d] BTN_LONG_POWER_12S \r\n", __FUNCTION__, __LINE__));
                                 }
                            }
                            else // 4 button
                            {
                                if (ui4_key_count >= 5000)
                                {
                                     b1_need_analog_key = TRUE;
                                     b1_is_need_key_event = FALSE;
                                     ui4_key_dir = KEY_TO_UNUSE;
                                     b_recv_key_down = FALSE;
                                     ui4_last_tick = 0;

                                     /*change key symbol*/
                                     ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;
                                     *ui4_key_symbol = BTN_LONG_POWER;
                                     DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[[%d][4 key][POWER] %d \n", __LINE__, ui4_key_count));
                                }
                            }
                        }
                        else if (long_key_symbol == BTN_LONG_INPUT_VOL_UP)
                        {
                            *ui4_key_symbol = BTN_LONG_INPUT_VOL_UP;
                        }
                        else if (long_key_symbol == BTN_LONG_INPUT_VOL_DOWN)
                        {
                             /*change key symbol*/
                             if ( ((ui4_key_count >= KEY_TIME_5_SEC) && (ui4_key_count < KEY_TIME_10_SEC))
                                &&(ui4_long_power_type != PRESS_KEYPAD_VOL_DOWN_AND_INPUT_5_SEC) )
                             {
                                 b1_need_analog_key = FALSE;
                                 ui4_long_power_type = PRESS_KEYPAD_VOL_DOWN_AND_INPUT_5_SEC;

                                 //"Reset to Defaults, from the back panel, press the Input for 10 seconds." is no need.
                                 //nav_request_context_switch(vol_down_input_notify_factory_reset,NULL,NULL,NULL);

                                 *ui4_key_symbol = BTN_LONG_INPUT_VOL_DOWN;

                                 DBG_LOG_PRINT((MSCVT_LOG_PREFIX" input & vol down key repeat 5 sec \n"));
                             }
                             else if (ui4_key_count >= KEY_TIME_10_SEC)
                             {
                                 ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;
                                 *ui4_key_symbol = BTN_LONG_INPUT_VOL_DOWN_10S;

                                 DBG_LOG_PRINT((MSCVT_LOG_PREFIX" input & vol down key repeat 10 sec \n"));
                             }
                        }

                        /*send analog down key*/
                        if (b1_need_analog_key == TRUE)
                        {
                            /*send analog down key*/
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);

                            long_key_symbol = 0x00;
                            ui4_vol_input_symbol = 0x00;
                        }
                    }
                }
                else
                {
                    ui4_key_dir = KEY_TO_IGNORE;
                }
            }
            else
            {
            #if 0
                if (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN) ||
                    *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP))
                {
                    ui4_key_dir = KEY_TO_IOM;
                }
                else
            #endif
                if (*ui4_key_symbol == BTN_CURSOR_LEFT  ||
                    *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                    *ui4_key_symbol == BTN_CURSOR_UP    ||
                    *ui4_key_symbol == BTN_CURSOR_DOWN )
                {
                    ui4_key_dir = _get_cur_focus_status(*ui4_key_symbol,i4_key_flag);
                }
                else
                {
                    ui4_key_dir = KEY_TO_IGNORE;
                }
            }
        }

        last_key_info.ui4_key_symbol = *ui4_key_symbol;
    }

    if (ui4_key_dir == KEY_TO_IOM || ui4_key_dir == KEY_TO_GAM || ui4_key_dir == KEY_TO_BR)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[_iom_system_ui_key_handle_fct] [%s] key_dir:%d, key_symbol:0x%X \n",
                        i4_key_type == KEY_STATE_DOWN ? "key down" :
                        i4_key_type == KEY_STATE_UP  ? "key up" : "key repeat",
                        ui4_key_dir, *ui4_key_symbol));
    }
    else if (ui4_key_dir == KEY_TO_IGNORE)
    {
        //DBG_LOG_PRINT ((MSCVT_LOG_PREFIX"[%s] IGNORE key_symbol:0x%X \n", __FUNCTION__, *ui4_key_symbol));
    }

    if (ui4_key_dir == KEY_TO_BR)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[_iom_system_ui_key_handle_fct] Reset power off timer for AirPlay\n"));
        nav_pwr_system_ui_key_nfy();
    }

    return ui4_key_dir;
}

static INT32  _iom_key_handle_fct(UINT32 *ui4_key_symbol,INT32 i4_key_type,INT32 i4_key_flag)
{
        /*keep*/
        static BOOL           b_recv_key_down         = false;
        static BOOL           b1_is_need_key_event    = TRUE; //if need to handle key
        static BOOL           b1_need_analog_key      = FALSE;
        UINT32                ui4_key_count           = 0;
        UINT32                ui4_key_dir             = KEY_TO_UNUSE;
        UINT8                 u1_zoom_status          = APP_CFG_CUST_ZOOM_MODE_OFF ;
        PCL_WAKE_UP_REASON_T  e_wake_up_reason        = PCL_WAKE_UP_REASON_UNKNOWN;
        UINT32                ui4_wake_up_sub_reason  = 0;
        CHAR                  s_app_name [APP_NAME_MAX_LEN+1] = {0};
        static UINT32         ui4_long_power_type        = PRESS_KEYPAD_POWER_INVALID;

        if( *ui4_key_symbol )
        {
            DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} *ui4_key_symbol:0x%x, i4_key_type:%d, i4_key_flag:%d\n",
                            __FUNCTION__, __LINE__, *ui4_key_symbol, i4_key_type, i4_key_flag )); );

          #if 0 // test for BTN_ASPECT
            if( BTN_CC == *ui4_key_symbol )
            {
                *ui4_key_symbol = BTN_ASPECT;
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} Debug change key to BTN_ASPECT: *ui4_key_symbol:0x%x, i4_key_type:%d, i4_key_flag:%d\n",
                            __FUNCTION__, __LINE__, *ui4_key_symbol, i4_key_type, i4_key_flag ));
            }
          #endif
        }

        if (!_iom_is_valid_key(ui4_key_symbol,i4_key_type,i4_key_flag))
        {
            return KEY_TO_UNUSE;
        }

        a_cfg_cust_get_zoom_status(&u1_zoom_status);

        if (b1_is_need_key_event == FALSE && i4_key_type != KEY_STATE_DOWN)
        {

            if (b1_need_analog_key == TRUE && i4_key_type == KEY_STATE_REPEAT)
            {
                b1_need_analog_key = FALSE;
                /*send analog up key*/
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] last_key_symbol:%x, last_save_key_type:%d.\n",
                        __LINE__, last_key_info.ui4_key_symbol,last_key_info.ui4_save_key_type));

                c_iom_send_evt_single(last_key_info.ui4_key_symbol, FALSE);
            }
            return KEY_TO_UNUSE;
        }

        if(*ui4_key_symbol == BTN_CUSTOM_102 && i4_key_type == KEY_STATE_DOWN)
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%d] media key launch mmp\n", __LINE__));
#ifdef  APP_C4TV_SUPPORT
            a_rest_app_launch_native_app_notify("REST_APP_NAME_NATIVE_MMP");
#endif
            rest_event_notify_current_input("usb");
            a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
            return KEY_TO_UNUSE;
        }

        /*if receive down event*/
        if (i4_key_type == KEY_STATE_DOWN)
        {
            DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} i4_key_type:%d=KEY_STATE_DOWN\n",
                                __FUNCTION__, __LINE__, i4_key_type )); );

            if (menu_custom_blank_oled_scrn_timer_is_start())
            {
                a_am_get_active_app (s_app_name);
                if(c_strcmp ((CHAR*)s_app_name, MSCVT_NAME) == 0)
                {
                    MSCVT_CUST_LOG_ON_FAIL(menu_blank_oled_scrn_timer_refresh());
                }
            }
            b_recv_key_down = TRUE;
            b1_is_need_key_event = TRUE;
            ui4_key_dir = _get_cur_focus_status(*ui4_key_symbol,0x0);
            ui4_last_tick = c_os_get_sys_tick();
            ui4_g_last_key_down = *ui4_key_symbol;

            if (APP_CFG_CUST_ZOOM_MODE_OFF == u1_zoom_status)
            {
                a_nav_zoom_cust_set_digital_pad_status(FALSE);
            }

            if (*ui4_key_symbol == BTN_MUTE ||
                *ui4_key_symbol == BTN_P_EFFECT ||
                *ui4_key_symbol == BTN_CC ||
                *ui4_key_symbol == BTN_ASPECT ||  //zoom
                *ui4_key_symbol == BTN_MENU  ||
                *ui4_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) ||
                *ui4_key_symbol == (BTN_INPUT_SRC | KEY_SRC_FRONT_PANEL) ||
                *ui4_key_symbol == (BTN_INPUT_AND_VOL_UP | KEY_SRC_FRONT_PANEL) ||
                *ui4_key_symbol == (BTN_INPUT_AND_VOL_DOWN | KEY_SRC_FRONT_PANEL))
            {
                ui4_key_dir = KEY_TO_UNUSE;
                long_key_symbol = *ui4_key_symbol;

                /*need send to gam*/
                if (*ui4_key_symbol == BTN_CC &&  _get_cur_focus_status(*ui4_key_symbol,0x0) == KEY_TO_GAM)
                {
                    ui4_key_dir = KEY_TO_GAM;
                }

                DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} ui4_key_dir:%d, long_key_symbol=0x%x\n",
                                    __FUNCTION__, __LINE__, ui4_key_dir, long_key_symbol )); );

            }
            else
            {
                long_key_symbol = 0x00;
            }

            if (APP_CFG_CUST_ZOOM_MODE_ON == u1_zoom_status)
            {
                if (*ui4_key_symbol == BTN_DIGIT_1 || *ui4_key_symbol == BTN_DIGIT_2 || *ui4_key_symbol == BTN_DIGIT_3 ||
                    *ui4_key_symbol == BTN_DIGIT_4 || *ui4_key_symbol == BTN_DIGIT_5 || *ui4_key_symbol == BTN_DIGIT_6 ||
                    *ui4_key_symbol == BTN_DIGIT_7 || *ui4_key_symbol == BTN_DIGIT_8 || *ui4_key_symbol == BTN_DIGIT_9 ||
                    *ui4_key_symbol == BTN_KB_MINUS_SIGN)
                {
                    if ( a_nav_zoom_cust_get_digital_pad_status() == FALSE )
                    {
                        ui4_key_dir = KEY_TO_UNUSE;
                    }
                    else
                    {
                        ui4_key_dir = _get_cur_focus_status(*ui4_key_symbol,0x0);
                    }
                }
                else if( *ui4_key_symbol == BTN_CURSOR_LEFT  || *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                         *ui4_key_symbol == BTN_CURSOR_UP    || *ui4_key_symbol == BTN_CURSOR_DOWN)
                {
                     if(a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
                     {
                         ui4_key_dir = KEY_TO_UNUSE;
                     }

                }
                else if (*ui4_key_symbol == BTN_DIGIT_0)
                {
                    ui4_key_dir = KEY_TO_GAM;
                }
            }

            // combination  of key
            if (ui4_vol_input_symbol != 0x00)
            {
                if ((*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP) &&
                     ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)) ||
                     (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC) &&
                     ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP)))
                {
                    ui4_key_dir = KEY_TO_UNUSE;
                    ui4_last_tick = c_os_get_sys_tick();
                    long_key_symbol = BTN_LONG_INPUT_VOL_UP;
                    /*send analog null key*/
                    c_iom_send_evt_single(0x00, TRUE);
                }
                else if ((*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN) &&
                         ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC)) ||
                         (*ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC) &&
                         ui4_vol_input_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN)))
                {
                    ui4_key_dir = KEY_TO_UNUSE;
                    ui4_last_tick = c_os_get_sys_tick();
                    long_key_symbol =  BTN_LONG_INPUT_VOL_DOWN;
                    /*send analog null key*/
                    c_iom_send_evt_single(0x00, TRUE);
                }
            }

            ui4_vol_input_symbol = *ui4_key_symbol;
            last_key_info.ui4_save_key_type = ui4_key_dir;
        }

        /*key down*/
        if (b_recv_key_down == TRUE)
        {
            /*key up*/
            if (i4_key_type == KEY_STATE_UP)
            {
                b_recv_key_down = FALSE;
                ui4_vol_input_symbol = 0x00;
                ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;

                //count < 5s
                _recv_key_event_count(ui4_last_tick,&ui4_key_count);

                if (long_key_symbol != 0x00)
                {
                    DBG_INFO((MSCVT_LOG_PREFIX" long key up ui4_key_count:%x,*ui4_key_symbol:%d(0x%X)\n",ui4_key_count,*ui4_key_symbol, *ui4_key_symbol));

                    if ((long_key_symbol != BTN_MUTE && long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL) && ui4_key_count < 5000)
                        || (long_key_symbol == BTN_MUTE && ui4_key_count < 2000)
                        || (long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) && ui4_key_count < 2000))
                    {

                        DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} long_key_symbol=0x%x\n",
                                        __FUNCTION__, __LINE__, long_key_symbol )); );
                        //short press
                        ui4_last_tick = 0;
                        b1_need_analog_key = TRUE;
                        b1_is_need_key_event = FALSE;
                        ui4_key_dir = KEY_TO_UNUSE;//_get_cur_focus_status(*ui4_key_symbol);
                        /*input and vol+/- no work*/
                        if (long_key_symbol != BTN_LONG_INPUT_VOL_DOWN && long_key_symbol != BTN_LONG_INPUT_VOL_UP )
                        {
                        #ifdef  MT5583_MODEL
                            if (  a_am_is_power_on() && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                            {
                                nav_set_power_to_input_status(TRUE);
                                *ui4_key_symbol = BTN_INPUT_SRC;
                                //*ui4_key_symbol = BTN_PANEL_POWER_INPUT;
                            }
                        #endif
                            if (is_one_button_model_platform() == TRUE)
                            {
                                if (  a_am_is_power_on() && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                                {
                                    nav_set_power_to_input_status(TRUE);
                                    *ui4_key_symbol = BTN_INPUT_SRC;
                                    //*ui4_key_symbol = BTN_PANEL_POWER_INPUT;
                                }
                            }

                            /*send analog down key*/
                            DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} call c_iom_send_evt_single(*ui4_key_symbol:0x%x, TRUE)\n",
                                                __FUNCTION__, __LINE__, *ui4_key_symbol )); );
                            c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                        }

                        /*need send to gam*/
                        if (*ui4_key_symbol == BTN_CC &&  _get_cur_focus_status(*ui4_key_symbol,0x0) == KEY_TO_GAM)
                        {
                            ui4_key_dir = KEY_TO_GAM;
                        }
                    }
                    else
                    {
                        DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} long_key_symbol=0x%x\n",
                                            __FUNCTION__, __LINE__, long_key_symbol )); );

                        b1_need_analog_key = TRUE;
                        b1_is_need_key_event = FALSE;
                        ui4_key_dir = KEY_TO_UNUSE;

                        if (long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                        {
                            if (ui4_key_count < KEY_TIME_12_SEC)
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_LONG_POWER;

                                DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} long_key_symbol=0x%x\n",
                                                    __FUNCTION__, __LINE__, long_key_symbol )); );

                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }
                    }
                }

                /*short symbol*/
                else
                {
                    /*key up*/
                    {
                        DBG_INFO((MSCVT_LOG_PREFIX" short key up ,*ui4_key_symbol:%x,u1_zoom_status:%d,last_key_info.ui4_save_key_type:%d.\n",*ui4_key_symbol,u1_zoom_status,last_key_info.ui4_save_key_type));

                        b1_need_analog_key = FALSE;
                        b1_is_need_key_event = FALSE;
                        b_recv_key_down = FALSE;
                        ui4_key_dir = last_key_info.ui4_save_key_type;

                        if (APP_CFG_CUST_ZOOM_MODE_ON == u1_zoom_status)
                        {

                            /*check navigation mode*/
                            if(a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
                            {
                                DBG_INFO((MSCVT_LOG_PREFIX"[navigation pad +++] {%s %s() %d}. digital pad key !!! *ui4_key_symbol: 0x%x\n",__FILE__, __FUNCTION__, __LINE__,*ui4_key_symbol));
                                if( *ui4_key_symbol == BTN_CURSOR_LEFT  || *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                                    *ui4_key_symbol == BTN_CURSOR_UP    || *ui4_key_symbol == BTN_CURSOR_DOWN)
                                    {
                                      *ui4_key_symbol = a_nav_zoom_cust_navigation_num_pad(*ui4_key_symbol);
                                      /* change the digit kay to special keys defined for Number Pad Zoom Navigation */
                                      //*ui4_key_symbol = BTN_GFX_ZOOM_SECTOR_1 + (*ui4_key_symbol - BTN_DIGIT_1);
                                      /*send analog down key*/
                                      b1_need_analog_key = TRUE;
                                      ui4_key_dir = KEY_TO_UNUSE;
                                      c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                                    }
                            }

                            if (a_nav_zoom_cust_get_digital_pad_status() == FALSE)
                            {
                                if (*ui4_key_symbol >= BTN_DIGIT_1 && *ui4_key_symbol <= BTN_DIGIT_9)
                                {
                                    /* change the digit kay to special keys defined for Number Pad Zoom Navigation */
                                    *ui4_key_symbol = BTN_GFX_ZOOM_SECTOR_1 + (*ui4_key_symbol - BTN_DIGIT_1);
                                    /*send analog down key*/
                                    b1_need_analog_key = TRUE;
                                    ui4_key_dir = KEY_TO_UNUSE;
                                    c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                                }
                             }
                            else
                            {
                                if (*ui4_key_symbol >= BTN_DIGIT_0 && *ui4_key_symbol <= BTN_DIGIT_9)
                                {
                                    DBG_INFO((MSCVT_LOG_PREFIX"[dash +++] {%s %s() %d}. a_nav_zoom_cust_enable_dash_timer.\n",__FILE__, __FUNCTION__, __LINE__));
                                    a_nav_zoom_cust_enable_dash_timer();
                                }
                            }

                            BOOL b_digital_timer = a_nav_zoom_cust_get_digital_timer_status();
                            BOOL b_zoom_digit_selection_support = a_cfg_cust_zoom_digit_selection_support();

                            DBG_INFO((MSCVT_LOG_PREFIX"[navigation pad +++] {%s() %d}. digital pad key !!! *ui4_key_symbol: 0x%x,digital pad status = %s\n",__FUNCTION__, __LINE__,*ui4_key_symbol,a_nav_zoom_cust_get_digital_pad_status() == TRUE ? "digital pad":"zoom pad"));
                            DBG_INFO(("[ZOOM] Digit selection support : %d\n", b_zoom_digit_selection_support));

                            if (*ui4_key_symbol == BTN_KB_MINUS_SIGN
                                && b_zoom_digit_selection_support == TRUE)
                            {
                                if(b_digital_timer == FALSE)
                                {
                                    /* change the Dash kay to special keys defined for Number Pad Zoom Navigation */
                                    *ui4_key_symbol = BTN_GFX_ZOOM_NAVIGATION;
                                    /*send analog down key*/
                                    b1_need_analog_key = TRUE;
                                    ui4_key_dir = KEY_TO_UNUSE;
                                    c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                                }
                            }
                            else if (*ui4_key_symbol == BTN_DIGIT_0)
                            {
                                /*send analog down key*/
                                b1_need_analog_key = TRUE;
                                ui4_key_dir = KEY_TO_GAM;
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);
                            }
                        }
                    }
                }
            }
            /*repeat*/
            else if (i4_key_type == KEY_STATE_REPEAT)
            {
                if (long_key_symbol != 0x00)
                {
                    _recv_key_event_count(ui4_last_tick,&ui4_key_count);
                    /*count > 5s */

                    if ( (ui4_key_count >= 5000 && long_key_symbol != BTN_MUTE && long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL)) ||
                         (ui4_key_count >= 2000 && long_key_symbol == BTN_MUTE ) ||
                         (ui4_key_count >= 2000 && long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL)))
                    {

                        if ((long_key_symbol != (BTN_POWER | KEY_SRC_FRONT_PANEL) && long_key_symbol != BTN_LONG_INPUT_VOL_DOWN) ||
                            (long_key_symbol == BTN_LONG_INPUT_VOL_DOWN & ui4_key_count >10000) ||
                            (long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL) && ui4_key_count >12000))

                        {
                            b1_need_analog_key = TRUE;
                            b1_is_need_key_event = FALSE;
                            ui4_key_dir = KEY_TO_UNUSE;
                            b_recv_key_down = FALSE;
                            ui4_last_tick == 0;

                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" key repeat ui4_key_count:%d,*ui4_key_symbol:%x.\n",ui4_key_count,*ui4_key_symbol));
                        }

                        {
                            /*change key value*/
                            if (long_key_symbol == BTN_MUTE)
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_BLANK_SCREEN;
                            }
                            else if(long_key_symbol == BTN_CC)
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_LONG_CC;
                            }
                            else if(long_key_symbol == BTN_P_EFFECT)
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_LONG_P_EFFECT;

                                DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} *ui4_key_symbol = BTN_LONG_P_EFFECT;\n",
                                                    __FUNCTION__, __LINE__ )); );

                            }
                            else if(long_key_symbol == BTN_ASPECT)
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_GFX_ZOOM;
                            }
                            else if(long_key_symbol == BTN_MENU)
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_LONG_MENU;
                            }
                            else if(long_key_symbol == (BTN_INPUT_SRC | KEY_SRC_FRONT_PANEL))
                            {
                                /*change key symbol*/
                                *ui4_key_symbol = BTN_LONG_INPUT;
                            }
                            else if(long_key_symbol == (BTN_POWER | KEY_SRC_FRONT_PANEL))
                            {
                                  /*change key symbol*/
                                 if (ui4_key_count >= 2000 && ui4_key_count < 7000 && ui4_long_power_type != PRESS_KEYPAD_POWER_2_SEC)
                                 {
                                     b1_need_analog_key = FALSE;
                                     ui4_long_power_type = PRESS_KEYPAD_POWER_2_SEC;
                                    nav_request_context_switch(nav_long_press_power_nfy_timer,
                                                                (VOID*) 3000,
                                                                (VOID*) ui4_long_power_type,
                                                                NULL);
                                     DBG_LOG_PRINT((MSCVT_LOG_PREFIX" keypad power key repeat 2 sec \n"));
                                 }
                                 else if (ui4_key_count >= 7000 && ui4_key_count < 12000 && ui4_long_power_type != PRESS_KEYPAD_POWER_7_SEC)
                                 {
                                     b1_need_analog_key = FALSE;
                                     ui4_long_power_type = PRESS_KEYPAD_POWER_7_SEC;
                                     nav_request_context_switch(nav_long_press_power_nfy_timer,
                                                                (VOID*) 3000,
                                                                (VOID*) ui4_long_power_type,
                                                                NULL);
                                     DBG_LOG_PRINT((MSCVT_LOG_PREFIX" keypad power key repeat 7 sec \n"));
                                 }
                                 else if (ui4_key_count >= 12000)
                                 {
                                     /*change key symbol*/
                                     ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;
                                     *ui4_key_symbol = BTN_LONG_POWER_12S;
                                 }
                            }
                            else if (long_key_symbol == BTN_LONG_INPUT_VOL_UP)
                            {
                                *ui4_key_symbol = BTN_LONG_INPUT_VOL_UP;
                            }
                            else if (long_key_symbol == BTN_LONG_INPUT_VOL_DOWN)
                            {
                                /*change key symbol*/
                                if (ui4_key_count >= 5000 && ui4_key_count < 10000 &&  ui4_long_power_type != PRESS_KEYPAD_VOL_DOWN_AND_INPUT_5_SEC)
                                {
                                    b1_need_analog_key = FALSE;
                                    ui4_long_power_type = PRESS_KEYPAD_VOL_DOWN_AND_INPUT_5_SEC;

                                     //"Reset so Defaults, from the back panel, press the Input for 10 seconds." is no need.
                                     //nav_request_context_switch(vol_down_input_notify_factory_reset,NULL,NULL,NULL);

                                    *ui4_key_symbol = BTN_LONG_INPUT_VOL_DOWN;

                                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX" input & vol down key repeat 5 sec [%s] \n", __FUNCTION__));
                                }
                                else if (ui4_key_count >= 10000 )
                                {
                                    ui4_long_power_type = PRESS_KEYPAD_POWER_INVALID;
                                    *ui4_key_symbol = BTN_LONG_INPUT_VOL_DOWN_10S;

                                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX" input & vol down key repeat 10 sec [%s] \n", __FUNCTION__));
                                }

                            }

                             /*send analog down key*/
                            if (b1_need_analog_key == TRUE)
                            {
                                /*send analog down key*/
                                c_iom_send_evt_single(*ui4_key_symbol, TRUE);

                                long_key_symbol = 0x00;
                                ui4_vol_input_symbol = 0x00;
                            }
                        }
                    }
                    else
                    {
                        ui4_key_dir = KEY_TO_IGNORE;
                    }
                }
                else
                {
                    if (*ui4_key_symbol == BTN_VOL_UP ||
                        *ui4_key_symbol == BTN_VOL_DOWN ||
                        *ui4_key_symbol == BTN_MUTE ||
                        *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN) ||
                        *ui4_key_symbol == IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP))
                    {
                        ui4_key_dir = KEY_TO_IOM;
                    }
                    else if (*ui4_key_symbol == BTN_CURSOR_LEFT ||
                            *ui4_key_symbol == BTN_CURSOR_RIGHT ||
                            *ui4_key_symbol == BTN_CURSOR_UP ||
                            *ui4_key_symbol == BTN_CURSOR_DOWN )
                    {
                        if (a_nav_zoom_cust_get_digital_pad_status() == FALSE && a_nav_zoom_cust_get_nav_zoom_status() == TRUE)
                        {
                             ui4_key_dir = KEY_TO_UNUSE;
                        }
                        else
                        {
                            ui4_key_dir = _get_cur_focus_status(*ui4_key_symbol,0x0);
                        }
                    }
                    else
                    {
                        ui4_key_dir = KEY_TO_IGNORE;
                    }
                }

            }
            last_key_info.ui4_key_symbol = *ui4_key_symbol;

        }

        if (ui4_key_dir == KEY_TO_IOM || ui4_key_dir == KEY_TO_GAM)
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s:%d] [%s] ui4_key_dir:%d,*ui4_key_symbol:0x%x.\n",
                            __FUNCTION__,__LINE__,
                            i4_key_type == KEY_STATE_DOWN ? "key down" :
                            i4_key_type == KEY_STATE_UP  ? "key up" : "key repeat",
                            ui4_key_dir,*ui4_key_symbol));
        }

        return ui4_key_dir;
}

INT32 msg_convert_custom_init(VOID)
{
    INT32 i4_ret = 0;

    _msg_convert_custom_pre_init();

    i4_ret = c_aee_thread_create(&__i_input_thread, MSCVT_CUS_INPUT_THREAD_NAME, MSCVT_CUS_THREAD_STACK_SIZE, MSCVT_CUS_THREAD_PRIORITY, _mc_app_process_input_thread, 0, NULL);

    _notify_BGM_mode();

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_NAV,
                              NULL,
                              _msgcvt_inp_src_chg_nfy_fct,
                              &ui2_acfg_inp_src_chg_id);

    if( access("/basic/features/VIZIO_FEATURE_LOKI", F_OK) == 0 && access("/3rd_rw/BLOCK_3RD", F_OK) != 0)
    {
        MSCVT_CUST_LOG_ON_FAIL(c_iom_long_press_nfy_register(_iom_loki_key_handle_fct));
    }
    else if( access("/basic/features/VIZIO_FEATURE_SYSTEM_UI", F_OK) == 0 && access("/3rd_rw/BLOCK_3RD", F_OK) != 0)
    {
        MSCVT_CUST_LOG_ON_FAIL(c_iom_long_press_nfy_register(_iom_system_ui_key_handle_fct));
    }
    else
    {
        MSCVT_CUST_LOG_ON_FAIL(c_iom_long_press_nfy_register(_iom_key_handle_fct));
    }
#ifdef MT5695_MODEL
    a_cfg_custom_get_oled_error_detect_count(&ui1_oled_error_count);
#endif
    return i4_ret;
}

static INT32 _mc_set_cc_status(BOOL b_show)
{
    HANDLE_T h_focus_svctx = NULL_HANDLE;
    INT32 i4_ret = -1;

    DBG_INFO((MSCVT_LOG_PREFIX" %s : b_show = %x-- \n", __FUNCTION__, b_show));
    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_focus_svctx);
    if(i4_ret != 0)
    {
        DBG_ERROR((MSCVT_LOG_PREFIX" -- Error - Function : %s, Line : %d, i4_ret = %d-- \n",__FUNCTION__,__LINE__,i4_ret));
        return -1;
    }

    nav_ci_set_exec_cond(TRUE == b_show ? NAV_CI_EC_ON : NAV_CI_EC_OFF);
    i4_ret = c_svctx_set_stream_attr(h_focus_svctx,
                                     ST_CLOSED_CAPTION,
                                     SM_CCH_SET_TYPE_CC_GLOBAL_VISIBLE,
                                     (VOID*)(UINT32)b_show,
                                     sizeof(BOOL));
    if(i4_ret != 0)
    {
        DBG_ERROR((MSCVT_LOG_PREFIX" -- Error - Function : %s, Line : %d, i4_ret = %d-- \n",__FUNCTION__,__LINE__,i4_ret));
        return -1;
    }

    return 0;
}

static VOID _mc_signal_resumed(VOID)
{
    b_ap_resumed = TRUE;
}

static VOID _mc_wait_for_resumed(VOID)
{
    b_ap_resumed = FALSE;
    UINT32 u4_count = 0;
    /*for cinemanow stop timeout 10s, default 5s by AM, not effect other process*/
    while(!b_ap_resumed && u4_count < 100)
    {
           c_thread_delay(100);
           u4_count ++;
    }

}

extern NAV_MODEL_T  t_g_navigator;

static INT32 _mc_custom_dtv_stop_svc(VOID)
{
    NAV_MODEL_T* pt_this;
    NAV_TV_WIN_T* pt_tv_win = NULL;
    TV_WIN_ID_T  e_tv_win_id;
    ISL_REC_T   t_isl_rec           = {0};
    CHAR        s_disp_name[16+1]   = {0};
    UINT8       ui1_crnt_input_src  = 0;
    CHAR        sz_active_app[32]   = {0};

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
    a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);
    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s %d] e_src_type = %d,e_video_type= 0x%x\n",__FUNCTION__,__LINE__,t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type));

    if(t_isl_rec.e_src_type != INP_SRC_TYPE_AV &&
       t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        return 0;
    }

    if (nav_get_focus_id(&e_tv_win_id) != 0)
    {
        DBG_ERROR((MSCVT_LOG_PREFIX" <><> nav_get_focus_id fail. \n"));
    }

    pt_this = &t_g_navigator;
    pt_tv_win = &pt_this->t_tv_wins[e_tv_win_id];

    if(access("/tmp/airplay_tv_running", F_OK) != 0 || b_browser_starting == TRUE)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" <><> _mc_custom_dtv_stop_svc b_browser_starting =%d\n",b_browser_starting));
        if (a_tv_stop(pt_tv_win->h_svctx) != 0)
        {
            DBG_ERROR((MSCVT_LOG_PREFIX" dtv_stop_svc fail. \n"));
        }
    }

    return 0;
}

static INT32 _mc_custom_dtv_start_svc()
{
    ISL_REC_T   t_isl_rec;
    INT32       i4_ret = 0;
    HANDLE_T    h_main_svctx;
    UINT8 ui1_scan_progress = -1;

    /*reset 3D mode*/
    a_cfg_custom_3D_setting_reset_3D_mode();
    /*restart tv*/
    i4_ret = a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec);
    if(TVR_OK != i4_ret)
    {
        DBG_ERROR((MSCVT_LOG_PREFIX"a_tv_get_isl_rec_by_win_id() failed. i4_ret = %d.\r\n", i4_ret));
        return i4_ret;
    }
    /* get main service context */
    i4_ret = nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_main_svctx);
    if(i4_ret != 0)
    {
        DBG_ERROR((MSCVT_LOG_PREFIX"\n -- Error - Function : %s, Line : %d, i4_ret = %d-- \n",__FUNCTION__,__LINE__,i4_ret));
        return i4_ret;
    }

    ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
        DBG_LOG_PRINT(("[MsgConvert][INPUT_SRC]{%s,%d} call a_tv_change_input_src_by_rec()\n", __FUNCTION__,__LINE__ ));
    );

    i4_ret = a_tv_change_input_src_by_rec(h_main_svctx, ST_MASK_AUDIO|ST_MASK_VIDEO, &t_isl_rec, NULL);
    if(TVR_NO_SVL_RECORD == i4_ret)
    {
        /*reset blue mute immediately.*/
        DBG_INFO((MSCVT_LOG_PREFIX" TVR_NO_SVL_RECORD\r\n"));
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE_MUTE));

        //for DTV02237254,switch to TV from SCH(virtual src),ap can not recv NAV_UI_MSG_EMPTY_SVL msg,this flow is different from isl flow
        //isl flow: use _ctrl_change_av_inp_by_id > ...  > _ctrl_empty_svl_handler
        //but _mc_custom_dtv_start_svc() would select svctx directly,and would not notify NAV_UI_MSG_EMPTY_SVL if necessary,so add it here
        a_cfg_cust_get_ch_scan_progress(&ui1_scan_progress);
        if((a_util_cnfg_get_crnt_channel_id() == INVALID_CHANNEL_ID) && (ui1_scan_progress == 0))
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" [tuner setup] start show msg to notify scan \n"));
            nav_dispatch_msg_to_component(NAV_COMP_ID_SCREEN_SAVER,
                                          NAV_UI_MSG_EMPTY_SVL,
                                          NULL);
        }
    }
    else if(TVR_OK != i4_ret)
    {
        DBG_ERROR((MSCVT_LOG_PREFIX" a_tv_change_input_src_by_rec() failed. i4_ret = %d.\r\n", i4_ret));
    }




    return i4_ret;
}

static void _mc_app_process_input_thread(void *pv_data)
{
    CMD_CVT_ASYNC_CMD_DATA *pt_cmd = NULL;

    while(!a_msg_convert_terminated())
    {
        pt_cmd = cmd_convert_wait_command();
        if(pt_cmd != NULL)
        {
            msg_convert_recv_cmd(pt_cmd->i4_type, pt_cmd->s_ack, pt_cmd->s_value);
        }
    }
}

static BOOL _msg_convert_is_cast_source(CHAR* ps_name)
{
    INT32       i4_ret              = 0;
    ISL_REC_T   t_isl_rec           = {0};
    CHAR        s_disp_name[16+1];
    UINT8       ui1_crnt_input_src  = 0;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    if(ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<mscvt> Fun:%s, Ln:%d  a_cfg_av_get_disp_name fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
    if(ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<mscvt_cust> Fun:%s, Ln:%d  a_cfg_av_get_input_src fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    i4_ret = a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);
    if(ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<mscvt_cust> Fun:%s, Ln:%d  a_isl_get_rec_by_id fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    if(DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {
        if(NULL != ps_name)
        {
            if (t_isl_rec.ui1_internal_id > 0)
            {
                c_strncpy(ps_name, t_isl_rec.s_src_name, 16);
            }else
            {
                c_strncpy(ps_name, "SMARTCAST", 9);
            }
        }
        return TRUE;
    }
    return FALSE;
}

static VOID _msg_convert_stop_dtv_svc_for_airplay_launch(VOID)
{
    ISL_REC_T  t_current_isl_rec;
    TV_WIN_ID_T     e_focus_id;

    a_tv_get_focus_win(&e_focus_id);
    a_tv_get_isl_rec_by_win_id(e_focus_id,&t_current_isl_rec);
    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"e_video_type =0x%x,nav running %d\n\r",t_current_isl_rec.t_avc_info.e_video_type,nav_is_running(e_focus_id)));
    if(t_current_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST && t_current_isl_rec.t_avc_info.e_video_type != DEV_VTRL_MMP)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"stop svc\n\r"));
        a_tv_stop_by_win_id(e_focus_id);//need stop the svc
    }
}

static INT32 _msg_convert_chg_input_src_to_cast(VOID)
{
    ISL_REC_T   t_isl_rec ={0};
    ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_HOME;

    // FIX ME: PATCH FOR MVV-10704
    // FIX ME: do not change input source while input source is HDMI1 and store demo is launched via conjure
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        printf("\x1b[41m [%s:%s:%d] do not change input source to cast if it's demo mode.\x1b[0m\n",__FILE__,__FUNCTION__,__LINE__);
        return 0;
    }
    // FIX ME: PATCH FOR MVV-10704
    // FIX ME: do not change input source while input source is HDMI1 and store demo is launched via conjure

    if(!_msg_convert_is_cast_source(NULL))
    {
         a_rest_app_reserved_org_input_for_airplay();
        _msg_convert_stop_dtv_svc_for_airplay_launch();
        if(0 == a_isl_get_rec_by_dev_type(DEV_VTRL_CAST, 0, &t_isl_rec) &&
           0 == nav_change_av_inp_by_rec(TV_WIN_ID_MAIN, &t_isl_rec, NULL))
        {
            //nav_ipts_update_current_src();
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"change to smart cast ok\n\r"));
        }
    }
    return 0;
}

VOID msg_convert_custom_pre_app_launch()
{
    _msg_convert_chg_input_src_to_cast();
}

static CMDCVT_APP_MSG_TYPE_T msgcvt_youtue_msg_type;

static INT32 _msg_convert_pop_up_default_msg_proc(HANDLE_T    h_widget,UINT32  ui4_msg,VOID*  pv_param1,VOID*  pv_param2)
{
    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;
            switch(ui4_keycode)
            {
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                case BTN_SELECT:
                     break;
                case BTN_EXIT:
                {
                    switch(msgcvt_youtue_msg_type)
                    {
                        case CMDCVT_MSG_APCMD_COBALT_NETWORK_ERROR:
                            a_tv_net_send_cmd("\n:dtv_app_mtk,cobalt,:dialog=0\n");
                            break;
                        case CMDCVT_MSG_APCMD_YOUTUBE_KIDS_NETWORK_ERROR:
                            a_tv_net_send_cmd("\n:dtv_app_mtk,youtube_kids,:dialog=0\n");
                            break;
                        case CMDCVT_MSG_APCMD_YOUTUBE_TV_NETWORK_ERROR:
                            a_tv_net_send_cmd("\n:dtv_app_mtk,youtube_tv,:dialog=0\n");
                            break;
                        case CMDCVT_MSG_APCMD_YOUTUBE_QUAL_E_NETWORK_ERROR:
                            a_tv_net_send_cmd("\n:dtv_app_mtk,youtube_qual_e,:dialog=0\n");
                            break;
                        default:
                            break;
                    }
                    nav_dialog_hide();
                }
                    return NAVR_OK;
                default:
                    //nav_rcu_key_handler(ui4_keycode);
                    return NAVR_OK;
                }
                break;
        }

        default:
            break;
    }

    return a_ui_simple_dialog_default_msg_proc(h_widget,
                                               ui4_msg,
                                               pv_param1,
                                               pv_param2);
}

static VOID _msg_convert_pop_dlg_ok_fct(VOID)
{
    switch(msgcvt_youtue_msg_type)
    {
        case CMDCVT_MSG_APCMD_COBALT_NETWORK_ERROR:
            a_tv_net_send_cmd("\n:dtv_app_mtk,cobalt,:dialog=0\n");
            break;
        case CMDCVT_MSG_APCMD_YOUTUBE_KIDS_NETWORK_ERROR:
            a_tv_net_send_cmd("\n:dtv_app_mtk,youtube_kids,:dialog=0\n");
            break;
        case CMDCVT_MSG_APCMD_YOUTUBE_TV_NETWORK_ERROR:
            a_tv_net_send_cmd("\n:dtv_app_mtk,youtube_tv,:dialog=0\n");
            break;
        case CMDCVT_MSG_APCMD_YOUTUBE_QUAL_E_NETWORK_ERROR:
            a_tv_net_send_cmd("\n:dtv_app_mtk,youtube_qual_e,:dialog=0\n");
            break;
            default:
            break;
    }
    nav_dialog_hide();
}

static VOID _msg_convert_pop_up_error_message(VOID)
{
    UINT16 ui2_key = MLM_NAV_KEY_NAV_DIALOG_COBALT_NETWORK_MESSAGE;
    GL_POINT_T t_begin_offset = {(-50*4/3), 0};

    nav_dialog_prompt_msg_dialog(NAV_DIALOG_ID_CUSTOM_1,
                                 MLM_NAV_TEXT(nav_get_mlm_lang_id(), ui2_key),
                                 MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_DIALOG_OK),
                                 &t_begin_offset,
                                 _msg_convert_pop_up_default_msg_proc,
                                 _msg_convert_pop_dlg_ok_fct);
    nav_dialog_stop_hide_timer();
}

static VOID _msg_convert_pop_up_sync_nav(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    msgcvt_youtue_msg_type = (CMDCVT_APP_MSG_TYPE_T)pv_tag;
    _msg_convert_pop_up_error_message();
}

static BOOL _msg_convert_check_conjureApp_status(VOID)
{
    BOOL         b_conjure_app_status = TRUE;

    MI_RESULT                   e_ret               = MI_ERR_FAILED;
    MI_HANDLE                   h_MI_MM_Hdl;
    MI_MM_QueryHandleParams_t   stQueryHandleParams;

    UINT32                      ui4_idx             = 0xD431;// %d  =  54321
    CHAR                        szMmName[128]       = {0};

    c_snprintf(szMmName, sizeof(szMmName), "CMA_OVER_MI_MM_%d", ui4_idx);

    DBG_LOG_PRINT((MSCVT_LOG_PREFIX" szMmName:%s.\n",szMmName));

    stQueryHandleParams.pszName = (uint8_t *)szMmName;
    stQueryHandleParams.eMediaType = E_MI_MM_MEDIA_MOVIE;

    e_ret = MI_MM_GetHandle(&stQueryHandleParams,&h_MI_MM_Hdl);
    if(e_ret != MI_OK)
    {
        DBG_ERROR((MSCVT_LOG_PREFIX"MI_MM_GetHandle fail ret = %d\n", e_ret));
        return FALSE;
    }
    DBG_INFO((MSCVT_LOG_PREFIX" MI_MM_GetHandle  = %d\n", h_MI_MM_Hdl));

    return b_conjure_app_status;
}

static BOOL _msg_convert_network_status(VOID)
{
    INT32                   i4_ret = NWR_INV_ARG;
    BOOL                    b_ethernet = FALSE;

    i4_ret = a_nw_get_ethernet_connect_info(&b_ethernet);
    if(NWR_OK != i4_ret)

{
        DBG_LOG_PRINT(("[%s %d] can not get network status !!!\n",__FUNCTION__,__LINE__));
        return FALSE;
    }
    if(!b_ethernet) /* WIFI*/
    {
        NW_WLAN_STATE_T     e_wlan_state;
        a_nw_wlan_status(&e_wlan_state);
        if ((e_wlan_state == NW_WLAN_ASSOCIATE)||(e_wlan_state == NW_WLAN_ASSOCIATING))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else/* WIRED */
    {
        if (NWR_OK == a_get_nw_init_status())
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    return FALSE;
}


static VOID _msg_convert_set_video_discription(UINT16 ui2_idx)
{
    ISO_639_LANG_T  s639_lang = {0};
    UINT16          ui2_tmp_idx = 0;

    if (ui2_idx == TRUE)
    {
        ui2_tmp_idx = 2; /* change to Spanish */
    }
    else
    {
        ui2_tmp_idx = 0; /* to English/change to english */
    }
    mlm_nav_langidx_to_s639(ui2_tmp_idx, s639_lang);
    a_cfg_set_aud_lang(s639_lang);
    a_cfg_custom_set_video_description_status(ui2_idx);
}

static INT32  _dtvsvc_ui_show_hide(UINT8 bt_ui_status)
{
    UINT8           ui1_enabled     = 0;
    INT32           ui1_video_dsc_enabled = a_cfg_custom_get_video_description_status();
    NAV_RETAIL_MODE_POPUP_DLG_T  e_popup_dlg = NAV_RETAIL_MODE_NO_POPUP_DLG;
    REST_API_BT_REMOTE_INFO_T p_remote_info;
    BOOL b_sleep_timer_showing = FALSE;
    static BOOL b_saved_video_dsc_state = FALSE;

    rest_get_bluetooth_status(&p_remote_info);

    a_cfg_get_cc_enabled(&ui1_enabled);
    a_nav_retail_mode_get_dlg_show(&e_popup_dlg);
    a_nav_get_sleep_prompt_dlg_status(&b_sleep_timer_showing);

    DBG_LOG_PRINT(("<mscvt> %s %d bt_ui_status:%d\n",__FUNCTION__,__LINE__,bt_ui_status));


    //BT paired and network connected
    //if(!(2 == p_remote_info.remote_status && _msg_convert_network_status()))
    if(!_msg_convert_network_status())
    {
        DBG_LOG_PRINT(("<mscvt> %s %d p_remote_info:%d nw_status:%d\n",__FUNCTION__,__LINE__,p_remote_info.remote_status,_msg_convert_network_status()));
        return NAVR_NO_ACTION;
    }

    /*if system ui showing*/
    if (bt_ui_status)
    {
        /* hide menu */
        CHAR app[20] = {0};
        a_am_get_active_app(app);
        if(c_strncmp(app,"menu",4) == 0)
        {
            a_amb_pause_app(app);
        }

        /*if cc enable,hide cc*/
        if(ui1_enabled == APP_CFG_CC_ON)
        {
            nav_ci_set_visible(FALSE);
        }
        /*if video description enabled,hide it for now*/
        if(ui1_video_dsc_enabled == 1)
        {
            b_saved_video_dsc_state = TRUE;
            _msg_convert_set_video_discription(0);
        }
        /*hide input list view*/
        nav_hide_component(NAV_COMP_ID_INPUT_SRC);
        /*hide banner and sidebar logo*/
        banner_hide_sidebar();
        nav_hide_component(NAV_COMP_ID_BANNER);
        /*hide revolt info*/
        nav_hide_component(NAV_COMP_ID_REVOLT_INFO);
        /*hide channel select digit pad*/
        nav_hide_component(NAV_COMP_ID_CH_SELECT);
        /*hide pwd dlg digit pad*/
        nav_hide_component(NAV_COMP_ID_PWD_DLG);
        /*hide scrn svr no_signal*/
        nav_hide_component(NAV_COMP_ID_SCREEN_SAVER);

        /*hide sleep timer if need*/
        if(b_sleep_timer_showing)
        {
            /*hide warning view*/
            a_nav_sleep_hide_toast_warning();
            /*stop the sleep timer,otherwise TV will sleep*/
            a_sleep_timer_stop();
        }

        /*in user manual , store mode UI showing...... */
        if (!a_rest_app_get_current_app_is_uml() || retail_mode_view_is_on() || NAV_RETAIL_MODE_NO_POPUP_DLG!= e_popup_dlg)
        {
            DBG_LOG_PRINT(("<mscvt> send exit key to focus ui \n", __func__  ));
            c_iom_send_evt (BTN_EXIT, 100);
        }
    }
    else
    {
        /*cc show again*/
        if(ui1_enabled == APP_CFG_CC_ON)
        {
            nav_ci_set_visible(TRUE);
        }
        /*restore video description*/
        if(b_saved_video_dsc_state == TRUE)
        {
            _msg_convert_set_video_discription(1);
        }

        if(a_common_setting_is_video_block() == TRUE)//DTV03140693
        {
            /*active pwd_dlg digit_pad,check conditon already in pwd_dlg active*/
            nav_grab_activation(NAV_COMP_ID_PWD_DLG);
        }

    }

    return NAVR_OK;
}


static VOID _msg_convert_handle_sys_ui_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    cmd_convert_send_cmd("\n:dtv_app_mtk,am,:system_ui_disable\n");
    _dtvsvc_ui_show_hide(SYSTEM_UI_HIDE);
}


static VOID _msg_convert_handle_sys_ui_show(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    cmd_convert_send_cmd("\n:dtv_app_mtk,am,:system_ui_enable\n");
    _dtvsvc_ui_show_hide(SYSTEM_UI_SHOW);
}


void msg_convert_recv_cmd(INT32 i4_type, const CHAR* s_ack, const CHAR* s_value)
{
    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"type:%d,s_ack:%s,value = %s\n",i4_type,NULL == s_ack? "null" : s_ack,NULL == s_value ? "null" : s_value));
    //DBG_INFO_DIRECT(MSCVT_LOG_PREFIX"type:%d,s_ack:%s,value = %s\n",i4_type,NULL == s_ack? "null" : s_ack,NULL == s_value ? "null" : s_value);
    switch(i4_type)
    {
        case CMDCVT_MSG_APCMD_NETFLIX_RESUME_BY_HOTKEY:
        {
            DBG_LOG_PRINT ((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_NETFLIX_RESUME_BY_HOTKEY\n"));
            msg_convert_custom_launch_netflix();
            break;
        }
        case CMDCVT_MSG_APCMD_MENU_START:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_MENU_START\n\r"));
            a_amb_start_app(MENU_NAME);
            break;
        case CMDCVT_MSG_APCMD_MENU_STOP:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_MENU_STOP\n\r"));
            a_amb_exit_app(MENU_NAME);
            break;
        case CMDCVT_MSG_APCMD_MENU_RESUME:
        {
            BOOL b_return_dir = FALSE;
            BOOL b_need_clean = FALSE; /*enter menu from epg, we should clean internal am stack, otherwise will back to epg*/
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_MENU_RESUME\n\r"));

            if (s_value != NULL)
            {
                if (strcmp(s_value,"sidebar") == 0)
                {
                    b_return_dir = TRUE;
                }
                else if (strcmp(s_value,"cleanstack") == 0)
                {
                    b_need_clean = TRUE;
                }
                if (b_return_dir)
                {
                    a_tv_net_send_cmd("\n:dtv_app_mtk,am,:resumed=menu\n");
                    break; /*have ack value sidebar, don't resume menu*/
                }
            }
            a_msg_convert_resume_menu();
            if (b_need_clean)
            {
                a_amb_clean_stack();
            }
        }
            break;
        case CMDCVT_MSG_APCMD_MENU_PAUSE:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_MENU_PAUSE\n\r"));
            a_amb_resume_app(MSCVT_NAME);
            break;
        case CMDCVT_MSG_APCMD_NAV_START:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_NAV_START\n\r"));
            a_amb_start_app(NAV_NAME);
            break;
        case CMDCVT_MSG_APCMD_NAV_STOP:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_NAV_STOP\n\r"));
            a_amb_exit_app(NAV_NAME);
            break;
        case CMDCVT_MSG_APCMD_NAV_RESUME:
        {
            CHAR s_src_name[32] = {0};

            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_NAV_RESUME\n\r"));
            a_scrn_svr_set_enable(TRUE);
            a_tv_custom_set_banner_visiable_allow(TRUE);

            BOOL b_is_cast_src = _msg_convert_is_cast_source(s_src_name);
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" s_src_name = %s\n",s_src_name));
            if(b_widget_pressed || ui4_last_stoped_app || b_is_cast_src)
            {
                BOOL b_skip_sch = FALSE;
                NAV_RETAIL_MODE_STATUS_T e_retail_status;

                a_nav_retail_mode_get_status(&e_retail_status);
                switch(ui4_last_stoped_app)
                {
                      case MSCVT_STOP_NETFLIX:
                      {
                          if(b_amazon_pressed)
                          {
                              b_skip_sch = TRUE;
                          }

                      }break;
                      case MSCVT_STOP_YOUTUBE:
                      {
                          if(b_amazon_pressed || b_cobalt_pressed)
                          {
                              b_skip_sch = TRUE;
                          }
                      }break;
                      case MSCVT_STOP_AMAZON:
                      {
                          if(b_netflix_pressed)
                          {
                               b_skip_sch = TRUE;
                          }
                      }break;
                      case MSCVT_STOP_BROWSER_CONTORL:
                      {
                         a_rest_app_unlock_launch_sema();
                        if(a_bgm_is_active_standby_state() == TRUE)
                        {
                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[EAM] QS mode,cann't launch APP\r\n"));
                            b_skip_sch = TRUE;
                        }

                      }break;
                      case MSCVT_STOP_BROWSER_AIRPLAY:
                      {
                            b_skip_sch = TRUE;
                            a_rest_app_leave_airplay();
                            ui4_last_stoped_app = MSCVT_STOP_NONE;
                            if(b_is_cast_src)
                            {
                                return;
                            }
                      }
                }

                if (menu_custom_is_blank_screen())
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"blank scrren => don't launch SC Home\r\n"));
                    b_skip_sch = TRUE;
                }
                // if exit Netflix because of input change, don't launch SC Home
                else if (!b_is_cast_src)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"not cast source  => don't launch SC Home\r\n"));
                    b_skip_sch = TRUE;
                }
                // if exit Netflix because of other partner keys, launch partner App
                else if (_g_hotkey_wakeup)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"hotkey wakeup  => launch partner App\r\n"));
                    b_skip_sch = TRUE;
                }
                // if exit Netflix because of other cast_receiver activated, don't launch SC Home
                else if (a_rest_app_get_current_app_is_cast_type() == 0 || a_rest_app_is_native_app_interrupted_by_cast() == 0)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"under | going casting => don't launch SC Home\r\n"));
                    b_skip_sch = TRUE;
                }
                else if (a_rest_app_get_current_app_is_oobe() == 0)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"oobe launching => don't launch SC Home\r\n"));
                    b_skip_sch = TRUE;
                }
                else if(a_rest_current_power_status() != 1)
                {
                    // eco off: 2 ,quick-start off: 0, on: 1.
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"starting standly mode =>don't launch SC Home\r\n"));
                    b_skip_sch = TRUE;
                }
                else if (_b_hotkey_pressed && !b_widget_pressed) //HOME KEY
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"hotkey pressed => launch partner App\r\n"));
                    b_skip_sch = TRUE;
                }
                else if(b_cast_wakeup)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"cast wake up =>don't launch SC Home\r\n"));
                    b_skip_sch = TRUE;
                }
                else if(Get_nav_cec_one_touch_play_flag())
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"cec one touch play =>don't launch SC Home\r\n"));
                    b_skip_sch = TRUE;
                    Clean_nav_cec_one_touch_play_flag();
                }
                else if(e_retail_status == NAV_RETAIL_MODE_LAUNCHING)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"going lanuch retail mode =>don't launch SC Home\r\n"));
                    b_skip_sch = TRUE;
                }

                if(!b_skip_sch)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"go smart cast \r\n"));
                    //a_rest_launch_sc_home();
                    if (c_strcmp(s_src_name, "watchfree") == 0)
                    {
                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" launch WatchFree\n\r"));
                        app_thread_run_launch_app_by_keycode(0xf7, 2);
                    }
                    else if((c_strcmp(s_src_name, "airplay") == 0))
                    {
                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" launch airplay\n\r"));
                        app_thread_run_launch_app_by_keycode(0xaa, 9);
                    }
                    else
                    {
                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" launch SCH\n\r"));
                        app_thread_run_launch_app_by_keycode(0x2d, 2);
                    }
                }
                ui4_last_stoped_app = MSCVT_STOP_NONE;
            }

            if(/*_b_input_src_change && */!b_is_cast_src)
            {
                if(_msg_convert_check_conjureApp_status() == TRUE)
                {
                    UINT8 i;
                    for(i = 0;i < 10;i++)
                    {
                        if(_msg_convert_check_conjureApp_status() == FALSE)
                        {
                            break;
                        }
                        else
                        {
                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"wait for 150ms\n\r"));
                            c_thread_delay(150);
                        }
                    }
                }

                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"resume dtv \r\n"));
                msg_convert_custom_resume_tv();
            }

            {
                CMD_CONVERT_SEND_CMD_T t_send_cmd;
                t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
                t_send_cmd.s_destination = CMDCVT_MACRO_AP_DTVCTX;
                t_send_cmd.s_ack = NULL;
                t_send_cmd.s_command = CMDCVT_MACRO_RESUMED;
                t_send_cmd.s_parameter = CMDCVT_MACRO_NAV;
                cmd_convert_send_command(&t_send_cmd);
                b_widget_pressed = FALSE;
                _b_input_src_change = FALSE;
                ui4_last_stoped_app = MSCVT_STOP_NONE;
            }
            break;
        }
        case CMDCVT_MSG_APCMD_DTV_RESUME:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_DTV_RESUME\n\r"));
            a_msg_convert_resume_tv_signal();
            a_tv_net_send_cmd(":dtv_app_mtk,am,:resumed=dtv\n");
            break;
        case CMDCVT_MSG_APCMD_DTV_PAUSE:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_DTV_PAUSE\n\r"));
            a_tv_net_send_cmd(":dtv_app_mtk,am,:paused=dtv\n");
        }
            break;
        case CMDCVT_MSG_APCMD_WZD_START:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_WZD_START\n\r"));
            a_amb_start_app(WZD_NAME);
            break;
        case CMDCVT_MSG_APCMD_WZD_STOP:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_WZD_STOP\n\r"));
            a_amb_exit_app(WZD_NAME);
            break;
        case CMDCVT_MSG_APCMD_WZD_RESUME:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_WZD_RESUME\n\r"));
            a_msg_convert_resume_wzd();
            break;
        case CMDCVT_MSG_APCMD_WZD_PAUSE:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_WZD_PAUSE\n\r"));
            a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:resume=navigator\n");
            a_amb_clean_stack();
            break;
        case CMDCVT_MSG_APCMD_MMP_START:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_MMP_START\n\r"));
            a_amb_start_app(MMP_NAME);
            break;
        case CMDCVT_MSG_APCMD_MMP_STOP:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_MMP_STOP\n\r"));
            a_amb_exit_app(MMP_NAME);
            break;
        case CMDCVT_MSG_APCMD_MMP_RESUME:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_MMP_RESUME\n\r"));
            DBG_LOG_PRINT(("<mscvt> exiting cast!\r\n"));
            MSCVT_CUST_LOG_ON_FAIL(a_c4tv_apron_stop_current_app());
            MSCVT_CUST_LOG_ON_FAIL(a_c4tv_apron_sync_exit_cast());
            a_msg_convert_resume_mmp();
            break;
        case CMDCVT_MSG_APCMD_MMP_PAUSE:
        {
            /* fix CR DTV00836488  if hotkey (neflix )exit mmp ,set icl */
            UINT32  ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_UNKNOWN;
            SIZE_T  z_size = ICL_RECID_CUSTOM_MMP_EXIT_REASON_SIZE;
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_MMP_PAUSE\n\r"));

            if (s_value)
            {
                ui4_exit_reason = ICL_RECID_CUSTOM_MMP_EXIT_REASON_BY_NETFLIX_LAUNCH;

                if(a_icl_set(ICL_MAKE_ID (ICL_GRPID_CUSTOM_MMP, ICL_RECID_CUSTOM_MMP_EXIT_REASON), (VOID*) &ui4_exit_reason, z_size) != 0)
                {
                    DBG_ERROR((MSCVT_ERROR_HEADER"icl set mmp exit reason error!!\n"));
                }
            }
            a_amb_resume_app(MSCVT_NAME);
        }
            break;
#ifdef APP_WFD_SUPPORT
        case CMDCVT_MSG_APCMD_WFD_START:
                a_amb_start_app(WFD_NAME);
                break;
        case CMDCVT_MSG_APCMD_WFD_STOP:
                a_amb_exit_app(WFD_NAME);
                break;
        case CMDCVT_MSG_APCMD_WFD_RESUME:
                a_msg_convert_resume_wfd();
                break;
        case CMDCVT_MSG_APCMD_WFD_PAUSE:
                a_amb_pause_app(WFD_NAME);
                break;
#endif
        case CMDCVT_MSG_APCMD_MSCVT_RESUME:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_MSCVT_RESUME\n\r"));
            msg_convert_custom_resume_mscvt();
            break;
        case CMDCVT_MSG_APCMD_MSCVT_PAUSE:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_MSCVT_PAUSE\n\r"));
            msg_convert_custom_pause_mscvt();
            break;
        case CMDCVT_MSG_APCMD_RESUME_TV_SIGNAL:
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_RESUME_TV_SIGNAL\n\r"));
                a_tv_net_send_cmd(":dtv_app_mtk,dtv_app_mtk,:pause=mscvt\n");
            }
            break;
        case CMDCVT_MSG_APCMD_SIDEBAR_MMP:
        {
            UINT32 ui4_effective_mnt_count = 0;
            UINT32 ui4_first_effective_idx = 0;

            a_rmv_dev_get_effective_mnt_count(&ui4_effective_mnt_count, &ui4_first_effective_idx);
            if (1 == ui4_effective_mnt_count)
            {
                MSCVT_CUST_LOG_ON_FAIL(a_rmv_dev_set_active_mnt_pnt(ui4_first_effective_idx));

                a_menu_shortcut_link(MENU_SHORT_CUT_MMP_MEDIA_TYPE);
            }
            else
            {
                a_menu_shortcut_link(MENU_SHORT_CUT_MMP_DEV_LIST);
            }

            break;
        }
        case CMDCVT_MSG_APCMD_SIDEBAR_GUIDED_SETUP:
        {
            a_menu_shortcut_link(MENU_SHORT_CUT_GUIDE_SETUP);
            break;
        }
        case CMDCVT_MSG_APCMD_STATUS:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_STATUS\n\r"));
            break;
        }
        case CMDCVT_MSG_APCMD_3DAP_SHTDN:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_3DAP_SHTDN\n\r"));
            cmd_convert_send_shtdn_signal();
            _b_wait_for_3rd_shtdn = FALSE;
        }
            break;
        case CMDCVT_MSG_APCMD_3DAP_PRE_SHTDN: /* for test */
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_3DAP_PRE_SHTDN\n\r"));
            a_tv_net_send_cmd(":dtv_app_mtk,am,:shutdown=3rd_party\n");
        }
            break;
        case CMDCVT_MSG_APCMD_VISIBLE_CHECK:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_VISIBLE_CHECK\n\r"));

            CHAR ps_cmd[MSCVT_AM_CMD_MAX_LENGTH] = {0};

            if (s_value == NULL)
            {
                DBG_ERROR((MSCVT_LOG_PREFIX"dtv_app_mtk get ap name\n"));
                break; /*no value error*/
            }
            else
            {
                if (a_msg_convert_visible_check((CHAR*)s_value) == TRUE)
                {
                    c_sprintf(ps_cmd,"\n:dtv_app_mtk,am,:visible_check=%s:yes\n", s_value);
                }
                else
                {
                    c_sprintf(ps_cmd,"\n:dtv_app_mtk,am,:visible_check=%s:no\n", s_value);
                }
                a_tv_net_send_cmd(ps_cmd);
            }
        }
        break;
        case CMDCVT_MSG_APCMD_ENTER_AIRPLAY:
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"enter airplay\r\n"));
                UINT32 ui4_power_mode = 0;
                a_cfg_custom_get_drv_eco_mode(&ui4_power_mode);

                //only quick start mode need wake up tv first
                if (FALSE == a_am_is_power_on() &&
                    ui4_power_mode > 0)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX" current in power off status, omit the request resource, please note it\r\n"));

                    //if (a_bgm_is_active_standby_state())
                    {
                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"active standby mode, wake up system as cast break in, current time:{%d}\r\n", c_os_get_sys_tick()*c_os_get_sys_tick_period()));
                        a_bgm_exit_active_standby_with_wakeup_reason(PCL_WAKE_UP_REASON_AIRPLAY);
                    }
                }

                 _msg_convert_stop_dtv_svc_for_airplay_launch();
                 a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_RESUMED);
                 if(a_rest_app_get_current_app_is_semaphore() != 0)
                {
                    a_rest_app_launch_native_app_notify("REST_APP_NAME_SEMAPHORE");
                }
                 rest_event_notify_current_input("CAST:BREAKIN:airplay");
                b_browser_airplay_started = TRUE;
                a_c4tv_apron_force_revoke_resource();
                a_nav_power_set_component_enable(TRUE);
             }
            break;
            case CMDCVT_MSG_APCMD_ENTER_SCH:
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" enter sch\r\n"));
                a_rest_app_reserved_org_input_for_airplay();
                a_c4tv_apron_force_revoke_resource();
                //a_rest_app_select_virtual_input("SMARTCAST");
             }
            break;
            case CMDCVT_MSG_APCMD_DISABLED_AIRPLAY:
            {
                 UINT8 airplay_disenable = 1;
                 acfg_set(IDX_CUSTOM_AIRPLAY_STATE_CTRL, &airplay_disenable, 1);
                 _rest_app_create_virtual_inputs();
                 DBG_LOG_PRINT((MSCVT_LOG_PREFIX" notify airplay/disabled\r\n"));
                // rest_event_notify("airplay/disabled",0,"");
                 rest_notify_airplay_disabled();
                 //a_rest_launch_sc_home();
             }
            break;
            case CMDCVT_MSG_APCMD_ENABLED_AIRPLAY:
            {
              UINT8 airplay_status = 0;
              SIZE_T  z_size;
              INT32    i4_ret = acfg_get(IDX_CUSTOM_AIRPLAY_STATE_CTRL, &airplay_status, &z_size);
              if((i4_ret != APP_CFGR_OK)) {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_ENABLED_AIRPLAY Failed to get IDX_CUSTOM_AIRPLAY_STATE_CTRL\n\r"));
              }

              DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_ENABLED_AIRPLAY IDX_CUSTOM_AIRPLAY_STATE_CTRL airplay_status Value: {%d} , b_browser_airplay_started: %s\n\r", airplay_status, b_browser_airplay_started? "TRUE": "FALSE"));

              if(airplay_status) {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_ENABLED_AIRPLAY Enabling Airplay \n\r"));
                UINT8 airplay_disenable = 0;
                acfg_set(IDX_CUSTOM_AIRPLAY_STATE_CTRL, &airplay_disenable, 1);
                if (access(REST_CONFIG_FILE_UPDATE, F_OK) != -1) {
                  DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_UPDATE));
                  _json_parse_config_file((CHAR*)REST_CONFIG_FILE_UPDATE, TRUE);
                }
                _rest_app_create_virtual_inputs();
              } else {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_ENABLED_AIRPLAY Airplay already enabled\n\r"));
              }

              a_rest_app_launch_native_app_notify("REST_APP_NAME_SEMAPHORE");
              rest_event_notify_current_input("CAST:BREAKIN:airplay");
              b_browser_airplay_started = TRUE;
              a_rest_app_select_virtual_input("browser_ctrl");
            }
            break;
        case CMDCVT_MSG_APCMD_VUDU_NAV_PAUSE:  //you can do some custom active here
        case CMDCVT_MSG_APCMD_NAV_PAUSE:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_NAV_PAUSE\n\r"));
            a_msg_convert_pause_tv();
            a_cfg_set_app_status (APP_CFG_APP_STATUS_LAST_ENTRY);
            a_tv_net_set_OSD_status();

            if(NULL != s_ack)
            {
                 UINT32 ui4_power_mode = 0;
                 PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
                 a_cfg_custom_get_drv_eco_mode(&ui4_power_mode);

                if (0 == strcmp(s_ack, "netflix")||
                    0 == strcmp(s_ack, "vzairplay")||
                    0 == strcmp(s_ack, "amazon_ignition") ||
                    0 == strcmp(s_ack, "Cobalt YTTV")||
                    0 == strcmp(s_ack, "YouTube Kids")||
                    0 == strcmp(s_ack, "YouTube TV")||
                    0 == strcmp(s_ack, "youtube_qual_e")||
                    0 == strcmp(s_ack, "browser_ctrl")||
                    0 == strcmp(s_ack, "appletv")||
                    0 == strcmp(s_ack, "hbomax") ||
                    0 == strcmp(s_ack, "castcore"))
                {
                    if (0 == strcmp(s_ack, "browser_ctrl"))
                    {
                        if(_b_browser_stopped)
                        {
                            _b_browser_stopped = FALSE;
                        }
                        else
                        {
                            e_wakeup_reason = PCL_WAKE_UP_REASON_AIRPLAY;
                        }
                        a_rest_app_lock_launch_sema();
                        b_browser_starting = TRUE;
                        // _b_browser_ctrl_alive = TRUE;
                        a_slogo_hide(0);
                        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_RESUMED);
                    }
                    if(FALSE == a_rest_is_conjure_install())
                    {
                        MSCVT_CUST_LOG_ON_FAIL(a_c4tv_apron_fake_enter_cast_mode());
                    }
                    else
                    {
                        _msg_convert_chg_input_src_to_cast();
                    }
                    if (0 == strcmp(s_ack, "netflix"))
                    {
                        _b_hotkey_netflix_started = TRUE;
                         _b_netflix_alive = TRUE;
                        a_rest_app_reset_key_code(0);
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_NATIVE_NETFLIX");
                        e_wakeup_reason = PCL_WAKE_UP_REASON_ETHERNET;
                    }
                    else if (0 == strcmp(s_ack, "vzairplay"))
                    {
                        b_browser_airplay_started = TRUE;
                        e_wakeup_reason = PCL_WAKE_UP_REASON_AIRPLAY;
                    }
                    else if (0 == strcmp(s_ack, "Cobalt YTTV"))
                    {
                        _b_cobalt_alive = TRUE;
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_COBALT");
                        e_wakeup_reason = PCL_WAKE_UP_REASON_ETHERNET;
                    }
                    else if (0 == strcmp(s_ack, "YouTube Kids"))
                    {
                        _b_cobalt_alive = TRUE;
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_COBALT_KIDS");
                    }
                    else if (0 == strcmp(s_ack, "YouTube TV"))
                    {
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_COBALT_TV");
                    }
                    else if (0 == strcmp(s_ack, "youtube_qual_e"))
                    {
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_COBALT_QUAL");
                    }
                    else if (0 == strcmp(s_ack, "browser_ctrl"))
                    {
                        a_rest_app_unlock_launch_sema();
                        //b_browser_starting = FALSE;
                        //a_rest_app_launch_native_app_notify("REST_APP_NAME_SEMAPHORE");
                    }
                    else if(0 == strcmp(s_ack, "amazon_ignition"))
                    {
                        _b_amazon_alive = TRUE;
                        a_rest_app_reset_key_code(0);
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_NATIVE_AMAZON");
                    }
                    else if(0 == strcmp(s_ack, "appletv"))
                    {
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_APPLETV");
                    }
                    else if(0 == strcmp(s_ack, "hbomax"))
                    {
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_HBOMAX");
                    }
                    else if(0 == strcmp(s_ack, "castcore"))
                    {
                        e_wakeup_reason = PCL_WAKE_UP_REASON_CASTCORE;
                        a_bgm_exit_active_standby_with_wakeup_reason(PCL_WAKE_UP_REASON_CASTCORE);
                        a_rest_app_launch_native_app_notify("REST_APP_NAME_CASTCORE");
                    }

                    MSCVT_CUST_LOG_ON_FAIL(a_c4tv_apron_stop_current_app());
                    MSCVT_CUST_LOG_ON_FAIL(a_c4tv_apron_sync_exit_cast());
                    a_rest_app_is_native_app_interrupted_by_cast();
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[EAM] %s is power on:%d,power mode:%d e_wakeup_reason = %d\r\n",s_ack,a_am_is_power_on(),ui4_power_mode,e_wakeup_reason));
                    if (FALSE == a_am_is_power_on() && e_wakeup_reason != PCL_WAKE_UP_REASON_UNKNOWN)
                    {
                        if(!(e_wakeup_reason  == PCL_WAKE_UP_REASON_AIRPLAY && ui4_power_mode == 0))
                        {
                            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"wake up TV now \r\n", s_ack));
                            a_bgm_exit_active_standby_with_wakeup_reason(e_wakeup_reason);
                        }
                    }
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"starting %s => ENTER CAST!\r\n", s_ack));
                }
            }

            {//make sure pre app paused and current app is mscvt
                CHAR sz_active_app[32] = {0};
                UINT32 ui4_max_try = 15;
                while(AEER_OK == a_am_get_active_app(sz_active_app) &&
                      c_strncmp(sz_active_app,MSCVT_NAME,c_strlen(MSCVT_NAME))!=0&&
                      --ui4_max_try > 0)
                {
                    usleep(150*1000);
                }
            }

            {
                CMD_CONVERT_SEND_CMD_T t_send_cmd;
                t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
                t_send_cmd.s_destination = CMDCVT_MACRO_AM;
                t_send_cmd.s_ack = NULL;
                t_send_cmd.s_command = CMDCVT_MACRO_PAUSED;
                t_send_cmd.s_parameter = CMDCVT_MACRO_NAV;
                cmd_convert_send_command(&t_send_cmd);
            }
            break;
        case CMDCVT_MSG_APCMD_3RD_APP_STARTED:
        {
            if ( s_value == NULL)
            {
                DBG_ERROR(("<mscvt>[%s %d] value is null\n",__FUNCTION__,__LINE__));
                break;
            }
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CMDCVT_MSG_APCMD_3RD_APP_STARTED s_value : %s: \r\n", s_value));

            if (0 == strcmp(s_value, "netflix")||
                0 == strcmp(s_value, "vzairplay")||
                0 == strcmp(s_value, "amazon_ignition") ||
                0 == strcmp(s_value, "Cobalt YTTV")||
                0 == strcmp(s_value, "YouTube Kids")||
                0 == strcmp(s_value, "YouTube TV")||
                0 == strcmp(s_value, "youtube_qual_e")||
                0 == strcmp(s_value, "browser_ctrl")||
                0 == strcmp(s_value, "appletv")||
                0 == strcmp(s_value, "hbomax") ||
                0 == strcmp(s_value, "castcore"))
            {
                if (0 != strcmp(s_value, "browser_ctrl"))
                {
                    if (!_msg_convert_is_cast_source(NULL))
                    {
                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"switch input to CAST\n\r"));
                        _msg_convert_chg_input_src_to_cast();
                    }

                    if(0 != strcmp(s_value, "vzairplay"))
                    {
                      a_rest_app_select_virtual_input((CHAR*)s_value);
                    }
                    else
                    {
                        b_browser_airplay_started = TRUE;
                    }

                    if (0 == strcmp(s_value, "netflix"))
                    {
#ifdef MT5583_MODEL //for MVD-1591. due to layer1 initial size is 1080P by CC init. So add patch for AC on first time to launched CSP/netflix(720P) and set zoom sector again.
#ifdef APP_ZOOM_MODE_SUPPORT
                        static b_zoom_3rd_app = FALSE;

                        ZOOM_SECTOR_ITEM e_curr_sector = a_zoom_mode_get_current_sector();
                        if(b_zoom_3rd_app ==  FALSE)
                        {
                            a_zoom_mode_select_sector(e_curr_sector, TRUE);
                            b_zoom_3rd_app = TRUE;
                        }
#endif
#endif
                        b_netflix_pressed = FALSE;
                        _b_netflix_alive = TRUE;

                    }
                    else if (0 == strcmp(s_value, "Cobalt YTTV")  ||
                             0 == strcmp(s_value, "YouTube Kids") ||
                             0 == strcmp(s_value, "youtube_qual_e")||
                             0 == strcmp(s_value, "YouTube TV"))
                    {
                        _b_cobalt_alive = TRUE;
                    }
                    else if(0 == strcmp(s_value, "amazon_ignition"))
                    {
                        b_amazon_pressed = FALSE;
                        _b_amazon_alive = TRUE;
                    }
                    else if(0 == strcmp(s_value, "appletv"))
                    {
                        _b_appletv_alive = TRUE;
                    }
                    else if(0 == strcmp(s_value, "hbomax"))
                    {
                        _b_hbomax_alive = TRUE;
                    }
                    else if(0 == strcmp(s_value, "castcore"))
                    {
                        _b_castcore_alive = TRUE;
                    }
                    a_rest_app_reserved_org_input_for_airplay();
                }
                else
                {
                     _b_browser_ctrl_alive = TRUE;
                     b_widget_pressed = FALSE;
                     _b_browser_stopped = FALSE;
                }

                a_amb_resume_app(MSCVT_NAME);

                DBG_INFO((MSCVT_LOG_PREFIX"%s is started\n", s_value));
                b_cast_wakeup = FALSE;
                /* Only notify SCH when the input source is in SC
                   Because the input source might be WatchFree or AirPlay */
                CHAR s_src_name[33] = {0};
                if (_msg_convert_is_cast_source(s_src_name) && c_strncmp(s_src_name, "SMARTCAST", 9) == 0 )
                {
                    rest_event_notify_current_input("CAST:SMARTCAST:VTRL");
                }

                a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_RESUMED);
            }
            break;
        }
        case CMDCVT_MSG_APCMD_3RD_APP_BACKGMED:
        case CMDCVT_MSG_APCMD_3RD_APP_STOPPED:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"%s\r\n",i4_type == CMDCVT_MSG_APCMD_3RD_APP_STOPPED ? "CMDCVT_MSG_APCMD_3RD_APP_STOPPED" :"CMDCVT_MSG_APCMD_3RD_APP_BACKGMED" ));

            ICL_3RD_AP_CHG_INFO_T t_change_info;

            c_memset(&t_change_info, 0, sizeof(ICL_3RD_AP_CHG_INFO_T));

            if (s_value)
            {
                c_strncpy(t_change_info.s_org_app_id, s_value, ICL_GRPID_NET_SVC_APP_NAME_SIZE);
                t_change_info.ui1_org_app_status = ICL_3RD_AP_STATUS_STOP;
            }
            else
            {
                DBG_ERROR(("dtv_app_mtk get value data is null!\n"));
                break;
            }
            a_tv_net_set_3rd_ap_status((CHAR*)s_value, t_change_info.ui1_org_app_status);

            if (s_ack)
            {
                c_strncpy(t_change_info.s_focus_app_id, s_ack, ICL_GRPID_NET_SVC_APP_NAME_SIZE);
            }
            a_icl_set_net_tv_svc_change (t_change_info);

            // 3rd-app event notfiy
            if(s_ack && (0==strncmp(s_ack, CMDCVT_MACRO_AP_DTVCTX, strlen(CMDCVT_MACRO_AP_DTVCTX)+1)))
            {
                cmd_convert_send_3rd_ap_event_signal(i4_type, s_value);
            }

            DBG_ERROR(("CMDCVT_MSG_APCMD_3RD_APP_STOPPED: %s\n", s_value));

            if (0 == strcmp(s_value, "netflix")||
                0 == strcmp(s_value, "amazon_ignition")||
                0 == strcmp(s_value, "Cobalt YTTV")||
                0 == strcmp(s_value, "YouTube Kids")||
                0 == strcmp(s_value, "YouTube TV")||
                0 == strcmp(s_value, "youtube_qual_e")||
                0 == strcmp(s_value, "browser_ctrl")||
                0 == strcmp(s_value, "appletv")||
                0 == strcmp(s_value, "hbomax") ||
                0 == strcmp(s_value, "vzairplay") ||
                0 == strcmp(s_value, "castcore"))
            {

                if (0 == strcmp(s_value, "netflix"))
                {
                    _b_netflix_alive = FALSE;
                    _b_hotkey_netflix_started = FALSE;
                    b_netflix_pressed = FALSE;
                    ui4_last_stoped_app = MSCVT_STOP_NETFLIX;
                    ui4_g_last_key_down = 0;
                }
                else if (0 == strcmp(s_value, "Cobalt YTTV")||
                         0 == strcmp(s_value, "YouTube Kids")||
                         0 == strcmp(s_value, "YouTube TV")||
                         0 == strcmp(s_value, "youtube_qual_e"))
                {
                    _b_cobalt_alive = FALSE;
                    ui4_last_stoped_app = MSCVT_STOP_YOUTUBE;
                }
                else if(0 == strcmp(s_value, "amazon_ignition"))
                {
                    _b_amazon_alive = FALSE;
                    b_amazon_pressed = FALSE;
                    ui4_last_stoped_app = MSCVT_STOP_AMAZON;
                }
                else if(0 == strcmp(s_value, "vzairplay"))
                {
                  DBG_LOG_PRINT((MSCVT_LOG_PREFIX"vzairplay stop!!!\n"));
                  ui4_last_stoped_app = MSCVT_STOP_BROWSER_AIRPLAY;
                  b_browser_airplay_started = FALSE;
                }
                else if (0 == strcmp(s_value, "browser_ctrl"))
                {
                    b_browser_starting = FALSE;
                    _b_browser_ctrl_alive = FALSE;
                    ui4_last_stoped_app = MSCVT_STOP_BROWSER_CONTORL;
                    if(b_browser_airplay_started == TRUE)
                    {
                        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"airplay stop!!!\n"));
                         ui4_last_stoped_app = MSCVT_STOP_BROWSER_AIRPLAY;
                         b_browser_airplay_started = FALSE;
                    }
                    if(!a_am_is_power_on() && i4_type == CMDCVT_MSG_APCMD_3RD_APP_STOPPED)
                    {
                        _b_browser_stopped = TRUE;
                    }
                }
                else if(0 == strcmp(s_value, "appletv"))
                {
                 _b_appletv_alive = FALSE;
                }
                else if(0 == strcmp(s_value, "hbomax"))
                {
                 _b_hbomax_alive = FALSE;
                }
                else if(0 == strcmp(s_value, "castcore"))
                {
                 _b_castcore_alive = FALSE;
                }

                _b_hotkey_pressed = FALSE;
                _g_hotkey_wakeup = FALSE;
                a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);
            }
            break;
        }
        case CMDCVT_MSG_APCMD_3RD_APP_RESUMED:
        {
            ICL_3RD_AP_CHG_INFO_T t_change_info;
            c_memset(&t_change_info, 0, sizeof(ICL_3RD_AP_CHG_INFO_T));
            if (s_value == 0)
            {
                DBG_ERROR((MSCVT_LOG_PREFIX"dtv_app_mtk get change ap name:\n"));
                break;
                /*no valuedata no need to set icl*/
            }
            else
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_3RD_APP_RESUMED\n\r"));
                if(s_value)
                {
                    CHAR * ps_proc = c_strdup(s_value);
                    CHAR * ps_app = 0;

                    if(ps_proc == NULL)
                    {
                        DBG_ERROR((MSCVT_LOG_PREFIX"dtv_app_mtk get valuedata null!\n"));
                        break;
                    }

                    if ((ps_app = c_strchr( ps_proc, '.' )) != NULL)
                    {
                        *ps_app++ = '\0';
                    }
                    else
                    {
                        ps_app = ps_proc;
                    }
                    c_strncpy(t_change_info.s_org_app_id, ps_app, ICL_GRPID_NET_SVC_APP_NAME_SIZE);
                    t_change_info.ui1_org_app_status = ICL_3RD_AP_STATUS_RESUME;
                    c_mem_free(ps_proc);
                }
            }
            a_tv_net_set_3rd_ap_status((CHAR*)s_value, t_change_info.ui1_org_app_status);
            if (s_ack != 0)
            {
                c_strncpy(t_change_info.s_focus_app_id, s_ack, ICL_GRPID_NET_SVC_APP_NAME_SIZE);
            }

            a_icl_set_net_tv_svc_change (t_change_info);
        }
        break;
        case CMDCVT_MSG_APCMD_3RD_APP_PAUSED:
        {
            ICL_3RD_AP_CHG_INFO_T t_change_info;
            c_memset(&t_change_info, 0, sizeof(ICL_3RD_AP_CHG_INFO_T));
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_3RD_APP_PAUSED\n\r"));
            if (s_value == 0)
            {
                DBG_ERROR(("dtv_app_mtk get change ap name:\n"));
                break;
            }
            else
            {
                if(s_value)
                {
                    CHAR * ps_proc = c_strdup(s_value);
                    if(ps_proc == NULL)
                    {
                        DBG_ERROR(("dtv_app_mtk get valuedata null!\n"));
                        break;
                    }
                    CHAR * ps_app = 0;
                    if ((ps_app = c_strchr( ps_proc, '.' )) != NULL)
                    {
                        *ps_app++ = '\0';
                    }
                    else
                    {
                        ps_app = ps_proc;
                    }
                    c_strncpy(t_change_info.s_org_app_id, ps_app, ICL_GRPID_NET_SVC_APP_NAME_SIZE);
                    t_change_info.ui1_org_app_status = ICL_3RD_AP_STATUS_PAUSE;
                    c_mem_free(ps_proc);
                }
            }
            a_tv_net_set_3rd_ap_status((CHAR*)s_value, t_change_info.ui1_org_app_status);

            if (s_ack)
            {
                c_strncpy(t_change_info.s_focus_app_id, s_ack, ICL_GRPID_NET_SVC_APP_NAME_SIZE);
            }
            if(s_value)
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"%s paused\r\n",s_value));
            }
            a_icl_set_net_tv_svc_change (t_change_info);
        }
            break;
        case CMDCVT_MSG_APCMD_emanual_STOPPED:
        {
            DBG_INFO(("====== emanual is stopped.\n"));

            UINT8 ui1_val = ICL_EMANUAL_STATUS_OFF;
            a_icl_set(ICL_MAKE_ID(ICL_GRPID_EMANUAL_STATUS, ICL_RECID_EMANUAL_STATUS),
                  &ui1_val, ICL_RECID_EMANUAL_STATUS_SIZE);

#ifdef APP_CFG_DIMMING_OFF_IN_EMANUAL
            a_cfg_custom_update_dimming_idx();
#endif
        }
            break;

#ifdef TVIS_UI_SUPPORT
        case CMDCVT_MSG_APCMD_FOCUSED:
        {
            _b_dtv_getfocus = TRUE;
        }
        break;
         case CMDCVT_MSG_APCMD_UNFOCUSED:
        {
            _b_dtv_getfocus = FALSE;
        }
        break;

        case CMDCVT_MSG_APCMD_TVIS_URL:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_TVIS_URL\n\r"));

            CHAR ps_cmd[TVIS_URL_LEN+1] = {0};
            CHAR ps_url[TVIS_URL_LEN+1] = {0};

            if (s_value != NULL)
            {
                if (s_value[0] == '[')
                {
                    c_strncpy(ps_url, s_value + 1, (c_strlen(s_value) - 2));
                }

                if (_is_launch_tvis_url())
                {
                    c_snprintf(ps_cmd, TVIS_URL_LEN,
                        "\n:dtv_app_mtk,am,:start_ex=[generic_osd,\"-w 1280 -h 720 -x generic_osd_app -m NO -u %s\"]\n", ps_url);
                    a_tv_net_send_cmd(ps_cmd);
                    e_g_tvis_ui_status = TVIS_UI_STAT_ON;
                }
            }
        }
            break;

        case CMDCVT_MSG_APCMD_TVIS_TERMINATE:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_TVIS_TERMINATE\n\r"));
        #ifndef TVIS_TEST_SUPPORT
            a_tv_net_send_cmd("\n:dtv_app_mtk,am,:stop=generic_osd\n");
            e_g_tvis_ui_status = TVIS_UI_STAT_OFF;
        #endif
        }
            break;
#endif

#ifdef APP_IPCC_SUPPORT
      case CMDCVT_MSG_APCMD_CC_ON:
            {
                 DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_CC_ON\n\r"));
                 a_tv_net_set_IPCC_status(TRUE);
                 a_amb_dispatch_msg(MENU_NAME,MENU_MSG_AM_ASYNC_IPCC_CHG,NULL,0);
            }
             break;
            case CMDCVT_MSG_APCMD_CC_OFF:
            {
                 DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_CC_OFF\n\r"));
                 a_tv_net_set_IPCC_status(FALSE);
                 a_amb_dispatch_msg(MENU_NAME,MENU_MSG_AM_ASYNC_IPCC_CHG,NULL,0);
            }
            break;
#endif
        case CMDCVT_MSG_APCMD_COBALT_NETWORK_ERROR:
        case CMDCVT_MSG_APCMD_YOUTUBE_KIDS_NETWORK_ERROR:
        case CMDCVT_MSG_APCMD_YOUTUBE_TV_NETWORK_ERROR:
        case CMDCVT_MSG_APCMD_YOUTUBE_QUAL_E_NETWORK_ERROR:
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_COBALT_NETWORK_ERROR.\n"));
            nav_request_context_switch(_msg_convert_pop_up_sync_nav, (VOID*) i4_type, NULL, NULL);
            break;
#if 0
        case CMDCVT_MSG_APCMD_KEY_IDLE_580:
            DBG_LOG_PRINT((" CMDCVT_MSG_APCMD_KEY_IDLE_580.\n"));
            nav_request_context_switch(_msg_convert_airplay_handle_timeout, (VOID*) i4_ret, NULL, NULL);
            break;
#endif
        case CMDCVT_MSG_APCMD_NETFLIX_START:
        {
            _b_netflix_alive = TRUE;
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_NETFLIX_START.\n"));
            break;
        }
        case CMDCVT_MSG_APCMD_NETFLIX_STOP:
        {
            _b_netflix_alive = FALSE;
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_NETFLIX_STOP.\n"));
            break;
        }
        case CMDCVT_MSG_APCMD_AMAZON_IGNITION_START:
        {
            _b_amazon_alive = TRUE;
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_AMAZON_IGNITION_START.\n"));
            break;
        }
        case CMDCVT_MSG_APCMD_AMAZON_IGNITION_STOP:
        {
            _b_amazon_alive = FALSE;
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_AMAZON_IGNITION_STOP.\n"));
            break;
        }
        case CMDCVT_MSG_APCMD_COBALT_START:
        {
            _b_cobalt_alive = TRUE;
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_COBALT_START.\n"));
            break;
        }
        case CMDCVT_MSG_APCMD_COBALT_STOP:
        {
            _b_cobalt_alive = FALSE;
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_COBALT_STOP.\n"));
            break;
        }
        case CMDCVT_MSG_APCMD_SCRNSAVER_HIDE:
        {
           DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_SCRNSAVER_HIDE.\n"));
            if (NULL != s_value && 0 == strcmp(s_value, "netflix"))
            {
                   b_netflix_inited = TRUE;
            }
            break;
        }
        case CMDCVT_MSG_APCMD_SETFLASHTIME:
        {
            INT32 relative_deflash_time = s_value?atol(s_value):0;
            TIME_T  t_crnt_utc = c_dt_get_utc(NULL, NULL);
            TIME_T  flash_time=t_crnt_utc+relative_deflash_time;
            if(relative_deflash_time==0)
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" clear Freshtime\n"));
                flash_time=0;
            }
            NFX_AR_MSG_T send_cmd={
                .msg_type=TIME_TYPE,
                .sc.t_refresh_time=flash_time
            };
            a_nfx_always_refresh_process(&send_cmd);
        }
        break;
        case CMDCVT_MSG_APCMD_FLASHSTATUS_COMPLETE:
        {
            NFX_AR_MSG_T send_cmd={
                .msg_type=ACTION_TYPE,
                .sc.t_status=ACTION_COMPLETE
            };
            a_nfx_always_refresh_process(&send_cmd);
        }
        break;
        case CMDCVT_MSG_APCMD_FLASHSTATUS_TIMEOUT:
        {
            NFX_AR_MSG_T send_cmd={
                .msg_type=ACTION_TYPE,
                .sc.t_status=ACTION_TIMEOUT
            };
            a_nfx_always_refresh_process(&send_cmd);
        }
        break;
        case CMDCVT_MSG_APCMD_SYS_UI_HIDE:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_SYS_UI_HIDE.\n"));
            _b_system_ui_showing = FALSE;
            nav_request_context_switch(_msg_convert_handle_sys_ui_hide, NULL, NULL, NULL);
        }
        break;
        case CMDCVT_MSG_APCMD_SYS_UI_SHOW:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_SYS_UI_SHOW.\n"));
            _b_system_ui_showing = TRUE;
            nav_request_context_switch(_msg_convert_handle_sys_ui_show, NULL, NULL, NULL);
        }
        break;
        case CMDCVT_MSG_APCMD_SOFT_MIC_BT_START:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_SOFT_MIC_BT_START.\n"));
            //s_touch("/tmp/soft_mic_pressed");
            msg_convert_custom_notify_btsoftmic_result(SendReqBTSOFTMIC_Q(SOFTMIC_START), CMDCVT_MSG_APCMD_SOFT_MIC_BT_START);
        }
        break;
        case CMDCVT_MSG_APCMD_SOFT_MIC_BT_STOP:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" CMDCVT_MSG_APCMD_SOFT_MIC_BT_STOP.\n"));
            //s_rm("/tmp/soft_mic_pressed");
            msg_convert_custom_notify_btsoftmic_result(SendReqBTSOFTMIC_Q(SOFTMIC_STOP), CMDCVT_MSG_APCMD_SOFT_MIC_BT_STOP);
        }
        break;

        default:
            break;
    }

}

BOOL _hotkey_handler(UINT32 ui4_key_code)
{
    /* Network Disconnected dialog box of Netflix, Netflix hotkey wakeup */

    DEBUG_KEY_FLOW( DBG_LOG_PRINT((MSCVT_LOG_PREFIX"{%s,%d} ui4_key_code:0x%x\n",
                        __FUNCTION__, __LINE__, ui4_key_code )); );

    if(ui4_key_code == BTN_CUSTOM_100)
    {
        return FALSE;
    }

    if(nav_is_channel_scan_active())
    {
        return FALSE;
    }

#ifdef MT5583_MODEL
    DBG_LOG_PRINT(("#### %s(%d) \n", __FILE__, __LINE__ ));
    if(BTN_MIC == ui4_key_code)
    {
        TTS_PLAY(L"Mike");
    }
#endif

    if (BTN_VUDU         == ui4_key_code||
        BTN_AMAZON       == ui4_key_code||
        BTN_MGO          == ui4_key_code||
        BTN_WIDGET       == ui4_key_code||
        BTN_IHEART_RADIO == ui4_key_code||
        BTN_WATCHFREE    == ui4_key_code||
        BTN_REDBOX       == ui4_key_code||
        BTN_HAYSTACK     == ui4_key_code||
        BTN_YOUTUBE      == ui4_key_code||
        BTN_XUMO         == ui4_key_code||
        BTN_DISNEY       == ui4_key_code||
        BTN_PARTNER_2    == ui4_key_code||
        BTN_PARTNER_3    == ui4_key_code||
        BTN_PARTNER_4    == ui4_key_code||
        BTN_PARTNER_5    == ui4_key_code||
        BTN_NETFLIX      == ui4_key_code||
        BTN_CRACKLE      == ui4_key_code||
        BTN_HULU         == ui4_key_code)
    {
        DBG_INFO(("_hotkey_handler(0x%x) sent to am\n", ui4_key_code));

        /*fix input source when entry app still show,entry app hide ui*/
        if(nav_is_component_visible(NAV_COMP_ID_INPUT_SRC))
          {
              nav_hide_component(NAV_COMP_ID_INPUT_SRC);
          }

        if(a_wzd_is_oobe_mode() == TRUE)
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX" OOBE status\n\r"));
            return TRUE;
        }
#ifdef APP_RETAIL_MODE_SUPPORT
        NAV_RETAIL_MODE_STATUS_T e_retail_status = NAV_RETAIL_MODE_INITIAL;
        a_nav_retail_mode_get_status(&e_retail_status);
        if (NAV_RETAIL_MODE_RUNNING == e_retail_status)
        {
            return TRUE;
        }
#endif
        if(a_oled_compensation_is_running())
        {
            a_amb_power_on(FALSE);
            c_thread_delay(20);
        }

        if(FALSE == a_tv_custom_get_tos())
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"tos not accepted,launch sch\n"));
            a_rest_launch_sc_home();
            return TRUE;
        }

        if(nav_is_component_visible(NAV_COMP_ID_VIA_DLG)&&
           TRUE == a_nav_via_dlg_is_show_warning_dialog())
         {
             /* block keys in Network Disconnected dialog box of Netflix */
             return TRUE;
         }
    }
    else{
        return FALSE;
    }

        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" _b_netflix_alive = %d  _b_cobalt_alive = %d,_b_amazon_alive = %d _b_browser_ctrl_alive = %d\n\r",
                                                _b_netflix_alive,
                                                _b_cobalt_alive,
                                                _b_amazon_alive,
                                                _b_browser_ctrl_alive));
        switch(ui4_key_code)
        {
            case BTN_LONG_INPUT:
            {
                if (_b_netflix_alive ||_b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive)
                {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_LONG_INPUT _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_NETFLIX:
            {


                if (_b_browser_ctrl_alive)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_NETFLIX browser_ctrl alive, hide\n\r"));
                    CMD_CONVERT_SEND_CMD_T t_send_cmd;
                    t_send_cmd.s_source = "am";
                    t_send_cmd.s_destination = "browser_ctrl";
                    t_send_cmd.s_ack = "";
                    t_send_cmd.s_command = "hide";
                    t_send_cmd.s_parameter = "browser_ctrl";
                    cmd_convert_send_command(&t_send_cmd);
                }
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"netflix");
#endif
                {
                    msg_convert_custom_launch_netflix();

                    if(_b_browser_ctrl_alive || _b_cobalt_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive)
                    {
                        _b_hotkey_pressed = TRUE;
                    }
                    else
                    {
                         _b_hotkey_pressed = FALSE;
                    }
                }
                b_netflix_pressed = TRUE;
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_NETFLIX _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_VUDU:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"  vu du");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_VUDU _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_AMAZON:
            {
                if (_b_browser_ctrl_alive)
                {
                    DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_AMAZON browser_ctrl alive, hide\n\r"));
                    CMD_CONVERT_SEND_CMD_T t_send_cmd;
                    t_send_cmd.s_source = "am";
                    t_send_cmd.s_destination = "browser_ctrl";
                    t_send_cmd.s_ack = "";
                    t_send_cmd.s_command = "hide";
                    t_send_cmd.s_parameter = "browser_ctrl";
                    cmd_convert_send_command(&t_send_cmd);
                }
                msg_convert_custom_launch_amazon();
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"PrimeVideo");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_browser_ctrl_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_AMAZON _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                b_amazon_pressed = TRUE;
                return TRUE;
            }
            case BTN_IHEART_RADIO:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"iHeartRatio");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_IHEART_RADIO _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_XUMO:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"  Xu mo");
#endif
                if (_b_netflix_alive  || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_XUMO _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_DISNEY:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"Disney+");
#endif
                if (_b_netflix_alive  || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_DISNEY _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_PARTNER_2:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"Peacock");
#endif
                if (_b_netflix_alive  || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_PARTNER_2(Peacock) _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_PARTNER_3:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"Tubi");
#endif
                if (_b_netflix_alive  || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_PARTNER_3(Tubi) _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_PARTNER_4:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"Pluto");
#endif
                if (_b_netflix_alive  || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_PARTNER_4(Pluto) _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_PARTNER_5:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"HBOMAX");
#endif
                if (_b_netflix_alive  || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_PARTNER_5(HBOMAX) _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_CRACKLE:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"Crackle");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_CRACKLE _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_HULU:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"Hulu");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_HULU _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_WATCHFREE:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"WatchFreePluss");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_WATCHFREE _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_REDBOX:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"RedBox");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_REDBOX _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_HAYSTACK:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"HayStack");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_HAYSTACK _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_WIDGET:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"widght");
#endif
                if (_b_netflix_alive || _b_cobalt_alive || _b_browser_ctrl_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive) {
                    _b_hotkey_pressed = TRUE;
                } else {
                    _b_hotkey_pressed = FALSE;
                }
                b_widget_pressed = TRUE;
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_WIDGET _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));
                return TRUE;
            }
            case BTN_CUSTOM_11:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"custom_10");
#endif
                DBG_LOG_PRINT(("launch retail mode by hotkey\n"));
                /* launch retail mode */
                a_tv_custom_launch_retail_mode_by_hotkey();
                return TRUE;
            }
            case BTN_PIP_CH_DOWN:
            {
                DBG_LOG_PRINT(("launch link mode by hotkey\n"));
                a_tv_custom_launch_link_by_hotkey();
                return TRUE;
            }
            case BTN_INPUT_AND_VOL_DOWN://BTN_INPUT_AND_VOL_DOWN:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"input_and_vol_down");
#endif
                DBG_LOG_PRINT(("launch input and vol_down by hotkey\n"));
                a_tv_custom_launch_input_and_voldown_hotkey();
                return TRUE;
            }
            case BTN_YOUTUBE:
            {
#ifdef APP_TTS_SUPPORT
                TTS_PLAY(L"YOUTUBE");
#endif
                msg_convert_custom_launch_youtube();
                if(_b_browser_ctrl_alive || _b_cobalt_alive || _b_amazon_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive)
                {
                    _b_hotkey_pressed = TRUE;
                }else
                {
                     _b_hotkey_pressed = FALSE;
                }
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" hotkey BTN_YOUTUBE _b_hotkey_pressed = %d\n\r",_b_hotkey_pressed));

                return TRUE;
            }
            default:
            {
                DBG_INFO((MSCVT_LOG_PREFIX" A recv key 0x%x\n", ui4_key_code));
                return FALSE;
            }
        }
        return FALSE;
}


VOID msg_convert_custom_airplay_launched()
{
    if (_b_netflix_alive == TRUE || _b_cobalt_alive == TRUE || _b_browser_ctrl_alive == TRUE || _b_amazon_alive == TRUE || _b_appletv_alive == TRUE || _b_hbomax_alive == TRUE || _b_castcore_alive == TRUE) {
    _b_hotkey_pressed = TRUE;
    } else {
    _b_hotkey_pressed = FALSE;
    }
    DBG_LOG_PRINT(("msg_convert_custom_airplay_launched,hotkey_press=%d\n",_b_hotkey_pressed));
}

INT32 msg_convert_custom_active_keyroute_callback(
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    UINT8    ui1_demo_mode = 0;

    UINT32 ui4_key_code = IOM_GET_EVT_GRP_ID((UINT32)pv_param1);

    a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);

    if (ui1_demo_mode != 0)
    {
        return WGLR_OK;
    }


    if (ui4_msg == WGL_MSG_KEY_DOWN ||
        ui4_msg == WGL_MSG_KEY_UP   ||
        ui4_msg == WGL_MSG_KEY_REPEAT)
    {
        if (ui4_msg == WGL_MSG_KEY_DOWN)
        {
            if (FALSE == _hotkey_handler(ui4_key_code))
            {
                a_amb_default_key_handler_ex (ui4_msg, pv_param1, pv_param2);
            }
        }
        else
        {
            a_amb_default_key_handler_ex (ui4_msg, pv_param1, pv_param2);
            DBG_INFO(("[MSGCONVERT] B recv key 0x%x status %d \n",ui4_key_code,ui4_msg));
        }
    }
    return WGLR_OK;

}

INT32 msg_convert_custom_default_keyroute_callback_fct(
                HANDLE_T            h_thread,
                UINT32              ui4_msg,
                UINT32              ui4_key_code)
{
    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        if (FALSE == _hotkey_handler(ui4_key_code) &&
            nav_is_component_visible(NAV_COMP_ID_REVOLT_MISC) &&
            a_revolt_misc_power_seq_cb())
        {
             a_amb_default_key_handler_ex (ui4_msg, (VOID*)ui4_key_code, (VOID*)NULL);
        }
    }
    else
    {
        DBG_INFO(("[MSGCONVERT] recv key 0x%x, status %d \n",ui4_key_code,ui4_msg));
    }

    return 0;
}

BOOL msg_convert_custom_power_seq_cb_fct(VOID)
{
#ifdef APP_HOTKEY_WAKEUP_SUPPORT
    UINT8                ui1_ap_status   = 0;
    PCL_WAKEUP_KEY_T t_wakeup_key = {0};
    INT32               i4_ret = PCLR_OK;
    PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
    c_pcl_get_wakeup_reason(&e_wakeup_reason,NULL);

    a_tv_custom_get_hotkey_wakeup_active(&ui1_ap_status);

    i4_ret = c_pcl_get_wakeup_irkey(&t_wakeup_key);
    if( c_pcl_get_hotkey_active() && i4_ret == PCLR_OK)
    {
        if ( (PCL_WAKEUP_KEY_HOTKEY == t_wakeup_key.e_key_type) && (PCL_WAKE_UP_REASON_IRRC == e_wakeup_reason) &&
             (0x0 == ui1_ap_status) )
        {
            DBG_LOG_PRINT(("[MSGCONVERT] power_seq_cb return true. \n"));
            return TRUE;
        }
        else
        {
            DBG_LOG_PRINT(("[MSGCONVERT] type=%d,reason=%d,status=%d \n",t_wakeup_key.e_key_type,e_wakeup_reason,ui1_ap_status));
        }
    }
    else
    {
        DBG_LOG_PRINT(("[MSGCONVERT] active=%d,i4_ret=%d \n",c_pcl_get_hotkey_active(),i4_ret));
    }

    if(_g_hotkey_wakeup)
    {
        DBG_LOG_PRINT(("receive hotkey command first!\n"));
        _g_hotkey_wakeup =FALSE;
        return TRUE;
    }
#endif
    _g_hotkey_wakeup =FALSE;

    return FALSE;
}

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
static VOID _msgcvt_hotkey_wakeup_from_BGM(VOID)
{
    PCL_WAKEUP_KEY_T    t_wakeup_key = {0};
    INT32               i4_ret = 0;
    UINT8               ui1_ap_status = 0;

    PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;

    a_tv_custom_get_hotkey_wakeup_active(&ui1_ap_status);
    c_pcl_get_wakeup_reason(&e_wakeup_reason,NULL);

    i4_ret = c_pcl_get_wakeup_irkey(&t_wakeup_key);

    if (i4_ret != PCLR_OK)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" [HOTKEY]:c_pcl_get_wakeup_irkey fail,i4_ret=%d\n",i4_ret));
        return;
    }
    if(t_wakeup_key.ui4_wakeupkey == BTN_NETFLIX ||
       t_wakeup_key.ui4_wakeupkey == BTN_AMAZON ||
       t_wakeup_key.ui4_wakeupkey == BTN_YOUTUBE)
    {
        ui4_g_last_key_down = t_wakeup_key.ui4_wakeupkey;
    }

    if ( (!c_pcl_get_hotkey_active()) ||
        (t_wakeup_key.e_key_type != PCL_WAKEUP_KEY_HOTKEY ) ||
        (e_wakeup_reason != PCL_WAKE_UP_REASON_IRRC )       ||
        (0x0 != ui1_ap_status) )  // active hotkey feature
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" [HOTKEY]:status=%d,type=%d,reason=%d\n",
                        ui1_ap_status,t_wakeup_key.e_key_type,e_wakeup_reason));
        return;
    }

    a_tv_custom_hotkey_wakeup(t_wakeup_key.ui4_wakeupkey);
}
#endif

INT32 msg_convert_custom_resume_fct(HANDLE_T  h_app)
{
    char ps_resume_ap[APP_NAME_MAX_LEN+1] = {0};

    if(a_am_get_active_app(ps_resume_ap) != AEER_OK)
    {
        DBG_ERROR((MSCVT_LOG_PREFIX"\n get active app failed\n"));
        return -1;
    }
   // DBG_INFO_DIRECT("[%s %d]\n",__FUNCTION__,__LINE__);

    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s %d] current %s\n",__FUNCTION__,__LINE__, ps_resume_ap));

    if(strncmp(ps_resume_ap,"wfd",strlen("wfd"))==0 && !b_cast_wakeup)
    {
        a_amb_clean_stack();
         DBG_LOG_PRINT((MSCVT_LOG_PREFIX"now resume navigator\n", ps_resume_ap));
        a_msg_convert_resume_navigator();
    }

    if(strncmp(ps_resume_ap,NAV_NAME,strlen(NAV_NAME))==0||
       strncmp(ps_resume_ap,MMP_NAME,strlen(MMP_NAME))==0)
    {
#ifdef TVIS_UI_SUPPORT
        a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);
#endif
        /*reset 3D mode*/
        a_cfg_custom_3D_setting_reset_3D_mode();
    }

    /*When msgconvert resumed, dtv service always stop!!, this is true.. */
    a_icl_custom_set_nw_widget_status(ICL_CUSTOM_NW_WIDGET_APP, NW_APP_STATUS_FULLSCREEN);
    if (APP_TV_NET_SVC_STATUS_RESUMED == a_tv_net_get_tv_svc_status())
    {
        return AEER_OK;
    }
    if (!_b_hotkey_wdg_pressed)
    {
        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_RESUMED);
    }
    _b_hotkey_wdg_pressed = FALSE;

    _mc_set_cc_status(FALSE);
    _mc_custom_dtv_stop_svc();

    a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, TRUE);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));

    if(strncmp(ps_resume_ap,MENU_NAME,strlen(MENU_NAME))!=0)
    {
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    }

    /*turn off test patterns when 3_rd app resume*/
    a_menu_test_patterns_turn_off();

    DBG_INFO((MSCVT_LOG_PREFIX"####%s(%d)turn off test patterns\n",__FUNCTION__,__LINE__));

    return AEER_OK;
}


INT32 msg_convert_custom_pause_fct(HANDLE_T  h_app)
{
    /*todo: if the next resume AP is navigator dtv service should be resumed*/
    char                        ps_resume_ap[APP_NAME_MAX_LEN+1];
    INT32                       i4_amb_ret;
    ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

#ifdef TVIS_UI_SUPPORT
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);
#endif

    i4_amb_ret = a_am_get_next_active_app(ps_resume_ap);
    if(i4_amb_ret != AEER_OK)
    {
        DBG_ERROR(("\n get next active app failed\n"));
        return -1;
    }

    DBG_INFO((MSCVT_LOG_PREFIX" Call function : %s. next %s\n",__FUNCTION__, ps_resume_ap));

    if(strncmp(ps_resume_ap,NAV_NAME,strlen(NAV_NAME))==0 && !b_cast_wakeup)
    {
        /*_b_resumenav_frommscvt = TRUE;*/
        a_msg_convert_resume_navigator();
        _b_recv_pause_cmd = FALSE;
    }else if(strncmp(ps_resume_ap,MMP_NAME,strlen(MMP_NAME))==0)
    {
        a_tv_net_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,:resume=mmp\n");
        _mc_wait_for_resumed();
    }
    _b_recv_pause_cmd = FALSE;

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL));

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));

    if(strncmp(ps_resume_ap,MENU_NAME,strlen(MENU_NAME))!=0 && t_retail_mode != ACFG_RETAIL_MODE_NORMAL)
    {
        DBG_INFO((MSCVT_LOG_PREFIX"%s Line %d update APP_CFG_RECID_PIC_MODE \n",__FUNCTION__, __LINE__));

        a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
    }
    //sa_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);

    return AEER_OK;
}

static UINT32 ui4_g_wakeup_key = 0;

INT32 msg_convert_custom_process_msg_fct (
    HANDLE_T     h_app,
    UINT32       ui4_type,
    const VOID*  pv_msg,
    SIZE_T       z_msg_len,
    BOOL         b_paused)

{
    switch (ui4_type)
    {
        /*original code move to thread*/
        case AM_BRDCST_MSG_PRE_POWER_OFF:
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" AM_BRDCST_MSG_PRE_POWER_OFF\n"));
                a_tv_custom_reset_hotkey_parameter();
                AP_SYSTEM_CALL("kill -15 `ps -A | grep hotkey_loading | awk '{print $1;}'`");

                 a_mtktvapi_highlevel_notify_linux_world_generic(REASON_HIHGLEVEL_POWER_STATUS,0,0,0,0);

#if defined(APP_SUPPORT_STR_CORE_OFF)
                if(a_am_is_suspend_allowed())
                {
                    c_pcl_set_hotkey_active(TRUE);
                }
#endif
               if(_b_wait_for_3rd_shtdn == FALSE)
                {
                    _b_wait_for_3rd_shtdn = TRUE;
                    cmd_convert_shutdown("suspend");
                }
                break;
            }
        case AM_BRDCST_MSG_POWER_OFF:
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX" AM_BRDCST_MSG_POWER_OFF\n"));
                _b_hotkey_pressed = FALSE;
                _b_netflix_alive = FALSE;
                _b_cobalt_alive = FALSE;
                _b_amazon_alive = FALSE;
                _b_browser_ctrl_alive = FALSE;
                _g_hotkey_wakeup = FALSE;
                _b_hotkey_netflix_pressed = FALSE;
                _b_hotkey_netflix_started = FALSE;
                b_cast_wakeup = FALSE;
                ui4_g_last_key_down = 0;
                ui4_last_stoped_app = MSCVT_STOP_NONE;

                if(_b_wait_for_3rd_shtdn)
                {
                    cmd_convert_wait_shtdn_signal();
                }

                a_rest_app_unlock_launch_sema();
                b_browser_starting = FALSE;
                DBG_LOG_PRINT((MSCVT_INFO_HEADER"finish power off \n"));
            }
            break;

#ifdef APP_HOTKEY_WAKEUP_SUPPORT
        case AM_BRDCST_MSG_HOTKEY_WAKEUP:
        {
            UINT32 ui4_key_code ;

            c_memcpy(&ui4_key_code,pv_msg,4);
            _g_hotkey_wakeup = TRUE;
            _b_hotkey_pressed = TRUE;


            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"AM_BRDCST_MSG_HOTKEY_WAKEUP ui4_key_code = 0x%x\n",ui4_key_code));

            a_tv_custom_set_banner_visiable_allow(FALSE);
            if(BTN_NETFLIX == ui4_key_code)
            {
                //system("touch /tmp/netflix_hotkey_wakeup");  //dolphin
                s_touch("/tmp/netflix_hotkey_wakeup");
                _b_hotkey_netflix_pressed = TRUE;
            }

            if(BTN_WIDGET == ui4_key_code)
            {
                _b_hotkey_wdg_pressed = TRUE;
            }
            ui4_g_wakeup_key = ui4_key_code;
        }
        break;
#endif
        case AM_BRDCST_MSG_SYS_PRE_SUSPEND_EXIT:
        {
            PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
            c_pcl_get_wakeup_reason(&e_wakeup_reason,NULL);

            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"AM_BRDCST_MSG_SYS_PRE_SUSPEND_EXIT\n"));

            if (PCL_WAKE_UP_REASON_RTC != e_wakeup_reason)
            {
                if(PCL_WAKE_UP_REASON_WIFI == e_wakeup_reason ||
                   PCL_WAKE_UP_REASON_ETHERNET == e_wakeup_reason)
                {
                    b_cast_wakeup = TRUE;
                    a_tv_custom_set_banner_visiable_allow(FALSE);
                }

                a_cfg_custom_set_wake_from_suspend(TRUE);
            }
        }
            break;
        case AM_BRDCST_MSG_EXT_BGM_INACTIVE:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"Line %d, AM_BRDCST_MSG_EXT_BGM_INACTIVE\n",__LINE__));
            b_bgm_runing = FALSE;
            CMD_CONVERT_SEND_CMD_T t_send_cmd;
            t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
            t_send_cmd.s_destination = CMDCVT_MACRO_AM;
            t_send_cmd.s_ack = NULL;
            t_send_cmd.s_command = CMDCVT_MACRO_PAUSED;
            t_send_cmd.s_parameter = "bgm";
            cmd_convert_send_command(&t_send_cmd);
        }
            break;
        case AM_BRDCST_MSG_EXT_BGM_ACTIVE:
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"Line %d, AM_BRDCST_MSG_EXT_BGM_ACTIVE\n",__LINE__));
            CMD_CONVERT_SEND_CMD_T t_send_cmd;
            t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
            t_send_cmd.s_destination = CMDCVT_MACRO_AM;
            t_send_cmd.s_ack = NULL;
            t_send_cmd.s_command = CMDCVT_MACRO_RESUMED;
            t_send_cmd.s_parameter = "bgm";
            cmd_convert_send_command(&t_send_cmd);

            CMD_CONVERT_SEND_CMD_T t_send_cmd2;
            t_send_cmd2.s_source = CMDCVT_MACRO_AP_DTVCTX;
            t_send_cmd2.s_destination = CMDCVT_MACRO_AM;
            t_send_cmd2.s_ack = NULL;
            t_send_cmd2.s_command = CMDCVT_MACRO_START;
            t_send_cmd2.s_parameter = "mtk_uli";
            cmd_convert_send_command(&t_send_cmd2);
            b_bgm_runing = TRUE;
            TIME_T  t_nfx_refresh_time = a_bgm_nfx_ar_get_refresh_time();
            NFX_AR_MSG_T send_cmd={
                .msg_type=TIME_TYPE,
                .sc.t_refresh_time=t_nfx_refresh_time
            };
            a_nfx_always_refresh_process(&send_cmd);
            a_uli_agent_init_wait_NTP();
        }
            break;
        case AM_BRDCST_MSG_PRE_POWER_ON:
        {
            if(ui4_g_wakeup_key)
            {
                _msgcvt_hotkey_wakeup_from_BGM();
                CHAR s_cmd[64] = {0};
                c_sprintf(s_cmd,":dtv_app_mtk,am,:hotkey=0x%x\n",ui4_g_wakeup_key);
                a_tv_net_send_cmd(s_cmd);
                ui4_g_wakeup_key = 0;
            }

            {
                CMD_CONVERT_SEND_CMD_T t_send_cmd;

                t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
                t_send_cmd.s_destination = CMDCVT_MACRO_AM;
                t_send_cmd.s_ack = NULL;
                t_send_cmd.s_command = "wakeup";
                t_send_cmd.s_parameter = "hotkey";
                cmd_convert_send_command(&t_send_cmd);
            }
        }break;
        case AM_BRDCST_MSG_POWER_ON:
        {
            PCL_WAKE_UP_REASON_T    e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;

            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"AM_BRDCST_MSG_POWER_ON\n"));

            a_mtktvapi_highlevel_notify_linux_world_generic(REASON_HIHGLEVEL_POWER_STATUS,1,0,0,0);

            if(PCLR_OK == c_pcl_get_wakeup_reason (& e_wakeup_reason, NULL) &&
               (PCL_WAKE_UP_REASON_WIFI == e_wakeup_reason ||
               PCL_WAKE_UP_REASON_ETHERNET == e_wakeup_reason))
            {
                a_tv_custom_set_banner_visiable_allow(FALSE);
                b_cast_wakeup = TRUE;
            }

            {
                TIME_T  t_nfx_refresh_time = a_bgm_nfx_ar_get_refresh_time();
                NFX_AR_MSG_T send_cmd={
                        .msg_type=TIME_TYPE,
                        .sc.t_refresh_time=t_nfx_refresh_time
                };
                a_nfx_always_refresh_process(&send_cmd);
            }
            break;
        }
#ifdef APP_TTS_SUPPORT
        case AM_BRDCST_MSG_TTS_PLAYED:
        {
            INT32 i4_ret;
            UINT8 ui1_tts_idx = 0;
            i4_ret = a_cfg_get_tts_switch_status(&ui1_tts_idx);
            if(i4_ret == APP_CFGR_OK)
            {
                if(ui1_tts_idx == APP_CFG_TTS_SWITCH_ON)
                {
                    a_cfg_turn_on_off_audio_by_outport(FALSE);
                }
            }
            else
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"failed to get tts switch status, mute audio anyways\r\n"));
                a_cfg_turn_on_off_audio_by_outport(FALSE);
            }
            break;
        }
#endif
        default:
            break;
    }

    return AEER_OK;
}

INT32 msg_convert_custom_stats_up_notify(const CHAR* ps_app_name, UINT32 i4_status, INT32 i4_ret)
{
    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s %d] ps_app_name = >%s status=> %d i4_ret=>%d\n",__FUNCTION__,__LINE__,ps_app_name,i4_status,i4_ret));

    if(c_strcmp(ps_app_name, MSCVT_NAME)==0)
    {
        /* Ignor the app return status */
        return AEER_OK;
    }
    else if(0==c_strcmp(ps_app_name, NAV_NAME))
    {
        if(AMB_NFY_STATE_CHG_PAUSE == i4_status &&  b_cast_wakeup)
        {
            ISL_REC_T  t_current_isl_rec;
            TV_WIN_ID_T     e_focus_id;

            a_tv_get_focus_win(&e_focus_id);
            a_tv_get_isl_rec_by_win_id(e_focus_id,&t_current_isl_rec);

            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"dial wakeup should stop current svc\n"));
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"e_video_type =0x%x,nav running %d\n\r",t_current_isl_rec.t_avc_info.e_video_type,nav_is_running(e_focus_id)));
           // if(t_current_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST)
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"stop svc\n\r"));
                a_tv_stop_by_win_id(e_focus_id);//need stop the svc
            }
        }
        else if(AMB_NFY_STATE_CHG_RESUME == i4_status && 0 == i4_ret)
        {
            UINT8       ui1_inp_src_id;
            ISL_REC_T   t_isl_rec = {0};

            a_cfg_get_input_src(SN_PRES_MAIN_DISPLAY,&ui1_inp_src_id);
            a_isl_get_rec_by_id(ui1_inp_src_id, &t_isl_rec);
            b_cast_wakeup = FALSE;

            if(b_bgm_runing && DEV_VTRL_CAST != t_isl_rec.t_avc_info.e_video_type)
            {
                DBG_LOG_PRINT((MSCVT_LOG_PREFIX"b_bgm_running,resume navigator\n"));
                msg_convert_custom_resume_tv();
            }
        }
        return AEER_OK;
    }
    return msg_convert_stats_up_notify_default(ps_app_name, i4_status, i4_ret);
}

INT32 msg_convert_custom_resume_menu(VOID)
{
    INT32 i4_amb_ret = 0;

    _mc_signal_resumed();
    i4_amb_ret = a_amb_resume_app(MENU_NAME);

    return i4_amb_ret;
}

INT32 msg_convert_custom_resume_mmp(VOID)
{
    INT32 i4_amb_ret = MSCVT_OK;

    _mc_signal_resumed();
    a_amb_clean_stack();
    a_icl_custom_set_nw_widget_status(ICL_CUSTOM_NW_WIDGET_APP, NW_APP_STATUS_HIDE);
    a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);
    i4_amb_ret = a_amb_resume_app(MMP_NAME);

    return i4_amb_ret;
}

INT32 msg_convert_custom_resume_tv(VOID)
{
    _b_recv_pause_cmd = TRUE;
    msg_convert_custom_resume_navigator();
    _mc_custom_dtv_start_svc();
    _b_recv_pause_cmd =FALSE;
    return MSCVT_OK;
}

#ifdef APP_WFD_SUPPORT
INT32 msg_convert_custom_resume_wfd(VOID)
{
    INT32 i4_amb_ret = 0;
    _mc_signal_resumed();
    _b_recv_pause_cmd = TRUE;
    i4_amb_ret = a_amb_resume_app(WFD_NAME);
    return i4_amb_ret;
}
#endif

INT32 msg_convert_custom_pause_tv(VOID)
{
    NAV_3RD_PARTY_RUNNING_INFO_T  t_info;
    INT32 i4_amb_ret = 0;
    char ps_resume_ap[APP_NAME_MAX_LEN+1];

    /* Notify navigator, it has no video. */
    c_memset (&t_info, 0, sizeof(NAV_3RD_PARTY_RUNNING_INFO_T));
    t_info.e_running_mode = NAV_3RD_PARTY_RUNNING_MODE_WITH_VIDEO;
    a_nav_inform_3rd_app_begin_info (&t_info);
    a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_RESUMED);

    i4_amb_ret = a_am_get_active_app(ps_resume_ap);
    if(i4_amb_ret != AEER_OK)
    {
        DBG_ERROR(("\n get next active app failed\n"));
        return i4_amb_ret;
    }

    if(strncmp(ps_resume_ap,MSCVT_NAME,strlen(MSCVT_NAME))==0)
    {
        _mc_custom_dtv_stop_svc();
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = CMDCVT_MACRO_PAUSED;
        t_send_cmd.s_parameter = CMDCVT_MACRO_DTV;
        cmd_convert_send_command(&t_send_cmd);
    }
    else
    {
        i4_amb_ret = a_amb_resume_app(MSCVT_NAME);
    }
    return i4_amb_ret;
}

static BOOL _mc_custom_check_current_is_mmp_source()
{
    INT32       i4_ret              = 0;
    ISL_REC_T   t_isl_rec           = {0};
    CHAR        s_disp_name[16+1]   = {0};
    UINT8       ui1_crnt_input_src  = 0;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    if(ISLR_OK != i4_ret)
    {
        DBG_INFO(("a_cfg_av_get_disp_name fail:%d \n", i4_ret));
        return FALSE;
    }

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
    if(ISLR_OK != i4_ret)
    {
        DBG_INFO(("a_cfg_av_get_input_src fail:%d \n", i4_ret));
        return FALSE;
    }

    i4_ret = a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);
    if(ISLR_OK != i4_ret)
    {
        DBG_INFO(("a_isl_get_rec_by_id fail:%d \n", i4_ret));
        return FALSE;
    }

    DBG_INFO(("t_isl_rec.t_avc_info.e_video_type: 0x%x \n", t_isl_rec.t_avc_info.e_video_type));
    if(DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type ||
       DEV_VTRL_MMP_PHOTO == t_isl_rec.t_avc_info.e_video_type ||
       DEV_VTRL_MMP_AUDIO == t_isl_rec.t_avc_info.e_video_type ||
       DEV_VTRL_MMP_VIDEO == t_isl_rec.t_avc_info.e_video_type)
    {
        return TRUE;
    }

    return FALSE;
}

VOID msg_convert_custom_stop_native()
{
    if (_b_netflix_alive)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"backgm netflix \n"));
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AM;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = "backgm";
        t_send_cmd.s_parameter = CMDCVT_MACRO_3RD_NETFLIX;
        cmd_convert_send_command(&t_send_cmd);
    }
    else if (_b_amazon_alive)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"stop amazon \n"));
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AM;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = CMDCVT_MACRO_STOP;
        t_send_cmd.s_parameter = CMDCVT_MACRO_3RD_AMAZON_IGNITION;
        cmd_convert_send_command(&t_send_cmd);
    }
    else if (_b_cobalt_alive)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"stop youtube \n"));
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AM;
        t_send_cmd.s_destination = "Cobalt YTTV";
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = CMDCVT_MACRO_STOP;
        t_send_cmd.s_parameter = "Cobalt YTTV";
        cmd_convert_send_command(&t_send_cmd);
    }
    else
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX"other app \n"));
    }
}

VOID msg_convert_custom_resume_nav()
{
    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"resume navigator\n"));
    CMD_CONVERT_SEND_CMD_T t_send_cmd;
    t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
    t_send_cmd.s_destination = CMDCVT_MACRO_AP_DTVCTX;
    t_send_cmd.s_ack = NULL;
    t_send_cmd.s_command = CMDCVT_MACRO_RESUME;
    t_send_cmd.s_parameter = CMDCVT_MACRO_NAV;
    cmd_convert_send_command(&t_send_cmd);
}


INT32 msg_convert_custom_resume_navigator(VOID)
{
    ACFG_RETAIL_MODE_T          t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

    DBG_LOG_PRINT((MSCVT_LOG_PREFIX" resume navigator recv:%s \n",_b_recv_pause_cmd?"TRUE":"FALSE"));

    if(!_b_recv_pause_cmd)
    {
        DBG_INFO(("send resume=navigator  \n"));
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = CMDCVT_MACRO_RESUME;
        t_send_cmd.s_parameter = CMDCVT_MACRO_NAV;
        cmd_convert_send_command(&t_send_cmd);

        _mc_wait_for_resumed();
    }
    else
    {
        _mc_signal_resumed();
        if(FALSE == _mc_custom_check_current_is_mmp_source())
        {
            a_amb_resume_app(NAV_NAME);
        }
        else
        {
            DBG_ERROR(("Not resume navigator in USB source\n"));
#ifdef APP_MENU_MMP_COEXIST
#ifdef APP_MMP_SUPPORT
        if (a_mmp_get_ap_status() == MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC)
        {
             a_amb_resume_app(MMP_NAME);
        }
#endif
#endif
        }
    }

    a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED);

    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (t_retail_mode != ACFG_RETAIL_MODE_NORMAL)
    {
        a_cfg_av_set_condition(APP_CFG_AV_COND_MASK_MMP, FALSE);
    }

    return MSCVT_OK;
}


INT32 msg_convert_custom_resume_webapp(VOID)
{
    return MSCVT_OK;
}
INT32 msg_convert_custom_pause_webapp(VOID)
{
    return MSCVT_OK;
}

INT32 msg_convert_custom_pause_navigator(VOID)
{
    INT32 i4_amb_ret = 0;
    char ps_resume_ap[APP_NAME_MAX_LEN+1] = {0};

    i4_amb_ret = a_am_get_active_app(ps_resume_ap);

    if(strncmp(ps_resume_ap,MSCVT_NAME,strlen(MSCVT_NAME))==0)
    {
        CMD_CONVERT_SEND_CMD_T t_send_cmd;
        t_send_cmd.s_source = CMDCVT_MACRO_AP_DTVCTX;
        t_send_cmd.s_destination = CMDCVT_MACRO_AM;
        t_send_cmd.s_ack = NULL;
        t_send_cmd.s_command = CMDCVT_MACRO_PAUSED;
        t_send_cmd.s_parameter = CMDCVT_MACRO_NAV;
        cmd_convert_send_command(&t_send_cmd);
    }
    else
    {
        i4_amb_ret = a_amb_resume_app(MSCVT_NAME);
    }

    return i4_amb_ret;
}

INT32 msg_convert_custom_resume_wzd(VOID)
{
    a_tv_net_send_cmd("\n:dtv_app_mtk,am,:resumed=wizard\n");
    return 0;
}

INT32 msg_convert_custom_resume_tv_sidebar(VOID)
{
    a_tv_net_send_cmd("\n:dtv_app_mtk,dtv_app_mtk,sidebar:resume=menu\n");
    return MSCVT_OK;
}

BOOL a_msg_convert_visible_check(CHAR* ps_visible_check_name)
{
    NAV_COMP_SET_T   t_nav_comp_set = 0;
    BOOL  b_return = TRUE; /*allow*/
    CHAR  s_active_name [APP_NAME_MAX_LEN+1];

    a_nav_get_comp_visibility (&t_nav_comp_set);

    a_am_get_active_app (s_active_name);

    if (c_strcmp(ps_visible_check_name, "nav_yahoo") == 0)
    {
        /* Current application is not navigator, always return FALSE */
        if (c_strcmp(s_active_name, "navigator") != 0)
        {
            b_return = FALSE; /* disallow */
        }
        else if ( t_nav_comp_set > 0 )  /* some component is visible. */
        {
            b_return = FALSE; /* disallow */
        }
    }

    DBG_INFO(("<><>Check for visible set: %s is %s\n", ps_visible_check_name, b_return?"YES":"NO"));
    return b_return;
}

INT32 msg_convert_custom_stop_3rd(VOID)
{
    return MSCVT_OK;
}
BOOL msg_convert_custom_netflix_active(VOID)
{
    return (_b_netflix_alive || _b_amazon_alive);
}
BOOL msg_convert_custom_airplay_active(VOID)
{
    return b_browser_airplay_started;
}
BOOL msg_convert_custom_appletv_plus_active(VOID)
{
    return _b_appletv_alive;
}
BOOL msg_convert_custom_hbomax_active(VOID)
{
    return _b_hbomax_alive;
}

BOOL msg_convert_custom_castcore_active(VOID)
{
    return _b_castcore_alive;
}

BOOL msg_convert_custom_browser_ctrl_active(VOID)
{
    return _b_browser_ctrl_alive;
}
BOOL msg_convert_custom_cobalt_alive(VOID)
{
    return _b_cobalt_alive;
}

BOOL msg_convert_custom_amazon_alive(VOID)
{
    return _b_amazon_alive;
}

#ifdef BRAND_V
INT32 msg_convert_custom_resume_tv_signal(VOID)
{
    //do noting on turnkey
    return MSCVT_OK;
}

VOID msg_convert_custom_show_dtv_osd(VOID)
{
    //do noting on turnkey
}

VOID msg_convert_custom_hide_dtv_osd(VOID)
{
    //do noting on turnkey
}

BOOL msg_convert_custom_is_yahoo_started(VOID)
{
    return TRUE;
}

BOOL msg_convert_custom_is_yahoo_ready(VOID)
{
    return TRUE;
}
#endif

BOOL msg_convert_custom_hotkey_netflix_need_recheck_hide_logo(VOID)
{
    return (!_b_hotkey_netflix_started)&&_b_hotkey_netflix_pressed;//For netflix hotkey wakeup,need check netflix is started then hide the logo
}

BOOL a_msg_convert_custom_wait_3rd_app_stop()
{
    return b_wait_power_off;
}

extern int _rest_app_no_app_notification();

BOOL a_msg_convert_custom_stop(BOOL b_wait_for_power_off)
{
    ISL_REC_T   t_isl_rec           = {0};
    CHAR        s_disp_name[16+1]   = {0};
    UINT8       ui1_crnt_input_src  = 0;
    CHAR        sz_active_app[32]   = {0};

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
    a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);

    a_am_get_active_app(sz_active_app);
    if(strcmp(sz_active_app,MENU_NAME) == 0)
    {
        a_amb_pause_app(MENU_NAME);
    }

    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s %d]browser_ctrl_active = %d,b_browser_airplay_started = %d,e_src_type = 0x%x,e_video_type = 0x%x,b_wait_for_power_off = %d\n",
                   __FUNCTION__,__LINE__,
                   _b_browser_ctrl_alive,b_browser_airplay_started,
                   t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type,b_wait_for_power_off));

    if(_b_browser_ctrl_alive || b_browser_airplay_started || _b_amazon_alive || _b_cobalt_alive || _b_netflix_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive )
    {
        if(b_wait_for_power_off)
            b_wait_power_off = TRUE;

        if(_b_amazon_alive || _b_cobalt_alive || _b_netflix_alive || _b_appletv_alive || _b_hbomax_alive || _b_castcore_alive)
        {
            DBG_LOG_PRINT((MSCVT_LOG_PREFIX"CSP app lanuching\n"));
            msg_convert_custom_resume_nav();
        }
        else if(_b_browser_ctrl_alive || b_browser_airplay_started)
        {
            UINT8  ui1_inp_src_id = 0;

            AP_SYSTEM_CALL("echo \"reasonBreakIn\ncast\" > /tmp/airplay_fg_reason");

            a_cfg_get_input_src(SN_PRES_MAIN_DISPLAY,&ui1_inp_src_id);

            a_cfg_set_last_input_src (SN_PRES_MAIN_DISPLAY, ui1_inp_src_id);
            MSCVT_CUST_LOG_ON_FAIL(a_c4tv_apron_stop_current_app());
            _rest_app_no_app_notification();
        }
    }

    if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV || t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        _mc_custom_dtv_stop_svc();
    }
    else if((INP_SRC_TYPE_VTRL == t_isl_rec.e_src_type && DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type) || INP_SRC_TYPE_MM == t_isl_rec.e_src_type)
    {
        //a_amb_pause_app(MMP_NAME);
        _msg_convert_chg_input_src_to_cast();
    }

    b_wait_power_off = FALSE;
    return TRUE;
}

VOID msg_convert_custom_interrupt_off_rs(BOOL b_interrupt_off_rs)
{
    _b_oled_interrupt_off_rs = b_interrupt_off_rs;
}

extern BOOL menu_custom_is_blank_screen(VOID);

BOOL msg_convert_custom_power_off_cb_fct(AMB_NFY_REASON_T e_reason)
{
    if(a_is_oled_compensation_support())
    {
         UINT8    ui1_exit_code = 0;

         a_cfg_custom_get_oled_status(&ui1_exit_code);
         if(ui1_exit_code > 0)/* skip if screen refresh  */
         {
            return TRUE;
         }
         if(_b_oled_interrupt_off_rs)
         {
             _b_oled_interrupt_off_rs = FALSE;

             DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s %d] _b_oled_interrupt_off_rs\n",__FUNCTION__,__LINE__));

             return TRUE;
         }
    }

    if(menu_custom_is_blank_screen()) /* skip if current is blank screen */
    {
        return TRUE;
    }

    DBG_LOG_PRINT((MSCVT_LOG_PREFIX"[%s %d] a_cfg_cust_is_off_rs_enable() = %d\n",__FUNCTION__,__LINE__,a_cfg_cust_is_off_rs_enable()));

    a_cfg_cust_audio_mute(TRUE);
    if(!a_cfg_cust_is_off_rs_enable())
    {
        a_cfg_cust_backlight_onoff(FALSE);
        a_cfg_cust_panel_onoff(FALSE);
    }

    return a_msg_convert_custom_stop(a_cfg_cust_is_off_rs_enable() ? FALSE : TRUE);
}

BOOL msg_convert_is_ready_to_show_logo()
{
    return access("/tmp/dtv_svc_is_ready", 0) == 0 && TRUE == a_nav_is_init_ready() && b_netflix_inited;
}

BOOL msg_convert_custom_system_ui_showing(VOID)
{
    return _b_system_ui_showing;
}

#ifdef APP_REGISTRY_SUPPORT
VOID msg_convert_custom_sytem_ui_state_cb_fct(REG_UI_STATE e_state)
{
    if(REG_UI_STATE_VISIBLE == e_state)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" System UI State is Visible.\n"));

        _b_system_ui_showing = TRUE;
        nav_request_context_switch(_msg_convert_handle_sys_ui_show, NULL, NULL, NULL);

    }else if(REG_UI_STATE_INVISIBLE == e_state)
    {
        DBG_LOG_PRINT((MSCVT_LOG_PREFIX" System UI State is NOT visible.\n"));

        _b_system_ui_showing = FALSE;
        nav_request_context_switch(_msg_convert_handle_sys_ui_hide, NULL, NULL, NULL);
    }
}
#endif
