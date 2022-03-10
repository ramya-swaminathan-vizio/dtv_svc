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
 * $RCSfile: menu_page_3d_setting.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: $
 * $SWAuthor: $
 * $MD5HEX: $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"
#include "c_version.h"
#include "u_atsc_si_eng.h"
#include "c_atsc_si_eng.h"

#include "app_util/a_cfg.h"
#include "app_client.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_screen_mode.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/nav/nav_colors.h"
//#include "menu_rm_parse.h"
#include "c_svctx.h"
#include "app_util/a_icl.h"
#include "res/app_util/icl/a_icl_custom.h"
#include "res/app_util/ui/ui_custom.h"
#include "menu2/menu_dbg.h"

/*-----------------------------------------------------------------------------
                        customizable macros
 ----------------------------------------------------------------------------*/
#define X_3D_SETTING_ICON_GAP         (3)
#define X_3D_SETTING_TITLE_TXT_X      (0)
#define X_3D_SETTING_TITLE_TXT_Y      (6)
#define X_3D_SETTING_TITLE_TXT_W      (X_3D_SETTING_FRAME_W)
#define X_3D_SETTING_TITLE_TXT_H      (20)

#define X_3D_SETTING_TXT_X      (X_3D_SETTING_BTN_X)
#define X_3D_SETTING_TXT_Y      (105) /* 30 + 77 - 20*/
#define X_3D_SETTING_TXT_W      (113)
#define X_3D_SETTING_TXT_H      (20)

#define X_3D_SETTING_BTN_X      (3)
#define X_3D_SETTING_BTN_Y      (33)
#define X_3D_SETTING_BTN_W      (113)
#define X_3D_SETTING_BTN_H      (96)

#define X_3D_SETTING_FRAME_W    ((X_3D_SETTING_ICON_GAP+X_3D_SETTING_BTN_W)*4 + X_3D_SETTING_BTN_X)
#define X_3D_SETTING_FRAME_H    (129)
#define X_3D_SETTING_FRAME_X    ((SCREEN_W - X_3D_SETTING_FRAME_W)/2)
#define X_3D_SETTING_FRAME_Y    ((SCREEN_H - X_3D_SETTING_FRAME_H)/2)

#define MENU_3D_PAGE_ICON_MAX_NUM   4

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum
{
    X_2D_TAG = 0,
    X_2D_TAG_2D_PLAY,
    X_2D_TAG_3D_PLAY,
    X_3D_TAG_2D_PLAY,
    X_3D_TAG_3D_PLAY,
    X_3D_MAX_NUM
}X_3D_OUTPUT_STATUS_T;

typedef struct _MENU_3D_SETTING_VIEW_T
{
    HANDLE_T        h_frame;
    HANDLE_T        h_title_txt;
    HANDLE_T        h_txt[MENU_3D_PAGE_ICON_MAX_NUM];
    HANDLE_T        h_btn[MENU_3D_PAGE_ICON_MAX_NUM];

    HANDLE_T        h_dialog_ok;
    HANDLE_T        h_timer;

    BOOL            b_is_3D_content;
    UINT8           ui1_focus_idx;
    VSH_SRC_TAG3D_TYPE_T    e_3D_type;
    X_3D_OUTPUT_STATUS_T    e_current_status;
}MENU_3D_SETTING_VIEW_T;

/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
extern BOOL                     b_3d_mode_playing;
MENU_PAGE_FCT_TBL_T             t_g_menu_custom_page_3D_setting;
MENU_3D_SETTING_VIEW_T          t_g_3D_setting_view;
const UINT8   aui_elem_num[X_3D_MAX_NUM] = {2,
                                            4,
                                            4,
                                            2,
                                            2};

static BOOL                     b_is_menu_showed = FALSE;

static INT32 _3D_setting_show_widgets(UINT8  ui1_focus_idx, BOOL  b_repaint);
static VOID _3D_setting_set_focus(UINT8  ui1_focus_idx, UINT8  ui1_repaint);
static VOID _3D_setting_get_next_focus(UINT8*  pui1_focus_idx);
static VOID _3D_setting_get_pre_focus(UINT8*  pui1_focus_idx);
static INT32 _3D_setting_set_config(VOID);
static INT32 _3D_setting_hide_confirm_dialog(BOOL  b_repaint);
static INT32 _3D_setting_show_confirm_dialog(BOOL         b_repaint);
static INT32 _config_3D_setting_title_text(HANDLE_T h_txt, FE_FNT_SIZE e_fnt, UINT16 u2mlm);

