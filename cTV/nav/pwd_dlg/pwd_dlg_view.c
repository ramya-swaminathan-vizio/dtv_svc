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
 * $RCSfile: pwd_dlg_view.c,v $
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
#include "u_common.h"
#include "u_wgl_sets.h"
#include "u_wgl_lb.h"
#include "u_irrc_btn_def.h"
#include "u_wgl_bdr_common.h"

#include "c_handle.h"
#include "c_gl.h"
#include "c_uc_str.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_rect.h"

#include "nav/pwd_dlg/pwd_dlg.h"
#include "res/nav/nav_mlm.h"
#include "res/nav/nav_colors.h"
#include "res/nav/nav_img.h"
#include "res/nav/nav_variant.h"
#include "res/nav/nav_img_rc.h"
#include "res/revolt/revolt_warnings_mlm.h"
#include "res/revolt/revolt_settings_mlm.h"

#ifdef APP_TTS_SUPPORT
#include "res/app_util/tts/a_tts_custom.h"
#endif


#include "c_wgl.h"
#include "menu2/menu.h"
#include "menu2/menu_common/menu_common.h"
#include "wdk/a_digit_pad.h"
#include "res/wdk/digit_pad/digit_images.h"


#ifndef APP_NO_PWD_DLG
/*-----------------------------------------------------------------------------
 * structure, constants, macro definitions
 *---------------------------------------------------------------------------*/
#define IS_SYNC_REPAINT             TRUE
#define FRAME_STYLE                 (NULL)
#define PWD_ALARM_DELAY             2000

#define PWD_FRAME_WIDTH             (1920)
#define PWD_FRAME_HEIGHT            (240)
#define PWD_FRAME_LEFT              (0)
#define PWD_FRAME_TOP               (0)

#define PWD_BOX_WIDTH               (55)
#define PWD_BOX_HEIGHT              (65)
#define PWD_BOX_LEFT                (800)
#define PWD_BOX_TOP                 (20)
#define PWD_BOX_DIS                 (4)

#define PWD_ALARM_WIDTH             (1320)
#define PWD_ALARM_HEIGHT            (32)
#define PWD_ALARM_LEFT              (300)
#define PWD_ALARM_TOP               (100)

#define PWD_TITLE_WIDTH             (760)

#define PWD_TITLE_HEIGHT            (53)

#define PWD_TITLE_LEFT              (600)
#define PWD_TITLE_TOP               (44)

#define PWD_ICON_WIDTH              (1920)
#define PWD_ICON_HEIGHT             (32)
#define PWD_ICON_LEFT               (0)
#define PWD_ICON_TOP                (200)

#define PWD_DLG_HIDE_TIMER_DELAY    (5000)

/*-----------------------------------------------------------------------------
 * variable declarations
 *---------------------------------------------------------------------------*/
static PWD_DLG_VIEW_T*  pt_g_pwd_data            = NULL;
static PWD_DLG_VIEW_T*  pt_g_pwd_warning         = NULL;

static UTF16_T*         pw2s_g_pwd_title         = NULL;
static UTF16_T*         pw2s_g_pwd_alarm         = NULL;
static UTF16_T*         pw2s_g_pwd_warning       = NULL;
static PWD_DLG_BUTTON_T e_current_button         = BUTTON_1;
static UTF16_T w2s_g_str[BUTTON_LAST_ENTRY + 1]  = {0};
static WGL_HIMG_TPL_T       h_g_pwd_dlg_bk_img;
static WGL_HIMG_TPL_T       h_g_pwd_dlg_inp_img;
static WGL_HIMG_TPL_T       h_g_pwd_dlg_sel_img;


static WGL_HIMG_TPL_T       h_g_pwd_dlg_down_img;
static WGL_HIMG_TPL_T       h_g_pwd_dlg_cancel_focus_img;
static WGL_HIMG_TPL_T       h_g_pwd_dlg_cancel_inactive_img;
static WGL_HIMG_TPL_T       h_g_pwd_dlg_up_img;

static UINT8       ui1_loop = 0;
static BOOL        b_is_warning_init = FALSE;
static HANDLE_T    h_digit_handle;
static BOOL        b_cancel_state = TRUE ;

/*-----------------------------------------------------------------------------
 * private methods declarations
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_frame_proc_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    );

static INT32 _pwd_dlg_view_show_box(VOID);

static INT32 _pwd_dlg_view_warning_deinit(VOID);


static INT32 _digit_pad_create( UINT32 ui4_page_id,VOID*  pv_create_data);
static INT32 _pwd_dlg_view_show_warning_msgs(UINT8  ui1_change_state);
static INT32 _pwd_dlg_view_show_cancel_text(VOID);
static INT32 _pwd_dlg_view_switch_cancel_background(BOOL b_cancel_state);

/*-----------------------------------------------------------------------------
 * private methods implementations
 *---------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _init_txt_alarm
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_init_parent_frame(
                    HANDLE_T            h_parent,
                    HANDLE_T*           ph_widget)
{
    INT32             i4_ret;
    GL_RECT_T         t_rect;
    UINT32            ui4_style;
    WGL_IMG_INFO_T    t_img_info;

    ui4_style = 0;

    c_memset(&t_rect, 0x0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE( &t_rect,
                      (INT32)PWD_FRAME_LEFT,
                      (INT32)PWD_FRAME_TOP,
                      (INT32)PWD_FRAME_WIDTH,
                      (INT32)PWD_FRAME_HEIGHT+800);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);

    if (i4_ret < 0)
    {
        return NAVR_FAIL;
    }

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_init_pwd_button
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_init_pwd_button(
                    HANDLE_T            h_parent,
                    HANDLE_T*           ph_widget,
                    UINT8               ui1_idx
                    )
{
    INT32               i4_ret;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = 0;

    c_memset(&t_rect, 0x0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     (INT32)(PWD_BOX_LEFT + ((PWD_BOX_DIS + PWD_BOX_WIDTH)*ui1_idx)+70),
                     (INT32) (PWD_TITLE_TOP + PWD_TITLE_HEIGHT+PWD_BOX_HEIGHT+PWD_ALARM_HEIGHT+4*20),
                     (INT32)PWD_BOX_WIDTH,
                     (INT32)PWD_BOX_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _pwd_dlg_view_frame_proc_fct,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    NAVR_CHK_FAIL(i4_ret);

    c_memset(&t_inset, 0x0, sizeof(WGL_INSET_T));

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_INSET,
                           &t_inset,
                           NULL);
    NAVR_CHK_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = 0;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    NAVR_CHK_FAIL(i4_ret);


    if(ui1_idx == 0)
    {
         c_wgl_enable(*ph_widget, TRUE);
    }
    else
    {
         c_wgl_enable(*ph_widget,FALSE);
    }

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable             = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_disable            = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_highlight          = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_push               = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    NAVR_CHK_FAIL(i4_ret);

    /* Set Image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_pwd_dlg_sel_img;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_pwd_dlg_sel_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_pwd_dlg_sel_img;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    NAVR_CHK_FAIL(i4_ret);


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    NAVR_CHK_FAIL(i4_ret);


    return NAVR_OK;
}
VOID nav_set_pwd_dlg_view_cannel_status(BOOL b1_status)
{
     b_cancel_state = b1_status ;
}

BOOL nav_get_pwd_dlg_view_cannel_status(VOID)
{
    return b_cancel_state;
}
/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_cancel_proc_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_cancel_proc_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               param1,
                    VOID*               param2
                    )
{
    UINT32 ui4_keycode      = (UINT32)param1;
    static HANDLE_T h_focus = NULL_HANDLE;

    switch (ui4_msg)
    {
        DBG_LOG_PRINT(("[PWD_DLG] ui4_keycode:%d,b_cancel_state:%d \n",ui4_keycode,b_cancel_state));
        case WGL_MSG_KEY_DOWN:
        {
            switch(ui4_keycode)
            {
                case BTN_SELECT:
                    b_cancel_state = !b_cancel_state;
                    _pwd_dlg_view_switch_cancel_background(b_cancel_state);

                    break;
                case BTN_CURSOR_DOWN:
                    if (b_cancel_state == FALSE)
                    {
                         nav_rcu_key_handler(ui4_keycode);
                    }

                    break;
                case BTN_CURSOR_UP:
                    if (b_cancel_state == FALSE)
                    {
                        nav_rcu_key_handler(ui4_keycode);
                    }
                    else
                    {
                        b_cancel_state = TRUE;
                        _pwd_dlg_view_switch_cancel_background(FALSE);
                        a_digit_pad_focus(h_digit_handle);
                    }

                    break;
                default :
                    nav_rcu_key_handler(ui4_keycode);
                    break;
            }
        }
    default:
        break;
    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
}

/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_init_cancel_button
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_init_cancel_button(
                    HANDLE_T            h_parent,
                    HANDLE_T*           ph_widget
                    )
{
    INT32               i4_ret;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_INSET_T         t_inset;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = 0;

    c_memset(&t_rect, 0x0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
                     (INT32)(PWD_BOX_LEFT + 20 +70),
                     (INT32) (360  +310),
                     (INT32) 204,
                     (INT32)50);


    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 _pwd_dlg_view_cancel_proc_fct,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    NAVR_CHK_FAIL(i4_ret);


    c_memset(&t_inset, 0x0, sizeof(WGL_INSET_T));

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_INSET,
                           &t_inset,
                           NULL);
    NAVR_CHK_FAIL(i4_ret);

    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));
    t_inset.i4_left     = -5;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 0;
    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;
    t_clr_info.u_color_data.t_extend.t_enable             = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_disable            = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_highlight          = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_push               = NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    NAVR_CHK_FAIL(i4_ret);

    /* Set Image */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_pwd_dlg_cancel_inactive_img;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_pwd_dlg_cancel_inactive_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_pwd_dlg_cancel_inactive_img;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    NAVR_CHK_FAIL(i4_ret);


    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_float(*ph_widget, TRUE, WGL_NO_AUTO_REPAINT);
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_init_help_tips
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_init_help_tips(HANDLE_T    h_parent,
                             HANDLE_T*   ph_widget)
{
    INT32           i4_ret;

    WGL_INSET_T                 t_inset;
    WGL_HTS_INIT_T              t_init;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_HTS_PARAG_ATTR_T        t_parag;
    CHAR*                       s_font_name = SN_FONT_DEFAULT;
    GL_RECT_T                   t_rect;

    c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, s_font_name);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_SMALL;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;

    SET_RECT_BY_SIZE(&t_rect,
                       PWD_ALARM_LEFT+25,
                       (INT32) (360 +396 ), //30,
                       PWD_ALARM_WIDTH,
                       PWD_ALARM_HEIGHT);

    /* create hyper text widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     ph_widget);
    NAVR_CHK_FAIL(i4_ret);

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_HTS_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* set justification */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_CENTER),
                              NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    t_color_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_TRANS);
    t_color_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_TRANS);
    t_color_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_TRANS);
    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info));
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (*ph_widget,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_HTS_VP_BK), /* viewport color */
                              WGL_PACK (& t_color_info));
    NAVR_CHK_FAIL(i4_ret);

    return  0;

}


