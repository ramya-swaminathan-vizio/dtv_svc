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
 * $RCSfile: screen_mode_custom.c,v $
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

#include "app_util/a_tv.h"
#include "app_util/a_screen_mode.h"
#include "app_util/a_cfg.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_view.h"
#include "nav/screen_mode/screen_mode.h"
#include "res/nav/screen_mode/screen_mode_custom.h"
#include "res/app_util/screen_mode/sml_mlm.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum _SCREEN_MODE_INPUT_T
{
    SCREEN_INPUT_TV,
    SCREEN_INPUT_HDMI,
    SCREEN_INPUT_PC,
    SCREEN_INPUT_DVI,
    SCREEN_INPUT_LAST_ENUM
}SCREEN_MODE_INPUT_T;

static SCREEN_MODE_INPUT_T  e_cur_sm_input;
/*-----------------------------------------------------------------------------
                    data declarations
 ----------------------------------------------------------------------------*/

#define NAV_SCREEN_MODE_TITLE_TEXT_IDX            MLM_NAV_KEY_NAV_CHANGE_ASPECT_RATIO
#define NAV_SCREEN_MODE_TITLE_TEXT(lang, key)     MLM_NAV_TEXT(lang, key);

#define NAV_SCREEN_MODE_TEXT_IDX                  0 /* MLM_SML_KEY_MSG_NORMAL */
#define NAV_SCREEN_MODE_TEXT(lang, key)           MLM_SML_TEXT(lang, key)

/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
extern INT32 _nav_screen_mode_get_current_input(VOID)
{
    INT32                       i4_ret;
    HANDLE_T                    h_svctx = NULL_HANDLE ;
    TV_WIN_ID_T                 e_focus_id;
    ISL_REC_T                   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T   t_resolution;

    c_memset(&t_resolution, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    i4_ret = a_tv_get_focus_win(&e_focus_id);
    NAV_SCREEN_MODE_LOG_ON_FAIL(i4_ret);

    i4_ret = nav_get_svctx_handle(e_focus_id, &h_svctx);
    NAV_SCREEN_MODE_LOG_ON_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(e_focus_id, &t_isl_rec);
    NAV_SCREEN_MODE_LOG_ON_FAIL(i4_ret);

    i4_ret = c_svctx_get_video_src_resolution(h_svctx, &t_resolution);
    NAV_SCREEN_MODE_LOG_ON_FAIL(i4_ret);

    if (INP_SRC_TYPE_TV == t_isl_rec.e_src_type)
    {
        e_cur_sm_input = SCREEN_INPUT_TV;
    }
    else if (INP_SRC_TYPE_AV == t_isl_rec.e_src_type)
    {
        if (DEV_AVC_HDMI == t_isl_rec.t_avc_info.e_video_type)
        {
            e_cur_sm_input = SCREEN_INPUT_HDMI;
            if (VSH_SRC_TIMING_GRAPHIC == t_resolution.e_timing_type)
            {
                e_cur_sm_input = SCREEN_INPUT_DVI;
            }
        }
        else if(DEV_AVC_VGA == t_isl_rec.t_avc_info.e_video_type)
        {
            if (VSH_SRC_TIMING_VIDEO == t_resolution.e_timing_type)
            {
                e_cur_sm_input = SCREEN_INPUT_TV;
            }
            else
            {
                e_cur_sm_input = SCREEN_INPUT_PC;
            }
        }
        else
        {
            e_cur_sm_input = SCREEN_INPUT_TV;
        }
    }
    else
    {
        e_cur_sm_input = SCREEN_INPUT_TV;
    }

    return 0;
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
UTF16_T* nav_screen_mode_custom_get_title(VOID)
{
    return (UTF16_T*) NAV_SCREEN_MODE_TITLE_TEXT(nav_get_mlm_lang_id(),
                                                 NAV_SCREEN_MODE_TITLE_TEXT_IDX);
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
UTF16_T* nav_screen_mode_custom_get_index_text(UINT16     ui2_idx)
{
    if (nav_get_mlm_lang_id() < MLM_SML_NUM_LANG
            && (NAV_SCREEN_MODE_TEXT_IDX+ui2_idx) < MLM_SML_NUM_KEY) {
        return (UTF16_T*) NAV_SCREEN_MODE_TEXT(
                                        nav_get_mlm_lang_id(),
                                        NAV_SCREEN_MODE_TEXT_IDX+ui2_idx
                                        );
    } else {
        return NULL;
    }
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: Determine screen mode element numbers
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 nav_screen_mode_custom_get_vid_screen_mode_numbers(VOID)
{
    return 6;
}
