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
 * $RCSfile: pop_params.c,v $
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
#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))
#include "res/nav/pop/pop_custom.h"
#include "nav/pop/pop.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_colors.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
/* 0. basic parameters */
ASPECT_RATIO_T t_screen_aspect_ratio = {16, 9}; /* if set to {0, 0}, it will change to {16, 9}*/
ASPECT_RATIO_T t_pip_aspect_ratio    = {16, 9}; /* if set to {0, 0}, it will change to {16, 9}*/
ASPECT_RATIO_T t_pop_aspect_ratio    = {16, 9}; /* if set to {?, 0}, it will set the height = VSH_REGION_MAX_HEIGHT*/

/* 1. parameters for PIP */
/* 1.1 pip main window's size */
VSH_REGION_INFO_T t_g_pip_main_region = {0, 0, VSH_REGION_MAX_WIDTH, VSH_REGION_MAX_HEIGHT};

/* 1.2 pip sub windows' position */
PIP_SUB_POS_T at_g_pip_sub_positions[] = {
    /*id                           name key                 x                                                 y                                                   (x, y) position description                      */
    {TV_PIP_SUB_POS_RIGHT_BOTTOM , MLM_NAV_KEY_PIP_POS_RB, {VSH_REGION_MAX_WIDTH - VSH_REGION_MAX_WIDTH / 20, VSH_REGION_MAX_HEIGHT - VSH_REGION_MAX_HEIGHT / 20, X_POS_INFO_RIGHT_EDGE | Y_POS_INFO_BOTTOM_EDGE}}, /* right-bottom  */
    {TV_PIP_SUB_POS_LEFT_BOTTOM  , MLM_NAV_KEY_PIP_POS_LB, {VSH_REGION_MAX_WIDTH / 20                       , VSH_REGION_MAX_HEIGHT - VSH_REGION_MAX_HEIGHT / 20, X_POS_INFO_LEFT_EDGE  | Y_POS_INFO_BOTTOM_EDGE}}, /* left-bottom   */
    {TV_PIP_SUB_POS_LEFT_TOP     , MLM_NAV_KEY_PIP_POS_LT, {VSH_REGION_MAX_WIDTH / 20                       , VSH_REGION_MAX_HEIGHT / 20                        , X_POS_INFO_LEFT_EDGE  | Y_POS_INFO_TOP_EDGE   }}, /* left-top      */
    {TV_PIP_SUB_POS_RIGHT_TOP    , MLM_NAV_KEY_PIP_POS_RT, {VSH_REGION_MAX_WIDTH - VSH_REGION_MAX_WIDTH / 20, VSH_REGION_MAX_HEIGHT / 20                        , X_POS_INFO_RIGHT_EDGE | Y_POS_INFO_TOP_EDGE   }}, /* right-top     */

    /* DO NOT REMOVE THIS LINE */
    {TV_PIP_SUB_POS_UNKNOWN      , INVALID_PIP_MLM_KEY, VIDEO_REGION_POS_END}
    };
UINT8 ui1_g_num_of_pip_sub_position = (UINT8)(sizeof(at_g_pip_sub_positions)/sizeof(at_g_pip_sub_positions[0]) - 1);

/* 1.3 pip sub window's width */
PIP_SUB_SIZE_T  at_g_pip_sub_sizes[] = {
    /*id                        name                         width                  */
    {TV_PIP_SUB_SIZE_SMALL  ,   MLM_NAV_KEY_PIP_SIZE_SMALL,  VSH_REGION_MAX_WIDTH * 10 / 50},
    {TV_PIP_SUB_SIZE_MEDIUM ,   MLM_NAV_KEY_PIP_SIZE_MEDIUM, VSH_REGION_MAX_WIDTH * 10 / 40},
    {TV_PIP_SUB_SIZE_LARGE  ,   MLM_NAV_KEY_PIP_SIZE_LARGE,  VSH_REGION_MAX_WIDTH * 10 / 25},

    /* DO NOT REMOVE THIS LINE */
    {TV_PIP_SUB_SIZE_UNKNOWN,   INVALID_PIP_MLM_KEY,    VIDEO_REGION_SIZE_END}
    };

UINT8 ui1_g_num_of_pip_sub_size = (UINT8)(sizeof(at_g_pip_sub_sizes)/sizeof(at_g_pip_sub_sizes[0]) - 1);

