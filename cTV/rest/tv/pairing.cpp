#include <iostream>
#include "handler.h"

#include "common.h"
#include <string.h>
#include "pairing.h"

#ifdef __cplusplus
extern "C" {
#include "wizard_anim/a_wzd.h"
#include "nav/revolt_info/a_revolt_info.h"

#include "res/app_util/icl/a_icl_custom.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "res/nav/c4tv_apron/c4tv_apron_custom.h"
#include "rest/a_rest_api.h"
#include "rest/rest.h"

#include "am/a_am.h"
}
#endif

#define  REST_PAIR_SOFTAP_PIN_TIMER_DURATION           2*60*1000 /* 2 mins according to UI spec 2.4*/

CHAR pair_token[16] = {0};
UTF16_T w2s_string[128]  = {0};

struct PairingGroupURI {
    std::string index[URI_INDEX_SIZE];
};

PairingGroupURI  pairingGroupURIs[] = {

        /*
        # PAIRING
        # pairing" , "start
        # pairing" , "pair
        # pairing" , "unpair
        */

        { "bt" , "getauthtoken" },
        { "bt" , "status" },
        { "bt" , "rssimeter" },
        { "start" },
        { "pair" },
        { "unpair" },
        { "correct_challenge_response" },
        { "cancel" },
        { "bt" , "dev_info" },
        { "" },
};

int bt_getauthtoken(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return 0;
}

int bt_status(Json::Value & root, Json::Value & response) 
{
    REST_LOG_I("Enter\n\r");
    return 0;
}

int bt_rssimeter(Json::Value & root, Json::Value & response) 
{
    REST_LOG_I("Enter\n\r");
    return 0;
}

static VOID _pairing_wait_for_power_on(HANDLE_T h_timer, VOID* pv_tag)
{
    static UINT8 _ui1_timer_count = 0;

    if(_ui1_timer_count >= 10 ||a_am_is_power_on()) //timeout 10s
    {
        if (c_timer_stop(h_timer_toast_nav) == OSR_OK)
        {
            REST_LOG_I("stop h_timer_toast_nav\n\r");
        }
        else
        {
            REST_LOG_E("stop h_timer_toast_nav failed\n\r");
        }

        usleep(500*1000); //dolphin sleep 500 for a better UI behavior

        WDK_TOAST_T t_toast;
        memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

        t_toast.e_toast_style  = WDK_STRING_TOAST;
        t_toast.e_string_style = WDK_STRING_STRING;
        t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

        rest_send_msg_to_nav(&t_toast);
        _ui1_timer_count=0;
    }

    _ui1_timer_count++;
    return;
}

int start(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    CHAR    pin[16] = {0};
    CHAR    str[128] = "PIN code is ";
    UINT32  ui4_len = 16;

    get_type(root);

    UINT8 ui1_power_mode = 0;
    a_icl_custom_get_power_mode(&ui1_power_mode);
    {
        REST_LOG_I("pairing in power off status, wake up tv and launch airplay\r\n");
        //wake up tv if current is QS mode
        c4tv_arpon_wakeup_tv(PCL_WAKE_UP_REASON_CUSTOM_4);

        string_get_string(root, pin, ui4_len);

        REST_LOG_I("pin: %s\n\r", pin);

        memset((VOID*)pair_token, 0, sizeof(pair_token));
        strcpy(pair_token, pin);

        Json::Value value;

        value["CHALLENGE_TYPE"] = 1;
        value["PAIRING_REQ_TOKEN"] = 1000;

        response["VALUE"]=value;

        UINT16  ui2_status    = 0;
        UINT8   ui1_state     = 0;

        RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
        ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

        REST_LOG_I("oobe [state= %d]\n\r", (int)ui1_state);
        if(WZD_STATE_RESUME_C4TV != ui1_state)
        {
            WDK_TOAST_T t_toast;

            strcat(str, pin);
            c_uc_ps_to_w2s((const CHAR*)str, w2s_string, 127);

            REST_LOG_I("str: %s\n\r", str);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;
            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

            REST_LOG_I("Set timeout to be: %d\n\r", REST_PAIR_SOFTAP_PIN_TIMER_DURATION);
            a_revolt_info_set_timeout(REST_PAIR_SOFTAP_PIN_TIMER_DURATION);

            if (ui1_power_mode == 1 && !a_am_is_power_on())
            {
                c_timer_start(h_timer_toast_nav,
                5000,
                X_TIMER_FLAG_REPEAT,
                _pairing_wait_for_power_on,
                NULL);
            }
            else
            {
                rest_send_msg_to_nav(&t_toast);
            }
        }
    }

    return 0;
}

int pair(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    Json::Value value;

    value["AUTH_TOKEN"] = "1111";

    response["VALUE"]=value;
    return 0;
}

int unpair(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return 0;
}

int correct_challenge_response(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    Json::Value value;

    value["CHALLENGE_TYPE"] = 1;
    value["RESPONSE_VALUE"] = "1111";

    response["VALUE"]=value;

    return 0;
}

int cancel(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return 0;
}

int bt_dev_info(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return 0;
}

int stop(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    rest_send_msg_to_revolt_info_hide();
    return 0;
}

handler pairing_handler[] = {
    bt_getauthtoken,
    bt_status,
    bt_rssimeter,
    start,
    pair,
    unpair,
    correct_challenge_response,
    cancel,
    bt_dev_info,
    stop,
};

