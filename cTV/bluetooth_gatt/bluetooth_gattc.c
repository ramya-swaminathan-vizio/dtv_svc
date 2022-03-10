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

#ifdef APP_BLUETOOTH_SUPPORT
#include <string.h>
#include <stdio.h>
#include <unistd.h>
// middleware level
#include "u_irrc_btn_def.h"
#include "u_appman.h"
#include "u_aee.h"
#include "u_cli.h"
#include "u_irrc_btn_def.h"

#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_iom.h"


// application level
#include "amb/a_amb.h"
#include "am/a_am.h"
#include "app_util/a_common.h"
#include "rest/a_rest.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "bgm/mtk_comp/bgm_cast_c4tv/a_bgm_cast_c4tv.h"
// private
#include "bluetooth.h"

#include "bluetooth_gattc_rssimeter_view.h"
#include "bluetooth_gattc.h"
#include "bluetooth_gattc_wake.h"           /* Keep it at last for dbg log print control */

#ifndef SYS_BLUETOOTH_LAZY_INIT
extern INT32  a_bt_system_bootup_sequence_init(VOID);
#endif
extern INT32 a_bt_gatt_cli_start_log_indicator_check(VOID);
extern INT32 a_bt_gatt_cli_stop_log_indicator_check(VOID);
extern INT32 a_bt_gatt_cli_exec_cmd_from_file(VOID);

/*********************************variable declaration***********************************/
static UINT16           bt_gatt_dbg_level       = DBG_INIT_LEVEL_APP_GATT;
static BT_GATT_OBJ_T    t_g_bt_gatt             = {0};
static CHAR             s_gattc_cred[GATTC_CRED_LEN+1] = {0};
static CHAR             s_gattc_session_token[GATTC_SESSION_TOKEN_LEN+1] = {0};
BOOL                    b_allow_scan            = FALSE;
BOOL                    b_can_scan              = TRUE;
BOOL                    b_is_poweroff           = FALSE;
BOOL                    b_dtv_force_stop_scan   = FALSE;
/************************************private methods declarations*************************************/
static INT32 _bluetooth_gattc_init(
                    const CHAR*                 ps_name,
                    HANDLE_T                    h_app
                    );
static INT32 _bluetooth_gattc_exit (
                    HANDLE_T                    h_app,
                    APP_EXIT_MODE_T             e_exit_mode
                    );
static INT32 _bluetooth_gattc_pause (
                    HANDLE_T                    h_app
                    );
static INT32 _bluetooth_gattc_resume (
                    HANDLE_T                    h_app
                    );
static INT32 _bluetooth_gattc_process_msg (
                    HANDLE_T                    h_app,
                    UINT32                      ui4_type,
                    const VOID*                 pv_msg,
                    SIZE_T                      z_msg_len,
                    BOOL                        b_paused
                    );
INT32 bt_gatt_send_msg(UINT32 ui4_msgtype, BT_GATT_MSG_T* pt_bt_msg);
INT32 bt_aud_sendmsg_to_ble_gatt(UINT32 ui4_msg);



/******************************************functions define********************************************/
// bluetooth_audio app call bluetooth_gatt app API, to start bluetooth gatt app
INT32 bt_audio_call_gatt_interface()
{
    BT_GATT_ENTER_FUNCTION();

    /*AMB_REGISTER_INFO_T* pt_amb_reg_info = NULL;

    // Register bluetooth gatt application
    pt_amb_reg_info =(AMB_REGISTER_INFO_T *)&t_bt_gatt_amb_reg_info;
    _memset (((VOID*) pt_amb_reg_info), 0, sizeof (AMB_REGISTER_INFO_T));

    a_bluetooth_gattc_init(&t_bt_gatt_amb_reg_info);// initial
    DBG_ERROR(("<BT_GATT> bluetooth gatt init.\r\n"));

    if (a_amb_register_app(&t_bt_gatt_amb_reg_info) != AMBR_OK)// register
    {
        return BLUETOOTH_GATTC_FAILED;
    }
    // Start bluetooth gatt application
    if (AMBR_OK!=a_amb_sync_start_app(t_bt_gatt_amb_reg_info.s_name))// start
    {
        return BLUETOOTH_GATTC_FAILED;
    }*/

    BT_GATT_EXTI_FUNCTION();
    return BLUETOOTH_GATTC_OK;
}

