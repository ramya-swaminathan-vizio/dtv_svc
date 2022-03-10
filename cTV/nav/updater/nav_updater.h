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
 * $RCSfile: nav_updater.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *         This header file contains DVD protocol specific definitions,
 *         which are exported.
 *---------------------------------------------------------------------------*/

#ifndef _NAV_UPDATER_H_
#define _NAV_UPDATER_H_

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/
#include <stdlib.h>
#include <unistd.h>

#include "u_xml.h"
#include "c_xml_api.h"
#include "u_lnk_list.h"

#include "app_util/a_common.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "a_nav_updater.h"
#include "app_util/a_updater.h"
#include "res/nav/updater/nav_updater_res.h"
#include "wizard_anim/a_wzd.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define NAV_UPDATER_PREFIX                                     "<NAV_UPDATER> "

#ifdef _UPDATER_DEBUG
    #ifdef DBG_INFO
        #undef DBG_INFO
    #endif

    #ifdef DBG_ERROR
        #undef DBG_ERROR
    #endif

    #define DBG_INFO(param)  DBG_INFO (param)
    #define DBG_ERROR(param) DBG_INFO (param)
#endif

#define _UPDATER_CHK_FAIL(_ret, _ret_on_err)                                                \
do {                                                                                     \
    if (_ret < 0)                                                                        \
    {                                                                                    \
        DBG_LOG_PRINT((NAV_UPDATER_PREFIX"Return fail:%s:%d:%d\r\n", __FILE__, __LINE__, _ret)); \
        return _ret_on_err;                                                              \
    }                                                                                    \
} while(0)

#define NAV_UPGRADE_LOG_PRINT(param)                                                \
	do {																					 \
		if (b_nav_update_is_enable_log())																		 \
		{																					 \
			DBG_LOG_PRINT(param); \
		}																					 \
	} while(0)

/* integrity check result */
#define UPDATER_INT_CHK_OK               0
#define UPDATER_INT_CHK_MODEL_FAIL       1
#define UPDATER_INT_CHK_VERSION_FAIL     2
#define UPDATER_INT_CHK_SN_FAIL          3
#define UPDATER_INT_CHK_CRC_FAIL         4

/* UPDATER_PCL_FLAG */
#define UPDATER_PCL_FLAG_DEFAULT        (0x00)
#define UPDATER_PCL_FLAG_ENABLE_UPDATE  (0x5900)    /* Trigger Loader to updater FW @ /upgrade/upgrade_loader.pkg */
#define UPDATER_PCL_FLAG_UPDATE_DONE    (0x7900)    /* Loader updater FW success */

#define UPDATER_DOWNLOAD_URL_BUF_LEN (256)
#define UPDATER_DOWNLOAD_PATH_BUF_LEN (256)

typedef enum
{
    UPDATER_COND_INIT = 0,          /* The initial state */
    UPDATER_COND_PREPROCESSING,     /* Preprocessing state */
    UPDATER_COND_VALIDATING,        /* Validating the image */
    UPDATER_COND_PARSING,           /* Parsing the XML info */
    UPDATER_COND_INITED,            /* All items need to be upgraded are checked */
    UPDATER_COND_DOWNLOADING,       /* Downloading the image */
    UPDATER_COND_COMPLETE_ONE,      /* Download one complete */
    UPDATER_COND_COMPLETE,          /* Download Complete */
    UPDATER_COND_FAILED,            /* Donwload failed */
    UPDATER_COND_DEAD,              /* The dead state */
    UPDATER_COND_EXIT               /* The exit state */
}   UPDATER_COND_T;

typedef enum
{
    UPDATER_UPDATE_REASON_COND,
    UPDATER_UPDATE_REASON_PROGRESS,
    UPDATER_UPDATE_REASON_DOWNLOAD,
    UPDATER_UPDATE_REASON_CHECK_UPDATE,
    UPDATER_UPDATE_REASON_DIALOG /* This field is added for webui feature to support network upgrade's dialog UI */
}   UPDATER_UPDATE_REASON_T;

