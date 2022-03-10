#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <pthread.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <unistd.h>

#include "a_jsonrpc.h"
//#include <json/json.h>
#include <json/value.h>
#include <json/reader.h>
#include "json/writer.h"

#include "handler.h"
#include "app.h"
#include "method.h"
#include "rest.h"
#include "rest_ipc.h"
#include <tv_settings/network.h>
#include "airplay.h"

#include "log.h"
#include "mDNSServer.h"

#include "netflix_pre_app.h"
#include "rest/rest.h"
#include "rest/rest_event_api.h"
#include "rest/rest_api_variables.h"
#include "vzipc/vzIpcServer.h"

#ifdef VIZIO_FUSION_SUPPORT
extern int Get_pre_app_data(Json::Value & response);
#endif

#ifdef __cplusplus
extern "C" {
#include "u_common.h"
#include "x_os.h"
#include "u_btn_map.h"
#include "nav/nav_common.h"
#include "nav/nav_comp_id.h"
#include "nav/c4tv_apron/a_c4tv_apron.h"
#include "am/a_am.h"
#include "res/nav/banner2/banner_rc.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/menu2/menu_custom.h"
#include "nav/updater/a_nav_updater.h"
#endif

#define REST_JSON_RPC_THREAD_PRIORITY               ((UINT8) 200)
#define REST_JSON_RPC_THREAD_NUM_OF_MSGS            ((UINT16)20)
#define REST_JSON_RPC_THREAD_DEFAULT_STACK_SIZE     ((SIZE_T)4*1024)
#define REST_JSON_RPC_THREAD_NAME                   "rest_json_rpc"
#define VIZIO_IPC_THREAD_NAME                       "vizio_ipc_v2"

//static volatile int g_run = 1;
volatile int g_run = 1;

static REST_MSG_BUF msg;
static bool b_python_reeady = false;

extern "C" VOID a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS eState); //dolphin
extern int power_status;

/* pre-unmute val define*/
static HANDLE_T        h_json_rpc_thread = NULL_HANDLE;
static THREAD_DESCR_T  t_json_rpc_thread_descr = {DEFAULT_STACK_SIZE,DEFAULT_PRIORITY,DEFAULT_NUM_MSGS};
typedef struct _CLI_KB_KEY_MAP
{
    int code;
    char key_name[10];
    int key_code;
} CLI_KB_KEY_MAP_CODE;

static HANDLE_T        vz_ipc_thread = NULL_HANDLE;

static CLI_KB_KEY_MAP_CODE t_cli_kb_key_map_code[] =
{
	{97,             "a",                0xc0061},
	{98,             "b",                0xc0062},
	{99,             "c",                0xc0063},
	{100,           "d",                0xc0064},
	{101,	    "e",		  0xc0065},
	{102,	    "f",		  0xc0066},
	{103,	    "g",		  0xc0067},
	{104,	    "h",	          0xc0068},
	{105,           "i",                 0xc0069},
	{106,           "j",                 0xc006A},
	{107,           "k",                0xc006B},
	{108,           "l",                 0xc006C},
	{109,           "m",               0xc006D},
	{110,           "n",                0xc006E},
	{111,           "o",                0xc006F},
	{112,           "p",                0xc0070},
	{113,           "q",                0xc0071},
	{114,           "r",                0xc0072},
	{115,           "s",                0xc0073},
	{116,           "t",                0xc0074},
	{117,           "u",                0xc0075},
	{118,           "v",                0xc0076},
	{119,           "w",               0xc0077},
	{120,           "x",                0xc0078},
	{121,           "y",                0xc0079},
	{122,           "z",                0xc007A},

	{65,             "A",                0xc0041},
	{66,             "B",                0xc0042},
	{67,             "C",                0xc0043},
	{68,             "D",                0xc0044},
	{69,	    	    "E",		  0xc0045},
	{70,	            "F",		  0xc0046},
	{71,	            "G",		  0xc0047},
	{72,	            "H",	          0xc0048},
	{73,             "I",                 0xc0049},
	{74,             "J",                 0xc004A},
	{75,             "K",                0xc004B},
	{76,             "L",                0xc004C},
	{77,             "M",               0xc004D},
	{78,             "N",                0xc004E},
	{79,             "O",                0xc004F},
	{80,             "P",                0xc0050},
	{81,             "Q",                0xc0051},
	{82,             "R",                0xc0052},
	{83,             "S",                0xc0053},
	{84,             "T",                0xc0054},
	{85,             "U",                0xc0055},
	{86,             "V",                0xc0056},
	{87,             "W",               0xc0057},
	{88,             "X",                0xc0058},
	{89,             "Y",                0xc0059},
	{90,             "Z",                0xc005A},

	{8,             "DEL",                0xc0008},
	{64,             "@",                0xc0040},
	{35,             "#",                0xc0023},
	{36,             "$",                0xc0024},
	{95,             "_",               0xc005F},
	{38,             "&",                0xc0026},
	{45,             "-",                0xc002D},
	{43,             "+",                0xc002B},
	{40,             "(",		   0xc0028},
	{41,	  	    ")",		  0xc0029},
	{47,		     "/",		 0xc002F},
	{34,		      "QN",		 0xc0022},
	{39,		      "'",		  0xc0027},
	{58,		      ":",		 0xc003A},
	{59,		      ";",		 0xc003B},
	{33,			"!",		0xc0021},
	{63,			 "?",		   0xc003F},
	{126,		"~",		  0xc007E},
	{124,	       "|",		 0xc007C},
	{61,			 "=",		 0xc003D},
	{92,			  "", 	 	0xc005C},
	{123,		"{",		 0xc007B},
	{125,		"}",		 0xc007D},
	{91,			"[",		 0xc005B},
	{93,			"]",		 0xc005D},
	{62,			 ">",	 	0xc003E},
	{60,			 "<",	  	0xc003C},
	{37,			 "%",	  0xc0025},
	{94,			 "^",	  	0xc005E},
	{42,			 "*",		0xc002A},
	{44,			 ",",		0xc002C},
	{46,			 ".",		0xc002E},
//{46,			 "",		"0xc0060"},'
	{0,       "CUSTOMKEY",		   0}
};
static int jsonrpc_get_key_code(int keycode)
{
	int i =0;
	int code =0;
	while((t_cli_kb_key_map_code[i].key_code != 0) &&
		(i < (sizeof(t_cli_kb_key_map_code)/sizeof(t_cli_kb_key_map_code[0]))))
	{
		if(t_cli_kb_key_map_code[i].key_code == keycode)
		{
			code = t_cli_kb_key_map_code[i].code;
			break;
		}
		i++;
	}
	REST_LOG_I( "[REST] jsonrpc_get_key_code CODE is: %d\n\r" ,code );
	return code;
}

VOID  airplay_rest_sync_send_msg (VOID*      pv_data,
                                   SIZE_T     z_data_size)
{

        _airplay_notify_to_airplay("power_status", power_status, "");

        REST_LOG_I("return airplay_rest_sync_send_msg\r\n");
}

void jsonrpc_set_python_reeady ()
{
    REST_LOG_I( "[REST] jsonrpc_set_python_reeady!!!\n\r" );
    b_python_reeady = true;
}

static void rest_json_rpc_task_thread(void *pv_arg)
{
    vzlog::Log::log(vzlog::Log::LEVEL_ERROR, "JSONRPC", "enter rest_json_rpc_task_thread \n");
    method::Method method;

    while (g_run)
    {
        Json::Value root;
        Json::Value response;

        std::string data;

        while (true) {
            c_memset(&msg, 0, sizeof(REST_MSG_BUF));
            int ret = rest_get_msg_from_Vssp(&msg);
            //printf("rest_get_msg_from_Vssp : \n");
            if (0 != ret) {
                data = "";
                break;
            }

            data.append(msg.data_str);
            if (msg.seq == msg.total_size) {
                break;
            }
        }
        if (data=="")
        {
            continue;
        }

        Json::Reader reader;
        if (reader.parse(data, root)) {
            method.method(root, response);
            Json::FastWriter writer;

            std::string responseStr = writer.write(response);

            int size = responseStr.length();
            int index = 0;
            char * p = (char *)responseStr.c_str();

            do {
                c_memset(&msg, 0, sizeof(REST_MSG_BUF));

                msg.total_size = responseStr.length();

                if((unsigned int)size > REST_BUFFER_DATA_SIZE) {
                    c_memcpy(msg.data_str, p+index, REST_BUFFER_DATA_SIZE);
                    index += REST_BUFFER_DATA_SIZE;
                    size -= REST_BUFFER_DATA_SIZE;
                } else {
                    c_memcpy(msg.data_str, p+index, size);
                    index += size;
                    size = 0;
                }

                msg.seq = index;

                if(index != msg.total_size)
                {
                    REST_LOG_I( "Send response %d @ %d " , index , msg.total_size );
                }

                if (rest_send_msg_2_Vssp(&msg) == -1)
                {
                    REST_LOG_I( "Send fail" );
                    perror("####ERROR:");
                    REST_LOG_E("Error while sending data!\n\r" );
                    return;
                }

            } while (size != 0);
        }

    }
    rest_vssp_destroy();
    return;
}

