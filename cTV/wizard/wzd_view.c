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
 * $RCSfile: wzd_view.c,v $
 * $Revision: #2 $
 * $Date: 2015/07/03 $
 * $Author: hs_nali $
 * $CCRevision: /main/DTV_X_ATSC/13 $
 * $SWAuthor: CS Kuo $
 * $MD5HEX: 0dc5e5894593d8bd6b2c6ecc9869c8fa $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "wizard/wzd_view.h"
#include "wizard/wzd_dbg.h"

#ifndef SETI_LB_PAGE_ELEM_NUM
#define SETI_LB_PAGE_ELEM_NUM               (8)
#endif

#define TITLE_PIC_FLAG                 		("%p")
#define TITLE_PIC_FLAG_LEN             		(3)

typedef struct _WZD_VIEW_FOOTER_INFO_T
{
    WZD_FOOTER_BTN_INDEX_T  e_focused_btn;  /* Focused footer button index */
    BOOL                    ab_enabled[WZD_FOOTER_BTN_COUNT];  /* Enabled or disabled status of each footer button */
}WZD_VIEW_FOOTER_INFO_T;

typedef struct _WZD_VIEW_SEL_BOX_CTRL_T
{	
	UINT32                      ui4_index_current;					/* The current index of select box button */
	UINT32                      ui4_index_offset;					/* The offset between current button and real button */

	BOOL                    	ab_enabled[WZD_SEL_BOX_BTN_COUNT];  /* Enabled or disabled status of each select box */
	BOOL						b_ignore_msg;
}WZD_VIEW_SEL_BOX_CTRL_T;

/*
   Structures.
*/
typedef struct
{
    /* frame widgets */
    HANDLE_T      h_main_frm;                /* main frame */
    HANDLE_T      h_base_frm;                /* base map frame */
    HANDLE_T      h_layout_frm;              /* layout frame */
    HANDLE_T      h_footer_frm;              /* Footer frame */

    /* list box widgets */
    HANDLE_T      h_title_txt;               /* title text */
    HANDLE_T      h_seti_lst;                /* setting list box */

    /* text widgets */
    HANDLE_T      h_desc_txt;                /* setting description text */

    /* scan progress bar widgets */
    HANDLE_T      h_scan_bar;                /* scan progress bar */
    HANDLE_T      h_scan_txt;                /* Scan status text */

    /* icon widget for WZD_PAGE_TYPE_DESC_LIST_WITH_ICON */
    HANDLE_T      h_seti_icon;

    /* Footer related */
    HANDLE_T      ah_footer_btn[WZD_FOOTER_BTN_COUNT];
    WZD_VIEW_FOOTER_INFO_T  t_footer_info;

	/* Select box */
	HANDLE_T      h_sb_frm;              /* Select box frame */
	HANDLE_T      ah_sb_btn[WZD_SEL_BOX_BTN_COUNT];
	HANDLE_T      ah_sb_txt[WZD_SEL_BOX_BTN_COUNT];
	HANDLE_T      ah_sb_icon_1[WZD_SEL_BOX_BTN_COUNT];
	HANDLE_T      ah_sb_icon_2[WZD_SEL_BOX_BTN_COUNT];
	HANDLE_T      h_sb_icon_plus;		/* additional icon */
	
    WZD_VIEW_SEL_BOX_INFO_T	t_sb_info;
	WZD_VIEW_SEL_BOX_CTRL_T	t_sb_ctrl;

	/* Full screen dialog */
	HANDLE_T	  h_full_screen_dlg_frm;	/* Full screen dialog frame */
	HANDLE_T      h_full_screen_dlg_btn;    /* Full screen dialog frame */
	HANDLE_T      h_full_screen_dlg_icon;	/* Full screen dialog icon */
    HANDLE_T      h_full_screen_dlg_txt;	/* Full screen dialog text */
	BOOL		  b_full_screen_is_show;	/* Full screen dialog is show */

    /* Demo picture icon */
    HANDLE_T      h_demo_icon;
    HANDLE_T      h_demo_txt;
    /*right panel icons*/
    HANDLE_T      h_right_panel_icons;

    /* osd related */
    GL_HPLANE_T   h_plane;
    HANDLE_T      h_canvas;
    UINT32        ui4_osd_offset_x;          /* OSD offset x */
    UINT32        ui4_osd_offset_y;          /* OSD offset y */
    UINT32        ui4_osd_width;             /* OSD width */
    UINT32        ui4_osd_height;            /* OSD height */
    CHAR          s_font_name[32];           /* font name */

#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
    /* code input list widiget */
    HANDLE_T      h_code_frm;                /* code input frame */
    HANDLE_T      ah_code_box[CODE_BOX_ELEM_NUM]; /* code input box list */
    UINT8         aui1_code_style[CODE_BOX_ELEM_NUM];     /* style definition for each code box */
    UTF16_T       w2_indicator;              /* indicator for empty digit */
    HANDLE_T      h_code_txt;                /* code input prompt text */
    UINT8         ui1_code_elem_num;         /* code input box elem num */
    UINT8         ui1_code_hlt_idx;          /* code input box hlt index */
    UINT8         aui1_code_digit[CODE_BOX_ELEM_NUM];     /* inputted code number */
#endif
}   WZD_VIEW_T;

WGL_HIMG_TPL_T      h_g_custom_img_network_setup;
WGL_HIMG_TPL_T      h_g_custom_img_choose_signal;
WGL_HIMG_TPL_T      h_g_custom_img_signal_all_av_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_dtv_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_HDMI_1_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_HDMI_2_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_HDMI_3_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_HDMI_4_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_component_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_composite_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_PC_hlt;
WGL_HIMG_TPL_T      h_g_custom_img_signal_AudioOut;

WGL_HIMG_TPL_T      h_g_custom_img_getting_started_rc;
WGL_HIMG_TPL_T      h_g_custom_img_keypad;
WGL_HIMG_TPL_T      h_g_custom_img_demo_scan;
WGL_HIMG_TPL_T      h_g_custom_img_demo_scan_comp_HL;
WGL_HIMG_TPL_T      h_g_custom_img_demo_scan_DTV_HL;
WGL_HIMG_TPL_T      h_g_custom_img_demo_scan_HDMI1_HL;
WGL_HIMG_TPL_T      h_g_custom_img_demo_scan_HDMI2_HL;
WGL_HIMG_TPL_T      h_g_custom_img_demo_scan_HDMI3_HL;
WGL_HIMG_TPL_T      h_g_custom_img_demo_scan_HDMI4_HL;
WGL_HIMG_TPL_T      h_g_custom_img_demo_scan_RGB_HL;

/*-----------------------------------------------------------------------------
                    static function declaraions
-----------------------------------------------------------------------------*/
static WZD_VIEW_T  t_g_view;

static INT32 _wzd_view_canvas_init (VOID);
static INT32 _wzd_view_create_main_frm (VOID);
static INT32 _wzd_view_create_base_frm (VOID);
static INT32 _wzd_view_create_layout_frm (VOID);

static INT32 _wzd_view_create_seti_lst (VOID);

static INT32 _wzd_view_create_desc_txt (VOID);

static INT32 _wzd_view_create_scan_bar (VOID);

static INT32 _wzd_view_create_seti_icon (VOID);
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
static INT32 _wzd_view_create_code_frm_and_txt (VOID);
static INT32 _wzd_view_create_code_box (UINT8    ui1_code_elem_num,
                                        UINT8    aui1_code_style[],
                                        UINT16   aw2s_code_sep_char[]);
static INT32 _wzd_view_clear_code_box  (VOID);
static INT32 _wzd_view_code_box_set_hlt_idx (UINT8 ui1_code_idx, BOOL b_repaint);


#endif

static INT32 _wzd_view_create_sel_box_frm (VOID);
static INT32 _wzd_view_create_sel_box_buttons (VOID);
static INT32 _wzd_view_sel_box_get_previous_btn (
                                WZD_SEL_BOX_BTN_INDEX_T  e_sel_box_index,
                                WZD_SEL_BOX_BTN_INDEX_T* pe_pre_btn_index);
static INT32 _wzd_view_sel_box_get_next_btn (
                                WZD_SEL_BOX_BTN_INDEX_T  e_sel_box_index,
                                WZD_SEL_BOX_BTN_INDEX_T* pe_next_btn_index);
static INT32 _wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_T e_direction);

static INT32 _wzd_view_create_btn_widget(
    HANDLE_T                    h_parent,
    UTF16_T*                    ws_text,
    const GL_RECT_T*            pt_rect,
    const WGL_COLOR_INFO_T*     pt_color_info_fg,
    const WGL_FONT_INFO_T*      pt_font,
    WGL_HIMG_TPL_T              t_img_tpl_ht,
    WGL_HIMG_TPL_T              t_img_tpl_un_ht,
    UINT8                       ui1_align,
    wgl_widget_proc_fct         pf_wdgt_proc,
    HANDLE_T*                   ph_btn);


static INT32 _wzd_view_full_screen_dlg_create(VOID);


/*-----------------------------------------------------------------------------
 * Name: _wzd_view_w2s_sch
 *
 * Description: The function.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 
 ----------------------------------------------------------------------------*/
static UTF16_T* _wzd_view_w2s_sch(UTF16_T*        pw2s_text,
                             	  const UTF16_T*  pw2s_sub_text)
{
    UTF16_T*   pw2s_start = NULL;
    SIZE_T     t_cmp_offset = 0;
    SIZE_T     t_txt_size = 0;
    SIZE_T     t_sub_txt_size = 0;

    if (!pw2s_text ||
        !pw2s_sub_text)
    {
        return (pw2s_start);
    }

    t_txt_size = c_uc_w2s_strlen(pw2s_text);
    t_sub_txt_size = c_uc_w2s_strlen(pw2s_sub_text);

    if (t_txt_size < t_sub_txt_size)
    {
        return (pw2s_start);
    }

    pw2s_start = pw2s_text;

    while (pw2s_start <= pw2s_text + t_txt_size - t_sub_txt_size)
    {
        t_cmp_offset = 0;
        while (t_cmp_offset < t_sub_txt_size)
        {
            if (*(pw2s_start + t_cmp_offset) == *(pw2s_sub_text + t_cmp_offset))
            {
                t_cmp_offset++;
            }
            else
            {
                break;
            }
        }
        if (t_cmp_offset == t_sub_txt_size)
        {
            return (pw2s_start);
        }
        pw2s_start++;
    }

    return (NULL);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_canvas_init
 *
 * Description: The function initiates the canvas.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_canvas_init (VOID)
{
    GL_HSCREEN_T     h_screen; /* screen handle */

    /* open screen */
    RET_ON_ERR (c_gl_screen_open (SN_PRES_MAIN_DISPLAY,
                                  NULL,
                                  NULL,
                                  & h_screen));

    /* open plane */
    RET_ON_ERR (c_gl_plane_open (h_screen, a_util_get_default_osd_plane_index(), & t_g_view.h_plane));

    /* link plane */
    RET_ON_ERR (c_gl_plane_link (t_g_view.h_plane, h_screen, TRUE));

    /* open canvas */
    RET_ON_ERR (c_wgl_get_canvas (t_g_view.h_plane, & t_g_view.h_canvas));

    /* free handles */
    c_handle_free (h_screen);

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nfy_frm
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nfy_frm (HANDLE_T    h_widget,
                           UINT32      ui4_msg,
                           VOID*       pv_param1,
                           VOID*       pv_param2)
{
    HANDLE_T              h_cb_widget;
    WGL_NOTIFY_DATA_T*    pt_wgl_nfy_data;

    h_cb_widget     = (HANDLE_T) pv_param1;
    pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if (ui4_msg == WGL_MSG_NOTIFY)
    {
        if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_GL_GET_FOCUS) /* some widget gets focus */
        {
            wzd_app_send_msg (WZD_MSG_WGL_GET_FOCUS, NULL, 0);
        }
        else if ((h_cb_widget == t_g_view.h_seti_lst) &&
                 (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_SEL)) /* setting list element selected */
        {
            if (pt_wgl_nfy_data->u.t_lb_elem_sel.b_is_selected)
            {
                wzd_app_send_msg (WZD_MSG_WGL_SETI_LST_ELEM_SEL, NULL, 0);
            }
        }
    }

    if (ui4_msg != WGL_MSG_DESTROY)
    {
        /* call default procedure */
        return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
    }

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_main_frm
 *
 * Description: This function creates the main (root) frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_main_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;

    /* get canvas size & offset */
    RET_ON_ERR (c_wgl_get_canvas_size (t_g_view.h_canvas,
                                       & t_g_view.ui4_osd_width,
                                       & t_g_view.ui4_osd_height));

    t_g_view.ui4_osd_offset_x = (t_g_view.ui4_osd_width  - MAIN_FRM_W) / 2;
    t_g_view.ui4_osd_offset_y = (t_g_view.ui4_osd_height - MAIN_FRM_H) / 2;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      MAIN_FRM_X,
                      MAIN_FRM_Y,
                      MAIN_FRM_W,
                      MAIN_FRM_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_canvas,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _wzd_nfy_frm,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_main_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_main_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_main_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_main_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_main_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = MAIN_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = MAIN_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = MAIN_FRM_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_main_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_main_frm, WGL_SW_HIDE));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: wzd_view_set_main_frm_bg
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_set_main_frm_bg (WGL_HIMG_TPL_T h_img, BOOL b_repaint)
{
    WGL_IMG_INFO_T      t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_img;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_main_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    if(b_repaint)
    {
        wzd_view_main_frm_repaint();
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_base_frm
 *
 * Description: This function creates a base frame to display background
 *              image.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_base_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_IMG_INFO_T      t_img_info;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      BASE_FRM_X,
                      BASE_FRM_Y,
                      BASE_FRM_W,
                      BASE_FRM_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_base_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_base_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = BASE_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = BASE_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = BASE_FRM_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_base_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_base_frm, WGL_SW_HIDE));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_nfy_layout_frm
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nfy_layout_frm (HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    HANDLE_T              h_cb_widget;
    WGL_NOTIFY_DATA_T*    pt_wgl_nfy_data;

    h_cb_widget     = (HANDLE_T) pv_param1;
    pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if (ui4_msg == WGL_MSG_NOTIFY)
    {
        if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_GL_GET_FOCUS) /* some widget gets focus */
        {
            wzd_app_send_msg (WZD_MSG_WGL_GET_FOCUS, NULL, 0);
        }
        else if ((h_cb_widget == t_g_view.h_seti_lst) &&
                 (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_SEL)) /* setting list element selected */
        {
            if (pt_wgl_nfy_data->u.t_lb_elem_sel.b_is_selected)
            {
                wzd_app_send_msg (WZD_MSG_WGL_SETI_LST_ELEM_SEL, NULL, 0);
            }
        }
        else if ((h_cb_widget == t_g_view.h_seti_lst) &&
                 (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_LB_ELEM_HLT) &&
                 (pt_wgl_nfy_data->u.t_lb_elem_hlt.b_is_highlighted)) /* highlight list element */
        {
            wzd_app_send_msg (WZD_MSG_WGL_SETI_LST_ELEM_HLT, NULL, 0);
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_layout_frm
 *
 * Description: This function creates a layout frame as the background of the
 *              page widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_layout_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    //WGL_IMG_INFO_T      t_img_info;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      LAYOUT_FRM_X,
                      LAYOUT_FRM_Y,
                      LAYOUT_FRM_W,
                      LAYOUT_FRM_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_base_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _wzd_nfy_layout_frm,
                                     255,
                                     (VOID*) WGL_STL_GL_NO_IMG_UI,
                                     0,
                                     & t_g_view.h_layout_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_layout_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_layout_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_layout_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_layout_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));
#if 0
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = LAYOUT_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = LAYOUT_FRM_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = LAYOUT_FRM_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_layout_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));
#endif
    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_layout_frm, WGL_SW_HIDE));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_seti_lst
 *
 * Description: This function creates a setting list to display settings for selecting.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_seti_lst (VOID)
{
    WGL_LB_INIT_T               t_lb_init;
    WGL_LB_COL_INIT_T           at_cols[1];
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_LB_COLOR_ELEM_SET_T     t_color_elem;
    //WGL_IMG_INFO_T              t_img_info;
    WGL_LB_IMG_ELEM_SET_T       t_img_elem;

    /* text */
    at_cols[0].e_col_type        = LB_COL_TYPE_TEXT;
    at_cols[0].ui1_align         = SETI_LB_COL_TEXT_ALIGN;
    at_cols[0].ui2_max_text_len  = 32;
    at_cols[0].ui2_width         = SETI_LB_COL_TEXT_W;

    t_lb_init.ui4_style          = WGL_STL_LB_ELEM_NO_PUSH
                                   | WZD_WIDGET_STYLE | WGL_STL_GL_NO_IMG_UI;

    t_lb_init.ui2_max_elem_num   = SETI_LB_ELEM_NUM;
    t_lb_init.ui2_elem_size      = SETI_LB_ELEM_H;
    t_lb_init.ui2_elem_distance  = 0;
    t_lb_init.ui1_col_num        = 1;
    t_lb_init.at_cols            = at_cols;

    SET_RECT_BY_SIZE (& t_rect,
                      SETI_LB_X,
                      SETI_LB_Y,
                      SETI_LB_W,
                      SETI_LB_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_layout_frm,
                                     HT_WGL_WIDGET_LIST_BOX,
                                     WGL_CONTENT_LIST_BOX_DEF,
                                     WGL_BORDER_NULL,
                                     &t_rect,
                                     NULL,
                                     255,
                                     & t_lb_init,
                                     NULL,
                                     & t_g_view.h_seti_lst));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = SETI_LB_COL_TEXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_COL_FONT,
                              WGL_PACK (0),
                              WGL_PACK (& t_fnt_info)));

    /* set content inset */
    t_inset.i4_left   = SETI_LB_CNT_INSET_L;
    t_inset.i4_right  = SETI_LB_CNT_INSET_R;
    t_inset.i4_top    = SETI_LB_CNT_INSET_T;
    t_inset.i4_bottom = SETI_LB_CNT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set element inset */
    t_inset.i4_left   = SETI_LB_ELEM_INSET_L;
    t_inset.i4_right  = SETI_LB_ELEM_INSET_R;
    t_inset.i4_top    = SETI_LB_ELEM_INSET_T;
    t_inset.i4_bottom = SETI_LB_ELEM_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_ELEM_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set colum inset */
    t_inset.i4_left   = SETI_LB_COL_TEXT_INSET_L;
    t_inset.i4_right  = SETI_LB_COL_TEXT_INSET_R;
    t_inset.i4_top    = SETI_LB_COL_TEXT_INSET_T;
    t_inset.i4_bottom = SETI_LB_COL_TEXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_COL_INSET,
                              WGL_PACK (0),
                              WGL_PACK (& t_inset)));

    /* set element number */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_ELEM_NUM,
                              WGL_PACK (SETI_LB_ELEM_NUM),
                              NULL));

    /* set focus to setting list */
    RET_ON_ERR (c_wgl_set_focus (t_g_view.h_seti_lst, FALSE));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_seti_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_seti_lst_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_seti_lst_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_seti_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_seti_lst_vp);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_seti_lst_vp);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_LB_VP_BK), /* viewport background color */
                              WGL_PACK (& t_color_info)));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_wzd_color_seti_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_wzd_color_seti_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_wzd_color_seti_lst_elem_hlt_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_wzd_color_seti_lst_elem_hlt_uf_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_wzd_color_seti_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_wzd_color_seti_lst_elem_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_wzd_color_seti_lst_elem_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_ELEM_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* element background color */
                              WGL_PACK (& t_color_elem)));

    t_img_elem.h_normal            = NULL_HANDLE;
    t_img_elem.h_disable           = NULL_HANDLE;
    t_img_elem.h_highlight         = SETI_LB_ELEM_IMG_BK;
    t_img_elem.h_highlight_unfocus = NULL_HANDLE;
    t_img_elem.h_pushed            = NULL_HANDLE;
    t_img_elem.h_selected          = NULL_HANDLE;
    t_img_elem.h_selected_disable  = NULL_HANDLE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_EXT_SET_ELEM_BK_IMAGE, /* element background image */
                              WGL_PACK(& t_img_elem),
                              NULL));

    COLOR_COPY (& t_color_elem.t_normal,            & t_g_wzd_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_wzd_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_wzd_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_wzd_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_wzd_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_wzd_color_help_lst_col_bk);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_wzd_color_help_lst_col_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_BK), /* columns background color */
                              WGL_PACK (& t_color_elem)));


    COLOR_COPY (& t_color_elem.t_normal,            & t_g_wzd_color_seti_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_disable,           & t_g_wzd_color_seti_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_highlight,         & t_g_wzd_color_seti_lst_col_hlt_txt);
    COLOR_COPY (& t_color_elem.t_highlight_unfocus, & t_g_wzd_color_seti_lst_col_hlt_uf_txt);
    COLOR_COPY (& t_color_elem.t_pushed,            & t_g_wzd_color_seti_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_selected,          & t_g_wzd_color_seti_lst_col_txt);
    COLOR_COPY (& t_color_elem.t_selected_disable,  & t_g_wzd_color_seti_lst_col_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_COL_COLOR,
                              WGL_PACK_2 (0, WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_elem)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_seti_lst, WGL_SW_HIDE));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_nfy_footer_frm
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_nfy_footer_frm (HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    HANDLE_T              h_cb_widget;
    WGL_NOTIFY_DATA_T*    pt_wgl_nfy_data;
    UINT32                ui4_i =0;

    h_cb_widget     = (HANDLE_T) pv_param1;
    pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if (ui4_msg == WGL_MSG_NOTIFY)
    {
        if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_GL_GET_FOCUS) /* some widget gets focus */
        {
            /*wzd_app_send_msg (WZD_MSG_WGL_GET_FOCUS, NULL, 0);*/
            for( ui4_i = 0 ; ui4_i < WZD_FOOTER_BTN_COUNT ; ui4_i++ )
            {
                if( h_cb_widget == t_g_view.ah_footer_btn[ui4_i] )
                {
                    wzd_footer_data_change( WZD_FOOTER_MSG_ITEM_FOCUSED, (VOID*)ui4_i, NULL );
                    break;
                }
            }
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_nfy_footer_frm
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_footer_btn_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32       i4_ret = WZDR_OK;
    UINT32      ui4_i =0;

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        for( ui4_i = 0 ; ui4_i < WZD_FOOTER_BTN_COUNT ; ui4_i++ )
        {
            if( h_widget == t_g_view.ah_footer_btn[ui4_i] )
            {
                break;  /* Focused button found */
            }
        }
        wzd_footer_data_change( WZD_FOOTER_MSG_KEY_INPUT, pv_param1, (VOID*)ui4_i );

        if( BTN_SELECT == (UINT32)pv_param1 )
        {
            return WZDR_OK;
        }
        break;

    default:
        break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    return i4_ret;

}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_footer_frm
 *
 * Description: This function creates a footer frame to display background
 *              image.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_footer_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_FOOTER_FRM_X,
                      WZD_FOOTER_FRM_Y,
                      WZD_FOOTER_FRM_W,
                      WZD_FOOTER_FRM_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_base_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _wzd_view_nfy_footer_frm,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_footer_frm));


    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_footer_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_footer_frm, WGL_SW_HIDE));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_footer_buttons
 *
 * Description: This function creates the footer buttons.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_footer_buttons (VOID)
{
    GL_RECT_T           at_btn_rect[WZD_FOOTER_BTN_COUNT] = WZD_FOOTER_BTN_GET_RECTS();
    UINT8               ui1_i = 0;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_FONT_INFO_T     t_fnt_info;
    INT32               i4_ret = 0;
    WGL_HIMG_TPL_T      at_img_ht_tpl[] =
                        {   h_g_wzd_img_button_highlight,
                            h_g_wzd_img_button_highlight,
                            h_g_wzd_img_button_highlight
                        };
    WGL_HIMG_TPL_T      at_img_un_ht_tpl[] =
                        {   h_g_wzd_img_button,
                            h_g_wzd_img_button,
                            h_g_wzd_img_button
                        };

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_footer_enable_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_footer_disable_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_footer_hlt_txt);

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = WZD_FOOTER_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    for( ui1_i = 0; ui1_i < WZD_FOOTER_BTN_COUNT ; ui1_i++ )
    {
        i4_ret = _wzd_view_create_btn_widget(
                t_g_view.h_footer_frm,
                L"",
                &at_btn_rect[ui1_i],
                &t_color_info,
                &t_fnt_info,
                at_img_ht_tpl[ui1_i],
                at_img_un_ht_tpl[ui1_i],
                WGL_AS_CENTER_CENTER,
                _wzd_view_footer_btn_nfy_fct,
                &t_g_view.ah_footer_btn[ui1_i]
                );
        RET_ON_ERR (i4_ret);
    }

    return WZDR_OK;
}

