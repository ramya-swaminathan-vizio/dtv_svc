#include <iostream>
#include <bits/unique_ptr.h>
#include "state.h"
#include "handler.h"
#include "devices.h"
#include "common.h"
#include "argument.h"
#include "tv_settings/channels.h"


#ifdef __cplusplus
extern "C" {
#define  LVL_ELM_IDX_OFFSET         ((UINT8)  1)
#define OP_VCHIP_MAX_RGN_NUM       ((UINT8)  8)
#define OP_VCHIP_MAX_DIM_NUM       ((UINT8) 255)
#define OP_VCHIP_MAX_LVL_NUM       ((UINT8) 15)

#include "app_util/a_network.h"
#include "app_util/a_bluetooth.h"
#include "app_util/mtktvapi/a_mtktvapi_rating.h"
#include "res/app_util/config/acfg_custom.h"

#include "nav/tuner_setup/tuner_setup_view.h"
#include "res/nav/one_channel_list/ocl.h"

#include "bgm/a_bgm.h"
#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#ifdef APP_BLUETOOTH_SUPPORT
#include "mtk_bt_service_gap_wrapper.h"
#endif


}
#endif

extern int power_status;

struct StateGroupURI {
    std::string index[URI_INDEX_SIZE];
};


StateGroupURI  stateGroupUris[] = {
        /*
        # STATE
        */
        { "device" , "deviceinfo" },
        { "devices" , "name_input" , "cast" },
        { "devices" , "name_input" , "hdmi1" },
        { "devices" , "name_input" , "hdmi2" },
        { "devices" , "name_input" , "hdmi3" },
        { "devices" , "name_input" , "hdmi4" },
        { "devices" , "name_input" , "hdmi5" },
        { "devices" , "name_input" , "comp" },
        { "devices" , "name_input" , "vga" },
        { "audio" , "is_sound_bar_connected" },
        { "acr" , "whatson" },
        { "cec" , "hdmi1" },
        { "cec" , "hdmi2" },
        { "cec" , "hdmi3" },
        { "cec" , "hdmi4" },
        { "cec" , "hdmi5" },
        { "device" , "currentstate" },
        { "device" , "power_mode" },

        { "devices" , "cast" },
        { "devices" , "hdmi1" },
        { "devices" , "hdmi2" },
        { "devices" , "hdmi3" },
        { "devices" , "hdmi4" },
        { "devices" , "hdmi5" },
        { "devices" , "comp" },
        { "devices" , "vga" },
        { "tuner" , "channel_settings" },
        { "tuner" , "all_channel_settings" },
        { "tuner" , "drrt_name" },
        { "tuner" , "drrt_all_settings" },
        { "tuner" , "drrt_settings" },
        { "" },
};

//static Json::Value drrtArray;

#ifdef __cplusplus

extern "C" {
#ifdef A_C4TV_APRON_CAST_NAME
    extern int a_c4tv_apron_get_cast_name(char * ps_cast_name, unsigned int *
pui4_cast_name_len);
#endif
    extern INT32 a_cfg_custom_get_model_name(CHAR *ps_model_name);
};

#endif

static std::string getDeviceName()
{
    char buf[128] = {0};

    unsigned int length = 128;
#ifdef A_C4TV_APRON_CAST_NAME
    a_c4tv_apron_get_cast_name(buf, &length);
#else
    a_cfg_custom_get_tv_name(buf, &length);
#endif

    return std::string(buf);
}

