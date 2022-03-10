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
 * $RCSfile: upg_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description: 
 *         This file contains all implementations for the upgrade custom
 *
 * History:
 *           
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
 ----------------------------------------------------------------------------*/


#include "u_pcl.h"

#include "c_pcl.h"
#include "c_dlm.h"
#include "c_fm.h"
#include "c_os.h"
#include "c_version.h"

#include "app_util/upgrade/upg.h"
#include "res/app_util/upgrade/a_upg_custom.h"


/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/


#define UPG_SETTING_ENABLE_BYTE (1)

#define UPG_TEST_TAG_SIZE       (64)

#define MAGIC_BYTE_NUM          (4)
#define LEN_DES_BYTE_NUM        (4)
#define HDR_BYTE_NUM            (MAGIC_BYTE_NUM+LEN_DES_BYTE_NUM)


/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/ 

static UPG_TAG_ENTRY_T t_g_upg_reg_cust[UPGRADE_MAX];

/*-----------------------------------------------------------------------------
                    functions declarations
 ----------------------------------------------------------------------------*/

#ifdef APP_UPG_SUPPORT
extern CHAR* sys_cust_get_usb_upg_version(VOID);
#endif

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: upg_cust_dlm_download
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
static INT32 _upg_cust_download(CHAR * filename, DLM_IO_T * pt_user_io, UCHAR *puc_tag, INT32 i4_check)
{
    return c_dlm_download_by_tag(filename, puc_tag, pt_user_io);
}


