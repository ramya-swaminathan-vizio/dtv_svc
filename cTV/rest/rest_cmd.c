#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <cJSON.h>

#include "c_dt.h"
#include "c_os.h"
#include "c_dbg.h"
#include "u_common.h"

#include "rest_ipc.h"
#include "rest.h"
#include "rest_ipc_handler.h"
#include "app_util/a_common.h"
#include "rest_cmd.h"
#include "rest_json.h"
#include "rest_network.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
//#include "wizard_anim/page/wzd_page_c4tv_setting.h"
#include "am/a_am.h"
#include "amb/a_amb.h"
#include "wizard2/a_wzd.h"
#include "rest_dbg_level.h"


static REST_PAIR_T g_rest_pair = {0};

static REST_URI_CMD_T at_uri_cmd[REST_CMD_LAST_ENTRY] = {
    {REST_CMD_GET_OOBE_IS_COMPLETE,       HTTP_REQ_GET, URL_OOBE_IS_COMPLETE},
    {REST_CMD_GET_OOBE_CURRENT_STATE,     HTTP_REQ_GET, URL_OOBE_CURRENT_STATE},
    {REST_CMD_GET_PAIRING_CHALLENGE,      HTTP_REQ_GET, URL_PAIRING_CHALLENGE},
    {REST_CMD_GET_PAIRING_START,          HTTP_REQ_GET, URL_PAIRING_START},
    {REST_CMD_GET_CURRENT_ACCESS_POINT,   HTTP_REQ_GET, URL_CURRENT_ACCESS_POINT},
    {REST_CMD_GET_WIRELESS_ACCESS_POINTS, HTTP_REQ_GET, URL_WIFI_ACCESS_POINTS},
    {REST_CMD_GET_NETWORK_TEST_RESULTS,   HTTP_REQ_GET, URL_TEST_RESULT},
    {REST_CMD_GET_IP_ADDRESS,             HTTP_REQ_GET, URL_IP_ADDRESS},
    {REST_CMD_GET_WIFI_PASSWORD,          HTTP_REQ_GET, URL_SET_WIFI_PASSWORD},
    {REST_CMD_GET_DEVICE_NAME,            HTTP_REQ_GET, URL_DEVICE_NAME},
    {REST_CMD_GET_TOS_ACCEPTED,           HTTP_REQ_GET, URL_TOS_ACCEPTED},
    {REST_CMD_GET_DEVICEINFO,             HTTP_REQ_GET, URL_STATE_DEVICEINFO},
    {REST_CMD_GET_NW_CONNECTION_TYPE,     HTTP_REQ_GET, URL_NW_CONNECTION_TYPE},
    {REST_CMD_GET_WIFI_SSID,              HTTP_REQ_GET, URL_WIFI_SSID},
    {REST_CMD_GET_WIFI_SECURITY_TYPE,     HTTP_REQ_GET, URL_WIFI_SECURITY_TYPE},
    {REST_CMD_GET_NW_GATEWAY,             HTTP_REQ_GET, URL_NW_GATEWAY},
    {REST_CMD_GET_NW_SUBNET_MASK,         HTTP_REQ_GET, URL_NW_SUBNET_MASK},
    {REST_CMD_GET_NW_PREFER_DNS_SERVER,   HTTP_REQ_GET, URL_NW_PREFRE_DNS},
    {REST_CMD_GET_NW_ALTERNATE_DNS_SERVER,HTTP_REQ_GET, URL_NW_ALTER_DNS},
    {REST_CMD_GET_NW_DOWDLOAD_SPEED,      HTTP_REQ_GET, URL_NW_DOWNLOAD_SPEED},
    {REST_CMD_GET_SIGNAL_STRENGTH,        HTTP_REQ_GET, URL_WIFI_SIGNAL_STRENGTH},
    {REST_CMD_GET_WIFI_RSSI,              HTTP_REQ_GET, URL_WIFI_RSSI},
    {REST_CMD_GET_WIFI_CHANNEL,           HTTP_REQ_GET, URL_WIFI_CHANNEL},
    {REST_CMD_GET_RJ45_MAC_ADDRESS,       HTTP_REQ_GET, URL_RJ45_MAC},
    {REST_CMD_GET_WLAN_MAC_ADDRESS,       HTTP_REQ_GET, URL_WLAN_MAC},
    {REST_CMD_GET_BT_MAC_ADDRESS,         HTTP_REQ_GET, URL_BT_MAC},
    
    {REST_CMD_SET_CURRENT_ACCESS_POINT,   HTTP_REQ_SET, URL_CURRENT_ACCESS_POINT},
    {REST_CMD_SET_WIFI_PASSWORD,          HTTP_REQ_SET, URL_SET_WIFI_PASSWORD},
    {REST_CMD_SET_TOS_ACCEPTED,           HTTP_REQ_SET, URL_TOS_ACCEPTED},
    {REST_CMD_SET_DEVICE_NAME,            HTTP_REQ_SET, URL_DEVICE_NAME},
    {REST_CMD_SET_OOBE_IS_COMPLETE,       HTTP_REQ_SET, URL_OOBE_IS_COMPLETE},
    {REST_CMD_SET_OOBE_CURRENT_STATE,     HTTP_REQ_SET, URL_OOBE_CURRENT_STATE},
    
    {REST_CMD_ACTION_START_AP_SEARCH,     HTTP_REQ_ACTION, URL_WIFI_SCAN_START},
    {REST_CMD_ACTION_STOP_AP_SEARCH,      HTTP_REQ_ACTION, URL_WIFI_SCAN_STOP},
    {REST_CMD_ACTION_PAIRING_END,         HTTP_REQ_ACTION, URL_PAIRING_END}
};



