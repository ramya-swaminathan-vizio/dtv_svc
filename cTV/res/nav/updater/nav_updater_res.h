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
 *      This file contains the images used by the Wizard application.
 *---------------------------------------------------------------------------*/

#ifndef _NAV_UPDATER_RES_H_
#define _NAV_UPDATER_RES_H_

#if 1//def APP_UPG_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_common.h"
#include "u_wgl.h"
#include "u_wgl_sets.h"
#include "c_wgl_image.h"
#include "app_util/a_common.h"
#include "app_util/a_updater.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define NAV_OSD_ALPHA       255

/* The main frame*/
#define NAV_FRAME_DL_X              NAV_WIDTH(270)
#define NAV_FRAME_DL_Y              NAV_HEIGHT(200)
#define NAV_FRAME_DL_W              NAV_WIDTH(420)
#define NAV_FRAME_DL_H              NAV_HEIGHT(140)

#define NAV_FRAME_UPG_X             NAV_WIDTH(0)
#define NAV_FRAME_UPG_Y             NAV_HEIGHT(0)
#define NAV_FRAME_UPG_W             NAV_WIDTH(310)
#define NAV_FRAME_UPG_H             (NAV_HEIGHT(540) - NAV_HELP_TIP_FRAME_H)

#define NAV_HELP_TIP_FRAME_X        (NAV_FRAME_UPG_X)
#define NAV_HELP_TIP_FRAME_Y        (NAV_FRAME_UPG_Y + NAV_FRAME_UPG_H)
#define NAV_HELP_TIP_FRAME_W        (NAV_FRAME_UPG_W)
#define NAV_HELP_TIP_FRAME_H        NAV_HEIGHT(129)

#define NAV_HOME_BAR_X              NAV_WIDTH(3)
#define NAV_HOME_BAR_Y              NAV_HEIGHT(4)
#define NAV_HOME_BAR_W              (NAV_FRAME_UPG_W - 2*NAV_HOME_BAR_X)
#define NAV_HOME_BAR_H              NAV_HEIGHT(34)

#define NAV_TITLE_FRM_X             (NAV_HOME_BAR_X)
#define NAV_TITLE_FRM_Y             NAV_HEIGHT(50)
#define NAV_TITLE_FRM_W             (NAV_HOME_BAR_W)
#define NAV_TITLE_FRM_H             NAV_HEIGHT(25)


#define NAV_TITLE_TXT_X             NAV_WIDTH(63)
#define NAV_TITLE_TXT_Y             NAV_HEIGHT(0)
#define NAV_TITLE_TXT_W             (NAV_HOME_BAR_W - NAV_WIDTH(47))
#define NAV_TITLE_TXT_H             (NAV_HOME_BAR_H - NAV_HEIGHT(10))
#define NAV_TITLE_TXT_ALIGN         (WGL_AS_LEFT_CENTER)
#define NAV_TITLE_TXT_FONT_SIZE     (FE_FNT_SIZE_MEDIUM)
#define NAV_TITLE_TXT_STYLE         (WGL_STL_TEXT_MAX_128)

#define NAV_UPG_WARNING_TXT_X       (NAV_FRAME_UPG_X)
#define NAV_UPG_WARNING_TXT_Y       NAV_HEIGHT(80)
#define NAV_UPG_WARNING_TXT_W       (NAV_FRAME_UPG_W)
#define NAV_UPG_WARNING_TXT_H       NAV_HEIGHT(120)
#define NAV_UPG_WARNING_TXT_ALIGN   (WGL_AS_LEFT_TOP)

#define NAV_DL_WARNING_TXT_X        NAV_WIDTH(0)
#define NAV_DL_WARNING_TXT_Y        (NAV_FRAME_DL_H/2)
#define NAV_DL_WARNING_TXT_W        (NAV_FRAME_DL_W)
#define NAV_DL_WARNING_TXT_H        (NAV_FRAME_DL_H/2)

#define NAV_WARNING_TXT_FONT_SIZE   (FE_FNT_SIZE_MEDIUM)
#define NAV_WARNING_TXT_STYLE       (WGL_STL_TEXT_MAX_512 | WGL_STL_TEXT_MULTILINE | WGL_STL_TEXT_MAX_DIS_5_LINE)

#define NAV_CUR_VER_TXT_X           (NAV_FRAME_UPG_X)
#define NAV_CUR_VER_TXT_Y           NAV_HEIGHT(205)
#define NAV_CUR_VER_TXT_W           (NAV_FRAME_UPG_W)
#define NAV_CUR_VER_TXT_H           NAV_HEIGHT(24)