static INT32 _3D_setting_nav_back(VOID)
{
    MENU_3D_SETTING_VIEW_T* pt_view = &(t_g_3D_setting_view);

    switch (pt_view->e_current_status)
    {
    case X_2D_TAG:
        menu_nav_back();
        break;
    case X_2D_TAG_2D_PLAY:
        pt_view->e_current_status = X_2D_TAG;
        _3D_setting_show_widgets(0, TRUE);
        break;
    case X_2D_TAG_3D_PLAY:
        pt_view->e_current_status = X_2D_TAG;
        _3D_setting_show_widgets(1, TRUE);
        break;
    case X_3D_TAG_2D_PLAY:
        menu_nav_back();
        break;
    case X_3D_TAG_3D_PLAY:
        menu_nav_back();
        break;
    default:
        break;
    }

    return MENUR_OK;
}
static BOOL _3D_crnt_is_3d_video_playing(VOID)
{
    INT32                           i4_ret = MENUR_OK;
    BOOL                            b_is_3D_content = FALSE;
    INT16                           i2_mode_idx = 0;
    INT16                           i2_3d_to_2d_mode = 0;
    VSH_SRC_RESOLUTION_INFO_T       t_src_res = {0};
    BOOL                            b_is_3d_playing = FALSE;

    i4_ret = c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_src_res);
    MENU_LOG_ON_FAIL(i4_ret);

    switch (t_src_res.e_src_tag3d_type)
    {
        case VSH_SRC_TAG3D_2D:
            b_is_3D_content = FALSE;
            return MENUR_OK;
        case VSH_SRC_TAG3D_MVC:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_FS:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_FP:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_REALD:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_TB:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_SBS:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_SENSIO:
            b_is_3D_content = TRUE;
            break;
        case VSH_SRC_TAG3D_TTDO:
        case VSH_SRC_TAG3D_NOT_SUPPORT:
        default:
            b_is_3D_content = FALSE;
            break;
    }


    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     &i2_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                 &i2_3d_to_2d_mode);
    MENU_CHK_FAIL(i4_ret);



    if (!b_is_3D_content)
    {

        switch ((UINT16)i2_3d_to_2d_mode)
        {
            case APP_CFG_3D_TO_2D_OFF:
                {
                    switch ((UINT16)i2_mode_idx)
                    {
                        case APP_CFG_3D_MODE_SBS:
                        case APP_CFG_3D_MODE_TAB:
                        case APP_CFG_3D_MODE_SENSIO:
                            b_is_3d_playing = TRUE;
                            break;
                        default:
                            b_is_3d_playing = FALSE;
                            break;
                    }
                }
                break;
            default:
                b_is_3d_playing = FALSE;
                break;
        }

    }
    else
    {
        switch ((UINT16)i2_3d_to_2d_mode)
        {
            case APP_CFG_3D_TO_2D_OFF:
                b_is_3d_playing = TRUE;
                break;
            default:
                b_is_3d_playing = FALSE;
                break;
        }
    }
    return b_is_3d_playing;
}

static INT32 _3D_get_crnt_3d_mode_index(UINT8*  pui1_index)
{
    INT32                           i4_ret = MENUR_OK;
    INT16                           i2_mode_idx = 0;
    UINT8                           ui1_tmp_index = 0;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     &i2_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    switch ((UINT16)i2_mode_idx)
    {
        case APP_CFG_3D_MODE_SBS:
            ui1_tmp_index = 1;
            break;
        case APP_CFG_3D_MODE_TAB:
            ui1_tmp_index = 2;
            break;
        case APP_CFG_3D_MODE_SENSIO:
            ui1_tmp_index = 3;
            break;
        default:
            ui1_tmp_index = 0;
            break;
    }

    *pui1_index = ui1_tmp_index;

    return MENUR_OK;
}


