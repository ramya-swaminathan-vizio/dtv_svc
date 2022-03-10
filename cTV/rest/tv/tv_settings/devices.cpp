#include <unistd.h>
#include <bits/unique_ptr.h>
#include <iostream>
#include "devices.h"
#include "picture_ex.h"
#include "handler.h"
#include "common.h"
#include "argument.h"
#include "rest/a_rest_event.h"
#include "app.h"

#include <string.h>

#ifdef __cplusplus
extern "C" {

#include "app_util/a_cfg.h"
#include "c_svctx.h"
#include "app_util/config/a_cfg_custom.h"
#include "nav/retail_mode/a_nav_retail_mode.h"
#include "a_picture_ex.h"
#include "nav/nav_common.h"
#include "nav/input_src/a_input_src.h"
#include "nav/input_src/input_src.h"
#include "nav/banner2/banner.h"
#include "res/nav/banner2/banner_rc.h"
#include "nav/cec2/nav_cec.h"
#include "c_cecm.h"
#include "am/a_am.h"
#include "mtvdecex.h"
#include "res/app_util/tts/a_tts_custom.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu_device/menu_page_input_ope_lst.h"

extern INT32  acfg_tv_get_focus_win(TV_WIN_ID_T*   pe_tv_win_id);
extern INT32  a_nav_retail_mode_get_status(NAV_RETAIL_MODE_STATUS_T* pe_status);
extern "C" INT32 vid_update_pic_size_info(UINT8 u1_input_id,INT32 i4_value,BOOL b_direction_v);
extern "C" INT32 vid_update_position_info(UINT8 u1_input_id,INT32 i4_value,BOOL b_direction_v);


#ifdef APP_C4TV_SUPPORT
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "nav/c4tv_apron/c4tv_apron.h"

#if defined(APP_C4TV_SUPPORT)&& defined(APP_VTRL_INP_SRC_SUPPORT) && defined(ISL_VTRL_INP_SRC_CAST)
extern VOID a_nav_ipts_src_c4tv_apron_custom_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3);
extern VOID a_nav_ipts_src_set_c4tv_apron_exit_status(BOOL b_exit);
#endif

#endif
extern BOOL a_wzd_is_oobe_mode(VOID);
extern int _rest_app_launch_app_by_keycode(int keycode, int reason);

extern UINT16     ui2_g_menu_curr_lang;
}
#endif

CHAR g_current_input[256];

TvSettingsGroupURI tvSettingsDevicesUri[] = {

        /*
        # DEVICES
        */
        { "name_input" , "cast" },
        { "name_input" , "hdmi1" },
        { "name_input" , "hdmi2" },
        { "name_input" , "hdmi3" },
        { "name_input" , "hdmi4" },
        { "name_input" , "hdmi5" },
        { "name_input" , "comp" },
        { "current_input" },
        { "hdmi1" , "hdmi_color" },
        { "hdmi2" , "hdmi_color" },
        { "hdmi3" , "hdmi_color" },
        { "hdmi4" , "hdmi_color" },
        { "hdmi5" , "hdmi_color" },
        { "full_chroma" , "hdmi1" },
        { "full_chroma" , "hdmi2" },
        { "full_chroma" , "hdmi3" },
        { "full_chroma" , "hdmi4" },
        { "full_chroma" , "hdmi5" },
        { "name_input" , "tuner" },
        { "name_input" , "vga" },
        { "auto_size_position"} ,
        { "picture_size" , "horizontal" },
        { "picture_size" , "vertical" },
        { "picture_position" , "horizontal" },
        { "picture_position" , "vertical" },

        { "cast" , "name_input" },
        { "hdmi1" , "name_input" },
        { "hdmi2" , "name_input" },
        { "hdmi3" , "name_input" },
        { "hdmi4" , "name_input" },
        { "hdmi5" , "name_input" },
        { "comp" , "name_input" },

	{ "hdmi1" , "hide_input" },
	{ "hdmi2" , "hide_input" },
	{ "hdmi3" , "hide_input" },
	{ "hdmi4" , "hide_input" },
	{ "hdmi5" , "hide_input" },
	{ "comp" , "hide_input" },

        { "tuner" , "picture_size","horizontal"},
        { "tuner" , "picture_size","vertical" },
        { "tuner" , "picture_position","horizontal"},
        { "tuner" , "picture_position","vertical" },
        { "tuner" , "hide_input"},
        { "current_inputs" },

        { "hdmi1","picture_size" , "horizontal" },
        { "hdmi1","picture_size" , "vertical" },
        { "hdmi1","picture_position" , "horizontal" },
        { "hdmi1","picture_position" , "vertical" },

        { "hdmi2","picture_size" , "horizontal" },
        { "hdmi2","picture_size" , "vertical" },
        { "hdmi2","picture_position" , "horizontal" },
        { "hdmi2","picture_position" , "vertical" },

        { "hdmi3","picture_size" , "horizontal" },
        { "hdmi3","picture_size" , "vertical" },
        { "hdmi3","picture_position" , "horizontal" },
        { "hdmi3","picture_position" , "vertical" },

        { "hdmi4","picture_size" , "horizontal" },
        { "hdmi4","picture_size" , "vertical" },
        { "hdmi4","picture_position" , "horizontal" },
        { "hdmi4","picture_position" , "vertical" },

        { "hdmi5","picture_size" , "horizontal" },
        { "hdmi5","picture_size" , "vertical" },
        { "hdmi5","picture_position" , "horizontal" },
        { "hdmi5","picture_position" , "vertical" },

        { "comp","picture_size" , "horizontal" },
        { "comp","picture_size" , "vertical" },
        { "comp","picture_position" , "horizontal" },
        { "comp","picture_position" , "vertical" },

        { "" },
};


int name_input_cast(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            input["NAME"]     = std::string("SMARTCAST");
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

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
int rest_get_src_indx(INP_SRC_TYPE_T e_src_type,
                      DEVICE_TYPE_T  e_video_type,
                      UINT8 ui1_internal_id)
{
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    int             ui1_src_index = -1;

    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);

        if (i4_ret != REST_R_OK)
        {
            return REST_R_ERR;
        }

        if ((t_isl_rec.e_src_type == e_src_type) &&
            (INP_SRC_TYPE_TV      == e_src_type))
        {
            ui1_src_index = ui1_index;
            break;
        }
        else if ((t_isl_rec.e_src_type == e_src_type) &&
                 (t_isl_rec.t_avc_info.e_video_type == e_video_type))
        {
            if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
            {
                if (t_isl_rec.ui1_internal_id != ui1_internal_id)
                {
                    continue;
                }
            }
            ui1_src_index = ui1_index;
            break;
        }
    }
    return ui1_src_index;
}
int name_input_hdmi1(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};//OSD_NAME_LENGTH----->15
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    CHAR model_name[32] = {0};

    i4_ret = a_cfg_custom_get_model_name(model_name);
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "HDMI-1 is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_device_type(src_indx,str);

            if (c_strcmp(model_name, "D24h-E1") == 0)
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI1));
            }
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int name_input_hdmi2(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "HDMI-2 is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_device_type(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI2));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int name_input_hdmi3(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "HDMI-3 is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};
            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_device_type(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI3));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int name_input_hdmi4(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};
            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_device_type(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI4));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}


int name_input_hdmi5(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};
            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_device_type(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI5));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int name_input_comp(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    INT32 src_indx =0;
    //WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
            if (src_indx < 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
            }
            a_cfg_custom_get_inp_name(src_indx, str);
            if (strcmp(str, "") == 0)
            {
                input["NAME"]     = std::string("COMP");
            }else
            {
                input["NAME"]     = std::string(str);
            }
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "COMP is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                if (src_indx < 0)
                {
                    break;
                }
            }
            a_cfg_custom_set_device_type(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_COMP));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

static INT32 _chg_inp_src(INP_SRC_TYPE_T e_src_type,
                          DEVICE_TYPE_T  e_video_type,
                          UINT8 ui1_internal_id)
{
    REST_LOG_I("Enter, e_src_type: %d, e_video_type: %d, ui1_internal_id: %d.\n\r",
                (INT32)e_src_type, (INT32)e_video_type, (INT32)ui1_internal_id);

    ISL_REC_T       t_isl_rec;
    INT32           i4_ret;
    UINT8           ui1_index = 0;
    UINT8           ui1_src_num = 0;
    UINT8           ui1_src_index = 0;

    a_isl_get_num_rec(&ui1_src_num);

    for (ui1_index = 0; ui1_index < ui1_src_num; ui1_index++)
    {
        i4_ret = a_isl_get_rec_by_idx(ui1_index, &t_isl_rec);

        if (i4_ret != REST_R_OK)
        {
            return REST_R_ERR;
        }

        if ((t_isl_rec.e_src_type == e_src_type) &&
            (INP_SRC_TYPE_TV      == e_src_type))
        {
            ui1_src_index = ui1_index;
            break;
        }
        else if ((t_isl_rec.e_src_type == e_src_type) &&
                 (t_isl_rec.t_avc_info.e_video_type == e_video_type))
        {
            if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
            {
                if (t_isl_rec.ui1_internal_id != ui1_internal_id)
                {
                    continue;
                }
            }
            ui1_src_index = ui1_index;
            break;
        }
    }

    if (ui1_src_index < ui1_src_num)
    {
        a_cfg_av_set_input_src(SN_PRES_MAIN_DISPLAY, t_isl_rec.ui1_id);
    }

    return REST_R_OK;
}