#define NAV_NEW_VER_TXT_X           (NAV_FRAME_UPG_X)
#define NAV_NEW_VER_TXT_Y           NAV_HEIGHT(280)
#define NAV_NEW_VER_TXT_W           (NAV_FRAME_UPG_W)
#define NAV_NEW_VER_TXT_H           NAV_HEIGHT(24)

#define NAV_VER_TITLE_TXT_ALIGN     (WGL_AS_LEFT_CENTER)
#define NAV_VER_TITLE_TXT_FONT_SIZE (FE_FNT_SIZE_MEDIUM)
#define NAV_VER_TITLE_TXT_STYLE     (WGL_STL_TEXT_MAX_128)

#define NAV_VER_TXT_ALIGN           (WGL_AS_LEFT_CENTER)
#define NAV_VER_TXT_FONT_SIZE       (FE_FNT_SIZE_MEDIUM)
#define NAV_VER_TXT_STYLE           (WGL_STL_TEXT_MAX_128 | WGL_STL_TEXT_MULTILINE)

#define NAV_UPG_PKG_DESC_TXT_X      (NAV_FRAME_UPG_X)
#define NAV_UPG_PKG_DESC_TXT_Y      NAV_HEIGHT(320)
#define NAV_UPG_PKG_DESC_TXT_W      (NAV_FRAME_UPG_W)
#define NAV_UPG_PKG_DESC_TXT_H      NAV_HEIGHT(24)

#define NAV_DL_TXT_ALIGN            (WGL_AS_CENTER_TOP)

#define NAV_DESC_TXT_ALIGN          (WGL_AS_LEFT_CENTER)
#define NAV_DESC_TXT_FONT_SIZE      (FE_FNT_SIZE_MEDIUM)
#define NAV_DESC_TXT_STYLE          (WGL_STL_TEXT_MAX_128)

#define  NAV_UPG_PROGRESS_BAR_X     NAV_WIDTH(8)
#define  NAV_UPG_PROGRESS_BAR_Y     (NAV_NEW_VER_TXT_Y + (NAV_NEW_VER_TXT_H * 3) + NAV_HEIGHT(23))
#define  NAV_UPG_PROGRESS_BAR_W     (NAV_FRAME_UPG_W - NAV_WIDTH(16))
#define  NAV_UPG_PROGRESS_BAR_H     NAV_HEIGHT(16)


typedef enum
{
    UPDATER_ITEM_COND_NONE = 0,
    UPDATER_ITEM_COND_RETRIEVING,
    UPDATER_ITEM_COND_RETRIEVE_FAIL,
    UPDATER_ITEM_COND_UPDATING,
    UPDATER_ITEM_COND_UPDATED,
    UPDATER_ITEM_COND_UPDATE_FAIL
}   UPDATER_ITEM_COND_T;

#define UPDATER_ITEM_FLAG_SELECTED                          MAKE_BIT_MASK_32(0)
#define UPDATER_ITEM_FLAG_DUAL_BANK                         MAKE_BIT_MASK_32(1)
#define UPDATER_SIGNATURE_TAG_NAME                                      "sign"
#define UPDATER_KERNEL_TAG_NAME                                         "kern"
#define UPDATER_ROOTFS_TAG_NAME                                         "crtf"
#define UPDATER_3RD_TAG_NAME                                            "3rdp"
#define UPDATER_SYSTEM_TAG_NAME                                         "csys"
#define UPDATER_CHROME_TAG_NAME                                         "cchr"
#define UPDATER_LINUX_ROOTFS_TAG_NAME                                   "rtfs"

/*< The following tag name macro is added for 1901 branch. */
#define UPDATER_MBOOT_TAG_NAME                                          "mbot"
#define UPDATER_MPOOL_TAG_NAME                                          "mpol"
#define UPDATER_OPTEE_TAG_NAME                                          "opte"
#define UPDATER_DTB_TAG_NAME                                            "dtbp"
#define UPDATER_FRC_TAG_NAME                                            "frcp"
#define UPDATER_ARMFW_TAG_NAME                                          "armf"
#define UPDATER_EEPROM_A_TAG_NAME                                       "eepr"
#define UPDATER_ACFG_TAG_NAME                                           "acfg"
#define UPDATER_CHANNEL_A_TAG_NAME                                      "chna"
#define UPDATER_CHANNEL_B_TAG_NAME                                      "chnb"
#define UPDATER_SCHEDPVR_TAG_NAME                                       "spvr"
#define UPDATER_CIPLUS_TAG_NAME                                         "cipl"
#define UPDATER_DVBSDB_TAG_NAME                                         "dvbs"
#define UPDATER_VBMETA_TAG_NAME                                         "vbme"
#define UPDATER_CERTIFICATE_TAG_NAME                                    "cert"
#define UPDATER_LIB_DYNAMIC_TAG_NAME                                    "libd"
#define UPDATER_MWLIB_TAG_NAME                                          "mwlb"
#define UPDATER_APPLICATION_TAG_NAME                                    "appl"
#define UPDATER_FACTORY_TAG_NAME                                        "fact"
#define UPDATER_BASIC_APFILE_TAG_NAME                                   "baca"
#define UPDATER_TVCONFIG_TAG_NAME                                       "tvcf"
#define UPDATER_CUSTOMER_TAG_NAME                                       "cust"
#define UPDATER_DATA_TAG_NAME                                           "data"
#define UPDATER_CACHE_TAG_NAME                                          "cach"

