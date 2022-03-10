#include <iostream>
#include <unistd.h>
#include <bits/unique_ptr.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>
#include <string>
#include "handler.h"
#include "events.h"
#include "common.h"
#include "argument.h"
#include "system_menu.h"
#include "a_jsonrpc.h"

#ifdef __cplusplus
extern "C" {

#include "am/a_am.h"

}
#endif

struct System_menuGroupURI {
    std::string index[URI_INDEX_SIZE];
};

System_menuGroupURI  system_menuGroupURIs[] = {

        /*
        # SYSTEM_MENU
        */
        { "enabled" },
        { "" },
};

int enabled(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    INT32   type    = 0;
    INT32   i4_ret  = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            CHAR s_app_name[APP_NAME_MAX_LEN + 1] = {0};
            a_am_get_next_active_app(s_app_name);

            if(c_strcmp(s_app_name,"menu") == 0)
            {
                response["VALUE"] =  (bool)TRUE;
                REST_LOG_W("menu status is TRUE\n");
            }
            else
            {
                response["VALUE"] =  (bool)FALSE;
                REST_LOG_W("menu status is FALSE\n");		
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value msg;
            Json::Value value;
            msg = root["message"];
            value = msg["VALUE"];

            REST_LOG_W("API do not completed\n");
            break;
        }
        default:
        {
            break;
        }
    }
    return 0;
}

handler system_menu_handler[] =
{
        enabled,
};

