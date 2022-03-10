/*----------------------------------------------------------------------------*
 * Copyright Statement:                                                       *
 *                                                                            *
 *   This software/firmware and related documentation ("MediaTek Software")   *
 * are protected under international and related jurisdictions'copyright laws *
 * as unpublished works. The information contained herein is confidential and *
 * proprietary to MediaTek Inc. Without the prior written permission of       *
 * MediaTek Inc., any reproduction, modification, use or disclosure of        *
 * MediaTek Software, and information contained herein, in whole or in part,  *
 * shall be strictly prohibited.                                              *
 * MediaTek Inc. Copyright (C) 2010. All rights reserved.                     *
 *                                                                            *
 *   BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND     *
 * AGREES TO THE FOLLOWING:                                                   *
 *                                                                            *
 *   1)Any and all intellectual property rights (including without            *
 * limitation, patent, copyright, and trade secrets) in and to this           *
 * Software/firmware and related documentation ("MediaTek Software") shall    *
 * remain the exclusive property of MediaTek Inc. Any and all intellectual    *
 * property rights (including without limitation, patent, copyright, and      *
 * trade secrets) in and to any modifications and derivatives to MediaTek     *
 * Software, whoever made, shall also remain the exclusive property of        *
 * MediaTek Inc.  Nothing herein shall be construed as any transfer of any    *
 * title to any intellectual property right in MediaTek Software to Receiver. *
 *                                                                            *
 *   2)This MediaTek Software Receiver received from MediaTek Inc. and/or its *
 * representatives is provided to Receiver on an "AS IS" basis only.          *
 * MediaTek Inc. expressly disclaims all warranties, expressed or implied,    *
 * including but not limited to any implied warranties of merchantability,    *
 * non-infringement and fitness for a particular purpose and any warranties   *
 * arising out of course of performance, course of dealing or usage of trade. *
 * MediaTek Inc. does not provide any warranty whatsoever with respect to the *
 * software of any third party which may be used by, incorporated in, or      *
 * supplied with the MediaTek Software, and Receiver agrees to look only to   *
 * such third parties for any warranty claim relating thereto.  Receiver      *
 * expressly acknowledges that it is Receiver's sole responsibility to obtain *
 * from any third party all proper licenses contained in or delivered with    *
 * MediaTek Software.  MediaTek is not responsible for any MediaTek Software  *
 * releases made to Receiver's specifications or to conform to a particular   *
 * standard or open forum.                                                    *
 *                                                                            *
 *   3)Receiver further acknowledge that Receiver may, either presently       *
 * and/or in the future, instruct MediaTek Inc. to assist it in the           *
 * development and the implementation, in accordance with Receiver's designs, *
 * of certain softwares relating to Receiver's product(s) (the "Services").   *
 * Except as may be otherwise agreed to in writing, no warranties of any      *
 * kind, whether express or implied, are given by MediaTek Inc. with respect  *
 * to the Services provided, and the Services are provided on an "AS IS"      *
 * basis. Receiver further acknowledges that the Services may contain errors  *
 * that testing is important and it is solely responsible for fully testing   *
 * the Services and/or derivatives thereof before they are used, sublicensed  *
 * or distributed. Should there be any third party action brought against     *
 * MediaTek Inc. arising out of or relating to the Services, Receiver agree   *
 * to fully indemnify and hold MediaTek Inc. harmless.  If the parties        *
 * mutually agree to enter into or continue a business relationship or other  *
 * arrangement, the terms and conditions set forth herein shall remain        *
 * effective and, unless explicitly stated otherwise, shall prevail in the    *
 * event of a conflict in the terms in any agreements entered into between    *
 * the parties.                                                               *
 *                                                                             *
 *   4)Receiver's sole and exclusive remedy and MediaTek Inc.'s entire and    *
 * cumulative liability with respect to MediaTek Software released hereunder  *
 * will be, at MediaTek Inc.'s sole discretion, to replace or revise the      *
 * MediaTek Software at issue.                                                *
 *                                                                            *
 *   5)The transaction contemplated hereunder shall be construed in           *
 * accordance with the laws of Singapore, excluding its conflict of laws      *
 * principles.  Any disputes, controversies or claims arising thereof and     *
 * related thereto shall be settled via arbitration in Singapore, under the   *
 * then current rules of the International Chamber of Commerce (ICC).  The    *
 * arbitration shall be conducted in English. The awards of the arbitration   *
 * shall be final and binding upon both parties and shall be entered and      *
 * enforceable in any court of competent jurisdiction.                        *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * $RCSfile: uli_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: Mark Chen $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *
 *
 *
 *---------------------------------------------------------------------------*/

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
#include "uli_custom.h"
#include "u_common.h"
#include "u_dbg.h"
#include "c_fm.h"
#include "c_dbg.h"
#include "u_handle.h"
#include "c_os.h"
#include "c_uc_str.h"
#include "app_util/a_network.h"
#include <cJSON.h>

#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#include "res/app_util/config/a_cfg_custom.h"