static INT32 _3D_setting_widgets_proc_fct(HANDLE_T    h_widget,
                               UINT32      ui4_msg,
                               VOID*       param1,
                               VOID*       param2)
{
    UINT8       ui1_focus_idx = 0;

    switch (ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
    {
        UINT32 ui4_keycode = (UINT32)param1;
        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
            _3D_setting_get_pre_focus(&ui1_focus_idx);
            _3D_setting_set_focus(ui1_focus_idx, WGL_SYNC_AUTO_REPAINT);
            return MENUR_OK;

        case BTN_CURSOR_UP:
            if (t_g_3D_setting_view.ui1_focus_idx > 0)
            {
                _3D_setting_get_pre_focus(&ui1_focus_idx);
                _3D_setting_set_focus(ui1_focus_idx, WGL_SYNC_AUTO_REPAINT);
            }
            return MENUR_OK;

        case BTN_3D:
        case BTN_CURSOR_RIGHT:
            _3D_setting_get_next_focus(&ui1_focus_idx);
            _3D_setting_set_focus(ui1_focus_idx, WGL_SYNC_AUTO_REPAINT);
            return MENUR_OK;

        case BTN_CURSOR_DOWN:
            if (t_g_3D_setting_view.e_current_status < X_3D_MAX_NUM)
            {
                if (t_g_3D_setting_view.ui1_focus_idx < (aui_elem_num[t_g_3D_setting_view.e_current_status] - 1))
                {
                    _3D_setting_get_next_focus(&ui1_focus_idx);
                    _3D_setting_set_focus(ui1_focus_idx, WGL_SYNC_AUTO_REPAINT);
                }
            }
            return MENUR_OK;

        case BTN_SELECT:
            {
                CHAR        s_curr_disp_name[ACFG_MAX_DISP_NAME+1];

                _3D_setting_set_config();

                a_cfg_av_get_disp_name(s_curr_disp_name, sizeof(s_curr_disp_name));
                acfg_custom_update_all(ACFG_UPDATE_REASON_CHG_TIMING, (VOID*)s_curr_disp_name);
            }
            return MENUR_OK;

        case BTN_RETURN:
            _3D_setting_nav_back();
            return MENUR_OK;
        default:
            break;
        }
    }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

static VOID _3D_setting_dlg_ok_proc_fct(VOID)
{
    _3D_setting_hide_confirm_dialog(FALSE);
    menu_nav_back();
}

static VOID _3D_setting_dlg_timer_handler_fct(VOID* pv_data,
                                            SIZE_T  z_data_size)
{
    _3D_setting_hide_confirm_dialog(FALSE);
    menu_nav_back();
}

static VOID _3D_setting_timer_cb_fct(HANDLE_T  pt_tm_handle,
                                   VOID*     pv_tag)
{
    menu_async_invoke(_3D_setting_dlg_timer_handler_fct, NULL, 0, TRUE);
}


/*----------------------------------------------------------------------------
 * Name: _3D_setting_hide_confirm_dialog
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
static INT32 _3D_setting_hide_confirm_dialog(BOOL  b_repaint)
{
    MENU_3D_SETTING_VIEW_T* pt_this = &t_g_3D_setting_view;

    c_timer_stop(pt_this->h_timer);

    a_ui_simple_dialog_hide(pt_this->h_dialog_ok);
    if(b_repaint)
    {
        menu_pm_repaint();
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _3D_setting_show_confirm_dialog
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
static INT32 _3D_setting_show_confirm_dialog(BOOL         b_repaint)
{
    MENU_3D_SETTING_VIEW_T* pt_this = &t_g_3D_setting_view;
    INT32 i4_ret = MENUR_OK;

	/* Update the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dialog_ok, MENU_TEXT(MLM_MENU_KEY_X_3D_SETTING_VIEW_WARNING));
    if(i4_ret != MENUR_OK){
        return MENUR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_dialog_ok, MENU_TEXT( MLM_MENU_KEY_OK));
    if(i4_ret != MENUR_OK){
        return MENUR_FAIL;
    }

    a_ui_simple_dialog_show(pt_this->h_dialog_ok);
    a_ui_simple_dialog_set_focus(pt_this->h_dialog_ok, FALSE);

    i4_ret = c_timer_start(pt_this->h_timer,
                        3000,
                        X_TIMER_FLAG_ONCE,
                        _3D_setting_timer_cb_fct,
                        NULL);
    MENU_CHK_FAIL(i4_ret);

    if(b_repaint)
    {
        menu_pm_repaint();
    }

    return MENUR_OK;
}


static INT32 _3D_setting_frame_reset(GL_RECT_T* pt_rect)
{
    INT32   i4_ret = MENUR_OK;

    i4_ret = c_wgl_move(t_g_3D_setting_view.h_frame, pt_rect, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _3D_setting_title_reset(GL_RECT_T* pt_rect)
{
    INT32   i4_ret = MENUR_OK;

    i4_ret = c_wgl_move(t_g_3D_setting_view.h_title_txt, pt_rect, WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _3D_setting_set_elem_num(UINT8 ui1_num)
{
    INT32           i4_ret = MENUR_OK;
    GL_RECT_T       t_rect = {0};
    INT32           i4_width = 0;
    INT8           i1_idx = 0;

    if (ui1_num > MENU_3D_PAGE_ICON_MAX_NUM)    /* Avoid buffer overflow*/
    {
        return MENUR_FAIL;
    }

    i4_width = (X_3D_SETTING_ICON_GAP+X_3D_SETTING_BTN_W)*ui1_num + X_3D_SETTING_BTN_X;

    SET_RECT_BY_SIZE (&t_rect,
                      ((SCREEN_W - i4_width)/2),
                      X_3D_SETTING_FRAME_Y,
                      i4_width,
                      X_3D_SETTING_FRAME_H);
    i4_ret = _3D_setting_frame_reset(&t_rect);
    MENU_CHK_FAIL(i4_ret);

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      X_3D_SETTING_TITLE_TXT_Y,
                      i4_width,
                      X_3D_SETTING_TITLE_TXT_H);
    i4_ret = _3D_setting_title_reset(&t_rect);
    MENU_CHK_FAIL(i4_ret);

    for (i1_idx = 0; i1_idx < ui1_num; i1_idx ++)
    {
        i4_ret = c_wgl_set_visibility(t_g_3D_setting_view.h_txt[i1_idx], WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);
        i4_ret = c_wgl_set_visibility(t_g_3D_setting_view.h_btn[i1_idx], WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);
    }

    for (i1_idx = ui1_num; i1_idx < MENU_3D_PAGE_ICON_MAX_NUM; i1_idx ++)
    {
        i4_ret = c_wgl_set_visibility(t_g_3D_setting_view.h_txt[i1_idx], WGL_SW_HIDE);
        MENU_CHK_FAIL(i4_ret);
        i4_ret = c_wgl_set_visibility(t_g_3D_setting_view.h_btn[i1_idx], WGL_SW_HIDE);
        MENU_CHK_FAIL(i4_ret);
    }

    return MENUR_OK;
}

static INT32 _config_3D_setting_title_text(HANDLE_T h_txt, FE_FNT_SIZE e_fnt, UINT16 u2mlm)
{
    INT32               i4_ret;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_INSET_T         t_inset;
    WGL_FONT_INFO_T     t_fnt_info;

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = e_fnt;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd ( h_txt,
                            WGL_CMD_GL_SET_FONT,
                            WGL_PACK(&t_fnt_info),
                            NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Text Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if (i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_LEFT_CENTER),
                          NULL);
    if (i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }
    /*set text*/
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(u2mlm)),
                          (VOID *)512);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }
    /* Set Insets */
    t_inset.i4_left     = 20;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_txt,
                            WGL_CMD_TEXT_SET_CNT_INSET,
                            &t_inset,
                            NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_insert(h_txt,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }
    return MENUR_OK;
}
static INT32 _config_3D_setting_text(HANDLE_T h_txt, FE_FNT_SIZE e_fnt, UINT16 u2mlm)
{
    INT32               i4_ret;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_INSET_T         t_inset;
    WGL_FONT_INFO_T     t_fnt_info;

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = e_fnt;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd ( h_txt,
                            WGL_CMD_GL_SET_FONT,
                            WGL_PACK(&t_fnt_info),
                            NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Text Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable    = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight = t_g_menu_color_bk1_txt;
    t_clr_info.u_color_data.t_standard.t_disable   = t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    if (i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    if (i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }
    /*set text*/
    i4_ret = c_wgl_do_cmd(h_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(MENU_TEXT(u2mlm)),
                          (VOID *)512);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }
    /* Set Insets */
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd(h_txt,
                            WGL_CMD_TEXT_SET_CNT_INSET,
                            &t_inset,
                            NULL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_insert(h_txt,
                          NULL_HANDLE,
                          WGL_INSERT_TOPMOST,
                          WGL_NO_AUTO_REPAINT);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }
    return MENUR_OK;
}

static INT32 _config_3D_setting_button(HANDLE_T h_btn, WGL_HIMG_TPL_T h_img, WGL_HIMG_TPL_T h_img_hlt)
{
    INT32  i4_ret;
    WGL_IMG_INFO_T   t_img_info;

    /* set the backgroung of buttom_ok*/
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_img;
    t_img_info.u_img_data.t_extend.t_disable            = h_img;
    t_img_info.u_img_data.t_extend.t_highlight          = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_push               = h_img_hlt;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_img;

    i4_ret = c_wgl_do_cmd(h_btn,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_FG),
                 WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);
    /* set the alignment */
    i4_ret = c_wgl_do_cmd(h_btn,
                 WGL_CMD_BTN_SET_ALIGN,
                 WGL_PACK(WGL_AS_CENTER_CENTER),
                 NULL);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _config_3D_setting_frame(HANDLE_T h_frame)
{
    INT32  i4_ret;
    WGL_IMG_INFO_T   t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_img_3D_content_mode_bkg;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_img_3D_content_mode_bkg;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_menu_img_3D_content_mode_bkg;

    i4_ret = c_wgl_do_cmd(h_frame,
                 WGL_CMD_GL_SET_IMAGE,
                 WGL_PACK(WGL_IMG_BK),
                 WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}
static INT32 _create_3D_setting_text(HANDLE_T h_parent, HANDLE_T * ph_handle,GL_RECT_T* pt_rect)
{
    INT32               i4_ret;

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_TEXT_MAX_32
                                  | WGL_STL_TEXT_SMART_CUT
                                  | WGL_STL_GL_NO_IMG_UI
                                  | WGL_STL_GL_NO_BK),
                                 0,
                                 ph_handle);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }

    return MENUR_OK;
}

