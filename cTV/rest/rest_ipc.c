/********************************************************************************************
 *     LEGAL DISCLAIMER
 *
 *     (Header of MediaTek Software/Firmware Release or Documentation)
 *
 *     BY OPENING OR USING THIS FILE, BUYER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 *     THAT THE SOFTWARE/FIRMWARE AND ITS DOCUMENTATIONS ("MEDIATEK SOFTWARE") RECEIVED
 *     FROM MEDIATEK AND/OR ITS REPRESENTATIVES ARE PROVIDED TO BUYER ON AN "AS-IS" BASIS
 *     ONLY. MEDIATEK EXPRESSLY DISCLAIMS ANY AND ALL WARRANTIES, EXPRESS OR IMPLIED,
 *     INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR
 *     A PARTICULAR PURPOSE OR NONINFRINGEMENT. NEITHER DOES MEDIATEK PROVIDE ANY WARRANTY
 *     WHATSOEVER WITH RESPECT TO THE SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY,
 *     INCORPORATED IN, OR SUPPLIED WITH THE MEDIATEK SOFTWARE, AND BUYER AGREES TO LOOK
 *     ONLY TO SUCH THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. MEDIATEK SHALL ALSO
 *     NOT BE RESPONSIBLE FOR ANY MEDIATEK SOFTWARE RELEASES MADE TO BUYER'S SPECIFICATION
 *     OR TO CONFORM TO A PARTICULAR STANDARD OR OPEN FORUM.
 *
 *     BUYER'S SOLE AND EXCLUSIVE REMEDY AND MEDIATEK'S ENTIRE AND CUMULATIVE LIABILITY WITH
 *     RESPECT TO THE MEDIATEK SOFTWARE RELEASED HEREUNDER WILL BE, AT MEDIATEK'S OPTION,
 *     TO REVISE OR REPLACE THE MEDIATEK SOFTWARE AT ISSUE, OR REFUND ANY SOFTWARE LICENSE
 *     FEES OR SERVICE CHARGE PAID BY BUYER TO MEDIATEK FOR SUCH MEDIATEK SOFTWARE AT ISSUE.
 *
 *     THE TRANSACTION CONTEMPLATED HEREUNDER SHALL BE CONSTRUED IN ACCORDANCE WITH THE LAWS
 *     OF THE STATE OF CALIFORNIA, USA, EXCLUDING ITS CONFLICT OF LAWS PRINCIPLES.
 ************************************************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/time.h>

#include <fcntl.h>
#include <mqueue.h>

#include "rest_ipc.h"
#include "c_dbg.h"
#include "rest.h"
#include "rest_dbg_level.h"
#include "app_util/a_common.h"
#include "u_common.h"
#include "u_dbg.h"

typedef struct _REST_IPC_MSG_T
{
    int TV_Msgq_Id;
    int Vssp_Msgq_Id;
    int Event_Msgq_Id;
} REST_IPC_MSG_T;

typedef struct _REST_MQD_T
{
    mqd_t TV_Mqd_Id;    //MSG VSSP -> REST
    mqd_t Vssp_Mqd_Id;  //MSG REST -> VSSP
    mqd_t Event_Mqd_Id; //EVENT MSG REST -> VSSP
} REST_MQD_T;

static REST_IPC_MSG_T t_g_rest_ipc_msgq = {0};

static REST_MQD_T t_g_rest_mqd = {0};
static struct mq_attr g_rest_mqd_attr;

static INT32 _rest_q_create(int* p_msg_handle,int key_value);
static INT32 _rest_q_destroy(int handle);
static INT32 _rest_q_send_msg(int handle, REST_MSG_BUF* pv_msg);
static INT32 _rest_q_receive_msg(int handle,REST_MSG_BUF* pv_msg);

#define MQD_VSSP2REST "/mqd_Vssp2Rest"
#define MQD_REST2VSSP "/mqd_Rest2Vssp"
#define MQD_EVENT_REST2VSSP "/mqd_Event_Rest2Vssp"
static INT32 _rest_mqd_create(mqd_t* mqd, char* mqd_name, int flag);
static INT32 _rest_mqd_destroy(mqd_t mqd);
static INT32 _rest_mqd_send_msg(mqd_t mqd, REST_MSG_BUF* pv_msg);
static INT32 _rest_mqd_receive_msg(mqd_t mqd, REST_MSG_BUF* pv_msg);

VOID is_timeout(int timeout_threshold)
{
    double time_diff = 0;
    struct timeval start, end;

    gettimeofday(&start, NULL);
    while(TRUE){
        gettimeofday(&end, NULL);
        time_diff = (end.tv_sec - start.tv_sec) * 1000 + (double)(end.tv_usec - start.tv_usec) / 1000;
        // printf("start=%ld, end=%ld, time_diff=%lf\n", start.tv_usec, end.tv_usec, time_diff);
        if(time_diff > timeout_threshold) break;
    }

    return;
}

static INT32 _rest_q_create(int* p_msg_handle,int key_value)
{
    key_t key;
    int flags = IPC_CREAT;
    int msgid = -1;

    key = ftok("/basic/dtv_svc", key_value);

    msgid = msgget(key, flags|00666);
    REST_CHK_FAIL(msgid);

    DBG_API(("\n%s,%d,key=%d,msgid=%d\n", __FUNCTION__, __LINE__, key, msgid));

    *p_msg_handle = msgid;
    return RESTR_OK;
}


static INT32 _rest_q_destroy(int handle)
{
    msgctl(handle, IPC_RMID, NULL);

    return RESTR_OK;
}

static INT32 _rest_q_send_msg(int handle, REST_MSG_BUF* pv_msg)
{
    INT32 i4_ret = RESTR_FAIL;
    INT32 retry_counter = 0;

    while(i4_ret == -1 ) {
        //REST_IPC_DEBUG("_rest_q_send_msg\n\r");
        i4_ret = msgsnd(handle, pv_msg, REST_BUFFER_SIZE, IPC_NOWAIT);
        if (i4_ret == -1) {
            DBG_ERROR(("[%s %d] ", __func__, __LINE__));
            perror("#### SND error");
            if (errno != EAGAIN || retry_counter >= 3) {
                break;
            }
            ++retry_counter;
            c_thread_delay (70);
            DBG_ERROR(("try again\n\r"));
            //is_timeout(70);
        }
    }

    return i4_ret;
}

static INT32 _rest_q_receive_msg(int handle,REST_MSG_BUF* pv_msg)
{
    INT32 i4_ret = RESTR_FAIL;

    while(i4_ret == -1 ) {
        i4_ret = msgrcv(handle, (void*)pv_msg, REST_BUFFER_SIZE, 0, 0);
        if (i4_ret == -1) {
            //perror("#### RCV error");
            if (errno != EAGAIN) {
                break;
            }
        }
    }

    return i4_ret;
}

static INT32 _rest_mqd_create(mqd_t* mqd, char* mqd_name, int flag)
{
    INT32 i4_ret = RESTR_OK;

    mqd_t mqd_t = mq_open(mqd_name, flag|O_RDWR, 0666, NULL);
    if (mqd_t < 0)
    {
        DBG_ERROR(("[%s %d] ", __func__, __LINE__));
        perror("mq_open fail");
        i4_ret = RESTR_FAIL;
    }

    *mqd = mqd_t;
    return i4_ret;
}

static INT32 _rest_mqd_destroy(mqd_t mqd)
{
    mq_close(mqd);

    return RESTR_OK;
}

static INT32 _rest_mqd_send_msg(mqd_t mqd, REST_MSG_BUF* pv_msg)
{
    INT32 i4_ret = RESTR_FAIL;
    INT32 retry_counter = 0;

    while(i4_ret == -1 ) {
        i4_ret = mq_send(mqd, (char*)pv_msg, g_rest_mqd_attr.mq_msgsize, 0);
        if (i4_ret == -1) {
            DBG_ERROR(("[%s %d] ", __func__, __LINE__));
            perror("#### SND error");
            if (errno != EAGAIN || retry_counter >= 3) {
                break;
            }
            ++retry_counter;
            c_thread_delay (70);
            DBG_LOG_PRINT(("try again\n\r"));
        }
    }

    return i4_ret;
}

static INT32 _rest_mqd_receive_msg(mqd_t mqd, REST_MSG_BUF* pv_msg)
{
    INT32 i4_ret = RESTR_FAIL;

    while(i4_ret == -1 ) {
        i4_ret = mq_receive(mqd, (char*)pv_msg, g_rest_mqd_attr.mq_msgsize, NULL);
        if (i4_ret == -1) {
            DBG_ERROR(("[%s %d] ", __func__, __LINE__));
            perror("#### RCV error");
            if (errno != EAGAIN) {
                break;
            }
        }
    }

    return i4_ret;
}

static INT32 _rest_q_send_msg_ori(int handle, REST_MSG_BUF_ORI* pv_msg)
{
    INT32 i4_ret = RESTR_FAIL;

    i4_ret = msgsnd(handle, pv_msg, REST_BUFFER_SIZE, IPC_NOWAIT);
    REST_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _rest_q_receive_msg_ori(int handle,REST_MSG_BUF_ORI* pv_msg)
{
    INT32 i4_ret = RESTR_FAIL;

    i4_ret = msgrcv(handle, (void*)pv_msg, REST_BUFFER_SIZE, 0, 0);
    REST_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

INT32 rest_ipc_init(void)
{
    INT32 i4_ret = RESTR_FAIL;
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
#ifndef SYSTEM_V
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    i4_ret = _rest_mqd_create(&(t_g_rest_mqd.TV_Mqd_Id), MQD_VSSP2REST, O_CREAT);
    REST_CHK_FAIL(i4_ret);
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = _rest_mqd_create(&(t_g_rest_mqd.Vssp_Mqd_Id), MQD_REST2VSSP, O_NONBLOCK|O_CREAT);
    REST_CHK_FAIL(i4_ret);
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    i4_ret = _rest_mqd_create(&(t_g_rest_mqd.Event_Mqd_Id), MQD_EVENT_REST2VSSP, O_NONBLOCK|O_CREAT);
    REST_CHK_FAIL(i4_ret);
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    if (mq_getattr(t_g_rest_mqd.TV_Mqd_Id, &g_rest_mqd_attr) < 0)
    {
        DBG_ERROR(("[%s %d] ", __func__, __LINE__));
        perror("get attr fail");
        return RESTR_FAIL;
    }
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    REST_IPC_DEBUG("create app msg queue finished!\n");
#else

    i4_ret = _rest_q_create(&(t_g_rest_ipc_msgq.TV_Msgq_Id), TV_IPC_REST_KEY);
    REST_CHK_FAIL(i4_ret);

    i4_ret = _rest_q_create(&(t_g_rest_ipc_msgq.Vssp_Msgq_Id), APP_IPC_REST_KEY);
    REST_CHK_FAIL(i4_ret);

    i4_ret = _rest_q_create(&(t_g_rest_ipc_msgq.Event_Msgq_Id), REST_EVENT_IPC_KEY);
    REST_CHK_FAIL(i4_ret);

    REST_IPC_DEBUG("create app msg queue finished!\n");
    REST_IPC_DEBUG("REST BUFFER_SIZE=%d!\n",REST_BUFFER_SIZE);
#endif
    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));
    return RESTR_OK;
}

INT32 rest_ipc_destroy(VOID)
{
    REST_IPC_DEBUG("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__);
#ifndef SYSTEM_V
    _rest_mqd_destroy(t_g_rest_mqd.TV_Mqd_Id);
    _rest_mqd_destroy(t_g_rest_mqd.Vssp_Mqd_Id);
    _rest_mqd_destroy(t_g_rest_mqd.Event_Mqd_Id);
    c_memset(&t_g_rest_mqd, 0, sizeof(REST_MQD_T));
#else
    _rest_q_destroy(t_g_rest_ipc_msgq.Event_Msgq_Id);
    _rest_q_destroy(t_g_rest_ipc_msgq.Vssp_Msgq_Id);
    _rest_q_destroy(t_g_rest_ipc_msgq.TV_Msgq_Id);

    c_memset(&t_g_rest_ipc_msgq, 0, sizeof(REST_IPC_MSG_T));
#endif
    return RESTR_OK;
}

INT32 rest_send_msg_2_Vssp(REST_MSG_BUF* pSendMsg)
{
    INT32 i4_ret = RESTR_FAIL;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    RETURN_VALUE_IF_FAIL((pSendMsg != NULL), RESTR_FAIL);
#ifndef SYSTEM_V
    i4_ret = _rest_mqd_send_msg(t_g_rest_mqd.Vssp_Mqd_Id, pSendMsg);
    REST_CHK_FAIL(i4_ret);
#else
    i4_ret = _rest_q_send_msg(t_g_rest_ipc_msgq.Vssp_Msgq_Id, pSendMsg);
    REST_CHK_FAIL(i4_ret);
#endif
    return RESTR_OK;
}

INT32 rest_send_msg_2_self(REST_MSG_BUF* pSendMsg)
{
    INT32 i4_ret = RESTR_FAIL;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    RETURN_VALUE_IF_FAIL((pSendMsg != NULL), RESTR_FAIL);
#ifndef SYSTEM_V
        i4_ret = _rest_mqd_send_msg(t_g_rest_mqd.TV_Mqd_Id, pSendMsg);
        REST_CHK_FAIL(i4_ret);
#else
    i4_ret = _rest_q_send_msg(t_g_rest_ipc_msgq.TV_Msgq_Id, pSendMsg);
    REST_CHK_FAIL(i4_ret);
#endif
    return RESTR_OK;
}

INT32 rest_get_msg_from_Vssp(REST_MSG_BUF* pRecvMsg)
{
    INT32 i4_ret = RESTR_FAIL;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    RETURN_VALUE_IF_FAIL((pRecvMsg!=NULL),RESTR_FAIL);
#ifndef SYSTEM_V
        i4_ret = _rest_mqd_receive_msg(t_g_rest_mqd.TV_Mqd_Id,pRecvMsg);
        REST_CHK_FAIL(i4_ret);
#else
    i4_ret = _rest_q_receive_msg(t_g_rest_ipc_msgq.TV_Msgq_Id,pRecvMsg);
    REST_CHK_FAIL(i4_ret);
#endif
    return RESTR_OK;
}

INT32 rest_send_msg_2_Vssp_ori(REST_MSG_BUF_ORI* pSendMsg)
{
    INT32 i4_ret = RESTR_FAIL;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    RETURN_VALUE_IF_FAIL((pSendMsg != NULL), RESTR_FAIL);
#ifndef SYSTEM_V
        REST_IPC_DEBUG("\n%s,%s,%d, not implement\n", __FILE__, __FUNCTION__, __LINE__);
#else
    i4_ret = _rest_q_send_msg_ori(t_g_rest_ipc_msgq.Vssp_Msgq_Id, pSendMsg);
    REST_CHK_FAIL(i4_ret);
#endif
    return RESTR_OK;
}

INT32 rest_get_msg_from_Vssp_ori(REST_MSG_BUF_ORI* pRecvMsg)
{
    INT32 i4_ret = RESTR_FAIL;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    RETURN_VALUE_IF_FAIL((pRecvMsg!=NULL),RESTR_FAIL);
#ifndef SYSTEM_V
        REST_IPC_DEBUG("\n%s,%s,%d, not implement\n", __FILE__, __FUNCTION__, __LINE__);
#else
    i4_ret = _rest_q_receive_msg_ori(t_g_rest_ipc_msgq.TV_Msgq_Id,pRecvMsg);
    REST_CHK_FAIL(i4_ret);
#endif
    return RESTR_OK;
}

INT32 rest_send_msg_2_Vssp_event(REST_MSG_BUF* pSendMsg)
{
    INT32 i4_ret = RESTR_FAIL;

    DBG_API(("\n%s,%s,%d\n", __FILE__, __FUNCTION__, __LINE__));

    RETURN_VALUE_IF_FAIL((pSendMsg != NULL), RESTR_FAIL);
#ifndef SYSTEM_V
    i4_ret = _rest_mqd_send_msg(t_g_rest_mqd.Event_Mqd_Id, pSendMsg);
    REST_CHK_FAIL(i4_ret);
#else
    i4_ret = _rest_q_send_msg(t_g_rest_ipc_msgq.Event_Msgq_Id, pSendMsg);
    REST_CHK_FAIL(i4_ret);
#endif
    return RESTR_OK;
}
