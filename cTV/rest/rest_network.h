#ifndef _REST_NETWORK_H_
#define _REST_NETWORK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <cJSON.h>

#include "app_util/a_common.h"
#include "rest_json.h"
#include "rest_cmd.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/
#define REST_ACCESS_POINT_LEN (32)
#define REST_IP_ADDRESS_LEN   (32)
#define REST_MAC_ADDRESS_LEN  (32)

/**
 * @brief This enum lists all network states.
 */
typedef enum _REST_NW_STATE_T
{
    REST_NETWORK_STATE_UNKNOWN,
    REST_NETWORK_STATE_WLAN_SCAN,
    REST_NETWORK_STATE_WLAN_ASSOCIATING,
    REST_NETWORK_STATE_WLAN_ASSOCIATED,
    REST_NETWORK_STATE_WLAN_DISASSOCIATING,
    REST_NETWORK_STATE_WLAN_DISASSOCIATED,
    REST_NETWORK_STATE_CONNECTION_TEST
}REST_NW_STATE_T;

typedef enum
{
    REST_NW_TEST_CONNECT_TEST = 0,
    REST_NW_TEST_SPEED_TEST,
    REST_NW_TEST_END
}REST_NW_CONN_TEST_STATUS;

typedef struct _REST_NW_TEST_CONNECTION_T{
    BOOL                        b_result;
    REST_NW_CONN_TEST_STATUS    e_status;
    REST_DATA_TEST_CONNECTION_T t_data;
}REST_NW_TEST_CONNECTION_T;

/**
    ERROR_CODE enum
    REST_NET_SUCCESS
        No networking error
    REST_NET_WIFI_MISSING_PASSWORD
        When t_ap_v1 is new, Ap is not open (encrypted), if "PASSWORD" in t_ap_v1 is empty string (""), will return this.
        When t_ap_v1 is old, Ap is not open (encrypted), if "VALUE" in set_wifi_password is empty string (""), will return this.
    REST_NET_WIFI_NOT_EXISTED
        When ssid is not matched in TV internal wifi list. Will return this.
    REST_NET_WIFI_ALREADY_CONNECTED
        When same AP already connected. Will return this.
    REST_NET_WIFI_NEEDS_VALID_SSID
        When client call set_wifi_password before calling current_access_point, will return this.
        When current_access_point is called but error returned, but client ignore it, then call set_wifi_password, will return this.
    REST_NET_WIFI_AUTH_REJECTED
        When connecting and there was a authentication rejected error, will return this.
    REST_NET_WIFI_CONNECT_TIMEOUT
        When connecting is timeout, will return this.
    REST_NET_WIFI_CONNECT_ABORTED
        When tv system abort/cancel this connecting, will return this
    REST_NET_WIFI_CONNECTION_ERROR
        Error occurring during connection for other than the above circumstances.
    REST_NET_IP_DHCP_FAILED
        DHCP server configuration failed.
    REST_NET_IP_MANUAL_CONFIG_ERROR
        Catch-all for Manual network config error.
    REST_NET_UNKNOWN_ERROR
        Unknown error (general error).
**/
typedef enum {
    REST_NET_EMPTY = 0,
    REST_NET_SUCCESS,
    REST_NET_WIFI_MISSING_PASSWORD = 10,
    REST_NET_WIFI_NOT_EXISTED,
    REST_NET_WIFI_ALREADY_CONNECTED,
    REST_NET_WIFI_NEEDS_VALID_SSID,
    REST_NET_WIFI_AUTH_REJECTED,
    REST_NET_WIFI_CONNECT_TIMEOUT,
    REST_NET_WIFI_CONNECT_ABORTED,
    REST_NET_WIFI_CONNECTION_ERROR,
    REST_NET_IP_DHCP_FAILED = 20,
    REST_NET_IP_MANUAL_CONFIG_ERROR,
    REST_NET_UNKNOWN_ERROR = 255
}REST_NET_ERR_CODE;

