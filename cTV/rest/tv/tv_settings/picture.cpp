#include <iostream>
#include <bits/unique_ptr.h>
#include <memory>
#include "picture.h"
#include "picture_ex.h"
#include "handler.h"
#include "common.h"
#include "argument.h"
#include <string.h>
#include <unistd.h>
#include "system.h"
#include "devices.h"

#ifdef __cplusplus
extern "C" {
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/menu2/menu_custom.h"

#include "app_util/config/_acfg.h"
#include "app_util/config/acfg_cust_misc.h"
#include "res_mngr/drv/u_drv_cust.h"
#include "a_picture_ex.h"
#include "app_util/tvstate/smart_dim.h"
#include "nav/input_src/input_src.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"
#include "nav/input_src/a_input_src.h"
#include "res/app_util/config/acfg_cust_video.h"

}
#endif

TvSettingsGroupURI tvSettingsPictureUri[] = {
        { "picture_mode" },
        { "auto_brightness_control" },
        { "backlight" },
        { "brightness" },
        { "contrast" },
        { "color" },
        { "tint" },
        { "sharpness" },
        { "color_calibration" , "picture_mode" },
        { "color_calibration" , "color_temperature" },
        { "color_calibration" , "calibration_tests" , "smpte_test_pattern" },
        { "color_calibration" , "calibration_tests" , "flat_test_pattern" },
        { "color_calibration" , "calibration_tests" , "ramp_test_pattern" },
        { "color_calibration" , "calibration_tests" , "uniformity_analyzer_test_pattern" },
        { "color_calibration" , "calibration_tests" , "dolby_vision_test_pattern" },
        { "color_calibration" , "reset_color_tuner" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "header" , "red" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "header" , "green" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "header" , "blue" },
       /* { "color_calibration" , "color_tuner" , "color_tuner_table" , "header" , "cyan" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "header" , "magenta" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "header" , "yellow"
        }, */
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "hue" , "red" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "hue" , "green" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "hue" , "blue" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "hue" , "cyan" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "hue" , "magenta" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "hue" , "yellow" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "saturation" , "red" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "saturation" , "green" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "saturation" , "blue" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "saturation" , "cyan" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "saturation" , "magenta" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "saturation" , "yellow" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "brightness" , "red" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "brightness" , "green" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "brightness" , "blue" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "brightness" , "cyan" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "brightness" , "magenta" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "brightness" , "yellow" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "offset" , "red" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "offset" , "green" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "offset" , "blue" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "gain" , "red" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "gain" , "green" },
        { "color_calibration" , "color_tuner" , "color_tuner_table" , "gain" , "blue" },
        { "more_picture" , "color_temperature" },
        { "more_picture" , "black_detail" },
        { "more_picture" , "active_led_zones" },
        { "more_picture" , "backlight_control" },
        { "more_picture" , "reduce_judder" },
        { "more_picture" , "reduce_motion_blur" },
        { "more_picture" , "clear_action" },
        { "more_picture" , "reduce_signal_noise" },
        { "more_picture" , "reduce_block_noise" },
        { "more_picture" , "game_low_latency" },
        { "more_picture" , "film_mode" },
        { "more_picture" , "color_space" },
        { "more_picture" , "gamma" },
        { "picture_mode_edit" , "save_picture_mode" },
        { "picture_mode_edit" , "lock_unlock_picture_mode" },
        { "picture_mode_edit" , "delete_picture_mode" },
        { "picture_mode_edit" , "reset_picture_mode" },
        /*{ "color_calibration" , "color_tuner" , "11_point_balance" , "gain" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "blue" },*/
        { "color_calibration" , "color_tuner" , "11_point_balance" , "5_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "5_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "5_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "10_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "10_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "10_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "20_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "20_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "20_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "30_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "30_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "30_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "40_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "40_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "40_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "50_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "50_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "50_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "60_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "60_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "60_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "70_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "70_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "70_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "80_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "80_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "80_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "90_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "90_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "90_ire", "blue" },

        { "color_calibration" , "color_tuner" , "11_point_balance" , "100_ire", "red" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "100_ire", "green" },
        { "color_calibration" , "color_tuner" , "11_point_balance" , "100_ire", "blue" },

        { "hdr_backlight"},
        { "more_picture" , "ultra_color_spectrum"},
        { "color_calibration" , "lut_selection_normal"},
        { "color_calibration" , "lut_selection_computer"},
        { "color_calibration" , "lut_selection_cool"},

        { "" },
};

INT32 more_picture_color_temperature(Json::Value & root, Json::Value & response);

INT32 set_picture_mode(const char* set_name)
{
            INT16  i2_pic_mode_idx = 0;
            INT32  i = 0;
            //CHAR   set_name[64] = {0};
            CHAR   name[64] = {0};

            REST_LOG_I("Enter, set_name:%s\n\r", set_name);

            for (; i<ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX; i++)
            {
                c_memset(name, 0, 64);
                get_vid_pic_mode_text(i, name, 64);
                if (c_strcmp(name, set_name) == 0)
                {
                    i2_pic_mode_idx = i;
                    REST_LOG_I("Set Pic mode idx:%d,name:%s,set_name:%s\n\r", i2_pic_mode_idx,name,set_name);
                    break;
                }
            }

            if (i < ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX)
            {
                UTF16_T     w2s_str_pic[256] = {0};
                UTF16_T     w2s_str_point[64] = {0};
                UTF16_T     w2s_str_name[64]  = {0};
                CHAR        str_point[8] = ".";
                WDK_TOAST_T t_toast;

                c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_ITEM));

                c_uc_ps_to_w2s((const CHAR*)set_name, w2s_str_name, 63);
                c_uc_w2s_strncat(w2s_str_pic,w2s_str_name,63);

                c_uc_ps_to_w2s((const CHAR*)str_point, w2s_str_point, 63);
                c_uc_w2s_strncat(w2s_str_pic,w2s_str_point,63);

                memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

                t_toast.e_toast_style  = WDK_STRING_TOAST;
                t_toast.e_string_style = WDK_STRING_STRING;

                t_toast.style.style_4.w2s_str = (VOID*)w2s_str_pic;

                rest_send_msg_to_nav(&t_toast);
                menu_set_vid_pic_mode_idx(i2_pic_mode_idx);
            }
            else
            {
                REST_LOG_I("Wrong value: %s\n\r", set_name);
                return -1;
            }

            return 0;
}

//get the picture name and return the picture mode number
INT16 _get_acfg_picture_name(CHAR (*p_name)[64])
{
	INT16 i2_pic_num_max = 14; //dolphin 20200413 said: it's a dead code define in menu_common_setting.c t_g_menu_common_item_vid_pic_mode.u.t_list.ui2_elem_num ,it's made by picture ,not us
	i2_pic_num_max = menu_get_cust_picture_mode_num(); //update num&cache
	REST_LOG_E("Picture mode num %d\n",i2_pic_num_max);

	for (INT32 i=0; i<i2_pic_num_max; i++)
	{
		CHAR name[64] = {0};
		get_vid_pic_mode_text(i, name, 64);
		REST_LOG_I("Pic mode, idx:%d, name:%s\n\r", i, name);
		if(c_strlen(name) != 0)
		{
			c_strcpy(p_name[i],name);
		}
	}
	return i2_pic_num_max;
}

INT32 picture_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT16  i2_idx = 0;
    INT32 i4_ret = 0;

    CHAR  s_pic_mode_name[12][64] = {0};

    type = get_type(root);
    i2_idx = _get_acfg_picture_name(s_pic_mode_name);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16  i2_pic_mode_idx = 0;
            Json::Value pictures;

            for (INT32 i=0; i<i2_idx; i++)
            {
                pictures[i] = std::string(s_pic_mode_name[i]);
            }

            i2_pic_mode_idx = menu_get_vid_pic_mode_idx();
            REST_LOG_I("map pic mode idx:%d name %s\n\r", i2_pic_mode_idx, s_pic_mode_name[i2_pic_mode_idx]);

            response["ELEMENTS"] = pictures;
            response["VALUE"] = pictures[i2_pic_mode_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT16  i2_pic_mode_idx = -1;
            INT32  i = 0;
            CHAR   set_name[64] = {0};
            CHAR   name[64] = {0};
            const INT16 i2_pic_num_max = ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX; //dolphin 20200413 said: it's a dead code define in menu_common_setting.c t_g_menu_common_item_vid_pic_mode.u.t_list.ui2_elem_num ,it's made by picture ,not us

            string_get_string(root, set_name, 64);
            REST_LOG_I("set_name:%s\n\r", set_name);

            for (; i<i2_pic_num_max; i++)
            {
                c_memset(name, 0, 64);
                get_vid_pic_mode_text(i, name, 64);
                //REST_LOG_I("get_vid_pic_mode_text:%s\n\r", name);

                if(0 == c_strcmp(name, set_name))
                {
                    i2_pic_mode_idx = i;
                    REST_LOG_I("**Set Pic mode idx:%d,name:%s,set_name:%s\n\r", i2_pic_mode_idx,name,set_name);
                    break;
                }
            }

            if ((i < ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX) && (i2_pic_mode_idx != -1))
            {
                UTF16_T     w2s_str_pic[256] = {0};
                UTF16_T     w2s_str_point[64] = {0};
                UTF16_T     w2s_str_name[64]  = {0};
                CHAR        str_point[8] = ".";
                WDK_TOAST_T t_toast;

                c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_ITEM));

                c_uc_ps_to_w2s((const CHAR*)set_name, w2s_str_name, 63);
                c_uc_w2s_strncat(w2s_str_pic,w2s_str_name,63);

                c_uc_ps_to_w2s((const CHAR*)str_point, w2s_str_point, 63);
                c_uc_w2s_strncat(w2s_str_pic,w2s_str_point,63);

                memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

                t_toast.e_toast_style  = WDK_STRING_TOAST;
                t_toast.e_string_style = WDK_STRING_STRING;

                t_toast.style.style_4.w2s_str = (VOID*)w2s_str_pic;

                rest_send_msg_to_nav(&t_toast);
                menu_set_vid_pic_mode_idx(i2_pic_mode_idx);
            }
            else
            {
                REST_LOG_E("Wrong value: %s\n\r", set_name);
                i4_ret = -1;
            }

            break;
        }
        default:
            break;
    }

    return i4_ret;
}


