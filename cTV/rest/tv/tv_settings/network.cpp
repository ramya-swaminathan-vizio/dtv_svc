#include <iostream>
#include <bits/unique_ptr.h>
#include "network.h"
#include "handler.h"
#include "common.h"
#include <cJSON.h>
#include "argument.h"
#include <string.h>
#include <unistd.h>
#include "system.h"
#include "admin_and_privacy.h"


#ifdef __cplusplus
extern "C" {

#include "rest_network.h"
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "wizard_anim/a_wzd.h"

#include "rest_ipc.h"
#include "rest.h"
#include "rest_ipc_handler.h"
#include "app_util/a_common.h"
#include "rest_cmd.h"
#include "rest_json.h"
#include "rest/a_rest_event.h"

#include "nav/a_navigator.h"
#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_network_phase1/menu_network.h"
#include "c_uc_str.h"
#include "rest/rest_cmd.h"

}
#endif

extern REST_DATA_WIFI_APS_T t_g_ap_list;
extern REST_DATA_TEST_CONNECTION_T t_g_test_result;
extern REST_NW_CONN_TEST_STATUS e_g_nw_test_status;

TvSettingsGroupURI tvSettingsNetworkUri[] = {
        /*
        # NETWORK
        */

        { "connection_type" },
        { "connection_status" },
        { "current_ssid_name" },
        { "dhcp_mode" },
        { "ip_address" },
        { "subnet_mask" },
        { "default_gateway" },
        { "wireless_access_points" },
        { "current_access_point" },
        { "manual_setup" },
        { "manual_setup" , "dhcp" },
        { "manual_setup" , "ip_address" },
        { "manual_setup" , "subnet_mask" },
        { "manual_setup" , "default_gateway" },
        { "manual_setup" , "pref_dns_server" },
        { "manual_setup" , "alt_dns_server" },
        { "manual_setup" , "rj45_mac_address" },
        { "manual_setup" , "wireless_mac_address" },
        { "start_ap_search" },
        { "stop_ap_search" },
        { "set_wifi_password" },
        { "hidden_network" },
        { "hidden_network" , "name" },
        { "hidden_network" , "password" },
        { "test_connection" },
        { "test_connection" , "test_connection" },
        { "test_connection" , "test_connection_results" },
        { "test_connection" , "retest" },
        { "test_connection" , "manual_setup" , "dhcp" },
        { "test_connection" , "manual_setup" , "ip_address" },
        { "test_connection" , "manual_setup" , "subnet_mask" },
        { "test_connection" , "manual_setup" , "default_gateway" },
        { "test_connection" , "manual_setup" , "pref_dns_server" },
        { "test_connection" , "manual_setup" , "alt_dns_server" },
        { "test_connection" , "manual_setup" , "rj45_mac_address" },
        { "test_connection" , "manual_setup" , "wireless_mac_address" },

        { "" },

};

static BOOL b_g_in_test_connection = FALSE;
static BOOL b_internet_connected = FALSE;
static BOOL b_buffer_connection_status = FALSE;
static BOOL b_already_connect_test_connection = FALSE;

static VOID _rest_send_test_connection_msg(VOID)
{
    WDK_TOAST_T t_toast;
    UTF16_T     w2s_title[256]={0};
    UTF16_T     w2s_title_temp[256]={0};
    CHAR        s_temp[256] = {0};
    INT32       i4_ret = RESTR_OK;
    static BOOL b_1st_show_test_connection_osd = TRUE;

    /* do NOT show osd on oobe page */
    if (a_wzd_is_oobe_mode())
    {
        DBG_LOG_PRINT(("[KK] %s:%d, in OOBE.\n", __FUNCTION__, __LINE__));
        return;
    }

    if (b_1st_show_test_connection_osd)
    {
        b_1st_show_test_connection_osd = FALSE;
        rest_cmd_get_network_test_results_ex();
    }

    c_memset(w2s_title, 0, sizeof(w2s_title));

    if (c_strncmp(t_g_test_result.conn_method,"Ethernet",c_strlen("Ethernet"))==0)
    {
        c_uc_w2s_strncat(w2s_title, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_NET_CONNECT_TO_ETH), sizeof(w2s_title)/sizeof(w2s_title[0])-1);
        c_sprintf(s_temp,"\n");
        c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
        c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);
    }
    else if (c_strncmp(t_g_test_result.conn_method,"WiFi",c_strlen("WiFi"))==0)
    {
        c_uc_w2s_strncat(w2s_title, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_NET_CONNECT_TO_WIFI), sizeof(w2s_title)/sizeof(w2s_title[0])-1);
        c_sprintf(s_temp,": %s\n",t_g_test_result.ssid);
        c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
        c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);
    }
    else
    {
        c_sprintf(s_temp,"Connected to Unknown\n");
        c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
        c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);
    }

#if 0
    c_sprintf(s_temp,"DHCP: %s\n",s_dhcp_mode);
    c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
    c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);
#endif

    if (c_strncmp(t_g_test_result.conn_method,"WiFi",c_strlen("WiFi"))==0)
    {
        c_uc_w2s_strncat(w2s_title, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_NET_SIGNAL_STRENGTH), sizeof(w2s_title)/sizeof(w2s_title[0])-1);

        INT32   i4Rssi_avg = 0;
        NET_802_11_WIFI_RSSI_T      t_rssi;

        c_memset (&t_rssi, 0, sizeof(NET_802_11_WIFI_RSSI_T));
        i4_ret = a_nw_wlan_get_rssi(&t_rssi);
        if (i4_ret == 0)
        {
            i4Rssi_avg = t_rssi.i4Rssi_a;
            if (t_rssi.i4Rssi_b > -99)
            {
                i4Rssi_avg = (i4Rssi_avg + t_rssi.i4Rssi_b)/2;
            }
            if (t_rssi.i4Rssi_c > -99)
            {
                i4Rssi_avg = (i4Rssi_avg + t_rssi.i4Rssi_c)/2;
            }
        }
        c_sprintf(s_temp,": %d dBm\n", i4Rssi_avg);
        c_uc_ps_to_w2s(s_temp, w2s_title_temp,sizeof(w2s_title_temp));
        c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);
    }

    c_uc_w2s_strncat(w2s_title, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_NET_DNS), sizeof(w2s_title)/sizeof(w2s_title[0])-1);
    c_sprintf(s_temp,": %s        ",t_g_test_result.dns);
    c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
    c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);

    c_uc_w2s_strncat(w2s_title, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_NET_NTP), sizeof(w2s_title)/sizeof(w2s_title[0])-1);
    c_sprintf(s_temp,": %s\n",t_g_test_result.ntp);
    c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
    c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);

    c_uc_w2s_strncat(w2s_title, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_NET_DLD_SPEED), sizeof(w2s_title)/sizeof(w2s_title[0])-1);
    if (t_g_test_result.conn_speed < 0.01)
    {
        c_sprintf(s_temp, ": %s", REST_STR_NOT_AVAILABLE);
    }
    else
    {
        c_sprintf(s_temp, ": %.2f Kb/s", t_g_test_result.conn_speed);
    }
    c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
    c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);

    c_memset(&t_toast,0,sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_CENTER_DIALOG;
    t_toast.e_string_style = WDK_STRING_TITLE_CONTENT;
    t_toast.style.style_5.w2s_title_str = MENU_TEXT(MLM_MENU_KEY_NET_CFG_CONN_TEST);
    t_toast.style.style_5.w2s_content_str  = WGL_PACK(w2s_title);

    rest_send_msg_to_nav(&t_toast);
}

static VOID _rest_send_warning_msg(UTF16_T* pw2s_string)
{
    WDK_TOAST_T t_toast;

    c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

    t_toast.e_toast_style  = WDK_WARNING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;
    t_toast.style.style_4.w2s_str = (VOID*)pw2s_string;

    rest_send_msg_to_nav(&t_toast);
}

extern VOID rest_network_send_warning_msd(REST_NET_ERR_CODE e_code)
{
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    LOG_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

#ifdef APP_C4TV_SUPPORT
    if(WZD_STATE_RESUME_C4TV == ui1_state)
#else
    if (0)
#endif
    {
        REST_LOG_I("DO not show warning osd in OOBE!!!\n\r");
        return;
    }

    UTF16_T     w2s_string[256]={0};
    UTF16_T     w2s_string_temp[256]={0};

    c_memset(w2s_string, 0, sizeof(w2s_string));
    c_memset(w2s_string_temp, 0, sizeof(w2s_string_temp));

	switch (e_code)
	{
    case REST_NET_WIFI_NOT_EXISTED:
	    //
	    break;
	default:
	    //
	    break;
	}

    if (c_uc_w2s_strlen(w2s_string) == 0)
    {
        return;
    }

    _rest_send_warning_msg(w2s_string);
}

static INT32 _rest_get_ip_address(CHAR *ps_ip_address, UINT32 ui4_address)
{
    INT32 i4_ret = 0;
    UINT8 ui1_col = 0;
    CHAR  char_data[5] = {0};

    for(ui1_col= 0; ui1_col < 4; ui1_col++)
    {
        c_memset(char_data, 0, sizeof(char_data));
        c_sprintf(char_data,("%d\0"), (ui4_address>>(8*ui1_col))&0xFF);
        c_strncat(ps_ip_address, char_data, c_strlen(char_data));
        if (ui1_col < 3)
        {
            c_strncat(ps_ip_address, ".", sizeof(CHAR));
        }
    }

    return i4_ret;
}

static BOOL _rest_is_wifi_association_config_matched(const CHAR* ps_ssid, const CHAR* ps_key)
{
    NET_802_11_ASSOCIATE_T  t_Associate;
    INT32                   i4_ret = NAVR_OK;
    CHAR                    s_key[65] = {0};

    if (ps_ssid == NULL)
    {
        return FALSE;
    }

    c_memset(&t_Associate, 0, sizeof(NET_802_11_ASSOCIATE_T));
    c_memset(s_key, 0, sizeof(CHAR)*65);

    t_Associate.t_Key.pui1_PassPhrase = s_key;

    i4_ret = nw_custom_get_associate(&t_Associate);
    if (i4_ret != NWR_OK)
    {
        return FALSE;
    }

    /* check ssid is stored first */
    if (t_Associate.t_Ssid.ui4_SsidLen == 0 || 0 == c_strlen(t_Associate.t_Ssid.ui1_aSsid))
    {
        return FALSE;
    }

    if (0 == c_strncmp(ps_ssid, t_Associate.t_Ssid.ui1_aSsid, t_Associate.t_Ssid.ui4_SsidLen))
    {
        if (nw_custom_is_lock_ap(t_Associate.e_AuthMode,t_Associate.e_AuthCipher))
        {
            if (ps_key == NULL)
            {
                return FALSE;
            }

            if (0 == c_strncmp(ps_key, t_Associate.t_Key.pui1_PassPhrase, c_strlen(ps_key)))
            {
                return TRUE;
            }
            else
            {
                return FALSE;
            }
        }
        else
        {
            return TRUE;
        }
    }

    return FALSE;
}