INT32 rest_cmd_get_oobe_is_complete(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = rest_pack_value_and_retcode("1", root, 0);
    REST_LOG_ON_FAIL(i4_ret);
    
    return i4_ret;
}

INT32 rest_cmd_get_oobe_current_state(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    
    i4_ret = rest_pack_value_and_retcode("\"\"", root, 0);
    REST_LOG_ON_FAIL(i4_ret);
    
    return i4_ret;
}

INT32 rest_cmd_get_pairing_challenge(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    CHAR  s_value[12] = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    if(g_rest_pair.b_pair_start && g_rest_pair.b_pair_auth)
    {
        c_strncpy(s_value, "TRUE", sizeof(s_value));
    }
    else
    {
        c_strncpy(s_value, "FALSE", sizeof(s_value));
    }

    i4_ret = rest_pack_value_and_retcode_only(s_value, root, 0);
    REST_LOG_ON_FAIL(i4_ret);
    
    return i4_ret;
}

INT32 rest_cmd_get_pairing_start(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = rest_pack_value_and_retcode_only("6", root, 0);
    REST_LOG_ON_FAIL(i4_ret);
    
    return i4_ret;
}

INT32 rest_cmd_get_device_name(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    CHAR s_tv_name[MAX_TV_NAME_LEN+1] = {0};
    SIZE_T  z_size = MAX_TV_NAME_LEN;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    
    a_cfg_custom_get_tv_name(s_tv_name, &z_size);
    i4_ret = rest_pack_device(s_tv_name, root, 0);
    REST_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

INT32 rest_cmd_get_tos_accepted(cJSON *root)
{
    BOOL b_tos   = FALSE;
    BOOL b_privacy = FALSE;
    BOOL b_tos_accept = FALSE;
    INT32 i4_ret = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    
    b_tos     = a_tv_custom_get_tos();
    b_privacy = a_tv_custom_get_privacy();
    if(b_tos && b_privacy)
    {
        b_tos_accept = TRUE;
    }
    
    i4_ret = rest_pack_tos_to_json(root, 0, b_tos_accept);
    REST_LOG_ON_FAIL(i4_ret);
    return i4_ret;
}

INT32 rest_cmd_get_deviceinfo(cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    INT32 i = 0;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    REST_DATA_DEVICE_INFO_T *pt_device_info = NULL;
    pt_device_info = c_mem_alloc(sizeof(REST_DATA_DEVICE_INFO_T));
    if (NULL == pt_device_info)
    {
        REST_ASSERT(0);
        return RESTR_OUT_OF_MEMORY;
    }
    
    c_memset(pt_device_info, 0, sizeof(REST_DATA_DEVICE_INFO_T));
    
    c_strcpy(pt_device_info->Name , "VIZIOSB-44");
    c_strcpy(pt_device_info->SettingRoot , SETTING_ROOT);
    c_strcpy(pt_device_info->ApiVersion , "1.0.7_1.0.6.4_0011");

    c_strcpy(pt_device_info->HdmiInputs[i++] , "cast");
    c_strcpy(pt_device_info->HdmiInputs[i++] , "aux1");
    c_strcpy(pt_device_info->HdmiInputs[i++] , "aux2");
    c_strcpy(pt_device_info->HdmiInputs[i++] , "digital3");
    c_strcpy(pt_device_info->HdmiInputs[i++] , "optical4");
    c_strcpy(pt_device_info->HdmiInputs[i++] , "hdmi5");
    c_strcpy(pt_device_info->HdmiInputs[i++] , "hdmiarc6");
    c_strcpy(pt_device_info->HdmiInputs[i++] , "bluetooth");
    c_strcpy(pt_device_info->HdmiInputs[i++] , "usb7");
    
    i = 0;
    c_strcpy(pt_device_info->Capabitities[i++] , "type:sb");
    c_strcpy(pt_device_info->Capabitities[i++] , "audio5.1");
    c_strcpy(pt_device_info->Capabitities[i++] , "vmin:0");
    c_strcpy(pt_device_info->Capabitities[i++] , "vmax:35");
    c_strcpy(pt_device_info->Capabitities[i++] , "vst:1");
    c_strcpy(pt_device_info->Capabitities[i++] , "dss5.1");

    i4_ret = rest_pack_deviceinfo(pt_device_info, root);
    REST_LOG_ON_FAIL(i4_ret);

    if (pt_device_info != NULL)
    {
        c_mem_free(pt_device_info);
        pt_device_info = NULL;
    }
    
    return i4_ret;
}

INT32 rest_cmd_set_tos_accepted(cJSON *jpackage, cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    T_REST_WRITE_REQ_CMD t_req;
    CHAR ps_resume_ap[APP_NAME_MAX_LEN+1] = {0};

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_req, 0, sizeof(T_REST_WRITE_REQ_CMD));
    i4_ret = rest_unpack_json_to_string_by_request_value(&t_req, jpackage, REST_STR_VALUE);
    if(i4_ret == 0 && t_req.value)
    {
        if(c_strcmp(t_req.value, "TRUE") == 0)
        {
            a_tv_custom_set_tos(TRUE);
            a_tv_custom_set_privacy(TRUE);
            i4_ret = a_am_get_active_app(ps_resume_ap);
            REST_LOG_ON_FAIL(i4_ret);

            /*
            if(strcmp(ps_resume_ap, WZD_NAME) == 0)
            {
                a_wzd_page_c4tv_setting_complete();
            }
            */
        }
    }

    if (t_req.value != NULL)
    {
        c_mem_free(t_req.value);
        t_req.value = NULL;
    }
    
    rest_pack_json_directly(root,i4_ret);
    return i4_ret;
}

