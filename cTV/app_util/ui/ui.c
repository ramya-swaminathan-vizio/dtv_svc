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
 *                                                                             *
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
 * $RCSfile: ui.c,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_ATSC/6 $
 * $SWAuthor: $
 * $MD5HEX: ecd1c8c573bd47ddeb3a3eefdacc447b $
 *
 * Description:
 *
 *
 *
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/

#include "u_common.h"
#include "u_wgl_lb.h"
#include "u_wgl_bdr_common.h"
#include "u_wgl_lb_cnt_common.h"
#include "u_wgl_tools.h"
#include "u_wgl_bdr_uniform.h"
#include "u_wgl_bdr_timg.h"
#include "u_wgl_progress.h"
#include "u_irrc_btn_def.h"

#include "c_os.h"
#include "c_handle.h"
#include "c_fe.h"
#include "c_wgl.h"
#include "c_wgl_image.h"
#include "c_wgl_sets.h"
#include "c_uc_str.h"


#include "app_util/a_ui.h"
#include "app_util/a_tv.h"
#include "app_util/ui/_ui.h"
#include "app_util/ui/ui_anim.h"
#include "res/app_util/ui/ui_custom.h"           /* Custom Logic */
#include "res/app_util/ui/ui_img.h"              /* Default image */
#include "res/app_util/config/a_cfg_custom.h"
#include "res/app_util/tts/a_tts_custom.h"
#include "app_util/a_common.h"
#include "nav/nav_common.h"

#include "res/app_util/ui/menu_bt_headset_icon_image_8888.i"
#include "res/app_util/ui/menu_bt_headset_zoom_icon_image_8888.i"

#ifdef APP_CEC_MENU
#include "app_util/a_cec.h"
#include "nav/cec2/nav_cec.h"
#endif

#define TXT_HL_CLR_TXT           COLOR_white
#define TXT_HL_CLR_TXT_ban       COLOR_ban_white

const GL_COLOR_T COLOR_white =
{
    255, {255}, {255}, {255}
};

const GL_COLOR_T COLOR_ban_white =
{
    0, {0}, {0}, {0}
};

/* image definition file */
#if defined(APP_COLOR_MODE_PALLET)
    #include "res/app_util/ui/ui_img_p.i"
#else /* 444 mode */
    #if defined(APP_OSD_640x720)
        #include "res/app_util/ui/ui_img_640x720_16bits.i"
    #elif defined APP_IMG_960X540_4444
        #include "res/app_util/ui/ui_img_960x540_4444.i"
    #else /* 1280 x 720 */
        #if defined(APP_OSD_960x540)
            #include "res/app_util/ui/ui_img_8888.i"
        #elif defined (IMG_960X540_8888_UI)
            #include "res/app_util/ui/ui_img_960x540_8888.i"
        #endif
    #endif
#endif
#include "res/app_util/ui/ui_img_oled.i"

#define RET_ON_ERR(_expr) if(_expr != 0){return -1;}

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

#ifndef UI_SLIDER_BAR_TEXT_INFO_NO_ICON_X
#define UI_SLIDER_BAR_TEXT_INFO_NO_ICON_X UI_SLIDER_BAR_TEXT_INFO_X
#endif
#ifndef UI_SLIDER_BAR_TEXT_INFO_NO_ICON_Y
#define UI_SLIDER_BAR_TEXT_INFO_NO_ICON_Y UI_SLIDER_BAR_TEXT_INFO_Y
#endif
#ifndef UI_SLIDER_BAR_TEXT_INFO_NO_ICON_W
#define UI_SLIDER_BAR_TEXT_INFO_NO_ICON_W UI_SLIDER_BAR_TEXT_INFO_W
#endif
#ifndef UI_SLIDER_BAR_TEXT_INFO_NO_ICON_H
#define UI_SLIDER_BAR_TEXT_INFO_NO_ICON_H UI_SLIDER_BAR_TEXT_INFO_H
#endif

#ifndef UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_X
#define UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_X UI_SLIDER_BAR_PROGRESS_BAR_X
#endif
#ifndef UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_Y
#define UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_Y UI_SLIDER_BAR_PROGRESS_BAR_Y
#endif
#ifndef UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_W
#define UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_W UI_SLIDER_BAR_PROGRESS_BAR_W
#endif
#ifndef UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_H
#define UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_H UI_SLIDER_BAR_PROGRESS_BAR_H
#endif

#ifndef UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_X
#define UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_X UI_SLIDER_BAR_ARROW_LEFT_X
#endif
#ifndef UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_Y
#define UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_Y UI_SLIDER_BAR_ARROW_LEFT_Y
#endif
#ifndef UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_W
#define UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_W UI_SLIDER_BAR_ARROW_LEFT_W
#endif
#ifndef UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_H
#define UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_H UI_SLIDER_BAR_ARROW_LEFT_H
#endif

#ifndef UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_X
#define UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_X UI_SLIDER_BAR_ARROW_RIGHT_X
#endif
#ifndef UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_Y
#define UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_Y UI_SLIDER_BAR_ARROW_RIGHT_Y
#endif
#ifndef UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_W
#define UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_W UI_SLIDER_BAR_ARROW_RIGHT_W
#endif
#ifndef UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_H
#define UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_H UI_SLIDER_BAR_ARROW_RIGHT_H
#endif

#ifndef UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_X
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_X UI_SLIDER_BAR_PROGRESS_BAR_TEXT_X
#endif
#ifndef UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_Y
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_Y UI_SLIDER_BAR_PROGRESS_BAR_TEXT_Y
#endif
#ifndef UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_W
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_W UI_SLIDER_BAR_PROGRESS_BAR_TEXT_W
#endif
#ifndef UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_H
#define UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_H UI_SLIDER_BAR_PROGRESS_BAR_TEXT_H
#endif

#define UI_SLIDER_BAR_TITLE_MAX 32


typedef struct _UI_SIMPLE_DIALOG_T {

    /* Widgets */
    HANDLE_T    h_frm_simple_dialog;   /* the main frame of the S-DLG */
    HANDLE_T    h_txt_txtinfo;         /* the text box */
    HANDLE_T    h_btn_yes;             /* the YES button */
    HANDLE_T    h_btn_no;              /* the NO button */
    HANDLE_T    h_btn_info;              /* the NO button */
    HANDLE_T    h_icon;                /* the ICON */

    /* Properties */
    UTF16_T*     pw2s_txtinfo;         /* the pointer of UTF16 txtinfo */
    UTF16_T*     pw2s_yes;             /* the pointer of UTF16 yes */
    UTF16_T*     pw2s_no;              /* the pointer of UTF16 no */
    UTF16_T*     pw2s_info;            /* the pointer of UTF16 info */
    BOOL         b_answer;
    BOOL         b_info_btn_focused;

    /* Optional Callbacks */
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct;
    ui_simple_dialog_no_cb_fct   pf_ui_simple_dialog_no_cb_fct;
    ui_simple_dialog_info_cb_fct   pf_ui_simple_dialog_info_cb_fct;
    ui_simple_dialog_other_key_cb_fct   pf_ui_simple_dialog_other_key_cb_fct;
    ui_simple_dialog_tts_cb_fct   pf_ui_simple_dialog_tts_cb_fct;

    /* Template Images */
    WGL_HIMG_TPL_T  h_ui_simple_dialog_bk0;             /* Simple Dialog BK */
#if defined(IMG_960X540_8888_UI)
    /* Template Images */
    WGL_HIMG_TPL_T  h_ui_simple_dialog_bk1;             /* Simple Dialog BK */

#endif
    WGL_HIMG_TPL_T  h_ui_simple_dialog_selected_bk;     /* Simple Dialog selected button BK */
    WGL_HIMG_TPL_T  h_ui_simple_dialog_unselected_bk;   /* Simple Dialog unselected button BK */
    WGL_HIMG_TPL_T  h_ui_simple_dialog_info_icon;

} UI_SIMPLE_DIALOG_T;

typedef struct _UI_SLIDER_BAR_T{

    /* Widgets */
    HANDLE_T    h_frm_slider;   /* the main frame of the slider */
    HANDLE_T    h_txt_txtinfo;  /* the left text hint */
    HANDLE_T    h_txt_bar_txt;  /* the progress bar's position */
    HANDLE_T    h_pb_bar;       /* point style */
    HANDLE_T    h_pb_point;     /* point style */

    HANDLE_T    h_audio;
    HANDLE_T    h_inaudio;
    HANDLE_T    h_zoom_audio;
    HANDLE_T    h_zoom_inaudio;
    HANDLE_T    h_toast;

    HANDLE_T    h_inaudio_for_bths;   
#ifdef IMG_960X540_8888_UI
    HANDLE_T    h_arrow_left;   /*arrow left*/
    HANDLE_T    h_arrow_right;  /*arrow right*/
    HANDLE_T    h_icon;         /*slider icon*/
#endif

    /* Properties */
    HANDLE_T    h_pb_active;    /* reference to h_pb_bar or h_pb_point */
    UI_SLIDER_BAR_STYLE_T e_style; /* the style of slider bar */
    INT32       i4_min;         /* the min value */
    INT32       i4_max;         /* the max value */
    INT32       i4_pos;         /* the position of the slider */
    UTF16_T     w2s_title[UI_SLIDER_BAR_TITLE_MAX];   /* the copy of the title of slider bar */
    UINT8       ui1_frm_alpha;      /* The Alpha value of frame */
    UINT8       ui1_pgbar_alpha;    /* The Alpha value of the progress bar */
    UINT8       ui1_text_alpha;     /* The Alpha value of the text */

    /* Optional Callbacks */
    ui_slider_bar_pos_chg_nfy_fct pf_ui_slider_bar_pos_chg_nfy_fct; /* Position Change nofify */
    ui_slider_bar_get_pos_cb_fct  pf_ui_slider_bar_get_pos_cb_fct; /* Get Pos call-back */

    /* Template Images */
    WGL_HIMG_TPL_T  h_ui_slider_bar_bk0;          /* Slider Bar BK */
    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_bar;       /* Slider Bar's Progress Bar's Bar */
    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_bk0;       /* Slider Bar's Progress Bar's BK */

    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_inaudio;
    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_audio;
    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_zoom_inaudio;
    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_zoom_audio;
    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_toast;
    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_inaudio_for_bths;
#ifdef IMG_960X540_8888_UI
    WGL_HIMG_TPL_T  h_g_ui_slider_arrow_left;       /* Slider Bar BK */
    WGL_HIMG_TPL_T  h_g_ui_slider_arrow_right;
#endif
    WGL_HIMG_TPL_T  h_ui_slider_bar_mute;
    WGL_HIMG_TPL_T  h_ui_slider_bar_pg_bar_red;
    WGL_HIMG_TPL_T  h_g_ui_vol_mute_fill_leftcap;

    WGL_HIMG_TPL_T  h_ui_slider_bar_bt_headphone_icon;
    WGL_HIMG_TPL_T  h_ui_slider_bar_zoom_bt_headphone_icon;

    /* User defined tag */
    VOID*       pv_tag;

} UI_SLIDER_BAR_T;


/*-----------------------------------------------------------------------------
                    data declarations
-----------------------------------------------------------------------------*/

/* debug level */
static UINT16               ui2_ui_dbg_level = DBG_INIT_LEVEL;

/* Image UI tag */
static BOOL                 b_image_ui = TRUE;
static BOOL                 b_oled = FALSE;
/*-----------------------------------------------------------------------------
                    public functions declarations
-----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name: _slider_bar_set_attach_data
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
 extern  BOOL a_is_oled_compensation_support();
static INT32 _ui_slider_bar_set_attach_data(
                HANDLE_T       h_slider_bar,
                UI_SLIDER_BAR_T*  pt_ui_slider_bar)
{
    INT32   i4_ret = APP_UIR_OK;
    i4_ret = c_wgl_do_cmd(h_slider_bar,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_ui_slider_bar),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _slider_bar_get_attach_data
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
static INT32 _ui_slider_bar_get_attach_data(
                HANDLE_T         h_slider_bar,
                UI_SLIDER_BAR_T**    ppt_ui_slider_bar)
{
    INT32   i4_ret = APP_UIR_OK;
    i4_ret = c_wgl_do_cmd(h_slider_bar,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_ui_slider_bar),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}



/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_slider_create_frm(UI_SLIDER_BAR_T*         pt_ui_slider_bar,
                                   UI_SLIDER_BAR_STYLE_T    e_style,
                                   wgl_widget_proc_fct      pf_wdgt_proc,
                                   HANDLE_T                 h_parent,
                                   GL_POINT_T*              pt_begin_offset)
{

    INT32             i4_ret;
    GL_RECT_T         t_rect;
    UINT32            ui4_style;
    WGL_COLOR_INFO_T  t_clr_info;
    WGL_IMG_INFO_T    t_img_info;

    ui4_style = 0;

    if(b_image_ui)
    {
        ui4_style = 0;
    }
    else
    {
        ui4_style |= WGL_STL_GL_NO_IMG_UI;
    }

    if(pt_begin_offset == NULL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_X,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_W,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_H);
    }
    else  /* App Customized */
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_X + pt_begin_offset->i4_x,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_Y + pt_begin_offset->i4_y,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_W,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_H);
        #if 1
        if (e_style == UI_SLIDER_BAR_STYLE_BAR)
        {
            SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_X + pt_begin_offset->i4_x,
                         UI_SLIDER_BAR_DEF_CONTENT_FRAME_Y + pt_begin_offset->i4_y,
                         UI_SLIDER_BAR_STYLE_BAR_CONTENT_FRAME_W,
                         UI_SLIDER_BAR_STYLE_BAR_CONTENT_FRAME_H);
        }
        #endif
    }

    if(e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);
    }


    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_ui_slider_bar->h_frm_slider);

    if (i4_ret < 0)
    {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }

    if(b_image_ui)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_frm_slider,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    =  t_g_ui_color_bk0;
        t_clr_info.u_color_data.t_standard.t_highlight =  t_g_ui_color_bk0;
        t_clr_info.u_color_data.t_standard.t_disable   =  t_g_ui_color_bk0;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_frm_slider,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info));
        UI_CHK_FAIL(i4_ret);
    }

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_slider_create_txtinfo(UI_SLIDER_BAR_T*    pt_ui_slider_bar,
                                       BOOL b_no_icon,
                                       UI_SLIDER_BAR_STYLE_T e_style)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;

    ui4_style =  WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MAX_128;

    if (b_no_icon)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_TEXT_INFO_NO_ICON_X,
                         UI_SLIDER_BAR_TEXT_INFO_NO_ICON_Y,
                         UI_SLIDER_BAR_TEXT_INFO_NO_ICON_W,
                         UI_SLIDER_BAR_TEXT_INFO_NO_ICON_H);
    }
    else
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_TEXT_INFO_X,
                         UI_SLIDER_BAR_TEXT_INFO_Y,
                         UI_SLIDER_BAR_TEXT_INFO_W,
                         UI_SLIDER_BAR_TEXT_INFO_H);
    }

    if(e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_TEXT_INFO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_TEXT_INFO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_TEXT_INFO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_TEXT_INFO_H);
    }

    i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_ui_slider_bar->h_txt_txtinfo);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_txtinfo,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Color */
       t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_pg_bk1;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_pg_bk1;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_pg_bk1;
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    UI_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_transp;
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    UI_CHK_FAIL(i4_ret);


    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_txtinfo,
                          WGL_CMD_TEXT_SET_ALIGN,
                     #ifdef IMG_960X540_8888_UI
                          WGL_PACK(WGL_AS_LEFT_TOP),
                     #else
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                     #endif
                          NULL);
    UI_CHK_FAIL(i4_ret);


    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_slider_create_progressbar_bar(UI_SLIDER_BAR_T*         pt_ui_slider_bar,
                                               BOOL                     b_is_no_icon,
                                               UI_SLIDER_BAR_STYLE_T    e_style)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_INSET_T         t_inset;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;

    if (b_is_no_icon)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_X,
                         UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_Y,
                         UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_W,
                         UI_SLIDER_BAR_PROGRESS_BAR_NO_ICON_H);
    }
    else
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_PROGRESS_BAR_X,
                         UI_SLIDER_BAR_PROGRESS_BAR_Y,
                         UI_SLIDER_BAR_PROGRESS_BAR_W,
                         UI_SLIDER_BAR_PROGRESS_BAR_H);
    }

    if(e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_X,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_W,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_H);

    }

    ui4_style = 0;

    if(b_image_ui)
    {
        ui4_style = 0;
    }
    else
    {
        ui4_style |= WGL_STL_GL_NO_IMG_UI;
    }

    i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_ui_slider_bar->h_pb_bar);

    UI_CHK_FAIL(i4_ret);

    /* Set Display mode */

    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                          WGL_CMD_PG_SET_DISPLAY_MODE,
                          WGL_PACK(WGL_PG_DM_HIDE_IDR),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Insets */ /* We use content-inset only */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));

    t_inset.i4_left     = UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_L;
    t_inset.i4_right    = UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_R;
    t_inset.i4_top      = UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_T;
    t_inset.i4_bottom   = UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_B;

    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                          WGL_CMD_PG_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    UI_CHK_FAIL(i4_ret);
/*
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));

    t_inset.i4_left     = 5;
    t_inset.i4_right    = 0;
    t_inset.i4_top      = 0;
    t_inset.i4_bottom   = 3;

    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                          WGL_CMD_GL_SET_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    UI_CHK_FAIL(i4_ret);
*/
    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_bar,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Default Range */
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_bar,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK((INT32)0),
                           WGL_PACK((INT32)100));
    UI_CHK_FAIL(i4_ret);

    /* Set Default Levels */
    t_pg_levels.a_boundary[0] = 100;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_bar,
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_fg0_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_fg0_txt;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_fg0_txt;
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    UI_CHK_FAIL(i4_ret);

    /* Set progressbar's BK Image */

    if(b_image_ui)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bk0;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_ui_color_pg_bk0;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bk0;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info));
        UI_CHK_FAIL(i4_ret);

        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bk1;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_ui_color_pg_bk1;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bk1;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_PG_BODY),
                              WGL_PACK(&t_clr_info));
        UI_CHK_FAIL(i4_ret);
    }

    /* Set progressbar's BAR */
    if(b_image_ui)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_PG_LEVEL_1),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bar;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_ui_color_pg_bar;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bar;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_PG_LEVEL_1),
                              WGL_PACK(&t_clr_info));
        UI_CHK_FAIL(i4_ret);

    }

    return APP_UIR_OK;

}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_slider_create_progressbar_point(UI_SLIDER_BAR_T*       pt_ui_slider_bar,
                                                 UI_SLIDER_BAR_STYLE_T  e_style)

