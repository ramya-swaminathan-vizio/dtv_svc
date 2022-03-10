#include <iostream>
#include <handler.h>
#include "system.h"
#include "common.h"
#include "argument.h"
#include <sys/time.h>
#include <string.h>
#include <bits/unique_ptr.h>

#include <dlfcn.h>
#include "pin.h"

#include "airplay.h"

#ifdef __cplusplus
extern "C" {
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/updater/nav_updater.h"

#include "app_util/a_cfg.h"
#include "app_util/a_icl.h"
#include "app_util/a_icl_common.h"
#include "app_util/a_network.h"
#include "res/app_util/network/network_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/icl/a_icl_custom.h"


#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "app_util/config/acfg_cust_misc.h"

#include "app_util/config/_acfg.h"
#include "c_version.h"
#include "c_svctx.h"
#include "x_os.h"

#include "c_os.h"
#include "u_common.h"
#include "u_scc.h"
#include "c_tsl.h"
#include "mmp/a_mmp.h"
#include "nav/nav_common.h"
#include "wizard_anim/a_wzd.h"
#include "res/nav/nav_mlm.h"
#include "wdk/vkb/vkb.h"
#include "res/menu2/menu_custom.h"
#include "c_dt.h"
#include "rest_network.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/banner2/banner.h"
#include "nav/input_src/a_input_src.h"
#ifdef APP_CEC_SUPPORT
#include "app_util/a_cec.h"
#include "nav/cec2/nav_cec.h"
#endif
#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif
#include "nav/screen_mode/a_screen_mode.h"
#include "res/app_util/dst/a_dst_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "u_net_socket.h"
#include "c_net_socket.h"
#include "c_cecm.h"
#ifdef LINUX_TURNKEY_SOLUTION
#include <sys/ioctl.h>
#include <net/if.h>
#include <errno.h>
#endif

#ifdef APP_BLUETOOTH_SUPPORT
#include "mtk_bt_service_gap_wrapper.h"
#endif

#include "wizard/page/wzd_page_nw_setup.h"

#include "rest/a_rest.h"
#include "rest/a_rest_event.h"
#include "rest/a_rest_api.h"
#include "rest/rest_system.h"
#include "mdns/a_mdns.h"

#include "c_speedtest_async.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/uli/uli_custom.h"

#include "c_pcl.h"

#include "registry/a_registry.h"

}
#endif
extern "C" INT32 menu_ver_info_get_audio_stream_text(CHAR* str_type, SIZE_T z_len);
BOOL _wlan_status(VOID);
static VOID _time_local_setting_country_info_thread_main (VOID* pv_arg);
int country(Json::Value & root, Json::Value & response);

#include "picture_ex.h"

#include <string>
#include <fstream>
#define MODEL_NAME_LEN        16+1
#define PROPERTY_VALUE         92
#define NETWORK_SPEED_LEN     (16)
#define SVCTX_NAME_MAIN       "main_svctx"
#define SVCTX_NAME_SUB        "sub_svctx"

#define ACR_ON             ((UINT8)1)
#define ACR_OFF            ((UINT8)0)
#ifdef APP_ULI_UPG_SUPPORT
/* status mask flags */
#define ULI_STATUS_MASK_REGISTERED                         0x0001
#define ULI_STATUS_MASK_FACTORY_TEST_MODE                  0x0002
#define ULI_STATUS_MASK_FIELD_TEST_MODE                    0x0004
#define ULI_STATUS_MASK_LOOP_TEST_MODE                     0x0008
#endif

#define CUST_TUNER_LG_TDVWH810F   0x71
#define CUST_TUNER_SS_DTVS203     0x72
#define CUST_TUNER_SONY           0x73
#define CUST_TUNER_NXP_TDA18273   0x74
#define CUST_TUNER_SS_DTVS20C     0x75
#define CUST_TUNER_SONY_RE215     0x76
#define CUST_TUNER_SILICON_TUNERA 0x77
#define CUST_TUNER_SHARP_VA1G2CD  0x78
#define CUST_TUNER_TCL_F20WT      0x79
#define CUST_TUNER_SILABS_SI2158  0x80
#define CUST_TUNER_Mxl_MXL601     0x81
#define CUST_TUNER_NXP_TDA18274   0x82
#define CUST_TUNER_SONY_RB221     0x83
#define CUST_TUNER_SONY_RA217     0x84
#define CUST_TUNER_LG_TDSTH570F   0x85
#define CUST_TUNER_SILABS_SI2157  0x86
#define CUST_TUNER_SONY_RA227     0x87
#define CUST_TUNER_NXP_TDA18275   0x88
#define CUST_TUNER_ML_MXL661      0x89
#define CUST_TUNER_SILABS_SI2151  0x8F
#define CUST_TUNER_SONY_RA231     0x90
#define CUST_TUNER_NXP_TDA182I5a  0x91

/*
*  0-eng, 1-spa, 2-fre
*  map to
*  0-eng, 1-fre, 2-spa
*/
static UINT16 sys_lang_id[3] = {REST_LANG_ENG, REST_LANG_SPA, REST_LANG_FRE};

TvSettingsGroupURI tvSettingsSystemUri[] = {
        /*
        # SYSTEM
        */

        { "system_information" , "tv_information" , "cast_name" },
        { "system_information" , "tv_information" , "serial_number" },
        { "system_information" , "tv_information" , "model_name" },
        { "system_information" , "tv_information" , "version" },
        { "system_information" , "tv_information" , "cast_version" },
        { "system_information" , "tv_information" , "source_type" },
        { "system_information" , "tv_information" , "resolution" },
        { "system_information" , "tv_information" , "vertical_frequency" },
        { "system_information" , "tv_information" , "hdr" },
        { "system_information" , "tv_information" , "audio_type" },
        { "system_information" , "tv_information" , "frc_version" },
        { "system_information" , "tv_information" , "netflix_esn" },
        { "system_information" , "tv_information" , "netflix_esn2" },
        { "system_information" , "network_information" , "connection_type" },
        { "system_information" , "network_information" , "ssid" },
        { "system_information" , "network_information" , "security_type" },
        { "system_information" , "network_information" , "ip_address" },
        { "system_information" , "network_information" , "gateway" },
        { "system_information" , "network_information" , "subnet_mask" },
        { "system_information" , "network_information" , "preferred_dns_server" },
        { "system_information" , "network_information" , "alternate_dns_server" },
        { "system_information" , "network_information" , "download_speed" },
        { "system_information" , "network_information" , "wifi_signal_strength" },
        { "system_information" , "network_information" , "rssi" },
        { "system_information" , "network_information" , "wifi_channel" },
        { "system_information" , "network_information" , "rj45_mac_address" },
        { "system_information" , "network_information" , "wlan_mac_address" },
        { "system_information" , "network_information" , "bt_mac_address" },
        { "system_information" , "uli_information" , "esn" },
        { "system_information" , "uli_information" , "uid" },
        { "system_information" , "uli_information" , "mv" },
        { "system_information" , "uli_information" , "sv" },
        { "system_information" , "uli_information" , "reg" },
        { "system_information" , "uli_information" , "fet" },
        { "system_information" , "uli_information" , "lt" },
        { "system_information" , "uli_information" , "np" },
        { "system_information" , "uli_information" , "ldt" },
        { "system_information" , "uli_information" , "ldm" },
        { "system_information" , "uli_information" , "ec" },
        { "system_information" , "uli_information" , "le" },
        { "system_information" , "uli_information" , "let" },
        { "system_information" , "uli_information" , "rd" },
        { "reset_and_admin" , "service_reset" },
        { "service_check" },
        { "local_time_settings" , "use_internet_time" },
        { "local_time_settings" , "date_time" },
        { "local_time_settings" , "timezone" },
        { "local_time_settings" , "daylight_savings_time" },
        { "local_time_settings" , "time_format" },
        { "local_time_settings" , "country" },
        { "menu_language" },
        { "cec" , "cec_function" },
        { "cec" , "device_discovery" },
        { "reset_and_admin" , "power_indicator" },
        { "reset_and_admin" , "usb_power" },
        { "reset_and_admin" , "factory_reset" },
        { "reset_and_admin" , "vizio_privacy_policy" },
        { "reset_and_admin" , "smart_interactivity" },
        { "reset_and_admin" , "store_demo" },
        { "system_information" , "tuner_information" , "physical_channel" },
        { "system_information" , "tuner_information" , "frequency" },
        { "system_information" , "tuner_information" , "modulation" },
        { "system_information" , "tuner_information" , "status" },
        { "system_information" , "tuner_information" , "signal_strength" },
        { "system_information" , "tuner_information" , "name" },
        { "country" },
        { "power_mode" },
        { "aspect_ratio" },
        { "cast_name" },
        { "reset_and_admin" , "system_pin" },
        { "system_information" , "tv_information" , "series" },
        { "system_information" , "tv_information" , "size" },
        { "accessibility","talkback" },
        { "accessibility","speech_rate" },
        { "accessibility","zoom_mode" },
        { "system_information" , "tv_information" , "audio_type_out" },
        { "system_information" , "network_information" , "wifi_module" },
        { "system_information" , "tv_information" , "airplay_version" },
        { "input_at_power_on" },
        { "" },

};

const int MAX_HDMI_INPUT = 5;//dolphin said it was infact defined in menu_page_cec.c

typedef struct _cec_node
{
    int i4_hdmi_id;
    char p_cec_name[32];
}_CEC_NODE;

_CEC_NODE _cec_node_list[MAX_HDMI_INPUT]; //record the cec list in the local memory
unsigned char ui1_display_device_count =0;  //record the cec dev number


int system_information_tv_information_cast_name(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR    str[128] = {0};
            UINT32  ui4_len = 128;
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

int system_information_tv_information_serial_number(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR    string[64] = "1234";
            INT32 i4_ret = 0;

#ifdef APP_ULI_UPG_SUPPORT
            UINT32 ui4_buff_len = 64;
            CHAR    str_sn[64] = {0};
            UINT32  ui4_digs_len = 0;
            c_memset(string, 0, sizeof(string));
            i4_ret = a_uli_get_serial_number((UINT8 *)str_sn, &ui4_buff_len);
            //LOG_ON_ERR(i4_ret);
            if (ui4_buff_len < 15)
            {
                c_strncpy(string, str_sn + 2, 2);
                c_strncat(string, str_sn, 2);
                c_strncat(string, str_sn + 6, 2);
                c_strncat(string, str_sn + 4, 2);
                c_strncat(string, str_sn + 8, 5);

                ui4_digs_len = c_strlen(string);
                c_strcat(string, str_sn + ui4_digs_len);
            }
            else
            {
                c_strncpy(string, str_sn + 8, 2);
                c_strncat(string, str_sn, 8);

                ui4_digs_len = c_strlen(string);
                c_strcat(string, str_sn + ui4_digs_len);
            }
#endif
            if ((i4_ret!=REST_R_OK) || (0==strcmp(string,"")))
            {
                i4_ret =34;  //dolphin 20200508 vizio SCPL need this error code while sn empty
                a_nw_get_mac_addr_string((CHAR*)NI_WIRELESS_0, string);

                if(0==strcmp(string,""))
                {
                    REST_LOG_I("RJ45 MAC\n\r");
                    a_nw_get_mac_addr_string((CHAR*)NI_ETHERNET_0, string);
                }
                else
                {
                    REST_LOG_I("WIFI MAC\n\r");
                }
            }

            REST_LOG_I("string: %s.\n\r", string);
            string_set_response(response, string);

            /* write to tmp */
            //char cmd[64];
            //memset(cmd, 0, 64);
            //snprintf(cmd, 64, "echo \"%s\" > /tmp/serial_number", string);
            //system(cmd);
            s_echo((CHAR*)"/tmp/serial_number",string,strlen(string));
            DBG_LOG_PRINT(("[REST][chris] Write %s to /tmp/serial_number\n\r", string));

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

    return i4_ret;
}

int system_information_tv_information_model_name(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR s_model_name[32] = {0};

            i4_ret = a_cfg_custom_get_model_name(s_model_name);
            LOG_ON_ERR(i4_ret);
            if (c_strlen(s_model_name) == 0)
            {
                c_strncpy(s_model_name, "V405-H9", strlen("V405-H9"));
            }

            REST_LOG_I("s_model_name: %s\n\r", s_model_name);
            string_set_response(response, s_model_name);
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

void print_hex(char *p,int len)
{
     for(int i=0;i<len;i++)
    {
        REST_LOG_E("Byte[%d]=0x%x\n",i,p[i]);
    }
}

int system_information_tv_information_version(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            CHAR    ver_string[64] ={0};
            //CHAR*   p_ver_string;
            CHAR*   str_ver;
            //long    tmp;

            //str_ver = c_sys_get_version();
            str_ver = sys_cust_get_usb_upg_version();
            //dolphin remove '\n' 20200420
            //print_hex(str_ver,64);
            //REST_LOG_E("Get length %d\n",strlen(str_ver));
            if(strlen(str_ver) >=1 && str_ver[strlen(str_ver)-1] == '\n')
            {
                REST_LOG_E("Get '\\n' ,just remove\n");
                str_ver[strlen(str_ver)-1]= '\0';
            }

            c_strncpy(ver_string, str_ver, 63);
            //p_ver_string = ver_string;
            //p_ver_string++;
            //tmp = strtol(p_ver_string+c_strlen(p_ver_string)-1, NULL, 10);
            /*if (tmp == 0
                && c_strcmp(p_ver_string+c_strlen(p_ver_string)-1, "0") != 0) {
                REST_LOG_I("Remove tailed char\n\r");
                p_ver_string[c_strlen(p_ver_string)-1] = 0;
            }*/
            REST_LOG_I("string: %s\n\r", ver_string);
            //print_hex(str_ver,64);

            string_set_response(response, ver_string);

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

HANDLE_T rest_get_crnt_tsl(VOID)
{
    INT32       i4_ret;
    UINT16      ui2_crnt_svl_id;
    HANDLE_T    h_tsl;

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        h_tsl = NULL_HANDLE;
    }
    else
    {
         if(ui2_crnt_svl_id == 1)
        {
            c_tsl_open(ATSC_TRSTRL_TSL_ID,NULL,NULL,&h_tsl);
        }
        else
        {
            c_tsl_open(ATSC_CABLE_TSL_ID,NULL,NULL,&h_tsl);
        }
     }
    return h_tsl;
}
HANDLE_T rest_get_crnt_svl(VOID)
{
    INT32       i4_ret;
    UINT16      ui2_crnt_svl_id;
    HANDLE_T    h_svl;

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        h_svl = NULL_HANDLE;
    }
    else
    {
         if(ui2_crnt_svl_id == 1)
        {
            c_svl_open(ATSC_TRSTRL_SVL_ID,NULL,NULL,&h_svl);
        }
        else
        {
            c_svl_open(ATSC_CABLE_SVL_ID,NULL,NULL,&h_svl);
        }
     }
    return h_svl;
}
INT32 rest_get_crnt_svl_rec(SVL_REC_T* pt_svl_rec, BOOL* pb_found)
{
    INT32       i4_ret;
    UINT32      ui4_channel_id;
    UINT32      ui4_ver_id;
    HANDLE_T    h_svl;

    if(pt_svl_rec == NULL ||
       pb_found == NULL)
    {
        return REST_R_ERR;
    }

    /* Get the current channel id */
    ui4_channel_id = a_util_cnfg_get_crnt_channel_id();

    /* Get current SVL */
    h_svl = rest_get_crnt_svl();

    /* Find current svl record */
    *pb_found = FALSE;
    if (INVALID_CHANNEL_ID != ui4_channel_id)
    {
        i4_ret = c_svl_get_rec_by_channel(h_svl,
                                          ui4_channel_id,
                                          SB_VNET_ALL,
                                          0,
                                          pt_svl_rec,
                                          &ui4_ver_id);
        if (i4_ret == SVLR_OK)
        {
            *pb_found = TRUE;
        }
    }

    return REST_R_OK;
}

HANDLE_T rest_get_crnt_svctx(VOID)
{
    TV_WIN_ID_T     t_win_id = TV_WIN_ID_MAIN;
    HANDLE_T        h_crnt_svctx = NULL_HANDLE;
    INT32 i4_ret = 0;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    if (REST_R_OK == i4_ret)
    {
        nav_get_svctx_handle(t_win_id,&h_crnt_svctx);
        return h_crnt_svctx;
    }
    else
    {
        REST_LOG_I("[NAV REVOLT_MISC] Could not get current svctx. \n");
    }

    return NULL_HANDLE;
}
INT32 rest_get_crnt_isl(ISL_REC_T* pt_isl_rec)
{
    INT32           i4_ret;
    TV_WIN_ID_T     t_win_id;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    LOG_ON_ERR(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id,
                                        pt_isl_rec);
    LOG_ON_ERR(i4_ret);

    return REST_R_OK;
}

UINT32 a_rest_get_cast_version_build_number(VOID)
{
    Json::Reader reader;
    Json::Value  rooter;
    std::ifstream fd;
    UINT32 build_num=0;

    fd.open("/chrome/cast_receiver_build_property.json",std::ios::binary);
    if (reader.parse(fd,rooter))
    {
        build_num = rooter["cast_receiver_build_number"].asInt();
    }
    fd.close();

    return build_num;
}

int system_information_tv_information_country(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR str[64] = {0};
    WDK_TOAST_T t_toast;

    type = get_type(root);

    Json::Value country;
    country[0] = "USA";
    country[1] = "Canada";
    country[2] = "Mexico";
    country[3] = "Unknown";

    response["ELEMENTS"]=country;

    INT32 indx = 0;
    UINT16	crnt_indx = 0;

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    ACFG_COUNTRY_CODE_T t_country = ACFG_COUNTRY_CODE_US;
    a_cfg_custom_get_country_code(&t_country);
    switch (t_country)
    {
        case ACFG_COUNTRY_CODE_UNKNOWN:
            indx = 3;
            break;
        case ACFG_COUNTRY_CODE_MEX:
            indx = 2;
            break;
        case ACFG_COUNTRY_CODE_CA:
            indx = 1;
            break;
        case ACFG_COUNTRY_CODE_US:
        default:
            indx = 0;
            break;
    }
#endif
    crnt_indx = indx;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET crnt_indx:%d\n\r",crnt_indx);
            response["VALUE"]=country[indx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            UINT16	ui2_status	  = 0;
            UINT8	ui1_state	  = 0;

            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str, item1.asString().c_str());

            if (c_strcmp(str, "USA") == 0)
            {
                indx = 0;
                t_country = ACFG_COUNTRY_CODE_US;
                if (_wlan_status())
                {
//#ifdef MT5583_MODEL
//                    system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=0");
//#else
                    system("wpa_cli -i wlan0 set country=US");
//#endif
                }
            }
            else if (c_strcmp(str, "Canada") == 0)
            {
                indx = 1;
                t_country = ACFG_COUNTRY_CODE_CA;
                if (_wlan_status())
                {
//#ifdef MT5583_MODEL
//                    system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=1");
//#else
                    system("wpa_cli -i wlan0 set country=CA");
//#endif
                }
            }
            else if (c_strcmp(str, "Mexico") == 0)
            {
                indx = 2;
                t_country = ACFG_COUNTRY_CODE_MEX;
                if (_wlan_status())
                {
//#ifdef MT5583_MODEL
//                    system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=2");
//#else
                    system("wpa_cli -i wlan0 set country=MX");
//#endif
                }
            }
            else if (c_strcmp(str, "Unknown") == 0)
            {
                indx = 3;
                t_country = ACFG_COUNTRY_CODE_UNKNOWN;
                if (_wlan_status())
                {
//#ifdef MT5583_MODEL
//                    system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=5");
//#else
                    system("wpa_cli -i wlan0 set country=WW");
//#endif
                }
            }

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
            a_cfg_custom_set_country_code(t_country);
#endif
            REST_LOG_I("sbx set country side %d \n\r",t_country);

            RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
            ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

            REST_LOG_I("oobe [state= %d]\n\r", (int)ui1_state);
#ifdef APP_C4TV_SUPPORT
            if(WZD_STATE_RESUME_C4TV != ui1_state)
#endif
            {
                c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

                t_toast.e_toast_style  = WDK_STRING_TOAST;
                t_toast.e_string_style = WDK_STRING_ID_ID;
                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_COUNTRY;
                if (0 == indx)
                {
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_COUNTRY_USA;
                }
                else if (1 == indx)
                {
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_COUNTRY_CANADA;
                }
                else if (2 == indx)
                {
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_COUNTRY_MEXICO;
                }
                else if (3 == indx)
                {
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_COUNTRY_UNKNOWN;
                }

                REST_LOG_I("send country notification \n\r");
                if (indx != crnt_indx)
                {
                    rest_send_msg_to_nav(&t_toast);
                }
                HANDLE_T h_thread;
                if (x_thread_create(& h_thread,
                                    "_thread_time_smartcastapp_reset_3rd_info",
                                    8192,
                                    127,
                                    _time_local_setting_country_info_thread_main,
                                    0,
                                   NULL) != OSR_OK)
                {
                    REST_LOG_E("_time_local_setting_country_info_thread_main create fail.\n");
                }
            }
            break;
        }
        default:
        break;
    }
    return 0;

}