INT32 auto_brightness_control(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT16 i2_get_val = 0;
    INT16 i2_set_val = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "Low";
            items[2] = "Medium";
            items[3] = "High";
            response["ELEMENTS"] = items;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_get_val);
            REST_LOG_I("id:%d\n\r", i2_get_val);
            response["VALUE"] = items[i2_get_val];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_BRI_CONTROL;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            if(c_strcmp(str,"Off") == 0)
            {
                i2_set_val  = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"Low") == 0)
            {
                i2_set_val = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_LOW;
            }
            else if(c_strcmp(str,"Medium") == 0)
            {
                i2_set_val = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_MEDIUM;
            }
            else if(c_strcmp(str,"High") == 0)
            {
                i2_set_val = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_HIGH;
            }
            REST_LOG_I("set val:%d\n\r", i2_set_val);
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), &i2_get_val);
            if(i2_get_val == i2_set_val)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR), i2_set_val);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_LIGHT_SENSOR));

            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 backlight(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_val = -1;
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            i4_val = menu_get_vid_back_light_val();
            if(i4_val<0)
            {
                REST_LOG_E("Invailed return %d\n", i4_val);
                break;
            }
            REST_LOG_I("get val:%d\n\r", i4_val);
            value_set_response(response, i4_val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value message = root["message"];
            i4_val = message["VALUE"].asInt();

            menu_set_vid_back_light_val(i4_val);
            REST_LOG_I("set val:%d\n\r", i4_val);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;
            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.i4_value = i4_val;

            if(ACFG_CUST_CONTENT_SDR != a_acfg_cust_get_dynamic_range())
            {
                t_toast.style.style_1.ui4_id = MLM_SETTINGS_KEY_VID_TONE_MAPPING;
            }
            else if(a_cfg_cust_oled_support())
            {
                t_toast.style.style_1.ui4_id = MLM_SETTINGS_KEY_VID_OLED_LUMINANCE;
            }
            else
            {
                t_toast.style.style_1.ui4_id = MLM_SETTINGS_KEY_VID_BAK;
            }

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 tone_mapping(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return backlight(root, response);
}

INT32 luminance(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return backlight(root, response);;
}

INT32 picture_aspect(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return aspect_ratio(root,response);
}


INT32 brightness(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            rest_config_get_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI, &val);
            REST_LOG_I("get val:%d\n\r", val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            val  = value_get_value(root);
            REST_LOG_I("set val:%d\n\r", val);
            rest_config_set_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI, val);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_BRI;
            t_toast.style.style_1.i4_value      = val;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 contrast(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            rest_config_get_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT, &val);
            REST_LOG_I("get val:%d\n\r", val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            val  = value_get_value(root);
            REST_LOG_I("set val:%d\n\r", val);
            rest_config_set_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CNT, val);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_CNT;
            t_toast.style.style_1.i4_value      = val;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            rest_config_get_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT, &val);
            REST_LOG_I("get val:%d\n\r", val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            val  = value_get_value(root);
            rest_config_set_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SAT, val);
            REST_LOG_I("set val:%d\n\r", val);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_SAT;
            t_toast.style.style_1.i4_value      = val;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 tint(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    INT32 i4_val_min = 0;
    INT32 i4_val_max = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            rest_config_get_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE, &val);
            REST_LOG_I("get val:%d\n\r", val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            val  = value_get_value(root);
            rest_config_set_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_HUE, val);
            REST_LOG_I("set val:%d\n\r", val);

            rest_config_get_min_max_value(APP_CFG_GRPID_VIDEO,APP_CFG_RECID_VID_HUE,&i4_val_min, &i4_val_max);
            REST_LOG_I("min:%d,max:%d\n\r", i4_val_min,i4_val_max);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_HUE;
            t_toast.style.style_1.i4_value      = val;
            t_toast.style.style_1.i4_max_val    = i4_val_max;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 sharpness(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            rest_config_get_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP, &val);
            REST_LOG_I("get val:%d\n\r", val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            val  = value_get_value(root);
            rest_config_set_value(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_SHP, val);
            REST_LOG_I("set val:%d\n\r", val);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_SHP;
            t_toast.style.style_1.i4_value      = val;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 color_calibration_picture_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            INT16  i2_pic_mode_idx = 0;
            CHAR name[64] = {0};

            i2_pic_mode_idx = menu_get_vid_pic_mode_idx();
            REST_LOG_I("Current pic mode idx:%d\n\r", i2_pic_mode_idx);

            get_vid_pic_mode_text(i2_pic_mode_idx, name, 64);
            REST_LOG_I("Pic mode name:%s\n\r", name);

            string_set_response(response,name);
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

//dolphin 20200403 add
INT32 super_resolution(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32	 type = 0;
    INT32 i4_ret = 0;
    WDK_TOAST_T t_toast;

    enum _resolution_type
    {
        _OFF = 0,
        _LOW,
        _MID,
        _HIGH,
        _TYPE_MAX,
    };

    Json::Value j_level;
    j_level[_OFF] = "Off";
    j_level[_LOW] = "Low";
    j_level[_MID] = "Medium";
    j_level[_HIGH] = "High";

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16 i2_val = 0;
            i2_val = menu_get_vid_super_resolution_idx();
            if(i2_val<0)
            {
                REST_LOG_E("Invailed return\n");
                i4_ret = -1;
                break;
            }
            response["VALUE"]=j_level[i2_val];
            response["ELEMENTS"] = j_level;
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
           INT32	 type = 0;
           INT16	 i2_pre_val = 0;
           INT16	 i2_val  = -1;
           memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
           t_toast.e_toast_style  = WDK_STRING_TOAST;
           t_toast.e_string_style = WDK_STRING_ID_ID;
           t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_SUPER_RESOLUTION;

           Json::Value message = root["message"];
           Json::Value value = message["VALUE"];

           for(int i=0;i<_TYPE_MAX;i++)
           {
               if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
               {
                   i2_val = i;
                   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF + i;
                   break;
               }
           }

           if(i2_val==-1)
           {
               REST_LOG_E("Get invailed arguments %s\n",value.asString());
               i4_ret = -1;
               break;
           }
           rest_send_msg_to_nav(&t_toast);
           menu_set_vid_super_resolution_idx(i2_val);
           menu_pm_repaint();
           break;
        }
        default:
        break;
    }
    return i4_ret;
}

INT32 edge_enhancement(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT32 i4_ret = 0;
    WDK_TOAST_T t_toast;

    enum _resolution_type
    {
        _OFF = 0,
        _LOW,
        _MID,
        _HIGH,
        _TYPE_MAX,
    };

    Json::Value j_level;
    j_level[_OFF] = "Off";
    j_level[_LOW] = "Low";
    j_level[_MID] = "Medium";
    j_level[_HIGH] = "High";

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16 i2_val = 0;
            i2_val = menu_get_vid_edge_enhancement_idx();
            if(i2_val<0)
            {
                REST_LOG_E("Invailed return\n");
                i4_ret = -1;
                break;
            }

            response["VALUE"]=j_level[i2_val];
            response["ELEMENTS"] = j_level;
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
           INT32	 type = 0;
           INT16	 i2_pre_val = 0;
           INT16	 i2_val  = -1;
           memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
           t_toast.e_toast_style  = WDK_STRING_TOAST;
           t_toast.e_string_style = WDK_STRING_ID_ID;
           t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_EDGE_ENHANCEMENT;

           Json::Value message = root["message"];
           Json::Value value = message["VALUE"];

           for(int i=0;i<_TYPE_MAX;i++)
           {
               if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
               {
                   i2_val = i;
                   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF + i;
                   break;
               }
           }

           if(i2_val==-1)
           {
               REST_LOG_E("Get invailed arguments %s\n",value.asString());
               i4_ret = -1;
               break;
           }
           rest_send_msg_to_nav(&t_toast);
           menu_set_vid_edge_enhancement_idx(i2_val);
           menu_pm_repaint();
           break;
        }
        default:
        break;
    }
    return i4_ret;
}

INT32 local_contrast(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32	 type = 0;
    INT32 i4_ret = 0;
    WDK_TOAST_T t_toast;

    enum _resolution_type
    {
        _OFF = 0,
        _LOW,
        _MID,
        _HIGH,
        _TYPE_MAX,
    };
  
    Json::Value j_level;
    j_level[_OFF] = "Off";
    j_level[_LOW] = "Low";
    j_level[_MID] = "Medium";
    j_level[_HIGH] = "High";

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16 i2_val = 0;
            i2_val = menu_get_vid_local_contrast_idx();
            if(i2_val<0)
            {
                REST_LOG_E("Invailed return\n");
                i4_ret = -1;
                break;
            }

            response["VALUE"]=j_level[i2_val];
            response["ELEMENTS"] = j_level;
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
           INT32	 type = 0;
           INT16	 i2_pre_val = 0;
           INT16	 i2_val  = -1;
           memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
           t_toast.e_toast_style  = WDK_STRING_TOAST;
           t_toast.e_string_style = WDK_STRING_ID_ID;
           t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_LOCAL_CONTRAST;

           Json::Value message = root["message"];
           Json::Value value = message["VALUE"];

           for(int i=0;i<_TYPE_MAX;i++)
           {
               if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
               {
                   i2_val = i;
                   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF + i;
                   break;
               }
           }

           if(i2_val==-1)
           {
               REST_LOG_E("Get invailed arguments %s\n",value.asString());
               i4_ret = -1;
               break;
           }
           rest_send_msg_to_nav(&t_toast);
           menu_set_vid_local_contrast_idx(i2_val);

           break;
        }
        default:
        break;
    }
    return i4_ret;
}

INT32 peak_luminance(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32	 type = 0;
    INT32 i4_ret = 0;
    WDK_TOAST_T t_toast;

    enum _resolution_type
    {
        _LOW = 0,
        _MID,
        _HIGH,
        _TYPE_MAX,
    };

    Json::Value j_level;
    j_level[_LOW] = "Low";
    j_level[_MID] = "Medium";
    j_level[_HIGH] = "High";

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16 i2_val = 0;
            //0--Low   1--Middle   2--High
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_PEAK_LUMINANCE), &i2_val);
            if(i2_val<0)
            {
                REST_LOG_E("Invailed return\n");
                i4_ret = -1;
                break;
            }

            response["VALUE"]=j_level[i2_val];
            response["ELEMENTS"] = j_level;
            break;
        }
        //READ ONLY
        case argument::RequestType::REQUEST_SET:
        {
           INT32	 type = 0;
           INT16	 i2_pre_val = 0;
           INT16	 i2_val  = -1;
           memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
           t_toast.e_toast_style  = WDK_STRING_TOAST;
           t_toast.e_string_style = WDK_STRING_ID_ID;
           t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_PEAK_LUMINANCE;

           Json::Value message = root["message"];
           Json::Value value = message["VALUE"];
		   REST_LOG_E("set peak_luminance %s\n", value.asString().c_str());

           for(int i=0;i<_TYPE_MAX;i++)
           {
               if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
               {
                   i2_val = i;
                   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_LOW + i;
                   break;
               }
           }

           if(i2_val==-1)
           {
               REST_LOG_E("Get invailed arguments %s\n",value.asString().c_str());
               i4_ret = -1;
               break;
           }
           rest_send_msg_to_nav(&t_toast);
           menu_set_vid_peak_luminance_idx(i2_val);
           menu_pm_repaint();

           break;
        }
        default:
        break;
    }
    return i4_ret;
}

