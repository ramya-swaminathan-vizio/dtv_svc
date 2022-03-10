#ifndef _REST_TV_SETTINGS_H_
#define _REST_TV_SETTINGS_H_

#include <cJSON.h>

#include <string>
#include <json/json.h>
#include "common.h"
#include "handler.h"

struct TvSettingsGroupURI {
    std::string index[URI_INDEX_SIZE];
};


extern int tv_settings_exit_blank_screen(Json::Value & root, Json::Value & response);

#endif



