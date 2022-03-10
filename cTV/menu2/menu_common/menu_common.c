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
 * $RCSfile: menu_common.c,v $
 * $Revision: #3 $
 * $Date: 2015/07/15 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/23 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 47aa641dbb1c0b2b64f3264199a32d61 $
 *
 * Description:
 *      This file contains the implementation of GUI-related functions of the
 * menu application
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_sb_atsc_eng.h"
#ifdef APP_DCR_SUPPORT
    #include "u_sb_oob_eng.h"
#else
    #include "u_sb_cqam_eng.h"
#endif

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_fm.h"
#include "c_svl.h"
#include "c_tsl.h"
#include "c_sb.h"
#include "c_svctx.h"
#include "c_cfg.h"
#include "c_nwl.h"
#include "c_lol.h"
#include "c_wgl.h"
#include "c_scc.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_rating.h"
#include "app_util/a_isl.h"
#include "app_util/a_tv.h"

#include "nav/pop/a_pop.h"

#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_page_ex/menu_page_ex.h"
#include "menu2/menu_common/menu_page_animation.h"
#include "menu2/menu_network_phase1/menu_network.h"

#include "res/app_util/app_tv/a_tv_custom.h"
#include "res/menu2/menu_custom.h"
#include "res/app_util/config/acfg_cust_video.h"
#include "res/app_util/config/acfg_custom.h"


#ifdef APP_MENU_STORE_CH_LST_BY_AGENT
    #include "agent/a_agent.h"
    #define  _ASYNC_INVOKE(_func, _data, _size, _retry)  a_agent_async_invoke(_func, _data, _size)
#else
    #define  _ASYNC_INVOKE(_func, _data, _size, _retry)  menu_async_invoke(_func, _data, _size, _retry)
#endif
#define IS_GAME_MODE_BASE	1
#define IS_NOT_GAME_MODE_BASE 0

#include "mmp/a_mmp.h"
#include "am/a_am.h"

#ifdef APP_MENU_MMP_COEXIST
#include "mmp/a_mmp.h"
#include "mmp/browse_eng/mmp_browse_eng.h"
#endif
#include "menu2/menu_dbg.h"
#include "unistd.h"
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
/* defined for hot key  --> */
#ifndef MENU_MAX_HOT_KEY_NUM
#define MENU_MAX_HOT_KEY_NUM        (16)
#endif

#ifndef ENABLE_SWITCH_CH_IN_MAIN_MENU_PAGE
#define ENABLE_SWITCH_CH_IN_MAIN_MENU_PAGE
#endif

#define MENU_INVALID_HOT_KEY_INDEX  ((UINT32)-1)

typedef struct _MENU_HOT_KEY_INFO_T
{
    UINT32              ui4_hot_key_num;
    MENU_HOT_KEY_REG_T  at_hot_key_reg[MENU_MAX_HOT_KEY_NUM];
}MENU_HOT_KEY_INFO_T;
/* <-- defined for hot key */


/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/
MENU_COMMON_T          t_g_menu_common;
BOOL                   t_g_menu_is_scanning;
BOOL                   t_g_menu_enable_channel_change;
extern UINT32          ui4_g_page_clear_memory;
extern UINT32          ui4_g_menu_page_main_menu;
#ifdef APP_AV_COMPONENT_USE_ONE_PORT
extern INT32 a_cfg_custom_get_srcid_com_or_av(UINT8* pSrcId);
#endif

static UINT32          ui4_g_last_strm_mode = ST_MASK_AUDIO|ST_MASK_VIDEO;

static                  MENU_HOT_KEY_INFO_T t_g_menu_hot_key_info = {0};
/*-----------------------------------------------------------------------------
                    function implementation
 ----------------------------------------------------------------------------*/
static VOID _do_store_cfg(VOID* pv_data,
                          SIZE_T  z_data_size)
{
    INT32 i4_ret;
    DBG_INFO(("<MENU>Begin storing config\r\n"));
    i4_ret = a_cfg_store();
    if(i4_ret != APP_CFGR_OK)
    {
        DBG_INFO(("<MENU>Can't store config.\r\n"));
    }
    else
    {
        DBG_INFO(("<MENU>End storing config\r\n"));
    }
}

static VOID _do_store_svl_air(VOID*   pv_data,
                               SIZE_T  z_data_size)
{
    DUAL_BANK_AS_MODE_T  e_as_mode;

    if (t_g_menu_common.b_dual_bank_dirty == TRUE)
    {
        e_as_mode = DUAL_BANK_AS_MODE_TO_MAIN_SUB;
    }
    else
    {
        e_as_mode = DUAL_BANK_AS_MODE_BY_NVM;
    }
    a_util_dual_bank_svl_fs_store(FM_ROOT_HANDLE, e_as_mode, ATSC_TRSTRL_SVL_ID, NULL);
}

static VOID _do_store_svl_cable(VOID*   pv_data,
                               SIZE_T  z_data_size)
{
    DUAL_BANK_AS_MODE_T  e_as_mode;

    if (t_g_menu_common.b_dual_bank_dirty == TRUE)
    {
        e_as_mode = DUAL_BANK_AS_MODE_TO_MAIN_SUB;
    }
    else
    {
        e_as_mode = DUAL_BANK_AS_MODE_BY_NVM;
    }
    a_util_dual_bank_svl_fs_store(FM_ROOT_HANDLE, e_as_mode, ATSC_CABLE_SVL_ID, NULL);
}

static VOID _do_store_tsl_air(VOID* pv_data,
                               SIZE_T  z_data_size)
{
    DUAL_BANK_AS_MODE_T  e_as_mode;

    if (t_g_menu_common.b_dual_bank_dirty == TRUE)
    {
        e_as_mode = DUAL_BANK_AS_MODE_TO_MAIN_SUB;
    }
    else
    {
        e_as_mode = DUAL_BANK_AS_MODE_BY_NVM;
    }
    a_util_dual_bank_tsl_fs_store(FM_ROOT_HANDLE, e_as_mode, ATSC_TRSTRL_TSL_ID, NULL);
}

static VOID _do_store_tsl_cable(VOID* pv_data,
                               SIZE_T  z_data_size)
{
    DUAL_BANK_AS_MODE_T  e_as_mode;

    if (t_g_menu_common.b_dual_bank_dirty == TRUE)
    {
        e_as_mode = DUAL_BANK_AS_MODE_TO_MAIN_SUB;
    }
    else
    {
        e_as_mode = DUAL_BANK_AS_MODE_BY_NVM;
    }
    a_util_dual_bank_tsl_fs_store(FM_ROOT_HANDLE, e_as_mode, ATSC_CABLE_TSL_ID, NULL);
}
#ifndef APP_LOL_NWL_DISABLE
static VOID _do_store_nwl_air(VOID* pv_data,
                               SIZE_T  z_data_size)
{
    DUAL_BANK_AS_MODE_T  e_as_mode;

    if (t_g_menu_common.b_dual_bank_dirty == TRUE)
    {
        e_as_mode = DUAL_BANK_AS_MODE_TO_MAIN_SUB;
    }
    else
    {
        e_as_mode = DUAL_BANK_AS_MODE_BY_NVM;
    }
    a_util_dual_bank_nwl_fs_store(FM_ROOT_HANDLE, e_as_mode, ATSC_TRSTRL_NWL_ID, NULL);
}

static VOID _do_store_nwl_cable(VOID* pv_data,
                               SIZE_T  z_data_size)
{
    DUAL_BANK_AS_MODE_T  e_as_mode;

    if (t_g_menu_common.b_dual_bank_dirty == TRUE)
    {
        e_as_mode = DUAL_BANK_AS_MODE_TO_MAIN_SUB;
    }
    else
    {
        e_as_mode = DUAL_BANK_AS_MODE_BY_NVM;
    }
    a_util_dual_bank_nwl_fs_store(FM_ROOT_HANDLE, e_as_mode, ATSC_CABLE_NWL_ID, NULL);
}

static VOID _do_store_lol_air(VOID* pv_data,
                               SIZE_T  z_data_size)
{
    DUAL_BANK_AS_MODE_T  e_as_mode;

    if (t_g_menu_common.b_dual_bank_dirty == TRUE)
    {
        e_as_mode = DUAL_BANK_AS_MODE_TO_MAIN_SUB;
    }
    else
    {
        e_as_mode = DUAL_BANK_AS_MODE_BY_NVM;
    }
    a_util_dual_bank_lol_fs_store(FM_ROOT_HANDLE, e_as_mode, ATSC_TRSTRL_LOL_ID, NULL);
}

static VOID _do_store_lol_cable(VOID* pv_data,
                               SIZE_T  z_data_size)
{
    DUAL_BANK_AS_MODE_T  e_as_mode;

    if (t_g_menu_common.b_dual_bank_dirty == TRUE)
    {
        e_as_mode = DUAL_BANK_AS_MODE_TO_MAIN_SUB;
    }
    else
    {
        e_as_mode = DUAL_BANK_AS_MODE_BY_NVM;
    }
    a_util_dual_bank_lol_fs_store(FM_ROOT_HANDLE, e_as_mode, ATSC_CABLE_LOL_ID, NULL);
}
#endif
static VOID _do_sync_src(VOID*   pv_data,
                         SIZE_T  z_data_size)
{
    INT32  i4_ret;
    UINT16 ui2_crnt_svl_id;
    DBG_INFO(("<MENU>Begin notifying DT to sync source\r\n"));
    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    if (i4_ret == APP_CFGR_OK)
    {
        i4_ret = a_cfg_set_tuner_sync_src(ui2_crnt_svl_id, NULL);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<MENU>Can't notify DT to sync source\r\n"));
        }
    }
    else
    {
        DBG_ERROR(("<MENU>Can't get tuner svl id and tuner name\r\n"));
    }
    DBG_INFO(("<MENU>End notifying DT to sync source\r\n"));
}