INT32 variable_refresh_rate(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;

	enum _resolution_type
	{
		_OFF = 0,
		_ON,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_OFF] = "Off";
	j_level[_ON] = "On";

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			INT16 i2_val = 0;
			i2_val = menu_get_vid_vss_idx();
			if(i2_val<0)
			{
				REST_LOG_E("Invailed return\n");
				i4_ret = -1;
				break;
			}
			response["VALUE"]=j_level[i2_val];
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
		   t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_VARIABLE_REFRESH_RATE;

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
		   menu_set_vid_vss_idx(i2_val);
		   rest_send_msg_to_nav(&t_toast);
		   menu_pm_repaint();

		   break;
		}
		default:
		break;
	}
	return i4_ret;
}

INT32 game_hdr(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;

	enum _resolution_type
	{
		_OFF = 0,
		_ON,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_OFF] = "Off";
	j_level[_ON] = "On";

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			UINT16 i2_val = 0;
			i2_val = menu_get_vid_game_hdr_idx();
			if(i2_val<0)
			{
				REST_LOG_E("Invailed return\n");
				i4_ret = -1;
				break;
			}
			response["VALUE"] = j_level[i2_val];
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
		   t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_GAME_HDR;

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

		   if(i2_val == -1)
		   {
			   REST_LOG_E("Get invailed arguments %s\n",value.asString());
			   i4_ret = -1;
			   break;
		   }
		   menu_set_vid_game_hdr_idx(i2_val);
		   rest_send_msg_to_nav(&t_toast);
		   menu_pm_repaint();

		   break;
		}
		default:
		break;
	}
	return i4_ret;
}

INT32 contour_smoothing(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;

	enum _resolution_type
	{
		_OFF = 0,
		_LOW,
		_MID,
		_HIGH,
		_TYPE_MAX,
	};

	Json::Value j_level;
	j_level[_OFF] = "Off";
	j_level[_LOW] = "Low";
	j_level[_MID] = "Medium";
	j_level[_HIGH] = "High";

	INT16 i2_get_val = 0;
	i2_get_val = menu_get_vid_contour_smoothing_idx();

	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			if(i2_get_val<0)
			{
				REST_LOG_E("Invailed return\n");
				i4_ret = -1;
				break;
			}
			response["VALUE"]=j_level[i2_get_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		//READ ONLY
		case argument::RequestType::REQUEST_SET:
		{
		   INT32	 type = 0;
		   INT16	 i2_pre_val = 0;
		   INT16	 i2_val  = -1;
		   memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
		   t_toast.e_toast_style  = WDK_STRING_TOAST;
		   t_toast.e_string_style = WDK_STRING_ID_ID;
		   t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_CONTOUR_SMOOTHING;

		   Json::Value message = root["message"];
		   Json::Value value = message["VALUE"];
		   
		   for(int i=0;i<_TYPE_MAX;i++)
		   {
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF+i;
				   i2_val = i;
				   break;
			   }
		   }

		   if(i2_val==-1)
		   {
			   REST_LOG_E("Get invailed arguments %s\n", value.asString());
			   i4_ret = -1;
			   break;
		   }

		   if(i2_get_val == i2_val)
		   {
			   break;
		   }

		   REST_LOG_I("set contour smoothing %s.\n\r", j_level[i2_val].asString().c_str());
		   menu_set_vid_contour_smoothing_idx(i2_val);
		   rest_send_msg_to_nav(&t_toast);
		   menu_pm_repaint();

		   break;
		}
		default:
		break;
	}
	return i4_ret;
}

INT32 color_calibration_color_temperature(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    return more_picture_color_temperature(root,response);
}

INT32 color_calibration_calibration_tests_smpte_test_pattern(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16	i2_val = 0;

            Json::Value items;
            items[0] = "Off";
            items[1] = "On";

            response["ELEMENTS"] = items;
            i2_val = menu_get_current_smpte_test_pattern_value();
            response["VALUE"] = items[i2_val];
            REST_LOG_I("smpte_test_pattern idx:%d\n\r", i2_val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            if( rest_set_test_pattern_turn_off_in_cast())
            {
                break;
            }

            CHAR    str[128] = {0};
            //WDK_TOAST_T t_toast;
            UINT16       ui2_set_val = 0;

            //memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            //t_toast.e_toast_style  = WDK_STRING_TOAST;
            //t_toast.e_string_style = WDK_STRING_ID_ID;
            //t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_SMPTE_TEST_PATTERN;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("smpte_test_pattern str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                ui2_set_val = 0;
                //t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                ui2_set_val = 1;
                //t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            menu_smpte_test_pattern_set_value_by_id(ui2_set_val);
            menu_smpte_test_pattern_update_txt(FALSE);
            color_tuner_rgb_update();
            //rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 color_calibration_calibration_tests_flat_test_pattern(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_val = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8   ui1_indx = 0;
            Json::Value items;
            items[0] = "Off";

            for(ui1_indx = 1; ui1_indx < 11; ui1_indx++)
            {
                CHAR    ac_val[8] = {0};
                snprintf(ac_val, 7, "%d", ui1_indx*10);
                c_strncat(ac_val,"%",1);
                items[ui1_indx] = std::string(ac_val);
            }
            response["ELEMENTS"] = items;
            i2_val = flat_test_pattern_get_value();
            response["VALUE"] = items[i2_val];
            REST_LOG_I("flat_test_pattern idx:%d\n\r", i2_val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            if( rest_set_test_pattern_turn_off_in_cast())
            {
                break;
            }

            CHAR    str[128] = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_FLAT_TEST_PATTERN;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            flat_test_pattern_set_value(str,&t_toast);
            color_tuner_rgb_update();

            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 color_calibration_calibration_tests_ramp_test_pattern(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    UINT16  ui2_val = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "White";
            items[2] = "Red";
            items[3] = "Green";
            items[4] = "Blue";
            response["ELEMENTS"] = items;

            ramp_test_pattern_get_value(&ui2_val);
            response["VALUE"] = items[ui2_val];
            REST_LOG_I("ramp_test_pattern idx:%d\n\r", ui2_val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            if( rest_set_test_pattern_turn_off_in_cast())
            {
                break;
            }

            CHAR    str[128] = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_RAMP_TEST_PATTERN_TITLE;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            if(c_strcmp(str,"Off") == 0)
            {
                ui2_val = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"White") == 0)
            {
                ui2_val = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE;
            }
            else if(c_strcmp(str,"Red") == 0)
            {
                ui2_val = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED;
            }
            else if(c_strcmp(str,"Green") == 0)
            {
                ui2_val = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN;
            }
            else if(c_strcmp(str,"Blue") == 0)
            {
                ui2_val = 4;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE;
            }
            ramp_test_pattern_set_value(ui2_val,&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 color_calibration_calibration_tests_uniformity_analyzer_test_pattern(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16 i2_val = 0;

            Json::Value items;
            items[0] = "Off";
            items[1] = "On";

            response["ELEMENTS"] = items;
            i2_val = menu_get_current_uniformity_analyzer_test_pattern_value();
            response["VALUE"] = items[i2_val];
            REST_LOG_I("get current uniformity analyzer test pattern value:%d\n\r", i2_val);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            if( rest_set_test_pattern_turn_off_in_cast())
            {
                break;
            }

            CHAR    str[128] = {0};
            //WDK_TOAST_T t_toast;
            UINT16       ui2_set_val = 0;

            //memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            //t_toast.e_toast_style  = WDK_STRING_TOAST;
            //t_toast.e_string_style = WDK_STRING_ID_ID;
            //t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_UNIFANA_TEST_PATTERN;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                ui2_set_val = 0;
                //t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                ui2_set_val = 1;
                //t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            menu_uniformity_analyzer_test_pattern_set_value_by_id(ui2_set_val);
            menu_uniformity_analyzer_test_pattern_update_txt(FALSE);
            color_tuner_rgb_update();
            //rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 color_calibration_calibration_tests_dolby_vision_test_pattern(Json::Value & root, Json::Value & response){return 0;}
INT32 color_calibration_reset_color_tuner(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT16   i2_clr_temp = 0;
    WDK_TOAST_T t_toast;
    UTF16_T     w2s_string[256]  = {0};

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_clr_temp);
    a_cfg_reset_clr_tuner(i2_clr_temp);

    a_cfg_custom_set_rgb_on_off(1,1,1);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));
    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN));

    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;

    c_uc_w2s_strcpy(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_COLOR_TUNER_RESET));

    t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

    rest_send_msg_to_nav(&t_toast);

    return 0;
}

//color: 0-red , 1-green , 2-blue
INT32 color_tuner_table_header(Json::Value & root, Json::Value & response, INT32 color)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    INT16 i2OnOff = 0;

    enum _COLOR
    {
        _RED = 0,
        _GREEN,
        _BLUE,
    };

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "On";
            response["ELEMENTS"] = items;
            if(color == _RED)
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_RED), &i2OnOff);
            }
            else if(color == _GREEN)
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GREEN), &i2OnOff);
            }
            else if(color == _BLUE)
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BLUE), &i2OnOff);
            }
            response["VALUE"] = items[i2OnOff];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT16 i2_val = 0;
            CHAR  str[128] = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            if(color == _RED)
            {
                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_PIC_RED_COLOR;
            }
            else if(color == _GREEN)
            {
                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_PIC_GREEN_COLOR;
            }
            else if(color == _BLUE)
            {
                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_PIC_BLUE_COLOR;
            }

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            if(c_strcmp(str,"Off") == 0)
            {
                i2_val = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                i2_val = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            else
            {
                REST_LOG_E("Get invailed arguments %s\n", str);
                i4_ret = -1;
                break;
            }
            color_calibration_set_color_tuner_table_header(color,i2_val,&t_toast);
            rest_set_preset_pic_mode_chg_status(TRUE);

            break;
        }
        default:
            break;
    }
    return i4_ret;
}

INT32 color_calibration_color_tuner_color_tuner_table_header_red(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return color_tuner_table_header(root, response, 0);
}

INT32 color_calibration_color_tuner_color_tuner_table_header_green(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return color_tuner_table_header(root, response, 1);
}

INT32 color_calibration_color_tuner_color_tuner_table_header_blue(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return color_tuner_table_header(root, response, 2);
}

static VOID _color_tuner_table_setting(Json::Value & root, Json::Value & response,
                                       UINT16 ui2_recid, UINT32 ui4_mlmid)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_get_val  = 0;
    INT32 i4_set_val  = 0;
    INT32 i4_val_min = 0;
    INT32 i4_val_max = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            rest_config_get_value(APP_CFG_GRPID_VIDEO, ui2_recid, &i4_get_val);
            REST_LOG_I("get val:%d\n\r", i4_get_val);
            value_set_response(response, i4_get_val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            i4_set_val  = value_get_value(root);
            REST_LOG_I("set val:%d\n\r", i4_set_val);

            rest_config_set_value(APP_CFG_GRPID_VIDEO, ui2_recid,i4_set_val);

            rest_config_get_min_max_value(APP_CFG_GRPID_VIDEO,ui2_recid,&i4_val_min, &i4_val_max);
            REST_LOG_I("min:%d,max:%d\n\r", i4_val_min,i4_val_max);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = ui4_mlmid;
            t_toast.style.style_1.i4_value      = i4_set_val;
            t_toast.style.style_1.i4_max_val    = i4_val_max;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return;
}

