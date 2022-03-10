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
 *         This file contains all implementations for the updater custom
 *
 * History:
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/


#include "u_pcl.h"
#include "u_rm_dev_types.h"

#include "c_dbg.h"
#include "c_pcl.h"
#include "c_dlm.h"
#include "c_fm.h"
#include "c_os.h"
#include "c_version.h"

#include "app_util/rmv_dev/a_rmv_dev.h"
#include "a_rmv_dev_custom.h"
#include "res/app_util/model/model.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    private methods implementations
 ----------------------------------------------------------------------------*/
RMV_DEV_CHECK_RESULT_T a_rmv_dev_check_device(VOID)
{
    INT32                       i4_ret = RMVR_OK;
    UINT32                      ui4_mnt_count = 0;
    UINT32                      ui4_mnt_point_idx = 0;
    RMV_DEV_CHECK_RESULT_T      e_check_result = RMV_DEV_NOT_FOUND_DEVICE;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    CHAR            s_mnt_name[128 + 1] = {0};
    SIZE_T          z_size = 0;

    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if ((RMVR_OK != i4_ret)
        ||(0 == ui4_mnt_count))
    {
        return RMV_DEV_NOT_FOUND_DEVICE;
    }

    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /* query mount point status */
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx,
                                                       &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        /* do not support this device type */
        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            e_check_result = RMV_DEV_FOUND_UNSUPPORTED_DEVICE;
            continue;
        }

        if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            if (a_is_DLNA_enable())
            { 
                z_size = 128;
                a_rmv_dev_get_mnt_point_info(
                                    ui4_mnt_point_idx,
                                    RMV_DEV_INFO_ID_DESC,
                                    &z_size,
                                    (VOID*)s_mnt_name);
                if (0 == c_strcmp(s_mnt_name, "MediaTek DMR"))
                {
                    DBG_LOG_PRINT(("\n%s,%s,%d,app ui ignore MediaTek DMR\n",
                                 __FILE__, __FUNCTION__, __LINE__));
                    e_check_result = RMV_DEV_FOUND_UNSUPPORTED_DEVICE;
                    continue;
                }
                else
                {
                    e_check_result = RMV_DEV_FOUND_DLNA_DEVICE;
                    break;
                }
            }
            else
            {
                e_check_result = RMV_DEV_FOUND_UNSUPPORTED_DEVICE;
                continue;
            }
        }
        else
        {
            e_check_result = RMV_DEV_FOUND_USB_DEVICE;
            break;
        }
    }

    DBG_LOG_PRINT(("\n%s,%s,%d,e_check_result=%d\n",
               __FILE__, __FUNCTION__, __LINE__,
               e_check_result));

    return e_check_result;
}

INT32 a_rmv_dev_get_effective_mnt_count(UINT32* pui4_mnt_count,
                                                    UINT32* pui4_first_effective_idx)
{
    INT32                       i4_ret = RMVR_OK;
    UINT32                      ui4_mnt_count = 0;
    UINT32                      ui4_mnt_point_idx = 0;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    UINT32                      ui4_effective_mnt_count = 0;
    CHAR            s_mnt_name[128 + 1] = {0};
    SIZE_T          z_size = 0;
    
    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if ((RMVR_OK != i4_ret)
        ||(0 == ui4_mnt_count))
    {
        *pui4_mnt_count = 0;
        return 0;
    }

    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /* query mount point status */
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx,
                                                       &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        /* do not support this device type */
        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            continue;
        }

        if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            if (a_is_DLNA_enable())
            { 
                z_size = 128;
                a_rmv_dev_get_mnt_point_info(
                                    ui4_mnt_point_idx,
                                    RMV_DEV_INFO_ID_DESC,
                                    &z_size,
                                    (VOID*)s_mnt_name);
                if (0 == c_strcmp(s_mnt_name, "MediaTek DMR"))
                {
                    DBG_LOG_PRINT(("\n%s,%s,%d,s_mnt_name=%s\n",
                                 __FILE__, __FUNCTION__, __LINE__,
                                 s_mnt_name));
                    continue;
                }
                else
                {
                    if (0 == ui4_effective_mnt_count)
                    {
                        *pui4_first_effective_idx = ui4_mnt_point_idx;
                    }
                    
                    ui4_effective_mnt_count++;
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            if (0 == ui4_effective_mnt_count)
            {
                *pui4_first_effective_idx = ui4_mnt_point_idx;
            }
            
            ui4_effective_mnt_count++;
        }
    }

    *pui4_mnt_count = ui4_effective_mnt_count;

    DBG_LOG_PRINT(("\n%s,%s,%d,ui4_effective_mnt_count=%d\n",
               __FILE__, __FUNCTION__, __LINE__,
               ui4_effective_mnt_count));
    
    return 0;
}