int system_information_tv_information_cast_version(Json::Value & root, Json::Value & response)
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
            UINT32 ui4_cast_builder_name_len=64;
            CHAR    string[64] = {0};//"1.19";
#if 0
            CHAR    string_inc[64] = {0};
            FILE *stream;
            Json::Reader reader;
            Json::Value  rooter;
            std::ifstream fd;
            UINT32 build_num=0;
            stream = popen("getprop ro.build.version.release","r");
            fread(string,1,4,stream);
            c_strncat(string,".",1);

            fd.open("/chrome/cast_receiver_build_property.json",std::ios::binary);
            if (reader.parse(fd,rooter))
            {
                build_num = rooter["cast_receiver_build_number"].asInt();
                REST_LOG_I("cast_receiver_build_number: %d\n\r", build_num);
            }
            c_sprintf(string_inc,"%d\0",build_num);
            c_strncat(string,string_inc,c_strlen(string_inc));
            fd.close();
#endif
            a_c4tv_apron_get_cast_builder_name(string,&ui4_cast_builder_name_len);
            REST_LOG_I("release_version of cast: %s\n\r", string);
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

int system_information_tv_information_chromium_version(Json::Value & root, Json::Value & response)
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
            CHAR string[64] = {0};
            a_rest_get_conjure_version(string);
            REST_LOG_I("release_version of chromium: %s.\n\r", string);
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

int system_information_tv_information_scpl_version(Json::Value & root, Json::Value & response)
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
            CHAR string[64] = {0};
            if(0 != rest_get_device_info(string) || c_strlen(string) == 0)
            {
                c_strncpy(string,"N/A",4);
            }
            REST_LOG_I("release_version of scpl: %s.\n\r", string);
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

int system_information_tv_information_amazon_version(Json::Value & root, Json::Value & response)
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
            CHAR string[64] = {0};
            a_rest_get_amazon_version(string);
            REST_LOG_I("release_version of amazon: %s\n\r", string);
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

