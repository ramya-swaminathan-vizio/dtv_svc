#ifndef _REST_TV_SETTINGS_DEVICES_H_
#define _REST_TV_SETTINGS_DEVICES_H_

#include <cJSON.h>

#include "tv_settings.h"

#ifdef __cplusplus
extern "C" {

#include "app_util/a_isl.h"

#include "u_common.h"
#include "u_inp_hdlr.h"

}
#endif

extern handler devices_handler[];

extern int name_input_cast(Json::Value & root, Json::Value & response);
extern int name_input_hdmi1(Json::Value & root, Json::Value & response);
extern int name_input_hdmi2(Json::Value & root, Json::Value & response);
extern int name_input_hdmi3(Json::Value & root, Json::Value & response);
extern int name_input_hdmi4(Json::Value & root, Json::Value & response);
extern int name_input_hdmi5(Json::Value & root, Json::Value & response);
extern int name_input_comp(Json::Value & root, Json::Value & response);
extern int name_input_tuner(Json::Value & root, Json::Value & response);
extern int name_input_vga(Json::Value & root, Json::Value & response);

extern INT32 picture_position_vertical(Json::Value & root, Json::Value & response);
extern INT32 picture_size_vertical(Json::Value & root, Json::Value & response);
extern INT32 picture_position_horizontal(Json::Value & root, Json::Value & response);
extern INT32 picture_size_horizontal(Json::Value & root, Json::Value & response);
extern INT32 hdmi_current_hdmi_color(Json::Value & root, Json::Value & response);

extern "C" INT32 chg_inp_src(INP_SRC_TYPE_T e_src_type, DEVICE_TYPE_T e_video_type, UINT8 ui1_internal_id);

void _rest_devices_current_inputs_notification(const char* s_input);

#endif



