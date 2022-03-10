#include <cJSON.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "u_cli.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"

#include "c_common.h"
#include "c_dbg.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_os.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "menu2/menu.h"
#include "menu_page_bt_json_db.h"
#include "rest/vzipc/vzIpcServer.h"

#include "app_util/sentry_log/sentry_log.h"

#define VZ_MENU_LOG_ON_FAIL(_ret)  \
do{ \
    INT32 ret = _ret;   \
    if (ret < 0)   \
    {   \
        DBG_LOG_PRINT(("<MENU> Return fail:  [%s,%s(),%d] : ret=%d\r\n", __FILE__, __FUNCTION__, __LINE__, ret)); \
    }   \
}while(FALSE)

#define BT_DB_SYSTEM_PATH "/data/bt_data/btdb.json"
#define BT_DB_ARR_CONN "connected"
#define BT_DB_ARR_PAIR "paired"
#define BT_DB_ARR_SCAN "scanned"
#define BT_DEVICE_NUMBER 4

static cJSON *json_bt_dev_db = NULL;
const char bt_db_arr_types[3][10] = {BT_DB_ARR_CONN, BT_DB_ARR_PAIR,
                                     BT_DB_ARR_SCAN};

INT32 _json_bt_db_init(void);
cJSON *_json_bt_db_get_array(t_bt_item_type type);
char *_json_bt_db_read_file(void);
INT32 _json_bt_db_store(void);
INT32 _json_bt_db_insert_item(t_bt_item_type type, const char *name, const char *mac, bool append);
INT32 _json_bt_db_update_item_time(t_bt_item_type type, const char *mac);
INT32 _json_bt_db_update_item_name(t_bt_item_type type, const char *mac, const char *name );
INT32 _json_bt_db_remove_item(t_bt_item_type type, const char *mac);
INT32 _json_bt_db_get_mac(t_bt_item_type type, const char *name, char *mac);
INT32 _json_bt_db_get_mac_from_index(t_bt_item_type type, int index, char *mac);
INT32 _json_bt_db_get_index_from_mac(t_bt_item_type type, int* index, char *mac);
INT32 _json_bt_db_get_name(t_bt_item_type type, const char *mac, char *name);
INT32 _json_bt_db_clean_arr(t_bt_item_type type);
void _json_bt_db_populate( const char *pt_update_data );

INT32 _json_bt_db_init(void)
{
    INT32 i4_ret = MENUR_FAIL;
    char *buffer = NULL;
    cJSON *j_array = NULL;

    if (NULL == json_bt_dev_db)
    {
        if (access(BT_DB_SYSTEM_PATH, F_OK) == 0)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] :  DB file exists, load db...\r\n",
                       __FILE__, __FUNCTION__, __LINE__));

            buffer = _json_bt_db_read_file();
            if (NULL == buffer)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error occurs during reading file\r\n",
                     __FILE__, __FUNCTION__, __LINE__));
                return MENUR_FAIL;
            }

            json_bt_dev_db = cJSON_Parse(buffer);
            if (json_bt_dev_db == NULL)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_Parse: json_bt_dev_db == NULL\r\n",
                     __FILE__, __FUNCTION__, __LINE__));
                free(buffer);
                return MENUR_FAIL;
            }

            free(buffer);
        }
        else
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : DB file do not exist ...\r\n",
                           __FILE__, __FUNCTION__, __LINE__));
            VzLogToSentry("BTHEADPHONES_UI : Error occurred while reading from db file. DB file not exists");
            json_bt_dev_db = cJSON_CreateObject();
            if (NULL == json_bt_dev_db)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error occurred while generating new JSON object\r\n",
                           __FILE__, __FUNCTION__, __LINE__));
                return MENUR_OUT_OF_MEMORY;
            }

            for (UINT32 i = 0; i < 3; i++)
            {
                j_array = cJSON_CreateArray();
                if (NULL == j_array)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error occurred while generating new JSON array\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    i4_ret = MENUR_FAIL;
                    break;
                }
                else
                {
                    i4_ret = MENUR_OK;
                }

                cJSON_AddItemToObject(json_bt_dev_db, bt_db_arr_types[i], j_array);
            }

            if (i4_ret != MENUR_OK)
            {
                cJSON_Delete(json_bt_dev_db);
            }

            buffer = cJSON_Print(json_bt_dev_db);
            if (NULL == buffer)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error occurs while rendering JSON db to string\r\n",
                           __FILE__, __FUNCTION__, __LINE__));
                return MENUR_OUT_OF_MEMORY;
            }

            FILE *fptr = fopen(BT_DB_SYSTEM_PATH, "w");
            if (NULL == fptr)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error occurs during opening db - %s\r\n",
                     __FILE__, __FUNCTION__, __LINE__, BT_DB_SYSTEM_PATH));
                VzLogToSentry("BTHEADPHONES_UI : Error occurred while opening the db file ");
                free(buffer);
                return MENUR_FAIL;
            }

            fwrite(buffer, 1, strlen(buffer), fptr);
            fclose(fptr);
            free(buffer);
        }
    }

    return MENUR_OK;
}

