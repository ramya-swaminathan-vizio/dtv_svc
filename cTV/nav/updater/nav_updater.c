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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <sys/time.h>
#include <mqueue.h>

#include "c_dbg.h"
#include "c_os.h"
#include "u_dlm.h"
#include "u_pcl.h"
#include "c_dlm.h"
#include "c_pcl.h"
#include "c_xml_api.h"
#include "c_fm.h"
#include "c_version.h"
#include "c_iom.h"
#include "c_handle.h"
#include "c_httpc_api.h"

#include "app_util/a_updater.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "app_util/a_icl.h"
#include "am/a_am.h"
#ifdef APP_EAS_SUPPORT
#include "eas/a_eas.h"
#endif
#include "nav/power/a_nav_power.h"
#include "wizard_anim/a_wzd.h"
#include "wizard/a_wzd.h"
#include "nav/a_banner.h"
#include "agent/a_agent.h"

#include "nav/nav_common.h"
#include "nav/a_navigator.h"
#include "nav/updater/nav_updater.h"
#include "nav/twinkle_msg/a_scrn_svr.h"

#include "res/nav/nav_variant.h"
#include "res/app_util/updater/a_updater_custom.h"
#include "res/nav/updater/nav_updater_res.h"
#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#endif

#ifdef APP_NAV_SCART_MONITOR
#include "nav/scart_monitor/a_scart_monitor.h"
#endif

#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_cust_odm.h"
#include "res/app_util/dev_db/a_dev_db_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "project-mtk-new-api.h"
#include "app_util/a_icl_common.h"
#include "res/msgconvert/msgconvert_custom.h"
#include "app_util/uli/uli_custom.h"

#include "wfrrc_interface.h"

#define NAV_UPDATER_TOGGLE_DUAL_BANK_AT_COMPLETED_ALL

#include "u_sys_name.h"
#include "u_fm.h"
#include "res/nav/nav_dbg.h"

#include <sys/ipc.h>
#include <sys/msg.h>

#include "rest/a_rest_event.h"
#ifdef APP_ZOOM_MODE_SUPPORT
#include "app_util/a_zoom_mode.h"
#endif
#include "menu2/menu.h"
// refer to mtk_util/mtk_indicator/mtk_indicator.h
#if 0
#define INDICATOR_MSG_PATH_MAX_LEN  (256)
#define INDICATOR_MSG_STR_MAX_LEN   (128)
#define INDICATOR_MSG_RECEIVE_ID    (50118)

typedef enum
{
    INDICATOR_MSG_UNKNOWN = 0,
    INDICATOR_MSG_INIT,
    INDICATOR_MSG_EXIT,
    INDICATOR_MSG_LOADING_SHOW = 10,
    INDICATOR_MSG_LOADING_HIDE,
    INDICATOR_MSG_SPLASH_SHOW = 20,
    INDICATOR_MSG_SPLASH_HIDE
}INDICATOR_MSG_TYPE;

typedef struct _INDICATOR_LOADING
{
    int  iconNum;
    char iconDirPath[INDICATOR_MSG_PATH_MAX_LEN];
    char msgString[INDICATOR_MSG_STR_MAX_LEN];
} INDICATOR_LOADING;

typedef struct _INDICATOR_SPLASH
{
    int  bgColor; /* hex color, eg. #020304 */
    char iconPath[INDICATOR_MSG_PATH_MAX_LEN];
    char msgString[INDICATOR_MSG_STR_MAX_LEN];
} INDICATOR_SPLASH;

typedef struct _INDICATOR_MSG
{
    long msgType;
    int  msgPacketIconNum;
    char msgPacketIconDirPath[INDICATOR_MSG_PATH_MAX_LEN];
    char msgPacketString[INDICATOR_MSG_STR_MAX_LEN];
}INDICATOR_MSG;
#endif
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 -----------------------------------------------------------------------------*/

#define ABS(x)                                      (((x) > 0) ? (x) : (-(x)))

/* The maximum updater log length is 511 characters. */
#define MAX_UPDATER_LOG_LEN (512)
#define UPDATER_TEST_LOG_FNAME    "/data/Updater_Log/updater_test.log"
#define UPDATER_TEST_LOG_FDIR     "/data/Updater_Log"

#define UPDATER_OPERA_CA_TAG_NAME     "opCA"
#define UPDATER_OPERA_CA_FDIR     "/data/opera/opera_home"

#define NAV_UPDATE_CAST_CERT_KEY_NAME     "/data/factory/mediatek_tv_dev_test_chain.pem"
#define NAV_UPDATE_CAST_KEY_NAME          "/data/factory/mediatek_tv_dev_test.key.pem"
#define NAV_UPDATE_CAST_KEY_PATH          "/data/factory"
#define GET_MQD_LOADING "/dtv_indicator"

#if 0
#define WIFI_REMOTE_SOFTWARE_OZMO_FNAME    "/3rd_rw/ozmo_sw/OZ20A___.OTA"
#define WIFI_REMOTE_SOFTWARE_OZMO_VER_INFO_FNAME     "/3rd_rw/ozmo_sw/ozmo_sw_ver_info"
#define WIFI_REMOTE_OZMO_SOFTWARE_FDIR     "/3rd_rw/ozmo_sw"
#endif


typedef enum
{
    START_FROM_FOLDER_INIT      = 0,
    START_FROM_FOLDER_A         = 1,
    START_FROM_FOLDER_B         = 2,
    DUAL_FOLDER_NOT_SUPPORTED   = 3
} UPDATER_DUAL_IMAGE_START_TYPE;

#define  NAV_UPDATE_DOWNLOAD_CHECK_TIMER_DURATION           4000

#define  NAV_UPDATE_DELAY_FIRMWARE_CHECK_TIMER_DURATION           3000

#define  NAV_UPDATE_FIRMWARE_NO_AVALIABLE_HIDE_TIMER_DURATION           5000
#define  NAV_UPDATE_WAITTING_FEEDBACK_TIMER_DURATION           1000
#define  NAV_UPDATER_CHECK_QDA_INIT_TIMER_DURATION           5000


/*-----------------------------------------------------------------------------
                    variable declarations
 -----------------------------------------------------------------------------*/

UPDATER_CTRL_T    t_g_updater_ctrl;

static  BOOL                             b_g_is_loading_page_show = FALSE;
static  BOOL                             b_g_dual_basic_enable = FALSE;
static  UPDATER_DUAL_IMAGE_START_TYPE    e_g_basic_start = START_FROM_FOLDER_INIT;
static  BOOL                             b_g_clean_bs_files = FALSE;

static  BOOL                             b_g_dual_3rd_enable = FALSE;
static  UPDATER_DUAL_IMAGE_START_TYPE    e_g_3rd_start   = START_FROM_FOLDER_INIT;
static  BOOL                             b_g_clean_3rd_files = FALSE;

static  BOOL                             b_g_is_rebooting = FALSE;
static  BOOL                             b_g_is_show_updater_completed = FALSE;


static   BOOL     b_s_is_need_dev_db_check    = FALSE;



#ifdef NAV_UPDATER_TOGGLE_DUAL_BANK_AT_COMPLETED_ALL
static  BOOL                             b_g_tar_basic_ok = FALSE;
static  BOOL                             b_g_tar_3rd_ok = FALSE;
#endif

static  UINT32           aui4_evtcode_arr_ex[3] = {0};
static  BOOL             b_g_power_key_iom_locked = FALSE;
static  BOOL             b_g_power_on_from_bgm = FALSE;


static  BOOL             b_g_query_sys_time_create = FALSE;
static  BOOL             b_g_loop_test_time_create = FALSE;
static  UINT32           ui4_g_loop_test_num = 0;

static  UINT32           ui4_g_query_num = 0;
HANDLE_T                 h_check_qda_init_timer = NULL_HANDLE;
HANDLE_T                 h_query_sys_timer = NULL_HANDLE;
HANDLE_T                 h_loop_test_timer = NULL_HANDLE;
static  UINT32           aui4_evtcode_ignore_arr_ex[35] = {0};
static  BOOL             b_all_key_disable = FALSE;
static  UINT32           ui4_waiting_check_update_timeount = 0;//This flag will remain timeout as
#if 0
static  HANDLE_T         h_iom;
#endif

static CHAR s_updater_log_message[ MAX_UPDATER_LOG_LEN + 8];
static CHAR s_updater_log[ MAX_UPDATER_LOG_LEN  * 2 ];

static  BOOL b_g_reboot_after_oobe_update = FALSE;
BOOL b_g_reboot_after_oobe_update_complete = FALSE;
static  BOOL b_nav_update_log_enable = FALSE;

/*-----------------------------------------------------------------------------
                    extern methods declarations
 -----------------------------------------------------------------------------*/

extern INT32 x_fm_delete_entry(
    HANDLE_T        h_dir,
    const CHAR      *ps_path,
    UINT32          ui4_mode);

extern VOID nav_updater_cfg_init(
    VOID
);

extern INT32 nav_updater_cfg_get_dual_bank_type_by_tag(
    CHAR*                    ps_tag,
    PCL_DUAL_BANK_TYPE_T*    pt_type
);

#ifdef MTK_CAMERA_DPTZ_SUPPORT
extern INT32 nav_updater_isp_upgrade_firmware(VOID);
#endif

/*-----------------------------------------------------------------------------
                    private methods declarations
 -----------------------------------------------------------------------------*/

static VOID _nav_updater_req_agent_upgrade(
    VOID*     pv_data,
    SIZE_T    z_data_len
);

static INT32 _nav_updater_cnd_chg(
    UPDATER_COND_T     e_cond
);

static BOOL _nav_updater_is_rebooting_system(VOID);

/* Dual folder Common */
static INT32 _nav_updater_dual_folder_init(VOID);
static INT32 _nav_updater_decompress_tgz_file(UINT32 ui4_item_idx);
/* For Basic dual folder */
static BOOL  _nav_updater_is_dual_basic_supported(VOID);
static INT32 _nav_updater_query_basic_start_from(VOID);
static INT32 _nav_updater_create_expire_file_in_basic(VOID);
static INT32 _nav_updater_get_next_basic_folder(CHAR *psz_folder_name, INT32 i4_len);
static INT32 _nav_updater_check_basic_folder(VOID);
/* For 3rd dual folder */
static BOOL  _nav_updater_is_dual_3rd_supported(VOID);
static INT32 _nav_updater_query_3rd_start_from(VOID);
static INT32 _nav_updater_check_3rd_folder(VOID);
static INT32 _nav_updater_create_expire_file_in_3rd(VOID);
static INT32 _nav_updater_get_next_3rd_folder(CHAR *psz_folder_name, INT32 i4_len);

static INT32 _nav_updater_set_complete_flag(VOID);
static INT32 _nav_updater_get_complete_flag(VOID);

static INT32 _nav_updater_set_old_fw_version(VOID);
static INT32 _nav_dev_db_query_sys_time_reset(VOID);
static VOID _nav_update_stop_download_check_timer(VOID);
static VOID _nav_update_delay_firmware_check_timeout_to_check(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
VOID nav_update_reset_delay_firmware_check_timer(VOID);
static VOID _nav_update_firmware_check_result_wait_feelback_fct(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );

static VOID _nav_update_firmware_check_result_wait_feelback(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    );
static VOID nav_update_reset_firmware_waitting_feedback_timer(VOID);
static VOID _nav_update_firmware_waitting_feedback_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    );
static VOID _nav_update_stop_firmware_waitting_feedback_timer(VOID);
static INT32 nav_updater_loop_test_timer_reset(VOID);
static VOID _nav_stop_loop_test_timer(VOID);

static VOID nav_update_check_drmp_waitting_qda_init_timer();
static VOID _nav_update_waitting_qda_init_timer_nty(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    );
static VOID _nav_update_check_drmp_waitting_qda_init();
#if 0
static VOID _iom_nfy_fct (VOID*             pv_nfy_tag,
                          IOM_NFY_COND_T    e_nfy_cond,
                          UINT32            ui4_evt_code,
                          UINT32            ui4_data);
#endif

/*This function is used to show loading page.*/
INT32 nav_loading_page_show(VOID);
/*This function is used to hide loading page.*/
INT32 nav_loading_page_hide(VOID);


/*-----------------------------------------------------------------------------
                    private methods implementation
 -----------------------------------------------------------------------------*/
#ifdef APP_BASIC_RO
static BOOL b_g_is_rw_basic = FALSE;
static BOOL b_g_is_rw_3rd   = FALSE;

INT32 nav_updater_remount_rw(NAV_UPDATER_REMOUNT_TYPE_T e_type)
{
    INT32 i4_ret = NAVR_FAIL;
    CHAR  s_path[60];

    if (UPDATER_REMOUNT_TYPE_BASIC == e_type)
    {
        c_strcpy(s_path, UPDATER_BASIC_FOLDER_PATH);
    }
    else if (UPDATER_REMOUNT_TYPE_3RD == e_type)
    {
        c_strcpy(s_path, UPDATER_3RD_FOLDER_PATH);
    }
    else
    {
        return NAVR_INV_ARG;
    }

    if (UPDATER_REMOUNT_TYPE_BASIC == e_type)
    {
        if (b_g_is_rw_basic)
        {
            return NAVR_NO_ACTION;
        }
        b_g_is_rw_basic = TRUE;
    }
    else if (UPDATER_REMOUNT_TYPE_3RD == e_type)
    {
        if (b_g_is_rw_3rd)
        {
            return NAVR_NO_ACTION;
        }
        b_g_is_rw_3rd = TRUE;
    }
    else
    {
        return NAVR_INV_ARG;
    }

    i4_ret = c_fm_remount_fs_rw(s_path);
    if (i4_ret != FMR_OK)
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"c_fm_remount_fs_rw: '%s' fails, i4_ret=%d \n", s_path, i4_ret));
        return NAVR_FAIL;
    }

    DBG_INFO((NAV_UPDATER_PREFIX"c_fm_remount_fs_rw: '%s' ok \n", s_path));

    return NAVR_OK;
}

INT32 nav_updater_remount_ro(NAV_UPDATER_REMOUNT_TYPE_T e_type)
{
    INT32 i4_ret = NAVR_FAIL;
    CHAR  s_path[60];

    if (UPDATER_REMOUNT_TYPE_BASIC == e_type)
    {
        c_strcpy(s_path, UPDATER_BASIC_FOLDER_PATH);
    }
    else if (UPDATER_REMOUNT_TYPE_3RD == e_type)
    {
        c_strcpy(s_path, UPDATER_3RD_FOLDER_PATH);
    }
    else
    {
        return NAVR_INV_ARG;
    }

    if (UPDATER_REMOUNT_TYPE_BASIC == e_type)
    {
        if (!b_g_is_rw_basic)
        {
            return NAVR_NO_ACTION;
        }
        b_g_is_rw_basic = FALSE;
    }
    else if (UPDATER_REMOUNT_TYPE_3RD == e_type)
    {
        if (!b_g_is_rw_3rd)
        {
            return NAVR_NO_ACTION;
        }
        b_g_is_rw_3rd = FALSE;
    }
    else
    {
        return NAVR_INV_ARG;
    }

    i4_ret = c_fm_remount_fs_ro(s_path);
    if (i4_ret != FMR_OK)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_fm_remount_fs_ro: '%s' fails, i4_ret=%d \n", s_path, i4_ret));
        return NAVR_FAIL;
    }

    NAV_UPGRADE_LOG_PRINT(NAV_UPDATER_PREFIX"c_fm_remount_fs_ro: '%s' ok \n", s_path);

    return NAVR_OK;
}
#endif
static VOID _nav_updater_progress_trigger_update_directly(
    VOID*              pv_tag1,
    VOID*              pv_tag2,
    VOID*              pv_tag3
)
{
    UINT8 ui1_fw_status_ex = 0;
    a_nav_updater_download_firmware_and_trigger_update_directly(&ui1_fw_status_ex);
}

static VOID _nav_updater_progress_trigger_usb_update_directly(
    VOID*              pv_tag1,
    VOID*              pv_tag2,
    VOID*              pv_tag3
)
{
    UINT8 ui1_fw_status_ex = 0;
    a_nav_updater_usb_download_firmware_and_trigger_update_directly(&ui1_fw_status_ex);
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_is_bgm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_preprocess_cb(
    BOOL                     b_success,
    UPDATER_EXIT_REASON_T    e_reason
)
{
    UPDATER_CTRL_T*          pt_this = &t_g_updater_ctrl;
    NAV_UPDATER_TRIGGER_TYPE_T   e_trigger_type = TRIGGER_TYPE_NONE;
    NAV_UPDATER_FW_STATE_T         e_fw_avaliable_state = CHECK_STATE_NONE;

	NAV_UPDATER_FW_STATE_T	e_fw_state = CHECK_STATE_NONE;

    nav_updater_uli_get_trigger_type(&e_trigger_type);

    if (TRUE != b_success)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_preprocess_cb: UPDATER_COND_EXIT\n"));
        pt_this->e_exit_reason = e_reason;
       	if(e_reason == UPDATER_EXIT_REASON_DOWNLOAD_FAIL)
		{
			_nav_updater_cnd_chg(UPDATER_COND_FAILED);
		}
		else
		{
       		_nav_updater_cnd_chg(UPDATER_COND_EXIT);
		}
    }
    else
    {
        if ((TRIGGER_TYPE_ULI_NETWORK_FW_CHECK == e_trigger_type)
            || (TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD == e_trigger_type)
            || (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE == e_trigger_type))
        {
             /* this case just for fw check or download*/
             NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_preprocess_cb: CHG UPDATER_COND_INIT [Just for FW Check or download]\n"));

             /* rollback to normal */
             _nav_updater_cnd_chg(UPDATER_COND_INIT);

             /* change the component visibility state */
             nav_hide_component(NAV_COMP_ID_UPDATER);

             pt_this->b_is_abort = TRUE;
             nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);
             if ((CHECK_STATE_CHECK_AVALIABLE == e_fw_avaliable_state) && (e_trigger_type == TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE))

             {
                nav_request_context_switch(_nav_updater_progress_trigger_update_directly,NULL,NULL,NULL);
             }
        }
		else if(TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM == e_trigger_type)
		{
			NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_preprocess_cb: CHG UPDATER_COND_INIT [Just for FW Check or download]\n"));

             /* rollback to normal */
             _nav_updater_cnd_chg(UPDATER_COND_INIT);

             /* change the component visibility state */
             nav_hide_component(NAV_COMP_ID_UPDATER);

             pt_this->b_is_abort = TRUE;
             nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);
             if (CHECK_STATE_CHECK_AVALIABLE == e_fw_avaliable_state&&e_trigger_type == TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM)

             {
                nav_request_context_switch(_nav_updater_progress_trigger_usb_update_directly,NULL,NULL,NULL);
             }
		}
		else if ((TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)&&
			    (a_nav_updater_uli_get_usb_upgrade_type() == UPDATER_USB_TYPE_CMD))
		{
			nav_updater_uli_get_fw_status(&e_fw_state);
			 if (CHECK_STATE_DOWNLOAD_SUCESS == e_fw_state)

             {
                nav_request_context_switch(_nav_updater_progress_trigger_usb_update_directly,NULL,NULL,NULL);
				a_cfg_cust_led_blinking_start(2);
				NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_preprocess_cb: LED 300ms \n"));
             }
		}
        else
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_preprocess_cb: UPDATER_COND_VALIDATING\n"));
        _nav_updater_cnd_chg(UPDATER_COND_VALIDATING);
    }
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_is_bgm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_is_bgm(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    return (pt_this->b_is_bgm);
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_disable_module
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_disable_module(
    VOID
)
{
#ifdef APP_EAS_SUPPORT
    a_eas_pause();
#endif

#ifdef APP_NAV_PWR_SUPPORT
    a_nav_power_set_component_enable(FALSE);
#endif

#ifdef APP_NAV_SCART_MONITOR
    a_nav_scart_monitor_set_all_detection(FALSE);
#endif

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_disable_module\n"));

    return NAVR_OK;
}

VOID nav_updater_turn_screen(BOOL b_on)
{
    SM_COMMAND_T            at_scc_cmds [4];

    /* Turn on backlight & LVDS */
    at_scc_cmds [0].e_code      = SCC_CMD_CODE_GRP_TYPE;
    at_scc_cmds [0].u.ui4_data  = SCC_CMD_TYPE_DISP;
    at_scc_cmds [1].e_code      = SCC_CMD_CODE_NAME;
    at_scc_cmds [1].u.ps_text   = SN_PRES_MAIN_DISPLAY;
    at_scc_cmds [2].e_code      = SCC_CMD_CODE_DISP_CTRL;
    at_scc_cmds [2].u.ui4_data  = b_on == TRUE ? SCC_DISP_CTRL_ENABLE : SCC_DISP_CTRL_DISABLE;
    at_scc_cmds [3].e_code      = SM_CMD_CODE_END;
    c_scc_comp_grp_set (at_scc_cmds);
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_enable_module
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_enable_module(
    VOID
)
{
    if (_nav_updater_is_rebooting_system())
    {
        return NAVR_OK;
    }

#ifdef APP_EAS_SUPPORT
    a_eas_resume();
#endif

#ifdef APP_NAV_PWR_SUPPORT
    a_nav_power_set_component_enable(TRUE);
#endif

#ifdef APP_NAV_SCART_MONITOR
    a_nav_scart_monitor_set_all_detection(TRUE);
#endif

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_enable_module\n"));

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_is_break_in_avail
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_is_break_in_avail(
    VOID
)
{
    INT32     i4_ret     = 0;
    UINT8     ui1_status = 0;
    SIZE_T    t_size     = sizeof(UINT8);
    BOOL      b_avail    = FALSE;

    do {
        i4_ret = a_icl_get(
                      (ICL_ID_TYPE)ICL_MAKE_ID(ICL_GRPID_OAD, ICL_RECID_OAD_STATUS),
                      (VOID*) &ui1_status,
                      &t_size);

        if (ICLR_OK != i4_ret)
        {
            break;
        }

        if (ICL_OAD_STATUS_NONE != ui1_status)
        {
            break;
        }

        b_avail = TRUE;
    } while (0);

    return b_avail;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_is_waiting_app_exit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static BOOL _nav_updater_is_waiting_app_exit(
    VOID
)
{
    CHAR     s_app_name[APP_NAME_MAX_LEN + 1] = {'\0'};
    INT32    i4_ret = 0;

    i4_ret = a_am_get_active_app(s_app_name);
    if (AMBR_OK != i4_ret)
    {
        return TRUE;
    }

    if (c_strcmp(WZD_NAME, (const CHAR*)s_app_name) == 0)
    {
        return FALSE;
    }

    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_progress_update_hdlr
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_progress_update_hdlr(
    VOID*              pv_tag1,
    VOID*              pv_tag2,
    VOID*              pv_tag3
)
{
    UPDATER_CTRL_T*    pt_this      = &t_g_updater_ctrl;
    INT32              i4_prog_crnt = (INT32)pv_tag1;
    INT32              i4_item_prog;

    i4_item_prog = (100-6)/pt_this->t_upg_fw_info.ui4_item_num;

    i4_prog_crnt = ((i4_prog_crnt * i4_item_prog)/100) + (pt_this->ui4_upg_done_item_num  * i4_item_prog);
    i4_prog_crnt = i4_prog_crnt + 6;

    pt_this->ui1_progress = (UINT8)(i4_prog_crnt);
    if (pt_this->ui1_progress > 100)
    {
        pt_this->ui1_progress = 100;
    }

    pt_this->t_updater_view_hdlr.pf_update_progress(UPDATER_UPDATE_REASON_PROGRESS);
}

#ifdef NAV_UPDATER_TOGGLE_DUAL_BANK_AT_COMPLETED_ALL
#if 0
static VOID _nav_updater_toggle_dual_bank(VOID)
{
    UPDATER_CTRL_T*         pt_this = &t_g_updater_ctrl;
    UPDATER_ITEM_T*         pt_upg_item;
    UINT32                  ui4_idx;
    PCL_DUAL_BANK_TYPE_T    e_dual_bank;
    INT32                   i4_ret;
    INT32                   i4_ret_tmp = 0;
     UINT8                  ui1_bank_idx = 0;

    for (ui4_idx = 0; ui4_idx < pt_this->t_upg_fw_info.ui4_item_num; ui4_idx++)
    {
        /* get upgrade item info */
        pt_upg_item = &(pt_this->t_upg_fw_info.pt_item[ui4_idx]);

        if ((pt_upg_item->ui4_flag & UPDATER_ITEM_FLAG_DUAL_BANK) &&
            (pt_upg_item->ui4_flag & UPDATER_ITEM_FLAG_SELECTED))
        {
            i4_ret = nav_updater_cfg_get_dual_bank_type_by_tag((CHAR *)pt_upg_item->s_tag, &e_dual_bank);

            i4_ret_tmp = c_pcl_get_dual_bank_index(e_dual_bank, &ui1_bank_idx);

            if (NAVR_OK == i4_ret)
            {
                /* upgrade all tags done, so toggle the dual bank index */
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[START] Toggle the bank for tag %s!!\n", pt_upg_item->s_tag));
                updater_log_printf(NAV_UPDATER_PREFIX"[Before] Toggle the bank for tag %s,bank index is:%d,return_value is:%d!!\n", pt_upg_item->s_tag,ui1_bank_idx,i4_ret_tmp);
                updater_log_printf(NAV_UPDATER_PREFIX"[START] Toggle the bank for tag %s!!\n", pt_upg_item->s_tag);

                i4_ret = c_pcl_toggle_dual_bank_index(e_dual_bank);
                if (i4_ret == PCLR_OK)
                {

                    i4_ret_tmp = c_pcl_get_dual_bank_index(e_dual_bank, &ui1_bank_idx);
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[END] Toggle the bank for tag %s success,i4_ret = %d\n", pt_upg_item->s_tag, i4_ret));
                    updater_log_printf(NAV_UPDATER_PREFIX"[END] Toggle the bank for tag %s success,i4_ret = %d\n", pt_upg_item->s_tag, i4_ret);
                    updater_log_printf(NAV_UPDATER_PREFIX"[After] Toggle the bank for tag %s,bank index is:%d,return_value is:%d!!\n", pt_upg_item->s_tag,ui1_bank_idx,i4_ret_tmp);

                }
                else
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[END] Toggle the bank for tag %s fail,i4_ret = %d\n", pt_upg_item->s_tag, i4_ret));
                    updater_log_printf(NAV_UPDATER_PREFIX"[END] Toggle the bank for tag %s fail,i4_ret = %d\n", pt_upg_item->s_tag, i4_ret);

                }
            }
        }
    }
}
#endif
static VOID _nav_updater_toggle_dual_bank_by_mask(VOID)
{
    UPDATER_CTRL_T*         pt_this = &t_g_updater_ctrl;
    UPDATER_ITEM_T*         pt_upg_item;
    UINT32                  ui4_idx;
    //PCL_DUAL_BANK_TYPE_T    e_dual_bank;
    INT32                   i4_ret;
    UINT32                  ui4_bank_mask = 0;
#if 0
    for (ui4_idx = 0; ui4_idx < pt_this->t_upg_fw_info.ui4_item_num; ui4_idx++)
    {
        /* get upgrade item info */
        pt_upg_item = &(pt_this->t_upg_fw_info.pt_item[ui4_idx]);

        if ((pt_upg_item->ui4_flag & UPDATER_ITEM_FLAG_DUAL_BANK) &&
            (pt_upg_item->ui4_flag & UPDATER_ITEM_FLAG_SELECTED))
        {
            if(c_strncmp(pt_upg_item->s_tag, UPDATER_SIGNATURE_TAG_NAME, UPDATER_TAG_NAME_LEN) == 0 ||
               c_strncmp(pt_upg_item->s_tag, UPDATER_KERNEL_TAG_NAME, UPDATER_TAG_NAME_LEN) == 0)
            {
                ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_KERNEL;

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag));
                updater_log_printf(NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag);
            }
            else if(c_strncmp(pt_upg_item->s_tag, UPDATER_ROOTFS_TAG_NAME, UPDATER_TAG_NAME_LEN) == 0)
            {
                ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_LINUX_ROOTFS;
				ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_KERNEL;
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag));
                updater_log_printf(NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag);
            }
            else if(c_strncmp(pt_upg_item->s_tag, UPDATER_3RD_TAG_NAME, UPDATER_TAG_NAME_LEN) == 0)
            {
                ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_3RD;

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag));
                updater_log_printf(NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag);
            }
            else if(c_strncmp(pt_upg_item->s_tag, UPDATER_SYSTEM_TAG_NAME, UPDATER_TAG_NAME_LEN) == 0)
            {
                ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_CAST_SYSTEM;

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag));
                updater_log_printf(NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag);
            }
            else if(c_strncmp(pt_upg_item->s_tag, UPDATER_CHROME_TAG_NAME, UPDATER_TAG_NAME_LEN) == 0)
            {
                ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_CHROME;

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag));
                updater_log_printf(NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag);
            }
            else if(c_strncmp(pt_upg_item->s_tag, UPDATER_LINUX_ROOTFS_TAG_NAME, UPDATER_TAG_NAME_LEN) == 0)
            {
                ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_LINUX_ROOTFS;
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag));
                updater_log_printf(NAV_UPDATER_PREFIX"[will] Toggle bank s_tag[%s]\n",pt_upg_item->s_tag);
            }
            else
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Can not toggle bank for %s\n", pt_upg_item->s_tag));
            }
        }
    }
