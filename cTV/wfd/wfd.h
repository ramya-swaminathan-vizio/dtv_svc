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
 *                                                                            *
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
 * $RCSfile: wfd.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: ----------$
 * $SWAuthor: cheng.shen $
 * $MD5HEX: --------- $
 *
 * Description: 
 *         This header file contains public interfaces, constant and type 
 *         definitions of the Widget Library.
 *---------------------------------------------------------------------------*/


#ifndef _WFD_H_
#define _WFD_H_



/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "stdlib.h"
#include "unistd.h"
#include "string.h"
#include "c_os.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_cli.h"
#include "c_aee.h"
#include "c_appman.h"
#include "c_wgl.h"
#include "c_fe.h"
#include "c_gl.h"
#include "c_pcl.h"
#include "c_wgl_image.h"
#include "c_uc_str.h"
#include "c_wgl.h"

#include "u_common.h"
#include "u_handle.h"
#include "u_cli.h"
#include "u_uc.h"
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "u_pcl.h"
#include "u_btn_map.h"
#include "u_sys_name.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_uniform.h"
#include "u_wgl_bdr_raised.h"
#include "u_dbg.h"

#include "amb/a_amb.h"
#include "am/a_am.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_icl.h"
#include "app_util/a_tv.h"

#include "app_util/lang/a_lang.h"

#include "../../dev/app_util/a_dbg_level_app.h"
#include "a_wfd.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
 
typedef enum _WFD_DEV_INFO_TYPE_T
{
    WFD_DEV_NAME = 0,        /**< DMR stopped state */
    WFD_DEV_MAC ,  
    WFD_DEV_TYPE,
    WFD_DEV_PORT,
    WFD_DEV_ALL
}WFD_DEV_INFO_TYPE_T;

typedef enum
{    
    WFD_MSG_DIRECT_ON,
    WFD_MSG_MAIN_EXIT,
    WFD_MSG_WGL_NFY ,
    WFD_MSG_ICL,
    WFD_MSG_VOL_CHG,
    WFD_MSG_SEND_CONTEXT,
    WFD_MSG_FIND,
    WFD_MSG_STOP_FIND,
    WFD_MSG_P2P_CONNECTED,//wait for multi client IN
    WFD_MSG_P2P_DISCNNECT,
    
    WFD_MSG_P2P_ENABLED,//10
    WFD_MSG_P2P_DISABLED,
    
    WFD_MSG_P2P_IP_GET,
    WFD_MSG_P2P_DEVICE_FOUND,
    WFD_MSG_P2P_DEVICE_LOST,
    
    WFD_MSG_P2P_START_CONNECT,
    WFD_MSG_P2P_GROUP_START,
    WFD_MSG_P2P_GROUP_REMOVED,
    
    WFD_MSG_P2P_GROUP_DISAPPEAR,
    
    WFD_MSG_P2P_START_DISABLE,
    WFD_MSG_P2P_DISABLE_OK ,//20
    WFD_MSG_P2P_DISABLE_FAILED,
        
    WFD_MSG_P2P_START_ENABLE,
    WFD_MSG_P2P_ENABLE_OK ,
    WFD_MSG_P2P_ENABLE_FAILED,
    
    WFD_MSG_P2P_PBC_REQ, //wait for pbc request     
    WFD_MSG_P2P_ENTER_PIN_REQ,
    WFD_MSG_P2P_SHOW_PIN_REQ ,
    WFD_MSG_P2P_NEG_REQ,
    
    WFD_MSG_P2P_ENTER_PIN,  
    WFD_MSG_P2P_SHOW_PIN, //30   
    //device
    WFD_MSG_DEVICE_REMOVE,
    WFD_MSG_DEVICE_PLUG,
    WFD_MSG_CONN_TIME_OUT,
    WFD_MSG_VIEW_CONNECTED_TO_STA, 
    WFD_MSG_VIEW_TO_STA,
    
    WFD_MSG_VIEW_TO_CONN,
    WFD_MSG_VIEW_CONFIRM_DIS_P2P,
    WFD_MSG_VIEW_DISCONNECT_P2P,
    WFD_MSG_VIEW_DISCONNECT_P2P_OK,
    WFD_MSG_VIEW_DISCONNECT_P2P_FAIL,//40
    WFD_MSG_VIEW_CONFIRM_DIS_RTSP,
    
    WFD_MSG_VIEW_STOP_RTSP,
    WFD_MSG_VIEW_STOP_RTSP_FAIL,
    WFD_MSG_VIEW_STOP_RTSP_OK,
    
    WFD_MSG_VIEW_START_RTSP,
    WFD_MSG_VIEW_START_RTSP_OK,
    WFD_MSG_VIEW_START_RTSP_FAIL,
    
    WFD_MSG_VIEW_SHOW_TO_PIN,
    WFD_MSG_VIEW_ENTER_TO_PIN,
    WFD_MSG_VIEW_SHOW_TO_PIN_REQ,
    
    WFD_MSG_VIEW_ENTER_TO_PIN_REQ,
    WFD_MSG_VIEW_INVALID_PIN,
    
    WFD_MSG_VIEW_TO_PLAY,
    
    WFD_MSG_VIEW_MSG_PAUSED,
    WFD_MSG_VIEW_MSG_PAUSE_FAIL,
    WFD_MSG_VIEW_MSG_PLAYD,
    WFD_MSG_VIEW_MSG_PLAY_FAIL,
    WFD_MSG_VIEW_MSG_TRY_CONN_FAIL,

	WFD_MSG_AP_STA_CONNECTED,
	WFD_MSG_AP_STA_DISCONNECTED,
    WFD_MSG_RTSP_TEARDOWN,
    
    WFD_MSG_END
}WFD_MSG_T;

