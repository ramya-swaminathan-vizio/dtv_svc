#include <iostream>
#include <handler.h>
#include "channels.h"
#include "common.h"
#include "argument.h"
#include <string.h>

#ifdef __cplusplus
extern "C" {
#include "u_scc.h"
#include "u_rrctx.h"
#include "x_os.h"
#include "nav/nav_common.h"
#include "nav/nav_comp_id.h"
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "app_util/a_icl.h"
#include "app_util/icl/a_icl_custom.h"
#include "nav/tuner_setup/tuner_setup_view.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "wizard_anim/a_wzd.h"
#include "res/nav/one_channel_list/ocl.h"
#include "nav/pwd_dlg/pwd_dlg.h"
#include "app_util/mtktvapi/a_mtktvapi_rating.h"
#include "rest/rest.h"
#include "app_util/config/acfg_ch_lst.h"
#include "menu2/menu_common/menu_common.h"
#include "am/a_am.h"


#define LVL_ELM_IDX_OFFSET         ((UINT8)  1)
#define OP_VCHIP_MAX_RGN_NUM       ((UINT8)  8)
#define OP_VCHIP_MAX_DIM_NUM       ((UINT8) 255)
#define OP_VCHIP_MAX_LVL_NUM       ((UINT8) 15)

}
#endif

#define     COL_A   0
#define     COL_FV  1
#define     COL_D   2
#define     COL_L   3
#define     COL_S   4
#define     COL_V   5

#define     ROW_Y   0
#define     ROW_Y7  1
#define     ROW_G   2
#define     ROW_PG  3
#define     ROW_14  4
#define     ROW_MA  5

static HANDLE_T h_rrctx_rrt     = NULL_HANDLE;
static BOOL     b_rrt_dirty     = FALSE;
Json::Value drrtArray;
static std::string drrtName;

TvSettingsGroupURI tvSettingsChannelsUri[] = {
	/*
	# CHANNELS
	*/
	
	{"auto_channel_scan"},
	{"analog"},
	{"digital"},
	{"percent_complete"},
	{"skip_channel"},
	{"analog_audio"},
	{"digital_language"},
	{"parental_controls"},
	{"parental_controls" , "locks"},
	{"parental_controls" , "channel_locks"},
	{"parental_controls" , "usa_tv"},
	{"parental_controls" , "usa_tv" , "tv_y"},
	{"parental_controls" , "usa_tv" , "tv_y" , "all"},
	{"parental_controls" , "usa_tv" , "tv_y7"},
	{"parental_controls" , "usa_tv" , "tv_y7" , "all"},
	{"parental_controls" , "usa_tv" , "tv_y7" , "fv"},
	{"parental_controls" , "usa_tv" , "tv_g"},
	{"parental_controls" , "usa_tv" , "tv_g" , "all"},
	{"parental_controls" , "usa_tv" , "tv_pg"},
	{"parental_controls" , "usa_tv" , "tv_pg" , "all"},
	{"parental_controls" , "usa_tv" , "tv_pg" , "d"},
	{"parental_controls" , "usa_tv" , "tv_pg" , "s"},
	{"parental_controls" , "usa_tv" , "tv_pg" , "l"},
	{"parental_controls" , "usa_tv" , "tv_pg" , "v"},
	{"parental_controls" , "usa_tv" , "tv_14"},
	{"parental_controls" , "usa_tv" , "tv_14" , "all"},
	{"parental_controls" , "usa_tv" , "tv_14" , "d"},
	{"parental_controls" , "usa_tv" , "tv_14" , "s"},
	{"parental_controls" , "usa_tv" , "tv_14" , "l"},
	{"parental_controls" , "usa_tv" , "tv_14" , "v"},
	{"parental_controls" , "usa_tv" , "tv_ma"},
	{"parental_controls" , "usa_tv" , "tv_ma" , "all"},
	{"parental_controls" , "usa_tv" , "tv_ma" , "s"},
	{"parental_controls" , "usa_tv" , "tv_ma" , "l"},
	{"parental_controls" , "usa_tv" , "tv_ma" , "v"},
	{"parental_controls" , "usa_movie"},
	{"parental_controls" , "usa_movie" , "all"},
	{"parental_controls" , "usa_movie" , "g"},
	{"parental_controls" , "usa_movie" , "pg"},
	{"parental_controls" , "usa_movie" , "pg_13"},
	{"parental_controls" , "usa_movie" , "r"},
	{"parental_controls" , "usa_movie" , "nc_17"},
	{"parental_controls" , "canadian_english"},
	{"parental_controls" , "canadian_english" , "c"},
	{"parental_controls" , "canadian_english" , "c_plus"},
	{"parental_controls" , "canadian_english" , "g"},
	{"parental_controls" , "canadian_english" , "pg"},
	{"parental_controls" , "canadian_english" , "14_plus"},
	{"parental_controls" , "canadian_english" , "18_plus"},
	{"parental_controls" , "canadian_french"},
	{"parental_controls" , "canadian_french" , "g"},
	{"parental_controls" , "canadian_french" , "8_ans_plus"},
	{"parental_controls" , "canadian_french" , "13_ans_plus"},
	{"parental_controls" , "canadian_french" , "16_ans_plus"},
	{"parental_controls" , "canadian_french" , "18_ans_plus"},
	{"parental_controls" , "drrt"},
	{"parental_controls" , "drrt" , "*"},//parental_controls_drrt_dimension_M
    {"parental_controls" , "drrt" , "*" , "*"},//parental_controls_drrt_dimension_M_ratingN
	{"parental_controls" , "block_unrated_shows"},
	{"parental_controls" , "reset"},
	{"current_channel"},
    {"skip_channel" , "*"}, //skip_channel_channel_N
    {"skip_channel" , "*" , "name"},//skip_channel_channel_N_name
    {"skip_channel" , "*" , "state"},//skip_channel_channel_N_state
    {"parental_controls" , "channel_locks" ,  "*"},//parental_controls_channel_locks_channel_N
    {"parental_controls" , "channel_locks" , "*" , "name"},//parental_controls_channel_locks_channel_N_name
    {"parental_controls" , "channel_locks" , "*" , "state"},//parental_controls_channel_locks_channel_N_state
    {"cancel_channel_scan"},
    { "" },
};


static INT32 _channel_get_svl_handle_by_id(UINT16 ui2_svl_id, HANDLE_T* ph_svl)
{
    extern INT32 nav_get_svl_handle_by_id(
                        UINT16                      ui2_svl_id,
                        HANDLE_T*                   ph_svl
                        );
    return nav_get_svl_handle_by_id(ui2_svl_id, ph_svl);
}

static VOID _rest_send_msg_to_tuner_setup_handler(VOID*    pv_tag1,
                                          VOID*    pv_tag2,
                                          VOID*    pv_tag3)
{
    REST_LOG_I("Enter\n\r");

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TUNER_SETUP),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              pv_tag1);

}

int auto_channel_scan(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    
    //get current active app,exit menu if need,then do nav_scan
    CHAR            s_active_app[32] = {0}; 
    if (0 == a_am_get_active_app(s_active_app) &&
        0 == c_strcmp(s_active_app, "menu"))
    {
        a_amb_pause_app(s_active_app);
        DBG_LOG_PRINT(("current active app is menu, exit it\r\n"));
    }

    a_tuner_setup_view_change_source_to_tv();
    a_nav_tuner_setup_set_scan_new_channel(FALSE);
    nav_request_context_switch(_rest_send_msg_to_tuner_setup_handler,
                               NULL,
                               NULL,
                               NULL);

    return 0;
}

int cancel_channel_scan(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    rest_async_invoke(a_tuner_setup_stop_scan, NULL, 0, TRUE);
    return 0;
}