static INT32 _do_Prev_Prg(BOOL *pProcessed)
{
    UINT32      ui4_channel_id, ui4_old_channel_id;
    INT32       i4_ret;
    APP_TV_NET_SVC_STATUS t_svc_state = APP_TV_NET_SVC_STATUS_PAUSED;
    TV_MODE_T   t_tv_mode;
    ISL_REC_T   t_isl_rec;
    HANDLE_T    h_main_frm = NULL_HANDLE;
    BOOL        b_visible = FALSE;

    if(t_g_menu_is_scanning == TRUE ||
       t_g_menu_enable_channel_change == FALSE)
    {                             /* Forbid to change channel */
        *pProcessed = FALSE;
        return MENUR_OK;
    }


    t_svc_state = a_tv_net_get_tv_svc_status();
    if(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
    {
        *pProcessed = TRUE;
        return MENUR_OK;
    }

    menu_get_crnt_tv_mode_and_isl_rec(&t_tv_mode, &t_isl_rec);
    if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        /* Forbid to change channel except TV */
        *pProcessed = FALSE;
        return MENUR_OK;
    }

    if(  (t_tv_mode == TV_MODE_TYPE_PIP || t_tv_mode == TV_MODE_TYPE_POP) &&
         (t_isl_rec.e_src_type != INP_SRC_TYPE_TV) )
    {
        /* When user is in PIP/P0P mode, and the focus win's input src != TV,
           forbid user to change channel */
        *pProcessed = FALSE;
        return MENUR_OK;
    }

    if ((t_isl_rec.ui4_attr_bits & ISL_ATTR_BIT_BLOCKED) > 0          &&
         (t_isl_rec.ui4_attr_bits & ISL_ATTR_BIT_USER_TMP_UNLOCK) == 0 &&
         t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
    {
        /* TV is blocked and isn't unlocked temporarily */
        *pProcessed = FALSE;
        return MENUR_OK;
    }

    ui4_old_channel_id = a_util_cnfg_get_crnt_channel_id();
    ui4_channel_id = a_util_cnfg_get_last_channel_id();

    if(ui4_channel_id == INVALID_CHANNEL_ID)   /* Old id is invalid */
    {
        *pProcessed = FALSE;
        return MENUR_FAIL;
    }
    else if (ui4_channel_id != ui4_old_channel_id)
    {
        a_util_cnfg_set_last_channel_id(ui4_old_channel_id);
        a_util_cnfg_set_crnt_channel_id(ui4_channel_id);

       i4_ret = a_tv_change_channel(menu_get_crnt_svctx(),
                                    ST_MASK_VIDEO | ST_MASK_AUDIO,
                                    ui4_channel_id,
                                    NULL);
       if(i4_ret != TVR_OK)
       {
           *pProcessed = FALSE;
           return MENUR_FAIL;
       }
    }

    /* deal with menu ui */
    menu_pm_get_main_frm(&h_main_frm);
    c_wgl_get_visibility(h_main_frm, &b_visible);

    if (!b_visible)
    {
        if (t_g_menu_common.b_is_hot_key_enter == TRUE)
        {
            menu_leave (TRUE, MENU_PM_HIDE_DELAY);
        }
        else
        {
            menu_nav_go_home_menu();
        }
    }
    else
    {
        /* do nothing */
    }

    *pProcessed = TRUE;

   return MENUR_OK;

}

static INT32 _do_channel_change(HANDLE_T h_svctx, UINT32 ui4_key)
{
    INT32       i4_ret = MENUR_OK;
    UINT32      ui4_channel_id;
    UINT32      ui4_old_channel_id;
    BOOL        b_found = FALSE;
    SVL_REC_T   t_svl_rec;
    HANDLE_T    h_crnt_svl;
    TV_WIN_ID_T e_win_id = TV_WIN_ID_MAIN;
    TV_MODE_T   e_mode = TV_MODE_TYPE_NORMAL;

    h_crnt_svl = menu_get_crnt_svl();
    b_found = FALSE;

    ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
    ui4_old_channel_id = ui4_channel_id;

    if(ui4_key == BTN_PRG_DOWN)
    {

        b_found = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                        h_crnt_svl,
                        a_tv_get_surfable_svl_rec_check_nw_mask(),
                        a_tv_get_surfable_svl_rec_check_nw_bits(),
#ifdef APP_BRA_PRIMARY_ES_SELECT
                        TV_ITERATE_DIR_PREV_PRIM_ES,
#else
                        TV_ITERATE_DIR_PREV,
#endif
                        &ui4_channel_id,          /* Will update the ui4_channel_id */
                        &t_svl_rec
                        );

    }
    else if(ui4_key == BTN_PRG_UP)
    {

        b_found = a_tv_mcl_get_svl_rec_by_logic_and_nw_masks(
                        h_crnt_svl,
                        a_tv_get_surfable_svl_rec_check_nw_mask(),
                        a_tv_get_surfable_svl_rec_check_nw_bits(),
#ifdef APP_BRA_PRIMARY_ES_SELECT
                        TV_ITERATE_DIR_NEXT_PRIM_ES,
#else
                        TV_ITERATE_DIR_NEXT,
#endif
                        &ui4_channel_id,          /* Will update the ui4_channel_id */
                        &t_svl_rec
                        );

    }
    else if(ui4_key == BTN_PREV_PRG)
    {
        if(ui4_old_channel_id == INVALID_CHANNEL_ID)   /* Old id is invalid */
        {
            b_found = FALSE;
        }
        else
        {
            ui4_channel_id = a_util_cnfg_get_last_channel_id();
            a_util_cnfg_set_last_channel_id(ui4_old_channel_id);
            a_util_cnfg_set_crnt_channel_id(ui4_channel_id);
            b_found = TRUE;
        }
    }
    else
    {
        /* Do nothing */
    }

    if (b_found == TRUE)
    {
        if (ui4_old_channel_id == INVALID_CHANNEL_ID)
        {
            a_util_cnfg_set_last_channel_id(ui4_channel_id);
            a_util_cnfg_set_crnt_channel_id(ui4_channel_id);
        }
        else if (ui4_channel_id != ui4_old_channel_id)
        {
            a_util_cnfg_set_last_channel_id(ui4_old_channel_id);
            a_util_cnfg_set_crnt_channel_id(ui4_channel_id);
        }

        i4_ret = a_tv_get_mode(&e_mode);
        if (i4_ret != TVR_OK)
        {
            e_mode = TV_MODE_TYPE_NORMAL;
        }

        if (e_mode == TV_MODE_TYPE_NORMAL)
        {
            i4_ret = a_tv_change_channel(h_svctx,
                                         ST_MASK_VIDEO | ST_MASK_AUDIO,
                                         ui4_channel_id,
                                         NULL);
        }
        else
        {
#ifdef APP_PIP_POP_CTRL
            a_pop_get_audio_focus_id(&e_win_id);
#endif
            if (((e_win_id == TV_WIN_ID_MAIN)&&(t_g_menu_common.h_svctx_sub == h_svctx)) ||
                ((e_win_id == TV_WIN_ID_SUB)&&(t_g_menu_common.h_svctx == h_svctx)))
            {
                    i4_ret = a_tv_change_channel(h_svctx,
                                                 ST_MASK_VIDEO,
                                                 ui4_channel_id,
                                                 NULL);
            }
            else
            {

                i4_ret = a_tv_change_channel(h_svctx,
                                             ST_MASK_VIDEO | ST_MASK_AUDIO,
                                             ui4_channel_id,
                                             NULL);
            }
        }

        if(i4_ret != TVR_OK)
        {
            return MENUR_FAIL;
        }
    }

    return MENUR_OK;
}

static BOOL _is_digital_key_in_menu(VOID)
{
    HANDLE_T        h_widget;
    HANDLE_TYPE_T   e_type;
    VOID*           pv_tag;
    UINT32          ui4_page_id;

    c_wgl_get_focus(&h_widget);
    c_handle_get_info(h_widget, &e_type, &pv_tag);

    menu_nav_get_crnt_page(&ui4_page_id);

    if ((e_type == HT_WGL_WIDGET_EDIT_BOX)||(e_type == HT_WGL_WIDGET_TEXT) ||
		#ifndef ENABLE_SWITCH_CH_IN_MAIN_MENU_PAGE
		(ui4_page_id == ui4_g_menu_page_main_menu) ||
		#endif
        (ui4_page_id == ui4_g_page_clear_memory)
        	|| (ui4_page_id == ui4_g_menu_custom_page_lock_pic_mode)
        	|| (ui4_page_id == ui4_g_menu_custom_page_unlock_pic_mode)
        	|| (ui4_page_id == ui4_g_menu_page_chg_pwd)
        	|| (ui4_page_id == ui4_g_page_input_sys_pin))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

static UINT32 _menu_get_key_index(UINT32 ui4_key_code)
{
    UINT32 ui4_index = 0;

    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X\n", __FUNCTION__, __LINE__,ui4_key_code )); );

    for (ui4_index = 0; ui4_index < t_g_menu_hot_key_info.ui4_hot_key_num; ui4_index++)
    {
        if (ui4_key_code == t_g_menu_hot_key_info.at_hot_key_reg[ui4_index].ui4_key_code)
        {
            MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X => ui4_index:%d\n", __FUNCTION__, __LINE__, ui4_key_code, ui4_index )); );

            return (ui4_index);
        }
    }

    return MENU_INVALID_HOT_KEY_INDEX;
}

static INT32 _menu_set_hot_key_page(UINT32 ui4_key_code, UINT32 ui4_page_id)
{
    UINT32 ui4_index = 0;

    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X, ui4_page_id:%d\n",
        __FUNCTION__, __LINE__,ui4_key_code, ui4_page_id )); );

    ui4_index = _menu_get_key_index(ui4_key_code);

    if (MENU_INVALID_HOT_KEY_INDEX == ui4_index)
    {
        return MENUR_FAIL;
    }

    t_g_menu_hot_key_info.at_hot_key_reg[ui4_index].ui4_page_idx = ui4_page_id;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_reset_svl_by_mask
 *
 * Description: h_svl -
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/

INT32 menu_reset_svl_by_mask(HANDLE_T h_svl,
                             UINT32 ui4_reset_mask,
                             UINT32 ui4_reset_value)
{
    INT32       i4_result;
    INT32       i4_ret = MENUR_OK;
    UINT32      ui4_lst_mask = SB_VNET_ALL;
    UINT16      ui2_idx;
    UINT16      ui2_rec_num = 0;
    UINT16*     aui2_rec_id;
    UINT32      ui4_ver_id = SVL_NULL_VER_ID;
    SVL_REC_T   t_svl_rec;

    if (h_svl == NULL_HANDLE)
    {
        return MENUR_INV_ARG;
    }

    /* lock SVL */
    i4_result = c_svl_lock(h_svl);
    if(i4_result != SVLR_OK)
    {
        i4_ret = MENUR_FAIL;
        DBG_ERROR(("<MENU> Can't lock SVL.\r\n"));
    }

    else
    {
        /* get record number */
        i4_result = c_svl_get_num_rec_by_brdcst_type(h_svl,
                                                     BRDCST_TYPE_UNKNOWN,
                                                     ui4_lst_mask,
                                                     &ui2_rec_num,
                                                     &ui4_ver_id);
        if(i4_result != SVLR_OK)
        {
            DBG_ERROR(("<MENU> Can't get record number.\r\n"));
            i4_ret = MENUR_FAIL;
        }
        else
        {
            /* Due to the bug in SVL, we use the two iteration work-around
               solution. In the first iteration, we store the svl record to
               an array; and the second iteration, we make use of these ids
               to update records. */
            aui2_rec_id = (UINT16*) c_mem_alloc(ui2_rec_num * sizeof(UINT16));
            if(aui2_rec_id == NULL)
            {
                i4_ret = MENUR_FAIL;
            }
            else
            {
                /* Iter 1: Get all record id. (readonly iteration) */
                for(ui2_idx=0; ui2_idx<ui2_rec_num; ui2_idx++)
                {
                    i4_result = c_svl_get_rec_by_brdcst_type(h_svl,
                                                             BRDCST_TYPE_UNKNOWN,
                                                             ui4_lst_mask,
                                                             ui2_idx,
                                                             &t_svl_rec,
                                                             &ui4_ver_id);
                    if(i4_result != SVLR_OK)
                    {
                        i4_ret = MENUR_FAIL;
                        DBG_ERROR(("<MENU> Can't iterate service list at idx=%d.\r\n",
                                   ui2_idx));
                        break;
                    }
                    aui2_rec_id[ui2_idx] = t_svl_rec.ui2_svl_rec_id;
                }

                /* Iter 2: Get the record by record id and update it */
                for (ui2_idx=0;
                     ui2_idx<ui2_rec_num && i4_ret == MENUR_OK;
                     ui2_idx++)
                {
                    i4_result = c_svl_get_rec(h_svl,
                                              aui2_rec_id[ui2_idx],
                                              &t_svl_rec,
                                              &ui4_ver_id);
                    if(i4_result != SVLR_OK)
                    {
                        i4_ret = MENUR_FAIL;
                        DBG_ERROR(("<MENU> Can't get record %d.\r\n",
                                   aui2_rec_id[ui2_idx]));
                        break;
                    }


                    t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask =
                        (t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & ~ui4_reset_mask) |
                        (ui4_reset_value & ui4_reset_mask);

                    i4_result = c_svl_update_rec(h_svl, &t_svl_rec, TRUE);
                    if (i4_result != SVLR_OK)
                    {
                        DBG_ERROR(("<MENU> Can't update record: %d < %d.\r\n",
                                    t_svl_rec.ui2_svl_rec_id));
                    }
                } /* end of Iteration  */

                c_mem_free(aui2_rec_id);
            } /* c_mem_alloc */
        }/* c_svl_get_num_rec_by_brdcst_type */

        /* Unlock SVL */
        c_svl_unlock(h_svl);
    } /* c_svl_lock */

    /* Set the proper dirty flag */

    if(h_svl == t_g_menu_common.h_svl_air)
    {
       t_g_menu_common.b_svl_air_dirty = TRUE;
    }

    if(h_svl == t_g_menu_common.h_svl_cable)
    {
       t_g_menu_common.b_svl_cable_dirty = TRUE;
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: menu_reset_isl_by_mask
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
INT32 menu_reset_isl_by_mask(UINT32 ui4_reset_mask,
                             UINT32 ui4_reset_value)
{
    INT32       i4_result;
    UINT8       ui1_idx;
    UINT8       ui1_rec_num;
    ISL_REC_T   t_isl_rec;

    /* lock isl */
    i4_result = a_isl_lock();

    MENU_CHK_FAIL(i4_result);

    /* get record number */

    i4_result = a_isl_get_num_rec(&ui1_rec_num);

    MENU_CHK_FAIL(i4_result);

    /* iterate all ISL record */

    for(ui1_idx = 0 ; ui1_idx < ui1_rec_num ;  ui1_idx++)
    {
        a_isl_get_rec_by_idx(ui1_idx, &t_isl_rec);
        MENU_CHK_FAIL(i4_result);

        /* Reset the ui4_attr_bits */
        t_isl_rec.ui4_attr_bits =
            (t_isl_rec.ui4_attr_bits & ~ui4_reset_mask) |
            (ui4_reset_value & ui4_reset_mask);

        a_isl_set_attr_bits_by_idx(ui1_idx, t_isl_rec.ui4_attr_bits);
        MENU_CHK_FAIL(i4_result);
    }

    /* unlock isl */
    i4_result = a_isl_unlock();

    MENU_CHK_FAIL(i4_result);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_reg_hot_key
 *
 * Description
 *      This api is used to register hot key.
 * Input arguments
 *      pt_hot_key
 * Output arguments
 *      None
 * Returns
 *      MENUR_OK    register success.
 *      Other       register fail.
 *---------------------------------------------------------------------------*/
extern INT32 menu_reg_hot_key(MENU_HOT_KEY_REG_T* pt_hot_key)
{
    UINT32 ui4_index = 0;

    if (!pt_hot_key)
    {
        return (MENUR_INV_ARG);
    }

    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X, ui4_page_id:%d\n",
        __FUNCTION__, __LINE__, pt_hot_key->ui4_key_code, pt_hot_key->ui4_page_idx)); );

    ui4_index = _menu_get_key_index(pt_hot_key->ui4_key_code);
    if (MENU_INVALID_HOT_KEY_INDEX != ui4_index)
    {
        return (MENUR_FAIL);
    }

    if (t_g_menu_hot_key_info.ui4_hot_key_num >= MENU_MAX_HOT_KEY_NUM)
    {
        return (MENUR_OUT_OF_MEMORY);
    }

    c_memcpy(t_g_menu_hot_key_info.at_hot_key_reg + t_g_menu_hot_key_info.ui4_hot_key_num,
             pt_hot_key,
             sizeof(MENU_HOT_KEY_REG_T));

    t_g_menu_hot_key_info.ui4_hot_key_num++;

    return (MENUR_OK);
}

