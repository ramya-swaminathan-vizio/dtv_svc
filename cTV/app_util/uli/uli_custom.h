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
 * $RCSfile: _ui.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/2 $
 * $SWAuthor: $
 * $MD5HEX: f2dd006620af85d9bf44b33f396ca280 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#ifndef _ULI_CUSTOM_H_
#define _ULI_CUSTOM_H_

#include "u_common.h"
#include "u_dbg.h"
#include "c_dbg.h"

#define ULI_OK                  0
#define ULI_FAIL               -1
#define ULI_INV_ARG            -2


#define ULI_NEW_PUBLIC_DELIVERY_MODE_BROADCAST   1
#define ULI_NEW_PUBLIC_DELIVERY_MODE_INTERNET    2
#define ULI_NEW_PUBLIC_DELIVERY_MODE_FILE        3

#ifndef ULI_TRUE
#define ULI_TRUE (int) 1
#endif

#ifndef ULI_FALSE
#define ULI_FALSE (int) 0
#endif


/*-----------------------------------------------------------------------------
                    Macros, Typedefs, Enumerations
-----------------------------------------------------------------------------*/
#define ULI_BUFFER_SIZE 8*1024
#define ULI_MSG_STR_MAX_LEN   (128)
#define ULI_MAX_SCHEDULE_SLOTS          64
#define ULI_MSG_MAX_LEN   (512)
#define ULI_USER_INFO_MAX_LEN   (1024)
#define ULI_MAX_AVAIABLE_DRMP   (17)

/* Debug */
#undef DBG_INIT_LEVEL
#ifdef DBG_INIT_LEVEL_APP_UI
#define DBG_INIT_LEVEL              	DBG_INIT_LEVEL_APP_UI
#else
#define DBG_INIT_LEVEL              	DBG_LEVEL_NONE
#endif

#undef DBG_LEVEL_MODULE
#define DBG_LEVEL_MODULE                ui_get_dbg_level()