/*
    events.__setitem__('oobe/currentstate', Event.OOBE_CURRENTSTATE)
    events.__setitem__('uli/update_status', Event.ULI_UPDATE_STATUS)
    events.__setitem__('uli/available_update_info', Event.ULI_AVAILABLE_UPDATE_INFO)
    events.__setitem__('tv_settings/system/menu_language', Event.LANGUAGE)
    events.__setitem__('tv_settings/cast/device_name', Event.DEVICE_NAME)
    events.__setitem__('tv_settings/devices/current_input', Event.CURRENT_INPUT)
    events.__setitem__('state/device/power_mode', Event.POWER_MODE)
    events.__setitem__('key_command', Event.KEYCOMMAND)
    events.__setitem__('app/current', Event.CURRENT_APP)
    events.__setitem__('app/tts/enabled', Event.TTS_ENABLE)
    events.__setitem__('app/zoom/enabled', Event.ZOOM_ENABLE)
    events.__setitem__('tv_settings/network/connection_status', Event.NETWORK_CONNECTION_STATUS)
    events.__setitem__('tv_settings/cast/tos_accepted', Event.CAST_TOS_ACCEPTED)
    events.__setitem__('tv_settings/closed_captions/closed_captions_enabled', Event.CLOSED_CAPTIONS_ENABLE)
*/
void jsonrpc_send_event(const char* uri, int intValue, const char* stringValue)
{
    //vzlog::Log::log(vzlog::Log::LEVEL_ERROR, "JSONRPC", "jsonrpc_send_event: enter, uri=%s, intValue=%d, stringValue=%s\n", uri, intValue, stringValue);
    REST_LOG_I( "[REST] jsonrpc_send_event uri: %s, intValue: %d, stringValue: %s\n\r", uri, intValue, stringValue);
    
    Json::Value         response, result;
    Json::FastWriter    writer;
    int                 size = 0, index = 0;
    char*               p = NULL;
    REST_MSG_BUF        notifyMsg;
    CHAR                s_active_app[16] = {0};
    int                 key_code = 0;

    response["jsonrpc"] = "2.0";
    response["uri"] = uri;

    if (c_strcmp(uri, "key_command") == 0)
    {
        Json::Value key, keylist;
        key["ACTION"] = "KEYPRESS";

        //REST_LOG_I( "[REST] jsonrpc_send_event: BTN_WIDGET is " << BTN_WIDGET );
        //REST_LOG_I( "[REST] jsonrpc_send_event: BTN_NETFLIX is " << BTN_NETFLIX );
        //REST_LOG_I( "[REST] jsonrpc_send_event: BTN_VUDU is " << BTN_VUDU );
        //REST_LOG_I( "[REST] jsonrpc_send_event: BTN_AMAZON is " << BTN_AMAZON );
        //REST_LOG_I( "[REST] jsonrpc_send_event: BTN_XUMO is " << BTN_XUMO );
        //REST_LOG_I( "[REST] jsonrpc_send_event: BTN_CRACKLE is " << BTN_CRACKLE );
        //REST_LOG_I( "[REST] jsonrpc_send_event: BTN_IHEART_RADIO is " << BTN_IHEART_RADIO );

        /* If it's browser_control activated. Need to handle system key here */
        //_rest_app_handle_key_for_browser_control(intValue);

        switch (intValue)
        {
            case BTN_DIGIT_0:
            case BTN_DIGIT_1:
            case BTN_DIGIT_2:
            case BTN_DIGIT_3:
            case BTN_DIGIT_4:
            case BTN_DIGIT_5:
            case BTN_DIGIT_6:
            case BTN_DIGIT_7:
            case BTN_DIGIT_8:
            case BTN_DIGIT_9:
                key["CODESET"] = 0;
                key["CODE"] = intValue - 65536;
                break;
            case BTN_KB_MINUS_SIGN:
                key["CODESET"] = 0;
                key["CODE"] = 45;
                break;

            case BTN_SELECT:
                //key["CODESET"] = 2;
                key["CODESET"] = 3;
                key["CODE"] = 2;
                break;

            case BTN_CURSOR_LEFT:
            case BTN_CURSOR_RIGHT:
            case BTN_CURSOR_UP:
            case BTN_CURSOR_DOWN:
                key["CODESET"] = 3;
                if(intValue == BTN_CURSOR_DOWN) key["CODE"] = 0;
                else if(intValue == BTN_CURSOR_LEFT) key["CODE"] = 1;
                else if(intValue == BTN_CURSOR_RIGHT) key["CODE"] = 7;
                else  key["CODE"] = 8;
                break;

            case BTN_PRG_DOWN:
            case BTN_PRG_UP:
            case BTN_PREV_PRG:
                key["CODESET"] = 8;
                if (intValue == BTN_PRG_DOWN) key["CODE"] = 0;
                else if (intValue == BTN_PRG_UP) key["CODE"] = 1;
                else key["CODE"] = 2;
                break;

            case BTN_RETURN:
                key["CODESET"] = 4;
                key["CODE"] = 0;
                break;

            case BTN_VOL_UP:
                key["CODESET"] = 5;
                key["CODE"] = 1;
                break;
            case BTN_VOL_DOWN:
                key["CODESET"] = 5;
                key["CODE"] = 0;
                break;

            case BTN_EXIT:      //323585
                key["CODESET"] = 4;
                key["CODE"] = 3;
                break;

            case BTN_MUTE:      //454658
                key["CODESET"] = 5;
                key["CODE"] = 4;
                break;

            case BTN_CC:        //389146
                key["CODESET"] = 13;
                key["CODE"] = 1;
                break;

            case BTN_ASPECT:    //389141
                key["CODESET"] = 6;
                key["CODE"] = 2;
                break;

            case BTN_INPUT_SRC: //389151
                key["CODESET"] = 7;
                key["CODE"] = 4;
                return;

            case BTN_P_EFFECT:  //389142 PIC key
                key["CODESET"] = 6;
                key["CODE"] = 0;
                return;

            //case BTN_PRG_INFO:  //389143
            //    key["CODESET"] = 4;
            //    key["CODE"] = 6;
            //    break;

            case BTN_FF:
                key["CODESET"] = 2;
                key["CODE"] = 0;
                break;
            case BTN_FR:
                key["CODESET"] = 2;
                key["CODE"] = 1;
                break;
            case BTN_PAUSE:
                key["CODESET"] = 2;
                key["CODE"] = 2;
                break;
            case BTN_PLAY:
                key["CODESET"] = 2;
                key["CODE"] = 3;
                break;
            case BTN_RECORD:
                key["CODESET"] = 2;
                key["CODE"] = 4;
                break;
            case BTN_SF:
                key["CODESET"] = 2;
                key["CODE"] = 5;
                break;
            case BTN_SR:
                key["CODESET"] = 2;
                key["CODE"] = 6;
                break;
            case BTN_STEPR:
                key["CODESET"] = 2;
                key["CODE"] = 7;
                break;
            case BTN_STEPF:
                key["CODESET"] = 2;
                key["CODE"] = 8;
                break;
            case BTN_STOP:
                key["CODESET"] = 2;
                key["CODE"] = 9;
                break;
            case BTN_NEXT:
                key["CODESET"] = 2;
                key["CODE"] = 10;
                break;
            case BTN_PREV:
                key["CODESET"] = 2;
                key["CODE"] = 11;
                break;

            case BTN_WIDGET: // VIA key
                _rest_app_receiving_hotkeys(0x2d, TRUE);
                return;
            case BTN_NETFLIX:
                _rest_app_receiving_hotkeys(0xeb, TRUE);
                REST_LOG_I( "[REST] jsonrpc_send_event: system will handle launching Netflix\n\r" );
                return;
            case BTN_VUDU:
                _rest_app_receiving_hotkeys(0xec, TRUE);
                return;
            case BTN_AMAZON:
                _rest_app_receiving_hotkeys(0xea, TRUE);
                return;
            case BTN_XUMO:
                _rest_app_receiving_hotkeys(0x6f, TRUE);
                return;
            case BTN_CRACKLE:
                _rest_app_receiving_hotkeys(0xf8, TRUE);
                return;
            case BTN_HULU:
                _rest_app_receiving_hotkeys(0xf9, TRUE);
                return;
            case BTN_IHEART_RADIO:
                _rest_app_receiving_hotkeys(0xee, TRUE);
                return;
            case BTN_WATCHFREE:
                _rest_app_receiving_hotkeys(0xf7, TRUE);
                return;
            case BTN_REDBOX:
                _rest_app_receiving_hotkeys(0x42, TRUE);
                return;
            case BTN_HAYSTACK:
		_rest_app_receiving_hotkeys(0x1e, TRUE);
		return;
		case BTN_DISNEY:
		_rest_app_receiving_hotkeys(0x1f, TRUE);
		return;
		case BTN_PARTNER_1:
		_rest_app_receiving_hotkeys(0x0b, TRUE);
		return;
		case BTN_PARTNER_2:
		_rest_app_receiving_hotkeys(0x51, TRUE);
		return;
		case BTN_PARTNER_3:
		_rest_app_receiving_hotkeys(0x5A, TRUE);
		return;
		case BTN_PARTNER_4:
		_rest_app_receiving_hotkeys(0x60, TRUE);
		return;
		case BTN_PARTNER_5:
		_rest_app_receiving_hotkeys(0x61, TRUE);
		return;
		case BTN_PARTNER_6:
		_rest_app_receiving_hotkeys(0x62, TRUE);
		return;
		case BTN_PARTNER_7:
		_rest_app_receiving_hotkeys(0x64, TRUE);
		return;
		case BTN_PARTNER_8:
		_rest_app_receiving_hotkeys(0x65, TRUE);
		return;
		case BTN_PARTNER_9:
		_rest_app_receiving_hotkeys(0x73, TRUE);
		return;
		case BTN_PARTNER_10:
		_rest_app_receiving_hotkeys(0x80, TRUE);
		return;
		case BTN_PARTNER_11:
		_rest_app_receiving_hotkeys(0xA0, TRUE);
		return;
		case BTN_PARTNER_12:
		_rest_app_receiving_hotkeys(0xA3, TRUE);
		return;
		case BTN_PARTNER_13:
		_rest_app_receiving_hotkeys(0xA4, TRUE);
		return;
		case BTN_PARTNER_14:
		_rest_app_receiving_hotkeys(0xB0, TRUE);
		return;
		case BTN_PARTNER_15:
		_rest_app_receiving_hotkeys(0xF1, TRUE);
		return;
		case BTN_PARTNER_16:
		_rest_app_receiving_hotkeys(0xF2, TRUE);
		return;
		case BTN_PARTNER_17:
		_rest_app_receiving_hotkeys(0xF3, TRUE);
		return;
		case BTN_PARTNER_18:
		_rest_app_receiving_hotkeys(0xF4, TRUE);
		return;
		case BTN_PARTNER_19:
		_rest_app_receiving_hotkeys(0xF5, TRUE);
		return;
		case BTN_PARTNER_20:
		_rest_app_receiving_hotkeys(0xF6, TRUE);
		return;
#if 0
		case BTN_PEACOCK:
		_rest_app_receiving_hotkeys(0x51, TRUE);
		return;
		case BTN_TUBI:
		_rest_app_receiving_hotkeys(0x5A, TRUE);
		return;
#endif
            default:
            {
                key_code = jsonrpc_get_key_code(intValue);
                if(key_code != 0)
                {
                    key["CODESET"] = 0;
                    key["CODE"] = key_code;
                    break;
                }else{
                    key["CODESET"] = 0;
                    key["CODE"] = intValue;
                    return;
                }
            }
        }

        keylist[0] = key;
        result["KEYLIST"] = keylist;
        response["result"] = result;

        if (a_c4tv_apron_check_cast_state() != TRUE
            && a_rest_app_get_current_app_is_semaphore() != 0)
        {
            REST_LOG_E( "[REST] jsonrpc_send_event: not in cast_shell, not in semaphore, don't notify key up\n\r" );
            return;
        }

        c_memset(s_active_app, '\0', 16);
        a_am_get_active_app (s_active_app) ;
        if (c_strcmp(s_active_app, "menu") == 0)
        {
            REST_LOG_E( "[REST] jsonrpc_send_event: menu topped, don't notify key up\n\r" );
            return;
        }
        if (c_strcmp(s_active_app, "navigator") == 0
            && NAV_COMP_ID_PICTURE_EFFECT == nav_get_active_component())
        {
            REST_LOG_E( "[REST] jsonrpc_send_event: pic topped, don't notify key up\n\r" );
            return;
        }
        REST_LOG_I( "[REST][10FAPPCHECKPOINT] jsonrpc_send_event: BTN_XXX=%d\n\r",intValue );
    }
    else if (c_strcmp(uri, "oobe/currentstate") == 0)
    {
        if(c_strcmp(stringValue, "UPDATING_SMARTCAST_IR") == 0) {
            result["IRMode"] = 1;
        }
        result["CS"] = stringValue;
        if (intValue==1) {
            result["TYPE"] = "PUT";
        } else {
            result["TYPE"] = "EVENT";
        }
        response["result"] = result;
    }
    /*else if (c_strcmp(uri, "tv_settings/devices/current_input") == 0)
    {
        char s_input[24] = {0};
        char* p = NULL;

        result["VALUE"] = stringValue;

        // If it's in DEMO mode, do not change current app
        ACFG_RETAIL_MODE_T t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        {
            REST_LOG_I( "[REST] jsonrpc_send_event: in demo mode" );
        }
        else if (c_strstr(stringValue, "CAST") == NULL)
        {
            REST_LOG_I( "[REST] jsonrpc_send_event: switch to none-cast input, clear current app" );
            _rest_app_no_app_notification();
        }
        else
        {
            REST_LOG_I( "[REST] jsonrpc_send_event: switch to cast input, launch corresponding app" );
            _rest_app_switch_input_to_cast(stringValue);

            c_memset(s_input, '\0', 24);
            c_strncpy(s_input, stringValue, 24);
            p = c_strstr(s_input, ":");
            if (p != NULL) {
                *p = '\0';
                result["VALUE"] = s_input;
            }

            a_nav_show_banner_ex();
        }

        response["result"] = result;
    }*/
    else if (c_strcmp(uri, "tv_settings/system/menu_language") == 0)
    {
        _rest_app_handle_menu_lang_chg();
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "tv_settings/channels/percent_complete") == 0
             || c_strcmp(uri, "tv_settings/channels/analog") == 0
             || c_strcmp(uri, "tv_settings/channels/digital") == 0)
    {
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "tv_settings/network/connection_status") == 0)
    {
        if (intValue == 1) {
            if (rest_network_is_internet_connected() == FALSE) {
                _rest_app_set_connection_status(FALSE);
                return;
            }
            _rest_app_set_connection_status(TRUE);

            if (b_python_reeady == false)
            {
                std::cout << "[REST]event: connection_status- python not ready" << std::endl;
            }

			std::cout << "[REST] jsonrpc_send_event: connection_status" << std::endl;
			_airplay_notify_to_airplay("power_status", 1, "");
        } else if (intValue == 0) {
            _rest_app_set_connection_status(FALSE);
        }
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "system/input/name") == 0
             || c_strcmp(uri, "system/input/enable") == 0)
    {
        printf( "[REST] notify received, uri %s, intValue %d, stringValue %s\n\r" , uri, intValue, stringValue);
        if ((strstr(stringValue, "hdmi") != NULL) || (strstr(stringValue, "Player") != NULL))
        {
            // MVV-10206: patch to get the correct input list
            _rest_app_set_input_name_status((BOOL)intValue);
        }
        result["VALUE"] = stringValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "system/input/visible") == 0
             || c_strcmp(uri, "system/input/cec") == 0)
    {
        printf( "[REST] notify received, uri %s, intValue %d, stringValue %s\n\r" , uri, intValue, stringValue);
        result["VALUE"] = stringValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "airplay/property") == 0
             || c_strcmp(uri, "tv_settings/system/power_mode") == 0
             || c_strcmp(uri, "tv_settings/picture/picture_mode") == 0
             || c_strcmp(uri, "tv_settings/audio/tv_speakers") == 0
             || c_strcmp(uri, "tv_settings/audio/mute") == 0
             || c_strcmp(uri, "airplay/disabled") == 0
             || c_strcmp(uri, "system/time/timezone") == 0)
    {
        result["VALUE"] = stringValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "system/picture/picture_mode") == 0)
    {
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "tv_settings/cast/device_name") == 0)
    {
        result["VALUE"] = stringValue;
        response["result"] = result;
        _airplay_notify_to_airplay("device_name", 1, stringValue);
    }
    else if (c_strcmp(uri, "system/input/list") == 0)
    {
        printf( "[REST] notify received, uri %s, intValue %d, stringValue %s\n\r" , uri, intValue, stringValue);
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "tv_settings/audio/tv_speakers") == 0
             || c_strcmp(uri, "tv_settings/audio/volume_selector") == 0
             || c_strcmp(uri, "tv_settings/cast/tos_accepted") == 0
             || c_strcmp(uri, "tv_settings/closed_captions/closed_captions_enabled") == 0
             || c_strcmp(uri, "app/zoom/enabled") == 0
             || c_strcmp(uri, "app/tts/enabled") == 0
             || c_strcmp(uri, "system/network_time") == 0
             || c_strcmp(uri, "tv_settings/audio/volume") == 0
             || c_strcmp(uri, "tv_settings/picture/brightness") == 0
             || c_strcmp(uri, "system/network_time") == 0)
    {
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "audio/volume/level") == 0) //dolphin 20200518 add  notify
    {
        int i4_volume = intValue; //vol:[pre|cur] dolphin 20200518 use one int to storage two short
        short i4_pre_volume = i4_volume >> 16 & 0xffff;
        short i4_cur_volume = i4_volume  & 0xffff;

        if(i4_pre_volume==-1)  //when first notify ,init value will be empty ,so we need to set it the init value
        {
            i4_pre_volume = rest_get_init_volume();
            REST_LOG_E("reset the volume [%d|%d]\n",i4_pre_volume,i4_cur_volume);
        }

        result["PREV_LEVEL"] = i4_pre_volume;
        result["CURRENT_LEVEL"] = i4_cur_volume;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "audio/volume/mute") == 0)
    {
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "state/device/power_mode") == 0)
    {
        result["VALUE"] = intValue;
        response["result"] = result;
        rest_async_invoke(airplay_rest_sync_send_msg, NULL, 0, TRUE);

    }
    else if (c_strcmp(uri, "uli/update_status") == 0)
    {
        result["STATUS"] = 0;
        result["PERCENT_COMPLETE"] = 0;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "uli/available_update_info") == 0)
    {
        result["UPDATE_LEVEL"] = 0;
        result["VERSION"] = "";
        result["IS_AVAILABLE"] = 0;
        response["VALUE"] = result;
    }
    else if (c_strcmp(uri, "tv_settings/cast/state") == 0)
    {
        if (intValue == 5) {
            intValue = 6;
        }
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "tv_settings/system/reset_and_admin/tvad_id_reset") == 0)
    {
        result["TYPE"] = "PUT";
        response["result"] = result;
    }
    else if (c_strcmp(uri, "app/current") == 0)
    {
        //REST_LOG_I( "[REST] jsonrpc_send_event: app/current" << uri );
        // EVENT type
        if (intValue == 0)
        {
            REST_LOG_I( "[REST] jsonrpc_send_event: app/current- EVENT\n\r" );

            TENFOOTAPP t_current_app;
            c_memset(&t_current_app, 0, sizeof(_TENFOOTAPP));

            _rest_app_get_current_app(&t_current_app);
            if (t_current_app.b_activated == TRUE)
            {
                result["NAME_SPACE"] = (int)t_current_app.i4_name_space;
                REST_LOG_I("[REST] jsonrpc_send_event: app/current- EVENT- NAME_SPACE: %d.\n\r", t_current_app.i4_name_space);
                result["APP_ID"] = std::string((char*)t_current_app.app_id);
                REST_LOG_I("[REST] jsonrpc_send_event: app/current- EVENT- APP_ID: %s.\n\r", t_current_app.app_id);
                result["MESSAGE"] = std::string(t_current_app.msg);
                REST_LOG_I("[REST] jsonrpc_send_event: app/current- EVENT- MESSAGE: %s.\n\r", t_current_app.msg);

                /* dolphin add judge conjure or normal paltform conjure */
                if(TRUE == a_rest_is_conjure_install())  //conjure
                {
                    if((4==(int)t_current_app.i4_name_space && 0==c_strncmp(t_current_app.app_id,"1",1))
                        ||(3==(int)t_current_app.i4_name_space && 0==c_strncmp(t_current_app.app_id,"2",1)))  //NAMESPACE: 4   APP ID: 1   >> SCH NAMESAPCE: 3 APP_ID : 2 >> MMP
                    {
                        REST_LOG_I("[REST] jsonrpc_send_event: app/current- EVENT CONJURE SCH\n\r");
                        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED); //dolphin 20190727 set 3rd stop to launch sch
                    }
                    else
                    {
                        REST_LOG_I("[REST] jsonrpc_send_event: app/current- EVENT CONJURE 3RD\n\r");
                        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_RESUMED); //dolphin 20190727 set 3rd resume
                    }
                }
                else //normal
                {
                    if((2==t_current_app.i4_name_space && 0==c_strncmp(t_current_app.app_id,"1",1))
                        ||(3==(int)t_current_app.i4_name_space && 0==c_strncmp(t_current_app.app_id,"2",1)))  //NAMESPACE: 2   APP ID: 1   >> SCH NAMESAPCE: 3 APP_ID : 2 >> MMP
                    {
                        REST_LOG_I("[REST] jsonrpc_send_event: app/current- EVENT CS SCH\n\r");
                        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_PAUSED); //dolphin 20190727 set 3rd stop to launch sch
                    }
                    else
                    {
                        REST_LOG_I("[REST] jsonrpc_send_event: app/current- EVENT CS\n\r");
                        a_tv_net_set_tv_svc_status(APP_TV_NET_SVC_STATUS_RESUMED); //dolphin 20190727 set 3rd resume
                    }
                }

            }
            else
            {
                result["NAME_SPACE"] = 0;
                result["APP_ID"] = "";
                result["MESSAGE"] = "";
            }
            result["TYPE"] = "EVENT";
            response["result"] = result;
        }
        // PUT type
        else
        {
            char s_app_id[16];
            char s_temp[1024+16+1];
            char s_msg[1024];
            char* sp_split;
            UINT32 split;

            std::cout << "[REST][10FAPPCHECKPOINT] jsonrpc_send_event: app/current- PUT" << std::endl;
            if (b_python_reeady == false) {
                std::cout << "[REST][10FAPPCHECKPOINT] jsonrpc_send_event: app/current- PUT- python not ready" << std::endl;
                return;
            }

            c_memset(s_app_id, '\0', 16);
            c_memset(s_temp, '\0', 1024+16+1);
            c_memset(s_msg, '\0', 1024);

            result["NAME_SPACE"] = intValue-1;

            c_strcpy(s_temp, stringValue);
            split = 0;
            while (split < c_strlen(s_temp)) {
                if (s_temp[split] == ':') {
                    s_temp[split] = '\0';
                    break;
                }
                split++;
            }
            c_strncpy(s_app_id, s_temp, 15);
            REST_LOG_I( "[10FAPPCHECKPOINT] split app_id:%s\n\r", s_app_id );
            result["APP_ID"] = s_app_id;

            if (s_temp[split+1] != '\0')
            {
                sp_split = &(s_temp[split+1]);
                REST_LOG_I( "[10FAPPCHECKPOINT] split msg:%s\n\r" , sp_split );
                c_strncpy(s_msg, sp_split, 1023);
                result["MESSAGE"] = s_msg;
            }
            else {
                result["MESSAGE"] = "";
            }
            result["TYPE"] = "PUT";
            response["result"] = result;
        }
    }
    else if(c_strcmp(uri, "tv_settings/channels/channel_scan_state") == 0) {
        REST_LOG_I( "[REST] jsonrpc_send_event: tv_settings/channels/channel_scan_state- EVENT\n\r" );
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (/*c_strcmp(uri, "system/current_inputs") == 0
             || c_strcmp(uri, "tv_settings/devices/current_inputs") == 0
             || */c_strcmp(uri, "system/input/current_input") == 0)
    {
        printf( "[REST] notify received, uri %s, intValue %d, stringValue %s\n\r" , uri, intValue, stringValue);
        Json::Value input_list;
        Json::Reader reader;

        /*if (c_strcmp(uri, "system/current_inputs") == 0
            && b_python_reeady == false) {
            REST_LOG_I( "[REST][10FAPPCHECKPOINT] jsonrpc_send_event: system/current_inputs- python not ready" );
            return;
        }*/

        if (!reader.parse(stringValue, input_list)) {
            REST_LOG_E( "[REST] jsonrpc_send_event: error parsing string to json\n\r" );
            return;
        }
        REST_LOG_I( "[REST] jsonrpc_send_event: parse result: %s\n\r", input_list.toStyledString().c_str());
        result["VALUE"] = input_list;
        response["result"] = result;
    }
    else if(c_strcmp(uri, "system/check_for_update") == 0) {
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if(c_strcmp(uri, "tv_settings/system/time/automatic_time/tuner_time") == 0) {  //dolphin 20200908 add notify whether get current AT status
        result["VALUE"] = intValue;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "ir_command") == 0)
    {
        REST_LOG_I( "ir_command: intValue: %d\n\r" , intValue );
        Json::Value key;

        UINT8 zoom_mode = -1;
        a_cfg_cust_get_zoom_status(&zoom_mode);
        if ((((unsigned long)intValue <= BTN_DIGIT_9 && (unsigned long)intValue >= BTN_DIGIT_0) || (unsigned long)intValue == BTN_KB_MINUS_SIGN) && (1 != zoom_mode))
        {
            REST_LOG_I( "only in zoom mode digit and dash key are non-routable\n\r" );
            return;
        }

        switch (intValue)
        {
            case BTN_KB_MINUS_SIGN:
                result["IR"] = "0xd4";
                key["CODESET"] = 0;
                key["CODE"] = 44;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_0:
                result["IR"] = "0x10";
                key["CODESET"] = 0;
                key["CODE"] = 48;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_1:
                result["IR"] = "0x11";
                key["CODESET"] = 0;
                key["CODE"] = 49;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_2:
                result["IR"] = "0x12";
                key["CODESET"] = 0;
                key["CODE"] = 50;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_3:
                result["IR"] = "0x13";
                key["CODESET"] = 0;
                key["CODE"] = 51;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_4:
                result["IR"] = "0x14";
                key["CODESET"] = 0;
                key["CODE"] = 52;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_5:
                result["IR"] = "0x15";
                key["CODESET"] = 0;
                key["CODE"] = 53;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_6:
                result["IR"] = "0x16";
                key["CODESET"] = 0;
                key["CODE"] = 54;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_7:
                result["IR"] = "0x17";
                key["CODESET"] = 0;
                key["CODE"] = 55;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_8:
                result["IR"] = "0x18";
                key["CODESET"] = 0;
                key["CODE"] = 56;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_DIGIT_9:
                result["IR"] = "0x19";
                key["CODESET"] = 0;
                key["CODE"] = 57;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_POWER:
                result["IR"] = "0x08";
                key["CODESET"] = 11;
                key["CODE"] = 2;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_INPUT_SRC: //389151
                result["IR"] = "0x2f";
                key["CODESET"] = 7;
                key["CODE"] = 4;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_MENU:
                result["IR"] = "0x43";
                key["CODESET"] = 4;
                key["CODE"] = 8;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_VOL_UP:
                result["IR"] = "0x02";
                key["CODESET"] = 5;
                key["CODE"] = 1;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_VOL_DOWN:
                result["IR"] = "0x03";
                key["CODESET"] = 5;
                key["CODE"] = 0;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_MUTE:      //454658
                result["IR"] = "0x09";
                key["CODESET"] = 5;
                key["CODE"] = 4;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_CC:        //389146
                result["IR"] = "x39";
                key["CODESET"] = 13;
                key["CODE"] = 1;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_WIDGET: // VIA key
                result["IR"] = "0x2d";
                key["CODESET"] = 4;
                key["CODE"] = 15;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_P_EFFECT:  //389142 PIC key
                result["IR"] = "0x67";
                key["CODESET"] = 6;
                key["CODE"] = 0;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_PRG_UP:
                result["IR"] = "0x00";
                key["CODESET"] = 8;
                key["CODE"] = 1;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_PRG_DOWN:
                result["IR"] = "0x01";
                key["CODESET"] = 8;
                key["CODE"] = 0;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_PREV_PRG:
                result["IR"] = "0x1a";
                key["CODESET"] = 8;
                key["CODE"] = 2;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_WIDE_MODE:
                result["IR"] = "0x77";
                key["CODESET"] = 6;
                key["CODE"] = 1;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_ILINK:
                result["IR"] = "0xb8";
                key["CODESET"] = 4;
                key["CODE"] = 16;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_PRG_INFO:      //0x5f017
                result["IR"] = "0x1b";
                key["CODESET"] = 4;
                key["CODE"] = 6;
                key["ACTION"] = 0;
                result["HAS_KEY"] = 1;
                break;
            case BTN_NETFLIX:
                result["IR"] = "0xeb";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_VUDU:
                result["IR"] = "0xec";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_AMAZON:
                result["IR"] = "0xea";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_XUMO:
                result["IR"] = "0x6f";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_CRACKLE:
                result["IR"] = "0xf8";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_HULU:
                result["IR"] = "0xf9";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_IHEART_RADIO:
                result["IR"] = "0xee";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_WATCHFREE:
                result["IR"] = "0xf7";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_REDBOX:
                result["IR"] = "0x42";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
            case BTN_HAYSTACK:
                result["IR"] = "0x1e";
                result["HAS_KEY"] = 0;
                key = "null";
                break;
		case BTN_MIC: // IR MIC key+
		   result["IR"] = "0x2d";
		   key["CODESET"] = 4;
		   key["CODE"] = 17;
		   key["ACTION"] = 0;
		   result["HAS_KEY"] = 1;
		break;
            default:
                REST_LOG_E( "routable key, do not send to rest\n\r" );
                return;
        }

        result["KEY"] = key;
        response["result"] = result;

        REST_LOG_I( "[REST][10FAPPCHECKPOINT] jsonrpc_send_event: BTN_XXX=%d\n\r" , intValue );
    }
    else if (c_strcmp(uri, "app/metadata") == 0)
    {
        Json::Value preAppData;
#ifdef VIZIO_FUSION_SUPPORT
        Get_pre_app_data(preAppData);
#endif
        response["result"] = preAppData;
    }
    else if (c_strcmp(uri, "tv_settings/closed_captions/digital_style") == 0) //dolphin 20200506 add nfy DTV02171858
    {
        Json::Value digital_style;
        digital_style["text_style"] = menu_get_font_style_idx();
        digital_style["text_size"] = menu_get_font_size_idx();
        digital_style["text_color"] = menu_get_font_color_idx();
        digital_style["text_opacity"] = menu_get_font_opac_idx();
        digital_style["text_edges"] = menu_get_text_edges_idx();
        digital_style["text_edges_color"] = menu_get_text_edges_color_idx();
        digital_style["background_color"] = menu_get_bg_color_idx();
        digital_style["background_opacity"] = menu_get_bg_opac_idx();
        digital_style["window_color"] = menu_get_win_color_idx();
        digital_style["window_opacity"] = menu_get_win_opac_idx();

        response["result"] = digital_style;
    }
    else if (c_strcmp(uri, "system/cec") == 0)
    {
        Json::Value cec_device;
        Json::Reader reader;

        if (!reader.parse(stringValue, cec_device)) {
            REST_LOG_E( "[REST] jsonrpc_send_event: error parsing string to json\n\r" );
            return;
        }
        REST_LOG_E( "[REST] jsonrpc_send_event: parse result: %s\n\r", cec_device.toStyledString().c_str());
        result["VALUE"] = cec_device;
        response["result"] = result;
    }
    else
    {
        REST_LOG_I( "[REST] jsonrpc_send_event: unknown uri:%s\n\r" , uri );
        return;
    }

    std::string responseStr = writer.write(response);
    size = responseStr.length();
    p = (char *)responseStr.c_str();

    do {
        c_memset(&notifyMsg, 0, sizeof(REST_MSG_BUF));
        notifyMsg.total_size = size;
        if ((unsigned int)size > REST_BUFFER_DATA_SIZE)
        {
            c_memcpy(notifyMsg.data_str, p+index, REST_BUFFER_DATA_SIZE);
            index += REST_BUFFER_DATA_SIZE;
            size -= REST_BUFFER_DATA_SIZE;
        }
        else
        {
            c_memcpy(notifyMsg.data_str, p+index, size);
            index += size;
            size = 0;
        }

        notifyMsg.seq = index;
        if (index != notifyMsg.total_size) {
            REST_LOG_I( "[REST] jsonrpc_send_event: send response %d %s %d\n\r", index, " @ " , notifyMsg.total_size );
        }

        if (rest_send_msg_2_Vssp_event(&notifyMsg) == -1) {
            REST_LOG_E( "[REST] jsonrpc_send_event: send fail\n\r" );
            return;
        }
        REST_LOG_I( "[REST] jsonrpc_send_event: send success\n\r" );
    } while (size != 0);

    return;
}

