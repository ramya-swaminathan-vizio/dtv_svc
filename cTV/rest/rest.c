/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <semaphore.h>

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
#include "c_pcl.h"
#include "x_os.h"

#include "amb/a_amb.h"
#include "am/a_am.h"
#include "app_util/a_cfg.h"
#include "app_util/a_common.h"
#include "app_util/a_network.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "app_util/rmv_dev/a_rmv_evt.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/input_src/a_input_src.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "wizard_anim/a_wzd.h"
#include "nav/updater/nav_updater.h"
#include "res/menu2/menu_custom.h"

#include "a_jsonrpc.h"
#include "c_httpc_api.h"

#include "rest.h"
#include "a_rest.h"
#include "rest_dbg_level.h"
#include "rest_cmd.h"
#include "rest_ipc.h"
#include "rest_network.h"
#include "rest_ipc_handler.h"
#include "a_rest_event.h"
#include "netflix_pre_app.h"
#include "mtosd.h"
#include "rest_system.h"
#include "mdns/a_mdns.h"
#include "rest/tv/tv_settings/a_picture_ex.h"

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define TIMER_READY_TO_CAST_INTERVAL (18000)
#define ULI_UPDATE_TIME_JSON "/data/uli/check_update.json"

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static BOOL         b_g_is_init = FALSE;
static HANDLE_T     h_rest_app = NULL_HANDLE;

#ifdef SYS_VSSP_REST_SERVER_DEBUG
UINT16       ui2_g_rest_dbg_level = 7;
#else
UINT16       ui2_g_rest_dbg_level = DBG_LEVEL_ERROR;
#endif

static CHAR         s_rest_prefix[] = "REST_APP";
static CHAR         s_rest_cred[REST_CRED_LEN+1];
static CHAR         s_rest_session_token[REST_SESSION_TOKEN_LEN+1];
//static BOOL         b_cast_shell_ready = FALSE;
static UINT8        ui1_ready_count = 0;    // this is only for handling power on case
static BOOL         b_connection_status = FALSE;
static BOOL         b_input_name_status = TRUE; // save the 2nd parameter when system/input/name is received. (MVV-12076) set default to TRUE
static INT32        i4_hotkey_wakeup = 0;
static HANDLE_T     h_g_httpc_handle = NULL_HANDLE;
//static INT32        airPlay_Enable_Status = 0;
static BOOL        i4_AC_power = TRUE;
static INT16 _i2_init_volume_value = 0; //dolphin add 20200519 for get the volume when power on

/* send input notify need to wait for python ready */
static UINT8    ui1_g_rest_ready_count_input_list = 0;
static UINT8    ui1_g_rest_ready_count_input_enable_airplay = 0;
static HANDLE_T h_rest_ready_timer_input_list = NULL_HANDLE;
static HANDLE_T h_rest_ready_timer_input_enable_airplay = NULL_HANDLE;
#define REST_CHECK_READY_TIMER      (1000)        /* 1 s */
static BOOL        b_has_sent_notify_input_list_while_python_ready = FALSE;


int power_status = 0; // eco off: 2 ,quick-start off: 0, on: 1.
INT32 g_i4_cast_state = (INT32)C4TV_APRON_CAST_STATE_Unknown;
BOOL        i4_hotkey_sch_wakeup = FALSE;

static HANDLE_T     h_timer_ready_to_cast = NULL_HANDLE;
HANDLE_T     h_timer_avoid_backdrop = NULL_HANDLE;
HANDLE_T     h_timer_flash_led = NULL_HANDLE;
HANDLE_T     h_timer_binary_update = NULL_HANDLE;
HANDLE_T     h_timer_create_vtrl_ipt = NULL_HANDLE;
HANDLE_T     h_timer_disable_airplay = NULL_HANDLE;
HANDLE_T     h_timer_airplay_launch = NULL_HANDLE;
HANDLE_T     h_timer_oobe_sch_launch = NULL_HANDLE;
HANDLE_T     h_timer_toast_nav = NULL_HANDLE;  //dolphin add 20200609

HANDLE_T     h_check_amazon_thread = NULL_HANDLE;
INT32     i4_second_check_cert = 0;
HANDLE_T     h_timer_check_homekit_power_status = NULL_HANDLE;

static UINT16 ui2_send_msg_fail_count = 0;
sem_t  t_airplay_lock; //dolphin sem
sem_t  t_install_script_lock;// dolphin add 20200319

extern uint32_t  ui4_rest_log_level;
extern INT32 rest_cli_attach_cmd_tbl(VOID);
extern int _rest_app_receiving_hotkeys(int keycode, bool b_check_power_state);
extern int _rest_app_receiving_hotkeys_force(int keycode, bool b_check_power_state);
extern int _rest_app_launch_app_by_keycode(int keycode, int reason);
extern int app_thread_run_launch_app_by_keycode(int keycode, int reason);
extern int _rest_app_launch_virtual_input(const char* cname);
//extern int _rest_app_launch_sc_home();
extern INT32 chg_inp_src(INP_SRC_TYPE_T e_src_type, DEVICE_TYPE_T e_video_type, UINT8 ui1_internal_id);
extern int _rest_app_no_app_notification();
extern int _rest_app_set_keycode_luanch_input(int keycode);
extern bool test_connection_status();
extern int _rest_app_create_virtual_inputs();
extern void homekit_factory_reset();
extern VOID _rest_system_update_binary_expired_timer_cb(HANDLE_T h_timer, VOID* pv_tag);
extern bool _rest_app_is_create_vtrl_ipts_ok();
extern int picture_acfg_notify_init(void);

/*-----------------------------------------------------------------------------
 * Name: rest_get_dbg_level
 *
 * Description: This API returns the current setting of debug level.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: The current setting of debug level.
 ----------------------------------------------------------------------------*/
UINT16 rest_get_dbg_level(VOID)
{
    return ui2_g_rest_dbg_level;
}

/*-----------------------------------------------------------------------------
 * Name: rest_set_dbg_level
 *
 * Description: This API set the debug level.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: The current setting of debug level.
 ----------------------------------------------------------------------------*/
VOID rest_set_dbg_level(
                    UINT16                      ui2_dbg_level
                    )
{
    ui2_g_rest_dbg_level = ui2_dbg_level;
    ui4_rest_log_level = (UINT32)ui2_dbg_level;
}

VOID rest_set_default_debug_level()
{
    DBG_INFO(("[REST_AP_API][%s] rest_set_default_debug_level.\r\n",__FUNCTION__));
    if (access(REST_DEBUG_FLAG, F_OK) != -1) {
        DBG_INFO(("[REST_AP_API][%s] debug flag set.\r\n",__FUNCTION__));
        rest_set_dbg_level(7);
        return;
    }
    return;
}

/*-----------------------------------------------------------------------------
 * Name: rest_get_log_prefix
 *
 * Description: This API returns the rest log prefix.
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns: the menu_dtmb log prefix.
 ----------------------------------------------------------------------------*/
CHAR* rest_get_log_prefix(VOID)
{
    return s_rest_prefix;
}
#if 0
BOOL _rest_is_cast_shell_ready()
{
    return b_cast_shell_ready;
}
#endif
static INT32 rest_obtain_session_token_for_local_host ()
{
    INT32 i4_ret = 0;
    INT32 i4_retry_count = 0;
    FILE* f_input_fd;
    INT32 i4_buf_size = REST_SESSION_TOKEN_LEN+1;
    CHAR buffer[i4_buf_size];
    c_memset(buffer, '\0', i4_buf_size);

    DBG_INFO(("<rest> rest_obtain_session_token_for_local_host\n\r"));

    while(1) {
        f_input_fd = fopen ("/tmp/cred.dat", "r");
        if (f_input_fd == NULL) {
            if (i4_retry_count > 50) {
                DBG_WARN(("<rest> err: meet retry count max\n\r"));
                //fclose (f_input_fd);
                return 2;
            }
            DBG_INFO(("<rest> open /tmp/cred.dat failed, retry %d\n\r", i4_retry_count));
            sleep(1);
            i4_retry_count++;
        } else {
            break;
        }
    }

    if (fgets(buffer, i4_buf_size, f_input_fd) != NULL)
    {
        char *pos;
        if ((pos = c_strchr(buffer, '\n')) != NULL) {
            *pos = '\0';
        }
        DBG_INFO(("<rest> cred buffer:%s, strlen(buffer)=%d.\n\r", buffer, c_strlen(buffer)));
        DBG_INFO(("<rest> original remembered s_rest_cred:%s, strlen(s_rest_cred)=%d.\n\r", s_rest_cred, c_strlen(s_rest_cred)));

        if (c_strlen(buffer)!=0 && c_strlen(s_rest_cred)!=0 && c_strcmp(buffer, s_rest_cred)==0)
        {
            DBG_WARN(("<rest> cred same as previously saved. needless to obtain again\n\r"));
            fclose (f_input_fd);
            return 0;
        }
        fclose (f_input_fd);

        c_memset(s_rest_cred, '\0', REST_CRED_LEN+1);
        c_strncpy(s_rest_cred, buffer, REST_CRED_LEN);
        DBG_INFO(("<rest> new s_rest_cred:%s, strlen(buffer)=%d.\n\r", s_rest_cred, c_strlen(s_rest_cred)));

        if (rest_ask_session() == 0) {
            i4_ret = _rest_rewrite_static_index_html();
        } else {
            i4_ret = -1;
        }
    }
    else
    {
        DBG_LOG_PRINT(("<rest> err: get null\n\r"));
        fclose (f_input_fd);
        i4_ret = -1;
    }

    return i4_ret;
}