INT32 rest_cmd_set_device_name(cJSON *jpackage, cJSON *root)
{
    INT32 i4_ret = RESTR_OK;
    T_REST_WRITE_REQ_CMD t_req;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    c_memset(&t_req, 0, sizeof(T_REST_WRITE_REQ_CMD));
    i4_ret = rest_unpack_json_device(&t_req, jpackage);
    if(i4_ret == 0 && t_req.value)
    {
        i4_ret = a_cfg_custom_set_tv_name(t_req.value);
        REST_LOG_ON_FAIL(i4_ret);
    }

    if (t_req.value != NULL)
    {
        c_mem_free(t_req.value);
        t_req.value = NULL;
    }

    rest_pack_json_directly(root,i4_ret);
    return i4_ret;
}

INT32 rest_cmd_set_oobe_current_state(cJSON *jpackage, cJSON *root)
{
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    
    rest_pack_json_directly(root, 0);
    return RESTR_OK;
}

INT32 rest_cmd_set_oobe_is_complete(cJSON *jpackage, cJSON *root)
{
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    
    rest_pack_json_directly(root, 0);
    return RESTR_OK;
}

INT32 rest_cmd_action_pairing_end(cJSON *root)
{
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    
    g_rest_pair.b_pair_auth = FALSE;
    g_rest_pair.b_pair_start = FALSE;
    rest_pack_json_directly(root, 0);
    return RESTR_OK;
}
    
