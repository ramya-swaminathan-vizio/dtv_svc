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
 * $RCSfile: menu_page_ch_lst2.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/19 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 7ed3c11a9ed90eba15305b24039bcab7 $
 *
 * Description:
 *      This file contains the implementation of channel lists.
 *---------------------------------------------------------------------------*/

#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"
#include "u_sb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_svl.h"
#include "c_svctx.h"
#include "res/app_util/icl/a_icl_custom.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "u_sb_atsc_eng.h"
#include "nav/pwd_dlg/pwd_dlg.h"

#ifdef APP_CLRQAM_SUPPORT
    #ifdef APP_DCR_SUPPORT
        #include "u_sb_oob_eng.h"
    #else
        #include "u_sb_cqam_eng.h"
    #endif
#endif

#include "res/nav/one_channel_list/ocl.h"


#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#include "c_tts.h"
#endif

#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "menu2/menu.h"
#include "nav/nav_common.h"
#include "res/nav/nav_custom_comp_id.h"
#include "res/menu2/menu_custom.h"
#include "nav/input_src/input_src.h"
#include "rest/a_rest_event.h"
#include "app_util/config/_acfg.h"
#include "menu2/menu_dbg.h"


#ifdef COMMON_CH_LST2_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/

#ifndef CH_LST2_STL_SCROLL
#define CH_LST2_STL_SCROLL    0
#endif

#ifndef CH_LST2_STL_WRAP_OVER
#define CH_LST2_STL_WRAP_OVER 1
#endif

#ifndef CH_LST2_BACK_ON_LEFT
#define CH_LST2_BACK_ON_LEFT  1
#endif

#ifndef CH_LST2_COL0_W
#define CH_LST2_COL0_W       80
#endif

#ifndef CH_LST2_COL1_W
#define CH_LST2_COL1_W       80
#endif

#ifndef CH_LST2_COL2_W
#define CH_LST2_COL2_W       (CONTENT_W - CH_LST2_COL0_W - CH_LST2_COL1_W - CH_LST2_COL3_W)
#endif

#ifndef CH_LST2_COL3_W
#define CH_LST2_COL3_W       80
#endif

#ifndef CH_LST2_ELEM_H
#define CH_LST2_ELEM_H       GRID_H
#endif

#ifndef CH_LST2_COL0_ALIGN
#define CH_LST2_COL0_ALIGN   WGL_AS_RIGHT_CENTER
#endif

#ifndef CH_LST2_COL1_ALIGN
#define CH_LST2_COL1_ALIGN   WGL_AS_LEFT_CENTER
#endif

#ifndef CH_LST2_COL2_ALIGN
#define CH_LST2_COL2_ALIGN   WGL_AS_CENTER_CENTER
#endif

#ifndef CH_LST2_COL3_ALIGN
#define CH_LST2_COL3_ALIGN   WGL_AS_CENTER_CENTER
#endif

#define MAX_CH_NAME_LEN     48
#define MAX_CH_TYPE_LEN     16
#define MAX_CH_NUM_LEN      8

#define MAX_CH_NUM          512
#define WARNING_MSG_TIMEOUT (3000)
#define WARNING_MSG_W   (260)
#define WARNING_MSG_H   (160)
#define WARNING_MSG_X   ((SCREEN_W-WARNING_MSG_W)/2)
#define WARNING_MSG_Y   ((SCREEN_H-WARNING_MSG_H)/2)
#define WARNING_BTN_W   (260)
#define WARNING_BTN_H   (20)
#define WARNING_BTN_X   (0)
#define WARNING_BTN_Y   (WARNING_MSG_H-WARNING_BTN_H)
#define CH_SHOW_NUM     (11)

#ifdef APP_TTS_SUPPORT
    #define _TTS_TEXT_MAX_LEN             ((UINT32) 128+1)
#endif

typedef struct _WARNING_MSG_T
{
    HANDLE_T    h_msg_frm;
    HANDLE_T    h_txt_txtinfo;
    HANDLE_T    h_msg_btn;
    HANDLE_T    h_timer;
}WARNING_MSG_T;

typedef enum _HELP_LST_STATE{
    HELP_LST_UP_ONLY = 0,
    HELP_LST_DOWN_ONLY,
    HELP_LST_UP_DOWN,
    HELP_LST_UNKNOWN
} HELP_LST_STATE;

typedef struct _CHANNEL_LIST_T
{
    UINT32                          ui4_page_id;
    MENU_COMMON_CHANNEL_LIST_INIT_T t_ch_lst2_init;
    UINT16                          ui2_ch_num;
    UINT16*                         pui2_idx_recid_map;
    UINT16*                         pui2_idx_ocl_map;
    HANDLE_T                        h_lb_ch;
    HANDLE_T                        h_img_down;
    HANDLE_T                        h_img_up;
    HANDLE_T                        h_img_sep_up;
    HANDLE_T                        h_img_sep_down;
    BOOL                            b_is_refreshing;
    WARNING_MSG_T                   t_warning_msg;
    HANDLE_T                        h_hl_timer;

}CHANNEL_LIST_T;

extern INT32 banner_view_refresh (BOOL b_at_once);
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T      t_g_menu_common_page_ch_lst2;

static HANDLE_T          h_crnt_svl = NULL_HANDLE;
static UINT32            ui4_ch_ubk_page_id;
static UINT32            ui4_ch_bk_page_id;
static UINT32            ui4_ch_sk_page_id;
static BOOL              b_is_msg_on = FALSE;

static GL_COLOR_T    t_g_color_warning_msg_bk = {0, {0 }, {0 }, {0 } };
static GL_COLOR_T    t_g_color_warning_msg_txt = { 255, {255 }, {255 }, {255}};

static UINT16            gui2_lb_elem_num;
static BOOL              b_is_channel_locked[MAX_CH_NUM];
static BOOL              b_is_channel_skiped[MAX_CH_NUM];

extern BOOL              b_g_select_is_menu_key;
#define     CHN_LIST_TOP_GAP        (33)

#define     CHN_LIST_SEP_HEIGHT     (10)

#define     CHN_LIST_ARROW_WIDTH    (30)
#define     CHN_LIST_ARROW_HEIGHT   (10)

static BOOL b_is_jagwheel_ctrl=FALSE;
static BOOL b_found_channel = FALSE;

/*-----------------------------------------------------------------------------
                    PIN to unlock
 ----------------------------------------------------------------------------*/
 static UINT16     ui2_g_rating_enabled_cfg = 0;
 static BOOL       b1_pin_to_unlock_state;
 extern PWD_DLG_T t_g_pwd_dlg;
 extern BOOL _tv_is_dual_tuner(VOID);

static BOOL _menu_common_page_ch_lst2_current_is_comp(VOID);


/*----------------------------------------------------------------------------
 * Name: a_set_pwd_to_unlock_state
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID a_set_pwd_to_unlock_state(UINT8 ui2_state)
{
    b1_pin_to_unlock_state = ui2_state;
}

/*----------------------------------------------------------------------------
 * Name: a_pwd_to_unlock_get_state
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/

UINT8 a_get_pwd_to_unlock_state(VOID)
{
    return b1_pin_to_unlock_state;
}

extern BOOL app_tv_is_dual_tuner();
/*-----------------------------------------------------------------------------
 * Name
 *      tv_reset_crnt_svl_rec_tmp_unlock_bit
 * Description
 * Input arguments
 *      pui2_svl_id     The current SVL list id
 *      pt_svl_rec      The current channle's SVL record
 * Output arguments
 *      -
 * Returns
 *      TVR_OK      The routine is ok.
 *      TVR_FAIL    The routine is failed
 *---------------------------------------------------------------------------*/
INT32 _tv_reset_crnt_svl_rec_tmp_unlock_bit(
                    TV_WIN_ID_T                 e_win_id,
                    UINT16*                     pui2_svl_id,
                    SVL_REC_T*                  pt_svl_rec
                    )
{
    UINT32    ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
    UINT32    ui4_svl_ver_id = SVL_NULL_VER_ID;
    CHAR*     ps_src_name    = NULL;
    HANDLE_T  h_svl          = NULL_HANDLE;
    INT32     i4_ret         = NAVR_OK;

    if (!app_tv_is_dual_tuner())
    {
        ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
        i4_ret = a_cfg_get_tuner_sync_src(pui2_svl_id, &ps_src_name);
        if (i4_ret != APP_CFGR_OK) {
            return NAVR_FAIL;
        }
    }
    else
    {
        /* In DualTuner feature design:
                1. PIP mode: Main window binding to Main tuner, and Sub window binding to Sub tuner
                2. Non-PIP mode: No above binding mapping.
              */
        if (TV_WIN_ID_MAIN == e_win_id)
        {
            ui4_channel_id = a_util_cnfg_get_crnt_channel_id();
            i4_ret = a_cfg_get_tuner_sync_src(pui2_svl_id, &ps_src_name);
            if (i4_ret != APP_CFGR_OK) {
                return NAVR_FAIL;
            }
        }
        else
        {
            ui4_channel_id = a_util_cnfg_get_2nd_crnt_channel_id();
            i4_ret = a_cfg_get_2nd_tuner_sync_src(pui2_svl_id);
            if (i4_ret != APP_CFGR_OK) {
                return NAVR_FAIL;
            }
        }
    }

    i4_ret = c_svl_open(*pui2_svl_id, NULL, NULL, &h_svl);
    if (i4_ret != SVLR_OK) {
        return NAVR_FAIL;
    }

    c_svl_lock(h_svl);
    do {
        i4_ret = c_svl_get_rec_by_channel (
                        h_svl,
                        ui4_channel_id,
                        SB_VNET_ALL,
                        0,
                        pt_svl_rec,
                        &ui4_svl_ver_id
                        );
        if (i4_ret == SVLR_REC_NOT_FOUND) {
            i4_ret = NAVR_OK;
            break;
        }

        if (i4_ret != SVLR_OK) {
            i4_ret = NAVR_FAIL;
            break;
        }

#ifdef APP_VCHIP_UNLOCK_ALL
        if ((pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_BLOCKED) == 0){
            a_rating_enable(TRUE);
        }
#endif
        pt_svl_rec->uheader.t_rec_hdr.ui4_option_mask &= ~SB_VOPT_USER_TMP_UNLOCK;

        i4_ret = c_svl_update_rec(h_svl, pt_svl_rec, TRUE);
        i4_ret = (i4_ret == SVLR_OK) ? NAVR_OK : NAVR_FAIL;
    } while(0);
    c_svl_unlock(h_svl);

    c_svl_close(h_svl);
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _rating_enabled_cfg_vchip_nfy_fct()
 *
 * Description: In order to listen Locks state change.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static VOID _rating_enabled_cfg_vchip_nfy_fct(
    UINT16                      ui2_nfy_id,
    VOID*                       pv_tag,
    UINT16                      ui2_id)
{
    PWD_DLG_T*        pt_this = &t_g_pwd_dlg;

    if(CFG_GET_SETTING(ui2_id) == APP_CFG_RECID_RATING_ENABLED)
    {
        UINT8      ui1_enabled;

        DBG_LOG_PRINT(("<LOCK> %s,%d\n\r",__FILE__,__LINE__));

        a_cfg_get_rating_enabled(&ui1_enabled);


        if (ui1_enabled == RATING_ENABLED_STATUS_ON)
        {
            UINT16    ui2_svl_id    = SVL_NULL_ID;
            SVL_REC_T t_svl_rec     = {0};

            if (a_get_pwd_to_unlock_state() == TRUE )
            {
                a_set_pwd_to_unlock_state(FALSE);
            }

            _tv_reset_crnt_svl_rec_tmp_unlock_bit(pt_this->e_focus_tv_win_id, &ui2_svl_id, &t_svl_rec);
        }

    }
}

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
static VOID _warning_msg_reset_timer(
                        CHANNEL_LIST_T* pt_ch_lst2
                        );

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/

static INT32 _ch_update_scrollbar(HANDLE_T h_lb_ch,
                                  CHANNEL_LIST_T*         pt_ch_lst2)
{
    INT32   i4_ret = WGLR_OK;
    UINT16  ui2_idx = 0;
    UINT16  ui2_hlt = 0;

    if(NULL == pt_ch_lst2)
    {
        return WGLR_INV_ARG;
    }

    GL_RECT_T   t_rect;
    HANDLE_T    h_last_shadow_item;
    UINT16      ui2_first_visible;
    UINT16      ui2_last_visible;

    i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                      WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                      WGL_PACK(&ui2_first_visible),
                      NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                      WGL_CMD_LB_GET_LAST_VISIBLE_INDEX,
                      WGL_PACK(&ui2_last_visible),
                      NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * (ui2_last_visible - ui2_first_visible + 1) + CONTENT_Y+20;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_idx),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui2_idx <= CH_SHOW_NUM)
    {
        i4_ret = c_wgl_show(pt_ch_lst2->h_img_up, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        i4_ret = c_wgl_show(pt_ch_lst2->h_img_down, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);

        menu_pm_repaint();

        return WGLR_OK;
    }

    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_LB_GET_FIRST_VISIBLE_INDEX,
                          WGL_PACK(&ui2_hlt),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    if (ui2_hlt < CH_SHOW_NUM)
    {
        i4_ret = c_wgl_show(pt_ch_lst2->h_img_up, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_show(pt_ch_lst2->h_img_up, WGL_SW_RECURSIVE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    if (ui2_hlt < (ui2_idx - (ui2_idx%CH_SHOW_NUM)))
    {
        i4_ret = c_wgl_show(pt_ch_lst2->h_img_down, WGL_SW_RECURSIVE);
        MENU_LOG_ON_FAIL(i4_ret);
    }
    else
    {
        i4_ret = c_wgl_show(pt_ch_lst2->h_img_down, WGL_SW_HIDE);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    menu_pm_repaint();

    return i4_ret;
}

static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    INT32           i4_ret;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;
    UINT32          ui4_page_id = 0;
    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_ch_lst2);
        MENU_LOG_ON_FAIL(i4_ret);

        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
        case BTN_RETURN:
            menu_nav_back();
            return MENUR_OK;

        case BTN_CURSOR_DOWN:

            if (nav_is_component_visible(NAV_COMP_ID_BANNER))
            {
                banner_view_refresh(TRUE);
            }

            /* set highlight of quick_operation & focus on it */
            c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                         WGL_CMD_LB_HLT_ELEM ,
                         WGL_PACK(0) ,
                         NULL);

            /* make sure it can be see */
            MENU_LOG_ON_FAIL (c_wgl_do_cmd (pt_ch_lst2->h_lb_ch ,
                              WGL_CMD_LB_ENSURE_HLT_ELEM_VISIBLE ,
                              NULL ,
                              NULL));

            c_wgl_set_focus(pt_ch_lst2->h_lb_ch, WGL_NO_AUTO_REPAINT);

            if(pt_ch_lst2->t_ch_lst2_init.ui2_msg_title == MLM_MENU_KEY_CH_SK)
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_SKIP_CH));
            }
            else if(pt_ch_lst2->t_ch_lst2_init.ui2_msg_title == MLM_MENU_KEY_CH_BK)
            {
                menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_PARENT_CH_BLOCK));
            }

            menu_pm_repaint();

            break ;
        case BTN_CURSOR_UP:
            MENU_LOG_ON_FAIL (menu_set_focus_on_homebar(TRUE));
            //menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
            break;
        default:
            break ;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static INT32 _homebar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    INT32           i4_ret;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;
    UINT32          ui4_page_id = 0;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_EMPTY));
    }

    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
        MENU_LOG_ON_FAIL(i4_ret);
        i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_ch_lst2);
        MENU_LOG_ON_FAIL(i4_ret);

        switch ((UINT32)param1)
        {
        case BTN_CURSOR_LEFT :
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return WGLR_OK;
        #endif
        case BTN_SELECT :
            menu_nav_go_home_menu();
            return MENUR_OK ;
        case BTN_RETURN:
            menu_nav_back();
            return MENUR_OK;

        case BTN_CURSOR_DOWN :
            MENU_LOG_ON_FAIL(menu_set_focus_on_backbar (TRUE));
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break ;

        default :
            break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}