typedef enum
{
    UPDATER_EXIT_REASON_NONE = 0,
    UPDATER_EXIT_REASON_USB_DEV_FAIL,
    UPDATER_EXIT_REASON_NETWORK_FAIL,
    UPDATER_EXIT_REASON_CHECKING_UPDATE_FAIL,
    UPDATER_EXIT_REASON_NO_UPDATE,
    UPDATER_EXIT_REASON_DECRYP_FAIL,
    UPDATER_EXIT_REASON_VALIDATE_FAIL,
    UPDATER_EXIT_REASON_DOWNLOAD_FAIL,
    UPDATER_EXIT_REASON_PARSE_FAIL,
    UPDATER_EXIT_REASON_INTRNL_ERR,
    UPDATER_EXIT_REASON_USB_NOT_READY,
    UPDATER_EXIT_REASON_USB_SPACE_NOT_ENOUGH
}   UPDATER_EXIT_REASON_T;

typedef enum
{
    UPDATER_DLIVRY_TYPE_NONE = 0,
    UPDATER_DLIVRY_TYPE_USB,
    UPDATER_DLIVRY_TYPE_INTRNT,
    UPDATER_DLIVRY_TYPE_BRDCST,
    UPDATER_DLIVRY_TYPE_ULI,
    UPDATER_DLIVRY_TYPE_SYS,
    UPDATER_DLIVRY_TYPE_OAD,
    UPDATER_DLIVRY_TYPE_OTA,
    UPDATER_DLIVRY_TYPE_DLM
}   UPDATER_DLIVRY_TYPE_T;

typedef enum
{
    UPDATER_SHOW_DLG_TYPE_COPY = 0,
    UPDATER_SHOW_DLG_TYPE_ULI_USB,
    UPDATER_SHOW_DLG_TYPE_PREPROCESS,
    UPDATER_SHOW_DLG_TYPE_UPGRADE,
    UPDATER_SHOW_DLG_INTRNT_HINT,
    UPDATER_SHOW_DLG_ULI_OOB_ENTER,
    UPDATER_SHOW_DLG_ULI_OOB_PROCESSING,
    UPDATER_SHOW_DLG_TYPE_UPGRADE_COMPLETE,
    UPDATER_SHOW_DLG_TYPE_ULI_COMMAND_STICK,
    UPDATER_SHOW_DLG_TYPE_ULI_USB_COMMAND_STICK_PROCESS,
    UPDATER_SHOW_DLG_TYPE_ISP_UPGRADE
} UPDATER_SHOW_DLG_TYPE_T;

typedef enum
{
    UPDATER_REMOUNT_TYPE_BASIC = 0,
    UPDATER_REMOUNT_TYPE_3RD
} NAV_UPDATER_REMOUNT_TYPE_T;

typedef enum
{
    NAV_UPDATER_CHK_STEP_NONE = 0,
    NAV_UPDATER_CHK_STEP_DOWNLOADING_OK,
    NAV_UPDATER_CHK_STEP_INSTALL_OK
} NAV_UPDATER_CHK_STEP_TYPE_T;


struct _UPDATER_CTRL_T;
struct _UPDATER_ITEM_T;

typedef INT32 (*updater_view_init_fct)
(
    struct _UPDATER_CTRL_T*    pt_ctrl,
    HANDLE_T                   h_canvas,
    INT32                      i4_frame_x_offset,
    INT32                      i4_frame_y_offset
);

typedef INT32 (*updater_view_deinit_fct) (VOID);
typedef INT32 (*updater_view_update_progress_fct) (UPDATER_UPDATE_REASON_T e_update_reason);
typedef INT32 (*updater_view_show_dialog_fct) (UPDATER_SHOW_DLG_TYPE_T e_type, UTF16_T* w2s_text);
typedef INT32 (*updater_view_hide_dialog_fct) (VOID);