/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_show_help_tips
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_show_help_tips(VOID)
{
    INT32             i4_ret = 0;
    UTF16_T*          w2s_str = NULL;
    UTF16_T           w2s_str1[128] = {0};
    UTF16_T           w2s_str2[128] = {0};
    UTF16_T           w2s_str3[128] = {0};
    CHAR              s_str[128]={0};
    CHAR              s_str1[128]={0};
    CHAR              s_str2[128]={0};
    CHAR              s_str3[128]={0};
    UINT16                      ui2_sec_id = 0;
    WGL_HTS_TEXT_INFO_T         t_hts_txt_info;
    WGL_HTS_IMG_INFO_T     t_hts_img_info;

    c_memset (& t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
    c_memset (& t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));


    i4_ret = c_wgl_do_cmd (pt_g_pwd_data->h_help_tips,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL);
    NAVR_CHK_FAIL(i4_ret);
    /* Set font data. */
    c_strcpy (t_hts_txt_info.t_font.a_c_font_name, SN_FONT_DEFAULT);

    t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_hts_txt_info.t_font.ui1_custom_size = 21;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

	t_hts_txt_info.t_clr_text = NAV_COLOR(NAV_COLOR_ID_WHITE);


    w2s_str = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_DLG_DIGIT_PAD_HELP_TIPS);

    c_uc_w2s_to_ps(w2s_str,s_str,128);


   sscanf(s_str,"%[^%]%*s %[^%]%*s%[a-zA-Z ]",s_str1,s_str2,s_str3);

    c_uc_ps_to_w2s(s_str1,w2s_str1,c_strlen(s_str1));

    t_hts_txt_info.t_string.w2s_str = w2s_str1;
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(w2s_str1);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * c_uc_w2s_strlen(w2s_str1);

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_help_tips,
                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                            WGL_PACK(&t_hts_txt_info),
                            WGL_PACK (&ui2_sec_id));
    NAVR_CHK_FAIL(i4_ret);

    /*up*/
    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
    t_hts_img_info.h_img = h_g_pwd_dlg_up_img;

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_help_tips,
                            WGL_CMD_HTS_APPEND_IMG_SEC,
                            WGL_PACK(&t_hts_img_info),
                             WGL_PACK (&ui2_sec_id));
    NAVR_CHK_FAIL(i4_ret);

    c_uc_ps_to_w2s(s_str2,w2s_str2,128);
    t_hts_txt_info.t_string.w2s_str = w2s_str2;
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(w2s_str2);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * c_uc_w2s_strlen(w2s_str2);
    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_help_tips,
                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                            WGL_PACK(&t_hts_txt_info),
                             WGL_PACK (&ui2_sec_id));
    NAVR_CHK_FAIL(i4_ret);

    /*down*/
    t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
    t_hts_img_info.h_img =h_g_pwd_dlg_down_img;

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_help_tips,
                            WGL_CMD_HTS_APPEND_IMG_SEC,
                            WGL_PACK(&t_hts_img_info),
                            WGL_PACK (&ui2_sec_id));
    NAVR_CHK_FAIL(i4_ret);

    c_uc_ps_to_w2s(s_str3,w2s_str3,128);
    t_hts_txt_info.t_string.w2s_str = w2s_str3;
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(w2s_str3);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * c_uc_w2s_strlen(w2s_str3);
    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_help_tips,
                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                            WGL_PACK(&t_hts_txt_info),
                             WGL_PACK (&ui2_sec_id));
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_g_pwd_data->h_help_tips,
                            WGL_SW_RECURSIVE);
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_show_cancel_text
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_show_cancel_text(VOID)
{
    INT32             i4_ret = 0;
    UTF16_T*          w2s_str = NULL;
    CHAR              s_str[128]={0};

    w2s_str = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_DLG_DIGIT_PAD_CANNEL);

     c_uc_w2s_to_ps(w2s_str,s_str,128);

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_cancel_icon,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(w2s_str),
                            WGL_PACK(0xFF));
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_g_pwd_data->h_cancel_icon,
                            WGL_SW_RECURSIVE);

    return NAVR_OK;
}


#if  0
/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_init_title_txt
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_init_title_txt(HANDLE_T    h_parent,
                             HANDLE_T*   ph_widget)
{
    INT32               i4_ret;
    UINT32              ui4_style;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = WGL_STL_GL_NO_IMG_UI;

    SET_RECT_BY_SIZE(&t_rect,
                     PWD_TITLE_LEFT,
                     PWD_TITLE_TOP,
                     PWD_TITLE_WIDTH,
                     PWD_TITLE_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*) (ui4_style | WGL_STL_TEXT_MAX_128),
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    NAVR_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    NAVR_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_TRANS);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_TRANS);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_TRANS);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_init_title
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_init_title(HANDLE_T    h_parent,
                             HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    UINT32          ui4_style;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = WGL_STL_GL_NO_IMG_UI
                | WGL_STL_TEXT_MAX_512
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                     PWD_TITLE_LEFT,
                     PWD_TITLE_TOP+30, //30
                     PWD_TITLE_WIDTH,
                     PWD_TITLE_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT/*SN_FONT_DEFAULT_SMALL*/);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    NAVR_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    NAVR_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_TRANS);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_TRANS);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_TRANS);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

