#ifndef _REST_CMD_H_
#define _REST_CMD_H_

#include "app_util/a_common.h"
#include "app_util/a_network.h"
#include "app_util/network/network.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define REST_DATA_BAND_LEN (12)
#define REST_DATA_EM_LEN (20)
#define REST_BSSID_LEN (20)
#define REST_SSID_MAX_LEN (NET_802_11_MAX_LEN_SSID)
#define REST_PASSWORD_LEN (128)
#define REST_DNS_LEN 16
#define REST_NTP_LEN 16
#define REST_CONN_METHOD_LEN 16
#define REST_ERROR_CODE (32)

#define REST_DEVICE_INFO_NAME_LEN 32
#define REST_DEVICE_INFO_NUM 9
#define REST_NW_CONN_TYPE_LEN (16)



#define REST_TV_APS_NUM_MAX (32)
#define REST_URI_MAX_LEN 127


#define SETTING_ROOT              "tv_settings"
#define URL_OOBE_IS_COMPLETE      "oobe/is_complete"
#define URL_OOBE_CURRENT_STATE    "oobe/currentstate"
#define URL_PAIRING_CHALLENGE     "pairing/correct_challenge_response"
#define URL_PAIRING_START         "pairing/start"
#define URL_PAIRING_END           "pairing/end"
#define URL_WIFI_SCAN_START       SETTING_ROOT"/network/start_ap_search"
#define URL_WIFI_SCAN_STOP        SETTING_ROOT"/network/stop_ap_search"
#define URL_WIFI_ACCESS_POINTS    SETTING_ROOT"/network/wireless_access_points"
#define URL_CURRENT_ACCESS_POINT  SETTING_ROOT"/network/current_access_point"
#define URL_SET_WIFI_PASSWORD     SETTING_ROOT"/network/set_wifi_password"
#define URL_DEVICE_NAME           SETTING_ROOT"/cast/device_name"
#define URL_TEST_RESULT           SETTING_ROOT"/network/test_connection/test_results"
#define URL_TOS_ACCEPTED          SETTING_ROOT"/cast/tos_accepted"
#define URL_DEVICE_INFO           SETTING_ROOT"/cast/device_info"
#define URL_STATE_DEVICEINFO      "state/device/deviceinfo"
#define URL_NW_CONNECTION_TYPE    SETTING_ROOT"/system/system_information/network_information/connection_type"
#define URL_WIFI_SSID             SETTING_ROOT"/system/system_information/network_information/ssid"
#define URL_WIFI_SECURITY_TYPE    SETTING_ROOT"/system/system_information/network_information/security_type"
#define URL_IP_ADDRESS            SETTING_ROOT"/system/system_information/network_information/ip_address"
#define URL_NW_GATEWAY            SETTING_ROOT"/system/system_information/network_information/gateway"
#define URL_NW_SUBNET_MASK        SETTING_ROOT"/system/system_information/network_information/subnet_mask"
#define URL_NW_PREFRE_DNS         SETTING_ROOT"/system/system_information/network_information/preferred_dns_server"
#define URL_NW_ALTER_DNS          SETTING_ROOT"/system/system_information/network_information/alternate_dns_server"
#define URL_NW_DOWNLOAD_SPEED     SETTING_ROOT"/system/system_information/network_information/download_speed"
#define URL_WIFI_SIGNAL_STRENGTH  SETTING_ROOT"/system/system_information/network_information/wifi_signal_strength"
#define URL_WIFI_RSSI             SETTING_ROOT"/system/system_information/network_information/rssi"
#define URL_WIFI_CHANNEL          SETTING_ROOT"/system/system_information/network_information/wifi_channel"
#define URL_RJ45_MAC              SETTING_ROOT"/system/system_information/network_information/rj45_mac_address"
#define URL_WLAN_MAC              SETTING_ROOT"/system/system_information/network_information/wlan_mac_address"
#define URL_BT_MAC                SETTING_ROOT"/system/system_information/network_information/bt_mac_address"