#define ULI_MSG_RECEIVE_LEN   (8192)
#define UTV_PLATFORM_MAX_UPDATES                        16
#define SEND_MQD_ULI "/dtv_to_uli"
#define GET_MQD_ULI "/uli_to_dtv"
static struct mq_attr g_rest_mqd_attr;
static mqd_t uli_sendmsgq_Id = 0;
static mqd_t uli_getmsgq_Id = 0;
static HANDLE_T     h_get_msg_thread;
static BOOL isNotifyNTPTimeEvent = TRUE;

#define ULI_UTV_INSTANT_RESET(_t) \
{ \
    (_t)->pv_result = NULL; \
    (_t)->t_arg.pf_user_nfy = NULL; \
    (_t)->t_arg.ui4_mode_count = 1; \
    (_t)->t_arg.ui4_mode[0] = ULI_NEW_PUBLIC_DELIVERY_MODE_INTERNET; \
    (_t)->t_arg.ui4_mode[1] = ULI_NEW_PUBLIC_DELIVERY_MODE_BROADCAST; \
    (_t)->t_arg.b_async = ULI_FALSE; \
    (_t)->t_arg.b_factory = ULI_FALSE; \
    (_t)->t_arg.b_from_server = ULI_FALSE; \
    (_t)->t_arg.b_direct_install = ULI_FALSE; \
    (_t)->t_arg.b_update_mode_configured = ULI_FALSE; \
    (_t)->t_arg.e_action = ULI_NEW_ACTION_NULL; \
    (_t)->t_arg.e_action = ULI_NEW_ACTION_NULL; \
}

typedef struct _uli_utv_arg_
{
    uli_new_update_nfy_fct          pf_user_nfy;
    uli_new_component_action_fct    pf_action;
    unsigned long                   ui4_mode_count;
    unsigned long                   ui4_mode[2];      /* delivery mode */
    int                    b_async;
    int                    b_factory;
    int                    b_from_server;
    int                    b_direct_install;
    int                    b_update_mode_configured;
    ULI_NEW_UPDATE_ACTION_T         e_action;
} ULI_NEW_UTV_ARG_T;
typedef struct _uli_utv_instance_
{
    void*            pv_result;         /* UTV_PUBLIC_RESULT_OBJECT */
    void*            pv_update;         /* UTV_PUBLIC_SCHEDULE */
    UINT32           ui4_avail_time[UTV_PLATFORM_MAX_UPDATES];
    ULI_NEW_UTV_ARG_T    t_arg;
} ULI_UTV_INSTANCE_T;
static ULI_UTV_INSTANCE_T      t_uli_instance;
static ULI_UTV_INSTANCE_T*     pt_instance = &t_uli_instance;
static ULI_NEW_UPDATE_INFO_T      t_update_info;
static uli_download_percent_nfy percent_nfy_fct;
static BOOL b_qda_init = FALSE;
static QdaState qda_state = QdaStateUninitialized;
static VOID _uli_custom_thread_create(VOID);
static INT32 a_uli_custom_consist_device_info(VOID);
static BOOL _uli_custom_check_sn_avaiable(VOID);

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
/* 60 seconds */
#define NAV_UPDATER_ULI_INIT_DELAY_TIME                    ((UINT32)(1000))
/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_init_start
 *
 * Description: Network connected to do qda init
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
#include <time.h>
static   HANDLE_T   h_check_network_connected_timer = NULL_HANDLE;
int cmptime(int year, int month, int day)
{
    time_t now_time = 0, set_time = 0;
    struct tm p;
    p.tm_year = year-1900;
    p.tm_mon = month-1;
    p.tm_mday = day;
    p.tm_hour = 0;
    p.tm_min = 0;
    p.tm_sec = 0;
    p.tm_isdst = 0;
    set_time = mktime(&p);
    time(&now_time);
    return now_time - set_time;
}
static VOID a_uli_init_start_timer_fct(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
)
{
    INT32 i4_ret;
    BOOL  b_is_connect = FALSE;
    a_nw_is_network_connected(&b_is_connect);
    if(b_is_connect)
    {
        FILE* fp;
        char buf[150]="", command[150]="";
        sprintf(command, "ps -ef | grep -w sntp | grep -v grep" );
        if((fp = popen(command,"r")) == NULL)
        {
            perror("Fail to popen\n");
            exit(1);
        }
        if( (fgets(buf,150,fp))== NULL )
        {
            system("/3rd/bin/sntp > /dev/null 2>&1 &");
        }
        pclose(fp);
        if(cmptime(2010, 10, 1)>0){
            i4_ret = c_timer_delete(h_check_network_connected_timer);
            if(TRUE == isNotifyNTPTimeEvent)
            {
                rest_event_notify("system/network_time", 1, "");
                isNotifyNTPTimeEvent = FALSE;
            }
            if (i4_ret != OSR_OK) {
                DBG_LOG_PRINT(("\n%s,%d, a_uli_init_start_timer() called!\n", __FUNCTION__, __LINE__));
            }
            a_uli_agent_init();
        }
    }
}
VOID a_uli_agent_init_wait_NTP(VOID)
{
    INT32 i4_ret;
    if (c_handle_valid(h_check_network_connected_timer) == TRUE) {
        c_timer_delete(h_check_network_connected_timer);
    }
    i4_ret = c_timer_create(&(h_check_network_connected_timer));
    if (i4_ret != OSR_OK) {
        DBG_LOG_PRINT(("\n%s,%d, h_check_network_connected_timer create failed!\n", __FUNCTION__, __LINE__));
        return;
    }

    /* enable the timer */
    c_timer_start(h_check_network_connected_timer,
                  NAV_UPDATER_ULI_INIT_DELAY_TIME,
                  X_TIMER_FLAG_REPEAT,
                  a_uli_init_start_timer_fct,
                  NULL);
}