static INT32 _create_3D_setting_button(HANDLE_T h_parent, HANDLE_T * ph_handle,GL_RECT_T* pt_rect)
{
    INT32               i4_ret;
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 _3D_setting_widgets_proc_fct,
                                 255,
                                 (VOID*)0,
                                 0,
                                 ph_handle);
    if(i4_ret != WGLR_OK)
    {
        return MENUR_FAIL;
    }
    return MENUR_OK;


}

static INT32 _create_3D_setting_widgets(VOID)
{
    INT32           i4_ret;
    HANDLE_T        h_canvas;
    GL_RECT_T       t_rect;
    INT8            i1_idx = 0;
    MENU_3D_SETTING_VIEW_T*  pt_view = &t_g_3D_setting_view;

    i4_ret = menu_pm_get_canvas(&h_canvas);
    if(i4_ret != MENUR_OK)
    {
        return MENUR_FAIL;
    }

    c_memset (pt_view, 0, sizeof (MENU_3D_SETTING_VIEW_T));

    SET_RECT_BY_SIZE (&t_rect,
                      X_3D_SETTING_FRAME_X,
                      X_3D_SETTING_FRAME_Y,
                      X_3D_SETTING_FRAME_W,
                      X_3D_SETTING_FRAME_H);

    i4_ret = c_wgl_create_widget(h_canvas,
                        HT_WGL_WIDGET_FRAME,
                        WGL_CONTENT_FRAME_DEF,
                        WGL_BORDER_NULL,
                        &t_rect,
                        _3D_setting_widgets_proc_fct,
                        255,
                        (VOID*)0,
                        NULL,
                        &pt_view->h_frame);
    if(i4_ret != MENUR_OK)
    {
        return MENUR_FAIL;
    }

    i4_ret = _config_3D_setting_frame(pt_view->h_frame);
    MENU_CHK_FAIL(i4_ret);

    SET_RECT_BY_SIZE (&t_rect,
                      X_3D_SETTING_TITLE_TXT_X,
                      X_3D_SETTING_TITLE_TXT_Y,
                      X_3D_SETTING_TITLE_TXT_W ,
                      X_3D_SETTING_TITLE_TXT_H);

    i4_ret = _create_3D_setting_text(pt_view->h_frame,
                          &pt_view->h_title_txt,
                          &t_rect);

    if(i4_ret != MENUR_OK)
    {
        return MENUR_FAIL;
    }

    for (i1_idx = 0; i1_idx < MENU_3D_PAGE_ICON_MAX_NUM; i1_idx ++)
    {
        SET_RECT_BY_SIZE (&t_rect,
                          X_3D_SETTING_TXT_X + (X_3D_SETTING_TXT_W+X_3D_SETTING_ICON_GAP) * i1_idx,
                          X_3D_SETTING_TXT_Y,
                          X_3D_SETTING_TXT_W,
                          X_3D_SETTING_TXT_H);

        i4_ret = _create_3D_setting_text(pt_view->h_frame,
                              &pt_view->h_txt[i1_idx],
                              &t_rect);
        if(i4_ret != MENUR_OK)
        {
            return MENUR_FAIL;
        }
    }

    for (i1_idx = 0; i1_idx < MENU_3D_PAGE_ICON_MAX_NUM; i1_idx ++)
    {
        SET_RECT_BY_SIZE (&t_rect,
                          X_3D_SETTING_BTN_X + (X_3D_SETTING_BTN_W+X_3D_SETTING_ICON_GAP) * i1_idx,
                          X_3D_SETTING_BTN_Y,
                          X_3D_SETTING_BTN_W,
                          X_3D_SETTING_BTN_H);

        i4_ret = _create_3D_setting_button(pt_view->h_frame,
                                        &pt_view->h_btn[i1_idx],
                                        &t_rect);
        if(i4_ret != MENUR_OK)
        {
            return MENUR_FAIL;
        }
    }

    return MENUR_OK;
}

