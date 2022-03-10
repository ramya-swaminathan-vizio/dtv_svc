#include <iostream>
#include <bits/unique_ptr.h>

#include "handler.h"
#include "common.h"
#include <cJSON.h>
#include "argument.h"
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include "uli.h"


#ifdef __cplusplus
extern "C" {

#include "nav/updater/a_nav_updater.h"
#include "rest_system.h"

}
#endif

#define EX_LEN 3
#define PHONE "PHONE"
#define FIRST_NAME "FIRST_NAME"
#define LAST_NAME "LAST_NAME"
#define POSTAL_CODE "POSTAL_CODE"
#define EMAIL "EMAIL"
#define ULI_UPDATE_TIME_JSON "/data/uli/check_update.json"

struct ULIGroupURI {
    std::string index[URI_INDEX_SIZE];
};

ULIGroupURI  uLIGroupURIs[] = {

        /*
        # ULI
        */

        { "register" },
        { "is_device_registered" },
        { "is_owner_registered" },
        { "is_updating" },
        { "available_update_info" },
        { "start_update" },
        { "update_status" },
        { "update_time" },
        { "" },
};

#if 0
static INT32 str_pause_value(const CHAR *str_orig, const CHAR *str_prefex, CHAR *str_value)
{
    DBG_LOG_PRINT(("\n[ULI_REST] str_pause_value\n"));

    INT32 idx = 0;
    const char *s_str = NULL;
    s_str = strstr(str_orig,str_prefex);

    if (NULL != s_str)
    {
      s_str = s_str+strlen(str_prefex)+EX_LEN;

      while('\"' != *(s_str+idx))
      {
           str_value[idx] = *(s_str+idx);
           idx++;
      }

      str_value[idx] = '\0';
    }
    else
    {
        DBG_LOG_PRINT(("\n[ULI_REST] %s not exist!\n", str_prefex));

    }

    return 0;
}
#endif

int register_(Json::Value & root, Json::Value & response)
{
    INT32 type = 0;

    type = get_type(root);

    DBG_LOG_PRINT(("\n[ULI_REST] register_ type[%d]\n",type));

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            DBG_LOG_PRINT(("\n[ULI_REST] register_ [REQUEST_GET]\n"));

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            Json::Value item1;
            Json::Value item2;

            CHAR  str_orig_value[1024] = {0};

            DBG_LOG_PRINT(("\n[ULI_REST] register_ [REQUEST_SET]\n"));

            item2 = root["message"];
            item1 = item2["VALUE"];

            c_strncpy(str_orig_value, item1.asString().c_str(), 1023);

            DBG_LOG_PRINT(("\n[ULI_REST] register_ INFO: %s\n", str_orig_value));

            if (NULL != str_orig_value)
            {
                DBG_LOG_PRINT(("\n[ULI_REST] register_ a_nav_updater_uli_register_user_info_new\n"));
#ifdef APP_ULI_UPG_SUPPORT
                a_nav_updater_uli_register_user_info_new(str_orig_value);
#endif
            }
            break;
        }
        default:
            break;
    }

    return 0;

}

int is_device_registered(Json::Value & root, Json::Value & response)
{
    INT32 type = 0;
    type = get_type(root);

    DBG_LOG_PRINT(("\n[ULI_REST] is_device_registered type[%d]\n",type));

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_device_register_status = 0;
#ifdef APP_ULI_UPG_SUPPORT
            a_nav_updater_uli_get_device_register_status(&ui1_device_register_status);
#endif
            response["VALUE"] = ui1_device_register_status;

            DBG_LOG_PRINT(("\n[ULI_REST] is_device_registered [REQUEST_GET] VALUE[%d]\n",
                ui1_device_register_status));

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            DBG_LOG_PRINT(("\n[ULI_REST] is_device_registered [REQUEST_SET]\n"));
            break;
        }
        default:
            break;
    }

    return 0;

}


