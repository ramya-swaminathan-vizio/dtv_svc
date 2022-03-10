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
#include "c_cli.h"
#include "c_os.h"

#ifdef LINUX_TURNKEY_SOLUTION
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#endif

#include "stdlib.h"
#include "app_util/a_cfg.h"
#include "app_util/config/_acfg.h"
#include "res/app_util/config/acfg_cust_ble.h"
#include "app_util/a_cli_app.h"

#include <mtk_bt_service_gap_wrapper.h>

#include "bluetooth.h"
#include "bluetooth_gattc_rssimeter_view.h"
#include "bluetooth_gattc.h"
#include "bluetooth_gattc_wake.h"

#define MAX_CMD_NUM                                 (20)
#define LOG_INDICATOR_FILE_GATT                     "/3rd_rw/ble_log_cmd"
#define LOG_INDICATOR_FILE_GATT_BAK                 "/3rd_rw/ble_log_cmd.bak"

#define CHECK_LOG_INDICATOR_FILE_DELAY              (3000)

extern BOOL b_always_allow_test_tool_pair;

extern BOOL a_bgm_is_active_standby_state(VOID);


static HANDLE_T     h_g_timer = NULL_HANDLE;

static BOOL         b_rssi_meter = FALSE;

static BLE_CACHE_DEVICE * pui1_value = NULL;

#ifdef CLI_SUPPORT
static VOID _bt_gatt_log_indicator_timer_cb (HANDLE_T  h_timer, VOID *pv_data)
{
    DBG_INFO(("%s() Enter\r\n",__FUNCTION__));

    if (access(LOG_INDICATOR_FILE_GATT, 0) != 0)
    {
        DBG_INFO(("<BT_GATT> ble cmd file not exist (%s)!\n",LOG_INDICATOR_FILE_GATT));
        return;
    }

    if (a_bgm_is_active_standby_state())
    {
        return;
    }

    BT_GATT_MSG_T t_msg = {0};

    t_msg.ui4_msg_id    = (UINT32)BT_GATT_TIMER_PROC;
    t_msg.ui4_data1     = (UINT32)BT_GATT_TIMER_TASK_CHECK_LOG_INDICATOR;
    t_msg.ui4_data3		= NULL;
    bt_gatt_send_msg(BT_GATT_TIMER_PROC, &t_msg);

}
#endif

extern INT32 a_bt_gatt_cli_exec_cmd_from_file(VOID)
{
    INT32 i4_ret = BLUETOOTH_GATTC_OK;
#ifdef CLI_SUPPORT
    INT32 i4_cmd_num = 0;
#define CMD_LEN             (64)
    FILE  *fp = NULL;
    CHAR  str_temp[CMD_LEN] = {0};
    CHAR  str_cmd[128] = {0};

    if (access(LOG_INDICATOR_FILE_GATT, 0) != 0)
    {
        DBG_LOG_PRINT(("<BT_GATT> No ble cmd file(%s)!\n",LOG_INDICATOR_FILE_GATT));
        return i4_ret;
    }

    if ((fp = fopen(LOG_INDICATOR_FILE_GATT, "rw")) == NULL)
    {
        DBG_LOG_PRINT(("<BT_GATT> ble cmd file open fail (%s)!\n",LOG_INDICATOR_FILE_GATT));
        return i4_ret;
    }

    while (fgets(str_temp, CMD_LEN-1, fp) != NULL)
    {
        if (c_strlen(str_temp) == 0)
        {
            DBG_LOG_PRINT(("<BT_GATT> NULL command.\r\n"));
            continue;
        }

        if (i4_cmd_num >= MAX_CMD_NUM)
        {
            DBG_LOG_PRINT(("<BT_GATT> more command is ignored(>%d).\r\n", MAX_CMD_NUM));
            break;
        }

        i4_cmd_num++;

        DBG_LOG_PRINT(("<BT_GATT> get cli command %d =[%s] \r\n", i4_cmd_num, str_temp));

        if (c_strlen(str_temp) == 0
            || (c_strstr(str_temp, "gatt") == NULL
                && c_strstr(str_temp, "gt") == NULL
                && c_strstr(str_temp, "bluetooth") == NULL))
        {
            DBG_LOG_PRINT(("<BT_GATT> Not a ble cli command.\r\n", str_temp));
            continue;
        }

        DBG_LOG_PRINT(("<BT_GATT> exec command begin.\n"));
        i4_ret = c_cli_parser(str_temp);
        DBG_LOG_PRINT(("<BT_GATT> exec command end(%d).\n",i4_ret));

        if (i4_ret != CLIR_OK)
        {
            fclose(fp);
            fp = NULL;
            break;
        }

        c_memset(str_temp, 0 , CMD_LEN);
    }

    if (fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }

    sprintf(str_cmd, "mv %s %s", LOG_INDICATOR_FILE_GATT, LOG_INDICATOR_FILE_GATT_BAK);
    system(str_cmd);

#endif
    return i4_ret;
}

