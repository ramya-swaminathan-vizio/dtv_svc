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
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *      This file implements the APP CFG APIs. APP CFG is a utility library which
 * encapsulates the definition of config database and builds a facade for the
 * application developer.
 *---------------------------------------------------------------------------*/
#ifdef APP_MMP_SUPPORT
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "c_common.h"
#include "c_svctx.h"

#include "app_util/a_cfg.h"
#include "mmp/mmp_common.h"
#include "app_util/config/_acfg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
static UINT8    ui1_g_cust_mmp_photo_recur_parsing_def  = 0;
static UINT8    ui1_g_cust_mmp_audio_recur_parsing_def  = 0;
static UINT8    ui1_g_cust_mmp_video_recur_parsing_def  = 0;

static UINT32   ui4_g_cust_mmp_photo_set_info_def       = 0;

static UINT8    ui1_g_cust_mmp_photo_sort               = MMP_SORT_TYPE_PHOTO_NAME;
static UINT8    ui1_g_cust_mmp_audio_sort               = MMP_SORT_TYPE_AUD_ALBUM;
static UINT8    ui1_g_cust_mmp_video_sort               = MMP_SORT_TYPE_VIDEO_INV_DATE;
/*-----------------------------------------------------------------------------
                    private functions declarations
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: acfg_cust_pre_init
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
extern INT32 acfg_cust_mmp_pre_init(VOID)
{
    DECLARE_FIELD(IDX_CUSTOM_MMP_PHOTO_SET_INFO,
                  APP_CFG_GRPID_CUSTOM_MMP_BASE,
                  APP_CFG_RECID_CUSTOM_MMP_PHOTO_SET_INFO,
                  CFG_32BIT_T,
                  1,
                  &ui4_g_cust_mmp_photo_set_info_def,
                  1,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_MMP_PHOTO_RECUR_PARSING,
                  APP_CFG_GRPID_CUSTOM_MMP_BASE,
                  APP_CFG_RECID_CUSTOM_MMP_PHOTO_RECUR_PARSING,
                  CFG_8BIT_T,
                  1,
                  &ui1_g_cust_mmp_photo_recur_parsing_def,
                  1,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_MMP_AUDIO_RECUR_PARSING,
                  APP_CFG_GRPID_CUSTOM_MMP_BASE,
                  APP_CFG_RECID_CUSTOM_MMP_AUDIO_RECUR_PARSING,
                  CFG_8BIT_T,
                  1,
                  &ui1_g_cust_mmp_audio_recur_parsing_def,
                  1,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_MMP_VIDEO_RECUR_PARSING,
                  APP_CFG_GRPID_CUSTOM_MMP_BASE,
                  APP_CFG_RECID_CUSTOM_MMP_VIDEO_RECUR_PARSING,
                  CFG_8BIT_T,
                  1,
                  &ui1_g_cust_mmp_video_recur_parsing_def,
                  1,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_MMP_PHOTO_SORT,
                  APP_CFG_GRPID_CUSTOM_MMP_BASE,
                  APP_CFG_RECID_CUSTOM_MMP_PHOTO_SORT,
                  CFG_8BIT_T,
                  1,
                  &ui1_g_cust_mmp_photo_sort,
                  1,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_MMP_AUDIO_SORT,
                  APP_CFG_GRPID_CUSTOM_MMP_BASE,
                  APP_CFG_RECID_CUSTOM_MMP_AUDIO_SORT,
                  CFG_8BIT_T,
                  1,
                  &ui1_g_cust_mmp_audio_sort,
                  1,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

    DECLARE_FIELD(IDX_CUSTOM_MMP_VIDEO_SORT,
                  APP_CFG_GRPID_CUSTOM_MMP_BASE,
                  APP_CFG_RECID_CUSTOM_MMP_VIDEO_SORT,
                  CFG_8BIT_T,
                  1,
                  &ui1_g_cust_mmp_video_sort,
                  1,
                  NULL,
                  NULL,
                  ACFG_ACCESS_PUBLIC);

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
extern INT32 acfg_cust_mmp_post_init(VOID)
{
    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_mmp_photo_recur_parsing
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_mmp_photo_recur_parsing(UINT8 ui1_id)
{
    return acfg_set(IDX_CUSTOM_MMP_PHOTO_RECUR_PARSING, &ui1_id, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_mmp_photo_recur_parsing
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_mmp_photo_recur_parsing(UINT8* pui1_id)
{
    SIZE_T  z_size;

    if(pui1_id == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_MMP_PHOTO_RECUR_PARSING, (VOID*)pui1_id, &z_size);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_mmp_audio_recur_parsing
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_mmp_audio_recur_parsing(UINT8 ui1_id)
{
    return acfg_set(IDX_CUSTOM_MMP_AUDIO_RECUR_PARSING, &ui1_id, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_mmp_audio_recur_parsing
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_mmp_audio_recur_parsing(UINT8* pui1_id)
{
    SIZE_T  z_size;

    if(pui1_id == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_MMP_AUDIO_RECUR_PARSING, (VOID*)pui1_id, &z_size);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_mmp_video_recur_parsing
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_mmp_video_recur_parsing(UINT8 ui1_id)
{
    return acfg_set(IDX_CUSTOM_MMP_VIDEO_RECUR_PARSING, &ui1_id, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_mmp_video_recur_parsing
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_mmp_video_recur_parsing(UINT8* pui1_id)
{
    SIZE_T  z_size;

    if(pui1_id == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_MMP_VIDEO_RECUR_PARSING, (VOID*)pui1_id, &z_size);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_photo_setting_shuffle
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/

INT32 a_cfg_custom_set_photo_setting_shuffle(
            UINT8       ui1_photo_set)
{
    SIZE_T  z_size;
    INT32   i4_photo_set = 0;
    INT32   i4_get_photo_set;
    INT32   i4_ret;

    i4_ret = acfg_get(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_get_photo_set , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    i4_photo_set = (INT32)(((UINT16)ui1_photo_set) << 8);
    i4_get_photo_set &= 0xFFFF00FF;
    i4_get_photo_set |= i4_photo_set;

    return acfg_set(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_get_photo_set, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_photo_setting_shuffle
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_photo_setting_shuffle(
            UINT8*      pui1_photo_get)
{
    SIZE_T          z_size;
    INT32           i4_ret;
    INT32           i4_val = 0;

    if (pui1_photo_get == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_val , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pui1_photo_get = (UINT8)((i4_val & 0x0000FF00) >> 8);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_photo_setting_speed
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_photo_setting_speed(
                UINT8       ui1_photo_set)
{
    SIZE_T  z_size;
    INT32   i4_photo_set = 0;
    INT32   i4_get_photo_set;
    INT32   i4_ret;

    i4_ret = acfg_get(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_get_photo_set , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    i4_photo_set = ((UINT32)ui1_photo_set) << 16;
    i4_get_photo_set &= 0xFF00FFFF;
    i4_get_photo_set |= i4_photo_set;

    return acfg_set(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_get_photo_set, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_photo_setting_speed
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_photo_setting_speed(
                UINT8*      pui1_photo_get)
{
    SIZE_T          z_size;
    INT32           i4_ret;
    INT32           i4_val = 0;

    if (pui1_photo_get == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_val , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pui1_photo_get = (UINT8)((i4_val & 0x00FF0000) >> 16);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_photo_setting_effect
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_photo_setting_effect(
                UINT8       ui1_photo_set)
{
    SIZE_T  z_size;
    INT32   i4_photo_set = 0;
    INT32   i4_get_photo_set;
    INT32   i4_ret;

    i4_ret = acfg_get(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_get_photo_set , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    i4_photo_set = ((UINT32)ui1_photo_set) << 24;
    i4_get_photo_set &= 0x00FFFFFF;
    i4_get_photo_set |= i4_photo_set;

    return acfg_set(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_get_photo_set, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_photo_setting_effect
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_photo_setting_effect(
                UINT8*      pui1_photo_get)
{
    SIZE_T          z_size;
    INT32           i4_ret;
    INT32           i4_val = 0;

    if (pui1_photo_get == NULL)
    {
     return APP_CFGR_INV_ARG;
    }

    i4_ret = acfg_get(IDX_CUSTOM_MMP_PHOTO_SET_INFO, &i4_val , &z_size);
    ACFG_CHK_FAIL (i4_ret, i4_ret);

    *pui1_photo_get = (UINT8)((i4_val & 0xFF000000) >> 24);

    return APP_CFGR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_mmp_photo_sort
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_mmp_photo_sort(
                UINT8       ui1_id)
{
    return acfg_set(IDX_CUSTOM_MMP_PHOTO_SORT, &ui1_id, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_mmp_photo_sort
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_mmp_photo_sort(
                UINT8*      pui1_id)
{
    SIZE_T  z_size;

    if(pui1_id == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_MMP_PHOTO_SORT, (VOID*)pui1_id, &z_size);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_mmp_audio_sort
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_mmp_audio_sort(
                UINT8       ui1_id)
{
    return acfg_set(IDX_CUSTOM_MMP_AUDIO_SORT, &ui1_id, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_mmp_audio_sort
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_mmp_audio_sort(
                UINT8*      pui1_id)
{
    SIZE_T  z_size;

    if(pui1_id == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_MMP_AUDIO_SORT, (VOID*)pui1_id, &z_size);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_set_mmp_video_sort
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_set_mmp_video_sort(
                UINT8       ui1_id)
{
    return acfg_set(IDX_CUSTOM_MMP_VIDEO_SORT, &ui1_id, 1);
}

/*-----------------------------------------------------------------------------
 * Name: a_cfg_custom_get_mmp_video_sort
 *
 * Description:
 *
 * Inputs: -
 *
 * Outputs:
 *
 * Returns:
 *
 *-----------------------------------------------------------------------------*/
INT32 a_cfg_custom_get_mmp_video_sort(
                UINT8*      pui1_id)
{
    SIZE_T  z_size;

    if(pui1_id == NULL)
    {
        return APP_CFGR_INV_ARG;
    }

    return acfg_get(IDX_CUSTOM_MMP_VIDEO_SORT, (VOID*)pui1_id, &z_size);
}
#endif /* APP_MMP_SUPPORT */
