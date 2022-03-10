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
 * $Revision: #2 $
 * $Date: 2015/06/22 $
 * $Author: heyi.wang $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#ifdef APP_ULI_UPG_SUPPORT

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <cJSON.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <openssl/evp.h>
#include <openssl/x509.h>
#include <openssl/rsa.h>

#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <openssl/crypto.h>


#include <time.h>
#include "am/a_am.h"
#include "app_util/a_updater.h"
#include "app_util/a_network.h"
#include "app_util/a_cfg.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "app_util/a_icl.h"
#include "app_util/a_icl_common.h"
#include "nav/nav_common.h"
#include "nav/updater/nav_updater.h"
#include "nav/updater/a_nav_updater.h"
#include "res/app_util/updater/a_updater_custom.h"
#include "res/nav/updater/nav_updater_res.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_misc.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "c_fm.h"
#include "c_dlm.h"
#include "agent/a_agent.h"
#include "c_os.h"
#include "c_dt.h"
#include "c_pcl.h"
#include "c_handle.h"
#include "msgconvert/msgconvert.h"
#include "bgm/a_bgm.h"
#include "res/app_util/dst/a_dst_custom.h"
#include "res/nav/nav_mlm.h"

#include "project-mtk-new-api.h"
#include "app_util/uli/uli_custom.h"

#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 -----------------------------------------------------------------------------*/

#define NAV_UPDATER_ULI_REDIRECT_FILE_NAME                   "updatelogic.txt"
#define NAV_UPDATER_ULI_OOB_TEST_START_FILE_NAME              "OOB_TEST_START"
#define NAV_UPDATER_ULI_OOB_TEST_END_FILE_NAME                  "OOB_TEST_END"
#define NAV_UPDATER_ULI_IN_OOB_TEST_FILE_NAME                       "OOB_TEST"

#define UPDATE_FW_VER_STRING_FILE     "/3rd_rw/update_ver_file"


/* 300 seconds */
#define NAV_UPDATER_ULI_DL_DELAY_TIME                    ((UINT32)(300 * 1000))

#define NAV_UPDATER_ULI_MAX_CHK_3RD_RETRY_NUM               ((UINT8)       90)
#define NAV_UPDATER_ULI_MAX_CHK_NETWORK_CONNECTION_RETRY_NUM               ((UINT8)       3)



/* 30 minites */
#define NAV_UPDATER_ULI_MAX_WAKE_UP_TIME                   ((UINT32)(30 * 60))

/* 20 minites */
#define NAV_UPDATER_ULI_CHK_UPDATE_TIME                    ((UINT32)(20 * 60))

#define NAV_UPDATER_SHA_LENGTH      20

/* status mask flags */
#define NAV_UPDATER_ULI_STATUS_MASK_REGISTERED                         0x0001
#define NAV_UPDATER_ULI_STATUS_MASK_FACTORY_TEST_MODE                  0x0002
#define NAV_UPDATER_ULI_STATUS_MASK_FIELD_TEST_MODE                    0x0004
#define NAV_UPDATER_ULI_STATUS_MASK_LOOP_TEST_MODE                     0x0008

#define NAV_UPDATE_ULI_PROVISION_NOT_READY                    ((UINT8)0)
#define NAV_UPDATE_ULI_PROVISION_DOWNLOAD_READY               ((UINT8)1)

#define NAV_UPDATE_ULI_PROVISION_MAX_NUM                      ((UINT8)8)

#define NAV_UPDATE_ULI_CHECK_NP_TIMES_MAX_NUM                 ((UINT32)60)
#define NAV_UPDATE_ULI_CHECK_NP_EVERY_TIMER_OUT               ((UINT32)10000)

#define APP_MULTISKU_USB_SUPPORT (1)

#ifdef APP_MULTISKU_USB_SUPPORT
#define MULTISKU_LINE_MAX_LEN                ((UINT32) 1024)
#define MULTISKU_FILE_NAME_MAX_LEN           ((UINT32) 128)
#define MULTISKU_MG_CFG_MIN_LEN              ((UINT32) 4)
#define MULTISKU_MG_CFG_PREFIX_LEN           ((UINT32) 2)
#define MULTISKU_NAME_CFG_MIN_LEN            ((UINT32) 5)
#define MULTISKU_NAME_CFG_SUFFIX_LEN         ((UINT32) 4)

#define MULTISKU_TXT_CFG_SUB_STR_DELIMS     ","
#define MULTISKU_TXT_CFG_FILE_NAME          "viziologic.txt"

#define UTV_FILE_SUFFIX_NAME     ".utv"
#define CMD_FILE_SUFFIX_NAME     ".cmd"

#define AES_LENGTH (16)
#define RSA_LENGTH (256)

typedef enum
{
    CONTENT_CFG_TYPE_MG=0,
    CONTENT_CFG_TYPE_VER,
    CONTENT_CFG_TYPE_NAME,
    CONTENT_CFG_TYPE_MAX
}MULTISKU_CONTENT_CFG_TYPE_T;

typedef struct _MULTISKU_INFO_T
{
    CHAR   s_usb_root_path[MULTISKU_FILE_NAME_MAX_LEN];
    CHAR   s_utv_file_name[MULTISKU_FILE_NAME_MAX_LEN];
    CHAR   s_cmd_file_name[MULTISKU_FILE_NAME_MAX_LEN];
    BOOL   b_utv_file_config;
    BOOL   b_cmd_file_config;
    BOOL   b_is_multisku_info_init;
    BOOL   b_is_utv_checked;
    UINT32 ui4_mg_value;
}MULTISKU_INFO_T;

static   MULTISKU_INFO_T        t_multisuk_info;
#endif

static   BOOL     b_s_is_usb_insert    = FALSE;
static   BOOL     b_g_check_np_time_create = FALSE;
static   HANDLE_T   h_check_np_timer = NULL_HANDLE;
static   UINT32     ui4_g_check_np_times_count = 0;



static   RMV_DEV_NFY_ID_T       e_s_nfy_id = RMV_DEV_NFY_ID_UNKNOWN;


typedef enum
{
    UPDATER_ULI_METHOD_USB = 0,
    UPDATER_ULI_METHOD_INTNT
} UPDATER_ULI_METHOD_T;

static UPDATER_USB_TYPE_T e_usb_update_type = UPDATER_USB_TYPE_UNKNOW;
typedef struct _UPDATER_ULI_CTRL_T
{
    UPDATER_DLIVRY_TYPE_T       e_type;

    CHAR                        s_src_file[64];
    UINT32                      ui4_rmv_dev_nfy;
    BOOL                        b_delay_start;
    BOOL                        b_uli_agent_in_progess;
    BOOL                        b_uli_agent_ok;
    BOOL                        b_uli_agent_download_ok;
    BOOL                        b_first_time_rmv_nfy;
    UPDATER_ULI_METHOD_T        e_method;
    ULI_UPDATE_EVENT_T          e_fail_reason;
    updater_uli_bgm_nfy_fct     pf_nfy;
    updater_preprocess_cb_fn    pf_preprocess_cb;
    UINT32                      ui4_nw_nfy_id;
    BOOL                        b_uli_evt_end;
    BOOL                        b_uli_evt_update;
    BOOL                        b_exit_checking_network;
    UINT32                      ui4_avail_delay;
    HANDLE_T                    h_dl_timer;

} UPDATER_ULI_CTRL_T;

/*-----------------------------------------------------------------------------
                    variable declarations
 -----------------------------------------------------------------------------*/
static UINT8 g_ui1_retry = 0;

static BOOL  g_b_poweron =FALSE;
static BOOL  g_b_uli_network_up =FALSE;
static BOOL  g_b_uli_provisioning_checked =FALSE;
static CHAR  usb_update_path[512] = {0};


extern INT32 c_base64_encode(const VOID *pv_in_data, INT32 i4_pv_in_data_size, VOID *pac_out_data, INT32 i4_pac_out_data_size);
extern CHAR* sys_cust_get_usb_upg_version(VOID);


/*-----------------------------------------------------------------------------
                    private methods declarations
 -----------------------------------------------------------------------------*/

#ifdef CLI_SUPPORT

static INT32 _nav_updater_uli_cli_start_dl
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_object_request
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_status_request
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_provisioning_status_request
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_is_ulpk_valid_in_given_path
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_reg_user_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_remove_user_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

/*Rest API CLI test*/
static INT32 _nav_updater_uli_cli_rest_register_user_info
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_get_dev_register_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_get_user_register_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_get_updating_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_check_fw_avaliable
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_start_update
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_get_update_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_just_download
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_reboot_install
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_updater_uli_show_usb_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);
static INT32 _nav_updater_uli_hide_usb_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);
static INT32 _nav_updater_uli_show_complete_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_hide_complete_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);
static INT32 _nav_updater_uli_show_updating_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);
static INT32 _nav_updater_uli_show_firmware_not_avaliable_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);
static INT32 _nav_updater_uli_hide_firmware_not_avaliable_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_hide_updating_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_show_progress_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);
static INT32 _nav_updater_uli_hide_progress_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_show_cmd_stick_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_hide_cmd_stick_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_cli_test_toast_process_bar
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);

static INT32 _nav_updater_uli_cli_rest_install
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);
static INT32 _nav_updater_uli_cli_rest_service_check
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_cli_rest_bgm_reboot
(
    INT32           i4_argc,
    const CHAR**    pps_argv
);

static INT32 _nav_updater_uli_check_network_updater
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
);


#endif

static INT32 _nav_updater_uli_get_path
(
    CHAR*                  ps_buff,
    SIZE_T                 z_buff_len
);
static VOID _nav_updater_uli_stop_dl_timer(VOID);

static INT32 _nav_updater_uli_get_provision_download_status(UINT8  *pui1_download_status);

static INT32 _nav_update_uli_check_np_time_create(VOID);

static VOID _nav_update_uli_stop_check_np_timer(VOID);
static VOID _nav_update_uli_check_np_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
static VOID _nav_update_uli_check_np_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    );
static INT32 _nav_update_uli_check_np_time_reset(VOID);
static INT32 _nav_updater_uli_timer_check_provision_download_status(VOID);
static VOID _nav_update_uli_decrypt_widevine_key(VOID);

#ifdef APP_MULTISKU_USB_SUPPORT
#if 0
static INT32 _nav_update_atoi(CHAR *ps);
#endif
static INT32 _nav_update_get_hexnum(CHAR *ps);

static void _nav_update_str_right_trim(CHAR *s_sting);
static void _nav_update_str_left_trim(CHAR *s_sting);
static INT32 _nav_update_check_multisku_info_by_text_line(char *s_text_line,
                                                   MULTISKU_INFO_T *pt_multisku_info);
static INT32 _nav_update_get_platform_mg_value(UINT32 *pui4_mg_value);
static INT32 _nav_update_get_multisku_info(char *s_file_name,
                                    MULTISKU_INFO_T *pt_multisku_info);
static INT32 _nav_update_create_utv_trigger_file_with_content(char *s_file_name,
                            char *s_txt_content);
static INT32 _nav_updater_get_multisku_usb_path(CHAR *s_path,UINT32 ui4_size,BOOL *pb_multisku_exist);

static INT32 _nav_updater_check_usb_multisku(CHAR *s_multisku_file_name);

static VOID _nav_updater_uli_do_multisku(VOID);
static BOOL _start_with(CHAR* src,CHAR* start);

static BOOL _end_with(CHAR* src,CHAR* end);


#endif

/*-----------------------------------------------------------------------------
                    variable declarations
 -----------------------------------------------------------------------------*/

static UPDATER_ULI_CTRL_T    t_g_uli_ctrl;

#ifdef CLI_SUPPORT
static CLI_EXEC_T at_g_uli_rest_api_cli_cmd_tbl[] =
{
    { "register user info",   "ru",  _nav_updater_uli_cli_rest_register_user_info,          NULL,   "register user info",         NAV_CLI_ACCESS_RIGHT_LVL },
    { "get dev register",     "gdr", _nav_updater_uli_cli_rest_get_dev_register_status,     NULL,   "get dev register",           NAV_CLI_ACCESS_RIGHT_LVL },
    { "get user register",    "gur", _nav_updater_uli_cli_rest_get_user_register_status,    NULL,   "get user register",          NAV_CLI_ACCESS_RIGHT_LVL },
    { "check if updating",    "ciu", _nav_updater_uli_cli_rest_get_updating_status,         NULL,   "check if updating",          NAV_CLI_ACCESS_RIGHT_LVL },
    { "check fw",             "cfw", _nav_updater_uli_cli_rest_check_fw_avaliable,          NULL,   "check fw",                   NAV_CLI_ACCESS_RIGHT_LVL },
    { "start update",         "sup", _nav_updater_uli_cli_rest_start_update,                NULL,   "start update",               NAV_CLI_ACCESS_RIGHT_LVL },
    { "get update status",    "gus", _nav_updater_uli_cli_rest_get_update_status,           NULL,   "get update status",          NAV_CLI_ACCESS_RIGHT_LVL },
    { "just download",        "jd",  _nav_updater_uli_cli_rest_just_download,               NULL,   "just download",              NAV_CLI_ACCESS_RIGHT_LVL },
    { "reboot install",       "ris", _nav_updater_uli_cli_rest_reboot_install,              NULL,   "reboot install",             NAV_CLI_ACCESS_RIGHT_LVL },
    { "just install",         "jis", _nav_updater_uli_cli_rest_install,                     NULL,   "just install",               NAV_CLI_ACCESS_RIGHT_LVL },
    { "service check",        "sck", _nav_updater_uli_cli_rest_service_check,                   NULL,   "service check",              NAV_CLI_ACCESS_RIGHT_LVL },
    { "bgm reboot",           "brt", _nav_updater_uli_cli_rest_bgm_reboot,                  NULL,   "service check",              NAV_CLI_ACCESS_RIGHT_LVL },
    { "check update",         "ckud", _nav_updater_uli_check_network_updater,                   NULL,   "check update",           NAV_CLI_ACCESS_RIGHT_LVL },

    END_OF_CLI_CMD_TBL
};

static CLI_EXEC_T at_g_uli_cli_cmd_tbl[] =
{
    { "start_dl",        "s", _nav_updater_uli_cli_start_dl,                 NULL, "Start to test the Internet & OAD update",                 NAV_CLI_ACCESS_RIGHT_LVL },
    { "obj_request",     "o", _nav_updater_uli_cli_object_request,           NULL, "Request provisioning objects <owner name> <object name>", NAV_CLI_ACCESS_RIGHT_LVL },
    { "status_request",  "r", _nav_updater_uli_cli_status_request,           NULL, "Request current status",                                  NAV_CLI_ACCESS_RIGHT_LVL },
    { "req_provioning_status",  "rps", _nav_updater_uli_cli_provisioning_status_request,             NULL, "Request provisioning status",                                 NAV_CLI_ACCESS_RIGHT_LVL },
    { "chk_ulpk",        "v", _nav_updater_uli_is_ulpk_valid_in_given_path,  NULL, "Check ULPK <path of ULPK>",                               NAV_CLI_ACCESS_RIGHT_LVL },
    { "reg_user_info",   "reg", _nav_updater_uli_reg_user_info,              NULL, "reg user info",                                           NAV_CLI_ACCESS_RIGHT_LVL },
    { "remove_user_info","rm", _nav_updater_uli_remove_user_info,            NULL, "remove user info",                                        NAV_CLI_ACCESS_RIGHT_LVL },
    { "show_usb_info",   "sui", _nav_updater_uli_show_usb_info,            NULL, "show_usb_info",                                        NAV_CLI_ACCESS_RIGHT_LVL },
    { "hide_usb_info",   "hui", _nav_updater_uli_hide_usb_info,         NULL, "hide_usb_info",                                        NAV_CLI_ACCESS_RIGHT_LVL },
    { "show_cmd_stick_info","scsi", _nav_updater_uli_show_cmd_stick_info,           NULL, "show_cmd_stick_info",                                      NAV_CLI_ACCESS_RIGHT_LVL },
    { "hide_cmd_stick_info","hcsi", _nav_updater_uli_hide_cmd_stick_info,           NULL, "hide_cmd_stick_info",                                      NAV_CLI_ACCESS_RIGHT_LVL },
    { "show_complete_info","sci", _nav_updater_uli_show_complete_info,          NULL, "show_complete_info",                                       NAV_CLI_ACCESS_RIGHT_LVL },
    { "hide_complete_info","hci", _nav_updater_uli_hide_complete_info,          NULL, "hide_complete_info",                                       NAV_CLI_ACCESS_RIGHT_LVL },
    { "show_firmware_not_avaliable_info","sfnai", _nav_updater_uli_show_firmware_not_avaliable_info,            NULL, "show_firmware_not_avaliable_info",                                     NAV_CLI_ACCESS_RIGHT_LVL },
    { "hide_firmware_not_avaliable_info","hfnai", _nav_updater_uli_hide_firmware_not_avaliable_info,            NULL, "hide_firmware_not_avaliable_info",                                     NAV_CLI_ACCESS_RIGHT_LVL },
    { "show_updating_info","suti", _nav_updater_uli_show_updating_info,         NULL, "show_updating_info",                                       NAV_CLI_ACCESS_RIGHT_LVL },
    { "hide_updating_info","huti", _nav_updater_uli_hide_updating_info,         NULL, "hide_updating_info",                                       NAV_CLI_ACCESS_RIGHT_LVL },
    { "show_progress_info","spi", _nav_updater_uli_show_progress_info,          NULL, "show_progress_info",                                       NAV_CLI_ACCESS_RIGHT_LVL },
    { "hide_progress_info","hpi", _nav_updater_uli_hide_progress_info,          NULL, "hide_progress_info",                                       NAV_CLI_ACCESS_RIGHT_LVL },
    { "process_bar_test", "pbt", _nav_updater_uli_cli_test_toast_process_bar,           NULL, "process_bar_test",                                     NAV_CLI_ACCESS_RIGHT_LVL },

    { "rest api",        "rai",    NULL,      at_g_uli_rest_api_cli_cmd_tbl, "rest api",                                          NAV_CLI_ACCESS_RIGHT_LVL },

    END_OF_CLI_CMD_TBL
};



static CLI_EXEC_T t_g_uli_cli_cmd_entry =
{
    "updater_uli", NULL, NULL, at_g_uli_cli_cmd_tbl, "updater commands", NAV_CLI_ACCESS_RIGHT_LVL
};

#endif