char *_json_bt_db_read_file(void)
{
    FILE *fptr = NULL;
    char *buffer = NULL;

    fptr = fopen(BT_DB_SYSTEM_PATH, "r");
    if (NULL == fptr)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error occurs during opening db - %s\r\n",
             __FILE__, __FUNCTION__, __LINE__, BT_DB_SYSTEM_PATH));
        return NULL;
    }

    fseek(fptr, 0L, SEEK_END);
    long size = ftell(fptr);
    rewind(fptr);
    buffer = (char *)malloc(size + 1);
    if (buffer != NULL)
    {
        fread(buffer, size, 1, fptr);
        fclose(fptr);
        fptr = NULL;
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error can't allocate mamory for read file\r\n",
                   __FILE__, __FUNCTION__, __LINE__));
        if (fptr != NULL)
            fclose(fptr);
        return NULL;
    }

    buffer[size] = '\0';
    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : succesfully read config to buffer: %s, buffer_size : %ld\r\n",
                   __FILE__, __FUNCTION__, __LINE__, buffer, size));

    return buffer;
}

cJSON *_json_bt_db_get_array(t_bt_item_type type)
{
    cJSON *j_array = NULL;

    if (NULL == json_bt_dev_db)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : ERROR: Bad arguments! equal to NULL!\r\n",
             __FILE__, __FUNCTION__, __LINE__));
        return NULL;
    }

    switch (type)
    {
    case BD_ARR_TYPE_CONNECTED:
    {
        j_array = cJSON_GetObjectItem(json_bt_dev_db, "connected");
        if (j_array == NULL)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem [connected] returned NULL\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
            return NULL;
        }
    }
    break;
    case BD_ARR_TYPE_PAIRED:
    {
        j_array = cJSON_GetObjectItem(json_bt_dev_db, "paired");
        if (j_array == NULL)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem [paired] returned NULL\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
            return NULL;
        }
    }
    break;
    case BD_ARR_TYPE_SCANNED:
    {
        j_array = cJSON_GetObjectItem(json_bt_dev_db, "scanned");
        if (j_array == NULL)
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem [scanned] returned NULL\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
            return NULL;
        }
    }
    break;
    default:
        return NULL;
        break;
    }

    return j_array;
}

INT32 _json_bt_db_store(void)
{
    char *buffer = NULL;
    FILE *fptr = NULL;

    if (NULL != json_bt_dev_db)
    {
        if (access(BT_DB_SYSTEM_PATH, F_OK) == 0)
        {
            buffer = cJSON_Print(json_bt_dev_db);
            if (NULL == buffer)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error occurred rendering JSON db to string\r\n",
                           __FILE__, __FUNCTION__, __LINE__));
                return MENUR_OUT_OF_MEMORY;
            }

            fptr = fopen(BT_DB_SYSTEM_PATH, "w");
            if (NULL == fptr)
            {
                DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Error occurs during opening db - %s\r\n",
                     __FILE__, __FUNCTION__, __LINE__, BT_DB_SYSTEM_PATH));
                free(buffer);
                return MENUR_FAIL;
            }

            fwrite(buffer, 1, strlen(buffer), fptr);
            fclose(fptr);
            free(buffer);
        }
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : ERROR: Bad arguments! equal to NULL!\r\n",
             __FILE__, __FUNCTION__, __LINE__));
    }

    return MENUR_OK;
}

