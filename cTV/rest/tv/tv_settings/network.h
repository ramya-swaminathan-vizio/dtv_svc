#ifndef _REST_TV_SETTINGS_NETWORK_H_
#define _REST_TV_SETTINGS_NETWORK_H_

#include <cJSON.h>
#include "tv_settings.h"

extern handler network_handler[];
extern int network_information_ipv6_address(Json::Value & root, Json::Value & response);
extern int network_information_ipv6_gateway(Json::Value & root, Json::Value & response);
extern int network_information_ipv6_prefix_len(Json::Value & root, Json::Value & response);
extern int network_information_ipv6_pref_dns_server(Json::Value & root, Json::Value & response);
extern int network_information_ipv6_alt_dns_server(Json::Value & root, Json::Value & response);
extern BOOL rest_network_is_internet_connected();
extern "C" bool test_connection_status();
extern "C" void update_test_connection_status();

#endif

