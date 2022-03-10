#ifndef _A_JSONRPC_H_
#define _A_JSONRPC_H_

#include "a_rest_api.h"
//#include "json/value.h"
//#include <json/json.h>

#ifdef __cplusplus
extern "C" {
#endif

int jsonrpc_init(void);
int jsonrpc_deinit(void);
void jsonrpc_send_event(const char*, int, const char*);
void jsonrpc_send_event_ex(const char*, const void*);
void jsonrpc_send_event_json(const char* uri, const void* data);
void jsonrpc_set_python_reeady();

int json_parse_hash_value(char*, char*);
int json_parse_paired_device_list(char*, unsigned int*, REST_API_PAIRED_DEV_T*);
int json_parse_session_token(char* raw_data, unsigned int session_token_size, char* session_token);
int _json_parse_config_file(char* filepath, bool b_update_vtrl_ipt);
int _json_parse_ssdp_udn_file(char* in_filepath, char* out_filepath);
int json_parse_dlm_update_info(char* raw_data, REST_API_DLM_UPDATE_AVAILABLE_T* update_availablee);
int json_parse_dlm_update_status(char* raw_data, REST_API_DLM_UPDATE_STATUS_T* update_status);
int json_parse_capabilities_status(char* raw_data, bool* b_cs);
int json_parse_capabilities_boot_to_sc(char* raw_data, bool* b_is);
int json_parse_airplay_enabled(char* raw_data, bool* b_is);
int json_parse_consent_status(const char* raw_data, bool* b_is_accept);
int json_parse_bt_remote_info(char* raw_data, REST_API_BT_REMOTE_INFO_T* remote_info);
int json_parse_binaries_version_info(char* raw_data, REST_API_BINARIES_VERSION_T* p_version);
int json_parse_adid_info(char* raw_data, REST_API_ADID_T* p_adid);
int json_parse_capability_geo_info(char* raw_data, char* p_geo_map_uri);
int json_parse_capability_geo_timezone(char* raw_data, REST_TIMZONE_T* p_geo_timezone);
int json_parse_headphones_status(char* raw_data, bool* b_cs);

#ifdef __cplusplus
}
#endif

#endif