typedef INT32 (*updater_model_download_fct) (VOID);
typedef INT32 (*updater_model_leave_fct) (VOID);

typedef INT32 (*updater_cfg_parse_fw_info_fct) (struct _UPDATER_CTRL_T* pt_hdlr);
typedef INT32 (*updater_cfg_integrity_chk_fct) (struct _UPDATER_CTRL_T* pt_hdlr);
typedef INT32 (*updater_cfg_pre_upg_chk_fct) (struct _UPDATER_CTRL_T* pt_hdlr);
typedef INT32 (*updater_cfg_save_upg_result_fct) (struct _UPDATER_CTRL_T* pt_hdlr);

typedef INT32 (*updater_progress_notify_fn) (INT32 i4_percentage);
typedef VOID (*updater_preprocess_cb_fn) (BOOL b_success, UPDATER_EXIT_REASON_T e_reason);

typedef INT32 (*updater_dlivry_preprocess_fct) (updater_preprocess_cb_fn pf_preprocess_cb);
typedef VOID (*updater_dlivry_handle_msg_fct) (NAV_UI_MSG_T* pt_ui_msg, VOID* pv_arg);
typedef INT32 (*updater_dlivry_get_path_fct) (CHAR* ps_buff, SIZE_T z_buff_len);
typedef INT32 (*updater_dlivry_get_fw_fct) (struct _UPDATER_ITEM_T* pt_item, updater_progress_notify_fn pf_progress_cb);
typedef INT32 (*updater_dlivry_exit_fct) (BOOL b_success);

#ifdef SYS_MTKTVAPI_SUPPORT
typedef VOID (*nav_updater_callback_fct)(INT32 i4_msgType, INT32 i4_arg1, INT32 i4_arg2, VOID* pv_argv3);
#endif

typedef struct _UPDATER_CONFIG_T
{
    updater_cfg_integrity_chk_fct      pf_integrity_chk;
    updater_cfg_parse_fw_info_fct      pf_parse_fw_info;
    updater_cfg_pre_upg_chk_fct        pf_pre_upg_chk;
    updater_cfg_save_upg_result_fct    pf_save_upg_result;
} UPDATER_CONFIG_T;

typedef struct _UPDATER_VIEW_HDLR_T
{
    updater_view_init_fct               pf_init;
    updater_view_deinit_fct             pf_deinit;
    updater_view_update_progress_fct    pf_update_progress;
    updater_view_show_dialog_fct        pf_show_dialog;
    updater_view_hide_dialog_fct        pf_hide_dialog;
} UPDATER_VIEW_HDLR_T;

typedef struct _UPDATER_DLIVRY_HDLR_REG_T
{
    UPDATER_DLIVRY_TYPE_T            e_type;
    updater_dlivry_preprocess_fct    pf_preprocess;
    updater_dlivry_handle_msg_fct    pf_handle_msg;
    updater_dlivry_get_path_fct      pf_get_path;
    updater_dlivry_get_fw_fct        pf_get_fw;
    updater_dlivry_exit_fct          pf_exit;
    DLM_IO_T*                        pt_io;
    BOOL                             b_division;
    SLIST_ENTRY_T(_UPDATER_DLIVRY_HDLR_REG_T)    t_link;
} UPDATER_DLIVRY_HDLR_REG_T;

typedef enum
{
    TRIGGER_TYPE_NONE = 0,
    TRIGGER_TYPE_ULI_NETWORK_FW_CHECK,
    TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD,
    TRIGGER_TYPE_ULI_NETWORK_FW_INSTALL,
    TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD_AND_INSTALL,
    TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL,
    TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM,
    TRIGGER_TYPE_ULI_BGM_NETWORK_FW_DOWNLOAD_AND_INSTALL,
    TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE,
}   NAV_UPDATER_TRIGGER_TYPE_T;