int is_owner_registered(Json::Value & root, Json::Value & response)
{
    INT32 type = 0;
    type = get_type(root);

    DBG_LOG_PRINT(("\n[ULI_REST] is_owner_registered type[%d]\n",type));

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_user_register_status = 0;
#ifdef APP_ULI_UPG_SUPPORT
            a_nav_updater_uli_get_user_register_status(&ui1_user_register_status);
#endif
            response["VALUE"] = ui1_user_register_status;

            DBG_LOG_PRINT(("\n[ULI_REST] is_owner_registered [REQUEST_GET] VALUE[%d]\n",
                ui1_user_register_status));

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            DBG_LOG_PRINT(("\n[ULI_REST] is_owner_registered [REQUEST_SET]\n"));
            break;
        }
        default:
            break;
    }

    return 0;

}

int is_updating(Json::Value & root, Json::Value & response)
{
    INT32 type = 0;
    type = get_type(root);

    DBG_LOG_PRINT(("\n[ULI_REST] is_updating type[%d]\n",type));

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_updating_status = 0;
#ifdef APP_ULI_UPG_SUPPORT
            a_nav_updater_uli_get_updating_status(&ui1_updating_status);
#endif
            response["VALUE"] = ui1_updating_status;

            DBG_LOG_PRINT(("\n[ULI_REST] is_updating [REQUEST_GET] VALUE[%d]\n",
                ui1_updating_status));

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            DBG_LOG_PRINT(("\n[ULI_REST] is_updating [REQUEST_SET]\n"));
            break;
        }
        default:
            break;
    }

    return 0;

}

int available_update_info(Json::Value & root, Json::Value & response)
{
    INT32 type = 0;
    INT32 i4_ret = 0;

    INT32 i4_ret_tmp = 0;

    type = get_type(root);

    DBG_LOG_PRINT(("\n[ULI_REST] available_update_info type[%d]\n",type));

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_fw_status = 0;
            UINT8 ui_fw_policy  = 0;
            CHAR  s_ver[64] = {0};

            Json::Value result;
#ifdef APP_ULI_UPG_SUPPORT
            a_nav_updater_check_fw_avaliable(&ui1_fw_status,&ui_fw_policy);
#endif
            if (NAV_UPDATE_FW_AVALIABLE_SATUS_CHECK_BUSY == ui1_fw_status)
            {

                result["UPDATE_LEVEL"] = 0;
                result["VERSION"] = "1.0";
                result["IS_AVAILABLE"] = 0;

                response["VALUE"] = result;

                /*return busy checking*/
                i4_ret = 2;
            }
            else
            {
#ifdef APP_ULI_UPG_SUPPORT
                i4_ret_tmp = nav_updater_get_update_ver_string(s_ver);
#endif
                DBG_LOG_PRINT(("\n[ULI_REST] available_update_info i4_ret_tmp[%d], s_ver[%s]\n",
                    i4_ret_tmp,s_ver));

                result["UPDATE_LEVEL"] = ui_fw_policy;

                if (NAVR_OK == i4_ret_tmp)
                {

                    result["VERSION"]= std::string(s_ver);
                }
                else
                {
                    /*default*/
                    result["VERSION"] = "1.0";
                }

                result["IS_AVAILABLE"] = ui1_fw_status;

                response["VALUE"] = result;

                i4_ret = 0;
            }

            DBG_LOG_PRINT(("\n[ULI_REST] available_update_info [REQUEST_GET] VALUE:fw_status[%d],fw_policy[%d],i4_ret[%d]\n",
                ui1_fw_status,ui_fw_policy,i4_ret));

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            DBG_LOG_PRINT(("\n[ULI_REST] available_update_info [REQUEST_SET]\n"));
            break;
        }
        default:
            break;
    }

    /*0 --> sucess
      2 --> busy
      1 --> blocked
    */
    return i4_ret;

}


int start_update(Json::Value & root, Json::Value & response)
{
    INT32 type = 0;

    type = get_type(root);

    DBG_LOG_PRINT(("\n[ULI_REST] start_update type[%d]\n",type));

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_fw_status = 0;
#ifdef APP_ULI_UPG_SUPPORT
            a_nav_updater_download_firmware_and_trigger_update(&ui1_fw_status);
#endif
            response["VALUE"] = ui1_fw_status;

            DBG_LOG_PRINT(("\n[ULI_REST] start_update [REQUEST_GET] VALUE[%d]\n",
                ui1_fw_status));

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            DBG_LOG_PRINT(("\n[ULI_REST] start_update [REQUEST_SET]\n"));
            break;
        }
        default:
            break;
    }

    return 0;

}