void jsonrpc_send_event_ex(const char* uri, const void* data)
{
    REST_LOG_I( "[REST] jsonrpc_send_event_ex uri:%s\n\r " , uri );

    Json::Value response, result;
    Json::FastWriter writer;
    int size = 0, index = 0;
    char * p = NULL;
    REST_MSG_BUF notifyMsg;

    response["jsonrpc"] = "2.0";
    response["uri"] = uri;

    if (c_strcmp(uri, "uli/available_update_info") == 0)
    {
        NAV_UPDATE_ULI_AVAIL_INFO_T* pt_avail_info = (NAV_UPDATE_ULI_AVAIL_INFO_T*)data;
        result["UPDATE_LEVEL"] = pt_avail_info->ui_fw_policy;
        result["VERSION"] = std::string(pt_avail_info->s_ver);
        result["IS_AVAILABLE"] = pt_avail_info->ui1_fw_status;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "uli/update_status") == 0)
    {
        NAV_UPDATE_ULI_UPDATE_STATUS_T* t_update_status = (NAV_UPDATE_ULI_UPDATE_STATUS_T*)data;
        result["STATUS"] = t_update_status->ui1_update_status;
        result["PERCENT_COMPLETE"] = t_update_status->ui1_progress;
        response["result"] = result;
    }
    else if (c_strcmp(uri, "airplay/property") == 0)
    {
        AirplayPropertyNotofication* nf_data = (AirplayPropertyNotofication*)data;
        // "VALUE": {"PROPERTY": "hkAccessControlLevel", "TYPE": 1, "VALUE": 1}
        result["PROPERTY"] = std::string(nf_data->propety);
        result["TYPE"] = nf_data->type;
        if (nf_data->type == 0) { // string
            result["VALUE"] = std::string(nf_data->value_string);
        } else if (nf_data->type == 1) { // int
            result["VALUE"] = nf_data->value_int;
        }
        response["result"] = result;
    }
    else
    {
        REST_LOG_I( "[REST] jsonrpc_send_event_ex: unknown uri:%s\n\r" , uri );
        return;
    }

    std::string responseStr = writer.write(response);
    size = responseStr.length();
    p = (char *)responseStr.c_str();

    do
    {
        c_memset(&notifyMsg, 0, sizeof(REST_MSG_BUF));

        notifyMsg.total_size = size;

        if((unsigned int)size > REST_BUFFER_DATA_SIZE)
        {
            c_memcpy(notifyMsg.data_str, p+index, REST_BUFFER_DATA_SIZE);
            index += REST_BUFFER_DATA_SIZE;
            size -= REST_BUFFER_DATA_SIZE;
        }
        else
        {
            c_memcpy(notifyMsg.data_str, p+index, size);
            index += size;
            size = 0;
        }

        notifyMsg.seq = index;

        if(index != notifyMsg.total_size)
        {
            REST_LOG_I( "[REST] jsonrpc_send_event_ex: send response %d %s %d\n\r" , index , " @ " , notifyMsg.total_size );
        }

        if (rest_send_msg_2_Vssp_event(&notifyMsg) == -1)
        {
            REST_LOG_E( "[REST] jsonrpc_send_event_ex: send fail\n\r" );
            return;
        }
        REST_LOG_I( "[REST] jsonrpc_send_event_ex: send success\n\r" );

    } while (size != 0);

    return;
}
#if 0
void jsonrpc_send_event_json(const char* uri, const void* data)
{
    REST_LOG_I( "[REST] jsonrpc_send_event_json uri: " << uri );

    Json::Value response, result;
    Json::FastWriter writer;
    int size = 0, index = 0;
    char * p = NULL;
    REST_MSG_BUF notifyMsg;

    response["jsonrpc"] = "2.0";
    response["uri"] = uri;

    result["VALUE"] = (Json::Value &)data;
    REST_LOG_I( "[REST] jsonrpc_send_event_json data: " << result["VALUE"].toStyledString() );
    response["result"] = result;

    std::string responseStr = writer.write(response);
    size = responseStr.length();
    p = (char *)responseStr.c_str();

    do {
        c_memset(&notifyMsg, 0, sizeof(REST_MSG_BUF));
        notifyMsg.total_size = size;
        if ((unsigned int)size > REST_BUFFER_DATA_SIZE)
        {
            c_memcpy(notifyMsg.data_str, p+index, REST_BUFFER_DATA_SIZE);
            index += REST_BUFFER_DATA_SIZE;
            size -= REST_BUFFER_DATA_SIZE;
        }
        else
        {
            c_memcpy(notifyMsg.data_str, p+index, size);
            index += size;
            size = 0;
        }

        notifyMsg.seq = index;
        if (index != notifyMsg.total_size) {
            REST_LOG_I( "[REST] jsonrpc_send_event_json: send response " << index << " @ " << notifyMsg.total_size );
        }

        if (rest_send_msg_2_Vssp_event(&notifyMsg) == -1) {
            REST_LOG_I( "[REST] jsonrpc_send_event_json: send fail" );
            return;
        }
        REST_LOG_I( "[REST] jsonrpc_send_event_json: send success" );
    } while (size != 0);

    return;
}
#endif
int jsonrpc_init(void)
{
    int i4_vssp_init = 0;
    vzlog::Log::log(vzlog::Log::LEVEL_ERROR, "JSONRPC", "enter jsonrpc_init \n");
    rest_ipc_init();
    i4_vssp_init = rest_init_vssp_uri();
    if(i4_vssp_init==0)
    {
    	DBG_LOG_PRINT(("rest_init_vssp_uri init done!\n"));
    }
    else
    {
	DBG_LOG_PRINT(("rest_init_vssp_uri init failed!\n"));
    }

    if (t_json_rpc_thread_descr.ui1_priority == DEFAULT_PRIORITY)
    {
        t_json_rpc_thread_descr.ui1_priority = REST_JSON_RPC_THREAD_PRIORITY;
    }

    if (t_json_rpc_thread_descr.ui2_num_msgs == DEFAULT_NUM_MSGS)
    {
        t_json_rpc_thread_descr.ui2_num_msgs = REST_JSON_RPC_THREAD_NUM_OF_MSGS;
    }

    if (t_json_rpc_thread_descr.z_stack_size == DEFAULT_STACK_SIZE)
    {
        t_json_rpc_thread_descr.z_stack_size = REST_JSON_RPC_THREAD_DEFAULT_STACK_SIZE;
    }

    int i4_ret = x_thread_create (&h_json_rpc_thread,
                      REST_JSON_RPC_THREAD_NAME,
                      t_json_rpc_thread_descr.z_stack_size,
                      t_json_rpc_thread_descr.ui1_priority,
                      rest_json_rpc_task_thread,
                      0,
                      NULL);

    if (i4_ret != OSR_OK)
    {
        DBG_LOG_PRINT(("[REST]rest_json_rpc_task_thread(fail) i4_ret[%d].\n",i4_ret));
	return i4_ret;
    }
    else
    {
        DBG_LOG_PRINT(("[REST]rest_json_rpc_task_thread(success) i4_ret[%d].\n",i4_ret));
    }

    i4_ret = x_thread_create (&vz_ipc_thread,
		    VIZIO_IPC_THREAD_NAME,
		    t_json_rpc_thread_descr.z_stack_size,
		    t_json_rpc_thread_descr.ui1_priority,
		    vz_ipc_task_thread,
		    0,
		    NULL);


    if (i4_ret != OSR_OK)
    {
	    DBG_LOG_PRINT(("[REST] vz_ipc_task_thread (fail) i4_ret[%d].\n",i4_ret));
    }
    else
    {
	    DBG_LOG_PRINT(("[REST] vz_ipc_task_thread (success) i4_ret[%d].\n",i4_ret));
    }

    /*startServer();*/

    return i4_ret;
}

