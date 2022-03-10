#ifndef _REST_H_
#define _REST_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "c_dbg.h"
#include "app_util/a_common.h"
#include "app_util/a_network.h"
#include <semaphore.h>

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/* Rest Return value */
#define RESTR_OK                  0
#define RESTR_FAIL               -1
#define RESTR_INV_ARG            -2
#define RESTR_INV_STATE          -3
#define RESTR_OUT_OF_MEMORY      -4
#define RESTR_CANT_CREATE_WIDGET -5
#define RESTR_PAGE_NOT_FOUND     -6
#define RESTR_PAGE_INIT_FAIL     -7
#define RESTR_PAGE_INV_STATE     -8
#define RESTR_ITEM_NOT_FOUND     -9
#define RESTR_TOKEN_NOT_READY    -10
#define RESTR_CUSTOM_BASE        -256

#define REST_STR_EMPTY                  ""
#define REST_STR_VALUE                  "VALUE"
#define REST_STR_NAME                   "NAME"
#define REST_STR_SUCCESS                "SUCCESS"
#define REST_STR_TRUE                   "True"
#define REST_STR_FALSE                  "False"
#define REST_STR_LOCKED                 "locked"
#define REST_STR_ENABLED                "enabled"
#define REST_STR_RSSI                   "RSSI"
#define REST_STR_BAND                   "BAND"
#define REST_STR_EM                     "EM"
#define REST_STR_BSSID                  "BSSID"
#define REST_STR_CONNECTED              "CONNECTED"
#define REST_STR_ESTABLISHEDDNSSERVERS  "ESTABLISHEDDNSSERVERS"
#define REST_STR_ESTABLISHEDNTPSERVER   "ESTABLISHEDNTPSERVER"
#define REST_STR_CONNECTIONMETHOD       "CONNECTIONMETHOD"
#define REST_STR_CONNECTIONSPEED        "CONNECTIONSPEED"
#define REST_STR_SSIDNAME               "SSIDNAME"
#define REST_STR_NOT_AVAILABLE          "N/A"

//#ifdef SYS_VSSP_REST_SERVER_DEBUG
#define REST_STATIC_INDEX_HTML          "/3rd_rw/web_server/index.html"
//#else
//    #define REST_STATIC_INDEX_HTML          "/3rd/oobe/index.html"
//#endif
#define REST_STATIC_CONJURE_JSON          "/tmp/occs_extrainfo"
#define REST_STATIC_CONJURE_OVERLAY_JSON  "/tmp/system_ui.dat"

#ifdef SYS_VSSP_REST_SERVER_DEBUG
#define REST_CONFIG_FILE_DEFAULT        "/3rd_rw/rest_server/REST/sc-config.json"
#else
#define REST_CONFIG_FILE_DEFAULT        "/application/scfs/sc-config.json"
#endif
#define REST_CONFIG_FILE_DEFAULT_DEBUG  "/3rd_rw/rest_server/REST/sc-config.json"
#define REST_CONFIG_FILE_UPDATE         "/data/app/storage/scpl/sc-config.json"
#define REST_DEBUG_FLAG                 "/data/restap.print"

/* Assertion.*/
#ifdef DEBUG
    #define REST_ASSERT(cond)   assert(cond)
#else
    #define REST_ASSERT(cond)   if(cond){}
#endif