/*-----------------------------------------------------------------------------
 * Name
 *      _warning_msg_set_text
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_msg_set_text(HANDLE_T            h_widget,
                                   UTF16_T*            w2s_text)
{
    INT32   i4_ret;

    i4_ret = c_wgl_do_cmd(h_widget,
                         WGL_CMD_TEXT_SET_TEXT,
                         WGL_PACK(w2s_text),
                         WGL_PACK(c_uc_w2s_strlen(w2s_text)));

    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_msg_show
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _warning_msg_show(
                    CHANNEL_LIST_T* pt_ch_lst2
                    )
{
    INT32       i4_ret;

    if (b_is_msg_on == FALSE)
    {
        i4_ret = c_wgl_set_visibility(pt_ch_lst2->t_warning_msg.h_msg_frm, WGL_SW_RECURSIVE);
        if (i4_ret != WGLR_OK) {
            return MENUR_FAIL;
        }
        i4_ret = c_wgl_set_focus(pt_ch_lst2->t_warning_msg.h_msg_btn,FALSE);
        if (i4_ret != WGLR_OK) {
            return MENUR_FAIL;
        }

        b_is_msg_on = TRUE;
        menu_pm_repaint();

        _warning_msg_reset_timer(pt_ch_lst2);
        DBG_INFO(("\n==== channel warning msg show ====\n"));

    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _warning_msg_stop_timer
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _warning_msg_stop_timer(CHANNEL_LIST_T* pt_ch_lst2)
{
    INT32   i4_ret;

    if (c_handle_valid(pt_ch_lst2->t_warning_msg.h_timer) == FALSE) {
        return MENUR_OK;
    }

    i4_ret = c_timer_stop(pt_ch_lst2->t_warning_msg.h_timer);
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("can french unlock page:: h_timer failed!"));
    }
    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _warning_msg_hide
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _warning_msg_hide(VOID)
{
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;
    INT32           i4_ret;
    UINT32          ui4_page_id;

    i4_ret = menu_nav_get_crnt_page(&ui4_page_id);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    if (b_is_msg_on == FALSE) {
        return MENUR_OK;
    }

    i4_ret = c_wgl_set_visibility(pt_ch_lst2->t_warning_msg.h_msg_frm, WGL_SW_HIDE);
    if (i4_ret != WGLR_OK){
        return MENUR_FAIL;
    }

    i4_ret = c_wgl_set_focus(pt_ch_lst2->h_lb_ch,FALSE);
    if (i4_ret != WGLR_OK) {
        return MENUR_FAIL;
    }

    b_is_msg_on = FALSE;
    menu_pm_repaint();
    _warning_msg_stop_timer(pt_ch_lst2);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _ch_image_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_image_create(HANDLE_T    h_parent,
                             INT32       i4_x,
                             INT32       i4_y,
                             INT32       i4_w,
                             INT32       i4_h,
                             CHANNEL_LIST_T*         pt_ch_lst2)
{
    INT32       i4_ret = WGLR_OK;
    GL_RECT_T  t_rect;
    WGL_IMG_INFO_T      t_img_info;
    INT32   i4_img_x = i4_x;
    INT32   i4_img_y = i4_y;
    INT32   i4_img_w = i4_w;
    INT32   i4_img_h = i4_h;

    if (NULL == pt_ch_lst2)
    {
        return WGLR_INV_ARG;
    }


    i4_img_h = CHN_LIST_SEP_HEIGHT;
    /* top text seperator */
    SET_RECT_BY_SIZE(&t_rect,
                        i4_img_x,
                        i4_img_y,
                        i4_img_w,
                        i4_img_h );

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &(pt_ch_lst2->h_img_sep_up));

    /* bottom text seperator */
    i4_img_x = i4_x;
    i4_img_y = i4_y + CHN_LIST_TOP_GAP + (CH_LST2_ELEM_H * CH_SHOW_NUM);
    i4_img_h = CHN_LIST_SEP_HEIGHT;
    SET_RECT_BY_SIZE(&t_rect,
                        i4_img_x,
                        i4_img_y,
                        i4_img_w,
                        i4_img_h);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &(pt_ch_lst2->h_img_sep_down));

    /* bottom arrow up */
    i4_img_x = i4_x + (i4_w-CHN_LIST_ARROW_WIDTH)/2;
    i4_img_y = i4_y + 1 ;
    i4_img_w = CHN_LIST_ARROW_WIDTH;
    i4_img_h = CHN_LIST_ARROW_HEIGHT;

    SET_RECT_BY_SIZE(&t_rect,
                        i4_img_x,
                        i4_img_y,
                        i4_img_w,
                        i4_img_h);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &(pt_ch_lst2->h_img_up));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_ch_lst_arrow_up;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_ch_lst_arrow_up;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_ch_lst_arrow_up;
    i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_img_up,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));

    /* bottom arrow down */
    i4_img_x = i4_x + (i4_w-CHN_LIST_ARROW_WIDTH)/2;
    i4_img_y = i4_y + (MENU_ITEM_V_HEIGHT * CH_SHOW_NUM)+ CHN_LIST_SEP_HEIGHT;
    i4_img_w = CHN_LIST_ARROW_WIDTH;
    i4_img_h = CHN_LIST_ARROW_HEIGHT;
    SET_RECT_BY_SIZE(&t_rect,
                        i4_img_x,
                        i4_img_y,
                        i4_img_w,
                        i4_img_h);
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &(pt_ch_lst2->h_img_down));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_ch_lst_arrow_down;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_ch_lst_arrow_down;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_ch_lst_arrow_down;
    i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_img_down,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    DBG_INFO(("i4_ret=%d\n",i4_ret));
    return WGLR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _ch_lst2_add_empty
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_add_empty(HANDLE_T            h_lb_ch,
                                CHANNEL_LIST_T*     pt_ch_lst2)

{
    INT32    i4_ret = WGLR_OK;
    WGL_LB_ITEM_IMG_SUIT_T t_img_suit;
    WGL_LB_ITEM_T at_items[4];
    UTF16_T w2s_name[MAX_CH_NAME_LEN+1];

    c_uc_w2s_strcpy(w2s_name, MENU_TEXT(MLM_MENU_KEY_SKIP_NO_CH));

    /* Append the data */
    c_memset(&t_img_suit, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));

    t_img_suit.h_normal                     = h_g_menu_img_not_ava;
    t_img_suit.h_disable                    = h_g_menu_img_not_ava;
    t_img_suit.h_highlight                  = h_g_menu_img_not_ava;
    t_img_suit.h_highlight_unfocus          = h_g_menu_img_not_ava;;
    t_img_suit.h_pushed                     = h_g_menu_img_not_ava;
    t_img_suit.h_selected                   = h_g_menu_img_not_ava;
    t_img_suit.h_selected_disable           = h_g_menu_img_not_ava;
    t_img_suit.h_selected_highlight         = h_g_menu_img_not_ava;
    t_img_suit.h_selected_highlight_unfocus = h_g_menu_img_not_ava;
    t_img_suit.h_selected_pushed            = h_g_menu_img_not_ava;

    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = NULL;
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = NULL;
    at_items[2].e_col_type = LB_COL_TYPE_TEXT;
    at_items[2].data.pw2s_text = w2s_name;
    at_items[3].e_col_type = LB_COL_TYPE_IMG_SUIT;
    at_items[3].data.pt_img_suit = &t_img_suit;

        /* append item */
    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _ch_lst2_set_attach_data
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_set_attach_data(HANDLE_T            h_lb_ch,
                                     CHANNEL_LIST_T*     pt_ch_lst2)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_ch_lst2),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _ch_lst2_get_attach_data
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_get_attach_data(HANDLE_T            h_lb_ch,
                                     CHANNEL_LIST_T**    ppt_ch_lst2)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_ch_lst2),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _ch_num_to_str
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _ch_num_to_str(UINT16      ui2_major,
                           UINT16      ui2_minor,
                           BOOL        b_one_part_ch,
                           UTF16_T*    w2s_str)
{
    CHAR    s_str[64];
    c_memset(s_str, 0, sizeof(s_str));
    if (b_one_part_ch)
    {   /* One part channel number */
        c_sprintf(s_str,
                  "%d",
                  ui2_major);
    }
    else
    {   /* Two part channel number */
        c_sprintf(s_str,
                  CHANNEL_NUMBER_FORMAT,   /* Defined in a_common.h */
                  ui2_major,
                  ui2_minor);
    }
    c_uc_ps_to_w2s(s_str ,w2s_str, MAX_CH_NUM_LEN);
}



