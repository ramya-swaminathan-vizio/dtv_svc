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
 * $RCSfile: a_ui.h,v $
 * $Revision: #1 $
 * $Date: 2015/05/29 $
 * $Author: brianpc.huang $
 * $CCRevision: /main/DTV_X_HQ_int/DTV_X_ATSC/5 $
 * $SWAuthor: $
 * $MD5HEX: 0555add6f5bb32c55eaf504cbf527d75 $
 *
 * Description:
 *
 *---------------------------------------------------------------------------*/
#ifndef _A_UI_H_
#define _A_UI_H_

/*-----------------------------------------------------------------------------
                    include files
-----------------------------------------------------------------------------*/
#include "u_common.h"
#include "u_handle.h"
#include "u_wgl.h"
#include "u_wgl_common.h"
#include "app_util/a_common.h"

/*-----------------------------------------------------------------------------
                    macros, defines, typedefs, enums
-----------------------------------------------------------------------------*/

/* Return Value */
#define APP_UIR_OK                     ((INT32)  0)
#define APP_UIR_INV_ARG                ((INT32) -1)
#define APP_UIR_FAIL                   ((INT32) -2)
#define APP_UIR_OUT_OF_MEMORY          ((INT32) -3)
#define APP_UIR_WIDGET_CREATE_FAIL     ((INT32) -4)

/* - Simple Dialog - ========================================================= */
typedef enum
{
    UI_SIMPLE_DIALOG_STYLE_SMALL = 0,
    UI_SIMPLE_DIALOG_STYLE_MEDIUM,
    UI_SIMPLE_DIALOG_STYLE_BIG,
    UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY,
    UI_SIMPLE_DIALOG_STYLE_WARNING_MSG
} UI_SIMPLE_DIALOG_STYLE_T;

typedef VOID (*ui_simple_dialog_yes_cb_fct)(VOID);
typedef VOID (*ui_simple_dialog_no_cb_fct)(VOID);
typedef BOOL (*ui_simple_dialog_other_key_cb_fct)(UINT32 ui4_keycode);
typedef VOID (*ui_simple_dialog_info_cb_fct)(VOID);
typedef INT32 (*ui_simple_dialog_tts_cb_fct)(UTF16_T* pw2s_string);


typedef enum
{
    UI_SIMPLE_DIALOG_ANSWER_NO = 0,
    UI_SIMPLE_DIALOG_ANSWER_YES,
    UI_SIMPLE_DIALOG_ANSWER_INFO,
} UI_SIMPLE_DIALOG_ANSWER;

typedef struct _UI_SIMPLE_DIALOG_INIT_T
{
    HANDLE_T                     h_parent;
    wgl_widget_proc_fct          pf_wdgt_proc;
    UI_SIMPLE_DIALOG_STYLE_T     e_style;
    UINT16                       ui2_txt_align_type;
    GL_RECT_T*                   pt_rect;            /* For Information style only */
    GL_POINT_T*                  pt_begin_offset;    /* For Small/Medium/Big style only */
    BOOL                         b_default_answer;   /* For Small/Medium/Big style only */
    BOOL                         b_one_btn_mode;     /**< Determine whether there is only one button if e_style != UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY! */
    BOOL                         b_three_btn_mode;     /**< Determine whether there is three button if e_style != UI_SIMPLE_DIALOG_STYLE_INFOMATION_ONLY! */
    ui_simple_dialog_yes_cb_fct  pf_ui_simple_dialog_yes_cb_fct; /* For Small/Medium/Big style only */
    ui_simple_dialog_no_cb_fct   pf_ui_simple_dialog_no_cb_fct;  /* For Small/Medium/Big style only */
    ui_simple_dialog_info_cb_fct   pf_ui_simple_dialog_info_cb_fct;  /* For Small/Medium/Big style only */
    ui_simple_dialog_other_key_cb_fct  pf_ui_simple_dialog_other_key_cb_fct;  /* For other key process */
    ui_simple_dialog_tts_cb_fct    pf_ui_simple_dialog_tts_cb_fct;
    BOOL                         b_info_icon;
} UI_SIMPLE_DIALOG_INIT_T;