static BOOL _rest_is_wifi_already_connected(const CHAR* ps_ssid)
{
    INT32                   i4_ret  = RESTR_OK;
    NW_WLAN_STATE_T         e_wlan_state = NW_WLAN_PLUG_STOP;
    NET_802_11_BSS_INFO_T   t_bss_info;
    NET_802_11_ASSOCIATE_T  t_Associate;

	/* need or not */
    i4_ret = a_nw_wlan_status(&e_wlan_state);
    if (i4_ret != NWR_OK)
    {
        return FALSE;
    }

    c_memset(&t_bss_info, 0, sizeof(t_bss_info));
    i4_ret = a_nw_wlan_get_curr_bss(&t_bss_info);
    if (i4_ret != NWR_OK)
    {
        return FALSE;
    }

    if (e_wlan_state != NW_WLAN_ASSOCIATE ||
        t_bss_info.t_Ssid.ui4_SsidLen == 0 ||
        t_bss_info.u8_wpa_status != (UINT8)WLAN_WPA_COMPLETED)
    {
        return FALSE;
    }

	c_memset(&t_Associate, 0, sizeof(NET_802_11_ASSOCIATE_T));

    i4_ret = nw_custom_get_associate(&t_Associate);

	if (t_Associate.e_AuthMode == IEEE_802_11_AUTH_MODE_OPEN 	||
		t_Associate.e_AuthMode == IEEE_802_11_AUTH_MODE_SHARED 	||
		t_Associate.e_AuthMode == IEEE_802_11_AUTH_MODE_WEPAUTO)
	{
        return FALSE;
	}

    if (NULL == ps_ssid)
    {
        return TRUE;
    }

    if (0 == c_strncmp(ps_ssid, t_bss_info.t_Ssid.ui1_aSsid, t_bss_info.t_Ssid.ui4_SsidLen))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

int connection_type(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    get_type(root);

    BOOL  b_ethernet = FALSE;
    CHAR  s_conn_type[REST_NW_CONN_TYPE_LEN+1] = {0};

    a_nw_get_ethernet_connect_info(&b_ethernet);

    if (b_ethernet)
    {
        c_strncpy(s_conn_type, "Ethernet", REST_NW_CONN_TYPE_LEN);
    }
    else
    {
        c_strncpy(s_conn_type, "Wi-Fi", REST_NW_CONN_TYPE_LEN);
    }

    response["VALUE"] = std::string(s_conn_type);

    return 0;
}

bool test_connection_status()
{
    BOOL            b_connected  = FALSE;
    BOOL            b_dhcp       = FALSE;
    NW_DHCP_STATE_T e_dhcp_state = NW_DHCP_FAILED;

    REST_LOG_I("Enter\n\r");

    // TODO(steven): need more info ?
    nw_custom_get_auto_ip_config(&b_dhcp);
    if (!b_dhcp)
    {
        b_connected = TRUE;
    }
    else
    {
        a_nw_get_dhcp_status(&e_dhcp_state);
        if ((NW_DHCP_STARTED == e_dhcp_state))
        {
            b_connected = TRUE;
        }
    }

    REST_LOG_I("Test result: %d\n\r", b_connected);
#if 0
    if (b_connected) {
        _rest_app_set_connection_status(TRUE);
    } else {
        _rest_app_set_connection_status(FALSE);
    }
#else
    if (b_connected == FALSE) {
        _rest_app_set_connection_status(FALSE);
    }
#endif
    return b_connected;
}

int connection_status(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    get_type(root);
    CHAR s_conn_status[REST_NW_CONN_TYPE_LEN+1] = {0};
    BOOL b_is_connect = FALSE;

    a_nw_is_network_connected(&b_is_connect);
    REST_LOG_I("b_is_connect: %d\n\r", b_is_connect);

    if (b_is_connect)
    {
        _rest_app_set_connection_status(TRUE);
        c_strncpy(s_conn_status, "Connected", REST_NW_CONN_TYPE_LEN);
    }
    else
    {
        _rest_app_set_connection_status(FALSE);
        c_strncpy(s_conn_status, "Disconnected", REST_NW_CONN_TYPE_LEN);
    }

    response["VALUE"] = std::string(s_conn_status);
    return 0;

}

int current_ssid_name(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    get_type(root);

    NET_802_11_BSS_INFO_T t_CurrBss;
    CHAR  s_ssid[REST_SSID_MAX_LEN+1] = {0};


    c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
    a_nw_wlan_get_curr_bss(&t_CurrBss);


    if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
    {
        c_strncpy(s_ssid, t_CurrBss.t_Ssid.ui1_aSsid, REST_SSID_MAX_LEN);
    }
    else
    {
        c_strcpy(s_ssid, REST_STR_NOT_AVAILABLE);
    }

    response["VALUE"] = std::string(s_ssid);

    return 0;

}

int dhcp_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = get_type(root);
    CHAR  str[64] = {0};

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            UINT8           ui1_dhcp_status = ACFG_DHCP_OFF;
            BOOL            b_auto_ip = FALSE;

            nw_custom_get_auto_ip_config(&b_auto_ip);
            if (b_auto_ip)
            {
                c_strncpy(str, "On", c_strlen("On"));
            }
            else
            {
                nw_custom_get_dhcp_status(&ui1_dhcp_status);

                if (ACFG_DHCP_OFF == ui1_dhcp_status)
                {
                    c_strncpy(str, "Off", c_strlen("Off"));
                }
                else if (ACFG_DHCP_DNS_ONLY == ui1_dhcp_status)
                {
                    c_strncpy(str, "Manual DNS", c_strlen("Manual DNS"));
                }
                else
                {
                    c_strncpy(str, REST_STR_EMPTY, c_strlen(REST_STR_EMPTY));
                }
            }

            string_set_response(response, str);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            NW_IP_INFO_T t_ip_info = {0};
            INT32   i4_ret = 0;

            c_memset(&t_ip_info, 0, sizeof(NW_IP_INFO_T));

            string_get_string(root, str, 64);

            DBG_LOG_PRINT(("[REST][INFO][API:%s-%d] --> %s\n\r", __FUNCTION__, __LINE__, str));

            if(c_strcmp(str, "On") == 0)
            {
                i4_ret = a_nw_start_dhcp_ip_config();
                LOG_ON_ERR(i4_ret);

                i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_OFF);
                LOG_ON_ERR(i4_ret);
            }
            else if(c_strcmp(str, "Off") == 0)
            {
                i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
                LOG_ON_ERR(i4_ret);

                i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_OFF);
                LOG_ON_ERR(i4_ret);

                i4_ret = a_nw_manual_ip_config(&t_ip_info);
                if (NWR_OK != i4_ret)
                {
                    i4_ret = nw_custom_set_auto_ip_config(FALSE);
                    LOG_ON_ERR(i4_ret);
                }
            }
            else if(c_strcmp(str, "Manual DNS") == 0)
            {
                i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
                LOG_ON_ERR(i4_ret);

                i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_DNS_ONLY);
                LOG_ON_ERR(i4_ret);

                i4_ret = a_nw_manual_ip_config(&t_ip_info);
                if (NWR_OK != i4_ret)
                {
                    i4_ret = nw_custom_set_auto_ip_config(FALSE);
                    LOG_ON_ERR(i4_ret);
                }
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

