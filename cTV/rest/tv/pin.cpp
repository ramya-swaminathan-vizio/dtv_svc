#include <iostream>
#include <bits/unique_ptr.h>

#include "handler.h"
#include "common.h"
#include "argument.h"
#include "pin.h"

#ifdef __cplusplus
extern "C" {

#include "app_util/a_cfg.h"
#include "wizard_anim/a_wzd.h"

}

#endif

struct PINGroupURI {
    std::string index[URI_INDEX_SIZE];
};

PINGroupURI  pinGroupURIs[] = {

    /*
    # ULI
    */

    { "confirm_pin" },
    { "set_pin" },
    { "is_pin_default" },
    {"is_pin_confirmed"},
    { "" },
};

static bool gb_pin_is_confirmed = 0;

static bool _is_pin_default()
{
    REST_LOG_I("Enter\n\r");

    UTF16_T    u2s_pwd[5] = {0};
    UTF16_T    u2s_pwd_exist[10] = {0};
    CHAR       psw[20] = {0};

    BOOL       b_pass = FALSE;

    u2s_pwd[0]='0';
    u2s_pwd[1]='0';
    u2s_pwd[2]='0';
    u2s_pwd[3]='0';

    a_cfg_get_password(u2s_pwd_exist, 10);

    c_uc_w2s_to_ps(u2s_pwd_exist,
                   psw,
                   20);

    REST_LOG_I("Existed password: %s\n\r", psw);

    a_cfg_chk_password(u2s_pwd,&b_pass);
    REST_LOG_I("_is_pin_default: %d\n\r", b_pass);

    return b_pass;
}

static bool _is_pin_confirmed()
{
    REST_LOG_I("Enter\n\r");
    bool b_confirm = true;

    if (_is_pin_default())
    {
        b_confirm = true;
    }
    else
    {
        b_confirm = gb_pin_is_confirmed;
    }

    REST_LOG_I("_is_pin_confirmed: %d\n\r", b_confirm);

    return b_confirm;
}

static int _set_is_pin_confirmed(bool b_confirm)
{
    REST_LOG_I("Enter, %d\n\r", b_confirm);

    gb_pin_is_confirmed = b_confirm;

    return 0;
}

int a_set_is_pin_confirmed(bool b_confirm)
{
    REST_LOG_I("Enter, %d\n\r", b_confirm);
    return _set_is_pin_confirmed(b_confirm);
}

int a_get_is_pin_confirmed(bool* b_confirm)
{
    REST_LOG_I("Enter\n\r");

    if (NULL == b_confirm)
    {
        REST_LOG_E("ERROR\n\r");
        return -1;
    }
    else
    {
        *b_confirm = gb_pin_is_confirmed;
        return 0;
    }
}

int confirm_pin(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    UTF16_T    u2s_pwd[5] = {0};
    BOOL       b_pass = FALSE;
    CHAR       pin[10] = {0};

    string_get_string(root, pin, 10);

    REST_LOG_I("confirm pin: %s\n\r", pin);

    c_uc_ps_to_w2s(pin, u2s_pwd,
            (c_strlen(pin) > APP_CFG_MAX_PWD_LEN) ? APP_CFG_MAX_PWD_LEN : c_strlen(pin));

    a_cfg_chk_password(u2s_pwd,&b_pass);
    REST_LOG_I("b_pass: %d\n\r", b_pass);

    if(b_pass)
    {
        response["VALUE"]=1;
        _set_is_pin_confirmed(true);

        return 0;
    }
    else
    {
        response["VALUE"]=6;
        _set_is_pin_confirmed(false);

        return 6;
    }
}

int set_pin(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    UTF16_T    u2s_pwd[10] = {0};
    CHAR       str[10] = {0};

    WDK_TOAST_T t_toast;

    string_get_string(root, str, 10);

    REST_LOG_I("set pin: %s\n\r", str);
    c_uc_ps_to_w2s(str, u2s_pwd,
            (c_strlen(str) > APP_CFG_MAX_PWD_LEN) ? APP_CFG_MAX_PWD_LEN : c_strlen(str));
    a_cfg_set_password(u2s_pwd);

    c_memset((VOID*)&t_toast, 0, sizeof(WDK_TOAST_T));

    t_toast.e_toast_style  = WDK_STRING_TOAST;
    t_toast.e_string_style = WDK_STRING_ID_ID;
    t_toast.style.style_2.ui4_id_1 = MLM_SETTINGS_KEY_SYS_PIN_CODE;
    t_toast.style.style_2.ui4_id_2 = MLM_SETTINGS_KEY_SYS_PIN_CODE_SET;

    rest_send_msg_to_nav(&t_toast);

    _set_is_pin_confirmed(true);

    return 0;
}

int is_pin_default(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    if(_is_pin_default())
    {
        response["VALUE"]=1;
    }
    else
    {
        response["VALUE"]=0;
    }

    return 0;
}

int is_pin_confirmed(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    if(_is_pin_confirmed())
    {
        response["VALUE"]=1;
    }
    else
    {
        response["VALUE"]=0;
    }

    return 0;
}

handler pin_handler[] = {
    confirm_pin,
    set_pin,
    is_pin_default,
    is_pin_confirmed,
};


