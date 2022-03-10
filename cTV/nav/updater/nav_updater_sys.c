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

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/

#include <unistd.h>
#include "c_fm.h"
#include "u_fm.h"
#include "c_os.h"
#include "c_uc_str.h"
#include "c_dlm.h"

#include "app_util/a_updater.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "nav/nav_common.h"
#include "nav/updater/nav_updater.h"
#include "res/app_util/updater/a_updater_custom.h"
#include "res/nav/updater/nav_updater_res.h"
#include "am/a_am.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 -----------------------------------------------------------------------------*/

typedef struct _UPDATER_USB_CTRL_T
{
    UPDATER_DLIVRY_TYPE_T       e_type;

    CHAR                        s_src_file[64];
    RMV_DEV_OPEN_ID_T           t_rmv_open_id;
    UINT32                      ui4_rmv_dev_nfy;
    UINT32                      ui4_mnt_point_index;
    BOOL                        b_delay_start;
    BOOL                        b_force_integrity_chk;
    updater_preprocess_cb_fn    pf_preprocess_cb;
    BOOL                        b_part_all_is_ready;
    BOOL                        is_semi_standby;
} UPDATER_SYS_CTRL_T;

/*-----------------------------------------------------------------------------
                    variable declarations
 -----------------------------------------------------------------------------*/

static UPDATER_SYS_CTRL_T    t_g_sys_ctrl;

static BOOL                  b_s_is_partition_all_ready = FALSE;

static INT32 _nav_updater_sys_get_path(
    CHAR*                  ps_buff,
    SIZE_T                 z_buff_len
);

/*-----------------------------------------------------------------------------
                    private methods implementation
 -----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: _nav_updater_sys_preprocess_cb
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_sys_preprocess_cb(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    UPDATER_SYS_CTRL_T*     pt_this = &t_g_sys_ctrl;
    BOOL                    b_success = (BOOL)((UINT32)(pv_tag1));

    if (NULL != pt_this->pf_preprocess_cb)
    {
        pt_this->pf_preprocess_cb(b_success,
                                  (TRUE == b_success) ? UPDATER_EXIT_REASON_NONE : UPDATER_EXIT_REASON_USB_DEV_FAIL);

        pt_this->pf_preprocess_cb = NULL;
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_sys_preprocess
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_sys_preprocess(
    updater_preprocess_cb_fn    pf_preprocess_cb
)
{
    UPDATER_SYS_CTRL_T*         pt_this = &t_g_sys_ctrl;

    if (NULL == pf_preprocess_cb)
    {
        return NAVR_FAIL;
    }

    /* assign the callback function */
    pt_this->pf_preprocess_cb = pf_preprocess_cb;

    /* callback the updater core */
    nav_request_context_switch(
                    _nav_updater_sys_preprocess_cb,
                    (VOID*)(TRUE),
                    NULL,
                    NULL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_sys_handle_msg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static VOID _nav_updater_sys_handle_msg(
    NAV_UI_MSG_T*          pt_ui_msg,
    VOID*                  pv_arg
)
{
    UPDATER_SYS_CTRL_T*    pt_this = &t_g_sys_ctrl;

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_POWER_ON:
            pt_this->is_semi_standby = FALSE;
            break;

        case NAV_UI_MSG_POWER_OFF:
            pt_this->is_semi_standby = TRUE;
            break;

        case NAV_UI_MSG_APP_RESUMED:
#if 0
            if (pt_this->b_part_all_is_ready)
            {
                if (TRUE == pt_this->b_delay_start)
                {
                    pt_this->b_delay_start = FALSE;
                    nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_UPGRADE, NULL);
                    nav_updater_trigger_update(pt_this->e_type);
                    DBG_INFO((NAV_UPDATER_PREFIX"<APP Resume> - trigger system update \n"));
                }
            }
#endif
            break;

        case NAV_UI_MSG_APP_PRE_RESUME:
#if 0
        {
            if (pt_this->b_part_all_is_ready && (TRUE == pt_this->b_delay_start))
            {
                INT32           i4_ret;
                HANDLE_T        h_file;
                CHAR            sz_src_path[256];

                /* Check PKG file exist in TV System */
                c_strcpy(sz_src_path, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_NAME);
                i4_ret = c_fm_open(FM_ROOT_HANDLE,
                                   sz_src_path,
                                   FM_READ_ONLY,
                                   0777,
                                   FALSE,
                                   &h_file);
                if (FMR_OK == i4_ret)
                {
                    c_fm_close(h_file);

                    DBG_INFO((NAV_UPDATER_PREFIX"<APP Pre-Resume> - Found PKG in TV: '%s \n", sz_src_path));

                    /* do integrity check */
                    i4_ret = c_dlm_integrity_check(sz_src_path, NULL);
                    if(DLM_OK != i4_ret)
                    {
                        DBG_INFO((NAV_UPDATER_PREFIX"c_dlm_integrity_check: i4_ret = %d \n", i4_ret));
                        return;
                    }

                    i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));
                    if (NAVR_OK == i4_ret)
                    {
                        nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_UPGRADE, NULL);
                        DBG_INFO((NAV_UPDATER_PREFIX"<APP Pre-Resume> - trigger system update \n"));
                        nav_updater_trigger_update(pt_this->e_type);
                    }
                }
            }
        }