static VOID _power_on_cec_dev_by_p_nfy_fct(VOID* pv_tag1, VOID* pv_tag2, VOID* pv_tag3)
{
    INT32 i4_ret = 0;
    CECM_CTRL_T t_cecmCtrl;
	CECM_DEV_T  t_devInfo;
    CECM_LOG_ADDR_T  e_la;
    UINT8  ui1_la;

    c_memset ((void*)&t_devInfo, 0, sizeof (CECM_DEV_T));
    t_cecmCtrl.b_sync = FALSE;

    for (ui1_la = CECM_LOG_ADDR_REC_DEV_1;ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST;ui1_la++)
    {
        i4_ret = c_cecm_get_dev_info_by_la (
                                    nav_cec_get_mw_handle (),
                                    (CECM_LOG_ADDR_T)ui1_la,
                                    &t_cecmCtrl,
                                    &t_devInfo);
        if (i4_ret != 0)
        {
            continue;
        }
        if (t_devInfo.e_dev_state != CECM_DEV_STATE_UPDATED || t_devInfo.t_report_phy_addr.ui2_pa == CECM_INV_PA)
        {
            continue;
        }
        else if (((UINT16)(UINT32)pv_tag1) == ((t_devInfo.t_report_phy_addr.ui2_pa >> 12)-1))
        {
            break;
        }
    }

    if (ui1_la < CECM_LOG_ADDR_UNREGED_BRDCST)
    {
        e_la = c_cecm_get_la_by_pa(nav_cec_get_mw_handle(), t_devInfo.t_report_phy_addr.ui2_pa);

        #ifdef APP_ARC_ONLY
        UINT8  ui1_cec_func = APP_CFG_CEC_OFF;
        a_cfg_get_cec_func(&ui1_cec_func);

        if (e_la == CECM_LOG_ADDR_AUD_SYS && ui1_cec_func != APP_CFG_CEC_ARC_ONLY) {
            REST_LOG_E("power on aud sys but isn't ARC only.\n\r");
            return;
        }
        #endif

        if ((i4_ret = c_cecm_set_stream_path(nav_cec_get_mw_handle(), e_la)) != 0) {
            REST_LOG_E("power on cec dev failed!\n\r");
        }
    }
}

static VOID _power_on_cec_dev_by_port(UINT16 ui2_port)
{
    nav_request_context_switch(_power_on_cec_dev_by_p_nfy_fct, (VOID*)(UINT32)ui2_port, NULL, NULL);
}

HANDLE_T get_crnt_svctx(VOID)
{
    TV_WIN_ID_T     t_win_id;
    HANDLE_T        h_crnt_svctx;

    a_tv_get_focus_win(&t_win_id);

    if(t_win_id == TV_WIN_ID_MAIN)
    {
        c_svctx_open(SVCTX_NAME_MAIN,&h_crnt_svctx);
        return h_crnt_svctx;
    }
    else if(t_win_id == TV_WIN_ID_SUB)
    {
        c_svctx_open(SVCTX_NAME_SUB,&h_crnt_svctx);
        return h_crnt_svctx;
    }
    else
    {
        REST_LOG_I("[NAV REVOLT_MISC] Could not get current svctx. \n");
    }

    return NULL_HANDLE;
}
int rest_chg_input_src(VOID)
{
    REST_LOG_I("[10FAPPCHECKPOINT] Enter\n\r");

    CHAR       s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8      ui1_input_id = 0;
    ISL_REC_T  t_isl_rec;
    INT32      i4_ret;
    TV_WIN_ID_T t_tv_win_id;
    //TV_INPUT_SOURCE_PARAM_T  t_inp_src_param;
    //HANDLE_T    h_main_svctx;
    //UINT32 ui4_stream_mode = ST_MASK_VIDEO|ST_MASK_AUDIO;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    LOG_ON_ERR(i4_ret);
    REST_LOG_I("s_disp_name:%s\n\r", s_disp_name);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    LOG_ON_ERR(i4_ret);
    REST_LOG_I("ui1_input_id:%d\n\r", ui1_input_id);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    LOG_ON_ERR(i4_ret);
    //c_memset (&t_inp_src_param, 0, sizeof(TV_INPUT_SOURCE_PARAM_T));
    //t_inp_src_param.b_pause_msg_converter = TRUE;

    //h_main_svctx = get_crnt_svctx();

    if (a_c4tv_apron_check_cast_state()
        && t_isl_rec.t_avc_info.e_video_type != DEV_VTRL_CAST)
    {
        REST_LOG_I("Enter\n\r");

        ACFG_RETAIL_MODE_T retm_status = ACFG_RETAIL_MODE_HOME;
        i4_ret = a_cfg_custom_get_retail_mode_setting(&retm_status);
        if (APP_CFGR_OK == i4_ret && ACFG_RETAIL_MODE_NORMAL == retm_status)
        {
            REST_LOG_I("\r[RETLMOD_DONNT_EXIT_CAST] %s LINE=%d\n", __FILE__, __LINE__);
        }
        else
        {
            /*Avoid nav_input start cast to cannot change to TV/AV source*/
            a_nav_ipts_src_set_c4tv_apron_exit_status(TRUE);
            REST_LOG_I("Call a_c4tv_apron_revoke_exit_cast\n\r");
            i4_ret = a_c4tv_apron_revoke_exit_cast(a_nav_ipts_src_c4tv_apron_custom_nfy);
            LOG_ON_ERR(i4_ret);
            return 0;
        }
    }

#if 1
	acfg_tv_get_focus_win(&t_tv_win_id);
	i4_ret = nav_ipts_switch_src(NAV_IPTS_SMS_BY_ID,t_tv_win_id,t_isl_rec.ui1_id);

    //start mm querry timer if need
    banner_view_mm_update_start_timer();

#else
    REST_LOG_I("Call a_nav_change_input_src\n\r");
    acfg_tv_get_focus_win(&t_tv_win_id);
    i4_ret = a_nav_change_input_src(t_tv_win_id, t_isl_rec.ui1_id) ? 0 : -1;
#endif
/*      i4_ret = a_tv_change_input_src_by_rec_ex(
                        h_main_svctx,
                        ui4_stream_mode,
                        &t_isl_rec,
                        NULL,
                        &t_inp_src_param
                        );
*/

    LOG_ON_ERR(i4_ret);
    return 0;
}

/*
*  This api will cause c4tv_apron grant resource to cast_shell only if in completely power on state
*/
INT32 chg_inp_src(INP_SRC_TYPE_T e_src_type, DEVICE_TYPE_T e_video_type, UINT8 ui1_internal_id)
{
    REST_LOG_I("Enter\n\r");

    _chg_inp_src(e_src_type,  e_video_type, ui1_internal_id);

    return rest_chg_input_src();
}

static VOID _rest_send_msg_to_tuner_setup_handler(VOID*    pv_tag1,
                                          VOID*    pv_tag2,
                                          VOID*    pv_tag3)
{
    REST_LOG_I("Enter\n\r");

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_TUNER_SETUP),
                              NAV_UI_MSG_REST_STOP_SCAN_TUNER,
                              pv_tag1);

}

