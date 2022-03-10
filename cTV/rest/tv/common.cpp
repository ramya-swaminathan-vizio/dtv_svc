#include "common.h"
#include "argument.h"
#include "picture_ex.h"
#include <string.h>
#include <bits/unique_ptr.h>
#ifdef __cplusplus
extern "C" {
#include "c_os.h"
#include "nav/nav_common.h"
#include "nav/nav_comp_id.h"
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "wizard_anim/a_wzd.h"
#include "c_uc_str.h"
extern INT32 menu_custom_unblank_screen(UINT32 ui4_keycode);
extern INT32 menu_custom_page_time_local_setting_refresh_item(WDK_STRING_STYLE_T e_string_style);
}
#endif

#ifdef SYS_VSSP_REST_SERVER_DEBUG
uint32_t  ui4_rest_log_level = 7;
#else
uint32_t  ui4_rest_log_level = 2;
#endif

static CHAR module_name[] = "REST";

static VOID _rest_send_msg_to_nav_handler(VOID*    pv_tag1,
                                          VOID*    pv_tag2,
                                          VOID*    pv_tag3)
{
	static UINT32 ui4_default_keycode = 1;
    REST_LOG_I("Enter\n\r");
	menu_custom_unblank_screen(ui4_default_keycode); //dolphin default key value to force unblank

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION,
                              pv_tag1);

}

UINT8 rest_get_mlm_settings_lang_id(VOID)
{
#if 0
    ISO_639_LANG_T s639_lang;
    UINT8          ui1_lang_id = 0;
    INT32          i4_ret;

    ui1_lang_id = REST_LANG_ENG;

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    if (i4_ret == APP_CFGR_OK)
    {
        ui1_lang_id = mlm_settings_s639_to_langidx(s639_lang);
    }

    return ui1_lang_id;
#else
    //dolphin 20200508 said that vizio would translate the text in SCPL ,so we no longer need to translate the string according to
    //the Language ,we just need to return string in English
    return 0;
#endif
}


UINT8 rest_get_mlm_warnings_lang_id(VOID)
{
    ISO_639_LANG_T s639_lang;
    UINT8          ui1_lang_id = 0;
    INT32          i4_ret;

    ui1_lang_id = REST_LANG_ENG;

    i4_ret = a_cfg_get_gui_lang(s639_lang);

    if (i4_ret == APP_CFGR_OK) {
        ui1_lang_id = mlm_warnings_s639_to_langidx(s639_lang);
    }

    return ui1_lang_id;
}