int system_information_tv_information_source_type(Json::Value & root, Json::Value & response)
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
            //CHAR    string[64] = "Cast";
            CHAR    string[64] = {0};
            ISL_REC_T   t_isl_rec;
            SVL_REC_T   t_svl_rec;
            BOOL        b_found;
            INT32           i4_ret=0;
            UINT8        cast_state = 0;

            i4_ret = rest_get_crnt_isl(&t_isl_rec);
            LOG_ON_ERR(i4_ret);
            i4_ret = rest_get_crnt_svl_rec(&t_svl_rec, &b_found);
            LOG_ON_ERR(i4_ret);

            a_icl_custom_get_cast_src_status(&cast_state);

            if (MMP_MAIN_AP_STATUS_RESUMED == a_mmp_get_ap_status())
            {
                c_strncpy(string,"MMP",4);
            }
            else if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
            {
                if (b_found && BRDCST_TYPE_ANALOG != t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)
                {
                    /*DTV*/
                    c_strncpy(string,"DTV",4);
                }
                else
                {
                    /*ATV*/
                    c_strncpy(string,"ATV",4);
                }
            }
            else if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type)
            {
                switch(t_isl_rec.t_avc_info.e_video_type)
                {
                    case DEV_AVC_COMP_VIDEO:
                    case DEV_AVC_S_VIDEO:
                    /*case DEV_AVC_COMBI:*/
                        /*AV*/
                        c_strncpy(string,"AV",3);
                        break;
                    case DEV_AVC_COMBI:
                    case DEV_AVC_Y_PB_PR:
                        /*Composite*/
                        c_strncpy(string,"Component",10);
                        break;
                    case DEV_AVC_DVI:
                        /*DVI*/
                        c_strncpy(string,"DVI",4);
                        break;
                    case DEV_AVC_HDMI:
                        /*HDMI*/
                        c_strncpy(string,"HDMI",5);
                        break;
                    case DEV_AVC_VGA:
                        /*RGB*/
                        c_strncpy(string,"RGB",4);
                        break;
                    default:
                        c_strncpy(string,"AV",3);
                        break;
                }
            }
            else if (cast_state || DEV_VTRL_CAST == t_isl_rec.t_avc_info.e_video_type)
            {
                REST_LOG_E("string: %s\n\r", string);
                c_strncpy(string,"SMARTCAST",9);
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

int system_information_tv_information_resolution(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret=0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR string[64] = {0};
            menu_ver_info_get_resolution(string);
            REST_LOG_I("get_resolution: %s.\n\r", string);
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

int system_information_tv_information_vertical_frequency(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret=0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            FLOAT f_frame_rate = 0;
            VSH_SRC_RESOLUTION_INFO_T t_res;

            f_frame_rate = menu_ver_info_get_vertical_frequency();
            REST_LOG_I("vertical_frequency: %2f\n\r", f_frame_rate);
            value_set_response(response, (INT32)f_frame_rate);
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET is not supported.\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

int system_information_tv_information_vrr(Json::Value & root, Json::Value & response)
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
            CHAR string[64] = {0};
			menu_ver_info_get_vss(string);
            REST_LOG_I("menu_ver_info_get_vss:%s.\n\r", string);
            string_set_response(response, string);
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

int system_information_tv_information_hdr(Json::Value & root, Json::Value & response)
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
            CHAR string[64] = "No";
            REST_LOG_I("string: %s\n\r", string);
#ifdef APP_HDR_SUPPORT
            ver_info_get_hdr_type(string);
#endif
            string_set_response(response, string);
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

int system_information_tv_information_audio_type(Json::Value & root, Json::Value & response)
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
            CHAR    string[128] = {0};
            menu_ver_info_get_audio_stream_text(string, 127);
            REST_LOG_I("get_audio_stream_text: %s.\n\r", string);
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
int system_information_tv_information_audio_type_out(Json::Value & root, Json::Value & response)
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
            CHAR string[64] = {0};
            menu_ver_info_get_audio_type_out(string);
            REST_LOG_I("get_audio_type_out: %s\n\r", string);
            string_set_response(response, string);
            break;
        }
        //READ ONLY
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

int system_information_tv_information_frc_version(Json::Value & root, Json::Value & response)
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
            CHAR    string[64] = "frc_ver";
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

int system_information_tv_information_netflix_esn(Json::Value & root, Json::Value & response)
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
            CHAR    string[256] = "N/A";
            FILE * pFile = NULL;

            pFile = fopen ("/certificate/netflix/ESNID","r");
            if (pFile != NULL)
            {
                c_memset(string, 0, sizeof(string));
                fgets(string, sizeof(string)-1, pFile);
                fclose(pFile);
            }
            REST_LOG_I("string: %s.\n\r", string);
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

int system_information_tv_information_netflix_esn2(Json::Value & root, Json::Value & response)
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
            CHAR string[256] = "N/A";
            FILE *pFile = NULL;

            pFile = fopen ("/certificate/netflix/ESNID","r");
            if (pFile != NULL)
            {
                c_memset(string, 0, sizeof(string));
                fgets(string, sizeof(string)-1, pFile);
                fclose(pFile);
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

int system_information_network_information_ssid(Json::Value & root, Json::Value & response)
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
            CHAR  s_ssid[REST_SSID_MAX_LEN+1] = {0};
            NET_802_11_BSS_INFO_T       t_CurrBss;
            c_memset (&t_CurrBss, 0, sizeof(t_CurrBss));
            a_nw_wlan_get_curr_bss(&t_CurrBss);
            if (t_CurrBss.t_Ssid.ui4_SsidLen > 0)
            {
                c_strncpy(s_ssid, t_CurrBss.t_Ssid.ui1_aSsid, REST_SSID_MAX_LEN);
            }
            else
            {
                c_strcpy(s_ssid, "N/A");
            }

            REST_LOG_I("\n\n------------- Current BSS info: -------------\n");
            REST_LOG_I("ssid:\t\t %s\n", s_ssid);

            string_set_response(response, s_ssid);
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

int system_information_network_information_security_type(Json::Value & root, Json::Value & response)
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
            CHAR    em[REST_DATA_EM_LEN+1] = {0};

            rest_get_curr_ap_security_type(em);
            REST_LOG_I("string: %s\n\r", em);
            string_set_response(response, em);
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

#define REST_ACCESS_POINT_LEN (32)
#define REST_IP_ADDRESS_LEN   (32)
#define REST_MAC_ADDRESS_LEN  (32)

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

int system_information_network_information_ip_address(Json::Value & root, Json::Value & response)
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

            CHAR  s_ip_address[REST_IP_ADDRESS_LEN+1] = {0};
            NW_IP_INFO_T t_ip_info = {0};

            a_nw_custom_get_ip_info(&t_ip_info);

            _rest_get_ip_address(s_ip_address, t_ip_info.ui4_address);

            REST_LOG_I("IP: %s\n\r", s_ip_address);

            response["VALUE"] = std::string(s_ip_address);
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

int system_information_network_information_gateway(Json::Value & root, Json::Value & response)
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

            NW_IP_INFO_T t_ip_info = {0};
            INT32 i4_ret = 0;
            CHAR  s_gateway[REST_IP_ADDRESS_LEN+1] = {0};

            i4_ret = a_nw_custom_get_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_gateway, t_ip_info.ui4_gw);
            LOG_ON_ERR(i4_ret);
            REST_LOG_I("gateway: %s\n\r", s_gateway);

            response["VALUE"] = std::string(s_gateway);
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

int system_information_network_information_subnet_mask(Json::Value & root, Json::Value & response)
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

            NW_IP_INFO_T t_ip_info = {0};
            INT32 i4_ret = 0;
            CHAR  s_subnet_mask[REST_IP_ADDRESS_LEN+1] = {0};

            REST_LOG_I("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);

            i4_ret = a_nw_custom_get_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_subnet_mask, t_ip_info.ui4_netmask);
            LOG_ON_ERR(i4_ret);

            response["VALUE"] = std::string(s_subnet_mask);
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

int system_information_network_information_preferred_dns_server(Json::Value & root, Json::Value & response)
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

            NW_IP_INFO_T t_ip_info = {0};
            INT32 i4_ret = 0;
            CHAR  s_dns[REST_IP_ADDRESS_LEN+1] = {0};

            REST_LOG_I("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);

            i4_ret = a_nw_custom_get_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_dns, t_ip_info.ui4_1st_dns);
            LOG_ON_ERR(i4_ret);

            response["VALUE"] = std::string(s_dns);
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

int system_information_network_information_alternate_dns_server(Json::Value & root, Json::Value & response)
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

            NW_IP_INFO_T t_ip_info = {0};
            INT32 i4_ret = 0;
            CHAR  s_dns[REST_IP_ADDRESS_LEN+1] = {0};

            REST_LOG_I("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);

            i4_ret = a_nw_custom_get_ip_info(&t_ip_info);
            LOG_ON_ERR(i4_ret);

            i4_ret = _rest_get_ip_address(s_dns, t_ip_info.ui4_2nd_dns);
            LOG_ON_ERR(i4_ret);

            response["VALUE"] = std::string(s_dns);
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

static float   i4_sys_speed = 0;

static VOID _rest_SpeedtestNtyFct(
                INT32               i4Status,
                DOUBLE              u4Speed)
{
    DBG_LOG_PRINT(("\n %s,%s,%d,i4Status=%d,u4Speed=%f\n",
                __FILE__, __FUNCTION__, __LINE__,  i4Status, u4Speed));
    /* store speed value */
    nw_custom_set_speed(u4Speed);

    if(i4Status == 0)
    {
        /*kbit/s, middleware return data is bytes/s, so need data*8/1024 */
        i4_sys_speed = (u4Speed/128);
        DBG_LOG_PRINT(("\n %s,%s,%d,Speed=%f\n",
                __FILE__, __FUNCTION__, __LINE__, i4_sys_speed));
    }
    return;
}


int system_information_network_information_download_speed(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR    string[64] = {0};

            INT32 i4_ret = 0;
            i4_ret= c_speedtest(NULL, _rest_SpeedtestNtyFct);
            if (i4_ret != 0)
            {
                REST_LOG_E("file=%s,line=%d,i4_ret:%d\n\r",__FILE__,__LINE__,i4_ret);
                c_speedtest_cancel();
            }

            c_snprintf(string, NETWORK_SPEED_LEN-1, "%.2f Kb/s", i4_sys_speed);
            REST_LOG_I("string: %s %f\n\r", string,i4_sys_speed);
            string_set_response(response, string);
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

int system_information_network_information_wifi_signal_strength(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32   i2_Level = 80;
            CHAR    string[64] = {0};

            i2_Level = a_nw_get_wlan_signal_lvl_from_rssi();

            c_sprintf(string,"%d", i2_Level);
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

int system_information_network_information_rssi(Json::Value & root, Json::Value & response)
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
            CHAR    string[64] = {0};
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
            c_sprintf(string, "%d", i4Rssi_avg);
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

int system_information_network_information_wifi_channel(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            INT32   i4_ret = 0;
            INT32   i2_Channel = 0;
            CHAR    string[64] = {0};
            NET_802_11_BSS_INFO_T CurrBss;

            c_memset(&CurrBss, 0, sizeof(CurrBss));
            i4_ret = a_nw_wlan_get_curr_bss(&CurrBss);
            LOG_ON_ERR(i4_ret);

            if (CurrBss.t_Ssid.ui4_SsidLen > 0)
            {
                i2_Channel = CurrBss.i2_Channel;
            }

            c_sprintf(string, "%d", i2_Channel);
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

int system_information_network_information_rj45_mac_address(Json::Value & root, Json::Value & response)
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

            CHAR  s_mac[REST_MAC_ADDRESS_LEN+1] = {0};

            REST_LOG_I("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);

            a_nw_get_mac_addr_string((CHAR*)NI_ETHERNET_0, s_mac);

            response["VALUE"] = std::string(s_mac);
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

int system_information_network_information_wlan_mac_address(Json::Value & root, Json::Value & response)
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

            CHAR  s_mac[REST_MAC_ADDRESS_LEN+1] = {0};

            REST_LOG_I("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);

            a_nw_get_mac_addr_string((CHAR*)NI_WIRELESS_0, s_mac);

            response["VALUE"] = std::string(s_mac);
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

int system_information_network_information_bt_mac_address(Json::Value & root, Json::Value & response)
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
#ifdef APP_BLUETOOTH_SUPPORT
            BT_LOCAL_DEV local_dev_info;

            c_memset(&local_dev_info, 0, sizeof(BT_LOCAL_DEV));
            i4_ret =a_mtkapi_bt_gap_get_local_dev_info(&local_dev_info);
            LOG_ON_ERR(i4_ret);

            response["VALUE"] = std::string(local_dev_info.bdAddr);
#else
            response["VALUE"] = std::string("BA:D0:00:BA:D0:00");
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

int system_information_network_information_wifi_module(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR str[ACFG_CUSTOM_WIFI_MODULE_NAME_LEN] = {0};
            a_cfg_cust_get_wifi_model_name(str, ACFG_CUSTOM_WIFI_MODULE_NAME_LEN);
            REST_LOG_I("dongle type read: %s\r\n", str);
            response["VALUE"] = std::string(str);
            break;
        }
        //READ ONLY
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

int system_information_uli_information_esn(Json::Value & root, Json::Value & response)
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

            CHAR  string_esn[16] ={0};
            UINT32 ui4_buff_len = 0;

            a_uli_get_serial_number((UINT8 *)string_esn, &ui4_buff_len);

            if (ui4_buff_len == 0)
            {
                c_strcpy((CHAR*)string_esn, " N/A");
                REST_LOG_E("No esn ,use N/A\n");
                i4_ret =35;  //dolphin 20200508 vizio SCPL need this error code while esn empty
            }

            REST_LOG_I("string_esn:%s.\n\r", string_esn);
            string_set_response(response, string_esn);

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

    return i4_ret;
}

int system_information_uli_information_sv(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            ULI_NEW_UPDATE_INFO_T t_update_info;
            a_uli_custom_get_update_info(&t_update_info);
            if (c_strlen((CHAR*)t_update_info.ps_software_version) <= 0 || c_strlen((CHAR*)t_update_info.ps_software_version) >= 32)
            {
                c_strcpy((CHAR*)t_update_info.ps_software_version, " ");
            }
            REST_LOG_I("t_update_info.ps_software_version:%s.\n\r", (CHAR*)t_update_info.ps_software_version);

            string_set_response(response, (CHAR*)t_update_info.ps_software_version);

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

int system_information_uli_information_reg(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR s_tmp_str_token_d[256] = {0};
            CHAR s_tmp_str_token_p[256] = {0};
            CHAR str_reg[8] = {0};

            getTokenFromFile("/certificate/PersistentPath", "core_",s_tmp_str_token_d);
            getTokenFromFile("/certificate/PersistentPath", "drmp_",s_tmp_str_token_p);

            if (s_tmp_str_token_p[0] !=0 &&
                s_tmp_str_token_d[0] != 0)
            {
                c_strcpy(str_reg, "Yes");
            }
            else
            {
                c_strcpy(str_reg, "No");
            }

            REST_LOG_I("str_reg:%s.\n\r", str_reg);
            string_set_response(response, str_reg);

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

int system_information_uli_information_netflix_esn_native(Json::Value & root, Json::Value & response)
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
        CHAR    string[256] = "N/A";
        FILE * pFile = NULL;

        pFile = fopen ("/certificate/netflix/ESNID","r");
        if (pFile != NULL)
        {
            c_memset(string, 0, sizeof(string));
            fgets(string, sizeof(string)-1, pFile);
            fclose(pFile);
        }
        REST_LOG_I("string: %s.\n\r", string);
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

int system_information_uli_information_np(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR str_np[8] = {0};
            CHAR str_tmp[8] = {0};
            UINT8 ui1_installed = 0;
            UINT32 avaiable_drmp = ULI_MAX_AVAIABLE_DRMP;

            ui1_installed = menu_ver_info_get_installed_drmp();
            REST_LOG_I("installed drmp %d \n\r", ui1_installed);

            c_sprintf(str_tmp, "%d",  ui1_installed);
            c_strcat(str_np, str_tmp);
            c_strcat(str_np, "/");
            c_sprintf(str_tmp, "%d",  avaiable_drmp);
            c_strcat(str_np, str_tmp);

            REST_LOG_I("str_np:%s.\n\r", str_np);
            string_set_response(response, str_np);

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

int system_information_uli_information_uid(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            UINT8	ui1_ulpk_key_temp[32];
            UINT32	ui4_ulpk_uid_temp = 0;
            UINT32	ui4_ulpk_len = 32;
            CHAR   str_uid[8] = {0};

            a_uli_get_factory_ulpk_v4(ui1_ulpk_key_temp, &ui4_ulpk_len, &ui4_ulpk_uid_temp);
            if(ui4_ulpk_uid_temp != 0)
            {
                c_sprintf(str_uid, "%d",  ui4_ulpk_uid_temp);
            }
            else
            {
                c_strcpy(str_uid, "N/A");
            }

            REST_LOG_I("str_uid:%s.\n\r", str_uid);
            string_set_response(response, str_uid);

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

int system_information_uli_information_dev_id(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR	s_tmp_str_token_d[256] = {0};
            CHAR   str_dev_id[8] = {0};

            getTokenFromFile("/certificate/PersistentPath", "core_",s_tmp_str_token_d);
            if(s_tmp_str_token_d[0] != 0)
            {
                c_strncpy(str_dev_id, (CHAR*)s_tmp_str_token_d, 5);
            }
            else
            {
                c_strcpy(str_dev_id, "N/A");
            }

            REST_LOG_I("str_dev_id:%s.\n\r", str_dev_id);
            string_set_response(response, str_dev_id);

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

int system_information_uli_information_prov_id(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR s_tmp_str_token_p[256] = {0};
            CHAR str_prov_id[8] = {0};

            getTokenFromFile("/certificate/PersistentPath", "drmp_",s_tmp_str_token_p);
            if(s_tmp_str_token_p[0] != 0)
            {
                c_strncpy(str_prov_id, (CHAR*)s_tmp_str_token_p, 5);
            }
            else
            {
                c_strcpy(str_prov_id, "N/A");
            }

            REST_LOG_I("str_prov_id:%s.\n\r", str_prov_id);
            string_set_response(response, str_prov_id);

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

int system_information_uli_information_da(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            ULI_NEW_UPDATE_INFO_T t_update_info;
            CHAR str_device_agent[32] = {0};

            a_uli_custom_get_update_info(&t_update_info);

            if (c_strlen((CHAR*)t_update_info.ps_qda_version) <= 0 || c_strlen((CHAR*)t_update_info.ps_qda_version) >= 32)
            {
                c_strcpy((CHAR*)t_update_info.ps_qda_version, " ");
            }
            c_strcpy(str_device_agent, (CHAR*)t_update_info.ps_qda_version);

            REST_LOG_I("str_device_agent:%s.\n\r", str_device_agent);
            string_set_response(response, str_device_agent);

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

int reset_and_admin_service_reset(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_ACTION:
        {
            INT32 i4_ret = 0;
            UTF16_T w2s_str[32] = {0};
            REST_LOG_I("Begin a_cfg_custom_service_reset,power on directly\n\r");
            #if 0
            //i4_ret = a_c4tv_apron_sync_exit_cast();
            if( i4_ret != 0 )
            {
                DBG_LOG_PRINT(("a_c4tv_apron_sync_exit_cast return fail, i4_ret=%d \n",i4_ret));
            }
            #endif
            #ifdef APP_TTS_SUPPORT
            c_uc_ps_to_w2s("power off", w2s_str, 32);
            a_app_tts_play(w2s_str, 32);
            #endif
            s_sync();
            i4_ret = a_cfg_custom_service_reset(1,TRUE);
            LOG_ON_ERR(i4_ret);
            break;
        }
        default:
            break;
    }
    return 0;
}

//dolphin add 20201027 for slient reboot
int reset_and_admin_dlm_reset(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    if(a_am_is_power_on())
    {
        a_cfg_custom_service_reset(1,ACFG_FORCE_REBOOT_UP_ON);
    }
    else
    {
        a_cfg_custom_set_drv_bgmupdate_flag(1);
        a_cfg_cust_set_force_reboot_up_flag(ACFG_FORCE_REBOOT_UP_OFF);
        system("reboot");
    }

    return 0;
}

int service_check(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_ACTION:
        {
            INT32 i4_ret = 0;

#ifdef APP_ULI_UPG_SUPPORT

            UINT8 pui1_fw_status = 0;
            UINT8 pui_fw_policy  = 0;

            i4_ret = a_nav_updater_check_network_update(&pui1_fw_status,&pui_fw_policy);

            DBG_LOG_PRINT(("%s, Do SERVICE CHECK (Check for Updates), i4_ret = %d\n", __FUNCTION__, i4_ret));

#endif

            LOG_ON_ERR(i4_ret);
            break;
        }
        default:
            break;
    }
    return 0;
}
#if 0
static BOOL _get_ntp_time(DTG_T* pt_loc_dtg)
{

    struct timeval tv;
    struct timezone tz;
    INT64      sec;

    if (gettimeofday(&tv, &tz) == 0)
    {
        sec = (INT64)tv.tv_sec;
        c_dt_utc_sec_to_loc_dtg(sec, pt_loc_dtg);

        if ((pt_loc_dtg->ui2_yr == 0) &&
            (pt_loc_dtg->ui1_mo == 0))
        {
            return FALSE;
        }

        return TRUE;
    }

    return FALSE;
}
#endif


int local_time_settings_use_internet_time(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};

    WDK_TOAST_T t_toast;

    type = get_type(root);

    Json::Value use_net_time;
    use_net_time[0]="Off";
    use_net_time[1]="On";
    response["ELEMENTS"]=use_net_time;
    INT32 indx = 0;
    UINT16  crnt_indx = 0;

    UINT8       use_internet_time;
    a_cfg_cust_get_net_time(&use_internet_time);
    if(use_internet_time)
    {
        indx = 1;
    }
    else
    {
        indx = 0;
    }
    crnt_indx = indx;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            response["VALUE"]=use_net_time[indx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str: %s\n\r", str);
            if (0 == c_strcmp("Off", str))
            {
                a_cfg_cust_set_net_time(0);
                indx = 0;
                REST_LOG_E("sbx set internet time %s \n\r",str);
            }
            else
            {
                a_cfg_cust_set_net_time(1);
                indx = 1;
                REST_LOG_E("sbx set internet time %s \n\r",str);
            }

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;

            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_USE_INTERNET_TIME;
            if (0 == indx)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if (1 == indx)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            if (indx != crnt_indx)
            {
                rest_send_msg_to_nav(&t_toast);
            }
            break;
        }
        default:
            break;
    }
    return 0;
}
int local_time_settings_date_time(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    //CHAR    str[128] = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            std::string t_mon[12]=
            {
                "Jan",
                "Feb",
                "Mar",
                "Apr",
                "May",
                "Jun",
                "Jul",
                "Aug",
                "Sep",
                "Oct",
                "Nov",
                "Dec"
            };
            CHAR str_mon[32]={0};
            CHAR str_time[128]={0};
            CHAR str_min[32]={0};
            CHAR str_am_pm[32]={0};
            CHAR str_week[32]={0};
            CHAR tmp[32]={0};
            INT32 t_week=0;
            BOOL        b_is_get_time = FALSE;
            UINT8       time_format;
            DTG_T       t_dtg = {0};
            b_is_get_time = a_dst_get_local_time(&t_dtg);
            if (TRUE == b_is_get_time)
            {
                c_strcpy(str_mon,t_mon[t_dtg.ui1_mo -1].c_str());

                a_cfg_cust_get_time_format(&time_format);
                if (t_dtg.ui1_min < 10)
                {
                    c_strcpy(str_min,"0");
                    c_sprintf(tmp,"%d",t_dtg.ui1_min);
                    c_strcat(str_min,tmp);
                }
                else
                {
                    c_sprintf(str_min,"%d",t_dtg.ui1_min);
                }

                t_week = (t_dtg.ui1_day + 2*t_dtg.ui1_mo+3*(t_dtg.ui1_mo+1)/5 + t_dtg.ui2_yr+
                    t_dtg.ui2_yr/4-t_dtg.ui2_yr/100+t_dtg.ui2_yr/400)%7;
                switch (t_week)
                {
                    case 0:
                    {
                        c_strcpy(str_week,"Mon,");
                        break;
                    }
                    case 1:
                    {
                        c_strcpy(str_week,"Tue,");
                        break;
                    }
                    case 2:
                    {
                        c_strcpy(str_week,"Wed,");
                        break;
                    }
                    case 3:
                    {
                        c_strcpy(str_week,"Thu,");
                        break;
                    }
                    case 4:
                    {
                        c_strcpy(str_week,"Fri,");
                        break;
                    }
                    case 5:
                    {
                        c_strcpy(str_week,"Sat,");
                        break;
                    }
                    case 6:
                    {
                        c_strcpy(str_week,"Sun,");
                        break;
                    }
                }
                REST_LOG_I("mon:%d,day:%d,hour:%d min:%s\n\r",t_dtg.ui1_mo,t_dtg.ui1_day,t_dtg.ui1_hr,str_min);
                if(time_format)//24H_format
                {
                    if (t_dtg.ui1_hr < 10)
                    {
                        if (t_dtg.ui1_day < 10)
                        {
                            c_sprintf(str_time,
                                      "%s %s 0%d, %d 0%d:%s",
                                      str_week,
                                      str_mon,
                                      t_dtg.ui1_day,
                                      t_dtg.ui2_yr,
                                      t_dtg.ui1_hr,
                                      str_min);
                        }
                        else
                        {
                            c_sprintf(str_time,
                                      "%s %s %d, %d 0%d:%s",
                                      str_week,
                                      str_mon,
                                      t_dtg.ui1_day,
                                      t_dtg.ui2_yr,
                                      t_dtg.ui1_hr,
                                      str_min);
                        }
                    }
                    else
                    {
                        if (t_dtg.ui1_day < 10)
                        {
                           c_sprintf(str_time,
                                     "%s %s 0%d, %d %d:%s",
                                     str_week,
                                     str_mon,
                                     t_dtg.ui1_day,
                                     t_dtg.ui2_yr,
                                     t_dtg.ui1_hr,
                                     str_min);
                        }
                        else
                        {
                            c_sprintf(str_time,
                                      "%s %s %d, %d %d:%s",
                                      str_week,
                                      str_mon,
                                      t_dtg.ui1_day,
                                      t_dtg.ui2_yr,
                                      t_dtg.ui1_hr,
                                      str_min);
                        }
                    }
                }
                else//12H_format
                {
                    if (t_dtg.ui1_hr > 12)
                    {
                        t_dtg.ui1_hr -= 12;
                        c_strcpy(str_am_pm,"PM");
                    }
                    else
                    {
                        if (t_dtg.ui1_hr == 0)
                        {
                            t_dtg.ui1_hr = t_dtg.ui1_hr + 12;
                            c_strcpy(str_am_pm,"AM");
                        }
                        else if (t_dtg.ui1_hr == 12)
                        {
                            c_strcpy(str_am_pm,"PM");
                        }
                        else
                        {
                            c_strcpy(str_am_pm,"AM");
                        }
                    }
                    if (t_dtg.ui1_hr < 10)
                    {
                        if (t_dtg.ui1_day < 10)
                        {
                            c_sprintf(str_time,
                                      "%s %s 0%d, %d 0%d:%s%s",
                                      str_week,
                                      str_mon,
                                      t_dtg.ui1_day,
                                      t_dtg.ui2_yr,
                                      t_dtg.ui1_hr,
                                      str_min,
                                      str_am_pm);
                        }
                        else
                        {
                            c_sprintf(str_time,
                                      "%s %s %d, %d 0%d:%s%s",
                                      str_week,
                                      str_mon,
                                      t_dtg.ui1_day,
                                      t_dtg.ui2_yr,
                                      t_dtg.ui1_hr,
                                      str_min,
                                      str_am_pm);
                        }
                    }
                    else
                    {
                        if (t_dtg.ui1_day < 10)
                        {
                            c_sprintf(str_time,
                                      "%s %s 0%d, %d %d:%s%s",
                                      str_week,
                                      str_mon,
                                      t_dtg.ui1_day,
                                      t_dtg.ui2_yr,
                                      t_dtg.ui1_hr,
                                      str_min,
                                      str_am_pm);
                        }
                        else
                        {
                            c_sprintf(str_time,
                                      "%s %s %d, %d %d:%s%s",
                                      str_week,
                                      str_mon,
                                      t_dtg.ui1_day,
                                      t_dtg.ui2_yr,
                                      t_dtg.ui1_hr,
                                      str_min,
                                      str_am_pm);
                        }
                    }
                }
            }
            response["VALUE"]=std::string(str_time);
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

static UINT16 _get_time_zone_idx(VOID)
{
    UINT8 ui1_tz = APP_CFG_TZ_EASTERN_TIME;

    a_cfg_custom_get_timezone_idx(&ui1_tz);

    return (UINT16)ui1_tz;
}

static BOOL _is_a_unnamed_tz()
{
     switch (_get_time_zone_idx())
     {
         case  8: case  9: case 11:
         case 12: case 13: case 10:
         case 14: case 15: case 16:
         case 17: case 18: case 19:
         case 21: case 22: case 20:
         case 23: case 24: case 25:
         case  0: case  7:
          {
             return TRUE;
          }
          default:
             return FALSE;
     }
}

static BOOL _is_auto_dls_support()
{
    switch (_get_time_zone_idx())
    {
       case 0:
       case 20: return FALSE;
       default:return TRUE;
    }
    return TRUE;
}

int local_time_settings_timezone(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    UINT8 ui1_tz = APP_CFG_TZ_EASTERN_TIME;
    UINT8 crnt_indx = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);
    REST_LOG_I("Enter\n\r");
    Json::Value time_zone;
    time_zone[0]="HST (GMT-10)";
    time_zone[1]="AKST (GMT-9)";
    time_zone[2]="PST (GMT-8)";
    time_zone[3]="MST (GMT-7)";
    //time_zone[4]="Arizona (-7)"; remove for new time zone standards
    time_zone[4]="CST (GMT-6)";
    //time_zone[6]="Indiana (-5)"; remove for vizio spec change 4.2.1
    time_zone[5]="EST (GMT-5)";
    time_zone[6]="AST (GMT-4)";
    //time_zone[8]="Newfoundland (-3.5)"; remove for new time zone standards
    time_zone[7]="ART (GMT-3)";
    time_zone[8]="AT (GMT-2)";
    time_zone[9]="WAT (GMT-1)";
    time_zone[10]="GMT (GMT+0)";
    time_zone[11]="CET (GMT+1)";
    time_zone[12]="EET (GMT+2)";
    time_zone[13]="MSK (GMT+3)";
    time_zone[14]="AMT (GMT+4)";
    time_zone[15]="PKT (GMT+5)";
    time_zone[16]="OMSK (GMT+6)";
    time_zone[17]="KRAT (GMT+7)";
    time_zone[18]="CST (GMT+8)";
    time_zone[19]="JST (GMT+9)";
    time_zone[20]="AEST (GMT+10)";
    time_zone[21]="SAKT (GMT+11)";
    time_zone[22]="NZST (GMT+12)";
    time_zone[23]="IDLW (GMT-12)";
    time_zone[24]="NT (GMT-11)";
    response["ELEMENTS"]=time_zone;
    response["VALUE"]=time_zone[0];

    a_cfg_custom_get_timezone_idx(&ui1_tz);
    crnt_indx = ui1_tz;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("timeZone value: %d\n\r", ui1_tz);
            response["VALUE"]=time_zone[ui1_tz];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str,item1.asString().c_str());
            std::string t_time_zone[25]=
            {
                "HST (GMT-10)",
                "AKST (GMT-9)",
                "PST (GMT-8)",
                "MST (GMT-7)",
                //"Arizona (-7)", remove for new time zone standards
                "CST (GMT-6)",
                //"Indiana (-5)", remove for vizio spec change 4.2.1
                "EST (GMT-5)",
                "AST (GMT-4)",
                //"Newfoundland (-3.5)", remove for new time zone standards
                "ART (GMT-3)",
                "AT (GMT-2)",
                "WAT (GMT-1)",
                "GMT (GMT+0)",
                "CET (GMT+1)",
                "EET (GMT+2)",
                "MSK (GMT+3)",
                "AMT (GMT+4)",
                "PKT (GMT+5)",
                "OMSK (GMT+6)",
                "KRAT (GMT+7)",
                "CST (GMT+8)",
                "JST (GMT+9)",
                "AEST (GMT+10)",
                "SAKT (GMT+11)",
                "NZST (GMT+12)",
                "IDLW (GMT-12)",
                "NT (GMT-11)"
            };
#if 0
            std::string str_cast_zone[]={
                "Pacific/Honolulu",//-10
                "America/Anchorage",//-9
                "America/Los_Angeles",//-8
                "America/Denver",//-7
                "America/Phoenix",//-7
                "America/Chicago",//-6
                "America/Chicago",//-5 //---"America/Indiana/Indianapolis",
                "America/New_York",//-5
                "America/Halifax",//-4
                "Australia/Darwin",//"America/St_Johns",//-3.5//  add12
                "America/Sao_Paulo",//-3
                "America/Noronha",//-2
                "Pacific/Pohnpei",//-1
                "Africa/Bamako",//"Europe/London",//0
                "Europe/Lisbon",//"Atlantic/Faroe",//+1
                "Europe/Oslo",//"Europe/Istanbul",//+2
                "Europe/Istanbul",//"Europe/Moscow",//+3
                "America/Anchorage",//+4//"Asia/Tehran",// add12
                "Asia/Ashgabat",//+5
                "Asia/Thimphu",//"Asia/Dhaka"//+6
                "Asia/Ho_Chi_Minh",//+7
                "Asia/Hong_Kong",//+8
                "Asia/Seoul",//+9
                "Australia/Brisbane",//+10
                "Pacific/Pohnpei",//+11
                "Pacific/Kwajalein",//+12
                "Pacific/Kwajalein",//-12
                "Pacific/Pago_Pago",//-11
            };
#endif
            TIME_T      t_tz_offset = 0;
            BOOL        b_dls       = FALSE;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[128] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};
            //CHAR  cast_str_zone[128]={0};
            for (INT32 num=0;num<25;num++)
            {
                if (item1.asString().c_str() == t_time_zone[num])
                {
                    ui1_tz = num;
                    break;
                }
            }

            switch (ui1_tz)
            {
            case 0:
                t_tz_offset = -10  * 3600;      /* HST */
                break;
            case 1:
                t_tz_offset = -9   * 3600;      /* AKST */
                break;
            case 2:
                t_tz_offset = -8   * 3600;      /* PST(default)*/
                break;
            case 3:
                t_tz_offset = -7   * 3600;      /* MST */
                break;
            case 4:
                t_tz_offset = -6   * 3600;      /* CST */
                break;
            case 5:
                t_tz_offset = -5   * 3600;      /* EST */
                break;
            case 6:
                t_tz_offset = -4   * 3600;      /* AST */
                break;
            case 7:
                t_tz_offset = -3  * 3600;      /* ART */
               break;
            case 8:
                t_tz_offset = -2  * 3600;      /* AT */
                break;
            case 9:
                t_tz_offset = -1   * 3600;      /* WAT */
                break;
            case 10:
                t_tz_offset = 0   * 3600;      /* GMT */
                break;
            case 11:
                t_tz_offset = 1   * 3600;      /* CET */
                break;
            case 12:
                t_tz_offset = 2   * 3600;      /* EET */
                break;
            case 13:
                t_tz_offset = 3   * 3600;      /* MSK */
                break;
            case 14:
                t_tz_offset = 4   * 3600;      /* AMT */
                break;
            case 15:
                t_tz_offset = 5   * 3600;      /* PKT */
                break;
            case 16:
                t_tz_offset = 6   * 3600;      /* OMSK */
               break;
            case 17:
                t_tz_offset = 7  * 3600;       /* KRAT */
               break;
            case 18:
                t_tz_offset = 8  * 3600;       /* CST */
                break;
            case 19:
                t_tz_offset = 9   * 3600;      /* JST */
                break;
            case 20:
                t_tz_offset = 10   * 3600;     /* AEST */
                break;
            case 21:
                t_tz_offset = 11   * 3600;     /* SAKT */
                break;
            case 22:
                t_tz_offset = 12   * 3600;     /* NZST */
                break;
            case 23:
                t_tz_offset = -12   * 3600;    /* IDLW */
                break;
            case 24:
                t_tz_offset = -11   * 3600;     /* NT */
                break;
            default:
                ui1_tz  = 2;
                t_tz_offset = -8   * 3600;      /* PST(default) */
                break;
            }


            REST_LOG_I("value: %s\n\r", str);
            a_cfg_set_time_zone_data(t_tz_offset, b_dls);
            a_cfg_custom_set_timezone_idx(ui1_tz);
            a_cfg_update_time_zone();
            /*set Cast Timezone*/
            //c_strcpy(cast_str_zone,str_cast_zone[ui1_tz].c_str());
            //a_c4tv_apron_set_timezone(cast_str_zone);
            /*set dst*/
            a_cfg_custom_set_dst((_is_a_unnamed_tz() || 20 == ui1_tz || 10 == ui1_tz) ? DST_OFF : DST_AUTO);
            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            rest_event_notify("system/time/timezone", 0, str);

            t_toast.e_toast_style  = WDK_STRING_TOAST;

            if (0 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_HAWAII;
            }
            else if (1 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_ALASKA;
            }
            else if (2 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_PACIFIC;
            }
            else if (3 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_MOUNTAIN;
            }
#if 0
            //remove for new time zone standards
            else if (4 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_ARIZONA;
            }
#endif
            else if (4 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_CENTRAL;
            }
            else if (5 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_EASTERN;
            }
            else if (6 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_ATLANTIC;
            }
#if 0
            //remove for new time zone standards
            else if (8 == ui1_tz)
            {
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_ZONE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_ZONE_NEWFOUNDLAND;
            }
#endif
			else
            {
                t_toast.e_string_style = WDK_STRING_STRING;
				t_toast.style.style_4.ui4_id = MLM_SETTINGS_KEY_TIME_ZONE;
                c_uc_ps_to_w2s(" ", str_2, 2);
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_TIME_ZONE));
                c_uc_w2s_strcat(w2s_string,str_2);
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_IS));
                c_uc_w2s_strcat(w2s_string,str_2);
                if (12 == ui1_tz)
                {
                    c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_TIME_ZONE_LONDON));
                }
                else
                {
                    c_uc_ps_to_w2s(item1.asString().c_str(), str_1, 255);
                    c_uc_w2s_strcat(w2s_string,str_1);
                    c_uc_ps_to_w2s(".", str_3, 2);
                    c_uc_w2s_strcat(w2s_string,str_3);
                }
                t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            }
            if (ui1_tz != crnt_indx)
            {
                rest_send_msg_to_nav(&t_toast);
            }
            break;
        }
        default:
            break;
    }
    return 0;
}