int current_input(Json::Value & root, Json::Value & response)
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

            ISL_REC_T    t_isl_rec;
            UTF16_T*     w2s_name = NULL;
            CHAR         s_current_input[APP_CFG_CUSTOM_INP_NAME_LEN+1];
            c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
            c_memset(s_current_input, '\0', APP_CFG_CUSTOM_INP_NAME_LEN+1);

            i4_ret = a_nav_ipts_get_crnt_isl_rec(&t_isl_rec);
            LOG_ON_ERR(i4_ret);
            REST_LOG_I("e_src_type:%d, e_video_type:%d\n\r", t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);
            w2s_name = a_isl_get_display_name(&t_isl_rec);
            c_uc_w2s_to_ps(w2s_name, s_current_input, APP_CFG_CUSTOM_INP_NAME_LEN);
            REST_LOG_I("current input: %s.\n\r", s_current_input);
            string_set_response(response, s_current_input);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            ACFG_RETAIL_MODE_T			t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;

            a_cfg_custom_get_retail_mode_setting(&t_retail_mode);

			if(t_retail_mode == ACFG_RETAIL_MODE_NORMAL)
            {
                REST_LOG_I("retail mode is running, cann't change input src.\n\r");
                return 0;
            }

            if(nav_is_channel_scan_active())
            {
                nav_request_context_switch(_rest_send_msg_to_tuner_setup_handler,
                               NULL,
                               NULL,
                               NULL);
            }

            a_rest_set_test_patterns_turn_off();

            if (a_wzd_is_oobe_mode())
            {
                REST_LOG_I("OOBE status, cann't change input src.\n\r");
                return 0;
            }

            CHAR            s_target_input[256];
            CHAR            s_ori_input[APP_CFG_CUSTOM_INP_NAME_LEN+1];
            ISL_REC_T       t_isl_rec_ori;
            CHAR            s_active_app[32] = {0};
            UTF16_T*        w2s_name = NULL;
            UTF16_T         w2s_alias[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
            CHAR            str_source_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
            CHAR            str_alias_name[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
            UINT8           ui1_loop = 0;
            UINT8           ui1_isl_num = 0;
            ISL_REC_T       t_isl_rec;

            c_memset(s_target_input, '\0', 256);
            c_memset(s_ori_input, '\0', APP_CFG_CUSTOM_INP_NAME_LEN+1);
            c_memset(&t_isl_rec_ori, 0, sizeof(ISL_REC_T));
            c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));

            //get current input
            i4_ret = a_nav_ipts_get_crnt_isl_rec(&t_isl_rec_ori);
            LOG_ON_ERR(i4_ret);
            REST_LOG_I("e_src_type:%d, e_video_type:%d\n\r", t_isl_rec_ori.e_src_type,t_isl_rec_ori.t_avc_info.e_video_type);
            w2s_name = a_isl_get_display_name(&t_isl_rec_ori);
            c_uc_w2s_to_ps(w2s_name, s_ori_input, APP_CFG_CUSTOM_INP_NAME_LEN);
            REST_LOG_I("Original input: %s.\n\r", s_ori_input);

            //get current active app
            if (0 == a_am_get_active_app(s_active_app) &&
                0 == c_strcmp(s_active_app, "menu"))
            {
                a_amb_pause_app(s_active_app);
                REST_LOG_I("current active app is menu, exit it\r\n");
            }

            //get target input
            string_get_string(root, s_target_input, 256);
            string_get_string(root, g_current_input, 256);

            REST_LOG_I("Target input: %s\n\r", s_target_input);
            i4_ret = a_isl_get_num_rec(&ui1_isl_num);
            for (ui1_loop = 0; ui1_loop < ui1_isl_num; ui1_loop++)
            {
                c_memset (w2s_alias, 0, sizeof(w2s_alias));
                c_memset (str_source_name, 0, sizeof(str_source_name));
                c_memset (str_alias_name, 0, sizeof(str_alias_name));

                i4_ret = a_isl_get_rec_by_idx(ui1_loop, &t_isl_rec);

                w2s_name = a_isl_get_display_name(&t_isl_rec);
                a_isl_get_display_name_ex(&t_isl_rec, w2s_alias, APP_CFG_CUSTOM_INP_NAME_LEN);

                c_uc_w2s_to_ps(w2s_name, str_source_name, APP_CFG_CUSTOM_INP_NAME_LEN);
                c_uc_w2s_to_ps(w2s_alias, str_alias_name, APP_CFG_CUSTOM_INP_NAME_LEN);

                REST_LOG_I("input source ID: %d  input name: %s  alias name: %s\n", t_isl_rec.ui1_id,str_source_name,str_alias_name);

                if(strcmp(s_target_input, str_source_name) == 0)
                {
                    break;
                }
                else if(strcmp(s_target_input, str_alias_name) == 0)
                {
                    c_strcpy(s_target_input, str_source_name);
                    REST_LOG_I("Motify Target input to %s.\n\r", s_target_input);
                    break;
                }
            }

            if ((strcmp(s_target_input, "tuner") == 0) || (strcmp(s_target_input, "TV") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_TV, 0, 0);
                if(t_isl_rec_ori.e_src_type == INP_SRC_TYPE_VTRL)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_chg_input_src();
                }
            }
            else if ((strcmp(s_target_input, "hdmi1") == 0) || (strcmp(s_target_input, "hdmi") == 0) ||
                (strcmp(s_target_input, "HDMI-1") == 0) || (strcmp(s_target_input, "HDMI") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_chg_input_src();
                    _power_on_cec_dev_by_port(0);
                }
            }
            else if ((strcmp(s_target_input, "hdmi2") == 0) ||(strcmp(s_target_input, "HDMI-2") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_chg_input_src();
                    _power_on_cec_dev_by_port(1);
                }
            }
            else if ((strcmp(s_target_input, "hdmi3") == 0) || (strcmp(s_target_input, "HDMI-3") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_chg_input_src();
                    _power_on_cec_dev_by_port(2);
                }
            }
            else if ((strcmp(s_target_input, "hdmi4") == 0) || (strcmp(s_target_input, "HDMI-4") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_chg_input_src();
                    _power_on_cec_dev_by_port(3);
                }
            }
            else if ((strcmp(s_target_input, "hdmi5") == 0) || (strcmp(s_target_input, "HDMI-5") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_chg_input_src();
                    _power_on_cec_dev_by_port(4);
                }
            }
            else if ((strcmp(s_target_input, "comp") == 0) || (strcmp(s_target_input, "COMP") == 0))
            {
                UINT8 ui1_isl_num = 0;
                ISL_REC_T   t_isl_rec_tmp;
                a_isl_get_num_rec(&ui1_isl_num);
                for (int i=0; i<ui1_isl_num; i++)
                {
                    c_memset(&t_isl_rec_tmp, 0, sizeof(ISL_REC_T));
                    a_isl_get_rec_by_idx(i, &t_isl_rec_tmp);

                    if (DEV_AVC_COMP_VIDEO == t_isl_rec_tmp.t_avc_info.e_video_type)
                    {
                        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                        break;
                    }
                    else if (DEV_AVC_COMBI == t_isl_rec_tmp.t_avc_info.e_video_type)
                    {
                        _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                        break;
                    }
                }
                if (strcmp(s_ori_input, "USB") == 0)
                {
                    a_amb_resume_app(NAV_NAME);
                }
                else
                {
                    rest_chg_input_src();
                }
            }
            else if ((strcmp(s_target_input, "av") == 0) ||(strcmp(s_target_input, "AV") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
                rest_chg_input_src();
            }
            else if ((strcmp(s_target_input, "CAST") == 0) || (strcmp(s_target_input, "SMARTCAST") == 0)
                || (strcmp(s_target_input, "cast") == 0) || (strcmp(s_target_input, "SmartCast") == 0))
            {
                ACFG_RETAIL_MODE_T retm_status = ACFG_RETAIL_MODE_HOME;
                i4_ret = a_cfg_custom_get_retail_mode_setting(&retm_status);
                if (APP_CFGR_OK == i4_ret && ACFG_RETAIL_MODE_NORMAL == retm_status)
                {
                    DBG_LOG_PRINT(("\r[RETLMOD_DONNT_EXIT_CAST] %s LINE=%d\n", __FILE__, __LINE__));
                }
                else
                {
                    _chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_CAST, 0);
                    rest_chg_input_src();
                    a_nav_show_banner_ex();
                }
            }
            else if ((strcmp(s_target_input, "vga") == 0) || (strcmp(s_target_input, "VGA") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
                rest_chg_input_src();
            }
            else if ((strcmp(s_target_input, "usb") == 0) || (strcmp(s_target_input, "USB") == 0))
            {
                _chg_inp_src(INP_SRC_TYPE_VTRL, DEV_VTRL_MMP, 0);
                rest_chg_input_src();
            }
            else if ((strcmp(s_target_input, "WatchFree") == 0) || (strcmp(s_target_input, "watchfree") == 0))
            {
                //for banner info
                a_nav_ipts_select_virtual_input("watchfree");
            }
            else if ((strcmp(s_target_input, "AirPlay") == 0) || (strcmp(s_target_input, "airplay") == 0))
            {
                //for banner info
                a_nav_ipts_select_virtual_input("airplay");
            }
            else
            {
                _chg_inp_src(INP_SRC_TYPE_TV, 0, 0);
                rest_chg_input_src();
            }

            if (c_strcmp(s_target_input, s_ori_input) != 0) {
                if ((c_strcmp(s_target_input, "SMARTCAST") == 0) || (c_strcmp(s_target_input, "CAST") == 0)
                    || (strcmp(s_target_input, "cast") == 0) || (strcmp(s_target_input, "SmartCast") == 0)) {
                    REST_LOG_I("Launch SCH\n\r");
                    if (t_isl_rec_ori.t_avc_info.e_video_type == DEV_VTRL_CAST)
                    {
                        rest_event_notify_current_input("CAST:SMARTCAST");
                    }
                    else
                    {
                        _rest_app_launch_app_by_keycode(0x2d, 1);
                    }
                } else if ((strcmp(s_target_input, "WatchFree") == 0) || (strcmp(s_target_input, "watchfree") == 0)) {
                    rest_event_notify_current_input("CAST:watchfree");
                } else if ((strcmp(s_target_input, "AirPlay") == 0) || (strcmp(s_target_input, "airplay") == 0)) {
                    rest_event_notify_current_input("CAST:airplay");
                } else {
                    rest_event_notify_current_input("");
                }
            }

            break;
        }
        default:
            break;
    }

    return 0;
}

int hdmi_color_hdmi1(Json::Value & root, Json::Value & response) { return 0; }
int hdmi_color_hdmi2(Json::Value & root, Json::Value & response) { return 0; }
int hdmi_color_hdmi3(Json::Value & root, Json::Value & response) { return 0; }
int hdmi_color_hdmi4(Json::Value & root, Json::Value & response) { return 0; }
int hdmi_color_hdmi5(Json::Value & root, Json::Value & response) { return 0; }

int full_chroma_hdmi1(Json::Value & root, Json::Value & response) { return 0; }
int full_chroma_hdmi2(Json::Value & root, Json::Value & response) { return 0; }
int full_chroma_hdmi3(Json::Value & root, Json::Value & response) { return 0; }
int full_chroma_hdmi4(Json::Value & root, Json::Value & response) { return 0; }
int full_chroma_hdmi5(Json::Value & root, Json::Value & response) { return 0; }

UINT8 u1_notify_hdmi_format = 0;
static HANDLE_T h_g_full_clor_timer = NULL_HANDLE;
static UINT32 u4_g_full_color_hlt_hdmi_idx;
static UINT32 i4_tts_id = -1;

static VOID full_color_second_notify(VOID*        pv_tag1,
                                        VOID*        pv_tag2,
                                        VOID*        pv_tag3)
{
    WDK_TOAST_T t_toast;
    UTF16_T w2s_string[256]  = {0};
    UTF16_T *pw2s_text = NULL;

    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_STRING;

    pw2s_text = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_HDMI_MODE_SET_OK);


    c_uc_w2s_strcpy(w2s_string, pw2s_text);
    t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
    rest_send_msg_to_nav(&t_toast);

    return ;
}

static VOID _full_clor_timer_nfy(HANDLE_T    h_timer,
                                     VOID*    pv_tag)
{
      nav_request_context_switch( full_color_second_notify, pv_tag, NULL, NULL);
}

static VOID _set_full_color_tts_notify(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag)
{
    if(ui4_tts_play_id == i4_tts_id &&
       e_tts_str_state == TTS_STR_ST_PLAYED )
    {
        DBG_LOG_PRINT(("[%s %d]############# TTS_STR_ST_PLAYED,ui1_hdmi_index = %d,ui_hdmi_format = %d\n",__FUNCTION__,__LINE__,u4_g_full_color_hlt_hdmi_idx,u1_notify_hdmi_format));
        i4_tts_id = -1;
        if( 0 != inp_lst_set_edid_by_port(u4_g_full_color_hlt_hdmi_idx,u1_notify_hdmi_format,FALSE))
        {
           DBG_LOG_PRINT(("[%s %d] inp_lst_set_edid_by_port failed\n",__FUNCTION__,__LINE__));
        }
        a_app_tts_nfy_unreg(_set_full_color_tts_notify);
        /* ps : if tts play slowly show delay longer that other status*/
        if(0 != c_timer_start(h_g_full_clor_timer,
                               3000,
                               X_TIMER_FLAG_ONCE,
                               _full_clor_timer_nfy,
                               NULL))
        {
            DBG_LOG_PRINT(("[%s %d] c_timer_start failed\n",__FUNCTION__,__LINE__));
        }
    }

    if(e_tts_str_state == TTS_STR_ST_PLAYING )
    {
        DBG_LOG_PRINT(("[%s %d]############# TTS_STR_ST_PLAYING ui4_tts_play_id = %d\n",__FUNCTION__,__LINE__,ui4_tts_play_id));
        i4_tts_id = ui4_tts_play_id;
    }
}