int device_deviceinfo(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = 0;
    CHAR model_name[32] = {0};

    Json::Value value;

    value["CAST_NAME"] = getDeviceName();
    #ifdef APP_ULI_UPG_SUPPORT
            CHAR serial_num[64] = "1234";
            CHAR temp_string[64] = "1234";
            UINT32 ui4_buff_len = 64;
            UINT32  ui4_digs_len = 0;
            c_memset(serial_num, '\0', 64);
            c_memset(temp_string, 0, 64);
            i4_ret = a_uli_get_serial_number((UINT8*)serial_num, &ui4_buff_len);
            LOG_ON_ERR(i4_ret);
            REST_LOG_I("serial_num ESN: %s\n\r", serial_num);
            if (ui4_buff_len < 15)
            {
                c_strncpy(temp_string, serial_num + 2, 2);
                c_strncat(temp_string, serial_num, 2);
                c_strncat(temp_string, serial_num + 6, 2);
                c_strncat(temp_string, serial_num + 4, 2);
                c_strncat(temp_string, serial_num + 8, 5);

                ui4_digs_len = c_strlen(temp_string);
                c_strcat(temp_string, serial_num + ui4_digs_len);
            }
            else
            {
                c_strncpy(temp_string, serial_num + 8, 2);
                c_strncat(temp_string, serial_num, 8);

                ui4_digs_len = c_strlen(temp_string);
                c_strcat(temp_string, serial_num + ui4_digs_len);
            }

    REST_LOG_I("serial_num: %s\n\r", temp_string);
    value["SERIAL"] = std::string(temp_string);
#endif
    i4_ret = a_cfg_custom_get_model_name(model_name);
    LOG_ON_ERR(i4_ret);
    if (c_strlen(model_name) == 0)
    {
        c_strncpy(model_name, "V405-H9", strlen("V405-H9"));
    }

    REST_LOG_I("model_name: %s\n\r", model_name);

    value["MODEL_NAME"] = std::string(model_name);

    value["SETTINGS_ROOT"] = "tv_settings";

    value["API_VERSION"] = "1.0.12_1.0.12.11_01_01";

    // get MAC address
    Json::Value mac;

    char s_rj45_mac[20] = {0};
    CHAR psz_eth[10] = NI_ETHERNET_0;
    a_nw_get_mac_addr_string(psz_eth, s_rj45_mac);
    mac["rj45"] = std::string(s_rj45_mac);

    char s_wlan_mac[20] = {0};
    CHAR psz_wlan[10] = NI_WIRELESS_0;
    a_nw_get_mac_addr_string(psz_wlan, s_wlan_mac);
    mac["wlan"] = std::string(s_wlan_mac);

#ifdef APP_BLUETOOTH_SUPPORT

    BT_LOCAL_DEV local_dev_info;
    c_memset(&local_dev_info, 0, sizeof(BT_LOCAL_DEV));
    if (a_bluetooth_driver_init_done() == TRUE)
    {
        i4_ret =a_mtkapi_bt_gap_get_local_dev_info(&local_dev_info);
        LOG_ON_ERR(i4_ret);
    }
    mac["bt"] = std::string(local_dev_info.bdAddr);
    value["MACS"] =  mac;

#endif

    Json::Value inputs;
    inputs[0] = "cast";
    inputs[1] = "hdmi1";

    if (c_strstr(model_name, "24h") != NULL)
    {
        inputs[2] = "comp";
        inputs[3] = "tuner";
        inputs[4] = "vga";
    }
    else if (c_strstr(model_name, "24f") != NULL)
    {
        inputs[2] = "hdmi2";
        inputs[3] = "comp";
        inputs[4] = "tuner";
    }
    else if (c_strstr(model_name, "32") != NULL
             || c_strstr(model_name, "40") != NULL
             || c_strstr(model_name, "39") != NULL)
    {
        inputs[2] = "hdmi2";
        inputs[3] = "comp";
        inputs[4] = "tuner";
    }
    else if (c_strstr(model_name, "E70") != NULL)
    {
        inputs[2] = "hdmi2";
        inputs[3] = "hdmi3";
        inputs[4] = "hdmi4";
        inputs[5] = "comp";
        inputs[6] = "tuner";
    }
    else
    {
        inputs[2] = "hdmi2";
        inputs[3] = "hdmi3";
        inputs[4] = "comp";
        inputs[5] = "tuner";
    }

    value["INPUTS"] = inputs;

    Json::Value capabilities;

    capabilities["type"] = "tvtuner";
    capabilities["memc"] = 0;
    if (c_strstr(model_name, "h") != NULL)
    {
        capabilities["res"] = "HD";
    }
    else if (c_strstr(model_name, "f") != NULL)
    {
        capabilities["res"] = "FHD";
    }
    else
    {
        capabilities["res"] = "UHD";
    }

    // FALSE: has bt; TRUE: w/t bt
  /*  if (a_bluetooth_driver_init_done() == TRUE) {
        REST_LOG_I("With BT\n\r");
        capabilities["BLE"] = 1;
    } else {
        REST_LOG_I("Without BT\n\r");
        capabilities["BLE"] = 0;
    }*/
    capabilities["BLE"] = 0;

    value["CAPABILITIES"] = capabilities;

    value["YT_DEEPLINK_SUPPORT"] = (bool)TRUE;

    response["VALUE"]=value;

    return 0;
}

int devices_name_input_cast(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return name_input_cast(root, response);
}

int devices_name_input_hdmi1(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return name_input_hdmi1(root, response);
    return 0;
}

int devices_name_input_hdmi2(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return name_input_hdmi2(root, response);
    return 0;
}

int devices_name_input_hdmi3(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return name_input_hdmi3(root, response);
    return 0;
}