/*-----------------------------------------------------------------------------
 * Name: menu_unreg_hot_key
 *
 * Description
 *      This api is used to unregiseter hot key.
 * Input arguments
 *      ui4_key_code
 * Output arguments
 *      None
 * Returns
 *      MENUR_OK    unregister success.
 *      Other       unregister fail.
 *---------------------------------------------------------------------------*/
extern INT32 menu_unreg_hot_key(UINT32 ui4_key_code)
{
    UINT32 ui4_index = 0;
    ui4_index = _menu_get_key_index(ui4_key_code);
    if (MENU_INVALID_HOT_KEY_INDEX == ui4_index)
    {
        return (MENUR_ITEM_NOT_FOUND);
    }

    c_memmove(t_g_menu_hot_key_info.at_hot_key_reg + ui4_index,
              t_g_menu_hot_key_info.at_hot_key_reg + ui4_index + 1,
              (t_g_menu_hot_key_info.ui4_hot_key_num - ui4_index - 1) * sizeof(MENU_HOT_KEY_REG_T));
    return (MENUR_OK);
}

/*-----------------------------------------------------------------------------
 * Name: menu_is_hot_key
 *
 * Description
 *      This API is to check certain is hot key.
 * Input arguments
 *      ui4_key_code
 *      ui4_kev_event
 * Output arguments
 *      None
 * Returns
 *      TRUE    The key is hot key.
 *      FALSE   The key is not hot key.
 *---------------------------------------------------------------------------*/
extern BOOL menu_is_hot_key(UINT32 ui4_key_code, UINT32 ui4_key_event)
{
    UINT32 ui4_index = 0;

    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X, ui4_key_event:0x%x\n",
        __FUNCTION__, __LINE__,ui4_key_code, ui4_key_event )); );

    if (WGL_MSG_KEY_DOWN != ui4_key_event)
    {
        MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X, ui4_key_event:0x%x not DOWN ==> FALSE\n",
            __FUNCTION__, __LINE__,ui4_key_code, ui4_key_event )); );

        return (FALSE);
    }

    ui4_index = _menu_get_key_index(ui4_key_code);

    BOOL b_rtn = (ui4_index != MENU_INVALID_HOT_KEY_INDEX);

    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X, ui4_key_event:0x%x ==> %d\n",
            __FUNCTION__, __LINE__,ui4_key_code, ui4_key_event, b_rtn )); );

    return b_rtn;
}

extern INT32 menu_hot_key_set_page(UINT32 ui4_key_code,UINT32 ui4_page_id)
{
    return _menu_set_hot_key_page(ui4_key_code, ui4_page_id);
}
/*-----------------------------------------------------------------------------
 * Name: menu_hot_key_handler
 *
 * Description
 *      This API is used to handler hot key event.
 * Input arguments
 *      ui4_key_code
 *      ui4_key_event
 *      pv_param
 * Output arguments
 *      None
 * Returns
 *      MENUR_OK    Hander hot key success.
 *      Other       Hander hot key fail.
 *---------------------------------------------------------------------------*/
extern INT32 menu_hot_key_handler(UINT32 ui4_key_code, UINT32 ui4_key_event, VOID* pv_param)
{
    INT32  i4_ret;
    UINT32 ui4_index = 0;
    extern BOOL menu_cc_is_visible(VOID);


    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X, ui4_key_event:0x%X\n",
        __FUNCTION__, __LINE__,ui4_key_code, ui4_key_event )); );


    if (WGL_MSG_KEY_DOWN != ui4_key_event)
    {
        return (MENUR_FAIL);
    }

    ui4_index = _menu_get_key_index(ui4_key_code);
    if (MENU_INVALID_HOT_KEY_INDEX == ui4_index)
    {
        return (MENUR_FAIL);
    }

    if (BTN_CC == ui4_key_code)
    {
        if (menu_cc_is_visible() == FALSE)
        {
            return (MENUR_OK);
        }
    }
    else if(BTN_BLANK_SCREEN == ui4_key_code)
    {
		menu_custom_blank_screen();
    }

    /* Wide key no effect on no signal or block channel */
#if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
    if (BTN_ASPECT == ui4_key_code)
    {
        MENU_DEBUG_KEY_ASPECT_RATIO(
            DBG_LOG_PRINT(("[MENU][KEY][ASPECT_RATIO]{%s,%d} ui4_key_code is BTN_ASPECT, should got ASPECT_list\n", __FUNCTION__, __LINE__ )); );
    }
#endif

#ifdef KK_SCREEN_MODE
    if (BTN_ASPECT == ui4_key_code)
    {
        VSH_SRC_RESOLUTION_INFO_T   t_resolution;

        c_memset (&t_resolution, 0, sizeof (VSH_SRC_RESOLUTION_INFO_T));
        c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_resolution);

        /* Wide key no effect on no signal or block channel */
        if (t_resolution.ui4_width == 0
            || t_resolution.ui4_height == 0)
        {
            DBG_INFO(("no signal or locked."));
            return MENUR_OK;
        }

        /* For CR636044 */
        a_tv_net_send_cmd("\n:am,am,WIDE:active_ap=dtv_app_mtk\n");
        a_tv_net_send_cmd("\n:am,am,:focus=dtv_app_mtk\n");
    }
#endif


#if( MENU_SUPPORT_HOT_KEY_PIC )
    if (BTN_P_EFFECT == ui4_key_code)
    {
        MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][KEY_PIC]{%s,%d} ui4_key_code is BTN_P_EFFECT, should got pic_mode_list\n", __FUNCTION__, __LINE__ )); );
    }
#endif

#ifdef APP_SUPPORT_PIC_HOT_KEY
    if (BTN_P_EFFECT == ui4_key_code)
    {
        ISL_REC_T   t_isl_rec;
        VSH_SRC_RESOLUTION_INFO_T t_timing;

        HANDLE_T    h_svctx;

        c_memset(&t_timing, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));

        h_svctx = menu_get_crnt_svctx();
        c_svctx_get_video_src_resolution(h_svctx, &t_timing);

        menu_get_crnt_isl(&t_isl_rec);

        if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
           (t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA ||
            t_isl_rec.t_avc_info.e_video_type == DEV_AVC_DVI) &&
           t_timing.e_timing_type != VSH_SRC_TIMING_VIDEO)
        {
            return MENUR_OK;
        }
    }
#endif

    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} call a_amb_resume_app(MENU_NAME)\n", __FUNCTION__, __LINE__ )); );

    i4_ret = a_amb_resume_app(MENU_NAME);
    MENU_CHK_FAIL(i4_ret);

    t_g_menu_common.ui4_key_code       = ui4_key_code;
    t_g_menu_common.b_is_hot_key_enter = TRUE;

    return (MENUR_OK);
}

/*-----------------------------------------------------------------------------
 * Name: menu_jump_to_hot_key_page
 *
 * Description
 *      The API is used to jump to the page of the hot key user pressed.
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      MENUR_OK    Jump to hot key page success.
 *      Other       Jump to hot key page fail.
 *---------------------------------------------------------------------------*/
extern INT32 menu_jump_to_hot_key_page(VOID)
{
    INT32  i4_ret;
    UINT32 ui4_index = 0;
    extern UINT32 ui4_g_menu_page_nw;


    MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key_code:0x%X \n", __FUNCTION__, __LINE__, t_g_menu_common.ui4_key_code )); );

#if( MENU_SUPPORT_HOT_KEY_PIC )
    if( BTN_P_EFFECT == t_g_menu_common.ui4_key_code )
    {
        MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][KEY_PIC]{%s,%d} ui4_key_code is BTN_P_EFFECT\n", __FUNCTION__, __LINE__ )); );
    }
#endif

#if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
    if( BTN_ASPECT == t_g_menu_common.ui4_key_code )
    {
        MENU_DEBUG_KEY_ASPECT_RATIO(
            DBG_LOG_PRINT(("[MENU][KEY][ASPECT_RATIO]{%s,%d} ui4_key_code is BTN_ASPECT\n", __FUNCTION__, __LINE__ )); );
    }
#endif

    do
    {
        ui4_index = _menu_get_key_index(t_g_menu_common.ui4_key_code);
        if (MENU_INVALID_HOT_KEY_INDEX == ui4_index)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        if (BTN_NETWORK == t_g_menu_common.ui4_key_code)
        {
            if (a_tv_custom_get_tos() == FALSE || a_tv_custom_get_privacy() == FALSE)
            {
                menu_hot_key_set_page(BTN_NETWORK, ui4_g_menu_page_terms);
            }
            else
            {
                menu_hot_key_set_page(BTN_NETWORK, ui4_g_menu_page_nw);
            }
        }

        i4_ret = menu_show_backbar(TRUE, FALSE);
        if (MENUR_OK != i4_ret)
        {
            break;
        }


    #if( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
        if( BTN_ASPECT == t_g_menu_common.ui4_key_code )
        {
            MENU_PAGE_HINT_T stMENU_PAGE_HINT = {0};
            stMENU_PAGE_HINT.e_hint_type = MENU_PAGE_HT_CUST_ITEM_ID;
            stMENU_PAGE_HINT.u.u16_item_id = g_menu_u16_item_id_PICTURE_ASPECT_RATIO;

            MENU_DEBUG_HOT_KEY(
                DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} call menu_nav_go(ui4_page_idx:%d, ui2_item_id:%d )\n",
                    __FUNCTION__, __LINE__, t_g_menu_hot_key_info.at_hot_key_reg[ui4_index].ui4_page_idx,
                    g_menu_u16_item_id_PICTURE_ASPECT_RATIO )); );

            i4_ret = menu_nav_go(t_g_menu_hot_key_info.at_hot_key_reg[ui4_index].ui4_page_idx,
                                 &stMENU_PAGE_HINT);

        }
        else
    #endif
        {
            MENU_DEBUG_HOT_KEY( DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} call menu_nav_go(ui4_page_idx:%d)\n",
                __FUNCTION__, __LINE__, t_g_menu_hot_key_info.at_hot_key_reg[ui4_index].ui4_page_idx )); );

            i4_ret = menu_nav_go(t_g_menu_hot_key_info.at_hot_key_reg[ui4_index].ui4_page_idx,
                                 NULL);
        }

        if (MENUR_OK != i4_ret)
        {
            break;
        }

        return (MENUR_OK);
    }while (0);

    t_g_menu_common.b_is_hot_key_enter = FALSE;
    return (i4_ret);
}

