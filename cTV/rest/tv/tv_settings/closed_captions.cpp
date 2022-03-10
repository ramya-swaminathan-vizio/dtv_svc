#include <iostream>
#include <bits/unique_ptr.h>
#include <handler.h>
#include "closed_captions.h"
#include "common.h"
#include "argument.h"
#include <string.h>


#ifdef __cplusplus
extern "C" {
#include "u_scc.h"
#include "u_gl.h"
#include "u_sys_name.h"
#include "nav/nav_common.h"
#include "nav/nav_comp_id.h"
#include "menu2/a_menu.h"
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "app_util/a_icl.h"
#include "app_util/icl/a_icl_custom.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "nav/revolt_misc/closed_captions_view.h"
#include "nav/cc_info/cc_info.h"
#include "nav/revolt_info/revolt_info.h"
}
#endif
#define CS_FS_STYLE1    SN_FONT_MONO_SP_SERF
#define CS_FS_STYLE2    SN_FONT_PROP_SP_SERF
#define CS_FS_STYLE3    SN_FONT_MONO_SP_WO_SERF
#define CS_FS_STYLE4    SN_FONT_PROP_SP_WO_SERF
#define CS_FS_STYLE5    SN_FONT_CASUAL
#define CS_FS_STYLE6    SN_FONT_CURSIVE
#define CS_FS_STYLE7    SN_FONT_SMALL_CAPITALS

static GL_COLOR_T t_g_color_black       = {255, {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_color_white       = {255, {255}, {255}, {255}};
static GL_COLOR_T t_g_color_green       = {255, {  0}, {255}, {  0}};
static GL_COLOR_T t_g_color_blue        = {255, {  0}, {  0}, {255}};
static GL_COLOR_T t_g_color_red         = {255, {255}, {  0}, {  0}};
static GL_COLOR_T t_g_color_cyan        = {255, {  0}, {255}, {255}};
static GL_COLOR_T t_g_color_yellow      = {255, {255}, {255}, {  0}};
static GL_COLOR_T t_g_color_magenta     = {255, {255}, {  0}, {255}};
static GL_COLOR_T t_g_color_broadcast   = {255, {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_opac_solid        = {255, {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_opac_transp       = {0  , {  0}, {  0}, {  0}};
static GL_COLOR_T t_g_opac_transl       = {127, {  0}, {  0}, {  0}};
static CC_CAP_STL_DATA_T t_cap = {0};

TvSettingsGroupURI tvSettingsClosedCaptionsUri[] = {
    /*
    # CLOSED CAPTIONS
    */

    { "closed_captions_enabled"} ,
    { "analog_closed_captions"} ,
    { "digital_closed_captions"} ,
    { "digital_style"} ,
		{ "digital_style","text_style"} ,
		{ "digital_style","text_size"} ,
		{ "digital_style","text_color"} ,
		{ "digital_style","text_opacity"} ,
		{ "digital_style","text_edges"} ,
		{ "digital_style","text_edges_color"} ,
		{ "digital_style","background_color"} ,
		{ "digital_style","background_opacity"} ,
		{ "digital_style","window_color"} ,
		{ "digital_style","window_opacity"} ,
      /*{ "caption_style"} ,*/
    { "" },
};


static VOID _rest_send_cc_msg_to_nav_handler(VOID*    pv_tag1,
                                          VOID*    pv_tag2,
                                          VOID*    pv_tag3)
{
    REST_LOG_I("Enter\n\r");

    if (a_menu_get_cc_preview_visiable())
    {
        REST_LOG_I("Menu show cc preview, no need send again.\n\r");
        return;
    }

    nav_send_msg_to_component(NAV_MAKE_COMP_ID_BIT_MASK(NAV_COMP_ID_REVOLT_INFO),
                              NAV_UI_MSG_REST_CC,
                              pv_tag1);
}

VOID rest_send_cc_msg_to_nav(CC_CAP_STL_DATA_T*   pt_cap)
{
    REST_LOG_I("Enter\n\r");

    CC_CAP_STL_DATA_T* pt_cap_cpy = NULL;

    pt_cap_cpy = (CC_CAP_STL_DATA_T*)c_mem_alloc(sizeof(CC_CAP_STL_DATA_T));

    if (NULL == pt_cap_cpy)
    {
        REST_LOG_E("NULL == pt_cap_cpy!!\n");
        return;
    }

    c_memcpy((VOID*)pt_cap_cpy, (const VOID*)pt_cap, sizeof(CC_CAP_STL_DATA_T));

    nav_request_context_switch(_rest_send_cc_msg_to_nav_handler,
                               (VOID*) pt_cap_cpy,
                               NULL,
                               NULL);
}


int closed_captions_enabled(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    INT32   val = 0;
    UINT8   ui1_enabled = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    Json::Value block;
    block[0]= "Off";
    block[1]= "On";
    response["ELEMENTS"]=block;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_cc_enabled(&ui1_enabled);
            REST_LOG_I("closed_captions:%d\n\r", ui1_enabled);
            if(ui1_enabled == APP_CFG_CC_OFF)
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
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"Off") == 0)
            {
                ui1_enabled = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_OFF;
            }
            else if(c_strcmp(str,"On") == 0)
            {
                ui1_enabled = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_ON;
            }
            a_cfg_set_cc_enabled(ui1_enabled);
            INT32 i4_ret = 0;
            i4_ret = nav_ci_set_exec_cond((NAV_CI_EXEC_COND_T)ui1_enabled);
            if(i4_ret != NAVR_OK)
            {
                REST_LOG_E("nav_ci_set_exec_cond() failed. i4_ret = %d\r\n", i4_ret);
                return i4_ret;
            }
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }

    return 0;
}

int analog_closed_captions(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    Json::Value acc;
    acc[0]= "CC1";
    acc[1]= "CC2";
    acc[2]= "CC3";
    acc[3]= "CC4";
    response["ELEMENTS"]=acc;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_cc = APP_CFG_CUSTOM_ANA_CC_CC1;
            a_cfg_get_anlg_cc(&ui1_cc);
            REST_LOG_I("analog_closed_captions:%d\n\r", ui1_cc);
            response["VALUE"]=acc[ui1_cc];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT32   i4_ret = APP_CFGR_OK;
            UINT8   ui1_idx = 0;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_ANALOG;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"CC1") == 0)
            {
                ui1_idx = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC1;
            }
            else if(c_strcmp(str,"CC2") == 0)
            {
                ui1_idx = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC2;
            }
            else if(c_strcmp(str,"CC3") == 0)
            {
                ui1_idx = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC3;
            }
            else if(c_strcmp(str,"CC4") == 0)
            {
                ui1_idx = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC4;
            }

            i4_ret = a_cfg_set_anlg_cc(ui1_idx);

            if (APP_CFGR_OK == i4_ret)
            {
                a_cfg_custom_plf_opt_set_cc_onoff((UINT32)ui1_idx);
            }
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

int digital_closed_captions(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;
    CHAR    str[128] = {0};
    WDK_TOAST_T t_toast;

    Json::Value dcc;
    dcc[0]= "CS1";
    dcc[1]= "CS2";
    dcc[2]= "CS3";
    dcc[3]= "CS4";
    dcc[4]= "CS5";
    dcc[5]= "CS6";
    response["ELEMENTS"]=dcc;
    response["VALUE"]=dcc[0];

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_cc = APP_CFG_CUSTOM_DIG_CC_SERVICE1;
            a_cfg_get_dig_cc(&ui1_cc);
            REST_LOG_I("digital_closed_captions:%d\n\r", ui1_cc);
            response["VALUE"]=dcc[ui1_cc];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            INT32   i4_ret = APP_CFGR_OK;
            UINT8   ui1_idx = 0;

            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_DIGITAL;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"CS1") == 0)
            {
                ui1_idx = 0;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CS1;
            }
            else if(c_strcmp(str,"CS2") == 0)
            {
                ui1_idx = 1;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CS2;
            }
            else if(c_strcmp(str,"CS3") == 0)
            {
                ui1_idx = 2;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CS3;
            }
            else if(c_strcmp(str,"CS4") == 0)
            {
                ui1_idx = 3;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CS4;
            }
            else if(c_strcmp(str,"CS5") == 0)
            {
                ui1_idx = 4;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CS5;
            }
            else if(c_strcmp(str,"CS6") == 0)
            {
                ui1_idx = 5;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CS6;
            }

            i4_ret = a_cfg_set_dig_cc(ui1_idx);

            if (APP_CFGR_OK == i4_ret)
            {
                a_cfg_custom_plf_opt_set_cc_onoff((UINT32)ui1_idx);
            }
            rest_send_msg_to_nav(&t_toast);
            break;
        }
        default:
            break;
    }
    return 0;
}