static INT32 _3D_setting_dialog_create( VOID )
{
    MENU_3D_SETTING_VIEW_T* pt_this = &t_g_3D_setting_view;
    UI_SIMPLE_DIALOG_INIT_T         t_simple_dialog_init;
    INT32                           i4_ret;
    HANDLE_T                        h_root_frm;
    GL_POINT_T                      t_offset = {-55, 0};

    i4_ret = menu_pm_get_root_frm(&h_root_frm);
    MENU_CHK_FAIL(i4_ret);

    c_memset(&t_simple_dialog_init, 0, sizeof(UI_SIMPLE_DIALOG_INIT_T));

    t_simple_dialog_init.e_style                        = UI_SIMPLE_DIALOG_STYLE_SMALL;
    t_simple_dialog_init.h_parent                       = h_root_frm;
    t_simple_dialog_init.pf_ui_simple_dialog_no_cb_fct  = NULL;
    t_simple_dialog_init.pf_ui_simple_dialog_yes_cb_fct = _3D_setting_dlg_ok_proc_fct;
    t_simple_dialog_init.pf_wdgt_proc                   = a_ui_simple_dialog_default_msg_proc;
    t_simple_dialog_init.pt_begin_offset                = &t_offset;
    t_simple_dialog_init.ui2_txt_align_type             = WGL_AS_CENTER_CENTER;
    t_simple_dialog_init.b_default_answer               = TRUE;
    t_simple_dialog_init.b_one_btn_mode                 = TRUE;

#if 0
    a_ui_simple_dialog_create_custom(&t_simple_dialog_init,
                                  &pt_this->h_dialog_ok);
#endif
    //Fix Coverity ID :4491838 Unchecked return value
    i4_ret = a_ui_simple_dialog_create(&t_simple_dialog_init,
                                  &pt_this->h_dialog_ok);
    MENU_CHK_FAIL(i4_ret);

    /* Modify the attribute */
    i4_ret = a_ui_simple_dialog_set_text(pt_this->h_dialog_ok, MENU_TEXT(MLM_MENU_KEY_X_3D_SETTING_VIEW_WARNING));
    if(i4_ret != MENUR_OK){
        return MENUR_FAIL;
    }

    i4_ret = a_ui_simple_dialog_set_yes_text(pt_this->h_dialog_ok, MENU_TEXT( MLM_MENU_KEY_OK));
    if(i4_ret != MENUR_OK){
        return MENUR_FAIL;
    }

    return MENUR_OK;
}


static INT32 _3D_setting_set_config(VOID)
{
    MENU_3D_SETTING_VIEW_T*  pt_view = &t_g_3D_setting_view;
    INT16          ui2_mode_idx = 0;
    INT16          ui2_3d_to_2d_mode = 0;
    INT32          i4_ret = MENUR_OK;
    UINT8                    ui1_index = 0;

    _3D_get_crnt_3d_mode_index(&ui1_index);
    switch (pt_view->e_current_status)
    {
    case X_2D_TAG:
            if (0 == pt_view->ui1_focus_idx)
        {
            pt_view->e_current_status = X_2D_TAG_2D_PLAY;
                _3D_setting_show_widgets(ui1_index, TRUE);
        }
        else
        {
            pt_view->e_current_status = X_2D_TAG_3D_PLAY;
                _3D_setting_show_widgets(ui1_index, TRUE);
        }
        return MENUR_OK;
    case X_2D_TAG_2D_PLAY:
        DBG_INFO(("[3D setting]-------------X_2D_TAG_2D_PLAY-------------"));

            if (0 == pt_view->ui1_focus_idx) /*select 2D content format*/
        {
            ui2_mode_idx = APP_CFG_3D_MODE_OFF;
            ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_OFF;
        }
            else if (1 == pt_view->ui1_focus_idx) /*select SBS/TB/Sensio content format*/
        {
            ui2_mode_idx = APP_CFG_3D_MODE_SBS;
            ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_LEFT;
        }
            else if (2 == pt_view->ui1_focus_idx)
        {
            ui2_mode_idx = APP_CFG_3D_MODE_TAB;
            ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_LEFT;
        }
            else if (3 == pt_view->ui1_focus_idx)
        {
            ui2_mode_idx = APP_CFG_3D_MODE_SENSIO;
            ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_LEFT;
        }
        else
        {
            break;
        }

        b_3d_mode_playing = FALSE;

        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     (INT16)ui2_mode_idx);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

        /* 3D to 2D*/
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                 (INT16 )ui2_3d_to_2d_mode);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

        break;
    case X_2D_TAG_3D_PLAY:
        DBG_INFO(("[3D setting]-------------X_2D_TAG_3D_PLAY-------------"));

            if (0 == pt_view->ui1_focus_idx)
            {
                /* do nothing*/
            }
            else
            {
		        c_wgl_set_visibility(pt_view->h_frame,WGL_SW_HIDE);

		        _3D_setting_show_confirm_dialog(TRUE);

		        i4_ret = c_timer_start(pt_view->h_timer,
		                            3000,
		                            X_TIMER_FLAG_ONCE,
		                            _3D_setting_timer_cb_fct,
		                            NULL);
                MENU_CHK_FAIL(i4_ret);
            }

            ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_OFF;

            if (0 == pt_view->ui1_focus_idx)
            {
                ui2_mode_idx = APP_CFG_3D_MODE_OFF;
            }
            else if (1 == pt_view->ui1_focus_idx)
            {
                ui2_mode_idx = APP_CFG_3D_MODE_SBS;
            }
            else if (2 == pt_view->ui1_focus_idx)
            {
                ui2_mode_idx = APP_CFG_3D_MODE_TAB;
            }
            else if (3 == pt_view->ui1_focus_idx)
            {
                ui2_mode_idx = APP_CFG_3D_MODE_SENSIO;
            }
            else
            {
                break;
            }

            b_3d_mode_playing = TRUE;

        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     (INT16)ui2_mode_idx);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

            /* 3D to 2D*/
            a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                     (INT16 )ui2_3d_to_2d_mode);
            a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

            if (0 == pt_view->ui1_focus_idx)
            {
                break;
            }
            else
            {
                return MENUR_OK;
            }
    case X_3D_TAG_2D_PLAY:
        DBG_INFO(("[3D setting]-------------current is 2D mode, set 3D mode-------------"));
        if (1 == pt_view->ui1_focus_idx)
        {
            ui2_mode_idx = APP_CFG_3D_MODE_AUTO;
            ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_OFF;
        }
        else
        {
            break;
        }

        b_3d_mode_playing = TRUE;

        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     (INT16)ui2_mode_idx);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

        /* 3D to 2D*/
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                 (INT16 )ui2_3d_to_2d_mode);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));

        break;
    case X_3D_TAG_3D_PLAY:
        DBG_INFO(("[3D setting]-------------current is 3D mode, set 2D mode-------------"));
            if (0 == pt_view->ui1_focus_idx)
        {
            ui2_mode_idx = APP_CFG_3D_MODE_AUTO;
            ui2_3d_to_2d_mode = APP_CFG_3D_TO_2D_LEFT;
        }
        else
        {
            break;
        }

        b_3d_mode_playing = FALSE;
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     (INT16)ui2_mode_idx);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE));

        /* 3D to 2D*/
        a_cfg_av_set(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                 (INT16 )ui2_3d_to_2d_mode);
        a_cfg_av_update(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D));
        break;
    default:
        break;
    }

    menu_nav_back();

    return MENUR_OK;
}