int ip_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            CHAR  s_ip_address[REST_IP_ADDRESS_LEN+1] = {0};
            NW_IP_INFO_T t_ip_info = {0};

            a_nw_custom_get_ip_info(&t_ip_info);

            _rest_get_ip_address(s_ip_address, t_ip_info.ui4_address);

            REST_LOG_I("IP: %s\n\r", s_ip_address);

            response["VALUE"]=std::string(s_ip_address);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int subnet_mask(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            NW_IP_INFO_T t_ip_info = {0};
            INT32 i4_ret = 0;
            CHAR  s_subnet_mask[REST_IP_ADDRESS_LEN+1] = {0};

            REST_LOG_I("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);

            i4_ret = a_nw_custom_get_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_subnet_mask, t_ip_info.ui4_netmask);
            LOG_ON_ERR(i4_ret);

            response["VALUE"]=std::string(s_subnet_mask);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int default_gateway(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            NW_IP_INFO_T t_ip_info = {0};
            INT32 i4_ret = 0;
            CHAR  s_gateway[REST_IP_ADDRESS_LEN+1] = {0};

            i4_ret = a_nw_custom_get_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_gateway, t_ip_info.ui4_gw);
            LOG_ON_ERR(i4_ret);

            response["VALUE"]=std::string(s_gateway);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int wireless_access_points(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 i = 0;
    Json::Value items;

    /* need update ap list */
    if (t_g_ap_list.connected != _rest_is_wifi_already_connected(NULL))
    {
        REST_LOG_I("[KK] %s:%d, need update ap list.\n", __FUNCTION__, __LINE__);
        rest_update_ap_list_with_local_buff();
    }

    for (; i<(INT32)t_g_ap_list.ap_num;i++)
    {
        REST_DATA_WIFI_AP_T *ap = &(t_g_ap_list.aplist[i]);
        Json::Value item;

        item["NAME"] = std::string(ap->name);
        item["RSSI"] = ap->rssi;
        item["BAND"] = std::string(ap->band);
        item["EM"] = std::string(ap->em);
        item["BSSID"] = std::string(ap->bssid);
        item["PASSWORDREQ"] = (ap->passwordReq ? "TRUE" : "FALSE");

        if (i==0)
        {
            item["CONNECTED"] = (t_g_ap_list.connected ? "TRUE" : "FALSE");
        }

        REST_LOG_I("Item[%d], [NAME]=%s, [RSSI]=%d, [BAND]=%s, [EM]=%s, [BSSID]=%s, [PASSWORDREQ]=%s\n\r",
                   i, ap->name, ap->rssi, ap->band, ap->em, ap->bssid, (ap->passwordReq ? "TRUE": "FALSE"));

        items[i] = item;
    }

    response["VALUE"] = items;

    return 0;
}

int current_access_point(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value item;
            Json::Value items;

            REST_DATA_WIFI_AP_T t_ap;
            CHAR s_ssid[REST_SSID_MAX_LEN + 1] = {0};

            c_memset(&t_ap, 0, sizeof(t_ap));
            i4_ret = rest_get_curr_access_point(&t_ap);
            if (i4_ret != RESTR_OK)
            {
                DBG_LOG_PRINT(("\n OOBE[NW] no wifi current connected [%s, %s, %d]\n", __FILE__, __FUNCTION__, __LINE__));
				item["NAME"] = std::string(REST_STR_EMPTY);
                item["RSSI"] = 0;
                item["BAND"] = std::string(REST_STR_EMPTY);
                item["EM"] = std::string(REST_STR_EMPTY);
                item["BSSID"] = std::string(REST_STR_EMPTY);
                #if 0
                rest_get_wifi_ssid(s_ssid);
                if (c_strlen(s_ssid) == 0)
                {
                    item["NAME"] = std::string(REST_STR_EMPTY);
                    item["RSSI"] = 0;
                    item["BAND"] = std::string(REST_STR_EMPTY);
                    item["EM"] = std::string(REST_STR_EMPTY);
                    item["BSSID"] = std::string(REST_STR_EMPTY);
                }
                else
                {
                    i4_ret = rest_get_access_point_by_ssid(s_ssid, &t_ap);
                    if (i4_ret != RESTR_OK || b_internet_connected ==FALSE)
                    {
                        item["NAME"] = std::string(REST_STR_EMPTY);
                        item["RSSI"] = 0;
                        item["BAND"] = std::string(REST_STR_EMPTY);
                        item["EM"] = std::string(REST_STR_EMPTY);
                        item["BSSID"] = std::string(REST_STR_EMPTY);
                    }
                    else
                    {
                        item["NAME"] = std::string(t_ap.name);
                        item["RSSI"] = t_ap.rssi;
                        item["BAND"] = std::string(t_ap.band);
                        item["EM"] = std::string(t_ap.em);
                        item["BSSID"] = std::string(t_ap.bssid);
                   }
                }
				#endif
            }
            else
            {
                DBG_LOG_PRINT(("\n OOBE[NW] wifi is currently connected [%s, %s, %d]\n", __FILE__, __FUNCTION__, __LINE__));
                item["NAME"] = std::string(t_ap.name);
                item["RSSI"] = t_ap.rssi;
                item["BAND"] = std::string(t_ap.band);
                item["EM"] = std::string(t_ap.em);
                item["BSSID"] = std::string(t_ap.bssid);
            }

            items[0] = item;

            response["VALUE"] = items;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            CHAR ap_name[REST_SSID_MAX_LEN + 1] = {0};
            REST_DATA_WIFI_AP_T t_ap;
            BOOL b_pwd_is_null = FALSE;

            Json::Value item;
            Json::Value item1;
            Json::Value item2;
            Json::Value jsonName;
            Json::Value jsonPwd;

            item2 = root["message"];
            item1 = item2["VALUE"];
            item = item1[0];
            jsonName = item["NAME"];
            jsonPwd = item["PASSWORD"];

            c_memset(ap_name, 0, sizeof(ap_name));
            if (!jsonName.isNull())
            {
                c_strcpy(ap_name, jsonName.asString().c_str());
                ap_name[REST_SSID_MAX_LEN] = 0;
            }
            else
            {
                DBG_LOG_PRINT(("%s, %d, ssid name is empty!", __FUNCTION__, __LINE__));

                rest_network_update_error_code(REST_NET_WIFI_NOT_EXISTED);

                return 0;
            }

            c_memset(&t_ap, 0, sizeof(REST_DATA_WIFI_AP_T));
            i4_ret = rest_get_access_point_by_ssid(ap_name, &t_ap);
            if (i4_ret != RESTR_OK)
            {
                rest_network_update_error_code(REST_NET_WIFI_NOT_EXISTED);
                return 0;
            }

            if (!jsonPwd.isNull())
            {
                c_strncpy(t_ap.password, jsonPwd.asString().c_str(), REST_PASSWORD_LEN);
                b_pwd_is_null = FALSE;
            }
            else
            {
                c_memset(t_ap.password, 0, sizeof(t_ap.password));
                b_pwd_is_null = TRUE;
            }

            REST_LOG_I("ssid: %s, i2_channel: %d\n\r", t_ap.name, t_ap.i2_Channel);

            if (-1000 != t_ap.i2_Channel)
            {
                //TODO update softap channel
                rest_change_softap_channel_setting(t_ap.i2_Channel);
            }

            REST_LOG_I("ap name: [%s], password: [%s]\n\r", t_ap.name, t_ap.password);
            rest_set_wifi_ssid(t_ap.name);

            if (b_pwd_is_null)
            {
                DBG_LOG_PRINT(("%s, %d, password is NULL!\n\r", __FUNCTION__, __LINE__));
                break;
            }

            /* IEEE_802_11_AUTH_MODE_NONE/IEEE_802_11_AUTH_MODE_OPEN */
            if (t_ap.password[0] != 0 || (c_strcasecmp(t_ap.em, "NONE") == 0) || !(t_ap.passwordReq))
	    {
                /* check wifi is already connected or not */
                if (TRUE == _rest_is_wifi_already_connected(t_ap.name))
                {
                    if (TRUE == _rest_is_wifi_association_config_matched(t_ap.name, t_ap.password))
                    {
                        rest_network_update_error_code(REST_NET_WIFI_ALREADY_CONNECTED);
                        b_already_connect_test_connection = TRUE;
                    }
                    else
                    {
                        /* TODO: (steven) return error directly or call wifi associate func */
                        rest_network_update_error_code(REST_NET_WIFI_AUTH_REJECTED);
                    }
                }
                else
                {
                    b_already_connect_test_connection = FALSE;
                    rest_wifi_associate_ex(FALSE, t_ap.password);
                }
            }
            else if((t_ap.password[0] == 0) && (TRUE == _rest_is_wifi_already_connected(t_ap.name)))
            {
                if (TRUE == _rest_is_wifi_association_config_matched(t_ap.name, t_ap.password))
                {
                    rest_network_update_error_code(REST_NET_WIFI_ALREADY_CONNECTED);
                    b_already_connect_test_connection = TRUE;
                }
                else
                {
                    /* TODO: (steven) return error directly or call wifi associate func */
                    rest_network_update_error_code(REST_NET_WIFI_AUTH_REJECTED);
                }
            }

            break;
        }
        default:
            break;
    }

    REST_LOG_I("End\n\r");

    return 0;
}