{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_INSET_T         t_inset;
    WGL_PG_LEVELS_INFO_T  t_pg_levels;

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_PROGRESS_BAR_X,
                     UI_SLIDER_BAR_PROGRESS_BAR_Y,
                     UI_SLIDER_BAR_PROGRESS_BAR_W,
                     UI_SLIDER_BAR_PROGRESS_BAR_H);

    if(e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_PROGRESS_BAR_LINE_X,
                     UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y,
                     UI_SLIDER_BAR_PROGRESS_BAR_LINE_W,
                     UI_SLIDER_BAR_PROGRESS_BAR_LINE_H);
    }


    ui4_style = WGL_STL_PG_POINT;

    if(b_image_ui)
    {
        ui4_style = WGL_STL_PG_POINT;
    }
    else
    {
        ui4_style |= WGL_STL_GL_NO_IMG_UI;
    }

    i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_PROGRESS_BAR,
                                 WGL_CONTENT_PROGRESS_BAR_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_ui_slider_bar->h_pb_point);

    UI_CHK_FAIL(i4_ret);

    /* Set Display mode */
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                          WGL_CMD_PG_SET_DISPLAY_MODE,
                          WGL_PACK(WGL_PG_DM_HIDE_IDR),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Insets */ /* We use content-inset only */
    c_memset(&t_inset, 0, sizeof(WGL_INSET_T));

    t_inset.i4_left     = UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_L;
    t_inset.i4_right    = UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_R;
    t_inset.i4_top      = UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_T;
    t_inset.i4_bottom   = UI_SLIDER_BAR_PROGRESS_BAR_CNT_INSET_B;

    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                          WGL_CMD_PG_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_point,
                           WGL_CMD_GL_SET_FONT,
                           (void*)&t_fnt_info,
                           NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Default Range */
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_point,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK((INT32)0),
                           WGL_PACK((INT32)100));
    UI_CHK_FAIL(i4_ret);

    /* Set Default Levels */
    t_pg_levels.a_boundary[0] = 100;
    t_pg_levels.ui1_level_number = 1;
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_point,
                           WGL_CMD_PG_SET_LEVELS,
                           WGL_PACK(&t_pg_levels),
                           NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_pg_bk1;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_pg_bk1;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_pg_bk1;
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info));
    UI_CHK_FAIL(i4_ret);

    /* Set Block Size, POINT style only */

    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                          WGL_CMD_PG_SET_BLK_PT_SIZE,
                          WGL_PACK(UI_SLIDER_BAR_PROGRESS_BAR_BLOCK_W),
                          WGL_PACK(UI_SLIDER_BAR_PROGRESS_BAR_BLOCK_H));

    /* Set progressbar's BK Image */
    if(b_image_ui)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bk1;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_ui_color_pg_bk1;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bk1;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info));
        UI_CHK_FAIL(i4_ret);

        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bk1;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_ui_color_pg_bk1;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bk1;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_PG_BODY),
                              WGL_PACK(&t_clr_info));
        UI_CHK_FAIL(i4_ret);
    }

    /* Set progressbar's BAR */
    if(b_image_ui)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_PG_LEVEL_1),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);
    }
    else
    {
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bar;
        t_clr_info.u_color_data.t_standard.t_highlight = t_g_ui_color_pg_bar;
        t_clr_info.u_color_data.t_standard.t_enable    = t_g_ui_color_pg_bar;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_PG_LEVEL_1),
                              WGL_PACK(&t_clr_info));
        UI_CHK_FAIL(i4_ret);
    }

    return APP_UIR_OK;

}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_slider_create_bar_txt(UI_SLIDER_BAR_T*      pt_ui_slider_bar,
                                       BOOL                  b_is_no_icon,
                                       UI_SLIDER_BAR_STYLE_T e_style)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_IMG_INFO_T      t_img_info;

    ui4_style =  WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MAX_128;

    if (b_is_no_icon)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_X,
                         UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_Y,
                         UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_W,
                         UI_SLIDER_BAR_PROGRESS_BAR_TEXT_NO_ICON_H);
    }
    else
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_PROGRESS_BAR_TEXT_X,
                         UI_SLIDER_BAR_PROGRESS_BAR_TEXT_Y-10,
                         UI_SLIDER_BAR_PROGRESS_BAR_TEXT_W,
                         UI_SLIDER_BAR_PROGRESS_BAR_TEXT_H);
    }

    if(e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                          UI_SLIDER_BAR_DEF_CONTENT_TOAST_X,
                          UI_SLIDER_BAR_DEF_CONTENT_TOAST_Y,
                          UI_SLIDER_BAR_DEF_CONTENT_TOAST_W,
                          UI_SLIDER_BAR_DEF_CONTENT_TOAST_H);

        i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     &(pt_ui_slider_bar->h_toast));

        /* set icon image buffer */
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_toast;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_toast;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_toast;

        i4_ret = c_wgl_do_cmd(
                        pt_ui_slider_bar->h_toast,
                        WGL_CMD_GL_SET_IMAGE,
                        WGL_PACK(WGL_IMG_FG),
                        WGL_PACK(&t_img_info));

        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_H);

        i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     &(pt_ui_slider_bar->h_inaudio));
        if (i4_ret < 0)
        {
            return APP_UIR_WIDGET_CREATE_FAIL;
        }
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_inaudio;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_inaudio;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_inaudio;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_inaudio,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_FG),
                              WGL_PACK(&t_img_info));

        UI_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     &(pt_ui_slider_bar->h_inaudio_for_bths));
        if (i4_ret < 0)
        {
            return APP_UIR_WIDGET_CREATE_FAIL;
        }
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_inaudio_for_bths;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_inaudio_for_bths;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_inaudio_for_bths;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_inaudio_for_bths,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_FG),
                              WGL_PACK(&t_img_info));

        UI_CHK_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_AUDIO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_AUDIO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_AUDIO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_AUDIO_H);

        i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &(pt_ui_slider_bar->h_audio));
        if (i4_ret < 0)
        {
            return APP_UIR_WIDGET_CREATE_FAIL;
        }

        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_audio;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_audio;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_audio;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_audio,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_FG),
                              WGL_PACK(&t_img_info));

        UI_CHK_FAIL(i4_ret);

        //zoom mode audio and inaudio icon
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_H);

        i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                     HT_WGL_WIDGET_ICON,
                                     WGL_CONTENT_ICON_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     &(pt_ui_slider_bar->h_zoom_inaudio));
        if (i4_ret < 0)
        {
            return APP_UIR_WIDGET_CREATE_FAIL;
        }
        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_inaudio;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_inaudio;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_inaudio;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_zoom_inaudio,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_FG),
                              WGL_PACK(&t_img_info));

        UI_CHK_FAIL(i4_ret);

        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_H);

        i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &(pt_ui_slider_bar->h_zoom_audio));
        if (i4_ret < 0)
        {
            return APP_UIR_WIDGET_CREATE_FAIL;
        }

        t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_audio;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_audio;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_audio;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_zoom_audio,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_FG),
                              WGL_PACK(&t_img_info));

        UI_CHK_FAIL(i4_ret);


        ui4_style =  WGL_STL_GL_NO_IMG_UI
                    |WGL_STL_TEXT_MAX_128;

        SET_RECT_BY_SIZE(&t_rect,
                             UI_SLIDER_BAR_DEF_CONTENT_TEXT_X,
                             UI_SLIDER_BAR_DEF_CONTENT_TEXT_Y,
                             UI_SLIDER_BAR_DEF_CONTENT_TEXT_W,
                             UI_SLIDER_BAR_DEF_CONTENT_TEXT_H);

        i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     &pt_ui_slider_bar->h_txt_bar_txt);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_CUSTOM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
        t_fnt_info.ui1_custom_size = 42;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        UI_CHK_FAIL(i4_ret);

        /* Set Color */
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_fg1_txt;
        t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_fg1_txt;
        t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_fg1_txt;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));
        UI_CHK_FAIL(i4_ret);

        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       = TXT_HL_CLR_TXT_ban;
        t_clr_info.u_color_data.t_standard.t_highlight    = TXT_HL_CLR_TXT_ban;
        t_clr_info.u_color_data.t_standard.t_disable      = TXT_HL_CLR_TXT_ban;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info ));
        UI_CHK_FAIL(i4_ret);

        /* Set Alignment */
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK(WGL_AS_CENTER_BOTTOM),
                              NULL);
        UI_CHK_FAIL(i4_ret);

        return APP_UIR_OK;
    }
    else
    {
      i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_ui_slider_bar->h_txt_bar_txt);

        /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        UI_CHK_FAIL(i4_ret);

        /* Set Color */
        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_pg_bk1;
        t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_pg_bk1;
        t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_pg_bk1;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_TEXT),
                              WGL_PACK(&t_clr_info ));
        UI_CHK_FAIL(i4_ret);

        t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
        t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_transp;
        t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_transp;
        t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_transp;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK(WGL_CLR_BK),
                              WGL_PACK(&t_clr_info ));
        UI_CHK_FAIL(i4_ret);

        /* Set Alignment */
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                          #ifdef IMG_960X540_8888_UI
                              WGL_PACK(WGL_AS_RIGHT_CENTER),
                          #else
                              WGL_PACK(WGL_AS_CENTER_CENTER),
                          #endif
                              NULL);
        UI_CHK_FAIL(i4_ret);

        return APP_UIR_OK;
    }
}
#ifdef IMG_960X540_8888_UI
/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_slider_create_icon(UI_SLIDER_BAR_T*    pt_ui_slider_bar)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;

    SET_RECT_BY_SIZE(&t_rect,
                     UI_SLIDER_BAR_ICON_X,
                     UI_SLIDER_BAR_ICON_Y,
                     UI_SLIDER_BAR_ICON_W,
                     UI_SLIDER_BAR_ICON_H);

    i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 NULL,
                                 NULL,
                                 &pt_ui_slider_bar->h_icon);
    if (i4_ret < 0)
    {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }

    t_rect.i4_left      = 0;
    t_rect.i4_right     = 0;
    t_rect.i4_top       = 0;
    t_rect.i4_bottom    = 0;
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_icon,
                           WGL_CMD_GL_SET_INSET,
                           &t_rect,
                           NULL);
    UI_CHK_FAIL(i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    UI_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_ui_slider_bar->h_icon, WGL_SW_NORMAL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _ui_slider_create_arrow
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
static INT32 _ui_slider_create_arrow(UI_SLIDER_BAR_T*    pt_ui_slider_bar, BOOL b_is_no_icon)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;

    /*create left arrow*/
    if (b_is_no_icon)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_X,
                         UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_Y,
                         UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_W,
                         UI_SLIDER_BAR_ARROW_LEFT_NO_ICON_H);
    }
    else
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_ARROW_LEFT_X,
                         UI_SLIDER_BAR_ARROW_LEFT_Y,
                         UI_SLIDER_BAR_ARROW_LEFT_W,
                         UI_SLIDER_BAR_ARROW_LEFT_H);
    }

    i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 NULL,
                                 NULL,
                                 &pt_ui_slider_bar->h_arrow_left);
    if (i4_ret < 0)
    {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }

    /*set arrow left GL inset*/
    t_rect.i4_left      = 0;
    t_rect.i4_right     = 0;
    t_rect.i4_top       = 0;
    t_rect.i4_bottom    = 0;
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_arrow_left,
                           WGL_CMD_GL_SET_INSET,
                           &t_rect,
                           NULL);
    UI_CHK_FAIL(i4_ret);

    /*set arrow left image*/
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_g_ui_slider_arrow_left;
    t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_g_ui_slider_arrow_left;
    t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_g_ui_slider_arrow_left;
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_arrow_left,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    UI_CHK_FAIL(i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_arrow_left,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_CENTER,
                          NULL);
    UI_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_ui_slider_bar->h_arrow_left, WGL_SW_NORMAL);
    UI_CHK_FAIL(i4_ret);


    /*create right arrow*/
    if (b_is_no_icon)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_X,
                         UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_Y,
                         UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_W,
                         UI_SLIDER_BAR_ARROW_RIGHT_NO_ICON_H);
    }
    else
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_ARROW_RIGHT_X,
                         UI_SLIDER_BAR_ARROW_RIGHT_Y,
                         UI_SLIDER_BAR_ARROW_RIGHT_W,
                         UI_SLIDER_BAR_ARROW_RIGHT_H);
    }

    i4_ret = c_wgl_create_widget(pt_ui_slider_bar->h_frm_slider,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 NULL,
                                 NULL,
                                 &pt_ui_slider_bar->h_arrow_right);

    /*set arrow right GL inset*/
    t_rect.i4_left      = 0;
    t_rect.i4_right     = 0;
    t_rect.i4_top       = 0;
    t_rect.i4_bottom    = 0;
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_arrow_right,
                           WGL_CMD_GL_SET_INSET,
                           &t_rect,
                           NULL);
    UI_CHK_FAIL(i4_ret);

    /*set arrow right image*/
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_g_ui_slider_arrow_right;
    t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_g_ui_slider_arrow_right;
    t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_g_ui_slider_arrow_right;
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_arrow_right,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    UI_CHK_FAIL(i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_arrow_right,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_CENTER,
                          NULL);
    UI_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_ui_slider_bar->h_arrow_right, WGL_SW_NORMAL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}


INT32 a_ui_slider_bar_set_caption_img(HANDLE_T    h_frm_slider,
                                      HANDLE_T    h_img_tpl_caption)
{
    INT32                   i4_ret;
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;
    WGL_IMG_INFO_T          t_img_info;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img_tpl_caption;
    t_img_info.u_img_data.t_standard.t_highlight = h_img_tpl_caption;
    t_img_info.u_img_data.t_standard.t_disable   = h_img_tpl_caption;
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    UI_CHK_FAIL(i4_ret);


    return APP_UIR_OK;

}


#endif
/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_slider_bar_image_init(UI_SLIDER_BAR_T*    pt_ui_slider_bar)
{

    b_oled = a_is_oled_compensation_support();

#ifdef IMG_960X540_8888_UI
    /* Background of slider bar */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_ui_slider_bar_bk0_png,
               &pt_ui_slider_bar->h_ui_slider_bar_bk0))

    /* Slider Bar's Progress Bar's Bar */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_ui_slider_bar_pg_bar_new_png,
               &pt_ui_slider_bar->h_ui_slider_bar_pg_bar))

    /* Slider Bar's Progress Bar's BK */
    pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 = NULL_HANDLE;
    /* Slider Bar's arrow left */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_ui_slider_arrow_left,
               &pt_ui_slider_bar->h_g_ui_slider_arrow_left))

    /* Slider Bar's arrow right */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_ui_slider_arrow_right,
               &pt_ui_slider_bar->h_g_ui_slider_arrow_right))
#endif

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static VOID _ui_slider_bar_set_visibility_by_style(UI_SLIDER_BAR_T*    pt_ui_slider_bar)
{
    /* Set visibility for all child widgets */
    c_wgl_set_visibility(pt_ui_slider_bar->h_txt_txtinfo, WGL_SW_NORMAL);

    UI_LOG_ON_FAIL (c_wgl_insert (pt_ui_slider_bar->h_txt_bar_txt,
                                  NULL_HANDLE,
                                  WGL_INSERT_TOPMOST,
                                  WGL_NO_AUTO_REPAINT));
    c_wgl_set_visibility(pt_ui_slider_bar->h_txt_bar_txt, WGL_SW_NORMAL);
    c_wgl_set_visibility(pt_ui_slider_bar->h_toast, WGL_SW_NORMAL);

    if(pt_ui_slider_bar->e_style == UI_SLIDER_BAR_STYLE_BAR)
    {
        c_wgl_set_visibility(pt_ui_slider_bar->h_pb_bar, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_ui_slider_bar->h_pb_point, WGL_SW_HIDE);

        /* Save the current active PGBAR handle */
        pt_ui_slider_bar->h_pb_active = pt_ui_slider_bar->h_pb_bar;
    }
    else if (pt_ui_slider_bar->e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        c_wgl_set_visibility(pt_ui_slider_bar->h_pb_bar, WGL_SW_NORMAL);
        c_wgl_set_visibility(pt_ui_slider_bar->h_pb_point, WGL_SW_HIDE);
        pt_ui_slider_bar->h_pb_active = pt_ui_slider_bar->h_pb_bar;
    }
    else
    {
        c_wgl_set_visibility(pt_ui_slider_bar->h_pb_bar, WGL_SW_HIDE);
        c_wgl_set_visibility(pt_ui_slider_bar->h_pb_point, WGL_SW_NORMAL);

        /* Save the current active PGBAR handle */
        pt_ui_slider_bar->h_pb_active = pt_ui_slider_bar->h_pb_point;
    }
}


static INT32 _ui_slider_bar_set_visibility_by_mute_status(UI_SLIDER_BAR_T* pt_ui_slider_bar, BOOL b_mute, BOOL is_headphone_vol)
{
    INT32               i4_ret;
    WGL_IMG_INFO_T      t_img_info;
    UINT8               ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;

    if (b_mute)
    {
            /* mute. */
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_mute;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_mute;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_mute;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_frm_slider,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));

        UI_CHK_FAIL(i4_ret);

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_PG_LEVEL_1),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);

    }
    else
    {
            /* unmute. */
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_frm_slider,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);


        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_PG_LEVEL_1),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);
    }

    i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
    UI_CHK_FAIL(i4_ret);

    if(b_mute)
    {
        if(ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_OFF)
        {
            c_wgl_set_visibility(pt_ui_slider_bar->h_audio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_zoom_inaudio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_zoom_audio, WGL_SW_HIDE);
            if (is_headphone_vol)
            {
                c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio, WGL_SW_HIDE);
                c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio_for_bths, WGL_SW_NORMAL);
            }
            else
            {
                c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio, WGL_SW_NORMAL);
                c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio_for_bths, WGL_SW_HIDE);
            }
        }
        else
        {
            c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_audio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_zoom_audio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_zoom_inaudio, WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio_for_bths, WGL_SW_HIDE);
        }
    }
    else
    {
        if(ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_OFF)
        {
            c_wgl_set_visibility(pt_ui_slider_bar->h_zoom_audio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_zoom_inaudio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_audio, WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio_for_bths, WGL_SW_HIDE);
        }
        else
        {
            c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_audio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_zoom_inaudio, WGL_SW_HIDE);
            c_wgl_set_visibility(pt_ui_slider_bar->h_zoom_audio, WGL_SW_NORMAL);
            c_wgl_set_visibility(pt_ui_slider_bar->h_inaudio_for_bths, WGL_SW_HIDE);
        }
    }

    return APP_UIR_OK;
}

static INT32 _ui_slider_bar_adjust_font_size(UI_SLIDER_BAR_T* pt_ui_slider_bar)
{
    UINT8           ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;
    INT32           i4_ret;
    GL_RECT_T       t_rect;

    if (pt_ui_slider_bar && pt_ui_slider_bar->e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
        UI_CHK_FAIL(i4_ret);

        if(ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
        {
             /* zoom audio - icon  */
            SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_zoom_audio,
                                &t_rect,
                                WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);

            /* inaudio - icon  */
            SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_zoom_inaudio,
                                 &t_rect,
                                 WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);
        }
        else
        {
             /* audio - icon  */
            SET_RECT_BY_SIZE(&t_rect,
                              UI_SLIDER_BAR_DEF_CONTENT_AUDIO_X,
                              UI_SLIDER_BAR_DEF_CONTENT_AUDIO_Y,
                              UI_SLIDER_BAR_DEF_CONTENT_AUDIO_W,
                              UI_SLIDER_BAR_DEF_CONTENT_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_audio,
                                &t_rect,
                                WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);

            /* inaudio - icon  */
            SET_RECT_BY_SIZE(&t_rect,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_X,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_Y,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_W,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_inaudio,
                                 &t_rect,
                                 WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);

            SET_RECT_BY_SIZE(&t_rect,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_X,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_Y,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_W,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_inaudio_for_bths,
                                 &t_rect,
                                 WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);
        }
    }

    return APP_UIR_OK;
}