//dolphin 20200909 add automatic time
int automatic_time(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);
    UINT16 ui2_status = 0;

    enum _automatic_time
    {
        AT_DISABLE=1,
        AT_ENABLE=0,
        AT_MAX,
    };

    Json::Value j_automatic_time;
    j_automatic_time[0]="Enabled";
    j_automatic_time[1]="Disabled";
    response["ELEMENTS"]=j_automatic_time;

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            ui2_status = menu_get_automatic_time_idx();
            if(ui2_status!=0 && ui2_status!=1)
            {
                REST_LOG_E("unknow return value %d\n",ui2_status);
                i4_ret = -1;
                break;
            }
            response["VALUE"]=j_automatic_time[ui2_status];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];

            if(c_strcmp(item1.asString().c_str(),j_automatic_time[AT_DISABLE].asString().c_str())==0)
            {
                 REST_LOG_I("Set value %s to %d\n",item1.asString().c_str(),AT_DISABLE);
                 ui2_status = AT_DISABLE;
            }
            else if(c_strcmp(item1.asString().c_str(),j_automatic_time[AT_ENABLE].asString().c_str())==0)
            {
                 REST_LOG_I("Set value %s to %d\n",item1.asString().c_str(),AT_ENABLE);
                 ui2_status = AT_ENABLE;
            }
            else
            {
                 REST_LOG_E("unknow set value %s\n",item1.asString().c_str());
                 i4_ret = -1;
                 break;
            }
            menu_set_automatic_time_idx(ui2_status);
            i4_ret = menu_page_set_automatic_time_to_refresh();
            break;
        }
        default:
            break;
    }

    return i4_ret;
}


int local_time_settings_daylight_savings_time(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_dst = 0;
    UINT16  crnt_indx = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);

    Json::Value day_saving_time;
    day_saving_time[0]="Auto";
    day_saving_time[1]="On";
    day_saving_time[2]="Off";
    response["ELEMENTS"]=day_saving_time;
    response["VALUE"]=day_saving_time[0];

    UINT8 ui1_tz = APP_CFG_TZ_EASTERN_TIME;
    a_cfg_custom_get_timezone_idx(&ui1_tz);

#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
    a_cfg_custom_get_dst(&ui2_dst);
#endif
    crnt_indx = ui2_dst;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            response["VALUE"]=day_saving_time[ui2_dst];
            REST_LOG_I("value: %d\n\r", ui2_dst);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST SET\r\n");
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str,item1.asString().c_str());

            if (0 == c_strcmp("Auto",str))
            {
                if (ui1_tz >= 1 && ui1_tz <= 3 || ui1_tz >= 4 && ui1_tz <= 6)
                {
                    ui2_dst = 0;
                }
                else
                {
                    ui2_dst = 2;
                }
            }
            else if (0 == c_strcmp("On",str))
            {
                ui2_dst = 1;
            }
            else if (0 == c_strcmp("Off",str))
            {
                ui2_dst = 2;
            }
#ifdef NEW_TIME_LOCAL_AUTO_DST_SUPPORT
            if(FALSE == _is_auto_dls_support() && ui2_dst == DST_AUTO)
		        ui2_dst = DST_OFF;
            a_cfg_custom_set_dst(ui2_dst);
#endif
            REST_LOG_I("sbx set daylight_savings_time %d \n\r",ui2_dst);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;

            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_DAYLIGHT_SAVING;
            if (0 == ui2_dst)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUTO;
            }
            else if (1 == ui2_dst)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            else if (2 == ui2_dst)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            if (ui2_dst != crnt_indx)
            {
                rest_send_msg_to_nav(&t_toast);
            }
            menu_pm_repaint();
            break;
        }
        default:
            break;
    }

    return 0;
}
int local_time_settings_time_format(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    UINT16      ui2_dst = 0;
    UINT16  crnt_indx = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);
    Json::Value b_time_format;
    b_time_format[0]="12 hour";
    b_time_format[1]="24 hour";
    response["ELEMENTS"]=b_time_format;

    UINT8       time_format;
    a_cfg_cust_get_time_format(&time_format);
    if(time_format)
    {
        ui2_dst = 1;
    }
    else
    {
        ui2_dst = 0;
    }
    crnt_indx = ui2_dst;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            response["VALUE"]=b_time_format[ui2_dst];
            REST_LOG_I("value: %d\n\r", ui2_dst);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str,item1.asString().c_str());
            if (0 == c_strcmp("12 hour",str))
            {
                ui2_dst = 0;
                a_cfg_cust_set_time_format(0);
                a_c4tv_apron_set_time_format(TRUE);
            }
            else if (0 == c_strcmp("24 hour",str))
            {
                ui2_dst = 1;
                a_cfg_cust_set_time_format(1);
                a_c4tv_apron_set_time_format(FALSE);
            }

            //TODO

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_TIME_FORMAT;
            if (0 == ui2_dst)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_FORMAT_12H;
            }
            else if (1 == ui2_dst)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TIME_FORMAT_24H;
            }
            if (ui2_dst != crnt_indx)
            {
                rest_send_msg_to_nav(&t_toast);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

BOOL _wlan_status(VOID)
{
    struct ifreq ifr;
    int sockfd;
    BOOL ret;

    c_memset(&ifr, 0, sizeof(struct ifreq));
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, "uap0");
    ioctl(sockfd, SIOCGIFFLAGS, &ifr);
    if (ifr.ifr_flags & IFF_UP && ifr.ifr_flags & IFF_RUNNING)//referenc to net_dev.c
        ret = TRUE;
    else
        ret = FALSE;

    close(sockfd);
    return ret;
}

static VOID _time_local_setting_country_info_thread_main (VOID* pv_arg)
{
    a_tv_net_reset_3rd_ap_data(APP_TV_NET_RESET_ITEM_ALL);

    REST_LOG_I("[system ] reset 3rd app data \n\r \r\n");
    x_thread_exit();
}

int local_time_settings_country(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return country(root,response);
}

int menu_language(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    WDK_TOAST_T t_toast;

    Json::Value language;
    Json::Value language_en;

    enum _LANG
    {
        _EN = 0,
        _SP = 1,
        _FR = 2,
        _LANG_MAX,
    };

    language[_EN] = "English";
    language[_SP] = "Español";
    language[_FR] = "Français";

    language_en[_EN] = "English";
    language_en[_SP] = "Spanish";
    language_en[_FR] = "Franch";

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");
            UINT16 ui2_indx=-1;
            ui2_indx = menu_custom_get_gui_lang_idx();

            response["ELEMENTS"]=language;
            response["VALUE"] = language[ui2_indx];
            REST_LOG_I("value: %d \n\r", ui2_indx);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_W("SET\n\r");
            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_MENU_LANG;
            t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_MENU_LANG_ENG;

            Json::Value value;
            Json::Value message;
            INT32 i4_lang_idx = -1;

            message=root["message"];
            value=message["VALUE"];

            REST_LOG_E("get [%s]\n",value.asString().c_str());
            for(int i=0;i<_LANG_MAX;i++)
            {
                if(strcmp(value.asString().c_str(),language[i].asString().c_str())==0 ||\
                   strcmp(value.asString().c_str(),language_en[i].asString().c_str())==0) //handle the argument no matter it was translated or in English
                {
                    i4_lang_idx = i;
                    break;
                }
            }

            if(i4_lang_idx!=-1)
            {
                 menu_custom_set_gui_lang_idx(i4_lang_idx);
            }
            else
            {
                REST_LOG_E("Could not match language\n");
                return -1;
            }
            rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }

    return 0;
}

int cec_cec_function(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_indx = 0;
    UINT16  crnt_indx = 0;
    WDK_TOAST_T t_toast;

    type = get_type(root);

    Json::Value cec_func;
    cec_func[0] = "Disabled";
    cec_func[1] = "Enabled";
    response["ELEMENTS"] = cec_func;
    response["VALUE"] = cec_func[0];

    UINT8 ui1_tmp_on = 0;
    a_cfg_get_cec_func (&ui1_tmp_on);
    switch (ui1_tmp_on)
    {
        case 0: /* OFF */
        {
            ui2_indx = 0;
            break;
        }
        case 1: /* ON */
        {
            ui2_indx = 1;
            break;
        }
        default:
        {
            ui2_indx = 1;
            break;
        }
    }
    crnt_indx = ui2_indx;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            response["VALUE"] = cec_func[ui2_indx];
            REST_LOG_I("value: %d\n\r", ui2_indx);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CEC;

            if (0 == c_strcmp("Disabled",str))
            {
                ui2_indx = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CEC_DISABLE;
            }
            else if (0 == c_strcmp("Enabled",str))
            {
                ui2_indx = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CEC_ENABLE;
            }
            else
            {
                REST_LOG_E("Error\n\r");
                break;
            }

            if(crnt_indx == ui2_indx)
            {
                break;
            }

            UINT8 ui1_sac=0;
            UINT8 ui1_cec_auto_on=0;
            UINT16 ui2_speaker_val = 0;
            a_cfg_get_cec_sac_func(&ui1_sac);
            a_cfg_get_cec_auto_on(&ui1_cec_auto_on);
            a_cfg_custom_get_speakers_out(&ui2_speaker_val);

            if(0 == ui2_indx)/* OFF */
            {
                a_cfg_set_cec_func (APP_CFG_CEC_OFF);
                if(0 != ui1_sac)
                {
                    a_cfg_set_cec_sac_func(0);
                }
                if(APP_CFG_CEC_OFF != ui1_cec_auto_on)
                {
                    a_cfg_set_cec_auto_on(APP_CFG_CEC_OFF);
                }
                c_thread_delay(300);
            }
            else if(1 == ui2_indx)/* ON */
            {
                a_cfg_set_cec_func (APP_CFG_CEC_ON);
                /* Set sac to on if TV speaker is Auto. */
                if((ui2_speaker_val == APP_CFG_AUD_AD_SPEAKER_AUTO) && (1 != ui1_sac))
                {
                    a_cfg_set_cec_sac_func(1);
                }
                if(APP_CFG_CEC_ON != ui1_cec_auto_on)
                {
                    a_cfg_set_cec_auto_on(APP_CFG_CEC_ON);
                }
                c_thread_delay(300);
            }

            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
        }
            break;
        default:
            break;
    }
    return 0;
}



//dolphin 20200730 custom need this endpoint to trigger the action of searching cec device
int cec_device_discovery(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_hdmi_port_id;
    INT32 i4_ret=0;
    const INT32 W2S_HDMI_NAME_LEN   = 32;  //dolphin it was in fact defined in menu_page_cec.c
    UTF16_T     W2S_HDMI_NAME[W2S_HDMI_NAME_LEN];
    CHAR        CEC_HDMI_NAME[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    CHAR        used_port[5][APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    S_HDMI_NAME_T CFG_HDMI_NAME;
    CECM_DEV_T t_dev_info;
    CECM_CTRL_T t_cecm_ctrl = {0};
    UTF16_T* pw2s_dev_osd_name = NULL;

    ui1_display_device_count = 0;
    memset(_cec_node_list,0x0,sizeof(_CEC_NODE)*MAX_HDMI_INPUT);

    usleep(500*1000); //sleep 500 for cec device ready

    t_cecm_ctrl.b_sync = TRUE;
    for (int ui1_la = CECM_LOG_ADDR_REC_DEV_1; ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST; ui1_la++)
    {

        c_memset (&t_dev_info, 0, sizeof (CECM_DEV_T));
        i4_ret = c_cecm_get_dev_info_by_la(nav_cec_get_mw_handle(),
                                            (CECM_LOG_ADDR_T)ui1_la,
                                            &t_cecm_ctrl,
                                            &t_dev_info);

        if (i4_ret != CECMR_OK)
        {
            REST_LOG_E("c_cecm_get_dev_info_by_la %d fail(%d)",ui1_la, i4_ret);
            continue;
        }
        if ((t_dev_info.e_dev_state != CECM_DEV_STATE_UPDATED)
         || (t_dev_info.t_report_phy_addr.ui2_pa == CECM_INV_PA)
         || (t_dev_info.t_report_phy_addr.ui2_pa == 0))
        {
            REST_LOG_I("Error: Invalid PA(0x%X) at LA=%d\n",t_dev_info.t_report_phy_addr.ui2_pa, ui1_la);
            continue;
        }

        UINT8 hdmi_port = t_dev_info.t_report_phy_addr.ui2_pa >> 12;
        if((hdmi_port > 4) || (hdmi_port == 0))
        {
            REST_LOG_E("Error: Invalid HDMI Port (%d)\n",hdmi_port);
            continue;
        }

        if (c_uc_w2s_strlen(t_dev_info.aw2_osd_name) != 0)
        {
            pw2s_dev_osd_name = t_dev_info.aw2_osd_name;
        }
        else
        {
            REST_LOG_E("Warning: No CEC name\n");
            //pw2s_dev_osd_name = _menu_cec_view_get_def_dev_osd_name(ui1_la);
        }
        c_uc_w2s_to_ps(pw2s_dev_osd_name, CEC_HDMI_NAME, APP_CFG_CUSTOM_INP_NAME_LEN);

        if(hdmi_port <= 4)
        {
            if(c_strlen(used_port[hdmi_port]) == 0)
            {
                if(c_strlen(CEC_HDMI_NAME))
                {
                    c_strcpy(used_port[hdmi_port], CEC_HDMI_NAME);
                    REST_LOG_I("LA:%d, Set used_port[%d]={%s}\n",ui1_la, hdmi_port, used_port[hdmi_port]);
                }
            }
            else
            {
                REST_LOG_I("LA:%d, Set used_port[%d]={%s}\n",ui1_la, hdmi_port, used_port[hdmi_port]);
                if(0 == c_strcmp(used_port[hdmi_port], CEC_HDMI_NAME))
                {
                    continue;
                }
            }
        }
        REST_LOG_E("cec devices name is port %d id %s\n",hdmi_port, CEC_HDMI_NAME);
        _cec_node_list[ui1_display_device_count].i4_hdmi_id = i4_hdmi_port_id;
        c_strcpy(_cec_node_list[ui1_display_device_count].p_cec_name,CEC_HDMI_NAME);
        ui1_display_device_count++;
    }

    REST_LOG_E("search finish ui1_display_device_count=%d\n",ui1_display_device_count);
    return 0;
}

//dolphin 20200730 custom need this endpoint to get the cec list
int cec_device_discovery_results(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    Json::Value cec_dev;

    for(int i=0;i<ui1_display_device_count;i++)
    {
        if(c_strlen(_cec_node_list[i].p_cec_name)!=0)
        {
            cec_dev[i]["OSDName"] = std::string(_cec_node_list[i].p_cec_name);
            cec_dev[i]["PrimaryDeviceType"] = "0";
            cec_dev[i]["VendorId"] = "0";
            cec_dev[i]["Children"].resize(0);
        }
    }

    response["HASHVAL"] = "0";
    response["CNAME"] = "device_discovery_results";
    response["TYPE"] = "T_LIST_CEC_DEVICE_V1";
    response["NAME"] = "Device Discovery Results";
    response["VALUE"] = cec_dev;

    return 0;
}


#if 0 //dolphin said the previous endpoint not use
int cec_device_discovery(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    Json::Value cec_dev;
#ifdef APP_CEC_SUPPORT
    UINT8                   ui1_cec_func = 0;
    //UINT8                   ui1_on_off =0;
    CEC_DEV_LST_T           t_lst;
    CHAR dev_osdname[64]={0};
    CHAR dev_logiaddr[64]={0};
    UTF16_T* dev_osd_name = NULL;

    //a_cfg_get_cec_sac_func(&ui1_on_off);//MENU -> Audio -> TV Speakers: Off/Auto - 1 , On - 0
    a_cfg_get_cec_func (&ui1_cec_func);

    c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
    a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

    if(/*ui1_on_off == 1 && */ui1_cec_func != APP_CFG_CEC_OFF)
    {
        REST_LOG_I("dev_num:%d\n\r",t_lst.ui1_dev_num);
        extern UTF16_T* get_def_dev_osd_name (UINT8 ui1_la);

        UINT8 ui1_display_device_count = 0;

        for (UINT8 ui1_idx = 0; ui1_idx < t_lst.ui1_dev_num; ui1_idx++)
        {
            c_memset(dev_osdname,0,sizeof(dev_osdname));
            c_memset(dev_logiaddr,0,sizeof(dev_logiaddr));

            if (APP_CFG_CEC_ARC_ONLY == ui1_cec_func
                && !(t_lst.at_dev_info[ui1_idx].e_la == CECM_LOG_ADDR_AUD_SYS))
            {
                continue;
            }

            if (c_uc_w2s_strlen(t_lst.at_dev_info[ui1_idx].aw2_osd_name) != 0)
            {
                dev_osd_name = t_lst.at_dev_info[ui1_idx].aw2_osd_name;
            }
            else
            {
                dev_osd_name = get_def_dev_osd_name(t_lst.at_dev_info[ui1_idx].e_la);
            }

            c_uc_w2s_to_ps(dev_osd_name, dev_osdname, 32-1);
            REST_LOG_I("DEV_OSD_NAME:%s\n\r", dev_osdname);

            c_sprintf(dev_logiaddr, "%d",
                t_lst.at_dev_info[ui1_idx].e_la);
            cec_dev[ui1_display_device_count]["OSDName"] = std::string(dev_osdname);
            cec_dev[ui1_display_device_count]["LogicalAddress"] = std::string(dev_logiaddr);
            cec_dev[ui1_display_device_count]["PrimaryDeviceType"] = "0";
            cec_dev[ui1_display_device_count]["VendorId"] = "0";
            cec_dev[ui1_display_device_count]["Children"].resize(0);
            ui1_display_device_count++;
        }
    }
#endif
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            //the important thing is the VALUE
            response["HASHVAL"] = "0";
            response["CNAME"] = "device_discovery";
            response["TYPE"] = "T_LIST_CEC_DEVICE_V1";
            response["NAME"] = "Device Discovery";
            response["VALUE"] = cec_dev;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");
            break;
        }
        default:
            break;
    }
    return 0;
}

