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
 * $RCSfile: wzd_view.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 *
 * Description:
 *         This file contains function prototypes to support view commands of
 * the Wizard application.
 *
 *---------------------------------------------------------------------------*/

#ifndef _WZD_VIEW_H_
#define _WZD_VIEW_H_

/*---------------------------------------------------------------------------
                    include files
----------------------------------------------------------------------------*/
#include "c_wgl.h"
#include "u_wgl_common.h"

#include "wizard/wzd.h"
#include "res/wizard/wzd_cfg.h"

/*
    Defines.
*/
#ifdef APP_IMG_UI
    #define  WZD_WIDGET_STYLE             ((UINT32) 0)
#else /* #ifndef APP_IMG_UI */
    #define  WZD_WIDGET_STYLE             WGL_STL_GL_NO_IMG_UI
#endif /* APP_IMG_UI */

#define WZD_CUSTOM_TEXT(_txt)    			((UTF16_T*)L##_txt)

/*
   Focused widget types.
*/
typedef enum
{
    WZD_FOCUS_WIDGET_SETI_LST = 0,         /* setting list is focused */
#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
    WZD_FOCUS_WIDGET_CODE_FRM,
#endif
}   WZD_FOCUS_WIDGET_T;


/*
   Title types.
*/
#ifdef WZD_TITLE_TYPE_PAGE_FIRST
typedef enum
{
    WZD_TITLE_TYPE_SETI = 0,              /* wizard title */
    WZD_TITLE_TYPE_WZD                    /* setting title */
}   WZD_TITLE_TYPE_T;
#else
typedef enum
{
    WZD_TITLE_TYPE_WZD = 0,               /* wizard title */
    WZD_TITLE_TYPE_SETI                   /* setting title */
}   WZD_TITLE_TYPE_T;
#endif

/*
   Help types.
*/
typedef enum
{
    WZD_HELP_TYPE_BACK = 0,               /* back */
    WZD_HELP_TYPE_SELECT,                 /* select */
    WZD_HELP_TYPE_ENTER,                  /* enter */
    WZD_HELP_TYPE_EXIT,                   /* exit */
#ifdef APP_DVBC_SUPPORT
    WZD_HELP_TYPE_SELECT_EX ,
    WZD_HELP_TYPE_ENTER_EX
#endif
}   WZD_HELP_TYPE_T;

/*
   Structure for WZD_PAGE_TYPE_DESC_LIST_WITH_ICON page type
*/
typedef struct
{
    GL_RECT_T           t_rect;
    WGL_HIMG_TPL_T      at_img_tpl[SETI_LB_ELEM_NUM];
}   WZD_PAGE_INFO_ICON_DATA;

/* Enum of the footer buttons */
typedef enum _WZD_FOOTER_BTN_INDEX_T
{
    WZD_FOOTER_BTN_01 = 0,
    WZD_FOOTER_BTN_02,
    WZD_FOOTER_BTN_03,
    WZD_FOOTER_BTN_COUNT  /* 3 */
}WZD_FOOTER_BTN_INDEX_T;

/*
	Select Box Widget
*/

/* Enum the box of the select box */
typedef enum _WZD_SEL_BOX_BTN_INDEX_T
{
    WZD_SEL_BOX_BTN_01 = 0,
    WZD_SEL_BOX_BTN_02,
    WZD_SEL_BOX_BTN_03,
    WZD_SEL_BOX_BTN_04,
    WZD_SEL_BOX_BTN_05,
    WZD_SEL_BOX_BTN_06,
    WZD_SEL_BOX_BTN_07,
    WZD_SEL_BOX_BTN_COUNT  /* 7 */
}WZD_SEL_BOX_BTN_INDEX_T;

/* Enum the move direction of the select box frm */
typedef enum _WZD_SEL_BOX_FRM_MOVE_T
{
    WZD_SEL_BOX_FRM_MOVE_CENTER = 0,
    WZD_SEL_BOX_FRM_MOVE_LEFT,
    WZD_SEL_BOX_FRM_MOVE_RIGHT
}WZD_SEL_BOX_FRM_MOVE_T;