INT32 a_ui_show_slider_bar_by_mute (HANDLE_T h_frm_slider, BOOL b_mute, BOOL is_headphone_vol)
{
     UI_SLIDER_BAR_T*        pt_ui_slider_bar;
     /* Get slider bar structure */
     UI_LOG_ON_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                    &pt_ui_slider_bar));

     UI_LOG_ON_FAIL(_ui_slider_bar_adjust_font_size(pt_ui_slider_bar));
     UI_LOG_ON_FAIL(_ui_slider_bar_set_visibility_by_mute_status(pt_ui_slider_bar, b_mute, is_headphone_vol));
     return a_ui_slider_bar_repaint(h_frm_slider);
}
/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_slider_bar_set_bar_text(HANDLE_T     h_frm_slider,
                                         INT32        i4_pos,
                                         BOOL         b_repaint,
                                         BOOL         is_headphone_vol)
{
    INT32               i4_ret;
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;

    CHAR                s_pos[6] = "";
    UTF16_T             w2s_str[6];
    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));

    /* Clear value if necessary */
    c_memset(w2s_str, 0, sizeof(UTF16_T) * 6);

    /* Set value to bar_txt */

    if (!is_headphone_vol)
    {
        c_sprintf(s_pos, "%ld", i4_pos);
    }
    else 
    {
        strcpy(s_pos, " ");
    }
    
    c_uc_ps_to_w2s(s_pos, w2s_str, c_strlen(s_pos));

    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_txt_bar_txt,
                        WGL_CMD_TEXT_SET_TEXT,
                        WGL_PACK(w2s_str),
                        WGL_PACK(c_uc_w2s_strlen(w2s_str)));
    UI_CHK_FAIL(i4_ret);

    /* repaint? */

    if(b_repaint)
    {
        c_wgl_repaint(pt_ui_slider_bar->h_txt_bar_txt, NULL, TRUE);
    }

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_simple_dialog_set_attach_data(
                HANDLE_T       h_simple_dialog,
                UI_SIMPLE_DIALOG_T*  pt_ui_simple_dialog)
{
    INT32   i4_ret = APP_UIR_OK;
    i4_ret = c_wgl_do_cmd(h_simple_dialog,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_ui_simple_dialog),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_simple_dialog_get_attach_data(
                HANDLE_T         h_simple_dialog,
                UI_SIMPLE_DIALOG_T**    ppt_ui_simple_dialog)
{
    INT32   i4_ret = APP_UIR_OK;
    i4_ret = c_wgl_do_cmd(h_simple_dialog,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_ui_simple_dialog),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_simple_dialog_create_frm(UI_SIMPLE_DIALOG_T*    pt_ui_simple_dialog,
                                          wgl_widget_proc_fct pf_wdgt_proc,
                                          HANDLE_T            h_parent,
                                          GL_RECT_T*          pt_rect,
                                          GL_POINT_T*         pt_begin_offset,
                                          UI_SIMPLE_DIALOG_STYLE_T e_style)

{

    INT32             i4_ret;
    GL_RECT_T         t_rect;
    UINT32            ui4_style;
    WGL_IMG_INFO_T    t_img_info;
    GL_POINT_T        t_begin_offset;

    ui4_style = 0;

    if(pt_begin_offset == NULL)
    {
        t_begin_offset.i4_x = 0;
        t_begin_offset.i4_y = 0;
    }
    else
    {
        t_begin_offset = *pt_begin_offset;
    }

    if(e_style == UI_SIMPLE_DIALOG_STYLE_BIG)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x,
                         UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                         UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_W,
                         UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_H);
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_MEDIUM)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x,
                         UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                         UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_W,
                         UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_H);
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_SMALL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x,
                         UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                         UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W,
                         UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_H);
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY)
    {
        /* If the pt_rect is specified, use this parameter */

        if(pt_rect == NULL)
        {
            SET_RECT_BY_SIZE(&t_rect,
                             UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x,
                             UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                             UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_W,
                             UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_H);
        }
        else
        {
            t_rect = *pt_rect;
        }
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_WARNING_MSG)
    {
        /* If the pt_rect is specified, use this parameter */

        if(pt_rect == NULL)
        {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_X + t_begin_offset.i4_x,
                         UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                         UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_W,
                         UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_H);
        }
        else
        {
         t_rect = *pt_rect;
        }
    }
    else
    {
        UI_CHK_FAIL(-1);
    }

    /*set dialog location*/

    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_FRAME,
                                 WGL_CONTENT_FRAME_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_ui_simple_dialog->h_frm_simple_dialog);

    if (i4_ret < 0)
    {
        return APP_UIR_WIDGET_CREATE_FAIL;
    }


#ifdef  IMG_960X540_8888_UI
    if( UI_SIMPLE_DIALOG_STYLE_SMALL == e_style ||
		UI_SIMPLE_DIALOG_STYLE_WARNING_MSG == e_style)
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_simple_dialog->h_ui_simple_dialog_bk0;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_simple_dialog->h_ui_simple_dialog_bk0;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_simple_dialog->h_ui_simple_dialog_bk0;
    }
    else
    {
        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_simple_dialog->h_ui_simple_dialog_bk1;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_simple_dialog->h_ui_simple_dialog_bk1;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_simple_dialog->h_ui_simple_dialog_bk1;
    }
    i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_frm_simple_dialog,
                       WGL_CMD_GL_SET_IMAGE,
                       WGL_PACK(WGL_IMG_BK),
                       WGL_PACK(&t_img_info));
    UI_CHK_FAIL(i4_ret);
#else
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_ui_simple_dialog->h_ui_simple_dialog_bk0;
    t_img_info.u_img_data.t_standard.t_highlight = pt_ui_simple_dialog->h_ui_simple_dialog_bk0;
    t_img_info.u_img_data.t_standard.t_disable   = pt_ui_simple_dialog->h_ui_simple_dialog_bk0;
    i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_frm_simple_dialog,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    UI_CHK_FAIL(i4_ret);
#endif
    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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

static INT32 _ui_simple_dialog_create_info_icon(UI_SIMPLE_DIALOG_T*      pt_ui_simple_dialog,
                                                  UI_SIMPLE_DIALOG_STYLE_T e_style,
                                                  GL_RECT_T*               pt_rect,
                                                  UINT16                   ui2_align_type)
{
    INT32               i4_ret = APP_UIR_OK;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    INT32               i4_left = 0;
    INT32               i4_top = 10;
    INT32               i4_width = 40;
    INT32               i4_height = 36;

    if (UI_SIMPLE_DIALOG_STYLE_SMALL == e_style)
    {
        i4_left = (UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W - i4_width) / 2;
        i4_top = UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_Y ;
    }
    else if (UI_SIMPLE_DIALOG_STYLE_MEDIUM == e_style)
    {
        i4_left = (UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_W - i4_width) / 2;
        i4_top = UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_Y;
    }
    else if (UI_SIMPLE_DIALOG_STYLE_BIG == e_style)
    {
        i4_left = (UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_W - i4_width) / 2;
        i4_top = UI_SIMPLE_DIALOG_BIG_TEXT_INFO_Y;
    }
    else
    {
        i4_left = (UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W - i4_width) / 2;
        i4_top = UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_Y;
    }

    SET_RECT_BY_SIZE(&t_rect,
                     i4_left,
                     i4_top,
                     i4_width,
                     i4_height);

    i4_ret = c_wgl_create_widget(pt_ui_simple_dialog->h_frm_simple_dialog,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &(pt_ui_simple_dialog->h_icon));
    if (i4_ret < 0)
    {
        DBG_ERROR(("\nFailed to create icon!\n"));
    }
    UI_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_ui_simple_dialog->h_ui_simple_dialog_info_icon;
    t_img_info.u_img_data.t_standard.t_highlight = pt_ui_simple_dialog->h_ui_simple_dialog_info_icon;
    t_img_info.u_img_data.t_standard.t_disable   = pt_ui_simple_dialog->h_ui_simple_dialog_info_icon;
    i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
    UI_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_set_visibility(pt_ui_simple_dialog->h_icon,
                                 WGL_SW_HIDE);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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

static INT32 _ui_simple_dialog_create_txtinfo(UI_SIMPLE_DIALOG_T*      pt_ui_simple_dialog,
                                              UI_SIMPLE_DIALOG_STYLE_T e_style,
                                              GL_RECT_T*               pt_rect,
                                              UINT16                   ui2_align_type)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT16              ui2_align;

    ui4_style =  WGL_STL_GL_NO_IMG_UI
                |WGL_STL_TEXT_MULTILINE
                |WGL_STL_TEXT_MAX_512
                |WGL_STL_TEXT_MAX_DIS_10_LINE;

    /* Default alignment */

    if(ui2_align_type == 0)
    {
        ui2_align = WGL_AS_LEFT_TOP;
    }
    else
    {
        ui2_align = ui2_align_type;
    }

    if(e_style == UI_SIMPLE_DIALOG_STYLE_BIG)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SIMPLE_DIALOG_BIG_TEXT_INFO_X,
                         UI_SIMPLE_DIALOG_BIG_TEXT_INFO_Y,
                         UI_SIMPLE_DIALOG_BIG_TEXT_INFO_W,
                         UI_SIMPLE_DIALOG_BIG_TEXT_INFO_H);
    }

    else if(e_style == UI_SIMPLE_DIALOG_STYLE_MEDIUM)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_X,
                         UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_Y,
                         UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_W,
                         UI_SIMPLE_DIALOG_MEDIUM_TEXT_INFO_H);
    }

    else if(e_style == UI_SIMPLE_DIALOG_STYLE_SMALL)
    {
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_X,
                         UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_Y,
                         UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_W,
                         (ui2_align_type == WGL_AS_LEFT_TOP)?UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_H+10:UI_SIMPLE_DIALOG_SMALL_TEXT_INFO_H);
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY)
    {
        /* If the pt_rect is specified, use this parameter */
        if(pt_rect == NULL)
        {
            SET_RECT_BY_SIZE(&t_rect,
                             UI_SIMPLE_DIALOG_INFO_TEXT_INFO_X,
                             UI_SIMPLE_DIALOG_INFO_TEXT_INFO_Y,
                             UI_SIMPLE_DIALOG_INFO_TEXT_INFO_W,
                             UI_SIMPLE_DIALOG_INFO_TEXT_INFO_H);
        }
        else
        {
            SET_RECT_BY_SIZE(&t_rect,
                             0,
                             0,
                             pt_rect->i4_right - pt_rect->i4_left,
                             pt_rect->i4_bottom - pt_rect->i4_top);

        }
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_WARNING_MSG)
    {
        /* If the pt_rect is specified, use this parameter */
        if(pt_rect == NULL)
        {
            SET_RECT_BY_SIZE(&t_rect,
                             UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_X,
                             UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_Y,
                             UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_W,
                             UI_SIMPLE_DIALOG_WARNING_MSG_TEXT_INFO_H);
        }
        else
        {
            SET_RECT_BY_SIZE(&t_rect,
                             0,
                             0,
                             pt_rect->i4_right - pt_rect->i4_left,
                             pt_rect->i4_bottom - pt_rect->i4_top);

        }
    }

    else
    {
        UI_CHK_FAIL(-1);
    }

    if (NULL_HANDLE != pt_ui_simple_dialog->h_icon)
    {
        t_rect.i4_top += 30;
    }
    if(ui2_align_type == WGL_AS_LEFT_TOP)
    {
        t_rect.i4_top = 5;
    }

    i4_ret = c_wgl_create_widget(pt_ui_simple_dialog->h_frm_simple_dialog,
                                 HT_WGL_WIDGET_TEXT,
                                 WGL_CONTENT_TEXT_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 &pt_ui_simple_dialog->h_txt_txtinfo);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_fg1_txt;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_fg1_txt;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_fg1_txt;
    i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    UI_CHK_FAIL(i4_ret);

    t_clr_info.e_type = WGL_COLOR_SET_STANDARD;
    t_clr_info.u_color_data.t_standard.t_enable       = t_g_ui_color_transp;
    t_clr_info.u_color_data.t_standard.t_highlight    = t_g_ui_color_transp;
    t_clr_info.u_color_data.t_standard.t_disable      = t_g_ui_color_transp;
    i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_txt_txtinfo,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_BK),
                          WGL_PACK(&t_clr_info ));
    UI_CHK_FAIL(i4_ret);

    /* Set Alignment */
    i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_txt_txtinfo,
                          WGL_CMD_TEXT_SET_ALIGN,
                          WGL_PACK(ui2_align),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_simple_dialog_create_button(UI_SIMPLE_DIALOG_T*    pt_ui_simple_dialog,
                                             HANDLE_T*              pt_btn,
                                             UINT16     ui2_start_x,
                                             UINT16     ui2_start_y,
                                             UINT16     ui2_width,
                                             UINT16     ui2_height)
{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    UINT32              ui4_style;
    WGL_COLOR_INFO_T    t_clr_info;
    WGL_IMG_INFO_T      t_img_info;
    WGL_FONT_INFO_T     t_fnt_info;

    /*ui4_style =  WGL_STL_GL_NO_IMG_UI; */
    ui4_style = WGL_STL_BTN_CHECKBOX;

    SET_RECT_BY_SIZE(&t_rect,
                     (INT32)ui2_start_x,
                     (INT32)ui2_start_y,
                     (INT32)ui2_width,
                     (INT32)ui2_height);

    i4_ret = c_wgl_create_widget(pt_ui_simple_dialog->h_frm_simple_dialog,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)ui4_style,
                                 NULL,
                                 pt_btn);

    /* Set Color */
    t_clr_info.e_type = WGL_COLOR_SET_EXTEND;

    t_clr_info.u_color_data.t_extend.t_enable             = t_g_ui_color_fg1_txt;
    t_clr_info.u_color_data.t_extend.t_disable            = t_g_ui_color_fg1_txt;
    t_clr_info.u_color_data.t_extend.t_highlight          = t_g_ui_color_fg1_txt;
    t_clr_info.u_color_data.t_extend.t_highlight_inactive = t_g_ui_color_fg1_txt;
    t_clr_info.u_color_data.t_extend.t_push               = t_g_ui_color_fg1_txt;
    t_clr_info.u_color_data.t_extend.t_push_unhighlight   = t_g_ui_color_fg2_txt;

    i4_ret = c_wgl_do_cmd(*pt_btn,
                          WGL_CMD_GL_SET_COLOR,
                          WGL_PACK(WGL_CLR_TEXT),
                          WGL_PACK(&t_clr_info ));
    UI_CHK_FAIL(i4_ret);

    /* Set Image */

    t_img_info.e_type = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable            = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_enable             = pt_ui_simple_dialog->h_ui_simple_dialog_unselected_bk;
    t_img_info.u_img_data.t_extend.t_highlight          = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push               = NULL_HANDLE;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = pt_ui_simple_dialog->h_ui_simple_dialog_selected_bk;

    i4_ret = c_wgl_do_cmd(*pt_btn,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_BK),
                          WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);

    /* Set Font */
    c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
    c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT);
    t_fnt_info.e_font_size  = FE_FNT_SIZE_SMALL;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    i4_ret = c_wgl_do_cmd(*pt_btn,
                          WGL_CMD_GL_SET_FONT,
                          WGL_PACK(&t_fnt_info),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    /* Set Alignment */

    i4_ret = c_wgl_do_cmd(*pt_btn,
                          WGL_CMD_BTN_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_simple_dialog_create_yes_button(UI_SIMPLE_DIALOG_T*      pt_ui_simple_dialog,
                                                 UI_SIMPLE_DIALOG_STYLE_T e_style,
                                                 BOOL                     b_one_btn_mode,
                                                 BOOL                     b_three_btn_mode,
                                                 HANDLE_T*                pt_btn)
{
    INT32   i4_result = APP_UIR_OK;
    UINT32  ui4_x = 0;
    UINT32  ui4_y = 0;
    UINT32  ui4_w = 0;
    UINT32  ui4_h = 0;

    if(e_style == UI_SIMPLE_DIALOG_STYLE_BIG)
    {
        ui4_x = UI_SIMPLE_DIALOG_BIG_BUTTON_YES_X;
        ui4_y = UI_SIMPLE_DIALOG_BIG_BUTTON_YES_Y;
        ui4_w = UI_SIMPLE_DIALOG_BIG_BUTTON_YES_W;
        ui4_h = UI_SIMPLE_DIALOG_BIG_BUTTON_YES_H;
        if (b_one_btn_mode)
        {
            ui4_x = (UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_W - UI_SIMPLE_DIALOG_BIG_BUTTON_YES_W)/2;
            ui4_w = UI_SIMPLE_DIALOG_BIG_BUTTON_YES_W;
        }
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_MEDIUM)
    {
        ui4_x = UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_X;
        ui4_y = UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_Y;
        ui4_w = UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_W;
        ui4_h = UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_H;
        if (b_one_btn_mode)
        {
			ui4_x = (UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_W - UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_W)/2;
            ui4_w = UI_SIMPLE_DIALOG_MEDIUM_BUTTON_YES_W;
        }
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_SMALL)
    {
        ui4_x = UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_X;
        ui4_y = UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_Y;
        ui4_w = UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W;
        ui4_h = UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_H;
        if (b_one_btn_mode)
        {
            ui4_x = (UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W - UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W)/2;
            ui4_w = UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W;
        }
        else if(b_three_btn_mode)
        {
            ui4_x = 0;
            ui4_y = UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_Y;
        }
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY)
    {
        return APP_UIR_OK;
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_WARNING_MSG)
    {
        return APP_UIR_OK;
    }
    else
    {
        UI_CHK_FAIL(-1);
    }

    i4_result = _ui_simple_dialog_create_button(pt_ui_simple_dialog,
                                                pt_btn,
                                                ui4_x,
                                                ui4_y,
                                                ui4_w,
                                                ui4_h);

    return i4_result;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_simple_dialog_create_no_button(UI_SIMPLE_DIALOG_T*      pt_ui_simple_dialog,
                                                UI_SIMPLE_DIALOG_STYLE_T e_style,
                                                BOOL                     b_three_btn_mode,
                                                HANDLE_T*                pt_btn)
{
    INT32 i4_result;

    if(e_style == UI_SIMPLE_DIALOG_STYLE_BIG)
    {
        i4_result = _ui_simple_dialog_create_button(pt_ui_simple_dialog,
                                                    pt_btn,
                                                    UI_SIMPLE_DIALOG_BIG_BUTTON_NO_X,
                                                    UI_SIMPLE_DIALOG_BIG_BUTTON_NO_Y,
                                                    UI_SIMPLE_DIALOG_BIG_BUTTON_NO_W,
                                                    UI_SIMPLE_DIALOG_BIG_BUTTON_NO_H);
    }

    else if(e_style == UI_SIMPLE_DIALOG_STYLE_MEDIUM)
    {
        i4_result = _ui_simple_dialog_create_button(pt_ui_simple_dialog,
                                                    pt_btn,
                                                    UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_X,
                                                    UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_Y,
                                                    UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_W,
                                                    UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_H);
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_SMALL)
    {
        if(b_three_btn_mode)
        {

            i4_result = _ui_simple_dialog_create_button(pt_ui_simple_dialog,
                                                        pt_btn,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_Y,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_W,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_H);
        }
        else
        {
            i4_result = _ui_simple_dialog_create_button(pt_ui_simple_dialog,
                                                        pt_btn,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_X,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_Y,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_W,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_H);
        }
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY)
    {
        i4_result = APP_UIR_OK;
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_WARNING_MSG)
    {
        i4_result = APP_UIR_OK;
    }
    else
    {
        UI_CHK_FAIL(-1);
    }

    return i4_result;
}

/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_simple_dialog_create_info_button(UI_SIMPLE_DIALOG_T*      pt_ui_simple_dialog,
                                                UI_SIMPLE_DIALOG_STYLE_T e_style,
                                                HANDLE_T*                pt_btn)
{
    INT32 i4_result;

    if(e_style == UI_SIMPLE_DIALOG_STYLE_BIG)
    {
        i4_result = _ui_simple_dialog_create_button(pt_ui_simple_dialog,
                                                    pt_btn,
                                                    UI_SIMPLE_DIALOG_BIG_BUTTON_NO_X,
                                                    UI_SIMPLE_DIALOG_BIG_BUTTON_NO_Y,
                                                    UI_SIMPLE_DIALOG_BIG_BUTTON_NO_W,
                                                    UI_SIMPLE_DIALOG_BIG_BUTTON_NO_H);
    }

    else if(e_style == UI_SIMPLE_DIALOG_STYLE_MEDIUM)
    {
        i4_result = _ui_simple_dialog_create_button(pt_ui_simple_dialog,
                                                    pt_btn,
                                                    UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_X,
                                                    UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_Y,
                                                    UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_W,
                                                    UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_H);
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_SMALL)
    {
            i4_result = _ui_simple_dialog_create_button(pt_ui_simple_dialog,
                                                        pt_btn,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_YES_W+UI_SIMPLE_DIALOG_MEDIUM_BUTTON_NO_W,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_Y,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_W,
                                                        UI_SIMPLE_DIALOG_SMALL_BUTTON_NO_H);

    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY)
    {
        i4_result = APP_UIR_OK;
    }
    else if(e_style == UI_SIMPLE_DIALOG_STYLE_WARNING_MSG)
    {
        i4_result = APP_UIR_OK;
    }
    else
    {
        UI_CHK_FAIL(-1);
    }

    return i4_result;
}


/*----------------------------------------------------------------------------
 * Name:
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
static INT32 _ui_simple_dialog_image_init(UI_SIMPLE_DIALOG_T*    pt_ui_simple_dialog)
{
    b_oled = a_is_oled_compensation_support();

#ifndef APP_UTIL_CUSTOM_UI_SIMPLE_DIALOG_BK_SEGMENT_TYPE
    #define APP_UTIL_CUSTOM_UI_SIMPLE_DIALOG_BK_SEGMENT_TYPE    WGL_IMG_ST_HV
#endif

#ifdef  IMG_960X540_8888_UI
    /* Background of simple_dialog */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_ui_Warning_Bar,/*&t_g_ui_simple_dialog_bk0_png,*/
               &pt_ui_simple_dialog->h_ui_simple_dialog_bk0))

    /* Background of simple_dialog */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_ui_demo_dialog_bkg,
               &pt_ui_simple_dialog->h_ui_simple_dialog_bk1))

    /* Background of selected button */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               b_oled ? &t_g_ui_dialog_button_highlight_oled : &t_g_ui_Warning_Bar_button_hlt,/*&t_g_ui_simple_dialog_selected_png,*/
               &pt_ui_simple_dialog->h_ui_simple_dialog_selected_bk))

    /* Background of unselected button */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_ui_Warning_Bar_button,/*&t_g_ui_simple_dialog_unselected_png,*/
               &pt_ui_simple_dialog->h_ui_simple_dialog_unselected_bk))

    /* Background of unselected button */
    RET_ON_ERR(c_wgl_img_tpl_create(WGL_IMG_ST_NO_SEGMENT,
               &t_g_ui_Dialog_info_icon,/*&t_g_ui_simple_dialog_unselected_png,*/
               &pt_ui_simple_dialog->h_ui_simple_dialog_info_icon))