VOID rest_send_msg_to_nav(WDK_TOAST_T* pt_toast)
{
    REST_LOG_I("Enter\n\r");

    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;

    LOG_ON_ERR(a_cfg_get_wzd_status(&ui2_status));
    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

    REST_LOG_I("oobe [state= %d]\n\r", (int)ui1_state);
    if(WZD_STATE_RESUME_C4TV == ui1_state)
    {
        REST_LOG_I("WZD_STATE_RESUME_C4TV == ui1_state, not to show UI\n\r");
        return;
    }

    WDK_TOAST_T* pt_toast_cpy = NULL;

    pt_toast_cpy = (WDK_TOAST_T*)c_mem_alloc(sizeof(WDK_TOAST_T));

    if (NULL == pt_toast_cpy)
    {
        REST_LOG_E("NULL == pt_toast_cpy!!\n");
        return;
    }

    c_memcpy((VOID*)pt_toast_cpy, (const VOID*)pt_toast, sizeof(WDK_TOAST_T));

    if (pt_toast->e_string_style == WDK_STRING_STRING)
    {
        CHAR     str[256]  = {0};
        UTF16_T* p_w2s_str = (UTF16_T*)pt_toast->style.style_4.w2s_str;
        INT32    len  = 0;

        c_uc_w2s_to_ps((const UTF16_T*)p_w2s_str, str, 255);
        REST_LOG_I("str: %s\n\r", str);

        len = (c_uc_w2s_strlen(p_w2s_str)+1)*2;

        REST_LOG_I("c_uc_w2s_strlen: %d\n\r", len);

        pt_toast_cpy->style.style_4.w2s_str = (UTF16_T*)c_mem_alloc(len);

        c_memset((VOID*)pt_toast_cpy->style.style_4.w2s_str, 0, len);

        c_memcpy((VOID*)pt_toast_cpy->style.style_4.w2s_str, (const VOID*)pt_toast->style.style_4.w2s_str, len);
    }
    else if (pt_toast->e_string_style == WDK_STRING_TITLE_CONTENT)
    {
        INT32    len  = 0;

        len = (c_uc_w2s_strlen((UTF16_T*)pt_toast->style.style_5.w2s_title_str)+1)*2;

        REST_LOG_I("c_uc_w2s_strlen: %d\n\r", len);
        pt_toast_cpy->style.style_5.w2s_title_str = (UTF16_T*)c_mem_alloc(len);
        c_memset((VOID*)pt_toast_cpy->style.style_5.w2s_title_str, 0, len);
        c_memcpy((VOID*)pt_toast_cpy->style.style_5.w2s_title_str, (const VOID*)pt_toast->style.style_5.w2s_title_str, len);


        len = (c_uc_w2s_strlen((UTF16_T*)pt_toast->style.style_5.w2s_content_str)+1)*2;
        pt_toast_cpy->style.style_5.w2s_content_str = (UTF16_T*)c_mem_alloc(len);
        c_memset((VOID*)pt_toast_cpy->style.style_5.w2s_content_str, 0, len);
        c_memcpy((VOID*)pt_toast_cpy->style.style_5.w2s_content_str, (const VOID*)pt_toast->style.style_5.w2s_content_str, len);
    }

	if(pt_toast->e_string_style == WDK_STRING_STRING)
	{
		if(pt_toast->style.style_4.ui4_id == MLM_SETTINGS_KEY_TIME_ZONE)
		{
			menu_custom_page_time_local_setting_refresh_item(pt_toast->e_string_style);
		}
	}
	else if(pt_toast->e_string_style == WDK_STRING_ID_ID)
	{
		if( pt_toast->style.style_2.ui4_id_1 == MLM_SETTINGS_KEY_TIME_ZONE ||
		    pt_toast->style.style_2.ui4_id_1 == MLM_SETTINGS_KEY_DAYLIGHT_SAVING ||
		    pt_toast->style.style_2.ui4_id_1 == MLM_SETTINGS_KEY_TIME_FORMAT )
		{
			menu_custom_page_time_local_setting_refresh_item(pt_toast->e_string_style);
		}
	}
    nav_request_context_switch(_rest_send_msg_to_nav_handler,
                               (VOID*) pt_toast_cpy,
                               NULL,
                               NULL);
}

static VOID _rest_send_msg_to_revolt_info_hide_handler(VOID*    pv_tag1,
                                                       VOID*    pv_tag2,
                                                       VOID*    pv_tag3)
{
    REST_LOG_I("Enter\n\r");

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_NOTIFICATION_HIDE,
                              NULL);

}

VOID rest_send_msg_to_revolt_info_hide()
{
    REST_LOG_I("Enter\n\r");

    nav_request_context_switch(_rest_send_msg_to_revolt_info_hide_handler,
                               NULL,
                               NULL,
                               NULL);
}

INT32 get_type(Json::Value & root)
{
    REST_LOG_I("Enter\n\r");

    argument::RequestType req_type(root);

    REST_LOG_I("type: %d\n\r", req_type.type);

    return req_type.type;
}

INT32 value_get_value(Json::Value & root)
{
    REST_LOG_I("Enter\n\r");
    INT32 value = 0;

    argument::Factory<argument::Value> &factory = argument::Factory<argument::Value>::getInstance();

    value = (factory.create(root))->value;
    REST_LOG_I("value: %d\n\r", value);

    return value;
}

VOID value_set_response(Json::Value & response, INT32 value)
{
    REST_LOG_I("Enter, value: %d\n\r", value);

    argument::Value v;
    argument::Factory<argument::Value> &factory = argument::Factory<argument::Value>::getInstance();

    v.value = (int)value;

    response["VALUE"] = factory.create(v);

    return;
}

VOID string_get_string(Json::Value & root, CHAR* string, INT32 length)
{
    REST_LOG_I("Enter\n\r");
    std::string str;

    if (NULL == string)
    {
        REST_LOG_E("NULL == string!!\n");
        return;
    }

    argument::Factory<argument::String> &factory = argument::Factory<argument::String>::getInstance();

    str = (factory.create(root))->str;

    c_memset((VOID*)string, 0, length);
    c_strncpy(string, (const CHAR*)str.c_str(), length-1);

    REST_LOG_I("string: %s\n\r", string);

    return;
}