INT32 _json_bt_db_get_mac(t_bt_item_type type, const char *name, char *mac)
{
    INT32 arr_size = 0;
    cJSON *j_array = NULL;
    cJSON *j_item = NULL;
    cJSON *j_value = NULL;
    cJSON *j_value_name = NULL;

    if( mac == NULL || NULL == json_bt_dev_db )
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : ERROR: Bad arguments equal to NULL\r\n",
             __FILE__, __FUNCTION__, __LINE__));
        return MENUR_FAIL;
    }

    j_array = _json_bt_db_get_array(type);
    if (NULL == j_array)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : j_array is NULL, Item not Found\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return MENUR_ITEM_NOT_FOUND;
    }

    if (cJSON_IsArray(j_array))
    {
        arr_size = cJSON_GetArraySize(j_array);

        for (UINT32 i = 0; i < arr_size; i++)
        {
            j_item = cJSON_GetArrayItem(j_array, i);
            if (NULL != j_item)
            {
                j_value_name = cJSON_GetObjectItem(j_item, "name");
                if (j_value_name == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [name] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                // If name is not provided just return the mac of first item
                if (name == NULL || 0 == c_strncmp(j_value_name->valuestring, name, 64))
                {
                    j_value = cJSON_GetObjectItem(j_item, "mac");
                    if (j_value == NULL)
                    {
                        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] returned NULL\r\n",
                                   __FILE__, __FUNCTION__, __LINE__));
                        continue;
                    }
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Device found in DB index: %d,name: %s,mac: %s\r\n",
                        __FILE__, __FUNCTION__, __LINE__, i, j_value_name->valuestring, j_value->valuestring));
                    if (NULL != mac)
                    {
                        strcpy(mac, j_value->valuestring);
                    }
                    return MENUR_OK;
                }
            }
            else
            {
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetArrayItem of index [%d] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__, i));
                    continue;
                }
            }
        }
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_IsArray returned FALSE\r\n", __FILE__, __FUNCTION__, __LINE__));
    }

    return MENUR_ITEM_NOT_FOUND;
}

INT32 _json_bt_db_get_mac_from_index( t_bt_item_type type, int index, char *mac)
{
    cJSON *j_array = _json_bt_db_get_array( type );
    if( j_array == NULL )
        return MENUR_ITEM_NOT_FOUND;

    cJSON *j_item = cJSON_GetArrayItem( j_array, index );
    if( j_item == NULL )
        return MENUR_ITEM_NOT_FOUND;

    cJSON *j_value = cJSON_GetObjectItem( j_item, "mac");
    if ( j_value == NULL)
        return MENUR_ITEM_NOT_FOUND;

    if( mac != NULL )
    {
        strcpy( mac, j_value->valuestring );
        return MENUR_OK;
    }

    return MENUR_ITEM_NOT_FOUND;
}

INT32 _json_bt_db_get_index_from_mac( t_bt_item_type type, int *index, char *mac )
{
    cJSON *j_array = _json_bt_db_get_array( type );
    if( j_array == NULL )
        return MENUR_ITEM_NOT_FOUND;

    if( mac != NULL )
    {
        INT32 arr_size = cJSON_GetArraySize(j_array);

        for (UINT32 i = 0; i < arr_size; i++)
        {
            cJSON *j_item = cJSON_GetArrayItem( j_array, i );
            if( j_item == NULL )
                return MENUR_ITEM_NOT_FOUND;

            cJSON *j_value = cJSON_GetObjectItem( j_item, "mac");
            if ( j_value == NULL)
                return MENUR_ITEM_NOT_FOUND;

            if( strcmp( mac, j_value->valuestring ) == 0 )
            {
                *index = i;
                return MENUR_OK;
            }
        }
    }

    return MENUR_ITEM_NOT_FOUND;
}

