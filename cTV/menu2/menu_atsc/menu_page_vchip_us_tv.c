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
 * $RCSfile: menu_page_vchip_us_tv.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/15 $
 * $SWAuthor: Richard Lu $
 * $MD5HEX: 61cb1377f1f69246c9ac07177bb76767 $
 *
 * Description:
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                   include files
-----------------------------------------------------------------------------*/
#include "u_irrc_btn_def.h"
#include "u_wgl_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_text.h"
#include "u_wgl_bdr_common.h"

#include "c_common.h"
#include "c_handle.h"
#include "c_handle_grp.h"
#include "c_uc_str.h"
#include "c_dbg.h"
#include "c_os.h"
#include "c_wgl.h"
#include "c_wgl_sets.h"

#include "app_util/a_common.h"
#include "app_util/a_cfg.h"

#include "menu2/menu_common/menu_common.h"
#include "menu2/menu_atsc/menu_atsc.h"
#include "menu2/menu_util2.h"
#include "menu2/menu_dbg.h"

#ifdef ATSC_VCHIP_US_TV_ENABLE
/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
 ----------------------------------------------------------------------------*/
#define     ATSC_VCHIP_US_TV_X_OFF
#define     COL_A   0
#define     COL_FV  1
#define     COL_D   2
#define     COL_L   3
#define     COL_S   4
#define     COL_V   5

#define     ROW_Y   0
#define     ROW_Y7  1
#define     ROW_G   2
#define     ROW_PG  3
#define     ROW_14  4
#define     ROW_MA  5

#define     H_CB_TV_Y      aah_cb_tr[0][0]
#define     H_CB_TV_Y7     aah_cb_tr[1][0]
#define     H_CB_TV_Y7_FV  aah_cb_tr[1][1]

#define     H_CB_TV_G      aah_cb_tr[2][0]
#define     H_CB_TV_PG     aah_cb_tr[3][0]
#define     H_CB_TV_PG_D   aah_cb_tr[3][2]
#define     H_CB_TV_PG_L   aah_cb_tr[3][3]
#define     H_CB_TV_PG_S   aah_cb_tr[3][4]
#define     H_CB_TV_PG_V   aah_cb_tr[3][5]

#define     H_CB_TV_14     aah_cb_tr[4][0]
#define     H_CB_TV_14_D   aah_cb_tr[4][2]
#define     H_CB_TV_14_L   aah_cb_tr[4][3]
#define     H_CB_TV_14_S   aah_cb_tr[4][4]
#define     H_CB_TV_14_V   aah_cb_tr[4][5]

#define     H_CB_TV_MA     aah_cb_tr[5][0]
#define     H_CB_TV_MA_L   aah_cb_tr[5][3]
#define     H_CB_TV_MA_S   aah_cb_tr[5][4]
#define     H_CB_TV_MA_V   aah_cb_tr[5][5]

#define MENU_VCHIP_GRID_W                  (MENU_ITEM_V_WIDE / 16)
#define MENU_VCHIP_GRID_H                  (62)
#define MENU_VCHIP_FIRST_TOP               (31)//1st row top
#define MENU_VCHIP_EACH_H                  (65)//height between each row
#define MENU_VCHIP_ROW_H                   (65)//height between each row
#define MENU_VCHIP_ICON_SIZE               (62)
#define MENU_VCHIP_BK_SIZE                 (400)
#define MENU_VCHIP_BK_X                    (162)
#define MENU_VCHIP_BK_Y                    (106)

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif
/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/
MENU_PAGE_FCT_TBL_T  t_g_menu_atsc_page_vchip_us_tv;

static UTF16_T* aw2s_str_dims[] =
{
    _TEXT("All"),
    _TEXT("FV"),
    _TEXT("D"),
    _TEXT("L"),
    _TEXT("S"),
    _TEXT("V")

};

static UTF16_T* aw2s_str_ages[] =
{
    _TEXT("TV-Y"),
    _TEXT("TV-Y7"),
    _TEXT("TV-G"),
    _TEXT("TV-PG"),
    _TEXT("TV-14"),
    _TEXT("TV-MA")
};

static BOOL        b_created = FALSE;
static HANDLE_T    h_cnt_frm;
static HANDLE_T    h_cnt_frm_scrip;
static HANDLE_T    h_lb_idctr;
static HANDLE_T    h_icon_bk;
static HANDLE_T    ah_txt_col[6];
static HANDLE_T    ah_txt_row[6];
static HANDLE_T    aah_cb_tr[6][6];
static BOOL        aab_locked[6][6];

