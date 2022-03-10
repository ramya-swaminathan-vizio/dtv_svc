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
 * $RCSfile: sound_effect_custom.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 164f107778d40dc636d1d0f28124de3c $
 *
 * Description:
 *      This file contains the color used by the MENU application.
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_scc.h"
#include "u_cfg.h"
#include "c_svctx.h"
#include "c_handle.h"
#include "c_wgl.h"

#include "app_util/a_cfg.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"
#include "nav/sound_effect/sound_effect.h"
#include "res/nav/sound_effect/sound_effect_custom.h"
#include "res/menu2/menu_mlm.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

#define NAV_SOUND_EFFECT_TEXT_IDX                  MLM_MENU_KEY_AUD_EQ
#define NAV_SOUND_EFFECT_TEXT(lang, key)           MLM_MENU_TEXT(lang, key)

/* One-to-One mapping between AP<=>MW<=>DRV */
#define NAV_SOUND_EFFECT_NUMBERS                   8

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Mapping NAV mlm to MENU mlm
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static UINT8    nav_get_mlm_lang_id_and_trans_to_menu(VOID)
{
#ifndef APP_MLM_S639_TO_LANGIDX_SUPPORT
/* Nav MLM Mapping to Menu MLM */

/*  NAV           MENU
   0 ENG         0 ENG
   1 FRE         1 ESL
   2 SPA         2 FRA
   3 KOA
*/

    UINT8       ui1_id;

    ui1_id    = nav_get_mlm_lang_id();

    if(ui1_id == 0)
    {
        return 0;
    }
    else if(ui1_id == 1)
    {
        return 2;
    }
    else if(ui1_id == 2)
    {
        return 1;
    }
    else if(ui1_id == 3)
    {
        return 0;
    }
    else
    {
        /* unhandled nav lang_id */
        return 0;
    }
#else /* APP_MLM_S639_TO_LANGIDX_SUPPORT */

    ISO_639_LANG_T s639_lang;
    a_cfg_get_gui_lang(s639_lang);
    return (UINT8) mlm_menu_s639_to_langidx(s639_lang);

#endif

}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Return the pw2s_text of title.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UTF16_T* nav_sound_effect_custom_get_title(VOID)
{
    return (UTF16_T*) NAV_SOUND_EFFECT_TEXT(nav_get_mlm_lang_id_and_trans_to_menu(),
                                        NAV_SOUND_EFFECT_TEXT_IDX);
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Give index, return the pw2s_text of that index.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

UTF16_T* nav_sound_effect_custom_get_index_text(UINT16     ui2_idx)
{
    return (UTF16_T*) NAV_SOUND_EFFECT_TEXT(nav_get_mlm_lang_id_and_trans_to_menu(),
                                        (UINT16) (NAV_SOUND_EFFECT_TEXT_IDX+1+ui2_idx));
}

/*----------------------------------------------------------------------------
 * Name: _set_vid_sound_effect_idx
 *
 * Description: Set sound effect mode
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
VOID nav_sound_effect_custom_set_sound_effect_idx(UINT16 ui2_idx)
{
    a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQUALIZER),
                 (INT16) ui2_idx);

    a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQUALIZER));
}

/*----------------------------------------------------------------------------
 * Name: _get_vid_sound_effect_idx
 *
 * Description: Return the index of sound effect
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
UINT16 nav_sound_effect_custom_get_sound_effect_idx(VOID)
{
    INT16   i2_val = 0;

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_AUDIO, APP_CFG_RECID_AUD_EQUALIZER),
                 &i2_val);

    return (UINT16)i2_val;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Get sound effect numbers
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 nav_sound_effect_custom_get_sound_effect_numbers(VOID)
{
    return NAV_SOUND_EFFECT_NUMBERS;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Post init for sound effect.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 nav_sound_effect_custom_post_init(VOID)
{
    return NAVR_OK;
}