#endif

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 _ui_simple_dialog_press_select(HANDLE_T            h_simple_dialog)
{
      INT32   i4_ret;
      UI_SIMPLE_DIALOG_T*        pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }
      if(pt_ui_simple_dialog->b_info_btn_focused == TRUE)
      {
          if(pt_ui_simple_dialog->pf_ui_simple_dialog_info_cb_fct != NULL)
          {
              pt_ui_simple_dialog->pf_ui_simple_dialog_info_cb_fct();
          }
          return APP_UIR_OK;
      }

      /* Run "Yes" call-back */
      if(pt_ui_simple_dialog->b_answer == TRUE)
      {
          if(pt_ui_simple_dialog->pf_ui_simple_dialog_yes_cb_fct != NULL)
          {
              pt_ui_simple_dialog->pf_ui_simple_dialog_yes_cb_fct();
          }

      }
      /* Run "No" call-back */
      else
      {
          if(pt_ui_simple_dialog->pf_ui_simple_dialog_no_cb_fct != NULL)
          {
              pt_ui_simple_dialog->pf_ui_simple_dialog_no_cb_fct();
          }
      }

      UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
BOOL _ui_simple_dialog_press_other_key(HANDLE_T h_widget, UINT32 ui4_keycode)
{
	INT32   i4_ret;
	UI_SIMPLE_DIALOG_T*        pt_ui_simple_dialog;
	BOOL							b_process = FALSE;

	/* Get simple dialog structure */

	i4_ret = _ui_simple_dialog_get_attach_data(h_widget,
	                                         &pt_ui_simple_dialog);

	UI_CHK_FAIL(i4_ret);

	if(pt_ui_simple_dialog->pf_ui_simple_dialog_other_key_cb_fct != NULL)
	{
		b_process = pt_ui_simple_dialog->pf_ui_simple_dialog_other_key_cb_fct(ui4_keycode);
	}
	return b_process;
}

/*----------------------------------------------------------------------------
 * Name: _ui_vol_ctrl_view_image_init
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
static INT32 _ui_vol_ctrl_view_image_deinit (UI_SLIDER_BAR_T*    pt_ui_slider_bar)
{
    if (pt_ui_slider_bar->h_ui_slider_bar_bk0)
    {
        c_wgl_img_tpl_destroy (pt_ui_slider_bar->h_ui_slider_bar_bk0);
        pt_ui_slider_bar->h_ui_slider_bar_bk0 = NULL_HANDLE;
    }
    if (pt_ui_slider_bar->h_ui_slider_bar_pg_bar)
    {
        c_wgl_img_tpl_destroy (pt_ui_slider_bar->h_ui_slider_bar_pg_bar);
        pt_ui_slider_bar->h_ui_slider_bar_pg_bar = NULL_HANDLE;
    }
    if (pt_ui_slider_bar->h_ui_slider_bar_mute)
    {
        c_wgl_img_tpl_destroy (pt_ui_slider_bar->h_ui_slider_bar_mute);
        pt_ui_slider_bar->h_ui_slider_bar_mute = NULL_HANDLE;
    }
    if (pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red)
    {
        c_wgl_img_tpl_destroy (pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red);
        pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red = NULL_HANDLE;
    }
    if (pt_ui_slider_bar->h_g_ui_vol_mute_fill_leftcap)
    {
        c_wgl_img_tpl_destroy (pt_ui_slider_bar->h_g_ui_vol_mute_fill_leftcap);
        pt_ui_slider_bar->h_g_ui_vol_mute_fill_leftcap = NULL_HANDLE;
    }
    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name: _ui_vol_ctrl_view_image_init
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
static INT32 _ui_vol_ctrl_view_image_init (UI_SLIDER_BAR_T*         pt_ui_slider_bar,
                                           UI_SLIDER_BAR_STYLE_T    e_style)
{
    INT32 i4_ret;

    b_oled = a_is_oled_compensation_support();

   if(e_style == UI_SLIDER_BAR_STYLE_VOL)
   {
        do
        {
            /* Background of slider bar */
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_new_vol_gradient_btm_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_bk0);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            /* Slider Bar's Progress Bar's Bar */
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        b_oled ? &t_g_new_track_fill_oled : &t_g_ui_new_track_fill_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_bar);
            if (i4_ret != WGLR_OK)
            {
                break;
            }

            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_new_vol_active_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_audio);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_new_vo_mute_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_inaudio);
            if (i4_ret != WGLR_OK)
            {
                break;
            }

            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_bt_ui_new_bt_vol_mute_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_inaudio_for_bths);
            if (i4_ret != WGLR_OK)
            {
                break;
            }

            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_new_vol_zoom_active_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_audio);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_new_vo_zoom_mute_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_inaudio);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_new_vol_toast_box_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_toast);
            if (i4_ret != WGLR_OK)
            {
                break;
            }

            /* Silder Bar Mute*/
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_new_vol_gradient_btm_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_mute);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            /* Slider Bar's Progress Bar's Bar Mute*/

#if 0
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        b_oled ? &t_g_track_mute_fill_big_icon_oled : &t_g_ui_new_track_mute_fill_big_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red);

            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        b_oled ? &t_g_new_track_mute_fill_small_icon_oled : &t_g_ui_new_track_mute_fill_small_icon,
                        &pt_ui_slider_bar->h_g_ui_vol_mute_fill_leftcap);
#endif

			i4_ret = c_wgl_img_tpl_create (
									WGL_IMG_ST_NO_SEGMENT,
									&t_g_ui_new_track_mute_fill_big_icon,
									&pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red);

            if (i4_ret != WGLR_OK)
            {
                break;
            }

            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
						&t_g_ui_new_track_mute_fill_small_icon,
                        &pt_ui_slider_bar->h_g_ui_vol_mute_fill_leftcap);

            if (i4_ret != WGLR_OK)
            {
                break;
            }
            pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 = NULL_HANDLE;

            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_bt_ui_new_bt_vol_active_icon,
                        &pt_ui_slider_bar->h_ui_slider_bar_bt_headphone_icon);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_bt_ui_new_bt_vol_active_icon_zoom,
                        &pt_ui_slider_bar->h_ui_slider_bar_zoom_bt_headphone_icon);
            if (i4_ret != WGLR_OK)
            {
                break;
            }

            return APP_UIR_OK;

        } while (0);
   }
   else
   {
      do
        {
            DBG_LOG_PRINT(("imge_init_else_zzz \r\n"));
            /* Background of slider bar */
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_vol_slider_bar_pg_bk0_bmp,
                        &pt_ui_slider_bar->h_ui_slider_bar_bk0);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            /* Slider Bar's Progress Bar's Bar */
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_vol_slider_bar_pg_bar_bmp,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_bar);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            /* Silder Bar Mute*/
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_vol_slider_bar_pg_bk0_mute_bmp,
                        &pt_ui_slider_bar->h_ui_slider_bar_mute);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            /* Slider Bar's Progress Bar's Bar Mute*/
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_vol_slider_bar_pg_bar_mute_bmp,
                        &pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            i4_ret = c_wgl_img_tpl_create (
                        WGL_IMG_ST_NO_SEGMENT,
                        &t_g_ui_vol_mute_fill_leftcap,
                        &pt_ui_slider_bar->h_g_ui_vol_mute_fill_leftcap);
            if (i4_ret != WGLR_OK)
            {
                break;
            }
            pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 = NULL_HANDLE;

            return APP_UIR_OK;
        } while (0);
   }
    _ui_vol_ctrl_view_image_deinit (pt_ui_slider_bar);

    return APP_UIR_FAIL;
}