int manual_setup(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
       case argument::RequestType::REQUEST_GET:
       {
            REST_LOG_I("REQUEST_GET\n\r");

            // get DHCP status
            UINT8           ui1_dhcp_status = ACFG_DHCP_OFF;
            BOOL            b_auto_ip = TRUE;
            CHAR            s_dhcp_mode[32] = {0};

            nw_custom_get_auto_ip_config(&b_auto_ip);
            if (b_auto_ip)
            {
                c_strncpy(s_dhcp_mode, "On", c_strlen("On"));
            }
            else
            {
                nw_custom_get_dhcp_status(&ui1_dhcp_status);

                if (ACFG_DHCP_OFF == ui1_dhcp_status)
                {
                    c_strncpy(s_dhcp_mode, "Off", c_strlen("Off"));
                }
                else if (ACFG_DHCP_DNS_ONLY == ui1_dhcp_status)
                {
                    c_strncpy(s_dhcp_mode, "Manual DNS", c_strlen("Manual DNS"));
                }
                else
                {
                    c_strncpy(s_dhcp_mode, REST_STR_EMPTY, c_strlen(REST_STR_EMPTY));
                }

                DBG_LOG_PRINT(("[KK] %s:%d, s_dhcp_mode: %s.\n", __FUNCTION__, __LINE__, s_dhcp_mode));
            }

            // get ip info
            CHAR  s_ip_address[REST_IP_ADDRESS_LEN+1] = {0};
            CHAR  s_subnet_mask[REST_IP_ADDRESS_LEN+1] = {0};
            CHAR  s_gateway[REST_IP_ADDRESS_LEN+1] = {0};
            CHAR  s_1st_dns[REST_IP_ADDRESS_LEN+1] = {0};
            CHAR  s_2nd_dns[REST_IP_ADDRESS_LEN+1] = {0};

            NW_IP_INFO_T t_ip_info = {0};

            i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_ip_address, t_ip_info.ui4_address);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_subnet_mask, t_ip_info.ui4_netmask);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_gateway, t_ip_info.ui4_gw);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_1st_dns, t_ip_info.ui4_1st_dns);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_2nd_dns, t_ip_info.ui4_2nd_dns);
            LOG_ON_ERR(i4_ret);

            // get MAC address
            char s_rj45_mac[20] = {0};
            CHAR psz_eth[10] = NI_ETHERNET_0;
            a_nw_get_mac_addr_string(psz_eth, s_rj45_mac);

            char s_wlan_mac[20] = {0};
            CHAR psz_wlan[10] = NI_WIRELESS_0;
            a_nw_get_mac_addr_string(psz_wlan, s_wlan_mac);

            Json::Value item;

            item["DHCP_MODE"]   = std::string(s_dhcp_mode);
            item["IP_ADDRESS"]  = std::string(s_ip_address);
            item["SUBNET_MASK"] = std::string(s_subnet_mask);
            item["DEFAULT_GATEWAY"] = std::string(s_gateway);
            item["PREF_DNS"]    = std::string(s_1st_dns);
            item["ALT_DNS"]     = std::string(s_2nd_dns);
            item["RJ45_MAC"]    = std::string(s_rj45_mac);
            item["WIFI_MAC"]    = std::string(s_wlan_mac);

            response["VALUE"] = item;

            break;
       }
       case argument::RequestType::REQUEST_SET:
       {
            REST_LOG_I("REQUEST_SET\n\r");

            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            CHAR        dhcp_osd_str[128] = "DHCP is ";

            Json::Value item;
            Json::Value item1;
            Json::Value itemDhcp;

            item1 = root["message"];
            item = item1["VALUE"];
            itemDhcp = item["DHCP_MODE"];

            NW_IP_INFO_T    t_ip_info;
            BOOL            b_auto_ip = TRUE;
            CHAR            s_dhcp_mode[32] = {0};
            BOOL            b_need_check_ip_conflict = FALSE;


            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            rest_network_update_error_code(REST_NET_EMPTY);

            if (!itemDhcp.isNull())
            {
                c_strcpy(s_dhcp_mode, itemDhcp.asString().c_str());
                s_dhcp_mode[31] = '\0';
            }

            nw_custom_get_auto_ip_config(&b_auto_ip);

            DBG_LOG_PRINT(("[KK] %s:%d, s_dhcp_mode: %s.\n", __FUNCTION__, __LINE__, s_dhcp_mode));

            if (c_strcasecmp(s_dhcp_mode, "On") == 0)
            {
                i4_ret = a_nw_start_dhcp_ip_config();
                if (i4_ret == NWR_OK)
                {
                    i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_OFF);
                    LOG_ON_ERR(i4_ret);

                    i4_ret = nw_custom_set_auto_ip_config(TRUE);
                    LOG_ON_ERR(i4_ret);

                    rest_network_update_error_code(REST_NET_SUCCESS);

                    /* show osd on tv */
                    c_strcat(dhcp_osd_str, s_dhcp_mode);
                    c_uc_ps_to_w2s((const CHAR*)dhcp_osd_str, w2s_string, 255);

                    t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
                    rest_send_msg_to_nav(&t_toast);
                }
                else
                {
                    rest_network_update_error_code(REST_NET_IP_MANUAL_CONFIG_ERROR);
                }

                return 0;
            }
            else if (c_strcasecmp(s_dhcp_mode, "Off") == 0)
            {
                b_need_check_ip_conflict = TRUE;
            }
            else if (c_strcasecmp(s_dhcp_mode, "Manual DNS") != 0)
            {
                rest_network_update_error_code(REST_NET_IP_MANUAL_CONFIG_ERROR);
                return 0;
            }

            /* should get current ip info before setup dhcp status */
            c_memset(&t_ip_info, 0, sizeof(t_ip_info));
            i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);


            /* start manual setup ip info */
            {
                BOOL                b_save_setting = TRUE;
                CHAR                s_ip_string[32] = {0};

                Json::Value item_ip;
                Json::Value item_subnet_mask;
                Json::Value item_default_gateway;
                Json::Value item_pref_dns;
                Json::Value item_alt_dns;

                item_ip = item["IP_ADDRESS"];
                item_subnet_mask = item["SUBNET_MASK"];
                item_default_gateway = item["DEFAULT_GATEWAY"];
                item_pref_dns = item["PREF_DNS"];
                item_alt_dns = item["ALT_DNS"];

                if (!item_ip.isNull())
                {
                    UINT32 ui4_address = 0;

                    c_memset(s_ip_string, 0, sizeof(s_ip_string));
                    c_strcpy(s_ip_string, item_ip.asString().c_str());
                    s_ip_string[31] = '\0';
                    a_nw_aton(&ui4_address, s_ip_string);

                    if (t_ip_info.ui4_address == ui4_address)
                    {
                        b_need_check_ip_conflict = FALSE;
                    }
                    else
                    {
                        t_ip_info.ui4_address = ui4_address;
                        b_need_check_ip_conflict = TRUE;
                    }
                }
                if (!item_subnet_mask.isNull())
                {
                    c_memset(s_ip_string, 0, sizeof(s_ip_string));
                    c_strcpy(s_ip_string, item_subnet_mask.asString().c_str());
                    s_ip_string[31] = '\0';
                    a_nw_aton(&(t_ip_info.ui4_netmask), s_ip_string);
                }
                if (!item_default_gateway.isNull())
                {
                    c_memset(s_ip_string, 0, sizeof(s_ip_string));
                    c_strcpy(s_ip_string, item_default_gateway.asString().c_str());
                    s_ip_string[31] = '\0';
                    a_nw_aton(&(t_ip_info.ui4_gw), s_ip_string);
                }
                if (!item_pref_dns.isNull())
                {
                    c_memset(s_ip_string, 0, sizeof(s_ip_string));
                    c_strcpy(s_ip_string, item_pref_dns.asString().c_str());
                    s_ip_string[31] = '\0';
                    a_nw_aton(&(t_ip_info.ui4_1st_dns), s_ip_string);
                }
                if (!item_alt_dns.isNull())
                {
                    c_memset(s_ip_string, 0, sizeof(s_ip_string));
                    c_strcpy(s_ip_string, item_alt_dns.asString().c_str());
                    s_ip_string[31] = '\0';
                    a_nw_aton(&(t_ip_info.ui4_2nd_dns), s_ip_string);
                }

                /* validate the ip config info(exp. host number shoud not be full zero and 1) */
                if (t_ip_info.ui4_address != 0 && t_ip_info.ui4_netmask != 0)
                {
                    b_save_setting = TRUE;
                }

                if (((t_ip_info.ui4_address & t_ip_info.ui4_netmask) == t_ip_info.ui4_address) ||
                    ((t_ip_info.ui4_address | (~t_ip_info.ui4_netmask)) == t_ip_info.ui4_address))
                {
                    b_save_setting = FALSE;
                    DBG_LOG_PRINT(("[KK] %s:%d, ip info is invalid!!!.\n", __FUNCTION__, __LINE__));
                }

                if (t_ip_info.ui4_gw != 0)
                {
                    if(((t_ip_info.ui4_gw & t_ip_info.ui4_netmask) == t_ip_info.ui4_gw) ||
                       ((t_ip_info.ui4_gw | ~t_ip_info.ui4_netmask) == t_ip_info.ui4_gw))
                     {
                         b_save_setting = FALSE;
                         DBG_LOG_PRINT(("[KK] %s:%d, ip info is invalid!!!.\n", __FUNCTION__, __LINE__));
                     }

                    if( (t_ip_info.ui4_address & t_ip_info.ui4_netmask) != (t_ip_info.ui4_gw & t_ip_info.ui4_netmask))
                    {
                        b_save_setting = FALSE;
                        DBG_LOG_PRINT(("[KK] %s:%d, ip info is invalid!!!.\n", __FUNCTION__, __LINE__));
                    }
                }

                if (FALSE == b_save_setting)
                {
                    DBG_LOG_PRINT(("[KK] %s:%d, ip info is invalid!!!.\n", __FUNCTION__, __LINE__));

                    rest_network_update_error_code(REST_NET_IP_MANUAL_CONFIG_ERROR);
                    return 0;
                }

                /* need check if this IP is exist or not */
                if (b_need_check_ip_conflict)
                {
                    if (a_nw_custom_is_IP_exist(t_ip_info.ui4_address))
                    {
                        DBG_LOG_PRINT(("[KK] %s:%d, ip address is exist!!!.\n", __FUNCTION__, __LINE__));

                        rest_network_update_error_code(REST_NET_IP_MANUAL_CONFIG_ERROR);
                        return 0;
                    }
                }

                i4_ret = a_nw_manual_ip_config(&t_ip_info);
                LOG_ON_ERR(i4_ret);
                if (NWR_OK != i4_ret)
                {
                    i4_ret = nw_custom_set_auto_ip_config(b_auto_ip);
                    LOG_ON_ERR(i4_ret);

                    rest_network_update_error_code(REST_NET_IP_MANUAL_CONFIG_ERROR);
                    return 0;
                }
                else
                {
                    i4_ret = nw_custom_set_auto_ip_config(FALSE);
                    LOG_ON_ERR(i4_ret);

                    if (c_strcasecmp(s_dhcp_mode, "Off") == 0)
                    {
                        i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_OFF);
                        LOG_ON_ERR(i4_ret);

                        b_need_check_ip_conflict = TRUE;
                    }
                    else if (c_strcasecmp(s_dhcp_mode, "Manual DNS") == 0)
                    {
                        i4_ret = nw_custom_set_dhcp_status(ACFG_DHCP_DNS_ONLY);
                        LOG_ON_ERR(i4_ret);
                    }

                    /* show osd on tv */
                    c_strcat(dhcp_osd_str, s_dhcp_mode);
                    c_uc_ps_to_w2s((const CHAR*)dhcp_osd_str, w2s_string, 255);

                    t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
                    rest_send_msg_to_nav(&t_toast);
                }

                DBG_LOG_PRINT(("[KK] %s:%d, manual setup complete!!!\n", __FUNCTION__, __LINE__));

                rest_network_update_error_code(REST_NET_SUCCESS);
            }

            break;
       }
       default:
        break;
    }
    return 0;
}