INT32 _json_bt_db_get_name(t_bt_item_type type, const char *mac, char *name)
{
    INT32 arr_size = 0;
    cJSON *j_array = NULL;
    cJSON *j_item = NULL;
    cJSON *j_value = NULL;

    if( NULL == name || NULL == json_bt_dev_db )
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : ERROR: Bad arguments! equal to NULL\r\n",
             __FILE__, __FUNCTION__, __LINE__));
        return MENUR_FAIL;
    }

    j_array = _json_bt_db_get_array(type);
    if (NULL == j_array)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : j_array is NULL, Item not Found\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return MENUR_ITEM_NOT_FOUND;
    }

    if (cJSON_IsArray(j_array))
    {
        arr_size = cJSON_GetArraySize(j_array);

        for (UINT32 i = 0; i < arr_size; i++)
        {
            j_item = cJSON_GetArrayItem(j_array, i);
            if (NULL != j_item)
            {
                j_value = cJSON_GetObjectItem(j_item, "mac");
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                // If mac is not provided just return the name of first item
                if( mac == NULL || 0 == c_strcmp(j_value->valuestring, mac))
                {
                    j_value = cJSON_GetObjectItem(j_item, "name");
                    if (j_value == NULL)
                    {
                        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [name] returned NULL\r\n",
                                   __FILE__, __FUNCTION__, __LINE__));
                        continue;
                    }
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Device found index: %d,name: %s,mac: %s\r\n",
                                   __FILE__, __FUNCTION__, __LINE__, i, j_value->valuestring, mac));
                    if (NULL != name)
                    {
                        strcpy(name, j_value->valuestring);
                    }
                    return MENUR_OK;
                }
            }
            else
            {
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetArrayItem with index [%d] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__, i));
                    continue;
                }
            }
        }
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_IsArray returned FALSE\r\n", __FILE__, __FUNCTION__, __LINE__));
    }

    return MENUR_ITEM_NOT_FOUND;
}

INT32 _json_bt_db_insert_item(t_bt_item_type type, const char *name, const char *mac, bool append )
{
    time_t curr_time = 0;
    INT32 i4_ret = 0;
    cJSON *j_array = NULL;
    cJSON *j_item = NULL;

    if ((NULL == name) || (NULL == mac))
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : ERROR: Bad arguments! equal to NULL\r\n",
             __FILE__, __FUNCTION__, __LINE__));
        return MENUR_FAIL;
    }

    char bt_name[255] = {0};
    if (MENUR_OK == _json_bt_db_get_name(type, mac, bt_name))
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : Device name %s already existed in btdb exiting..\r\n",
             __FILE__, __FUNCTION__, __LINE__, bt_name));

        if( strcmp( bt_name, name ) != 0 )
        {
            _json_bt_db_update_item_name( type, mac, name );
        }

        return MENUR_OK;
    }

    if (NULL == json_bt_dev_db)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : ERROR: File handle json_bt_dev_db is NULL\r\n",
             __FILE__, __FUNCTION__, __LINE__));
        return MENUR_FAIL;
    }

    j_array = _json_bt_db_get_array(type);
    if (NULL == j_array)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : j_array is NULL, Item not Found\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return MENUR_OUT_OF_MEMORY;
    }

    j_item = cJSON_CreateObject();
    if (NULL == j_item)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_CreateObject returned NULL\r\n",
                   __FILE__, __FUNCTION__, __LINE__));
        return MENUR_OUT_OF_MEMORY;
    }

    if (!cJSON_AddStringToObject(j_item, "name", name))
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_AddStringToObject returned NULL\r\n",
                   __FILE__, __FUNCTION__, __LINE__));
        i4_ret = MENUR_OUT_OF_MEMORY;
    }

    if (!cJSON_AddStringToObject(j_item, "mac", mac))
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_AddStringToObject returned NULL\r\n",
                   __FILE__, __FUNCTION__, __LINE__));
        i4_ret = MENUR_OUT_OF_MEMORY;
    }

    if (BD_ARR_TYPE_SCANNED != type)
    {
        time(&curr_time);
        if (!cJSON_AddNumberToObject(j_item, "time", curr_time))
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_AddNumberToObject returned NULL\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
            i4_ret = MENUR_OUT_OF_MEMORY;
        }
    }

    if( append )
    {
        cJSON_AddItemToArray( j_array, j_item );
    }
    else
        cJSON_InsertItemInArray(j_array, 0, j_item);

    if (i4_ret < 0)
    {
        cJSON_Delete(j_item);
    }
    else
    {
        _json_bt_db_store();
    }

    return i4_ret;
}