int analog(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
   
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            tuner_setup_scan_analog_get_val(&val);            
            value_set_response(response, val);
            REST_LOG_I("analog num:%d\n\r", val);
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

int digital(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            tuner_setup_scan_digital_get_val(&val);           
            value_set_response(response, val);
            REST_LOG_I("digital num:%d\n\r", val);
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

int percent_complete(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            tuner_setup_range_get_val(&val);            
            value_set_response(response, val);
            REST_LOG_I("percent:%d\n\r", val);
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

int skip_channel(Json::Value & root, Json::Value & response){return 0;}

int find_new_channel(Json::Value & root, Json::Value & response)
{   
    REST_LOG_I("Enter\n\r");
    
    //get current active app,exit menu if need,then do nav_scan
    CHAR            s_active_app[32] = {0}; 
    if (0 == a_am_get_active_app(s_active_app) &&
        0 == c_strcmp(s_active_app, "menu"))
    {
        a_amb_pause_app(s_active_app);
        DBG_LOG_PRINT(("current active app is menu, exit it\r\n"));
    }
    
    a_tuner_setup_view_change_source_to_tv();
    a_nav_tuner_setup_set_scan_new_channel(TRUE);
    nav_request_context_switch(_rest_send_msg_to_tuner_setup_handler,
                               NULL,
                               NULL,
                               NULL);

    
    return 0;
}


static UINT16 _analog_audio_get_aud_mts_idx(VOID)
{
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS);
    INT16           i2_val = (INT16)SCC_AUD_MTS_STEREO;
    SCC_AUD_MTS_T   e_mts;
    UINT16          ui2_idx = 0;

    a_cfg_av_get(ui2_id, &i2_val);

    e_mts = (SCC_AUD_MTS_T)i2_val;

    switch(e_mts)
    {
    case SCC_AUD_MTS_MONO:
        ui2_idx = 2;
        break;
    case SCC_AUD_MTS_SUB_LANG:
        ui2_idx = 1;
        break;
    case SCC_AUD_MTS_STEREO:
        ui2_idx = 0;
        break;
    default:
        ui2_idx = 0;
        break;
    }

    return (UINT16)ui2_idx;
}

static VOID _analog_audio_set_aud_mts_idx(UINT16 ui2_idx)
{
    UINT16          ui2_id  = CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_MTS);
    SCC_AUD_MTS_T   e_mts;

    switch(ui2_idx)
    {
    case 0: /* STEREO */
        e_mts = SCC_AUD_MTS_STEREO;
        break;
    case 1: /* SAP */
        e_mts = SCC_AUD_MTS_SUB_LANG;
        break;
    case 2: /* MONO */
        e_mts = SCC_AUD_MTS_MONO;
        break;
    default:
        e_mts = SCC_AUD_MTS_STEREO;
        break;
    }

    a_cfg_av_set(ui2_id, (INT16)e_mts);
    a_cfg_av_update(ui2_id);
}

int analog_audio(Json::Value & root, Json::Value & response)
{   
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    UINT16  val = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;
    
    Json::Value audio;
    audio[0]="Stereo";
    audio[1]="SAP";
    audio[2]="Mono";
    response["ELEMENTS"]=audio;
    response["VALUE"]=audio[0];

    type = get_type(root);
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            val = _analog_audio_get_aud_mts_idx();
            REST_LOG_I("analog audio:%d\n\r", val);
            response["VALUE"]=audio[val];           
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {   
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_ANALOG_AUDIO;
            
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            if(c_strcmp(str,"Stereo") == 0)
            {
                val = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ANALOG_AUDIO_STEREO;
            }
            else if(c_strcmp(str,"SAP") == 0)
            {
                val = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ANALOG_AUDIO_SAP;
            }
            else if(c_strcmp(str,"Mono") == 0)
            {
                val = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ANALOG_AUDIO_MONO;
            }
            _analog_audio_set_aud_mts_idx(val);           

            rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }
    
    return 0;
}

static UINT16 _digital_language_get_lang_idx(VOID)
{
    INT32   i4_ret;
    ISO_639_LANG_T s639_lang = {0};
    UINT16 ui2_idx = 0;
    UINT16 ui2_tmp_idx = 0;

    i4_ret = a_cfg_get_aud_lang(s639_lang);
    if(i4_ret != APP_CFGR_OK)
    {
        return 0;
    }

    ui2_tmp_idx = mlm_settings_s639_to_langidx(s639_lang);
    
    switch (ui2_tmp_idx)
    {
        case 0: 
            /* English */
            ui2_idx = 0;
            break;
        case 1: 
            /* Spanish */
            ui2_idx = 2;
            break;
        case 2: 
            /* French */
            ui2_idx = 1;
            break;
        default:
            ui2_idx = 0;
            break;            
    }

    return ui2_idx;
}


static VOID _digital_language_set_lang_idx(UINT16 ui2_idx)
{
    ISO_639_LANG_T  s639_lang;
    UINT16          ui2_tmp_idx = 0;

    switch (ui2_idx)
    {
        case 0: 
            /* English */
            ui2_tmp_idx = 0;
            break;
        case 1: 
            /* Spanish */
            ui2_tmp_idx = 2;
            break;
        case 2: 
            /* French */
            ui2_tmp_idx = 1;
            break;
        default:
            ui2_tmp_idx = 0;
            break;            
    }

    mlm_settings_langidx_to_s639(ui2_tmp_idx, s639_lang);

    a_cfg_set_aud_lang(s639_lang);

	a_cfg_custom_set_aud_lang_vid_des(ui2_tmp_idx);//set VD
}

int digital_language(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    UINT16  val = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    Json::Value language;
    language[0]="English";
    language[1]="Spanish/Video Description";
    language[2]="French";
    response["ELEMENTS"]=language;
    response["VALUE"]=language[0];

    type = get_type(root);
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("GET\n\r")
            val = _digital_language_get_lang_idx();
            REST_LOG_I("digital language :%d\n\r", val);
            response["VALUE"]=language[val];        
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {   
            REST_LOG_I("SET\n\r")
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_DIGITAL_LANG;
            
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str, item1.asString().c_str());
            REST_LOG_I("digital language :%s\n\r", str);
            if(c_strcmp(str,"English") == 0)
            {
                val = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CH_DIGITAL_LANG_ENG;
            }
            else if(c_strcmp(str,"Spanish/Video Description") == 0)
            {
                val = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_MENU_LANG_ESL;
            }
            else if(c_strcmp(str,"French") == 0)
            {
                val = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_MENU_LANG_FRA;
            }
            
            REST_LOG_I("digital language id:%d\n\r", val);
            
            _digital_language_set_lang_idx(val);           

            rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls(Json::Value & root, Json::Value & response){return 0;}

static VOID _op_vchip_nfy_fct(HANDLE_T          h_nfy,
                              VOID*             pv_nfy_tag,
                              UINT32            ui4_reason)
{
    if (h_rrctx_rrt != NULL_HANDLE)
    {   /* The rrt handle is already opened. */
        if (h_nfy != h_rrctx_rrt)
        {
            REST_LOG_I("[REST] Invalid notification handle\n\r");
        }

        REST_LOG_I("[REST] RRCTX Notification: Reason = [%d], Handle = [%d]\n\r", ui4_reason, h_nfy);

        switch (ui4_reason)
        {
        case RRCTX_REASON_UNKNOWN:
            break;
        case RRCTX_REASON_RATE_ENABLE:
            break;
        case RRCTX_REASON_RATE_DISABLE:
            break;
        case RRCTX_REASON_RATE_UPDATED:
            b_rrt_dirty = TRUE;
            break;
        case RRCTX_REASON_RATE_AVAIL:
            b_rrt_dirty = TRUE;
            break;
        case RRCTX_REASON_RATE_UNAVAIL:
            b_rrt_dirty = TRUE;
            break;
        case RRCTX_REASON_HANDLE_CLOSED:
            break;
        default:
            break;
        }
    }
    else
    {
        REST_LOG_I("[REST] This situation should not happen. NULL RRT handle when receving the notification.\n\r");
    }

    return;
}

int parental_control_get_drrt_info(Json::Value *array, std::string &drrtname)
{
    REST_LOG_I("Enter\n\r");
    REST_LOG_I("drrtArray size=%d\n",drrtArray.size());

    if (drrtArray.size() > 0)
    {
        if (array != NULL)
        {
            for (unsigned int i = 0; i < drrtArray.size(); i++)
            {
                (*array)[i] = drrtArray[i];
            }
            REST_LOG_I("array size=%d\n",(*array).size());
        }

        drrtname = drrtName;
    }

    return 0;
}

static int _parental_control_get_drrt_name(void)
{
    REST_LOG_I("Enter\n\r");

    INT32                   i4_ret = 0;
    Open_Vchip_Key_Param_T  t_rrt_key_param;
    Open_Vchip_Table_Data_T t_rrt_data;

    /* Return the DRRT system name as a string.
     * If no DRRT, must return empty string.
     * SmartCast DRRT item will be grayed out when DRRT system name is an empty string.
     */

    c_memset(&t_rrt_key_param, 0, sizeof(t_rrt_key_param));
    c_memset(&t_rrt_data, 0, sizeof(t_rrt_data));

    t_rrt_key_param.e_open_vchip_data_type = OPEN_VCHIP_KEY_TYPE_RGN_NUM;
    i4_ret = a_mtktvapi_rating_get_op_vchip_info(&t_rrt_key_param, &t_rrt_data);
    if (MTKTVAPIR_OK == i4_ret
        && t_rrt_data.u_data.ui1_rgn_num > 0)
    {
        t_rrt_key_param.e_open_vchip_data_type = OPEN_VCHIP_KEY_TYPE_RGN_TEXT;
        t_rrt_key_param.ui1_rgn_idx = 0;
        i4_ret =  a_mtktvapi_rating_get_op_vchip_info(&t_rrt_key_param, &t_rrt_data);
        if (MTKTVAPIR_OK == i4_ret)
        {
            drrtName = std::string(t_rrt_data.u_data.w2s_rgn_text);
        }
    }

    return 0;
}

static int _parental_control_update_drrt_info(void)
{
    REST_LOG_I("Enter\n\r");

    INT32                   i4_ret = 0;
    UINT16                  ui2_array_idx = 0;
    UINT16                  ui2_dim_num = 0;
    UINT16                  ui2_dim_idx = 0;
    UINT16                  ui2_lvl_num = 0;
    UINT16                  ui2_lvl_idx = 0;
    CHAR                    w2s_dim_text[OPEN_VCHIP_MAX_DIM_TEXT_LEN] ={0};
    Open_Vchip_Key_Param_T  t_rrt_key_param;
    Open_Vchip_Table_Data_T t_rrt_data;

    Json::Value tmpArray;
    Json::Value value;

    /* Return the all DRRT dimensions & ratings' combination as a list.
     * All combinations should be in order.
     */
    
    tmpArray.resize(0);

    do {
        _parental_control_get_drrt_name();
        
        c_memset(&t_rrt_key_param, 0, sizeof(t_rrt_key_param));
        c_memset(&t_rrt_data, 0, sizeof(t_rrt_data));

        t_rrt_key_param.e_open_vchip_data_type = OPEN_VCHIP_KEY_TYPE_RGN_NUM;
        i4_ret = a_mtktvapi_rating_get_op_vchip_info(&t_rrt_key_param, &t_rrt_data);
        if (i4_ret != MTKTVAPIR_OK
            || 0 == t_rrt_data.u_data.ui1_rgn_num)
        {
            REST_LOG_I("Not have DRRT.\n");
            break;
        }

        t_rrt_key_param.e_open_vchip_data_type = OPEN_VCHIP_KEY_TYPE_DIM_NUM;
        t_rrt_key_param.ui1_rgn_idx = 0;

        i4_ret = a_mtktvapi_rating_get_op_vchip_info(&t_rrt_key_param, &t_rrt_data);
        if (i4_ret != MTKTVAPIR_OK || 0 == t_rrt_data.u_data.ui1_dim_num)
        {
            REST_LOG_I("Not have Dimension.\n");
            break;
        }

        REST_LOG_I("Dim num is %d .\n", t_rrt_data.u_data.ui1_dim_num);

        ui2_dim_num = (t_rrt_data.u_data.ui1_dim_num > OP_VCHIP_MAX_DIM_NUM) ? \
                        OP_VCHIP_MAX_DIM_NUM : t_rrt_data.u_data.ui1_dim_num;

        for (ui2_dim_idx = 0; ui2_dim_idx < ui2_dim_num; ui2_dim_idx++)
        {
            t_rrt_key_param.e_open_vchip_data_type = OPEN_VCHIP_KEY_TYPE_DIM_TEXT;
            t_rrt_key_param.ui1_rgn_idx = 0;
            t_rrt_key_param.ui1_dim_idx = ui2_dim_idx;

            i4_ret = a_mtktvapi_rating_get_op_vchip_info(&t_rrt_key_param, &t_rrt_data);
            if (MTKTVAPIR_OK == i4_ret)
            {
                c_memset(w2s_dim_text, 0, sizeof(w2s_dim_text));
                c_strncpy(w2s_dim_text, t_rrt_data.u_data.w2s_dim_text, OPEN_VCHIP_MAX_DIM_TEXT_LEN-1);

                t_rrt_key_param.e_open_vchip_data_type = OPEN_VCHIP_KEY_TYPE_LVL_NUM;

                i4_ret = a_mtktvapi_rating_get_op_vchip_info(&t_rrt_key_param, &t_rrt_data);
                if (MTKTVAPIR_OK == i4_ret && t_rrt_data.u_data.ui1_lvl_num > 0)
                {
                    ui2_lvl_num = t_rrt_data.u_data.ui1_lvl_num;

                    REST_LOG_I("Level num is %d in dim(%d)[%s].\n",ui2_lvl_num, ui2_dim_idx, w2s_dim_text);

                    ui2_lvl_num = (ui2_lvl_num > OP_VCHIP_MAX_LVL_NUM) ? OP_VCHIP_MAX_LVL_NUM : ui2_lvl_num;

                    for (ui2_lvl_idx = LVL_ELM_IDX_OFFSET; ui2_lvl_idx < ui2_lvl_num+1; ui2_lvl_idx++)
                    {
                        t_rrt_key_param.e_open_vchip_data_type = OPEN_VCHIP_KEY_TYPE_LVL_ABBR;
                        t_rrt_key_param.ui1_lvl_idx = ui2_lvl_idx;

                        i4_ret = a_mtktvapi_rating_get_op_vchip_info(&t_rrt_key_param, &t_rrt_data);
                        if (MTKTVAPIR_OK == i4_ret)
                        {
                            REST_LOG_I("Level Text is[%s] in dim(%d)[%s].\n", t_rrt_data.u_data.w2s_lvl_abbr_text, ui2_lvl_num, w2s_dim_text);

                            if (t_rrt_data.u_data.w2s_lvl_abbr_text[0] == '\0')
                            {   /* NULL String */
                                c_strncpy(t_rrt_data.u_data.w2s_lvl_abbr_text, "(No Text.)", OPEN_VCHIP_MAX_LVL_ABBR_TEXT_LEN-1);
                            }

                            value["DIMENSION"]= std::string(w2s_dim_text);
                            value["RATING"] = std::string(t_rrt_data.u_data.w2s_lvl_abbr_text);
                            tmpArray[ui2_array_idx++] = value;
                        }
                        else
                        {
                            REST_LOG_I("Not have Level text of lvl(%d) dim(%d).\n",ui2_lvl_idx, ui2_dim_idx);
                        }
                    }
                }
                else
                {
                    REST_LOG_I("Not have Level of dim(%d).\n", ui2_dim_idx);
                }
            }
            else
            {
                REST_LOG_I("Not have Dimension.\n");
            }
        }
    } while(0);

    REST_LOG_I("ui2_array_idx=%d\n\n",ui2_array_idx);
    if (ui2_array_idx > 0)
    {
        for (int i=0; i<ui2_array_idx;i++)
        {
            drrtArray[i] = tmpArray[i];
        }
        a_tuner_setup_url_put_drrt_changed();
    }

    return 0;
}

VOID _channels_update_drrt (VOID*  pv_arg)
{
    _parental_control_update_drrt_info();

    if (b_rrt_dirty)
    {
        b_rrt_dirty = FALSE;
    }
}

static VOID _parental_controls_drrt_changed(VOID)
{
static UINT32   ui4_last_time = 0;
static HANDLE_T h_thread = NULL_HANDLE;
    
    INT32       i4_ret = 0;
    UINT32      ui4_cur_time = 0;
    
    UINT16      ui2_svl_id = 0;
    CHAR*       ps_tuner_name;

    if (NULL_HANDLE == h_rrctx_rrt)
    {
        a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_tuner_name);
        c_rrctx_open_rating(RRCTX_RATING_TYPE_RRT,
                            (VOID*) ps_tuner_name,
                            _op_vchip_nfy_fct,
                            NULL,
                            &h_rrctx_rrt);
    }

    ui4_cur_time = c_os_get_sys_tick() * c_os_get_sys_tick_period();
    if (b_rrt_dirty || (ui4_last_time > 0 && ui4_cur_time - ui4_last_time > 30000))
    {
        ui4_last_time = ui4_cur_time;
        //if (NULL == h_thread)
        {
            i4_ret = x_thread_create(&h_thread,
                                     "_thread_update_drrt",
                                     8192,
                                     128,
                                     _channels_update_drrt,
                                     0,
                                     NULL);
            REST_LOG_I("_parental_controls_drrt_changed() create thread(_thread_update_drrt) i4_ret=%d\n",i4_ret);
        }
        //#endif
    }

    if (0 == ui4_last_time)
    {
        ui4_last_time = ui4_cur_time;
    }
}

static UINT16 _parental_controls_locks_get_rating_enable_idx(VOID)
{
    UINT8   ui1_rating_enabled;
    UINT8   ui1_val = RATING_ENABLED_STATUS_ON;
    SIZE_T  z_size = ICL_RECID_RATING_ENABLED_STATUS_SIZE;

    a_icl_get(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS), 
            &ui1_val, &z_size);

    REST_LOG_I("a_icl_get(ICL_GRPID_RATING_ENABLED_STATUS) :%d\n\r", ui1_val);
    
    if (RATING_ENABLED_STATUS_OFF == ui1_val)
    {
        REST_LOG_I("RATING_ENABLED_STATUS_OFF :%d\n\r", ui1_val);
    
        ui1_rating_enabled = 0;
    }
    else
    {
        a_cfg_get_rating_enabled(&ui1_rating_enabled);
    }
    #ifdef APP_NAV_PIP_VCHIP_SOL
    return (ui1_rating_enabled == APP_CFG_RATING_ENABLED_OFF) ? 0 : 1;
    #else
        return ui1_rating_enabled ? 1 : 0;
    #endif
}