VOID a_uli_agent_init(VOID)
{
    ULI_NEW_MSG msg = {0};
    UINT8 ui1_sn_check = 0;
    DBG_LOG_PRINT(("\n%s,%d, b_qda_init=%d\n", __FUNCTION__, __LINE__, b_qda_init));
    while(!_uli_custom_check_sn_avaiable())
    {
        ui1_sn_check++;
        a_uli_custom_consist_device_info();
        c_thread_delay(1000);
        DBG_LOG_PRINT(("\n%s,%d,sn empty check count=%x\n", __FUNCTION__, __LINE__, ui1_sn_check));
        if(ui1_sn_check>4)
        {
            break;
        }
    }
    c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
    msg.msgType = ULI_NEW_MSG_INIT;
    a_uli_msg_send_msg(&msg);
    c_memset(&t_update_info, 0, sizeof(ULI_NEW_UPDATE_INFO_T));
    b_qda_init = TRUE;
    DBG_LOG_PRINT(("\n%s,%d, b_qda_init=%d\n", __FUNCTION__, __LINE__, b_qda_init));
}
BOOL a_uli_check_qda_init(VOID)
{
    return b_qda_init;
}

VOID waitForQdaStateTerminating(VOID)
{
    int count=0;
    DBG_LOG_PRINT(("\n%s,%d, qda_state=%d\n", __FUNCTION__, __LINE__, qda_state));
    while(qda_state==QdaStateInitialized && count<50)
    {
        DBG_LOG_PRINT(("\n%s,%d, qda_state=%d\n", __FUNCTION__, __LINE__, qda_state));
        usleep(100*1000);
        count++;
    }
}

INT32 a_uli_qda_term(VOID)
{
    if (c_handle_valid(h_check_network_connected_timer) == TRUE) {
        c_timer_delete(h_check_network_connected_timer);
    }

    if(!b_qda_init)
    {
        DBG_LOG_PRINT(("\n%s,%d, a_uli_qda_term failed! b_qda_init=%d\n", __FUNCTION__, __LINE__, b_qda_init));
        return 1;
    }

    ULI_NEW_MSG msg = {0};
    c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
    msg.msgType = ULI_NEW_QDA_TERM;
    //c_strncpy(msg.reserved, "Test_command1", ULI_MSG_STR_MAX_LEN);
    a_uli_msg_send_msg(&msg);
    c_memset(&t_update_info, 0, sizeof(ULI_NEW_UPDATE_INFO_T));
    waitForQdaStateTerminating();
    b_qda_init = FALSE;
    DBG_LOG_PRINT(("\n%s,%d, a_uli_qda_term success! b_qda_init=%d\n", __FUNCTION__, __LINE__, b_qda_init));
    return 0;
}

VOID a_uli_qda_reset(VOID)
{
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
	msg.msgType = ULI_NEW_QDA_RESET;
	//c_strncpy(msg.reserved, "Test_command1", ULI_MSG_STR_MAX_LEN);
	a_uli_msg_send_msg(&msg);
	c_memset(&t_update_info, 0, sizeof(ULI_NEW_UPDATE_INFO_T));

}


VOID a_uli_check_drmp_update(VOID)
{
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
	msg.msgType = ULI_NEW_MSG_CHECK_DRMP;
	//c_strncpy(msg.reserved, "Test_command1", ULI_MSG_STR_MAX_LEN);
	a_uli_msg_send_msg(&msg);

}

INT32 a_uli_msg_create(VOID)
{
	INT32 i4_ret = ULI_FAIL;
	a_uli_custom_consist_device_info();
    mqd_t mqd_t = mq_open(SEND_MQD_ULI,O_CREAT|O_RDWR, 0666, NULL);
    if (mqd_t < 0)
    {
        perror("mq_open fail");
        i4_ret = ULI_FAIL;
    }
 	DBG_LOG_PRINT(("\n%s,%d,mqd_t=%x\n", __FUNCTION__, __LINE__, mqd_t));
    uli_sendmsgq_Id = mqd_t;
    DBG_LOG_PRINT(("\n%s,%d,uli_sendmsgq_Id=%x\n", __FUNCTION__, __LINE__, uli_sendmsgq_Id));
	if (mq_getattr(uli_sendmsgq_Id, &g_rest_mqd_attr) < 0)
    {
        perror("get attr fail");
        return ULI_FAIL;
    }

	mqd_t = mq_open(GET_MQD_ULI,O_CREAT|O_RDWR, 0666, NULL);
    if (mqd_t < 0)
    {
        perror("mq_open fail");
        i4_ret = ULI_FAIL;
    }
 	DBG_LOG_PRINT(("\n%s,%d,mqd_t=%x\n", __FUNCTION__, __LINE__, mqd_t));
    uli_getmsgq_Id = mqd_t;
    DBG_LOG_PRINT(("\n%s,%d,uli_sendmsgq_Id=%x\n", __FUNCTION__, __LINE__, uli_sendmsgq_Id));
	if (mq_getattr(uli_getmsgq_Id, &g_rest_mqd_attr) < 0)
    {
        perror("get attr fail");
        return ULI_FAIL;
    }
	_uli_custom_thread_create();
    return i4_ret;
}

