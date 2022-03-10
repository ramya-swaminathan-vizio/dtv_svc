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
 * $RCSfile: screen_mode.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: chengwei.shan $
 * $CCRevision: /main/DTV_X/DTV_X_HQ_int/DTV_X_ATSC/3 $
 * $SWAuthor: Chengwei Shan $
 * $MD5HEX: 72ec35f463230d3f1747ea7bd18764a5 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifdef APP_537X_SUPPORT

#include "u_common.h"
#include "u_cfg.h"
#include "c_scc.h"
#include "c_svctx.h"
#include "c_handle.h"

#include "app_util/a_cfg.h"
#include "app_util/a_common.h"
#include "app_util/a_screen_mode.h"
#include "nav/screen_mode/screen_mode.h"
#include "res/nav/screen_mode/screen_mode_custom.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/nav/nav_view.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_mlm.h"

#include "res/nav/banner2/banner_rc.h"
#include "nav/c4tv_apron/c4tv_apron.h"
#include "mmp/a_mmp.h"
#include "am/a_am.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define CFG_ID_SCREEN_MODE           CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_SCREEN_MODE)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static NAV_SCREEN_MODE_T t_g_nav_screen_mode;

static UTF16_T*      apw2s_g_out_fmts[SCREEN_FMT_LAST_VALID_ENTRY] = {0};