/*-----------------------------------------------------------------------------
                    private methods implementation
 -----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Name: _nav_updater_cb_bgm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static VOID _nav_updater_cb_bgm(
    NAV_UPDATER_ULI_COND_T    e_cond
)
{
    UPDATER_ULI_CTRL_T*       pt_this = &t_g_uli_ctrl;
    UINT8                     ui1_status = ICL_ULI_STATUS_GOING_BACK_TO_STANDBY;

    if (NULL != pt_this->pf_nfy)
    {
        /* callback bgm */
        pt_this->pf_nfy(e_cond, NULL);

        /* set to updater core */
        nav_updater_enter_bgm(FALSE);

        /*as pf_nfy have been called,
          the ULI bgm will run into next
          component, here just set the pf_nfy
          to null to avoid double call*/
          pt_this->pf_nfy = NULL;
    }

    /* set to ICL */
    a_icl_set((ICL_ID_TYPE)ICL_MAKE_ID(ICL_GRPID_ULI, ICL_RECID_ULI_STATUS),
              (VOID*) &ui1_status,
              ICL_RECID_ULI_STATUS_SIZE);

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_abort_updates
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_uli_abort_updates(
    VOID
)
{
    UPDATER_ULI_CTRL_T*    pt_this = &t_g_uli_ctrl;

    /* abort current update process */
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Tell ULI agent to abort current update process!!!\n"));
#ifdef ULI_USE_ODL_LIB

    a_uli_abort_updates();
#endif
    pt_this->b_uli_agent_in_progess = FALSE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_preprocess_cb
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_preprocess_cb(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    BOOL                    b_success = (BOOL)((UINT32)pv_tag1);
    DBG_LOG_PRINT(("%s_%d \n",__FUNCTION__,__LINE__));
    if (NULL != pt_this->pf_preprocess_cb)
    {
        DBG_LOG_PRINT(("%s_%d \n",__FUNCTION__,__LINE__));
        if (TRUE == b_success)
        {
            DBG_LOG_PRINT(("%s_%d \n",__FUNCTION__,__LINE__));
            pt_this->pf_preprocess_cb(TRUE,
                                      UPDATER_EXIT_REASON_NONE);
        }
        else
        {
            switch(pt_this->e_fail_reason)
            {
                case ULI_EVENT_CHECKING_UPDATE_FAILURE:
                case ULI_EVENT_NO_UPDATE:
                    pt_this->pf_preprocess_cb(FALSE,
                                              UPDATER_EXIT_REASON_NO_UPDATE);
                    break;

                case ULI_EVENT_INSTALL_FAILURE:
                case ULI_EVENT_DOWNLOAD_INSTALL_FAILURE:
                    pt_this->pf_preprocess_cb(FALSE,
                                              UPDATER_EXIT_REASON_DECRYP_FAIL);
                    break;
				case ULI_NEW_EVENT_DOWNLOAD_FAILURE:
					pt_this->pf_preprocess_cb(FALSE,
                                              UPDATER_EXIT_REASON_DOWNLOAD_FAIL);
                    break;
                default:
                    pt_this->pf_preprocess_cb(FALSE,
                                              UPDATER_EXIT_REASON_CHECKING_UPDATE_FAIL);
            }
        }
        DBG_LOG_PRINT(("%s_%d \n",__FUNCTION__,__LINE__));
        pt_this->pf_preprocess_cb = NULL;
    }

    return;
}

static VOID _nav_updater_uli_process_show_cb(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    UINT32  ui4_status = (UINT32)pv_tag3;

    if (pt_this->e_method == UPDATER_ULI_METHOD_USB)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_process_show_cb ui4_status[%d]\n",ui4_status));

        /* Allow user press Power key */
        a_amb_enable_power_key(TRUE);
        if (1 == ui4_status)
        {
            /* for cmd stick*/
            nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_ULI_COMMAND_STICK, NULL);
        }
        else
        {
            /*usb downloading*/
            nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_ULI_USB, NULL);
        }
    }
    else if (pt_this->e_method == UPDATER_ULI_METHOD_INTNT)
    {
        /* just for menu trigger network upgrade
        so here should not in oobe condition*/
        UINT16 ui2_status = 0;
        BOOL   b_is_in_wzd_condition = FALSE;

        /*check the wizard status*/
        if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK
                                && (WZD_UTIL_GET_STATUS_STATE(ui2_status) == WZD_STATE_RESUME_C4TV))
        {
            b_is_in_wzd_condition = TRUE;
        }
        else
        {
            b_is_in_wzd_condition = FALSE;
        }

        if (!b_is_in_wzd_condition)
        {
            /*downloading*/
            nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_ULI_USB, NULL);
        }

    }
    else
    {
        /* do nothing*/
    }

}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_set_next_wakeup_time
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_set_next_wakeup_time(
    UINT32                  ui4_delay
)
{
    TIME_T                  t_current_utc = 0;
    DTG_T                   t_loc_dtg;
    //UINT32                  ui4_day_sec;
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;

    /* get current UTC time */
    t_current_utc = c_dt_get_utc(NULL, NULL);

    /* initialize t_loc_dtg */
    c_memset((VOID*)&t_loc_dtg, 0, sizeof(DTG_T));

    /* convert current utc time to DTG local time */
    c_dt_utc_sec_to_loc_dtg(t_current_utc, &t_loc_dtg);

    //ui4_day_sec = (t_loc_dtg.ui1_hr * 3600) + (t_loc_dtg.ui1_min * 60) + (t_loc_dtg.ui1_sec);

    pt_this->ui4_avail_delay = ui4_delay;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_chk_schedule
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_chk_schedule(
    VOID
)
{
    UINT32    ui4_update_idx = 0;
    UINT32    ui4_delay = 0;
    INT32     i4_ret;
#ifdef ULI_USE_ODL_LIB

    i4_ret = a_uli_check_updates();

    if (ULIR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_check_updates() failed, %d\n", i4_ret));
        return NAVR_FAIL;
    }

    i4_ret = a_uli_get_download_schedule(ui4_update_idx, &ui4_delay);

    if (ULIR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_get_download_schedule() failed, %d\n", i4_ret));
        return NAVR_FAIL;
    }
#endif

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_get_download_schedule() ===> delay %d seconds\n", ui4_delay));

    /* if schedule delay > NAV_UPDATER_ULI_MAX_WAKE_UP_TIME, set new wakeup time & go standby */
    if (ui4_delay > NAV_UPDATER_ULI_MAX_WAKE_UP_TIME)
    {
        /* set new wakeup time */
        i4_ret = _nav_updater_uli_set_next_wakeup_time(ui4_delay - NAV_UPDATER_ULI_CHK_UPDATE_TIME);
        if (NAVR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_set_next_wakeup_time() failed, %d\n", i4_ret));
            return NAVR_FAIL;
        }

        return NAVR_DELAY_ACTION;
    }
    else
    {
        return NAVR_OK;
    }
}

static INT32 _nav_updater_uli_usb_cmd_script_running(CHAR* str_script_path)
{
	cJSON *proot,*pc_header,*pc_version,*pc_model_group,*pc_model_name,*pc_command,*pc_index_cmd,*pc_oem_msg;
	INT32 i4_ret = ULIR_OK;
	INT32 i4_file_len = 0;
	INT32 ui4_read_cnt = 0;
	INT32 ui4_cmd_index = 1;
	FILE*		fl = NULL;
	FILE*		cmd_pf = NULL;
	FILE*		cmd_complete_pf = NULL;
	CHAR*	   usb_cmd_buf = NULL;


	CHAR usb_cmd_index[128] = {0};
	NAV_UPGRADE_LOG_PRINT(("str_script_path:%s \n",str_script_path));
	fl = fopen(str_script_path, "r");
	system("touch /upgrade/usb_cmd_installing");
	if (fl == NULL)
	{
		return ULIR_INV_ARG;
	}
	i4_ret = fseek(fl, 0, SEEK_END);
	i4_file_len = ftell(fl);
   if(NULL ==( usb_cmd_buf = (CHAR*)malloc(i4_file_len + 1)))
	{
		NAV_UPGRADE_LOG_PRINT((" failed to memalloc memory!\n"));
		return ULIR_INV_ARG;
	}
   fseek(fl, 0, SEEK_SET);
   memset(usb_cmd_buf,0,i4_file_len + 1);
	ui4_read_cnt = fread(usb_cmd_buf,i4_file_len,1,fl);
	if(ui4_read_cnt <= 0)
	{
		NAV_UPGRADE_LOG_PRINT(("failed to read content!\n"));
		return ULIR_INV_ARG;
	}
	NAV_UPGRADE_LOG_PRINT(("usb cmd:%s \n",usb_cmd_buf));
	if(NULL == (proot = cJSON_Parse(usb_cmd_buf)))
	{
		NAV_UPGRADE_LOG_PRINT(("failed to parse content cJSON_Parse!,try verify compress file\n"));
		cmd_complete_pf = fopen("/upgrade/usb_cmd_complete","wr");
		fclose(cmd_complete_pf);
		return ULIR_INV_ARG;
	}


	pc_header = cJSON_GetObjectItem(proot,"Header");
	if(pc_header)
	{
		NAV_UPGRADE_LOG_PRINT(("Header:%s \n",pc_header->valuestring));
	}

	pc_version = cJSON_GetObjectItem(proot,"Version");
	if(pc_version)
	{
		NAV_UPGRADE_LOG_PRINT(("Version:%s \n",pc_version->valuestring));
	}

	pc_model_group = cJSON_GetObjectItem(proot,"Model Group");
	if(pc_model_group)
	{
		NAV_UPGRADE_LOG_PRINT(("Model Group:%s \n",pc_model_group->valuestring));
	}

	pc_model_name = cJSON_GetObjectItem(proot,"Model Name");
	if(pc_model_name)
	{
		NAV_UPGRADE_LOG_PRINT(("Model Name:%s \n",pc_model_name->valuestring));
	}

	pc_oem_msg = cJSON_GetObjectItem(proot,"Oem_msg");
	if(pc_oem_msg)
	{
		NAV_UPGRADE_LOG_PRINT(("oem msg:%s \n",pc_oem_msg->valuestring));
	}


	pc_command = cJSON_GetObjectItem(proot,"commands");
	if(pc_command)
	{
		cmd_pf = fopen("/upgrade/usb_cmd_stick.sh","wr");
		sprintf(usb_cmd_index,"%d",ui4_cmd_index);
		while((pc_index_cmd = cJSON_GetObjectItem(pc_command,usb_cmd_index))!= NULL)
		{
			NAV_UPGRADE_LOG_PRINT(("index:%s \n",usb_cmd_index));
			NAV_UPGRADE_LOG_PRINT(("cmd:%s \n",pc_index_cmd->valuestring));
			fprintf(cmd_pf, "%s \n", pc_index_cmd->valuestring);


			ui4_cmd_index++;
			sprintf(usb_cmd_index,"%d",ui4_cmd_index);
		}
		fclose(fl);
		fclose(cmd_pf);
		system("sh /upgrade/usb_cmd_stick.sh");
		cmd_complete_pf = fopen("/upgrade/usb_cmd_complete","wr");
		fclose(cmd_complete_pf);
		if(pc_oem_msg)
		{
			NAV_UPGRADE_LOG_PRINT(("need set oem message\n"));
		}
		system("rm /upgrade/usb_cmd_stick.sh");
		if(pc_oem_msg)
		{
			a_uli_custom_set_oem_msg(pc_oem_msg->valuestring,strlen(pc_oem_msg->valuestring));
		}
		if(usb_cmd_buf)
		{
			free(usb_cmd_buf);
		}

	}



}


void Read_filevalue(CHAR* p_KeyPath,CHAR** s_value,INT32* length)
{
	FILE *fp = NULL;
	CHAR szKeyPath[1024];
	INT32 value_length = 0;


	if(NULL == (fp = fopen(p_KeyPath, "r")))
	{
		printf( "fopen[%s] failed \n", p_KeyPath);
		return;
	}
	fseek(fp, 0, 2);
	value_length = ftell(fp);
	*s_value=(CHAR *)c_mem_alloc(value_length+10);
	if(*s_value == NULL)
	{
		NAV_UPGRADE_LOG_PRINT(("malloc fail \n"));
		return;
	}
	fseek(fp, 0, 0);
	NAV_UPGRADE_LOG_PRINT(("sign length:%d \n",value_length));
	fread(*s_value,value_length,1,fp);
	*length = value_length;

	fclose(fp);


}

RSA* Read_publicKey(CHAR* p_KeyPath)
{
	FILE *fp = NULL;
	CHAR szKeyPath[1024];
	RSA* priRsa = NULL, *pubRsa = NULL, *pOut = NULL;


	if(NULL == (fp = fopen(p_KeyPath, "r")))
	{
		NAV_UPGRADE_LOG_PRINT(( "fopen[%s] failed \n", p_KeyPath));
		return NULL;
	}

	priRsa = PEM_read_RSA_PUBKEY(fp, NULL, NULL,NULL);
	if(NULL == priRsa)
	{
		NAV_UPGRADE_LOG_PRINT(("PEM_read_PrivateKey failed !!!\n"));
		fclose(fp);
		return NULL;
	}
	fclose(fp);

	pOut = priRsa;
	return pOut;
}
void printhex(UINT8* md,INT32 len)
{
	INT32 i = 0;
	for(i =0;i<len;i++)
	{
		md[i] = md[i]&0xFF;
		NAV_UPGRADE_LOG_PRINT(("md:%x \n",md[i]));
	}
}

static INT32 _nav_updater_check_signature_of_cmd_stick(VOID)
{


    UINT32            ui4_mg_value;
    CHAR              model_group[32] = {0};
    CHAR*             cmd_type = ".sh";
	char*             str_signature_end = "sign";
	BOOL              b_signature_exist = FALSE;
	BOOL              b_script_file_exist = FALSE;
	CHAR str_signature_path[256] = {0};
	CHAR str_stript_path[256] = {0};
	CHAR str_public_key_path[256] = {0};
	CHAR*			  str_clear_value = NULL;
	CHAR*			  str_sign_value = NULL;

	CHAR signature_file_name[FM_MAX_FILE_LEN] = {0};
	CHAR script_file_name[FM_MAX_FILE_LEN] = {0};
	CHAR str_rm_cmd[256] = {0};

	UINT8 md[NAV_UPDATER_SHA_LENGTH] = {0};
	//CHAR sign_value[1024]={0};
	//CHAR clear_value[1024*4] = {0};
	INT32 ui4_cmd_verify = 0;
	INT32 sign_len;
	INT32 clear_len;
	RSA *rsa=NULL;
	HANDLE_T			h_dir_hdl;
	FM_DIR_ENTRY_T		t_dir_entr;
	UINT32				ui4_num_entr;
	INT32				i4_ret;
	INT32				i;

    if(NAVR_OK != _nav_update_get_platform_mg_value(&ui4_mg_value))
    {
        NAV_UPGRADE_LOG_PRINT(("zile_multi,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        return NAVR_FAIL;
    }

    model_group[0] = 'm';
    model_group[1] = 'g';
    sprintf((model_group+2),"%x",ui4_mg_value);

    model_group[strlen(model_group)] = '_';
	sprintf(str_public_key_path,"%s%s%s","/basic/",model_group,"sign_cmd_stick_public.pem");
	NAV_UPGRADE_LOG_PRINT(("str_public_key_path:%s \n",str_public_key_path));

    {


        i4_ret = c_fm_open_dir(FM_ROOT_HANDLE, "/upgrade", &h_dir_hdl);
        if (FMR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT(("zile_multi,ERROR,%d,%s,%s\n",__LINE__,__func__,__FILE__));
            return NAVR_FAIL;
        }

        do
        {
            CHAR file_name_lower_case[FM_MAX_FILE_LEN] = {0};
            c_memset(&t_dir_entr, 0, sizeof(FM_DIR_ENTRY_T));

            i4_ret = c_fm_read_dir_entries(h_dir_hdl, &t_dir_entr, 1, &ui4_num_entr);
            if (FMR_EOF == i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT(("zile_multi,no more files,%d,%s,%s\n",__LINE__,__func__,__FILE__));
                break;
            }
            else if (FMR_OK != i4_ret || 0 == ui4_num_entr)
            {
                NAV_UPGRADE_LOG_PRINT(("zile_multi,ERROR,%d,%s,%s\n",__LINE__,__func__,__FILE__));
                break;
            }
			DBG_LOG_PRINT(("t_dir_entr.s_name:%s \n",t_dir_entr.s_name));
            if ((0 == c_strcmp(t_dir_entr.s_name, "."))  ||
                (0 == c_strcmp(t_dir_entr.s_name, "..")) ||
                FM_IS_DIR(t_dir_entr.t_file_info.ui4_mode))
            {
                continue;
            }
            for(i = 0;t_dir_entr.s_name[i] && i < FM_MAX_FILE_LEN-1;++i)
            {
                file_name_lower_case[i] = tolower(t_dir_entr.s_name[i]);
            }
            if(_start_with(file_name_lower_case,model_group) && _end_with(file_name_lower_case,cmd_type))
            {
                b_script_file_exist = TRUE;
				strcpy(script_file_name,t_dir_entr.s_name);
            }
            if(_start_with(file_name_lower_case,model_group) && _end_with(file_name_lower_case,str_signature_end))
            {
                b_signature_exist = TRUE;
				strcpy(signature_file_name,t_dir_entr.s_name);
            }
			if(b_signature_exist&&b_script_file_exist)
			{
				NAV_UPGRADE_LOG_PRINT(("file check sucess \n"));
				break;
			}
        }while(TRUE);

        i4_ret = c_fm_close(h_dir_hdl);
        if (FMR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT(("ERROR,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        }
		if(b_signature_exist&&b_script_file_exist)
		{

			sprintf(str_signature_path,"%s/%s","/upgrade/",signature_file_name);
			sprintf(str_stript_path,"%s/%s","/upgrade/",script_file_name);
			NAV_UPGRADE_LOG_PRINT(("signature_file_name:%s  script_file_name:%s \n",signature_file_name,script_file_name));
			Read_filevalue(str_signature_path,&str_sign_value,&sign_len);
	  		Read_filevalue(str_stript_path,&str_clear_value,&clear_len);
			if(str_sign_value == NULL ||
				str_clear_value == NULL)
			{
				NAV_UPGRADE_LOG_PRINT(("read file fail \n"));
				return NAVR_FAIL;
			}
			rsa = Read_publicKey(str_public_key_path);

			//NAV_UPGRADE_LOG_PRINT(("clear_len:%d str_clear_value:%s \n",clear_len,str_clear_value));
			SHA1(str_clear_value,clear_len,md);
			printhex(md,NAV_UPDATER_SHA_LENGTH);

			if(rsa == NULL)
			{
				NAV_UPGRADE_LOG_PRINT(("read RSA fail \n"));
				return NAVR_FAIL;
			}
			ui4_cmd_verify = RSA_verify(NID_sha1, md, NAV_UPDATER_SHA_LENGTH,
               str_sign_value, sign_len, rsa);
			NAV_UPGRADE_LOG_PRINT(("returen_value:%d  \n",ui4_cmd_verify));
		}
		else
		{
			return NAVR_FAIL;
		}
		sprintf(str_rm_cmd,"%s%s","rm ",str_signature_path);
		//NAV_UPGRADE_LOG_PRINT(("str_rm_cmd:%s  \n",str_rm_cmd));
		system(str_rm_cmd);
		c_memset(str_rm_cmd, 0, sizeof(str_rm_cmd));
		if(ui4_cmd_verify == 1)
		{
			_nav_updater_uli_usb_cmd_script_running(str_stript_path);
			NAV_UPGRADE_LOG_PRINT(("cmd stick verify pass,will run this script  \n"));
		}
		sprintf(str_rm_cmd,"%s%s","rm ",str_stript_path);
		//NAV_UPGRADE_LOG_PRINT(("str_rm_cmd:%s  \n",str_rm_cmd));
		system(str_rm_cmd);
		if(str_clear_value)
		{
			c_mem_free(str_clear_value);
		}
		if(str_sign_value)
		{
			c_mem_free(str_sign_value);
		}
    }
    return NAVR_OK;

}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_usb_cb_handler
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static VOID _nav_updater_uli_cb_handler(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    UPDATER_ULI_CTRL_T*     pt_this        = &t_g_uli_ctrl;
    INT32      e_event        = (ULI_UPDATE_EVENT_T)pv_tag1;
    NAV_UPDATER_TRIGGER_TYPE_T e_trigger_type = TRIGGER_TYPE_NONE;

    BOOL                    b_uli_agent_ok = pt_this->b_uli_agent_ok;

    nav_updater_uli_get_trigger_type(&e_trigger_type);

    if (FALSE == pt_this->b_uli_agent_in_progess&&e_event != ULI_NEW_EVENT_USB_CMD_VERIFY)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Ignore ULI agent's callback msg, event: %d\n", e_event));
        return;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Get ULI agent's callback msg, event: %d\n", e_event));
    }

    switch(e_event)
    {
        /* end of update session */
        case ULI_NEW_EVENT_END:
        case ULI_EVENT_END:
            pt_this->b_uli_evt_end = TRUE;
            pt_this->b_uli_agent_in_progess = FALSE;

            nav_updater_uli_set_update_stage(STAGE_NONE);

            if (FALSE == b_uli_agent_ok)
            {
               /* download fail*/

               NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cb_handler ULI_EVENT_END [Download fail]\n"));
                nav_updater_uli_set_fw_status(CHECK_STATE_DOWNLOAD_FAIL);
                /* call back to BGM to handle the fail case */
                _nav_updater_cb_bgm(NAV_UPDATER_ULI_FAIL);
            }
            else
            {
                BOOL b_is_to_continue = FALSE;
                /* reset */
                pt_this->b_uli_agent_ok = FALSE;

                pt_this->b_uli_agent_download_ok = TRUE;

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cb_handler ULI_EVENT_END [Download sucuss]\n"));
                nav_updater_uli_set_fw_status(CHECK_STATE_DOWNLOAD_SUCESS);

                /* rename the firmware name to mark its integrity is ok */
                CHAR    s_cmd[512] = {0};
                CHAR    s_path[128] = {0};

                _nav_updater_uli_get_path(s_path, 128);

                c_sprintf(s_cmd, "mv %s %s",
                                 UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_NAME,
                                 s_path);
                system(s_cmd);
                sync();

                /*For rest should wait the status have been get by the rest app*/
                nav_updater_check_continue_next_step(NAV_UPDATER_CHK_STEP_DOWNLOADING_OK,&b_is_to_continue);
            }

            /* call back the core updater */
            nav_request_context_switch(
                            _nav_updater_uli_preprocess_cb,
                            (VOID*)((FALSE == b_uli_agent_ok) ? FALSE : TRUE),
                            NULL,
                            NULL);
            break;
        case ULI_NEW_EVENT_DOWNLOAD_INSTALLED:
        case ULI_EVENT_DOWNLOAD_INSTALLED:

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cb_handler ULI_EVENT_DOWNLOAD_INSTALLED [Download complete]\n"));
            /* download completed (sucss)*/
            pt_this->b_uli_agent_ok = TRUE;
            break;
        case ULI_NEW_EVENT_CHECKING_UPDATE_FAILURE:
		case ULI_NEW_EVENT_DOWNLOAD_FAILURE:
        case ULI_EVENT_CHECKING_UPDATE_FAILURE:
        case ULI_EVENT_NO_UPDATE:

            if (ULI_EVENT_CHECKING_UPDATE_FAILURE == e_event || ULI_NEW_EVENT_CHECKING_UPDATE_FAILURE == e_event)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cb_handler ULI_EVENT_CHECKING_UPDATE_FAILURE [FW Check fail]\n"));
                nav_updater_uli_set_fw_status(CHECK_STATE_CHECK_FAIL);

                nav_updater_uli_set_fw_avaliable(CHECK_STATE_CHECK_FAIL);
            }
            else if (ULI_NEW_EVENT_DOWNLOAD_FAILURE == e_event)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cb_handler ULI_NEW_EVENT_DOWNLOAD_FAILURE [FW download fail]\n"));
                nav_updater_uli_set_fw_status(CHECK_STATE_DOWNLOAD_FAIL);
                nav_updater_uli_set_fw_avaliable(CHECK_STATE_DOWNLOAD_FAIL);

            }
			if(UPDATER_USB_TYPE_CMD==e_usb_update_type)
			{
				a_cfg_cust_led_blinking_stop();
			}

            pt_this->e_fail_reason = e_event;
			if(ULI_NEW_EVENT_DOWNLOAD_FAILURE == e_event)
			{
				nav_updater_uli_set_update_stage(STAGE_NONE);
				nav_request_context_switch(
					_nav_updater_uli_preprocess_cb,
					(VOID*)(FALSE),
					NULL,
					NULL);
			}

            if ((TRIGGER_TYPE_ULI_NETWORK_FW_CHECK == e_trigger_type) || (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE == e_trigger_type))
            {
                INT32     i4_force_status = 0;
                nav_updater_uli_set_update_stage(STAGE_NONE);

                nav_update_send_fw_check_msg_to_observer(UPDATER_CHECK_UPDATE_COND_COMPLETE, i4_force_status);

                /* here should exit*/

                /* call back the core updater */
                nav_request_context_switch(
                                _nav_updater_uli_preprocess_cb,
                                (VOID*)(TRUE),
                                NULL,
                                NULL);
            }
            break;

        case ULI_EVENT_INSTALL_FAILURE:
            pt_this->e_fail_reason = e_event;
            break;

        case ULI_EVENT_COMMANDS_DETECTED:
        {
            /*cmd stick*/
            UINT32   ui4_status = 1;
            pt_this->b_uli_evt_update = TRUE;
            pt_this->e_fail_reason = e_event;

            /*Show cmd stick warning*/
            if((UPDATER_USB_TYPE_CMD!=e_usb_update_type))
            {
                _nav_updater_uli_process_show_cb((VOID*)"COMMANDS STICK DETECTED,",
                                                 (VOID*)"DONE PROCESSING COMMANDS",
                                                  (VOID*)ui4_status);

                /* delay 5s, TV will reboot then */
                c_thread_delay(5000);
            }
            break;
        }
        case ULI_NEW_EVENT_CHECKING_UPDATE:
            nav_updater_uli_set_update_stage(STAGE_FW_WAITING_RESULT);

            break;
		case ULI_NEW_EVENT_USB_CMD_VERIFY:
		{
				_nav_updater_check_signature_of_cmd_stick();
		}
			break;
        case ULI_NEW_EVENT_UPDATE_AVAIABLE:
        case ULI_EVENT_UPDATE:
        {
            INT32                i4_ret;
            ULI_NEW_UPDATE_INFO_T    t_update_info;
			UINT32	 ui4_status = 0;


            nav_updater_uli_set_fw_status(CHECK_STATE_CHECK_AVALIABLE);
            nav_updater_uli_set_fw_avaliable(CHECK_STATE_CHECK_AVALIABLE);
			i4_ret = a_uli_custom_get_update_info(&t_update_info);
			if ((TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM == e_trigger_type)&&
				(pt_this->e_method == UPDATER_ULI_METHOD_USB))
			{
			    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Update ver: %s\n", t_update_info.ps_version));
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Update info: %s\n", t_update_info.ps_info));
				if(e_usb_update_type == UPDATER_USB_TYPE_UTV)
				{
	                nav_updater_set_update_ver_string((CHAR*)(t_update_info.ps_version));
				}
                /* call back the core updater */
                nav_request_context_switch(
                                _nav_updater_uli_preprocess_cb,
                                (VOID*)(TRUE),
                                NULL,
                                                 NULL);
				break;
			}

            /*check force flag*/
            pt_this->b_uli_evt_update = TRUE;



            if (ULIR_OK == i4_ret)
            {

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Update ver: %s\n", t_update_info.ps_version));
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Update info: %s\n", t_update_info.ps_info));

                nav_updater_set_update_ver_string((CHAR*)(t_update_info.ps_version));

                if (FALSE == nav_updater_is_bgm_ex())
                {
                    if (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK != e_trigger_type)
                    {
                        /*show usb downloading warning*/
                        _nav_updater_uli_process_show_cb((VOID*)(t_update_info.ps_version),
                                                     (VOID*)(t_update_info.ps_info),
                                                     (VOID*)ui4_status);
                    }
                }
            }

            if (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK == e_trigger_type)
            {
                _nav_updater_uli_abort_updates();
            }
            else if (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE == e_trigger_type)
            {
                BOOL      b_is_option = FALSE;
                INT32     i4_force_status = 0;
                nav_updater_uli_set_update_stage(STAGE_NONE);
                //b_is_option = a_uli_is_optional_update_mode();

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cb_handler ULI_EVENT_UPDATE b_is_option[%d]\n", b_is_option));

                if (b_is_option)
                {
                    nav_updater_uli_set_fw_force_update_flag(FALSE);
                    i4_force_status = 0;
                }
                else
                {
                    nav_updater_uli_set_fw_force_update_flag(TRUE);

                    i4_force_status = 1;
                }

                nav_update_send_fw_check_msg_to_observer(UPDATER_CHECK_UPDATE_COND_COMPLETE, i4_force_status);

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cb_handler ULI_EVENT_UPDATE [FW Check valid],b_is_option[%d]\n",
                       b_is_option));

                /* here should exit*/

                /* call back the core updater */
                nav_request_context_switch(
                                _nav_updater_uli_preprocess_cb,
                                (VOID*)(TRUE),
                                NULL,
                                                 NULL);
            }
            break;
        }

        /* set new wakeup time */
        case ULI_EVENT_DOWNLOAD_FUTURE:
            _nav_updater_uli_chk_schedule();
            break;
        case ULI_EVENT_DOWNLOADING_COMPONENT:
            nav_updater_uli_set_fw_status(CHECK_STATE_DOWNLOADING);
            break;

        default:
            ;
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_cb
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_cb(
    ULI_UPDATE_EVENT_T    e_event
)
{
    nav_request_context_switch(_nav_updater_uli_cb_handler,
                               (VOID*)(e_event),
                               NULL,
                               NULL);
    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_is_3rd_part_ready
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_uli_is_3rd_part_ready(
    VOID
)
{
    FM_FS_INFO_T    t_fm_fs_info;
    INT32           i4_ret;

    i4_ret = c_fm_get_fs_info(FM_ROOT_HANDLE,
                              "/upgrade",
                              &t_fm_fs_info);
    if (FMR_OK != i4_ret)
    {
        return FALSE;
    }

    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_set_mode
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_uli_get_updates(
    UPDATER_ULI_METHOD_T     e_method
)
{
    ULI_NEW_UPDATE_MODE_T        t_mode;
    NAV_UPDATER_TRIGGER_TYPE_T e_trigger_type = TRIGGER_TYPE_NONE;
    INT32                    i4_ret;
    UINT8                    ui1_retry = 0;

    switch(e_method)
    {
        case UPDATER_ULI_METHOD_USB:
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Config ULI agent to UPDATER_ULI_METHOD_USB\n"));
            t_mode.e_delivery = ULI_DELIVERY_FILE_ASYNC;
            t_mode.b_from_server = FALSE;
            break;

        case UPDATER_ULI_METHOD_INTNT:
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Config ULI agent to UPDATER_ULI_METHOD_INTNT\n"));
            t_mode.e_delivery = ULI_DELIVERY_INTERNET_ASYNC;
            t_mode.b_from_server = TRUE;
            break;

        default:
            return NAVR_FAIL;
    }
    t_mode.b_direct_install = TRUE;
    t_mode.pf_nfy           = _nav_updater_uli_cb;
    t_mode.pf_action        = NULL;
    t_mode.b_factory        = FALSE;
	if(TRUE == nav_updater_is_bgm_ex())
	{
    	t_mode.e_action         = ULI_ACTION_BGM;
	}
	else
	{
		t_mode.e_action         = ULI_ACTION_APPROVE_ALL_OPTIONAL;
	}
	NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"check upgrade partition start \n"));

    /* make sure the 3rd partition is already mounted!! */
    do
    {
        if (TRUE == _nav_updater_uli_is_3rd_part_ready())
        {
            break;
        }
        c_thread_delay(1000);
        ui1_retry++;
    }
    while(ui1_retry < NAV_UPDATER_ULI_MAX_CHK_3RD_RETRY_NUM);
	NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"check upgrade partition end \n"));

    nav_updater_uli_get_trigger_type(&e_trigger_type);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_get_updates() e_trigger_type[%d]\n", e_trigger_type));

    if ((TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD == e_trigger_type)
        || (TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)
        || (TRIGGER_TYPE_ULI_BGM_NETWORK_FW_DOWNLOAD_AND_INSTALL == e_trigger_type))
    {

        UINT16 ui2_status = 0;
        BOOL   b_is_in_wzd_condition = FALSE;

        /*check the wizard status*/
        if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK
                                && (WZD_UTIL_GET_STATUS_STATE(ui2_status) == WZD_STATE_RESUME_C4TV))
        {
            b_is_in_wzd_condition = TRUE;
        }
        else
        {
            b_is_in_wzd_condition = FALSE;
        }

        nav_updater_uli_set_update_stage(STAGE_FW_DOWNLOADING);

        nav_updater_uli_set_fw_status(CHECK_STATE_CHECKING);

        if ((TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD == e_trigger_type)
            || (TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD_AND_INSTALL == e_trigger_type))
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_get_updates() nav_update_reset_download_check_timer\n"));
            nav_update_reset_download_check_timer();
        }
		#if 0
        if ((TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)
              || ((TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)
                    && (!b_is_in_wzd_condition)
                    && (a_am_is_power_on())))
        {
            nav_update_reset_utv_download_check_timer();
        }
		#endif
        /* set to ULI agent */
        i4_ret = a_uli_custom_triger_sw_download_and_install(&t_mode);

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_updater_uli_get_updates a_uli_get_updates() fw_download e_method[%d], i4_ret[%d]\n",
                        e_method,i4_ret));

        if (ULIR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_get_updates() failed, %d\n", i4_ret));
            return NAVR_FAIL;
        }
    }
    else if ((TRIGGER_TYPE_ULI_NETWORK_FW_CHECK == e_trigger_type) || (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE == e_trigger_type))
    {
        /*just fheck the fw*/
        nav_updater_uli_set_update_stage(STAGE_FW_CHECKING);
        nav_updater_uli_set_fw_status(CHECK_STATE_CHECKING);

        /* here shoud call the uli check api*/
        //a_uli_scan_updates(&t_mode);
        a_uli_custom_check_sw_update_avaiable(&t_mode);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_updater_uli_get_updates fw_checking e_method[%d], i4_ret[%d]\n",
                    e_method,i4_ret));

        if (ULIR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_scan_updates() failed, %d\n", i4_ret));
            return NAVR_FAIL;
        }
    }
	else if(TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM == e_trigger_type)
	{
		/*just fheck the fw*/
        nav_updater_uli_set_update_stage(STAGE_FW_CHECKING);
        nav_updater_uli_set_fw_status(CHECK_STATE_CHECKING);


        nav_update_reset_utv_download_check_timer();


        /* here shoud call the uli check api*/
        //a_uli_scan_updates(&t_mode);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"usb_update_path:%s \n", usb_update_path));
        i4_ret = a_uli_custom_check_usb_update_avaiable(&t_mode,usb_update_path);
        if(UPDATER_USB_TYPE_CMD==a_nav_updater_uli_get_usb_upgrade_type())
        {
			a_cfg_cust_led_blinking_start(5);
			NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_preprocess_cb: LED 800ms \n"));
        }

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_updater_uli_get_updates fw_checking e_method[%d], i4_ret[%d]\n",
                    e_method,i4_ret));

        if (ULIR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_scan_updates() failed, %d\n", i4_ret));
            return NAVR_FAIL;
        }
	}
	else if(TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)
	{
		/*just fheck the fw*/
        nav_updater_uli_set_update_stage(STAGE_FW_DOWNLOADING);
        nav_updater_uli_set_fw_status(CHECK_STATE_DOWNLOADING);

    	if(UPDATER_USB_TYPE_UTV==a_nav_updater_uli_get_usb_upgrade_type())
    	{
        	nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_ULI_USB, NULL);
    	}

        nav_update_reset_utv_download_check_timer();
        if(UPDATER_USB_TYPE_CMD==a_nav_updater_uli_get_usb_upgrade_type())
        {
			NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_preprocess_cb: LED 500ms \n"));
			a_cfg_cust_led_blinking_start(4);
        }

        i4_ret = a_uli_custom_triger_sw_download_and_install(&t_mode);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_updater_uli_get_updates fw_checking e_method[%d], i4_ret[%d]\n",
                    e_method,i4_ret));

        if (ULIR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_scan_updates() failed, %d\n", i4_ret));
            return NAVR_FAIL;
        }
	}
    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_uli_show_oob_mode_osd
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_show_oob_mode_osd(
    VOID
)
{
    UTF16_T    w2s_str[256];

    /* set dialog text */
    c_uc_ps_to_w2s("OOB Processing...", w2s_str, 256);

    /* prompt OSD */
    nav_updater_show_dialog(UPDATER_SHOW_DLG_ULI_OOB_PROCESSING, w2s_str);
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_uli_enter_oob_mode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_enter_oob_mode(
    BOOL       b_enter
)
{
    CHAR       s_str[256];
    UTF16_T    w2s_str[256];

    c_snprintf(s_str, 256,
               "SW Update Version: OOB %s\n"
               "Let the TV Reboot\n"
               "Do not power off TV, update in progesss.\n"
               "TV will restart when done.",
               (TRUE == b_enter) ? "START" : "END", NAV_UPDATER_ULI_OOB_TEST_START_FILE_NAME);

    /* set dialog text */
    c_uc_ps_to_w2s(s_str, w2s_str, 256);

    /* prompt OSD */
    nav_updater_show_dialog(UPDATER_SHOW_DLG_ULI_OOB_ENTER, w2s_str);

    if (TRUE == b_enter)
    {
        CHAR    s_cmd[256] = {0};

        /* enter OOB mode */
        #ifdef ULI_USE_ODL_LIB
        a_uli_perform_factory_mode();
        #endif
        c_sprintf(s_cmd,
                  "touch %s",
                  UPDATER_XML_PATH "/" NAV_UPDATER_ULI_IN_OOB_TEST_FILE_NAME);

        system(s_cmd);
    }
    else
    {
        /* exit OOB mode */
        #ifdef ULI_USE_ODL_LIB
        a_uli_reset_component_manifest();
        #endif
        c_fm_delete_file(FM_ROOT_HANDLE,
                         UPDATER_XML_PATH "/" NAV_UPDATER_ULI_IN_OOB_TEST_FILE_NAME);
    }

    /* Flush file system buffers */
    sync();

    nav_updater_reboot_system();
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_uli_is_oob_mode
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_uli_is_oob_mode(
    VOID
)
{
#if 0
    ULI_PROJECT_STATUS_STRUCT    t_status;
    INT32                        i4_ret;

    c_memset((VOID*)&t_status, 0, sizeof(ULI_PROJECT_STATUS_STRUCT));

    i4_ret = a_uli_on_status_request(&t_status);

    if ((ULIR_OK != i4_ret)
        || (0 == (NAV_UPDATER_ULI_STATUS_MASK_FACTORY_TEST_MODE & t_status.usStatusMask)))
    {
        return FALSE;
    }

    return FALSE;
#else
    FM_FILE_INFO_T    t_file_info;

    if (FMR_OK == c_fm_get_info_by_name(FM_ROOT_HANDLE,
                                        UPDATER_XML_PATH "/" NAV_UPDATER_ULI_IN_OOB_TEST_FILE_NAME,
                                        &t_file_info))
    {
        return TRUE;
    }

    return FALSE;
#endif
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_uli_is_oob_test_start_file
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_uli_is_oob_test_start_file(
    VOID
)
{
    CHAR              s_mnt_point[512] = { 0 };
    CHAR              s_file_name[512] = { 0 };
    SIZE_T            z_mnt_point_size = 512;
    UINT32            ui4_mnt_count;
    UINT8             ui1_i;
    FM_FILE_INFO_T    t_file_info;

    if ((RMVR_OK != a_rmv_dev_get_mnt_count(&ui4_mnt_count))
         || (0 == ui4_mnt_count))
    {
        return FALSE;
    }

    for (ui1_i = 0 ; ui1_i < ui4_mnt_count ; ui1_i++)
    {
        if (RMVR_OK != a_rmv_dev_get_mnt_point(ui1_i, &z_mnt_point_size, s_mnt_point))
        {
            continue;
        }
        c_snprintf(s_file_name, 512, "%s/%s", s_mnt_point, NAV_UPDATER_ULI_OOB_TEST_START_FILE_NAME);

        if (FMR_OK == c_fm_get_info_by_name(FM_ROOT_HANDLE, s_file_name, &t_file_info))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_uli_is_oob_test_end_file
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_uli_is_oob_test_end_file(
    VOID
)
{
    CHAR              s_mnt_point[512] = { 0 };
    CHAR              s_file_name[512] = { 0 };
    SIZE_T            z_mnt_point_size = 512;
    UINT32            ui4_mnt_count;
    UINT8             ui1_i;
    FM_FILE_INFO_T    t_file_info;

    if ((RMVR_OK != a_rmv_dev_get_mnt_count(&ui4_mnt_count))
         || (0 == ui4_mnt_count))
    {
        return FALSE;
    }

    for (ui1_i = 0 ; ui1_i < ui4_mnt_count ; ui1_i++)
    {
        if (RMVR_OK != a_rmv_dev_get_mnt_point(ui1_i, &z_mnt_point_size, s_mnt_point))
        {
            continue;
        }
        c_snprintf(s_file_name, 512, "%s/%s", s_mnt_point, NAV_UPDATER_ULI_OOB_TEST_END_FILE_NAME);

        if (FMR_OK == c_fm_get_info_by_name(FM_ROOT_HANDLE, s_file_name, &t_file_info))
        {
            return TRUE;
        }
    }

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_uli_is_secure_fw_ready
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_uli_is_secure_fw_ready(
    VOID
)
{
    CHAR              s_mnt_point[512] = { 0 };
    CHAR              s_file_name[512] = { 0 };
    SIZE_T            z_mnt_point_size = 512;
    UINT32            ui4_mnt_count;
    UINT8             ui1_i;
    FM_FILE_INFO_T    t_file_info;

    if ((RMVR_OK != a_rmv_dev_get_mnt_count(&ui4_mnt_count))
         || (0 == ui4_mnt_count))
    {
        return FALSE;
    }

    for (ui1_i = 0 ; ui1_i < ui4_mnt_count ; ui1_i++)
    {
        if (RMVR_OK != a_rmv_dev_get_mnt_point(ui1_i, &z_mnt_point_size, s_mnt_point))
        {
            continue;
        }
        c_snprintf(s_file_name, 512, "%s/%s", s_mnt_point, NAV_UPDATER_ULI_REDIRECT_FILE_NAME);

        if (FMR_OK == c_fm_get_info_by_name(FM_ROOT_HANDLE, s_file_name, &t_file_info))
        {
            CHAR    cmd_string[128] = "N/A";
            FILE * pFile = NULL;
            pFile = fopen (s_file_name,"r");
            if (pFile != NULL)
            {
                c_memset(cmd_string, 0, sizeof(cmd_string));
                fgets(cmd_string, sizeof(cmd_string)-1, pFile);
                fclose(pFile);
                NAV_UPGRADE_LOG_PRINT(("%s_%d cmd_string:%s \n",__FUNCTION__,__LINE__,cmd_string));
                if(c_strstr(cmd_string,UTV_FILE_SUFFIX_NAME) != NULL)
                {
                    e_usb_update_type = UPDATER_USB_TYPE_UTV;
                    NAV_UPGRADE_LOG_PRINT(("%s_%d cmd_string:%s \n",__FUNCTION__,__LINE__,cmd_string));
                }
                else if(c_strstr(cmd_string,CMD_FILE_SUFFIX_NAME) != NULL)
                {
                    e_usb_update_type = UPDATER_USB_TYPE_CMD;
                    NAV_UPGRADE_LOG_PRINT(("%s_%d cmd_string:%s \n",__FUNCTION__,__LINE__,cmd_string));
                }
                else
                {
                    e_usb_update_type = UPDATER_USB_TYPE_UNKNOW;
                }
            }
            return TRUE;
        }
    }
    e_usb_update_type = UPDATER_USB_TYPE_UNKNOW;
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_is_fw_ready
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_uli_is_fw_ready(
    VOID
)
{
    FM_FILE_INFO_T    t_info;
    CHAR              s_path[128] = {0};
    UINT32            ui4_size = 128;

    if (NAVR_OK == _nav_updater_uli_get_path(s_path, ui4_size))
    {
        if (FMR_OK == c_fm_get_info_by_name(FM_ROOT_HANDLE, s_path, &t_info))
        {
                return TRUE;
            }
    }

    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_rmv_dev_nfy_handler
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static VOID _nav_updater_uli_rmv_dev_nfy_handler(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    INT32                   i4_ret;
    UPDATER_ULI_CTRL_T*     pt_this  = &t_g_uli_ctrl;
    RMV_DEV_NFY_ID_T        e_nfy_id = (RMV_DEV_NFY_ID_T)((UINT32)pv_tag1);
#ifdef APP_RETAIL_MODE_SUPPORT
    ACFG_RETAIL_MODE_T      t_retail_mode = ACFG_RETAIL_MODE_LAST_ENTRY;
#endif

    if (RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
    {
#ifdef APP_RETAIL_MODE_SUPPORT//will go down here
        a_cfg_custom_get_retail_mode_setting(&t_retail_mode);
        if (ACFG_RETAIL_MODE_NORMAL == t_retail_mode)
        {
            return;
        }
#endif

#ifdef APP_WR_UPDATER_UI_SUPPORT//will not go down here

        /* for start setup is active should not do the nav updater*/
        if (NAV_COMP_ID_WR_UPDATER == nav_get_active_component())
        {
            return;
        }
#endif

        pt_this->b_uli_evt_end = FALSE;
        pt_this->b_uli_evt_update = FALSE;

        if (nav_updater_pkgfile_existed_in_tv())
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"<_nav_updater_uli> RMV_DEV_NFY_ID_DEVICE_INSERTED - Skip \n"));
            return;
        }

#ifdef APP_MULTISKU_USB_SUPPORT//will go down here
        NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_uli_rmv_dev_nfy_handler _nav_updater_check_usb_multisku\n"));

        /*here should check the multisku usb feature first*/
        _nav_updater_uli_do_multisku();
        _nav_updater_check_usb_multisku(MULTISKU_TXT_CFG_FILE_NAME);
#endif

        /* check if the secure ULI FW is ready, if not ready => do nothing */
        if (TRUE == _nav_updater_uli_is_secure_fw_ready())
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_is_secure_fw_ready \n"));

            i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

            if (NAVR_OK == i4_ret)
            {
                nav_updater_uli_set_user_mode(USER_MODE_NORMAL);
                a_uli_agent_init();
                nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM);

                pt_this->e_method = UPDATER_ULI_METHOD_USB;
                nav_updater_trigger_update(pt_this->e_type);
            }
        }
        /* tell ULI to enter factory test mode */
        else if (TRUE == _nav_updater_uli_is_oob_test_start_file())
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_is_oob_test_start_file \n"));

            if (FALSE == _nav_updater_uli_is_oob_mode())
            {
                _nav_updater_uli_enter_oob_mode(TRUE);
            }
        }
        /* tell ULI to exit factory test mode */
        else if (TRUE == _nav_updater_uli_is_oob_test_end_file())
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_is_oob_test_end_file \n"));

            /* should doubly check if current mode is OOB mode */
            if (TRUE == _nav_updater_uli_is_oob_mode())
            {
                _nav_updater_uli_enter_oob_mode(FALSE);
            }
        }
    }
    else if (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"USB device is removed!, ULI agent is in progess? (%d)\n",
                   pt_this->b_uli_agent_in_progess));

        if ((TRUE == pt_this->b_uli_agent_in_progess)
            && (FALSE == _nav_updater_uli_is_fw_ready())
            && (pt_this->e_method == UPDATER_ULI_METHOD_USB))
        {
            _nav_updater_uli_abort_updates();

            /* call back the core updater */
            pt_this->e_fail_reason = ULI_EVENT_DOWNLOAD_INSTALL_FAILURE;

            nav_request_context_switch(
                            _nav_updater_uli_preprocess_cb,
                            (VOID*)(FALSE),
                            NULL,
                            NULL);
        }
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_rmv_dev_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_rmv_dev_agent_nfy(
    VOID*     pv_data,
    SIZE_T    z_data_len
)
{
    /* delay 3000 ms */
    c_thread_delay(3000);

    nav_request_context_switch(_nav_updater_uli_rmv_dev_nfy_handler,
                               (VOID*)(*((RMV_DEV_NFY_ID_T*)(pv_data))),
                               NULL,
                               NULL);
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_rmv_dev_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_rmv_dev_nfy(
    VOID*                  pv_tag,
    RMV_DEV_NFY_ID_T       e_nfy_id,
    VOID*                  pv_nfy_param
)
{
    if((RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
        || (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id))
    {

            e_s_nfy_id = e_nfy_id;

            if (RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
            {
                b_s_is_usb_insert = TRUE;
            }
            else
            {
                b_s_is_usb_insert = FALSE;
            }
			DBG_LOG_PRINT(("%s_%d  \n",__FUNCTION__,__LINE__));

            //if (nav_updater_is_all_partition_ready())
            {
                nav_updater_uli_trigger_sub_updater();
            }

	DBG_LOG_PRINT(("%s_%d  \n",__FUNCTION__,__LINE__));

    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: nav_updater_uli_trigger_sub_updater
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
VOID nav_updater_uli_trigger_sub_updater( VOID )
{
    UPDATER_ULI_CTRL_T*    pt_this  = &t_g_uli_ctrl;

    if(b_s_is_usb_insert == TRUE)
    {
        /*
           if it is the first time to get rmv notification,
           switch to the thread of agent and do some delay
        */
        if (TRUE == pt_this->b_first_time_rmv_nfy)
        {
             a_agent_async_invoke(_nav_updater_uli_rmv_dev_agent_nfy,
                                  (VOID*)(&e_s_nfy_id),
                                  sizeof(RMV_DEV_NFY_ID_T));

            pt_this->b_first_time_rmv_nfy = FALSE;
        }
        else
        {
            nav_request_context_switch(_nav_updater_uli_rmv_dev_nfy_handler,
                                       (VOID*)e_s_nfy_id,
                                       NULL,
                                       NULL);
        }

        b_s_is_usb_insert = FALSE;
    }

    return;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_download_start
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_download_start(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    INT32                   i4_ret;
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
	BOOL   b_is_fw_download_ready = FALSE;
    CHAR                   s_path[128] = {0};
    UINT32                 ui4_size    = 128;
    NAV_UPDATER_FW_STATE_T  e_fw_state = CHECK_STATE_NONE;

    /* set to updater core */
    nav_updater_enter_bgm(TRUE);

    nav_updater_uli_get_fw_status(&e_fw_state);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_download_start [bgm&full_update] e_fw_state:%d \n",e_fw_state));
    b_is_fw_download_ready = _nav_updater_uli_is_fw_ready();
	NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"b_is_fw_download_ready [%d]\n",b_is_fw_download_ready));
	if (b_is_fw_download_ready && (NAVR_OK == _nav_updater_uli_get_path(s_path, ui4_size))&&(e_fw_state != CHECK_STATE_DOWNLOADING))
	{
		NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"need delete the pre file to trigger again \n"));
		c_fm_delete_file(FM_ROOT_HANDLE, s_path);
	}

    i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

    if (NAVR_OK == i4_ret)
    {
        /* if network connection is ready, try internet update, otherwise, try broadcast update */
        do
        {
            i4_ret = a_nw_connection_test_upg((CHAR*)"www.mediatek.com");
            c_thread_delay(1000);
        }
        while(0);

        /* should reset the flag */
        if (TRUE == pt_this->b_exit_checking_network)
        {
            pt_this->b_exit_checking_network = FALSE;

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Exit current checking network process!!!\n"));
        }
    }
    else
    {
        _nav_updater_cb_bgm(NAV_UPDATER_ULI_FAIL);
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_download_stop
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_download_stop(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    /* should stop the dl timer*/
    _nav_updater_uli_stop_dl_timer();
    /* do abort */
    nav_updater_do_abort();

    /* set to updater core */
    nav_updater_enter_bgm(FALSE);

    return;
}
/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_nw_notify_handler
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_nw_notify_handler(
    VOID*          pv_tag1,
    VOID*          pv_tag2,
    VOID*          pv_tag3
)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    NW_NFY_ID_T    e_nfy_id = (NW_NFY_ID_T)((UINT32)pv_tag2);
    BOOL           b_test_result = FALSE;
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_nw_notify_handler e_nfy_id %u!\n",e_nfy_id));
    UINT8 ui1_value = ACFG_VLOG_OFF;


    switch(e_nfy_id)
    {
        case NW_NFY_ID_DHCP_SUCCESS_DHCPv4:
            {
                    nav_updater_set_check_dev_db_flag(TRUE);
                    g_b_uli_provisioning_checked = FALSE;

                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_nw_notify_handler Reset[g_b_uli_provisioning_checked]\n"));
                a_cfg_cust_get_ota_loop_test(&ui1_value);
				if(ui1_value == ACFG_VLOG_ON)
				{
					a_cfg_custom_set_oobe_mode(TRUE);
                	nav_updater_loop_test_timer_start();
				}

            }
            break;
#ifdef APP_UPG_SUPPORT
        case NW_NFY_ID_INTERN_CT_UPG_RESULT:
        {
            if (FALSE == nav_updater_is_bgm_ex())
            {
                /* if this is not bgm should just skip the network testing*/
                return;
            }

            b_test_result = (UINT32)pv_tag3;
            /* Internet connection test result, pv_nfy_param: 0=>Fail; 1=>Success */
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[bgm_condition]Internet connection [test result %u  retry times %u]!\n",b_test_result,g_ui1_retry));

            if (!b_test_result)
            {
                if (g_ui1_retry >= NAV_UPDATER_ULI_MAX_CHK_3RD_RETRY_NUM)
                {
                /* if this the last time about the network connection check will try to do the download
                               and assume that the network connection is ok*/
                    nav_updater_uli_set_user_mode(USER_MODE_SILENTLY);
                    nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE);

                    pt_this->e_method = UPDATER_ULI_METHOD_INTNT;

                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" nav_updater_trigger_update() e_type %u e_method %u in _nav_updater_uli_nw_notify_handler!\n",
                        (UINT16)pt_this->e_type,(UPDATER_ULI_METHOD_T)pt_this->e_method));
                    nav_updater_trigger_update(pt_this->e_type);
                }
                else
                {
                     if (g_b_poweron)
                     {
                       g_b_poweron = FALSE;

                       nav_updater_uli_set_user_mode(USER_MODE_SILENTLY);
                       nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE);

                       pt_this->e_method = UPDATER_ULI_METHOD_INTNT;
                       NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" nav_updater_trigger_update() e_type %u e_method %u g_b_poweron %u in _nav_updater_uli_nw_notify_handler!\n",
                           (UINT16)pt_this->e_type,(UPDATER_ULI_METHOD_T)pt_this->e_method,g_b_poweron));
                        nav_updater_trigger_update(pt_this->e_type);
                     }
                     else
                     {
                       a_nw_connection_test_upg((CHAR*)"www.mediatek.com");
                       c_thread_delay(1000);
                       g_ui1_retry++;
                     }

                }
            }
            else
            {

                nav_updater_uli_set_user_mode(USER_MODE_SILENTLY);
                nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE);

                pt_this->e_method = UPDATER_ULI_METHOD_INTNT;

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" nav_updater_trigger_update() e_type %u e_method %u in _nav_updater_uli_nw_notify_handler!\n",
                    (UINT16)pt_this->e_type,(UPDATER_ULI_METHOD_T)pt_this->e_method));
                nav_updater_trigger_update(pt_this->e_type);
            }
            break;
        }