// bluetooth gatt app start first step, other two steps are register, start, refer to above function bt_audio_call_gatt_interface()
VOID a_bluetooth_gattc_init(AMB_REGISTER_INFO_T* pt_reg)
{
    DBG_ERROR(("<BT_GATT> Enter function =%s, line=%d\r\n",__FUNCTION__, __LINE__));

    if (t_g_bt_gatt.b_app_init_ok)
    {
        DBG_ERROR(("<BT_GATT> error: %s() called again.\r\n", __FUNCTION__));
        return;
    }

    // Application can only use middleware's c_ API
    c_memset(pt_reg->s_name, 0, sizeof(CHAR)*(APP_NAME_MAX_LEN + 1));
    c_strncpy(pt_reg->s_name, BLUETOOTH_GATT_APP_NAME, APP_NAME_MAX_LEN);
    pt_reg->t_fct_tbl.pf_init                   = _bluetooth_gattc_init;
    pt_reg->t_fct_tbl.pf_exit                   = _bluetooth_gattc_exit;
    pt_reg->t_fct_tbl.pf_pause                  = _bluetooth_gattc_pause;
    pt_reg->t_fct_tbl.pf_resume                 = _bluetooth_gattc_resume;
    pt_reg->t_fct_tbl.pf_process_msg            = _bluetooth_gattc_process_msg;
    pt_reg->t_desc.ui8_flags                    = ~((UINT64)0);
    pt_reg->t_desc.t_thread_desc.z_stack_size   = BLUETOOTH_GATT_STACK_SIZE;
    pt_reg->t_desc.t_thread_desc.ui1_priority   = 200;
    pt_reg->t_desc.t_thread_desc.ui2_num_msgs   = 300;
    pt_reg->t_desc.ui4_app_group_id             = 0;
    pt_reg->t_desc.ui4_app_id                   = 0;
    pt_reg->t_desc.t_max_res.z_min_memory       = 1024 * 8;
    pt_reg->t_desc.t_max_res.z_max_memory       = 1024 * 32;
    pt_reg->t_desc.t_max_res.ui8_max_files_size = 0;
    pt_reg->t_desc.t_max_res.ui2_max_files      = 0;
    pt_reg->t_desc.t_max_res.ui2_max_handles    = 128;
    pt_reg->t_desc.t_max_res.ui2_max_threads    = 1;
    pt_reg->t_desc.t_max_res.ui2_max_semaphores = 4;
    pt_reg->t_desc.t_max_res.ui2_max_msg_queues = 1;
    pt_reg->t_desc.t_max_res.ui2_max_nb_msgs    = 300;
    pt_reg->t_desc.t_max_res.ui2_max_msg_size   = 512;
    pt_reg->t_desc.ui2_msg_count                = 300;
    pt_reg->t_desc.ui2_max_msg_size             = 512;
    pt_reg->at_system_keys[0].ui4_key_code      = 0;// no system keys
    pt_reg->at_system_keys[0].ui2_state_num     = 0;
    pt_reg->ui2_key_num                         = 0;

    BT_GATT_EXTI_FUNCTION();
    return;
}

// get dbg level
UINT16 bt_gatt_get_dbg_level(VOID)
{
    return bt_gatt_dbg_level;
}

// set dbg level
VOID bt_gatt_set_dbg_level(UINT16 ui2_db_level)
{
    bt_gatt_dbg_level = ui2_db_level;
}

CHAR * bt_gatt_get_session_token(VOID)
{
    return s_gattc_session_token;
}

static INT32 _bluetooth_gattc_ask_session(VOID)
{
    return a_rest_ask_session(s_gattc_cred, s_gattc_session_token, GATTC_SESSION_TOKEN_LEN+1);
}