typedef enum
{
    USER_MODE_NONE = 0,
    USER_MODE_NORMAL,
    USER_MODE_SILENTLY,
}   NAV_UPDATER_USER_MODE_T;

typedef enum
{
    CHECK_STATE_NONE = 0,
    CHECK_STATE_CHECKING,
    CHECK_STATE_CHECK_FAIL,
    CHECK_STATE_CHECK_NO_AVALIABLE,
    CHECK_STATE_CHECK_AVALIABLE,
    CHECK_STATE_DOWNLOADING,
    CHECK_STATE_DOWNLOAD_FAIL,
    CHECK_STATE_DOWNLOAD_SUCESS,
    CHECK_STATE_FW_VALIDATING,
    CHECK_STATE_FW_PARSING,
    CHECK_STATE_FW_INITED,
    CHECK_STATE_CHECK_INSTALLING,
    CHECK_STATE_CHECK_INSTALLED,
}   NAV_UPDATER_FW_STATE_T;

typedef enum
{
    DOWNLOAD_STATE_NONE = 0,
    DOWNLOAD_STATE_OK,
    DOWNLOAD_STATE_FAIL,
}   NAV_UPDATER_FW_DOWNLOAD_STATE_T;

typedef enum
{
    STAGE_NONE = 0,
    STAGE_FW_CHECKING,
    STAGE_FW_WAITING_RESULT,
    STAGE_FW_DOWNLOADING,
    STAGE_FW_INSTALING,
}   NAV_UPDATER_RUNNING_STAGE_T;

typedef enum
{
    UPD_CMD_TYPE_NONE = 0,
    UPD_CMD_TYPE_FW_CHECK,
    UPD_CMD_TYPE_FW_DOWNLOAD,
    UPD_CMD_TYPE_FW_INSTALL,
    UPD_CMD_TYPE_FW_REBOOT_INSTALL,
    UPD_CMD_TYPE_FW_NET_FULL_UPGRADE,
    UPD_CMD_TYPE_FW_CMD_FULL_UPGRADE,
    UPD_CMD_TYPE_FW_CMD_INSTALL,
    UPD_CMD_TYPE_FW_CHECK_AND_UPDATE
}   NAV_UPDATER_EXEC_CMD_TYPE_T;

typedef enum
{
    UPDATER_DOWNLOAD_COND_START = 0,
    UPDATER_DOWNLOAD_COND_DOWNLOADING,
    UPDATER_DOWNLOAD_COND_DOWNLOAD_COMPLETE,
    UPDATER_DOWNLOAD_COND_VALIDATING,
    UPDATER_DOWNLOAD_COND_VALIDATE_COMPLETE,
    UPDATER_DOWNLOAD_COND_EXIT
} UPDATER_DOWNLOAD_COND_T;

typedef enum
{
    UPDATER_DOWNLOAD_EXIT_REASON_NONE = 0,
    UPDATER_DOWNLOAD_EXIT_REASON_CANCEL_DONE,
    UPDATER_DOWNLOAD_EXIT_REASON_NETWORK_ERROR,
    UPDATER_DOWNLOAD_EXIT_REASON_VALIDATE_ERROR,
    UPDATER_DOWNLOAD_EXIT_REASON_FAIL
} UPDATER_DOWNLOAD_EXIT_REASON_T;

typedef enum
{
    UPDATER_CHECK_UPDATE_COND_START = 0,
    UPDATER_CHECK_UPDATE_COND_CHECKING,
    UPDATER_CHECK_UPDATE_COND_COMPLETE,
    UPDATER_CHECK_UPDATE_COND_EXIT
} UPDATER_CHECK_UPDATE_COND_T;

