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
 * $RCSfile: ulpk.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/

#ifdef APP_USB_INSTALL_ULPK_SUPPORT
#ifdef APP_537X_SUPPORT
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "u_irrc_btn_def.h"
#include "u_fm.h"


#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_fm.h"
#include "c_fm_mfw.h"

#ifdef APP_ULI_UPG_SUPPORT
#include "project-mtk-new-api.h"
#endif

#include "c_rm.h"
#include "u_drv_cust.h"


#include "app_util/a_cfg.h"
#include "app_util/rmv_dev/a_rmv_dev.h"
#include "nav/a_navigator.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "nav/ulpk/ulpk.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
 #define NAV_ULPK_MAX_PATH_LEN             (128)
 #define NAV_ULPK_MSX_FILE_LEN             (3)
 #define NAV_ULPK_BAD_FOLDER              "_bad"
 #define NAV_ULPK_USED_FOLDER             "_used"
 #define NAV_ULPK_MSX_FILE                "key"
 static CHAR                            s_mnt_path[NAV_ULPK_MAX_PATH_LEN];
 static RMV_DEV_OPEN_ID_T               t_rmv_dev_open_id;
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_ULPK_T t_g_nav_ulpk;
static UINT32 ui4_g_nfy_id = RMV_DEV_NULL_NFY_ID;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_led_blink_process
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/