BOOL _ui_vol_ctrl_view_aud_system_visible(VOID)
{
    A_CFG_CUSTOM_ANALOG_AUD_OUT_T e_aud_out;
    UINT16   ui2_idx = 0;
    INT32    i4_ret;

    i4_ret = a_cfg_custom_get_ana_audio_out(&e_aud_out);
    UI_CHK_FAIL(i4_ret);

    i4_ret = a_cfg_custom_get_speakers_out(&ui2_idx);
    UI_CHK_FAIL(i4_ret);

    if((e_aud_out == A_CFG_CUSTOM_ANALOG_AUD_OUT_VARIABLE) && (ui2_idx == APP_CFG_AUD_AD_SPEAKER_OFF))
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

INT32 a_ui_slider_bar_create_ex (UI_SLIDER_BAR_INIT_EX_T*   pt_ui_slider_bar_init_ex,  /* In  */
                                 HANDLE_T*                  ph_slider)                 /* Out */
{
    INT32       i4_ret;
    INT32       i4_result;
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;
    UI_SLIDER_BAR_INIT_T*   pt_ui_slider_bar_init;

    if (!pt_ui_slider_bar_init_ex)
    {
        return APP_UIR_INV_ARG;
    }

    pt_ui_slider_bar_init = &pt_ui_slider_bar_init_ex->t_ui_slider_bar_init;
    /* Determine Image UI or Graphic UI */

#ifdef APP_IMG_UI
    b_image_ui = TRUE;
#else
    b_image_ui = FALSE;
#endif

    pt_ui_slider_bar =(UI_SLIDER_BAR_T*)c_mem_alloc(sizeof(UI_SLIDER_BAR_T));

    if(pt_ui_slider_bar == NULL)
    {
        return APP_UIR_OUT_OF_MEMORY;
    }
    c_memset(pt_ui_slider_bar, 0 , sizeof(UI_SLIDER_BAR_T));

    /* default value assignment for UI_SLIDER_BAR_T, pending */

    _ui_slider_bar_image_init(pt_ui_slider_bar);

    /* Create content frame widget */

    do
    {
        /* Content Frame */
        i4_result = _ui_slider_create_frm(pt_ui_slider_bar,
                                          0,
                                          pt_ui_slider_bar_init->pf_wdgt_proc,       /* App assigns the pf_wdgt_proc */
                                          pt_ui_slider_bar_init->h_parent,
                                          pt_ui_slider_bar_init->pt_begin_offset
                                          );


        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* txtinfo */
        if (UI_SLIDER_BAR_ATTR_IS_NO_ICON (pt_ui_slider_bar_init_ex->ui4_attr_bits))
        {
            i4_result = _ui_slider_create_txtinfo(pt_ui_slider_bar, TRUE, 0);
        }
        else
        {
            i4_result = _ui_slider_create_txtinfo(pt_ui_slider_bar, FALSE, 0);
        }

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* progressbar - bar type */
        if (UI_SLIDER_BAR_ATTR_IS_NO_ICON (pt_ui_slider_bar_init_ex->ui4_attr_bits))
        {
            i4_result = _ui_slider_create_progressbar_bar(pt_ui_slider_bar, TRUE, 0);
        }
        else
        {
            i4_result = _ui_slider_create_progressbar_bar(pt_ui_slider_bar, FALSE, 0);
        }

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* progressbar - point type */
        i4_result = _ui_slider_create_progressbar_point(pt_ui_slider_bar, 0);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* txtinfo */

        if (UI_SLIDER_BAR_ATTR_IS_NO_ICON (pt_ui_slider_bar_init_ex->ui4_attr_bits))
        {
            i4_result = _ui_slider_create_bar_txt(pt_ui_slider_bar, TRUE, 0);
        }
        else
        {
            i4_result = _ui_slider_create_bar_txt(pt_ui_slider_bar, FALSE, 0);
        }

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

#ifdef IMG_960X540_8888_UI
        /* create icon */
        i4_result = _ui_slider_create_icon(pt_ui_slider_bar);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* create arrow */
        if (UI_SLIDER_BAR_ATTR_IS_NO_ICON (pt_ui_slider_bar_init_ex->ui4_attr_bits))
        {
            i4_result = _ui_slider_create_arrow(pt_ui_slider_bar, TRUE);
        }
        else
        {
            i4_result = _ui_slider_create_arrow(pt_ui_slider_bar, FALSE);
        }

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }
#endif

        /* initialize the alpha value */
        pt_ui_slider_bar->ui1_frm_alpha   = 255;
        pt_ui_slider_bar->ui1_pgbar_alpha = 255;
        pt_ui_slider_bar->ui1_text_alpha  = 255;

        /* e_style */
        pt_ui_slider_bar->e_style = pt_ui_slider_bar_init->e_style;

        /* save the function call back */

        if(pt_ui_slider_bar_init->pf_ui_slider_bar_pos_chg_nfy_fct != NULL)
        {
            pt_ui_slider_bar->pf_ui_slider_bar_pos_chg_nfy_fct =
            pt_ui_slider_bar_init->pf_ui_slider_bar_pos_chg_nfy_fct;
        }

        if(pt_ui_slider_bar_init->pf_ui_slider_bar_get_pos_cb_fct != NULL)
        {
            pt_ui_slider_bar->pf_ui_slider_bar_get_pos_cb_fct =
            pt_ui_slider_bar_init->pf_ui_slider_bar_get_pos_cb_fct;
        }

        /* 1. Set the correct visibility for child widgets */
        _ui_slider_bar_set_visibility_by_style(pt_ui_slider_bar);

        /* 2. Hide the main frame at initial time */
        c_wgl_set_visibility(pt_ui_slider_bar->h_frm_slider, WGL_SW_HIDE);

        /* Return the h_frm_slider handle */
        *ph_slider = pt_ui_slider_bar->h_frm_slider;

        /* Done */
        _ui_slider_bar_set_attach_data(pt_ui_slider_bar->h_frm_slider,
                                       pt_ui_slider_bar);

        i4_ret = APP_UIR_OK;

    } while(0);

    if(i4_ret != APP_UIR_OK)
    {
        /* Release childs*/

        if(pt_ui_slider_bar->h_txt_txtinfo != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_txt_txtinfo);
        }

        if(pt_ui_slider_bar->h_txt_bar_txt != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_txt_bar_txt);
        }

        if(pt_ui_slider_bar->h_pb_bar != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_pb_bar);
        }

        if(pt_ui_slider_bar->h_pb_point != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_pb_point);
        }

        /* Release parent */

        if(pt_ui_slider_bar->h_frm_slider != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_frm_slider);
        }

        /* Release template image */

        if(pt_ui_slider_bar->h_ui_slider_bar_bk0 != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_bk0);
        }

        if(pt_ui_slider_bar->h_ui_slider_bar_pg_bar != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bar);
        }

        if(pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bk0);
        }
        if(pt_ui_slider_bar->h_ui_slider_bar_mute != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_mute);
        }
        if(pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red);
        }

        /* Release the structure */
        c_mem_free(pt_ui_slider_bar);
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_create
 *
 * Description: Create a "Slider Bar" widget.
 *              Slider Bar is a collection of widgets
 *
 * Inputs:    pt_ui_slider_bar_init   - The Slider Bar initialization data
 *
 * Outputs:   ph_slider - Return the "Slider Bar" handle.
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_create(UI_SLIDER_BAR_INIT_T*    pt_ui_slider_bar_init,   /* In  */
                             HANDLE_T*                ph_slider)                 /* Out */
{
    INT32 i4_ret;
    INT32 i4_result;
    UI_SLIDER_BAR_T* pt_ui_slider_bar;

    /* Determine Image UI or Graphic UI */

#ifdef APP_IMG_UI
    b_image_ui = TRUE;
#else
    b_image_ui = FALSE;
#endif

    pt_ui_slider_bar =(UI_SLIDER_BAR_T*)c_mem_alloc(sizeof(UI_SLIDER_BAR_T));

    if(pt_ui_slider_bar == NULL)
    {
        return APP_UIR_OUT_OF_MEMORY;
    }
    c_memset(pt_ui_slider_bar, 0 , sizeof(UI_SLIDER_BAR_T));

    /* default value assignment for UI_SLIDER_BAR_T, pending */

    _ui_slider_bar_image_init(pt_ui_slider_bar);

    /* Create content frame widget */

    do
    {
        /* Content Frame */
        i4_result = _ui_slider_create_frm(pt_ui_slider_bar,
                                          0,
                                          pt_ui_slider_bar_init->pf_wdgt_proc,       /* App assigns the pf_wdgt_proc */
                                          pt_ui_slider_bar_init->h_parent,
                                          pt_ui_slider_bar_init->pt_begin_offset
                                          );


        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* txtinfo */
        i4_result = _ui_slider_create_txtinfo(pt_ui_slider_bar, FALSE, 0);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* progressbar - bar type */
        i4_result = _ui_slider_create_progressbar_bar(pt_ui_slider_bar, FALSE, 0);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* progressbar - point type */
        i4_result = _ui_slider_create_progressbar_point(pt_ui_slider_bar, 0);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* txtinfo */

        i4_result = _ui_slider_create_bar_txt(pt_ui_slider_bar, FALSE, 0);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* initialize the alpha value */
        pt_ui_slider_bar->ui1_frm_alpha   = 255;
        pt_ui_slider_bar->ui1_pgbar_alpha = 255;
        pt_ui_slider_bar->ui1_text_alpha  = 255;

        /* e_style */
        pt_ui_slider_bar->e_style = pt_ui_slider_bar_init->e_style;

        /* save the function call back */

        if(pt_ui_slider_bar_init->pf_ui_slider_bar_pos_chg_nfy_fct != NULL)
        {
            pt_ui_slider_bar->pf_ui_slider_bar_pos_chg_nfy_fct =
            pt_ui_slider_bar_init->pf_ui_slider_bar_pos_chg_nfy_fct;
        }

        if(pt_ui_slider_bar_init->pf_ui_slider_bar_get_pos_cb_fct != NULL)
        {
            pt_ui_slider_bar->pf_ui_slider_bar_get_pos_cb_fct =
            pt_ui_slider_bar_init->pf_ui_slider_bar_get_pos_cb_fct;
        }

        /* 1. Set the correct visibility for child widgets */
        _ui_slider_bar_set_visibility_by_style(pt_ui_slider_bar);

        /* 2. Hide the main frame at initial time */
        c_wgl_set_visibility(pt_ui_slider_bar->h_frm_slider, WGL_SW_HIDE);

        /* Return the h_frm_slider handle */
        *ph_slider = pt_ui_slider_bar->h_frm_slider;

        /* Done */
        _ui_slider_bar_set_attach_data(pt_ui_slider_bar->h_frm_slider,
                                       pt_ui_slider_bar);

        i4_ret = APP_UIR_OK;

    } while(0);

    if(i4_ret != APP_UIR_OK)
    {
        /* Release childs*/

        if(pt_ui_slider_bar->h_txt_txtinfo != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_txt_txtinfo);
        }

        if(pt_ui_slider_bar->h_txt_bar_txt != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_txt_bar_txt);
        }

        if(pt_ui_slider_bar->h_pb_bar != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_pb_bar);
        }

        if(pt_ui_slider_bar->h_pb_point != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_pb_point);
        }

        /* Release parent */

        if(pt_ui_slider_bar->h_frm_slider != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_frm_slider);
        }

        /* Release template image */

        if(pt_ui_slider_bar->h_ui_slider_bar_bk0 != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_bk0);
        }

        if(pt_ui_slider_bar->h_ui_slider_bar_pg_bar != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bar);
        }

        if(pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bk0);
        }

        /* Release the structure */
        c_mem_free(pt_ui_slider_bar);
    }

    return i4_ret;
}
/*----------------------------------------------------------------------------
 * Name: _ui_vol_ctrl_view_reset
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
static INT32 _ui_vol_ctrl_view_reset(UI_SLIDER_BAR_T*       pt_ui_slider_bar,
                                     UI_SLIDER_BAR_STYLE_T  e_style)

{
    INT32               i4_ret;
    GL_RECT_T           t_rect;
    WGL_FONT_INFO_T     t_fnt_info;
    UINT8               ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;

    if(e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        /* progressbar - main frame  */
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_X,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_W,
                         UI_SLIDER_BAR_DEF_CONTENT_FRA_GRADIENT_H);

        i4_ret = c_wgl_move(pt_ui_slider_bar->h_frm_slider,
                             &t_rect,
                             WGL_NO_AUTO_REPAINT);
        UI_CHK_FAIL(i4_ret);

        /* progressbar - bar  */
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_X,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_W,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_H);

        i4_ret = c_wgl_move(pt_ui_slider_bar->h_pb_bar,
                            &t_rect,
                            WGL_NO_AUTO_REPAINT);
        UI_CHK_FAIL(i4_ret);

        /* progressbar - point  */
        SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_X,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_W,
                         UI_SLIDER_BAR_PROGRESS_BAR_LINE_H);

        i4_ret = c_wgl_move(pt_ui_slider_bar->h_pb_point,
                            &t_rect,
                            WGL_NO_AUTO_REPAINT);
        UI_CHK_FAIL(i4_ret);

        /* toast - icon  */
        SET_RECT_BY_SIZE(&t_rect,
                          UI_SLIDER_BAR_DEF_CONTENT_TOAST_X,
                          UI_SLIDER_BAR_DEF_CONTENT_TOAST_Y,
                          UI_SLIDER_BAR_DEF_CONTENT_TOAST_W,
                          UI_SLIDER_BAR_DEF_CONTENT_TOAST_H);

        i4_ret = c_wgl_move(pt_ui_slider_bar->h_toast,
                            &t_rect,
                            WGL_NO_AUTO_REPAINT);
        UI_CHK_FAIL(i4_ret);

        i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
        UI_CHK_FAIL(i4_ret);

        if(ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
        {
            /* zoom audio - icon  */
            SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_zoom_audio,
                                &t_rect,
                                WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);

            /* inaudio - icon  */
            SET_RECT_BY_SIZE(&t_rect,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_X,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_Y,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_W,
                         UI_SLIDER_BAR_DEF_CONTENT_ZOOM_MUTE_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_zoom_inaudio,
                                 &t_rect,
                                 WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);
        }
        else
        {
            /* audio - icon  */
            SET_RECT_BY_SIZE(&t_rect,
                              UI_SLIDER_BAR_DEF_CONTENT_AUDIO_X,
                              UI_SLIDER_BAR_DEF_CONTENT_AUDIO_Y,
                              UI_SLIDER_BAR_DEF_CONTENT_AUDIO_W,
                              UI_SLIDER_BAR_DEF_CONTENT_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_audio,
                                &t_rect,
                                WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);

            /* inaudio - icon  */
            SET_RECT_BY_SIZE(&t_rect,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_X,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_Y,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_W,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_inaudio,
                                 &t_rect,
                                 WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);

            SET_RECT_BY_SIZE(&t_rect,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_X,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_Y,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_W,
                              UI_SLIDER_BAR_DEF_CONTENT_MUTE_AUDIO_H);

            i4_ret = c_wgl_move(pt_ui_slider_bar->h_inaudio_for_bths,
                                 &t_rect,
                                 WGL_NO_AUTO_REPAINT);
            UI_CHK_FAIL(i4_ret);
        }

        return APP_UIR_OK;
    }
    else
    {
        /* progressbar - main frame  */
        SET_RECT_BY_SIZE(&t_rect,
                         UI_VOL_BAR_BASE_FRM_X,
                         UI_VOL_BAR_BASE_FRM_Y,
                         UI_VOL_BAR_BASE_FRM_W,
                         UI_VOL_BAR_BASE_FRM_H);
        i4_ret = c_wgl_move(pt_ui_slider_bar->h_frm_slider,
                             &t_rect,
                             WGL_NO_AUTO_REPAINT);
        if(i4_ret != APP_UIR_OK)
        {
            return APP_UIR_FAIL;
        }

        /* progressbar - bar  */
        SET_RECT_BY_SIZE(&t_rect,
                         UI_VOL_BAR_PG_BAR_X,
                         UI_VOL_BAR_PG_BAR_Y,
                         UI_VOL_BAR_PG_BAR_W,
                         UI_VOL_BAR_PG_BAR_H);
        i4_ret = c_wgl_move(pt_ui_slider_bar->h_pb_bar,
                             &t_rect,
                             WGL_NO_AUTO_REPAINT);
        if(i4_ret != APP_UIR_OK)
        {
            return APP_UIR_FAIL;
        }

        /* progressbar - txt  */
        SET_RECT_BY_SIZE(&t_rect,
                          UI_VOL_PG_BAR_TEXT_X,
                          UI_VOL_PG_BAR_TEXT_Y,
                          UI_VOL_PG_BAR_TEXT_W,
                          UI_VOL_PG_BAR_TEXT_H);

        i4_ret = c_wgl_move(pt_ui_slider_bar->h_txt_bar_txt,
                            &t_rect,
                            WGL_NO_AUTO_REPAINT);

        if(i4_ret != APP_UIR_OK)
        {
            return APP_UIR_FAIL;
        }
            /* Set Font */
        c_memset(& t_fnt_info, 0, sizeof(WGL_FONT_INFO_T));
        c_strcpy(t_fnt_info.a_c_font_name, SN_FONT_DEFAULT_SMALL);
        t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                               WGL_CMD_GL_SET_FONT,
                               WGL_PACK(&t_fnt_info),
                               NULL);
        UI_CHK_FAIL(i4_ret);

        return APP_UIR_OK;
    }
}

/*----------------------------------------------------------------------------
 * Name: a_ui_volume_bar_create
 *
 * Description: Create a "Volume Slider Bar" widget.
 *              Slider Bar is a collection of widgets
 *
 * Inputs:    pt_ui_slider_bar_init   - The Slider Bar initialization data
 *
 * Outputs:   ph_slider - Return the "vol Slider Bar" handle.
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_vol_ctrl_view_create(UI_SLIDER_BAR_INIT_T*    pt_ui_slider_bar_init,   /* In  */
                                HANDLE_T*                ph_slider)               /* Out */
{
    INT32 i4_ret;
    INT32 i4_result;
    UI_SLIDER_BAR_T* pt_ui_slider_bar;

    /* Determine Image UI or Graphic UI */
#ifdef APP_IMG_UI
    b_image_ui = TRUE;
#else
    b_image_ui = FALSE;
#endif

    pt_ui_slider_bar = (UI_SLIDER_BAR_T*)c_mem_alloc(sizeof(UI_SLIDER_BAR_T));

    if (pt_ui_slider_bar == NULL)
    {
        return APP_UIR_OUT_OF_MEMORY;
    }
    c_memset(pt_ui_slider_bar, 0 ,sizeof(UI_SLIDER_BAR_T));

    /* Create content frame widget */
    do
    {
        i4_result = _ui_vol_ctrl_view_image_init (pt_ui_slider_bar,
                                                  pt_ui_slider_bar_init->e_style);
        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }
        /* Content Frame */
        i4_result = _ui_slider_create_frm(pt_ui_slider_bar,
                                          pt_ui_slider_bar_init->e_style,
                                          pt_ui_slider_bar_init->pf_wdgt_proc,       /* App assigns the pf_wdgt_proc */
                                          pt_ui_slider_bar_init->h_parent,
                                          pt_ui_slider_bar_init->pt_begin_offset
                                          );
        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* txtinfo */
        i4_result = _ui_slider_create_txtinfo (pt_ui_slider_bar, FALSE, pt_ui_slider_bar_init->e_style);
        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* progressbar - bar type */
        i4_result = _ui_slider_create_progressbar_bar (pt_ui_slider_bar, FALSE, pt_ui_slider_bar_init->e_style);
        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* progressbar - point type */
        i4_result = _ui_slider_create_progressbar_point(pt_ui_slider_bar, pt_ui_slider_bar_init->e_style);
        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* txtinfo */
        i4_result = _ui_slider_create_bar_txt(pt_ui_slider_bar, FALSE, pt_ui_slider_bar_init->e_style);
        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* initialize the alpha value */
        pt_ui_slider_bar->ui1_frm_alpha   = 255;
        pt_ui_slider_bar->ui1_pgbar_alpha = 255;
        pt_ui_slider_bar->ui1_text_alpha  = 255;

        /* e_style */
        pt_ui_slider_bar->e_style = pt_ui_slider_bar_init->e_style;

        /* save the function call back */

        if(pt_ui_slider_bar_init->pf_ui_slider_bar_pos_chg_nfy_fct != NULL)
        {
            pt_ui_slider_bar->pf_ui_slider_bar_pos_chg_nfy_fct =
            pt_ui_slider_bar_init->pf_ui_slider_bar_pos_chg_nfy_fct;
        }

        if(pt_ui_slider_bar_init->pf_ui_slider_bar_get_pos_cb_fct != NULL)
        {
            pt_ui_slider_bar->pf_ui_slider_bar_get_pos_cb_fct =
            pt_ui_slider_bar_init->pf_ui_slider_bar_get_pos_cb_fct;
        }

        _ui_slider_bar_set_visibility_by_style(pt_ui_slider_bar);

        c_wgl_set_visibility(pt_ui_slider_bar->h_frm_slider, WGL_SW_HIDE);

        *ph_slider = pt_ui_slider_bar->h_frm_slider;

        _ui_slider_bar_set_attach_data(pt_ui_slider_bar->h_frm_slider,
                                       pt_ui_slider_bar);

        i4_ret = APP_UIR_OK;
        _ui_vol_ctrl_view_reset (pt_ui_slider_bar, pt_ui_slider_bar_init->e_style);
    } while(0);

    if (i4_ret != APP_UIR_OK)
    {
        a_ui_slider_bar_destroy (pt_ui_slider_bar->h_frm_slider);

        /* Release the structure */
        c_mem_free(pt_ui_slider_bar);
    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_destroy
 *
 * Description: Destroy the Slider Bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_destroy(HANDLE_T    h_frm_slider)
{
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));

    if (pt_ui_slider_bar->h_txt_txtinfo != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_txt_txtinfo);
        pt_ui_slider_bar->h_txt_txtinfo = NULL_HANDLE;
    }

    if (pt_ui_slider_bar->h_txt_bar_txt != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_txt_bar_txt);
        pt_ui_slider_bar->h_txt_bar_txt = NULL_HANDLE;
    }

    if (pt_ui_slider_bar->h_pb_bar != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_pb_bar);
        pt_ui_slider_bar->h_pb_bar = NULL_HANDLE;
    }

    if (pt_ui_slider_bar->h_pb_point != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_pb_point);
        pt_ui_slider_bar->h_pb_point = NULL_HANDLE;
    }

    /* Release parent */
    if(pt_ui_slider_bar->h_frm_slider != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_frm_slider);
        pt_ui_slider_bar->h_frm_slider = NULL_HANDLE;
    }

    /* Release template image */
    _ui_vol_ctrl_view_image_deinit (pt_ui_slider_bar);
    if (pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bk0);
        pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 = NULL_HANDLE;
    }

    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_destroy
 *
 * Description: Destroy the Slider Bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_vol_ctrl_view_destroy (HANDLE_T    h_frm_slider)
{
    INT32 i4_ret;
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;
    UINT8                   ui1_zoom_mode_value = APP_CFG_CUST_ZOOM_MODE_OFF;

    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));

    i4_ret = a_cfg_cust_get_zoom_mode(&ui1_zoom_mode_value);
    UI_CHK_FAIL(i4_ret);

    if(pt_ui_slider_bar->h_txt_txtinfo != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_txt_txtinfo);
    }

    if(pt_ui_slider_bar->h_toast!= NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_toast);
    }
    if(pt_ui_slider_bar->h_audio!= NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_audio);
    }
    if(pt_ui_slider_bar->h_inaudio!= NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_inaudio);
    }
    if(pt_ui_slider_bar->h_inaudio_for_bths != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_inaudio_for_bths);
    }
    if(ui1_zoom_mode_value == APP_CFG_CUST_ZOOM_MODE_ON)
    {
        if(pt_ui_slider_bar->h_zoom_audio!= NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_zoom_audio);
        }
        if(pt_ui_slider_bar->h_zoom_inaudio!= NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_slider_bar->h_zoom_inaudio);
        }
    }

    if(pt_ui_slider_bar->h_txt_bar_txt != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_txt_bar_txt);
    }


    if(pt_ui_slider_bar->h_pb_bar != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_pb_bar);
    }

    if(pt_ui_slider_bar->h_pb_point != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_pb_point);
    }

    if(pt_ui_slider_bar->h_frm_slider != NULL_HANDLE)
    {
        c_wgl_destroy_widget(pt_ui_slider_bar->h_frm_slider);
    }

    if(pt_ui_slider_bar->h_ui_slider_bar_bk0 != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_bk0);
    }

    if(pt_ui_slider_bar->h_ui_slider_bar_pg_bar != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bar);
    }

    if(pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bk0);
    }

    if(pt_ui_slider_bar->h_ui_slider_bar_mute != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_mute);
    }
    if(pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_ui_slider_bar_pg_bar_red);
    }
    if(pt_ui_slider_bar->h_g_ui_vol_mute_fill_leftcap != NULL_HANDLE)
    {
        c_wgl_img_tpl_destroy(pt_ui_slider_bar->h_g_ui_vol_mute_fill_leftcap);
    }

    c_mem_free(pt_ui_slider_bar);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_show
 *
 * Description: Show the slider bar. First it will reset the PGBAR's value,
 *              And then show the slider bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_show(HANDLE_T            h_frm_slider, 
                           BOOL                is_headphone_vol)
{
      INT32   i4_ret;
      INT32   i4_pos = 0;
      UI_SLIDER_BAR_T*        pt_ui_slider_bar;
      WGL_IMG_INFO_T          t_img_info;

      /* Get slider bar structure */
      UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                              &pt_ui_slider_bar));

      if(is_headphone_vol == FALSE)
      {
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_audio;
            t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_audio;
            t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_audio;

            i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_audio,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK(WGL_IMG_FG),
                                  WGL_PACK(&t_img_info));

            UI_CHK_FAIL(i4_ret);

            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_audio;
            t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_audio;
            t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_zoom_audio;

            i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_zoom_audio,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK(WGL_IMG_FG),
                                  WGL_PACK(&t_img_info));

            UI_CHK_FAIL(i4_ret);
      }
      else
      {
            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_bt_headphone_icon;
            t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_bt_headphone_icon;
            t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_bt_headphone_icon;

            i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_audio,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK(WGL_IMG_FG),
                                  WGL_PACK(&t_img_info));

            UI_CHK_FAIL(i4_ret);

            t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
            t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_zoom_bt_headphone_icon;
            t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_zoom_bt_headphone_icon;
            t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_zoom_bt_headphone_icon;

            i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_zoom_audio,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK(WGL_IMG_FG),
                                  WGL_PACK(&t_img_info));

            UI_CHK_FAIL(i4_ret);
      }

      /* Update the PGBAR value */
      if(pt_ui_slider_bar->pf_ui_slider_bar_get_pos_cb_fct != NULL)
      {
          i4_pos = pt_ui_slider_bar->pf_ui_slider_bar_get_pos_cb_fct();

          /* Set value to widget */
          a_ui_slider_bar_set_pos(h_frm_slider, i4_pos, is_headphone_vol);
          pt_ui_slider_bar->i4_pos = i4_pos;
      }

      UI_LOG_ON_FAIL(_ui_slider_bar_adjust_font_size(pt_ui_slider_bar));
      /* Set correct visibility for all child widgets */
      _ui_slider_bar_set_visibility_by_style(pt_ui_slider_bar);
      /*i4_ret = c_wgl_show(pt_ui_slider_bar->h_frm_slider, WGL_SW_NORMAL);*/
      i4_ret = c_wgl_set_visibility(pt_ui_slider_bar->h_frm_slider, WGL_SW_NORMAL);
      UI_CHK_FAIL(i4_ret);
      c_wgl_repaint(pt_ui_slider_bar->h_frm_slider,NULL,TRUE);
      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_repaint
 *
 * Description: Repaint the whole Slider Bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_repaint(HANDLE_T            h_frm_slider)
{
      INT32   i4_ret;

      /* Repaint it */
      i4_ret = c_wgl_repaint(h_frm_slider, NULL, FALSE);
      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_repaint_pgbar
 *
 * Description: Repaint the Slider Bar's PGBAR only
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_repaint_pgbar(HANDLE_T            h_frm_slider)
{
      INT32   i4_ret;
      UI_SLIDER_BAR_T*        pt_ui_slider_bar;

      /* Get slider bar structure */

      UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                              &pt_ui_slider_bar));
      /* Repaint the pgbar only */
      i4_ret = c_wgl_repaint(pt_ui_slider_bar->h_pb_bar, NULL, TRUE);
      i4_ret = c_wgl_repaint(pt_ui_slider_bar->h_pb_point, NULL, TRUE);
      i4_ret = c_wgl_repaint(pt_ui_slider_bar->h_txt_bar_txt, NULL, TRUE);
      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}



