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

#include "app_util/updater/updater.h"
#include "res/app_util/updater/a_updater_custom.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define UPDATER_SETTING_ENABLE_BYTE                                         (1)

#define MAGIC_BYTE_NUM                                                      (4)
#define LEN_DES_BYTE_NUM                                                    (4)
#define HDR_BYTE_NUM                        (MAGIC_BYTE_NUM + LEN_DES_BYTE_NUM)

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

static UPDATER_TAG_ENTRY_T*    pt_g_updater_reg_cust = NULL;
static UINT32                  ui4_g_tag_num         = 0;

/*-----------------------------------------------------------------------------
                    private methods implementations
 ----------------------------------------------------------------------------*/
#ifdef APP_UPG_SUPPORT
    extern CHAR* sys_cust_get_usb_upg_version(VOID);
#endif

/*----------------------------------------------------------------------------
 * Name: updater_cust_dlm_download
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
static INT32 _updater_cust_download(
    CHAR*        filename,
    DLM_IO_T*    pt_user_io,
    UCHAR*       puc_tag,
    INT32        i4_check
)
{
    return c_dlm_download_by_tag(filename, puc_tag, pt_user_io);
}

/*----------------------------------------------------------------------------
 * Name: _updater_read_data_cust_fn
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
static INT32 _updater_read_data_cust_fn
(
    VOID*          pv_data,
    UINT32         ui4_buff_size,
    INT32*         pi4_read,
    const CHAR*    pac_path,
    UINT32         ui4_type
)
{
    return updater_read_data_fn(pv_data, ui4_buff_size, pi4_read, pac_path, ui4_type);
}

/*----------------------------------------------------------------------------
 * Name: _updater_write_data_cust_fn
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
static INT32 _updater_write_data_cust_fn
(
    VOID*     pv_data,
    UINT32    ui4_data_size,
    UINT32    ui4_type
)
{
    if (pt_g_updater_reg_cust != NULL)
    {
        return updater_write_data_fn(
                        pv_data,
                        ui4_data_size,
                        ui4_type,
                        pt_g_updater_reg_cust[ui4_type].s_dev_path);
    }
    else
    {
        return UPDATERR_FAIL;
    }
}
#if 0
/*----------------------------------------------------------------------------
 * Name: _updater_get_item_data
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
static INT32 _updater_get_item_data
(
    UINT32    ui4_item_idx,
    CHAR*     ps_tag_buff,
    CHAR*     ps_buff,
    UINT32    ui4_size
)
{
    UINT32    ui4_total_cust_data_len = (UINT32)(UINT8)ps_tag_buff[0];
    UINT32    ui4_offset = 0;
    UINT32    ui4_idx = 0;
    SIZE_T    z_size = 0;

    for (ui4_idx = 0 ; ui4_idx < ui4_item_idx ; ui4_idx++)
    {
        ui4_offset += LEN_DES_BYTE_NUM;
        ui4_offset += ps_tag_buff[ui4_offset];
    }

    ui4_offset += LEN_DES_BYTE_NUM;
    if (ui4_offset >= ui4_total_cust_data_len)
    {
        return UPDATERR_FAIL;
    }

    z_size = (UINT8)(ps_tag_buff[ui4_offset]);
    c_strncpy(ps_buff, &ps_tag_buff[ui4_offset + LEN_DES_BYTE_NUM], z_size);

    return UPDATERR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _updater_cust_get_tag_name
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
static UCHAR* _updater_cust_get_tag_name
(
    UINT32    ui4_idx
)
{
    if ((ui4_idx >= ui4_g_tag_num)
         || (pt_g_updater_reg_cust == NULL))
    {
        return NULL;
    }
    else
    {
        return pt_g_updater_reg_cust[ui4_idx].t_reg_fn.s_reg_name;
    }
}

/*----------------------------------------------------------------------------
 * Name: _updater_nfy
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
static INT32 _updater_nfy
(
    DLM_ACCESS_T    e_flag,
    UCHAR*          pauc_buffer,
    INT32*          pi4_read,
    UINT32          ui4_idx
)
{
    if (pt_g_updater_reg_cust == NULL)
    {
        return UPDATERR_FAIL;
    }

    if (e_flag == DLM_READ)
    {
        return pt_g_updater_reg_cust[ui4_idx].t_updater_io.read_to_dlm(
                                                (VOID*)pauc_buffer,
                                                pt_g_updater_reg_cust[ui4_idx].ui4_reg_buff_size,
                                                pi4_read,
                                                pt_g_updater_reg_cust[ui4_idx].s_dev_path,
                                                ui4_idx);
    }
    else
    {
        return pt_g_updater_reg_cust[ui4_idx].t_updater_io.write_to_tv(
                                                (VOID*)pauc_buffer,
                                                (UINT32)(*pi4_read),
                                                (UINT32)ui4_idx);
    }
}

/*----------------------------------------------------------------------------
 * Name: _updater_firm_nfy
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
static INT32 _updater_general_nfy
(
    UCHAR*          s_tag_name,
    DLM_ACCESS_T    e_flag,
    UCHAR*          pauc_buffer,
    INT32*          pi4_read
)
{
    UINT32          ui4_idx;

    if (pt_g_updater_reg_cust == NULL)
    {
        return UPDATERR_FAIL;
    }

    for (ui4_idx = 0 ; ui4_idx < ui4_g_tag_num ; ui4_idx++)
    {
        if (0 == c_memcmp(
                    pt_g_updater_reg_cust[ui4_idx].t_reg_fn.s_reg_name,
                    s_tag_name,
                    4))
        {
            return _updater_nfy(e_flag, pauc_buffer, pi4_read, ui4_idx);
        }
    }

    /* no match, nothing to do */
    return UPDATERR_OK;
}