int cec_device_discovery_results(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32 type = 0;
	UINT16	ui2_indx = 0;

	type = get_type(root);

	Json::Value cec_dev;
#ifdef APP_CEC_SUPPORT
	UINT8					ui1_cec_func = 0;
	//UINT8 				  ui1_on_off =0;
	CEC_DEV_LST_T			t_lst;
	CHAR dev_osdname[64]={0};
	CHAR dev_logiaddr[64]={0};
	UTF16_T* dev_osd_name = NULL;

	//a_cfg_get_cec_sac_func(&ui1_on_off);//MENU -> Audio -> TV Speakers: Off/Auto - 1 , On - 0
	a_cfg_get_cec_func (&ui1_cec_func);

	c_memset (&t_lst, 0, sizeof (CEC_DEV_LST_T));
	a_cec_get_dev_list(nav_cec_get_mw_handle (), &t_lst, CEC_SORT_TYPE_DEFAULT);

	if(/*ui1_on_off == 1 && */ui1_cec_func != APP_CFG_CEC_OFF)
	{
		REST_LOG_I("dev_num:%d\n\r",t_lst.ui1_dev_num);
		extern UTF16_T* get_def_dev_osd_name (UINT8 ui1_la);

		UINT8 ui1_display_device_count = 0;

		for (UINT8 ui1_idx = 0; ui1_idx < t_lst.ui1_dev_num; ui1_idx++)
		{
			c_memset(dev_osdname,0,sizeof(dev_osdname));
			c_memset(dev_logiaddr,0,sizeof(dev_logiaddr));

			if (APP_CFG_CEC_ARC_ONLY == ui1_cec_func
				&& !(t_lst.at_dev_info[ui1_idx].e_la == CECM_LOG_ADDR_AUD_SYS))
			{
				continue;
			}

			if (c_uc_w2s_strlen(t_lst.at_dev_info[ui1_idx].aw2_osd_name) != 0)
			{
				dev_osd_name = t_lst.at_dev_info[ui1_idx].aw2_osd_name;
			}
			else
			{
				dev_osd_name = get_def_dev_osd_name(t_lst.at_dev_info[ui1_idx].e_la);
			}

			c_uc_w2s_to_ps(dev_osd_name, dev_osdname, 32-1);
			REST_LOG_I("DEV_OSD_NAME:%s\n\r", dev_osdname);

			c_sprintf(dev_logiaddr, "%d",
				t_lst.at_dev_info[ui1_idx].e_la);
			cec_dev[ui1_display_device_count]["OSDName"] = std::string(dev_osdname);
			cec_dev[ui1_display_device_count]["LogicalAddress"] = std::string(dev_logiaddr);
			cec_dev[ui1_display_device_count]["PrimaryDeviceType"] = "0";
			cec_dev[ui1_display_device_count]["VendorId"] = "0";
			cec_dev[ui1_display_device_count]["Children"].resize(0);
			ui1_display_device_count++;
		}
	}
#endif
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		case argument::RequestType::REQUEST_ACTION:
		{
			REST_LOG_I("REQUEST_GET\n\r");

			//the important thing is the VALUE
			response["HASHVAL"] = "0";
			response["CNAME"] = "device_discovery";
			response["TYPE"] = "T_LIST_CEC_DEVICE_V1";
			response["NAME"] = "Device Discovery";
			response["VALUE"] = cec_dev;

			REST_LOG_I("value: %d\n\r", ui2_indx);
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
#endif

int reset_and_admin_power_indicator(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR str[64] = {0};
    WDK_TOAST_T t_toast;

    type = get_type(root);
    Json::Value power_indx;
    power_indx[0] = "Off";
    power_indx[1] = "On";
    response["ELEMENTS"]=power_indx;
    INT32 indx = 0;
    UINT16  crnt_indx = 0;

#ifdef APP_LED_LOGO_CTRL
    indx = a_cfg_custom_get_led_logo_ctrl();
#endif
    crnt_indx = indx;
    //REST_LOG_I("sbx get power_indocator indx:%d\n\r",indx);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            response["VALUE"]=power_indx[indx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str,item1.asString().c_str());
            REST_LOG_E("sbx set power_indocator:%s\n\r",str);
            if (0 == c_strcmp("Off",str))
            {
                indx = 0;
#ifdef APP_LED_LOGO_CTRL
                a_cfg_custom_set_led_logo_ctrl(0);
#endif
            }
            else if (0 == c_strcmp("On",str))
            {
                indx = 1;
#ifdef APP_LED_LOGO_CTRL
                a_cfg_custom_set_led_logo_ctrl(1);
#endif
            }

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;

            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_POWER_INDICATOR;
            if (0 == indx)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_POWER_INDICATOR_OFF;
            }
            else if (1 == indx)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_POWER_INDICATOR_ON;
            }
            if (indx != crnt_indx)
            {
                rest_send_msg_to_nav(&t_toast);
            }
            menu_pm_repaint();
            break;
        }
        default:
            break;
    }
    return 0;
}

int reset_and_admin_usb_power(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR str[64] = {0};
    CHAR    str_usb_power_always_on[32] = {0};
    CHAR    str_usb_power_off_if_tv_off[32] = {0};
    UTF16_T*  pt_w2s = NULL;

    Json::Value usb_power;
    WDK_TOAST_T t_toast;

    type = get_type(root);

    pt_w2s = MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_USB_POWER_ALWAYS_ON);
    c_uc_w2s_to_ps(pt_w2s, str_usb_power_always_on, 32);
    pt_w2s = MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_USB_POWER_OFF_IF_TV_OFF);
    c_uc_w2s_to_ps(pt_w2s, str_usb_power_off_if_tv_off, 32);

    usb_power[0] = str_usb_power_always_on;
    usb_power[1] = str_usb_power_off_if_tv_off;
    REST_LOG_E("str_usb_power_always_on:%s\n\r",str_usb_power_always_on);
    REST_LOG_E("str_usb_power_off_if_tv_off:%s\n\r",str_usb_power_off_if_tv_off);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET.\n\r");
            UINT16 power_index =0;
            //TODO: hardcode for now, need owner to implement
            power_index = a_cfg_custom_get_usb_power_ctrl();
            REST_LOG_E("Get usb power:%d\n\r", power_index);

            response["ELEMENTS"] = usb_power;
            response["VALUE"] = usb_power[power_index];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET.\n\r");
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str,item1.asString().c_str());
            REST_LOG_E("set usb power:%s\n\r",str);
            if ((0 == c_strcmp("Always On",str)) || (0 == c_strcmp("Mantener Encendido",str)) || (0 == c_strcmp("Toujours Activé",str)))
            {
                a_cfg_custom_set_usb_power_ctrl((UINT8)0);
            }
            else
            {
                a_cfg_custom_set_usb_power_ctrl((UINT8)1);
            }
            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_USB_POWER;
            if ((0 == c_strcmp("Always On",str)) || (0 == c_strcmp("Mantener Encendido",str)) || (0 == c_strcmp("Toujours Activé",str)))
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_USB_POWER_ALWAYS_ON;
            }
            else
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_USB_POWER_OFF_IF_TV_OFF;
            }
            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();

            break;
        }
        default:
            break;
    }
    return 0;
}

int reset_and_admin_factory_reset(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_ACTION:
        {
            WDK_TOAST_T t_toast;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_WARNING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = WGL_PACK(MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_58));
            rest_send_msg_to_nav(&t_toast);

            REST_LOG_I("Enter a_menu_custom_reset_fac\n\r");
            a_menu_custom_reset_fac();
            break;
        }
        default:
            break;
    }
    return 0;
}
int reset_and_admin_vizio_privacy_policy(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);
    Json::Value privacy_policy;
    privacy_policy[0]="No";
    privacy_policy[1]="Yes";
    response["ELEMENTS"] = privacy_policy;
    INT32 indx = 1;
    switch (type)
    {
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");
            response["VALUE"] = privacy_policy[indx];
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

int reset_and_admin_smart_interactivity(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR str[64]={0};

    WDK_TOAST_T t_toast;
    type = get_type(root);
    Json::Value smart_interactivity;
    smart_interactivity[0]="Off";
    smart_interactivity[1]="On";
    response["ELEMENTS"]=smart_interactivity;
    response["VALUE"]=smart_interactivity[0];
    INT16 indx = 1;
    UINT16  crnt_indx = 0;

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
    UINT16 t_smart_inter;
    a_cfg_custom_get_acr(&t_smart_inter);
    if (ACR_ON == t_smart_inter)
    {
        indx = 1;
    }
    else
    {
        indx = 0;
    }
    crnt_indx = indx;
    REST_LOG_I("get smart_interactivity indx:%d \n\r",indx);
#endif
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            response["VALUE"]=smart_interactivity[indx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            UINT16  ui2_status    = 0;
            UINT8   ui1_state     = 0;

            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
            c_strcpy(str,item1.asString().c_str());

#ifdef APP_ADD_COUNTRY_CODE_SUPPORT
            ACFG_COUNTRY_CODE_T t_country = ACFG_COUNTRY_CODE_US;
            a_cfg_custom_get_country_code(&t_country);
            if (ACFG_COUNTRY_CODE_US != t_country)
            {
                REST_LOG_E("sbx disable smart enteractivity not US\n\r");
                break;
            }
#endif
            REST_LOG_E("sbx str:%s\n\r",str);
            if (0 == c_strcmp("Off",str))
            {
                indx = 0;
                a_tv_custom_set_viewing_data_accepted(indx);
                //a_tv_custom_set_viewing_data_accepted_by_oobe_menu(FALSE);
                a_cfg_custom_set_acr(ACR_OFF);
                //a_tv_custom_set_viewing_data_accepted_by_oobe_menu(FALSE);
            }
            else if (0 == c_strcmp("On",str))
            {
                indx = 1;
				a_tv_custom_set_viewing_data_accepted_by_oobe_menu(TRUE);
				a_tv_custom_set_viewing_data_accepted(indx);
                a_cfg_custom_set_acr(ACR_ON);
            }
            REST_LOG_E("sbx set smart_interactivity %d \n\r",indx);

            RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
            ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

            REST_LOG_I("oobe [state= %d]\n\r", (int)ui1_state);
#ifdef APP_C4TV_SUPPORT
            if(WZD_STATE_RESUME_C4TV != ui1_state)
#endif
            {
                c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

                t_toast.e_toast_style  = WDK_STRING_TOAST;
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VIEWING_DATA;
                if (0 == indx)
                {
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
                }
                else if (1 == indx)
                {
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
                }
                if (indx != crnt_indx)
                {
                    rest_send_msg_to_nav(&t_toast);
                }
            }

            break;
        }
        default:
            break;
    }
    return 0;

}
int reset_and_admin_store_demo(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR str[64] = {0};
    ACFG_RETAIL_MODE_T   t_retail_mode = ACFG_RETAIL_MODE_HOME;
    UINT16  crnt_indx = 0;
    UINT8   ui1_demo_mode = 0;
    CHAR s_active_app[32] = {0};

    type = get_type(root);
    Json::Value store_demo;
    store_demo[0]="Off";
    store_demo[1]="Demo 1";
	store_demo[2]="Demo 2";
    response["ELEMENTS"]=store_demo;
    response["VALUE"]=store_demo[0];

    INT32 indx = 0;

#ifdef APP_RETAIL_MODE_SUPPORT
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
#endif
	a_cfg_cust_get_demo_mode_value(&ui1_demo_mode);

    REST_LOG_I("current store_demo:%d.\n\r",ui1_demo_mode);
    if (ACFG_RETAIL_MODE_HOME == t_retail_mode)
    {
        indx = 0;
    }
    else
    {
        indx = 1;
    }
	indx = ui1_demo_mode;
    crnt_indx = indx;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            response["VALUE"]=store_demo[indx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            item2=root["message"];
            item1=item2["VALUE"];
           /* L_STORE_DEMO = [[u'Off', u'Demo 1', u'Demo 2'],
                [u'Apagado', u'Demo 1', u'Demo 2'],
                [u'Arr?at??', u'Demo 1', u'Demo 2']]*/

            //get current active app
            if (0 == a_am_get_active_app(s_active_app) &&
                0 == c_strcmp(s_active_app, "menu"))
            {
                a_amb_pause_app(s_active_app);
                REST_LOG_I("current active app is menu, exit it\r\n");
            }

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("REQUEST_SET target store_demo:%s.\n\r",str);

            if (0 == c_strcmp("Off",str) || 0 == c_strcmp("Apagado",str) || 0 == c_strcmp("Arr?at??",str))
            {
            #ifdef APP_RETAIL_MODE_SUPPORT
                a_cfg_cust_set_demo_mode_value(0);
                a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

                if(ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
                {
                    a_nav_retail_mode_exit();
                }
                else if(ACFG_RETAIL_MODE_NO_PLAYING == t_retail_mode)
                {
                    a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
                }
            #endif
            }
            else if (0 == c_strcmp("Demo 2",str) || 0 == c_strcmp("Activ??e",str) || 0 == c_strcmp("Activado",str))
            {
                INT32 i4_ret;
                RETAIL_MODE_PARAM_T t_param;
                a_cfg_cust_set_demo_mode_value(2);
                a_cfg_cust_set_retail_mode_first_time_setting(ACFG_RETAIL_MODE_IS_FIRST_TIME_SETTING);
                c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));
                t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_OOBE;
                t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
                t_param.t_launch_info.ui2_count = 15;
                i4_ret = a_nav_retail_mode_start(&t_param);
                RET_ON_ERR(i4_ret == NAVR_OK ? REST_R_OK : i4_ret);
        	}
            else if(0 == c_strcmp("Demo 1",str) || 0 == c_strcmp("Superpos??",str) || 0 == c_strcmp("Superpuesto",str))
            {
                if (0 == crnt_indx)
                {
                    REST_LOG_I("REQUEST_SET store_demo\n\r");
                    a_tv_custom_launch_retail_mode_by_hotkey();
                }
                else
                {
                    a_cfg_cust_set_demo_mode_value(1);
                    a_cfg_cust_set_retail_mode_first_time_setting(ACFG_RETAIL_MODE_IS_FIRST_TIME_SETTING);
                    {
                        INT32 i4_ret;
                        RETAIL_MODE_PARAM_T t_param;
                        c_memset(&t_param, 0, sizeof(RETAIL_MODE_PARAM_T));
                        t_param.t_launch_info.e_launch_from_app = NAV_RETAIL_MODE_RESUME_FROM_OOBE;
                        t_param.t_launch_info.e_launch_osd_type = RETAIL_MODE_LAUNCH_OSD_COUNTDOWN;
                        t_param.t_launch_info.ui2_count = 15;
                        i4_ret = a_nav_retail_mode_start(&t_param);
                        RET_ON_ERR(i4_ret == NAVR_OK ? REST_R_OK : i4_ret);
                    }
                }
            }

            break;
        }
        default:
            break;
    }

    return 0;
}