/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_title
 *
 * Description: Set the slider bar's title.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         w2s_title - The UTF16 title string
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_title(HANDLE_T            h_frm_slider,
                                UTF16_T*            w2s_title)
{
      INT32    i4_ret;
      UI_SLIDER_BAR_T*        pt_ui_slider_bar;

      /* Get slider bar structure */
      UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                              &pt_ui_slider_bar));

      c_uc_w2s_strncpy(pt_ui_slider_bar->w2s_title, w2s_title, UI_SLIDER_BAR_TITLE_MAX-1);

      i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_txtinfo,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(w2s_title),
                            WGL_PACK(c_uc_w2s_strlen(w2s_title)));

      UI_CHK_FAIL(i4_ret);
      return APP_UIR_OK;
}


/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_hide
 *
 * Description: Hide the slider bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_hide(HANDLE_T            h_frm_slider)
{
      INT32    i4_ret;
      UI_SLIDER_BAR_T*        pt_ui_slider_bar;

      /* Get slider bar structure */
      UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                     &pt_ui_slider_bar));
      i4_ret = c_wgl_set_visibility(pt_ui_slider_bar->h_frm_slider, WGL_SW_HIDE);
      UI_CHK_FAIL(i4_ret);
      c_wgl_repaint(pt_ui_slider_bar->h_frm_slider,NULL,TRUE);
      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_alpha
 *
 * Description: Set the current alpha level of the Slider Bar
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         e_comp_id    - Component ID
 *
 * Outputs: ui1_alpha - The alpha level of the Slider Bar
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_alpha(
            HANDLE_T                 h_frm_slider,
            UI_SLIDER_BAR_COMP_ID_T  e_comp_id,
            UINT8                    ui1_alpha)
{
    INT32                   i4_ret;
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));

    if(e_comp_id == UI_SLIDER_BAR_COMP_ID_FRAME)
    {
        /* Save the current alpha value */
        pt_ui_slider_bar->ui1_frm_alpha = ui1_alpha;

        i4_ret = c_wgl_set_alpha(pt_ui_slider_bar->h_frm_slider,
                                 ui1_alpha);
        UI_CHK_FAIL(i4_ret);
    }
    else if(e_comp_id == UI_SLIDER_BAR_COMP_ID_PGBAR)
    {
        /* Save the current alpha value */
        pt_ui_slider_bar->ui1_pgbar_alpha = ui1_alpha;

        i4_ret = c_wgl_set_alpha(pt_ui_slider_bar->h_pb_point,
                                 ui1_alpha);
        UI_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_set_alpha(pt_ui_slider_bar->h_pb_bar,
                                 ui1_alpha);
        UI_CHK_FAIL(i4_ret);
    }
    else if(e_comp_id == UI_SLIDER_BAR_COMP_ID_TEXT)
    {
        /* Save the current alpha value */
        pt_ui_slider_bar->ui1_text_alpha = ui1_alpha;

        i4_ret = c_wgl_set_alpha(pt_ui_slider_bar->h_txt_bar_txt,
                                 ui1_alpha);
        UI_CHK_FAIL(i4_ret);

        i4_ret = c_wgl_set_alpha(pt_ui_slider_bar->h_txt_txtinfo,
                                 ui1_alpha);
        UI_CHK_FAIL(i4_ret);
    }
    else
    {
        return APP_UIR_INV_ARG;
    }

    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_get_alpha
 *
 * Description: Get the current alpha level of the Slider Bar
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         e_comp_id    - Component ID
 *
 * Outputs: pui1_alpha - The pointer to value to save the current alpha level.
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_get_alpha(
                HANDLE_T                 h_frm_slider,
                UI_SLIDER_BAR_COMP_ID_T  e_comp_id,
                UINT8*                   pui1_alpha)
{
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));

    /* return the current alpha value */
    if(e_comp_id == UI_SLIDER_BAR_COMP_ID_FRAME)
    {
        *pui1_alpha = pt_ui_slider_bar->ui1_frm_alpha;
    }
    else if(e_comp_id == UI_SLIDER_BAR_COMP_ID_PGBAR)
    {
        *pui1_alpha = pt_ui_slider_bar->ui1_pgbar_alpha;
    }
    else if(e_comp_id == UI_SLIDER_BAR_COMP_ID_TEXT)
    {
        *pui1_alpha = pt_ui_slider_bar->ui1_text_alpha;
    }
    else
    {
        return APP_UIR_INV_ARG;
    }

    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_pos
 *
 * Description: Set the position of the Slider Bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         i4_pos - The position of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_pos(
            HANDLE_T    h_frm_slider,
            INT32       i4_pos,
            BOOL        is_headphone_vol)
{
    INT32                   i4_ret;
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;
    GL_RECT_T         	    t_rect;

    CHAR                    s_pos[6] = "";
    UTF16_T                 w2s_str[6];

    #ifdef APP_CEC_MENU
    UINT8           ui1_icl_val;
    SIZE_T          z_size = sizeof(UINT8);
    #endif

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    /* Clear value if necessary */
    c_memset(w2s_str, 0, sizeof(UTF16_T) * 6);

    /* Set value to object */
    pt_ui_slider_bar->i4_pos = i4_pos;

    /* Set value to widget */
    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_bar,
                           WGL_CMD_PG_SET_POS,
                           WGL_PACK(i4_pos),
                           NULL);
    UI_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_point,
                           WGL_CMD_PG_SET_POS,
                           WGL_PACK(i4_pos),
                           NULL);
    UI_CHK_FAIL(i4_ret);

    if (pt_ui_slider_bar->e_style == UI_SLIDER_BAR_STYLE_VOL)
    {
        #ifdef APP_CEC_MENU
        z_size = ICL_RECID_CEC_SAC_STATUS_SIZE;
        i4_ret = a_icl_get(ICL_MAKE_ID (ICL_GRPID_CEC, ICL_RECID_CEC_SAC_STATUS),
                           &ui1_icl_val,
                           &z_size);

        if(ICL_CEC_SAC_STATUS_ON == ui1_icl_val || _ui_vol_ctrl_view_aud_system_visible())
        {
            i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                                  WGL_CMD_TEXT_SET_ALIGN,
                                  WGL_PACK(WGL_AS_CENTER_TOP),
                                  NULL);
            UI_CHK_FAIL(i4_ret);

        }
        else
        #endif
        {
            i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_txt_bar_txt,
                                  WGL_CMD_TEXT_SET_ALIGN,
                                  WGL_PACK(WGL_AS_CENTER_BOTTOM),
                                  NULL);
            UI_CHK_FAIL(i4_ret);
        }

        if (is_headphone_vol)
        {
            DBG_LOG_PRINT(("bt i4_pos = %d, x coord = %lf, bar_line_x = %d \n", i4_pos, (UI_SLIDER_BAR_PROGRESS_BAR_LINE_X-i4_pos*7.559), UI_SLIDER_BAR_PROGRESS_BAR_LINE_X));
            SET_RECT_BY_SIZE(&t_rect,
                            (UI_SLIDER_BAR_PROGRESS_BAR_LINE_X-i4_pos*7.559),
                            UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y,
                            UI_SLIDER_BAR_PROGRESS_BAR_LINE_W,
                            UI_SLIDER_BAR_PROGRESS_BAR_LINE_H);
        }
        else
        {
            SET_RECT_BY_SIZE(&t_rect,
                            (UI_SLIDER_BAR_PROGRESS_BAR_LINE_X-i4_pos*9.6),
                            UI_SLIDER_BAR_PROGRESS_BAR_LINE_Y,
                            UI_SLIDER_BAR_PROGRESS_BAR_LINE_W,
                            UI_SLIDER_BAR_PROGRESS_BAR_LINE_H);
        }

        i4_ret = c_wgl_move(pt_ui_slider_bar->h_pb_bar, &t_rect, WGL_NO_AUTO_REPAINT);
        UI_CHK_FAIL(i4_ret);


        if (is_headphone_vol)
        {
            strcpy(s_pos, " ");      
        }
        else 
        {
            c_sprintf(s_pos, "%ld", i4_pos);
        }
    
        /* Set value to bar_txt */
        c_uc_ps_to_w2s(s_pos, w2s_str, c_strlen(s_pos));

        i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_txt_bar_txt,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(w2s_str),
                            WGL_PACK(c_uc_w2s_strlen(w2s_str)));
        UI_CHK_FAIL(i4_ret);
      

        return APP_UIR_OK;
    }
    else
    {
        if (is_headphone_vol)
        {
            strcpy(s_pos, " ");      
        }
        else 
        {
            c_sprintf(s_pos, "%ld", i4_pos);
        }
    
        c_uc_ps_to_w2s(s_pos, w2s_str, c_strlen(s_pos));

        i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_txt_bar_txt,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(w2s_str),
                            WGL_PACK(c_uc_w2s_strlen(w2s_str)));
        UI_CHK_FAIL(i4_ret);

        return APP_UIR_OK;

    }
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_get_pos
 *
 * Description: Get the current position of the Slider Bar
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs: pi4_pos - The pointer to value to save the current position.
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_get_pos(
                HANDLE_T    h_frm_slider,
                INT32*      pi4_pos)
{
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    *pi4_pos = pt_ui_slider_bar->i4_pos;

    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_style
 *
 * Description: Set the style of the Slider Bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         e_style - The new style.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_style(HANDLE_T                 h_frm_slider,
                                UI_SLIDER_BAR_STYLE_T    e_style)
{
     UI_SLIDER_BAR_T*        pt_ui_slider_bar;

     /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                             &pt_ui_slider_bar));
     pt_ui_slider_bar->e_style = e_style;
     _ui_slider_bar_set_visibility_by_style(pt_ui_slider_bar);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_fast_mode_attr
 *
 * Description:
 *
 * Inputs:
 *
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_fast_mode_attr(HANDLE_T                 h_frm_slider,
                                         WGL_PG_FAST_MODE_ATTR_T* pt_pg_fast_mode_attr)
{
     INT32    i4_ret;
     UI_SLIDER_BAR_T*        pt_ui_slider_bar;

     /* Get slider bar structure */
     UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                             &pt_ui_slider_bar));
     /* Set fast mode attr to PGBAR-BAR */
     i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                           WGL_CMD_PG_SET_FAST_MODE_ATTR,
                           WGL_PACK(pt_pg_fast_mode_attr),
                           NULL);

     UI_CHK_FAIL(i4_ret);

     /* Set fast mode attr to PGBAR-POINT */
     i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                           WGL_CMD_PG_SET_FAST_MODE_ATTR,
                           WGL_PACK(pt_pg_fast_mode_attr),
                           NULL);

     UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_key_map
 *
 * Description:
 *
 * Inputs:
 *
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_key_map(HANDLE_T             h_frm_slider,
                                  WGL_PG_KEY_MAP_T*    pt_pg_key_map)
{
     INT32    i4_ret;
     UI_SLIDER_BAR_T*        pt_ui_slider_bar;

     /* Get slider bar structure */
     UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                             &pt_ui_slider_bar));
     /* Set Key Map  to PGBAR-BAR */
     i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                           WGL_CMD_PG_SET_KEY_MAP,
                           WGL_PACK(pt_pg_key_map),
                           NULL);

     UI_CHK_FAIL(i4_ret);

     /* Set Key Map to PGBAR-POINT */
     i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                           WGL_CMD_PG_SET_KEY_MAP,
                           WGL_PACK(pt_pg_key_map),
                           NULL);

     UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_get_key_map
 *
 * Description:
 *
 * Inputs:
 *
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_get_key_map(HANDLE_T             h_frm_slider,
                                  WGL_PG_KEY_MAP_T*    pt_pg_key_map)
{
     UI_SLIDER_BAR_T*        pt_ui_slider_bar;

     /* Get slider bar structure */
     UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                             &pt_ui_slider_bar));
     if(pt_ui_slider_bar->e_style == UI_SLIDER_BAR_STYLE_BAR)
     {
        /* Set Key Map to PGBAR-BAR */
         c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                               WGL_CMD_PG_GET_KEY_MAP,
                               WGL_PACK(pt_pg_key_map),
                               NULL);

     }
     else
     {
     /* Set Key Map to PGBAR-POINT */

         c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                               WGL_CMD_PG_GET_KEY_MAP,
                               WGL_PACK(pt_pg_key_map),
                               NULL);
     }

    return APP_UIR_OK;
}



/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_get_style
 *
 * Description: Get the style of the Slider Bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs: pe_style - the current style of the Slider Bar.
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_get_style(HANDLE_T                 h_frm_slider,
                                UI_SLIDER_BAR_STYLE_T*   pe_style)
{
     UI_SLIDER_BAR_T*   pt_ui_slider_bar;

     /* Get slider bar structure */
     UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                             &pt_ui_slider_bar));
     *pe_style = pt_ui_slider_bar->e_style;
     _ui_slider_bar_set_visibility_by_style(pt_ui_slider_bar);

    return APP_UIR_OK;
}


