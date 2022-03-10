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
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "c_dbg.h"
#include "c_os.h"
#include "nav/nav_common.h"
#include "nav/updater/nav_updater.h"
#include "iniparser.h"
#include "MtkV4L2.h"
#include "MtkV4L2_Type.h"

#define SSTAR_VENDOR_ID "1D6B"
#define SSTAR_PRODUCT_ID "0102"
#define SYSTEM_CMD_BIND_DEV_BUS_USB "mount -o bind /cast_root/dev/bus/usb /dev/bus/usb"
#define CHECK_DEV_BUS_MOUNTED "cat /proc/mounts | grep /dev/bus/usb"
#define ISP_FW_AUTO_UPDATE_TXT_PATH "/application/camera_fw/auto_update.txt"
#define ISP_FW_VERSION_INI_PATH "/application/camera_fw/version.ini"

INT32 nav_updater_isp_get_current_version(CHAR* ps_buff, UINT32 ui4_size)
{
    AVAILABLE_DEVICE_INFO_T availableDeviceInfo = {0};
    if (E_MTK_V4L2_RET_OK != mtk_v4l2_get_available_device(&availableDeviceInfo))
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Failed to find ISP, abort ISP firmware upgrade\n"));
        return NAVR_FAIL;
    }

    DEVICE_INFO_T* pSStarDevice = NULL;
    for (int i = 0; i < availableDeviceInfo.size; ++i)
    {
        pSStarDevice = &availableDeviceInfo.deviceList[i];
        if (0 == c_strncasecmp(pSStarDevice->vendorid, SSTAR_VENDOR_ID, sizeof(SSTAR_VENDOR_ID)) &&
            0 == c_strncasecmp(pSStarDevice->productid, SSTAR_PRODUCT_ID, sizeof(SSTAR_PRODUCT_ID)))
        {
            break;
        }
        pSStarDevice = NULL;
    }

    if (NULL == pSStarDevice)
    {
        return NAVR_NOT_EXIST;
    }

    c_strncpy(ps_buff, pSStarDevice->firmwareVersion, ui4_size);
    return NAVR_OK;
}

INT32 nav_updater_isp_get_version(CHAR* ps_buff, UINT32 ui4_size)
{
    dictionary* pIni = iniparser_load(ISP_FW_VERSION_INI_PATH);
    if (NULL == pIni)
    {
        return NAVR_FAIL;
    }

    UINT32 ui4_major_num = iniparser_getunsignedint(pIni, "Version:MajorNum", 0);
    UINT32 ui4_minor_num = iniparser_getunsignedint(pIni, "Version:MinorNum", 0);
    UINT32 ui4_release_num = iniparser_getunsignedint(pIni, "Version:ReleaseNum", 0);
    UINT32 ui4_build_num = iniparser_getunsignedint(pIni, "Version:BuildNum", 0);
    iniparser_freedict(pIni);

    c_snprintf(ps_buff, ui4_size, "%2u.%2u.%2u.%2u", ui4_major_num, ui4_minor_num, ui4_release_num, ui4_build_num);

    return NAVR_OK;
}

INT32 nav_updater_isp_upgrade_firmware()
{
    AVAILABLE_DEVICE_INFO_T availableDeviceInfo = {0};
    if (E_MTK_V4L2_RET_OK != mtk_v4l2_get_available_device(&availableDeviceInfo))
    {
        NAV_UPGRADE_LOG_PRINT((NAV_UPDATER_PREFIX"Failed to find ISP, abort ISP firmware upgrade\n"));
        return NAVR_FAIL;
    }

    DEVICE_INFO_T* pSStarDevice = NULL;
    for (int i = 0; i < availableDeviceInfo.size; ++i)
    {
        pSStarDevice = &availableDeviceInfo.deviceList[i];
        if (0 == c_strncasecmp(pSStarDevice->vendorid, SSTAR_VENDOR_ID, sizeof(SSTAR_VENDOR_ID)) &&
            0 == c_strncasecmp(pSStarDevice->productid, SSTAR_PRODUCT_ID, sizeof(SSTAR_PRODUCT_ID)))
        {
            break;
        }
        pSStarDevice = NULL;
    }

    if (NULL == pSStarDevice)
    {
        return NAVR_NOT_EXIST;
    }

    nav_updater_show_dialog(UPDATER_SHOW_DLG_TYPE_ISP_UPGRADE, NULL);

    int ret = system(CHECK_DEV_BUS_MOUNTED);
    if (ret != 0)
    {
        system(SYSTEM_CMD_BIND_DEV_BUS_USB);
    }
    MTK_V4L2_RESULT_E eRet = mtk_v4l2_upgrade_isp_firmware(pSStarDevice->deviceid, ISP_FW_AUTO_UPDATE_TXT_PATH);
    nav_updater_hide_dialog();
    return eRet == E_MTK_V4L2_RET_OK? NAVR_OK : NAVR_FAIL;
}