typedef struct _UI_SIMPLE_DIALOG_WIDGET_HANDLE_T {

    /* Widgets */
    HANDLE_T    h_frm_simple_dialog;   /* the main frame of the S-DLG */
    HANDLE_T    h_txt_txtinfo;         /* the text box */
    HANDLE_T    h_btn_yes;             /* the YES button */
    HANDLE_T    h_btn_no;              /* the NO button */
    HANDLE_T    h_btn_info;            /* the INFO button */

} UI_SIMPLE_DIALOG_WIDGET_HANDLE_T;

/* =========================================================================== */



/* - Slider Bar - ============================================================ */
#define UI_SLIDER_BAR_ATTR_NO_ICON  (MAKE_BIT_MASK_32 (0))

#define UI_SLIDER_BAR_ATTR_IS_NO_ICON(_x) ((((_x) & UI_SLIDER_BAR_ATTR_NO_ICON) == UI_SLIDER_BAR_ATTR_NO_ICON))

typedef enum
{
    UI_SLIDER_BAR_STYLE_BAR = 0,
    UI_SLIDER_BAR_STYLE_VOL,
    UI_SLIDER_BAR_STYLE_POINT
} UI_SLIDER_BAR_STYLE_T;


typedef enum
{
    UI_SLIDER_BAR_COMP_ID_FRAME = 0,
    UI_SLIDER_BAR_COMP_ID_PGBAR,
    UI_SLIDER_BAR_COMP_ID_TEXT
} UI_SLIDER_BAR_COMP_ID_T;

typedef VOID (*ui_slider_bar_pos_chg_nfy_fct)(INT32 i4_pos);
typedef INT32 (*ui_slider_bar_get_pos_cb_fct)(VOID);

typedef struct _UI_SLIDER_BAR_INIT_T
{
    HANDLE_T                     h_parent;
    wgl_widget_proc_fct          pf_wdgt_proc;
    UI_SLIDER_BAR_STYLE_T        e_style;
    GL_POINT_T*                  pt_begin_offset;

    ui_slider_bar_pos_chg_nfy_fct  pf_ui_slider_bar_pos_chg_nfy_fct;
    ui_slider_bar_get_pos_cb_fct   pf_ui_slider_bar_get_pos_cb_fct;
} UI_SLIDER_BAR_INIT_T;

typedef struct UI_SLIDER_BAR_INIT_EX_T
{
    UI_SLIDER_BAR_INIT_T         t_ui_slider_bar_init;
    UINT32                       ui4_attr_bits;
} UI_SLIDER_BAR_INIT_EX_T;

/* =========================================================================== */

/*-----------------------------------------------------------------------------
                    data declaraions
 ----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
                    functions declarations
-----------------------------------------------------------------------------*/

extern INT32 a_ui_init(VOID);

extern INT32 a_ui_slider_bar_create(
                      UI_SLIDER_BAR_INIT_T*    pt_ui_slider_bar_init,     /* In  */
                      HANDLE_T*                ph_slider);                /* Out */

extern INT32 a_ui_slider_bar_create_ex(
                      UI_SLIDER_BAR_INIT_EX_T* pt_ui_slider_bar_init_ex,  /* In  */
                      HANDLE_T*                ph_slider);                /* Out */

extern INT32 a_ui_slider_bar_destroy(
                      HANDLE_T    h_frm_slider
);

extern INT32 a_ui_slider_bar_default_msg_proc(
                      HANDLE_T    h_widget,
                      UINT32      ui4_msg,
                      VOID*       pv_param1,
                      VOID*       pv_param2,
                      BOOL        is_headphone_vol);

extern INT32 a_ui_slider_bar_set_range(
                      HANDLE_T    h_frm_slider,
                      INT32       i4_min,
                      INT32       i4_max);

extern INT32 a_ui_slider_bar_get_range(
                      HANDLE_T    h_frm_slider,
                      INT32*      pi4_min,
                      INT32*      pi4_max);


extern INT32 a_ui_slider_bar_set_pos(
                      HANDLE_T    h_frm_slider,
                      INT32       i4_pos,
                      BOOL        is_headphone_vol);

extern INT32 a_ui_slider_bar_get_pos(
                      HANDLE_T    h_frm_slider,
                      INT32*      pi4_pos);

extern INT32 a_ui_slider_bar_set_style(
                      HANDLE_T                 h_frm_slider,
                      UI_SLIDER_BAR_STYLE_T    e_style);

