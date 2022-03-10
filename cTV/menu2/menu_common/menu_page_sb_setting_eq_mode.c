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
 * $RCSfile: menu_page_inp_lst.c,v $
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

#include "c_common.h"
#include "c_handle.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"
#include "app_util/a_isl.h"

#include "menu2/menu.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_common/menu_common.h"
#include "res/menu2/menu_custom.h"
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/tts/a_tts_custom.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
typedef enum
{
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT = 0,
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MUSIC = _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT,
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MOVIE,
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_GAME,
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DIRECT,
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DIALOGUE,
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MAX

} _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_T;

typedef INT32 (*ope_lb2_proc_fct)(HANDLE_T            h_widget,
                                     UINT32              ui4_msg,
                                     VOID*               pv_param1,
                                     VOID*               pv_param2);
typedef struct {
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_T    e_eq_mode;
} MENU_PAGE_SB_SETTING_EQ_MODE_T;

MENU_PAGE_FCT_TBL_T     t_g_menu_page_sb_setting_eq_mode;
static HANDLE_T         h_sb_setting_eq_mode;
static MENU_PAGE_SB_SETTING_EQ_MODE_T  arr_sb_setting_eq_mode[_MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MAX];
static BOOL             b_from_backbar = FALSE;
/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32       i4_ret=  MENUR_OK;
    return i4_ret;
}