#endif
        default:
            break;
    }
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_uli_nw_notify_callback
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

static VOID _nav_updater_uli_nw_notify_callback(
    VOID*          pv_tag,
    NW_NFY_ID_T    e_nfy_id,
    VOID*          pv_nfy_param
)
{
    nav_request_context_switch(_nav_updater_uli_nw_notify_handler,
                              (VOID*)pv_tag,
                              (VOID*)e_nfy_id,
                              (VOID*)pv_nfy_param);
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_preprocess
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_uli_preprocess(
    updater_preprocess_cb_fn    pf_preprocess_cb
)
{
    UPDATER_ULI_CTRL_T*         pt_this = &t_g_uli_ctrl;
    INT32                       i4_ret;

    if (NULL == pf_preprocess_cb)
    {
        return NAVR_FAIL;
    }

    /* assign the callback function */
    pt_this->pf_preprocess_cb = pf_preprocess_cb;

    if (TRUE == _nav_updater_uli_is_fw_ready())
    {
        /* callback successful directly */
        nav_request_context_switch(
                        _nav_updater_uli_preprocess_cb,
                        (VOID*)TRUE,
                        NULL,
                        NULL);
    }
    else
    {
        pt_this->b_uli_agent_in_progess = TRUE;

        i4_ret = _nav_updater_uli_get_updates(pt_this->e_method);

        if (NAVR_OK != i4_ret)
        {
            pt_this->b_uli_agent_in_progess = FALSE;
            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_usb_handle_msg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static VOID _nav_updater_uli_handle_msg(
    NAV_UI_MSG_T*           pt_ui_msg,
    VOID*                   pv_arg
)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_APP_RESUMED:
            if (TRUE == pt_this->b_delay_start)
            {
                pt_this->b_delay_start = FALSE;
                if (UPDATER_ULI_METHOD_USB == pt_this->e_method)
                {
                    _nav_updater_uli_rmv_dev_nfy_handler(((VOID*)RMV_DEV_NFY_ID_DEVICE_INSERTED),
                                                          NULL,
                                                          NULL);
                }
            }
            break;

        case NAV_UI_MSG_POWER_ON:
        {
            /* if g_b_poweron is true ,then not need monitor network */
            g_b_poweron = TRUE;

            NAV_UPGRADE_LOG_PRINT(("\n[UPTT]POWER_ON Trigger\n"));

            a_uli_agent_init_wait_NTP();
            nav_updater_uli_send_started_msg_to_am();

            /* if system is in OOB mode currently => always show the "OOB in progess" OSD */
            if (TRUE == _nav_updater_uli_is_oob_mode())
            {
                _nav_updater_uli_show_oob_mode_osd();
            }
        }
            break;

        case NAV_UI_MSG_APP_INITED:
        {
            if(TRUE == a_am_is_power_on())
            {
                NAV_UPGRADE_LOG_PRINT(("\n[UPTT]APP_INITED Trigger\n"));
                nav_updater_uli_send_started_msg_to_am();
            }
            break;
        }

        case NAV_UI_MSG_POWER_OFF:
            {
                INT32 i4_ret;
                NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATE]NAV_UI_MSG_POWER_OFF call qda_term()\n"));
                i4_ret = a_uli_qda_term();
                if(!i4_ret){
                    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATE] a_uli_qda_term success!\n"));
                }
            }
            break;
        case NAV_UI_MSG_PRE_POWER_OFF:
            {
                NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATE]NAV_UI_MSG_PRE_POWER_OFF g_b_uli_network_up[Reset]\n"));
                g_b_uli_network_up = FALSE;
            }
            break;

        default:
            break;
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_usb_get_path
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_uli_get_path(
    CHAR*                  ps_buff,
    SIZE_T                 z_buff_len
)
{
    UPDATER_ULI_CTRL_T*    pt_this = &t_g_uli_ctrl;

    if (ps_buff == NULL)
    {
        return NAVR_FAIL;
    }

    c_snprintf(ps_buff, z_buff_len, "%s/%s", UPDATER_FILE_BASED_UPG_PATH, pt_this->s_src_file);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_usb_exit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_uli_get_fw(
    UPDATER_ITEM_T*               pt_item,
    updater_progress_notify_fn    pf_progress_cb
)
{
    /* do something */

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_usb_exit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_uli_exit(
    BOOL                   b_success
)
{
    CHAR                   s_path[128] = {0};
    UINT32                 ui4_size    = 128;
    UPDATER_ULI_CTRL_T*    pt_this     = &t_g_uli_ctrl;
    NAV_UPDATER_TRIGGER_TYPE_T  e_trigger_type = TRIGGER_TYPE_NONE;

    /*if this just for download,
    here should just shutdown the uli*/
    nav_updater_uli_get_trigger_type(&e_trigger_type);

    if ((TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD == e_trigger_type)
        || (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK == e_trigger_type)
        || (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE == e_trigger_type))
    {

        _nav_updater_cb_bgm(NAV_UPDATER_ULI_ABORT);
        #ifdef ULI_USE_ODL_LIB
        a_uli_shutdown();
        #endif
        pt_this->b_uli_agent_in_progess = FALSE;

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_exit Download_ok[break]\n"));

        return NAVR_OK;
    }

    if (TRUE == b_success)
    {
        /* if successful => remove the file */
        if (NAVR_OK == _nav_updater_uli_get_path(s_path, ui4_size))
        {
            c_fm_delete_file(FM_ROOT_HANDLE, s_path);
        }

        _nav_updater_cb_bgm(NAV_UPDATER_ULI_COMPLETE);
    }
    else
    {
        if (TRUE == pt_this->b_uli_agent_in_progess)
        {
            _nav_updater_uli_abort_updates();
        }

        _nav_updater_cb_bgm(NAV_UPDATER_ULI_ABORT);
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_exit a_uli_shutdown[10s]\n"));

    //c_thread_delay(10000);

    /* always call this API to shutdown and clean up the update process */
    #ifdef ULI_USE_ODL_LIB
    a_uli_shutdown();
    #endif
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_download_start_timer_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_download_start_timer_fct(
    HANDLE_T    h_timer,
    VOID*       pv_tag
)
{
    nav_request_context_switch(_nav_updater_uli_download_start,
                               NULL,
                               NULL,
                               NULL);
    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_do_delay_download
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_uli_do_delay_download(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    UPDATER_ULI_CTRL_T*    pt_this = &t_g_uli_ctrl;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Download start, trigger a timer to wait for %d seconds!\n", (NAV_UPDATER_ULI_DL_DELAY_TIME / 1000)));

    /* enable the timer */
    c_timer_start(pt_this->h_dl_timer,
                  NAV_UPDATER_ULI_DL_DELAY_TIME,
                  X_TIMER_FLAG_ONCE,
                  _nav_updater_uli_download_start_timer_fct,
                  NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_updater_uli_stop_dl_timer
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_updater_uli_stop_dl_timer(VOID)
{
    INT32 i4_ret;

    UPDATER_ULI_CTRL_T*    pt_this = &t_g_uli_ctrl;

    if (c_handle_valid(pt_this->h_dl_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_dl_timer);
    if (i4_ret != OSR_OK) {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_stop_dl_timer() called \n"));
    }
}


#ifdef CLI_SUPPORT
/*rest api test*/
static INT32 _nav_updater_uli_cli_rest_register_user_info
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_register_user_info[BEG]\n"));

#if 0
    CHAR *s_user_info[NAV_UPDATE_ULI_REG_INFO_LAST_ENTRY];
    s_user_info[NAV_UPDATE_ULI_REG_INFO_PHONE_NUM] = "test_123456";
    s_user_info[NAV_UPDATE_ULI_REG_INFO_FIRST_NAME] = "test_f_name";
    s_user_info[NAV_UPDATE_ULI_REG_INFO_LAST_NAME] = "test_l_name";
    s_user_info[NAV_UPDATE_ULI_REG_INFO_ZIP_CODE] = "test_zip_code";
    s_user_info[NAV_UPDATE_ULI_REG_INFO_MAIL] = "test_mail";
    s_user_info[NAV_UPDATE_ULI_REG_INFO_COMMIT] = "test_commit";

    a_nav_updater_uli_register_user_info(s_user_info,NAV_UPDATE_ULI_REG_INFO_LAST_ENTRY);
#endif

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_register_user_info[END]\n"));

    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_get_dev_register_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT8 ui1_device_register_status = 0;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_get_dev_register_status[BEG]\n"));
    a_nav_updater_uli_get_device_register_status(&ui1_device_register_status);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"ui1_device_register_status[%d]\n",ui1_device_register_status));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_get_dev_register_status[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_get_user_register_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT8 ui1_user_register_status = 0;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_get_user_register_status[BEG]\n"));
    a_nav_updater_uli_get_user_register_status(&ui1_user_register_status);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"ui1_user_register_status[%d]\n",ui1_user_register_status));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_get_user_register_status[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_get_updating_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT8 ui1_updating_status = 0;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_get_updating_status[BEG]\n"));
    a_nav_updater_uli_get_updating_status(&ui1_updating_status);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"ui1_updating_status[%d]\n",ui1_updating_status));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_get_updating_status[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_check_fw_avaliable
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT8 ui1_fw_status = 0;
    UINT8 ui_fw_policy = 0;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_check_fw_avaliable[BEG]\n"));
    a_nav_updater_check_fw_avaliable(&ui1_fw_status,&ui_fw_policy);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"check_fw_avaliable ui1_fw_status[%d],ui_fw_policy[%d]\n",ui1_fw_status,ui_fw_policy));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_check_fw_avaliable[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_start_update
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT8 ui1_fw_status = 0;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_start_update[BEG]\n"));
    a_nav_updater_download_firmware_and_trigger_update(&ui1_fw_status);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"start_update ui1_fw_status[%d]\n",ui1_fw_status));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_start_update[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_get_update_status
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    UINT8 ui1_update_status = 0;
    UINT8 ui1_progress = 0;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_get_update_status[BEG]\n"));
    a_nav_updater_get_update_status(&ui1_update_status,&ui1_progress);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"start_update ui1_update_status[%d],ui1_progress[%d]\n",ui1_update_status,ui1_progress));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_get_update_status[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_just_download
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    NAV_UPDATER_USER_MODE_T e_user_mode = USER_MODE_NORMAL;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_just_download[BEG]\n"));
    nav_updater_uli_start_fw_download(e_user_mode);
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_just_download[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_reboot_install
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_reboot_install[BEG]\n"));
    nav_updater_sys_install_fw(USER_MODE_NORMAL,TRUE);
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_reboot_install[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_install
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_install[BEG]\n"));
    nav_updater_sys_install_fw(USER_MODE_NORMAL,FALSE);
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_install[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_service_check
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32 i4_ret = 0;
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_service_check[BEG]\n"));
    #ifdef ULI_USE_ODL_LIB
    i4_ret = a_uli_project_on_force_noc_contact();
    #endif
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_on_force_noc_contact i4_ret[%d]\n",i4_ret));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_service_check[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_rest_bgm_reboot
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    INT32 i4_ret = 0;
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_bgm_reboot[BEG]\n"));
    //i4_ret = c_pcl_set_bgm_reboot();
	nav_updater_reboot_system_ex();

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_pcl_set_bgm_reboot i4_ret[%d]\n",i4_ret));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_cli_rest_bgm_reboot[END]\n"));
    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_test_toast_process_bar
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    UINT8 ui1_value = 0;

    if (i4_argc == 1) {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"This cmd need to input type\n"));
        return CLIR_OK;
    }

    ui1_value = (UINT8)nav_atoi(pps_argv[1]);

    nav_updater_show_toast_progress_test(ui1_value);

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_cli_start_dl
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_cli_start_dl
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Start to test the Internet!\n"));

    nav_request_context_switch(_nav_updater_uli_download_start,
                               NULL,
                               NULL,
                               NULL);
    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_cli_object_request
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_cli_object_request
(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    #define OBJ_ID_BUFF_SZ         (256)         /* 256 bytes */
    #define OBJ_CONTENT_BUFF_SZ    (1024 * 5)    /* 5K bytes */
	#ifdef ULI_USE_ODL_LIB
    INT32           i4_ret;
	#endif
    CHAR            s_obj_id[OBJ_ID_BUFF_SZ] = {0};
    CHAR            s_obj_content[OBJ_CONTENT_BUFF_SZ] = {0};
    UINT32          ui4_obj_sz = 0;
    UINT32          ui4_encrypt_type = 0;

    if (3 == i4_argc)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Requesting provisioning objects for owner name: %s, object name: %s!\n",
                   pps_argv[1],
                   pps_argv[2]));
#ifdef ULI_USE_ODL_LIB

        i4_ret = a_uli_on_object_request((INT8*)pps_argv[1], (INT8*)pps_argv[2],
                                         (INT8*)&(s_obj_id[0]), OBJ_ID_BUFF_SZ,
                                         (UINT8*)&(s_obj_content[0]), OBJ_CONTENT_BUFF_SZ, &ui4_obj_sz,
                                         &ui4_encrypt_type);

        if (ULIR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_on_object_request() failed, %d\n", i4_ret));

            return CLIR_CMD_EXEC_ERROR;
        }
#endif

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Object id: %s, size: %d, content: %s\n",
                                      s_obj_id,
                                      ui4_obj_sz,
                                      s_obj_content));
        return CLIR_OK;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Usage: obj_request <owner name> <object name>\n"));

        return CLIR_INV_CMD_USAGE;
    }
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_cli_status_request
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_cli_status_request
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    ULI_PROJECT_STATUS_STRUCT    t_status;
    CHAR                         s_esn[48];
    CHAR                         s_qh[32];
    CHAR                         s_version[32];
    CHAR                         s_info[128];
    CHAR                         s_error[128];

    c_memset((VOID*)&t_status, 0, sizeof(ULI_PROJECT_STATUS_STRUCT));

    /* setup return strings */
    t_status.pszESN               = (INT8 *)s_esn;
    t_status.uiESNBufferLen       = sizeof(s_esn);
    t_status.pszQueryHost         = (INT8 *)s_qh;
    t_status.uiQueryHostBufferLen = sizeof(s_qh);
    t_status.pszVersion           = (INT8 *)s_version;
    t_status.uiVersionBufferLen   = sizeof(s_version);
    t_status.pszInfo              = (INT8 *)s_info;
    t_status.uiInfoBufferLen      = sizeof(s_info);
    t_status.pszLastError         = (INT8 *)s_error;
    t_status.uiLastErrorBufferLen = sizeof(s_error);


    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"ESN: %s\n", t_status.pszESN ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"UID: %u\n", t_status.uiULPKIndex ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"QH:  %s\n", t_status.pszQueryHost ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"VER: %s\n", t_status.pszVersion ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"INF: %s\n", t_status.pszInfo ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"OUI: 0x%06X\n", t_status.uiOUI ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"MG:  0x%04X\n", t_status.usModelGroup ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"HM:  0x%04X\n", t_status.usHardwareModel ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"SV:  0x%04X\n", t_status.usSoftwareVersion ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"MV:  0x%04X\n", t_status.usModuleVersion ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"NP:  %u\n", t_status.usNumObjectsProvisioned ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"REG: %u\n", 0 != (t_status.usStatusMask & NAV_UPDATER_ULI_STATUS_MASK_REGISTERED) ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"FCT: %u\n", 0 != (t_status.usStatusMask & NAV_UPDATER_ULI_STATUS_MASK_FACTORY_TEST_MODE) ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"FET: %u\n", 0 != (t_status.usStatusMask & NAV_UPDATER_ULI_STATUS_MASK_FIELD_TEST_MODE) ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LP:  %u\n", 0 != (t_status.usStatusMask & NAV_UPDATER_ULI_STATUS_MASK_LOOP_TEST_MODE) ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"EC:  %u\n", t_status.uiErrorCount ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LE:  %u\n", t_status.uiLastErrorCode ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LES: %s\n", t_status.pszLastError ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LET: %s\n", ctime(&(t_status.tLastErrorTime)) ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LPS: %u\n", t_status.usLastProvisioningStatus ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LDV: %u\n", t_status.usLastDownloadEndedMV ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LDM: %u\n", t_status.usLastDownloadEndedType ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LDS: %u\n", t_status.usLastDownloadEndedStatus ));
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"LDT: %s\n", ctime(&(t_status.tLastDownloadEndedEvent)) ));

    return CLIR_OK;
}