int digital_style(Json::Value & root, Json::Value & response)
{
#if 0
    REST_LOG_I("Enter\n\r");
    INT32   type = 0;

    Json::Value stype;
    stype[0]= "As Broadcast";
    stype[1]= "Playbill";
    stype[2]= "Newsprint";
    stype[3]= "Computer";
    stype[4]= "Modern";
    stype[5]= "Casual";
    stype[6]= "Script";
    stype[7]= "Capitols";
    response["ELEMENTS"]=stype;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            response["VALUE"]=stype[0];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            break;
        }
        default:
            break;
    }
#endif
    return 0;
}

static UINT16 _text_style_get_font_style_idx(VOID)
{
    UINT8       ui1_value      = 0;
    UINT16      ui2_idx        = 0;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    a_cfg_get_dcs(APP_CFG_RECID_DCS_FONT_STYLE, &ui1_value);

    switch (ui1_value)
    {
   	case APP_CFG_DCS_FS_BROADCAST:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  SN_FONT_MONO_SP_WO_SERF);
        ui2_idx = 0;
		break;
    case APP_CFG_DCS_FS_STYLE1:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE1);
        ui2_idx = 1;
        break;
    case APP_CFG_DCS_FS_STYLE2:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE2);
        ui2_idx = 2;
        break;
    case APP_CFG_DCS_FS_STYLE3:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE3);
        ui2_idx = 3;
        break;
    case APP_CFG_DCS_FS_STYLE4:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE4);
        ui2_idx = 4;
        break;
    case APP_CFG_DCS_FS_STYLE5:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE5);
        ui2_idx = 5;
        break;
    case APP_CFG_DCS_FS_STYLE6:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE6);
        ui2_idx = 6;
        break;
    case APP_CFG_DCS_FS_STYLE7:
		CS_CPY_FS(pt_this->t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE7);
        ui2_idx = 7;
        break;
    default:
        ui2_idx = 0;
        break;
    }
    return ui2_idx;
}

static VOID _text_style_set_font_style(
                        CHAR*  ps_str)
{
    UINT8       ui1_font_style = APP_CFG_DCS_FS_BROADCAST;
    WDK_TOAST_T t_toast;
    memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_ID_ID;
    t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_STYLE;

    REST_LOG_I("str:%s\n\r",ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_font_style = APP_CFG_DCS_FS_BROADCAST;
        t_toast.style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_STYLE_AS_BRDCST;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  SN_FONT_MONO_SP_WO_SERF);
    }
    else if(c_strcmp(ps_str,"Playbill") == 0)
    {
        ui1_font_style = APP_CFG_DCS_FS_STYLE1;
        t_toast.style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_STYLE_PLAYBILL;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE1);
    }
    else if(c_strcmp(ps_str,"Newsprint") == 0)
    {
        ui1_font_style = APP_CFG_DCS_FS_STYLE2;
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_STYLE_NEWSPRINT;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE2);
    }
    else if(c_strcmp(ps_str,"Computer") == 0)
    {
        ui1_font_style = APP_CFG_DCS_FS_STYLE3;
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_STYLE_PC;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE3);
    }
    else if(c_strcmp(ps_str,"Modern") == 0)
    {
        ui1_font_style = APP_CFG_DCS_FS_STYLE4;
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_STYLE_MODERN;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE4);
    }
    else if(c_strcmp(ps_str,"Casual") == 0)
    {
        ui1_font_style = APP_CFG_DCS_FS_STYLE5;
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_STYLE_CASUAL;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE5);
    }
    else if(c_strcmp(ps_str,"Script") == 0)
    {
        ui1_font_style = APP_CFG_DCS_FS_STYLE6;
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_STYLE_SCRIPT;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE6);
    }
    else if(c_strcmp(ps_str,"Capitals") == 0)
    {
        ui1_font_style = APP_CFG_DCS_FS_STYLE7;
        t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_STYLE_CAPITAL;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  CS_FS_STYLE7);
    }
    else
    {
        ui1_font_style = APP_CFG_DCS_FS_BROADCAST;
        t_toast.style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_STYLE_AS_BRDCST;
        CS_CPY_FS(t_cap.t_cc_info.t_pen_font.t_font.s_font_name,
                  SN_FONT_MONO_SP_WO_SERF);
    }

    REST_LOG_I("ui1_font_style:%d\n\r",ui1_font_style);

    a_cfg_set_dcs(APP_CFG_RECID_DCS_FONT_STYLE, ui1_font_style);

    a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

    a_cfg_update_dcs();

    rest_send_msg_to_nav(&t_toast);
    rest_send_cc_msg_to_nav(&t_cap);
}


