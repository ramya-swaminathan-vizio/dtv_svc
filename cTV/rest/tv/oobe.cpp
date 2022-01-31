#include <iostream>
#include <unistd.h>
#include <bits/unique_ptr.h>
#include <unistd.h>

#include <sstream>
#include <fstream>
#include <string>

#include "handler.h"
#include "oobe.h"
#include "common.h"
#include "json/writer.h"
#include "devices.h"
#include "argument.h"
#include "picture_ex.h"
#include "app.h"
#include "system.h"
#include "a_jsonrpc.h"


#ifdef __cplusplus
extern "C" {
#include "c_os.h"
#include "x_os.h"

#include "u_common.h"

#include "app_util/a_cfg.h"
#include "wizard_anim/a_wzd.h"
#include "rest_network.h"

#include "nav/revolt_info/a_revolt_info.h"

#include "nav/cec2/nav_cec.h"
#include "c_cecm.h"

#include "nav/retail_mode/a_nav_retail_mode.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"

#include "res/nav/c4tv_apron/c4tv_apron_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "res/app_util/config/acfg_custom.h"

#include "nav/link_mode/link_mode.h"
#include "nav/input_src/a_input_src.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "rest/rest.h"

#include "rest/a_rest_event.h"
#include "nav/ppp/pic_pw_popup.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "rest_system.h"
#include "nav/long_press/long_press.h"

#include "nav/banner2/a_banner.h"
#include "nav/banner2/banner.h"

#include "registry/a_registry.h"

}
#endif

extern INT32 set_picture_mode(const char* set_name);
extern int cmd_binary_update(const char* path);

struct OobeGroupURI {
    std::string index[URI_INDEX_SIZE];
};

OobeGroupURI  oobeGroupURIs[] = {

        /*
        # OOBE
        */

        { "currentstate" },
        { "is_complete" },
        { "" },
};

/*
    'START_OOBE': 0,
    'DEVICE_PAIR': 1,
    'ENTER_CODE': 2,
    'SUCCESS_PAIR': 3,
    'CONNECT_WIFI': 4,
    'UPDATING_SMARTCAST': 5,
    'UPDATE_COMPLETE': 6,
    'ADD_GOOGLE_ACCOUNT': 7,
    'NAME_DISPLAY': 8,
    'NAME_SAVED': 9,
    'ACCEPT_TERMS': 10,
    'REGISTER_DISPLAY': 11,
    'ALL_SET': 12,
    'REFRESH': 13,
    'DOWNLOADING_UPDATE': 14,
    'ERROR': 15,
    'LINK_START': 16,
    'TUNER_SETUP': 17,
    'TUNER_SCAN': 18,
    'TUNER_COMPLETE': 19,
    'IR_REMOTE': 20,
    'STORE_DEMO': 5000
*/

static BOOL interrupt_all_set = FALSE;
static BOOL b_pair_state = FALSE;