/* Return on error */
#define ULI_CHK_FAIL(_ret)  \
do{ \
INT32 ret = _ret;   \
if (ret < 0)   \
{   \
    if(0)\
       DBG_LOG_PRINT(("<REST> Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, ret)); \
    return ULI_FAIL;  \
}   \
}while(FALSE)

typedef enum QdaState
{
  QdaStateUninitialized,
  QdaStateInitialized,
  QdaStateTerminating,
  QdaStateFactoryResetting,
  QdaStateMin = QdaStateUninitialized,
  QdaStateMax = QdaStateFactoryResetting
} QdaState;

typedef enum
{
	ULI_NEW_NEW_MSG_NULL = 0,
	ULI_NEW_MSG_UPDATE,			   /* update */
	ULI_MSG_UPDATE_PERCENT, 	   /*download percnet*/
	ULI_NEW_MSG_DRM,	   /* drm */
	ULI_MSGQDAINFO,	   /* QDA info */
	ULI_NEW_MSG_END

}ULI_NEW_MSG_T;

typedef enum
{
	ULI_QDA_INFO_NULL ,
	ULI_QDA_INFO_VERSION,
	ULI_QDA_INFO_SOFTWARE_VERSION

} ULI_QDA_INFO_T;


typedef enum
{
	ULI_NEW_EVENT_NULL = 30,
	ULI_NEW_EVENT_CHECKING_UPDATE,			   /* checking update */
	ULI_NEW_EVENT_UPDATE_AVAIABLE,			   /* checking update */
	ULI_NEW_EVENT_CHECKING_UPDATE_FAILURE,	   /* checking update failed */
	ULI_NEW_EVENT_UPDATE,					   /* got update info */
	ULI_NEW_EVENT_NO_UPDATE,				   /* no update now */
	ULI_NEW_EVENT_COMMANDS_DETECTED,		   /* commands detected */
	ULI_NEW_EVENT_APPROVE_COMPONENT,		   /* approve all components */
	ULI_NEW_EVENT_APPROVE_COMPONENT_FAILURE,   /* approve all components failed */
	ULI_NEW_EVENT_APPROVE_MANDATORY_COMPONENT,
	ULI_NEW_EVENT_APPROVE_OPTIONAL_COMPONENT, /* approve one optional component */
	ULI_NEW_EVENT_APPROVE_OPTIONAL_COMPONENT_FAILURE, /* optional component failed*/
	ULI_NEW_EVENT_WAIT_DOWNLOAD_SCHEDULE,		/* wait for download schedule */
	ULI_NEW_EVENT_DOWNLOADING_COMPONENT,		/* downloading components */
	ULI_NEW_EVENT_DOWNLOADED,
	ULI_NEW_EVENT_DOWNLOAD_FAILURE,
	ULI_NEW_EVENT_INSTALLING,
	ULI_NEW_EVENT_INSTALLED,
	ULI_NEW_EVENT_INSTALL_FAILURE,
	ULI_NEW_EVENT_DOWNLOAD_INSTALLED,
	ULI_NEW_EVENT_DOWNLOAD_INSTALL_FAILURE,
	ULI_NEW_EVENT_DOWNLOAD_FUTURE,
	ULI_NEW_EVENT_USB_CMD_VERIFY,
	ULI_NEW_EVENT_END,
	ULI_NEW_EVENT_UNSUPPORTED
} ULI_NEW_UPDATE_EVENT_T;

typedef enum
{
    ULI_NEW_MSG_UNKNOWN = 0,
    ULI_NEW_MSG_INIT,
    ULI_NEW_MSG_EXIT,
    ULI_NEW_MSG_CHECK_UPDATE_VALID,
    ULI_NEW_MSG_CHECK_DRMP,
    ULI_NEW_QDA_TERM,
    ULI_NEW_QDA_RESET,
    ULI_NEW_MSG_USB_UPDATE,
    ULI_NEW_QDA_SUBMIT_DATA,
    ULI_NEW_MSG_LOADING_SHOW = 10,
    ULI_NEW_MSG_LOADING_HIDE
}ULI_NEW_MSG_TYPE;

typedef enum
{
    ULI_NEW_DELIVERY_INTERNET,                  /* run in the same context */
    ULI_NEW_DELIVERY_BROADCAST,
    ULI_NEW_DELIVERY_INTERNET_BROADCAST,        /* INTERNET then BROADCAST */
    ULI_NEW_DELIVERY_INTERNET_ASYNC,            /* run in separate context */
    ULI_NEW_DELIVERY_BROADCAST_ASYNC,
    ULI_NEW_DELIVERY_INTERNET_BROADCAST_ASYNC,
	ULI_NEW_DELIVERY_FILE,
	ULI_NEW_DELIVERY_FILE_ASYNC
} ULI_NEW_UPDATE_DELIVERY_T;

typedef enum
{
    ULI_NEW_ACTION_NULL = 0,
    ULI_NEW_ACTION_APPROVE,                 /* approve individual one */
    ULI_NEW_ACTION_APPROVE_ALL_OPTIONAL,    /* approve all OPTIONAL */
    ULI_NEW_ACTION_REJECT,                  /* reject individual one */
    ULI_NEW_ACTION_REJECT_ALL_OPTIONAL,      /* reject all OPTIONAL */
    ULI_ACTION_BGM      /* for bgm check */
} ULI_NEW_UPDATE_ACTION_T;
typedef enum
{
	ULI_NEW_MSG_CHECK_UPDATE_IS_VALID,
	ULI_NEW_MSG_CHECK_UPDATE_SOURCE,
	ULI_NEW_MSG_CHECK_UPDATE_DOWNLOAD,
    ULI_NEW_MSG_CHECK_UPDATE_INSTALL,
    ULI_NEW_MSG_CHECK_USB_CMD_INSTALL,
    ULI_NEW_MSG_DOWNLOAD_PRECENT,
    ULI_NEW_MSG_CHECK_UPDATE_IS_VALID_BGM,
    ULI_NEW_MSG_USB_CMD_VERIFY,
    ULI_NEW_MSG_USB_CMD_SET_OEM_MSG
}ULI_NEW_MSG_CHECK_UPDATE_TYPE;

typedef enum ULI_NEW_SOFTWARE_UPDATE_STATE
{
  ULI_NEW_SoftwareUpdateStateNotAvailable,
  ULI_NEW_SoftwareUpdateStateFailed,
  ULI_NEW_SoftwareUpdateStateAvailable,
  ULI_NEW_SoftwareUpdateStateDownloaded,
  ULI_NEW_SoftwareUpdateStateConfirmed,
  ULI_NEW_SoftwareUpdateStateUnsupported,
  ULI_NEW_SoftwareUpdateStateMin = ULI_NEW_SoftwareUpdateStateNotAvailable,
  ULI_NEW_SoftwareUpdateStateMax = ULI_NEW_SoftwareUpdateStateUnsupported
} ULI_NEW_SOFTWARE_UPDATE_STATE;


typedef struct _uli_new_update_info_
{
    UINT32      ui4_update_index;
    UINT32      ui4_n_component;
    UINT8       ps_version[32];
    UINT8       ps_info[128];
	UINT8       ps_qda_version[32];
	UINT8       ps_software_version[32];
} ULI_NEW_UPDATE_INFO_T;


typedef struct _ULI_NEW_MSG
{
    long msgType;
	int msg_value;
    char reserved[ULI_MSG_STR_MAX_LEN];
	char usb_update_path[ULI_MSG_MAX_LEN];
	char user_info[ULI_USER_INFO_MAX_LEN];
}ULI_NEW_MSG;

typedef struct _ULI_NEW_CALLBACK_MSG
{
    long msgType;
	int msg_value;
	QdaState msg_state;
	char msg_str[ULI_MSG_STR_MAX_LEN];
}ULI_NEW_CALLBACK_MSG;


typedef struct _uli_new_comp_info_
{
    ULI_NEW_UPDATE_INFO_T   t_update_info;
    UINT32              ui4_comp_index;
    UINT8               ps_name[32];
    UINT8               ps_version[32];
    UINT8               ps_info[128];
    UINT32              ui4_attr;
    UINT32              ui4_time_slot;
    UINT32              ui4_avail_delay[ULI_MAX_SCHEDULE_SLOTS];
} ULI_NEW_COMPONENT_INFO_T;

typedef ULI_NEW_UPDATE_ACTION_T (* uli_new_component_action_fct) (ULI_NEW_COMPONENT_INFO_T  *pt_component);


typedef INT32 (* uli_new_update_nfy_fct) (ULI_NEW_UPDATE_EVENT_T    e_event);

typedef INT32 (*uli_download_percent_nfy) (INT32	 ui4_percent);


typedef struct _uli_new_update_mode_
{
    ULI_NEW_UPDATE_DELIVERY_T    e_delivery;
    uli_new_update_nfy_fct       pf_nfy;            /* ignore in sync delivery */
    uli_new_component_action_fct pf_action;         /* component action function */
    BOOL                     b_factory;         /* factory just-in update */
    BOOL                     b_from_server;     /* update from server (NOC) */
    BOOL                     b_direct_install;  /* download/install w/o store */
    ULI_NEW_UPDATE_ACTION_T      e_action;          /* APPROVE_ALL_OPTIONAL or */
                                                /* REJECT_ALL_OPTIONAL */
} ULI_NEW_UPDATE_MODE_T;

extern INT32 a_uli_msg_create(VOID);
extern INT32 a_uli_msg_receive_msg(ULI_NEW_CALLBACK_MSG* pv_msg);
extern INT32 a_uli_msg_send_msg(ULI_NEW_MSG* pv_msg);
extern INT32 a_uli_custom_check_sw_update_avaiable(
    ULI_NEW_UPDATE_MODE_T*    pt_mode
);
extern INT32 a_uli_custom_get_update_info(ULI_NEW_UPDATE_INFO_T* pt_update_info);
extern INT32 a_uli_custom_triger_sw_download_and_install(ULI_NEW_UPDATE_MODE_T*    pt_mode);
extern VOID a_uli_agent_init_wait_NTP(VOID);
extern VOID a_uli_agent_init(VOID);
extern BOOL a_uli_check_qda_init(VOID);
extern INT32 a_uli_custom_get_download_percentage(uli_download_percent_nfy percent_nfy);
extern VOID a_uli_check_drmp_update(VOID);
extern INT32 a_uli_qda_term(VOID);
extern VOID a_uli_qda_reset(VOID);
extern INT32 a_uli_qda_submit_data(CHAR ps_user_info[]);
extern VOID getTokenFromFile(CHAR* directory, CHAR * prefix,CHAR* outbuf);
extern INT32 a_uli_custom_check_usb_update_avaiable(
    ULI_NEW_UPDATE_MODE_T*    pt_mode,CHAR      *ps_usb_path
);
extern INT32 a_uli_custom_triger_usb_cmd_install(VOID);
extern INT32 uli_custom_usb_cmd_script_running();
extern INT32 a_uli_custom_set_oem_msg(CHAR* str_msg,INT32 i4_length);

#endif /* _ULI_CUSTOM_H_ */