#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: _wzd_nfy_code_frm
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_nfy_code_frm (HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    if (ui4_msg == WGL_MSG_KEY_DOWN)
    {
        UINT32  ui4_key_code = (UINT32) pv_param1;
        UTF16_T w2s_temp[2];

        switch (ui4_key_code)
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
                w2s_temp[0] = L'0' + (ui4_key_code - BTN_DIGIT_0);
                w2s_temp[1] = 0;
                RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx],
                                          WGL_CMD_EB_SET_TEXT,
                                          WGL_PACK (w2s_temp),
                                          WGL_PACK (1)));
                RET_ON_ERR (c_wgl_repaint (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx], NULL, TRUE));

                t_g_view.aui1_code_digit[t_g_view.ui1_code_hlt_idx] = (ui4_key_code - BTN_DIGIT_0);
                wzd_view_code_txt_clear_text(TRUE);
                wzd_view_code_box_set_focus_next_digit();
                break;
            case BTN_KB_MINUS_SIGN:
            case BTN_DIGIT_DOT:
                if (t_g_view.aui1_code_style[t_g_view.ui1_code_hlt_idx] & CODE_BOX_STL_INDICATOR)
                {
                    w2s_temp[0] = t_g_view.w2_indicator;
                }
                else
                {
                    w2s_temp[0] = 0;
                }
                w2s_temp[1] = 0;
                RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx],
                                          WGL_CMD_EB_SET_TEXT,
                                          WGL_PACK (w2s_temp),
                                          WGL_PACK (1)));
                RET_ON_ERR (c_wgl_repaint (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx], NULL, TRUE));

                t_g_view.aui1_code_digit[t_g_view.ui1_code_hlt_idx] = 0xFF;
                wzd_view_code_txt_clear_text(TRUE);
                break;

            default:
                break;
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}
/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_code_frm_and_txt
 *
 * Description: This function creates code input frame for handling input, as
 *              well as the prompt text for code input validation.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_code_frm_and_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    INT32                       i4_i;

    for (i4_i = 0; i4_i < CODE_BOX_ELEM_NUM; ++i4_i)
    {
        t_g_view.ah_code_box[i4_i] = NULL_HANDLE;
        t_g_view.aui1_code_style[i4_i] = 0;
    }
    t_g_view.ui1_code_elem_num   = 0;
    t_g_view.ui1_code_hlt_idx    = 0;
    c_memset(t_g_view.aui1_code_digit, 0xFF, sizeof (t_g_view.aui1_code_digit));
    t_g_view.w2_indicator        = 0;

    t_g_view.h_code_frm          = NULL_HANDLE;
    t_g_view.h_code_txt          = NULL_HANDLE;

    SET_RECT_BY_SIZE (& t_rect,
                      CODE_FRM_X,
                      CODE_FRM_Y,
                      CODE_FRM_W,
                      CODE_FRM_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_layout_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _wzd_nfy_code_frm,
                                     255,
                                     (VOID*)WGL_STL_GL_NO_IMG_UI,
                                     0,
                                     & t_g_view.h_code_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_code_frm, WGL_SW_HIDE));

    SET_RECT_BY_SIZE (& t_rect,
                      CODE_TXT_X,
                      CODE_TXT_Y,
                      CODE_TXT_W,
                      CODE_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_layout_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_128  |
                                             WGL_STL_TEXT_MAX_DIS_5_LINE |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_code_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = CODE_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = CODE_TXT_INSET_L;
    t_inset.i4_right  = CODE_TXT_INSET_R;
    t_inset.i4_top    = CODE_TXT_INSET_T;
    t_inset.i4_bottom = CODE_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (CODE_TXT_ALIGN),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) CODE_TXT_LINE_GAPS),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_code_txt, WGL_SW_HIDE));

    return  0;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_view_clear_code_box
 *
 * Description: This function destroys the list of edit boxes for code input.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_clear_code_box (VOID)
{
    INT32       i4_i;

    for (i4_i = 0; i4_i < CODE_BOX_ELEM_NUM; ++i4_i)
    {
        if (c_handle_valid (t_g_view.ah_code_box[i4_i]))
        {
            RET_ON_ERR (c_wgl_destroy_widget (t_g_view.ah_code_box[i4_i]));
            t_g_view.ah_code_box[i4_i] = NULL_HANDLE;
            t_g_view.aui1_code_style[i4_i] = 0;
        }
    }

    t_g_view.ui1_code_elem_num   = 0;
    t_g_view.ui1_code_hlt_idx    = 0;
    c_memset(t_g_view.aui1_code_digit, 0xFF, sizeof (t_g_view.aui1_code_digit));
    t_g_view.w2_indicator        = 0;

    return  0;
}
/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_code_box
 *
 * Description: This function creates a list of edit boxes for code input.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_code_box (UINT8    ui1_code_elem_num,
                                        UINT8    aui1_code_style[],
                                        UTF16_T  aw2s_code_sep_char[])
{
    WGL_INSET_T                 t_inset;
    WGL_INSET_T                 t_inset_border;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info_bk;
    WGL_COLOR_INFO_T            t_color_info_bd;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_COLOR_INFO_T            t_color_info_sep_bk;
    WGL_COLOR_INFO_T            t_color_info_sep_bd;
    WGL_COLOR_INFO_T            t_color_info_sep;
    UTF16_T                     w2s_temp[2];
    UINT32                      ui4_border;
    INT32                       i4_i;

    if (!c_handle_valid(t_g_view.h_code_frm))
    {
        return WZDR_FAIL;
    }

    if (t_g_view.ui1_code_elem_num == ui1_code_elem_num &&
        c_memcmp(t_g_view.aui1_code_style, aui1_code_style, ui1_code_elem_num) == 0
        && t_g_view.w2_indicator == aw2s_code_sep_char[0])
    {
        return WZDR_OK;
    }

    RET_ON_ERR (_wzd_view_clear_code_box());

    t_g_view.ui1_code_elem_num = ui1_code_elem_num;

    t_g_view.w2_indicator = aw2s_code_sep_char[0];

    SET_RECT_BY_SIZE (& t_rect,
                      CODE_BOX_X,
                      CODE_BOX_Y,
                      0,
                      CODE_BOX_H);

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = CODE_BOX_FNT_SIZE;
    t_fnt_info.e_font_style = CODE_BOX_FNT_STYLE;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    /* set border inset */
    t_inset_border.i4_left   = CODE_BOX_INSET_L;
    t_inset_border.i4_right  = CODE_BOX_INSET_R;
    t_inset_border.i4_top    = CODE_BOX_INSET_T;
    t_inset_border.i4_bottom = CODE_BOX_INSET_B;

    /* set content inset */
    t_inset.i4_left   = CODE_BOX_TXT_INSET_L;
    t_inset.i4_right  = CODE_BOX_TXT_INSET_R;
    t_inset.i4_top    = CODE_BOX_TXT_INSET_T;
    t_inset.i4_bottom = CODE_BOX_TXT_INSET_B;

    /* set theme */
    t_color_info_bk.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_bk);
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_bk);
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_bk);

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box);

    t_color_info_bd.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_bd);
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_bd);
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_bd);

    /* set theme for separators */
    t_color_info_sep_bk.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_sep_bk.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep_bk);
    COLOR_COPY (& t_color_info_sep_bk.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep_bk);
    COLOR_COPY (& t_color_info_sep_bk.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep_bk);

    t_color_info_sep.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_sep.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep);
    COLOR_COPY (& t_color_info_sep.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep);
    COLOR_COPY (& t_color_info_sep.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep);

    t_color_info_sep_bd.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_sep_bd.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep_bd);
    COLOR_COPY (& t_color_info_sep_bd.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep_bd);
    COLOR_COPY (& t_color_info_sep_bd.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep_bd);

    for (i4_i = 0; i4_i < t_g_view.ui1_code_elem_num; ++i4_i)
    {
        t_rect.i4_left = t_rect.i4_right;
        if (aui1_code_style[i4_i] & CODE_BOX_STL_FULLWIDTH)
        {
            t_rect.i4_right = t_rect.i4_left + CODE_BOX_FULL_W;
        }
        else
        {
            t_rect.i4_right = t_rect.i4_left + CODE_BOX_HALF_W;
        }

        if (aui1_code_style[i4_i] & CODE_BOX_STL_NO_BORDER)
        {
            ui4_border = WGL_BORDER_NULL;
        }
        else
        {
            ui4_border = WGL_BORDER_UNIFORM;
        }

        RET_ON_ERR (c_wgl_create_widget (t_g_view.h_code_frm,
                                         HT_WGL_WIDGET_EDIT_BOX,
                                         WGL_CONTENT_EDIT_BOX_DEF,
                                         ui4_border,
                                         & t_rect,
                                         NULL,
                                         255,
                                         (VOID*) WGL_STL_GL_NO_IMG_UI,
                                         NULL,
                                         & t_g_view.ah_code_box[i4_i]));

        t_rect.i4_right += CODE_BOX_SEP;

        /* set font size */
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_GL_SET_FONT,
                                  WGL_PACK (& t_fnt_info),
                                  NULL));

        /* set border inset */
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_GL_SET_INSET,
                                  WGL_PACK (& t_inset_border),
                                  NULL));

        /* set content inset */
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_EB_SET_CNT_INSET,
                                  WGL_PACK (& t_inset),
                                  NULL));

        /* set alignment */
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_EB_SET_ALIGN,
                                  WGL_PACK (CODE_BOX_TXT_ALIGN),
                                  NULL));

        /* set theme */
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_BK), /* background color */
                                  WGL_PACK (& t_color_info_bk)));

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_GL_SET_COLOR,
                                  WGL_PACK (WGL_CLR_TEXT), /* text color */
                                  WGL_PACK (& t_color_info)));

        if (ui4_border == WGL_BORDER_UNIFORM)
        {
            RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                      WGL_CMD_GL_SET_BDR_COLOR,
                                      WGL_PACK (WGL_CLR_BDR_BK), /* border background color */
                                      WGL_PACK (& t_color_info_bd)));
        }

        /* set input limit */
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_EB_SET_INPUT_LIMIT,
                                  WGL_PACK ((UINT16) 1),
                                  NULL));

        /* set auto edit */
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_EB_SET_EXT_ATTR,
                                  WGL_PACK (WGL_EB_EA_AUTO_EDITING),
                                  WGL_PACK (WGL_EB_EA_AUTO_EDITING)));

        /* set indicator or separator */
        w2s_temp[0] = 0;
        w2s_temp[1] = 0;
        if ((aui1_code_style[i4_i] & CODE_BOX_STL_SEP_MASK) == 0)
        {
            if (aui1_code_style[i4_i] & CODE_BOX_STL_INDICATOR)
            {
                w2s_temp[0] = aw2s_code_sep_char[0];
            }
        }
        else
        {
            w2s_temp[0] = aw2s_code_sep_char[aui1_code_style[i4_i] & CODE_BOX_STL_SEP_MASK];

            /* set theme for separators */
            RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                      WGL_CMD_GL_SET_COLOR,
                                      WGL_PACK (WGL_CLR_BK), /* background color */
                                      WGL_PACK (& t_color_info_sep_bk)));

            RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                      WGL_CMD_GL_SET_COLOR,
                                      WGL_PACK (WGL_CLR_TEXT), /* text color */
                                      WGL_PACK (& t_color_info_sep)));

            if (ui4_border == WGL_BORDER_UNIFORM)
            {
                RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                          WGL_CMD_GL_SET_BDR_COLOR,
                                          WGL_PACK (WGL_CLR_BDR_BK), /* border background color */
                                          WGL_PACK (& t_color_info_sep_bd)));
            }
        }

        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[i4_i],
                                  WGL_CMD_EB_SET_TEXT,
                                  WGL_PACK (w2s_temp),
                                  WGL_PACK (1)));

        /* set visibility */
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.ah_code_box[i4_i], WGL_SW_HIDE));

        t_g_view.aui1_code_style[i4_i] = aui1_code_style[i4_i];
    }

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_code_box_set_hlt_idx
 *
 * Description: This function sets the highlight box index for code input
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_code_box_set_hlt_idx (UINT8 ui1_code_idx, BOOL b_repaint)
{
    WGL_COLOR_INFO_T            t_color_info_bk;
    WGL_COLOR_INFO_T            t_color_info_bd;
    WGL_COLOR_INFO_T            t_color_info;

    if (ui1_code_idx >= t_g_view.ui1_code_elem_num)
    {
        return -1;
    }

    /* set theme for old focus */
    t_color_info_bk.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_bk);
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_bk);
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_bk);

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box);

    t_color_info_bd.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_bd);
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_bd);
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_bd);

    if ((t_g_view.aui1_code_style[t_g_view.ui1_code_hlt_idx] & CODE_BOX_STL_SEP_MASK) != 0)
    {
        t_color_info_bk.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep_bk);
        COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep_bk);
        COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep_bk);

        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep);

        t_color_info_bd.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep_bd);
        COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep_bd);
        COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep_bd);
    }

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info_bk)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    if ((t_g_view.aui1_code_style[t_g_view.ui1_code_hlt_idx] & CODE_BOX_STL_NO_BORDER) == 0)
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx],
                                  WGL_CMD_GL_SET_BDR_COLOR,
                                  WGL_PACK (WGL_CLR_BDR_BK), /* border background color */
                                  WGL_PACK (& t_color_info_bd)));
    }

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx], NULL, TRUE));
    }

    /* set theme for new focus */
    t_g_view.ui1_code_hlt_idx = ui1_code_idx;

    t_color_info_bk.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_hlt_bk);
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_hlt_bk);
    COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_hlt_bk);

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_hlt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_hlt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_hlt);

    t_color_info_bd.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_hlt_bd);
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_hlt_bd);
    COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_hlt_bd);

    if ((t_g_view.aui1_code_style[t_g_view.ui1_code_hlt_idx] & CODE_BOX_STL_SEP_MASK) != 0)
    {
        t_color_info_bk.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep_bk);
        COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep_bk);
        COLOR_COPY (& t_color_info_bk.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep_bk);

        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep);

        t_color_info_bd.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_enable,    & t_g_wzd_color_code_box_sep_bd);
        COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_disable,   & t_g_wzd_color_code_box_sep_bd);
        COLOR_COPY (& t_color_info_bd.u_color_data.t_standard.t_highlight, & t_g_wzd_color_code_box_sep_bd);
    }

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info_bk)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx],
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    if ((t_g_view.aui1_code_style[t_g_view.ui1_code_hlt_idx] & CODE_BOX_STL_NO_BORDER) == 0)
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx],
                                  WGL_CMD_GL_SET_BDR_COLOR,
                                  WGL_PACK (WGL_CLR_BDR_BK), /* border background color */
                                  WGL_PACK (& t_color_info_bd)));
    }

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.ah_code_box[t_g_view.ui1_code_hlt_idx], NULL, TRUE));
    }
    return 0;
}

#endif

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_right_panel_icon
 *
 * Description: This function creates the demo icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_right_panel_icon (VOID)
{
    GL_RECT_T           t_rect = {0};
    INT32               i4_ret;

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_DEMO_ICON_X,
                      WZD_VIDEO_FRM_Y + WZD_VIDEO_FRM_H + 10 * WZD_UI_RATIO_W,    /* below video frm*/
                      WZD_DEMO_ICON_W,
                      170 * WZD_UI_RATIO_W);

    i4_ret = c_wgl_create_widget(t_g_view.h_main_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &t_g_view.h_right_panel_icons
                                 );

    RET_ON_ERR (i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(t_g_view.h_right_panel_icons,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_TOP,
                          NULL);
    RET_ON_ERR (i4_ret);

    /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_right_panel_icons, WGL_SW_HIDE));
    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_right_icon_show
 *
 * Description: The function shows or hides the demo picture in the right side.
 *
 * Inputs:  b_show          TRUE - Show demo pic.
 *                                 FALSE - Hide demo pic.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_right_icon_show (BOOL    b_show, BOOL    b_repaint)
{
    if (b_show) /* show demo picture */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_right_panel_icons, WGL_SW_NORMAL));
    }
    else /* hide demo picture */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_right_panel_icons, WGL_SW_HIDE));
    }

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_right_panel_icons, NULL, TRUE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_right_icon_set_image
 *
 * Description: The function set image template to the demo picture icon.
 *
 *
 *
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_right_icon_set_image (
                                WGL_HIMG_TPL_T  h_right_icon,
                                BOOL            b_repaint)
{
    WGL_IMG_INFO_T              t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_right_icon;
    t_img_info.u_img_data.t_standard.t_disable = h_right_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_right_icon;
    RET_ON_ERR (c_wgl_do_cmd(t_g_view.h_right_panel_icons, WGL_CMD_GL_SET_IMAGE, (VOID*)WGL_IMG_FG, (VOID*)&t_img_info));

    if( b_repaint )
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_right_panel_icons, NULL, TRUE));
    }

    return WZDR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_demo_icon
 *
 * Description: This function creates the demo icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_demo_txt(VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      TV_SETUP_RIGHT_PANEL_TXT_X,
                      TV_SETUP_RIGHT_PANEL_TXT_Y,
                      TV_SETUP_RIGHT_PANEL_TXT_W,
                      TV_SETUP_RIGHT_PANEL_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_512  |
                                             WGL_STL_TEXT_MAX_DIS_10_LINE |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_demo_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = DESC_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = TV_SETUP_RIGHT_PANEL_TXT_INSET_L;
    t_inset.i4_right  = TV_SETUP_RIGHT_PANEL_TXT_INSET_R;
    t_inset.i4_top    = TV_SETUP_RIGHT_PANEL_TXT_INSET_T;
    t_inset.i4_bottom = TV_SETUP_RIGHT_PANEL_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_LEFT_CENTER),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) DESC_TXT_LINE_GAPS),
                              NULL));

    /* set theme */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_right_panel;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_right_panel;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_right_panel;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_txt,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_demo_txt, WGL_SW_HIDE));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_demo_icon
 *
 * Description: This function creates the demo icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_demo_icon (VOID)
{
    GL_RECT_T           t_rect = {0};
    INT32               i4_ret;
    WGL_INSET_T         t_inset;
    WGL_IMG_INFO_T              t_img_info;

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_DEMO_ICON_X,
                      WZD_DEMO_ICON_Y,
                      WZD_DEMO_ICON_W,
                      WZD_DEMO_ICON_H);

    i4_ret = c_wgl_create_widget(t_g_view.h_main_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &t_g_view.h_demo_icon
                                 );

    RET_ON_ERR (i4_ret);

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_icon,
                              WGL_CMD_ICON_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(t_g_view.h_demo_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_LEFT_TOP,
                          NULL);
    RET_ON_ERR (i4_ret);

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_g_wzd_img_right_panel;
    t_img_info.u_img_data.t_standard.t_disable   = h_g_wzd_img_right_panel;
    t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_right_panel;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_icon,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_demo_icon, WGL_SW_NORMAL));
    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_title_txt
 *
 * Description: This function creates the text widget for Wizard title.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_title_txt (VOID)
{
	WGL_HTS_INIT_T              t_init;
    WGL_INSET_T                 t_inset;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_HTS_PARAG_ATTR_T        t_parag;

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_TITLE_TXT_X,
                      WZD_TITLE_TXT_Y,
                      WZD_TITLE_TXT_W,
                      WZD_TITLE_TXT_H);

	/* htxt info */
	c_memset (& t_init, 0, sizeof (WGL_HTS_INIT_T));
    t_init.ui4_style         = WGL_STL_GL_NO_IMG_UI;
    t_init.at_font_reg_table = NULL;
    t_init.ui2_num_reg_font  = (UINT16)0;

    /* set default font */
    c_strcpy (t_init.t_font_info_dft.a_c_font_name, t_g_view.s_font_name);
    t_init.t_font_info_dft.e_font_size  = FE_FNT_SIZE_CUSTOM;
    t_init.t_font_info_dft.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_init.t_font_info_dft.e_font_style = FE_FNT_STYLE_REGULAR;
	t_init.t_font_info_dft.ui1_custom_size	= WZD_TITLE_TXT_FNT_SIZE;

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_base_frm,
                                     HT_WGL_WIDGET_HTS,
                                     WGL_CONTENT_HTS_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(& t_init),
                                     NULL,
                                     & t_g_view.h_title_txt));

    /* set content inset */
    t_inset.i4_left   = WZD_TITLE_TXT_INSET_L;
    t_inset.i4_right  = WZD_TITLE_TXT_INSET_R;
    t_inset.i4_top    = WZD_TITLE_TXT_INSET_T;
    t_inset.i4_bottom = WZD_TITLE_TXT_INSET_B;

	RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_title_txt,
                              WGL_CMD_HTS_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));


	/* set justification */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_title_txt,
                              WGL_CMD_HTS_CUR_PARAG_SET_JUSTIF,
                              WGL_PACK (WGL_HTS_JUSTIF_CENTER),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_title_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_title_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_title_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_title_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),
                              WGL_PACK (& t_color_info)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_title_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_HTS_VP_BK),
                              WGL_PACK (& t_color_info)));


    c_memset (&t_parag, 0, sizeof(WGL_HTS_PARAG_ATTR_T));
    t_parag.e_justif = WGL_HTS_JUSTIF_CENTER;
    t_parag.ui2_indent = 0;
    t_parag.i4_line_gap_bottom = 0;
    t_parag.i4_line_gap_top = 0;
    t_parag.ui2_parag_gap_bottom = 0;
    t_parag.ui2_parag_gap_top = 0;
    RET_ON_ERR (c_wgl_do_cmd(t_g_view.h_title_txt,
                             WGL_CMD_HTS_CUR_PARAG_SET,
                             WGL_PACK(&t_parag),
                             NULL));

    /* set visibility, default show */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_title_txt, WGL_SW_NORMAL));

    return  0;
}


/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_desc_txt
 *
 * Description: This function creates a description text to display setting
 *              details.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_desc_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      DESC_TXT_X,
                      DESC_TXT_Y,
                      DESC_TXT_W,
                      DESC_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_layout_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_512  |
                                             WGL_STL_TEXT_MAX_DIS_10_LINE |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_desc_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM ;//DESC_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = DESC_TXT_INSET_L;
    t_inset.i4_right  = DESC_TXT_INSET_R;
    t_inset.i4_top    = DESC_TXT_INSET_T;
    t_inset.i4_bottom = DESC_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (DESC_TXT_ALIGN),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) DESC_TXT_LINE_GAPS),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_desc_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_desc_txt, WGL_SW_HIDE));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_scan_txt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_scan_txt (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      SCAN_TXT_X,
                      SCAN_TXT_Y,
                      SCAN_TXT_W,
                      SCAN_TXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_layout_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_512  |
                                             WGL_STL_TEXT_MAX_DIS_5_LINE |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_scan_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = DESC_TXT_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = SCAN_TXT_INSET_L;
    t_inset.i4_right  = SCAN_TXT_INSET_R;
    t_inset.i4_top    = SCAN_TXT_INSET_T;
    t_inset.i4_bottom = SCAN_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (SCAN_TXT_ALIGN),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) SCAN_TXT_LINE_GAPS),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_scan_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_scan_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_scan_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_scan_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_scan_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_scan_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    /* set visibility, default show */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_scan_txt, WGL_SW_HIDE));

    return  0;
}