typedef enum
{
    UPDATER_CHECK_UPDATE_REASON_NONE = 0,
    UPDATER_CHECK_UPDATE_REASON_NETWORK_ERROR,
    UPDATER_CHECK_UPDATE_REASON_FAIL
} UPDATER_CHECK_UPDATE_EXIT_REASON_T;
typedef enum
{
    UPDATER_USB_TYPE_UNKNOW = 0,
    UPDATER_USB_TYPE_UTV,
    UPDATER_USB_TYPE_CMD
} UPDATER_USB_TYPE_T;

typedef enum
{
    UPDATER_SET_TYPE_NO_OTA_DOWNLOAD_UI = 0,
}   UPDATER_SET_TYPE_T;

typedef struct _UPDATER_CTRL_T
{
    UINT32                                 ui4_crnt_upg_item_idx;
    UINT32                                 ui4_upg_done_item_num;
    UPDATER_FW_INFO_T                      t_upg_fw_info;
    XML_T*                                 pt_download_xml;
#ifdef APP_PRE_UPG_CHK
    UPDATER_FW_INFO_T                      t_crnt_fw_info;
    XML_T*                                 pt_version_xml;
#endif
    UPDATER_COND_T                         e_cond;
    UINT8                                  ui1_int_chk;

	/*install progress*/
    UINT8                                  ui1_progress;

    NAV_CONTEXT_T*                         pt_ctx;
    BOOL                                   b_is_leaving;
    BOOL                                   b_is_updater_triggered;
    BOOL                                   b_is_usb_not_plugged;
    BOOL                                   b_is_svc_stop;
    BOOL                                   b_is_bgm;
    BOOL                                   b_is_abort;
    BOOL                                   is_semi_standby;
    UPDATER_EXIT_REASON_T                  e_exit_reason;

    UPDATER_CONFIG_T*                      pt_updater_cfg;

    UPDATER_VIEW_HDLR_T                    t_updater_view_hdlr;

    updater_model_download_fct             pf_download;
    updater_model_leave_fct                pf_leave;

    /* Mutex Semaphore */
    HANDLE_T        h_sema_mtx;                 /* Semaphore (Mutex) */
    SLIST_T(_UPDATER_DLIVRY_HDLR_REG_T)    t_hdlr_reg_list;
    UPDATER_DLIVRY_HDLR_REG_T*             pt_curr_dlivry_hdlr;
    BOOL                                   b_is_inited;

	/* update notify*/
    nav_updater_callback_fct               pf_nfy;
    VOID*                                  pv_tag;

	/*nav update active trigger type*/
    NAV_UPDATER_TRIGGER_TYPE_T             e_trigger_type;

	/*nav update active user mode
	  silently case should not show
	  update UI*/
    NAV_UPDATER_USER_MODE_T                e_user_mode;

    /* nav update running stage*/
	NAV_UPDATER_RUNNING_STAGE_T            e_update_stage;

	/*download progress*/
    UINT8                                  ui1_fw_download_progress;

	HANDLE_T                               h_download_process_timer;
	HANDLE_T                               h_utv_download_process_timer;

	HANDLE_T                               h_delay_firmware_check_timer;
	HANDLE_T                               h_firmware_check_result_query_timer;

	HANDLE_T                               h_firmware_no_avaliable_hide_timer;
	HANDLE_T                               h_firmware_check_waiting_feedback;//timeout for wait uli process feedback check update result

    NAV_UPDATER_FW_STATE_T                 e_fw_state;

    NAV_UPDATER_FW_STATE_T                 e_fw_check_avaliable;
	BOOL                                   b_is_force_update;

	BOOL                                   b_is_need_fw_re_check;


	BOOL                                   b_is_download_ok_received;
	UINT8                                  ui1_download_ok_get_times;

	BOOL                                   b_is_install_ok_received;
	UINT8                                  ui1_install_ok_get_times;

} UPDATER_CTRL_T;

/*-----------------------------------------------------------------------------
                    functions declarations
 ----------------------------------------------------------------------------*/

