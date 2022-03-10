#include <iostream>

#include "handler.h"
#include "common.h"
#include "argument.h"
#include <string.h>
#include "picture_ex.h"
#include "a_jsonrpc.h"
#include "rest.h"
#include <unistd.h>
#include <signal.h>
#include "server.h"

#ifdef __cplusplus
extern "C" {
#include "c_svctx.h"
#include "c_rm.h"
#include "rest_util.h"
#include "res/app_util/app_tv/a_tv_custom.h"

#include "app_util/a_bluetooth.h"
#include "app_util/config/a_cfg_custom.h"
#include "app_util/config/acfg_custom.h"

#include "rest/a_jsonrpc.h"
#include "rest/a_rest_event.h"
}
#endif


struct ServerGroupURI {
    std::string index[URI_INDEX_SIZE];
};


ServerGroupURI serverGroupURIs[] = {
	{ "ready" },
	{ "" },
};
int server_ready(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            REST_LOG_I("Not implement\n\r");
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            REST_LOG_I("Python notify ready\n\r");
            jsonrpc_set_python_reeady();
            rest_set_python_reeady();
            break;
        }
        default:
            break;
    }

	return 0;
}

handler server_handler[] = {
    server_ready,
};