INT32 a_uli_msg_send_msg(ULI_NEW_MSG* pv_msg)
{
    INT32 i4_ret = ULI_FAIL;
    INT32 retry_counter = 0;

    while(i4_ret == ULI_FAIL ) {
        DBG_LOG_PRINT(("a_uli_msg_send_msg \n\r"));
        i4_ret = mq_send(uli_sendmsgq_Id, (char*)pv_msg, sizeof(ULI_NEW_MSG), 0);
        if (i4_ret == -1) {
            perror("#### SND error");
            if (errno != EAGAIN || retry_counter >= 3) {
                break;
            }
            ++retry_counter;
            c_thread_delay (70);
            DBG_LOG_PRINT(("try again\n\r"));
            //is_timeout(70);
        }
    }

    return i4_ret;
}

INT32 a_uli_msg_receive_msg(ULI_NEW_CALLBACK_MSG* pv_msg)
{
    INT32 i4_ret = ULI_OK;

    while(i4_ret == -1 ) {
        i4_ret = mq_receive(uli_getmsgq_Id, (char*)pv_msg, sizeof(ULI_NEW_CALLBACK_MSG), NULL);
        if (i4_ret == -1) {
            if (errno != EAGAIN) {
                break;
            }
        }
    }

    return i4_ret;
}
extern INT32 x_thread_create(HANDLE_T    *ph_th_hdl,         /* thread handle */
            const CHAR  *ps_name,
            SIZE_T       z_stacksize,
            UINT8        ui1_pri,           /* thread priority */
            x_os_thread_main_fct pf_main,   /* thread's main function */
            SIZE_T       z_arg_size,
            VOID         *pv_arg);
extern VOID x_thread_exit(VOID);
static VOID _uli_custom_thread_main (VOID*  pv_arg)
{
    //INT32   i4_ret = ULI_OK;
    ULI_NEW_CALLBACK_MSG receiveMsg = {0};

    if(uli_getmsgq_Id == -1)
    {
        DBG_LOG_PRINT(("ULI get message handle fail! \n"));
        return;
    }

    while (TRUE)
    {
    		//printf("ULI start run thread333! mqd_t:%x \n",uli_msgq_Id);
        if(mq_receive(uli_getmsgq_Id, (char*)&receiveMsg, ULI_MSG_RECEIVE_LEN, NULL) == -1)
        {
            //DBG_LOG_PRINT(("ULI receive fail! \n"));
        }
        else
        {
            DBG_LOG_PRINT(("dtv msgType:%d\n",(int)receiveMsg.msgType));
			DBG_LOG_PRINT(("dtv msg_value:%d\n",(int)receiveMsg.msg_value));
			DBG_LOG_PRINT(("dtv msg_state:%d\n",receiveMsg.msg_state));
			DBG_LOG_PRINT(("dtv msg_str:%s\n",receiveMsg.msg_str));

            switch((ULI_NEW_MSG_TYPE)receiveMsg.msgType)
            {
            	case ULI_NEW_MSG_UPDATE:
				{
					uli_new_update_nfy_fct uli_cb = NULL;
					uli_cb = pt_instance->t_arg.pf_user_nfy;
					if(receiveMsg.msg_value == ULI_NEW_EVENT_UPDATE_AVAIABLE)
					{
						c_strncpy(t_update_info.ps_version, receiveMsg.msg_str, 32 - 1 );
					}
					(uli_cb) ((ULI_NEW_UPDATE_EVENT_T)receiveMsg.msg_value);
				}
					break;
				case ULI_MSG_UPDATE_PERCENT:
				{
					(percent_nfy_fct) ((INT32)receiveMsg.msg_value);
				}
					break;
                case ULI_NEW_MSG_DRM:
                {
                    break;
                }
				case ULI_MSGQDAINFO:
				{
					if(receiveMsg.msg_value == ULI_QDA_INFO_VERSION)
					{
						qda_state = receiveMsg.msg_state;;
						c_strncpy(t_update_info.ps_qda_version, receiveMsg.msg_str, 32 - 1 );
					}
					else if(receiveMsg.msg_value == ULI_QDA_INFO_SOFTWARE_VERSION)
					{
						qda_state = receiveMsg.msg_state;;
						c_strncpy(t_update_info.ps_software_version, receiveMsg.msg_str, 32 - 1 );
					}
					break;
				}
                default:
                    break;
            }
        }
    }

    x_thread_exit();
}
static VOID _uli_custom_thread_create(VOID)
{
    INT32   i4_ret = ULI_OK;
    i4_ret = x_thread_create(&h_get_msg_thread,
                             "uli_get_msg",
                             4096,
                             128,
                             _uli_custom_thread_main,
                             0,
                             NULL);
	DBG_LOG_PRINT(("i4_ret:%d \n\r",i4_ret));
    //SLOGO_LOG_ON_FAIL(i4_ret);
}