/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_scan_bar
 *
 * Description: This function creates a progress bar to display scanning status.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_scan_bar (VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;
    WGL_IMG_INFO_T              t_img_info;
    WGL_PG_LEVELS_INFO_T        t_pg_levels;
	WGL_PG_IDR_LOC_T             t_pg_idr_loc;

    SET_RECT_BY_SIZE (& t_rect,
                      SCAN_BAR_X,
                      SCAN_BAR_Y,
                      SCAN_BAR_W,
                      SCAN_BAR_H);

	t_pg_idr_loc.t_loc_rect.i4_left = SCAN_BAR_X;
	t_pg_idr_loc.t_loc_rect.i4_right = SCAN_BAR_X + SCAN_BAR_W;
	t_pg_idr_loc.t_loc_rect.i4_top = SCAN_BAR_Y;
	t_pg_idr_loc.t_loc_rect.i4_bottom = SCAN_BAR_Y + SCAN_BAR_H;
	t_pg_idr_loc.ui1_align = WGL_AS_CENTER_CENTER;

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_layout_frm,
                                     HT_WGL_WIDGET_PROGRESS_BAR,
                                     WGL_CONTENT_PROGRESS_BAR_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     230,
                                     (VOID*)(WGL_STL_GL_NO_BK |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_scan_bar));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = SCAN_BAR_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_bar,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set inset */
    t_inset.i4_left   = SCAN_BAR_INSET_L;
    t_inset.i4_right  = SCAN_BAR_INSET_R;
    t_inset.i4_top    = SCAN_BAR_INSET_T;
    t_inset.i4_bottom = SCAN_BAR_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_bar,
                              WGL_CMD_PG_SET_BAR_INSET,
                              WGL_PACK (& t_inset),
                              NULL));
    /* set alignment */
	t_pg_idr_loc.ui1_align = WGL_AS_CENTER_CENTER;
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_bar,
						  WGL_CMD_PG_SET_IDR_LOC,
						  WGL_PACK(WGL_PG_CNT_ILT_POS),
						  WGL_PACK(&t_pg_idr_loc))); 

    /* set range */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_bar,
                              WGL_CMD_PG_SET_RANGE,
                              WGL_PACK((INT32)0),
                              WGL_PACK((INT32)100)));

    /* set levels */
    t_pg_levels.a_boundary[0]    = 100;
    t_pg_levels.ui1_level_number = 1;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_bar,
                              WGL_CMD_PG_SET_LEVELS,
                              WGL_PACK(&t_pg_levels),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_scan_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_scan_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_scan_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_bar,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (& t_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = SCAN_BAR_IMG_BK;
    t_img_info.u_img_data.t_standard.t_disable   = SCAN_BAR_IMG_BK;
    t_img_info.u_img_data.t_standard.t_highlight = SCAN_BAR_IMG_BK;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_bar,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_PG_BODY), /* bar background image */
                              WGL_PACK (& t_img_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = SCAN_BAR_IMG_LEVEL;
    t_img_info.u_img_data.t_standard.t_disable   = SCAN_BAR_IMG_LEVEL;
    t_img_info.u_img_data.t_standard.t_highlight = SCAN_BAR_IMG_LEVEL;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_scan_bar,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_PG_LEVEL_1), /* bar level image */
                              WGL_PACK (& t_img_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_scan_bar, WGL_SW_HIDE));

    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_seti_icon
 *
 * Description: This function creates an icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_seti_icon (VOID)
{
    GL_RECT_T                   t_rect = {0};
    INT32                       i4_ret;

    i4_ret = c_wgl_create_widget(t_g_view.h_layout_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)(WGL_STL_GL_NO_BK),
                                 NULL,
                                 &t_g_view.h_seti_icon
                                 );
    RET_ON_ERR (i4_ret);

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(t_g_view.h_seti_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_CENTER,
                          NULL);
    RET_ON_ERR (i4_ret);
    return  0;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_footer_get_next_enabled_btn
 *
 * Description: This function get the next enable footer btn from a specified index.
 *
 * Inputs:           e_footer_index - The index of the specified footer button
 *                      pe_next_enabled_index - the index of the next enabled footer button
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed. If not found, it will return WZDR_FAIL.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_footer_get_next_enabled_btn (
                                WZD_FOOTER_BTN_INDEX_T  e_footer_index,
                                WZD_FOOTER_BTN_INDEX_T* pe_next_enabled_index)
{
    UINT32 ui4_j = 0;

    if( pe_next_enabled_index == NULL )
    {
        return WZDR_FAIL;
    }

    if( e_footer_index >= WZD_FOOTER_BTN_COUNT )
    {
        return WZDR_FAIL;
    }

    ui4_j = e_footer_index + 1;

    while( ui4_j < WZD_FOOTER_BTN_COUNT )
    {
        if( TRUE == t_g_view.t_footer_info.ab_enabled[ui4_j] )
        {
            *pe_next_enabled_index = (WZD_FOOTER_BTN_INDEX_T)ui4_j;
            return WZDR_OK;
        }
        ui4_j++;
    }

    return  WZDR_FAIL;  /* Not found */
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_demo_txt_set_text
 *
 * Description: The function shows or hides the demo text in the right side.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_demo_txt_set_text (UTF16_T*  pw2s_text,
                                    HANDLE_T    h_bk_img)
{
    WGL_IMG_INFO_T              t_img_info;

    /* set theme */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = h_bk_img;
    t_img_info.u_img_data.t_standard.t_disable   = h_bk_img;
    t_img_info.u_img_data.t_standard.t_highlight = h_bk_img;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_txt,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (& t_img_info)));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_demo_txt,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (pw2s_text),
                      WGL_PACK (c_uc_w2s_strlen (pw2s_text))));

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_demo_txt_show
 *
 * Description: The function shows or hides the demo txt in the right side.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_demo_txt_show (BOOL        b_show,
                              BOOL        b_repaint)
{
    if (b_show) /* show right panel demo txt*/
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_demo_txt, WGL_SW_NORMAL));
    }
    else /* hide demo txt */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_demo_txt, WGL_SW_HIDE));
    }

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_demo_txt, NULL, TRUE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_demo_pic_show
 *
 * Description: The function shows or hides the demo picture in the right side.
 *
 * Inputs:  b_show          TRUE - Show demo pic.
 *                                 FALSE - Hide demo pic.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_demo_pic_show (BOOL    b_show)
{
    if (b_show) /* show demo picture */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_demo_icon, WGL_SW_NORMAL));
    }
    else /* hide demo picture */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_demo_icon, WGL_SW_HIDE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_demo_pic_set_image
 *
 * Description: The function set image template to the demo picture icon.
 *
 *
 *
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_demo_pic_set_image (
                                WGL_HIMG_TPL_T  h_demo_image,
                                BOOL            b_repaint)
{
    WGL_IMG_INFO_T              t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_demo_image;
    t_img_info.u_img_data.t_standard.t_disable = h_demo_image;
    t_img_info.u_img_data.t_standard.t_highlight = h_demo_image;
    RET_ON_ERR (c_wgl_do_cmd(t_g_view.h_demo_icon, WGL_CMD_GL_SET_IMAGE, (VOID*)WGL_IMG_FG, (VOID*)&t_img_info));

    if( b_repaint )
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_demo_icon, NULL, TRUE));
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_footer_get_previous_enabled_btn
 *
 * Description: This function get the prevous enable footer btn from a specified index.
 *
 * Inputs:           e_footer_index - The index of the specified footer button
 *                      pe_pre_enabled_index - the index of the previous enabled footer button
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed. If not found, it will return WZDR_FAIL.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_footer_get_previous_enabled_btn (
                                WZD_FOOTER_BTN_INDEX_T  e_footer_index,
                                WZD_FOOTER_BTN_INDEX_T* pe_pre_enabled_index)
{
    INT32 i4_j = 0;

    if( pe_pre_enabled_index == NULL )
    {
        return WZDR_FAIL;
    }

    if( e_footer_index >= WZD_FOOTER_BTN_COUNT )
    {
        return WZDR_FAIL;
    }

    i4_j  = e_footer_index - 1;

    while( i4_j >= WZD_FOOTER_BTN_01 )
    {
        if( TRUE == t_g_view.t_footer_info.ab_enabled[i4_j] )
        {
            *pe_pre_enabled_index = (WZD_FOOTER_BTN_INDEX_T)i4_j;
            return WZDR_OK;
        }
        i4_j--;
    }

    return  WZDR_FAIL;  /* Not found */
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_set_visibility
 *
 * Description: The function shows or hides the footer.
 *
 * Inputs:  b_show                 TRUE - Show footer.
 *                                 FALSE - Hide footer.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_footer_set_visibility (BOOL    b_show)
{
    if (b_show) /* show main frame */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_footer_frm, WGL_SW_NORMAL));
    }
    else /* hide main frame */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_footer_frm, WGL_SW_HIDE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_show
 *
 * Description: The function shows or hides the footer.
 *
 * Inputs:  b_show                 TRUE - Show footer.
 *                                 FALSE - Hide footer.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_footer_show (BOOL    b_show)
{
    if (b_show) /* show main frame */
    {
        RET_ON_ERR (c_wgl_show (t_g_view.h_footer_frm, WGL_SW_RECURSIVE));
    }
    else /* hide main frame */
    {
        RET_ON_ERR (c_wgl_show (t_g_view.h_footer_frm, WGL_SW_HIDE_RECURSIVE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_frm_repaint
 *
 * Description: This API repaints the footer frm.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_footer_frm_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_footer_frm, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_set_text
 *
 * Description: The function set text to footer buttons.
 *
 * Inputs:  e_footer_index                 Which footer button.
 * Inputs:  pw2s_text                       The footer text.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_footer_set_text (WZD_FOOTER_BTN_INDEX_T e_footer_index, UTF16_T* pw2s_text)
{
    INT32   i4_ret = WZDR_OK;

    i4_ret = c_wgl_do_cmd(
                t_g_view.ah_footer_btn[e_footer_index],
                WGL_CMD_BTN_SET_TEXT,
                WGL_PACK(pw2s_text),
                WGL_PACK((UINT16)0xFFFF));

    RET_ON_ERR (i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_set_btn_num
 *
 * Description: The function set footer buttons num.
 *
 * Inputs:  ui1_btn_num                footer button num.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_footer_set_btn_num (const UINT8 ui1_btn_num)
{
	GL_RECT_T   	t_rect;
	UINT8			ui1_i = 0;
	INT32   		i4_ret = WZDR_OK;
	INT32   		i4_left = 0; /* left margins */


	/* 3-buttons are special case */
	if (ui1_btn_num >= WZD_FOOTER_BTN_COUNT)
	{
		wzd_view_footer_set_enable(WZD_FOOTER_BTN_03, TRUE);
	}
	else
	{
		wzd_view_footer_set_enable(WZD_FOOTER_BTN_03, FALSE);
	}

	/* update visible button position */
	if (ui1_btn_num > 0)
	{
		/* the first button left margins */
		i4_left = (WZD_FOOTER_FRM_W - ui1_btn_num*WZD_FOOTER_BTN_W - (ui1_btn_num-1)*WZD_FOOTER_BTN_GAP)/2;

		for (ui1_i = 0; ui1_i < ui1_btn_num; ui1_i ++)
		{
			/* update button position */
			SET_RECT_BY_SIZE (&t_rect,
				(i4_left + (WZD_FOOTER_BTN_W + WZD_FOOTER_BTN_GAP) * ui1_i),
				WZD_FOOTER_BTN_Y,
				WZD_FOOTER_BTN_W,
				WZD_FOOTER_BTN_H);

			i4_ret = c_wgl_move(
				t_g_view.ah_footer_btn[ui1_i],
				&t_rect, 
				FALSE);
    		RET_ON_ERR (i4_ret);
		}
	}

	if (ui1_btn_num >= WZD_FOOTER_BTN_COUNT)
	{
		/* three footer buttons need to show */
		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_01],
				WGL_SW_NORMAL);
    	RET_ON_ERR (i4_ret);

		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_02],
				WGL_SW_NORMAL);
    	RET_ON_ERR (i4_ret);

		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_03],
				WGL_SW_NORMAL);
    	RET_ON_ERR (i4_ret);
	}
	else if (ui1_btn_num == 2)
	{	
		/* two footer buttons need to show */
		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_01],
				WGL_SW_NORMAL);
    	RET_ON_ERR (i4_ret);

		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_02],
				WGL_SW_NORMAL);
    	RET_ON_ERR (i4_ret);

		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_03],
				WGL_SW_HIDE);
    	RET_ON_ERR (i4_ret);
	}
	else if (ui1_btn_num == 1)
	{
		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_01],
				WGL_SW_NORMAL);
    	RET_ON_ERR (i4_ret);

		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_02],
				WGL_SW_HIDE);
    	RET_ON_ERR (i4_ret);

		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_03],
				WGL_SW_HIDE);
    	RET_ON_ERR (i4_ret);
	}
	else
	{
		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_01],
				WGL_SW_HIDE);
    	RET_ON_ERR (i4_ret);

		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_02],
				WGL_SW_HIDE);
    	RET_ON_ERR (i4_ret);

		i4_ret = c_wgl_set_visibility(
				t_g_view.ah_footer_btn[WZD_FOOTER_BTN_03],
				WGL_SW_HIDE);
    	RET_ON_ERR (i4_ret);
	}

	return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_set_enable
 *
 * Description: The function set enable state to footer buttons.
 *
 * Inputs:  e_footer_index                 Which footer button.
 * Inputs:  b_enable                         Enable or disable.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_footer_set_enable (WZD_FOOTER_BTN_INDEX_T e_footer_index, BOOL b_enable)
{	
	t_g_view.t_footer_info.ab_enabled[e_footer_index] = b_enable;

   	c_wgl_enable(
                t_g_view.ah_footer_btn[e_footer_index],
                b_enable);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_get_enable
 *
 * Description: The function get enable state of footer buttons.
 *
 * Inputs:  e_footer_index                 Which footer button.
 *
 * Outputs: -
 *
 * Returns: TRUE                   Be enable.
 *          Any other values       Be dis enable.
 ----------------------------------------------------------------------------*/
BOOL wzd_view_footer_get_enable (WZD_FOOTER_BTN_INDEX_T e_footer_index)
{
    return t_g_view.t_footer_info.ab_enabled[e_footer_index];
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_set_focus
 *
 * Description: The function set focus to footer buttons.
 *
 * Inputs:  e_footer_index                 Which footer button.
 * Inputs:  b_repaint                        auto repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_footer_set_focus (WZD_FOOTER_BTN_INDEX_T e_footer_index, BOOL b_repaint)
{
    INT32   i4_ret = WZDR_OK;

    t_g_view.t_footer_info.e_focused_btn = e_footer_index;

    i4_ret = c_wgl_set_focus(
                t_g_view.ah_footer_btn[e_footer_index],
                b_repaint);

    RET_ON_ERR (i4_ret);

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_get_handle
 *
 * Description: The function get handle of footer buttons.
 *
 * Inputs:  e_footer_index                 Which footer button.
 * Inputs:  b_repaint                        auto repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
HANDLE_T wzd_view_footer_get_handle (WZD_FOOTER_BTN_INDEX_T e_footer_index)
{
    return t_g_view.ah_footer_btn[e_footer_index];
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_footer_update_btn_navigation
 *
 * Description: The function update the focus transition.
 *
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_footer_update_btn_navigation (VOID)
{
    INT32           i4_ret = WZDR_OK;
    WZD_FOOTER_BTN_INDEX_T e_next_enable_index = WZD_FOOTER_BTN_COUNT;
    WZD_FOOTER_BTN_INDEX_T e_pre_enable_index = WZD_FOOTER_BTN_COUNT;
    WGL_KEY_LINK_T  at_key_lnk[2];
    UINT8           ui1_i = 0;
    UINT8           ui1_key_lnk_num = 0;

    for( ui1_i = 0 ; ui1_i < WZD_FOOTER_BTN_COUNT ; ui1_i ++ )
    {
        i4_ret = _wzd_view_footer_get_next_enabled_btn( ui1_i, &e_next_enable_index );
        if( WZDR_OK == i4_ret )
        {
            at_key_lnk[ui1_key_lnk_num].ui4_key  = BTN_CURSOR_RIGHT;
            at_key_lnk[ui1_key_lnk_num].h_widget = t_g_view.ah_footer_btn[e_next_enable_index];
            ui1_key_lnk_num++;
        }

        i4_ret = _wzd_view_footer_get_previous_enabled_btn( ui1_i, &e_pre_enable_index );
        if( WZDR_OK == i4_ret )
        {
            at_key_lnk[ui1_key_lnk_num].ui4_key  = BTN_CURSOR_LEFT;
            at_key_lnk[ui1_key_lnk_num].h_widget = t_g_view.ah_footer_btn[e_pre_enable_index];
            ui1_key_lnk_num++;
        }

        if( ui1_key_lnk_num > 0 )
        {
            i4_ret = c_wgl_set_navigation(t_g_view.ah_footer_btn[ui1_i], ui1_key_lnk_num, at_key_lnk);
            RET_ON_ERR (i4_ret);
        }
        ui1_key_lnk_num = 0;
    }

    return WZDR_OK;
}


/*-----------------------------------------------------------------------------
 * Name: wzd_view_main_frm_set_visibility
 *
 * Description: This API sets visibility to description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_main_frm_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_main_frm, WGL_SW_RECURSIVE);
    }
    else /* hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_main_frm, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_main_frm_show
 *
 * Description: The function shows or hides the main frame.
 *
 * Inputs:  b_show                 TRUE - Show main frame.
 *                                 FALSE - Hide main frame.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_main_frm_show (BOOL    b_show)
{
    if (b_show) /* show main frame */
    {
        RET_ON_ERR (c_wgl_show (t_g_view.h_main_frm, WGL_SW_NORMAL));
    }
    else /* hide main frame */
    {
        RET_ON_ERR (c_wgl_show (t_g_view.h_main_frm, WGL_SW_HIDE));
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_main_frm_repaint
 *
 * Description: This API repaints the title list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_main_frm_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_main_frm, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_desc_txt_set_visibility
 *
 * Description: This API sets visibility to description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_desc_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_txt, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_desc_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_desc_txt_set_text
 *
 * Description: This API sets text to the description text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_desc_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_desc_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_desc_txt_repaint
 *
 * Description: This API repaints the description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_desc_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_desc_txt, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_title_txt_set_visibility
 *
 * Description: This API sets visibility to title text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_title_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_title_txt, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_title_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_title_txt_set_text
 *
 * Description: This API sets text to the title text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_title_txt_set_text (UTF16_T*    pw2s_text)
{
	UINT16                 ui2_sec_id = 0;
	WGL_HTS_TEXT_INFO_T    t_hts_txt_info;
	
    c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));

	RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_title_txt,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL));

	/* Set font data. */
    c_strcpy (t_hts_txt_info.t_font.a_c_font_name, t_g_view.s_font_name);

	t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_LARGE;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

	/* Set text background color. */
    COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_wzd_color_desc_txt);
    COLOR_COPY (&t_hts_txt_info.t_clr_text_bk, &t_g_wzd_color_desc_txt_bk);

	t_hts_txt_info.t_string.w2s_str = pw2s_text;
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

    RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                            WGL_PACK (&t_hts_txt_info),
                            WGL_PACK (&ui2_sec_id)));
	
    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_title_txt_set_text_ex
 *
 * Description: This API sets text to the title text widget.
 *
 * Inputs:  pw2s_msg           Text to be set.
 *          pw2s_txt		   Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_title_txt_set_text_ex (UTF16_T* pw2s_msg, UTF16_T* pw2s_txt)
{
	UINT16                 ui2_sec_id = 0;
	WGL_HTS_TEXT_INFO_T    t_hts_txt_info;
	
    c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));

	RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_title_txt,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL));

	/* Set font data. */
    c_strcpy (t_hts_txt_info.t_font.a_c_font_name, t_g_view.s_font_name);

	t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_LARGE;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

	/* Set first text section color. */
    COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_wzd_color_title_txt_nor);
    COLOR_COPY (&t_hts_txt_info.t_clr_text_bk, &t_g_wzd_color_title_txt_bk);

	t_hts_txt_info.t_string.w2s_str = pw2s_msg;
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

	ui2_sec_id = 0;
    RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                            WGL_PACK (&t_hts_txt_info),
                            WGL_PACK (&ui2_sec_id)));


	/* Set second text section color. */
    COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_wzd_color_title_txt_hlt);
    COLOR_COPY (&t_hts_txt_info.t_clr_text_bk, &t_g_wzd_color_title_txt_bk);

	t_hts_txt_info.t_string.w2s_str = pw2s_txt;
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

	ui2_sec_id = 1;
	RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                            WGL_PACK (&t_hts_txt_info),
                            WGL_PACK (&ui2_sec_id)));
	
    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_title_set_htxt
 *
 * Description: This API sets hyper-text to the title text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *			h_img           	Icon to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_title_set_htxt (UTF16_T* pw2s_text, WGL_HIMG_TPL_T h_img)
{
    UINT16                 ui2_sec_id = 0;
    WGL_HTS_TEXT_INFO_T    t_hts_txt_info;
    WGL_HTS_IMG_INFO_T     t_hts_img_info;
    UTF16_T                w2s_pic_flag[TITLE_PIC_FLAG_LEN + 1];
    UTF16_T*               pw2s_next = NULL;
    UTF16_T*               pw2s_temp = pw2s_text;
	
    c_memset (&t_hts_txt_info, 0, sizeof(WGL_HTS_TEXT_INFO_T));
    c_memset (&t_hts_img_info, 0, sizeof(WGL_HTS_IMG_INFO_T));
    c_memset (w2s_pic_flag, 0, sizeof(w2s_pic_flag));

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_title_txt,
                              WGL_CMD_HTS_CLEAR_ALL,
                              WGL_PACK (FALSE),
                              NULL));
    /* Set font data. */
    c_strcpy (t_hts_txt_info.t_font.a_c_font_name, t_g_view.s_font_name);

    t_hts_txt_info.t_font.e_font_cmap  = FE_CMAP_ENC_UNICODE;
    t_hts_txt_info.t_font.e_font_style = FE_FNT_STYLE_REGULAR;
    t_hts_txt_info.t_font.e_font_size  = FE_FNT_SIZE_CUSTOM;
	t_hts_txt_info.t_font.ui1_custom_size = WZD_TITLE_TXT_FNT_SIZE;

    t_hts_txt_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;

    /* Set text background color. */
    COLOR_COPY (&t_hts_txt_info.t_clr_text, &t_g_wzd_color_title_txt_hlt);
    COLOR_COPY (&t_hts_txt_info.t_clr_text_bk, &t_g_wzd_color_title_txt_bk);

	/* Append first "-" icon and "  " */
	t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
	t_hts_img_info.h_img = h_g_wzd_img_title_dash;
	
	RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
                            WGL_CMD_HTS_APPEND_IMG_SEC,
                            WGL_PACK(&t_hts_img_info),
                            WGL_PACK(&ui2_sec_id)));

	t_hts_txt_info.t_string.w2s_str = WZD_CUSTOM_TEXT("  ");
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

    RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                            WGL_PACK (&t_hts_txt_info),
                            WGL_PACK (&ui2_sec_id)));


	/* Parse hyper-text */
    c_uc_ps_to_w2s (TITLE_PIC_FLAG, w2s_pic_flag, sizeof(w2s_pic_flag));
    pw2s_next = _wzd_view_w2s_sch(pw2s_temp, w2s_pic_flag);
	
	if(NULL == pw2s_next)
	{
		/* no icon need to show */
		t_hts_txt_info.t_string.w2s_str = pw2s_text;
        t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_text);
        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

        RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
                                WGL_CMD_HTS_APPEND_TEXT_SEC,
                                WGL_PACK (&t_hts_txt_info),
                                WGL_PACK (&ui2_sec_id)));
		
	}
	else
	{
	    while (pw2s_next)
	    {
	        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
	        t_hts_txt_info.t_string.ui2_len_str = pw2s_next - pw2s_temp;
	        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * (pw2s_next - pw2s_temp);

	        RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
	                                WGL_CMD_HTS_APPEND_TEXT_SEC,
	                                WGL_PACK (&t_hts_txt_info),
	                                WGL_PACK (&ui2_sec_id)));

	        t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
	        t_hts_img_info.h_img = h_img;

	        RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
	                                WGL_CMD_HTS_APPEND_IMG_SEC,
	                                WGL_PACK(&t_hts_img_info),
	                                WGL_PACK(&ui2_sec_id)));

	        pw2s_temp = pw2s_next + c_uc_w2s_strlen(w2s_pic_flag);
	        pw2s_next = _wzd_view_w2s_sch(pw2s_temp, w2s_pic_flag);
	    }

	    if (pw2s_temp < pw2s_text + c_uc_w2s_strlen(pw2s_text))
	    {
	        t_hts_txt_info.t_string.w2s_str = pw2s_temp;
	        t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(pw2s_temp);
	        t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

	        RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
	                                WGL_CMD_HTS_APPEND_TEXT_SEC,
	                                WGL_PACK (&t_hts_txt_info),
	                                WGL_PACK (&ui2_sec_id)));
	    }
	}

	/* Append "  " and the last "-" icon */
	t_hts_txt_info.t_string.w2s_str = WZD_CUSTOM_TEXT("  ");
    t_hts_txt_info.t_string.ui2_len_str = c_uc_w2s_strlen(t_hts_txt_info.t_string.w2s_str);
    t_hts_txt_info.t_string.ui2_size_buf = sizeof(UTF16_T) * t_hts_txt_info.t_string.ui2_len_str;

    RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
                            WGL_CMD_HTS_APPEND_TEXT_SEC,
                            WGL_PACK (&t_hts_txt_info),
                            WGL_PACK (&ui2_sec_id)));
	
	t_hts_img_info.e_v_anchor = WGL_HTS_V_ANCHOR_CENTER;
	t_hts_img_info.h_img = h_g_wzd_img_title_dash;
	
	RET_ON_ERR(c_wgl_do_cmd(t_g_view.h_title_txt,
                            WGL_CMD_HTS_APPEND_IMG_SEC,
                            WGL_PACK(&t_hts_img_info),
                            WGL_PACK(&ui2_sec_id)));

    return (WZDR_OK);
}