int jsonrpc_deinit(void)
{
    g_run = 0;
    c_memset(&msg, 0, sizeof(REST_MSG_BUF));
    rest_send_msg_2_self(&msg);
    rest_ipc_destroy();

    /*stopServer() ;*/
    return 0;
}

int json_parse_hash_value(char* raw_data, char* hash_val)
{
    Json::Reader reader;
    Json::Value json_data;
    std::string data(raw_data);

    if(reader.parse(data, json_data) && json_data["ITEMS"] > 0 && json_data["ITEMS"][0].isMember("HASHVAL")) {
        snprintf(hash_val, 11, json_data["ITEMS"][0]["HASHVAL"].asString().c_str());
        return 0;
    }

    return -1;
}

int json_parse_paired_device_list(char* raw_data, unsigned int* device_list_size, REST_API_PAIRED_DEV_T* device_list)
{
    Json::Reader reader;
    Json::Value json_data;
    std::string data(raw_data);
    unsigned int num_of_paired_device = 0;

    if(reader.parse(data, json_data)) {
        num_of_paired_device = json_data["ITEMS"][0]["VALUE"].size();
        REST_LOG_I( "[json_parse_paired_device_list] the VALUE array size is %d\n\r" , num_of_paired_device );
        if(*device_list_size < num_of_paired_device){
            *device_list_size = num_of_paired_device;
            return -1;
        }

        if(*device_list_size > 0){
            for(unsigned int i = 0; i < json_data["ITEMS"][0]["VALUE"].size(); i++){
                REST_LOG_I( "[json_parse_paired_device_list] paired device [%d%s" , i , "]: ");
                REST_LOG_I( "DEVICE ID=%s\n\r", json_data["ITEMS"][0]["VALUE"][i]["DEVICE ID"].asString().c_str());
                REST_LOG_I( "DEVICE NAME=%s\n\r" , json_data["ITEMS"][0]["VALUE"][i]["DEVICE NAME"].asString().c_str() );
                c_strncpy(device_list[i].device_id, json_data["ITEMS"][0]["VALUE"][i]["DEVICE ID"].asString().c_str(), 50);
                device_list[i].device_id[49] = '\0';
                c_strncpy(device_list[i].device_name, json_data["ITEMS"][0]["VALUE"][i]["DEVICE NAME"].asString().c_str(), 25);
                device_list[i].device_name[24] = '\0';
            }
        }
        *device_list_size = num_of_paired_device;

    }

    return 0;
}

