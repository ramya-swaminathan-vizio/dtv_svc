//
// Created by mtk40058 on 1/14/16.
//

#ifndef REST_DTV_HANDLER_H
#define REST_DTV_HANDLER_H

#include <json/json.h>


//typedef int (*handler) (int id, Json::Value & root, Json::Value & response);
//typedef int (*action_handler) (Json::Value & root, Json::Value & response);

typedef int (*handler) (Json::Value & root, Json::Value & response);
typedef struct _HandlerAction
{
    int i4_handler_num;
    handler *sub_handler;
}HandlerAction;

#endif //DTV_HANDLER_H