extern INT32 a_ui_slider_bar_get_style(
                      HANDLE_T                 h_frm_slider,
                      UI_SLIDER_BAR_STYLE_T*   pe_style);

extern INT32 a_ui_slider_bar_set_title(
                      HANDLE_T            h_frm_slider,
                      UTF16_T*            w2s_title);

extern INT32 a_ui_slider_bar_set_pgbar_point_size(
                      HANDLE_T    h_frm_slider,
                      INT16       i2_w,
                      INT16       i2_h);

extern INT32 a_ui_slider_bar_show(
                      HANDLE_T       h_frm_slider,
                      BOOL           is_headphone_vol);

extern INT32 a_ui_slider_bar_repaint(
                      HANDLE_T       h_frm_slider);

extern INT32 a_ui_slider_bar_repaint_pgbar(
                      HANDLE_T       h_frm_slider);

extern INT32 a_ui_slider_bar_hide(
                      HANDLE_T       h_frm_slider);

extern INT32 a_ui_slider_bar_set_focus(HANDLE_T  h_frm_slider, BOOL b_repaint);

extern INT32 a_ui_slider_bar_set_pos_chg_nfy_fct(HANDLE_T                   h_frm_slider,
                                                 ui_slider_bar_pos_chg_nfy_fct pf_set_pos);

extern INT32 a_ui_slider_bar_set_get_pos_cb_fct(
                      HANDLE_T                     h_frm_slider,
                      ui_slider_bar_get_pos_cb_fct pf_get_pos);

extern INT32 a_ui_slider_bar_set_fast_mode_attr(HANDLE_T                 h_frm_slider,
                                                WGL_PG_FAST_MODE_ATTR_T* pt_pg_fast_mode_attr);

extern INT32 a_ui_slider_bar_get_fast_mode_attr(HANDLE_T                 h_frm_slider,
                                                WGL_PG_FAST_MODE_ATTR_T* pt_pg_fast_mode_attr);


extern INT32 a_ui_slider_bar_set_key_map(HANDLE_T             h_frm_slider,
                                         WGL_PG_KEY_MAP_T*    pt_pg_key_map);

extern INT32 a_ui_slider_bar_get_key_map(HANDLE_T             h_frm_slider,
                                         WGL_PG_KEY_MAP_T*    pt_pg_key_map);

extern INT32 a_ui_slider_bar_get_tag (
                      HANDLE_T  h_frm_slider,
                      VOID**    ppv_tag);

extern INT32 a_ui_slider_bar_set_tag (
                      HANDLE_T  h_frm_slider,
                      VOID*     pv_tag);

extern INT32 a_ui_slider_bar_set_alpha(
    HANDLE_T                  h_frm_slider,
    UI_SLIDER_BAR_COMP_ID_T   e_comp_id,
    UINT8                     ui1_alpha);


extern INT32 a_ui_slider_bar_get_alpha(
    HANDLE_T                  h_frm_slider,
    UI_SLIDER_BAR_COMP_ID_T   e_comp_id,
    UINT8*                    pui1_alpha);

extern INT32 a_ui_slider_bar_set_bk_img(HANDLE_T    h_frm_slider,
                                        HANDLE_T    h_img_tpl_frm_bk0,
                                        HANDLE_T    h_img_tpl_bar_pg_bar,
                                        HANDLE_T    h_img_tpl_bar_pg_bk0);

//#ifdef IMG_960X540_8888_UI
extern INT32 a_ui_slider_bar_set_caption_img(HANDLE_T    h_frm_slider,
                                             HANDLE_T    h_img_tpl_caption);
//#endif


/* ---------------------------------------------------------------- */
extern INT32 a_ui_simple_dialog_default_tts_cb_fct(UTF16_T* pw2s_string);

extern INT32 a_ui_simple_dialog_default_msg_proc(
                      HANDLE_T    h_widget,
                      UINT32      ui4_msg,
                      VOID*       pv_param1,
                      VOID*       pv_param2);

extern INT32 a_ui_simple_dialog_create(
                      UI_SIMPLE_DIALOG_INIT_T*    pt_ui_simple_dialog_init,   /* In  */
                      HANDLE_T*                   ph_simple_dialog);          /* Out */

