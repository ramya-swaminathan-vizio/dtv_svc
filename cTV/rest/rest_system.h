#ifndef REST_SYSTEM_H 
#define REST_SYSTEM_H

#include "c_common.h"


#define MAX_CACHE_BUFFER_LEN 512  //max buffer length 512B

typedef  enum
{
    S_SYSTEM_ERR =-1,
    S_SYSTEM_OK   =0,
    S_SYSTEM_ARGUMENT_ERR =1, 
    S_SYSTEM_RESERVED,
    S_SYSTEM_CACHE_OVERFLOW,
}S_API_ERRNO;

#define S_DBG_I(fmt...)  \
    if(i4_s_dbg_level >= 3)\
    {\
        DBG_INFO(("\n\033[47;32m[%s][%d][INFO]",__FUNCTION__,__LINE__));\
        DBG_INFO((fmt));\
        DBG_INFO(("\033[0m"));\
    }

#define S_DBG_W(fmt...)  \
    if(i4_s_dbg_level >= 2)\
    {\
        DBG_INFO(("\n\033[47;33m[%s][%d][WARN]",__FUNCTION__,__LINE__));\
        DBG_INFO((fmt));\
        DBG_INFO(("\033[0m"));\
    }

#define S_DBG_E(fmt...)  \
    if(i4_s_dbg_level >= 1)\
    {\
        DBG_INFO(("\n\033[47;31m[%s][%d][ERROR]",__FUNCTION__,__LINE__));\
        DBG_INFO((fmt));\
        DBG_INFO(("\033[0m"));\
    }

extern INT32 i4_s_dbg_level;

/****       API List       ****/
INT32 s_echo(CHAR* p_path, CHAR* p_string, INT32 i4_strlen);        //echo "hello world" >  <file path> 
VOID s_sync(VOID);                                                                            //sync
INT32 s_touch(CHAR* p_path);                                                            //touch
INT32 s_rm(CHAR* p_path);                                                                //rm dir  OR rm file including it's content
INT32 s_ln(CHAR *p_old_path ,CHAR *p_new_path);                         //ln
INT32 s_mkdir(CHAR *p_dir_path);                                                     //mkdir
INT32 s_chmod(CHAR* p_path, INT32 i_mode);                                 //chmod
INT32 s_chown(CHAR* p_path, INT32 t_user_id ,INT32 t_group_id); //chown
INT32 s_r_chown(CHAR* p_path, INT32 t_user_id ,INT32 t_group_id); //chown -R


/****   Test for all  api    ****/
VOID s_test(VOID);


#endif //REST_SYSTEM_H

