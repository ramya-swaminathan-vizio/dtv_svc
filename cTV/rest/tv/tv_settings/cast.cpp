#include <iostream>
#include <bits/unique_ptr.h>
#include <handler.h>
#include "cast.h"
#include "common.h"
#include "argument.h"

#include <string.h>

#include "airplay.h"

#ifdef __cplusplus
extern "C" {
#include "u_cli.h"
#include "u_common.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"

#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "c_version.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "app_util/a_cfg.h"
#include "wizard_anim/a_wzd.h"
#ifdef LINUX_TURNKEY_SOLUTION
#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>
#endif
#include "c_os.h"
#include "c_net_config.h"
#include "u_dhcpc_api.h"
#include "u_net_common.h"
#include "u_net_ni_if.h"
#include "u_net_oid.h"
#include "u_net_socket.h"
#include "c_net_socket.h"
#include "c_net_p2p_ctl.h"

#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#include "rest_network.h"
#include "rest.h"
#include "rest/a_rest_event.h"
#include "mdns/a_mdns.h"
}
#endif


#define REST_MAC_ADDRESS_LEN  (32)

extern BOOL _rest_can_notify_ready_to_cast(VOID);

int device_name(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    UINT32  ui4_len = 128;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            #ifdef A_C4TV_APRON_CAST_NAME
            a_c4tv_apron_get_cast_name(str, &ui4_len);
            #else
            a_cfg_custom_get_tv_name(str, &ui4_len);
            #endif
            REST_LOG_I("str: %s\n\r", str);
            string_set_response(response, str);

            /* if (c_strlen(str) != 0) {
                _airplay_notify_to_airplay("device_name", 0, str);
            } */

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            CHAR    name[128] = {0};
            CHAR    s_ssid[256] = {0};
            UINT32  ui4_name_len = 128;
            #ifdef A_C4TV_APRON_CAST_NAME
            a_c4tv_apron_get_cast_name(name, &ui4_name_len);
            #else
            a_cfg_custom_get_tv_name(name, &ui4_name_len);
            #endif
            REST_LOG_I("Existed name: %s\n\r", name);
            rest_get_wifi_ssid(s_ssid);
            REST_LOG_I("Existed ssid: %s\n\r", s_ssid);

            string_get_string(root, str, ui4_len);

            /*The MAXnum of 24 support*/
            str[24] = '\0';
            REST_LOG_I("%s, %d, len of [%s]: %u!\n", __FUNCTION__, __LINE__, str, c_strlen(str));

            UINT32 ui4_index = 0;
            UINT32 ui4_index_new = 0;
            CHAR    str_name[128] = {0};
            c_memset(&str_name, 0, 128);
            for (ui4_index = 0; ui4_index < c_strlen(str);ui4_index++)
            {
            //    if (str[ui4_index] > 0 && str[ui4_index] < 177)
                {
                    str_name[ui4_index_new++] = str[ui4_index];
                }
            }
            str_name[127] = '\0';
            if (0 != c_strncmp(name, str_name, 128) || 0 != c_strncmp(s_ssid, str_name, 256))
            {
                REST_LOG_I("Save name:%s ssid:%s\n\r", str_name, s_ssid);
                #ifdef A_C4TV_APRON_CAST_NAME
                a_c4tv_apron_set_cast_name(str_name);
                #else
                a_cfg_custom_set_tv_name(str_name);
                #endif
                rest_change_softap_name(str_name);
                a_mdns_stop();
                a_mdns_start();

                REST_DATA_WIFI_AP_T t_ap;
                INT32 i4_ret = 0;
                c_memset(&t_ap, 0, sizeof(t_ap));
                i4_ret = rest_get_curr_access_point(&t_ap);

                /* VIZIO TV has no softap mode/
                if (i4_ret == RESTR_OK)
                {
                    // restart softap if the user doesn't skip Wi-Fi connection
                    REST_LOG_I("Restart softap\n\r", str_name);
                    rest_stop_softap();
                    rest_start_softap();
                }
                */

                rest_event_notify("tv_settings/cast/device_name", 0, str_name);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int serial_device_id(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            //CHAR    string[64] = "P-Series 50";
            CHAR    string[64] ={0};
            //const CHAR* str_ser;
            //str_ser = c_sys_get_serial_number();
#ifdef APP_ULI_UPG_SUPPORT
            INT32 i4_ret = 0;
            UINT32 ui4_buff_len = 64;
            i4_ret = a_uli_get_serial_number((UINT8 *)string, &ui4_buff_len);
            LOG_ON_ERR(i4_ret);
#endif
            //c_strncpy(string,str_ser,c_strlen(str_ser)+1);
            REST_LOG_I("string: %s\n\r", string);
            string_set_response(response, string);
            break;
        }
        //read only
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int google_privacy_policy(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    UINT32  ui4_len = 128;

//    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR    string[64] = "TRUE";
            REST_LOG_I("string: %s\n\r", string);
            string_set_response(response, string);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            string_get_string(root, str, ui4_len);
            REST_LOG_I("str: %s\n\r", str);
            if (!strncmp("TRUE", str, 4))
            {
                a_tv_custom_set_privacy(TRUE);
                REST_LOG_I("sbx set privacy %s \n\r",str);
            }
            else
            {
                REST_LOG_I("sbx set privacy %s \n\r",str);
                a_tv_custom_set_privacy(FALSE);
            }
#if 0
            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_BRI;//TO be chg
            t_toast.style.style_1.i4_value      = 0;

            rest_send_msg_to_nav(&t_toast);
#endif
            break;
        }
        default:
            break;
    }

    return 0;
}

