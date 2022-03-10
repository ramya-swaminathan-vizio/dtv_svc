#ifndef _REST_JSON_H_
#define _REST_JSON_H_

#include "u_common.h"
#include "c_dbg.h"
#include "app_util/a_common.h"
#include "rest_cmd.h"

#include <cJSON.h>

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/



/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/ 
extern INT32 rest_pack_string(CHAR *ps_string, cJSON *root, REST_DATA_PARAM_1_T *pt_param);
extern INT32 rest_pack_int(INT32 i4_from, cJSON *root, REST_DATA_PARAM_1_T *pt_param);
extern INT32 rest_pack_double(DOUBLE d_from, cJSON *root,const CHAR* string_name);
extern INT32 rest_pack_ap(REST_DATA_WIFI_AP_T *ap, cJSON *root, INT32 ret_code);
extern INT32 rest_pack_ap_password_to_json(cJSON *root, INT32 ret_code);
extern INT32 rest_pack_aps(REST_DATA_WIFI_APS_T* aps, cJSON *root, INT32 ret_code);
extern INT32 rest_pack_test_connection(REST_DATA_TEST_CONNECTION_T *pt_result, 
                                                       cJSON *root,INT32 ret_code);
extern INT32 rest_pack_device(CHAR *s_device_name, cJSON *root,INT32 ret_code);
extern INT32 rest_pack_value_and_retcode_only(CHAR *s_value, cJSON *root, INT32 ret_code);
extern INT32 rest_pack_value_and_retcode(CHAR *s_value, cJSON *root,INT32 ret_code);
extern INT32 rest_pack_tos_to_json(cJSON *root,INT32 ret_code, BOOL b_tos_accept);
extern INT32 rest_pack_deviceinfo(REST_DATA_DEVICE_INFO_T *pt_device_info, cJSON *root);

/* the allocated memory must be freed after this API is called. */
extern INT32 rest_unpack_json_to_string_by_request_value(T_REST_WRITE_REQ_CMD *req, 
                                                                        cJSON *pjson, CHAR* value);

/* the allocated memory must be freed after this API is called. */
extern INT32 rest_unpack_json_value_int(T_REST_WRITE_REQ_CMD *req, cJSON *pjson);

/* the allocated memory must be freed after this API is called. */
extern INT32 rest_unpack_json_value_double(T_REST_WRITE_REQ_CMD *req, cJSON *pjson);
extern INT32 rest_unpack_json_to_ap(cJSON *pjson, REST_DATA_WIFI_AP_T *ap );
extern INT32 rest_unpack_json_ap(REST_DATA_WIFI_AP_T *ap, cJSON *pjson);

/* the allocated memory must be freed after this API is called. */
extern INT32 rest_unpack_json_aps(T_REST_WRITE_REQ_CMD *req, cJSON *pjson);

/* the allocated memory must be freed after this API is called. */
extern INT32 rest_unpack_json_test_connection(T_REST_WRITE_REQ_CMD *req, cJSON *pjson);

/* the allocated memory must be freed after this API is called. */
extern INT32 rest_unpack_json_device(T_REST_WRITE_REQ_CMD *req, cJSON *pjson);
extern VOID rest_pack_json_directly(cJSON *object, INT32 ret_code);
extern VOID rest_pack_json_read_head(INT32 ret_code, cJSON *root);

#endif