int parental_controls_locks(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT32   val = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;
    
    Json::Value block;
    block[0]= "Off"; 
    block[1]= "On"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];
    
    type = get_type(root);
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_drrt_changed();

            val = _parental_controls_locks_get_rating_enable_idx();
            REST_LOG_I("lock :%d\n\r", val);
            response["VALUE"]=block[val];           
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_PARENTAL_CONTROL_LOCKS;
            
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                val = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                val = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            a_cfg_set_rating_enabled(val == 0 ? FALSE : TRUE);           

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}
int parental_controls_channel_locks(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    Json::Value array;
    array.resize(0);
    response["VALUE"] = array;
    return 0;
}

static INT32 _parental_controls_usa_tv_set_value(UINT16 ui2_row,UINT16 ui2_col,INT32 i4_val)
{
    REST_LOG_I("Enter, ui2_row: %d, ui2_col: %d\n\r", (int)ui2_row, (int)ui2_col);

    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age;
    UINT64  ui8_tv_cnt_map;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;

    a_cfg_lock();
    a_cfg_get_vchip_us(&ui1_mpaa,
                    &ui1_tv_age,
                    &ui8_tv_cnt_map,
                    &b_mpaa_bu,
                    &b_tv_bu);
    REST_LOG_I("set age:%d,map:%d\n\r", ui1_tv_age,ui8_tv_cnt_map);
    /* TV AGE */
    if (i4_val == 1)
    {
        if(COL_A == ui2_col)
        {
            ui1_tv_age = ui2_row;
        }       
    } 

    else if(i4_val == 0)
    {
        if(COL_A == ui2_col)
        {
            ui1_tv_age = ui2_row + 1;
        }
    }

    /* TV CNT */  
    if(1 == i4_val)
    {  
        //ui8_tv_cnt_map = 0;
        switch(ui2_col)
        {       
            case COL_A:
            {
                switch(ui2_row)
                {
                    case ROW_Y:
                    case ROW_Y7:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_Y7_FV;
                    case ROW_G:
                    case ROW_PG:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_D;
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_L;
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_S;
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_V;
                    case ROW_14:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_D;
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_L;
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_S;
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_V;
                    case ROW_MA:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_L;
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_S;
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_V;
                        break;
                    default:
                        break;
                }
            }
            case COL_FV:
            {
                switch(ui2_row)
                {
                    case ROW_Y7:
                    {
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_Y7_FV;
                        break;
                    }
                    default:
                        break;
                }
            }
            case COL_D:
            {
                switch(ui2_row)
                {
                    case ROW_PG:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_D;
                    case ROW_14:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_D;
                        break;
                    default:
                        break;
                }
                break;
            }
            case COL_L:
            {
                switch(ui2_row)
                {
                    case ROW_PG:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_L;
                    case ROW_14:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_L;
                    case ROW_MA:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_L;
                        break;
                    default:
                        break;
                }
                break;
            }
            case COL_S:
            {
                switch(ui2_row)
                {
                    case ROW_PG:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_S;
                    case ROW_14:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_S;
                    case ROW_MA:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_S;
                        break;
                    default:
                        break;
                }
                break;
            }
            case COL_V:
            {
                switch(ui2_row)
                {
                    case ROW_PG:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_V;
                    case ROW_14:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_V;
                    case ROW_MA:
                        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_V;
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
    }
    else if(0 == i4_val)
    {        
        switch(ui2_col)
        {       
            case COL_A:
            {
                switch(ui2_row)
                {                 
                    case ROW_MA:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_MA_L));
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_MA_S));
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_MA_V));                        
                    case ROW_14:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_14_D));
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_14_L));
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_14_S));
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_14_V));
                    case ROW_PG:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_PG_D));
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_PG_L));
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_PG_S));
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_PG_V));
                    case ROW_G:
                    case ROW_Y7:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_Y7_FV));
                        break;
                    default:
                        break;
                }
            }
            case COL_FV:
            {
                switch(ui2_row)
                {
                    case ROW_Y7:
                    {
                        ui8_tv_cnt_map &= ~(APP_CFG_VCHIP_US_CNT_TV_Y7_FV);
                        break;
                    }
                    default:
                        break;
                }
            }
            case COL_D:
            {
                switch(ui2_row)
                {
                    case ROW_14:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_14_D));
                    case ROW_PG:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_PG_D));
                        break;
                    default:
                        break;
                }
                break;
            }
            case COL_L:
            {
                switch(ui2_row)
                {
                    case ROW_MA:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_MA_L));
                    case ROW_14:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_14_L));
                    case ROW_PG:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_PG_L));
                        break;
                    default:
                        break;
                }
                break;
            }
            case COL_S:
            {
                switch(ui2_row)
                {
                    case ROW_MA:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_MA_S));
                    case ROW_14:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_14_S));
                    case ROW_PG:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_PG_S));
                        break;
                    default:
                        break;
                }
                break;
            }
            case COL_V:
            {
                switch(ui2_row)
                {
                    case ROW_MA:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_MA_V));
                    case ROW_14:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_14_V));
                    case ROW_PG:
                        ui8_tv_cnt_map &= (~(APP_CFG_VCHIP_US_CNT_TV_PG_V));
                        break;
                    default:
                        break;
                }
                break;
            }
            default:
                break;
        }
    }
    
    REST_LOG_I("set age:%d,map:%d\n\r", ui1_tv_age,ui8_tv_cnt_map);
    a_cfg_set_vchip_us(ui1_mpaa,
                    ui1_tv_age,
                    ui8_tv_cnt_map,
                    b_mpaa_bu,
                    b_tv_bu);

    a_cfg_unlock();
    return 0;
}