#else

    ui4_bank_mask |= PCL_MISC_CTRL_DUAL_BANK_ROOTFS;
#endif


    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[START] Toggle bank [BEG]\n"));
    /* upgrade all tags done, so toggle the dual bank index */
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[nav_updater.c %s %d][START] Toggle dual bank PCL_MISC_CTRL_DUAL_BANK_ROOTFS\n", __func__, __LINE__));

    i4_ret = c_pcl_toggle_dual_bank_by_mask(ui4_bank_mask);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[START] Toggle bank [END] i4_ret[%d]\n",i4_ret));
    updater_log_printf(NAV_UPDATER_PREFIX"[START] Toggle bank [END] i4_ret[%d]\n",i4_ret);
    if (i4_ret == PCLR_OK)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[END] Toggle dual bank %x success,i4_ret = %d\n", ui4_bank_mask, i4_ret));
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[END] Toggle dual bank %x fail,i4_ret = %d\n", ui4_bank_mask, i4_ret));
    }
}

#endif

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_progress_complete
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_progress_complete(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    UPDATER_CTRL_T*         pt_this = &t_g_updater_ctrl;
    UINT32                  ui4_idx = pt_this->ui4_crnt_upg_item_idx;
    UPDATER_ITEM_T*         pt_upg_item;
#ifndef NAV_UPDATER_TOGGLE_DUAL_BANK_AT_COMPLETED_ALL
    PCL_DUAL_BANK_TYPE_T    e_dual_bank;
#endif
    INT32                   i4_ret;

    /* get current upgrade item */
    pt_upg_item =
        &(pt_this->t_upg_fw_info.pt_item[ui4_idx]);

    if (UPDATER_ITEM_COND_UPDATED == pt_upg_item->e_cond)
    {
#ifndef NAV_UPDATER_TOGGLE_DUAL_BANK_AT_COMPLETED_ALL
        if (pt_upg_item->ui4_flag & UPDATER_ITEM_FLAG_DUAL_BANK)
        {
            i4_ret = nav_updater_cfg_get_dual_bank_type_by_tag((CHAR *)pt_upg_item->s_tag, &e_dual_bank);

            if (NAVR_OK == i4_ret)
            {
                /* upgrade done, so toggle the dual bank index */
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Toggle the bank for tag %s!!\n", pt_upg_item->s_tag));

                c_pcl_toggle_dual_bank_index(e_dual_bank);
            }
        }
#endif
        i4_ret = _nav_updater_cnd_chg(UPDATER_COND_COMPLETE_ONE);

        if (NAVR_NOT_ALLOW != i4_ret)
        {
            if (pt_this->ui4_crnt_upg_item_idx < pt_this->t_upg_fw_info.ui4_item_num)
            {
                _nav_updater_cnd_chg(UPDATER_COND_DOWNLOADING);
                a_agent_async_invoke(_nav_updater_req_agent_upgrade, NULL, 0);
            }
            else
            {
                _nav_updater_cnd_chg(UPDATER_COND_COMPLETE);
            }
        }
    }
    else
    {
        _nav_updater_cnd_chg(UPDATER_COND_FAILED);
    }
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_progress_update_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_progress_update_nfy(
    INT32           i4_percentage
)
{
    static INT32    i4_prog_prev = 0xFF;

    if ((ABS((i4_percentage - i4_prog_prev)) >= 10) || (100 == i4_percentage))
    {
        i4_prog_prev = i4_percentage;

        nav_request_context_switch(
                            _nav_updater_progress_update_hdlr,
                            (VOID*)i4_percentage,
                            NULL,
                            NULL);
    }

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_item_cnd_chg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_item_cnd_chg(
    VOID*                  pv_tag1,
    VOID*                  pv_tag2,
    VOID*                  pv_tag3
)
{
    UINT32                 ui4_idx = (UINT32)pv_tag1;
    UPDATER_ITEM_COND_T    e_cond  = (UPDATER_ITEM_COND_T)pv_tag2;

    UPDATER_CTRL_T*        pt_this = &t_g_updater_ctrl;

    /* update the item condition */
    pt_this->t_upg_fw_info.pt_item[ui4_idx].e_cond = e_cond;

    return;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_updater_req_agent_reboot
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_req_agent_reboot(
    VOID*                 pv_data,
    SIZE_T                z_data_len
)
{
	if (a_am_is_power_on())
	{
		a_cfg_custom_service_reset(1,TRUE);
	}
	else
	{
		a_cfg_custom_set_drv_bgmupdate_flag(1);
		c_pcl_set_reboot ();
	}

    a_amb_reboot();
}

/*-----------------------------------------------------------------------------
 * Name: nav_updater_reboot_system_ex
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/


INT32 nav_updater_reboot_system_ex(VOID)
{
    b_g_is_rebooting = TRUE;
	a_uli_qda_term();
#ifdef APP_BASIC_RO
    nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_BASIC);
    /* nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_3RD); */
#endif
    /* delay 3s */
    c_thread_delay(3000);

    DBG_LOG_PRINT((NAV_UPDATER_PREFIX"%s, call /application/vzservices/bin/fwupdate_reboot.sh\n", __FUNCTION__));
    AP_SYSTEM_CALL("/application/vzservices/bin/fwupdate_reboot.sh");//[2020-6-8][DTV02207969] execute fwupdate_reboot.sh script provided by Vizio.

    a_agent_async_invoke(_nav_updater_req_agent_reboot, NULL, 0);

    return NAVR_OK;
}

static INT32 _nav_updater_upgrade_pre_handle(UPDATER_ITEM_T* pt_upg_item)
{
    INT32       i4_ret;
    UINT16      ui2_unit = 0;
    UINT32      ui4_mode;
    DRV_TYPE_T  t_drv_type;

extern INT32 x_fm_delete_entry(
    HANDLE_T        h_dir,
    const CHAR      *ps_path,
    UINT32          ui4_mode);

#ifndef APP_CFG_NOR_PATH
#ifndef SYS_EMMC_SUPPORT
    t_drv_type = DRVT_NAND_FLASH;
#else
    t_drv_type = DRVT_EMMC;
#endif
    ui4_mode   = FM_MODE_TYPE_BLK;
#else
    t_drv_type = DRVT_NOR_FLASH;
    ui4_mode   = FM_MODE_TYPE_CHR;
#endif

    if (!pt_upg_item)
    {
        return NAVR_INV_ARG;
    }

    DBG_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_upgrade_pre_handle t_drv_type: %d\n", (INT32)t_drv_type));

#ifndef AP_UPGRADE_BIN_FMT_SUPPORT
    if (pt_upg_item->ui4_flag & UPDATER_ITEM_FLAG_DUAL_BANK)
#else
    if (1) /* Always do this operation for Bin Fmt Support */
#endif
    {
        /* Delete virtual device */
        i4_ret = x_fm_delete_entry(FM_ROOT_HANDLE, pt_upg_item->s_dev_path, (ui4_mode | 0666));
        if(FMR_OK != i4_ret)
        {
            DBG_LOG_PRINT((NAV_UPDATER_PREFIX"%s,  x_fm_delete_entry=%s, i4_ret=%d \n", __FUNCTION__, pt_upg_item->s_dev_path, i4_ret));
#ifndef AP_UPGRADE_BIN_FMT_SUPPORT
            return i4_ret;
#else
            /* do nothing */
#endif
        }

        /* Make true device */
        ui2_unit = pt_upg_item->ui1_part_id;
        i4_ret = c_fm_make_entry (FM_ROOT_HANDLE, pt_upg_item->s_dev_path, (ui4_mode | FM_MODE_DEV_TRUE | 0666), t_drv_type, ui2_unit);
        if(FMR_OK != i4_ret)
        {
            DBG_LOG_PRINT((NAV_UPDATER_PREFIX"%s,  c_fm_make_entry=%s, i4_ret=%d \n", __FUNCTION__, pt_upg_item->s_dev_path, i4_ret));
            return i4_ret;
        }
    }
    else
    {
        if(c_strncmp(UPDATER_3RD_TAG_NAME, pt_upg_item->s_tag, UPDATER_TAG_NAME_LEN) == 0 &&
           pt_upg_item->e_method == UPDATER_METHOD_PART)
        {
            _nav_updater_3rd_single_part_pre_handle(pt_upg_item);
        }
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: _nav_updater_req_agent_upgrade
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_req_agent_upgrade(
    VOID*                 pv_data,
    SIZE_T                z_data_len
)
{
    INT32                 i4_ret;
    CHAR                  s_path[128] = {0};
    UINT32                ui4_size    = 128;

    UPDATER_CTRL_T*       pt_this = &t_g_updater_ctrl;
    UINT32                ui4_idx = pt_this->ui4_crnt_upg_item_idx;
    UPDATER_REG_ATTR_T    t_attr  = {0};
    UPDATER_ITEM_T*       pt_upg_item;
#if 0
    UINT16                ui2_unit = 0;
    UINT8                 ui1_bank_idx = 0;

    DRV_TYPE_T t_drv_type;
    UINT32        ui4_mode;

#ifndef APP_CFG_NOR_PATH
    #ifdef SYS_EMMC_SUPPORT
        t_drv_type = DRVT_EMMC;
    #else
        t_drv_type = DRVT_NAND_FLASH;
    #endif
    ui4_mode = FM_MODE_TYPE_BLK;
#else
    t_drv_type = DRVT_NOR_FLASH;
    ui4_mode = FM_MODE_TYPE_CHR;
#endif
#endif

#if 0
    UINT8                 ui1_ff_byte[16] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
                                       0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
#endif

    /* get current upgrade item */
    pt_upg_item =
        &(pt_this->t_upg_fw_info.pt_item[ui4_idx]);
	_nav_updater_upgrade_pre_handle(pt_upg_item);
    do
    {
        nav_request_context_switch(_nav_updater_item_cnd_chg,
                                   (VOID*)ui4_idx,
                                   (VOID*)UPDATER_ITEM_COND_RETRIEVING,
                                   NULL);

        /* retrieve data */
        i4_ret = pt_this->pt_curr_dlivry_hdlr->pf_get_fw(
                     pt_upg_item,
                    _nav_updater_progress_update_nfy);

        if(UPDATERR_OK != i4_ret)
        {
            nav_request_context_switch(_nav_updater_item_cnd_chg,
                                       (VOID*)ui4_idx,
                                       (VOID*)UPDATER_ITEM_COND_UPDATE_FAIL,
                                       NULL);

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Get FW failed!\n"));
            break;
        }

        /* update data */
        nav_request_context_switch(_nav_updater_item_cnd_chg,
                                   (VOID*)ui4_idx,
                                   (VOID*)UPDATER_ITEM_COND_UPDATING,
                                   NULL);

        /* fill data for t_attr */
        t_attr.ui4_reg_buff_size = UPDATER_DLM_BUFF_SZ;
        c_strcpy((CHAR *)t_attr.s_dev_path, (const CHAR *)pt_upg_item->s_dev_path);

        c_strncpy(t_attr.s_tag_name, pt_upg_item->s_tag, UPDATER_TAG_NAME_LEN);

        t_attr.e_method = pt_upg_item->e_method;

        i4_ret = a_fw_updater_reg(ui4_idx, &t_attr);

        if (UPDATERR_OK != i4_ret)
        {
            nav_request_context_switch(_nav_updater_item_cnd_chg,
                                       (VOID*)ui4_idx,
                                       (VOID*)UPDATER_ITEM_COND_UPDATE_FAIL,
                                       NULL);

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_fw_updater_reg() error\n"));

            break;
        }

        /* get the full path, ex. /mnt/usb/Mass-000/upgrade.pkg */
        i4_ret = pt_this->pt_curr_dlivry_hdlr->pf_get_path(
                    s_path,
                    (SIZE_T)ui4_size);

        if(NAVR_OK > i4_ret)
        {
            nav_request_context_switch(_nav_updater_item_cnd_chg,
                                       (VOID*)ui4_idx,
                                       (VOID*)UPDATER_ITEM_COND_UPDATE_FAIL,
                                       NULL);

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"get path fail error\n"));


            break;
        }

        /*as the 3rd is dual bank & the tvap will not update
          so the following mark will not need*/
#if 0
        /* umount tvap and 3rdp */
        if( (c_strcmp(t_attr.s_tag_name,"3rdp") == 0 )||(c_strcmp(t_attr.s_tag_name,"tvap") == 0 ))
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"t_attr.s_tag_name = %s\n",t_attr.s_tag_name));

            if(c_strcmp(t_attr.s_tag_name,"3rdp") == 0)
            {
                /* a_iptv_util_detach_and_unmount_3rd(); */
                system("sync;sync");

                i4_ret = c_fm_umount(FM_ROOT_HANDLE,  "/3rd");
                NAV_UPGRADE_LOG_PRINT(("c_fm_umount i4_ret = %d\n", i4_ret));

                /*
                system("/basic/detach_3rd.sh");
                */

                ui2_unit = APP_3RD_UPG_PATH;
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"3rdp ui2_unit[%d]\n",ui2_unit));
            }
            else if(c_strcmp(t_attr.s_tag_name,"tvap") == 0)
            {
                c_fm_umount(FM_ROOT_HANDLE,  "/basic");
                i4_ret = c_pcl_get_dual_bank_index(PCL_DUAL_BANK_ROOTFS, &ui1_bank_idx);
                NAV_UPGRADE_LOG_PRINT (("*******====nav_updater1 c_pcl_get_dual_bank_index return value=%d====****\n",i4_ret));

                if (PCLR_OK == i4_ret)
                {
                    /* 0->mtd9 or 1->mtd8*/
                    ui2_unit = (ui1_bank_idx == 0) ? 9 : 8 ;
                }
            }

            if(UPDATERR_OK != i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"i4_ret = %d\n",i4_ret));

                nav_request_context_switch(_nav_updater_item_cnd_chg,
                                    (VOID*)ui4_idx,
                                    (VOID*)UPDATER_ITEM_COND_UPDATE_FAIL,
                                    NULL);
                break;
            }

            i4_ret = x_fm_delete_entry(FM_ROOT_HANDLE, t_attr.s_dev_path, (ui4_mode | FM_MODE_DEV_VIRT | 0666));

            NAV_UPGRADE_LOG_PRINT(("*******====nav_updater2 x_fm_delete_entry return value=%d s_dev_path %s====****\n",i4_ret,t_attr.s_dev_path));

#if 0  //deal with if no this entry
            if(FMR_OK != i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"i4_ret = %d\n",i4_ret));
                nav_request_context_switch(_nav_updater_item_cnd_chg,
                                    (VOID*)ui4_idx,
                                    (VOID*)UPDATER_ITEM_COND_UPDATE_FAIL,
                                    NULL);
                break;
            }
#endif

            i4_ret = c_fm_make_entry (FM_ROOT_HANDLE, t_attr.s_dev_path, (ui4_mode | FM_MODE_DEV_TRUE | 0666), t_drv_type, ui2_unit);
            NAV_UPGRADE_LOG_PRINT(("*******====nav_updater3 x_fm_make_entry return value=%d====****\n",i4_ret));

            if(FMR_OK != i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"i4_ret = %d\n",i4_ret));

                nav_request_context_switch(_nav_updater_item_cnd_chg,
                                    (VOID*)ui4_idx,
                                    (VOID*)UPDATER_ITEM_COND_UPDATE_FAIL,
                                    NULL);
                break;
            }

        }
#endif
        i4_ret = a_fw_updater_download(
                    ui4_idx,
                    (i4_ret == NAVR_NO_ACTION) ? NULL : s_path,
                    pt_this->pt_curr_dlivry_hdlr->pt_io,
                    _nav_updater_progress_update_nfy,
                    NULL,
                    pt_this->pt_curr_dlivry_hdlr->b_division);

        a_fw_updater_unreg(ui4_idx);

        if (UPDATERR_TAG_NOT_EXIST == i4_ret)
        {
            if (pt_upg_item->ui4_flag & UPDATER_ITEM_FLAG_DUAL_BANK)
            {
                /* Don't toggle the dual bank index, becase this tag is not exist */
                pt_upg_item->ui4_flag &= ~UPDATER_ITEM_FLAG_DUAL_BANK;
            }

            /* If tag is not exist, would retry the next tag! */
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_fw_updater_download() tag '%s' not exist! \n", t_attr.s_tag_name));

        }

        if (UPDATERR_OK == i4_ret || UPDATERR_TAG_NOT_EXIST == i4_ret)
        {
            nav_request_context_switch(_nav_updater_item_cnd_chg,
                                       (VOID*)ui4_idx,
                                       (VOID*)UPDATER_ITEM_COND_UPDATED,
                                       NULL);

            i4_ret = a_fw_updater_close(ui4_idx);

            if (UPDATERR_OK != i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_fw_updater_close() failed\n"));

            }
        }
        else
        {
            nav_request_context_switch(_nav_updater_item_cnd_chg,
                                       (VOID*)ui4_idx,
                                       (VOID*)UPDATER_ITEM_COND_UPDATE_FAIL,
                                       NULL);

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_fw_updater_download() fail\n"));

        }

    }while(0);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Complete!!\n"));

    nav_request_context_switch(_nav_updater_progress_complete,
                               NULL,
                               NULL,
                               NULL);

    return;
}

static INT32 _nav_updater_stop_video(VOID)
{
    INT32              i4_ret;
    TV_WIN_ID_T        t_tv_win_id;
    HANDLE_T           h_svctx = NULL_HANDLE;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (FALSE == pt_this->b_is_svc_stop)
    {
        nav_get_focus_id(&t_tv_win_id);

        i4_ret = nav_get_svctx_handle(t_tv_win_id, &h_svctx);

        if (NAVR_OK != i4_ret)
        {
            return NAVR_FAIL;
        }


        i4_ret = c_svctx_sync_stop_svc(h_svctx, DEFAULT_STOP_SVC_TIMEOUT);

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_stop_video: i4_ret=%d\n", i4_ret));

        if (SVCTXR_ALREADY_STOPPED == i4_ret)
        {
            /* do nothing */
        }
        else if (SVCTXR_OK != i4_ret)
        {
            return NAVR_FAIL;
        }
        pt_this->b_is_svc_stop = TRUE;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_model_download
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_model_download(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
    BOOL               b_found;
    UINT32             ui4_idx;

    if((UPDATER_COND_INITED != pt_this->e_cond)
        && (UPDATER_COND_FAILED != pt_this->e_cond))
    {
        return NAVR_NOT_ALLOW;
    }
#ifdef APP_BASIC_RO
/*
    nav_updater_remount_rw(UPDATER_REMOUNT_TYPE_BASIC);
    nav_updater_remount_rw(UPDATER_REMOUNT_TYPE_3RD);
*/
#endif

    if (_nav_updater_is_dual_basic_supported())
    {
        b_g_clean_bs_files = FALSE;
    }

    if (_nav_updater_is_dual_3rd_supported())
    {
        b_g_clean_3rd_files = FALSE;
    }

    b_found = FALSE;

    /* decide the first upgrade index, only first time needed */
    if (0 == pt_this->ui4_upg_done_item_num)
    {
        for (ui4_idx = 0 ; ui4_idx < pt_this->t_upg_fw_info.ui4_item_num ; ui4_idx++)
        {
            if (pt_this->t_upg_fw_info.pt_item[ui4_idx].ui4_flag & UPDATER_ITEM_FLAG_SELECTED)
            {
                pt_this->ui4_crnt_upg_item_idx = ui4_idx;
                b_found = TRUE;
                break;
            }
        }
    }

    _nav_updater_stop_video();

    if ((TRUE == b_found) || (0 != pt_this->ui4_upg_done_item_num))
    {
        _nav_updater_cnd_chg(UPDATER_COND_DOWNLOADING);
        a_agent_async_invoke(_nav_updater_req_agent_upgrade, NULL, 0);
    }
    /* if not found => no item need to be upgraded */
    else
    {
        _nav_updater_cnd_chg(UPDATER_COND_COMPLETE);
    }

    return NAVR_OK;
}

static INT32 _nav_updater_sync_wzd_sys_upgrade_status(UINT8  ui1_value)
{
    UINT16 ui2_status = 0;

    /*check the wizard status*/
    if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK
                            && (WZD_UTIL_GET_STATUS_STATE(ui2_status) == WZD_STATE_RESUME_C4TV))
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_sync_wzd_sys_upgrade_status() ui1_value[%d]\n",
                ui1_value));

        a_cfg_cust_set_wzd_sys_upgrade_status(ui1_value);
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_updater_model_leave
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_model_leave(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    pt_this->b_is_leaving = TRUE;

    if ((UPDATER_COND_INITED == pt_this->e_cond)
        || (UPDATER_COND_EXIT == pt_this->e_cond))
    {
       /* rollback to normal */
        _nav_updater_cnd_chg(UPDATER_COND_INIT);

        /* change the component visibility state */
        nav_hide_component(NAV_COMP_ID_UPDATER);
    }
    else
    {
        _nav_updater_cnd_chg(UPDATER_COND_DEAD);
    }

    /* reset the flag*/
    nav_updater_uli_set_trigger_type(TRIGGER_TYPE_NONE);
    nav_updater_uli_set_update_stage(STAGE_NONE);
    nav_updater_uli_set_user_mode(USER_MODE_NONE);

    nav_updater_view_set_toast_process_bar_status(FALSE);

    pt_this->b_is_leaving = FALSE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_cnd_chg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_cnd_chg(
    UPDATER_COND_T     e_cond
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
    INT32              i4_ret  = UPDATERR_FAIL;
    UINT32             ui4_idx;
    BOOL               b_found;
    BOOL               b_is_file_base;

    BOOL               b_is_for_bgm_upgrade = FALSE;

    BOOL b_is_to_continue = FALSE;

    NAV_UPDATER_TRIGGER_TYPE_T  e_trigger_type = TRIGGER_TYPE_NONE;
	NAV_UPDATER_FW_STATE_T		e_fw_avaliable_state = CHECK_STATE_NONE;

    pt_this->e_cond = e_cond;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"%s is called to change e_cond = 0x%x, Abort? %s\n",
                    __FUNCTION__,
                    e_cond,
                    (TRUE == pt_this->b_is_abort) ? "YES" : "NO"));

    nav_updater_uli_get_trigger_type(&e_trigger_type);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_cnd_chg e_trigger_type[%d],\n",
        e_trigger_type));

    if (TRUE == pt_this->b_is_abort)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_cnd_chg Break[b_is_abort],\n",
            e_trigger_type));

        return NAVR_NOT_ALLOW;
    }

    if (FALSE == _nav_updater_is_bgm())
    {
        pt_this->t_updater_view_hdlr.pf_update_progress(UPDATER_UPDATE_REASON_COND);
    }

    switch (e_cond)
    {
        case UPDATER_COND_INIT:
            pt_this->b_is_updater_triggered = FALSE;
            pt_this->b_is_svc_stop = FALSE;

            _nav_update_stop_download_check_timer();

            a_fw_updater_cancel(pt_this->ui4_crnt_upg_item_idx);

            nav_updater_update_info((UINT8)UPDATER_STATUS_CLEAR);
			nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);

            a_tv_net_send_cmd(":dtv_app_mtk,am,:enable_PKWD\n");
            if (FALSE == _nav_updater_is_bgm())
            {
                if (FALSE == a_wzd_is_oobe_mode())
                {
                    // In OOBE, do not enable system keys
                    a_amb_enable_system_key(TRUE);
                }
                a_amb_enable_power_key(TRUE);

            }

/*
            a_fw_updater_cust_free_tag_buff();
*/
            if ((NULL != pt_this->pt_curr_dlivry_hdlr) &&
                (NULL != pt_this->pt_curr_dlivry_hdlr->pf_exit)&&
                (e_fw_avaliable_state != CHECK_STATE_CHECK_AVALIABLE))
            {
                pt_this->pt_curr_dlivry_hdlr->pf_exit(FALSE);
            }

            /* free XML tree */
            if (NULL != pt_this->pt_download_xml)
            {
                c_xml_free(pt_this->pt_download_xml);
                pt_this->pt_download_xml = NULL;
            }
#ifdef APP_PRE_UPG_CHK
            if (NULL != pt_this->pt_version_xml)
            {
                c_xml_free(pt_this->pt_version_xml);
                pt_this->pt_version_xml = NULL;
            }
#endif
            /* delete upg_download.xml because the whole upgrade process is not completed! */
            c_fm_delete_file(FM_ROOT_HANDLE, UPDATER_XML_PATH "/" UPDATER_UPG_XML_NAME);

            /* Flush file system buffers */
            sync();

            /* reset the flag*/
            nav_updater_uli_set_trigger_type(TRIGGER_TYPE_NONE);
            nav_updater_uli_set_update_stage(STAGE_NONE);
            nav_updater_uli_set_user_mode(USER_MODE_NONE);

