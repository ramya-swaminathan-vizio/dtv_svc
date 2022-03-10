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
#ifdef APP_MTK_UPG_SUPPORT
#include <stdlib.h>
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
    BOOL                        b_is_sys_reboot;
} UPDATER_USB_CTRL_T;

/*-----------------------------------------------------------------------------
                    variable declarations
 -----------------------------------------------------------------------------*/
static UPDATER_USB_CTRL_T    t_g_usb_ctrl;

static INT32 _nav_updater_usb_get_path(
    CHAR*                  ps_buff,
    SIZE_T                 z_buff_len
);

/*-----------------------------------------------------------------------------
                    private methods implementation
 -----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_alloc_rmv_res
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_usb_alloc_rmv_res(
    VOID
)
{
    INT32                   i4_ret;
    UINT32                  ui4_count;
    UINT32                  ui4_idx;
    BOOL                    b_found   = FALSE;
    UPDATER_USB_CTRL_T*     pt_this   = &t_g_usb_ctrl;
    SIZE_T                  z_size    = sizeof(UINT32);
    UINT32                  ui4_info  = 0;
    RMV_DEV_OPEN_ID_T       t_open_id = 0;
    RMV_DEV_DEVICE_STATUS_T e_dev_status;

    i4_ret = a_rmv_dev_get_mnt_count(&ui4_count);

    if (RMVR_OK != i4_ret || 0 == ui4_count)
    {
        return NAVR_FAIL;
    }

    for (ui4_idx = 0 ; ui4_idx < ui4_count ; ui4_idx++)
    {
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_idx, &e_dev_status);
        if (RMVR_OK == i4_ret)
        {
#ifdef APP_NETWORK_SUPPORT
#ifdef APP_NET_DLNA_SUPPORT
            if (RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
            {
                continue;
            }
#endif
#endif
#ifdef APP_NET_NEIGHBOR_SUPPORT
            if(RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))
            {
                continue;
            }
#endif
        }

        if (RMV_DEV_NULL_OPEN_ID == pt_this->t_rmv_open_id)
        {
             i4_ret = a_rmv_dev_get_mnt_point_info(
                        ui4_idx,
                        RMV_DEV_INFO_ID_USER_DATA,
                        &z_size,
                        (VOID*)&ui4_info);

            if (RMVR_OK != i4_ret)
            {
                continue;
            }

            if (RMV_DEV_USER_DATA_POINT_CHECKED & ui4_info)
            {
                continue;
            }

            ui4_info |= RMV_DEV_USER_DATA_POINT_CHECKED;

            i4_ret = a_rmv_dev_set_mnt_point_info(
                        ui4_idx,
                        RMV_DEV_INFO_ID_USER_DATA,
                        &z_size,
                        (VOID*)&ui4_info);

            if (RMVR_OK != i4_ret)
            {
                return NAVR_FAIL;
            }
        }

        i4_ret = a_rmv_dev_open_mnt_point(ui4_idx, &t_open_id);

        if (RMVR_OK != i4_ret)
        {
            return NAVR_FAIL;
        }

        if (a_fw_updater_is_fw_ready(ui4_idx, pt_this->s_src_file))
        {
            b_found = TRUE;
            pt_this->ui4_mnt_point_index = ui4_idx;
            pt_this->t_rmv_open_id       = t_open_id;
            break;
        }
        else
        {
            a_rmv_dev_close_mnt_point(t_open_id);
        }
    }

    if (FALSE == b_found)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_usb_free_res
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_usb_free_res(
    VOID
)
{
    INT32                      i4_ret;
    UPDATER_USB_CTRL_T*        pt_this  = &t_g_usb_ctrl;
    RMV_DEV_DEVICE_STATUS_T    e_status = 0;

    if (RMV_DEV_NULL_OPEN_ID != t_g_usb_ctrl.t_rmv_open_id)
    {
        i4_ret = a_rmv_dev_get_mnt_point_status(pt_this->t_rmv_open_id, &e_status);

        if (RMVR_OK != i4_ret)
        {
            return NAVR_FAIL;
        }

        if (RMV_DEV_DEVICE_STATUS_REMOVED & e_status)
        {
            i4_ret = a_rmv_dev_close_mnt_point(pt_this->t_rmv_open_id);

            if (RMVR_OK != i4_ret)
            {
                return NAVR_FAIL;
            }
            else
            {
                pt_this->t_rmv_open_id = RMV_DEV_NULL_OPEN_ID;
                return NAVR_OK;
            }
        }
    }

    return NAVR_NO_ACTION;
}

static INT32 _nav_updater_usb_chk_dst_space(CHAR *psz_dst_path, BOOL* pb_enough)
{
    INT32           i4_ret;
    FM_FS_INFO_T    t_fs_info;
    FM_FILE_INFO_T  t_file_info;
    CHAR            sz_usb_src_path[128];
    HANDLE_T        h_file;
    UINT64          ui8_file_size = 0;

    if (!pb_enough || !psz_dst_path)
    {
        return UPDATERR_INV_ARG;
    }

    /* Check PKG file exist or not in USB */
    i4_ret = _nav_updater_usb_get_path(sz_usb_src_path, 256);
    if(UPDATERR_OK != i4_ret)
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"_nav_updater_usb_get_path faile! i4_ret = %d\n", i4_ret));
        return UPDATERR_FAIL;
    }

    /* Get the PKG File Size in USB */
    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       sz_usb_src_path,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_file);
    if (FMR_OK != i4_ret)
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"c_fm_open faile! i4_ret = %d\n", i4_ret));
        return UPDATERR_FAIL;
    }
    i4_ret = c_fm_get_info_by_handle(h_file, &t_file_info);
    if (FMR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Get information %s error[%d]!\n", sz_usb_src_path, i4_ret));
        c_fm_close(h_file);
        return UPDATERR_FAIL;
    }

    ui8_file_size = t_file_info.ui8_size;

    c_fm_close(h_file);

    /* Get TV Space Size */
    i4_ret = c_fm_get_fs_info(FM_ROOT_HANDLE, psz_dst_path, &t_fs_info);
    if (FMR_OK != i4_ret)
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"c_fm_get_fs_info() return: %d\n", i4_ret));
        return (UPDATERR_FAIL);
    }

    /* Check TV Space Size */
    if ((FM_TYPE_INVAL != t_fs_info.e_type) &&
        (ui8_file_size > (t_fs_info.ui8_blk_size * t_fs_info.ui8_free_blk)))
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"Not Enough Space to save PKG file into TV!!\n"));
        DBG_ERROR((NAV_UPDATER_PREFIX"    PKG File Size  = %llu \n", ui8_file_size));
        DBG_ERROR((NAV_UPDATER_PREFIX"    SYS Free Space = %llu \n", t_fs_info.ui8_blk_size * t_fs_info.ui8_free_blk));

        *pb_enough = FALSE;
    }
    else
    {
        *pb_enough = TRUE;
    }

    return (UPDATERR_OK);
}

