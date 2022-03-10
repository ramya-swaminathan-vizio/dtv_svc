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
 * $RCSfile: pop_custom.c,v $
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
#include "u_irrc_btn_def.h"

#include "res/nav/nav_variant.h"
#include "res/nav/pop/pop_custom.h"
#include "nav/pop/pop.h"
#include "res/nav/nav_mlm.h"
#include "app_util/a_tv.h"
#include "res/nav/nav_dbg.h"

#if (defined(APP_PIP_POP_CTRL) || defined (APP_VOG_SUPPORT))
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define INVALID_SIZE_IDX        (0xFF)
#define INVALID_POS_IDX         (0xFF)
#define INVALID_POP_IDX         (0xFF)
/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
/* public global variable */
extern ASPECT_RATIO_T       t_screen_aspect_ratio;
extern ASPECT_RATIO_T       t_pip_aspect_ratio;
extern ASPECT_RATIO_T       t_pop_aspect_ratio;

extern VSH_REGION_INFO_T    t_g_pip_main_region;
extern PIP_SUB_POS_T        at_g_pip_sub_positions[];
extern PIP_SUB_SIZE_T       at_g_pip_sub_sizes[];

extern POP_REGION_INFO_T    t_g_pop_main_region_info;
extern POP_REGION_INFO_T    t_g_pop_sub_region_info;
extern POP_CUSTOM_KEY_MAP   t_g_pop_custom_key_map_table[];
extern POP_TV_MODE_TRAN_MAP t_g_pop_tv_mode_tran_map_table[];
extern UINT8                ui1_g_num_of_pip_sub_position;
extern UINT8                ui1_g_num_of_pip_sub_size;