static UINT16      aaui2_tip_id[6][6] =
                    {
                       {MLM_MENU_KEY_HELP_TIP_RATE_TV_Y,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY},
                       {MLM_MENU_KEY_HELP_TIP_RATE_TV_Y7,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_Y7_FV,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY},
                       {MLM_MENU_KEY_HELP_TIP_RATE_TV_G,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY},
                       {MLM_MENU_KEY_HELP_TIP_RATE_TV_PG,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_PG_D,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_PG_L,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_PG_S,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_PG_V},
                       {MLM_MENU_KEY_HELP_TIP_RATE_TV_14,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_14_D,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_14_L,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_14_S,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_14_V},
                       {MLM_MENU_KEY_HELP_TIP_RATE_TV_MA,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_EMPTY,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_MA_L,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_MA_S,
                            MLM_MENU_KEY_HELP_TIP_RATE_TV_MA_V}
                    };

/*-----------------------------------------------------------------------------
                    function declarations
 ----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name: _backbar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _backbar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_SELECT:
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_CURSOR_DOWN:
            c_wgl_set_focus(H_CB_TV_Y, WGL_SYNC_AUTO_REPAINT);
            menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[0][0]));
            menu_hide_help_tip();
            break;

        case BTN_CURSOR_UP:
            menu_set_focus_on_homebar(TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_HOME_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _homebar_proc_fct
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _homebar_proc_fct (HANDLE_T        h_widget,
                                UINT32          ui4_msg,
                                VOID*           pv_param1,
                                VOID*           pv_param2)
{
    if (WGL_MSG_KEY_DOWN == ui4_msg)
    {
        UINT32 ui4_keycode = (UINT32)pv_param1;

        switch (ui4_keycode)
        {
        case BTN_CURSOR_LEFT:
        #ifndef BTN_LEFT_BACK_RIGHT_SELECT
            return MENUR_OK;
        #endif
        case BTN_PREV_PRG:
        case BTN_RETURN:
            menu_nav_back();
            return WGLR_OK;

        case BTN_SELECT:
            menu_nav_go_home_menu();
            return WGLR_OK;

        case BTN_CURSOR_UP:
/*
            c_wgl_set_focus(H_CB_TV_Y, WGL_SYNC_AUTO_REPAINT);

            menu_hide_help_tip();
*/
            break;

        case BTN_CURSOR_DOWN :
            menu_set_focus_on_backbar (TRUE);
            menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _create_col_title
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
static INT32 _create_col_title(INT32       i4_index,
                               UTF16_T*    w2s_str,
                               HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T    t_clr_txt;
    WGL_COLOR_INFO_T    t_clr_bk;
    WGL_FONT_INFO_T             t_fnt_info;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_VCHIP_GRID_W * 4 + MENU_VCHIP_EACH_H * (i4_index),
                     MENU_ITEM_V_HEIGHT/2,
                     MENU_VCHIP_GRID_W * 2,
                     MENU_VCHIP_GRID_H);

    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_str,
                          (VOID*)c_uc_w2s_strlen(w2s_str));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = 25;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_txt.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_txt.u_color_data.t_standard.t_enable   = t_g_menu_color_bk1_txt;
    t_clr_txt.u_color_data.t_standard.t_highlight= t_g_menu_color_bk1_txt;
    t_clr_txt.u_color_data.t_standard.t_disable  = t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_txt ));
    MENU_CHK_FAIL(i4_ret);

    t_clr_bk.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_bk.u_color_data.t_standard.t_enable    = t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_standard.t_highlight = t_g_menu_color_bk1;
    t_clr_bk.u_color_data.t_standard.t_disable   = t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_bk ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_row_title
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
static INT32 _create_row_title(INT32       i4_index,
                               UTF16_T*    w2s_str,
                               HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_FONT_INFO_T t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_txt;
    WGL_COLOR_INFO_T    t_clr_bk;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_VCHIP_GRID_W * 1,
                     MENU_ITEM_V_HEIGHT + MENU_VCHIP_FIRST_TOP + MENU_VCHIP_EACH_H * i4_index,
                     MENU_VCHIP_GRID_W * 3,
                     MENU_VCHIP_ROW_H);

    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_IMG_UI | WGL_STL_TEXT_MAX_32),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_TEXT,
                          w2s_str,
                          (VOID*)c_uc_w2s_strlen(w2s_str));
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_CENTER,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, menu_font_name());
    t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_fnt_info.ui1_custom_size = 25;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set color */
    t_clr_txt.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_txt.u_color_data.t_standard.t_enable       =t_g_menu_color_bk1_txt;
    t_clr_txt.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk1_txt;
    t_clr_txt.u_color_data.t_standard.t_disable      =t_g_menu_color_bk1_txt;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_txt ));
    MENU_CHK_FAIL(i4_ret);


    t_clr_bk.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_bk.u_color_data.t_standard.t_enable       =t_g_menu_color_transp;
    t_clr_bk.u_color_data.t_standard.t_highlight    =t_g_menu_color_bk1;
    t_clr_bk.u_color_data.t_standard.t_disable      =t_g_menu_color_transp;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_bk ));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_cb
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
static INT32 _create_cb(INT32       i4_x,
                        INT32       i4_y,
                        HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    WGL_IMG_INFO_T  t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_VCHIP_BK_X + 66 * i4_x,
                     MENU_VCHIP_BK_Y + 66 * i4_y,
                     MENU_VCHIP_ICON_SIZE,
                     MENU_VCHIP_ICON_SIZE);

    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (void*)(WGL_STL_GL_NO_BK | WGL_STL_BTN_CHECKBOX),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_enable             = h_g_menu_ratings_unlock_icon_v2;
    t_img_info.u_img_data.t_extend.t_disable            = h_g_menu_ratings_unlock_icon_v2;
    t_img_info.u_img_data.t_extend.t_highlight          = h_g_unlock_white_hlt_v2;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = h_g_unlock_white_hlt_v2;
    t_img_info.u_img_data.t_extend.t_push               = h_g_lock_white_hlt_v2;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = h_g_menu_ratings_lock_icon_v2;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info) );
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _create_bk_icon
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
static INT32 _create_bk_icon(VOID)
{
    INT32           i4_ret;
    GL_RECT_T       t_rect;
    UINT32          ui4_style;
    WGL_IMG_INFO_T  t_img_info;

    ui4_style = 0;

    SET_RECT_BY_SIZE(&t_rect,
                     MENU_VCHIP_BK_X,
                     MENU_ITEM_V_HEIGHT + MENU_VCHIP_ICON_SIZE/2,
                     MENU_VCHIP_BK_SIZE,
                     MENU_VCHIP_BK_SIZE);

    i4_ret = c_wgl_create_widget(h_cnt_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &h_icon_bk);

    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    /* set image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_g_menu_ratings_bk_icon_v2;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_ratings_bk_icon_v2;
    t_img_info.u_img_data.t_standard.t_disable = h_g_menu_ratings_bk_icon_v2;
    i4_ret = c_wgl_do_cmd(h_icon_bk,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _page_create
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
INT32 _page_create(VOID)
{
    INT32   i4_ret;

    i4_ret = menu_text_create(h_cnt_frm, 0, NULL, &h_cnt_frm_scrip);
    MENU_CHK_FAIL(i4_ret);
    menu_range_chg_lang(h_cnt_frm_scrip, MLM_MENU_KEY_VCHIP_US_TV);

    i4_ret = _create_col_title(0, aw2s_str_dims[0], &ah_txt_col[0]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(1, aw2s_str_dims[1], &ah_txt_col[1]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(2, aw2s_str_dims[2], &ah_txt_col[2]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(3, aw2s_str_dims[3], &ah_txt_col[3]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(4, aw2s_str_dims[4], &ah_txt_col[4]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_col_title(5, aw2s_str_dims[5], &ah_txt_col[5]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(0, aw2s_str_ages[0], &ah_txt_row[0]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(1, aw2s_str_ages[1], &ah_txt_row[1]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(2, aw2s_str_ages[2], &ah_txt_row[2]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(3, aw2s_str_ages[3], &ah_txt_row[3]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(4, aw2s_str_ages[4], &ah_txt_row[4]);
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_row_title(5, aw2s_str_ages[5], &ah_txt_row[5]);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 0, &H_CB_TV_Y  );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(0, 1, &H_CB_TV_Y7  );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(1, 1, &H_CB_TV_Y7_FV);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 2, &H_CB_TV_G );
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 3, &H_CB_TV_PG );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(2, 3, &H_CB_TV_PG_D );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(3, 3, &H_CB_TV_PG_L );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(4, 3, &H_CB_TV_PG_S );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(5, 3, &H_CB_TV_PG_V );
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 4, &H_CB_TV_14 );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(2, 4, &H_CB_TV_14_D );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(3, 4, &H_CB_TV_14_L );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(4, 4, &H_CB_TV_14_S );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(5, 4, &H_CB_TV_14_V );
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_cb(0, 5, &H_CB_TV_MA );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(3, 5, &H_CB_TV_MA_L );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(4, 5, &H_CB_TV_MA_S );
    MENU_CHK_FAIL(i4_ret);
    i4_ret = _create_cb(5, 5, &H_CB_TV_MA_V );
    MENU_CHK_FAIL(i4_ret);

    i4_ret = menu_atsc_rating_indicator_create(h_cnt_frm,
                                               8,
                                               &h_lb_idctr);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = _create_bk_icon();
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_RECURSIVE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(h_lb_idctr,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lock_cb
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
static INT32 _lock_cb(UINT16 ui2_row,
                     UINT16 ui2_col,
                     BOOL b_lock)
{
    INT32 i4_ret;

    if(ui2_row >= 6 ||
       ui2_col >= 6)
    {
        return MENUR_INV_ARG;
    }

    i4_ret = c_wgl_do_cmd(aah_cb_tr[ui2_row][ui2_col],
                          WGL_CMD_BTN_SET_PUSHED,
                          WGL_PACK(b_lock),
                          NULL);
    MENU_CHK_FAIL(i4_ret);

    aab_locked[ui2_row][ui2_col] = b_lock;

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _unlock_age_based
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
static INT32 _unlock_age_based(UINT16 ui2_idx)
{
    INT32 i4_ret;
    UINT16 ui2_i = 0;
    UINT16 ui2_j = 0;

    if(ui2_idx >= 6)
    {
        return MENUR_INV_ARG;
    }

    for (ui2_i = 0; ui2_i <= ui2_idx; ui2_i++)
    {
        for (ui2_j = 0; ui2_j < 6; ui2_j++)
        {
            if (aah_cb_tr[ui2_i][ui2_j] != NULL_HANDLE &&
                aab_locked[ui2_i][ui2_j] == TRUE)
            {
                i4_ret = _lock_cb(ui2_i, ui2_j, FALSE);
                MENU_CHK_FAIL(i4_ret);
            }
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lock_age_based
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
static INT32 _lock_age_based(UINT16 ui2_idx)
{
    INT32 i4_ret;
    UINT16 ui2_i;
    UINT16 ui2_j;
    for (ui2_i = ui2_idx; ui2_i < 6; ui2_i++)
    {
        for (ui2_j = 0; ui2_j < 6; ui2_j++)
        {
            if (aah_cb_tr[ui2_i][ui2_j] != NULL_HANDLE &&
                aab_locked[ui2_i][ui2_j] == FALSE)
            {
                i4_ret = _lock_cb(ui2_i, ui2_j, TRUE);
                MENU_CHK_FAIL(i4_ret);
            }
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _unlock_cnt_based
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
static INT32 _unlock_cnt_based(UINT16 ui2_row,
                              UINT16 ui2_col)
{
    INT32 i4_ret;
    UINT16 ui2_i;

    if(ui2_row >= 6 ||
       ui2_col >= 6)
    {
        return MENUR_INV_ARG;
    }

    for (ui2_i = 0; ui2_i <= ui2_row; ui2_i++)
    {
        if (aah_cb_tr[ui2_i][ui2_col] != NULL_HANDLE &&
            aab_locked[ui2_i][ui2_col] == TRUE)
        {
            i4_ret = _lock_cb(ui2_i, ui2_col, FALSE);
            MENU_CHK_FAIL(i4_ret);
        }
    }

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _lock_cnt_based
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
static INT32 _lock_cnt_based(UINT16 ui2_row,
                             UINT16 ui2_col)
{
    INT32 i4_ret;
    UINT16 ui2_i;

    if(ui2_row >= 6 ||
       ui2_col >= 6)
    {
        return MENUR_INV_ARG;
    }

    for (ui2_i = ui2_row; ui2_i < 6; ui2_i++)
    {
        if (aah_cb_tr[ui2_i][ui2_col] != NULL_HANDLE &&
            aab_locked[ui2_i][ui2_col] == FALSE)
        {
            i4_ret = _lock_cb(ui2_i, ui2_col, TRUE);
            MENU_CHK_FAIL(i4_ret);
        }
    }
    return MENUR_OK;
}

static INT32 _set_vchip_settings()
{
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age = 0;
    UINT64  ui8_tv_cnt_map = 0;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;
    UINT8   ui1_i;


    a_cfg_lock();

    a_cfg_get_vchip_us(&ui1_mpaa,
                       &ui1_tv_age,
                       &ui8_tv_cnt_map,
                       &b_mpaa_bu,
                       &b_tv_bu);

    /* TV AGE */
    for (ui1_i = 0;
        ui1_i < 6;
        ui1_i ++)
    {
        if (aab_locked[ui1_i][0])
        {
            ui1_tv_age = ui1_i;
            break;
        }
    }

    if (ui1_i == 6)
    {
        ui1_tv_age = APP_CFG_VCHIP_US_AGE_OFF;
    }

    /* TV CNT */
    ui8_tv_cnt_map = 0;

    if (aab_locked[ROW_Y7][COL_FV])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_Y7_FV;
    }

    if (aab_locked[ROW_PG][COL_D])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_D;
    }

    if (aab_locked[ROW_PG][COL_L])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_L;
    }

    if (aab_locked[ROW_PG][COL_S])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_S;
    }

    if (aab_locked[ROW_PG][COL_V])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_PG_V;
    }

    if (aab_locked[ROW_14][COL_D])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_D;
    }

    if (aab_locked[ROW_14][COL_L])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_L;
    }

    if (aab_locked[ROW_14][COL_S])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_S;
    }

    if (aab_locked[ROW_14][COL_V])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_14_V;
    }

    if (aab_locked[ROW_MA][COL_L])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_L;
    }

    if (aab_locked[ROW_MA][COL_S])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_S;
    }

    if (aab_locked[ROW_MA][COL_V])
    {
        ui8_tv_cnt_map |= APP_CFG_VCHIP_US_CNT_TV_MA_V;
    }


    a_cfg_set_vchip_us(ui1_mpaa,
                       ui1_tv_age,
                       ui8_tv_cnt_map,
                       b_mpaa_bu,
                       b_tv_bu);

    a_cfg_unlock();

    return MENUR_OK;
}