/* Select box data change notification */
#define WZD_SEL_BOX_MSG_ITEM_FOCUSED		(1)     /* focused button index msg */
#define WZD_SEL_BOX_MSG_ITEM_LOSE_FOCUSED	(2)     /* lose focused button index msg */
#define WZD_SEL_BOX_MSG_ITEM_LEFT_SHIFT		(3)     /* left shift msg */
#define WZD_SEL_BOX_MSG_ITEM_RIGHT_SHIFT	(4)     /* right shift msg */
#define WZD_SEL_BOX_MSG_KEY_INPUT    		(5)     /* other key code input msg */

/* For select box data change */
typedef VOID (*wzd_view_sel_box_data_change_nfy_fct)(
	                                 UINT32   ui4_msg,
	                                 VOID*    pv_param1,
	                                 VOID*    pv_param2);

typedef struct _WZD_VIEW_SEL_BOX_INFO_T
{
	UINT32                      ui4_index_total;					/* The total num of select box button */
    wzd_view_sel_box_data_change_nfy_fct  pf_data_chg_nfy; 			/* Select box data change callback function */
}WZD_VIEW_SEL_BOX_INFO_T;


/* Common dialog related */

/* Dlg style mask */
#define WZD_DLG_STYLE_MASK_2_BTN                MAKE_BIT_MASK_32(0)  /* If not defined, treat as 1 button */
#define WZD_DLG_STYLE_MASK_AUTO_HIDE            MAKE_BIT_MASK_32(1)
#define WZD_DLG_STYLE_MASK_WITH_DESC			MAKE_BIT_MASK_32(2)
#define WZD_DLG_STYLE_MASK_WITH_DESC_MUTI_LINE	MAKE_BIT_MASK_32(3)

/* Data change notification*/
#define   WZD_DLG_MSG_BTN_FOCUSED       (1)     /* pv1= (WZD_DLG_BTN_TYPE_T) BTN index*/
#define   WZD_DLG_MSG_KEY_INPUT         (2)     /* pv1=ui4_key_code, pv2 = (WZD_DLG_BTN_TYPE_T) BTN index */
#define   WZD_DLG_MSG_HIDE_TIMEOUT      (3)     /* Notify client auto hide, please call wzd_dlg_hide() when received */
#define   WZD_DLG_MSG_DLG_HIDED       (4)     /* Notify client dialog is hidden */
#define   WZD_DLG_MSG_INVALID       (5)     /* Valid message value must small than this one */

typedef enum _WZD_DLG_BTN_TYPE_T
{
    WZD_DLG_BTN_TYPE_01,
    WZD_DLG_BTN_TYPE_02,
    WZD_DLG_BTN_TYPE_COUNT
}WZD_DLG_BTN_TYPE_T;

typedef VOID (*wzd_dlg_data_change_nfy_fct)(VOID*    pv_tag,
                                            UINT32   ui4_msg,
                                            VOID*    pv_param1,
                                            VOID*    pv_param2);


typedef struct _WZD_DLG_INIT_T
{
    HANDLE_T                        h_parent;
    UINT32                          ui4_style_mask;
    WGL_FONT_INFO_T                 t_fnt_info;
    wzd_dlg_data_change_nfy_fct     pf_fct;
    VOID*                           pv_tag;
    UINT32                          ui4_hide_timer;
    WZD_DLG_BTN_TYPE_T              e_default_focus_btn;
}WZD_DLG_INIT_T;

typedef struct _WZD_DLG_CONTROL_T
{
    HANDLE_T                        h_frame;
    HANDLE_T                        h_text;
	HANDLE_T                        h_desc_text;
    HANDLE_T                        h_btn_01;
    HANDLE_T                        h_btn_02;
    HANDLE_T                        h_hide_timer;
	HANDLE_T						h_icon;
    WGL_HIMG_TPL_T                  h_frame_bk;
    WGL_HIMG_TPL_T                  h_btn_bk;
    WGL_HIMG_TPL_T                  h_btn_hlt;
    BOOL                            b_is_show;
    WZD_DLG_BTN_TYPE_T              e_focused_btn;

    /* From init data */
    HANDLE_T                        h_parent;
    UINT32                          ui4_style_mask;
    WGL_FONT_INFO_T                 t_fnt_info;
    wzd_dlg_data_change_nfy_fct     pf_fct;
    VOID*                           pv_tag;
    UINT32                          ui4_hide_timer;
    WZD_DLG_BTN_TYPE_T              e_default_focus_btn;
}WZD_DLG_CONTROL_T;