/* 2. parameters for POP */
/* 2.1 pip main windows region information */
POP_REGION_INFO_T t_g_pop_main_region_info = {
    {{0, VSH_REGION_MAX_HEIGHT / 2, X_POS_INFO_LEFT_EDGE | Y_POS_INFO_MIDDLE}, VSH_REGION_MAX_WIDTH * 1 / 2}, /* center */
    VSH_REGION_MAX_WIDTH / 100, /* step size, min = 1 */
    0,  /* max step count to increase */
    0   /* max step count to decrease */
    };
/* 2.2 pip main windows region information */
POP_REGION_INFO_T t_g_pop_sub_region_info = {
    {{VSH_REGION_MAX_WIDTH, VSH_REGION_MAX_HEIGHT / 2, X_POS_INFO_RIGHT_EDGE | Y_POS_INFO_MIDDLE}, VSH_REGION_MAX_WIDTH * 1 / 2}, /* center */
    VSH_REGION_MAX_WIDTH / 100, /* step size,  min = 1 */
    0,  /* max step count to increase */
    0   /* max step count to decrease */
    };

/* 3. custom key mapping table */
POP_CUSTOM_KEY_MAP t_g_pop_custom_key_map_table[] = {
#if (defined(APP_PIP_POP_CTRL) && (!defined(APP_VOG_SUPPORT)))
    {BTN_CURSOR_LEFT,  MAKE_BIT_MASK_8(TV_MODE_TYPE_PIP),                                   CUSTOM_BTN_PIP_PREV_POS  },
    {BTN_CURSOR_RIGHT, MAKE_BIT_MASK_8(TV_MODE_TYPE_PIP),                                   CUSTOM_BTN_PIP_NEXT_POS  },
/* in order to not conflict with the cursor up/down as program details is over 1 pages.
    {BTN_CURSOR_UP,    MAKE_BIT_MASK_8(TV_MODE_TYPE_PIP)                                  , CUSTOM_BTN_PIP_NEXT_SIZE },
    {BTN_CURSOR_UP,    MAKE_BIT_MASK_8(TV_MODE_TYPE_POP)                                  , CUSTOM_BTN_POP_NEXT_SIZE },
    {BTN_CURSOR_DOWN,  MAKE_BIT_MASK_8(TV_MODE_TYPE_PIP)                                  , CUSTOM_BTN_PIP_PREV_SIZE },
    {BTN_CURSOR_DOWN,  MAKE_BIT_MASK_8(TV_MODE_TYPE_POP)                                  , CUSTOM_BTN_POP_PREV_SIZE },
*/
#else
    {BTN_SWAP,         MAKE_BIT_MASK_8(TV_MODE_TYPE_PIP)                                  , CUSTOM_BTN_NULL          },
/* in order to not conflict with the cursor up/down as program details is over 1 pages.
    {BTN_CURSOR_UP,    MAKE_BIT_MASK_8(TV_MODE_TYPE_PIP)                                  , CUSTOM_BTN_PIP_NEXT_SIZE },
    {BTN_CURSOR_DOWN,  MAKE_BIT_MASK_8(TV_MODE_TYPE_PIP)                                  , CUSTOM_BTN_PIP_PREV_SIZE },
*/
#endif
    /* DO NOT REMOVE THIS LINE */
    POP_CUSTOM_KEY_MAP_END
    };

/* 4. supported PIP/POP mode transition table */
POP_TV_MODE_TRAN_MAP t_g_pop_tv_mode_tran_map_table[] = {
#if (defined(APP_PIP_POP_CTRL) && (!defined(APP_VOG_SUPPORT)))
    {TV_MODE_TYPE_NORMAL,           TV_MODE_TYPE_PIP},
    {TV_MODE_TYPE_PIP,              TV_MODE_TYPE_POP},
    {TV_MODE_TYPE_POP,              TV_MODE_TYPE_NORMAL},
    {TV_MODE_TYPE_LAST_VALID_ENTRY, TV_MODE_TYPE_PIP},
#else
    {TV_MODE_TYPE_NORMAL,           TV_MODE_TYPE_PIP},
    {TV_MODE_TYPE_PIP,              TV_MODE_TYPE_NORMAL},
#endif
    /* DO NOT REMOVE THIS LINE */
    POP_TV_MODE_TRAN_MAP_END
    };

/* 5 win frame color */
const GL_COLOR_T  t_g_pop_win_focus_color = NAV_COLOR_POP_FOCUS;
const GL_COLOR_T  t_g_pop_win_blur_color  = NAV_COLOR_POP_BLUR;
const WGL_INSET_T t_g_pop_win_focus_bdr   = {0, 0, 0, 0};
const WGL_INSET_T t_g_pop_win_blur_bdr    = {0, 0, 0, 0};
#endif /*APP_PIP_POP_CTRL*/