static VOID update_full_color_info(UINT32 u4_crnt_full_color_hdmi_idx,UINT8 ui1_color_value)
{
     WDK_TOAST_T t_toast;
     UINT8       i1_switch = 0;
	 UTF16_T     w2s_tmp_str[512] = {0};
	 INT32       i4_ret;

	 if(NULL_HANDLE == h_g_full_clor_timer)
		c_timer_create(&h_g_full_clor_timer);
	 else
	 	c_timer_stop(h_g_full_clor_timer);
	 u4_g_full_color_hlt_hdmi_idx = u4_crnt_full_color_hdmi_idx;
	 a_cfg_cust_set_full_uhd_color(ui1_color_value);
     a_cfg_get_tts_switch_status(&i1_switch);
     if(a_app_tts_is_enable())
     {
            i4_ret = a_app_tts_nfy_reg(_set_full_color_tts_notify,NULL);
            DBG_LOG_PRINT(("[%s %d]############# tts _set_full_color_tts_notify ret = %d hdmi idx = %d\n",__FUNCTION__,__LINE__,i4_ret,u4_crnt_full_color_hdmi_idx));
     }
     c_uc_w2s_strcpy(w2s_tmp_str, MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_HDMI_MODE_SET));
     c_memset((VOID*)&t_toast, 0x0, sizeof(WDK_TOAST_T));
     t_toast.e_toast_style  = WDK_WARNING_TOAST;
     t_toast.e_string_style = WDK_STRING_STRING;
     t_toast.style.style_4.w2s_str = (VOID*)w2s_tmp_str;
     rest_send_msg_to_nav(&t_toast);
     if(!a_app_tts_is_enable())
     {
         if( 0 != inp_lst_set_edid_by_port(u4_crnt_full_color_hdmi_idx,u1_notify_hdmi_format,FALSE))
                       DBG_LOG_PRINT(("[%s %d] inp_lst_set_edid_by_port failed\n",__FUNCTION__,__LINE__));
         a_app_tts_nfy_unreg(_set_full_color_tts_notify);

         /* ps : if tts play slowly show delay longer that other status*/
         i4_ret = c_timer_start(h_g_full_clor_timer,
                                3000,
                                X_TIMER_FLAG_ONCE,
                                _full_clor_timer_nfy,
                                NULL);
            DBG_LOG_PRINT(("[%s %d]############# tts _set_full_color_tts_notify ret = %d\n",__FUNCTION__,__LINE__,i4_ret));
        }
}

INT32 hdmi_current_hdmi_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    UINT8 ui1_color_value = 0;
    ISL_REC_T   t_isl_rec;
    UINT16 ui2_hdmi_idx;

    menu_get_crnt_isl(&t_isl_rec);
    ui2_hdmi_idx = t_isl_rec.ui1_internal_id;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);

            if ((ui1_color_value >> ui2_hdmi_idx) & 0x01)
            {
                response["VALUE"] = std::string("On");
            }
            else
            {
                response["VALUE"] = std::string("OFF");
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            CHAR str[32] = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item1 = root["message"];
            item2 = item1["VALUE"];

            c_strcpy(str, item2.asString().c_str());

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);
            if(c_strcmp(str,"On") == 0)
            {
                ui1_color_value |= (UINT8)1 << ui2_hdmi_idx;
                u1_notify_hdmi_format = 1;
            }
            else
            {
                ui1_color_value &= ~((UINT8)1 << ui2_hdmi_idx);
                u1_notify_hdmi_format = 0;
            }
            update_full_color_info(ui2_hdmi_idx+1,ui1_color_value);
            break;
        }
        default:
        break;
    }

    return 0;
}


int hdmi1_hdmi_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    UINT8 ui1_hdmi_index = 1;
    UINT8 ui1_color_value = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);

            if ((ui1_color_value >> (ui1_hdmi_index - 1)) & 0x01)
            {
                response["VALUE"] = std::string("On");
            }
            else
            {
                response["VALUE"] = std::string("OFF");
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            CHAR str[32] = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item1 = root["message"];
            item2 = item1["VALUE"];

            c_strcpy(str, item2.asString().c_str());

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);
            if(c_strcmp(str,"On") == 0)
            {
                ui1_color_value |= (UINT8)1 << (ui1_hdmi_index - 1);
                u1_notify_hdmi_format = 1;
            }
            else
            {
                ui1_color_value &= ~((UINT8)1 << (ui1_hdmi_index - 1));
                u1_notify_hdmi_format = 0;
            }
            update_full_color_info(ui1_hdmi_index,ui1_color_value);
            break;
        }
        default:
        break;
    }

    return 0;
}
int hdmi2_hdmi_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    UINT8 ui1_hdmi_index = 2;
    UINT8 ui1_color_value = 0;

        type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);

            if ((ui1_color_value >> (ui1_hdmi_index - 1)) & 0x01)
            {
                response["VALUE"] = std::string("On");
            }
            else
            {
                response["VALUE"] = std::string("OFF");
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            char str[32] = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item1 = root["message"];
            item2 = item1["VALUE"];

            c_strcpy(str, item2.asString().c_str());

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);
            if (c_strcmp(str, "On") == 0)
            {
                ui1_color_value |= (UINT8)1 << (ui1_hdmi_index - 1);
                u1_notify_hdmi_format = 1;
            }
            else
            {
                ui1_color_value &= ~((UINT8)1 << (ui1_hdmi_index - 1));
                u1_notify_hdmi_format = 0;
            }

            update_full_color_info(ui1_hdmi_index,ui1_color_value);
            break;
        }
        default:
        break;
    }

        return 0;
}

int hdmi3_hdmi_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    UINT8 ui1_hdmi_index = 3;
    UINT8 ui1_color_value = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);

            if ((ui1_color_value >> (ui1_hdmi_index - 1)) & 0x01)
            {
                response["VALUE"] = std::string("On");
            }
            else
            {
                response["VALUE"] = std::string("OFF");
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            char str[32] = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item1 = root["message"];
            item2 = item1["VALUE"];

            c_strcpy(str, item2.asString().c_str());

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);
            if (c_strcmp(str, "On") == 0)
            {
                ui1_color_value |= (UINT8)1 << (ui1_hdmi_index - 1);
                u1_notify_hdmi_format = 1;
            }
            else
            {
                ui1_color_value &= ~((UINT8)1 << (ui1_hdmi_index - 1));
                u1_notify_hdmi_format = 0;
            }

            update_full_color_info(ui1_hdmi_index,ui1_color_value);
            break;
        }
        default:
        break;
    }

    return 0;
}
int hdmi4_hdmi_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    UINT8 ui1_hdmi_index = 4;
    UINT8 ui1_color_value = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);

            if ((ui1_color_value >> (ui1_hdmi_index - 1)) & 0x01)
            {
                response["VALUE"] = std::string("On");
            }
            else
            {
                response["VALUE"] = std::string("OFF");
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            char str[32] = {0};
            WDK_TOAST_T t_toast;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item1 = root["message"];
            item2 = item1["VALUE"];

            c_strcpy(str, item2.asString().c_str());

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);
            if (c_strcmp(str, "On") == 0)
            {
                ui1_color_value |= (UINT8)1 << (ui1_hdmi_index - 1);
                u1_notify_hdmi_format = 1;
            }
            else
            {
                ui1_color_value &= ~((UINT8)1 << (ui1_hdmi_index - 1));
                u1_notify_hdmi_format = 0;
            }

            update_full_color_info(ui1_hdmi_index,ui1_color_value);
            break;
        }
        default:
        break;
    }
    return 0;
}

int hdmi5_hdmi_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    UINT8 ui1_hdmi_index = 5;
    UINT8 ui1_color_value = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);

            if ((ui1_color_value >> (ui1_hdmi_index - 1)) & 0x01)
            {
                response["VALUE"] = std::string("On");
            }
            else
            {
                response["VALUE"] = std::string("OFF");
            }

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            char str[32] = {0};
            WDK_TOAST_T t_toast;
            UINT32 i4_ret = 0;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            Json::Value item1;
            Json::Value item2;

            item1 = root["message"];
            item2 = item1["VALUE"];

            c_strcpy(str, item2.asString().c_str());

            a_cfg_cust_get_full_uhd_color(&ui1_color_value);
            if (c_strcmp(str, "On") == 0)
            {
                ui1_color_value |= (UINT8)1 << (ui1_hdmi_index - 1);
                u1_notify_hdmi_format = 1;
            }
            else
            {
                ui1_color_value &= ~((UINT8)1 << (ui1_hdmi_index - 1));
                u1_notify_hdmi_format = 0;
            }

            update_full_color_info(ui1_hdmi_index,ui1_color_value);
            break;
        }
        default:
        break;
    }
    return 0;
}

