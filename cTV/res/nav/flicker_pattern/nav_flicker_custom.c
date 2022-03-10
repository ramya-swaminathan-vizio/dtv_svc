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
 * $RCSfile: nav_flicker_custom.c,v $
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
// FXC Jim 20180423 removed #ifdef APP_NAV_FLICKER_SUPPORT
#if 1//(defined(APP_NAV_FLICKER_SUPPORT)||defined(FXCAPP_NAV_FLICKER_SUPPORT))
#include "u_common.h"
#include "u_svctx.h"
#include "c_dbg.h"
#include "c_tsl.h"
#include "c_svl.h"
#include "c_svctx.h"
#include "u_cecm.h"
#include "c_cecm.h"
#include "c_iom.h"
#include "c_pcl.h"

#include "nav/nav_common.h"
#include "nav/navigator.h"
#include "nav/flicker_pattern/nav_flicker.h"
#include "res/nav/nav_variant.h"
#include "c_handle.h"
#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "res/app_util/config/a_cfg_custom.h"
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static INT16 g_i2_bti_val;
/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name:    nav_flicker_custom_pre_init
 * Description: This function is called before common part init.
 * Input:   pv_param1   -
 *          pv_param2   -
 *          pv_param3   -
 *          pv_param4   -
 * Output:  -
 * Returns  NAVR_OK     This function succeeded.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_flicker_custom_pre_init (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    INT32 i4_ret;
    INT16 i2_min, i2_max;
    
    /* Set the brightness to the middle value. */
    a_cfg_eep_enable_flush (FALSE);
    i4_ret = a_cfg_av_get_min_max (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), &i2_min, &i2_max);
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = a_cfg_av_get (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), &g_i2_bti_val);
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = a_cfg_av_set (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), ((i2_min+i2_max)/2));
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:    nav_flicker_custom_pre_deinit
 * Description: This function is called after common part init.
 * Input:   pv_param1   -
 *          pv_param2   -
 *          pv_param3   -
 *          pv_param4   -
 * Output:  -
 * Returns  NAVR_OK     This function succeeded.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_flicker_custom_pre_deinit (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    INT32 i4_ret;
    
    i4_ret = a_cfg_av_set (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI), g_i2_bti_val);
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }
    i4_ret = a_cfg_av_update (CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_BRI));
    if (i4_ret != APP_CFGR_OK)
    {
        return NAVR_FAIL;
    }
    a_cfg_eep_enable_flush (TRUE);
    
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:    nav_flicker_custom_post_init
 * Description: This function is called before common part deinit.
 * Input:   pv_param1   -
 *          pv_param2   -
 *          pv_param3   -
 *          pv_param4   -
 * Output:  -
 * Returns  NAVR_OK     This function succeeded.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_flicker_custom_post_init (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name:    nav_flicker_custom_post_deinit
 * Description: This function is called after common part deinit.
 * Input:   pv_param1   -
 *          pv_param2   -
 *          pv_param3   -
 *          pv_param4   -
 * Output:  -
 * Returns  NAVR_OK     This function succeeded.
 *          Otherwise   This function failed.
 *---------------------------------------------------------------------------*/
INT32 nav_flicker_custom_post_deinit (VOID* pv_param1, VOID* pv_param2, VOID* pv_param3, VOID* pv_param4)
{
    return NAVR_OK;
}
#endif