#ifdef APP_NET_UPG_SUPPORT
#define UPDATER_NET_UPG_CA_NAME                                   "netupg.crt"
#if 0
#define UPDATER_NET_UPG_FW_URL "https://pc0701015895.mediatek.inc/upgrade.pkg"
#else
#define UPDATER_NET_UPG_URL_DB                                     "netupg.db"
#endif
#define UPDATER_NET_UPG_BUFF_SZ                         ((UINT32)(512 * 1024))
#endif

typedef struct _UPDATER_ITEM_T
{
    /* item information from XML */
    CHAR                   s_tag[UPDATER_TAG_NAME_LEN];
    CHAR                   s_dev_path[UPDATER_DEV_PATH_LEN];
    UPDATER_METHOD_T       e_method;
    CHAR                   s_name[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_file_name[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_ver[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_checksum[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_storageType[UPDATER_MAX_BUFF_LEN];
    UINT32                 ui4_size;
    UINT32                 ui4_offset;
#ifdef APP_ONE_IMG_FOR_MULTI_NAND
    BOOL                   b_nand_match;
#endif

    /* variables used during upgrade */
    UPDATER_ITEM_COND_T    e_cond;
    UINT32                 ui4_flag;
    UINT8                  ui1_part_id;     /* For partition base only!! */
    BOOL                   b_3rd_dual_bank; /* For 3RD dual partition only!! */
} UPDATER_ITEM_T;

typedef struct _UPDATER_FW_INFO_T
{
    CHAR                   s_manufacturer[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_model[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_ic_ver[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_hw_ver[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_build_name[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_build_date[UPDATER_MAX_BUFF_LEN];
    CHAR                   s_serial_num[UPDATER_MAX_BUFF_LEN];

    UINT32                 ui4_item_num;
    UPDATER_ITEM_T*        pt_item;
} UPDATER_FW_INFO_T;

typedef struct
{
    WGL_HIMG_TPL_T  h_g_img_back_bar_bk;
    WGL_HIMG_TPL_T  h_g_img_back_bar_bk_hlt;
    WGL_HIMG_TPL_T  h_g_img_bk_plain;
    WGL_HIMG_TPL_T  h_g_img_home_bar;
    WGL_HIMG_TPL_T  h_g_img_home_bar_hlt;
    WGL_HIMG_TPL_T  h_g_img_banner_bk;

    WGL_HIMG_TPL_T  h_g_img_progress_bar_bk;
    WGL_HIMG_TPL_T  h_g_img_progress_bar_level;
    WGL_HIMG_TPL_T  h_g_nav_updater_progress_bar_bk_rightshadow;
    WGL_HIMG_TPL_T  h_g_nav_updater_progress_bar_bk_leftshadow;
    WGL_HIMG_TPL_T  h_g_nav_updater_bk_plain_exit;
    WGL_HIMG_TPL_T  h_g_nav_updater_warning_toast;
    WGL_HIMG_TPL_T  h_g_nav_updater_track_fill_toast;
    WGL_HIMG_TPL_T  h_g_nav_updater_track_cap_left_toast;
    WGL_HIMG_TPL_T  h_g_nav_updater_track_cap_right_toast;

    GL_COLOR_T      t_clr_txt;
} NAV_UPDATER_RES_T;

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

extern NAV_UPDATER_RES_T    t_g_nav_updater_res;

/*-----------------------------------------------------------------------------
                    functions declarations
 ----------------------------------------------------------------------------*/

extern INT32 nav_updater_res_init (
    VOID
);

extern INT32 nav_updater_res_deinit (
    VOID
);

#endif /* APP_UPG_SUPPORT */
#endif /* _FW_UPG_RES_H_ */