static VOID _3D_setting_get_pre_focus(UINT8*  pui1_focus_idx)
{
    MENU_3D_SETTING_VIEW_T*  pt_view = &t_g_3D_setting_view;

    if (pt_view->e_current_status < X_3D_MAX_NUM)   /* avoid buffer overflow*/
    {
        if (pt_view->ui1_focus_idx > 0)
        {
            *pui1_focus_idx = pt_view->ui1_focus_idx - 1;
        }
        else
        {
            *pui1_focus_idx = (aui_elem_num[pt_view->e_current_status] - 1);
        }
    }
    else
    {
        *pui1_focus_idx = 0;
    }
}

static VOID _3D_setting_get_next_focus(UINT8*  pui1_focus_idx)
{
    MENU_3D_SETTING_VIEW_T*  pt_view = &t_g_3D_setting_view;

    *pui1_focus_idx = pt_view->ui1_focus_idx + 1;

    if (pt_view->e_current_status < X_3D_MAX_NUM)   /* avoid buffer overflow*/
    {
        if (*pui1_focus_idx >= aui_elem_num[pt_view->e_current_status])
        {
            *pui1_focus_idx = 0;
        }
    }
    else
    {
        *pui1_focus_idx = 0;
    }
}

static VOID _3D_setting_set_focus(UINT8  ui1_focus_idx, UINT8  ui1_repaint)
{
    if (ui1_focus_idx < MENU_3D_PAGE_ICON_MAX_NUM)  /* avoid buffer overflow*/
    {
        t_g_3D_setting_view.ui1_focus_idx = ui1_focus_idx;
        c_wgl_set_focus(t_g_3D_setting_view.h_btn[ui1_focus_idx], ui1_repaint);
    }
}

static INT32  _3D_setting_config_elem(UINT8 ui1_elem_idx, UINT16 ui2_text_id, WGL_HIMG_TPL_T h_img, WGL_HIMG_TPL_T h_img_hlt)
{
    INT32   i4_ret = MENUR_OK;

    if (ui1_elem_idx < MENU_3D_PAGE_ICON_MAX_NUM)       /*avoid buffer overflow */
    {
        i4_ret = _config_3D_setting_text(t_g_3D_setting_view.h_txt[ui1_elem_idx], FE_FNT_SIZE_SMALL, ui2_text_id);
        MENU_CHK_FAIL(i4_ret);

        i4_ret = _config_3D_setting_button(t_g_3D_setting_view.h_btn[ui1_elem_idx], h_img, h_img_hlt);
        MENU_CHK_FAIL(i4_ret);
    }
    return MENUR_OK;
}

static INT32 _3D_setting_set_title_text(UINT16 ui2_title_id)
{
    INT32   i4_ret = MENUR_OK;

    i4_ret = _config_3D_setting_title_text(t_g_3D_setting_view.h_title_txt, FE_FNT_SIZE_MEDIUM, ui2_title_id);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32  _3D_setting_set_status(VOID)
{
    INT32       i4_ret = MENUR_OK;
    INT16       i2_mode_idx = 0;
    INT16       i2_3d_to_2d_mode = 0;
    MENU_3D_SETTING_VIEW_T*         pt_view = &t_g_3D_setting_view;

    i4_ret = a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_MODE),
                     &i2_mode_idx);
    MENU_CHK_FAIL(i4_ret);

    a_cfg_av_get(CFG_MAKE_ID(APP_CFG_GRPID_VIDEO, APP_CFG_RECID_VID_3D_TO_2D),
                 &i2_3d_to_2d_mode);
    MENU_CHK_FAIL(i4_ret);

    DBG_INFO(("[3D setting]------APP_CFG_RECID_VID_3D_MODE:%d\n", i2_mode_idx));

    if (!pt_view->b_is_3D_content)
    {
        pt_view->e_current_status = X_2D_TAG;
    }
    else
    {
        switch ((UINT16)i2_3d_to_2d_mode)
        {
        case APP_CFG_3D_TO_2D_OFF:
            pt_view->e_current_status = X_3D_TAG_3D_PLAY;
            break;
        default:
            pt_view->e_current_status = X_3D_TAG_2D_PLAY;
            break;
        }
    }

    return MENUR_OK;
}