int name_input_tuner(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            input["NAME"]     = std::string("TV");
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

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


int name_input_vga(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 src_indx =0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
            a_cfg_custom_get_inp_name(src_indx, str);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "VGA is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_VGA, 0);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_inp_name(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_VGA));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }

    return 0;
}

INT32 auto_size_position(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    WDK_TOAST_T t_toast;

    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_ID_ID;
    t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_VID_PIC_ADJUST;
    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_COMPLETE;

    auto_size_postion_start(&t_toast);

    return 0;
}

INT32 picture_size_horizontal(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_hsize = 0;
    UINT8   ui1_input = 0xFF;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    SIZE_T  z_size = sizeof(INT16);
    ISL_REC_T t_isl_rec;
    WDK_TOAST_T t_toast;

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    REST_LOG_I("VGA src_type:%d,video_type:%d\n\r",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
            {
                acfg_get(IDX_CUSTOM_VGA_H_SIZE, &i2_hsize, &z_size);
                REST_LOG_I("get:%d\n\r",i2_hsize);
            }
            else
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE),
                            &i2_hsize);
            }
            REST_LOG_I("get:%d\n\r",i2_hsize);
            value_set_response(response,i2_hsize);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            i2_hsize = value_get_value(root);
            REST_LOG_I("set:%d\n\r",i2_hsize);
            //i2_hsize += 50;
            if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
            {
                acfg_set(IDX_CUSTOM_VGA_H_SIZE, &i2_hsize, z_size);
            }
            else
            {
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE),
                            i2_hsize);
            }

            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
            a_cfg_update_viewport();

            vid_update_pic_size_info(ui1_input, i2_hsize, FALSE);


            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_PIC_SIZE_H;
            t_toast.style.style_1.i4_value      = (INT32)i2_hsize;
            t_toast.style.style_1.i4_max_val    = (INT32)50;

            rest_send_msg_to_nav(&t_toast);

            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 picture_size_vertical(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_hsize = 0;
    UINT8   ui1_input = 0xFF;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    SIZE_T  z_size = sizeof(INT16);
    ISL_REC_T t_isl_rec;
    WDK_TOAST_T t_toast;

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
    REST_LOG_I("VGA src_type:%d,video_type:%d\n\r",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
            {
                acfg_get(IDX_CUSTOM_VGA_V_SIZE, &i2_hsize, &z_size);
            }
            else
            {
                a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE),
                            &i2_hsize);
            }
            REST_LOG_I("get:%d\n\r",i2_hsize);
            value_set_response(response, i2_hsize);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            i2_hsize = value_get_value(root);
            REST_LOG_I("set:%d\n\r",i2_hsize);
            //i2_hsize += 50;

            if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
                && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
            {
                acfg_set(IDX_CUSTOM_VGA_V_SIZE, &i2_hsize, z_size);
            }
            else
            {
                a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE),
                            i2_hsize);
            }
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
            a_cfg_update_viewport();

            vid_update_pic_size_info(ui1_input, i2_hsize, TRUE);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_PIC_SIZE_V;
            t_toast.style.style_1.i4_value      = i2_hsize;
            t_toast.style.style_1.i4_max_val    = 50;

            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 picture_position_horizontal(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_vid_pos_h = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);
    UINT8   ui1_input = 0xFF;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    ISL_REC_T   t_isl_rec;
    WDK_TOAST_T t_toast;

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
    REST_LOG_I("VGA src_type:%d,video_type:%d\n\r",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_H);
    }
    else
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);
    }

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_av_get(ui2_id, &i2_vid_pos_h);
            REST_LOG_I("get:%d\n\r",i2_vid_pos_h);
            value_set_response(response, i2_vid_pos_h);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            i2_vid_pos_h = value_get_value(root);
            REST_LOG_I("set:%d\n\r",i2_vid_pos_h);
            a_cfg_av_set(ui2_id, i2_vid_pos_h);
            a_cfg_av_update(ui2_id);

            vid_update_position_info(ui1_input, i2_vid_pos_h, FALSE);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_PIC_POS_H;
            t_toast.style.style_1.i4_value      = i2_vid_pos_h;
            t_toast.style.style_1.i4_max_val    = 50;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

INT32 picture_position_vertical(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT16   i2_vid_pos_v = 0;
    UINT16  ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);
    UINT8   ui1_input = 0xFF;
    CHAR    s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    ISL_REC_T   t_isl_rec;
    WDK_TOAST_T t_toast;

    a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    a_cfg_av_get_input_src(s_disp_name, &ui1_input);
    a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

    REST_LOG_I("VGA src_type:%d,video_type:%d\n\r",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);
    if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV
        && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VGA, APP_CFG_RECID_VGA_POS_V);
    }
    else
    {
        ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);
    }

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_av_get(ui2_id, &i2_vid_pos_v);
            REST_LOG_I("get:%d\n\r",i2_vid_pos_v);
            value_set_response(response, i2_vid_pos_v);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            i2_vid_pos_v = value_get_value(root);
            REST_LOG_I("set:%d\n\r",i2_vid_pos_v);
            a_cfg_av_set(ui2_id, i2_vid_pos_v );
            a_cfg_av_update(ui2_id);

            vid_update_position_info(ui1_input, i2_vid_pos_v, TRUE);

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
            t_toast.e_string_style = WDK_STRING_TRACK;

            t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
            t_toast.style.style_1.ui4_id        = MLM_SETTINGS_KEY_VID_PIC_POS_V;
            t_toast.style.style_1.i4_value      = i2_vid_pos_v;
            t_toast.style.style_1.i4_max_val    = 50;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

int cast_name_input(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32 type = 0;

	type = get_type(root);

	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			REST_LOG_I("REQUEST_GET\n\r");

			Json::Value input;

			input["NAME"]	  = std::string("SMARTCAST");
			input["METADATA"] = std::string("");

			response["VALUE"] = input;

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
int hdmi1_name_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};//OSD_NAME_LENGTH----->15
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    CHAR model_name[32] = {0};

    i4_ret = a_cfg_custom_get_model_name(model_name);
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "HDMI-1 is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 0);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_inp_name(src_indx,str);

            if (c_strcmp(model_name, "D24h-E1") == 0)
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI1));
            }
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}
int hdmi2_name_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "HDMI-2 is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 1);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_inp_name(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI2));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}
int hdmi3_name_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "HDMI-3 is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};
            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 2);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_inp_name(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI3));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int hdmi4_name_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};
            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 3);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_inp_name(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI4));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int hdmi5_name_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    UTF16_T str_cec[APP_CFG_CUSTOM_INP_NAME_LEN + 1];
    INT32 src_indx =0;
    INT32 i4_ret=0;
    ISL_REC_T  t_isl_update = {0};

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
            i4_ret = a_isl_get_rec_by_idx(src_indx, &t_isl_update);
            LOG_ON_ERR(i4_ret);
            a_isl_get_display_name_ex(&t_isl_update, str_cec, APP_CFG_CUSTOM_INP_NAME_LEN);
            c_uc_w2s_to_ps(str_cec, str, APP_CFG_CUSTOM_INP_NAME_LEN);
            input["NAME"]     = std::string(str);
            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};
            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_HDMI, 4);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                break;
            }
            a_cfg_custom_set_inp_name(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI5));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int comp_name_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    CHAR    str[APP_CFG_CUSTOM_INP_NAME_LEN+1] = {0};
    INT32 src_indx =0;
    //WDK_TOAST_T t_toast;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value input;

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
            if (src_indx < 0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
            }
            a_cfg_custom_get_inp_name(src_indx, str);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (strcmp(str, "") == 0)
            {
                input["NAME"]     = std::string("COMP");
            }else
            {
                input["NAME"]     = std::string(str);
            }

            input["METADATA"] = std::string("");

            response["VALUE"] = input;

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            //CHAR        name_str[128] = "COMP is named ";
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[128] = {0};
            UTF16_T     str_3[16] = {0};

            item2 = root["message"];
            item1 = item2["VALUE"];
            c_strncpy(str,item1["NAME"].asString().c_str(),APP_CFG_CUSTOM_INP_NAME_LEN);

            src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMBI, 0);
            REST_LOG_I("str: %s,src_indx:%d\n\r", str,src_indx);
            if (src_indx<0)
            {
                src_indx = rest_get_src_indx(INP_SRC_TYPE_AV, DEV_AVC_COMP_VIDEO, 0);
                if (src_indx < 0)
                {
                    break;
                }
            }
            a_cfg_custom_set_inp_name(src_indx,str);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_COMP));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_3, 2);
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_NAMED));
            c_uc_w2s_strcat(w2s_string,str_1);
            c_uc_ps_to_w2s(str, str_2, 127);
            c_uc_w2s_strcat(w2s_string,str_2);
            c_uc_w2s_strcat(w2s_string,str_3);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int hdmi1_hide_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret =0;
    UINT8 ui1_hide_value = 0;
    CHAR model_name[32] = {0};

    i4_ret = a_cfg_custom_get_model_name(model_name);
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR string[64] = {0};
            a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
            if(((ui1_hide_value >> (1-1)) & (UINT8)1) == 1)
            {
                REST_LOG_I("REQUEST_GET, hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_HIDDEN), string, 64);
                //c_strncpy(string,"Hidden",7);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);

            }else
            {
                REST_LOG_I("REQUEST_GET, not hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_VISIBLE), string, 64);
                //c_strncpy(string,"Visible",8);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            CHAR s_target_value[256];
            c_memset(s_target_value, '\0', 256);
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[16] = {0};

            string_get_string(root, s_target_value, 256);
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Target value: %s\n\r", s_target_value);

            i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

            if (c_strcmp(model_name, "D24h-E1") == 0)
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI1));
            }
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_2, 2);
            c_uc_w2s_strcat(w2s_string,str_1);

            if (strcmp(s_target_value, "Visible") == 0)
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_VISIBLE));
                ui1_hide_value &= ~((UINT8)1 << (1 - 1));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_HIDDEN));
                ui1_hide_value |= (UINT8)1 << (1 - 1);
            }
            c_uc_w2s_strcat(w2s_string,str_2);

            i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            rest_event_notify("system/input/visible", 0,"hdmi1");
            break;
        }
        default:
        break;
    }

    return 0;
}