/*----------------------------------------------------------------------------
 * Name: _upg_cust_upload
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
static INT32 _upg_cust_upload(CHAR * filename, DLM_IO_T * pt_user_io, UCHAR *puc_tag, INT32 i4_check)
{
    return c_dlm_upload((CHAR*)puc_tag, pt_user_io, filename);
}


/*----------------------------------------------------------------------------
 * Name: _upg_read_data_cust_fn
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
static INT32 _upg_read_data_cust_fn
(
    VOID * pv_data,
    UINT32 ui4_buff_size,
    INT32 * pi4_read,
    const CHAR * pac_path,
    UINT32 ui4_type
)
{
    return upg_read_data_fn(pv_data,ui4_buff_size,pi4_read,pac_path,ui4_type);
}


/*----------------------------------------------------------------------------
 * Name: _upg_firm_nfy
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
static INT32 _upg_firm_nfy
(
    DLM_ACCESS_T e_flag,
    UCHAR *pauc_buffer,
    INT32 *pi4_read
)
{
    if (e_flag == DLM_READ)
    {
        return t_g_upg_reg_cust[UPGRADE_FIRM].t_upg_io.read_to_dlm(
                                                            (VOID*)pauc_buffer,
                                                            t_g_upg_reg_cust[UPGRADE_FIRM].ui4_reg_buff_size,
                                                            pi4_read,
                                                            t_g_upg_reg_cust[UPGRADE_FIRM].as_dev_path,
                                                            UPGRADE_FIRM);
    }
    else
    {
        return t_g_upg_reg_cust[UPGRADE_FIRM].t_upg_io.write_to_tv((VOID*)pauc_buffer,*pi4_read,UPGRADE_FIRM);
    }
}

/*----------------------------------------------------------------------------
 * Name: _upg_firm_write_data
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
static INT32 _upg_firm_write_data
(
    VOID *pv_data,
    UINT32 ui4_data_size,
    UINT32 ui4_type
)
{
    return upg_write_data_fn(
                    pv_data,
                    ui4_data_size,
                    UPGRADE_FIRM,
                    t_g_upg_reg_cust[UPGRADE_FIRM].as_dev_path);
}



/*----------------------------------------------------------------------------
 * Name: _upg_get_item_data
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
static INT32 _upg_get_item_data
(
    UINT32 ui4_item_idx,
    CHAR   *ps_tag_buff,
    CHAR   *ps_buff,
    UINT32 ui4_size
)
{
    UINT32 ui4_total_cust_data_len = ps_tag_buff[0];
    UINT32 ui4_offset = 0;
    UINT32 ui4_idx = 0;

    for (ui4_idx=0; ui4_idx<ui4_item_idx; ui4_idx++)
    {
    	  ui4_offset += LEN_DES_BYTE_NUM;
        ui4_offset += ps_tag_buff[ui4_offset];
    }

    ui4_offset += LEN_DES_BYTE_NUM;
    if (ui4_offset >= ui4_total_cust_data_len)
    {
        return UPGR_FAIL;
    }

    c_strncpy(ps_buff, &ps_tag_buff[ui4_offset+LEN_DES_BYTE_NUM], ps_tag_buff[ui4_offset]);

    return UPGR_OK;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: upg_custom_init
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
INT32 upg_custom_init()
{

    c_memset(&t_g_upg_reg_cust[0], 0, sizeof(UPG_TAG_ENTRY_T)*UPGRADE_MAX);

    c_strcpy((CHAR*)t_g_upg_reg_cust[UPGRADE_FIRM].t_reg_fn.as_reg_name, FIRM_TAG_NAME);
    t_g_upg_reg_cust[UPGRADE_FIRM].t_reg_fn.pf_read     = _upg_read_data_cust_fn;
    t_g_upg_reg_cust[UPGRADE_FIRM].t_reg_fn.pf_write    = _upg_firm_write_data;
    t_g_upg_reg_cust[UPGRADE_FIRM].t_reg_fn.pfunc       = _upg_firm_nfy;
    t_g_upg_reg_cust[UPGRADE_FIRM].t_reg_fn.pf_download = _upg_cust_download;
    t_g_upg_reg_cust[UPGRADE_FIRM].t_reg_fn.pf_upload   = _upg_cust_upload;


    upg_init(&t_g_upg_reg_cust[0], (UINT32) UPGRADE_MAX);

    return UPGR_OK;
}


/*----------------------------------------------------------------------------
 * Name: a_fw_upgrade_cust_tag_test
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
INT32 a_fw_upgrade_cust_tag_test(UINT32 ui4_type, CHAR *ps_fw_name, CHAR *ps_buff, UINT32 ui4_size)
{
    CHAR *ps_tag_buff = 0;
    INT32 i4_ret = 0;

    if (0 == ps_fw_name || 0==ps_buff || ui4_type>=UPGRADE_MAX || 0 == ui4_size)
    {
        return UPGR_INV_ARG;
    }

    switch(ui4_type)
    {
        case UPGRADE_FIRM:
          ps_tag_buff = (CHAR*)c_mem_alloc(ui4_size);/*(*4) for decrypt */
          c_memset(ps_tag_buff, 0 , ui4_size);
          if (DLM_OK == c_dlm_tag_test(ps_fw_name,(UCHAR *)FIRM_TAG_NAME, NULL, ps_tag_buff, ui4_size))
          {
              if ((HDR_BYTE_NUM+ps_tag_buff[4]) <= ui4_size)
              {
                  c_memcpy(ps_buff,ps_tag_buff,HDR_BYTE_NUM+ps_tag_buff[4]);
              }
              else
              {
                  i4_ret = UPGR_FAIL;
              }
          }
          else
          {
              i4_ret = UPGR_FAIL;
          }
          c_mem_free(ps_tag_buff);
          break;

        default:
          i4_ret = UPGR_FAIL;
          break;
    }

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: a_fw_upgrade_cust_get_sys_ver
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
INT32 a_fw_upgrade_cust_get_sys_ver(UINT32 ui4_type, CHAR *ps_buff, UINT32 ui4_size)
{
    INT32 i4_ret = UPGR_OK;
    
    if (0 == ps_buff)
    {
        return UPGR_INV_ARG;
    }

    switch (ui4_type)
    {
        case UPGRADE_FIRM:
#ifdef SHOW_MTK_MW_VER
#ifdef APP_UPG_SUPPORT
          c_strcpy(ps_buff, sys_cust_get_usb_upg_version());
#endif
#else
          c_strcpy(ps_buff, c_sys_get_serial_number());
#endif

          i4_ret= UPGR_OK;
          break;

        default:
          i4_ret = UPGR_INV_ARG;
          break;
    }
    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: a_fw_upgrade_cust_get_file_item_data
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
INT32 a_fw_upgrade_cust_get_file_item_data
(
    UINT32 ui4_type,
    UINT32 ui4_item_idx,
    CHAR   *ps_fw_name,
    CHAR   *ps_buff,
    UINT32 ui4_size
)
{
    CHAR *ps_tag_buff = 0;
    INT32 i4_ret = 0;

    if (0 == ps_fw_name || 0==ps_buff || ui4_type>=UPGRADE_MAX || 0 == ui4_size)
    {
        return UPGR_INV_ARG;
    }

    ps_tag_buff = (CHAR*)c_mem_alloc(ui4_size);/*(*4) for decrypt */
    c_memset(ps_tag_buff, 0 , ui4_size);


    switch(ui4_type)
    {
        case UPGRADE_FIRM:
          if (DLM_OK != c_dlm_tag_test(ps_fw_name,(UCHAR *)FIRM_TAG_NAME, NULL, ps_tag_buff, ui4_size))
          {
              i4_ret = UPGR_FAIL;
          }
          break;

        default:
          i4_ret = UPGR_FAIL;
          break;
    }

    if (UPGR_OK != i4_ret)
    {
        c_mem_free(ps_tag_buff);
        return i4_ret;
    }

    /* check data valid */
    if (((ps_tag_buff[MAGIC_BYTE_NUM] + LEN_DES_BYTE_NUM) > ui4_size) || (0 == ps_tag_buff[MAGIC_BYTE_NUM]) )
    {
        c_mem_free(ps_tag_buff);
        return UPGR_FAIL;
    }


    i4_ret =  _upg_get_item_data(ui4_item_idx, &ps_tag_buff[MAGIC_BYTE_NUM], ps_buff, ui4_size);

    c_mem_free(ps_tag_buff);

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: a_fw_upgrade_cust_write_data_fn
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
INT32 a_fw_upgrade_cust_write_data_fn
(
    VOID *pv_data,
    INT32 i4_size,
    UINT32 ui4_type,
    const CHAR * ps_path
)
{
    INT32 i4_ret = 0;

    switch (ui4_type)
    {
        case UPGRADE_FIRM:
          i4_ret = upg_write_data_fn(pv_data,i4_size,ui4_type,ps_path);
          break;
        default:
          i4_ret = UPGR_INV_ARG;
          break;
    }

    return i4_ret;

}


/*---------------------------------------------------------------------------
 * Name
 *      a_fw_upgrade_cust_reset_value
 * Description:		
 * Input arguments:	
 * Output arguments:	
 * Returns:		
 *---------------------------------------------------------------------------*/
extern INT32 a_fw_upgrade_cust_reset_value(VOID)
{
    /* reset firm handle*/
    if (NULL_HANDLE != t_g_upg_reg_cust[UPGRADE_FIRM].h_in_file)
    {
        c_fm_close(t_g_upg_reg_cust[UPGRADE_FIRM].h_in_file);
        t_g_upg_reg_cust[UPGRADE_FIRM].h_in_file = NULL_HANDLE;
    }
    if (NULL_HANDLE != t_g_upg_reg_cust[UPGRADE_FIRM].h_out_file)
    {
        c_fm_close(t_g_upg_reg_cust[UPGRADE_FIRM].h_out_file);
        t_g_upg_reg_cust[UPGRADE_FIRM].h_out_file = NULL_HANDLE;
    }

    upg_reset_value();

    return UPGR_OK;
}


