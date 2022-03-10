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
 * $RCSfile: vol_ctrl_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description: Password dialog is a signaltone
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_cfg.h"
#include "c_wgl_image.h"

#include "app_util/a_cfg.h"
#include "nav/nav_common.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_view.h"
#include "res/nav/vol_ctrl/vol_ctrl_custom.h"
#include "res/nav/nav_colors.h"
#include "res/nav/nav_dbg.h"

#ifdef APP_VOLUME_CTRL
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
#ifdef APP_MUTE_DISP_AS_TEXT
static WGL_FONT_INFO_T  t_g_font_info = {FE_FNT_SIZE_MEDIUM, FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: vol_ctrl_mute_init_rc
 *
 * Description:
 *      Initiate the colors for menu.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *  0 - Successful
 *  -1- Failed
 ----------------------------------------------------------------------------*/
INT32 vol_ctrl_mute_init_rc(
                    VOL_CTRL_MUTE_RC_T*         pt_rc
                    )
{
#if 0
    INT32 i4_ret;

    i4_ret = nav_img_create_default_bk_img_tpl(&pt_rc->h_img_bk);
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
#else
    pt_rc->h_img_bk = NULL_HANDLE;
#endif
    pt_rc->pt_text_font = &t_g_font_info;
    pt_rc->t_text_fg    = NAV_COLOR(NAV_COLOR_ID_ORANGE);
    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: vol_ctrl_mute_deinit_rc
 *
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
INT32 vol_ctrl_mute_deinit_rc(
                    VOL_CTRL_MUTE_RC_T*         pt_rc
                    )
{
#if 0
    c_wgl_img_tpl_destroy (pt_rc->h_img_bk);
    pt_rc->h_img_bk = NULL_HANDLE;
#endif
    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_get_vol_cfg_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_get_vol_cfg_id(
                    UINT8                   ui1_idx,
                    UINT16*                 pui2_cfg_id
                    )
{
    if (ui1_idx > ((UINT8)z_g_vol_ch_params_size)) {
        return NAVR_INV_ARG;
    }

    *pui2_cfg_id = t_g_vol_ch_params[ui1_idx].ui2_cfg_id;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_next_vol_cfg_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_next_vol_cfg_id(
                    UINT8*                  pui1_idx,
                    UINT16*                 pui2_cfg_id
                    )
{
    UINT8 ui1_idx;

    if (pui1_idx == NULL || pui2_cfg_id == NULL) {
        return NAVR_INV_ARG;
    }

    ui1_idx = *pui1_idx;

    if (ui1_idx >= ((UINT8)z_g_vol_ch_params_size)) {
        ui1_idx = 0;
    } else {
        if (((UINT8)(ui1_idx+1)) == ((UINT8)z_g_vol_ch_params_size)) {
            ui1_idx = 0;
        } else {
            ui1_idx += 1;
        }
    }

    if ((*pui1_idx) == ui1_idx) {
        return NAVR_NO_ACTION;
    }

    *pui2_cfg_id = t_g_vol_ch_params[ui1_idx].ui2_cfg_id;
    *pui1_idx    = ui1_idx;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_prev_vol_cfg_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 vol_ctrl_prev_vol_cfg_id(
                    UINT8*                  pui1_idx,
                    UINT16*                 pui2_cfg_id
                    )
{
    UINT8 ui1_idx;

    if (pui1_idx == NULL || pui2_cfg_id == NULL) {
        return NAVR_INV_ARG;
    }

    ui1_idx = *pui1_idx;

    if (ui1_idx >= ((UINT8)z_g_vol_ch_params_size)) {
        ui1_idx = 0;
    } else {
        if (ui1_idx == 0) {
            ui1_idx = (UINT8)(z_g_vol_ch_params_size-1);
        } else {
            ui1_idx -= 1;
        }
    }

    if ((*pui1_idx) == ui1_idx) {
        return NAVR_NO_ACTION;
    }

    *pui2_cfg_id = t_g_vol_ch_params[ui1_idx].ui2_cfg_id;
    *pui1_idx    = ui1_idx;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      vol_ctrl_get_vol_ch_display_name
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
UTF16_T* vol_ctrl_get_vol_ch_display_name(
                    UINT8                   ui1_idx
                    )
{
    if (ui1_idx > ((UINT8)z_g_vol_ch_params_size)) {
        return NULL;
    }

    return MLM_NAV_TEXT(nav_get_mlm_lang_id(), t_g_vol_ch_params[ui1_idx].ui2_msg_key);
}
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
#endif