extern INT32 nav_updater_init(
    const UPDATER_CONFIG_T*    pt_updater_cfg
);

extern INT32 nav_updater_view_register_default_hdlr(
    UPDATER_VIEW_HDLR_T*     pt_view_hdlr
);

extern INT32 nav_updater_update_info(
    UINT8    ui1_status
);

extern BOOL nav_updater_is_new_ver
(
    CHAR*    ps_updater_file_ver,
    CHAR*    ps_ver_sys_ver
);

extern INT32 nav_updater_request_update
(
    BOOL*    pb_delay_start
);

extern INT32 nav_updater_trigger_update
(
    UPDATER_DLIVRY_TYPE_T    e_type
);

extern INT32 nav_updater_reg_dlivry_hdlr
(
    UPDATER_DLIVRY_HDLR_REG_T*    pt_reg
);

extern UINT8* nav_updater_get_fbm_addr
(
    VOID
);

extern UINT32 nav_updater_get_total_fbm_size
(
    VOID
);

extern VOID nav_updater_enter_bgm
(
    BOOL    b_bgm
);

extern VOID  nav_updater_do_abort
(
    VOID
);

extern INT32 nav_updater_integrity_chk
(
    VOID
);

extern INT32 nav_updater_show_dialog
(
    UPDATER_SHOW_DLG_TYPE_T e_type,
    UTF16_T*    w2s_text
);

extern INT32 nav_updater_hide_dialog
(
    VOID
);

extern VOID nav_updater_mem_init
(
    VOID
);

extern INT32 nav_updater_mem_get_io_fn
(
    DLM_IO_T*    pt_io
);

extern INT32 nav_updater_mem_acquire_mem(
    UINT32    ui4_sz,
    BOOL      b_use_fbm,
    UINT8**   ppui1_buf
);

extern INT32 nav_updater_mem_release_mem(
    VOID
);

extern INT32 nav_updater_reboot_system(VOID);
extern BOOL  nav_updater_pkgfile_existed_in_tv(VOID);

extern INT32 nav_updater_uli_unreg_dev_monitor(VOID);
extern INT32 nav_updater_uli_progress_show(VOID);
extern BOOL  nav_updater_uli_need_reboot(VOID);
extern BOOL nav_updater_is_3rd_rw_part_ready(
    VOID
);
extern BOOL nav_updater_is_all_partition_ready(
    VOID
);

#ifdef APP_ULI_UPG_SUPPORT
extern BOOL  nav_updater_uli_is_usb_method(VOID);
extern VOID nav_updater_uli_trigger_sub_updater( VOID );
extern BOOL  nav_updater_uli_is_intnt_method(VOID);
extern INT32 nav_updater_uli_send_started_msg_to_am( VOID );
extern INT32 a_nav_updater_uli_partition_all_query_network_up( VOID );
extern BOOL nav_updater_is_uli_agent_in_progress( VOID );
#endif

extern INT32 nav_dev_db_network_ready_query_time(VOID);

#ifdef APP_BASIC_RO
extern INT32 nav_updater_remount_rw(NAV_UPDATER_REMOUNT_TYPE_T e_type);
extern INT32 nav_updater_remount_ro(NAV_UPDATER_REMOUNT_TYPE_T e_type);
#endif