#endif
        break;

        default:
            break;
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_sys_get_path
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_sys_get_path(
    CHAR*                  ps_buff,
    SIZE_T                 z_buff_len
)
{
    UPDATER_SYS_CTRL_T*    pt_this  = &t_g_sys_ctrl;
    CHAR                   s_tmp[64];

    if (ps_buff == NULL)
    {
        return NAVR_FAIL;
    }

    /* get the TV system path, for example: /basic/upgrade */
    c_strcpy(s_tmp, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH);

    c_snprintf(ps_buff, z_buff_len, "%s/%s", s_tmp, pt_this->s_src_file);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_sys_exit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_sys_get_fw(
    UPDATER_ITEM_T*               pt_item,
    updater_progress_notify_fn    pf_progress_cb
)
{
    UPDATER_SYS_CTRL_T*           pt_this  = &t_g_sys_ctrl;

    if (TRUE == pt_this->b_force_integrity_chk)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Do integrity check forcely because the usb device may be unplug and plug!!!\n"));

        return nav_updater_integrity_chk();
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_sys_exit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_sys_exit(
    BOOL                   b_success
)
{
    UPDATER_SYS_CTRL_T*    pt_this  = &t_g_sys_ctrl;

    pt_this->b_force_integrity_chk = FALSE;

    return NAVR_OK;
}

static VOID _nav_updater_sys_trigger_update_nfy_handler(
    VOID*                  pv_tag1,
    VOID*                  pv_tag2,
    VOID*                  pv_tag3
)
{
    INT32                  i4_ret;
    HANDLE_T               h_file;
    CHAR                   sz_src_path[256];
    UPDATER_SYS_CTRL_T*    pt_this = &t_g_sys_ctrl;

#ifdef APP_ULI_UPG_SUPPORT
    if(TRUE == a_am_is_power_on())
    {
        NAV_UPGRADE_LOG_PRINT(("\n[UPTT]PARTITION_ALL Trigger\n"));
        nav_updater_uli_send_started_msg_to_am();
    }
#endif

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

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"<_nav_updater_sys_trigger_update_nfy_handler> - Found PKG in TV: '%s \n", sz_src_path));
#if 0
        /* do integrity check */
        i4_ret = c_dlm_integrity_check(sz_src_path, NULL);
        if(DLM_OK != i4_ret)
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"c_dlm_integrity_check: i4_ret = %d \n", i4_ret));

            return;
        }
#endif
        i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

        if (NAVR_OK == i4_ret)
        {
			nav_updater_uli_set_user_mode(USER_MODE_NORMAL);
			nav_updater_uli_set_trigger_type(TRIGGER_TYPE_ULI_NETWORK_FW_INSTALL);

            nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_PREPROCESS, NULL);

            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"<_nav_updater_sys_trigger_update_nfy_handler> - trigger system update \n"));
            nav_updater_trigger_update(pt_this->e_type);
        }
    }
}