INT32 color_calibration_color_tuner_color_tuner_table_hue_red(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_HUE_R, MLM_SETTINGS_KEY_VID_HUE_RED);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_hue_green(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_HUE_G, MLM_SETTINGS_KEY_VID_HUE_GREEN);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_hue_blue(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_HUE_B, MLM_SETTINGS_KEY_VID_HUE_BLUE);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_hue_cyan(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_HUE_C, MLM_SETTINGS_KEY_VID_HUE_CYAN);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_hue_magenta(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_HUE_M, MLM_SETTINGS_KEY_VID_HUE_MAGENTA);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_hue_yellow(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_HUE_Y, MLM_SETTINGS_KEY_VID_HUE_YELLOW);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_saturation_red(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_SAT_R, MLM_SETTINGS_KEY_VID_SAT_RED);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_saturation_green(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_SAT_G, MLM_SETTINGS_KEY_VID_SAT_GREEN);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_saturation_blue(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_SAT_B, MLM_SETTINGS_KEY_VID_SAT_BLUE);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_saturation_cyan(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_SAT_C, MLM_SETTINGS_KEY_VID_SAT_CYAN);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_saturation_magenta(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_SAT_M, MLM_SETTINGS_KEY_VID_SAT_MAGENTA);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_saturation_yellow(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_SAT_Y, MLM_SETTINGS_KEY_VID_SAT_YELLOW);
    return 0;
}


INT32 color_calibration_color_tuner_color_tuner_table_brightness_red(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_BRI_R, MLM_SETTINGS_KEY_VID_BRI_RED);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_brightness_green(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_BRI_G, MLM_SETTINGS_KEY_VID_BRI_GREEN);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_brightness_blue(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_BRI_B, MLM_SETTINGS_KEY_VID_BRI_BLUE);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_brightness_cyan(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_BRI_C, MLM_SETTINGS_KEY_VID_BRI_CYAN);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_brightness_magenta(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_BRI_M, MLM_SETTINGS_KEY_VID_BRI_MAGENTA);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_brightness_yellow(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CLR_BRI_Y, MLM_SETTINGS_KEY_VID_BRI_YELLOW);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_offset_red(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CUST_CLR_OFFSET_R, MLM_SETTINGS_KEY_VID_OFFSET_RED);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_offset_green(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CUST_CLR_OFFSET_G, MLM_SETTINGS_KEY_VID_OFFSET_GREEN);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_offset_blue(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CUST_CLR_OFFSET_B, MLM_SETTINGS_KEY_VID_OFFSET_BLUE);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_gain_red(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CUST_CLR_GAIN_R, MLM_SETTINGS_KEY_VID_GAIN_RED);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_gain_green(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CUST_CLR_GAIN_G, MLM_SETTINGS_KEY_VID_GAIN_GREEN);
    return 0;
}

INT32 color_calibration_color_tuner_color_tuner_table_gain_blue(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _color_tuner_table_setting(root, response, APP_CFG_RECID_VID_CUST_CLR_GAIN_B, MLM_SETTINGS_KEY_VID_GAIN_BLUE);
    return 0;
}


INT32 more_picture_color_temperature(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_get_idx = 0;
    INT16   i2_set_idx = 0;
    CHAR    str[128] = {0};
    BOOL    b_is_chg = 0;
    WDK_TOAST_T t_toast;
    CHAR    s_color_temp[3][64];
    CHAR    s_color_temp_ex[3][64];
    UTF16_T w2s_tmp_str[64] = {0};
    INT16   i2_clr[3] = {ACFG_CUST_CLR_TEMP_WARM,ACFG_CUST_CLR_TEMP_COOL,ACFG_CUST_CLR_TEMP_NORMAL};
    INT16   i2_mlm_id[3] = {MLM_SETTINGS_KEY_VID_CLR_TEMP_WARM,
                            MLM_SETTINGS_KEY_VID_CLR_TEMP_COOL,
                            MLM_SETTINGS_KEY_VID_CLR_TEMP_NORMAL};
    INT16   i2_mlm_ex_id[3] = {MLM_SETTINGS_KEY_VID_CLR_TEMP_WARM_EX,
                               MLM_SETTINGS_KEY_VID_CLR_TEMP_COOL_EX,
                               MLM_SETTINGS_KEY_VID_CLR_TEMP_NORMAL_EX};

    for (INT32 i=0; i<3; i++)
    {
        c_memset(w2s_tmp_str, 0, 64);
        c_uc_w2s_strcpy(w2s_tmp_str,REST_SETTINGS_TEXT(i2_mlm_id[i]));
        c_uc_w2s_to_ps(w2s_tmp_str,s_color_temp[i],64);

        c_strcpy(s_color_temp_ex[i],s_color_temp[i]);
        c_strncat(s_color_temp_ex[i],"*",1);
    }

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value temperature;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_get_idx);
#ifdef APP_CFG_LIGHT_SENSOR_GAMMA_SUPPORT
            a_cfg_custom_set_light_sensor_GAMMA_index(i2_get_idx);
#endif
            REST_LOG_I("get idx:%d\n\r", i2_get_idx);
            switch (i2_get_idx)
            {
                case ACFG_CUST_CLR_TEMP_WARM:
                    i2_get_idx = 0;
                    break;
                case ACFG_CUST_CLR_TEMP_COOL:
                    i2_get_idx = 1;
                    break;
                case ACFG_CUST_CLR_TEMP_NORMAL:
                    i2_get_idx = 2;
                    break;
                default:
                    i2_get_idx = 0;
                    break;
            }

            for (INT32 i=0; i<3; i++)
            {
                a_cfg_get_clr_temp_chg_status(i2_clr[i],&b_is_chg);
                REST_LOG_I("b_is_chg:%d\n\r", b_is_chg);
                if(b_is_chg)
                {

                    c_strncat(s_color_temp[i],"*",1);
                    REST_LOG_I("color_temp:%d\n\r", s_color_temp[i]);
                }
                temperature[i] = std::string(s_color_temp[i]);
            }
            response["ELEMENTS"] = temperature;
            response["VALUE"] = temperature[i2_get_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_CLR_TEMP;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);

            b_is_chg = FALSE;
            if(c_strstr(str,"*"))
            {
                b_is_chg = TRUE;
                REST_LOG_I("b_is_chg:%d\n\r", b_is_chg);
            }

            for(INT32 i=0; i<3; i++)
            {
                if(c_strncmp(str,s_color_temp_ex[i],c_strlen(str)) == 0)
                {
                    i2_set_idx = i2_clr[i];
                    if(b_is_chg)
                    {
                        t_toast.style.style_2.ui4_id_2 = i2_mlm_ex_id[i];
                    }
                    else
                    {
                        t_toast.style.style_2.ui4_id_2 = i2_mlm_id[i];
                    }
                }
            }

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP), &i2_get_idx);
            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP),i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_CLR_TEMP));

            color_tuner_rgb_update();
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_11_POINT_GAIN));

            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }
    return 0;
}


INT32 more_picture_active_full_array(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    BOOL b_support     = FALSE;
    b_support = a_cfg_cust_get_support_local_dimming();
    
    enum _local_dimming_type
    {
        _OFF = 0,
        _LOW,
        _MID,
        _HIGH,
        _TYPE_MAX,
    };
    
    enum _non_local_dimming_type
    {
        _N_OFF = 0,
        _N_ON,
        _TYPE_N_MAX,
    };
    
    Json::Value j_local_dimming;
    j_local_dimming[_OFF] = "Off";
    j_local_dimming[_LOW] = "Low";
    j_local_dimming[_MID] = "Medium";
    j_local_dimming[_HIGH] = "High";
    
    Json::Value j_non_local_dimming;
    j_non_local_dimming[_N_OFF] = "Off";
    j_non_local_dimming[_N_ON] = "On";
    
    type = get_type(root);
    
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT16 ui2_val = 0;
            
            ui2_val = menu_get_local_dimming_idx();
            
            if(b_support)
            {
                response["VALUE"]=j_local_dimming[ui2_val];
                response["ELEMENTS"] = j_local_dimming;
            }
            else
            {
                response["VALUE"]=j_non_local_dimming[ui2_val];
                response["ELEMENTS"] = j_non_local_dimming;
            }
            
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            UINT8 ui1_tmp_val = 0;
            INT16 i2_val  = -1;
            WDK_TOAST_T t_toast;
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_LOCAL_DEMMING_ACTIVE_FULL_ARRAY;

            ui1_tmp_val = a_smart_dim_get_assume_val();
            
            Json::Value message = root["message"];
            Json::Value value = message["VALUE"];

            DBG_INFO( ("%s:%d: set APP_CFG_RECID_VID_CUSTOM_DIMMING to %s.\n", __FUNCTION__, __LINE__, value.asString().c_str()));

            if(b_support)
            {
                for(int i=0;i<_TYPE_MAX;i++)
                {
                    if(strcmp(j_local_dimming[i].asString().c_str(),value.asString().c_str())==0)
                    {
                         i2_val = i;
                         t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF + i;
                         break;
                    }
                }
            }
            else
            {
                for(int i=0;i<_TYPE_N_MAX;i++)
                {
                    if(strcmp(j_non_local_dimming[i].asString().c_str(),value.asString().c_str())==0)
                    {
                         i2_val = i;
                         t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF - i;
                         break;
                    }
                }        
            }
            
            if(i2_val==-1)
            {
                REST_LOG_E("Get invailed arguments %s\n",value.asString().c_str());
                i4_ret = -1;
                break;
            }
            menu_set_local_dimming_idx((INT16)i2_val);
            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
            break;
        }
        default:
        break;
    }
    return i4_ret;
}

INT32 more_picture_black_detail(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = 0;
    INT32 type = 0;
    INT16 i2_get_idx = 0;
    INT16 i2_set_idx = -1;
    CHAR str[128] = {0};
    WDK_TOAST_T t_toast;

    enum _black_detail_value
    {
        _OFF= 0,
        _LOW,
        _MEDIUM,
        _HIGH,
        _TYPE_MAX
    };

    Json::Value j_level;
    j_level[_OFF] = "Off";
    j_level[_LOW] = "Low";
    j_level[_MEDIUM] = "Medium";
    j_level[_HIGH] = "High";

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN), &i2_get_idx);

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            response["ELEMENTS"] = j_level;
            REST_LOG_I("get current black detail idx:%d\n\r", i2_get_idx);
            response["VALUE"] = j_level[i2_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_VID_BLK_DETAIL;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);

            for(int i=0;i<_TYPE_MAX;i++)
            {
                if(strcmp(j_level[i].asString().c_str(),str)==0)
                {
                    i2_set_idx = i;
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF + i;
                    break;
                }
            }
            if(i2_set_idx == -1)
            {
                REST_LOG_E("Get invailed arguments %s\n", str);
                i4_ret = -1;
                break;
            }

            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN), i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CONTRAST_EN));
            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return i4_ret;
}