int json_parse_dlm_update_info(char* raw_data, REST_API_DLM_UPDATE_AVAILABLE_T* update_available)
{
    Json::Reader reader;
    Json::Value json_data;
    std::string data(raw_data);
    unsigned int ui_is_available = 0;
    unsigned int ui_update_lavel = 0;
    char c_version[50];

    if(reader.parse(data, json_data)) {
        ui_is_available = json_data["ITEM"]["VALUE"]["IS_AVAILABLE"].asInt();
        REST_LOG_I( "[json_parse_dlm_update_info] IS_AVAILABLE= %d\n\r" , ui_is_available );

        c_strncpy(c_version, json_data["ITEM"]["VALUE"]["VERSION"].asString().c_str(), 49);
        REST_LOG_I( "[json_parse_dlm_update_info] VERSION=%s\n\r" , json_data["ITEMS"]["VALUE"]["VERSION"].asString().c_str() );

        ui_update_lavel = json_data["ITEM"]["VALUE"]["UPDATE_LEVEL"].asInt();
        REST_LOG_I( "[json_parse_dlm_update_info] UPDATE_LEVEL= %d\n\r" , ui_update_lavel );
    }
    update_available->is_available = ui_is_available;
    update_available->update_level= ui_update_lavel;
    c_strncpy(update_available->version, c_version, 49);
    update_available->version[49] = '\0';

    return 0;
}

