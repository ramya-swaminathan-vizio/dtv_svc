#ifndef _REST_AIRPLAY_H_
#define _REST_AIRPLAY_H_

#include <cJSON.h>
#include "common.h"
#include <json/json.h>
#include "rest/a_rest.h"

typedef struct _AirplayPropertyNotofication{
    char propety[64];
    int type;
    char value_string[64];
    int value_int;
} AirplayPropertyNotofication;

extern handler airplay_handler[];
extern "C" int _airplay_notify_to_airplay(const char* ps_event, int int_value, const char* str_val);

#endif

