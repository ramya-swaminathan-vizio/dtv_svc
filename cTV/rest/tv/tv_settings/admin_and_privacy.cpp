#include <iostream>
#include <bits/unique_ptr.h>
#include <handler.h>
#include "admin_and_privacy.h"
#include "common.h"
#include "argument.h"
#include "system.h"
#include "network.h"

#include <string.h>

#include "airplay.h"

#ifdef __cplusplus
extern "C" {
#include "u_cli.h"
#include "u_common.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"

#include "app_util/a_cfg.h"
#include "app_util/a_network.h"
#include "app_util/a_isl.h"

#include "res/app_util/network/network_custom.h"

#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "c_version.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "menu2/menu_common/menu_common.h"

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

#include "rest_network.h"
#include "rest.h"
#include "rest/a_rest_event.h"
#include "rest/a_rest_api.h"
#include "mmp/a_mmp.h"


extern INT32 a_isl_get_vtrl_input_display_name(ISL_REC_T*   pt_isl_rec,
                                            CHAR*         s_name);

}
#endif


int system_information_tv_information_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 i4_ret = -1;
            CHAR string[24] = {0};
            ISL_REC_T t_isl_rec;
            const CHAR* s_tmp_str;
            CHAR s_vtrl_name[24] = {0};
            /*Source Type*/
            SVL_REC_T t_svl_rec;
            BOOL b_found;
            UINT8 cast_state = 0;

            i4_ret = menu_get_crnt_isl(&t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);
            i4_ret = menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
            MENU_LOG_ON_FAIL(i4_ret);

            a_icl_custom_get_cast_src_status(&cast_state);

            if (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())
            {
                s_tmp_str = "MMP";
            }
            else if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
            {
                if (b_found && BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
                {
                    /*DTV*/
                    s_tmp_str = "DTV";
                }
                else
                {
                    /*ATV*/
                    s_tmp_str = "ATV";
                }
            }
            else if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type)
            {
                switch(t_isl_rec.t_avc_info.e_video_type)
                {
                    case DEV_AVC_S_VIDEO:
                    /*case DEV_AVC_COMBI:*/
                        /*AV*/
                        s_tmp_str = "AV";
                        break;
                    case DEV_AVC_COMP_VIDEO:
                    case DEV_AVC_COMBI:
                    case DEV_AVC_Y_PB_PR:
                        /*Composite*/
                        s_tmp_str = "Composite";
                        break;
                    case DEV_AVC_DVI:
                        /*DVI*/
                        s_tmp_str = "DVI";
                        break;
                    case DEV_AVC_HDMI:
                        /*HDMI*/
                        s_tmp_str = "HDMI";
                        break;
                    case DEV_AVC_VGA:
                        /*RGB*/
                        s_tmp_str = "RGB";
                        break;
                    default:
                        s_tmp_str = "AV";
                        break;
                }
            }
            else if (cast_state || DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
            {
                if(t_isl_rec.ui1_internal_id == 0)
                {
                    s_tmp_str = "SMARTCAST";
                }
                else
                {
                    a_isl_get_vtrl_input_display_name(&t_isl_rec,s_vtrl_name);
                    REST_LOG_I("get input:%s.\n\r", s_vtrl_name);
                    string_set_response(response, s_vtrl_name);
					break;
                }
            }
            else
            {
                s_tmp_str = "SMARTCAST";
            }

            c_strncpy(string, s_tmp_str, c_strlen(s_tmp_str));
            REST_LOG_I("get s_tmp_str:%s, string:%s.\n\r", s_tmp_str, string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_tv_information_frame_rate(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_tv_information_vertical_frequency(root, response);
}

int system_information_tv_information_audio_in(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_tv_information_audio_type(root, response);
}

int system_information_tv_information_audio_out(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_tv_information_audio_type_out(root, response);
}

int system_information_tv_information_bluetooth_version(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR bt_ver[64] = {0};
			menu_ver_info_bluetooth_ver(bt_ver, 64);
            REST_LOG_I("bt_ver: %s.\n\r", bt_ver);
            string_set_response(response, bt_ver);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_tv_information_display_hours(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            FLOAT f_value = 0;
            CHAR s_buf[32];

            if(a_is_oled_compensation_support())
            {
                menu_ver_info_accumulated_operating_hours(&f_value);
                REST_LOG_I("f_value = %d, %.1f\n", f_value, f_value);
                c_sprintf(s_buf, "%.1f", f_value);
            }
            else
            {
                c_strncpy(s_buf,"0",2);
            }
            REST_LOG_I("display_hours: %s.\n\r", s_buf);
            string_set_response(response, s_buf);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_network_information_wifi_network(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_ssid(root, response);
}

int system_information_network_information_id_mac_address(Json::Value & root, Json::Value & response){REST_LOG_I("Enter\n\r");return 0;}

int system_information_network_information_connection_type(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            //CHAR    string[64] = "wifi";
            CHAR    string[64] = {0};
            INT32           i4_ret =0;
            BOOL            b_plug = FALSE;
            i4_ret = a_nw_get_ethernet_connect_info(&b_plug);
            if(i4_ret)
            {
                c_strncpy(string,"UNKNOWN",8);
            }
            else
            {
                if(b_plug)
                {
                    c_strncpy(string,"Wired Connection",16);
                }
                else
                {
                    c_strncpy(string,"WIFI",5);
                }
            }
            REST_LOG_I("string: %s\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_network_information_wifi_security(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_network_information_security_type(root, response);
}

int system_information_remote_information_remote_status(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BT_REMOTE_INFO_T remote_info = {0};
            Json::Value v_remote_status;
            v_remote_status[0]="Paired, not connected";
            v_remote_status[1]="Not Paired, not connected";
            v_remote_status[2]="Paired, connected";

            ret = rest_get_bluetooth_status(&remote_info);
            REST_LOG_I("ret = %d , remote_status = %d.\n", ret, remote_info.remote_status);
            if(ret != 0 || remote_info.remote_status > 2)
            {
                remote_info.remote_status = 1;
            }
            response["VALUE"]=v_remote_status[remote_info.remote_status];
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_remote_information_remote_firmware(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BT_REMOTE_INFO_T remote_info = {0};
            CHAR string[64] = {0};

            ret = rest_get_bluetooth_status(&remote_info);
            REST_LOG_I("ret = %d , remote_status = %d.\n", ret, remote_info.remote_status);
            if(ret != 0 || remote_info.remote_status == 1)// remote_status == 1:NOT PAIRED
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, remote_info.firmware_version, c_strlen(remote_info.firmware_version));
            }
            REST_LOG_I("firmware_version string: %s.\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_remote_information_remote_serial_number(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BT_REMOTE_INFO_T remote_info = {0};
            CHAR string[64] = {0};

            ret = rest_get_bluetooth_status(&remote_info);
            REST_LOG_I("ret = %d , remote_status = %d.\n", ret, remote_info.remote_status);
            if(ret != 0 || remote_info.remote_status == 1)// remote_status == 1:NOT PAIRED
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, remote_info.serial_number, c_strlen(remote_info.serial_number));
            }
            REST_LOG_I("serial_number string: %s.\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_remote_information_bluetooth_firmware(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BINARIES_VERSION_T version = {0};
            CHAR string[64] = {0};

            ret = rest_get_binaries_version(&version);
            if(ret != 0)
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, version.bluetooth, c_strlen(version.bluetooth));
            }
            REST_LOG_I("version.bluetooth: %s.\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_remote_information_bluetooth_mac_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BT_REMOTE_INFO_T remote_info = {0};
            CHAR string[64] = {0};

            ret = rest_get_bluetooth_status(&remote_info);
            REST_LOG_I("ret = %d , remote_status = %d.\n", ret, remote_info.remote_status);
            if(ret != 0 || remote_info.remote_status == 1)// remote_status == 1:NOT PAIRED
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, remote_info.address, c_strlen(remote_info.address));
            }
            REST_LOG_I("bluetooth_mac_address string: %s.\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_application_information(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return 0;
}

int system_information_application_information_scpl(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR scpl_version[128] = {0};
            a_rest_get_Rest_Version(scpl_version);
            if(scpl_version[0] == 0)
            {
                c_strncpy(scpl_version,"N/A",4);
            }
            REST_LOG_I("get scpl version : %s.\n\r", scpl_version);
            string_set_response(response, scpl_version);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_application_information_airplay(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR airplay_version[1024] = {0};
            CHAR string[64] = {0};
            a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)airplay_version);
            if(c_strlen(airplay_version) == 0)
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, airplay_version, c_strlen(airplay_version));
            }
            REST_LOG_I("airplay_version: %s.\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_application_information_airplay_internal(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR str_version[64] = {0};
			menu_ver_info_airplay_internal_ver(str_version, 64);
            REST_LOG_I("get airplay internal ver: %s.\n\r", str_version);
            string_set_response(response, str_version);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_application_information_appletv(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
#if 0
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR str_version[64] = {0};
            menu_ver_info_apple_tv_ver(str_version, 64);
            REST_LOG_I("get airplay internal ver: %s.\n\r", str_version);
            string_set_response(response, str_version);
#else
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BINARIES_VERSION_T version = {0};
            CHAR string[64] = {0};

            ret = rest_get_binaries_version(&version);
            if(ret != 0)
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, version.appletv, c_strlen(version.appletv));
            }
            REST_LOG_I("version.appletv: %s.\n\r", string);
            string_set_response(response, string);
