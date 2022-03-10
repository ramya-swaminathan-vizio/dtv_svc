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

#include "c_dlm.h"
#include "u_xml.h"
#include "c_xml_api.h"
#include "c_fm.h"
#include "c_pcl.h"
#include "nav/updater/nav_updater.h"
#include "res/app_util/updater/a_updater_custom.h"
#include "res/nav/updater/nav_updater_res.h"
#include "res/app_util/config/acfg_custom.h"

#ifdef MLC_EMMC_MG_COMMON_SUPPORT
#include "c_rm.h"
#include "u_drv_cust.h"
#endif

#include <stdlib.h>
#include "res/nav/nav_dbg.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#define UPDATER_XML_VALUE(pt_xml)   ((pt_xml != NULL) ? XML_Value(pt_xml) : "")
#define UPDATER_TOKENS                                                 "-_\n,."

/*-----------------------------------------------------------------------------
                     variable declarations
 ----------------------------------------------------------------------------*/

UPDATER_CONFIG_T    t_updater_cfg;

/*-----------------------------------------------------------------------------
                     private methods implementation
 ----------------------------------------------------------------------------*/
#ifdef MLC_EMMC_MG_COMMON_SUPPORT

/*-----------------------------------------------------------------------------
 * Name: nav_updater_cfg_get_flash_name
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/

INT32 nav_updater_cfg_get_flash_name(UINT32*      pui4_flash_type)
{
    DRV_CUST_OPERATION_INFO_T    t_op_info;
    INT32                        i4_ret = 0;
    UINT32                       ui4_flash_type = 0;
    SIZE_T                       z_size_drv = sizeof(DRV_CUST_OPERATION_INFO_T);
    SIZE_T                       z_size = sizeof(UINT32);

    /* set operation type */
    t_op_info.e_op_type = DRV_CUSTOM_OPERATION_TYPE_CUST_SPEC_GET;
    t_op_info.u.t_cust_spec_get_info.e_cust_spec_type = DRV_CUSTOM_CUST_SPEC_TYPE_GET_BOOTTYPE;
    t_op_info.u.t_cust_spec_get_info.pv_get_info = &ui4_flash_type;
    t_op_info.u.t_cust_spec_get_info.pz_size = &z_size;

    /*get driver value */
    i4_ret = c_rm_get_comp(
                            DRVT_CUST_DRV,
                            DRV_CUST_COMP_ID,
                            FALSE,
                            ANY_PORT_NUM,
                            0,
                            &t_op_info,
                            &z_size_drv
                            );

    if (i4_ret != RMR_OK)
    {
        return NAVR_FAIL;
    }
    else
    {
        *pui4_flash_type = ui4_flash_type;
        return NAVR_OK;
    }
}
#endif

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_fill_sys_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 _nav_updater_cfg_fill_sys_info(
    XML_T*                pt_download_xml,
    UPDATER_FW_INFO_T*    pt_fw_info
)
{
    XML_Element*          pt_ele_sys;
    XML_Element*          pt_ele_temp;

    pt_ele_sys = c_xml_get_element(pt_download_xml, "SYS_INFO");
    if (pt_ele_sys == NULL)
    {
        return NAVR_FAIL;
    }

    /* MANUFACTURER */
    pt_ele_temp = c_xml_get_element(pt_ele_sys, "MANUFACTURER");
    c_strncpy(pt_fw_info->s_manufacturer, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);

    /* MODEL */
    pt_ele_temp = c_xml_get_element(pt_ele_sys, "MODEL");
    c_strncpy(pt_fw_info->s_model, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);

    /* IC_VER */
    pt_ele_temp = c_xml_get_element(pt_ele_sys, "IC_VER");
    c_strncpy(pt_fw_info->s_ic_ver, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);

    /* HW_VER */
    pt_ele_temp = c_xml_get_element(pt_ele_sys, "HW_VER");
    c_strncpy(pt_fw_info->s_hw_ver, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);

    /* BUILD_NAME */
    pt_ele_temp = c_xml_get_element(pt_ele_sys, "BUILD_NAME");
    c_strncpy(pt_fw_info->s_build_name, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);

    /* BUILD_DATE */
    pt_ele_temp = c_xml_get_element(pt_ele_sys, "BUILD_DATE");
    c_strncpy(pt_fw_info->s_build_date, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);

    /* SERIAL_NUM */
    pt_ele_temp = c_xml_get_element(pt_ele_sys, "SERIAL_NUM");
    c_strncpy(pt_fw_info->s_serial_num, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_get_sw_info_num
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 _nav_updater_cfg_get_sw_info_num(
    XML_T*         pt_download_xml,
    UINT32*        pui4_num
)
{
    XML_NODE_T*    pt_node_sw = NULL;

    if ((pt_download_xml == NULL) || (pui4_num == NULL))
    {
        return NAVR_FAIL;
    }

    pt_node_sw = c_xml_get_elements_by_tag_name(pt_download_xml, "SW");
    if (pt_node_sw == NULL)
    {
        return NAVR_FAIL;
    }
    *pui4_num = XML_NodeLength(pt_node_sw);

    if (pt_node_sw != NULL)
    {
        c_xml_free_node(pt_node_sw);
    }

    return NAVR_OK;
}
#ifdef MLC_EMMC_MG_COMMON_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: nav_updater_cfg_get_dual_bank_type_by_tag
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 nav_updater_cfg_get_dual_bank_type_by_tag(
    CHAR*                    ps_tag,
    PCL_DUAL_BANK_TYPE_T*    pt_type
)
{
    UINT32       ui4_flash_type = 0;
    
    if (NULL == pt_type)
    {
        return NAVR_FAIL;
    }
	DBG_LOG_PRINT(("%s_%d ps_tag:%s \n",__FUNCTION__,__LINE__,ps_tag));
    
	if (NAVR_OK != nav_updater_cfg_get_flash_name(&ui4_flash_type))
	{
	    DBG_LOG_PRINT((NAV_UPDATER_PREFIX"flash type get fail!!\n"));
        return NAVR_FAIL;
	}

    if (1 == ui4_flash_type)
    {

        /* it is signature => signature need to be compared with kernel, so use the same bank index of kernel */
        if (0 == c_strncmp(UPDATER_SIGNATURE_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
        {
            *pt_type = PCL_DUAL_BANK_KERNEL;

            return NAVR_OK;
        }
        /* it is kernel */
        if (0 == c_strncmp(UPDATER_KERNEL_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
        {
            *pt_type = PCL_DUAL_BANK_KERNEL;

            return NAVR_OK;
        }
        /* it is rootfs */
        if (0 == c_strncmp(UPDATER_ROOTFS_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
        {
            *pt_type = PCL_DUAL_BANK_ROOTFS;

            return NAVR_OK;
        }
    }
    else if (2 == ui4_flash_type)
    {
        
        /* it is kernel */
        if (0 == c_strncmp(UPDATER_KERNEL_TAG_EMMC_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
        {
            *pt_type = PCL_DUAL_BANK_KERNEL;

            return NAVR_OK;
        }
        /* it is rootfs */
        if (0 == c_strncmp(UPDATER_ROOTFS_TAG_EMMC_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
        {
            *pt_type = PCL_DUAL_BANK_ROOTFS;

            return NAVR_OK;
        }
    }
    else
    {
        return NAVR_FAIL;
    }

    return NAVR_FAIL;
}

#else
/*-----------------------------------------------------------------------------
 * Name: nav_updater_cfg_get_dual_bank_type_by_tag
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 nav_updater_cfg_get_dual_bank_type_by_tag(
    CHAR*                    ps_tag,
    PCL_DUAL_BANK_TYPE_T*    pt_type
)
{
    if (NULL == pt_type)
    {
        return NAVR_FAIL;
    }
	DBG_LOG_PRINT(("%s_%d ps_tag:%s \n",__FUNCTION__,__LINE__,ps_tag));

    /* it is signature => signature need to be compared with kernel, so use the same bank index of kernel */
    if (0 == c_strncmp(UPDATER_SIGNATURE_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
    {
        *pt_type = PCL_DUAL_BANK_KERNEL;

        return NAVR_OK;
    }
    /* it is kernel */
    if (0 == c_strncmp(UPDATER_KERNEL_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
    {
        *pt_type = PCL_DUAL_BANK_KERNEL;

        return NAVR_OK;
    }
    /* it is rootfs */
    if (0 == c_strncmp(UPDATER_ROOTFS_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
    {
        *pt_type = PCL_DUAL_BANK_LINUX_ROOTFS;

        return NAVR_OK;
    }

    /* it is system */
    if (0 == c_strncmp(UPDATER_SYSTEM_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
    {
        *pt_type = PCL_DUAL_BANK_CAST_SYSTEM;

        return NAVR_OK;
    }
	
    /* it is chrome */
    if (0 == c_strncmp(UPDATER_CHROME_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
    {
        *pt_type = PCL_DUAL_BANK_CHROME;

        return NAVR_OK;
    }

    /* it is 3RD */
    if (0 == c_strncmp(UPDATER_3RD_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
    {
        *pt_type = PCL_DUAL_BANK_3RD;

        return NAVR_OK;
    }

    /* it is linux_rootfs of Two-Worlds */
    if (0 == c_strncmp(UPDATER_LINUX_ROOTFS_TAG_NAME, ps_tag, UPDATER_TAG_NAME_LEN))
    {
        *pt_type = PCL_DUAL_BANK_LINUX_ROOTFS;

        return NAVR_OK;
    }

    return NAVR_FAIL;
}
#endif

#ifdef APP_ONE_IMAGE_UPDATER_SUPPORT
static INT32 _nav_updater_cfg_get_platform_odm_id(UINT8  *pui1_odm_id)
{
	UINT8  ui1_id = 0;
    INT32  i4_ret;
	
	/*
	 the meaning of ui1_id is as following:
	 0 ---> common;
	 1 ---> Amtran;
	 3 ---> Wistron;
	 4 ---> Foxconn;
	 */

	i4_ret = a_cfg_custom_get_odm_idx(&ui1_id);
	if (APP_CFGR_OK != i4_ret)
	{
		DBG_LOG_PRINT(("\n[NAV_UPDATER_TEST] _nav_updater_cfg_get_platform_odm_id Fail !!!!!!!\n"));
		return NAVR_FAIL;
	}

	*pui1_odm_id = ui1_id;
	
	DBG_LOG_PRINT(("\n[NAV_UPDATER_TEST] _nav_updater_cfg_get_platform_odm_id ui1_odm_id[%d]\n",
		   *pui1_odm_id));
	
	return NAVR_OK;
}

#endif
/*-----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_fill_sw_info_by_idx
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 _nav_updater_cfg_fill_sw_info_by_idx(
    XML_T*                  pt_download_xml,
    UINT32                  ui4_idx,
    UPDATER_ITEM_T*         pt_item_info
)
	{
		XML_NODE_T* 			pt_node_sw;
		UINT32					ui4_num;
		XML_Element*			pt_ele_sw;
		XML_Element*			pt_ele_temp;
		XML_Element*			pt_ele_temp2;
		INT32					i4_ret;
		UINT8					ui1_bank_idx = 0;
		UINT8					ui1_part_id;
		PCL_DUAL_BANK_TYPE_T	e_dual_bank;
#ifdef APP_ONE_IMG_FOR_MULTI_NAND
		CHAR					s_nand_name[UPDATER_MAX_BUFF_LEN];
#endif
	
		if ((NULL == pt_download_xml) || (NULL == pt_item_info))
		{
			return NAVR_FAIL;
		}
	
		/* clear this item info first */
		c_memset((VOID*)pt_item_info, 0, sizeof(UPDATER_ITEM_T));
	
		pt_node_sw = c_xml_get_elements_by_tag_name(pt_download_xml, "SW");
		if (NULL == pt_node_sw)
		{
			return NAVR_FAIL;
		}
		ui4_num = XML_NodeLength(pt_node_sw);
	
		if (ui4_idx > ui4_num)
		{
			return NAVR_FAIL;
		}
	
		/* get the ui4_idx SW_INFO */
		pt_ele_sw = XML_NodeItem(pt_node_sw, ui4_idx);
	
		/* TAG */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "TAG");
		c_strncpy(pt_item_info->s_tag, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_TAG_NAME_LEN);
	
		/* NAME */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "NAME");
		c_strncpy(pt_item_info->s_name, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);
	
		/* METHOD */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "METHOD");
	
		pt_item_info->e_method = (0 == c_strcmp("PART", UPDATER_XML_VALUE(pt_ele_temp)))
								  ? UPDATER_METHOD_PART
								  : UPDATER_METHOD_FILE;
	
		/* FILE_NAME */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "FILE_NAME");
		c_strncpy(pt_item_info->s_file_name, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN - 1);
	
#ifdef APP_ONE_IMG_FOR_MULTI_NAND
		/* NAND_TYPE */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "NAND");
		if (!_nav_updater_cfg_get_nand_name(s_nand_name, UPDATER_MAX_BUFF_LEN))
		{
			return NAVR_FAIL;
		}
		if (c_strcmp(s_nand_name, UPDATER_XML_VALUE(pt_ele_temp)) == 0 || c_strcmp("NAND_ALL", UPDATER_XML_VALUE(pt_ele_temp)) == 0)
		{
			pt_item_info->b_nand_match = TRUE;
		}
		else
		{
			pt_item_info->b_nand_match = FALSE;
		}
		DBG_LOG_PRINT((NAV_UPDATER_PREFIX"\nFunc:%s,ui4_idx:%d,current_nand:%s,nand:%s,b_nand_match:%d\n",
			__FUNCTION__, ui4_idx,s_nand_name, UPDATER_XML_VALUE(pt_ele_temp),pt_item_info->b_nand_match));
#endif
	
		/* VER */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "VER");
		c_strncpy(pt_item_info->s_ver, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);
	
		/*Storage Type*/
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "STORAGE_TYPE");
		c_strncpy(pt_item_info->s_storageType, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);
	
		if(c_strncmp(pt_item_info->s_storageType, "EEPROM", UPDATER_MAX_BUFF_LEN) == 0)
		{
			pt_ele_temp = c_xml_get_element(pt_ele_sw, "PATH");
	
			if(pt_ele_temp == NULL)
			{
				DBG_LOG_PRINT((NAV_UPDATER_PREFIX" get eeprom path fail \n"));
				return NAVR_FAIL;
			}
	
			CHAR* ps_str = UPDATER_XML_VALUE(pt_ele_temp);
	
			if(ps_str[0] >= '0' && ps_str[0] <= '9')
			{
				c_sprintf(pt_item_info->s_dev_path, SN_DEV_PATH"/eeprom_%s", ps_str);
			}
			else
			{
				c_strcpy(pt_item_info->s_dev_path, SN_DEV_PATH "/");
				c_strcat(pt_item_info->s_dev_path, ps_str);
			}
	
			DBG_LOG_PRINT((NAV_UPDATER_PREFIX"eeprom path: %s \n", pt_item_info->s_dev_path));
		}
		else
		{
			/* PATH */
			if (UPDATER_METHOD_PART == pt_item_info->e_method)
			{
				/* partition based */
				pt_ele_temp = c_xml_get_element(pt_ele_sw, "PATH");
				pt_ele_temp2 = c_xml_get_element(pt_ele_sw, "PATH2");
	
				/* maybe dual bank */
				if (NULL != pt_ele_temp2)
				{
            #ifndef AP_UPGRADE_BIN_FMT_SUPPORT
					/* type support? */
					i4_ret = _nav_updater_cfg_get_dual_bank_type_by_tag(pt_item_info->s_tag, &e_dual_bank);
	
					if (NAVR_OK == i4_ret)
            #endif
					{
                #ifdef AP_UPGRADE_BIN_FMT_SUPPORT
						if ((UINT8)c_strtoull(UPDATER_XML_VALUE(pt_ele_temp), NULL, 10) ==
							(UINT8)c_strtoull(UPDATER_XML_VALUE(pt_ele_temp2), NULL, 10))
						{
							DBG_LOG_PRINT((NAV_UPDATER_PREFIX"single bank.\n"));
							ui1_bank_idx = 0;
						}
						else
                #endif
						{
                    #ifndef AP_UPGRADE_BIN_FMT_SUPPORT
							/* it's dual bank -> get current index */
							i4_ret = c_pcl_get_dual_bank_index(e_dual_bank, &ui1_bank_idx);
                    #else
							/*
							 * We will only use PCL_MISC_CTRL_DUAL_BANK_ROOTFS bit to hold the
							 * bank index in 1901.
							 */
							i4_ret = c_pcl_get_dual_bank_index(PCL_DUAL_BANK_ROOTFS, &ui1_bank_idx);
                    #endif
	
							if (PCLR_OK == i4_ret)
							{
								/* toggle the bank index, 0 => 1, 1 => 0 */
								ui1_bank_idx = (ui1_bank_idx == 0) ? 1 : 0 ;
	
								/* set the dual bank flag, so that updater could toggle the bank index after this item is upgraded successfully */
								/* don't need for signature, because it is compared with kernel  */
								if (0 != c_strncmp(UPDATER_SIGNATURE_TAG_NAME, pt_item_info->s_tag, UPDATER_TAG_NAME_LEN))
								{
									pt_item_info->ui4_flag |= UPDATER_ITEM_FLAG_DUAL_BANK;
								}
							}
						}
					}
            #ifndef AP_UPGRADE_BIN_FMT_SUPPORT
					else if (0 == c_strncmp(UPDATER_3RD_TAG_NAME, pt_item_info->s_tag, UPDATER_TAG_NAME_LEN))
					{
						UINT8 ui1_3rd_part1_id = (UINT8)c_strtoull(UPDATER_XML_VALUE(pt_ele_temp), NULL, 10);
						UINT8 ui1_3rd_part2_id = (UINT8)c_strtoull(UPDATER_XML_VALUE(pt_ele_temp2), NULL, 10);
	
						if (ui1_3rd_part1_id != ui1_3rd_part2_id)
						{
							DBG_LOG_PRINT((NAV_UPDATER_PREFIX"3RD dual bank supported!! \n", i4_ret));
							pt_item_info->b_3rd_dual_bank = TRUE;
	
							/* TODO: If support dual 3rd bank method, should check next bank index!! */
							ui1_bank_idx = 0;
						}
						else
						{
							DBG_LOG_PRINT((NAV_UPDATER_PREFIX"3RD single bank supported!! \n", i4_ret));
							pt_item_info->b_3rd_dual_bank = FALSE;
							ui1_bank_idx = 0;
						}
					}
            #endif
				}
	
				c_strcat(pt_item_info->s_dev_path, SN_DEV_PATH "/");
	
				ui1_part_id = (0 == ui1_bank_idx)
							  ? (UINT8)c_strtoull(UPDATER_XML_VALUE(pt_ele_temp), NULL, 10)
							  : (UINT8)c_strtoull(UPDATER_XML_VALUE(pt_ele_temp2), NULL, 10);
	
				pt_item_info->ui1_part_id = ui1_part_id;
	
				switch (ui1_part_id)
				{
					case 0:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_0);
						break;
					case 1:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_1);
						break;
					case 2:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_2);
						break;
					case 3:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_3);
						break;
					case 4:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_4);
						break;
					case 5:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_5);
						break;
					case 6:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_6);
						break;
					case 7:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_7);
						break;
					case 8:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_8);
						break;
					case 9:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_9);
						break;
					case 10:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_10);
						break;
					case 11:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_11);
						break;
					case 12:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_12);
						break;
					case 13:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_13);
						break;
					case 14:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_14);
						break;
					case 15:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_15);
						break;
					case 16:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_16);
						break;
					case 17:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_17);
						break;
					case 18:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_18);
						break;
					case 19:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_19);
						break;
					case 20:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_20);
						break;
					case 21:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_21);
						break;
					case 22:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_22);
						break;
					case 23:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_23);
						break;
					case 24:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_24);
						break;
            #ifdef SYS_EMMC_SUPPORT
					case 25:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_25);
						break;
					case 26:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_26);
						break;
					case 27:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_27);
						break;
					case 28:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_28);
						break;
					case 29:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_29);
						break;
					case 30:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_30);
						break;
					case 31:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_31);
						break;
					case 32:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_32);
						break;
					case 33:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_33);
						break;
					case 34:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_34);
						break;
					case 35:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_35);
						break;
					case 36:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_36);
						break;
					case 37:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_37);
						break;
					case 38:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_38);
						break;
					case 39:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_39);
						break;
					case 40:
						c_strcat(pt_item_info->s_dev_path, SN_MTD_BLK_40);
						break;
            #endif
					default:
						return NAVR_FAIL;
				}
	
				DBG_LOG_PRINT((NAV_UPDATER_PREFIX"Tag: %s, path: %s \n",pt_item_info->s_tag, pt_item_info->s_dev_path));
			}
			else
			{
				/* file based */
#ifndef APP_UPG_FILE_BASED_ITEM_TO_USB
				c_strcat(pt_item_info->s_dev_path, UPDATER_FILE_BASED_UPG_PATH "/");
				if((c_strlen(pt_item_info->s_dev_path) + c_strlen(pt_item_info->s_file_name)) < UPDATER_DEV_PATH_LEN)
				{
					c_strcat(pt_item_info->s_dev_path, pt_item_info->s_file_name);
				}
				else
				{
					return NAVR_FAIL;
				}
#else
				/* get the mount point path */
				CHAR					   s_mnt_path[128] = {0};
				UINT32					   ui4_i;
				UINT32					   ui4_count;
				RMV_DEV_DEVICE_STATUS_T    e_dev_status;
	
				i4_ret = a_rmv_dev_get_mnt_count(&ui4_count);
	
				if (RMVR_OK != i4_ret || 0 == ui4_count)
				{
					return NAVR_FAIL;
				}
	
				for (ui4_i = 0 ; ui4_i < ui4_count ; ui4_i++)
				{
					i4_ret = a_rmv_dev_get_mnt_point_status_by_idx(ui4_i, &e_dev_status);
	
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
					i4_ret = a_fw_updater_get_mnt_point_path(ui4_i, s_mnt_path, 64);
	
					if(UPDATERR_OK != i4_ret)
					{
						DBG_LOG_PRINT((NAV_UPDATER_PREFIX"Get mount path for USB dongle faile! i4_ret = %d\n", i4_ret));
						return NAVR_FAIL;
					}
					break;
				}
	
				c_sprintf(pt_item_info->s_dev_path, "%s/", s_mnt_path);
				c_strcat(pt_item_info->s_dev_path, pt_item_info->s_file_name);
#endif
			}
		}
	
		/* SIZE */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "SIZE");
		pt_item_info->ui4_size = c_strtoull(UPDATER_XML_VALUE(pt_ele_temp), NULL, 10);
	
		/* OFFSET */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "OFFSET");
		pt_item_info->ui4_offset = c_strtoull(UPDATER_XML_VALUE(pt_ele_temp), NULL, 10);
	
		/* CHECKSUM */
		pt_ele_temp = c_xml_get_element(pt_ele_sw, "CHECKSUM");
		c_strncpy(pt_item_info->s_checksum, UPDATER_XML_VALUE(pt_ele_temp), UPDATER_MAX_BUFF_LEN);
	
		if (NULL != pt_node_sw)
		{
			c_xml_free_node(pt_node_sw);
		}
	
		return NAVR_OK;
	}