static INT32 _nav_ulpk_led_blink_process(NAV_ULPK_STATE_ID_T t_ulpk_state)
{
    MISC_TYPE_LED_NOTIFY_T t_mtln;
    DRV_CUST_OPERATION_INFO_T   t_op_info ;
    INT32 i4_ret;

    c_memset(&t_op_info, 0, sizeof(DRV_CUST_OPERATION_INFO_T));
    c_memset(&t_mtln, 0, sizeof(MISC_TYPE_LED_NOTIFY_T));

    t_op_info.e_op_type                    = DRV_CUSTOM_OPERATION_TYPE_MISC_SET;
    t_op_info.u.t_misc_set_info.e_misc_type  = DRV_CUSTOM_MISC_TYPE_LED_NOTIFICATION;


    if (NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL == t_ulpk_state)
    {
        t_mtln.e_led_notify_type = DRV_CUSTOM_MISC_LED_UPDATE_FLASHING_EVT;
    }
#ifdef APP_CUST_SPEC_TYPE
    else if (NAV_ULPK_STATE_ID_INSTALL_COMPLETE_SUCCESS == t_ulpk_state)
    {
        t_mtln.e_led_notify_type = DRV_CUSTOM_MISC_LED_UPDATE_FLASHING_EVT_2;
    }
#endif
    else
    {
        /* do nothing*/
    }

    t_op_info.u.t_misc_set_info.pv_set_info = (VOID*)(UINT32)(&t_mtln);

    t_op_info.u.t_misc_set_info.z_size      = sizeof(MISC_TYPE_LED_NOTIFY_T);

    i4_ret = c_rm_set_comp(DRVT_CUST_DRV,
                           DRV_CUST_COMP_ID,
                           FALSE,
                           ANY_PORT_NUM,
                           0,
                           &t_op_info,
                           sizeof(DRV_CUST_OPERATION_INFO_T));
    if (i4_ret != NAVR_OK)
    {
        return NAVR_FAIL;
    }
    return NAVR_OK;

}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ulpk_stop_timer(
                    NAV_ULPK_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop ulpk::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _ulpk_check_key
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ulpk_check_key(const CHAR* ps_file_path)
{
#if 1
    CHAR    s_path[NAV_ULPK_MAX_PATH_LEN] = {0};

    c_strcpy(s_path, ps_file_path);
    if (FALSE == a_uli_is_ulpk_valid_in_given_path(s_path))
    {
        return NAVR_FAIL;
    }
    else
    {
        return NAVR_OK;
    }
#else
    return NAVR_OK;
#endif
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ulpk_check_key
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ulpk_install_key(const CHAR* ps_file_path)
{
    CHAR                        s_buff[128] = {0};
    SIZE_T                      t_size     = 128;
    INT32                       i4_ret;
    HANDLE_T                    h_handle = NULL_HANDLE;
    UINT32                      ui4_read = 0;


    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       ps_file_path,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_handle);

    if (FMR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = c_fm_read(h_handle, (VOID*)s_buff, t_size, &ui4_read);
    if ((FMR_EOF != i4_ret) && (FMR_OK != i4_ret))
    {
        c_fm_close(h_handle);
        return NAVR_FAIL;
    }
    s_buff[ui4_read] = '\0';
    c_fm_close(h_handle);

    i4_ret = a_uli_factory_install_ulpk ((UINT8*)s_buff,
                                         ui4_read);


    if (i4_ret)
    {
        return NAVR_OK;
    }
    else
    {
        return NAVR_FAIL;
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _ulpk_check_one_file
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ulpk_check_one_file(const CHAR* ps_file_path)
{
    SIZE_T              t_length;
    INT32               i4_ret;
    CHAR                s_path_bad[NAV_ULPK_MAX_PATH_LEN];
    CHAR                s_path_used[NAV_ULPK_MAX_PATH_LEN];
    CHAR                s_path[NAV_ULPK_MAX_PATH_LEN];


    INT32               i4_ret_test;

    c_strcpy(s_path_bad, s_mnt_path);
    c_strcat(s_path_bad, "/" NAV_ULPK_BAD_FOLDER);
    c_strcat(s_path_bad, "/");
    c_strcat(s_path_bad, ps_file_path);


    c_strcpy(s_path_used, s_mnt_path);
    c_strcat(s_path_used, "/" NAV_ULPK_USED_FOLDER);
    c_strcat(s_path_used, "/");
    c_strcat(s_path_used, ps_file_path);

    c_strcpy(s_path, s_mnt_path);
    c_strcat(s_path, "/");
    c_strcat(s_path, ps_file_path);


    t_length = c_strlen(ps_file_path);
    if (t_length <= NAV_ULPK_MSX_FILE_LEN)
    {
       return NAVR_FAIL;
    }
    else
    {
        if (0 == c_strcmp((ps_file_path + t_length - NAV_ULPK_MSX_FILE_LEN), NAV_ULPK_MSX_FILE))
        {
            i4_ret = _ulpk_check_key(s_path);

            if (i4_ret == NAVR_OK)
            {
                 /* when the install is ok*/
                 i4_ret_test = c_fm_rename(
                        NULL_HANDLE,
                        s_path,
                        NULL_HANDLE,
                        s_path_used);


                 /* install this ulpk*/
                 _ulpk_install_key(s_path_used);

                 BOOL b_ulpk_is_valid = FALSE;
                 /* if install is ok*/
#ifdef APP_ULI_UPG_SUPPORT
                 b_ulpk_is_valid = a_uli_is_ulpk_valid();
#endif
                 if (b_ulpk_is_valid == TRUE)
                 {
                     a_cfg_custom_set_ulpk_flag(TRUE);
                     i4_ret = NAVR_OK;
                 }
                 else
                 {
                     i4_ret = NAVR_NOT_EXIST;
                 }

            }
            else
            {
                 i4_ret_test = c_fm_rename(
                             NULL_HANDLE,
                             s_path,
                             NULL_HANDLE,
                             s_path_bad);
            }
            return i4_ret;
        }
        else
        {
            return NAVR_FAIL;
        }
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

static INT32 _ulpk_check_one_dir(const CHAR* ps_dir_name)
{
    HANDLE_T            h_dir_hdl;
    FM_DIR_ENTRY_T      t_dir_entr;
    UINT32              ui4_num_entr;
    INT32               i4_ret;

    i4_ret = c_fm_open_dir(FM_ROOT_HANDLE, ps_dir_name, &h_dir_hdl);
    if (FMR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    do
    {
        c_memset(&t_dir_entr, 0, sizeof(FM_DIR_ENTRY_T));

        i4_ret = c_fm_read_dir_entries(h_dir_hdl, &t_dir_entr, 1, &ui4_num_entr);
        if (FMR_EOF == i4_ret)
        {
            nav_set_ulpk_state(NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL);
            nav_return_activation(NAV_COMP_ID_ULPK);
            nav_hide_component(NAV_COMP_ID_ULPK);
            nav_ulpk_activate(NULL,BTN_RED);
            _nav_ulpk_led_blink_process(NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL);
            break;
        }
        else if (FMR_OK != i4_ret || 0 == ui4_num_entr)
        {
            break;
        }

        if ((0 == c_strcmp(t_dir_entr.s_name, "."))  ||
            (0 == c_strcmp(t_dir_entr.s_name, "..")) ||
            FM_IS_DIR(t_dir_entr.t_file_info.ui4_mode))
        {
            continue;
        }

        i4_ret = _ulpk_check_one_file(t_dir_entr.s_name);
        if (NAVR_OK == i4_ret)
        {

            /* to installation the ulpk*/
            nav_set_ulpk_state(NAV_ULPK_STATE_ID_INSTALL_COMPLETE_SUCCESS);
            nav_return_activation(NAV_COMP_ID_ULPK);
            nav_hide_component(NAV_COMP_ID_ULPK);
            nav_ulpk_activate(NULL,BTN_RED);
            _nav_ulpk_led_blink_process(NAV_ULPK_STATE_ID_INSTALL_COMPLETE_SUCCESS);
            break;
        }
        else if (NAVR_NOT_EXIST == i4_ret)
        {
            nav_set_ulpk_state(NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL);
            nav_return_activation(NAV_COMP_ID_ULPK);
            nav_hide_component(NAV_COMP_ID_ULPK);
            nav_ulpk_activate(NULL,BTN_RED);
            _nav_ulpk_led_blink_process(NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL);
            break;
        }
        else
        {
            continue;
        }
    }while(TRUE);

    i4_ret = c_fm_close(h_dir_hdl);
    if (FMR_OK != i4_ret)
    {

    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name     _demo_mode_usb_process
 * Description
 * Input
 * Output   -
 * Returns  -
 *---------------------------------------------------------------------------*/
static VOID _ulpk_usb_process (VOID* pv_arg1, VOID* pv_arg2, VOID* pv_arg3)
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    RMV_DEV_NFY_ID_T e_nfy_id = (RMV_DEV_NFY_ID_T)(UINT32)pv_arg1;

    if(RMV_DEV_NFY_ID_DEVICE_INSERTED == e_nfy_id)
    {
        NAV_ULPK_STATE_ID_T t_ulpk_state = NAV_ULPK_STATE_ID_NONE;
        nav_get_ulpk_state(&t_ulpk_state);
        nav_set_usb_state(NAV_ULPK_USB_STATE_ID_IN);
        if (NAV_ULPK_STATE_ID_PLUG_USB_STICK == t_ulpk_state)
        {
            nav_set_ulpk_state(NAV_ULPK_STATE_ID_INSTALL_ULPK);
            if (pt_this->b_is_on)
            {
                nav_return_activation(NAV_COMP_ID_ULPK);
                nav_hide_component(NAV_COMP_ID_ULPK);
                nav_ulpk_activate(NULL,BTN_RED);
            }
            else
            {
                nav_ulpk_activate(NULL,BTN_RED);
            }

            /* judge if the _bad and the _used is exist , if not exist create them*/

            {
                INT32   i4_ret;
                UINT32  ui4_i;
                SIZE_T  z_size;
                UINT32  ui4_mnt_count = 0;
                RMV_DEV_DEVICE_STATUS_T         t_rmv_dev_status;
                CHAR            s_path_bad[NAV_ULPK_MAX_PATH_LEN];
                CHAR            s_path_used[NAV_ULPK_MAX_PATH_LEN];
                FM_FILE_INFO_T  t_file_bad_info;
                FM_FILE_INFO_T  t_file_used_info;
#if 1
                a_rmv_dev_lock();
#endif
                /* Check all the mount point */
                i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
                if(ui4_mnt_count > 0)
                {
                    for(ui4_i =0; ui4_i<ui4_mnt_count; ui4_i++)
                    {
                        /* Get the mount point status */
                        i4_ret= a_rmv_dev_get_mnt_point_status_by_idx(ui4_i,
                                                                      &t_rmv_dev_status);
                        if(i4_ret != RMVR_OK)
                        {
                            continue;
                        }

                        /* Check the mount point status */
                        if(RMV_DEV_DEVICE_IS_REMOVED(t_rmv_dev_status) ||
                           RMV_DEV_DEVICE_IS_UNSUPPORT(t_rmv_dev_status))
                        {
                            continue;
                        }
                        /* Open mount point */
                        i4_ret = a_rmv_dev_open_mnt_point(ui4_i,
                                                          &t_rmv_dev_open_id);

                         /* Get the mount path */
                        z_size = NAV_ULPK_MAX_PATH_LEN;
                        i4_ret = a_rmv_dev_get_mnt_point(ui4_i,
                                                         &z_size,
                                                         s_mnt_path);
                        c_strcpy(s_path_bad, s_mnt_path);
                        c_strcat(s_path_bad, "/" NAV_ULPK_BAD_FOLDER);


                        c_strcpy(s_path_used, s_mnt_path);
                        c_strcat(s_path_used, "/" NAV_ULPK_USED_FOLDER);


                        /*create folder _bad*/
                        i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE,
                                                       s_path_bad,
                                                       &t_file_bad_info);
                        if (i4_ret != FMR_OK)
                        {
                            i4_ret = c_fm_create_dir(FM_ROOT_HANDLE,
                                                     s_path_bad,
                                                     0777);
                            if(i4_ret != FMR_OK &&
                               i4_ret != FMR_EXIST)
                            {
                                a_rmv_dev_unlock();
                                return ;
                            }
                        }


                         /*create folder _used*/
                        i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE,
                                                       s_path_used,
                                                       &t_file_used_info);
                        if (i4_ret != FMR_OK)
                        {
                            i4_ret = c_fm_create_dir(FM_ROOT_HANDLE,
                                                     s_path_used,
                                                     0777);
                            if(i4_ret != FMR_OK &&
                               i4_ret != FMR_EXIST)
                            {
                                a_rmv_dev_unlock();
                                return ;
                            }
                        }
                        _ulpk_check_one_dir(s_mnt_path);
                    }
                }
#if 1
                a_rmv_dev_unlock();
#endif

            }
        }
    }
    else if(RMV_DEV_NFY_ID_DEVICE_REMOVED == e_nfy_id)
    {
    /*
         nav_return_activation(NAV_COMP_ID_ULPK);
         nav_hide_component(NAV_COMP_ID_ULPK); */
        nav_set_usb_state(NAV_ULPK_USB_STATE_ID_OUT);
        if (pt_this->b_is_on)
        {
            BOOL        b_is_ulpk_valid = FALSE;
#ifdef APP_ULI_UPG_SUPPORT
            b_is_ulpk_valid = a_uli_is_ulpk_valid();
#endif
            if (b_is_ulpk_valid)
            {
                /* do nothing*/
            }
            else
            {
                nav_set_ulpk_state(NAV_ULPK_STATE_ID_INSTALL_COMPLETE_FAIL);
                nav_ulpk_activate(NULL,BTN_RED);
            }
        }
        if (t_rmv_dev_open_id != RMV_DEV_NULL_OPEN_ID)
        {
            RMV_DEV_DEVICE_STATUS_T         t_rmv_dev_status;
            a_rmv_dev_lock();


            /* If the mount point has been opened, try if the device is stiil
               avaiable */
            a_rmv_dev_get_mnt_point_status(t_rmv_dev_open_id,
                                           &t_rmv_dev_status);

            if(RMV_DEV_DEVICE_IS_REMOVED(t_rmv_dev_status))
            {
                /* Free the resources */
                a_rmv_dev_close_mnt_point(t_rmv_dev_open_id);
                t_rmv_dev_open_id = RMV_DEV_NULL_OPEN_ID;
            }

            a_rmv_dev_unlock();
        }
    }

    return;
}

/*-----------------------------------------------------------------------------
 * Name: _demo_mode_usb_nfy_cb
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static VOID _ulpk_usb_nfy_cb(
    VOID*                       pv_unused,
    RMV_DEV_NFY_ID_T            e_nfy_id,
    VOID*                       pv_nfy_param)
{
    /* Context switch to Navigator's thread. */
    nav_request_context_switch (_ulpk_usb_process,
                                (VOID*)(UINT32)e_nfy_id,
                                pv_nfy_param,
                                NULL);
    return;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_trigger_update_nfy_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/



static VOID _nav_ulpk_trigger_update_nfy_handler(
    VOID*                  pv_tag1,
    VOID*                  pv_tag2,
    VOID*                  pv_tag3)
{
    BOOL b_ulpk_flag = FALSE;
    a_cfg_custom_get_ulpk_flag(&b_ulpk_flag);
    if (TRUE == b_ulpk_flag)
    {
        /* do nothing*/
        return;
    }
    else
    {
        BOOL        b_is_ulpk_valid = FALSE;
#ifdef APP_ULI_UPG_SUPPORT
        b_is_ulpk_valid = a_uli_is_ulpk_valid();
#endif
        if (TRUE == b_is_ulpk_valid)
        {
            a_cfg_custom_set_ulpk_flag(TRUE);
            return;
        }
        else
        {
            nav_set_ulpk_state(NAV_ULPK_STATE_ID_PLUG_USB_STICK);
            nav_ulpk_activate(NULL,BTN_RED);
        }

    }
}



/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_fm_partition_status_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

static INT32 _nav_ulpk_fm_partition_status_nfy(
        UINT32             ui4_tag,
        FS_PARTITION_T     e_partition)
{
    if (FS_PARTITION_ALL == e_partition)
    {
        nav_request_context_switch(_nav_ulpk_trigger_update_nfy_handler,
                                   NULL,
                                   NULL,
                                   NULL);
    }

    return NAVR_OK;
}



/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    INT32       i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->t_ulpk_state = NAV_ULPK_STATE_ID_NONE;
    pt_this->b_usb_state  = NAV_ULPK_USB_STATE_ID_NONE;
    pt_this->b_is_on      = FALSE;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }
    /* monitor the usb device*/
    if(RMV_DEV_NULL_NFY_ID == ui4_g_nfy_id)
    {
        a_rmv_dev_reg_monitor( _ulpk_usb_nfy_cb,
                               NULL,
                               &ui4_g_nfy_id);
    }
    c_fm_partition_reg_nfy(_nav_ulpk_fm_partition_status_nfy, 0);
    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset
                    );

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_deinit(VOID)
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    INT32       i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }

    if(RMV_DEV_NULL_NFY_ID != ui4_g_nfy_id)
    {
        i4_ret = a_rmv_dev_unreg_monitor(ui4_g_nfy_id);
        if (i4_ret != NAVR_OK)
        {
            return NAVR_FAIL;
        }

        ui4_g_nfy_id = RMV_DEV_NULL_NFY_ID;
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->t_ulpk_state = NAV_ULPK_STATE_ID_NONE;
    pt_this->b_usb_state  = NAV_ULPK_USB_STATE_ID_NONE;
    pt_this->b_is_on      = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_ulpk_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
     return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ulpk_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ulpk_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    INT32        i4_ret;
    i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    nav_grab_activation(NAV_COMP_ID_ULPK);
    nav_set_component_visible(NAV_COMP_ID_ULPK);
    pt_this->b_is_on = TRUE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
#if 0
    INT32        i4_ret;
    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_APP_RESUMED:
        {
            BOOL        b_is_power_on = FALSE;
            b_is_power_on  = (BOOL)(UINT32)pv_arg1;
            if((b_is_power_on) && (nav_is_resumed_from_app_switch() == FALSE))
            {

                BOOL b_ulpk_flag = FALSE;
#if 0
                nav_set_ulpk_state(NAV_ULPK_STATE_ID_PLUG_USB_STICK);
                nav_ulpk_activate(pt_ctx,BTN_RED);
#endif

                a_cfg_custom_get_ulpk_flag(&b_ulpk_flag);
                if (TRUE == b_ulpk_flag)
                {
                    /* do nothing*/
                    return NAVR_NO_ACTION;
                }
                else
                {
                    BOOL        b_is_ulpk_valid = FALSE;
                    b_is_ulpk_valid = a_uli_is_ulpk_valid();
                    if (TRUE == b_ulpk_flag)
                    {
                        a_cfg_custom_set_ulpk_flag(TRUE);
                        return NAVR_NO_ACTION;
                    }
                    else
                    {
                        nav_set_ulpk_state(NAV_ULPK_STATE_ID_PLUG_USB_STICK);
                        i4_ret = nav_ulpk_activate(pt_ctx,BTN_RED);
                        if (i4_ret != NAVR_OK) {
                            return i4_ret;
                        }
                    }

                }
            }
            break;
        }
        default:
            break;
    }
#endif
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_ulpk_hide(
                    VOID
                    )
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    pt_this->t_view_hdlr.pf_hide();
    pt_this->b_is_on = FALSE;
    _nav_ulpk_stop_timer(pt_this);
    nav_return_activation(NAV_COMP_ID_ULPK);

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ulpk_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    /* execute in navigator's thread context */
    nav_hide_component(NAV_COMP_ID_ULPK);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_ulpk_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_ulpk_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_ulpk_timeout_to_hide, pv_tag, NULL, NULL);
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_ulpk_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_ulpk_reset_timer(
                    NAV_ULPK_T*                 pt_this,
                    UINT32                       ui4_timeout
                    )
{
    INT32 i4_ret;

    _nav_ulpk_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_ulpk_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start ulpk::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * Name
 *      nav_set_ulpk_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

VOID nav_set_ulpk_state(NAV_ULPK_STATE_ID_T t_ulpk_state)
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    pt_this->t_ulpk_state = t_ulpk_state;
}
/*-----------------------------------------------------------------------------
 * Name
 *      nav_get_ulpk_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

VOID nav_get_ulpk_state(NAV_ULPK_STATE_ID_T* pt_ulpk_state)
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    *pt_ulpk_state = pt_this->t_ulpk_state;
}



/*-----------------------------------------------------------------------------
 * Name
 *      nav_set_usb_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

VOID nav_set_usb_state(NAV_ULPK_USB_STATE_ID_T t_usb_state)
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    pt_this->b_usb_state = t_usb_state;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_get_usb_state
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/

VOID nav_get_usb_state(NAV_ULPK_USB_STATE_ID_T* pt_usb_state)
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    *pt_usb_state = pt_this->b_usb_state;
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_ulpk_install_process
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 nav_ulpk_install_process(VOID)
{
    INT32   i4_ret;
    UINT32  ui4_i;
    SIZE_T  z_size;
    UINT32  ui4_mnt_count = 0;
    RMV_DEV_DEVICE_STATUS_T         t_rmv_dev_status;
    CHAR            s_path_bad[NAV_ULPK_MAX_PATH_LEN];
    CHAR            s_path_used[NAV_ULPK_MAX_PATH_LEN];
    FM_FILE_INFO_T  t_file_bad_info;
    FM_FILE_INFO_T  t_file_used_info;
#if 1
    a_rmv_dev_lock();
#endif
    /* Check all the mount point */
    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if(ui4_mnt_count > 0)
    {
        for(ui4_i =0; ui4_i<ui4_mnt_count; ui4_i++)
        {
            /* Get the mount point status */
            i4_ret= a_rmv_dev_get_mnt_point_status_by_idx(ui4_i,
                                                          &t_rmv_dev_status);
            if(i4_ret != RMVR_OK)
            {
                continue;
            }

            /* Check the mount point status */
            if(RMV_DEV_DEVICE_IS_REMOVED(t_rmv_dev_status) ||
               RMV_DEV_DEVICE_IS_UNSUPPORT(t_rmv_dev_status))
            {
                continue;
            }
            /* Open mount point */
            i4_ret = a_rmv_dev_open_mnt_point(ui4_i,
                                              &t_rmv_dev_open_id);

             /* Get the mount path */
            z_size = NAV_ULPK_MAX_PATH_LEN;
            i4_ret = a_rmv_dev_get_mnt_point(ui4_i,
                                             &z_size,
                                             s_mnt_path);
            c_strcpy(s_path_bad, s_mnt_path);
            c_strcat(s_path_bad, "/" NAV_ULPK_BAD_FOLDER);


            c_strcpy(s_path_used, s_mnt_path);
            c_strcat(s_path_used, "/" NAV_ULPK_USED_FOLDER);


            /*create folder _bad*/
            i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE,
                                           s_path_bad,
                                           &t_file_bad_info);
            if (i4_ret != FMR_OK)
            {
                i4_ret = c_fm_create_dir(FM_ROOT_HANDLE,
                                         s_path_bad,
                                         0777);
                if(i4_ret != FMR_OK &&
                   i4_ret != FMR_EXIST)
                {
                    return NAVR_FAIL;
                }
            }


             /*create folder _used*/
            i4_ret = c_fm_get_info_by_name(FM_ROOT_HANDLE,
                                           s_path_used,
                                           &t_file_used_info);
            if (i4_ret != FMR_OK)
            {
                i4_ret = c_fm_create_dir(FM_ROOT_HANDLE,
                                         s_path_used,
                                         0777);
                if(i4_ret != FMR_OK &&
                   i4_ret != FMR_EXIST)
                {
                    return NAVR_FAIL;
                }
            }
            _ulpk_check_one_dir(s_mnt_path);
        }
    }
#if 1
    a_rmv_dev_unlock();
#endif

    return NAVR_OK;

}
/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_ulpk_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_ulpk_register(
                    NAV_ULPK_VIEW_HDLR_T*      pt_view_hdlr
                    )
{
    NAV_ULPK_T* pt_this = &t_g_nav_ulpk;
    NAV_COMP_T  t_comp;
    INT32       i4_ret;

    /* NAV_COMP_ID_ULPK */
    c_memset (& t_comp, 0, sizeof(NAV_COMP_T));
    t_comp.pf_init           = _nav_ulpk_init;
    t_comp.pf_deinit         = _nav_ulpk_deinit;
    t_comp.pf_is_key_handler = _nav_ulpk_is_key_handler;
    t_comp.pf_activate       = NULL;
    t_comp.pf_inactivate     = _nav_ulpk_inactivate;
    t_comp.pf_hide           = _nav_ulpk_hide;
    t_comp.pf_handle_msg     = _nav_ulpk_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_ULPK, &t_comp, COMP_EXEC_SET_ULPK);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_view_hdlr == NULL) {
        nav_ulpk_view_register_default_hdlr(&pt_this->t_view_hdlr);
    } else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }

    return NAVR_OK;
}
#endif
#endif
