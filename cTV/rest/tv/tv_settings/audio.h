#ifndef _REST_TV_SETTINGS_AUDIO_H_
#define _REST_TV_SETTINGS_AUDIO_H_

#include <cJSON.h>

#include "tv_settings.h"

extern handler tv_settings_audio_handler[];
extern int volume(Json::Value & root, Json::Value & response);
extern int mute(Json::Value & root, Json::Value & response);

#endif