//            nav_updater_view_set_toast_process_bar_status(FALSE);
            break;

        case UPDATER_COND_PREPROCESSING:
            if (FALSE == _nav_updater_is_bgm())
            {
                /* if BGM into Normal and it is ULI internet method update,
                   then don't need trigger update */
            #ifdef APP_ULI_UPG_SUPPORT
                if ((pt_this->pt_curr_dlivry_hdlr != NULL) &&
                    (UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type) &&
                    nav_updater_uli_is_intnt_method()
                    && (TRIGGER_TYPE_ULI_BGM_NETWORK_FW_DOWNLOAD_AND_INSTALL == e_trigger_type))
            #else
                if ((pt_this->pt_curr_dlivry_hdlr != NULL) &&
                    (UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type))
            #endif
                {
                    /*BGM Power on should stop the bgm update flow*/
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" don't need trigger ULI bgm update in normal condition!\n"));
                    pt_this->e_exit_reason = UPDATER_EXIT_REASON_CHECKING_UPDATE_FAIL;
                    _nav_updater_cnd_chg(UPDATER_COND_EXIT);
                    break;
                }
                else
                {
                    /* if this case is for fw install,
                       should disable the system key*/
                    if (TRIGGER_TYPE_ULI_NETWORK_FW_INSTALL == e_trigger_type)
                    {
                          NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" UPDATER_COND_PREPROCESSING [disable sys key] !\n"));
                          a_amb_enable_system_key(FALSE);
                          a_amb_enable_power_key(FALSE);
                    }
                }
            }

            if ((TRIGGER_TYPE_ULI_NETWORK_FW_INSTALL == e_trigger_type)
                || (TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)
                || (TRIGGER_TYPE_ULI_BGM_NETWORK_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)
                || (TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)
                || (TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM == e_trigger_type))
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" UPDATER_COND_PREPROCESSING Install_trigger[disable AM power key] !\n"));
            a_tv_net_send_cmd(":dtv_app_mtk,am,:disable_PKWD\n");
            }

            nav_updater_update_info((UINT8)UPDATER_STATUS_SHOW_UI);

            if ((NULL != pt_this->pt_curr_dlivry_hdlr) &&
                (NULL != pt_this->pt_curr_dlivry_hdlr->pf_preprocess))
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" trigger curr_dlivry_hdlr preprocess !\n"));
                i4_ret = pt_this->pt_curr_dlivry_hdlr->pf_preprocess(_nav_updater_preprocess_cb);
            }

            if (NAVR_OK != i4_ret)
            {
                pt_this->e_exit_reason = UPDATER_EXIT_REASON_CHECKING_UPDATE_FAIL;
                _nav_updater_cnd_chg(UPDATER_COND_EXIT);
            }
            else
            {
                /* wait for the callback, do nothing */
                ;
            }
            break;

        case UPDATER_COND_VALIDATING:
            nav_updater_uli_set_fw_status(CHECK_STATE_FW_VALIDATING);
            updater_reset_log_file();
            pt_this->ui1_progress = 0;
            pt_this->t_updater_view_hdlr.pf_update_progress(UPDATER_UPDATE_REASON_PROGRESS);

            /* do integrity check */
            if ((NULL != pt_this->pt_curr_dlivry_hdlr) &&
                (FALSE == pt_this->pt_curr_dlivry_hdlr->b_division))
            {
                if (pt_this->pt_updater_cfg->pf_integrity_chk)
                {
                    i4_ret = pt_this->pt_updater_cfg->pf_integrity_chk(pt_this);
                }
            }
            else
            {
                i4_ret = UPDATERR_OK;
            }

            if (UPDATERR_OK != i4_ret)
            {
                pt_this->e_exit_reason = UPDATER_EXIT_REASON_VALIDATE_FAIL;
                _nav_updater_cnd_chg(UPDATER_COND_EXIT);
            }
            else
            {
            #ifdef APP_ULI_UPG_SUPPORT
                if ((pt_this->pt_curr_dlivry_hdlr != NULL) &&
                    (UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type) &&
                    nav_updater_uli_is_usb_method() && (FALSE == _nav_updater_is_bgm()))
            #else
                if ((pt_this->pt_curr_dlivry_hdlr != NULL) &&
                    (UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type) &&
                    (FALSE == _nav_updater_is_bgm()))
            #endif
                {
                    /* Flush file system buffers */
                    //sync();

                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" ULI Download ok, paring directly!\n"));

					_nav_updater_cnd_chg(UPDATER_COND_PARSING);

                    //nav_updater_reboot_system();
                }
                else
                {
                    _nav_updater_cnd_chg(UPDATER_COND_PARSING);
                }
            }
            break;

        case UPDATER_COND_PARSING:

            nav_updater_uli_set_fw_status(CHECK_STATE_FW_PARSING);
            pt_this->t_updater_view_hdlr.pf_update_progress(UPDATER_UPDATE_REASON_PROGRESS);

            /* parse firmware version */
            if (NULL != pt_this->pt_updater_cfg->pf_parse_fw_info)
            {
                i4_ret = pt_this->pt_updater_cfg->pf_parse_fw_info(pt_this);
            }

            if ((NAVR_OK != i4_ret)
                || (0 == pt_this->t_upg_fw_info.ui4_item_num))
            {
                pt_this->e_exit_reason = UPDATER_EXIT_REASON_PARSE_FAIL;
                _nav_updater_cnd_chg(UPDATER_COND_EXIT);
            }
            else
            {
#ifdef APP_PRE_UPG_CHK
                /* compare firmware version */
                if (NULL != pt_this->pt_updater_cfg->pf_pre_upg_chk)
                {
                    i4_ret = pt_this->pt_updater_cfg->pf_pre_upg_chk(pt_this);
                }

                UINT32    ui4_selcted_item_num = 0;

                for (ui4_idx = 0 ; ui4_idx < pt_this->t_upg_fw_info.ui4_item_num ; ui4_idx++)
                {
                    if (pt_this->t_upg_fw_info.pt_item[ui4_idx].ui4_flag & UPDATER_ITEM_FLAG_SELECTED)
                    {
                         ui4_selcted_item_num++;
                    }
                }

                if ((NAVR_OK != i4_ret)
                    || (0 == ui4_selcted_item_num))
                {
                    pt_this->e_exit_reason = UPDATER_EXIT_REASON_PARSE_FAIL;
                    _nav_updater_cnd_chg(UPDATER_COND_EXIT);
                }
                else
                {
#endif
                    a_fw_updater_cust_free_tag_buff();

                    i4_ret = a_fw_updater_cust_alloc_tag_buff(pt_this->t_upg_fw_info.ui4_item_num);

                    if (UPDATERR_OK != i4_ret)
                    {
                        pt_this->e_exit_reason = UPDATER_EXIT_REASON_PARSE_FAIL;
                        _nav_updater_cnd_chg(UPDATER_COND_EXIT);
                    }
                    _nav_updater_cnd_chg(UPDATER_COND_INITED);
#ifdef APP_PRE_UPG_CHK
                }
#endif
            }
            break;

        case UPDATER_COND_INITED:

            nav_updater_uli_set_fw_status(CHECK_STATE_FW_INITED);
            pt_this->t_updater_view_hdlr.pf_update_progress(UPDATER_UPDATE_REASON_PROGRESS);

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"UPDATER_COND_INITED: pt_curr_dlivry_hdlr->e_type = %d \n", pt_this->pt_curr_dlivry_hdlr->e_type));

#if 0
            if ((UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type)
                 && (!nav_updater_uli_is_usb_method()))
#endif
            {
                /* Showing Sidebar in BGM mode or FGM mode */
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"UPDATER_COND_INITED: showing sidebar \n"));

                nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_UPGRADE, NULL);
            }

            if ((TRUE == _nav_updater_is_bgm())
                ||(UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type)
                || (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK != e_trigger_type)&& (TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD != e_trigger_type) && (TRIGGER_TYPE_ULI_NETWORK_FW_CHECK_AND_UPDATE != e_trigger_type))
            {
                /* do download forcely */
                _nav_updater_model_download();
            }
            break;

        case UPDATER_COND_DOWNLOADING:
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"UPDATER_COND_DOWNLOADING: UPDATING_SMARTCAST \n"));
            nav_updater_set_oobe_update_status(WZD_PAGE_INDEX_C4TV_UPDATING_SMARTCAST);

            nav_updater_uli_set_update_stage(STAGE_FW_INSTALING);

            nav_updater_uli_set_fw_status(CHECK_STATE_CHECK_INSTALLING);
            if (FALSE == _nav_updater_is_bgm())
            {
                CHAR                            s_active_app[APP_NAME_MAX_LEN + 1] = {0} ;
                INT32  i4_ret;
                i4_ret = a_am_get_active_app(s_active_app);

                NAV_UPGRADE_LOG_PRINT(("\n************========[nav_updater.c]_nav_updater_cnd_chg:UPDATER_COND_DOWNLOADING:i4_ret=%d,active_app=%s =========***************\n",i4_ret,s_active_app));

                if ((AMR_OK == i4_ret)
                    &&(0 == c_strcmp (s_active_app, NAV_NAME)))
                {
                a_amb_enable_system_key(FALSE);
                a_amb_enable_power_key(FALSE);
                }
            }

                a_tv_net_send_cmd(":dtv_app_mtk,am,:disable_PKWD\n");
            break;

        case UPDATER_COND_COMPLETE_ONE:
            /* If pre-item is a .tgz file, should to decompress it. */
            _nav_updater_decompress_tgz_file(pt_this->ui4_crnt_upg_item_idx);

            pt_this->ui4_upg_done_item_num++;
            b_found = FALSE;
            for (ui4_idx = (pt_this->ui4_crnt_upg_item_idx + 1) ; ui4_idx < pt_this->t_upg_fw_info.ui4_item_num ; ui4_idx++)
            {
                if (pt_this->t_upg_fw_info.pt_item[ui4_idx].ui4_flag & UPDATER_ITEM_FLAG_SELECTED)
                {
                     pt_this->ui4_crnt_upg_item_idx = ui4_idx;
                     b_found = TRUE;
                     break;
                }
            }

            /* if not found => just set next upgrade index to the total item number */
            if (FALSE == b_found)
            {
                pt_this->ui4_crnt_upg_item_idx = pt_this->t_upg_fw_info.ui4_item_num;
            }
            else
            {

                UPDATER_ITEM_T*    pt_upg_item;
                if ((pt_this->ui4_crnt_upg_item_idx - 1) >=0 )
                {
                    pt_upg_item = &(pt_this->t_upg_fw_info.pt_item[pt_this->ui4_crnt_upg_item_idx - 1]);
                    updater_log_printf(NAV_UPDATER_PREFIX" %s updater Complete!!\n",pt_upg_item->s_name);
                }
            }
            break;

        case UPDATER_COND_FAILED:
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" UPDATER_COND_FAILED: pt_curr_dlivry_hdlr->e_type=%d _nav_updater_is_bgm()=%d\n",pt_this->pt_curr_dlivry_hdlr->e_type,_nav_updater_is_bgm()));
            if ((UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type) || (UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type))
            {
                /*
                  1. Hide UI   - failed and not start upgrade data to TV.
                  2. Reboot TV - failed and start update data to TV.
                */
                if ((UPDATER_COND_INITED == pt_this->e_cond) || (UPDATER_COND_EXIT == pt_this->e_cond))
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" Upgrade failed, Hide UI!\n"));

                }
                _nav_updater_model_leave();
#ifdef APP_BASIC_RO
                nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_BASIC);
                /* nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_3RD); */
#endif
            }
            else if (TRUE == _nav_updater_is_bgm())
            {
                /* do not retry and change to dead state direcly */
                _nav_updater_cnd_chg(UPDATER_COND_DEAD);
            }
            break;

        case UPDATER_COND_DEAD:
            nav_updater_update_info((UINT8)UPDATER_STATUS_CLEAR);
            /*
            a_fw_updater_cust_free_tag_buff();
            */
            if ((pt_this->pt_curr_dlivry_hdlr != NULL) &&
                (pt_this->pt_curr_dlivry_hdlr->pf_exit!= NULL))
            {
                pt_this->pt_curr_dlivry_hdlr->pf_exit(FALSE);
            }
            /* free XML tree */
            if (NULL != pt_this->pt_download_xml)
            {
                c_xml_free(pt_this->pt_download_xml);
                pt_this->pt_download_xml = NULL;
            }
#ifdef APP_PRE_UPG_CHK
            if (NULL != pt_this->pt_version_xml)
            {
                c_xml_free(pt_this->pt_version_xml);
                pt_this->pt_version_xml = NULL;
            }
#endif
#if 0
            /* delete upg_download.xml because the whole upgrade process is not completed! */
            c_fm_delete_file(FM_ROOT_HANDLE, UPDATER_XML_PATH "/" UPDATER_UPG_XML_NAME);
#endif
            a_tv_net_send_cmd(":dtv_app_mtk,am,:enable_PKWD\n");
            if (FALSE == _nav_updater_is_bgm())
            {
                a_amb_enable_power_key(TRUE);
            }
#if 0
            if (UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type)
            {
                /* delete upgrade.pkg because the whole upgrade process is not completed! */
                c_fm_delete_file(FM_ROOT_HANDLE, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_NAME);
            }

            /* Flush file system buffers */
            sync();
#endif

            if (FALSE == _nav_updater_is_bgm())
            {
                if ((pt_this->pt_curr_dlivry_hdlr != NULL) &&
                    ((UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type) ||
                    (UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type)))
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" Upgrade failed, reboot TV system!\n"));


                    /* Reboot TV - failed and start update data to TV. */
                    nav_updater_reboot_system();
                }
            }
#ifdef APP_BASIC_RO
            nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_BASIC);
            /* nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_3RD); */
#endif
            break;

        case UPDATER_COND_COMPLETE:
            pt_this->ui1_progress = 100;
            pt_this->t_updater_view_hdlr.pf_update_progress(UPDATER_UPDATE_REASON_PROGRESS);

#ifdef APP_PRE_UPG_CHK
            if (NULL != pt_this->pt_updater_cfg->pf_save_upg_result)
            {
                i4_ret = pt_this->pt_updater_cfg->pf_save_upg_result(pt_this);
            }

            if (NAVR_OK != i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Cat not save upgrade result!\n"));

            }
#endif

            _nav_updater_set_complete_flag();
            _nav_updater_set_old_fw_version();

            _nav_updater_sync_wzd_sys_upgrade_status(APP_CFG_CUST_WZD_SYS_UPDATE_COMPLETE);
            a_cfg_custom_set_bootup_assistant_flag(ACFG_BOOTUP_ASSISTANT_FAC_RESET);

#ifdef NAV_UPDATER_TOGGLE_DUAL_BANK_AT_COMPLETED_ALL
            /* Toggle dual bank index after completed all */
            _nav_updater_toggle_dual_bank_by_mask();

            /* Upgrade completed, should create a expire flag file for 3rd */
            if (b_g_tar_3rd_ok)
            {
                _nav_updater_create_expire_file_in_3rd();
            }

            /* Upgrade completed, should create a expire flag file for basic */
            if (b_g_tar_basic_ok)
            {
                _nav_updater_create_expire_file_in_basic();
            }
#endif

            nav_updater_update_info((UINT8)UPDATER_STATUS_EXEC_DONE);

            a_fw_updater_cust_free_tag_buff();

            if (nav_updater_is_bgm_ex()
                && ((pt_this->pt_curr_dlivry_hdlr != NULL) &&
                    (UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type) &&
                    nav_updater_uli_is_intnt_method()
                    && (TRIGGER_TYPE_ULI_BGM_NETWORK_FW_DOWNLOAD_AND_INSTALL == e_trigger_type)))
            {

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"UPDATER_COND_COMPLETE set BGM_POWER_DOWN_MODE_FORCE_REBOOT\n"));
                a_icl_set_bgm_power_down_mode (BGM_POWER_DOWN_MODE_FORCE_REBOOT);
                b_is_for_bgm_upgrade = TRUE;
            }

            if ((pt_this->pt_curr_dlivry_hdlr != NULL) &&
                (pt_this->pt_curr_dlivry_hdlr->pf_exit!= NULL))
            {
                pt_this->pt_curr_dlivry_hdlr->pf_exit(TRUE);
            }
            /* free XML tree */
            if (NULL != pt_this->pt_download_xml)
            {
                c_xml_free(pt_this->pt_download_xml);
                pt_this->pt_download_xml = NULL;
            }
#ifdef APP_PRE_UPG_CHK
            if (NULL != pt_this->pt_version_xml)
            {
                c_xml_free(pt_this->pt_version_xml);
                pt_this->pt_version_xml = NULL;
            }
#endif
            b_is_file_base = FALSE;
            for (ui4_idx = 0 ; ui4_idx < pt_this->t_upg_fw_info.ui4_item_num ; ui4_idx++)
            {
                if (UPDATER_METHOD_FILE == pt_this->t_upg_fw_info.pt_item[ui4_idx].e_method)
                {
                     b_is_file_base = TRUE;
                     break;
                }
            }

            if (!b_is_file_base)
            {
                /* the upg_download.xml should be delete when current upgrade is not file base method! */
                c_fm_delete_file(FM_ROOT_HANDLE, UPDATER_XML_PATH "/" UPDATER_UPG_XML_NAME);
            }
            else
            {
                /* rename upg_download.xml to download.xml, and delete upg_download.xml */
                a_fw_updater_vailidate_upg_xml();
            }

            /* delete upgrade.pkg because the whole upgrade process is completed! */
            i4_ret = c_fm_delete_file(FM_ROOT_HANDLE, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_INTEGRITY_OK_NAME);
            if (FMR_OK != i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_fm_delete_file: i4_ret=%d, %s/%s !\n", i4_ret,UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH,UPDATER_FW_INTEGRITY_OK_NAME));

            }

            /* Flush file system buffers */
            sync();

            a_tv_net_send_cmd(":dtv_app_mtk,am,:enable_PKWD\n");

            updater_log_printf(NAV_UPDATER_PREFIX" All partition updater complete!!\n");

            nav_updater_uli_set_fw_status(CHECK_STATE_CHECK_INSTALLED);

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"UPDATER_COND_DOWNLOADING: UPDATE_COMPLETE \n"));
            nav_updater_set_oobe_update_status(WZD_PAGE_INDEX_C4TV_UPDATE_COMPLETE);

            /*For rest should wait the status have been get by the rest app*/
            nav_updater_check_continue_next_step(NAV_UPDATER_CHK_STEP_INSTALL_OK,&b_is_to_continue);
            /* reset the flag*/
            nav_updater_uli_set_trigger_type(TRIGGER_TYPE_NONE);
            nav_updater_uli_set_update_stage(STAGE_NONE);
            nav_updater_uli_set_user_mode(USER_MODE_NONE);

            nav_updater_view_set_toast_process_bar_status(FALSE);

            if (FALSE == b_is_for_bgm_upgrade)
            {
                i4_ret = a_nav_updater_uli_set_oobe_update_finished_complete(TRUE);
                a_amb_enable_power_key(TRUE);

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" Upgrade success, reboot TV system!\n"));
                a_tv_set_env_to_mpool("OTA_REBOOT", "1");


                /* Reboot TV System after the whole upgrade process is completed! */
                nav_updater_reboot_system_ex();
            }
            else
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" Upgrade success [BGM]!\n"));
                b_is_for_bgm_upgrade = FALSE;
            }

#ifdef APP_BASIC_RO
            nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_BASIC);
            /* nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_3RD); */
#endif
            break;

        case UPDATER_COND_EXIT:
            a_tv_net_send_cmd(":dtv_app_mtk,am,:enable_PKWD\n");
            if (FALSE == _nav_updater_is_bgm())
            {
                if (FALSE == a_wzd_is_oobe_mode())
                {
                    // In OOBE, do not enable system keys
                    a_amb_enable_system_key(TRUE);
                }
                a_amb_enable_power_key(TRUE);
                /* do leave forcely */
                _nav_updater_model_leave();
            }
        #ifdef APP_ULI_UPG_SUPPORT
            if ((UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type) ||
                ((UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type) && nav_updater_uli_is_usb_method()) ||
                ((UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type) && (FALSE == _nav_updater_is_bgm())))
        #else
            if ((UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type) ||
                ((UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type)))
        #endif
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s, Delivery type: %d, BGM: %d.\n",
                    __FUNCTION__, pt_this->pt_curr_dlivry_hdlr->e_type, _nav_updater_is_bgm()));

                /* delete upgrade.pkg because the whole upgrade process is completed! */
                i4_ret = c_fm_delete_file(FM_ROOT_HANDLE, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_INTEGRITY_OK_NAME);
                if (FMR_OK != i4_ret)
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_fm_delete_file: i4_ret=%d, %s/%s !\n", i4_ret,UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH,UPDATER_FW_INTEGRITY_OK_NAME));

                }
                /* Flush file system buffers */
                sync();

                if (FALSE == _nav_updater_is_bgm())
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s, %d, hide UI.\n", __FUNCTION__, __LINE__));
                    nav_updater_hide_dialog();

                    if (UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type)
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" Upgrade failed, reboot TV system!\n"));
                        nav_updater_reboot_system();
                    }
                #ifdef APP_ULI_UPG_SUPPORT
                    else if (nav_updater_uli_is_usb_method() &&
                            (pt_this->e_exit_reason == UPDATER_EXIT_REASON_DECRYP_FAIL))
                #else
                    else if (pt_this->e_exit_reason == UPDATER_EXIT_REASON_DECRYP_FAIL)
                #endif
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"DECRYP_FAIL, reboot TV system!\n"));
                        nav_updater_reboot_system();
                    }
                    else
                    {
                        /* do leave forcely */
                        _nav_updater_model_leave();
                    }
                }
                else
                {
                    /* do leave forcely */
                    _nav_updater_model_leave();
                }
            }
            else if (TRUE == _nav_updater_is_bgm())
            {
                /* do leave forcely */
                _nav_updater_model_leave();
            }
#ifdef APP_BASIC_RO
            nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_BASIC);
            /* nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_3RD); */
#endif
            break;

        default:
            break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_init
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_init(
    NAV_CONTEXT_T*     pt_ctx
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
    INT32              i4_ret;
    UPDATER_ITEM_T*    pt_tmp = NULL;

    /* Init semaphore (mutex) */
    NAV_LOG_ON_FAIL(c_sema_create(&t_g_updater_ctrl.h_sema_mtx,
                               X_SEMA_TYPE_MUTEX,
                               X_SEMA_STATE_UNLOCK));


    pt_this->pt_ctx = pt_ctx;

    pt_this->pf_download = _nav_updater_model_download;
    pt_this->pf_leave    = _nav_updater_model_leave;

    pt_this->t_upg_fw_info.ui4_item_num = 0;

    pt_tmp = c_mem_alloc(sizeof(UPDATER_ITEM_T) * UPDATER_MAX);

    if (NULL == pt_tmp)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"insufficient memory\n"));

        return NAVR_FAIL;
    }

    pt_this->t_upg_fw_info.pt_item = pt_tmp;
    c_memset(pt_this->t_upg_fw_info.pt_item, 0, sizeof(UPDATER_ITEM_T) * UPDATER_MAX);

#ifdef APP_PRE_UPG_CHK
    pt_tmp = c_mem_alloc(sizeof(UPDATER_ITEM_T) * UPDATER_MAX);

    if (NULL == pt_tmp)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"insufficient memory\n"));

        return NAVR_FAIL;
    }

    pt_this->t_crnt_fw_info.pt_item = pt_tmp;
