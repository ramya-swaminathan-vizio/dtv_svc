#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cJSON.h>
#include <stdarg.h>

#include "rest.h"
#include "rest_dbg_level.h"

#include "a_rest_api.h"
#include "a_jsonrpc.h"
#include "c_httpc_api.h"

#include "curl/curl.h"
#include "curl/easy.h"
#include "rest_curl.h"
#include "rest_system.h"

//#include "app.h"

/*
int rest_launch_app (char* app)
{
    if (c_strlen(app) != 0) {
        return _rest_app_launch_app(app);
    } else {
        return -1;
    }
}
*/

int _i4_debug_level = 1; //1:error 2:warnning 3:info

void rest_set_rest_api_debug_level(int i4_level)
{
    _i4_debug_level=i4_level;
	rest_set_dbg_level(i4_level);
}

int rest_get_rest_api_debug_level(void)
{
    return _i4_debug_level;
}

//dolphin 20191227 change rest_api.c debug log for accomplish custom said VLOG=off still print log/
void _rest_api_print(char* s_string,...)
{
    char s_ptintfstring[512]={0};
    va_list ap;
    va_start(ap,s_string);
    vsprintf(s_ptintfstring,s_string,ap);
    va_end(ap);

    fprintf(stderr,s_ptintfstring);
}

int rest_get_paired_devices(unsigned int* device_list_size, REST_API_PAIRED_DEV_T* device_list)
{
    HANDLE_T h_handle = NULL_HANDLE;
    HTTPC_DATA_T t_data;
    int ret = 0;
    char uri[256] = "http://127.0.0.1:7346/menu_native/dynamic/tv_settings/system/mobile_devices/paired_devices";
    char s_c_session_token[24] = {'\0'};
    char session_header[33] = {'\0'};

    ret = c_httpc_new_session(&h_handle);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return -1;
    }

    c_httpc_data_init(&t_data);
    c_httpc_append_header(h_handle, "Content-Type: application/json");

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return RESTR_TOKEN_NOT_READY;
    }
    sprintf(session_header, "SESSION: %s", s_c_session_token);
    session_header[32] = '\0';
    c_httpc_append_header(h_handle, session_header);

    ret = c_httpc_get(h_handle, uri, &t_data);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_get error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    DBG_INFO(("[REST_AP_API][%s] c_httpc_get, len=%d, pac_data=%s\r\n", __FUNCTION__, t_data.ui4_len, t_data.pac_data));

    ret = json_parse_paired_device_list(t_data.pac_data, device_list_size, device_list);
    if(ret < 0){
        DBG_ERROR(("[REST_AP_API][%s] device list is not enough, please allocate a bigger one according to the 2nd parameter and re-call\r\n", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    if (h_handle != NULL_HANDLE) {
        c_httpc_free_session(h_handle);
        h_handle = NULL_HANDLE;
    }
    c_httpc_data_free(&t_data);

    return 0;
}

int rest_delete_paired_device(char* device_id)
{
    HANDLE_T h_handle = NULL_HANDLE;
    HTTPC_DATA_T t_data;
    int ret = 0;
    char uri[256] = "http://127.0.0.1:7346/menu_native/dynamic/tv_settings/system/mobile_devices/delete_paired_device";
    char body_data[150];
    char hash_val[11];
    unsigned int len = 0;
    char s_c_session_token[24] = {'\0'};
    char session_header[33] = {'\0'};

    ret = c_httpc_new_session(&h_handle);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return -1;
    }

    c_httpc_data_init(&t_data);
    c_httpc_append_header(h_handle, "Content-Type: application/json");

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return RESTR_TOKEN_NOT_READY;
    }
    sprintf(session_header, "SESSION: %s", s_c_session_token);
    session_header[32] = '\0';
    c_httpc_append_header(h_handle, session_header);

    ret = c_httpc_get(h_handle, uri, &t_data);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_get error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    ret = json_parse_hash_value(t_data.pac_data, hash_val);
    if(ret < 0){
        DBG_ERROR(("[REST_AP_API][%s] json_parse_hash_value error, no HASHVAL\r\n", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    len = snprintf(body_data, sizeof body_data, "{\"REQUEST\":\"ACTION\",\"VALUE\":\"%s\",\"HASHVAL\":%s}", device_id, hash_val);
    if (h_handle != NULL_HANDLE) {
        c_httpc_free_session(h_handle);
        h_handle = NULL_HANDLE;
    }
    c_httpc_data_free(&t_data);

    DBG_INFO(("[REST_AP_API][%s] hash_val=%s, body_data=%s, sizeof body_data=%d, len=%d\r\n", __FUNCTION__, hash_val, body_data, sizeof body_data, len));


    HANDLE_T h_handle2 = NULL_HANDLE;
    HTTPC_DATA_T t_data2;

    ret = c_httpc_new_session(&h_handle2);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle2 != NULL_HANDLE) {
            c_httpc_free_session(h_handle2);
            h_handle2 = NULL_HANDLE;
        }
        return -1;
    }

    c_httpc_data_init(&t_data2);
    c_httpc_append_header(h_handle2, "Expect: ");
    c_httpc_append_header(h_handle2, "Content-Type: application/json");
    c_httpc_append_header(h_handle2, session_header);
    ret = c_httpc_put(h_handle2, uri, (void*)body_data, len, &t_data2);
    DBG_INFO(("[REST_AP_API][%s] c_httpc_put, len=%d, pac_data=%s\r\n", __FUNCTION__, t_data2.ui4_len, t_data2.pac_data));
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_put error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle2 != NULL_HANDLE) {
            c_httpc_free_session(h_handle2);
            h_handle2 = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data2);
        return -1;
    }

    if (h_handle2 != NULL_HANDLE) {
        c_httpc_free_session(h_handle2);
        h_handle2 = NULL_HANDLE;
    }
    c_httpc_data_free(&t_data2);

    return 0;
}