/*
   View model.
*/
extern INT32  wzd_view_init    (VOID);
extern INT32  wzd_view_destroy (VOID);
extern INT32  wzd_view_get_focus_widget (WZD_FOCUS_WIDGET_T* pe_focus_widget);
extern INT32  wzd_view_set_focus_widget (WZD_FOCUS_WIDGET_T e_focus_widget);
extern UINT32 wzd_view_get_osd_offset_x (VOID);
extern UINT32 wzd_view_get_osd_offset_y (VOID);
extern UINT32 wzd_view_get_osd_width (VOID);
extern UINT32 wzd_view_get_osd_height (VOID);
extern CHAR*  wzd_view_get_font_name (VOID);
extern GL_HPLANE_T wzd_view_get_plane (VOID);
extern HANDLE_T wzd_view_get_canvas (VOID);

/*
   Main frame.
*/
extern INT32 wzd_view_main_frm_set_visibility (BOOL b_show);
extern INT32 wzd_view_main_frm_show (BOOL b_show);
extern INT32 wzd_view_main_frm_repaint (VOID);

/*
   Title text of the setting list.
*/
extern INT32 wzd_view_title_txt_set_visibility (BOOL b_show);
extern INT32 wzd_view_title_txt_set_text (UTF16_T*    pw2s_text);
extern INT32 wzd_view_title_txt_set_text_ex (UTF16_T* pw2s_msg, UTF16_T* pw2s_txt);
extern INT32 wzd_view_title_set_htxt (UTF16_T* pw2s_text, WGL_HIMG_TPL_T h_img);
extern INT32 wzd_view_title_txt_repaint (VOID);

/*
   Description text of the setting list.
*/
extern INT32 wzd_view_desc_txt_set_visibility (BOOL b_show);
extern INT32 wzd_view_desc_txt_set_text (UTF16_T* pw2s_text);
extern INT32 wzd_view_desc_txt_repaint (VOID);

/*
   Setting list.
*/
extern INT32 wzd_view_seti_lst_set_visibility (BOOL b_show);
extern INT32 wzd_view_seti_lst_clr_elems (UINT16 ui2_start, UINT16 ui2_end);
extern INT32 wzd_view_seti_lst_enable_control_key (BOOL b_enable);
extern INT32 wzd_view_seti_lst_get_hlt_idx (UINT16* pui2_idx);
extern INT32 wzd_view_seti_lst_hlt_elem (UINT16 ui2_idx);
extern INT32 wzd_view_seti_lst_unhlt_elem (UINT16 ui2_idx);
extern INT32 wzd_view_seti_lst_set_elem_num (UINT16 ui2_elem_num);
extern INT32 wzd_view_seti_lst_set_elem_text (UINT16 ui2_elem_idx, UTF16_T* pw2s_text);
extern INT32 wzd_view_seti_lst_repaint_elems (UINT16 ui2_start, UINT16 ui2_end);
extern INT32 wzd_view_seti_lst_reset (BOOL b_repaint);
extern INT32 wzd_view_seti_lst_repaint (VOID);

/*
   Scan progrss bar.
*/
extern INT32 wzd_view_scan_bar_set_visibility (BOOL b_show);
extern INT32 wzd_view_scan_bar_set_pos (INT32 i4_progress);
extern INT32 wzd_view_scan_bar_repaint (VOID);

/*
   Setting list with icon
*/
extern INT32 wzd_view_seti_icon_set_visibility (BOOL b_show);
extern INT32 wzd_view_seti_icon_load_img (WZD_PAGE_INFO_ICON_DATA* pt_icon_data,
                                          UINT16                   ui2_idx);
extern INT32 wzd_view_seti_icon_repaint (VOID);

#ifdef APP_WIZARD_CODE_INPUT_SUPPORT
/*
   Code input box.
*/
extern INT32 wzd_view_code_box_set_visibility_focus (BOOL b_show);
extern INT32 wzd_view_code_box_setup (UINT8    ui1_code_elem_num,
                                      UINT8    aui1_code_style[],
                                      UINT16   aw2s_code_sep_char[]);