int hdmi2_hide_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret =0;
    UINT8 ui1_hide_value = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR    string[64] = {0};
            a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
            if(((ui1_hide_value >> (2-1)) & (UINT8)1) == 1)
            {
                REST_LOG_I("REQUEST_GET, hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_HIDDEN), string, 64);
                //c_strncpy(string,"Hidden",7);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);

            }else
            {
                REST_LOG_I("REQUEST_GET, not hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_VISIBLE), string, 64);
                //c_strncpy(string,"Visible",8);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            CHAR s_target_value[256];
            c_memset(s_target_value, '\0', 256);
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[16] = {0};

            string_get_string(root, s_target_value, 256);
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Target value: %s\n\r", s_target_value);

            i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI2));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_2, 2);
            c_uc_w2s_strcat(w2s_string,str_1);

            if (strcmp(s_target_value, "Visible") == 0)
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_VISIBLE));
                ui1_hide_value &= ~((UINT8)1 << (2 - 1));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_HIDDEN));
                ui1_hide_value |= (UINT8)1 << (2 - 1);
            }
            c_uc_w2s_strcat(w2s_string,str_2);

            i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            rest_event_notify("system/input/visible", 0,"hdmi2");
            break;
        }
        default:
        break;
    }

    return 0;
}


int hdmi3_hide_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret =0;
    UINT8 ui1_hide_value = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR string[64] = {0};
            a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
            if(((ui1_hide_value >> (3-1)) & (UINT8)1) == 1)
            {
                REST_LOG_I("REQUEST_GET, hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_HIDDEN), string, 64);
                //c_strncpy(string,"Hidden",7);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);

            }else
            {
                REST_LOG_I("REQUEST_GET, not hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_VISIBLE), string, 64);
                //c_strncpy(string,"Visible",8);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            CHAR s_target_value[256];
            c_memset(s_target_value, '\0', 256);
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[16] = {0};

            string_get_string(root, s_target_value, 256);
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Target value: %s\n\r", s_target_value);

            i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI3));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_2, 2);
            c_uc_w2s_strcat(w2s_string,str_1);

            if (strcmp(s_target_value, "Visible") == 0)
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_VISIBLE));
                ui1_hide_value &= ~((UINT8)1 << (3 - 1));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_HIDDEN));
                ui1_hide_value |= (UINT8)1 << (3 - 1);
            }
            c_uc_w2s_strcat(w2s_string,str_2);

            i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            rest_event_notify("system/input/visible", 0,"hdmi3");
            break;
        }
        default:
        break;
    }

    return 0;
}


int hdmi4_hide_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret =0;
    UINT8 ui1_hide_value = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR string[64] = {0};
            a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
            if(((ui1_hide_value >> (4-1)) & (UINT8)1) == 1)
            {
                REST_LOG_I("REQUEST_GET, hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_HIDDEN), string, 64);
                //c_strncpy(string,"Hidden",7);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);

            }else
            {
                REST_LOG_I("REQUEST_GET, not hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_VISIBLE), string, 64);
                //c_strncpy(string,"Visible",8);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            CHAR s_target_value[256];
            c_memset(s_target_value, '\0', 256);
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[16] = {0};

            string_get_string(root, s_target_value, 256);
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Target value: %s\n\r", s_target_value);

            i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI4));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_2, 2);
            c_uc_w2s_strcat(w2s_string,str_1);

            if (strcmp(s_target_value, "Visible") == 0)
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_VISIBLE));
                ui1_hide_value &= ~((UINT8)1 << (4 - 1));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_HIDDEN));
                ui1_hide_value |= (UINT8)1 << (4 - 1);
            }
            c_uc_w2s_strcat(w2s_string,str_2);

            i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            rest_event_notify("system/input/visible", 0,"hdmi4");
            break;
        }
        default:
        break;
    }

    return 0;
}


int hdmi5_hide_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret =0;
    UINT8 ui1_hide_value = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR string[64] = {0};
            a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
            if(((ui1_hide_value >> (5-1)) & (UINT8)1) == 1)
            {
                REST_LOG_I("REQUEST_GET, hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_HIDDEN), string, 64);
                //c_strncpy(string,"Hidden",7);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);

            }else
            {
                REST_LOG_I("REQUEST_GET, not hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_VISIBLE), string, 64);
                //c_strncpy(string,"Visible",8);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            CHAR s_target_value[256];
            c_memset(s_target_value, '\0', 256);
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[16] = {0};

            string_get_string(root, s_target_value, 256);
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Target value: %s\n\r", s_target_value);

            i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_HDMI5));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_2, 2);
            c_uc_w2s_strcat(w2s_string,str_1);

            if (strcmp(s_target_value, "Visible") == 0)
            {
                c_uc_w2s_strcat(w2s_string, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_VISIBLE));
                ui1_hide_value &= ~((UINT8)1 << (5 - 1));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_HIDDEN));
                ui1_hide_value |= (UINT8)1 << (5 - 1);
            }
            c_uc_w2s_strcat(w2s_string,str_2);

            i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            rest_event_notify("system/input/visible", 0,"hdmi5");
            break;
        }
        default:
        break;
    }

    return 0;
}

int comp_hide_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret =0;
    UINT8 ui1_hide_value = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR string[64] = {0};
            a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
            if(((ui1_hide_value >> (5)) & (UINT8)1) == 1)
            {
                REST_LOG_I("REQUEST_GET, hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_HIDDEN), string, 64);
                //c_strncpy(string,"Hidden",7);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);

            }else
            {
                REST_LOG_I("REQUEST_GET, not hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_VISIBLE), string, 64);
                //c_strncpy(string,"Visible",8);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            CHAR s_target_value[256];
            c_memset(s_target_value, '\0', 256);
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[16] = {0};

            string_get_string(root, s_target_value, 256);
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Target value: %s\n\r", s_target_value);

            i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_COMP));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_2, 2);
            c_uc_w2s_strcat(w2s_string,str_1);

            if (strcmp(s_target_value, "Visible") == 0)
            {
                c_uc_w2s_strcat(w2s_string, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_VISIBLE));
                ui1_hide_value &= ~((UINT8)1 << (5));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_HIDDEN));
                ui1_hide_value |= (UINT8)1 << (5);
            }
            c_uc_w2s_strcat(w2s_string,str_2);

            i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            rest_event_notify("system/input/visible", 0,"comp");
            break;
        }
        default:
        break;
    }

    return 0;
}

int hdmi1_picture_size_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_size_horizontal( root,response);
}
int hdmi1_picture_size_vertical(Json::Value & root, Json::Value & response)
{
    return picture_size_vertical(root, response);
}
int hdmi1_picture_position_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_position_horizontal(root,response);
}
int hdmi1_picture_position_vertical(Json::Value & root, Json::Value & response)
{
    return picture_position_vertical(root,response);
}

int hdmi2_picture_size_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_size_horizontal( root,response);
}
int hdmi2_picture_size_vertical(Json::Value & root, Json::Value & response)
{
    return picture_size_vertical(root, response);
}
int hdmi2_picture_position_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_position_horizontal(root,response);
}
int hdmi2_picture_position_vertical(Json::Value & root, Json::Value & response)
{
    return picture_position_vertical(root,response);
}

int hdmi3_picture_size_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_size_horizontal( root,response);
}
int hdmi3_picture_size_vertical(Json::Value & root, Json::Value & response)
{
    return picture_size_vertical(root, response);
}
int hdmi3_picture_position_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_position_horizontal(root,response);
}
int hdmi3_picture_position_vertical(Json::Value & root, Json::Value & response)
{
    return picture_position_vertical(root,response);
}

int hdmi4_picture_size_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_size_horizontal( root,response);
}
int hdmi4_picture_size_vertical(Json::Value & root, Json::Value & response)
{
    return picture_size_vertical(root, response);
}
int hdmi4_picture_position_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_position_horizontal(root,response);
}
int hdmi4_picture_position_vertical(Json::Value & root, Json::Value & response)
{
    return picture_position_vertical(root,response);
}

int hdmi5_picture_size_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_size_horizontal( root,response);
}
int hdmi5_picture_size_vertical(Json::Value & root, Json::Value & response)
{
    return picture_size_vertical(root, response);
}
int hdmi5_picture_position_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_position_horizontal(root,response);
}
int hdmi5_picture_position_vertical(Json::Value & root, Json::Value & response)
{
    return picture_position_vertical(root,response);
}

int comp_picture_size_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_size_horizontal( root,response);
}
int comp_picture_size_vertical(Json::Value & root, Json::Value & response)
{
    return picture_size_vertical(root, response);
}
int comp_picture_position_horizontal(Json::Value & root, Json::Value & response)
{
    return picture_position_horizontal(root,response);
}
int comp_picture_position_vertical(Json::Value & root, Json::Value & response)
{
    return picture_position_vertical(root,response);
}

int tuner_picture_size_horizontal(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	type = 0;
	INT16	i2_hsize = 0;
	UINT8	ui1_input = 0xFF;
	CHAR	s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};

	ISL_REC_T t_isl_rec;
	WDK_TOAST_T t_toast;

	a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
	a_cfg_av_get_input_src(s_disp_name, &ui1_input);
	a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

	REST_LOG_I("VGA src_type:%d,video_type:%d\n\r",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);
	type = get_type(root);

	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE),
			&i2_hsize);

			REST_LOG_I("get:%d\n\r",i2_hsize);
			value_set_response(response,i2_hsize);
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			i2_hsize = value_get_value(root);
			REST_LOG_I("set:%d\n\r",i2_hsize);
			a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_H_SIZE),
			i2_hsize);

			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
			a_cfg_update_viewport();

			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

			t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
			t_toast.e_string_style = WDK_STRING_TRACK;

			t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
			t_toast.style.style_1.ui4_id		= MLM_SETTINGS_KEY_VID_PIC_SIZE_H;
			t_toast.style.style_1.i4_value		= (INT32)i2_hsize;
			t_toast.style.style_1.i4_max_val	= (INT32)50;

			rest_send_msg_to_nav(&t_toast);

			break;
		}
		default:
		break;
	}
	return 0;
}