/*----------------------------------------------------------------------------
 * Name: _ch_lst2_add_ch
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_add_ch(HANDLE_T            h_lb_ch,
                            CHANNEL_LIST_T*     pt_ch_lst2,
                            SVL_REC_T*          pt_svl_rec,
                            UINT16              ui2_ocl_idx)
{
    INT32   i4_ret;
    UINT32  ui4_channel_id = pt_svl_rec->uheader.t_rec_hdr.ui4_channel_id;
    UINT16  ui4_rec_id = pt_svl_rec->ui2_svl_rec_id;
    UINT32  ui4_nw_mask = pt_svl_rec->uheader.t_rec_hdr.ui4_nw_mask;
    UINT32  ui4_sel_mask = pt_ch_lst2->t_ch_lst2_init.ui4_sel_mask;
    UTF16_T w2s_digits[MAX_CH_NUM_LEN+1];
    UTF16_T w2s_name[MAX_CH_NAME_LEN+1];
    UTF16_T *w2s_type;
    BOOL    b_one_part_ch = SB_ATSC_IS_ONE_PART_CHANNEL_ID(ui4_channel_id);
    UINT16  ui2_major     = SB_ATSC_GET_MAJOR_CHANNEL_NUM(ui4_channel_id);
    UINT16  ui2_minor     = SB_ATSC_GET_MINOR_CHANNEL_NUM(ui4_channel_id);
    INT32   i4_len;
    UINT16  ui2_idx;
    WGL_LB_ITEM_T at_items[4];
    WGL_LB_ITEM_IMG_SUIT_T t_img_suit;

    /* Get the channel number */
    c_memset(w2s_digits, 0, sizeof(w2s_digits));
    _ch_num_to_str(ui2_major, ui2_minor, b_one_part_ch, w2s_digits);

    /* Get the channel name */
    c_memset(w2s_name, 0, sizeof(w2s_name));
    i4_len = (INT32)c_strlen(pt_svl_rec->uheader.t_rec_hdr.ac_name);
    if(i4_len > MAX_CH_NAME_LEN)
    {
        i4_len = MAX_CH_NAME_LEN;
    }
    c_uc_ps_to_w2s(pt_svl_rec->uheader.t_rec_hdr.ac_name,
                   w2s_name,
                   (UINT32)i4_len);

    /* Get the broadcast type */
    if(pt_svl_rec->uheader.t_rec_hdr.e_brdcst_type == BRDCST_TYPE_ANALOG)
    {
        w2s_type = MENU_TEXT(MLM_MENU_KEY_CH_ANLG);
    }
    else
    {
        w2s_type = MENU_TEXT(MLM_MENU_KEY_CH_DIG);
    }

    /* Append the data */
    c_memset(&t_img_suit, 0, sizeof(WGL_LB_ITEM_IMG_SUIT_T));
    t_img_suit.h_normal                     = pt_ch_lst2->t_ch_lst2_init.h_img_normal;
    t_img_suit.h_disable                    = NULL_HANDLE;
    t_img_suit.h_highlight                  = pt_ch_lst2->t_ch_lst2_init.h_img_highlight;
    t_img_suit.h_highlight_unfocus          = pt_ch_lst2->t_ch_lst2_init.h_img_normal;;
    t_img_suit.h_pushed                     = NULL_HANDLE;
    t_img_suit.h_selected                   = pt_ch_lst2->t_ch_lst2_init.h_img_selected;
    t_img_suit.h_selected_disable           = NULL_HANDLE;
    t_img_suit.h_selected_highlight         = pt_ch_lst2->t_ch_lst2_init.h_img_selected_highlight;
    t_img_suit.h_selected_highlight_unfocus = pt_ch_lst2->t_ch_lst2_init.h_img_selected;
    t_img_suit.h_selected_pushed            = NULL_HANDLE;


    at_items[0].e_col_type = LB_COL_TYPE_TEXT;
    at_items[0].data.pw2s_text = w2s_digits;
    at_items[1].e_col_type = LB_COL_TYPE_TEXT;
    at_items[1].data.pw2s_text = w2s_type;
    at_items[2].e_col_type = LB_COL_TYPE_TEXT;
    at_items[2].data.pw2s_text = w2s_name;
    at_items[3].e_col_type = LB_COL_TYPE_IMG_SUIT;
    at_items[3].data.pt_img_suit = &t_img_suit;

    /* append item */
    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_LB_APPEND_ELEM,
                          WGL_PACK(at_items),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Get the index */
    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_idx),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    ui2_idx -= 1;

    /* Sel or not */
    if (ui4_nw_mask & ui4_sel_mask)
    {
        i4_ret = c_wgl_do_cmd(h_lb_ch,
                              WGL_CMD_LB_SEL_ELEM,
                              WGL_PACK(ui2_idx),
                              NULL);
        MENU_LOG_ON_FAIL(i4_ret);
        if(ui2_idx<MAX_CH_NUM)
        {
            b_is_channel_locked[ui2_idx] = TRUE;
            b_is_channel_skiped[ui2_idx] = FALSE;
        }

    }
    else
    {
        if(ui2_idx<MAX_CH_NUM)
        {
            b_is_channel_locked[ui2_idx] = FALSE;
            b_is_channel_skiped[ui2_idx] = TRUE;
        }
    }

    /* mapping */
    pt_ch_lst2->pui2_idx_recid_map[ui2_idx] = ui4_rec_id;
    pt_ch_lst2->pui2_idx_ocl_map[ui2_idx] = ui2_ocl_idx;

    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _ch_lst2_on_sel
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_on_sel(HANDLE_T    h_lb_ch,
                             UINT16      ui2_idx,
                             BOOL        b_sel)
{
    INT32           i4_result;
    INT32           i4_ret;

    UINT16          ui2_rec_id;
    UINT16          ui2_ocl_idx;
    SVL_REC_T       t_svl_rec;
    OCL_SVL_REC_T   t_ocl_svl_rec;
    HANDLE_T        h_ocl_svl = NULL_HANDLE;
    UINT32          ui4_sel_mask;
    CHANNEL_LIST_T* pt_ch_lst2;
    UINT8   ui1_val = RATING_ENABLED_STATUS_ON;
    SIZE_T  z_size = ICL_RECID_RATING_ENABLED_STATUS_SIZE;

    /* get the channel list data */
    i4_result = _ch_lst2_get_attach_data(h_lb_ch, &pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_result);

    if (pt_ch_lst2 == NULL)
    {
        return MENUR_FAIL;
    }

    if (pt_ch_lst2->b_is_refreshing)
    {
        return MENUR_OK;
    }

    /* get the list mask */
    ui4_sel_mask = pt_ch_lst2->t_ch_lst2_init.ui4_sel_mask;

    /* get the rec id*/
    ui2_rec_id = pt_ch_lst2->pui2_idx_recid_map[ui2_idx];

    /* get the ocl idx*/
    ui2_ocl_idx = pt_ch_lst2->pui2_idx_ocl_map[ui2_idx];

    DBG_INFO(("<MENU> _ch_lst2_on_sel rec_id:[%u], ocl_idx:[%u]\r\n", ui2_rec_id, ui2_ocl_idx));

    c_memset(&t_svl_rec, 0, sizeof(t_svl_rec));
    c_memset(&t_ocl_svl_rec, 0, sizeof(t_ocl_svl_rec));

    i4_ret = ocl_get_ocl_svl_by_index(ui2_ocl_idx, &t_svl_rec, &t_ocl_svl_rec);
    if (OCLR_OK != i4_ret)
    {
        return MENUR_FAIL;
    }

    if (t_ocl_svl_rec.ui2_svl_id == ANTENNA_SVL_ID)
    {
        h_ocl_svl = t_g_menu_common.h_svl_air;
    }
    else
    {
        h_ocl_svl = t_g_menu_common.h_svl_cable;
    }

    /* update the record*/
    i4_result = c_svl_lock(h_ocl_svl);
    if (i4_result != SVLR_OK)
    {
        i4_ret = MENUR_FAIL;
    }
    else
    {
        {
            if (b_sel)
            {
                t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask |= ui4_sel_mask;
                if ((pt_ch_lst2->ui4_page_id == ui4_ch_bk_page_id) ||
                    (pt_ch_lst2->ui4_page_id == ui4_ch_ubk_page_id) )
                {
                    if(ui2_idx<MAX_CH_NUM)
                    {
                        b_is_channel_locked[ui2_idx] = TRUE;
                    }
                }

                if (pt_ch_lst2->ui4_page_id == ui4_ch_sk_page_id)
                {
                    if(ui2_idx<MAX_CH_NUM)
                    {
                        b_is_channel_skiped[ui2_idx] = FALSE;
                    }
                }
#ifdef APP_EPG_SKIP_INVISIBLE_CH
                /* This is for the channel can be displayed in EPG. */
                t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask |= SB_VNET_EPG;
#endif
            }
            else
            {
                t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask &= ~ui4_sel_mask;

                if ((pt_ch_lst2->ui4_page_id == ui4_ch_bk_page_id) ||
                    (pt_ch_lst2->ui4_page_id == ui4_ch_ubk_page_id) )
                {
                    if(ui2_idx<MAX_CH_NUM)
                    {
                        b_is_channel_locked[ui2_idx] = FALSE;
                    }
                }
                if (pt_ch_lst2->ui4_page_id == ui4_ch_sk_page_id)
                {
                    if(ui2_idx<MAX_CH_NUM)
                    {
                        b_is_channel_skiped[ui2_idx] = TRUE;
                    }
                }
            }
#ifdef APP_TTS_SUPPORT
            UTF16_T     w2s_text[32+1] ={0};

            if(ui2_idx<MAX_CH_NUM)
            {
                if ( pt_ch_lst2->t_ch_lst2_init.ui2_msg_title != MLM_MENU_KEY_CH_SK )
                {
                    if(b_is_channel_locked[ui2_idx] == TRUE)
                    {
                        c_uc_ps_to_w2s("lock", w2s_text, c_strlen("lock"));
                    }
                    else
                    {
                        c_uc_ps_to_w2s("unlock", w2s_text, c_strlen("unlock"));
                    }
                    a_tts_switch_dash_to_dash_string(w2s_text,w2s_text,64);
                    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
                }
                else
                {
                    if(b_is_channel_skiped[ui2_idx])
                    {
                        c_uc_ps_to_w2s("skip", w2s_text, c_strlen("skip"));
                    }
                    else
                    {
                        c_uc_ps_to_w2s("unskip", w2s_text, c_strlen("unskip"));
                    }
                    a_tts_switch_dash_to_dash_string(w2s_text,w2s_text,64);
                    a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
                }
            }
#endif
#ifdef APP_MENU_REMOVE_TMP_UNLOCK_BIT_WHILE_TOGGLE_CHANNEL_BLOCKING
            if ( (ui4_sel_mask & SB_VNET_BLOCKED) > 0)
            {
                t_svl_rec.uheader.t_rec_hdr.ui4_option_mask &= ~SB_VOPT_USER_TMP_UNLOCK;
            }
#endif /* APP_MENU_REMOVE_TMP_UNLOCK_BIT_WHILE_TOGGLE_CHANNEL_BLOCKING */

			a_icl_get(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
					&ui1_val, &z_size);

		    if (RATING_ENABLED_STATUS_ON == ui1_val)
		    {
		       	if ( (ui4_sel_mask & SB_VNET_BLOCKED) > 0)
	            {
	                t_svl_rec.uheader.t_rec_hdr.ui4_option_mask &= ~SB_VOPT_USER_TMP_UNLOCK;
	                ui1_val = RATING_ENABLED_STATUS_ON;
	                z_size   = ICL_RECID_RATING_ENABLED_STATUS_SIZE;
	                a_icl_set(ICL_MAKE_ID(ICL_GRPID_RATING_ENABLED_STATUS, ICL_RECID_RATING_ENABLED_STATUS),
	                          (VOID*)&ui1_val,
	                          z_size);
	            }
            }

            i4_result = c_svl_update_rec(h_ocl_svl,
                                         &t_svl_rec,
                                         TRUE);
            if (i4_result != SVLR_OK)
            {
                i4_ret = MENUR_FAIL;
            }
            else
            {
                i4_ret = MENUR_OK;
                if (h_ocl_svl == t_g_menu_common.h_svl_air)
                {
                    t_g_menu_common.b_svl_air_dirty = TRUE;
                }
                else
                {
                    t_g_menu_common.b_svl_cable_dirty = TRUE;
                }
            }

        }
        c_svl_unlock(h_ocl_svl);

        if (i4_ret == MENUR_OK && (ui4_sel_mask & SB_VNET_BLOCKED) > 0)
        {
            if (c_svctx_unblock_svc(t_g_menu_common.h_svctx, FALSE) != SVCTXR_OK)
            {
                DBG_ERROR(("<MENU> (MAIN) c_svctx_unblock_svc() failed, ret=%d\r\n",
                           i4_ret));
            }

            if (c_svctx_unblock_svc(t_g_menu_common.h_svctx_sub, FALSE) != SVCTXR_OK)
            {
                DBG_ERROR(("<MENU> (SUB) c_svctx_unblock_svc() failed, ret=%d\r\n",
                           i4_ret));
            }

        }


    }/* finish to update record */

    return i4_ret;
}