int json_parse_dlm_update_status(char* raw_data, REST_API_DLM_UPDATE_STATUS_T* update_status)
{
    Json::Reader reader;
    Json::Value json_data;
    std::string data(raw_data);
    unsigned int ui_status = 0;
    unsigned int ui_percent = 0;

    if(reader.parse(data, json_data)) {
        ui_status = json_data["ITEM"]["VALUE"]["STATUS"].asInt();
        REST_LOG_I( "[json_parse_dlm_update_status] STATUS= %d\n\r" , ui_status );

        ui_percent = json_data["ITEM"]["VALUE"]["PERCENT_COMPLETE"].asInt();
        REST_LOG_I( "[json_parse_dlm_update_status] PERCENT_COMPLETE= %d\n\r" , ui_percent );
    }
    update_status->status = ui_status;
    update_status->percent_complete = ui_percent;

    return 0;
}

int json_parse_binaries_version_info(char* raw_data, REST_API_BINARIES_VERSION_T* p_version)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);
    REST_LOG_I("raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data)) {
         Json::Value value = json_data["ITEM"]["VALUE"];
         c_strcpy(p_version->dai, value["DAI"].asString().c_str());
         c_strcpy(p_version->airplay, value["AIRPLAY"].asString().c_str());
         c_strcpy(p_version->cobalt, value["COBALT"].asString().c_str());
         c_strcpy(p_version->acr, value["ACR"].asString().c_str());
         c_strcpy(p_version->bluetooth, value["BLUETOOTH"].asString().c_str());
         c_strcpy(p_version->chromium, value["CHROMIUM"].asString().c_str());
         c_strcpy(p_version->conjure, value["CONJURE"].asString().c_str());
         c_strcpy(p_version->viziondk, value["VIZIONDK"].asString().c_str());
         c_strcpy(p_version->appletv, value["APPLETV"].asString().c_str());
         c_strcpy(p_version->hbomax, value["HBOMAX"].asString().c_str());
         c_strcpy(p_version->castcore, value["CASTCORE"].asString().c_str());
         REST_LOG_I("BINARIES VERSINO: dai = %s \n airplay = %s \n cobalt = %s \n acr = %s \n bluetooth = %s \n chromium = %s \n conjure = %s \n viziondk = %s \n appletv = %s \n hbomax = %s \n castcore = %s \n",
                p_version->dai,
                p_version->airplay,
                p_version->cobalt,
                p_version->acr,
                p_version->bluetooth,
                p_version->chromium,
                p_version->conjure,
                p_version->viziondk,
                p_version->appletv,
                p_version->hbomax,
                p_version->castcore);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}

int json_parse_adid_info(char* raw_data, REST_API_ADID_T* p_adid)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);
    REST_LOG_I("raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data)) {
         Json::Value value = json_data["ITEM"]["VALUE"];
         c_strcpy(p_adid->adid, value["IFA"].asString().c_str());
         c_strcpy(p_adid->adid_type, value["IFA_TYPE"].asString().c_str());
         p_adid->LMT = value["LMT"].asBool();
         REST_LOG_I("ADID: adid = %s \n adid_type = %s \n LMT = %s \n \n",
                p_adid->adid,
                p_adid->adid_type,
                p_adid->LMT ? "TURE" : "FALSE");
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}