static INT32 _get_vchip_settings()
{
    INT32   i4_ret;
    UINT8   ui1_mpaa;
    UINT8   ui1_tv_age;
    UINT64  ui8_tv_cnt_map;
    BOOL    b_mpaa_bu;
    BOOL    b_tv_bu;
    BOOL    b_lock;
    UINT8   ui1_i;

    i4_ret = a_cfg_get_vchip_us(&ui1_mpaa,
                                &ui1_tv_age,
                                &ui8_tv_cnt_map,
                                &b_mpaa_bu,
                                &b_tv_bu);
    if(i4_ret != APP_CFGR_OK)
    {
        return MENUR_FAIL;
    }

    /* TV AGE */
    for (ui1_i = 0;
        ui1_i < 6;
        ui1_i ++)
    {
        if(ui1_i < ui1_tv_age)
        {
            _lock_cb(ui1_i, COL_A, FALSE);
        }
        else
        {
            _lock_cb(ui1_i, COL_A, TRUE);
        }
    }

    /* TV CNT */
    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_Y7_FV) != 0);
    _lock_cb(ROW_Y7, COL_FV, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_D) != 0);
    _lock_cb(ROW_PG, COL_D, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_L) != 0);
    _lock_cb(ROW_PG, COL_L, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_S) != 0);
    _lock_cb(ROW_PG, COL_S, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_PG_V) != 0);
    _lock_cb(ROW_PG, COL_V, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_D) != 0);
    _lock_cb(ROW_14, COL_D, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_L) != 0);
    _lock_cb(ROW_14, COL_L, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_S) != 0);
    _lock_cb(ROW_14, COL_S, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_14_V) != 0);
    _lock_cb(ROW_14, COL_V, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_L) != 0);
    _lock_cb(ROW_MA, COL_L, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_S) != 0);
    _lock_cb(ROW_MA, COL_S, b_lock);

    b_lock = ((ui8_tv_cnt_map & APP_CFG_VCHIP_US_CNT_TV_MA_V) != 0);
    _lock_cb(ROW_MA, COL_V, b_lock);

    return MENUR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _get_crnt_item_index
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
static BOOL _get_crnt_item_index(HANDLE_T   h_widget,
                                 INT32*     pi4_x,
                                 INT32*     pi4_y)
{
    UINT16 ui2_i = 0;
    UINT16 ui2_j = 0;

    for (ui2_i = 0; ui2_i < 6; ui2_i++)
    {
        for (ui2_j = 0; ui2_j < 6; ui2_j++)
        {
            if (aah_cb_tr[ui2_i][ui2_j] == h_widget)
            {
                *pi4_x = ui2_i;
                *pi4_y = ui2_j;
                return TRUE;
            }
        }
    }

    return FALSE;
}
/*----------------------------------------------------------------------------
 * Name: _vchip_tts_play
 *
 * Description:play the focus tts
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
static INT32 _vchip_tts_play(INT32 i4_i, INT32 i4_j, BOOL b_locked)
{
#ifdef APP_TTS_SUPPORT
#define _STR_AGES_NUM        (6)
#define _STR_DIMS_NUM        (6)

static UTF16_T* _aw2s_str_ages[_STR_AGES_NUM] = {
                                    _TEXT("TV.Y"),
                                    _TEXT("TV.Y7"),
                                    _TEXT("TV.G"),
                                    _TEXT("TV.PG"),
                                    _TEXT("TV.14"),
                                    _TEXT("TV.MA")
                                };
static UTF16_T* _aw2s_str_dims[_STR_DIMS_NUM] = {
                                    _TEXT("All."),
                                    _TEXT("FV."),
                                    _TEXT("D."),
                                    _TEXT("L."),
                                    _TEXT("S."),
                                    _TEXT("V.")
                                };
    UTF16_T w2s_txt[64] = {0};
    UTF16_T *pw2s_tmp = L"";

    if (i4_i >= _STR_AGES_NUM || i4_j >= _STR_DIMS_NUM)
    {
        DBG_ERROR(("<MENU> %s() %d: Out of rang i4_i=%d,i4_j=%d\n", __FUNCTION__, __LINE__, i4_i, i4_j));
        return MENUR_FAIL;
    }

    pw2s_tmp = (b_locked) ? L"locked" : L"unlocked";

    c_uc_w2s_strncpy(w2s_txt, _aw2s_str_ages[i4_i], 63);
    c_uc_w2s_strncat(w2s_txt, L".", 63 - c_uc_w2s_strlen(w2s_txt));
    c_uc_w2s_strncat(w2s_txt, _aw2s_str_dims[i4_j], 63 - c_uc_w2s_strlen(w2s_txt));
    c_uc_w2s_strncat(w2s_txt, pw2s_tmp, 63 - c_uc_w2s_strlen(w2s_txt));
    a_app_tts_play(w2s_txt, c_uc_w2s_strlen(w2s_txt));
#endif
    return MENUR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _frm_proc_fct
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
static INT32 _frm_proc_fct(HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    INT32 i4_i = 0;
    INT32 i4_j = 0;
    HANDLE_T h_source;
    WGL_NOTIFY_DATA_T* pt_nfy_data;
    INT32 i4_cur_i = 0;
    INT32 i4_cur_j = 0;

    if (WGL_MSG_NOTIFY == ui4_msg)
    {
        h_source = (HANDLE_T)pv_param1;
        pt_nfy_data = (WGL_NOTIFY_DATA_T*)pv_param2;

        switch (pt_nfy_data->ui4_nc_code)
        {
		/*if crnt item have foucs,play tts*/
		 case WGL_NC_GL_GET_FOCUS:
            {
               if (_get_crnt_item_index(h_source, &i4_i, &i4_j))
               {
                   _vchip_tts_play(i4_i, i4_j, aab_locked[i4_i][i4_j]);
               }
               return WGLR_OK;
            }
         case WGL_NC_BTN_UNPUSHED:
         case WGL_NC_BTN_PUSHED:
             for (i4_i = 0; i4_i < 6; i4_i++)
             {
                 for (i4_j = 0; i4_j < 6; i4_j++)
                 {
                     if (aah_cb_tr[i4_i][i4_j] == h_source)
                     {
                         if (i4_j == 0)
                         {
                             if (aab_locked[i4_i][i4_j])
                             {
                                 _unlock_age_based(i4_i);
                             }
                             else
                             {
                                 _lock_age_based(i4_i);
                             }
                         }
                         else
                         {
                             if (aab_locked[i4_i][i4_j])
                             {
                                 _unlock_cnt_based(i4_i, i4_j);
                             }
                             else
                             {
                                 _lock_cnt_based(i4_i, i4_j);
                             }
                         }
#ifdef APP_TTS_SUPPORT
                         /* play tts */
                         if (aab_locked[i4_i][i4_j])
                         {
                            a_app_tts_play(L"locked", c_uc_w2s_strlen(L"locked"));
                         }
                         else
                         {
                            a_app_tts_play(L"unlocked", c_uc_w2s_strlen(L"unlocked"));
                         }
#endif
                         /* change the block level to CUSTOM */
                         /*_set_bl_index(4); */

                         /* repaint */
                         c_wgl_repaint(h_cnt_frm, NULL, TRUE);

                         /* set the vchip setting to configuration manager. */
                         _set_vchip_settings();

                         return WMPR_DONE;
                     }
                 }
             }
             break;

        case WGL_NC_GL_KEY_DOWN:
        case WGL_NC_GL_KEY_REPEAT:
            switch (pt_nfy_data->u.t_key.ui4_key_code)
            {
            case BTN_CURSOR_UP:
                if (_get_crnt_item_index(h_source, &i4_i, &i4_j))
                {
                    if (i4_i == 0)
                    {
                        menu_set_focus_on_backbar(TRUE);
                        menu_set_and_show_help_tip(MENU_TEXT(MLM_MENU_KEY_HELP_TIP_BACK_BAR));
                        break;
                    }
                    else
                    {
                        i4_i -= 1;
                    }
                    if (aah_cb_tr[i4_i][i4_j])
                    {
                        c_wgl_set_focus(aah_cb_tr[i4_i][i4_j], TRUE);
                        menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[i4_i][i4_j]));
                    }
                    else
                    {
                        for (i4_j = 5; i4_j >= 0; i4_j--)
                        {
                            if (aah_cb_tr[i4_i][i4_j])
                            {
                                c_wgl_set_focus(aah_cb_tr[i4_i][i4_j], TRUE);
                                menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[i4_i][i4_j]));
                            }
                        }
                    }
                }

                break;

            case BTN_CURSOR_DOWN:
                if (_get_crnt_item_index(h_source, &i4_i, &i4_j))
                {
                    if (i4_i >= 5)
                    {
                        menu_help_tip_keytip_set_focus(h_source,3,FALSE);
                        menu_pm_repaint();
                    }
                    else
                    {
                        i4_i += 1;

                        if (aah_cb_tr[i4_i][i4_j])
                        {
                            c_wgl_set_focus(aah_cb_tr[i4_i][i4_j], TRUE);
                            menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[i4_i][i4_j]));
                        }
                        else
                        {
                            for (i4_j = 0; i4_j <= 5; i4_j++)
                            {
                                if (aah_cb_tr[i4_i][i4_j])
                                {
                                    c_wgl_set_focus(aah_cb_tr[i4_i][i4_j], TRUE);
                                    menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[i4_i][i4_j]));
                                    break;
                                }
                            }
                        }
                    }
                }

                break;

            case BTN_CURSOR_LEFT:
            {
                if (_get_crnt_item_index(h_source, &i4_i, &i4_j))
                {
                    if (i4_j == 0)
                    {
                        #ifdef BTN_LEFT_BACK_RIGHT_SELECT
                            menu_nav_back();
                        #endif

                        return WMPR_DONE;
                    }

                    if ( (i4_j == 0) && (i4_i == 0) )
                    {
                        i4_cur_i = 5;
                        i4_cur_j = 4;
                    }
                    else
                    {
                        i4_cur_i = i4_i;
                        i4_cur_j = i4_j - 1;
                    }

                    for (i4_i = i4_cur_i; i4_i >= 0; i4_i--)
                    {
                        for (i4_j = i4_cur_j; i4_j >= 0; i4_j--)
                        {
                            if (aah_cb_tr[i4_i][i4_j])
                            {
                                c_wgl_set_focus(aah_cb_tr[i4_i][i4_j], TRUE);
                                menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[i4_i][i4_j]));
                                return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
                            }

                        }

                        i4_cur_j = 5;
                    }
                }

                break;
            }
            case BTN_CURSOR_RIGHT:
            {
                if (_get_crnt_item_index(h_source, &i4_i, &i4_j))
                {
                    i4_cur_i = i4_i;
                    if (i4_j >= 5)
                    {
                        i4_j = 0;
                        i4_cur_j = 0;
                    }
                    else
                    {
                        i4_cur_j = i4_j + 1;
                    }

                    for (i4_j = i4_cur_j; i4_j < 6; i4_j++)
                    {
                        if (aah_cb_tr[i4_cur_i][i4_j])
                        {
                            c_wgl_set_focus(aah_cb_tr[i4_cur_i][i4_j], TRUE);
                            menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[i4_i][i4_j]));
                            return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
                        }
                    }
                    for (i4_j = 0; i4_j < i4_cur_j; i4_j++)
                    {
                        if (aah_cb_tr[i4_cur_i][i4_j])
                        {
                            c_wgl_set_focus(aah_cb_tr[i4_cur_i][i4_j], TRUE);
                            menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[i4_i][i4_j]));
                            return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
                        }
                    }
                }

                break;
            }

            case BTN_PREV_PRG:
            case BTN_RETURN:
                menu_nav_back();
                return WMPR_DONE;

            default:
                break;
            }
            break;

        default:
            break;
        }
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
                        page interface implementation