INT32 tv_cmd_do(HTTP_REQ_TYPE_E req_type,const char *uri,const char *cmd_package)
{   
    INT32 i4_ret = 0;
    cJSON *root = cJSON_CreateObject(); 
    REST_MSG_TYPE type = REST_MSG_RESPONSE_FROM_TV;
    cJSON *jpackage = cJSON_Parse(cmd_package);
    UINT32 ui4_i = 0;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    
    for(ui4_i=0; ui4_i<REST_CMD_LAST_ENTRY; ui4_i++)
    {
        if ((c_strcmp(uri, at_uri_cmd[ui4_i].s_uri) == 0)
            &&(req_type == at_uri_cmd[ui4_i].req_type))
        {
            break;
        }
    }

    if (REST_CMD_LAST_ENTRY == ui4_i)
    {
        DBG_LOG_PRINT(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
        return -1; // whenever this API is called, check the return value to see if it failed. Coverity: 4490187 
    }

    DBG_LOG_PRINT(("\n%s,%s,%d,e_cmd=%d\n", 
                    __FILE__, __FUNCTION__, __LINE__, at_uri_cmd[ui4_i].e_cmd));

    switch(at_uri_cmd[ui4_i].e_cmd)
    {
        case REST_CMD_GET_OOBE_IS_COMPLETE:
            i4_ret = rest_cmd_get_oobe_is_complete(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_OOBE_CURRENT_STATE:
            i4_ret = rest_cmd_get_oobe_current_state(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_PAIRING_CHALLENGE:
            i4_ret = rest_cmd_get_pairing_challenge(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_PAIRING_START:
            i4_ret = rest_cmd_get_pairing_start(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_WIRELESS_ACCESS_POINTS:
            i4_ret = rest_cmd_get_wireless_access_points(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_CURRENT_ACCESS_POINT:
            i4_ret = rest_cmd_get_current_access_point(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_NETWORK_TEST_RESULTS:
            i4_ret = rest_cmd_get_network_test_results(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_IP_ADDRESS:
            i4_ret = rest_cmd_get_ip_address(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_WIFI_PASSWORD:
            i4_ret = rest_cmd_get_wifi_password(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_DEVICE_NAME:
            i4_ret = rest_cmd_get_device_name(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_TOS_ACCEPTED:
            i4_ret = rest_cmd_get_tos_accepted(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_DEVICEINFO:
            i4_ret = rest_cmd_get_deviceinfo(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_NW_CONNECTION_TYPE:
            i4_ret = rest_cmd_get_nw_connection_type(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_WIFI_SSID:
            i4_ret = rest_cmd_get_wifi_ssid(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_WIFI_SECURITY_TYPE:
            i4_ret = rest_cmd_get_wifi_security_type(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_NW_GATEWAY:
            i4_ret = rest_cmd_get_nw_gateway(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_NW_SUBNET_MASK:
            i4_ret = rest_cmd_get_nw_subnet_mask(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_NW_PREFER_DNS_SERVER:
            i4_ret = rest_cmd_get_nw_prefer_dns_server(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_NW_ALTERNATE_DNS_SERVER:
            i4_ret = rest_cmd_get_alternate_dns_server(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_NW_DOWDLOAD_SPEED:
            i4_ret = rest_cmd_get_nw_download_speed(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_SIGNAL_STRENGTH:
            i4_ret = rest_cmd_get_signal_strength(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_WIFI_RSSI:
            i4_ret = rest_cmd_get_wifi_rssi(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_WIFI_CHANNEL:
            i4_ret = rest_cmd_get_wifi_channel(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_RJ45_MAC_ADDRESS:
            i4_ret = rest_cmd_get_rj45_mac_address(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_WLAN_MAC_ADDRESS:
            i4_ret = rest_cmd_get_wlan_mac_address(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_GET_BT_MAC_ADDRESS:
            i4_ret = rest_cmd_get_bt_mac_address(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_SET_CURRENT_ACCESS_POINT:
            i4_ret = rest_cmd_set_current_access_point(jpackage, root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_SET_WIFI_PASSWORD:
            i4_ret = rest_cmd_set_wifi_password(jpackage, root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_SET_TOS_ACCEPTED:
            i4_ret = rest_cmd_set_tos_accepted(jpackage, root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_SET_OOBE_IS_COMPLETE:
            i4_ret = rest_cmd_set_oobe_is_complete(jpackage, root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_SET_DEVICE_NAME:
            i4_ret = rest_cmd_set_device_name(jpackage, root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_SET_OOBE_CURRENT_STATE:
            i4_ret = rest_cmd_set_oobe_current_state(jpackage, root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_ACTION_START_AP_SEARCH:
            i4_ret = rest_cmd_action_start_ap_search(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_ACTION_STOP_AP_SEARCH:
            i4_ret = rest_cmd_action_stop_ap_search(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;

        case REST_CMD_ACTION_PAIRING_END:
            i4_ret = rest_cmd_action_pairing_end(root);
            REST_LOG_ON_FAIL(i4_ret);
            break;
            
        default:
            rest_pack_json_directly(root, 0);
            break;
    }

    
    rest_notify(root, type, uri);
    cJSON_Delete(root);
    cJSON_Delete(jpackage);

    return i4_ret;
}