static INT32 _input_no_match_image_create(HANDLE_T h_parent, HANDLE_T* ph_widget)
{
    INT32 i4_ret = WDKR_OK;
    GL_RECT_T t_rect;
    WGL_IMG_INFO_T t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                     (PWD_FRAME_WIDTH-53)/2+20,
                     PWD_TITLE_TOP + PWD_TITLE_HEIGHT+30, //30
                     PWD_TITLE_WIDTH,
                     PWD_TITLE_HEIGHT+20);


    /* create widget */
    i4_ret = c_wgl_create_widget (h_parent,
                                    HT_WGL_WIDGET_ICON,
                                    WGL_CONTENT_ICON_DEF,
                                    WGL_BORDER_NULL,
                                    & t_rect,
                                    NULL,
                                    255,
                                    (VOID*)(0),
                                    0,
                                    ph_widget);
    if (i4_ret < 0)
    {
        return MENUR_CANT_CREATE_WIDGET;
    }

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_pin_no_match_bkg;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_pin_no_match_bkg;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_pin_no_match_bkg;

    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));

	i4_ret = c_wgl_set_visibility(*ph_widget,
                                  WGL_SW_HIDE);
    MENU_CHK_FAIL(i4_ret);

    return  i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _init_txt_alarm
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_init_txt_alarm(HANDLE_T    h_parent,
                             HANDLE_T*   ph_widget)
{
    INT32           i4_ret;
    UINT32          ui4_style;
    GL_RECT_T       t_rect;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style = WGL_STL_GL_NO_IMG_UI
                | WGL_STL_TEXT_MAX_512
                | WGL_STL_TEXT_MULTILINE
                | WGL_STL_TEXT_MAX_DIS_5_LINE;

    SET_RECT_BY_SIZE(&t_rect,
                      PWD_ALARM_LEFT+25,
                      PWD_TITLE_TOP + PWD_TITLE_HEIGHT+PWD_BOX_HEIGHT+3*20 , //30
                      PWD_ALARM_WIDTH,
                      PWD_ALARM_HEIGHT);

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 ph_widget);
    if (i4_ret < 0)
    {
        return NAVR_FAIL;
    }

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT/*SN_FONT_DEFAULT_SMALL*/);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                           WGL_CMD_GL_SET_FONT,
                           WGL_PACK(&t_fnt_info),
                           NULL);
    NAVR_CHK_FAIL(i4_ret);


    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_WHITE);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_WHITE);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    NAVR_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       =NAV_COLOR(NAV_COLOR_ID_TRANS);
    t_clr_info.u_color_data.t_standard.t_highlight    =NAV_COLOR(NAV_COLOR_ID_TRANS);
    t_clr_info.u_color_data.t_standard.t_disable      =NAV_COLOR(NAV_COLOR_ID_TRANS);
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

#if 0

/*----------------------------------------------------------------------------
 * Name: _pwd_view_init_warning_icon
 * Description:
 * Inputs:  -
 * Outputs: -
 * Returns: -
 ----------------------------------------------------------------------------*/