typedef enum
{
    WFD_COND_NOT_INIT = 0,
    WFD_COND_PAUSE , 
    WFD_COND_RESUME,
#ifdef APP_MENU_WFD_COEXIST
    WFD_COND_PAUSED_WAIT_SVC,
#endif
    WFD_COND_END
}WFD_COND_T;

typedef enum
{
    WFD_P2P_CONN_CONNECTING = 0,
    WFD_P2P_CONN_CONNECTED , 
    WFD_P2P_CONN_DISCONNECT,
    WFD_P2P_CONN_DISCONNECTING,
    WFD_P2P_CONN_END
}WFD_P2P_CONN_STA_T;

typedef enum
{
    WFD_RTSP_CONN_START,
    WFD_RTSP_CONN_PLAY,
    WFD_RTSP_CONN_PAUSE,
    WFD_RTSP_CONN_STOP,
    WFD_RTSP_CONN_END
}WFD_RTSP_CONN_STA_T;

typedef enum
{
    WFD_P2P_ENABLING,
    WFD_P2P_ENABLED,
    WFD_P2P_DISABLING,
    WFD_P2P_DISABLED,
    WFD_P2P_END 
}WFD_P2P_STA_T;

typedef enum
{
    //start
    WFD_CMD_RESUME = 0,
    WFD_CMD_PAUSE,
    WFD_CMD_ENABLE,
    WFD_CMD_DISABLE, 
    WFD_CMD_FIND,
    WFD_CMD_STOP_FIND,
    WFD_CMD_PBC,
    WFD_CMD_PBC_ACCEPT,
    WFD_CMD_SHOW_PIN,
    WFD_CMD_ENTER_PIN,
    WFD_CMD_PIN_CONNECT,
    WFD_CMD_DISCONNECT_P2P,
    WFD_CMD_CANCEL_CONNECT,
    WFD_CMD_STOP_RTSP,
    WFD_CMD_START_RTSP,
    WFD_CMD_STOP_TIMER,
    WFD_CMD_PAUSE_TV,
    
    WFD_CMD_RESUME_TV,
    
    WFD_CMD_PAUSE_RTSP,
    
    WFD_CMD_VIEW_DO_MSG,
    
    WFD_CMD_PLAY,

	WFD_CMD_PIN_GET,
    
    WFD_CMD_END
}WFD_CMD_T;

typedef enum 
{
    WFD_SEND_RETRY_TYPE_ONCE = 0,             /*Try 1 time*/
    WFD_SEND_RETRY_TYPE_NORMAL,               /*Try 5 time*/
    WFD_SEND_RETRY_TYPE_IMPORTANT,            /*Try 10 time*/
    WFD_SEND_RETRY_TYPE_CRITICAL              /*Try 20 time*/
} WFD_SEND_RETRY_TYPE_T;