static INT32 _3D_setting_get_3D_tag_type(VOID)
{
    INT32   i4_ret = MENUR_OK;
    MENU_3D_SETTING_VIEW_T*         pt_view = &t_g_3D_setting_view;
    VSH_SRC_RESOLUTION_INFO_T       t_src_res = {0};

    i4_ret = c_svctx_get_video_src_resolution(menu_get_crnt_svctx(), &t_src_res);
    MENU_LOG_ON_FAIL(i4_ret);

    DBG_INFO(("[3D setting]------3D type:%d\n", t_src_res.e_src_tag3d_type));

    switch (t_src_res.e_src_tag3d_type)
    {
        case VSH_SRC_TAG3D_2D:
            pt_view->b_is_3D_content = FALSE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_2D;
            return MENUR_OK;
        case VSH_SRC_TAG3D_MVC:
            pt_view->b_is_3D_content = TRUE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_MVC;
            break;
        case VSH_SRC_TAG3D_FS:
            pt_view->b_is_3D_content = TRUE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_FS;
            break;
        case VSH_SRC_TAG3D_FP:
            pt_view->b_is_3D_content = TRUE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_FP;
            break;
        case VSH_SRC_TAG3D_REALD:
            pt_view->b_is_3D_content = TRUE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_REALD;
            break;
#if 0
        case VSH_SRC_TAG3D_TTDO:
            pt_view->b_is_3D_content = TRUE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_TTDO;
            break;
#endif
        case VSH_SRC_TAG3D_TB:
            pt_view->b_is_3D_content = TRUE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_TB;
            break;
        case VSH_SRC_TAG3D_SBS:
            pt_view->b_is_3D_content = TRUE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_SBS;
            break;
        case VSH_SRC_TAG3D_SENSIO:
            pt_view->b_is_3D_content = TRUE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_SENSIO;
            break;
        case VSH_SRC_TAG3D_TTDO:
        case VSH_SRC_TAG3D_NOT_SUPPORT:
        default:
            pt_view->b_is_3D_content = FALSE;
            pt_view->e_3D_type = VSH_SRC_TAG3D_NOT_SUPPORT;
            break;
    }

    return MENUR_OK;
}

static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32 i4_ret = MENUR_OK;

    i4_ret = _create_3D_setting_widgets();
    MENU_CHK_FAIL(i4_ret);

    t_g_3D_setting_view.e_3D_type = VSH_SRC_TAG3D_2D;

    i4_ret = _3D_setting_dialog_create();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_timer_create(&t_g_3D_setting_view.h_timer);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    if (NULL_HANDLE != t_g_3D_setting_view.h_timer)
    {
        c_timer_delete(t_g_3D_setting_view.h_timer);
    }
    return MENUR_OK;
}