int manual_setup_info_dhcp(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = 0;
    INT32 type = 0;
    INT16 i2_set_idx = -1;
    WDK_TOAST_T t_toast;
    enum _E_MENU_UI_DHCP
    {
        _ON = 0,
        _OFF,
        _MANUAL_DNS,
        _TYPE_MAX
    };

    Json::Value j_level;
    j_level[_ON] = "On";
    j_level[_OFF] = "Off";
    j_level[_MANUAL_DNS] = "Manual DNS";

    type = get_type(root);

    switch (type)
    {
       case argument::RequestType::REQUEST_GET:
       {
            REST_LOG_I("REQUEST_GET\n\r");

            UINT8           ui1_dhcp_status = ACFG_DHCP_OFF;
            BOOL            b_auto_ip = FALSE;
            CHAR            s_dhcp_mode[32] = {0};

            nw_custom_get_auto_ip_config(&b_auto_ip);
            if (b_auto_ip)
            {
                c_strncpy(s_dhcp_mode, "On", c_strlen("On"));
            }
            else
            {
                nw_custom_get_dhcp_status(&ui1_dhcp_status);

                if (ACFG_DHCP_OFF == ui1_dhcp_status)
                {
                    c_strncpy(s_dhcp_mode, "Off", c_strlen("Off"));
                }
                else if (ACFG_DHCP_DNS_ONLY == ui1_dhcp_status)
                {
                    c_strncpy(s_dhcp_mode, "Manual DNS", c_strlen("Manual DNS"));
                }
                else
                {
                    c_strncpy(s_dhcp_mode, REST_STR_EMPTY, c_strlen(REST_STR_EMPTY));
                }
            }

            response["VALUE"] = std::string(s_dhcp_mode);

            break;
       }
       case argument::RequestType::REQUEST_SET:
       {
           REST_LOG_I("REQUEST_SET\n\r");

           memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
           t_toast.e_toast_style  = WDK_STRING_TOAST;
           t_toast.e_string_style = WDK_STRING_ID_ID;
           t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_NET_CFG_AT;

           Json::Value item1;
           Json::Value item2;
           CHAR str[128] = {0};

           item2 = root["message"];
           item1 = item2["VALUE"];

           c_strcpy(str,item1.asString().c_str());
           REST_LOG_I("str:%s\n\r", str);

           for(int i=0;i<_TYPE_MAX;i++)
           {
              if(strcmp(j_level[i].asString().c_str(),str)==0)
              {
                  i2_set_idx = i;
                  t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_NET_CFG_AT_AUTO + i;
                  break;
              }
           }
           if(i2_set_idx == -1)
           {
               REST_LOG_E("Get invailed arguments %s\n", str);
               i4_ret = -1;
               break;
           }

           menu_page_ip_setting_lb_addr_type_change_fct(i2_set_idx);

           rest_send_msg_to_nav(&t_toast);

           break;
       }
       default:
        break;
    }
    return i4_ret;
}

int manual_setup_info_ip_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            CHAR  s_ip_address[REST_IP_ADDRESS_LEN+1] = {0};
            NW_IP_INFO_T t_ip_info = {0};

            i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            _rest_get_ip_address(s_ip_address, t_ip_info.ui4_address);

            REST_LOG_I("IP: %s\n\r", s_ip_address);

            response["VALUE"]=std::string(s_ip_address);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            BOOL  b_ethernet = FALSE;
            INT32 ip_val    = value_get_value(root);

            a_nw_get_ethernet_connect_info(&b_ethernet);
            if (b_ethernet)
            {
                i4_ret = a_cfg_custom_set_ip_addr((UINT32)ip_val, 0);
                LOG_ON_ERR(i4_ret);
            }
            else
            {
                i4_ret = a_cfg_custom_set_ip_addr((UINT32)ip_val, 1);
                LOG_ON_ERR(i4_ret);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int manual_setup_info_subnet_mask(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            NW_IP_INFO_T t_ip_info = {0};
            CHAR  s_subnet_mask[REST_IP_ADDRESS_LEN+1] = {0};

            REST_LOG_I("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);

            i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_subnet_mask, t_ip_info.ui4_netmask);
            LOG_ON_ERR(i4_ret);

            response["VALUE"]=std::string(s_subnet_mask);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            BOOL  b_ethernet = FALSE;
            INT32 mask_val=0;
            a_nw_get_ethernet_connect_info(&b_ethernet);

            mask_val = value_get_value(root);
            if (b_ethernet)
            {
                i4_ret = a_cfg_custom_set_subnet_mask((UINT32)mask_val,0);
                LOG_ON_ERR(i4_ret);
            }
            else
            {
                i4_ret = a_cfg_custom_set_subnet_mask((UINT32)mask_val,1);
                LOG_ON_ERR(i4_ret);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int manual_setup_info_default_gateway(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            NW_IP_INFO_T t_ip_info = {0};
            CHAR  s_gateway[REST_IP_ADDRESS_LEN+1] = {0};

            i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_gateway, t_ip_info.ui4_gw);
            LOG_ON_ERR(i4_ret);

            response["VALUE"]=std::string(s_gateway);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            BOOL  b_ethernet = FALSE;
            INT32 gw_val=0;
            a_nw_get_ethernet_connect_info(&b_ethernet);

            gw_val = value_get_value(root);
            if (b_ethernet)
            {
                i4_ret = a_cfg_custom_set_default_gateway((UINT32)gw_val,0);
                LOG_ON_ERR(i4_ret);
            }
            else
            {
                i4_ret = a_cfg_custom_set_default_gateway((UINT32)gw_val,1);
                LOG_ON_ERR(i4_ret);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int manual_setup_info_pref_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            NW_IP_INFO_T t_ip_info = {0};
            CHAR  s_1st_dns[REST_IP_ADDRESS_LEN+1] = {0};

            i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_1st_dns, t_ip_info.ui4_1st_dns);
            LOG_ON_ERR(i4_ret);

            response["VALUE"]=std::string(s_1st_dns);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            BOOL  b_ethernet = FALSE;
            INT32 ui4_1st_dns=0;
            a_nw_get_ethernet_connect_info(&b_ethernet);

            ui4_1st_dns = value_get_value(root);
            if (b_ethernet)
            {
                i4_ret =a_cfg_custom_set_1st_dns((UINT32)ui4_1st_dns,0);
                LOG_ON_ERR(i4_ret);
            }
            else
            {
                i4_ret =a_cfg_custom_set_1st_dns((UINT32)ui4_1st_dns,1);
                LOG_ON_ERR(i4_ret);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int manual_setup_info_alt_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            NW_IP_INFO_T t_ip_info = {0};
            CHAR  s_2nd_dns[REST_IP_ADDRESS_LEN+1] = {0};

            i4_ret = a_nw_get_crnt_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_2nd_dns, t_ip_info.ui4_2nd_dns);
            LOG_ON_ERR(i4_ret);

            response["VALUE"]=std::string(s_2nd_dns);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            BOOL  b_ethernet = FALSE;
            INT32 ui4_2nd_dns=0;
            a_nw_get_ethernet_connect_info(&b_ethernet);

            ui4_2nd_dns = value_get_value(root);
            if (b_ethernet)
            {
                i4_ret = a_cfg_custom_set_2nd_dns((UINT32)ui4_2nd_dns,0);
                LOG_ON_ERR(i4_ret);
            }
            else
            {
                i4_ret = a_cfg_custom_set_2nd_dns((UINT32)ui4_2nd_dns,1);
                LOG_ON_ERR(i4_ret);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int manual_setup_info_rj45_mac_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    char ps_mac_str[256]={0};
    type = get_type(root);

    CHAR psz_name[28] = NI_ETHERNET_0;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            a_nw_get_mac_addr_string(psz_name,ps_mac_str);

            response["VALUE"]=std::string(ps_mac_str);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            string_get_string(root, ps_mac_str, 256);

            REST_LOG_I("ps_mac_str:%s\n\r", ps_mac_str);
            a_nw_save_mac_addr_string(psz_name,ps_mac_str);
            break;
        }
        default:
            break;
    }
    return 0;
}

int manual_setup_info_wireless_mac_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    char ps_mac_str[256]={0};
    type = get_type(root);

    CHAR psz_name[28] = NI_WIRELESS_0;

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            a_nw_get_mac_addr_string(psz_name,ps_mac_str);

            response["VALUE"]=std::string(ps_mac_str);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            string_get_string(root, ps_mac_str, 256);

            REST_LOG_I("ps_mac_str:%s\n\r", ps_mac_str);
            a_nw_save_mac_addr_string(psz_name,ps_mac_str);
            break;
        }
        default:
            break;
    }
    return 0;
}

int start_ap_search(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 i4_ret  = RESTR_OK;

    i4_ret = a_nw_wlan_scan();
    LOG_ON_ERR(i4_ret);

    return 0;
}

int stop_ap_search(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    return 0;
}

int set_wifi_password(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            response["VALUE"] = std::string(REST_STR_EMPTY);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            CHAR s_pwd[256] = {0};
            CHAR s_ssid[256] = {0};

            string_get_string(root, s_pwd, 256);
            REST_LOG_I("s_pwd:%s\n\r", s_pwd);

            /* check ssid */
            rest_get_wifi_ssid(s_ssid);
            if (c_strlen(s_ssid) == 0)
            {
                NET_802_11_BSS_INFO_T t_CurrBss;

                c_memset(&t_CurrBss, 0, sizeof(t_CurrBss));
                a_nw_wlan_get_curr_bss(&t_CurrBss);

                if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
                {
                    c_strncpy(s_ssid, t_CurrBss.t_Ssid.ui1_aSsid, 255);
                }
                else
                {
                    rest_network_update_error_code(REST_NET_WIFI_NEEDS_VALID_SSID);
                    return 0;
                }
            }

            /* check wifi is already connected or not */
            if (TRUE == _rest_is_wifi_already_connected(s_ssid))
            {
                if (TRUE == _rest_is_wifi_association_config_matched(s_ssid, s_pwd))
                {
                    rest_network_update_error_code(REST_NET_WIFI_ALREADY_CONNECTED);
                }
                else
                {
                    /* TODO: (steven) return error directly or call wifi associate func */
                    rest_network_update_error_code(REST_NET_WIFI_AUTH_REJECTED);
                }
            }
            else
            {
                rest_wifi_associate_ex(FALSE, s_pwd);
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

int hidden_network(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value item;
            Json::Value items;

            item["NAME"] = std::string(REST_STR_EMPTY);
            item["RSSI"] = 0;
            item["BAND"] = std::string(REST_STR_EMPTY);
            item["EM"] = std::string(REST_STR_EMPTY);
            item["BSSID"] = std::string(REST_STR_EMPTY);

            items[0] = item;

            response["VALUE"] = items;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            //TODO
            REST_LOG_I("REQUEST_SET\n\r");

            INT32 i4_ret  = RESTR_OK;
            CHAR ap_name[REST_SSID_MAX_LEN + 1] = {0};
            REST_DATA_WIFI_AP_T t_ap;
            BOOL b_real_hidden_network = TRUE;

            Json::Value item;
            Json::Value item1;
            Json::Value item2;
            Json::Value jsonName;
            Json::Value jsonPwd;

            item2 = root["message"];
            item1 = item2["VALUE"];
            item = item1[0];
            jsonName = item["NAME"];
            jsonPwd = item["PASSWORD"];

            c_memset(ap_name, 0, sizeof(ap_name));
            if (!jsonName.isNull())
            {
                c_strcpy(ap_name, jsonName.asString().c_str());
                ap_name[REST_SSID_MAX_LEN] = 0;
            }
            else
            {
                DBG_LOG_PRINT(("%s, %d, ssid name is empty!", __FUNCTION__, __LINE__));
                rest_network_update_error_code(REST_NET_WIFI_NOT_EXISTED);

                return 0;
            }

            c_memset(&t_ap, 0, sizeof(REST_DATA_WIFI_AP_T));
            i4_ret = rest_get_access_point_by_ssid(ap_name, &t_ap);
            if (i4_ret != RESTR_OK)
            {
                b_real_hidden_network = TRUE;
            }
            else
            {
                b_real_hidden_network = FALSE;

                REST_LOG_I("ssid: %s, i2_channel: %d\n\r", t_ap.name, t_ap.i2_Channel);

                if (-1000 != t_ap.i2_Channel)
                {
                    rest_change_softap_channel_setting(t_ap.i2_Channel);
                }
            }

            if (!jsonPwd.isNull())
            {
                c_strncpy(t_ap.password, jsonPwd.asString().c_str(), REST_PASSWORD_LEN);
            }
            else
            {
                c_memset(t_ap.password, 0, sizeof(t_ap.password));
            }

            REST_LOG_I("ap name: [%s], password: [%s]\n\r", ap_name, t_ap.password);
            rest_set_wifi_ssid(ap_name);

            /* check wifi is already connected or not */
            if (TRUE == _rest_is_wifi_already_connected(ap_name))
            {
                if (TRUE == _rest_is_wifi_association_config_matched(ap_name, t_ap.password))
                {
                    rest_network_update_error_code(REST_NET_WIFI_ALREADY_CONNECTED);
                }
                else
                {
                    /* TODO: (steven) return error directly or call wifi associate func */
                    rest_network_update_error_code(REST_NET_WIFI_AUTH_REJECTED);
                }
            }
            else
            {
                rest_wifi_associate_ex(b_real_hidden_network, t_ap.password);
            }

            break;
        }
        default:
            break;
    }
    return 0;
}