INT32 a_uli_custom_get_update_info(ULI_NEW_UPDATE_INFO_T*            pt_update_info)
{
	pt_update_info->ui4_n_component = 0;
	pt_update_info->ui4_update_index = 0;
	c_strncpy(pt_update_info->ps_version, t_update_info.ps_version, 32 - 1 );
	c_strncpy(pt_update_info->ps_info, "MT5691 Upgrade", 32 - 1 );
	c_strncpy(pt_update_info->ps_qda_version, t_update_info.ps_qda_version, 32 - 1 );
	c_strncpy(pt_update_info->ps_software_version,t_update_info.ps_software_version, 32 - 1 );
	return ULI_OK;
}

INT32 _uli_custom_configure_update_mode_internal(
    ULI_NEW_UPDATE_MODE_T*    pt_mode
)
{
    ULI_NEW_UTV_ARG_T*        pt_uli_arg;
    INT32                 ret;

    if (!pt_mode)
    {
        return ULI_INV_ARG;
    }

    /* alrady configured ==> do nothing */
    if (TRUE
        == (pt_instance->t_arg.b_update_mode_configured))
    {
        return ULI_OK;
    }

    ULI_UTV_INSTANT_RESET(pt_instance);

    pt_uli_arg = &(pt_instance->t_arg);

    pt_uli_arg->pf_user_nfy = pt_mode->pf_nfy;
    pt_uli_arg->pf_action = pt_mode->pf_action;

    pt_uli_arg->b_factory = pt_mode->b_factory;
    pt_uli_arg->b_from_server = pt_mode->b_from_server;
    pt_uli_arg->b_direct_install = pt_mode->b_direct_install;

    if ((pt_mode->e_action == ULI_NEW_ACTION_APPROVE_ALL_OPTIONAL) ||
        (pt_mode->e_action == ULI_NEW_ACTION_REJECT_ALL_OPTIONAL))
    {
        pt_uli_arg->e_action = pt_mode->e_action;
    }

    if (pt_mode->e_delivery == ULI_NEW_DELIVERY_INTERNET_BROADCAST)
    {
        pt_uli_arg->ui4_mode[0] = ULI_NEW_PUBLIC_DELIVERY_MODE_INTERNET;
        pt_uli_arg->ui4_mode[1] = ULI_NEW_PUBLIC_DELIVERY_MODE_BROADCAST;
        pt_uli_arg->ui4_mode_count = 2;
    }
    else if (pt_mode->e_delivery == ULI_NEW_DELIVERY_INTERNET_BROADCAST_ASYNC)
    {
        pt_uli_arg->b_async = ULI_TRUE;
        pt_uli_arg->ui4_mode[0] = ULI_NEW_PUBLIC_DELIVERY_MODE_INTERNET;
        pt_uli_arg->ui4_mode[1] = ULI_NEW_PUBLIC_DELIVERY_MODE_BROADCAST;
        pt_uli_arg->ui4_mode_count = 2;
    }
    else if (pt_mode->e_delivery == ULI_NEW_DELIVERY_INTERNET_ASYNC)
    {
        pt_uli_arg->b_async = ULI_TRUE;
    }
    else if (pt_mode->e_delivery == ULI_NEW_DELIVERY_BROADCAST_ASYNC)
    {
        pt_uli_arg->b_async = ULI_TRUE;
        pt_uli_arg->ui4_mode[0] = ULI_NEW_PUBLIC_DELIVERY_MODE_BROADCAST;
    }
    else if (pt_mode->e_delivery == ULI_NEW_DELIVERY_BROADCAST)
    {
        pt_uli_arg->ui4_mode[0] = ULI_NEW_PUBLIC_DELIVERY_MODE_BROADCAST;
    }
    else if (pt_mode->e_delivery == ULI_NEW_DELIVERY_INTERNET)
    {
        /* noop */
    }
    else if (pt_mode->e_delivery == ULI_NEW_DELIVERY_FILE)
    {
        pt_uli_arg->ui4_mode[0] = ULI_NEW_PUBLIC_DELIVERY_MODE_FILE;
    }
    else if (pt_mode->e_delivery == ULI_NEW_DELIVERY_FILE_ASYNC)
    {
        pt_uli_arg->b_async = ULI_TRUE;
        pt_uli_arg->ui4_mode[0] = ULI_NEW_PUBLIC_DELIVERY_MODE_FILE;
    }
    else
    {
        return ULI_INV_ARG;
    }

    /* attempt a new update session */
    pt_instance->pv_update = NULL;
    ret = ULI_OK;


    pt_uli_arg->b_update_mode_configured = ULI_TRUE;


    return ret;
}
INT32 a_uli_custom_check_sw_update_avaiable(
    ULI_NEW_UPDATE_MODE_T*    pt_mode
)
{
    INT32                 ret;
    uli_new_update_nfy_fct uli_cb = NULL;
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
    ret = _uli_custom_configure_update_mode_internal (pt_mode);
    if (ret != ULI_OK)
    {
        return ret;
    }

    uli_cb = pt_instance->t_arg.pf_user_nfy;

    do
    {

        if (uli_cb)
        {
            (uli_cb) (ULI_NEW_EVENT_CHECKING_UPDATE);
        }
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_SOURCE;
		c_strncpy(msg.reserved, "Network", ULI_MSG_STR_MAX_LEN);
		a_uli_msg_send_msg(&msg);

		c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		if(pt_mode->e_action == ULI_ACTION_BGM)
		{
			msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_IS_VALID_BGM;
		}
		else
		{
			msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_IS_VALID;
		}
		a_uli_msg_send_msg(&msg);


    }while (FALSE);

    return ret;
}
INT32 a_uli_qda_submit_data(CHAR ps_user_info[])
{
    INT32 ret=0;
    ULI_NEW_MSG msg = {0};
    c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
    msg.msgType = ULI_NEW_QDA_SUBMIT_DATA;
    c_strncpy(msg.user_info, ps_user_info, 1023);
    a_uli_msg_send_msg(&msg);
    return ret;
}