extern INT32 a_bt_gatt_cli_start_log_indicator_check(VOID)
{
#ifdef CLI_SUPPORT
    INT32       i4_ret = BLUETOOTH_GATTC_OK;

    if (NULL_HANDLE == h_g_timer)
    {
        i4_ret = c_timer_create(&h_g_timer);
        if (i4_ret != BLUETOOTH_GATTC_OK)
        {
            DBG_LOG_PRINT(("<BT_GATT> Create timer fail\n"));
            return i4_ret;
        }
    }

    if (h_g_timer != NULL_HANDLE)
    {
        c_timer_start(h_g_timer,
                      CHECK_LOG_INDICATOR_FILE_DELAY,
                      X_TIMER_FLAG_REPEAT,
                      _bt_gatt_log_indicator_timer_cb,
                      NULL);
    }
#endif
    return BLUETOOTH_GATTC_OK;
}

extern INT32 a_bt_gatt_cli_stop_log_indicator_check(VOID)
{
#ifdef CLI_SUPPORT
    if (h_g_timer != NULL_HANDLE)
    {
        c_timer_stop(h_g_timer);
    }
#endif
    return BLUETOOTH_GATTC_OK;
}

extern INT32 a_bt_app_init(VOID);
#ifdef CLI_SUPPORT
/**********************************structure, constants, macro definitions********************************/
extern INT32 bt_gatt_cli_attach_cmd_tbl(VOID);
static INT32 _bt_gatt_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_scan_device (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_set_rssi(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_get_rssi(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_stop_scan(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_get_put (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_get_response(INT32 i4_argc, const CHAR** pps_argv);
static INT32  _bt_gatt_cli_write_data (INT32 i4_argc, const CHAR** pps_argv);
static INT32  _bt_gatt_cli_read_data (INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_security_data(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_add_woble_sf(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_del_woble_sf(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_woble_enable(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_show_sf(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_show_rssi_meter(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_get_remote_name(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gatt_cli_set_rssi_meter_enable(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gattc_cli_rssi_meter_dialog_enable(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gattc_cli_set_allow_pair_4_test_tool(INT32 i4_argc, const CHAR** pps_argv);
static INT32 _bt_gattc_cli_force_stop_scan(INT32 i4_argc, const CHAR** pps_argv);

static INT32 _bt_gattc_cli_bt_init(INT32 i4_argc, const CHAR** pps_argv)
{
    a_bt_app_init();
    return 0;
}
// cli commands in gatt app
static CLI_EXEC_T bt_gatt_cmd_tbl[] =
{
	{
		"gdl",
		NULL,
		_bt_gatt_cli_get_dbg_level,
		NULL,
		CLI_GET_DBG_LVL_HELP_STR,
		CLI_ACCESS_RIGHT_APP_NW,
	},
	{
		"sdl",
		NULL,
		_bt_gatt_cli_set_dbg_level,
		NULL,
		CLI_SET_DBG_LVL_HELP_STR,
		CLI_ACCESS_RIGHT_APP_NW,
	},
	{
		"scan",
        NULL,
        _bt_gatt_cli_scan_device,
        NULL,
        "scan, stop_scan, open, search_service, get_char",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"set_rssi",
		NULL,
		_bt_gatt_cli_set_rssi,
		NULL,
		"set rssi threshold",
		CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"get_rssi",
		NULL,
		_bt_gatt_cli_get_rssi,
		NULL,
		"get rssi threshold",
		CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"stop_scan",
		NULL,
		_bt_gatt_cli_stop_scan,
		NULL,
		"stop scan",
		CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"get_put",
		NULL,
		_bt_gatt_cli_get_put,
		NULL,
		"httpc put json",
		CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"response",
		NULL,
		_bt_gatt_cli_get_response,
		NULL,
		"get response",
		CLI_ACCESS_RIGHT_APP_NW
	},
    {
        "write",
        NULL,
        _bt_gatt_cli_write_data,
        NULL,
        "client send data to server",
        CLI_ACCESS_RIGHT_APP_NW
    },
    {
        "read",
        NULL,
        _bt_gatt_cli_read_data,
        NULL,
        "client receive data from sever",
        CLI_ACCESS_RIGHT_APP_NW
    },
    {
		"security",
        NULL,
        _bt_gatt_cli_security_data,
        NULL,
        "client encrypt data for message",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"add_sf",
        NULL,
        _bt_gatt_cli_add_woble_sf,
        NULL,
        "add a scan filter for wake on BLE, usage:[CMD] type id data",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"del_sf",
        NULL,
        _bt_gatt_cli_del_woble_sf,
        NULL,
        "delete a scan filter for wake on BLE, usage:[CMD] type id data",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"show_sf",
        NULL,
        _bt_gatt_cli_show_sf,
        NULL,
        "show all scan filter dev info",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"woble",
        NULL,
        _bt_gatt_cli_woble_enable,
        NULL,
        "wake on BLE",
        CLI_ACCESS_RIGHT_APP_NW
	},
    {
		"rssi_meter",
        "rssim",
        _bt_gatt_cli_show_rssi_meter,
        NULL,
        "rssi meter",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"remote_name",
        "rn",
        _bt_gatt_cli_get_remote_name,
        NULL,
        "get remote device name(Ex.cell phone)",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
		"rssi_meter_enable",
        "rme",
        _bt_gatt_cli_set_rssi_meter_enable,
        NULL,
        "Enable rssi meter",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
        "rssi_show",
        "show",
        _bt_gattc_cli_rssi_meter_dialog_enable,
        NULL,
        "show rssi meter dialog",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
        "allow_pair_tool",
        "apt",
        _bt_gattc_cli_set_allow_pair_4_test_tool,
        NULL,
        "Always allow pair BLE tools",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
        "force_stop_scan",
        "fss",
        _bt_gattc_cli_force_stop_scan,
        NULL,
        "Always allow pair BLE tools",
        CLI_ACCESS_RIGHT_APP_NW
	},
	{
        "btinit",
        "btinit",
        _bt_gattc_cli_bt_init,
        NULL,
        "Always allow pair BLE tools",
        CLI_ACCESS_RIGHT_APP_NW
	},
 	END_OF_CLI_CMD_TBL
};

// gatt cli in application layer
static CLI_EXEC_T bt_gatt_root_cmd_tbl[] =
{
	{   "gatt",
	    "gt",
	    NULL,
	    bt_gatt_cmd_tbl,
	    "BLE proxy commands",
	    CLI_ACCESS_RIGHT_APP_NW
	},
	END_OF_CLI_CMD_TBL
};

// attach gatt cli to application layer
INT32 bt_gatt_cli_attach_cmd_tbl(VOID)
{
    return (c_cli_attach_cmd_tbl(bt_gatt_root_cmd_tbl, CLI_CAT_APP, CLI_GRP_GUI));
}

// get dbg level
static INT32 _bt_gatt_cli_get_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    INT32  i4_ret;

    i4_ret = c_cli_show_dbg_level(bt_gatt_get_dbg_level());

    return i4_ret;
}

// set dbg level
static INT32 _bt_gatt_cli_set_dbg_level (INT32 i4_argc, const CHAR** pps_argv)
{
    UINT16 ui2_dbg_level;
    INT32  i4_ret;

    i4_ret = c_cli_parse_dbg_level(i4_argc, pps_argv, &ui2_dbg_level);

    if (i4_ret == CLIR_OK)
	{
        bt_gatt_set_dbg_level(ui2_dbg_level);
    }

    return i4_ret;
}

// scan cli
static INT32 _bt_gatt_cli_scan_device (INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();

	INT32 i4_ret;

	i4_ret = bluetooth_gatt_scan_device_cli();
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_scan_device_cli, i4_ret);

	return BLUETOOTH_GATTC_OK;
}

// set_rssi cli
static INT32 _bt_gatt_cli_set_rssi(INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();

	INT32 i4_ret;

    INT32 rssi_threshold;

    if (i4_argc != 2)
    {
        DBG_ERROR(("<BT_GATT> %s() parameter number is not correct.\r\n", __FUNCTION__));
        return BLUETOOTH_GATTC_FAILED;
    }

    rssi_threshold = atoi(pps_argv[1]);

	i4_ret = bluetooth_gatt_set_rssi_cli(rssi_threshold);
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_set_rssi_cli, i4_ret);

	return BLUETOOTH_GATTC_OK;
}

// get_rssi cli
static INT32 _bt_gatt_cli_get_rssi(INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();

	INT32 i4_ret;

	i4_ret = bluetooth_gatt_get_rssi_cli();
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_get_rssi_cli, i4_ret);

	return BLUETOOTH_GATTC_OK;
}

// stop_scan cli
static INT32 _bt_gatt_cli_stop_scan(INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();

	INT32 i4_ret;

	i4_ret = bluetooth_gatt_stop_scan_cli();
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_stop_scan_cli, i4_ret);

	return BLUETOOTH_GATTC_OK;
}

// connect cli
static INT32 _bt_gatt_cli_get_put(INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();

	INT32 i4_ret;
	//int i = 0;
	//char temp_argv[500];

	if(i4_argc != 2)
	{
		DBG_ERROR(("<BT_GATT> %s() parameter number is not correct.\r\n", __FUNCTION__));
		return BLUETOOTH_GATTC_FAILED;
	}

	i4_ret = bluetooth_gatt_get_put_cli(pps_argv[1]);
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_get_put_cli,i4_ret);

	return BLUETOOTH_GATTC_OK;
}

// search service cli
static INT32 _bt_gatt_cli_get_response(INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();

	INT32 i4_ret;
	//int i = 1;

	if (i4_argc != 2)
    {
        DBG_ERROR(("<BT_GATT> %s() parameter number is not correct.\r\n", __FUNCTION__));
        return BLUETOOTH_GATTC_FAILED;
    }

	i4_ret = bluetooth_gatt_get_response_cli(pps_argv[1]);
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_get_response_cli, i4_ret);

	return BLUETOOTH_GATTC_OK;
}

// write cli
static INT32 _bt_gatt_cli_write_data(INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();

	INT32 i4_ret;

	INT32 characteristic_index;
	//int write_len = 0;
	//char *write_string = NULL;

    if (i4_argc != 3)
    {
        DBG_ERROR(("<BT_GATT> %s() parameter number is not correct.\r\n", __FUNCTION__));
        return BLUETOOTH_GATTC_FAILED;
    }

	characteristic_index = atoi(pps_argv[1]);
	if((characteristic_index > 80) && (characteristic_index != 255))
	{
		DBG_ERROR(("<BT_GATT> wrong number, number should between 0~80, and 255.\r\n"));
		return BLUETOOTH_GATTC_FAILED;
	}
	//write_len = strlen(pps_argv[2]);
	//write_string = (char*)malloc(write_len);
	//c_strncpy(write_string, pps_argv[2], write_len);
    //write_string[17] = '0';

	i4_ret = bluetooth_gatt_write_data_cli(characteristic_index, pps_argv[2]);
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_write_data_cli,i4_ret);

	//free(write_string);
	return BLUETOOTH_GATTC_OK;
}

// read cli
static INT32 _bt_gatt_cli_read_data(INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();


	INT32 i4_ret;

    INT32 characteristic_index;

    if (i4_argc != 2)
    {
        DBG_ERROR(("<BT_GATT> %s() parameter number is not correct.\r\n", __FUNCTION__));
        return BLUETOOTH_GATTC_FAILED;
    }

    characteristic_index = atoi(pps_argv[1]);

	i4_ret = bluetooth_gatt_read_data_cli(characteristic_index);
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_read_data_cli,i4_ret);

	return 0;
}

static INT32 _bt_gatt_cli_security_data(INT32 i4_argc, const CHAR** pps_argv)
{
	BT_GATT_ENTER_FUNCTION();


	INT32 i4_ret, key_sign = 0;

    if (i4_argc != 3)
    {
        DBG_ERROR(("<BT_GATT> %s() parameter number is not correct.\r\n", __FUNCTION__));
        return BLUETOOTH_GATTC_FAILED;
    }

	key_sign = atoi(pps_argv[2]);

	i4_ret = bluetooth_gatt_security_data_cli(pps_argv[1], key_sign);
	BT_GATT_CHECK_FAIL_RET(bluetooth_gatt_security_data_cli,i4_ret);

	return 0;
}

static INT32 _bt_gatt_cli_add_woble_sf(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT32 ui4_filter_type;
    UINT8 ui1_id;
    CHAR ac_info[SF_FILT_DATA_SIZE]={0};
    UINT16  i = 0;

    if (i4_argc != 4)
    {
        DBG_ERROR(("<BT_GATT><WAKE> Err:invalid argument.\r\n"));
        return CLIR_INV_ARG;
    }
    ui4_filter_type = atoi(pps_argv[1]);
    ui1_id = atoi(pps_argv[2]);
    c_strncpy(ac_info, pps_argv[3], SF_FILT_DATA_SIZE);
    ac_info[SF_FILT_DATA_SIZE - 1]=0;
    bluetooth_gatt_add_scan_filter(ui4_filter_type, //type
                                    ui1_id,         //target id
                                    ac_info);       //filt data
    if (NULL == pui1_value)
    {
        pui1_value = (BLE_CACHE_DEVICE*)c_mem_alloc(MAX_CACHE_BLE_NUMBER*sizeof(BLE_CACHE_DEVICE));
        c_memset(pui1_value, 0, (MAX_CACHE_BLE_NUMBER*sizeof(BLE_CACHE_DEVICE)));
    }

    if (pui1_value != NULL)
    {
        a_cfg_get_blegatt_macaddress_threshold(pui1_value);

        for (i = 0; i< MAX_CACHE_BLE_NUMBER; i++)
        {
            if (c_strncmp(pui1_value[i].c_mac_address, BLEGATT_MAC_ADDR_DEF, MAC_ADDRESS_LENGTH_LEN) == 0)
            {
                pui1_value[i].b_is_IOS = FALSE;
                pui1_value[i].ui_target_ID = ui1_id;
                c_strncpy(pui1_value[i].c_mac_address, ac_info, MAC_ADDRESS_LENGTH_LEN);

                a_cfg_set_blegatt_macaddress_threshold(pui1_value);
                break;
            }
        }
    }

    return CLIR_OK;
}
static INT32 _bt_gatt_cli_del_woble_sf(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT32 ui4_filter_type;
    UINT8 ui1_id;
    CHAR ac_info[SF_FILT_DATA_SIZE]={0};
    UINT16 i = 0;

    if (i4_argc != 4)
    {
        DBG_ERROR(("<BT_GATT><WAKE> Err:invalid argument.\r\n"));
        return CLIR_INV_ARG;
    }
    ui4_filter_type = atoi(pps_argv[1]);
    ui1_id = atoi(pps_argv[2]);
    c_strncpy(ac_info, pps_argv[3], SF_FILT_DATA_SIZE);
    ac_info[SF_FILT_DATA_SIZE - 1]=0;
    bluetooth_gatt_del_scan_filter(ui4_filter_type, //type
                                    ui1_id,         //target id
                                    ac_info);       //filt data

    if (NULL == pui1_value)
    {
        pui1_value = (BLE_CACHE_DEVICE*)c_mem_alloc(MAX_CACHE_BLE_NUMBER*sizeof(BLE_CACHE_DEVICE));
        c_memset(pui1_value, 0, (MAX_CACHE_BLE_NUMBER*sizeof(BLE_CACHE_DEVICE)));
    }

    if (pui1_value != NULL)
    {
        a_cfg_get_blegatt_macaddress_threshold(pui1_value);

        for (i = 0; i< MAX_CACHE_BLE_NUMBER; i++)
        {
            if (c_strncmp(pui1_value[i].c_mac_address, ac_info, MAC_ADDRESS_LENGTH_LEN) == 0)
            {
                pui1_value[i].b_is_IOS = FALSE;
                pui1_value[i].ui_target_ID = 0;
                c_memset(pui1_value[i].c_mac_address, 0, sizeof(pui1_value[i].c_mac_address));

                a_cfg_set_blegatt_macaddress_threshold(pui1_value);
                break;
            }
        }
    }

    return CLIR_OK;
}
static INT32 _bt_gatt_cli_show_sf(INT32 i4_argc, const CHAR** pps_argv)
{
    UINT16 i = 0;

    bluetooth_gatt_show_scan_filter();

    if (NULL == pui1_value)
    {
        pui1_value = (BLE_CACHE_DEVICE*)c_mem_alloc(MAX_CACHE_BLE_NUMBER*sizeof(BLE_CACHE_DEVICE));
        c_memset(pui1_value, 0, (MAX_CACHE_BLE_NUMBER*sizeof(BLE_CACHE_DEVICE)));
    }

    if (pui1_value != NULL)
    {
        a_cfg_get_blegatt_macaddress_threshold(pui1_value);

        for (i = 0; i< MAX_CACHE_BLE_NUMBER; i++)
        {
            DBG_LOG_PRINT(("<%d> %2d %2d %s\n",
                		    i,
                		    pui1_value[i].b_is_IOS,
                		    pui1_value[i].ui_target_ID,
                		    pui1_value[i].c_mac_address));
        }
    }

    return CLIR_OK;
}
static INT32 _bt_gatt_cli_woble_enable(INT32 i4_argc, const CHAR** pps_argv)
{
    BOOL b_enable;
    if (i4_argc != 2)
    {
        DBG_ERROR(("<BT_GATT><WAKE> Err:invalid argument.\r\n"));
        return CLIR_INV_ARG;
    }

    b_enable = atoi(pps_argv[1]);

	if (b_enable == TRUE)
	{
	    bluetooth_gatt_wake_on_ble_enable(TRUE);
	}
	else
	{
	    bluetooth_gatt_wake_on_ble_enable(FALSE);
	}
    return CLIR_OK;
}

static INT32 _bt_gatt_cli_show_rssi_meter(INT32 i4_argc, const CHAR** pps_argv)
{
    T_RSSI_METER t_rssi_meter;

    c_memset(&t_rssi_meter, 0, sizeof(t_rssi_meter));
    a_bluetooth_gattc_rssi_meter_show(&t_rssi_meter);

    return CLIR_OK;
}

static INT32 _bt_gatt_cli_get_remote_name(INT32 i4_argc, const CHAR** pps_argv)
{
    BLUETOOTH_DEVICE device_info;
    CHAR btaddr[MAX_BDADDR_LEN] = {0};
    BT_LOCAL_DEV local_dev;
    c_memset(&device_info,0,sizeof(BLUETOOTH_DEVICE));
    a_mtkapi_bt_gap_get_dev_info(&device_info,btaddr);

    DBG_LOG_PRINT(("remote name is [%s],addr:%s\n", device_info.name,btaddr));
    a_mtkapi_bt_gap_get_local_dev_info(&local_dev);

    DBG_LOG_PRINT(("local name is [%s],addr:%s\n", local_dev.name,local_dev.bdAddr));

    return CLIR_OK;
}

static INT32 _bt_gatt_cli_set_rssi_meter_enable(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc >= 2)
    {
        b_rssi_meter = (BOOL)atoi(pps_argv[1]);
        DBG_LOG_PRINT(("set rssi meter %s\n", b_rssi_meter ? "Enabled" : "Disabled"));
    }
    else
    {
        DBG_LOG_PRINT(("Invalid arg!\n"));
    }
    return CLIR_OK;
}
static INT32 _bt_gattc_cli_rssi_meter_dialog_enable(INT32 i4_argc, const CHAR** pps_argv)
{
    if (i4_argc >= 2)
    {
        BOOL b_rssi_enable = (BOOL)atoi(pps_argv[1]);
        a_bluetooth_gattc_rssi_meter_dialog_enable(b_rssi_enable);
        DBG_LOG_PRINT(("set rssi meter dialog show %s\n", b_rssi_enable ? "Enabled" : "Disabled"));
    }
    else
    {
        DBG_LOG_PRINT(("Invalid arg!\n"));
    }
    return CLIR_OK;
}

static INT32 _bt_gattc_cli_set_allow_pair_4_test_tool(INT32 i4_argc, const CHAR** pps_argv)
{
    INT32 i4_val = atoi(pps_argv[1]);

    b_always_allow_test_tool_pair = (i4_val == 0) ? FALSE : TRUE;
    DBG_LOG_PRINT(("Allow tools pair always turn %s\n", b_always_allow_test_tool_pair ? "True" : "False"));

    return CLIR_OK;
}

static INT32 _bt_gattc_cli_force_stop_scan(INT32 i4_argc, const CHAR** pps_argv)
{
    BOOL    b_stop = FALSE;

    if (i4_argc >= 1) b_stop = atoi(pps_argv[1]);

    BT_GATT_MSG_T t_msg = {0};
	t_msg.ui4_msg_id    = BT_DTV_MSG_TO_GATT;
	t_msg.ui4_data1     = b_stop ? BT_DTV_MSG_STOP_SCAN : BT_DTV_MSG_START_SCAN;
	t_msg.ui4_data3     = NULL;
	bt_gatt_send_msg(BT_DTV_MSG_TO_GATT, &t_msg);

    return CLIR_OK;
}

VOID bt_gatt_cli_set_allow_pair_4_test_tool(BOOL b_allow)
{
    b_always_allow_test_tool_pair = b_allow;
    DBG_LOG_PRINT(("Allow tools pair always turn %s\n", b_always_allow_test_tool_pair ? "True" : "False"));
    return;
}

BOOL bt_gatt_cli_get_rssi_meter_enable(VOID)
{
    return b_rssi_meter;
}
#endif
#endif