int json_parse_device_info(char* raw_data, CHAR* p_version)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);

    REST_LOG_I("\n raw_data : %s,size:%d\n\r", raw_data,c_strlen(raw_data));

    if(reader.parse(data, json_data))
    {
        Json::Value value = json_data["ITEM"];
        c_strcpy(p_version, value["VALUE"].asString().c_str());
        REST_LOG_I("\nitem_value: %s, p_version : %s\n\r", value["VALUE"].asString().c_str(), p_version);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}

int json_parse_device_info_diid(char* raw_data, CHAR* p_diid)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);

    if(reader.parse(data, json_data))
    {
        Json::Value value = json_data["ITEMS"][0]["VALUE"]["SYSTEM_INFO"];
        c_strcpy(p_diid, value["DIID"].asString().c_str());
        REST_LOG_I("\n DIID : %s. --- \n\r", p_diid);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}

int json_parse_bt_remote_info(char* raw_data, REST_API_BT_REMOTE_INFO_T* remote_info)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);
    REST_LOG_I("raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data)) {
        Json::Value value = json_data["ITEM"]["VALUE"];
         c_strcpy(remote_info->battery_level, value["BATTERY_LEVEL"].asString().c_str());
         remote_info->remote_status= value["REMOTE_STATUS"].asInt() == 0 ? 2 : 1;
         c_strcpy(remote_info->model_number, value["MODEL_NUMBER"].asString().c_str());
         c_strcpy(remote_info->signal_strength, value["SIGNAL_STRENGTH"].asString().c_str());
         remote_info->device_type = value["DEVICE_TYPE"].asInt();
         remote_info->remote_mode= value["REMOTE_MODE"].asInt();
         c_strcpy(remote_info->name, value["NAME"].asString().c_str());
         remote_info->dongle_status = value["DONGLE_STATUS"].asInt();
         c_strcpy(remote_info->address, value["ADDRESS"].asString().c_str());
         c_strcpy(remote_info->serial_number, value["SERIAL_NUMBER"].asString().c_str());
         c_strcpy(remote_info->firmware_version, value["FIRMWARE_VERSION"].asString().c_str());

         REST_LOG_I("BT REMOTE INTO \n remote_status = %d \n device_type = %d \n remote_mode = %d \n dongle_status = %d \n battery_level = %s \n model_number = %s \n signal_strength = %s \n name = %s \n address = %s \n serial_number = %s \n firmware_version = %s \n",
            remote_info->remote_status,
            remote_info->device_type,
            remote_info->remote_mode,
            remote_info->dongle_status,
            remote_info->battery_level,
            remote_info->model_number,
            remote_info->signal_strength,
            remote_info->name,
            remote_info->address,
            remote_info->serial_number,
            remote_info->firmware_version);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}


//dolphin 20200909 parse return value to see whether the  geolocation whether correct
int json_parse_capability_geo_info(char* raw_data, char* p_geo_map_uri)
{
    int i4_ret = 0;
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);
    REST_LOG_I("raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data))
    {
        Json::Value value = json_data["ITEM"]["VALUE"];
        Json::Value json_geolocation = value["GeoLocation"];
        if(json_geolocation == NULL)
        {
             i4_ret = -1;
             REST_LOG_E("Geolocation not found!\n");
        }
        else
        {
            if(json_geolocation.isBool())
            {
                i4_ret = -1;
                REST_LOG_E("Geolocation should not be bool !\n");
            }
            else if(json_geolocation.isString())
            {
                c_strcpy(p_geo_map_uri,json_geolocation.asString().c_str());
                REST_LOG_I("Geolocation  = %s\n",p_geo_map_uri);
            }
            else
            {
                i4_ret = -1;
                REST_LOG_E("Geolocation unsuport type !\n");
            }
        }
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        i4_ret = -1;
    }

    return i4_ret;
}


int json_parse_capabilities_status(char* raw_data, bool* b_cs)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);
    // REST_LOG_I("raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data)) {
        Json::Value value = json_data["ITEMS"][0]["VALUE"];

        //REST_LOG_I("value : %s\n\r", value.toStyledString().c_str());
        *b_cs = value["CAPABILITIES"]["CS_TROUBLESHOOT_ENABLED"].asBool();
        REST_LOG_I("CS_TROUBLESHOOT_ENABLED = %d\n\r" , *b_cs);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}

int json_parse_airplay_enabled(char* raw_data, bool* b_is)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);
    // REST_LOG_I("raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data)) {
        Json::Value value = json_data["ITEMS"][0]["VALUE"];
        *b_is = value.asBool();
        REST_LOG_I("InputsSupported = %d\n\r" , *b_is);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}

int json_parse_consent_status(const char* raw_data, bool* b_accept)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);

    if(reader.parse(data, json_data))
    {
        Json::Value value = json_data["consentStatus"];
        *b_accept = value.asBool();
        REST_LOG_D("InputsSupported = %d\n\r" , *b_accept);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}


int json_parse_capabilities_boot_to_sc(char* raw_data, bool* b_is)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);
    // REST_LOG_I("raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data)) {
        Json::Value value = json_data["ITEMS"][0]["VALUE"];

        //REST_LOG_I("value : %s\n\r", value.toStyledString().c_str());
        *b_is = value["CAPABILITIES"]["BootToSC"].asBool();
        REST_LOG_I("BootToSC = %d\n\r" , *b_is);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        return -1;
    }

    return 0;
}