typedef enum _REST_CMD_E{
    REST_CMD_GET_OOBE_IS_COMPLETE = 0,
    REST_CMD_GET_OOBE_CURRENT_STATE,
    REST_CMD_GET_PAIRING_CHALLENGE,
    REST_CMD_GET_PAIRING_START,
    REST_CMD_GET_CURRENT_ACCESS_POINT,
    REST_CMD_GET_WIRELESS_ACCESS_POINTS,
    REST_CMD_GET_NETWORK_TEST_RESULTS,
    REST_CMD_GET_IP_ADDRESS,
    REST_CMD_GET_WIFI_PASSWORD,
    REST_CMD_GET_DEVICE_NAME,
    REST_CMD_GET_TOS_ACCEPTED,
    REST_CMD_GET_DEVICEINFO,
    REST_CMD_GET_NW_CONNECTION_TYPE,
    REST_CMD_GET_WIFI_SSID,
    REST_CMD_GET_WIFI_SECURITY_TYPE,
    REST_CMD_GET_NW_GATEWAY,
    REST_CMD_GET_NW_SUBNET_MASK,
    REST_CMD_GET_NW_PREFER_DNS_SERVER,
    REST_CMD_GET_NW_ALTERNATE_DNS_SERVER,
    REST_CMD_GET_NW_DOWDLOAD_SPEED,
    REST_CMD_GET_SIGNAL_STRENGTH,
    REST_CMD_GET_WIFI_RSSI,
    REST_CMD_GET_WIFI_CHANNEL,
    REST_CMD_GET_RJ45_MAC_ADDRESS,
    REST_CMD_GET_WLAN_MAC_ADDRESS,
    REST_CMD_GET_BT_MAC_ADDRESS,
    REST_CMD_SET_CURRENT_ACCESS_POINT,
    REST_CMD_SET_WIFI_PASSWORD,
    REST_CMD_SET_TOS_ACCEPTED,
    REST_CMD_SET_DEVICE_NAME,
    REST_CMD_SET_OOBE_IS_COMPLETE,
    REST_CMD_SET_OOBE_CURRENT_STATE,
    REST_CMD_ACTION_START_AP_SEARCH,
    REST_CMD_ACTION_STOP_AP_SEARCH,
    REST_CMD_ACTION_PAIRING_END,
    REST_CMD_LAST_ENTRY
}REST_CMD_E;

typedef enum _HTTP_REQ_TYPE_E{
    HTTP_REQ_GET,
    HTTP_REQ_SET,
    HTTP_REQ_RESET,
    HTTP_REQ_ACTION,
    HTTP_REQ_KEYCMD,
    HTTP_REQ_GETSTATUS,
    HTTP_REQ_MAX,
}HTTP_REQ_TYPE_E;

typedef struct _REST_UR_CMD_T{
    REST_CMD_E      e_cmd;
    HTTP_REQ_TYPE_E req_type;
    CHAR            s_uri[REST_URI_MAX_LEN];
}REST_URI_CMD_T;

typedef enum{
    E_AGENT_STATIC,
    E_AGENT_DYNAMIC,
    E_AGENT_KEYCMD,
    E_AGENT_STATE,
    E_AGENT_PAIRING,
}E_REST_REQ_TYPE;

typedef enum
{
    E_REST_KEY_ACTION_UP,       
    E_REST_KEY_ACTION_DOWN,
    E_REST_KEY_ACTION_PRESS,
}E_REST_KEY_ACTION;

typedef enum
{
    E_REST_KEY_CODESET_AUDIO,
    E_REST_KEY_CODESET_TRANSPORT,   
    E_REST_KEY_CODESET_ASCII,       
    E_REST_KEY_CODESET_KEYMODIFIER,
    E_REST_KEY_CODESET_DPAD,
    E_REST_KEY_CODESET_NAV,
    E_REST_KEY_CODESET_VIDEO,
    E_REST_KEY_CODESET_INPUT,
    E_REST_KEY_CODESET_CH,
    E_REST_KEY_CODESET_COLOR,   
    E_REST_KEY_CODESET_FACTORY,
    E_REST_KEY_CODESET_MAX,
}E_REST_KEY_CODESET;

typedef struct _REST_PAIR_T{
    BOOL b_pair_start;
    BOOL b_pair_auth;
}REST_PAIR_T;

