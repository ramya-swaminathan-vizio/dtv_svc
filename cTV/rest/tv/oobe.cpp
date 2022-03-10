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

            switch (ui1_page_idx)
            {
                case WZD_PAGE_INDEX_C4TV_START_OOBE:
                {
                    REST_LOG_I("START_OOBE\n\r");
                    state["CS"] = "START_OOBE";
                    response["VALUE"] = writer.write(state);
                    /* Update oobe started state for wzd checking */
                    a_wzd_set_oobe_started();
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_DEVICE_PAIR:
                {
                    REST_LOG_I("DEVICE_PAIR\n\r");
                    state["CS"] = "DEVICE_PAIR";
                    response["VALUE"] = writer.write(state);
                    /* Update oobe started state for wzd checking */
                    a_wzd_set_oobe_started();
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_OOBE_DID_START:
                {
                    REST_LOG_I("OOBE_DID_START\n\r");
                    state["CS"] = "OOBE_DID_START";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_MODE:
                {
                    REST_LOG_I("MODE\n\r");
                    state["CS"] = "MODE";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_ENTER_CODE:
                {
                    REST_LOG_I("ENTER_CODE\n\r");
                    state["CS"] = "ENTER_CODE";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_SUCCESS_PAIR:
                {
                    REST_LOG_I("SUCCESS_PAIR\n\r");
                    state["CS"] = "SUCCESS_PAIR";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_CONNECT_WIFI:
                {
                    REST_LOG_I("CONNECT_WIFI\n\r");
                    state["CS"] = "CONNECT_WIFI";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST:
                {
                    REST_LOG_I("UPDATING_SMARTCAST\n\r");
                    state["CS"] = "UPDATING_SMARTCAST";

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

                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_UPDATE_COMPLETE:
                {
                    REST_LOG_I("UPDATE_COMPLETE\n\r");
                    state["CS"] = "UPDATE_COMPLETE";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_ADD_GOOGLE_ACCOUNT:
                {
                    REST_LOG_I("ADD_GOOGLE_ACCOUNT\n\r");
                    state["CS"] = "ADD_GOOGLE_ACCOUNT";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_NAME_DISPLAY:
                {
                    REST_LOG_I("NAME_DISPLAY\n\r");
                    state["CS"] = "NAME_DISPLAY";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_NAME_SAVED:
                {
                    REST_LOG_I("NAME_SAVED\n\r");
                    state["CS"] = "NAME_SAVED";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS:
                {
                    REST_LOG_I("ACCEPT_TERMS\n\r");
                    state["CS"] = "ACCEPT_TERMS";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_REGISTER_DISPLAY:
                {
                    REST_LOG_I("REGISTER_DISPLAY\n\r");
                    state["CS"] = "REGISTER_DISPLAY";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_ALL_SET:
                {
                    REST_LOG_I("ALL_SET\n\r");
                    state["CS"] = "ALL_SET";
                    response["VALUE"] = writer.write(state);
                    interrupt_all_set = TRUE;
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_REFRESH:
                {
                    REST_LOG_I("REFRESH\n\r");
                    state["CS"] = "REFRESH";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_DOWNLOADING_UPDATE:
                {
                    REST_LOG_I("DOWNLOADING_UPDATE\n\r");
                    state["CS"] = "DOWNLOADING_UPDATE";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_ERROR:
                {
                    REST_LOG_I("ERROR\n\r");
                    state["CS"] = "ERROR";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_LINK_START:
                {
                    REST_LOG_I("LINK_START\n\r");
                    state["CS"] = "LINK_START";
                    response["VALUE"] = writer.write(state);
                    /* Update oobe started state for wzd checking */
                    a_wzd_set_oobe_started();
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_TUNER_SETUP:
                {
                    REST_LOG_I("TUNER_SETUP\n\r");
                    state["CS"] = "TUNER_SETUP";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_TUNER_SCAN:
                {
                    REST_LOG_I("TUNER_SCAN\n\r");
                    state["CS"] = "TUNER_SCAN";
                    response["VALUE"] = writer.write(state);

                    INT32 percent  = 0;
                    tuner_setup_range_get_val(&percent);
                    if(percent == 100)
                    {
                        a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_TUNER_COMPLETE));
                    }
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_TUNER_COMPLETE:
                {
                    REST_LOG_I("TUNER_COMPLETE\n\r");
                    state["CS"] = "TUNER_COMPLETE";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_IR_REMOTE:
                {
                    REST_LOG_I("IR_REMOTE\n\r");
                    state["CS"] = "IR_REMOTE";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                case WZD_PAGE_INDEX_C4TV_STORE_DEMO:
                {
                    REST_LOG_I("Launch store demo\n\r");
                    state["CS"] = "STORE_DEMO";
                    response["VALUE"] = writer.write(state);

                    break;
                }
                case WZD_PAGE_INDEX_C4TV_END:
                {
                    REST_LOG_I("ALL_SET\n\r");
                    state["CS"] = "ALL_SET";
                    response["VALUE"] = writer.write(state);
                    break;
                }
                default:
                {
                    REST_LOG_E("Unknown page index, set to DEVICE_PAIR\n\r");
                    //REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_DEVICE_PAIR\n\r");
                    //a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(WZD_STATE_RESUME_C4TV, WZD_PAGE_INDEX_C4TV_DEVICE_PAIR));
                    state["CS"] = "DEVICE_PAIR";
                    response["VALUE"] = writer.write(state);

                    break;
                }
            }

            break;
        }

        case argument::RequestType::REQUEST_SET:
        {
            Json::Value msg;
            Json::Value value;
            std::string ss;
            CHAR state[128] = {0};

            msg = root["message"];
            value = msg["VALUE"];

            UINT8   ui1_new_index = 0;

            c_strcpy(state, value.asString().c_str());

            if (c_strstr(state, "START_OOBE"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_START_OOBE\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_START_OOBE;
                ss = std::string("START_OOBE");
            }
            else if (c_strstr(state, "DEVICE_PAIR"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_DEVICE_PAIR\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_DEVICE_PAIR;
                ss = std::string("DEVICE_PAIR");
            }
            else if (c_strstr(state, "OOBE_DID_START"))
            {
                REST_LOG_I("OOBE_DID_START\n\r");
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_OOBE_DID_START\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_OOBE_DID_START;
                ss = std::string("OOBE_DID_START");
            }
            else if (c_strstr(state, "ENTER_CODE"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_ENTER_CODE\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_ENTER_CODE;
                ss = std::string("ENTER_CODE");
            }
            else if (c_strstr(state, "SUCCESS_PAIR"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_SUCCESS_PAIR\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_SUCCESS_PAIR;
                ss = std::string("SUCCESS_PAIR");
				b_pair_state = TRUE;
                a_revolt_info_play_audio_tone();
            }
            else if (c_strstr(state, "CONNECT_WIFI"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_CONNECT_WIFI\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_CONNECT_WIFI;
                ss = std::string("CONNECT_WIFI");
            }
            else if (c_strstr(state, "UPDATING_SMARTCAST"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST;

                UINT8   ui1_idx_ir_mode = WZD_OOBE_IR_MODE;
                if(c_strstr(state, "IRMode")) {
                    ui1_idx_ir_mode = WZD_OOBE_IR_MODE;
                    ss = std::string("UPDATING_SMARTCAST_IR");
                } else {
                    ui1_idx_ir_mode = WZD_OOBE_SC_MODE;
                    ss = std::string("UPDATING_SMARTCAST");
                }
                a_cfg_cust_set_oobe_ir_mode(ui1_idx_ir_mode);
            }
            else if (c_strstr(state, "UPDATE_COMPLETE"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_UPDATE_COMPLETE\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_UPDATE_COMPLETE;
                ss = std::string("UPDATE_COMPLETE");
            }
            else if (c_strstr(state, "ADD_GOOGLE_ACCOUNT"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_ADD_GOOGLE_ACCOUNT\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_ADD_GOOGLE_ACCOUNT;
                ss = std::string("ADD_GOOGLE_ACCOUNT");
            }
            else if (c_strstr(state, "NAME_DISPLAY"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_NAME_DISPLAY\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_NAME_DISPLAY;
                ss = std::string("NAME_DISPLAY");

                /* if in scanning, need stop it */
                if(nav_is_channel_scan_active())
                {
                    REST_LOG_I("Stop oobe scan. \n\r");
                    rest_async_invoke(a_tuner_setup_stop_scan, NULL, 0, TRUE);
                    _chg_inp_src_to_cast();
                }
            }
            else if (c_strstr(state, "NAME_SAVED"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_NAME_SAVED\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_NAME_SAVED;
                ss = std::string("NAME_SAVED");
            }
            else if (c_strstr(state, "ACCEPT_TERMS"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_ACCEPT_TERMS;
                ss = std::string("ACCEPT_TERMS");
                /* if in scanning, need stop it */
                if(nav_is_channel_scan_active())
                {
                    REST_LOG_I("Stop oobe scan. \n\r");
                    rest_async_invoke(a_tuner_setup_stop_scan, NULL, 0, TRUE);
                    _chg_inp_src_to_cast();
                }
            }
            else if (c_strstr(state, "REGISTER_DISPLAY"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_REGISTER_DISPLAY\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_REGISTER_DISPLAY;
                ss = std::string("REGISTER_DISPLAY");
            }
            else if (c_strstr(state, "ALL_SET"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_ALL_SET\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_ALL_SET;
                ss = std::string("ALL_SET");
            }
            else if (c_strstr(state, "REFRESH"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_REFRESH\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_REFRESH;
                ss = std::string("REFRESH");
            }
            else if (c_strstr(state, "DOWNLOADING_UPDATE"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_DOWNLOADING_UPDATE\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_DOWNLOADING_UPDATE;
                ss = std::string("DOWNLOADING_UPDATE");
            }
            else if (c_strstr(state, "ERROR"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_ERROR\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_ERROR;
                ss = std::string("ERROR");
            }
            else if (c_strstr(state, "LINK_START"))
            {
                REST_LOG_E("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_LINK_START\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_LINK_START;
                ss = std::string("LINK_START");
            }
            else if (c_strstr(state, "TUNER_SETUP"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_TUNER_SETUP\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_TUNER_SETUP;
                ss = std::string("TUNER_SETUP");
            }
            else if (c_strstr(state, "TUNER_SCAN"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_TUNER_SCAN\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_TUNER_SCAN;
                ss = std::string("TUNER_SCAN");
                a_cfg_cust_set_ch_scan_progress(0);  //clean last channel scan progress
            }
            else if (c_strstr(state, "TUNER_COMPLETE"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_TUNER_COMPLETE\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_TUNER_COMPLETE;
                ss = std::string("TUNER_COMPLETE");
            }
            else if (c_strstr(state, "IR_REMOTE"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_IR_REMOTE\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_IR_REMOTE;
                ss = std::string("IR_REMOTE");
            }
            else if (c_strstr(state, "STORE_DEMO"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_STORE_DEMO\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_STORE_DEMO;
                ss = std::string("STORE_DEMO");
            }
            else if (c_strstr(state, "MODE"))
            {
                REST_LOG_I("a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_MODE\n\r");
                ui1_new_index = WZD_PAGE_INDEX_C4TV_MODE;
                ss = std::string("MODE");
            }
            else
            {
                REST_LOG_E("Unknown status, state from oobe = [%s]; a_cfg_set_wzd_status, WZD_PAGE_INDEX_C4TV_START_OOBE\n\r", state);
                ui1_new_index = WZD_PAGE_INDEX_C4TV_START_OOBE;
                ss = std::string("START_OOBE");
            }

            rest_event_notify("oobe/currentstate", 0, ss.c_str());

            if (ui1_new_index == WZD_PAGE_INDEX_C4TV_ALL_SET)
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
                a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(ui1_state, ui1_new_index));
            }

            /* if current is store demo, restart oobe app */
            if (ui1_state    == WZD_STATE_RESUME_C4TV &&
                ui1_page_idx == WZD_PAGE_INDEX_C4TV_STORE_DEMO &&
                ui1_new_index != WZD_PAGE_INDEX_C4TV_STORE_DEMO)
            {
            #ifdef APP_RETAIL_MODE_SUPPORT
                i4_ret = a_cfg_custom_set_retail_mode_setting(ACFG_RETAIL_MODE_HOME);
                if (APP_CFGR_OK != i4_ret)
                {
                    REST_LOG_E("acfg set_retail_mode_setting failed\n\r");
                }
            #endif
                a_wzd_resume_c4tv(ui1_state, ui1_new_index);
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

handler oobe_handler[] =
{
        currentstate,
        is_complete,
};