/* Return on error */
#define REST_CHK_FAIL(_ret)  \
do{ \
INT32 ret = _ret;   \
if (ret < 0)   \
{   \
    if(0)\
       DBG_LOG_PRINT(("<REST> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
    return RESTR_FAIL;  \
}   \
}while(FALSE)

#define REST_LOG_ON_FAIL(_ret)  \
do{ \
INT32 ret = _ret;   \
if (ret < 0)   \
{   \
    DBG_LOG_PRINT(("<REST> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
}   \
}while(FALSE)

#define REST_BREAK_ON_FAIL(_ret)  \
{ \
INT32 ret = _ret;   \
if (ret < 0)   \
{   \
    DBG_LOG_PRINT(("<REST> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
    break;  \
} \
}

/* rest Messages */
#define REST_MSG_WGL_NOTIFY      0
#define REST_MSG_ASYNC_INVOKE    1
#define REST_MSG_AM_ASYNC_INVOKE 2
#define REST_MSG_SHOW            3
#define REST_MSG_FACTORY_KEY     4
#define REST_REQ_CTX_SWITCH_EVENT 5
#define REST_MSG_AM_ASYNC_IPCC_CHG  6
#define REST_MSG_ASYNC_INIT  7
#define REST_MSG_CUSTOM_BASE     256

/* max message size */
#define REST_MAX_MSG_COUNT      32
#define REST_MAX_MSG_SIZE       128  //64

#define REST_CRED_LEN           (24)
#define REST_SESSION_TOKEN_LEN  (24)
//#define REST_CONFIG_FILE_LEN  ()

#define REST_MDNS_PORT 5353
#define REST_MDNS_PACKET_MAX_SIZE 65536

/* rest aysnchronous procedure */
typedef VOID (*rest_async_func)(VOID* pv_data,
                                SIZE_T  z_data_size);

/* Aysnchronous Invokcation */
#define REST_ASYNC_DATA_THRESHOLD   (REST_MAX_MSG_SIZE - 4)

typedef struct _REST_MSG_ASYNC_INVOKE_T {
    rest_async_func pf_async_func;
    UINT8           aui1_data[REST_ASYNC_DATA_THRESHOLD];
} REST_MSG_ASYNC_INVOKE_T;

typedef struct _REST_NW_NFY_DATA_T
{
    VOID*       pv_tag;
    NW_NFY_ID_T e_nfy_id;
    VOID*       pv_nfy_param;
} REST_NW_NFY_DATA_T;

typedef struct rest_mdns_packet
{
    UINT16 u2PktSize;
    UINT8* buffer;
}rest_mdns_packet_t;

typedef struct rest_mdns_server
{
    INT32 i4SockFd;
    pthread_mutex_t dataLock;
    pthread_t tid;
    rest_mdns_packet_t pkt;
}rest_mdns_server_t;

extern HANDLE_T h_timer_avoid_backdrop;
extern HANDLE_T h_timer_flash_led;
extern HANDLE_T h_timer_binary_update;
extern HANDLE_T h_timer_create_vtrl_ipt;
extern HANDLE_T h_timer_check_homekit_power_status;
extern HANDLE_T h_timer_airplay_launch;
extern HANDLE_T h_timer_oobe_sch_launch;
extern HANDLE_T h_timer_toast_nav;

extern int power_status;
extern sem_t  t_airplay_lock; //dolphin sem
extern sem_t  t_install_script_lock; //dolphin sem

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern UINT16 rest_get_dbg_level(VOID);
extern VOID rest_set_dbg_level(UINT16 ui2_db_level);
extern INT32 rest_async_invoke(rest_async_func  pf_async_func,
                        VOID*            pv_data,
                        SIZE_T           z_data_len,
                        BOOL             b_retry);
extern BOOL rest_get_session_token(CHAR* s_buffer, UINT16 ui2_size);
extern INT32 _rest_rewrite_static_index_html();
extern VOID _rest_app_set_connection_status(BOOL b_status);
BOOL _rest_app_get_connection_status(VOID);
extern VOID _rest_app_set_input_name_status(BOOL b_status);
extern BOOL _rest_app_get_input_name_status(VOID);
//extern BOOL _rest_is_cast_shell_ready();
extern BOOL _rest_app_is_cast_source(VOID);

//mdns
BOOL _rest_mdns_get_google_cid(CHAR* val);
INT32 _rest_mdns_create_recv_sock();
INT32 _rest_mdns_parse_google_cid(rest_mdns_packet_t *pkt);
INT32 _rest_mdns_start(void);

//extern INT32 _rest_cmd_cli_launch_by_keycode(INT32 key_code);
INT32 rest_ask_session();
extern int _rest_app_launch_cast_app_notify(char** active_app_ids, int active_app_num);
extern int _rest_app_cast_shell_ready();
extern BOOL _rest_can_notify_ready_to_cast(VOID);
extern void _rest_app_factory_reset();
void rest_set_python_reeady();
BOOL rest_get_python_ready ();
BOOL a_rest_is_conjure_install(VOID);
extern int a_rest_current_power_status();
INT16 rest_get_init_volume(VOID);
VOID rest_no_ready_delay_notify_input_list(VOID);
VOID rest_no_ready_delay_notify_input_enable_airplay(VOID);
VOID rest_set_sent_notify_input_list_while_python_ready(VOID);
BOOL rest_get_sent_notify_input_list_while_python_ready(VOID);

#ifdef __cplusplus
}
#endif

#endif

