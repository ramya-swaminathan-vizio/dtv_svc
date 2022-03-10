#ifndef _REST_SYSTEM_H_
#define _REST_SYSTEM_H_

#include <cJSON.h>

#include <string>
#include "common.h"

#include <json/json.h>

#define PA_MASK 0x7000
#define CEC_OSD_NAME_SIZE 15
#define CEC_VENDOR_ID_SIZE CEC_OSD_NAME_SIZE
#define CEC_DEVICE_LA_SIZE (CEC_OSD_NAME_SIZE >> 1)
#define CEC_DEVICE_PA_SIZE CEC_DEVICE_LA_SIZE
#define CEC_DEVICE_VER_SIZE CEC_DEVICE_LA_SIZE

extern handler system_handler[];

extern "C" int cmd_assets_update();
extern "C" int cmd_binary_update(const char* path);
extern "C" int get_Rest_Version(char * restVerStr);
extern "C" VOID _rest_system_update_binary_expired_timer_cb(HANDLE_T h_timer, VOID* pv_tag);
extern "C" int c_assets_stage(char *p_path);
extern "C" int c_assets_update(char *p_path);

void _rest_system_current_input_notification(const char* s_input);
int rest_system_chg_input_src(VOID);
int _rest_system_stop_start_chromium(bool b_start);

#endif