/*----------------------------------------------------------------------------
 * Name: _ch_lst2_on_highlight
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static VOID _ch_lst2_on_highlight(
                          VOID*         pv_tag1,
                          VOID*         pv_tag2,
                          VOID*         pv_tag3)

{
     UINT32         ui4_idx = (UINT32)pv_tag1;
     UINT16         ui2_crt_hl_idx;
    INT32           i4_ret;

    UINT16          ui2_rec_id;
    UINT16          ui2_ocl_idx;
    SVL_REC_T       t_svl_rec;
    OCL_SVL_REC_T   t_ocl_svl_rec;
    CHANNEL_LIST_T* pt_ch_lst2;

    i4_ret = menu_page_get_data(ui4_ch_sk_page_id, (VOID**)&pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crt_hl_idx),
                              WGL_PACK(NULL));

    if (pt_ch_lst2 == NULL)
    {
        return;
    }

    if (pt_ch_lst2->b_is_refreshing)
    {
        return;
    }

    if(ui2_crt_hl_idx != ui4_idx)
    {
        return;
    }

    if(_menu_common_page_ch_lst2_current_is_comp())
    {
        return;
    }

    /* get the rec id*/
    ui2_rec_id = pt_ch_lst2->pui2_idx_recid_map[ui4_idx];

    /* get the ocl idx*/
    ui2_ocl_idx = pt_ch_lst2->pui2_idx_ocl_map[ui4_idx];

    DBG_INFO(("<MENU> _ch_lst2_on_sel rec_id:[%u], ocl_idx:[%u]\r\n", ui2_rec_id, ui2_ocl_idx));

    c_memset(&t_svl_rec, 0, sizeof(t_svl_rec));
    c_memset(&t_ocl_svl_rec, 0, sizeof(t_ocl_svl_rec));

    i4_ret = ocl_get_ocl_svl_by_index(ui2_ocl_idx, &t_svl_rec, &t_ocl_svl_rec);
    if (OCLR_OK != i4_ret)
    {
        return ;
    }

    if(t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id == ATSC_CABLE_SVL_ID)
        a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_CABLE);
    else if(t_svl_rec.uheader.t_rec_hdr.ui2_tsl_id == ATSC_TRSTRL_SVL_ID)
        a_cfg_set_tuner_type (APP_CFG_RECID_BS_SRC, APP_CFG_BS_SRC_AIR);

    {
        i4_ret = a_tv_change_channel_by_rec(
                        menu_get_crnt_svctx(),
                        SVCTX_STRM_MODE_AS_LAST,
                        &t_svl_rec,
                        NULL);
        MENU_LOG_ON_FAIL(i4_ret);
    }

    return;
}


static VOID _ch_lst2_hl_timer_cb_fct(
    HANDLE_T                  h_timer,
    VOID*                     pv_tag)
{

    /* execute in timer's thread context */
    menu_request_context_switch(_ch_lst2_on_highlight, pv_tag, NULL, NULL);
}


/*----------------------------------------------------------------------------
 * Name: menu_ch_lst2_refresh
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_refresh(HANDLE_T h_lb_ch)
{
    INT32           i4_result=0;
    INT32           i4_ret=0;
    SVL_REC_T       t_svl_rec;
    CHANNEL_LIST_T* pt_ch_lst2=NULL;

    UINT16          ui2_idx=0;
    UINT16          ui2_rec_num=0;

    BOOL            b_again=FALSE;

    OCL_SVL_REC_T   t_ocl_svl_rec;

    c_memset(&t_svl_rec,0,sizeof(t_svl_rec));


    /* get the channel list data */
    _ch_lst2_get_attach_data(h_lb_ch, &pt_ch_lst2);
    if (pt_ch_lst2 == NULL)
    {
        return MENUR_FAIL;
    }

    if (h_crnt_svl == NULL_HANDLE)
    {
        /* do nothing */
        return MENUR_OK;
    }

    /* Set the refreshing flag */
    pt_ch_lst2->b_is_refreshing = TRUE;

    c_memset(&t_ocl_svl_rec, 0, sizeof(t_ocl_svl_rec));

    /* This loop is used for redo the iteration when somebody modify the SVL
       during our iteration. */
    do
    {
        b_again = FALSE;

        /* clear the list */
        i4_result = c_wgl_do_cmd(h_lb_ch,
                                 WGL_CMD_LB_DEL_ALL,
                                 NULL, NULL);
        MENU_LOG_ON_FAIL(i4_result);

        /* get record number */
        ui2_rec_num = ocl_get_ocl_num();

        /* check if the record number exceeds the max channel number */
        if (ui2_rec_num > pt_ch_lst2->t_ch_lst2_init.ui2_max_rec_num)
        {
            DBG_ERROR(("<MENU> Record number exceeds max sec number: %d < %d.\r\n",
                       ui2_rec_num, pt_ch_lst2->t_ch_lst2_init.ui2_max_rec_num));
            ui2_rec_num = pt_ch_lst2->t_ch_lst2_init.ui2_max_rec_num;
        }

        pt_ch_lst2->ui2_ch_num = ui2_rec_num;

        /* iterate */
        for (ui2_idx = 0; ui2_idx<ui2_rec_num; ui2_idx++)
        {
            /* get the one channel list channel by the channel index */
            i4_ret = ocl_get_ocl_svl_by_index(ui2_idx, &t_svl_rec, &t_ocl_svl_rec);
            if (OCLR_OK != i4_ret)
            {
                DBG_ERROR(("<MENU> ocl_get ocl_svl_by_index failed at idx:[%u], ret:[%d].\r\n", ui2_idx, i4_ret));
                break;
            }

            if (t_svl_rec.uheader.t_rec_hdr.ui4_nw_mask & SB_VNET_FAKE)
            {
                /* skip fake channel */
                continue ;
            }

            i4_result = _ch_lst2_add_ch(h_lb_ch,
                                       pt_ch_lst2,
                                       &t_svl_rec,
                                       ui2_idx);
            if (i4_result < 0)
            {
                i4_ret = i4_result;
                DBG_ERROR(("<MENU> Can't add channel to channel list.\r\n"));
                break;
            }

            b_found_channel = TRUE;
        }

        if (FALSE == b_found_channel)
        {
            i4_result = _ch_lst2_add_empty(h_lb_ch, pt_ch_lst2);
            if (i4_result < 0)
            {
                i4_ret = i4_result;
                DBG_ERROR(("<MENU> Can't add channel to channel list.\r\n"));
            }
        }
    }while(b_again);

    /* Set the refreshing flag */
    pt_ch_lst2->b_is_refreshing = FALSE;

    /* Set the total number to global */
    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&gui2_lb_elem_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _ch_lst2_hlt_curent_ch
 *
 * Description:
 *  Highlight current playing channel
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_hlt_curent_ch(HANDLE_T h_lb_ch)
{
    INT32           i4_ret;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;
    SVL_REC_T       t_svl_rec;
    BOOL            b_found;
    UINT16          ui2_idx = 0;
    UINT16          ui2_elem_num = 0;

    c_memset(&t_svl_rec,0,sizeof(SVL_REC_T));

    /* get the channel list data */
    _ch_lst2_get_attach_data(h_lb_ch, &pt_ch_lst2);
    if (pt_ch_lst2 == NULL)
    {
        return MENUR_FAIL;
    }

    /* get the current svl record */
    i4_ret = menu_get_crnt_svl_rec(&t_svl_rec, &b_found);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_LB_GET_ELEM_NUM,
                          WGL_PACK(&ui2_elem_num),
                          NULL);
    MENU_LOG_ON_FAIL(i4_ret);
    /* No channels*/
    if (ui2_elem_num <= 1)
    {
        i4_ret = _ch_update_scrollbar(h_lb_ch, pt_ch_lst2);
        MENU_LOG_ON_FAIL (i4_ret);
        return i4_ret;
    }

    if(b_found)
    {
        for(ui2_idx=0; ui2_idx<pt_ch_lst2->ui2_ch_num; ui2_idx++)
        {
            if(pt_ch_lst2->pui2_idx_recid_map[ui2_idx] == t_svl_rec.ui2_svl_rec_id)
            {
                break;
            }
        }

        if(ui2_idx == pt_ch_lst2->ui2_ch_num)
        {
            ui2_idx = 0;
        }
    }

    i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                          WGL_CMD_LB_HLT_ELEM_VISIBLE,
                          WGL_PACK(ui2_idx),                            /* hlt elem */
                          WGL_PACK(ui2_idx % CH_SHOW_NUM));    /* hlt pos */
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(
                                  pt_ch_lst2->h_lb_ch,
                                  WGL_SW_NORMAL
                                 );
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ch_update_scrollbar(h_lb_ch, pt_ch_lst2);
    MENU_LOG_ON_FAIL (i4_ret);
    return MENUR_OK;
}
/*----------------------------------------------------------------------------
 * Name: menu_ch_lst2_on_notify
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_on_notify(HANDLE_T    h_lb_ch,
                                WGL_NOTIFY_DATA_T* pt_nfy_data)
{
    switch (pt_nfy_data->ui4_nc_code)
    {
    case WGL_NC_LB_ELEM_SEL:
        {
            UINT16 i2_idx = pt_nfy_data->u.t_lb_elem_sel.ui2_elem_idx;
            BOOL b_sel = pt_nfy_data->u.t_lb_elem_sel.b_is_selected;

            if (menu_get_cond() != MENU_COND_NOT_INIT)
            {
                _ch_lst2_on_sel(h_lb_ch, i2_idx, b_sel);
            }
            break;
        }

    case WGL_NC_LB_ELEM_HLT:
        {
            UINT16            i2_end_index;
            CHANNEL_LIST_T*   pt_ch_list;
#ifdef APP_TTS_SUPPORT
            UTF16_T           w2s_text[_TTS_TEXT_MAX_LEN] ={0};
            UINT16            ui2_idx = pt_nfy_data->u.t_lb_elem_hlt.ui2_elem_idx;
            CHAR              chanel_info[128+1] = {0};
#endif

            _ch_lst2_get_attach_data(h_lb_ch,
                                     &pt_ch_list);


            /* If the CH_LIST is refreshing, do nothing */
            if(pt_ch_list->b_is_refreshing)
            {
                return WMPR_DONE;
            }

            /* Change the HELP_LST */

            /* Get the index */
            c_wgl_do_cmd(h_lb_ch,
                         WGL_CMD_LB_GET_ELEM_NUM,
                         WGL_PACK(&i2_end_index),
                         NULL);

            i2_end_index -= 1;
