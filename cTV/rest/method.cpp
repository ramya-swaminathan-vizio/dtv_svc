#include <iostream>


#include "handler.h"
#include "common.h"
#include "rest_event_api.h"
#include "rest_api_variables.h"
#include "method.h"

#include "tv_settings.h"
#include "state.h"
#include "pairing.h"
#include "oobe.h"
#include "uli.h"
#include "pin.h"
#include "system.h"
#include "key_command.h"
#include "events.h"
#include "app.h"
#include "server.h"
#include "airplay.h"
#include "homekit.h"
#include "system_menu.h"


namespace method {
    bool Method::method(const Json::Value &root, Json::Value &response) {
        REST_LOG_I("Enter\n\r");

        Json::FastWriter writer;
        Json::Value j_root=root;

        int id = j_root["id"].asInt();
        std::string uri = j_root["uri"].asString();
        Json::Value mess = j_root["message"];
        std::string message;
        if(!mess.isNull()) {
            message= writer.write(mess);
        }

        REST_LOG_I("id: %d\n\r", id);
        REST_LOG_I("uri: %s\n\r", uri.c_str());
        REST_LOG_I("message: %s\n\r", message.c_str());

        /*cJSON * agument = cJSON_Parse(message.c_str());
        cJSON * resp = cJSON_CreateObject();*/

        int ret = 0;
        int channel_n = -1;
        int i4_offset = -1;
        Json::Value result;

        response["jsonrpc"] = "2.0";
        response["uri"] = uri;
        response["id"] = id;

        if (c_strstr(uri.c_str(), "acr") == NULL
            && c_strstr(uri.c_str(), "tv_settings/system/timers/blank_screen") == NULL
            && c_strstr(uri.c_str(), "app/tts/play") == NULL)
        {
            tv_settings_exit_blank_screen((Json::Value &)j_root, result);
        }

        i4_offset = rest_search_uri(uri,&channel_n);
        j_root["N"]=channel_n;  //parse N channel
        if(i4_offset != -1)
        {
           //REST_LOG_E("%s succeed ,offset %d\n",uri.c_str(),i4_offset);
           ret = rest_init_offset_handler(i4_offset,(Json::Value &)j_root, result);
        }
        else
        {
            ret = -1;
            REST_LOG_E("%s failded\n",uri.c_str());
        }
        result["SUCCESS"] = ret;

        REST_LOG_I("result: %s\n\r", (writer.write(result)).c_str());
        response["result"] = result;

        return true;
    }
};