static INT32 _nav_updater_uli_cli_provisioning_status_request
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    ULI_PROJECT_PROVISION_STATUS  t_provisioning_status;
	#ifdef ULI_USE_ODL_LIB
    INT32                         i4_ret;
	#endif

    c_memset((VOID*)&t_provisioning_status, 0, sizeof(ULI_PROJECT_PROVISION_STATUS));
#ifdef ULI_USE_ODL_LIB

    i4_ret = a_uli_get_provisioning_status(&t_provisioning_status);

    if (ULIR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_get_provisioning_status() failed, %d\n", i4_ret));
        return CLIR_CMD_EXEC_ERROR;
    }
#endif

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Provisioning status[ui4_MaxAvailable[%d],ui4_CurrentlyAvailable[%d],ui4_DeliverySuccess[%d]]\n",
              t_provisioning_status.ui4_MaxAvailable,
              t_provisioning_status.ui4_CurrentlyAvailable,
              t_provisioning_status.ui4_DeliverySuccess));

    return CLIR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_reg_user_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_reg_user_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    CHAR *apszRegStoreValues[ 10 ];
	#ifdef ULI_USE_ODL_LIB
    INT32                   i4_ret;
	#endif

     /* mock up some CEM status values */
    apszRegStoreValues[ 0 ] = "1";
    apszRegStoreValues[ 1 ] = "random stuff";
    apszRegStoreValues[ 2 ] = "like error code 14 from Rhapsody";
    apszRegStoreValues[ 3 ] = "or libcurl error 58 from Amazon";
    apszRegStoreValues[ 4 ] = "or owner-name not found";
    apszRegStoreValues[ 5 ] = "how about network connection error";
    apszRegStoreValues[ 6 ] = "or even more and more things";
    apszRegStoreValues[ 7 ] = "like number 1 2 3 4 5 6 7 8 9";
    apszRegStoreValues[ 8 ] = "or more and more fields: this is the ninth field";
    apszRegStoreValues[ 9 ] = "this is the tenth";
    /*apszRegStoreValues[ 10 ] = "this is the eleventh"; Marked by Jia fix warning 20121108*/


    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_reg_store_user_info() called , numstring:=10\n"));