#endif

    pt_this->pt_updater_cfg = NULL;

    i4_ret = nav_updater_res_init();
    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    nav_updater_cfg_init();

    i4_ret = pt_this->t_updater_view_hdlr.pf_init(pt_this,
                                                  pt_this->pt_ctx->t_gui_res.h_canvas,
                                                  pt_this->pt_ctx->t_gui_res.i4_x_offset,
                                                  pt_this->pt_ctx->t_gui_res.i4_y_offset);

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    nav_updater_mem_init();


    if (c_handle_valid(pt_this->h_download_process_timer) == TRUE) {
        c_timer_delete(pt_this->h_download_process_timer);
    }

    i4_ret = c_timer_create(&(pt_this->h_download_process_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    /*for UTV download check*/
    if (c_handle_valid(pt_this->h_utv_download_process_timer) == TRUE) {
        c_timer_delete(pt_this->h_utv_download_process_timer);
    }

    i4_ret = c_timer_create(&(pt_this->h_utv_download_process_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    if (c_handle_valid(pt_this->h_delay_firmware_check_timer) == TRUE) {
        c_timer_delete(pt_this->h_delay_firmware_check_timer);
    }

    i4_ret = c_timer_create(&(pt_this->h_delay_firmware_check_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    if (c_handle_valid(pt_this->h_firmware_check_result_query_timer) == TRUE) {
        c_timer_delete(pt_this->h_firmware_check_result_query_timer);
    }

    i4_ret = c_timer_create(&(pt_this->h_firmware_check_result_query_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    if (c_handle_valid(pt_this->h_firmware_check_waiting_feedback) == TRUE) {
        c_timer_delete(pt_this->h_firmware_check_waiting_feedback);
    }

    i4_ret = c_timer_create(&(pt_this->h_firmware_check_waiting_feedback));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }


    if (c_handle_valid(pt_this->h_firmware_no_avaliable_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_firmware_no_avaliable_hide_timer);
    }

    i4_ret = c_timer_create(&(pt_this->h_firmware_no_avaliable_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    /*for rest check*/
    pt_this->b_is_need_fw_re_check = TRUE;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_deinit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_deinit(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    /* deinit the view */
    pt_this->t_updater_view_hdlr.pf_deinit();

    /* free memory  */
    if (NULL != pt_this->t_upg_fw_info.pt_item)
    {
        c_mem_free(pt_this->t_upg_fw_info.pt_item);
    }

#ifdef APP_PRE_UPG_CHK
    if (NULL != pt_this->t_crnt_fw_info.pt_item)
    {
        c_mem_free(pt_this->t_crnt_fw_info.pt_item);
    }
#endif

    if (c_handle_valid(pt_this->h_download_process_timer) == TRUE) {
        c_timer_delete(pt_this->h_download_process_timer);
    }

    pt_this->h_download_process_timer = NULL_HANDLE;

    /*for UTV Download*/
    if (c_handle_valid(pt_this->h_utv_download_process_timer) == TRUE) {
        c_timer_delete(pt_this->h_utv_download_process_timer);
    }

    pt_this->h_utv_download_process_timer = NULL_HANDLE;


    if (c_handle_valid(pt_this->h_delay_firmware_check_timer) == TRUE) {
        c_timer_delete(pt_this->h_delay_firmware_check_timer);
    }

    pt_this->h_delay_firmware_check_timer = NULL_HANDLE;


    if (c_handle_valid(pt_this->h_firmware_check_result_query_timer) == TRUE) {
        c_timer_delete(pt_this->h_firmware_check_result_query_timer);
    }

    pt_this->h_firmware_check_result_query_timer = NULL_HANDLE;


    if (c_handle_valid(pt_this->h_firmware_check_waiting_feedback) == TRUE) {
        c_timer_delete(pt_this->h_firmware_check_waiting_feedback);
    }

    pt_this->h_firmware_check_waiting_feedback = NULL_HANDLE;


    if (c_handle_valid(pt_this->h_firmware_no_avaliable_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_firmware_no_avaliable_hide_timer);
    }

    pt_this->h_firmware_no_avaliable_hide_timer = NULL_HANDLE;

    return NAVR_OK;
}

static VOID _nav_update_stop_download_check_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (c_handle_valid(pt_this->h_download_process_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_download_process_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop NAV_UPDATE::h_download_process_timer failed!"));
    }
}
static VOID _nav_updater_uli_download_percent_handler
(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    INT32   ui4_percent        = (INT32)pv_tag1;
    BOOL    b_force_state = FALSE;
	NAV_UPDATER_TRIGGER_TYPE_T   e_trigger_type = TRIGGER_TYPE_NONE;
    /*update the process bar*/
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
	nav_updater_uli_get_trigger_type(&e_trigger_type);
	if(e_trigger_type == TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM)
	{
		DBG_LOG_PRINT(("%s_%d usb cmd case,no need \n",__FUNCTION__,__LINE__));
		return;
	}
    pt_this->ui1_fw_download_progress = ui4_percent;

    DBG_LOG_PRINT(("%s_%d ui4_percent:%d \n",__FUNCTION__,__LINE__,ui4_percent));
    nav_updater_view_update_toast_process_bar((UINT8)ui4_percent,TRUE);
    nav_updater_uli_get_fw_force_update_flag(&b_force_state);
    if (b_force_state)
    {
        nav_update_send_fw_download_msg_to_observer(UPDATER_DOWNLOAD_COND_DOWNLOADING, ui4_percent);
    }
}

static INT32 _nav_updater_uli_download_percent_cb(
    INT32    ui4_percent
)
{
    nav_request_context_switch(_nav_updater_uli_download_percent_handler,
                               (VOID*)(ui4_percent),
                               NULL,
                               NULL);
    return 0;
}
static VOID _nav_update_download_check_timeout_to_check(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    //UINT32 ui4_PercentComplete = 0;
    NAV_UPDATER_RUNNING_STAGE_T  e_update_stage = STAGE_NONE;
    NAV_UPDATER_FW_STATE_T  e_fw_state = CHECK_STATE_NONE;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
    INT32   i4_download_percent = 0;
    BOOL    b_force_state = FALSE;
    /* execute in navigator's thread context */
    a_uli_custom_get_download_percentage(_nav_updater_uli_download_percent_cb);

    nav_updater_uli_get_update_stage(&e_update_stage);
    nav_updater_uli_get_fw_status(&e_fw_state);

    /* notify*/
    if (STAGE_FW_DOWNLOADING != e_update_stage ||
		e_fw_state == CHECK_STATE_DOWNLOAD_FAIL ||
		CHECK_STATE_NONE == e_fw_state ||
		CHECK_STATE_CHECK_FAIL == e_fw_state)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_download_check_timeout_to_check download_check_timer[stop] \n"));
        _nav_update_stop_download_check_timer();
    }
    else
    {

        nav_update_reset_download_check_timer();
    }
	if(STAGE_FW_DOWNLOADING == e_update_stage)
	{
		nav_updater_uli_set_fw_status(CHECK_STATE_DOWNLOADING);
	}
	if(e_fw_state == CHECK_STATE_DOWNLOAD_FAIL ||
	CHECK_STATE_NONE == e_fw_state ||
	CHECK_STATE_CHECK_FAIL == e_fw_state)
	{
		  NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"CHECK_STATE_DOWNLOAD_FAIL [FW_AVALIABLE_SATUS_NO] \n"));
		  nav_updater_view_show_download_fail_info(TRUE);
		  nav_update_reset_firmware_download_fail_hide_timer();
		  a_uli_check_drmp_update();
		  return;
	}
    if ((CHECK_STATE_DOWNLOAD_SUCESS == e_fw_state)
        ||(CHECK_STATE_FW_VALIDATING == e_fw_state)
        || (CHECK_STATE_FW_PARSING == e_fw_state)
        ||(CHECK_STATE_FW_INITED == e_fw_state)
        ||(CHECK_STATE_CHECK_INSTALLING == e_fw_state)
        ||(CHECK_STATE_CHECK_INSTALLED == e_fw_state))
    {

         pt_this->ui1_fw_download_progress = 100;
    }

    i4_download_percent = pt_this->ui1_fw_download_progress;
    nav_updater_uli_get_fw_force_update_flag(&b_force_state);
    if (100 == pt_this->ui1_fw_download_progress)
    {
    	nav_updater_uli_set_fw_status(CHECK_STATE_DOWNLOAD_SUCESS);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_download_check_timeout_to_check download[complete] \n"));
        if (b_force_state)
        {
            nav_update_send_fw_download_msg_to_observer(UPDATER_DOWNLOAD_COND_DOWNLOADING, i4_download_percent);
        }
    }


}

static VOID _nav_update_download_check_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_download_check_timeout_to_check, pv_tag, NULL, NULL);
}

VOID nav_update_reset_download_check_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    _nav_update_stop_download_check_timer();

    i4_ret = c_timer_start(
                    pt_this->h_download_process_timer,
                    NAV_UPDATE_DOWNLOAD_CHECK_TIMER_DURATION,
                    X_TIMER_FLAG_ONCE,
                    _nav_update_download_check_timer_nfy,
                    pt_this
                    );

    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start nav update::h_download_process_timer failed!"));
    }
}
static VOID _nav_update_update_led_status_fct(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
	a_cfg_custom_update_led_logo_ctrl();
}


static VOID _nav_update_update_led_status(VOID)
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_update_led_status_fct, NULL, NULL, NULL);
}

static VOID _nav_update_stop_utv_download_check_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (c_handle_valid(pt_this->h_utv_download_process_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_utv_download_process_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop NAV_UPDATE::h_utv_download_process_timer failed!"));
    }
}

static VOID _nav_update_utv_download_check_timeout_to_check(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    UINT32 ui4_PercentComplete = 0;
    NAV_UPDATER_RUNNING_STAGE_T  e_update_stage = STAGE_NONE;
    NAV_UPDATER_FW_STATE_T  e_fw_state = CHECK_STATE_NONE;
    NAV_UPDATER_TRIGGER_TYPE_T   e_trigger_type = TRIGGER_TYPE_NONE;
    CHAR                   s_path[128] = {0};
    UINT32                 ui4_size    = 128;
	UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    nav_updater_uli_get_trigger_type(&e_trigger_type);
    /* execute in navigator's thread context */
	nav_updater_uli_get_update_stage(&e_update_stage);
    nav_updater_uli_get_fw_status(&e_fw_state);
	if(e_update_stage == STAGE_FW_INSTALING && e_fw_state ==CHECK_STATE_DOWNLOAD_SUCESS)
	{
		if(access("/upgrade/usb_cmd_complete",0) == 0)
		{
			NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"usb cmd install sucess \n"));
			if (NAVR_OK == pt_this->pt_curr_dlivry_hdlr->pf_get_path(s_path, ui4_size))
			{
				c_fm_delete_file(FM_ROOT_HANDLE, s_path);
			}
			system("rm /upgrade/usb_cmd_complete;sync");
			a_cfg_cust_led_blinking_stop();
			_nav_update_stop_utv_download_check_timer();
			nav_updater_hide_dialog();
		    a_amb_enable_system_key(TRUE);
		    a_amb_enable_power_key(TRUE);
			_nav_updater_cnd_chg(UPDATER_COND_INIT);
            _nav_updater_model_leave();
			_nav_update_update_led_status();
			return;
		}
	}
	else
	{
   		a_uli_custom_get_download_percentage(_nav_updater_uli_download_percent_cb);
	}


    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_utv_download_check_timeout_to_check \n"));
    if((e_update_stage == STAGE_FW_DOWNLOADING || e_update_stage == STAGE_FW_INSTALING)&&
        (e_trigger_type == TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL || e_trigger_type == TRIGGER_TYPE_ULI_USB_FW_CHECK_CONFIRM))
    {
    	if(UPDATER_USB_TYPE_CMD==a_nav_updater_uli_get_usb_upgrade_type())
    	{
        	nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_ULI_USB_COMMAND_STICK_PROCESS, NULL);
    	}
    }

    /* notify*/
    if (STAGE_NONE == e_update_stage ||
		e_fw_state == CHECK_STATE_DOWNLOAD_FAIL ||
		CHECK_STATE_NONE == e_fw_state ||
		CHECK_STATE_CHECK_FAIL == e_fw_state)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_download_check_timeout_to_check download_check_timer[stop] \n"));
        _nav_update_stop_utv_download_check_timer();
    }
    else
    {
        nav_update_reset_utv_download_check_timer();
    }

    //NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_utv_download_check_timeout_to_check TRG_ui4_PercentComplete[%d]\n",ui4_PercentComplete));

}

static VOID _nav_update_utv_download_check_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_utv_download_check_timeout_to_check, pv_tag, NULL, NULL);
}

VOID nav_update_reset_utv_download_check_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    _nav_update_stop_utv_download_check_timer();

    i4_ret = c_timer_start(
                    pt_this->h_utv_download_process_timer,
                    NAV_UPDATE_DOWNLOAD_CHECK_TIMER_DURATION,
                    X_TIMER_FLAG_ONCE,
                    _nav_update_utv_download_check_timer_nfy,
                    pt_this
                    );

    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start nav update::h_download_process_timer failed!"));
    }
}

static VOID _nav_update_stop_firmware_no_avaliable_hide_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (c_handle_valid(pt_this->h_firmware_no_avaliable_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_firmware_no_avaliable_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop NAV_UPDATE::h_firmware_no_avaliable_hide_timer failed!"));
    }
}

static VOID _nav_update_firmware_no_avaliable_hide_timeout_to_check(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    nav_updater_view_show_firmware_check_not_avaliable_info(FALSE);
}

static VOID _nav_update_firmware_no_avaliable_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_firmware_no_avaliable_hide_timeout_to_check, pv_tag, NULL, NULL);
}

VOID nav_update_reset_firmware_no_avaliable_hide_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    _nav_update_stop_firmware_no_avaliable_hide_timer();

    i4_ret = c_timer_start(
                    pt_this->h_firmware_no_avaliable_hide_timer,
                    NAV_UPDATE_FIRMWARE_NO_AVALIABLE_HIDE_TIMER_DURATION,
                    X_TIMER_FLAG_ONCE,
                    _nav_update_firmware_no_avaliable_hide_timer_nfy,
                    pt_this
                    );

    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start nav update::h_firmware_no_avaliable_hide_timer failed!"));
    }
}
static VOID _nav_update_firmware_download_fail_hide_timeout_to_check(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    nav_updater_view_show_download_fail_info(FALSE);
}

static VOID _nav_update_firmware_download_fail_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_firmware_download_fail_hide_timeout_to_check, pv_tag, NULL, NULL);
}

VOID nav_update_reset_firmware_download_fail_hide_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    _nav_update_stop_firmware_no_avaliable_hide_timer();

    i4_ret = c_timer_start(
                    pt_this->h_firmware_no_avaliable_hide_timer,
                    NAV_UPDATE_FIRMWARE_NO_AVALIABLE_HIDE_TIMER_DURATION,
                    X_TIMER_FLAG_ONCE,
                    _nav_update_firmware_download_fail_hide_timer_nfy,
                    pt_this
                    );

    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start nav update::h_firmware_no_avaliable_hide_timer failed!"));
    }
}

static VOID _nav_update_stop_firmware_check_result_query_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (c_handle_valid(pt_this->h_firmware_check_result_query_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_firmware_check_result_query_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop NAV_UPDATE::h_firmware_check_result_query_timer failed!"));
    }
}

static VOID _nav_update_stop_firmware_waitting_feedback_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (c_handle_valid(pt_this->h_firmware_check_waiting_feedback) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_firmware_check_waiting_feedback);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop NAV_UPDATE::h_firmware_check_result_query_timer failed!"));
    }
}

static VOID nav_update_reset_firmware_waitting_feedback_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    _nav_update_stop_firmware_waitting_feedback_timer();


    i4_ret = c_timer_start(
                    pt_this->h_firmware_check_waiting_feedback,
                    NAV_UPDATE_WAITTING_FEEDBACK_TIMER_DURATION,
                    X_TIMER_FLAG_ONCE,
                    _nav_update_firmware_waitting_feedback_timer_nfy,
                    pt_this
                    );

    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start nav update::h_firmware_check_result_query_timer failed!"));
    }
}
static VOID _nav_update_firmware_waitting_feedback_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_firmware_check_result_wait_feelback, pv_tag, NULL, NULL);
}

static VOID nav_update_check_drmp_waitting_qda_init_timer()
{
    INT32 i4_ret;
    if (c_handle_valid(h_check_qda_init_timer) == TRUE) {
        c_timer_delete(h_check_qda_init_timer);
    }
    i4_ret = c_timer_create(&(h_check_qda_init_timer));
    if (i4_ret != OSR_OK) {
        return;
    }

    /* enable the timer */
    c_timer_start(h_check_qda_init_timer,
                  NAV_UPDATER_CHECK_QDA_INIT_TIMER_DURATION,
                  X_TIMER_FLAG_REPEAT,
                  _nav_update_waitting_qda_init_timer_nty,
                  NULL);
}
static VOID _nav_update_waitting_qda_init_timer_nty(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    nav_request_context_switch(_nav_update_check_drmp_waitting_qda_init,
                               NULL,
                               NULL,
                               NULL);
    return;
}
static VOID _nav_update_check_drmp_waitting_qda_init()
{
    INT32 i4_ret;
    if(a_uli_check_qda_init())
    {
        i4_ret = c_timer_delete(h_check_qda_init_timer);
        if (i4_ret != OSR_OK) {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_check_qda_init_timer() called \n"));
        }
        a_uli_check_drmp_update();
    }
}

static VOID _nav_update_firmware_check_result_query_timeout_to_check(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _nav_update_delay_firmware_check_timeout_to_check(NULL,NULL,NULL);
}

static VOID _nav_update_firmware_check_result_query_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_firmware_check_result_query_timeout_to_check, pv_tag, NULL, NULL);
}

VOID nav_update_reset_firmware_check_result_query_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    _nav_update_stop_firmware_check_result_query_timer();

    i4_ret = c_timer_start(
                    pt_this->h_firmware_check_result_query_timer,
                    NAV_UPDATE_DELAY_FIRMWARE_CHECK_TIMER_DURATION,
                    X_TIMER_FLAG_ONCE,
                    _nav_update_firmware_check_result_query_timer_nfy,
                    pt_this
                    );

    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start nav update::h_firmware_check_result_query_timer failed!"));
    }
}

static VOID _nav_update_stop_delay_firmware_check_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (c_handle_valid(pt_this->h_delay_firmware_check_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_delay_firmware_check_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop NAV_UPDATE::h_delay_firmware_check_timer failed!"));
    }
}
static VOID _nav_update_firmware_check_result_wait_feelback_fct(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
      NAV_UPDATER_FW_STATE_T           e_fw_avaliable_state = CHECK_STATE_NONE;
      NAV_UPDATER_RUNNING_STAGE_T    e_update_stage = STAGE_NONE;
      UINT8 ui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_NO;
      //UINT8 ui1_fw_status_ex = 0;
      UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

      nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);
      nav_updater_uli_get_update_stage(&e_update_stage);
	  if(ui4_waiting_check_update_timeount >= 120)//two minutes means check for update fail
	  {
  	        nav_updater_uli_set_fw_status(CHECK_STATE_CHECK_FAIL);
			nav_updater_uli_set_update_stage(STAGE_NONE);

            nav_updater_uli_set_fw_avaliable(CHECK_STATE_CHECK_FAIL);
			e_update_stage = STAGE_NONE;
			e_fw_avaliable_state = CHECK_STATE_CHECK_FAIL;
	  }
	  if(ui4_waiting_check_update_timeount >= 35)//35 secs need check network status
	  {
	  	   if(!(0 == a_nw_connection_test((CHAR*)"www.google.com") ||
               0 == a_nw_connection_test6((CHAR*)"www.google.com") ))
	  	   	{
	  	        nav_updater_uli_set_fw_status(CHECK_STATE_CHECK_FAIL);
				nav_updater_uli_set_update_stage(STAGE_NONE);

	            nav_updater_uli_set_fw_avaliable(CHECK_STATE_CHECK_FAIL);
				e_update_stage = STAGE_NONE;
				e_fw_avaliable_state = CHECK_STATE_CHECK_FAIL;
				NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"no network connect \n"));
	  	   	}
	  }
      if(e_update_stage == STAGE_FW_WAITING_RESULT)
      {
      	  ui4_waiting_check_update_timeount++;

          nav_update_reset_firmware_waitting_feedback_timer();
          return;
      }

      if (STAGE_FW_CHECKING == e_update_stage)
      {
          ui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_CHECK_BUSY;

           NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_direcly_check_fw_avaliable [BUSY]\n"));
      }
      else
      {
            if (CHECK_STATE_CHECK_AVALIABLE == e_fw_avaliable_state)
            {
                 ui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_YES;
            }
            else
            {
                 ui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_NO;
            }
            pt_this->b_is_need_fw_re_check = TRUE;
      }

      /*Currently defult set the policy to none(noraml)*/

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_direcly_check_fw_avaliable ui1_fw_status[%d]\n",
           ui1_fw_status));
      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_direcly_check_fw_avaliable [END]\n"));

        if (NAV_UPDATE_FW_AVALIABLE_SATUS_CHECK_BUSY == ui1_fw_status)
        {
            /*here should start a timer to
              query the fw avaliable status
            */
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_delay_firmware_check_timeout_to_check [FW_AVALIABLE_SATUS_CHECK_BUSY] \n"));
            nav_update_reset_firmware_check_result_query_timer();
        }
        else if (NAV_UPDATE_FW_AVALIABLE_SATUS_NO == ui1_fw_status)
        {
            /*here should trigger should the firmware
              not avaliable message dialog and also
              should start a timer to with 5s timeout
              to hide this warning
            */

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_delay_firmware_check_timeout_to_check [FW_AVALIABLE_SATUS_NO] \n"));
            nav_loading_page_hide();
            nav_updater_view_show_firmware_check_not_avaliable_info(TRUE);
            nav_update_reset_firmware_no_avaliable_hide_timer();
			a_uli_check_drmp_update();

        }
        else if (NAV_UPDATE_FW_AVALIABLE_SATUS_YES == ui1_fw_status)
        {
            /*as the firmware check is ok,
              so just trigger the firmware
              update
             */

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_delay_firmware_check_timeout_to_check [FW_AVALIABLE_SATUS_YES] \n"));
            nav_loading_page_hide();
            //a_nav_updater_download_firmware_and_trigger_update_directly(&ui1_fw_status_ex);
        }
        else if (NAV_UPDATE_FW_UPDATE_STATUS_FAIL == ui1_fw_status)
        {
            nav_loading_page_hide();//modified by zile.pang
            nav_updater_view_show_firmware_check_not_avaliable_info(TRUE);
            nav_update_reset_firmware_no_avaliable_hide_timer();
            /*do nothing*/
        }
        else
        {
            nav_loading_page_hide();//modified by zile.pang

        }
}

static VOID _nav_update_firmware_check_result_wait_feelback(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    _nav_update_firmware_check_result_wait_feelback_fct(NULL,NULL,NULL);
}

static VOID _nav_update_delay_firmware_check_timeout_to_check(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    UINT8 ui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_NO;
    UINT8 ui_fw_policy = NAV_UPDATE_FW_POLICY_DEFAULT;
    //UINT8 ui1_fw_status_ex = 0;
    CHAR  s_active_name [APP_NAME_MAX_LEN+1]= {0};
    a_am_get_active_app(s_active_name);
    if(c_strcmp(s_active_name, "mscvt")==0
        && (a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
        && !msg_convert_custom_browser_ctrl_active())
    {
        nav_update_reset_delay_firmware_check_timer();
        return;
    }
    if(c_strcmp(s_active_name, "mmp")==0 || c_strcmp(s_active_name, "menu")==0)
    {
        rest_event_notify("key_command", BTN_WIDGET, "");
		nav_update_reset_delay_firmware_check_timer();
        return;
    }

    if (nav_is_active()||(a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED))
    {
        /*start the firmware check*/
        a_nav_updater_direcly_check_fw_avaliable(&ui1_fw_status,&ui_fw_policy);
		ui4_waiting_check_update_timeount = 0;
        nav_update_reset_firmware_waitting_feedback_timer();

    }
    else
    {
        nav_loading_page_hide();//modified by zile.pang
    }

}

static VOID _nav_update_delay_firmware_check_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_update_delay_firmware_check_timeout_to_check, pv_tag, NULL, NULL);
}

VOID nav_update_reset_delay_firmware_check_timer(VOID)
{
    INT32 i4_ret;
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    _nav_update_stop_delay_firmware_check_timer();

    i4_ret = c_timer_start(
                    pt_this->h_delay_firmware_check_timer,
                    NAV_UPDATE_DELAY_FIRMWARE_CHECK_TIMER_DURATION,
                    X_TIMER_FLAG_ONCE,
                    _nav_update_delay_firmware_check_timer_nfy,
                    pt_this
                    );

    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start nav update::h_delay_firmware_check_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_is_key_handler
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static BOOL _nav_updater_is_key_handler(
    NAV_CONTEXT_T*    pt_ctx,
    UINT32            ui4_key_code
)
{
    return FALSE;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_activate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_activate(
    NAV_CONTEXT_T*     pt_ctx,
    UINT32             ui4_key_code
)
{
#if 0
    INT32              i4_ret;
    TV_MODE_T          e_mode;
#endif

    if (b_g_is_show_updater_completed)
    {
        nav_set_component_visible(NAV_COMP_ID_UPDATER);
        b_g_is_show_updater_completed = FALSE;
        return NAVR_OK;
    }

    _nav_updater_disable_module();

    /* hide the banner */
    a_banner_set_excl_comp_on(TRUE);

    nav_set_component_visible(NAV_COMP_ID_UPDATER);
#if 0 /* Keep current input source! */
    i4_ret = a_tv_get_mode(&e_mode);
    if ((TVR_OK == i4_ret)
        && (TV_MODE_TYPE_NORMAL != e_mode))
    {
        a_tv_set_mode(TV_MODE_TYPE_NORMAL);
    }
#endif
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_inactivate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_inactivate(
    NAV_CONTEXT_T*    pt_ctx
)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_inactivate
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_handle_msg(
    NAV_CONTEXT_T*                pt_ctx,
    NAV_UI_MSG_T*                 pt_ui_msg,
    VOID*                         pv_arg1
)
{
    UPDATER_CTRL_T*               pt_this = &t_g_updater_ctrl;
    UPDATER_DLIVRY_HDLR_REG_T*    pt_tmp_hdlr_reg;

    /* broadcast to all delivery handler */
    SLIST_FOR_EACH(pt_tmp_hdlr_reg, &(pt_this->t_hdlr_reg_list), t_link)
    {
        if (NULL != pt_tmp_hdlr_reg->pf_handle_msg)
        {
            pt_tmp_hdlr_reg->pf_handle_msg(pt_ui_msg, pv_arg1);
        }
    }
	NAV_UPDATER_FW_STATE_T		 e_fw_avaliable_state = CHECK_STATE_NONE;

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_APP_PAUSING:
            if (nav_is_component_visible(NAV_COMP_ID_UPDATER))
            {
                nav_updater_do_abort();
            }
            break;

        case NAV_UI_MSG_APP_PRE_RESUME:
            if (NAVR_OK == _nav_updater_get_complete_flag())
            {
                nav_update_check_drmp_waitting_qda_init_timer();
                //system("touch /tmp/reboot_required");
                /*need disable block 3rd for urgent issue*/
                a_tv_net_send_cmd(":dtv_app_mtk,am,:unblock_3rd\n");
#ifdef MTK_CAMERA_DPTZ_SUPPORT
                nav_updater_isp_upgrade_firmware();
#endif
                b_g_is_show_updater_completed = TRUE;
                nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_UPGRADE_COMPLETE, NULL);

            }
			a_cfg_custom_set_drv_bgmupdate_flag(0);
			nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);
			if (nav_updater_is_uli_agent_in_progress()&&
				(e_fw_avaliable_state == CHECK_STATE_DOWNLOADING||
				e_fw_avaliable_state == CHECK_STATE_CHECK_AVALIABLE))
			{
				nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_PREPROCESS, NULL);
				nav_update_reset_utv_download_check_timer();
			}
            break;

        case NAV_UI_MSG_EXTERNAL_CTRL_END:
            if (nav_is_component_visible(NAV_COMP_ID_UPDATER))
            {
                a_amb_enable_system_key(FALSE);
            }
            break;
        case NAV_UI_MSG_POWER_ON:

            if((UPDATER_COND_VALIDATING == pt_this->e_cond)
                || (UPDATER_COND_PARSING == pt_this->e_cond)
                || (UPDATER_COND_INITED == pt_this->e_cond)
                || (UPDATER_COND_DOWNLOADING == pt_this->e_cond)
                || (UPDATER_COND_COMPLETE_ONE == pt_this->e_cond))
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"BGM ==> Power on, disable system key!\n"));


                /* disable power key & system key */
                a_amb_enable_system_key(FALSE);
                a_amb_enable_power_key(FALSE);

                if (b_g_power_key_iom_locked)
                {
                    c_thread_delay(100);
                }

                /* Mute video */
                pt_this->b_is_svc_stop = FALSE;
                _nav_updater_stop_video();
            }

            a_nav_updater_iom_lock_power_key(FALSE);
            if (access("/tmp/uli_log_enable", 0) == 0)
            {
                b_nav_update_log_enable = TRUE;
            }
            else
            {
                b_nav_update_log_enable = FALSE;
            }
            break;
        case NAV_UI_MSG_POWER_OFF:
            a_nav_updater_iom_all_key_locked(FALSE,FALSE);
            break;
        default:
            break;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_hide
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_hide(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this    = &t_g_updater_ctrl;
    TV_WIN_ID_T        e_focus_id = TV_WIN_ID_MAIN;
    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_hide BEG\n"));

    pt_this->b_is_leaving = TRUE;

    if (NULL != pt_this->pt_curr_dlivry_hdlr)
    {
        if ((UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type) ||
            ((UPDATER_DLIVRY_TYPE_ULI == pt_this->pt_curr_dlivry_hdlr->e_type) && (FALSE == _nav_updater_is_bgm())))
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX" %s, Delivery type: %d, BGM: %d, hide UI.\n",
                __FUNCTION__, pt_this->pt_curr_dlivry_hdlr->e_type, _nav_updater_is_bgm()));
            nav_updater_hide_dialog();
        }
    }

    if (FALSE == _nav_updater_is_bgm())
    {
        nav_return_activation(NAV_COMP_ID_UPDATER);

        /* we stop svc when activation so we need to change back to current channel when hide */
        nav_get_focus_id (&e_focus_id);

        if(INP_SRC_TYPE_TV == nav_get_src_type(e_focus_id))
        {
            NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_hide\n"));
            if (a_am_is_power_on())
            {
                NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_hide(SVC)\n"));
                if (pt_this->b_is_svc_stop)
                {
            nav_change_crnt_channel(e_focus_id, NULL);
                    pt_this->b_is_svc_stop = FALSE;
                }
        }
    }
    }

    a_banner_set_excl_comp_on(FALSE);

    _nav_updater_enable_module();

    pt_this->b_is_leaving = FALSE;
    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] _nav_updater_hide END\n"));

    return NAVR_OK;
}