/* private global variable */
static UINT16 ui2_g_pop_main_crnt_step      = 0;
static BOOL   b_g_pop_main_is_positive_step = TRUE;
static UINT16 ui2_g_pop_sub_crnt_step       = 0;
static BOOL   b_g_pop_sub_is_positive_step  = TRUE;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_last_pos_idx
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static UINT8 _pop_get_last_pos_idx(
                    VOID
                    )
{
#if 0
    static UINT8 ui1_g_last_pos_idx = INVALID_POS_IDX;

    if (ui1_g_last_pos_idx == INVALID_POS_IDX) {
        ui1_g_last_pos_idx = 0;

        while(!IS_VIDEO_REGION_POS_END(&(at_g_pip_sub_positions[ui1_g_last_pos_idx].t_pos))) {
            if (ui1_g_last_pos_idx == INVALID_POS_IDX) {
                ui1_g_last_pos_idx = 0;
                break;
            }
            ui1_g_last_pos_idx++;
        }
        if (ui1_g_last_pos_idx != 0) {
            ui1_g_last_pos_idx -= 1;
        }
    }

    return ui1_g_last_pos_idx;
#else
    return (UINT8)(ui1_g_num_of_pip_sub_position-1);
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_last_size_idx
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static UINT8 _pop_get_last_size_idx(
                    VOID
                    )
{
#if 0
    static UINT8 ui1_g_last_size_idx = INVALID_SIZE_IDX;

    if (ui1_g_last_size_idx == INVALID_SIZE_IDX) {
        ui1_g_last_size_idx = 0;

        while(!IS_VIDEO_REGION_SIZE_END(at_g_pip_sub_sizes[ui1_g_last_size_idx].ui4_width)) {
            if (ui1_g_last_size_idx == INVALID_SIZE_IDX) {
                ui1_g_last_size_idx = 0;
                break;
            }
            ui1_g_last_size_idx++;
        }

        if (ui1_g_last_size_idx != 0) {
            ui1_g_last_size_idx -= 1;
        }
    }

    return ui1_g_last_size_idx;
#else
    return (UINT8)(ui1_g_num_of_pip_sub_size-1);
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_pos_idx_by_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_get_pos_idx_by_id(
                    TV_PIP_SUB_POSITION_T       e_pos_id,
                    UINT8*                      pui1_idx
                    )
{
    UINT8 ui1_idx = 0;

    while(!IS_VIDEO_REGION_POS_END(&(at_g_pip_sub_positions[ui1_idx].t_pos))) {
        if (e_pos_id == at_g_pip_sub_positions[ui1_idx].e_id) {
            *pui1_idx = ui1_idx;
            return NAVR_OK;
        }
        ui1_idx++;
    }

    return NAVR_NOT_EXIST;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_size_idx_by_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pop_get_size_idx_by_id(
                    TV_PIP_SUB_SIZE_T           e_size_id,
                    UINT8*                      pui1_idx
                    )
{
    UINT8 ui1_idx = 0;

    while(!IS_VIDEO_REGION_SIZE_END(at_g_pip_sub_sizes[ui1_idx].ui4_width)) {
        if (e_size_id == at_g_pip_sub_sizes[ui1_idx].e_id) {
            *pui1_idx = ui1_idx;
            return NAVR_OK;
        }
        ui1_idx++;
    }

    return NAVR_NOT_EXIST;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_pos_idx
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static UINT8 _pop_get_pos_idx(
                    WIN_POS_DIR_T               e_pos_dir,
                    UINT8                       ui1_pos_idx
                    )
{
    switch(e_pos_dir) {
    case WIN_POS_DIR_NEXT:
        ui1_pos_idx += 1;
        if (IS_VIDEO_REGION_POS_END(&(at_g_pip_sub_positions[ui1_pos_idx].t_pos))) {
            ui1_pos_idx = 0;
        }
        break;
    case WIN_POS_DIR_PREV:
        ui1_pos_idx = ui1_pos_idx == 0 ? _pop_get_last_pos_idx() : ((UINT8)(ui1_pos_idx-1));
        break;
    default:
        break;
    }
    return ui1_pos_idx;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_size_idx
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static UINT8 _pop_get_size_idx(
                    WIN_SIZE_DIR_T              e_size_dir,
                    UINT8                       ui1_size_idx
                    )
{
    switch(e_size_dir) {
    case WIN_SIZE_DIR_NEXT:
        ui1_size_idx += 1;
        if (IS_VIDEO_REGION_SIZE_END(at_g_pip_sub_sizes[ui1_size_idx].ui4_width)) {
            ui1_size_idx = 0;
        }
        break;
    case WIN_SIZE_DIR_PREV:
        ui1_size_idx = (ui1_size_idx == 0) ? _pop_get_last_size_idx() : ((UINT8)(ui1_size_idx-1));
        break;
    default:
        break;
    }
    return ui1_size_idx;
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_pip_region_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_get_region_info(
                    VIDEO_REGION_POS_T*         pt_pos,
                    VSH_REGION_INFO_T*          pt_region
                    )
{
    switch(pt_pos->ui1_pos_info & X_POS_INFO_MASK) {
    case X_POS_INFO_RIGHT_EDGE:
        pt_region->ui4_x -= pt_region->ui4_width;
        break;
    case X_POS_INFO_CENTER:
        pt_region->ui4_x -= (pt_region->ui4_width/2);
        break;
    case X_POS_INFO_LEFT_EDGE:
    default:
        break;
    }

    switch(pt_pos->ui1_pos_info & Y_POS_INFO_MASK) {
    case Y_POS_INFO_BOTTOM_EDGE:
        pt_region->ui4_y -= pt_region->ui4_height;
        break;
    case Y_POS_INFO_MIDDLE:
        pt_region->ui4_y -= (pt_region->ui4_height/2);
        break;
    case Y_POS_INFO_TOP_EDGE:
    default:
        break;
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_pop_region_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_get_pop_region_info(
                    WIN_POS_DIR_T               e_pos_dir,
                    POP_REGION_INFO_T*          pt_region_info,
                    UINT16*                     pui2_crnt_step,
                    BOOL*                       pb_is_positive_step,
                    VSH_REGION_INFO_T*          pt_region
                    )
{
    switch(e_pos_dir) {
    case WIN_POS_DIR_NEXT:
        if ((*pb_is_positive_step) == FALSE) {
            if ((*pui2_crnt_step) > 0) {
                (*pui2_crnt_step) -= 1;
            } else {
                (*pb_is_positive_step) = TRUE;
            }
        }

        if ((*pb_is_positive_step) == TRUE) {
            if ((*pui2_crnt_step) < pt_region_info->ui2_num_of_increase_step) {
                (*pui2_crnt_step) += 1;
            }
        }
        break;
    case WIN_POS_DIR_PREV:
        if ((*pb_is_positive_step) == TRUE) {
            if ((*pui2_crnt_step) > 0) {
                (*pui2_crnt_step) -= 1;
            } else {
                (*pb_is_positive_step) = FALSE;
            }
        }

        if ((*pb_is_positive_step) == FALSE) {
            if ((*pui2_crnt_step) < pt_region_info->ui2_num_of_decrease_step) {
                (*pui2_crnt_step) += 1;
            }
        }
        break;
    default:
        break;
    }

    if ((*pb_is_positive_step) == TRUE) {
        pt_region->ui4_width = pt_region_info->t_center_region.ui4_width + pt_region_info->ui4_step_width * (*pui2_crnt_step);
    } else {
        pt_region->ui4_width = pt_region_info->t_center_region.ui4_width - pt_region_info->ui4_step_width * (*pui2_crnt_step);
    }

    if (t_screen_aspect_ratio.ui1_width == 0 || t_screen_aspect_ratio.ui1_height == 0) {
        t_screen_aspect_ratio.ui1_width  = 16;
        t_screen_aspect_ratio.ui1_height = 9;
    }

    if (t_pop_aspect_ratio.ui1_height == 0) {
        pt_region->ui4_height = VSH_REGION_MAX_HEIGHT;
    } else {
        pt_region->ui4_height = GET_W_FROM_H(pt_region->ui4_width, &t_screen_aspect_ratio, &t_pop_aspect_ratio);
    }

    pt_region->ui4_x = pt_region_info->t_center_region.t_pos.ui4_x;
    pt_region->ui4_y = pt_region_info->t_center_region.t_pos.ui4_y;

    _pop_get_region_info(&pt_region_info->t_center_region.t_pos, pt_region);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _pop_get_pip_region_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _pop_get_pip_region_info(
                    VIDEO_REGION_POS_T*         pt_pos,
                    UINT32                      ui4_width,
                    VSH_REGION_INFO_T*          pt_region
                    )
{
    if (t_screen_aspect_ratio.ui1_width == 0 || t_screen_aspect_ratio.ui1_height == 0) {
        t_screen_aspect_ratio.ui1_width  = 16;
        t_screen_aspect_ratio.ui1_height = 9;
    }

    if (t_pip_aspect_ratio.ui1_width == 0 || t_pip_aspect_ratio.ui1_height == 0) {
        t_pip_aspect_ratio.ui1_width  = 16;
        t_pip_aspect_ratio.ui1_height = 9;
    }

    pt_region->ui4_width  = ui4_width;
    pt_region->ui4_height = GET_W_FROM_H(pt_region->ui4_width, &t_screen_aspect_ratio, &t_pip_aspect_ratio);
    pt_region->ui4_x      = pt_pos->ui4_x;
    pt_region->ui4_y      = pt_pos->ui4_y;

    _pop_get_region_info(pt_pos, pt_region);
}
/*-----------------------------------------------------------------------------
 * public methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      pop_custom_rcu_key_pre_handler
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
VOID pop_custom_rcu_key_pre_handler(
                    UINT32*                     pui4_key_code
                    )
{
    POP_CUSTOM_KEY_MAP* pt_key_map = NULL;
    TV_MODE_T           e_tv_mode;
    INT32               i4_ret;

    i4_ret = nav_get_tv_mode(&e_tv_mode);
    if (i4_ret != NAVR_OK) {
        return;
    }

    for (pt_key_map = &t_g_pop_custom_key_map_table[0]; !IS_POP_CUSTOM_KEY_MAP_END(pt_key_map); pt_key_map++) {
        if (pt_key_map->ui4_original_key == (*pui4_key_code)
                && (pt_key_map->ui1_tv_mode_bits & MAKE_BIT_MASK_8(e_tv_mode)) > 0) {
            *pui4_key_code = pt_key_map->ui4_mapped_key;
            break;
        }
    }
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_next_tv_mode
 * Description
 * Input arguments
 * Output arguments
 *      None
 * Returns
 *      None
 *---------------------------------------------------------------------------*/
TV_MODE_T pop_get_next_tv_mode(
                    TV_MODE_T                   e_crnt_mode
                    )
{
    POP_TV_MODE_TRAN_MAP* pt_map = NULL;

    for (pt_map = &t_g_pop_tv_mode_tran_map_table[0]; !IS_POP_TV_MODE_TRAN_MAP_END(pt_map); pt_map++) {
        if (pt_map->e_crnt_mode == e_crnt_mode) {
            return pt_map->e_next_mode;
        }
    }

    return t_g_pop_tv_mode_tran_map_table[0].e_next_mode;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_get_pop_region_infos
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pop_get_pop_region_infos(
                    WIN_POS_DIR_T               e_pos_dir,
                    VSH_REGION_INFO_T*          pt_main_region,
                    VSH_REGION_INFO_T*          pt_sub_region
                    )
{
    UINT16 ui2_pop_main_crnt_step = ui2_g_pop_main_crnt_step;
    UINT16 ui2_pop_sub_crnt_step  = ui2_g_pop_sub_crnt_step;
    BOOL   b_main_step_changed    = FALSE;
    BOOL   b_sub_step_changed     = FALSE;

    if (pt_main_region == NULL || pt_sub_region == NULL) {
        return NAVR_INV_ARG;
    }

    /* get main's step information */
    _pop_get_pop_region_info(
                    e_pos_dir,
                    &t_g_pop_main_region_info,
                    &ui2_pop_main_crnt_step,
                    &b_g_pop_main_is_positive_step,
                    pt_main_region
                    );
    if (ui2_pop_main_crnt_step != ui2_g_pop_main_crnt_step) {
        ui2_g_pop_main_crnt_step = ui2_pop_main_crnt_step;
        b_main_step_changed      = TRUE;
    } else {
        b_main_step_changed      = FALSE;
    }

    if (e_pos_dir == WIN_POS_DIR_NEXT) {
        e_pos_dir = WIN_POS_DIR_PREV;
    } else if (e_pos_dir == WIN_POS_DIR_PREV) {
        e_pos_dir = WIN_POS_DIR_NEXT;
    }

    /* get sub's step information */
    _pop_get_pop_region_info(
                    e_pos_dir,
                    &t_g_pop_sub_region_info,
                    &ui2_pop_sub_crnt_step,
                    &b_g_pop_sub_is_positive_step,
                    pt_sub_region
                    );
    if (ui2_pop_sub_crnt_step != ui2_g_pop_sub_crnt_step) {
        ui2_g_pop_sub_crnt_step = ui2_pop_sub_crnt_step;
        b_sub_step_changed      = TRUE;
    } else {
        b_sub_step_changed      = FALSE;
    }

    return (b_main_step_changed == FALSE && b_sub_step_changed == FALSE) ? NAVR_NO_ACTION : NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_get_pip_sub_region_info
 * Description
 *      This API is used to update and get the current SUB's position and size indexes]
 *      and it also presist these indexes into storage
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pop_get_pip_sub_region_info(
                    WIN_POS_DIR_T           e_pos_dir,
                    WIN_SIZE_DIR_T          e_size_dir,
                    VSH_REGION_INFO_T*      pt_region_info
                    )
{
#ifdef APP_NAV_LISTEN_PIP_SUB_POS_SIZE_CFG_CHANGE
    TV_PIP_SUB_POSITION_T e_pos_id;
    TV_PIP_SUB_SIZE_T     e_size_id;
    UINT8                 ui1_pos_idx;
    UINT8                 ui1_size_idx;
    INT32                 i4_ret;

    if (pt_region_info == NULL) {
        return NAVR_INV_ARG;
    }

    i4_ret = a_tv_get_pip_sub_position(&e_pos_id);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = a_tv_get_pip_sub_size(&e_size_id);
    if (i4_ret != TVR_OK) {
        return NAVR_FAIL;
    }

    i4_ret = _pop_get_pos_idx_by_id(e_pos_id, &ui1_pos_idx);
    if (i4_ret != NAVR_OK) {
        ui1_pos_idx = 0;
    }

    i4_ret = _pop_get_size_idx_by_id(e_size_id, &ui1_size_idx);
    if (i4_ret != NAVR_OK) {
         ui1_size_idx = 0;
    }

    ui1_pos_idx  = _pop_get_pos_idx(e_pos_dir, ui1_pos_idx);
    ui1_size_idx = _pop_get_size_idx(e_size_dir, ui1_size_idx);

    if (e_pos_dir != WIN_POS_DIR_CRNT) {
        i4_ret = a_tv_set_pip_sub_position(at_g_pip_sub_positions[ui1_pos_idx].e_id);
        if (i4_ret != TVR_OK) {
            return NAVR_FAIL;
        }
    }

    if (e_size_dir != WIN_SIZE_DIR_CRNT) {
        i4_ret = a_tv_set_pip_sub_size(at_g_pip_sub_sizes[ui1_size_idx].e_id);
        if (i4_ret != TVR_OK) {
            return NAVR_FAIL;
        }
    }

    _pop_get_pip_region_info(
                    &(at_g_pip_sub_positions[ui1_pos_idx].t_pos),
                    at_g_pip_sub_sizes[ui1_size_idx].ui4_width,
                    pt_region_info
                    );
    return NAVR_OK;
#else
	static UINT8 ui1_g_crnt_pip_sub_pos_idx  = 0;
	static UINT8 ui1_g_crnt_pip_sub_size_idx = 0;

	if (pt_region_info == NULL) {
        return NAVR_INV_ARG;
    }

	ui1_g_crnt_pip_sub_pos_idx  = _pop_get_pos_idx(e_pos_dir, ui1_g_crnt_pip_sub_pos_idx);
    ui1_g_crnt_pip_sub_size_idx = _pop_get_size_idx(e_size_dir, ui1_g_crnt_pip_sub_size_idx);

	_pop_get_pip_region_info(
                    &(at_g_pip_sub_positions[ui1_g_crnt_pip_sub_pos_idx].t_pos),
                    at_g_pip_sub_sizes[ui1_g_crnt_pip_sub_size_idx].ui4_width,
                    pt_region_info
                    );
    return NAVR_OK;
#endif
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_get_pip_sub_region_info_by_id
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pop_get_pip_sub_region_info_by_id(
                    TV_PIP_SUB_POSITION_T   e_pos_id,
                    TV_PIP_SUB_SIZE_T       e_size_id,
                    VSH_REGION_INFO_T*      pt_region_info
                    )
{
    UINT8 ui1_pos_idx  = 0;
    UINT8 ui1_size_idx = 0;
    INT32 i4_ret;

    if (pt_region_info == NULL) {
        return NAVR_INV_ARG;
    }

    i4_ret = _pop_get_pos_idx_by_id(e_pos_id, &ui1_pos_idx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    i4_ret = _pop_get_size_idx_by_id(e_size_id, &ui1_size_idx);
    if (i4_ret != NAVR_OK) {
        return i4_ret;
    }

    _pop_get_pip_region_info(
                    &(at_g_pip_sub_positions[ui1_pos_idx].t_pos),
                    at_g_pip_sub_sizes[ui1_size_idx].ui4_width,
                    pt_region_info
                    );
    return NAVR_OK;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pop_get_pip_main_region_info
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pop_get_pip_main_region_info(
                    VSH_REGION_INFO_T*          pt_region_info
                    )
{
    if (pt_region_info == NULL) {
        return NAVR_INV_ARG;
    }

    *pt_region_info = t_g_pip_main_region;
    return NAVR_OK;
}
#ifdef APP_PIP_POP_DISP_NO_VIDEO_REASON
/*----------------------------------------------------------------------------
 * Name: pop_view_init_reason_msg_rc
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
INT32 pop_view_init_reason_msg_rc(
                    POP_VIEW_REASON_MSG_RC_T*   pt_rc
                    )
{
    static WGL_FONT_INFO_T t_g_pip_main_font = {FE_FNT_SIZE_SMALL, FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_BIG};
    static WGL_FONT_INFO_T t_g_pip_sub_font  = {FE_FNT_SIZE_SMALL, FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
    static WGL_FONT_INFO_T t_g_pop_main_font = {FE_FNT_SIZE_LARGE, FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};
    static WGL_FONT_INFO_T t_g_pop_sub_font  = {FE_FNT_SIZE_LARGE, FE_FNT_STYLE_REGULAR, FE_CMAP_ENC_UNICODE, NAV_FONT_NORMAL};

    pt_rc->pt_pip_fonts[TV_WIN_ID_MAIN] = &t_g_pip_main_font;
    pt_rc->pt_pip_fonts[TV_WIN_ID_SUB]  = &t_g_pip_sub_font;
    pt_rc->pt_pop_fonts[TV_WIN_ID_MAIN] = &t_g_pop_main_font;
    pt_rc->pt_pop_fonts[TV_WIN_ID_SUB]  = &t_g_pop_sub_font;

    SET_COLOR(&pt_rc->t_colors[TV_WIN_ID_MAIN], 0xff, 0xff, 0xff, 0xff); /* white */
    SET_COLOR(&pt_rc->t_colors[TV_WIN_ID_SUB],  0xff, 0xff, 0xff, 0xff); /* white */

    return NAVR_OK;
}
/*----------------------------------------------------------------------------
 * Name: pop_view_deinit_msg_rc
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
INT32 pop_view_deinit_reason_msg_rc(
                    POP_VIEW_REASON_MSG_RC_T*   pt_rc
                    )
{
    return NAVR_OK;
}
#endif
/*-----------------------------------------------------------------------------
 * exported methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: a_tv_get_pip_sub_position_display_name
 *
 * Description:
 *      return the PIP sub window position name
 * Inputs:
 *      e_pos_id        the pip sub windows's position id
 * Outputs:
 *      -
 * Returns:
 *      UTF16_T*        the pip sub position name
 ----------------------------------------------------------------------------*/
UTF16_T* a_tv_get_pip_sub_position_display_name(
                    TV_PIP_SUB_POSITION_T       e_pos_id
                    )
{
    UINT8 ui1_idx = 0;

    for (ui1_idx = 0; !IS_VIDEO_REGION_POS_END(&(at_g_pip_sub_positions[ui1_idx].t_pos)); ui1_idx++) {
        if (at_g_pip_sub_positions[ui1_idx].e_id != e_pos_id) {
            continue;
        }

        if (at_g_pip_sub_positions[ui1_idx].ui2_mlm_key == INVALID_PIP_MLM_KEY) {
            return NULL;
        } else {
            return MLM_NAV_TEXT(nav_get_mlm_lang_id(), at_g_pip_sub_positions[ui1_idx].ui2_mlm_key);
        }
    }
    return NULL;
}
/*----------------------------------------------------------------------------
 * Name:
 *      a_tv_get_num_of_pip_sub_position
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
UINT8 a_tv_get_num_of_pip_sub_position(
                    VOID
                    )
{
    return ui1_g_num_of_pip_sub_position;
}
/*----------------------------------------------------------------------------
 * Name:
 *      a_tv_get_pip_sub_position_id_by_idx
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
INT32 a_tv_get_pip_sub_position_id_by_idx(
                    UINT8                       ui1_idx,             /* in  */
                    TV_PIP_SUB_POSITION_T*      pe_resulted_id       /* out */
                    )
{
    if (pe_resulted_id == NULL) {
        return TVR_INV_ARG;
    }

    if (ui1_g_num_of_pip_sub_position == 0 || ui1_idx >= ui1_g_num_of_pip_sub_position) {
        return TVR_NO_EXIST;
    }

    *pe_resulted_id = at_g_pip_sub_positions[ui1_idx].e_id;

    return TVR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
 *      a_tv_iterate_pip_sub_position_id
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
INT32 a_tv_iterate_pip_sub_position_id(
                    TV_PIP_SUB_POSITION_T       e_ref_id,            /* in  */
                    TV_ITERATE_DIR_T            e_dir,               /* in  */
                    TV_PIP_SUB_POSITION_T*      pe_resulted_id       /* out */
                    )
{
    INT32 i4_ret;
    UINT8 ui1_idx = 0;

    if (pe_resulted_id == NULL) {
        return TVR_INV_ARG;
    }

    if (ui1_g_num_of_pip_sub_position == 0) {
        return TVR_NO_EXIST;
    }

    if (e_ref_id == TV_PIP_SUB_POS_UNKNOWN
            && (e_dir != TV_ITERATE_DIR_FIRST && e_dir != TV_ITERATE_DIR_LAST)) {
        e_dir = TV_ITERATE_DIR_FIRST;
    }

    switch(e_dir) {
    case TV_ITERATE_DIR_CRNT:
        i4_ret = _pop_get_pos_idx_by_id(e_ref_id, &ui1_idx);
        if (i4_ret != NAVR_OK) {
            return TVR_NO_EXIST;
        }
        *pe_resulted_id = at_g_pip_sub_positions[ui1_idx].e_id;
        break;
    case TV_ITERATE_DIR_NEXT_NO_LOOP:
    case TV_ITERATE_DIR_NEXT:
        i4_ret = _pop_get_pos_idx_by_id(e_ref_id, &ui1_idx);
        if (i4_ret != NAVR_OK) {
            return TVR_NO_EXIST;
        }

        if ((ui1_idx+1) >= ui1_g_num_of_pip_sub_position) {
            if (e_dir == TV_ITERATE_DIR_NEXT_NO_LOOP) {
                return TVR_NO_EXIST;
            }
            /* loop to first one */
            *pe_resulted_id = at_g_pip_sub_positions[0].e_id;
        } else {
            *pe_resulted_id = at_g_pip_sub_positions[ui1_idx+1].e_id;
        }
        break;
    case TV_ITERATE_DIR_PREV:
    case TV_ITERATE_DIR_PREV_NO_LOOP:
        i4_ret = _pop_get_pos_idx_by_id(e_ref_id, &ui1_idx);
        if (i4_ret != NAVR_OK) {
            return TVR_NO_EXIST;
        }

        if (ui1_idx == 0) {
            if (e_dir == TV_ITERATE_DIR_PREV_NO_LOOP) {
                return TVR_NO_EXIST;
            }
            /* loop to last one */
            *pe_resulted_id = at_g_pip_sub_positions[ui1_g_num_of_pip_sub_position-1].e_id;
        } else {
            *pe_resulted_id = at_g_pip_sub_positions[ui1_idx-1].e_id;
        }
        break;
    case TV_ITERATE_DIR_FIRST:
        *pe_resulted_id = at_g_pip_sub_positions[0].e_id;
        break;
    case TV_ITERATE_DIR_LAST:
        *pe_resulted_id = at_g_pip_sub_positions[ui1_g_num_of_pip_sub_position-1].e_id;
        break;
    default:
        return TVR_INV_ARG;
    }

    return TVR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
 *      a_tv_iterate_pip_sub_position_id
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
UTF16_T* a_tv_get_pip_sub_size_display_name(
                    TV_PIP_SUB_SIZE_T           e_size_id            /* in */
                    )
{
    UINT8 ui1_idx = 0;

    for (ui1_idx = 0; !IS_VIDEO_REGION_SIZE_END(at_g_pip_sub_sizes[ui1_idx].ui4_width); ui1_idx++) {
        if (at_g_pip_sub_sizes[ui1_idx].e_id != e_size_id) {
            continue;
        }

        if (at_g_pip_sub_sizes[ui1_idx].ui2_mlm_key == INVALID_PIP_MLM_KEY) {
            return NULL;
        } else {
            return MLM_NAV_TEXT(nav_get_mlm_lang_id(), at_g_pip_sub_sizes[ui1_idx].ui2_mlm_key);
        }
    }
    return NULL;
}
/*----------------------------------------------------------------------------
 * Name:
 *      a_tv_get_num_of_pip_sub_size
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
UINT8 a_tv_get_num_of_pip_sub_size(
                    VOID
                    )
{
    return ui1_g_num_of_pip_sub_size;
}
/*----------------------------------------------------------------------------
 * Name:
 *      a_tv_get_pip_sub_size_id_by_idx
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
INT32 a_tv_get_pip_sub_size_id_by_idx(
                    UINT8                       ui1_idx,             /* in  */
                    TV_PIP_SUB_SIZE_T*          pe_resulted_id       /* out */
                    )
{
    if (pe_resulted_id == NULL) {
        return TVR_INV_ARG;
    }

    if (ui1_g_num_of_pip_sub_size == 0 || ui1_idx >= ui1_g_num_of_pip_sub_size) {
        return TVR_NO_EXIST;
    }

    *pe_resulted_id = at_g_pip_sub_sizes[ui1_idx].e_id;

    return TVR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
 *      a_tv_iterate_pip_sub_size_id
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 *----------------------------------------------------------------------------*/
INT32 a_tv_iterate_pip_sub_size_id(
                    TV_PIP_SUB_SIZE_T           e_ref_id,            /* in  */
                    TV_ITERATE_DIR_T            e_dir,               /* in  */
                    TV_PIP_SUB_SIZE_T*          pe_resulted_id       /* out */
                    )
{
    INT32 i4_ret;
    UINT8 ui1_idx = 0;

    if (pe_resulted_id == NULL) {
        return TVR_INV_ARG;
    }

    if (ui1_g_num_of_pip_sub_size == 0) {
        return TVR_NO_EXIST;
    }

    if (e_ref_id == TV_PIP_SUB_SIZE_UNKNOWN
            && (e_dir != TV_ITERATE_DIR_FIRST && e_dir != TV_ITERATE_DIR_LAST)) {
        e_dir = TV_ITERATE_DIR_FIRST;
    }

    switch(e_dir) {
    case TV_ITERATE_DIR_CRNT:
        i4_ret = _pop_get_size_idx_by_id(e_ref_id, &ui1_idx);
        if (i4_ret != NAVR_OK) {
            return TVR_NO_EXIST;
        }
        *pe_resulted_id = at_g_pip_sub_sizes[ui1_idx].e_id;
        break;
    case TV_ITERATE_DIR_NEXT_NO_LOOP:
    case TV_ITERATE_DIR_NEXT:
        i4_ret = _pop_get_size_idx_by_id(e_ref_id, &ui1_idx);
        if (i4_ret != NAVR_OK) {
            return TVR_NO_EXIST;
        }

        if ((ui1_idx+1) >= ui1_g_num_of_pip_sub_size) {
            if (e_dir == TV_ITERATE_DIR_NEXT_NO_LOOP) {
                return TVR_NO_EXIST;
            }
            /* loop to first one */
            *pe_resulted_id = at_g_pip_sub_sizes[0].e_id;
        } else {
            *pe_resulted_id = at_g_pip_sub_sizes[ui1_idx+1].e_id;
        }
        break;
    case TV_ITERATE_DIR_PREV:
    case TV_ITERATE_DIR_PREV_NO_LOOP:
        i4_ret = _pop_get_size_idx_by_id(e_ref_id, &ui1_idx);
        if (i4_ret != NAVR_OK) {
            return TVR_NO_EXIST;
        }

        if (ui1_idx == 0) {
            if (e_dir == TV_ITERATE_DIR_PREV_NO_LOOP) {
                return TVR_NO_EXIST;
            }
            /* loop to last one */
            *pe_resulted_id = at_g_pip_sub_sizes[ui1_g_num_of_pip_sub_size-1].e_id;
        } else {
            *pe_resulted_id = at_g_pip_sub_sizes[ui1_idx-1].e_id;
        }
        break;
    case TV_ITERATE_DIR_FIRST:
        *pe_resulted_id = at_g_pip_sub_sizes[0].e_id;
        break;
    case TV_ITERATE_DIR_LAST:
        *pe_resulted_id = at_g_pip_sub_sizes[ui1_g_num_of_pip_sub_size-1].e_id;
        break;
    default:
        return TVR_INV_ARG;
    }

    return TVR_OK;
}
#endif /*APP_PIP_POP_CTRL*/