/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_focus
 *
 * Description: Set focus to the slider_bar. (Without repaint)
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_focus(HANDLE_T  h_frm_slider, BOOL b_repaint)
{
     c_wgl_set_focus(h_frm_slider, b_repaint);

     return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_range
 *
 * Description: Set the range of the slider bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         i4_min - The minimum value of the Slider Bar.
 *         i4_max - The maximum value of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_range(HANDLE_T    h_frm_slider,
                                INT32       i4_min,
                                INT32       i4_max)
{
    INT32               i4_ret;
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));

    pt_ui_slider_bar->i4_max = i4_max;
    pt_ui_slider_bar->i4_min = i4_min;

    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_bar,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK(i4_min),
                           WGL_PACK(i4_max));
    UI_CHK_FAIL(i4_ret);

    i4_ret = c_wgl_do_cmd (pt_ui_slider_bar->h_pb_point,
                           WGL_CMD_PG_SET_RANGE,
                           WGL_PACK(i4_min),
                           WGL_PACK(i4_max));
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_get_range
 *
 * Description: Get the range of the slider bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         pi4_min - The current minimum value of the Slider Bar.
 *         pi4_max - The current maximum value of the Slider Bar.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_get_range(HANDLE_T    h_frm_slider,
                                INT32*      pi4_min,
                                INT32*      pi4_max)
{
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    *pi4_min = pt_ui_slider_bar->i4_min;
    *pi4_max = pt_ui_slider_bar->i4_max;

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_pgbar_point_size
 *
 * Description: Set the BLOCK POINT size of the slider bar.
 *              ps. This API is for e_style = UI_SLIDER_BAR_STYLE_POINT only.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         i2_w - The width of the block point.
 *         i2_h - The height of the block point.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_pgbar_point_size(HANDLE_T    h_frm_slider,
                                           INT16       i2_w,
                                           INT16       i2_h)
{
    INT32               i4_ret;
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_point,
                          WGL_CMD_PG_SET_BLK_PT_SIZE,
                          WGL_PACK(i2_w),
                          WGL_PACK(i2_h));


    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_pos_chg_nfy_fct
 *
 * Description: Set the "Position Change" callback function of the Slider Bar.
 *              The callback function is called when the progressbar's value
 *              has been changed.
 *
 * Inputs:  h_frm_slider - The handle of the Slider Bar.
 *          pf_get_pos - The "Get position" callback function.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_pos_chg_nfy_fct(HANDLE_T                   h_frm_slider,
                                          ui_slider_bar_pos_chg_nfy_fct pf_set_pos)
{
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    pt_ui_slider_bar->pf_ui_slider_bar_pos_chg_nfy_fct = pf_set_pos;

    return APP_UIR_OK;
}



/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_get_pos_cb_fct
 *
 * Description: Set the "Get position" callback function of the Slider Bar.
 *              The callback function is called when showing the Slider Bar.
 *
 * Inputs:  h_frm_slider - The handle of the Slider Bar.
 *          pf_get_pos - The "Get position" callback function.
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_get_pos_cb_fct(HANDLE_T                  h_frm_slider,
                                         ui_slider_bar_get_pos_cb_fct pf_get_pos)
{
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    pt_ui_slider_bar->pf_ui_slider_bar_get_pos_cb_fct = pf_get_pos;

    return APP_UIR_OK;
}


/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_default_msg_proc
 *
 * Description: The default message processing function of the Slider Bar.
 *
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_default_msg_proc(
                HANDLE_T            h_widget,   /* Frame */
                UINT32              ui4_msg,
                VOID*               pv_param1,
                VOID*               pv_param2,
                BOOL                is_headphone_vol)
{

    UI_SLIDER_BAR_T*   pt_ui_slider_bar;
    HANDLE_T           h_child_widget;
    WGL_NOTIFY_DATA_T* pt_wgl_nfy_data;

    switch(ui4_msg)
    {
        case WGL_MSG_NOTIFY:
        {
        /* First, check if the NOTIFICATION is coming from PGBAR-BAR or PGBAR-POINT */
        /* It means, the value of the PGBAR has been changed */
        /* So, notify the APP */

            UI_LOG_ON_FAIL(_ui_slider_bar_get_attach_data(h_widget,
                                           &pt_ui_slider_bar));

            h_child_widget  = (HANDLE_T) pv_param1;
            pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

            if(pt_wgl_nfy_data->ui4_nc_code == WGL_NC_PG_POS_CHANGE)
            {
                if(h_child_widget == pt_ui_slider_bar->h_pb_bar ||
                   h_child_widget == pt_ui_slider_bar->h_pb_point)
                {
                    _ui_slider_bar_set_bar_text(h_widget,
                                                pt_wgl_nfy_data->u.t_pos.i4_new_pos,
                                                TRUE, is_headphone_vol);
                    /* call the callback */
                    if(pt_ui_slider_bar->pf_ui_slider_bar_pos_chg_nfy_fct != NULL)
                    {
                        pt_ui_slider_bar->pf_ui_slider_bar_pos_chg_nfy_fct(
                        pt_wgl_nfy_data->u.t_pos.i4_new_pos);
                    }
                }
            }
            break;
        }

        case WGL_MSG_KEY_DOWN:
        case WGL_MSG_KEY_REPEAT:
        /* Second, if the KEY has been input, redirect to the PGBAR-BAR or PGBAR-POINT widget */
            UI_LOG_ON_FAIL(_ui_slider_bar_get_attach_data(h_widget,
                                           &pt_ui_slider_bar));

            /* Simulate the REPEAT event to DOWN */
            ui4_msg = WGL_MSG_KEY_DOWN;

            if(pt_ui_slider_bar->e_style == UI_SLIDER_BAR_STYLE_BAR)
            {
                c_wgl_default_msg_proc(pt_ui_slider_bar->h_pb_bar, ui4_msg, pv_param1, pv_param2);
            }
            else
            {
                c_wgl_default_msg_proc(pt_ui_slider_bar->h_pb_point, ui4_msg, pv_param1, pv_param2);
            }

            return WGLR_OK;

        default:
            break;


    }

    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_get_tag
 *
 * Description: Get the Tag value of the slider bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *
 * Outputs: ppv_tag - The output tag value.
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_get_tag (HANDLE_T  h_frm_slider,
                               VOID**    ppv_tag)
{
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    /* load the tag */
    *ppv_tag = pt_ui_slider_bar->pv_tag;

    return APP_UIR_OK;


}
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_set_tag
 *
 * Description: Set the Tag value of the slider bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         pv_tag       - The tag value.
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_tag(HANDLE_T  h_frm_slider,
                              VOID*     pv_tag)
{
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;

    /* Get slider bar structure */
   UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    /* Save the tag */
    pt_ui_slider_bar->pv_tag = pv_tag;

    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_cnt_inset
 *
 * Description: Set the content inset value of the slider bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         pv_tag       - The tag value.
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_set_cnt_inset(HANDLE_T  h_frm_slider,
                                    WGL_INSET_T *pt_inset)
{
    INT32               i4_ret = APP_UIR_OK;
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;
    WGL_INSET_T         t_inset;

    if (NULL == pt_inset || NULL_HANDLE == h_frm_slider)
    {
        return APP_UIR_INV_ARG;
    }

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    c_memset(&t_inset, 0, sizeof(t_inset));
    t_inset.i4_left = pt_inset->i4_left;
    t_inset.i4_right = pt_inset->i4_right;
    t_inset.i4_top = pt_inset->i4_top;
    t_inset.i4_bottom = pt_inset->i4_bottom;

    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                          WGL_CMD_PG_SET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_get_cnt_inset
 *
 * Description: Get the content inset value of the slider bar.
 *
 * Inputs: h_frm_slider - The handle of the Slider Bar.
 *         pv_tag       - The tag value.
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_slider_bar_get_cnt_inset(HANDLE_T  h_frm_slider,
                                    WGL_INSET_T *pt_inset)
{
    INT32               i4_ret = APP_UIR_OK;
    UI_SLIDER_BAR_T*    pt_ui_slider_bar;
    WGL_INSET_T         t_inset;

    if (NULL == pt_inset || NULL_HANDLE == h_frm_slider)
    {
        return APP_UIR_INV_ARG;
    }

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));
    c_memset(&t_inset, 0, sizeof(t_inset));

    i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                          WGL_CMD_PG_GET_CNT_INSET,
                          WGL_PACK(&t_inset),
                          NULL);
    UI_CHK_FAIL(i4_ret);

    pt_inset->i4_left = t_inset.i4_left;
    pt_inset->i4_right = t_inset.i4_right;
    pt_inset->i4_top = t_inset.i4_top;
    pt_inset->i4_bottom = t_inset.i4_bottom;

    return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_slider_bar_set_bk_img(HANDLE_T    h_frm_slider,
                                 HANDLE_T    h_img_tpl_frm_bk0,
                                 HANDLE_T    h_img_tpl_bar_pg_bar,
                                 HANDLE_T    h_img_tpl_bar_pg_bk0)
{
    INT32 i4_ret;
    UI_SLIDER_BAR_T*        pt_ui_slider_bar;
    WGL_IMG_INFO_T          t_img_info;

    /* Get slider bar structure */
    UI_CHK_FAIL(_ui_slider_bar_get_attach_data(h_frm_slider,
                                            &pt_ui_slider_bar));

    if (h_img_tpl_frm_bk0 != NULL_HANDLE)
    {
        pt_ui_slider_bar->h_ui_slider_bar_bk0 = h_img_tpl_frm_bk0;

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable    = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        t_img_info.u_img_data.t_standard.t_disable   = pt_ui_slider_bar->h_ui_slider_bar_bk0;
        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_frm_slider,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);
    }

    if (h_img_tpl_bar_pg_bar != NULL_HANDLE)
    {
        pt_ui_slider_bar->h_ui_slider_bar_pg_bar = h_img_tpl_bar_pg_bar;

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable =    pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_bar;
        t_img_info.u_img_data.t_standard.t_disable =   pt_ui_slider_bar->h_ui_slider_bar_pg_bar;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_PG_LEVEL_1),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);
    }

    if (h_img_tpl_bar_pg_bk0 != NULL_HANDLE)
    {
        pt_ui_slider_bar->h_ui_slider_bar_pg_bk0 = h_img_tpl_bar_pg_bk0;

        t_img_info.e_type = WGL_IMG_SET_STANDARD;
        t_img_info.u_img_data.t_standard.t_enable =    pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;
        t_img_info.u_img_data.t_standard.t_highlight = pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;
        t_img_info.u_img_data.t_standard.t_disable =   pt_ui_slider_bar->h_ui_slider_bar_pg_bk0;

        i4_ret = c_wgl_do_cmd(pt_ui_slider_bar->h_pb_bar,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK(WGL_IMG_BK),
                              WGL_PACK(&t_img_info));
        UI_CHK_FAIL(i4_ret);

    }

    return APP_UIR_OK;
}

INT32  a_ui_simple_dialog_default_tts_cb_fct(UTF16_T* pw2s_string)
{
    if(NULL == pw2s_string)
    {
        DBG_ERROR(("[MENU][%s %d] try to read a null string!!!!!\n"));
        return APP_UIR_FAIL;
    }
    INT32 i4_ret = a_app_tts_play(pw2s_string, c_uc_w2s_strlen(pw2s_string));
    //DBG_LOG_PRINT(("[UI][%s %d] i4_ret = %d\n",__FUNCTION__,__LINE__,i4_ret));
    return  i4_ret >= 0 ? APP_UIR_OK : APP_UIR_FAIL;
}

static VOID _a_ui_simple_dialog_tts_notify(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag);


/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_default_msg_proc(
                    HANDLE_T            h_widget,   /* Frame */
                    UINT32              ui4_msg,
                    VOID*               pv_param1,
                    VOID*               pv_param2)
{
    switch(ui4_msg)
    {
        case WGL_MSG_KEY_DOWN:
        {
            UINT32 ui4_keycode = (UINT32)pv_param1;
            UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog = NULL;
            BOOL   b_three_btn =FALSE;
#ifdef UI_SIMPLE_DIALOG_SELECTION_WRAP_OVER
            INT32                   i4_ret;

            if (ui4_keycode == BTN_CURSOR_LEFT ||
                ui4_keycode == BTN_CURSOR_RIGHT)
            {
                /* Get simple dialog structure */
                i4_ret = _ui_simple_dialog_get_attach_data (h_widget, & pt_ui_simple_dialog);
                if(i4_ret == APP_UIR_OK && pt_ui_simple_dialog != NULL)
                {
                    /* Loop selection */
                    a_ui_simple_dialog_set_answer(h_widget, !(pt_ui_simple_dialog->b_answer));
                    c_wgl_repaint(h_widget, NULL, TRUE);
                    return WGLR_OK;
                }
            }
#else
            /* LEFT => Yes */
            UI_LOG_ON_FAIL(_ui_simple_dialog_get_attach_data (h_widget, & pt_ui_simple_dialog));
            if(pt_ui_simple_dialog->h_btn_info != NULL_HANDLE)
            {
                b_three_btn = TRUE;
            }

            a_app_tts_nfy_unreg(_a_ui_simple_dialog_tts_notify);

            if(ui4_keycode == BTN_CURSOR_LEFT)
            {
                if(pt_ui_simple_dialog->b_info_btn_focused)
                {
                    pt_ui_simple_dialog->b_info_btn_focused = FALSE;
                    a_ui_simple_dialog_set_answer(h_widget, FALSE);
                    if(pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct)
                    {
                        pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_no);
                    }
                }
                else
                {
                    if(pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct)
                    {
                        pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_yes);
                    }
                    a_ui_simple_dialog_set_answer(h_widget, TRUE);
                }
                c_wgl_repaint(h_widget, NULL, TRUE);
                return WGLR_OK;
            }
            /* RIGHT => No */
            else if(ui4_keycode == BTN_CURSOR_RIGHT)
            {
                if(!pt_ui_simple_dialog->b_answer&&b_three_btn)
                {
                    pt_ui_simple_dialog->b_info_btn_focused = TRUE;
                    if(pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct)
                    {
                        pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_info);
                    }
                }
                else
                {
                    if(pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct)
                    {
                        pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_no);
                    }
                }
                a_ui_simple_dialog_set_answer(h_widget, FALSE);
                c_wgl_repaint(h_widget, NULL, TRUE);

                return WGLR_OK;
            }
#endif
            else if(ui4_keycode == BTN_SELECT)
            {
                UI_LOG_ON_FAIL(_ui_simple_dialog_press_select(h_widget));
                return WGLR_OK;
            }

		    else
            {
                if(_ui_simple_dialog_press_other_key(h_widget,ui4_keycode))
            	{
            		return WGLR_OK;
            	}
            }
            break;
        }

        default:
            break;
    }
    return c_wgl_default_msg_proc(h_widget, ui4_msg, pv_param1, pv_param2);

}
/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_create(UI_SIMPLE_DIALOG_INIT_T*    pt_ui_simple_dialog_init,   /* In  */
                                HANDLE_T*                ph_simple_dialog)              /* Out */
{
    INT32               i4_ret;
    INT32               i4_result;
    UI_SIMPLE_DIALOG_T* pt_ui_simple_dialog;

    pt_ui_simple_dialog = (UI_SIMPLE_DIALOG_T *) c_mem_alloc(sizeof(UI_SIMPLE_DIALOG_T));

    if(pt_ui_simple_dialog == NULL)
    {
        return APP_UIR_OUT_OF_MEMORY;
    }
    c_memset(pt_ui_simple_dialog,0 , sizeof(UI_SIMPLE_DIALOG_T));

    /* default value assignment for UI_SIMPLE_DIALOG_T, pending */

    _ui_simple_dialog_image_init(pt_ui_simple_dialog);

    /* Create content frame widget */

    do
    {
        /* Content Frame */
        i4_result = _ui_simple_dialog_create_frm(pt_ui_simple_dialog,
                                                 pt_ui_simple_dialog_init->pf_wdgt_proc,       /* App assigns the pf_wdgt_proc */
                                                 pt_ui_simple_dialog_init->h_parent,
                                                 pt_ui_simple_dialog_init->pt_rect,
                                                 pt_ui_simple_dialog_init->pt_begin_offset,
                                                 pt_ui_simple_dialog_init->e_style
                                                );

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* info icon */
        if (pt_ui_simple_dialog_init->b_info_icon)

        {
            i4_result = _ui_simple_dialog_create_info_icon(pt_ui_simple_dialog,
                                                             pt_ui_simple_dialog_init->e_style,
                                                             NULL,
                                                             0);

            if(i4_result != APP_UIR_OK)
            {
                i4_ret = i4_result;
                break;
            }
        }


        /* txtinfo */
        i4_result = _ui_simple_dialog_create_txtinfo(pt_ui_simple_dialog,
                                                     pt_ui_simple_dialog_init->e_style,
                                                     pt_ui_simple_dialog_init->pt_rect,
                                                     pt_ui_simple_dialog_init->ui2_txt_align_type);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        /* yes button */

        i4_result = _ui_simple_dialog_create_yes_button(pt_ui_simple_dialog,
                                                        pt_ui_simple_dialog_init->e_style,
                                                        pt_ui_simple_dialog_init->b_one_btn_mode,
                                                        pt_ui_simple_dialog_init->b_three_btn_mode,
                                                        &pt_ui_simple_dialog->h_btn_yes);

        if(i4_result != APP_UIR_OK)
        {
            i4_ret = i4_result;
            break;
        }

        if (!pt_ui_simple_dialog_init->b_one_btn_mode)
        {
            /* no button */

            i4_result = _ui_simple_dialog_create_no_button(pt_ui_simple_dialog,
                                                            pt_ui_simple_dialog_init->e_style,
                                                            pt_ui_simple_dialog_init->b_three_btn_mode,
                                                            &pt_ui_simple_dialog->h_btn_no);


            if(i4_result != APP_UIR_OK)
            {
                i4_ret = i4_result;
                break;
            }
        }
        if(pt_ui_simple_dialog_init->b_three_btn_mode)
        {

            i4_result = _ui_simple_dialog_create_info_button(pt_ui_simple_dialog,
                                                            pt_ui_simple_dialog_init->e_style,
                                                            &pt_ui_simple_dialog->h_btn_info);


            if(i4_result != APP_UIR_OK)
            {
                i4_ret = i4_result;
                break;
            }
        }
        /* Save the current answer */
        pt_ui_simple_dialog->b_answer = pt_ui_simple_dialog_init->b_default_answer;

        /* Save the function call back */

        if(pt_ui_simple_dialog_init->pf_ui_simple_dialog_yes_cb_fct!= NULL)
        {
            pt_ui_simple_dialog->pf_ui_simple_dialog_yes_cb_fct =
            pt_ui_simple_dialog_init->pf_ui_simple_dialog_yes_cb_fct;
        }

        if(pt_ui_simple_dialog_init->pf_ui_simple_dialog_no_cb_fct!= NULL)
        {
            pt_ui_simple_dialog->pf_ui_simple_dialog_no_cb_fct =
            pt_ui_simple_dialog_init->pf_ui_simple_dialog_no_cb_fct;
        }
		if(pt_ui_simple_dialog_init->pf_ui_simple_dialog_other_key_cb_fct!= NULL)
        {
            pt_ui_simple_dialog->pf_ui_simple_dialog_other_key_cb_fct =
            pt_ui_simple_dialog_init->pf_ui_simple_dialog_other_key_cb_fct;
        }

        if(pt_ui_simple_dialog_init->pf_ui_simple_dialog_info_cb_fct!= NULL)
        {
            pt_ui_simple_dialog->pf_ui_simple_dialog_info_cb_fct =
            pt_ui_simple_dialog_init->pf_ui_simple_dialog_info_cb_fct;
        }

        if(pt_ui_simple_dialog_init->pf_ui_simple_dialog_tts_cb_fct!= NULL)
        {
            pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct =
            pt_ui_simple_dialog_init->pf_ui_simple_dialog_tts_cb_fct;
        }
        /* 0. set all visible */
        c_wgl_set_visibility(pt_ui_simple_dialog->h_frm_simple_dialog, WGL_SW_RECURSIVE);

        /* 2. Hide the main frame at initial time */
        c_wgl_set_visibility(pt_ui_simple_dialog->h_frm_simple_dialog, WGL_SW_HIDE);

        /* Return the h_simple_dialog handle */
        *ph_simple_dialog = pt_ui_simple_dialog->h_frm_simple_dialog;

        /* Done */

        _ui_simple_dialog_set_attach_data(pt_ui_simple_dialog->h_frm_simple_dialog,
                                          pt_ui_simple_dialog);



        /* check answer and set the button status */

        i4_ret = a_ui_simple_dialog_set_answer(pt_ui_simple_dialog->h_frm_simple_dialog,
                                      pt_ui_simple_dialog->b_answer);

    } while(0);

    if(i4_ret != APP_UIR_OK)
    {
        /* Release childs*/

        if(pt_ui_simple_dialog->h_txt_txtinfo != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_txt_txtinfo);
        }

        if(pt_ui_simple_dialog->h_btn_yes != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_btn_yes);
        }

        if(pt_ui_simple_dialog->h_btn_no != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_btn_no);
        }
        if(pt_ui_simple_dialog->h_btn_info != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_btn_info);
        }

        /* Release parent */

        if(pt_ui_simple_dialog->h_frm_simple_dialog != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_frm_simple_dialog);
        }

        /* Release template images */

        if(pt_ui_simple_dialog->h_ui_simple_dialog_bk0 != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_simple_dialog->h_ui_simple_dialog_bk0);
        }

        if(pt_ui_simple_dialog->h_ui_simple_dialog_selected_bk != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_simple_dialog->h_ui_simple_dialog_selected_bk);
        }

        if(pt_ui_simple_dialog->h_ui_simple_dialog_unselected_bk != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_simple_dialog->h_ui_simple_dialog_unselected_bk);
        }

        /* Release the structure */
        c_mem_free(pt_ui_simple_dialog);

    }

    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_destory(HANDLE_T            h_simple_dialog)