int digital_style_text_style(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8    i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    CHAR    text_style[8][32];
    INT16   i2_mlm_id[8] = {MLM_SETTINGS_KEY_CC_TEXT_STYLE_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_STYLE_PLAYBILL,
            MLM_SETTINGS_KEY_CC_TEXT_STYLE_NEWSPRINT,
            MLM_SETTINGS_KEY_CC_TEXT_STYLE_PC,
            MLM_SETTINGS_KEY_CC_TEXT_STYLE_MODERN,
            MLM_SETTINGS_KEY_CC_TEXT_STYLE_CASUAL,
            MLM_SETTINGS_KEY_CC_TEXT_STYLE_SCRIPT,
            MLM_SETTINGS_KEY_CC_TEXT_STYLE_CAPITAL};

    Json::Value stype;
    /* stype[0]= "As Broadcast";
    stype[1]= "Playbill";
    stype[2]= "Newsprint";
    stype[3]= "Computer";
    stype[4]= "Modern";
    stype[5]= "Casual";
    stype[6]= "Script";
    stype[7]= "Capitals"; */
    for (i = 0; i < 8; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), text_style[i], 32);
        stype[i] = text_style[i];
    }
    response["ELEMENTS"]=stype;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            ui2_idx = _text_style_get_font_style_idx();
            REST_LOG_I("text_style:%d\n\r", ui2_idx);
            response["VALUE"]=stype[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            _text_style_set_font_style(str);
            break;
        }
        default:
            break;
    }
    return 0;
}

int digital_style_text_size(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8    i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT8   ui1_font_size = APP_CFG_DCS_FZ_BROADCAST;
    UINT16  ui2_idx = 0;
    WDK_TOAST_T t_toast;
    CHAR    text_size[4][32];
    INT16   i2_mlm_id[4] = {MLM_SETTINGS_KEY_CC_TEXT_SIZE_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_SIZE_SMALL,
            MLM_SETTINGS_KEY_CC_TEXT_SIZE_MEDIUM,
            MLM_SETTINGS_KEY_CC_TEXT_SIZE_LARGE};

    Json::Value size;
    /* size[0]= "As Broadcast";
    size[1]= "Small";
    size[2]= "Medium";
    size[3]= "Large"; */
    for (i = 0; i < 4; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), text_size[i], 32);
        size[i] = text_size[i];
    }
    response["ELEMENTS"]=size;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            CC_CAP_STL_DATA_T *pt_this = &t_cap;

            a_cfg_get_dcs(APP_CFG_RECID_DCS_FONT_SIZE, &ui1_font_size);
            REST_LOG_I("text_size:%d\n\r", ui1_font_size);
            switch (ui1_font_size)
            {
                case APP_CFG_DCS_FZ_BROADCAST:
                    pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
                    ui2_idx = 0;
                    break;
                case APP_CFG_DCS_FZ_SMALL:
                    pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_SMALL;
                    ui2_idx = 1;
                    break;
                case APP_CFG_DCS_FZ_MEDIUN:
                    pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
                    ui2_idx = 2;
                    break;
                case APP_CFG_DCS_FZ_LARGE:
                    pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_LARGE;
                    ui2_idx = 3;
                    break;
                default:
                    pt_this->t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
                    ui2_idx = 0;
                    break;
            }
            response["VALUE"]=size[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_SIZE;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            REST_LOG_I("str:%s\n\r", str);
            if(c_strcmp(str,"As Broadcast") == 0)
            {
                ui1_font_size = APP_CFG_DCS_FZ_BROADCAST;
                t_toast.style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_SIZE_AS_BRDCST;
                t_cap.t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            }
            else if(c_strcmp(str,"Small") == 0)
            {
                ui1_font_size = APP_CFG_DCS_FZ_SMALL;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_SIZE_SMALL;
                t_cap.t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_SMALL;
            }
            else if(c_strcmp(str,"Medium") == 0)
            {
                ui1_font_size = APP_CFG_DCS_FZ_MEDIUN;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_SIZE_MEDIUM;
                t_cap.t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            }
            else if(c_strcmp(str,"Large") == 0)
            {
                ui1_font_size = APP_CFG_DCS_FZ_LARGE;
                t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_CC_TEXT_SIZE_LARGE;
                t_cap.t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_LARGE;
            }
            else
            {
                ui1_font_size = APP_CFG_DCS_FZ_BROADCAST;
                t_toast.style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_SIZE_AS_BRDCST;
                t_cap.t_cc_info.t_pen_font.t_font.e_size = FE_FNT_SIZE_MEDIUM;
            }
            a_cfg_set_dcs(APP_CFG_RECID_DCS_FONT_SIZE, ui1_font_size);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            a_cfg_update_dcs();
            DBG_LOG_PRINT(("[CC]e_size=[%d]", t_cap.t_cc_info.t_pen_font.t_font.e_size));
            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }
    return 0;
}

