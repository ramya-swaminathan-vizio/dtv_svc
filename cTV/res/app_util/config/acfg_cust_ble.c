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
 * $RCSfile: acfg_custom.c,v $
 * $Revision$
 * $Date$
 * $Author$
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *      This file implements the APP CFG APIs. APP CFG is a utility library which
 * encapsulates the definition of config database and builds a facade for the
 * application developer.
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#ifdef LINUX_TURNKEY_SOLUTION
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#endif

#include "c_common.h"
#include "c_svctx.h"
#include "c_pcl.h"
#include "c_dt.h"
#include "c_iom.h"
#include "c_scc.h"
#include "u_iom.h"
#include "u_irrc_btn_def.h"
#include "u_cecm.h"
#include "u_drv_cust.h"
#include "c_rm.h"
#include "c_fm.h"
#include "u_fm.h"
#include "u_drv_cust.h"

#include "am/a_am.h"
#include "amb/a_amb.h"
#include "app_util/a_tv.h"
#include "app_util/a_cfg.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/app_util/config/a_cfg_custom.h"

#include "res/app_util/config/acfg_cust_ble.h"
#include "app_util/config/_acfg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

static UINT8 		ble_device[BLEGATT_MAC_ADDR_ELEM_SIZE] = {0};

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: acfg_cust_ble_pre_init
 *
 * Description:
 *      Pre initialiation. You can do following thing here:
 *  1. Override the default value
 *  2. Put some config in EEPROM
 *  3. Remove some configs by setting them as b_enable=FALSE
 *  4. Change the value in at_acfg_descr
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_ble_pre_init(VOID)
{
    UINT8                   ui1_i = 0;

    c_memset(ble_device, 0, sizeof(ble_device));
    c_strncpy((CHAR*)&ble_device[2], BLEGATT_MAC_ADDR_DEF, MAC_ADDRESS_LENGTH_LEN);

    for(ui1_i=0; ui1_i < MAX_CACHE_BLE_NUMBER_DEF; ui1_i++)
    {
        if ((IDX_CUSTOM_BLEGATT_MAC_ADDR_0 + ui1_i) < IDX_CUSTOM_BLEGATT_MAC_ADDR_END)
        {
            DECLARE_FIELD((IDX_CUSTOM_BLEGATT_MAC_ADDR_0+ui1_i), APP_CFG_GRPID_CUSTOM_BLEGATT, (APP_CFG_RECID_CUST_BLEGATT_MAC_ADDR_0+ui1_i),
                          CFG_8BIT_T,   BLEGATT_MAC_ADDR_ELEM_SIZE, ble_device, BLEGATT_MAC_ADDR_ELEM_SIZE,
                          NULL,         NULL,        ACFG_ACCESS_PUBLIC);
        }
    }

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: acfg_cust_post_init
 *
 * Description:
 *      Post initialiation. You can do following thing here:
 *  1. Update the middleware component in accordance with config value.
 *  2. Always set a config to a specific value.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
extern INT32 acfg_cust_ble_post_init(VOID)
{
    return APP_CFGR_OK;
}

extern INT32 a_cfg_set_blegatt_cache_dev_by_idx(BLE_CACHE_DEVICE* ui1_value, UINT16 ui2_idx)
{
    INT32 i4_ret;

    /* b_is_IOS + ui_target_ID + c_mac_address */
    UINT8 acfg_ble_device[BLEGATT_MAC_ADDR_ELEM_SIZE] = {0};

    if (NULL == ui1_value || ui2_idx >= MAX_CACHE_BLE_NUMBER)
    {
        DBG_ERROR(("<ACFG> a_cfg_set_blegatt_cache_dev pui1_value is null.\n"));
        return APP_CFGR_INV_ARG;
    }

    acfg_ble_device[0] = ui1_value[ui2_idx].b_is_IOS;
    acfg_ble_device[1] = ui1_value[ui2_idx].ui_target_ID;
    c_memcpy(&acfg_ble_device[2], ui1_value[ui2_idx].c_mac_address, MAC_ADDRESS_LENGTH_LEN);

    i4_ret = acfg_set(IDX_CUSTOM_BLEGATT_MAC_ADDR_0+ui2_idx, acfg_ble_device, sizeof(acfg_ble_device));
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<ACFG> a_cfg_set_blegatt_cache_dev fail, error code: %d\n", i4_ret));
        return i4_ret;
    }

    return APP_CFGR_OK;
}