{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

        /* Release childs*/

        if(pt_ui_simple_dialog->h_txt_txtinfo != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_txt_txtinfo);
        }

        if(pt_ui_simple_dialog->h_btn_yes != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_btn_yes);
        }

        if(pt_ui_simple_dialog->h_btn_no != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_btn_no);
        }

        if(pt_ui_simple_dialog->h_btn_info != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_btn_info);
        }

        /* Release parent */

        if(pt_ui_simple_dialog->h_frm_simple_dialog != NULL_HANDLE)
        {
            c_wgl_destroy_widget(pt_ui_simple_dialog->h_frm_simple_dialog);
        }

        /* Release template images */

        if(pt_ui_simple_dialog->h_ui_simple_dialog_bk0 != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_simple_dialog->h_ui_simple_dialog_bk0);
        }

        if(pt_ui_simple_dialog->h_ui_simple_dialog_selected_bk != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_simple_dialog->h_ui_simple_dialog_selected_bk);
        }

        if(pt_ui_simple_dialog->h_ui_simple_dialog_unselected_bk != NULL_HANDLE)
        {
            c_wgl_img_tpl_destroy(pt_ui_simple_dialog->h_ui_simple_dialog_unselected_bk);
        }

        /* Release the structure */
        c_mem_free(pt_ui_simple_dialog);


    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_repaint(HANDLE_T            h_simple_dialog)
{
      INT32   i4_ret;

      /* Repaint it */
      i4_ret = c_wgl_repaint(h_simple_dialog, NULL, TRUE);
      UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_txt_txtinfo_repaint(HANDLE_T     h_simple_dialog)
{
    INT32                   i4_ret;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    /* Get simple dialog structure */

     i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                &pt_ui_simple_dialog);

     if(i4_ret != APP_UIR_OK)
     {
         return i4_ret;
     }

     /* Repaint it */
     i4_ret = c_wgl_repaint(pt_ui_simple_dialog->h_txt_txtinfo, NULL, TRUE);
     UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

static INT32    i4_tts_id;
static HANDLE_T h_simple_dialog_tts;
INT32 a_ui_simple_dialog_set_answer_ex(HANDLE_T                  h_simple_dialog,
                                              UI_SIMPLE_DIALOG_ANSWER   e_answer);

static VOID _a_ui_simple_dialog_tts_notify(TTS_STRING_STATE_E e_tts_str_state, UINT32 ui4_tts_play_id, VOID* pv_tag)
{
    UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */
     UI_LOG_ON_FAIL(_ui_simple_dialog_get_attach_data(h_simple_dialog_tts,&pt_ui_simple_dialog));

    if(ui4_tts_play_id == i4_tts_id)
    {
        if(e_tts_str_state == TTS_STR_ST_PLAYED)
        {
            a_app_tts_nfy_unreg(_a_ui_simple_dialog_tts_notify);
            if(pt_ui_simple_dialog->b_answer)
            {
                pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_yes);
                a_ui_simple_dialog_set_answer_ex(h_simple_dialog_tts,UI_SIMPLE_DIALOG_ANSWER_YES);
            }
            else
            {
                if(pt_ui_simple_dialog->b_info_btn_focused && pt_ui_simple_dialog->h_btn_info)
                {
                    pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_info);
                    a_ui_simple_dialog_set_answer_ex(h_simple_dialog_tts,UI_SIMPLE_DIALOG_ANSWER_INFO);
                }
                else
                {
                     pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_no);
                     a_ui_simple_dialog_set_answer_ex(h_simple_dialog_tts,UI_SIMPLE_DIALOG_ANSWER_NO);
                }
            }
        }
        else if(e_tts_str_state == TTS_STR_ST_STOPPED)
        {
            a_app_tts_nfy_unreg(_a_ui_simple_dialog_tts_notify);
        }
        i4_tts_id = -1;
    }

    if(e_tts_str_state == TTS_STR_ST_PLAYING)
    {
        i4_tts_id = ui4_tts_play_id;
    }
};

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_show(HANDLE_T            h_simple_dialog)
{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }
      h_simple_dialog_tts = h_simple_dialog;

      i4_ret = c_wgl_set_visibility(pt_ui_simple_dialog->h_frm_simple_dialog, WGL_SW_RECURSIVE);
      UI_CHK_FAIL(i4_ret);

      a_tv_net_OSD_appear();

      if(NULL != pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct && pt_ui_simple_dialog->pw2s_txtinfo)
      {
           a_app_tts_nfy_reg(_a_ui_simple_dialog_tts_notify,NULL);

           if(APP_UIR_OK != pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_txtinfo))
           {
                if(pt_ui_simple_dialog->b_answer)
                {
                    pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_yes);
                    a_ui_simple_dialog_set_answer_ex(h_simple_dialog,UI_SIMPLE_DIALOG_ANSWER_YES);
                }
                else
                {
                    if(pt_ui_simple_dialog->b_info_btn_focused && pt_ui_simple_dialog->h_btn_info)
                    {
                        pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_info);
                        a_ui_simple_dialog_set_answer_ex(h_simple_dialog,UI_SIMPLE_DIALOG_ANSWER_INFO);
                    }
                    else
                    {
                         pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct(pt_ui_simple_dialog->pw2s_no);
                         a_ui_simple_dialog_set_answer_ex(h_simple_dialog,UI_SIMPLE_DIALOG_ANSWER_NO);
                    }
                }
           }
      }

    c_wgl_set_focus(h_simple_dialog,FALSE);
    c_wgl_repaint(h_simple_dialog, NULL, TRUE);

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_hide(HANDLE_T            h_simple_dialog)
{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;
      BOOL                  b_is_visible = FALSE;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      c_wgl_get_visibility(h_simple_dialog, &b_is_visible);
      pt_ui_simple_dialog->b_info_btn_focused = FALSE;
      if (b_is_visible == TRUE)
      {
          i4_ret = c_wgl_set_visibility(pt_ui_simple_dialog->h_frm_simple_dialog, WGL_SW_HIDE);
          UI_CHK_FAIL(i4_ret);
          c_wgl_repaint(pt_ui_simple_dialog->h_frm_simple_dialog,NULL,TRUE);

          a_tv_net_OSD_disapper();
      }

    return APP_UIR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_get_widget(HANDLE_T                           h_simple_dialog,
                                    UI_SIMPLE_DIALOG_WIDGET_HANDLE_T*  pt_widget_handle)

{
    INT32                   i4_ret;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    if (pt_widget_handle == NULL)
    {
        return APP_UIR_INV_ARG;
    }

    /* Get simple dialog structure */

    i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    pt_widget_handle->h_frm_simple_dialog = pt_ui_simple_dialog->h_frm_simple_dialog;
    pt_widget_handle->h_txt_txtinfo       = pt_ui_simple_dialog->h_txt_txtinfo;
    pt_widget_handle->h_btn_yes           = pt_ui_simple_dialog->h_btn_yes;
    pt_widget_handle->h_btn_no            = pt_ui_simple_dialog->h_btn_no;
    pt_widget_handle->h_btn_info          = pt_ui_simple_dialog->h_btn_info;
    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_text(HANDLE_T            h_simple_dialog,
                                  UTF16_T*            w2s_text)
{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      pt_ui_simple_dialog->pw2s_txtinfo = w2s_text;

      i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_txt_txtinfo,
                            WGL_CMD_TEXT_SET_TEXT,
                            WGL_PACK(w2s_text),
                            WGL_PACK(c_uc_w2s_strlen(w2s_text)));

      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_text_align(HANDLE_T   h_simple_dialog,
                                        UINT8       ui1_align)
{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_txt_txtinfo,
                            WGL_CMD_TEXT_SET_ALIGN,
                            WGL_PACK(ui1_align),
                            NULL);

      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_text_rect(HANDLE_T            h_simple_dialog,
                                       GL_RECT_T           *pt_rect,
                                       BOOL                b_repaint)
{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      i4_ret = c_wgl_move(pt_ui_simple_dialog->h_txt_txtinfo, pt_rect, b_repaint);

      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_yes_text(HANDLE_T            h_simple_dialog,
                                      UTF16_T*            w2s_text)
{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      pt_ui_simple_dialog->pw2s_yes = w2s_text;

      i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_yes,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(w2s_text),
                            WGL_PACK(c_uc_w2s_strlen(w2s_text)));

      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_no_text(HANDLE_T            h_simple_dialog,
                                     UTF16_T*            w2s_text)
{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      pt_ui_simple_dialog->pw2s_no = w2s_text;

      i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_no,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(w2s_text),
                            WGL_PACK(c_uc_w2s_strlen(w2s_text)));

      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}
/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_info_text(HANDLE_T            h_simple_dialog,
                                     UTF16_T*            w2s_text)
{
      INT32                 i4_ret;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      pt_ui_simple_dialog->pw2s_info = w2s_text;

      i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_info,
                            WGL_CMD_BTN_SET_TEXT,
                            WGL_PACK(w2s_text),
                            WGL_PACK(c_uc_w2s_strlen(w2s_text)));

      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_yes_no_rect(HANDLE_T            h_simple_dialog,
                                         BOOL                b_btn_yes,
                                         GL_RECT_T           *pt_rect,
                                         BOOL                b_repaint)
{
      INT32                 i4_ret;
      HANDLE_T              h_btn = NULL_HANDLE;
      UI_SIMPLE_DIALOG_T*   pt_ui_simple_dialog;

      /* Get simple dialog structure */

      i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                                 &pt_ui_simple_dialog);

      if(i4_ret != APP_UIR_OK)
      {
          return i4_ret;
      }

      h_btn = (b_btn_yes == TRUE) ? pt_ui_simple_dialog->h_btn_yes : pt_ui_simple_dialog->h_btn_no;

      i4_ret = c_wgl_move(h_btn, pt_rect, b_repaint);

      UI_CHK_FAIL(i4_ret);

      return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_answer(HANDLE_T            h_simple_dialog,
                                    BOOL                b_answer)
{
    INT32                   i4_ret = APP_UIR_OK;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    /* Get simple dialog structure */

    i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                             &pt_ui_simple_dialog);

    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }
    DBG_INFO(("[UI][%s %d]b_answer=%d,b_info_btn_focused = %d \n",__FUNCTION__,__LINE__,b_answer,pt_ui_simple_dialog->b_info_btn_focused));

    if (pt_ui_simple_dialog->h_btn_no == NULL_HANDLE)
    {
        /* This is one button mode. Set highlight to Yes. */
        b_answer = TRUE;
    }

    /* Save the current answer */
    pt_ui_simple_dialog->b_answer = b_answer;

    if(b_answer)
    {
        if (pt_ui_simple_dialog->h_btn_yes)
        {
            i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_yes,
                                  WGL_CMD_BTN_SET_PUSHED,
                                  WGL_PACK(TRUE),
                                  NULL);
        }

        if (pt_ui_simple_dialog->h_btn_no)
        {
            i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_no,
                                  WGL_CMD_BTN_SET_PUSHED,
                                  WGL_PACK(FALSE),
                                  NULL);
        }

        if (pt_ui_simple_dialog->h_btn_info)
        {
            i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_info,
                                  WGL_CMD_BTN_SET_PUSHED,
                                  WGL_PACK(FALSE),
                                  NULL);
        }
    }
    else
    {
        if (pt_ui_simple_dialog->h_btn_yes)
        {
            i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_yes,
                                  WGL_CMD_BTN_SET_PUSHED,
                                  WGL_PACK(FALSE),
                                  NULL);
        }

        if (pt_ui_simple_dialog->b_info_btn_focused == FALSE)
        {
            i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_info,
                                  WGL_CMD_BTN_SET_PUSHED,
                                  WGL_PACK(FALSE),
                                  NULL);
            i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_no,
                                  WGL_CMD_BTN_SET_PUSHED,
                                  WGL_PACK(TRUE),
                                  NULL);
        }
        else
        {
            i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_no,
                                  WGL_CMD_BTN_SET_PUSHED,
                                  WGL_PACK(FALSE),
                                  NULL);
            if (pt_ui_simple_dialog->h_btn_info)
            {
                pt_ui_simple_dialog->b_info_btn_focused = TRUE;
                i4_ret = c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_info,
                                      WGL_CMD_BTN_SET_PUSHED,
                                      WGL_PACK(TRUE),
                                      NULL);
            }
        }
    }

    UI_CHK_FAIL(i4_ret);

    return APP_UIR_OK;
}

INT32 a_ui_simple_dialog_set_answer_ex(HANDLE_T                  h_simple_dialog,
                                              UI_SIMPLE_DIALOG_ANSWER   e_answer)
{
    INT32                   i4_ret = APP_UIR_OK;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    /* Get simple dialog structure */

    i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                              &pt_ui_simple_dialog);

    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }
    if (pt_ui_simple_dialog->h_btn_no   == NULL_HANDLE ||
        (pt_ui_simple_dialog->h_btn_info == NULL_HANDLE && UI_SIMPLE_DIALOG_ANSWER_INFO == e_answer))
    {
        /* This is one button mode. Set highlight to Yes. */
        e_answer = UI_SIMPLE_DIALOG_ANSWER_YES;
    }

   switch(e_answer)
   {
        case UI_SIMPLE_DIALOG_ANSWER_NO :
        {
            pt_ui_simple_dialog->b_info_btn_focused = FALSE;
            pt_ui_simple_dialog->b_answer           = FALSE;

            c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_yes,
                         WGL_CMD_BTN_SET_PUSHED,
                         WGL_PACK(FALSE),
                         NULL);
            if(pt_ui_simple_dialog->b_info_btn_focused == TRUE)
            {
                pt_ui_simple_dialog->b_info_btn_focused = FALSE;
                c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_info,
                             WGL_CMD_BTN_SET_PUSHED,
                             WGL_PACK(FALSE),
                             NULL);
            }
            c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_no,
                                WGL_CMD_BTN_SET_PUSHED,
                                WGL_PACK(TRUE),
                                NULL);
            break;
        }
        case UI_SIMPLE_DIALOG_ANSWER_INFO:
        {
             pt_ui_simple_dialog->b_info_btn_focused = TRUE;
             pt_ui_simple_dialog->b_answer           = FALSE;
             c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_no,
                          WGL_CMD_BTN_SET_PUSHED,
                          WGL_PACK(FALSE),
                          NULL);
             c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_yes,
                          WGL_CMD_BTN_SET_PUSHED,
                          WGL_PACK(FALSE),
                          NULL);
             c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_info,
                          WGL_CMD_BTN_SET_PUSHED,
                          WGL_PACK(TRUE),
                          NULL);
             break;
        }
        default:
        {
            pt_ui_simple_dialog->b_info_btn_focused = FALSE;
            pt_ui_simple_dialog->b_answer = e_answer;
            if(pt_ui_simple_dialog->h_btn_no)
            {
                c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_no,
                             WGL_CMD_BTN_SET_PUSHED,
                             WGL_PACK(FALSE),
                             NULL);
            }
            if(pt_ui_simple_dialog->h_btn_info)
            {
                c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_info,
                             WGL_CMD_BTN_SET_PUSHED,
                             WGL_PACK(FALSE),
                             NULL);
            }
            c_wgl_do_cmd(pt_ui_simple_dialog->h_btn_yes,
                         WGL_CMD_BTN_SET_PUSHED,
                         WGL_PACK(TRUE),
                         NULL);

        }
   }
   return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_yes_fct(HANDLE_T                    h_simple_dialog,
                                     ui_simple_dialog_yes_cb_fct pf_yes)
{
    INT32                   i4_ret;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    /* Get simple dialog structure */

    i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                               &pt_ui_simple_dialog);

    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    pt_ui_simple_dialog->pf_ui_simple_dialog_yes_cb_fct = pf_yes;

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_no_fct(HANDLE_T                    h_simple_dialog,
                                    ui_simple_dialog_no_cb_fct pf_no)
{
    INT32                   i4_ret;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    /* Get simple dialog structure */

    i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                               &pt_ui_simple_dialog);

    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    pt_ui_simple_dialog->pf_ui_simple_dialog_no_cb_fct = pf_no;

    return APP_UIR_OK;
}


/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_info_fct(HANDLE_T                    h_simple_dialog,
                                     ui_simple_dialog_info_cb_fct pf_info)
{
    INT32                   i4_ret;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    /* Get simple dialog structure */

    i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                               &pt_ui_simple_dialog);

    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    pt_ui_simple_dialog->pf_ui_simple_dialog_info_cb_fct= pf_info;

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_tts_fct(HANDLE_T                    h_simple_dialog,
                                        ui_simple_dialog_tts_cb_fct  pf_tts)
{
    INT32                   i4_ret;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    /* Get simple dialog structure */

    i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                               &pt_ui_simple_dialog);

    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    pt_ui_simple_dialog->pf_ui_simple_dialog_tts_cb_fct= pf_tts;

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
 *
 * Description:
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns: TRUE is process the key .
 *
 ----------------------------------------------------------------------------*/
INT32 a_ui_simple_dialog_set_other_key_cb_fct(HANDLE_T                    h_simple_dialog,
                                    ui_simple_dialog_other_key_cb_fct pf_other)
{
    INT32                   i4_ret;
    UI_SIMPLE_DIALOG_T*     pt_ui_simple_dialog;

    /* Get simple dialog structure */

    i4_ret = _ui_simple_dialog_get_attach_data(h_simple_dialog,
                                               &pt_ui_simple_dialog);

    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }

    pt_ui_simple_dialog->pf_ui_simple_dialog_other_key_cb_fct = pf_other;

    return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_focus(HANDLE_T  h_simple_dialog, BOOL b_repaint)
{
     c_wgl_set_focus(h_simple_dialog, b_repaint);

     return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_default_msg_proc(HANDLE_T  h_simple_dialog, wgl_widget_proc_fct msg_proc )
{
   return c_wgl_set_widget_proc(h_simple_dialog,msg_proc);
}


/*----------------------------------------------------------------------------
 * Name:
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
INT32 a_ui_simple_dialog_set_offset(HANDLE_T  h_simple_dialog,GL_RECT_T* pt_rect,  GL_POINT_T* pt_begin_offset,UI_SIMPLE_DIALOG_STYLE_T e_style)
{
     GL_RECT_T         t_rect;
     GL_POINT_T        t_begin_offset;

     if(pt_begin_offset == NULL)
     {
         t_begin_offset.i4_x = 0;
         t_begin_offset.i4_y = 0;
     }
     else
     {
         t_begin_offset = *pt_begin_offset;
     }

     if(e_style == UI_SIMPLE_DIALOG_STYLE_BIG)
     {
         SET_RECT_BY_SIZE(&t_rect,
                          UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x,
                          UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                          UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_W,
                          UI_SIMPLE_DIALOG_BIG_DEF_CONTENT_FRAME_H);
     }
     else if(e_style == UI_SIMPLE_DIALOG_STYLE_MEDIUM)
     {
         SET_RECT_BY_SIZE(&t_rect,
                          UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x,
                          UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                          UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_W,
                          UI_SIMPLE_DIALOG_MEDIUM_DEF_CONTENT_FRAME_H);
     }
     else if(e_style == UI_SIMPLE_DIALOG_STYLE_SMALL)
     {
         SET_RECT_BY_SIZE(&t_rect,
                          UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x,
                          UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                          UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_W,
                          UI_SIMPLE_DIALOG_SMALL_DEF_CONTENT_FRAME_H);
     }
     else if(e_style == UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY)
     {
         /* If the pt_rect is specified, use this parameter */

         if(pt_rect == NULL)
         {
             SET_RECT_BY_SIZE(&t_rect,
                              UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_X + t_begin_offset.i4_x,
                              UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                              UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_W,
                              UI_SIMPLE_DIALOG_INFO_DEF_CONTENT_FRAME_H);
         }
         else
         {
             t_rect = *pt_rect;
         }
     }
     else if(e_style == UI_SIMPLE_DIALOG_STYLE_WARNING_MSG)
     {
         /* If the pt_rect is specified, use this parameter */

         if(pt_rect == NULL)
         {
         SET_RECT_BY_SIZE(&t_rect,
                          UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_X + t_begin_offset.i4_x,
                          UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_Y + t_begin_offset.i4_y,
                          UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_W,
                          UI_SIMPLE_DIALOG_WARNING_MSG_CONTENT_FRAME_H);
         }
         else
         {
          t_rect = *pt_rect;
         }
     }

     c_wgl_move(h_simple_dialog,&t_rect, FALSE);

     return APP_UIR_OK;
}

/*----------------------------------------------------------------------------
 * Name: ui_get_dbg_level
 *
 * Description:
 *      Get UI debug level
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
UINT16 ui_get_dbg_level(VOID)
{
    return ui2_ui_dbg_level;
}

/*----------------------------------------------------------------------------
 * Name: ui_set_dbg_level
 *
 * Description:
 *      Set UI debug level
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
VOID ui_set_dbg_level(UINT16 ui2_dbg_level)
{
    ui2_ui_dbg_level = ui2_dbg_level;
}
extern BOOL a_is_oled_compensation_support();
/*----------------------------------------------------------------------------
 * Name: a_ui_slider_bar_create
 * Description:
 * Inputs:
 * Outputs:
 * Returns:
 ----------------------------------------------------------------------------*/
extern INT32 a_ui_init(VOID)
{
    if (a_is_oled_compensation_support())
    {
        t_g_ui_color_fg1_txt = t_g_ui_color_fg1_oled_txt;
        t_g_ui_color_fg2_txt = t_g_ui_color_fg1_oled_txt;
    }
#ifdef WGL_ANIM_SUPPORT
    INT32 i4_ret;

    i4_ret = ui_anim_init();
    if(i4_ret != APP_UIR_OK)
    {
        return i4_ret;
    }
#endif

    return APP_UIR_OK;
}
