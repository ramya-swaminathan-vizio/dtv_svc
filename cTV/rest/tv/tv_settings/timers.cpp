#include <iostream>
#include<bits/unique_ptr.h>

#include "timers.h"
#include "handler.h"
#include "common.h"
#include <cJSON.h>
#include "argument.h"
#include <string.h>


#ifdef __cplusplus
extern "C" {

#include "u_btn_map.h"
#include "nav/scrn_blank/a_nav_scrn_blank.h"
#include "amb/a_amb.h"
#include "am/a_am.h"

#include "app_util/a_cfg.h"
#include "app_util/a_sleep_timer.h"

#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"
#include "wizard_anim/a_wzd.h"

#include "rest_ipc.h"
#include "rest.h"
#include "rest_ipc_handler.h"
#include "app_util/a_common.h"
#include "rest_cmd.h"
#include "rest_json.h"

#include "res/app_util/network/network_custom.h"
#include "res/menu2/menu_custom.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
}
#endif


TvSettingsGroupURI tvSettingsTimerUri[] = {
        /*
        # TIMER
        */

        { "sleep_timer" },
        { "auto_power_off_timer" },
	{"blank_screen"},
        { "" },
};



static VOID rest_set_sleep_timer_idx(UINT16 ui2_idx)
{
    UINT32  ui4_time = 0;

    a_sleep_timer_get_time_by_idx((UINT8)ui2_idx, &ui4_time);

	DBG_LOG_PRINT(("\n[TIMERS_TEST] rest_set_sleep_timer_idx\n"));
    if(ui4_time == 0)
    {
        a_sleep_timer_stop();
    }
    else
    {
        a_sleep_timer_start(ui4_time);
    }

}

static INT32 rest_get_sleep_timer_idx(VOID)
{
    UINT8   ui1_num_rec = 0;
    INT32   i4_idx = 0;
    UINT32  ui4_time = 0;
    UINT32  ui4_time_remaining = 0;

    a_sleep_timer_get_num_rec(&ui1_num_rec);
    a_sleep_timer_get_remaining_time(&ui4_time_remaining);

    for(i4_idx=0; i4_idx<ui1_num_rec; i4_idx++)
    {
        a_sleep_timer_get_time_by_idx(i4_idx,  &ui4_time);
        if(ui4_time_remaining <= ui4_time)
        {
            break;
        }
    }
    if(i4_idx == ui1_num_rec)
    {
        /* only happen when someone sets the timer by a_sleep_timer_start() directly,*/
        /* Use the last element */
        a_sleep_timer_stop();
        i4_idx = 0;
    }
    return i4_idx;
}




int sleep_timer(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");

	INT32 type = 0;
	INT32 val = 0;
	type = get_type(root);

	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			REST_LOG_I("REQUEST_GET\n\r");

			val = rest_get_sleep_timer_idx();

			UINT32  ui4_time = 0;
			UTF16_T  w2s_str[128]={0};
			char s_sleep_time[128]={0};
			a_sleep_timer_get_time_by_idx((UINT8)val, &ui4_time);
			a_sleep_timer_get_text(ui4_time, w2s_str, sizeof(w2s_str));

			c_uc_w2s_to_ps (w2s_str,s_sleep_time,sizeof(s_sleep_time));
			response["VALUE"] = std::string(s_sleep_time);
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			char s_sleep_time[128]={0};
            string_get_string(root, s_sleep_time, 128);


			if(c_strcmp(s_sleep_time,"30 minutes")==0)
			{
				val = 1;
			}
			else if(c_strcmp(s_sleep_time,"60 minutes")==0)
			{
				val = 2;
			}
			else if(c_strcmp(s_sleep_time,"90 minutes")==0)
			{
				val = 3;
			}
			else if(c_strcmp(s_sleep_time,"120 minutes")==0)
			{
				val = 4;
			}
			else if(c_strcmp(s_sleep_time,"180 minutes")==0)
			{
				val = 5;
			}
			else
			{
				val = 0;
			}
			REST_LOG_I("REQUEST_GET HS_HUICHEN %s %d\n\r",s_sleep_time ,val);
			rest_set_sleep_timer_idx((UINT16)val);

			WDK_TOAST_T t_toast;
			char 		s_temp[256]={0};
			UTF16_T		w2s_title[1028]={0};
			UTF16_T		w2s_title_temp[1028]={0};
		    c_memset(&t_toast,0,sizeof(WDK_TOAST_T));
		    t_toast.e_toast_style  = WDK_STRING_TOAST;
		    t_toast.e_string_style = WDK_STRING_STRING;


			c_memset(w2s_title, 0, sizeof(w2s_title));
    		c_uc_w2s_strncat(w2s_title, MENU_TEXT(MLM_MENU_KEY_SLEEP_TIMER), sizeof(w2s_title)/sizeof(w2s_title[0])-1);
			c_sprintf(s_temp," is %s.\n",s_sleep_time);
			c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
			c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);
			t_toast.style.style_4.w2s_str  = WGL_PACK(w2s_title);
			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();

			break;
		}
		default:
			break;
	}
	return 0;
}