int devices_name_input_hdmi4(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return name_input_hdmi4(root, response);
    return 0;
}

int devices_name_input_hdmi5(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return name_input_hdmi5(root, response);
    return 0;
}

int devices_name_input_comp(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return name_input_comp(root, response);
    return 0;
}

int devices_name_input_vga(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return name_input_comp(root, response);
}
int audio_is_sound_bar_connected(Json::Value & root, Json::Value & response) { return 0; }
int acr_whatson(Json::Value & root, Json::Value & response) { return 0; }
int cec_hdmi1(Json::Value & root, Json::Value & response) { return 0; }
int cec_hdmi2(Json::Value & root, Json::Value & response) { return 0; }
int cec_hdmi3(Json::Value & root, Json::Value & response) { return 0; }
int cec_hdmi4(Json::Value & root, Json::Value & response) { return 0; }
int cec_hdmi5(Json::Value & root, Json::Value & response) { return 0; }


static int const OOBE = 0;
static int const STORE_DEMO = 1;

int device_currentstate(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    /* get value from local setting */

    int value = OOBE;

    response["VALUE"]=value;


    return 0;
}

int device_power_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter. power_status=%d\n\r", power_status);
    get_type(root);

    enum POWER_MODE
    {
        ACTIVE_STANDBY = 0,
        ON,
        OFF
    };

    if (a_bgm_is_running() || power_status == 0)
    {
        REST_LOG_I("under bgm\n\r");
        response["VALUE"] = ACTIVE_STANDBY;
    }
    else if(power_status == 1)
    {
        REST_LOG_I("under power on\n\r");
        response["VALUE"] = ON;
    }
    else if(power_status == 2)
    {
        REST_LOG_I("under power off\n\r");
        response["VALUE"] = OFF;
    }

    return 0;
}

int devices_cast(Json::Value & root, Json::Value & response) { return 0; }
int devices_hdmi1(Json::Value & root, Json::Value & response) { return 0; }
int devices_hdmi2(Json::Value & root, Json::Value & response) { return 0; }
int devices_hdmi3(Json::Value & root, Json::Value & response) { return 0; }
int devices_hdmi4(Json::Value & root, Json::Value & response) { return 0; }
int devices_hdmi5(Json::Value & root, Json::Value & response) { return 0; }
int devices_comp(Json::Value & root, Json::Value & response) { return 0; }
int devices_vga(Json::Value & root, Json::Value & response) { return 0; }

int tuner_channel_settings(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    ocl_reinstall();
    
    Json::Value array;
    UINT16 ui2_ch_num = 0;
    ui2_ch_num = ocl_get_ocl_num();
    INT32 i4_ret = OCLR_FAIL;
    INT32 i4_count = 0;
        
    REST_LOG_I("Channel total number:[%d]\n\r", ui2_ch_num);

    if(ui2_ch_num == 0)
    {
        array.resize(0);
    }
    else
    {
        INT32 idx = 0;
        for(idx = 0; idx < ui2_ch_num; idx++)
        {
            Json::Value value;
            CHAR name[64] = {0};
            CHAR num[64] = {0};
            SVL_REC_T     t_svl_rec     = {0};
            OCL_SVL_REC_T t_ocl_svl_rec = {0};

            i4_ret = ocl_get_ocl_svl_by_index(idx, &t_svl_rec, &t_ocl_svl_rec);
            if(OCLR_OK != i4_ret)
            {
                array.resize(0);
                continue;
            }
            nav_set_ch_num_and_name(&t_svl_rec, num, name);
            
            value["SKIPPED"]= ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE)?(0):(1));
            value["LOCKED"] = ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_BLOCKED)?(1):(0));
            value["NAME"] = std::string(name);
            value["CHANNEL"] = std::string(num);
            value["DIGITAL"] = (INT32)((BRDCST_TYPE_ATSC == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)?TRUE:FALSE);

            REST_LOG_I("idx:%d,num:%s,name:%s,b_is_dig:%d,skip:%d.block:%d,i4_count:%d\n\r",idx,num,name,\
                       (BRDCST_TYPE_ATSC == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type?TRUE:FALSE), \
                       ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE)?(0):(1)),\
                       ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_BLOCKED)?(1):(0)),i4_count);
            
            array[i4_count++] = value;
        }
    }
    response["VALUE"] = array;

    return 0;
}