#ifdef ULI_USE_ODL_LIB

    i4_ret = a_uli_project_reg_store_user_info (
                             (UINT8**)apszRegStoreValues,
                             10 );


    if (ULIR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_reg_store_user_info() failed, return_value=%d\n", i4_ret));

        return CLIR_CMD_EXEC_ERROR;
    }



    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_reg_store_user_info() success ,  return_value=%d\n", i4_ret));
#endif

    return CLIR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_customization_aes_key
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_customization_aes_key(VOID)
{
    INT32                   i4_ret;
	FILE  *pf_aes = NULL;
	FILE  *pf_rsa = NULL;
	FILE  *fl_check = NULL ;
	CHAR  s_aes[AES_LENGTH] = {0};
	CHAR  s_rsa[RSA_LENGTH] = {0};
	DBG_LOG_PRINT(("%s_%d  \n",__FUNCTION__,__LINE__));

    pf_aes = fopen("/basic/AESupgrade.bin", "r");
    // no /basic/AESupgrade.bin
    if (NULL == pf_aes)
    {
    	DBG_LOG_PRINT(("%s_%d aes key error \n",__FUNCTION__,__LINE__));
        return NAVR_NOT_EXIST;
    }

    pf_rsa = fopen("/basic/RSAupgrade_pub.bin", "r");
    // no /basic/RSAupgrade_pub.bin
    if (NULL == pf_rsa)
    {
    	DBG_LOG_PRINT(("%s_%d rsa key error \n",__FUNCTION__,__LINE__));
        return NAVR_NOT_EXIST;
    }

	if(fread(&s_aes, sizeof(CHAR), AES_LENGTH, pf_aes) != 0)
	{
	    char *pos;
		if(s_aes[0] == 0)
		{
			return NAVR_OK;
		}
	    if ((pos = c_strchr(s_aes, '\n')) != NULL) {
	        *pos = '\0';
	    }
	}
	if(fread(&s_rsa, sizeof(CHAR), RSA_LENGTH, pf_rsa) != 0)
	{
	    char *pos;
		if(s_rsa[0] == 0)
		{
			return NAVR_OK;
		}
	    if ((pos = c_strchr(s_rsa, '\n')) != NULL) {
	        *pos = '\0';
	    }
	}
	fl_check = fopen ("/data/aes_key","w+");
	if(s_aes[0] != 0)
	{
		fprintf(fl_check, "%s\n", s_aes);
	}
	fclose (fl_check);


	fl_check = NULL;
	fl_check = fopen ("/data/rsa_key","w+");
	if(s_rsa[0] != 0)
	{
		fprintf(fl_check, "%s\n", s_rsa);
	}
	fclose (fl_check);


	i4_ret = c_dlm_set_customer_aes_key((unsigned char*)s_aes,AES_LENGTH,NULL,0);
	i4_ret = c_dlm_set_customer_key((unsigned char*)s_rsa);
	fclose (pf_rsa);
	fclose (pf_aes);
    return NAVR_OK;
}



/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_remove_user_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_remove_user_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
	#ifdef ULI_USE_ODL_LIB
    INT32                   i4_ret;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_remove_user_info() called \n"));


    i4_ret = a_uli_project_remove_user_info ();


    if (ULIR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_remove_user_info() failed, return_value=%d\n", i4_ret));

        return CLIR_CMD_EXEC_ERROR;
    }



    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_remove_user_info() success ,  return_value=%d\n", i4_ret));
	#endif

    return CLIR_OK;
}
static INT32 _nav_updater_uli_show_usb_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_show_usb_info()\n"));

    nav_updater_view_show_usb_info(TRUE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_hide_usb_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_hide_usb_info()\n"));
    nav_updater_view_show_usb_info(FALSE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_show_complete_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    nav_updater_view_show_complete_info(TRUE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_hide_complete_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_hide_complete_info()\n"));
    nav_updater_view_show_complete_info(FALSE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_show_firmware_not_avaliable_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_show_firmware_not_avaliable_info()\n"));
    nav_updater_view_show_firmware_check_not_avaliable_info(TRUE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_hide_firmware_not_avaliable_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_hide_firmware_not_avaliable_info()\n"));
    nav_updater_view_show_firmware_check_not_avaliable_info(FALSE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_check_network_updater
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    UINT8 ui1_fw_status = 0;
    UINT8 ui_fw_policy = 0;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_check_network_updater()\n"));
    a_nav_updater_check_network_update(&ui1_fw_status,&ui_fw_policy);


    return CLIR_OK;
}



static INT32 _nav_updater_uli_show_updating_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_show_updating_info()\n"));
    nav_updater_show_updating_page_ex(TRUE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_hide_updating_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_hide_complete_info()\n"));
    nav_updater_show_updating_page_ex(FALSE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_show_progress_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_show_updating_info()\n"));
    nav_updater_show_preprocess_page_ex(TRUE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_hide_progress_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_hide_complete_info()\n"));
    nav_updater_show_preprocess_page_ex(FALSE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_show_cmd_stick_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_show_updating_info()\n"));
    nav_updater_view_show_command_stick_info(TRUE);

    return CLIR_OK;
}

static INT32 _nav_updater_uli_hide_cmd_stick_info
(
    INT32                        i4_argc,
    const CHAR**                 pps_argv
)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_hide_complete_info()\n"));
    nav_updater_view_show_command_stick_info(FALSE);

    return CLIR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_updater_uli_cli_object_request
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_uli_is_ulpk_valid_in_given_path(
    INT32           i4_argc,
    const CHAR**    pps_argv
)
{
    if (2 == i4_argc)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Check ULPK is valid or NOT, path: %s!\n", pps_argv[1]));

        if (FALSE == a_uli_is_ulpk_valid_in_given_path((char *)pps_argv[1]))
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"ULPK: %s is invalid!\n", pps_argv[1]));

            return CLIR_CMD_EXEC_ERROR;
        }

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"ULPK: %s is valid!\n", pps_argv[1]));
        return CLIR_OK;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Usage: Check ULPK <path of ULPK>\n"));

        return CLIR_INV_CMD_USAGE;
    }
}


#endif


/*-----------------------------------------------------------------------------
                     public methods implementations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: nav_updater_uli_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 nav_updater_uli_init(
    VOID
)
{
    UPDATER_DLIVRY_HDLR_REG_T    t_reg;
    INT32                        i4_ret;
    UPDATER_ULI_CTRL_T*          pt_this = &t_g_uli_ctrl;

    /* fill data for t_g_uli_ctrl */
    c_memset(pt_this, 0, sizeof(UPDATER_ULI_CTRL_T));

    pt_this->e_type = UPDATER_DLIVRY_TYPE_ULI;
    c_strcpy(pt_this->s_src_file, UPDATER_FW_INTEGRITY_OK_NAME);

    /* fill data for t_reg */
    c_memset(&t_reg, 0, sizeof(UPDATER_DLIVRY_HDLR_REG_T));

    t_reg.e_type = pt_this->e_type;

    t_reg.pf_preprocess = _nav_updater_uli_preprocess;
    t_reg.pf_handle_msg = _nav_updater_uli_handle_msg;
    t_reg.pf_get_path   = _nav_updater_uli_get_path;
    t_reg.pf_get_fw     = _nav_updater_uli_get_fw;
    t_reg.pf_exit       = _nav_updater_uli_exit;

    t_reg.pt_io         = NULL;

    t_reg.b_division    = FALSE;

    i4_ret = nav_updater_reg_dlivry_hdlr(&t_reg);

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    /*will not enable the first time check the device mount notify*/
    pt_this->b_first_time_rmv_nfy = FALSE;

    /* register to removable deivice utility */
    i4_ret = a_rmv_dev_reg_monitor(
                _nav_updater_uli_rmv_dev_nfy,
                NULL,
                &(pt_this->ui4_rmv_dev_nfy));

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);


#ifdef CLI_SUPPORT
    nav_register_comp_cli_entry (&t_g_uli_cli_cmd_entry);
#endif

    /* register to network utility */
    i4_ret = a_nw_register(_nav_updater_uli_nw_notify_callback, NULL, &(pt_this->ui4_nw_nfy_id));

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    /* create the download delay timer */
    pt_this->h_dl_timer = NULL_HANDLE;
    i4_ret = c_timer_create(&(pt_this->h_dl_timer));
    _UPDATER_CHK_FAIL(i4_ret, i4_ret);
	_nav_updater_uli_customization_aes_key();



    return NAVR_OK;
}

INT32 nav_updater_uli_unreg_dev_monitor(VOID)
{
    UPDATER_ULI_CTRL_T*          pt_this = &t_g_uli_ctrl;

    a_rmv_dev_unreg_monitor(pt_this->ui4_rmv_dev_nfy);

    return NAVR_OK;
}

BOOL  nav_updater_uli_is_usb_method(VOID)
{
    UPDATER_ULI_CTRL_T*          pt_this = &t_g_uli_ctrl;

    if (pt_this->e_method == UPDATER_ULI_METHOD_USB)
    {
        return TRUE;
    }

    return FALSE;
}
BOOL  nav_updater_uli_is_intnt_method(VOID)
{
    UPDATER_ULI_CTRL_T*          pt_this = &t_g_uli_ctrl;

    if (pt_this->e_method == UPDATER_ULI_METHOD_INTNT)
    {
        return TRUE;
    }

    return FALSE;
}


BOOL  nav_updater_uli_need_reboot(VOID)
{
    UPDATER_ULI_CTRL_T*          pt_this = &t_g_uli_ctrl;

    if (pt_this->e_method == UPDATER_ULI_METHOD_USB)
    {
        if (pt_this->b_uli_evt_end && pt_this->b_uli_evt_update)
        {
            return TRUE;
        }
    }

    return FALSE;
}

INT32 nav_updater_uli_progress_show(VOID)
{
    UPDATER_ULI_CTRL_T*          pt_this = &t_g_uli_ctrl;

    if (pt_this->e_method == UPDATER_ULI_METHOD_USB)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_progress_show \n"));
        /* Show message box */
        nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_ULI_USB, NULL);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
                    exported methods implementations
 -----------------------------------------------------------------------------*/

 INT32 a_nav_updater_network_upg_manual_start(VOID)
 {
    return NAVR_OK;
 }

/*----------------------------------------------------------------------------
 * Name: a_nav_updater_network_upg_manual_start
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_nav_updater_uli_download_start(
    updater_uli_bgm_nfy_fct    pf_nfy_fct
)
{
    INT32                      i4_ret;
    UPDATER_ULI_CTRL_T*        pt_this = &t_g_uli_ctrl;

    pt_this->pf_nfy = pf_nfy_fct;
    i4_ret = nav_request_context_switch(_nav_updater_uli_do_delay_download,
                NULL,
                NULL,
                NULL);

    if (NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: a_nav_updater_uli_download_stop
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_nav_updater_uli_download_stop(
    VOID
)
{
    INT32                  i4_ret;
    UPDATER_ULI_CTRL_T*    pt_this = &t_g_uli_ctrl;

    /* turn on flag to exit network checking */
    pt_this->b_exit_checking_network = TRUE;

    if (TRUE == pt_this->b_uli_agent_in_progess)
    {
        _nav_updater_uli_abort_updates();
    }

    i4_ret = nav_request_context_switch(
                   _nav_updater_uli_download_stop,
                    NULL,
                    NULL,
                    NULL);

    if (NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: a_nav_updater_uli_get_available_time
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_nav_updater_uli_get_avail_delay(
    UINT32*                pui4_avail_delay
)
{
    UPDATER_ULI_CTRL_T*    pt_this = &t_g_uli_ctrl;

    if (NULL == pui4_avail_delay)
    {
        return NAVR_INV_ARG;
    }

    *pui4_avail_delay = (0 != pt_this->ui4_avail_delay)
                        ? pt_this->ui4_avail_delay : 86400;

    /* if in the loop test mode, always set the wakeup time to 1 minite */
    #ifdef ULI_USE_ODL_LIB
    if (TRUE == a_uli_is_loop_test_mode())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"IN LOOP TEST MODE ==> Set next wake up time to 1 minite.\n"));

        *pui4_avail_delay = 60;
    }
    #endif
    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_nav_updater_uli_partition_all_query_network_up
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_nav_updater_uli_partition_all_query_network_up( VOID )
{
    PCL_WAKE_UP_REASON_T    e_wake_up_reason               = PCL_WAKE_UP_REASON_UNKNOWN;
    UINT32                  ui4_wake_up_sub_reason         = 0;
    BOOL                    b_is_will_to_bgm               = FALSE;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"%s, Line %d\n", __FUNCTION__, __LINE__));

    /* if the uli have already in up status do
     * not neet to check the netwok for uli
     */
    if (g_b_uli_network_up)
    {
        return NAVR_OK;
    }

    /* Get the wakeup reason/sub-reason */
    c_pcl_get_wakeup_reason (& e_wake_up_reason,
                             & ui4_wake_up_sub_reason);

    if (( e_wake_up_reason == PCL_WAKE_UP_REASON_RTC)
        && (ui4_wake_up_sub_reason & PCL_WAKE_UP_SUB_REASON_QUIET_BOOT))
    {
        b_is_will_to_bgm = TRUE;
    }

    if (((TRUE == a_am_is_power_on())
         || (FALSE == a_bgm_is_running()
             && FALSE == b_is_will_to_bgm))
        && (nav_updater_is_all_partition_ready()))
    {
        if (FALSE == g_b_uli_network_up)
        {
            if (FALSE == a_wzd_is_oobe_mode())
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"IP is obtained, call a_uli_on_network_up()!\n"));
                // In OOBE, do not dwonload provisions since will conflict the checking updates flow
                #ifdef ULI_USE_ODL_LIB
                a_uli_on_network_up();
                #endif
            }
            else
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"In OOBE status, do not call a_uli_on_network_up to download provision!\n"));
            }

            g_b_uli_network_up = TRUE;
        }

    }
    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_uli_send_started_msg_to_am
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 nav_updater_uli_send_started_msg_to_am( VOID )
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    BOOL                    b_is_updating_status = FALSE;
    INT32                   i4_ret;

    i4_ret = a_nav_updater_is_updating_status(
                                &b_is_updating_status
                                );

    if (((nav_updater_is_all_partition_ready() || (a_cfg_is_fs_partition_all())))
        && (a_nav_updater_is_power_on_from_bgm())
        && (!pt_this->b_uli_agent_download_ok)
        && ((NAVR_OK == i4_ret) && (FALSE == b_is_updating_status)))
    {
        /* reset the bgm power on flag*/
        a_nav_updater_set_power_on_from_bgm_flag(FALSE);

        /* start Y!W because we do not run it in BGM */
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Start Y!W because we do not run it in BGM\n"));
        NAV_UPGRADE_LOG_PRINT(("[UPTT][OK]\n"));
        a_tv_net_send_cmd(":dtv_app_mtk,am,:started=dtv_app_mtk\n");
        a_tv_net_send_cmd(":dtv_app_mtk,am,:enable_keyroute\n");
    }
    else
    {
          NAV_UPGRADE_LOG_PRINT(("[UPTT][FAIL] PTTN[%d],ACFG_PTTN[%d]FBGM[%d],ag_ok[%d],ret[%d],upst[%d]\n",
                        nav_updater_is_all_partition_ready(),
                        a_cfg_is_fs_partition_all(),
                        a_nav_updater_is_power_on_from_bgm(),
                        pt_this->b_uli_agent_download_ok,
                        i4_ret,
                        b_is_updating_status));
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_is_uli_agent_in_progress
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
BOOL nav_updater_is_uli_agent_in_progress( VOID )
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;

    if (pt_this->b_uli_agent_in_progess)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }

}