/*-----------------------------------------------------------------------------
 * Name: wzd_view_title_txt_repaint
 *
 * Description: This API repaints the title text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_title_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_title_txt, NULL, TRUE);
}


/*-----------------------------------------------------------------------------
 * Name: wzd_view_scan_bar_set_visibility
 *
 * Description: This API sets visibility to scan progrsss bar widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_scan_bar_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_scan_bar, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_scan_bar, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_scan_bar_set_pos
 *
 * Description: This API sets progress level to the scan progress bar widget.
 *
 * Inputs:  i4_progress         Progress level to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_scan_bar_set_pos (INT32    i4_progress)
{
    return  c_wgl_do_cmd (t_g_view.h_scan_bar,
                          WGL_CMD_PG_SET_POS,
                          WGL_PACK (i4_progress),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_scan_bar_repaint
 *
 * Description: This API repaints the scan progress bar widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_scan_bar_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_scan_bar, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_scan_txt_set_visibility
 *
 * Description: This API sets visibility to scan text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_scan_txt_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_scan_txt, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
        return  c_wgl_set_visibility (t_g_view.h_scan_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_scan_txt_repaint
 *
 * Description: This API repaints the scan text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_scan_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_scan_txt, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_scan_txt_set_text
 *
 * Description: This API sets text to the scan text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_scan_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_scan_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_icon_set_visibility
 *
 * Description: This API sets visibility to setting icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_icon_set_visibility (BOOL b_show)
{
    return  c_wgl_set_visibility (t_g_view.h_seti_icon,
                                  b_show ? WGL_SW_NORMAL : WGL_SW_HIDE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_icon_load_img
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_icon_load_img (WZD_PAGE_INFO_ICON_DATA* pt_icon_data,
                                   UINT16                   ui2_idx)
{
    INT32                       i4_ret;
    WGL_IMG_INFO_T              t_img_info;

    i4_ret = c_wgl_move(t_g_view.h_seti_icon,
                        &pt_icon_data->t_rect,
                        FALSE);
    RET_ON_ERR (i4_ret);

    t_img_info.e_type                            = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = pt_icon_data->at_img_tpl[ui2_idx];
    t_img_info.u_img_data.t_standard.t_disable   = pt_icon_data->at_img_tpl[ui2_idx];
    t_img_info.u_img_data.t_standard.t_highlight = pt_icon_data->at_img_tpl[ui2_idx];
    i4_ret = c_wgl_do_cmd(t_g_view.h_seti_icon,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info)
                          );
    RET_ON_ERR (i4_ret);

    return 0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_icon_repaint
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_icon_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_seti_icon, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_set_visibility
 *
 * Description: This API sets visibility to setting list widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_set_visibility (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        return  c_wgl_set_visibility (t_g_view.h_seti_lst, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
         return  c_wgl_set_visibility (t_g_view.h_seti_lst, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_clr_elems
 *
 * Description: This API clears the elements of the setting list within a given
 *              range.
 *
 * Inputs:  ui2_start           Start index.
 *          ui2_end             End index.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_clr_elems (UINT16    ui2_start,
                                   UINT16    ui2_end)
{
    return  c_wgl_do_cmd (t_g_view.h_seti_lst,
                          WGL_CMD_LB_CLEAR_ELEMS_BY_RANGE,
                          WGL_PACK (ui2_start),
                          WGL_PACK (ui2_end));
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_enable_control_key
 *
 * Description: This API enables/disables the control keys for the setting list.
 *
 * Inputs:  b_enable            TRUE - Enable control keys.
 *                              FALSE - Disable control keys.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_enable_control_key (BOOL    b_enable)
{
    INT32               i4_rc;
    WGL_LB_KEY_MAP_T    t_key_map;

    if (b_enable) /* enable control keys */
    {
        t_key_map.ui4_key_next      = BTN_CURSOR_DOWN;
        t_key_map.ui4_key_prev      = BTN_CURSOR_UP;
        t_key_map.ui4_key_select    = BTN_SELECT;
        t_key_map.ui4_key_page_up   = 0;
        t_key_map.ui4_key_page_down = 0;

        i4_rc = c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_KEY_MAP,
                              WGL_PACK (& t_key_map),
                              NULL);
    }
    else /* disable control keys */
    {
        t_key_map.ui4_key_next      = 0;
        t_key_map.ui4_key_prev      = 0;
        t_key_map.ui4_key_select    = 0;
        t_key_map.ui4_key_page_up   = 0;
        t_key_map.ui4_key_page_down = 0;

        i4_rc = c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_SET_KEY_MAP,
                              WGL_PACK (& t_key_map),
                              NULL);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_get_hlt_idx
 *
 * Description: This API gets current highlighted index in the setting list.
 *
 * Inputs:  -
 *
 * Outputs: pui2_idx            Highlighted index.
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_get_hlt_idx (UINT16*    pui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_seti_lst,
                          WGL_CMD_LB_GET_HLT_INDEX,
                          WGL_PACK (pui2_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_hlt_elem
 *
 * Description: This API highlights a specific element in the setting list.
 *
 * Inputs:  ui2_idx             The index of element to be highlighted.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_hlt_elem (UINT16    ui2_idx)
{
    INT32 i4_rc;

    i4_rc = c_wgl_do_cmd (t_g_view.h_seti_lst,
                          WGL_CMD_LB_HLT_ELEM,
                          WGL_PACK (ui2_idx),
                          NULL);
    if (i4_rc != WGLR_OK)
    {
        return i4_rc;
    }

    /* move as the last visible element */
    if (ui2_idx >= SETI_LB_PAGE_ELEM_NUM)
    {
        i4_rc = c_wgl_do_cmd (t_g_view.h_seti_lst,
                              WGL_CMD_LB_MOVE_ELEM_VISIBLE,
                              WGL_PACK (ui2_idx),
                              WGL_PACK (SETI_LB_PAGE_ELEM_NUM - 1));
    }

    return i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_unhlt_elem
 *
 * Description: This API unhighlights an elements in the setting list.
 *
 * Inputs:  ui2_idx             The index of element to be unhighlighted.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_unhlt_elem (UINT16    ui2_idx)
{
    return  c_wgl_do_cmd (t_g_view.h_seti_lst,
                          WGL_CMD_LB_UNHLT_ELEM,
                          WGL_PACK (ui2_idx),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_set_elem_num
 *
 * Description: This API sets the number of elements to the setting list.
 *
 * Inputs:  ui2_elem_num        The number of elements to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_set_elem_num (UINT16    ui2_elem_num)
{
    return  c_wgl_do_cmd (t_g_view.h_seti_lst,
                          WGL_CMD_LB_SET_ELEM_NUM,
                          WGL_PACK (ui2_elem_num),
                          NULL);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_set_elem_text
 *
 * Description: This API sets the element data of a given index to the setting
 *              list.
 *
 * Inputs:  ui2_elem_idx     Element index.
 *          pw2s_text        Element data.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_set_elem_text (UINT16       ui2_elem_idx,
                                       UTF16_T*     pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_seti_lst,
                          WGL_CMD_LB_SET_ITEM_TEXT,
                          WGL_PACK_2 (ui2_elem_idx, 0),
                          WGL_PACK (pw2s_text));
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_setting_lst_repaint_elems
 *
 * Description: This API repaints the elements within a given range.
 *
 * Inputs:  ui2_start           Start index.
 *          ui2_end             End index.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_repaint_elems (UINT16    ui2_start,
                                       UINT16    ui2_end)
{
    return  c_wgl_do_cmd (t_g_view.h_seti_lst,
                          WGL_CMD_LB_REPAINT_ELEMS,
                          WGL_PACK (ui2_start),
                          WGL_PACK (ui2_end));
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_reset
 *
 * Description: This API resets all the elements in the setting list.
 *
 * Inputs:  b_repaint           Repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_reset (BOOL    b_repaint)
{
    INT32    i4_rc;

    i4_rc = c_wgl_do_cmd (t_g_view.h_seti_lst,
                          WGL_CMD_LB_CLEAR_ELEMS_BY_RANGE,
                          WGL_PACK (0),
                          WGL_PACK (SETI_LB_ELEM_NUM-1));

    /* repaint */
    if ((i4_rc == WGLR_OK) && (b_repaint))
    {
        i4_rc = c_wgl_repaint (t_g_view.h_seti_lst, NULL, TRUE);
    }

    return  i4_rc;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_seti_lst_repaint
 *
 * Description: This API repaints the setting list.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_seti_lst_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_seti_lst, NULL, TRUE);
}

#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_box_set_visibility
 *
 * Description: This API sets visibility to description text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_box_set_visibility_focus (BOOL    b_show)
{
    if (b_show) /* visible */
    {
        /* set focus to setting list */
        RET_ON_ERR (c_wgl_set_focus (t_g_view.h_code_frm, FALSE));
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_code_frm, WGL_SW_RECURSIVE));
        return  c_wgl_set_visibility (t_g_view.h_code_txt, WGL_SW_NORMAL);
    }
    else /* hidden */
    {
        /* set focus to setting list */
        RET_ON_ERR (c_wgl_set_focus (t_g_view.h_seti_lst, FALSE));
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_code_frm, WGL_SW_HIDE));
        return  c_wgl_set_visibility (t_g_view.h_code_txt, WGL_SW_HIDE);
    }
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_box_setup
 *
 * Description: This API sets text to the description text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_box_setup (UINT8    ui1_code_elem_num,
                               UINT8    aui1_code_style[],
                               UINT16   aw2s_code_sep_char[])
{
    INT32   i4_ret = WZDR_OK;

    if (ui1_code_elem_num == 0 || ui1_code_elem_num > CODE_BOX_ELEM_NUM)
    {
        return WZDR_INV_ARG;
    }

    RET_ON_ERR (wzd_view_code_txt_set_text (NULL));

    i4_ret = _wzd_view_create_code_box (ui1_code_elem_num,
                                        aui1_code_style,
                                        aw2s_code_sep_char);

    return i4_ret;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_box_set_focus_next_digit
 *
 * Description: This API sets the code input focus to the next digit
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_box_set_focus_next_digit (VOID)
{
    UINT8   ui1_code_idx;

    ui1_code_idx = t_g_view.ui1_code_hlt_idx + 1;

    while (ui1_code_idx < t_g_view.ui1_code_elem_num && 0 !=
           (t_g_view.aui1_code_style[ui1_code_idx] & CODE_BOX_STL_SEP_MASK))
    {
        ++ui1_code_idx;
    }
    if (ui1_code_idx >= t_g_view.ui1_code_elem_num)
    {
        return WZDR_FAIL;
    }

    RET_ON_ERR (_wzd_view_code_box_set_hlt_idx (ui1_code_idx, TRUE));
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_box_set_focus_next_digit
 *
 * Description: This API sets the code input focus to the previous digit
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_box_set_focus_prev_digit (VOID)
{
    UINT8   ui1_code_idx;

    ui1_code_idx = t_g_view.ui1_code_hlt_idx;

    while (ui1_code_idx > 0 && 0 !=
           (t_g_view.aui1_code_style[ui1_code_idx-1] & CODE_BOX_STL_SEP_MASK))
    {
        --ui1_code_idx;
    }
    if (ui1_code_idx == 0)
    {
        return WZDR_FAIL;
    }

    RET_ON_ERR (_wzd_view_code_box_set_hlt_idx (ui1_code_idx-1, TRUE));
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_box_set_code_num
 *
 * Description: This API sets the number of elements to the setting list.
 *
 * Inputs:  ui2_elem_num        The number of elements to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_box_set_code_num (UINT64    ui8_code_num, BOOL  b_repaint)
{
    UINT16  ui2_first = 0;
    UINT16  ui2_i;
    UTF16_T w2s_temp[2];

    w2s_temp[1] = 0;
    for (ui2_i = t_g_view.ui1_code_elem_num; ui2_i > 0; --ui2_i)
    {
        if ((t_g_view.aui1_code_style[ui2_i-1] & CODE_BOX_STL_SEP_MASK) == 0)
        {
            t_g_view.aui1_code_digit[ui2_i-1] = ui8_code_num & 0x0F;

            if (t_g_view.aui1_code_digit[ui2_i-1] <= 9)
            {
                w2s_temp[0] = L'0' + t_g_view.aui1_code_digit[ui2_i-1];
            }
            else
            {
                if (t_g_view.aui1_code_style[ui2_i-1] & CODE_BOX_STL_INDICATOR)
                {
                    w2s_temp[0] = t_g_view.w2_indicator;
                }
                else
                {
                    w2s_temp[0] = 0;
                }
            }
            RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_code_box[ui2_i-1],
                                      WGL_CMD_EB_SET_TEXT,
                                      WGL_PACK (w2s_temp),
                                      WGL_PACK (1)));
            ui8_code_num >>= 4;
            ui2_first = ui2_i - 1;
        }
    }

    RET_ON_ERR (_wzd_view_code_box_set_hlt_idx (ui2_first, b_repaint));
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_box_get_code_num
 *
 * Description: This API sets the number of elements to the setting list.
 *
 * Inputs:  ui2_elem_num        The number of elements to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_box_get_code_num (UINT64*   pui8_code_num)
{
    BOOL    b_valid = FALSE;
    UINT16  ui2_i;

    if (pui8_code_num == NULL)
    {
        return WZDR_INV_ARG;
    }


    for (ui2_i = 0; ui2_i < t_g_view.ui1_code_elem_num; ++ui2_i)
    {
        if ((t_g_view.aui1_code_style[ui2_i] & CODE_BOX_STL_SEP_MASK) == 0 &&
            t_g_view.aui1_code_digit[ui2_i] <= 9)
        {
            b_valid = TRUE;
        }
    }

    if (!b_valid)
    {
        *pui8_code_num = CODE_NUM_INVALID;
    }
    else
    {
        UINT64  ui8_code_num = 0;

        for (ui2_i = 0; ui2_i < t_g_view.ui1_code_elem_num; ++ui2_i)
        {
            if ((t_g_view.aui1_code_style[ui2_i] & CODE_BOX_STL_SEP_MASK) == 0)
            {
                ui8_code_num <<= 4;
                ui8_code_num |= t_g_view.aui1_code_digit[ui2_i] & 0x0F;
            }
        }

        *pui8_code_num = ui8_code_num;
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_txt_set_text
 *
 * Description: This API sets text to the code prompt text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_txt_set_text (UTF16_T*    pw2s_text)
{
    return  c_wgl_do_cmd (t_g_view.h_code_txt,
                          WGL_CMD_TEXT_SET_TEXT,
                          WGL_PACK (pw2s_text),
                          WGL_PACK (c_uc_w2s_strlen (pw2s_text)));
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_txt_clear_text
 *
 * Description: This API sets text to the code prompt text widget.
 *
 * Inputs:  pw2s_text           Text to be set.
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_txt_clear_text (BOOL    b_repaint)
{
    UTF16_T    w2s_text[128];

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_txt,
                          WGL_CMD_TEXT_GET_TEXT,
                          WGL_PACK (w2s_text),
                          WGL_PACK (128)));
    if (w2s_text[0] == 0)
    {
        return WZDR_OK;
    }
    else
    {
        RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_code_txt,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK (NULL),
                                  WGL_PACK (0)));
        if (b_repaint)
        {
                RET_ON_ERR (c_wgl_repaint (t_g_view.h_code_txt, NULL, TRUE));
        }
    }
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_txt_repaint
 *
 * Description: This API repaints the code prompt text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_txt_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_code_txt, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_code_box_repaint
 *
 * Description: This API repaints the code input form and prompt text.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_code_box_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_code_frm, NULL, TRUE);
}

#endif

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_focus_widget
 *
 * Description: This API gets current focused widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 wzd_view_get_layout_frm (HANDLE_T*  ph_layout_frm)
{
    if (!ph_layout_frm)
    {
        return WZDR_INV_ARG ;
    }

    *ph_layout_frm = t_g_view.h_layout_frm ;

    if (NULL_HANDLE == *ph_layout_frm)
    {
        return WZDR_FAIL ;
    }

    return WZDR_OK ;
}

#ifdef APP_2K12_RETAIL_DEMO_MODE
/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_main_frm
 *
 * Description: This API gets main frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 wzd_view_get_main_frm (HANDLE_T*  ph_layout_frm)
{
    if (!ph_layout_frm)
    {
        return WZDR_INV_ARG ;
    }

    *ph_layout_frm = t_g_view.h_main_frm ;

    if (NULL_HANDLE == *ph_layout_frm)
    {
        return WZDR_FAIL ;
    }

    return WZDR_OK ;
}

INT32 wzd_view_get_base_frm (HANDLE_T*  ph_base_frm)
{
    if (!ph_base_frm)
    {
        return WZDR_INV_ARG ;
    }

    *ph_base_frm = t_g_view.h_base_frm ;

    if (NULL_HANDLE == *ph_base_frm)
    {
        return WZDR_FAIL ;
    }

    return WZDR_OK ;
}
#endif

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_focus_widget
 *
 * Description: This API gets current focused widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 wzd_view_get_focus_widget (WZD_FOCUS_WIDGET_T*    pe_focus_widget)
{
    HANDLE_T    h_widget;

    RET_ON_ERR (c_wgl_get_focus (& h_widget));

    if (h_widget == t_g_view.h_seti_lst)
    {
        *pe_focus_widget = WZD_FOCUS_WIDGET_SETI_LST;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_set_focus_widget
 *
 * Description: This API sets focus to a given widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: -
 ----------------------------------------------------------------------------*/
INT32 wzd_view_set_focus_widget (WZD_FOCUS_WIDGET_T    e_focus_widget)
{
    HANDLE_T    h_widget;

    switch (e_focus_widget)
    {
        case WZD_FOCUS_WIDGET_SETI_LST:
            h_widget = t_g_view.h_seti_lst;
            break;

        default:
            return (-1);
    }

    return  c_wgl_set_focus (h_widget, FALSE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_osd_offset_x
 *
 * Description: This API returns OSD offset y.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: OSD offset x.
 ----------------------------------------------------------------------------*/
UINT32 wzd_view_get_osd_offset_x (VOID)
{
    return  t_g_view.ui4_osd_offset_x;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_osd_offset_y
 *
 * Description: This API returns OSD offset y.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: OSD offset y.
 ----------------------------------------------------------------------------*/
UINT32 wzd_view_get_osd_offset_y (VOID)
{
    return  t_g_view.ui4_osd_offset_y;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_osd_width
 *
 * Description: This API returns the width of OSD.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: The width of OSD.
 ----------------------------------------------------------------------------*/
UINT32 wzd_view_get_osd_width (VOID)
{
    return  t_g_view.ui4_osd_width;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_osd_height
 *
 * Description: This API returns the height of OSD.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: The height of OSD.
 ----------------------------------------------------------------------------*/
UINT32 wzd_view_get_osd_height (VOID)
{
    return  t_g_view.ui4_osd_height;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_font_name
 *
 * Description: This API gets the font name for the Wizard application.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: The string point of font name.
 ----------------------------------------------------------------------------*/
CHAR* wzd_view_get_font_name (VOID)
{
    return  t_g_view.s_font_name;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_plane
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
GL_HPLANE_T  wzd_view_get_plane (VOID)
{
   return t_g_view.h_plane;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_get_canvas
 *
 * Description: -
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
HANDLE_T  wzd_view_get_canvas (VOID)
{
   return t_g_view.h_canvas;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_init
 *
 * Description: This API initializes all the widgets and sets attributes, colors,
 *              images to the widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_init (VOID)
{
    /* reset variables of view */
    c_memset (& t_g_view, 0, sizeof(WZD_VIEW_T));

    /* set wizard's font */
    if(c_fe_has_font (WZD_FONT_NAME, FE_FNT_STYLE_UNIFORM))
    {
        c_strcpy (t_g_view.s_font_name, WZD_FONT_NAME);
    }
    else    /* use system default font */
    {
        c_strcpy (t_g_view.s_font_name, SN_FONT_DEFAULT);
    }

    /* initialize canvas */
    RET_ON_ERR (_wzd_view_canvas_init ());

    /* initialize colors */
    RET_ON_ERR (wzd_color_init ());

    /* initialize images */
    RET_ON_ERR (wzd_image_init ());

    /* create widgets */
    RET_ON_ERR (_wzd_view_create_main_frm ());        /* main frame */
    RET_ON_ERR (_wzd_view_create_base_frm ());        /* base map frame */
    RET_ON_ERR (_wzd_view_create_layout_frm ());      /* layout frame */
    RET_ON_ERR (_wzd_view_create_footer_frm());       /* footer frame */
    RET_ON_ERR (_wzd_view_create_footer_buttons());   /* footer buttons */
    RET_ON_ERR (_wzd_view_create_seti_lst ());        /* setting list */
    RET_ON_ERR (_wzd_view_create_title_txt());        /* Title text */
    RET_ON_ERR (_wzd_view_create_desc_txt ());        /* setting description text */
    RET_ON_ERR (_wzd_view_create_scan_bar ());        /* scan progress bar */
    RET_ON_ERR (_wzd_view_create_scan_txt());         /* Scan status text */
    RET_ON_ERR (_wzd_view_create_seti_icon());        /* icon widget */
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
    RET_ON_ERR (_wzd_view_create_code_frm_and_txt()); /* code input form & prompt */
#endif
    RET_ON_ERR (_wzd_view_create_demo_icon());        /* Demo picture */

    RET_ON_ERR (_wzd_view_create_demo_txt());         /* when scanning, show message at right panel*/
    RET_ON_ERR (_wzd_view_create_right_panel_icon());

	/* select box widget create */
	RET_ON_ERR (_wzd_view_create_sel_box_frm());
	RET_ON_ERR (_wzd_view_create_sel_box_buttons());

	/* full screen dialog create */
	RET_ON_ERR (_wzd_view_full_screen_dlg_create());

    RET_ON_ERR (wzd_image_cust_init());            	  /* wizard custom image init*/

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_destroy
 *
 * Description: This API destroies all the widgets.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_destroy (VOID)
{
    /* icon widget */
    if (t_g_view.h_seti_icon != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_seti_icon));
        t_g_view.h_seti_icon = NULL_HANDLE;
    }

    /* title text */
    if (t_g_view.h_title_txt != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_title_txt));
        t_g_view.h_title_txt = NULL_HANDLE;
    }

    /* scan progress bar */
    if (t_g_view.h_scan_bar != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_scan_bar));
        t_g_view.h_scan_bar = NULL_HANDLE;
    }

    /* setting description text */
    if (t_g_view.h_desc_txt != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_desc_txt));
        t_g_view.h_desc_txt = NULL_HANDLE;
    }

    /* setting list box */
    if (t_g_view.h_seti_lst != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_seti_lst));
        t_g_view.h_seti_lst = NULL_HANDLE;
    }

#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
    RET_ON_ERR (_wzd_view_clear_code_box()); /* code input form & prompt */

    /* code input prompt text */
    if (t_g_view.h_code_txt != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_code_txt));
        t_g_view.h_code_txt = NULL_HANDLE;
    }

    /* code frame */
    if (t_g_view.h_code_frm != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_code_frm));
        t_g_view.h_code_frm = NULL_HANDLE;
    }
#endif

    /* layout frame */
    if (t_g_view.h_layout_frm != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_layout_frm));
        t_g_view.h_layout_frm = NULL_HANDLE;
    }

    /* base map frame */
    if (t_g_view.h_base_frm != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_base_frm));
        t_g_view.h_base_frm = NULL_HANDLE;
    }

    /* main frame */
    if (t_g_view.h_main_frm != NULL_HANDLE)
    {
        RET_ON_ERR (c_wgl_destroy_widget (t_g_view.h_main_frm));
        t_g_view.h_main_frm = NULL_HANDLE;
    }

    return  0;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_create_btn_widget
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_btn_widget(
    HANDLE_T                    h_parent,
    UTF16_T*                    ws_text,
    const GL_RECT_T*            pt_rect,
    const WGL_COLOR_INFO_T*     pt_color_info_fg,
    const WGL_FONT_INFO_T*      pt_font,
    WGL_HIMG_TPL_T              t_img_tpl_ht,
    WGL_HIMG_TPL_T              t_img_tpl_un_ht,
    UINT8                       ui1_align,
    wgl_widget_proc_fct         pf_wdgt_proc,
    HANDLE_T*                   ph_btn)
{
    WGL_IMG_INFO_T              t_img_info;
    WGL_INSET_T                 t_inset = {0};

    RET_ON_ERR (c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 pt_rect,
                                 pf_wdgt_proc,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_btn));
    /*foreground color*/
    RET_ON_ERR (c_wgl_do_cmd(*ph_btn, WGL_CMD_GL_SET_COLOR, WGL_PACK(WGL_CLR_TEXT), WGL_PACK(pt_color_info_fg)));

    RET_ON_ERR (c_wgl_do_cmd(
                        *ph_btn,
                        WGL_CMD_BTN_SET_ALIGN,
                        WGL_PACK(ui1_align),
                        NULL));

    c_memset(&t_inset, 0, sizeof(t_inset));

    /*content inset*/
    RET_ON_ERR (c_wgl_do_cmd(*ph_btn,
                           WGL_CMD_BTN_SET_CNT_INSET,
                           WGL_PACK(&t_inset),
                           NULL));


    /*font*/
    RET_ON_ERR (c_wgl_do_cmd(*ph_btn, WGL_CMD_GL_SET_FONT, (VOID*)pt_font, NULL));

    /*text*/
    if(ws_text)
    {
        RET_ON_ERR (c_wgl_do_cmd(*ph_btn, WGL_CMD_BTN_SET_TEXT, WGL_PACK(ws_text), WGL_PACK(c_uc_w2s_strlen(ws_text))));
    }

    /* background image */
    /*set image*/
    t_img_info.e_type                                   = WGL_IMG_SET_EXTEND;
    t_img_info.u_img_data.t_extend.t_disable            = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_enable             = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_highlight          = t_img_tpl_ht;
    t_img_info.u_img_data.t_extend.t_highlight_inactive = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_push               = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_extend.t_push_unhighlight   = t_img_tpl_un_ht;

    RET_ON_ERR (c_wgl_do_cmd(*ph_btn, WGL_CMD_GL_SET_IMAGE, WGL_PACK(WGL_IMG_BK), WGL_PACK(&t_img_info)));

    return WZDR_OK;

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
static INT32 _wzd_dlg_set_attach_data(
                    HANDLE_T            h_dlg_handle,
                    WZD_DLG_CONTROL_T*  pt_dlg_ctrl)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_dlg_handle,
                          WGL_CMD_GL_SET_ATTACH_DATA,
                          WGL_PACK(pt_dlg_ctrl),
                          NULL);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;

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
static INT32 _wzd_dlg_get_attach_data(
                    HANDLE_T            h_dlg_handle,
                    WZD_DLG_CONTROL_T** ppt_dlg_ctrl)
{
    INT32 i4_ret;
    i4_ret = c_wgl_do_cmd(h_dlg_handle,
                          WGL_CMD_GL_GET_ATTACH_DATA,
                          WGL_PACK(ppt_dlg_ctrl),
                          NULL);
    RET_ON_ERR(i4_ret);

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_dlg_txt
 *
 * Description: This function creates a description text to display setting
 *              details.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_dlg_txt (
		HANDLE_T					h_parent,
		HANDLE_T* 					ph_handle,
		const GL_RECT_T*			pt_rect,
		const WGL_COLOR_INFO_T* 	pt_color_info,
		const WGL_FONT_INFO_T*		pt_fnt_info,
		const UINT8                 ui1_align)
{
    WGL_INSET_T                 t_inset;
    WGL_COLOR_INFO_T            t_color_info;

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_512  |
                                             WGL_STL_TEXT_MAX_DIS_10_LINE |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     ph_handle));

    /* set font size */
    RET_ON_ERR (c_wgl_do_cmd (*ph_handle,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (pt_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = WZD_DLG_TXT_INSET_L;
    t_inset.i4_right  = WZD_DLG_TXT_INSET_R;
    t_inset.i4_top    = WZD_DLG_TXT_INSET_T;
    t_inset.i4_bottom = WZD_DLG_TXT_INSET_B;

    RET_ON_ERR (c_wgl_do_cmd (*ph_handle,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (*ph_handle,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (ui1_align),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (*ph_handle,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) WZD_DLG_TXT_LINE_GAPS),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt_bk);

    RET_ON_ERR (c_wgl_do_cmd (*ph_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (& t_color_info)));

    RET_ON_ERR (c_wgl_do_cmd (*ph_handle,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (pt_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (*ph_handle, WGL_SW_NORMAL));

    return  0;
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
static VOID _wzd_dlg_hide_timer_nfy_fct(
                    HANDLE_T                    h_timer,
                    VOID*                       pv_tag
                    )
{
    WZD_DLG_CONTROL_T*     pt_dlg_ctrl = (WZD_DLG_CONTROL_T*) pv_tag;

    if (pt_dlg_ctrl == NULL)
    {
        return;
    }

    if (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_AUTO_HIDE)
    {
        if ( pt_dlg_ctrl->pf_fct != NULL)
        {
            pt_dlg_ctrl->pf_fct(pt_dlg_ctrl->pv_tag,
                  WZD_DLG_MSG_HIDE_TIMEOUT,
                  NULL,
                  NULL);
        }
    }
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
static INT32 _wzd_dlg_start_timer (
                    WZD_DLG_CONTROL_T*     pt_dlg_ctrl
                    )
{
    INT32    i4_ret = WZDR_OK;

    if ( (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_AUTO_HIDE)&&
         (NULL_HANDLE != pt_dlg_ctrl->h_hide_timer) )
    {
        i4_ret = c_timer_start (pt_dlg_ctrl->h_hide_timer,
                                pt_dlg_ctrl->ui4_hide_timer,
                                X_TIMER_FLAG_ONCE,
                                _wzd_dlg_hide_timer_nfy_fct,
                                pt_dlg_ctrl);
        if (i4_ret < WZDR_OK)
        {
            return WZDR_FAIL;
        }
    }
    return WZDR_OK;
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
static INT32 _wzd_dlg_stop_timer (
                    WZD_DLG_CONTROL_T*     pt_dlg_ctrl
                    )
{
    INT32    i4_ret = WZDR_OK;

    if ( (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_AUTO_HIDE) &&
         (NULL_HANDLE != pt_dlg_ctrl->h_hide_timer))
    {
        i4_ret = c_timer_stop (pt_dlg_ctrl->h_hide_timer);

         if (i4_ret < OSR_OK)
         {
            return WZDR_FAIL;
         }

    }

    if (i4_ret < OSR_OK)
    {
        return WZDR_FAIL;
    }

    return WZDR_OK;
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
static INT32 _wzd_dlg_create_timer (
                    WZD_DLG_CONTROL_T*     pt_dlg_ctrl
                    )
{
    INT32    i4_ret = WZDR_OK;

    if (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_AUTO_HIDE)
    {
         i4_ret = c_timer_create (& pt_dlg_ctrl->h_hide_timer);

         if (i4_ret < OSR_OK)
         {
            return WZDR_FAIL;
         }
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_dlg_update_btn_navigation
 *
 * Description: The function update the focus transition.
 *
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 _wzd_dlg_update_btn_navigation (WZD_DLG_CONTROL_T*  pt_dlg_ctrl)
{
    WGL_KEY_LINK_T  at_key_lnk[1];
    INT32           i4_ret = WZDR_OK;

    if( pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_2_BTN )
    {
        at_key_lnk[0].ui4_key  = BTN_CURSOR_RIGHT;
        at_key_lnk[0].h_widget = pt_dlg_ctrl->h_btn_02;
        i4_ret = c_wgl_set_navigation(pt_dlg_ctrl->h_btn_01, 1, at_key_lnk);
        if( WZDR_OK != i4_ret )
        {
            DBG_LOG_PRINT(( "[WZD][DLG] WGL_CMD_GL_SET_IMAGE fail, i4_ret =%d\n", i4_ret ));
            return i4_ret;
        }

        at_key_lnk[0].ui4_key  = BTN_CURSOR_LEFT;
        at_key_lnk[0].h_widget = pt_dlg_ctrl->h_btn_01;
        i4_ret = c_wgl_set_navigation(pt_dlg_ctrl->h_btn_02, 1, at_key_lnk);
        if( WZDR_OK != i4_ret )
        {
            DBG_LOG_PRINT(( "[WZD][DLG] WGL_CMD_GL_SET_IMAGE fail, i4_ret =%d\n", i4_ret ));
            return i4_ret;
        }
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_dlg_frm_nfy
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_dlg_frm_nfy (HANDLE_T    h_widget,
                                UINT32      ui4_msg,
                                VOID*       pv_param1,
                                VOID*       pv_param2)
{
    HANDLE_T              h_cb_widget;
    WGL_NOTIFY_DATA_T*    pt_wgl_nfy_data;
    WZD_DLG_CONTROL_T*    pt_dlg_ctrl = NULL;
    INT32                 i4_ret = WZDR_OK;

    h_cb_widget     = (HANDLE_T) pv_param1;
    pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if (ui4_msg == WGL_MSG_NOTIFY)
    {
        if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_GL_GET_FOCUS) /* some widget gets focus */
        {
            /* Get dlg control */
            i4_ret = _wzd_dlg_get_attach_data(h_widget,
                                          &pt_dlg_ctrl);
            if( WZDR_OK != i4_ret )
            {
                DBG_LOG_PRINT(( "[WZD][DLG][_wzd_dlg_frm_nfy] _wzd_dlg_get_attach_data() fail, i4_ret =%d\n", i4_ret ));
                return i4_ret;
            }

            if( NULL == pt_dlg_ctrl )
            {
                DBG_LOG_PRINT(( "[WZD][DLG][_wzd_dlg_frm_nfy] pt_dlg_ctrl = NULL\n" ));
                return i4_ret;
            }

            if( h_cb_widget == pt_dlg_ctrl->h_btn_01 )
            {
                pt_dlg_ctrl->pf_fct( pt_dlg_ctrl->pv_tag, WZD_DLG_MSG_BTN_FOCUSED, (VOID*)(UINT32)WZD_DLG_BTN_TYPE_01, NULL );
                _wzd_dlg_start_timer(pt_dlg_ctrl);
            }
            else if( h_cb_widget == pt_dlg_ctrl->h_btn_02 )
            {
                pt_dlg_ctrl->pf_fct( pt_dlg_ctrl->pv_tag, WZD_DLG_MSG_BTN_FOCUSED, (VOID*)(UINT32)WZD_DLG_BTN_TYPE_02, NULL );
                _wzd_dlg_start_timer(pt_dlg_ctrl);
            }
        }
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_dlg_btn_nfy
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_dlg_btn_nfy(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    WZD_DLG_CONTROL_T*    pt_dlg_ctrl = NULL;
    HANDLE_T              h_frame = NULL_HANDLE;
    INT32                 i4_ret = WZDR_OK;

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        i4_ret = c_wgl_get_parent(h_widget, &h_frame);
        if( WZDR_OK != i4_ret )
        {
            DBG_ERROR(( "[WZD][_wzd_dlg_btn_nfy] c_wgl_get_parent() fail, i4_ret =%d\n", i4_ret ));
            return i4_ret;
        }

        /* Get dlg control */
        i4_ret = _wzd_dlg_get_attach_data(h_frame,
                                      &pt_dlg_ctrl);
        if( WZDR_OK != i4_ret )
        {
            DBG_ERROR(( "[WZD][_wzd_dlg_btn_nfy] _wzd_dlg_get_attach_data() fail, i4_ret =%d\n", i4_ret ));
            return i4_ret;
        }

        if( NULL == pt_dlg_ctrl )
        {
            DBG_ERROR(( "[WZD][_wzd_dlg_btn_nfy] pt_dlg_ctrl = NULL\n" ));
            return i4_ret;
        }

        if( h_widget == pt_dlg_ctrl->h_btn_01 )
        {
            pt_dlg_ctrl->pf_fct( pt_dlg_ctrl->pv_tag, WZD_DLG_MSG_KEY_INPUT, pv_param1, (VOID*)(UINT32)WZD_DLG_BTN_TYPE_01 );
        }
        else if( h_widget == pt_dlg_ctrl->h_btn_02 )
        {
            pt_dlg_ctrl->pf_fct( pt_dlg_ctrl->pv_tag, WZD_DLG_MSG_KEY_INPUT, pv_param1, (VOID*)(UINT32)WZD_DLG_BTN_TYPE_02 );
        }

        _wzd_dlg_start_timer(pt_dlg_ctrl);
        break;

    default:
        break;
    }

	if( BTN_SELECT == (UINT32)pv_param1 )
    {
        return WZDR_OK;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
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
INT32 wzd_dlg_destroy(
                    HANDLE_T            h_dlg_handle)

{
    INT32               i4_ret = WZDR_OK;
    WZD_DLG_CONTROL_T*  pt_dlg_ctrl = NULL;

    /* Get dlg control */
    i4_ret = _wzd_dlg_get_attach_data(h_dlg_handle,
                                   &pt_dlg_ctrl);

    if(i4_ret != WZDR_OK)
    {
        RET_ON_ERR( i4_ret );
    }

    /* Release childs*/
    if( pt_dlg_ctrl->h_frame )
    {
        c_wgl_destroy_widget_ex(pt_dlg_ctrl->h_frame, FALSE);
    }

    if( pt_dlg_ctrl->h_text )
    {
        c_wgl_destroy_widget_ex(pt_dlg_ctrl->h_text, FALSE);
    }

	if( pt_dlg_ctrl->h_desc_text )
    {
        c_wgl_destroy_widget_ex(pt_dlg_ctrl->h_desc_text, FALSE);
    }

    if( pt_dlg_ctrl->h_btn_01 )
    {
        c_wgl_destroy_widget_ex(pt_dlg_ctrl->h_btn_01, FALSE);
    }

    if( pt_dlg_ctrl->h_btn_02 )
    {
        c_wgl_destroy_widget_ex(pt_dlg_ctrl->h_btn_02, FALSE);
    }

    /* delete the timer*/
    if( pt_dlg_ctrl->h_hide_timer )
    {
        c_timer_delete(pt_dlg_ctrl->h_hide_timer);
    }

    /* Free the dlg control */
    c_mem_free(pt_dlg_ctrl);

    return WZDR_OK;
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
INT32 wzd_dlg_create(
                    WZD_DLG_INIT_T*     pt_dlg_init,        /* In  */
                    HANDLE_T*           ph_dlg_handle)      /* Out */
{
    INT32               i4_ret = WZDR_OK;
    WZD_DLG_CONTROL_T*  pt_dlg_ctrl = NULL;
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_IMG_INFO_T      t_img_info;

    /* Allocate memory for dlg control */
    pt_dlg_ctrl = (WZD_DLG_CONTROL_T *) c_mem_alloc(sizeof(WZD_DLG_CONTROL_T));

    if(pt_dlg_ctrl == NULL)
    {
        DBG_ERROR(( "[WZD][DLG] Out of memory when create dlg control\n" ));
        return WZDR_OUT_OF_MEM;
    }

    c_memset(pt_dlg_ctrl, 0 , sizeof(WZD_DLG_CONTROL_T));

    /* Image initial*/

    /* Set the style mask */
    pt_dlg_ctrl->ui4_style_mask = pt_dlg_init->ui4_style_mask;

	/* Create frame */
	SET_RECT_BY_SIZE (& t_rect,
				  WZD_DLG_FRM_X,
				  WZD_DLG_FRM_Y,
				  WZD_DLG_FRM_W,
				  WZD_DLG_FRM_H);

    do
    {
        i4_ret = c_wgl_create_widget (pt_dlg_init->h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _wzd_dlg_frm_nfy,
                                     240,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     & pt_dlg_ctrl->h_frame);

        if( WZDR_OK != i4_ret )
        {
            DBG_ERROR(( "[WZD][DLG] Create frame fail, i4_ret =%d\n", i4_ret ));
            break;
        }

		t_img_info.e_type = WGL_IMG_SET_STANDARD;
		t_img_info.u_img_data.t_standard.t_enable	 = h_g_wzd_img_dialog;
		t_img_info.u_img_data.t_standard.t_disable	 = h_g_wzd_img_dialog;
		t_img_info.u_img_data.t_standard.t_highlight = h_g_wzd_img_dialog;

        i4_ret = c_wgl_do_cmd (pt_dlg_ctrl->h_frame,
                                  WGL_CMD_GL_SET_IMAGE,
                                  WGL_PACK (WGL_IMG_BK), /* background image */
                                  WGL_PACK (& t_img_info));

        if( WZDR_OK != i4_ret )
        {
            DBG_ERROR(( "[WZD][DLG] WGL_CMD_GL_SET_IMAGE fail, i4_ret =%d\n", i4_ret ));
            break;
        }

        /* Create text */
		if (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_WITH_DESC)
		{
			SET_RECT_BY_SIZE (& t_rect,
	              WZD_DLG_TXT_X,
	              WZD_DLG_DESC_TXT_Y - (40 * WZD_UI_RATIO_W),
	              WZD_DLG_TXT_W,
	              (30 * WZD_UI_RATIO_W));
		}
		else if (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_WITH_DESC_MUTI_LINE)
		{
			SET_RECT_BY_SIZE (& t_rect,
	              WZD_DLG_TXT_X,
	              WZD_DLG_DESC_TXT_Y - ((40+ WZD_DLG_DESC_TXT_MUTI_LINE_V_OFFS) * WZD_UI_RATIO_W),
	              WZD_DLG_TXT_W,
	              ((30+ WZD_DLG_DESC_TXT_MUTI_LINE_V_OFFS) * WZD_UI_RATIO_W));
		}
		else
		{
		    SET_RECT_BY_SIZE (& t_rect,
	              WZD_DLG_TXT_X,
	              WZD_DLG_TXT_Y,
	              WZD_DLG_TXT_W,
	              WZD_DLG_TXT_H);
		}

        if (pt_dlg_init->t_fnt_info.e_font_size != 0)
        {
            /* set default font */
            c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    	    c_strcpy (t_fnt_info.a_c_font_name, pt_dlg_init->t_fnt_info.a_c_font_name);
            t_fnt_info.e_font_size  =  pt_dlg_init->t_fnt_info.e_font_size;
            t_fnt_info.e_font_cmap  =  pt_dlg_init->t_fnt_info.e_font_cmap;
            t_fnt_info.e_font_style =  pt_dlg_init->t_fnt_info.e_font_style;
        	t_fnt_info.ui1_custom_size	=  pt_dlg_init->t_fnt_info.ui1_custom_size;       
        }
        else
        {
    		/* set font size */
    	    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    	    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);
    	    t_fnt_info.e_font_size  = WZD_DLG_TXT_FNT_SIZE;
    	    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    	    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;
	    }

		/* set text color */
	    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
	    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_dlg_txt);
	    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_dlg_txt);
	    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_dlg_txt);

        i4_ret = _wzd_view_create_dlg_txt(
                pt_dlg_ctrl->h_frame,
                &pt_dlg_ctrl->h_text,
                &t_rect,
                &t_color_info,
                &t_fnt_info,
                WGL_AS_CENTER_CENTER
                );
        if( WZDR_OK != i4_ret )
        {
            DBG_ERROR(( "[WZD][DLG] _wzd_view_create_dlg_txt() fail, i4_ret =%d\n", i4_ret ));
            break;
        }

        c_wgl_set_visibility (pt_dlg_ctrl->h_text, WGL_SW_NORMAL);

		/* Create desc text */
		if(pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_WITH_DESC)
		{
		    SET_RECT_BY_SIZE (&t_rect,
							  WZD_DLG_DESC_TXT_X,
							  WZD_DLG_DESC_TXT_Y,
							  WZD_DLG_DESC_TXT_W,
							  WZD_DLG_DESC_TXT_H);

			/* set font size */
		    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
		    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);
		    t_fnt_info.e_font_size  = WZD_DLG_TXT_DESC_FNT_SIZE;
		    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
		    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

			/* set text color */
			t_color_info.e_type = WGL_COLOR_SET_STANDARD;
		    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_dlg_desc_txt);
		    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_dlg_desc_txt);
		    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_dlg_desc_txt);

	        i4_ret = _wzd_view_create_dlg_txt(
                pt_dlg_ctrl->h_frame,
                &pt_dlg_ctrl->h_desc_text,
                &t_rect,
                &t_color_info,
                &t_fnt_info,
                WGL_AS_CENTER_TOP
                );
	        if( WZDR_OK != i4_ret )
	        {
	            DBG_ERROR(( "[WZD][DLG] _wzd_view_create_dlg_txt() fail, i4_ret =%d\n", i4_ret ));
	            break;
	        }

	        c_wgl_set_visibility (pt_dlg_ctrl->h_desc_text, WGL_SW_NORMAL);
		}
		if (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_WITH_DESC_MUTI_LINE)
		{
			SET_RECT_BY_SIZE (&t_rect,
							  WZD_DLG_DESC_TXT_X,
							  WZD_DLG_DESC_TXT_Y + WZD_DLG_DESC_TXT_MUTI_LINE_V_OFFS,
							  WZD_DLG_DESC_TXT_W,
							  WZD_DLG_DESC_TXT_H - WZD_DLG_DESC_TXT_MUTI_LINE_V_OFFS);

			/* set font size */
		    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
		    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);
		    t_fnt_info.e_font_size  = WZD_DLG_TXT_DESC_FNT_SIZE;
		    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
		    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

			/* set text color */
			t_color_info.e_type = WGL_COLOR_SET_STANDARD;
		    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_dlg_desc_txt);
		    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_dlg_desc_txt);
		    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_dlg_desc_txt);

	        i4_ret = _wzd_view_create_dlg_txt(
									                pt_dlg_ctrl->h_frame,
									                &pt_dlg_ctrl->h_desc_text,
									                &t_rect,
									                &t_color_info,
									                &t_fnt_info,
									                WGL_AS_CENTER_TOP
									                );
	        if( WZDR_OK != i4_ret )
	        {
	            DBG_ERROR(( "[WZD][DLG] _wzd_view_create_dlg_txt() fail, i4_ret =%d\n", i4_ret ));
	            break;
	        }

	        c_wgl_set_visibility (pt_dlg_ctrl->h_desc_text, WGL_SW_NORMAL);
		}
        if (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_2_BTN)
        {
    		SET_RECT_BY_SIZE (& t_rect,
    					  WZD_DLG_BTN01_X,
    					  WZD_DLG_BTN01_Y,
    					  WZD_DLG_BTN01_W,
    					  WZD_DLG_BTN01_H);
        }
        /* only one button should palce the center */
        else
        {
    		SET_RECT_BY_SIZE (& t_rect,
    					  (WZD_DLG_FRM_W - WZD_DLG_BTN01_W)/2 ,
    					  WZD_DLG_BTN01_Y,
    					  WZD_DLG_BTN01_W,
    					  WZD_DLG_BTN01_H);
        }

        /* Create buttons */
        t_color_info.e_type = WGL_COLOR_SET_STANDARD;
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt);
        COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt);

        /* set font size */
        c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
        c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

        t_fnt_info.e_font_size  = WZD_DLG_BTN_FNT_SIZE;
        t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
        t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

        i4_ret = _wzd_view_create_btn_widget(
                pt_dlg_ctrl->h_frame,
                L"",
                &t_rect,
                &t_color_info,
                &t_fnt_info,
                h_g_wzd_img_button_highlight,
                h_g_wzd_img_button,
                WGL_AS_CENTER_CENTER,
                _wzd_dlg_btn_nfy,
                &pt_dlg_ctrl->h_btn_01
                );

        if( WZDR_OK != i4_ret )
        {
            DBG_ERROR(( "[WZD][DLG] create button 01 fail, i4_ret =%d\n", i4_ret ));
            break;
        }

        c_wgl_set_visibility (pt_dlg_ctrl->h_btn_01, WGL_SW_NORMAL);
        if (pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_2_BTN)
        {
    		SET_RECT_BY_SIZE (& t_rect,
    					  WZD_DLG_BTN02_X,
    					  WZD_DLG_BTN02_Y,
    					  WZD_DLG_BTN02_W,
    					  WZD_DLG_BTN02_H);

            i4_ret = _wzd_view_create_btn_widget(
                    pt_dlg_ctrl->h_frame,
                    L"",
                    &t_rect,
                    &t_color_info,
                    &t_fnt_info,
                    h_g_wzd_img_button_highlight,
                    h_g_wzd_img_button,
                    WGL_AS_CENTER_CENTER,
                    _wzd_dlg_btn_nfy,
                    &pt_dlg_ctrl->h_btn_02
                    );

            if( WZDR_OK != i4_ret )
            {
                DBG_ERROR(( "[WZD][DLG] create button 02 fail, i4_ret =%d\n", i4_ret ));
                break;
            }

            c_wgl_set_visibility (pt_dlg_ctrl->h_btn_02, WGL_SW_NORMAL);
        }

        i4_ret = _wzd_dlg_update_btn_navigation( pt_dlg_ctrl );
        if( WZDR_OK != i4_ret )
        {
            DBG_ERROR(( "[WZD][DLG] _wzd_dlg_update_btn_navigation fail, i4_ret =%d\n", i4_ret ));
            break;
        }

        /* Create timer */
        if( pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_AUTO_HIDE )
        {
            i4_ret = _wzd_dlg_create_timer( pt_dlg_ctrl );

            if( WZDR_OK != i4_ret )
            {
                DBG_ERROR(( "[WZD][DLG] create timer fail, i4_ret =%d\n", i4_ret ));
                break;
            }
        }

        /* Save initial data */
        pt_dlg_ctrl->h_parent = pt_dlg_init->h_parent;
        pt_dlg_ctrl->pf_fct = pt_dlg_init->pf_fct;
        pt_dlg_ctrl->pv_tag = pt_dlg_init->pv_tag;
        pt_dlg_ctrl->ui4_hide_timer = pt_dlg_init->ui4_hide_timer;
        pt_dlg_ctrl->e_default_focus_btn = pt_dlg_init->e_default_focus_btn;

        /* Hide the frame at initial time */
        c_wgl_set_visibility(pt_dlg_ctrl->h_frame, WGL_SW_HIDE);

        /* Return the option list handle */
        *ph_dlg_handle = pt_dlg_ctrl->h_frame;

        /* Set attach date */
        i4_ret = _wzd_dlg_set_attach_data( pt_dlg_ctrl->h_frame, pt_dlg_ctrl );
        if( WZDR_OK != i4_ret )
        {
            DBG_ERROR(( "[WZD][DLG] _wzd_dlg_set_attach_data(), i4_ret =%d\n", i4_ret ));
            break;
        }

        i4_ret = WZDR_OK;
    } while(0);

    if(i4_ret != WZDR_OK)
    {
        SHOW_ON_ERR( i4_ret );
        i4_ret = wzd_dlg_destroy(pt_dlg_ctrl->h_frame);
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
INT32 wzd_dlg_show (HANDLE_T            h_dlg_handle,
					BOOL            	b_repaint)
{
    WZD_DLG_CONTROL_T*  pt_dlg_ctrl = NULL;
    INT32               i4_ret = WZDR_OK;

    /* Get dlg control */
    i4_ret = _wzd_dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_ctrl);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] _wzd_dlg_get_attach_data() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    if( NULL == pt_dlg_ctrl )
    {
        DBG_ERROR(( "[WZD][DLG][Show] pt_dlg_ctrl = NULL\n" ));
        return i4_ret;
    }

    /* Set the visibility of frame */
    c_wgl_set_visibility(h_dlg_handle, WGL_SW_NORMAL);

    /* Set focus on one of the button */
    if( WZD_DLG_BTN_TYPE_02 == pt_dlg_ctrl->e_default_focus_btn )
    {
        if( pt_dlg_ctrl->h_btn_02 )
        {
            i4_ret = c_wgl_set_focus(pt_dlg_ctrl->h_btn_02, FALSE);
            if( WZDR_OK != i4_ret )
            {
                DBG_ERROR(( "[WZD][DLG][Show] c_wgl_set_focus(h_btn_02) fail, i4_ret =%d\n", i4_ret ));
                return i4_ret;
            }
        }
        pt_dlg_ctrl->e_focused_btn = WZD_DLG_BTN_TYPE_02;
    }
    else
    {
        if( pt_dlg_ctrl->h_btn_01 )
        {
            i4_ret = c_wgl_set_focus(pt_dlg_ctrl->h_btn_01, FALSE);
            if( WZDR_OK != i4_ret )
            {
                DBG_ERROR(( "[WZD][DLG][Show] c_wgl_set_focus(h_btn_01) fail, i4_ret =%d\n", i4_ret ));
                return i4_ret;
            }
        }
        pt_dlg_ctrl->e_focused_btn = WZD_DLG_BTN_TYPE_01;
    }

    /* Set to topmost */
    i4_ret = c_wgl_insert (h_dlg_handle,
                           NULL_HANDLE,
                           WGL_INSERT_TOPMOST,
                           WGL_NO_AUTO_REPAINT);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] c_wgl_insert() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    /* Repaint the frame */
    i4_ret = c_wgl_set_visibility(h_dlg_handle, WGL_SW_RECURSIVE);
    i4_ret = c_wgl_set_visibility(pt_dlg_ctrl->h_btn_01, WGL_SW_NORMAL);
    i4_ret = c_wgl_set_visibility(pt_dlg_ctrl->h_btn_02, WGL_SW_NORMAL);
    i4_ret = c_wgl_set_visibility(pt_dlg_ctrl->h_text, WGL_SW_NORMAL);
	if(pt_dlg_ctrl->ui4_style_mask & WZD_DLG_STYLE_MASK_WITH_DESC)
	{
		i4_ret = c_wgl_set_visibility(pt_dlg_ctrl->h_desc_text, WGL_SW_NORMAL);
	}

	if (b_repaint)
	{
		i4_ret = wzd_view_main_frm_repaint();
	    if( WZDR_OK != i4_ret )
	    {
	        DBG_ERROR(( "[WZD][DLG][Show] c_wgl_show() fail, i4_ret =%d\n", i4_ret ));
	        return i4_ret;
	    }
	}

    /* Start the timer if necessary */
    i4_ret = _wzd_dlg_start_timer(pt_dlg_ctrl);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] _wzd_dlg_start_timer() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    pt_dlg_ctrl->b_is_show = TRUE;

    return WZDR_OK;
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
INT32 wzd_dlg_hide(
                    HANDLE_T            h_dlg_handle)
{
    WZD_DLG_CONTROL_T*  pt_dlg_ctrl = NULL;
    INT32               i4_ret = WZDR_OK;

    /* Get dlg control */
    i4_ret = _wzd_dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_ctrl);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] _wzd_dlg_get_attach_data() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    if( NULL == pt_dlg_ctrl )
    {
        DBG_ERROR(( "[WZD][DLG][Show] pt_dlg_ctrl = NULL\n" ));
        return i4_ret;
    }

    /* Stop the timer */
    i4_ret = _wzd_dlg_stop_timer(pt_dlg_ctrl);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] _wzd_dlg_stop_timer() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    /* Reset focus */
    pt_dlg_ctrl->e_focused_btn = pt_dlg_ctrl->e_default_focus_btn;

    /* Hide frame */
    i4_ret = c_wgl_set_visibility(h_dlg_handle, WGL_SW_HIDE_RECURSIVE);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] c_wgl_set_visibility() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    /* Repaint */
    i4_ret = c_wgl_repaint(h_dlg_handle, NULL, TRUE);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] c_wgl_repaint() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    /* Notify hidden */
    pt_dlg_ctrl->pf_fct(pt_dlg_ctrl->pv_tag,
              WZD_DLG_MSG_DLG_HIDED,
              NULL,
              NULL);

    pt_dlg_ctrl->b_is_show = FALSE;

    return WZDR_OK;
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
INT32 wzd_dlg_set_text(
                    HANDLE_T            h_dlg_handle,
                    UTF16_T*            pw2s_text,
                    BOOL                b_repaint)
{
    WZD_DLG_CONTROL_T*  pt_dlg_ctrl = NULL;
    INT32               i4_ret = WZDR_OK;

    /* Get dlg control */
    i4_ret = _wzd_dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_ctrl);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] _wzd_dlg_get_attach_data() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    if( NULL == pt_dlg_ctrl )
    {
        DBG_ERROR(( "[WZD][DLG][Show] pt_dlg_ctrl = NULL\n" ));
        return i4_ret;
    }

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_ctrl->h_text,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK (pw2s_text),
                                  WGL_PACK (c_uc_w2s_strlen (pw2s_text))));
    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (pt_dlg_ctrl->h_text, NULL, TRUE));
    }

    return WZDR_OK;
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
INT32 wzd_dlg_set_desc_text(
                    HANDLE_T            h_dlg_handle,
                    UTF16_T*            pw2s_text,
                    BOOL                b_repaint)
{
    WZD_DLG_CONTROL_T*  pt_dlg_ctrl = NULL;
    INT32               i4_ret = WZDR_OK;

    /* Get dlg control */
    i4_ret = _wzd_dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_ctrl);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] _wzd_dlg_get_attach_data() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    if( NULL == pt_dlg_ctrl )
    {
        DBG_ERROR(( "[WZD][DLG][Show] pt_dlg_ctrl = NULL\n" ));
        return i4_ret;
    }

	if (NULL_HANDLE == pt_dlg_ctrl->h_desc_text)
	{
		return i4_ret;
	}

    RET_ON_ERR (c_wgl_do_cmd (pt_dlg_ctrl->h_desc_text,
                                  WGL_CMD_TEXT_SET_TEXT,
                                  WGL_PACK (pw2s_text),
                                  WGL_PACK (c_uc_w2s_strlen (pw2s_text))));
    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (pt_dlg_ctrl->h_desc_text, NULL, TRUE));
    }

    return WZDR_OK;
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
INT32 wzd_dlg_set_btn_text(
                    HANDLE_T            h_dlg_handle,
                    WZD_DLG_BTN_TYPE_T  e_btn_index,
                    UTF16_T*            pw2s_text,
                    BOOL                b_repaint)
{
    WZD_DLG_CONTROL_T*  pt_dlg_ctrl = NULL;
    INT32               i4_ret = WZDR_OK;

    /* Get dlg control */
    i4_ret = _wzd_dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_ctrl);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] _wzd_dlg_get_attach_data() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    if( NULL == pt_dlg_ctrl )
    {
        DBG_ERROR(( "[WZD][DLG][Show] pt_dlg_ctrl = NULL\n" ));
        return i4_ret;
    }

    if( e_btn_index >= WZD_DLG_BTN_TYPE_COUNT )
    {
        DBG_LOG_PRINT(( "[WZD][DLG][Show] invalid button index = %d\n", (UINT32)e_btn_index ));
        return WZDR_FAIL;
    }

    if( WZD_DLG_BTN_TYPE_01 == e_btn_index )
    {
        if( pt_dlg_ctrl->h_btn_01 )
        {
            RET_ON_ERR (c_wgl_do_cmd (pt_dlg_ctrl->h_btn_01,
                                      WGL_CMD_BTN_SET_TEXT,
                                      WGL_PACK (pw2s_text),
                                      WGL_PACK ((UINT16)0xFFFF)));
        }
    }
    else
    {
        if( pt_dlg_ctrl->h_btn_02 )
        {
            RET_ON_ERR (c_wgl_do_cmd (pt_dlg_ctrl->h_btn_02,
                                      WGL_CMD_BTN_SET_TEXT,
                                      WGL_PACK (pw2s_text),
                                      WGL_PACK ((UINT16)0xFFFF)));
        }
    }

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (pt_dlg_ctrl->h_text, NULL, TRUE));
    }

    return WZDR_OK;
}