extern BOOL nav_updater_is_need_to_check_dev_db(VOID);
extern INT32 nav_updater_set_check_dev_db_flag(BOOL   b_is_need_to_check);
extern BOOL nav_updater_is_bgm_ex(
    VOID
);
extern INT32 nav_updater_reboot_system_ex(VOID);
extern INT32 nav_updater_register_callback(nav_updater_callback_fct pf_nfy, VOID* pv_tag);
extern INT32 nav_updater_unregister_callback(nav_updater_callback_fct pf_nfy, VOID* pv_tag);
extern INT32 nav_updater_start(UPDATER_DLIVRY_TYPE_T t_delivery_type, BOOL b_start);
extern INT32 nav_updater_trigger(UPDATER_DLIVRY_TYPE_T t_delivery_type);
extern INT32 nav_updater_get_firmware_info(UPDATER_FW_INFO_T* pt_firmwareInfo);
extern INT32 nav_updater_get_item_info(UPDATER_ITEM_T* pt_item, UINT32 ui4_index);
extern INT32 nav_updater_start_download_firmware(UPDATER_DLIVRY_TYPE_T t_delivery_type, const CHAR* ps_url, const CHAR* ps_fwPath);
extern INT32 nav_updater_cancel_download_firmware(UPDATER_DLIVRY_TYPE_T t_delivery_type);
extern INT32 nav_updater_download_firmware_and_trigger_update(UPDATER_DLIVRY_TYPE_T t_delivery_type, const CHAR* ps_url, const CHAR* ps_fwPath);
extern INT32 nav_updater_start_reboot_upgrade(UPDATER_DLIVRY_TYPE_T t_delivery_type);
extern INT32 nav_updater_query_upgrade_result(UPDATER_DLIVRY_TYPE_T t_delivery_type);
extern INT32 nav_updater_is_supported(UPDATER_DLIVRY_TYPE_T t_delivery_type, BOOL* pb_supported);
extern INT32 nav_updater_check_update(UPDATER_DLIVRY_TYPE_T t_delivery_type);

extern INT32 nav_updater_uli_get_user_mode(NAV_UPDATER_USER_MODE_T *pe_user_mode);
extern INT32 nav_updater_uli_set_user_mode(NAV_UPDATER_USER_MODE_T e_user_mode);
extern INT32 nav_updater_uli_set_trigger_type(NAV_UPDATER_TRIGGER_TYPE_T	e_type);
extern INT32 nav_updater_uli_get_trigger_type(NAV_UPDATER_TRIGGER_TYPE_T	*pe_type);
extern INT32 nav_updater_uli_get_update_stage(NAV_UPDATER_RUNNING_STAGE_T  *pe_update_stage);
extern INT32 nav_updater_uli_set_update_stage(NAV_UPDATER_RUNNING_STAGE_T   e_update_stage);
extern INT32 nav_updater_uli_set_fw_status(NAV_UPDATER_FW_STATE_T   e_fw_state);
extern INT32 nav_updater_uli_get_fw_status(NAV_UPDATER_FW_STATE_T  *pe_fw_state);
extern INT32 nav_updater_uli_get_fw_avaliable(NAV_UPDATER_FW_STATE_T  *pe_fw_state);
extern INT32 nav_updater_uli_set_fw_avaliable(NAV_UPDATER_FW_STATE_T   e_fw_state);
extern VOID nav_update_reset_download_check_timer(VOID);
extern INT32 nav_updater_uli_get_fw_force_update_flag(BOOL   *pb_force_state);
extern INT32 nav_updater_uli_set_fw_force_update_flag(BOOL   b_force_state);

extern BOOL nav_update_is_sys_sw_image_ready(VOID);
extern INT32 nav_updater_uli_start_full_sys_upgrade(NAV_UPDATER_USER_MODE_T e_user_mode);
extern INT32 nav_updater_uli_check_sw_available(NAV_UPDATER_USER_MODE_T e_user_mode);
extern INT32 nav_updater_uli_check_sw_available_and_update(NAV_UPDATER_USER_MODE_T e_user_mode);
extern INT32 nav_updater_uli_start_fw_download(NAV_UPDATER_USER_MODE_T e_user_mode);
extern INT32 nav_updater_cmd_exec(NAV_UPDATER_EXEC_CMD_TYPE_T  e_cmd_type,
	                           NAV_UPDATER_USER_MODE_T  e_user_mode);
extern INT32 nav_updater_sys_install_fw(NAV_UPDATER_USER_MODE_T e_user_mode,
                               BOOL   b_is_to_reboot);