static INT32 _nav_updater_sys_fm_partition_status_nfy(
        UINT32             ui4_tag,
        FS_PARTITION_T     e_partition
)
{
    UPDATER_SYS_CTRL_T*    pt_this  = &t_g_sys_ctrl;

    if (FS_PARTITION_ALL == e_partition
        || FS_PARTITION_3RD == e_partition)
    {
        DBG_INFO((NAV_UPDATER_PREFIX"FS_PARTITION_ALL mounted.\n"));
        pt_this->b_part_all_is_ready = TRUE;
        b_s_is_partition_all_ready = TRUE;

        if (!pt_this->is_semi_standby)
        {
        #ifdef APP_ULI_UPG_SUPPORT
            nav_updater_uli_trigger_sub_updater();
		#endif
            nav_request_context_switch(_nav_updater_sys_trigger_update_nfy_handler,
                                   NULL,
                                   NULL,
                                   NULL);
        }
    }

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
                     public methods implementations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: nav_updater_usb_init
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
INT32 nav_updater_sys_init(
    VOID
)
{
    UPDATER_DLIVRY_HDLR_REG_T    t_reg;
    INT32                        i4_ret;
    UPDATER_SYS_CTRL_T*          pt_this = &t_g_sys_ctrl;

    /* fill data for t_g_sys_ctrl */
    c_memset(pt_this, 0, sizeof(UPDATER_SYS_CTRL_T));

    pt_this->e_type = UPDATER_DLIVRY_TYPE_SYS;
    c_strcpy(pt_this->s_src_file, UPDATER_FW_INTEGRITY_OK_NAME);

    /* fill data for t_reg */
    c_memset(&t_reg, 0, sizeof(UPDATER_DLIVRY_HDLR_REG_T));

    t_reg.e_type = pt_this->e_type;

    t_reg.pf_preprocess = _nav_updater_sys_preprocess;
    t_reg.pf_handle_msg = _nav_updater_sys_handle_msg;
    t_reg.pf_get_path   = _nav_updater_sys_get_path;
    t_reg.pf_get_fw     = _nav_updater_sys_get_fw;
    t_reg.pf_exit       = _nav_updater_sys_exit;

    t_reg.pt_io         = NULL;

    t_reg.b_division    = FALSE;

    i4_ret = nav_updater_reg_dlivry_hdlr(&t_reg);
    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    c_fm_partition_reg_nfy(_nav_updater_sys_fm_partition_status_nfy, 0);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: nav_updater_is_all_partition_ready
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
BOOL nav_updater_is_all_partition_ready(
    VOID
)
{
    return b_s_is_partition_all_ready;
}

/* this api should run in the nav thread*/
INT32 nav_updater_sys_install_fw(NAV_UPDATER_USER_MODE_T e_user_mode,
                               BOOL   b_is_to_reboot)
{
    if(e_user_mode == USER_MODE_NONE)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_sys_install_fw [Just force reboot]\n"));
        if(a_am_is_power_on())
        {
            a_cfg_custom_service_reset(1,ACFG_FORCE_REBOOT_UP_ON);
        }
        else
        {
            a_cfg_custom_set_drv_bgmupdate_flag(1);
            a_cfg_cust_set_force_reboot_up_flag(ACFG_FORCE_REBOOT_UP_OFF);
            system("reboot");
        }
        return NAVR_OK;
    }
    else if (nav_update_is_sys_sw_image_ready())
	{
		if (b_is_to_reboot)
		{
		    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_sys_install_fw ready[Just reboot]\n"));
			a_cfg_cust_set_force_reboot_up_flag(ACFG_FORCE_REBOOT_UP_ON);

			a_amb_reboot();
		}
		else
		{
		    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_sys_install_fw ready[direct install]\n"));
			_nav_updater_sys_trigger_update_nfy_handler(NULL,NULL,NULL);
		}

		return NAVR_OK;
	}
	else
	{
		NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"nav_updater_sys_install_fw not_ready[Just reject]\n"));

		return NAVR_FAIL;
	}
}


