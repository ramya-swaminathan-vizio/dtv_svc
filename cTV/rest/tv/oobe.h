#ifndef _REST_OOBE_H_
#define _REST_OOBE_H_

#include <cJSON.h>

#include <string>
#include "common.h"
#include <json/json.h>



extern handler oobe_handler[];
extern VOID _oobe_stop_revoke_nfy(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3);
UINT8 a_oobe_state_name_to_page_index(const char* state_name);
const char * a_oobe_page_index_to_state_name(UINT8 page_index);
#endif