static INT32 _pwd_view_init_warning_icon(HANDLE_T    h_parent,
                             HANDLE_T*   ph_widget)
{
    INT32                       i4_ret;
    GL_RECT_T                   t_rect;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE(&t_rect,
                     PWD_ICON_LEFT,
                     PWD_ICON_TOP,
                     PWD_ICON_WIDTH,
                     PWD_ICON_HEIGHT);

    i4_ret = c_wgl_create_widget (h_parent,
                                HT_WGL_WIDGET_ICON,
                                WGL_CONTENT_ICON_DEF,
                                WGL_BORDER_NULL,
                                &t_rect,
                                NULL,
                                255,
                                (VOID *)WGL_STL_GL_NO_BK,
                                NULL,
                                ph_widget);
    NAVR_CHK_FAIL(i4_ret);

    /* set icon image buffer */

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_pwd_dlg_warning_icon;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_pwd_dlg_warning_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_pwd_dlg_warning_icon;

    i4_ret = c_wgl_do_cmd (*ph_widget,
                                WGL_CMD_GL_SET_IMAGE,
                                WGL_PACK(WGL_IMG_FG),
                                WGL_PACK(&t_img_info));
    NAVR_CHK_FAIL(i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd (*ph_widget,
                                WGL_CMD_ICON_SET_ALIGN,
                                (VOID*)WGL_AS_CENTER_CENTER,
                                NULL);
    NAVR_CHK_FAIL(i4_ret);

    /* make icon invisible */
    i4_ret = c_wgl_set_visibility (*ph_widget, WGL_SW_HIDE);
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}
#endif

/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_show_title
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_show_title(VOID)
{
	INT32             i4_ret = 0;
	UTF16_T*          w2s_str = NULL;
	TV_WIN_ID_T       e_tv_win_id;
	LOCKED_STATUS_T   e_locked_status;
	/* Get Focus Win */
	nav_get_focus_id(&e_tv_win_id);
	/* Get Locked status / signal status */
	e_locked_status = nav_get_locked_status(e_tv_win_id);

	if (e_locked_status == LOCKED_STATUS_CHANNEL_LOCKED)
	{
		w2s_str = MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_MSG_LOCKED_CH);
	}
	else
	{
		w2s_str = MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_MSG_LOCKED_PROG);
	}
	i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_title,
		WGL_CMD_TEXT_SET_TEXT,
		WGL_PACK(w2s_str),
		WGL_PACK(0xFF));
	NAVR_CHK_FAIL(i4_ret);

	i4_ret = c_wgl_set_visibility(pt_g_pwd_data->h_pwd_title,
		WGL_SW_RECURSIVE);

	return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_set_info_txt
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_set_info_txt(UTF16_T* w2s_str)
{
    INT32   i4_ret = 0;

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_txt_alarm,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(w2s_str),
                          WGL_PACK(0xFF));
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _backup_input
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_backup_input(UINT8 ui1_input)
{
    INT32   i4_ret;
    CHAR    s_buf[2] = {0};
    UTF16_T w2s_str_temp[2] = {0};

    if(ui1_input > 9)
    {
        return NAVR_INV_ARG;
    }

    i4_ret = c_sprintf(s_buf, "%d",  ui1_input);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_uc_ps_to_w2s(s_buf, w2s_str_temp, 1);
    NAVR_CHK_FAIL(i4_ret);

    if(BUTTON_LAST_ENTRY > c_uc_w2s_strlen(w2s_g_str))
    {
        c_uc_w2s_strcat(w2s_g_str,w2s_str_temp);
    }
    else
    {
        return NAVR_FAIL;
    }
    ui1_loop = 0;
    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_init_crt_btn
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_init_currentt_btn(VOID)
{
    INT32   i4_ret = 0;
    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[e_current_button],
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(L" "),
                          WGL_PACK(c_uc_w2s_strlen (L" ")));
    NAVR_CHK_FAIL(i4_ret);
    return NAVR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_set_btn_null
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_set_btn_null(VOID)
{
    INT32   i4_ret = 0;
    UINT8    ui1_loop = 0;
    for(ui1_loop = 0; ui1_loop < BUTTON_LAST_ENTRY; ui1_loop++)
    {
        i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[ui1_loop],
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(L" "),
                          WGL_PACK(c_uc_w2s_strlen (L" ")));
        NAVR_CHK_FAIL(i4_ret);
    }

    i4_ret = c_wgl_repaint(pt_g_pwd_data->h_parent_frm, NULL, TRUE);
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_pwd_button_input
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_pwd_button_input(UINT32 ui4_keycode)
{
    INT32       i4_ret = 0;
    UTF16_T     w2s_get_pin[4] = {0};
    UTF16_T     w2s_set_pin[4] = {0};
    CHAR        s_set_buf[4] = {0};

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[e_current_button],
                          WGL_CMD_BTN_GET_TEXT,
                          WGL_PACK(w2s_get_pin),
                          WGL_PACK(1));
    NAVR_CHK_FAIL(i4_ret);
    for(ui1_loop = 0; ui1_loop < 10; ui1_loop++)
    {
        i4_ret = c_sprintf(s_set_buf, "%d",  ui1_loop);
        NAVR_CHK_FAIL(i4_ret);

        i4_ret = c_uc_ps_to_w2s(s_set_buf, w2s_set_pin, 1);
        NAVR_CHK_FAIL(i4_ret);

        if(c_uc_w2s_strcmp(w2s_get_pin,w2s_set_pin) == 0)
        {
            break;
        }
    }

    if(BTN_VOL_UP == ui4_keycode)
    {
        if(ui1_loop >= 9)
        {
            ui1_loop = 0;
        }
        else
        {
            ui1_loop++;
        }
    }
    else if(BTN_VOL_DOWN == ui4_keycode)
    {
        if(ui1_loop <= 0)
        {
            ui1_loop = 9;
        }
        else
        {
            ui1_loop--;
        }
    }

    i4_ret = c_sprintf(s_set_buf, "%d",  ui1_loop);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_uc_ps_to_w2s(s_set_buf, w2s_set_pin, 1);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[e_current_button],
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(w2s_set_pin),
                          WGL_PACK(c_uc_w2s_strlen(w2s_set_pin)));
    NAVR_CHK_FAIL(i4_ret);

    c_wgl_repaint(pt_g_pwd_data->h_parent_frm,NULL,TRUE);
    DBG_LOG_PRINT(("[PWD_DLG]ui1_loop=[%d], in line=[%d]", ui1_loop, __LINE__));

    return NAVR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_switch_button_state
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_switch_button_state(HANDLE_T h_widget,BOOL b_have_pwd)
{
    INT32               i4_ret = -1;
    WGL_IMG_INFO_T      t_img_info;

    c_memset(&t_img_info, 0x0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;

    if(b_have_pwd)
    {
        t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_system_pin_box_pushed_v2;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_system_pin_box_pushed_v2; 
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_system_pin_box_pushed_v2;
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_disable   = h_g_menu_system_pin_box_inactive_v2;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_menu_system_pin_box_active_v2;  
        t_img_info.u_img_data.t_standard.t_highlight = h_g_menu_system_pin_box_active_v2;
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;


}


/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_switch_button_state
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_switch_cancel_background(BOOL b_cancel_state)
{
    INT32               i4_ret = -1;
    WGL_IMG_INFO_T      t_img_info;
    HANDLE_T h_widget = pt_g_pwd_data->h_cancel_icon;

    c_memset(&t_img_info, 0x0, sizeof(WGL_IMG_INFO_T));
    t_img_info.e_type = WGL_IMG_SET_STANDARD;

    if(b_cancel_state)
    {
        t_img_info.u_img_data.t_standard.t_disable   = h_g_pwd_dlg_cancel_focus_img;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_pwd_dlg_cancel_focus_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_pwd_dlg_cancel_focus_img;
    }
    else
    {
        t_img_info.u_img_data.t_standard.t_disable   = h_g_pwd_dlg_cancel_inactive_img;
        t_img_info.u_img_data.t_standard.t_enable    = h_g_pwd_dlg_cancel_inactive_img;
        t_img_info.u_img_data.t_standard.t_highlight = h_g_pwd_dlg_cancel_inactive_img;
    }

    i4_ret = c_wgl_do_cmd(h_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;


}


#if 0 /* can't deal with in cast tv spec */
/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_pwd_btn_repaint
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_pwd_btn_repaint(BOOL b_is_repaint_all,HANDLE_T h_first_widget, HANDLE_T h_last_widget)
{
    INT32  i4_ret = -1;
    GL_RECT_T   t_rect_1;
    GL_RECT_T   t_rect_2;
    GL_RECT_T   t_rect_union;
    GL_RECT_T*  pt_rect = NULL;

    if(b_is_repaint_all == FALSE)
    {
        i4_ret = c_wgl_get_coords(h_first_widget,
                         WGL_COORDS_PARENT,
                         &t_rect_1);
        NAVR_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_get_coords(h_last_widget,
                         WGL_COORDS_PARENT,
                         &t_rect_2);
        NAVR_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_rect_union(&t_rect_union, &t_rect_1, &t_rect_2);
        NAVR_CHK_FAIL(i4_ret);

        pt_rect = &t_rect_union;
    }

    i4_ret = c_wgl_repaint(pt_g_pwd_data->h_parent_frm,pt_rect,TRUE);

    return i4_ret;
}
#endif


static INT32 pwd_dlg_view_get_rcu_input(UINT32 ui4_keycode)
{
    INT32       i4_ret         =  0;
    UTF16_T     w2s_get_pin[4] = {0};
    UTF16_T     w2s_set_pin[4] = {0};
    CHAR        s_set_buf[4]   = {0};

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[e_current_button],
                          WGL_CMD_BTN_GET_TEXT,
                          WGL_PACK(w2s_get_pin),
                          WGL_PACK(1));
    NAVR_CHK_FAIL(i4_ret);


    switch(ui4_keycode)
    {
        case BTN_DIGIT_0:
            ui1_loop = 0;
            break;
        case BTN_DIGIT_1:
            ui1_loop = 1;
            break;
        case BTN_DIGIT_2:
            ui1_loop = 2;
            break;
        case BTN_DIGIT_3:
            ui1_loop = 3;
            break;
        case BTN_DIGIT_4:
            ui1_loop = 4;
            break;
        case BTN_DIGIT_5:
            ui1_loop = 5;
            break;
        case BTN_DIGIT_6:
            ui1_loop = 6;
            break;
        case BTN_DIGIT_7:
            ui1_loop = 7;
            break;
        case BTN_DIGIT_8:
            ui1_loop = 8;
            break;
        case BTN_DIGIT_9:
            ui1_loop = 9;
            break;

        default:
            break;
    }

    i4_ret = c_sprintf(s_set_buf, "%d",  ui1_loop);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_uc_ps_to_w2s(s_set_buf, w2s_set_pin, 1);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[e_current_button],
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(w2s_set_pin),
                          WGL_PACK(c_uc_w2s_strlen(w2s_set_pin)));
    NAVR_CHK_FAIL(i4_ret);

    c_wgl_repaint(pt_g_pwd_data->h_parent_frm,NULL,TRUE);

    DBG_LOG_PRINT(("[PWD_DLG]ui1_loop=[%d], in line=[%d]", ui1_loop, __LINE__));

    return NAVR_OK;
}

static INT32 _page_reset(VOID)
{
    INT32   i4_ret = MENUR_OK;
    UINT8   ui1_i;


    e_current_button = BUTTON_1;

    for (ui1_i = 0; ui1_i < BUTTON_LAST_ENTRY; ui1_i++)
    {
        _pwd_dlg_view_switch_button_state(pt_g_pwd_data->h_pwd_button[ui1_i],FALSE);

        i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[ui1_i],
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(L" "),
                          WGL_PACK(c_uc_w2s_strlen (L" ")));
        NAVR_CHK_FAIL(i4_ret);


        i4_ret = c_wgl_float(pt_g_pwd_data->h_pwd_button[ui1_i], TRUE, WGL_NO_AUTO_REPAINT);
        NAVR_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[ui1_i],
                                WGL_CMD_BTN_SET_PUSHED,
                                WGL_PACK(FALSE),
                                NULL);
        NAVR_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_float(pt_g_pwd_data->h_pwd_button[ui1_i], TRUE, WGL_NO_AUTO_REPAINT);
        NAVR_CHK_FAIL(i4_ret);

        if(ui1_i == BUTTON_1)
        {
            c_wgl_enable(pt_g_pwd_data->h_pwd_button[ui1_i],TRUE);
        }
        else
        {
            c_wgl_enable(pt_g_pwd_data->h_pwd_button[ui1_i],FALSE);
        }

        c_wgl_repaint(pt_g_pwd_data->h_pwd_button[ui1_i],NULL,TRUE);
    }

