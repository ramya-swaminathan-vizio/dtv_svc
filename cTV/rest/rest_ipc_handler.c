#include <pthread.h>
#include <assert.h>
#include <string.h>
#include <cJSON.h>

#include "c_dbg.h"
#include "c_os.h"

#include "rest_ipc.h"
#include "rest.h"
#include "app_util/a_common.h"
#include "rest_cmd.h"
#include "rest_ipc_handler.h"
#include "rest_dbg_level.h"


static pthread_t rest_ipc_thread;
static BOOL b_g_cmd_busy = FALSE;
static REST_MSG_BUF_ORI t_g_data_from_vssp = {0};

static void* rest_process_msg_thread(void *pv_arg);




/******************************** 
* call this method when rest startup.
* create ipc recv thread.   
* create ipc msg queue.
*********************************/
INT32 rest_init(VOID)
{
    INT32 i4_ret  = RESTR_OK;
    
    i4_ret = rest_ipc_init();
    REST_CHK_FAIL(i4_ret);
    
    i4_ret = pthread_create(&rest_ipc_thread, NULL, 
                            rest_process_msg_thread, NULL);
    REST_CHK_FAIL(i4_ret);

    return i4_ret;
}

/*****************************
* uninit
****************************/
INT32 rest_uninit(VOID)
{
    INT32 i4_ret  = RESTR_OK;
    
    i4_ret = rest_ipc_destroy();
    REST_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static BOOL _is_cmd_busy(VOID)
{
    return b_g_cmd_busy;
}
static VOID _set_cmd_busy(BOOL b_busy)
{
    b_g_cmd_busy = b_busy;
}

/*****************************
* recv ipc msg.
* dispatch the msg to handle.
****************************/

static VOID* rest_process_msg_thread(VOID *pv_arg)
{
    INT32 i4_ret = RESTR_OK;    
    INT32 i4_running = 1;
    
    while(i4_running)
    {       
        c_memset(&t_g_data_from_vssp, 0, sizeof(REST_MSG_BUF_ORI));
        i4_ret = rest_get_msg_from_Vssp_ori(&t_g_data_from_vssp);
        REST_LOG_ON_FAIL(i4_ret);
        
        DBG_INFO(("\n%s,%d,i4_ret=%d,uri=%s,mtype=%d\n", 
                    __FILE__, __LINE__, i4_ret, 
                    t_g_data_from_vssp.uri, t_g_data_from_vssp.mtype));

        if (0 == t_g_data_from_vssp.mtype)
        {
            DBG_INFO(("\n%s,%d\n", __FUNCTION__, __LINE__));
            continue;
        }

        if(_is_cmd_busy())
        {
            REST_ASSERT(0);
        }
        _set_cmd_busy(TRUE);

        switch(t_g_data_from_vssp.mtype)
        {
            case REST_MSG_REQUEST_GET:
            {
                i4_ret = tv_cmd_do(HTTP_REQ_GET, t_g_data_from_vssp.uri, 
                                    t_g_data_from_vssp.data_str);
                REST_LOG_ON_FAIL(i4_ret);
                
                break;
            }

            case REST_MSG_REQUEST_SET:
            {
                i4_ret = tv_cmd_do(HTTP_REQ_SET, t_g_data_from_vssp.uri, 
                                    t_g_data_from_vssp.data_str);
                REST_LOG_ON_FAIL(i4_ret);
                
                break;
            }

            case REST_MSG_REQUEST_RESET:
            {
                i4_ret = tv_cmd_do(HTTP_REQ_SET, t_g_data_from_vssp.uri, 
                                    t_g_data_from_vssp.data_str);
                REST_LOG_ON_FAIL(i4_ret);
                
                break;
            }

            case REST_MSG_REQUEST_ACTION:
            {
                i4_ret = tv_cmd_do(HTTP_REQ_ACTION, t_g_data_from_vssp.uri, 
                                    t_g_data_from_vssp.data_str);
                REST_LOG_ON_FAIL(i4_ret);

                break;
            }
            
            default:
            {
                i4_ret = tv_cmd_do(HTTP_REQ_MAX, t_g_data_from_vssp.uri, 
                                    t_g_data_from_vssp.data_str);
                REST_LOG_ON_FAIL(i4_ret);
            }
                break;
        }

        _set_cmd_busy(FALSE);
    }

    REST_ASSERT(0);
    return NULL;
}

/*****************************
* send the msg to client by ipc.
****************************/

INT32 rest_notify(cJSON* pv_msg, long mtype, const CHAR *uri)
{
    REST_MSG_BUF_ORI *pt_notify_msg;
    INT32 i4_ret = RESTR_OK;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    pt_notify_msg = (REST_MSG_BUF_ORI *)c_mem_alloc(sizeof(REST_MSG_BUF_ORI));
    if (NULL == pt_notify_msg)
    {
        REST_ASSERT(0);
        DBG_ERROR(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
        return RESTR_OUT_OF_MEMORY;
    }
        
    c_memset(pt_notify_msg, 0, sizeof(REST_MSG_BUF_ORI));
    pt_notify_msg->mtype = REST_MSG_RESPONSE_FROM_TV;
    c_strncpy(pt_notify_msg->uri, uri, REST_URI_LEN);
    c_strncpy(pt_notify_msg->data_str, cJSON_Print(pv_msg), REST_BUFFER_SIZE);

    DBG_INFO(("\n%s,%s,%d,uri=%s,\ndata_str=%s\n", 
            __FILE__, __FUNCTION__, __LINE__,
            pt_notify_msg->uri, pt_notify_msg->data_str));
    
    i4_ret = rest_send_msg_2_Vssp_ori(pt_notify_msg);
    REST_LOG_ON_FAIL(i4_ret);

    if (pt_notify_msg)
    {
        c_mem_free(pt_notify_msg);
        pt_notify_msg = NULL;
    }

    return i4_ret;
}