#ifdef APP_TTS_SUPPORT
            c_wgl_do_cmd(h_lb_ch,
                          WGL_CMD_LB_GET_ITEM_TEXT,
                          WGL_PACK_2(ui2_idx,0),
                          WGL_PACK(w2s_text));

            c_wgl_do_cmd(h_lb_ch,
                              WGL_CMD_LB_GET_ITEM_TEXT,
                              WGL_PACK_2(ui2_idx,2),
                              WGL_PACK(w2s_text+c_uc_w2s_strlen(w2s_text)));

            if(ui2_idx<MAX_CH_NUM)
            {
                c_uc_w2s_to_ps (w2s_text, chanel_info, 128);
                if ( pt_ch_list->t_ch_lst2_init.ui2_msg_title != MLM_MENU_KEY_CH_SK )
                {
                    if(b_is_channel_locked[ui2_idx])
                    {
                        c_strncat(chanel_info, " lock", 5);
                    }
                    else
                    {
                        c_strncat(chanel_info, " unlock", 7);
                    }
                }
                else
                {
                    if(b_is_channel_skiped[ui2_idx])
                    {
                        c_strncat(chanel_info, " skip", 5);
                    }
                    else
                    {
                        c_strncat(chanel_info, " unskip", 7);
                    }

                    c_timer_stop(pt_ch_list->h_hl_timer);
                    c_timer_start(pt_ch_list->h_hl_timer,
                       1000,
                       X_TIMER_FLAG_ONCE,
                       _ch_lst2_hl_timer_cb_fct,
                       (VOID*)(UINT32)ui2_idx);
                }
            }

            c_uc_ps_to_w2s(chanel_info, w2s_text, 128);
            a_tts_switch_dash_to_dash_string(w2s_text,w2s_text,64);
            a_app_tts_play(w2s_text, c_uc_w2s_strlen(w2s_text));
            DBG_INFO(("%s,%d  channel_info= %s  \r\n",__FUNCTION__,__LINE__,chanel_info));
#endif

            break;
        }

    default:
        break;
    }
    return WMPR_DONE;
}


static INT32 _ch_lst2_w2s_ch_r(
            UTF16_T *pt_src_w2s,
            UTF16_T *pt_dst_w2s,
            SIZE_T t_dst_size,
            CHAR a,
            CHAR *b
            )
{
    SIZE_T t_sz;
    CHAR  ps_src[64] = {0};
    CHAR  ps_dst[128] = {0};
    CHAR  ps_a_tmp[2] = {0};

    c_uc_w2s_to_ps(pt_src_w2s, ps_src, 64);
    ps_a_tmp[0] = a;

    CHAR *p_str = ps_src;
    CHAR *p_next;
    while ((p_str = c_strtok(p_str, &ps_a_tmp, &p_next, &t_sz)) != NULL)
    {
        c_strncat(ps_dst, p_str, p_next-p_str);
        if (*p_next == 0)
            break;
        c_strcat(ps_dst, b);
        p_str = p_next;
    }

    SIZE_T t_len = c_strlen(ps_dst);
    if (t_len < t_dst_size)
    {
        return c_uc_ps_to_w2s(ps_dst, pt_dst_w2s, t_len);
    }

    return NAVR_FAIL;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _ch_lst2_proc_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _ch_lst2_proc_fct(HANDLE_T            h_widget,
                               UINT32              ui4_msg,
                               VOID*               pv_param1,
                               VOID*               pv_param2)
{
    INT32        i4_ret=0;
    UTF16_T      w2s_string[256];
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;

    c_memset(w2s_string, 0, sizeof(w2s_string));

    switch (ui4_msg)
    {
    case WGL_MSG_GET_FOCUS:
    {
        i4_ret = _ch_lst2_get_attach_data(h_widget, &pt_ch_lst2);
        MENU_LOG_ON_FAIL(i4_ret);
        if(i4_ret != MENUR_OK || NULL == pt_ch_lst2)
        {
            return WGLR_OK;
        }

        if(pt_ch_lst2->t_ch_lst2_init.ui2_msg_title == MLM_MENU_KEY_CH_SK)
        {
            menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_TAB_HELP_SKIP_CH));
        }
        else if(pt_ch_lst2->t_ch_lst2_init.ui2_msg_title == MLM_MENU_KEY_CH_BK)
        {
            menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_PARENT_CH_BLOCK));
        }
#ifdef APP_TTS_SUPPORT
        UTF16_T           w2s_text[_TTS_TEXT_MAX_LEN] ={0};
        UTF16_T           w2s_text_tts[_TTS_TEXT_MAX_LEN] = {0} ;
        UINT16            ui2_idx = 0;
        CHAR              chanel_info[128+1] = {0};

        if (pt_ch_lst2->b_is_refreshing)
        {
            break;
        }

        if (FALSE == b_found_channel)
        {
            c_uc_w2s_strcpy(w2s_text, MENU_TTS_TEXT(MLM_MENU_KEY_SKIP_NO_CH));
        }
        else
        {
            //get channel num
            i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_idx),
                              WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);

            //get DTV channel info: channel name
            i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                              WGL_CMD_LB_GET_ITEM_TEXT,
                              WGL_PACK_2(ui2_idx, 0),
                              WGL_PACK(w2s_text+c_uc_w2s_strlen(w2s_text)));
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                              WGL_CMD_LB_GET_ITEM_TEXT,
                              WGL_PACK_2(ui2_idx, 2),
                              WGL_PACK(w2s_text+c_uc_w2s_strlen(w2s_text)));
            MENU_LOG_ON_FAIL(i4_ret);

            if(ui2_idx<MAX_CH_NUM)
            {
                c_uc_w2s_to_ps (w2s_text, chanel_info, 128);
                if ( pt_ch_lst2->t_ch_lst2_init.ui2_msg_title != MLM_MENU_KEY_CH_SK )
                {
                    if(b_is_channel_locked[ui2_idx])
                    {
                        c_strncat(chanel_info, " lock", 5);
                    }
                    else
                    {
                        c_strncat(chanel_info, " unlock", 7);
                    }
                }
                else
                {
                    if(b_is_channel_skiped[ui2_idx])
                    {
                        c_strncat(chanel_info, " skip", 5);
                    }
                    else
                    {
                        c_strncat(chanel_info, " unskip", 7);
                    }
                }
            }

            c_uc_ps_to_w2s(chanel_info, w2s_text, 128);
            DBG_INFO(("%s,%d  channel_info= %s  \r\n",__FUNCTION__,__LINE__,chanel_info));
        }

        c_uc_w2s_strncpy(w2s_text_tts,w2s_text,128);
        _ch_lst2_w2s_ch_r(w2s_text_tts, w2s_text_tts, 128, '-', " dash ");

        a_app_tts_play(w2s_text_tts, c_uc_w2s_strlen(w2s_text_tts));
#endif

        break;
    }
    case WGL_MSG_KEY_DOWN:
    case WGL_MSG_KEY_REPEAT:
        {

            UINT32          ui4_keycode = (UINT32)pv_param1;
            UINT16          ui2_total_num;
            UINT16          ui2_idx;

            i4_ret = _ch_lst2_get_attach_data(h_widget, &pt_ch_lst2);
            MENU_LOG_ON_FAIL(i4_ret);
            if(i4_ret != MENUR_OK || NULL == pt_ch_lst2)
            {
                return WGLR_OK;
            }


            /* get the channel list data */
            i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                           WGL_CMD_LB_GET_HLT_INDEX,
                           WGL_PACK(&ui2_idx),
                           WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);

            i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                                 WGL_CMD_LB_GET_ELEM_NUM,
                                 WGL_PACK(&ui2_total_num),
                                 WGL_PACK(NULL));
            MENU_LOG_ON_FAIL(i4_ret);

            switch (ui4_keycode)
            {
            case BTN_CURSOR_LEFT:
                if(pt_ch_lst2->ui4_page_id == ui4_ch_bk_page_id)
                {
                    c_wgl_default_msg_proc(h_widget, ui4_msg, (VOID *)BTN_SELECT, pv_param2);
                     if (ui2_idx != ui2_total_num - 1)
                     {
                         i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                                            WGL_CMD_LB_HLT_NEXT_ELEM,
                                            WGL_PACK(TRUE),
                                            NULL);
                         MENU_LOG_ON_FAIL(i4_ret);
                     }

                     i4_ret = _ch_update_scrollbar(pt_ch_lst2->h_lb_ch, pt_ch_lst2);
                     MENU_LOG_ON_FAIL(i4_ret);

                     return MENUR_OK;
                }
                break;
            case BTN_CURSOR_RIGHT:
                if(pt_ch_lst2->t_ch_lst2_init.b_back_on_left)
                {
                    /* do nothing */
                    return WGLR_OK;
                }
                else
                {
                    if(pt_ch_lst2->ui4_page_id == ui4_ch_bk_page_id)
                    {
                        c_wgl_default_msg_proc(h_widget, ui4_msg, (VOID *)BTN_SELECT, pv_param2);
                         if (ui2_idx != ui2_total_num - 1)
                         {
                             i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                                                WGL_CMD_LB_HLT_NEXT_ELEM,
                                                WGL_PACK(TRUE),
                                                NULL);
                             MENU_LOG_ON_FAIL(i4_ret);
                         }

                         i4_ret = _ch_update_scrollbar(pt_ch_lst2->h_lb_ch, pt_ch_lst2);
                         MENU_LOG_ON_FAIL(i4_ret);

                         return MENUR_OK;
                    }
                    else{
                        /* simulate the page up */
                        pv_param1 = WGL_PACK(BTN_GREEN);
                    }
                }
                break;
            case BTN_SELECT:
            {
                /*NO Channel*/
                if(FALSE==b_found_channel)
                {
                    return WGLR_OK;
                }

                if (b_g_select_is_menu_key)
                {
                     b_g_select_is_menu_key = FALSE;
                     menu_leave(TRUE, 0);
                     return WGLR_OK;
                }
                 else
                 {
                     b_g_select_is_menu_key = FALSE;

#ifdef APP_CH_LOCK_WARN_MSG_ENABLE
                     if (ui2_idx<MAX_CH_NUM &&
                         b_is_channel_locked[ui2_idx] == FALSE)
                     {
                         if (pt_ch_lst2->ui4_page_id == ui4_ch_ubk_page_id)
                         {
                             c_uc_w2s_strcpy(w2s_string, MENU_TEXT(MLM_MENU_KEY_UNLOCK_WARNING_MSG));
                             i4_ret =_warning_msg_set_text(pt_ch_lst2->t_warning_msg.h_txt_txtinfo, w2s_string);
                             MENU_LOG_ON_FAIL(i4_ret);
                             i4_ret =_warning_msg_show(pt_ch_lst2);
                             MENU_LOG_ON_FAIL(i4_ret);
                             return WGLR_OK;
                         }
                     }
                     else
                     {
                         if (pt_ch_lst2->ui4_page_id == ui4_ch_bk_page_id)
                         {
                             c_uc_w2s_strcpy(w2s_string, MENU_TEXT(MLM_MENU_KEY_LOCK_WARNING_MSG));
                             i4_ret =_warning_msg_set_text(pt_ch_lst2->t_warning_msg.h_txt_txtinfo, w2s_string);
                             MENU_LOG_ON_FAIL(i4_ret);
                             i4_ret =_warning_msg_show(pt_ch_lst2);
                             MENU_LOG_ON_FAIL(i4_ret);
                             return WGLR_OK;
                         }
                     }
#endif
                     c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
                     if (ui2_idx != ui2_total_num - 1)
                     {
                         i4_ret = c_wgl_do_cmd(pt_ch_lst2->h_lb_ch,
                                            WGL_CMD_LB_HLT_NEXT_ELEM,
                                            WGL_PACK(TRUE),
                                            NULL);
                         MENU_LOG_ON_FAIL(i4_ret);
                     }

                     i4_ret = _ch_update_scrollbar(pt_ch_lst2->h_lb_ch, pt_ch_lst2);
                     MENU_LOG_ON_FAIL(i4_ret);
                 }
             }
            return MENUR_OK;

            case BTN_CURSOR_UP:
                if (nav_is_component_visible(NAV_COMP_ID_BANNER))
                {
                    banner_view_refresh(TRUE);
                }

                if(ui2_idx == 0)
                {
                    MENU_LOG_ON_FAIL (menu_set_focus_on_backbar(TRUE));
                    menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                    menu_pm_repaint();
                    return WGLR_OK;
                }
                else
                {
                    HANDLE_T  h_last_shadow_item;
                    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_HIDE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
                    return _ch_update_scrollbar(pt_ch_lst2->h_lb_ch, pt_ch_lst2);
                }
            case BTN_CURSOR_DOWN:
                if (nav_is_component_visible(NAV_COMP_ID_BANNER))
                {
                    banner_view_refresh(TRUE);
                }

                if(ui2_idx == ui2_total_num - 1)
                {
                    MENU_LOG_ON_FAIL (menu_help_tip_keytip_set_focus(pt_ch_lst2->h_lb_ch , 0 , FALSE));
                    menu_pm_repaint();
                    return WGLR_OK;
                }
                else
                {
                    c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
                    return _ch_update_scrollbar(pt_ch_lst2->h_lb_ch, pt_ch_lst2);
                }
            case BTN_RETURN:
                i4_ret =menu_nav_back();
                MENU_LOG_ON_FAIL(i4_ret);

                i4_ret =_warning_msg_hide();
                MENU_LOG_ON_FAIL(i4_ret);
                return WGLR_OK;
            case BTN_INVALID:
                if (b_is_jagwheel_ctrl)
                {
                    c_uc_w2s_strcpy(w2s_string, MENU_TEXT(MLM_MENU_KEY_JW_SELECT_WARNING_MSG));
                    i4_ret =_warning_msg_set_text(pt_ch_lst2->t_warning_msg.h_txt_txtinfo, w2s_string);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret =_warning_msg_show(pt_ch_lst2);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    c_uc_w2s_strcpy(w2s_string, MENU_TEXT(MLM_MENU_KEY_LOCK_PAGE_BTN_SELECT_WARNING_MSG));
                    i4_ret =_warning_msg_set_text(pt_ch_lst2->t_warning_msg.h_txt_txtinfo, w2s_string);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret =_warning_msg_show(pt_ch_lst2);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            break;
            case BTN_CUSTOM_2:
                if (b_is_jagwheel_ctrl)
                {
                    c_uc_w2s_strcpy(w2s_string, MENU_TEXT(MLM_MENU_KEY_JW_WHEEL_WARNING_MSG));

                    i4_ret =_warning_msg_set_text(pt_ch_lst2->t_warning_msg.h_txt_txtinfo, w2s_string);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret =_warning_msg_show(pt_ch_lst2);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
                else
                {
                    c_uc_w2s_strcpy(w2s_string, MENU_TEXT(MLM_MENU_KEY_LOCK_PAGE_BTN_DIRECT_WARNING_MSG));
                    i4_ret =_warning_msg_set_text(pt_ch_lst2->t_warning_msg.h_txt_txtinfo, w2s_string);
                    MENU_LOG_ON_FAIL(i4_ret);
                    i4_ret =_warning_msg_show(pt_ch_lst2);
                    MENU_LOG_ON_FAIL(i4_ret);
                }
            break;
            default:
                break;
            }
        }
    default:
        break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _frm_proc_fct
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 *
 ----------------------------------------------------------------------------*/