typedef struct _WFD_VOL_UPD_INFO_T
{
    BOOL        b_volume_up;
    BOOL        b_volume_down;
    BOOL        b_cec_sac;
    INT16       i2_vol;
} WFD_VOL_UPD_INFO_T;


typedef INT32 (*wfd_view_do_msg)(
        WFD_MSG_T e_msg_id, VOID* pv_msg_param);
typedef VOID  (*wfd_event_handler) (
        VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4);

typedef struct _WFD_SEND_CTX_T
{
    wfd_event_handler           pf_event_handler;
    VOID*                       pv_param1;
    VOID*                       pv_param2;
    VOID*                       pv_param3;
    VOID*                       pv_param4;
} WFD_SEND_CTX_T;

#define  WFD_DBG_ERR(_expr)                                                      \
    do{                                                                            \
         if(_expr != 0)                                                              \
         {                                                                           \
             DBG_LOG_PRINT(("%s,%d,%s,%d\n\r",  \
                         __FILE__, __LINE__, __FUNCTION__,_expr));                    \
         }                                                                           \
    } while (0)

#define  WFD_DBG_LOG(_expr)                                                      \
             do{                                                                            \
                  if(wfd_get_log())                                                              \
                  {                                                                           \
                      DBG_LOG_PRINT(("%s,%d,%s,%d\n\r", __FILE__, __LINE__, __FUNCTION__,_expr));\
                  }                                                                           \
             } while (0)
         
#define  WFD_DBG_LOG_EX(_expr1,_expr2)                                                      \
               do{                                                                            \
                    if(wfd_get_log())                                                              \
                    {                                                                           \
                        DBG_LOG_PRINT(("%s,%d,%s,%s,%d\n\r", __FILE__, __LINE__, __FUNCTION__,_expr1,_expr2));\
                    }                                                                           \
               } while (0)
#define WFD_DBG_ERR_EX(_stmt, _i4_ok)                                                \
                 {                                                                               \
                     INT32    _i4_ret;                                                           \
                     _i4_ret = _stmt;                                                            \
                     if((_i4_ok) != (_i4_ret))                                                   \
                     {                                                                           \
                         DBG_LOG_PRINT(("%s,%d,%s,%d\n\r",  \
                                     __FILE__, __LINE__, __FUNCTION__,_i4_ret));                  \
                     }                                                                           \
                 }                                                                               

#define  WFD_RET_ON_ERR(_expr)                                                      \
    do{                                                                            \
         if(_expr != 0)                                                              \
         {                                                                           \
             DBG_LOG_PRINT(("%s,%d,%s,%d\n\r",  \
                         __FILE__, __LINE__, __FUNCTION__,_expr));                    \
             return WFDR_FAIL;                                                       \
         }                                                                           \
    } while (0)

#define  WFD_RET_VOID_ON_ERR(_expr)                                                      \
             do{                                                                            \
                  if(_expr != 0)                                                              \
                  {                                                                           \
                      DBG_LOG_PRINT(("%s,%d,%s,%d\n\r",  \
                                  __FILE__, __LINE__, __FUNCTION__,_expr));                    \
                      return;                                                       \
                  }                                                                           \
             } while (0)

#define WFD_RET_ON_ERR_EX(_stmt, _i4_ok)                                                \
        {                                                                               \
            INT32    _i4_ret;                                                           \
            _i4_ret = _stmt;                                                            \
            if((_i4_ok) != (_i4_ret))                                                   \
            {                                                                           \
                DBG_LOG_PRINT(("%s,%d,%s,%d\n\r",  \
                            __FILE__, __LINE__, __FUNCTION__,_i4_ret));                  \
                return WFDR_FAIL;                                                       \
            }                                                                           \
        }                                                                               

#define MAX_WIDGET_MSG_DELAY_TOLERANCE 100

#define DEVICE_INFO_ARR_LEN (20)

#define WFD_MAX_DEVICE_NUM (20)

typedef struct _WFD_DEVICE_INFO_T
{
    char   ps_device_name[DEVICE_INFO_ARR_LEN]; 
    char   ps_device_mac[DEVICE_INFO_ARR_LEN]; 
    char   ps_device_ip[DEVICE_INFO_ARR_LEN];    
    char   ps_device_type[DEVICE_INFO_ARR_LEN]; 
    BOOL   b_connect; 
    INT32  i4_device_port;
}WFD_DEVICE_INFO_T;