static INT32 _3D_setting_show_widgets(UINT8  ui1_focus_idx, BOOL  b_repaint)
{
    INT32             i4_ret = MENUR_OK;
    MENU_3D_SETTING_VIEW_T*  pt_view = &t_g_3D_setting_view;

    DBG_INFO(("[3D setting]------play status:%d, 3D type:%d\n", pt_view->e_current_status, pt_view->e_3D_type));

    switch (pt_view->e_current_status)
    {
        case X_2D_TAG:
            _3D_setting_set_elem_num(aui_elem_num[pt_view->e_current_status]);

            i4_ret = _3D_setting_config_elem( 0,
                                    MLM_MENU_KEY_X_3D_SETTING_2D,
                                    h_g_menu_img_3d_setting_2d,
                                    h_g_menu_img_3d_setting_2d_hlt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _3D_setting_config_elem( 1,
                                    MLM_MENU_KEY_X_3D_SETTING_3D,
                                    h_g_menu_img_3d_setting_3d,
                                    h_g_menu_img_3d_setting_3d_hlt);
            MENU_CHK_FAIL(i4_ret);

            /*set Title*/
            _3D_setting_set_title_text(MLM_MENU_KEY_X_3D_SETTING_OUTPUT_MODE);
            break;
        case X_2D_TAG_2D_PLAY:
            _3D_setting_set_elem_num(aui_elem_num[pt_view->e_current_status]);

            i4_ret = _3D_setting_config_elem( 0,
                                    MLM_MENU_KEY_X_3D_SETTING_2D,
                                    h_g_menu_img_3d_setting_2d,
                                    h_g_menu_img_3d_setting_2d_hlt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _3D_setting_config_elem( 1,
                                    MLM_MENU_KEY_X_3D_SETTING_SBS,
                                    h_g_menu_img_3d_setting_sbs,
                                    h_g_menu_img_3d_setting_sbs_hlt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _3D_setting_config_elem( 2,
                                    MLM_MENU_KEY_X_3D_SETTING_TB,
                                    h_g_menu_img_3d_setting_tb,
                                    h_g_menu_img_3d_setting_tb_hlt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _3D_setting_config_elem( 3,
                                    MLM_MENU_KEY_X_3D_SETTING_SENSIO,
                                    h_g_menu_img_3d_setting_sensio,
                                    h_g_menu_img_3d_setting_sensio_hlt);
            MENU_CHK_FAIL(i4_ret);

            /*set Title*/
            _3D_setting_set_title_text(MLM_MENU_KEY_X_3D_SETTING_CONTENT_FORMAT);
            break;
        case X_2D_TAG_3D_PLAY:
            _3D_setting_set_elem_num(aui_elem_num[pt_view->e_current_status]);

            i4_ret = _3D_setting_config_elem( 0,
                                    MLM_MENU_KEY_X_3D_SETTING_2D,
                                    h_g_menu_img_3d_setting_2d,
                                    h_g_menu_img_3d_setting_2d_hlt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _3D_setting_config_elem( 1,
                                    MLM_MENU_KEY_X_3D_SETTING_SBS,
                                    h_g_menu_img_3d_setting_sbs,
                                    h_g_menu_img_3d_setting_sbs_hlt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _3D_setting_config_elem( 2,
                                    MLM_MENU_KEY_X_3D_SETTING_TB,
                                    h_g_menu_img_3d_setting_tb,
                                    h_g_menu_img_3d_setting_tb_hlt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _3D_setting_config_elem( 3,
                                    MLM_MENU_KEY_X_3D_SETTING_SENSIO,
                                    h_g_menu_img_3d_setting_sensio,
                                    h_g_menu_img_3d_setting_sensio_hlt);
            MENU_CHK_FAIL(i4_ret);

            /*set Title*/
            _3D_setting_set_title_text(MLM_MENU_KEY_X_3D_SETTING_CONTENT_FORMAT);
            break;
        case X_3D_TAG_2D_PLAY:
            _3D_setting_set_elem_num(aui_elem_num[pt_view->e_current_status]);


            i4_ret = _3D_setting_config_elem( 0,
                                    MLM_MENU_KEY_X_3D_SETTING_2D,
                                    h_g_menu_img_3d_setting_2d,
                                    h_g_menu_img_3d_setting_2d_hlt);
            MENU_CHK_FAIL(i4_ret);

            i4_ret = _3D_setting_config_elem( 1,
                                    MLM_MENU_KEY_X_3D_SETTING_3D,
                                    h_g_menu_img_3d_setting_3d,
                                    h_g_menu_img_3d_setting_3d_hlt);
            MENU_CHK_FAIL(i4_ret);

            /*set Title*/
            _3D_setting_set_title_text(MLM_MENU_KEY_X_3D_SETTING_OUTPUT_MODE);
            break;
        case X_3D_TAG_3D_PLAY:
            _3D_setting_set_elem_num(aui_elem_num[pt_view->e_current_status]);

            i4_ret = _3D_setting_config_elem( 0,
                                    MLM_MENU_KEY_X_3D_SETTING_2D,
                                    h_g_menu_img_3d_setting_2d,
                                    h_g_menu_img_3d_setting_2d_hlt);
            MENU_CHK_FAIL(i4_ret);


            i4_ret = _3D_setting_config_elem( 1,
                                    MLM_MENU_KEY_X_3D_SETTING_3D,
                                    h_g_menu_img_3d_setting_3d,
                                    h_g_menu_img_3d_setting_3d_hlt);
            MENU_CHK_FAIL(i4_ret);

            /*set Title*/
            _3D_setting_set_title_text(MLM_MENU_KEY_X_3D_SETTING_OUTPUT_MODE);
            break;
        default:
            break;
    }

    _3D_setting_set_focus(ui1_focus_idx, WGL_NO_AUTO_REPAINT);

    if (b_repaint)
    {
        menu_pm_repaint();
    }

    return MENUR_OK;
}

static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32             i4_ret = MENUR_OK;
    MENU_3D_SETTING_VIEW_T*  pt_view = &t_g_3D_setting_view;
    UINT8                    ui1_index = 0;
    BOOL                     b_is_3d_video_playing = FALSE;
    HANDLE_T                 h_menu_main_frm = NULL_HANDLE;

#ifdef VIEWPORT_SUPPORT
    a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_WIDE_MODE);
    a_cfg_update_viewport ();
#endif

    /* Hide the main menu */
    menu_pm_get_main_frm(&h_menu_main_frm);

    if (h_menu_main_frm != NULL_HANDLE)
    {
        c_wgl_get_visibility(h_menu_main_frm, &b_is_menu_showed);
    }

    menu_main_set_visibility(FALSE);
    menu_hide_help_tip();

    i4_ret = _3D_setting_get_3D_tag_type();
    MENU_CHK_FAIL(i4_ret);

    _3D_setting_set_status();

    b_is_3d_video_playing = _3D_crnt_is_3d_video_playing();

    if (!b_is_3d_video_playing)
    {
        ui1_index = 1;    /* if current is not 3d video playing should focus the 3d itemdefaut*/
    }
    else
    {
        ui1_index = 0;
    }

    _3D_setting_show_widgets( (UINT8)ui1_index, FALSE);
    _3D_setting_set_title_text(MLM_MENU_KEY_X_3D_SETTING_OUTPUT_MODE);

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_frame,
                    WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_title_txt,
                    WGL_SW_NORMAL);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_focus(pt_view->h_btn[(UINT8)ui1_index], WGL_NO_AUTO_REPAINT);
    MENU_CHK_FAIL(i4_ret);
    pt_view->ui1_focus_idx = ui1_index;

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32       i4_ret = MENUR_OK;
    UINT8       ui1_status = 0;

    MENU_3D_SETTING_VIEW_T*  pt_view = &t_g_3D_setting_view;

    i4_ret = c_wgl_set_visibility(
                    pt_view->h_frame,
                    WGL_SW_HIDE_RECURSIVE);
    if (i4_ret != WGLR_OK) {
        return MENUR_FAIL;
    }

#ifdef VIEWPORT_SUPPORT
    if (a_cfg_get_app_status () == APP_CFG_APP_STATUS_MENU_WIDE_MODE)
    {
        a_cfg_set_app_status (APP_CFG_APP_STATUS_MENU_NOT_WIDE_MODE);
    }

    if (a_icl_custom_get_nw_widget_status(ICL_CUSTOM_NW_WIDGET_DOCK, &ui1_status) == ICLR_OK)
    {

        if ((YAHOO_STATUS_DOCK_UP & ui1_status) != 0)
        {
            a_cfg_set_app_status (APP_CFG_APP_STATUS_YH_DOCK);
        }
        if ((YAHOO_STATUS_SIDEBAR & ui1_status) != 0)
        {
            a_cfg_set_app_status (APP_CFG_APP_STATUS_YH_SIDEBAR);
        }
    }

    a_cfg_update_viewport ();
#endif

    if (b_is_menu_showed)
    {
        menu_main_set_visibility(TRUE);
    }

    return MENUR_OK;
}

static INT32 _on_page_get_focus(
    UINT32 ui4_page_id,
    MENU_PAGE_HINT_T* pt_hint)
{
    return MENUR_OK;
}

static INT32 _on_page_lose_focus(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_update(
    UINT32 ui4_page_id,
    UINT32 ui4_update_mask)
{
    return MENUR_OK;
}


extern INT32 menu_custom_page_3D_setting_init(VOID)
{
    t_g_menu_custom_page_3D_setting.pf_menu_page_create =    _on_page_create;
    t_g_menu_custom_page_3D_setting.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_custom_page_3D_setting.pf_menu_page_show=       _on_page_show;
    t_g_menu_custom_page_3D_setting.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_custom_page_3D_setting.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_custom_page_3D_setting.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_custom_page_3D_setting.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