typedef struct _REST_DATA_WIFI_AP_T{
    INT32 rssi;
    INT16 i2_Channel;
    CHAR band[REST_DATA_BAND_LEN];
    CHAR em[REST_DATA_EM_LEN];
    CHAR bssid[REST_BSSID_LEN];
    CHAR name[REST_SSID_MAX_LEN + 1];
    CHAR password[REST_PASSWORD_LEN+1];
    BOOL passwordReq;
}REST_DATA_WIFI_AP_T;

typedef struct _REST_DATA_WIFI_APS_T{
    BOOL   connected;
    SIZE_T ap_num;
    REST_DATA_WIFI_AP_T aplist[REST_TV_APS_NUM_MAX];
}REST_DATA_WIFI_APS_T;

typedef struct _REST_DATA_TEST_CONNECTION_T{
    DOUBLE conn_speed;
    CHAR dns[REST_DNS_LEN];
    CHAR ntp[REST_NTP_LEN];
    CHAR conn_method[REST_CONN_METHOD_LEN];
    CHAR ssid[REST_SSID_MAX_LEN + 1];
    CHAR err_code[REST_ERROR_CODE];
    BOOL reconnecting;
}REST_DATA_TEST_CONNECTION_T;

typedef struct _REST_DATA_DEVICE_INFO_T{
    CHAR Name[REST_DEVICE_INFO_NAME_LEN+1];
    CHAR SettingRoot[REST_DEVICE_INFO_NAME_LEN+1];
    CHAR ApiVersion[REST_DEVICE_INFO_NAME_LEN+1];
    CHAR HdmiInputs[REST_DEVICE_INFO_NUM][REST_DEVICE_INFO_NAME_LEN+1];   
    CHAR Capabitities[REST_DEVICE_INFO_NUM][REST_DEVICE_INFO_NAME_LEN+1];
}REST_DATA_DEVICE_INFO_T;

typedef enum _REST_DATA_LOCK_TYPE_E
{
    REST_DATA_LOCK_TYPE_NONE = 0,
    REST_DATA_LOCK_TYPE_FALSE,
    REST_DATA_LOCK_TYPE_TRUE,
    REST_DATA_LOCK_TYPE_LAST
}REST_DATA_LOCK_TYPE_E;

typedef enum _REST_DATA_ENABLE_TYPE_E
{
    REST_DATA_ENABLE_TYPE_NONE = 0,
    REST_DATA_ENABLE_TYPE_FALSE,
    REST_DATA_ENABLE_TYPE_TRUE,
    REST_DATA_ENABLE_TYPE_LAST
}REST_DATA_ENABLE_TYPE_E;

typedef struct _REST_DATA_PARAM_1_T
{
    INT32 i4_ret_code;
    REST_DATA_LOCK_TYPE_E e_lock_type;
    REST_DATA_ENABLE_TYPE_E e_enable_type;
}REST_DATA_PARAM_1_T;

typedef struct{
    BOOL hash_only;
    BOOL flat;
    BOOL help_text;
}T_REST_READ_REQ_CMD;

typedef struct{
    BOOL reset;
    INT32 hashval;
    VOID *value;
    SIZE_T value_size;
}T_REST_WRITE_REQ_CMD;

typedef struct{
    E_REST_KEY_ACTION codeset;
    INT32 code;
    E_REST_KEY_CODESET keyaction;
}T_REST_KEYCMD_REQ_CMD;

typedef struct{
    E_REST_REQ_TYPE cmd_type;
    CHAR uri[REST_URI_MAX_LEN+1];
    union
    {
        T_REST_READ_REQ_CMD read_cmd;
        T_REST_WRITE_REQ_CMD write_cmd;
        T_REST_KEYCMD_REQ_CMD key_cmd;
    }cmd_args;
}T_REST_CMD_INFO;

typedef struct{
    CHAR Name[REST_DEVICE_INFO_NAME_LEN+1];
}T_REST_DATA_TYPE_DEVICE;

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/ 
extern INT32 tv_cmd_do(HTTP_REQ_TYPE_E req_type,const char *uri,const char *cmd_package);


#endif