static INT32 _nav_updater_dual_folder_init(VOID)
{
    b_g_clean_bs_files = FALSE;
    b_g_clean_3rd_files= FALSE;

    e_g_basic_start = START_FROM_FOLDER_INIT;
    e_g_3rd_start   = START_FROM_FOLDER_INIT;

#ifdef APP_FW_UPGRADE_SUPPORT_DUAL_BASIC
    b_g_dual_basic_enable = TRUE;
    /*c_dbg_secure_stmt(NAV_UPDATER_PREFIX"Dual Basic is supported! \n");*/
#else
    b_g_dual_basic_enable = FALSE;
    /*c_dbg_secure_stmt(NAV_UPDATER_PREFIX"Dual Basic is not supported! \n");*/
#endif

#ifdef APP_FW_UPGRADE_SUPPORT_DUAL_3RD
    b_g_dual_3rd_enable = TRUE;
    /*c_dbg_secure_stmt(NAV_UPDATER_PREFIX"Dual 3RD is supported! \n");*/
#else
    b_g_dual_3rd_enable = FALSE;
    /*c_dbg_secure_stmt(NAV_UPDATER_PREFIX"Dual 3RD is not supported! \n");*/
#endif

    return (NAVR_OK);
}

static INT32 _nav_updater_query_basic_start_from(VOID)
{
    INT32           i4_ret;
    CHAR            sz_start_from_path[128]={0};

    if (e_g_basic_start != START_FROM_FOLDER_INIT)
    {
        return NAVR_OK;
    }

    /* Check start flag file - /.basic/start_from_bs1 */
    c_strcpy(sz_start_from_path, UPDATER_BASIC_FOLDER_PATH);
    c_strcat(sz_start_from_path, "/");
    c_strcat(sz_start_from_path, UPDATER_BASIC_START_FROM_A_FILE_NAME);

    i4_ret = access(sz_start_from_path, F_OK);
    if (i4_ret == 0)
    {
        e_g_basic_start = START_FROM_FOLDER_A;

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Found '%s' \n", sz_start_from_path));
    }
    else
    {
        /* Check start flag file - /.basic/start_from_bs2 */
        c_strcpy(sz_start_from_path, UPDATER_BASIC_FOLDER_PATH);
        c_strcat(sz_start_from_path, "/");
        c_strcat(sz_start_from_path, UPDATER_BASIC_START_FROM_B_FILE_NAME);

        i4_ret = access(sz_start_from_path, F_OK);
        if (i4_ret == 0)
        {
            e_g_basic_start = START_FROM_FOLDER_B;

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Found '%s' \n", sz_start_from_path));
        }
        else
        {
            e_g_basic_start = DUAL_FOLDER_NOT_SUPPORTED;

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Not found '%s' and '%s' in %s \n",
                       UPDATER_BASIC_START_FROM_A_FILE_NAME,
                       UPDATER_BASIC_START_FROM_B_FILE_NAME,
                       UPDATER_BASIC_FOLDER_PATH));
        }
    }

    return (NAVR_OK);
}

static INT32 _nav_updater_query_3rd_start_from(VOID)
{
    INT32           i4_ret;
    CHAR            sz_start_from_path[128]={0};

    if (e_g_3rd_start != START_FROM_FOLDER_INIT)
    {
        return NAVR_OK;
    }

    /* Check start flag file - /.3rd/start_from_3rd1 */
    c_strcpy(sz_start_from_path, UPDATER_3RD_FOLDER_PATH);
    c_strcat(sz_start_from_path, "/");
    c_strcat(sz_start_from_path, UPDATER_3RD_START_FROM_A_FILE_NAME);

    i4_ret = access(sz_start_from_path, F_OK);
    if (i4_ret == 0)
    {
        e_g_3rd_start = START_FROM_FOLDER_A;

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Found '%s' \n", sz_start_from_path));
    }
    else
    {
        /* Check start flag file - /.3rd/start_from_3rd2 */
        c_strcpy(sz_start_from_path, UPDATER_3RD_FOLDER_PATH);
        c_strcat(sz_start_from_path, "/");
        c_strcat(sz_start_from_path, UPDATER_3RD_START_FROM_B_FILE_NAME);

        i4_ret = access(sz_start_from_path, F_OK);
        if (i4_ret == 0)
        {
            e_g_3rd_start = START_FROM_FOLDER_B;

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Found '%s' \n", sz_start_from_path));
        }
        else
        {
            e_g_3rd_start = DUAL_FOLDER_NOT_SUPPORTED;

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Not found '%s' and '%s' in %s \n",
                       UPDATER_3RD_START_FROM_A_FILE_NAME,
                       UPDATER_3RD_START_FROM_B_FILE_NAME,
                       UPDATER_3RD_FOLDER_PATH));
        }
    }

    return (NAVR_OK);
}

static BOOL  _nav_updater_is_dual_basic_supported(VOID)
{
    return b_g_dual_basic_enable;
}

static BOOL  _nav_updater_is_dual_3rd_supported(VOID)
{
    return b_g_dual_3rd_enable;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_get_next_basic_folder
 *
 * Description: This function using to query current active basic folder,
 *              and return next basic folder id.
 * Inputs:
 *         pui4_next_bs_id - Output pointer.
 *         i4_len          - Buffer lenght of the output pointer.
 *
 * Outputs:
 *         pui4_next_bs_id - Next basic folder id.
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_get_next_basic_folder(CHAR *psz_folder_name, INT32 i4_len)
{
    if (!psz_folder_name)
    {
        return NAVR_INV_ARG;
    }

    if (e_g_basic_start == START_FROM_FOLDER_INIT)
    {
        _nav_updater_query_basic_start_from();
    }

    if (e_g_basic_start == START_FROM_FOLDER_A)
    {
        if (i4_len < c_strlen(UPDATER_BASIC_B_FOLDER_NAME))
        {
            return NAVR_INV_ARG;
        }

        c_strcpy(psz_folder_name, UPDATER_BASIC_B_FOLDER_NAME);

        return NAVR_OK;
    }
    else if (e_g_basic_start == START_FROM_FOLDER_B)
    {
        if (i4_len < c_strlen(UPDATER_BASIC_A_FOLDER_NAME))
        {
            return NAVR_INV_ARG;
        }

        c_strcpy(psz_folder_name, UPDATER_BASIC_A_FOLDER_NAME);

        return NAVR_OK;
    }

    return NAVR_INV_ARG;
}

static INT32 _nav_updater_get_next_3rd_folder(CHAR *psz_folder_name, INT32 i4_len)
{
    if (!psz_folder_name)
    {
        return NAVR_INV_ARG;
    }

    if (e_g_3rd_start == START_FROM_FOLDER_INIT)
    {
        _nav_updater_query_3rd_start_from();
    }

    if (e_g_3rd_start == START_FROM_FOLDER_A)
    {
        if (i4_len < c_strlen(UPDATER_3RD_B_FOLDER_NAME))
        {
            return NAVR_INV_ARG;
        }

        c_strcpy(psz_folder_name, UPDATER_3RD_B_FOLDER_NAME);

        return NAVR_OK;
    }
    else if (e_g_3rd_start == START_FROM_FOLDER_B)
    {
        if (i4_len < c_strlen(UPDATER_3RD_A_FOLDER_NAME))
        {
            return NAVR_INV_ARG;
        }

        c_strcpy(psz_folder_name, UPDATER_3RD_A_FOLDER_NAME);

        return NAVR_OK;
    }

    return NAVR_INV_ARG;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_check_basic_folder
 *
 * Description: Create the folder for bs1 or bs2. If the folder has existed,
 *              There would be no other action.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_check_basic_folder(VOID)
{
#if 1
    INT32           i4_ret;
    CHAR            s_cmd[128];
    CHAR            s_path[80];
    CHAR            s_bs_folder_name[16];

    if (!_nav_updater_is_dual_basic_supported())
    {
        return NAVR_OK;
    }

    i4_ret = _nav_updater_get_next_basic_folder(s_bs_folder_name, 16);
    if(i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    /* Create bs1 or bs2 folder in /.basic/ */
    c_strcpy(s_path, UPDATER_BASIC_FOLDER_PATH);
    c_strcat(s_path, "/");
    c_strcat(s_path, s_bs_folder_name);

    i4_ret = access(UPDATER_BASIC_FOLDER_PATH, F_OK);
    if (i4_ret == 0)
    {
        c_strcpy(s_cmd, "mkdir ");
        c_strcat(s_cmd, s_path);
        i4_ret = system(s_cmd);
        if (i4_ret == 0)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Created folder '%s' ok\n", s_path));
        }
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"access folder '%s' failed, i4_ret=%d \n", UPDATER_BASIC_FOLDER_PATH, i4_ret));
    }

    return NAVR_OK;
#else

    INT32           i4_ret;
    CHAR            s_path[80];
    FM_FILE_INFO_T  t_file_info;
    CHAR            s_bs_folder_name[16];

    if (!_nav_updater_is_dual_basic_supported())
    {
        return NAVR_OK;
    }

    i4_ret = _nav_updater_get_next_basic_folder(s_bs_folder_name, 16);
    if(i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    /* Create bs1 or bs2 folder in /.basic/ */
    c_strcpy(s_path, UPDATER_BASIC_FOLDER_PATH);
    c_strcat(s_path, "/");
    c_strcat(s_path, s_bs_folder_name);

    i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE,
                                   s_path,
                                   &t_file_info);
    if(i4_ret == FMR_OK)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Existed folder '%s' in %s \n", s_bs_folder_name, UPDATER_BASIC_FOLDER_PATH));
        return NAVR_OK;
    }

    i4_ret = c_fm_create_dir(FM_ROOT_HANDLE,
                             s_path,
                             0777);
    if(i4_ret != FMR_OK)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_fm_create_dir '%s' fail i4_ret = %d \n", s_path, i4_ret));
        return NAVR_FAIL;
    }

    /* Flush file system buffers */
    sync();

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Created folder '%s' in '%s' ok\n", s_bs_folder_name, UPDATER_BASIC_FOLDER_PATH));

    return NAVR_OK;
#endif
}

static INT32 _nav_updater_check_3rd_folder(VOID)
{
    INT32           i4_ret;
    CHAR            s_cmd[128];
    CHAR            s_path[80];
    CHAR            s_3rd_folder_name[16];

    if (!_nav_updater_is_dual_3rd_supported())
    {
        return NAVR_OK;
    }

    i4_ret = _nav_updater_get_next_3rd_folder(s_3rd_folder_name, 16);
    if(i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    /* Create bs1 or bs2 folder in /.basic/ */
    c_strcpy(s_path, UPDATER_3RD_FOLDER_PATH);
    c_strcat(s_path, "/");
    c_strcat(s_path, s_3rd_folder_name);

    i4_ret = access(UPDATER_3RD_FOLDER_PATH, F_OK);
    if (i4_ret == 0)
    {
        c_strcpy(s_cmd, "mkdir ");
        c_strcat(s_cmd, s_path);
        i4_ret = system(s_cmd);
        if (i4_ret == 0)
        {
            /* Flush file system buffers */
            sync();

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Created folder '%s' ok\n", s_path));
        }
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"access folder '%s' failed, i4_ret=%d \n", UPDATER_3RD_FOLDER_PATH, i4_ret));
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_write_remote_ozmo_version
 *
 * Description:
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_write_remote_ozmo_version( UINT32             ui4_idx )
{
    UPDATER_CTRL_T*    pt_this    = &t_g_updater_ctrl;
    CHAR               c_current_version[128] = {0};
    int                fd;

    if ((fd = open(WIFI_REMOTE_SOFTWARE_OZMO_VER_INFO_FNAME, O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create file %s fail!!\n",WIFI_REMOTE_SOFTWARE_OZMO_VER_INFO_FNAME));
        return NAVR_FAIL;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"TAG - %s version is %s\n", pt_this->t_upg_fw_info.pt_item[ui4_idx].s_tag,pt_this->t_upg_fw_info.pt_item[ui4_idx].s_ver));

    c_sprintf( c_current_version, "%s\n",pt_this->t_upg_fw_info.pt_item[ui4_idx].s_ver );
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"the version info write to file %s is %s\n", WIFI_REMOTE_SOFTWARE_OZMO_VER_INFO_FNAME,c_current_version));

    write(fd,c_current_version,( (UINT32)c_strlen( ( const CHAR * )c_current_version ) ));
    fsync(fd);
    close(fd);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_decompress_tgz_file
 *
 * Description: untar .tgz file to specical directory, and delete .tgz file.
 *              This function should be called after upgrade completed one.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_reg_agent_decompress_tgz_file(
    VOID*                 pv_data,
    SIZE_T                z_data_len
)
{
    UPDATER_CTRL_T*    pt_this    = &t_g_updater_ctrl;
    INT32              i4_ret;
    UINT32             ui4_idx = *((UINT32*)pv_data);;
    struct stat     sDirInfo;

    if (ui4_idx >= pt_this->t_upg_fw_info.ui4_item_num)
    {
        return;
    }

    if (UPDATER_METHOD_FILE == pt_this->t_upg_fw_info.pt_item[ui4_idx].e_method)
    {
        CHAR       s_bs_folder_name[16];
        CHAR       s_3rd_folder_name[16];
        CHAR       sz_cmd[128] = {0};
        UINT32     ui4_len = 0;

        ui4_len = c_strlen(pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path);
        if (ui4_len <= 4)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Not a tgz file: '%s' \n", pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path));
            return ;
        }

        /* Check file whether is tgz file */
        if (c_strncmp(".tgz", (const CHAR *)&pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path[ui4_len - 4], 4) == 0)
        {
            if (c_strcmp(pt_this->t_upg_fw_info.pt_item[ui4_idx].s_tag, "3rdp") == 0)
            {
                if (!_nav_updater_is_dual_3rd_supported())
                {
                    /* Decompress 3rd.tgz to /3rd/ */
                    c_strcpy(sz_cmd, "tar -zxf");
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path); /* .tgz file name */
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, "-C");
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, "/3rd");
                    if (0 == system(sz_cmd))
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress OK - %s \n", sz_cmd));
                    }
                    else
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress Fails - %s \n", sz_cmd));
                    }
                }
                else
                {
                    i4_ret = _nav_updater_get_next_3rd_folder(s_3rd_folder_name, 16);
                    if(i4_ret != NAVR_OK)
                    {
                        return;
                    }

                    /* Remove all files in pre bs folder to avoid space not enought! */
                    if (!b_g_clean_3rd_files)
                    {
                        b_g_clean_3rd_files = TRUE;

                        c_strcpy(sz_cmd, "rm -r -f ");
                        c_strcat(sz_cmd, UPDATER_3RD_FOLDER_PATH);
                        c_strcat(sz_cmd, "/");
                        c_strcat(sz_cmd, s_3rd_folder_name);
                        c_strcat(sz_cmd, "/*");
                        i4_ret = system(sz_cmd);
                    }

                    /* Check folder exist or not, if not then to create it */
                    _nav_updater_check_3rd_folder();

                    /* Decompress 3rd.tgz to /3rd/ */
                    c_strcpy(sz_cmd, "tar -zxf");
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path); /* .tgz file name */
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, "-C");
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, UPDATER_3RD_FOLDER_PATH);
                    c_strcat(sz_cmd, "/");
                    c_strcat(sz_cmd, s_3rd_folder_name);
                    if (0 == system(sz_cmd))
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress OK - %s \n", sz_cmd));

#ifdef NAV_UPDATER_TOGGLE_DUAL_BANK_AT_COMPLETED_ALL
                        b_g_tar_3rd_ok = TRUE;
#else
                        /* Upgrade completed, should create a expire flag file */
                        _nav_updater_create_expire_file_in_3rd();
#endif
                    }
                    else
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress Fails - %s \n", sz_cmd));
                    }
                }
            }
            else if (c_strcmp(pt_this->t_upg_fw_info.pt_item[ui4_idx].s_tag, "tvap") == 0)
            {
                if (!_nav_updater_is_dual_basic_supported())
                {
                    /* Decompress basic.tgz to /.basic/bs1/ or /.basic/bs2/ */
                    c_strcpy(sz_cmd, "tar -zxf");
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path); /* .tgz file name */
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, "-C");
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, "/basic");
                    if (0 == system(sz_cmd))
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress OK - %s \n", sz_cmd));
                    }
                    else
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress Fails - %s \n", sz_cmd));
                    }
                }
                else
                {
                    i4_ret = _nav_updater_get_next_basic_folder(s_bs_folder_name, 16);
                    if(i4_ret != NAVR_OK)
                    {
                        return;
                    }

                    /* Remove all files in pre bs folder to avoid space not enought! */
                    if (!b_g_clean_bs_files)
                    {
                        b_g_clean_bs_files = TRUE;

                        c_strcpy(sz_cmd, "rm -r -f ");
                        c_strcat(sz_cmd, UPDATER_BASIC_FOLDER_PATH);
                        c_strcat(sz_cmd, "/");
                        c_strcat(sz_cmd, s_bs_folder_name);
                        c_strcat(sz_cmd, "/*");
                        i4_ret = system(sz_cmd);
                    }

                    /* Check folder exist or not, if not then to create it */
                    _nav_updater_check_basic_folder();

                    /* Decompress basic.tgz to /.basic/bs1/ or /.basic/bs2/ */
                    c_strcpy(sz_cmd, "tar -zxf");
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path); /* .tgz file name */
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, "-C");
                    c_strcat(sz_cmd, " ");
                    c_strcat(sz_cmd, UPDATER_BASIC_FOLDER_PATH);
                    c_strcat(sz_cmd, "/");
                    c_strcat(sz_cmd, s_bs_folder_name);
                    if (0 == system(sz_cmd))
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress OK - %s \n", sz_cmd));

#ifdef NAV_UPDATER_TOGGLE_DUAL_BANK_AT_COMPLETED_ALL
                        b_g_tar_basic_ok = TRUE;
#else
                        /* Upgrade completed, should create a expire flag file */
                        _nav_updater_create_expire_file_in_basic();
#endif
                    }
                    else
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress Fails - %s \n", sz_cmd));
                    }
                }
            }
            else if (c_strcmp(pt_this->t_upg_fw_info.pt_item[ui4_idx].s_tag, UPDATER_OPERA_CA_TAG_NAME) == 0)
            {
                /* check the path dir exist or not, if not exist should create it first*/


                /* if the dir/3rd_rw/opera/opera_home/ do not exsit should make it first*/
                i4_ret = access(UPDATER_OPERA_CA_FDIR, F_OK);
                if (i4_ret != 0)
                {
                    if (mkdir(UPDATER_OPERA_CA_FDIR, 0777) == -1)
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create dir %s fail!!\n",UPDATER_OPERA_CA_FDIR));
                    }
                }

                /* Decompress ozmo.tgz to /3rd_rw/ozmo_sw */
                c_strcpy(sz_cmd, "tar -zxf");
                c_strcat(sz_cmd, " ");
                c_strcat(sz_cmd, pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path); /* .tgz file name */
                c_strcat(sz_cmd, " ");
                c_strcat(sz_cmd, "-C");
                c_strcat(sz_cmd, " ");
                c_strcat(sz_cmd, UPDATER_OPERA_CA_FDIR);

                if (0 == system(sz_cmd))
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress OK - %s \n", sz_cmd));
                }
                else
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress Fails - %s \n", sz_cmd));
                }

            }
            else if ((c_strcmp(pt_this->t_upg_fw_info.pt_item[ui4_idx].s_tag, "ozmo") == 0) &&
                      a_cfg_custom_get_wifi_remote_support())
            {

                /* if the dir /3rd_rw/remote do not exsit should make it first*/
                i4_ret = access(WIFI_REMOTE_OZMO_SOFTWARE_FDIR, F_OK);
                if (i4_ret != 0)
                {
                    if (mkdir(WIFI_REMOTE_OZMO_SOFTWARE_FDIR, 0777) == -1)
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create dir %s fail!!\n",WIFI_REMOTE_OZMO_SOFTWARE_FDIR));
                    }
                }


                /* clean the content that is in the path:/3rd_rw/ozmo_sw*/
                c_strcpy(sz_cmd, "rm -r -f ");
                c_strcat(sz_cmd, WIFI_REMOTE_OZMO_SOFTWARE_FDIR);
                c_strcat(sz_cmd, "/*");
                i4_ret = system(sz_cmd);

                if (0 == i4_ret)
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"run the cmd %s successful \n", sz_cmd));
                }
                else
                {
                     NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"run the cmd %s fail \n", sz_cmd));
                }


                /* Decompress ozmo.tgz to /3rd_rw/ozmo_sw */
                c_strcpy(sz_cmd, "tar -zxf");
                c_strcat(sz_cmd, " ");
                c_strcat(sz_cmd, pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path); /* .tgz file name */
                c_strcat(sz_cmd, " ");
                c_strcat(sz_cmd, "-C");
                c_strcat(sz_cmd, " ");
                c_strcat(sz_cmd, WIFI_REMOTE_OZMO_SOFTWARE_FDIR);

                if (0 == system(sz_cmd))
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress OK - %s \n", sz_cmd));


                    if ( 0 == stat( WIFI_REMOTE_SOFTWARE_OZMO_FNAME, &sDirInfo ))
                    {
                        /* updater the remote software ozmo version info*/
                        _nav_updater_write_remote_ozmo_version(ui4_idx);
                    }
                    else
                    {
                        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"The %s file do not exist!!\n",WIFI_REMOTE_SOFTWARE_OZMO_FNAME));
                    }


                }
                else
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Decompress Fails - %s \n", sz_cmd));
                }
            }
            else
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Unkown Tag - %s \n", pt_this->t_upg_fw_info.pt_item[ui4_idx].s_tag));
                return;
            }

            /* delete tgz file */
            c_fm_delete_file(FM_ROOT_HANDLE, pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path);
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Delete '%s' \n", pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path));

            /* Flush file system buffers */
            sync();
        }
        else if (c_strcmp(pt_this->t_upg_fw_info.pt_item[ui4_idx].s_tag, "ozmo") == 0)
        {
            if (a_cfg_custom_get_wifi_remote_support())
                {
            /* if the dir /3rd_rw/remote do not exsit should make it first*/
            i4_ret = access(WIFI_REMOTE_OZMO_SOFTWARE_FDIR, F_OK);
            if (i4_ret != 0)
            {
                if (mkdir(WIFI_REMOTE_OZMO_SOFTWARE_FDIR, 0777) == -1)
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create dir %s fail!!\n",WIFI_REMOTE_OZMO_SOFTWARE_FDIR));
                }
            }


            /* clean the content that is in the path:/3rd_rw/ozmo_sw*/
            c_strcpy(sz_cmd, "rm -r -f ");
            c_strcat(sz_cmd, WIFI_REMOTE_OZMO_SOFTWARE_FDIR);
            c_strcat(sz_cmd, "/*");
            i4_ret = system(sz_cmd);

            if (0 == i4_ret)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"run the cmd %s successful \n", sz_cmd));
            }
            else
            {
                 NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"run the cmd %s fail \n", sz_cmd));
            }

            /* Decompress ozmo.tgz to /3rd_rw/ozmo_sw */
            c_strcpy(sz_cmd, "mv");
            c_strcat(sz_cmd, " ");
            c_strcat(sz_cmd, pt_this->t_upg_fw_info.pt_item[ui4_idx].s_dev_path); /* .tgz file name */
            c_strcat(sz_cmd, " ");
            c_strcat(sz_cmd, WIFI_REMOTE_SOFTWARE_OZMO_FNAME);

            if (0 == system(sz_cmd))
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Move OK - %s \n", sz_cmd));
                sync();

                if ( 0 == stat( WIFI_REMOTE_SOFTWARE_OZMO_FNAME, &sDirInfo ))
                {
                    /* updater the remote software ozmo version info*/
                    _nav_updater_write_remote_ozmo_version(ui4_idx);
                }
                else
                {
                    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"The %s file do not exist!!\n",WIFI_REMOTE_SOFTWARE_OZMO_FNAME));
                }
            }
            else
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"MOve Fails - %s \n", sz_cmd));
            }
        }
        }
        else
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Unkown Tag - %s \n", pt_this->t_upg_fw_info.pt_item[ui4_idx].s_tag));
            return;
        }
    }
}

static INT32 _nav_updater_decompress_tgz_file(UINT32 ui4_item_idx)
{
    UPDATER_CTRL_T*    pt_this    = &t_g_updater_ctrl;
    UINT32             ui4_len = 0;

    if (ui4_item_idx >= pt_this->t_upg_fw_info.ui4_item_num)
    {
        return NAVR_INV_ARG;
    }

    if (UPDATER_METHOD_FILE != pt_this->t_upg_fw_info.pt_item[ui4_item_idx].e_method)
    {
        return NAVR_OK;
    }

    ui4_len = c_strlen(pt_this->t_upg_fw_info.pt_item[ui4_item_idx].s_dev_path);
    if (ui4_len <= 4)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Not a tgz file: '%s' \n", pt_this->t_upg_fw_info.pt_item[ui4_item_idx].s_dev_path));
        return NAVR_OK;
    }

    if ((c_strncmp(".tgz", (const CHAR *)&pt_this->t_upg_fw_info.pt_item[ui4_item_idx].s_dev_path[ui4_len - 4], 4) == 0)
        || (c_strcmp(pt_this->t_upg_fw_info.pt_item[ui4_item_idx].s_tag, "ozmo") == 0))
    {
        a_agent_async_invoke(_nav_updater_reg_agent_decompress_tgz_file, (VOID *)&ui4_item_idx, (SIZE_T)sizeof(UINT32));
    }

    return NAVR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _nav_updater_create_expire_file_in_basic
 *
 * Description: When upgrade completed successfully, the expire flag fle should
 *              be created for rc.local using.
 *              During TV reboot, the rc.local should check this expire flag
 *              and delete it.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_create_expire_file_in_basic(VOID)
{
#if 1
    INT32          i4_ret = 0;
    CHAR           sz_cmd[256] = {0};
    CHAR           auc_path[128] = {0};
    CHAR           s_bs_folder_name[16];

    if (!_nav_updater_is_dual_basic_supported())
    {
        return NAVR_OK;
    }

    i4_ret = _nav_updater_get_next_basic_folder(s_bs_folder_name, 16);
    if(i4_ret != NAVR_OK)
    {
        return NAVR_OK;
    }

    /* Create a 'expire' flag file in /.basic/bs1/ or /.basic/bs2/ */
    c_strcpy(auc_path, UPDATER_BASIC_FOLDER_PATH);
    c_strcat(auc_path, "/");
    c_strcat(auc_path, s_bs_folder_name);
    c_strcat(auc_path, "/");
    c_strcat(auc_path, UPDATER_EXPIRE_FILE_NAME);

    c_strcpy(sz_cmd, "touch ");
    c_strcat(sz_cmd, auc_path);
    i4_ret = system(sz_cmd);
    if(i4_ret == 0)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create '%s' file ok \n", auc_path));

        /* Remove pre 'expire' file */
        c_strcpy(auc_path, UPDATER_BASIC_FOLDER_PATH);
        c_strcat(auc_path, "/");
        if (c_strcmp(s_bs_folder_name, UPDATER_BASIC_A_FOLDER_NAME) == 0)
        {
            c_strcat(auc_path, UPDATER_BASIC_B_FOLDER_NAME);
        }
        else
        {
            c_strcat(auc_path, UPDATER_BASIC_A_FOLDER_NAME);
        }
        c_strcat(auc_path, "/");
        c_strcat(auc_path, UPDATER_EXPIRE_FILE_NAME);

        c_strcpy(sz_cmd, "rm -r -f ");
        c_strcat(sz_cmd, auc_path);
        i4_ret = system(sz_cmd);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Remove '%s', i4_ret = %d \n", auc_path, i4_ret));
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create '%s' fail: '%s', i4_ret=%d \n", auc_path, i4_ret));
    }

    return (NAVR_OK);