/*----------------------------------------------------------------------------
 * Name: wzd_dlg_set_focus_to_btn
 *
 * Description: wzd_dlg_set_focus_to_btn1/btn2
 *
 * Inputs:
 *
 * Outputs:
 *
 * Returns:
 *
 ----------------------------------------------------------------------------*/
INT32 wzd_dlg_set_focus_to_btn(
                    HANDLE_T            h_dlg_handle,
                    WZD_DLG_BTN_TYPE_T  e_btn_index,
                    BOOL                b_repaint)
{
    WZD_DLG_CONTROL_T*  pt_dlg_ctrl = NULL;
    INT32               i4_ret = WZDR_OK;

    /* Get dlg control */
    i4_ret = _wzd_dlg_get_attach_data(h_dlg_handle,
                                  &pt_dlg_ctrl);
    if( WZDR_OK != i4_ret )
    {
        DBG_ERROR(( "[WZD][DLG][Show] _wzd_dlg_get_attach_data() fail, i4_ret =%d\n", i4_ret ));
        return i4_ret;
    }

    if( NULL == pt_dlg_ctrl )
    {
        DBG_ERROR(( "[WZD][DLG][Show] pt_dlg_ctrl = NULL\n" ));
        return i4_ret;
    }

    if( e_btn_index >= WZD_DLG_BTN_TYPE_COUNT )
    {
        DBG_LOG_PRINT(( "[WZD][DLG][Show] invalid button index = %d\n", (UINT32)e_btn_index ));
        return WZDR_FAIL;
    }

    if( WZD_DLG_BTN_TYPE_01 == e_btn_index )
    {
        if( pt_dlg_ctrl->h_btn_01 )
        {
			RET_ON_ERR (c_wgl_set_focus(pt_dlg_ctrl->h_btn_01, b_repaint));
        }
    }
    else
    {
    	if( pt_dlg_ctrl->h_btn_02 )
        {
			RET_ON_ERR (c_wgl_set_focus(pt_dlg_ctrl->h_btn_02, b_repaint));
        }
    }

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (pt_dlg_ctrl->h_text, NULL, TRUE));
    }

    return WZDR_OK;
}