-----------------------------------------------------------------------------*/
static INT32 _on_page_create(UINT32 ui4_page_id,
                             VOID*  pv_create_data)
{
    INT32   i4_ret = 0;

    i4_ret = menu_page_get_cnt_frm(ui4_page_id,
                                   &h_cnt_frm);
    MENU_CHK_FAIL(i4_ret);

    if(b_g_menu_lazy_init_support)
    {
        b_created = FALSE;
    }
    else
    {
        _page_create();
        b_created = TRUE;
    }

    menu_page_set_proc_func(ui4_page_id, _frm_proc_fct);

    return MENUR_OK;
}

static INT32 _on_page_destroy(UINT32 ui4_page_id)
{
    return MENUR_OK;
}

static INT32 _on_page_show(UINT32 ui4_page_id)
{
    INT32   i4_ret;
    if(!b_created)
    {
        _page_create();
        b_created = TRUE;

        i4_ret = c_wgl_set_visibility(h_cnt_frm,
                                      WGL_SW_NORMAL);
        MENU_CHK_FAIL(i4_ret);
    }

    _get_vchip_settings();

    menu_main_set_title(MLM_MENU_KEY_VCHIP_US_TV);

    return MENUR_OK;
}

static INT32 _on_page_hide(UINT32 ui4_page_id)
{

    return MENUR_OK;
}