namespace {

/*
   We need to find pageindex using state name and vice versa. boost::multi_index would be
   perfect option here, but since we don't have it here - just going std::map.
   For "state name to page index" it will be O(log(n)) string comparisons,
   for "page index to state name" it will be O(N) int comparisons.
 */
const std::map<std::string, WZD_PAGE_INDEX_T> kStateNameToPageIndexMap {
    {"START_OOBE",                WZD_PAGE_INDEX_C4TV_START_OOBE },
    {"DEVICE_PAIR",               WZD_PAGE_INDEX_C4TV_DEVICE_PAIR },
    {"OOBE_DID_START",            WZD_PAGE_INDEX_C4TV_OOBE_DID_START },
    {"MODE",                      WZD_PAGE_INDEX_C4TV_MODE },
    {"ENTER_CODE",                WZD_PAGE_INDEX_C4TV_ENTER_CODE },
    {"SUCCESS_PAIR",              WZD_PAGE_INDEX_C4TV_SUCCESS_PAIR },
    {"CONNECT_WIFI",              WZD_PAGE_INDEX_C4TV_CONNECT_WIFI },
    {"UPDATING_SMARTCAST",        WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST },
    {"UPDATE_COMPLETE",           WZD_PAGE_INDEX_C4TV_UPDATE_COMPLETE },
    {"ADD_GOOGLE_ACCOUNT",        WZD_PAGE_INDEX_C4TV_ADD_GOOGLE_ACCOUNT },
    {"NAME_DISPLAY",              WZD_PAGE_INDEX_C4TV_NAME_DISPLAY },
    {"NAME_SAVED",                WZD_PAGE_INDEX_C4TV_NAME_SAVED },
    {"ACCEPT_TERMS",              WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS },
    {"REGISTER_DISPLAY",          WZD_PAGE_INDEX_C4TV_REGISTER_DISPLAY },
    {"ALL_SET",                   WZD_PAGE_INDEX_C4TV_ALL_SET },
    {"REFRESH",                   WZD_PAGE_INDEX_C4TV_REFRESH },
    {"DOWNLOADING_UPDATE",        WZD_PAGE_INDEX_C4TV_DOWNLOADING_UPDATE },
    {"ERROR",                     WZD_PAGE_INDEX_C4TV_ERROR },
    {"LINK_START",                WZD_PAGE_INDEX_C4TV_LINK_START },
    {"TUNER_SETUP",               WZD_PAGE_INDEX_C4TV_TUNER_SETUP },
    {"TUNER_SCAN",                WZD_PAGE_INDEX_C4TV_TUNER_SCAN },
    {"TUNER_COMPLETE",            WZD_PAGE_INDEX_C4TV_TUNER_COMPLETE },
    {"IR_REMOTE",                 WZD_PAGE_INDEX_C4TV_IR_REMOTE },
    {"STORE_DEMO",                WZD_PAGE_INDEX_C4TV_STORE_DEMO },
    // new pages
    {"LANGUAGE",                           WZD_PAGE_INDEX_C4TV_LANGUAGE },
    {"LOCATION",                           WZD_PAGE_INDEX_C4TV_LOCATION },
    {"CUSTOM_LOCATION",                    WZD_PAGE_INDEX_C4TV_CUSTOM_LOCATION },
    {"SELECT_WIFI",                        WZD_PAGE_INDEX_C4TV_SELECT_WIFI },
    {"BLUETOOTH_REMOTE",                   WZD_PAGE_INDEX_C4TV_BLUETOOTH_REMOTE },
    {"ACCEPT_ACTIVITY_DATA",               WZD_PAGE_INDEX_C4TV_ACCEPT_ACTIVITY_DATA },
    {"ACCEPT_ACTIVITY_DATA_ONETRUST",      WZD_PAGE_INDEX_C4TV_ACCEPT_ACTIVITY_DATA_ONETRUST },
    {"ACCEPT_TERMS_GOOGLE",                WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_GOOGLE },
    {"ACCEPT_TERMS_VIEWING_DATA",          WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_VIEWING_DATA },
    {"ACCEPT_TERMS_VIEWING_DATA_ONETRUST", WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_VIEWING_DATA_ONETRUST },
    {"ACCEPT_TERMS_ONETRUST",              WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_ONETRUST },
    {"VIZIO_HOME",                         WZD_PAGE_INDEX_C4TV_VIZIO_HOME },
};

/**
 * @brief Converts OOBE state name into page index
 * @param [in] state_name the name of the OOBE state as reported by SCPL/OOBE web app
 * @return page index corresponding to state name or WZD_PAGE_INDEX_C4TV_START_OOBE
 *         for unknown state names
 * @see kStateNameToPageIndexMap for conversion map
 */
WZD_PAGE_INDEX_T _oobe_state_name_to_page_index(const char* state_name) {
    WZD_PAGE_INDEX_T page_index = WZD_PAGE_INDEX_C4TV_START_OOBE;

    auto iter = kStateNameToPageIndexMap.find(state_name);
    if (iter != kStateNameToPageIndexMap.end()) {
        page_index = iter->second;
    } else {
        REST_LOG_E("_to_page_index: unknown oobe state name: %s\n", state_name);
    }
    return page_index;
}

/**
 * @brief Converts OOBE page index into state name
 * @param [in] page_index the WZD page index
 * @return state name corresponding to page index or DEVICE_PAIR
 *         if page index is unknown
 * @see kStateNameToPageIndexMap for conversion map
 */
const char * _oobe_page_index_to_state_name(WZD_PAGE_INDEX_T page_index) {
    // keeping as before - for unknown index default to DEVICE_PAIR
    const char* state_name = "DEVICE_PAIR";

    for (const auto& pair : kStateNameToPageIndexMap) {
        if (pair.second == page_index) {
            state_name = pair.first.c_str();
            break;
        }
    }

    return state_name;
}

/**
 * @brief Reads the "VALUE" contents of the root JSON
 * @param [in]  root JSON root object for the payload of oobe/current
 * @param [out] value JSON object corresponding to "VALUE" field
 *
 * @note Because jsoncpp library is build with C++03 (or older standard)
 *       it is impossible write here a function that returns Json::Value -
 *       linking fails with underined reference to Json::Value move
 *       constructor. Because of this I had to use ugly return parameter.
 */
void _get_value_json(const Json::Value& root, Json::Value& value) {
    const Json::Value msg = root["message"];
    value = msg["VALUE"];

    if (value.isString()) {
        // "for historical reasons" contents of VALUE is string, even though
        // it is actually a JSON object.
        const std::string valueString = value.asString();

        Json::Value parsedValue;
        Json::Reader reader;
        if(reader.parse(valueString, parsedValue)) {
            value = parsedValue;
        } else {
            REST_LOG_E("Couldn't parse VALUE: '%s'\n", valueString.c_str());
            value = {};
        }
    } else if (!value.isObject()) {
        REST_LOG_E("Unexpected format of VALUE field\n");
        value = {};
    }
}

} // anonymous namespace