/*----------------------------------------------------------------------------
 * Name: a_nav_updater_is_uli_loop_test
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
BOOL a_nav_updater_is_uli_loop_test( VOID )
{
    #ifdef ULI_USE_ODL_LIB
    if (TRUE == a_uli_is_loop_test_mode())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"IN LOOP TEST MODE !!\n"));

        return TRUE;
    }
    else
    #endif
    {
        return FALSE;
    }

}

/* the following api will be implemented for rest uli api*/
static INT32 _nav_updater_uli_reg_info_json_merge(CHAR **pstr_in, CHAR **pstr_out)
{
    CHAR    s_sn[NAV_UPDATE_ULI_REG_INFO_SN_LEN+1] = {0};
    CHAR    s_sn_json[NAV_UPDATE_ULI_REG_INFO_SN_JSON_LEN+1] = {0};
    CHAR    s_mac[NAV_UPDATE_ULI_REG_INFO_MAC_LEN+1] = {0};
    CHAR    s_mac_json[NAV_UPDATE_ULI_REG_INFO_MAC_JSON_LEN+1] = {0};
    CHAR    s_vn_json[NAV_UPDATE_ULI_REG_INFO_VN_JSON_LEN+1] = {0};
    CHAR    s_dt[NAV_UPDATE_ULI_REG_INFO_DT_LEN+1] = {0};
    CHAR    s_dt_json[NAV_UPDATE_ULI_REG_INFO_DT_JSON_LEN+1] = {0};
    DTG_T   t_dtg = {0};
    UINT32  ui4_buff_len = sizeof(s_sn);
    INT32   i4_ret = NAVR_OK;
    BOOL    b_is_get_time = FALSE;

    if(NULL == pstr_in)
    {
        NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] _nav_updater_uli_reg_info_json_merge ARG invalid !!!\n"));
        return NAVR_INV_ARG;
    }

    /*get and convert serial num*/

    i4_ret = a_uli_get_serial_number((UINT8 *)s_sn, &ui4_buff_len);

    if(NAVR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] _nav_updater_uli_reg_info_json_merge a_uli_get_serial_number FAIL !!!\n"));
    }
    else
    {
        c_base64_encode(s_sn,c_strlen(s_sn),s_sn_json,NAV_UPDATE_ULI_REG_INFO_SN_JSON_LEN);
    }

    /*get and convert mac address*/
    a_nw_get_mac_addr_string(NI_ETHERNET_0,s_mac);
    c_base64_encode(s_mac,c_strlen(s_mac),s_mac_json,NAV_UPDATE_ULI_REG_INFO_MAC_JSON_LEN);

    /*get and convert firmware version*/
    c_base64_encode(sys_cust_get_usb_upg_version(),c_strlen(sys_cust_get_usb_upg_version()),s_vn_json,NAV_UPDATE_ULI_REG_INFO_VN_JSON_LEN);

    /*get and convert data time*/
    b_is_get_time = a_dst_get_local_time(&t_dtg);
    if(TRUE == b_is_get_time)
    {
        /*format:yr-mo-day hr:min:sec*/
        c_sprintf(s_dt,"%d-%d-%d %d:%d:%d",t_dtg.ui2_yr,t_dtg.ui1_mo,t_dtg.ui1_day,t_dtg.ui1_hr,t_dtg.ui1_min,t_dtg.ui1_sec);
    }

    c_base64_encode(s_dt,c_strlen(s_dt),s_dt_json,NAV_UPDATE_ULI_REG_INFO_DT_JSON_LEN);

    /*merge str and the sequence is: MA->VN->DT->ZC->PH->FN->LN->EM->OC->SN*/

    /*merge MA:mac address str*/
    c_strcat(pstr_out[0],NAV_UPDATE_ULI_MAC_JSON_KEY);
    c_strcat(pstr_out[0],s_mac_json);
    c_strcat(pstr_out[0],"',");

    /*merge VN:firmware version str*/
    c_strcat(pstr_out[0],NAV_UPDATE_ULI_VN_JSON_KEY);
    c_strcat(pstr_out[0],s_vn_json);
    c_strcat(pstr_out[0],"',");

    /*merge DT:data time str*/
    c_strcat(pstr_out[0],NAV_UPDATE_ULI_DT_JSON_KEY);
    c_strcat(pstr_out[0],s_dt_json);
    c_strcat(pstr_out[0],"',");

    do
    {
        /*merge zip code str*/
        c_strcat(pstr_out[0],NAV_UPDATE_ULI_ZIP_CODE_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[NAV_UPDATE_ULI_REG_INFO_ZIP_CODE]);
        c_strcat(pstr_out[0],"',");

        /*merge phone num str*/
        c_strcat(pstr_out[0],NAV_UPDATE_ULI_PHONE_NUM_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[NAV_UPDATE_ULI_REG_INFO_PHONE_NUM]);
        c_strcat(pstr_out[0],"',");

        /*merge first name str*/
        c_strcat(pstr_out[0],NAV_UPDATE_ULI_FIRST_NAME_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[NAV_UPDATE_ULI_REG_INFO_FIRST_NAME]);
        c_strcat(pstr_out[0],"',");

        /*merge last name str*/
        c_strcat(pstr_out[0],NAV_UPDATE_ULI_LAST_NAME_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[NAV_UPDATE_ULI_REG_INFO_LAST_NAME]);
        c_strcat(pstr_out[0],"',");

        /*merge email str*/
        c_strcat(pstr_out[0],NAV_UPDATE_ULI_EMAIL_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[NAV_UPDATE_ULI_REG_INFO_MAIL]);
        c_strcat(pstr_out[0],"',");

        /*merge offer contact str*/
        c_strcat(pstr_out[0],NAV_UPDATE_ULI_OFFER_CONTACT_JSON_KEY);
        c_strcat(pstr_out[0],pstr_in[NAV_UPDATE_ULI_REG_INFO_COMMIT]);
        c_strcat(pstr_out[0],"',");
    }
    while (0);

    /*merge SN:serial num str*/
    c_strcat(pstr_out[0],NAV_UPDATE_ULI_SN_JSON_KEY);
    c_strcat(pstr_out[0],s_sn_json);
    c_strcat(pstr_out[0],"'}");

    NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] _nav_updater_uli_reg_info_json_merge pstr_out[%s]\n",pstr_out[0]));

    return NAVR_OK;
}

/*a_nav_updater_uli_register_user_info()
* user info register:
* phone:       <sting>
* First name:  <sting>
* last name:   <sting>
* postal code: <sting>
* email:       <sting>
*/
extern INT32 a_nav_updater_uli_register_user_info(CHAR p_str_user_info[][NAV_UPDATE_ULI_REG_INFO_STR_MAX_LEN],
                                              UINT8 ui1_str_num)
{
    CHAR    *pstr_json[NAV_UPDATE_ULI_REG_INFO_LAST_ENTRY];
    CHAR    *pstr_json_merge[NAV_UPDATE_ULI_REG_INFO_GROUP_NUM];
    UINT8    ui1_loop = 0;
    INT32    i4_ret = NAVR_OK;
    BOOL     b_is_continue = TRUE;

    do
    {
        if ((NAV_UPDATE_ULI_REG_INFO_LAST_ENTRY != ui1_str_num)
            || (NULL == p_str_user_info))
        {
            NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info arg invalid !!!\n"));
            i4_ret = NAVR_FAIL;
            break;
        }

        /*reset point value*/
        for(ui1_loop = 0; ui1_loop < ui1_str_num; ui1_loop++)
        {
            pstr_json[ui1_loop] = NULL;
        }

        for(ui1_loop = 0; ui1_loop < NAV_UPDATE_ULI_REG_INFO_GROUP_NUM; ui1_loop++)
        {
            pstr_json_merge[ui1_loop] = NULL;
        }

        b_is_continue = TRUE;

        /*convert string to json data format base 64 encode*/
        for(ui1_loop = 0; ui1_loop < ui1_str_num; ui1_loop++)
        {
             pstr_json[ui1_loop] = (CHAR *)c_mem_alloc((NAV_UPDATE_ULI_REG_INFO_JSON_TXT_MAX_LEN + 1)*sizeof(CHAR));

             if(NULL == pstr_json[ui1_loop])
             {
                 NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info pstr_json alloc fail !!!\n"));
                 i4_ret = NAVR_FAIL;
                 b_is_continue = FALSE;
                 break;
             }

             c_memset(pstr_json[ui1_loop], 0, (NAV_UPDATE_ULI_REG_INFO_JSON_TXT_MAX_LEN + 1)*sizeof(CHAR));

             i4_ret = c_base64_encode(p_str_user_info[ui1_loop],c_strlen(p_str_user_info[ui1_loop]),pstr_json[ui1_loop],NAV_UPDATE_ULI_REG_INFO_JSON_TXT_MAX_LEN);
        }

        if (!b_is_continue)
        {
            break;
        }

         /*alloc memory for merged str*/
         for(ui1_loop = 0; ui1_loop < NAV_UPDATE_ULI_REG_INFO_GROUP_NUM; ui1_loop++)
         {
             pstr_json_merge[ui1_loop] = (CHAR *)c_mem_alloc((NAV_UPDATE_ULI_REG_INFO_JSON_TXT_GROUP_MAX_LEN + 1)*sizeof(CHAR));

             if(NULL == pstr_json_merge[ui1_loop])
             {
                 NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info pstr_json_merge alloc fail !!!\n"));
                 i4_ret = NAVR_FAIL;
                 b_is_continue = FALSE;
                 break;
             }

             c_memset(pstr_json_merge[ui1_loop], 0, (NAV_UPDATE_ULI_REG_INFO_JSON_TXT_GROUP_MAX_LEN + 1)*sizeof(CHAR));
         }

         if (!b_is_continue)
         {
             break;
         }

         /*merge reg info to one group*/
         i4_ret = _nav_updater_uli_reg_info_json_merge(pstr_json,pstr_json_merge);
         if (NAVR_OK != i4_ret)
         {
            NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info _nav_updater_uli_reg_info_json_merge fail !!!\n"));
            break;
         }

         /* call ULI api to store user info */
         #ifdef ULI_USE_ODL_LIB
         i4_ret = a_uli_project_reg_store_user_info (
                                  (UINT8**)pstr_json_merge,
                                  (UINT8) NAV_UPDATE_ULI_REG_INFO_GROUP_NUM);
        #endif

         if (ULIR_OK != i4_ret)
         {
             NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info a_uli_project_reg_store_user_info fail !!!\n"));
             i4_ret = NAVR_FAIL;
             break;
         }

     }while (0);


     /* free memory*/
     for(ui1_loop = 0; ui1_loop < ui1_str_num; ui1_loop++)
     {
         if (pstr_json[ui1_loop] != NULL)
         {
             c_mem_free(pstr_json[ui1_loop]);
             pstr_json[ui1_loop] = NULL;
         }
     }

     for(ui1_loop = 0; ui1_loop < NAV_UPDATE_ULI_REG_INFO_GROUP_NUM; ui1_loop++)
     {
         if (pstr_json_merge[ui1_loop]!= NULL)
         {
             c_mem_free(pstr_json_merge[ui1_loop]);
             pstr_json_merge[ui1_loop] = NULL;
         }
     }

     return NAVR_OK;

}

/*a_nav_updater_uli_register_user_info()
* user info register:
* phone:       <sting>
* First name:  <sting>
* last name:   <sting>
* postal code: <sting>
* email:       <sting>
*/
extern INT32 a_nav_updater_uli_register_user_info_new(CHAR p_str_user_info[])
{
    CHAR    *pstr_json_merge[NAV_UPDATE_ULI_REG_INFO_GROUP_NUM] = {0};
    UINT8    ui1_loop = 0;
    INT32    i4_ret = NAVR_OK;

    NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] %s Enter\n", __FUNCTION__));

    if (NULL == p_str_user_info)
    {
        NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info arg invalid !!!\n"));
        i4_ret = NAVR_FAIL;
        return i4_ret;
    }

     /*alloc memory for merged str*/
     for(ui1_loop = 0; ui1_loop < NAV_UPDATE_ULI_REG_INFO_GROUP_NUM; ui1_loop++)
     {
         pstr_json_merge[ui1_loop] = (CHAR *)c_mem_alloc((NAV_UPDATE_ULI_REG_INFO_JSON_TXT_GROUP_MAX_LEN)*sizeof(CHAR));

         if(NULL == pstr_json_merge[ui1_loop])
         {
             NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info pstr_json_merge alloc fail !!!\n"));
             i4_ret = NAVR_FAIL;
             return i4_ret;
         }

         c_memset(pstr_json_merge[ui1_loop], 0, (NAV_UPDATE_ULI_REG_INFO_JSON_TXT_GROUP_MAX_LEN)*sizeof(CHAR));
     }

     /*merge reg info to one group*/
     c_strncat(pstr_json_merge[0], p_str_user_info, NAV_UPDATE_ULI_REG_INFO_JSON_TXT_GROUP_MAX_LEN-1);

     NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info pstr_json_merge: %s\n", pstr_json_merge[0]));

     /* call ULI api to store user info */
     #ifdef ULI_USE_ODL_LIB
     i4_ret = a_uli_project_reg_store_user_info (
                              (UINT8**)pstr_json_merge,
                              (UINT8) NAV_UPDATE_ULI_REG_INFO_GROUP_NUM);
    #else
    i4_ret = a_uli_qda_submit_data (p_str_user_info);
    #endif

     if (ULIR_OK != i4_ret)
     {
         NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] register_user_info a_uli_project_reg_store_user_info fail !!!\n"));
         i4_ret = NAVR_FAIL;
         return i4_ret;
     }

     /* free memory*/
     for(ui1_loop = 0; ui1_loop < NAV_UPDATE_ULI_REG_INFO_GROUP_NUM; ui1_loop++)
     {
         if (pstr_json_merge[ui1_loop]!= NULL)
         {
             c_mem_free(pstr_json_merge[ui1_loop]);
             pstr_json_merge[ui1_loop] = NULL;
         }
     }

     NAV_UPGRADE_LOG_PRINT(("\n[NAV_ULI_REST] %s Exit\n", __FUNCTION__));

     return NAVR_OK;

}


/*Get tv register status*/
extern INT32 a_nav_updater_uli_get_device_register_status(UINT8 *pui1_device_register_status)
{
    ULI_PROJECT_STATUS_STRUCT    t_status;
    CHAR                         s_esn[48];
    CHAR                         s_qh[32];
    CHAR                         s_version[32];
    CHAR                         s_info[128];
    CHAR                         s_error[128];
    INT32                        i4_ret;

    c_memset((VOID*)&t_status, 0, sizeof(ULI_PROJECT_STATUS_STRUCT));

    /* setup return strings */
    t_status.pszESN               = (INT8 *)s_esn;
    t_status.uiESNBufferLen       = sizeof(s_esn);
    t_status.pszQueryHost         = (INT8 *)s_qh;
    t_status.uiQueryHostBufferLen = sizeof(s_qh);
    t_status.pszVersion           = (INT8 *)s_version;
    t_status.uiVersionBufferLen   = sizeof(s_version);
    t_status.pszInfo              = (INT8 *)s_info;
    t_status.uiInfoBufferLen      = sizeof(s_info);
    t_status.pszLastError         = (INT8 *)s_error;
    t_status.uiLastErrorBufferLen = sizeof(s_error);
#ifdef ULI_USE_ODL_LIB

    i4_ret = a_uli_on_status_request(&t_status);
#endif
    if (ULIR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"get_device_register_status a_uli_on_status_request [fail]\n"));
        return NAVR_FAIL;
    }

    if (0 != (t_status.usStatusMask & NAV_UPDATER_ULI_STATUS_MASK_REGISTERED))
    {
        *pui1_device_register_status = NAV_UPDATE_ULI_DEVICE_REGISTER_ACTION_YES;
    }
    else
    {
        *pui1_device_register_status = NAV_UPDATE_ULI_DEVICE_REGISTER_ACTION_NO;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"get_device_register_status register[%d]\n",*pui1_device_register_status));

    return NAVR_OK;
}

/*Get tv register status*/
extern INT32 a_nav_updater_uli_get_user_register_status(UINT8 *pui1_user_register_status)
{
    BOOL  b_user_register = FALSE;
    b_user_register = a_uli_is_user_reg_info();

    if (b_user_register)
    {
        *pui1_user_register_status = NAV_UPDATE_ULI_USER_REGISTER_ACTION_YES;
    }
    else
    {
        *pui1_user_register_status = NAV_UPDATE_ULI_USER_REGISTER_ACTION_NO;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_uli_get_user_register_status b_user_register[%d]\n",b_user_register));

    return NAVR_OK;
}


extern INT32 a_nav_updater_uli_get_updating_status(UINT8 *pui1_updating_status)
{
    NAV_UPDATER_FW_STATE_T  e_fw_state = CHECK_STATE_NONE;
    nav_updater_uli_get_fw_status(&e_fw_state);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_uli_get_updating_status get_fw_status e_fw_state[%d]\n",e_fw_state));

    if ((CHECK_STATE_DOWNLOADING == e_fw_state)
        || (CHECK_STATE_FW_VALIDATING == e_fw_state)
        || (CHECK_STATE_FW_PARSING == e_fw_state)
        || (CHECK_STATE_FW_INITED == e_fw_state)
        || (CHECK_STATE_CHECK_INSTALLING == e_fw_state)
        || (CHECK_STATE_CHECK_INSTALLED == e_fw_state))
    {
        *pui1_updating_status = NAV_UPDATE_ULI_USER_REGISTER_ACTION_YES;
    }
    else
    {
        *pui1_updating_status = NAV_UPDATE_ULI_USER_REGISTER_ACTION_NO;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_uli_get_updating_status updating_status[%d]\n",*pui1_updating_status));

    return NAVR_OK;
}

/*check fw available or not*/
INT32 nav_updater_uli_check_sw_available(NAV_UPDATER_USER_MODE_T e_user_mode)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    INT32  i4_ret;
    BOOL   b_is_fw_download_ready = FALSE;

    /*Default will reject*/
    BOOL   b_is_to_reject = TRUE;
    CHAR                   s_path[128] = {0};
    UINT32                 ui4_size    = 128;

    i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

    b_is_fw_download_ready = _nav_updater_uli_is_fw_ready();
	NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"b_is_fw_download_ready [%d]\n",b_is_fw_download_ready));

    if (NAVR_OK == i4_ret)
    {
        b_is_to_reject = FALSE;
    }
	if (b_is_fw_download_ready && (NAVR_OK == _nav_updater_uli_get_path(s_path, ui4_size)))
	{
		NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"need delete the pre file to trigger again \n"));
		c_fm_delete_file(FM_ROOT_HANDLE, s_path);
	}

    if (!b_is_to_reject)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_check_sw_available e_user_mode[%d]\n",e_user_mode));

        //i4_ret = a_uli_project_on_force_noc_contact();

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_on_force_noc_contact i4_ret[%d]\n",i4_ret));

        nav_updater_uli_set_user_mode(e_user_mode);
        nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_NETWORK_FW_CHECK);

        pt_this->e_method = UPDATER_ULI_METHOD_INTNT;

        nav_updater_trigger_update(pt_this->e_type);

        return NAVR_OK;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_check_sw_available [reject] e_user_mode[%d],i4_ret[%d] fw_download_ready[%d]\n",
                         e_user_mode,i4_ret,b_is_fw_download_ready));

        return NAVR_FAIL;
    }

}

INT32 nav_updater_uli_check_sw_available_and_update(NAV_UPDATER_USER_MODE_T e_user_mode)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    INT32  i4_ret;
    BOOL   b_is_fw_download_ready = FALSE;

    /*Default will reject*/
    BOOL   b_is_to_reject = TRUE;
    CHAR                   s_path[128] = {0};
    UINT32                 ui4_size    = 128;

    i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

    b_is_fw_download_ready = _nav_updater_uli_is_fw_ready();
	NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"b_is_fw_download_ready [%d]\n",b_is_fw_download_ready));

    if (NAVR_OK == i4_ret)
    {
        b_is_to_reject = FALSE;
    }
	if (b_is_fw_download_ready && (NAVR_OK == _nav_updater_uli_get_path(s_path, ui4_size)))
	{
		NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"need delete the pre file to trigger again \n"));
		c_fm_delete_file(FM_ROOT_HANDLE, s_path);
	}

    if (!b_is_to_reject)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_check_sw_available_and_update e_user_mode[%d]\n",e_user_mode));

        //i4_ret = a_uli_project_on_force_noc_contact();

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_uli_project_on_force_noc_contact i4_ret[%d]\n",i4_ret));

        nav_updater_uli_set_user_mode(e_user_mode);
        nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE);

        pt_this->e_method = UPDATER_ULI_METHOD_INTNT;

        nav_updater_trigger_update(pt_this->e_type);

        return NAVR_OK;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_check_sw_available_and_update [reject] e_user_mode[%d],i4_ret[%d] fw_download_ready[%d]\n",
                         e_user_mode,i4_ret,b_is_fw_download_ready));

        return NAVR_FAIL;
    }

}

INT32 nav_updater_uli_start_full_sys_upgrade(NAV_UPDATER_USER_MODE_T e_user_mode)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    INT32 i4_ret;

    i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

    if (NAVR_OK == i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_start_full_sys_upgrade e_user_mode[%d]\n",e_user_mode));
        nav_updater_uli_set_user_mode(e_user_mode);

        nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD_AND_INSTALL);

        pt_this->e_method = UPDATER_ULI_METHOD_INTNT;

        nav_updater_trigger_update(pt_this->e_type);

        return NAVR_OK;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_start_full_sys_upgrade e_user_mode[%d] [reject]\n",e_user_mode));
        return NAVR_FAIL;
    }
}