INT32 a_uli_custom_check_usb_update_avaiable(
    ULI_NEW_UPDATE_MODE_T*    pt_mode,CHAR      *ps_usb_path
)
{
    INT32                 ret;
    uli_new_update_nfy_fct uli_cb = NULL;
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
    ret = _uli_custom_configure_update_mode_internal (pt_mode);
    if (ret != ULI_OK)
    {
        return ret;
    }

    uli_cb = pt_instance->t_arg.pf_user_nfy;

    do
    {

        if (uli_cb)
        {
            (uli_cb) (ULI_NEW_EVENT_CHECKING_UPDATE);
        }
		msg.msgType = ULI_NEW_MSG_USB_UPDATE;
		//msg.msg_value = ULI_NEW_MSG_USB_UPDATE;
		c_strncpy(msg.reserved, "Usb", ULI_MSG_STR_MAX_LEN);
		c_strncpy(msg.usb_update_path, ps_usb_path, 511);
		a_uli_msg_send_msg(&msg);

		c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_IS_VALID;
		a_uli_msg_send_msg(&msg);
    }while (FALSE);

    return ret;
}

INT32 a_uli_custom_triger_usb_download_and_install(
    ULI_NEW_UPDATE_MODE_T*    pt_mode
)
{
    INT32                 ret;
    uli_new_update_nfy_fct uli_cb = NULL;
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
    ret = _uli_custom_configure_update_mode_internal (pt_mode);
    if (ret != ULI_OK)
    {
        return ret;
    }

    uli_cb = pt_instance->t_arg.pf_user_nfy;

    do
    {
		c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_INSTALL;
		a_uli_msg_send_msg(&msg);


    }while (FALSE);

    return ret;
}

INT32 a_uli_custom_triger_usb_cmd_install(VOID)
{
    INT32                 ret = 0;
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));

    do
    {
		c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
		msg.msgType = ULI_NEW_MSG_USB_UPDATE;
		msg.msg_value = ULI_NEW_MSG_CHECK_USB_CMD_INSTALL;
		a_uli_msg_send_msg(&msg);


    }while (FALSE);

    return ret;
}

INT32 a_uli_custom_set_oem_msg(CHAR* str_msg,INT32 i4_length)
{
    INT32                 ret = 0;
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));

    do
    {
		c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
		msg.msgType = ULI_NEW_MSG_USB_UPDATE;
		msg.msg_value = ULI_NEW_MSG_USB_CMD_SET_OEM_MSG;
		if(i4_length < (ULI_MSG_MAX_LEN - 1))
		{
			strncpy(msg.usb_update_path, str_msg, i4_length + 1);
		}
		else
		{
			strncpy(msg.usb_update_path, str_msg, ULI_MSG_MAX_LEN - 1);
		}
		a_uli_msg_send_msg(&msg);


    }while (FALSE);

    return ret;
}



INT32 a_uli_custom_triger_sw_download_and_install(
    ULI_NEW_UPDATE_MODE_T*    pt_mode
)
{
    INT32                 ret;
    uli_new_update_nfy_fct uli_cb = NULL;
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
    ret = _uli_custom_configure_update_mode_internal (pt_mode);
    if (ret != ULI_OK)
    {
        return ret;
    }

    uli_cb = pt_instance->t_arg.pf_user_nfy;

    do
    {
		c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
		msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
		msg.msg_value = ULI_NEW_MSG_CHECK_UPDATE_INSTALL;
		a_uli_msg_send_msg(&msg);


    }while (FALSE);

    return ret;
}