static INT32 _cnt_frm_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    switch (ui4_msg)
    {
    case WGL_MSG_NOTIFY:
        {
            HANDLE_T h_source = (HANDLE_T)param1;
            WGL_NOTIFY_DATA_T* pt_nfy_data = (WGL_NOTIFY_DATA_T*)param2;
            _ch_lst2_on_notify(h_source, pt_nfy_data);
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}


/*----------------------------------------------------------------------------
 * Name: _ch_lst_create
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _ch_lst2_create(HANDLE_T    h_parent,
                             INT32       i4_x,
                             INT32       i4_y,
                             INT32       i4_w,
                             INT32       i4_h,
                             CHANNEL_LIST_T*         pt_ch_lst2,
                             HANDLE_T*               ph_lb_ch)
{
    INT32               i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[4];
    GL_RECT_T           t_rect;
    WGL_LB_KEY_MAP_T    t_lb_key_map;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;

    /* channel no. or none */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = CH_LST2_COL0_ALIGN;
    at_cols[0].ui2_max_text_len = MAX_CH_NUM_LEN;
    at_cols[0].ui2_width        = CH_LST2_COL0_W;

    /* ATV/DTV */
    at_cols[1].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[1].ui1_align        = CH_LST2_COL1_ALIGN;
    at_cols[1].ui2_max_text_len = MAX_CH_TYPE_LEN;
    at_cols[1].ui2_width        = CH_LST2_COL1_W;

    /* channel name or starting time */
    at_cols[2].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[2].ui1_align        = CH_LST2_COL2_ALIGN;
    at_cols[2].ui2_max_text_len = MAX_CH_NAME_LEN;
    at_cols[2].ui2_width        = CH_LST2_COL2_W+120;

    /* pre-selected */
    at_cols[3].e_col_type       = LB_COL_TYPE_IMG_SUIT;
    at_cols[3].ui1_align        = CH_LST2_COL3_ALIGN;
    at_cols[3].ui2_width        = CONTENT_W - (CH_LST2_COL0_W+CH_LST2_COL1_W+CH_LST2_COL2_W);


    t_lb_init.ui4_style         = WGL_STL_LB_FORCE_HLT
                                  | WGL_STL_LB_ELEM_NO_PUSH
                                  | WGL_STL_LB_MULTI_SEL;

    if(!pt_ch_lst2->t_ch_lst2_init.b_scroll)
    {
        t_lb_init.ui4_style         |= WGL_STL_LB_NO_SCROLL;
    }

    if(!pt_ch_lst2->t_ch_lst2_init.b_wrap_over)
    {
        t_lb_init.ui4_style         |= WGL_STL_LB_NO_WRAP_OVER;
    }

    t_lb_init.ui2_max_elem_num  = pt_ch_lst2->t_ch_lst2_init.ui2_max_rec_num;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 4;
    t_lb_init.at_cols           = at_cols;

    i4_ret = _ch_image_create(h_parent,
                              i4_x,
                              i4_y,
                              i4_w,
                              i4_h,
                              pt_ch_lst2);

    i4_y += CHN_LIST_ARROW_HEIGHT;
    i4_h = (MENU_ITEM_V_HEIGHT * CH_SHOW_NUM);
    SET_RECT_BY_SIZE (&t_rect,
                      i4_x,
                      i4_y,
                      i4_w,
                      i4_h);

    i4_ret = menu_list2_create(h_parent,
                               &t_rect,
                               _ch_lst2_proc_fct,
                               &t_lb_init,
                               NULL,
                               ph_lb_ch);
    if (i4_ret != WGLR_OK)
    {
        DBG_ERROR(("<MENU> create listbox for channel list failed - %d\n", i4_ret));
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* Set background image */
    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (*ph_lb_ch,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* Set Key Map */
    c_memset(&t_lb_key_map, 0, sizeof(WGL_CMD_LB_SET_KEY_MAP));
    t_lb_key_map.ui4_key_next   = BTN_CURSOR_DOWN;
    t_lb_key_map.ui4_key_prev   = BTN_CURSOR_UP;
    t_lb_key_map.ui4_key_select = BTN_SELECT;
    t_lb_key_map.ui4_key_page_up    = BTN_RED;
    t_lb_key_map.ui4_key_page_down  = BTN_GREEN;
    i4_ret = c_wgl_do_cmd(*ph_lb_ch, WGL_CMD_LB_SET_KEY_MAP, &t_lb_key_map, NULL);
    MENU_LOG_ON_FAIL(i4_ret);

    /* attach data */
    i4_ret = _ch_lst2_set_attach_data(*ph_lb_ch, pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _ch_lst2_alloc_resource(
    CHANNEL_LIST_T* pt_ch_lst2)
{
    INT32 i4_ret = MENUR_FAIL;
    MENU_COMMON_CHANNEL_LIST_INIT_T* pt_ch_lst2_init = NULL;
    HANDLE_T    h_cnt_frm;

    if (pt_ch_lst2 == NULL)
    {
        return MENUR_FAIL;
    }

    pt_ch_lst2_init = &pt_ch_lst2->t_ch_lst2_init;

    /* Attach data */
    do
    {
        i4_ret = menu_page_get_cnt_frm(pt_ch_lst2->ui4_page_id, &h_cnt_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        pt_ch_lst2->pui2_idx_recid_map =
            c_mem_alloc(pt_ch_lst2_init->ui2_max_rec_num * sizeof(UINT16));
        if(pt_ch_lst2->pui2_idx_recid_map == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        pt_ch_lst2->pui2_idx_ocl_map =
            c_mem_alloc(pt_ch_lst2_init->ui2_max_rec_num * sizeof(UINT16));
        if(pt_ch_lst2->pui2_idx_ocl_map == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        /* Create channel list box */
        i4_ret = _ch_lst2_create(h_cnt_frm,
                    CH_LST_X,
                    CH_LST_Y,
                    CH_LST_W,
                    CH_LST_H,
                    pt_ch_lst2,
                    &pt_ch_lst2->h_lb_ch);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
        c_wgl_set_visibility(pt_ch_lst2->h_img_up, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_ch_lst2->h_img_down, WGL_SW_HIDE);

        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }
         c_timer_create(&pt_ch_lst2->h_hl_timer);

        i4_ret = MENUR_OK;
    }while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_ch_lst2 != NULL)
        {
            if(pt_ch_lst2->h_lb_ch != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_lb_ch);
            }

            if(pt_ch_lst2->h_img_up != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_img_up);
            }

            if(pt_ch_lst2->h_img_down != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_img_down);
            }

            if(pt_ch_lst2->h_img_sep_up != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_img_sep_up);
            }

            if(pt_ch_lst2->h_img_sep_down != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_img_sep_down);
            }

            if(pt_ch_lst2->pui2_idx_recid_map != NULL)
            {
                c_mem_free(pt_ch_lst2->pui2_idx_recid_map);
            }

            if(pt_ch_lst2->pui2_idx_ocl_map != NULL)
            {
                c_mem_free(pt_ch_lst2->pui2_idx_ocl_map);
            }
        }
    }

    return i4_ret;
}