extern INT32 wzd_view_code_box_repaint (VOID);
extern INT32 wzd_view_code_box_set_focus_next_digit (VOID);
extern INT32 wzd_view_code_box_set_focus_prev_digit (VOID);
extern INT32 wzd_view_code_box_set_code_num (UINT64    ui8_code_num, BOOL  b_repaint);
extern INT32 wzd_view_code_box_get_code_num (UINT64*   pui8_code_num);
extern INT32 wzd_view_code_txt_set_text (UTF16_T*    pw2s_text);
extern INT32 wzd_view_code_txt_clear_text (BOOL    b_repaint);
extern INT32 wzd_view_code_txt_repaint (VOID);
#endif

extern INT32 wzd_view_get_layout_frm (HANDLE_T*  ph_layout_frm) ;

#ifdef APP_2K12_RETAIL_DEMO_MODE
extern INT32 wzd_view_get_main_frm (HANDLE_T*  ph_layout_frm);
extern INT32 wzd_view_get_base_frm (HANDLE_T*  ph_main_frm);
#endif

extern INT32 wzd_view_footer_set_visibility (BOOL    b_show);
extern INT32 wzd_view_footer_show (BOOL    b_show);
extern INT32 wzd_view_footer_frm_repaint (VOID);

extern INT32 wzd_view_footer_set_btn_num (const UINT8 ui1_btn_num);

extern INT32 wzd_view_footer_set_text (WZD_FOOTER_BTN_INDEX_T e_footer_index, UTF16_T* pw2s_text);

extern INT32 wzd_view_footer_set_enable (WZD_FOOTER_BTN_INDEX_T e_footer_index, BOOL b_enable);

extern BOOL  wzd_view_footer_get_enable (WZD_FOOTER_BTN_INDEX_T e_footer_index);

extern INT32 wzd_view_footer_set_focus (WZD_FOOTER_BTN_INDEX_T e_footer_index, BOOL b_repaint);

extern HANDLE_T wzd_view_footer_get_handle (WZD_FOOTER_BTN_INDEX_T e_footer_index);

extern INT32 wzd_view_footer_update_btn_navigation (VOID);

/* Select box widget */
extern INT32 wzd_view_sel_box_show (BOOL b_show);
extern INT32 wzd_view_sel_box_frm_repaint (VOID);
extern INT32 wzd_view_sel_box_set_info_data (WZD_VIEW_SEL_BOX_INFO_T*	pt_info_data);

extern INT32 wzd_view_sel_box_set_focus (WZD_SEL_BOX_BTN_INDEX_T e_sel_box_index, BOOL b_repaint);
extern INT32 wzd_view_sel_box_set_text (UINT32 ui4_idx, UTF16_T* pw2s_text);
extern INT32 wzd_view_sel_box_set_plus_icon (WGL_HIMG_TPL_T h_plus_icon, BOOL b_repaint);

extern HANDLE_T wzd_view_sel_box_get_btn_handle (UINT32 ui4_idx);
extern HANDLE_T wzd_view_sel_box_get_txt_handle (UINT32 ui4_idx);
extern HANDLE_T wzd_view_sel_box_get_icon_1_handle (UINT32 ui4_idx);
extern HANDLE_T wzd_view_sel_box_get_icon_2_handle (UINT32 ui4_idx);

extern WZD_SEL_BOX_BTN_INDEX_T wzd_view_sel_box_get_btn_idx (UINT32 ui4_idx);

/* Full screen dialog widget */
extern INT32 wzd_view_full_screen_dlg_show (BOOL b_has_button);

extern INT32 wzd_view_full_screen_dlg_hide (VOID);

extern INT32 wzd_view_full_screen_dlg_repaint (VOID);

extern INT32 wzd_view_full_screen_dlg_set_icon (
                                WGL_HIMG_TPL_T  h_demo_icon,
                                BOOL            b_repaint);
extern INT32 wzd_view_full_screen_dlg_set_btn_text (
								UTF16_T*		pw2s_text,
								BOOL            b_repaint);
extern INT32 wzd_view_full_screen_dlg_set_btn_proc_fct (wgl_widget_proc_fct pf_proc);
extern INT32 wzd_view_full_screen_dlg_set_text (
								UTF16_T*		pw2s_text,
								BOOL            b_repaint);