//    i4_ret = c_wgl_set_focus(pt_g_pwd_data->h_pwd_button[BUTTON_1], WGL_NO_AUTO_REPAINT);
//    NAVR_CHK_FAIL(i4_ret);

    a_digit_pad_focus(h_digit_handle);

    _pwd_dlg_view_show_warning_msgs(1);

    c_wgl_repaint(pt_g_pwd_data->h_parent_frm,NULL,TRUE);

    return i4_ret;
}

extern VOID a_set_pwd_to_unlock_state(UINT8 ui2_state);

INT32 jump_to_next_box(BOOL b_pushed)
{
    BOOL   b_pass = FALSE;
    UINT8  btn_index;
    if(b_pushed)
    {
        _pwd_dlg_view_set_btn_null();

        if(b_is_warning_init)
        {
            _pwd_dlg_view_warning_deinit();
            pwd_dlg_stop_timer();
            _pwd_dlg_view_show_box();
            pwd_dlg_view_load_msgs(nav_get_mlm_lang_id());

            return NAVR_OK;
        }

        if (e_current_button == BUTTON_1)
        {
            _pwd_dlg_view_show_warning_msgs(0);
        }

        if((e_current_button != BUTTON_4) && (e_current_button != -1))
        {
            _pwd_dlg_view_backup_input(ui1_loop);
            _pwd_dlg_view_switch_button_state(pt_g_pwd_data->h_pwd_button[e_current_button],TRUE);
            e_current_button++;
            _pwd_dlg_view_init_currentt_btn();
          //  c_wgl_repaint(pt_g_pwd_data->h_parent_frm,NULL,TRUE);
        }
        else if(e_current_button == BUTTON_4)
        {
            _pwd_dlg_view_switch_button_state(pt_g_pwd_data->h_pwd_button[e_current_button],TRUE);
           // c_wgl_repaint(pt_g_pwd_data->h_parent_frm,NULL,TRUE);
            _pwd_dlg_view_backup_input(ui1_loop);
            b_pass = pwd_dlg_box_chk_pwd(w2s_g_str);

            /* if valid show parental settting frame */
            if (b_pass)
            {
                a_set_pwd_to_unlock_state(TRUE);
                nav_hide_component(NAV_COMP_ID_PWD_DLG);
                nav_return_activation(NAV_COMP_ID_PWD_DLG);
            }
            else
            {
                _page_reset();
                c_memset(w2s_g_str,0x0,sizeof(w2s_g_str));
                ui1_loop = 0;
                e_current_button = BUTTON_1;
            }
            pt_g_pwd_data->b_is_pin_box = FALSE;
        }
        else if(e_current_button == -1)
        {
        _pwd_dlg_view_show_box();
        }

    }
    else
    {
        pwd_dlg_reset_timer();
        e_current_button --;
        w2s_g_str[e_current_button] = 0;
       _pwd_dlg_view_switch_button_state(pt_g_pwd_data->h_pwd_button[e_current_button],FALSE);
    }

    for(btn_index = BUTTON_1;btn_index<BUTTON_LAST_ENTRY;btn_index++)
    {
        if(btn_index == e_current_button)
        {
            c_wgl_enable(pt_g_pwd_data->h_pwd_button[btn_index],TRUE);
        }
        else
        {
            c_wgl_enable(pt_g_pwd_data->h_pwd_button[btn_index],FALSE);
        }
    }
    c_wgl_repaint(pt_g_pwd_data->h_parent_frm,NULL,TRUE);

    return NAVR_OK;
}



/*----------------------------------------------------------------------------
 * Name: _pwd_dlg_view_frame_proc_fct
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_frame_proc_fct(
                    HANDLE_T            h_widget,
                    UINT32              ui4_msg,
                    VOID*               param1,
                    VOID*               param2
                    )
{
    UINT32 ui4_keycode      = (UINT32)param1;
    static HANDLE_T h_focus = NULL_HANDLE;
    INT32  i4_ret;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
            if(pwd_dlg_get_delay_return_activation_status())
            {
                break;
            }
            switch(ui4_keycode)
            {
            case BTN_KB_BACKSPACE:
            case BTN_CURSOR_LEFT:
            #if 1   /* can't deal with in cast tv  spec */
                if(e_current_button != BUTTON_1)
                {
                    pwd_dlg_reset_timer();
                    e_current_button --;
                    w2s_g_str[e_current_button] = 0;
                    _pwd_dlg_view_switch_button_state(pt_g_pwd_data->h_pwd_button[e_current_button],FALSE);
                    c_wgl_set_focus(pt_g_pwd_data->h_pwd_button[e_current_button],WGL_NO_AUTO_REPAINT);
                    //_pwd_dlg_view_pwd_btn_repaint(FALSE,pt_g_pwd_data->h_pwd_button[e_current_button],h_widget);
					c_wgl_repaint(pt_g_pwd_data->h_parent_frm,NULL,TRUE);
                }
                else
                {
                    //menu_nav_back();
                }
            #endif
                return NAVR_OK;
            case BTN_VOL_UP:
            case BTN_VOL_DOWN:
            {
                if(e_current_button == -1)
                {
                    nav_rcu_key_handler(ui4_keycode);
                    break;
                }
                if(b_is_warning_init)
                {
                    _pwd_dlg_view_warning_deinit();
                }
                _pwd_dlg_view_pwd_button_input(ui4_keycode);
                break;
            }

            case BTN_DIGIT_0:
            case BTN_DIGIT_1:
            case BTN_DIGIT_2:
            case BTN_DIGIT_3:
            case BTN_DIGIT_4:
            case BTN_DIGIT_5:
            case BTN_DIGIT_6:
            case BTN_DIGIT_7:
            case BTN_DIGIT_8:
            case BTN_DIGIT_9:
            {
                if(e_current_button == -1)
                {
                    nav_rcu_key_handler(ui4_keycode);
                    break;
                }
                if(b_is_warning_init)
                {
                    _pwd_dlg_view_warning_deinit();
                }
                pwd_dlg_view_get_rcu_input(ui4_keycode);
                jump_to_next_box(TRUE);

                break;
            }

            case BTN_SELECT:
            case BTN_PAUSE:
            case BTN_PLAY:
            {
               jump_to_next_box(TRUE);
               return NAVR_OK;
            }
            case BTN_RETURN:
                //menu_nav_back();
               return NAVR_OK;
            case BTN_CURSOR_DOWN:
                a_digit_pad_focus(h_digit_handle);
                break;
            case BTN_CURSOR_UP:
                c_wgl_get_focus(&h_focus);
                if (h_focus == h_digit_handle)
                {
                    c_wgl_set_focus(pt_g_pwd_data->h_pwd_button[e_current_button],WGL_NO_AUTO_REPAINT);
                }
                break;
            default :
                nav_rcu_key_handler(ui4_keycode);
                break;
            }
        }
    default:
        break;
    }

    i4_ret = c_wgl_default_msg_proc(h_widget, ui4_msg, param1, param2);
    return i4_ret;
}

BOOL _pwd_dlg_view_digit_pad_fct(UINT32 ui4_msg,
                                          VOID* pv_param1,
                                          VOID* pv_param2)
{
    UINT32 ui4_keycode      = (UINT32)pv_param1;

    switch (ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        {
             switch(ui4_keycode)
            {
                case BTN_DIGIT_0:
                case BTN_DIGIT_1:
                case BTN_DIGIT_2:
                case BTN_DIGIT_3:
                case BTN_DIGIT_4:
                case BTN_DIGIT_5:
                case BTN_DIGIT_6:
                case BTN_DIGIT_7:
                case BTN_DIGIT_8:
                case BTN_DIGIT_9:
                {
DBG_LOG_PRINT((" [%d] e_current_button: %X \n", __LINE__, e_current_button));
DBG_LOG_PRINT((" [%d] b_is_warning_init: %X \n", __LINE__, b_is_warning_init));

                    if(e_current_button == -1)
                    {
                        nav_rcu_key_handler(ui4_keycode);
                        break;
                    }
                    if(b_is_warning_init)
                    {
                        _pwd_dlg_view_warning_deinit();
                    }
                    pwd_dlg_view_get_rcu_input(ui4_keycode);
                    jump_to_next_box(TRUE);

                    break;
                }
                case BTN_SELECT:
                case BTN_CURSOR_LEFT:
                case BTN_CURSOR_RIGHT:
                case BTN_CURSOR_DOWN:
                case BTN_CURSOR_UP:
                    break;
                default :
                    nav_rcu_key_handler(ui4_keycode);
                    break;
            }
        }
    default:
        break;
    }

    return NAVR_OK ;

}

