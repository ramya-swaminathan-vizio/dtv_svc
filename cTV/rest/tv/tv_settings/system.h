#ifndef _REST_TV_SETTINGS_SYSTEM_H_
#define _REST_TV_SETTINGS_SYSTEM_H_

#include <cJSON.h>

#include "tv_settings.h"

extern int system_information_network_information_ssid(Json::Value & root, Json::Value & response);
extern int system_information_network_information_security_type(Json::Value & root, Json::Value & response);
extern int system_information_network_information_ip_address(Json::Value & root, Json::Value & response);
extern int system_information_network_information_gateway(Json::Value & root, Json::Value & response);
extern int system_information_network_information_subnet_mask(Json::Value & root, Json::Value & response);
extern int system_information_network_information_preferred_dns_server(Json::Value & root, Json::Value & response);
extern int system_information_network_information_alternate_dns_server(Json::Value & root, Json::Value & response);
extern int system_information_network_information_rssi(Json::Value & root, Json::Value & response);
extern int system_information_network_information_rj45_mac_address(Json::Value & root, Json::Value & response);
extern int system_information_network_information_wlan_mac_address(Json::Value & root, Json::Value & response);
extern int system_information_network_information_wifi_module(Json::Value & root, Json::Value & response);
extern int system_information_tv_information_vertical_frequency(Json::Value & root, Json::Value & response);
extern int system_information_tv_information_audio_type(Json::Value & root, Json::Value & response);
extern int system_information_tv_information_audio_type_out(Json::Value & root, Json::Value & response);

extern handler tv_settings_system_handler[];

extern int aspect_ratio(Json::Value & root, Json::Value & response);

#ifdef APP_HDR_SUPPORT
extern "C" INT32 ver_info_get_hdr_type(CHAR* str_hdr);
#endif

#endif



