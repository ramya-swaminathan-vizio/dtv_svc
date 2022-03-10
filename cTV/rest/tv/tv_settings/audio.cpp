#include <iostream>
#include <bits/unique_ptr.h>
#include <memory>
#include <unistd.h>
#include "audio.h"
#include "handler.h"
#include "common.h"
#include "argument.h"
#include <string.h>
#include "tv_settings.h"
#include "a_rest_event.h"
#include "audio_ex.h"

#ifdef __cplusplus
extern "C" {
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "app_util/a_bluetooth.h"
#include "app_util/a_tv.h"
#include "c_iom.h"
#include "u_btn_map.h"
#include "nav/nav_common.h"
#include "menu2/menu_common/menu_common.h"
#include "res/app_util/mtktvapi/a_mtktvapi_volctrl_custom.h"

}
#endif

TvSettingsGroupURI tvSettingsAudioUri[] = {

        /*
        ###########################################
        # AUDIO
        */

        { "tv_speakers" },
        { "volume_control_display" },
        { "surround_sound" },
        { "volume_leveling" },
        { "balance" },
        { "lip_sync" },
        { "digital_audio_out" },
        { "analog_audio_out" },
        { "volume" },
        { "mute" },
        { "equalizer" , "audio_mode" },
        { "equalizer" , "100_hz" },
        { "equalizer" , "300_hz" },
        { "equalizer" , "1k_hz" },
        { "equalizer" , "3k_hz" },
        { "equalizer" , "10k_hz" },
        { "delete_audio_mode" },
        { "bluetooth" },
        { "bluetooth_pair" },
        { "dialogue_enhancer"},
        { "" },
};