//show pwd input box and input msg
static INT32 _pwd_dlg_view_show_box(VOID)
{
    INT32    i4_ret;
    UINT8    ui1_loop_idx = 0;
    i4_ret = c_wgl_set_visibility(pt_g_pwd_data->h_parent_frm, WGL_SW_RECURSIVE);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_g_pwd_data->h_image_no_match, WGL_SW_HIDE);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret =  _pwd_dlg_view_show_title();
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = a_digit_pad_show(h_digit_handle);
    NAVR_CHK_FAIL(i4_ret);

    for(ui1_loop_idx = BUTTON_1; ui1_loop_idx < BUTTON_LAST_ENTRY; ui1_loop_idx++)
    {
        _pwd_dlg_view_switch_button_state(pt_g_pwd_data->h_pwd_button[ui1_loop_idx],FALSE);
        i4_ret = c_wgl_do_cmd(pt_g_pwd_data->h_pwd_button[ui1_loop_idx],
                          WGL_CMD_BTN_SET_TEXT,
                          WGL_PACK(L" "),
                          WGL_PACK(c_uc_w2s_strlen (L" ")));
        NAVR_CHK_FAIL(i4_ret);

        if(ui1_loop_idx == BUTTON_1)
        {
            c_wgl_enable(pt_g_pwd_data->h_pwd_button[ui1_loop_idx],TRUE);
        }
        else
        {
            c_wgl_enable(pt_g_pwd_data->h_pwd_button[ui1_loop_idx],FALSE);
        }
    }
    i4_ret = _pwd_dlg_view_set_info_txt(pw2s_g_pwd_alarm);
    NAVR_CHK_FAIL(i4_ret);

    c_memset(w2s_g_str,0x0,sizeof(w2s_g_str));
    ui1_loop = 0;
    pt_g_pwd_data->b_is_pin_box = TRUE;

    a_digit_pad_focus(h_digit_handle);

    _pwd_dlg_view_show_cancel_text();
    _pwd_dlg_view_show_help_tips();

    e_current_button = BUTTON_1;
    /* could not show the first "0" in password dialog box. */
    /* DTV00759467 */
    //_pwd_dlg_view_init_currentt_btn();

    i4_ret = c_wgl_repaint(pt_g_pwd_data->h_parent_frm, NULL, TRUE);
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}

static INT32 _pwd_dlg_view_locked_message_show(VOID)
{
    INT32    i4_ret = 0;
    TV_WIN_ID_T       e_tv_win_id;
    LOCKED_STATUS_T   e_locked_status;
    UTF16_T w2s_str[128] = {0};

    /* Get Focus Win */
    nav_get_focus_id(&e_tv_win_id);

    /* Get Locked status / signal status */
    e_locked_status = nav_get_locked_status(e_tv_win_id);

    if (e_locked_status == LOCKED_STATUS_CHANNEL_LOCKED)
    {
        pw2s_g_pwd_title = MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_MSG_LOCKED_CH);
    }
    else
    {
        pw2s_g_pwd_title = MLM_SETTINGS_TEXT(nav_get_mlm_lang_id(), MLM_SETTINGS_KEY_MSG_LOCKED_PROG);
    }

    i4_ret = c_wgl_do_cmd(pt_g_pwd_warning->h_title_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_g_pwd_title),
                          (VOID*)c_uc_w2s_strlen(pw2s_g_pwd_title));
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_g_pwd_warning->h_parent_frm, NULL, TRUE);
    NAVR_CHK_FAIL(i4_ret);

    pw2s_g_pwd_warning = MLM_NAV_TEXT(nav_get_mlm_lang_id(),MLM_NAV_KEY_NAV_CHANNEL_LOCK);
    //a_app_tts_play(pw2s_g_pwd_warning, c_uc_w2s_strlen(pw2s_g_pwd_warning));
    c_uc_w2s_strcat(w2s_str, pw2s_g_pwd_title);
    c_uc_w2s_strcat(w2s_str, L". ") ;
    c_uc_w2s_strcat(w2s_str, MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_57));
    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));

    return NAVR_OK;
}

#if 0
static VOID _pwd_dlg_view_warning_do_timer(VOID* pv_data1,
                                VOID* pv_data2,
                                VOID* pv_data3)
{
    _pwd_dlg_view_locked_message_show();
}

static VOID _pwd_dlg_view_warning_timer_nfy(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    nav_request_context_switch(_pwd_dlg_view_warning_do_timer,pv_tag, NULL,NULL);
}

static INT32 _pwd_dlg_view_warning_show(VOID)
{
    INT32    i4_ret;
    UTF16_T w2s_str[128] = {0};

    i4_ret = c_wgl_set_visibility(pt_g_pwd_warning->h_parent_frm,
                                  WGL_SW_RECURSIVE);
    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    pw2s_g_pwd_warning = MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_57);

    i4_ret = c_wgl_do_cmd(pt_g_pwd_warning->h_txt_alarm,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_g_pwd_warning),
                          WGL_PACK((VOID*)c_uc_w2s_strlen(pw2s_g_pwd_warning)));
    NAVR_CHK_FAIL(i4_ret);

    pw2s_g_pwd_title = MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_56);
    i4_ret = c_wgl_do_cmd(pt_g_pwd_warning->h_title_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_g_pwd_title),
                          (VOID*)c_uc_w2s_strlen(pw2s_g_pwd_title));
    NAVR_CHK_FAIL(i4_ret);


    /* make icon invisible */
    i4_ret = c_wgl_set_visibility (pt_g_pwd_warning->h_pwd_icon, WGL_SW_NORMAL);
     NAVR_CHK_FAIL(i4_ret);


    i4_ret = c_wgl_repaint(pt_g_pwd_warning->h_parent_frm, NULL, TRUE);
    NAVR_CHK_FAIL(i4_ret);

    pw2s_g_pwd_warning = MLM_NAV_TEXT(nav_get_mlm_lang_id(), MLM_NAV_KEY_NAV_INCORRENT_PIN);
    //a_app_tts_play(pw2s_g_pwd_warning, c_uc_w2s_strlen(pw2s_g_pwd_warning));
    c_uc_w2s_strcat(w2s_str, pw2s_g_pwd_title);
    c_uc_w2s_strcat(w2s_str, MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_57));
    a_app_tts_play(w2s_str, c_uc_w2s_strlen(w2s_str));

    i4_ret = c_timer_start(
                    pt_g_pwd_warning->h_hide_timer,
                    PWD_DLG_HIDE_TIMER_DELAY,
                    X_TIMER_FLAG_ONCE,
                    _pwd_dlg_view_warning_timer_nfy,
                    NULL
                    );
    NAVR_CHK_FAIL(i4_ret);

    return NAVR_OK;
}
#endif

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_view_warning_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_warning_deinit(VOID)
{
    INT32       i4_ret = 0;

    return NAVR_OK;
}