static UINT8 _text_color_set_color(CHAR*  ps_str,
                    WDK_TOAST_T* pt_toast,
                    CC_CAP_STL_DATA_T* pt_cap)
{
    UINT8       ui1_color = APP_CFG_DCS_CLR_BROADCAST;

    REST_LOG_I("str:%s\n\r", ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_broadcast);
    }
    else if(c_strcmp(ps_str,"Black") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BLACK;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLACK;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_black);
    }
    else if(c_strcmp(ps_str,"White") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_WHITE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
    }
    else if(c_strcmp(ps_str,"Green") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_GREEN;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_green);
    }
    else if(c_strcmp(ps_str,"Blue") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BLUE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_blue);
    }
    else if(c_strcmp(ps_str,"Red") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_RED;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_red);
    }
    else if(c_strcmp(ps_str,"Cyan") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_CYAN;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_CYAN;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_cyan);
    }
    else if(c_strcmp(ps_str,"Yellow") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_YELLOW;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_YELLOW;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_yellow);
    }
    else if(c_strcmp(ps_str,"Magenta") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_MAGENTA;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_MAGENTA;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_magenta);
    }
    else
    {
        ui1_color = APP_CFG_DCS_CLR_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_color_broadcast);
    }
    return ui1_color;
}
/*----------------------------------------------------------------------------
 * Name: _get_font_color_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_font_color_idx(UINT8     ui1_font_color)
{
    UINT16      ui2_idx = 0;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    switch (ui1_font_color)
    {
        case APP_CFG_DCS_CLR_BROADCAST:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_CLR_BLACK:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_black);
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_CLR_WHITE:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_white);
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_CLR_GREEN:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_green);
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_CLR_BLUE:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_blue);
            ui2_idx = 4;
            break;
        case APP_CFG_DCS_CLR_RED:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_red);
            ui2_idx = 5;
            break;
        case APP_CFG_DCS_CLR_CYAN:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_cyan);
            ui2_idx = 6;
            break;
        case APP_CFG_DCS_CLR_YELLOW:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_yellow);
            ui2_idx = 7;
            break;
        case APP_CFG_DCS_CLR_MAGENTA:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_magenta);
            ui2_idx = 8;
            break;
        default:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_color_broadcast);
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;
}

int digital_style_text_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8     i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    UINT8   ui1_color = APP_CFG_DCS_CLR_BROADCAST;
    WDK_TOAST_T t_toast;
    CHAR    text_color[9][32];
    INT16   i2_mlm_id[9] = {MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLACK,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_CYAN,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_YELLOW,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_MAGENTA};

    Json::Value color;
    /* color[0]= "As Broadcast";
    color[1]= "Black";
    color[2]= "White";
    color[3]= "Green";
    color[4]= "Blue";
    color[5]= "Red";
    color[6]= "Cyan";
    color[7]= "Yellow";
    color[8]= "Magenta"; */
    for (i = 0; i < 9; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), text_color[i], 32);
        color[i] = text_color[i];
    }
    response["ELEMENTS"]=color;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_dcs(APP_CFG_RECID_DCS_FONT_COLOR, &ui1_color);
            ui2_idx = _get_font_color_idx(ui1_color);
            REST_LOG_I("text_colot:%d,%d\n\r", ui2_idx,ui1_color);
            response["VALUE"]=color[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_COLOR;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            ui1_color = _text_color_set_color(str,&t_toast,&t_cap);
            REST_LOG_I("text_colot:%s,%d\n\r", str,ui1_color);

            a_cfg_set_dcs(APP_CFG_RECID_DCS_FONT_COLOR, ui1_color);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            a_cfg_update_dcs();

            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }
    return 0;
}

static UINT8 _text_opacity_set_opac(CHAR*  ps_str,
                    WDK_TOAST_T* pt_toast,
                    CC_CAP_STL_DATA_T* pt_cap)
{
    UINT8   ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;

    REST_LOG_I("str:%s\n\r", ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_fg = FALSE;
    }
    else if(c_strcmp(ps_str,"Solid") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_SOLID;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_SOLID;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_fg = FALSE;
    }
    else if(c_strcmp(ps_str,"Flashing") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_FLASH;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_FLASHING;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_fg = TRUE;
    }
    else if(c_strcmp(ps_str,"Translucent") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_TRANSLUCENT;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSLUCENT;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_opac_transl);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_fg = FALSE;
    }
    else if(c_strcmp(ps_str,"Transparent") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_TRANSPARENT;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSPARENT;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_opac_transp);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_fg = FALSE;
    }
    else
    {
        ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_fg = FALSE;
    }
    return ui1_font_opac;
}