INT32 a_uli_custom_get_download_percentage(uli_download_percent_nfy percent_nfy)
{
	ULI_NEW_MSG msg = {0};
	c_memset(&msg, 0, sizeof(ULI_NEW_MSG));
	msg.msgType = ULI_NEW_MSG_CHECK_UPDATE_VALID;
	msg.msg_value = ULI_NEW_MSG_DOWNLOAD_PRECENT;
	a_uli_msg_send_msg(&msg);
	percent_nfy_fct = percent_nfy;
	return ULI_OK;
}
extern CHAR* sys_cust_get_usb_upg_version(VOID);
static INT32 a_uli_custom_consist_device_info(VOID)
{
	cJSON *proot;   //,*device_info;
	CHAR *str_device =NULL;
	CHAR  string_id[32] ={0};
	CHAR     model_name[32] = {0};
	CHAR     model_group_name[16 + 1] = {0};
	UINT32 ui4_buff_len = 0;
	UINT32      ui4_group_id = 0;
	CHAR            s_mac_str[64];
	UINT8 ui1_temp[6] = {0};
	CHAR s_version[32] = {0};
	UINT32 u32_index = 0;
	FILE * fl ;
	FILE*  fl_tmp_sn = NULL;
	INT32 i4_file_len = 0;
	/****/
	FILE*		fl_pre = NULL;
	CHAR*	   device_info_buf = NULL;
	INT32 i4_ret = ULIR_OK;
	cJSON *proot_pre,*pc_pre_sn,*pc_pre_id;
	CHAR			s_tmn[128] = {0};

	INT32 ui4_read_cnt = 0;
	/****/
	a_uli_get_serial_number((UINT8 *)string_id, &ui4_buff_len);
	if(string_id[0] == 0)
	{
		{
			fl_tmp_sn = fopen("/data/uli/sn", "r");
			DBG_LOG_PRINT(("check sn file  \n\r"));
			if (fl_tmp_sn != NULL)
			{
				fseek(fl_tmp_sn, 0, SEEK_END);
				i4_file_len = ftell(fl_tmp_sn);
				fseek(fl_tmp_sn, 0, SEEK_SET);
				if(i4_file_len > 15)
				{
					i4_file_len = 15;
				}
				DBG_LOG_PRINT(("i4_file_len:%d  \n\r",i4_file_len));
				if (fread((VOID*)string_id,i4_file_len,1, fl_tmp_sn) != 0)
				{
					DBG_LOG_PRINT(("string_id %s\n\r", string_id));
				}

				fclose (fl_tmp_sn);
				if(string_id[0] == '0' &&
				   string_id[1] == '0' &&
				   string_id[2] == '0' &&
				   string_id[3] == '0' &&
				   string_id[4] == '0')
				{
					DBG_LOG_PRINT(("empty string \n\r"));
					c_memset(string_id, 0, 32);
				}
				else
				{
					for ( u32_index = 0; 0 != string_id[ u32_index ] && '\r' != string_id[ u32_index ] && '\n' != string_id[ u32_index ]; u32_index++ );
					string_id[ u32_index ] = 0;
				}
			}
		}

		if((string_id[0] == 0)&&access("/data/uli/device_info.json",0) == 0)
		{
			do{
				DBG_LOG_PRINT(("check pre file \n\r"));
				fl_pre = fopen("/data/uli/device_info.json", "r");
				if (fl_pre == NULL)
				{
					break;
				}
				i4_ret = fseek(fl_pre, 0, SEEK_END);
				i4_file_len = ftell(fl_pre);
			   if(NULL ==( device_info_buf = (CHAR*)malloc(i4_file_len + 1)))
				{
					DBG_LOG_PRINT((" failed to memalloc memory!\n"));
					break;
				}
			   fseek(fl_pre, 0, SEEK_SET);
			   memset(device_info_buf,0,i4_file_len + 1);
				ui4_read_cnt = fread(device_info_buf,i4_file_len,1,fl_pre);
				if(ui4_read_cnt <= 0)
				{
					DBG_LOG_PRINT(("failed to read content!\n"));
					break;
				}

				if(NULL == (proot_pre = cJSON_Parse(device_info_buf)))
				{
					DBG_LOG_PRINT(("failed to parse content cJSON_Parse !\n"));
					break;
				}
				pc_pre_sn = cJSON_GetObjectItem(proot_pre,"esn");
				DBG_LOG_PRINT(("line:%d esn:%s legth:%d \n",__LINE__,pc_pre_sn->valuestring,c_strlen(pc_pre_sn->valuestring)));
				if(!(pc_pre_sn&&c_strlen(pc_pre_sn->valuestring) > 0))
				{
					 cJSON_Delete(proot_pre);
					break;
				}
               c_strncpy(string_id,
               pc_pre_sn->valuestring,
               c_strlen(pc_pre_sn->valuestring));
				pc_pre_id = cJSON_GetObjectItem(proot_pre,"id");
				DBG_LOG_PRINT(("line:%d id:%s length:%d \n",__LINE__,pc_pre_id->valuestring,c_strlen(pc_pre_id->valuestring)));
				if(!(pc_pre_id&&c_strlen(pc_pre_id->valuestring) > 0))
				{
					 cJSON_Delete(proot_pre);
					break;
				}
				 cJSON_Delete(proot_pre);
			}while(0);
			if(device_info_buf != NULL)
			{
				free(device_info_buf);
			}

		}

	}
	else
	{
		if (access("/data/uli/sn", F_OK) != 0)
		{
			c_snprintf(s_tmn, 128, "echo \"%s\" > /data/uli/sn", (char *)string_id);

    		system(s_tmn);
		}
	}
	c_memset(s_mac_str,0,sizeof(CHAR)*64);
	a_cfg_cust_drv_read_RJ45_value(ui1_temp);
	if(ui1_temp[0] == 0 &&
   		ui1_temp[1] == 0 &&
   		ui1_temp[2] == 0 &&
   		ui1_temp[3] == 0 &&
   		ui1_temp[4] == 0 &&
   		ui1_temp[5] == 0)
	{
    	a_nw_get_mac_addr((CHAR*)NI_ETHERNET_0, ui1_temp);
	}

	c_sprintf ( s_mac_str,
                "%02X:%02X:%02X:%02X:%02X:%02X\0",
                ui1_temp[0],
                ui1_temp[1],
                ui1_temp[2],
                ui1_temp[3],
                ui1_temp[4],
                ui1_temp[5]
               );
	a_cfg_custom_get_model_name(model_name);
	proot = cJSON_CreateObject();
	if (!proot)
    {
        return ULI_INV_ARG;
    }
	c_strncpy(s_version, sys_cust_get_usb_upg_version(), (SIZE_T)31);
	for ( u32_index = 0; 0 != s_version[ u32_index ] && '\r' != s_version[ u32_index ] && '\n' != s_version[ u32_index ]; u32_index++ );
		s_version[ u32_index ] = 0;

	a_cfg_custom_get_model_group_id(&ui4_group_id);
	c_sprintf(model_group_name,"%x",ui4_group_id);
	DBG_LOG_PRINT(("%s_%d string_id:%s,model:%s,subModel:%s,mac:%s,swVersion:%s \n",__FUNCTION__,__LINE__,
		(char *)string_id,MODEL_NAME,(char *)model_name,(char *)s_mac_str,sys_cust_get_usb_upg_version()));

	//cJSON_AddItemToObject(proot, "device", device_info = cJSON_CreateObject());

	cJSON_AddStringToObject(proot, "id",(char *)string_id);
	cJSON_AddStringToObject(proot, "esn", (char *)string_id);

	cJSON_AddStringToObject(proot, "model", MODEL_NAME);
	cJSON_AddStringToObject(proot, "subModel", (char *)model_name);
	cJSON_AddStringToObject(proot, "brand", "Vizio");

	cJSON_AddStringToObject(proot, "mac", (char *)s_mac_str);
	cJSON_AddStringToObject(proot, "swVersion", (char *)s_version);
	str_device = cJSON_Print(proot);
    DBG_LOG_PRINT(("str_device %s\n\r", str_device));
	if (0 == access("/data/uli/device_info.json", F_OK))
    {
        system("rm /data/uli/device_info.json;sync");
    }
	fl = fopen ("/data/uli/device_info.json","w+");
    if (fl == NULL)
    {
        DBG_INFO(("\n---Open wzd_reg_info failed!---\n"));
        return ULI_INV_ARG;
    }
    fprintf(fl, "%s\n", str_device);
    fclose (fl);
	if(fl_pre != NULL)
	{
		fclose (fl_pre);
	}
	if(str_device != NULL)
	{
		free(str_device);
	}
    cJSON_Delete(proot);
	return ULI_OK;
}

