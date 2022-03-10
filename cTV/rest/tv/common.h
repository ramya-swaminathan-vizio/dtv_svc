//
// Created by mtk40058 on 1/14/16.
//

#ifndef REST_DTV_COMMON_H
#define REST_DTV_COMMON_H

#include <json/json.h>
#include <stdio.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#include "c_dbg.h"
#include "u_dbg.h"
#include "u_common.h"
#include "wdk/widget/wdk_widget.h"
#include "res/revolt/revolt_settings_mlm.h"
#include "res/revolt/revolt_warnings_mlm.h"
}
#endif

#define REST_R_OK     (0)
#define REST_R_ERR    (-1)


static const int URI_INDEX_SIZE = 8;
extern uint32_t  ui4_rest_log_level;

#ifdef DBG_MODULE_NAME_PREFIX
#undef DBG_MODULE_NAME_PREFIX
#define DBG_MODULE_NAME_PREFIX rest_get_rest_name_prefix()
#endif

#define RET_ON_ERR(_expr)  \
{ \
    INT32 expr = _expr; \
    if(expr != 0)\
    {\
        DBG_LOG_PRINT(("<REST> ERR: %s, %s, %d, ret: %d\n\r", __FILE__, __FUNCTION__, __LINE__, expr)); \
        return expr;\
    } \
}

#define LOG_ON_ERR(_expr)  \
{ \
    INT32 expr = _expr; \
    if(expr != 0)\
    {\
        DBG_LOG_PRINT(("<REST> ERR: %s, %s, %d, ret: %d\n\r", __FILE__, __FUNCTION__, __LINE__, expr)); \
    } \
}

#define REST_LOG_E(fmt,... ) \
{\
    do{\
        if(ui4_rest_log_level < 1)\
            break;\
        DBG_LOG_PRINT(("[REST][ERROR][API:%s,%d] --> " fmt, __FUNCTION__, __LINE__,##__VA_ARGS__));\
    }while(0);\
}

#define REST_LOG_W(fmt,... ) \
{\
    do{\
        if(ui4_rest_log_level < 2)\
            break;\
       DBG_LOG_PRINT(("[REST][WARN][API:%s,%d] --> " fmt, __FUNCTION__, __LINE__,##__VA_ARGS__));\
    }while(0);\
}

#define REST_LOG_I(fmt,... ) \
{\
    do{\
        if(ui4_rest_log_level < 3)\
            break;\
        DBG_LOG_PRINT(("[REST][INFO][API:%s,%d] --> " fmt, __FUNCTION__, __LINE__,##__VA_ARGS__));\
    }while(0);\
}

#define REST_LOG_D(fmt,... ) \
{\
    do{\
        if(ui4_rest_log_level < 5)\
            break;\
        DBG_LOG_PRINT(("[REST][DEBUG][API:%s,%d] --> " fmt, __FUNCTION__, __LINE__,##__VA_ARGS__));\
    }while(0);\
}

#define REST_LANG_ENG 0
#define REST_LANG_SPA 2
#define REST_LANG_FRE 1

#define REST_SETTINGS_TEXT(key)   MLM_SETTINGS_TEXT(rest_get_mlm_settings_lang_id(), (key))
#define REST_WARNINGS_TEXT(key)   MLM_WARNINGS_TEXT(rest_get_mlm_warnings_lang_id(), (key))

extern UINT8 rest_get_mlm_settings_lang_id(VOID);
extern UINT8 rest_get_mlm_warnings_lang_id(VOID);

extern VOID  rest_send_msg_to_nav(WDK_TOAST_T* t_toast);
extern VOID  rest_send_msg_to_revolt_info_hide();

extern INT32 get_type(Json::Value & root);

extern INT32 value_get_value(Json::Value & root);
extern VOID  value_set_response(Json::Value & response, INT32 value);

extern VOID string_get_string(Json::Value & root, CHAR* string, INT32 length);
extern VOID string_set_response(Json::Value & response, CHAR* str);
extern INT32 rest_config_set_value(UINT16 ui2_grpid, UINT16 ui2_recid, INT32 i4_val);
extern INT32 rest_config_get_value(UINT16 ui2_grpid, UINT16 ui2_recid, INT32* pi4_val);
extern INT32 rest_config_get_min_max_value(UINT16 ui2_grpid, UINT16 ui2_recid, INT32* pi4_min_val, INT32* pi4_max_val);
extern CHAR* rest_get_rest_name_prefix();
#endif //DTV_COMMON_H
