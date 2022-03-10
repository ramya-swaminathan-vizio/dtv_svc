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
 * $RCSfile: aud_only.c,v $
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

/**
 * @file aud_only_custom.c
 *
 * @brief This file implements customization part of the Audio Only.
 *
 * @author Qingfeng Liu
 */
#ifdef APP_NAV_AUD_ONLY_SUPPORT
/*-----------------------------------------------------------------------------
 *               include files
 *-----------------------------------------------------------------------------*/

#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"
#include "c_iom.h"
#include "c_scc.h"

#include "app_util/a_cfg.h"
#include "nav/a_navigator.h"
#include "nav/aud_only/aud_only.h"

#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/nav/aud_only/aud_only_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/

/**
 * @brief   This function is used to disable the RCU keys and Panel keys.
 * @param   h_iom [in]    Handle of the IO manager.
 * @param   b_disable [in]    TRUE for disable keys, FALSE for enable keys.* @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
INT32 nav_aud_only_custom_disable_keys(HANDLE_T h_iom, BOOL b_disable)
{
    INT32  i4_ret;

#if 0 /*Disable all*/
    SIZE_T z_info_len;
    UINT64 ui8_evt_src;

    z_info_len = sizeof (UINT64);

    i4_ret = c_iom_get (h_iom,
               IOM_GET_IRRC_EVT_SRC_MASK,
               (VOID*)& ui8_evt_src,
               & z_info_len);
    AUD_ONLY_CHK_FAIL(i4_ret);

    if (b_disable)
    {
        /* Disable Remote control. */
        ui8_evt_src &= ~(IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL) |
                                       IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL));
    }
    else
    {
        /* Enable Remote control. */
        ui8_evt_src |= IOM_EVT_SRC_TO_MASK(KEY_SRC_REMOTE_CTRL) |
                       IOM_EVT_SRC_TO_MASK(KEY_SRC_FRONT_PANEL);
    }

    i4_ret = c_iom_set (h_iom,
               IOM_SET_IRRC_EVT_SRC_MASK,
               (VOID*)& ui8_evt_src,
               sizeof (UINT64));
    AUD_ONLY_CHK_FAIL(i4_ret);
#endif

    DISABLE_EVTCODE_T   t_disable_evtcode;
    UINT32              aui4_evtcode_arr[9];

    c_memset (&t_disable_evtcode, 0, sizeof(DISABLE_EVTCODE_T));

    t_disable_evtcode.b_positive_filter = FALSE;
    t_disable_evtcode.pui4_evtcode_arr = aui4_evtcode_arr;

    if (!b_disable)
    {
        t_disable_evtcode.b_enable = FALSE; /*Enable the key*/
    }
    else
    {
        /*Except these keys, other key will be disable.*/
        aui4_evtcode_arr[0] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_POWER);
        aui4_evtcode_arr[1] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_POWER);
        aui4_evtcode_arr[2] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_MUTE);
        aui4_evtcode_arr[3] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_MUTE);
        aui4_evtcode_arr[4] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_VOL_UP);
        aui4_evtcode_arr[5] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_UP);
        aui4_evtcode_arr[6] = IOM_GEN_EVT_CODE(KEY_SRC_REMOTE_CTRL, BTN_VOL_DOWN);
        aui4_evtcode_arr[7] = IOM_GEN_EVT_CODE(KEY_SRC_FRONT_PANEL, BTN_VOL_DOWN);

        aui4_evtcode_arr[8] = 0;

        t_disable_evtcode.z_evtcode_cnt = 8;

        t_disable_evtcode.b_enable = TRUE;
    }

    i4_ret = c_iom_set_global_disable_evtcode(&t_disable_evtcode);
    AUD_ONLY_CHK_FAIL(i4_ret);

    return NAVR_OK;
}
/**
 * @brief   This function is used to disable the RCU keys and Panel keys.
 * @param   b_disable [in]    TRUE for disable keys, FALSE for enable keys.
 * @retval  NAVR_OK     The function succeded.
 * @retval  Otherwise   The function failed.
 */
BOOL nav_aud_only_custom_ignore_keys(UINT32 ui4_key_code, IOM_NFY_COND_T  e_nfy_cond)
{
    BOOL b_is_ignore = FALSE;

    if (e_nfy_cond == IOM_NFY_COND_BTN_REPEAT)
    {
        /*Do some things*/
    }

    switch (IOM_GET_EVT_GRP_ID(ui4_key_code))
    {
    case BTN_POWER:    /* power-off */
    case BTN_VOL_UP:
    case BTN_VOL_DOWN:
    case BTN_MUTE:
        b_is_ignore = TRUE;
        break;
    default:
        break;
    }

    return b_is_ignore;

}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/

#endif /*APP_NAV_AUD_ONLY_SUPPORT*/