#if 0
/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_view_warning_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_warning_init(VOID)
{
    INT32       i4_ret = NAVR_OK;
    if( b_is_warning_init == TRUE){
        return i4_ret;
    }
    b_is_warning_init = TRUE;

    i4_ret = nav_img_create_pwd_dlg_warning_icon(&h_g_pwd_dlg_warning_icon);
    NAVR_CHK_FAIL(i4_ret);

    /* new warning view form */
    pt_g_pwd_warning = c_mem_alloc(sizeof(PWD_DLG_VIEW_T));
    if( pt_g_pwd_warning == NULL)
    {
        i4_ret = NAVR_OUT_OF_MEM;
        return i4_ret;
    }
    c_memset(pt_g_pwd_warning, 0, sizeof(PWD_DLG_VIEW_T));

    /* Create Clear Memory password dialog frame. */
    i4_ret = _pwd_dlg_view_init_parent_frame(nav_get_ui_canvas(), &pt_g_pwd_warning->h_parent_frm);
    NAVR_CHK_FAIL(i4_ret);

    /*init txt alarm*/
    i4_ret = _pwd_dlg_view_init_txt_alarm(pt_g_pwd_warning->h_parent_frm, &pt_g_pwd_warning->h_txt_alarm);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = _pwd_dlg_view_init_title_txt(pt_g_pwd_warning->h_parent_frm, &pt_g_pwd_warning->h_title_txt);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = _pwd_view_init_warning_icon(pt_g_pwd_warning->h_parent_frm, &pt_g_pwd_warning->h_pwd_icon);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_g_pwd_warning->h_parent_frm,WGL_SW_RECURSIVE);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_g_pwd_warning->h_parent_frm, WGL_SW_HIDE);
    NAVR_CHK_FAIL(i4_ret);

    /* destory allocated data when some error on creating process*/
    if(i4_ret != NAVR_OK)
    {
        _pwd_dlg_view_warning_deinit();
    }

    i4_ret = c_timer_create(&(pt_g_pwd_warning->h_hide_timer));
    NAVR_CHK_FAIL(i4_ret);

    return i4_ret;
}
#endif

/*-----------------------------------------------------------------------------
 * puiblic methods implementations
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 * Name
 *      pwd_dlg_view_load_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
VOID pwd_dlg_view_load_msgs(
                    UINT8                       ui1_lang_id
                    )
{
    pw2s_g_pwd_alarm = MLM_WARNINGS_TEXT(ui1_lang_id,MLM_WARNINGS_KEY_WARNING_73);

	a_app_tts_play(pw2s_g_pwd_alarm, c_uc_w2s_strlen(pw2s_g_pwd_alarm));
}

/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_view_show_warning_msgs
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_show_warning_msgs(UINT8  ui1_change_state)
{
    INT32  i4_ret;
    static UTF16_T*         pw2s_warning_str       = NULL;

    if (ui1_change_state == 1)
    {
        i4_ret = c_wgl_set_visibility(pt_g_pwd_data->h_image_no_match,WGL_SW_RECURSIVE);
    	NAVR_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_repaint(pt_g_pwd_data->h_image_no_match, NULL, TRUE);
    	NAVR_CHK_FAIL(i4_ret);

        pw2s_warning_str = MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_56);
    	a_app_tts_play(pw2s_warning_str, c_uc_w2s_strlen(pw2s_warning_str));

        _pwd_dlg_view_set_info_txt(pw2s_warning_str);

       /* make icon invisible */
       i4_ret = c_wgl_set_visibility (pt_g_pwd_data->h_txt_alarm, WGL_SW_RECURSIVE);
        NAVR_CHK_FAIL(i4_ret);
    }
    else
    {
         c_wgl_set_visibility(pt_g_pwd_data->h_image_no_match,WGL_SW_HIDE);

         i4_ret = c_wgl_repaint(pt_g_pwd_data->h_image_no_match, NULL, TRUE);
         NAVR_CHK_FAIL(i4_ret);

         pw2s_warning_str = MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_73);
         a_app_tts_play(pw2s_warning_str, c_uc_w2s_strlen(pw2s_warning_str));

         _pwd_dlg_view_set_info_txt(pw2s_warning_str);

        /* make icon invisible */
        i4_ret = c_wgl_set_visibility (pt_g_pwd_data->h_txt_alarm, WGL_SW_RECURSIVE);
         NAVR_CHK_FAIL(i4_ret);

    }
    return NAVR_OK;

}

/*-----------------------------------------------------------------------------
 * Name
 *      pwd_dlg_view_deinit
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pwd_dlg_view_deinit(VOID)
{
    PWD_DLG_VIEW_T* pt_this = pt_g_pwd_data;

    if(pt_this != NULL)
    {
        c_wgl_destroy_widget_ex (pt_this->h_parent_frm, FALSE);
        c_mem_free(pt_g_pwd_data);
    }
//    _pwd_dlg_view_warning_deinit();

    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      pwd_dlg_view_init
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pwd_dlg_view_init(
                    HANDLE_T                    h_canvas,
                    INT32                       i4_frame_x_offset,
                    INT32                       i4_frame_y_offset,
                    APP_COLOR_TYPE_T            e_color_type
                    )
{
    INT32       i4_ret;
    UINT8       ui1_button_idx = 0;

    i4_ret = nav_img_create_pwd_dlg_input_pin(&h_g_pwd_dlg_inp_img);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = nav_img_create_pwd_dlg_bk_white_line(&h_g_pwd_dlg_bk_img);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = nav_img_create_pwd_dlg_select_pin_box(&h_g_pwd_dlg_sel_img);
    NAVR_CHK_FAIL(i4_ret);
    i4_ret = nav_img_create_pwd_dlg_no_match_pic(&h_g_pin_no_match_bkg);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = nav_img_create_pwd_dlg_down_pic(&h_g_pwd_dlg_down_img);
    NAVR_CHK_FAIL(i4_ret);
    i4_ret = nav_img_create_pwd_dlg_cancel_focus_pic(&h_g_pwd_dlg_cancel_focus_img);
    NAVR_CHK_FAIL(i4_ret);
    i4_ret = nav_img_create_pwd_dlg_cancel_inactive_pic(&h_g_pwd_dlg_cancel_inactive_img);
    NAVR_CHK_FAIL(i4_ret);
    i4_ret = nav_img_create_pwd_dlg_up_pic(&h_g_pwd_dlg_up_img);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = wdk_digit_pad_init_image();
    NAVR_CHK_FAIL(i4_ret);

    do
    {
        /* new password form */
        pt_g_pwd_data = c_mem_alloc(sizeof(PWD_DLG_VIEW_T));
        if( pt_g_pwd_data  == NULL)
        {
            i4_ret = NAVR_OUT_OF_MEM;
            break;
        }
        c_memset(pt_g_pwd_data, 0, sizeof(PWD_DLG_VIEW_T));

        /* Create Clear Memory password dialog frame. */
        i4_ret = _pwd_dlg_view_init_parent_frame(nav_get_ui_canvas(), &pt_g_pwd_data->h_parent_frm);
        if(i4_ret != NAVR_OK)
        {
            break;
        }
         /*init title*/
         i4_ret = _pwd_dlg_view_init_title(pt_g_pwd_data->h_parent_frm, &pt_g_pwd_data->h_pwd_title);
         if(i4_ret != NAVR_OK)
         {
             break;
         }

         /* no match image */
         i4_ret =  _input_no_match_image_create(pt_g_pwd_data->h_parent_frm,&pt_g_pwd_data->h_image_no_match);
         if(i4_ret != NAVR_OK)
         {
             break;
         }

        /*init txt alarm*/
        i4_ret = _pwd_dlg_view_init_txt_alarm(pt_g_pwd_data->h_parent_frm, &pt_g_pwd_data->h_txt_alarm);
        if(i4_ret != NAVR_OK)
        {
            break;
        }

        for(ui1_button_idx = 0; ui1_button_idx < BUTTON_LAST_ENTRY; ui1_button_idx++)
        {
            i4_ret = _pwd_dlg_view_init_pwd_button(pt_g_pwd_data->h_parent_frm, &pt_g_pwd_data->h_pwd_button[ui1_button_idx],ui1_button_idx);
            if(i4_ret != NAVR_OK)
            {
                break;
            }
        }
        if(i4_ret != NAVR_OK)
        {
            break;
        }
        i4_ret = _digit_pad_create(pt_g_pwd_data->h_parent_frm,NULL);
		if(i4_ret != NAVR_OK)
        {
            break;
        }
        i4_ret = _pwd_dlg_view_init_cancel_button(pt_g_pwd_data->h_parent_frm,&pt_g_pwd_data->h_cancel_icon);
        if(i4_ret != NAVR_OK)
        {
            break;
        }
        i4_ret = _pwd_dlg_view_init_help_tips(pt_g_pwd_data->h_parent_frm,&pt_g_pwd_data->h_help_tips);
        if(i4_ret != NAVR_OK)
        {
            break;
        }
        i4_ret = c_wgl_set_visibility(pt_g_pwd_data->h_parent_frm,
                                  WGL_SW_RECURSIVE);
        if(i4_ret != WGLR_OK)
        {
            i4_ret = NAVR_FAIL;
            break;
        }

        i4_ret = c_wgl_set_visibility(pt_g_pwd_data->h_parent_frm, WGL_SW_HIDE);
        if(i4_ret != WGLR_OK)
        {
           i4_ret = NAVR_FAIL;
           break;
        }
    }while (0);

    /* destory allocated data when some error on creating process*/
    if(i4_ret != NAVR_OK)
    {
        pwd_dlg_view_deinit();
    }

    return i4_ret;
}
/*-----------------------------------------------------------------------------
 * Name
 *      pwd_dlg_view_hide_all
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pwd_dlg_view_hide_all(VOID)
{
    INT32 i4_ret;

    i4_ret = c_wgl_show (pt_g_pwd_data->h_parent_frm, WGL_SW_HIDE_RECURSIVE);
    if(i4_ret != WGLR_OK)
    {
        DBG_LOG_PRINT(("[PWD DLG]error c_wgl_show i4_ret=[%d], line=[%d]", i4_ret, __LINE__));
        return NAVR_FAIL;
    }
    pt_g_pwd_data->b_is_pin_box = FALSE;

    b_cancel_state = TRUE;

    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      _pwd_dlg_view_show_lock_msg
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
static INT32 _pwd_dlg_view_show_lock_msg(VOID)
{
    INT32 i4_ret = WGLR_OK;
    /* init pincode dialog */
    i4_ret = c_wgl_set_focus(pt_g_pwd_data->h_pwd_button[BUTTON_1],WGL_NO_AUTO_REPAINT );
    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }
    e_current_button = -1;

    i4_ret = c_wgl_repaint(pt_g_pwd_data->h_parent_frm, NULL, TRUE);
    NAVR_CHK_FAIL(i4_ret);