extern INT32 a_cfg_get_blegatt_cache_dev_by_idx(BLE_CACHE_DEVICE *pui1_value, UINT16 ui2_idx)
{
    INT32    i4_ret;
    SIZE_T   z_size;
    /* b_is_IOS + ui_target_ID + c_mac_address */
    UINT8 acfg_ble_device[BLEGATT_MAC_ADDR_ELEM_SIZE] = {0};

    if (NULL == pui1_value || ui2_idx >= MAX_CACHE_BLE_NUMBER)
    {
        DBG_ERROR(("<ACFG> a_cfg_get_blegatt_cache_dev pui1_value is null.\n"));
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_BLEGATT_MAC_ADDR_0+ui2_idx, acfg_ble_device, &z_size);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("<ACFG> a_cfg_get_blegatt_cache_dev fail, error code: %d\n", i4_ret));
        return i4_ret;
    }

    pui1_value[ui2_idx].b_is_IOS = acfg_ble_device[0];
    pui1_value[ui2_idx].ui_target_ID = acfg_ble_device[1];
    c_memcpy(pui1_value[ui2_idx].c_mac_address, &acfg_ble_device[2], MAC_ADDRESS_LENGTH_LEN);

    DBG_INFO(("<ACFG> a_cfg_get_blegatt_cache_dev mac_address: %s, target_ID: %d\n",
                                                            pui1_value[ui2_idx].c_mac_address,
                                                            pui1_value[ui2_idx].ui_target_ID));
    return APP_CFGR_OK;
}

extern INT32 a_cfg_set_blegatt_cache_dev(BLE_CACHE_DEVICE* ui1_value)
{
    INT32 i4_ret;
    INT32 i = 0;

    if (NULL == ui1_value)
    {
        DBG_ERROR(("<ACFG> a_cfg_set_blegatt_cache_dev pui1_value is null.\n"));
        return APP_CFGR_INV_ARG;
    }

	for(i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
	{
		DBG_INFO(("<ACFG> a_cfg_set_blegatt_cache_dev mac_address: %s, target_ID: %d\n",
                                                                        ui1_value[i].c_mac_address,
                                                                        ui1_value[i].ui_target_ID));
        i4_ret = a_cfg_set_blegatt_cache_dev_by_idx(ui1_value, i);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<ACFG> a_cfg_set_blegatt_cache_dev fail, error code: %d\n", i4_ret));
            return i4_ret;
        }
	}

    return APP_CFGR_OK;
}

extern INT32 a_cfg_get_blegatt_cache_dev(BLE_CACHE_DEVICE *pui1_value)
{
    INT32    i4_ret;
	int 	 i = 0;

    if (NULL == pui1_value)
    {
        DBG_ERROR(("<ACFG> a_cfg_get_blegatt_cache_dev pui1_value is null.\n"));
        return APP_CFGR_INV_ARG;
    }

	for (i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
	{
	    i4_ret = a_cfg_get_blegatt_cache_dev_by_idx(pui1_value, i);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<ACFG> a_cfg_get_blegatt_cache_dev fail, error code: %d\n", i4_ret));
            return i4_ret;
        }
	}

    return APP_CFGR_OK;
}

extern INT32 a_cfg_blegatt_cache_dev_reset(VOID)
{
    INT32 i4_ret;
    INT32 i = 0;

    AP_SYSTEM_CALL("rm -rf /3rd_rw/bluetooth/bleRemoteDb;sync");

	for(i = 0; i < MAX_CACHE_BLE_NUMBER; i++)
	{
        i4_ret = acfg_set_default(IDX_CUSTOM_BLEGATT_MAC_ADDR_0+i);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<ACFG> a_cfg_blegatt_cache_dev_reset fail, error code: %d\n", i4_ret));
        }
	}

    return APP_CFGR_OK;
}

/*------------------------------------------------------------------------------
                    external functions declarations
------------------------------------------------------------------------------*/