VOID string_set_response(Json::Value & response, CHAR* str)
{
    REST_LOG_I("Enter, str: %s\n\r", str);

    argument::String v;
    argument::Factory<argument::String> &factory = argument::Factory<argument::String>::getInstance();

    v.str = std::string(str);

    response["VALUE"] = factory.create(v);

    return;
}

INT32 rest_config_set_value(UINT16 ui2_grpid, UINT16 ui2_recid, INT32 i4_val)
{
    REST_LOG_I("Enter, ui2_grpid: %d, ui2_recid: %d, i4_val: %d\n\r", (int)ui2_grpid, (int)ui2_recid, (int)i4_val);

    UINT16 ui2_rec_id = CFG_MAKE_ID(ui2_grpid, ui2_recid);
    INT16  i2_set_val = 0;

    switch (ui2_grpid)
    {
        case APP_CFG_GRPID_VIDEO:
        {
            REST_LOG_I("APP_CFG_GRPID_VIDEO\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_VID_BRI:
                case APP_CFG_RECID_VID_CNT:
                case APP_CFG_RECID_VID_SAT:
                case APP_CFG_RECID_VID_HUE:
                case APP_CFG_RECID_VID_SHP:
                {
                    a_cfg_av_set(ui2_rec_id, (INT16)i4_val);
                    a_cfg_av_update(ui2_rec_id);

                    rest_set_preset_pic_mode_chg_status(TRUE);

                    break;
                }

                case APP_CFG_RECID_VID_CLR_HUE_R:
                case APP_CFG_RECID_VID_CLR_HUE_G:
                case APP_CFG_RECID_VID_CLR_HUE_B:
                case APP_CFG_RECID_VID_CLR_HUE_C:
                case APP_CFG_RECID_VID_CLR_HUE_M:
                case APP_CFG_RECID_VID_CLR_HUE_Y:

                case APP_CFG_RECID_VID_CLR_SAT_R:
                case APP_CFG_RECID_VID_CLR_SAT_G:
                case APP_CFG_RECID_VID_CLR_SAT_B:
                case APP_CFG_RECID_VID_CLR_SAT_C:
                case APP_CFG_RECID_VID_CLR_SAT_M:
                case APP_CFG_RECID_VID_CLR_SAT_Y:

                case APP_CFG_RECID_VID_CLR_BRI_R:
                case APP_CFG_RECID_VID_CLR_BRI_G:
                case APP_CFG_RECID_VID_CLR_BRI_B:
                case APP_CFG_RECID_VID_CLR_BRI_C:
                case APP_CFG_RECID_VID_CLR_BRI_M:
                case APP_CFG_RECID_VID_CLR_BRI_Y:

                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:

                case APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
                case APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
                case APP_CFG_RECID_VID_CUST_CLR_GAIN_B:

                {
                    a_cfg_av_set(ui2_rec_id, (INT16)i4_val);
                    clr_tuner_custom_process(ui2_grpid, ui2_recid, i4_val);

                    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

                    if(ui2_recid >= APP_CFG_RECID_VID_CUST_CLR_GAIN_R && ui2_recid <= APP_CFG_RECID_VID_CUST_CLR_OFFSET_B)
                    {
                        set_clr_temp_chg_status(TRUE);
                    }

                    break;
                }

                case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
                {
                    a_cfg_av_set(ui2_rec_id, (INT16)i4_val);
                    a_cfg_av_update(ui2_rec_id);

                #ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
                    a_cfg_custom_plf_opt_set_lightsensor((UINT16)i4_val);
                #endif

                    rest_set_preset_pic_mode_chg_status(TRUE);
                    break;
                }

                default:
                    break;
            }

            break;
        }

        case APP_CFG_GRPID_AUDIO:
        {
            REST_LOG_I("APP_CFG_GRPID_AUDIO\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_AUD_LATENCY:
                {
                    i2_set_val=(INT16)i4_val*10;
                    a_cfg_set_lip_sync(i2_set_val);
                    a_cfg_av_update(ui2_rec_id);

                    break;
                }
                case APP_CFG_RECID_AUD_BALANCE:
                case APP_CFG_RECID_VOLUME_ALL:
                case APP_CFG_RECID_AUD_BASS:
                case APP_CFG_RECID_AUD_TREBLE:
                {
                    a_cfg_av_set(ui2_rec_id, (INT16)i4_val);
                    a_cfg_av_update(ui2_rec_id);

                    break;
                }

                default:
                    break;
            }

            break;
        }

        case APP_CFG_GRPID_DISP:
        {
            REST_LOG_I("APP_CFG_GRPID_DISP\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_DISP_BACK_LIGHT:
                {
                    a_cfg_av_set(ui2_rec_id, (INT16)i4_val);
                    a_cfg_av_update(ui2_rec_id);

                    rest_set_preset_pic_mode_chg_status(TRUE);

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

    return 0;
}

INT32 rest_config_get_value(UINT16 ui2_grpid, UINT16 ui2_recid, INT32* pi4_val)
{
    REST_LOG_I("Enter, ui2_grpid: %d, ui2_recid: %d\n\r", (int)ui2_grpid, (int)ui2_recid);

    UINT16 ui2_rec_id = CFG_MAKE_ID(ui2_grpid, ui2_recid);
    INT16  i2_val =0;

    switch (ui2_grpid)
    {
        case APP_CFG_GRPID_VIDEO:
        {
            REST_LOG_I("APP_CFG_GRPID_VIDEO\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_VID_BRI:
                case APP_CFG_RECID_VID_CNT:
                case APP_CFG_RECID_VID_SAT:
                case APP_CFG_RECID_VID_HUE:
                case APP_CFG_RECID_VID_SHP:

                case APP_CFG_RECID_VID_CLR_HUE_R:
                case APP_CFG_RECID_VID_CLR_HUE_G:
                case APP_CFG_RECID_VID_CLR_HUE_B:
                case APP_CFG_RECID_VID_CLR_HUE_C:
                case APP_CFG_RECID_VID_CLR_HUE_M:
                case APP_CFG_RECID_VID_CLR_HUE_Y:

                case APP_CFG_RECID_VID_CLR_SAT_R:
                case APP_CFG_RECID_VID_CLR_SAT_G:
                case APP_CFG_RECID_VID_CLR_SAT_B:
                case APP_CFG_RECID_VID_CLR_SAT_C:
                case APP_CFG_RECID_VID_CLR_SAT_M:
                case APP_CFG_RECID_VID_CLR_SAT_Y:

                case APP_CFG_RECID_VID_CLR_BRI_R:
                case APP_CFG_RECID_VID_CLR_BRI_G:
                case APP_CFG_RECID_VID_CLR_BRI_B:
                case APP_CFG_RECID_VID_CLR_BRI_C:
                case APP_CFG_RECID_VID_CLR_BRI_M:
                case APP_CFG_RECID_VID_CLR_BRI_Y:

                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:

                case APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
                case APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
                case APP_CFG_RECID_VID_CUST_CLR_GAIN_B:

                {
                    a_cfg_av_get(ui2_rec_id, &i2_val);
                    *pi4_val = (INT32)i2_val;

                    break;
                }

                case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
                {
                    a_cfg_av_get(ui2_rec_id, &i2_val);
                    *pi4_val = (INT32)i2_val;

                #ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
                    a_cfg_custom_plf_opt_get_lightsensor();
                #endif

                    break;
                }

                default:
                    break;
            }

            break;
        }

        case APP_CFG_GRPID_AUDIO:
        {
            REST_LOG_I("APP_CFG_GRPID_AUDIO\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_AUD_LATENCY:
                {
                    a_cfg_get_lip_sync(&i2_val);
                    i2_val= i2_val/10;
                    *pi4_val = (INT32)i2_val;

                    break;
                }
                case APP_CFG_RECID_AUD_BALANCE:
                case APP_CFG_RECID_VOLUME_ALL:
                case APP_CFG_RECID_AUD_BASS:
                case APP_CFG_RECID_AUD_TREBLE:
                {
                    a_cfg_av_get(ui2_rec_id, &i2_val);
                    *pi4_val = (INT32)i2_val;

                    break;
                }

                default:
                    break;
            }

            break;
        }

        case APP_CFG_GRPID_DISP:
        {
            REST_LOG_I("APP_CFG_GRPID_DISP\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_DISP_BACK_LIGHT:
                {
                    a_cfg_av_get(ui2_rec_id, &i2_val);
                    *pi4_val = (INT32)i2_val;

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

    return 0;
}

INT32 rest_config_get_min_max_value(UINT16 ui2_grpid, UINT16 ui2_recid, INT32* pi4_min_val, INT32* pi4_max_val)
{
    REST_LOG_I("Enter, ui2_grpid: %d, ui2_recid: %d\n\r", (int)ui2_grpid, (int)ui2_recid);

    UINT16 ui2_rec_id = CFG_MAKE_ID(ui2_grpid, ui2_recid);
    INT16  i2_min_val = 0;
    INT16  i2_max_val = 0;

    switch (ui2_grpid)
    {
        case APP_CFG_GRPID_VIDEO:
        {
            REST_LOG_I("APP_CFG_GRPID_VIDEO\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_VID_BRI:
                case APP_CFG_RECID_VID_CNT:
                case APP_CFG_RECID_VID_SAT:
                case APP_CFG_RECID_VID_HUE:
                case APP_CFG_RECID_VID_SHP:

                case APP_CFG_RECID_VID_CLR_HUE_R:
                case APP_CFG_RECID_VID_CLR_HUE_G:
                case APP_CFG_RECID_VID_CLR_HUE_B:
                case APP_CFG_RECID_VID_CLR_HUE_C:
                case APP_CFG_RECID_VID_CLR_HUE_M:
                case APP_CFG_RECID_VID_CLR_HUE_Y:

                case APP_CFG_RECID_VID_CLR_SAT_R:
                case APP_CFG_RECID_VID_CLR_SAT_G:
                case APP_CFG_RECID_VID_CLR_SAT_B:
                case APP_CFG_RECID_VID_CLR_SAT_C:
                case APP_CFG_RECID_VID_CLR_SAT_M:
                case APP_CFG_RECID_VID_CLR_SAT_Y:

                case APP_CFG_RECID_VID_CLR_BRI_R:
                case APP_CFG_RECID_VID_CLR_BRI_G:
                case APP_CFG_RECID_VID_CLR_BRI_B:
                case APP_CFG_RECID_VID_CLR_BRI_C:
                case APP_CFG_RECID_VID_CLR_BRI_M:
                case APP_CFG_RECID_VID_CLR_BRI_Y:

                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_R:
                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_G:
                case APP_CFG_RECID_VID_CUST_CLR_OFFSET_B:

                case APP_CFG_RECID_VID_CUST_CLR_GAIN_R:
                case APP_CFG_RECID_VID_CUST_CLR_GAIN_G:
                case APP_CFG_RECID_VID_CUST_CLR_GAIN_B:

                case APP_CFG_RECID_VID_11_POINT_GAIN_RED: /*11 POINT GAIN READ*/
                case APP_CFG_RECID_VID_11_POINT_GAIN_GREEN:/*11 POINT GAIN GREEN*/
                case APP_CFG_RECID_VID_11_POINT_GAIN_BLUE:/*11 POINT GAIN BLUE*/

                {
                    a_cfg_av_get_min_max(ui2_rec_id, &i2_min_val, &i2_max_val);
                    *pi4_min_val = (INT32)i2_min_val;
                    *pi4_max_val = (INT32)i2_max_val;
                    break;
                }

                case APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR:
                {
                    break;
                }

                default:
                    break;
            }

            break;
        }

        case APP_CFG_GRPID_AUDIO:
        {
            REST_LOG_I("APP_CFG_GRPID_AUDIO\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_AUD_LATENCY:
                case APP_CFG_RECID_AUD_BALANCE:
                case APP_CFG_RECID_VOLUME_ALL:
                case APP_CFG_RECID_AUD_BASS:
                case APP_CFG_RECID_AUD_TREBLE:
                {
                    a_cfg_av_get_min_max(ui2_rec_id, &i2_min_val, &i2_max_val);
                    *pi4_min_val = (INT32)i2_min_val;
                    *pi4_max_val = (INT32)i2_max_val;

                    break;
                }

                default:
                    break;
            }

            break;
        }

        case APP_CFG_GRPID_DISP:
        {
            REST_LOG_I("APP_CFG_GRPID_DISP\n\r");

            switch (ui2_recid)
            {
                case APP_CFG_RECID_DISP_BACK_LIGHT:
                {
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

    return 0;
}

CHAR* rest_get_rest_name_prefix()
{
    return module_name;
}