INT32 more_picture_active_led_zones(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_set_idx = 0;
    UINT16  ui2_get_idx = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;
	BOOL b_support = FALSE;
	INT16 i2_val = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "Low";
            items[2] = "Medium";
            items[3] = "High";
            response["ELEMENTS"] = items;
            //a_cfg_custom_get_is_support_local_dimming(&b_support);
            b_support = a_cfg_cust_get_support_local_dimming();
			if(b_support)
			{
				a_cfg_custom_get_dimming_idx(&ui2_get_idx);
			}
			else
			{
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_val);
				ui2_get_idx = (UINT16)i2_val;
			}

            REST_LOG_I("get idx:%d\n\r", ui2_get_idx);
            response["VALUE"] = items[ui2_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = a_cfg_get_local_dimming_mlm_string();

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                i2_set_idx   = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"Low") == 0)
            {
                i2_set_idx  = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_LOW;
            }
            else if(c_strcmp(str,"Medium") == 0)
            {
                i2_set_idx  = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_MEDIUM;
            }
            else if(c_strcmp(str,"High") == 0)
            {
                i2_set_idx  = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_HIGH;
            }
            //a_cfg_custom_get_is_support_local_dimming(&b_support);
            b_support = a_cfg_cust_get_support_local_dimming();
			if(b_support)
			{
				a_cfg_custom_get_dimming_idx(&ui2_get_idx);
			}
			else
			{
				a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_val);
				ui2_get_idx = (UINT16)i2_val;
			}
            if(ui2_get_idx == (UINT16)i2_set_idx)
            {
                break;
            }

            if(b_support)
			{
			    REST_LOG_I("%s:%d: set APP_CFG_RECID_VID_CUSTOM_DIMMING to 0x%02x\n",
			                __FUNCTION__, __LINE__, i2_set_idx);

			    /* set the value to the EEPROM acfg partition */
				a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING), (INT16)i2_set_idx);

				a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));

			}
			else
			{
			    /*
			     * if we have dcr support, the the DCR_ID val will be: 0: off, 1: DCR, 2: OPC
			     * else, it will be 0: off, 1: OPC
			     */

			    REST_LOG_I("%s:%d: set APP_CFG_RECID_VID_CUSTOM_DCR to 0x%02x\n",
			                __FUNCTION__, __LINE__, i2_set_idx);
			    /* set the value to the EEPROM acfg partition */
			    a_cfg_av_set (CFG_MAKE_ID (APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), i2_set_idx);
			    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));
#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
			    a_cfg_custom_plf_opt_set_dcr_setting(i2_set_idx);
#endif

			}
            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 more_picture_backlight_control(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT16 i2_get_idx = 0;
    INT16 i2_set_idx = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "On";
            response["ELEMENTS"] = items;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_get_idx);
            if(i2_get_idx == 2) //if dcr support, the DCR_ID val will be: 0: off, 1: DCR, 2: OPC
            {
              i2_get_idx = 1;
            }
            REST_LOG_I("get idx:%d\n\r", i2_get_idx);
            response["VALUE"] = items[i2_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_BACK_LIGHT_CTRL;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                i2_set_idx  = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                i2_set_idx  = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_get_idx);
            if(i2_get_idx == 2) //if dcr support, the DCR_ID val will be: 0: off, 1: DCR, 2: OPC
            {
              i2_get_idx = 1;
            }

            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR),i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));
            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 more_picture_reduce_judder(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    INT32 i4_val = 0;
    INT16 i2_val_min = 0;
    INT16 i2_val_max = 0;
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
#ifdef APP_SUPPPORT_FRC
            i4_val = menu_get_vid_judder_reduction_idx();
#endif
            REST_LOG_I("get judder_reduction val:%d\n\r", i4_val);
            value_set_response(response, i4_val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value message = root["message"];
            i4_val = message["VALUE"].asInt();
#ifdef APP_SUPPPORT_FRC
            a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_JUDDER_REDUCTION), &i2_val_min, &i2_val_max);
            menu_set_vid_judder_reduction_idx(i4_val);
            REST_LOG_I("max:%d , set judder_reduction val:%d\n\r", i2_val_max, i4_val);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;
            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.ui4_id = MLM_SETTINGS_KEY_VID_JUDDER_REDUCTION;
            t_toast.style.style_1.i4_max_val = (INT32)i2_val_max;
            t_toast.style.style_1.i4_value = i4_val;

            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
#endif
            break;
        }
        default:
            break;
    }

    return i4_ret;
}

INT32 more_picture_reduce_motion_blur(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    INT32 i4_val = 0;
    INT16 i2_val_min = 0;
    INT16 i2_val_max = 0;
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
#ifdef APP_SUPPPORT_FRC
            i4_val = menu_get_vid_motion_blur_reduction_idx();
#endif
            REST_LOG_I("get motion_blur_reduction val:%d\n\r", i4_val);
            value_set_response(response, i4_val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value message = root["message"];
            i4_val = message["VALUE"].asInt();
#ifdef APP_SUPPPORT_FRC
            a_cfg_av_get_min_max(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MOTION_BLUR_REDUCTION), &i2_val_min, &i2_val_max);
            menu_set_vid_motion_blur_reduction_idx(i4_val);
            REST_LOG_I("max:%d , set motion_blur_reduction val:%d\n\r", i2_val_max, i4_val);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;
            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.ui4_id = MLM_SETTINGS_KEY_VID_MOTION_BLUR_REDUCTION;
            t_toast.style.style_1.i4_max_val = (INT32)i2_val_max;
            t_toast.style.style_1.i4_value = i4_val;

            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
#endif
            break;
        }
        default:
            break;
    }

    return i4_ret;
}

INT32 more_picture_clear_action(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    UINT16   ui2_get_idx = 0;
    UINT16   ui2_set_idx = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "On";
            response["ELEMENTS"] = items;

            ui2_get_idx = menu_get_vid_clear_action_idx();
            REST_LOG_I("get idx:%d\n\r", ui2_get_idx);
            response["VALUE"] = items[ui2_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_CLEAR_ACTION;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                ui2_set_idx  = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                ui2_set_idx = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }

            menu_set_vid_clear_action_idx(ui2_set_idx);
            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 more_picture_reduce_signal_noise(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT16 i2_get_idx = 0;
    INT16 i2_set_idx = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "Low";
            items[2] = "Medium";
            items[3] = "High";
            response["ELEMENTS"] = items;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR), &i2_get_idx);
            REST_LOG_I("get idx:%d\n\r", i2_get_idx);
            response["VALUE"] = items[i2_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_REDUCE_SN;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                i2_set_idx  = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"Low") == 0)
            {
                i2_set_idx = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_LOW;
            }
            else if(c_strcmp(str,"Medium") == 0)
            {
                i2_set_idx = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_MEDIUM;
            }
            else if(c_strcmp(str,"High") == 0)
            {
                i2_set_idx = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_HIGH;
            }
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR), &i2_get_idx);
            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR), i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_NR));

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR), i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_NR));
            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 more_picture_reduce_block_noise(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT16 i2_get_idx = 0;
    INT16 i2_set_idx = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "Low";
            items[2] = "Medium";
            items[3] = "High";
            response["ELEMENTS"] = items;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR), &i2_get_idx);
            REST_LOG_I("get idx:%d\n\r", i2_get_idx);
            response["VALUE"] = items[i2_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_REDUCE_BN;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                i2_set_idx  = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"Low") == 0)
            {
                i2_set_idx = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_LOW;
            }
            else if(c_strcmp(str,"Medium") == 0)
            {
                i2_set_idx = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_MEDIUM;
            }
            else if(c_strcmp(str,"High") == 0)
            {
                i2_set_idx = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_HIGH;
            }
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR), &i2_get_idx);
            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR), i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_MPEG_NR));
            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 more_picture_game_low_latency(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_get_idx = 0;
    INT16   i2_set_idx = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;
    enum game_low_latency
    {
       t_AUTO=0,
       t_OFF,
       t_ON,
    };

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[t_AUTO] = "Auto";
            items[t_OFF] = "Off";
            items[t_ON] = "On";
            response["ELEMENTS"] = items;

            if(a_cfg_cust_is_support_game_low_latency())
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_get_idx);
            }
            else
            {
                i2_get_idx = t_OFF;
            }
            REST_LOG_I("get idx:%d\n\r", i2_get_idx);
            response["VALUE"] = items[i2_get_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_GAME_LOW_LATENCY;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                i2_set_idx  = t_OFF;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                i2_set_idx = t_ON;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            else if(c_strcmp(str,"Auto") == 0)
            {
                i2_set_idx = t_AUTO;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUTO;
            }

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), &i2_get_idx);
            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY), i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_GAME_LOW_LATENCY));

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));

            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 more_picture_film_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_get_idx = 0;
    INT16   i2_set_idx = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "On";
            response["ELEMENTS"] = items;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE), &i2_get_idx);

            if(i2_get_idx >= 1)
            {
                i2_get_idx = 1;
            }
            REST_LOG_I("get idx:%d\n\r", i2_get_idx);
            response["VALUE"] = items[i2_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_FILM_MODE;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                i2_set_idx  = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                i2_set_idx = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE), &i2_get_idx);

            if(i2_get_idx >= 1)
            {
                i2_get_idx = 1;
            }
            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE), i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_DI_FILM_MODE));
            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 more_picture_color_space(Json::Value & root, Json::Value & response)
{
     //N/A.
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    INT32 i4_ret = 0;
    CHAR s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8 ui1_input_id = 0;
    ISL_REC_T t_isl_rec;
    SCC_VID_HDR_TYPE_T t_acfg_hdr_type = SCC_VID_PQ_SDR;
    HANDLE_T  h_scc_comp;
    INT32    i4_dolby_vision = a_icl_custom_get_dolby_vision_status();

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    h_scc_comp = (c_strcmp(s_disp_name, SN_PRES_MAIN_DISPLAY) == 0) ? h_g_acfg_scc_main_vid : h_g_acfg_scc_sub_vid;
    c_scc_vid_get_hdr_type(h_scc_comp,&t_acfg_hdr_type);
    LOG_ON_ERR(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    LOG_ON_ERR(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    LOG_ON_ERR(i4_ret);

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            INT16 color_space = 0;

            Json::Value items;
            items[0] = "Auto";
            items[1] = "RGB";
            items[2] = "YCbCr";

            if ((t_isl_rec.t_avc_info.e_video_type != DEV_AVC_HDMI)||(SCC_VID_PQ_HDR10 == t_acfg_hdr_type)||(SCC_VID_PQ_HLG == t_acfg_hdr_type)
                ||(i4_dolby_vision == 1)
                )
            {
                color_space = 0;
            }
            else
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_COLOR_SPACE), &color_space);
                switch (color_space)
                {
                    case SCC_VID_COLORSPACE_AUTO:
                        color_space = 0;
                        break;
                    case SCC_VID_COLORSPACE_FORCE_RGB:
                        color_space = 1;
                        break;
                    case SCC_VID_COLORSPACE_FORCE_YCBCR:
                        color_space = 2;
                        break;
                    default:
                        color_space = 0;
                        break;
                }
            }

            response["ELEMENTS"] = items;
            response["VALUE"] = items[color_space];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            WDK_TOAST_T t_toast;
            INT16 color_space = 0;
            UINT16 	ui2_id = 0;
            CHAR str[128] = {0};
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_COLOR_SPACE;

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);

            if (c_strcmp(str, "Auto") == 0)
            {
                color_space = SCC_VID_COLORSPACE_AUTO;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUTO;
            }
            else if (c_strcmp(str, "RGB") == 0)
            {
                color_space = SCC_VID_COLORSPACE_FORCE_RGB;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_RGB;
            }
            else if (c_strcmp(str, "YCbCr") == 0)
            {
                color_space = SCC_VID_COLORSPACE_FORCE_YCBCR;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_YCBCR;
            }
            else
            {
                REST_LOG_E("Get invailed arguments %s\n", str);
                i4_ret = -1;
                break;
            }
            ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_COLOR_SPACE);
            a_cfg_av_set(ui2_id, color_space);
            a_cfg_av_update(ui2_id);

            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
            break;
        }
        default:
            break;
    }

    return i4_ret;
}