static VOID _oobe_stop_revoke_nfy_interrupt(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    REST_LOG_I("Enter\n\r");
    interrupt_all_set = FALSE;

    ACFG_RETAIL_MODE_T   t_retail_mode = ACFG_RETAIL_MODE_HOME;
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        DBG_LOG_PRINT(("[RTM] re-launch retail mode after oobe is interrupted. FUNC:%s, LN:%d.\n",__FILE__,__LINE__));

        /* change wzd status first */
        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_RETAIL_MODE, WZD_PAGE_INDEX_C4TV_STORE_DEMO));
        rest_event_notify("oobe/currentstate", 0, "STORE_DEMO");

        /* reset retail mode env */
        a_nav_retail_mode_reset_env();

        /* launching retail mode */
        //a_c4tv_apron_launch_app((char*)APP_ID);
        _rest_app_launch_static_app_by_system();
    }
    else
    {
        a_c4tv_apron_resume_cast();
        chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
    }
     if (access("/tmp/browser_ctrl_disable", R_OK) == 0) {
		REST_LOG_I("Enable LMK.\n\r");
		//dolphin modify using func to replace system
		//system("rm -f /tmp/browser_ctrl_disable");
		//system("sync;sync;sync");
		s_rm("/tmp/browser_ctrl_disable");
		s_sync();
	}

}

static VOID _oobe_amp_nfy(VOID)
{
    CECM_CTRL_T             t_ctrl;
    CECM_DEV_T              t_devinfo;
    CECM_PWR_STS_T          e_pwr_sts;
    INT32                   i4_ret = 0;

    c_memset(&t_devinfo, 0, sizeof(CECM_DEV_T));

    t_ctrl.b_sync = TRUE;
    i4_ret = c_cecm_get_dev_info_by_la(nav_cec_get_mw_handle (),CECM_LOG_ADDR_AUD_SYS,&t_ctrl,&t_devinfo);

    if (i4_ret != 0)
    {
        DBG_LOG_PRINT(("%s,%d Routine fail= %d \r\n", __FUNCTION__, __LINE__,i4_ret ));
    }

    if (t_devinfo.b_dev_present != 0)
    {
        i4_ret = c_cecm_give_device_power_status(nav_cec_get_mw_handle (), CECM_LOG_ADDR_AUD_SYS, TRUE, &e_pwr_sts);
        if (i4_ret != 0)
        {
            DBG_LOG_PRINT(("%s,%d Routine fail= %d \r\n", __FUNCTION__, __LINE__,i4_ret ));
        }
        REST_LOG_I("amp_pwr_sts= %d  \r\n", e_pwr_sts);

        if ((e_pwr_sts == CECM_PWR_STS_ON) || (e_pwr_sts == CECM_PWR_STS_STANDBY_TO_ON))
        {
            #ifdef APP_ARC_ONLY
            nav_cec_custom_amp_nfy();
            #endif
        }
        else
        {
            REST_LOG_I("Don't show amp notification when amp was power off right after oobe \r\n");
        }
    }

}