BOOL rest_get_session_token(CHAR* s_buffer, UINT16 ui2_size)
{
    DBG_INFO(("[REST_AP_API][%s] original s_rest_session_token: %s.\r\n",__FUNCTION__, s_rest_session_token));

    if (c_strlen(s_rest_session_token) == 0 || ui2_size <= c_strlen(s_rest_session_token)) {
        // try to get session token again
        //if (rest_obtain_session_token_for_local_host() != 0)
        {
            DBG_ERROR(("[REST_AP_API][%s] rest_obtain_session_token_for_local_host error\r\n",__FUNCTION__));
            return FALSE;
        }
    }
    c_strncpy(s_buffer, s_rest_session_token, c_strlen(s_rest_session_token));

    return TRUE;
}


/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

INT32 rest_parse_config_file_to_get_app_table ()
{
    //REST_CONFIG_FILE
    if (access(REST_CONFIG_FILE_UPDATE, F_OK) != -1) {
        DBG_INFO(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_UPDATE));
        return _json_parse_config_file(REST_CONFIG_FILE_UPDATE, TRUE);
    } else if (access(REST_CONFIG_FILE_DEFAULT_DEBUG, F_OK) != -1) {
        DBG_INFO(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT_DEBUG));
        return _json_parse_config_file(REST_CONFIG_FILE_DEFAULT_DEBUG, TRUE);
    } else {
        DBG_INFO(("[REST_AP_API][%s] update file not existed. parse default one: %s\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT));
        return _json_parse_config_file(REST_CONFIG_FILE_DEFAULT, TRUE);
    }
}

static INT32 _rest_ask_session (
    HANDLE_T    h_handle,
    CHAR*       ps_cred,
    CHAR*       ps_session_token,
    UINT16      ui2_token_size)
{
    HTTPC_DATA_T    t_data;
    int             ret = 0;
    int             retry_count = 0;
    char uri[256] = "http://127.0.0.1:7346/pairing/getSessionAuthToken?CRED=";

    if (NULL == ps_cred || c_strlen(ps_cred) == 0)
    {
        DBG_INFO(("[REST_AP_API][%s] ps_cred is empty.\r\n",__FUNCTION__));
        return RESTR_INV_ARG;
    }
    if (NULL == ps_session_token || 0 == ui2_token_size)
    {
        DBG_INFO(("[REST_AP_API][%s] ps_session_token is empty.\r\n",__FUNCTION__));
        return RESTR_INV_ARG;
    }
    if (NULL_HANDLE == h_handle)
    {
        DBG_INFO(("[REST_AP_API][%s] h_g_httpc_handle is NULL_HANDLE!!\r\n",__FUNCTION__));
        return RESTR_FAIL;
    }

    c_strncat(uri, ps_cred, c_strlen(ps_cred));
    DBG_INFO(("[REST_AP_API][%s] uri = %s, h_handle = %x.\r\n",__FUNCTION__, uri, h_handle));

    c_httpc_data_init(&t_data);

    while (1)
    {
        if (retry_count >= 20)
        {
            DBG_ERROR(("[REST_AP_API][%s] c_httpc_get error max, h_handle = %x\r\n", __FUNCTION__, h_handle));
            c_httpc_data_free(&t_data);
            return -1;
        }
        ret = c_httpc_get(h_handle, uri, &t_data);
        retry_count ++;
        if (ret != HTTPR_OK)
        {
            DBG_ERROR(("[REST_AP_API][%s] c_httpc_get error, ret = %d, h_handle = %x\r\n",__FUNCTION__, ret, h_handle));
            sleep(1);
        }
        else
        {
            DBG_INFO(("[REST_AP_API][%s] c_httpc_get, len=%d, pac_data=%s, h_handle = %x\r\n", __FUNCTION__, t_data.ui4_len, t_data.pac_data, h_handle));
            if (c_strstr(t_data.pac_data, "SESSION") != NULL)
            {
                DBG_INFO(("[REST_AP_API][%s] There is SESSION, h_handle = %x\r\n",__FUNCTION__, h_handle));
                break;
            } else {
                DBG_INFO(("[REST_AP_API][%s] There is no SESSION, h_handle = %x\r\n",__FUNCTION__, h_handle));
                sleep(1);
            }
        }
    }
    c_memset(ps_session_token, '\0', ui2_token_size);
    ret = json_parse_session_token(t_data.pac_data, ui2_token_size-1, ps_session_token);
    DBG_INFO(("[REST_AP_API][%s] s_rest_session_token = %s, h_handle = %x\r\n",__FUNCTION__, ps_session_token, h_handle));

    c_httpc_data_free(&t_data);

    return RESTR_OK;
}

INT32 rest_ask_session ()
{
    return _rest_ask_session(h_g_httpc_handle, s_rest_cred, s_rest_session_token, sizeof(s_rest_session_token));
}

INT32 a_rest_ask_session (CHAR* ps_cred, CHAR* ps_session_token, UINT16 ui2_token_size)
{
#if 1
    return 0;
#else
    HANDLE_T    h_httpc_handle = NULL_HANDLE;
    INT32       i4_ret = RESTR_OK;

    i4_ret = c_httpc_new_session(&h_httpc_handle);
    if (HTTPR_OK != i4_ret) {
        DBG_ERROR(("[REST_AP_API][%s] FATAL: c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, i4_ret));
        return RESTR_FAIL;
    }
    i4_ret = _rest_ask_session(h_httpc_handle, ps_cred, ps_session_token, ui2_token_size);
    if (RESTR_OK != i4_ret) {
        DBG_ERROR(("[REST_AP_API][%s] FATAL: _rest_ask_session error, ret = %d\r\n", __FUNCTION__, i4_ret));
    }
    if (NULL_HANDLE != h_httpc_handle)
    {
        c_httpc_free_session(h_httpc_handle);
    }

    return i4_ret;
#endif
}

static VOID _rest_create_path_if_not_existed (CHAR* path)
{
    DIR* dir = NULL;
    dir = opendir("path");
    if (dir) {
        /* Directory exists. */
        DBG_INFO(("[REST_AP_API][%s] %s existed\r\n",__FUNCTION__, path));
        closedir(dir);
    } else {
        /* Directory does not exist. */
        DBG_INFO(("[REST_AP_API][%s] create %s\r\n",__FUNCTION__, path));
        mkdir(path, 0700);
    }
    return;
}

static INT32 _rest_trigger_python (HANDLE_T h_handle)
{
    HTTPC_DATA_T    t_data;
    int             ret = 0;
    int             retry_count = 0;
    char uri[256] = "http://127.0.0.1:7346/restinit";

    if (NULL_HANDLE == h_handle)
    {
        DBG_INFO(("[REST_AP_API][%s] h_g_httpc_handle is NULL_HANDLE!!\r\n",__FUNCTION__));
        return RESTR_FAIL;
    }
    DBG_INFO(("[REST_AP_API][%s] uri = %s, h_handle = %x.\r\n",__FUNCTION__, uri, h_handle));

    // create necessary path
    _rest_create_path_if_not_existed("/3rd_rw/sc-data/config");
    _rest_create_path_if_not_existed("/3rd_rw/sc-data/tmp");

    c_httpc_data_init(&t_data);
    while (1)
    {
        DBG_INFO(("[REST_AP_API][%s] sending restinit %d\r\n", __FUNCTION__, retry_count));
        if (retry_count >= 20)
        {
            DBG_ERROR(("[REST_AP_API][%s] c_httpc_get error(%d) max \r\n", __FUNCTION__,ret));
            c_httpc_data_free(&t_data);
            return -1;
        }
        ret = c_httpc_get(h_handle, uri, &t_data);
        retry_count ++;
        if (ret != HTTPR_OK)
        {
            //DBG_ERROR(("[REST_AP_API][%s] c_httpc_get error, ret = %d\r\n",__FUNCTION__, ret));
            sleep(1);
        }
        else
        {
            DBG_INFO(("[REST_AP_API][%s] c_httpc_get, len=%d, pac_data=%s\r\n", __FUNCTION__, t_data.ui4_len, t_data.pac_data));
            if (c_strstr(t_data.pac_data, "503") != NULL) {
                DBG_INFO(("[REST_AP_API][%s] 503 error\r\n",__FUNCTION__));
                sleep(2);
            } else if (c_strstr(t_data.pac_data, "500") != NULL) {
                DBG_INFO(("[REST_AP_API][%s] 500 error\r\n",__FUNCTION__));
                if (retry_count >= 10) {
                    break;
                }
                if (retry_count < 10) {
                    retry_count = 10;
                }
                sleep(2);
            } else {
                DBG_INFO(("[REST_AP_API][%s] There is no SESSION\r\n",__FUNCTION__));
                break;
            }
        }
    }

    c_httpc_data_free(&t_data);

    return RESTR_OK;
}

static VOID _rest_async_init (
    VOID*    pv_arg)
{
    UINT8    ui1_count = 0;
    INT32    i4_ret;

    DBG_INFO(("<rest> Enter _rest_async_init()\n\r"));

    i4_ret = _json_parse_ssdp_udn_file("/data/chrome/.eureka.conf", "/data/ssdp.udn");
    if (i4_ret == 0)
    {
        rest_app_restart_dial();
    }

    while(1)
    {
        ui1_count ++;
        i4_ret = rest_parse_config_file_to_get_app_table();
        if (i4_ret == 0)
        {
            DBG_INFO(("<rest> Parse config file done\r\n"));
            break;
        }
        if (ui1_count > 10)
        {
            ui1_count = 0;
            return;
        }
        sleep(1);
    }

#if 1

    i4_ret = _rest_app_create_virtual_inputs();
    DBG_INFO(("<rest> creating virtual input i4_ret = %d\n\r", i4_ret));
#endif

    i4_ret = _rest_trigger_python(h_g_httpc_handle);
    DBG_INFO(("<rest> _rest_trigger_python ret: %d\n\r", i4_ret));

    i4_ret = rest_obtain_session_token_for_local_host();
    REST_LOG_ON_FAIL(i4_ret);

    //system("touch /tmp/restap_ready");
    s_touch("/tmp/restap_ready");
#ifdef VIZIO_FUSION_SUPPORT
    pre_app_init();
#endif
    return;
}

/*
INT32 _rest_cmd_cli_launch_by_keycode(INT32 key_code)
{
    return _rest_app_receiving_hotkeys(key_code);
}
*/
INT32 _rest_rewrite_static_index_html ()
{
    /*
    <!DOCTYPE html>
    <html>
    <head>
    </head>
    <body>
    <script src="jquery-3.1.1.min.js"></script>
    <script src="script.js" SESSION="..."></script>
    </body>
    </html>
    */

    CHAR s_webpage[1024] = {'\0'};
    //CHAR s_session_token[24] = {'\0'};

    c_strcat (s_webpage, "<!DOCTYPE html>\n<html>\n<head>\n</head>\n<body>\n<script src=\"jquery-3.1.1.min.js\"></script>\n<script src=\"script.js\"");
    if (c_strlen(s_rest_session_token) != 0)
    {
        c_strcat (s_webpage, " SESSION=\"");
        c_strcat (s_webpage, s_rest_session_token);
        c_strcat (s_webpage, "\"");
    }
    c_strcat (s_webpage, "></script>\n</body>\n</html>\n");

    DBG_INFO(("-----webpage-----\n\r"));
    DBG_INFO(("%s", s_webpage));
    DBG_INFO(("\n\r-----webpage-----\n\r"));
    DBG_INFO(("len(s_webpage)=%d\n\r", c_strlen(s_webpage)));

    FILE* f_input_fd;
    //"w": Create an empty file for output operations. If a file with the same name already exists, its contents are discarded and the file is treated as a new empty file
    f_input_fd = fopen (REST_STATIC_INDEX_HTML, "w");
    if (f_input_fd != NULL) {
        fprintf (f_input_fd, "%s", s_webpage);
        fclose (f_input_fd);
        DBG_INFO(("<rest> end writing index.html\n\r"));
    } else {
        DBG_INFO(("<rest> error open file\n\r"));
        return -1;
    }

    return 0;
}

VOID _rest_app_set_connection_status(BOOL b_status)
{
    if (b_status) {
        b_connection_status = TRUE;
        DBG_INFO(("<rest> set b_connection_status to true\n\r"));
        //c_dbg_dump_stack();
    } else {
        b_connection_status = FALSE;
        DBG_INFO(("<rest> set b_connection_status to false\n\r"));
    }
    return;
}

BOOL _rest_app_get_connection_status(VOID)
{
    if (b_connection_status == TRUE) {
        DBG_INFO(("<rest> _rest_app_get_connection_status return true\n\r"));
        return TRUE;
    } else {
        DBG_INFO(("<rest> _rest_app_get_connection_status return false\n\r"));
        return FALSE;
    }
}

VOID _rest_app_set_input_name_status(BOOL b_status)
{
    if (b_status) {
        b_input_name_status = TRUE; // rest_event_notify("system/input/name", 1, "xxx")
        DBG_INFO(("<rest> set b_input_name_status to true\n\r"));
    } else {
        b_input_name_status = FALSE; // rest_event_notify("system/input/name", 0, "xxx")
        DBG_INFO(("<rest> set b_input_name_status to false\n\r"));
    }
    return;
}

BOOL _rest_app_get_input_name_status(VOID)
{
    if (b_input_name_status == TRUE) {
        DBG_INFO(("<rest> _rest_app_get_input_name_status return true\n\r"));
        return TRUE;
    } else {
        DBG_INFO(("<rest> _rest_app_get_input_name_status return false\n\r"));
        return FALSE;
    }
}

BOOL _rest_can_notify_ready_to_cast(VOID)
{
    if (_rest_app_get_connection_status() == TRUE
        || test_connection_status() == TRUE) {
        if (ui1_ready_count == 4) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        return FALSE;
    }
}

static VOID _rest_ready_to_cast_expired_timer_cb(HANDLE_T h_timer, VOID* pv_tag)
{
    INT32 val = 0;

    DBG_INFO(("<rest> _rest_ready_to_cast_expired_timer_cb\n\r"));

    ui1_ready_count = 4;
    val = a_c4tv_apron_get_cast_state();
    rest_event_notify("tv_settings/cast/state", val, "");
#if 0
    if (ui1_ready_count != 3
        && (_rest_app_get_connection_status() == TRUE
            || test_connection_status() == TRUE)) {
        ui1_ready_count = 3;
        val = a_c4tv_apron_get_cast_state();
        rest_event_notify("tv_settings/cast/state", val, "");
    }
#endif
    c_timer_stop(h_timer_ready_to_cast);

    return;
}

INT32 a_rest_get_cast_state ()
{
    return g_i4_cast_state;
}

static BOOL b_is_cast_shell_ready = FALSE;

static VOID c4tv_apron_nfy_to_rest_cb(C4TV_APRON_CAST_STATE    e_cast_state,
                                VOID*                    pv_param1,
                                VOID*                    pv_param2,
                                VOID*                    pv_param3)
{
    //INT32 i4_ret = 0;
    UINT32 ui4_control_connect = 0;
    C4TV_APRON_CAST_STATUS t_cast_status;
    CHAR* active_app_ids[MAX_CAST_APP_NUM] = {0};
    //UINT8  ui1_power_mode = 0;

    //DBG_INFO(("<rest> c4tv_apron_nfy_to_rest_cb\n\r"));

    ui4_control_connect = (UINT32)pv_param1;
    if (1 != ui4_control_connect)
    {
        DBG_INFO(("<rest> Not connected\n\r"));
        return;
    }
    if (pv_param2 == NULL)
    {
        DBG_INFO(("<rest> Not status\n\r"));
        return;
    }

    c_memcpy(&t_cast_status, pv_param2, sizeof(C4TV_APRON_CAST_STATUS));
    if (t_cast_status.b_is_state_init == FALSE)
    {
        DBG_INFO(("<rest> Have not got cast status\n\r"));
        return;
    }

    //rest_event_notify("tv_settings/cast/state", (INT32)t_cast_status.e_cast_state, "");
    g_i4_cast_state = (INT32)t_cast_status.e_cast_state;

    if (t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_ForcedUpdate)
    {
        DBG_INFO(("<rest> It's for C4TV_APRON_CAST_STATE_ForcedUpdate\n\r"));
        return;
    }

    //C4TV_APRON_CAST_STATE e_cast_state;
    DBG_INFO(("<rest> c4tv_apron_nfy_to_rest_cb: t_cast_status.e_cast_state=%d (C4TV_APRON_CAST_STATE_ReadyToCast=%d)\n\r", t_cast_status.e_cast_state, C4TV_APRON_CAST_STATE_ReadyToCast));
    DBG_INFO(("<rest> ui1_ready_count before: %d\n\r", ui1_ready_count));
    switch (ui1_ready_count)
    {
        case 1:
            if (t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_ReadyToCast
                || t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_Suspended) {
                ui1_ready_count = 2;
            }
            break;
        case 2:
            if (t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_Offline) {
                ui1_ready_count = 3;
            }
            break;
        case 3:
            if (t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_ReadyToCast
                || t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_Suspended) {
                ui1_ready_count = 4;
            }
            break;
        default:
            break;
    }
    DBG_INFO(("<rest> ui1_ready_count after: %d\n\r", ui1_ready_count));

    // if cast state is 5 or 6, should consider want to notify or not
    if (t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_Suspended
        || t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_ReadyToCast)
    {
        if (_rest_can_notify_ready_to_cast()) {
            rest_event_notify("tv_settings/cast/state", (INT32)t_cast_status.e_cast_state, "");
            _rest_app_cast_shell_ready();
            b_is_cast_shell_ready = TRUE;
        }
        MTOSD_PLA_Enable(2, TRUE);
        DBG_INFO(("[REST] cast ready, ENABLE OSD3\n\r"));
#if 0
        i4_ret = a_icl_custom_get_power_mode(&ui1_power_mode);
        //DBG_INFO(("<rest> ui1_power_mode=%d (ICL_CUSTOM_POWER_MODE_QUICK_START=%d)\r\n",__LINE__,ui1_power_mode, ICL_CUSTOM_POWER_MODE_QUICK_START));
        if (i4_ret == ICLR_OK
            && ICL_CUSTOM_POWER_MODE_QUICK_START == ui1_power_mode)
        {
            //DBG_INFO(("<rest> quick start mode. believe\n\r"));
            rest_event_notify("tv_settings/cast/state", (INT32)t_cast_status.e_cast_state, "");
        }
        // power eco mode
        else
        {
            if (b_connection_status == FALSE && t_cast_status.e_cast_state == C4TV_APRON_CAST_STATE_ReadyToCast) {
                DBG_INFO(("<rest> Don't notify tv_settings/cast/state up\n\r"));
                return;
            } else {
                rest_event_notify("tv_settings/cast/state", (INT32)t_cast_status.e_cast_state, "");
                DBG_INFO(("<rest> c4tv_apron_nfy_to_rest_cb: call _rest_app_cast_shell_ready\n\r"));
                _rest_app_cast_shell_ready();
            }
        }
#endif
    }
    else
    {
        rest_event_notify("tv_settings/cast/state", (INT32)t_cast_status.e_cast_state, "");
    }

    //DBG_INFO(("<rest> c4tv_apron_nfy_to_rest_cb: ui1_active_apllications_num=%d\n\r", t_cast_status.ui1_active_apllications_num));

    // TODO: notify if there is no app

    for (INT32 i=0; i<t_cast_status.ui1_active_apllications_num; i++)
    {
        if (c_strlen(t_cast_status.at_active_applications[i].ps_app_id) != 0)
        {
            active_app_ids[i] = t_cast_status.at_active_applications[i].ps_app_id;
            DBG_INFO(("<rest> [10FAPPCHECKPOINT] active_app_ids[%d]=%s\n\r", i, active_app_ids[i]));
        }
    }
    _rest_app_launch_cast_app_notify(active_app_ids, t_cast_status.ui1_active_apllications_num);
}

static VOID rest_register_callback_to_c4tv_apron()
{
    DBG_INFO(("<rest> rest_register_callback_to_c4tv_apron\n\r"));

    INT32 i4_ret = 0;

    i4_ret = a_c4tv_apron_register_nfy_cb(c4tv_apron_nfy_to_rest_cb);
    DBG_INFO(("<rest> a_c4tv_apron_register_nfy_cb return %d\n\r", i4_ret));
}

INT16 rest_get_init_volume(VOID)
{
    return _i2_init_volume_value;
}

VOID rest_set_init_volume(INT16 i2_val)
{
    _i2_init_volume_value = i2_val;
}


/*---------------------------------------------------------------------------
 * Name
 *      _rest_app_init_fct
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _rest_app_init_fct (
                    const CHAR*                 ps_name,
                    HANDLE_T                    h_app
                    )
{
    INT32 i4_ret = 0;
    UINT16 ui2_dbg_level = 0;
    HANDLE_T h_async_init = NULL_HANDLE;
    //dolphin
    i4_ret=sem_init(&t_airplay_lock,1,0); //dolphin global - initvalue 0
    if(i4_ret<0)
    {
        DBG_LOG_PRINT(("<rest> t_airplay_lock sem init faild!\n"));
    }

    //dolphin
    i4_ret=sem_init(&t_install_script_lock,0,0); //dolphin global - internal use- initvalue 0
    if(i4_ret<0)
    {
        DBG_LOG_PRINT(("<rest> t_install_script_lock sem init faild!\n"));
    }

    DBG_INFO(("<rest> _rest_app_init_fct\r\n"));
#ifdef CLI_SUPPORT
    i4_ret = rest_cli_attach_cmd_tbl();
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> Err: rest_cli_attach_cmd_tbl() failed, ret=%ld\r\n", i4_ret));
        return AEER_FAIL;
    }
#endif /* CLI_SUPPORT */

    /* init application structue */
    h_rest_app = h_app;

    /*i4_ret = rest_init();
    REST_LOG_ON_FAIL(i4_ret);*/

    //cmd_convert_register_nfy(_rest_recv_cmd);

    //b_cast_shell_ready = FALSE;
    b_connection_status = FALSE;
    i4_hotkey_wakeup = 0;

    ui2_dbg_level = dbg_get_log_level_from_file("rest", "/data/loglevel.txt");
    DBG_LOG_PRINT(("[%s %d] rest_dbg_level [%d]\n", __func__, __LINE__, ui2_dbg_level));
    if(ui2_dbg_level<=1)
    {
        ui2_dbg_level=1; //dolphin 20200320 at least should have error debug
    }
    rest_set_dbg_level(ui2_dbg_level);

    i4_ret = c_timer_create (&h_timer_ready_to_cast);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_ready_to_cast failed\r\n"));
    }
    i4_ret = c_timer_create (&h_timer_avoid_backdrop);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_avoid_backdrop failed\r\n"));
    }
    i4_ret = c_timer_create (&h_timer_airplay_launch);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_airplay_launch failed\r\n"));
    }

    i4_ret = c_timer_create (&h_timer_oobe_sch_launch);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_oobe_sch_launch failed\r\n"));
    }


    i4_ret = c_timer_create(&h_timer_flash_led);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_flash_led failed\r\n"));
    }
    i4_ret = c_timer_create(&h_timer_binary_update);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_binary_update failed\r\n"));
    }
    i4_ret = c_timer_create(&h_timer_create_vtrl_ipt);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_create_vtrl_ipt failed\r\n"));
    }

    i4_ret = c_timer_create(&h_timer_disable_airplay);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_disable_airplay failed\r\n"));
    }
    i4_ret = c_timer_create(&h_timer_check_homekit_power_status);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_check_homekit_power_status failed\r\n"));
    }
    i4_ret = c_timer_create(&h_timer_toast_nav);
    if (i4_ret != 0) {
        DBG_ERROR(("<rest> _rest_app_init_fct- init h_timer_toast_nav failed\r\n"));
    }

    i4_ret = rest_network_register_notify();
    REST_LOG_ON_FAIL(i4_ret);

    //i4_ret = rest_bluetooth_register_notify();
    //REST_LOG_ON_FAIL(i4_ret);

    i4_ret = jsonrpc_init();
    REST_LOG_ON_FAIL(i4_ret);

    b_g_is_init = TRUE;

    rest_register_callback_to_c4tv_apron();
    httpc_client_init();

    i4_ret = c_httpc_new_session(&h_g_httpc_handle);
    if (HTTPR_OK != i4_ret) {
        DBG_ERROR(("[REST_AP_API][%s] FATAL: c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, i4_ret));
        h_g_httpc_handle = NULL_HANDLE;
        return AEER_FAIL;
    }

    DBG_INFO(("<rest> c_httpc_new_session() OK\r\n"));
    i4_ret = c_httpc_append_header(h_g_httpc_handle, "Content-Type: application/json");
    REST_LOG_ON_FAIL(i4_ret);

    //dolphin 20200519 add for record volume when power on
    rest_set_init_volume(menu_get_aud_volume_val());
    DBG_LOG_PRINT(("<rest> volume when power on is %d\r\n",rest_get_init_volume()));


#if 0
    /* Send the message to the rest message queue. */
    UINT16    ui2_retry = 10;

    do
    {
        i4_ret = c_app_send_msg(h_rest_app,
                        REST_MSG_ASYNC_INIT,
                        NULL,
                        0,
                        NULL,
                        NULL);
        if(i4_ret != AEER_OK)
        {
            if(ui2_retry > 0)
            {
                DBG_ERROR(("<REST>Cannot send REST_MSG_ASYNC_INIT message! resend again!\r\n"));
                c_thread_delay(100);
                ui2_retry--;
            }
            else
            {
                DBG_ERROR(("<REST>Cannot send REST_MSG_ASYNC_INIT message!\r\n"));
                break;
            }
        }
        else
        {
            break;
        }
    } while (TRUE);
#else
    i4_ret = x_thread_create(
                 &h_async_init,
                  "rest_async_init",
                 ((SIZE_T)4*1024),
                 ((UINT8) 200),
                 _rest_async_init,
                 0,
                 NULL);

    if (i4_ret != OSR_OK) {
        DBG_ERROR(("[REST] Create rest_async_init thread (fail) i4_ret[%d].\n", i4_ret));
    } else {
        DBG_INFO(("[REST] Create rest_async_init thread (success) i4_ret[%d].\n", i4_ret));
    }
#endif

    i4_ret = picture_acfg_notify_init();
    if (i4_ret != NAVR_OK) {
        DBG_ERROR(("[REST] picture_acfg_notify_init fail i4_ret %d.\n", i4_ret));
    } else {
        DBG_INFO(("[REST] picture_acfg_notify_init success i4_ret %d.\n", i4_ret));
    }

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name             _rest_app_exit_fct
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _rest_app_exit_fct (
                    HANDLE_T                    h_app,
                    APP_EXIT_MODE_T             e_exit_mode
                    )
{
    DBG_INFO(("<rest> _rest_app_exit_fct\r\n"));

    if (b_g_is_init == FALSE) {
        return AEER_FAIL;
    }

    rest_network_unregister_notify();
    //rest_bluetooth_unregister_notify();

    b_g_is_init = FALSE;

    jsonrpc_deinit();

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _rest_app_pause_fct
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _rest_app_pause_fct (
                    HANDLE_T                    h_app
                    )
{
    DBG_INFO(("<rest> _rest_app_pause_fct\r\n"));
    if (b_g_is_init == FALSE)
    {
        return AEER_FAIL;
    }

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      _rest_app_resume_fct
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
static INT32 _rest_app_resume_fct (
                    HANDLE_T                    h_app
                    )
{
    DBG_INFO(("<rest> _rest_app_resume_fct\r\n"));
    return AEER_OK;
}

BOOL _rest_app_is_cast_source_ex(CHAR* ps_cname)
{
    INT32       i4_ret              = 0;
    ISL_REC_T   t_isl_rec           = {0};
    CHAR        s_disp_name[16+1];
    UINT8       ui1_crnt_input_src  = 0;
    UINT8       ui1_count = 0;

    while (!_rest_app_is_create_vtrl_ipts_ok() && ui1_count < 50)
    {
        DBG_INFO(("_rest_app_is_create_vtrl_ipts_ok virtual didn't create yet\r\n"));
        usleep(30000);
        ui1_count++;
    }

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    if (ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<rest> Fun:%s, Ln:%d  a_cfg_av_get_disp_name fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
    if (ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<rest> Fun:%s, Ln:%d  a_cfg_av_get_input_src fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    i4_ret = a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);
    if (ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<rest> Fun:%s, Ln:%d  a_isl_get_rec_by_id fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    DBG_INFO(("<rest> Fun:%s, Ln:%d  t_isl_rec.t_avc_info.e_video_type=%d (DEV_VTRL_CAST=%d) t_isl_rec.ui1_internal_id: %d, t_isl_rec.s_src_name: %s\n",
                    __FUNCTION__, __LINE__, t_isl_rec.t_avc_info.e_video_type, DEV_VTRL_CAST, t_isl_rec.ui1_internal_id, t_isl_rec.s_src_name));
    if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type || DEV_VTRL_MMP == t_isl_rec.t_avc_info.e_video_type)
    {
        if (t_isl_rec.ui1_internal_id > 0) {
            c_strncpy(ps_cname, t_isl_rec.s_src_name, 16);
        } else {
            c_strncpy(ps_cname, "SMARTCAST", 9);
        }
        return TRUE;
    }

    return FALSE;
}

BOOL _rest_app_is_cast_source(VOID)
{
    INT32       i4_ret              = 0;
    ISL_REC_T   t_isl_rec           = {0};
    CHAR        s_disp_name[16+1];
    UINT8       ui1_crnt_input_src  = 0;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    if (ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<rest> Fun:%s, Ln:%d  a_cfg_av_get_disp_name fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    i4_ret = a_cfg_av_get_input_src(s_disp_name, &ui1_crnt_input_src);
    if (ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<rest> Fun:%s, Ln:%d  a_cfg_av_get_input_src fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    i4_ret = a_isl_get_rec_by_id(ui1_crnt_input_src, &t_isl_rec);
    if (ISLR_OK != i4_ret)
    {
        DBG_ERROR(("<rest> Fun:%s, Ln:%d  a_isl_get_rec_by_id fail:%d \n", __FUNCTION__, __LINE__, i4_ret));
        return FALSE;
    }

    DBG_INFO(("<rest> Fun:%s, Ln:%d  t_isl_rec.t_avc_info.e_video_type=%d (DEV_VTRL_CAST=%d)\n", __FUNCTION__, __LINE__, t_isl_rec.t_avc_info.e_video_type, DEV_VTRL_CAST));
    if (DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
    {
        return TRUE;
    }

    return FALSE;
}

static VOID _rest_app_check_switch_cast_source()
{
    ISL_REC_T    isl_rec = {0};
    TV_WIN_ID_T focus_id = {0};

    a_tv_get_focus_win(&focus_id);
    a_tv_get_isl_rec_by_win_id(focus_id, &isl_rec);

    /*change to cast source*/
    //DBG_INFO(("<rest> change to SCH when power on s_src_name:%s =airplay OR video type: %d = (DEV_VTRL_MMP: %d)\n\r",isl_rec.s_src_name, isl_rec.t_avc_info.e_video_type, DEV_VTRL_MMP));
    DBG_INFO(("<rest> change to SCH when power on MMP, video type: %d = (DEV_VTRL_MMP: %d)\n\r",isl_rec.t_avc_info.e_video_type, DEV_VTRL_MMP));

    if (DEV_VTRL_MMP == isl_rec.t_avc_info.e_video_type)        //((isl_rec.ui1_internal_id > 0) && c_strcmp(isl_rec.s_src_name,"airplay") == 0) ||
    {
        {
            ISL_REC_T       t_isl_rec;
            BOOL            b_found = FALSE;

            /* get virtual input by name */
            {
                UINT8           ui1_src_count = 0;
                UINT8           ui1_idx = 0;

                a_isl_get_num_rec(&ui1_src_count);

                if( 0 == ui1_src_count )
                {
                    return;
                }

                for (ui1_idx = 0; ui1_idx < ui1_src_count; ui1_idx++)
                {
                    c_memset(&t_isl_rec, 0, sizeof(t_isl_rec));

                    a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);

                    /* find casttv source */
                    if(a_nav_ipts_is_cast_source(&t_isl_rec) == FALSE)
                    {
                        continue;
                    }
                    DBG_INFO(("<rest> *******s_src_name=%s,ui1_idx=%d\n\r",t_isl_rec.s_src_name,ui1_idx));
                    b_found = TRUE;
                    break;
                }
            }

            if( b_found == TRUE )
            {
               CHAR            s_disp_name[16+1] = {0};

               a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));

               a_cfg_av_set_input_src(s_disp_name, t_isl_rec.ui1_id);
               DBG_INFO(("<rest> change to SCH when power on airplay\n\r"));
            }
        }
    }
}
extern VOID c4tv_customer_get_amazon_iot_cert_key_truststore();
static VOID _rest_app_check_amazon_iot_cert_thread (VOID*  pv_arg)
{

    c4tv_customer_get_amazon_iot_cert_key_truststore();
    x_thread_exit();
}

static VOID _rest_app_check_amazon_iot_cert()
{
    DBG_INFO(("<rest> _rest_app_check_amazon_iot_cert\r\n"));

    if (0 != access("/3rd_rw/amazon_iot/certificate.pem.crt", R_OK)
        || 0 != access("/3rd_rw/amazon_iot/private.key.pem", R_OK)
        || 0 != access("/3rd_rw/amazon_iot/CA.pem", R_OK)) {
        DBG_INFO(("<rest> no amazon iot cert\r\n"));
        {

        if(i4_second_check_cert >0)
        {
            if(h_check_amazon_thread == NULL_HANDLE)
            {
                DBG_INFO(("<rest> create check amazon thread\r\n"));
                x_thread_create(&h_check_amazon_thread,
                "check_amazon_iot_cert",
                4096,
                128,
                _rest_app_check_amazon_iot_cert_thread,
                0,
                NULL);
            }else
            {
                DBG_INFO(("<rest> not check amazon cert,if you need check,please AC TV\r\n"));
            }
            }else
            {
                i4_second_check_cert ++;
            }

        }
    }

    return;
}

extern INT32 a_c4tv_apron_enter_cast_mode(VOID);

static bool b_python_ready = false;
void rest_set_python_reeady ()
{
    DBG_INFO(("<rest> rest_set_python_reeady set python ready\n\r"));
    b_python_ready = true;
}

BOOL rest_get_python_ready ()
{
    DBG_INFO(("<rest> rest_get_python_ready get python ready\n\r"));
    return b_python_ready;
}

static VOID _rest_no_ready_delay_notify_input_list_timer_nfy_cb (HANDLE_T  pt_tm_handle, VOID* pv_tag)
{
    DBG_INFO(("<rest> Enter\n\r"));
    INT32 i4_ret = RESTR_OK;
    ui1_g_rest_ready_count_input_list ++;
    if(rest_get_python_ready() || (ui1_g_rest_ready_count_input_list >= 20))
    {
        rest_event_notify("system/input/list", 1, "");
        rest_set_sent_notify_input_list_while_python_ready();
        c_timer_stop(h_rest_ready_timer_input_list);
    }
    else
    {
        c_timer_stop(h_rest_ready_timer_input_list);
        DBG_INFO(("<rest> h_rest_ready_timer_input_list timer start\n\r"));
        i4_ret = c_timer_start (h_rest_ready_timer_input_list,
                                REST_CHECK_READY_TIMER,
                                X_TIMER_FLAG_ONCE,
                                _rest_no_ready_delay_notify_input_list_timer_nfy_cb,
                                NULL);
        REST_LOG_ON_FAIL(i4_ret);
    }
}

VOID rest_no_ready_delay_notify_input_list(VOID)
{
    DBG_INFO(("<rest> Enter\n\r"));

    INT32 i4_ret = RESTR_OK;
    ui1_g_rest_ready_count_input_list =0;
    if (NULL_HANDLE == h_rest_ready_timer_input_list)
    {
        i4_ret = c_timer_create(&h_rest_ready_timer_input_list);
        DBG_INFO(("<rest> h_rest_ready_timer_input_list timer create\n\r"));
        REST_LOG_ON_FAIL(h_rest_ready_timer_input_list);
    }
    c_timer_stop(h_rest_ready_timer_input_list);
    DBG_INFO(("<rest> h_rest_ready_timer_input_list timer start\n\r"));
    i4_ret = c_timer_start (h_rest_ready_timer_input_list,
                            REST_CHECK_READY_TIMER,
                            X_TIMER_FLAG_ONCE,
                            _rest_no_ready_delay_notify_input_list_timer_nfy_cb,
                            NULL);
    REST_LOG_ON_FAIL(i4_ret);
}

static VOID _rest_no_ready_delay_notify_input_enable_airplay_timer_nfy_cb (HANDLE_T  pt_tm_handle, VOID* pv_tag)
{
    DBG_INFO(("<rest> Enter\n\r"));

    INT32 i4_ret = RESTR_OK;
    ui1_g_rest_ready_count_input_enable_airplay ++;
    if(rest_get_python_ready() || (ui1_g_rest_ready_count_input_enable_airplay >= 20))
    {
        rest_event_notify("system/input/enable", 1, "airplay");
        c_timer_stop(h_rest_ready_timer_input_enable_airplay);
    }
    else
    {
        c_timer_stop(h_rest_ready_timer_input_enable_airplay);
        DBG_INFO(("<rest> h_rest_ready_timer_input_enable_airplay timer start\n\r"));
        i4_ret = c_timer_start (h_rest_ready_timer_input_enable_airplay,
                                REST_CHECK_READY_TIMER,
                                X_TIMER_FLAG_ONCE,
                                _rest_no_ready_delay_notify_input_enable_airplay_timer_nfy_cb,
                                NULL);
        REST_LOG_ON_FAIL(i4_ret);
    }
}

VOID rest_no_ready_delay_notify_input_enable_airplay(VOID)
{
    DBG_INFO(("<rest> Enter\n\r"));

    INT32 i4_ret = RESTR_OK;
    ui1_g_rest_ready_count_input_enable_airplay =0;
    if (NULL_HANDLE == h_rest_ready_timer_input_enable_airplay)
    {
        i4_ret = c_timer_create(&h_rest_ready_timer_input_enable_airplay);
        DBG_INFO(("<rest> h_rest_ready_timer_input_enable_airplay timer create\n\r"));
        REST_LOG_ON_FAIL(h_rest_ready_timer_input_enable_airplay);
    }
    c_timer_stop(h_rest_ready_timer_input_enable_airplay);
    DBG_INFO(("<rest> h_rest_ready_timer_input_enable_airplay timer start\n\r"));
    i4_ret = c_timer_start (h_rest_ready_timer_input_enable_airplay,
                            REST_CHECK_READY_TIMER,
                            X_TIMER_FLAG_ONCE,
                            _rest_no_ready_delay_notify_input_enable_airplay_timer_nfy_cb,
                            NULL);
    REST_LOG_ON_FAIL(i4_ret);
}

VOID rest_set_sent_notify_input_list_while_python_ready(VOID)
{
    DBG_INFO(("<rest> Enter\n\r"));
    b_has_sent_notify_input_list_while_python_ready = TRUE;
}

BOOL rest_get_sent_notify_input_list_while_python_ready(VOID)
{
    DBG_INFO(("<rest> Enter\n\r"));
    DBG_INFO(("<rest> b_has_sent_notify_input_list_while_python_ready is %d\n\r", b_has_sent_notify_input_list_while_python_ready));
    return b_has_sent_notify_input_list_while_python_ready;
}

/*---------------------------------------------------------------------------
 * Name
 *      _rest_app_process_msg_fct
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
extern BOOL        i4_hotkey_sch_wakeup;

static INT32 _rest_app_process_msg_fct (
                    HANDLE_T                    h_app,
                    UINT32                      ui4_type,
                    const VOID*                 pv_msg,
                    SIZE_T                      z_msg_len,
                    BOOL                        b_paused
                    )
{
    //INT32 i4_key;
    //INT32 i4_loop_count;
    //INT32 i4_ret = 0;

    switch (ui4_type)
    {
        case REST_MSG_ASYNC_INVOKE:
        {
            REST_MSG_ASYNC_INVOKE_T* pt_msg_async = (REST_MSG_ASYNC_INVOKE_T*)pv_msg;

            if(z_msg_len <= 4) {
                pt_msg_async->pf_async_func(NULL, 0);
            } else {
                pt_msg_async->pf_async_func(pt_msg_async->aui1_data, z_msg_len - 4);
            }

            break;
        }
        case AM_BRDCST_MSG_POWER_ON:
        {
            PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
            CHAR ps_cname[16] = {0};
            DBG_INFO(("[%s %d] AM_BRDCST_MSG_POWER_ON set mdns_for vizio\n", __func__, __LINE__));
            a_mdns_stop();
            a_mdns_start();
            power_status = 1;
            rest_event_notify("state/device/power_mode", 1, "");
            DBG_INFO(("[%s %d] AM_BRDCST_MSG_POWER_ON set mdns_for vizio\n", __func__, __LINE__));
            ui1_ready_count = 0;
            // start a timmer to check
            if (c_timer_stop(h_timer_ready_to_cast) == OSR_OK) {
                c_timer_start(h_timer_ready_to_cast,
                              TIMER_READY_TO_CAST_INTERVAL,
                              X_TIMER_FLAG_REPEAT,
                              _rest_ready_to_cast_expired_timer_cb,
                              NULL);
                ui1_ready_count = 1;
                DBG_INFO(("<rest> start h_timer_ready_to_cast for %ds\r\n", TIMER_READY_TO_CAST_INTERVAL));
            } else {
                DBG_INFO(("<rest> stop h_timer_ready_to_caste failed\r\n"));
            }

            DBG_INFO(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_POWER_ON\n\r"));

             //dolphin 20190906 enable osd 1 for chromium showed in osd 1 prevent from RC power on showing garbage
            MTOSD_PLA_Enable(0, TRUE);
            DBG_INFO(("<rest> power on enable osd1\n"));

            rest_softap_power_on();
            _rest_app_check_amazon_iot_cert();

            /* check is there pending binary update */
            if (c_timer_stop(h_timer_binary_update) == OSR_OK) {
                c_timer_start(h_timer_binary_update,
                            30000,
                            X_TIMER_FLAG_REPEAT,
                            _rest_system_update_binary_expired_timer_cb,
                            NULL);
                DBG_INFO(("Start h_timer_binary_update for 30s\n\r"));
            } else {
                DBG_INFO(("Stop h_timer_binary_update failed\n\r"));
            }


            c_pcl_get_wakeup_reason(&e_wakeup_reason, NULL);
#ifndef LINUX_AUTO_TEST /* disable usb input list in LINUX_AUTO_TEST=true build */
            c_memset(ps_cname, '\0', 16);
            if (a_wzd_is_oobe_mode()) {
                DBG_INFO(("<rest> _rest_app_process_msg_fct-starting oobe\n\r"));
            }else
            {
                DBG_LOG_PRINT(("<rest><wo>_rest_app_process_msg_fct line: %d - AM_BRDCST_MSG_POWER_ON-,reason=%d,wakeup=0x%x\n\r", __LINE__,e_wakeup_reason,i4_hotkey_wakeup));
                if (_rest_app_is_cast_source_ex(ps_cname)
                    && i4_hotkey_wakeup == 0
                    && PCL_WAKE_UP_REASON_CASTCORE != e_wakeup_reason
                    && PCL_WAKE_UP_REASON_HDMI != e_wakeup_reason
                    && PCL_WAKE_UP_REASON_CUSTOM_1 != e_wakeup_reason
                    && PCL_WAKE_UP_REASON_AIRPLAY != e_wakeup_reason
                    && FALSE == msg_convert_custom_cobalt_alive()
                    && FALSE == msg_convert_custom_amazon_alive()
                    && FALSE == msg_convert_custom_netflix_active())
                {
                    if (c_strcmp(ps_cname, "SMARTCAST") != 0)
                    {
                        if (c_strcmp(ps_cname, "watchfree") == 0)
                        {
                            DBG_INFO(("<rest> _rest_app_process_msg_fct line: %d - AM_BRDCST_MSG_POWER_ON- launch WatchFree\n\r", __LINE__));
                            //a_c4tv_apron_enter_cast_mode(); //dolphin 20191218 no launch c4tv when watchfree wakeup
                            app_thread_run_launch_app_by_keycode(0xf7, 2);
                        }else if((c_strcmp(ps_cname, "airplay") == 0))
                            {
                                if(i4_AC_power == TRUE)
                                {
                                      DBG_LOG_PRINT(("<rest> _rest_app_process_msg_fct line: %d - AM_BRDCST_MSG_POWER_ON- launch SCH\n\r", __LINE__));
                                      app_thread_run_launch_app_by_keycode(0x2d, 2);
                                }else{
                                    //define 0xaa & 9 for airplay source
                                     DBG_LOG_PRINT(("<rest> _rest_app_process_msg_fct line: %d - AM_BRDCST_MSG_POWER_ON- launch Airplay\n\r", __LINE__));
                                    app_thread_run_launch_app_by_keycode(0xaa, 9);
                                }
                            }
                        else
                        {
                            DBG_INFO(("<rest> _rest_app_process_msg_fct line: %d - AM_BRDCST_MSG_POWER_ON- launch SCH\n\r", __LINE__));
                            //for conjure
                           // a_c4tv_apron_enter_cast_mode();
                            app_thread_run_launch_app_by_keycode(0x2d, 2);
                        }
                    }
                    else
                    {
                        DBG_INFO(("<rest> >>_rest_app_process_msg_fct line: %d - AM_BRDCST_MSG_POWER_ON- launch SCH\n\r", __LINE__));
                        //for conjure
                        //a_c4tv_apron_enter_cast_mode();
                        app_thread_run_launch_app_by_keycode(0x2d, 2);
                    }
                }
            }
#endif
            i4_AC_power = FALSE;
            if (i4_hotkey_wakeup > 0) {
                DBG_INFO(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_POWER_ON- launch partner app 0x%x\n\r", i4_hotkey_wakeup));
                if (i4_hotkey_wakeup == 0xeb) {
                    break;
                }

                if (_rest_app_is_cast_source() == FALSE && a_rest_is_conjure_install() == FALSE) //dolphin 20191205 when conjure install power on do not change src to nav
                {
                    UINT8 ui1_count;
                    ui1_count = 0;
                    while (a_am_is_power_on() == FALSE)
                    {
                        if (ui1_count > 30) {
                            break;
                        }
                        DBG_INFO(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_POWER_ON- wait till power on, ui1_count = %d\n\r", ui1_count));
                        c_thread_delay(200);
                    }
                    DBG_INFO(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_POWER_ON- switch input to cast\n\r"));
                    chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_CAST, 0);
                }

                if (i4_hotkey_wakeup == 0x2d ||i4_hotkey_wakeup == 0xec || i4_hotkey_wakeup == 0x6f || i4_hotkey_wakeup == 0xea
                    || i4_hotkey_wakeup == 0xf8 || i4_hotkey_wakeup == 0xee || i4_hotkey_wakeup == 0xf7) {
                    ui1_ready_count = 4;
                }
                if(i4_hotkey_wakeup == 0x2d)
                {
                    i4_hotkey_sch_wakeup = TRUE;
                    DBG_INFO(("<rest>_rest_app_process_msg_fct- AM_BRDCST_MSG_POWER_ON- launch sch\n\r"));
                }
                    app_thread_run_launch_app_by_keycode(i4_hotkey_wakeup, 3);


                i4_hotkey_wakeup = 0;
            }

            if(rest_get_python_ready())
            {
                c_thread_delay(100);
                rest_event_notify("system/input/list", 1, "");
                rest_set_sent_notify_input_list_while_python_ready();
            }
            else
            {
                rest_no_ready_delay_notify_input_list();
            }
#ifdef MT5583_MODEL
            a_nw_check_resume_connection_status();
#endif
            break;
        }
        case AM_BRDCST_MSG_PRE_POWER_OFF:
        {
            INT32 i4_ret;
            DBG_LOG_PRINT(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_PRE_POWER_OFF\n\r"));

            UINT8 ui1_power_mode = 0;
            i4_ret = a_icl_custom_get_power_mode(&ui1_power_mode);
            if (i4_ret == ICLR_OK
                && ICL_CUSTOM_POWER_MODE_ECO == ui1_power_mode) {
                DBG_INFO(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_PRE_POWER_OFF- eco mode\n\r"));
                power_status = 2;
                rest_event_notify("state/device/power_mode", 2, "");
                a_mdns_stop();
            } else {
                power_status = 0;
                rest_event_notify("state/device/power_mode", 0, "");//0:bgm
            }
            i4_ret = a_c4tv_apron_stop_current_app();

            DBG_INFO(("<rest> call a_c4tv_apron_stop_current_app: %d\n", i4_ret));

            i4_hotkey_wakeup = 0;
            ui1_ready_count = 0;
            b_connection_status = FALSE;
            b_is_cast_shell_ready = FALSE;

            _rest_app_no_app_notification();
            _rest_app_set_keycode_luanch_input(0);
            /*if current source is airplay,then switch to smarthome before enter standby*/
            _rest_app_check_switch_cast_source();
             {
                        ISL_REC_T    isl_rec = {0};
                        INT32        ret = NAVR_OK;
                        TV_WIN_ID_T focus_id = {0};

                        ret = a_tv_get_focus_win(&focus_id);
                        ret = a_tv_get_isl_rec_by_win_id(focus_id, &isl_rec);
                        if(isl_rec.e_src_type == INP_SRC_TYPE_VTRL)
                        {
                                //next power on is sch
                                DBG_INFO(("<rest> power off current virtual input \n"));
                        }
              }

             //dolphin 20190906 disable osd 1 for chromium showed in osd 1 prevent from RC power on showing garbage
            MTOSD_PLA_Enable(0, FALSE);
            DBG_INFO(("<rest> power off disable osd1\n"));

            /* Reset wakeup reason when power off */
            PCL_WAKE_UP_REASON_T e_wakeup_reason = PCL_WAKE_UP_REASON_UNKNOWN;
            c_pcl_get_wakeup_reason(&e_wakeup_reason, NULL);
            if (e_wakeup_reason == PCL_WAKE_UP_REASON_AIRPLAY) {
                DBG_INFO(("<rest> reset e_wakeup_reason when power off \n"));
                c_pcl_set_wakeup_reason(PCL_WAKE_UP_REASON_IRRC, NULL);
            }

            break;
        }
        case AM_BRDCST_MSG_POWER_OFF:
        {
            DBG_LOG_PRINT(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_POWER_OFF\n\r"));
            //b_cast_shell_ready = FALSE;
            b_is_cast_shell_ready = FALSE;
            break;
        }
        case AM_BRDCST_MSG_HOTKEY_WAKEUP:
        {
            UINT32 ui4_key_code;
            ui4_key_code = 0;
            c_memcpy(&ui4_key_code, (UINT8*)pv_msg, sizeof(ui4_key_code));

            DBG_INFO(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_HOTKEY_WAKEUP\n\r"));
            DBG_INFO(("<rest> [10FAPPCHECKPOINT] Get hotkey wakeup 0x%x\n", ui4_key_code));

            if (ui4_key_code == BTN_NETFLIX) {
                i4_hotkey_wakeup = 0xeb;
                return AEER_OK;
            }

            switch (ui4_key_code)
            {
                case BTN_WIDGET: // VIA key
                    i4_hotkey_wakeup = 0x2d;
                    break;
                case BTN_VUDU:
                    i4_hotkey_wakeup = 0xec;
                    break;
                case BTN_AMAZON:
                    i4_hotkey_wakeup = 0xea;
                    break;
                case BTN_XUMO:
                    i4_hotkey_wakeup = 0x6f;
                    break;
                case BTN_CRACKLE:
                    i4_hotkey_wakeup = 0xf8;
                    break;
                case BTN_HULU:
                    i4_hotkey_wakeup = 0xf9;
                    break;
                case BTN_IHEART_RADIO:
                    i4_hotkey_wakeup = 0xee;
                    break;
                case BTN_WATCHFREE:
                    i4_hotkey_wakeup = 0xf7;
                    break;
                case BTN_REDBOX:
                    i4_hotkey_wakeup = 0x42;
                    break;
                case BTN_HAYSTACK:
                    i4_hotkey_wakeup = 0x1e;
                    break;
        case BTN_DISNEY:
            i4_hotkey_wakeup = 0x1f;
            break;
        case BTN_PARTNER_1:
            i4_hotkey_wakeup = 0x0b;
            break;
        case BTN_PARTNER_2:
            i4_hotkey_wakeup = 0x51;
            break;
        case BTN_PARTNER_3:
            i4_hotkey_wakeup = 0x5A;
            break;
        case BTN_PARTNER_4:
            i4_hotkey_wakeup = 0x60;
            break;
        case BTN_PARTNER_5:
            i4_hotkey_wakeup = 0x61;
            break;
        case BTN_PARTNER_6:
            i4_hotkey_wakeup = 0x62;
            break;
        case BTN_PARTNER_7:
            i4_hotkey_wakeup = 0x64;
            break;
        case BTN_PARTNER_8:
            i4_hotkey_wakeup = 0x65;
            break;
        case BTN_PARTNER_9:
            i4_hotkey_wakeup = 0x73;
            break;
        case BTN_PARTNER_10:
            i4_hotkey_wakeup = 0x80;
            break;
        case BTN_PARTNER_11:
            i4_hotkey_wakeup = 0xA0;
            break;
        case BTN_PARTNER_12:
            i4_hotkey_wakeup = 0xA3;
            break;
        case BTN_PARTNER_13:
            i4_hotkey_wakeup = 0xA4;
            break;
        case BTN_PARTNER_14:
            i4_hotkey_wakeup = 0xB0;
            break;
        case BTN_PARTNER_15:
            i4_hotkey_wakeup = 0xF1;
            break;
        case BTN_PARTNER_16:
            i4_hotkey_wakeup = 0xF2;
            break;
        case BTN_PARTNER_17:
            i4_hotkey_wakeup = 0xF3;
            break;
        case BTN_PARTNER_18:
            i4_hotkey_wakeup = 0xF4;
            break;
        case BTN_PARTNER_19:
            i4_hotkey_wakeup = 0xF5;
            break;
        case BTN_PARTNER_20:
            i4_hotkey_wakeup = 0xF6;
            break;
                default:
                    return AEER_OK;
            }
            DBG_INFO(("<rest> [10FAPPCHECKPOINT] Set i4_hotkey_wakeup 0x%x\n", i4_hotkey_wakeup));
#if 0
            i4_loop_count = 0;
            while (1) {
                if (i4_loop_count > 60) {
                    return AEER_OK;
                }
                if (FALSE == a_am_is_power_on()) {
                    c_thread_delay(500);
                    i4_loop_count++;
                    DBG_INFO(("<rest> _rest_app_process_msg_fct- AM_BRDCST_MSG_HOTKEY_WAKEUP- wait until power on. i4_loop_count=%d\n\r", i4_loop_count));
                    continue;
                }
                break;
            }
#endif
            break;
        }
        default:
            break;
    }

    return AEER_OK;
}

/*---------------------------------------------------------------------------
 * Name
 *      a_app_set_registration
 * Description      -
 * Input arguments  -
 * Output arguments -
 * Returns          -
 *---------------------------------------------------------------------------*/
VOID a_rest_registration(
                AMB_REGISTER_INFO_T*            pt_reg
                )
{
    if (b_g_is_init == TRUE)
    {
        return;
    }

    DBG_API(("<rest>a_rest_registration\r\n"));

    /* Application can only use middleware's c_ API */
    c_memset(pt_reg->s_name, 0, sizeof(CHAR)*(APP_NAME_MAX_LEN + 1));
    c_strncpy(pt_reg->s_name, REST_NAME, APP_NAME_MAX_LEN);
    pt_reg->t_fct_tbl.pf_init                   = _rest_app_init_fct;
    pt_reg->t_fct_tbl.pf_exit                   = _rest_app_exit_fct;
    pt_reg->t_fct_tbl.pf_pause                  = _rest_app_pause_fct;
    pt_reg->t_fct_tbl.pf_resume                 = _rest_app_resume_fct;
    pt_reg->t_fct_tbl.pf_process_msg            = _rest_app_process_msg_fct;
    pt_reg->t_desc.ui8_flags                    = AEE_FLAG_WRITE_CONFIG|AEE_FLAG_WRITE_FLM|AEE_FLAG_WRITE_TSL|AEE_FLAG_WRITE_SVL; //~((UINT64)0);
    pt_reg->t_desc.t_thread_desc.z_stack_size   = 4096*8;
    pt_reg->t_desc.t_thread_desc.ui1_priority   = 200;
    pt_reg->t_desc.t_thread_desc.ui2_num_msgs   = 20;
    pt_reg->t_desc.ui4_app_group_id             = 0;
    pt_reg->t_desc.ui4_app_id                   = 0;
    pt_reg->t_desc.t_max_res.z_min_memory       = 1024 * 8;
    pt_reg->t_desc.t_max_res.z_max_memory       = 1024 * 8;
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
    pt_reg->at_system_keys[0].ui4_key_code      = 0;
    pt_reg->at_system_keys[0].ui2_state_num     = 0;
    pt_reg->ui2_key_num                         = 1;

    return;
}

/*----------------------------------------------------------------------------
 * Name: rest_async_invoke
 *
 * Description:
 *      Invoke a function in the rest thread context.
 *
 * Inputs:
 *      rest_async_func - The asynchronous function to call
 *      pv_data - The data of the the callback function. This parameter could be
 *                NULL, which is used to send NO data.
 *      z_data_len - The data length of pv_data. If the pv_data is NULL,
 *                   the z_data_len is ignored and the actual data len will be
 *                   zero.
 *      b_retry - Retry or not if message queue is full
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 rest_async_invoke(rest_async_func  pf_async_func,
                        VOID*            pv_data,
                        SIZE_T           z_data_len,
                        BOOL             b_retry)
{
    INT32                   i4_ret;
    REST_MSG_ASYNC_INVOKE_T t_msg_async;
    UINT16                  ui2_retry;
    static UINT32 ui4_message_current_tick = 0;

    if (pf_async_func == NULL) {
        return RESTR_INV_ARG;
    }
    if(b_g_is_init == FALSE) {
        DBG_ERROR(("<REST> L%d Cannot send async invoke message! rest not inited\n", __LINE__));
        return RESTR_FAIL;
    } else if(h_rest_app == NULL_HANDLE){
        DBG_ERROR(("<REST> L%d Cannot send async invoke message! NULL_HANDLE\n", __LINE__));
        return RESTR_FAIL;
    }

    if (b_retry) {
        ui2_retry = 30;
    } else {
        ui2_retry = 0;
    }

    c_memset(&t_msg_async, 0, sizeof(REST_MSG_ASYNC_INVOKE_T));
    t_msg_async.pf_async_func = pf_async_func;
    if(pv_data != NULL)
    {
        if(z_data_len <= REST_ASYNC_DATA_THRESHOLD) {
            c_memcpy(t_msg_async.aui1_data, pv_data, z_data_len);
        } else {
            DBG_ERROR(("<REST> Aysnc data size is too big: %d>%d", z_data_len, REST_ASYNC_DATA_THRESHOLD));
            return RESTR_INV_ARG;
        }
    }

    /* Send the message to the rest message queue. */
    do {
        i4_ret = c_app_send_msg(h_rest_app,
                        REST_MSG_ASYNC_INVOKE,
                        &t_msg_async,
                        z_data_len + 4,
                        NULL,
                        NULL);
        if (i4_ret != AEER_OK)
        {
            ui2_send_msg_fail_count++;
            DBG_INFO(("<REST> L%d Cannot send async invoke message! ui2_send_msg_fail_count: %d, ret:%d\r\n", __LINE__,ui2_send_msg_fail_count, i4_ret));
            if (ui2_retry > 0)
            {
                c_thread_delay(100);
                ui2_retry--;
            }
            else
            {
                //DBG_ERROR(("<REST> L%d Cannot send async invoke message ret:%d\r\n", __LINE__, i4_ret));
                break;
            }
        }
        else
        {
            ui2_send_msg_fail_count = 0;
            break;
        }
    } while (TRUE);
    /**
    For send message fail count more then 100 times will b.dtvall,and during 2 mins only one time d.dtvall
    ***/
    if(ui2_send_msg_fail_count >200)
    {
        ui2_send_msg_fail_count =0;
        if((c_os_get_sys_tick() > ui4_message_current_tick)&&
          (ui4_message_current_tick > 0)&&
          (((c_os_get_sys_tick() - ui4_message_current_tick)*c_os_get_sys_tick_period()) > 2*60*1000)) //The b.dtvall need 2 minus to output log
        {
            ui4_message_current_tick = c_os_get_sys_tick();
            system("PATH=/bin:/sbin:/system/bin:/system/sbin LD_LIBRARY_PATH=/lib:/system/lib /bin/cli b.dtvall &");
        }
        else if(ui4_message_current_tick == 0)
        {
            ui4_message_current_tick = c_os_get_sys_tick();
            system("PATH=/bin:/sbin:/system/bin:/system/sbin LD_LIBRARY_PATH=/lib:/system/lib /bin/cli b.dtvall &");
        }
    }

    return i4_ret == AEER_OK ? RESTR_OK : RESTR_FAIL;
}

void _rest_app_factory_reset()
{
    DBG_INFO(("<rest> _rest_app_factory_reset\n\r"));

    if (0 == access("/3rd_rw/rest_server/pairedDevices", 0)) {
        //system("rm -rf /3rd_rw/rest_server/pairedDevices; sync");
        s_rm("/3rd_rw/rest_server/pairedDevices");
        s_sync();
    }
    if(0 == access(ULI_UPDATE_TIME_JSON,F_OK))
    {
        s_rm(ULI_UPDATE_TIME_JSON);
    }

    /* remove data downloaded by python */
    //system("rm -rf /3rd_rw/sc-data"); //dolphin
    //system("rm -rf /3rd_rw/apps");
    s_rm("/3rd_rw/sc-data");
    s_rm("/3rd_rw/apps");

    /* reset web server content */
    //system("rm -rf /3rd_rw/web_server");
    //system("rm -rf /3rd_rw/oobe");
    //system("rm -rf /demo/sc");
    s_rm("/3rd_rw/web_server");
    s_rm("/3rd_rw/oobe");
    s_rm("/demo/sc");
    s_rm("/demo/permission_cfg");
    s_rm("/data/permission_cfg");

    /* reset SCH page content */
    system("rm -rf /data/chromium/");
    system("rm -rf /data/chrome/");

    /* remove the binaries */
    system("rm -rf /data/app/*");

    /* reset homekit data */
    homekit_factory_reset();

    /* reset airplay data */
    //radar id:50625143
   // system("rm -rf /3rd_rw/airplay/mfi_provision");
    //system("rm -rf /3rd_rw/airplay/fps_provision");
    system("rm -rf /3rd_rw/airplay/Library/*");
    system("rm -rf /3rd_rw/airplay/Library/.*"); //remove .HomeKitStore

    //reset Apple TV account
    system("rm -rf /data/storage/appletv/data/");

    //reset HBOMAX account
    system("rm -rf /data/storage/hbomax/");

    //reset upgrade pkg
    system("rm -rf /upgrade/upgrade_integrity_ok.pkg");

    //system("sync; sync; sync");
    s_sync();
    /* Kill process in order to force filesystem to free disk */

    system("kill -9 `ps | grep chromium_shell | awk \'{print $1}\'`");
    system("kill -9 `ps | grep chromium_ctrl_svc | awk \'{print $1}\'`");
    system("kill -9 `ps | grep chrome-sandbox | awk \'{print $1}\'`");
    system("kill -9 `ps | grep airplaydemo | awk \'{print $1}\'`");
    system("kill -9 `ps | grep HAPAS_Tv | awk \'{print $1}\'`");

    system("kill -9 `ps -ef | awk '/[c]hromium_ctrl_svc/{print $2}'`");

    return;
}

//dolphin check conjure had been installed
BOOL a_rest_is_conjure_install(VOID)
{
    char linkpath[100]={0};
    ssize_t rlen;

    /* conjure real install in /data/app/ */
    if(0 == access("/data/app/conjure/VERSION", F_OK))  //conjure bin exist
    {
        memset(linkpath,0x0,sizeof(linkpath));
        ssize_t rlen = readlink("/data/app/chromium", linkpath, sizeof(linkpath) - 1); //chromium soft link exist
        if (-1 != rlen)
        {
            linkpath[rlen] = '\0';
             if(NULL != c_strstr(linkpath,"conjure")) //chromium had link to conjure
             {
                 return TRUE;
             }
        }
    }

    /* conjure real install in /backup/chromium */
    if(0 == access("/backup/chromium/VERSION", F_OK))
    {
        return TRUE;
    }

    /* conjure real install in /application/chromium for backup */
    if(0==access("/application/chromium/VERSION", F_OK))  //conjure bin exist
    {
        return TRUE;
    }

    return FALSE;
}

bool _rest_get_file_ver(char p_file_path[64],char p_ver[64])
{
    FILE*   f_input_fd;
    char    p_no_ver[64] = "N/A";
    char p_file_ver[64] = {0};

    f_input_fd = fopen (p_file_path, "r");
    if (f_input_fd)
    {
        if (fgets(p_file_ver, 64, f_input_fd) != NULL)
        {
            char *pos;
            if ((pos = c_strchr(p_file_ver, '\n')) != NULL) {
                *pos = '\0';
            }
        }
        fclose (f_input_fd);
        c_strncpy(p_ver, p_file_ver, c_strlen(p_file_ver));
    }
    else
    {
        c_strncpy(p_ver, p_no_ver, c_strlen(p_no_ver));
        return FALSE;
    }
    return TRUE;
}

//dolphin 20200109 if get version file return fileversion and return TRUE ,else return FALSE and "N/A"
bool a_rest_get_conjure_version(char p_ver[64])
{
    char    p_no_ver[64] = "N/A";
    bool b_ret=FALSE;

    if(a_rest_is_conjure_install()==TRUE)
    {
        if(0==access("/data/app/conjure/VERSION",F_OK))
        {
            b_ret = _rest_get_file_ver("/data/app/conjure/VERSION",p_ver);
        }
        else if(0==access("/backup/chromium/VERSION",F_OK))
        {
            b_ret = _rest_get_file_ver("/backup/chromium/VERSION",p_ver);
        }
        else if(0==access("/application/chromium/VERSION",F_OK))
        {
            b_ret = _rest_get_file_ver("/application/chromium/VERSION",p_ver);
        }
        else{
            c_strcpy(p_ver,p_no_ver);
        }
    }
    else{
        c_strcpy(p_ver,p_no_ver);
    }
    return b_ret;
}

bool a_rest_get_amazon_version(char* str_version)
{
    FILE *fp;
    CHAR str_buffer[256];
    CHAR* pc_version;

    c_strncpy(str_version, "N/A", c_strlen("N/A"));

    if ((fp = fopen("/3rd/amazon/config.ini", "r")) != NULL)
    {
        while(fgets(str_buffer, 256, fp) != NULL)
        {
            if (c_strncmp(str_buffer, "PlatformPackageVersion", c_strlen("PlatformPackageVersion")) == 0)
            {
                pc_version = c_strchr(str_buffer, '=');
                pc_version++;
                strncpy(str_version, pc_version, strlen(pc_version));
                break;
            }
        }
        fclose(fp);
        return;
    }
    DBG_INFO(("%s %d read config.ini failed\n\r"));
    return;
}

int a_rest_current_power_status()
{
    return power_status;
}

#ifdef __cplusplus
}
#endif