/*-----------------------------------------------------------------------------
                    public methods implementations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: updater_custom_init
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
INT32 updater_custom_init(VOID)
{
    return UPDATERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_fw_updater_cust_tag_test
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
INT32 a_fw_updater_cust_tag_test(
    UINT32    ui4_type,
    CHAR*     ps_fw_name,
    CHAR*     ps_buff,
    INT32     i4_size
)
{
    CHAR*     ps_tag_buff = 0;
    INT32     i4_ret = 0;

    if (0 == ps_fw_name || 0 == ps_buff || ui4_type >= ui4_g_tag_num || 0 == i4_size)
    {
        return UPDATERR_INV_ARG;
    }

    if (NULL != _updater_cust_get_tag_name(ui4_type))
    {
        ps_tag_buff = (CHAR*)c_mem_alloc((SIZE_T)i4_size);/*(*4) for decrypt */
        c_memset(ps_tag_buff, 0 , (SIZE_T)i4_size);
        if (DLM_OK == c_dlm_tag_test(
                                ps_fw_name,
                                _updater_cust_get_tag_name(ui4_type),
                                NULL,
                                ps_tag_buff,
                                i4_size))
        {
          if ((HDR_BYTE_NUM + (UINT8)ps_tag_buff[4]) <= i4_size)
          {
              c_memcpy(ps_buff, ps_tag_buff, (SIZE_T)(HDR_BYTE_NUM + (UINT8)ps_tag_buff[4]));
          }
          else
          {
              i4_ret = UPDATERR_FAIL;
          }
        }
        else
        {
          i4_ret = UPDATERR_FAIL;
        }
        c_mem_free(ps_tag_buff);
    }
    else
    {
        i4_ret = UPDATERR_FAIL;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: a_fw_updater_cust_write_data_fn
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
INT32 a_fw_updater_cust_write_data_fn
(
    VOID*          pv_data,
    INT32          i4_size,
    UINT32         ui4_type,
    const CHAR*    ps_path
)
{
    INT32          i4_ret = 0;

    if (ui4_type >= ui4_g_tag_num)
    {
        i4_ret = UPDATERR_INV_ARG;
    }
    else
    {
        i4_ret = updater_write_data_fn(pv_data, (UINT32)i4_size, ui4_type, ps_path);
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: a_fw_updater_cust_get_sys_ver
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
INT32 a_fw_updater_cust_alloc_tag_buff(
    UINT32    ui4_tag_num
)
{
    UINT32    ui4_idx;

    /* allocate memory */
    pt_g_updater_reg_cust = (UPDATER_TAG_ENTRY_T*)c_mem_alloc(sizeof(UPDATER_TAG_ENTRY_T) * ui4_tag_num);

    if (pt_g_updater_reg_cust == NULL)
    {
        return UPDATERR_FAIL;
    }

    c_memset((VOID*)pt_g_updater_reg_cust, 0, sizeof(UPDATER_TAG_ENTRY_T) * ui4_tag_num);
    ui4_g_tag_num = ui4_tag_num;

    if (pt_g_updater_reg_cust == NULL)
    {
        return UPDATERR_FAIL;
    }

    for (ui4_idx = 0 ; ui4_idx < ui4_g_tag_num ; ui4_idx++)
    {
        pt_g_updater_reg_cust[ui4_idx].t_reg_fn.pf_read     = _updater_read_data_cust_fn;
        pt_g_updater_reg_cust[ui4_idx].t_reg_fn.pf_write    = _updater_write_data_cust_fn;
        pt_g_updater_reg_cust[ui4_idx].t_reg_fn.pfunc       = _updater_general_nfy;
        pt_g_updater_reg_cust[ui4_idx].t_reg_fn.pf_download = _updater_cust_download;
    }

    updater_init(pt_g_updater_reg_cust, ui4_tag_num);

    return UPDATERR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_fw_updater_cust_get_sys_ver
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
INT32 a_fw_updater_cust_free_tag_buff(
    VOID
)
{
    /* free memory */
    if (NULL != pt_g_updater_reg_cust)
    {
        c_mem_free(pt_g_updater_reg_cust);
        pt_g_updater_reg_cust = NULL;
    }

    return UPDATERR_OK;
}
extern CHAR* sys_cust_get_usb_upg_version(VOID);
INT32 a_fw_updater_cust_get_sys_ver(UINT32 ui4_type, CHAR *ps_buff, UINT32 ui4_size)
{
    INT32 i4_ret = UPDATERR_OK;
    
    if (0 == ps_buff)
    {
        return UPDATERR_INV_ARG;
    }

    switch (ui4_type)
    {
        case 0:
#ifdef APP_UPG_SUPPORT
          c_strcpy(ps_buff, sys_cust_get_usb_upg_version());
#endif
          i4_ret= UPDATERR_OK;
          break;

        default:
          i4_ret = UPDATERR_INV_ARG;
          break;
    }
    return i4_ret;
}