#else
    INT32          i4_ret = 0;
    UINT32         ui4_count = 0;
    UINT32         ui4_written = 0;
    HANDLE_T       h_out_file;
    UCHAR          auc_buffer[256] = {0};
    CHAR           auc_path[256] = {0};
    CHAR           s_bs_folder_name[16];

    if (!_nav_updater_is_dual_basic_supported())
    {
        return NAVR_OK;
    }

    i4_ret = _nav_updater_get_next_basic_folder(s_bs_folder_name, 16);
    if(i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }

    /* Create a 'expire' flag file in /.basic/bs1/ or /.basic/bs2/ */
    c_strcpy(auc_path, UPDATER_BASIC_FOLDER_PATH);
    c_strcat(auc_path, "/");
    c_strcat(auc_path, s_bs_folder_name);
    c_strcat(auc_path, "/");
    c_strcat(auc_path, UPDATER_EXPIRE_FILE_NAME);

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       auc_path,
                       (FM_READ_WRITE | FM_OPEN_CREATE),
                       0777,
                       TRUE,
                       &h_out_file);
    if(i4_ret < 0)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create '%s' fail: '%s', i4_ret=%d \n", auc_path, i4_ret));
        return NAVR_OK;
    }

    /* TODO: Set the kernel version info */
    c_strcpy((CHAR*)auc_buffer, "1.0");

    ui4_count = c_strlen((const CHAR*)auc_buffer);

    i4_ret = c_fm_write(h_out_file,
                        ((UINT8*)auc_buffer),
                        ui4_count,
                        &ui4_written);
    if(i4_ret != FMR_OK)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Can't write data into '%s', i4_ret=%d \n", auc_path, i4_ret));
        c_fm_close(h_out_file);
        return NAVR_FAIL;
    }

    c_fm_close(h_out_file);

    /* Flush file system buffers */
    sync();

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create '%s' file ok \n", auc_path));

    return NAVR_OK;
#endif
}

static INT32 _nav_updater_create_expire_file_in_3rd(VOID)
{
    INT32          i4_ret = 0;
    CHAR           sz_cmd[256] = {0};
    CHAR           auc_path[128] = {0};
    CHAR           s_3rd_folder_name[16];

    if (!_nav_updater_is_dual_3rd_supported())
    {
        return NAVR_OK;
    }

    i4_ret = _nav_updater_get_next_3rd_folder(s_3rd_folder_name, 16);
    if(i4_ret != NAVR_OK)
    {
        return NAVR_OK;
    }

    /* Create a 'expire' flag file in /.basic/bs1/ or /.basic/bs2/ */
    c_strcpy(auc_path, UPDATER_3RD_FOLDER_PATH);
    c_strcat(auc_path, "/");
    c_strcat(auc_path, s_3rd_folder_name);
    c_strcat(auc_path, "/");
    c_strcat(auc_path, UPDATER_EXPIRE_FILE_NAME);

    c_strcpy(sz_cmd, "touch ");
    c_strcat(sz_cmd, auc_path);
    i4_ret = system(sz_cmd);
    if(i4_ret == 0)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create '%s' file ok \n", auc_path));

        /* Remove pre 'expire' file */
        c_strcpy(auc_path, UPDATER_3RD_FOLDER_PATH);
        c_strcat(auc_path, "/");
        if (c_strcmp(s_3rd_folder_name, UPDATER_3RD_A_FOLDER_NAME) == 0)
        {
            c_strcat(auc_path, UPDATER_3RD_B_FOLDER_NAME);
        }
        else
        {
            c_strcat(auc_path, UPDATER_3RD_A_FOLDER_NAME);
        }
        c_strcat(auc_path, "/");
        c_strcat(auc_path, UPDATER_EXPIRE_FILE_NAME);

        c_strcpy(sz_cmd, "rm -r -f ");
        c_strcat(sz_cmd, auc_path);
        i4_ret = system(sz_cmd);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Remove '%s', i4_ret = %d \n", auc_path, i4_ret));
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create '%s' fail: '%s', i4_ret=%d \n", auc_path, i4_ret));
    }

    return (NAVR_OK);
}

static INT32 _nav_updater_get_complete_flag(VOID)
{
    INT32 i4_ret;

    if(a_cfg_custom_get_updater_completed_flag())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_get_complete_flag: ok \n"));

        a_icl_custom_set_cust_updater_status (ICL_CUSTOM_UPDATER_FIRST_BOOT_UP);

        i4_ret = a_cfg_custom_set_updater_completed_flag(FALSE);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_get_complete_flag: [reset to FALSE] i4_ret=%d \n", i4_ret));

        return NAVR_OK;
    }

    return NAVR_NOT_EXIST;
}

static INT32 _nav_updater_set_complete_flag(VOID)
{
    INT32 i4_ret;

    a_cfg_custom_updater_completed_trig_fac();

    i4_ret = a_cfg_custom_set_updater_completed_flag(TRUE);
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_cfg_custom_set_updater_completed_flag: [reset to TRUE] i4_ret=%d \n", i4_ret));

    return i4_ret;
}

/*-----------------------------------------------------------------------------
                    public methods implementations
 -----------------------------------------------------------------------------*/
INT32 nav_updater_uli_get_trigger_type(NAV_UPDATER_TRIGGER_TYPE_T   *pe_type)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    *pe_type = pt_this->e_trigger_type;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_get_trigger_type e_trigger_type[%d] \n", *pe_type));

    return NAVR_OK;
}

INT32 nav_updater_uli_set_trigger_type(NAV_UPDATER_TRIGGER_TYPE_T   e_type)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    pt_this->e_trigger_type = e_type;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_set_trigger_type e_trigger_type[%d] \n", e_type));

    return NAVR_OK;
}

INT32 nav_updater_uli_get_user_mode(NAV_UPDATER_USER_MODE_T   *pe_user_mode)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (NULL == pe_user_mode)
    {
        return NAVR_INV_ARG;
    }

    *pe_user_mode = pt_this->e_user_mode;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_get_user_mode e_user_mode[%d] \n", *pe_user_mode));

    return NAVR_OK;
}

INT32 nav_updater_uli_set_user_mode(NAV_UPDATER_USER_MODE_T e_user_mode)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    pt_this->e_user_mode = e_user_mode;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_set_user_mode e_user_mode[%d] \n", e_user_mode));

    return NAVR_OK;
}

INT32 nav_updater_uli_get_update_stage(NAV_UPDATER_RUNNING_STAGE_T  *pe_update_stage)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (NULL == pe_update_stage)
    {
        return NAVR_INV_ARG;
    }

    *pe_update_stage = pt_this->e_update_stage;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_get_update_stage e_update_stage[%d] \n", *pe_update_stage));

    return NAVR_OK;
}

INT32 nav_updater_uli_set_update_stage(NAV_UPDATER_RUNNING_STAGE_T   e_update_stage)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    pt_this->e_update_stage = e_update_stage;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_set_update_stage e_update_stage[%d] \n", e_update_stage));

    return NAVR_OK;
}


INT32 nav_updater_uli_get_fw_status(NAV_UPDATER_FW_STATE_T  *pe_fw_state)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (NULL == pe_fw_state)
    {
        return NAVR_INV_ARG;
    }

    *pe_fw_state = pt_this->e_fw_state;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_get_fw_status e_update_stage[%d] \n", *pe_fw_state));

    return NAVR_OK;
}

INT32 nav_updater_uli_set_fw_status(NAV_UPDATER_FW_STATE_T   e_fw_state)
{
    UPDATER_CTRL_T*                 pt_this = &t_g_updater_ctrl;
    NAV_UPDATE_ULI_UPDATE_STATUS_T  t_update_status = {0};

    pt_this->e_fw_state = e_fw_state;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_set_fw_status e_fw_state[%d] \n", e_fw_state));

    if (CHECK_STATE_CHECKING == e_fw_state)
    {
        t_update_status.ui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_CHECKING;
    }
    else if (CHECK_STATE_CHECK_AVALIABLE == e_fw_state)
    {
        t_update_status.ui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_FW_FOUND;
    }
    else if (CHECK_STATE_DOWNLOADING == e_fw_state)
    {
        t_update_status.ui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_DOWNLOADING;
        t_update_status.ui1_progress = pt_this->ui1_fw_download_progress;
    }
    else if (CHECK_STATE_DOWNLOAD_SUCESS == e_fw_state)
    {

        t_update_status.ui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_DOWNLOADING;
        t_update_status.ui1_progress = 100;
    }
    else if ((CHECK_STATE_FW_VALIDATING == e_fw_state)
           ||(CHECK_STATE_FW_PARSING == e_fw_state)
           ||(CHECK_STATE_FW_INITED == e_fw_state)
           ||(CHECK_STATE_CHECK_INSTALLING == e_fw_state))
    {
        t_update_status.ui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_APPLYING;
        t_update_status.ui1_progress = pt_this->ui1_progress;
    }
    else if (CHECK_STATE_CHECK_INSTALLED == e_fw_state)
    {
        t_update_status.ui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_FINISHED;
    }
    else if(CHECK_STATE_DOWNLOAD_FAIL == e_fw_state)
    {
        t_update_status.ui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_FAIL;
    }
    else if (CHECK_STATE_NONE == e_fw_state)
    {
        t_update_status.ui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_NONE;
    }

    /* Notify rest python of update status */
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_set_fw_status ui1_update_status[%d], ui1_progress[%d]\n",
                   t_update_status.ui1_update_status, t_update_status.ui1_progress));
    rest_event_notify_ex("uli/update_status", (VOID*)&t_update_status);

    return NAVR_OK;
}

INT32 nav_updater_uli_get_fw_avaliable(NAV_UPDATER_FW_STATE_T  *pe_fw_state)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (NULL == pe_fw_state)
    {
        return NAVR_INV_ARG;
    }

    *pe_fw_state = pt_this->e_fw_check_avaliable;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_get_fw_avalable e_update_stage[%d] \n", *pe_fw_state));

    return NAVR_OK;
}

INT32 nav_updater_uli_set_fw_avaliable(NAV_UPDATER_FW_STATE_T   e_fw_state)
{
    INT32                        i4_ret = 0;
    CHAR                         s_ver[64] = {0};
    UPDATER_CTRL_T*              pt_this = &t_g_updater_ctrl;
    NAV_UPDATE_ULI_AVAIL_INFO_T  t_avail_info = {0};

    pt_this->e_fw_check_avaliable = e_fw_state;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_set_fw_avaliable e_fw_state[%d] \n", e_fw_state));

    if (CHECK_STATE_CHECK_AVALIABLE == e_fw_state)
    {
         t_avail_info.ui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_YES;
    }
    else
    {
         t_avail_info.ui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_NO;
    }

    t_avail_info.ui_fw_policy = NAV_UPDATE_FW_POLICY_DEFAULT;

    i4_ret = nav_updater_get_update_ver_string(s_ver);

    if (NAVR_OK == i4_ret)
    {
        c_memset(t_avail_info.s_ver, 0, 64);
        c_strncpy(t_avail_info.s_ver, s_ver, 63);
    }
    else
    {
        /*default*/
        c_strncpy(t_avail_info.s_ver, "1.0", 63);
    }

    if (NAV_UPDATE_FW_AVALIABLE_SATUS_YES == t_avail_info.ui1_fw_status)
    {
        /* Notify rest python when update available */

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_set_fw_avaliable ui1_fw_status[%d], s_ver[%s]\n",
                       t_avail_info.ui1_fw_status, t_avail_info.s_ver));
        rest_event_notify_ex("uli/available_update_info", (VOID*)&t_avail_info);
    }

    return NAVR_OK;
}

INT32 nav_updater_uli_get_fw_force_update_flag(BOOL   *pb_force_state)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (NULL == pb_force_state)
    {
        return NAVR_INV_ARG;
    }

    *pb_force_state = pt_this->b_is_force_update;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_get_fw_force_update_flag b_is_force_update[%d] \n", *pb_force_state));

    return NAVR_OK;
}

INT32 nav_updater_uli_set_fw_force_update_flag(BOOL   b_force_state)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    pt_this->b_is_force_update = b_force_state;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_uli_set_fw_force_update_flag b_force_state[%d] \n", b_force_state));

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_init
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
INT32 nav_updater_init(
    const UPDATER_CONFIG_T*    pt_updater_cfg
)
{
    UPDATER_CTRL_T*            pt_this = &t_g_updater_ctrl;

    pt_this->pt_updater_cfg = (UPDATER_CONFIG_T *)pt_updater_cfg;

    _nav_updater_dual_folder_init();

    return (NAVR_OK);
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_update_info
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
INT32 nav_updater_update_info(
    UINT8               ui1_status
)
{
    UPDATER_STATUS_T    e_status        = (UPDATER_STATUS_T) ui1_status;
    UINT8               ui1_info_status = ICL_USB_UPGRADE_STATUS_NONE;
    INT32               i4_ret          = 0;

    switch (e_status)
    {
        case UPDATER_STATUS_CLEAR:
        case UPDATER_STATUS_CHCKING:
        default:
            ui1_info_status = ICL_USB_UPGRADE_STATUS_NONE;
            break;

        case UPDATER_STATUS_SHOW_UI:
        case UPDATER_STATUS_EXECING:
        case UPDATER_STATUS_EXEC_DONE:
            ui1_info_status = ICL_USB_UPGRADE_STATUS_RUNNING;
            break;
    }

    a_fw_updater_set_updater_status(e_status);

    i4_ret = a_icl_set(
                (ICL_ID_TYPE) ICL_MAKE_ID(ICL_GRPID_USB_UPGRADE, ICL_RECID_USB_UPGRADE_STATUS),
                (VOID*) &ui1_info_status,
                ICL_RECID_USB_UPGRADE_STATUS_SIZE);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"ICL_SET ret = %d\n", i4_ret));
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_request_update
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
INT32 nav_updater_request_update(
    BOOL*              pb_delay_start
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

	CHAR  s_active_name [APP_NAME_MAX_LEN+1]= {0};
	a_am_get_active_app(s_active_name);
    if (NULL == pb_delay_start)
    {
        return NAVR_FAIL;
    }

    /* set FALSE by default */
    *pb_delay_start = FALSE;

    if (TRUE == pt_this->b_is_updater_triggered)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_request_update Reject[Alread running]\n"));
        return NAVR_FAIL;
    }

    if (FALSE == _nav_updater_is_break_in_avail())
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_request_update Reject[avail check fail]\n"));
        return NAVR_FAIL;
    }

    if (FALSE == _nav_updater_is_bgm())
    {
		if ((FALSE == nav_is_active())&&
		!(c_strcmp(s_active_name, "mscvt")==0))

        {
            if (TRUE == _nav_updater_is_waiting_app_exit())
            {
                *pb_delay_start = TRUE;
            }

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_request_update Reject[Other app running]\n"));

            return NAVR_FAIL;
        }
    }

    return NAVR_OK;
}

BOOL nav_updater_is_running(VOID)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    NAV_UPGRADE_LOG_PRINT(("\n[NAV_UPDATER] nav_updater_is_running b_is_updater_triggered[%d]\n",
        pt_this->b_is_updater_triggered));

    return (pt_this->b_is_updater_triggered);
}


/*----------------------------------------------------------------------------
 * Name: nav_updater_trigger_update
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
INT32 nav_updater_trigger_update(
    UPDATER_DLIVRY_TYPE_T         e_type
)
{
    UPDATER_CTRL_T*               pt_this = &t_g_updater_ctrl;
    UPDATER_DLIVRY_HDLR_REG_T*    pt_tmp_hdlr_reg;
    NAV_UPDATER_TRIGGER_TYPE_T    e_trigger_type = TRIGGER_TYPE_NONE;
    NAV_UPDATER_USER_MODE_T       e_user_mode = USER_MODE_NONE;
    BOOL                          b_found = FALSE;

    nav_updater_uli_get_trigger_type(&e_trigger_type);
    nav_updater_uli_get_user_mode(&e_user_mode);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger_update: e_type[%d],e_trigger_type[%d],e_user_mode[%d]\n",
                   e_type,e_trigger_type,e_user_mode));
#if 0
    /* this case the system is alread in install status*/
    if (TRIGGER_TYPE_ULI_NETWORK_FW_INSTALL == e_trigger_type)
    {
         NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger_update Break[FW Install is running]\n"));
         return NAVR_OK;
    }
#endif

    if (pt_this->pt_curr_dlivry_hdlr)
    {
        if (UPDATER_DLIVRY_TYPE_SYS == pt_this->pt_curr_dlivry_hdlr->e_type)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger_update Break[FW Install is running]\n"));
            return NAVR_OK;
        }
    }

    /* check if the handler is exist */
    SLIST_FOR_EACH(pt_tmp_hdlr_reg, &(pt_this->t_hdlr_reg_list), t_link)
    {
        if (pt_tmp_hdlr_reg->e_type == e_type)
        {
            b_found = TRUE;
            pt_this->pt_curr_dlivry_hdlr = pt_tmp_hdlr_reg;

            break;
        }
    }

    if (FALSE == b_found)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger_update Break[No dlivry_hdlr found]\n"));
        return NAVR_FAIL;
    }

    /* turn on the triggered flag */
    if(TRIGGER_TYPE_ULI_NETWORK_FW_CHECK != e_trigger_type)
    {
        pt_this->b_is_updater_triggered = TRUE;
    }

    /* turn off the abort flag if needed */
    if (TRUE == pt_this->b_is_abort)
    {
        pt_this->b_is_abort = FALSE;
    }
	NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger_update e_type:%d \n",e_type));

    if (e_type == UPDATER_DLIVRY_TYPE_USB)
    {
        /* grab activation */
        if (FALSE == _nav_updater_is_bgm())
        {
            nav_grab_activation(NAV_COMP_ID_UPDATER);
        }

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger_update Break[UPDATER_DLIVRY_TYPE_USB]\n"));
        return NAVR_OK;
    }

    nav_updater_update_info((UINT8)UPDATER_STATUS_CHCKING);

    /* grab activation */
    if ((FALSE == _nav_updater_is_bgm())
        && (USER_MODE_NORMAL == e_user_mode))
    {
        nav_grab_activation(NAV_COMP_ID_UPDATER);
/*
        if (e_type == UPDATER_DLIVRY_TYPE_ULI)
        {
            nav_updater_uli_progress_show();
        }
*/
        if (e_type == UPDATER_DLIVRY_TYPE_SYS)
        {
            a_amb_enable_system_key(FALSE);
            pt_this->b_is_svc_stop = FALSE;
            _nav_updater_stop_video();
        }

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger_update e_user_mode[Normal]\n"));
    }
#ifdef APP_BASIC_RO
/*
    nav_updater_remount_rw(UPDATER_REMOUNT_TYPE_BASIC);
    nav_updater_remount_rw(UPDATER_REMOUNT_TYPE_3RD);
*/
#endif
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger_update CHG_COND[UPDATER_COND_PREPROCESSING]\n"));

    /* change current status to UPDATER_COND_UPDATER_COND_PREPROCESSING */
    _nav_updater_cnd_chg(UPDATER_COND_PREPROCESSING);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_trigger_update
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
INT32 nav_updater_reg_dlivry_hdlr(
    UPDATER_DLIVRY_HDLR_REG_T*    pt_reg
)
{
    UPDATER_CTRL_T*               pt_this = &t_g_updater_ctrl;
    UPDATER_DLIVRY_HDLR_REG_T*    pt_tmp_hdlr_reg;

    if (pt_reg == NULL)
    {
        return NAVR_FAIL;
    }

    /* check if the handler is exist */
    SLIST_FOR_EACH(pt_tmp_hdlr_reg, &(pt_this->t_hdlr_reg_list), t_link)
    {
        if (pt_tmp_hdlr_reg->e_type == pt_reg->e_type)
        {
            return NAVR_FAIL;
        }
    }

    /* malloc node */
    pt_tmp_hdlr_reg = c_mem_alloc(sizeof(UPDATER_DLIVRY_HDLR_REG_T));
    if (pt_tmp_hdlr_reg == NULL)
    {
        return NAVR_FAIL;
    }

    /* fill data */
    c_memset(pt_tmp_hdlr_reg, 0, sizeof(UPDATER_DLIVRY_HDLR_REG_T));
    c_memcpy(pt_tmp_hdlr_reg, pt_reg, sizeof(UPDATER_DLIVRY_HDLR_REG_T));

    /* add new node */
    SLIST_INSERT_HEAD(pt_tmp_hdlr_reg, &(pt_this->t_hdlr_reg_list), t_link);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_enter_bgm
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
VOID nav_updater_enter_bgm(
    BOOL               b_bgm
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if ((TRUE == _nav_updater_is_bgm()) && (FALSE == b_bgm))
    {
        nav_grab_activation(NAV_COMP_ID_UPDATER);

        /* trigger UI update */
        pt_this->t_updater_view_hdlr.pf_update_progress(UPDATER_UPDATE_REASON_COND);
    }

    pt_this->b_is_bgm = b_bgm;

    return;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_do_abort
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
VOID nav_updater_do_abort(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
    BOOL               b_is_updating_status = FALSE;

    if (_nav_updater_is_rebooting_system())
    {
        return;
    }

    a_nav_updater_is_updating_status(
        &b_is_updating_status
    );

    if (b_is_updating_status)
    {
        /* If in BGM updating, then press Power ON, skip to abort and let updating go on!! */
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_do_abort() is skiped b_is_updating_status[TRUE]\n"));
        return;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_do_abort() is called\n"));

    /* rollback to normal */
    _nav_updater_cnd_chg(UPDATER_COND_INIT);

    /* reset fw_status */
    nav_updater_uli_set_fw_status(CHECK_STATE_NONE);

    /* change the component visibility state */
    nav_hide_component(NAV_COMP_ID_UPDATER);

    pt_this->b_is_abort = TRUE;

    return;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_integrity_chk
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
INT32 nav_updater_integrity_chk(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (NULL != pt_this->pt_updater_cfg->pf_integrity_chk)
    {
        return pt_this->pt_updater_cfg->pf_integrity_chk(pt_this);
    }

    return NAVR_NO_ACTION;;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_show_dialog
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
INT32 nav_updater_show_dialog(
    UPDATER_SHOW_DLG_TYPE_T e_type,
    UTF16_T*                w2s_text
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
    UINT16 ui2_status = 0;

    /*check the wizard status*/
    if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK
                            && (WZD_UTIL_GET_STATUS_STATE(ui2_status) == WZD_STATE_RESUME_C4TV))
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_show_dialog() Break[Wizard_ON]\n"));
        return NAVR_NO_ACTION;
    }

    if (NULL != pt_this->t_updater_view_hdlr.pf_show_dialog)
    {
        if (e_type != UPDATER_SHOW_DLG_TYPE_UPGRADE_COMPLETE)
        {
            nav_enable_scrn_svr(FALSE);
        }

        return pt_this->t_updater_view_hdlr.pf_show_dialog(e_type, w2s_text);
    }

    return NAVR_NO_ACTION;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_hide_dialog
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
INT32 nav_updater_hide_dialog(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    if (NULL != pt_this->t_updater_view_hdlr.pf_hide_dialog)
    {
        pt_this->t_updater_view_hdlr.pf_hide_dialog();

        nav_enable_scrn_svr(TRUE);
    }

    return NAVR_NO_ACTION;
}

static BOOL _nav_updater_is_3rd_part_ready(
    VOID
)
{
    FM_FS_INFO_T    t_fm_fs_info;
    INT32           i4_ret;

    i4_ret = c_fm_get_fs_info(FM_ROOT_HANDLE,
                              "/3rd",
                              &t_fm_fs_info);
    if (FMR_OK != i4_ret)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL nav_updater_is_3rd_rw_part_ready(
    VOID
)
{
    FM_FS_INFO_T    t_fm_fs_info;
    INT32           i4_ret;

    i4_ret = c_fm_get_fs_info(FM_ROOT_HANDLE,
                              "/data",
                              &t_fm_fs_info);
    if (FMR_OK != i4_ret)
    {
        return FALSE;
    }

    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: nav_updater_is_bgm_ex
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL nav_updater_is_bgm_ex(
    VOID
)
{
    UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;

    return (pt_this->b_is_bgm);
}



BOOL nav_updater_pkgfile_existed_in_tv(VOID)
{
    CHAR            sz_src_file[128]={0};
    //UINT8           ui1_retry = 0;
    FM_FILE_INFO_T  t_info;
	#if 0
    /* make sure the 3rd partition is already mounted!! */
    do
    {
        if (TRUE == _nav_updater_is_3rd_part_ready())
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"[pkgfile_existed_in_tv] 3rd part was ready!, ui1_retry=%d\n", ui1_retry));
            break;
        }
        c_thread_delay(1000);
        ui1_retry++;
    } while(ui1_retry < 10);
	#endif
    c_strcpy(sz_src_file, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_INTEGRITY_OK_NAME);
    if (FMR_OK == c_fm_get_info_by_name(FM_ROOT_HANDLE, sz_src_file, &t_info))
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"'%s' existed in TV\n", sz_src_file));

#if 0
        /* do integrity check */
        i4_ret = c_dlm_integrity_check(sz_src_file, NULL);
        if(DLM_OK == i4_ret)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_dlm_integrity_check: i4_ret = %d \n", i4_ret));
            return TRUE;
        }
#else
        return TRUE;
#endif
    }

    return (FALSE);
}

INT32 nav_updater_reboot_system(VOID)
{
    b_g_is_rebooting = TRUE;
#ifdef APP_BASIC_RO
    nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_BASIC);
    /* nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_3RD); */
#endif
    /* delay 3s */
    c_thread_delay(3000);
    a_cfg_cust_set_force_reboot_up_flag(ACFG_FORCE_REBOOT_UP_ON);

    a_amb_reboot();

    return NAVR_OK;
}

static BOOL _nav_updater_is_rebooting_system(VOID)
{
    return (b_g_is_rebooting);
}