int reset_and_admin_advertising_limit_ad_tracking(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32       type = 0;
    UINT16      i2_get_idx = 0;
    UINT16      i2_set_idx = 0;
    CHAR        str[128] = {0};

    enum limit_ad_tracking
    {
        t_ON = 0,
        t_OFF,
    };

    i2_get_idx = menu_custom_get_limited_ad_tracking_idx();
    REST_LOG_I("get current Limited Ad Tracking :%d.\n\r", i2_get_idx);

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            Json::Value items;
            items[t_ON] = "On";
            items[t_OFF] = "Off";
            response["ELEMENTS"] = items;
            response["VALUE"] = items[i2_get_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            UINT16	ui2_mlm_warning_key = 0;
            UINT16  ui2_w2s_len;
            UTF16_T* pt_w2s = NULL;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strcpy(str, item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if (c_strcmp(str,"Off") == 0)
            {
                i2_set_idx = 1;
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_67;
            }
            else if (c_strcmp(str,"On") == 0)
            {
                i2_set_idx = 0;
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_66;
            }
            else
            {
                break;
            }

            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            pt_w2s = MLM_WARNINGS_TEXT(rest_get_mlm_warnings_lang_id(), ui2_mlm_warning_key);
            ui2_w2s_len = (c_uc_w2s_strlen(pt_w2s)+1)*2;
            t_toast.style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(ui2_w2s_len);
            if (t_toast.style.style_4.w2s_str != NULL)
            {
                c_memset((VOID*)t_toast.style.style_4.w2s_str, 0x0, ui2_w2s_len);
                c_memcpy((VOID*)t_toast.style.style_4.w2s_str, (const VOID *)pt_w2s, c_uc_w2s_strlen(pt_w2s)*sizeof(UTF16_T));
                rest_send_msg_to_nav(&t_toast);
            }

            REST_LOG_I("menu set Limited Ad Tracking %s\n\r", (i2_set_idx==0)?"On":"Off");
            menu_custom_set_limited_ad_tracking_idx(i2_set_idx);
            menu_pm_repaint();

            break;
        }
        default:
           break;
    }

    return 0;
}

int reset_and_admin_advertising_tvad_id_reset(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    WDK_TOAST_T t_toast;
    UINT16	ui2_mlm_warning_key = 0;
    UINT16	ui2_w2s_len;
    UTF16_T* pt_w2s = NULL;

    //SCPL call "tv_settings/admin_and_privacy/advertising/tvad_id_reset" to REST means SCPL has reset the tvad_id value.
    //rest_event_notify("tv_settings/system/reset_and_admin/tvad_id_reset", 0, NULL);

    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;

    ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_68;
    pt_w2s = MLM_WARNINGS_TEXT(rest_get_mlm_warnings_lang_id(), ui2_mlm_warning_key);
    ui2_w2s_len = (c_uc_w2s_strlen(pt_w2s)+1)*2;
    t_toast.style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(ui2_w2s_len);
    if (t_toast.style.style_4.w2s_str != NULL)
    {
        c_memset((VOID*)t_toast.style.style_4.w2s_str, 0x0, ui2_w2s_len);
        c_memcpy((VOID*)t_toast.style.style_4.w2s_str, (const VOID *)pt_w2s, c_uc_w2s_strlen(pt_w2s)*sizeof(UTF16_T));
        rest_send_msg_to_nav(&t_toast);
    }

    return 0;
}

int reset_and_admin_advertising_ad_replacement(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32       type = 0;
    UINT16      i2_get_idx = 0;
    UINT16      i2_set_idx = 0;
    CHAR        str[128] = {0};

    enum ad_replacement
    {
        t_ON = 0,
        t_OFF,
    };

    i2_get_idx = menu_custom_get_dynamic_content_idx();
    REST_LOG_I("get current Ad Replacement :%d.\n\r", i2_get_idx);

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            Json::Value items;
            items[t_ON] = "On";
            items[t_OFF] = "Off";
            response["ELEMENTS"] = items;
            response["VALUE"] = items[i2_get_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            UINT16	ui2_mlm_warning_key = 0;
            UINT16  ui2_w2s_len;
            UTF16_T* pt_w2s = NULL;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strcpy(str, item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if (c_strcmp(str,"Off") == 0)
            {
                i2_set_idx = 1;
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_70;
            }
            else if (c_strcmp(str,"On") == 0)
            {
                i2_set_idx = 0;
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_69;
            }
            else
            {
                break;
            }

            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            pt_w2s = MLM_WARNINGS_TEXT(rest_get_mlm_warnings_lang_id(), ui2_mlm_warning_key);
            ui2_w2s_len = (c_uc_w2s_strlen(pt_w2s)+1)*2;
            t_toast.style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(ui2_w2s_len);
            if (t_toast.style.style_4.w2s_str != NULL)
            {
                c_memset((VOID*)t_toast.style.style_4.w2s_str, 0x0, ui2_w2s_len);
                c_memcpy((VOID*)t_toast.style.style_4.w2s_str, (const VOID *)pt_w2s, c_uc_w2s_strlen(pt_w2s)*sizeof(UTF16_T));
                rest_send_msg_to_nav(&t_toast);
            }

            REST_LOG_I("menu set Ad Replacement %d\n\r", i2_set_idx);
            menu_custom_set_dynamic_content_idx(i2_set_idx);
            menu_pm_repaint();

            break;
        }
        default:
           break;
    }

    return 0;
}

int system_information_tuner_information_physical_channel(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    INT32  phy_channel = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            BOOL                            b_found = FALSE;
            SVL_REC_T                       t_svl_rec ;
            ISL_REC_T                       t_isl_rec;
            CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
            UINT8                           ui1_input_id = 0;

            c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));

            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            RET_ON_ERR(i4_ret);
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            RET_ON_ERR(i4_ret);
            i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
            RET_ON_ERR(i4_ret);

            if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
            {
                phy_channel = 0;
            }
            else
            {
                /*get svl record*/
                rest_get_crnt_svl_rec (&t_svl_rec ,&b_found) ;

                phy_channel= (INT32)SB_TSL_GET_PTC_FROM_RECID(t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id);
            }
            REST_LOG_I("value: %d\n\r", phy_channel);
            value_set_response(response, phy_channel);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            //READ ONLY
            break;
        }
        default:
            break;
    }
    return 0;
}
int system_information_tuner_information_frequency(Json::Value & root, Json::Value & response)
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

            BOOL                            b_found = FALSE;
            BOOL                            b_digital = FALSE;
            BOOL                            b_cable = FALSE;
            SVL_REC_T                       t_svl_rec ;
            TSL_REC_T                       t_tsl_rec;
            ISL_REC_T                       t_isl_rec;
            CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
            UINT8                           ui1_input_id = 0;
            UINT32                          ui4_ver_id = 0;
            UINT32                          ui4_freq = 0;
            UINT16                          ui2_crnt_svl_id = 0;

            c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
            c_memset(&t_tsl_rec, 0, sizeof(TSL_REC_T));

            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            RET_ON_ERR(i4_ret);
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            RET_ON_ERR(i4_ret);
            i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
            RET_ON_ERR(i4_ret);

            if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
            {
                ui4_freq = 0;
            }
            else
            {
                /*get svl record*/
                rest_get_crnt_svl_rec (&t_svl_rec ,&b_found) ;

                /*get tsl record*/
                c_tsl_get_rec(rest_get_crnt_tsl(),
                                t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                                &t_tsl_rec,
                                &ui4_ver_id);

                i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
                RET_ON_ERR(i4_ret);

                b_cable = (ATSC_TRSTRL_SVL_ID == ui2_crnt_svl_id) ? FALSE : TRUE ;
                b_digital = (BRDCST_TYPE_ANALOG == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type) ? FALSE :TRUE ;

                switch ((UINT8)(b_cable) << 1 | (UINT8)(b_digital))
                {
                    case 0 :                                    /* air && analog */
                        ui4_freq = t_tsl_rec.udata.t_ter_ana.ui4_freq ;
                        // for DTV02028123
                        ui4_freq += 15625;
                        break ;
                    case 1 :                                    /* air && digital */
                        ui4_freq = t_tsl_rec.udata.t_ter_dig.ui4_freq;
                        break ;
                    case 2 :                                    /* cable && analog */
                        ui4_freq = t_tsl_rec.udata.t_cab_ana.ui4_freq ;
                        break ;
                    case 3 :                                    /* cable && digital */
                        ui4_freq = t_tsl_rec.udata.t_cab_dig.ui4_freq ;
                        break ;
                    default :
                        break ;
                }
            }
            // for DTV02028123
            ui4_freq /= 1000000;
            REST_LOG_I("value: %d\n\r", ui4_freq);
            value_set_response(response, ui4_freq);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            //READ ONLY
            break;
        }
        default:
            break;
    }
    return 0;
}
int system_information_tuner_information_modulation(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    CHAR str_mod[32] = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            BOOL                            b_found = FALSE;
            BOOL                            b_digital = FALSE;
            BOOL                            b_cable = FALSE;
            SVL_REC_T                       t_svl_rec ;
            TSL_REC_T                       t_tsl_rec;
            ISL_REC_T                       t_isl_rec;
            CHAR                            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
            UINT8                           ui1_input_id = 0;
            UINT32                          ui4_ver_id = 0;
            UINT32                          ui4_msgid = 0;
            UINT16                          ui2_crnt_svl_id = 0;

            c_memset(&t_svl_rec, 0, sizeof(SVL_REC_T));
            c_memset(&t_tsl_rec, 0, sizeof(TSL_REC_T));

            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            RET_ON_ERR(i4_ret);
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            RET_ON_ERR(i4_ret);
            i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
            RET_ON_ERR(i4_ret);

            if (INP_SRC_TYPE_TV != t_isl_rec.e_src_type)
            {
                ui4_msgid = MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_UNLOCK;
            }
            else
            {
                /*get svl record*/
                rest_get_crnt_svl_rec (&t_svl_rec ,&b_found) ;

                /*get tsl record*/
                c_tsl_get_rec(rest_get_crnt_tsl(),
                                t_svl_rec.uheader.t_rec_hdr.ui2_tsl_rec_id,
                                &t_tsl_rec,
                                &ui4_ver_id);

                i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
                RET_ON_ERR(i4_ret);

                b_cable = (ATSC_TRSTRL_SVL_ID == ui2_crnt_svl_id) ? FALSE : TRUE ;
                b_digital = (BRDCST_TYPE_ANALOG == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type) ? FALSE :TRUE ;

                switch ((UINT8)(b_cable) << 1 | (UINT8)(b_digital))
                {
                    case 0 :                                    /* air && analog */
                        ui4_msgid = MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_NTSC;
                        break ;
                    case 1 :                                    /* air && digital */
                        ui4_msgid = (UINT32)t_tsl_rec.udata.t_ter_dig.e_mod +MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_UNKNOWN ;
                        break ;
                    case 2 :                                    /* cable && analog */
                        ui4_msgid = MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_NTSC;
                        break ;
                    case 3 :                                    /* cable && digital */
                        ui4_msgid = (UINT32)t_tsl_rec.udata.t_cab_dig.e_mod +MLM_MENU_KEY_TV_DIAGNOSTICS_MOD_UNKNOWN ;
                        break ;
                    default :
                        break ;
                }
            }
            c_uc_w2s_to_ps(MENU_TEXT(ui4_msgid),str_mod,c_uc_w2s_strlen(MENU_TEXT(ui4_msgid)));
            REST_LOG_I("str_indx: %d,str_mod:%s\n\r", ui4_msgid,str_mod);
            string_set_response(response, str_mod);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            //READ ONLY
            break;
        }
        default:
            break;
    }
    return 0;
}

int system_information_tuner_information_status(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    Json::Value items;

    INT32 i4_idx = 0;

    items[0] = "Unlock";
    items[1] = "Lock";
    response["ELEMENTS"] = items;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            i4_idx = rest_get_menu_is_signal_loss();
            REST_LOG_I("get idx:%d\n\r", i4_idx);
            response["VALUE"] = items[i4_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            //READ ONLY
            break;
        }
        default:
            break;
    }
    return 0;
}

int system_information_tuner_information_signal_strength(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            SVL_REC_T           t_svl_rec;
            BOOL                b_found;
            BOOL                b_digital_ch = FALSE;

            /* Get digital/analog channel */
            rest_get_crnt_svl_rec(&t_svl_rec, &b_found);

            if(b_found &&
               t_svl_rec.uheader.t_rec_hdr.e_brdcst_type != BRDCST_TYPE_ANALOG)
            {
                b_digital_ch = TRUE;
            }
            if (b_digital_ch)
            {
                UINT8 ui1_signal_level = 0;
                i4_ret = c_svctx_get_signal_level(rest_get_crnt_svctx(),&ui1_signal_level);
                LOG_ON_ERR(i4_ret);
                REST_LOG_I("DTV signal level:%d\n\r",ui1_signal_level);
                value_set_response(response, ui1_signal_level);
            }
            else
            {
                INT16 ui2_signal_level = 0;
                i4_ret = c_svctx_get_dbm_signal_level(rest_get_crnt_svctx(),&ui2_signal_level);
                LOG_ON_ERR(i4_ret);
                REST_LOG_I("ATV signal level:%d\n\r",ui2_signal_level);
                value_set_response(response, ui2_signal_level);
            }

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

int system_information_tuner_information_name(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR    str_name[128] = {0};
            UINT32   ui4_idx = 0;

            a_cfg_custom_get_tuner_name(str_name);

            REST_LOG_I("tuner name:%s\n\r", str_name);
            string_set_response(response, str_name);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            //READ ONLY
            break;
        }
        default:
            break;
    }
    return 0;
}

int country(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    Json::Value country;
    enum COUNTRY
    {
        _USA = 0,
        _MEX = 1,
        _CAN = 2,
        _UNK = 3,
        _COUNTRY_MAX,
    };

    country[_USA] = "USA";
    country[_CAN] = "Canada";
    country[_MEX] = "Mexico";
    country[_UNK] = "Unknown";

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r");

            UINT16 ui2_indx=-1;
            ACFG_COUNTRY_CODE_T t_country;
            a_cfg_custom_get_country_code(&t_country);

            if(t_country>=_COUNTRY_MAX)
            {
                REST_LOG_E("Get country code wrong\n");
                return -1;
            }

            ui2_indx = t_country;
            response["ELEMENTS"]=country;
            response["VALUE"] = country[ui2_indx];

            REST_LOG_I("value: %d \n\r", ui2_indx);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("SET\n\r");

            Json::Value value;
            Json::Value message;
            INT32 i4_country_idx = -1;

            message=root["message"];
            value=message["VALUE"];

            REST_LOG_E("set country to [%s]\n",value.asString().c_str());
            for(int i=0; i<_COUNTRY_MAX; i++)
            {
                if(strcmp(value.asString().c_str(),country[i].asString().c_str())==0) //handle the argument no matter it was translated or in English
                {
                    i4_country_idx = i;
                    break;
                }
            }

            REST_LOG_E("country code index %d\n",i4_country_idx);
            if(i4_country_idx != -1)
            {
                 a_cfg_custom_set_country_code((ACFG_COUNTRY_CODE_T)i4_country_idx);

                // According to the select country to set the country code for Wi-Fi
                switch ((ACFG_COUNTRY_CODE_T)i4_country_idx)
                {
                    case ACFG_COUNTRY_CODE_MEX:
//#ifdef MT5583_MODEL
//                        system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=2");
//#else
                        system("wpa_cli -i wlan0 set country=MX");
//#endif
                        break;
                    case ACFG_COUNTRY_CODE_CA:
//#ifdef MT5583_MODEL
//                        system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=1");
//#else
                        system("wpa_cli -i wlan0 set country=CA");
//#endif
                        break;
                    case ACFG_COUNTRY_CODE_US:
//#ifdef MT5583_MODEL
//                        system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=0");
//#else
                        system("wpa_cli -i wlan0 set country=US");
//#endif
                        break;
                    case ACFG_COUNTRY_CODE_UNKNOWN:
//#ifdef MT5583_MODEL
//                        system("/3rd/bin/wpa_supplicant/common/iwpriv wlan0 set CountryRegion=5");
//#else
                        system("wpa_cli -i wlan0 set country=WW");
//#endif
                        break;
                }
            }
            else
            {
                REST_LOG_E("No match country\n");
                return -1;
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int hide_from_input_list(Json::Value & root, Json::Value & response){REST_LOG_I("Enter\n\r");return 0;}
int hide_input_tv(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;
	UINT8 i2_get_val = 0;
	UINT8 ui1_hide_value = 0;

	enum _resolution_type
	{
		_VISIBLE = 0,
		_HIDDEN,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_VISIBLE] = "Visible";
	j_level[_HIDDEN] = "Hidden";
	a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if (((ui1_hide_value >> (6)) & (UINT8)1) == 1) {
				i2_get_val = _HIDDEN;
			} else {
				i2_get_val = _VISIBLE;
			}

			response["VALUE"] = j_level[i2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			INT32	 type = 0;
			INT16	 i2_pre_val = 0;
			INT16	 i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_TUNER;

			Json::Value message = root["message"];
			Json::Value value = message["VALUE"];

			for(int i=0;i<_TYPE_MAX;i++)
			{
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_INPUT_IS_VISIBLE - i;
				   break;
			   }
			}

			if(i2_val == _VISIBLE)
			{
                ui1_hide_value &= ~((UINT8)1 << (6));
            }
            else if(i2_val == _HIDDEN)
            {
                ui1_hide_value |= (UINT8)1 << (6);
            }
			a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

			if(i2_val==-1)
			{
			   REST_LOG_E("Get invailed arguments %s\n",value.asString().c_str());
			   i4_ret = -1;
			   break;
			}

			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
		break;
	}
	return i4_ret;
}

int hide_input_comp(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;
	UINT8 i2_get_val = 0;
	UINT8 ui1_hide_value = 0;

	enum _resolution_type
	{
		_VISIBLE = 0,
		_HIDDEN,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_VISIBLE] = "Visible";
	j_level[_HIDDEN] = "Hidden";
	a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if (((ui1_hide_value >> (5)) & (UINT8)1) == 1) {
				i2_get_val = _HIDDEN;
			} else {
				i2_get_val = _VISIBLE;
			}

			response["VALUE"] = j_level[i2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			INT32	 type = 0;
			INT16	 i2_pre_val = 0;
			INT16	 i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_COMP;

			Json::Value message = root["message"];
			Json::Value value = message["VALUE"];

			for(int i=0;i<_TYPE_MAX;i++)
			{
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_INPUT_IS_VISIBLE - i;
				   break;
			   }
			}

			if(i2_val == _VISIBLE)
			{
				ui1_hide_value &= ~((UINT8)1 << (5));
			}
			else if(i2_val == _HIDDEN)
			{
				ui1_hide_value |= (UINT8)1 << (5);
			}
			a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

			if(i2_val==-1)
			{
			   REST_LOG_E("Get invailed arguments %s\n",value.asString().c_str());
			   i4_ret = -1;
			   break;
			}

			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
		break;
	}
	return i4_ret;
}

int hide_input_hdmi1(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;
	UINT8 i2_get_val = 0;
	UINT8 ui1_hide_value = 0;
	UINT8 ui1_hide_value_manually = 0;

	enum _resolution_type
	{
		_VISIBLE = 0,
		_HIDDEN,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_VISIBLE] = "Visible";
	j_level[_HIDDEN] = "Hidden";
	//a_cfg_cust_get_hide_from_input(&ui1_hide_value);
	a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value_manually);

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if (((ui1_hide_value_manually >> (1-1)) & (UINT8)1) == 1 //&&
                /*(((ui1_hide_value >> (1-1)) & (UINT8)1) == 0)*/) {
				i2_get_val = _HIDDEN;
			} else {
				i2_get_val = _VISIBLE;
			}

			response["VALUE"] = j_level[i2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			INT32	 type = 0;
			INT16	 i2_pre_val = 0;
			INT16	 i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI1;

			Json::Value message = root["message"];
			Json::Value value = message["VALUE"];

			for(int i=0;i<_TYPE_MAX;i++)
			{
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_INPUT_IS_VISIBLE - i;
				   break;
			   }
			}

			if(i2_val == _VISIBLE)
			{
				ui1_hide_value_manually &= ~((UINT8)1 << (1 - 1));
			}
			else if(i2_val == _HIDDEN)
			{
				ui1_hide_value_manually |= (UINT8)1 << (1 - 1);
			}
			a_cfg_cust_set_hide_from_input_manually(ui1_hide_value_manually);

			if(i2_val==-1)
			{
			   REST_LOG_E("Get invailed arguments %s\n",value.asString().c_str());
			   i4_ret = -1;
			   break;
			}

			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
		break;
	}
	return i4_ret;
}

