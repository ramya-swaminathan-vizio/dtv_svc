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

#ifndef __REST_IPC_H__
#define __REST_IPC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "u_common.h"
#include "c_dbg.h"

#define TV_IPC_REST_KEY (128 - 5)
#define APP_IPC_REST_KEY (64 - 5)
#define REST_EVENT_IPC_KEY (32 - 5)
#define REST_BUFFER_SIZE 8*1024
#define REST_BUFFER_DATA_SIZE (REST_BUFFER_SIZE - 2* sizeof(long) - 1)
#define REST_URI_LEN 256

typedef unsigned int  uint32_t;


#define RETURN_VALUE_IF_FAIL(p, ret) if(!(p)) \
{DBG_LOG_PRINT(("%s:%d Warning: "#p" failed. \n",   \
__func__,__LINE__)); return(ret);}

#define REST_IPC_DEBUG(fmt,...) do {DBG_INFO(("[MTK REST_IPC][%s]" fmt,__func__,##__VA_ARGS__));}while(0)
#define REST_IPC_ERROR(fmt,...) do {DBG_ERROR(("[MTK REST_IPC Error][%s][%d]" fmt,__func__,__LINE__,##__VA_ARGS__));}while(0)


typedef enum
{
    REST_MSG_INVALID = 0,
    REST_MSG_STUB_INIT,                  //init , to REST
    REST_MSG_STUB_INIT_DONE,             // init done, REST -> TV
    REST_MSG_STUB_UINIT,                 //TV -> REST
    REST_MSG_STUB_UINIT_DONE,            //uninit done , REST -> TV
    REST_MSG_REQUEST_GET,
    REST_MSG_REQUEST_SET,
    REST_MSG_REQUEST_RESET,
    REST_MSG_REQUEST_ACTION,
    REST_MSG_RESPONSE_FROM_TV
}REST_MSG_TYPE;

typedef struct _REST_MSG_BUF{
    long total_size;
    long seq;
    char data_str[REST_BUFFER_SIZE - 2* sizeof(long)];
}REST_MSG_BUF;

typedef struct _REST_MSG_BUF_ORI{
    long mtype;                             //REST_MSG_TYPE
    char uri[REST_URI_LEN];
    char data_str[REST_BUFFER_SIZE];
}REST_MSG_BUF_ORI;

typedef struct _REST_PROGRESS{
    double duration;
    double elapsed;
}REST_PROGRESS;

typedef struct _REST_METADATA{
    char title[128];
    char album[128];
    char artist[128];
    char composer[128];
    char artwork_mimetype[128];
}REST_METADATA;

typedef  enum{
    REST_KEYCODE_NEXT,
    REST_KEYCODE_PREV,
    REST_KEYCODE_PLAY,
    REST_KEYCODE_PAUSE,
    REST_KEYCODE_STOP,
    REST_KEYCODE_REPEAT_TOGGLE,         // repeat toggle, -> REST
    REST_KEYCODE_SHUFFLE_TOGGLE,        // shuffle toggle, ->REST
    REST_KEYCODE_MUTE_TOGGLE,           // mute toggle,  ->REST
    REST_KEYCODE_VOLUME_UP,             // volume up,-> REST
    REST_KEYCODE_VOLUME_DOWN
}REST_KEYEVENT;


extern INT32 rest_ipc_init(VOID);
extern INT32 rest_ipc_destroy(VOID);
extern INT32 rest_send_msg_2_Vssp(REST_MSG_BUF* pSendMsg);
extern INT32 rest_get_msg_from_Vssp(REST_MSG_BUF* pRecvMsg);
extern INT32 rest_send_msg_2_self(REST_MSG_BUF* pSendMsg);

extern INT32 rest_send_msg_2_Vssp_ori(REST_MSG_BUF_ORI* pSendMsg);
extern INT32 rest_get_msg_from_Vssp_ori(REST_MSG_BUF_ORI* pRecvMsg);
extern INT32 rest_send_msg_2_Vssp_event(REST_MSG_BUF* pRecvMsg);

#ifdef __cplusplus
}
#endif
#endif