VOID _oobe_stop_revoke_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3)
{
    REST_LOG_I("Enter\n\r");

    ACFG_RETAIL_MODE_T   t_retail_mode = ACFG_RETAIL_MODE_HOME;
    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
    if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
    {
        DBG_LOG_PRINT(("[RTM] reset retail mode after oobe is complete. FUNC:%s, LN:%d.\n",__FILE__,__LINE__));
        a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
        //TODO: reset PQ to Standard
    }

	if (access("/tmp/browser_ctrl_disable", R_OK) == 0) {
		REST_LOG_I("Enable LMK.\n\r");
		//dolphin modify using func to replace system
		//system("rm -f /tmp/browser_ctrl_disable");
		//system("sync;sync;sync");
		s_rm("/tmp/browser_ctrl_disable");
		s_sync();
	}

    // TODO: if user skipped network setup we should also land on HDMI-1 according to OOBE PRD:
    // https://vizioirvine.atlassian.net/wiki/spaces/PM/pages/185429483048/VIZIO+Home+OOBE+MP+PRD, item 11
    if (a_tv_custom_get_tos())
    {
        int nCount = 0;
        DBG_LOG_PRINT(("%s,%d a_c4tv_apron_resume_cast\r\n", __FUNCTION__, __LINE__));
        a_c4tv_apron_resume_cast();

        while (0!=access("/tmp/browser_ctrl_ready", R_OK) && nCount < 100)
        {
            DBG_LOG_PRINT(("%s,%d waiting for conjure ready///nCount=%d\r\n", __FUNCTION__, __LINE__,nCount));
            c_thread_delay(200);
            nCount++;
        }


        REST_LOG_I("Change source to virtual cast\r\n");
        chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_CAST, 0);

        c_thread_delay(200);
        DBG_LOG_PRINT(("%s,%d launch SCH\r\n", __FUNCTION__, __LINE__));
        //_rest_app_switch_input_to_cast(TRUE);
        _rest_app_launch_app_by_keycode(0x2d, 1);
        nav_show_banner_input_source_msg_hdlr();
    }
    else
    {
        REST_LOG_I("Change source to hdmi0\r\n");
        chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
        rest_event_notify_current_input("hdmi1");

        a_amb_pause_app(WZD_NAME);
    }


    _oobe_amp_nfy();
}

static INT32 _chg_inp_src_to_cast(VOID)
{
    UINT8  ui1_index = 0, ui1_src_num = 0;
    ISL_REC_T  t_isl_rec;

    a_isl_get_num_rec(&ui1_src_num);
    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);
        if ( t_isl_rec.t_avc_info.e_video_type == DEV_VTRL_CAST )
        {
            a_nav_change_input_src(TV_WIN_ID_MAIN, t_isl_rec.ui1_id);
            return 0;
        }
    }

    return -1;
}

static void _stop_tuner_scan_if_any() {
    /* if in scanning, need stop it */
    if(nav_is_channel_scan_active())
    {
        REST_LOG_I("Stop oobe scan.\n");
        rest_async_invoke(a_tuner_setup_stop_scan, NULL, 0, TRUE);
        _chg_inp_src_to_cast();
    }
}