static INT32 _bluetooth_gattc_dtv_msg_handle(BT_GATT_MSG_T *pt_msg)
{
    BT_DTV_MSG_TYPE e_dtv_msg = BT_DTV_MSG_LAST;

    if (NULL == pt_msg)
    {
        DBG_ERROR(("<BT_GATT> _bluetooth_gattc_dtv_msg_handle() NULL arg!\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    if (pt_msg->ui4_msg_id != BT_DTV_MSG_TO_GATT)
    {
        DBG_INFO(("<BT_GATT>_bluetooth_gattc_dtv_msg_handle() ignor message.\n"));
        return BLUETOOTH_GATTC_OK;
    }

    e_dtv_msg = (BT_DTV_MSG_TYPE)pt_msg->ui4_data1;
    switch (e_dtv_msg)
    {
        case BT_DTV_MSG_STOP_SCAN:
        {
            DBG_INFO(("<BT_GATT>_bluetooth_gattc_dtv_msg_handle() BT_DTV_MSG_STOP_SCAN.\n"));
            bluetooth_gattc_stop_scan_proc();
            b_dtv_force_stop_scan = TRUE;
            break;
        }
        case BT_DTV_MSG_START_SCAN:
        {
            DBG_INFO(("<BT_GATT>%d Message BT_DTV_MSG_START_SCAN b_dtv_force_stop_scan=%d\n",__LINE__,b_dtv_force_stop_scan));

            if (bluetooth_gatt_get_wake_on_ble_enable())
            {
                bluetooth_gatt_wake_on_ble_enable(FALSE);
            }

            b_dtv_force_stop_scan = FALSE;

            BT_GATT_MSG_T t_msg = {0};
            t_msg.ui4_msg_id    = BT_GATT_MSG_SCAN;
            //t_msg.ui4_data1     = bt_gatt_event;
            t_msg.ui4_data3     = NULL;
            bt_gatt_send_msg(BT_GATT_MSG_SCAN, &t_msg);

            break;
        }
        default:
        {
            DBG_INFO(("<BT_GATT>_bluetooth_gattc_dtv_msg_handle(),unknow dtv msg.\n"));
            break;
        }
    }

    return BLUETOOTH_GATTC_OK;
}

static INT32 _bluetooth_gattc_obtain_session_token_for_local_host(VOID)
{
    INT32 i4_ret = BLUETOOTH_GATTC_OK;
    INT32 i4_retry_count = 0;
    FILE* f_input_fd;
    INT32 i4_buf_size = GATTC_SESSION_TOKEN_LEN+1;
    CHAR buffer[GATTC_SESSION_TOKEN_LEN+1];
    c_memset(buffer, '\0', GATTC_SESSION_TOKEN_LEN+1);

    while(1) {
        f_input_fd = fopen ("/tmp/cred.dat", "r");
        if (f_input_fd == NULL) {
            if (i4_retry_count > 25) {
                DBG_LOG_PRINT(("<BT_GATT> err: meet retry count max\n\r"));
                //fclose (f_input_fd);
                return BLUETOOTH_GATTC_FAILED;
            }
            DBG_LOG_PRINT(("<BT_GATT> open /tmp/cred.dat failed, retry...\n\r"));
            sleep(1);
            i4_retry_count++;
        } else {
            break;
        }
    }

    if (fgets(buffer, i4_buf_size, f_input_fd) != NULL)
    {
        DBG_LOG_PRINT(("<BT_GATT> cred buffer:%s, strlen(buffer)=%d.\n\r", buffer, c_strlen(buffer)));

        if (c_strlen(buffer)!=0 && c_strlen(s_gattc_cred)!=0 && c_strcmp(buffer, s_gattc_cred)==0)
        {
            DBG_LOG_PRINT(("<BT_GATT> cred same as previous saved\n\r"));
            fclose (f_input_fd);
            return BLUETOOTH_GATTC_OK;
        }
        fclose (f_input_fd);

        c_memset(s_gattc_cred, '\0', GATTC_CRED_LEN+1);
        c_strncpy(s_gattc_cred, buffer, GATTC_CRED_LEN);
        char *pos;
        if ((pos = c_strchr(s_gattc_cred, '\n')) != NULL) {
            *pos = '\0';
        }
        DBG_LOG_PRINT(("<BT_GATT> s_gattc_cred:%s, strlen(buffer)=%d.\n\r", s_gattc_cred, c_strlen(s_gattc_cred)));

        if (_bluetooth_gattc_ask_session() == 0)
        {
            i4_ret = BLUETOOTH_GATTC_OK;
        }
        else
        {
            i4_ret = BLUETOOTH_GATTC_FAILED;
        }
    }
    else
    {
        DBG_LOG_PRINT(("<BT_GATT> err: get null\n\r"));
        fclose (f_input_fd);
        i4_ret = BLUETOOTH_GATTC_FAILED;
    }

    return i4_ret;
}
// one of the five app life circle functions, refer to function a_bluetooth_gattc_init()
static INT32 _bluetooth_gattc_init(const CHAR * ps_name,HANDLE_T h_app)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i4_ret;

#ifdef CLI_SUPPORT
    i4_ret = bt_gatt_cli_attach_cmd_tbl();
    if(i4_ret != CLIR_NOT_INIT && i4_ret != CLIR_OK)
    {
        DBG_ERROR(("<BT_GATT> error: bt_gatt_cli_attach_cmd_tbl() failed, ret=%ld\r\n", i4_ret));
        return BLUETOOTH_GATTC_FAILED;
    }
#endif // CLI_SUPPORT

    bt_gatt_set_dbg_level(DBG_INIT_LEVEL_APP_GATT);

    DBG_ERROR(("<BT_GATT> %s() is invoked - ps_name = %s, h_app = %d\r\n", __FUNCTION__, ps_name, h_app));

    // init application structue
    c_memset(&t_g_bt_gatt, 0, sizeof(BT_GATT_OBJ_T));
    t_g_bt_gatt.h_app = h_app;

    t_g_bt_gatt.b_app_init_ok = TRUE;

#ifndef SYS_BLUETOOTH_LAZY_INIT
    UINT8 ui1_odm_idx = 2;
    BOOL  ab_rssi_meter[5] = {TRUE,TRUE,TRUE,FALSE,FALSE};  /*the idx=0 is used for getting odm idx fail */

    // init bluetooth directly when bt init is not delayed
    a_bt_system_bootup_sequence_init();

#if SYS_BLE_SUPPORT
    //DBG_LOG_PRINT(("<BT_GATT> calling bt_aud_sendmsg_to_ble_gatt\r\n"));
    //i4_ret = 0;
    //i4_ret = bt_aud_sendmsg_to_ble_gatt(BT_MSG_TO_GATT_APP);
#endif
    a_cfg_custom_get_odm_idx(&ui1_odm_idx);
    a_bluetooth_gattc_rssi_meter_dialog_enable((ui1_odm_idx >= 0 && ui1_odm_idx <= 4) ? ab_rssi_meter[ui1_odm_idx] : TRUE);

#endif


    return BLUETOOTH_GATTC_OK;

}

// one of the five app life circle functions, refer to function a_bluetooth_gattc_init()
static INT32 _bluetooth_gattc_exit (HANDLE_T h_app,APP_EXIT_MODE_T e_exit_mode)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i4_ret;

    if (!t_g_bt_gatt.b_app_init_ok)
    {
        DBG_ERROR(("<BT_GATT> error: _bluetooth_gattc_init() is not called.\r\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    // call close && deinit function
    i4_ret = bluetooth_gatt_close_proc();
    BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_close_proc,i4_ret);
    bluetooth_gatt_deinit_proc();

    DBG_INFO(("<BT_GATT> %s() is invoked - h_app = %d e_exit_mode=%d\r\n", __FUNCTION__, h_app, e_exit_mode));

    t_g_bt_gatt.b_app_init_ok = FALSE;

    return BLUETOOTH_GATTC_OK;
}

// one of the five app life circle functions, refer to function a_bluetooth_gattc_init()
static INT32 _bluetooth_gattc_pause (HANDLE_T h_app)
{
    BT_GATT_ENTER_FUNCTION();

    if (!t_g_bt_gatt.b_app_init_ok)
    {
        DBG_ERROR(("<BT_GATT> error: _bluetooth_gattc_init() is not called.\r\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    DBG_INFO(("<BT_GATT> %s() is invoked - h_app = %d\r\n", __FUNCTION__, h_app));

    return BLUETOOTH_GATTC_OK;
}

// one of the five app life circle functions, refer to function a_bluetooth_gattc_init()
static INT32 _bluetooth_gattc_resume (HANDLE_T h_app)
{
    BT_GATT_ENTER_FUNCTION();

    if (!t_g_bt_gatt.b_app_init_ok)
    {
        DBG_ERROR(("<BT_GATT> error: _bluetooth_gattc_init() is not called.\r\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    // register callback functions
    bluetooth_gatt_init_proc();

    a_bt_gatt_cli_start_log_indicator_check();

    DBG_INFO(("<BT_GATT>%s() is invoked - h_app = %d\r\n", __FUNCTION__, h_app));

    return BLUETOOTH_GATTC_OK;
}

/*static INT32 _bluetooth_gattc_handle_ultility_app_msg(APPMSG_T * pv_msg)
{
    INT32 i4_ret = BLUETOOTH_GATTC_OK;
    APPMSG_T * pt_app_msg = (APPMSG_T*)pv_msg;


    switch(pt_app_msg->ui4_msg_type)
    {
        case SYSTEM_BOOT_UP_MSG:
        {
            DBG_ERROR(("<BT_GATT> system boot up,ble start scan ...\r\n"));
            b_allow_scan = TRUE;
            i4_ret = bluetooth_gattc_scan_proc();
            BT_GATT_CHECK_FAIL_RET(bluetooth_gattc_scan_proc, i4_ret);
            break;
        }

#if CONFIG_APP_SUPPORT_ULI
        case ULI_ON_MSG:
        {
            DBG_ERROR(("<BT_GATT> uli on,ble close proc ...\r\n"));
            i4_ret = bluetooth_gatt_close_proc();
            BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_close_proc,i4_ret);
            bluetooth_gatt_deinit_proc();
            break;
        }
#endif
       case BLUETOOTH_DONGLE_PLUGIN:
       {
            DBG_ERROR(("<BT_GATT> Enter function =%s, line=%d\r\n",__FUNCTION__, __LINE__));
            // register to mw our callback functions
            bluetooth_gatt_init_proc();

            // Wait system init done to scan (BOOT UP MSG)
#if 0
            //i4_ret = bluetooth_gattc_scan_proc();
            //BT_GATT_CHECK_FAIL_RET(bluetooth_gattc_scan_proc, i4_ret);
            // send msg to gatt app self
            //DBG_ERROR(("<BT_GATT> call ble gatt scan.\r\n", __FUNCTION__));
            BT_GATT_MSG_T t_msg = {0};
            t_msg.ui4_msg_id    = BT_GATT_MSG_SCAN;
            //t_msg.ui4_data1     = bt_gatt_event;
            t_msg.ui4_data3     = NULL;
            bt_gatt_send_msg(BT_GATT_MSG_SCAN, &t_msg);
#endif
            break;
        }
        default:
            DBG_ERROR(("<BT_GATT>Other message comes!\n"));
            break;
    }


    return i4_ret;

}*/

// one of the five app life circle functions, refer to function a_bluetooth_gattc_init()
static INT32 _bluetooth_gattc_process_msg (HANDLE_T h_app,UINT32 ui4_type,const VOID* pv_msg,SIZE_T z_msg_len,BOOL b_paused)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i4_ret;

    BT_GATT_MSG_T* pt_msg = (BT_GATT_MSG_T*) pv_msg;// get the msg

    if (!t_g_bt_gatt.b_app_init_ok)
    {
        DBG_ERROR(("<BT_GATT> error: _bluetooth_gattc_init() is not called.\r\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    if (ui4_type < AMB_BROADCAST_OFFSET)
    {
        /* private message */
        switch(pt_msg->ui4_msg_id)
        {
            case BT_GATT_MSG_EVENT:
                {
                    DBG_INFO(("<BT_GATT> BT_GATT_MSG_EVENT\r\n"));
                    i4_ret = bluetooth_gatt_event_msg_proc(pt_msg);// process the event from mw
                    BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_event_msg_proc,i4_ret);
                }
                break;

            case BT_GATT_MSG_INTRA:
                {
                    DBG_INFO(("<BT_GATT> BT_GATT_MSG_INTRA\r\n"));
                    i4_ret = bluetooth_gatt_intra_msg_proc(pt_msg);// process the event from gatt app self
                    if(i4_ret == BLUETOOTH_GATTC_FAILED)
                    {
                        b_can_scan = TRUE;
                    }
                    BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_intra_msg_proc,i4_ret);
                }
                break;

            case BT_GATT_MSG_SCAN:
                {
                    DBG_ERROR(("<BT_GATT> BLE start scan now...\r\n"));
                    b_allow_scan = TRUE;
                    i4_ret = bluetooth_gattc_scan_proc();
                    BT_GATT_CHECK_FAIL_RET(bluetooth_gattc_scan_proc, i4_ret);
                }
                break;

            case BT_MSG_TO_GATT_APP:
                {
                    c_thread_delay(3000);
                    DBG_INFO(("<BT_GATT> Message is %s @Line%d\n","BT_MSG_TO_GATT_APP",__LINE__));
                    _bluetooth_gattc_obtain_session_token_for_local_host();
                    // register to mw our callback functions
                    bluetooth_gatt_init_proc();

                    if (a_bgm_is_active_standby_state()
                        && FALSE == bluetooth_gatt_get_wake_on_ble_enable())
                    {
                        DBG_LOG_PRINT(("<BT_GATT> in Quick-start mode, enable woble.\r\n"));
                        bluetooth_gatt_wake_on_ble_enable(TRUE);
                    }

                    /*AC off with retail mode enabled, then AC ON to stop scan after init filer*/
                    if (b_dtv_force_stop_scan && a_bgm_is_active_standby_state() == FALSE)
                    {
                        DBG_ERROR(("<BT_GATT> BT_MSG_TO_GATT_APP, BLE DTV had force stop scan.\r\n"));
                        bluetooth_gattc_stop_scan_proc();
                    }
                    else
                    {
                        BT_GATT_MSG_T t_msg = {0};
                        t_msg.ui4_msg_id    = BT_GATT_MSG_SCAN;
                        //t_msg.ui4_data1     = bt_gatt_event;
                        t_msg.ui4_data3     = NULL;
                        bt_gatt_send_msg(BT_GATT_MSG_SCAN, &t_msg);
                    }

                    break;
                }
            case BT_GATT_TIMER_PROC:
                {
                    if (BT_GATT_TIMER_TASK_CHECK_LOG_INDICATOR == pt_msg->ui4_data1)
                    {
                        a_bt_gatt_cli_stop_log_indicator_check();
                        a_bt_gatt_cli_exec_cmd_from_file();
                        a_bt_gatt_cli_start_log_indicator_check();
                    }
                    break;
                }
            case BT_GATT_MSG_RSSI_METER:
                {
                    T_RSSI_NOTIFY_MSG t_rssi_nfy_msg;

                    if (NULL == pt_msg->ui4_data3)
                    {
                        DBG_INFO(("<BT_GATT> NULL rssi meter message\n"));
                        break;
                    }

                    c_memset(&t_rssi_nfy_msg, 0, sizeof(T_RSSI_NOTIFY_MSG));
                    c_memcpy(&t_rssi_nfy_msg, (T_RSSI_NOTIFY_MSG*)pt_msg->ui4_data3, sizeof(T_RSSI_NOTIFY_MSG));

                    if (pt_msg->ui4_data3 != NULL)
                    {
                        c_mem_free(pt_msg->ui4_data3);
                    }
                    a_bluetooth_gattc_rssi_meter_info_refresh(&t_rssi_nfy_msg);
                    break;
                }
            case BT_DTV_MSG_TO_GATT:
                {
                    /* This proceduer added for Retail mode enable, to stop bt scan until Retail mode disabled.
                    * If power off(ActiveStandby/ECO) with Retail mode enabled, bt scanning enabled automaticly by
                    * WakeOn filter settings.
                    * If DC On (AM_BRDCST_MSG_POWER_ON) with Retail mode enabled, not enable bt scanning.
                    * If AC On (BT_MSG_TO_GATT_APP) stop scan after filter inited.
                    */
                    _bluetooth_gattc_dtv_msg_handle(pt_msg);
                    break;
                }
            default:
                break;
        }
    }
    else if(ui4_type >= AMB_BROADCAST_APPMAN)
    {
        /* system message */
        switch(ui4_type)
        {
            case AM_BRDCST_MSG_POWER_ON:
                {
                    b_is_poweroff = FALSE;

                    if (b_dtv_force_stop_scan)
                    {
                        DBG_ERROR(("<BT_GATT> AM_BRDCST_MSG_POWER_ON, BLE DTV had force stop scan.\r\n"));
                    }
                    else
                    {
                        DBG_ERROR(("<BT_GATT> AM_BRDCST_MSG_POWER_ON, BLE start scan now...\r\n"));
                        bluetooth_gatt_wake_on_ble_enable(FALSE);

                        i4_ret = bluetooth_gattc_poweron_scan_proc();
                        BT_GATT_CHECK_FAIL_RET(bluetooth_gattc_poweron_scan_proc,i4_ret);
                    }
                }
                break;

            case AM_BRDCST_MSG_PRE_POWER_OFF:
                {
                    UINT32 ui4_eco = 0;

                    DBG_LOG_PRINT(("<BT_GATT> AM_BRDCST_MSG_PRE_POWER_OFF\r\n"));
                    a_cfg_custom_get_drv_eco_mode(&ui4_eco);
                    b_is_poweroff = TRUE;
                    i4_ret = bluetooth_gatt_close_proc();
                    BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_close_proc,i4_ret);
                    bluetooth_gatt_deinit_proc();
                    bluetooth_gatt_wake_on_ble_enable(TRUE);

                    if (1 == ui4_eco)
                    {
                        DBG_LOG_PRINT(("<BT_GATT> quick start\r\n"));

                        i4_ret = bluetooth_gattc_poweron_scan_proc();
                        BT_GATT_CHECK_FAIL_RET(bluetooth_gattc_poweron_scan_proc,i4_ret);
                    }
                }
                break;

            case AM_BRDCST_MSG_POWER_OFF:
                {
                    DBG_INFO(("<BT_GATT> AM_BRDCST_MSG_POWER_OFF\r\n"));
                    //i4_ret = bluetooth_gatt_close_proc();
                    //BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_close_proc,i4_ret);
                    //bluetooth_gatt_deinit_proc();
                }
                break;
            default:
                break;
        }
    }

    return BLUETOOTH_GATTC_OK;
}

INT32 bt_aud_sendmsg_to_ble_gatt(UINT32 ui4_msg)
{
    DBG_ERROR(("<BT_GATT> bluetooth send msg to ble gatt, cmd=%d.\r\n", ui4_msg));

    INT32 i4_ret = 0;
    BT_GATT_MSG_T t_msg = {0};

    t_msg.ui4_msg_id    = BT_MSG_TO_GATT_APP;

    // send msg to gatt app self
    i4_ret = c_app_send_msg(t_g_bt_gatt.h_app,
                    ui4_msg,
                    &t_msg,
                    sizeof(BT_GATT_MSG_T),
                    NULL,
                    NULL);

    BT_GATT_CHECK_FAIL_RET(c_app_send_msg,i4_ret);

    return BLUETOOTH_GATTC_OK;

}

// gatt app send msg
INT32 bt_gatt_send_msg(UINT32 ui4_msgtype, BT_GATT_MSG_T* pt_bt_msg)
{
    BT_GATT_ENTER_FUNCTION();

    INT32 i4_ret = 0;

    if ((HANDLE_T)NULL == t_g_bt_gatt.h_app)
    {
        DBG_ERROR(("<BT_GATT> error: t_g_bt_gatt.h_app is NULL.\r\n"));
        return BLUETOOTH_GATTC_FAILED;
    }

    //DBG_INFO(("<BT_GATT> send msg type = %d.\r\n", ui4_msgtype));

    // send msg to gatt app self
    i4_ret = c_app_send_msg(t_g_bt_gatt.h_app,
                    ui4_msgtype,
                    pt_bt_msg,
                    sizeof(BT_GATT_MSG_T),
                    NULL,
                    NULL);

    BT_GATT_CHECK_FAIL_RET(c_app_send_msg,i4_ret);

    return BLUETOOTH_GATTC_OK;
}

INT32 a_bluetooth_gattc_force_stop_scan(BOOL b_stop)
{
    BT_GATT_MSG_T t_msg = {0};
    t_msg.ui4_msg_id    = BT_DTV_MSG_TO_GATT;
    t_msg.ui4_data1     = b_stop ? BT_DTV_MSG_STOP_SCAN : BT_DTV_MSG_START_SCAN;
    t_msg.ui4_data3     = NULL;
    bt_gatt_send_msg(BT_DTV_MSG_TO_GATT, &t_msg);

    return CLIR_OK;
}

#endif