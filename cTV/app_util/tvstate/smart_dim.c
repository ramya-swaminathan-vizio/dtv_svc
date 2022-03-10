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
 * $RCSfile: network.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/3 $
 * $SWAuthor: Weider Chang $
 * $MD5HEX: 4b4dfb21a971fe1b226efee5cf3ed5f1 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/**
 * @file network.c
 *
 * @brief This file implements the API of network.
 *
 * @author
 */

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include <unistd.h>
#include <pthread.h>
#include "c_os.h"

#include "agent/agent.h"
#include "app_util/a_cfg.h"

#ifdef APP_NET_NEIGHBOR_SUPPORT
#include "c_dm_smb.h"
#include "c_fm_smb.h"
#endif

#include "app_util/a_tv.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/config/acfg_custom.h"
#include "res/app_util/config/acfg_cust_plf_opt.h"

#include "app_util/tvstate/tvstate.h"
#include "app_util/tvstate/smart_dim.h"

#include "menu2/menu.h"
#include "menu2/menu_page.h"
#include "res/menu2/menu_cust_define.h"

/*-----------------------------------------------------------------------------
                    customizable macros
----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    macros, defines
----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    typedefs, enums, structures
----------------------------------------------------------------------------*/
static UINT8   ui1_smart_dim_state = SMART_DIM_AS_MENU_SETTING;
/*-----------------------------------------------------------------------------
                    function declarations
----------------------------------------------------------------------------*/
static UINT16 _get_local_dimming_idx (VOID)
{
    UINT16  ui2_idx = 0;
	BOOL b_support = FALSE;
	INT16 i2_val = 0;

    a_cfg_custom_get_is_support_local_dimming(&b_support);
	if(b_support)
	{
		a_cfg_custom_get_dimming_idx(&ui2_idx);
        DBG_INFO (("%s:%d: got local dimming idx: 0x%02x\n",
                    __FUNCTION__, __LINE__, ui2_idx));
		return ui2_idx;
	}
    else
	{
        /* get the val from the EEPROM acfg partition */
		a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR), &i2_val);
	#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
		a_cfg_custom_plf_opt_get_dcr_setting();
	#endif
		return (UINT16)(i2_val);
	}

}

static VOID _smart_dim_update(UINT8 ui1_state)
{
    /* for acfg customization ,it should use a_cfg_av_set/a_cfg_av_update  ,make it run to acfg_cust_odm_video_update */
    BOOL b_support = FALSE;
    UINT16 ui2_local_dim;

    if (ui1_state == ui1_smart_dim_state)
    {
        return;
    }

    ui1_smart_dim_state = ui1_state;

    ui2_local_dim = _get_local_dimming_idx();
    DBG_INFO(("ui2_local_dim=%d\n", (int)ui2_local_dim));

    a_cfg_custom_get_is_support_local_dimming(&b_support);

	if(b_support)
	{
		a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DIMMING));
	}
	else
	{
        ACFG_DEBUG_BACKLIGHT(
            DBG_LOG_PRINT(("[ACFG][BACKLIGHT_CTRL]{%s: %d} Call a_cfg_av_update(APP_CFG_RECID_VID_CUSTOM_DCR)\n", __FUNCTION__, __LINE__ ));
        );

        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_CUSTOM_DCR));

        /* set the val to mem: _u1DCRSetting@Vizio_d_custom.c */
#ifdef APP_MENU_CUSTOM_DRC_LIGHTSENSOR
        a_cfg_custom_plf_opt_set_dcr_setting(ui2_local_dim);
#endif
	}

    return;
}

static VOID _smart_dim_ts_proc(VOID* pv_data, SIZE_T z_data_len)
{
    UINT8 ui1_state = SMART_DIM_AS_MENU_SETTING;
    UINT32  ui4_state_mask = *((UINT32*)pv_data);

    if (ui4_state_mask)
    {
        if (ui4_state_mask & TV_STATE_FULL_SCREEN_GRAPHIC_MASK)
        {
            ui1_state = SMART_DIM_AS_OFF;
        }
        else if (ui4_state_mask & TV_STATE_SIDEBAR_NOT_PIC_SETTING_MASK)
        {
            ui1_state = SMART_DIM_AS_OFF;
        }
        else if (ui4_state_mask & TV_STATE_SIDEBAR_PIC_SETTING_MASK)
        {
            ui1_state = SMART_DIM_AS_OFF;
        }
        else if (ui4_state_mask & TV_STATE_POP_UP_3_4_MASK)
        {
            ui1_state = SMART_DIM_AS_OFF;
        }
        else if (ui4_state_mask & TV_STATE_DOCK_MASK)
        {
            ui1_state = SMART_DIM_AS_OFF;
        }
        else if (ui4_state_mask & TV_STATE_RETAIL_MODE_MASK)
        {
            ui1_state = SMART_DIM_AS_ON;
        }
        else if (ui4_state_mask & TV_STATE_OSD_POP_UP_MASK)
        {
            ui1_state = SMART_DIM_AS_MENU_SETTING;
        }
        else if (ui4_state_mask & TV_STATE_POP_UP_PIC_MASK)
        {
            ui1_state = SMART_DIM_AS_MENU_SETTING;
        }
        else if (ui4_state_mask & TV_STATE_FULL_SCREEN_VID_MASK)
        {
            ui1_state = SMART_DIM_AS_MENU_SETTING;
        }
        else
        {
            ui1_state = SMART_DIM_AS_MENU_SETTING;
        }
    }
    else
    {
        ui1_state = SMART_DIM_AS_MENU_SETTING;
    }

    DBG_INFO(("<TVSTATE> %s() ui4_state_mask = %x, ui1_state = %x\n",
                                                    __FUNCTION__,
                                                    ui4_state_mask,
                                                    ui1_state));

    _smart_dim_update(ui1_state);
    return;
}

INT32  a_smart_dim_init(VOID)
{
    TVSTATE_COMP_T t_ts_comp = {0};

    t_ts_comp.e_ts_comp_id = TS_COMP_TYPE_SMART_DIMMING;
    t_ts_comp.pf_proc = _smart_dim_ts_proc;

    a_tv_state_reg(&t_ts_comp);

    return TSR_OK;
}

UINT8 a_smart_dim_get_assume_val(VOID)
{
    return ui1_smart_dim_state;
}

VOID a_smart_dim_set_assume_val(UINT8 ui1_val)
{
    ui1_smart_dim_state = ui1_val;
}