extern INT32 nav_update_send_fw_check_msg_to_observer(INT32 i4_arg1, INT32 i4_arg2);
extern INT32 nav_update_send_fw_download_msg_to_observer(INT32 i4_arg1, INT32 i4_arg2);
extern INT32 nav_updater_check_continue_next_step(NAV_UPDATER_CHK_STEP_TYPE_T e_chk_type,
	                                      BOOL *pb_is_to_continue);

extern INT32 nav_updater_set_oobe_update_status(WZD_PAGE_INDEX_T e_idx);

/*new ui for spec change*/
extern INT32 nav_updater_view_show_usb_command_process_info(BOOL b_show);
extern INT32 nav_updater_view_show_usb_info(BOOL b_show);
extern INT32 nav_updater_view_show_command_stick_info(BOOL b_show);
extern INT32 nav_updater_view_show_complete_info(BOOL b_show);
extern INT32 nav_updater_show_preprocess_page_ex(BOOL b_show);
extern INT32 nav_updater_show_updating_page_ex(BOOL b_show);
extern INT32 nav_updater_show_isp_updating_page_ex(BOOL b_show);
extern INT32 nav_updater_uli_check_provisioning_status(VOID);

extern INT32 nav_updater_get_cast_key_status(BOOL  *pb_is_ready);
extern INT32 nav_updater_show_toast_progress_test(UINT8 ui1_value);
extern INT32 nav_updater_view_update_toast_process_bar(UINT8 ui1_value,
                                                            BOOL  b_is_repaint);

extern INT32 nav_updater_view_set_toast_process_bar_status(BOOL b_is_show);
extern VOID nav_update_reset_utv_download_check_timer(VOID);
extern INT32 nav_updater_view_show_firmware_check_not_avaliable_info(BOOL b_show);
extern INT32 nav_updater_view_show_download_fail_info(BOOL b_show);
extern INT32 a_nav_updater_check_network_update(UINT8 *pui1_fw_status,
                                                   UINT8 *pui_fw_policy);
extern INT32 nav_updater_cmd_directly_exec(NAV_UPDATER_EXEC_CMD_TYPE_T  e_cmd_type,
	                           NAV_UPDATER_USER_MODE_T  e_user_mode);

extern INT32 a_nav_updater_direcly_check_fw_avaliable(UINT8 *pui1_fw_status,
                                                   UINT8 *pui_fw_policy);

extern INT32 nav_updater_cmd_directly_exec(NAV_UPDATER_EXEC_CMD_TYPE_T  e_cmd_type,
	                           NAV_UPDATER_USER_MODE_T  e_user_mode);
extern INT32 a_nav_updater_download_firmware_and_trigger_update_directly(UINT8  *pui1_fw_status);
extern BOOL nav_updater_is_running(VOID);
extern BOOL a_nav_updater_uli_get_oobe_update_finished_complete();
extern INT32 a_nav_updater_uli_set_oobe_update_finished_complete(BOOL   b_oobe_update_complete);
extern BOOL a_nav_is_loading_page_show(VOID);
extern INT32 nav_loading_page_hide(VOID);
extern UPDATER_USB_TYPE_T a_nav_updater_uli_get_usb_upgrade_type(VOID);
extern BOOL b_nav_update_is_enable_log(VOID);
extern INT32 a_nav_updater_iom_all_key_locked(BOOL b_is_to_lock,BOOL b_is_power_lock);
extern INT32 nav_updater_loop_test_timer_start(VOID);

#ifdef MTK_CAMERA_DPTZ_SUPPORT
extern INT32 nav_updater_isp_get_current_version(CHAR* ps_buff, UINT32 ui4_size);
extern INT32 nav_updater_isp_get_version(CHAR* ps_buff, UINT32 ui4_size);
#endif

#endif /* _NAV_UPDATER_H_ */


