#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <sys/time.h>
#include <cJSON.h>

#include "u_common.h"
#include "c_dt.h"
#include "c_os.h"
#include "c_dbg.h"

#include "app_util/a_common.h"
#include "rest.h"
#include "rest_dbg_level.h"
#include "rest_ipc_handler.h"
#include "rest_cmd.h"
#include "rest_json.h"


static inline VOID _pack_add_ap(cJSON *item, REST_DATA_WIFI_AP_T *ap);

static inline VOID _pack_add_ap(cJSON *item, REST_DATA_WIFI_AP_T *ap)
{
    if(ap == NULL || item == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return;
    }
    
    cJSON_AddItemToObject(item, REST_STR_NAME, cJSON_CreateString(ap->name));
    cJSON_AddItemToObject(item, REST_STR_RSSI, cJSON_CreateNumber(ap->rssi));
    cJSON_AddItemToObject(item, REST_STR_BAND, cJSON_CreateString(ap->band));
    cJSON_AddItemToObject(item, REST_STR_EM, cJSON_CreateString(ap->em));
    cJSON_AddItemToObject(item, REST_STR_BSSID, cJSON_CreateString(ap->bssid));
}




/*package json function*/
INT32 rest_pack_string(CHAR *ps_string, cJSON *root, REST_DATA_PARAM_1_T *pt_param)
{
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(pt_param->i4_ret_code));
    cJSON_AddItemToObject(root, REST_STR_VALUE, cJSON_CreateString(ps_string));

    if (REST_DATA_LOCK_TYPE_FALSE == pt_param->e_lock_type)
    {
        cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    }
    else if (REST_DATA_LOCK_TYPE_TRUE == pt_param->e_lock_type)
    {
        cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_TRUE));
    }

    if (REST_DATA_ENABLE_TYPE_FALSE == pt_param->e_enable_type)
    {
        cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_FALSE));
    }
    else if (REST_DATA_ENABLE_TYPE_TRUE == pt_param->e_enable_type)
    {
        cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));
    }

    return RESTR_OK;
}

INT32 rest_pack_int(INT32 i4_from, cJSON *root, REST_DATA_PARAM_1_T *pt_param)
{
    INT32 i4_ret = RESTR_OK;
    
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }

    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(pt_param->i4_ret_code));
    cJSON_AddItemToObject(root, REST_STR_VALUE, cJSON_CreateNumber(i4_from));
    
    if (REST_DATA_LOCK_TYPE_FALSE == pt_param->e_lock_type)
    {
        cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    }
    else if (REST_DATA_LOCK_TYPE_TRUE == pt_param->e_lock_type)
    {
        cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_TRUE));
    }

    if (REST_DATA_ENABLE_TYPE_FALSE == pt_param->e_enable_type)
    {
        cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_FALSE));
    }
    else if (REST_DATA_ENABLE_TYPE_TRUE == pt_param->e_enable_type)
    {
        cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));
    }
    
    return i4_ret;
}

INT32 rest_pack_double(DOUBLE d_from, cJSON *root,const CHAR* string_name)
{
    INT32 i4_ret = RESTR_OK;
    
    if(string_name == NULL || root==NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, string_name, cJSON_CreateNumber((const DOUBLE)d_from));
    return i4_ret;
}

INT32 rest_pack_ap(REST_DATA_WIFI_AP_T *ap, cJSON *root, INT32 ret_code)
{
    if(ap == NULL || root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
    cJSON *items = cJSON_CreateArray();
    cJSON_AddItemToObject(root, REST_STR_VALUE, items);

    cJSON *item = cJSON_CreateObject();
    cJSON_AddItemToArray(items, item);
    _pack_add_ap(item, ap);
    
    cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));

    return RESTR_OK;
}

INT32 rest_pack_ap_password_to_json(cJSON *root, INT32 ret_code)
{
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
    cJSON_AddItemToObject(root, REST_STR_VALUE, cJSON_CreateString(REST_STR_EMPTY));
    cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));

    return RESTR_OK;
}