int hide_input_hdmi2(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;
	UINT8 i2_get_val = 0;
	UINT8 ui1_hide_value = 0;
	UINT8 ui1_hide_value_manually = 0;

	enum _resolution_type
	{
		_VISIBLE = 0,
		_HIDDEN,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_VISIBLE] = "Visible";
	j_level[_HIDDEN] = "Hidden";
	//a_cfg_cust_get_hide_from_input(&ui1_hide_value);
	a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value_manually);

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if (((ui1_hide_value_manually >> (2-1)) & (UINT8)1) == 1 //&&
				/*(((ui1_hide_value >> (2-1)) & (UINT8)1) == 0)*/) {
				i2_get_val = _HIDDEN;
			} else {
				i2_get_val = _VISIBLE;
			}

			response["VALUE"] = j_level[i2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			INT32	 type = 0;
			INT16	 i2_pre_val = 0;
			INT16	 i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI2;

			Json::Value message = root["message"];
			Json::Value value = message["VALUE"];

			for(int i=0;i<_TYPE_MAX;i++)
			{
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_INPUT_IS_VISIBLE - i;
				   break;
			   }
			}

			if(i2_val == _VISIBLE)
			{
				ui1_hide_value_manually &= ~((UINT8)1 << (2 - 1));
			}
			else if(i2_val == _HIDDEN)
			{
				ui1_hide_value_manually |= (UINT8)1 << (2 - 1);
			}
			a_cfg_cust_set_hide_from_input_manually(ui1_hide_value_manually);

			if(i2_val==-1)
			{
			   REST_LOG_E("Get invailed arguments %s\n",value.asString().c_str());
			   i4_ret = -1;
			   break;
			}

			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
		break;
	}
	return i4_ret;
}

int hide_input_hdmi3(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;
	UINT8 i2_get_val = 0;
	UINT8 ui1_hide_value = 0;
	UINT8 ui1_hide_value_manually = 0;

	enum _resolution_type
	{
		_VISIBLE = 0,
		_HIDDEN,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_VISIBLE] = "Visible";
	j_level[_HIDDEN] = "Hidden";
	//a_cfg_cust_get_hide_from_input(&ui1_hide_value);
	a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value_manually);

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if (((ui1_hide_value_manually >> (3-1)) & (UINT8)1) == 1 //&&
                /*(((ui1_hide_value >> (3-1)) & (UINT8)1) == 0)*/) {
				i2_get_val = _HIDDEN;
			} else {
				i2_get_val = _VISIBLE;
			}

			response["VALUE"] = j_level[i2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			INT32	 type = 0;
			INT16	 i2_pre_val = 0;
			INT16	 i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI3;

			Json::Value message = root["message"];
			Json::Value value = message["VALUE"];

			for(int i=0;i<_TYPE_MAX;i++)
			{
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_INPUT_IS_VISIBLE - i;
				   break;
			   }
			}

			if(i2_val == _VISIBLE)
			{
				ui1_hide_value_manually &= ~((UINT8)1 << (3 - 1));
			}
			else if(i2_val == _HIDDEN)
			{
				ui1_hide_value_manually |= (UINT8)1 << (3 - 1);
			}
			a_cfg_cust_set_hide_from_input_manually(ui1_hide_value_manually);

			if(i2_val==-1)
			{
			   REST_LOG_E("Get invailed arguments %s\n",value.asString().c_str());
			   i4_ret = -1;
			   break;
			}

			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
		break;
	}
	return i4_ret;
}

int hide_input_hdmi4(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;
	UINT8 i2_get_val = 0;
	UINT8 ui1_hide_value = 0;
	UINT8 ui1_hide_value_manually = 0;

	enum _resolution_type
	{
		_VISIBLE = 0,
		_HIDDEN,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_VISIBLE] = "Visible";
	j_level[_HIDDEN] = "Hidden";
	//a_cfg_cust_get_hide_from_input(&ui1_hide_value);
	a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value_manually);

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if (((ui1_hide_value_manually >> (4-1)) & (UINT8)1) == 1// &&
				/*(((ui1_hide_value >> (4-1)) & (UINT8)1) == 0)*/) {
				i2_get_val = _HIDDEN;
			} else {
				i2_get_val = _VISIBLE;
			}

			response["VALUE"] = j_level[i2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			INT32	 type = 0;
			INT16	 i2_pre_val = 0;
			INT16	 i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_INPUT_HDMI4;

			Json::Value message = root["message"];
			Json::Value value = message["VALUE"];

			for(int i=0;i<_TYPE_MAX;i++)
			{
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_INPUT_IS_VISIBLE - i;
				   break;
			   }
			}

			if(i2_val == _VISIBLE)
			{
				ui1_hide_value_manually &= ~((UINT8)1 << (4 - 1));
			}
			else if(i2_val == _HIDDEN)
			{
				ui1_hide_value_manually |= (UINT8)1 << (4 - 1);
			}
			a_cfg_cust_set_hide_from_input_manually(ui1_hide_value_manually);

			if(i2_val==-1)
			{
			   REST_LOG_E("Get invailed arguments %s\n",value.asString().c_str());
			   i4_ret = -1;
			   break;
			}

			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
		break;
	}
	return i4_ret;
}


int energy_saving_mode(Json::Value & root, Json::Value & response){REST_LOG_I("Enter\n\r");return 0;}
int oled_panel(Json::Value & root, Json::Value & response){REST_LOG_I("Enter\n\r");return 0;}

int screen_refresher(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;
	UINT8 i2_get_val = SCREEN_REFRESH_START_CANCEL;

	enum _resolution_type
	{
		_CANCEL = 0,
		_SAPO,
		_SN,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_CANCEL] = "Cancel";
	j_level[_SAPO] = "Start at Power Off";
	j_level[_SN] = "Start Now";

	a_cfg_cust_get_oled_panel_refresh_value(&i2_get_val);
	REST_LOG_I("get current oled panel screen refresher %d.\n\r", i2_get_val);

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if(i2_get_val>=_TYPE_MAX)
			{
				REST_LOG_E("Invailed return\n");
				i4_ret = -1;
				break;
			}
			response["VALUE"] = j_level[i2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			INT32	 type = 0;
			INT16	 i2_pre_val = 0;
			INT16	 i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_VID_OLED_SCRREN_REFRESH;

			Json::Value message = root["message"];
			Json::Value value = message["VALUE"];

			for(int i=0;i<_TYPE_MAX;i++)
			{
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_OLED_SCRREN_REFRESH_BTN_CANCELE+ i;
				   break;
			   }
			}

			if(i2_val==-1)
			{
			   REST_LOG_E("Get invailed arguments %s\n",value.asString());
			   i4_ret = -1;
			   break;
			}

			a_cfg_cust_set_oled_panel_refresh_value(i2_val);
			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
		break;
	}
	return i4_ret;
}

int pixel_shift(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;
	UINT16 ui2_get_val = 0;

	enum _resolution_type
	{
		_OFF = 0,
		_ON,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_OFF] = "Off";
	j_level[_ON] = "On";

	ui2_get_val = menu_get_vid_oled_pixel_shift_idx();
	REST_LOG_I("get current oled panel pixel shift %d.\n\r", ui2_get_val);

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if(ui2_get_val>=_TYPE_MAX)
			{
				REST_LOG_E("Invailed return\n");
				i4_ret = -1;
				break;
			}
			response["VALUE"] = j_level[ui2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			INT32	 type = 0;
			INT16	 i2_pre_val = 0;
			INT16	 i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_VID_OLED_PIXEL_SHIFT;

			Json::Value message = root["message"];
			Json::Value value = message["VALUE"];

			for(int i=0;i<_TYPE_MAX;i++)
			{
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF - i;
				   break;
			   }
			}

			if(i2_val==-1)
			{
			   REST_LOG_E("Get invailed arguments %s\n",value.asString());
			   i4_ret = -1;
			   break;
			}
			menu_set_vid_oled_pixel_shift_idx(i2_val);
			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
		break;
	}
	return i4_ret;
}

int voice_remote(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");
            // MVV-11590: ref _action_voice_remote
            a_nav_ipts_select_virtual_input("SMARTCAST");
            rest_event_notify("app/current", 2, "10");
            break;
        }
        default:
            break;
    }
    return 0;
}

int power_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[128] = {0};
    CHAR    str_mode_eco[32] = {0};
    CHAR    str_mode_quick[32] = {0};
    UINT32  ui4_len = 128;
    UINT8   ui1_power_mode = ICL_CUSTOM_POWER_MODE_ECO;
    UINT16  crnt_indx = 0;
    UINT16  indx = 0;
    UTF16_T*  pt_w2s = NULL;

    enum POWER_SETTING
    {
        ECO = 0,
        QUICK_START
    };

    pt_w2s = MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_POWER_MODE_QUICK);
    c_uc_w2s_to_ps(pt_w2s, str_mode_quick, 32);
    pt_w2s = MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_POWER_MODE_ECO);
    c_uc_w2s_to_ps(pt_w2s, str_mode_eco, 32);

    WDK_TOAST_T t_toast;
    type = get_type(root);
    Json::Value fast_boot;
    fast_boot[ECO] = str_mode_eco;
    fast_boot[QUICK_START] = str_mode_quick;
    response["ELEMENTS"]=fast_boot;

    UINT8 ui1_fast_boot = 0;
#ifdef APP_SUPPORT_STR_CORE_OFF
    a_cfg_get_fast_boot(&ui1_fast_boot);
    if (0 == ui1_fast_boot)
    {
        indx = QUICK_START;
    }
    else
    {
        indx = ECO;
    }
#endif
    crnt_indx = indx;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            response["VALUE"]=fast_boot[indx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            string_get_string(root, str, ui4_len);
            REST_LOG_I("str: %s\n\r", str);

            if (strcmp(str, "Eco Mode") == 0)
            {
                ui1_power_mode = ICL_CUSTOM_POWER_MODE_ECO;
#ifdef APP_SUPPORT_STR_CORE_OFF
                a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_ON);
#endif
                indx = ECO;
            }
            else if (strcmp(str, "Quick Start") == 0)
            {
                ui1_power_mode = ICL_CUSTOM_POWER_MODE_QUICK_START;
#ifdef APP_SUPPORT_STR_CORE_OFF
                a_cfg_set_fast_boot(APP_CFG_FAST_BOOT_OFF);
#endif
                indx = QUICK_START;
            }

            a_icl_custom_set_power_mode(ui1_power_mode);
            a_cfg_custom_set_drv_eco_mode((UINT16)ui1_power_mode);
            a_cfg_custom_set_power_mode_save(ui1_power_mode);
            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_POWER_MODE;
            if (strcmp(str, "Eco Mode") == 0)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_POWER_MODE_ECO;
            }
            else if (strcmp(str, "Quick Start") == 0)
            {
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_POWER_MODE_QUICK;
            }
            if (indx != crnt_indx)
            {
                rest_send_msg_to_nav(&t_toast);
            }
            menu_pm_repaint();
            break;
        }
        default:
            break;
    }
    return 0;
}

int aspect_ratio(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    typedef struct T_WIDE_LIST_TEXT_MAP
    {
        SCC_VID_SCREEN_MODE_T e_scr_mode;
        CHAR s_text[32];
        CHAR s_text_lang[32];
        UINT16 ui2_mlm_key;
    }T_WIDE_LIST_TEXT_MAP;

    UINT16 i = 0;
    UINT16 j = 0;
    INT32 type = 0;
    INT32 ret = 0;
    UTF16_T* pt_w2s = NULL;
    SCC_VID_SCREEN_MODE_T e_scr_mode = SCC_VID_SCREEN_MODE_UNKNOWN;
    SCC_VID_SCREEN_MODE_T ae_scr_mode[5] = {SCC_VID_SCREEN_MODE_UNKNOWN};
    T_WIDE_LIST_TEXT_MAP at_wide_map[5] = {
        {SCC_VID_SCREEN_MODE_NORMAL,            "Normal",       "Normal",       MLM_SETTINGS_KEY_ASPECT_RATIO_NORMAL},
        {SCC_VID_SCREEN_MODE_LETTERBOX,         "Stretch",      "Stretch",      MLM_SETTINGS_KEY_ASPECT_RATIO_STRETCH},
        {SCC_VID_SCREEN_MODE_CUSTOM_DEF_1,      "Wide",         "Wide",         MLM_SETTINGS_KEY_ASPECT_RATIO_WIDE},
        {SCC_VID_SCREEN_MODE_CUSTOM_DEF_0,      "Zoom",         "Zoom",         MLM_SETTINGS_KEY_ASPECT_RATIO_ZOOM},
        {SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM,   "Panoramic",    "Panoramic",    MLM_SETTINGS_KEY_ASPECT_RATIO_PANORAMIC}
    };

    Json::Value aspect_ratio_list;

    type = get_type(root);

    /* Get current wide list */
    ret = a_nav_screen_mode_get_wide_list(ae_scr_mode, 5);
    if (ret > 0)
    {
        for (j = 0; j < 5; j++)
        {
            pt_w2s = MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), at_wide_map[j].ui2_mlm_key);
            c_uc_w2s_to_ps(pt_w2s, at_wide_map[j].s_text_lang, 32);
        }
        for (i = 0; i < 5 && i < ret; i++)
        {
            aspect_ratio_list[i] = "Normal";

            for (j = 0; j < 5; j++)
            {
                if (ae_scr_mode[i] == at_wide_map[j].e_scr_mode)
                {
                    aspect_ratio_list[i] = at_wide_map[j].s_text_lang;
                    break;
                }
            }
        }
    }
    else
    {
        aspect_ratio_list[0] = "Normal";
        aspect_ratio_list[1] = "Stretch";
        aspect_ratio_list[2] = "Wide";
        aspect_ratio_list[3] = "Zoom";
        aspect_ratio_list[4] = "Panoramic";
    }
    response["ELEMENTS"] = aspect_ratio_list;

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            response["VALUE"] = "Normal";

            a_nav_screen_mode_get_cur_mode(&e_scr_mode);
            for (i = 0; i < 5; i++)
            {
                if (e_scr_mode == at_wide_map[i].e_scr_mode)
                {
                    response["VALUE"] = at_wide_map[i].s_text_lang;
                    break;
                }
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            CHAR    str[32] = {0};
            SCC_VID_SCREEN_MODE_T   e_scr_mode_crnt = SCC_VID_SCREEN_MODE_UNKNOWN;
            BOOL                    b_enable_change_wide_mode = FALSE;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strncpy(str, (const CHAR *)item1.asString().c_str(), 31);

            REST_LOG_I("str:%s\n\r", str);

            for (i = 0; i < 5; i++)
            {
                if (c_strcmp(at_wide_map[i].s_text, str) == 0 || c_strcmp(at_wide_map[i].s_text_lang, str) == 0)
                {
                    e_scr_mode = at_wide_map[i].e_scr_mode;
                    break;
                }
            }

            /* get curnt screen mode */
            a_nav_screen_mode_get_cur_mode(&e_scr_mode_crnt);
            a_cfg_custom_get_wide_mode_enable_change(&b_enable_change_wide_mode);

            /* Set screen mode to config. */
            if (a_cfg_av_set (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE), (INT16) e_scr_mode) != APP_CFGR_OK)
            {
                REST_LOG_E("a_cfg_av_set failed \n");
            }

            /* Update config. */
            if (a_cfg_update_screen_mode_ex() != APP_CFGR_OK)
            {
                REST_LOG_E("a_cfg_av_update failed \n");
            }

            //  Add  Aspect_Ratio announce
            if (e_scr_mode_crnt != e_scr_mode && b_enable_change_wide_mode)
            {
                WDK_TOAST_T  t_toast;
                c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

                t_toast.e_toast_style  = WDK_STRING_TOAST;
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_ASPECT_RATIO;
                for (i = 0; i < 5; i++)
                {
                    if (e_scr_mode == at_wide_map[i].e_scr_mode)
                    {
                        t_toast.style.style_2.ui4_id_2 = at_wide_map[i].ui2_mlm_key;
                        break;
                    }
                }
                rest_send_msg_to_nav(&t_toast);
            }

            break;
        }
        default:
            break;
    }
    return 0;
}

int tv_name(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    CHAR current_tv_name[128] = {0};
    UINT32 ui4_len = 32;
    a_cfg_custom_get_tv_name(current_tv_name,&ui4_len);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            REST_LOG_I("get current_tv_name: %s\n\r", current_tv_name);
            string_set_response(response, current_tv_name);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            //CHAR    s_ssid[256] = {0};
            CHAR str[128] = {0};
            UINT32 length = 128;

            REST_LOG_I("Existed name: %s\n\r", current_tv_name);
            //rest_get_wifi_ssid(s_ssid);
            //REST_LOG_I("Existed ssid: %s, len:%d.\n\r", s_ssid, c_strlen(s_ssid));

            string_get_string(root, str, length);
            /*The MAXnum of 24 support*/
            str[24] = '\0';
            REST_LOG_I("len of [%s]: %u!\n", str, c_strlen(str));

            if (0 != c_strncmp(current_tv_name, str, 128) /*|| 0 != c_strncmp(s_ssid, str, 256)*/)
            {
                REST_LOG_I("Save name:%s.\n\r", str);
                a_cfg_custom_set_tv_name(str);
                a_mdns_stop();
                a_mdns_start();

                /*
                rest_change_softap_name(str);

                REST_DATA_WIFI_AP_T t_ap;
                INT32 i4_ret = 0;
                c_memset(&t_ap, 0, sizeof(t_ap));
                i4_ret = rest_get_curr_access_point(&t_ap);
                if (i4_ret == 0)
                {
                    // restart softap if the user doesn't skip Wi-Fi connection
                    REST_LOG_I("Restart softap\n\r", str);
                    rest_stop_softap();
                    rest_start_softap();
                }
                */
                menu_pm_repaint();
            }
            rest_event_notify("tv_settings/cast/device_name", 0, str);

            break;
        }
        default:
            break;
    }

    return 0;
}

int reset_and_admin_system_pin(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    //CHAR str[64]= "12345678";

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            //string_set_response(response, str);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            UTF16_T    u2s_pwd[10] = {0};
            CHAR       str[10] = {0};

            WDK_TOAST_T t_toast;

            string_get_string(root, str, 10);

            REST_LOG_I("set pin: %s\n\r", str);
            c_uc_ps_to_w2s(str, u2s_pwd,
                    (c_strlen(str) > APP_CFG_MAX_PWD_LEN) ? APP_CFG_MAX_PWD_LEN : c_strlen(str));
            a_cfg_set_password(u2s_pwd);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_SYS_PIN_CODE;
            t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_SYS_PIN_CODE_SET;

            rest_send_msg_to_nav(&t_toast);

            a_set_is_pin_confirmed(true);

            break;
        }
        default:
            break;
    }
    return 0;
}