INT32 _json_bt_db_update_item_name( t_bt_item_type type, const char *mac, const char *name )
{
    INT32 arr_size = 0;
    cJSON *j_array = NULL;
    cJSON *j_item = NULL;
    cJSON *j_value = NULL;

    if (NULL == json_bt_dev_db)
    {
        return MENUR_FAIL;
    }

    j_array = _json_bt_db_get_array(type);
    if (NULL == j_array)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : j_array is NULL, Item not Found\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return MENUR_ITEM_NOT_FOUND;
    }

    if (cJSON_IsArray(j_array))
    {
        arr_size = cJSON_GetArraySize(j_array);

        for (UINT32 i = 0; i < arr_size; i++)
        {
            j_item = cJSON_GetArrayItem(j_array, i);
            if (NULL != j_item)
            {
                j_value = cJSON_GetObjectItem(j_item, "mac");
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                if (0 == c_strcmp(j_value->valuestring, mac))
                {
                    j_value = cJSON_GetObjectItem(j_item, "name");
                    if (j_value == NULL)
                    {
                        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [time] returned NULL\r\n",
                                   __FILE__, __FUNCTION__, __LINE__));
                        continue;
                    }

                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : The previous name is: %s\r\n", __FILE__, __FUNCTION__, __LINE__, j_value->valuestring));

                    // remove old name
                    cJSON_DeleteItemFromObject( j_item, "name");

                    // insert new name
                    if (!cJSON_AddStringToObject(j_item, "name", name))
                    {
                        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_AddStringToObject return NULL\r\n",
                            __FILE__, __FUNCTION__, __LINE__));
                        return MENUR_OUT_OF_MEMORY;
                    }

                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : The updated name is: %s\r\n", __FILE__, __FUNCTION__, __LINE__, j_value->valuestring));

                    _json_bt_db_store();

                    return MENUR_OK;
                }
            }
            else
            {
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetArrayItem with index [%d] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__, i));
                    continue;
                }
            }
        }
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_IsArray: FALSE\r\n", __FILE__, __FUNCTION__, __LINE__));
    }

    return MENUR_ITEM_NOT_FOUND;
}
INT32 _json_bt_db_update_item_time(t_bt_item_type type, const char *mac)
{
    time_t curr_time = 0;
    INT32 arr_size = 0;
    cJSON *j_array = NULL;
    cJSON *j_item = NULL;
    cJSON *j_value = NULL;

    if (NULL == json_bt_dev_db)
    {
        return MENUR_FAIL;
    }

    j_array = _json_bt_db_get_array(type);
    if (NULL == j_array)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : j_array is NULL, Item not Found\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return MENUR_ITEM_NOT_FOUND;
    }

    if (cJSON_IsArray(j_array))
    {
        arr_size = cJSON_GetArraySize(j_array);

        for (UINT32 i = 0; i < arr_size; i++)
        {
            j_item = cJSON_GetArrayItem(j_array, i);
            if (NULL != j_item)
            {
                j_value = cJSON_GetObjectItem(j_item, "mac");
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                if (0 == c_strcmp(j_value->valuestring, mac))
                {
                    j_value = cJSON_GetObjectItem(j_item, "time");
                    if (j_value == NULL)
                    {
                        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [time] returned NULL\r\n",
                                   __FILE__, __FUNCTION__, __LINE__));
                        continue;
                    }

                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : The previous time is: %d\r\n", __FILE__, __FUNCTION__, __LINE__, j_value->valueint));

                    // remove old time
                    cJSON_DeleteItemFromObject( j_item, "time");
                    time(&curr_time);

                    // insert new time
                    if (!cJSON_AddNumberToObject(j_item, "time", curr_time))
                    {
                        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_AddStringToObject return NULL\r\n",
                            __FILE__, __FUNCTION__, __LINE__));
                        return MENUR_OUT_OF_MEMORY;
                    }

                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : The updated time is: %d\r\n", __FILE__, __FUNCTION__, __LINE__, j_value->valueint));
                    // Move to top
                    cJSON *temp = cJSON_DetachItemFromArray( j_array, i);
                    cJSON_InsertItemInArray( j_array, 0, temp );

                    _json_bt_db_store();

                    return MENUR_OK;
                }
            }
            else
            {
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetArrayItem with index [%d] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__, i));
                    continue;
                }
            }
        }
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_IsArray: FALSE\r\n", __FILE__, __FUNCTION__, __LINE__));
    }

    return MENUR_ITEM_NOT_FOUND;
}