INT32 rest_pack_aps(REST_DATA_WIFI_APS_T* aps, cJSON *root, INT32 ret_code)
{
    if(aps == NULL || root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
    cJSON *items = cJSON_CreateArray();
    cJSON_AddItemToObject(root,REST_STR_VALUE,items);

    INT32 i = 0;
    for (; i<aps->ap_num;i++)
    {
        REST_DATA_WIFI_AP_T *ap = &(aps->aplist[i]);
        cJSON *item = cJSON_CreateObject();
        cJSON_AddItemToArray(items,item);
        _pack_add_ap(item,ap);
        if(i==0)
        {      
            cJSON_AddItemToObject(item, REST_STR_CONNECTED, 
            cJSON_CreateString(aps->connected ? "Connected" : "Disconnected"));
        }
    }
    
    cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));

    return RESTR_OK;
}

INT32 rest_pack_test_connection(REST_DATA_TEST_CONNECTION_T *pt_result, 
                                                cJSON *root, INT32 ret_code)
{
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
    
    cJSON *item = NULL;
    cJSON_AddItemToObject(root,REST_STR_VALUE,item=cJSON_CreateObject());

    cJSON_AddItemToObject(item, REST_STR_ESTABLISHEDDNSSERVERS, cJSON_CreateString(pt_result->dns));
    cJSON_AddItemToObject(item, REST_STR_ESTABLISHEDNTPSERVER, cJSON_CreateString(pt_result->ntp));
    cJSON_AddItemToObject(item, REST_STR_CONNECTIONMETHOD, cJSON_CreateString(pt_result->conn_method));
    cJSON_AddItemToObject(item, REST_STR_CONNECTIONSPEED, cJSON_CreateNumber(pt_result->conn_speed));
    cJSON_AddItemToObject(item, REST_STR_SSIDNAME, cJSON_CreateString(pt_result->ssid));
    cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));

    return RESTR_OK;
}

INT32 rest_pack_device(CHAR *s_device_name, cJSON *root, INT32 ret_code)
{
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
    cJSON_AddItemToObject(root, REST_STR_VALUE, cJSON_CreateString(s_device_name));
    cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));

    return RESTR_OK;
}

INT32 rest_pack_value_and_retcode_only(CHAR *s_value, cJSON *root, INT32 ret_code)
{
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
    cJSON_AddItemToObject(root, REST_STR_VALUE, cJSON_CreateString(s_value));

    return RESTR_OK;
}

INT32 rest_pack_value_and_retcode(CHAR *s_value, cJSON *root, INT32 ret_code)
{
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
    cJSON_AddItemToObject(root, REST_STR_VALUE, cJSON_CreateString(s_value));
    cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));

    return RESTR_OK;
}

INT32 rest_pack_tos_to_json(cJSON *root, INT32 ret_code, BOOL b_tos_accept)
{
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
    if(b_tos_accept)
    {
        cJSON_AddItemToObject(root, REST_STR_VALUE, cJSON_CreateString(REST_STR_TRUE));
    }
    else
    {
        cJSON_AddItemToObject(root, REST_STR_VALUE, cJSON_CreateString(REST_STR_FALSE));
    }
    
    cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));

    return RESTR_OK;
}

INT32 rest_pack_deviceinfo(REST_DATA_DEVICE_INFO_T *pt_device_info, cJSON *root)
{
    if(root == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }

    cJSON_AddItemToObject(root, REST_STR_SUCCESS, cJSON_CreateNumber(RESTR_OK));

    cJSON * item = cJSON_CreateObject();
    cJSON *items1 = cJSON_CreateArray();            
    cJSON *items2 = cJSON_CreateArray();
    INT32 i = 0;

    cJSON_AddItemToObject(root, REST_STR_VALUE, item);
    cJSON_AddItemToObject(item, REST_STR_NAME, cJSON_CreateString(pt_device_info->Name));
    cJSON_AddItemToObject(item, "SETTINGSROOT", cJSON_CreateString(pt_device_info->SettingRoot));
    cJSON_AddItemToObject(item, "APIVERSION", cJSON_CreateString(pt_device_info->ApiVersion));

    cJSON_AddItemToObject(item, "INPUTS", items1);
    while(i<REST_DEVICE_INFO_NUM && (pt_device_info->HdmiInputs[i][0])!='0')
    {
        cJSON_AddItemToArray(items1, cJSON_CreateString(pt_device_info->HdmiInputs[i++]));
    }
    
    cJSON_AddItemToObject(item, "CAPABILITIES", items2);
    i = 0;
    while(i<REST_DEVICE_INFO_NUM && (pt_device_info->Capabitities[i][0])!='0')
    {
        cJSON_AddItemToArray(items2, cJSON_CreateString(pt_device_info->Capabitities[i++]));
    }

    cJSON_AddItemToObject(root, REST_STR_LOCKED, cJSON_CreateString(REST_STR_FALSE));
    cJSON_AddItemToObject(root, REST_STR_ENABLED, cJSON_CreateString(REST_STR_TRUE));

    return RESTR_OK;
}