int tuner_picture_size_vertical(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	type = 0;
	INT16	i2_hsize = 0;
	UINT8	ui1_input = 0xFF;
	CHAR	s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};

	ISL_REC_T t_isl_rec;
	WDK_TOAST_T t_toast;

	a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
	a_cfg_av_get_input_src(s_disp_name, &ui1_input);
	a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
	REST_LOG_I("VGA src_type:%d,video_type:%d\n\r",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);
	type = get_type(root);

	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE),
							&i2_hsize);
			REST_LOG_I("get:%d\n\r",i2_hsize);
			value_set_response(response, i2_hsize);
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			i2_hsize = value_get_value(root);
			REST_LOG_I("set:%d\n\r",i2_hsize);

			a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_V_SIZE),
							i2_hsize);

			a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_OVERSCAN));
			a_cfg_update_viewport();

			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

			t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
			t_toast.e_string_style = WDK_STRING_TRACK;

			t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
			t_toast.style.style_1.ui4_id		= MLM_SETTINGS_KEY_VID_PIC_SIZE_V;
			t_toast.style.style_1.i4_value		= i2_hsize;
			t_toast.style.style_1.i4_max_val	= 50;

			rest_send_msg_to_nav(&t_toast);
			break;
		}
		default:
			break;
	}
	return 0;
}


int tuner_picture_position_horizontal(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	type = 0;
	INT16	i2_vid_pos_h = 0;
	UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);
	UINT8	ui1_input = 0xFF;
	CHAR	s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
	ISL_REC_T	t_isl_rec;
	WDK_TOAST_T t_toast;

	a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
	a_cfg_av_get_input_src(s_disp_name, &ui1_input);
	a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);
	REST_LOG_I("VGA src_type:%d,video_type:%d\n\r",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);

	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_H);


	type = get_type(root);

	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			a_cfg_av_get(ui2_id, &i2_vid_pos_h);
			REST_LOG_I("get:%d\n\r",i2_vid_pos_h);
			value_set_response(response, i2_vid_pos_h);
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			i2_vid_pos_h = value_get_value(root);
			REST_LOG_I("set:%d\n\r",i2_vid_pos_h);
			a_cfg_av_set(ui2_id, i2_vid_pos_h);
			a_cfg_av_update(ui2_id);

			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

			t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
			t_toast.e_string_style = WDK_STRING_TRACK;

			t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
			t_toast.style.style_1.ui4_id		= MLM_SETTINGS_KEY_VID_PIC_POS_H;
			t_toast.style.style_1.i4_value		= i2_vid_pos_h;
			t_toast.style.style_1.i4_max_val	= 50;
			rest_send_msg_to_nav(&t_toast);
			break;
		}
		default:
			break;
	}
	return 0;
}

int tuner_picture_position_vertical(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");
	INT32	type = 0;
	INT16	i2_vid_pos_v = 0;
	UINT16	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);
	UINT8	ui1_input = 0xFF;
	CHAR	s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
	ISL_REC_T	t_isl_rec;
	WDK_TOAST_T t_toast;

	a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
	a_cfg_av_get_input_src(s_disp_name, &ui1_input);
	a_isl_get_rec_by_idx (ui1_input, &t_isl_rec);

	REST_LOG_I("VGA src_type:%d,video_type:%d\n\r",t_isl_rec.e_src_type,t_isl_rec.t_avc_info.e_video_type);

	ui2_id = CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_POS_V);


	type = get_type(root);

	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			a_cfg_av_get(ui2_id, &i2_vid_pos_v);
			REST_LOG_I("get:%d\n\r",i2_vid_pos_v);
			value_set_response(response, i2_vid_pos_v);
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			i2_vid_pos_v = value_get_value(root);
			REST_LOG_I("set:%d\n\r",i2_vid_pos_v);
			a_cfg_av_set(ui2_id, i2_vid_pos_v );
			a_cfg_av_update(ui2_id);

			memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

			t_toast.e_toast_style  = WDK_TOAST_SETTINGS_SLIDER;
			t_toast.e_string_style = WDK_STRING_TRACK;

			t_toast.style.style_1.e_track_style = WDK_TOAST_VOL_TRACK_HALF;
			t_toast.style.style_1.ui4_id		= MLM_SETTINGS_KEY_VID_PIC_POS_V;
			t_toast.style.style_1.i4_value		= i2_vid_pos_v;
			t_toast.style.style_1.i4_max_val	= 50;
			rest_send_msg_to_nav(&t_toast);
			break;
		}
		default:
			break;
	}
	return 0;
}


int tuner_hide_input(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    INT32 i4_ret =0;
    UINT8 ui1_hide_value = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            CHAR string[64] = {0};
            a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);
            if(((ui1_hide_value >> (6)) & (UINT8)1) == 1)
            {
                REST_LOG_I("REQUEST_GET, hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_HIDDEN), string, 64);
                //c_strncpy(string,"Hidden",7);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);

            }else
            {
                REST_LOG_I("REQUEST_GET, not hide\n\r");
                c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), MLM_SETTINGS_KEY_INPUT_IS_VISIBLE), string, 64);
                //c_strncpy(string,"Visible",8);
                REST_LOG_I("string: %s\n\r", string);
                string_set_response(response, string);
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            CHAR s_target_value[256];
            c_memset(s_target_value, '\0', 256);
            WDK_TOAST_T t_toast;
            UTF16_T     w2s_string[256]  = {0};
            UTF16_T     str_1[16] = {0};
            UTF16_T     str_2[16] = {0};

            string_get_string(root, s_target_value, 256);
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Target value: %s\n\r", s_target_value);

            i4_ret = a_cfg_cust_get_hide_from_input_manually(&ui1_hide_value);

            c_uc_w2s_strcat(w2s_string,REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_TUNER));
            c_uc_ps_to_w2s(" ", str_1, 2);
            c_uc_ps_to_w2s(".", str_2, 2);
            c_uc_w2s_strcat(w2s_string,str_1);

            if (strcmp(s_target_value, "Visible") == 0)
            {
                c_uc_w2s_strcat(w2s_string, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_VISIBLE));
                ui1_hide_value &= ~((UINT8)1 << (6));
            }
            else
            {
                c_uc_w2s_strcat(w2s_string, REST_SETTINGS_TEXT(MLM_SETTINGS_KEY_INPUT_IS_HIDDEN));
                ui1_hide_value |= (UINT8)1 << (6);
            }
            c_uc_w2s_strcat(w2s_string,str_2);

            i4_ret = a_cfg_cust_set_hide_from_input_manually(ui1_hide_value);

            c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_STRING;

            t_toast.style.style_4.w2s_str = (VOID*)w2s_string;
            rest_send_msg_to_nav(&t_toast);
            rest_event_notify("system/input/visible", 0,"tuner");
            break;
        }
        default:
        break;
    }

    return 0;
}