int tv_speakers(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type = 0;
    UINT16  ui2_current_mode = 0;
    INT32 i4_ret = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Off";
            items[1] = "On";
            items[2] = "Auto";

            response["ELEMENTS"] = items;

            get_aud_speaker_status(&ui2_current_mode);

            response["VALUE"] = items[ui2_current_mode];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            CHAR    str[64]={0};
            INT32   val  = 0;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_SPEAKERS;

            string_get_string(root, str, 64);

            if(c_strcmp(str,"On") == 0)
            {
                val = 1;
                set_aud_speaker_status(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Off") == 0)
            {
                val = 0;
                set_aud_speaker_status(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Auto") == 0)
            {
                val = 2;
                set_aud_speaker_status(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUTO;
                rest_send_msg_to_nav(&t_toast);
            }
            else
            {
                i4_ret = -1;
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }

            break;
        }
        default:
            break;
    }

    return i4_ret;
}

int volume_control_display(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type = 0;
    UINT8   ui1_current_mode = 0;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "On";
            items[1] = "Off";
            response["ELEMENTS"] = items;

            aud_get_vol_control_display(&ui1_current_mode);
            REST_LOG_I("%s,%d [audio]vol_dis= %d \r\n",__FUNCTION__,__LINE__,ui1_current_mode);

            response["VALUE"] = items[ui1_current_mode];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            CHAR    str[64]={0};
            UINT8   ui1_val  = 0;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_VOL_CONTROL_DIS;

            string_get_string(root, str, 64);

            if(c_strcmp(str,"On") == 0)
            {
                ui1_val = 0;
                aud_set_vol_control_display(ui1_val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Off") == 0)
            {
                ui1_val = 1;
                aud_set_vol_control_display(ui1_val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
                rest_send_msg_to_nav(&t_toast);
            }
            else
            {
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int surround_sound(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type = 0;
    UINT16  ui2_current_mode = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "Virtual:X";
            items[1] = "On";
            items[2] = "Off";

            response["ELEMENTS"] = items;

            get_aud_surround_sound(&ui2_current_mode);
            if(0 == ui2_current_mode)
            {
                response["VALUE"] = items[0];
            }
            else if(1 == ui2_current_mode)
            {
                response["VALUE"] = items[1];
            }
            else
            {
                response["VALUE"] = items[2];
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            CHAR    str[64]={0};
            INT32   val  = 0;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_SURROUND_SOUND;

            string_get_string(root, str, 64);

            if(c_strcmp(str,"On") == 0)
            {
                val = 1;
                set_aud_surround_sound(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Off") == 0)
            {
                val = 2;
                set_aud_surround_sound(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Virtual:X") == 0)
            {
                val = 0;
                set_aud_surround_sound(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_SURROUND_SOUND_VIRTUAL;
                rest_send_msg_to_nav(&t_toast);
            }
            else
            {
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int volume_leveling(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32   type = 0;
    UINT16  ui2_current_mode = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "On";
            items[1] = "Off";

            response["ELEMENTS"] = items;

            get_aud_volume_leveling(&ui2_current_mode);
            if(1 == ui2_current_mode)
            {
                response["VALUE"] = items[0];
            }
            else
            {
                response["VALUE"] = items[1];
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            CHAR    str[64]={0};
            INT32   val  = 0;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_VOL_LEVEL;

            string_get_string(root, str, 64);

            if(c_strcmp(str,"On") == 0)
            {
                val = 1;
                set_aud_volume_leveling(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Off") == 0)
            {
                val = 0;
                set_aud_volume_leveling(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
                rest_send_msg_to_nav(&t_toast);
            }
            else
            {
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

int balance(Json::Value & root, Json::Value & response)
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
            rest_config_get_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE, &val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT32 i4_min = 0;
            INT32 i4_max = 0;

            val  = value_get_value(root);
            rest_config_set_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE, val);

            rest_config_get_min_max_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BALANCE, &i4_min, &i4_max);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_AUD_BALANCE;
            t_toast.style.style_1.i4_value      = val;
            t_toast.style.style_1.i4_max_val    = i4_max;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int lip_sync(Json::Value & root, Json::Value & response)
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
            rest_config_get_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY, &val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT32 i4_min = 0;
            INT32 i4_max = 0;

            val  = value_get_value(root);
            rest_config_set_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY, val);

            rest_config_get_min_max_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_LATENCY, &i4_min, &i4_max);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_CENTER;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_AUD_LIP_SYNC;
            t_toast.style.style_1.i4_value      = val;
            t_toast.style.style_1.i4_max_val    = i4_max;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int digital_audio_out(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            UINT16  ui2_idx = 0;

            items[0] = "Auto";
            items[1] = "PCM";
			items[2] = "Digital";
#if 0
            items[2] = "Dolby D";
            items[3] = "Bitstream";
#endif

            response["ELEMENTS"] = items;

            get_aud_digital_audio_out_idx(&ui2_idx);
            if(0 == ui2_idx)
            {
                response["VALUE"] = items[0];
            }
            else if(1 == ui2_idx)
            {
                response["VALUE"] = items[1];
            }
            else if(2 == ui2_idx)
            {
                response["VALUE"] = items[2];
            }
#if 0
            else if(3 == ui2_idx)
            {
                response["VALUE"] = items[3];
            }
#endif
            else
            {
                response["VALUE"] = items[0];
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            CHAR str[64] = {0};
            UINT16 val = 0;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_DIG_AUD_OUT;

            string_get_string(root, str, 64);

            if(c_strcmp(str,"Auto") == 0)
            {
                val = 0;
                set_aud_digital_audio_out_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUTO; //Auto
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"PCM") == 0)
            {
                val = 1;
                set_aud_digital_audio_out_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_DIG_PCM; //PCM
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Digital") == 0)
            {
                val = 2;
                set_aud_digital_audio_out_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_DIG_DOLBY_D; //Digital
                rest_send_msg_to_nav(&t_toast);
            }
#if 0
            else if(c_strcmp(str,"Bitstream") == 0)
            {
                val = 3;
                set_aud_digital_audio_out_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_DIG_BITSTREAM; //Bitstream
                rest_send_msg_to_nav(&t_toast);
            }
#endif
            else
            {
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

int analog_audio_out(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            UINT16  ui2_idx = 0;

            items[0] = "Fixed";
            items[1] = "Variable";

            response["ELEMENTS"] = items;

            get_aud_analog_audio_out_idx(&ui2_idx);
            if(1 == ui2_idx)
            {
                response["VALUE"] = items[1];
            }
            else
            {
                response["VALUE"] = items[0];
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            CHAR str[64] = {0};
            UINT16 val = 0;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_ANALOG_AUD_OUT;

            string_get_string(root, str, 64);

            if(c_strcmp(str,"Fixed") == 0)
            {
                val = 0;
                set_aud_analog_audio_out_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_ANALOG_FIXED;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Variable") == 0)
            {
                val = 1;
                set_aud_analog_audio_out_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_ANALOG_VARIABLE;
                rest_send_msg_to_nav(&t_toast);
            }
            else
            {
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

int earc_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    UINT16 i2_get_idx = 0;
    UINT16 i2_set_idx = 0;
    type = get_type(root);

    i2_get_idx = a_get_cec_earc_idx();
    REST_LOG_I("get current earc_mode :%d.\n\r", i2_get_idx);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value earc_mode;
            earc_mode[0] = "Off";
            earc_mode[1] = "On";
            response["ELEMENTS"] = earc_mode;
            response["VALUE"] = earc_mode[i2_get_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            WDK_TOAST_T t_toast;
            UINT16	ui2_mlm_warning_key = 0;
            UINT16  ui2_w2s_len;
            UTF16_T* pt_w2s = NULL;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            CHAR str[128] = {0};
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strcpy(str, item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if (c_strcmp("Off", str) == 0)
            {
                i2_set_idx = 0;
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_72;
            }
            else if (c_strcmp("On", str) == 0)
            {
                i2_set_idx = 1;
                ui2_mlm_warning_key = MLM_WARNINGS_KEY_WARNING_71;
            }
            else
            {
                REST_LOG_E("Error\n\r");
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

            REST_LOG_I("set earc %s.\n\r", i2_set_idx? "On":"Off");
            a_set_cec_earc_idx(i2_set_idx);

            break;
        }
        default:
            break;
    }
    return 0;
}

int volume(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;
    INT32 i4_ret =0;
    INT32 value  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            rest_config_get_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL, &val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT32 i4_pre_vol = -1;
            val  = value_get_value(root);

            rest_config_get_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL, &i4_pre_vol);
            rest_config_set_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL, val);
            rest_config_get_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_VOLUME_ALL, &value);

            if((value >= 0) && (value <= 100))
            {
                i4_ret = c_iom_send_evt(BTN_SHOW_VOL_BAR,120);
                if(i4_ret != 0)
                {
                    REST_LOG_E("c_iom_send_evt_single i4_ret=%d\r\n",i4_ret);
                    return REST_R_ERR;
                }
                if(i4_pre_vol!=value)
                {
                    rest_event_notify("audio/volume/level", i4_pre_vol<<16 |value,""); //vol:[pre|cur] dolphin 20200812 add notify even user set
                }
                // For MVV-4863 DTV02178539, unmute when the volume level is set and the value is not 0.
                // Do the same thing as mute OFF.
                if (value !=0)
                {
                    REST_LOG_I("volume level is not 0, unmute here.\n\r");
                    a_mtktvapi_volctrl_custom_setMute_by_type(1, FALSE);
                    //nav_set_mute(FALSE);
                    //t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
                    rest_event_notify("audio/volume/mute",0,"");
                    //rest_send_msg_to_nav(&t_toast);
                }
            }
            else
            {
                REST_LOG_E("get volume value fail val=%d\r\n",value);
                return REST_R_ERR;
            }

            break;
        }
        default:
            break;
    }

    return 0;
}


int mute(Json::Value & root, Json::Value & response)
{
    //TODO
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            items[0] = "On";
            items[1] = "Off";

            response["ELEMENTS"] = items;

            if(a_tv_get_mute())
            {
                response["VALUE"] = items[0];
            }
            else
            {
                response["VALUE"] = items[1];
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            //WDK_TOAST_T t_toast;
            CHAR    str[64]={0};

            //c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            //t_toast.e_toast_style  = WDK_STRING_TOAST;
            //t_toast.e_string_style = WDK_STRING_ID_ID;
            //t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_MUTE;

            string_get_string(root, str, 64);

            if(c_strcmp(str,"On") == 0)
            {
                a_mtktvapi_volctrl_custom_setMute_by_type(1, TRUE);
                //nav_set_mute(TRUE);
                //t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
                rest_event_notify("audio/volume/mute",1,"");
                //rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,"Off") == 0)
            {
                a_mtktvapi_volctrl_custom_setMute_by_type(1, FALSE);
                //nav_set_mute(FALSE);
                //t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
                rest_event_notify("audio/volume/mute",0,"");
                //rest_send_msg_to_nav(&t_toast);
            }
            else
            {
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

int equalizer_audio_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    s_audio_mode[6][64];
    UTF16_T w2s_tmp_str[64] = {0};
    INT16   i2_mlm_audio_id[6] = {MLM_SETTINGS_KEY_AUD_MODE_FLAT,
                               MLM_SETTINGS_KEY_AUD_MODE_DYNAMIC,
                               MLM_SETTINGS_KEY_AUD_MODE_CENTER,
                               MLM_SETTINGS_KEY_AUD_MODE_BASS_BOOST,
                               MLM_SETTINGS_KEY_AUD_MODE_BRIGHT,
                               MLM_SETTINGS_KEY_AUD_MODE_CUSTOM};

    for (INT32 i=0; i<6; i++)
    {
        c_memset(w2s_tmp_str, 0, 64);
        c_uc_w2s_strcpy(w2s_tmp_str,REST_SETTINGS_TEXT(i2_mlm_audio_id[i]));
        c_uc_w2s_to_ps(w2s_tmp_str,s_audio_mode[i],64);
    }

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            INT16   i2_cust_aud_mode = 0;
            UINT16  ui2_idx = 0;

            for (INT32 i=0; i<5; i++)
            {
                items[i] = std::string(s_audio_mode[i]);
            }

            a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS),&i2_cust_aud_mode);

            if (i2_cust_aud_mode == 1)
            {
                // Custom audio mode exists.
                items[5] = std::string(s_audio_mode[5]);
            }

            response["ELEMENTS"] = items;

            get_aud_mode_idx(&ui2_idx);
            response["VALUE"] = items[ui2_idx];

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            CHAR str[64] = {0};
            UINT16 val = 0;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_MODE;

            string_get_string(root, str, 64);

            if(c_strcmp(str,s_audio_mode[0]) == 0)
            {
                val = 0;
                set_aud_mode_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_MODE_FLAT;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,s_audio_mode[1]) == 0)
            {
                val = 1;
                set_aud_mode_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_MODE_DYNAMIC;
                rest_send_msg_to_nav(&t_toast);
            }
            else if(c_strcmp(str,s_audio_mode[2]) == 0)
            {
                val = 2;
                set_aud_mode_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_MODE_CENTER;
                rest_send_msg_to_nav(&t_toast);
            }

            else if(c_strcmp(str,s_audio_mode[3]) == 0)
            {
                val = 3;
                set_aud_mode_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_MODE_BASS_BOOST;
                rest_send_msg_to_nav(&t_toast);
            }

            else if(c_strcmp(str,s_audio_mode[4]) == 0)
            {
                val = 4;
                set_aud_mode_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_MODE_BRIGHT;
                rest_send_msg_to_nav(&t_toast);
            }

            else if(c_strcmp(str,s_audio_mode[5]) == 0)
            {
                val = 5;
                set_aud_mode_idx(val);
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_MODE_CUSTOM;
                rest_send_msg_to_nav(&t_toast);
            }
            else
            {
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }

            break;
        }
        default:
            break;
    }

    return 0;
}


static VOID _equalizer_process(Json::Value & root, Json::Value & response,
                               UINT8 ui1_band_idx, UINT32 ui4_mlmid)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 val  = 0;

    WDK_TOAST_T t_toast;

    type = get_type(root);
    UINT16  ui2_idx = 0;
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            audio_equalizer_get_value(ui1_band_idx, &val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT32 i4_min = 0;
            INT32 i4_max = 0;

            get_aud_mode_idx(&ui2_idx);

            if(ui2_idx != 5)
            {
                c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
                t_toast.e_toast_style  = WDK_STRING_TOAST;
                t_toast.e_string_style = WDK_STRING_ID_ID;

                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_AUD_MODE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_AUD_MODE_CUSTOM;
                rest_send_msg_to_nav(&t_toast);
                sleep(1);
            }

            val  = value_get_value(root);
            audio_equalizer_set_value(ui1_band_idx, val);

            audio_equalizer_get_min_max_value(ui1_band_idx, &i4_min, &i4_max);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = ui4_mlmid;
            t_toast.style.style_1.i4_value      = val;
            t_toast.style.style_1.i4_max_val    = i4_max;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return;
}

int equalizer_100_hz(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _equalizer_process(root, response, EQ_BAND_100HZ, MLM_SETTINGS_KEY_AUD_100HZ);
    return 0;
}

int equalizer_300_hz(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _equalizer_process(root, response, EQ_BAND_300HZ, MLM_SETTINGS_KEY_AUD_300HZ);
    return 0;
}

int equalizer_1k_hz(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _equalizer_process(root, response, EQ_BAND_1KHZ, MLM_SETTINGS_KEY_AUD_1KHZ);
    return 0;
}

int equalizer_3k_hz(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _equalizer_process(root, response, EQ_BAND_3KHZ, MLM_SETTINGS_KEY_AUD_3KHZ);
    return 0;
}

int equalizer_10k_hz(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    _equalizer_process(root, response, EQ_BAND_10KHZ, MLM_SETTINGS_KEY_AUD_10KHZ);
    return 0;
}

int delete_audio_mode(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    UINT16 ui2_idx = 0;
    UINT8  ui1_loop = 0;

    get_type(root);

    get_aud_mode_idx(&ui2_idx);
    set_aud_mode_idx(EQ_AUD_MODE_CUSTOM_IDX);

    for(ui1_loop = 0; ui1_loop < EQ_BAND_NUM; ui1_loop++)
    {
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, (APP_CFG_RECID_AUD_EQ_BAND_1+ui1_loop)), 126);
    }

    /* restore audio mode */
    if (EQ_AUD_MODE_CUSTOM_IDX == ui2_idx)
    {
        set_aud_mode_idx(0);
    }
    else
    {
        set_aud_mode_idx(ui2_idx);
    }

    a_cfg_av_set(CFG_MAKE_ID( APP_CFG_GRPID_AUDIO, APP_CFG_RECID_CUST_AUD_MODE_EXIST_STATUS), 0);
    {
        WDK_TOAST_T t_toast;

        c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
        t_toast.e_toast_style  = WDK_STRING_TOAST;
        t_toast.e_string_style = WDK_STRING_ID_ID;
        t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CUSTOM_AUD_MODE;
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_VID_PIC_ALL_DELETE;
        rest_send_msg_to_nav(&t_toast);

        rest_show_flat_aud_mode();
    }

    return 0;
}

int bluetooth(Json::Value & root, Json::Value & response)
{
#if 0
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    type = get_type(root);
    UINT8 u1_bt_mode = 0;
    WDK_TOAST_T t_toast;
    CHAR ps_mac_str[64]={0};

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;

            items[0] = "On";
            items[1] = "Off";

            response["ELEMENTS"] = items;

            a_cfg_get_bluetooth_switch_status(&u1_bt_mode);
            if(APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode)
            {
                response["VALUE"] = items[0];
            }
            else
            {
               response["VALUE"] = items[1];
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;

            string_get_string(root, ps_mac_str, 64);
            if(c_strcmp(ps_mac_str,"On") == 0)
            {
                a_cfg_set_bluetooth_switch_status(APP_CFG_BLUETOOTH_SWITCH_ON);
                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_BLUETOOTH;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            else if(c_strcmp(ps_mac_str,"Off") == 0)
            {
                a_cfg_set_bluetooth_switch_status(APP_CFG_BLUETOOTH_SWITCH_OFF);
                t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_BLUETOOTH;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }

             rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
#endif
    return 0;
}

int bluetooth_pair(Json::Value & root, Json::Value & response)
{
#if 0
    REST_LOG_I("Enter\n\r");
    UINT8 u1_bt_mode = 0;

    a_cfg_get_bluetooth_switch_status(&u1_bt_mode);
    if(APP_CFG_BLUETOOTH_SWITCH_ON == u1_bt_mode)
    {
        rest_a_bt_create_timer();

        rest_a_bt_status();
        //rest_a_bt_hide();

        //rest_a_bt_pair();
        //rest_a_bt_hide();

        //rest_a_bt_delete_timer();
    }
#endif
    return 0;
}

int dialogue_enhancer(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
	DBG_LOG_PRINT(("[rest audio +++] {%s() %d}. \n",__FUNCTION__, __LINE__));
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            Json::Value items;
            INT16  i2_idx = 0;

			items[0] = "Off";
			items[1] = "Low";
			items[2] = "Medium";
			items[3] = "High";

            response["ELEMENTS"] = items;

            get_dialogue_enhancer(&i2_idx);
			DBG_LOG_PRINT(("[rest audio +++] {%s() %d}. i2_idx = %d\n",__FUNCTION__, __LINE__,i2_idx));
            if(0 == i2_idx)
            {
                response["VALUE"] = items[0];
            }
            else if(1 == i2_idx)
            {
                response["VALUE"] = items[1];
            }
			else if(2 == i2_idx)
            {
                response["VALUE"] = items[2];
            }
            else if(3 == i2_idx)
            {
                response["VALUE"] = items[3];
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            WDK_TOAST_T t_toast;
            CHAR str[64] = {0};
            UINT16 val = 0;

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_DIALOGUE_ENHANCER;

            string_get_string(root, str, 64);

            if(c_strcmp(str,"Off") == 0)
            {
                val = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_DIALOGUE_ENHANCER_OFF;
            }
            else if(c_strcmp(str,"Low") == 0)
            {
                val = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_DIALOGUE_ENHANCER_LOW;
            }
			else if(c_strcmp(str,"Medium") == 0)
            {
                val = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_DIALOGUE_ENHANCER_MIDDLE;
            }
			else if(c_strcmp(str,"High") == 0)
            {
                val = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_DIALOGUE_ENHANCER_HIGH;
            }
            else
            {
                REST_LOG_E("Wrong Value:%s\n\r", str);
            }
			DBG_LOG_PRINT(("[rest audio +++] {%s() %d}. val = %d\n",__FUNCTION__, __LINE__,val));
			set_dialogue_enhancer(val);
			rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }

    return 0;
}

int bass(Json::Value & root, Json::Value & response)
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
            rest_config_get_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS, &val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT32 i4_min = 0;
            INT32 i4_max = 0;

            val  = value_get_value(root);
            rest_config_set_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS, val);

            rest_config_get_min_max_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_BASS, &i4_min, &i4_max);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_AUD_BASS;
            t_toast.style.style_1.i4_value      = val;
            t_toast.style.style_1.i4_max_val    = i4_max;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int treble(Json::Value & root, Json::Value & response)
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
            rest_config_get_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE, &val);
            value_set_response(response, val);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT32 i4_min = 0;
            INT32 i4_max = 0;

            val  = value_get_value(root);
            rest_config_set_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE, val);

            rest_config_get_min_max_value(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_TREBLE, &i4_min, &i4_max);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_AUD_TREBLE;
            t_toast.style.style_1.i4_value      = val;
            t_toast.style.style_1.i4_max_val    = i4_max;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

handler tv_settings_audio_handler[] = {
    tv_speakers,
    volume_control_display,
    surround_sound,
    volume_leveling,
    balance,
    lip_sync,
    digital_audio_out,
    analog_audio_out,
    earc_mode,
    volume,
    mute,
    equalizer_audio_mode,
    equalizer_100_hz,
    equalizer_300_hz,
    equalizer_1k_hz,
    equalizer_3k_hz,
    equalizer_10k_hz,
    delete_audio_mode,
    bluetooth,
    bluetooth_pair,
    dialogue_enhancer,
    bass,
    treble
};