static INT32 _parental_controls_usa_tv_get_value(UINT16 ui2_row,UINT16 ui2_col,INT32* pi4_val)
{
    REST_LOG_I("Enter, ui2_row: %d, ui2_col: %d\n\r", (int)ui2_row, (int)ui2_col);
    
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age;
    UINT64  ui8_tv_cnt_map;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;
    BOOL    b_lock = FALSE;

    a_cfg_get_vchip_us(&ui1_mpaa,
                    &ui1_tv_age,
                    &ui8_tv_cnt_map,
                    &b_mpaa_bu,
                    &b_tv_bu);
    REST_LOG_I("get age:%d,map:%d\n\r", ui1_tv_age,ui8_tv_cnt_map);
    /* TV AGE */
    if(0 == ui2_col)
    {
        if(ui2_row < ui1_tv_age)
        {
            b_lock = FALSE;
        }
        else
        {
            b_lock = TRUE;                      
        }
    }
    /* TV CNT */  
    switch(ui2_row)
    {           
        case 1:
        {
            if(1 == ui2_col)
            {
                b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_Y7_FV) != 0);
            }
            break;
        }
        case 2:
            break;
        case 3:
        {
            switch(ui2_col)
            {
                case 2:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_D) != 0);
                    break;
                }
                case 3:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_L) != 0);
                    break;
                }
                case 4:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_S) != 0);
                    break;
                }
                case 5:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_V) != 0);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case 4:
        {
            switch(ui2_col)
            {
                case 2:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_D) != 0);
                    break;
                }
                case 3:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_L) != 0);
                    break;
                }
                case 4:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_S) != 0);
                    break;
                }
                case 5:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_V) != 0);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case 5:
        {
            switch(ui2_col)
            {
                case 3:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_L) != 0);
                    break;
                }
                case 4:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_S) != 0);
                    REST_LOG_I("get s b_lock:%d,map:%d\n\r", b_lock,ui8_tv_cnt_map);
                    break;
                }
                case 5:
                {
                    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_V) != 0);
                    REST_LOG_I("get v b_lock:%d,map:%d\n\r", b_lock,ui8_tv_cnt_map);
                    break;
                }
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }

    *pi4_val = (INT32)b_lock;

    return 0;
}