INT32 _json_bt_db_remove_item(t_bt_item_type type, const char *mac)
{
    INT32 arr_size = 0;
    cJSON *j_array = NULL;
    cJSON *j_item = NULL;
    cJSON *j_value = NULL;

    if (NULL == json_bt_dev_db)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : json_bt_dev_db is NULL\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return MENUR_FAIL;
    }

    j_array = _json_bt_db_get_array(type);
    if (NULL == j_array)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : j_array is NULL, Item not Found\r\n",
                       __FILE__, __FUNCTION__, __LINE__));
        return MENUR_ITEM_NOT_FOUND;
    }

    if (cJSON_IsArray(j_array))
    {
        arr_size = cJSON_GetArraySize(j_array);

        for (UINT32 i = 0; i < arr_size; i++)
        {
            j_item = cJSON_GetArrayItem(j_array, i);
            if (NULL != j_item)
            {
                j_value = cJSON_GetObjectItem(j_item, "mac");
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                if (0 == c_strcmp(j_value->valuestring, mac))
                {
                    cJSON_DeleteItemFromArray(j_array, i);
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : device successfully deleted from db with index: %d,mac: %s\r\n",
                                   __FILE__, __FUNCTION__, __LINE__, i, mac));
                    _json_bt_db_store();
                    return MENUR_OK;
                }
            }
            else
            {
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetArrayItem with index [%d] returned NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__, i));
                    continue;
                }
            }
        }
        VzLogToSentry("BTHEADPHONES_UI : mac address not found in db while trying to remove it from db ");
    }
    else
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_IsArray: FALSE\r\n", __FILE__, __FUNCTION__, __LINE__));
    }

    return MENUR_ITEM_NOT_FOUND;
}

INT32 _json_bt_db_clean_arr(t_bt_item_type type)
{
    INT32 array_size = 0;
    cJSON *j_array = NULL;

    j_array = _json_bt_db_get_array(type);
    if (NULL == j_array)
    {
        return MENUR_FAIL;
    }

    while( cJSON_GetArraySize( j_array ) > 0 )
    {
        cJSON_DeleteItemFromArray( j_array, 0 );
    }

    return MENUR_OK;
}