INT32 more_picture_gamma(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_get_idx = 0;
    INT16   i2_set_idx = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "1.8";
            items[1] = "2.0";
            items[2] = "2.1 - Normal";
            items[3] = "2.2";
            items[4] = "2.4";

            response["ELEMENTS"] = items;

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA), &i2_get_idx);
            REST_LOG_I("gamma i2_val:%d\n\r", i2_get_idx);
            response["VALUE"] = items[i2_get_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_GAMMA;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"1.8") == 0)
            {
                i2_set_idx  = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_GAMMA_1;
            }
            else if(c_strcmp(str,"2.0") == 0)
            {
                i2_set_idx = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_GAMMA_2;
            }
            else if(c_strncmp(str,"2.1",strlen("2.1")) == 0) //for 2.1 - Normal
            {
                i2_set_idx = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_GAMMA_3;
            }
            else if(c_strcmp(str,"2.2") == 0)
            {
                i2_set_idx = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_GAMMA_4;
            }
            else if(c_strcmp(str,"2.4") == 0)
            {
                i2_set_idx = 4;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_GAMMA_5;
            }
            else
            {
                REST_LOG_E("Get invailed arguments %s\n", str);
                i4_ret = -1;
                break;
            }
            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA), &i2_get_idx);
            if(i2_get_idx == i2_set_idx)
            {
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA),i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUST_GAMMA));
            rest_set_preset_pic_mode_chg_status(TRUE);

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }


    return i4_ret;
}

INT32 enhanced_viewing_angle(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_ret = 0;
    INT32 type = 0;
    INT16 i2_get_idx = -1;
    INT16 i2_set_idx = -1;
    WDK_TOAST_T t_toast;
    enum _EN_VIEW_ANGLE
    {
        _OFF = 0,
        _ON,
        _TYPE_MAX,
    };

    Json::Value j_level;
    j_level[_OFF] = "Off";
    j_level[_ON] = "On";

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), &i2_get_idx);
    REST_LOG_I("get current enhanced viewing angle idx:%d\n\r", i2_get_idx);

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            if(i2_get_idx<0)
            {
                REST_LOG_E("Invailed return\n");
                i4_ret = -1;
                break;
            }
            response["VALUE"] = j_level[i2_get_idx];
            response["ELEMENTS"] = j_level;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_ENHANCED_VIEWING_ANGLE;

            Json::Value message = root["message"];
            Json::Value value = message["VALUE"];

            for(int i=0;i<_TYPE_MAX;i++)
            {
                if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
                {
                    i2_set_idx = i;
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF - i;
                    break;
                }
            }

            if(i2_set_idx==-1)
            {
                REST_LOG_E("Get invailed arguments %s.\n", value.asString().c_str());
                i4_ret = -1;
                break;
            }

            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE), i2_set_idx);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_EN_VIEW_ANGLE));
            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
            break;
        }
        default:
            break;
    }
    return i4_ret;
}

INT32 picture_mode_edit_save_picture_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT16   i2_pic_mode = 0;
    UINT16  ui2_count = 0;
    CHAR    s_name[ACFG_MAX_DISP_NAME+1] = {0};
    BOOL    b_is_exist = FALSE;
    WDK_TOAST_T t_toast;
    UTF16_T w2s_string[256]  = {0};

    UINT16 ui2_pic_num = get_total_picture_mode_num();
    REST_LOG_I("total pic num:%d\n\r",ui2_pic_num);
    if(ui2_pic_num == ACFG_PRE_SET_PIC_MODE_NUM + ACFG_CUST_SET_PIC_MODE_NUM_EX)
    {
        c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
        t_toast.e_toast_style  = WDK_WARNING_TOAST;
        t_toast.e_string_style = WDK_STRING_STRING;
        c_uc_w2s_strcpy(w2s_string,REST_WARNINGS_TEXT(MLM_WARNINGS_KEY_WARNING_24));
        t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

        rest_send_msg_to_nav(&t_toast);
        return 6;
    }

    string_get_string(root, s_name, ACFG_MAX_DISP_NAME);

    if(c_strlen(s_name) != 0)
    {
        UTF16_T     w2s_str_name[64] = {0};
        UTF16_T     w2s_str_point[64] = {0};
        UTF16_T     w2s_str_pic[64]  = {0};
        UTF16_T     w2s_str_saved[64]  = {0};
        UTF16_T     w2s_str_is[8]  = {0};
        CHAR        str_point[8] = ".";

        memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

        menu_save_pic_btn_fct(s_name);

        t_toast.e_toast_style  = WDK_STRING_TOAST;
        t_toast.e_string_style = WDK_STRING_STRING;

        c_uc_w2s_strcpy(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_THE));

        if(rest_get_mlm_settings_lang_id() == 0)  /*english*/
        {
            c_uc_ps_to_w2s((const CHAR*)s_name, w2s_str_name, 63);
            c_uc_w2s_strncat(w2s_string,w2s_str_name,63);

            c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_LOW_CASE));
            c_uc_w2s_strncat(w2s_string,w2s_str_pic,63);
        }
        else
        {
            c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_LOW_CASE));
            c_uc_w2s_strncat(w2s_string,w2s_str_pic,63);

            c_uc_ps_to_w2s((const CHAR*)s_name, w2s_str_name, 63);
            c_uc_w2s_strncat(w2s_string,w2s_str_name,63);
        }

        c_uc_w2s_strcpy(w2s_str_is,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_IS_SE));
        c_uc_w2s_strncat(w2s_string,w2s_str_is,63);

        c_uc_w2s_strcpy(w2s_str_saved,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_SAVED));
        c_uc_w2s_strncat(w2s_string,w2s_str_saved,63);

        c_uc_ps_to_w2s((const CHAR*)str_point, w2s_str_point, 63);
        c_uc_w2s_strncat(w2s_string,w2s_str_point,63);

        t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

        rest_send_msg_to_nav(&t_toast);
    }

    return 0;
}

INT32 picture_mode_edit_lock_unlock_picture_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    BOOL  b_is_pic_mode_lock = FALSE;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16   i2_idx = 0;

            Json::Value items;
            items[0] = "Off";
            items[1] = "On";
            response["ELEMENTS"] = items;
            a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_pic_mode_lock);
            if(b_is_pic_mode_lock)
            {
                i2_idx = 1;
            }
            else
            {
                i2_idx = 0;
            }
            REST_LOG_I("idx: %d\n\r", i2_idx);
            response["VALUE"] = items[i2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            CHAR    str[128] = {0};
            UTF16_T     w2s_string[256]  = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("lock_unlock str: %s\n\r", str);

            a_cfg_cust_get_cust_pic_mode_lock_status(&b_is_pic_mode_lock);
            REST_LOG_I("b_is_pic_mode_lock: %d\n\r", b_is_pic_mode_lock);

            if(c_strcmp(str,"On") == 0)
            {
                a_cfg_cust_set_cust_pic_mode_lock_status(TRUE);
                c_uc_w2s_strcpy(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_ALL_PIC_MODE_LOCK));
            }
            else if(c_strcmp(str,"Off") == 0)
            {
                a_cfg_cust_set_cust_pic_mode_lock_status(FALSE);
                c_uc_w2s_strcpy(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_ALL_PIC_MODE_UNLOCK));
            }

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 picture_mode_edit_delete_picture_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   i4_ret = 0;
    INT16   i2_pic_mode = 0;
    INT16   i2_val = 0;
    UINT16  ui2_elem_idx = 0;

    WDK_TOAST_T t_toast;
    CHAR        s_name[64] = {0};
    UTF16_T     w2s_string[256]  = {0};
    UTF16_T     w2s_str_name[64] = {0};
    UTF16_T     w2s_str_pic[64]  = {0};
    UTF16_T     w2s_str_is[8]  = {0};
    UTF16_T     w2s_str_del[64]  = {0};
    UTF16_T     w2s_str_point[64] = {0};
    CHAR        str_point[8] = ".";
    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

    get_current_vid_pic_mode_name(s_name);

    c_uc_w2s_strcpy(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_THE));

    if(rest_get_mlm_settings_lang_id() == 0)/*english*/
    {
        c_uc_ps_to_w2s((const CHAR*)s_name, w2s_str_name, 63);
        c_uc_w2s_strncat(w2s_string,w2s_str_name,63);

        c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_LOW_CASE));
        c_uc_w2s_strncat(w2s_string,w2s_str_pic,63);
    }
    else
    {
        c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_LOW_CASE));
        c_uc_w2s_strncat(w2s_string,w2s_str_pic,63);

        c_uc_ps_to_w2s((const CHAR*)s_name, w2s_str_name, 63);
        c_uc_w2s_strncat(w2s_string,w2s_str_name,63);
    }

    c_uc_w2s_strcpy(w2s_str_is,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_IS_SE));
    c_uc_w2s_strncat(w2s_string,w2s_str_is,63);

    c_uc_w2s_strcpy(w2s_str_del,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_ALL_DELETE));
    c_uc_w2s_strncat(w2s_string,w2s_str_del,63);

    c_uc_ps_to_w2s((const CHAR*)str_point, w2s_str_point, 63);
    c_uc_w2s_strncat(w2s_string,w2s_str_point,63);

    t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;

    rest_send_msg_to_nav(&t_toast);

    /* get crnt pic mode*/
    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE),&i2_pic_mode);
    REST_LOG_I("pic mode:%d\n\r", i2_pic_mode);

    i4_ret = a_cfg_cust_delete_pic_mode();
    if(i4_ret != 0)
    {
        REST_LOG_E("<REST>Failed to delete pic mode. [i4_ret = %d]\r\n", i4_ret);
    }
    else
    {
        /*After delete is selected, then Bright Room pictrue mode is set for any sources previously assigned to the picture mode*/
        i4_ret = a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE), ACFG_PIC_MODE_DEF);
        if(i4_ret != 0)
        {
            REST_LOG_E("<REST>Failed to delete pic mode. [i4_ret = %d]\r\n", i4_ret);
        }
        else
        {
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     w2s_str_name[64]  = {0};
            CHAR        curt_pic_name[64] = {0};

            get_current_vid_pic_mode_name(curt_pic_name);
            REST_LOG_I("pic_name:%s\r\n", curt_pic_name);

            c_uc_w2s_strcpy(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_ITEM));

            c_uc_ps_to_w2s((const CHAR*)curt_pic_name, w2s_str_name, 63);
            c_uc_w2s_strncat(w2s_string,w2s_str_name,63);

            c_uc_w2s_strncat(w2s_string,w2s_str_point,63);

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

            rest_show_sleep_toast(w2s_string);

            for(UINT8 ui1_input_src=ACFG_CUST_INPUT_GRP_TV;ui1_input_src<ACFG_CUST_INPUT_GRP_MAX;ui1_input_src++)
            {
                ui2_elem_idx = ui1_input_src;

                i4_ret = acfg_get_int16_by_idx(IDX_PIC_MODE, ui2_elem_idx, &i2_val);
                if(i2_val == i2_pic_mode)
                {
                    i4_ret = acfg_set_int16_by_idx(IDX_PIC_MODE, ui2_elem_idx, ACFG_PIC_MODE_DEF);
                }
            }
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_PIC_MODE));
        }
    }
    return 0;
}