INT32 nav_updater_uli_start_full_cmd_upgrade(NAV_UPDATER_USER_MODE_T e_user_mode)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    INT32 i4_ret;

    i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

    if (NAVR_OK == i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_start_full_cmd_upgrade e_user_mode[%d]\n",e_user_mode));
        nav_updater_uli_set_user_mode(e_user_mode);

        nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL);

        pt_this->e_method = UPDATER_ULI_METHOD_USB;

        nav_updater_trigger_update(pt_this->e_type);

        return NAVR_OK;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_start_full_sys_upgrade e_user_mode[%d] [reject]\n",e_user_mode));
        return NAVR_FAIL;
    }
}

INT32 nav_updater_uli_start_full_cmd_install(NAV_UPDATER_USER_MODE_T e_user_mode)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    INT32 i4_ret;


    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_start_full_cmd_install e_user_mode[%d]\n",e_user_mode));
    nav_updater_uli_set_user_mode(e_user_mode);

	nav_updater_uli_set_update_stage(STAGE_FW_INSTALING);
    nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL);

    pt_this->e_method = UPDATER_ULI_METHOD_USB;
	a_uli_custom_triger_usb_cmd_install();



        return NAVR_OK;

}


/* fw check & download*/
INT32 nav_updater_uli_start_fw_download(NAV_UPDATER_USER_MODE_T e_user_mode)
{
    UPDATER_ULI_CTRL_T*     pt_this = &t_g_uli_ctrl;
    INT32 i4_ret;
    BOOL   b_is_fw_download_ready = FALSE;

    /*Default will reject*/
    BOOL   b_is_to_reject = TRUE;


    i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

    b_is_fw_download_ready = _nav_updater_uli_is_fw_ready();

    if ((NAVR_OK == i4_ret)
        && (!b_is_fw_download_ready))
    {
        b_is_to_reject = FALSE;
    }

    if (!b_is_to_reject)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_start_fw_download e_user_mode[%d]\n",e_user_mode));
        nav_updater_uli_set_user_mode(e_user_mode);

        nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD);

        pt_this->e_method = UPDATER_ULI_METHOD_INTNT;

        nav_updater_trigger_update(pt_this->e_type);

        return NAVR_OK;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_start_fw_download [reject] e_user_mode[%d],i4_ret[%d] fw_download_ready[%d]\n",
                         e_user_mode,i4_ret,b_is_fw_download_ready));

        return NAVR_FAIL;
    }

}

static INT32 _nav_updater_uli_get_provision_download_status(UINT8  *pui1_download_status)
{
    ULI_PROJECT_PROVISION_STATUS  t_provisioning_status;
    INT32                        i4_ret;

    if (NULL == pui1_download_status)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_updater_uli_get_provision_download_status ARG[invalid]\n"));
        return NAVR_INV_ARG;
    }

    c_memset((VOID*)&t_provisioning_status, 0, sizeof(ULI_PROJECT_PROVISION_STATUS));
#ifdef ULI_USE_ODL_LIB

    i4_ret = a_uli_get_provisioning_status(&t_provisioning_status);
#endif
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Provisioning status[i4_ret[%d], ui4_MaxAvailable[%d],ui4_CurrentlyAvailable[%d],ui4_DeliverySuccess[%d]]\n",
              i4_ret,
              t_provisioning_status.ui4_MaxAvailable,
              t_provisioning_status.ui4_CurrentlyAvailable,
              t_provisioning_status.ui4_DeliverySuccess));

    if (ULIR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"get_provision_download_status a_uli_get_provisioning_status() failed, %d\n", i4_ret));
        *pui1_download_status = NAV_UPDATE_ULI_PROVISION_NOT_READY;

        return NAVR_FAIL;
    }

    if (( t_provisioning_status.ui4_MaxAvailable > 0)
        && (t_provisioning_status.ui4_MaxAvailable == t_provisioning_status.ui4_DeliverySuccess))
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" check_provision provision_ready\n"));
        *pui1_download_status = NAV_UPDATE_ULI_PROVISION_DOWNLOAD_READY;
    }

    else if (t_provisioning_status.ui4_MaxAvailable > 0
        && (t_provisioning_status.ui4_CurrentlyAvailable == 0))
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" check_provision provision_ready\n"));
        *pui1_download_status = NAV_UPDATE_ULI_PROVISION_DOWNLOAD_READY;
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" check_provision provision_not_ready\n"));
        *pui1_download_status = NAV_UPDATE_ULI_PROVISION_NOT_READY;
    }

    return NAVR_OK;
}

static INT32 _nav_update_uli_check_np_time_create(VOID)
{
    INT32 i4_ret;
    if (FALSE == b_g_check_np_time_create)
    {

        if (c_handle_valid(h_check_np_timer) == TRUE) {
            c_timer_delete(h_check_np_timer);
        }


        i4_ret = c_timer_create(&(h_check_np_timer));
        if (i4_ret != OSR_OK) {
            return NAVR_FAIL;
        }
        /* create the query time*/

        b_g_check_np_time_create = TRUE;
    }

    return NAVR_OK;
}

static VOID _nav_update_uli_stop_check_np_timer(VOID)
{
    INT32 i4_ret;

    if (c_handle_valid(h_check_np_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(h_check_np_timer);
    if (i4_ret != OSR_OK) {

    }
}

static VOID _nav_update_uli_check_np_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32     i4_ret;
    UINT8     ui1_download_status = NAV_UPDATE_ULI_PROVISION_NOT_READY;
    i4_ret = _nav_updater_uli_get_provision_download_status(&ui1_download_status);
    if (NAVR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_update_uli_check_np_timeout cas1[fail]\n"));
        /*should reset timer to check*/
        ui4_g_check_np_times_count = NAV_UPDATE_ULI_CHECK_NP_TIMES_MAX_NUM;
    }
    else
    {
        if (NAV_UPDATE_ULI_PROVISION_DOWNLOAD_READY == ui1_download_status)
        {
            ui4_g_check_np_times_count = NAV_UPDATE_ULI_CHECK_NP_TIMES_MAX_NUM;

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_update_uli_check_np_timeout provision_check_ready\n"));
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_update_uli_check_np_timeout [ICL_ULI_DOWNLOAD_STATUS_DONE]\n"));

            /*here should set the icl status*/
            a_icl_set_uli_download_status(ICL_ULI_DOWNLOAD_STATUS_DONE);
            _nav_update_uli_decrypt_widevine_key();
        }
        else
        {

            ui4_g_check_np_times_count ++;
        }
    }

    if (ui4_g_check_np_times_count < NAV_UPDATE_ULI_CHECK_NP_TIMES_MAX_NUM)
    {

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" _nav_update_uli_check_np_timeout reset timer\n"));
        _nav_update_uli_check_np_time_reset();
    }

}

static VOID _nav_update_uli_check_np_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_uli_check_np_timeout, pv_tag, NULL, NULL);
}

static INT32 _nav_update_uli_check_np_time_reset(VOID)
{
    INT32 i4_ret;

    _nav_update_uli_stop_check_np_timer();

    if (ui4_g_check_np_times_count < NAV_UPDATE_ULI_CHECK_NP_TIMES_MAX_NUM) /* will query 2min*/
    {
        i4_ret = c_timer_start(
                        h_check_np_timer,
                        NAV_UPDATE_ULI_CHECK_NP_EVERY_TIMER_OUT,
                        X_TIMER_FLAG_ONCE,
                        _nav_update_uli_check_np_timer_nfy,
                        NULL
                        );
        if (i4_ret != OSR_OK) {

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_uli_check_np_time_reset fail\n"));
        }
    }
    return NAVR_OK;
}

static INT32 _nav_updater_uli_timer_check_provision_download_status(VOID)
{
    INT32 i4_ret;
    i4_ret = _nav_update_uli_check_np_time_create();

    if (NAVR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_uli_check_np_time_create fail\n"));
        return NAVR_FAIL;
    }
    else
    {
        _nav_update_uli_check_np_time_reset();
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_uli_timer_check_provision_download_status\n"));

    return NAVR_OK;
}

#ifdef APP_MULTISKU_USB_SUPPORT
extern CHAR* sys_cust_get_usb_upg_version(VOID);
typedef enum
{
    MULTISKU_FILE_TYPE_UTV = 0,
    MULTISKU_FILE_TYPE_CMD,
    MULTISKU_FILE_TYPE_MAX,
}MULTISKU_FILE_TYPE_T;

#if 0
static INT32 _nav_update_atoi(CHAR *ps)
{
    UINT32    ui4_total;

    ui4_total = 0;
    while ( *ps != 0 )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            /* accumulate digit */
            ui4_total = 10 * ui4_total + (*ps - '0');

            ps++; /* get next char */
        }
        else /* not a digit char */
        {
            ui4_total = 0xFFFF;
            break;
        }
    }

    return ui4_total;
}
#endif

static INT32 _nav_update_get_hexnum(CHAR *ps)
{
    UINT32    ui4_total;

    ui4_total = 0;
    while ( *ps != 0 )
    {
        if ( *ps >= '0' && *ps <= '9' )
        {
            /* accumulate digit */
            ui4_total = 16 * ui4_total + (*ps - '0');
        }
        else if ( *ps >= 'A' && *ps <= 'F' )
        {

            ui4_total = 16 * ui4_total + (*ps - 'A') + 10;
        }
        else if ( *ps >= 'a' && *ps <= 'f' )
        {

            ui4_total = 16 * ui4_total + (*ps - 'a') + 10;
        }
        else /* not a digit char */
        {
            ui4_total = 0xFFFF;
            break;
        }

        ps++; /* get next char */
    }

    return ui4_total;
}


#if 0
static void _nav_update_str_trm(CHAR *s_sting)
{
    CHAR *pstring_tmp = s_sting;

    while ('\0' != *s_sting)
    {
        if (' ' != *pstring_tmp)
        {
            *pstring_tmp = *s_sting;
            pstring_tmp++;
        }
        s_sting++;
    }
    *pstring_tmp = '\0';
}
#endif

static void _nav_update_str_right_trim(CHAR *s_sting)
{
    CHAR *pstring_tmp = s_sting + c_strlen(s_sting) - 1;

    while (' ' == *pstring_tmp)
    {
        *pstring_tmp = '\0';
        pstring_tmp--;
    }
}

static void _nav_update_str_left_trim(CHAR *s_sting)
{
    CHAR *pstring_tmp = s_sting;

    while (' ' == *pstring_tmp)
    {
        pstring_tmp++;
    }

    while('\0' != *pstring_tmp)
    {
        *s_sting = *pstring_tmp;
        s_sting++;
        pstring_tmp++;
    }

    *s_sting = '\0';
}

static INT32 _nav_update_check_multisku_info_by_text_line(char *s_text_line,
                                                   MULTISKU_INFO_T *pt_multisku_info)
{
    UINT32 ui4_cfg_type_index = 0;
    UINT32 ui4_idx_txt = 0;
    UINT32 ui4_mg_value = 0;

    CHAR s_mg_info[MULTISKU_FILE_NAME_MAX_LEN];
    CHAR s_ver_info[MULTISKU_FILE_NAME_MAX_LEN];
    CHAR s_name_info[MULTISKU_FILE_NAME_MAX_LEN];
    CHAR *p_str_tmp = s_text_line;

    c_memset( s_mg_info, 0, MULTISKU_FILE_NAME_MAX_LEN );
    c_memset( s_ver_info, 0, MULTISKU_FILE_NAME_MAX_LEN );
    c_memset( s_name_info, 0, MULTISKU_FILE_NAME_MAX_LEN );


    for (ui4_idx_txt = 0; (0 != s_text_line[ui4_idx_txt]) && ('\r' != s_text_line[ui4_idx_txt]) && ('\n' != s_text_line[ui4_idx_txt]); ui4_idx_txt++);

    s_text_line[ui4_idx_txt] = 0;

    ui4_idx_txt = 0;

    while ('\0' != *p_str_tmp)
    {
        if (CONTENT_CFG_TYPE_MG == ui4_cfg_type_index)
        {
            if (',' != *p_str_tmp)
            {
                s_mg_info[ui4_idx_txt] = *p_str_tmp;
                ui4_idx_txt++;
            }
            else
            {
                s_mg_info[ui4_idx_txt]= '\0';

                ui4_idx_txt=0;
                ui4_cfg_type_index++;
            }

            p_str_tmp++;
        }
        else if (CONTENT_CFG_TYPE_VER == ui4_cfg_type_index)
        {
            if (',' != *p_str_tmp)
            {
                s_ver_info[ui4_idx_txt] = *p_str_tmp;
                ui4_idx_txt++;
            }
            else
            {
                s_ver_info[ui4_idx_txt]= '\0';
                ui4_idx_txt=0;
                ui4_cfg_type_index++;
            }

            p_str_tmp++;

        }
        else if (CONTENT_CFG_TYPE_NAME == ui4_cfg_type_index)
        {
            /*This should be the last one*/

            s_name_info[ui4_idx_txt] = *p_str_tmp;
            ui4_idx_txt++;
            p_str_tmp++;

        }
        else
        {

        }
    }

    s_name_info[ui4_idx_txt] = '\0';
    ui4_cfg_type_index++;

    if (CONTENT_CFG_TYPE_MAX != ui4_cfg_type_index)
    {
        return NAVR_FAIL;
    }


    for (ui4_cfg_type_index = 0; ui4_cfg_type_index < CONTENT_CFG_TYPE_MAX; ui4_cfg_type_index++)
    {
        switch(ui4_cfg_type_index)
        {
            case CONTENT_CFG_TYPE_MG:
                {
                    _nav_update_str_right_trim(s_mg_info);

                    _nav_update_str_left_trim(s_mg_info);
                }
                break;

            case CONTENT_CFG_TYPE_VER:
                {
                    _nav_update_str_right_trim(s_ver_info);
                    _nav_update_str_left_trim(s_ver_info);
                }
                break;

            case CONTENT_CFG_TYPE_NAME:
                {
                    _nav_update_str_right_trim(s_name_info);
                    _nav_update_str_left_trim(s_name_info);
                }
                break;
            default:
                break;
        }
    }



    /*check mg value*/
    if ((c_strlen(s_mg_info) < MULTISKU_MG_CFG_MIN_LEN)
        || ((s_mg_info[0] != 'm') && (s_mg_info[0] != 'M'))
        || ((s_mg_info[1] != 'g') && (s_mg_info[1] != 'G')))
    {
        return NAVR_FAIL;
    }

    ui4_mg_value = _nav_update_get_hexnum(s_mg_info+MULTISKU_MG_CFG_PREFIX_LEN);

    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_update_check_multisku_info_by_text_line mg_value[%d]\n",ui4_mg_value));

    /*only get the first config of the utv & cmd*/
    if (ui4_mg_value == pt_multisku_info->ui4_mg_value)
    {
        /*check the name config*/
        if (c_strlen(s_name_info) >= MULTISKU_NAME_CFG_MIN_LEN)
        {
            if (0 == c_strcmp((s_name_info+c_strlen(s_name_info)-MULTISKU_NAME_CFG_SUFFIX_LEN),UTV_FILE_SUFFIX_NAME))
            {
                /*this is the utv case*/
                if (!(pt_multisku_info->b_utv_file_config))
                {
                    c_strncpy(pt_multisku_info->s_utv_file_name,s_name_info,MULTISKU_FILE_NAME_MAX_LEN-1);

                    pt_multisku_info->b_utv_file_config = TRUE;
                }

            }
            else if (0 == c_strcmp((s_name_info+c_strlen(s_name_info)-MULTISKU_NAME_CFG_SUFFIX_LEN),CMD_FILE_SUFFIX_NAME))
            {
                /*this is the cmd case*/
                if (!(pt_multisku_info->b_cmd_file_config))
                {
                    c_strncpy(pt_multisku_info->s_cmd_file_name,s_name_info,MULTISKU_FILE_NAME_MAX_LEN-1);
                    pt_multisku_info->b_cmd_file_config = TRUE;
                }

            }
            else
            {
                /*do nothing*/
            }
        }

    }

    return NAVR_OK;
}

static INT32 _nav_update_get_platform_mg_value(UINT32 *pui4_mg_value)
{
    UINT32 ui4_mg = 0;
    CHAR   s[32] = {0};
    FILE* fp = fopen("/proc/cmdline", "r");

    if (fp)
    {
        while (!feof(fp) && fscanf(fp, "%30s", s) == 1)
        {
            if (sscanf(s, "MODELGROUP=%x", &ui4_mg) == 1)
            {
                break;
            }
        }

        fclose(fp);
    }
    else
    {
        return NAVR_FAIL;
    }

    *pui4_mg_value = ui4_mg;

    return NAVR_OK;
}


static INT32 _nav_update_get_multisku_info(char *s_file_name,
                                    MULTISKU_INFO_T *pt_multisku_info)
{
    FILE *fp = NULL;
    CHAR s_text_line[MULTISKU_LINE_MAX_LEN];
    UINT32 ui4_mg_value = 0;
    INT32  i4_ret;

    if((NULL == pt_multisku_info)
        ||(NULL == s_file_name))
    {
        return NAVR_INV_ARG;
    }

    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_update_get_multisku_info s_file_name[%s]\n",
        s_file_name));

    if (NULL == (fp = fopen(s_file_name,"r")))
    {
        return NAVR_FAIL;
    }

    c_memset( s_text_line, 0, MULTISKU_LINE_MAX_LEN );

    /*get currnt mg info*/
    i4_ret = _nav_update_get_platform_mg_value(&ui4_mg_value);
    if (NAVR_OK != i4_ret)
    {
    	fclose (fp);
        return NAVR_FAIL;
    }


    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_update_get_multisku_info ui4_mg_value[0x%x]\n",
        ui4_mg_value));

    pt_multisku_info->ui4_mg_value = ui4_mg_value;

    while (NULL != fgets(s_text_line,MULTISKU_LINE_MAX_LEN,fp))
    {

        NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_update_get_multisku_info s_text_line[%s]\n",
            s_text_line));

        _nav_update_check_multisku_info_by_text_line(s_text_line,
            pt_multisku_info);

        c_memset( s_text_line, 0, MULTISKU_LINE_MAX_LEN );
    }

    fclose(fp);

    return NAVR_OK;

}