int auto_power_off_timer(Json::Value & root, Json::Value & response)
{
	REST_LOG_I("Enter\n\r");

	INT32 type = 0;
	type = get_type(root);

	switch (type)
	{
		case argument::RequestType::REQUEST_GET:
		{
			REST_LOG_I("REQUEST_GET\n\r");
			char s_auto_timer[28]={0};
			ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
		    BOOL    b_dpms = FALSE;

		    a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
		    a_cfg_get_dpms(&b_dpms);

		    if (ACFG_RETAIL_MODE_NORMAL==t_retail_mode)
		    {
				c_strncpy(s_auto_timer, "Off", c_strlen("Off"));
		    }
		    else
		    {
			    if(b_dpms)
		    	{
		    		c_strncpy(s_auto_timer, "10 minutes", c_strlen("10 minutes"));
		    	}
				else
				{
					c_strncpy(s_auto_timer, "Off", c_strlen("Off"));
				}
		    }

			response["VALUE"] = std::string(s_auto_timer);
			break;
		}
		case argument::RequestType::REQUEST_SET:
		{
			char s_sleep_time[128]={0};
            string_get_string(root, s_sleep_time, 128);
			REST_LOG_I("REQUEST_GET HS_HUICHEN %s \n\r",s_sleep_time);

			ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
			a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
			if (ACFG_RETAIL_MODE_NORMAL==t_retail_mode)
			{
				/* no action requited in retail mode */
				break;
			}

			if(c_strcmp(s_sleep_time,"Off")==0)
			{
				a_cfg_set_dpms(FALSE);
			}
			else
			{
				a_cfg_set_dpms(TRUE);
			}


			WDK_TOAST_T t_toast;
			char 		s_temp[256]={0};
			UTF16_T		w2s_title[1028]={0};
			UTF16_T		w2s_title_temp[1028]={0};
		    c_memset(&t_toast,0,sizeof(WDK_TOAST_T));
		    t_toast.e_toast_style  = WDK_STRING_TOAST;
		    t_toast.e_string_style = WDK_STRING_STRING;


			c_memset(w2s_title, 0, sizeof(w2s_title));
    		c_uc_w2s_strncat(w2s_title, MENU_TEXT(MLM_MENU_KEY_AUTO_POWER_OFF), sizeof(w2s_title)/sizeof(w2s_title[0])-1);
			c_sprintf(s_temp," is %s.\n",s_sleep_time);
			c_uc_ps_to_w2s(s_temp,w2s_title_temp,sizeof(w2s_title_temp));
			c_uc_w2s_strncat(w2s_title, w2s_title_temp, sizeof(w2s_title)/sizeof(w2s_title[0])-1);
			t_toast.style.style_4.w2s_str  = WGL_PACK(w2s_title);
			rest_send_msg_to_nav(&t_toast);
			menu_pm_repaint();
			break;
		}
		default:
			break;
	}
	return 0;
}

int blank_screen(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            /*FORCE_BACK_LIGHT_T t_bl = {0};
            a_cfg_cust_get_blank_screen_state((VOID *)&t_bl);
            value_set_response(response,t_bl.u1Force);*/
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("REQUEST_ACTION\n\r");

          a_menu_hot_key_handler(BTN_BLANK_SCREEN,
                                 WGL_MSG_KEY_DOWN,
                                 NULL);
        }
        default:
            break;
    }

    return 0;
}

int timer_exit_blank_screen(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32 type = 0;
    static UINT32 ui4_default_keycode = 1;

    type = get_type(root);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("Request Type is GET, do not care\r\n");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        case argument::RequestType::REQUEST_ACTION:
        {
            REST_LOG_I("Request Type is SET/ACTION, exit blank screen\r\n");
            menu_custom_unblank_screen(ui4_default_keycode);
            break;
        }
        default:
            REST_LOG_I("not implement\r\n");
            break;
    }

    return 0;
}

handler timers_handler[] = {
    sleep_timer,
    auto_power_off_timer,
    blank_screen,
};