#endif
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_application_information_hbomax(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
#if 0
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR str_version[64] = {0};
            menu_ver_info_hbomax_ver(str_version, 64);
            REST_LOG_I("get airplay internal ver: %s.\n\r", str_version);
            string_set_response(response, str_version);
#else
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BINARIES_VERSION_T version = {0};
            CHAR string[64] = {0};

            ret = rest_get_binaries_version(&version);
            if(ret != 0)
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, version.hbomax, c_strlen(version.hbomax));
            }
            REST_LOG_I("version.hbomax: %s.\n\r", string);
            string_set_response(response, string);
#endif
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_application_information_castcore(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
#if 0
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR str_version[64] = {0};
            menu_ver_info_castcore_ver(str_version, 64);
            REST_LOG_I("get airplay internal ver: %s.\n\r", str_version);
            string_set_response(response, str_version);
#else
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BINARIES_VERSION_T version = {0};
            CHAR string[64] = {0};

            ret = rest_get_binaries_version(&version);
            if(ret != 0)
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, version.castcore, c_strlen(version.hbomax));
            }
            REST_LOG_I("version.castcore: %s.\n\r", string);
            string_set_response(response, string);
#endif
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}


int system_information_application_information_cobalt(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BINARIES_VERSION_T version = {0};
            CHAR string[64] = {0};

            ret = rest_get_binaries_version(&version);
            if(ret != 0)
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, version.cobalt, c_strlen(version.cobalt));
            }
            REST_LOG_I("version.cobalt: %s.\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_application_information_dai(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BINARIES_VERSION_T version = {0};
            CHAR string[64] = {0};

            ret = rest_get_binaries_version(&version);
            if(ret != 0)
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, version.dai, c_strlen(version.dai));
            }
            REST_LOG_I("version.dai: %s.\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_application_information_vizio_ndk(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            REST_API_BINARIES_VERSION_T version = {0};
            CHAR string[64] = {0};

            ret = rest_get_binaries_version(&version);
            if(ret != 0)
            {
                c_strncpy(string,"N/A",4);
            }
            else
            {
                c_strncpy(string, version.viziondk, c_strlen(version.viziondk));
            }
            REST_LOG_I("version.viziondk: %s.\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_uli_information_country(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32 ret = -1;
            ACFG_COUNTRY_CODE_T t_country;
            Json::Value v_country;
            v_country[0]="USA";
            v_country[1]="Mexico";
            v_country[2]="Canada";
            v_country[3]="Unknown";

            ret = a_cfg_custom_get_country_code(&t_country);
            REST_LOG_I("get country code = %d.\n", t_country);

            if(ret != 0 || t_country >= ACFG_COUNTRY_CODE_LAST_ENTRY)
            {
                t_country = ACFG_COUNTRY_CODE_US;
            }
            response["VALUE"]=v_country[t_country];
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_uli_information_display_hours(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return system_information_tv_information_display_hours(root, response);
}

int support_code(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET do nothing.\n\r");
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            if(menu_is_support_code_hidden())
            {
                REST_LOG_I("support_code is hidden, do nothing.\n\r");
            }
            else
            {
                rest_event_notify("app/current", 2, "12");
                menu_leave(FALSE,0);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}


int system_information_network_information_ipv6_address(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return network_information_ipv6_address(root, response);
}

int system_information_network_information_ipv6_gateway(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return network_information_ipv6_gateway(root, response);
}

int system_information_network_information_ipv6_prefix_len(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return network_information_ipv6_prefix_len(root, response);
}

int system_information_network_information_ipv6_preferred_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return network_information_ipv6_pref_dns_server(root, response);
}

int system_information_network_information_ipv6_alternate_dns_server(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return network_information_ipv6_alt_dns_server(root, response);
}

handler tv_settings_admin_and_privacy_handler[] = {
    system_information_tv_information_input,
    system_information_tv_information_frame_rate,
    system_information_tv_information_audio_in,
    system_information_tv_information_audio_out,
    system_information_tv_information_bluetooth_version,
    system_information_tv_information_display_hours,
    system_information_network_information_wifi_network,
    system_information_network_information_id_mac_address,
    system_information_network_information_connection_type,
    system_information_network_information_wifi_security,
    system_information_remote_information_remote_status,
    system_information_remote_information_remote_firmware,
    system_information_remote_information_remote_serial_number,
    system_information_remote_information_bluetooth_firmware,
    system_information_remote_information_bluetooth_mac_address,
    system_information_application_information,
    system_information_application_information_scpl,
    system_information_application_information_airplay,
    system_information_application_information_airplay_internal,
    system_information_application_information_appletv,
    system_information_application_information_hbomax,
    system_information_application_information_castcore,
    system_information_application_information_cobalt,
    system_information_application_information_dai,
    system_information_application_information_vizio_ndk,
    system_information_uli_information_country,
    system_information_uli_information_display_hours,
    support_code,
    system_information_network_information_ipv6_address,
    system_information_network_information_ipv6_gateway,
    system_information_network_information_ipv6_prefix_len,
    system_information_network_information_ipv6_preferred_dns_server,
    system_information_network_information_ipv6_alternate_dns_server
};