/*----------------------------------------------------------------------------
 * Name: menu_enable_video_mute
 *
 * Description:
 *  This API used to enable/disble the bluemute when it's scanning
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
extern INT32 menu_enable_video_mute(BOOL b_enable)
{
    HANDLE_T h_svctx;
    SIZE_T   z_size;
    INT32    i4_ret;
    BOOL     b_cfg_blue_mute_enable = FALSE;

    i4_ret = a_cfg_get_blue_mute(&b_cfg_blue_mute_enable);
    if (i4_ret != APP_CFGR_OK || b_cfg_blue_mute_enable == FALSE) {
        return MENUR_OK;
    }

    /* only need to disable video mute temporarily if the related ACFG is set.*/
    h_svctx = menu_get_crnt_svctx();

    z_size = sizeof(BOOL);
    i4_ret = c_svctx_set(h_svctx,
                         SVCTX_COMMON_SET_VIDEO_MUTE_VIA_FLAG,
                         &b_enable,
                         z_size);
    if (i4_ret != SVCTXR_OK) {
        return MENUR_FAIL;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_is_tv_block
 *
 * Description:
 *  If the tv source is blocked.
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
extern BOOL menu_is_tv_block(VOID)
{
    INT32           i4_ret;
    TV_WIN_ID_T     t_win_id;
    ISL_REC_T       t_isl_rec;
    SVL_REC_T       t_svl_rec;
    BOOL            b_found;
    BOOL            b_block       = FALSE;
    UINT32          ui4_attr_bits = 0;

    do
    {
        i4_ret = a_tv_get_focus_win(&t_win_id);
        if (i4_ret != TVR_OK)
        {
            break;
        }

        i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id, &t_isl_rec);
        if (i4_ret != TVR_OK)
        {
            break;
        }

        if (t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
        {
            break;
        }

        /* check the block value in acfg */
        a_cfg_get_input_src_block (t_isl_rec.ui1_id, &b_block);
        if (b_block == TRUE)
        {
            /* If TV source is blocked, it can be temp-unlocked by ISL_ATTR_BIT_USER_TMP_UNLOCK */
            i4_ret = a_isl_get_attr_bits_by_idx(t_isl_rec.ui1_id, &ui4_attr_bits);
            if (i4_ret != ISLR_OK)
            {
                break;
            }

            if (ui4_attr_bits & ISL_ATTR_BIT_USER_TMP_UNLOCK)
            {
                b_block = FALSE;
                break;
            }

            /* If TV source is blocked, it can also be temp-unlocked by SB_VNET_USER_TMP_UNLOCK */
            i4_ret = menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
            if (i4_ret != MENUR_OK || b_found == FALSE)
            {
                break;
            }

            if ((t_svl_rec.uheader.t_rec_hdr.ui4_option_mask & SB_VOPT_USER_TMP_UNLOCK) > 0)
            {
                b_block = FALSE;
                break;
            }
        }
    } while (FALSE);

    return b_block;
}

/*-----------------------------------------------------------------------------
 * Name: menu_is_crnt_channel_block
 *
 * Description
 *  If the current channel is blocked.
 *
 * Input arguments
 *
 * Output arguments
 *      None
 * Returns
 *      TRUE    Block
 *      FALSE   Normal or temperary unblock
 *---------------------------------------------------------------------------*/
extern BOOL menu_is_crnt_channel_block (VOID)
{
    INT32           i4_ret;
    TV_WIN_ID_T     e_tv_win_id;
    ISL_REC_T       t_isl_rec;
    SVL_REC_T       t_svl_rec;
    BOOL            b_found;

    /* get current isl */
    i4_ret = a_tv_get_focus_win (&e_tv_win_id);
    if (i4_ret != TVR_OK)
    {
        return FALSE;
    }
    i4_ret = a_tv_get_isl_rec_by_win_id (e_tv_win_id, & t_isl_rec);
    if (i4_ret != TVR_OK)
    {
        return FALSE;
    }
    if (t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        return FALSE;
    }

    /* get current channel */
    i4_ret = menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
    if (i4_ret != MENUR_OK || b_found == FALSE)
    {
        return FALSE;
    }

    if ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_BLOCKED) > 0 &&
        (t_svl_rec.uheader.t_rec_hdr.ui4_option_mask & SB_VOPT_USER_TMP_UNLOCK) == 0)
    {
        /* blocked and not be temperarily unblocked by users */
        return TRUE;
    }

    return FALSE;
}

/*----------------------------------------------------------------------------
 * Name: menu_get_crnt_svl
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
HANDLE_T menu_get_crnt_svl(VOID)
{
    INT32  i4_ret;
    UINT16 ui2_crnt_svl_id;

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        return NULL_HANDLE;
    }

    return ((ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID) ?
            t_g_menu_common.h_svl_air :
            t_g_menu_common.h_svl_cable);
}

/*----------------------------------------------------------------------------
 * Name: menu_get_crnt_svl_rec
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
INT32 menu_get_crnt_svl_rec(SVL_REC_T* pt_svl_rec, BOOL* pb_found)
{
    INT32   i4_ret;
    UINT32  ui4_channel_id;
    UINT32  ui4_ver_id;
    HANDLE_T    h_svl;

    if(pt_svl_rec == NULL ||
       pb_found == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* Get the current channel id */
    ui4_channel_id = a_util_cnfg_get_crnt_channel_id();

    /* Get current SVL */
    h_svl = menu_get_crnt_svl();

    /* Find current svl record */
    *pb_found = FALSE;
    if (INVALID_CHANNEL_ID != ui4_channel_id)
    {
        i4_ret = c_svl_get_rec_by_channel(h_svl,
                                          ui4_channel_id,
                                          SB_VNET_ALL,
                                          0,
                                          pt_svl_rec,
                                          &ui4_ver_id);
        if (i4_ret == SVLR_OK)
        {
            *pb_found = TRUE;
        }
    }

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: menu_get_crnt_tsl
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
HANDLE_T menu_get_crnt_tsl(VOID)
{
    INT32  i4_ret;
    UINT16 ui2_crnt_svl_id;

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, NULL);
    if (i4_ret != APP_CFGR_OK)
    {
        return NULL_HANDLE;
    }

    return ((ui2_crnt_svl_id == ATSC_TRSTRL_SVL_ID) ?
            t_g_menu_common.h_tsl_air :
            t_g_menu_common.h_tsl_cable);
}