INT32 picture_mode_edit_reset_picture_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    WDK_TOAST_T t_toast;
    CHAR        s_name[64] = {0};
    UTF16_T     w2s_string[256]  = {0};
    UTF16_T     w2s_str_name[64] = {0};
    UTF16_T     w2s_str_pic[64]  = {0};
    UTF16_T     w2s_str_is[8]  = {0};
    UTF16_T     w2s_str_reset[64]  = {0};
    UTF16_T     w2s_str_point[64] = {0};
    CHAR        str_point[8] = ".";

    UINT8   ui1_input = 0xFF;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    ISL_REC_T t_isl_rec;

    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;

    get_current_vid_pic_mode_name(s_name);
    a_cfg_reset_preset_pic_mode();

    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        REST_LOG_I("DEV_AVC_VGA\n\r");
        //auto_size_postion_start(NULL);
        acfg_vga_reset();
        a_cfg_vga_auto_clk_phs_pos();
		auto_size_postion_vga_sync_hv_size();

        acfg_cust_vga_reset();
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE));
    }

    c_uc_w2s_strcpy(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_THE));

    if(rest_get_mlm_settings_lang_id() == 0)/*english*/
    {
        c_uc_ps_to_w2s((const CHAR*)s_name, w2s_str_name, 63);
        c_uc_w2s_strncat(w2s_string,w2s_str_name,63);

        c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_LOW_CASE));
        c_uc_w2s_strncat(w2s_string,w2s_str_pic,63);
    }
    else
    {
        c_uc_w2s_strcpy(w2s_str_pic,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_VID_PIC_MODE_LOW_CASE));
        c_uc_w2s_strncat(w2s_string,w2s_str_pic,63);

        c_uc_ps_to_w2s((const CHAR*)s_name, w2s_str_name, 63);
        c_uc_w2s_strncat(w2s_string,w2s_str_name,63);
    }

    c_uc_w2s_strcpy(w2s_str_is,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_IS_SE));
    c_uc_w2s_strncat(w2s_string,w2s_str_is,63);

    c_uc_w2s_strcpy(w2s_str_reset,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_RESET));
    c_uc_w2s_strncat(w2s_string,w2s_str_reset,63);

    c_uc_ps_to_w2s((const CHAR*)str_point, w2s_str_point, 63);
    c_uc_w2s_strncat(w2s_string,w2s_str_point,63);

    t_toast.style.style_4.w2s_str = (VOID*)w2s_string;

    rest_send_msg_to_nav(&t_toast);

    return 0;
}

static VOID _menu_copy_pic_mode(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
    REST_LOG_I("Enter\n\r");
    UINT32 i2_index = (UINT32)pv_tag1;
    menu_copy_cus_pic_mode_to_preset_pic_mode(i2_index);  //copy to preset
}

INT32 picture_mode_edit_copy_picture_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT16  i2_idx = 0;
    CHAR  s_pic_mode_name[12][64] = {0};
    type = get_type(root);

    i2_idx = _get_acfg_picture_name(s_pic_mode_name);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            INT16  i2_pic_mode_idx = 0;

            i2_pic_mode_idx = menu_get_vid_pic_mode_idx();
            REST_LOG_I("map pic mode idx:%d name %s\n\r", i2_pic_mode_idx, s_pic_mode_name[i2_pic_mode_idx]);

            response["VALUE"] = std::string(s_pic_mode_name[i2_pic_mode_idx]);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT16 i2_index = -1;
            Json::Value message = root["message"];
            Json::Value value = message["VALUE"];

            REST_LOG_I("Copy to defaule name %s\n", value.asString().c_str()); //get name

            for(int i=0;i<ACFG_PRE_SET_PIC_MODE_NUM;i++) //look for name in pre-set and set
            {
                if(strncmp(value.asString().c_str(),s_pic_mode_name[i],strlen(value.asString().c_str()))==0)
                {
                    i2_index = i;
                    REST_LOG_I("Get preset index %d\n",i2_index);
                    menu_request_context_switch(_menu_copy_pic_mode, (VOID*)(UINT32)i2_index, NULL, NULL);
                    //menu_set_vid_pic_mode_idx(i2_pic_mode_idx); //set current picture mode index
                    break;
                }
            }
            if(i2_index==-1)
            {
                REST_LOG_E("Could not set the preset value\n");
                return -1;
            }
            break;
        }
        default:
            break;
    }
    return 0;
}


static VOID _color_tuner_11_point_balance(Json::Value & root, Json::Value & response,
                                          UINT16 ui2_recid, UINT8 ui1_gain_id, UINT32 ui4_mlmid)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_get_val  = 0;
    INT32 i4_set_val  = 0;
    INT32 i4_val_min = 0;
    INT32 i4_val_max = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            clr_tuner_11_point_page_get_values(ui2_recid, ui1_gain_id, &i4_get_val);
            value_set_response(response, i4_get_val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value message = root["message"];
            if(!message["VALUE"].isInt())
            {
                REST_LOG_E("Get invailed arguments.\n");
                break;
            }
            i4_set_val = message["VALUE"].asInt();

            rest_config_get_min_max_value(APP_CFG_GRPID_VIDEO,ui2_recid,&i4_val_min,&i4_val_max);
            REST_LOG_I("min:%d,max:%d\n\r", i4_val_min,i4_val_max);
            if(i4_val_min > i4_set_val || i4_val_max < i4_set_val)
            {
                REST_LOG_E("Get invailed arguments %d.\n", i4_set_val);
                break;
            }

            clr_tuner_11_point_page_set_values(ui2_recid, ui1_gain_id, i4_set_val);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = ui4_mlmid;
            t_toast.style.style_1.i4_value      = i4_set_val;
            t_toast.style.style_1.i4_max_val    = i4_val_max;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return;
}

INT32 color_calibration_color_tuner_11_point_balance_n_red(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_n;
    UINT8 ui1_gain_id;
    UINT8 i4_mlm_index_offset;
    INT32 i4_mlm_index_base = MLM_SETTINGS_KEY_VID_GAIN_5_RED;

    i4_n = root["N"].asInt();
    ui1_gain_id = (i4_n -1)/5;  //Gain 5 - >0;Gain 10 ->1
    i4_mlm_index_offset = ui1_gain_id;
    REST_LOG_I("Get N is %d gain is %d\n",i4_n,ui1_gain_id);

    _color_tuner_11_point_balance(root, response, APP_CFG_RECID_VID_11_POINT_GAIN_RED,
                                  ui1_gain_id, i4_mlm_index_base+i4_mlm_index_offset);
    return 0;
}

INT32 color_calibration_color_tuner_11_point_balance_n_green(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_n;
    UINT8 ui1_gain_id;
    UINT8 i4_mlm_index_offset;
    INT32 i4_mlm_index_base = MLM_SETTINGS_KEY_VID_GAIN_5_GREEN;

    i4_n = root["N"].asInt();
    ui1_gain_id = (i4_n -1)/5;  //Gain 5 - >0;Gain 10 ->1
    i4_mlm_index_offset = ui1_gain_id;
    REST_LOG_I("Get N is %d gain is %d\n",i4_n,ui1_gain_id);

    _color_tuner_11_point_balance(root, response, APP_CFG_RECID_VID_11_POINT_GAIN_GREEN,
                                  ui1_gain_id, i4_mlm_index_base+i4_mlm_index_offset);
    return 0;
}

INT32 color_calibration_color_tuner_11_point_balance_n_blue(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 i4_n;
    UINT8 ui1_gain_id;
    UINT8 i4_mlm_index_offset;
    INT32 i4_mlm_index_base = MLM_SETTINGS_KEY_VID_GAIN_5_BLUE;

    i4_n = root["N"].asInt();
    ui1_gain_id = (i4_n -1)/5;  //Gain 5 - >0;Gain 10 ->1
    i4_mlm_index_offset = ui1_gain_id;
    REST_LOG_I("Get N is %d gain is %d\n",i4_n,ui1_gain_id);

    _color_tuner_11_point_balance(root, response, APP_CFG_RECID_VID_11_POINT_GAIN_BLUE,
                                  ui1_gain_id, i4_mlm_index_base+i4_mlm_index_offset);
    return 0;
}