/*----------------------------------------------------------------------------
 * Name: _get_font_opac_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_font_opac_idx(UINT8       ui1_font_opac)
{
    UINT16      ui2_idx = 0;
    BOOL        b_is_font_flash = FALSE;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    switch (ui1_font_opac)
    {
        case APP_CFG_DCS_OP_BROADCAST:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_OP_SOLID:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_OP_TRANSLUCENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_transl);
            b_is_font_flash = FALSE;
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_OP_TRANSPARENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_transp);
            b_is_font_flash = FALSE;
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_OP_FLASH:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = TRUE;
            ui2_idx = 4;
			break;
        default:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_text, t_g_opac_solid);
            b_is_font_flash = FALSE;
            ui2_idx = 0;
            break;
    }

    pt_this->t_cc_info.t_pen_color.b_is_flash_fg = b_is_font_flash;

    return  ui2_idx;
}

int digital_style_text_opacity(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8     i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    UINT8   ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
    WDK_TOAST_T t_toast;
    CHAR    text_opacity[5][32];
    INT16   i2_mlm_id[5] = {MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_SOLID,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSLUCENT,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSPARENT,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_FLASHING};

    Json::Value opac;
    /* opac[0]= "As Broadcast";
    opac[1]= "Solid";
    opac[2]= "Translucent";
    opac[3]= "Transparent";
    opac[4]= "Flashing"; */
    for (i = 0; i < 5; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), text_opacity[i], 32);
        opac[i] = text_opacity[i];
    }
    response["ELEMENTS"]=opac;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_dcs(APP_CFG_RECID_DCS_FONT_OPACITY, &ui1_font_opac);
            ui2_idx = _get_font_opac_idx(ui1_font_opac);
            REST_LOG_I("text_opacity:%d,%d\n\r", ui2_idx,ui1_font_opac);
            response["VALUE"]=opac[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_OPACITY;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            ui1_font_opac = _text_opacity_set_opac(str,&t_toast,&t_cap);
            REST_LOG_I("text_opacity:%s,%d\n\r", str,ui1_font_opac);

            a_cfg_set_dcs(APP_CFG_RECID_DCS_FONT_OPACITY, ui1_font_opac);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            a_cfg_update_dcs();

            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }
    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _get_text_edges_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_text_edges_idx(UINT8       ui1_edge_type)
{
    UINT16      ui2_idx = 0;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    switch (ui1_edge_type)
    {
        case APP_CFG_DCS_TYPE_BROADCAST:
			pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_TYPE_NONE:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            ui2_idx = 1;
            break;
	    case APP_CFG_DCS_TYPE_RAISED:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_RAISED;
            ui2_idx = 2;
			break;
        case APP_CFG_DCS_TYPE_DEPRESSED:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_DEPRESSED;
            ui2_idx = 3;
            break;
	  case APP_CFG_DCS_TYPE_UNIFORM:
	        pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_UNIFORM;
	        ui2_idx = 4;
	        break;
        case APP_CFG_DCS_TYPE_RIGHT_DROP_SHADOW:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_RIGHT_DROP_SHADOW;
            ui2_idx = 5;
            break;
        default:
            pt_this->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;

}
static UINT8 _text_edges_set_text_edges(CHAR*  ps_str,
                    WDK_TOAST_T* pt_toast,
                    CC_CAP_STL_DATA_T* pt_cap)
{
    UINT8   ui1_text_edges = APP_CFG_DCS_TYPE_BROADCAST;

    REST_LOG_I("str:%s\n\r", ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_text_edges = APP_CFG_DCS_TYPE_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_EDGES_AS_BRDCST;
        pt_cap->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
    }
    else if(c_strcmp(ps_str,"None") == 0)
    {
        ui1_text_edges = APP_CFG_DCS_TYPE_NONE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_EDGES_NONE;
        pt_cap->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
    }
    else if(c_strcmp(ps_str,"Raised") == 0)
    {
        ui1_text_edges = APP_CFG_DCS_TYPE_RAISED;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_EDGES_RAISED;
        pt_cap->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_RAISED;
    }
    else if(c_strcmp(ps_str,"Depressed") == 0)
    {
        ui1_text_edges = APP_CFG_DCS_TYPE_DEPRESSED;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_EDGES_DEPRESSED;
        pt_cap->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_DEPRESSED;
    }
    else if(c_strcmp(ps_str,"Uniform") == 0)
    {
        ui1_text_edges = APP_CFG_DCS_TYPE_UNIFORM;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_EDGES_UNIFORM;
        pt_cap->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_UNIFORM;
    }
    else if(c_strcmp(ps_str,"Drop Shadow") == 0)
    {
        ui1_text_edges = APP_CFG_DCS_TYPE_RIGHT_DROP_SHADOW;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_EDGES_DROP_SHADOW;
        pt_cap->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_RIGHT_DROP_SHADOW;
    }
    else
    {
        ui1_text_edges = APP_CFG_DCS_TYPE_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_EDGES_AS_BRDCST;
        pt_cap->t_cc_info.t_pen_font.t_font.ui1_edge_type = WGL_CC_EDGE_TYPE_NONE;
    }
    return ui1_text_edges;
}


int digital_style_text_edges(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8   i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    UINT8   ui1_edge_type = APP_CFG_DCS_TYPE_BROADCAST;;
    WDK_TOAST_T t_toast;
    CHAR    text_edges[6][32];
    INT16   i2_mlm_id[6] = {MLM_SETTINGS_KEY_CC_TEXT_EDGES_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_EDGES_NONE,
            MLM_SETTINGS_KEY_CC_TEXT_EDGES_RAISED,
            MLM_SETTINGS_KEY_CC_TEXT_EDGES_DEPRESSED,
            MLM_SETTINGS_KEY_CC_TEXT_EDGES_UNIFORM,
            MLM_SETTINGS_KEY_CC_TEXT_EDGES_DROP_SHADOW};

    Json::Value edges;
    /* edges[0]= "As Broadcast";
    edges[1]= "None";
    edges[2]= "Raised";
    edges[3]= "Depressed";
    edges[4]= "Uniform";
    edges[5]= "Drop Shadow"; */
    for (i = 0; i < 6; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), text_edges[i], 32);
        edges[i] = text_edges[i];
    }
    response["ELEMENTS"]=edges;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_dcs(APP_CFG_RECID_DCS_EDGE_TYPE, &ui1_edge_type);
            ui2_idx = _get_text_edges_idx(ui1_edge_type);
            REST_LOG_I("text_edges:%d,%d\n\r", ui2_idx,ui1_edge_type);
            response["VALUE"]=edges[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 =  MLM_SETTINGS_KEY_CC_TEXT_EDGES;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            ui1_edge_type = _text_edges_set_text_edges(str,&t_toast,&t_cap);
            REST_LOG_I("text_edges:%s,%d\n\r", str,ui1_edge_type);

            a_cfg_set_dcs(APP_CFG_RECID_DCS_EDGE_TYPE, ui1_edge_type);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            a_cfg_update_dcs();

            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }
    return 0;
}

static UINT8 _text_edges_color_set_color(CHAR*  ps_str,
                    WDK_TOAST_T* pt_toast,
                    CC_CAP_STL_DATA_T* pt_cap)
{
    UINT8       ui1_color = APP_CFG_DCS_CLR_BROADCAST;

    REST_LOG_I("str:%s\n\r", ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_broadcast);
    }
    else if(c_strcmp(ps_str,"Black") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BLACK;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLACK;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_black);
    }
    else if(c_strcmp(ps_str,"White") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_WHITE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_white);
    }
    else if(c_strcmp(ps_str,"Green") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_GREEN;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_green);
    }
    else if(c_strcmp(ps_str,"Blue") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BLUE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_blue);
    }
    else if(c_strcmp(ps_str,"Red") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_RED;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_red);
    }
    else if(c_strcmp(ps_str,"Cyan") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_CYAN;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_CYAN;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_cyan);
    }
    else if(c_strcmp(ps_str,"Yellow") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_YELLOW;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_YELLOW;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_yellow);
    }
    else if(c_strcmp(ps_str,"Magenta") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_MAGENTA;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_MAGENTA;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_magenta);
    }
    else
    {
        ui1_color = APP_CFG_DCS_CLR_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_edge, t_g_color_broadcast);
    }
    return ui1_color;
}