#if  0

    /* init warning dialog */
    _pwd_dlg_view_warning_init();

    i4_ret = c_wgl_set_visibility(pt_g_pwd_warning->h_parent_frm,
                                  WGL_SW_RECURSIVE);
    if(i4_ret != WGLR_OK)
    {
        return NAVR_FAIL;
    }

    pw2s_g_pwd_warning = MLM_WARNINGS_TEXT(nav_get_mlm_lang_id(), MLM_WARNINGS_KEY_WARNING_57);

    i4_ret = c_wgl_do_cmd(pt_g_pwd_warning->h_txt_alarm,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK(pw2s_g_pwd_warning),
                          WGL_PACK((VOID*)c_uc_w2s_strlen(pw2s_g_pwd_warning)));
    NAVR_CHK_FAIL(i4_ret);

    /* make icon invisible */
    i4_ret = c_wgl_set_visibility (pt_g_pwd_warning->h_pwd_icon, WGL_SW_NORMAL);
    NAVR_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_repaint(pt_g_pwd_warning->h_parent_frm, NULL, TRUE);
    NAVR_CHK_FAIL(i4_ret);

    /* show locked msg dialog */
    _pwd_dlg_view_locked_message_show();
#endif
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      pwd_dlg_view_show_box
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pwd_dlg_view_show_box(VOID)
{
    _pwd_dlg_view_show_box();

    nav_set_component_visible(NAV_COMP_ID_PWD_DLG);
    nav_grab_activation(NAV_COMP_ID_PWD_DLG);
    return NAVR_OK;
}


/*-----------------------------------------------------------------------------
 * Name
 *      pwd_dlg_view_show_box
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
INT32 pwd_dlg_view_show_lock_msg_box(VOID)
{
   // _pwd_dlg_view_show_box();

    _pwd_dlg_view_show_lock_msg();

    nav_set_component_visible(NAV_COMP_ID_PWD_DLG);
    nav_grab_activation(NAV_COMP_ID_PWD_DLG);
    return NAVR_OK;
}

/*-----------------------------------------------------------------------------
 * Name
 *      pwd_dlg_view_is_show_box
 * Description
 * Input arguments
 * Output arguments
 * Returns
 *---------------------------------------------------------------------------*/
BOOL pwd_dlg_view_is_show_box(VOID)
{
    return pt_g_pwd_data->b_is_pin_box;
}
static VOID digit_pad_key_event_nfy(DIGIT_PAD_EVENT_TYPE event_type, VOID* pv_param)
{
    CHAR            digit_val ;
    UINT32          ui4_keycode;

    DBG_LOG_PRINT(("[PWD] [%s][%d] event_type = %d\n", __FUNCTION__, __LINE__, event_type));

    switch(event_type)
    {
        case DIGIT_PAD_DIGIT_KEY:
            digit_val = *((CHAR*)pv_param);
            if (digit_val == '0' || digit_val == '1' || digit_val == '2' ||
                digit_val == '3' || digit_val == '4' || digit_val == '5' ||
                digit_val == '6' || digit_val == '7' || digit_val == '8' ||
                digit_val == '9' )
            {
                a_digit_pad_focus_btn_ok(h_digit_handle);

                ui4_keycode = BTN_DIGIT_0 + (UINT32)(digit_val - '0');
                if(e_current_button == -1)
                {
                    nav_rcu_key_handler(ui4_keycode);
                    break;
                }
                if(b_is_warning_init)
                {
                    _pwd_dlg_view_warning_deinit();
                }
                pwd_dlg_view_get_rcu_input(ui4_keycode);
                jump_to_next_box(TRUE);

            }
            break;

        case DIGIT_PAD_DEL_KEY:
            if(e_current_button != BUTTON_1)
            {
                jump_to_next_box(FALSE);
              
            }
            break;

        case DIGIT_PAD_BUTTON_OK:
            break;
        case DIGIT_PAD_BUTTON_CANCEL:
            break;
        case DIGIT_PAD_NAV_BACK:
            break;
        case DIGIT_PAD_FOCUS_TO_ABOVE_WGL:
            menu_set_focus_on_backbar(TRUE);
            break;
        case DIGIT_PAD_FOCUS_TO_BELOW_WGL:
            b_cancel_state = TRUE;
            c_wgl_set_focus(pt_g_pwd_data->h_cancel_icon,WGL_NO_AUTO_REPAINT);
            _pwd_dlg_view_switch_cancel_background(TRUE);
            c_wgl_repaint(pt_g_pwd_data->h_parent_frm, NULL, TRUE);

            break;

        default:
            break;
    }
}


static INT32 _digit_pad_create(
    UINT32 ui4_page_id,
    VOID*  pv_create_data)
{
    INT32               i4_ret;

    // if you want to show digit pad as a dialog, please use the root frame of menu(menu_pm_get_root_frm) as parent frame of digit pad .
    // if you want to show digit pad in a menu page, please use the frame of the page(menu_page_get_cnt_frm) as parent frame of digit pad
//    i4_ret = menu_pm_get_root_frm(&h_cnt_frm);
//    MENU_LOG_ON_FAIL(i4_ret);

    DIGIT_PAD_CONFIG cfg;

    a_digit_pad_init_config(&cfg);
    cfg.parent_frame = ui4_page_id;
    cfg.position.ui4_left = PWD_BOX_LEFT + 10 +70;
    cfg.position.ui4_top = 360;

    cfg.digit_key_event_nfy = digit_pad_key_event_nfy;
    cfg.pf_rc_event_default_handle = (digit_rc_event_default_handle )_pwd_dlg_view_digit_pad_fct;
    i4_ret = a_digit_pad_create(cfg, &h_digit_handle);

    return NAVR_OK;
}

INT32 nav_update_pwd_digit_ui(VOID)
{
    if ( a_pwd_dlg_check_osd_on() == TRUE
       &&a_pwd_dlg_check_box_on() == TRUE )
    {
        /*update pwd dlg state for DTV03067979*/
        nav_grab_activation(NAV_COMP_ID_PWD_DLG);

        a_digit_pad_focus(h_digit_handle);
    }

    return NAVR_OK;
}

#endif