static INT32 _on_page_get_focus(UINT32 ui4_page_id,
                                MENU_PAGE_HINT_T* pt_hint)
{
    /* use help tip instead of menu's help list */
    #if 0
    MENU_HELP_LST_BUCKET_T at_help_lst[] =
    {
        {h_g_menu_img_btn_enter,    MLM_MENU_KEY_HELP_SET},
        {h_g_menu_img_btn_select,   MLM_MENU_KEY_HELP_SELECT},
        {h_g_menu_img_btn_exit,     MLM_MENU_KEY_HELP_BACK}
    };

    menu_main_set_help(at_help_lst,
                       (UINT16)(sizeof(at_help_lst)/ sizeof(at_help_lst[0])));
    #endif

    MENU_LOG_ON_FAIL(c_wgl_set_visibility(h_lb_idctr, WGL_SW_NORMAL));

    c_wgl_set_focus(H_CB_TV_Y, WGL_NO_AUTO_REPAINT);
    menu_set_and_show_help_tip(MENU_TEXT(aaui2_tip_id[0][0]));

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
    if((ui4_update_mask & MENU_PAGE_UMASK_CHG_LANG) != 0)
    {
        menu_atsc_rating_indicator_chg_lang(h_lb_idctr);
    }

    return MENUR_OK;
}

extern INT32 menu_atsc_page_vchip_us_tv_init(VOID)
{
    t_g_menu_atsc_page_vchip_us_tv.pf_menu_page_create =    _on_page_create;
    t_g_menu_atsc_page_vchip_us_tv.pf_menu_page_destroy=    _on_page_destroy;
    t_g_menu_atsc_page_vchip_us_tv.pf_menu_page_show=       _on_page_show;
    t_g_menu_atsc_page_vchip_us_tv.pf_menu_page_hide=       _on_page_hide;
    t_g_menu_atsc_page_vchip_us_tv.pf_menu_page_get_focus=  _on_page_get_focus;
    t_g_menu_atsc_page_vchip_us_tv.pf_menu_page_lose_focus= _on_page_lose_focus;
    t_g_menu_atsc_page_vchip_us_tv.pf_menu_page_update=     _on_page_update;

    return MENUR_OK;
}


#endif /* ATSC_VCHIP_US_TV_ENABLE */