/*----------------------------------------------------------------------------
 * Name: _get_text_edges_color_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_text_edges_color_idx(UINT8       ui1_edge_color)
{
    UINT16      ui2_idx = 0;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    switch (ui1_edge_color)
    {
        case APP_CFG_DCS_CLR_BROADCAST:
			pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_white;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_CLR_BLACK:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_black;
            ui2_idx = 1;
            break;
	    case APP_CFG_DCS_CLR_WHITE:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_white;
            ui2_idx = 2;
			break;
        case APP_CFG_DCS_CLR_GREEN:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_green;
            ui2_idx = 3;
            break;
	  	case APP_CFG_DCS_CLR_BLUE:
	        pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_blue;
	        ui2_idx = 4;
	        break;
        case APP_CFG_DCS_CLR_RED:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_red;
            ui2_idx = 5;
            break;
		case APP_CFG_DCS_CLR_CYAN:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_cyan;
            ui2_idx = 6;
            break;
		case APP_CFG_DCS_CLR_YELLOW:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_yellow;
            ui2_idx = 7;
            break;
		case APP_CFG_DCS_CLR_MAGENTA:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_magenta;
            ui2_idx = 8;
            break;
        default:
            pt_this->t_cc_info.t_pen_color.t_color_edge = t_g_color_broadcast;
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;

}
int digital_style_text_edges_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8   i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    UINT8   ui1_edge_color = APP_CFG_DCS_TYPE_BROADCAST;
    WDK_TOAST_T t_toast;
    CHAR    text_edges_color[9][32];
    INT16   i2_mlm_id[9] = {MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLACK,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_CYAN,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_YELLOW,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_MAGENTA};

    Json::Value color;
    /* color[0]= "As Broadcast";
    color[1]= "Black";
    color[2]= "White";
    color[3]= "Green";
    color[4]= "Blue";
    color[5]= "Red";
    color[6]= "Cyan";
    color[7]= "Yellow";
    color[8]= "Magenta"; */
    for (i = 0; i < 9; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), text_edges_color[i], 32);
        color[i] = text_edges_color[i];
    }
    response["ELEMENTS"]=color;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_dcs(APP_CFG_RECID_DCS_EDGE_COLOR, &ui1_edge_color);
            ui2_idx = _get_text_edges_color_idx(ui1_edge_color);
            REST_LOG_I("text_edges_color:%d,%d\n\r", ui2_idx,ui1_edge_color);
            response["VALUE"]=color[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_EDGES_COLOR;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            ui1_edge_color = _text_edges_color_set_color(str,&t_toast,&t_cap);
            REST_LOG_I("text_edges_color:%s,%d\n\r", str,ui1_edge_color);

            a_cfg_set_dcs(APP_CFG_RECID_DCS_EDGE_COLOR, ui1_edge_color);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            if(ui1_edge_color != APP_CFG_DCS_CLR_BROADCAST)
        	{
        		a_cfg_set_dcs(APP_CFG_RECID_DCS_EDGE_OPACITY, APP_CFG_DCS_OP_SOLID);
        	}

            a_cfg_update_dcs();

            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }
    return 0;
}

static UINT8 _background_color_set_color(CHAR*  ps_str,
                    WDK_TOAST_T* pt_toast,
                    CC_CAP_STL_DATA_T* pt_cap)
{
    UINT8       ui1_color = APP_CFG_DCS_CLR_BROADCAST;

    REST_LOG_I("str:%s\n\r", ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_broadcast);
    }
    else if(c_strcmp(ps_str,"Black") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BLACK;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLACK;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_black);
    }
    else if(c_strcmp(ps_str,"White") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_WHITE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_white);
    }
    else if(c_strcmp(ps_str,"Green") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_GREEN;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_green);
    }
    else if(c_strcmp(ps_str,"Blue") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BLUE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_blue);
    }
    else if(c_strcmp(ps_str,"Red") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_RED;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_red);
    }
    else if(c_strcmp(ps_str,"Cyan") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_CYAN;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_CYAN;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_cyan);
    }
    else if(c_strcmp(ps_str,"Yellow") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_YELLOW;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_YELLOW;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_yellow);
    }
    else if(c_strcmp(ps_str,"Magenta") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_MAGENTA;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_MAGENTA;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_magenta);
    }
    else
    {
        ui1_color = APP_CFG_DCS_CLR_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST;
        CS_CPY_RGB(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_color_broadcast);
    }
    return ui1_color;
}

static UINT8 _win_color_set_color(CHAR*  ps_str,
                                  WDK_TOAST_T* pt_toast,
                                  CC_CAP_STL_DATA_T* pt_cap)
{
    UINT8       ui1_color = APP_CFG_DCS_CLR_BROADCAST;

    REST_LOG_I("str:%s\n\r", ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_broadcast);
    }
    else if(c_strcmp(ps_str,"Black") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BLACK;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLACK;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_black);
    }
    else if(c_strcmp(ps_str,"White") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_WHITE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_white);
    }
    else if(c_strcmp(ps_str,"Green") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_GREEN;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_green);
    }
    else if(c_strcmp(ps_str,"Blue") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_BLUE;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_blue);
    }
    else if(c_strcmp(ps_str,"Red") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_RED;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_red);
    }
    else if(c_strcmp(ps_str,"Cyan") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_CYAN;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_CYAN;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_cyan);
    }
    else if(c_strcmp(ps_str,"Yellow") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_YELLOW;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_YELLOW;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_yellow);
    }
    else if(c_strcmp(ps_str,"Magenta") == 0)
    {
        ui1_color = APP_CFG_DCS_CLR_MAGENTA;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_MAGENTA;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_magenta);
    }
    else
    {
        ui1_color = APP_CFG_DCS_CLR_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST;
        CS_CPY_RGB(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_color_broadcast);
    }
    return ui1_color;
}


/*----------------------------------------------------------------------------
 * Name: _get_bg_color_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_bg_color_idx( UINT8       ui1_bg_color)
{
    UINT16      ui2_idx = 0;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    switch (ui1_bg_color)
    {
        case APP_CFG_DCS_CLR_BROADCAST:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_broadcast);
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_CLR_BLACK:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_black);
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_CLR_WHITE:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_white);
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_CLR_GREEN:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_green);
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_CLR_BLUE:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_blue);
            ui2_idx = 4;
            break;
        case APP_CFG_DCS_CLR_RED:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_red);
            ui2_idx = 5;
            break;
        case APP_CFG_DCS_CLR_CYAN:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_cyan);
            ui2_idx = 6;
            break;
        case APP_CFG_DCS_CLR_YELLOW:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_yellow);
            ui2_idx = 7;
            break;
        case APP_CFG_DCS_CLR_MAGENTA:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_magenta);
            ui2_idx = 8;
            break;
        default:
            CS_CPY_RGB(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_color_broadcast);
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;
}

int digital_style_background_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8   i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    UINT8   ui1_bg_color = APP_CFG_DCS_CLR_BROADCAST;
    WDK_TOAST_T t_toast;
    CHAR    background_color[9][32];
    INT16   i2_mlm_id[9] = {MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLACK,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_CYAN,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_YELLOW,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_MAGENTA};

    Json::Value color;
    /* color[0]= "As Broadcast";
    color[1]= "Black";
    color[2]= "White";
    color[3]= "Green";
    color[4]= "Blue";
    color[5]= "Red";
    color[6]= "Cyan";
    color[7]= "Yellow";
    color[8]= "Magenta"; */
    for (i = 0; i < 9; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), background_color[i], 32);
        color[i] = background_color[i];
    }
    response["ELEMENTS"]=color;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {

            a_cfg_get_dcs(APP_CFG_RECID_DCS_BK_COLOR, &ui1_bg_color);
            ui2_idx = _get_bg_color_idx(ui1_bg_color);
            REST_LOG_I("background_color:%d,%d\n\r", ui2_idx,ui1_bg_color);
            response["VALUE"]=color[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_BACKGROUND_COLOR;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            ui1_bg_color = _background_color_set_color(str,&t_toast,&t_cap);
            REST_LOG_I("background_color:%s,%d\n\r", str,ui1_bg_color);

            a_cfg_set_dcs(APP_CFG_RECID_DCS_BK_COLOR, ui1_bg_color);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            a_cfg_update_dcs();

            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }

    return 0;
}