int currentstate(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type    = 0;
    INT32   i4_ret  = 0;

    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;
    UINT8   ui1_page_idx  = 0;

    RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));

    ui1_state    = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX  (ui2_status);

    REST_LOG_I("oobe [state= %d] [page= %d]\n\r", (int)ui1_state, (int)ui1_page_idx);

    if ((WZD_PAGE_INDEX_C4TV_ALL_SET != ui1_page_idx) &&
        (WZD_PAGE_INDEX_C4TV_END != ui1_page_idx))
    {
        rest_start_softap_ex();
        if(access("/data/chrome/set_default_name",F_OK)!=0)
        {
            //reset tv name
            rest_set_default_name();
            s_touch("/data/chrome/set_default_name");
            s_sync();
        }
    }

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value m;
            Json::Value state;
            Json::FastWriter writer;

            const std::string current_state = _oobe_page_index_to_state_name((WZD_PAGE_INDEX_T)ui1_page_idx);
            REST_LOG_I("CURRENT STATE: [%d] %s\n", (int)ui1_page_idx, current_state.c_str());

            state["CS"] = current_state;

            // some states had some special handling before refactoring, keeping as it was
            switch (ui1_page_idx)
            {
                case WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST:
                {
                    UINT8   ui1_idx_ir_mode = WZD_OOBE_IR_MODE;
                    a_cfg_cust_get_oobe_ir_mode(&ui1_idx_ir_mode);
                    if(ui1_idx_ir_mode == WZD_OOBE_IR_MODE) {
                        state["IRMode"] = 1;
                        REST_LOG_I("current state is UPDATING_SMARTCAST(get), IR Mode status is WZD_OOBE_IR_MODE.\n\r", __FUNCTION__, __LINE__);
                    } else if(ui1_idx_ir_mode == WZD_OOBE_SC_MODE) {
                        REST_LOG_I("current state is UPDATING_SMARTCAST(get), IR Mode status is WZD_OOBE_SC_MODE.\n\r", __FUNCTION__, __LINE__);
                    } else {
                        REST_LOG_I("current state is UPDATING_SMARTCAST(get), IR Mode status is UNKNOWN.\n\r", __FUNCTION__, __LINE__);
                    }
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_ALL_SET:
                {
                    interrupt_all_set = TRUE;
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_TUNER_SCAN:
                {
                    INT32 percent  = 0;
                    tuner_setup_range_get_val(&percent);
                    if(percent == 100)
                    {
                        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_TUNER_COMPLETE));
                    }
                    break;
                }
                default:
                    break;
            }

            response["VALUE"] = writer.write(state);
            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            Json::Value value;
            _get_value_json(root, value);

            // to avoid exceptions check format beforehand
            if (!value.isObject() ||
                !value["CS"].isString()) {
                REST_LOG_E("Invalid VALUE format\n");
                break;
            }

            const std::string new_state = value["CS"].asString();

            // due to some reasons the state name reported back is different
            // from the one requested
            std::string new_state_to_report = new_state;

            const UINT8 new_index = static_cast<UINT8>(_oobe_state_name_to_page_index(new_state.c_str()));

            // some states had some special handling before refactoring, keeping as it was
            switch (new_index)
            {
                case WZD_PAGE_INDEX_C4TV_SUCCESS_PAIR:
                    b_pair_state = TRUE;
                    a_revolt_info_play_audio_tone();
                    break;

                case WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST:
                {
                    UINT8 ir_mode = WZD_OOBE_SC_MODE;
                    if (value["IRMode"].isString()) {
                        const std::string ir_mode_string = value["IRMode"].asString();
                        if (ir_mode_string == "1") {
                            ir_mode = WZD_OOBE_IR_MODE;
                            new_state_to_report = "UPDATING_SMARTCAST_IR";
                        } else {
                            ir_mode = WZD_OOBE_SC_MODE;
                            new_state_to_report = "UPDATING_SMARTCAST";
                        }
                    }
                    a_cfg_cust_set_oobe_ir_mode(ir_mode);
                    break;
                }

                case WZD_PAGE_INDEX_C4TV_NAME_DISPLAY:
                case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS:
                case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_GOOGLE:
                case WZD_PAGE_INDEX_C4TV_ACCEPT_ACTIVITY_DATA:
                case WZD_PAGE_INDEX_C4TV_ACCEPT_ACTIVITY_DATA_ONETRUST:
                case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_VIEWING_DATA_ONETRUST:
                case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_ONETRUST:
                case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS_VIEWING_DATA:
                case WZD_PAGE_INDEX_C4TV_SINGLE_TERMS:
                    _stop_tuner_scan_if_any();
                    break;

                case WZD_PAGE_INDEX_C4TV_TUNER_SCAN:
                    a_cfg_cust_set_ch_scan_progress(0);  //clean last channel scan progress
                    break;
            }

            // report back
            rest_event_notify("oobe/currentstate", 0, new_state_to_report.c_str());

            // additional legacy logic
            if (new_index == WZD_PAGE_INDEX_C4TV_ALL_SET)
            {
                a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(ui1_state, WZD_PAGE_INDEX_C4TV_ALL_SET));

                /* Clear link mode status */
                a_nav_link_mode_set_mode(NAV_LINK_MODE_INITIAL);
                /*reset flags of hdmi-x/comp if 1st choice*/
                a_cfg_cust_set_ipts_select_state(IPTS_SELECT_NULL);
                break;
            }
            else
            {
                DBG_LOG_PRINT(("Setting new page index: %s (%d)\n",
                          _oobe_page_index_to_state_name((WZD_PAGE_INDEX_T)new_index), new_index));
                a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(ui1_state, new_index));
            }

            /* if current is store demo, restart oobe app */
            if (ui1_state    == WZD_STATE_RESUME_C4TV &&
                ui1_page_idx == WZD_PAGE_INDEX_C4TV_STORE_DEMO &&
                new_index    != WZD_PAGE_INDEX_C4TV_STORE_DEMO)
            {
            #ifdef APP_RETAIL_MODE_SUPPORT
                i4_ret = a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
                if (APP_CFGR_OK != i4_ret)
                {
                    REST_LOG_E("acfg set_retail_mode_setting failed\n\r");
                }
            #endif
                a_wzd_resume_c4tv(ui1_state, new_index);
            }
            break;
        }

        default:
        {
            break;
        }
    }

    return 0;
}
static VOID install_conjure_thread (VOID*    pv_arg)
{
        REST_LOG_I("Enter\n\r");
        cmd_binary_update("/3rd/conjure/conjure.MTK.zip");
}