static BOOL _uli_custom_check_sn_avaiable(VOID)
{
	FILE*		fl = NULL;
	CHAR*	   device_info_buf = NULL;
	INT32 i4_ret = ULIR_OK;
	INT32 i4_file_len = 0;
	INT32 ui4_read_cnt = 0;
	cJSON *proot,*pc_sn,*pc_id;
	fl = fopen("/data/uli/device_info.json", "r");
	if (fl == NULL)
	{
		return FALSE;
	}
	i4_ret = fseek(fl, 0, SEEK_END);
	i4_file_len = ftell(fl);
   if(NULL ==( device_info_buf = (CHAR*)malloc(i4_file_len + 1)))
	{
		DBG_LOG_PRINT((" failed to memalloc memory!\n"));
		return FALSE;
	}
   fseek(fl, 0, SEEK_SET);
   memset(device_info_buf,0,i4_file_len + 1);
	ui4_read_cnt = fread(device_info_buf,i4_file_len,1,fl);
	if(ui4_read_cnt <= 0)
	{
		DBG_LOG_PRINT(("failed to read content!\n"));
		fclose (fl);
		free(device_info_buf);
		return FALSE;
	}

	if(NULL == (proot = cJSON_Parse(device_info_buf)))
	{
		DBG_LOG_PRINT(("failed to parse content cJSON_Parse !\n"));
		fclose (fl);
		free(device_info_buf);
		return FALSE;
	}
	pc_sn = cJSON_GetObjectItem(proot,"esn");
	DBG_LOG_PRINT(("esn:%s legth:%d \n",pc_sn->valuestring,c_strlen(pc_sn->valuestring)));
	if(!(pc_sn&&c_strlen(pc_sn->valuestring) > 0))
	{
		cJSON_Delete(proot);
		fclose (fl);
		free(device_info_buf);
		return FALSE;
	}
	pc_id = cJSON_GetObjectItem(proot,"id");
	DBG_LOG_PRINT(("id:%s length:%d \n",pc_id->valuestring,c_strlen(pc_id->valuestring)));
	if(!(pc_id&&c_strlen(pc_id->valuestring) > 0))
	{
		cJSON_Delete(proot);
		fclose (fl);
		free(device_info_buf);
		return FALSE;
	}
	cJSON_Delete(proot);
	fclose (fl);
	free(device_info_buf);
	return TRUE;
}
