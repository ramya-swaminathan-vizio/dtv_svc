#include <stdio.h> //printf
#include <string.h>
#include <stdlib.h> //exit(0);
#include <unistd.h>
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <poll.h>
#include "cJSON.h"

#include "handler.h"
#include "common.h"
#include "argument.h"
#include "rest.h"

#include "app.h"
#include "airplay.h"
#include "homekit.h"

#ifdef __cplusplus
extern "C" {
#include "c_os.h"
#include "x_os.h"
#include "rest_util.h"
#include "rest/a_jsonrpc.h"
#include "rest/a_rest_event.h"
#include "nav/input_src/a_input_src.h"
#include "app_util/a_cfg.h"
#include "app_util/config/a_cfg_custom.h"
}
#endif

#define BUFLEN 40960
#define IPC_SOCKET_PATH "/tmp/semaphore_ipc"

struct AirplayGroupURI {
    std::string index[URI_INDEX_SIZE];
};
extern int airplay_create_status;

AirplayGroupURI airplayGroupURIs[] = {
	{ "property" },
    { "action" },
	{ "" },
};

void _airplay_send_msg_to_airplay_die(const char *s)
{
    perror(s);
    REST_LOG_E("Error %s\n\r", s);
    //exit(1);
}

int _airplay_send_msg_to_airplay_send_ipc(char* message, char* res, int res_buf_len)
{
    struct sockaddr_un si_other;
    int s;
    //int slen=sizeof(si_other);
    char buf[BUFLEN];

    if ((s=socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        _airplay_send_msg_to_airplay_die(std::string("socket").c_str());
        return -1;
    }

    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sun_family = AF_UNIX;
    strncpy(si_other.sun_path, IPC_SOCKET_PATH, sizeof(si_other.sun_path)-1);
	if (connect(s, (struct sockaddr *)&si_other, sizeof(struct sockaddr_un)) < 0) {
		_airplay_send_msg_to_airplay_die(std::string("connect").c_str());
        close(s);
        return -1;
	}

    // send the message
    //printf("Send:\n%s\n", message);
    if (write(s, message, strlen(message)) == -1) {
        _airplay_send_msg_to_airplay_die(std::string("sendto()").c_str());
        close(s);
        return -1;
    }

    // receive a reply and print it
    // clear the buffer by filling null, it might have previously received data
    memset(buf, '\0', BUFLEN);

    // try to receive some data, this is a blocking call
    // TODO: modify it to be allow timeout. i.e. poll()
    /*
    struct pollfd ufds[1];
    int nfds = 1;
    ufds[0].events = POLLIN;
    ufds[0].fd = s;
    int r = 0;
    r = poll(ufds, nfds, 3000);
    if(r<=0)
    {
        REST_LOG_I("semaphore_ipc cann't read.send to airplay fail,\n\r");
    }else
    {
        REST_LOG_I("semaphore_ipc poll success \n\r");
        if(ufds[0].revents & POLLIN)
        {
                REST_LOG_I("semaphore_ipc can read.\n\r");
                if (read(s, buf, BUFLEN) == -1) {
                    _airplay_send_msg_to_airplay_die(std::string("recvfrom()").c_str());
                    close(s);
                    return -1;
                }
                //printf("Recv:\n%s\n", buf);
                REST_LOG_I("Recv %s.\n\r", buf);

                c_strncpy(res, buf, res_buf_len);
        }
     }
    */
	//dolphin use select instead of poll

    fd_set readfds;
	INT32 maxfdp = -1;
	INT32 i4_ret  = 0;
	struct timeval t_airplay_timeout;

	FD_ZERO(&readfds);
    FD_SET(s, &readfds);
    maxfdp = s;

    /* 3 sec */
    t_airplay_timeout.tv_sec   = 3;
    t_airplay_timeout.tv_usec = 0;

	i4_ret = select(maxfdp+1, &readfds, NULL, NULL, &t_airplay_timeout);
	if(i4_ret<=0)
	{
		REST_LOG_E("<airplay> dolphin semaphore_ipc cann't read.send to airplay fail,\n\r");
	}
	else
	{
		REST_LOG_I("<airplay> semaphore_ipc select success \n\r");
		if(FD_ISSET(s, &readfds))
		{
				REST_LOG_I("<airplay> semaphore_ipc can read.\n\r");
				if (read(s, buf, BUFLEN) == -1) {
					_airplay_send_msg_to_airplay_die(std::string("recvfrom()").c_str());
					close(s);
					return -1;
				}
				//printf("Recv:\n%s\n", buf);
				REST_LOG_I("<airplay> dolphin Recv %s.\n\r", buf);

                c_strncpy(res, buf, res_buf_len);
        }
     }


    close(s);

    return 0;
}

/*
1: AirPlayReceiverServerSetProperty
2: AirPlayReceiverServerCopyProperty
3: AirPlayReceiverServerControl
4: AirPlayReceiverServerControlAsync
*/
int _airplay_send_msg_to_airplay(int i_cmd_type, const char* prop, char* res, int res_buf_len, int type, int int_val, const char* str_val, bool bool_val)
{
    char *message;
    cJSON *root, *ipc, *param, *params, *ctrl_param, *ctrl_param_2;

    root = cJSON_CreateObject();
    switch (i_cmd_type)
    {
        case 1: // AirPlayReceiverServerSetProperty
        {
            cJSON_AddItemToObject(root, "ipc", ipc = cJSON_CreateObject());
            cJSON_AddStringToObject(ipc, "command", "AirPlayReceiverServerSetProperty");
            cJSON_AddItemToObject(ipc, "property_param", param = cJSON_CreateObject());
            cJSON_AddStringToObject(param, "key", prop);

            switch (type) // ["string", "boolean", "integer"]
            {
                case 0:
                    cJSON_AddStringToObject(param, "type", "string");
                    cJSON_AddStringToObject(param, "value", str_val);
                    break;
                case 1:
                    cJSON_AddStringToObject(param, "type", "boolean");
                    if (bool_val) {
                        cJSON_AddTrueToObject(param, "value");
                    } else {
                        cJSON_AddFalseToObject(param, "value");
                    }
                    break;
                case 2:
                    cJSON_AddStringToObject(param, "type", "integer");
                    cJSON_AddNumberToObject(param, "value", int_val);
                    break;
                default:
                    break;
            }

            break;
        }
        case 2: // AirPlayReceiverServerCopyProperty
        {
            cJSON_AddItemToObject(root, "ipc", ipc = cJSON_CreateObject());
            cJSON_AddStringToObject(ipc, "command", "AirPlayReceiverServerCopyProperty");
            cJSON_AddItemToObject(ipc, "property_param", param = cJSON_CreateObject());
            cJSON_AddStringToObject(param, "key", prop);
            break;
        }
        case 3: // AirPlayReceiverServerControl
        {
            cJSON_AddItemToObject(root, "ipc", ipc = cJSON_CreateObject());
            cJSON_AddStringToObject(ipc, "command", "AirPlayReceiverServerControl");
            cJSON_AddItemToObject(ipc, "ctrl_param", ctrl_param = cJSON_CreateObject());
            cJSON_AddStringToObject(ctrl_param, "key", "devicePowerStateWillChange");
            cJSON_AddItemToObject(ctrl_param, "params", params = cJSON_CreateArray());
            cJSON_AddItemToArray(params, ctrl_param_2 = cJSON_CreateObject());
            cJSON_AddStringToObject(ctrl_param_2, "key", prop);
            cJSON_AddStringToObject(ctrl_param_2, "type", "integer");
            cJSON_AddNumberToObject(ctrl_param_2, "value", int_val);
            break;
        }
        case 4: // AirPlayReceiverServerControlAsync
        {
            cJSON_AddItemToObject(root, "ipc", ipc = cJSON_CreateObject());
            cJSON_AddStringToObject(ipc, "command", "AirPlayReceiverServerControlAsync");
            cJSON_AddItemToObject(ipc, "ctrl_param", ctrl_param = cJSON_CreateObject());

            if (c_strcmp(prop, "remoteControlKeyPressed") == 0) {
                cJSON_AddStringToObject(ctrl_param, "key", str_val);
            } else if (c_strcmp(prop, "nameChanged") == 0) {
                cJSON_AddStringToObject(ctrl_param, "key", prop);
                cJSON_AddItemToObject(ctrl_param, "params", params = cJSON_CreateArray());
                cJSON_AddItemToArray(params, ctrl_param_2 = cJSON_CreateObject());
                cJSON_AddStringToObject(ctrl_param_2, "key", "name");
                cJSON_AddStringToObject(ctrl_param_2, "type", "string");
                cJSON_AddStringToObject(ctrl_param_2, "value", str_val);
            }

            break;
        }
        case 5: // AirPlayReceiverServerControlAsync
        {
            REST_LOG_I("Sending show/hide static resource, type; %d\n\r", type);
            cJSON_AddItemToObject(root, "ipc", ipc = cJSON_CreateObject());
            cJSON_AddStringToObject(ipc, "command", "AirPlayReceiverServerControlAsync");
            cJSON_AddItemToObject(ipc, "ctrl_param", param = cJSON_CreateObject());
            switch (type)
            {
                case 0:
                    cJSON_AddStringToObject(param, "key", "hideResourceOnDisplay");
                    cJSON_AddItemToObject(param, "params", params = cJSON_CreateArray());
                    cJSON_AddItemToArray(params, ctrl_param = cJSON_CreateObject());
                    cJSON_AddStringToObject(ctrl_param, "key", "path");
                    cJSON_AddStringToObject(ctrl_param, "type", "string");
                    cJSON_AddStringToObject(ctrl_param, "value", "LoadingScreen/AirPlayDefaultImage.png");
                    break;
                case 1:
                    cJSON_AddStringToObject(param, "key", "showResourceOnDisplay");
                    cJSON_AddItemToObject(param, "params", params = cJSON_CreateArray());
                    cJSON_AddItemToArray(params, ctrl_param = cJSON_CreateObject());
                    cJSON_AddStringToObject(ctrl_param, "key", "path");
                    cJSON_AddStringToObject(ctrl_param, "type", "string");
                    cJSON_AddStringToObject(ctrl_param, "value", "LoadingScreen/AirPlayDefaultImage.png");
                    cJSON_AddItemToArray(params, ctrl_param = cJSON_CreateObject());
                    cJSON_AddStringToObject(ctrl_param, "key", "mimeType");
                    cJSON_AddStringToObject(ctrl_param, "type", "string");
                    cJSON_AddStringToObject(ctrl_param, "value", "image/png");
                    cJSON_AddItemToArray(params, ctrl_param = cJSON_CreateObject());
                    cJSON_AddStringToObject(ctrl_param, "key", "presentationType");
                    cJSON_AddStringToObject(ctrl_param, "type", "int");
                    cJSON_AddNumberToObject(ctrl_param, "value", 0);
                    break;
                 case 2:
                    cJSON_AddStringToObject(param, "key", "bringAirPlayToForeground");
                    cJSON_AddItemToObject(param, "params", params = cJSON_CreateArray());
                    cJSON_AddItemToArray(params, ctrl_param = cJSON_CreateObject());
                    cJSON_AddStringToObject(ctrl_param, "key", "bringAirPlayToForegroundReason");
                    cJSON_AddStringToObject(ctrl_param, "type", "string");
                    cJSON_AddStringToObject(ctrl_param, "value", str_val);
                    break;
                case 3:
                    cJSON_AddStringToObject(param, "key", "willSendAirPlayToBackground");
                    cJSON_AddItemToObject(param, "params", params = cJSON_CreateArray());
                    cJSON_AddItemToArray(params, ctrl_param = cJSON_CreateObject());
                    cJSON_AddStringToObject(ctrl_param, "key", "reasonCode");
                    cJSON_AddStringToObject(ctrl_param, "type", "integer");
                    cJSON_AddNumberToObject(ctrl_param, "value", int_val);
                    break;
                case 4:
                    cJSON_AddStringToObject(param, "key", "showSettings");
                    cJSON_AddItemToObject(param, "params", params = cJSON_CreateArray());
                    cJSON_AddItemToArray(params, ctrl_param = cJSON_CreateObject());
                    cJSON_AddStringToObject(ctrl_param, "key", "type");
                    cJSON_AddStringToObject(ctrl_param, "type", "integer");
                    cJSON_AddNumberToObject(ctrl_param, "value", int_val);
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            cJSON_Delete(root);
            return 0;
    }

    message = cJSON_Print(root);
    REST_LOG_I("Sending %s\n\r", message);
    if( _airplay_send_msg_to_airplay_send_ipc(message, res, res_buf_len)!=0)
    {
            free(message);
            cJSON_Delete(root);
            return -1;
    }
    free(message);
    cJSON_Delete(root);

    if (c_strlen(res) <= 0) {
        REST_LOG_I("No response string.\n\r");
        return 0;
    }

    return 0;
}

int _airplay_notify_to_airplay(const char* ps_event, int int_value, const char* str_val)
{
    DBG_LOG_PRINT(("Enter. int_value=%d, str_val=%s.\n\r", int_value, str_val));

    char res_buf[BUFLEN] = {0};
    c_memset(res_buf, 0, BUFLEN);
    static int current_status = -1;

    /*
        VIZIO Python
            Utils.enum('ACTIVE_STANDBY', 'ON', 'OFF')
        Apple AirPlay
            #define kAirPlayDevicePowerState_Off 0 // Device is powered off
            #define kAirPlayDevicePowerState_ActiveStandby 1 // Device display, speaker are off, network stack and processor are active
            #define kAirPlayDevicePowerState_On 2 // Device is powered on
    */
    int i;
    if (c_strcmp(ps_event, "power_status") == 0)
    {
        if (current_status == int_value)
        {
            DBG_LOG_PRINT(("same state, skip\r\n"));
            return 0;
        }
        current_status = int_value;
        switch (int_value)
        {
            case 0:
                i = 1;
                break;
            case 1:
                i = 2;
                break;
            case 2:
                i = 0;
                break;
            case 3:  //dolpin add when receive 3 need send semapore
                i=0;
                break;
            default:
                return -1;
        }
        _airplay_send_msg_to_airplay(3, "devicePowerState", res_buf, BUFLEN-1, /*type*/ 2, i, NULL, TRUE);

    }
    else if (c_strcmp(ps_event, "device_name") == 0)
    {
        _airplay_send_msg_to_airplay(4, "nameChanged", res_buf, BUFLEN-1, /*type*/ 0, i, str_val, TRUE);
    }
    else if (c_strcmp(ps_event, "ShowResource") == 0)
    {
        switch (int_value)
        {
            case 0:
                _airplay_send_msg_to_airplay(5, "ShowResource", res_buf, BUFLEN-1, /*type*/ 0, i, str_val, TRUE);
                break;
            case 1:
                _airplay_send_msg_to_airplay(5, "ShowResource", res_buf, BUFLEN-1, /*type*/ 1, i, str_val, TRUE);
                break;
            default:
                return -1;
        }
    }

    return 0;
}

/*
Type.AIRPLAY_PROP_V1
{
    "PROPERTY": <airplay string property name>,
    "TYPE": <REST Enum.DATA_TYPE>,
    "VALUE": <value>
}
Enum.DATA_TYPE = {STRING, NUMBER, BOOLEAN, DICT}
*/
int save_hkAccessControlLevel;
char save_Password[64];
int save_property_key_RequireCode;
int property(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    char res_buf[BUFLEN] = {0};
    c_memset(res_buf, 0, BUFLEN);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");

            Json::Value airplay_prop;
            Json::Value value;
            char prop[128] = {0};
            char* p_prop;
            airplay_prop = root["airplay_prop"];
            if(airplay_prop.asString().empty())
            {
                REST_LOG_E("airplay_prop of root is empty.");
                airplay_prop = root["query"];
            }
            REST_LOG_I("airplay_prop:%s.\n\r", airplay_prop.asString().c_str());
            c_memset(prop, 0, 128);
            c_strncpy(prop, airplay_prop.asString().c_str(), 127);
            if (c_strncmp(prop, "prop=", 5) == 0) {
                p_prop = prop+5;
            } else {
                p_prop = prop;
            }

            _airplay_send_msg_to_airplay(2, std::string(p_prop).c_str(), res_buf, BUFLEN-1, -1, 0, NULL, TRUE);

            /*
            res_buf:
            {
                "result":
                {
                    "status":"SUCCESS",
                    "value":
                    {
                        "key":"AirPlayEnabled",
                        "type":"boolean",
                        "value":true
                    }
                }
            }
            */
            if (c_strstr(res_buf, "SUCCESS") == NULL) {
                REST_LOG_E("Request to airplay failed.\n\r");
                return -1;
            }

            cJSON *root_res, *j_result, *j_value, *j_key, *j_type, *j_value_value;
            root_res = cJSON_Parse(res_buf);
            if (root_res == NULL) {
                REST_LOG_E("Parse response failed.\n\r");
                return -1;
            }
            j_result = cJSON_GetObjectItem(root_res, "result");
            if (j_result == NULL) {
                REST_LOG_E("Parse j_result failed.\n\r");
                cJSON_Delete(root_res);
                return -1;
            }
            j_value = cJSON_GetObjectItem(j_result, "value");
            if (j_value == NULL) {
                REST_LOG_E("Parse j_value failed.\n\r");
                if (c_strcmp(p_prop, "Password") != 0) {
                    cJSON_Delete(root_res);
                    return -1;
                } else {
                    REST_LOG_I("It's ok for Password query.\n\r");
#if 0
                    value["PROPERTY"] = "Password";
                    value["TYPE"] = 0;
                    value["VALUE"] = "Hello";
                    response["VALUE"] = value;
#else
                    //response["VALUE"] = Json::Value::null;
                    response["VALUE"] = "";
                    //response["VALUE"] = "Hello";
#endif
                    cJSON_Delete(root_res);
                    break;
                }
            }

            j_key = cJSON_GetObjectItem(j_value, "key");
            if (j_key == NULL) {
                REST_LOG_E("Parse j_key failed.\n\r");
                cJSON_Delete(root_res);
                return -1;
            }
            j_type = cJSON_GetObjectItem(j_value, "type");
            if (j_type == NULL) {
                REST_LOG_E("Parse j_type failed.\n\r");
                cJSON_Delete(root_res);
                return -1;
            }
            j_value_value = cJSON_GetObjectItem(j_value, "value");
            if (j_type == NULL) {
                REST_LOG_E("Parse j_value_value failed.\n\r");
                cJSON_Delete(root_res);
                return -1;
            }

            if (c_strcmp(j_key->valuestring, p_prop) != 0) {
                REST_LOG_E("key is %s, but expect %s.\n\r", j_key->valuestring, p_prop);
                cJSON_Delete(root_res);
                return -1;
            }

            /*
            /airplay/property?prop=userSettingsModel
            Returns Type.AIRPLAY_PROP_V1 object
            {
                "PROPERTY": "userSettingsModel",
                "TYPE": 3, // Enum.DATA_TYPE = {STRING, NUMBER, BOOLEAN, DICT}
                "VALUE": "AirPlaySettings_v1-Accessory-Not-In-Home.json"
            */
            /* ["string", "boolean", "number"] */
#if 0
            value["PROPERTY"] = std::string(j_key->valuestring);
            if (c_strcmp(j_type->valuestring, "boolean") == 0) {
                value["TYPE"] = 2;
                value["VALUE"] = j_value_value->valueint == 1 ? (bool)TRUE : (bool)FALSE;
            } else if (c_strcmp(j_type->valuestring, "string") == 0) { // Passwork is string also
                value["TYPE"] = 0;
                value["VALUE"] = std::string(j_value_value->valuestring);
            } else if (c_strcmp(j_type->valuestring, "integer") == 0) {
                value["TYPE"] = 1;
                value["VALUE"] = j_value_value->valueint;
            }
            response["VALUE"] = value;
#else
            if (c_strcmp(j_type->valuestring, "boolean") == 0) {
                response["VALUE"] = j_value_value->valueint == 1 ? (bool)TRUE : (bool)FALSE;
            } else if (c_strcmp(j_type->valuestring, "string") == 0) { // Password is string also
#if 0
                if (c_strcmp(p_prop, "Password") == 0)
                    response["VALUE"] = "Hello";
                else
#endif
                response["VALUE"] = std::string(j_value_value->valuestring);
            } else if (c_strcmp(j_type->valuestring, "integer") == 0) {
                response["VALUE"] = j_value_value->valueint;
            }
#endif
            /* if it's privilege or password, save it */
            if (c_strcmp(j_key->valuestring, "hkAccessControlLevel") == 0) {
                REST_LOG_I("key %s is %d\n\r", j_key->valuestring, j_value_value->valueint);
                save_hkAccessControlLevel = j_value_value->valueint;
            }
            if (c_strcmp(j_key->valuestring, "Password") == 0) {
                REST_LOG_I("key %s is %s\n\r", j_key->valuestring, j_value_value->valuestring);
                c_memset(save_Password, 0, 64);
                c_strncpy(save_Password, j_value_value->valuestring, 63);
            }
            if (c_strcmp(j_key->valuestring, "property_key_RequireCode") == 0) {
                REST_LOG_I("key %s is %d\n\r", j_key->valuestring, j_value_value->valueint);
                save_property_key_RequireCode = j_value_value->valueint;
            }

            cJSON_Delete(root_res);

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            Json::Value msg;
            Json::Value value;
            Json::Value property;
            Json::Value type;
            Json::Value value_value;

            msg = root["message"];
            value = msg["VALUE"];
            property = value["PROPERTY"];
            REST_LOG_I("PROPERTY: %s.\n\r", property.asString().c_str());
            type = value["TYPE"];
            REST_LOG_I("TYPE: %d.\n\r", type.asInt());
            value_value = value["VALUE"];

            AirplayPropertyNotofication nf;
            switch(type.asInt())
            {
                case 0: // string
                    REST_LOG_I("VALUE: %s.\n\r", value_value.asString().c_str());
                    _airplay_send_msg_to_airplay(1, property.asString().c_str(), res_buf, BUFLEN-1, /*type*/ 0, 0, value_value.asString().c_str(), TRUE); // ["string", "boolean", "integer"]
                    if (c_strcmp(property.asString().c_str(), "Password") == 0) {
                        REST_LOG_I("key %s is %s. previous is %s\n\r", property.asString().c_str(), value_value.asString().c_str(), save_Password);
                        if (c_strstr(res_buf, "SUCCESS") != NULL && c_strcmp(value_value.asString().c_str(), save_Password) != 0) {
                            /*
                            "URI": "airplay/property",
                            "VALUE": {"PROPERTY": "hkAccessControlLevel", "TYPE": 1, "VALUE": 1}
                            */
                            c_memset(nf.propety, 0, 64);
                            c_strcpy(nf.propety, "Password");
                            nf.type = 0;
                            c_memset(nf.value_string, 0, 64);
                            c_strncpy(nf.value_string, value_value.asString().c_str(), 63);
                            rest_event_notify_ex("airplay/property", (void*)&nf);
                        }
                    }
                    break;
                case 1: // num
                    REST_LOG_I("VALUE: %d.\n\r", value_value.asInt());
                    _airplay_send_msg_to_airplay(1, property.asString().c_str(), res_buf, BUFLEN-1, /*type*/ 2, value_value.asInt(), NULL, TRUE);
                    if (c_strcmp(property.asString().c_str(), "hkAccessControlLevel") == 0) {
                        REST_LOG_I("key %s is %d. previous is %d\n\r", property.asString().c_str(), value_value.asInt(), save_hkAccessControlLevel);
                        if (c_strstr(res_buf, "SUCCESS") != NULL && value_value.asInt() != save_hkAccessControlLevel) {
                            c_memset(nf.propety, 0, 64);
                            c_strcpy(nf.propety, "hkAccessControlLevel");
                            nf.type = 1;
                            nf.value_int = 1;
                            rest_event_notify_ex("airplay/property", (void*)&nf);
                        }
                    }
                    if (c_strcmp(property.asString().c_str(), "property_key_RequireCode") == 0) {
                        REST_LOG_I("key %s is %d. previous is %d\n\r", property.asString().c_str(), value_value.asInt(), save_property_key_RequireCode);
                        REST_LOG_I("res_buf = %s\n",res_buf);
                        if (c_strstr(res_buf, "SUCCESS") != NULL && value_value.asInt() != save_property_key_RequireCode) {
                            c_memset(nf.propety, 0, 64);
                            c_strcpy(nf.propety, "property_key_RequireCode");
                            nf.type = 1;
                            nf.value_int = value_value.asInt();
                            save_property_key_RequireCode = nf.value_int;
                            rest_event_notify_ex("airplay/property", (void*)&nf);
                        }else
                         {
                             return -1;
                         }
                    }
                    break;
                case 2: // bool
                    REST_LOG_I("VALUE: %d.\n\r", value_value.asInt());
                    _airplay_send_msg_to_airplay(1, property.asString().c_str(), res_buf, BUFLEN-1, /*type*/ 1, 0, NULL, value_value.asInt() == 1 ? TRUE : FALSE);
                    if (c_strcmp(property.asString().c_str(), "AirPlayEnabled") == 0) {
                               if(value_value.asInt() == 1)
                                {
                                    UINT8 airplay_disenable = 0;
                                    acfg_set(IDX_CUSTOM_AIRPLAY_STATE_CTRL, &airplay_disenable, 1);
                                     //_json_parse_config_file((char*)"/3rd_rw/sc-data/config/sc-config.json", TRUE);
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
                                }else{
                                     UINT8 airplay_disenable = 1;
                                    acfg_set(IDX_CUSTOM_AIRPLAY_STATE_CTRL, &airplay_disenable, 1);
                                    _rest_app_create_virtual_inputs();
                                    airplay_create_status = 1;//ac-config include airplay source,but airplay not installed.
                                    //a_nav_ipts_delete_virtual_input((CHAR *) "airplay");
                                }
                        }
                    break;
                case 3: // dict
                    REST_LOG_E("Not support dict type.\n\r", type.asInt());
                    break;
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

int action(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;
    type = get_type(root);

    char res_buf[BUFLEN] = {0};
    c_memset(res_buf, 0, BUFLEN);
    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET.\n\r");
            REST_LOG_I("Not implement.\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");

            Json::Value msg;
            Json::Value value;
            Json::Value cmd;

            msg = root["message"];
            value = msg["VALUE"];
            cmd = value["COMMAND"];
            REST_LOG_I("COMMAND: %s.\n\r", cmd.asString().c_str());

            if (c_strcmp(cmd.asString().c_str(), "command_key_ShowDiagnosticsAndUsageLog") == 0) {
                _airplay_send_msg_to_airplay(4, "remoteControlKeyPressed", res_buf, BUFLEN-1, -1, 0, cmd.asString().c_str(), TRUE);
            }

            break;
        }
        default:
            break;
    }

	return 0;
}

handler airplay_handler[] = {
    property,
    action,
};