/* Full screen info dialog */

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_nfy_full_screen_dlg
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_nfy_full_screen_dlg(
										HANDLE_T    h_widget,
		                                UINT32      ui4_msg,
		                                VOID*       pv_param1,
		                                VOID*       pv_param2
		                                )
{
	INT32		i4_ret = WZDR_OK;

	switch(ui4_msg)
	{
	case WGL_MSG_KEY_DOWN:
		if (BTN_EXIT == (UINT32)pv_param1)
		{
			/* do something */
		}
		break;

	default:
		break;
	}

	i4_ret = c_wgl_default_msg_proc(
					h_widget,
					ui4_msg,
					pv_param1,
					pv_param2
					);
	return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_full_screen_dlg_icon_create
 *
 * Description: This function creates the dialog icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_full_screen_dlg_icon_create (VOID)
{
    GL_RECT_T           t_rect = {0};
    INT32               i4_ret;
    WGL_INSET_T         t_inset;

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_FULL_SCREEN_DLG_ICON_X,
                      WZD_FULL_SCREEN_DLG_ICON_Y,
                      WZD_FULL_SCREEN_DLG_ICON_W,
                      WZD_FULL_SCREEN_DLG_ICON_H);

    i4_ret = c_wgl_create_widget(t_g_view.h_full_screen_dlg_frm,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &t_g_view.h_full_screen_dlg_icon
                                 );

    RET_ON_ERR (i4_ret);

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_icon,
                              WGL_CMD_ICON_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set icon alignment */
    i4_ret = c_wgl_do_cmd(t_g_view.h_full_screen_dlg_icon,
                          WGL_CMD_ICON_SET_ALIGN,
                          (VOID*)WGL_AS_CENTER_BOTTOM,
                          NULL);
    RET_ON_ERR (i4_ret);

    /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_icon, WGL_SW_HIDE));
	
    return WZDR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _wzd_view_full_screen_dlg_btn_create
 *
 * Description: This function creates the dialog button widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_full_screen_dlg_btn_create (VOID)
{
    GL_RECT_T           t_rect = {0};
    INT32               i4_ret = 0;   
    WGL_FONT_INFO_T     t_fnt_info;
    WGL_COLOR_INFO_T    t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_FULL_SCREEN_DLG_BTN_X,
                      WZD_FULL_SCREEN_DLG_BTN_Y,
                      WZD_FULL_SCREEN_DLG_BTN_W,
                      WZD_FULL_SCREEN_DLG_BTN_H);

    i4_ret = c_wgl_create_widget(t_g_view.h_full_screen_dlg_frm,
                                 HT_WGL_WIDGET_BUTTON,
                                 WGL_CONTENT_BUTTON_DEF,
                                 WGL_BORDER_NULL,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 &t_g_view.h_full_screen_dlg_btn
                                 );
    DBG_INFO(("i4_ret=%d\n", i4_ret));

    /* set font colort */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_footer_enable_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_footer_disable_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_footer_hlt_txt);

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = WZD_FOOTER_FNT_SIZE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (_wzd_view_create_btn_widget(t_g_view.h_full_screen_dlg_frm, 
            WZD_TEXT(MLM_WZD_KEY_DLG_OK), 
            &t_rect, 
            &t_color_info, 
            &t_fnt_info, 
            h_g_wzd_img_button_highlight, 
            h_g_wzd_img_button_highlight, 
            WGL_AS_CENTER_CENTER,
            NULL,
            &t_g_view.h_full_screen_dlg_btn));

    /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_btn, WGL_SW_HIDE));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_full_screen_dlg_text_create
 *
 * Description: This function creates the full screen dialog text widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_full_screen_dlg_text_create(VOID)
{
    WGL_INSET_T                 t_inset;
    WGL_FONT_INFO_T             t_fnt_info;
    GL_RECT_T                   t_rect;
    WGL_COLOR_INFO_T            t_color_info;

    SET_RECT_BY_SIZE (& t_rect,
                      WZD_FULL_SCREEN_DLG_TEXT_X,
                      WZD_FULL_SCREEN_DLG_TEXT_Y,
                      WZD_FULL_SCREEN_DLG_TEXT_W,
                      WZD_FULL_SCREEN_DLG_TEXT_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_full_screen_dlg_frm,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     NULL,
                                     255,
                                     (VOID*)(WGL_STL_TEXT_MULTILINE |
                                             WGL_STL_TEXT_MAX_512  |
                                             WGL_STL_TEXT_MAX_DIS_5_LINE |
                                             WZD_WIDGET_STYLE),
                                     NULL,
                                     & t_g_view.h_full_screen_dlg_txt));

    /* set font size */
    c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_LARGE;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (& t_fnt_info),
                              NULL));

    /* set content inset */
    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (& t_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (WGL_AS_CENTER_TOP),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_desc_txt);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_desc_txt);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT),
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_txt, WGL_SW_HIDE));

    return WZDR_OK;
}


/*----------------------------------------------------------------------------
 * Name: _wzd_view_full_screen_dlg_create
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
static INT32 _wzd_view_full_screen_dlg_create (VOID)
{
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;
    WGL_COLOR_INFO_T    t_color_info;

	t_g_view.b_full_screen_is_show = FALSE;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_FULL_SCREEN_DLG_FRM_X,
                      WZD_FULL_SCREEN_DLG_FRM_Y,
                      WZD_FULL_SCREEN_DLG_FRM_W,
                      WZD_FULL_SCREEN_DLG_FRM_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_main_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _wzd_view_nfy_full_screen_dlg,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_full_screen_dlg_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),
                              WGL_PACK (& t_color_info)));

	t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = MAIN_FRM_IMG_BK_FULL_DLG;
    t_img_info.u_img_data.t_standard.t_disable   = MAIN_FRM_IMG_BK_FULL_DLG;
    t_img_info.u_img_data.t_standard.t_highlight = MAIN_FRM_IMG_BK_FULL_DLG;

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_frm,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK),
                              WGL_PACK (& t_img_info)));

    /* create icon */
    RET_ON_ERR (_wzd_view_full_screen_dlg_icon_create());

    /* create button */
    RET_ON_ERR (_wzd_view_full_screen_dlg_btn_create());

    /* create text */
    RET_ON_ERR (_wzd_view_full_screen_dlg_text_create());

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_frm, WGL_SW_HIDE));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_full_screen_dlg_show
 *
 * Description: The function shows or hides the full screen dialog.
 *
 * Inputs:  b_show                 TRUE - Show full screen dialog.
 *                                 FALSE - Hide full screen dialog.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_full_screen_dlg_show (BOOL b_has_button)
{
    if (b_has_button)
    {
        GL_RECT_T  t_rect = {0};
        
        SET_RECT_BY_SIZE(&t_rect,
                 WZD_FULL_SCREEN_DLG_TEXT_X,
                 WZD_FULL_SCREEN_DLG_ICON_Y + 25,
                 WZD_FULL_SCREEN_DLG_TEXT_W,
                 WZD_FULL_SCREEN_DLG_TEXT_H); 
                 
        RET_ON_ERR (c_wgl_move(t_g_view.h_full_screen_dlg_txt, &t_rect, FALSE));

        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_btn, WGL_SW_NORMAL));
    }
    else
    {
        GL_RECT_T  t_rect = {0};
        
        SET_RECT_BY_SIZE(&t_rect,
                 WZD_FULL_SCREEN_DLG_TEXT_X,
                 WZD_FULL_SCREEN_DLG_TEXT_Y,
                 WZD_FULL_SCREEN_DLG_TEXT_W,
                 WZD_FULL_SCREEN_DLG_TEXT_H); 
                 
        RET_ON_ERR (c_wgl_move(t_g_view.h_full_screen_dlg_txt, &t_rect, FALSE));
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_btn, WGL_SW_HIDE));
    }

    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_icon, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_txt, WGL_SW_NORMAL));

    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_full_screen_dlg_frm, WGL_SW_NORMAL));
    
    RET_ON_ERR (c_wgl_insert (t_g_view.h_full_screen_dlg_frm,
                              NULL_HANDLE,
                              WGL_INSERT_TOPMOST,
                              WGL_NO_AUTO_REPAINT));
    if (b_has_button)
    {
        RET_ON_ERR (c_wgl_set_focus(t_g_view.h_full_screen_dlg_btn, FALSE));
    }
    else
    {
        RET_ON_ERR (c_wgl_set_focus(t_g_view.h_full_screen_dlg_frm, FALSE));
    }
    
    t_g_view.b_full_screen_is_show = TRUE;

    RET_ON_ERR (wzd_view_main_frm_repaint());

    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_full_screen_dlg_hide
 *
 * Description: The function hide the full screen dialog.
 *
 * Inputs:  b_show                 TRUE - Show full screen dialog.
 *                                 FALSE - Hide full screen dialog.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_full_screen_dlg_hide (VOID)
{
	t_g_view.b_full_screen_is_show = FALSE;

    return c_wgl_set_visibility (t_g_view.h_full_screen_dlg_frm, WGL_SW_HIDE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_full_screen_dlg_repaint
 *
 * Description: This API repaints the full screen dialog frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_full_screen_dlg_repaint (VOID)
{
	return c_wgl_repaint (t_g_view.h_full_screen_dlg_frm, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_full_screen_dlg_set_icon
 *
 * Description: The function set image template to the full screen dialog icon.
 *
 *
 *
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_full_screen_dlg_set_icon (
                                WGL_HIMG_TPL_T  h_demo_icon,
                                BOOL            b_repaint)
{
    WGL_IMG_INFO_T              t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_demo_icon;
    t_img_info.u_img_data.t_standard.t_disable = h_demo_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_demo_icon;
    RET_ON_ERR (c_wgl_do_cmd(t_g_view.h_full_screen_dlg_icon,
							WGL_CMD_GL_SET_IMAGE,
							(VOID*)WGL_IMG_FG,
							(VOID*)&t_img_info));

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_full_screen_dlg_icon, NULL, TRUE));
    }

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_full_screen_dlg_icon_create
 *
 * Description: This function creates the dialog icon widget.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_full_screen_dlg_set_btn_proc_fct (wgl_widget_proc_fct pf_proc)
{
       /* set visibility, default hidden */
    RET_ON_ERR (c_wgl_set_widget_proc(t_g_view.h_full_screen_dlg_btn, pf_proc));
	
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_full_screen_dlg_set_btn_text
 *
 * Description: The function set the full screen dialog text.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_full_screen_dlg_set_btn_text (
								UTF16_T*		pw2s_text,
								BOOL            b_repaint)
{
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_btn,
                      WGL_CMD_BTN_SET_TEXT,
                      WGL_PACK (pw2s_text),
                      WGL_PACK ((UINT16)0xFFFF)));

	if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_full_screen_dlg_btn, NULL, TRUE));
    }

    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_full_screen_dlg_set_text
 *
 * Description: The function set the full screen dialog text.
 *
 * Inputs:
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_full_screen_dlg_set_text (
								UTF16_T*		pw2s_text,
								BOOL            b_repaint)
{
    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_full_screen_dlg_txt,
                      WGL_CMD_TEXT_SET_TEXT,
                      WGL_PACK (pw2s_text),
                      WGL_PACK ((UINT16)0xFFFF)));

	if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_full_screen_dlg_txt, NULL, TRUE));
    }

    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_full_screen_dlg_is_show
 *
 * Description: This API repaints the full screen dialog frame is show.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: TRUE                      Show.
 *			FALSE                     Hide.
 ----------------------------------------------------------------------------*/