static VOID _nav_updater_usb_copy_file_nfy(
    HANDLE_T           h_req,
    VOID*              pv_tag,
    FM_COPY_NFY_COND_T e_copy_cond,
    UINT32             ui4_data
)
{
    switch (e_copy_cond)
    {
    case FM_COPY_NFY_COND_CONFIRM_FILE_REPLACE:
        {
            FM_CONFIRM_FILE_REPLACE_T* pt_rep = (FM_CONFIRM_FILE_REPLACE_T *)ui4_data;

            pt_rep->b_replace_existing_file = TRUE;
        }
        break;

    case FM_COPY_NFY_COND_PRGS:
        {
            FM_COPY_FILE_PRGS_T* pt_prgs = (FM_COPY_FILE_PRGS_T *)ui4_data;

            DBG_INFO((NAV_UPDATER_PREFIX"Copying (%llu): %d \n", pt_prgs->ui8_file_size, pt_prgs->ui8_transferred_bytes));
        }
        break;

    default:
        DBG_INFO((NAV_UPDATER_PREFIX"_nav_updater_usb_copy_file_nfy: e_copy_cond = %d\n", e_copy_cond));
        break;
    }
}

static INT32 _nav_updater_usb_copy_pkg_file_to_sys(CHAR *psz_dst_folder, CHAR *psz_src_file)
{
    INT32                  i4_ret;
    UPDATER_USB_CTRL_T*    pt_this  = &t_g_usb_ctrl;

    if (!psz_dst_folder || !psz_src_file)
    {
        return UPDATERR_INV_ARG;
    }
#ifdef APP_BASIC_RO
    /*nav_updater_remount_rw(UPDATER_REMOUNT_TYPE_3RD);*/
#endif

    /* Start copy pkg fle to TV System */
    i4_ret = c_fm_copy_file(NULL_HANDLE,
                            psz_src_file,
                            NULL_HANDLE,
                            psz_dst_folder,
                            _nav_updater_usb_copy_file_nfy);
    if (FMR_OK == i4_ret)
    {
        /* Flush file system buffers */
        sync();

        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Download %s to %s successfully \n", psz_src_file, psz_dst_folder));
    }
    else
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Download %s to %s failed,  i4_ret = %d\n", psz_src_file, psz_dst_folder, i4_ret));
    }

    /* do integrity check */
    i4_ret = c_dlm_integrity_check(UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_NAME, NULL);

    if(DLM_OK == i4_ret)
    {
        /* rename the firmware name to mark its integrity is ok */
        CHAR    s_cmd[512] = {0};

        c_sprintf(s_cmd, "mv %s %s",
                         UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_NAME,
                         UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH "/" UPDATER_FW_INTEGRITY_OK_NAME);
        system(s_cmd);
        sync();
    }

    NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Reboot TV System ...\n"));

    pt_this->b_is_sys_reboot = TRUE;
