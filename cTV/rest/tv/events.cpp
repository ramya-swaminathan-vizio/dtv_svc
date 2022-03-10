#include <iostream>
#include <string>

#include "handler.h"
#include "events.h"
#include "common.h"
#include "argument.h"

int endpoints[5] = { 0, 1, 2, 3, 4 };

struct EventsGroupURI {
    std::string index[URI_INDEX_SIZE];
};

EventsGroupURI eventsGroupURIs[] = {
        { "subscribe" },
        { "unsubscribe" },
        { "list" },
        { "" }
};

int subscribe(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            endpoints[3] = 100;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

int unsubscribe(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            endpoints[3] = -1;
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

int list(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");

    INT32 type = 0;

    type = get_type(root);

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            REST_LOG_I("REQUEST_GET\n\r");
            REST_LOG_I("/events/list, %d\n\r", endpoints[2]);
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            REST_LOG_I("REQUEST_SET\n\r");
            break;
        }
        default:
            break;
    }

    return 0;
}

handler events_handler[] = {
    subscribe,
    unsubscribe,
    list
};
