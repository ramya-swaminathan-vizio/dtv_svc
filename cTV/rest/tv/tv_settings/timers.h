#ifndef _REST_TV_SETTINGS_TIMERS_H_
#define _REST_TV_SETTINGS_TIMERS_H_

#include <cJSON.h>

#include "tv_settings.h"

extern handler timers_handler[];
extern int timer_exit_blank_screen(Json::Value & root, Json::Value & response);


#endif