static UINT8 _background_opacity_set_opac(CHAR*  ps_str,
                    WDK_TOAST_T* pt_toast,
                    CC_CAP_STL_DATA_T* pt_cap)
{
    UINT8   ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;

    REST_LOG_I("str:%s\n\r", ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_bk= FALSE;
    }
    else if(c_strcmp(ps_str,"Solid") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_SOLID;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_SOLID;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_bk = FALSE;
    }
    else if(c_strcmp(ps_str,"Flashing") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_FLASH;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_FLASHING;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_bk = TRUE;
    }
    else if(c_strcmp(ps_str,"Translucent") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_TRANSLUCENT;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSLUCENT;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_opac_transl);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_bk = FALSE;
    }
    else if(c_strcmp(ps_str,"Transparent") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_TRANSPARENT;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSPARENT;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_opac_transp);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_bk = FALSE;
    }
    else
    {
        ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
        pt_cap->t_cc_info.t_pen_color.b_is_flash_bk = FALSE;
    }
    return ui1_font_opac;
}

static UINT8 _win_opacity_set_opac(CHAR*  ps_str,
                    WDK_TOAST_T* pt_toast,
                    CC_CAP_STL_DATA_T* pt_cap)
{
    UINT8   ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;

    REST_LOG_I("str:%s\n\r", ps_str);
    if(c_strcmp(ps_str,"As Broadcast") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
        pt_cap->t_cc_info.t_win_attr.b_is_flash_bk= FALSE;
    }
    else if(c_strcmp(ps_str,"Solid") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_SOLID;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_SOLID;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
        pt_cap->t_cc_info.t_win_attr.b_is_flash_bk = FALSE;
    }
    else if(c_strcmp(ps_str,"Flashing") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_FLASH;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_FLASHING;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
        pt_cap->t_cc_info.t_win_attr.b_is_flash_bk = TRUE;
    }
    else if(c_strcmp(ps_str,"Translucent") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_TRANSLUCENT;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSLUCENT;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_opac_transl);
        pt_cap->t_cc_info.t_win_attr.b_is_flash_bk = FALSE;
    }
    else if(c_strcmp(ps_str,"Transparent") == 0)
    {
        ui1_font_opac = APP_CFG_DCS_OP_TRANSPARENT;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSPARENT;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_opac_transp);
        pt_cap->t_cc_info.t_win_attr.b_is_flash_bk = FALSE;
    }
    else
    {
        ui1_font_opac = APP_CFG_DCS_OP_BROADCAST;
        pt_toast->style.style_2.ui4_id_2 =  MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST;
        CS_CPY_ALPHA(pt_cap->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
        pt_cap->t_cc_info.t_win_attr.b_is_flash_bk = FALSE;
    }
    return ui1_font_opac;
}


/*----------------------------------------------------------------------------
 * Name: _get_bg_opac_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_bg_opac_idx(UINT8       ui1_bk_opac)
{
    UINT16      ui2_idx = 0;
    BOOL        b_is_bk_flash = FALSE;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    switch (ui1_bk_opac)
    {
        case APP_CFG_DCS_OP_BROADCAST:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_OP_SOLID:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_OP_TRANSLUCENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_transl);
            b_is_bk_flash = FALSE;
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_OP_TRANSPARENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_transp);
            b_is_bk_flash = FALSE;
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_OP_FLASH:
			CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
			b_is_bk_flash = TRUE;
			ui2_idx = 4;
			break;
        default:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_pen_color.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 0;
            break;
    }

    pt_this->t_cc_info.t_pen_color.b_is_flash_bk = b_is_bk_flash;

    return  ui2_idx;
}
int digital_style_background_opacity(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8   i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    UINT8   ui1_bk_opac = APP_CFG_DCS_OP_BROADCAST;
    WDK_TOAST_T t_toast;
    CHAR    background_opacity[5][32];
    UINT16  i2_mlm_id[5] = {MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_SOLID,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSLUCENT,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSPARENT,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_FLASHING};

    Json::Value opac;
    /* opac[0]= "As Broadcast";
    opac[1]= "Solid";
    opac[2]= "Translucent";
    opac[3]= "Transparent";
    opac[4]= "Flashing"; */
    for (i = 0; i < 5; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), background_opacity[i], 32);
        opac[i] = background_opacity[i];
    }
    response["ELEMENTS"]=opac;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_dcs(APP_CFG_RECID_DCS_BK_OPACITY, &ui1_bk_opac);
            ui2_idx = _get_bg_opac_idx(ui1_bk_opac);
            REST_LOG_I("background_opacity:%d,%d\n\r", ui2_idx,ui1_bk_opac);
            response["VALUE"]=opac[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_BACKGROUND_OPACITY;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            ui1_bk_opac = _background_opacity_set_opac(str,&t_toast,&t_cap);
            REST_LOG_I("background_opacity:%s,%d\n\r", str,ui1_bk_opac);

            a_cfg_set_dcs(APP_CFG_RECID_DCS_BK_OPACITY, ui1_bk_opac);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            a_cfg_update_dcs();

            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }
    return 0;
}
/*----------------------------------------------------------------------------
 * Name: _get_win_color_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_win_color_idx(UINT8       ui1_win_color)
{
    UINT16      ui2_idx = 0;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    switch (ui1_win_color)
    {
        case APP_CFG_DCS_CLR_BROADCAST:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_broadcast);
            ui2_idx = 0;
            break;
        case APP_CFG_DCS_CLR_BLACK:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_black);
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_CLR_WHITE:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_white);
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_CLR_GREEN:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_green);
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_CLR_BLUE:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_blue);
            ui2_idx = 4;
            break;
        case APP_CFG_DCS_CLR_RED:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_red);
            ui2_idx = 5;
            break;
        case APP_CFG_DCS_CLR_CYAN:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_cyan);
            ui2_idx = 6;
            break;
        case APP_CFG_DCS_CLR_YELLOW:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_yellow);
            ui2_idx = 7;
            break;
        case APP_CFG_DCS_CLR_MAGENTA:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_magenta);
            ui2_idx = 8;
            break;
        default:
            CS_CPY_RGB(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_color_broadcast);
            ui2_idx = 0;
            break;
    }

    return  ui2_idx;
}

int digital_style_window_color(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8   i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    UINT8   ui1_win_color = APP_CFG_DCS_CLR_BROADCAST;
    WDK_TOAST_T t_toast;
    CHAR    window_color[9][32];
    INT16   i2_mlm_id[9] = {MLM_SETTINGS_KEY_CC_TEXT_COLOR_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLACK,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_WHITE,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_GREEN,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_BLUE,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_RED,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_CYAN,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_YELLOW,
            MLM_SETTINGS_KEY_CC_TEXT_COLOR_MAGENTA};

    Json::Value color;
    /* color[0]= "As Broadcast";
    color[1]= "Black";
    color[2]= "White";
    color[3]= "Green";
    color[4]= "Blue";
    color[5]= "Red";
    color[6]= "Cyan";
    color[7]= "Yellow";
    color[8]= "Magenta"; */
    for (i = 0; i < 9; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), window_color[i], 32);
        color[i] = window_color[i];
    }
    response["ELEMENTS"]=color;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_dcs(APP_CFG_RECID_DCS_WIN_COLOR, &ui1_win_color);
            ui2_idx = _get_win_color_idx(ui1_win_color);
            REST_LOG_I("window_color:%d,%d\n\r", ui2_idx,ui1_win_color);
            response["VALUE"]=color[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_WINDOW_COLOR;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            ui1_win_color = _win_color_set_color(str,&t_toast,&t_cap);//_background_color_set_color(str,&t_toast,&t_cap);
            REST_LOG_I("window_color:%s,%d\n\r", str,ui1_win_color);

            a_cfg_set_dcs(APP_CFG_RECID_DCS_WIN_COLOR, ui1_win_color);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            a_cfg_update_dcs();

            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }
    return 0;
}