#ifdef APP_BASIC_RO
    /*nav_updater_remount_ro(UPDATER_REMOUNT_TYPE_3RD);*/
#endif

    /* Reboot TV System after copy completed */
    nav_updater_reboot_system();

    return UPDATERR_OK;
}

static INT32 _nav_updater_usb_trigger_copy(VOID)
{
    INT32           i4_ret;
    CHAR            sz_src_path[128]={0};
    CHAR            sz_dst_path[128]={0};
    HANDLE_T        h_file;
    BOOL            b_enough = FALSE;

    /* Check PKG file exist in TV System */
    c_memset(sz_dst_path, 0, sizeof(sz_dst_path));
    c_strcpy(sz_dst_path, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH);
    c_strcat(sz_dst_path, "/");
    c_strcat(sz_dst_path, UPDATER_FW_NAME);
    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       sz_dst_path,
                       FM_MODE_USR_READ,
                       0777,
                       FALSE,
                       &h_file);
    if (FMR_OK == i4_ret)
    {
        c_fm_close(h_file);
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Found PKG in TV: '%s\n ", sz_dst_path));
        return UPDATERR_FAIL;
    }

    /* Check PKG file exist or not in USB */
    i4_ret = _nav_updater_usb_get_path(sz_src_path, 256);
    if(UPDATERR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_usb_get_path faile! i4_ret = %d\n", i4_ret));
        return UPDATERR_FAIL;
    }

    /* Check TV System Free Space */
    c_memset(sz_dst_path, 0, sizeof(sz_dst_path));
    c_strcpy(sz_dst_path, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH);
    i4_ret = _nav_updater_usb_chk_dst_space(sz_dst_path, &b_enough);
    if(UPDATERR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"_nav_updater_usb_chk_dst_space faile! i4_ret = %d\n", i4_ret));
        return UPDATERR_FAIL;
    }
    if (!b_enough)
    {
        return UPDATERR_OUT_MEM;
    }

    /* Integrity check */
    i4_ret = c_dlm_integrity_check(sz_src_path, NULL);
    if(UPDATERR_OK != i4_ret)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"c_dlm_integrity_check faile! i4_ret = %d\n", i4_ret));
        return UPDATERR_FAIL;
    }

    nav_updater_uli_unreg_dev_monitor();

    /* Show message box */
    nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_COPY, NULL);

    /* Start copy pkg file to TV system */
    c_memset(sz_dst_path, 0, sizeof(sz_dst_path));
    c_strcpy(sz_dst_path, UPDATER_COPY_PKG_FILE_TO_FOLDER_PATH);
    c_strcat(sz_dst_path, "/");
    c_strcat(sz_dst_path, UPDATER_FW_NAME);
    _nav_updater_usb_copy_pkg_file_to_sys(sz_dst_path, sz_src_path);

    return UPDATERR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _rmv_dev_nfy_handler
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static VOID _nav_updater_usb_rmv_dev_nfy_handler(
    VOID*                  pv_tag1,
    VOID*                  pv_tag2,
    VOID*                  pv_tag3
)
{
    INT32                  i4_ret;
    UPDATER_USB_CTRL_T*    pt_this  = &t_g_usb_ctrl;
    RMV_DEV_NFY_ID_T       e_nfy_id = (RMV_DEV_NFY_ID_T)((UINT32)pv_tag1);

    if (RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
    {
        if (nav_updater_pkgfile_existed_in_tv())
        {
            NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"<_nav_updater_usb> RMV_DEV_NFY_ID_DEVICE_INSERTED - Skip \n"));
            return;
        }

        i4_ret = _nav_updater_usb_alloc_rmv_res();

        if (NAVR_OK == i4_ret)
        {
            i4_ret = nav_updater_request_update(&(pt_this->b_delay_start));

            if (NAVR_OK == i4_ret)
            {
                nav_updater_trigger_update(pt_this->e_type);
                _nav_updater_usb_trigger_copy();
            }
        }
        else
        {
            _nav_updater_usb_free_res();
        }
    }
    else if (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id)
    {
        _nav_updater_usb_free_res();
        pt_this->b_force_integrity_chk = TRUE;
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_usb_rmv_dev_nfy
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_usb_rmv_dev_nfy(
    VOID*               pv_tag,
    RMV_DEV_NFY_ID_T    e_nfy_id,
    VOID*               pv_nfy_param
)
{
    UPDATER_USB_CTRL_T*    pt_this  = &t_g_usb_ctrl;

    if (pt_this->b_is_sys_reboot)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"<_nav_updater_usb_rmv_dev_nfy> USB b_is_sys_reboot \n"));
        return;
    }

    if((RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
        || (RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id))
    {
        nav_request_context_switch(_nav_updater_usb_rmv_dev_nfy_handler,
                                   (VOID*)e_nfy_id,
                                   NULL,
                                   NULL);
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_usb_preprocess_cb
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static VOID _nav_updater_usb_preprocess_cb(
    VOID*                   pv_tag1,
    VOID*                   pv_tag2,
    VOID*                   pv_tag3
)
{
    UPDATER_USB_CTRL_T*     pt_this = &t_g_usb_ctrl;
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
 * Name: _nav_updater_usb_preprocess
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_usb_preprocess(
    updater_preprocess_cb_fn    pf_preprocess_cb
)
{
    UPDATER_USB_CTRL_T*         pt_this = &t_g_usb_ctrl;

    if (NULL == pf_preprocess_cb)
    {
        return NAVR_FAIL;
    }

    /* assign the callback function */
    pt_this->pf_preprocess_cb = pf_preprocess_cb;

    /* callback the updater core */
    nav_request_context_switch(
                    _nav_updater_usb_preprocess_cb,
                    (VOID*)(TRUE),
                    NULL,
                    NULL);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_usb_handle_msg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static VOID _nav_updater_usb_handle_msg(
    NAV_UI_MSG_T*          pt_ui_msg,
    VOID*                  pv_arg
)
{
    UPDATER_USB_CTRL_T*    pt_this = &t_g_usb_ctrl;

    switch (pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_APP_RESUMED:
            if (TRUE == pt_this->b_delay_start)
            {
                pt_this->b_delay_start = FALSE;
                _nav_updater_usb_rmv_dev_nfy_handler(((VOID*)RMV_DEV_NFY_ID_DEVICE_INSERTED),
                                                   NULL,
                                                   NULL);
            }
            break;

        default:
            break;
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_usb_get_path
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_usb_get_path(
    CHAR*                  ps_buff,
    SIZE_T                 z_buff_len
)
{
    INT32                  i4_ret;
    UPDATER_USB_CTRL_T*    pt_this  = &t_g_usb_ctrl;
    CHAR                   s_tmp[64];

    if (ps_buff == NULL)
    {
        return NAVR_FAIL;
    }

    /* get the mount point path */
    i4_ret = a_fw_updater_get_mnt_point_path(pt_this->ui4_mnt_point_index, s_tmp, 64);

    if(UPDATERR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    c_snprintf(ps_buff, z_buff_len, "%s/%s", s_tmp, pt_this->s_src_file);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_usb_exit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_usb_get_fw(
    UPDATER_ITEM_T*               pt_item,
    updater_progress_notify_fn    pf_progress_cb
)
{
    UPDATER_USB_CTRL_T*           pt_this  = &t_g_usb_ctrl;

    if (TRUE == pt_this->b_force_integrity_chk)
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Do integrity check forcely because the usb device may be unplug and plug!!!\n"));

        return nav_updater_integrity_chk();
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_usb_exit
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_usb_exit(
    BOOL                   b_success
)
{
    UPDATER_USB_CTRL_T*    pt_this  = &t_g_usb_ctrl;

    pt_this->b_force_integrity_chk = FALSE;

    return _nav_updater_usb_free_res();
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
INT32 nav_updater_usb_init(
    VOID
)
{
    UPDATER_DLIVRY_HDLR_REG_T    t_reg;
    INT32                        i4_ret;
    UPDATER_USB_CTRL_T*          pt_this = &t_g_usb_ctrl;

    /* fill data for t_g_usb_ctrl */
    c_memset(pt_this, 0, sizeof(UPDATER_USB_CTRL_T));

    pt_this->e_type = UPDATER_DLIVRY_TYPE_USB;
    c_strcpy(pt_this->s_src_file, UPDATER_FW_NAME);

    /* fill data for t_reg */
    c_memset(&t_reg, 0, sizeof(UPDATER_DLIVRY_HDLR_REG_T));

    t_reg.e_type = pt_this->e_type;

    t_reg.pf_preprocess = _nav_updater_usb_preprocess;
    t_reg.pf_handle_msg = _nav_updater_usb_handle_msg;
    t_reg.pf_get_path   = _nav_updater_usb_get_path;
    t_reg.pf_get_fw     = _nav_updater_usb_get_fw;
    t_reg.pf_exit       = _nav_updater_usb_exit;

    t_reg.pt_io         = NULL;

    t_reg.b_division    = FALSE;

    i4_ret = nav_updater_reg_dlivry_hdlr(&t_reg);

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    /* register to removable deivice utility */
    i4_ret = a_rmv_dev_reg_monitor(
                _nav_updater_usb_rmv_dev_nfy,
                NULL,
                &(pt_this->ui4_rmv_dev_nfy));

    _UPDATER_CHK_FAIL(i4_ret, i4_ret);

    return NAVR_OK;
}
#endif /* APP_MTK_UPG_SUPPORT */