int tuner_all_channel_settings(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    
    Json::Value array;
    UINT16 ui2_ch_num = 0;
    ui2_ch_num = ocl_get_ocl_num();

    REST_LOG_I("Channel total number:[%d]\n\r", ui2_ch_num);

    if(ui2_ch_num == 0)
    {
        array.resize(0);
    }
    else
    {
        INT32 idx = 0;
        for(idx = 0; idx < ui2_ch_num; idx++)
        {
            Json::Value value;
            CHAR name[64] = {0};
            CHAR num[64] = {0};
            SVL_REC_T     t_svl_rec     = {0};
            OCL_SVL_REC_T t_ocl_svl_rec = {0};

            INT32 i4_ret = ocl_get_ocl_svl_by_index(idx, &t_svl_rec, &t_ocl_svl_rec);
            if(OCLR_OK != i4_ret)
            {
                continue;
            }
            nav_set_ch_num_and_name(&t_svl_rec, num, name);

            value["SKIPPED"]= ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE)?(0):(1));
            value["LOCKED"] = ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_BLOCKED)?(1):(0));
            value["NAME"] = std::string(name);
            value["CHANNEL"] = std::string(num);
            value["DIGITAL"] = (INT32)(INT32)((BRDCST_TYPE_ATSC == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type)?TRUE:FALSE);;
            
            REST_LOG_I("idx:%d,num:%s,name:%s,b_is_dig:%d,skip:%d.block:%d,i4_count:%d\n\r",idx,num,name,\
                       (BRDCST_TYPE_ATSC == t_svl_rec.uheader.t_rec_hdr.e_brdcst_type?TRUE:FALSE), \
                       ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_VISIBLE)?(0):(1)),\
                       ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_BLOCKED)?(1):(0)));

            
            array[idx] = value;
        }
    }
    response["VALUE"] = array;
    return 0;
}


int tuner_drrt_name(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    /* Return the DRRT system name as a string.
     * If no DRRT, must return empty string.
     * SmartCast DRRT item will be grayed out when DRRT system name is an empty string.
     */
    response["VALUE"] = std::string("");

    std::string drrtname;

    parental_control_get_drrt_info(NULL, drrtname);
    if (drrtname.length() > 0)
    {
        response["VALUE"] = drrtname;
    }

    return 0;
}

int tuner_drrt_all_settings(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    Json::Value array;
    /* Return the all DRRT dimensions & ratings' combination as a list.
     * All combinations should be in order.
     */

    array.resize(0);

    std::string drrtname;
    parental_control_get_drrt_info(&array, drrtname);

    REST_LOG_I("array size=%d\n", array.size());

    for (unsigned int i = 0; i < array.size(); i++)
    {
        if (0 == i || (i > 0 && c_strcmp(array[i-1]["DIMENSION"].asCString(),array[i]["DIMENSION"].asCString()) != 0))
        {
            REST_LOG_I("Dim=%s\n", array[i]["DIMENSION"].asCString());
        }
        REST_LOG_I("\tValue=%s\n", array[i]["RATING"].asCString());
    }

    response["VALUE"] = array;
    return 0;
}

int tuner_drrt_settings(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    Json::Value array;
    /* Return the all DRRT dimensions & ratings' combination as a list.
     * All combinations should be in order.
     */

    array.resize(0);

    std::string drrtname;
    parental_control_get_drrt_info(&array, drrtname);

    REST_LOG_I("array size=%d\n", array.size());

    for (unsigned int i = 0; i < array.size(); i++)
    {
        if (0 == i || (i > 0 && c_strcmp(array[i-1]["DIMENSION"].asCString(),array[i]["DIMENSION"].asCString()) != 0))
        {
            REST_LOG_I("Dim=%s\n", array[i]["DIMENSION"].asCString());
        }
        REST_LOG_I("\tValue=%s\n", array[i]["RATING"].asCString());
    }

    response["VALUE"] = array;
    return 0;
}

handler state_handler[] = {
    device_deviceinfo,
    devices_name_input_cast,
    devices_name_input_hdmi1,
    devices_name_input_hdmi2,
    devices_name_input_hdmi3,
    devices_name_input_hdmi4,
    devices_name_input_hdmi5,
    devices_name_input_comp,
    devices_name_input_vga,
    audio_is_sound_bar_connected,
    acr_whatson,
    cec_hdmi1,
    cec_hdmi2,
    cec_hdmi3,
    cec_hdmi4,
    cec_hdmi5,
    device_currentstate,
    device_power_mode,
    devices_cast,
    devices_hdmi1,
    devices_hdmi2,
    devices_hdmi3,
    devices_hdmi4,
    devices_hdmi5,
    devices_comp,
    devices_vga,
    tuner_channel_settings,
    tuner_all_channel_settings,
    tuner_drrt_name,
    tuner_drrt_all_settings,
    tuner_drrt_settings,
};


