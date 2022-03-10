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
 * $RCSfile: record.c,v $
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

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "nav/sys_info/sys_info.h"

#include "nav/sys_info/si_comp/si_tuning_info/a_si_tuning_info.h"
#include "nav/sys_info/si_comp/si_event_info/a_si_event_info.h"
#include "nav/sys_info/si_comp/si_dt_info/a_si_dt_info.h"
#include "nav/sys_info/si_comp/si_3D_info/a_si_3D_info.h"

#include "res/nav/sys_info/si_custom_info.h"
#include "res/nav/nav_dbg.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
                    public method implementation
-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      si_custom_register_subcomp
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 si_custom_register_subcomp(VOID)
{
    a_si_tuning_info_register();
    a_si_event_info_register();
    a_si_dt_info_register();
    a_si_3D_info_register();

    si_custom_info_register();

    return NAVR_OK;
}
#ifdef SI_CUSTOM_CATEGORY_SUPPORT
/*-----------------------------------------------------------------------------
 * Name
 *      si_custom_set_item_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 si_custom_set_item_info
(
    SI_INFO_CTRL_T  e_ctrl,
    SI_WIN_INFO_T   *pt_win_info,       /* IN */
    SI_SET_INFO_T   *pt_set_info        /* IN */
)
{
    SI_CUST_INFO_1_T    *pt_info = 0;
    UINT32              ui4_mask = 0;

#if 0
    if (e_ctrl >= SI_INFO_CTRL_LAST_ENTRY           ||
        0 == pt_set_info->u.t_cust_info_1           ||
        0 == pt_set_info->u.t_cust_info_1.ui4_info_mask)
    {
        return NAVR_INV_ARG;
    }
#endif

    pt_info  = & pt_win_info->t_cust_info_1;
    ui4_mask = pt_set_info->u.t_cust_info_1.ui4_info_mask;

    if (SI_INFO_CTRL_SET == e_ctrl)
    {
        if (ui4_mask & SI_CUSTOM_INFO_MASK_NETWORK_INFO)
        {
            c_memcpy(& pt_info->t_network_info,
                     & pt_set_info->u.t_cust_info_1.t_network_info,
                     sizeof(SI_CUSTOM_INFO_NETWORK_INFO_T));
        }

        if (ui4_mask & SI_CUSTOM_INFO_MASK_SCREEN_MODE)
        {
            c_memcpy(& pt_info->i2_scr_mode,
                     & pt_set_info->u.t_cust_info_1.i2_scr_mode,
                     sizeof(INT16));
        }

        pt_info->ui4_info_mask |= ui4_mask;

    }
    else if (SI_INFO_CTRL_UNSET == e_ctrl)
    {
        pt_info->ui4_info_mask &= (~(ui4_mask));
    }

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      si_custom_cpy_item_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 si_custom_cpy_item_info
(
    SI_WIN_INFO_T   *pt_win_to_info,    /* IN */
    SI_WIN_INFO_T   *pt_win_from_info,  /* IN */
    SI_SET_INFO_T   *pt_set_info        /* IN */
)
{
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      si_custom_get_item_info
 * Description
 * Input arguments
 * Output arguments
 * Returns  -
 *---------------------------------------------------------------------------*/
INT32 si_custom_get_item_info
(
    SI_WIN_INFO_T   *pt_win_info,
    SI_CATEGORY_T   e_category,
    VOID            *pv_info,
    SIZE_T          t_size
)
{
    return NAVR_OK;
}

#endif
