#ifndef _REST_TV_SETTINGS_ADMIN_AND_PRIVACY_H_
#define _REST_TV_SETTINGS_ADMIN_AND_PRIVACY_H_

#include <cJSON.h>

#include "tv_settings.h"

extern int system_information_network_information_connection_type(Json::Value & root, Json::Value & response);

extern handler tv_settings_admin_and_privacy_handler[];



#endif