INT32 a_rmv_dev_get_mount_point_info(RMV_DEV_MNT_POINT_INFO_T* pt_mount_point_info)
{
    INT32                       i4_ret = RMVR_OK;
    UINT32                      ui4_mnt_point_idx = 0;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    UINT32                      ui4_effective_mnt_count = 0;
    CHAR            s_mnt_name[128 + 1] = {0};
    SIZE_T          z_size = 0;
    
    i4_ret = a_rmv_dev_get_mnt_count(&pt_mount_point_info->ui4_mount_count);
    if ((RMVR_OK != i4_ret)
        ||(0 == pt_mount_point_info->ui4_mount_count))
    {
        pt_mount_point_info->ui4_mount_count = 0;
        return 0;
    }

    for (ui4_mnt_point_idx=0; 
         ui4_mnt_point_idx<pt_mount_point_info->ui4_mount_count; 
         ui4_mnt_point_idx++)
    {
        /* query mount point status */
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx,
                                                       &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        /* do not support this device type */
        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            continue;
        }

        if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            if (a_is_DLNA_enable())
            { 
                z_size = 128;
                a_rmv_dev_get_mnt_point_info(
                                    ui4_mnt_point_idx,
                                    RMV_DEV_INFO_ID_DESC,
                                    &z_size,
                                    (VOID*)s_mnt_name);
                if (0 == c_strcmp(s_mnt_name, "MediaTek DMR"))
                {
                    DBG_LOG_PRINT(("\n%s,%s,%d,s_mnt_name=%s\n",
                                 __FILE__, __FUNCTION__, __LINE__,
                                 s_mnt_name));
                    continue;
                }
                else
                {
                    if (0 == ui4_effective_mnt_count)
                    {
                        pt_mount_point_info->ui4_first_effective_idx = ui4_mnt_point_idx;
                    }
                    
                    ui4_effective_mnt_count++;
                    pt_mount_point_info->ui4_last_effective_idx = ui4_mnt_point_idx;
                }
            }
            else
            {
                continue;
            }
        }
        else
        {
            if (0 == ui4_effective_mnt_count)
            {
                pt_mount_point_info->ui4_first_effective_idx = ui4_mnt_point_idx;
            }
            
            ui4_effective_mnt_count++;
            pt_mount_point_info->ui4_last_effective_idx = ui4_mnt_point_idx;
        }
    }

    pt_mount_point_info->ui4_effective_mnt_count = ui4_effective_mnt_count;
    
    return 0;
}

INT32 a_rmv_dev_custom_check_status(RMV_DEV_CUSTOM_CURRENT_STATUS_T* pe_custom_status)
{
    INT32                       i4_ret = RMVR_OK;
    UINT32                      ui4_mnt_count = 0;
    UINT32                      ui4_mnt_point_idx = 0;
    RMV_DEV_CUSTOM_CURRENT_STATUS_T      e_custom_status = RMV_DEV_CUSTOM_CURRENT_WITH_NOTHING;
    RMV_DEV_DEVICE_STATUS_T     e_dev_status = RMV_DEV_DEVICE_STATUS_EMPTY;
    CHAR            s_mnt_name[128 + 1] = {0};
    SIZE_T          z_size = 0;

    i4_ret = a_rmv_dev_get_mnt_count(&ui4_mnt_count);
    if ((RMVR_OK != i4_ret)
        ||(0 == ui4_mnt_count))
    {
        *pe_custom_status = RMV_DEV_CUSTOM_CURRENT_WITH_NOTHING;
        return RMVR_OK;
    }

    for (ui4_mnt_point_idx=0; ui4_mnt_point_idx<ui4_mnt_count; ui4_mnt_point_idx++)
    {
        /* query mount point status */
        i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_mnt_point_idx,
                                                       &e_dev_status);
        if(RMVR_OK != i4_ret)
        {
            continue;
        }

        /* do not support this device type */
        if ((TRUE == RMV_DEV_DEVICE_IS_UNSUPPORT(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_NET_NEIGHBOR(e_dev_status))||
            (TRUE == RMV_DEV_DEVICE_IS_REMOVED(e_dev_status)))
        {
            e_custom_status |= RMV_DEV_CUSTOM_CURRENT_WITH_UNSUPPORT;
            continue;
        }

        if (TRUE == RMV_DEV_DEVICE_IS_DLNA_DMS(e_dev_status))
        {
            if (a_is_DLNA_enable())
            { 
                z_size = 128;
                a_rmv_dev_get_mnt_point_info(
                                    ui4_mnt_point_idx,
                                    RMV_DEV_INFO_ID_DESC,
                                    &z_size,
                                    (VOID*)s_mnt_name);
                if (0 == c_strcmp(s_mnt_name, "MediaTek DMR"))
                {
                    DBG_LOG_PRINT(("\n%s,%s,%d,app ui ignore MediaTek DMR\n",
                                 __FILE__, __FUNCTION__, __LINE__));
                    e_custom_status |= RMV_DEV_CUSTOM_CURRENT_WITH_UNSUPPORT;
                    continue;
                }
                else
                {
                    e_custom_status = RMV_DEV_CUSTOM_CURRENT_WITH_DLNA;
                    continue;
                }
            }
            else
            {
                e_custom_status = RMV_DEV_CUSTOM_CURRENT_WITH_UNSUPPORT;
                continue;
            }
        }
        else
        {
            e_custom_status = RMV_DEV_CUSTOM_CURRENT_WITH_USB;
            break;
        }
    }

    DBG_LOG_PRINT(("\n%s,%s,%d,e_custom_status=0x%x\n",
               __FILE__, __FUNCTION__, __LINE__,
               e_custom_status));

    *pe_custom_status = e_custom_status;

    return 0;
}




