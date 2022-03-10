#include <iostream>
#include "handler.h"
#include <tv_settings/picture.h>
#include <tv_settings/audio.h>
#include <tv_settings/timers.h>
#include <tv_settings/network.h>
#include <tv_settings/devices.h>
#include <tv_settings/system.h>
#include <tv_settings/cast.h>
#include <tv_settings/channels.h>
#include <tv_settings/closed_captions.h>
#include "uli.h"



#if 0
static const int ID_GROUP_TV_SETTINGS_PICTURE	= 0x00;
static const int ID_GROUP_TV_SETTINGS_AUDIO		= 0x01;
static const int ID_GROUP_TV_SETTINGS_TIMERS	= 0x02;
static const int ID_GROUP_TV_SETTINGS_NETWORK	= 0x03;
static const int ID_GROUP_TV_SETTINGS_DEVICES	= 0x04;
static const int ID_GROUP_TV_SETTINGS_SYSTEM	= 0x05;
static const int ID_GROUP_TV_SETTINGS_CAST		= 0x06;
static const int ID_GROUP_TV_SETTINGS_CHANNELS		= 0x07;
static const int ID_GROUP_TV_SETTINGS_CLOSED_CAPTIONS		= 0x08;


handler tv_settins_handler1s[] = {
    picture_handler,
    audio_handler,
    timers_handler,
    network_handler,
    devices_handler,
    system_handler,
    cast_handler,
    channels_handler,
    closed_captions_handler,
} ;



int tv_settings_handler(int id, Json::Value & root, Json::Value & response){
    REST_LOG_I("Enter\n\r");
    return tv_settins_handler1s[(id % ID_GROUP_MASK) >> ID_GROUP_OFFSET](id, root, response);
}
#endif

int tv_settings_exit_blank_screen(Json::Value & root, Json::Value & response)
{
    return timer_exit_blank_screen(root, response);
}