int update_status(Json::Value & root, Json::Value & response)
{
    INT32 type = 0;

    type = get_type(root);

    DBG_LOG_PRINT(("\n[ULI_REST] update_status type[%d]\n",type));

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            UINT8 ui1_update_status = 0;
            UINT8 ui1_progress = 0;
            Json::Value result;
#ifdef APP_ULI_UPG_SUPPORT
            a_nav_updater_get_update_status(&ui1_update_status,&ui1_progress);
#endif
            result["STATUS"] = ui1_update_status;
            result["PERCENT_COMPLETE"] = ui1_progress;

            response["VALUE"] = result;

            DBG_LOG_PRINT(("\n[ULI_REST] update_status [REQUEST_GET] VALUE:ui1_update_status[%d],ui1_progress[%d]\n",
                ui1_update_status,ui1_progress));

            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            DBG_LOG_PRINT(("\n[ULI_REST] update_status [REQUEST_SET]\n"));
            break;
        }
        default:
            break;
    }

    return 0;
}

static int _uli_get_update_time_interval(char *p_filepath)
{
    FILE *f_read=NULL;
    char p_buffer[128]={0};
    char *p_msg=NULL;
    char p_time[16] = {0};
    int i4_time = 0;

    if((f_read=fopen(p_filepath,"r"))==NULL)
    {
        DBG_LOG_PRINT(( "%s open file failed: %s\n\r" , __FUNCTION__,p_filepath));
        return -1;
    }
    fread(p_buffer,0x1,sizeof(p_buffer),f_read);
    fclose(f_read);

    p_msg = strstr(p_buffer,"time");
    sscanf(p_msg,"%*[^0-9]%[0-9]",p_time);
    sscanf(p_time,"%d",&i4_time);

    if(i4_time>0)
    {
        return  i4_time;
    }
    else
    {
        DBG_LOG_PRINT(("%s invaild value %s\n",i4_time));
        return -1;
    }
}

static int _uli_set_update_time_interval(int i4_timevalue,char *p_filepath)
{
    FILE *f_write=NULL;
    char p_buffer[128]={0};

    if((f_write=fopen(p_filepath,"w"))==NULL)
    {
        DBG_LOG_PRINT(( "%s open file failed: %s\n\r" , __FUNCTION__,p_filepath));
        return -1;
    }
    sprintf(p_buffer,"{ \"timer\":\"%d\"}",i4_timevalue);
    fwrite(p_buffer,0x1,strlen(p_buffer),f_write);
    fclose(f_write);

    s_chmod(p_filepath,0777);

    return 0;
}

int update_time(Json::Value & root, Json::Value & response)
{
    INT32 type = 0;

    type = get_type(root);

    DBG_LOG_PRINT(("\n[ULI_REST] update_time type [%d]-[%s]\n",type,type==argument::RequestType::REQUEST_GET?"GET":"SET"));

    switch (type)
    {
        case argument::RequestType::REQUEST_GET:
        {
            int i4_time = 0;
            i4_time = _uli_get_update_time_interval((char*)ULI_UPDATE_TIME_JSON);
            if(i4_time<=0)
            {
                DBG_LOG_PRINT(("update_time get value error\n"));
                response["VALUE"] = 24*60; //default 24 Hour
            }
            else
            {
                response["VALUE"] = i4_time;
                DBG_LOG_PRINT(("update_time get %d\n",i4_time));
            }
            break;
        }
        case argument::RequestType::REQUEST_SET:
        {
            int i4_time = 1;
            Json::Value msg;

            msg = root["message"];
            i4_time = msg["VALUE"].asInt();
            _uli_set_update_time_interval(i4_time,(char*)ULI_UPDATE_TIME_JSON);
            DBG_LOG_PRINT(("update_time set value finish\n"));
            break;
        }
        default:
            break;
    }

    return 0;
}

handler uli_handler[] = {
    register_,
    is_device_registered,
    is_owner_registered,
    is_updating,
    available_update_info,
    start_update,
    update_status,
    update_time,
};