static INT32 _ch_lst2_free_resource(
    CHANNEL_LIST_T* pt_ch_lst2)
{
    if(pt_ch_lst2->h_lb_ch != NULL_HANDLE)
    {
        c_wgl_destroy_widget_ex(pt_ch_lst2->h_lb_ch, FALSE);
    }

    if (pt_ch_lst2->h_img_down != NULL_HANDLE)
    {
        c_wgl_destroy_widget_ex(pt_ch_lst2->h_img_down, FALSE);
    }

    if (pt_ch_lst2->h_img_up != NULL_HANDLE)
    {
        c_wgl_destroy_widget_ex(pt_ch_lst2->h_img_up, FALSE);
    }

    if (pt_ch_lst2->h_img_sep_up != NULL_HANDLE)
    {
        c_wgl_destroy_widget_ex(pt_ch_lst2->h_img_sep_up, FALSE);
    }

    if (pt_ch_lst2->h_img_sep_down != NULL_HANDLE)
    {
        c_wgl_destroy_widget_ex(pt_ch_lst2->h_img_sep_down, FALSE);
    }

    if(pt_ch_lst2->pui2_idx_recid_map != NULL)
    {
        c_mem_free(pt_ch_lst2->pui2_idx_recid_map);
    }

    if(pt_ch_lst2->pui2_idx_ocl_map != NULL)
    {
        c_mem_free(pt_ch_lst2->pui2_idx_ocl_map);
    }

    if(pt_ch_lst2->h_hl_timer != NULL_HANDLE);
    {
        c_timer_delete(pt_ch_lst2->h_hl_timer);
    }
        return MENUR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_msg_timeout_to_hide_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _warning_msg_timeout_to_hide_msg(
                                     VOID* pv_data,
                                     SIZE_T  z_data_size)
{
    _warning_msg_hide();
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_msg_hide_msg_timer_nfy
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _warning_msg_hide_msg_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    /* execute in timer's thread context */
    menu_async_invoke(_warning_msg_timeout_to_hide_msg,
                      (VOID*)NULL,
                      (SIZE_T)0,
                      FALSE);
}

/*-----------------------------------------------------------------------------
 * Name
 *      _warning_msg_reset_timer
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static VOID _warning_msg_reset_timer(
                    CHANNEL_LIST_T* pt_ch_lst2
                    )
{
    INT32 i4_ret;

    _warning_msg_stop_timer(pt_ch_lst2);

    i4_ret = c_timer_start(
                    pt_ch_lst2->t_warning_msg.h_timer,
                    WARNING_MSG_TIMEOUT,
                    X_TIMER_FLAG_ONCE,
                    _warning_msg_hide_msg_timer_nfy,
                    NULL
                    );
    if (i4_ret != OSR_OK) {
        ABORT_APPL(DBG_MOD_NAVIGATOR, ("can french unlock page::h_timer failed!"));
    }
}

 /*-----------------------------------------------------------------------------
 * Name
 *      _warning_msg_frm_proc_fct
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 static INT32 _warning_msg_btn_proc_fct(HANDLE_T   h_widget,
                                        UINT32     ui4_msg,
                                        VOID*      param1,
                                        VOID*      param2)
{
    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_SELECT:
                case BTN_EXIT:
                {
                    _warning_msg_hide();
                    break;
                }
            default:
                break;
            }
        }
        case WGL_MSG_KEY_UP:
        {
            UINT32 ui4_keycode = (UINT32)param1;
            switch (ui4_keycode)
            {
                case BTN_INPUT_SRC:
                case BTN_PRG_INFO:
                case BTN_PIP:
                case BTN_PRG_UP:
                case BTN_PRG_DOWN:
                {
                    _warning_msg_hide();
                    a_amb_default_key_handler (WGL_MSG_KEY_DOWN,
                                               (VOID*)ui4_keycode,
                                               (VOID*)NULL);
                    break;
                }
            default:
                break;
            }
        }
        default:
            break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);

}
/*-----------------------------------------------------------------------------
 * Name
 *      _create_warning_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
 static INT32 _create_warning_msg(HANDLE_T h_parent,
                                  WARNING_MSG_T* pt_warning_msg)
 {
    GL_RECT_T           t_rect;
    GL_RECT_T           t_inset;
    UINT32              ui4_style = 0;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    INT32               i4_ret;

    c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     WARNING_MSG_X,
                     WARNING_MSG_Y,
                     WARNING_MSG_W,
                     WARNING_MSG_H);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_warning_msg->h_msg_frm);
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    c_memset(&t_img_info, 0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_img_msg_background;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_img_msg_background;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_img_msg_background;

    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_msg_frm,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    ui4_style =  WGL_STL_GL_NO_IMG_UI|WGL_STL_TEXT_MAX_512|WGL_STL_TEXT_MULTILINE;

    SET_RECT_BY_SIZE(&t_rect,
                     0,
                     0,
                     WARNING_MSG_W,
                     WARNING_MSG_H-WARNING_BTN_H);

    i4_ret = c_wgl_create_widget(pt_warning_msg->h_msg_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_warning_msg->h_txt_txtinfo);
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_txt_txtinfo,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_color_warning_msg_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_color_warning_msg_txt;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_color_warning_msg_txt;
    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =t_g_color_warning_msg_bk;
    t_clr_info.u_color_data.t_standard.t_highlight    =t_g_color_warning_msg_bk;
    t_clr_info.u_color_data.t_standard.t_disable      =t_g_color_warning_msg_bk;
    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_txt_txtinfo,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     WARNING_BTN_X,
                     WARNING_BTN_Y,
                     WARNING_BTN_W,
                     WARNING_BTN_H);

    i4_ret = c_wgl_create_widget(pt_warning_msg->h_msg_frm,
                                HT_WGL_WIDGET_BUTTON,
                                WGL_CONTENT_BUTTON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                _warning_msg_btn_proc_fct,
                                255,
                                NULL,
                                NULL,
                                &pt_warning_msg->h_msg_btn);
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_msg_btn,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push               = h_g_menu_img_item_hlt_bk;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_img_item_hlt_bk;

    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_msg_btn,
                           WGL_CMD_GL_SET_IMAGE,
                           WGL_PACK(WGL_IMG_BK),
                           WGL_PACK(& t_img_info));
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable = t_g_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_disable = t_g_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_highlight = t_g_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_push = t_g_color_warning_msg_txt;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight = t_g_color_warning_msg_txt;
    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_msg_btn,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_msg_btn,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_msg_btn,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    i4_ret = c_wgl_do_cmd(pt_warning_msg->h_msg_btn,
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(MLM_MENU_TEXT(0,MLM_MENU_KEY_OK)),
                          WGL_PACK(c_uc_w2s_strlen(MLM_MENU_TEXT(0,MLM_MENU_KEY_OK))));
    if (MENUR_OK != i4_ret)
    {
        return i4_ret;
    }

    c_wgl_set_visibility(pt_warning_msg->h_msg_frm, WGL_SW_HIDE);
    pt_warning_msg->h_timer = NULL_HANDLE;

    i4_ret = c_timer_create(&(pt_warning_msg->h_timer));
    if (i4_ret != OSR_OK) {
        return MENUR_FAIL;
    }

    b_is_msg_on = FALSE;
    return MENUR_OK;

 }

static VOID _ch_lst2_sync_change_source_to_tv(
    VOID*                              pv_this,
    VOID*                              pv_unused2,
    VOID*                              pv_unused3)
{
    nav_ipts_switch_src(NAV_IPTS_SMS_TO_TV, TV_WIN_ID_MAIN, 0);
    menu_custom_update_the_old_display_region_after_change_source_tv();
}
static INT32 _ch_lst2_change_source_to_tv(VOID)
{
    CHAR            s_disp_name[ACFG_MAX_DISP_NAME+1] = {0};
    UINT8           ui1_input_id = 0;
    ISL_REC_T       t_isl_rec;
    INT32           i4_ret = MENUR_OK;

    i4_ret = a_cfg_av_get_disp_name(s_disp_name, sizeof(s_disp_name));
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_cfg_get_input_src(s_disp_name, &ui1_input_id);
    MENU_LOG_ON_FAIL(i4_ret);
    i4_ret = a_isl_get_rec_by_id(ui1_input_id, &t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);
    if((INP_SRC_TYPE_TV == t_isl_rec.e_src_type))
    {
        DBG_LOG_PRINT(("%s_%d current source is tv \n ",__FUNCTION__,__LINE__));
        return MENUR_OK;
    }

    rest_event_notify_current_input("tuner");

    nav_request_context_switch(_ch_lst2_sync_change_source_to_tv,
                               NULL,
                               NULL,
                               NULL);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
                        page inteface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32 i4_ret = MENUR_FAIL;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;
    MENU_COMMON_CHANNEL_LIST_INIT_T* pt_ch_lst2_init =
        (MENU_COMMON_CHANNEL_LIST_INIT_T*)pv_create_data;
    HANDLE_T    h_cnt_frm;
    HANDLE_T    h_root_frm;

    if(pt_ch_lst2_init == NULL)
    {
        return MENUR_INV_ARG;
    }

    /* Attach data */
    do
    {
        i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        pt_ch_lst2 = c_mem_alloc(sizeof(CHANNEL_LIST_T));
        if(pt_ch_lst2 == NULL)
        {
            i4_ret = MENUR_OUT_OF_MEMORY;
            break;
        }

        c_memset(pt_ch_lst2, 0, sizeof(CHANNEL_LIST_T));

        c_memcpy(&pt_ch_lst2->t_ch_lst2_init,
                 pt_ch_lst2_init,
                 sizeof(MENU_COMMON_CHANNEL_LIST_INIT_T));

        pt_ch_lst2->ui4_page_id = ui4_page_id;

        i4_ret = menu_page_set_data(ui4_page_id, pt_ch_lst2);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = MENUR_FAIL;
            break;
        }

        i4_ret = menu_page_set_proc_func(ui4_page_id,
                                         _cnt_frm_proc_fct);
        if(i4_ret != WGLR_OK)
        {
            break;
        }

        i4_ret = menu_pm_get_root_frm(&h_root_frm);
        if(i4_ret != MENUR_OK)
        {
            break;
        }

        i4_ret = _create_warning_msg(h_root_frm,&pt_ch_lst2->t_warning_msg);
        MENU_LOG_ON_FAIL(i4_ret);

    }while(0);

    if(i4_ret != MENUR_OK)
    {
        if(pt_ch_lst2 != NULL)
        {
            if(pt_ch_lst2->h_lb_ch != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_lb_ch);
            }

            if(pt_ch_lst2->h_img_up != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_img_up);
            }

            if(pt_ch_lst2->h_img_down != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_img_down);
            }

            if(pt_ch_lst2->h_img_sep_up != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_img_sep_up);
            }

            if(pt_ch_lst2->h_img_sep_down != NULL_HANDLE)
            {
                c_wgl_destroy_widget(pt_ch_lst2->h_img_sep_down);
            }

            c_mem_free(pt_ch_lst2);
        }
    }

    i4_ret = a_cfg_notify_reg(APP_CFG_GRPID_VCHIP,
                              NULL,
                              _rating_enabled_cfg_vchip_nfy_fct,
                              &ui2_g_rating_enabled_cfg);
    MENU_LOG_ON_FAIL(i4_ret);

    return i4_ret;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_ch_lst2);

    if(i4_ret == MENUR_OK)
    {
        if(pt_ch_lst2 != NULL)
        {
            c_mem_free(pt_ch_lst2);
        }
    }

    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;

    b_found_channel = FALSE;

    h_crnt_svl = menu_get_crnt_svl();

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ch_lst2_alloc_resource(pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ch_lst2_refresh(pt_ch_lst2->h_lb_ch);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_main_set_title(pt_ch_lst2->t_ch_lst2_init.ui2_msg_title);

    menu_help_tip_keytip_show(FALSE);

    //menu_pm_repaint();

    i4_ret = _ch_lst2_hlt_curent_ch(pt_ch_lst2->h_lb_ch);
    MENU_LOG_ON_FAIL(i4_ret);
    b_is_msg_on = FALSE;
    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{
    INT32 i4_ret;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ch_lst2_free_resource(pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_help_tip_keytip_show(TRUE);

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    INT32 i4_ret;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;

    //TV channels only visible in comp/TV,need change to TV in comp
    _ch_lst2_change_source_to_tv();

    i4_ret = menu_page_get_data(ui4_page_id, (VOID**)&pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_set_focus(pt_ch_lst2->h_lb_ch, WGL_NO_AUTO_REPAINT);


    menu_set_backbar_proc(_backbar_proc_fct) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(_homebar_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_lose_focus(UINT32 ui4_page_id)
{
    menu_set_backbar_proc(NULL) ;

    /* set callback function for homebar */
    menu_set_homebar_proc(NULL);

    return MENUR_OK;
}

static INT32 _on_page_update(UINT32 ui4_page_id,
                             UINT32 ui4_update_mask)
{
    INT32               i4_ret;
    MENU_PAGE_STATE_T   e_state;
    ISL_REC_T           t_isl_rec;

    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        /* do_nothing */
    }

    /* leave channel related items when input source is changed to non-TV. */
    if((ui4_update_mask & MENU_PAGE_UMASK_REFRESH) != 0)
    {
        i4_ret = menu_page_get_state(ui4_page_id, &e_state);
        MENU_LOG_ON_FAIL(i4_ret);

        if (e_state == MENU_PAGE_STATE_SHOW || e_state == MENU_PAGE_STATE_FOCUS)
        {
            i4_ret = menu_get_crnt_isl(&t_isl_rec);
            MENU_LOG_ON_FAIL(i4_ret);

            if (t_isl_rec.e_src_type == INP_SRC_TYPE_TV || _menu_common_page_ch_lst2_current_is_comp())
            {
                /* do_nothing */
            }
            else
            {
                menu_nav_back();
            }
        }
    }

    return MENUR_OK;
}
/*-----------------------------------------------------------------------------
                    global functions declarations
 ----------------------------------------------------------------------------*/
extern INT32 menu_common_create_page_sk_ch2(UINT32 *pui4_page_id)
{
    MENU_COMMON_CHANNEL_LIST_INIT_T t_ch_lst2_init;
    INT32                           i4_ret;

    c_memset(&t_ch_lst2_init, 0, sizeof(MENU_COMMON_CHANNEL_LIST_INIT_T));
    t_ch_lst2_init.ui2_msg_title            = MLM_MENU_KEY_CH_SK;
    t_ch_lst2_init.ui2_max_rec_num          = CH_LST_ELEM_N;

    t_ch_lst2_init.h_img_normal             = h_g_menu_img_skip;
    t_ch_lst2_init.h_img_highlight          = h_g_menu_img_skip_hlt;
    t_ch_lst2_init.h_img_selected           = h_g_menu_img_unskip;
    t_ch_lst2_init.h_img_selected_highlight = h_g_menu_img_unskip_hlt;

    t_ch_lst2_init.ui4_lst_mask             = SB_VNET_ACTIVE;
    t_ch_lst2_init.ui4_sel_mask             = SB_VNET_VISIBLE;
    t_ch_lst2_init.e_brdcst_type            = BRDCST_TYPE_UNKNOWN;
    t_ch_lst2_init.b_scroll                 = CH_LST2_STL_SCROLL;
    t_ch_lst2_init.b_wrap_over              = CH_LST2_STL_WRAP_OVER;
    t_ch_lst2_init.b_back_on_left           = CH_LST2_BACK_ON_LEFT;

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_ch_lst2,
                               (VOID*)&t_ch_lst2_init,
                               pui4_page_id);
    if (i4_ret == MENUR_OK)
    {
        ui4_ch_sk_page_id = *pui4_page_id;
    }
    return i4_ret;
}

extern INT32 menu_common_create_page_ubk_ch2(UINT32 *pui4_page_id)
{
    MENU_COMMON_CHANNEL_LIST_INIT_T t_ch_lst2_init;
    INT32                           i4_ret;

    c_memset(&t_ch_lst2_init, 0, sizeof(MENU_COMMON_CHANNEL_LIST_INIT_T));

    t_ch_lst2_init.ui2_msg_title            = MLM_MENU_KEY_CH_UBK;
    t_ch_lst2_init.ui2_max_rec_num          = CH_LST_ELEM_N;

    t_ch_lst2_init.h_img_normal             = h_g_unlock_grey_v2;
#if 0
    t_ch_lst2_init.h_img_highlight          = h_g_menu_img_unlock_hlt;
#else
    t_ch_lst2_init.h_img_highlight          = h_g_unlock_grey_v2;
#endif
    t_ch_lst2_init.h_img_selected           = h_g_lock_grey_v2;
#if 0
    t_ch_lst2_init.h_img_selected_highlight = h_g_menu_img_lock_hlt;
#else
    t_ch_lst2_init.h_img_selected_highlight = h_g_lock_grey_v2;
#endif
    t_ch_lst2_init.ui4_lst_mask             = SB_VNET_ACTIVE;
    t_ch_lst2_init.ui4_sel_mask             = SB_VNET_BLOCKED;
    t_ch_lst2_init.e_brdcst_type            = BRDCST_TYPE_UNKNOWN;
    t_ch_lst2_init.b_scroll                 = CH_LST2_STL_SCROLL;
    t_ch_lst2_init.b_wrap_over              = CH_LST2_STL_WRAP_OVER;
    t_ch_lst2_init.b_back_on_left           = CH_LST2_BACK_ON_LEFT;

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_ch_lst2,
                        (VOID*)&t_ch_lst2_init,
                        pui4_page_id);

    if (i4_ret == MENUR_OK)
    {
        ui4_ch_ubk_page_id = *pui4_page_id;
    }
    return i4_ret;
}
extern INT32 menu_common_create_page_bk_ch2(UINT32 *pui4_page_id)
{
    MENU_COMMON_CHANNEL_LIST_INIT_T t_ch_lst2_init;
    INT32                           i4_ret;

    c_memset(&t_ch_lst2_init, 0, sizeof(MENU_COMMON_CHANNEL_LIST_INIT_T));
    t_ch_lst2_init.ui2_msg_title            = MLM_MENU_KEY_CH_BK;
    t_ch_lst2_init.ui2_max_rec_num          = CH_LST_ELEM_N;

    t_ch_lst2_init.h_img_normal             = h_g_unlock_grey_v2;
    t_ch_lst2_init.h_img_highlight          = h_g_unlock_grey_v2;
    t_ch_lst2_init.h_img_selected           = h_g_lock_grey_v2;
    t_ch_lst2_init.h_img_selected_highlight = h_g_lock_grey_v2;

    t_ch_lst2_init.ui4_lst_mask             = SB_VNET_ACTIVE;
    t_ch_lst2_init.ui4_sel_mask             = SB_VNET_BLOCKED;
    t_ch_lst2_init.e_brdcst_type            = BRDCST_TYPE_UNKNOWN;
    t_ch_lst2_init.b_scroll                 = CH_LST2_STL_SCROLL;
    t_ch_lst2_init.b_wrap_over              = CH_LST2_STL_WRAP_OVER;
    t_ch_lst2_init.b_back_on_left           = 0;

    i4_ret = menu_pm_page_create(&t_g_menu_common_page_ch_lst2,
                                 (VOID*)&t_ch_lst2_init,
                                 pui4_page_id);
    if (i4_ret == MENUR_OK)
    {
        ui4_ch_bk_page_id = *pui4_page_id;
    }
    return i4_ret;
}

extern INT32 menu_common_create_page_fav_lst2(UINT32 *pui4_page_id)
{
    MENU_COMMON_CHANNEL_LIST_INIT_T t_ch_lst2_init;

    c_memset(&t_ch_lst2_init, 0, sizeof(MENU_COMMON_CHANNEL_LIST_INIT_T));
    t_ch_lst2_init.ui2_msg_title            = MLM_MENU_KEY_CH_FAV;
    t_ch_lst2_init.ui2_max_rec_num          = CH_LST_ELEM_N;
    t_ch_lst2_init.h_img_normal             = h_g_menu_img_nfav;
    t_ch_lst2_init.h_img_highlight          = h_g_menu_img_nfav_hlt;
    t_ch_lst2_init.h_img_selected           = h_g_menu_img_fav;
    t_ch_lst2_init.h_img_selected_highlight = h_g_menu_img_fav_hlt;
    t_ch_lst2_init.ui4_lst_mask             = SB_VNET_ACTIVE;
    t_ch_lst2_init.ui4_sel_mask             = SB_VNET_FAVORITE1;
    t_ch_lst2_init.e_brdcst_type            = BRDCST_TYPE_UNKNOWN;
    t_ch_lst2_init.b_scroll                 = CH_LST2_STL_SCROLL;
    t_ch_lst2_init.b_wrap_over              = CH_LST2_STL_WRAP_OVER;
    t_ch_lst2_init.b_back_on_left           = CH_LST2_BACK_ON_LEFT;

    return menu_pm_page_create(&t_g_menu_common_page_ch_lst2,
                               (VOID*)&t_ch_lst2_init,
                               pui4_page_id);
}

extern INT32 mneu_common_ch_lst2_create(
    MENU_COMMON_CHANNEL_LIST_INIT_T t_ch_lst_init,
    UINT32*                         pui4_page_id)
{
    return menu_pm_page_create(&t_g_menu_common_page_ch_lst2,
                               (VOID*)&t_ch_lst_init,
                               pui4_page_id);
}

extern BOOL menu_common_page_ch_lst2_is_enabled(VOID)
{
    INT32       i4_ret;
    HANDLE_T    h_crnt_svl = menu_get_crnt_svl();
    UINT16      ui2_rec_num = 0;
    UINT32      ui4_ver_id = 0;

    if(h_crnt_svl == NULL_HANDLE)
    {
        return FALSE;
    }
    else
    {
        i4_ret = c_svl_get_num_rec_by_brdcst_type(h_crnt_svl,
                                                  BRDCST_TYPE_UNKNOWN,
                                                  SB_VNET_ACTIVE,
                                                  &ui2_rec_num,
                                                  &ui4_ver_id);
        if(i4_ret != 0 ||
           ui2_rec_num == 0)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}

extern BOOL menu_common_page_ch_lst2_is_analog_enabled(VOID)
{
    INT32       i4_ret;
    HANDLE_T    h_crnt_svl = menu_get_crnt_svl();
    UINT16      ui2_rec_num = 0;
    UINT32      ui4_ver_id = 0;

    if(h_crnt_svl == NULL_HANDLE)
    {
        return FALSE;
    }
    else
    {
        i4_ret = c_svl_get_num_rec_by_brdcst_type(h_crnt_svl,
                                                  BRDCST_TYPE_ANALOG,
                                                  SB_VNET_ACTIVE,
                                                  &ui2_rec_num,
                                                  &ui4_ver_id);
        if(i4_ret != 0 ||
           ui2_rec_num == 0)
        {
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}

extern INT32 menu_common_page_ch_lst2_init(VOID)
{
    t_g_menu_common_page_ch_lst2.pf_menu_page_create =    _on_page_create;
    t_g_menu_common_page_ch_lst2.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_common_page_ch_lst2.pf_menu_page_show=       _on_page_show;
    t_g_menu_common_page_ch_lst2.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_common_page_ch_lst2.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_common_page_ch_lst2.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_common_page_ch_lst2.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

//for update page when svl updated by app
INT32 menu_common_page_ch_lst2_refresh(VOID)
{

    INT32 i4_ret;
    CHANNEL_LIST_T* pt_ch_lst2 = NULL;
    UINT32 crnt_page_id = menu_get_current_page_id();
    if((ui4_ch_sk_page_id != crnt_page_id) && (ui4_ch_bk_page_id != crnt_page_id))
        return MENUR_FAIL;

    i4_ret = menu_page_get_data(crnt_page_id, (VOID**)&pt_ch_lst2);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = _ch_lst2_refresh(pt_ch_lst2->h_lb_ch);
    MENU_LOG_ON_FAIL(i4_ret);

    menu_main_set_title(pt_ch_lst2->t_ch_lst2_init.ui2_msg_title);


    i4_ret = _ch_lst2_hlt_curent_ch(pt_ch_lst2->h_lb_ch);
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}


static BOOL _menu_common_page_ch_lst2_current_is_comp(VOID)
{
    INT32           i4_ret = 0;
    ISL_REC_T       t_isl_rec;

    i4_ret = menu_get_crnt_isl(&t_isl_rec);
    MENU_LOG_ON_FAIL(i4_ret);

    return a_nav_ipts_is_comp_source(&t_isl_rec);
}

#endif /* COMMON_CH_LST2_ENABLE */