/*-----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_parse_xml_to_fw_info
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 _nav_updater_cfg_parse_xml_to_fw_info(
    CHAR*                 ps_path,
    UPDATER_FW_INFO_T*    pt_fw_info,
    XML_T**               ppt_xml
)
{
    INT32                 i4_ret = NAVR_OK;
    CHAR*                 ps_buff = NULL;
    SIZE_T                z_buff_len;
    XML_T*                pt_tmp_xml = NULL;
    UINT32                ui4_num = 0;
    UINT32                ui4_idx;
    HANDLE_T              h_xml_file = NULL_HANDLE;
    UINT32                ui4_read = 0;

    /* check parameters */
    if ((NULL == ps_path) || (NULL == pt_fw_info))
    {
        return NAVR_FAIL;
    }

    /* allocate memory */
    z_buff_len = (sizeof(CHAR) * UPDATER_XML_HDR_SZ ) - sizeof(Append_DATA_TLV_T);

    ps_buff = (CHAR*)c_mem_alloc(z_buff_len);
    c_memset((VOID*)ps_buff, 0, z_buff_len);

    do
    {
        /* read XML file to memory */
        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                           ps_path,
                           FM_READ_ONLY,
                           0777,
                           FALSE,
                           &h_xml_file);

        if (FMR_OK != i4_ret)
        {
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = c_fm_read(h_xml_file, (VOID*)ps_buff, (UINT32)z_buff_len, &ui4_read);
        if ((FMR_OK != i4_ret) && (FMR_EOF != i4_ret))
        {
            i4_ret = NAVR_FAIL;
            break;
        }


        /* parse the buffer */
        i4_ret = c_xml_parse_buffer(ps_buff, ui4_read, &pt_tmp_xml);

        if(XML_SUCCESS != i4_ret)
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"XML parse failed!i4_ret=%d \n",i4_ret));

            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = _nav_updater_cfg_fill_sys_info(pt_tmp_xml, pt_fw_info);
        if (NAVR_OK != i4_ret)
        {
            break;
        }

        i4_ret = _nav_updater_cfg_get_sw_info_num(pt_tmp_xml, &ui4_num);
        if ((NAVR_OK != i4_ret) && (ui4_num > UPDATER_MAX))
        {
            break;
        }

        /* save the item number */
        pt_fw_info->ui4_item_num = ui4_num;
		DBG_LOG_PRINT(("%s_%d ui4_item_num:%d \n",__FUNCTION__,__LINE__,pt_fw_info->ui4_item_num));
        /* get all item information */
        for (ui4_idx = 0 ; ui4_idx < pt_fw_info->ui4_item_num ; ui4_idx++)
        {
            _nav_updater_cfg_fill_sw_info_by_idx(pt_tmp_xml, ui4_idx, &(pt_fw_info->pt_item[ui4_idx]));
#ifdef MLC_EMMC_MG_COMMON_SUPPORT
            if ((pt_fw_info->pt_item[ui4_idx].b_flash_match)
#ifdef APP_ONE_IMAGE_UPDATER_SUPPORT
				&& (pt_fw_info->pt_item[ui4_idx].b_odm_id_match)
#endif
               )
#else
#ifdef APP_ONE_IMAGE_UPDATER_SUPPORT

			if (pt_fw_info->pt_item[ui4_idx].b_odm_id_match)
#endif
#endif
            {
                /* by default, we select all items */
                pt_fw_info->pt_item[ui4_idx].ui4_flag |= UPDATER_ITEM_FLAG_SELECTED;
            }
        }
    }
    while(0);

    /* close XML file */
    if (NULL_HANDLE != h_xml_file)
    {
        c_fm_close(h_xml_file);
    }

    /* free memory */
    c_mem_free(ps_buff);

    if (NAVR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* save the XML tree structure */
    *ppt_xml = pt_tmp_xml;

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_gen_md5_chksum
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
#ifdef APP_PRE_UPG_CHK
INT32 _nav_updater_gen_md5_chksum(
    CHAR*    ps_src_path,
    CHAR*    ps_md5_path
)
{
    CHAR    s_cmd[256] = {0};

    c_sprintf(s_cmd, "md5sum %s > %s", ps_src_path, ps_md5_path);

    if (0 != system(s_cmd))
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_file_is_valid
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
#ifdef APP_PRE_UPG_CHK
BOOL _nav_updater_cfg_is_file_valid(
    CHAR*       ps_src_path,
    CHAR*       ps_md5_path
)
{
    #define MD5_CHKSUM_LEN       ((UINT32) 32)
    #define TMP_MD5_FILE_PATH    "/3rd/tmp.md5"

    INT32       i4_ret;
    HANDLE_T    h_handle = NULL_HANDLE;
    CHAR        s_md5chksum_1[MD5_CHKSUM_LEN];
    CHAR        s_md5chksum_2[MD5_CHKSUM_LEN];
    UINT32      ui4_read = 0;

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       ps_md5_path,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_handle);

    if (FMR_OK != i4_ret)
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"Open file handle for %s fail, err = %d\n", ps_src_path, i4_ret));

        return FALSE;
    }

    i4_ret = c_fm_read(h_handle, (VOID*)&(s_md5chksum_1[0]), MD5_CHKSUM_LEN, &ui4_read);
    if ((MD5_CHKSUM_LEN != ui4_read) || (FMR_OK != i4_ret))
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"Read file %s fail, err = %d\n", ps_src_path, i4_ret));

        c_fm_close(h_handle);
        return FALSE;
    }

    c_fm_close(h_handle);
    h_handle = NULL_HANDLE;

    i4_ret = _nav_updater_gen_md5_chksum(ps_src_path,
                                         TMP_MD5_FILE_PATH);

    if (NAVR_OK != i4_ret)
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"Call _nav_updater_gen_md5_chksum() for %s error!!!\n",
                                        TMP_MD5_FILE_PATH));
        return FALSE;
    }

    i4_ret = c_fm_open(FM_ROOT_HANDLE,
                       TMP_MD5_FILE_PATH,
                       FM_READ_ONLY,
                       0777,
                       FALSE,
                       &h_handle);

    if (FMR_OK != i4_ret)
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"Open file handle for %s fail, err = %d\n", TMP_MD5_FILE_PATH, i4_ret));

        c_fm_delete_file(FM_ROOT_HANDLE, TMP_MD5_FILE_PATH);
        return FALSE;
    }

    ui4_read = 0;
    i4_ret = c_fm_read(h_handle, (VOID*)&(s_md5chksum_2[0]), MD5_CHKSUM_LEN, &ui4_read);
    if ((MD5_CHKSUM_LEN != ui4_read) || (FMR_OK != i4_ret))
    {
        DBG_ERROR((NAV_UPDATER_PREFIX"Read file %s fail, err = %d\n", TMP_MD5_FILE_PATH, i4_ret));

        c_fm_delete_file(FM_ROOT_HANDLE, TMP_MD5_FILE_PATH);
        c_fm_close(h_handle);
        return FALSE;
    }

    c_fm_delete_file(FM_ROOT_HANDLE, TMP_MD5_FILE_PATH);
    c_fm_close(h_handle);
    h_handle = NULL_HANDLE;

    /* do compare */
    if (0 == c_strncmp(s_md5chksum_1, s_md5chksum_2, MD5_CHKSUM_LEN))
    {
        return TRUE;
    }

    return FALSE;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _nav_updater_is_new_ver
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
#ifdef APP_PRE_UPG_CHK
BOOL _nav_updater_cfg_is_new_ver(
    CHAR*    ps_upg_ver,
    CHAR*    ps_crnt_ver
)
{
    CHAR     s_my_ver[UPDATER_MAX_BUFF_LEN];
    CHAR     s_dl_ver[UPDATER_MAX_BUFF_LEN];
    CHAR*    ps_token;
    CHAR*    ps_tmp;
    INT64    i8_version;
    BOOL     b_is_new;

    struct version_s
    {
        INT64                i8_version;
        struct version_s*    pt_next;
    };

    struct version_s*        pt_my_ver = NULL;
    struct version_s*        pt_dl_ver = NULL;
    struct version_s*        pt_my_tmp;
    struct version_s*        pt_new_tmp;

    c_strncpy(s_my_ver, ps_crnt_ver, UPDATER_MAX_BUFF_LEN);
    c_strncpy(s_dl_ver, ps_upg_ver, UPDATER_MAX_BUFF_LEN);

    /* get current version */
    ps_tmp = s_my_ver;
    ps_token = c_strtok(ps_tmp, UPDATER_TOKENS, &ps_tmp, NULL);

    while (NULL != ps_token)
    {
        struct version_s*    pt_new;
        i8_version = c_strtoll(ps_token, NULL, 10);
        pt_new = (struct version_s*)c_mem_alloc(sizeof(struct version_s));

        if (NULL == pt_new)
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"Allocate memory fail!\n"));
            break;
        }

        pt_new->i8_version = i8_version;
        pt_new->pt_next = NULL;
        if (pt_my_ver)
        {
            struct version_s*    pt_last = pt_my_ver;
            while (pt_last)
            {
                if (pt_last->pt_next == NULL)
                {
                    break;
                }
                pt_last = pt_last->pt_next;
            }
            pt_last->pt_next = pt_new;
        }
        else
        {
            pt_my_ver = pt_new;
        }
        ps_token = c_strtok(ps_tmp, UPDATER_TOKENS, &ps_tmp, NULL);
    }

    /* get upg version */
    ps_tmp = s_dl_ver;
    ps_token = c_strtok(ps_tmp, UPDATER_TOKENS, &ps_tmp, NULL);
    while (NULL != ps_token)
    {
        struct version_s*    pt_new;
        i8_version =  c_strtoll(ps_token, NULL, 10);
        pt_new = (struct version_s*)c_mem_alloc(sizeof(struct version_s));
        if (NULL == pt_new)
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"Allocate memory fail!\n"));
            break;
        }

        pt_new->i8_version = i8_version;
        pt_new->pt_next = NULL;
        if (pt_dl_ver)
        {
            struct version_s*    pt_last = pt_dl_ver;

            while (pt_last)
            {
                if (pt_last->pt_next == NULL)
                {
                    break;
                }
                pt_last = pt_last->pt_next;
            }
            pt_last->pt_next = pt_new;
        }
        else
        {
            pt_dl_ver = pt_new;
        }
        ps_token = c_strtok(ps_tmp, UPDATER_TOKENS, &ps_tmp, NULL);
    }

    /* do version compare */
    pt_my_tmp = pt_my_ver;
    pt_new_tmp = pt_dl_ver;
    b_is_new = FALSE;

    while (pt_my_tmp && pt_new_tmp)
    {
        if (pt_new_tmp->i8_version > pt_my_tmp->i8_version)
        {
            b_is_new = TRUE;
            break;
        }

        DBG_INFO((NAV_UPDATER_PREFIX"my %d, download %d, is new? %s\n",
                    (int)pt_my_tmp->i8_version,
                    (int)pt_new_tmp->i8_version,
                    (TRUE == b_is_new) ? "Yes" : "No"));

        pt_my_tmp = pt_my_tmp->pt_next;
        pt_new_tmp = pt_new_tmp->pt_next;
    }

    if (FALSE == b_is_new && pt_new_tmp)
    {
        /* ex. 1.01.1 (download) > 1.0 (my current) */
        b_is_new = TRUE;
    }

    /* free allocated memory */
    while (pt_my_ver)
    {
        pt_my_tmp = pt_my_ver->pt_next;
        c_mem_free(pt_my_ver);
        pt_my_ver = pt_my_tmp;
    }
    while (pt_dl_ver)
    {
        pt_my_tmp = pt_dl_ver->pt_next;
        c_mem_free(pt_dl_ver);
        pt_dl_ver = pt_my_tmp;
    }

    return b_is_new;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_integrity_chk
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _nav_updater_cfg_integrity_chk(
    UPDATER_CTRL_T*                pt_this
)
{
    INT32                       i4_ret = NAVR_FAIL;
    CHAR                        s_path[128] = {0};
    UINT32                      ui4_size = 128;

    do
    {
        if (NULL == pt_this->pt_curr_dlivry_hdlr)
        {
            return NAVR_FAIL;
        }

        /* get the full path, ex. /mnt/usb/Mass-000/upgrade.pkg */
        i4_ret = pt_this->pt_curr_dlivry_hdlr->pf_get_path(
                    s_path,
                    (SIZE_T)ui4_size);

        if(NAVR_OK > i4_ret)
        {
            return i4_ret;
        }

        /* do integrity check */
        i4_ret = c_dlm_integrity_check(
                    (i4_ret == NAVR_NO_ACTION) ? NULL : s_path,
                    pt_this->pt_curr_dlivry_hdlr->pt_io);

        if(DLM_OK == i4_ret)
        {
            pt_this->ui1_int_chk = UPDATER_INT_CHK_OK;
        }
        else
        {
            switch(i4_ret)
            {
                case DLM_ID_NOT_MATCH:
                    pt_this->ui1_int_chk = UPDATER_INT_CHK_MODEL_FAIL;
                    break;
                case DLM_MODEL_NAME_NOT_MATCH:
                    pt_this->ui1_int_chk = UPDATER_INT_CHK_MODEL_FAIL;
                    break;
                case DLM_VERSION_NOT_MATCH:
                    pt_this->ui1_int_chk = UPDATER_INT_CHK_VERSION_FAIL;
                    break;
                case DLM_HDR_MAGIC_NOT_MATCH:
                    pt_this->ui1_int_chk = UPDATER_INT_CHK_CRC_FAIL;
                    break;
                case DLM_DIGEST_NOT_MATCH:
                    pt_this->ui1_int_chk = UPDATER_INT_CHK_CRC_FAIL;
                    break;
                default:
                    pt_this->ui1_int_chk = UPDATER_INT_CHK_CRC_FAIL;
                    break;
            }

            DBG_INFO((NAV_UPDATER_PREFIX"Integrity check failed. [%d]\n", i4_ret));
        }

    }while(0);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_parse_fw_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_cfg_parse_fw_info(
    UPDATER_CTRL_T*      pt_this
)
{
    INT32                i4_ret;
    CHAR                 s_path[128] = {0};
    UINT32               ui4_size = 128;

    if (NULL == pt_this->pt_curr_dlivry_hdlr)
    {
        return NAVR_FAIL;
    }

    /* get the full path, ex. /mnt/usb/Mass-000/upgrade.pkg */
    i4_ret = pt_this->pt_curr_dlivry_hdlr->pf_get_path(s_path, (SIZE_T)ui4_size);

    if(NAVR_OK > i4_ret)
    {
        return NAVR_FAIL;
    }

    i4_ret = a_fw_updater_download_xml((i4_ret == NAVR_NO_ACTION) ? NULL : s_path,
                                        pt_this->pt_curr_dlivry_hdlr->pt_io,
                                        pt_this->pt_curr_dlivry_hdlr->b_division);

    if (UPDATERR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    /* get fw_info from XML */
    i4_ret = _nav_updater_cfg_parse_xml_to_fw_info(UPDATER_XML_PATH "/" UPDATER_UPG_XML_NAME,
                                                   &(pt_this->t_upg_fw_info),
                                                   &(pt_this->pt_download_xml));
    if (NAVR_OK != i4_ret)
    {
        return NAVR_FAIL;
    }

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_parse_fw_info
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_cfg_pre_upg_chk(
    UPDATER_CTRL_T*      pt_this
)
{
#ifdef APP_PRE_UPG_CHK
    INT32                i4_ret;
    UINT32               ui4_i, ui4_j;

    /* check current fw information xml file is valid or not */
    if (TRUE == _nav_updater_cfg_is_file_valid(UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                                               UPDATER_XML_PATH "/" CRNT_VERSION_XML_MD5_NAME))
    {
        /* valid => backup it first */
        c_fm_copy_file(FM_ROOT_HANDLE,
                       UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                       FM_ROOT_HANDLE,
                       UPDATER_XML_PATH "/" CRNT_VERSION_BAK_XML_NAME,
                       NULL);
    }
    else
    {
        /* invalid => use backup file */
        c_fm_copy_file(FM_ROOT_HANDLE,
                       UPDATER_XML_PATH "/" CRNT_VERSION_BAK_XML_NAME,
                       FM_ROOT_HANDLE,
                       UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                       NULL);

        /* generate checksum */
        i4_ret = _nav_updater_gen_md5_chksum(UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                                             UPDATER_XML_PATH "/" CRNT_VERSION_XML_MD5_NAME);

        if (NAVR_OK != i4_ret)
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"Call _nav_updater_gen_md5_chksum() for %s error!!!\n",
                                            UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME));

            /* ignore this error */
            return NAVR_OK;
        }
    }

    /* get current fw information first */
    i4_ret = _nav_updater_cfg_parse_xml_to_fw_info(UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                                                   &(pt_this->t_crnt_fw_info),
                                                   &(pt_this->pt_version_xml));
    if (NAVR_OK != i4_ret)
    {
        /* ignore this error, maybe current FW information does not exist! */
        return NAVR_OK;
    }

    for (ui4_i = 0 ; ui4_i < pt_this->t_upg_fw_info.ui4_item_num ; ui4_i++)
    {
        for (ui4_j = 0 ; ui4_j < pt_this->t_crnt_fw_info.ui4_item_num ; ui4_j++)
        {
            /* if tag name matches */
            if (0 == c_strncmp(pt_this->t_upg_fw_info.pt_item[ui4_i].s_tag,
                               pt_this->t_crnt_fw_info.pt_item[ui4_j].s_tag,
                               UPDATER_TAG_NAME_LEN))
            {
                if (FALSE == _nav_updater_cfg_is_new_ver(
                                    pt_this->t_upg_fw_info.pt_item[ui4_i].s_ver,
                                    pt_this->t_crnt_fw_info.pt_item[ui4_j].s_ver))
                {
                    /* if upgrade version is older than current one, do not select this item */
                    pt_this->t_upg_fw_info.pt_item[ui4_i].ui4_flag &= ~UPDATER_ITEM_FLAG_SELECTED;
                }
                DBG_INFO((NAV_UPDATER_PREFIX"Item %s is selected? %s\n",
                            pt_this->t_upg_fw_info.pt_item[ui4_i].s_name,
                           (pt_this->t_upg_fw_info.pt_item[ui4_i].ui4_flag & UPDATER_ITEM_FLAG_SELECTED) ? "Yes" : "No"));
                break;
            }
        }
    }
#endif

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _nav_updater_cfg_save_upg_result
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

static INT32 _nav_updater_cfg_save_upg_result(
    UPDATER_CTRL_T*      pt_this
)
{
#ifdef APP_PRE_UPG_CHK
    UINT8                ui1_i, ui1_j;
    XML_NODE_T*          pt_upg_node_sw = NULL;
    XML_Element*         pt_upg_ele_sw = NULL;
    XML_Element*         pt_upg_ele_sw_tag = NULL;
    XML_Element*         pt_upg_ele_sw_ver = NULL;

    XML_NODE_T*          pt_crnt_node_sw = NULL;
    XML_Element*         pt_crnt_ele_sw = NULL;
    XML_Element*         pt_crnt_ele_sw_tag = NULL;
    XML_Element*         pt_crnt_ele_sw_ver = NULL;

    CHAR*                ps_buff = NULL;
    HANDLE_T             h_handle = NULL_HANDLE;
    INT32                i4_ret;
    UINT32               ui4_written = 0;

    BOOL                 b_update_crnt = FALSE;

    pt_upg_node_sw = c_xml_get_elements_by_tag_name(pt_this->pt_download_xml, "SW");
    if (NULL == pt_upg_node_sw)
    {
        return NAVR_FAIL;
    }

    for (ui1_i = 0 ; ui1_i < pt_this->t_upg_fw_info.ui4_item_num ; ui1_i++)
    {
        if ((pt_this->t_upg_fw_info.pt_item[ui1_i].ui4_flag & UPDATER_ITEM_FLAG_SELECTED)
             && (UPDATER_ITEM_COND_UPDATED == pt_this->t_upg_fw_info.pt_item[ui1_i].e_cond)
             && (UPDATER_METHOD_PART == pt_this->t_upg_fw_info.pt_item[ui1_i].e_method))
        {
            pt_upg_ele_sw = XML_NodeItem(pt_upg_node_sw, ui1_i);
            pt_upg_ele_sw_tag = c_xml_get_element(pt_upg_ele_sw, "TAG");

            for (ui1_j = 0 ; ui1_j < pt_this->t_crnt_fw_info.ui4_item_num ; ui1_j++)
            {
                pt_crnt_node_sw = c_xml_get_elements_by_tag_name(pt_this->pt_version_xml, "SW");
                if (NULL == pt_crnt_node_sw)
                {
                    return NAVR_FAIL;
                }

                pt_crnt_ele_sw = XML_NodeItem(pt_crnt_node_sw, ui1_j);
                pt_crnt_ele_sw_tag = c_xml_get_element(pt_crnt_ele_sw, "TAG");

                /* if tag name matches */
                if (0 == c_strncmp(UPDATER_XML_VALUE(pt_upg_ele_sw_tag),
                                   UPDATER_XML_VALUE(pt_crnt_ele_sw_tag),
                                   UPDATER_TAG_NAME_LEN))
                {
                    /* modify current version of the corresponding item */
                    pt_crnt_ele_sw_ver = c_xml_get_element(pt_crnt_ele_sw, "VER");

                    if (NULL != pt_crnt_ele_sw_ver)
                    {
                        c_xml_delete_element(pt_crnt_ele_sw_ver);
                        c_xml_free(pt_crnt_ele_sw_ver);
                    }

                    /* add */
                    pt_upg_ele_sw_ver = c_xml_get_element(pt_upg_ele_sw, "VER");
                    c_xml_add_element(pt_crnt_ele_sw, "VER", UPDATER_XML_VALUE(pt_upg_ele_sw_ver));

                    b_update_crnt = TRUE;
                    break;
                }
            }
        }
    }

    if (TRUE == b_update_crnt)
    {
        ps_buff = c_xml_print_document(pt_this->pt_version_xml);
        if (NULL == ps_buff)
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"Call c_xml_print_document error, i4_ret = %d!!!\n"));

            return NAVR_FAIL;
        }

        c_fm_delete_file(FM_ROOT_HANDLE, UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME);

        i4_ret = c_fm_open(FM_ROOT_HANDLE,
                           UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                           (FM_READ_WRITE | FM_OPEN_CREATE),
                           0777,
                           FALSE,
                           &h_handle);

        if (FMR_OK != i4_ret)
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"Open file %s error, i4_ret = %d!!!\n",
                                            UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                                            i4_ret));
            return NAVR_FAIL;
        }

        i4_ret = c_fm_write(h_handle, (VOID*)ps_buff, c_strlen(ps_buff), &ui4_written);

        if ((FMR_OK != i4_ret) && (ui4_written != c_strlen(ps_buff)))
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"Write file %s error, i4_ret = %d!!!\n",
                                            UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                                            i4_ret));
            c_fm_close(h_handle);
            return NAVR_FAIL;
        }
        c_fm_close(h_handle);

        /* generate checksum */
        i4_ret = _nav_updater_gen_md5_chksum(UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME,
                                             UPDATER_XML_PATH "/" CRNT_VERSION_XML_MD5_NAME);

        if (NAVR_OK != i4_ret)
        {
            DBG_ERROR((NAV_UPDATER_PREFIX"Call _nav_updater_gen_md5_chksum() for %s error!!!\n",
                                            UPDATER_XML_PATH "/" CRNT_VERSION_XML_NAME));

            /* ignore this error */
            return NAVR_OK;
        }
    }

    if (NULL != pt_crnt_node_sw)
    {
        c_xml_free_node(pt_crnt_node_sw);
    }

    if (NULL != pt_upg_node_sw)
    {
        c_xml_free_node(pt_upg_node_sw);
    }
#endif

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
                    export methods implementations
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name: nav_updater_cfg_init
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 ----------------------------------------------------------------------------*/

VOID nav_updater_cfg_init(
    VOID
)
{
    c_memset(&t_updater_cfg, 0, sizeof(UPDATER_CONFIG_T));

    t_updater_cfg.pf_integrity_chk = _nav_updater_cfg_integrity_chk;
    t_updater_cfg.pf_parse_fw_info = _nav_updater_cfg_parse_fw_info;
    t_updater_cfg.pf_pre_upg_chk   = _nav_updater_cfg_pre_upg_chk;
    t_updater_cfg.pf_save_upg_result = _nav_updater_cfg_save_upg_result;

    nav_updater_init(&t_updater_cfg);
}