int parental_controls_usa_tv(Json::Value & root, Json::Value & response){return 0;}
int parental_controls_usa_tv_tv_y(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_usa_tv_tv_y_all(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_Y,COL_A,&val);
            REST_LOG_I("get tv y all:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_Y,COL_A,val);
            break;
        }
        default:
            break;
    }

    return 0;
}

int parental_controls_usa_tv_tv_y7(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_usa_tv_tv_y7_all(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_Y7,COL_A,&val);
            REST_LOG_I("get tv y7 all:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_Y7,COL_A,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_y7_fv(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_Y7,COL_FV,&val);
            REST_LOG_I("get tv y7 fv:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_Y7,COL_FV,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_g(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_usa_tv_tv_g_all(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_G,COL_A,&val);
            REST_LOG_I("get tv g all:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_G,COL_A,val);
            break;
        }
        default:
            break;
    }

    return 0;
}

int parental_controls_usa_tv_tv_pg(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_usa_tv_tv_pg_all(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_PG,COL_A,&val);
            REST_LOG_I("get tv pg all:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_PG,COL_A,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_pg_d(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_PG,COL_D,&val);
            REST_LOG_I("get tv pg d:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_PG,COL_D,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_pg_s(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_PG,COL_S,&val);
            REST_LOG_I("get tv pg s:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_PG,COL_S,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_pg_l(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_PG,COL_L,&val);
            REST_LOG_I("get tv pg l:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_PG,COL_L,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_pg_v(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_PG,COL_V,&val);
            REST_LOG_I("get tv pg v:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_PG,COL_V,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_14(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_usa_tv_tv_14_all(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_14,COL_A,&val);
            REST_LOG_I("get tv 14 all:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_14,COL_A,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_14_d(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_14,COL_D,&val);
            REST_LOG_I("get tv 14 d:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_14,COL_D,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_14_s(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_14,COL_S,&val);
            REST_LOG_I("get tv 14 s:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_14,COL_S,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_14_l(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_14,COL_L,&val);
            REST_LOG_I("get tv 14 l all:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_14,COL_L,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_14_v(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_14,COL_V,&val);
            REST_LOG_I("get tv 14 v:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_14,COL_V,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_ma(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_usa_tv_tv_ma_all(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_MA,COL_A,&val);
            REST_LOG_I("get tv ma all:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_MA,COL_A,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_ma_s(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_MA,COL_S,&val);
            REST_LOG_I("get tv ma s:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_MA,COL_S,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_ma_l(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_MA,COL_L,&val);
            REST_LOG_I("get tv ma l:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_MA,COL_L,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_tv_tv_ma_v(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0; /* val: 0 1 */
    CHAR  str[128] = {0};

    type = get_type(root);
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_tv_get_value(ROW_MA,COL_V,&val);
            REST_LOG_I("get tv ma v:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_tv_set_value(ROW_MA,COL_V,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

static INT32 _parental_controls_usa_movie_set_value(UINT16 ui2_idx,INT32 i4_val)
{
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age;
    UINT64  ui8_tv_cnt_map;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;

    a_cfg_lock();

    a_cfg_get_vchip_us(&ui1_mpaa,
                       &ui1_tv_age,
                       &ui8_tv_cnt_map,
                       &b_mpaa_bu,
                       &b_tv_bu);

    if(ui2_idx < ui1_mpaa && i4_val == 1)
    {
        /* unlock -> lock */
        ui1_mpaa = (UINT8)(ui2_idx);
    }    
    else
    {
        /* lock -> unlock */
        if (ui2_idx >= ui1_mpaa && i4_val == 0)
        {
            if (ui2_idx == 4)
            {
                ui1_mpaa = (UINT8)(ui2_idx + 2);

            }
            else
            {
                ui1_mpaa = (UINT8)(ui2_idx + 1);
            }
        }
    }
    a_cfg_set_vchip_us(ui1_mpaa,
                       ui1_tv_age,
                       ui8_tv_cnt_map,
                       b_mpaa_bu,
                       b_tv_bu);
    
    a_cfg_unlock();
    return 0;
}

static INT32 _parental_controls_usa_movie_get_value(UINT16 ui2_idx,INT32* pi4_val)
{
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age;
    UINT64  ui8_tv_cnt_map;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;
    INT32   ui4_val;

    a_cfg_get_vchip_us(&ui1_mpaa,
                       &ui1_tv_age,
                       &ui8_tv_cnt_map,
                       &b_mpaa_bu,
                       &b_tv_bu);

    if(ui2_idx < ui1_mpaa)
    {
        ui4_val = 0;
    }
    else
    {
        ui4_val = 1;
    }
    *pi4_val = ui4_val;
    return 0;
}

int parental_controls_usa_movie(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_usa_movie_all(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_movie_get_value(0,&val);
            REST_LOG_I("val:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_movie_set_value(0,val);
            break;
        }
        default:
            break;
    }

    return 0;
}

int parental_controls_usa_movie_g(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_movie_get_value(0,&val);
            REST_LOG_I("val:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_movie_set_value(0,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_movie_pg(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_movie_get_value(1,&val);
            REST_LOG_I("val:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_movie_set_value(1,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_movie_pg_13(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_movie_get_value(2,&val);
            REST_LOG_I("val:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_movie_set_value(2,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_movie_r(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_movie_get_value(3,&val);
            REST_LOG_I("val:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_movie_set_value(3,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_usa_movie_nc_17(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_usa_movie_get_value(4,&val);
            REST_LOG_I("val:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_usa_movie_set_value(4,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

static INT32 _parental_controls_canadian_english_set_value(UINT16 ui2_idx,INT32 i4_val)
{
    UINT8   ui1_en_rating = 0;
    UINT8   ui1_fr_rating = 0;

    a_cfg_lock();

    a_cfg_get_vchip_ca(&ui1_en_rating,
                       &ui1_fr_rating);
    REST_LOG_I("rating:%d\n\r",ui1_en_rating);
    if(ui2_idx+1 < ui1_en_rating && i4_val == 1)
    {
        /* unlock -> lock */
        ui1_en_rating = (UINT8)(ui2_idx + 1);
    }
    else
    {
        /* lock -> unlock */
        if (ui2_idx+1 >= ui1_en_rating && i4_val == 0)
        {
            ui1_en_rating = (UINT8)(ui2_idx + 2);
        }
    }
    
    a_cfg_set_vchip_ca(ui1_en_rating,
                       ui1_fr_rating);
    
    a_cfg_unlock();
    return 0;
}


static INT32 _parental_controls_canadian_english_get_value(UINT16 ui2_idx,INT32* pi4_val)
{
    UINT8   ui1_en_rating;
    UINT8   ui1_fr_rating;
    INT32   i4_val;

    a_cfg_get_vchip_ca(&ui1_en_rating,&ui1_fr_rating);
    REST_LOG_I("rating:%d\n\r",ui1_en_rating);
    if(ui2_idx+1 < ui1_en_rating)
    {
        /* unlock */
       i4_val = 0;
    }
    else
    {
        i4_val = 1;
    }
    *pi4_val = i4_val;

    return 0;
}


int parental_controls_canadian_english(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_canadian_english_c(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};
    
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_english_get_value(0,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_english_set_value(0,val);
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_english_c_plus(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};
    
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_english_get_value(1,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_english_set_value(1,val);
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_english_g(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};
    
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_english_get_value(2,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_english_set_value(2,val);
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_english_pg(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};
    
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_english_get_value(3,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_english_set_value(3,val);
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_english_14_plus(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};
    
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_english_get_value(4,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_english_set_value(4,val);
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_english_18_plus(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};
    
    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_english_get_value(5,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_english_set_value(5,val);
        }
        default:
            break;
    }
    return 0;
}

static INT32 _parental_controls_canadian_french_set_value(UINT16 ui2_idx,INT32 i4_val)
{
    UINT8   ui1_en_rating = 0;
    UINT8   ui1_fr_rating = 0;

    a_cfg_lock();

    a_cfg_get_vchip_ca(&ui1_en_rating,
                       &ui1_fr_rating);

    if(ui2_idx+1 < ui1_fr_rating && i4_val == 1)
    {
        /* unlock -> lock */
        ui1_fr_rating = (UINT8)(ui2_idx + 1);
    }
    else
    {
        /* lock -> unlock */
        if (ui2_idx+1 >= ui1_fr_rating && i4_val == 0)
        {
            ui1_fr_rating = (UINT8)(ui2_idx + 2);
        }
    }
    
    a_cfg_set_vchip_ca(ui1_en_rating,
                       ui1_fr_rating);
    
    a_cfg_unlock();
    return 0;
}


static INT32 _parental_controls_canadian_french_get_value(UINT16 ui2_idx,INT32* pi4_val)
{
    UINT8   ui1_en_rating;
    UINT8   ui1_fr_rating;
    INT32   i4_val;

    a_cfg_get_vchip_ca(&ui1_en_rating,&ui1_fr_rating);

    if(ui2_idx+1 < ui1_fr_rating)
    {
        /* unlock */
       i4_val = 0;
    }
    else
    {
        i4_val = 1;
    }
    *pi4_val = i4_val;

    return 0;
}


int parental_controls_canadian_french(Json::Value & root, Json::Value & response){return 0;}

int parental_controls_canadian_french_g(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_french_get_value(0,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_french_set_value(0,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_french_8_ans_plus(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_french_get_value(1,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_french_set_value(1,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_french_13_ans_plus(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_french_get_value(2,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_french_set_value(2,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_french_16_ans_plus(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_french_get_value(3,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_french_set_value(3,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_canadian_french_18_ans_plus(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    CHAR  str[128] = {0};

    Json::Value block;
    block[0]= "Unlocked"; 
    block[1]= "Locked"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_canadian_french_get_value(4,&val);
            REST_LOG_I("get value:%d\n\r",val);
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r",str);
            if(c_strcmp(str,"Unlocked") == 0)
            {
                val = 0;
            }
            else if(c_strcmp(str,"Locked") == 0)
            {
                val = 1;
            }
            _parental_controls_canadian_french_set_value(4,val);
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_drrt(Json::Value & root, Json::Value & response){return 0;}
int parental_controls_drrt_dimension_M(Json::Value & root, Json::Value & response)
{
    //int dimension_M = (root["N"].asInt())>>16;
    
    return 0;
}

static INT32 _op_vchip_trigger_vchip_exceed (VOID)
{
    INT32   i4_ret;
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age;
    UINT64  ui8_tv_cnt_map;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;

    /* dummy acfg setup -> trigger the notify only */
    i4_ret = a_cfg_get_vchip_us(&ui1_mpaa,
                                &ui1_tv_age,
                                &ui8_tv_cnt_map,
                                &b_mpaa_bu,
                                &b_tv_bu);
    if (APP_CFGR_OK == i4_ret)
    {
        a_cfg_set_vchip_us(ui1_mpaa,
                            ui1_tv_age,
                            ui8_tv_cnt_map,
                            b_mpaa_bu,
                            b_tv_bu);
    }

    return 0;
}

static INT32 _parental_controls_drrt_op_vchip_rating_settings(
    BOOL*               pb_lvl_block,
    BOOL                b_set_get,
    UINT8               ui1_dimming_idx)
{
    INT32       i4_ret = 0;
    RRCTX_RRT_RATE_SETTING_T t_rrt_setting;
    UINT16      ui2_svl_id = 0;
    CHAR*       ps_tuner_name;

    a_cfg_get_tuner_sync_src(&ui2_svl_id, &ps_tuner_name);

    if (NULL_HANDLE == h_rrctx_rrt)
    {
        c_rrctx_open_rating(RRCTX_RATING_TYPE_RRT,
                            (VOID*) ps_tuner_name,
                            _op_vchip_nfy_fct,
                            NULL,
                            &h_rrctx_rrt);
    }

    t_rrt_setting.b_set_get     = b_set_get;                      /* TRUE: Set, FALSE: Get */
    t_rrt_setting.ui1_rgn_idx   = 0;
    t_rrt_setting.ui1_dim_idx   = ui1_dimming_idx;
    t_rrt_setting.pb_lvl_block  = pb_lvl_block;
    t_rrt_setting.pui1_bu       = NULL;

    i4_ret = c_rrctx_rating_settings( h_rrctx_rrt, (VOID*) &t_rrt_setting);

    if (b_set_get)
    {
        _op_vchip_trigger_vchip_exceed();
        c_rrctx_rating_storage(h_rrctx_rrt, TRUE);
    }

    return i4_ret;
}

    
int parental_controls_drrt_dimension_M_ratingN(Json::Value & root, Json::Value & response)
{
    //int dimension_M = (root["N"].asInt())>>16;
    //int ratingN = (root["N"].asInt()) & 0xffff;
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    UINT16  val = 0;
    BOOL    b_block = FALSE;
    CHAR    str[128] = {0};
    UINT8   ui1_dimension_idx = ((root["N"].asInt())>>16) - 1;
    UINT8   ui1_rating_idx = (root["N"].asInt()) & 0xffff;
    static BOOL     pb_lvl_elem_block[15] = { FALSE };

    REST_LOG_I("ui1_dimension_idx: %d, ui1_rating_idx: %d\n\r",
        ui1_dimension_idx, ui1_rating_idx);

    Json::Value block;
    block[0]= "Off"; 
    block[1]= "On"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];
    
    type = get_type(root);
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            _parental_controls_drrt_op_vchip_rating_settings(pb_lvl_elem_block,
                                                            FALSE,
                                                            ui1_dimension_idx);
            b_block = pb_lvl_elem_block[ui1_rating_idx];
            val = (UINT16)(b_block ? 1 : 0);
            response["VALUE"]=block[val];           
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            if(c_strcmp(str,"Off") == 0)
            {
                pb_lvl_elem_block[ui1_rating_idx] = FALSE;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                pb_lvl_elem_block[ui1_rating_idx] = TRUE;
            }
            _parental_controls_drrt_op_vchip_rating_settings(pb_lvl_elem_block,
                                                            TRUE,
                                                            ui1_dimension_idx);
            break;
        }
        default:
            break;
    }
    return 0;
}


static VOID _parental_controls_block_unrated_shows_set_block_unrated_idx(UINT16 ui2_idx)
{
    UINT8   ui1_mpaa        = APP_CFG_VCHIP_US_MPAA_OFF;
    UINT8   ui1_tv_age      = APP_CFG_VCHIP_US_AGE_OFF;
    UINT64  ui8_tv_cnt_map  = 0;
    BOOL    b_mpaa_bu       = FALSE;
    BOOL    b_tv_bu         = FALSE;
    BOOL    b_block         = (ui2_idx == 0? FALSE: TRUE);

    REST_LOG_I("[Channel]b_block:%d\n\r", b_block);

    a_cfg_lock();

    a_cfg_set_vchip_unrated(b_block);

    a_cfg_get_vchip_us(&ui1_mpaa,
                       &ui1_tv_age,
                       &ui8_tv_cnt_map,
                       &b_mpaa_bu,
                       &b_tv_bu);

    a_cfg_set_vchip_us(ui1_mpaa,
                       ui1_tv_age,
                       ui8_tv_cnt_map,
                       b_block,     /* block MPAA NA/NR as well */
                       b_block);    /* block TV None setting */

    a_cfg_unlock();
}

int parental_controls_block_unrated_shows(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    UINT16  val = 0;
    BOOL    b_block = FALSE;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;
    
    Json::Value block;
    block[0]= "Off"; 
    block[1]= "On"; 
    response["ELEMENTS"]=block;
    response["VALUE"]=block[0];
    
    type = get_type(root);
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_vchip_unrated(&b_block);
            val = (UINT16)(b_block ? 1 : 0);
            response["VALUE"]=block[val];           
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;

            t_toast.style.style_2.ui4_id_1      = MLM_SETTINGS_KEY_PARENTAL_CONTROL_BLOCK_UNRATED;
            
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            if(c_strcmp(str,"Off") == 0)
            {
                val = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                val = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            
            REST_LOG_I("[Channel]val:%d\n\r", val);

            _parental_controls_block_unrated_shows_set_block_unrated_idx(val);           

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
        
    return 0;
}

int parental_controls_reset(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    a_cfg_custom_reset_channel_lock ();

    /* hide pin code dialog at the moment. */
    pwd_dlg_view_hide_all();

    return 0;
}

int current_channel(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    CHAR    s_ch_num[64]  = {0}; 
    CHAR    s_ch_name[CH_NAME_MAX_LENGTH + 1] = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {                       
            c_memset (s_ch_num, 0, sizeof(s_ch_num));
            tuner_setup_get_current_channel(s_ch_num,s_ch_name);
            REST_LOG_I("ch_num_name: %s,%s\n\r", s_ch_num,s_ch_name);
            string_set_response(response, s_ch_num);
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

int skip_channel_channel_N(Json::Value & root, Json::Value & response) 
{
//int channel_id = root["N"].asInt();//channel_id is channel id for use,comment it for build pass
    REST_LOG_I("Enter\n\r");
    return 0;
}

int skip_channel_channel_N_name(Json::Value & root, Json::Value & response) 
{
    //int channel_id = root["N"].asInt();//channel_id is channel id for use,comment it for build pass
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    CHAR    str_num[128] = {0};
    CHAR    str_name[128] = {0};
    BOOL    b_is_dig = FALSE;
    UINT32  ui4_id = root["N"].asInt();//(UINT32)id&ID_INDEX_MASK;

    type = get_type(root);
    REST_LOG_I("channel %d\n",ui4_id); 

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            tuner_setup_get_scan_channel_info_(ui4_id-1,str_num,str_name,&b_is_dig);
            REST_LOG_I("ui4_id:%d,str: %s\n\r", ui4_id,str_name);
            string_set_response(response, str_name);
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
#if 0
static VOID _channel_get_dig_and_ana_num(HANDLE_T h_svl,
                                            UINT16* pui2_num_recs_digital,
                                            UINT16* pui2_num_recs_analog)
{
    UINT32     ui4_ver_id = 0;
    UINT16     ui2_num_recs = 0;
    UINT16     ui2_i=0;
    UINT16     ui2_num_recs_digital = 0;
    UINT16     ui2_num_recs_analog = 0;
    SVL_REC_T  t_svl_rec;
    
    c_memset(&t_svl_rec,0,sizeof(t_svl_rec));   
    
    c_svl_lock(h_svl);
    /* get digital number */
    c_svl_get_num_rec_by_brdcst_type(h_svl, 
                                    BRDCST_TYPE_UNKNOWN, 
                                    SB_VNET_ALL, 
                                    &ui2_num_recs, 
                                    &ui4_ver_id);
               
    for(ui2_i = 0; ui2_i < ui2_num_recs; ui2_i++)
    {
        c_svl_get_rec_by_brdcst_type(h_svl,
                                     BRDCST_TYPE_UNKNOWN,
                                     SB_VNET_ALL,
                                     ui2_i,
                                     &t_svl_rec,
                                     &ui4_ver_id);

        if(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
        {
            continue;
        }
        ui2_num_recs_digital++;
    }                    
                
    /* get analog number */
    c_svl_get_num_rec_by_brdcst_type(h_svl, 
                                     BRDCST_TYPE_ANALOG,
                                     SB_VNET_ALL, 
                                     &ui2_num_recs,
                                     &ui4_ver_id);

    for(ui2_i = 0; ui2_i < ui2_num_recs; ui2_i++)
    {
      c_svl_get_rec_by_brdcst_type(h_svl,
                                   BRDCST_TYPE_ANALOG,
                                   SB_VNET_ALL,
                                   ui2_i,
                                   &t_svl_rec,
                                   &ui4_ver_id);

      if(t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE)
      {
          continue;
      }  

      ui2_num_recs_analog++;
    }  

    *pui2_num_recs_digital = ui2_num_recs_digital;
    *pui2_num_recs_analog  = ui2_num_recs_analog;
    c_svl_unlock(h_svl); 
 }
#endif
/*----------------------------------------------------------------------------
 * Name: tuner_setup_get_scan_channel_rec
 *
 * Description: 
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: 
 *          
 ----------------------------------------------------------------------------*/
VOID channel_get_scan_channel_rec(INT32 idx, SVL_REC_T *pt_svl_rec)
{
   
    OCL_SVL_REC_T  t_ocl_svl_rec = {0};

    if (NULL == pt_svl_rec)
    {
        DBG_LOG_PRINT(("tuner_setup_get_scan_channel_rec ARG Invalid\n"));
        return;
    }

    /* get the one channel list channel by the channel index */
    ocl_get_ocl_svl_by_index(idx, pt_svl_rec, &t_ocl_svl_rec);

}

#if 0
static INT32 _get_antenna_channel_num(UINT16* pui2_rec_num)
{    
    //INT32       i4_ret = 0;
    //UINT32      ui4_ver_id = SVL_NULL_VER_ID;
    UINT16      ui2_num_recs_digital = 0;
    UINT16      ui2_num_recs_analog = 0;
    HANDLE_T    h_svl = NULL_HANDLE;

    _channel_get_svl_handle_by_id(ATSC_TRSTRL_SVL_ID, &h_svl);
    _channel_get_dig_and_ana_num(h_svl, &ui2_num_recs_digital, &ui2_num_recs_analog);

    REST_LOG_I("svl rec num is %d\n", ui2_num_recs_digital + ui2_num_recs_analog);
   
    *pui2_rec_num = ui2_num_recs_digital + ui2_num_recs_analog;

    return 0;
}
#endif

static BOOL _channels_get_state_handler(UINT16 ui2_id,
                                                UINT32 ui4_sel_mask)
{
    SVL_REC_T       t_svl_rec;
#if 0
    UINT32          ui4_ver_id;
    UINT32          ui4_rec_id;
    UINT16          ui2_num = 0;
    HANDLE_T        h_svl = NULL_HANDLE;

    _get_antenna_channel_num(&ui2_num);
    
    if(ui2_id < ui2_num)
    {
        _channel_get_svl_handle_by_id(ATSC_TRSTRL_SVL_ID, &h_svl);
        c_svl_get_rec_by_channel(h_svl,
                                ui2_id - 1,
                                SB_VNET_ALL,
                                0,
                                &t_svl_rec,
                                &ui4_rec_id);
        /* get the record*/
        c_svl_get_rec(h_svl,
                    (UINT16)ui4_rec_id,
                    &t_svl_rec,
                    &ui4_ver_id);
    }
    else
    {
        _channel_get_svl_handle_by_id(ATSC_CABLE_SVL_ID, &h_svl);
        c_svl_get_rec_by_channel(h_svl,
                                ui2_id - 1,
                                SB_VNET_ALL,
                                0,
                                &t_svl_rec,
                                &ui4_rec_id);
        /* get the record*/
        c_svl_get_rec(h_svl,
                    (UINT16)ui4_rec_id,
                    &t_svl_rec,
                    &ui4_ver_id);
    }
#endif
    channel_get_scan_channel_rec(ui2_id-1, &t_svl_rec);

    if(t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & ui4_sel_mask)
    {
        
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

//extern INT32 menu_common_page_ch_lst2_refresh(VOID);

INT32 _channels_set_state_handler(UINT16 ui2_id,
                                                UINT32 ui4_sel_mask,
                                                BOOL b_sel)
{
    INT32       i4_ret = 0;
    SVL_REC_T     t_svl_rec     = {0};
    OCL_SVL_REC_T t_ocl_svl_rec = {0};
    HANDLE_T    h_svl = NULL_HANDLE;
    UINT8      ui1_val;
    SIZE_T     z_size;
    REST_LOG_I("ui2_id = %d\n", ui2_id);

    /* get the one channel list channel by the channel index */
    i4_ret = ocl_get_ocl_svl_by_index((ui2_id - 1), &t_svl_rec, &t_ocl_svl_rec);

    if (OCLR_OK != i4_ret)
    {
        REST_LOG_I("ocl_get_ocl_svl_by_index Error = %d, in fct=[%s]\n", i4_ret, __FUNCTION__);
    }
    
    if (t_ocl_svl_rec.ui2_svl_id == ANTENNA_SVL_ID)
    {
        _channel_get_svl_handle_by_id(ATSC_TRSTRL_SVL_ID, &h_svl);
    }
    else
    {
        _channel_get_svl_handle_by_id(ATSC_CABLE_SVL_ID, &h_svl);
    }    

    if(b_sel)
    {
        
        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask |= ui4_sel_mask;
    }
    else
    {
        t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask &= ~ui4_sel_mask;
    }

	if ( (ui4_sel_mask & SB_VNET_BLOCKED) > 0)
    {
         t_svl_rec.uheader.t_rec_hdr.ui4_option_mask &= ~SB_VOPT_USER_TMP_UNLOCK;
        ui1_val = RATING_ENABLED_STATUS_ON;
        z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;
        a_icl_set(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
                  (VOID*)&ui1_val,
                          z_size);
	}

    c_svl_lock(h_svl);
    c_svl_update_rec(h_svl,
                    &t_svl_rec,
                    TRUE);
    
    c_svl_unlock(h_svl);  
    
	/*Store SVL/TSL/NWL*/
	i4_ret = a_cfg_ch_lst_store();
	if(i4_ret != APP_CFGR_OK)
	{
		DBG_LOG_PRINT(("<ACFG> %s %d Can't store SVL/TSL/NWL.\n",__FUNCTION__,__LINE__));
	}
	
    return 0;
}


int skip_channel_channel_N_state(Json::Value & root, Json::Value & response) {
    //int channel_id = root["N"].asInt();//channel_id is channel id for use,comment it for build pass
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT32   val = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_id = root["N"].asInt();//(UINT32)id&ID_INDEX_MASK;
    BOOL    b_sel = FALSE;
    
    Json::Value block;
    block[0]= "No"; 
    block[1]= "Yes"; 
    response["ELEMENTS"]=block;

    type = get_type(root);
    REST_LOG_I("channel %d\n",ui2_id); 
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            b_sel = _channels_get_state_handler(ui2_id,SB_VNET_VISIBLE);
            if(b_sel)
            {
                val = 0;
            }
            else
            {
                val = 1;
            }
            response["VALUE"]=block[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {           
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            if(c_strcmp(str,"Yes") == 0)
            {
                _channels_set_state_handler(ui2_id,SB_VNET_VISIBLE,FALSE);
                menu_common_page_ch_lst2_refresh();
            }
            else if(c_strcmp(str,"No") == 0)
            {
                _channels_set_state_handler(ui2_id,SB_VNET_VISIBLE,TRUE);
                menu_common_page_ch_lst2_refresh();
            }
            break;
        }
        default:
            break;
    }
    return 0;
}

int parental_controls_channel_locks_channel_N(Json::Value & root, Json::Value & response) {
    //int channel_id = root["N"].asInt();//channel_id is channel id for use,comment it for build pass
    REST_LOG_I("Enter\n\r");
    return 0;
}
int parental_controls_channel_locks_channel_N_name(Json::Value & root, Json::Value & response) 
{
    //int channel_id = root["N"].asInt();//channel_id is channel id for use,comment it for build pass
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    CHAR    str_num[128] = {0};
    CHAR    str_name[128] = {0};
    BOOL    b_is_dig = FALSE;
    UINT32  ui4_id = root["N"].asInt();//(UINT32)id&ID_INDEX_MASK;

    type = get_type(root);
    REST_LOG_I("channel %d\n",ui4_id);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            tuner_setup_get_scan_channel_info_(ui4_id-1,str_num,str_name,&b_is_dig);
            REST_LOG_I("ui4_id:%d,str: %s\n\r", ui4_id,str_name);
            string_set_response(response, str_name);
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

int parental_controls_channel_locks_channel_N_state(Json::Value & root, Json::Value & response) {
    //int channel_id = root["N"].asInt();//channel_id is channel id for use,comment it for build pass
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT32   val = 0;
    CHAR    str[128] = {0};
    BOOL    b_sel = FALSE;
    UINT16  ui2_id = root["N"].asInt();//(UINT32)id&ID_INDEX_MASK;

    Json::Value lock;
    lock[0]= "Off";//"Unlocked"; 
    lock[1]= "On";//"Locked"; 
    response["ELEMENTS"]=lock;

    type = get_type(root);

    REST_LOG_I("channel %d\n",ui2_id);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("Get\n\r");
            b_sel = _channels_get_state_handler(ui2_id,SB_VNET_BLOCKED);
            if(b_sel)
            {
                val = 1;
            }
            else
            {
                val = 0;
            }
            REST_LOG_I("Get,val=%d\n\r",val);
            response["VALUE"]=lock[val];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            HANDLE_T h_svctx = NULL_HANDLE;
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("Set,str=%s\n\r",str);
            if(c_strcmp(str,"On") == 0)
            {
                _channels_set_state_handler(ui2_id,SB_VNET_BLOCKED,TRUE);
                menu_common_page_ch_lst2_refresh();
            }
            else if(c_strcmp(str,"Off") == 0)
            {
                _channels_set_state_handler(ui2_id,SB_VNET_BLOCKED,FALSE);
                menu_common_page_ch_lst2_refresh();
            }

            nav_get_svctx_handle(TV_WIN_ID_MAIN, &h_svctx);
            c_svctx_unblock_svc(h_svctx, FALSE);
            break;
        }
        default:
            break;
    }
    return 0;
}


handler channels_handler[] = {
    auto_channel_scan,
    analog,
    digital,
    percent_complete,
    //skip_channel,
    find_new_channel,
    analog_audio,
    digital_language,
    parental_controls,
    parental_controls_locks,
    parental_controls_channel_locks,
    parental_controls_usa_tv,
    parental_controls_usa_tv_tv_y,
    parental_controls_usa_tv_tv_y_all,
    parental_controls_usa_tv_tv_y7,
    parental_controls_usa_tv_tv_y7_all,
    parental_controls_usa_tv_tv_y7_fv,
    parental_controls_usa_tv_tv_g,
    parental_controls_usa_tv_tv_g_all,
    parental_controls_usa_tv_tv_pg,
    parental_controls_usa_tv_tv_pg_all,
    parental_controls_usa_tv_tv_pg_d,
    parental_controls_usa_tv_tv_pg_s,
    parental_controls_usa_tv_tv_pg_l,
    parental_controls_usa_tv_tv_pg_v,
    parental_controls_usa_tv_tv_14,
    parental_controls_usa_tv_tv_14_all,
    parental_controls_usa_tv_tv_14_d,
    parental_controls_usa_tv_tv_14_s,
    parental_controls_usa_tv_tv_14_l,
    parental_controls_usa_tv_tv_14_v,
    parental_controls_usa_tv_tv_ma,
    parental_controls_usa_tv_tv_ma_all,
    parental_controls_usa_tv_tv_ma_s,
    parental_controls_usa_tv_tv_ma_l,
    parental_controls_usa_tv_tv_ma_v,
    parental_controls_usa_movie,
    parental_controls_usa_movie_all,
    parental_controls_usa_movie_g,
    parental_controls_usa_movie_pg,
    parental_controls_usa_movie_pg_13,
    parental_controls_usa_movie_r,
    parental_controls_usa_movie_nc_17,
    parental_controls_canadian_english,
    parental_controls_canadian_english_c,
    parental_controls_canadian_english_c_plus,
    parental_controls_canadian_english_g,
    parental_controls_canadian_english_pg,
    parental_controls_canadian_english_14_plus,
    parental_controls_canadian_english_18_plus,
    parental_controls_canadian_french,
    parental_controls_canadian_french_g,
    parental_controls_canadian_french_8_ans_plus,
    parental_controls_canadian_french_13_ans_plus,
    parental_controls_canadian_french_16_ans_plus,
    parental_controls_canadian_french_18_ans_plus,
    parental_controls_drrt,
    parental_controls_drrt_dimension_M,
    parental_controls_drrt_dimension_M_ratingN,
    parental_controls_block_unrated_shows,
    parental_controls_reset,
    current_channel,
    skip_channel_channel_N,
    skip_channel_channel_N_name,
    skip_channel_channel_N_state,
    parental_controls_channel_locks_channel_N,
    parental_controls_channel_locks_channel_N_name,
    parental_controls_channel_locks_channel_N_state,
    cancel_channel_scan,

};