int rest_get_dlm_available_info(REST_API_DLM_UPDATE_AVAILABLE_T* update_available)
{
    HANDLE_T h_handle = NULL_HANDLE;
    HTTPC_DATA_T t_data;
    int ret = 0;
    char uri[256] = "http://127.0.0.1:7346/dlm/available_update_info";
    char s_c_session_token[24] = {'\0'};
    char session_header[33] = {'\0'};

    c_httpc_data_init(&t_data);
    ret = c_httpc_new_session(&h_handle);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return -1;
    }

    c_httpc_data_init(&t_data);

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
        return RESTR_TOKEN_NOT_READY;
    }
    sprintf(session_header, "SESSION: %s", s_c_session_token);
    session_header[32] = '\0';
    c_httpc_append_header(h_handle, session_header);

    ret = c_httpc_get(h_handle, uri, &t_data);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_get error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    DBG_INFO(("[REST_AP_API][%s] c_httpc_get, len=%d, pac_data=%s\r\n", __FUNCTION__, t_data.ui4_len, t_data.pac_data));

    ret = json_parse_dlm_update_info(t_data.pac_data, update_available);
    DBG_INFO(("[REST_AP_API][%s] c_httpc_get, is_dlm_update_available: %d\r\n", __FUNCTION__, update_available->is_available));
    if(ret < 0){
        DBG_ERROR(("[REST_AP_API][%s] device list is not enough, please allocate a bigger one according to the 2nd parameter and re-call\r\n", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    if (h_handle != NULL_HANDLE) {
        c_httpc_free_session(h_handle);
        h_handle = NULL_HANDLE;
    }
    c_httpc_data_free(&t_data);

    return 0;
}

int rest_start_update_dlm()
{
    HANDLE_T h_handle = NULL_HANDLE;
    HTTPC_DATA_T t_data;
    int ret = 0;
    char uri[256] = "http://127.0.0.1:7346/dlm/start_update";

    char s_c_session_token[24] = {'\0'};
    char session_header[33] = {'\0'};

    ret = c_httpc_new_session(&h_handle);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return -1;
    }

    c_httpc_data_init(&t_data);

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return RESTR_TOKEN_NOT_READY;
    }
    sprintf(session_header, "SESSION: %s", s_c_session_token);
    session_header[32] = '\0';
    c_httpc_append_header(h_handle, session_header);

    ret = c_httpc_post(h_handle, uri, NULL, 0, &t_data);

    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_put error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    c_httpc_free_session(h_handle);
    c_httpc_data_free(&t_data);

    return 0;
}