int hidden_network_info_name(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            response["VALUE"] = std::string(REST_STR_EMPTY);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }
    return 0;
}

int hidden_network_info_password(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            response["VALUE"] = std::string(REST_STR_EMPTY);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }
    return 0;
}

int test_connection(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    return 0;
}

int test_connection_test_connection(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = get_type(root);

    REST_LOG_I("type: %d\n\r", type);

    if (argument::RequestType::REQUEST_ACTION == type)
    {
        b_g_in_test_connection = TRUE;

        /* show test connection msg immediately */
        _rest_send_test_connection_msg();

        if (e_g_nw_test_status == REST_NW_TEST_END)
        {
            e_g_nw_test_status = REST_NW_TEST_CONNECT_TEST;
            rest_cmd_test_network_connection();
        }
        else
        {
            DBG_LOG_PRINT(("[KK][Warning] <%s,%d> e_g_nw_test_status=%d\n", __FUNCTION__, __LINE__, e_g_nw_test_status));
        }
    }

    return 0;
}

int test_connection_test_connection_test()
{
    REST_LOG_I("Enter\n\r");

    b_g_in_test_connection = TRUE;

    if (e_g_nw_test_status == REST_NW_TEST_END)
    {
        e_g_nw_test_status = REST_NW_TEST_CONNECT_TEST;
        rest_cmd_test_network_connection();
    }
    else
    {
        DBG_LOG_PRINT(("[KK][Warning] <%s,%d> e_g_nw_test_status=%d\n", __FUNCTION__, __LINE__, e_g_nw_test_status));
    }

    return 0;
}

static VOID _rest_network_delay_connection_status (
                                    VOID*      pv_data,
                                    SIZE_T     z_data_size
                                    )
{
    REST_LOG_I("Enter\n\r");
    //DBG_LOG_PRINT(("Ping 8.8.8.8\n\r"));
    //system("ping -c 3 8.8.8.8");
    //DBG_LOG_PRINT(("Ping google.com\n\r"));
    //system("ping -c 3 google.com");
    if(rest_get_python_ready())
    {
        c_thread_delay(100);
        rest_event_notify("tv_settings/network/connection_status", 1, "");
    }
    else
    {
        rest_no_ready_delay_notify_network_status();
    }
}

static BOOL b_first_test_connection = FALSE;
int test_connection_test_connection_results(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 i4_ret = RESTR_OK;
    Json::Value result;
    Json::Value results;
    BOOL b_finish = FALSE;
    int internet_connect;
    CHAR s_speed[32] = {0};

    if ((b_first_test_connection == FALSE && b_g_in_test_connection == FALSE) ||
        ((TRUE == b_already_connect_test_connection) && (e_g_nw_test_status == REST_NW_TEST_END))) {
        REST_LOG_I("First getting connection result, trigger test connection\n\r");
        b_first_test_connection = TRUE;
        b_already_connect_test_connection=FALSE;
        test_connection_test_connection_test();
    }

    internet_connect = 0;
    if (b_g_in_test_connection)
    {
        if (REST_NW_TEST_END == e_g_nw_test_status)
        {
            b_finish = TRUE;
        }
        else
        {
            b_finish = FALSE;
        }
    }
    else
    {
        rest_test_interface();

        if (c_strlen(t_g_test_result.err_code) > 0)
        {
            b_finish = TRUE;
        }
        else
        {
            b_finish = FALSE;
        }
    }

    DBG_LOG_PRINT(("[KK] %s, LINE: %d, b_finish: %d, Error code: %s\n", __FUNCTION__, __LINE__, b_finish, t_g_test_result.err_code));

    /* get DHCP status */
    UINT8           ui1_dhcp_status = ACFG_DHCP_OFF;
    BOOL            b_auto_ip = FALSE;
    CHAR            s_dhcp_mode[32] = {0};

    nw_custom_get_auto_ip_config(&b_auto_ip);
    if (b_auto_ip)
    {
        c_strncpy(s_dhcp_mode, "On", c_strlen("On"));
    }
    else
    {
        nw_custom_get_dhcp_status(&ui1_dhcp_status);

        if (ACFG_DHCP_OFF == ui1_dhcp_status)
        {
            c_strncpy(s_dhcp_mode, "Off", c_strlen("Off"));
        }
        else if (ACFG_DHCP_DNS_ONLY == ui1_dhcp_status)
        {
            c_strncpy(s_dhcp_mode, "Manual DNS", c_strlen("Manual DNS"));
        }
        else
        {
            c_strncpy(s_dhcp_mode, REST_STR_EMPTY, 31);
        }
    }
    s_dhcp_mode[31] = '\0';

    if (t_g_test_result.conn_speed < 0.01)
    {
        c_strcpy(s_speed, REST_STR_NOT_AVAILABLE);
    }
    else
    {
        c_sprintf(s_speed,"%.2f Kb/s",t_g_test_result.conn_speed);
    }

    //"CONNECTION METHOD":"WiFi","CONNECTION SPEED":"8682.57 Kb/s","DHCP":"On","ERROR_CODE":"SUCCESS","ESTABLISHED DNS SERVERS":"TRUE","ESTABLISHED NTP SERVER":"TRUE","SSID NAME":"MTK_2.4G"
    result["ESTABLISHED DNS SERVERS"] = std::string(t_g_test_result.dns);
    //REST_LOG_I("ESTABLISHED DNS SERVERS=%s(%d)\n\r", t_g_test_result.dns, c_strlen(t_g_test_result.dns));
    if (c_strcmp(t_g_test_result.dns, "TRUE") == 0) {
        internet_connect++;
    }
    result["ESTABLISHED NTP SERVER"] = std::string(t_g_test_result.ntp);
    //REST_LOG_I("ESTABLISHED NTP SERVERS=%s(%d)\n\r", t_g_test_result.ntp, c_strlen(t_g_test_result.ntp));
    if (c_strcmp(t_g_test_result.ntp, "TRUE") == 0) {
        internet_connect++;
    }
    result["CONNECTION METHOD"] = std::string(t_g_test_result.conn_method);
    result["CONNECTION SPEED"] = std::string(s_speed);
    result["SSID NAME"] = std::string(t_g_test_result.ssid);
    result["DHCP"] = std::string(s_dhcp_mode);
    result["ERROR_CODE"] = std::string(t_g_test_result.err_code);
    //REST_LOG_I("ERROR_CODE=%s(%d)\n\r", t_g_test_result.err_code, c_strlen(t_g_test_result.err_code));
    if (c_strcmp(t_g_test_result.err_code, "SUCCESS") == 0) {
        internet_connect++;
    }

    if (c_strcmp(t_g_test_result.conn_method, "Ethernet") == 0) {
        internet_connect = 3;
    }
    REST_LOG_I("internet_connect=%d\n\r", internet_connect);

    results[0] = result;
    response["VALUE"] = results;

    /* show test connection info on tv if we are not in oobe stage*/
    UINT16 ui2_status = 0;
    UINT8  ui1_state = 0;
    UINT8  ui1_page_idx = 0;

    a_cfg_get_wzd_status(&ui2_status);
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);

    do
    {
        /* only show osd while test connection is running */
        if (!b_g_in_test_connection || (WZD_STATE_RESUME_C4TV_END == ui1_state && WZD_PAGE_INDEX_C4TV_END   == ui1_page_idx))
        {
            break;
        }

        if (b_finish)
        {
            b_g_in_test_connection = FALSE;
            DBG_LOG_PRINT(("[KK] %s, LINE: %d, test connection complete! \n", __FUNCTION__, __LINE__));

            NAV_COMP_SET_T   t_nav_comp_set = 0;
            i4_ret = a_nav_get_comp_visibility (&t_nav_comp_set);
            if (i4_ret != NAVR_OK)
            {
                break;
            }

            if ((t_nav_comp_set & NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PICTURE_EFFECT)) > 0 ||
                (t_nav_comp_set & NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCREEN_MODE)) > 0 ||
                (t_nav_comp_set & NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)) > 0)
            {
                /* Pic mode or screen mode is visible. */
                DBG_LOG_PRINT(("[KK] %s, LINE: %d, nav comp is visible! \n", __FUNCTION__, __LINE__));
                break;
            }

            _rest_send_test_connection_msg();
        }

    } while(0);

    /* test connection is busy or not */
    /* t_g_test_result.conn_speed != 0 should be added after customer's smartphone app
     * sends test_connection before querying result
     */
    if (b_finish)
    {
        // set flag for allowing notify connection_status = 1
        // "CONNECTION METHOD":"WiFi","CONNECTION SPEED":"8682.57 Kb/s","DHCP":"On","ERROR_CODE":"SUCCESS","ESTABLISHED DNS SERVERS":"TRUE","ESTABLISHED NTP SERVER":"TRUE","SSID NAME":"MTK_2.4G"
        if ((internet_connect == 3) || (g_pin_google_success == TRUE)) {
			g_pin_google_success = FALSE;
            REST_LOG_I("Internet connected\n\r");
            if (b_internet_connected == FALSE && b_buffer_connection_status) {
                REST_LOG_I("Send connection_status notification\n\r");
                b_internet_connected = TRUE;
                b_buffer_connection_status = FALSE;
                //rest_event_notify("tv_settings/network/connection_status", 1, "");
                rest_async_invoke(_rest_network_delay_connection_status, NULL, 0, TRUE);
            } else if (b_internet_connected == FALSE) {
                REST_LOG_I("Still send connection_status notification\n\r");
                b_internet_connected = TRUE;
                //b_buffer_connection_status = FALSE;
                //rest_event_notify("tv_settings/network/connection_status", 1, "");
                rest_async_invoke(_rest_network_delay_connection_status, NULL, 0, TRUE);
            }
            b_internet_connected = TRUE;
        } else {
            b_internet_connected = FALSE;
        }
        return 0;
    }
    else
    {
        return 2;
    }
}