int tos_accepted(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    UINT32  ui4_len = 128;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR    string_true[64] = "TRUE";
            CHAR    string_false[64] = "FALSE";

            if(a_tv_custom_get_tos() == TRUE) {
                REST_LOG_I("TOS is TRUE\n\r");
                string_set_response(response, string_true);
            } else {
                REST_LOG_I("TOS is FALSE\n\r");
                string_set_response(response, string_false);
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            string_get_string(root, str, ui4_len);
            REST_LOG_I("str: %s\n\r", str);
            if (!strncmp("TRUE", str, 4))
            {
                a_tv_custom_set_tos(TRUE);
                a_tv_custom_set_privacy(TRUE);
                a_c4tv_apron_resume_cast();
                a_c4tv_apron_accept_tos();
                a_tv_custom_set_viewing_data_show(TRUE);
                a_tv_custom_set_tos_version();
                REST_LOG_I("sbx set tos %s \n\r",str);
            }
            else
            {
                REST_LOG_I("sbx set tos %s \n\r",str);
                a_tv_custom_set_tos(FALSE);
                a_tv_custom_set_privacy(FALSE);
                a_tv_custom_clear_tos_version();
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

int soft_ap_config(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 i4_ret = 0;
            CHAR  s_mac[REST_MAC_ADDRESS_LEN+1] = {0};
            CHAR    str[128] = {0};
            UINT32  ui4_len = 128;

            Json::Value value;

            #ifdef A_C4TV_APRON_CAST_NAME
            a_c4tv_apron_get_cast_name(str, &ui4_len);//for ssid  to be check
            #else
             a_cfg_custom_get_tv_name(str, &ui4_len);
            #endif
            i4_ret = a_nw_get_mac_addr_string((CHAR*)NI_ETHERNET_0, s_mac);//for bssid
            LOG_ON_ERR(i4_ret);
            REST_LOG_I("REQUEST_GET ssid:%s,bssid:%s,\n\r",str,s_mac);
            value["HIDDEN"] = 1;
            value["SSID"] = std::string(str);
            value["BSSID"] = std::string(s_mac);//add by sbx for bssid

            response["VALUE"] = value;
            break;
        }
        //read only
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int start_soft_ap(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_ACTION:
        {
            rest_start_softap();
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

int stop_soft_ap(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_ACTION:
        {
            rest_stop_softap();
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

int soft_ap_status(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    struct ifreq ifr;
    int sockfd;
    INT32 indx = 0;
    Json::Value soft_sts;
    soft_sts[0]="Off";
    soft_sts[1]="On";
    response["ELEMENTS"]=soft_sts;
    response["VALUE"]=soft_sts[0];

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            c_memset(&ifr, 0, sizeof(struct ifreq));
            sockfd= socket(AF_INET, SOCK_DGRAM, 0);
            strcpy(ifr.ifr_name, "uap0");
            ioctl(sockfd, SIOCGIFFLAGS, &ifr);
            if (ifr.ifr_flags & IFF_UP && ifr.ifr_flags & IFF_RUNNING)//referenc to net_dev.c
            {
                REST_LOG_I("sbx stop_soft_ap status ON\n\r");
                indx = 1;
            }
            else
            {
                REST_LOG_I("sbx stop_soft_ap status OFF\n\r");
                indx = 0;
            }
            response["VALUE"]=soft_sts[indx];
            break;
        }
        //read only
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    close(sockfd);
    return 0;
}

int soft_ap_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            value_set_response(response, val);
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

int state(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            val = a_c4tv_apron_get_cast_state();
            REST_LOG_I("a_c4tv_apron_get_cast_state = %d\n\r", val);
            if ((val == 5 || val == 6)
                && _rest_can_notify_ready_to_cast() == FALSE) {
                REST_LOG_I("connection_status = FALSE\n\r");
                val = 3;
            } else {
                if (val == 5) {
                    val = 6;
                }
                REST_LOG_I("a_c4tv_apron_get_cast_state() = %d\n\r", val);
            }
            //value_set_response(response, val);
            response["VALUE"] = (int)val;
            response["VALUE"] = response["VALUE"].asInt();
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("Not imeplent SET type\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

int session_device_id(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR value[128] = {0};

            a_mdns_get_google_cast_id(value);
            string_set_response(response, value);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET, do nothing\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

int google_cast_id(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return session_device_id(root, response);
}

int google_cast_cd(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR value[128] = {0};
            a_mdns_get_google_cast_cd(value);
            string_set_response(response, value);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET, do nothing\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

handler cast_handler[] = {
        device_name,
        serial_device_id,
        google_privacy_policy,
        tos_accepted,
        soft_ap_config,
        start_soft_ap,
        stop_soft_ap,
        soft_ap_status,
        soft_ap_mode,
        state,
        session_device_id,
        google_cast_id,
        google_cast_cd
};