static INT32 _nav_updater_set_old_fw_version(VOID)
{
    INT32           i4_ret;
    CHAR            s_path[UPDATER_DEV_PATH_LEN];
    CHAR            s_3rd_folder_name[16];
    CHAR            s_ver[UPDATER_VERSION_LEN+1];

    if (_nav_updater_is_dual_3rd_supported())
    {
        i4_ret = _nav_updater_get_next_3rd_folder(s_3rd_folder_name, 16);
        if(i4_ret != NAVR_OK)
        {
            return NAVR_FAIL;
        }

        c_strcpy(s_path, UPDATER_3RD_FOLDER_PATH);
        c_strcat(s_path, "/");
        c_strcat(s_path, s_3rd_folder_name);
    }
    else
    {
        c_strcpy(s_path, UPDATER_OLD_FW_VERSION_FILE_NAME);
    }

    c_strcpy(s_ver, sys_cust_get_usb_upg_version());

    a_fw_updater_set_old_fw_ver(s_path, s_ver, c_strlen(s_ver));

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
                    exported methods implementations
 -----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Name: a_nav_updater_is_updating_status
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_nav_updater_is_updating_status(
    BOOL*                         pb_is_updating_status
)
{
    UPDATER_CTRL_T*         pt_this = &t_g_updater_ctrl;

    if (NULL== pb_is_updating_status)
    {
        return NAVR_FAIL;
    }


    if((UPDATER_COND_VALIDATING == pt_this->e_cond)
                || (UPDATER_COND_PARSING == pt_this->e_cond)
                || (UPDATER_COND_INITED == pt_this->e_cond)
                || (UPDATER_COND_DOWNLOADING == pt_this->e_cond)
                || (UPDATER_COND_COMPLETE_ONE == pt_this->e_cond))
    {
        *pb_is_updating_status = TRUE;
    }
    else
    {
        *pb_is_updating_status = FALSE;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name: a_nav_updater_iom_all_key_locked
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_nav_updater_iom_all_key_locked(BOOL b_is_to_lock,BOOL b_is_power_lock)
{


    INT32   i4_ret = 0;
    DISABLE_EVTCODE_T   t_disable_evtcode;
    c_memset (&t_disable_evtcode, 0, sizeof(DISABLE_EVTCODE_T));
    t_disable_evtcode.b_positive_filter = TRUE;
    t_disable_evtcode.pui4_evtcode_arr = aui4_evtcode_ignore_arr_ex;
    if(b_all_key_disable&&b_is_to_lock&&b_is_power_lock)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"all key is disable,so no need \n"));
        return NAVR_OK;
    }
    if((!b_is_to_lock)||(b_is_to_lock&&b_is_power_lock))
    {
        aui4_evtcode_ignore_arr_ex[0] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_POWER);
        aui4_evtcode_ignore_arr_ex[1] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_POWER);
    }
    else
    {
        aui4_evtcode_ignore_arr_ex[0] = 0;
        aui4_evtcode_ignore_arr_ex[1] = 0;
    }
    aui4_evtcode_ignore_arr_ex[2] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_VOL_UP);
    aui4_evtcode_ignore_arr_ex[3] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP);
    aui4_evtcode_ignore_arr_ex[4] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_VOL_DOWN);
    aui4_evtcode_ignore_arr_ex[5] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN);
    aui4_evtcode_ignore_arr_ex[6] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_INPUT_SRC);
    aui4_evtcode_ignore_arr_ex[7] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_INPUT_SRC);
    aui4_evtcode_ignore_arr_ex[8] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_MENU);
    aui4_evtcode_ignore_arr_ex[9] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_EXIT);
    aui4_evtcode_ignore_arr_ex[10] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_RETURN);
    aui4_evtcode_ignore_arr_ex[11] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_PRG_INFO);
    aui4_evtcode_ignore_arr_ex[12] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_PRG_UP);
    aui4_evtcode_ignore_arr_ex[13] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_PRG_DOWN);
    aui4_evtcode_ignore_arr_ex[14] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_CC);
    aui4_evtcode_ignore_arr_ex[15] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_P_EFFECT);
    aui4_evtcode_ignore_arr_ex[16] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_MUTE);
    aui4_evtcode_ignore_arr_ex[17] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_CURSOR_LEFT);
    aui4_evtcode_ignore_arr_ex[18] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_CURSOR_RIGHT);
    aui4_evtcode_ignore_arr_ex[19] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_CURSOR_UP);
    aui4_evtcode_ignore_arr_ex[20] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_CURSOR_DOWN);
    aui4_evtcode_ignore_arr_ex[21] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_SELECT);
    aui4_evtcode_ignore_arr_ex[22] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_CLEAR);
    aui4_evtcode_ignore_arr_ex[23] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_ASPECT);
    aui4_evtcode_ignore_arr_ex[24] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_KB_MINUS_SIGN);
    aui4_evtcode_ignore_arr_ex[25] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_NETFLIX);
    aui4_evtcode_ignore_arr_ex[26] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_WIDGET);
    aui4_evtcode_ignore_arr_ex[27] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_AMAZON);
    aui4_evtcode_ignore_arr_ex[28] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_VUDU);
    aui4_evtcode_ignore_arr_ex[29] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_XUMO);
    aui4_evtcode_ignore_arr_ex[30] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_IHEART_RADIO);

    t_disable_evtcode.b_enable = b_is_to_lock;

    b_all_key_disable = b_is_to_lock&&b_is_power_lock;
	if(b_all_key_disable)
	{
		a_amb_enable_power_key(FALSE);
	}
	else
	{
		a_amb_enable_power_key(TRUE);
	}
    t_disable_evtcode.z_evtcode_cnt = 26;
    i4_ret = c_iom_set_global_disable_evtcode(&t_disable_evtcode);
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_iom_set_global_disable_evtcode lock i4_ret = %d\n",i4_ret));

    return NAVR_OK;

}
/*-----------------------------------------------------------------------------
 * Name: a_nav_updater_iom_power_key_locked
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_nav_updater_iom_lock_power_key(BOOL b_is_to_lock)
{
    if ((!b_g_power_key_iom_locked)
        &&(b_is_to_lock))
    {
        INT32   i4_ret = 0;
        DISABLE_EVTCODE_T   t_disable_evtcode;
#if 0
        UINT64  ui8_lock_src = 0;
        size_t  z_len = sizeof (UINT64);

        c_iom_get (h_iom,
                   IOM_GET_IRRC_EVT_SRC_MASK,
                   (VOID*)&ui8_lock_src,
                   &z_len);
        ui8_lock_src |= IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL);
        c_iom_set(h_iom,
                      IOM_SET_IRRC_EVT_SRC_MASK,
                      (const VOID*)&ui8_lock_src,
                      sizeof(UINT64));
#endif

        c_memset (&t_disable_evtcode, 0, sizeof(DISABLE_EVTCODE_T));
        t_disable_evtcode.b_positive_filter = TRUE;
        t_disable_evtcode.pui4_evtcode_arr = aui4_evtcode_arr_ex;

        aui4_evtcode_arr_ex[0] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_POWER);
        aui4_evtcode_arr_ex[1] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_POWER);
        aui4_evtcode_arr_ex[2] = 0;

        t_disable_evtcode.b_enable = TRUE;
        t_disable_evtcode.z_evtcode_cnt = 3;

        i4_ret = c_iom_set_global_disable_evtcode(&t_disable_evtcode);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_iom_set_global_disable_evtcode lock i4_ret = %d\n",i4_ret));

        if (i4_ret == IOMR_OK)
        {
            b_g_power_key_iom_locked = TRUE;
        }

    }

    if ((b_g_power_key_iom_locked)
        && (!b_is_to_lock))
    {
        INT32   i4_ret = 0;
        DISABLE_EVTCODE_T   t_disable_evtcode;
#if 0
        UINT64  ui8_lock_src = 0;
        size_t  z_len = sizeof (UINT64);

        c_iom_get (h_iom,
                   IOM_GET_IRRC_EVT_SRC_MASK,
                   (VOID*)&ui8_lock_src,
                   &z_len);

        ui8_lock_src |= IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL);

        c_iom_set(h_iom,
                      IOM_SET_IRRC_EVT_SRC_MASK,
                      (const VOID*)&ui8_lock_src,
                      sizeof(UINT64));
#endif

        c_memset (&t_disable_evtcode, 0, sizeof(DISABLE_EVTCODE_T));
        t_disable_evtcode.b_positive_filter = TRUE;
        t_disable_evtcode.pui4_evtcode_arr = aui4_evtcode_arr_ex;
        t_disable_evtcode.b_enable = FALSE;
        t_disable_evtcode.z_evtcode_cnt = 3;

        i4_ret = c_iom_set_global_disable_evtcode(&t_disable_evtcode);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_iom_set_global_disable_evtcode unlock i4_ret = %d\n",i4_ret));

        if (i4_ret == IOMR_OK)
        {
            b_g_power_key_iom_locked = FALSE;
        }

    }

    return NAVR_OK;

}


/*-----------------------------------------------------------------------------
 * Name: a_nav_updater_set_power_on_from_bgm_flag
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 a_nav_updater_set_power_on_from_bgm_flag(BOOL b_is_from_bgm)
{
    b_g_power_on_from_bgm = b_is_from_bgm;
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_nav_updater_is_power_on_from_bgm
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL a_nav_updater_is_power_on_from_bgm( VOID )
{
    return b_g_power_on_from_bgm;
}



/*-----------------------------------------------------------------------------
 * Name: _nav_dev_db_query_sys_time_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 _nav_dev_db_query_sys_time_create(VOID)
{
    INT32 i4_ret;
    if (FALSE == b_g_query_sys_time_create)
    {

        if (c_handle_valid(h_query_sys_timer) == TRUE) {
            c_timer_delete(h_query_sys_timer);
        }


        i4_ret = c_timer_create(&(h_query_sys_timer));
        if (i4_ret != OSR_OK) {
            return NAVR_FAIL;
        }
        /* create the query time*/

        b_g_query_sys_time_create = TRUE;
    }


    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: _nav_loop_test_time_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 _nav_loop_test_time_create(VOID)
{
    INT32 i4_ret;
    if (FALSE == b_g_loop_test_time_create)
    {

        if (c_handle_valid(h_loop_test_timer) == TRUE) {
            c_timer_delete(h_loop_test_timer);
        }


        i4_ret = c_timer_create(&(h_loop_test_timer));
        if (i4_ret != OSR_OK) {
            return NAVR_FAIL;
        }
        /* create the query time*/

        b_g_loop_test_time_create = TRUE;
    }


    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_stop_loop_test_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_stop_loop_test_timer(VOID)
{
    INT32 i4_ret;

    if (c_handle_valid(h_loop_test_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(h_loop_test_timer);
    if (i4_ret != OSR_OK) {

    }
}


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_dev_db_stop_sys_query_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_dev_db_stop_sys_query_timer(VOID)
{
    INT32 i4_ret;

    if (c_handle_valid(h_query_sys_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(h_query_sys_timer);
    if (i4_ret != OSR_OK) {

    }
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_is_sys_time_ready
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL _nav_updater_is_sys_time_ready( VOID )
{
    time_t t_current_time = 0;
    t_current_time = time (NULL);

    if (t_current_time < ((time_t)(365 * 24 * 60 * 60)))  /* should one year sec to check the time ready*/
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_dev_db_query_sys_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32     i4_ret;
    if ((nav_updater_is_all_partition_ready())
        && (_nav_updater_is_sys_time_ready()))
    {
        nav_updater_uli_check_provisioning_status();

        if ((a_cfg_custom_get_wifi_remote_support())
            && (nav_updater_is_need_to_check_dev_db()))
      {
        BOOL    b_db_status = FALSE;
        DEV_DB_LOCK_CHECK_COND_T e_check_cond = DEV_DB_LOCK_CHECK_COND_NONE;

        i4_ret = a_dev_db_check_lock_info( e_check_cond, &b_db_status );
        NAV_UPGRADE_LOG_PRINT(("\n[nav_updater_IP] a_dev_db_check_lock_info() i4_ret=%d , check_cond=%d, b_db_status=%d\n", i4_ret, e_check_cond, b_db_status));

       }

        if (FALSE == nav_updater_is_need_to_check_dev_db())
        {
            BOOL                         b_is_updating_status = FALSE;
            i4_ret = a_nav_updater_is_updating_status(
                                    &b_is_updating_status
                                );

            if ((NAVR_OK == i4_ret)
                     && (b_is_updating_status))
            {
                NAV_UPGRADE_LOG_PRINT(("\n[nav_updater_IP] _nav_dev_db_query_sys_timeout b_is_updating_status[TRUE]\n"));
                ui4_g_query_num = 0; /* reset the time query num flag*/
                /* here should just do return */
                return;
            }
        #ifdef APP_ULI_UPG_SUPPORT
            else if (FALSE == nav_updater_is_uli_agent_in_progress())
            {
                NAV_UPGRADE_LOG_PRINT(("\n[nav_updater_IP] _nav_dev_db_query_sys_timeout network_up\n"));
        a_nav_updater_uli_partition_all_query_network_up();

        ui4_g_query_num = 0; /* reset the time query num flag*/
                /* here should just do return */
                return;
            }
        #endif
            else
            {
                NAV_UPGRADE_LOG_PRINT(("\n[nav_updater_IP] _nav_dev_db_query_sys_timeout RECHECK[TRUE]\n"));
            }
    }
    else
    {
            nav_updater_set_check_dev_db_flag(FALSE);
        }

    }
    if ((ui4_g_query_num + 1) >= 60)
        {
            ui4_g_query_num = 0; /* reset the time query num flag*/
        }
        else
        {
            ui4_g_query_num ++;

            _nav_dev_db_query_sys_time_reset();
        }
    }


/*-----------------------------------------------------------------------------
 * Name
 *      _nav_pic_mode_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_dev_db_query_sys_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_dev_db_query_sys_timeout, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_query_sys_time_create
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_dev_db_query_sys_time_reset(VOID)
{
    INT32 i4_ret;

    _nav_dev_db_stop_sys_query_timer();

    if (ui4_g_query_num < 60) /* will query 5min*/
    {
        i4_ret = c_timer_start(
                        h_query_sys_timer,
                        10000,
                        X_TIMER_FLAG_ONCE,
                        _nav_dev_db_query_sys_timer_nfy,
                        NULL
                        );
        if (i4_ret != OSR_OK) {
        }
    }
    return NAVR_FAIL;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_loop_test_timeout
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_loop_test_timeout(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    INT32     i4_ret;
	UINT8 pui1_fw_status = 0;
    UINT8 pui_fw_policy  = 0;
	NAV_UPDATER_FW_STATE_T         e_fw_avaliable_state = CHECK_STATE_NONE;
    NAV_UPDATER_RUNNING_STAGE_T    e_update_stage = STAGE_NONE;
	nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);
    nav_updater_uli_get_update_stage(&e_update_stage);
	 NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"e_fw_avaliable_state:%d e_update_stage:%d ui4_g_loop_test_num:%d \n",e_fw_avaliable_state,e_update_stage,ui4_g_loop_test_num));
	if (STAGE_FW_CHECKING == e_update_stage)
	{
		 NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_loop_test_timeout [BUSY]\n"));
		 nav_updater_loop_test_timer_reset();
		 return;
	}
	else
	{
		  if (CHECK_STATE_CHECK_AVALIABLE == e_fw_avaliable_state ||
		  	  CHECK_STATE_DOWNLOADING == e_fw_avaliable_state ||
		  	  CHECK_STATE_FW_PARSING == e_fw_avaliable_state ||
		  	  CHECK_STATE_FW_VALIDATING == e_fw_avaliable_state)
		  {
			   _nav_stop_loop_test_timer();
			   return;
		  }
		  else
		  {
		  		if(ui4_g_loop_test_num <5)
		  		{
		  			ui4_g_loop_test_num++;
		  			a_nav_updater_check_network_update(&pui1_fw_status,&pui_fw_policy);
			   		nav_updater_loop_test_timer_reset();
		  		}
				else
				{
						_nav_stop_loop_test_timer();
						ui4_g_loop_test_num=0;
				}
			   return;
		  }
	}
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_loop_test_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_loop_test_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_loop_test_timeout, pv_tag, NULL, NULL);
}


/*-----------------------------------------------------------------------------
 * Name: _nav_updater_loop_test_timer_reset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 nav_updater_loop_test_timer_start(VOID)
{
    INT32 i4_ret;

    _nav_loop_test_time_create();
	ui4_g_loop_test_num = 0;

    i4_ret = c_timer_start(
                    h_loop_test_timer,
                    1000*2*60,
                    X_TIMER_FLAG_ONCE,
                    _nav_loop_test_timer_nfy,
                    NULL
                    );
    if (i4_ret != OSR_OK) {
    }

    return NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_loop_test_timer_reset
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 nav_updater_loop_test_timer_reset(VOID)
{
    INT32 i4_ret;

    if (ui4_g_loop_test_num < 5) /* will query 5min*/
    {
        i4_ret = c_timer_start(
                        h_loop_test_timer,
                        1000*2*60,
                        X_TIMER_FLAG_ONCE,
                        _nav_loop_test_timer_nfy,
                        NULL
                        );
        if (i4_ret != OSR_OK) {
        }
    }
    return NAVR_FAIL;
}


BOOL nav_update_is_sys_sw_image_ready(VOID)
{
    INT32                  i4_ret;
    HANDLE_T               h_file;
    CHAR                   sz_src_path[256];
    BOOL                   b_is_ready = FALSE;

    /* Check PKG file exist in TV System */
    c_strcpy(sz_src_path, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_INTEGRITY_OK_NAME);

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       sz_src_path,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_file);

    if (FMR_OK == i4_ret)
    {
        c_fm_close(h_file);

        b_is_ready = TRUE;

    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_update_is_sys_sw_image_ready b_is_ready[%d]\n",b_is_ready));

    return b_is_ready;
}



/*-----------------------------------------------------------------------------
 * Name: nav_dev_db_network_ready_query_time
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 nav_dev_db_network_ready_query_time(VOID)
{
    INT32 i4_ret;
    i4_ret = _nav_dev_db_query_sys_time_create();

    if (NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }
    else
    {
        _nav_dev_db_query_sys_time_reset();
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: nav_updater_is_need_to_check_dev_db
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
BOOL nav_updater_is_need_to_check_dev_db(VOID)
{
    return b_s_is_need_dev_db_check;
}

/*-----------------------------------------------------------------------------
 * Name: nav_updater_set_check_dev_db_flag
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 nav_updater_set_check_dev_db_flag(BOOL   b_is_need_to_check)
{
    b_s_is_need_dev_db_check = b_is_need_to_check;

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_nav_updater_register
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

INT32 a_nav_updater_register(
    UPDATER_VIEW_HDLR_T*    pt_view_hdlr
)
{
    UPDATER_CTRL_T*         pt_this = &t_g_updater_ctrl;
    NAV_COMP_T              t_comp;
    INT32                   i4_ret;

    /* clear t_g_updater_ctrl first */
    c_memset((VOID*)pt_this, 0, sizeof(UPDATER_CTRL_T));

    c_memset((VOID*)&t_comp, 0, sizeof(NAV_COMP_T));

    /* NAV_COMP_ID_UPDATER */
    t_comp.pf_init           = _nav_updater_init;
    t_comp.pf_deinit         = _nav_updater_deinit;
    t_comp.pf_is_key_handler = _nav_updater_is_key_handler;
    t_comp.pf_activate       = _nav_updater_activate;
    t_comp.pf_inactivate     = _nav_updater_inactivate;
    t_comp.pf_hide           = _nav_updater_hide;
    t_comp.pf_handle_msg     = _nav_updater_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_UPDATER, &t_comp, COMP_EXEC_SET_UPDATER);
    if (i4_ret != NAVR_OK)
    {
        return i4_ret;
    }

    if (NULL == pt_view_hdlr)
    {
        nav_updater_view_register_default_hdlr(&pt_this->t_updater_view_hdlr);
    }
    else
    {
        pt_this->t_updater_view_hdlr = *pt_view_hdlr;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 nav_updater_lock(VOID)
{
    return c_sema_lock(t_g_updater_ctrl.h_sema_mtx, X_SEMA_OPTION_WAIT) == OSR_OK ?
           NAVR_OK :
           NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 nav_updater_unlock(VOID)
{
    return c_sema_unlock(t_g_updater_ctrl.h_sema_mtx) == OSR_OK ?
           NAVR_OK :
           NAVR_FAIL;
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/

INT32 updater_reset_log_file( VOID )
{
    nav_updater_lock();
    {
        int fd = -1;
        INT32   i4_ret;

        i4_ret = access(UPDATER_TEST_LOG_FDIR, F_OK);
        if (i4_ret != 0)
        {
            if (mkdir(UPDATER_TEST_LOG_FDIR, 0777) == -1)
            {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create dir %s fail!!\n",UPDATER_TEST_LOG_FDIR));
                nav_updater_unlock();
                return NAVR_FAIL;
            }
        }

        if ((fd = open(UPDATER_TEST_LOG_FNAME, O_RDWR|O_CREAT|O_TRUNC, 0666)) == -1)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Create file %s fail!!\n",UPDATER_TEST_LOG_FNAME));
            nav_updater_unlock();
            return NAVR_FAIL;
        }

        close(fd);
    }

    nav_updater_unlock();
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/

INT32 updater_log_printf(
    const CHAR *format,
    ...)
{

    nav_updater_lock();
    {
        INT32 i4_total = 0;
        va_list va_mark;
        int fd;
        struct stat     sDirInfo;

        va_start(va_mark, format);
        i4_total = c_vsprintf(s_updater_log_message, format, va_mark);
        va_end(va_mark);
        if(i4_total >= MAX_UPDATER_LOG_LEN)
        {
            s_updater_log_message[MAX_UPDATER_LOG_LEN] = 0;
        }
        c_sprintf( s_updater_log, "[Updater_Log] %s\n",s_updater_log_message );

        if ( 0 == stat( UPDATER_TEST_LOG_FNAME, &sDirInfo ))
        {
            /* do nothing*/
        }
        else
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"The %s file do not exist!!\n",UPDATER_TEST_LOG_FNAME));
            nav_updater_unlock();
            return NAVR_FAIL;
        }

        if ((fd = open(UPDATER_TEST_LOG_FNAME, O_RDWR|O_APPEND)) == -1)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Open file %s fail!!\n",UPDATER_TEST_LOG_FNAME));
            nav_updater_unlock();
            return NAVR_FAIL;
        }

        write(fd,s_updater_log,( (UINT32)c_strlen( ( const CHAR * )s_updater_log ) ));
        fsync(fd);
        close(fd);
    }
    nav_updater_unlock();

    return NAVR_OK;
}

static VOID _nav_update_cmd_exec_handle(
                    VOID*                       pv_tag,
    VOID*                  pv_tag2,
    VOID*                  pv_tag3
)
{
    NAV_UPDATER_EXEC_CMD_TYPE_T  e_cmd_type = (NAV_UPDATER_EXEC_CMD_TYPE_T)((UINT32)pv_tag);
    NAV_UPDATER_USER_MODE_T e_user_mode = (NAV_UPDATER_USER_MODE_T)((UINT32)pv_tag2);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_update_cmd_exec_handle e_cmd_type[%d], e_user_mode[%d]\n",
                    e_cmd_type,e_user_mode));

    switch (e_cmd_type)
{
        case UPD_CMD_TYPE_FW_CHECK:
    {
                /*check about whether there is
                  valid fw in the server, also
                  check if it is forced FW*/
                nav_updater_uli_check_sw_available(e_user_mode);
        }
            break;
        case UPD_CMD_TYPE_FW_CHECK_AND_UPDATE:
        {
            nav_updater_uli_check_sw_available_and_update(e_user_mode);
        }
        break;

        case UPD_CMD_TYPE_FW_DOWNLOAD:
        {
                /*Silently*/
                nav_updater_uli_start_fw_download(e_user_mode);
        }
            break;

        case UPD_CMD_TYPE_FW_REBOOT_INSTALL:
        {
                /*Reboot system install*/
                nav_updater_sys_install_fw(e_user_mode,TRUE);
        }
            break;

        case UPD_CMD_TYPE_FW_INSTALL:
        {
                /*System install without reboot*/
                nav_updater_sys_install_fw(e_user_mode,FALSE);
            }
                break;

        case UPD_CMD_TYPE_FW_NET_FULL_UPGRADE:
                {

                /*Full system upgrade*/
                nav_updater_uli_start_full_sys_upgrade(e_user_mode);

        }
            break;
		case UPD_CMD_TYPE_FW_CMD_FULL_UPGRADE:
		{
			nav_updater_uli_start_full_cmd_upgrade(e_user_mode);
		}
			break;
		case UPD_CMD_TYPE_FW_CMD_INSTALL:
		{
			nav_updater_uli_start_full_cmd_install(e_user_mode);
		}
			break;
        default:
            break;
        }

    return;
    }


/* to-do update event call register: for Googel update event*/
extern INT32 nav_updater_register_callback(nav_updater_callback_fct pf_nfy, VOID* pv_tag)
{
    UPDATER_CTRL_T* pt_this = &t_g_updater_ctrl;
    INT32 i4_ret = NAVR_OK;

    do
    {
        if(pf_nfy == NULL)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"invalid arguments\n"));
            i4_ret = NAVR_INV_ARG;
            break;
        }

        if(pt_this->pf_nfy || pt_this->pv_tag)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"callback function has been already registered\n"));
            i4_ret = NAVR_FAIL;
            break;
        }

        pt_this->pf_nfy = pf_nfy;
        pt_this->pv_tag = pv_tag;
    }while(0);

    return i4_ret;
}

extern INT32 nav_updater_unregister_callback(nav_updater_callback_fct pf_nfy, VOID* pv_tag)
{
    UPDATER_CTRL_T* pt_this = &t_g_updater_ctrl;
    INT32 i4_ret = NAVR_OK;

    do
    {
        if(pf_nfy == NULL)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"invalid arguments\n"));
            i4_ret = NAVR_INV_ARG;
            break;
        }

        if(pt_this->pf_nfy != pf_nfy || pt_this->pv_tag != pv_tag)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"callback function has not been already registered\n"));
            i4_ret = NAVR_FAIL;
            break;
        }

        pt_this->pf_nfy = NULL;
        pt_this->pv_tag = NULL;
    }while(0);

    return i4_ret;
}

INT32 nav_update_send_fw_check_msg_to_observer(INT32 i4_arg1, INT32 i4_arg2)
{
    UPDATER_CTRL_T* pt_this = &t_g_updater_ctrl;

    if (pt_this->pf_nfy)
    {
        pt_this->pf_nfy(UPDATER_UPDATE_REASON_CHECK_UPDATE,i4_arg1,i4_arg2,pt_this->pv_tag);
    }

    return NAVR_OK;
        }

INT32 nav_update_send_fw_download_msg_to_observer(INT32 i4_arg1, INT32 i4_arg2)
        {
    UPDATER_CTRL_T* pt_this = &t_g_updater_ctrl;

    if (pt_this->pf_nfy)
        {
        pt_this->pf_nfy(UPDATER_UPDATE_REASON_DOWNLOAD,i4_arg1,i4_arg2,pt_this->pv_tag);
        }

    return NAVR_OK;
}



extern INT32 nav_updater_start(UPDATER_DLIVRY_TYPE_T t_delivery_type, BOOL b_start)
    {
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_start [Not support]\n"));
    return NAVR_NOT_IMPLEMENT;
}

extern INT32 nav_updater_get_firmware_info(UPDATER_FW_INFO_T* pt_firmwareInfo)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_firmware_info [Not support]\n"));
    return NAVR_NOT_IMPLEMENT;
}

extern INT32 nav_updater_get_item_info(UPDATER_ITEM_T* pt_item, UINT32 ui4_index)
    {
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_item_info [Not support]\n"));
    return NAVR_NOT_IMPLEMENT;
        }