/*----------------------------------------------------------------------------
 * Name: menu_adjust_vplane
 *
 * Description:
 *       Adjust the video plane and tune to current channel. If the current
 * channel is not avaiable, tune to the first channel. If the SVL is absent,
 * no action is performed.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
INT32 menu_keep_crnt_stream_mode(VOID)
{
    INT32   i4_ret;
    SIZE_T  z_size = sizeof(UINT32);

    i4_ret = c_svctx_get (menu_get_crnt_svctx(),
                          SVCTX_COMMON_GET_STREAM_MODE,
                          &ui4_g_last_strm_mode,
                          &z_size
                          );
    if (i4_ret != SVCTXR_OK)
    {
        ui4_g_last_strm_mode = ST_MASK_VIDEO | ST_MASK_AUDIO;
        return MENUR_FAIL;
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_select_crnt_or_first_channel
 *
 * Description:
 *      Tune to current channel. If the current channel is not avaiable,
 *      tune to the first channel. If the SVL is absent,
 *      no action is performed.
 *
 * Inputs:       b_skip_fake   If current channel is a fake channel, skip it
 *                             or not when iterating a playable channel.
 *
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
INT32 menu_select_crnt_or_first_channel(BOOL b_skip_fake)
{
    INT32                      i4_ret;
    SVL_REC_T                  t_svl_rec          = {0};
    UINT32                     ui4_channel_id     = 0;
    UINT16                     ui2_crnt_svl_id    = ATSC_TRSTRL_SVL_ID;
    CHAR*                      ps_crnt_tuner_name = ATSC_TRSTRL_TUNER_NAME;
    HANDLE_T                   h_crnt_svl         = t_g_menu_common.h_svl_air;
    ISL_REC_T                  t_isl_rec;
    TV_MODE_T                  t_tv_mode;
    TV_WIN_ID_T                t_win_id;

    /* Get current working TV Mode */
    a_tv_get_mode(&t_tv_mode);

    /* Check the input source on FOCUSED WIN */
    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        if(t_tv_mode == TV_MODE_TYPE_NORMAL)
        {
            /* TV_MODE = NORMAL */
            /* Input Src != TV, so, change it to TV */

            a_tv_get_focus_win(&t_win_id);

            i4_ret = a_isl_get_rec_by_type(
                        INP_SRC_TYPE_TV,
                        0,
                        &t_isl_rec
                        );
            if (i4_ret != ISLR_OK) {
                return MENUR_FAIL;
            }

            ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
                DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_set_input_src_id(%d)\n", __FUNCTION__,__LINE__, t_win_id ));
            );

            i4_ret = a_tv_set_input_src_id(t_win_id, t_isl_rec.ui1_id);

            if (i4_ret != TVR_OK) {
                return MENUR_FAIL;
            }

        }
        else if(t_tv_mode == TV_MODE_TYPE_PIP ||
                t_tv_mode == TV_MODE_TYPE_POP)
        {
            /* TV_MODE = PIP/POP */
            /* Focus Win Input Src != TV, don't change anything, return directly */
            return MENUR_OK;
        }
        else
        {
            DBG_ERROR(("[MENU]menu_adjust_vplane can't handle.\n"));
        }
     }

    /* ------------------------------------------------- */

    /* The focus win's input src == INP_SRC_TYPE_TV now */

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, &ps_crnt_tuner_name);
    if (i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }
    h_crnt_svl = menu_get_crnt_svl();

    if (h_crnt_svl == NULL_HANDLE)
    {
        return MENUR_OK;
    }

    if (t_g_menu_common.b_src_dirty == TRUE)
    {
        i4_ret = a_cfg_set_tuner_sync_src(ui2_crnt_svl_id, ps_crnt_tuner_name);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<MENU>Can't notify DT to sync source in menu_adjust_vplane()\r\n"));
            return MENUR_FAIL;
        }
        t_g_menu_common.b_src_dirty = FALSE;
    }

    /* Try to get a proper playable svl_rec */
    /* b_skip_fake argument is taking from outside */

    i4_ret = a_tv_get_crnt_or_first_svl_rec(h_crnt_svl, b_skip_fake, &t_svl_rec);

    if(i4_ret != TVR_OK)
    {
        i4_ret = a_tv_stop(menu_get_crnt_svctx());

        if (i4_ret != TVR_OK)
        {
            DBG_ERROR (("<MENU> Stop service failed = %d\n\r", i4_ret));
        }

        return MENUR_OK;
    }
    else
    {
        ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;
    }

    /* Successfully get a playable svl_rec, so play it */
    if(t_tv_mode != TV_MODE_TYPE_NORMAL)
    {
        /* If PIP/POP mode, use the last stream mode. */
        i4_ret = a_tv_change_channel(menu_get_crnt_svctx(),
                                     ui4_g_last_strm_mode,
                                     ui4_channel_id,
                                     NULL);
    }
    else
    {
        /* If normal mode, always play video and audio */
        i4_ret = a_tv_change_channel(menu_get_crnt_svctx(),
                                     ST_MASK_VIDEO | ST_MASK_AUDIO,
                                     ui4_channel_id,
                                     NULL);
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_adjust_vplane
 *
 * Description:
 *       Adjust the video plane and tune to current channel. If the current
 * channel is not avaiable, tune to the first channel. If the SVL is absent,
 * no action is performed.
 *
 *       Remark: If the current channel is a fake channel, it will be skipped,
 *               and find next un-fake channel.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/

INT32 menu_adjust_vplane(VOID)
{
    return menu_select_crnt_or_first_channel(TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: menu_common_init
 *
 * Description: The initaiting function of "common-part" menu
 *
 * Inputs:  ps_name             References the application's name.
 *          h_app               Contains the application handle.
 *
 * Outputs: -
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
INT32 menu_common_init(VOID)
{
    SM_COMMAND_T at_sm_cmds[3];
    INT32 i4_ret;
    do
    {
        /* Open Service Context (MAIN) */
        MENU_TMS_SPLIT("open svctx main");
        i4_ret = c_svctx_open(SVCTX_NAME_MAIN,    /* defined in a_common.h*/
                              &t_g_menu_common.h_svctx);
        if (i4_ret != 0)
        {
            break;
        }

        /* Open Service Context (SUB) */
        MENU_TMS_SPLIT("open svctx main");
        i4_ret = c_svctx_open(SVCTX_NAME_SUB,    /* defined in a_common.h*/
                              &t_g_menu_common.h_svctx_sub);
        if (i4_ret != 0)
        {
            break;
        }

        /* Open Service Context (MAIN) */
        MENU_TMS_SPLIT("open scan svctx main");
        i4_ret = c_svctx_open(SVCTX_NAME_MAIN,    /* defined in a_common.h*/
                              &t_g_menu_common.h_scan_svctx);
        if (i4_ret != 0)
        {
            break;
        }

        /* Open Service Context (SUB) */
        MENU_TMS_SPLIT("open scan svctx sub");
        i4_ret = c_svctx_open(SVCTX_NAME_SUB,    /* defined in a_common.h*/
                              &t_g_menu_common.h_scan_svctx_sub);
        if (i4_ret != 0)
        {
            break;
        }

        /* Open SVL */
        MENU_TMS_SPLIT("open svl");
        i4_ret = c_svl_open(ATSC_TRSTRL_SVL_ID, /* defined in a_common.h*/
                            NULL,
                            NULL,
                            &t_g_menu_common.h_svl_air);
        if (i4_ret != SVLR_OK)
        {
            DBG_ERROR(("<MENU>Can't open AIR SVL\r\n"));
            t_g_menu_common.h_svl_air = NULL_HANDLE;
        }

        i4_ret = c_svl_open(ATSC_CABLE_SVL_ID, /* defined in a_common.h*/
                            NULL,
                            NULL,
                            &t_g_menu_common.h_svl_cable);
        if (i4_ret != SVLR_OK)
        {
            DBG_ERROR(("<MENU>Can't open CABLE SVL\r\n"));
            t_g_menu_common.h_svl_cable = NULL_HANDLE;
        }

        /* Open TSL */
        MENU_TMS_SPLIT("open tsl");
        i4_ret = c_tsl_open(ATSC_TRSTRL_TSL_ID, /* defined in a_common.h*/
                            NULL,
                            NULL,
                            &t_g_menu_common.h_tsl_air);
        if (i4_ret != TSLR_OK)
        {
            DBG_ERROR(("<MENU>Can't open AIR TSL\r\n"));
            t_g_menu_common.h_tsl_air = NULL_HANDLE;
        }

        i4_ret = c_tsl_open(ATSC_CABLE_TSL_ID, /* defined in a_common.h*/
                            NULL,
                            NULL,
                            &t_g_menu_common.h_tsl_cable);
        if (i4_ret != TSLR_OK)
        {
            DBG_ERROR(("<MENU>Can't open CABLE TSL\r\n"));
            t_g_menu_common.h_tsl_cable = NULL_HANDLE;
        }

#ifndef APP_LOL_NWL_DISABLE
        /* open nwl */
        i4_ret = c_nwl_open (ATSC_TRSTRL_NWL_ID,
                            NULL,
                            NULL,
                            & t_g_menu_common.h_nwl_air) ;
        if (i4_ret != NWLR_OK)
        {
            DBG_ERROR(("<MENU>Can't open AIR NWL\r\n"));
            t_g_menu_common.h_nwl_air = NULL_HANDLE;
        }

        /* open lol */
        i4_ret = c_lol_open (ATSC_TRSTRL_LOL_ID,
                            NULL,
                            NULL,
                            & t_g_menu_common.h_lol_air) ;
        if (i4_ret != LOLR_OK)
        {
            DBG_ERROR(("<MENU>Can't open AIR LOL\r\n"));
            t_g_menu_common.h_lol_air = NULL_HANDLE;
        }
#endif /* APP_LOL_NWL_DISABLE */
#ifdef APP_DVBC_SUPPORT
#ifndef APP_LOL_NWL_DISABLE
        i4_ret = c_nwl_open (ATSC_CABLE_NWL_ID,
                            NULL,
                            NULL,
                            & t_g_menu_common.h_nwl_cable) ;
        if (i4_ret != NWLR_OK)
        {
            DBG_ERROR(("<MENU>Can't open CABLE NWL\r\n"));
            t_g_menu_common.h_nwl_cable = NULL_HANDLE;
        }

        i4_ret = c_lol_open (ATSC_CABLE_LOL_ID,
                            NULL,
                            NULL,
                            & t_g_menu_common.h_lol_cable) ;
        if (i4_ret != LOLR_OK)
        {
            DBG_ERROR(("<MENU>Can't open CABLE LOL\r\n"));
            t_g_menu_common.h_lol_cable = NULL_HANDLE;
        }
#endif
#endif
        /*Open SCC AUD*/
        MENU_TMS_SPLIT("open scc aud");
        at_sm_cmds[0].e_code     = SCC_CMD_CODE_GRP_TYPE;
        at_sm_cmds[0].u.ui4_data = SCC_CMD_TYPE_AUDIO;
        at_sm_cmds[1].e_code     = SCC_CMD_CODE_NAME;
        at_sm_cmds[1].u.ps_text  = SN_PRES_MAIN_DISPLAY;
        at_sm_cmds[2].e_code = SM_CMD_CODE_END;
        at_sm_cmds[2].u.ui4_data = 0;
        i4_ret = c_scc_comp_open(at_sm_cmds, &t_g_menu_common.h_scc_aud);
        if(i4_ret != SMR_OK)
        {
            DBG_ERROR(("<MENU>Can't Open SCC handle"));
            t_g_menu_common.h_scc_aud = NULL_HANDLE;
        }

        MENU_TMS_SPLIT("init pages");

		i4_ret = menu_page_pic_mode_init();
		MENU_CHK_FAIL(i4_ret);

		i4_ret = menu_page_gaming_mode_init();
		MENU_CHK_FAIL(i4_ret);

		i4_ret = menu_common_page_picture_quality_init();
		MENU_CHK_FAIL(i4_ret);

		i4_ret = menu_common_page_white_balance_tuner_init();
		MENU_CHK_FAIL(i4_ret);

		i4_ret = menu_page_create_new_pic_mode_init();
		MENU_CHK_FAIL(i4_ret);

		i4_ret = menu_page_pic_mode_edit_init();
		MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_page_lock_pic_mode_lb2_init();
        MENU_CHK_FAIL(i4_ret);

		i4_ret = menu_page_color_calibration_init();
		MENU_CHK_FAIL(i4_ret);

		i4_ret =  menu_page_lock_new_pic_mode_init();
		MENU_CHK_FAIL(i4_ret);

		i4_ret =  menu_page_unlock_new_pic_mode_init();
		MENU_CHK_FAIL(i4_ret);

		i4_ret =  menu_page_delete_new_pic_mode_init();
		MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_page_audio_dbginfo_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_page_hdmi_dbginfo_init();
        MENU_CHK_FAIL(i4_ret);

		i4_ret =  menu_common_page_test_special_param_init();
		MENU_CHK_FAIL(i4_ret);

#ifdef APP_LOG2USB_SUPPORT
        i4_ret =  menu_common_page_log_to_usb_init();
        MENU_CHK_FAIL(i4_ret);
#endif
#ifdef COMMON_PWD_ENABLE
        i4_ret = menu_common_page_pwd_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_PWD_ENABLE
        i4_ret = menu_clear_memory_pwd_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_CHG_PWD_ENABLE
        i4_ret = menu_common_page_chg_pwd_init();
        MENU_CHK_FAIL(i4_ret);
#endif
        i4_ret = menu_common_page_sys_pin_init();
        MENU_CHK_FAIL(i4_ret);

#ifdef COMMON_CH_LST2_ENABLE
        i4_ret = menu_common_page_ch_lst2_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_VER_INFO_ENABLE
        i4_ret = menu_common_page_ver_info_init();
        MENU_CHK_FAIL(i4_ret);
#ifdef APP_EMANUAL_SP6_SUPPORT
                i4_ret = menu_page_mc_ver_init();
                MENU_CHK_FAIL(i4_ret);
#endif
#endif

#ifdef COMMON_FE_CHK_ENABLE
        i4_ret = menu_common_page_fe_chk_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_DIVX_INFO_ENABLE
#ifdef DIVX_DRM_40
        i4_ret = menu_common_page_divx_info_init();
        MENU_CHK_FAIL(i4_ret);
#endif /* DIVX_DRM_40 */
#ifdef DIVX_DRM_51
        i4_ret = menu_common_page_divx_info_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_common_page_divx_deact_init();
        MENU_CHK_FAIL(i4_ret);
#endif /* DIVX_DRM_51 */
#endif /* COMMON_DIVX_INFO_ENABLE */

#ifdef COMMON_SIMPLE_DIALOG_ENABLE
        i4_ret = menu_common_page_simple_dialog_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_VGA_AUTO_ENABLE
        i4_ret = menu_common_page_vga_auto_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_AUTO_COLOR_ENABLE
        i4_ret = menu_common_page_auto_color_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_AUTO_PHASE_ENABLE
        i4_ret = menu_common_page_auto_phase_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_INP_LST_ENABLE
        i4_ret = menu_common_page_inp_lst_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_INP_SRC_ENABLE
        i4_ret = menu_common_page_inp_src_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_INP_SRC_NAMING_ENABLE
        i4_ret = menu_common_page_naming_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_GUI_TIME_ZONE_SELECTION
       i4_ret = menu_custom_page_time_zone_init();
       MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_DATE_TIME_ENABLE
        i4_ret = menu_common_page_date_time_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_BURN_ENABLE
        i4_ret = menu_common_page_burn_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_IMG_CLNR_ENABLE
        i4_ret = menu_common_page_img_clnr_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_AUD_FAC_ENABLE
        i4_ret = menu_common_page_aud_fac_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_TUNER_FAC_ENABLE
        i4_ret = menu_common_page_tuner_fac_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_MJC_DEMO_ENABLE
        i4_ret = menu_common_page_mjc_demo_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef  COMMON_VGA_AMBIGUOUS_ENABLE
        i4_ret = menu_common_vga_ambigous_init();
        MENU_CHK_FAIL(i4_ret);
#endif

    /* menu page animation */
    i4_ret = menu_page_animation_init();
    MENU_CHK_FAIL(i4_ret);

#ifdef COMMON_EX_MAIN_MENU_ENABLE
        i4_ret = menu_page_ex_main_menu_init();
        MENU_CHK_FAIL(i4_ret);
#endif

#ifdef COMMON_EX_MASTERLIST_ENABLE
        i4_ret = menu_ex_page_masterlist_init() ;
        MENU_CHK_FAIL (i4_ret);
#endif

#ifdef COMMON_EX_CH_EDIT_ENABLE
        i4_ret = menu_page_ex_ch_edit_init() ;
        MENU_CHK_FAIL (i4_ret);
#endif

        i4_ret = menu_page_inp_edit_init ();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_page_screen_mode_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_page_aspec_ratio_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_page_sb_setting_eq_mode_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_page_tv_name_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_common_settings_init();
        MENU_CHK_FAIL(i4_ret);
        MENU_TMS_SPLIT("common_init_done");

        i4_ret = menu_common_page_terms_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_common_page_sub_terms_init();
        MENU_CHK_FAIL(i4_ret);

        i4_ret = menu_common_page_acr_init();
        MENU_CHK_FAIL(i4_ret);

#ifdef APP_CEC_MENU
        i4_ret = menu_common_page_cec_init();
        MENU_CHK_FAIL(i4_ret);
#endif
        i4_ret = menu_common_page_scrn_blank_init();
        MENU_CHK_FAIL(i4_ret);

        t_g_menu_hot_key_info.ui4_hot_key_num = 0;

    }while(0);

    t_g_menu_is_scanning = FALSE;
    t_g_menu_enable_channel_change = TRUE;

    if(i4_ret != MENUR_OK)
    {
        return AEER_FAIL;
    }
    else
    {
        return AEER_OK;
    }
}


INT32 menu_common_pause(VOID)
{
    menu_async_invoke(_do_store_cfg, NULL, 0, FALSE);

    if (t_g_menu_common.b_src_dirty == TRUE)
    {
        _ASYNC_INVOKE(_do_sync_src, NULL, 0, FALSE);
        t_g_menu_common.b_src_dirty = FALSE;
    }

    /* Because [DTV00130467], we don't call store channel list here.
       Move to the last step in function _menu_app_pause_fct() */

    return AEER_OK;
}

INT32 menu_common_resume(VOID)
{
#ifdef APP_PIP_POP_CTRL
    a_pop_sync_hide_warning_osd ();
#endif
    menu_main_update_input_ind();

    t_g_menu_is_scanning = FALSE;
    t_g_menu_enable_channel_change = TRUE;

    /* tirgger to store svl/tsl in both main and sub of dual bank */
    t_g_menu_common.b_dual_bank_dirty = FALSE;

    MENU_TMS_SPLIT("common_resume_done");
    return AEER_OK;
}

CHIPSET menu_common_get_chipset(VOID)
{
#ifdef MT5691_MODEL
    return CHIPSET_5691;
#endif

#ifdef MT5695_MODEL
    return CHIPSET_5695;
#endif

#ifdef MT5695L_MODEL
    return CHIPSET_5695L;
#endif

#ifdef MT5583_MODEL
    return CHIPSET_5583;
#endif
    return CHIPSET_UNKNOW;
}


INT32 menu_common_exit(VOID)
{
#ifndef APP_LOL_NWL_DISABLE
    /* close nwl */
    if (t_g_menu_common.h_nwl_air != NULL_HANDLE)
    {
        c_nwl_close(t_g_menu_common.h_nwl_air);
        t_g_menu_common.h_nwl_air = NULL_HANDLE;
    }

    /* close lol */
    if (t_g_menu_common.h_lol_air != NULL_HANDLE)
    {
        c_lol_close(t_g_menu_common.h_lol_air);
        t_g_menu_common.h_lol_air = NULL_HANDLE;
    }
#endif
#ifdef APP_DVBC_SUPPORT
    if (t_g_menu_common.h_nwl_cable != NULL_HANDLE)
    {
        c_nwl_close(t_g_menu_common.h_nwl_cable);
        t_g_menu_common.h_nwl_cable = NULL_HANDLE;
    }

    if (t_g_menu_common.h_lol_cable != NULL_HANDLE)
    {
        c_lol_close(t_g_menu_common.h_lol_cable);
        t_g_menu_common.h_lol_cable = NULL_HANDLE;
    }
#endif

    return AEER_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_common_process_msg
 *
 * Description: Process the "common-part" menu messages.
 *
 * Inputs:  h_app               Contains the application handle.
 *          ui4_type            Contains the type of the data contained in
 *                              pv_msg, or simple a request type. Values are
 *                              defined by the application.
 *          pv_msg              References the message data.
 *          z_msg_len           Contains the length (in bytes) of pv_msg.
 *          b_paused            Sepcifies whether the application is currently
 *                              paused.
 *
 * Outputs: -
 *          pb_processed        Output TRUE if the message has been procesed;
 *                              Otherwise, output FALSE.
 *
 * Returns: AEER_OK             Routine successful.
 *          Any other value     Routine failed.
 ----------------------------------------------------------------------------*/
INT32 menu_common_process_msg (
    UINT32       ui4_type,
    const VOID*  pv_msg,
    SIZE_T       z_msg_len,
    BOOL*        pb_processed)
{
    INT32  i4_ret                = MENUR_OK;
    BOOL   b_processed             = FALSE;

    MENU_ASSERT(pb_processed != NULL);

    if(pb_processed == NULL)
    {
        return MENUR_FAIL;
    }

    *pb_processed = FALSE;

    b_processed = FALSE;

    switch (ui4_type)
    {
    case MENU_MSG_WGL_NOTIFY:
        {
            MENU_MSG_WGL_NOTIFY_T*  pt_msg_wgl_notify = (MENU_MSG_WGL_NOTIFY_T*)pv_msg;
            UINT32  ui4_key = (UINT32)pt_msg_wgl_notify->pv_param1;

            if (t_g_menu_is_scanning == TRUE)
            {
                break;
            }

            if ((pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN) ||
                (pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_REPEAT))
            {
                MENU_DEBUG_KEY(
                    DBG_LOG_PRINT(("[MENU][KEY]{%s,%d} ui4_key:0x%X\n", __FUNCTION__, __LINE__, ui4_key )); );

                switch (ui4_key)
                {
                case BTN_PIP_POP:
                case BTN_POP:
                case BTN_PIP:
                    menu_leave (FALSE, 0);
                    /* no break. */
                case BTN_INPUT_SRC:
                    /* Call default key handler. */
                    a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key, NULL);
                    b_processed = TRUE;
                    break;
                case BTN_MUTE:
                case BTN_VOL_DOWN:
                case BTN_VOL_UP:
				case BTN_SHOW_VOL_BAR:
                    /* Call default key handler. */
                    a_amb_default_key_handler_ex (pt_msg_wgl_notify->ui4_msg, (VOID*)ui4_key, NULL);
                    b_processed = TRUE;
                    break;
                case BTN_BLUE:
                {
                    BOOL        b_is_main_menu_visible = TRUE;
                    HANDLE_T    h_main_frm;

                    b_processed = TRUE;
                    menu_pm_get_main_frm(&h_main_frm);
                    i4_ret = c_wgl_get_visibility(h_main_frm, &b_is_main_menu_visible);
                    if (i4_ret != WGLR_OK)
                    {
                        b_is_main_menu_visible = TRUE;
                    }
                    if (b_is_main_menu_visible == TRUE)
                    {
                        UINT8 ui1_sts = ICL_VIEWPORT_LAST_REQ_FAIL;

                        if (!a_cfg_is_able_to_apply_viewport ())
                        {
                            ui1_sts = ICL_VIEWPORT_LAST_REQ_FAIL;
                            i4_ret = a_icl_set (
                                ICL_MAKE_ID(ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                                (VOID *) &ui1_sts,
                                ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE);
                        }
                        else
                        {
                            ui1_sts = ICL_VIEWPORT_LAST_REQ_SUCCEED;
                            i4_ret = a_icl_set (
                                ICL_MAKE_ID(ICL_GRPID_VIEWPORT, ICL_RECID_VIEWPORT_LAST_REQ_STS),
                                (VOID *) &ui1_sts,
                                ICL_RECID_VIEWPORT_LAST_REQ_STS_SIZE);

                            a_cfg_set_next_viewport ();
                            a_cfg_update_viewport ();
                        }
                    }
                    else
                    {
                        return MENUR_OK;
                    }
                    break;
                }
                default:
                    break;
                }

                if ( pt_msg_wgl_notify->ui4_msg == WGL_MSG_KEY_DOWN)
                {

                    if (ui4_key == BTN_PREV_PRG)
                    {
                        i4_ret = _do_Prev_Prg(&b_processed);
                        if (i4_ret != MENUR_OK)
                        {
                            return MENUR_FAIL;
                        }
                    }
                    else if (ui4_key==BTN_PRG_UP || ui4_key==BTN_PRG_DOWN)
                    {
                        if(t_g_menu_is_scanning == TRUE ||
                           t_g_menu_enable_channel_change == FALSE)
                        {                             /* Forbid to change channel */
                            b_processed = FALSE;
                        }
                        else                          /* Menu is not SCANNING and is available to change channel */
                        {
                            APP_TV_NET_SVC_STATUS t_svc_state = APP_TV_NET_SVC_STATUS_PAUSED;
                            TV_MODE_T             e_tv_mode = TV_MODE_TYPE_NORMAL;
                        #ifdef APP_MENU_MMP_COEXIST
                            MMP_MAIN_AP_STATUS_T    e_mmp_status = MMP_MAIN_AP_STATUS_DEINITED;
                        #endif

                            t_svc_state = a_tv_net_get_tv_svc_status();
                            if(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
                            {
                                b_processed = TRUE;
                                break;
                            }

                        #ifdef APP_MENU_MMP_COEXIST
                            e_mmp_status = a_mmp_get_ap_status();
                            if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_mmp_status)
                            {
                                b_processed = TRUE;
                                break;
                            }
                        #endif

                            i4_ret = a_tv_get_mode(&e_tv_mode);
                            if (i4_ret != TVR_OK)
                            {
                                b_processed = FALSE;
                            }

                            if (e_tv_mode == TV_MODE_TYPE_NORMAL)
                            {
                                ISL_REC_T    t_isl_rec;

                                c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));
                                menu_get_crnt_isl(&t_isl_rec);

                                if (t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
                                {
                                    /* When the focus win's input src != TV,
                                       forbid user to change channel */
                                    b_processed = FALSE;
                                }
                                else if ((t_isl_rec.ui4_attr_bits & ISL_ATTR_BIT_BLOCKED) > 0          &&
                                         (t_isl_rec.ui4_attr_bits & ISL_ATTR_BIT_USER_TMP_UNLOCK) == 0 &&
                                         t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
                                {
                                    /* TV is blocked and isn't unlocked temporarily */
                                    b_processed = FALSE;
                                }
                                else
                                {
                                    /* Call default key handler. */
                                    //a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key, NULL);
                                    HANDLE_T    h_main_frm = NULL_HANDLE;
                                    BOOL        b_visible = FALSE;

                                    menu_pm_get_main_frm(&h_main_frm);
                                    c_wgl_get_visibility(h_main_frm, &b_visible);

                                    if (!b_visible)
                                    {
                                        if (t_g_menu_common.b_is_hot_key_enter == TRUE)
                                        {
                                            menu_leave (TRUE, MENU_PM_HIDE_DELAY);
                                            a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key, NULL);
                                        }
                                        else
                                        {
                                        #ifdef APP_CAST_TEST_PATTERN
                                            /* if pattern is on ,exit pattern ,then ch+/- */
                                            a_menu_test_patterns_turn_off();
                                        #endif
                                            _do_channel_change(t_g_menu_common.h_svctx, ui4_key);

                                            b_processed = TRUE;
                                            menu_nav_go_home_menu();
                                        }
                                    }
                                    else
                                    {
                                        _do_channel_change(t_g_menu_common.h_svctx, ui4_key);
                                        b_processed = TRUE;
                                    }
                                }
                            }
                            else
                            {
                                ISL_REC_T    t_isl_rec_main;
                                ISL_REC_T    t_isl_rec_sub;

                                c_memset(&t_isl_rec_main, 0, sizeof(ISL_REC_T));
                                c_memset(&t_isl_rec_sub, 0, sizeof(ISL_REC_T));
                                a_tv_get_isl_rec_by_win_id(TV_WIN_ID_MAIN, &t_isl_rec_main);
                                a_tv_get_isl_rec_by_win_id(TV_WIN_ID_SUB, &t_isl_rec_sub);

                                if (t_isl_rec_main.e_src_type == INP_SRC_TYPE_TV)
                                {
                                    _do_channel_change(t_g_menu_common.h_svctx, ui4_key);
                                    b_processed = TRUE;
                                }

                                if (t_isl_rec_sub.e_src_type == INP_SRC_TYPE_TV)
                                {
                                    _do_channel_change(t_g_menu_common.h_svctx_sub, ui4_key);
                                    b_processed = TRUE;
                                }

                            }
                        }
                    }

                    else if (ui4_key == BTN_DIGIT_0 || ui4_key == BTN_DIGIT_1 || ui4_key == BTN_DIGIT_2
                             || ui4_key == BTN_DIGIT_3 || ui4_key == BTN_DIGIT_4 || ui4_key == BTN_DIGIT_5
                             || ui4_key == BTN_DIGIT_6 || ui4_key == BTN_DIGIT_7 || ui4_key == BTN_DIGIT_8
                             || ui4_key == BTN_DIGIT_9 || ui4_key == BTN_DIGIT_DOT || ui4_key == BTN_KB_MINUS_SIGN)
                    {
                        BOOL b_is_digital_key_in_menu;
						#ifdef ENABLE_SWITCH_CH_IN_MAIN_MENU_PAGE
						UINT32          ui4_page_id = 0;
						#endif

                        b_is_digital_key_in_menu = _is_digital_key_in_menu();

                        if (b_is_digital_key_in_menu == FALSE)
                        {
                            APP_TV_NET_SVC_STATUS t_svc_state = APP_TV_NET_SVC_STATUS_PAUSED;

                            t_svc_state = a_tv_net_get_tv_svc_status();

							#ifdef APP_MENU_MMP_COEXIST
							if((APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state) ||
								(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == a_mmp_get_ap_status()))
							#else
							if(APP_TV_NET_SVC_STATUS_RESUMED == t_svc_state)
							#endif
                            {
                                b_processed = TRUE;
                                break;
                            }

                            /* Call default key handler. fix DTV00877049 */
                            //a_amb_default_key_handler (WGL_MSG_KEY_DOWN, (VOID*)ui4_key, NULL);
							#ifdef ENABLE_SWITCH_CH_IN_MAIN_MENU_PAGE
							menu_nav_get_crnt_page(&ui4_page_id);
							if(ui4_page_id == ui4_g_menu_page_main_menu)
							{
								b_processed = FALSE;
							}
							else
							{
                                b_processed = TRUE;
                            }
							#else
								b_processed = TRUE;
							#endif
                        }
                    }

                }

            }
        }
        break;
    }

    if(b_processed)
    {
        *pb_processed = TRUE;
        return i4_ret;
    }

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: menu_common_help_show_back
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_common_help_show_back(VOID)
{
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_common_help_show_back
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_common_help_show_select_back(VOID)
{
    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_common_store_ch_list
 *
 * Description:
 *  This function is to store channel list asynchronously and supposed to be used
 *  by menu.c only.
 *
 *  The store channel list should be after the _page_lose_focus() and _page_hide().
 *  Because there is some SVL operation is at these functions.
 *
 *  NOTE: This function is asyncrhounously and will check the dirty flag
 *    Please don't call this function instead of menu.c
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_common_store_ch_list(VOID)
{
#ifdef APP_SVL_TSL_DUAL_BANK_SUPPORT
    /*  Description:
            The SVL/TSL of Air and Cable will be not consistent after the following steps.
        Repeat steps:
            1. Scan Air -> Exit Menu -> AC Off
                a. Load channels from Sub bank. (Empty channels)
                b. Air channels are stored in Main bank.
            2. Switch to Cable -> Scan Cable -> Exit -> AC Off
                a. Load channels from Main bank. (Air channels)
                b. Cable channels are stored in Sub bank.
            3. Check Air channels and Cable channels.
                a. Load channels from Sub bank (Cable channels)
                b. Non-Consistent: Cable channels (OK), Air No Cahnnels (NG)
                c. Expect: Air channels and Cable channels.
    */
    if (t_g_menu_common.b_svl_air_dirty ||
        t_g_menu_common.b_svl_cable_dirty)
    {
        t_g_menu_common.b_svl_air_dirty   = TRUE;
        t_g_menu_common.b_svl_cable_dirty = TRUE;
    }

    if (t_g_menu_common.b_tsl_air_dirty ||
        t_g_menu_common.b_tsl_cable_dirty)
    {
        t_g_menu_common.b_tsl_air_dirty   = TRUE;
        t_g_menu_common.b_tsl_cable_dirty = TRUE;
    }
#endif

    /* Store AIR's SVL,TSL,NWL,LOL */
    if (t_g_menu_common.b_svl_air_dirty == TRUE ||
        t_g_menu_common.b_tsl_air_dirty == TRUE)
    {
        _ASYNC_INVOKE(_do_store_svl_air, NULL, 0, FALSE);
        t_g_menu_common.b_svl_air_dirty = FALSE;

        _ASYNC_INVOKE(_do_store_tsl_air, NULL, 0, FALSE);
        t_g_menu_common.b_tsl_air_dirty = FALSE;
#ifndef APP_LOL_NWL_DISABLE
        _ASYNC_INVOKE(_do_store_nwl_air, NULL, 0, FALSE);
        _ASYNC_INVOKE(_do_store_lol_air, NULL, 0, FALSE);
#endif
    }

    /* Store CABLE's SVL,TSL,NWL,LOL */
    if (t_g_menu_common.b_svl_cable_dirty == TRUE ||
        t_g_menu_common.b_tsl_cable_dirty == TRUE)
    {
        _ASYNC_INVOKE(_do_store_svl_cable, NULL, 0, FALSE);
        t_g_menu_common.b_svl_cable_dirty = FALSE;

        _ASYNC_INVOKE(_do_store_tsl_cable, NULL, 0, FALSE);
        t_g_menu_common.b_tsl_cable_dirty = FALSE;
#ifndef APP_LOL_NWL_DISABLE
        _ASYNC_INVOKE(_do_store_nwl_cable, NULL, 0, FALSE);
        _ASYNC_INVOKE(_do_store_lol_cable, NULL, 0, FALSE);
#endif
    }

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_get_crnt_tv_mode_and_isl
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_get_crnt_tv_mode_and_isl_rec(TV_MODE_T* pt_tv_mode,
                                               ISL_REC_T* pt_isl_rec)
{
    INT32          i4_ret;
    TV_WIN_ID_T    t_win_id;

    i4_ret = a_tv_get_mode(pt_tv_mode);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_tv_get_focus_win(&t_win_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id,
                                        pt_isl_rec);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: menu_get_crnt_svctx
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern HANDLE_T menu_get_crnt_svctx(VOID)
{
    TV_WIN_ID_T     t_win_id;

    a_tv_get_focus_win(&t_win_id);

    if(t_win_id == TV_WIN_ID_MAIN)
    {
        return t_g_menu_common.h_svctx;
    }
    else if(t_win_id == TV_WIN_ID_SUB)
    {
        return t_g_menu_common.h_svctx_sub;
    }
    else
    {
        DBG_ERROR(("[MENU] Could not get current svctx. \n"));
    }

    return NULL_HANDLE;
}

/*-----------------------------------------------------------------------------
 * Name: menu_get_crnt_scan_svctx
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern HANDLE_T menu_get_crnt_scan_svctx(VOID)
{
    TV_WIN_ID_T     t_win_id;

    a_tv_get_focus_win(&t_win_id);

    if(t_win_id == TV_WIN_ID_MAIN)
    {
        return t_g_menu_common.h_scan_svctx;
    }
    else if(t_win_id == TV_WIN_ID_SUB)
    {
        return t_g_menu_common.h_scan_svctx_sub;
    }
    else
    {
        DBG_ERROR(("[MENU] Could not get current svctx. \n"));
    }

    return NULL_HANDLE;
}

/*-----------------------------------------------------------------------------
 * Name: menu_get_current_svctx (deprecated)
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern HANDLE_T menu_get_current_svctx(VOID)
{
    return menu_get_crnt_svctx();
}

/*-----------------------------------------------------------------------------
 * Name: menu_get_crnt_svctx
 *
 * Description: -
 *
 * Inputs: -
 *
 * Outputs: -
 *
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 menu_get_crnt_isl(ISL_REC_T* pt_isl_rec)
{
    INT32           i4_ret;
    TV_WIN_ID_T     t_win_id;

    i4_ret = a_tv_get_focus_win(&t_win_id);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = a_tv_get_isl_rec_by_win_id(t_win_id,
                                        pt_isl_rec);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: menu_is_signal_loss
 *
 * Description:
 *  Check if it is in signal loss status.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern BOOL  menu_is_signal_loss(VOID)
{
    INT32       i4_ret;
    HANDLE_T    h_svctx;
    BOOL        b_signal_loss = FALSE;

    h_svctx = menu_get_crnt_svctx();

    i4_ret = c_svctx_is_signal_loss(h_svctx, &b_signal_loss);
    if(i4_ret != MENUR_OK)
    {
        return TRUE;
    }

    return b_signal_loss;
}

/*----------------------------------------------------------------------------
 * Name: menu_is_video_block
 *
 * Description:
 *  Check if it is in signal loss status.
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
extern BOOL  menu_is_video_block(VOID)
{
    INT32       i4_ret;
    HANDLE_T    h_svctx;
    SIZE_T      z_get_info_size = sizeof(BOOL);
    BOOL        b_is_blocked     = FALSE;

    h_svctx = menu_get_crnt_svctx();

    i4_ret = c_svctx_get(
        h_svctx,
        SVCTX_COMMON_GET_TYPE_IS_BLOCK,
        &b_is_blocked,
        &z_get_info_size
    );

    if(i4_ret != MENUR_OK)
    {
        MENU_LOG_ON_FAIL(i4_ret);
        return FALSE;
    }

    return b_is_blocked;
}

/*-----------------------------------------------------------------------------
 * Name: menu_is_digital_tv
 *
 * Description
 *      The API is used to check current content of a specific TV window
 *      is from digital TV or not.
 * Input arguments
 *      e_tv_win_id     the target TV window ID
 * Output arguments
 *      None
 * Returns
 *      TRUE    It is analog TV
 *      FALSE   It is not analog TV.
 *---------------------------------------------------------------------------*/
extern BOOL menu_is_digital_tv (TV_WIN_ID_T  e_tv_win_id)
{
    INT32       i4_ret;
    ISL_REC_T   t_isl_rec;
    SVL_REC_T   t_svl_rec;
    BOOL        b_found;

    /* get current isl */
    i4_ret = a_tv_get_isl_rec_by_win_id (e_tv_win_id, & t_isl_rec);
    if (i4_ret != TVR_OK)
    {
        return FALSE;
    }
    if (t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        return FALSE;
    }

    /* check the current channel */
    i4_ret = menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
    if (i4_ret != MENUR_OK || b_found == FALSE)
    {
        return FALSE;
    }

    if(t_svl_rec.uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
    {
        /* Analog TV */
        return FALSE;
    }

    /* digital TV */
    return TRUE;
}
/*----------------------------------------------------------------------------
 * Name: menu_add_analog_select_channel
 *
 * Description:
 *
 * Inputs:
 *
 *
 * Outputs:
 *
 * Returns:
 *      MENUR_OK        Successful
 *      MENUR_FAIL      Fail
 ----------------------------------------------------------------------------*/
INT32 menu_add_analog_select_channel(UINT32  ui4_channel_num, BOOL* pb_found)
{
    INT32              i4_ret = -1;
    SVL_REC_T          t_svl_rec;
    HANDLE_T           h_crnt_svl         = t_g_menu_common.h_svl_air;
    UINT16             ui2_crnt_svl_id    = ATSC_TRSTRL_SVL_ID;
    CHAR*              ps_crnt_tuner_name = ATSC_TRSTRL_TUNER_NAME;
    ISL_REC_T          t_isl_rec;
    TV_MODE_T          t_tv_mode;
    TV_WIN_ID_T        t_win_id;
    BOOL               b_found = FALSE;
    UINT32             ui4_channel_id = 0;
	UINT32      	   ui4_old_channel_id = INVALID_CHANNEL_ID;

    /* Get current working TV Mode */
    a_tv_get_mode(&t_tv_mode);

    /* Check the input source on FOCUSED WIN */
    menu_get_crnt_isl(&t_isl_rec);

    if(t_isl_rec.e_src_type != INP_SRC_TYPE_TV)
    {
        if(t_tv_mode == TV_MODE_TYPE_NORMAL)
        {
            /* TV_MODE = NORMAL */
            /* Input Src != TV, so, change it to TV */

            a_tv_get_focus_win(&t_win_id);

            i4_ret = a_isl_get_rec_by_type(
                        INP_SRC_TYPE_TV,
                        0,
                        &t_isl_rec
                        );
            if (i4_ret != ISLR_OK) {
                return MENUR_FAIL;
            }

            ACFG_DEBUG_LOG( ACFG_DBG_INPUT_CHG,
                DBG_LOG_PRINT(("[MENU][INPUT_SRC]{%s,%d} call a_tv_set_input_src_id(%d)\n", __FUNCTION__,__LINE__, t_win_id ));
            );

            i4_ret = a_tv_set_input_src_id(t_win_id, t_isl_rec.ui1_id);

            if (i4_ret != TVR_OK) {
                return MENUR_FAIL;
            }

        }
        else if(t_tv_mode == TV_MODE_TYPE_PIP ||
                t_tv_mode == TV_MODE_TYPE_POP)
        {
            /* TV_MODE = PIP/POP */
            /* Focus Win Input Src != TV, don't change anything, return directly */
            return MENUR_OK;
        }
        else
        {
            DBG_ERROR(("[MENU]menu_adjust_vplane can't handle.\n"));
        }
     }

    /* ------------------------------------------------- */

    /* The focus win's input src == INP_SRC_TYPE_TV now */

    i4_ret = a_cfg_get_tuner_sync_src(&ui2_crnt_svl_id, &ps_crnt_tuner_name);
    if (i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }
    h_crnt_svl = menu_get_crnt_svl();

    if (h_crnt_svl == NULL_HANDLE)
    {
        return MENUR_OK;
    }

    if (t_g_menu_common.b_src_dirty == TRUE)
    {
        i4_ret = a_cfg_set_tuner_sync_src(ui2_crnt_svl_id, ps_crnt_tuner_name);
        if (i4_ret != APP_CFGR_OK)
        {
            DBG_ERROR(("<MENU>Can't notify DT to sync source in menu_adjust_vplane()\r\n"));
            return MENUR_FAIL;
        }
        t_g_menu_common.b_src_dirty = FALSE;
    }


    c_memset(&t_svl_rec, 0x0, sizeof(SVL_REC_T));
    i4_ret = a_tv_get_svl_rec_by_si_numbers(menu_get_crnt_svl(),
                                            ui4_channel_num,
                                            0,
                                            &t_svl_rec);
    if (i4_ret == TVR_OK) {
        if ((t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE) > 0) {
            b_found = FALSE;
        } else {
            b_found = TRUE;
            ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;

        }
		*pb_found = b_found;
    }

    if(FALSE == b_found)
    {

        i4_ret = a_tv_get_crnt_or_first_svl_rec(h_crnt_svl, TRUE, &t_svl_rec);

        if(i4_ret != TVR_OK)
        {
            i4_ret = a_tv_stop(menu_get_crnt_svctx());

            if (i4_ret != TVR_OK)
            {
                DBG_ERROR (("<MENU> Stop service failed = %d\n\r", i4_ret));
            }

            return MENUR_OK;
        }
        else
        {
            ui4_channel_id = t_svl_rec.uheader.t_rec_hdr.ui4_channel_id;
        }

    }

	/* save current and previous channel */
	ui4_old_channel_id = a_util_cnfg_get_crnt_channel_id();

	if (ui4_old_channel_id == INVALID_CHANNEL_ID)
	{
	   a_util_cnfg_set_last_channel_id(ui4_channel_id);
	   a_util_cnfg_set_crnt_channel_id(ui4_channel_id);
	}
	else if (ui4_channel_id != ui4_old_channel_id)
	{
	   a_util_cnfg_set_last_channel_id(ui4_old_channel_id);
	   a_util_cnfg_set_crnt_channel_id(ui4_channel_id);
	}

    /* Successfully get a playable svl_rec, so play it */
    if(t_tv_mode != TV_MODE_TYPE_NORMAL)
    {
        /* If PIP/POP mode, use the last stream mode. */
        i4_ret = a_tv_change_channel(menu_get_crnt_svctx(),
                                     ui4_g_last_strm_mode,
                                     ui4_channel_id,
                                     NULL);
    }
    else
    {
        /* If normal mode, always play video and audio */
        i4_ret = a_tv_change_channel(menu_get_crnt_svctx(),
                                     ST_MASK_VIDEO | ST_MASK_AUDIO,
                                     ui4_channel_id,
                                     NULL);
    }


    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _is_analog_pc_or_hdmi_pc
 *
 * Description
 *
 * Input arguments
 * Output arguments
 * Returns
 *
 *---------------------------------------------------------------------------*/
static BOOL _is_analog_pc_or_hdmi_pc(VOID)
{
    BOOL        b_pc_mode = FALSE;
    INT32       i4_ret;
    ISL_REC_T   t_isl_rec;
    VSH_SRC_RESOLUTION_INFO_T t_timing;

    c_memset(&t_timing, 0, sizeof(VSH_SRC_RESOLUTION_INFO_T));
    c_memset(&t_isl_rec, 0, sizeof(ISL_REC_T));

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    if(i4_ret != MENUR_OK)
    {
        return FALSE;
    }
    else if(t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
           t_isl_rec.t_avc_info.e_video_type == DEV_AVC_VGA)
    {
        b_pc_mode = TRUE;   /*VGA PC*/
    }
    else if (t_isl_rec.e_src_type == INP_SRC_TYPE_AV &&
             t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI)
    {
        i4_ret = c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_timing);
        if (i4_ret != MENUR_OK)
        {
            return FALSE;
        }

        if (VSH_SRC_TIMING_GRAPHIC == t_timing.e_timing_type)
        {
            b_pc_mode = TRUE; /*HDMI PC*/
        }
    }

    return (b_pc_mode);
}

extern BOOL a_menu_is_cc_hot_key(VOID)
{
	if((t_g_menu_common.b_is_hot_key_enter == TRUE)&&
		(t_g_menu_common.ui4_key_code == BTN_CC))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

#if( MENU_SUPPORT_HOT_KEY_PIC|| defined(APP_SUPPORT_PIC_HOT_KEY) )
BOOL a_menu_is_pic_hot_key(VOID)
{
    if( (t_g_menu_common.b_is_hot_key_enter == TRUE)&&
        (t_g_menu_common.ui4_key_code == BTN_P_EFFECT))
    {
        MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][KEY][PIC]{%s,%d} is PIC key!\n", __FUNCTION__, __LINE__ )); );
        return TRUE;
    }

    MENU_DEBUG_KEY_PIC( DBG_LOG_PRINT(("[MENU][KEY][PIC]{%s,%d} is NOT PIC key\n", __FUNCTION__, __LINE__ )); );

    return FALSE;
}
#endif

#if 0//( MENU_SUPPORT_HOT_KEY_ASPECT_RATIO )
BOOL a_menu_is_hot_key_BTN_ASPECT(VOID)
{
    if( (t_g_menu_common.b_is_hot_key_enter == TRUE)&&
        (t_g_menu_common.ui4_key_code == BTN_ASPECT))
    {
        MENU_DEBUG_KEY_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][KEY][ASPECT]{%s,%d} is PIC key!\n", __FUNCTION__, __LINE__ )); );
        return TRUE;
    }

    MENU_DEBUG_KEY_ASPECT_RATIO( DBG_LOG_PRINT(("[MENU][KEY][ASPECT]{%s,%d} is NOT PIC key\n", __FUNCTION__, __LINE__ )); );

    return FALSE;
}
#endif


/*-----------------------------------------------------------------------------
 * Name: a_menu_3d_setting_is_able_to_enable
 *
 * Description
 *      This api is query if menu -> 3d item should be enable/disable
 * Input arguments
 * Output arguments
 * Returns
 *      TRUE    enable 3D item
 *      FALSE   disable 3D item
 *---------------------------------------------------------------------------*/
extern BOOL a_menu_3d_setting_is_able_to_enable(VOID)
{
    TV_MODE_T       e_tv_mode;
    ISL_REC_T       t_isl_rec = {0};
    CHAR            s_disp_name[17];
    VSH_SRC_RESOLUTION_INFO_T t_timing = {0};
    INT32           i4_ret = MENUR_OK;
    CHAR            s_app_name[APP_NAME_MAX_LEN + 1];
    INT16           i2_3d_mode = 0;
#ifdef APP_AV_COMPONENT_USE_ONE_PORT
	UINT8           SrcId = 0;
#endif

#ifdef APP_MENU_MMP_COEXIST
    MMP_MAIN_AP_STATUS_T    e_mmp_status = MMP_MAIN_AP_STATUS_DEINITED;

    /*Menu conexist with MMP*/
    e_mmp_status = a_mmp_get_ap_status();
    if(MMP_MAIN_AP_STATUS_PAUSED_WAIT_SVC == e_mmp_status)
    {
        if ((MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status())
        ||(MMP_BE_BROWSER_STATUS_VIDEO_NORMAL_FULLSCREEN_PAUSING == a_mmp_be_get_browser_status())
        ||(MMP_BE_BROWSER_STATUS_VIDEO_FF_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status())
        ||(MMP_BE_BROWSER_STATUS_VIDEO_FR_FULLSCREEN_PLAYING == a_mmp_be_get_browser_status()))
        {
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
#endif

    /* If current is 3D mode , should enable*/
    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                          &i2_3d_mode);
    if ((i4_ret == MENUR_OK) && (i2_3d_mode != APP_CFG_3D_MODE_OFF))
    {
        return TRUE;
    }

    menu_get_crnt_isl(&t_isl_rec);

    /* 3D Item only enable in MMP and HDMI, or 3rd*/
    if (a_tv_net_get_tv_svc_status() == APP_TV_NET_SVC_STATUS_RESUMED)  /* 3rd */
    {
        /* do not check video resolution*/
        #if 0
        i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        if (i4_ret != APP_CFGR_OK)
        {
            return FALSE;
        }

        i4_ret = a_cfg_av_get_timing(s_disp_name, &t_timing);
        if (i4_ret != APP_CFGR_OK)
        {
            return FALSE;
        }

        if (t_timing.ui4_height < 720)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
        #endif
        return TRUE;
    }
    else
    {
        i4_ret = a_am_get_active_app (s_app_name);
        if (i4_ret != AMR_OK)
        {
            return FALSE;    /* Error handle : enable 3D */
        }

        if ( c_strcmp (s_app_name, MMP_NAME) == 0 )
        {
            return TRUE;
        }

        /* support MMP / HDMI / COMP /DTV */
#ifndef APP_AV_COMPONENT_USE_ONE_PORT
        if ((t_isl_rec.e_src_type == INP_SRC_TYPE_TV) ||
            (t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI) ||
            (t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_Y_PB_PR))
        {
            DBG_INFO(("\n========================== menu 3D can be enable ================\n"));
        }
#else
	   if ((t_isl_rec.e_src_type == INP_SRC_TYPE_TV) ||
	   	   (t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_HDMI) ||
           (t_isl_rec.e_src_type == INP_SRC_TYPE_AV && t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI))
	   	{
	   		/*AV source and component source use the same port*/
			if(t_isl_rec.t_avc_info.e_video_type == DEV_AVC_COMBI)
			{
				i4_ret = a_cfg_custom_get_srcid_com_or_av(&SrcId);
				if(i4_ret != MENUR_OK)
		        {
		        	DBG_INFO(("<MENU>a_cfg_custom_get_srcid_com_or_av fail   fail(%d), line(%d)\n",i4_ret,__LINE__));
		            return FALSE;
		        }

				if((SrcId == 0) || (SrcId == 2))/*0 , No source , or 2 AV source*/
				{
					return FALSE;
				}
				else /*component source */
				{
				}
			}
			DBG_INFO(("\n========================== menu 3D can be enable ================\n"));
        }
#endif


        else
        {
            return FALSE; /* For other source , disable 3D */
        }

        /* no signal detect/no signal lock */
        if (menu_is_signal_loss() || menu_is_video_block())
        {
            return FALSE;
        }

        a_tv_get_mode(&e_tv_mode);
        /* PIP is active */
        if (TV_MODE_TYPE_PIP == e_tv_mode ||
            TV_MODE_TYPE_POP == e_tv_mode)
        {
            return FALSE;
        }

        a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
        a_cfg_av_get_timing(s_disp_name, &t_timing);

        if(_is_analog_pc_or_hdmi_pc())
        {
            return FALSE;
        }
        else
        {
            /*disbale SD timing*/
            if(t_timing.ui4_height < 720)
            {
                return FALSE;
            }

            /* enable DTV, disable ATV */
            if(t_isl_rec.e_src_type == INP_SRC_TYPE_TV)
            {
                if ( menu_is_digital_tv(TV_WIN_ID_MAIN) )
                {
                    return TRUE;
                }
                else
                {
                    return FALSE;
                }
            }
        }
    }

    return TRUE;
}

/*-----------------------------------------------------------------------------
 * Name: a_menu_enter_factory_menu
 *
 * Description
 *      The API is used to enter to the factory menu
 * Input arguments
 *      None
 * Output arguments
 *      None
 * Returns
 *      MENUR_OK    Enter factory menu success.
 *      Other       Enter factory menu fail.
 *---------------------------------------------------------------------------*/
extern INT32 a_menu_enter_factory_menu(VOID)
{
    INT32   i4_ret;
    UINT8   ui1_fac_mode = APP_CFG_FAC_MODE_NORMAL;

    a_cfg_get_factory_mode(&ui1_fac_mode);

    ui1_fac_mode = (UINT8)(ui1_fac_mode | APP_CFG_FAC_MODE_FACTORY_MASK);
    a_cfg_set_factory_mode(ui1_fac_mode);
    a_cfg_update_factory_mode();
    a_cfg_store();

    a_tv_net_send_cmd(":dtv_app_mtk,am,:block_3rd\n");

    DBG_INFO(("\n------------[menu_enter_factory_menu]------------\n"));

    i4_ret = a_amb_resume_app(MENU_NAME);
    if (AMBR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }
    return MENUR_OK;
}

HANDLE_T menu_get_crnt_lol(VOID)
{
    return NULL_HANDLE;
}


