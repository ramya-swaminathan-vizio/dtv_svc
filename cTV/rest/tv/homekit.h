#ifndef _REST_HOMEKIT_H_
#define _REST_HOMEKIT_H_

#include <cJSON.h>
#include "common.h"
#include <json/json.h>
#include "rest/a_rest.h"

extern handler homekit_handler[];
extern "C" void homekit_factory_reset();

bool _homekit_pairing_status();

#endif