void _json_bt_db_populate( const char *pt_update_data )
{
    cJSON *json_root = NULL;
    cJSON *j_array = NULL;
    cJSON *j_item = NULL;
    cJSON *j_value = NULL;
    INT32 list_size = 0, i4_ret = 0;
    bool is_paired = false;
    char *bt_paired_mac[130] = {0};
    char *bt_paired_mac_delete[130] = {0};
    INT32 bt_paired_count = 0;

    if( pt_update_data == NULL )
       return;

    i4_ret = _json_bt_db_clean_arr( BD_ARR_TYPE_CONNECTED );
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _json_bt_db_clean_arr( BD_ARR_TYPE_SCANNED );
    VZ_MENU_LOG_ON_FAIL(i4_ret);

    json_root = cJSON_Parse( pt_update_data );
    if (json_root == NULL)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_Parse: json_root == NULL\r\n",
                   __FILE__, __FUNCTION__, __LINE__));
        return;
    }

    j_array = cJSON_GetObjectItem(json_root, "list");
    if (j_array == NULL)
    {
        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_Parse: j_array == NULL\r\n",
                   __FILE__, __FUNCTION__, __LINE__));
        cJSON_Delete(json_root);
        return;
    }

    if (cJSON_IsArray(j_array))
    {
        list_size = cJSON_GetArraySize(j_array);

        for( INT32 i = 0; i < list_size; i++)
        {
            j_item = cJSON_GetArrayItem(j_array, i);

            if (NULL != j_item)
            {
                j_value = cJSON_GetObjectItem(j_item, "paired");

                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [paired] "
                               "j_array == NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                is_paired = (j_value->valuestring[0] == 'Y') ? true : false;

                char *bt_name = NULL;
                char *bt_mac = NULL;
                bool is_connected = false;

                j_value = cJSON_GetObjectItem(j_item, "connected");
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [connected] "
                               "j_array == NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                is_connected = (j_value->valuestring[0] == 'Y') ? true : false;

                j_value = cJSON_GetObjectItem(j_item, "name");
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [name] j_value "
                               "== NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                bt_name = j_value->valuestring;
                if (bt_name == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [name] bt_name "
                               "== NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : new BT device found %s, "
                               "is_paired %s, is_connected %s\r\n",
                               __FILE__, __FUNCTION__, __LINE__, bt_name,
                               is_paired ? "Y" : "N", is_connected ? "Y" : "N"));

                j_value = cJSON_GetObjectItem(j_item, "mac");
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [name] j_value "
                               "== NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                bt_mac = j_value->valuestring;

                if (is_paired)
                {
                    bt_paired_mac[ bt_paired_count++ ] = bt_mac;

                    _json_bt_db_insert_item( BD_ARR_TYPE_PAIRED, bt_name, bt_mac, TRUE);

                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : added to paired %s\r\n", __FILE__, __FUNCTION__, __LINE__, bt_name));

                    if (is_connected)
                    {
                        _json_bt_db_insert_item( BD_ARR_TYPE_CONNECTED, bt_name, bt_mac, TRUE);
                        DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : added to connected %s\r\n", __FILE__, __FUNCTION__, __LINE__, bt_name));
                    }
                }
                else
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : added to other %s\r\n", __FILE__, __FUNCTION__, __LINE__, bt_name));
                    _json_bt_db_insert_item(BD_ARR_TYPE_SCANNED, bt_name, bt_mac, TRUE);
                }
            }
            else
            {
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetArrayItem: [%d] j_item == "
                               "NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__, i));
                    continue;
                }
            }
        }

        // Check if there is item in json db's paired list that is not in scan response paired list,
        // if so delete it from json db's paired list.
        // MVV-10556

        cJSON *paired_array = _json_bt_db_get_array( BD_ARR_TYPE_PAIRED );
        list_size = cJSON_GetArraySize( paired_array );

    	DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : MVV-10556, %d\r\n", __FILE__, __FUNCTION__, __LINE__, list_size));

        bt_paired_count = 0;

        for( INT32 i = 0; i < list_size; i++)
        {
            cJSON *paired_item = cJSON_GetArrayItem( paired_array, i);

            if( NULL != paired_item )
            {
                j_value = cJSON_GetObjectItem( paired_item, "mac");
                if (j_value == NULL)
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : cJSON_GetObjectItem: [mac] j_value "
                               "== NULL\r\n",
                               __FILE__, __FUNCTION__, __LINE__));
                    continue;
                }

                INT32 j = 0, found = 0;
                while( j < 130 && bt_paired_mac[ j ] != NULL )
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : comparing %s, %s\r\n",
                           __FILE__, __FUNCTION__, __LINE__, j_value->valuestring, bt_paired_mac[ j ]));

                    if( 0 == c_strcmp( j_value->valuestring, bt_paired_mac[ j ]))
                    {
                        found++;
                        break;
                    }
                    ++j;
                }

                // If json db's Paired list's mac is not found in scan response paired list
                // mark it for deletion
                if( found == 0 )
                {
                    DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : mac to delete %s\r\n",
                           __FILE__, __FUNCTION__, __LINE__, j_value->valuestring));

                    bt_paired_mac_delete[ bt_paired_count++ ] = j_value->valuestring;
                }
            }
        }

        INT32 j = 0;
        while( j < 130 && bt_paired_mac_delete[ j ] != NULL )
        {
            DBG_LOG_PRINT(("BT_HEADPHONES_JSON_DB : [%s,%s(),%d] : mac to delete %s\r\n",
                           __FILE__, __FUNCTION__, __LINE__, bt_paired_mac_delete[ j ]));

            _json_bt_db_remove_item( BD_ARR_TYPE_PAIRED, bt_paired_mac_delete[ j ]);
            ++j;
        }
    }

    cJSON_Delete( json_root );
}