typedef struct _WFD_MAIN_T
{
    HANDLE_T h_app;
    HANDLE_T                    h_ip_timer;
    HANDLE_T                    h_main_svctx;
    HANDLE_T                    h_sub_svctx;
#ifdef APP_TV_AV_SCART_BYPASS_SUPPORT
    HANDLE_T                    h_tvbypass_svctx;
    HANDLE_T                    h_mnbypass_svctx;
#endif  
    
#ifdef APP_NAV_REC_SUPPORT
    HANDLE_T                    h_rec_svctx;
#endif

    HANDLE_T                    h_cable_svl;
    HANDLE_T                    h_air_svl;
	HANDLE_T                    h_iom;

    // init
    INT32    connect_idx;
    WFD_P2P_CONN_STA_T e_p2p_conn_sta;
    WFD_RTSP_CONN_STA_T e_rtsp_conn_sta;
    WFD_P2P_STA_T  e_p2p_sta;
	BOOL     b_enable;
	BOOL     b_ip_get;
    WFD_COND_T e_wfd_cond;    

    //for volume
    UINT16    ui2_icl_nfy_id;
    INT8      i1_cec_vol;
    
}WFD_MAIN_T;

typedef struct _WFD_WIDGET_MSG_T
{
	UINT32 ui4_msg;
	VOID*  pv_param1;
	VOID*  pv_param2;
}WFD_WIDGET_MSG_T;

typedef struct _WFD_CMD_CONT_T
{
	WFD_CMD_T e_cmd;
	VOID*  pv_param;
    
}WFD_CMD_CONT_T;

extern BOOL b_do_this;

#ifdef APP_WFD_SUPPORT
#undef DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE			  wfd_get_dbg_level()
#endif

BOOL    wfd_app_is_active(VOID);

VOID    wfd_app_set_p2p_sta(WFD_P2P_STA_T e_sta);

VOID    wfd_app_set_p2p_conn_sta(WFD_P2P_CONN_STA_T e_sta);
VOID    wfd_app_set_rtsp_conn_sta(WFD_RTSP_CONN_STA_T e_sta);
WFD_P2P_STA_T  wfd_app_get_p2p_sta(VOID);

WFD_P2P_CONN_STA_T  wfd_app_get_p2p_conn_sta(VOID);
WFD_RTSP_CONN_STA_T  wfd_app_get_rtsp_conn_sta(VOID);

INT32  wfd_app_get_conn_idx(VOID);
UINT16  wfd_get_dbg_level(VOID);

VOID    wfd_set_dbg_level(UINT16  ui2_db_level);

INT32   wfd_reg_view_nfy(wfd_view_do_msg pf_handle_msg);

VOID    wfd_main_cmd_do(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4);

VOID    wfd_main_handle_msg(VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4);

INT32 wfd_app_get_conn_device_info(WFD_DEVICE_INFO_T * pt_info);

INT32 wfd_app_get_conn_device_num(VOID);

INT32 wfd_app_get_device_info(WFD_DEVICE_INFO_T * pt_info,UINT32 index);

INT32 wfd_event_send_context(
    WFD_SEND_RETRY_TYPE_T     e_retry_type,
    wfd_event_handler        pf_event_handler, 
    VOID*                       pv_param1, 
    VOID*                       pv_param2, 
    VOID*                       pv_param3, 
    VOID*                       pv_param4);

VOID wfd_app_amb_pause(VOID);

VOID wfd_app_amb_resume(VOID);

WFD_COND_T wfd_app_get_wfd_cond(VOID);

VOID wfd_app_pin_display_accept(VOID);
INT32 wfd_free_video_resource(VOID);
INT32 wfd_restore_video_resource(VOID);
BOOL wfd_get_log(VOID);
INT32 wfd_main_send_msg_to_view(WFD_MSG_T e_msg,VOID* param);
UINT32 wfd_app_get_timeout(VOID);
INT32 a_wfd_wifi_display_show_rtp_statistics(void);
INT32 a_wfd_wifi_display_dump_ts_set_path(char *path);
INT32 a_wfd_wifi_display_dump_ts_set_enable(int enable);
INT32 a_wfd_wifi_display_start_rtsp(char *s_ip, UINT32 ui4_port);
BOOL a_wfd_is_rtsp_play_status(VOID);
INT32 a_wfd_get_device_name(UTF16_T* w2s_name);

#endif