int json_parse_capability_geo_timezone(char* raw_data, REST_TIMZONE_T* p_geo_timezone)
{
    int i4_ret = 0;
    Json::Reader reader;
    Json::Value json_data;
    std::string data(raw_data);
    REST_LOG_E("\n\n raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data))
    {
        Json::Value value           = json_data["ITEM"]["VALUE"]["locationViews"][0];
        Json::Value json_city       = value["city"];
        Json::Value json_country    = value["country"];
        Json::Value json_longitude 	= value["longitude"];
        Json::Value json_latitude   = value["latitude"];
        Json::Value json_postalCode = value["postalCode"];
        Json::Value json_timeZone   = value["timeZone"];
        Json::Value json_dst        = value["dstOffset"];
        if(json_city == NULL || json_country == NULL ||
        json_longitude == NULL || json_latitude == NULL ||
        json_postalCode == NULL || json_timeZone == NULL )
        {
            REST_LOG_E("json reader.parse fail,please check format!!\n\r");
            i4_ret = -1;
        }
        if(json_dst != NULL)
        {
            p_geo_timezone->dstOffset = value["dstOffset"].asInt();
        }
        if(json_city != NULL && json_city.isString())
        {
            c_strncpy(p_geo_timezone->city,json_city.asString().c_str(),63);
            REST_LOG_E("json_city  = %s\n",json_city.asString().c_str());
        }
        if(json_country != NULL && json_country.isString())
        {
            c_strncpy(p_geo_timezone->country,json_country.asString().c_str(),63);
            REST_LOG_E("json_country  = %s\n",json_country.asString().c_str());
        }
        /*location*/
        if(json_longitude != NULL && json_latitude != NULL)
        {
            //c_strncpy(p_geo_timezone.city,json_city.asString().c_str(),63);
            //if(json_latitude.isDouble() && json_longitude.isDouble())
            {
                p_geo_timezone->latitude.location_val   = value["latitude"].asDouble();
                c_strncpy(p_geo_timezone->latitude.location_name,"latitude",c_strlen("latitude"));

                p_geo_timezone->longitude.location_val  = value["longitude"].asDouble();
                c_strncpy(p_geo_timezone->longitude.location_name,"longitude",c_strlen("longitude"));
            }
            //REST_LOG_I("json_city  = %s\n",json_city.asString().c_str());
        }
        if(json_postalCode != NULL && json_postalCode.isString())
        {
            c_strncpy(p_geo_timezone->postalCode,json_postalCode.asString().c_str(),63);
            REST_LOG_I("json_postalCode  = %s\n",json_postalCode.asString().c_str());
        }
        if(json_timeZone != NULL && json_timeZone.isString())
        {
            c_strncpy(p_geo_timezone->timeZone,json_timeZone.asString().c_str(),63);\
            REST_LOG_I("json_timeZone  = %s\n",json_timeZone.asString().c_str());
        }
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        i4_ret = -1;
    }

    return i4_ret;
}

int json_parse_headphones_status(char* raw_data, bool* b_cs)
{
    Json::Reader reader;
    Json::Value json_data;
    Json::Value value;
    std::string data(raw_data);
    // REST_LOG_I("raw_data : %s\n\r", raw_data);

    if(reader.parse(data, json_data)) {
        Json::Value value = json_data["ITEMS"][0]["VALUE"];

        //REST_LOG_I("value : %s\n\r", value.toStyledString().c_str());
        *b_cs = value["CAPABILITIES"]["BT_AUDIO_STREAMING"].asBool();
        REST_LOG_I("BTHeadphones Menu option = %d\n\r" , *b_cs);
        vzlog::Log::log(vzlog::Log::LEVEL_ERROR, "JSONRPC", "BTHeadphones Menu option = %d\n", *b_cs);
    }
    else
    {
        REST_LOG_E("json reader.parse fail\n\r");
        vzlog::Log::log(vzlog::Log::LEVEL_ERROR, "JSONRPC", "BTHeadphones Menu option reader.parse fail\n");
        return -1;
    }

    return 0;
}

int json_parse_session_token(char* raw_data, unsigned int session_token_size, char* session_token)
{
    /*
    {
      "STATUS": {
        "RESULT": "SUCCESS",
        "DETAIL": "Success"
      },
      "ITEM": {
        "SESSION": "Q4ovz4druc"
      }
    }
    */

    Json::Reader reader;
    Json::Value json_data;
    std::string data(raw_data);

    if(reader.parse(data, json_data)) {
        // {"STATUS":{"RESULT":"SUCCESS","DETAIL":"Success"},"ITEM":{"SESSION":"Qbmyvhsulk"}}
        //REST_LOG_I( "SESSION TOKEN 1=" << json_data["ITEM"].asString().c_str() );
        //REST_LOG_I( "SESSION TOKEN 2=" << json_data["ITEM"][0].asString().c_str() );
        //REST_LOG_I( "SESSION TOKEN 3=" << json_data["ITEM"][0]["VALUE"].asString().c_str() );
        //REST_LOG_I( "SESSION TOKEN 4=" << json_data["ITEM"][0]["VALUE"][0].asString().c_str() );
        //REST_LOG_I( "SESSION TOKEN 5=" << json_data["ITEM"][0]["VALUE"][0]["SESSION"].asString().c_str() );
        REST_LOG_I( "SESSION TOKEN 3=%s\n\r" , json_data["ITEM"]["SESSION"].asString().c_str() );
        c_strncpy(session_token, json_data["ITEM"]["SESSION"].asString().c_str(), session_token_size);
        session_token[session_token_size] = '\0';
        REST_LOG_I( "confirm SESSION TOKEN=%s\n\r" , session_token );
    }

    return 0;
}

int _json_parse_config_file(char* filepath, bool b_update_vtrl_ipt)
{
    IrCodeAssignments   infos = {0};
    TYPE_APP_INPUTs     vtrl_inputs = {0};

    Json::Reader reader;
    Json::Value json_data;

    std::stringstream sstr;
    std::ifstream in(filepath);
    if (!in) {
        REST_LOG_E( "[REST] open file failed: %s\n\r" , filepath );
        return -1;
    }
    sstr << in.rdbuf();
    std::string data = sstr.str();
    in.close();

    if (reader.parse(data, json_data))
    {
        //REST_LOG_I( "[REST] _json_parse_config_file" );
        //REST_LOG_I( json_data.toStyledString() );
        //REST_LOG_I( "[REST] -----------------------" );

        //std::stringstream ss;
        int x;
        std::string memberName;
        Json::Value value;

        Json::Value::Members members(json_data["IrCodeAssignments"].getMemberNames());
        REST_LOG_I( "members size:%d",members.size() );
        for (unsigned int i=0; i<members.size() && i<50; ++i)
        {
            memberName = members[i];
            value = json_data["IrCodeAssignments"][memberName];
            x = (int)strtol(memberName.c_str(), NULL, 16);
            //REST_LOG_I( "Key: " << memberName << ", " << x );
            infos.app[i].i4_keycode = x;
/*
typedef struct _IrCodeAssignment
{
    INT32   i4_keycode;
    UINT8   i1_name_space;
    UINT8   i1_app_id;
    CHAR    msg[1024];
}IrCodeAssignment;
*/
            //std::cout << "Value: " << value.toStyledString() << std::endl;

            infos.app[i].i4_name_space = std::stoi(value["NAME_SPACE"].asString(), NULL, 0);
            //std::cout << "NAME_SPACE-" << std::to_string((int)infos.app[i].i4_name_space) << std::endl;
            c_memset(infos.app[i].app_id, '\0', 16);
            c_strncpy(infos.app[i].app_id, value["APP_ID"].asString().c_str(), 15);
            //std::cout << "APP_ID-" << std::string((char*)infos.app[i].app_id) << std::endl;

            c_memset(infos.app[i].msg, 0, 1024);
            c_strncpy(infos.app[i].msg, value["MESSAGE"].asString().c_str(), 1023);
            int msg_size = value["MESSAGE"].asString().size();
            //std::cout << "MESSAGE-" << std::string((char*)infos.app[i].msg) << ", len=" << msg_size << std::endl;

            if (msg_size > 1023)
            {
                std::cout << "ERROR MESSAGE size is too big! SIZE-" << msg_size << std::endl;
            }
        }
        infos.num = members.size();

        if (b_update_vtrl_ipt)
        {
            Json::Value members_vtrl_inputs = json_data["VirtualInputs"];
            std::cout << "VirtualInputs size: " << members_vtrl_inputs.size() << std::endl;
            for (unsigned int i=0; i<members_vtrl_inputs.size() && i<8; ++i)
            {
                Json::Value vtrl_input;
                vtrl_input = members_vtrl_inputs[i]; // object
                //std::cout << "members_vtrl_inputs: " << vtrl_input.toStyledString() << std::endl;

                //std::cout << "HIDEABLE-" << vtrl_input["HIDEABLE"].asBool() << std::endl;
                vtrl_inputs.vtrl_inputs[i].vtrl_input.b_hideable = vtrl_input["HIDEABLE"].asBool();

                //std::cout << "CNAME-" << vtrl_input["CNAME"].asString() << std::endl;
                c_strncpy(vtrl_inputs.vtrl_inputs[i].vtrl_input.s_cname, vtrl_input["CNAME"].asString().c_str(), 24);

                //std::cout << "APP_ID-" << vtrl_input["APP_ID"].toStyledString() << std::endl;
                c_strncpy(vtrl_inputs.vtrl_inputs[i].app.msg, vtrl_input["APP_ID"]["MESSAGE"].asString().c_str(), 1024);

                c_strncpy(vtrl_inputs.vtrl_inputs[i].app.app_id, vtrl_input["APP_ID"]["APP_ID"].asString().c_str(), 16);
                //std::cout << "NAME_SPACE-" << vtrl_input["APP_ID"]["NAME_SPACE"].toStyledString() << std::endl;
                vtrl_inputs.vtrl_inputs[i].app.i4_name_space = vtrl_input["APP_ID"]["NAME_SPACE"].asInt();

                /* Look whether there is an APP_IDS member and save its APP_ID children */
                if(vtrl_input.isMember("APP_IDS")==true)
               {
                    Json::Value app_ids = vtrl_input["APP_IDS"];
                    for(unsigned int j=0;j<app_ids.size() && j<5;j++)  //we suppose max 5 app_id in one app_ids member
                    {
                         Json::Value app_ids_member=app_ids[j]; //APP_IDS its member
                         c_strncpy(vtrl_inputs.vtrl_inputs[i].app.app_ids[j], app_ids_member["APP_ID"].asString().c_str(), 16);
                         vtrl_inputs.vtrl_inputs[i].app.i4_name_spaces[j] = app_ids_member["NAME_SPACE"].asInt();
                         vtrl_inputs.vtrl_inputs[i].app.app_ids_num++;
                    }
               }

                //std::cout << "AFTER_CNAME-" << vtrl_input["AFTER_CNAME"].asString() << std::endl;
                c_strncpy(vtrl_inputs.vtrl_inputs[i].vtrl_input.s_position_after, vtrl_input["AFTER_CNAME"].asString().c_str(), 24);

                //std::cout << "NAMES-" << vtrl_input["NAMES"].toStyledString() << std::endl;
                c_strncpy(vtrl_inputs.vtrl_inputs[i].vtrl_input.s_name_en[0], vtrl_input["NAMES"]["en"].asString().c_str(), 24);
                c_strncpy(vtrl_inputs.vtrl_inputs[i].vtrl_input.s_name_en[1], vtrl_input["NAMES"]["es"].asString().c_str(), 24);
                c_strncpy(vtrl_inputs.vtrl_inputs[i].vtrl_input.s_name_en[2], vtrl_input["NAMES"]["fr"].asString().c_str(), 24);

                c_strncpy(vtrl_inputs.vtrl_inputs[i].vtrl_input.launch_msg, vtrl_input["LAUNCH_APP_ID"]["MESSAGE"].asString().c_str(), 1024);
                c_strncpy(vtrl_inputs.vtrl_inputs[i].vtrl_input.launch_app_id, vtrl_input["LAUNCH_APP_ID"]["APP_ID"].asString().c_str(), 16);
                //std::cout << "NAME_SPACE-" << vtrl_input["LAUNCH_APP_ID"]["NAME_SPACE"].toStyledString() << std::endl;
                vtrl_inputs.vtrl_inputs[i].vtrl_input.i4_launch_name_space = vtrl_input["LAUNCH_APP_ID"]["NAME_SPACE"].asInt();
            }
            vtrl_inputs.num = members_vtrl_inputs.size();
        }
    }

    if (b_update_vtrl_ipt) {
        return _rest_app_set_ir_code_assignment_table(&infos, &vtrl_inputs);
    } else {
        return _rest_app_set_ir_code_assignment_table(&infos, NULL);
    }
}

int _json_parse_ssdp_udn_file(char* in_filepath, char* out_filepath)
{
    Json::Reader reader;
    Json::Value json_data;

    REST_LOG_I("open file: %s, %s\n\r" , in_filepath, out_filepath);

    std::stringstream sstr;
    std::ifstream in(in_filepath);
    if (!in) {
        REST_LOG_E( "open file failed: %s\n\r" , in_filepath);
        return -1;
    }
    sstr << in.rdbuf();
    std::string data = sstr.str();
    in.close();

    REST_LOG_I( "open file:\n\r" );

    if (reader.parse(data, json_data))
    {
        std::cout << "ssdp-udn" << json_data["ssdp-udn"].asString() << std::endl;
        if (!json_data["ssdp-udn"].asString().empty())
        {
            std::ofstream out(out_filepath);
            if (!out) {
                REST_LOG_E("open file failed: %s\n\r" , out_filepath);
                return -1;
            }
            out << json_data["ssdp-udn"].asString();
            out.close();
        }
        else
        {
            REST_LOG_E("no ssdp udn in: %s\n\r" , in_filepath);
            return -1;
        }
    }
    return 0;
}

#ifdef __cplusplus
}
#endif