/* the allocated memory must be freed after this API is called. */
INT32 rest_unpack_json_to_string_by_request_value(T_REST_WRITE_REQ_CMD *req, 
                                                                 cJSON *pjson, CHAR* value)
{
    if(req == NULL || pjson == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON *item = NULL;
    INT32 i4_ret = RESTR_OK;
    
    item = cJSON_GetObjectItem(pjson,value);
    if( item != NULL)
    {
        req->value_size = c_strlen(item->valuestring);
        req->value      = c_mem_alloc(req->value_size+1);
        if( req->value)
        {
            c_strcpy((char*)req->value,item->valuestring);
        }
        else
        {
            DBG_ERROR(("[REST_TV] error:%d \n",__LINE__));
            return RESTR_FAIL;
        }
        
        return i4_ret;
    }
    else
    {
        DBG_ERROR(("[REST_TV] error:%d \n",__LINE__));
        return RESTR_FAIL;
    }
}

/* the allocated memory must be freed after this API is called. */
INT32 rest_unpack_json_value_int(T_REST_WRITE_REQ_CMD *req, cJSON *pjson)
{
    INT32 i4_ret = RESTR_OK;
    
    if(req == NULL || pjson == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    req->value_size = sizeof(int);
    req->value = c_mem_alloc(req->value_size);

    *(INT32*)(req->value) = pjson->valueint;
    return i4_ret;
}

/* the allocated memory must be freed after this API is called. */
INT32 rest_unpack_json_value_double(T_REST_WRITE_REQ_CMD *req, cJSON *pjson)
{
    INT32 i4_ret = RESTR_OK;
    
    if( req == NULL || pjson == NULL )
    {
        DBG_ERROR(("[REST_TV] error:%d \n",__LINE__));
        return RESTR_FAIL;
    }
    
    req->value_size = sizeof(DOUBLE);
    req->value = c_mem_alloc(req->value_size);

    *(DOUBLE*)(req->value) = pjson->valuedouble;
    return i4_ret;
}


INT32 rest_unpack_json_to_ap(cJSON *pjson, REST_DATA_WIFI_AP_T *ap)
{
    if(ap == NULL || pjson == NULL)
    {
        DBG_ERROR(("[REST_CMD] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    cJSON *item;

    item = cJSON_GetObjectItem(pjson, REST_STR_NAME);
    if(item != NULL)
    {
        c_strcpy(ap->name,item->valuestring);
        DBG_INFO(("[REST_CMD]NAME:%s \n", ap->name));
    }
    
    item = cJSON_GetObjectItem(pjson, REST_STR_RSSI);
    if(item != NULL)
    {
        ap->rssi = item->valueint;  
        DBG_INFO(("[REST_CMD] RSSI:%d \n", ap->rssi));
    }
    
    item = cJSON_GetObjectItem(pjson, REST_STR_BAND);
    if(item != NULL)
    {
        c_strcpy(ap->band, item->valuestring);
        DBG_INFO(("[REST_CMD] BAND:%s \n", ap->band));
    }
    
    item = cJSON_GetObjectItem(pjson, REST_STR_EM);
    if(item != NULL)
    {
        c_strcpy(ap->em, item->valuestring);
        DBG_INFO(("[REST_CMD] EM:%s \n", ap->em));
    }
    
    item = cJSON_GetObjectItem(pjson, REST_STR_BSSID);
    if(item != NULL)
    {
        c_strcpy(ap->bssid, item->valuestring);
        DBG_INFO(("[REST_CMD] BSSID:%s \n", ap->bssid));
    }
    
    return RESTR_OK;
}


INT32 rest_unpack_json_ap(REST_DATA_WIFI_AP_T *ap, cJSON *pjson)
{
    
    if(ap == NULL || pjson == NULL)
    {
        DBG_ERROR(("[REST_CMD]: ap is NULL!! \n"));
        return RESTR_FAIL;
    }
    
    DBG_INFO(("[REST_CMD]:JSON:%s \n", cJSON_Print(pjson)));
    
    cJSON* pObj   = NULL;
    pObj          = cJSON_GetObjectItem(pjson, "TYPE");
    if( pObj )
    {
        DBG_INFO(("[REST_CMD]:TYPE:%s \n", pObj->valuestring));
    }
    cJSON* pArray = NULL;
    pArray = cJSON_GetObjectItem(pjson, REST_STR_VALUE);
    if(pArray)
    {
        cJSON *pArrayItem = NULL;
        pArrayItem = cJSON_GetArrayItem(pArray, 0);
        rest_unpack_json_to_ap(pArrayItem, ap);
    }
    return RESTR_OK;
}

/* the allocated memory must be freed after this API is called. */
INT32 rest_unpack_json_aps(T_REST_WRITE_REQ_CMD *req, cJSON *pjson)
{
    int i =0;

    int num = cJSON_GetArraySize(pjson);
    req->value_size = num*sizeof(REST_DATA_WIFI_AP_T);
    req->value = c_mem_alloc(req->value_size);

    for(;i<num;i++)
    {
        cJSON *pval = cJSON_GetArrayItem(pjson, i);
        cJSON * item = cJSON_GetObjectItem(pval, REST_STR_VALUE);
        rest_unpack_json_to_ap(item, &(((REST_DATA_WIFI_AP_T*)req->value)[i]));
    }

    return RESTR_OK;
}

/* the allocated memory must be freed after this API is called. */
INT32 rest_unpack_json_test_connection(T_REST_WRITE_REQ_CMD *req, cJSON *pjson)
{
    cJSON *item = NULL;
    req->value_size = sizeof(REST_DATA_TEST_CONNECTION_T);
    req->value = c_mem_alloc(req->value_size);
    REST_DATA_TEST_CONNECTION_T *test_conn= (REST_DATA_TEST_CONNECTION_T *)req->value;

    item = cJSON_GetObjectItem(pjson, REST_STR_ESTABLISHEDDNSSERVERS);
    if(item != NULL)
    {
        c_strcpy(test_conn->dns, item->valuestring);
    }
    item = cJSON_GetObjectItem(pjson, REST_STR_ESTABLISHEDNTPSERVER);
    if(item != NULL)
    {
        c_strcpy(test_conn->ntp, item->valuestring);
    }
    item = cJSON_GetObjectItem(pjson, REST_STR_CONNECTIONMETHOD);
    if(item != NULL)
    {
        c_strcpy(test_conn->conn_method, item->valuestring); 
    }
    item = cJSON_GetObjectItem(pjson, REST_STR_CONNECTIONSPEED);
    if(item != NULL)
    {
        test_conn->conn_speed = item->valueint; 
    }
    item = cJSON_GetObjectItem(pjson, REST_STR_SSIDNAME);
    if(item != NULL)
    {
        c_strcpy(test_conn->ssid, item->valuestring);
    }
    
    return RESTR_OK;
}

/* the allocated memory must be freed after this API is called. */
INT32 rest_unpack_json_device(T_REST_WRITE_REQ_CMD *req, cJSON *pjson)
{
    if(req == NULL || pjson == NULL)
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    cJSON *item = NULL;
    
    req->value_size = sizeof(T_REST_DATA_TYPE_DEVICE);
    req->value      = c_mem_alloc(req->value_size);
    if( req->value != NULL)
    {
        T_REST_DATA_TYPE_DEVICE *pdev = (T_REST_DATA_TYPE_DEVICE*)(req->value);
        item = cJSON_GetObjectItem(pjson, REST_STR_VALUE);
        if(item!=NULL)
        {
            c_strncpy(pdev->Name, item->valuestring, REST_DEVICE_INFO_NAME_LEN);
        }   
    }
    else
    {
        DBG_ERROR(("[REST_TV] error:%d \n", __LINE__));
        return RESTR_FAIL;
    }
    
    return RESTR_OK;   
}


VOID rest_pack_json_directly(cJSON *object, INT32 ret_code)
{
    cJSON_AddItemToObject(object, REST_STR_SUCCESS, cJSON_CreateNumber(ret_code));
}

//
// json read head include : status, uri, parameter
//
VOID rest_pack_json_read_head(INT32 ret_code, cJSON *root)
{
    rest_pack_json_directly(root, ret_code);
}

