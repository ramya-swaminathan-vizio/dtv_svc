#ifndef _REST_PIN_H_
#define _REST_PIN_H_

#include <cJSON.h>
#include "common.h"
#include <json/json.h>

extern handler pin_handler[];

extern "C" int a_set_is_pin_confirmed(bool b_confirm);

extern "C" int a_get_is_pin_confirmed(bool* b_confirm);

#endif