static INT32 _nav_update_create_utv_trigger_file_with_content(char *s_file_name,
                            char *s_txt_content)
{
    int fd = -1;

    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_update_create_utv_trigger_file_with_content s_file_name[%s],s_txt_content[%s]\n",
        s_file_name,
        s_txt_content));

    if ((fd = open(s_file_name, O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1)
    {

        NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_update_create_utv_trigger_file_with_content open[Fail]\n"));
        /*file create fail*/
        return NAVR_FAIL;
    }
    else
    {
        /*file exist and then write txt to this file*/
        write(fd,s_txt_content,c_strlen(s_txt_content));
        fsync(fd);
        close(fd);
    }
    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_update_create_utv_trigger_file_with_content success\n"));

    return NAVR_OK;
}

static INT32 _nav_updater_get_multisku_usb_path(CHAR *s_path,UINT32 ui4_size,BOOL *pb_multisku_exist)
{
    CHAR              s_mnt_point[512] = { 0 };
    CHAR              s_file_name[512] = { 0 };
    SIZE_T            z_mnt_point_size = 512;
    UINT32            ui4_mnt_count;
    UINT8             ui1_i;
    FM_FILE_INFO_T    t_file_info;
    INT32 ret_val = RMVR_OK;

    ret_val = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if(RMVR_OK != ret_val)
    {
        NAV_UPGRADE_LOG_PRINT(("[nav_updater_uli.c %s() L%d] a_rmv_dev_get_mnt_count ret [%d]\n", __func__, __LINE__, ret_val));
        return NAVR_FAIL;
    }else if(0 == ui4_mnt_count){
        c_thread_delay(200);
        ret_val = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
        if((RMVR_OK != ret_val)|| (0 == ui4_mnt_count)){
            NAV_UPGRADE_LOG_PRINT(("[nav_updater_uli.c %s() L%d] ui4_mnt_count[%d]\n", __func__, __LINE__, ui4_mnt_count));
            return NAVR_FAIL;
        }
    }

    for (ui1_i = 0 ; ui1_i < ui4_mnt_count ; ui1_i++)
    {
        if (RMVR_OK != a_rmv_dev_get_mnt_point(ui1_i, &z_mnt_point_size, s_mnt_point))
        {
            continue;
        }

        c_snprintf(s_file_name, 512, "%s/%s", s_mnt_point, MULTISKU_TXT_CFG_FILE_NAME);

        if (FMR_OK == c_fm_get_info_by_name(FM_ROOT_HANDLE, s_file_name, &t_file_info))
        {
            c_strncpy(s_path,s_mnt_point,ui4_size-1);
            s_path[ui4_size-1] = '\0';
            *pb_multisku_exist = TRUE;
            break;
        }
    }

    return NAVR_OK;
}


static INT32 _nav_updater_check_usb_multisku(CHAR *s_multisku_file_name)
{
    MULTISKU_INFO_T*    pt_multisuk = &t_multisuk_info;
    CHAR s_usb_path[MULTISKU_FILE_NAME_MAX_LEN];
    CHAR s_usb_multisku_file_name[MULTISKU_FILE_NAME_MAX_LEN];
    CHAR s_utv_trigger_file_name[MULTISKU_FILE_NAME_MAX_LEN];
    BOOL  b_multisku_exist = FALSE;
    INT32 i4_ret;

    c_memset(s_usb_path,0,MULTISKU_FILE_NAME_MAX_LEN);
    c_memset(s_usb_multisku_file_name,0,MULTISKU_FILE_NAME_MAX_LEN);
    c_memset(s_utv_trigger_file_name,0,MULTISKU_FILE_NAME_MAX_LEN);

    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_check_usb_multisku Enter\n"));

    do
    {
        if (nav_updater_is_running())
        {
            NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_check_usb_multisku Break[nav_updater_is_running]\n"));
            break;
        }

        if (!pt_multisuk->b_is_multisku_info_init)
        {
            /*current this just for usb case*/
            i4_ret = _nav_updater_get_multisku_usb_path(s_usb_path,
                        MULTISKU_FILE_NAME_MAX_LEN,
                        &b_multisku_exist);

            if ((NAVR_OK == i4_ret)
                && (b_multisku_exist))
            {
                NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_check_usb_multisku find MULTISKU_FILE\n"));
                c_strcpy(pt_multisuk->s_usb_root_path,s_usb_path);
                c_snprintf(s_usb_multisku_file_name, MULTISKU_FILE_NAME_MAX_LEN, "%s/%s", pt_multisuk->s_usb_root_path, s_multisku_file_name);


                /*analysis the multisku config file*/
                _nav_update_get_multisku_info(s_usb_multisku_file_name,pt_multisuk);
            }
            else
            {
                NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_check_usb_multisku Break[No MULTISKU_FILE]\n"));
                break;
            }

        }

        /*dump multisku info*/

        NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] multisku_info ("
                  "b_utv_file_config[%d),"
                  "b_cmd_file_config[%d],"
                  "s_usb_root_path[%s],"
                  "s_utv_file_name[%s],"
                  "s_cmd_file_name[%s]"
                  "b_is_multisku_info_init[%d],"
                  "b_is_utv_checked[%d],"
                  "ui4_mg_value[%d]"
                  ")\n",
                  pt_multisuk->b_utv_file_config,
                  pt_multisuk->b_cmd_file_config,
                  pt_multisuk->s_usb_root_path,
                  pt_multisuk->s_utv_file_name,
                  pt_multisuk->s_cmd_file_name,
                  pt_multisuk->b_is_multisku_info_init,
                  pt_multisuk->b_is_utv_checked,
                  pt_multisuk->ui4_mg_value
                  ));

        if ((pt_multisuk->b_utv_file_config)
            || (pt_multisuk->b_cmd_file_config))
        {
            pt_multisuk->b_is_multisku_info_init = TRUE;

            NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_check_usb_multisku b_is_multisku_info_init[TRUE]\n"));
        }

        if (pt_multisuk->b_utv_file_config)
        {
            /*just trigger utv*/
            c_snprintf(s_utv_trigger_file_name, MULTISKU_FILE_NAME_MAX_LEN, "%s/%s", pt_multisuk->s_usb_root_path, NAV_UPDATER_ULI_REDIRECT_FILE_NAME);

            NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_check_usb_multisku Create utv trigger file\n"));
            _nav_update_create_utv_trigger_file_with_content(s_utv_trigger_file_name,
                            pt_multisuk->s_utv_file_name);
        }
        else if (pt_multisuk->b_cmd_file_config)
        {
            /*here will run the cmd*/
            c_snprintf(s_utv_trigger_file_name, MULTISKU_FILE_NAME_MAX_LEN, "%s/%s", pt_multisuk->s_usb_root_path, NAV_UPDATER_ULI_REDIRECT_FILE_NAME);

            NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_check_usb_multisku Create cmd trigger file\n"));

            _nav_update_create_utv_trigger_file_with_content(s_utv_trigger_file_name,
                            pt_multisuk->s_cmd_file_name);
        }
        else
        {
            /*do nothing*/
        }

#if 0
        if ((pt_multisuk->b_utv_file_config)
            &&(FALSE == pt_multisuk->b_is_utv_checked))
        {
#if 0
            /*here should just check the utv file*/
            _nav_update_create_utv_trigger_file_with_content(char *s_file_name,
                            pt_multisuk->s_utv_file_name)
#endif
        }
#endif


    }while (0);

    return NAVR_OK;
}

static BOOL _start_with(CHAR* src,CHAR* start)
{
    BOOL result = FALSE;
    UINT32 start_len = 0,src_len = 0;

    if(src == NULL || start == NULL)
    {
        return FALSE;
    }

    start_len = strlen(start);
    src_len = strlen(src);
    if(src_len < start_len)
    {
        return FALSE;
    }

    if(strncmp(src,start,start_len) == 0)
    {
        result = TRUE;
    }

    return result;
}

static BOOL _end_with(CHAR* src,CHAR* end)
{
    BOOL result = TRUE;
    UINT32 end_len = 0,src_len = 0;
    INT32 i,j;

    if(src == NULL || end == NULL)
    {
        return FALSE;
    }

    end_len = strlen(end);
    src_len = strlen(src);
    if(src_len < end_len)
    {
        return FALSE;
    }

    for(i = end_len-1,j = src_len-1;i >= 0 && j >= 0; --i,--j)
    {
        if(end[i] != src[j])
        {
            result = FALSE;
            break;
        }
    }

    return result;
}

static INT32 _nav_updater_uli_find_multisku_file_in_usb_disk(MULTISKU_FILE_TYPE_T multidku_file_type,CHAR* file_name,CHAR *usb_path)
{
    UINT32            ui4_mnt_count;
    UINT8             ui1_i;
    UINT32            ui4_mg_value;
    CHAR*             ver_str;
    CHAR*             ver_str_tmp;
    CHAR              model_group[32] = {0};
    CHAR*             utv_type = ".utv";
    CHAR*             cmd_type = ".cmd";
    INT32             i4_ver1,i4_ver2,i4_ver3;
    //CHAR              tmp_file_name[FM_MAX_FILE_LEN] = {0};


    if(multidku_file_type >= MULTISKU_FILE_TYPE_MAX)
    {
        NAV_UPGRADE_LOG_PRINT(("zile_multi,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        return NAVR_FAIL;
    }
    if(file_name == NULL || usb_path == NULL)
    {
        NAV_UPGRADE_LOG_PRINT(("zile_multi,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        return NAVR_FAIL;
    }
    file_name[0] = 0;

    if(NAVR_OK != _nav_update_get_platform_mg_value(&ui4_mg_value))
    {
        NAV_UPGRADE_LOG_PRINT(("zile_multi,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        return NAVR_FAIL;
    }

    model_group[0] = 'm';
    model_group[1] = 'g';
    sprintf((model_group+2),"%x",ui4_mg_value);
    //itoa(ui4_mg_value,(model_group+2),10);
    model_group[strlen(model_group)] = '-';

    ver_str = sys_cust_get_usb_upg_version();
    if(ver_str == NULL)
    {
        NAV_UPGRADE_LOG_PRINT(("zile_multi,ERROR,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        return NAVR_FAIL;
    }
    ver_str_tmp = (CHAR*)(ver_str+1);
	NAV_UPGRADE_LOG_PRINT(("%d,%s,%s i4_ver1:%d i4_ver2:%d i4_ver3:%d \n",__LINE__,__func__,__FILE__,i4_ver1,i4_ver2,i4_ver3));
    sscanf(ver_str_tmp,"%d.%d.%d\n",&i4_ver1,&i4_ver2,&i4_ver3);

    if ((RMVR_OK != a_rmv_dev_get_mnt_count(&ui4_mnt_count)) || (0 == ui4_mnt_count))
    {
        NAV_UPGRADE_LOG_PRINT(("zile_multi,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        return NAVR_FAIL;
    }
	NAV_UPGRADE_LOG_PRINT(("%d,%s,%s ver_str_tmp:%s \n",__LINE__,__func__,__FILE__,ver_str_tmp));

    for (ui1_i = 0 ; ui1_i < ui4_mnt_count ; ui1_i++)
    {
        CHAR                s_mnt_point[FM_MAX_FILE_LEN] = { 0 };
        SIZE_T              z_mnt_point_size = FM_MAX_FILE_LEN;

        HANDLE_T            h_dir_hdl;
        FM_DIR_ENTRY_T      t_dir_entr;
        UINT32              ui4_num_entr;
        INT32               i4_ret;
        INT32               i;


        if (RMVR_OK != a_rmv_dev_get_mnt_point(ui1_i, &z_mnt_point_size, s_mnt_point))
        {
            continue;
        }
        i4_ret = c_fm_open_dir(FM_ROOT_HANDLE, s_mnt_point, &h_dir_hdl);
        if (FMR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT(("zile_multi,ERROR,%d,%s,%s\n",__LINE__,__func__,__FILE__));
            return NAVR_FAIL;
        }

        do
        {
            CHAR file_name_lower_case[FM_MAX_FILE_LEN] = {0};
            c_memset(&t_dir_entr, 0, sizeof(FM_DIR_ENTRY_T));

            i4_ret = c_fm_read_dir_entries(h_dir_hdl, &t_dir_entr, 1, &ui4_num_entr);
            if (FMR_EOF == i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT(("zile_multi,no more files,%d,%s,%s\n",__LINE__,__func__,__FILE__));
                break;
            }
            else if (FMR_OK != i4_ret || 0 == ui4_num_entr)
            {
                NAV_UPGRADE_LOG_PRINT(("zile_multi,ERROR,%d,%s,%s\n",__LINE__,__func__,__FILE__));
                break;
            }

            if ((0 == c_strcmp(t_dir_entr.s_name, "."))  ||
                (0 == c_strcmp(t_dir_entr.s_name, "..")) ||
                FM_IS_DIR(t_dir_entr.t_file_info.ui4_mode))
            {
                continue;
            }
            for(i = 0;t_dir_entr.s_name[i] && i < FM_MAX_FILE_LEN-1;++i)
            {
                file_name_lower_case[i] = tolower(t_dir_entr.s_name[i]);
            }

            if(multidku_file_type == MULTISKU_FILE_TYPE_UTV)
            {
                if(_start_with(file_name_lower_case,model_group) && _end_with(file_name_lower_case,utv_type))
                {
                    CHAR* pos_version_start;
                    CHAR* pos_version_end;
                    CHAR *p;
                    CHAR file_name_version[FM_MAX_FILE_LEN] = {0};
                    INT32 i = 0;
                    INT32 i4_filename_ver1,i4_filename_ver2,i4_filename_ver3;
                    BOOL b_file_exist = FALSE;
					NAV_UPGRADE_LOG_PRINT(("file_name_lower_case:%s\n",file_name_lower_case));

                    pos_version_start = (CHAR*)((UINT32)file_name_lower_case + strlen(model_group));
                    pos_version_end = strrchr(file_name_lower_case,'.');
					NAV_UPGRADE_LOG_PRINT(("pos_version_start:%s pos_version_end:%s \n",pos_version_start,pos_version_end));
                    for(i = 0,p = pos_version_start;p < pos_version_end;i++,p++)
                    {
                        file_name_version[i] = *p;
                    }
					NAV_UPGRADE_LOG_PRINT(("file_name_version:%s \n",file_name_version));
                    sscanf(file_name_version,"%d.%d.%d\n",&i4_filename_ver1,&i4_filename_ver2,&i4_filename_ver3);
					NAV_UPGRADE_LOG_PRINT(("%d,%s,%s  i4_filename_ver1:%d i4_filename_ver2:%d i4_filename_ver3:%d \n",__LINE__,__func__,__FILE__,
						i4_filename_ver1,i4_filename_ver2,i4_filename_ver3));

                    if(i4_filename_ver1 == i4_ver1 && i4_filename_ver2 == i4_ver2 && i4_filename_ver3 == i4_ver3)
                    {
                        if(strcmp(file_name_version,ver_str_tmp) > 0)
                        {
                            b_file_exist = TRUE;
                        }
                    }
                    else if(i4_filename_ver1 == i4_ver1 && i4_filename_ver2 == i4_ver2 && i4_filename_ver3 > i4_ver3)
                    {
                        b_file_exist = TRUE;
                    }
                    else if(i4_filename_ver1 == i4_ver1 && i4_filename_ver2 > i4_ver2)
                    {
                        b_file_exist = TRUE;
                    }
                    else if(i4_filename_ver1 > i4_ver1)
                    {
                        b_file_exist = TRUE;
                    }

                    if(b_file_exist == TRUE)
                    {
                        strcpy(file_name,t_dir_entr.s_name);
                        strcpy(usb_path,s_mnt_point);
                    }
                }
            }
            else if(multidku_file_type == MULTISKU_FILE_TYPE_CMD)
            {
                if(_start_with(file_name_lower_case,model_group) && _end_with(file_name_lower_case,cmd_type))
                {
                    strcpy(file_name,t_dir_entr.s_name);
                    strcpy(usb_path,s_mnt_point);
                    break;
                }
            }
        }while(TRUE);

        i4_ret = c_fm_close(h_dir_hdl);
        if (FMR_OK != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT(("zile_multi,ERROR,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        }
    }
    return NAVR_OK;

}
static VOID _nav_updater_uli_do_multisku(VOID)
{
    INT32 ret;
    //UINT32 ui4_mg_value;
    //CHAR utv_file_version[FM_MAX_FILE_LEN] = {0};
    CHAR utv_file_name[FM_MAX_FILE_LEN] = {0};
    CHAR cmd_file_name[FM_MAX_FILE_LEN] = {0};
    CHAR usb_path[FM_MAX_FILE_LEN] = {0};

    if (nav_updater_is_running())
    {
        NAV_UPGRADE_LOG_PRINT(("zile_multi,nav_updater_is_running,%d,%s,%s\n",__LINE__,__func__,__FILE__));
        return;
    }

    ret = _nav_updater_uli_find_multisku_file_in_usb_disk(MULTISKU_FILE_TYPE_UTV,utv_file_name,usb_path);

    if(ret!= 0 || utv_file_name[0] == 0)
    {
        ret = _nav_updater_uli_find_multisku_file_in_usb_disk(MULTISKU_FILE_TYPE_CMD,cmd_file_name,usb_path);
        if(ret == 0 && cmd_file_name[0] != 0)
        {
            CHAR full_name[FM_MAX_FILE_LEN] = {0};
            FILE *fp = NULL;
			c_memset(usb_update_path,0,512);
			sprintf(usb_update_path,"%s/%s",usb_path,cmd_file_name);
			NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" usb_update_path:%s \n",usb_update_path));

            sprintf(full_name,"%s/%s",usb_path,"updatelogic.txt");
            fp = fopen(full_name,"w");
            if(fp)
            {
                fprintf(fp,"%s",cmd_file_name);
                fclose(fp);
            }

        }
        return;
    }
    else if(ret == 0 && utv_file_name[0] != 0)
    {
        CHAR full_name[FM_MAX_FILE_LEN] = {0};
        FILE *fp = NULL;
		c_memset(usb_update_path,0,512);
		sprintf(usb_update_path,"%s/%s",usb_path,utv_file_name);
		NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" usb_update_path:%s \n",usb_update_path));
        sprintf(full_name,"%s/%s",usb_path,"updatelogic.txt");
        fp = fopen(full_name,"w");
        if(fp)
        {
            fprintf(fp,"%s",utv_file_name);
            fclose(fp);
        }
    }
    return;

}


#endif

INT32 nav_updater_set_update_ver_string(CHAR *s_ver_str)
{
    FILE* fp = NULL;

    if (NULL == s_ver_str)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_set_update_ver_string ARG[Invalid]\n"));
        return NAVR_INV_ARG;
    }

    fp = fopen(UPDATE_FW_VER_STRING_FILE,"w");
    if (NULL == fp)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_set_update_ver_string fopen[Fail]\n"));
        return NAVR_FAIL;
    }

    fputs(s_ver_str,fp);

    fflush(fp);

    fclose(fp);

    sync();

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_set_update_ver_string s_ver_str[%s]\n",s_ver_str));

    return 0;
}



INT32 nav_updater_get_update_ver_string(CHAR *s_ver_str)
{
    FILE* fp = NULL;

    if (NULL == s_ver_str)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_update_ver_string ARG[Invalid]\n"));
        return NAVR_INV_ARG;
    }

    fp = fopen(UPDATE_FW_VER_STRING_FILE,"r");
    if (NULL == fp)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_update_ver_string fopen[Fail]\n"));
        return NAVR_FAIL;
    }

    fgets(s_ver_str, NAV_UPDATE_FW_VER_STR_MAX_LEN-1, fp);

    fclose(fp);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_update_ver_string s_ver_str[%s]\n",s_ver_str));

    return NAVR_OK;
}


static BOOL _nav_update_uli_is_widevine_key_ready(VOID)
{

    #define WIDEVINE_KEY_PATH "/data/widevine/WVkeybox"
    INT32 ret;
    struct stat buf;

    memset(&buf,0,sizeof(struct stat));
    ret = stat(WIDEVINE_KEY_PATH,&buf);
    if(ret < 0 || buf.st_size == 0)
    {
        return FALSE;
    }
    return TRUE;
}

static VOID _nav_update_uli_decrypt_widevine_key(VOID)
{
#define WIDEVINE_LOG_PREFIX "zile_wv"
#define WIDEVINE_KEY_DIR "/data/widevine"
#define WIDEVINE_KEY_PATH "/data/widevine/WVkeybox"
#define APP_WIDEVINE       "WIDEVINE2"
#define KEY_WIDEVINE       "WIDEVINE2"
#define WIDEVINE_ID_BUFF_SIZE                         (1024)
#define WIDEVINE_CONTENT_BUFF_SIZE                    (1024 * 6)

    INT32            i4_ret = 0;
    CHAR             s_owner_name[16] = {0};
    CHAR             s_object_name[16] = {0};
    CHAR             s_obj_id[WIDEVINE_ID_BUFF_SIZE] = {0};
    CHAR             s_obj_content[WIDEVINE_CONTENT_BUFF_SIZE] = {0};
    unsigned long    ui4_obj_sz = 0;
    unsigned long    ui4_encrypt_type = 0;
    FILE             *fp_wv = NULL;

    if(0 != access(WIDEVINE_KEY_DIR, 0))
    {
        i4_ret = mkdir(WIDEVINE_KEY_DIR, S_IRWXU|S_IRWXG|S_IRWXO);

        if (0 != i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT((WIDEVINE_LOG_PREFIX"mkdir /data/widevine failed!\n"));
            return;
        }
    }
#ifdef ULI_USE_ODL_LIB

    i4_ret = utv_project_get_owner(APP_WIDEVINE, (char *)&(s_owner_name[0]));
    if (0 != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((WIDEVINE_LOG_PREFIX"utv_project_get_owner() failed, %d\n", i4_ret));

        return;
    }

    i4_ret = utv_project_get_name(KEY_WIDEVINE, (char *)&(s_object_name[0]));
    if (0 != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((WIDEVINE_LOG_PREFIX"utv_project_get_name() failed, %d\n", i4_ret));

        return;
    }

    i4_ret = utv_project_on_obj_req((char *)&(s_owner_name[0]),
                                    (char *)&(s_object_name[0]),
                                    &(s_obj_id[0]),
                                    WIDEVINE_ID_BUFF_SIZE,
                                    (unsigned char*)s_obj_content,
                                    WIDEVINE_CONTENT_BUFF_SIZE,
                                    &ui4_obj_sz,
                                    &ui4_encrypt_type);
    if (0 != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((WIDEVINE_LOG_PREFIX"utv_project_on_obj_req() failed, %d\n", i4_ret));

        return;
    }
#endif
    fp_wv = fopen(WIDEVINE_KEY_PATH, "wb");
    if (NULL != fp_wv)
    {
        fwrite(s_obj_content, ui4_obj_sz, 1, fp_wv);
        fclose(fp_wv);
        chmod(WIDEVINE_KEY_PATH,0644);
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((WIDEVINE_LOG_PREFIX"open /data/widevine/WVkeybox failed!\n"));
        return;
    }
}


INT32 nav_updater_uli_check_provisioning_status(VOID)
{
    UINT8     ui1_download_status = NAV_UPDATE_ULI_PROVISION_NOT_READY;
    INT32     i4_ret;
    BOOL      b_is_key_ready = FALSE;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_check_provisioning_status \n"));

    if (g_b_uli_provisioning_checked)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_check_provisioning_status g_b_uli_provisioning_checked\n"));
        return NAVR_OK;
    }

    i4_ret = _nav_updater_uli_get_provision_download_status(&ui1_download_status);
    if (NAVR_OK != i4_ret)
    {
        /*Do nothing*/
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"check_provisioning_status get_provision_download_status fail\n"));
    }
    else
    {
        if (NAV_UPDATE_ULI_PROVISION_DOWNLOAD_READY == ui1_download_status)
        {
            /*do nothing*/
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"check_provisioning_status get_provision_download_status [ready]\n"));
            i4_ret = nav_updater_get_cast_key_status(&b_is_key_ready);
            if (NAVR_OK == i4_ret)
            {
                if (FALSE == b_is_key_ready)
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_check_provisioning_status [ICL_ULI_DOWNLOAD_STATUS_DONE]\n"));
                    /*here should set the icl status*/
                    a_icl_set_uli_download_status(ICL_ULI_DOWNLOAD_STATUS_DONE);
                }
            }
            _nav_update_uli_decrypt_widevine_key();

            g_b_uli_provisioning_checked = TRUE;
        }
        else
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"check_provisioning_status _nav_updater_uli_timer_check_provision_download_status\n"));
            _nav_updater_uli_timer_check_provision_download_status();
        }
    }


    return NAVR_OK;
}

UPDATER_USB_TYPE_T a_nav_updater_uli_get_usb_upgrade_type(VOID)
{
    return e_usb_update_type;
}
#endif /* APP_ULI_UPG_SUPPORT */