static INT32 _on_page_destroy(
    UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _sb_setting_eq_mode_lb2_create(HANDLE_T h_parent, HANDLE_T *ph_wgt, VOID * pf_proc_fct)
{
    INT32  i4_ret;
    WGL_LB_INIT_T       t_lb_init;
    WGL_LB_COL_INIT_T   at_cols[1];
    GL_RECT_T           t_rect = {0};
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;
    WGL_LB_COLOR_ELEM_SET_T     t_lb_color;
    ope_lb2_proc_fct pf_lb2_proc_fct = NULL;

    pf_lb2_proc_fct = (ope_lb2_proc_fct)pf_proc_fct;
    /* Listbox */
    at_cols[0].e_col_type       = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align        = WGL_AS_CENTER_CENTER;
    at_cols[0].ui2_max_text_len = 64;
    at_cols[0].ui2_width        = CONTENT_W - MENU_ITEM_BAR_CNT_INSET_L - MENU_ITEM_BAR_CNT_INSET_R;

    t_lb_init.ui4_style         = WGL_STL_LB_ELEM_NO_PUSH |
                                  WGL_STL_LB_NO_SCROLL;

    t_lb_init.ui2_max_elem_num  = 32;
    t_lb_init.ui2_elem_size     = MENU_ITEM_V_HEIGHT;
    t_lb_init.ui2_elem_distance = 0;
    t_lb_init.ui1_col_num       = 1;
    t_lb_init.at_cols           = at_cols;

    SET_RECT_BY_SIZE (&t_rect,
                      0,
                      0,
                      CONTENT_W,
                      CONTENT_H);

    i4_ret = menu_list2_create(h_parent,
                               &t_rect,
                               pf_lb2_proc_fct,
                               &t_lb_init,
                               NULL,
                               ph_wgt);
    MENU_CHK_FAIL(i4_ret);

    t_img_elem.h_normal             = h_g_menu_img_item_bk;
    t_img_elem.h_disable            = h_g_menu_img_item_bk;
    t_img_elem.h_highlight          = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_highlight_unfocus  = h_g_menu_img_item_hlt_bk;
    t_img_elem.h_pushed             = h_g_menu_img_item_bk;
    t_img_elem.h_selected           = h_g_menu_img_item_bk;
    t_img_elem.h_selected_disable   = h_g_menu_img_item_bk;
    i4_ret = c_wgl_do_cmd (*ph_wgt,
                           WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE,
                           WGL_PACK(& t_img_elem),
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set LB colors */
    t_lb_color.t_normal = t_g_menu_color_white;
    t_lb_color.t_disable = t_g_menu_color_bk2_txt_disable;
    t_lb_color.t_highlight = t_g_menu_color_white;
    t_lb_color.t_highlight_unfocus = t_g_menu_color_white;
    t_lb_color.t_pushed = t_g_menu_color_white;
    t_lb_color.t_selected = t_g_menu_color_white;
    t_lb_color.t_selected_disable = t_g_menu_color_bk2_txt_disable;

    i4_ret = c_wgl_do_cmd(*ph_wgt,
                          WGL_CMD_LB_SET_COL_COLOR,
                          WGL_PACK_2(0, WGL_CLR_TEXT),
                          WGL_PACK(&t_lb_color) );
    MENU_LOG_ON_FAIL(i4_ret);

    return MENUR_OK;
}

static UINT16 _get_sb_setting_eq_mode_mlm_idx(_MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_T e_sb_setting_eq_mode)
{
    UINT16 ui2_idx = MLM_MENU_KEY_EMPTY;

    switch(e_sb_setting_eq_mode)
    {
        case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MUSIC:
        ui2_idx = MLM_MENU_KEY_EQ_MODE_MUSIC ;
        break;

        case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MOVIE:
        ui2_idx = MLM_MENU_KEY_EQ_MODE_MOVIE;
        break;

        case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_GAME:
        ui2_idx = MLM_MENU_KEY_EQ_MODE_GAME;
        break;

        case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DIRECT:
        ui2_idx = MLM_MENU_KEY_EQ_MODE_DIRECT;
        break;

        case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DIALOGUE:
        ui2_idx = MLM_MENU_KEY_EQ_MODE_DIALOGUE;
        break;
        default:/* unknown sb setting eq mode? */
        break;
    }
    return ui2_idx;
}

static INT32 _backbar_proc_fct (
    HANDLE_T                    h_widget,
    UINT32                      ui4_msg,
    VOID*                       param1,
    VOID*                       param2
    )
{
    INT32 i4_ret;

    if (WGL_MSG_GET_FOCUS == ui4_msg)
    {
        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
        menu_pm_repaint();
    }
    else if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        switch ((UINT32)param1)
        {
            case BTN_RETURN :
            case BTN_SELECT :
            {
                menu_nav_back();
                break;
            }
            case BTN_CURSOR_DOWN:
            {
                b_from_backbar = TRUE;
                i4_ret = c_wgl_set_focus(h_sb_setting_eq_mode, WGL_NO_AUTO_REPAINT);
                MENU_CHK_FAIL(i4_ret);
                break;
            }
            default :
                break ;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, param1, param2);
}

static VOID _sb_setting_eq_mode_move_help_tip(UINT8 ui1_row_num)
{
    INT32 i4_ret;
    GL_RECT_T t_rect;
    HANDLE_T  h_last_shadow_item;

    /* move help tip text */
    t_rect.i4_left = CONTENT_X;
    t_rect.i4_right = CONTENT_X + CONTENT_H;
    t_rect.i4_top = MENU_ITEM_V_HEIGHT * ui1_row_num + CONTENT_Y;
    t_rect.i4_bottom = t_rect.i4_top + HELP_TIP_FRAME_H;

    i4_ret = menu_pm_get_last_shadow_item(&h_last_shadow_item);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_move(h_last_shadow_item, &t_rect, WGL_NO_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_last_shadow_item, WGL_SW_NORMAL);
    MENU_LOG_ON_FAIL(i4_ret);

}

static INT32 _sb_setting_eq_mode_lb2_proc_fct(HANDLE_T            h_widget,
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2)
{
    INT32   i4_ret;
    UINT16  ui2_crnt_ht;
    INT16   i2_value = 0;
    UINT8   ui2_idx = 0;
    UINT8   ui1_num = acfg_custom_get_eq_mode_valid_num();

    if(WGL_MSG_GET_FOCUS==ui4_msg)
    {
        if (b_from_backbar)
        {
            b_from_backbar = FALSE;

            i4_ret=c_wgl_do_cmd(h_sb_setting_eq_mode,
                                WGL_CMD_LB_HLT_ELEM,
                                WGL_PACK(0),
                                NULL);
            MENU_LOG_ON_FAIL(i4_ret);
        }
        else
        {
            i2_value = (_MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_T)acfg_custom_get_eq_mode_type();

            do
            {
                if (i2_value == arr_sb_setting_eq_mode[ui2_idx].e_eq_mode)
                {
                    i4_ret = c_wgl_do_cmd(h_sb_setting_eq_mode,
                                WGL_CMD_LB_HLT_ELEM,
                                WGL_PACK(ui2_idx),
                                NULL);
                    MENU_LOG_ON_FAIL(i4_ret);
                    break;
                }
                ui2_idx++;
            }while(ui2_idx < ui1_num);
        }

        //menu_set_help_tip(MENU_TEXT(MLM_MENU_KEY_MENU_ASPECT_RATIO_HELP_TEXT));
        menu_pm_repaint();
    }
    else if(WGL_MSG_KEY_DOWN==ui4_msg)
    {
         i4_ret = c_wgl_do_cmd(h_sb_setting_eq_mode,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);

        MENU_LOG_ON_FAIL(i4_ret);

        switch ((UINT32)pv_param1)
        {
            case BTN_SELECT:
            {
                acfg_custom_set_eq_mode_type(  (UINT8)(arr_sb_setting_eq_mode[ui2_crnt_ht].e_eq_mode));
                i4_ret = nav_cec_sac_set_EQ_mode((UINT8)(arr_sb_setting_eq_mode[ui2_crnt_ht].e_eq_mode));
                MENU_CHK_FAIL(i4_ret);
            }

            case BTN_RETURN:
                i4_ret = c_wgl_set_visibility(h_sb_setting_eq_mode, WGL_SW_HIDE);
                MENU_LOG_ON_FAIL(i4_ret);
                menu_nav_back();
                break;

            case BTN_CURSOR_UP:
                if (ui2_crnt_ht == 0)
                {
                    i4_ret = c_wgl_do_cmd(h_sb_setting_eq_mode,
                                          WGL_CMD_LB_UNHLT_ELEM,
                                          WGL_PACK(ui2_crnt_ht),
                                          NULL);
                    MENU_LOG_ON_FAIL(i4_ret);

                    i4_ret = menu_set_focus_on_backbar(FALSE);
                    MENU_LOG_ON_FAIL(i4_ret);

                    return MENUR_OK;
                }
                break;
            case BTN_CURSOR_DOWN:
                break;
            default:
                break;
        }
    }
#ifdef APP_TTS_SUPPORT
    else if (WGL_MSG_KEY_UP==ui4_msg)
    {
        UINT32  ui4_crnt_page;
        UTF16_T*  pt_w2s = NULL;

        i4_ret = menu_nav_get_crnt_page(&ui4_crnt_page);
        MENU_CHK_FAIL(i4_ret);

        if (ui4_crnt_page == ui4_g_menu_page_sb_setting_eq_mode)
        {
            i4_ret = c_wgl_do_cmd(h_sb_setting_eq_mode,
                              WGL_CMD_LB_GET_HLT_INDEX,
                              WGL_PACK(&ui2_crnt_ht),
                              NULL);
            MENU_LOG_ON_FAIL(i4_ret);

            pt_w2s = MENU_TEXT(_get_sb_setting_eq_mode_mlm_idx(arr_sb_setting_eq_mode[ui2_crnt_ht].e_eq_mode));

            a_app_tts_play(pt_w2s, c_uc_w2s_strlen(pt_w2s));
        }
    }
#endif

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

static VOID _menu_page_sb_settings_eq_mode_get_valid_type(VOID)
{
    UINT8 ui1_idx,ui2_idx = 0;
    BOOL bEnable;

    c_memset(arr_sb_setting_eq_mode, 0, sizeof(arr_sb_setting_eq_mode));

    for(ui1_idx = _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT; ui1_idx <  _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MAX; ui1_idx++)
    {
        bEnable = FALSE;

        switch(ui1_idx)
        {
            case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MUSIC:
            if(acfg_custom_get_eq_mode_enable_music() == TRUE){
            bEnable = TRUE;
            }
            break;

            case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_MOVIE:
            if(acfg_custom_get_eq_mode_enable_movie() == TRUE){
            bEnable = TRUE;
            }
            break;

            case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_GAME:
            if(acfg_custom_get_eq_mode_enable_game() == TRUE){
            bEnable = TRUE;
            }
            break;

            case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DIRECT:
            if(acfg_custom_get_eq_mode_enable_direct() == TRUE){
            bEnable = TRUE;
            }
            break;

            case _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DIALOGUE:
            if(acfg_custom_get_eq_mode_enable_dialogue() == TRUE){
            bEnable = TRUE;
            }
            break;
            default:
            break;
        }

        if(bEnable == TRUE)
        {
            arr_sb_setting_eq_mode[ui2_idx].e_eq_mode = (_MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_T)ui1_idx;
            ui2_idx++;
        }
    }
}
static INT32 _on_page_show(
    UINT32 ui4_page_id)
{
    INT32  i4_ret = 0;
    HANDLE_T  h_cnt_frm;
    _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_T    e_sb_setting_eq_mode = _MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_DEFAULT;
    UINT8  ui1_num = 0;
    UINT8  ui1_idx = 0;

    /* set title */
    menu_main_set_title(MLM_MENU_KEY_AUD_EQ_MODE_INDENTATION);
    MENU_CHK_FAIL(i4_ret);

    /* set callback function for backbar */
    menu_set_backbar_proc(_backbar_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_page_get_cnt_frm(ui4_page_id, &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    ui1_num = acfg_custom_get_eq_mode_valid_num();
    //DBG_LOG_PRINT(("#### %s(%d) ui1_num = %d\n", __FILE__, __LINE__,ui1_num));

    if(ui1_num == 0){
    DBG_LOG_PRINT(("#### %s(%d) MENUR_INV_ARG\n", __FILE__, __LINE__));
    return MENUR_INV_ARG;
    }

    _menu_page_sb_settings_eq_mode_get_valid_type();

    i4_ret = _sb_setting_eq_mode_lb2_create(h_cnt_frm, &h_sb_setting_eq_mode, _sb_setting_eq_mode_lb2_proc_fct);
    MENU_CHK_FAIL(i4_ret);

    e_sb_setting_eq_mode = (_MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_T)acfg_custom_get_eq_mode_type();
    //DBG_LOG_PRINT(("#### %s(%d) e_sb_setting_eq_mode = %d\n", __FILE__, __LINE__,e_sb_setting_eq_mode));

    i4_ret = c_wgl_do_cmd(h_sb_setting_eq_mode,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK(ui1_num),
                          NULL);

    do {
        i4_ret = c_wgl_do_cmd(h_sb_setting_eq_mode,
                            WGL_CMD_LB_SET_ITEM_TEXT,
                            WGL_PACK_2 (ui1_idx, 0),
                            WGL_PACK(MENU_TEXT(_get_sb_setting_eq_mode_mlm_idx((_MENU_PAGE_SETTINGS_SB_SETTINGS_EQ_MODE_T)arr_sb_setting_eq_mode[ui1_idx].e_eq_mode)))
                            );
        MENU_LOG_ON_FAIL(i4_ret);

        //DBG_LOG_PRINT(("#### %s(%d) e_eq_mode[%d]=%d\n", __FILE__, __LINE__,ui1_idx,arr_sb_setting_eq_mode[ui1_idx].e_eq_mode));

    } while(ui1_idx++ <ui1_num);

    c_wgl_set_visibility(h_sb_setting_eq_mode, WGL_SW_NORMAL);
    c_wgl_set_focus(h_sb_setting_eq_mode, WGL_NO_AUTO_REPAINT);

    _sb_setting_eq_mode_move_help_tip(ui1_num);
    menu_pm_repaint();

    return MENUR_OK;
}

static INT32 _on_page_hide(
    UINT32 ui4_page_id)
{
    INT32  i4_ret;

    i4_ret = c_wgl_set_visibility(h_sb_setting_eq_mode, WGL_SYNC_AUTO_REPAINT);
    MENU_LOG_ON_FAIL(i4_ret);

    c_wgl_destroy_widget(h_sb_setting_eq_mode);
    MENU_LOG_ON_FAIL(i4_ret);

    h_sb_setting_eq_mode = NULL_HANDLE;

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

extern INT32 menu_page_sb_setting_eq_mode_init(VOID)
{
    t_g_menu_page_sb_setting_eq_mode.pf_menu_page_create =    _on_page_create;
    t_g_menu_page_sb_setting_eq_mode.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_page_sb_setting_eq_mode.pf_menu_page_show=       _on_page_show;
    t_g_menu_page_sb_setting_eq_mode.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_page_sb_setting_eq_mode.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_page_sb_setting_eq_mode.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_page_sb_setting_eq_mode.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}

static VOID _do_refresh_Eqmode(
    VOID* pv_data,
    SIZE_T  z_data_size)
{

    menu_pm_repaint();
    menu_pm_refresh();

}


extern UINT32 ui4_page_aud_sb_settings;
extern UINT32 ui4_g_menu_page_sb_setting_eq_mode;
static UINT8 sb_live_Count = 0;
extern INT32 menu_page_cec_sb_settings_refresh(VOID)
{
    UINT32 ui4_cnt_page = 0;
    INT32 i4_ret = menu_nav_get_crnt_page(&ui4_cnt_page);

    //DBG_LOG_PRINT(("\n ####%s(%d) \n",__FUNCTION__,__LINE__));

    if(i4_ret == MENUR_OK)
    {
        if(nav_cec_custom_get_enable_soundbarsettings() == TRUE)
        {
            if(ui4_cnt_page == ui4_page_aud_sb_settings \
            ||ui4_cnt_page == ui4_g_menu_page_sb_setting_eq_mode \
            ||ui4_cnt_page == ui4_g_menu_page_aud)
            {
                menu_async_invoke(_do_refresh_Eqmode, (VOID*)NULL, 0, TRUE);

            }
            sb_live_Count = 0;
        }
        else
        {
            sb_live_Count++;

            if((sb_live_Count > 0) \
            && (ui4_cnt_page == ui4_page_aud_sb_settings \
            ||ui4_cnt_page == ui4_g_menu_page_sb_setting_eq_mode))
            {
                c_iom_send_evt (BTN_MENU, 100);
                c_thread_delay(100);
            }
        }
    }
}