int system_information_tv_information_series(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR    str[16] = {0};
            INT32   i4_ret = 0;
            CHAR    model_name[32] = {0};

            i4_ret = a_cfg_custom_get_model_name(model_name);
            LOG_ON_ERR(i4_ret);
            if (c_strlen(model_name) == 0)
            {
                c_strncpy(model_name, "V405-H9", strlen("V405-H9"));
            }

            REST_LOG_I("model_name: %s\n\r", model_name);

            str[0] = model_name[0];
            REST_LOG_I("series: %s\n\r", str);
            string_set_response(response, str);
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

int system_information_tv_information_size(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT32   val = 0;
            INT32   i4_ret = 0;
            CHAR    model_name[32] = {0};

            i4_ret = a_cfg_custom_get_model_name(model_name);
            LOG_ON_ERR(i4_ret);

            REST_LOG_I("model_name: %s\n\r", model_name);

            if ((0 == i4_ret) &&
                (strlen(model_name)>=3))
            {
                val = (model_name[1]-'0') * 10 + (model_name[2]-'0');
            }
            else
            {
                val = 32;
            }

            REST_LOG_I("size: %d\n\r", val);

            value_set_response(response, val);
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

int accessibility_talkback(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    UINT8 ui1_val = 0;

    type = get_type(root);
    a_cfg_get_tts_switch_status(&ui1_val);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "On";

            response["ELEMENTS"] = items;
            response["VALUE"] = items[ui1_val];
            REST_LOG_I("accessibility_talkback val:%d\n\r", ui1_val);
        }
            break;
        case argument::RequestType::REQUEST_SET:
        {
            CHAR    str[128] = {0};
            WDK_TOAST_T t_toast;
            UINT16  ui2_mlm_warning_key = 0;
            UINT16  ui2_w2s_len;
            UTF16_T* pt_w2s = NULL;
            UINT8   ui1_set_val = 0;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str, item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if (c_strcmp(str,"Off") == 0)
            {
                ui1_set_val = 0;
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_62;
            }
            else if (c_strcmp(str,"On") == 0)
            {
                ui1_set_val = 1;
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_61;
            }
            else
            {
                break;
            }

            if (ui1_val == ui1_set_val) {
                break;
            }

            pt_w2s = MLM_WARNINGS_TEXT(rest_get_mlm_warnings_lang_id(), ui2_mlm_warning_key);
            ui2_w2s_len = (c_uc_w2s_strlen(pt_w2s)+1)*2;
            t_toast.style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(ui2_w2s_len);
            if (t_toast.style.style_4.w2s_str != NULL)
            {
                c_memset((VOID*)t_toast.style.style_4.w2s_str, 0x0, ui2_w2s_len);
                c_memcpy((VOID*)t_toast.style.style_4.w2s_str, (const VOID *)pt_w2s, c_uc_w2s_strlen(pt_w2s)*sizeof(UTF16_T));
                rest_send_msg_to_nav(&t_toast);
            }
            a_cfg_set_tts_switch_status(ui1_set_val);
            a_cfg_update_tts_switch_status();

            rest_event_notify("app/tts/enabled", ((ui1_set_val == 0) ? 0 : 1), "");
            a_registry_set_tts_state((ui1_set_val == 0) ? REG_TTS_STATE_OFF : REG_TTS_STATE_ON);

            menu_pm_repaint();
        }
            break;
        default:
            break;
    }

    return 0;

}

int accessibility_speech_rate(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type = 0;
    UINT8   ui2_val = 0;
    UINT8   ui1_tts_speed = APP_CFG_TTS_SPEED_NORMAL;
    ISO_639_LANG_T  s639_lang;

    INT32           i4_ret = 0;
    UINT16          ui2_g_nav_curr_lang= 0;


    type = get_type(root);
    a_cfg_get_tts_speed(&ui1_tts_speed);

    /*convert UINT16 to UNIT8*/
    if (APP_CFG_TTS_SPEED_SLOW == ui1_tts_speed)           //UI Slow
    {
        ui2_val = 0;
    }
    else if (APP_CFG_TTS_SPEED_NORMAL == ui1_tts_speed)      //UI Normal
    {
        ui2_val = 1;
    }
    else if (APP_CFG_TTS_SPEED_FAST == ui1_tts_speed)      //UI Fast
    {
        ui2_val = 2;
    }
    else
    {
        ui2_val = 0;
    }

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items_en;
            Json::Value items_spa;
            Json::Value items_fre;
            i4_ret = a_cfg_get_gui_lang(s639_lang);

            ui2_g_nav_curr_lang = mlm_nav_s639_to_langidx(s639_lang); // 0-eng, 1-fre, 2-spa
            REST_LOG_I("langidx ui2_g_nav_curr_lang = %d\n\r", ui2_g_nav_curr_lang);

            items_en[0] = "Slow";
            items_en[1] = "Normal";
            items_en[2] = "Fast";

            items_spa[0] = "Lenta";
            items_spa[1] = "Normal";
            items_spa[2] = "Rápida";

            items_fre[0] = "Lente";
            items_fre[1] = "Normale";
            items_fre[2] = "Rapide";
            REST_LOG_I("Enter get\n\r");
            if(ui2_g_nav_curr_lang == 1)//fre
            {
                response["ELEMENTS"] = items_fre;
                response["VALUE"] = items_fre[ui2_val];
            }else if(ui2_g_nav_curr_lang == 2)//spa
            {
                response["ELEMENTS"] = items_spa;
                response["VALUE"] = items_spa[ui2_val];
            }else
             {
                response["ELEMENTS"] = items_en;
                response["VALUE"] = items_en[ui2_val];
             }

            REST_LOG_I("accessibility_speech_rate val:%d\n\r", ui2_val);
        }
            break;
        case argument::RequestType::REQUEST_SET:
        {
            CHAR    str[128] = {0};
            UINT8   ui1_set_val = 0;
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_SPEECH_RATE;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];
            REST_LOG_I("Enter set\n\r");
            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("Enter set,str=%s\n\r",str);

            if(c_strcmp(str,"Slow") == 0||c_strcmp(str,"Lenta")==0 ||c_strcmp(str,"Lente")==0)
            {
                ui1_set_val = APP_CFG_TTS_SPEED_SLOW;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TTS_SLOW;
            }
            else if(c_strcmp(str,"Normal") == 0||c_strcmp(str,"Normale")==0)
            {
                ui1_set_val = APP_CFG_TTS_SPEED_NORMAL;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TTS_NORMAL;
            }
            else if(c_strcmp(str,"Fast") == 0||c_strcmp(str,"Rapide")==0||c_strcmp(str,"Rápida")==0)
            {
                ui1_set_val = APP_CFG_TTS_SPEED_FAST;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TTS_FAST;
            }
            else
            {
                ui1_set_val = APP_CFG_TTS_SPEED_NORMAL;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_TTS_NORMAL;
                break;
            }

            a_cfg_set_tts_speed(ui1_set_val);
            a_cfg_update_tts_speed();

            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
        }
            break;
        default:
            break;
    }

    return 0;

}

static VOID _menu_set_zoom_mode(VOID *p1, VOID *p2, VOID *p3)
{
    INT32  i4_ret = 0;
    UINT32 ui1_set_idx = (UINT32)p1;
    CHAR   s_app_name[16] = {0};
#ifdef VIZIO_FUSION_SUPPORT
    c_wgl_enable_zoom((ui1_set_idx == 0) ? FALSE : TRUE);
#endif
    i4_ret = a_am_get_active_app(s_app_name);
    if (i4_ret == AMR_OK && (c_strcmp(s_app_name, MENU_NAME) == 0))
    {
        i4_ret = menu_pm_repaint();
    }
}

int accessibility_zoom_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    UINT8   ui1_get_idx = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;

            items[0] = "Off";
            items[1] = "On";
            response["ELEMENTS"] = items;

            a_cfg_cust_get_zoom_status(&ui1_get_idx);

            if(ui1_get_idx >= 1)
            {
                ui1_get_idx = 1;
            }
            REST_LOG_I("get idx:%d\n\r", ui1_get_idx);
            response["VALUE"] = items[ui1_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            UINT8   ui1_set_idx = 0;
            CHAR    str[128] = {0};
            WDK_TOAST_T t_toast;
            UTF16_T         w2s_str[512] = {0};

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;
            t_toast.style.style_4.w2s_str = (VOID *)&w2s_str[0];

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                ui1_set_idx  = 0;
                c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_ZOOM_MODE_OFF));
            }
            else if(c_strcmp(str,"On") == 0)
            {
                ui1_set_idx = 1;
                c_uc_w2s_strcpy(w2s_str, MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_ZOOM_MODE_ON));
            }
            else
            {
                REST_LOG_E("Error\n\r");
                break;
            }

            a_cfg_cust_get_zoom_status(&ui1_get_idx);

            if(ui1_get_idx >= 1)
            {
                ui1_get_idx = 1;
            }
            if(ui1_get_idx == ui1_set_idx)
            {
                break;
            }

            a_cfg_cust_set_zoom_mode(ui1_set_idx);
            rest_event_notify("app/zoom/enabled", ui1_set_idx, "");
            menu_request_context_switch(_menu_set_zoom_mode, (VOID *)(UINT32)ui1_set_idx, NULL, NULL);

            //don't show wdk,because acfg will notify zoom compoment.
            //rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

int accessibility_video_description(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    INT32 i4_val = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "On";
			i4_val = a_cfg_custom_get_video_description_status();
            response["ELEMENTS"] = items;
            response["VALUE"] = items[i4_val];
            REST_LOG_I("accessibility_video_description val:%d\n\r", i4_val);
        }
            break;
        case argument::RequestType::REQUEST_SET:
        {
            CHAR    str[128] = {0};
            WDK_TOAST_T t_toast;
            UINT16  ui2_mlm_warning_key = 0;
            UINT16  ui2_w2s_len;
            UTF16_T* pt_w2s = NULL;
            UINT8   ui1_set_val = 0;
            ISO_639_LANG_T	s639_lang;
            UINT16			ui2_tmp_idx = 0;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strcpy(str, item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if (c_strcmp(str,"Off") == 0)
            {
                ui1_set_val = 0;
				ui2_tmp_idx = 0;//english
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_65;
            }
            else if (c_strcmp(str,"On") == 0)
            {
                ui1_set_val = 1;
				ui2_tmp_idx = 2;//spanish
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_64;
            }
            else
            {
                break;
            }

            pt_w2s = MLM_WARNINGS_TEXT(rest_get_mlm_warnings_lang_id(), ui2_mlm_warning_key);
            ui2_w2s_len = (c_uc_w2s_strlen(pt_w2s)+1)*2;
            t_toast.style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(ui2_w2s_len);
            if (t_toast.style.style_4.w2s_str != NULL)
            {
                c_memset((VOID*)t_toast.style.style_4.w2s_str, 0x0, ui2_w2s_len);
                c_memcpy((VOID*)t_toast.style.style_4.w2s_str, (const VOID *)pt_w2s, c_uc_w2s_strlen(pt_w2s)*sizeof(UTF16_T));
                rest_send_msg_to_nav(&t_toast);
            }

            /*to set aud lang*/
            mlm_settings_langidx_to_s639(ui2_tmp_idx, s639_lang);
            a_cfg_set_aud_lang(s639_lang);

            /*set VD ON/OFF*/
            a_cfg_custom_set_video_description_status(ui1_set_val);

            if (ui1_set_val == 0)
                rest_event_notify("app/video_description/enabled", 0, "");
            else
                rest_event_notify("app/video_description/enabled", 1, "");

        }
            break;
        default:
            break;
    }

    return 0;

}

int system_information_tv_information_airplay_version(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            if(_rest_app_check_install_airplay() == FALSE)
            {
                   REST_LOG_I("airplay uninstall\n\r");
                   return 9;
            }
            CHAR    ver_string[1024] ={0};
            a_rest_app_get_info_from_airplay("sdkBuildVersion",(void *)ver_string);
            DBG_LOG_PRINT(("[REST] sdkBuildVersion:%s\n\r",ver_string));
            REST_LOG_I("string: %s\n\r", ver_string);
            string_set_response(response, ver_string);

           REST_LOG_I("string: %s\n\r", ver_string);
           string_set_response(response, ver_string);

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
    REST_LOG_I("end airplay_version\n\r");

    return 0;
}


extern "C" INT16 get_power_on_input_idx_count();
extern "C" UINT16 get_power_on_input_idx(VOID);
extern "C" INT32 set_power_on_input_idx_from_rest_api(UINT16 ui2_idx);
extern "C" VOID get_power_on_mode_text(UINT16 ui2_idx /* in */,    UTF16_T *w2s_str /* out */,  SIZE_T z_len);

static int input_at_power_on(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    
    auto fGetTitleForIndex =[](auto theIndex)
    {
        std::u16string tmpItemName(512, 0); //enough for 256 asian chars.
        get_power_on_mode_text(theIndex, (UTF16_T*)&tmpItemName[0], tmpItemName.size() );
        auto tmpUtf16CharCount = c_uc_w2s_strlen( (UTF16_T*)&tmpItemName[0]);
        tmpItemName.resize( tmpUtf16CharCount );
  
        std::string tmpUtf8ItemName(tmpUtf16CharCount*6, 0); //enough for 256 utf8 chars
  
        c_uc_w2s_to_ps( (const UTF16_T*)&tmpItemName[0], &tmpUtf8ItemName[0], tmpUtf8ItemName.size());
        tmpUtf8ItemName.resize( c_strlen(&tmpUtf8ItemName[0]) );
        return tmpUtf8ItemName;
    };

    auto tmpPowerOnInputndex = get_power_on_input_idx();
    auto tmpEntryCount = get_power_on_input_idx_count();
      
    auto tmpCurrentValue = fGetTitleForIndex(tmpPowerOnInputndex);


    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
           
            Json::Value tmpResponseItems;
            for( auto i = 0; i < tmpEntryCount; ++i)
            {
               auto tmpEntryTitle = fGetTitleForIndex(i);
               tmpResponseItems.append(tmpEntryTitle);
            }

            response["ELEMENTS"] = tmpResponseItems;
            response["VALUE"] = tmpCurrentValue;
            
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            auto tmpMessageNode = root["message"];
            
            if(tmpMessageNode.empty())
            {
               REST_LOG_I("invalid message node in setter");
               rest_event_notify("tv_settings/system/input_at_power_on",  0, tmpCurrentValue.c_str());

               return -1;
            }
            
            auto tmpValueNode = tmpMessageNode["VALUE"];
 
            if(tmpValueNode.empty())
            {
               REST_LOG_I("missing VALUE node in setter");
               rest_event_notify("tv_settings/system/input_at_power_on",  0, tmpCurrentValue.c_str());
               return -1;
            }
            
            auto tmpValue = tmpValueNode.asString();
            
            if(tmpValue == "")
            {
               REST_LOG_I("empty VALUE node in setter");
               rest_event_notify("tv_settings/system/input_at_power_on",  0, tmpCurrentValue.c_str());
               return -1;
            }
            
            
            for( auto i = (UINT16)0; i < tmpEntryCount; ++i)
            {
               auto tmpEntryTitle = fGetTitleForIndex(i);
               
               if(tmpValue == tmpEntryTitle)
               {
                  set_power_on_input_idx_from_rest_api(i);
                  menu_pm_repaint();
                  return 0;
               }
            }
            
            REST_LOG_I("invalid value");        
            break;
        }
        default:
        break;
    }

    return 0;
}



handler tv_settings_system_handler[] = {
    system_information_tv_information_cast_name,
    system_information_tv_information_serial_number,
    system_information_tv_information_model_name,
    system_information_tv_information_version,
    system_information_tv_information_chromium_version,
    system_information_tv_information_scpl_version,
    system_information_tv_information_amazon_version,
    system_information_tv_information_vrr,
    system_information_tv_information_country, //country
    system_information_tv_information_cast_version,
    system_information_tv_information_source_type,
    system_information_tv_information_resolution,
    system_information_tv_information_vertical_frequency,
    system_information_tv_information_hdr,
    system_information_tv_information_audio_type,
    system_information_tv_information_frc_version,
    system_information_tv_information_netflix_esn,
    system_information_tv_information_netflix_esn2,
    system_information_network_information_ssid,
    system_information_network_information_security_type,
    system_information_network_information_ip_address,
    system_information_network_information_gateway,
    system_information_network_information_subnet_mask,
    system_information_network_information_preferred_dns_server,
    system_information_network_information_alternate_dns_server,
    system_information_network_information_download_speed,
    system_information_network_information_wifi_signal_strength,
    system_information_network_information_rssi,
    system_information_network_information_wifi_channel,
    system_information_network_information_rj45_mac_address,
    system_information_network_information_wlan_mac_address,
    system_information_network_information_bt_mac_address,
    system_information_uli_information_esn,
    system_information_uli_information_sv,
    system_information_uli_information_reg,
    system_information_uli_information_netflix_esn_native,
    system_information_uli_information_np,
    system_information_uli_information_uid,
    system_information_uli_information_dev_id,
    system_information_uli_information_prov_id,
    system_information_uli_information_da,
    reset_and_admin_service_reset,
    reset_and_admin_dlm_reset,
    service_check,
    local_time_settings_use_internet_time,
    local_time_settings_date_time,
    local_time_settings_timezone,
    automatic_time,
    local_time_settings_daylight_savings_time,
    local_time_settings_time_format,
    local_time_settings_country,
    menu_language,
    cec_cec_function,
    cec_device_discovery,
    cec_device_discovery_results,
    reset_and_admin_power_indicator,
    reset_and_admin_usb_power,
    reset_and_admin_factory_reset,
    reset_and_admin_vizio_privacy_policy,
    reset_and_admin_smart_interactivity,
    reset_and_admin_store_demo,
    reset_and_admin_advertising_limit_ad_tracking,
    reset_and_admin_advertising_tvad_id_reset,
    reset_and_admin_advertising_ad_replacement,
    system_information_tuner_information_physical_channel,
    system_information_tuner_information_frequency,
    system_information_tuner_information_modulation,
    system_information_tuner_information_status,
    system_information_tuner_information_signal_strength,
    system_information_tuner_information_name,
    country,
    hide_from_input_list,
    hide_input_tv,
    hide_input_comp,
    hide_input_hdmi1,
    hide_input_hdmi2,
    hide_input_hdmi3,
    hide_input_hdmi4,
    energy_saving_mode,
    oled_panel,
    screen_refresher,
    pixel_shift,
    voice_remote,
    power_mode,
    aspect_ratio,
    tv_name,
    reset_and_admin_system_pin,
    system_information_tv_information_series,
    system_information_tv_information_size,
    accessibility_talkback,
    accessibility_speech_rate,
    accessibility_zoom_mode,
    accessibility_video_description,
    system_information_tv_information_audio_type_out,
    system_information_network_information_wifi_module,
    system_information_tv_information_airplay_version,
    input_at_power_on,
};