BOOL wzd_view_full_screen_dlg_is_show (VOID)
{
	return t_g_view.b_full_screen_is_show;
}

/* Select box widget */
/*-----------------------------------------------------------------------------
 * Name: _wzd_view_create_sel_box_btn_widget
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_sel_box_btn_widget(
		    HANDLE_T                    h_parent,
		    const GL_RECT_T*            pt_rect,
		    const WGL_COLOR_INFO_T*     pt_color_info,
		    WGL_HIMG_TPL_T              t_img_tpl_ht,
		    WGL_HIMG_TPL_T              t_img_tpl_un_ht,
		    wgl_widget_proc_fct         pf_wdgt_proc,
		    HANDLE_T*                   ph_btn)
{
    WGL_IMG_INFO_T      t_img_info;

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     pf_wdgt_proc,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     NULL,
                                     ph_btn));

    /* set theme */
    RET_ON_ERR (c_wgl_do_cmd (*ph_btn,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK(pt_color_info)));

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_standard.t_disable   = t_img_tpl_un_ht;
    t_img_info.u_img_data.t_standard.t_highlight = t_img_tpl_ht;

    RET_ON_ERR (c_wgl_do_cmd (*ph_btn,
                              WGL_CMD_GL_SET_IMAGE,
                              WGL_PACK (WGL_IMG_BK), /* background image */
                              WGL_PACK (&t_img_info)));

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_sel_box_create_txt
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_sel_box_create_txt (
                           GL_RECT_T*               pt_rect,
                           HANDLE_T                 h_parent,
                           wgl_widget_proc_fct      pf_wdgt_proc,
                           UINT32                   ui4_style,
                           HANDLE_T*                ph_txt,
                           WGL_FONT_INFO_T*         pt_fnt_info,
                           UINT8                    ui1_align,
                           WGL_COLOR_INFO_T*        pt_color_bk,
                           WGL_COLOR_INFO_T*        pt_color_fg,
                           WGL_INSET_T*             pt_inset)
{
    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (h_parent,
                                     HT_WGL_WIDGET_TEXT,
                                     WGL_CONTENT_TEXT_DEF,
                                     WGL_BORDER_NULL,
                                     pt_rect,
                                     pf_wdgt_proc,
                                     255,
                                     (VOID*)ui4_style,
                                     NULL,
                                     ph_txt));

    /* set font size */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_FONT,
                              WGL_PACK (pt_fnt_info),
                              NULL));

    /* set content inset */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_CNT_INSET,
                              WGL_PACK (pt_inset),
                              NULL));

    /* set alignment */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_ALIGN,
                              WGL_PACK (ui1_align),
                              NULL));

    /* set line gap */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_TEXT_SET_LINE_GAP,
                              WGL_PACK ((INT32) 0),
                              NULL));

    /* set theme */
    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK), /* background color */
                              WGL_PACK (pt_color_bk)));

    RET_ON_ERR (c_wgl_do_cmd (*ph_txt,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_TEXT), /* text color */
                              WGL_PACK (pt_color_fg)));	

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (*ph_txt, WGL_SW_HIDE));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_sel_box_create_icon
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
static INT32 _wzd_view_sel_box_create_icon(HANDLE_T		h_parent,
                                           HANDLE_T*    ph_widget,
                                           GL_RECT_T*	pt_rect)
{   
    RET_ON_ERR (c_wgl_create_widget(h_parent,
							  HT_WGL_WIDGET_ICON,
							  WGL_CONTENT_ICON_DEF,
							  WGL_BORDER_NULL,
							  pt_rect,
							  NULL,
							  255,
							  (VOID*)WGL_STL_GL_NO_BK,
							  NULL,
							  ph_widget));

    RET_ON_ERR (c_wgl_do_cmd(*ph_widget,
							  WGL_CMD_ICON_SET_ALIGN,
							  WGL_PACK(WGL_AS_CENTER_CENTER),
							  NULL));

    RET_ON_ERR (c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE));
    
    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_sel_box_create_plus_icon
 *
 * Description:
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_sel_box_create_plus_icon (HANDLE_T   h_parent,
                                                 HANDLE_T*  ph_widget)
{
    INT32               i4_ret = 0;
    GL_RECT_T           t_rect;
    WGL_IMG_INFO_T      t_img_info;

	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
    SET_RECT_BY_SIZE(&t_rect,
	                 WZD_SEL_BOX_BTN_ICON_1_X,
	                 WZD_SEL_BOX_BTN_ICON_1_Y + 28 * WZD_UI_RATIO, 
	                 WZD_SEL_BOX_BTN_ICON_1_W,
	                 WZD_SEL_BOX_BTN_ICON_1_H);
        
    i4_ret = c_wgl_create_widget(h_parent,
                                 HT_WGL_WIDGET_ICON,
                                 WGL_CONTENT_ICON_DEF,
                                 WGL_BORDER_TIMG,
                                 &t_rect,
                                 NULL,
                                 255,
                                 (VOID*)0,
                                 NULL,
                                 ph_widget);
    RET_ON_ERR(i4_ret);

    /* Set EB Alignment */
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_ICON_SET_ALIGN,
                          WGL_PACK(WGL_AS_CENTER_CENTER),
                          NULL);
    RET_ON_ERR(i4_ret);

    /* Set images */
    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable    = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_highlight = NULL_HANDLE;
    t_img_info.u_img_data.t_standard.t_disable   = NULL_HANDLE;
    i4_ret = c_wgl_do_cmd(*ph_widget,
                          WGL_CMD_GL_SET_IMAGE,
                          WGL_PACK(WGL_IMG_FG),
                          WGL_PACK(&t_img_info));
    RET_ON_ERR(i4_ret);

    RET_ON_ERR(c_wgl_set_visibility(*ph_widget, WGL_SW_HIDE));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_nfy_sel_box_frm
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_nfy_sel_box_frm (HANDLE_T    h_widget,
		                                UINT32      ui4_msg,
		                                VOID*       pv_param1,
		                                VOID*       pv_param2)
{
    HANDLE_T              h_cb_widget;
    WGL_NOTIFY_DATA_T*    pt_wgl_nfy_data;
    UINT32                ui4_i = 0;

	if (t_g_view.t_sb_ctrl.b_ignore_msg)
	{
		return WZDR_OK;
	}

    h_cb_widget     = (HANDLE_T) pv_param1;
    pt_wgl_nfy_data = (WGL_NOTIFY_DATA_T*) pv_param2;

    if (ui4_msg == WGL_MSG_NOTIFY)
    {
        if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_GL_GET_FOCUS) /* some widget gets focus */
        {	
            for (ui4_i = 0; ui4_i < WZD_SEL_BOX_BTN_COUNT; ui4_i++)
            {
                if (h_cb_widget == t_g_view.ah_sb_btn[ui4_i])
                {
                	/* float current widget */
                	c_wgl_float(h_cb_widget, TRUE, FALSE);
                	if (ui4_i > 0)
					{
						c_wgl_float (t_g_view.ah_sb_btn[ui4_i-1], FALSE, FALSE);
					}
					if (ui4_i+1 < WZD_SEL_BOX_BTN_COUNT)
					{
						c_wgl_float (t_g_view.ah_sb_btn[ui4_i+1], FALSE, FALSE);
					}
					
                	if (NULL != t_g_view.t_sb_info.pf_data_chg_nfy)
                	{
                    	t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_ITEM_FOCUSED, (VOID*)t_g_view.t_sb_ctrl.ui4_index_current, NULL);
                	}
                    break;
                }
            }
        }
		else if (pt_wgl_nfy_data->ui4_nc_code == WGL_NC_GL_LOSE_FOCUS) /* lose focus */
		{
			for (ui4_i = 0; ui4_i < WZD_SEL_BOX_BTN_COUNT; ui4_i++)
            {
                if (h_cb_widget == t_g_view.ah_sb_btn[ui4_i])
                {
                	/* un-float current widget */
                	c_wgl_float(h_cb_widget, FALSE, FALSE);

					if (NULL != t_g_view.t_sb_info.pf_data_chg_nfy)
					{
						t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_ITEM_LOSE_FOCUSED, (VOID*)t_g_view.t_sb_ctrl.ui4_index_current, NULL);
					}
                    break;
                }
            }
		}
    }

    return c_wgl_default_msg_proc (h_widget, ui4_msg, pv_param1, pv_param2);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_sel_box_btn_nfy_fct
 *
 * Description: The function is called by the Widget Library when child widgets
 *              call back.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_sel_box_btn_nfy_fct(
                    HANDLE_T                    h_widget,
                    UINT32                      ui4_msg,
                    VOID*                       pv_param1,
                    VOID*                       pv_param2
                    )
{
    INT32       	i4_ret = WZDR_OK;
    UINT32      	ui1_i = 0;
	BOOL			b_need_shift = FALSE;

	WZD_SEL_BOX_BTN_INDEX_T e_enable_index = WZD_SEL_BOX_BTN_COUNT;

    switch(ui4_msg)
    {
    case WGL_MSG_KEY_DOWN:
        for (ui1_i = 0; ui1_i < WZD_SEL_BOX_BTN_COUNT; ui1_i++)
        {
        	/* focused button found */
            if (h_widget == t_g_view.ah_sb_btn[ui1_i])
            {
                break;
            }
        }

		/* deal with LEFT & RIGHT key first */
		if (BTN_CURSOR_LEFT == (UINT32)pv_param1)
        {
			i4_ret = _wzd_view_sel_box_get_previous_btn(ui1_i, &e_enable_index);
	        if (WZDR_FAIL == i4_ret)
	        {
	        	return WZDR_FAIL;
	        }

			/* just 6 box */
			if (t_g_view.t_sb_info.ui4_index_total == WZD_SEL_BOX_BTN_COUNT-1)
			{
				if (e_enable_index == WZD_SEL_BOX_BTN_03)
				{
					/* reset sel box frame */
					_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_RIGHT);
				}
 				else
 				{
					/* do nothing */
				}
			}
			else if (t_g_view.t_sb_info.ui4_index_total > WZD_SEL_BOX_BTN_COUNT-1)
			{
				if (e_enable_index == WZD_SEL_BOX_BTN_04)
				{
					/* reset sel box frame */
					_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_CENTER);
				}
 				else if (e_enable_index < WZD_SEL_BOX_BTN_04)
				{
					/* keep focus middle box */
					if (t_g_view.t_sb_ctrl.ui4_index_current > WZD_SEL_BOX_BTN_04)
					{
						b_need_shift = TRUE;
						e_enable_index = WZD_SEL_BOX_BTN_04;
					}
					else if (t_g_view.t_sb_ctrl.ui4_index_current == 3)
					{
						/* reset sel box frame */
						_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_RIGHT);

						t_g_view.t_sb_ctrl.ui4_index_offset = 0;
					}
					else
					{
						/* focus previous box */
					}
				}
				else
				{
					/* do nothing */
				}
			}
			else
			{
				/* reset sel box frame */
				_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_CENTER);
			}

			t_g_view.t_sb_ctrl.ui4_index_current--;

			if (b_need_shift)
			{
				t_g_view.t_sb_ctrl.ui4_index_offset = t_g_view.t_sb_ctrl.ui4_index_current - ui1_i;

				/* Left shift 1 button, update button content by custom */
				if (NULL != t_g_view.t_sb_info.pf_data_chg_nfy)
				{
		        	t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_ITEM_LEFT_SHIFT, (VOID*)t_g_view.t_sb_ctrl.ui4_index_current, NULL);
				}
			}
			else
			{
				/* set focus to pre box */
				t_g_view.t_sb_ctrl.b_ignore_msg = TRUE;

				i4_ret = c_wgl_set_focus(t_g_view.ah_sb_btn[e_enable_index], FALSE);
		    	RET_ON_ERR (i4_ret);

				if (NULL != t_g_view.t_sb_info.pf_data_chg_nfy)
            	{
            		c_wgl_float(t_g_view.ah_sb_btn[e_enable_index+1], FALSE, FALSE);
					c_wgl_float(t_g_view.ah_sb_btn[e_enable_index], TRUE, FALSE);
					
            		t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_ITEM_LOSE_FOCUSED, (VOID*)(t_g_view.t_sb_ctrl.ui4_index_current + 1), NULL);
                	t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_ITEM_FOCUSED, (VOID*)t_g_view.t_sb_ctrl.ui4_index_current, NULL);
            	}
				t_g_view.t_sb_ctrl.b_ignore_msg = FALSE;
			}

			RET_ON_ERR (c_wgl_repaint (t_g_view.h_base_frm, NULL, TRUE));
			
            return WZDR_OK;
        }
		else if (BTN_CURSOR_RIGHT == (UINT32)pv_param1)
		{
			
			i4_ret = _wzd_view_sel_box_get_next_btn(ui1_i, &e_enable_index);
	        if (WZDR_FAIL == i4_ret)
	        {
	        	return WZDR_FAIL;
	        }

			/* just 6 box */
			if (t_g_view.t_sb_info.ui4_index_total == WZD_SEL_BOX_BTN_COUNT-1)
			{
				if (e_enable_index == WZD_SEL_BOX_BTN_04)
				{
					/* reset sel box frame */
					_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_CENTER);
				}
 				else
 				{
					/* do nothing */
				}
			}
			else if (t_g_view.t_sb_info.ui4_index_total > WZD_SEL_BOX_BTN_COUNT-1)
			{
				if (e_enable_index == WZD_SEL_BOX_BTN_04)
				{
					/* reset sel box frame */
					_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_CENTER);
				}
 				else if (e_enable_index > WZD_SEL_BOX_BTN_04)
				{
					if (t_g_view.t_sb_ctrl.ui4_index_current == t_g_view.t_sb_info.ui4_index_total-4)
					{
						/* reset sel box frame */
						_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_LEFT);
					}
					else if (t_g_view.t_sb_ctrl.ui4_index_current < t_g_view.t_sb_info.ui4_index_total-4)
					{
						/* keep focus middle box */
						b_need_shift = TRUE;
						e_enable_index = WZD_SEL_BOX_BTN_04;
					}
					else
					{
						/* focus next box */
					}
				}
				else
				{
					t_g_view.t_sb_ctrl.ui4_index_offset = 0;
				}
			}
			else
			{
				/* reset sel box frame */
				_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_CENTER);
			}

			t_g_view.t_sb_ctrl.ui4_index_current++;

			if (b_need_shift)
			{
				t_g_view.t_sb_ctrl.ui4_index_offset = t_g_view.t_sb_ctrl.ui4_index_current - ui1_i;

				/* Right shift 1 button, update button content by custom */
				if (NULL != t_g_view.t_sb_info.pf_data_chg_nfy)
				{
		        	t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_ITEM_RIGHT_SHIFT, (VOID*)t_g_view.t_sb_ctrl.ui4_index_current, NULL);
				}
			}
			else
			{
				/* set focus to next box */
				t_g_view.t_sb_ctrl.b_ignore_msg = TRUE;

				i4_ret = c_wgl_set_focus(t_g_view.ah_sb_btn[e_enable_index], FALSE);
		    	RET_ON_ERR (i4_ret);

				if (NULL != t_g_view.t_sb_info.pf_data_chg_nfy)
            	{
					c_wgl_float(t_g_view.ah_sb_btn[e_enable_index-1], FALSE, FALSE);
					c_wgl_float(t_g_view.ah_sb_btn[e_enable_index], TRUE, FALSE);
					
            		t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_ITEM_LOSE_FOCUSED, (VOID*)(t_g_view.t_sb_ctrl.ui4_index_current - 1), NULL);
                	t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_ITEM_FOCUSED, (VOID*)t_g_view.t_sb_ctrl.ui4_index_current, NULL);
            	}
				t_g_view.t_sb_ctrl.b_ignore_msg = FALSE;
			}

			RET_ON_ERR (c_wgl_repaint (t_g_view.h_base_frm, NULL, TRUE));
				
            return WZDR_OK;
		}
		
		if (NULL != t_g_view.t_sb_info.pf_data_chg_nfy)
		{
        	t_g_view.t_sb_info.pf_data_chg_nfy(WZD_SEL_BOX_MSG_KEY_INPUT, pv_param1, (VOID*)t_g_view.t_sb_ctrl.ui4_index_current);
		}

        if (BTN_SELECT == (UINT32)pv_param1)
		{
			return WZDR_OK;
		}
        break;

    default:
        break;
    }

    i4_ret = c_wgl_default_msg_proc(
                    h_widget,
                    ui4_msg,
                    pv_param1,
                    pv_param2
                    );
    return i4_ret;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_sel_box_frm
 *
 * Description: This function creates a select box frame to display background
 *              image.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_sel_box_frm (VOID)
{
    GL_RECT_T           t_rect;
    WGL_COLOR_INFO_T    t_color_info;

    /* get rectangle size */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_SEL_BOX_FRM_X,
                      WZD_SEL_BOX_FRM_Y,
                      WZD_SEL_BOX_FRM_W,
                      WZD_SEL_BOX_FRM_H);

    /* create widget */
    RET_ON_ERR (c_wgl_create_widget (t_g_view.h_base_frm,
                                     HT_WGL_WIDGET_FRAME,
                                     WGL_CONTENT_FRAME_DEF,
                                     WGL_BORDER_NULL,
                                     & t_rect,
                                     _wzd_view_nfy_sel_box_frm,
                                     255,
                                     (VOID*) WZD_WIDGET_STYLE,
                                     0,
                                     & t_g_view.h_sb_frm));

    /* set theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.h_sb_frm,
                              WGL_CMD_GL_SET_COLOR,
                              WGL_PACK (WGL_CLR_BK),
                              WGL_PACK (& t_color_info)));

    /* set visibility */
    RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_sb_frm, WGL_SW_HIDE));

    return  WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_create_sel_box_buttons
 *
 * Description: This function creates the select box buttons.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_create_sel_box_buttons (VOID)
{
    GL_RECT_T           at_btn_rect[WZD_SEL_BOX_BTN_COUNT] = WZD_SEL_BOX_7_BTN_GET_RECTS();
    UINT8               ui1_i = 0;
    WGL_COLOR_INFO_T    t_color_info;
    INT32               i4_ret = 0;

	/* text */
	GL_RECT_T      		t_rect;
    UINT32             	ui4_style = 0;
    WGL_FONT_INFO_T    	t_fnt_info;
    UINT8              	ui1_align = 0;
    WGL_COLOR_INFO_T  	t_color_info_bg, t_color_info_fg;
    WGL_INSET_T        	t_inset;


	/* initial style mask */
	t_g_view.t_sb_info.ui4_index_total 	= WZD_SEL_BOX_BTN_COUNT;

	t_g_view.t_sb_ctrl.ui4_index_current= 0;
	t_g_view.t_sb_ctrl.ui4_index_offset	= 0;

	/* set select box button theme */
    t_color_info.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_enable,    &t_g_wzd_color_base_frm_bk);
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_disable,   &t_g_wzd_color_base_frm_bk);
    COLOR_COPY (&t_color_info.u_color_data.t_standard.t_highlight, &t_g_wzd_color_base_frm_bk);

    for( ui1_i = 0; ui1_i < WZD_SEL_BOX_BTN_COUNT ; ui1_i++ )
    {
        i4_ret = _wzd_view_create_sel_box_btn_widget(
                t_g_view.h_sb_frm,
                &at_btn_rect[ui1_i],
                &t_color_info,
                h_g_wzd_img_select_box_highlight,
                h_g_wzd_img_select_box,
                _wzd_view_sel_box_btn_nfy_fct,
                &t_g_view.ah_sb_btn[ui1_i]
                );
        RET_ON_ERR (i4_ret);
    }

	/* create extern icon on FIRST button */
    i4_ret = _wzd_view_sel_box_create_plus_icon(t_g_view.ah_sb_btn[0], &t_g_view.h_sb_icon_plus);
	RET_ON_ERR(i4_ret);

	/* set select box text theme */
    SET_RECT_BY_SIZE (& t_rect,
                      WZD_SEL_BOX_BTN_TXT_X,
                      WZD_SEL_BOX_BTN_TXT_Y,
                      WZD_SEL_BOX_BTN_TXT_W,
                      WZD_SEL_BOX_BTN_TXT_H);

    ui4_style = WGL_STL_TEXT_MULTILINE |
				WGL_STL_TEXT_MAX_128  |
				WGL_STL_TEXT_MAX_DIS_5_LINE |
				WZD_WIDGET_STYLE;
		
    /* set font size */
	c_memset (& t_fnt_info, 0, sizeof (WGL_FONT_INFO_T));
    c_strcpy (t_fnt_info.a_c_font_name, t_g_view.s_font_name);

    t_fnt_info.e_font_size  = FE_FNT_SIZE_MEDIUM;
    t_fnt_info.e_font_style = FE_FNT_STYLE_REGULAR;
    t_fnt_info.e_font_cmap  = FE_CMAP_ENC_UNICODE;

    ui1_align = WGL_AS_CENTER_CENTER;

    t_color_info_bg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_base_frm_bk);
    COLOR_COPY (& t_color_info_bg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_base_frm_bk);

    t_color_info_fg.e_type = WGL_COLOR_SET_STANDARD;
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_enable,    & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_disable,   & t_g_wzd_color_sel_box_enable_txt);
    COLOR_COPY (& t_color_info_fg.u_color_data.t_standard.t_highlight, & t_g_wzd_color_sel_box_enable_txt);

    t_inset.i4_left   = 0;
    t_inset.i4_right  = 0;
    t_inset.i4_top    = 0;
    t_inset.i4_bottom = 0;

	for( ui1_i = 0 ; ui1_i < WZD_SEL_BOX_BTN_COUNT ; ui1_i ++ )
	{
		i4_ret = _wzd_view_sel_box_create_txt(
	            &t_rect,
	            t_g_view.ah_sb_btn[ui1_i],
	            NULL,
	            ui4_style,
	            &t_g_view.ah_sb_txt[ui1_i],
	            &t_fnt_info,
	            ui1_align,
	            &t_color_info_bg,
	            &t_color_info_fg,
	            &t_inset);
		RET_ON_ERR (i4_ret);
	}

	/* set first icon theme */
	SET_RECT_BY_SIZE (& t_rect,
                      WZD_SEL_BOX_BTN_ICON_1_X,
                      WZD_SEL_BOX_BTN_ICON_1_Y,
                      WZD_SEL_BOX_BTN_ICON_1_W,
                      WZD_SEL_BOX_BTN_ICON_1_H);
	
	for( ui1_i = 0 ; ui1_i < WZD_SEL_BOX_BTN_COUNT ; ui1_i ++ )
	{
		i4_ret = _wzd_view_sel_box_create_icon(
	            t_g_view.ah_sb_btn[ui1_i],
	            &t_g_view.ah_sb_icon_1[ui1_i],
	            &t_rect);
		RET_ON_ERR (i4_ret);
	}

	/* set second icon theme */
	SET_RECT_BY_SIZE (& t_rect,
                      WZD_SEL_BOX_BTN_ICON_2_X,
                      WZD_SEL_BOX_BTN_ICON_2_Y,
                      WZD_SEL_BOX_BTN_ICON_2_W,
                      WZD_SEL_BOX_BTN_ICON_2_H);
	
	for( ui1_i = 0 ; ui1_i < WZD_SEL_BOX_BTN_COUNT ; ui1_i ++ )
	{
		i4_ret = _wzd_view_sel_box_create_icon(
	            t_g_view.ah_sb_btn[ui1_i],
	            &t_g_view.ah_sb_icon_2[ui1_i],
	            &t_rect);
		RET_ON_ERR (i4_ret);
	}

    return WZDR_OK;
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_sel_box_get_next_btn
 *
 * Description: This function get the next enable footer btn from a specified index.
 *
 * Inputs:           e_sel_box_index - The index of the specified select box button
 *                   pe_next_btn_index - the index of the next enabled button
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed. If not found, it will return WZDR_FAIL.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_sel_box_get_next_btn (
                                WZD_SEL_BOX_BTN_INDEX_T  e_sel_box_index,
                                WZD_SEL_BOX_BTN_INDEX_T* pe_next_btn_index)
{
    UINT32 ui4_j = 0;

    if (pe_next_btn_index == NULL)
    {
        return WZDR_FAIL;
    }

    if (e_sel_box_index >= WZD_SEL_BOX_BTN_COUNT)
    {
        return WZDR_FAIL;
    }

    ui4_j = e_sel_box_index + 1;

    while (ui4_j < WZD_SEL_BOX_BTN_COUNT)
    {
        if (TRUE == t_g_view.t_sb_ctrl.ab_enabled[ui4_j])
        {
            *pe_next_btn_index = (WZD_SEL_BOX_BTN_INDEX_T)ui4_j;
            return WZDR_OK;
        }
        ui4_j++;
    }

    return  WZDR_FAIL;  /* Not found */
}