extern INT32 a_ui_simple_dialog_set_focus(
                      HANDLE_T  h_simple_dialog,
                      BOOL      b_repaint);

extern INT32 a_ui_simple_dialog_show(HANDLE_T h_simple_dialog);

extern INT32 a_ui_simple_dialog_txt_txtinfo_repaint(HANDLE_T h_simple_dialog);

extern INT32 a_ui_simple_dialog_hide(HANDLE_T h_simple_dialog);

extern INT32 a_ui_simple_dialog_repaint(HANDLE_T            h_simple_dialog);

extern INT32 a_ui_simple_dialog_destory(HANDLE_T            h_simple_dialog);

extern INT32 a_ui_simple_dialog_get_widget(HANDLE_T                           h_simple_dialog,
                                           UI_SIMPLE_DIALOG_WIDGET_HANDLE_T*  pt_widget_handle);

extern INT32 a_ui_simple_dialog_set_text(
                      HANDLE_T            h_simple_dialog,
                      UTF16_T*            w2s_text);

extern INT32 a_ui_simple_dialog_set_text_rect(
                      HANDLE_T            h_simple_dialog,
                      GL_RECT_T           *pt_rect,
                      BOOL                b_repaint);

extern INT32 a_ui_simple_dialog_set_yes_text(
                      HANDLE_T            h_simple_dialog,
                      UTF16_T*            w2s_text);

extern INT32 a_ui_simple_dialog_set_no_text(
                      HANDLE_T            h_simple_dialog,
                      UTF16_T*            w2s_text);

extern INT32 a_ui_simple_dialog_set_yes_no_rect(
                      HANDLE_T            h_simple_dialog,
                      BOOL                b_btn_yes,
                      GL_RECT_T           *pt_rect,
                      BOOL                b_repaint);

extern INT32 a_ui_simple_dialog_set_answer(
                      HANDLE_T            h_simple_dialog,
                      BOOL                b_answer);

extern INT32 a_ui_simple_dialog_set_answer_ex(HANDLE_T                  h_simple_dialog,
                                              UI_SIMPLE_DIALOG_ANSWER   e_answer);

extern INT32 a_ui_simple_dialog_set_yes_fct(
                      HANDLE_T                    h_simple_dialog,
                      ui_simple_dialog_yes_cb_fct pf_yes);

extern INT32 a_ui_simple_dialog_set_no_fct(
                      HANDLE_T                    h_simple_dialog,
                      ui_simple_dialog_no_cb_fct pf_no);

extern INT32 a_ui_simple_dialog_set_info_fct(HANDLE_T                    h_simple_dialog,
                                            ui_simple_dialog_info_cb_fct pf_info);

extern INT32 a_ui_simple_dialog_set_tts_fct(HANDLE_T                    h_simple_dialog,
                                               ui_simple_dialog_tts_cb_fct  pf_tts);

extern INT32 a_ui_simple_dialog_set_text_align(HANDLE_T   h_simple_dialog,
                                               UINT8       ui1_align);

extern INT32 a_ui_slider_bar_set_cnt_inset(HANDLE_T  h_frm_slider,
                                    WGL_INSET_T *pt_inset);

extern INT32 a_ui_slider_bar_get_cnt_inset(HANDLE_T  h_frm_slider,
                                    WGL_INSET_T *pt_inset);

extern INT32 a_ui_simple_dialog_set_other_key_cb_fct(HANDLE_T h_simple_dialog, ui_simple_dialog_other_key_cb_fct pf_other);
extern INT32 a_ui_simple_dialog_set_btn_state(HANDLE_T  h_simple_dialog, BOOL b_yes_btn);
extern INT32 a_ui_simple_dialog_set_info_text(HANDLE_T            h_simple_dialog,
                                     UTF16_T*            w2s_text);
extern INT32 a_ui_simple_dialog_set_offset(HANDLE_T  h_simple_dialog,GL_RECT_T* pt_rect,  GL_POINT_T* pt_begin_offset,UI_SIMPLE_DIALOG_STYLE_T e_style);
extern INT32 a_ui_simple_dialog_set_default_msg_proc(HANDLE_T  h_simple_dialog, wgl_widget_proc_fct msg_proc );
#endif /* _A_UI_H_ */