/* to-do need re-implement*/
extern INT32 nav_updater_cancel_download_firmware(UPDATER_DLIVRY_TYPE_T t_delivery_type)
        {
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_cancel_download_firmware [Not support]\n"));
    return NAVR_NOT_IMPLEMENT;
        }


extern INT32 nav_updater_query_upgrade_result(UPDATER_DLIVRY_TYPE_T t_delivery_type)
{
    return NAVR_NOT_IMPLEMENT;
}


INT32 nav_updater_cmd_exec(NAV_UPDATER_EXEC_CMD_TYPE_T  e_cmd_type,
                               NAV_UPDATER_USER_MODE_T  e_user_mode)
    {
    /* execute cmd request in nav context */
    nav_request_context_switch(_nav_update_cmd_exec_handle, (VOID*)(UINT32)e_cmd_type, (VOID*)(UINT32)e_user_mode, NULL);
    return NAVR_OK;
        }

INT32 nav_updater_cmd_directly_exec(NAV_UPDATER_EXEC_CMD_TYPE_T  e_cmd_type,
                               NAV_UPDATER_USER_MODE_T  e_user_mode)
{
    /* execute cmd request in nav context */
    _nav_update_cmd_exec_handle((VOID*)(UINT32)e_cmd_type, (VOID*)(UINT32)e_user_mode, NULL);
    return NAVR_OK;
}

extern INT32 nav_updater_start_reboot_upgrade(UPDATER_DLIVRY_TYPE_T t_delivery_type)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_start_reboot_upgrade\n"));
    if(t_delivery_type == UPDATER_DLIVRY_TYPE_DLM)
    {
        nav_updater_cmd_exec(UPD_CMD_TYPE_FW_REBOOT_INSTALL,USER_MODE_NONE);
    }
    else
    {
        nav_updater_cmd_exec(UPD_CMD_TYPE_FW_REBOOT_INSTALL,USER_MODE_NORMAL);
    }
    return NAVR_OK;
}

/*just for fw install without system reboot*/
extern INT32 nav_updater_trigger(UPDATER_DLIVRY_TYPE_T t_delivery_type)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_trigger\n"));
    nav_updater_cmd_exec(UPD_CMD_TYPE_FW_INSTALL,USER_MODE_NORMAL);

    return NAVR_OK;
}

/*for full sys upgrade in one cmd*/
extern INT32 nav_updater_download_firmware_and_trigger_update(UPDATER_DLIVRY_TYPE_T t_delivery_type, const CHAR* ps_url, const CHAR* ps_fwPath)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_download_firmware_and_trigger_update\n"));
    nav_updater_cmd_exec(UPD_CMD_TYPE_FW_NET_FULL_UPGRADE,USER_MODE_NORMAL);

    return NAVR_OK;
        }

/* check whether the update is support
   for current delivry*/
extern INT32 nav_updater_is_supported(UPDATER_DLIVRY_TYPE_T t_delivery_type, BOOL* pb_supported)
        {
    if (NULL == pb_supported)
            {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_is_supported Arg invalid\n"));
        return NAVR_INV_ARG;
            }

    /*According to the spec,
      only support uli update*/
    *pb_supported = TRUE;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_is_supported b_supported[%d]\n",
        *pb_supported));

    return NAVR_OK;
            }

/* to-do:
1. if sw avliable;
2. forced*/
extern INT32 nav_updater_check_update(UPDATER_DLIVRY_TYPE_T t_delivery_type)
            {
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_check_update\n"));
    nav_updater_cmd_exec(UPD_CMD_TYPE_FW_CHECK,USER_MODE_SILENTLY);

    return NAVR_OK;
}

/*just download, need re-implement*/
extern INT32 nav_updater_start_download_firmware(UPDATER_DLIVRY_TYPE_T t_delivery_type, const CHAR* ps_url, const CHAR* ps_fwPath)
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_start_download_firmware\n"));
    nav_updater_cmd_exec(UPD_CMD_TYPE_FW_DOWNLOAD,USER_MODE_NORMAL);

    return NAVR_OK;
}

/*Get if it is reboot from oobe update*/
BOOL a_nav_updater_uli_get_oobe_update_finished()
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_uli_get_oobe_update_finished b_g_reboot_after_oobe_update[%d] \n", b_g_reboot_after_oobe_update));

    return b_g_reboot_after_oobe_update;
}

/*Set it is reboot from oobe update*/
INT32 a_nav_updater_uli_set_oobe_update_finished(BOOL   b_oobe_update)
{
    b_g_reboot_after_oobe_update = b_oobe_update;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_uli_set_oobe_update_finished b_g_reboot_after_oobe_update[%d] \n", b_g_reboot_after_oobe_update));

    return NAVR_OK;
}
/*Get if it is reboot from oobe update complete*/
BOOL a_nav_updater_uli_get_oobe_update_finished_complete()
{
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_uli_get_oobe_update_finished_complete b_g_reboot_after_oobe_update_complete[%d] \n", b_g_reboot_after_oobe_update_complete));

    return b_g_reboot_after_oobe_update_complete;
}

/*Set it is reboot from oobe update complete*/
INT32 a_nav_updater_uli_set_oobe_update_finished_complete(BOOL b_oobe_update_complete)
{
    b_g_reboot_after_oobe_update_complete = b_oobe_update_complete;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_uli_set_oobe_update_finished_complete b_g_reboot_after_oobe_update_complete[%d] \n", b_g_reboot_after_oobe_update_complete));

    return NAVR_OK;
}



/*The following api is the
  for the rest menu*/
extern INT32 a_nav_updater_check_fw_avaliable(UINT8 *pui1_fw_status,
                                                   UINT8 *pui_fw_policy)
{
      NAV_UPDATER_FW_STATE_T         e_fw_avaliable_state = CHECK_STATE_NONE;
      NAV_UPDATER_RUNNING_STAGE_T    e_update_stage = STAGE_NONE;
      UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
	  #if 0
      BOOL b_ulpk_is_valid = FALSE;

      b_ulpk_is_valid = a_uli_is_ulpk_valid();

      if (!b_ulpk_is_valid)
      {
          *pui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_NO;

          *pui_fw_policy = NAV_UPDATE_FW_POLICY_DEFAULT;

          NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_check_fw_avaliable [ULPK INVALID]\n"));

          return NAVR_OK;
      }
	  #endif
      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_check_fw_avaliable [BEG]\n"));

      if (pt_this->b_is_need_fw_re_check)
      {
      	  a_uli_check_drmp_update();
          nav_updater_cmd_exec(UPD_CMD_TYPE_FW_CHECK,USER_MODE_SILENTLY);

          c_thread_delay(4000*5);
      }

      pt_this->b_is_need_fw_re_check = FALSE;

      nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);
      nav_updater_uli_get_update_stage(&e_update_stage);

      if (STAGE_FW_CHECKING == e_update_stage)
      {
          *pui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_CHECK_BUSY;

           NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_check_fw_avaliable [BUSY]\n"));
      }
      else
      {
            if (CHECK_STATE_CHECK_AVALIABLE == e_fw_avaliable_state)
            {
                 *pui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_YES;
            }
            else
            {
                 *pui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_NO;
            }
            pt_this->b_is_need_fw_re_check = TRUE;
      }

      /*Currently defult set the policy to none(noraml)*/
      *pui_fw_policy = NAV_UPDATE_FW_POLICY_DEFAULT;

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_check_fw_avaliable ui1_fw_status[%d]\n",
           *pui1_fw_status));

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_check_fw_avaliable [END]\n"));

      return NAVR_OK;
            }

/*while in nav thread check firmware avaliable status
should directly call this fun should be call in nav thread*/
extern INT32 a_nav_updater_direcly_check_fw_avaliable(UINT8 *pui1_fw_status,
                                                   UINT8 *pui_fw_policy)
{
      UPDATER_CTRL_T*    pt_this = &t_g_updater_ctrl;
      BOOL b_ulpk_is_valid = FALSE;

      //b_ulpk_is_valid = a_uli_is_ulpk_valid();
      b_ulpk_is_valid = TRUE;
      if (!b_ulpk_is_valid)
      {
          *pui1_fw_status = NAV_UPDATE_FW_AVALIABLE_SATUS_NO;

          *pui_fw_policy = NAV_UPDATE_FW_POLICY_DEFAULT;

          NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_direcly_check_fw_avaliable [ULPK INVALID]\n"));

          return NAVR_OK;
      }

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_direcly_check_fw_avaliable [BEG]\n"));

      if (pt_this->b_is_need_fw_re_check)
      {
          NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"fw check \n"));
          nav_updater_cmd_exec(UPD_CMD_TYPE_FW_CHECK_AND_UPDATE,USER_MODE_SILENTLY);
      }

      pt_this->b_is_need_fw_re_check = FALSE;



      return NAVR_OK;
}


extern INT32 a_nav_updater_download_firmware_and_trigger_update(UINT8  *pui1_fw_status)
{
      NAV_UPDATER_FW_STATE_T       e_fw_avaliable_state = CHECK_STATE_NONE;
      UPDATER_CTRL_T*              pt_this = &t_g_updater_ctrl;

      pt_this->b_is_download_ok_received = FALSE;
      pt_this->b_is_install_ok_received  = FALSE;

      pt_this->ui1_download_ok_get_times = 0;
      pt_this->ui1_install_ok_get_times = 0;

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update [BEG]\n"));

      nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update e_fw_avaliable_state[%d]\n",
              e_fw_avaliable_state));

      if (CHECK_STATE_CHECK_AVALIABLE == e_fw_avaliable_state)
      {
          nav_updater_cmd_exec(UPD_CMD_TYPE_FW_NET_FULL_UPGRADE,USER_MODE_NORMAL);
          *pui1_fw_status = 1;
          c_thread_delay(2000);
      }
      else
      {
          *pui1_fw_status = 0;
      }

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update ui1_fw_status[%d]\n",
           *pui1_fw_status));

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update [END]\n"));

      return NAVR_OK;
}

extern INT32 a_nav_updater_download_firmware_and_trigger_update_directly(UINT8  *pui1_fw_status)
{
      NAV_UPDATER_FW_STATE_T       e_fw_avaliable_state = CHECK_STATE_NONE;
      UPDATER_CTRL_T*              pt_this = &t_g_updater_ctrl;

      pt_this->b_is_download_ok_received = FALSE;
      pt_this->b_is_install_ok_received  = FALSE;

      pt_this->ui1_download_ok_get_times = 0;
      pt_this->ui1_install_ok_get_times = 0;

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update_directly [BEG]\n"));

      nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update_directly e_fw_avaliable_state[%d]\n",
              e_fw_avaliable_state));

      if (CHECK_STATE_CHECK_AVALIABLE == e_fw_avaliable_state)
      {

          nav_updater_cmd_directly_exec(UPD_CMD_TYPE_FW_NET_FULL_UPGRADE,USER_MODE_NORMAL);

          *pui1_fw_status = 1;
      }
      else
      {
          *pui1_fw_status = 0;
      }

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update_directly ui1_fw_status[%d]\n",
           *pui1_fw_status));

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update_directly [END]\n"));

      return NAVR_OK;
}

extern INT32 a_nav_updater_usb_download_firmware_and_trigger_update_directly(UINT8  *pui1_fw_status)
{
      NAV_UPDATER_FW_STATE_T       e_fw_avaliable_state = CHECK_STATE_NONE;
      UPDATER_CTRL_T*              pt_this = &t_g_updater_ctrl;
	  NAV_UPDATER_FW_STATE_T  e_fw_state = CHECK_STATE_NONE;

      pt_this->b_is_download_ok_received = FALSE;
      pt_this->b_is_install_ok_received  = FALSE;

      pt_this->ui1_download_ok_get_times = 0;
      pt_this->ui1_install_ok_get_times = 0;

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_usb_download_firmware_and_trigger_update_directly [BEG]\n"));

      nav_updater_uli_get_fw_avaliable(&e_fw_avaliable_state);

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_usb_download_firmware_and_trigger_update_directly e_fw_avaliable_state[%d]\n",
              e_fw_avaliable_state));
	   nav_updater_uli_get_fw_status(&e_fw_state);

      if (CHECK_STATE_CHECK_AVALIABLE == e_fw_avaliable_state && e_fw_state == CHECK_STATE_CHECK_AVALIABLE)
      {

          nav_updater_cmd_directly_exec(UPD_CMD_TYPE_FW_CMD_FULL_UPGRADE,USER_MODE_NORMAL);

          *pui1_fw_status = 1;
      }
	  else if(CHECK_STATE_DOWNLOAD_SUCESS == e_fw_state && e_fw_avaliable_state == CHECK_STATE_CHECK_AVALIABLE)
	  {
	  	  nav_updater_cmd_directly_exec(UPD_CMD_TYPE_FW_CMD_INSTALL,USER_MODE_NORMAL);

          *pui1_fw_status = 1;
	  }
      else
      {
          *pui1_fw_status = 0;
      }

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update_directly ui1_fw_status[%d]\n",
           *pui1_fw_status));

      NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_download_firmware_and_trigger_update_directly [END]\n"));

      return NAVR_OK;
}

extern INT32 a_nav_updater_get_update_status(UINT8  *pui1_update_status,
                                             UINT8  *pui1_progress)
{
    UPDATER_CTRL_T* pt_this = &t_g_updater_ctrl;
    NAV_UPDATER_FW_STATE_T  e_fw_state = CHECK_STATE_NONE;

    do
    {
        if (TRUE == a_nav_updater_uli_get_oobe_update_finished())
        {
            *pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_FINISHED;
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_get_update_status Install complete[received], after reboot from oobe update\n"));
            a_nav_updater_uli_set_oobe_update_finished(FALSE);
            break;
        }

		nav_updater_uli_get_fw_status(&e_fw_state);
		if(CHECK_STATE_DOWNLOAD_FAIL == e_fw_state)
		{
			*pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_FAIL;
        	break;

		}

        if (FALSE == pt_this->b_is_updater_triggered)
        {
            *pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_NONE;
            break;
        }



        if (CHECK_STATE_CHECKING == e_fw_state)
        {
            *pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_CHECKING;
                    break;
        }

        if (CHECK_STATE_CHECK_AVALIABLE == e_fw_state)
        {
            *pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_FW_FOUND;
            break;
        }

        if (CHECK_STATE_DOWNLOADING == e_fw_state)
        {
            *pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_DOWNLOADING;
            *pui1_progress = pt_this->ui1_fw_download_progress;

            if (100 == (*pui1_progress))
            {
                pt_this->b_is_download_ok_received = TRUE;
                pt_this->ui1_download_ok_get_times = pt_this->ui1_download_ok_get_times+1;

                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_get_update_status case1 Downloading complete[received]\n"));
            }
            break;
        }

        if (CHECK_STATE_DOWNLOAD_SUCESS == e_fw_state)
        {

            *pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_DOWNLOADING;
            *pui1_progress = 100;

            pt_this->b_is_download_ok_received = TRUE;
            pt_this->ui1_download_ok_get_times = pt_this->ui1_download_ok_get_times+1;

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_get_update_status case2 Downloading complete[received]\n"));
        }

        if ((CHECK_STATE_FW_VALIDATING == e_fw_state)
            ||(CHECK_STATE_FW_PARSING == e_fw_state)
            ||(CHECK_STATE_FW_INITED == e_fw_state)
            ||(CHECK_STATE_CHECK_INSTALLING == e_fw_state))
        {
            *pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_APPLYING;
            *pui1_progress = pt_this->ui1_progress;

            break;
        }

        if (CHECK_STATE_CHECK_INSTALLED == e_fw_state)
        {
            *pui1_update_status = NAV_UPDATE_FW_UPDATE_STATUS_APPLYING;
            *pui1_progress = 100;
            pt_this->b_is_install_ok_received  = TRUE;
            pt_this->ui1_install_ok_get_times = pt_this->ui1_install_ok_get_times+1;

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_get_update_status Install complete[received], but return applying 100%\n"));
        }
    }while(0);

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"a_nav_updater_get_update_status e_fw_state[%d],update_status[%d],progress[%d]\n",
        pt_this->b_is_updater_triggered,
        *pui1_update_status,
        *pui1_progress));

    return NAVR_OK;
}

INT32 nav_updater_check_continue_next_step(NAV_UPDATER_CHK_STEP_TYPE_T e_chk_type,
                                          BOOL *pb_is_to_continue)
{
    UINT8  ui1_chk_times = 0;
    NAV_UPDATER_TRIGGER_TYPE_T  e_type = TRIGGER_TYPE_NONE;
    UINT16 ui2_status = 0;
    UPDATER_CTRL_T* pt_this = &t_g_updater_ctrl;

    nav_updater_uli_get_trigger_type(&e_type);

    if (TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD_AND_INSTALL != e_type)
    {
        *pb_is_to_continue = TRUE;
        return NAVR_OK;
    }

    /*check the wizard status*/
    if (a_cfg_get_wzd_status(&ui2_status) == APP_CFGR_OK
        && (WZD_UTIL_GET_STATUS_STATE(ui2_status) == WZD_STATE_RESUME_C4TV))
    {
       /*do nothing*/
    }
    else
    {
        *pb_is_to_continue = TRUE;
        return NAVR_OK;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_check_continue_next_step\n"));
    /*this fun only be call in nav thread, and just after downloading & install ok
      also here should only wait 30s*/
    for(ui1_chk_times=0; ui1_chk_times<30; ui1_chk_times++)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_check_continue_next_step ui1_chk_times:%d\n", ui1_chk_times));

         if (NAV_UPDATER_CHK_STEP_DOWNLOADING_OK == e_chk_type)
         {
             if ((pt_this->b_is_download_ok_received)
                &&(2 == pt_this->ui1_download_ok_get_times))
             {
                NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_check_continue_next_step [Download_ok]\n"));
                break;
             }
             else
             {
                 c_thread_delay(500);
             }
         }
         else if (NAV_UPDATER_CHK_STEP_INSTALL_OK == e_chk_type)
         {
            if ((pt_this->b_is_install_ok_received)
                && (2 == pt_this->ui1_install_ok_get_times))
            {
               NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_check_continue_next_step [Install_ok]\n"));
               break;
            }
            else
            {
                c_thread_delay(500);
            }
         }
         else
         {
            /*do nothing*/
         }
    }

    if (30 == ui1_chk_times)
    {
        if (NAV_UPDATER_CHK_STEP_DOWNLOADING_OK == e_chk_type)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_check_continue_next_step Download_ok_chk[timeout]\n"));
        }
        else if (NAV_UPDATER_CHK_STEP_INSTALL_OK == e_chk_type)
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_check_continue_next_step Install_ok_chk[timeout]\n"));
        }
        else
        {

        }
    }

    /*always*/
    *pb_is_to_continue = TRUE;
    return NAVR_OK;
}

INT32 nav_updater_set_oobe_update_status(WZD_PAGE_INDEX_T e_idx)
{
#if 0
    NAV_UPDATER_TRIGGER_TYPE_T  e_type = TRIGGER_TYPE_NONE;
    UINT16  ui2_status    = 0;
    UINT8   ui1_state     = 0;

    nav_updater_uli_get_trigger_type(&e_type);

    /* check the trigger type*/
    if ((TRIGGER_TYPE_ULI_NETWORK_FW_DOWNLOAD_AND_INSTALL != e_type)
        && (TRIGGER_TYPE_ULI_NETWORK_FW_INSTALL != e_type)
        && (TRIGGER_TYPE_ULI_USB_FW_DOWNLOAD_AND_INSTALL))
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"\n nav_updater_set_oobe_update_status Reject  e_type[%d]\n",e_type));
        return NAVR_OK;
    }

    a_cfg_get_wzd_status(&ui2_status);

    ui1_state = WZD_UTIL_GET_STATUS_STATE(ui2_status);

    a_cfg_set_wzd_status (WZD_UTIL_SET_STATUS(ui1_state, e_idx));


    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"\n nav_updater_set_oobe_update_status e_idx[%d],ui1_state[%d]\n",
                  e_idx,ui1_state));
#endif
    return NAVR_OK;
}

/*This fun only could be called when
all the partition is ready*/

INT32 nav_updater_get_cast_key_status(BOOL  *pb_is_ready)
{
    INT32   i4_ret;
    BOOL    b_is_cast_key_exist = FALSE;
    BOOL    b_is_cast_cert_key_exist = FALSE;

    if (NULL == pb_is_ready)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_cast_key_status Break[Invalid ARG]\n"));
        return NAVR_INV_ARG;
    }

    /*step1: check the cast key path is exist or not*/
    i4_ret = access(NAV_UPDATE_CAST_KEY_PATH, F_OK);
    if (i4_ret != 0)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_cast_key_status Break[CAST_KEY_PATH_NOT_EXIST]\n"));
        return NAVR_FAIL;
    }

    /*step2: check cast cert key exist or not*/
    i4_ret = access(NAV_UPDATE_CAST_CERT_KEY_NAME, F_OK);
    if (i4_ret != 0)
    {
        b_is_cast_cert_key_exist = FALSE;
    }
    else
    {
        b_is_cast_cert_key_exist = TRUE;
    }


    /*step3: check cast key exist or not*/
    i4_ret = access(NAV_UPDATE_CAST_KEY_NAME, F_OK);
    if (i4_ret != 0)
    {
        b_is_cast_key_exist = FALSE;
    }
    else
    {
        b_is_cast_key_exist = TRUE;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_cast_key_status b_is_cast_cert_key_exist[%d],b_is_cast_key_exist[%d]\n",
                        b_is_cast_cert_key_exist,b_is_cast_key_exist));

    if ((FALSE == b_is_cast_key_exist)
        || (FALSE == b_is_cast_cert_key_exist))
    {
        *pb_is_ready = FALSE;
    }
    else
    {
        *pb_is_ready = TRUE;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_get_cast_key_status b_is_ready[%d]\n",
                        *pb_is_ready));

    return NAVR_OK;
}

/*This function is used to show loading page.*/
INT32 nav_loading_page_show(VOID)
{
    INDICATOR_MSG msg = {0};
    struct mq_attr g_mqd_attr;
    mqd_t mqd_t = mq_open(GET_MQD_LOADING,O_CREAT|O_RDWR, 0666, NULL);
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_loading_page_show start.\n"));


    msg.msgType = 10;//show

    if (mqd_t < 0)
    {
        perror("mq_open fail");
        return NAVR_FAIL;
    }
    if (mq_getattr(mqd_t, &g_mqd_attr) < 0)
    {
        perror("get attr fail");
        return NAVR_FAIL;
    }
    DBG_LOG_PRINT(("\n%s,%d,mqd_t=%x\n", __FUNCTION__, __LINE__, mqd_t));

    if(mq_send(mqd_t, (char*)(&msg), sizeof(INDICATOR_MSG) - sizeof(long), 0) == -1)
    {
        NAV_UPGRADE_LOG_PRINT(("[ERROR] a_cfg_custom_show_splash - Send msg to mtk indicator failed!\n"));
        return NAVR_FAIL;
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_loading_page_show exit.\n"));

    // Disable system keys.
    a_amb_enable_system_key(FALSE);//modified by zile.pang
    a_amb_enable_power_key(TRUE);

    // Disable screen saver.
    a_scrn_svr_set_enable(FALSE);

    b_g_is_loading_page_show = TRUE;
#ifdef APP_ZOOM_MODE_SUPPORT
    NAV_UPGRADE_LOG_PRINT(("\nwuli %s,%d\n",__FUNCTION__,__LINE__));
    a_zoom_mode_set_sector_id(ZOOM_SHOW_MAKE_ID(ZOOM_APP_GRPID_NAV, NAV_COMP_ID_SCREEN_SAVER));
#endif

    return 0;
}

/*This function is used to hide loading page.*/
INT32 nav_loading_page_hide(VOID)
{
    INDICATOR_MSG msg = {0};
    struct mq_attr g_mqd_attr;
    mqd_t mqd_t = mq_open(GET_MQD_LOADING,O_CREAT|O_RDWR, 0666, NULL);
    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_loading_page_hide start.\n"));


    msg.msgType = 11;//show

    if (mqd_t < 0)
    {
        perror("mq_open fail");
        return NAVR_FAIL;
    }
    if (mq_getattr(mqd_t, &g_mqd_attr) < 0)
    {
        perror("get attr fail");
        return NAVR_FAIL;
    }
    DBG_LOG_PRINT(("\n%s,%d,mqd_t=%x\n", __FUNCTION__, __LINE__, mqd_t));

    if(mq_send(mqd_t, (char*)(&msg), sizeof(INDICATOR_MSG) - sizeof(long), 0) == -1)
    {
        NAV_UPGRADE_LOG_PRINT(("[ERROR] a_cfg_custom_show_splash - Send msg to mtk indicator failed!\n"));
        return NAVR_FAIL;
    }


    // Enable system keys.
    a_amb_enable_system_key(TRUE);
    a_amb_enable_power_key(TRUE);

    // Enable screen saver.
    a_scrn_svr_set_enable(TRUE);
    b_g_is_loading_page_show = FALSE;

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_loading_page_hide exit.\n"));

    return 0;
}

/*this funtion will call by other app(ex:menu),so:
step1: should async resume nav;
step2: start a timer, and the timeout may
       be 5s(assume the nav resume should within 5s);
step3: when the timeout, here should first trigger
       firmware check, if the firmware check is ok
       should continue run the firmware update,
       if no firmware avaliable,should just show a
       warning dialog related to it.
*/
extern INT32 a_nav_updater_check_network_update(UINT8 *pui1_fw_status,
                                                   UINT8 *pui_fw_policy)
{
    CHAR  s_active_name [APP_NAME_MAX_LEN+1]= {0};
    a_am_get_active_app(s_active_name);
    if (FALSE == nav_is_active())
    {
        if((c_strcmp(s_active_name, "menu")==0)&&(a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED ||
            (MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status())))
        {
            a_amb_pause_app(s_active_name);
			//NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"mmp status:%d \n",a_mmp_get_ap_status()));
			if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC != a_mmp_get_ap_status() &&
			   a_tv_net_get_tv_svc_status() != APP_TV_NET_SVC_STATUS_RESUMED)
			{
            	rest_event_notify("key_command", BTN_WIDGET, "");
			}
        }
        else if((c_strcmp(s_active_name, "menu")==0)&&(msg_convert_custom_browser_ctrl_active()))
        {
            menu_leave(FALSE,0);
        }
        else if((c_strcmp(s_active_name, "mscvt")==0) && (msg_convert_custom_browser_ctrl_active()))
        {
            // Updater from voice command in SCH, don't resume nav, it will cause SCH black screen.
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Updater from voice command\n"));
        }
		else if(a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)
		{

		}
		else if(c_strcmp(s_active_name, "mmp")==0)
		{
			rest_event_notify("key_command", BTN_WIDGET, "");
		}
        else
        {
            nav_resume_self();
        }
    }

    nav_loading_page_show();

    nav_update_reset_delay_firmware_check_timer();

    return NAVR_OK;
}


extern BOOL a_nav_is_loading_page_show(VOID)
{
    return b_g_is_loading_page_show;
}

BOOL b_nav_update_is_enable_log(VOID)
{
	return TRUE;
}

INT32 nav_updater_set(UPDATER_SET_TYPE_T e_set_type, VOID* pv_data, UINT32 ui4_data_len, VOID* pv_arg)
{
    return NAVR_OK;
}