BOOL rest_network_is_internet_connected()
{
    REST_LOG_I("Enter- b_internet_connected = %d\n\r", b_internet_connected);


    if (b_first_test_connection == FALSE && b_g_in_test_connection == FALSE)
    {
        REST_LOG_I("First getting connection internet, trigger test connection\n\r");
        b_first_test_connection = TRUE;
        test_connection_test_connection_test();
    }

    if (b_internet_connected == FALSE) {
        b_buffer_connection_status = TRUE;
    } else {
        b_buffer_connection_status = FALSE;
        rest_nw_set_is_hidden_notwork(FALSE);
    }

    return b_internet_connected;
}

void update_test_connection_status()
{
    REST_LOG_I("Enter***\n\r");

    INT32 i4_ret = RESTR_OK;
    BOOL b_finish = FALSE;
    int internet_connect;
    CHAR s_speed[32] = {0};

    if (b_first_test_connection == FALSE && b_g_in_test_connection == FALSE) {
        REST_LOG_I("First getting connection result, trigger test connection\n\r");
        b_first_test_connection = TRUE;
        test_connection_test_connection_test();
    }

    internet_connect = 0;
    if (b_g_in_test_connection)
    {
        if (REST_NW_TEST_END == e_g_nw_test_status)
        {
            b_finish = TRUE;
        }
        else
        {
            b_finish = FALSE;
        }
    }
    else
    {
        rest_test_interface();

        if (c_strlen(t_g_test_result.err_code) > 0)
        {
            b_finish = TRUE;
        }
        else
        {
            b_finish = FALSE;
        }
    }

    DBG_LOG_PRINT(("[KK] %s, LINE: %d, b_finish: %d, Error code: %s\n", __FUNCTION__, __LINE__, b_finish, t_g_test_result.err_code));

    /* get DHCP status */
    UINT8           ui1_dhcp_status = ACFG_DHCP_OFF;
    BOOL            b_auto_ip = FALSE;
    CHAR            s_dhcp_mode[32] = {0};

    nw_custom_get_auto_ip_config(&b_auto_ip);
    if (b_auto_ip)
    {
        c_strncpy(s_dhcp_mode, "On", c_strlen("On"));
    }
    else
    {
        nw_custom_get_dhcp_status(&ui1_dhcp_status);

        if (ACFG_DHCP_OFF == ui1_dhcp_status)
        {
            c_strncpy(s_dhcp_mode, "Off", c_strlen("Off"));
        }
        else if (ACFG_DHCP_DNS_ONLY == ui1_dhcp_status)
        {
            c_strncpy(s_dhcp_mode, "Manual DNS", c_strlen("Manual DNS"));
        }
        else
        {
            c_strncpy(s_dhcp_mode, REST_STR_EMPTY, 31);
        }
    }
    s_dhcp_mode[31] = '\0';

    if (t_g_test_result.conn_speed < 0.01)
    {
        c_strcpy(s_speed, REST_STR_NOT_AVAILABLE);
    }
    else
    {
        c_sprintf(s_speed,"%.2f Kb/s",t_g_test_result.conn_speed);
    }
    if (c_strcmp(t_g_test_result.dns, "TRUE") == 0) {
        internet_connect++;
    }
    if (c_strcmp(t_g_test_result.ntp, "TRUE") == 0) {
        internet_connect++;
    }

    if (c_strcmp(t_g_test_result.err_code, "SUCCESS") == 0) {
        internet_connect++;
    }
    REST_LOG_I("internet_connect=%d\n\r", internet_connect);

    /* show test connection info on tv if we are not in oobe stage*/
    UINT16 ui2_status = 0;
    UINT8  ui1_state = 0;
    UINT8  ui1_page_idx = 0;

    a_cfg_get_wzd_status(&ui2_status);
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);

    do
    {
        /* only show osd while test connection is running */
        if (!b_g_in_test_connection || (WZD_STATE_RESUME_C4TV_END == ui1_state && WZD_PAGE_INDEX_C4TV_END   == ui1_page_idx))
        {
            break;
        }

        if (b_finish)
        {
            b_g_in_test_connection = FALSE;
            DBG_LOG_PRINT(("[KK] %s, LINE: %d, test connection complete! \n", __FUNCTION__, __LINE__));

            NAV_COMP_SET_T   t_nav_comp_set = 0;
            i4_ret = a_nav_get_comp_visibility (&t_nav_comp_set);
            if (i4_ret != NAVR_OK)
            {
                break;
            }

            if ((t_nav_comp_set & NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_PICTURE_EFFECT)) > 0 ||
                (t_nav_comp_set & NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_SCREEN_MODE)) > 0 ||
                (t_nav_comp_set & NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_INPUT_SRC)) > 0)
            {
                /* Pic mode or screen mode is visible. */
                DBG_LOG_PRINT(("[KK] %s, LINE: %d, nav comp is visible! \n", __FUNCTION__, __LINE__));
                break;
            }

            //_rest_send_test_connection_msg(); //DTV02196489 In some cases, TV will show "Test Connection" content when power on.
        }

    } while(0);

    /* test connection is busy or not */
    /* t_g_test_result.conn_speed != 0 should be added after customer's smartphone app
     * sends test_connection before querying result
     */
    if (b_finish)
    {
        // set flag for allowing notify connection_status = 1
        // "CONNECTION METHOD":"WiFi","CONNECTION SPEED":"8682.57 Kb/s","DHCP":"On","ERROR_CODE":"SUCCESS","ESTABLISHED DNS SERVERS":"TRUE","ESTABLISHED NTP SERVER":"TRUE","SSID NAME":"MTK_2.4G"
        if ((internet_connect == 3) || (g_pin_google_success == TRUE)) {
			g_pin_google_success = FALSE;
            REST_LOG_I("Internet connected\n\r");
            if (b_internet_connected == FALSE && b_buffer_connection_status) {
                REST_LOG_I("Send connection_status notification\n\r");
                b_internet_connected = TRUE;
                b_buffer_connection_status = FALSE;
                //rest_event_notify("tv_settings/network/connection_status", 1, "");
                rest_async_invoke(_rest_network_delay_connection_status, NULL, 0, TRUE);
            } else if (b_internet_connected == FALSE) {
                REST_LOG_I("Still send connection_status notification\n\r");
                b_internet_connected = TRUE;
                //b_buffer_connection_status = FALSE;
                //rest_event_notify("tv_settings/network/connection_status", 1, "");
                rest_async_invoke(_rest_network_delay_connection_status, NULL, 0, TRUE);
            }
            b_internet_connected = TRUE;
        } else {
            b_internet_connected = FALSE;
        }
    }
    else
    {
    }
}

int test_connection_retest(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = get_type(root);

    REST_LOG_I("type: %d\n\r", type);

    if (argument::RequestType::REQUEST_ACTION == type)
    {
        b_g_in_test_connection = TRUE;

        /* show test connection msg immediately */
        _rest_send_test_connection_msg();

        if (e_g_nw_test_status == REST_NW_TEST_END)
        {
            e_g_nw_test_status = REST_NW_TEST_CONNECT_TEST;
            rest_cmd_test_network_connection();
        }
        else
        {
            DBG_LOG_PRINT(("[KK][Warning] <%s,%d> e_g_nw_test_status=%d\n", __FUNCTION__, __LINE__, e_g_nw_test_status));
        }
    }

    return 0;
}

int test_connection_manual_setup_dhcp(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 val  = 0;
    INT32 i4_ret  = RESTR_OK;

    val = value_get_value(root);
    i4_ret = nw_custom_set_dhcp_status((UINT8)val);
    LOG_ON_ERR(i4_ret);

    rest_cmd_test_network_connection();
    return 0;
}

int test_connection_manual_setup_ip_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    BOOL  b_ethernet = FALSE;
    INT32 ip_val    = value_get_value(root);
    INT32 i4_ret = 0;

    a_nw_get_ethernet_connect_info(&b_ethernet);
    if (b_ethernet)
    {
        i4_ret = a_cfg_custom_set_ip_addr((UINT32)ip_val, 0);
        LOG_ON_ERR(i4_ret);
    }
    else
    {
        i4_ret = a_cfg_custom_set_ip_addr((UINT32)ip_val, 1);
        LOG_ON_ERR(i4_ret);
    }

    rest_cmd_test_network_connection();
    return 0;
}

int test_connection_manual_setup_subnet_mask(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    BOOL  b_ethernet = FALSE;
    INT32 mask_val=0;
    INT32 i4_ret  = RESTR_OK;
    a_nw_get_ethernet_connect_info(&b_ethernet);

    mask_val = value_get_value(root);
    if (b_ethernet)
    {
        i4_ret = a_cfg_custom_set_subnet_mask((UINT32)mask_val,0);
        LOG_ON_ERR(i4_ret);
    }
    else
    {
        i4_ret = a_cfg_custom_set_subnet_mask((UINT32)mask_val,1);
        LOG_ON_ERR(i4_ret);
    }

    rest_cmd_test_network_connection();
    return 0;
}