extern REST_DATA_WIFI_APS_T t_g_ap_list;
extern REST_DATA_TEST_CONNECTION_T t_g_test_result;

extern BOOL g_pin_google_success;


/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/
extern INT32 rest_network_get_error_str_with_id(const UINT16 ui2_id, CHAR* ps_error_string);
extern INT32 rest_network_update_error_code(REST_NET_ERR_CODE e_code);
extern VOID  rest_network_send_warning_msd(REST_NET_ERR_CODE e_code);

extern INT32 rest_network_register_notify(VOID);
extern INT32 rest_network_unregister_notify(VOID);
extern INT32 rest_cmd_get_wireless_access_points(cJSON *root);
extern INT32 rest_cmd_get_wifi_password(cJSON *root);
extern INT32 rest_cmd_get_ip_address(cJSON *root);
extern INT32 rest_cmd_test_network_connection(VOID);
extern INT32 rest_cmd_get_network_test_results(cJSON *root);
extern INT32 rest_cmd_get_current_access_point(cJSON *root);
extern INT32 rest_cmd_set_current_access_point(cJSON *jpackage, cJSON *root);
extern INT32 rest_cmd_set_wifi_password(cJSON *jpackage, cJSON *root);
extern INT32 rest_cmd_action_start_ap_search(cJSON *root);
extern INT32 rest_cmd_action_stop_ap_search(cJSON *root);
extern INT32 rest_cmd_get_nw_connection_type(cJSON *root);
extern INT32 rest_cmd_get_wifi_ssid(cJSON *root);
extern INT32 rest_cmd_get_wifi_security_type(cJSON *root);
extern INT32 rest_cmd_get_nw_gateway(cJSON *root);
extern INT32 rest_cmd_get_nw_subnet_mask(cJSON *root);
extern INT32 rest_cmd_get_nw_prefer_dns_server(cJSON *root);
extern INT32 rest_cmd_get_alternate_dns_server(cJSON *root);
extern INT32 rest_cmd_get_nw_download_speed(cJSON *root);
extern INT32 rest_cmd_get_signal_strength(cJSON *root);
extern INT32 rest_cmd_get_wifi_rssi(cJSON *root);
extern INT32 rest_cmd_get_wifi_channel(cJSON *root);
extern INT32 rest_cmd_get_rj45_mac_address(cJSON *root);
extern INT32 rest_cmd_get_wlan_mac_address(cJSON *root);
extern INT32 rest_cmd_get_bt_mac_address(cJSON *root);

extern INT32 rest_get_curr_access_point(REST_DATA_WIFI_AP_T *pt_ap);
extern INT32 rest_get_access_point_by_ssid(CHAR *ps_ssid, REST_DATA_WIFI_AP_T *pt_ap);
extern INT32 rest_get_curr_ap_security_type(CHAR *ps_security);
extern INT32 rest_update_ap_list_with_local_buff(VOID);

extern INT32 rest_set_wifi_ssid(CHAR *ps_ssid);
extern INT32 rest_get_wifi_ssid(CHAR *ps_ssid);
extern INT32 rest_wifi_associate(CHAR *ps_password);
extern INT32 rest_wifi_associate_ex(BOOL b_hidden, CHAR *ps_password);
extern INT32 rest_cmd_get_network_test_results_ex(VOID);
extern VOID  rest_test_interface();

extern VOID  rest_change_softap_channel_setting(INT16 i2_channel);

extern VOID  rest_change_softap_default_name(VOID);
extern VOID  rest_change_softap_name(CHAR* name);
extern VOID  rest_stop_softap(VOID);
extern VOID  rest_start_softap(VOID);
extern VOID  rest_start_softap_ex(VOID);
extern VOID rest_set_default_name(VOID);
extern INT32 rest_check_network_time();
extern VOID rest_no_ready_delay_notify_network_status();

extern VOID  rest_softap_power_on(VOID);
extern VOID rest_nw_set_is_hidden_notwork(BOOL is_hidden);

#ifdef __cplusplus
}
#endif

#endif