/*----------------------------------------------------------------------------
 * Name: _get_win_opac_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static UINT16 _get_win_opac_idx(UINT8       ui1_win_opac)
{
    UINT16      ui2_idx = 0;
    BOOL        b_is_bk_flash = FALSE;
    CC_CAP_STL_DATA_T *pt_this = &t_cap;

    switch (ui1_win_opac)
    {
        case APP_CFG_DCS_OP_BROADCAST:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx= 0;
            break;
        case APP_CFG_DCS_OP_SOLID:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 1;
            break;
        case APP_CFG_DCS_OP_TRANSLUCENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_transl);
            b_is_bk_flash = FALSE;
            ui2_idx = 2;
            break;
        case APP_CFG_DCS_OP_TRANSPARENT:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_transp);
            b_is_bk_flash = FALSE;
            ui2_idx = 3;
            break;
        case APP_CFG_DCS_OP_FLASH:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = TRUE;
            ui2_idx = 4;
            break;
        default:
            CS_CPY_ALPHA(pt_this->t_cc_info.t_win_attr.t_color_bk, t_g_opac_solid);
            b_is_bk_flash = FALSE;
            ui2_idx = 0;
            break;
    }

    pt_this->t_cc_info.t_win_attr.b_is_flash_bk = b_is_bk_flash;

    return  ui2_idx;
}

int digital_style_window_opacity(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UINT8   i = 0;
    INT32   type = 0;
    CHAR    str[128] = {0};
    UINT16  ui2_idx = 0;
    UINT8   ui1_win_opac = APP_CFG_DCS_OP_BROADCAST;
    WDK_TOAST_T t_toast;
    CHAR    window_opacity[5][32];
    UINT16  i2_mlm_id[5] = {MLM_SETTINGS_KEY_CC_TEXT_OPACITY_AS_BRDCST,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_SOLID,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSLUCENT,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_TRANSPARENT,
            MLM_SETTINGS_KEY_CC_TEXT_OPACITY_FLASHING};

    Json::Value opac;
    /* opac[0]= "As Broadcast";
    opac[1]= "Solid";
    opac[2]= "Translucent";
    opac[3]= "Transparent";
    opac[4]= "Flashing"; */
    for (i = 0; i < 5; i++)
    {
        c_uc_w2s_to_ps(MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), i2_mlm_id[i]), window_opacity[i], 32);
        opac[i] = window_opacity[i];
    }
    response["ELEMENTS"]=opac;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            a_cfg_get_dcs(APP_CFG_RECID_DCS_WIN_OPACITY, &ui1_win_opac);
            ui2_idx = _get_win_opac_idx(ui1_win_opac);
            REST_LOG_I("window_opacity:%d,%d\n\r", ui2_idx,ui1_win_opac);
            response["VALUE"]=opac[ui2_idx];
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));
            t_toast.e_toast_style  = WDK_STRING_TOAST;
            t_toast.e_string_style = WDK_STRING_ID_ID;
            t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_CC_TEXT_WINDOW_OPACITY;

            Json::Value item1;
            Json::Value item2;

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strcpy(str,item1.asString().c_str());
            ui1_win_opac = _win_opacity_set_opac(str,&t_toast,&t_cap);//_background_opacity_set_opac(str,&t_toast,&t_cap);
            REST_LOG_I("window_opacity:%s,%d\n\r", str,ui1_win_opac);

            a_cfg_set_dcs(APP_CFG_RECID_DCS_WIN_OPACITY, ui1_win_opac);

            a_cfg_set_dcs(APP_CFG_RECID_DCS, APP_CFG_DCS_CUSTOM);

            a_cfg_update_dcs();

            rest_send_msg_to_nav(&t_toast);
            rest_send_cc_msg_to_nav(&t_cap);
            break;
        }
        default:
            break;
    }

    return 0;
}

int caption_style(Json::Value & root, Json::Value & response){return 0;}

handler closed_captions_handler[] = {
    closed_captions_enabled ,
    analog_closed_captions   ,
    digital_closed_captions  ,
    digital_style    ,
    digital_style_text_style   ,
    digital_style_text_size    ,
    digital_style_text_color   ,
    digital_style_text_opacity     ,
    digital_style_text_edges   ,
    digital_style_text_edges_color     ,
    digital_style_background_color     ,
    digital_style_background_opacity   ,
    digital_style_window_color     ,
    digital_style_window_opacity   ,
};


/*----------------------------------------------------------------------------
 * Name: a_close_caption_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID a_close_caption_init(VOID)
{
    DBG_LOG_PRINT(("enter a_close_caption_init\n"));
    /* init CC preview */
    HANDLE_T h_canvas = a_revolt_info_get_canvas();
    closed_captions_view_init(h_canvas,&t_cap);
}