int test_connection_manual_setup_default_gateway(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    BOOL  b_ethernet = FALSE;
    INT32 gw_val=0;
    INT32 i4_ret  = RESTR_OK;
    a_nw_get_ethernet_connect_info(&b_ethernet);

    gw_val = value_get_value(root);
    if (b_ethernet)
    {
        i4_ret = a_cfg_custom_set_default_gateway((UINT32)gw_val,0);
        LOG_ON_ERR(i4_ret);
    }
    else
    {
        i4_ret = a_cfg_custom_set_default_gateway((UINT32)gw_val,1);
        LOG_ON_ERR(i4_ret);
    }
    rest_cmd_test_network_connection();
    return 0;
}

int test_connection_manual_setup_pref_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret  = RESTR_OK;
    BOOL  b_ethernet = FALSE;
    INT32 ui4_1st_dns=0;
    a_nw_get_ethernet_connect_info(&b_ethernet);

    ui4_1st_dns = value_get_value(root);
    if (b_ethernet)
    {
        i4_ret =a_cfg_custom_set_1st_dns((UINT32)ui4_1st_dns,0);
        LOG_ON_ERR(i4_ret);
    }
    else
    {
        i4_ret =a_cfg_custom_set_1st_dns((UINT32)ui4_1st_dns,1);
        LOG_ON_ERR(i4_ret);
    }
    rest_cmd_test_network_connection();
    return 0;
}

int test_connection_manual_setup_alt_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret  = RESTR_OK;
    BOOL  b_ethernet = FALSE;
    INT32 ui4_2nd_dns=0;
    a_nw_get_ethernet_connect_info(&b_ethernet);

    ui4_2nd_dns = value_get_value(root);
    if (b_ethernet)
    {
        i4_ret = a_cfg_custom_set_2nd_dns((UINT32)ui4_2nd_dns,0);
        LOG_ON_ERR(i4_ret);
    }
    else
    {
        i4_ret = a_cfg_custom_set_2nd_dns((UINT32)ui4_2nd_dns,1);
        LOG_ON_ERR(i4_ret);
    }
    rest_cmd_test_network_connection();
    return 0;
}

int test_connection_manual_setup_rj45_mac_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    char ps_mac_str[256]={0};
    CHAR psz_name[28] = NI_ETHERNET_0;

    string_get_string(root, ps_mac_str, 256);
    REST_LOG_I("ps_mac_str:%s\n\r", ps_mac_str);
    a_nw_save_mac_addr_string(psz_name,ps_mac_str);

    rest_cmd_test_network_connection();
    return 0;
}

int test_connection_manual_setup_wireless_mac_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    char ps_mac_str[256]={0};
    CHAR psz_name[28] = NI_WIRELESS_0;

    string_get_string(root, ps_mac_str, 256);
    REST_LOG_I("ps_mac_str:%s\n\r", ps_mac_str);
    a_nw_save_mac_addr_string(psz_name,ps_mac_str);

    rest_cmd_test_network_connection();
    return 0;
}

//dolphin 20200401 get network wired connect status
int wired_connection(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    int i4_ret =0;
    BOOL b_status=FALSE;
    Json::Value j_status;

    j_status[0]="Disconnected";
    j_status[1]="Connected";

    i4_ret = a_nw_get_ethernet_connect_info(&b_status);
    if(b_status==TRUE)
    {
    	response["VALUE"]=j_status[1];
    }
    else
    {
       	response["VALUE"]=j_status[0];
    }

    return i4_ret;
}

int forget_saved_network(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    int i4_ret =0;

    i4_ret =  a_menu_network_forget_temporary_ssid();
    if(i4_ret!=0)
    {
        REST_LOG_E("Forget failed\n");
    }

    return i4_ret;
}

int terms_and_conditions(Json::Value & root, Json::Value & response) {REST_LOG_I("Enter\n\r"); return 0;}

int network_viewing_data(Json::Value & root, Json::Value & response) {REST_LOG_I("Enter\n\r"); return 0;}

int network_information_connection_type(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_connection_type(root, response);
}

int network_information_ssid(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_ssid(root, response);
}

int network_information_security_type(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_security_type(root, response);
}

int network_information_ip_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_ip_address(root, response);
}

int network_information_default_gateway(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_gateway(root, response);
}

int network_information_subnet_mask(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_subnet_mask(root, response);
}

int network_information_pref_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_preferred_dns_server(root, response);
}

int network_information_alt_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_alternate_dns_server(root, response);
}

int network_information_rssi(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_rssi(root, response);
}

int network_information_rj45_mac(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_rj45_mac_address(root, response);
}

int network_information_wlan_mac(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_wlan_mac_address(root, response);
}

int network_information_wifi_module(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_wifi_module(root, response);
}

int network_information_ipv6_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            NW_IPV6_INFO_T  t_net_ipv6_info;
            int i4_ret = 0;
            c_memset(&t_net_ipv6_info, 0, sizeof(t_net_ipv6_info));
            i4_ret = a_nw_get_v6_info(&t_net_ipv6_info);
            if(i4_ret < 0)
            {
                REST_LOG_E("Get IPv6 information Fail\n");
                response["VALUE"] = std::string("0");
            }
            else if(0 == c_strlen(t_net_ipv6_info.ac_v6ip))
            {
                response["VALUE"] = std::string(REST_STR_NOT_AVAILABLE);
            }
            else
            {
                response["VALUE"] = std::string(t_net_ipv6_info.ac_v6ip);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int network_information_ipv6_gateway(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            NW_IPV6_INFO_T  t_net_ipv6_info;
            int i4_ret = 0;
            c_memset(&t_net_ipv6_info, 0, sizeof(t_net_ipv6_info));
            i4_ret = a_nw_get_v6_info(&t_net_ipv6_info);
            if(i4_ret < 0)
            {
                REST_LOG_E("Get IPv6 information Fail\n");
                response["VALUE"] = std::string("0");
            }
            else if(0 == c_strlen(t_net_ipv6_info.ac_v6gw))
            {
                response["VALUE"] = std::string(REST_STR_NOT_AVAILABLE);
            }
            else
            {
                response["VALUE"] = std::string(t_net_ipv6_info.ac_v6gw);
            }
            break;

        }
        default:
            break;
    }

    return 0;
}

int network_information_ipv6_prefix_len(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            NW_IPV6_INFO_T  t_net_ipv6_info;
            int i4_ret = 0;
            c_memset(&t_net_ipv6_info, 0, sizeof(t_net_ipv6_info));
            i4_ret = a_nw_get_v6_info(&t_net_ipv6_info);
            if(i4_ret < 0)
            {
                REST_LOG_E("Get IPv6 information Fail\n");
                response["VALUE"] = std::string("0");
            }
            else if(0 == t_net_ipv6_info.ui4_prefix)
            {
                response["VALUE"] = std::string(REST_STR_NOT_AVAILABLE);
            }
            else
            {
                response["VALUE"] = std::string(std::to_string(t_net_ipv6_info.ui4_prefix));
            }
            break;
        }
        default:
            break;
    }

    return 0;
}


int network_information_ipv6_pref_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            NW_IPV6_INFO_T  t_net_ipv6_info;
            int i4_ret = 0;
            c_memset(&t_net_ipv6_info, 0, sizeof(t_net_ipv6_info));
            i4_ret = a_nw_get_v6_info(&t_net_ipv6_info);
            if(i4_ret < 0)
            {
                REST_LOG_E("Get IPv6 information Fail\n");
                response["VALUE"] = std::string("0");
            }
            else
            {
                response["VALUE"] = std::string(t_net_ipv6_info.ac_dns1);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int network_information_ipv6_alt_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            NW_IPV6_INFO_T  t_net_ipv6_info;
            int i4_ret = 0;
            c_memset(&t_net_ipv6_info, 0, sizeof(t_net_ipv6_info));
            i4_ret = a_nw_get_v6_info(&t_net_ipv6_info);
            if(i4_ret < 0)
            {
                REST_LOG_E("Get IPv6 information Fail\n");
                response["VALUE"] = std::string("0");
            }
            else
            {
                response["VALUE"] = std::string(t_net_ipv6_info.ac_dns2);
            }
            break;

        }
        default:
            break;
    }

    return 0;
}


handler network_handler[] = {

    connection_type,
    connection_status,
    current_ssid_name,
    dhcp_mode,
    ip_address,
    subnet_mask,
    default_gateway,
    wireless_access_points,
    current_access_point,
    manual_setup,
    manual_setup_info_dhcp,
    manual_setup_info_ip_address,
    manual_setup_info_subnet_mask,
    manual_setup_info_default_gateway,
    manual_setup_info_pref_dns_server,
    manual_setup_info_alt_dns_server,
    manual_setup_info_rj45_mac_address,
    manual_setup_info_wireless_mac_address,
    start_ap_search,
    stop_ap_search,
    set_wifi_password,
    hidden_network,
    hidden_network_info_name,
    hidden_network_info_password,
    test_connection,
    test_connection_test_connection,
    test_connection_test_connection_results,
    test_connection_retest,
    test_connection_manual_setup_dhcp,
    test_connection_manual_setup_ip_address,
    test_connection_manual_setup_subnet_mask,
    test_connection_manual_setup_default_gateway,
    test_connection_manual_setup_pref_dns_server,
    test_connection_manual_setup_alt_dns_server,
    test_connection_manual_setup_rj45_mac_address,
    test_connection_manual_setup_wireless_mac_address,
    wired_connection,
    forget_saved_network,
    terms_and_conditions,
    network_viewing_data,
    network_information_connection_type,
    network_information_ssid,
    network_information_security_type,
    network_information_ip_address,
    network_information_default_gateway,
    network_information_subnet_mask,
    network_information_pref_dns_server,
    network_information_alt_dns_server,
    network_information_rssi,
    network_information_rj45_mac,
    network_information_wlan_mac,
    network_information_wifi_module,
    network_information_ipv6_address,
    network_information_ipv6_gateway,
    network_information_ipv6_prefix_len,
    network_information_ipv6_pref_dns_server,
    network_information_ipv6_alt_dns_server
};