#define CONFIG_FILE_UPDATE         "/3rd_rw/sc-data/config/sc-config.json"

int is_complete(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    UINT16	ui2_status	  = 0;
    UINT8	ui1_state	  = 0;
    UINT8	ui1_page_idx  = 0;

    RET_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);
    ui1_page_idx = WZD_UTIL_GET_STATUS_IDX(ui2_status);
    REST_LOG_I("oobe [state= %d] [page= %d] WZD_PAGE_INDEX_C4TV_ALL_SET:%d\n\r", (int)ui1_state, (int)ui1_page_idx, WZD_PAGE_INDEX_C4TV_ALL_SET);

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            if ((WZD_STATE_RESUME_C4TV_END == ui1_state) &&
                (WZD_PAGE_INDEX_C4TV_END   == ui1_page_idx))
            {
                val = 1;
            }
            else
            {
                val = 0;
            }

            value_set_response(response, val);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            CHAR    str[128] = {0};
            UINT32  ui4_len = 128;
            UINT32  ui4_ret = -1;

            string_get_string(root, str, ui4_len);
            REST_LOG_I("str: %s\n\r", str);

            if (0 == c_strcmp("1", str))
            {
                /* if it's in OOBE, disalbe LMK */
                REST_LOG_I("Disable low memory killer to avoid chromium is killed in between chromium/airplay installations.\n\r");
                //system("touch /tmp/browser_ctrl_disable");  //dolphin
                //system("sync;sync;sync");
                s_touch("/tmp/browser_ctrl_disable");
                s_sync();

                REST_LOG_I("Stop channel scan if necessary\n\r");

#ifdef NEVER
                //DTV02052065(MVV-1734)
                if (ui1_page_idx == WZD_PAGE_INDEX_C4TV_ALL_SET)
                {
                    //OOBE completed
                    REST_LOG_I("Set picture mode to Calibrated\r\n");
                    a_cfg_custom_set_all_src_pic_mode(ACFG_CUST_PIC_MODE_BRIGHT_ROOM);
                }
                else
                {
                    //Exit OOBE,demo mode
                    REST_LOG_I("Set picture mode to Vivid\r\n");
                    a_cfg_custom_set_all_src_pic_mode(ACFG_CUST_PIC_MODE_VIVID);
                }
#endif /* NEVER */

                if (ui1_page_idx != WZD_PAGE_INDEX_C4TV_TUNER_SCAN) {
                    REST_LOG_I("Channel scan not ongoing\n\r");
                } else {
                    REST_LOG_I("Stop channel scan\n\r");
                    rest_async_invoke(a_tuner_setup_stop_scan, NULL, 0, TRUE);
                }
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_END\n\r");
                a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV_END, WZD_PAGE_INDEX_C4TV_END));
                rest_event_notify("oobe/currentstate", 0, "ALL_SET");
                UINT8 ui1_tts_val = 0;
                a_cfg_get_tts_switch_status(&ui1_tts_val);
                REST_LOG_I("get tts val: %d.\n\r", ui1_tts_val);
                if(ui1_tts_val == 1)//tts on
                {
                    REST_LOG_I("TTS must be disabled at the conclusion of OOBE.\n\r");
                    a_cfg_set_tts_switch_status(0);
                    a_cfg_update_tts_switch_status();

                    a_cfg_get_tts_switch_status(&ui1_tts_val);
                    if (ui1_tts_val == 0)
                    {
                        rest_event_notify("app/tts/enabled", 0, "");
                        a_registry_set_tts_state(REG_TTS_STATE_OFF);
                    }
                }
                else if(ui1_tts_val == 0)
                {
                    REST_LOG_I("tts is already off, do not need to turn it off.\n\r");
                }

                /* Clear link mode status */
                a_nav_link_mode_set_mode(NAV_LINK_MODE_INITIAL);
				/*reset retail mode status :DTV02118508*/
				 a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
				 a_cfg_cust_set_demo_mode_value(0);

               // _json_parse_config_file((char*)CONFIG_FILE_UPDATE, TRUE);
                {
                    //REST_CONFIG_FILE
                    if (access(REST_CONFIG_FILE_UPDATE, F_OK) != -1) {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_UPDATE));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_UPDATE, TRUE);
                    } else if (access(REST_CONFIG_FILE_DEFAULT_DEBUG, F_OK) != -1) {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file existed: %s.\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT_DEBUG));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT_DEBUG, TRUE);
                    } else {
                        DBG_LOG_PRINT(("[REST_AP_API][%s] update file not existed. parse default one: %s\r\n",__FUNCTION__, REST_CONFIG_FILE_DEFAULT));
                        _json_parse_config_file((CHAR*)REST_CONFIG_FILE_DEFAULT, TRUE);
                    }
                }
                _rest_app_create_virtual_inputs();

                ui4_ret = _json_parse_ssdp_udn_file("/data/chrome/.eureka.conf", "/data/ssdp.udn");
                if (ui4_ret == 0)
                {
                    rest_app_restart_dial();
                }

                if(FALSE == a_rest_is_conjure_install())
                {
                    REST_LOG_W("<OOBE> OOBE finish but conjure not installed ,use defaulted in /application\n\n\r");
                }


                REST_LOG_I("After OOBE finished, stop softap.\n\r");
                rest_stop_softap();
                //_rest_app_no_app_notification();

                if (WZD_STATE_RESUME_C4TV == ui1_state && !b_pair_state) {
                    a_ppp_timer_launch(); //If the device is paired,the ppp mode will pop by sc but bot tv
                }
                b_pair_state = FALSE;

		/*when finish or exit OOBE,check TTS status*/
		a_nav_long_press_set_tts_status(TRUE);
                if ((a_retail_mode_is_sec_press_play_pause_key() || a_retail_mode_get_ir_exit_key_state())
                    && interrupt_all_set)
                {
                    a_retail_mode_set_ir_exit_key_state(FALSE);
                    a_wzd_stop_c4tv(_oobe_stop_revoke_nfy_interrupt);
                }
                else
                {
                    a_wzd_stop_c4tv(_oobe_stop_revoke_nfy);
                }
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

UINT8 a_oobe_state_name_to_page_index(const char* state_name) {
    return static_cast<UINT8>(_oobe_state_name_to_page_index(state_name));
}

const char * a_oobe_page_index_to_state_name(UINT8 page_index) {
    return _oobe_page_index_to_state_name(static_cast<WZD_PAGE_INDEX_T>(page_index));
}

handler oobe_handler[] =
{
        currentstate,
        is_complete,
};