static UINT8                        ui1_g_element_in_listbox = 0;
static SCC_VID_SCREEN_MODE_T        ag_e_scr_mode_in_listbox[16];

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_view_load_msgs(
                    UINT8             ui1_lang_id
                    )
{
    apw2s_g_out_fmts [SCREEN_FMT_4_3_NORMAL            ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NORMAL);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_LETTERBOX         ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_LETTERBOX);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_PAN_SCAN          ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_PAN_SCAN);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_USER_DEFINED      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_USER_DEFINED);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_NON_LINEAR_ZOOM   ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_DOT_BY_DOT        ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_DOT_BY_DOT);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_CUSTOM_DEF_0      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_0);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_CUSTOM_DEF_1      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_1);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_CUSTOM_DEF_2      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_2);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_CUSTOM_DEF_3      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_3);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_CUSTOM_DEF_4      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_4);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_CUSTOM_DEF_5      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_5);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_CUSTOM_DEF_6      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_6);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_CUSTOM_DEF_7      ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_CUSTOM_DEF_7);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_NLZ_CUSTOM_DEF_0  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_0);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_NLZ_CUSTOM_DEF_1  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_1);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_NLZ_CUSTOM_DEF_2  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_2);
    apw2s_g_out_fmts [SCREEN_FMT_4_3_NLZ_CUSTOM_DEF_3  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_4_3, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_3);

    apw2s_g_out_fmts [SCREEN_FMT_16_9_NORMAL           ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NORMAL);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_LETTERBOX        ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_LETTERBOX);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_PAN_SCAN         ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_PAN_SCAN);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_USER_DEFINED     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_USER_DEFINED);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_NON_LINEAR_ZOOM  ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_DOT_BY_DOT       ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_DOT_BY_DOT);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_CUSTOM_DEF_0     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_0);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_CUSTOM_DEF_1     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_1);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_CUSTOM_DEF_2     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_2);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_CUSTOM_DEF_3     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_3);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_CUSTOM_DEF_4     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_4);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_CUSTOM_DEF_5     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_5);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_CUSTOM_DEF_6     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_6);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_CUSTOM_DEF_7     ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_CUSTOM_DEF_7);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_NLZ_CUSTOM_DEF_0 ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_0);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_NLZ_CUSTOM_DEF_1 ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_1);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_NLZ_CUSTOM_DEF_2 ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_2);
    apw2s_g_out_fmts [SCREEN_FMT_16_9_NLZ_CUSTOM_DEF_3 ] = a_sml_get_disp_name (VSH_SRC_ASPECT_RATIO_16_9, SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_3);

    apw2s_g_out_fmts [SCREEN_FMT_NO_ADJUST             ] = MLM_NAV_TEXT(ui1_lang_id, MLM_NAV_KEY_MSG_NO_ADJUST);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_get_src_asp_ratio
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VSH_SRC_ASPECT_RATIO_T _nav_screen_mode_get_src_asp_ratio (
                    TV_WIN_ID_T             e_focus_tv_win_id
                    )
{
    INT32                       i4_ret;
    VSH_SRC_RESOLUTION_INFO_T   t_src_res;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;;

    c_memset(&t_src_res, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

    /* Get source aspect ratio. */
    i4_ret = nav_get_crnt_video_res_info (e_focus_tv_win_id, &t_src_res);

    if ((i4_ret != NAVR_OK) ||
        (t_src_res.ui4_width == 0) ||
        (t_src_res.ui4_height == 0) ||
        (t_src_res.e_timing_type == VSH_SRC_TIMING_NOT_SUPPORT))
    {
        e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_UNKNOWN;
    }
    else
    {
        /* Get aspect ratio from Screen Mode Library. */
        e_src_asp_ratio = a_sml_get_src_asp_ratio (& t_src_res);
    }

    if (VSH_SRC_ASPECT_RATIO_UNKNOWN == e_src_asp_ratio)
    {
        e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_4_3;
        //e_src_asp_ratio = VSH_SRC_ASPECT_RATIO_16_9;
    }

    return e_src_asp_ratio;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_get_screen_fmt
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static SCREEN_FMT_T _nav_screen_mode_get_screen_fmt (
                            VSH_SRC_ASPECT_RATIO_T        e_src_asp_ratio,
                            SCC_VID_SCREEN_MODE_T         e_scr_mode
                            )
{
    SCREEN_FMT_T      e_scr_fmt;

    switch (e_scr_mode)
    {
        case SCC_VID_SCREEN_MODE_NORMAL:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_NORMAL : SCREEN_FMT_16_9_NORMAL;
            break;

        case SCC_VID_SCREEN_MODE_LETTERBOX:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_LETTERBOX : SCREEN_FMT_16_9_LETTERBOX;
            break;

        case SCC_VID_SCREEN_MODE_USER_DEFINED:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_USER_DEFINED : SCREEN_FMT_16_9_USER_DEFINED;
            break;

        case SCC_VID_SCREEN_MODE_PAN_SCAN:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_PAN_SCAN : SCREEN_FMT_16_9_PAN_SCAN;
            break;

        case SCC_VID_SCREEN_MODE_NON_LINEAR_ZOOM:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_NON_LINEAR_ZOOM : SCREEN_FMT_16_9_NON_LINEAR_ZOOM;
            break;

        case SCC_VID_SCREEN_MODE_DOT_BY_DOT:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_DOT_BY_DOT : SCREEN_FMT_16_9_DOT_BY_DOT;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_0:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_CUSTOM_DEF_0 : SCREEN_FMT_16_9_CUSTOM_DEF_0;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_1:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_CUSTOM_DEF_1 : SCREEN_FMT_16_9_CUSTOM_DEF_1;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_2:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_CUSTOM_DEF_2 : SCREEN_FMT_16_9_CUSTOM_DEF_2;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_3:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_CUSTOM_DEF_3 : SCREEN_FMT_16_9_CUSTOM_DEF_3;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_4:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_CUSTOM_DEF_4 : SCREEN_FMT_16_9_CUSTOM_DEF_4;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_5:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_CUSTOM_DEF_5 : SCREEN_FMT_16_9_CUSTOM_DEF_5;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_6:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_CUSTOM_DEF_6 : SCREEN_FMT_16_9_CUSTOM_DEF_6;
            break;

        case SCC_VID_SCREEN_MODE_CUSTOM_DEF_7:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_CUSTOM_DEF_7 : SCREEN_FMT_16_9_CUSTOM_DEF_7;
            break;

        case SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_0:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_NLZ_CUSTOM_DEF_0 : SCREEN_FMT_16_9_NLZ_CUSTOM_DEF_0;
            break;

        case SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_1:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_NLZ_CUSTOM_DEF_0 : SCREEN_FMT_16_9_NLZ_CUSTOM_DEF_1;
            break;

        case SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_2:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_NLZ_CUSTOM_DEF_0 : SCREEN_FMT_16_9_NLZ_CUSTOM_DEF_2;
            break;

        case SCC_VID_SCREEN_MODE_NLZ_CUSTOM_DEF_3:
            e_scr_fmt = (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3) ?
                        SCREEN_FMT_4_3_NLZ_CUSTOM_DEF_0 : SCREEN_FMT_16_9_NLZ_CUSTOM_DEF_3;
            break;

        default:
            e_scr_fmt = SCREEN_FMT_NO_ADJUST;
            break;
    }

    return e_scr_fmt;
}

/*----------------------------------------------------------------------------
 * Name: _nav_screen_mode_refresh_list
 *
 * Description: Refresh the list and save the operation mode.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_screen_mode_refresh_list(VOID)
{
    NAV_SCREEN_MODE_T*          pt_this = & t_g_nav_screen_mode;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio;
    SCC_VID_SCREEN_MODE_T       e_scr_mode = SCC_VID_SCREEN_MODE_UNKNOWN;
    SCREEN_FMT_T                e_scr_fmt;
    UINT16                      ui2_elem_num = 0;
    UINT16                      ui2_idx;

    /* Set Title */
    pt_this->t_view_hdlr.pf_set_title_text(nav_screen_mode_custom_get_title());

    /* Get the element numbers (1. Get src asp ratio 2. use a_sml API to get num recs) */

    e_src_asp_ratio = _nav_screen_mode_get_src_asp_ratio (pt_this->e_focus_tv_win_id);

#if 0
    /* Save the current states */
    if (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_4_3)
    {
        ui1_g_operation_mode = OPERATION_MODE_4_3;
    }
    else if (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_16_9 ||
             e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_2_21_1)
    {
        ui1_g_operation_mode = OPERATION_MODE_16_9;
    }
    else
    {   /* Unknown, not adjustable */
        ui1_g_operation_mode = OPERATION_MODE_UNKNOWN;
    }

    if (ui1_g_operation_mode == OPERATION_MODE_UNKNOWN)
    {
        /* Reset the listbox */
        pt_this->t_view_hdlr.pf_set_elem_num(1);

        e_scr_fmt = SCREEN_FMT_NO_ADJUST;
        pt_this->t_view_hdlr.pf_set_index_text(0, apw2s_g_out_fmts[e_scr_fmt]);

        /* Return directly, no further insert needed. */
        return;
    }
#endif

    /* Determine the element numbers */
    a_sml_get_num_rec(e_src_asp_ratio, (UINT8*) &ui2_elem_num);

    if (ui2_elem_num == 0)
    {
        ui2_elem_num = 1;   /* One for "Not Adjustable" */
    }
    else if (ui2_elem_num > 16)
    {
        ui2_elem_num = 16;
    }

    ui1_g_element_in_listbox = (UINT8) ui2_elem_num;

    /* Reset the listbox */
    pt_this->t_view_hdlr.pf_set_elem_num(ui2_elem_num);


    /* Set the element text ----------------------------------------------- */

    /* Get first screen mode. */
    a_sml_iterate_rec (e_src_asp_ratio,
                       SML_ITERATE_DIR_FIRST,
                       & e_scr_mode);

    /* Put the first e_scr_mode in bucket */
    ag_e_scr_mode_in_listbox[0] = e_scr_mode;

    /* Get screen format by e_src_asp_ratio & e_scr_mode */
    e_scr_fmt = _nav_screen_mode_get_screen_fmt (e_src_asp_ratio, e_scr_mode);

    /* Set the first index-text to screen format */
    pt_this->t_view_hdlr.pf_set_index_text(0, apw2s_g_out_fmts[e_scr_fmt]);

    for (ui2_idx = 1 ; ui2_idx < ui2_elem_num ; ui2_idx++)
    {
        a_sml_iterate_rec (e_src_asp_ratio,
                           SML_ITERATE_DIR_NEXT,
                           & e_scr_mode);

        ag_e_scr_mode_in_listbox[ui2_idx] = e_scr_mode;

        /* Get screen format. */
        e_scr_fmt = _nav_screen_mode_get_screen_fmt (e_src_asp_ratio, e_scr_mode);
        pt_this->t_view_hdlr.pf_set_index_text(ui2_idx, apw2s_g_out_fmts[e_scr_fmt]);
    }

    return;
}

/*----------------------------------------------------------------------------
 * Name: _nav_screen_mode_refresh_highlight
 *
 * Description: Refresh the highlight index.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _nav_screen_mode_refresh_highlight(VOID)
{
    INT32                       i4_ret;
    NAV_SCREEN_MODE_T*          pt_this = & t_g_nav_screen_mode;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio;
    SCC_VID_SCREEN_MODE_T       e_scr_mode;
    INT16                       i2_scr_mode;
    UINT16                      ui2_idx;

    /* Get source aspect ratio. */
    e_src_asp_ratio = _nav_screen_mode_get_src_asp_ratio (pt_this->e_focus_tv_win_id);

    if (e_src_asp_ratio == VSH_SRC_ASPECT_RATIO_UNKNOWN)
    {
        pt_this->t_view_hdlr.pf_set_hlt_index(0);

        pt_this->ui2_curr_idx = 0;

        /* Return directly, no further process needed */
        return;
    }
    else
    {
        /* Get current screen mode. */
        i4_ret = a_cfg_av_get (CFG_ID_SCREEN_MODE, & i2_scr_mode);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("[NAV] _screen_mode_refresh_highlight, a_cfg_av_get failed\n"));
        }

        /* Convert to screen mode defined in SCC. */
        e_scr_mode = (SCC_VID_SCREEN_MODE_T) i2_scr_mode;

        /* Check if current screen mode is valid. */
        i4_ret = a_sml_iterate_rec (e_src_asp_ratio,
                                    SML_ITERATE_DIR_THIS,
                                    & e_scr_mode);

        if (i4_ret != SMLR_OK) /* Invalid screen mode? */
        {
            /* Get first screen mode. */
            i4_ret = a_sml_iterate_rec (e_src_asp_ratio,
                                        SML_ITERATE_DIR_FIRST,
                                        & e_scr_mode);
            if (i4_ret != SMLR_OK)
            {
                DBG_ERROR(("[NAV] _screen_mode_refresh_highlight, a_sml_iterate_rec failed\n"));
            }

            /* Set first screen mode to config. */
            i4_ret = a_cfg_av_set (CFG_ID_SCREEN_MODE, (INT16) e_scr_mode);

            if (i4_ret != APP_CFGR_OK)
            {
                DBG_ERROR(("[NAV] _screen_mode_refresh_highlight, a_cfg_av_set failed\n"));
            }

            /* Update config. */
            i4_ret = a_cfg_update_screen_mode_ex();
            if (i4_ret != APP_CFGR_OK)
            {
                DBG_ERROR(("[NAV] _screen_mode_refresh_highlight, a_cfg_av_update failed\n"));
            }
        }
    }

    /* Linear search the e_scr_mode in listbox */
    for (ui2_idx = 0 ; ui2_idx < ui1_g_element_in_listbox ; ui2_idx++)
    {
        if (ui2_idx > 15)
        {
            break;
        }

        if (ag_e_scr_mode_in_listbox[ui2_idx] == e_scr_mode)
        {
            break;
        }
    }

    if (ui2_idx == ui1_g_element_in_listbox)
    {
        DBG_ERROR(("[NAV][SCREEN_MODE] Couldn't find e_scr_fmt in ag_e_scr_mode_in_listbox\n"));
        ui2_idx = 0;
    }

    /* Set the highlight index */
    pt_this->t_view_hdlr.pf_set_hlt_index(ui2_idx);

    pt_this->ui2_curr_idx = ui2_idx;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_stop_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_stop_timer(
                    NAV_SCREEN_MODE_T*                pt_this
                    )
{
    INT32 i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_hide_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop screen_mode::h_hide_timer failed!"));
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_init(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;
    INT32               i4_ret;

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    if (c_handle_valid(pt_this->h_update_ctrl_timer) == TRUE) {
        c_timer_delete(pt_this->h_update_ctrl_timer);
    }

    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->h_update_ctrl_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;
    pt_this->b_is_view_init      = FALSE;
    pt_this->ui4_timeout  = NAV_SCREEN_MODE_AUTO_HIDE_TIMER_DURATION;

    i4_ret = c_timer_create(&(pt_this->h_hide_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = c_timer_create(&(pt_this->h_update_ctrl_timer));
    if (i4_ret != OSR_OK) {
        return NAVR_FAIL;
    }

    /* the view will be inited once the component to be active in order to shrink the memory*/
#if 0
    i4_ret = pt_this->t_view_hdlr.pf_init(
                    pt_this,
                    pt_ctx->t_gui_res.h_canvas,
                    pt_ctx->t_gui_res.i4_x_offset,
                    pt_ctx->t_gui_res.i4_y_offset,
                    nav_screen_mode_custom_get_vid_screen_mode_numbers()      /* Elem Numbers */
                    );
#endif

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_deinit(VOID)
{
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;
    INT32               i4_ret;

    if (c_handle_valid(pt_this->h_update_ctrl_timer) == TRUE) {
        c_timer_delete(pt_this->h_update_ctrl_timer);
    }

    if (c_handle_valid(pt_this->h_hide_timer) == TRUE) {
        c_timer_delete(pt_this->h_hide_timer);
    }

    /* deinit the view*/

    if (pt_this->b_is_view_init == TRUE)
    {
    i4_ret = pt_this->t_view_hdlr.pf_deinit();
    if (i4_ret != NAVR_OK) {
        return NAVR_FAIL;
    }
        else
        {
            pt_this->b_is_view_init = FALSE;
        }
    }

    pt_this->h_update_ctrl_timer = NULL_HANDLE;
    pt_this->h_hide_timer = NULL_HANDLE;
    pt_this->b_is_on      = FALSE;

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_is_key_handler
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static BOOL _nav_screen_mode_is_key_handler(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI) == TRUE) {
        return FALSE;
    }

    return pt_this->t_view_hdlr.pf_is_key_handler(ui4_key_code);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_activate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_activate(
                    NAV_CONTEXT_T*              pt_ctx,
                    UINT32                      ui4_key_code
                    )
{
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;
    INT32               i4_ret;

    /* do the view init*/
    if (pt_this->b_is_view_init == FALSE)
    {
        i4_ret = pt_this->t_view_hdlr.pf_init(
                        pt_this,
                        pt_ctx->t_gui_res.h_canvas,
                        pt_ctx->t_gui_res.i4_x_offset,
                        pt_ctx->t_gui_res.i4_y_offset,
                        nav_screen_mode_custom_get_vid_screen_mode_numbers()      /* Elem Numbers */
                        );

        if (i4_ret != NAVR_OK) {
            return i4_ret;
        }
        else
        {
            pt_this->b_is_view_init = TRUE;
        }
    }

    pt_this->e_focus_tv_win_id = pt_ctx->t_svc_res.e_focus_tv_win_id;

    /* Load messages */
    _nav_screen_mode_view_load_msgs(nav_get_mlm_lang_id());

    /* Set Refreshing Flag */
    pt_this->t_view_hdlr.pf_set_is_refreshing(TRUE);

    /* Refresh the Title text / element text */
    _nav_screen_mode_refresh_list();

    /* Refresh the highlight text */
    _nav_screen_mode_refresh_highlight();

    /* Unset Refreshing Flag */
    pt_this->t_view_hdlr.pf_set_is_refreshing(FALSE);

    i4_ret = pt_this->t_view_hdlr.pf_activate(ui4_key_code);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    /* Enable update */
    pt_this->b_can_update = TRUE;

    nav_screen_mode_reset_timer(pt_this);
    nav_set_component_visible(NAV_COMP_ID_SCREEN_MODE);

    if (pt_this->b_is_on == FALSE)
    {
        pt_this->b_is_on = TRUE;
        //a_tv_net_OSD_appear();

        a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_EXIST);
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_inactivate
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_inactivate(
                    NAV_CONTEXT_T*              pt_ctx
                    )
{

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_handle_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_handle_msg(
                    NAV_CONTEXT_T*              pt_ctx,
                    NAV_UI_MSG_T*               pt_ui_msg,
                    VOID*                       pv_arg1
                    )
{
    INT32               i4_ret;
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;

    switch(pt_ui_msg->e_id)
    {
        case NAV_UI_MSG_NO_SIGNAL:
        case NAV_UI_MSG_LOCKED_INP:
        case NAV_UI_MSG_LOCKED_PROG:
        case NAV_UI_MSG_LOCKED_CH:
        case NAV_UI_MSG_BEFORE_SVC_CHANGE:
        case NAV_UI_MSG_EMPTY_SVL:
        {
            if (pt_this->b_is_on) /* Screen mode is being on. */
            {
                /* Hide screen mode. */
                nav_hide_component(NAV_COMP_ID_SCREEN_MODE);
            }
        }
        break;

        case NAV_UI_MSG_STREAM_NOTIFY:
        {
			UINT8 ui1_cast_tv_status = 0;
			i4_ret = a_cfg_get_cast_tv_status(&ui1_cast_tv_status);

			BOOL  b_enable = TRUE;
			a_cfg_custom_get_wide_mode_enable_change(&b_enable);

            if (pt_this->b_is_on && (ui1_cast_tv_status != APP_CFG_CAST_TV_STATUS_CAST_MODE)&&((b_enable == TRUE))) /* Screen mode is being on. */
            {
                /* Set Refreshing Flag */
                pt_this->t_view_hdlr.pf_set_is_refreshing(TRUE);

                /* Refresh the Title text / element text */
                _nav_screen_mode_refresh_list();

                /* Refresh the highlight text */
                _nav_screen_mode_refresh_highlight();

                /* Unset Refreshing Flag */
                pt_this->t_view_hdlr.pf_set_is_refreshing(FALSE);

                /* Call view_hdlr.pf_activate to repaint */
                pt_this->t_view_hdlr.pf_activate(0);
            }
        }
        break;

        case NAV_UI_MSG_AFTER_TV_MODE_CHANGE:
        {
            i4_ret = a_cfg_update_screen_mode_ex ();
            if (i4_ret != APP_CFGR_OK)
            {
                DBG_ERROR(("<NAV> ERR: a_cfg_update_screen_mode failed = %d\n\r", i4_ret));
            }
        }
        break;

        default:
            break;
    }

    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _nav_screen_mode_hide(
                    VOID
                    )
{
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;

    if (pt_this->b_is_on == FALSE) {
        return NAVR_NO_ACTION;
    }

    pt_this->t_view_hdlr.pf_hide();
    pt_this->b_is_on = FALSE;
    _nav_screen_mode_stop_timer(pt_this);

    /* Return control. */
    if (nav_get_active_component() == NAV_COMP_ID_SCREEN_MODE)
    {
        nav_return_activation(NAV_COMP_ID_SCREEN_MODE);
    }

    //a_tv_net_OSD_disapper();
    a_icl_custom_set_is_ui_popup(ICL_MSGCVT_UI_NOT_EXIST);

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_timeout_to_hide
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_timeout_to_hide(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    nav_hide_component(NAV_COMP_ID_SCREEN_MODE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_hide_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_hide_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_screen_mode_timeout_to_hide, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_timeout_to_update
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_timeout_to_update(
                    VOID*                       pv_tag,
                    VOID*                       pv_tag2,
                    VOID*                       pv_tag3
                    )
{
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;

    pt_this->b_can_update = TRUE;

    if (pt_this->ui2_last_idx != pt_this->ui2_curr_idx)
    {
        nav_screen_mode_ctrl_update_index();
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_update_ctrl_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_update_ctrl_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    nav_request_context_switch(_nav_screen_mode_timeout_to_update, pv_tag, NULL, NULL);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _nav_screen_mode_reset_update_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _nav_screen_mode_reset_update_timer(VOID)
{
    INT32               i4_ret;
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;

    if (c_handle_valid(pt_this->h_update_ctrl_timer) == FALSE) {
        return;
    }

    i4_ret = c_timer_stop(pt_this->h_update_ctrl_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("stop screen_mode::h_update_ctrl_timer failed!"));
    }

    i4_ret = c_timer_start(
                pt_this->h_update_ctrl_timer,
                NAV_SCREEN_MODE_UPDATE_CTRL_TIMER_DURATION,
                X_TIMER_FLAG_ONCE,
                _nav_screen_mode_update_ctrl_timer_nfy,
                pt_this
                );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start screen_mode::h_hide_timer failed!"));
    }

    pt_this->b_can_update = FALSE;
}

/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      nav_screen_mode_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID nav_screen_mode_reset_timer(
                    NAV_SCREEN_MODE_T*                 pt_this
                    )
{
    INT32 i4_ret;

    if (pt_this == NULL)
    {
        pt_this = & t_g_nav_screen_mode;
    }

    _nav_screen_mode_stop_timer(pt_this);

    i4_ret = c_timer_start(
                    pt_this->h_hide_timer,
                    pt_this->ui4_timeout,
                    X_TIMER_FLAG_ONCE,
                    _nav_screen_mode_hide_timer_nfy,
                    pt_this
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("start screen_mode::h_hide_timer failed!"));
    }
}

/*-----------------------------------------------------------------------------
 * Name
 *      nav_screen_mode_is_on
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL nav_screen_mode_is_on(VOID)
{
   NAV_SCREEN_MODE_T*   pt_this = &t_g_nav_screen_mode;

   return pt_this->b_is_on;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: API for view to set the index.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID nav_screen_mode_ctrl_set_index(UINT16       ui2_idx)
{
    NAV_SCREEN_MODE_T*      pt_this = &t_g_nav_screen_mode;

    if (ui2_idx == pt_this->ui2_curr_idx)
    {
        return;
    }

    pt_this->ui2_curr_idx = ui2_idx;

    if (pt_this->b_can_update)
    {
        nav_screen_mode_ctrl_update_index();
    }
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description: API for view to update the index value.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID nav_screen_mode_ctrl_update_index(VOID)
{
    INT32                   i4_ret;
    SCC_VID_SCREEN_MODE_T   e_scr_mode;
    NAV_SCREEN_MODE_T*      pt_this = &t_g_nav_screen_mode;

    _nav_screen_mode_reset_update_timer();

    pt_this->ui2_last_idx = pt_this->ui2_curr_idx;

    /* Get the screen_mode from the bucket */
    e_scr_mode = ag_e_scr_mode_in_listbox[pt_this->ui2_curr_idx];

    /* Set screen mode to config. */
    i4_ret = a_cfg_av_set (CFG_ID_SCREEN_MODE, (INT16) e_scr_mode);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[NAV] a_cfg_av_set failed \n"));
    }

    /* Update config. */
    i4_ret = a_cfg_update_screen_mode_ex();
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[NAV] a_cfg_av_update failed \n"));
    }

    nav_brdcst_msg_from_component (t_g_nav_screen_mode.e_focus_tv_win_id,
                                   NAV_UI_MSG_AFTER_ASPECT_RATIO_CHANGE,
                                   NULL);

    return;
}

/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
INT32 a_nav_screen_mode_get_wide_list(SCC_VID_SCREEN_MODE_T *pae_scr_mode, UINT8 ui1_len)
{
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio;
    SCC_VID_SCREEN_MODE_T       e_scr_mode = 0;
    UINT16                      ui2_elem_num = 0;
    UINT16                      ui2_idx = 0;

    if (NULL == pae_scr_mode || 0 == ui1_len)
    {
        DBG_LOG_PRINT(("[NAV] a_nav_screen_mode_get_wide_list arg invalid!\n"));
        return NAVR_FAIL;
    }

    /* Get the element numbers (1. Get src asp ratio 2. use a_sml API to get num recs) */
    e_src_asp_ratio = _nav_screen_mode_get_src_asp_ratio (TV_WIN_ID_MAIN);

    /* Determine the element numbers */
    a_sml_get_num_rec(e_src_asp_ratio, (UINT8*) &ui2_elem_num);

    if (ui2_elem_num == 0)
    {
        ui2_elem_num = 1;   /* One for "Not Adjustable" */
    }
    else if (ui2_elem_num > 16)
    {
        ui2_elem_num = 16;
    }

    /* Get first screen mode. */
    a_sml_iterate_rec (e_src_asp_ratio,
                       SML_ITERATE_DIR_FIRST,
                       & e_scr_mode);
    pae_scr_mode[0] = e_scr_mode;

    for (ui2_idx = 1 ; ui2_idx < ui2_elem_num && ui2_idx < ui1_len; ui2_idx++)
    {
        a_sml_iterate_rec (e_src_asp_ratio,
                           SML_ITERATE_DIR_NEXT,
                           & e_scr_mode);

        pae_scr_mode[ui2_idx] = e_scr_mode;
    }

    return ui2_idx;
}
INT32 a_nav_screen_mode_get_cur_mode(SCC_VID_SCREEN_MODE_T *pe_scr_mode)
{
    INT32                       i4_ret = NAVR_OK;
    INT16                       i2_scr_mode = 0;
    SCC_VID_SCREEN_MODE_T       e_scr_mode;
    VSH_SRC_ASPECT_RATIO_T      e_src_asp_ratio;

    /* Get current screen mode. */
    i4_ret = a_cfg_av_get (CFG_ID_SCREEN_MODE, & i2_scr_mode);
    if (i4_ret != APP_CFGR_OK)
    {
        DBG_ERROR(("[NAV] a_nav_screen_mode_get_cur_mode, a_cfg_av_get failed\n"));
    }

    /* Convert to screen mode defined in SCC. */
    e_scr_mode = (SCC_VID_SCREEN_MODE_T) i2_scr_mode;

    e_src_asp_ratio = _nav_screen_mode_get_src_asp_ratio(TV_WIN_ID_MAIN);

    /* Check if current screen mode is valid. */
    i4_ret = a_sml_iterate_rec (e_src_asp_ratio,
                                SML_ITERATE_DIR_THIS,
                                & e_scr_mode);

    if (i4_ret != SMLR_OK) /* Invalid screen mode? */
    {
        /* Get first screen mode. */
        i4_ret = a_sml_iterate_rec (e_src_asp_ratio,
                                    SML_ITERATE_DIR_FIRST,
                                    & e_scr_mode);
        if (i4_ret != SMLR_OK)
        {
            DBG_ERROR(("[NAV] a_nav_screen_mode_get_cur_mode, a_sml_iterate_rec failed\n"));
        }

        /* Set first screen mode to config. */
        i4_ret = a_cfg_av_set (CFG_ID_SCREEN_MODE, (INT16) e_scr_mode);

        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("[NAV] a_nav_screen_mode_get_cur_mode, a_cfg_av_set failed\n"));
        }

        /* Update config. */
        i4_ret = a_cfg_update_screen_mode_ex();
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("[NAV] a_nav_screen_mode_get_cur_mode, a_cfg_av_update failed\n"));
        }
    }

    *pe_scr_mode = e_scr_mode;

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      a_nav_screen_mode_register
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 a_nav_screen_mode_register(
                    NAV_SCREEN_MODE_VIEW_HDLR_T*      pt_view_hdlr,
                    NAV_SCREEN_MODE_STYLE             e_style
                    )
{
    NAV_SCREEN_MODE_T*  pt_this = &t_g_nav_screen_mode;
    NAV_COMP_T          t_comp;
    INT32               i4_ret;

    NAV_DEBUG_ASPECT_RADIO( DBG_LOG_PRINT(("[NAV][ASPECT]{%s,%d} \n", __FUNCTION__, __LINE__ )); );

    c_memset( &t_comp, 0, sizeof(NAV_COMP_T) );

    /* NAV_COMP_ID_SCREEN_MODE */
    t_comp.pf_init           = _nav_screen_mode_init;
    t_comp.pf_deinit         = _nav_screen_mode_deinit;
    t_comp.pf_is_key_handler = _nav_screen_mode_is_key_handler;
    t_comp.pf_activate       = _nav_screen_mode_activate;
    t_comp.pf_inactivate     = _nav_screen_mode_inactivate;
    t_comp.pf_hide           = _nav_screen_mode_hide;
    t_comp.pf_handle_msg     = _nav_screen_mode_handle_msg;

    i4_ret = nav_register_component(NAV_COMP_ID_SCREEN_MODE, &t_comp, COMP_EXC_SET_SCREEN_MODE);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    if (pt_view_hdlr == NULL)
    {
        if(e_style == NAV_SCREEN_MODE_STYLE_SINGLE_SELECT_LIST)
        {
            nav_screen_mode_view_register_single_select_list_hdlr(&pt_this->t_view_hdlr);
        }
        else
        {    /* Default */
            nav_screen_mode_view_register_single_select_list_hdlr(&pt_this->t_view_hdlr);
        }
    }
    else {
        pt_this->t_view_hdlr = *pt_view_hdlr;
    }
#ifdef CLI_SUPPORT
    nav_scrn_mode_cli_register_cmd_tbl();
#endif

    return NAVR_OK;
}

BOOL a_screen_mode_is_enable(VOID)
{
     TV_WIN_ID_T    e_tv_win_id;

    if (nav_is_under_ex_ctrl(NAV_EXTERNAL_CTRL_RULE_NO_ANY_UI) == TRUE) {
        return FALSE;
    }

    nav_get_focus_id(&e_tv_win_id);
    if (_nav_screen_mode_get_src_asp_ratio(e_tv_win_id) == VSH_SRC_ASPECT_RATIO_UNKNOWN) {
        return FALSE;
    }
    return TRUE;
}

#endif /* APP_537X_SUPPORT */