INT32 hdr_backlight(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            value_set_response(response, 50);
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


INT32 more_picture_ultra_color_spectrum(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value pictures;
            pictures[0] = "Standard";
            pictures[1] = "Calibrated";
            pictures[2] = "Calibrated Dark";
            pictures[3] = "Vivid";
            pictures[4] = "Game";
            pictures[5] = "Computer";

            response["ELEMENTS"] = pictures;
            response["VALUE"] = pictures[0];

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

INT32 color_calibration_color_calibration_lut_selection_normal(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value pictures;
            pictures[0] = "Factory";
            pictures[1] = "Custom";

            response["ELEMENTS"] = pictures;
            response["VALUE"] = pictures[0];

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

INT32 color_calibration_lut_selection_computer(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value pictures;
            pictures[0] = "Factory";
            pictures[1] = "Custom";

            response["ELEMENTS"] = pictures;
            response["VALUE"] = pictures[0];

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

INT32 full_color_444(Json::Value & root, Json::Value & response)
{
	 REST_LOG_I("Enter\n\r");
	 INT32	  type = 0;
	 INT32 i4_ret = 0;
	 WDK_TOAST_T t_toast;

	 enum _resolution_type
	 {
		 _OFF = 0,
		 _ON,
		 _TYPE_MAX,
	 };
	
	 Json::Value j_level;
	 j_level[_OFF] = "Off";
	 j_level[_ON] = "On";
	
	 type = get_type(root);
	 switch (type)
	 {
		 case argument::RequestType::REQUEST_GET:
		 {
			 INT16 i2_val = 0;
			 i2_val = menu_get_inp_full_444_color_idx();
			 if(i2_val<0)
			{
				REST_LOG_E("Invailed return\n");
				i4_ret = -1;
				break;
			}
			 response["VALUE"]=j_level[i2_val];
			 response["ELEMENTS"] = j_level;
			 break;
		 }
		 //READ ONLY
		 case argument::RequestType::REQUEST_SET:
		 {
			INT32	  type = 0;
			INT16	  i2_pre_val = 0;
			INT16	  i2_val  = -1;
			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
			t_toast.e_toast_style  = WDK_STRING_TOAST;
			t_toast.e_string_style = WDK_STRING_ID_ID;
			t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_FULL_CHROMA;

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

			menu_set_inp_full_color_444_idx(i2_val);
			rest_send_msg_to_nav(&t_toast);
			break;
		 }
		 default:
		 break;
	 }
	 return i4_ret;
}

INT32 filmmaker_mode(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	
	enum _resolution_type
	{
		_AUTO = 0,
		_ON,
		_OFF,
		_TYPE_MAX,
	};
	
	Json::Value j_level;
	j_level[_AUTO] = "Auto",
	j_level[_OFF] = "Off";
	j_level[_ON] = "On";
	
	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			INT16 i2_val = 0;
			i2_val = menu_get_inp_film_maker_mode_idx();
			if(i2_val<0)
		   {
			   REST_LOG_E("Invailed return\n");
			   i4_ret = -1;
			   break;
		   }
			response["VALUE"]=j_level[i2_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		//READ ONLY
		case argument::RequestType::REQUEST_SET:
		{
		   INT32	 type = 0;
		   INT16	 i2_pre_val = 0;
		   INT16	 i2_val  = -1;
		   
		   Json::Value message = root["message"];
		   Json::Value value = message["VALUE"];
		   
		   for(int i=0;i<_TYPE_MAX;i++)
		   {
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   break;
			   }
		   }
	
		   if(i2_val==-1)
		   {
			   REST_LOG_E("Get invailed arguments %s\n",value.asString());
			   i4_ret = -1;
			   break;
		   }
	
		   menu_set_inp_film_maker_mode_idx(i2_val);
		   break;
		}
		default:
		break;
	}
	return i4_ret;

}

INT32 color_space_range(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	 type = 0;
	INT32 i4_ret = 0;
	WDK_TOAST_T t_toast;

	enum _resolution_type
	{
		_AUTO= 0,
		_RGB,
		_YCBCR,
		_TYPE_MAX,
	};
	
	Json::Value j_level;
	j_level[_AUTO] = "Auto";
	j_level[_RGB] = "RGB";
	j_level[_YCBCR] = "YCbCr";
	
	type = get_type(root);
	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			INT16 i2_val = 0;
			i2_val = menu_get_vid_hdmi_mode_idx();
			if(i2_val<0)
		   	{
			   REST_LOG_E("Invailed return\n");
			   i4_ret = -1;
			   break;
		   	}
			response["VALUE"]=j_level[i2_val];
			response["ELEMENTS"] = j_level;
			break;
		}
		//READ ONLY
		case argument::RequestType::REQUEST_SET:
		{
		   INT32	 type = 0;
		   INT16	 i2_pre_val = 0;
		   INT16	 i2_val  = -1;
		   memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
		   t_toast.e_toast_style  = WDK_STRING_TOAST;
		   t_toast.e_string_style = WDK_STRING_ID_ID;
		   t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_VID_COLOR_SPACE;
		   
		   Json::Value message = root["message"];
		   Json::Value value = message["VALUE"];
		   
		   for(int i=0;i<_TYPE_MAX;i++)
		   {
			   if(strcmp(j_level[i].asString().c_str(),value.asString().c_str())==0)
			   {
				   i2_val = i;
				   t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUTO + i;
				   break;
			   }
		   }
	
		   if(i2_val==-1)
		   {
			   REST_LOG_E("Get invailed arguments %s\n",value.asString());
			   i4_ret = -1;
			   break;
		   }

		   menu_set_vid_hdmi_mode_idx(i2_val);
		   rest_send_msg_to_nav(&t_toast);
		   menu_pm_repaint();
		   break;
		}
		default:
		break;
	}
	return i4_ret;

}

INT32 size_position_size_vertical(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	return picture_size_vertical(root, response);
}

INT32 size_position_size_horizontal(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	return picture_size_horizontal(root, response);
}

INT32 size_position_position_vertical(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	return picture_position_vertical(root,response);
}


INT32 size_position_position_horizontal(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	return picture_position_horizontal(root, response);
}

INT32 input_picture_settings_hdmi_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret = 0;
    WDK_TOAST_T t_toast;

    enum _resolution_type
    {
        _AUTO = 0,
        _2_1,
        _1_4,
        _TYPE_MAX,
    };

    Json::Value hdmi_mode;
    hdmi_mode[_AUTO] = "Auto";
    hdmi_mode[_2_1] = "2.1";
    hdmi_mode[_1_4] = "1.4";

    INT32 i4_hdmi_idx = a_nav_ipts_get_hdmi_comp_idx();

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_value = 0;
            inp_lst_get_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, &ui1_value);
            REST_LOG_I("get_value:%d.\n\r", ui1_value);

            response["VALUE"] = hdmi_mode[2-ui1_value];
            response["ELEMENTS"] = hdmi_mode;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT16 i2_val = -1;
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_VID_HDMI_MODE;

            Json::Value message = root["message"];
            Json::Value value = message["VALUE"];

            for(int i=0;i<_TYPE_MAX;i++)
            {
                if(strcmp(hdmi_mode[i].asString().c_str(),value.asString().c_str())==0)
                {
                    i2_val = 2-i;
                    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_HDMI_MODE_AUTO + i;
                    break;
                }
            }

            if(i2_val==-1)
            {
                REST_LOG_E("Get invailed arguments %s\n",value.asString());
                i4_ret = -1;
                break;
            }

            inp_lst_set_full_uhd_color_by_hdmi_idx(i4_hdmi_idx, i2_val);
            rest_send_msg_to_nav(&t_toast);
            menu_pm_repaint();
            break;
        }
        default:
        break;
    }

    return 0;
}


handler picture_handler[] = {

    picture_mode,
    auto_brightness_control,
    backlight,
    tone_mapping,
    luminance,
    picture_aspect,
    brightness,
    contrast,
    color,
    tint,
    sharpness,
    color_calibration_picture_mode,
    super_resolution,
    edge_enhancement,
    local_contrast,
    peak_luminance,
    variable_refresh_rate,
    game_hdr,
    contour_smoothing,
    color_calibration_color_temperature,
    color_calibration_calibration_tests_smpte_test_pattern,
    color_calibration_calibration_tests_flat_test_pattern,
    color_calibration_calibration_tests_ramp_test_pattern,
    color_calibration_calibration_tests_uniformity_analyzer_test_pattern,
    color_calibration_calibration_tests_dolby_vision_test_pattern,
    color_calibration_reset_color_tuner,
    color_calibration_color_tuner_color_tuner_table_header_red,
    color_calibration_color_tuner_color_tuner_table_header_green,
    color_calibration_color_tuner_color_tuner_table_header_blue,
    color_calibration_color_tuner_color_tuner_table_hue_red,
    color_calibration_color_tuner_color_tuner_table_hue_green,
    color_calibration_color_tuner_color_tuner_table_hue_blue,
    color_calibration_color_tuner_color_tuner_table_hue_cyan,
    color_calibration_color_tuner_color_tuner_table_hue_magenta,
    color_calibration_color_tuner_color_tuner_table_hue_yellow,
    color_calibration_color_tuner_color_tuner_table_saturation_red,
    color_calibration_color_tuner_color_tuner_table_saturation_green,
    color_calibration_color_tuner_color_tuner_table_saturation_blue,
    color_calibration_color_tuner_color_tuner_table_saturation_cyan,
    color_calibration_color_tuner_color_tuner_table_saturation_magenta,
    color_calibration_color_tuner_color_tuner_table_saturation_yellow,
    color_calibration_color_tuner_color_tuner_table_brightness_red,
    color_calibration_color_tuner_color_tuner_table_brightness_green,
    color_calibration_color_tuner_color_tuner_table_brightness_blue,
    color_calibration_color_tuner_color_tuner_table_brightness_cyan,
    color_calibration_color_tuner_color_tuner_table_brightness_magenta,
    color_calibration_color_tuner_color_tuner_table_brightness_yellow,
    color_calibration_color_tuner_color_tuner_table_offset_red,
    color_calibration_color_tuner_color_tuner_table_offset_green,
    color_calibration_color_tuner_color_tuner_table_offset_blue,
    color_calibration_color_tuner_color_tuner_table_gain_red,
    color_calibration_color_tuner_color_tuner_table_gain_green,
    color_calibration_color_tuner_color_tuner_table_gain_blue,
    more_picture_color_temperature,
    more_picture_active_full_array,
    more_picture_black_detail,
    more_picture_active_led_zones,
    more_picture_backlight_control,
    more_picture_reduce_judder,
    more_picture_reduce_motion_blur,
    more_picture_clear_action,
    more_picture_reduce_signal_noise,
    more_picture_reduce_block_noise,
    more_picture_game_low_latency,
    more_picture_film_mode,
    more_picture_color_space,
    more_picture_gamma,
    enhanced_viewing_angle,
    picture_mode_edit_save_picture_mode,
    picture_mode_edit_lock_unlock_picture_mode,
    picture_mode_edit_delete_picture_mode,
    picture_mode_edit_reset_picture_mode,
    picture_mode_edit_copy_picture_mode,
    color_calibration_color_tuner_11_point_balance_n_red,
    color_calibration_color_tuner_11_point_balance_n_green,
    color_calibration_color_tuner_11_point_balance_n_blue,
    hdr_backlight,
    more_picture_ultra_color_spectrum,
    color_calibration_color_calibration_lut_selection_normal,
    color_calibration_lut_selection_computer,
    full_color_444,
    filmmaker_mode,
    color_space_range,
    size_position_size_vertical,
    size_position_size_horizontal,
    size_position_position_vertical,
    size_position_position_horizontal,
    input_picture_settings_hdmi_mode,
};

