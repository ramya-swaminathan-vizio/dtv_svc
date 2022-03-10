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
 #ifndef _BLUETOOTH_GATTC_H
 #define _BLUETOOTH_GATTC_H

/********************************************include files*********************************************/
 #include "amb/a_amb.h"

/************************************macros, defines, typedefs, enums***********************************/
// return value
#define		BLUETOOTH_GATTC_OK				0
#define 	BLUETOOTH_GATTC_FAILED			-1

// define log macros
#define DBG_INIT_LEVEL_APP_GATT 			(DBG_LEVEL_ERROR)
#undef  DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE                	bt_gatt_get_dbg_level()

#undef DBG_MODULE_NAME_PREFIX
#define DBG_MODULE_NAME_PREFIX              "GATTC APP"

#define BLUETOOTH_GATT_APP_NAME        		"bluetooth_gatt"
#define BLUETOOTH_GATT_STACK_SIZE          	(1024 * 32)

#define GATTC_CRED_LEN                       (24)
#define GATTC_SESSION_TOKEN_LEN              (24)

// define check macros
#define BT_GATT_CHECK_FAIL_RET(_func, _ret)   \
do{if (_ret != 0){DBG_ERROR(("<BT_GATT> error: "#_func" return error, ret=%d.\r\n", _ret));return BLUETOOTH_GATTC_FAILED;}}while(0)

#define BT_GATT_CHECK_FAIL(_func, _ret)   \
do{if (_ret != 0){DBG_ERROR(("<BT_GATT> error: "#_func" return error, ret=%d.\r\n", _ret));}}while(0)

#define BT_GATT_ENTER_FUNCTION() \
DBG_API(("<BT_GATT> Enter function =%s, line=%d\r\n",__FUNCTION__, __LINE__))

#define BT_GATT_EXTI_FUNCTION() \
DBG_API(("<BT_GATT> Exit function =%s, line=%d\r\n",__FUNCTION__, __LINE__))

#define BT_GATT_MALLOC(pvg, length) \
{if(pvg == NULL) {pvg = malloc(length);} else{DBG_INFO(("<BT_GATT> "#pvg" is not NULL\r\n"));}}

#define BT_GATT_FREE(pvg) \
{if(pvg != NULL) {free(pvg); pvg = NULL;} else{DBG_INFO(("<BT_GATT> "#pvg" is NULL\r\n"));}}

// message struct
typedef struct _BT_GATT_MSG_T
{
    UINT32          ui4_msg_id;
    UINT32          ui4_data1;
    UINT32          ui4_data2;
    VOID*	        ui4_data3;
} BT_GATT_MSG_T;

// application structure
typedef struct _BT_GATT_OBJ_T
{
	HANDLE_T	 h_app; 					 //app handle
	BOOL		 b_app_init_ok; 			 //app init ok flag

}BT_GATT_OBJ_T;

// message type
typedef enum{
	BT_GATT_MSG_EVENT = 1,// from mw event
	BT_GATT_MSG_INTRA,// from app event
	BT_GATT_MSG_SCAN,
    BT_MSG_TO_GATT_APP,
    BT_GATT_TIMER_PROC,
    BT_GATT_MSG_RSSI_METER,
    BT_DTV_MSG_TO_GATT,

	BT_GATT_MSG_MAX
}BT_GATT_MSG_TYPE_T;

// intra message type
typedef enum
{
    BT_GATT_SCAN_RESULT_CB = 0,
    BT_GATT_SEARCH_SERVICE_CB,
    BT_GATT_GET_CHAR_CB,
    BT_GATT_GET_DESC_CB,
    BT_GATT_READ_CHAR_CB,
    BT_GATT_WRITE_CHAR_CB,
    BT_GATT_WRITE_DESC_CB,
    BT_GATT_REG_NOTI_CB,
    BT_GATT_GET_DB_CB,
    BT_GATT_REG_APP_CB,
    BT_GATT_INTRA_MAX
}BTGATTIntra;

typedef enum
{
    BT_GATT_TIMER_TASK_CHECK_LOG_INDICATOR,
    BT_GATT_TIMER_TASK_LAST
}BT_GATT_TIMER_TASK;

typedef enum
{
    BT_DTV_MSG_STOP_SCAN,
    BT_DTV_MSG_START_SCAN,
    BT_DTV_MSG_LAST
}BT_DTV_MSG_TYPE;

/****************************************function declarations******************************************/
extern INT32 bt_audio_call_gatt_interface();
extern INT32 bt_gatt_cli_attach_cmd_tbl(VOID);
extern UINT16 bt_gatt_get_dbg_level(VOID);
extern VOID  bt_gatt_set_dbg_level(UINT16 ui2_db_level);
extern VOID  a_bluetooth_gattc_init(AMB_REGISTER_INFO_T* pt_reg);
extern INT32 bluetooth_gatt_close_proc(VOID);
extern VOID  bluetooth_gatt_deinit_proc(VOID);
extern INT32 bluetooth_gatt_init_proc(VOID);
extern INT32 bluetooth_gatt_event_msg_proc(const VOID *pv_msg);
extern INT32 bluetooth_gatt_intra_msg_proc(const VOID *pv_msg);
extern INT32 bluetooth_gattc_scan_proc(VOID);
extern INT32 bluetooth_gattc_stop_scan_proc(VOID);
extern INT32 bluetooth_gattc_poweron_scan_proc(VOID);
extern INT32 bt_gatt_send_msg(UINT32 ui4_msgtype, BT_GATT_MSG_T* pt_bt_msg);
extern INT32 bt_aud_sendmsg_to_ble_gatt(UINT32 ui4_msg);
extern INT32 bluetooth_gatt_scan_device_cli(VOID);
extern INT32 bluetooth_gatt_set_rssi_cli(int rssi_threshold);
extern INT32 bluetooth_gatt_get_rssi_cli(VOID);
extern INT32 bluetooth_gatt_stop_scan_cli(VOID);
extern INT32 bluetooth_gatt_connect_service_cli(char *mac_address);
extern INT32 bluetooth_gatt_get_put_cli(const char *url_json);
extern INT32 bluetooth_gatt_get_response_cli(const char *dir_path);
extern INT32 bluetooth_gatt_write_data_cli(int char_index, const char* write_str);
extern INT32 bluetooth_gatt_read_data_cli(int char_index);
extern INT32 bluetooth_gatt_security_data_cli(const char *message, int i_msd_key);
extern CHAR* bt_gatt_get_session_token(VOID);
extern INT32 bt_gattc_get_client_if(VOID);

extern INT32 a_bluetooth_gattc_force_stop_scan(BOOL b_stop);
#endif
#endif