/*
T_INPUT_V2
{
    "CNAME": <string>,
    "NAME": <string>,
    "CUSTOM_NAME": <string>,
    "INPUT_TYPE": Enum.INPUT_TYPE, // INPUT_TYPE = Utils.enum('SYSTEM', 'VIRTUAL')
    "SELECTED": Boolean,
    "METADATA": <string>
}
*/
int _rest_devices_current_inputs(Json::Value & items, const char* s_input)
{
    REST_LOG_I("Enter. s_input: %s\n\r", s_input);

    INT32       i4_ret = 0;
    UINT8       ui1_isl_num = 0;
    ISL_REC_T   t_isl_iterate = {0};
    Json::Value item;
    CHAR        s_disp_name[SYS_NAME_LEN+1] = {0};
    UINT8       ui1_input_id = 0;
    int         j;
    CHAR        s_TV_disp_name[128] = {0};
    SVL_REC_T   t_svl_rec           = {0};
    CHAR        sz_channel_id[6]    = {0};
    CHAR        sz_channel_name[64] = {0};
    BOOL        b_found             = FALSE;

    i4_ret = a_isl_get_num_rec(&ui1_isl_num);
    if (ISLR_OK != i4_ret) {
        REST_LOG_E("a_isl_get_num_rec() failed. i4_ret = %d\r\n", i4_ret);
        return -1;
    }
    REST_LOG_E("ui1_isl_num = %d\r\n", ui1_isl_num);

    //i4_ret = a_cfg_custom_get_model_name(model_name);
    //REST_LOG_I("model_name = %s\r\n", model_name);

    j = 0;
    for (int i=0; i<ui1_isl_num; i++)
    {
        c_memset(&t_isl_iterate, 0, sizeof(ISL_REC_T));
        a_isl_get_rec_by_idx(i, &t_isl_iterate);
        if (ISLR_OK != i4_ret) {
            REST_LOG_E("a_isl_get_rec_by_idx failed. i4_ret = %d\r\n", i4_ret);
            return -1;
        }

        REST_LOG_I("get[%d] e_src_type:%d, e_video_type:%d\n\r", i, t_isl_iterate.e_src_type, t_isl_iterate.t_avc_info.e_video_type);
        // TODO: correct CUSTOM_NAME
        switch (t_isl_iterate.e_src_type)
        {
            case INP_SRC_TYPE_TV:
            {
                nav_get_crnt_svl_rec (&t_svl_rec, &b_found);
                nav_set_ch_num_and_name (&t_svl_rec, sz_channel_id, sz_channel_name) ;
                REST_LOG_E("%s  %s\r\n", sz_channel_id, sz_channel_name);
                if (0 == c_strcmp(sz_channel_id, "") && 0 == c_strcmp(sz_channel_id, ""))
                {
                    c_sprintf(s_TV_disp_name, "%s", "tuner");
                }
                else
                {
                    c_sprintf(s_TV_disp_name, "%s  %s", sz_channel_id, sz_channel_name);
                }
                item["CNAME"] = std::string("tuner");
                item["NAME"] = std::string("tuner");
                item["CUSTOM_NAME"] = std::string(s_TV_disp_name);
                item["INPUT_TYPE"] = 0;
                item["METADATA"] = "";
                if (c_strcmp(s_input, "tuner") == 0) {
                    item["SELECTED"] = (bool)TRUE;
                } else {
                    item["SELECTED"] = (bool)FALSE;
                }
                break;
            }
            case INP_SRC_TYPE_AV:
            {
                if (DEV_AVC_HDMI == t_isl_iterate.t_avc_info.e_video_type)
                {
                    if (0 == t_isl_iterate.ui1_internal_id)
                    {
                        /*if (c_strcmp(model_name, "D24h-E1") == 0)
                        {
                            REST_LOG_I("HDMI\n\r");
                            response["VALUE"] = std::string("HDMI");
                        }
                        else
                        {
                            REST_LOG_I("HDMI-1\n\r");
                            response["VALUE"] = std::string("HDMI-1");
                        }*/
                        item["CNAME"] = std::string("hdmi1");
                        item["NAME"] = std::string("HDMI-1");
                        item["CUSTOM_NAME"] = std::string("hdmi1");
                        if (c_strcmp(s_input, "hdmi1") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else if (1 == t_isl_iterate.ui1_internal_id)
                    {
                        item["CNAME"] = std::string("hdmi2");
                        item["NAME"] = std::string("HDMI-2");
                        item["CUSTOM_NAME"] = std::string("hdmi2");
                        if (c_strcmp(s_input, "hdmi2") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else if (2 == t_isl_iterate.ui1_internal_id)
                    {
                        item["CNAME"] = std::string("hdmi3");
                        item["NAME"] = std::string("HDMI-3");
                        item["CUSTOM_NAME"] = std::string("hdmi3");
                        if (c_strcmp(s_input, "hdmi3") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else if (3 == t_isl_iterate.ui1_internal_id)
                    {
                        item["CNAME"] = std::string("hdmi4");
                        item["NAME"] = std::string("HDMI-4");
                        item["CUSTOM_NAME"] = std::string("hdmi4");
                        if (c_strcmp(s_input, "hdmi4") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else
                    {
                        item["CNAME"] = std::string("hdmi5");
                        item["NAME"] = std::string("HDMI-5");
                        item["CUSTOM_NAME"] = std::string("hdmi5");
                        if (c_strcmp(s_input, "hdmi5") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                }
                else if (DEV_AVC_COMBI == t_isl_iterate.t_avc_info.e_video_type || DEV_AVC_COMP_VIDEO == t_isl_iterate.t_avc_info.e_video_type)
                {
                    item["CNAME"] = std::string("comp");
                    item["NAME"] = std::string("COMP");
                    item["CUSTOM_NAME"] = std::string("comp");
                    if (c_strcmp(s_input, "comp") == 0) {
                        item["SELECTED"] = (bool)TRUE;
                    } else {
                        item["SELECTED"] = (bool)FALSE;
                    }
                }
                else if (DEV_AVC_VGA == t_isl_iterate.t_avc_info.e_video_type)
                {
                    item["CNAME"] = std::string("vga");
                    item["NAME"] = std::string("vga");
                    item["CUSTOM_NAME"] = std::string("vga");
                    if (c_strcmp(s_input, "vga") == 0) {
                        item["SELECTED"] = (bool)TRUE;
                    } else {
                        item["SELECTED"] = (bool)FALSE;
                    }
                }
                else
                {
                    item["CNAME"] = std::string("tuner");
                    item["NAME"] = std::string("tuner");
                    item["CUSTOM_NAME"] = std::string("tuner");
                    if (c_strcmp(s_input, "tuner") == 0) {
                        item["SELECTED"] = (bool)TRUE;
                    } else {
                        item["SELECTED"] = (bool)FALSE;
                    }
                }
                item["INPUT_TYPE"] = 0;
                item["METADATA"] = "";
                break;
            }
            case INP_SRC_TYPE_VTRL:
            {
                if (DEV_VTRL_CAST == t_isl_iterate.t_avc_info.e_video_type)
                {
                    if (0 == t_isl_iterate.ui1_internal_id)
                    {
                        REST_LOG_I("SMARTCAST\n\r");
                        item["CNAME"] = std::string("cast");
                        item["NAME"] = std::string("cast");
                        item["CUSTOM_NAME"] = std::string("cast");
                        item["INPUT_TYPE"] = 0;
                        item["METADATA"] = "";
                        if (c_strcmp(s_input, "smartcast") == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                    else
                    {
                        TYPE_APP_INPUT  t_vtrl_input = {0};
                        //SIZE_T          z_size = 0;
                        //UINT16          ui2_cfg_idx;
                        //INT32           i4_ret;
                        CHAR            s_cname[24] = {0};

                        //ui2_cfg_idx = IDX_IPTS_VTRL_NAME_1 + t_isl_iterate.ui1_internal_id - 1;
                        c_memset(s_cname, 0, 24);
                        //i4_ret = acfg_get(ui2_cfg_idx, s_cname, &z_size);
						i4_ret = a_cfg_get_vtrl_name(t_isl_iterate.ui1_internal_id - 1, s_cname, APP_CFG_CUSTOM_INP_NAME_LEN);
                        if (c_strlen(s_cname) == 0) {
                            j++;
                            continue;
                        }
                        REST_LOG_I("Vtrl\n\r");
                        _rest_app_get_virtual_input(t_isl_iterate.s_src_name, &t_vtrl_input);
                        item["CNAME"] = t_isl_iterate.s_src_name;
                        item["NAME"] = t_vtrl_input.vtrl_input.s_name_en[0];
                        item["CUSTOM_NAME"] = t_isl_iterate.s_src_name;
                        item["INPUT_TYPE"] = 1;
                        item["METADATA"] = "";
                        if (c_strcmp(s_input, t_vtrl_input.vtrl_input.s_cname) == 0) {
                            item["SELECTED"] = (bool)TRUE;
                        } else {
                            item["SELECTED"] = (bool)FALSE;
                        }
                    }
                }
                else if (DEV_VTRL_MMP == t_isl_iterate.t_avc_info.e_video_type)
                {
                    item["CNAME"] = std::string("usb");
                    item["NAME"] = std::string("usb");
                    item["CUSTOM_NAME"] = std::string("usb");
                    item["INPUT_TYPE"] = 0;
                    item["METADATA"] = "";
                    if (c_strcmp(s_input, "usb") == 0) {
                        item["SELECTED"] = (bool)TRUE;
                    } else {
                        item["SELECTED"] = (bool)FALSE;
                    }
                }
                else
                {
                    REST_LOG_I("Not Valid\n\r");
                    continue;
                }
                break;
            }
            default:
            {
                item["CNAME"] = std::string("tuner");
                item["NAME"] = std::string("tuner");
                item["CUSTOM_NAME"] = std::string("tuner");
                item["INPUT_TYPE"] = 0;
                item["METADATA"] = "";
                if (c_strcmp(s_input, "tuner") == 0) {
                    item["SELECTED"] = (bool)TRUE;
                } else {
                    item["SELECTED"] = (bool)FALSE;
                }
                break;
            }
        }

        if (c_strcmp(s_input, "auto") == 0)
        {
            i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
            LOG_ON_ERR(i4_ret);
            i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
            LOG_ON_ERR(i4_ret);

            if (i == ui1_input_id) {
                item["SELECTED"] = (bool)TRUE;
            } else {
                item["SELECTED"] = (bool)FALSE;
            }
        }

        items[i-j] = item;
        //REST_LOG_I("item[%d]:%s\n\r", i-j, items[i-j].toStyledString().c_str());
    }

    return 0;
}

void _rest_devices_current_inputs_notification(const char* s_input)
{
    REST_LOG_I("Enter s_input: %s\n\r", s_input);

    Json::Value items;
    _rest_devices_current_inputs(items, s_input);
    //REST_LOG_I("items(len=%d): %s\n\r", c_strlen(items.toStyledString().c_str()), items.toStyledString().c_str());

    rest_event_notify("tv_settings/devices/current_inputs", 0, items.toStyledString().c_str());

    return;
}

// returns list of T_INPUT_V2 objects
int devices_current_inputs(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value items;
            _rest_devices_current_inputs(items, "auto");

            response["VALUE"] = items;
            break;
        }
        default:
            break;
    }

    return 0;
}

handler devices_handler[] = {
    name_input_cast,
    name_input_hdmi1,
    name_input_hdmi2,
    name_input_hdmi3,
    name_input_hdmi4,
    name_input_hdmi5,
    name_input_comp,
    current_input,
    hdmi1_hdmi_color,
    hdmi2_hdmi_color,
    hdmi3_hdmi_color,
    hdmi4_hdmi_color,
    hdmi5_hdmi_color,
    full_chroma_hdmi1,
    full_chroma_hdmi2,
    full_chroma_hdmi3,
    full_chroma_hdmi4,
    full_chroma_hdmi5,
    name_input_tuner,
    name_input_vga,
    auto_size_position,
    picture_size_horizontal,
    picture_size_vertical,
    picture_position_horizontal,
    picture_position_vertical,
    cast_name_input,
    hdmi1_name_input,
    hdmi2_name_input,
    hdmi3_name_input,
    hdmi4_name_input,
    hdmi5_name_input,
    comp_name_input,
    hdmi1_hide_input,
    hdmi2_hide_input,
    hdmi3_hide_input,
    hdmi4_hide_input,
    hdmi5_hide_input,
    comp_hide_input,
    tuner_picture_size_horizontal,
    tuner_picture_size_vertical,
    tuner_picture_position_horizontal,
    tuner_picture_position_vertical,
    tuner_hide_input,
    devices_current_inputs,
    hdmi1_picture_size_horizontal,
    hdmi1_picture_size_vertical,
    hdmi1_picture_position_horizontal,
    hdmi1_picture_position_vertical,
    hdmi2_picture_size_horizontal,
    hdmi2_picture_size_vertical,
    hdmi2_picture_position_horizontal,
    hdmi2_picture_position_vertical,
    hdmi3_picture_size_horizontal,
    hdmi3_picture_size_vertical,
    hdmi3_picture_position_horizontal,
    hdmi3_picture_position_vertical,
    hdmi4_picture_size_horizontal,
    hdmi4_picture_size_vertical,
    hdmi4_picture_position_horizontal,
    hdmi4_picture_position_vertical,
    hdmi5_picture_size_horizontal,
    hdmi5_picture_size_vertical,
    hdmi5_picture_position_horizontal,
    hdmi5_picture_position_vertical,
    comp_picture_size_horizontal,
    comp_picture_size_vertical,
    comp_picture_position_horizontal,
    comp_picture_position_vertical,
};

