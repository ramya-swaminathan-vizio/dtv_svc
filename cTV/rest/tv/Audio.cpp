#include <iostream>
#include <bits/unique_ptr.h>
#include <memory>
#include <unistd.h>
#include "common.h"
#include "argument.h"
#include <string.h>
#include "handler.h"
#include "Audio.h"
#include "tv_settings/audio.h"


int volume_level(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return volume(root,response);
}

int volume_mute(Json::Value & root, Json::Value & response)
{
    REST_LOG_I("Enter\n\r");
    return mute(root,response);
}


handler audio_handler[] = {
    volume_level,
    volume_mute,
};