int rest_get_dlm_update_status(REST_API_DLM_UPDATE_STATUS_T* update_status)
{
    HANDLE_T h_handle = NULL_HANDLE;
    HTTPC_DATA_T t_data;
    int ret = 0;
    char uri[256] = "http://127.0.0.1:7346/dlm/update_status";
    char s_c_session_token[24] = {'\0'};
    char session_header[33] = {'\0'};

    ret = c_httpc_new_session(&h_handle);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return -1;
    }

    c_httpc_data_init(&t_data);

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return RESTR_TOKEN_NOT_READY;
    }
    sprintf(session_header, "SESSION: %s", s_c_session_token);
    session_header[32] = '\0';
    c_httpc_append_header(h_handle, session_header);

    ret = c_httpc_get(h_handle, uri, &t_data);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_get error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    DBG_INFO(("[REST_AP_API][%s] c_httpc_get, len=%d, pac_data=%s\r\n", __FUNCTION__, t_data.ui4_len, t_data.pac_data));

    ret = json_parse_dlm_update_status(t_data.pac_data, update_status);
    DBG_INFO(("[REST_AP_API][%s] c_httpc_get, percent_complete: %d\r\n", __FUNCTION__, update_status->percent_complete));
    if(ret < 0){
        DBG_ERROR(("[REST_AP_API][%s] device list is not enough, please allocate a bigger one according to the 2nd parameter and re-call\r\n", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    if (h_handle != NULL_HANDLE) {
        c_httpc_free_session(h_handle);
        h_handle = NULL_HANDLE;
    }
    c_httpc_data_free(&t_data);

    return 0;
}
int rest_notify_airplay_disabled()
{
    HANDLE_T h_handle = NULL_HANDLE;
    HTTPC_DATA_T t_data;
    int ret = 0;
    char uri[256] = "http://127.0.0.1:7346/airplay/disabled";

    char s_c_session_token[24] = {'\0'};
    char session_header[33] = {'\0'};

    ret = c_httpc_new_session(&h_handle);
    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_new_session error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return -1;
    }

    c_httpc_data_init(&t_data);

    if (rest_get_session_token (s_c_session_token, 24) == FALSE){
        DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        return RESTR_TOKEN_NOT_READY;
    }
    sprintf(session_header, "SESSION: %s", s_c_session_token);
    session_header[32] = '\0';
    c_httpc_append_header(h_handle, session_header);

    ret = c_httpc_post(h_handle, uri, NULL, 0, &t_data);

    if(ret != HTTPR_OK){
        DBG_ERROR(("[REST_AP_API][%s] c_httpc_put error, ret = %d\r\n", __FUNCTION__, ret));
        if (h_handle != NULL_HANDLE) {
            c_httpc_free_session(h_handle);
            h_handle = NULL_HANDLE;
        }
        c_httpc_data_free(&t_data);
        return -1;
    }

    c_httpc_free_session(h_handle);
    c_httpc_data_free(&t_data);

    return 0;
}

int rest_get_capabilities_troubleshoot_status(bool *b_cs)
{
    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/state/device/deviceinfo";

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret = RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        DBG_INFO(("[REST_AP_API][%s] response = %s\r\n", __FUNCTION__,t_revbuf.memory));
        ret = json_parse_capabilities_status(t_revbuf.memory, b_cs);
    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

int rest_get_capabilities_boot_to_sc(bool *b_is)
{
    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/state/device/deviceinfo";

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret = RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));

        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        DBG_INFO(("[REST_AP_API][%s] response = %s\r\n", __FUNCTION__,t_revbuf.memory));
        ret = json_parse_capabilities_boot_to_sc(t_revbuf.memory, b_is);
    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

int rest_get_airplay_enabled(bool *b_is)
{
    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/airplay/property?prop=AirPlayEnabled";

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            printf("BOOTSC [REST_AP_API][%s] No Session Token\n\r", __FUNCTION__);
            ret = RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            printf("BOOTSC [REST_AP_API][%s]  succeed\r\n", __FUNCTION__);

        }
        else
        {
            printf("BOOTSC [REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret);
            break;
        }
        ret = json_parse_airplay_enabled(t_revbuf.memory, b_is);
    }while(0);

    if (t_revbuf.memory)
    {
        printf("BOOTSC [REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__);
        free(t_revbuf.memory);
    }
    return ret;
}


int rest_get_binaries_version(REST_API_BINARIES_VERSION_T *p_version)
{

    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/system/binaries/version";

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret =	RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        DBG_ERROR(("[REST_AP_API][%s]  response = %s\r\n", __FUNCTION__,t_revbuf.memory));
        ret = json_parse_binaries_version_info(t_revbuf.memory, p_version);
    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

int rest_get_adid(REST_API_ADID_T *p_adid)
{

    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/system/tvad_id";

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret =	RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        DBG_ERROR(("[REST_AP_API][%s]  response = %s\r\n", __FUNCTION__,t_revbuf.memory));
        ret = json_parse_adid_info(t_revbuf.memory, p_adid);
    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

int rest_get_device_info(CHAR *p_version)
{

    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/app/config/version";

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret =	RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_ERROR(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        DBG_ERROR(("[REST_AP_API][%s], size: %d,  response = %s \r\n", __FUNCTION__, t_revbuf.size,t_revbuf.memory));
        ret = json_parse_device_info(t_revbuf.memory, p_version);
    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

int rest_get_device_instance_id(CHAR *p_diid)
{
    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/state/device/deviceinfo";

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret =	RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_ERROR(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        ret = json_parse_device_info_diid(t_revbuf.memory, p_diid);
        DBG_INFO(("[%s][%d] DIID = %s, ret = %d \r\n", __FUNCTION__, __LINE__, p_diid, ret));

    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

int rest_get_bluetooth_status(REST_API_BT_REMOTE_INFO_T *p_remote_info)
{

    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/bluetooth/remote_information";

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret =	RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        DBG_ERROR(("[REST_AP_API][%s]  response = %s\r\n", __FUNCTION__,t_revbuf.memory));
        ret = json_parse_bt_remote_info(t_revbuf.memory, p_remote_info);
    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

int a_rest_app_launch_cast_to_conjure_apps()
{
    return _rest_app_launch_cast_to_conjure_apps();
}

int a_rest_app_update_overlay_app(bool retaildemo)
{
    return _rest_app_update_overlay_app(retaildemo);
}

//dolphin add 20200909 for get Geofencing support time
int rest_get_geofencing_time(char *p_geo_buf)
{
    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/system/capabilities";
    const char p_https_uri_header[]="https://127.0.0.1:7345/";
    char p_trans_url[256] = {0}; //the jump link to other URL
    char p_trans_uri[256] = {0}; //get the argument uri

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE){
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret =	RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);

        t_list.header[t_list.num++] = p_session_header;  //AUTH
        t_list.header[t_list.num++] = p_content_type;  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        DBG_ERROR(("[REST_AP_API][%s]  response = %s\r\n", __FUNCTION__,t_revbuf.memory));
        ret = json_parse_capability_geo_info(t_revbuf.memory,p_trans_uri); //1. get the next request uri
        if(ret != 0)
        {
            DBG_ERROR(("[REST_AP_API][%s]  get response error\r\n", __FUNCTION__));
        }
        else
        {
            sprintf(p_trans_url,"%s%s",p_https_uri_header,p_trans_uri);
            ret = rest_https_get_req(p_trans_url ,t_list ,&t_revbuf);
            if(ret==0)
            {
                DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
            }
            else
            {
                DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
                break;
            }
        }
    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

/*
* For static type app, it's native modules' responsibility to launch cast_shell.
* This API is just for notifying to rest ap
*/
int a_rest_launch_static_app()
{
    return _rest_app_launch_static_app_by_system();
}

int a_rest_app_launch_user_manual()
{
    return _rest_app_launch_user_manual();
}

int a_rest_leave_cast_input()
{
    return _rest_app_no_app_notification();
}

// shall firing switching to cast input before call this api
int a_rest_launch_sc_home()
{
    //return _rest_app_launch_sc_home();
    return _rest_app_launch_app_by_keycode(0x2d, 1);
}

int a_rest_app_is_key_handler(int key_code)
{
    return _rest_app_is_key_handler(key_code);
}

int a_rest_app_cancel_oobe()
{
    return rest_app_cancel_oobe();
}
int a_rest_get_Rest_Version(char * restVerStr)
{
       return get_Rest_Version(restVerStr);
}

#if 0
int a_rest_launch_partner_key_app()
{
    return _rest_launch_partner_key_app();
}
#endif

int a_rest_notify_after_grant_resource()
{
    return _rest_launch_through_c4tv_apron_delay_launch();
}

int a_rest_notify_on_receiving_request_resource()
{
    return _rest_notify_on_receiving_request_resource();
}

int a_rest_app_get_current_app_is_cast_type()
{
    return _rest_app_get_current_app_is_cast_type();
}

int a_rest_app_get_current_app_need_cast_shell()
{
    return _rest_app_get_current_app_need_cast_shell();
}

int a_rest_app_get_current_app_is_oobe()
{
    return _rest_app_get_current_app_is_oobe();
}

int a_rest_app_get_current_app_is_uml()
{
    return _rest_app_get_current_app_is_uml();
}

int a_rest_app_get_current_app_is_watchfree()
{
    return _rest_app_get_current_app_is_watchfree();
}

int a_rest_app_launch_native_app_notify(char* app_name)
{
    return _rest_app_launch_native_app_notify(app_name);
}

int a_rest_app_leave_airplay()
{
    return _rest_app_leave_airplay();
}

int a_rest_app_is_native_app_interrupted_by_cast()
{
    return _rest_app_is_native_app_interrupted_by_cast();
}

int a_rest_app_avoid_revoke_resource()
{
    return _rest_app_avoid_revoke_resource();
}

int a_rest_app_launch_virtual_input(char* cname)
{
    return _rest_app_launch_virtual_input(cname);
}

int a_rest_app_select_virtual_input(char* name)
{
    return _rest_app_select_virtual_input(name);
}

void a_rest_app_reset_key_code(int key_code)
{
    _reset_app_set_key_code(key_code);
}

void a_rest_app_handle_key_for_browser_control(int ui4_key_code)
{
    return _rest_app_handle_key_for_browser_control(ui4_key_code);
}

int a_rest_app_get_current_app_is_semaphore()
{
    return _rest_app_get_current_app_is_semaphore();
}

void a_rest_app_factory_reset()
{
    return _rest_app_factory_reset();
}
void a_rest_app_get_info_from_airplay(const char* prop,void* res_buf)
{
    cJSON *root_res, *j_value, *j_value_value,*j_value_value_value,*j_type;
    char ret_buf[1024] = {0};
    c_memset(ret_buf, 0, 1024);

    _airplay_send_msg_to_airplay(2, prop, ret_buf, 1024-1, -1, 0, NULL, TRUE);
    if (c_strstr(ret_buf, "SUCCESS") == NULL)
    {
        DBG_ERROR(("%s_%d get airplay vision fail \n",__FUNCTION__,__LINE__));
        return;
    }
    root_res = cJSON_Parse(ret_buf);
    j_value = cJSON_GetObjectItem(root_res, "result");
    if (j_value == NULL) {
        cJSON_Delete(root_res);
        return;
    }
    j_value_value = cJSON_GetObjectItem(j_value, "value");
    if (j_value_value == NULL) {
        cJSON_Delete(root_res);
        return;
    }

    j_type = cJSON_GetObjectItem(j_value_value, "type");
    if (j_type == NULL) {
        DBG_ERROR(("Parse j_type failed.\n\r"));
        cJSON_Delete(root_res);
        return;
    }

    j_value_value_value = cJSON_GetObjectItem(j_value_value, "value");
    if (j_value_value_value == NULL) {
        cJSON_Delete(root_res);
        return;
    }
    if (c_strcmp(j_type->valuestring, "boolean") == 0) {
        DBG_INFO(("a_rest_app_get_info_from_airplay boolean type,j_value_value->valueint=%d\n\r",j_value_value->valueint));
        int * res_buf_int_t = (int *)res_buf;
        *res_buf_int_t= j_value_value_value->valueint;
    }else
    {
        char * res_buf_char_t =   (char *)res_buf;
        c_memset(res_buf_char_t, 0, 1024);
        c_strncpy(res_buf_char_t, j_value_value_value->valuestring, 12);
    }
}

int a_rest_app_sent_disable_airplay(const char* prop,bool bool_val)
{
        char res_buf[1024] = {0};
        c_memset(res_buf, 0, 1024);
       return  _airplay_send_msg_to_airplay(1, prop, res_buf, 1024-1,1, 0, NULL,bool_val);
}

bool a_rest_app_check_install_airplay()
{
    return _rest_app_check_install_airplay();
}

void a_rest_app_lock_launch_sema()
{
    lockLaunchSema();
}

void a_rest_app_unlock_launch_sema()
{
    unlockLaunchSema();
}

void a_rest_app_reserved_org_input_for_airplay()
{
    _rest_app_reserved_org_input_for_airplay();
}

int rest_get_geofencing_timezone(REST_TIMZONE_T *p_geo_timezone)
{
    int ret=-1;
    char p_session_token[24] = {'\0'};
    char p_session_header[33] = {'\0'};
    char p_content_type[64]= "Content-Type: application/json";
    HeaderList t_list={0};
    MemoryStruct t_revbuf;
    char p_uri[256] = "https://127.0.0.1:7345/system/capabilities";
    const char p_https_uri_header[]="https://127.0.0.1:7345/";
    char p_trans_url[256] = {0};//the jump link to other URL
    char p_trans_uri[256] = {0}; //get the argument uri

    t_revbuf.memory = NULL;
    t_revbuf.size = 0;
    do
    {
        if (rest_get_session_token (p_session_token, 24) == FALSE)
        {
            DBG_ERROR(("[REST_AP_API][%s] No Session Token\n\r", __FUNCTION__));
            ret = RESTR_TOKEN_NOT_READY;
            break;
        }
        sprintf(p_session_header, "AUTH: %s", p_session_token);
        t_list.header[t_list.num++] = p_session_header,strlen(p_session_header);  //AUTH
        t_list.header[t_list.num++] = p_content_type,strlen(p_content_type);  //CONTENT
        ret = rest_https_get_req(p_uri ,t_list ,&t_revbuf);
        if(ret==0)
        {
            DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
        }
        else
        {
            DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
            break;
        }

        DBG_ERROR(("[REST_AP_API][%s]  response = %s\r\n", __FUNCTION__,t_revbuf.memory));
        ret = json_parse_capability_geo_info(t_revbuf.memory,p_trans_uri); //1. get the next request uri
        if(ret != 0)
        {
            DBG_ERROR(("[REST_AP_API][%s]  get response error\r\n", __FUNCTION__));
        }
        else
        {
            /*clear 0*/
            c_memset(&t_revbuf,0,sizeof(MemoryStruct));

            sprintf(p_trans_url,"%s%s",p_https_uri_header,p_trans_uri);
            ret = rest_https_get_req(p_trans_url ,t_list ,&t_revbuf);
            if(ret==0)
            {
                DBG_INFO(("[REST_AP_API][%s]  succeed\r\n", __FUNCTION__));
            }
            else
            {
                DBG_ERROR(("[REST_AP_API][%s]  error, ret = %d\r\n", __FUNCTION__, ret));
                break;
            }

            ret = json_parse_capability_geo_timezone(t_revbuf.memory,p_geo_timezone); //1. get the next request uri
            if(ret != 0)
            {
                DBG_ERROR(("[REST_AP_API][%s]  get response error\r\n", __FUNCTION__));
            }
        }
    }while(0);

    if (t_revbuf.memory)
    {
        DBG_INFO(("[REST_AP_API][%s, %d] free memory\r\n", __FUNCTION__, __LINE__));
        free(t_revbuf.memory);
    }
    return ret;
}

