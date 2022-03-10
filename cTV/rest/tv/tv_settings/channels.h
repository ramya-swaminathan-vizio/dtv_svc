#ifndef _REST_TV_SETTINGS_CHANNELS_H_
#define _REST_TV_SETTINGS_CHANNELS_H_

#include <cJSON.h>

#include "tv_settings.h"

typedef struct _CHANNEL_ID_MAP
{
    UINT32  ui4_channel_id;
    INT32   skipped;
    INT32   locked;
    CHAR    name[64];
    CHAR    channel[64];
    INT32   digital;
}CHANNEL_ID_MAP;

extern handler channels_handler[];
extern int parental_control_get_drrt_info(Json::Value *array, std::string &drrtname);
#endif