/*----------------------------------------------------------------------------
 * Name: _wzd_view_sel_box_get_previous_btn
 *
 * Description: This function get the prevous enable footer btn from a specified index.
 *
 * Inputs:           e_footer_index - The index of the specified select box button
 *                   pe_pre_btn_index - the index of the previous enabled button
 *
 * Outputs: -
 *
 * Returns: 0                  Successful.
 *          Any other values   Failed. If not found, it will return WZDR_FAIL.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_sel_box_get_previous_btn (
                                WZD_SEL_BOX_BTN_INDEX_T  e_sel_box_index,
                                WZD_SEL_BOX_BTN_INDEX_T* pe_pre_btn_index)
{	
    INT32 i4_j = 0;

    if( pe_pre_btn_index == NULL )
    {
        return WZDR_FAIL;
    }

    if( e_sel_box_index >= WZD_SEL_BOX_BTN_COUNT )
    {
        return WZDR_FAIL;
    }

    i4_j  = e_sel_box_index - 1;

    while( i4_j >= WZD_SEL_BOX_BTN_01 )
    {
        if( TRUE == t_g_view.t_sb_ctrl.ab_enabled[i4_j] )
        {
            *pe_pre_btn_index = (WZD_SEL_BOX_BTN_INDEX_T)i4_j;
            return WZDR_OK;
        }
        i4_j--;
    }

    return  WZDR_FAIL;  /* Not found */
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_sel_box_frm_move_by_direction
 *
 * Description: The function move frame postion by direction.
 *
 * Inputs:	
 * Inputs:	
 *
 * Outputs: -
 *
 * Returns: 0					   Successful.
 *			Any other values	   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_T e_direction)
{
	INT32   		i4_left;
	GL_RECT_T   	t_rect;

	if (t_g_view.t_sb_info.ui4_index_total < WZD_SEL_BOX_BTN_COUNT - 1)
	{
		i4_left = WZD_SEL_BOX_FRM_X;
	}
	else
	{
		if (WZD_SEL_BOX_FRM_MOVE_LEFT == e_direction)
		{
			i4_left = WZD_SEL_BOX_FRM_X - WZD_SEL_BOX_BTN_W - WZD_SEL_BOX_BTN_GAP;
		}
		else if (WZD_SEL_BOX_FRM_MOVE_RIGHT == e_direction)
		{
			i4_left = WZD_SEL_BOX_FRM_X + WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP;
		}
		else
		{
			i4_left = WZD_SEL_BOX_FRM_X;
		}
	}

	c_memset(&t_rect, 0, sizeof(GL_RECT_T));
	SET_RECT_BY_SIZE (& t_rect,
                      i4_left,
                      WZD_SEL_BOX_FRM_Y,
                      WZD_SEL_BOX_FRM_W,
                      WZD_SEL_BOX_FRM_H);

	RET_ON_ERR (c_wgl_move(
				t_g_view.h_sb_frm,
				&t_rect, 
				FALSE));

	return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_show
 *
 * Description: The function shows or hides the select box frame.
 *
 * Inputs:  b_show                 TRUE - Show select box frame.
 *                                 FALSE - Hide select box frame.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_sel_box_show (BOOL b_show)
{
    if (b_show) /* show select box frame */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_sb_frm, WGL_SW_NORMAL));
    }
    else /* hide select box frame */
    {
        RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_sb_frm, WGL_SW_HIDE));
    }

    return  WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_frm_repaint
 *
 * Description: This API repaints the select box frame.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                   Successful.
 *          Any other values    Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_sel_box_frm_repaint (VOID)
{
    return  c_wgl_repaint (t_g_view.h_sb_frm, NULL, TRUE);
}

/*-----------------------------------------------------------------------------
 * Name: _wzd_view_sel_box_update_btn_pos
 *
 * Description: The function update button postion by total index.
 *
 * Inputs:	
 * Inputs:	
 *
 * Outputs: -
 *
 * Returns: 0					   Successful.
 *			Any other values	   Failed.
 ----------------------------------------------------------------------------*/
static INT32 _wzd_view_sel_box_update_btn_pos(VOID)
{
	UINT8			ui1_i = 0;
	UINT32			ui4_total;
	INT32   		i4_left;		/* left margins */
	GL_RECT_T   	t_rect;

	ui4_total = t_g_view.t_sb_info.ui4_index_total;

	/* update button postion by total index */
	if (0 == ui4_total)
	{
		RET_ON_ERR (c_wgl_set_visibility (t_g_view.h_sb_frm, WGL_SW_HIDE));
	}
	else if (ui4_total < WZD_SEL_BOX_BTN_COUNT - 1)
	{
		RET_ON_ERR (_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_CENTER));

		/* the first select box button left margins */
		i4_left = (WZD_SEL_BOX_FRM_W - ui4_total*WZD_SEL_BOX_BTN_W - (ui4_total-1)*WZD_SEL_BOX_BTN_GAP)/2;
		
		/* set enable */
		for (ui1_i = 0 ; ui1_i < ui4_total; ui1_i ++)
		{			
			t_g_view.t_sb_ctrl.ab_enabled[ui1_i] = TRUE;

			/* update button position */
			SET_RECT_BY_SIZE (&t_rect,
				(i4_left + (WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP) * ui1_i),
				WZD_SEL_BOX_BTN_Y,
				WZD_SEL_BOX_BTN_W,
				WZD_SEL_BOX_BTN_H);
			
			RET_ON_ERR (c_wgl_move(
				t_g_view.ah_sb_btn[ui1_i],
				&t_rect, 
				FALSE));

			/* set visibility */
			RET_ON_ERR (c_wgl_set_visibility(
				t_g_view.ah_sb_btn[ui1_i],
				WGL_SW_NORMAL));
		}

		/* dis-enable */
		for (ui1_i = ui4_total; ui1_i < WZD_SEL_BOX_BTN_COUNT; ui1_i ++)
		{	
			t_g_view.t_sb_ctrl.ab_enabled[ui1_i] = FALSE;
			
			RET_ON_ERR (c_wgl_set_visibility(
				t_g_view.ah_sb_btn[ui1_i],
				WGL_SW_HIDE));
		}
	}
	else if (ui4_total == WZD_SEL_BOX_BTN_COUNT - 1)
	{
		RET_ON_ERR (_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_RIGHT));

		/* the first select box button left margins */
		i4_left = (WZD_SEL_BOX_FRM_W - WZD_SEL_BOX_BTN_COUNT*WZD_SEL_BOX_BTN_W - (WZD_SEL_BOX_BTN_COUNT-1)*WZD_SEL_BOX_BTN_GAP)/2;
		
		/* set previous 6 buttons enable */
		for (ui1_i = 0; ui1_i < WZD_SEL_BOX_BTN_COUNT - 1; ui1_i ++)
		{	
			t_g_view.t_sb_ctrl.ab_enabled[ui1_i] = TRUE;

			/* update button position */
			SET_RECT_BY_SIZE (&t_rect,
				(i4_left + (WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP) * ui1_i),
				WZD_SEL_BOX_BTN_Y,
				WZD_SEL_BOX_BTN_W,
				WZD_SEL_BOX_BTN_H);
			
			RET_ON_ERR (c_wgl_move(
				t_g_view.ah_sb_btn[ui1_i],
				&t_rect, 
				FALSE));

			/* set visibility */
			RET_ON_ERR (c_wgl_set_visibility(
				t_g_view.ah_sb_btn[ui1_i],
				WGL_SW_NORMAL));
		}

		/* set sixth box dis-enable */
		t_g_view.t_sb_ctrl.ab_enabled[WZD_SEL_BOX_BTN_COUNT - 1] = FALSE;

		RET_ON_ERR (c_wgl_set_visibility(
			t_g_view.ah_sb_btn[WZD_SEL_BOX_BTN_COUNT - 1],
			WGL_SW_HIDE));
	}
	else
	{
		RET_ON_ERR (_wzd_view_sel_box_frm_move_by_direction(WZD_SEL_BOX_FRM_MOVE_RIGHT));

		/* the first select box button left margins */
		i4_left = (WZD_SEL_BOX_FRM_W - WZD_SEL_BOX_BTN_COUNT*WZD_SEL_BOX_BTN_W - (WZD_SEL_BOX_BTN_COUNT-1)*WZD_SEL_BOX_BTN_GAP)/2;
		
		/* set all button enable */
		for (ui1_i = 0; ui1_i < WZD_SEL_BOX_BTN_COUNT; ui1_i ++)
		{	
			t_g_view.t_sb_ctrl.ab_enabled[ui1_i] = TRUE;

			/* update button position */
			SET_RECT_BY_SIZE (&t_rect,
				(i4_left + (WZD_SEL_BOX_BTN_W + WZD_SEL_BOX_BTN_GAP) * ui1_i),
				WZD_SEL_BOX_BTN_Y,
				WZD_SEL_BOX_BTN_W,
				WZD_SEL_BOX_BTN_H);
			
			RET_ON_ERR (c_wgl_move(
				t_g_view.ah_sb_btn[ui1_i],
				&t_rect, 
				FALSE));

			/* set visibility */
			RET_ON_ERR (c_wgl_set_visibility(
				t_g_view.ah_sb_btn[ui1_i],
				WGL_SW_NORMAL));
		}
	}

	return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_set_info_data
 *
 * Description: The function set text to select box buttons.
 *
 * Inputs:  e_sel_box_index                  Which select box button.
 * Inputs:  b_enable                         Enable or disable.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_sel_box_set_info_data (WZD_VIEW_SEL_BOX_INFO_T*	pt_info_data)
{
	UINT8           ui1_i = 0;
	
	if (NULL == pt_info_data)
	{
		return WZDR_INV_ARG;
	}

	t_g_view.t_sb_info.ui4_index_total 	= pt_info_data->ui4_index_total;
	t_g_view.t_sb_info.pf_data_chg_nfy 	= pt_info_data->pf_data_chg_nfy;

	/* reset flag & resource */
	t_g_view.t_sb_ctrl.ui4_index_current= 0;
	t_g_view.t_sb_ctrl.ui4_index_offset	= 0;
	t_g_view.t_sb_ctrl.b_ignore_msg = FALSE;

	for( ui1_i = 0 ; ui1_i < WZD_SEL_BOX_BTN_COUNT ; ui1_i ++ )
	{
		RET_ON_ERR (c_wgl_do_cmd(
						t_g_view.ah_sb_txt[ui1_i],
						WGL_CMD_TEXT_SET_TEXT,
						WGL_PACK (NULL),
						WGL_PACK (0)));

		RET_ON_ERR (c_wgl_do_cmd (
						t_g_view.ah_sb_icon_1[ui1_i],
						WGL_CMD_GL_SET_IMAGE,
						WGL_PACK(WGL_IMG_FG),
						WGL_PACK(NULL)))

		RET_ON_ERR (c_wgl_do_cmd (
						t_g_view.ah_sb_icon_2[ui1_i],
						WGL_CMD_GL_SET_IMAGE,
						WGL_PACK(WGL_IMG_FG),
						WGL_PACK(NULL)))
	}

	/* reset additional icon */
	wzd_view_sel_box_set_plus_icon(NULL_HANDLE, FALSE);

	/* update button postion by total index */
	_wzd_view_sel_box_update_btn_pos();

	/* update visibility */
	for( ui1_i = 0 ; ui1_i < WZD_SEL_BOX_BTN_COUNT ; ui1_i ++ )
	{
		if( TRUE == t_g_view.t_sb_ctrl.ab_enabled[ui1_i] )
        {
            RET_ON_ERR (c_wgl_set_visibility(
						t_g_view.ah_sb_txt[ui1_i],
						WGL_SW_NORMAL));

			RET_ON_ERR (c_wgl_set_visibility(
						t_g_view.ah_sb_icon_1[ui1_i],
						WGL_SW_NORMAL));

			RET_ON_ERR (c_wgl_set_visibility(
						t_g_view.ah_sb_icon_2[ui1_i],
						WGL_SW_NORMAL));
        }
		else
		{
			RET_ON_ERR (c_wgl_set_visibility(
						t_g_view.ah_sb_txt[ui1_i],
						WGL_SW_HIDE));

			RET_ON_ERR (c_wgl_set_visibility(
						t_g_view.ah_sb_icon_1[ui1_i],
						WGL_SW_HIDE));

			RET_ON_ERR (c_wgl_set_visibility(
						t_g_view.ah_sb_icon_2[ui1_i],
						WGL_SW_HIDE));
		}
	}

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_set_focus
 *
 * Description: The function set focus to select box buttons.
 *
 * Inputs:  e_sel_box_index                  Which select box button.
 * Inputs:  b_repaint                        auto repaint or not.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_sel_box_set_focus (WZD_SEL_BOX_BTN_INDEX_T e_sel_box_index, BOOL b_repaint)
{
    INT32   					i4_ret = WZDR_OK;

	t_g_view.t_sb_ctrl.ui4_index_current = (UINT32)e_sel_box_index + t_g_view.t_sb_ctrl.ui4_index_offset;

    i4_ret = c_wgl_set_focus(
                t_g_view.ah_sb_btn[e_sel_box_index],
                b_repaint);

    RET_ON_ERR (i4_ret);

	/* sent item lose focus & get focuse message */
	if (NULL != t_g_view.t_sb_info.pf_data_chg_nfy)
	{
		t_g_view.t_sb_info.pf_data_chg_nfy (WZD_SEL_BOX_MSG_ITEM_FOCUSED, (VOID*)t_g_view.t_sb_ctrl.ui4_index_current, NULL); 
	}

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_get_btn_idx
 *
 * Description: The function get index of select box buttons.
 *
 * Inputs:  ui4_idx                 	Which select box button.
 *
 * Outputs: -
 *
 * Returns: WZD_SEL_BOX_BTN_INDEX_T
 *          
 ----------------------------------------------------------------------------*/
WZD_SEL_BOX_BTN_INDEX_T wzd_view_sel_box_get_btn_idx (UINT32 ui4_idx)
{
	WZD_SEL_BOX_BTN_INDEX_T 	e_sb_idx;
	
	/* map select box btn */
	e_sb_idx = (WZD_SEL_BOX_BTN_INDEX_T)(ui4_idx - t_g_view.t_sb_ctrl.ui4_index_offset);
	
	if (e_sb_idx < WZD_SEL_BOX_BTN_01 || e_sb_idx >= WZD_SEL_BOX_BTN_COUNT)
	{
		e_sb_idx = WZD_SEL_BOX_BTN_01;
	}

	return e_sb_idx;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_set_text
 *
 * Description: The function set text to select box buttons.
 *
 * Inputs:  e_sel_box_index                 Which select box button.
 * Inputs:  pw2s_text                       The text to set.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_sel_box_set_text (UINT32 ui4_idx, UTF16_T* pw2s_text)
{
	WZD_SEL_BOX_BTN_INDEX_T 	e_sb_idx;
	
	if (NULL == pw2s_text)
	{
		return WZDR_INV_ARG;
	}

	/* map select box btn */
	e_sb_idx = (WZD_SEL_BOX_BTN_INDEX_T)(ui4_idx - t_g_view.t_sb_ctrl.ui4_index_offset);
	
	if (e_sb_idx < WZD_SEL_BOX_BTN_01 || e_sb_idx >= WZD_SEL_BOX_BTN_COUNT)
	{
		e_sb_idx = WZD_SEL_BOX_BTN_01;
	}

    RET_ON_ERR (c_wgl_do_cmd (t_g_view.ah_sb_txt[e_sb_idx],
			                  WGL_CMD_TEXT_SET_TEXT,
			                  WGL_PACK (pw2s_text),
			                  WGL_PACK ((UINT16)0xFFFF)));

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_set_plus_icon
 *
 * Description: The function set select box plus icon.
 *
 * Inputs:  -
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
INT32 wzd_view_sel_box_set_plus_icon (
                                WGL_HIMG_TPL_T  h_plus_icon,
                                BOOL            b_repaint)
{
	WGL_IMG_INFO_T              t_img_info;

    t_img_info.e_type = WGL_IMG_SET_STANDARD;
    t_img_info.u_img_data.t_standard.t_enable = h_plus_icon;
    t_img_info.u_img_data.t_standard.t_disable = h_plus_icon;
    t_img_info.u_img_data.t_standard.t_highlight = h_plus_icon;

    RET_ON_ERR (c_wgl_do_cmd(t_g_view.h_sb_icon_plus,
		                     WGL_CMD_GL_SET_IMAGE,
		                     (VOID*)WGL_IMG_FG,
		                     (VOID*)&t_img_info));

    if (b_repaint)
    {
        RET_ON_ERR (c_wgl_repaint (t_g_view.h_sb_icon_plus, NULL, TRUE));
    }

    return WZDR_OK;
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_get_btn_handle
 *
 * Description: The function get handle of select box buttons.
 *
 * Inputs:  e_sel_box_index                 Which select box button.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
HANDLE_T wzd_view_sel_box_get_btn_handle (UINT32 ui4_idx)
{
	WZD_SEL_BOX_BTN_INDEX_T 	e_sb_idx;
	
	/* map select box btn */
	e_sb_idx = (WZD_SEL_BOX_BTN_INDEX_T)(ui4_idx - t_g_view.t_sb_ctrl.ui4_index_offset);
	
	if (e_sb_idx >= WZD_SEL_BOX_BTN_01 && e_sb_idx < WZD_SEL_BOX_BTN_COUNT)
	{
		return t_g_view.ah_sb_btn[e_sb_idx];
	}
	else
	{
		return t_g_view.ah_sb_btn[WZD_SEL_BOX_BTN_01];
	}
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_get_txt_handle
 *
 * Description: The function get handle of select box text.
 *
 * Inputs:  e_sel_box_index                 Which select box button.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
HANDLE_T wzd_view_sel_box_get_txt_handle (UINT32 ui4_idx)
{
	WZD_SEL_BOX_BTN_INDEX_T 	e_sb_idx;

	/* map select box btn */
	e_sb_idx = (WZD_SEL_BOX_BTN_INDEX_T)(ui4_idx - t_g_view.t_sb_ctrl.ui4_index_offset);
	
	if (e_sb_idx >= WZD_SEL_BOX_BTN_01 && e_sb_idx < WZD_SEL_BOX_BTN_COUNT)
	{
		return t_g_view.ah_sb_txt[e_sb_idx];
	}
	else
	{
		return t_g_view.ah_sb_txt[WZD_SEL_BOX_BTN_01];
	}
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_get_icon_1_handle
 *
 * Description: The function get handle of select box first icon.
 *
 * Inputs:  e_sel_box_index                 Which select box button.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
HANDLE_T wzd_view_sel_box_get_icon_1_handle (UINT32 ui4_idx)
{
    WZD_SEL_BOX_BTN_INDEX_T 	e_sb_idx;

	/* map select box btn */
	e_sb_idx = (WZD_SEL_BOX_BTN_INDEX_T)(ui4_idx - t_g_view.t_sb_ctrl.ui4_index_offset);
	
	if (e_sb_idx >= WZD_SEL_BOX_BTN_01 && e_sb_idx < WZD_SEL_BOX_BTN_COUNT)
	{
		return t_g_view.ah_sb_icon_1[e_sb_idx];
	}
	else
	{
		return t_g_view.ah_sb_icon_1[WZD_SEL_BOX_BTN_01];
	}
}

/*-----------------------------------------------------------------------------
 * Name: wzd_view_sel_box_get_icon_2_handle
 *
 * Description: The function get handle of select box second icon.
 *
 * Inputs:  e_sel_box_index                 Which select box button.
 *
 * Outputs: -
 *
 * Returns: 0                      Successful.
 *          Any other values       Failed.
 ----------------------------------------------------------------------------*/
HANDLE_T wzd_view_sel_box_get_icon_2_handle (UINT32 ui4_idx)
{
	WZD_SEL_BOX_BTN_INDEX_T 	e_sb_idx;

	/* map select box btn */
	e_sb_idx = (WZD_SEL_BOX_BTN_INDEX_T)(ui4_idx - t_g_view.t_sb_ctrl.ui4_index_offset);
	
	if (e_sb_idx >= WZD_SEL_BOX_BTN_01 && e_sb_idx < WZD_SEL_BOX_BTN_COUNT)
	{
		return t_g_view.ah_sb_icon_2[e_sb_idx];
	}
	else
	{
		return t_g_view.ah_sb_icon_2[WZD_SEL_BOX_BTN_01];
	}
}