extern BOOL wzd_view_full_screen_dlg_is_show (VOID);


/* Right area demo pictures */
extern INT32 wzd_view_demo_pic_show (BOOL    b_show);

extern INT32 wzd_view_demo_pic_set_image (
                                WGL_HIMG_TPL_T  h_demo_image,
                                BOOL            b_repaint);

extern INT32 wzd_view_demo_txt_set_text (UTF16_T*  pw2s_text,
                                            HANDLE_T    h_bk_img);

extern INT32 wzd_view_demo_txt_show (BOOL        b_show,
                                            BOOL        b_repaint);

extern INT32 wzd_view_right_icon_show (BOOL    b_show, BOOL    b_repaint);

extern INT32 wzd_view_right_icon_set_image (WGL_HIMG_TPL_T  h_right_icon,
                                            BOOL            b_repaint);

/* Dialog */
extern INT32 wzd_dlg_create(
                    WZD_DLG_INIT_T*     pt_dlg_init,        /* In  */
                    HANDLE_T*           ph_dlg_handle);      /* Out */

extern INT32 wzd_dlg_destroy(
                    HANDLE_T            h_dlg_handle);

extern INT32 wzd_dlg_show(
                    HANDLE_T            h_dlg_handle,
                    BOOL            	b_repaint);

extern INT32 wzd_dlg_hide(
                    HANDLE_T            h_dlg_handle);

extern INT32 wzd_dlg_set_btn_text(
                    HANDLE_T            h_dlg_handle,
                    WZD_DLG_BTN_TYPE_T  e_btn_index,
                    UTF16_T*            pw2s_text,
                    BOOL                b_repaint);

extern INT32 wzd_dlg_set_focus_to_btn(
                    HANDLE_T            h_dlg_handle,
                    WZD_DLG_BTN_TYPE_T  e_btn_index,
                    BOOL                b_repaint);
                    
extern INT32 wzd_dlg_set_text(
                    HANDLE_T            h_dlg_handle,
                    UTF16_T*            pw2s_text,
                    BOOL                b_repaint);

extern INT32 wzd_dlg_set_desc_text(
                    HANDLE_T            h_dlg_handle,
                    UTF16_T*            pw2s_text,
                    BOOL                b_repaint);

/* Right area demo text */
extern INT32 wzd_view_scan_txt_set_visibility (BOOL    b_show);
extern INT32 wzd_view_scan_txt_repaint (VOID);
extern INT32 wzd_view_scan_txt_set_text (UTF16_T*    pw2s_text);

extern INT32 wzd_view_set_main_frm_bg (WGL_HIMG_TPL_T h_img, BOOL b_repaint);

/* WGL image handle */
extern WGL_HIMG_TPL_T       h_g_custom_img_network_setup;
extern WGL_HIMG_TPL_T       h_g_custom_img_choose_signal;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_all_av_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_dtv_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_component_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_composite_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_HDMI_1_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_HDMI_2_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_HDMI_3_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_HDMI_4_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_PC_hlt;
extern WGL_HIMG_TPL_T       h_g_custom_img_signal_AudioOut;

extern WGL_HIMG_TPL_T       h_g_custom_img_getting_started_rc;
extern WGL_HIMG_TPL_T       h_g_custom_img_keypad;

extern WGL_HIMG_TPL_T       h_g_custom_img_demo_scan;
extern WGL_HIMG_TPL_T       h_g_custom_img_demo_scan_comp_HL;
extern WGL_HIMG_TPL_T       h_g_custom_img_demo_scan_DTV_HL;
extern WGL_HIMG_TPL_T       h_g_custom_img_demo_scan_HDMI1_HL;
extern WGL_HIMG_TPL_T       h_g_custom_img_demo_scan_HDMI2_HL;
extern WGL_HIMG_TPL_T       h_g_custom_img_demo_scan_HDMI3_HL;
extern WGL_HIMG_TPL_T       h_g_custom_img_demo_scan_HDMI4_HL;
extern WGL_HIMG_TPL_T       h_g_custom_img_demo_scan_RGB_HL;

#endif /* _WZD_VIEW_H_ */


